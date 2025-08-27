<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-27T20:58:31+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "no"
}
-->
# Sett en timer - Wio Terminal

I denne delen av leksjonen vil du kalle din serverløse kode for å tolke tale og sette en timer på din Wio Terminal basert på resultatene.

## Sett en timer

Teksten som kommer tilbake fra tale-til-tekst-kallet må sendes til din serverløse kode for å bli behandlet av LUIS, som returnerer antall sekunder for timeren. Dette antallet sekunder kan brukes til å sette en timer.

Mikrokontrollere har ikke innebygd støtte for flere tråder i Arduino, så det finnes ingen standard timerklasser som du kanskje finner når du programmerer i Python eller andre høyere nivå-språk. I stedet kan du bruke timerbiblioteker som fungerer ved å måle forløpt tid i `loop`-funksjonen og kalle funksjoner når tiden er ute.

### Oppgave - send teksten til den serverløse funksjonen

1. Åpne prosjektet `smart-timer` i VS Code hvis det ikke allerede er åpent.

1. Åpne header-filen `config.h` og legg til URL-en for din funksjonsapp:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    Erstatt `<URL>` med URL-en for din funksjonsapp som du fikk i siste steg av forrige leksjon, og som peker til IP-adressen til din lokale maskin som kjører funksjonsappen.

1. Opprett en ny fil i `src`-mappen kalt `language_understanding.h`. Denne vil bli brukt til å definere en klasse som sender den gjenkjente talen til din funksjonsapp for å bli konvertert til sekunder ved hjelp av LUIS.

1. Legg til følgende øverst i denne filen:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    Dette inkluderer noen nødvendige header-filer.

1. Definer en klasse kalt `LanguageUnderstanding`, og deklarer en instans av denne klassen:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. For å kalle funksjonsappen din, må du deklarere en WiFi-klient. Legg til følgende i den `private` delen av klassen:

    ```cpp
    WiFiClient _client;
    ```

1. I den `public` delen, deklarer en metode kalt `GetTimerDuration` for å kalle funksjonsappen:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. I metoden `GetTimerDuration`, legg til følgende kode for å bygge JSON som skal sendes til funksjonsappen:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Dette konverterer teksten som sendes til `GetTimerDuration`-metoden til følgende JSON:

    ```json
    {
        "text" : "<text>"
    }
    ```

    hvor `<text>` er teksten som sendes til funksjonen.

1. Under dette, legg til følgende kode for å gjøre kallet til funksjonsappen:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Dette gjør en POST-forespørsel til funksjonsappen, sender JSON-body og mottar svarkoden.

1. Legg til følgende kode under dette:

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

    Denne koden sjekker svarkoden. Hvis den er 200 (suksess), hentes antall sekunder for timeren fra svarbodyen. Ellers sendes en feil til seriemonitoren, og antall sekunder settes til 0.

1. Legg til følgende kode på slutten av denne metoden for å lukke HTTP-tilkoblingen og returnere antall sekunder:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. I `main.cpp`-filen, inkluder denne nye headeren:

    ```cpp
    #include "speech_to_text.h"
    ```

1. På slutten av `processAudio`-funksjonen, kall metoden `GetTimerDuration` for å få timerens varighet:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    Dette konverterer teksten fra kallet til `SpeechToText`-klassen til antall sekunder for timeren.

### Oppgave - sett en timer

Antall sekunder kan brukes til å sette en timer.

1. Legg til følgende biblioteksavhengighet i `platformio.ini`-filen for å legge til et bibliotek for å sette en timer:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. Legg til en include-direktiv for dette biblioteket i `main.cpp`-filen:

    ```cpp
    #include <arduino-timer.h>
    ```

1. Over `processAudio`-funksjonen, legg til følgende kode:

    ```cpp
    auto timer = timer_create_default();
    ```

    Denne koden deklarerer en timer kalt `timer`.

1. Under dette, legg til følgende kode:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    Denne `say`-funksjonen vil til slutt konvertere tekst til tale, men for nå vil den bare skrive den sendte teksten til seriemonitoren.

1. Under `say`-funksjonen, legg til følgende kode:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    Dette er en callback-funksjon som vil bli kalt når en timer utløper. Den får en melding som skal sies når timeren utløper. Timere kan gjentas, og dette kan kontrolleres av returverdien til denne callbacken - denne returnerer `false` for å indikere at timeren ikke skal kjøre igjen.

1. Legg til følgende kode på slutten av `processAudio`-funksjonen:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    Denne koden sjekker det totale antallet sekunder, og hvis det er 0, returnerer den fra funksjonskallet slik at ingen timere settes. Den konverterer deretter det totale antallet sekunder til minutter og sekunder.

1. Under denne koden, legg til følgende for å lage en melding som skal sies når timeren starter:

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

1. Under dette, legg til lignende kode for å lage en melding som skal sies når timeren har utløpt:

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

1. Etter dette, si meldingen om at timeren har startet:

    ```cpp
    say(begin_message);
    ```

1. På slutten av denne funksjonen, start timeren:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    Dette utløser timeren. Timeren settes ved hjelp av millisekunder, så det totale antallet sekunder multipliseres med 1 000 for å konvertere til millisekunder. `timerExpired`-funksjonen sendes som callback, og `end_message` sendes som et argument til callbacken. Denne callbacken tar kun `void *`-argumenter, så strengen konverteres tilsvarende.

1. Til slutt må timeren *tikke*, og dette gjøres i `loop`-funksjonen. Legg til følgende kode på slutten av `loop`-funksjonen:

    ```cpp
    timer.tick();
    ```

1. Bygg denne koden, last den opp til din Wio Terminal og test den gjennom seriemonitoren. Når du ser `Ready` i seriemonitoren, trykk på C-knappen (den på venstre side, nærmest strømbryteren), og snakk. 4 sekunder med lyd vil bli tatt opp, konvertert til tekst, sendt til funksjonsappen din, og en timer vil bli satt. Sørg for at funksjonsappen din kjører lokalt.

    Du vil se når timeren starter, og når den slutter.

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

> 💁 Du finner denne koden i [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal)-mappen.

😀 Timerprogrammet ditt var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.