<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-27T20:58:09+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "da"
}
-->
# Indstil en timer - Wio Terminal

I denne del af lektionen vil du kalde din serverløse kode for at forstå talen og indstille en timer på din Wio Terminal baseret på resultaterne.

## Indstil en timer

Teksten, der kommer tilbage fra tale-til-tekst-kaldet, skal sendes til din serverløse kode for at blive behandlet af LUIS, som returnerer antallet af sekunder for timeren. Dette antal sekunder kan bruges til at indstille en timer.

Mikrocontrollere har ikke indbygget understøttelse af flere tråde i Arduino, så der findes ingen standard timer-klasser, som du måske kender fra programmering i Python eller andre højere niveau-sprog. I stedet kan du bruge timer-biblioteker, der fungerer ved at måle forløbet tid i `loop`-funktionen og kalde funktioner, når tiden er udløbet.

### Opgave - send teksten til den serverløse funktion

1. Åbn `smart-timer`-projektet i VS Code, hvis det ikke allerede er åbent.

1. Åbn header-filen `config.h` og tilføj URL'en til din function app:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    Erstat `<URL>` med URL'en til din function app, som du fik i sidste trin af den sidste lektion, og som peger på IP-adressen for din lokale maskine, der kører function app'en.

1. Opret en ny fil i `src`-mappen kaldet `language_understanding.h`. Denne fil vil blive brugt til at definere en klasse, der sender den genkendte tale til din function app for at blive konverteret til sekunder ved hjælp af LUIS.

1. Tilføj følgende øverst i denne fil:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    Dette inkluderer nogle nødvendige header-filer.

1. Definer en klasse kaldet `LanguageUnderstanding`, og deklarér en instans af denne klasse:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. For at kalde din function app skal du deklarere en WiFi-klient. Tilføj følgende til den private sektion af klassen:

    ```cpp
    WiFiClient _client;
    ```

1. I den offentlige sektion skal du deklarere en metode kaldet `GetTimerDuration` for at kalde function app'en:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. I metoden `GetTimerDuration` skal du tilføje følgende kode for at opbygge JSON, der skal sendes til function app'en:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Dette konverterer teksten, der sendes til metoden `GetTimerDuration`, til følgende JSON:

    ```json
    {
        "text" : "<text>"
    }
    ```

    hvor `<text>` er teksten, der sendes til funktionen.

1. Tilføj følgende kode nedenfor for at lave kaldet til function app'en:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Dette laver en POST-anmodning til function app'en, sender JSON-indholdet og modtager svarkoden.

1. Tilføj følgende kode nedenfor dette:

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

    Denne kode kontrollerer svarkoden. Hvis den er 200 (succes), hentes antallet af sekunder for timeren fra svarindholdet. Ellers sendes en fejl til den serielle monitor, og antallet af sekunder sættes til 0.

1. Tilføj følgende kode til slutningen af denne metode for at lukke HTTP-forbindelsen og returnere antallet af sekunder:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. I filen `main.cpp` skal du inkludere denne nye header:

    ```cpp
    #include "speech_to_text.h"
    ```

1. I slutningen af funktionen `processAudio` skal du kalde metoden `GetTimerDuration` for at få timerens varighed:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    Dette konverterer teksten fra kaldet til klassen `SpeechToText` til antallet af sekunder for timeren.

### Opgave - indstil en timer

Antallet af sekunder kan bruges til at indstille en timer.

1. Tilføj følgende biblioteksafhængighed til filen `platformio.ini` for at tilføje et bibliotek til at indstille en timer:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. Tilføj en include-direktiv for dette bibliotek til filen `main.cpp`:

    ```cpp
    #include <arduino-timer.h>
    ```

1. Over funktionen `processAudio` skal du tilføje følgende kode:

    ```cpp
    auto timer = timer_create_default();
    ```

    Denne kode deklarerer en timer kaldet `timer`.

1. Nedenfor dette skal du tilføje følgende kode:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    Denne `say`-funktion vil til sidst konvertere tekst til tale, men for nu vil den blot skrive den modtagne tekst til den serielle monitor.

1. Nedenfor `say`-funktionen skal du tilføje følgende kode:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    Dette er en callback-funktion, der vil blive kaldt, når en timer udløber. Den modtager en besked, der skal siges, når timeren udløber. Timere kan gentages, og dette kan styres af returværdien af denne callback - denne returnerer `false` for at fortælle timeren, at den ikke skal køre igen.

1. Tilføj følgende kode til slutningen af funktionen `processAudio`:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    Denne kode kontrollerer det samlede antal sekunder, og hvis det er 0, returneres fra funktionskaldet, så ingen timere indstilles. Det konverterer derefter det samlede antal sekunder til minutter og sekunder.

1. Nedenfor denne kode skal du tilføje følgende for at oprette en besked, der skal siges, når timeren starter:

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

1. Nedenfor dette skal du tilføje lignende kode for at oprette en besked, der skal siges, når timeren er udløbet:

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

1. Efter dette skal du sige beskeden om, at timeren er startet:

    ```cpp
    say(begin_message);
    ```

1. I slutningen af denne funktion skal du starte timeren:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    Dette aktiverer timeren. Timeren indstilles ved hjælp af millisekunder, så det samlede antal sekunder ganges med 1.000 for at konvertere til millisekunder. Funktionen `timerExpired` sendes som callback, og `end_message` sendes som et argument til callbacken. Denne callback accepterer kun `void *`-argumenter, så strengen konverteres passende.

1. Endelig skal timeren "tikke", og dette gøres i funktionen `loop`. Tilføj følgende kode til slutningen af funktionen `loop`:

    ```cpp
    timer.tick();
    ```

1. Byg denne kode, upload den til din Wio Terminal, og test den via den serielle monitor. Når du ser `Ready` i den serielle monitor, skal du trykke på C-knappen (den til venstre, tættest på tænd/sluk-knappen) og tale. 4 sekunders lyd vil blive optaget, konverteret til tekst, sendt til din function app, og en timer vil blive indstillet. Sørg for, at din function app kører lokalt.

    Du vil se, hvornår timeren starter, og hvornår den slutter.

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

> 💁 Du kan finde denne kode i [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal)-mappen.

😀 Dit timer-program var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der opstår som følge af brugen af denne oversættelse.