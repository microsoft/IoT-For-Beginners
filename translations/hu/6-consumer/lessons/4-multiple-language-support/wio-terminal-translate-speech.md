<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f6c164e349f8989959e02a90f37908d",
  "translation_date": "2025-08-27T21:32:22+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/wio-terminal-translate-speech.md",
  "language_code": "hu"
}
-->
# Beszéd fordítása - Wio Terminal

Ebben a leckében kódot fogsz írni, amely a fordító szolgáltatást használja szöveg fordítására.

## Szöveg átalakítása beszéddé a fordító szolgáltatás segítségével

A beszédszolgáltatás REST API-ja nem támogatja a közvetlen fordítást, ehelyett a Fordító szolgáltatást használhatod a beszéd-szöveg szolgáltatás által generált szöveg és a kimondott válasz szövegének fordítására. Ez a szolgáltatás egy REST API-t biztosít a szöveg fordításához, de a használat megkönnyítése érdekében ezt egy másik HTTP triggerbe csomagoljuk a funkciós alkalmazásodban.

### Feladat - szerver nélküli funkció létrehozása szöveg fordítására

1. Nyisd meg a `smart-timer-trigger` projektet a VS Code-ban, és nyisd meg a terminált, ügyelve arra, hogy a virtuális környezet aktiválva legyen. Ha nem, zárd be és hozd létre újra a terminált.

1. Nyisd meg a `local.settings.json` fájlt, és add hozzá a fordító API kulcsának és helyének beállításait:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    Cseréld le a `<key>` értéket a fordító szolgáltatás erőforrásának API kulcsára. Cseréld le a `<location>` értéket arra a helyre, amelyet a fordító szolgáltatás erőforrás létrehozásakor használtál.

1. Adj hozzá egy új HTTP triggert ehhez az alkalmazáshoz `translate-text` néven a következő parancs segítségével, amelyet a VS Code termináljában futtatsz a funkciós alkalmazás projekt gyökérmappájában:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    Ez létrehoz egy `translate-text` nevű HTTP triggert.

1. Cseréld le a `translate-text` mappában található `__init__.py` fájl tartalmát a következőre:

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

    Ez a kód kinyeri a szöveget és a nyelveket a HTTP kérésből. Ezután kérést küld a fordító REST API-nak, a nyelveket paraméterként adva meg az URL-hez, és a fordítandó szöveget a törzsben. Végül visszaadja a fordítást.

1. Futtasd helyben a funkciós alkalmazásodat. Ezután egy olyan eszközzel, mint például a curl, meghívhatod, ugyanúgy, ahogy a `text-to-timer` HTTP triggert tesztelted. Ügyelj arra, hogy a fordítandó szöveget és a nyelveket JSON törzsként add meg:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    Ez a példa a *Définir une minuterie de 30 secondes* szöveget fordítja franciáról amerikai angolra. Az eredmény *Set a 30-second timer* lesz.

> 💁 Ezt a kódot megtalálod a [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions) mappában.

### Feladat - a fordító funkció használata szöveg fordítására

1. Nyisd meg a `smart-timer` projektet a VS Code-ban, ha még nincs megnyitva.

1. Az okos időzítőd két nyelvet fog használni - a szerver nyelvét, amelyet a LUIS betanításához használtak (ugyanez a nyelv használatos a felhasználónak szóló üzenetek összeállításához is), és a felhasználó által beszélt nyelvet. Frissítsd a `LANGUAGE` konstans értékét a `config.h` fejlécfájlban a felhasználó által beszélt nyelvre, és adj hozzá egy új konstansot `SERVER_LANGUAGE` néven a LUIS betanításához használt nyelvhez:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    Cseréld le a `<user language>` értéket a beszélt nyelv helyi nevére, például `fr-FR` a franciához vagy `zn-HK` a kantonihoz.

    Cseréld le a `<server language>` értéket a LUIS betanításához használt nyelv helyi nevére.

    A támogatott nyelvek és helyi nevek listáját megtalálod a [Microsoft dokumentációjában a nyelv- és hangtámogatásról](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Ha nem beszélsz több nyelvet, használhatsz olyan szolgáltatásokat, mint a [Bing Translate](https://www.bing.com/translator) vagy a [Google Translate](https://translate.google.com), hogy lefordítsd a kedvenc nyelvedet egy másik nyelvre. Ezek a szolgáltatások le is tudják játszani a fordított szöveg hangját.
    >
    > Például, ha LUIS-t angolul tanítod be, de franciát szeretnél használni felhasználói nyelvként, lefordíthatod az olyan mondatokat, mint például "set a 2 minute and 27 second timer" angolról franciára a Bing Translate segítségével, majd a **Listen translation** gombbal kimondhatod a fordítást a mikrofonodba.
    >
    > ![A Bing Translate hallgatás fordítás gombja](../../../../../translated_images/hu/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Add hozzá a fordító API kulcsát és helyét a `SPEECH_LOCATION` alá:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    Cseréld le a `<KEY>` értéket a fordító szolgáltatás erőforrásának API kulcsára. Cseréld le a `<LOCATION>` értéket arra a helyre, amelyet a fordító szolgáltatás erőforrás létrehozásakor használtál.

1. Add hozzá a fordító trigger URL-jét a `VOICE_URL` alá:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    Cseréld le a `<URL>` értéket a `translate-text` HTTP trigger URL-jére a funkciós alkalmazásodban. Ez ugyanaz lesz, mint a `TEXT_TO_TIMER_FUNCTION_URL` értéke, kivéve, hogy a funkció neve `translate-text` lesz `text-to-timer` helyett.

1. Adj hozzá egy új fájlt a `src` mappához `text_translator.h` néven.

1. Ez az új `text_translator.h` fejlécfájl egy osztályt fog tartalmazni a szöveg fordítására. Add hozzá a következőt ehhez a fájlhoz az osztály deklarálásához:

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

    Ez deklarálja a `TextTranslator` osztályt, valamint ennek egy példányát. Az osztálynak egyetlen mezője van a WiFi kliens számára.

1. Az osztály `public` szekciójához adj hozzá egy metódust a szöveg fordítására:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    Ez a metódus megkapja a forrásnyelvet és a célnyelvet. Beszéd kezelésekor a beszédet a felhasználói nyelvről a LUIS szerver nyelvére fordítja, válaszadáskor pedig a LUIS szerver nyelvéről a felhasználói nyelvre.

1. Ebben a metódusban adj hozzá kódot egy JSON törzs létrehozásához, amely tartalmazza a fordítandó szöveget és a nyelveket:

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

1. Ezután adj hozzá kódot a törzs elküldéséhez a szerver nélküli funkciós alkalmazásnak:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Ezután adj hozzá kódot a válasz lekéréséhez:

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

1. Végül adj hozzá kódot a kapcsolat lezárásához és a fordított szöveg visszaadásához:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### Feladat - a felismert beszéd és a válaszok fordítása

1. Nyisd meg a `main.cpp` fájlt.

1. Adj hozzá egy include direktívát a fájl tetejéhez a `TextTranslator` osztály fejlécfájljához:

    ```cpp
    #include "text_translator.h"
    ```

1. Az időzítő beállításakor vagy lejártakor kimondott szöveget le kell fordítani. Ehhez add hozzá a következőt a `say` függvény első soraként:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Ez lefordítja a szöveget a felhasználó nyelvére.

1. A `processAudio` függvényben a rögzített hangból szöveget nyerünk ki a `String text = speechToText.convertSpeechToText();` hívással. E hívás után fordítsd le a szöveget:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Ez lefordítja a szöveget a felhasználó nyelvéről a szerveren használt nyelvre.

1. Fordítsd le a kódot, töltsd fel a Wio Terminal eszközödre, és teszteld a soros monitoron keresztül. Amint a `Ready` üzenetet látod a soros monitoron, nyomd meg a C gombot (a bal oldali, a bekapcsoló kapcsolóhoz legközelebbi gomb), és beszélj. Győződj meg róla, hogy a funkciós alkalmazásod fut, és kérj időzítőt a felhasználói nyelven, akár saját magad beszélve, akár egy fordító alkalmazás segítségével.

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

> 💁 Ezt a kódot megtalálod a [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal) mappában.

😀 A többnyelvű időzítő programod sikeres volt!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Fontos információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.