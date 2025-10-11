<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-10-11T12:22:18+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "et"
}
-->
# Kõne tekstiks - Raspberry Pi

Selles õppetunni osas kirjutad koodi, et muuta salvestatud heli kõne tekstiks, kasutades kõneteenust.

## Saada heli kõneteenusele

Heli saab saata kõneteenusele REST API kaudu. Kõneteenuse kasutamiseks tuleb esmalt taotleda juurdepääsutokenit ja seejärel kasutada seda tokenit REST API-le juurdepääsuks. Need juurdepääsutokenid aeguvad 10 minuti pärast, seega peaks sinu kood neid regulaarselt taotlema, et need oleksid alati ajakohased.

### Ülesanne - juurdepääsutokeni hankimine

1. Ava `smart-timer` projekt oma Raspberry Pi-s.

1. Eemalda funktsioon `play_audio`. Seda pole enam vaja, kuna nutikas taimer ei pea sulle kordama, mida sa ütlesid.

1. Lisa järgmine import `app.py` faili algusesse:

    ```python
    import requests
    ```

1. Lisa järgmine kood `while True` tsükli kohale, et määrata mõned kõneteenuse seaded:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    Asenda `<key>` oma kõneteenuse ressursi API võtmega. Asenda `<location>` asukohaga, mida kasutasid kõneteenuse ressursi loomisel.

    Asenda `<language>` keele lokaadi nimega, milles sa räägid, näiteks `en-GB` inglise keele jaoks või `zn-HK` kantoni keele jaoks. Saad toetatud keelte ja nende lokaadi nimede loendi [Microsofti dokumentatsioonist keele ja hääle toe kohta](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

1. Lisa selle alla järgmine funktsioon, et hankida juurdepääsutoken:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    See kutsub tokenite väljastamise lõpp-punkti, edastades API võtme päises. See kutse tagastab juurdepääsutokeni, mida saab kasutada kõneteenuste kutsumiseks.

1. Lisa selle alla funktsioon, mis konverteerib salvestatud heli kõne tekstiks REST API abil:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. Selle funktsiooni sees seadista REST API URL ja päised:

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

    See koostab URL-i, kasutades kõneteenuse ressursi asukohta. Seejärel täidab päised juurdepääsutokeniga funktsioonist `get_access_token`, samuti helisalvestuse näidissagedusega. Lõpuks määratleb mõned parameetrid, mis edastatakse URL-iga, sisaldades heli keelt.

1. Lisa selle alla järgmine kood, et kutsuda REST API ja saada tagasi tekst:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    See kutsub URL-i ja dekodeerib JSON-väärtuse, mis vastusesse tuleb. Vastuse `RecognitionStatus` väärtus näitab, kas kõne tekstiks teisendamine õnnestus, ja kui see on `Success`, tagastatakse funktsioonist tekst, vastasel juhul tagastatakse tühi string.

1. Määra `while True:` tsükli kohale funktsioon, mis töötleb kõneteenusest tagastatud teksti. See funktsioon prindib teksti praegu lihtsalt konsoolile.

    ```python
    def process_text(text):
        print(text)
    ```

1. Lõpuks asenda `while True` tsüklis `play_audio` funktsiooni kutse `convert_speech_to_text` funktsiooni kutsumisega, edastades teksti `process_text` funktsioonile:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. Käivita kood. Vajuta nuppu ja räägi mikrofoni. Lase nupp lahti, kui oled lõpetanud, ja heli konverteeritakse tekstiks ning prinditakse konsoolile.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    Proovi erinevat tüüpi lauseid, samuti lauseid, kus sõnad kõlavad sarnaselt, kuid tähendused on erinevad. Näiteks, kui räägid inglise keeles, ütle "I want to buy two bananas and an apple too" ja märka, kuidas see kasutab õiget "to", "two" ja "too" vastavalt sõna kontekstile, mitte ainult selle kõlale.

> 💁 Selle koodi leiad [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi) kaustast.

😀 Sinu kõne tekstiks programm oli edukas!

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.