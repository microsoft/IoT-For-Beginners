<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-27T21:24:16+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "hu"
}
-->
# Beszéd szöveggé alakítása - Raspberry Pi

Ebben a leckében kódot fogsz írni, amely a rögzített hangban lévő beszédet szöveggé alakítja a beszédfelismerő szolgáltatás segítségével.

## Küldd el a hangot a beszédfelismerő szolgáltatásnak

A hangot a REST API segítségével lehet elküldeni a beszédfelismerő szolgáltatásnak. A szolgáltatás használatához először hozzáférési tokent kell kérned, majd ezt a tokent használva érheted el a REST API-t. Ezek a hozzáférési tokenek 10 perc után lejárnak, ezért a kódodnak rendszeresen új tokent kell kérnie, hogy mindig naprakész legyen.

### Feladat - hozzáférési token kérése

1. Nyisd meg a `smart-timer` projektet a Pi eszközödön.

1. Távolítsd el a `play_audio` függvényt. Erre már nincs szükség, mivel nem szeretnéd, hogy az okos időzítő visszamondja, amit mondtál.

1. Add hozzá a következő importot az `app.py` fájl tetejéhez:

    ```python
    import requests
    ```

1. Add hozzá a következő kódot a `while True` ciklus fölé, hogy beállítsd a beszédfelismerő szolgáltatás néhány paraméterét:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    Cseréld ki a `<key>` helyére a beszédfelismerő szolgáltatás API kulcsát. A `<location>` helyére írd be azt a helyet, amelyet a beszédfelismerő szolgáltatás létrehozásakor megadtál.

    A `<language>` helyére írd be azt a nyelvi helyet, amelyen beszélni fogsz, például `en-GB` angolhoz vagy `zn-HK` kantonihoz. A támogatott nyelvek és nyelvi helyek listáját megtalálhatod a [Microsoft dokumentációjában](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

1. Ezután add hozzá a következő függvényt, amely hozzáférési tokent kér:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Ez a függvény egy token kiadó végpontot hív meg, az API kulcsot fejlécben továbbítva. A hívás egy hozzáférési tokent ad vissza, amelyet a beszédfelismerő szolgáltatás hívásához használhatsz.

1. Ezután deklarálj egy függvényt, amely a rögzített hangban lévő beszédet szöveggé alakítja a REST API segítségével:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. Ebben a függvényben állítsd be a REST API URL-t és a fejlécet:

    ```python
    url = f'https://{location}.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1'

    headers = {
        'Authorization': 'Bearer ' + get_access_token(),
        'Content-Type': f'audio/wav; codecs=audio/pcm; samplerate={rate}',
        'Accept': 'application/json;text/xml'
    }

    params = {
        'language': language
    }
    ```

    Ez az URL-t a beszédfelismerő szolgáltatás helyének megfelelően építi fel. A fejlécet a `get_access_token` függvényből származó hozzáférési tokennel, valamint a hang rögzítéséhez használt mintavételi frekvenciával tölti ki. Végül meghatároz néhány paramétert, amelyeket az URL-lel együtt továbbít, és amelyek tartalmazzák a hang nyelvét.

1. Ezután add hozzá a következő kódot, amely meghívja a REST API-t és visszakapja a szöveget:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    Ez az URL-t hívja meg, és dekódolja a válaszban érkező JSON értéket. A válaszban található `RecognitionStatus` érték jelzi, hogy a hívás sikeresen alakította-e a beszédet szöveggé. Ha ez `Success`, akkor a függvény visszaadja a szöveget, ellenkező esetben egy üres karakterláncot ad vissza.

1. A `while True:` ciklus fölé definiálj egy függvényt, amely feldolgozza a beszédfelismerő szolgáltatás által visszaadott szöveget. Ez a függvény egyelőre csak kiírja a szöveget a konzolra.

    ```python
    def process_text(text):
        print(text)
    ```

1. Végül cseréld ki a `while True` ciklusban a `play_audio` hívást a `convert_speech_to_text` függvény hívására, és add át a szöveget a `process_text` függvénynek:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. Futtasd a kódot. Nyomd meg a gombot, és beszélj a mikrofonba. Engedd el a gombot, amikor végeztél, és a hang szöveggé lesz alakítva, majd kiíródik a konzolra.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    Próbálj ki különböző típusú mondatokat, valamint olyan mondatokat, amelyekben azonos hangzású, de eltérő jelentésű szavak szerepelnek. Például, ha angolul beszélsz, mondj olyat, hogy "I want to buy two bananas and an apple too", és figyeld meg, hogyan használja a megfelelő "to", "two" és "too" szavakat a szó kontextusa alapján, nem csak a hangzása alapján.

> 💁 Ezt a kódot megtalálhatod a [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi) mappában.

😀 A beszéd szöveggé alakító programod sikeres volt!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.