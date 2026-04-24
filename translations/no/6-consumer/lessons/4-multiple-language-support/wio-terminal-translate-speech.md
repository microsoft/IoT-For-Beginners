# Oversett tale - Wio Terminal

I denne delen av leksjonen skal du skrive kode for å oversette tekst ved hjelp av oversettertjenesten.

## Konverter tekst til tale ved hjelp av oversettertjenesten

REST API-et for taletjenesten støtter ikke direkte oversettelser. I stedet kan du bruke oversettertjenesten til å oversette teksten som genereres av tale-til-tekst-tjenesten, samt teksten til det talte svaret. Denne tjenesten har et REST API som kan brukes til å oversette tekst, men for å gjøre det enklere vil dette bli pakket inn i en annen HTTP-trigger i funksjonsappen din.

### Oppgave - opprett en serverløs funksjon for å oversette tekst

1. Åpne prosjektet ditt `smart-timer-trigger` i VS Code, og åpne terminalen mens du sørger for at det virtuelle miljøet er aktivert. Hvis ikke, avslutt og opprett terminalen på nytt.

1. Åpne filen `local.settings.json` og legg til innstillinger for API-nøkkelen og plasseringen til oversettertjenesten:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    Erstatt `<key>` med API-nøkkelen for ressursen til oversettertjenesten din. Erstatt `<location>` med plasseringen du brukte da du opprettet ressursen til oversettertjenesten.

1. Legg til en ny HTTP-trigger i denne appen kalt `translate-text` ved å bruke følgende kommando fra terminalen i rotmappen til funksjonsapp-prosjektet:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    Dette vil opprette en HTTP-trigger kalt `translate-text`.

1. Erstatt innholdet i filen `__init__.py` i mappen `translate-text` med følgende:

    ```python
    import logging
    import os
    import requests
    
    import azure.functions as func
    
    location = os.environ['TRANSLATOR_LOCATION']
    translator_key = os.environ['TRANSLATOR_KEY']
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        from_language = req_body['from_language']
        to_language = req_body['to_language']
        text = req_body['text']
        
        logging.info(f'Translating {text} from {from_language} to {to_language}')
    
        url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'
    
        headers = {
            'Ocp-Apim-Subscription-Key': translator_key,
            'Ocp-Apim-Subscription-Region': location,
            'Content-type': 'application/json'
        }
    
        params = {
            'from': from_language,
            'to': to_language
        }
    
        body = [{
            'text' : text
        }]
        
        response = requests.post(url, headers=headers, params=params, json=body)
        return func.HttpResponse(response.json()[0]['translations'][0]['text'])
    ```

    Denne koden henter ut teksten og språkene fra HTTP-forespørselen. Deretter sender den en forespørsel til oversetterens REST API, hvor språkene sendes som parametere for URL-en og teksten som skal oversettes sendes som innhold. Til slutt returneres oversettelsen.

1. Kjør funksjonsappen din lokalt. Du kan deretter teste den ved å bruke et verktøy som curl, på samme måte som du testet HTTP-triggeren `text-to-timer`. Sørg for å sende teksten som skal oversettes og språkene som en JSON-body:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    Dette eksemplet oversetter *Définir une minuterie de 30 secondes* fra fransk til amerikansk engelsk. Det vil returnere *Set a 30-second timer*.

> 💁 Du finner denne koden i [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions)-mappen.

### Oppgave - bruk oversetterfunksjonen til å oversette tekst

1. Åpne prosjektet `smart-timer` i VS Code hvis det ikke allerede er åpent.

1. Din smarte timer vil ha 2 språk satt - språket til serveren som ble brukt til å trene LUIS (det samme språket brukes også til å bygge meldingene som skal snakkes til brukeren), og språket som brukes av brukeren. Oppdater konstanten `LANGUAGE` i header-filen `config.h` til å være språket som skal snakkes av brukeren, og legg til en ny konstant kalt `SERVER_LANGUAGE` for språket som ble brukt til å trene LUIS:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    Erstatt `<user language>` med lokalitetsnavnet for språket du skal snakke, for eksempel `fr-FR` for fransk, eller `zn-HK` for kantonesisk.

    Erstatt `<server language>` med lokalitetsnavnet for språket som ble brukt til å trene LUIS.

    Du finner en liste over støttede språk og deres lokalitetsnavn i [Language and voice support documentation on Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Hvis du ikke snakker flere språk, kan du bruke en tjeneste som [Bing Translate](https://www.bing.com/translator) eller [Google Translate](https://translate.google.com) for å oversette fra ditt foretrukne språk til et annet språk. Disse tjenestene kan også spille av lyd av den oversatte teksten.
    >
    > For eksempel, hvis du trener LUIS på engelsk, men ønsker å bruke fransk som brukerspråk, kan du oversette setninger som "set a 2 minute and 27 second timer" fra engelsk til fransk ved hjelp av Bing Translate, og deretter bruke **Listen translation**-knappen for å snakke oversettelsen inn i mikrofonen din.
    >
    > ![Knappen for å lytte til oversettelse på Bing Translate](../../../../../translated_images/no/bing-translate.348aa796d6efe2a9.webp)

1. Legg til API-nøkkelen og plasseringen til oversettertjenesten under `SPEECH_LOCATION`:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    Erstatt `<KEY>` med API-nøkkelen for ressursen til oversettertjenesten din. Erstatt `<LOCATION>` med plasseringen du brukte da du opprettet ressursen til oversettertjenesten.

1. Legg til URL-en til oversettertriggeren under `VOICE_URL`:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    Erstatt `<URL>` med URL-en for HTTP-triggeren `translate-text` i funksjonsappen din. Dette vil være det samme som verdien for `TEXT_TO_TIMER_FUNCTION_URL`, bortsett fra at funksjonsnavnet er `translate-text` i stedet for `text-to-timer`.

1. Legg til en ny fil i `src`-mappen kalt `text_translator.h`.

1. Denne nye header-filen `text_translator.h` vil inneholde en klasse for å oversette tekst. Legg til følgende i denne filen for å erklære klassen:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    
    class TextTranslator
    {
    public:   
    private:
        WiFiClient _client;
    };
    
    TextTranslator textTranslator;
    ```

    Dette erklærer klassen `TextTranslator`, sammen med en instans av denne klassen. Klassen har et enkelt felt for WiFi-klienten.

1. I den `public`-seksjonen av denne klassen, legg til en metode for å oversette tekst:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    Denne metoden tar språket som skal oversettes fra, og språket som skal oversettes til. Når tale behandles, vil talen bli oversatt fra brukerspråket til LUIS-serverens språk, og når svar gis, vil det bli oversatt fra LUIS-serverens språk til brukerspråket.

1. I denne metoden, legg til kode for å konstruere en JSON-body som inneholder teksten som skal oversettes og språkene:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;
    doc["from_language"] = from_language;
    doc["to_language"] = to_language;

    String body;
    serializeJson(doc, body);

    Serial.print("Translating ");
    Serial.print(text);
    Serial.print(" from ");
    Serial.print(from_language);
    Serial.print(" to ");
    Serial.print(to_language);
    ```

1. Under dette, legg til følgende kode for å sende innholdet til den serverløse funksjonsappen:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Deretter, legg til kode for å hente responsen:

    ```cpp
    String translated_text = "";

    if (httpResponseCode == 200)
    {
        translated_text = httpClient.getString();
        Serial.print("Translated: ");
        Serial.println(translated_text);
    }
    else
    {
        Serial.print("Failed to translate text - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. Til slutt, legg til kode for å lukke tilkoblingen og returnere den oversatte teksten:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### Oppgave - oversett den gjenkjente talen og svarene

1. Åpne filen `main.cpp`.

1. Legg til en include-direktiv øverst i filen for header-filen til klassen `TextTranslator`:

    ```cpp
    #include "text_translator.h"
    ```

1. Teksten som sies når en timer settes eller utløper må oversettes. For å gjøre dette, legg til følgende som første linje i funksjonen `say`:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Dette vil oversette teksten til brukerspråket.

1. I funksjonen `processAudio` hentes tekst fra den fangede lyden med kallet `String text = speechToText.convertSpeechToText();`. Etter dette kallet, oversett teksten:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Dette vil oversette teksten fra brukerspråket til språket som brukes på serveren.

1. Bygg denne koden, last den opp til din Wio Terminal og test den gjennom seriell monitor. Når du ser `Ready` i seriell monitor, trykk på C-knappen (den til venstre, nærmest strømbryteren), og snakk. Sørg for at funksjonsappen din kjører, og be om en timer på brukerspråket, enten ved å snakke det språket selv, eller ved å bruke en oversettelsesapp.

    ```output
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Définir une minuterie de 2 minutes 27 secondes.","Offset":9600000,"Duration":40400000}
    Translating Définir une minuterie de 2 minutes 27 secondes. from fr-FR to en-US
    Translated: Set a timer of 2 minutes 27 seconds.
    Set a timer of 2 minutes 27 seconds.
    {"seconds": 147}
    Translating 2 minute 27 second timer started. from en-US to fr-FR
    Translated: 2 minute 27 seconde minute a commencé.
    2 minute 27 seconde minute a commencé.
    Translating Times up on your 2 minute 27 second timer. from en-US to fr-FR
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

> 💁 Du finner denne koden i [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal)-mappen.

😀 Programmet ditt for flerspråklige timere var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for eventuelle misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.