<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d620a470d9dd8614d99824832978360a",
  "translation_date": "2025-08-27T21:34:48+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/virtual-device-translate-speech.md",
  "language_code": "hu"
}
-->
# Beszéd fordítása - Virtuális IoT eszköz

A lecke ezen részében kódot fogsz írni, amely a beszédet szöveggé alakítja a beszédfelismerő szolgáltatás segítségével, majd a szöveget lefordítja a Fordító szolgáltatással, mielőtt egy beszélt választ generálna.

## A beszédfelismerő szolgáltatás használata beszéd fordítására

A beszédfelismerő szolgáltatás nemcsak a beszédet tudja szöveggé alakítani ugyanazon a nyelven, hanem az eredményt más nyelvekre is le tudja fordítani.

### Feladat - a beszédfelismerő szolgáltatás használata beszéd fordítására

1. Nyisd meg a `smart-timer` projektet a VS Code-ban, és győződj meg róla, hogy a virtuális környezet betöltődött a terminálban.

1. Add hozzá a következő import utasításokat a meglévő importok alá:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    Ez importálja azokat az osztályokat, amelyek a beszéd fordításához szükségesek, valamint egy `requests` könyvtárat, amelyet később a Fordító szolgáltatás hívásához fogsz használni.

1. Az okos időzítőnek két nyelvet kell beállítanod - a szerver nyelvét, amelyet a LUIS betanításához használtál (ugyanez a nyelv használatos a felhasználónak szóló üzenetek létrehozásához is), és a felhasználó által beszélt nyelvet. Frissítsd a `language` változót a felhasználó által beszélt nyelvre, és adj hozzá egy új változót `server_language` néven a LUIS betanításához használt nyelvhez:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Cseréld ki a `<user language>` helyére a beszélt nyelv helyi beállításának nevét, például `fr-FR` a franciához, vagy `zn-HK` a kantonihoz.

    Cseréld ki a `<server language>` helyére a LUIS betanításához használt nyelv helyi beállításának nevét.

    A támogatott nyelvek és azok helyi beállításainak listáját megtalálod a [Microsoft dokumentációjában a nyelv- és hangtámogatásról](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Ha nem beszélsz több nyelvet, használhatsz olyan szolgáltatásokat, mint a [Bing Translate](https://www.bing.com/translator) vagy a [Google Translate](https://translate.google.com), hogy lefordítsd a preferált nyelvedet egy másik nyelvre. Ezek a szolgáltatások képesek lejátszani a lefordított szöveg hangját is. Vedd figyelembe, hogy a beszédfelismerő figyelmen kívül hagyhat néhány hangkimenetet az eszközödről, ezért szükséged lehet egy másik eszközre a lefordított szöveg lejátszásához.
    >
    > Például, ha angolul tanítod be a LUIS-t, de franciát szeretnél használni felhasználói nyelvként, lefordíthatod az olyan mondatokat, mint például "set a 2 minute and 27 second timer" angolról franciára a Bing Translate segítségével, majd a **Listen translation** gombbal mondhatod el a fordítást a mikrofonodba.
    >
    > ![A Bing Translate hallgatási fordítás gombja](../../../../../translated_images/hu/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Cseréld le a `recognizer_config` és `recognizer` deklarációkat a következőre:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    Ez létrehoz egy fordítási konfigurációt, amely felismeri a beszédet a felhasználói nyelven, és fordításokat készít a felhasználói és a szerver nyelvre. Ezután ezt a konfigurációt használja egy fordítási felismerő létrehozásához - egy olyan beszédfelismerőhöz, amely a beszédfelismerés eredményét több nyelvre is le tudja fordítani.

    > 💁 Az eredeti nyelvet meg kell adni a `target_languages` mezőben, különben nem kapsz fordításokat.

1. Frissítsd a `recognized` függvényt, cseréld le a függvény teljes tartalmát a következőre:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    Ez a kód ellenőrzi, hogy a felismerési esemény azért lett-e aktiválva, mert a beszédet lefordították (ez az esemény máskor is aktiválódhat, például amikor a beszédet felismerik, de nem fordítják le). Ha a beszédet lefordították, megkeresi a fordítást az `args.result.translations` szótárban, amely megfelel a szerver nyelvének.

    Az `args.result.translations` szótár a helyi beállítás nyelvi részére van kulcsolva, nem az egész beállításra. Például, ha `fr-FR`-re kérsz fordítást franciára, a szótár tartalmazni fog egy bejegyzést `fr`-re, nem pedig `fr-FR`-re.

    A lefordított szöveget ezután elküldi az IoT Hubnak.

1. Futtasd a kódot a fordítások teszteléséhez. Győződj meg róla, hogy a funkcióalkalmazásod fut, és kérj egy időzítőt a felhasználói nyelven, akár úgy, hogy magad beszéled azt a nyelvet, akár egy fordító alkalmazás segítségével.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## Szöveg fordítása a Fordító szolgáltatással

A beszédfelismerő szolgáltatás nem támogatja a szöveg visszafordítását beszéddé, ehelyett a Fordító szolgáltatást használhatod a szöveg fordítására. Ez a szolgáltatás egy REST API-t biztosít, amelyet a szöveg fordítására használhatsz.

### Feladat - a Fordító erőforrás használata szöveg fordítására

1. Add hozzá a Fordító API kulcsát a `speech_api_key` alá:

    ```python
    translator_api_key = '<key>'
    ```

    Cseréld ki a `<key>` helyére a Fordító szolgáltatás erőforrásának API kulcsát.

1. A `say` függvény fölé definiálj egy `translate_text` függvényt, amely a szöveget a szerver nyelvéről a felhasználói nyelvre fordítja:

    ```python
    def translate_text(text):
    ```

1. Ebben a függvényben definiáld az URL-t és a fejlécet a REST API híváshoz:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    Ennek az API-nak az URL-je nem helyspecifikus, ehelyett a helyet egy fejlécben kell megadni. Az API kulcsot közvetlenül használják, így a beszédfelismerő szolgáltatással ellentétben nincs szükség hozzáférési token beszerzésére a tokenkibocsátó API-tól.

1. Ez alatt definiáld a hívás paramétereit és törzsét:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    A `params` határozza meg az API híváshoz átadandó paramétereket, megadva a forrás- és célnyelveket. Ez a hívás a `from` nyelven lévő szöveget fordítja le a `to` nyelvre.

    A `body` tartalmazza a lefordítandó szöveget. Ez egy tömb, mivel több szövegrészlet is lefordítható ugyanabban a hívásban.

1. Hajtsd végre a REST API hívást, és szerezd meg a választ:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    A visszakapott válasz egy JSON tömb, amely egy elemet tartalmaz a fordításokkal. Ez az elem egy tömböt tartalmaz az összes fordításról, amelyeket a törzsben átadtál.

    ```json
    [
        {
            "translations": [
                {
                    "text": "Chronométrant votre minuterie de 2 minutes 27 secondes.",
                    "to": "fr"
                }
            ]
        }
    ]
    ```

1. Add vissza az első elem első fordításának `text` tulajdonságát:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Frissítsd a `say` függvényt, hogy a kimondandó szöveget lefordítsa, mielőtt az SSML-t generálná:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    Ez a kód az eredeti és a lefordított szöveget is kiírja a konzolra.

1. Futtasd a kódot. Győződj meg róla, hogy a funkcióalkalmazásod fut, és kérj egy időzítőt a felhasználói nyelven, akár úgy, hogy magad beszéled azt a nyelvet, akár egy fordító alkalmazás segítségével.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 A különböző nyelveken való kifejezésmódok eltérései miatt előfordulhat, hogy a fordítások kissé eltérnek a LUIS-nek adott példáktól. Ha ez a helyzet, adj hozzá több példát a LUIS-hez, tanítsd újra, majd publikáld újra a modellt.

> 💁 Ezt a kódot megtalálod a [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device) mappában.

😀 A többnyelvű időzítő programod sikeres volt!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Fontos információk esetén javasolt professzionális, emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.