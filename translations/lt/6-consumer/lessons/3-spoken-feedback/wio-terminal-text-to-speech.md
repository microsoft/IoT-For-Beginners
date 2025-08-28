<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-28T19:19:28+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "lt"
}
-->
# Teksto pavertimas į kalbą - Wio Terminal

Šioje pamokos dalyje tekstą paversite kalba, kad būtų galima pateikti garsinį atsiliepimą.

## Teksto pavertimas į kalbą

Kalbos paslaugų SDK, kurį naudojote paskutinėje pamokoje tekstui paversti į kalbą, taip pat gali būti naudojamas tekstui paversti atgal į kalbą.

## Gauti balsų sąrašą

Prašant kalbos, reikia nurodyti balsą, kurį norite naudoti, nes kalba gali būti generuojama naudojant įvairius balsus. Kiekviena kalba palaiko skirtingus balsus, o kalbos paslaugų SDK leidžia gauti palaikomų balsų sąrašą kiekvienai kalbai. Čia atsiranda mikrovaldiklių apribojimai - užklausa, skirta gauti balsų sąrašą, yra JSON dokumentas, kurio dydis viršija 77 KB, per didelis, kad būtų apdorotas Wio Terminal. Rašymo metu visas sąrašas apima 215 balsų, kiekvienas apibrėžtas JSON dokumentu, panašiu į šį:

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

Šis JSON dokumentas skirtas **Aria** balsui, kuris turi kelis balso stilius. Viskas, ko reikia tekstui paversti į kalbą, yra trumpasis pavadinimas, `en-US-AriaNeural`.

Užuot atsisiuntę ir dekodavę visą šį sąrašą mikrovaldiklyje, turėsite parašyti daugiau serverless kodo, kad gautumėte balsų sąrašą kalbai, kurią naudojate, ir iškviestumėte tai iš savo Wio Terminal. Jūsų kodas gali pasirinkti tinkamą balsą iš sąrašo, pavyzdžiui, pirmąjį, kurį randa.

### Užduotis - sukurti serverless funkciją balsų sąrašui gauti

1. Atidarykite savo `smart-timer-trigger` projektą VS Code ir terminale įsitikinkite, kad virtuali aplinka yra aktyvuota. Jei ne, uždarykite ir iš naujo sukurkite terminalą.

1. Atidarykite `local.settings.json` failą ir pridėkite nustatymus kalbos API raktui ir vietai:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    Pakeiskite `<key>` į savo kalbos paslaugos resurso API raktą. Pakeiskite `<location>` į vietą, kurią naudojote kurdami kalbos paslaugos resursą.

1. Pridėkite naują HTTP trigerį šiai programai, pavadintą `get-voices`, naudodami šią komandą iš VS Code terminalo, esančio funkcijų programos projekto šakniniame aplanke:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    Tai sukurs HTTP trigerį, pavadintą `get-voices`.

1. Pakeiskite `get-voices` aplanke esančio `__init__.py` failo turinį šiuo kodu:

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

    Šis kodas atlieka HTTP užklausą į galinį tašką, kad gautų balsus. Balsų sąrašas yra didelis JSON blokas su balsais visoms kalboms, todėl balsai, atitinkantys užklausos kūne nurodytą kalbą, yra filtruojami, tada trumpasis pavadinimas išgaunamas ir grąžinamas kaip JSON sąrašas. Trumpasis pavadinimas yra vertė, reikalinga tekstui paversti į kalbą, todėl grąžinama tik ši vertė.

    > 💁 Galite pakeisti filtrą, jei reikia, kad pasirinktumėte tik norimus balsus.

    Tai sumažina duomenų dydį nuo 77 KB (rašymo metu) iki daug mažesnio JSON dokumento. Pavyzdžiui, JAV balsams tai yra 408 baitai.

1. Vietoje paleiskite savo funkcijų programą. Tada galite ją iškviesti naudodami tokį įrankį kaip curl, taip pat kaip testavote savo `text-to-timer` HTTP trigerį. Įsitikinkite, kad perduodate savo kalbą kaip JSON kūną:

    ```json
    {
        "language":"<language>"
    }
    ```

    Pakeiskite `<language>` į savo kalbą, pavyzdžiui, `en-GB` arba `zh-CN`.

> 💁 Šį kodą galite rasti [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) aplanke.

### Užduotis - gauti balsą iš savo Wio Terminal

1. Atidarykite `smart-timer` projektą VS Code, jei jis dar neatidarytas.

1. Atidarykite `config.h` antraštės failą ir pridėkite savo funkcijų programos URL:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    Pakeiskite `<URL>` į `get-voices` HTTP trigerio URL savo funkcijų programoje. Tai bus tas pats kaip `TEXT_TO_TIMER_FUNCTION_URL` reikšmė, išskyrus funkcijos pavadinimą `get-voices` vietoj `text-to-timer`.

1. Sukurkite naują failą `src` aplanke, pavadintą `text_to_speech.h`. Jis bus naudojamas klasei apibrėžti, kuri konvertuos tekstą į kalbą.

1. Pridėkite šiuos įtraukimo direktyvas į naujo `text_to_speech.h` failo viršų:

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

1. Pridėkite šį kodą žemiau, kad deklaruotumėte `TextToSpeech` klasę, kartu su egzemplioriumi, kuris gali būti naudojamas likusioje programoje:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. Norėdami iškviesti savo funkcijų programą, turite deklaruoti WiFi klientą. Pridėkite šį kodą į klasės `private` sekciją:

    ```cpp
    WiFiClient _client;
    ```

1. `private` sekcijoje pridėkite lauką pasirinktam balsui:

    ```cpp
    String _voice;
    ```

1. `public` sekcijoje pridėkite `init` funkciją, kuri gaus pirmąjį balsą:

    ```cpp
    void init()
    {
    }
    ```

1. Norėdami gauti balsus, JSON dokumentas turi būti išsiųstas funkcijų programai su kalba. Pridėkite šį kodą į `init` funkciją, kad sukurtumėte šį JSON dokumentą:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. Toliau sukurkite `HTTPClient`, tada naudokite jį funkcijų programos iškvietimui, kad gautumėte balsus, siunčiant JSON dokumentą:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Žemiau pridėkite kodą, kad patikrintumėte atsakymo kodą, ir jei jis yra 200 (sėkmė), išgaukite balsų sąrašą, gaudami pirmąjį iš sąrašo:

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

1. Po to užbaikite HTTP kliento ryšį:

    ```cpp
    httpClient.end();
    ```

1. Atidarykite `main.cpp` failą ir pridėkite šią įtraukimo direktyvą viršuje, kad įtrauktumėte šį naują antraštės failą:

    ```cpp
    #include "text_to_speech.h"
    ```

1. `setup` funkcijoje, po `speechToText.init();` iškvietimo, pridėkite šį kodą, kad inicializuotumėte `TextToSpeech` klasę:

    ```cpp
    textToSpeech.init();
    ```

1. Sukurkite šį kodą, įkelkite jį į savo Wio Terminal ir išbandykite per serijinį monitorių. Įsitikinkite, kad jūsų funkcijų programa veikia.

    Pamatysite funkcijų programos grąžintą galimų balsų sąrašą kartu su pasirinktu balsu.

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

## Teksto pavertimas į kalbą

Kai turite balsą, kurį norite naudoti, jis gali būti naudojamas tekstui paversti į kalbą. Tie patys atminties apribojimai, kurie taikomi balsams, taip pat taikomi tekstui paversti į kalbą, todėl kalbą reikės įrašyti į SD kortelę, kad ją būtų galima atkurti per ReSpeaker.

> 💁 Ankstesnėse šio projekto pamokose naudojote flash atmintį, kad išsaugotumėte mikrofono užfiksuotą kalbą. Šioje pamokoje naudojama SD kortelė, nes ją lengviau naudoti garsui atkurti naudojant Seeed garso bibliotekas.

Taip pat yra dar vienas apribojimas, kurį reikia apsvarstyti - galimi garso duomenys iš kalbos paslaugos ir formatų, kuriuos palaiko Wio Terminal, suderinamumas. Skirtingai nei pilni kompiuteriai, mikrovaldiklių garso bibliotekos gali būti labai ribotos palaikomų garso formatų atžvilgiu. Pavyzdžiui, Seeed Arduino Audio biblioteka, kuri gali atkurti garsą per ReSpeaker, palaiko tik 44.1KHz pavyzdžių dažnį. Azure kalbos paslaugos gali pateikti garsą įvairiais formatais, tačiau nė vienas iš jų nenaudoja šio pavyzdžių dažnio - jie teikia tik 8KHz, 16KHz, 24KHz ir 48KHz. Tai reiškia, kad garsą reikia perrašyti į 44.1KHz, o tam reikėtų daugiau resursų, nei turi Wio Terminal, ypač atminties.

Kai reikia manipuliuoti tokiais duomenimis, dažnai geriau naudoti serverless kodą, ypač jei duomenys gaunami per interneto užklausą. Wio Terminal gali iškviesti serverless funkciją, perduodant tekstą konvertuoti, o serverless funkcija gali tiek iškviesti kalbos paslaugą tekstui paversti į kalbą, tiek perrašyti garsą į reikiamą pavyzdžių dažnį. Tada ji gali grąžinti garsą forma, kurios reikia Wio Terminal, kad jis būtų išsaugotas SD kortelėje ir atkurtas per ReSpeaker.

### Užduotis - sukurti serverless funkciją tekstui paversti į kalbą

1. Atidarykite savo `smart-timer-trigger` projektą VS Code ir terminale įsitikinkite, kad virtuali aplinka yra aktyvuota. Jei ne, uždarykite ir iš naujo sukurkite terminalą.

1. Pridėkite naują HTTP trigerį šiai programai, pavadintą `text-to-speech`, naudodami šią komandą iš VS Code terminalo, esančio funkcijų programos projekto šakniniame aplanke:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    Tai sukurs HTTP trigerį, pavadintą `text-to-speech`.

1. [librosa](https://librosa.org) Pip paketas turi funkcijas garsui perrašyti, todėl pridėkite jį į `requirements.txt` failą:

    ```sh
    librosa
    ```

    Kai tai bus pridėta, įdiekite Pip paketus naudodami šią komandą iš VS Code terminalo:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ Jei naudojate Linux, įskaitant Raspberry Pi OS, gali tekti įdiegti `libsndfile` naudodami šią komandą:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. Norėdami tekstą paversti į kalbą, negalite tiesiogiai naudoti kalbos API rakto, vietoj to turite paprašyti prieigos žetono, naudodami API raktą prieigos žetono užklausos autentifikavimui. Atidarykite `__init__.py` failą iš `text-to-speech` aplanko ir pakeiskite visą jo kodą šiuo:

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

    Tai apibrėžia konstantas vietai ir kalbos raktui, kurie bus skaitomi iš nustatymų. Tada apibrėžia `get_access_token` funkciją, kuri gaus prieigos žetoną kalbos paslaugai.

1. Žemiau šio kodo pridėkite šį:

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

    Tai apibrėžia HTTP trigerį, kuris konvertuoja tekstą į kalbą. Jis ištraukia tekstą konvertuoti, kalbą ir balsą iš JSON kūno, nurodyto užklausoje, sukuria SSML, kad paprašytų kalbos, tada iškviečia atitinkamą REST API, autentifikuodamas naudodamas prieigos žetoną. Šis REST API iškvietimas grąžina garsą, užkoduotą kaip 16-bitų, 48KHz mono WAV failą, apibrėžtą `playback_format` reikšme, kuri siunčiama REST API iškvietimui.

    Tada šis garsas perrašomas `librosa` iš 48KHz pavyzdžių dažnio į 44.1KHz pavyzdžių dažnį, tada šis garsas išsaugomas į dvejetainį buferį, kuris vėliau grąžinamas.

1. Vietoje paleiskite savo funkcijų programą arba įdiekite ją debesyje. Tada galite ją iškviesti naudodami tokį įrankį kaip curl, taip pat kaip testavote savo `text-to-timer` HTTP trigerį. Įsitikinkite, kad perduodate kalbą, balsą ir tekstą kaip JSON kūną:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    Pakeiskite `<language>` į savo kalbą, pavyzdžiui, `en-GB` arba `zh-CN`. Pakeiskite `<voice>` į balsą, kurį norite naudoti. Pakeiskite `<text>` į tekstą, kurį norite paversti į kalbą. Galite išsaugoti rezultatą į failą ir atkurti jį bet kuriuo garso grotuvu, kuris gali atkurti WAV failus.

    Pavyzdžiui, norėdami paversti "Hello" į kalbą, naudodami JAV anglų kalbą su Jenny Neural balsu, kai funkcijų programa veikia vietoje, galite naudoti šią curl komandą:

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

    Tai išsaugos garsą į `hello.wav` dabartiniame kataloge.

> 💁 Šį kodą galite rasti [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) aplanke.

### Užduotis - gauti kalbą iš savo Wio Terminal

1. Atidarykite `smart-timer` projektą VS Code, jei jis dar neatidarytas.

1. Atidarykite `config.h` antraštės failą ir pridėkite savo funkcijų programos URL:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    Pakeiskite `<URL>` į `text-to-speech` HTTP trigerio URL savo funkcijų programoje. Tai bus tas pats kaip `TEXT_TO_TIMER_FUNCTION_URL` reikšmė, išskyrus funkcijos pavadinimą `text-to-speech` vietoj `text-to-timer`.

1. Atidarykite `text_to_speech.h` antraštės failą ir pridėkite šį metodą į `public` sekciją `TextToSpeech` klasėje:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. `convertTextToSpeech` metode pridėkite šį kodą, kad sukurtumėte JSON, kurį reikia išsiųsti funkcijų programai:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Tai rašo kalbą, balsą ir tekstą į JSON dokumentą, tada serializuoja jį į eilutę.

1. Žemiau pridėkite šį kodą, kad iškviestumėte funkcijų programą:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Tai sukuria HTTPClient, tada atlieka POST užklausą, naudodamas JSON dokumentą, į tekstą į kalbą HTTP trigerį.

1. Jei užklausa veikia, žali dvejetainiai duomenys, grąžinti iš funkcijų programos iškvietimo, gali būti perduoti į failą SD kortelėje. Pridėkite šį kodą, kad tai padarytumėte:

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

    Šis kodas patikrina atsakymą, ir jei jis yra 200 (sėkmė), dvejetainiai duomenys perduodami į failą SD kortelės šaknyje, pavadintą `SPEECH.WAV`.

1. Šio metodo pabaigoje uždarykite HTTP ryšį:

    ```cpp
    httpClient.end();
    ```

1. Dabar tekstas, kurį reikia pasakyti, gali būti paverstas į garsą. `main.cpp` faile pridėkite šią eilutę į `say` funkcijos pabaigą, kad tekstas būtų paverstas į garsą:
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### Užduotis - paleisti garsą iš savo Wio Terminal

**Greitai pasirodys**

## Funkcijų programos diegimas debesyje

Priežastis, kodėl funkcijų programa vykdoma lokaliai, yra ta, kad `librosa` Pip paketas Linux sistemoje priklauso nuo bibliotekos, kuri nėra įdiegta pagal numatytuosius nustatymus, ir ją reikės įdiegti prieš paleidžiant funkcijų programą. Funkcijų programos yra be serverių - nėra serverių, kuriuos galėtumėte valdyti patys, todėl nėra galimybės iš anksto įdiegti šią biblioteką.

Tam, kad tai padarytumėte, funkcijų programą reikia diegti naudojant „Docker“ konteinerį. Šis konteineris yra diegiamas debesyje, kai reikia paleisti naują funkcijų programos instanciją (pavyzdžiui, kai paklausa viršija turimus resursus arba jei funkcijų programa ilgą laiką nebuvo naudojama ir buvo uždaryta).

Instrukcijas, kaip sukurti funkcijų programą ir diegti ją per „Docker“, galite rasti [Microsoft Docs dokumentacijoje apie funkcijų kūrimą Linux sistemoje naudojant pasirinktinius konteinerius](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python).

Kai tai bus įdiegta, galite perkelti savo Wio Terminal kodą, kad pasiektumėte šią funkciją:

1. Pridėkite Azure Functions sertifikatą į `config.h`:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Pakeiskite visus `
<WiFiClient.h>` į `<WiFiClientSecure.h>`.

1. Pakeiskite visus `WiFiClient` laukus į `WiFiClientSecure`.

1. Kiekvienoje klasėje, kurioje yra `WiFiClientSecure` laukas, pridėkite konstruktorių ir nustatykite sertifikatą tame konstruktoriuje:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama profesionali žmogaus vertimo paslauga. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius naudojant šį vertimą.