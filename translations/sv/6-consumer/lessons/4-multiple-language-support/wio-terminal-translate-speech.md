<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f6c164e349f8989959e02a90f37908d",
  "translation_date": "2025-08-27T21:14:32+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/wio-terminal-translate-speech.md",
  "language_code": "sv"
}
-->
# Översätt tal - Wio Terminal

I den här delen av lektionen kommer du att skriva kod för att översätta text med hjälp av översättningstjänsten.

## Konvertera text till tal med översättningstjänsten

REST-API:t för tal-tjänsten stöder inte direkta översättningar, men du kan använda översättningstjänsten för att översätta texten som genereras av tal-till-text-tjänsten och texten för det talade svaret. Den här tjänsten har ett REST-API som du kan använda för att översätta text, men för att göra det enklare att använda kommer detta att kapslas in i en annan HTTP-trigger i din funktionapp.

### Uppgift - skapa en serverlös funktion för att översätta text

1. Öppna ditt `smart-timer-trigger`-projekt i VS Code och öppna terminalen, se till att den virtuella miljön är aktiverad. Om inte, avsluta och återskapa terminalen.

1. Öppna filen `local.settings.json` och lägg till inställningar för API-nyckeln och platsen för översättningstjänsten:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    Ersätt `<key>` med API-nyckeln för din översättningstjänstresurs. Ersätt `<location>` med platsen du använde när du skapade översättningstjänstresursen.

1. Lägg till en ny HTTP-trigger i den här appen som heter `translate-text` med följande kommando från terminalen i VS Code i rotmappen för funktionapp-projektet:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    Detta skapar en HTTP-trigger som heter `translate-text`.

1. Ersätt innehållet i filen `__init__.py` i mappen `translate-text` med följande:

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

    Den här koden extraherar texten och språken från HTTP-förfrågan. Den gör sedan en förfrågan till översättningstjänstens REST-API, skickar språken som parametrar för URL:en och texten som ska översättas som kroppen. Slutligen returneras översättningen.

1. Kör din funktionapp lokalt. Du kan sedan anropa den med ett verktyg som curl på samma sätt som du testade din `text-to-timer` HTTP-trigger. Se till att skicka texten som ska översättas och språken som en JSON-kropp:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    Detta exempel översätter *Définir une minuterie de 30 secondes* från franska till amerikansk engelska. Det kommer att returnera *Set a 30-second timer*.

> 💁 Du kan hitta denna kod i mappen [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions).

### Uppgift - använd översättningsfunktionen för att översätta text

1. Öppna projektet `smart-timer` i VS Code om det inte redan är öppet.

1. Din smarta timer kommer att ha två språk inställda - språket för servern som användes för att träna LUIS (samma språk används också för att bygga meddelanden som ska talas till användaren) och språket som talas av användaren. Uppdatera konstanten `LANGUAGE` i header-filen `config.h` till att vara språket som kommer att talas av användaren, och lägg till en ny konstant som heter `SERVER_LANGUAGE` för språket som användes för att träna LUIS:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    Ersätt `<user language>` med lokalnamnet för språket du kommer att tala, till exempel `fr-FR` för franska eller `zn-HK` för kantonesiska.

    Ersätt `<server language>` med lokalnamnet för språket som användes för att träna LUIS.

    Du kan hitta en lista över de stödda språken och deras lokalnamn i [Language and voice support documentation på Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Om du inte talar flera språk kan du använda en tjänst som [Bing Translate](https://www.bing.com/translator) eller [Google Translate](https://translate.google.com) för att översätta från ditt föredragna språk till ett språk du väljer. Dessa tjänster kan sedan spela upp ljud av den översatta texten.
    >
    > Till exempel, om du tränar LUIS på engelska men vill använda franska som användarspråk, kan du översätta meningar som "set a 2 minute and 27 second timer" från engelska till franska med Bing Translate, och sedan använda knappen **Lyssna på översättning** för att tala översättningen i din mikrofon.
    >
    > ![Knappen för att lyssna på översättning på Bing Translate](../../../../../translated_images/sv/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Lägg till API-nyckeln och platsen för översättningstjänsten under `SPEECH_LOCATION`:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    Ersätt `<KEY>` med API-nyckeln för din översättningstjänstresurs. Ersätt `<LOCATION>` med platsen du använde när du skapade översättningstjänstresursen.

1. Lägg till URL:en för översättningstriggern under `VOICE_URL`:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    Ersätt `<URL>` med URL:en för HTTP-triggern `translate-text` i din funktionapp. Detta kommer att vara samma som värdet för `TEXT_TO_TIMER_FUNCTION_URL`, förutom med funktionsnamnet `translate-text` istället för `text-to-timer`.

1. Lägg till en ny fil i mappen `src` som heter `text_translator.h`.

1. Denna nya header-fil `text_translator.h` kommer att innehålla en klass för att översätta text. Lägg till följande i denna fil för att deklarera klassen:

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

    Detta deklarerar klassen `TextTranslator`, tillsammans med en instans av denna klass. Klassen har ett enda fält för WiFi-klienten.

1. Till den `public` sektionen av denna klass, lägg till en metod för att översätta text:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    Denna metod tar språket att översätta från och språket att översätta till. När tal hanteras kommer talet att översättas från användarspråket till LUIS-serverns språk, och när svar ges kommer det att översättas från LUIS-serverns språk till användarens språk.

1. I denna metod, lägg till kod för att konstruera en JSON-kropp som innehåller texten att översätta och språken:

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

1. Nedanför detta, lägg till följande kod för att skicka kroppen till den serverlösa funktionappen:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Nästa steg är att lägga till kod för att hämta svaret:

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

1. Slutligen, lägg till kod för att stänga anslutningen och returnera den översatta texten:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### Uppgift - översätt det igenkända talet och svaren

1. Öppna filen `main.cpp`.

1. Lägg till en include-direktiv högst upp i filen för header-filen för klassen `TextTranslator`:

    ```cpp
    #include "text_translator.h"
    ```

1. Texten som sägs när en timer ställs in eller går ut behöver översättas. För att göra detta, lägg till följande som första raden i funktionen `say`:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Detta kommer att översätta texten till användarens språk.

1. I funktionen `processAudio` hämtas text från det inspelade ljudet med anropet `String text = speechToText.convertSpeechToText();`. Efter detta anrop, översätt texten:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Detta kommer att översätta texten från användarens språk till språket som används på servern.

1. Bygg denna kod, ladda upp den till din Wio Terminal och testa den via seriell monitor. När du ser `Ready` i den seriella monitorn, tryck på C-knappen (den till vänster, närmast strömbrytaren) och tala. Se till att din funktionapp körs och begär en timer på användarspråket, antingen genom att tala det språket själv eller använda en översättningstjänst.

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

> 💁 Du kan hitta denna kod i mappen [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal).

😀 Ditt flerspråkiga timerprogram blev en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiserade översättningar kan innehålla fel eller inexaktheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.