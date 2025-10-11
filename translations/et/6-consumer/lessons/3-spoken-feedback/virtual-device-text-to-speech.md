<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-10-11T12:10:34+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "et"
}
-->
# Teksti kõneks - Virtuaalne IoT-seade

Selles õppetunni osas kirjutad koodi, et muuta tekst kõneks, kasutades kõneteenust.

## Teksti muutmine kõneks

Kõneteenuste SDK, mida kasutasid eelmises õppetunnis kõne tekstiks muutmiseks, saab kasutada ka teksti tagasi kõneks muutmiseks. Kõne taotlemisel tuleb määrata hääl, mida kasutada, kuna kõnet saab genereerida mitmesuguste erinevate häältega.

Iga keel toetab erinevaid hääli, ja kõneteenuste SDK-st saad nimekirja iga keele toetatud häältest.

### Ülesanne - teksti muutmine kõneks

1. Ava projekt `smart-timer` VS Code'is ja veendu, et virtuaalne keskkond on terminalis laaditud.

1. Impordi `SpeechSynthesizer` paketist `azure.cognitiveservices.speech`, lisades selle olemasolevatele importidele:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. Loo `say` funktsiooni kohal kõnekonfiguratsioon, mida kasutada kõnesüntesaatoriga:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    See kasutab sama API-võtit, asukohta ja keelt, mida kasutas äratundja.

1. Lisa sellele alla järgmine kood, et saada hääl ja määrata see kõnekonfiguratsioonile:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    See hangib nimekirja kõigist saadaolevatest häältest ja leiab esimese hääle, mis vastab kasutatavale keelele.

    > 💁 Saad täieliku nimekirja toetatud häältest [Microsoft Docs'i keele ja hääle toe dokumentatsioonist](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Kui soovid kasutada konkreetset häält, siis võid selle funktsiooni eemaldada ja määrata hääle nime dokumentatsioonist. Näiteks:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. Uuenda `say` funktsiooni sisu, et genereerida SSML vastuse jaoks:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. Selle alla peata kõnetuvastus, räägi SSML, ja seejärel käivita tuvastus uuesti:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    Tuvastus peatatakse, kui tekst räägitakse, et vältida taimeri käivitamise teate tuvastamist, LUIS-i saatmist ja võimaliku uue taimeri seadistamise tõlgendamist.

    > 💁 Saad seda testida, kommenteerides välja read, mis peatavad ja taaskäivitavad tuvastuse. Sea üks taimer ja võid avastada, et teade seab uue taimeri, mis põhjustab uue teate, mis seab uue taimeri, ja nii edasi lõputult!

1. Käivita rakendus ja veendu, et funktsioonirakendus töötab samuti. Sea mõned taimerid ja kuuled kõne vastust, mis ütleb, et sinu taimer on seadistatud, ning teist kõne vastust, kui taimer on lõppenud.

> 💁 Selle koodi leiad kaustast [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device).

😀 Sinu taimeriprogramm oli edukas!

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.