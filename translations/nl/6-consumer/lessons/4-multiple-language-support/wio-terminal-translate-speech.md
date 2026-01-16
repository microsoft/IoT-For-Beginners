<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f6c164e349f8989959e02a90f37908d",
  "translation_date": "2025-08-27T22:13:16+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/wio-terminal-translate-speech.md",
  "language_code": "nl"
}
-->
# Vertaal spraak - Wio Terminal

In dit deel van de les schrijf je code om tekst te vertalen met behulp van de vertaaldienst.

## Converteer tekst naar spraak met behulp van de vertaaldienst

De REST API van de spraakdienst ondersteunt geen directe vertalingen. Je kunt echter de vertaaldienst gebruiken om de tekst te vertalen die is gegenereerd door de spraak-naar-tekst-dienst, evenals de tekst van de gesproken reactie. Deze dienst heeft een REST API die je kunt gebruiken om tekst te vertalen, maar om het gebruik te vereenvoudigen wordt deze verpakt in een andere HTTP-trigger in je functies-app.

### Taak - maak een serverloze functie om tekst te vertalen

1. Open je `smart-timer-trigger`-project in VS Code en open de terminal, zorg ervoor dat de virtuele omgeving is geactiveerd. Zo niet, sluit en herstart de terminal.

1. Open het bestand `local.settings.json` en voeg instellingen toe voor de API-sleutel en locatie van de vertaaldienst:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    Vervang `<key>` door de API-sleutel van je vertaaldienstbron. Vervang `<location>` door de locatie die je hebt gebruikt bij het aanmaken van de vertaaldienstbron.

1. Voeg een nieuwe HTTP-trigger toe aan deze app genaamd `translate-text` met behulp van het volgende commando in de VS Code-terminal in de hoofdmap van het functies-app-project:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    Dit maakt een HTTP-trigger genaamd `translate-text`.

1. Vervang de inhoud van het bestand `__init__.py` in de map `translate-text` door het volgende:

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

    Deze code haalt de tekst en de talen uit het HTTP-verzoek. Vervolgens wordt een verzoek gedaan aan de REST API van de vertaaldienst, waarbij de talen als parameters voor de URL worden doorgegeven en de te vertalen tekst als de body. Tot slot wordt de vertaling geretourneerd.

1. Voer je functies-app lokaal uit. Je kunt deze vervolgens aanroepen met een tool zoals curl, op dezelfde manier als je de `text-to-timer` HTTP-trigger hebt getest. Zorg ervoor dat je de te vertalen tekst en de talen als een JSON-body doorgeeft:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    Dit voorbeeld vertaalt *Définir une minuterie de 30 secondes* van Frans naar Amerikaans Engels. Het zal *Set a 30-second timer* retourneren.

> 💁 Je kunt deze code vinden in de map [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions).

### Taak - gebruik de vertaalfunctie om tekst te vertalen

1. Open het `smart-timer`-project in VS Code als het nog niet geopend is.

1. Je slimme timer zal 2 talen hebben ingesteld: de taal van de server die is gebruikt om LUIS te trainen (dezelfde taal wordt ook gebruikt om berichten te maken die aan de gebruiker worden gesproken) en de taal die door de gebruiker wordt gesproken. Werk de constante `LANGUAGE` in het `config.h`-headerbestand bij naar de taal die door de gebruiker zal worden gesproken, en voeg een nieuwe constante toe genaamd `SERVER_LANGUAGE` voor de taal die is gebruikt om LUIS te trainen:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    Vervang `<user language>` door de locatienaam van de taal waarin je zult spreken, bijvoorbeeld `fr-FR` voor Frans of `zn-HK` voor Kantonees.

    Vervang `<server language>` door de locatienaam van de taal die is gebruikt om LUIS te trainen.

    Je kunt een lijst met ondersteunde talen en hun locatienamen vinden in de [documentatie over taal- en stemondersteuning op Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Als je niet meerdere talen spreekt, kun je een dienst zoals [Bing Translate](https://www.bing.com/translator) of [Google Translate](https://translate.google.com) gebruiken om te vertalen van je voorkeurstaal naar een taal naar keuze. Deze diensten kunnen vervolgens audio afspelen van de vertaalde tekst.
    >
    > Bijvoorbeeld, als je LUIS in het Engels traint, maar Frans wilt gebruiken als de gebruikers-taal, kun je zinnen zoals "set a 2 minute and 27 second timer" vertalen van Engels naar Frans met Bing Translate, en vervolgens de knop **Luister naar vertaling** gebruiken om de vertaling in je microfoon te spreken.
    >
    > ![De knop Luister naar vertaling op Bing Translate](../../../../../translated_images/nl/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Voeg de API-sleutel en locatie van de vertaaldienst toe onder de `SPEECH_LOCATION`:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    Vervang `<KEY>` door de API-sleutel van je vertaaldienstbron. Vervang `<LOCATION>` door de locatie die je hebt gebruikt bij het aanmaken van de vertaaldienstbron.

1. Voeg de URL van de vertaaldienst-trigger toe onder de `VOICE_URL`:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    Vervang `<URL>` door de URL van de `translate-text` HTTP-trigger in je functies-app. Dit zal hetzelfde zijn als de waarde voor `TEXT_TO_TIMER_FUNCTION_URL`, behalve dat de functienaam `translate-text` is in plaats van `text-to-timer`.

1. Voeg een nieuw bestand toe aan de map `src` genaamd `text_translator.h`.

1. Dit nieuwe `text_translator.h`-headerbestand zal een klasse bevatten om tekst te vertalen. Voeg het volgende toe aan dit bestand om deze klasse te declareren:

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

    Dit declareert de `TextTranslator`-klasse, samen met een instantie van deze klasse. De klasse heeft één veld voor de WiFi-client.

1. Voeg aan het `public`-gedeelte van deze klasse een methode toe om tekst te vertalen:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    Deze methode neemt de taal waaruit vertaald moet worden en de taal waarnaar vertaald moet worden. Bij het verwerken van spraak wordt de spraak vertaald van de gebruikers-taal naar de LUIS-server-taal, en bij het geven van reacties wordt vertaald van de LUIS-server-taal naar de gebruikers-taal.

1. Voeg in deze methode code toe om een JSON-body te construeren met de te vertalen tekst en de talen:

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

1. Voeg hieronder de volgende code toe om de body naar de serverloze functies-app te sturen:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Voeg vervolgens code toe om de respons op te halen:

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

1. Voeg tot slot code toe om de verbinding te sluiten en de vertaalde tekst te retourneren:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### Taak - vertaal de herkende spraak en de reacties

1. Open het bestand `main.cpp`.

1. Voeg bovenaan het bestand een include-directive toe voor het headerbestand van de `TextTranslator`-klasse:

    ```cpp
    #include "text_translator.h"
    ```

1. De tekst die wordt uitgesproken wanneer een timer wordt ingesteld of afloopt, moet worden vertaald. Voeg hiervoor het volgende toe als de eerste regel van de `say`-functie:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Dit zal de tekst vertalen naar de gebruikers-taal.

1. In de `processAudio`-functie wordt tekst opgehaald uit de opgenomen audio met de aanroep `String text = speechToText.convertSpeechToText();`. Vertaal de tekst na deze aanroep:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Dit zal de tekst vertalen van de gebruikers-taal naar de taal die op de server wordt gebruikt.

1. Bouw deze code, upload deze naar je Wio Terminal en test het via de seriële monitor. Zodra je `Ready` ziet in de seriële monitor, druk je op de C-knop (de knop aan de linkerkant, het dichtst bij de aan/uit-schakelaar) en spreek je. Zorg ervoor dat je functies-app actief is en vraag een timer aan in de gebruikers-taal, door zelf die taal te spreken of door een vertaal-app te gebruiken.

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

> 💁 Je kunt deze code vinden in de map [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal).

😀 Je meertalige timerprogramma was een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.