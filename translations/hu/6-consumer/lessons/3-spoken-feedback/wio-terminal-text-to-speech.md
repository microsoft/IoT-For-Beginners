<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-27T21:11:05+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "hu"
}
-->
# Szöveg beszéddé alakítása - Wio Terminal

Ebben a leckében a szöveget beszéddé alakítjuk, hogy hangos visszajelzést kapjunk.

## Szöveg beszéddé alakítása

Az előző leckében használt beszédszolgáltatások SDK, amelyet a beszéd szöveggé alakítására használtunk, lehetővé teszi a szöveg visszaalakítását beszéddé.

## Hangok listájának lekérése

Amikor beszédet kérünk, meg kell adnunk a használni kívánt hangot, mivel a beszéd különböző hangokkal generálható. Minden nyelvhez többféle hang érhető el, és a beszédszolgáltatások SDK segítségével lekérhetjük az egyes nyelvekhez támogatott hangok listáját. Itt lépnek előtérbe a mikrokontrollerek korlátai - a beszédszolgáltatások által támogatott hangok listájának lekérése egy több mint 77KB méretű JSON dokumentum, amely túl nagy ahhoz, hogy a Wio Terminal feldolgozza. A cikk írásakor a teljes lista 215 hangot tartalmaz, mindegyik egy JSON dokumentumban van definiálva, például az alábbi módon:

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

Ez a JSON az **Aria** hanghoz tartozik, amely több hangstílussal rendelkezik. A szöveg beszéddé alakításához csak a rövid név szükséges, `en-US-AriaNeural`.

Ahelyett, hogy letöltenénk és dekódolnánk ezt az egész listát a mikrokontrolleren, további szerver nélküli kódot kell írnunk, hogy lekérjük az általunk használt nyelvhez tartozó hangok listáját, és ezt a Wio Terminalról hívjuk meg. A kódunk ezután kiválaszthat egy megfelelő hangot a listából, például az elsőt, amit talál.

### Feladat - szerver nélküli funkció létrehozása a hangok listájának lekéréséhez

1. Nyisd meg a `smart-timer-trigger` projektet a VS Code-ban, és nyisd meg a terminált, ügyelve arra, hogy a virtuális környezet aktiválva legyen. Ha nem, állítsd le és hozd létre újra a terminált.

1. Nyisd meg a `local.settings.json` fájlt, és adj hozzá beállításokat a beszéd API kulcsához és helyéhez:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    Cseréld ki `<key>`-t a beszédszolgáltatás erőforrásának API kulcsára. Cseréld ki `<location>`-t arra a helyre, amelyet a beszédszolgáltatás erőforrás létrehozásakor használtál.

1. Adj hozzá egy új HTTP trigger-t az alkalmazáshoz `get-voices` néven az alábbi parancs segítségével a VS Code termináljában, a funkciók alkalmazás projekt gyökérmappájában:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    Ez létrehoz egy `get-voices` nevű HTTP trigger-t.

1. Cseréld ki a `get-voices` mappában található `__init__.py` fájl tartalmát az alábbiakra:

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

    Ez a kód HTTP kérést küld az endpointnak a hangok lekéréséhez. A hangok listája egy nagy JSON blokk, amely az összes nyelvhez tartozó hangokat tartalmazza, így a kérésben megadott nyelvhez tartozó hangok kiszűrésre kerülnek, majd a rövid név kinyerésre és JSON listaként visszaküldésre kerül. A rövid név az érték, amely szükséges a szöveg beszéddé alakításához, így csak ez az érték kerül visszaküldésre.

    > 💁 A szűrőt szükség szerint módosíthatod, hogy csak azokat a hangokat válaszd ki, amelyeket szeretnél.

    Ez csökkenti az adatok méretét 77KB-ról (a cikk írásakor) egy sokkal kisebb JSON dokumentumra. Például az amerikai hangok esetében ez 408 bájt.

1. Futtasd az alkalmazás funkcióit helyben. Ezután egy olyan eszközzel, mint a curl, meghívhatod ezt ugyanúgy, ahogy a `text-to-timer` HTTP trigger-t tesztelted. Ügyelj arra, hogy a nyelvet JSON testként add meg:

    ```json
    {
        "language":"<language>"
    }
    ```

    Cseréld ki `<language>`-t a nyelvedre, például `en-GB` vagy `zh-CN`.

> 💁 Ezt a kódot megtalálhatod a [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) mappában.

### Feladat - hang lekérése a Wio Terminalról

1. Nyisd meg a `smart-timer` projektet a VS Code-ban, ha még nincs megnyitva.

1. Nyisd meg a `config.h` fejlécfájlt, és add hozzá az alkalmazás funkció URL-jét:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    Cseréld ki `<URL>`-t a `get-voices` HTTP trigger URL-jére az alkalmazás funkcióban. Ez ugyanaz lesz, mint a `TEXT_TO_TIMER_FUNCTION_URL` értéke, kivéve, hogy a funkció neve `get-voices` lesz `text-to-timer` helyett.

1. Hozz létre egy új fájlt a `src` mappában `text_to_speech.h` néven. Ez arra szolgál, hogy definiáljunk egy osztályt a szöveg beszéddé alakításához.

1. Add hozzá az alábbi include direktívákat az új `text_to_speech.h` fájl tetejéhez:

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

1. Add hozzá az alábbi kódot, hogy deklaráld a `TextToSpeech` osztályt, valamint egy példányt, amelyet az alkalmazás többi részében használhatsz:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. Az alkalmazás funkció meghívásához deklarálnod kell egy WiFi klienst. Add hozzá az alábbiakat az osztály `private` szekciójához:

    ```cpp
    WiFiClient _client;
    ```

1. A `private` szekcióban adj hozzá egy mezőt a kiválasztott hanghoz:

    ```cpp
    String _voice;
    ```

1. A `public` szekcióhoz adj hozzá egy `init` függvényt, amely lekéri az első hangot:

    ```cpp
    void init()
    {
    }
    ```

1. A hangok lekéréséhez egy JSON dokumentumot kell küldeni az alkalmazás funkciónak a nyelvvel. Add hozzá az alábbi kódot az `init` függvényhez, hogy létrehozd ezt a JSON dokumentumot:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. Ezután hozz létre egy `HTTPClient`-et, majd használd ezt az alkalmazás funkció meghívására a hangok lekéréséhez, a JSON dokumentumot küldve:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Ezután adj hozzá kódot a válaszkód ellenőrzéséhez, és ha az 200 (sikeres), akkor a hangok listáját kinyerjük, és az elsőt választjuk ki a listából:

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

1. Ezután zárd le a HTTP kliens kapcsolatot:

    ```cpp
    httpClient.end();
    ```

1. Nyisd meg a `main.cpp` fájlt, és add hozzá az alábbi include direktívát a tetejére, hogy beilleszd ezt az új fejlécfájlt:

    ```cpp
    #include "text_to_speech.h"
    ```

1. A `setup` függvényben, a `speechToText.init();` hívás alatt add hozzá az alábbiakat a `TextToSpeech` osztály inicializálásához:

    ```cpp
    textToSpeech.init();
    ```

1. Fordítsd le a kódot, töltsd fel a Wio Terminalra, és teszteld a soros monitoron keresztül. Ügyelj arra, hogy az alkalmazás funkció fut.

    Látni fogod az alkalmazás funkció által visszaküldött elérhető hangok listáját, valamint a kiválasztott hangot.

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

## Szöveg beszéddé alakítása

Miután van egy használható hang, azzal a szöveg beszéddé alakítható. Ugyanazok a memória korlátok érvényesek a beszéd szöveggé alakításánál, mint a szöveg beszéddé alakításánál, ezért a beszédet SD kártyára kell írni, hogy lejátszható legyen a ReSpeaker-en keresztül.

> 💁 A projekt korábbi leckéiben flash memóriát használtál a mikrofonról rögzített beszéd tárolására. Ebben a leckében SD kártyát használunk, mivel könnyebb hangot lejátszani róla a Seeed audio könyvtárak segítségével.

Van egy másik korlát is, amelyet figyelembe kell venni: a beszédszolgáltatás által biztosított audio adatok és a Wio Terminal által támogatott formátumok. A teljes számítógépekkel ellentétben a mikrokontrollerek audio könyvtárai nagyon korlátozottak lehetnek az általuk támogatott audio formátumokban. Például a Seeed Arduino Audio könyvtár, amely hangot tud lejátszani a ReSpeaker-en keresztül, csak 44.1KHz mintavételi frekvenciájú hangot támogat. Az Azure beszédszolgáltatások számos formátumban tudnak hangot biztosítani, de egyikük sem használja ezt a mintavételi frekvenciát, csak 8KHz, 16KHz, 24KHz és 48KHz érhető el. Ez azt jelenti, hogy a hangot újra kell mintavételezni 44.1KHz-re, ami több erőforrást igényelne, mint amennyit a Wio Terminal biztosítani tud, különösen memóriát.

Amikor ilyen adatokat kell manipulálni, gyakran jobb szerver nélküli kódot használni, különösen, ha az adatokat webes híváson keresztül kapjuk. A Wio Terminal meghívhat egy szerver nélküli funkciót, amely átadja az átalakítandó szöveget, és a szerver nélküli funkció nemcsak a beszédszolgáltatást hívhatja meg a szöveg beszéddé alakításához, hanem újra mintavételezheti a hangot a szükséges mintavételi frekvenciára. Ezután visszaküldheti a hangot olyan formában, amelyet a Wio Terminal az SD kártyára menthet, és lejátszhat a ReSpeaker-en keresztül.

### Feladat - szerver nélküli funkció létrehozása a szöveg beszéddé alakításához

1. Nyisd meg a `smart-timer-trigger` projektet a VS Code-ban, és nyisd meg a terminált, ügyelve arra, hogy a virtuális környezet aktiválva legyen. Ha nem, állítsd le és hozd létre újra a terminált.

1. Adj hozzá egy új HTTP trigger-t az alkalmazáshoz `text-to-speech` néven az alábbi parancs segítségével a VS Code termináljában, a funkciók alkalmazás projekt gyökérmappájában:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    Ez létrehoz egy `text-to-speech` nevű HTTP trigger-t.

1. A [librosa](https://librosa.org) Pip csomag rendelkezik funkciókkal a hang újra mintavételezéséhez, ezért add hozzá ezt a `requirements.txt` fájlhoz:

    ```sh
    librosa
    ```

    Miután ezt hozzáadtad, telepítsd a Pip csomagokat az alábbi parancs segítségével a VS Code termináljában:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ Ha Linuxot használsz, beleértve a Raspberry Pi OS-t, előfordulhat, hogy telepítened kell a `libsndfile`-t az alábbi parancs segítségével:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. A szöveg beszéddé alakításához nem használhatod közvetlenül a beszéd API kulcsot, hanem hozzáférési tokent kell kérned, az API kulcsot használva a hozzáférési token kérés hitelesítéséhez. Nyisd meg a `text-to-speech` mappában található `__init__.py` fájlt, és cseréld ki az összes kódot az alábbiakra:

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

    Ez konstansokat definiál a beállításokból olvasott hely és beszéd kulcs számára. Ezután definiálja a `get_access_token` függvényt, amely hozzáférési tokent kér a beszédszolgáltatáshoz.

1. Ez alatt a kód alatt add hozzá az alábbiakat:

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

    Ez definiálja a szöveget beszéddé alakító HTTP trigger-t. Kinyeri az átalakítandó szöveget, a nyelvet és a hangot a kérés JSON testéből, SSML-t épít a beszéd kéréséhez, majd meghívja a megfelelő REST API-t, amelyet a hozzáférési tokennel hitelesít. Ez a REST API hívás 16 bites, 48KHz mono WAV fájl formátumban kódolt hangot ad vissza, amelyet a `playback_format` értéke határoz meg, amelyet a REST API hívásnak küldünk.

    Ezután a `librosa` újra mintavételezi a hangot 48KHz-ről 44.1KHz-re, majd ezt a hangot egy bináris pufferbe menti, amelyet visszaküld.

1. Futtasd az alkalmazás funkcióit helyben, vagy telepítsd a felhőbe. Ezután egy olyan eszközzel, mint a curl, meghívhatod ezt ugyanúgy, ahogy a `text-to-timer` HTTP trigger-t tesztelted. Ügyelj arra, hogy a nyelvet, hangot és szöveget JSON testként add meg:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    Cseréld ki `<language>`-t a nyelvedre, például `en-GB` vagy `zh-CN`. Cseréld ki `<voice>`-t a használni kívánt hangra. Cseréld ki `<text>`-et az átalakítandó szövegre. Az outputot fájlba mentheted, és lejátszhatod bármely WAV fájlokat lejátszó audio lejátszóval.

    Például, ha az "Hello" szöveget szeretnéd beszéddé alakítani amerikai angol nyelven a Jenny Neural hanggal, az alkalmazás funkció helyi futtatásával az alábbi curl parancsot használhatod:

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

    Ez a hangot a `hello.wav` fájlba menti az aktuális könyvtárban.

> 💁 Ezt a kódot megtalálhatod a [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) mappában.

### Feladat - beszéd lekérése a Wio Terminalról

1. Nyisd meg a `smart-timer` projektet a VS Code-ban, ha még nincs megnyitva.

1. Nyisd meg a `config.h` fejlécfájlt, és add hozzá az alkalmazás funkció URL-jét:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    Cseréld ki `<URL>`-t a `text-to-speech` HTTP trigger URL-jére az alkalmazás funkcióban. Ez ugyanaz lesz, mint a `TEXT_TO_TIMER_FUNCTION_URL` értéke, kivéve, hogy a funkció neve `text-to-speech` lesz `text-to-timer` helyett.

1. Nyisd meg a `text_to_speech.h` fejlécfájlt, és add hozzá az alábbi metódust a `TextToSpeech` osztály `public` szekciójához:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. A `convertTextToSpeech` metódushoz add hozzá az alábbi kódot, hogy létrehozd a JSON-t, amelyet az alkalmazás funkciónak küldesz:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Ez a nyelvet, hangot és szöveget írja a JSON dokumentumba, majd sorosítja azt egy sztringgé.

1. Ez alatt add hozzá az alábbi kódot az alkalmazás funkció meghívásához:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Ez létrehoz egy HTTPClient-et, majd POST kérést küld a JSON dokumentummal a szöveget beszéddé alakító HTTP trigger-nek.

1. Ha a hívás sikeres, az alkalmazás funkció által visszaküldött nyers bináris adatokat egy fájlba lehet streamelni az SD kártyán. Add hozzá az alábbi kódot ennek végrehajtásához:

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

    Ez a kód ellenőrzi a választ, és ha az 200 (sikeres), a bináris adatokat az SD kártya gyökérkönyvtárában
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### Feladat - hang lejátszása a Wio Terminal eszközön

**Hamarosan**

## Funkcióalkalmazás telepítése a felhőbe

Azért futtatjuk a funkcióalkalmazást helyben, mert a `librosa` Pip csomagnak Linuxon van egy függősége egy olyan könyvtárra, amely alapértelmezetten nincs telepítve, és telepíteni kell, mielőtt a funkcióalkalmazás futtatható lenne. A funkcióalkalmazások szervermentesek - nincsenek olyan szerverek, amelyeket saját magad kezelhetnél, így nincs lehetőség előzetesen telepíteni ezt a könyvtárat.

A megoldás az, hogy a funkcióalkalmazást egy Docker konténer segítségével telepítjük. Ezt a konténert a felhő indítja el, amikor új példányt kell létrehozni a funkcióalkalmazásból (például amikor a kereslet meghaladja a rendelkezésre álló erőforrásokat, vagy ha a funkcióalkalmazás egy ideje nem volt használatban és leállt).

Az utasításokat a funkcióalkalmazás létrehozásához és Docker segítségével történő telepítéséhez megtalálhatod a [Linuxon egyedi konténer használatával funkció létrehozása dokumentációban a Microsoft Docs oldalán](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python).

Miután ez telepítve lett, átviheted a Wio Terminal kódodat, hogy hozzáférjen ehhez a funkcióhoz:

1. Add hozzá az Azure Functions tanúsítványt a `config.h` fájlhoz:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Módosítsd az összes `<WiFiClient.h>` hivatkozást `<WiFiClientSecure.h>`-re.

1. Módosítsd az összes `WiFiClient` mezőt `WiFiClientSecure`-re.

1. Minden olyan osztályban, amelynek van `WiFiClientSecure` mezője, adj hozzá egy konstruktort, és állítsd be a tanúsítványt ebben a konstruktorban:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.