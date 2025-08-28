<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-28T19:25:44+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "lt"
}
-->
# Kalbos pavertimas tekstu - Virtualus IoT įrenginys

Šioje pamokos dalyje rašysite kodą, kuris pavers mikrofono užfiksuotą kalbą į tekstą, naudodamiesi kalbos paslauga.

## Kalbos pavertimas tekstu

Windows, Linux ir macOS operacinėse sistemose Python SDK kalbos paslaugos gali būti naudojamos mikrofonui klausytis ir aptiktą kalbą paversti tekstu. Ji nuolat klausosi, aptinka garso lygius ir siunčia kalbą konvertavimui į tekstą, kai garso lygis sumažėja, pavyzdžiui, pasibaigus kalbos blokui.

### Užduotis - paversti kalbą tekstu

1. Sukurkite naują Python programą savo kompiuteryje aplanke, pavadintame `smart-timer`, su vienu failu, pavadintu `app.py`, ir Python virtualia aplinka.

1. Įdiekite Pip paketą kalbos paslaugoms. Įsitikinkite, kad tai darote terminale, kuriame aktyvuota virtuali aplinka.

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ Jei gaunate šią klaidą:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > Jums reikės atnaujinti Pip. Tai padarykite naudodami šią komandą, tada bandykite dar kartą įdiegti paketą:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Pridėkite šiuos importus į `app.py` failą:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    Tai importuoja kai kurias klases, naudojamas kalbos atpažinimui.

1. Pridėkite šį kodą, kad deklaruotumėte konfigūraciją:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    Pakeiskite `<key>` į savo kalbos paslaugos API raktą. Pakeiskite `<location>` į vietą, kurią naudojote kurdami kalbos paslaugos resursą.

    Pakeiskite `<language>` į kalbos, kuria kalbėsite, lokalės pavadinimą, pavyzdžiui, `en-GB` anglų kalbai arba `zn-HK` kantoniečių kalbai. Palaikomų kalbų ir jų lokalės pavadinimų sąrašą galite rasti [Microsoft dokumentacijoje apie kalbos ir balso palaikymą](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Ši konfigūracija naudojama `SpeechConfig` objektui sukurti, kuris bus naudojamas kalbos paslaugų konfigūravimui.

1. Pridėkite šį kodą, kad sukurtumėte kalbos atpažinimo įrankį:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. Kalbos atpažinimo įrankis veikia fone, klausydamas garso ir paversdamas jame esančią kalbą į tekstą. Tekstą galite gauti naudodami atgalinio iškvietimo funkciją - funkciją, kurią apibrėžiate ir perduodate atpažinimo įrankiui. Kiekvieną kartą aptikus kalbą, iškviečiama atgalinio iškvietimo funkcija. Pridėkite šį kodą, kad apibrėžtumėte atgalinio iškvietimo funkciją, perduotumėte ją atpažinimo įrankiui ir apibrėžtumėte funkciją, kuri apdoroja tekstą, išvesdama jį į konsolę:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. Atpažinimo įrankis pradeda klausytis tik tada, kai jį aiškiai paleidžiate. Pridėkite šį kodą, kad pradėtumėte atpažinimą. Tai vyksta fone, todėl jūsų programai taip pat reikės begalinio ciklo, kuris užmigdo programą, kad ji liktų aktyvi.

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. Paleiskite šią programą. Kalbėkite į mikrofoną, ir konvertuota kalba į tekstą bus išvesta į konsolę.

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    Išbandykite skirtingus sakinių tipus, taip pat sakinius, kuriuose žodžiai skamba vienodai, bet turi skirtingas reikšmes. Pavyzdžiui, jei kalbate angliškai, pasakykite „I want to buy two bananas and an apple too“ ir pastebėkite, kaip programa naudoja tinkamus „to“, „two“ ir „too“, remdamasi žodžio kontekstu, o ne tik jo skambesiu.

> 💁 Šį kodą galite rasti [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device) aplanke.

😀 Jūsų kalbos pavertimo tekstu programa buvo sėkminga!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama profesionali žmogaus vertimo paslauga. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius naudojant šį vertimą.