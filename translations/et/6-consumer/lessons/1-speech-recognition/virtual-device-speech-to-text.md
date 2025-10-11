<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-10-11T12:23:32+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "et"
}
-->
# Kõne tekstiks - Virtuaalne IoT-seade

Selles õppetunni osas kirjutad koodi, et mikrofonist salvestatud kõne teisendada tekstiks, kasutades kõneteenust.

## Kõne tekstiks teisendamine

Windowsis, Linuxis ja macOS-is saab kõneteenuste Python SDK-d kasutada mikrofonist kuulamiseks ja tuvastatud kõne tekstiks teisendamiseks. See kuulab pidevalt, tuvastab helitaseme ja saadab kõne tekstiks teisendamiseks, kui helitase langeb, näiteks kõne lõpus.

### Ülesanne - kõne tekstiks teisendamine

1. Loo oma arvutis kaustas `smart-timer` uus Python rakendus, millel on üks fail nimega `app.py` ja Python virtuaalne keskkond.

1. Paigalda kõneteenuste Pip pakett. Veendu, et paigaldad selle terminalist, kus virtuaalne keskkond on aktiveeritud.

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ Kui saad järgmise vea:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > Pead Pip-i uuendama. Tee seda järgmise käsuga ja proovi seejärel paketti uuesti paigaldada.
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Lisa `app.py` faili järgmised impordid:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    Need impordivad mõned klassid, mida kasutatakse kõne tuvastamiseks.

1. Lisa järgmine kood konfiguratsiooni määramiseks:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    Asenda `<key>` oma kõneteenuse API võtmega. Asenda `<location>` asukohaga, mida kasutasid kõneteenuse ressursi loomisel.

    Asenda `<language>` keele lokaadi nimega, milles räägid, näiteks `en-GB` inglise keele jaoks või `zn-HK` kantoni keele jaoks. Saad toetatud keelte ja nende lokaadi nimede loendi [Microsofti dokumentatsioonist keele ja hääle toe kohta](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Seda konfiguratsiooni kasutatakse `SpeechConfig` objekti loomiseks, mis konfigureerib kõneteenused.

1. Lisa järgmine kood kõnetuvastaja loomiseks:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. Kõnetuvastaja töötab taustal, kuulates heli ja teisendades kõne tekstiks. Teksti saad kätte tagasihelistamise funktsiooni abil - funktsioon, mille määrad ja edastad tuvastajale. Iga kord, kui kõne tuvastatakse, kutsutakse tagasihelistamise funktsioon. Lisa järgmine kood tagasihelistamise funktsiooni määramiseks ja selle edastamiseks tuvastajale, samuti funktsiooni määramiseks teksti töötlemiseks, kirjutades selle konsooli:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. Tuvastaja alustab kuulamist ainult siis, kui seda selgesõnaliselt käivitatakse. Lisa järgmine kood tuvastamise käivitamiseks. See töötab taustal, seega vajab rakendus ka lõpmatut tsüklit, mis magab, et rakendus töötaks edasi.

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. Käivita see rakendus. Räägi oma mikrofoni ja konsooli kuvatakse tekstiks teisendatud heli.

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    Proovi erinevaid lausetüüpe, samuti lauseid, kus sõnad kõlavad samamoodi, kuid tähendused on erinevad. Näiteks, kui räägid inglise keeles, ütle 'I want to buy two bananas and an apple too' ja märka, kuidas see kasutab õiget 'to', 'two' ja 'too' vastavalt sõna kontekstile, mitte ainult selle kõlale.

> 💁 Selle koodi leiad kaustast [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device).

😀 Sinu kõne tekstiks programm oli edukas!

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.