<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-27T21:21:17+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "hu"
}
-->
# Beszéd szöveggé alakítása - Virtuális IoT eszköz

Ebben a leckében kódot fogsz írni, amely a mikrofonod által rögzített beszédet szöveggé alakítja a beszédfelismerő szolgáltatás segítségével.

## Beszéd szöveggé alakítása

Windows, Linux és macOS rendszereken a beszédfelismerő szolgáltatások Python SDK-ja használható arra, hogy a mikrofonodat figyelje, és az észlelt beszédet szöveggé alakítsa. Folyamatosan figyeli az audio szinteket, és akkor küldi el a beszédet szöveggé alakításra, amikor az audio szint csökken, például egy beszédblokk végén.

### Feladat - beszéd szöveggé alakítása

1. Hozz létre egy új Python alkalmazást a számítógépeden egy `smart-timer` nevű mappában, amely egyetlen `app.py` fájlt és egy Python virtuális környezetet tartalmaz.

1. Telepítsd a beszédfelismerő szolgáltatásokhoz szükséges Pip csomagot. Győződj meg róla, hogy ezt egy olyan terminálból telepíted, amelyben a virtuális környezet aktiválva van.

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ Ha a következő hibát kapod:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > Frissítened kell a Pip-et. Ezt az alábbi parancs segítségével teheted meg, majd próbáld meg újra telepíteni a csomagot:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Add hozzá a következő importokat az `app.py` fájlhoz:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    Ezek olyan osztályokat importálnak, amelyek a beszédfelismeréshez szükségesek.

1. Add hozzá a következő kódot a konfiguráció deklarálásához:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    Cseréld ki a `<key>` helyére a beszédfelismerő szolgáltatás API kulcsát. Cseréld ki a `<location>` helyére azt a helyet, amelyet a beszédfelismerő szolgáltatás erőforrás létrehozásakor használtál.

    Cseréld ki a `<language>` helyére azt a nyelvi helyet, amelyen beszélni fogsz, például `en-GB` angolhoz vagy `zn-HK` kantonihoz. A támogatott nyelvek és nyelvi helyek listáját megtalálhatod a [Microsoft dokumentációjában a nyelv- és hangtámogatásról](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Ez a konfiguráció egy `SpeechConfig` objektumot hoz létre, amelyet a beszédfelismerő szolgáltatások konfigurálására használnak.

1. Add hozzá a következő kódot egy beszédfelismerő létrehozásához:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. A beszédfelismerő egy háttérszálon fut, amely figyeli az audio jeleket, és az észlelt beszédet szöveggé alakítja. A szöveget egy visszahívási funkcióval érheted el - egy olyan funkcióval, amelyet definiálsz és átadsz a felismerőnek. Minden alkalommal, amikor beszédet észlel, a visszahívás meghívásra kerül. Add hozzá a következő kódot egy visszahívás definiálásához, és add át ezt a visszahívást a felismerőnek, valamint definiálj egy funkciót a szöveg feldolgozására, amely kiírja azt a konzolra:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. A felismerő csak akkor kezd el figyelni, amikor kifejezetten elindítod. Add hozzá a következő kódot a felismerés elindításához. Ez a háttérben fut, így az alkalmazásodnak egy végtelen ciklust is tartalmaznia kell, amely alvó állapotban tartja az alkalmazást.

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. Futtasd az alkalmazást. Beszélj a mikrofonba, és az audio szöveggé alakítva megjelenik a konzolon.

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    Próbálj ki különböző típusú mondatokat, valamint olyan mondatokat, amelyekben azonos hangzású, de eltérő jelentésű szavak szerepelnek. Például, ha angolul beszélsz, mondj olyat, hogy "I want to buy two bananas and an apple too", és figyeld meg, hogyan használja a megfelelő "to", "two" és "too" szavakat a szó kontextusa alapján, nem csak a hangzása alapján.

> 💁 Ezt a kódot megtalálhatod a [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device) mappában.

😀 A beszéd szöveggé alakító programod sikeres volt!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Fontos információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.