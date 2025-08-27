<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-27T20:57:45+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "sv"
}
-->
# Ställ in en timer - Wio Terminal

I den här delen av lektionen kommer du att anropa din serverlösa kod för att förstå talet och ställa in en timer på din Wio Terminal baserat på resultaten.

## Ställ in en timer

Texten som kommer tillbaka från tal-till-text-anropet behöver skickas till din serverlösa kod för att bearbetas av LUIS, vilket ger tillbaka antalet sekunder för timern. Detta antal sekunder kan användas för att ställa in en timer.

Mikrokontroller har inte inbyggt stöd för flera trådar i Arduino, så det finns inga standardklasser för timers som du kanske hittar när du kodar i Python eller andra högre nivåspråk. Istället kan du använda timerbibliotek som fungerar genom att mäta förfluten tid i funktionen `loop` och anropa funktioner när tiden är ute.

### Uppgift - skicka texten till den serverlösa funktionen

1. Öppna projektet `smart-timer` i VS Code om det inte redan är öppet.

1. Öppna headerfilen `config.h` och lägg till URL:en för din funktionsapp:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    Ersätt `<URL>` med URL:en för din funktionsapp som du fick i sista steget av den föregående lektionen, pekande på IP-adressen för din lokala maskin som kör funktionsappen.

1. Skapa en ny fil i mappen `src` som heter `language_understanding.h`. Denna kommer att användas för att definiera en klass som skickar det igenkända talet till din funktionsapp för att konverteras till sekunder med hjälp av LUIS.

1. Lägg till följande högst upp i filen:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    Detta inkluderar några nödvändiga headerfiler.

1. Definiera en klass som heter `LanguageUnderstanding` och deklarera en instans av denna klass:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. För att anropa din funktionsapp behöver du deklarera en WiFi-klient. Lägg till följande i den privata sektionen av klassen:

    ```cpp
    WiFiClient _client;
    ```

1. I den publika sektionen, deklarera en metod som heter `GetTimerDuration` för att anropa funktionsappen:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. I metoden `GetTimerDuration`, lägg till följande kod för att bygga JSON som ska skickas till funktionsappen:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Detta konverterar texten som skickas till metoden `GetTimerDuration` till följande JSON:

    ```json
    {
        "text" : "<text>"
    }
    ```

    där `<text>` är texten som skickas till funktionen.

1. Nedanför detta, lägg till följande kod för att göra anropet till funktionsappen:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Detta gör en POST-förfrågan till funktionsappen, skickar JSON-innehållet och får tillbaka svarskoden.

1. Lägg till följande kod nedanför detta:

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

    Denna kod kontrollerar svarskoden. Om den är 200 (framgång) hämtas antalet sekunder för timern från svarsinnehållet. Annars skickas ett felmeddelande till seriell monitor och antalet sekunder sätts till 0.

1. Lägg till följande kod i slutet av denna metod för att stänga HTTP-anslutningen och returnera antalet sekunder:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. I filen `main.cpp`, inkludera denna nya header:

    ```cpp
    #include "speech_to_text.h"
    ```

1. I slutet av funktionen `processAudio`, anropa metoden `GetTimerDuration` för att få timerns varaktighet:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    Detta konverterar texten från anropet till klassen `SpeechToText` till antalet sekunder för timern.

### Uppgift - ställ in en timer

Antalet sekunder kan användas för att ställa in en timer.

1. Lägg till följande biblioteksberoende i filen `platformio.ini` för att lägga till ett bibliotek för att ställa in en timer:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. Lägg till en inkluderingsdirektiv för detta bibliotek i filen `main.cpp`:

    ```cpp
    #include <arduino-timer.h>
    ```

1. Ovanför funktionen `processAudio`, lägg till följande kod:

    ```cpp
    auto timer = timer_create_default();
    ```

    Denna kod deklarerar en timer som heter `timer`.

1. Nedanför detta, lägg till följande kod:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    Denna `say`-funktion kommer så småningom att konvertera text till tal, men för tillfället kommer den bara att skriva den skickade texten till seriell monitor.

1. Nedanför funktionen `say`, lägg till följande kod:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    Detta är en callback-funktion som kommer att anropas när en timer går ut. Den får ett meddelande att säga när timern går ut. Timers kan upprepas, och detta kan styras av returvärdet från denna callback - detta returnerar `false` för att indikera att timern inte ska köras igen.

1. Lägg till följande kod i slutet av funktionen `processAudio`:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    Denna kod kontrollerar det totala antalet sekunder, och om det är 0, returnerar från funktionsanropet så att inga timers ställs in. Den konverterar sedan det totala antalet sekunder till minuter och sekunder.

1. Nedanför denna kod, lägg till följande för att skapa ett meddelande att säga när timern startas:

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

1. Nedanför detta, lägg till liknande kod för att skapa ett meddelande att säga när timern har gått ut:

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

1. Efter detta, säg meddelandet om att timern har startat:

    ```cpp
    say(begin_message);
    ```

1. I slutet av denna funktion, starta timern:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    Detta triggar timern. Timern ställs in med millisekunder, så det totala antalet sekunder multipliceras med 1 000 för att konvertera till millisekunder. Funktionen `timerExpired` skickas som callback, och `end_message` skickas som ett argument till callbacken. Denna callback tar endast `void *`-argument, så strängen konverteras på lämpligt sätt.

1. Slutligen behöver timern *ticka*, och detta görs i funktionen `loop`. Lägg till följande kod i slutet av funktionen `loop`:

    ```cpp
    timer.tick();
    ```

1. Bygg denna kod, ladda upp den till din Wio Terminal och testa den via seriell monitor. När du ser `Ready` i seriell monitor, tryck på C-knappen (den till vänster, närmast strömbrytaren) och prata. 4 sekunder av ljud kommer att fångas, konverteras till text, skickas till din funktionsapp och en timer kommer att ställas in. Se till att din funktionsapp körs lokalt.

    Du kommer att se när timern startar och när den slutar.

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

> 💁 Du kan hitta denna kod i mappen [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal).

😀 Ditt timerprogram blev en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiserade översättningar kan innehålla fel eller brister. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.