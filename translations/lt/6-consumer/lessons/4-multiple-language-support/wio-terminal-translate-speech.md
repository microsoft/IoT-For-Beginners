<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f6c164e349f8989959e02a90f37908d",
  "translation_date": "2025-08-28T19:32:15+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/wio-terminal-translate-speech.md",
  "language_code": "lt"
}
-->
# Išversti kalbą - Wio Terminal

Šioje pamokos dalyje rašysite kodą, skirtą teksto vertimui naudojant vertimo paslaugą.

## Konvertuoti tekstą į kalbą naudojant vertimo paslaugą

Kalbos paslaugos REST API tiesiogiai nepalaiko vertimų, tačiau galite naudoti Vertimo paslaugą, kad išverstumėte tekstą, sugeneruotą kalbos į tekstą paslauga, ir tekstą, kuris bus pasakytas atsakant. Ši paslauga turi REST API, kurį galite naudoti tekstui versti, tačiau, kad būtų lengviau naudoti, ji bus apgaubta kitu HTTP trigeriu jūsų funkcijų programoje.

### Užduotis - sukurti serverless funkciją tekstui versti

1. Atidarykite savo projektą `smart-timer-trigger` VS Code programoje ir atidarykite terminalą, įsitikindami, kad virtuali aplinka yra aktyvuota. Jei ne, uždarykite ir iš naujo sukurkite terminalą.

1. Atidarykite failą `local.settings.json` ir pridėkite nustatymus vertimo API raktui ir vietai:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    Pakeiskite `<key>` API raktu, skirtu jūsų vertimo paslaugos resursui. Pakeiskite `<location>` vieta, kurią naudojote kurdami vertimo paslaugos resursą.

1. Pridėkite naują HTTP trigerį šiai programai, pavadintą `translate-text`, naudodami šią komandą iš VS Code terminalo, esančio funkcijų programos projekto šakniniame aplanke:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    Tai sukurs HTTP trigerį, pavadintą `translate-text`.

1. Pakeiskite `__init__.py` failo turinį aplanke `translate-text` šiuo:

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

    Šis kodas ištraukia tekstą ir kalbas iš HTTP užklausos. Tada jis pateikia užklausą vertimo REST API, perduodamas kalbas kaip URL parametrus ir tekstą, kurį reikia išversti, kaip užklausos turinį. Galiausiai grąžinamas vertimas.

1. Vietoje paleiskite savo funkcijų programą. Tada galite ją iškviesti naudodami tokį įrankį kaip curl, taip pat kaip testavote savo `text-to-timer` HTTP trigerį. Įsitikinkite, kad perduodate tekstą, kurį reikia išversti, ir kalbas kaip JSON turinį:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    Šis pavyzdys verčia *Définir une minuterie de 30 secondes* iš prancūzų į JAV anglų kalbą. Jis grąžins *Set a 30-second timer*.

> 💁 Šį kodą galite rasti aplanke [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions).

### Užduotis - naudoti vertimo funkciją tekstui versti

1. Atidarykite projektą `smart-timer` VS Code programoje, jei jis dar neatidarytas.

1. Jūsų išmanusis laikmatis turės nustatytas 2 kalbas - serverio kalbą, kuri buvo naudojama LUIS mokymui (ta pati kalba taip pat naudojama kuriant pranešimus, skirtus vartotojui), ir vartotojo kalbą. Atnaujinkite konstantą `LANGUAGE` faile `config.h`, kad ji būtų kalba, kuria kalbės vartotojas, ir pridėkite naują konstantą, pavadintą `SERVER_LANGUAGE`, skirtą kalbai, kuri buvo naudojama LUIS mokymui:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    Pakeiskite `<user language>` kalbos lokalės pavadinimu, kuria kalbėsite, pavyzdžiui, `fr-FR` prancūzų kalbai arba `zn-HK` kantoniečių kalbai.

    Pakeiskite `<server language>` kalbos lokalės pavadinimu, kuris buvo naudojamas LUIS mokymui.

    Palaikomų kalbų ir jų lokalės pavadinimų sąrašą galite rasti [Microsoft dokumentacijoje apie kalbos ir balso palaikymą](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Jei nekalbate keliomis kalbomis, galite naudoti tokią paslaugą kaip [Bing Translate](https://www.bing.com/translator) arba [Google Translate](https://translate.google.com), kad išverstumėte iš savo pageidaujamos kalbos į pasirinktą kalbą. Šios paslaugos gali atkurti išversto teksto garsą.
    >
    > Pavyzdžiui, jei mokote LUIS anglų kalba, bet norite naudoti prancūzų kalbą kaip vartotojo kalbą, galite išversti sakinius, tokius kaip "set a 2 minute and 27 second timer" iš anglų į prancūzų kalbą naudodami Bing Translate, tada naudoti mygtuką **Listen translation**, kad pasakytumėte vertimą į mikrofoną.
    >
    > ![Mygtukas "Listen translation" Bing Translate](../../../../../translated_images/lt/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Pridėkite vertimo API raktą ir vietą po `SPEECH_LOCATION`:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    Pakeiskite `<KEY>` API raktu, skirtu jūsų vertimo paslaugos resursui. Pakeiskite `<LOCATION>` vieta, kurią naudojote kurdami vertimo paslaugos resursą.

1. Pridėkite vertimo trigerio URL po `VOICE_URL`:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    Pakeiskite `<URL>` URL adresu, skirtu `translate-text` HTTP trigeriui jūsų funkcijų programoje. Tai bus tas pats kaip `TEXT_TO_TIMER_FUNCTION_URL` reikšmė, išskyrus funkcijos pavadinimą `translate-text` vietoj `text-to-timer`.

1. Pridėkite naują failą aplanke `src`, pavadintą `text_translator.h`.

1. Šis naujas antraštės failas `text_translator.h` turės klasę, skirtą tekstui versti. Pridėkite šį kodą į failą, kad deklaruotumėte šią klasę:

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

    Tai deklaruoja klasę `TextTranslator` kartu su šios klasės egzemplioriumi. Klasė turi vieną lauką, skirtą WiFi klientui.

1. Prie klasės `public` sekcijos pridėkite metodą tekstui versti:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    Šis metodas priima kalbą, iš kurios reikia versti, ir kalbą, į kurią reikia versti. Apdorojant kalbą, ji bus verčiama iš vartotojo kalbos į LUIS serverio kalbą, o atsakant ji bus verčiama iš LUIS serverio kalbos į vartotojo kalbą.

1. Šiame metode pridėkite kodą, kad sukurtumėte JSON turinį, kuriame būtų tekstas, kurį reikia išversti, ir kalbos:

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

1. Po to pridėkite šį kodą, kad išsiųstumėte turinį į serverless funkcijų programą:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Toliau pridėkite kodą, kad gautumėte atsakymą:

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

1. Galiausiai pridėkite kodą, kad uždarytumėte ryšį ir grąžintumėte išverstą tekstą:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### Užduotis - išversti atpažintą kalbą ir atsakymus

1. Atidarykite failą `main.cpp`.

1. Pridėkite įtraukimo direktyvą failo viršuje, skirtą `TextTranslator` klasės antraštės failui:

    ```cpp
    #include "text_translator.h"
    ```

1. Tekstas, kuris sakomas, kai laikmatis nustatomas arba baigiasi, turi būti išverstas. Norėdami tai padaryti, pridėkite šį kodą kaip pirmą eilutę funkcijoje `say`:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Tai išvers tekstą į vartotojo kalbą.

1. Funkcijoje `processAudio` tekstas gaunamas iš užfiksuoto garso naudojant `String text = speechToText.convertSpeechToText();`. Po šio iškvietimo išverskite tekstą:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Tai išvers tekstą iš vartotojo kalbos į serverio naudojamą kalbą.

1. Sukurkite šį kodą, įkelkite jį į savo Wio Terminal ir išbandykite per serijinį monitorių. Kai serijiniame monitoriuje pamatysite `Ready`, paspauskite C mygtuką (kairėje pusėje, arčiausiai maitinimo jungiklio) ir kalbėkite. Įsitikinkite, kad jūsų funkcijų programa veikia, ir paprašykite laikmačio vartotojo kalba, arba kalbėdami ta kalba patys, arba naudodami vertimo programą.

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

> 💁 Šį kodą galite rasti aplanke [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal).

😀 Jūsų daugiakalbė laikmačio programa buvo sėkminga!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.