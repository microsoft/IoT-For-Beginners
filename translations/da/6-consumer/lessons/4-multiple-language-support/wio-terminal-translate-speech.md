# Oversæt tale - Wio Terminal

I denne del af lektionen vil du skrive kode til at oversætte tekst ved hjælp af oversættelsestjenesten.

## Konverter tekst til tale ved hjælp af oversættelsestjenesten

REST API'en for taletjenesten understøtter ikke direkte oversættelser. I stedet kan du bruge oversættelsestjenesten til at oversætte teksten, der genereres af tale-til-tekst-tjenesten, samt teksten til det talte svar. Denne tjeneste har et REST API, som du kan bruge til at oversætte teksten, men for at gøre det nemmere at bruge, vil dette blive pakket ind i en anden HTTP-trigger i din funktion-app.

### Opgave - opret en serverløs funktion til at oversætte tekst

1. Åbn dit `smart-timer-trigger`-projekt i VS Code, og åbn terminalen, og sørg for, at det virtuelle miljø er aktiveret. Hvis ikke, luk og genskab terminalen.

1. Åbn filen `local.settings.json` og tilføj indstillinger for oversættelsestjenestens API-nøgle og placering:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    Erstat `<key>` med API-nøglen til din oversættelsestjeneste. Erstat `<location>` med den placering, du brugte, da du oprettede oversættelsestjenesten.

1. Tilføj en ny HTTP-trigger til denne app kaldet `translate-text` ved hjælp af følgende kommando fra terminalen i rodmappen af funktion-app-projektet:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    Dette vil oprette en HTTP-trigger kaldet `translate-text`.

1. Erstat indholdet af filen `__init__.py` i mappen `translate-text` med følgende:

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

    Denne kode udtrækker teksten og sprogene fra HTTP-anmodningen. Den sender derefter en anmodning til oversættelsestjenestens REST API, hvor sprogene sendes som parametre i URL'en, og teksten, der skal oversættes, sendes som body. Til sidst returneres oversættelsen.

1. Kør din funktion-app lokalt. Du kan derefter kalde denne ved hjælp af et værktøj som curl på samme måde, som du testede din `text-to-timer` HTTP-trigger. Sørg for at sende teksten, der skal oversættes, og sprogene som en JSON-body:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    Dette eksempel oversætter *Définir une minuterie de 30 secondes* fra fransk til amerikansk engelsk. Det vil returnere *Set a 30-second timer*.

> 💁 Du kan finde denne kode i mappen [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions).

### Opgave - brug oversættelsesfunktionen til at oversætte tekst

1. Åbn projektet `smart-timer` i VS Code, hvis det ikke allerede er åbent.

1. Din smarte timer vil have 2 sprog indstillet - sproget på serveren, der blev brugt til at træne LUIS (det samme sprog bruges også til at opbygge beskederne, der skal tales til brugeren), og sproget, der tales af brugeren. Opdater konstanten `LANGUAGE` i header-filen `config.h` til at være det sprog, der vil blive talt af brugeren, og tilføj en ny konstant kaldet `SERVER_LANGUAGE` for sproget, der blev brugt til at træne LUIS:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    Erstat `<user language>` med lokalnavnet for det sprog, du vil tale, for eksempel `fr-FR` for fransk eller `zn-HK` for kantonesisk.

    Erstat `<server language>` med lokalnavnet for det sprog, der blev brugt til at træne LUIS.

    Du kan finde en liste over de understøttede sprog og deres lokalnavne i [Language and voice support documentation on Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Hvis du ikke taler flere sprog, kan du bruge en tjeneste som [Bing Translate](https://www.bing.com/translator) eller [Google Translate](https://translate.google.com) til at oversætte fra dit foretrukne sprog til et sprog efter eget valg. Disse tjenester kan derefter afspille lyd af den oversatte tekst.
    >
    > For eksempel, hvis du træner LUIS på engelsk, men ønsker at bruge fransk som brugersprog, kan du oversætte sætninger som "set a 2 minute and 27 second timer" fra engelsk til fransk ved hjælp af Bing Translate, og derefter bruge knappen **Lyt til oversættelse** til at tale oversættelsen ind i din mikrofon.
    >
    > ![Knappen Lyt til oversættelse på Bing Translate](../../../../../translated_images/da/bing-translate.348aa796d6efe2a9.webp)

1. Tilføj oversættelsestjenestens API-nøgle og placering under `SPEECH_LOCATION`:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    Erstat `<KEY>` med API-nøglen til din oversættelsestjeneste. Erstat `<LOCATION>` med den placering, du brugte, da du oprettede oversættelsestjenesten.

1. Tilføj URL'en til oversættelsestriggeren under `VOICE_URL`:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    Erstat `<URL>` med URL'en til HTTP-triggeren `translate-text` i din funktion-app. Dette vil være det samme som værdien for `TEXT_TO_TIMER_FUNCTION_URL`, bortset fra at funktionsnavnet er `translate-text` i stedet for `text-to-timer`.

1. Tilføj en ny fil til mappen `src` kaldet `text_translator.h`.

1. Denne nye header-fil `text_translator.h` vil indeholde en klasse til at oversætte tekst. Tilføj følgende til denne fil for at erklære klassen:

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

    Dette erklærer klassen `TextTranslator` sammen med en instans af denne klasse. Klassen har et enkelt felt til WiFi-klienten.

1. Til den offentlige sektion af denne klasse, tilføj en metode til at oversætte tekst:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    Denne metode tager sproget, der skal oversættes fra, og sproget, der skal oversættes til. Når tale behandles, vil talen blive oversat fra brugersproget til LUIS-serverens sprog, og når der gives svar, vil det blive oversat fra LUIS-serverens sprog til brugersproget.

1. I denne metode, tilføj kode til at konstruere en JSON-body, der indeholder teksten, der skal oversættes, og sprogene:

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

1. Under dette, tilføj følgende kode for at sende body til den serverløse funktion-app:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Tilføj derefter kode til at hente svaret:

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

1. Til sidst, tilføj kode til at lukke forbindelsen og returnere den oversatte tekst:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### Opgave - oversæt den genkendte tale og svarene

1. Åbn filen `main.cpp`.

1. Tilføj en include-direktiv øverst i filen for header-filen til klassen `TextTranslator`:

    ```cpp
    #include "text_translator.h"
    ```

1. Teksten, der siges, når en timer indstilles eller udløber, skal oversættes. For at gøre dette, tilføj følgende som den første linje i funktionen `say`:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Dette vil oversætte teksten til brugersproget.

1. I funktionen `processAudio` hentes tekst fra den optagede lyd med kaldet `String text = speechToText.convertSpeechToText();`. Efter dette kald, oversæt teksten:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Dette vil oversætte teksten fra brugersproget til det sprog, der bruges på serveren.

1. Byg denne kode, upload den til din Wio Terminal, og test den via den serielle monitor. Når du ser `Ready` i den serielle monitor, tryk på C-knappen (den til venstre, tættest på tænd/sluk-knappen), og tal. Sørg for, at din funktion-app kører, og anmod om en timer på brugersproget, enten ved at tale det sprog selv eller ved at bruge en oversættelsesapp.

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

> 💁 Du kan finde denne kode i mappen [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal).

😀 Dit flersprogede timerprogram var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der opstår som følge af brugen af denne oversættelse.