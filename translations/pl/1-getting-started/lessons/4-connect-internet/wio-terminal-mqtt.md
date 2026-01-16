<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-26T07:00:57+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "pl"
}
-->
# Steruj swoją lampką nocną przez Internet - Wio Terminal

Urządzenie IoT musi zostać zaprogramowane, aby komunikować się z *test.mosquitto.org* za pomocą MQTT w celu wysyłania wartości telemetrycznych z odczytem czujnika światła oraz odbierania poleceń do sterowania diodą LED.

W tej części lekcji połączysz swój Wio Terminal z brokerem MQTT.

## Zainstaluj biblioteki WiFi i MQTT dla Arduino

Aby komunikować się z brokerem MQTT, musisz zainstalować kilka bibliotek Arduino, które umożliwią korzystanie z modułu WiFi w Wio Terminal oraz komunikację z MQTT. Podczas tworzenia aplikacji dla urządzeń Arduino możesz korzystać z szerokiej gamy bibliotek zawierających otwarty kod źródłowy, które implementują różnorodne funkcje. Seeed publikuje biblioteki dla Wio Terminal, które umożliwiają komunikację przez WiFi. Inni deweloperzy opublikowali biblioteki do komunikacji z brokerami MQTT, z których będziesz korzystać na swoim urządzeniu.

Te biblioteki są dostarczane jako kod źródłowy, który można automatycznie zaimportować do PlatformIO i skompilować dla Twojego urządzenia. Dzięki temu biblioteki Arduino będą działać na każdym urządzeniu obsługującym framework Arduino, pod warunkiem, że urządzenie posiada odpowiedni sprzęt wymagany przez daną bibliotekę. Niektóre biblioteki, takie jak biblioteki WiFi od Seeed, są specyficzne dla określonego sprzętu.

Biblioteki można instalować globalnie i kompilować w razie potrzeby lub w ramach konkretnego projektu. W tym zadaniu biblioteki zostaną zainstalowane w projekcie.

✅ Więcej informacji o zarządzaniu bibliotekami oraz o tym, jak je znaleźć i zainstalować, znajdziesz w [dokumentacji bibliotek PlatformIO](https://docs.platformio.org/en/latest/librarymanager/index.html).

### Zadanie - zainstaluj biblioteki WiFi i MQTT dla Arduino

Zainstaluj biblioteki Arduino.

1. Otwórz projekt lampki nocnej w VS Code.

1. Dodaj następujący kod na końcu pliku `platformio.ini`:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    To importuje biblioteki WiFi od Seeed. Składnia `@ <number>` odnosi się do konkretnej wersji biblioteki.

    > 💁 Możesz usunąć `@ <number>`, aby zawsze używać najnowszej wersji bibliotek, ale nie ma gwarancji, że nowsze wersje będą działać z poniższym kodem. Kod tutaj został przetestowany z tą wersją bibliotek.

    To wszystko, co musisz zrobić, aby dodać biblioteki. Przy następnym budowaniu projektu PlatformIO pobierze kod źródłowy tych bibliotek i skompiluje go w Twoim projekcie.

1. Dodaj następujący kod do `lib_deps`:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    To importuje [PubSubClient](https://github.com/knolleary/pubsubclient), klienta MQTT dla Arduino.

## Połącz się z WiFi

Teraz możesz połączyć Wio Terminal z WiFi.

### Zadanie - połącz się z WiFi

Połącz Wio Terminal z WiFi.

1. Utwórz nowy plik w folderze `src` o nazwie `config.h`. Możesz to zrobić, wybierając folder `src` lub plik `main.cpp` w środku, a następnie klikając przycisk **New file** w eksploratorze. Ten przycisk pojawia się tylko wtedy, gdy kursor znajduje się nad eksploratorem.

    ![Przycisk nowego pliku](../../../../../translated_images/pl/vscode-new-file-button.182702340fe6723c.png)

1. Dodaj następujący kod do tego pliku, aby zdefiniować stałe dla danych logowania do WiFi:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    Zamień `<SSID>` na SSID swojej sieci WiFi. Zamień `<PASSWORD>` na hasło do swojej sieci WiFi.

1. Otwórz plik `main.cpp`.

1. Dodaj następujące dyrektywy `#include` na początku pliku:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    To dodaje pliki nagłówkowe dla wcześniej dodanych bibliotek oraz plik nagłówkowy konfiguracji. Te pliki nagłówkowe są potrzebne, aby PlatformIO mogło zaimportować kod z bibliotek. Bez ich wyraźnego uwzględnienia niektóre fragmenty kodu nie zostaną skompilowane, co spowoduje błędy kompilatora.

1. Dodaj następujący kod powyżej funkcji `setup`:

    ```cpp
    void connectWiFi()
    {
        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("Connecting to WiFi..");
            WiFi.begin(SSID, PASSWORD);
            delay(500);
        }
    
        Serial.println("Connected!");
    }
    ```

    Ten kod działa w pętli, dopóki urządzenie nie połączy się z WiFi, i próbuje połączyć się, używając SSID i hasła z pliku nagłówkowego konfiguracji.

1. Dodaj wywołanie tej funkcji na końcu funkcji `setup`, po skonfigurowaniu pinów.

    ```cpp
    connectWiFi();
    ```

1. Wgraj ten kod na swoje urządzenie, aby sprawdzić, czy połączenie WiFi działa. Powinieneś zobaczyć to w monitorze szeregowym.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## Połącz się z MQTT

Gdy Wio Terminal jest połączony z WiFi, może połączyć się z brokerem MQTT.

### Zadanie - połącz się z MQTT

Połącz się z brokerem MQTT.

1. Dodaj następujący kod na końcu pliku `config.h`, aby zdefiniować szczegóły połączenia z brokerem MQTT:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    Zamień `<ID>` na unikalny identyfikator, który będzie używany jako nazwa tego klienta urządzenia, a później jako nazwa tematów, które to urządzenie publikuje i subskrybuje. Broker *test.mosquitto.org* jest publiczny i używany przez wiele osób, w tym innych studentów realizujących to zadanie. Posiadanie unikalnej nazwy klienta MQTT i tematów zapewnia, że Twój kod nie będzie kolidował z kodem innych osób. Będziesz również potrzebować tego identyfikatora podczas tworzenia kodu serwera w dalszej części zadania.

    > 💁 Możesz użyć strony internetowej, takiej jak [GUIDGen](https://www.guidgen.com), aby wygenerować unikalny identyfikator.

    `BROKER` to URL brokera MQTT.

    `CLIENT_NAME` to unikalna nazwa tego klienta MQTT na brokerze.

1. Otwórz plik `main.cpp` i dodaj następujący kod poniżej funkcji `connectWiFi` i powyżej funkcji `setup`:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    Ten kod tworzy klienta WiFi, korzystając z bibliotek WiFi Wio Terminal, i używa go do utworzenia klienta MQTT.

1. Poniżej tego kodu dodaj następujący fragment:

    ```cpp
    void reconnectMQTTClient()
    {
        while (!client.connected())
        {
            Serial.print("Attempting MQTT connection...");
    
            if (client.connect(CLIENT_NAME.c_str()))
            {
                Serial.println("connected");
            }
            else
            {
                Serial.print("Retying in 5 seconds - failed, rc=");
                Serial.println(client.state());
                
                delay(5000);
            }
        }
    }
    ```

    Ta funkcja testuje połączenie z brokerem MQTT i ponownie łączy się, jeśli połączenie zostało zerwane. Działa w pętli, dopóki nie zostanie nawiązane połączenie, i próbuje połączyć się, używając unikalnej nazwy klienta zdefiniowanej w pliku nagłówkowym konfiguracji.

    Jeśli połączenie się nie powiedzie, próbuje ponownie po 5 sekundach.

1. Dodaj następujący kod poniżej funkcji `reconnectMQTTClient`:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    Ten kod ustawia brokera MQTT dla klienta oraz konfiguruje wywołanie zwrotne, gdy wiadomość zostanie odebrana. Następnie próbuje połączyć się z brokerem.

1. Wywołaj funkcję `createMQTTClient` w funkcji `setup` po nawiązaniu połączenia z WiFi.

1. Zastąp całą funkcję `loop` następującym kodem:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    Ten kod zaczyna od ponownego połączenia z brokerem MQTT. Połączenia te mogą być łatwo zrywane, więc warto regularnie sprawdzać i ponownie łączyć się w razie potrzeby. Następnie wywołuje metodę `loop` na kliencie MQTT, aby przetworzyć wszelkie wiadomości przychodzące na subskrybowany temat. Ta aplikacja jest jednowątkowa, więc wiadomości nie mogą być odbierane w tle, dlatego należy przeznaczyć czas w głównym wątku na przetwarzanie wiadomości oczekujących na połączeniu sieciowym.

    Na koniec opóźnienie 2 sekund zapewnia, że poziomy światła nie są wysyłane zbyt często, co zmniejsza zużycie energii przez urządzenie.

1. Wgraj kod na swój Wio Terminal i użyj monitora szeregowego, aby zobaczyć, jak urządzenie łączy się z WiFi i MQTT.

    ```output
    > Executing task: platformio device monitor <
    
    source /Users/jimbennett/GitHub/IoT-For-Beginners/1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal/nightlight/.venv/bin/activate
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    ```

> 💁 Ten kod znajdziesz w folderze [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal).

😀 Udało Ci się pomyślnie połączyć swoje urządzenie z brokerem MQTT.

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.