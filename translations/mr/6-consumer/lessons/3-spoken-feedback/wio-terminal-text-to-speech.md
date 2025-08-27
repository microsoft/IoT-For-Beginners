<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-27T13:55:45+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "mr"
}
-->
# टेक्स्ट ते स्पीच - Wio Terminal

या धड्याच्या भागात, तुम्ही टेक्स्टला स्पीचमध्ये रूपांतरित करून बोलण्याचे फीडबॅक प्रदान कराल.

## टेक्स्ट ते स्पीच

मागील धड्यात तुम्ही टेक्स्टमध्ये रूपांतरित करण्यासाठी वापरलेली स्पीच सर्व्हिसेस SDK टेक्स्टला पुन्हा स्पीचमध्ये रूपांतरित करण्यासाठी वापरली जाऊ शकते.

## आवाजांची यादी मिळवा

स्पीचची विनंती करताना, तुम्हाला वापरण्यासाठी आवाज प्रदान करावा लागतो कारण विविध आवाजांचा वापर करून स्पीच तयार केला जाऊ शकतो. प्रत्येक भाषेसाठी विविध आवाजांचा एक श्रेणी असतो, आणि स्पीच सर्व्हिसेस SDK मधून प्रत्येक भाषेसाठी समर्थित आवाजांची यादी मिळवता येते. मायक्रोकंट्रोलर्सच्या मर्यादा येथे येतात - टेक्स्ट ते स्पीच सर्व्हिसेसद्वारे समर्थित आवाजांची यादी मिळवण्यासाठी केलेला कॉल 77KB पेक्षा मोठ्या आकाराचा JSON दस्तऐवज असतो, जो Wio Terminal द्वारे प्रक्रिया करण्यासाठी खूप मोठा आहे. लेखनाच्या वेळी, संपूर्ण यादीमध्ये 215 आवाज आहेत, प्रत्येक आवाज खालीलप्रमाणे JSON दस्तऐवजाद्वारे परिभाषित केला जातो:

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

हा JSON **Aria** आवाजासाठी आहे, ज्यामध्ये अनेक आवाज शैली आहेत. टेक्स्टला स्पीचमध्ये रूपांतरित करताना आवश्यक असलेली एकमेव गोष्ट म्हणजे shortname, `en-US-AriaNeural`.

मायक्रोकंट्रोलरवर ही संपूर्ण यादी डाउनलोड आणि डिकोड करण्याऐवजी, तुम्हाला वापरत असलेल्या भाषेसाठी आवाजांची यादी मिळवण्यासाठी काही अधिक serverless कोड लिहिण्याची आवश्यकता आहे, आणि Wio Terminal वरून हे कॉल करावे लागेल. तुमचा कोड यादीतील योग्य आवाज निवडू शकतो, जसे की त्याला सापडलेला पहिला आवाज.

### कार्य - आवाजांची यादी मिळवण्यासाठी serverless फंक्शन तयार करा

1. VS Code मध्ये तुमचा `smart-timer-trigger` प्रकल्प उघडा, आणि टर्मिनल उघडा, याची खात्री करा की वर्च्युअल वातावरण सक्रिय आहे. नसल्यास, टर्मिनल बंद करा आणि पुन्हा तयार करा.

1. `local.settings.json` फाइल उघडा आणि स्पीच API की आणि स्थानासाठी सेटिंग्ज जोडा:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    `<key>` ला तुमच्या स्पीच सर्व्हिस रिसोर्ससाठी API कीने बदला. `<location>` ला तुम्ही स्पीच सर्व्हिस रिसोर्स तयार करताना वापरलेल्या स्थानाने बदला.

1. या अॅपमध्ये `get-voices` नावाचा नवीन HTTP ट्रिगर खालील कमांड वापरून तयार करा:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    हे `get-voices` नावाचा HTTP ट्रिगर तयार करेल.

1. `get-voices` फोल्डरमधील `__init__.py` फाइलची सामग्री खालीलप्रमाणे बदला:

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

    हा कोड आवाजांची यादी मिळवण्यासाठी एंडपॉइंटला HTTP विनंती करतो. ही आवाजांची यादी सर्व भाषांसाठी मोठा JSON ब्लॉक आहे, त्यामुळे विनंती बॉडीमध्ये दिलेल्या भाषेसाठी आवाज फिल्टर केले जातात, नंतर shortname काढून JSON यादी म्हणून परत दिले जाते. टेक्स्टला स्पीचमध्ये रूपांतरित करण्यासाठी shortname आवश्यक आहे, त्यामुळे फक्त ही मूल्य परत दिली जाते.

    > 💁 तुम्ही आवश्यक असल्यास फक्त तुम्हाला हवे असलेले आवाज निवडण्यासाठी फिल्टर बदलू शकता.

    यामुळे डेटा 77KB (लेखनाच्या वेळी) पासून खूपच छोट्या JSON दस्तऐवजात कमी होतो. उदाहरणार्थ, US आवाजांसाठी हा 408 बाइट्स आहे.

1. तुमचा फंक्शन अॅप स्थानिक पातळीवर चालवा. तुम्ही तुमच्या `text-to-timer` HTTP ट्रिगरची चाचणी घेतल्याप्रमाणे curl सारख्या टूलचा वापर करून हे कॉल करू शकता. तुमची भाषा JSON बॉडी म्हणून पाठवा:

    ```json
    {
        "language":"<language>"
    }
    ```

    `<language>` ला तुमची भाषा बदला, जसे की `en-GB`, किंवा `zh-CN`.

> 💁 तुम्ही हा कोड [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) फोल्डरमध्ये शोधू शकता.

### कार्य - Wio Terminal वरून आवाज मिळवा

1. जर `smart-timer` प्रकल्प उघडलेला नसेल तर VS Code मध्ये उघडा.

1. `config.h` हेडर फाइल उघडा आणि तुमच्या फंक्शन अॅपसाठी URL जोडा:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    `<URL>` ला तुमच्या फंक्शन अॅपवरील `get-voices` HTTP ट्रिगरसाठी URL ने बदला. हे `TEXT_TO_TIMER_FUNCTION_URL` च्या मूल्यासारखेच असेल, फक्त फंक्शनचे नाव `text-to-timer` ऐवजी `get-voices` असेल.

1. `src` फोल्डरमध्ये `text_to_speech.h` नावाची नवीन फाइल तयार करा. टेक्स्टला स्पीचमध्ये रूपांतरित करण्यासाठी एक क्लास परिभाषित करण्यासाठी याचा वापर केला जाईल.

1. `text_to_speech.h` फाइलच्या शीर्षस्थानी खालील include निर्देश जोडा:

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

1. खालील कोड जोडा, जो `TextToSpeech` क्लास घोषित करतो, तसेच अॅप्लिकेशनमध्ये वापरता येणारी एक instance:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. तुमच्या फंक्शन अॅपला कॉल करण्यासाठी, तुम्हाला WiFi क्लायंट घोषित करावा लागेल. क्लासच्या `private` विभागात खालील जोडा:

    ```cpp
    WiFiClient _client;
    ```

1. `private` विभागात निवडलेल्या आवाजासाठी एक फील्ड जोडा:

    ```cpp
    String _voice;
    ```

1. `public` विभागात एक `init` फंक्शन जोडा, जे पहिला आवाज मिळवेल:

    ```cpp
    void init()
    {
    }
    ```

1. आवाज मिळवण्यासाठी, फंक्शन अॅपला JSON दस्तऐवज पाठवणे आवश्यक आहे ज्यामध्ये भाषा असेल. `init` फंक्शनमध्ये खालील कोड जोडा:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. पुढे एक `HTTPClient` तयार करा, आणि फंक्शन अॅपला कॉल करण्यासाठी वापरा, JSON दस्तऐवज पोस्ट करत:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. खालील कोड जोडा, जो प्रतिसाद कोड तपासतो, आणि जर तो 200 (यशस्वी) असेल, तर आवाजांची यादी काढतो, यादीतील पहिला आवाज मिळवतो:

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

1. यानंतर, HTTP क्लायंट कनेक्शन समाप्त करा:

    ```cpp
    httpClient.end();
    ```

1. `main.cpp` फाइल उघडा, आणि शीर्षस्थानी नवीन हेडर फाइल समाविष्ट करण्यासाठी खालील include directive जोडा:

    ```cpp
    #include "text_to_speech.h"
    ```

1. `setup` फंक्शनमध्ये, `speechToText.init();` कॉलच्या खाली, `TextToSpeech` क्लास initialize करण्यासाठी खालील जोडा:

    ```cpp
    textToSpeech.init();
    ```

1. हा कोड तयार करा, Wio Terminal वर अपलोड करा आणि serial monitor द्वारे चाचणी करा. तुमचा फंक्शन अॅप चालू असल्याची खात्री करा.

    तुम्हाला फंक्शन अॅपद्वारे परत दिलेली उपलब्ध आवाजांची यादी दिसेल, तसेच निवडलेला आवाज.

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

## टेक्स्टला स्पीचमध्ये रूपांतरित करा

एकदा तुम्हाला वापरण्यासाठी आवाज मिळाला की, तो टेक्स्टला स्पीचमध्ये रूपांतरित करण्यासाठी वापरला जाऊ शकतो. आवाजांसह स्पीचला टेक्स्टमध्ये रूपांतरित करताना समान मेमरी मर्यादा लागू होतात, त्यामुळे तुम्हाला SD कार्डवर स्पीच लिहावे लागेल जे ReSpeaker वर प्ले करण्यासाठी तयार असेल.

> 💁 या प्रकल्पातील पूर्वीच्या धड्यांमध्ये तुम्ही मायक्रोफोनमधून कॅप्चर केलेले स्पीच स्टोअर करण्यासाठी फ्लॅश मेमरीचा वापर केला होता. या धड्यात SD कार्ड वापरले जाते कारण Seeed ऑडिओ लायब्ररी वापरून त्यावरून ऑडिओ प्ले करणे सोपे आहे.

तसेच आणखी एक मर्यादा विचारात घ्यावी लागते, स्पीच सर्व्हिसेसमधून उपलब्ध ऑडिओ डेटा, आणि Wio Terminal समर्थन देणारे स्वरूप. पूर्ण संगणकांप्रमाणे नाही, मायक्रोकंट्रोलर्ससाठी ऑडिओ लायब्ररी समर्थित ऑडिओ स्वरूपांमध्ये खूप मर्यादित असू शकतात. उदाहरणार्थ, ReSpeaker वर आवाज प्ले करण्यासाठी Seeed Arduino Audio लायब्ररी फक्त 44.1KHz नमुना दरावर ऑडिओ समर्थन देते. Azure स्पीच सर्व्हिसेस अनेक स्वरूपांमध्ये ऑडिओ प्रदान करू शकते, पण त्यापैकी कोणताही 44.1KHz नमुना दर वापरत नाही, ते फक्त 8KHz, 16KHz, 24KHz आणि 48KHz प्रदान करतात. याचा अर्थ ऑडिओला 44.1KHz वर पुन्हा नमुना घ्यावा लागतो, जे Wio Terminal कडे असलेल्या संसाधनांपेक्षा अधिक संसाधने आवश्यक आहे, विशेषतः मेमरी.

डेटा अशा प्रकारे हाताळण्याची आवश्यकता असल्यास, serverless कोड वापरणे चांगले असते, विशेषतः जर डेटा वेब कॉलद्वारे मिळवला जात असेल. Wio Terminal serverless फंक्शनला कॉल करू शकतो, टेक्स्ट रूपांतरित करण्यासाठी पाठवतो, आणि serverless फंक्शन टेक्स्टला स्पीचमध्ये रूपांतरित करण्यासाठी स्पीच सर्व्हिसेसला कॉल करू शकतो, तसेच ऑडिओला आवश्यक नमुना दरावर पुन्हा नमुना घेऊ शकतो. त्यानंतर ते ऑडिओ Wio Terminal ला आवश्यक स्वरूपात परत करू शकते, जे SD कार्डवर स्टोअर केले जाऊ शकते आणि ReSpeaker वर प्ले केले जाऊ शकते.

### कार्य - टेक्स्टला स्पीचमध्ये रूपांतरित करण्यासाठी serverless फंक्शन तयार करा

1. VS Code मध्ये तुमचा `smart-timer-trigger` प्रकल्प उघडा, आणि टर्मिनल उघडा, याची खात्री करा की वर्च्युअल वातावरण सक्रिय आहे. नसल्यास, टर्मिनल बंद करा आणि पुन्हा तयार करा.

1. या अॅपमध्ये `text-to-speech` नावाचा नवीन HTTP ट्रिगर खालील कमांड वापरून तयार करा:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    हे `text-to-speech` नावाचा HTTP ट्रिगर तयार करेल.

1. [librosa](https://librosa.org) Pip पॅकेजमध्ये ऑडिओ पुन्हा नमुना घेण्यासाठी फंक्शन्स आहेत, त्यामुळे हे `requirements.txt` फाइलमध्ये जोडा:

    ```sh
    librosa
    ```

    एकदा हे जोडले की, VS Code टर्मिनलमधून खालील कमांड वापरून Pip पॅकेजेस इंस्टॉल करा:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ जर तुम्ही Linux वापरत असाल, ज्यामध्ये Raspberry Pi OS समाविष्ट आहे, तर तुम्हाला `libsndfile` खालील कमांड वापरून इंस्टॉल करावे लागेल:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. टेक्स्टला स्पीचमध्ये रूपांतरित करण्यासाठी, तुम्ही थेट स्पीच API की वापरू शकत नाही, त्याऐवजी तुम्हाला API की वापरून access token विनंती करावी लागेल. `text-to-speech` फोल्डरमधील `__init__.py` फाइल उघडा आणि त्यातील सर्व कोड खालीलप्रमाणे बदला:

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

    हे सेटिंग्जमधून वाचल्या जाणाऱ्या स्थान आणि स्पीच कीसाठी constants परिभाषित करते. त्यानंतर `get_access_token` फंक्शन परिभाषित करते जे स्पीच सर्व्हिसेससाठी access token मिळवेल.

1. या कोडखाली खालील जोडा:

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

    हे टेक्स्टला स्पीचमध्ये रूपांतरित करणारा HTTP ट्रिगर परिभाषित करते. हे रूपांतरित करण्यासाठी टेक्स्ट, भाषा आणि आवाज JSON बॉडीमधून काढते, SSML तयार करते, नंतर संबंधित REST API कॉल करते access token वापरून authenticate करत. हा REST API कॉल ऑडिओ 16-bit, 48KHz mono WAV फाइल म्हणून परत करतो, ज्याचे स्वरूप `playback_format` द्वारे परिभाषित केले जाते, जे REST API कॉलला पाठवले जाते.

    नंतर `librosa` द्वारे 48KHz नमुना दरावरून 44.1KHz नमुना दरावर पुन्हा नमुना घेतले जाते, नंतर हा ऑडिओ बायनरी बफरमध्ये सेव्ह केला जातो जो परत दिला जातो.

1. तुमचा फंक्शन अॅप स्थानिक पातळीवर चालवा, किंवा क्लाउडवर तैनात करा. तुम्ही तुमच्या `text-to-timer` HTTP ट्रिगरची चाचणी घेतल्याप्रमाणे curl सारख्या टूलचा वापर करून हे कॉल करू शकता. भाषा, आवाज आणि टेक्स्ट JSON बॉडी म्हणून पाठवा:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    `<language>` ला तुमची भाषा बदला, जसे की `en-GB`, किंवा `zh-CN`. `<voice>` ला तुम्हाला हवा असलेला आवाज बदला. `<text>` ला तुम्हाला स्पीचमध्ये रूपांतरित करायचा टेक्स्ट बदला. तुम्ही आउटपुट फाइलमध्ये सेव्ह करू शकता आणि WAV फाइल प्ले करू शकणाऱ्या कोणत्याही ऑडिओ प्लेयरद्वारे प्ले करू शकता.

    उदाहरणार्थ, "Hello" US English मध्ये Jenny Neural आवाज वापरून स्पीचमध्ये रूपांतरित करण्यासाठी, फंक्शन अॅप स्थानिक पातळीवर चालू असल्यास, तुम्ही खालील curl कमांड वापरू शकता:

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

    हे ऑडिओ `hello.wav` नावाने वर्तमान डिरेक्टरीमध्ये सेव्ह करेल.

> 💁 तुम्ही हा कोड [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) फोल्डरमध्ये शोधू शकता.

### कार्य - Wio Terminal वरून स्पीच मिळवा

1. जर `smart-timer` प्रकल्प उघडलेला नसेल तर VS Code मध्ये उघडा.

1. `config.h` हेडर फाइल उघडा आणि तुमच्या फंक्शन अॅपसाठी URL जोडा:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    `<URL>` ला तुमच्या फंक्शन अॅपवरील `text-to-speech` HTTP ट्रिगरसाठी URL ने बदला. हे `TEXT_TO_TIMER_FUNCTION_URL` च्या मूल्यासारखेच असेल, फक्त फंक्शनचे नाव `text-to-timer` ऐवजी `text-to-speech` असेल.

1. `text_to_speech.h` हेडर फाइल उघडा, आणि `TextToSpeech` क्लासच्या `public` विभागात खालील मेथड जोडा:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. `convertTextToSpeech` मेथडमध्ये, फंक्शन अॅपला पाठवण्यासाठी JSON तयार करण्यासाठी खालील कोड जोडा:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    हे भाषा, आवाज आणि टेक्स्ट JSON दस्तऐवजात लिहिते, नंतर त्याला स्ट्रिंगमध्ये serializes करते.

1. याखाली, फंक्शन अॅपला कॉल करण्यासाठी खालील कोड जोडा:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    हे एक HTTPClient तयार करते, नंतर JSON दस्तऐवज वापरून text-to-speech HTTP ट्रिगरला POST विनंती करते.

1. जर कॉल यशस्वी झाला, तर फंक्शन अॅप कॉलद्वारे परत दिलेला कच्चा बायनरी डेटा SD कार्डवरील फाइलमध्ये स्ट्रीम केला जाऊ शकतो. हे करण्यासाठी खालील कोड जोडा:

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

    हा कोड प्रतिसाद तपासतो, आणि जर तो 200 (यशस्वी) असेल, तर बायनरी डेटा SD कार्डच्या मूळ फोल्डरमध्ये `SPEECH.WAV` नावाच्या फाइलमध्ये स्ट्रीम केला जातो.

1. या मेथडच्या शेवटी, HTTP कनेक्शन बंद करा:

    ```cpp
    httpClient.end();
    ```

1. आता बोलायचा टेक्स्ट ऑडिओमध्ये रूपांतरित केला जाऊ शकतो. `main.cpp` फाइलमध्ये, `say` फंक्शनच्या शेवटी खालील ओळ जोडा, ज्यामुळे बोलायचा टेक्स्ट ऑडिओमध्ये रूपांतरित होईल:
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### कार्य - तुमच्या Wio Terminal वर ऑडिओ प्ले करा

**लवकरच येत आहे**

## तुमचे functions app क्लाउडवर तैनात करणे

तुमचे functions app स्थानिक स्तरावर चालवण्याचे कारण म्हणजे `librosa` Pip पॅकेजला लिनक्सवर अशा लायब्ररीची आवश्यकता असते जी डीफॉल्टने स्थापित केलेली नसते, आणि ती लायब्ररी स्थापित केल्याशिवाय function app चालवता येत नाही. Function apps हे serverless असतात - तुम्ही स्वतः व्यवस्थापित करू शकणारे सर्व्हर नसतात, त्यामुळे ही लायब्ररी आधीच स्थापित करण्याचा कोणताही मार्ग उपलब्ध नसतो.

यासाठी पर्याय म्हणजे तुमचे functions app Docker कंटेनर वापरून तैनात करणे. क्लाउड नवीन instance तयार करण्याची गरज भासल्यावर (उदाहरणार्थ, मागणी उपलब्ध संसाधनांपेक्षा जास्त असल्यास किंवा function app बराच वेळ वापरले गेले नसल्यामुळे बंद झाले असल्यास) हे कंटेनर तैनात केले जाते.

तुम्ही Microsoft Docs वर [लिनक्सवर कस्टम कंटेनर वापरून function तयार करण्याचे दस्तऐवज](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python) मध्ये function app सेट अप करण्याचे आणि Docker द्वारे तैनात करण्याचे निर्देश शोधू शकता.

एकदा हे तैनात झाल्यावर, तुम्ही तुमचा Wio Terminal कोड या function ला access करण्यासाठी पोर्ट करू शकता:

1. Azure Functions प्रमाणपत्र `config.h` मध्ये जोडा:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. `<WiFiClient.h>` चा समावेश बदलून `<WiFiClientSecure.h>` करा.

1. सर्व `WiFiClient` फील्ड्स बदलून `WiFiClientSecure` करा.

1. ज्या प्रत्येक class मध्ये `WiFiClientSecure` फील्ड आहे, त्या class मध्ये एक constructor जोडा आणि त्या constructor मध्ये प्रमाणपत्र सेट करा:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

**अस्वीकरण**:  
हा दस्तऐवज AI भाषांतर सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) वापरून भाषांतरित करण्यात आला आहे. आम्ही अचूकतेसाठी प्रयत्नशील असलो तरी कृपया लक्षात ठेवा की स्वयंचलित भाषांतरे त्रुटी किंवा अचूकतेच्या अभावाने युक्त असू शकतात. मूळ भाषेतील दस्तऐवज हा अधिकृत स्रोत मानला जावा. महत्त्वाच्या माहितीसाठी व्यावसायिक मानवी भाषांतराची शिफारस केली जाते. या भाषांतराचा वापर करून उद्भवलेल्या कोणत्याही गैरसमज किंवा चुकीच्या अर्थासाठी आम्ही जबाबदार राहणार नाही.