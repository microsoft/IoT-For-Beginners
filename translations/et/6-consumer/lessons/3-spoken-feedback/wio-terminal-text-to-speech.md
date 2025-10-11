<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-10-11T12:06:58+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "et"
}
-->
# Teksti kõneks - Wio Terminal

Selles õppetunni osas muudad teksti kõneks, et pakkuda suulist tagasisidet.

## Teksti kõneks

Kõneteenuste SDK, mida kasutasid eelmises õppetunnis kõne teksti muundamiseks, saab kasutada ka teksti kõneks muundamiseks.

## Häälte loendi hankimine

Kõne taotlemisel tuleb määrata hääl, mida kasutada, kuna kõnet saab genereerida mitmesuguste erinevate häälte abil. Iga keel toetab erinevaid hääli, ja kõneteenuste SDK-st saab hankida loendi iga keele toetatud häältest. Siin tulevad mängu mikroprotsessorite piirangud - kõneteenuste poolt toetatud häälte loendi päring tagastab JSON-dokumendi, mille suurus on üle 77KB, mis on Wio Terminali jaoks liiga suur, et seda töödelda. Kirjutamise ajal sisaldab täielik loend 215 häält, millest igaüks on määratletud JSON-dokumendiga, näiteks järgmine:

```json
{
    "Name": "Microsoft Server Speech Text to Speech Voice (en-US, AriaNeural)",
    "DisplayName": "Aria",
    "LocalName": "Aria",
    "ShortName": "en-US-AriaNeural",
    "Gender": "Female",
    "Locale": "en-US",
    "StyleList": [
        "chat",
        "customerservice",
        "narration-professional",
        "newscast-casual",
        "newscast-formal",
        "cheerful",
        "empathetic"
    ],
    "SampleRateHertz": "24000",
    "VoiceType": "Neural",
    "Status": "GA"
}
```

See JSON on **Aria** hääle jaoks, millel on mitu hääle stiili. Teksti kõneks muundamisel on vaja ainult lühinime, `en-US-AriaNeural`.

Selle asemel, et mikroprotsessoril kogu loend alla laadida ja dekodeerida, tuleb kirjutada serverivaba kood, et hankida kasutatava keele häälte loend ja kutsuda seda Wio Terminalist. Kood võib seejärel valida sobiva hääle loendist, näiteks esimese leitud hääle.

### Ülesanne - loo serverivaba funktsioon häälte loendi hankimiseks

1. Ava oma `smart-timer-trigger` projekt VS Code'is ja ava terminal, veendudes, et virtuaalne keskkond on aktiveeritud. Kui ei, sulge ja loo terminal uuesti.

1. Ava `local.settings.json` fail ja lisa kõneteenuste API võtme ja asukoha seaded:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    Asenda `<key>` oma kõneteenuste ressursi API võtmega. Asenda `<location>` asukohaga, mida kasutasid kõneteenuste ressursi loomisel.

1. Lisa sellele rakendusele uus HTTP trigger nimega `get-voices`, kasutades järgmist käsku VS Code'i terminalis funktsioonirakenduse projekti juurkataloogis:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    See loob HTTP triggeri nimega `get-voices`.

1. Asenda `get-voices` kausta `__init__.py` faili sisu järgmisega:

    ```python
    import json
    import os
    import requests
    
    import azure.functions as func
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        location = os.environ['SPEECH_LOCATION']
        speech_key = os.environ['SPEECH_KEY']
    
        req_body = req.get_json()
        language = req_body['language']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        voices = filter(lambda x: x['Locale'].lower() == language.lower(), voices_json)
        voices = map(lambda x: x['ShortName'], voices)
    
        return func.HttpResponse(json.dumps(list(voices)), status_code=200)
    ```

    See kood teeb HTTP päringu häälte loendi hankimiseks. Häälte loend on suur JSON-plokk, mis sisaldab hääli kõigi keelte jaoks, seega filtreeritakse välja hääled keele jaoks, mis on päringu kehas määratud, ja lühinimi eraldatakse ning tagastatakse JSON-loendina. Lühinimi on väärtus, mida on vaja teksti kõneks muundamiseks, seega tagastatakse ainult see väärtus.

    > 💁 Filtrit saab vajadusel muuta, et valida ainult soovitud hääled.

    See vähendab andmete suurust 77KB-st (kirjutamise ajal) palju väiksemaks JSON-dokumendiks. Näiteks USA häälte puhul on see 408 baiti.

1. Käivita oma funktsioonirakendus lokaalselt. Seda saab seejärel testida tööriistaga nagu curl samamoodi nagu testisid `text-to-timer` HTTP triggerit. Veendu, et edastad oma keele JSON-kehana:

    ```json
    {
        "language":"<language>"
    }
    ```

    Asenda `<language>` oma keelega, näiteks `en-GB` või `zh-CN`.

> 💁 Selle koodi leiad [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) kaustast.

### Ülesanne - hääle hankimine Wio Terminalist

1. Ava `smart-timer` projekt VS Code'is, kui see pole juba avatud.

1. Ava `config.h` päisefail ja lisa oma funktsioonirakenduse URL:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    Asenda `<URL>` oma funktsioonirakenduse `get-voices` HTTP triggeri URL-iga. See on sama, mis `TEXT_TO_TIMER_FUNCTION_URL` väärtus, välja arvatud funktsiooni nimi, mis on `get-voices` asemel `text-to-timer`.

1. Loo `src` kausta uus fail nimega `text_to_speech.h`. Seda kasutatakse klassi määratlemiseks, mis muundab teksti kõneks.

1. Lisa uue `text_to_speech.h` faili ülaossa järgmised include-direktiivid:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <Seeed_FS.h>
    #include <SD/Seeed_SD.h>
    #include <WiFiClient.h>
    #include <WiFiClientSecure.h>
    
    #include "config.h"
    #include "speech_to_text.h"
    ```

1. Lisa sellele kood, et deklareerida `TextToSpeech` klass, koos instantsiga, mida saab kasutada ülejäänud rakenduses:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. Funktsioonirakenduse kutsumiseks tuleb deklareerida WiFi klient. Lisa see klassi `private` sektsiooni:

    ```cpp
    WiFiClient _client;
    ```

1. `private` sektsiooni lisa väli valitud hääle jaoks:

    ```cpp
    String _voice;
    ```

1. `public` sektsiooni lisa `init` funktsioon, mis hangib esimese hääle:

    ```cpp
    void init()
    {
    }
    ```

1. Häälte hankimiseks tuleb funktsioonirakendusele saata JSON-dokument keelega. Lisa järgmine kood `init` funktsiooni, et luua see JSON-dokument:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. Seejärel loo `HTTPClient` ja kasuta seda funktsioonirakenduse kutsumiseks, postitades JSON-dokumendi:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Lisa sellele kood, et kontrollida vastusekoodi, ja kui see on 200 (õnnestumine), eralda häälte loend, hankides loendist esimese:

    ```cpp
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonArray obj = doc.as<JsonArray>();
        _voice = obj[0].as<String>();

        Serial.print("Using voice ");
        Serial.println(_voice);
    }
    else
    {
        Serial.print("Failed to get voices - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. Pärast seda lõpeta HTTP kliendi ühendus:

    ```cpp
    httpClient.end();
    ```

1. Ava `main.cpp` fail ja lisa ülaossa järgmine include-direktiiv, et lisada see uus päisefail:

    ```cpp
    #include "text_to_speech.h"
    ```

1. `setup` funktsioonis, `speechToText.init();` kõne all, lisa järgmine, et algatada `TextToSpeech` klass:

    ```cpp
    textToSpeech.init();
    ```

1. Koosta see kood, laadi see üles oma Wio Terminali ja testi seda läbi seeriamonitori. Veendu, et sinu funktsioonirakendus töötab.

    Näed funktsioonirakendusest tagastatud häälte loendit koos valitud häälega.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    ["en-US-JennyNeural", "en-US-JennyMultilingualNeural", "en-US-GuyNeural", "en-US-AriaNeural", "en-US-AmberNeural", "en-US-AnaNeural", "en-US-AshleyNeural", "en-US-BrandonNeural", "en-US-ChristopherNeural", "en-US-CoraNeural", "en-US-ElizabethNeural", "en-US-EricNeural", "en-US-JacobNeural", "en-US-MichelleNeural", "en-US-MonicaNeural", "en-US-AriaRUS", "en-US-BenjaminRUS", "en-US-GuyRUS", "en-US-ZiraRUS"]
    Using voice en-US-JennyNeural
    Ready.
    ```

## Teksti muundamine kõneks

Kui sul on hääl, mida kasutada, saab seda kasutada teksti kõneks muundamiseks. Samad mälupiirangud, mis kehtivad häälte puhul, kehtivad ka kõne teksti muundamisel, seega tuleb kõne salvestada SD-kaardile, et seda saaks ReSpeakeri kaudu esitada.

> 💁 Selle projekti varasemates õppetundides kasutasid mikrofoni kaudu salvestatud kõne salvestamiseks välkmälu. Selles õppetunnis kasutatakse SD-kaarti, kuna Seeed audio teekide abil on lihtsam heli sellest esitada.

Samuti tuleb arvestada teise piiranguga, mis puudutab kõneteenuse saadaval olevat helimaterjali ja Wio Terminali toetatud formaate. Erinevalt täisväärtuslikest arvutitest on mikroprotsessorite heliteegid väga piiratud toetatud heliformaatide osas. Näiteks Seeed Arduino Audio teek, mis suudab ReSpeakeri kaudu heli esitada, toetab ainult heli sagedusega 44.1KHz. Azure kõneteenused võivad pakkuda heli mitmes formaadis, kuid ükski neist ei kasuta seda sagedust, vaid ainult 8KHz, 16KHz, 24KHz ja 48KHz. See tähendab, et heli tuleb ümber proovida sagedusele 44.1KHz, mis vajaks rohkem ressursse, kui Wio Terminalil on, eriti mälu.

Kui on vaja andmeid sellisel viisil manipuleerida, on sageli parem kasutada serverivaba koodi, eriti kui andmed pärinevad veebikõnest. Wio Terminal saab kutsuda serverivaba funktsiooni, edastades teksti, mida muundada, ja serverivaba funktsioon saab nii kõneteenust kutsuda teksti kõneks muundamiseks kui ka heli ümber proovida vajalikule sagedusele. Seejärel saab see tagastada heli vormis, mida Wio Terminal vajab, et seda SD-kaardile salvestada ja ReSpeakeri kaudu esitada.

### Ülesanne - loo serverivaba funktsioon teksti kõneks muundamiseks

1. Ava oma `smart-timer-trigger` projekt VS Code'is ja ava terminal, veendudes, et virtuaalne keskkond on aktiveeritud. Kui ei, sulge ja loo terminal uuesti.

1. Lisa sellele rakendusele uus HTTP trigger nimega `text-to-speech`, kasutades järgmist käsku VS Code'i terminalis funktsioonirakenduse projekti juurkataloogis:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    See loob HTTP triggeri nimega `text-to-speech`.

1. [librosa](https://librosa.org) Pip pakett sisaldab funktsioone heli ümberproovimiseks, seega lisa see `requirements.txt` faili:

    ```sh
    librosa
    ```

    Kui see on lisatud, installi Pip paketid, kasutades järgmist käsku VS Code'i terminalis:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ Kui kasutad Linuxi, sealhulgas Raspberry Pi OS-i, võib olla vajalik installida `libsndfile` järgmise käsuga:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. Teksti kõneks muundamiseks ei saa kasutada kõneteenuste API võtit otse, selle asemel tuleb taotleda juurdepääsuluba, kasutades API võtit juurdepääsuloa taotluse autentimiseks. Ava `text-to-speech` kausta `__init__.py` fail ja asenda kogu selle sisu järgmisega:

    ```python
    import io
    import os
    import requests
    
    import librosa
    import soundfile as sf
    import azure.functions as func
    
    location = os.environ['SPEECH_LOCATION']
    speech_key = os.environ['SPEECH_KEY']
    
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    See määratleb konstandid asukoha ja kõnevõtme jaoks, mis loetakse seadistustest. Seejärel määratleb `get_access_token` funktsiooni, mis hangib juurdepääsuloa kõneteenuse jaoks.

1. Lisa sellele koodile järgmine:

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'

    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        language = req_body['language']
        voice = req_body['voice']
        text = req_body['text']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    
        ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
        ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
        ssml += text
        ssml += '</voice>'
        ssml += '</speak>'
    
        response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    
        raw_audio, sample_rate = librosa.load(io.BytesIO(response.content), sr=48000)
        resampled = librosa.resample(raw_audio, sample_rate, 44100)
        
        output_buffer = io.BytesIO()
        sf.write(output_buffer, resampled, 44100, 'PCM_16', format='wav')
        output_buffer.seek(0)
    
        return func.HttpResponse(output_buffer.read(), status_code=200)
    ```

    See määratleb HTTP triggeri, mis muundab teksti kõneks. See eraldab JSON-kehast teksti, keele ja hääle, koostab SSML-i kõne taotlemiseks, seejärel kutsub vastavat REST API-d, autentides juurdepääsuloa abil. See REST API kõne tagastab heli kodeeritud 16-bitise, 48KHz mono WAV-failina, mida määratleb `playback_format` väärtus, mis saadetakse REST API kõnesse.

    Seejärel proovib `librosa` heli ümber sageduselt 48KHz sagedusele 44.1KHz, seejärel salvestatakse see heli binaarsesse puhvrisse, mis seejärel tagastatakse.

1. Käivita oma funktsioonirakendus lokaalselt või juuruta see pilve. Seda saab seejärel testida tööriistaga nagu curl samamoodi nagu testisid `text-to-timer` HTTP triggerit. Veendu, et edastad keele, hääle ja teksti JSON-kehana:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    Asenda `<language>` oma keelega, näiteks `en-GB` või `zh-CN`. Asenda `<voice>` häälega, mida soovid kasutada. Asenda `<text>` tekstiga, mida soovid kõneks muundada. Saad väljundi salvestada faili ja esitada seda mis tahes helimängijaga, mis suudab esitada WAV-faile.

    Näiteks, et muundada "Hello" kõneks, kasutades USA inglise keelt Jenny Neural häälega, kui funktsioonirakendus töötab lokaalselt, saad kasutada järgmist curl käsku:

    ```sh
    curl -X GET 'http://localhost:7071/api/text-to-speech' \
         -H 'Content-Type: application/json' \
         -o hello.wav \
         -d '{
           "language":"en-US",
           "voice": "en-US-JennyNeural",
           "text": "Hello"
         }'
    ```

    See salvestab heli `hello.wav` faili praeguses kataloogis.

> 💁 Selle koodi leiad [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) kaustast.

### Ülesanne - kõne hankimine Wio Terminalist

1. Ava `smart-timer` projekt VS Code'is, kui see pole juba avatud.

1. Ava `config.h` päisefail ja lisa oma funktsioonirakenduse URL:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    Asenda `<URL>` oma funktsioonirakenduse `text-to-speech` HTTP triggeri URL-iga. See on sama, mis `TEXT_TO_TIMER_FUNCTION_URL` väärtus, välja arvatud funktsiooni nimi, mis on `text-to-speech` asemel `text-to-timer`.

1. Ava `text_to_speech.h` päisefail ja lisa järgmine meetod `TextToSpeech` klassi `public` sektsiooni:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. `convertTextToSpeech` meetodisse lisa järgmine kood, et luua JSON, mida funktsioonirakendusele saata:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    See kirjutab keele, hääle ja teksti JSON-dokumenti, seejärel serialiseerib selle stringiks.

1. Selle alla lisa järgmine kood funktsioonirakenduse kutsumiseks:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    See loob HTTPClienti, seejärel teeb POST-päringu JSON-dokumendiga teksti kõneks HTTP triggerile.

1. Kui kõne õnnestub, saab funktsioonirakenduselt tagastatud binaarandmeid voogesitada failiks SD-kaardil. Lisa järgmine kood selleks:

    ```cpp
    if (httpResponseCode == 200)
    {            
        File wav_file = SD.open("SPEECH.WAV", FILE_WRITE);
        httpClient.writeToStream(&wav_file);
        wav_file.close();
    }
    else
    {
        Serial.print("Failed to get speech - error ");
        Serial.println(httpResponseCode);
    }
    ```

    See kood kontrollib vastust ja kui see on 200 (õnnestumine), voogesitatakse binaarandmed faili SD-kaardi juurkataloogis nimega `SPEECH.WAV`.

1. Selle meetodi lõpus sulge HTTP ühendus:

    ```cpp
    httpClient.end();
    ```

1. Teksti, mida tuleb ette lugeda, saab nüüd muuta heliks. Failis `main.cpp` lisage järgmine rida `say` funktsiooni lõppu, et muuta tekst heliks:

    ```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### Ülesanne - mängi heli oma Wio Terminalis

**Tulekul peagi**

## Funktsioonirakenduse pilvele juurutamine

Funktsioonirakenduse kohalikult käivitamise põhjus on see, et Linuxi `librosa` Pip pakett sõltub teegist, mida vaikimisi ei installita ja mis tuleb enne funktsioonirakenduse käivitamist installida. Funktsioonirakendused on serverivabad - puuduvad serverid, mida saaks ise hallata, seega pole võimalik seda teeki eelnevalt installida.

Selle asemel tuleb funktsioonirakendus juurutada Docker konteineri abil. See konteiner juurutatakse pilve poolt alati, kui on vaja käivitada uus funktsioonirakenduse eksemplar (näiteks kui nõudlus ületab olemasolevaid ressursse või kui funktsioonirakendust pole mõnda aega kasutatud ja see on suletud).

Juhised funktsioonirakenduse seadistamiseks ja Dockeriga juurutamiseks leiate [Microsoft Docs'i Linuxi kohandatud konteineri dokumentatsioonist](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python).

Kui see on juurutatud, saate oma Wio Terminali koodi muuta, et pääseda sellele funktsioonile ligi:

1. Lisage Azure Functions sertifikaat faili `config.h`:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Muutke kõik `<WiFiClient.h>` viited `<WiFiClientSecure.h>` viideteks.

1. Muutke kõik `WiFiClient` väljad `WiFiClientSecure` väljadeks.

1. Igas klassis, millel on `WiFiClientSecure` väli, lisage konstruktor ja seadistage sertifikaat selles konstruktoris:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.