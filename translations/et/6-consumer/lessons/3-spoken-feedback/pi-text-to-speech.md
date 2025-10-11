<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-10-11T12:09:08+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "et"
}
-->
# Teksti kõneks - Raspberry Pi

Selles õppetunni osas kirjutad koodi, et muuta tekst kõneks, kasutades kõneteenust.

## Teksti muutmine kõneks kõneteenuse abil

Teksti saab saata kõneteenusele REST API kaudu, et saada kõne helifailina, mida saab esitada sinu IoT-seadmes. Kõne taotlemisel tuleb määrata hääl, mida kasutada, kuna kõnet saab genereerida mitmesuguste erinevate häältega.

Iga keel toetab erinevaid hääli, ja kõneteenuse vastu saab teha REST-päringu, et saada nimekiri iga keele toetatud häältest.

### Ülesanne - hääle leidmine

1. Ava `smart-timer` projekt VS Code'is.

1. Lisa järgmine kood `say` funktsiooni kohale, et taotleda keele jaoks häälte nimekirja:

    ```python
    def get_voice():
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token()
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        first_voice = next(x for x in voices_json if x['Locale'].lower() == language.lower() and x['VoiceType'] == 'Neural')
        return first_voice['ShortName']
    
    voice = get_voice()
    print(f'Using voice {voice}')
    ```

    See kood määratleb funktsiooni nimega `get_voice`, mis kasutab kõneteenust häälte nimekirja saamiseks. Seejärel leiab funktsioon esimese hääle, mis vastab kasutatavale keelele.

    See funktsioon kutsutakse välja, et salvestada esimene hääl, ja hääle nimi prinditakse konsooli. Seda häält saab taotleda üks kord ja väärtust kasutada iga kord, kui tekst muudetakse kõneks.

    > 💁 Saad täieliku nimekirja toetatud häältest [Microsoft Docs'i keele ja hääle toe dokumentatsioonist](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Kui soovid kasutada konkreetset häält, siis võid selle funktsiooni eemaldada ja hääle nime otse dokumentatsioonist koodi lisada. Näiteks:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### Ülesanne - teksti muutmine kõneks

1. Määra selle alla konstant, mis määrab heliformaadi, mida kõneteenuselt taotleda. Helifaili saab taotleda mitmes erinevas formaadis.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    Kasutatav formaat sõltub sinu riistvarast. Kui saad veateate `Invalid sample rate` helifaili esitamisel, muuda see teiseks väärtuseks. Toetatud väärtuste nimekirja leiad [Teksti kõneks REST API dokumentatsioonist Microsoft Docs'is](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs). Pead kasutama `riff` formaadis heli, ja proovida väärtusi `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` ja `riff-48khz-16bit-mono-pcm`.

1. Määra selle alla funktsioon nimega `get_speech`, mis muudab teksti kõneks, kasutades kõneteenuse REST API-d:

    ```python
    def get_speech(text):
    ```

1. `get_speech` funktsioonis määra URL, mida kutsuda, ja päised, mida edastada:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    See määrab päised, et kasutada genereeritud juurdepääsutokenit, määrab sisu SSML-iks ja määrab vajaliku heliformaadi.

1. Määra selle alla SSML, mida REST API-le saata:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    See SSML määrab keele ja hääle, mida kasutada, koos tekstiga, mida muuta.

1. Lõpuks lisa kood, mis teeb REST-päringu ja tagastab binaarse helifaili andmed:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### Ülesanne - heli esitamine

1. `get_speech` funktsiooni alla määra uus funktsioon, mis esitab REST API päringust tagastatud heli:

    ```python
    def play_speech(speech):
    ```

1. Funktsioonile edastatav `speech` on binaarne helifaili andmestik, mis tagastati REST API-st. Kasuta järgmist koodi, et avada see kui lainefail ja edastada PyAudio-le heli esitamiseks:

    ```python
    def play_speech(speech):
        with wave.open(speech, 'rb') as wave_file:
            stream = audio.open(format=audio.get_format_from_width(wave_file.getsampwidth()),
                                channels=wave_file.getnchannels(),
                                rate=wave_file.getframerate(),
                                output_device_index=speaker_card_number,
                                output=True)

            data = wave_file.readframes(4096)

            while len(data) > 0:
                stream.write(data)
                data = wave_file.readframes(4096)

            stream.stop_stream()
            stream.close()
    ```

    See kood kasutab PyAudio voogu, samamoodi nagu heli salvestamisel. Erinevus seisneb selles, et voog määratakse väljundvooguks, ja andmed loetakse helifailist ning edastatakse voogu.

    Selle asemel, et voogu üksikasju nagu näidissagedus käsitsi määrata, loetakse need helifaili andmetest.

1. Asenda `say` funktsiooni sisu järgmisega:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    See kood muudab teksti kõneks binaarseks helifailiks ja esitab heli.

1. Käivita rakendus ja veendu, et funktsioonirakendus töötab samuti. Määra mõned taimerid, ja kuuled kõnelevat vastust, mis ütleb, et sinu taimer on määratud, ning teist kõnelevat vastust, kui taimer on lõppenud.

    Kui saad veateate `Invalid sample rate`, muuda `playback_format` nagu eespool kirjeldatud.

> 💁 Selle koodi leiad [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi) kaustast.

😀 Sinu taimeriprogramm oli edukas!

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.