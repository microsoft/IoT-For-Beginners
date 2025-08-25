<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-25T17:47:53+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "hi"
}
-->
# टेक्स्ट से स्पीच - Wio Terminal

इस पाठ के इस भाग में, आप टेक्स्ट को स्पीच में बदलेंगे ताकि बोले गए फीडबैक प्रदान किया जा सके।

## टेक्स्ट से स्पीच

स्पीच सर्विसेज SDK, जिसे आपने पिछले पाठ में स्पीच को टेक्स्ट में बदलने के लिए उपयोग किया था, टेक्स्ट को वापस स्पीच में बदलने के लिए भी उपयोग किया जा सकता है।

## वॉयस की सूची प्राप्त करें

स्पीच का अनुरोध करते समय, आपको उपयोग करने के लिए वॉयस प्रदान करनी होगी क्योंकि स्पीच विभिन्न प्रकार की वॉयस का उपयोग करके उत्पन्न की जा सकती है। प्रत्येक भाषा विभिन्न प्रकार की वॉयस का समर्थन करती है, और आप स्पीच सर्विसेज SDK से प्रत्येक भाषा के लिए समर्थित वॉयस की सूची प्राप्त कर सकते हैं। माइक्रोकंट्रोलर की सीमाएं यहां प्रभाव डालती हैं - टेक्स्ट से स्पीच सर्विसेज द्वारा समर्थित वॉयस की सूची प्राप्त करने के लिए कॉल एक JSON दस्तावेज़ है जिसका आकार 77KB से अधिक है, जो Wio Terminal द्वारा संसाधित करने के लिए बहुत बड़ा है। लेखन के समय, पूरी सूची में 215 वॉयस शामिल हैं, प्रत्येक को निम्नलिखित JSON दस्तावेज़ द्वारा परिभाषित किया गया है:

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

यह JSON **Aria** वॉयस के लिए है, जिसमें कई वॉयस स्टाइल हैं। टेक्स्ट को स्पीच में बदलते समय केवल `en-US-AriaNeural` जैसे शॉर्टनेम की आवश्यकता होती है।

पूरी सूची को माइक्रोकंट्रोलर पर डाउनलोड और डिकोड करने के बजाय, आपको उस भाषा के लिए वॉयस की सूची प्राप्त करने के लिए कुछ और सर्वरलेस कोड लिखने की आवश्यकता होगी जिसे आप उपयोग कर रहे हैं, और इसे अपने Wio Terminal से कॉल करें। आपका कोड फिर सूची से एक उपयुक्त वॉयस चुन सकता है, जैसे कि पहली वॉयस जो उसे मिलती है।

### कार्य - वॉयस की सूची प्राप्त करने के लिए एक सर्वरलेस फंक्शन बनाएं

1. अपने `smart-timer-trigger` प्रोजेक्ट को VS Code में खोलें और सुनिश्चित करें कि टर्मिनल में वर्चुअल एनवायरनमेंट सक्रिय है। यदि नहीं, तो टर्मिनल को बंद करें और फिर से बनाएं।

1. `local.settings.json` फ़ाइल खोलें और स्पीच API कुंजी और स्थान के लिए सेटिंग्स जोड़ें:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    `<key>` को अपनी स्पीच सर्विस रिसोर्स की API कुंजी से बदलें। `<location>` को उस स्थान से बदलें जिसे आपने स्पीच सर्विस रिसोर्स बनाते समय उपयोग किया था।

1. इस ऐप में एक नया HTTP ट्रिगर `get-voices` नामक जोड़ें। इसे VS Code टर्मिनल में फंक्शन ऐप प्रोजेक्ट के रूट फ़ोल्डर से निम्नलिखित कमांड का उपयोग करके बनाएं:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    यह एक HTTP ट्रिगर `get-voices` बनाएगा।

1. `get-voices` फ़ोल्डर में `__init__.py` फ़ाइल की सामग्री को निम्नलिखित से बदलें:

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

    यह कोड वॉयस प्राप्त करने के लिए एंडपॉइंट पर HTTP अनुरोध करता है। वॉयस की यह सूची सभी भाषाओं के लिए वॉयस के साथ एक बड़ा JSON ब्लॉक है, इसलिए अनुरोध बॉडी में पास की गई भाषा के लिए वॉयस को फ़िल्टर किया जाता है, फिर शॉर्टनेम को निकाला जाता है और JSON सूची के रूप में लौटाया जाता है। टेक्स्ट को स्पीच में बदलने के लिए केवल इस शॉर्टनेम की आवश्यकता होती है, इसलिए केवल यही मान लौटाया जाता है।

    > 💁 आप आवश्यकतानुसार फ़िल्टर बदल सकते हैं ताकि केवल वही वॉयस चुनी जाएं जो आप चाहते हैं।

    यह डेटा का आकार 77KB (लेखन के समय) से घटाकर एक बहुत छोटे JSON दस्तावेज़ में बदल देता है। उदाहरण के लिए, US वॉयस के लिए यह 408 बाइट्स है।

1. अपनी फंक्शन ऐप को लोकली चलाएं। फिर आप इसे `text-to-timer` HTTP ट्रिगर का परीक्षण करने के समान तरीके से `curl` जैसे टूल का उपयोग करके कॉल कर सकते हैं। सुनिश्चित करें कि अपनी भाषा को JSON बॉडी के रूप में पास करें:

    ```json
    {
        "language":"<language>"
    }
    ```

    `<language>` को अपनी भाषा से बदलें, जैसे `en-GB` या `zh-CN`।

> 💁 आप इस कोड को [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) फ़ोल्डर में पा सकते हैं।

### कार्य - अपने Wio Terminal से वॉयस प्राप्त करें

1. यदि `smart-timer` प्रोजेक्ट पहले से खुला नहीं है, तो इसे VS Code में खोलें।

1. `config.h` हेडर फ़ाइल खोलें और अपनी फंक्शन ऐप के लिए URL जोड़ें:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    `<URL>` को अपनी फंक्शन ऐप के `get-voices` HTTP ट्रिगर के URL से बदलें। यह `TEXT_TO_TIMER_FUNCTION_URL` के मान के समान होगा, सिवाय इसके कि फंक्शन का नाम `text-to-timer` के बजाय `get-voices` होगा।

1. `src` फ़ोल्डर में एक नई फ़ाइल बनाएं जिसका नाम `text_to_speech.h` हो। इसका उपयोग टेक्स्ट को स्पीच में बदलने के लिए एक क्लास को परिभाषित करने के लिए किया जाएगा।

1. नई `text_to_speech.h` फ़ाइल के शीर्ष पर निम्नलिखित इनक्लूड निर्देश जोड़ें:

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

1. इसके नीचे निम्नलिखित कोड जोड़ें ताकि `TextToSpeech` क्लास को घोषित किया जा सके, साथ ही एक इंस्टेंस जिसे एप्लिकेशन के बाकी हिस्सों में उपयोग किया जा सके:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. अपनी फंक्शन ऐप को कॉल करने के लिए, आपको एक WiFi क्लाइंट घोषित करना होगा। क्लास के `private` सेक्शन में निम्नलिखित जोड़ें:

    ```cpp
    WiFiClient _client;
    ```

1. `private` सेक्शन में, चयनित वॉयस के लिए एक फ़ील्ड जोड़ें:

    ```cpp
    String _voice;
    ```

1. `public` सेक्शन में, एक `init` फंक्शन जोड़ें जो पहली वॉयस प्राप्त करेगा:

    ```cpp
    void init()
    {
    }
    ```

1. वॉयस प्राप्त करने के लिए, एक JSON दस्तावेज़ को फंक्शन ऐप में भेजा जाना चाहिए जिसमें भाषा हो। `init` फंक्शन में निम्नलिखित कोड जोड़ें ताकि यह JSON दस्तावेज़ बनाया जा सके:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. इसके बाद एक `HTTPClient` बनाएं, फिर इसका उपयोग वॉयस प्राप्त करने के लिए फंक्शन ऐप को कॉल करने के लिए करें, JSON दस्तावेज़ को पोस्ट करते हुए:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. इसके नीचे कोड जोड़ें ताकि प्रतिक्रिया को चेक किया जा सके, और यदि यह 200 (सफलता) है, तो वॉयस की सूची निकाली जाए और सूची से पहली वॉयस प्राप्त की जाए:

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

1. इसके बाद, HTTP क्लाइंट कनेक्शन को समाप्त करें:

    ```cpp
    httpClient.end();
    ```

1. `main.cpp` फ़ाइल खोलें, और इस नई हेडर फ़ाइल को शामिल करने के लिए शीर्ष पर निम्नलिखित इनक्लूड निर्देश जोड़ें:

    ```cpp
    #include "text_to_speech.h"
    ```

1. `setup` फंक्शन में, `speechToText.init();` कॉल के नीचे निम्नलिखित जोड़ें ताकि `TextToSpeech` क्लास को इनिशियलाइज़ किया जा सके:

    ```cpp
    textToSpeech.init();
    ```

1. इस कोड को बिल्ड करें, इसे अपने Wio Terminal पर अपलोड करें और इसे सीरियल मॉनिटर के माध्यम से टेस्ट करें। सुनिश्चित करें कि आपकी फंक्शन ऐप चल रही है।

    आपको फंक्शन ऐप से लौटाई गई उपलब्ध वॉयस की सूची दिखाई देगी, साथ ही चयनित वॉयस भी।

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

## टेक्स्ट को स्पीच में बदलें

एक बार आपके पास उपयोग करने के लिए वॉयस हो, इसे टेक्स्ट को स्पीच में बदलने के लिए उपयोग किया जा सकता है। वॉयस के साथ वही मेमोरी सीमाएं स्पीच को टेक्स्ट में बदलने पर भी लागू होती हैं, इसलिए आपको स्पीच को SD कार्ड पर लिखने की आवश्यकता होगी ताकि इसे ReSpeaker पर चलाया जा सके।

> 💁 इस प्रोजेक्ट के पिछले पाठों में आपने माइक्रोफोन से कैप्चर की गई स्पीच को स्टोर करने के लिए फ्लैश मेमोरी का उपयोग किया था। इस पाठ में SD कार्ड का उपयोग किया गया है क्योंकि Seeed ऑडियो लाइब्रेरी का उपयोग करके इसे चलाना आसान है।

एक और सीमा पर विचार करना है, स्पीच सर्विस से उपलब्ध ऑडियो डेटा और Wio Terminal द्वारा समर्थित फॉर्मेट। पूर्ण कंप्यूटरों के विपरीत, माइक्रोकंट्रोलर के लिए ऑडियो लाइब्रेरी ऑडियो फॉर्मेट में बहुत सीमित हो सकती हैं। उदाहरण के लिए, Seeed Arduino Audio लाइब्रेरी जो ReSpeaker पर साउंड चला सकती है, केवल 44.1KHz सैंपल रेट पर ऑडियो का समर्थन करती है। Azure स्पीच सर्विसेज कई फॉर्मेट में ऑडियो प्रदान कर सकती हैं, लेकिन उनमें से कोई भी इस सैंपल रेट का उपयोग नहीं करता है, वे केवल 8KHz, 16KHz, 24KHz और 48KHz प्रदान करते हैं। इसका मतलब है कि ऑडियो को 44.1KHz में फिर से सैंपल करना होगा, जो Wio Terminal के पास अधिक संसाधन, विशेष रूप से मेमोरी, की आवश्यकता होगी।

जब इस तरह के डेटा को हेरफेर करने की आवश्यकता होती है, तो अक्सर सर्वरलेस कोड का उपयोग करना बेहतर होता है, खासकर यदि डेटा वेब कॉल के माध्यम से प्राप्त किया गया हो। Wio Terminal एक सर्वरलेस फंक्शन को कॉल कर सकता है, टेक्स्ट को बदलने के लिए पास कर सकता है, और सर्वरलेस फंक्शन टेक्स्ट को स्पीच में बदलने के लिए स्पीच सर्विस को कॉल कर सकता है, साथ ही ऑडियो को आवश्यक सैंपल रेट में फिर से सैंपल कर सकता है। फिर यह ऑडियो को उस फॉर्म में लौटा सकता है जिसकी Wio Terminal को आवश्यकता है ताकि इसे SD कार्ड पर स्टोर किया जा सके और ReSpeaker पर चलाया जा सके।

### कार्य - टेक्स्ट को स्पीच में बदलने के लिए एक सर्वरलेस फंक्शन बनाएं

1. अपने `smart-timer-trigger` प्रोजेक्ट को VS Code में खोलें और सुनिश्चित करें कि टर्मिनल में वर्चुअल एनवायरनमेंट सक्रिय है। यदि नहीं, तो टर्मिनल को बंद करें और फिर से बनाएं।

1. इस ऐप में एक नया HTTP ट्रिगर `text-to-speech` नामक जोड़ें। इसे VS Code टर्मिनल में फंक्शन ऐप प्रोजेक्ट के रूट फ़ोल्डर से निम्नलिखित कमांड का उपयोग करके बनाएं:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    यह एक HTTP ट्रिगर `text-to-speech` बनाएगा।

1. [librosa](https://librosa.org) Pip पैकेज में ऑडियो को फिर से सैंपल करने के लिए फंक्शन हैं, इसलिए इसे `requirements.txt` फ़ाइल में जोड़ें:

    ```sh
    librosa
    ```

    इसे जोड़ने के बाद, निम्नलिखित कमांड का उपयोग करके Pip पैकेज इंस्टॉल करें:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ यदि आप Linux, जिसमें Raspberry Pi OS शामिल है, का उपयोग कर रहे हैं, तो आपको `libsndfile` को निम्नलिखित कमांड का उपयोग करके इंस्टॉल करना पड़ सकता है:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. टेक्स्ट को स्पीच में बदलने के लिए, आप सीधे स्पीच API कुंजी का उपयोग नहीं कर सकते, इसके बजाय आपको एक एक्सेस टोकन का अनुरोध करना होगा, एक्सेस टोकन अनुरोध को प्रमाणित करने के लिए API कुंजी का उपयोग करते हुए। `text-to-speech` फ़ोल्डर से `__init__.py` फ़ाइल खोलें और इसमें सभी कोड को निम्नलिखित से बदलें:

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

    यह सेटिंग्स से पढ़े जाने वाले स्थान और स्पीच कुंजी के लिए कॉन्स्टेंट्स को परिभाषित करता है। फिर यह `get_access_token` फंक्शन को परिभाषित करता है जो स्पीच सर्विस के लिए एक्सेस टोकन प्राप्त करेगा।

1. इस कोड के नीचे निम्नलिखित जोड़ें:

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

    यह टेक्स्ट को स्पीच में बदलने वाले HTTP ट्रिगर को परिभाषित करता है। यह JSON बॉडी से टेक्स्ट, भाषा और वॉयस को निकालता है, स्पीच का अनुरोध करने के लिए कुछ SSML बनाता है, फिर संबंधित REST API को एक्सेस टोकन का उपयोग करके प्रमाणित करता है। यह REST API कॉल ऑडियो को 16-बिट, 48KHz मोनो WAV फ़ाइल के रूप में लौटाता है, जिसे `playback_format` के मान द्वारा परिभाषित किया गया है, जिसे REST API कॉल में भेजा जाता है।

    फिर इसे `librosa` द्वारा 48KHz के सैंपल रेट से 44.1KHz के सैंपल रेट में फिर से सैंपल किया जाता है, फिर इस ऑडियो को एक बाइनरी बफर में सेव किया जाता है जिसे फिर लौटाया जाता है।

1. अपनी फंक्शन ऐप को लोकली चलाएं, या इसे क्लाउड में डिप्लॉय करें। फिर आप इसे `text-to-timer` HTTP ट्रिगर का परीक्षण करने के समान तरीके से `curl` जैसे टूल का उपयोग करके कॉल कर सकते हैं। सुनिश्चित करें कि भाषा, वॉयस और टेक्स्ट को JSON बॉडी के रूप में पास करें:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    `<language>` को अपनी भाषा से बदलें, जैसे `en-GB` या `zh-CN`। `<voice>` को उस वॉयस से बदलें जिसे आप उपयोग करना चाहते हैं। `<text>` को उस टेक्स्ट से बदलें जिसे आप स्पीच में बदलना चाहते हैं। आप आउटपुट को एक फ़ाइल में सेव कर सकते हैं और इसे किसी भी ऑडियो प्लेयर के साथ चला सकते हैं जो WAV फ़ाइल चला सकता है।

    उदाहरण के लिए, "Hello" को US English में Jenny Neural वॉयस के साथ स्पीच में बदलने के लिए, जब फंक्शन ऐप लोकली चल रही हो, तो आप निम्नलिखित `curl` कमांड का उपयोग कर सकते हैं:

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

    यह ऑडियो को वर्तमान डायरेक्टरी में `hello.wav` में सेव करेगा।

> 💁 आप इस कोड को [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) फ़ोल्डर में पा सकते हैं।

### कार्य - अपने Wio Terminal से स्पीच प्राप्त करें

1. यदि `smart-timer` प्रोजेक्ट पहले से खुला नहीं है, तो इसे VS Code में खोलें।

1. `config.h` हेडर फ़ाइल खोलें और अपनी फंक्शन ऐप के लिए URL जोड़ें:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    `<URL>` को अपनी फंक्शन ऐप के `text-to-speech` HTTP ट्रिगर के URL से बदलें। यह `TEXT_TO_TIMER_FUNCTION_URL` के मान के समान होगा, सिवाय इसके कि फंक्शन का नाम `text-to-timer` के बजाय `text-to-speech` होगा।

1. `text_to_speech.h` हेडर फ़ाइल खोलें, और `TextToSpeech` क्लास के `public` सेक्शन में निम्नलिखित मेथड जोड़ें:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. `convertTextToSpeech` मेथड में, फंक्शन ऐप को भेजने के लिए JSON बनाने के लिए निम्नलिखित कोड जोड़ें:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    यह भाषा, वॉयस और टेक्स्ट को JSON दस्तावेज़ में लिखता है, फिर इसे एक स्ट्रिंग में सीरियलाइज़ करता है।

1. इसके नीचे, फंक्शन ऐप को कॉल करने के लिए निम्नलिखित कोड जोड़ें:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    यह एक HTTPClient बनाता है, फिर JSON दस्तावेज़ का उपयोग करके `text-to-speech` HTTP ट्रिगर को POST अनुरोध करता है।

1. यदि कॉल सफल होती है, तो फंक्शन ऐप कॉल से लौटाए गए रॉ बाइनरी डेटा को SD कार्ड पर एक फ़ाइल में स्ट्रीम किया जा सकता है। ऐसा करने के लिए निम्नलिखित कोड जोड़ें:

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

    यह कोड प्रतिक्रिया की जांच करता है, और यदि यह 200 (सफलता) है, तो बाइनरी डेटा को SD कार्ड की रूट में `SPEECH.WAV` नामक फ़ाइल में स्ट्रीम किया जाता है।

1. इस मेथड के अंत में, HTTP कनेक्शन को बंद करें:

    ```cpp
    httpClient.end();
    ```

1. अब टेक्स्ट को स्पीच में बदलकर ऑडियो में कन्वर्ट किया जा सकता है। `main.cpp` फ़ाइल में, `say` फंक्शन के अंत में निम्नलिखित लाइन जोड़ें ताकि बोले जाने वाले टेक्स्ट को ऑडियो में बदला जा सके:
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### कार्य - अपने Wio Terminal से ऑडियो चलाएं

**जल्द आ रहा है**

## अपने फ़ंक्शन्स ऐप को क्लाउड पर डिप्लॉय करना

फ़ंक्शन्स ऐप को लोकली चलाने का कारण यह है कि Linux पर `librosa` Pip पैकेज की एक निर्भरता ऐसी लाइब्रेरी पर है जो डिफ़ॉल्ट रूप से इंस्टॉल नहीं होती है, और इसे फ़ंक्शन ऐप चलाने से पहले इंस्टॉल करना होगा। फ़ंक्शन ऐप्स सर्वरलेस होते हैं - आपके पास कोई सर्वर नहीं होता जिसे आप खुद मैनेज कर सकें, इसलिए इस लाइब्रेरी को पहले से इंस्टॉल करने का कोई तरीका नहीं है।

इसका समाधान यह है कि आप अपने फ़ंक्शन्स ऐप को एक Docker कंटेनर का उपयोग करके डिप्लॉय करें। यह कंटेनर क्लाउड द्वारा तब डिप्लॉय किया जाता है जब भी आपके फ़ंक्शन ऐप का नया इंस्टेंस शुरू करने की आवश्यकता होती है (जैसे कि जब डिमांड उपलब्ध संसाधनों से अधिक हो जाती है, या यदि फ़ंक्शन ऐप का उपयोग कुछ समय से नहीं हुआ है और इसे बंद कर दिया गया है)।

Linux पर कस्टम कंटेनर का उपयोग करके फ़ंक्शन बनाने और Docker के माध्यम से डिप्लॉय करने के निर्देश आप [Microsoft Docs पर Linux का उपयोग करके कस्टम कंटेनर में फ़ंक्शन बनाने की डाक्यूमेंटेशन](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python) में पा सकते हैं।

एक बार यह डिप्लॉय हो जाने के बाद, आप अपने Wio Terminal कोड को इस फ़ंक्शन का उपयोग करने के लिए पोर्ट कर सकते हैं:

1. Azure Functions प्रमाणपत्र को `config.h` में जोड़ें:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. सभी `<WiFiClient.h>` इनक्लूड्स को `<WiFiClientSecure.h>` में बदलें।

1. सभी `WiFiClient` फ़ील्ड्स को `WiFiClientSecure` में बदलें।

1. हर उस क्लास में जिसमें `WiFiClientSecure` फ़ील्ड है, एक कंस्ट्रक्टर जोड़ें और उस कंस्ट्रक्टर में प्रमाणपत्र सेट करें:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

**अस्वीकरण**:  
यह दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) का उपयोग करके अनुवादित किया गया है। जबकि हम सटीकता के लिए प्रयासरत हैं, कृपया ध्यान दें कि स्वचालित अनुवाद में त्रुटियां या अशुद्धियां हो सकती हैं। मूल भाषा में उपलब्ध मूल दस्तावेज़ को प्रामाणिक स्रोत माना जाना चाहिए। महत्वपूर्ण जानकारी के लिए, पेशेवर मानव अनुवाद की सिफारिश की जाती है। इस अनुवाद के उपयोग से उत्पन्न किसी भी गलतफहमी या गलत व्याख्या के लिए हम उत्तरदायी नहीं हैं।