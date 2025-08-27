<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-27T22:26:50+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "nl"
}
-->
# Stel een timer in - Wio Terminal

In dit deel van de les roep je je serverloze code aan om de spraak te begrijpen en stel je een timer in op je Wio Terminal op basis van de resultaten.

## Stel een timer in

De tekst die terugkomt van de spraak-naar-tekst-aanroep moet naar je serverloze code worden gestuurd om door LUIS te worden verwerkt, waarbij het aantal seconden voor de timer wordt teruggegeven. Dit aantal seconden kan worden gebruikt om een timer in te stellen.

Microcontrollers hebben standaard geen ondersteuning voor meerdere threads in Arduino, dus er zijn geen standaard timerklassen zoals je die zou vinden bij het programmeren in Python of andere hogere programmeertalen. In plaats daarvan kun je timerbibliotheken gebruiken die werken door de verstreken tijd in de `loop`-functie te meten en functies aan te roepen wanneer de tijd is verstreken.

### Taak - stuur de tekst naar de serverloze functie

1. Open het `smart-timer`-project in VS Code als het nog niet geopend is.

1. Open het `config.h`-headerbestand en voeg de URL toe voor je function app:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    Vervang `<URL>` door de URL voor je function app die je hebt verkregen in de laatste stap van de vorige les, wijzend naar het IP-adres van je lokale machine waarop de function app draait.

1. Maak een nieuw bestand in de `src`-map genaamd `language_understanding.h`. Dit wordt gebruikt om een klasse te definiëren die de herkende spraak naar je function app stuurt om te worden omgezet in seconden met behulp van LUIS.

1. Voeg het volgende toe aan de bovenkant van dit bestand:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    Dit bevat enkele benodigde headerbestanden.

1. Definieer een klasse genaamd `LanguageUnderstanding` en declareer een instantie van deze klasse:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. Om je function app aan te roepen, moet je een WiFi-client declareren. Voeg het volgende toe aan het `private`-gedeelte van de klasse:

    ```cpp
    WiFiClient _client;
    ```

1. Declareer in het `public`-gedeelte een methode genaamd `GetTimerDuration` om de function app aan te roepen:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. Voeg in de `GetTimerDuration`-methode de volgende code toe om de JSON op te bouwen die naar de function app wordt gestuurd:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Dit zet de tekst die wordt doorgegeven aan de `GetTimerDuration`-methode om in de volgende JSON:

    ```json
    {
        "text" : "<text>"
    }
    ```

    waarbij `<text>` de tekst is die aan de functie wordt doorgegeven.

1. Voeg hieronder de volgende code toe om de function app aan te roepen:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Dit maakt een POST-verzoek naar de function app, waarbij de JSON-body wordt doorgegeven en de response code wordt verkregen.

1. Voeg de volgende code hieronder toe:

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

    Deze code controleert de response code. Als deze 200 (succes) is, wordt het aantal seconden voor de timer opgehaald uit de response body. Anders wordt een fout naar de seriële monitor gestuurd en wordt het aantal seconden ingesteld op 0.

1. Voeg de volgende code toe aan het einde van deze methode om de HTTP-verbinding te sluiten en het aantal seconden terug te geven:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. Voeg in het `main.cpp`-bestand deze nieuwe header toe:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Roep aan het einde van de `processAudio`-functie de `GetTimerDuration`-methode aan om de timerduur te verkrijgen:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    Dit zet de tekst van de aanroep naar de `SpeechToText`-klasse om in het aantal seconden voor de timer.

### Taak - stel een timer in

Het aantal seconden kan worden gebruikt om een timer in te stellen.

1. Voeg de volgende bibliotheekafhankelijkheid toe aan het `platformio.ini`-bestand om een bibliotheek toe te voegen voor het instellen van een timer:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. Voeg een include-directive voor deze bibliotheek toe aan het `main.cpp`-bestand:

    ```cpp
    #include <arduino-timer.h>
    ```

1. Voeg boven de `processAudio`-functie de volgende code toe:

    ```cpp
    auto timer = timer_create_default();
    ```

    Deze code declareert een timer genaamd `timer`.

1. Voeg hieronder de volgende code toe:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    Deze `say`-functie zal uiteindelijk tekst omzetten in spraak, maar voor nu zal het alleen de doorgegeven tekst naar de seriële monitor schrijven.

1. Voeg onder de `say`-functie de volgende code toe:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    Dit is een callbackfunctie die wordt aangeroepen wanneer een timer afloopt. Er wordt een bericht doorgegeven dat moet worden uitgesproken wanneer de timer afloopt. Timers kunnen herhalen, en dit kan worden gecontroleerd door de returnwaarde van deze callback - deze retourneert `false`, om aan te geven dat de timer niet opnieuw moet worden uitgevoerd.

1. Voeg de volgende code toe aan het einde van de `processAudio`-functie:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    Deze code controleert het totale aantal seconden, en als dit 0 is, wordt de functieaanroep beëindigd zodat er geen timers worden ingesteld. Vervolgens wordt het totale aantal seconden omgezet in minuten en seconden.

1. Voeg hieronder de volgende code toe om een bericht te maken dat wordt uitgesproken wanneer de timer wordt gestart:

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

1. Voeg hieronder soortgelijke code toe om een bericht te maken dat wordt uitgesproken wanneer de timer is verlopen:

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

1. Spreek na deze code het bericht uit dat de timer is gestart:

    ```cpp
    say(begin_message);
    ```

1. Start aan het einde van deze functie de timer:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    Dit activeert de timer. De timer wordt ingesteld met milliseconden, dus het totale aantal seconden wordt vermenigvuldigd met 1.000 om om te zetten naar milliseconden. De `timerExpired`-functie wordt doorgegeven als de callback, en de `end_message` wordt doorgegeven als een argument dat aan de callback wordt doorgegeven. Deze callback accepteert alleen `void *`-argumenten, dus de string wordt op de juiste manier omgezet.

1. Tot slot moet de timer *tikken*, en dit gebeurt in de `loop`-functie. Voeg de volgende code toe aan het einde van de `loop`-functie:

    ```cpp
    timer.tick();
    ```

1. Bouw deze code, upload deze naar je Wio Terminal en test het via de seriële monitor. Zodra je `Ready` ziet in de seriële monitor, druk je op de C-knop (de knop aan de linkerkant, het dichtst bij de aan/uit-schakelaar) en spreek je. 4 seconden audio worden vastgelegd, omgezet in tekst, vervolgens naar je function app gestuurd, en een timer wordt ingesteld. Zorg ervoor dat je function app lokaal draait.

    Je ziet wanneer de timer start en wanneer deze eindigt.

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

> 💁 Je kunt deze code vinden in de [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal) map.

😀 Je timerprogramma was een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we ons best doen om nauwkeurigheid te garanderen, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.