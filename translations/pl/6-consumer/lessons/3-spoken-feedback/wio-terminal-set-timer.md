<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-26T07:19:11+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "pl"
}
-->
# Ustaw timer - Wio Terminal

W tej części lekcji wywołasz swój kod serverless, aby zrozumieć mowę i ustawić timer na Wio Terminal na podstawie wyników.

## Ustaw timer

Tekst, który wraca z wywołania funkcji zamiany mowy na tekst, musi zostać przesłany do Twojego kodu serverless, aby został przetworzony przez LUIS, który zwróci liczbę sekund dla timera. Ta liczba sekund może być użyta do ustawienia timera.

Mikrokontrolery nie mają natywnego wsparcia dla wielu wątków w Arduino, więc nie ma standardowych klas timerów, jak w Pythonie czy innych językach wyższego poziomu. Zamiast tego możesz użyć bibliotek timerów, które działają poprzez mierzenie upływu czasu w funkcji `loop` i wywoływanie funkcji, gdy czas się skończy.

### Zadanie - wyślij tekst do funkcji serverless

1. Otwórz projekt `smart-timer` w VS Code, jeśli nie jest już otwarty.

1. Otwórz plik nagłówkowy `config.h` i dodaj URL dla swojej aplikacji funkcji:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    Zamień `<URL>` na URL dla swojej aplikacji funkcji, który uzyskałeś w ostatnim kroku poprzedniej lekcji, wskazując adres IP lokalnej maszyny, na której działa aplikacja funkcji.

1. Utwórz nowy plik w folderze `src` o nazwie `language_understanding.h`. Będzie on używany do zdefiniowania klasy, która wyśle rozpoznaną mowę do Twojej aplikacji funkcji, aby została przekształcona na sekundy za pomocą LUIS.

1. Dodaj następujące elementy na początku tego pliku:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    To zawiera potrzebne pliki nagłówkowe.

1. Zdefiniuj klasę o nazwie `LanguageUnderstanding` i zadeklaruj instancję tej klasy:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. Aby wywołać aplikację funkcji, musisz zadeklarować klienta WiFi. Dodaj następujące elementy do sekcji `private` klasy:

    ```cpp
    WiFiClient _client;
    ```

1. W sekcji `public` zadeklaruj metodę o nazwie `GetTimerDuration`, aby wywołać aplikację funkcji:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. W metodzie `GetTimerDuration` dodaj następujący kod, aby zbudować JSON, który zostanie wysłany do aplikacji funkcji:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    To konwertuje tekst przekazany do metody `GetTimerDuration` na następujący JSON:

    ```json
    {
        "text" : "<text>"
    }
    ```

    gdzie `<text>` to tekst przekazany do funkcji.

1. Poniżej tego dodaj następujący kod, aby wywołać aplikację funkcji:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    To wykonuje żądanie POST do aplikacji funkcji, przekazując ciało JSON i uzyskując kod odpowiedzi.

1. Dodaj następujący kod poniżej tego:

    ```cpp
    int seconds = 0;
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonObject obj = doc.as<JsonObject>();
        seconds = obj["seconds"].as<int>();
    }
    else
    {
        Serial.print("Failed to understand text - error ");
        Serial.println(httpResponseCode);
    }
    ```

    Ten kod sprawdza kod odpowiedzi. Jeśli wynosi 200 (sukces), liczba sekund dla timera jest pobierana z ciała odpowiedzi. W przeciwnym razie błąd jest wysyłany do monitora szeregowego, a liczba sekund jest ustawiana na 0.

1. Dodaj następujący kod na końcu tej metody, aby zamknąć połączenie HTTP i zwrócić liczbę sekund:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. W pliku `main.cpp` dołącz ten nowy nagłówek:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Na końcu funkcji `processAudio` wywołaj metodę `GetTimerDuration`, aby uzyskać czas trwania timera:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    To konwertuje tekst z wywołania klasy `SpeechToText` na liczbę sekund dla timera.

### Zadanie - ustaw timer

Liczba sekund może być użyta do ustawienia timera.

1. Dodaj następującą zależność biblioteki do pliku `platformio.ini`, aby dodać bibliotekę do ustawienia timera:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. Dodaj dyrektywę `include` dla tej biblioteki do pliku `main.cpp`:

    ```cpp
    #include <arduino-timer.h>
    ```

1. Nad funkcją `processAudio` dodaj następujący kod:

    ```cpp
    auto timer = timer_create_default();
    ```

    Ten kod deklaruje timer o nazwie `timer`.

1. Poniżej tego dodaj następujący kod:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    Ta funkcja `say` ostatecznie przekształci tekst na mowę, ale na razie będzie tylko zapisywać przekazany tekst do monitora szeregowego.

1. Poniżej funkcji `say` dodaj następujący kod:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    To jest funkcja zwrotna, która zostanie wywołana, gdy timer wygaśnie. Przekazywana jest wiadomość do wypowiedzenia, gdy timer wygaśnie. Timery mogą się powtarzać, a to może być kontrolowane przez wartość zwrotną tej funkcji zwrotnej - tutaj zwraca `false`, aby poinformować timer, że nie ma się uruchamiać ponownie.

1. Dodaj następujący kod na końcu funkcji `processAudio`:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    Ten kod sprawdza całkowitą liczbę sekund, a jeśli wynosi 0, zwraca się z wywołania funkcji, aby nie ustawiać timerów. Następnie konwertuje całkowitą liczbę sekund na minuty i sekundy.

1. Poniżej tego kodu dodaj następujący kod, aby utworzyć wiadomość do wypowiedzenia, gdy timer zostanie uruchomiony:

    ```cpp
    String begin_message;
    if (minutes > 0)
    {
        begin_message += minutes;
        begin_message += " minute ";
    }
    if (seconds > 0)
    {
        begin_message += seconds;
        begin_message += " second ";
    }

    begin_message += "timer started.";
    ```

1. Poniżej tego dodaj podobny kod, aby utworzyć wiadomość do wypowiedzenia, gdy timer wygaśnie:

    ```cpp
    String end_message("Times up on your ");
    if (minutes > 0)
    {
        end_message += minutes;
        end_message += " minute ";
    }
    if (seconds > 0)
    {
        end_message += seconds;
        end_message += " second ";
    }

    end_message += "timer.";
    ```

1. Po tym wypowiedz wiadomość o uruchomieniu timera:

    ```cpp
    say(begin_message);
    ```

1. Na końcu tej funkcji uruchom timer:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    To uruchamia timer. Timer jest ustawiany w milisekundach, więc całkowita liczba sekund jest mnożona przez 1,000, aby przekształcić ją na milisekundy. Funkcja `timerExpired` jest przekazywana jako funkcja zwrotna, a `end_message` jest przekazywana jako argument do funkcji zwrotnej. Ta funkcja zwrotna przyjmuje tylko argumenty typu `void *`, więc ciąg znaków jest odpowiednio konwertowany.

1. Na koniec timer musi *tykać*, a to jest robione w funkcji `loop`. Dodaj następujący kod na końcu funkcji `loop`:

    ```cpp
    timer.tick();
    ```

1. Zbuduj ten kod, wgraj go na swój Wio Terminal i przetestuj go przez monitor szeregowy. Gdy zobaczysz `Ready` w monitorze szeregowym, naciśnij przycisk C (ten po lewej stronie, najbliżej przełącznika zasilania) i mów. 4 sekundy dźwięku zostaną przechwycone, przekształcone na tekst, a następnie przesłane do Twojej aplikacji funkcji, a timer zostanie ustawiony. Upewnij się, że Twoja aplikacja funkcji działa lokalnie.

    Zobaczysz, kiedy timer się uruchomi i kiedy się zakończy.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Set a 2 minute and 27 second timer.","Offset":4700000,"Duration":35300000}
    Set a 2 minute and 27 second timer.
    {"seconds": 147}
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 Ten kod znajdziesz w folderze [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal).

😀 Twój program timera zakończył się sukcesem!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż staramy się zapewnić dokładność, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji krytycznych zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.