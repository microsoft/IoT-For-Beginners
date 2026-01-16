<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "bbb5aa34221fe129dd3ce4d9ec33831a",
  "translation_date": "2025-08-27T21:33:36+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/pi-translate-speech.md",
  "language_code": "hu"
}
-->
# Beszéd fordítása - Raspberry Pi

A lecke ezen részében kódot fogsz írni, amely a fordító szolgáltatást használja szöveg fordítására.

## Szöveg beszéddé alakítása a fordító szolgáltatás segítségével

A beszédszolgáltatás REST API-ja nem támogatja a közvetlen fordítást, ehelyett a Fordító szolgáltatást használhatod a beszéd szöveggé alakítása során generált szöveg, valamint a kimondott válasz szövegének fordítására. Ez a szolgáltatás egy REST API-t biztosít, amelyet a szöveg fordítására használhatsz.

### Feladat - a fordító erőforrás használata szöveg fordítására

1. Az okos időzítőd két nyelvet fog használni - a szerver nyelvét, amelyet a LUIS betanításához használtak (ugyanez a nyelv használatos a felhasználóval való kommunikációhoz), és a felhasználó által beszélt nyelvet. Frissítsd a `language` változót a felhasználó által beszélt nyelvre, és adj hozzá egy új változót `server_language` néven a LUIS betanításához használt nyelvhez:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Cseréld ki a `<user language>` helyére a beszélt nyelv helyi beállításának nevét, például `fr-FR` a franciához, vagy `zn-HK` a kantonihoz.

    Cseréld ki a `<server language>` helyére a LUIS betanításához használt nyelv helyi beállításának nevét.

    A támogatott nyelvek és azok helyi beállításainak listáját megtalálod a [Microsoft dokumentációjában a nyelv- és hangtámogatásról](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Ha nem beszélsz több nyelvet, használhatsz olyan szolgáltatásokat, mint a [Bing Translate](https://www.bing.com/translator) vagy a [Google Translate](https://translate.google.com), hogy lefordítsd a preferált nyelvedet egy másik nyelvre. Ezek a szolgáltatások a fordított szöveg hangos lejátszását is lehetővé teszik.
    >
    > Például, ha angolul tanítod be a LUIS-t, de franciát szeretnél használni felhasználói nyelvként, lefordíthatod az olyan mondatokat, mint például "állíts be egy 2 perc és 27 másodperces időzítőt" angolról franciára a Bing Translate segítségével, majd a **Hallgasd meg a fordítást** gombbal mondhatod el a fordítást a mikrofonodba.
    >
    > ![A Hallgasd meg a fordítást gomb a Bing Translate-en](../../../../../translated_images/hu/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Add hozzá a fordító API kulcsot a `speech_api_key` alá:

    ```python
    translator_api_key = '<key>'
    ```

    Cseréld ki a `<key>` helyére a fordító szolgáltatás erőforrásának API kulcsát.

1. A `say` függvény fölé definiálj egy `translate_text` függvényt, amely szöveget fordít a szerver nyelvéről a felhasználói nyelvre:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    A függvényhez átadott nyelvek a forrás- és célnyelvek - az alkalmazásodnak a felhasználói nyelvről a szerver nyelvére kell fordítania a beszéd felismerésekor, és a szerver nyelvéről a felhasználói nyelvre a kimondott válaszok esetén.

1. A függvényen belül definiáld az URL-t és a REST API hívás fejlécét:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    Ennek az API-nak az URL-je nem helyspecifikus, ehelyett a helyet egy fejlécben kell megadni. Az API kulcs közvetlenül használatos, így a beszédszolgáltatással ellentétben nincs szükség hozzáférési tokenre a tokenkibocsátó API-tól.

1. Ezután definiáld a hívás paramétereit és törzsét:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    A `params` határozza meg az API hívás paramétereit, megadva a forrás- és célnyelveket. Ez a hívás a `from` nyelven lévő szöveget fordítja a `to` nyelvre.

    A `body` tartalmazza a fordítandó szöveget. Ez egy tömb, mivel több szövegrész is fordítható egy hívásban.

1. Hajtsd végre a REST API hívást, és szerezd meg a választ:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    A visszaérkező válasz egy JSON tömb, amely egy elemet tartalmaz a fordításokkal. Ez az elem egy tömböt tartalmaz az összes, a törzsben megadott elem fordításával.

    ```json
    [
        {
            "translations": [
                {
                    "text": "Set a 2 minute 27 second timer.",
                    "to": "en"
                }
            ]
        }
    ]
    ```

1. Add vissza az első elem első fordításának `text` tulajdonságát:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Frissítsd a `while True` ciklust, hogy a `convert_speech_to_text` hívásból származó szöveget a felhasználói nyelvről a szerver nyelvére fordítsa:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    Ez a kód a konzolra is kiírja az eredeti és a fordított szövegváltozatokat.

1. Frissítsd a `say` függvényt, hogy a kimondandó szöveget a szerver nyelvéről a felhasználói nyelvre fordítsa:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    Ez a kód a konzolra is kiírja az eredeti és a fordított szövegváltozatokat.

1. Futtasd a kódodat. Győződj meg róla, hogy a funkcióalkalmazásod fut, és kérj egy időzítőt a felhasználói nyelven, akár úgy, hogy te magad beszéled azt a nyelvet, akár egy fordító alkalmazás segítségével.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py
    Connecting
    Connected
    Using voice fr-FR-DeniseNeural
    Original: Définir une minuterie de 2 minutes et 27 secondes.
    Translated: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 A különböző nyelveken való eltérő kifejezésmódok miatt előfordulhat, hogy a fordítások kissé eltérnek a LUIS-nek adott példáktól. Ha ez a helyzet, adj hozzá több példát a LUIS-hez, tanítsd újra, majd publikáld újra a modellt.

> 💁 Ezt a kódot megtalálod a [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi) mappában.

😀 A többnyelvű időzítő programod sikeres volt!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.