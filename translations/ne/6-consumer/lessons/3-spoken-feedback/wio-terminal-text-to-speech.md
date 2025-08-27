<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-27T13:56:41+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "ne"
}
-->
# टेक्स्टलाई आवाजमा रूपान्तरण - Wio Terminal

यस पाठको यस भागमा, तपाईं टेक्स्टलाई आवाजमा रूपान्तरण गरेर बोल्ने प्रतिक्रिया प्रदान गर्नुहुनेछ।

## टेक्स्टलाई आवाजमा रूपान्तरण गर्नुहोस्

पछिल्लो पाठमा तपाईंले प्रयोग गरेको स्पीच सेवाहरूको SDK, जसले आवाजलाई टेक्स्टमा रूपान्तरण गर्‍यो, टेक्स्टलाई पुनः आवाजमा रूपान्तरण गर्न पनि प्रयोग गर्न सकिन्छ।

## आवाजहरूको सूची प्राप्त गर्नुहोस्

जब आवाजको अनुरोध गरिन्छ, तपाईंले प्रयोग गर्नुपर्ने आवाज प्रदान गर्नुपर्छ किनभने विभिन्न आवाजहरू प्रयोग गरेर आवाज उत्पन्न गर्न सकिन्छ। प्रत्येक भाषाले विभिन्न आवाजहरूको दायरा समर्थन गर्दछ, र तपाईं स्पीच सेवाहरूको SDK बाट प्रत्येक भाषाको लागि समर्थित आवाजहरूको सूची प्राप्त गर्न सक्नुहुन्छ। यहाँ माइक्रोकन्ट्रोलरहरूको सीमितताहरू खेलमा आउँछन् - टेक्स्टलाई आवाजमा रूपान्तरण सेवाहरूले समर्थन गर्ने आवाजहरूको सूची प्राप्त गर्न गरिएको कल ७७KB भन्दा ठूलो JSON दस्तावेज हो, जुन Wio Terminal द्वारा प्रशोधन गर्न धेरै ठूलो छ। लेखनको समयमा, पूर्ण सूचीमा २१५ आवाजहरू छन्, प्रत्येक निम्न JSON दस्तावेजद्वारा परिभाषित गरिएको छ:

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

यो JSON **Aria** आवाजको लागि हो, जसमा धेरै आवाज शैलीहरू छन्। टेक्स्टलाई आवाजमा रूपान्तरण गर्दा आवश्यक पर्ने सबै कुरा छोटो नाम हो, `en-US-AriaNeural`।

यस सम्पूर्ण सूचीलाई तपाईंको माइक्रोकन्ट्रोलरमा डाउनलोड र डिकोड गर्ने सट्टा, तपाईंले प्रयोग गरिरहेको भाषाको लागि आवाजहरूको सूची प्राप्त गर्न केही थप सर्वरलेस कोड लेख्न आवश्यक छ, र यसलाई तपाईंको Wio Terminal बाट कल गर्नुहोस्। त्यसपछि तपाईंको कोडले सूचीबाट उपयुक्त आवाज चयन गर्न सक्छ, जस्तै पहिलो भेटिएको आवाज।

### कार्य - आवाजहरूको सूची प्राप्त गर्न सर्वरलेस फङ्क्शन बनाउनुहोस्

1. VS Code मा तपाईंको `smart-timer-trigger` प्रोजेक्ट खोल्नुहोस्, र टर्मिनल खोल्नुहोस् सुनिश्चित गर्दै कि भर्चुअल वातावरण सक्रिय छ। यदि छैन भने, टर्मिनल बन्द गरेर पुनः सिर्जना गर्नुहोस्।

1. `local.settings.json` फाइल खोल्नुहोस् र स्पीच API कुञ्जी र स्थानको लागि सेटिङहरू थप्नुहोस्:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    `<key>` लाई तपाईंको स्पीच सेवा स्रोतको API कुञ्जीले प्रतिस्थापन गर्नुहोस्। `<location>` लाई तपाईंले स्पीच सेवा स्रोत सिर्जना गर्दा प्रयोग गरेको स्थानले प्रतिस्थापन गर्नुहोस्।

1. यस एपमा `get-voices` नामको नयाँ HTTP ट्रिगर थप्नुहोस् निम्न कमाण्ड प्रयोग गरेर, VS Code टर्मिनलमा फङ्क्शन एप प्रोजेक्टको मूल फोल्डरभित्र:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    यसले `get-voices` नामको HTTP ट्रिगर सिर्जना गर्नेछ।

1. `get-voices` फोल्डरको `__init__.py` फाइलको सामग्रीलाई निम्नसँग प्रतिस्थापन गर्नुहोस्:

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

    यो कोडले आवाजहरूको सूची प्राप्त गर्न अन्त बिन्दुमा HTTP अनुरोध गर्दछ। यो आवाजहरूको सूची सबै भाषाहरूको लागि ठूलो JSON ब्लक हो, त्यसैले अनुरोध शरीरमा पास गरिएको भाषाको लागि आवाजहरू फिल्टर गरिन्छ, त्यसपछि छोटो नाम निकालेर JSON सूचीको रूपमा फर्काइन्छ। टेक्स्टलाई आवाजमा रूपान्तरण गर्न आवश्यक पर्ने मान छोटो नाम हो, त्यसैले केवल यो मान फर्काइन्छ।

    > 💁 तपाईं आवश्यक अनुसार फिल्टर परिवर्तन गर्न सक्नुहुन्छ ताकि तपाईंले चाहेको आवाजहरू मात्र चयन गर्न सक्नुहुन्छ।

    यसले डेटा आकारलाई लेखनको समयमा ७७KB बाट घटाएर धेरै सानो JSON दस्तावेजमा रूपान्तरण गर्दछ। उदाहरणका लागि, US आवाजहरूको लागि यो ४०८ बाइट्स हो।

1. तपाईंको फङ्क्शन एपलाई स्थानीय रूपमा चलाउनुहोस्। त्यसपछि तपाईं यसलाई curl जस्तो उपकरण प्रयोग गरेर कल गर्न सक्नुहुन्छ, ठीक त्यस्तै जसरी तपाईंले `text-to-timer` HTTP ट्रिगर परीक्षण गर्नुभयो। सुनिश्चित गर्नुहोस् कि तपाईंको भाषा JSON शरीरको रूपमा पास गरिएको छ:

    ```json
    {
        "language":"<language>"
    }
    ```

    `<language>` लाई तपाईंको भाषा, जस्तै `en-GB` वा `zh-CN` ले प्रतिस्थापन गर्नुहोस्।

> 💁 तपाईं यो कोड [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) फोल्डरमा फेला पार्न सक्नुहुन्छ।

### कार्य - Wio Terminal बाट आवाज प्राप्त गर्नुहोस्

1. यदि खुला छैन भने, VS Code मा `smart-timer` प्रोजेक्ट खोल्नुहोस्।

1. `config.h` हेडर फाइल खोल्नुहोस् र तपाईंको फङ्क्शन एपको URL थप्नुहोस्:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    `<URL>` लाई तपाईंको फङ्क्शन एपको `get-voices` HTTP ट्रिगरको URL ले प्रतिस्थापन गर्नुहोस्। यो `TEXT_TO_TIMER_FUNCTION_URL` को मानसँग समान हुनेछ, तर `text-to-timer` को सट्टा `get-voices` को फङ्क्शन नाम हुनेछ।

1. `src` फोल्डरमा नयाँ फाइल सिर्जना गर्नुहोस् जसलाई `text_to_speech.h` भनिन्छ। यो टेक्स्टलाई आवाजमा रूपान्तरण गर्न कक्षा परिभाषित गर्न प्रयोग गरिनेछ।

1. नयाँ `text_to_speech.h` फाइलको शीर्षमा निम्न समावेश निर्देशनहरू थप्नुहोस्:

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

1. यसपछि निम्न कोड थप्नुहोस् ताकि `TextToSpeech` कक्षा घोषणा गर्न सकियोस्, साथै एप्लिकेसनको बाँकी भागमा प्रयोग गर्न सकिने उदाहरण:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. तपाईंको फङ्क्शन एपलाई कल गर्न, तपाईंले WiFi क्लाइन्ट घोषणा गर्न आवश्यक छ। कक्षाको `private` खण्डमा निम्न थप्नुहोस्:

    ```cpp
    WiFiClient _client;
    ```

1. `private` खण्डमा, चयन गरिएको आवाजको लागि एउटा फिल्ड थप्नुहोस्:

    ```cpp
    String _voice;
    ```

1. `public` खण्डमा, एउटा `init` फङ्क्शन थप्नुहोस् जसले पहिलो आवाज प्राप्त गर्नेछ:

    ```cpp
    void init()
    {
    }
    ```

1. आवाजहरू प्राप्त गर्न, अनुरोध गरिएको भाषासहित JSON दस्तावेज फङ्क्शन एपमा पठाउन आवश्यक छ। `init` फङ्क्शनमा निम्न कोड थप्नुहोस्:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. त्यसपछि एउटा `HTTPClient` सिर्जना गर्नुहोस्, त्यसपछि यसलाई फङ्क्शन एपलाई आवाजहरू प्राप्त गर्न कल गर्न प्रयोग गर्नुहोस्, JSON दस्तावेज पोस्ट गर्दै:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. यसपछि प्रतिक्रिया कोड जाँच गर्न कोड थप्नुहोस्, र यदि यो २०० (सफलता) हो भने, आवाजहरूको सूची निकाल्नुहोस्, सूचीबाट पहिलो आवाज प्राप्त गर्दै:

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

1. यसपछि, HTTP क्लाइन्ट कनेक्शन समाप्त गर्नुहोस्:

    ```cpp
    httpClient.end();
    ```

1. `main.cpp` फाइल खोल्नुहोस्, र यस नयाँ हेडर फाइल समावेश गर्न शीर्षमा निम्न समावेश निर्देशन थप्नुहोस्:

    ```cpp
    #include "text_to_speech.h"
    ```

1. `setup` फङ्क्शनमा, `speechToText.init();` कलको तल निम्न थप्नुहोस् ताकि `TextToSpeech` कक्षा आरम्भ गर्न सकियोस्:

    ```cpp
    textToSpeech.init();
    ```

1. यो कोड निर्माण गर्नुहोस्, यसलाई तपाईंको Wio Terminal मा अपलोड गर्नुहोस् र यसलाई सिरियल मोनिटर मार्फत परीक्षण गर्नुहोस्। सुनिश्चित गर्नुहोस् कि तपाईंको फङ्क्शन एप चलिरहेको छ।

    तपाईंले फङ्क्शन एपबाट फर्काइएको उपलब्ध आवाजहरूको सूची देख्नुहुनेछ, साथै चयन गरिएको आवाज।

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

## टेक्स्टलाई आवाजमा रूपान्तरण गर्नुहोस्

एकपटक तपाईंले प्रयोग गर्नको लागि आवाज प्राप्त गर्नुभयो भने, यसलाई टेक्स्टलाई आवाजमा रूपान्तरण गर्न प्रयोग गर्न सकिन्छ। आवाजलाई टेक्स्टमा रूपान्तरण गर्दा जस्तै, आवाजलाई रूपान्तरण गर्दा पनि समान मेमोरी सीमितताहरू लागू हुन्छन्, त्यसैले तपाईंले यसलाई SD कार्डमा लेख्न आवश्यक छ ताकि यसलाई ReSpeaker मार्फत बजाउन सकियोस्।

> 💁 यस प्रोजेक्टको प्रारम्भिक पाठहरूमा तपाईंले माइक्रोफोनबाट क्याप्चर गरिएको आवाज भण्डारण गर्न फ्ल्यास मेमोरी प्रयोग गर्नुभएको थियो। यो पाठले SD कार्ड प्रयोग गर्दछ किनभने Seeed अडियो लाइब्रेरीहरू प्रयोग गरेर यसबाट अडियो बजाउन सजिलो छ।

त्यहाँ अर्को सीमितता पनि विचार गर्नुपर्छ, स्पीच सेवाबाट उपलब्ध अडियो डेटा, र Wio Terminal ले समर्थन गर्ने ढाँचाहरू। पूर्ण कम्प्युटरहरू जस्तो नभई, माइक्रोकन्ट्रोलरहरूको लागि अडियो लाइब्रेरीहरूले समर्थन गर्ने अडियो ढाँचाहरू धेरै सीमित हुन सक्छ। उदाहरणका लागि, Seeed Arduino Audio लाइब्रेरीले ReSpeaker मार्फत बजाउन सक्ने अडियो केवल ४४.१KHz नमूना दरमा समर्थन गर्दछ। Azure स्पीच सेवाहरूले धेरै ढाँचाहरूमा अडियो प्रदान गर्न सक्छ, तर तीमध्ये कुनै पनि ४४.१KHz नमूना दर प्रयोग गर्दैनन्, तिनीहरूले केवल ८KHz, १६KHz, २४KHz र ४८KHz प्रदान गर्छन्। यसको मतलब अडियोलाई ४४.१KHz मा पुनः नमूना गर्न आवश्यक छ, जुन Wio Terminal सँग अधिक संसाधनहरू आवश्यक पर्दछ, विशेष गरी मेमोरी।

यस प्रकारको डेटा हेरफेर गर्न आवश्यक पर्दा, यो अक्सर वेब कल मार्फत स्रोत गरिएको डेटा भएमा सर्वरलेस कोड प्रयोग गर्नु राम्रो हुन्छ। Wio Terminal ले सर्वरलेस फङ्क्शनलाई कल गर्न सक्छ, रूपान्तरण गर्न टेक्स्ट पास गर्दै, र सर्वरलेस फङ्क्शनले टेक्स्टलाई आवाजमा रूपान्तरण गर्न स्पीच सेवालाई कल गर्न सक्छ, साथै अडियोलाई आवश्यक नमूना दरमा पुनः नमूना गर्न सक्छ। त्यसपछि यसले अडियोलाई Wio Terminal ले आवश्यक रूपमा SD कार्डमा भण्डारण गर्न र ReSpeaker मार्फत बजाउन फिर्ता गर्न सक्छ।

### कार्य - टेक्स्टलाई आवाजमा रूपान्तरण गर्न सर्वरलेस फङ्क्शन बनाउनुहोस्

1. VS Code मा तपाईंको `smart-timer-trigger` प्रोजेक्ट खोल्नुहोस्, र टर्मिनल खोल्नुहोस् सुनिश्चित गर्दै कि भर्चुअल वातावरण सक्रिय छ। यदि छैन भने, टर्मिनल बन्द गरेर पुनः सिर्जना गर्नुहोस्।

1. यस एपमा `text-to-speech` नामको नयाँ HTTP ट्रिगर थप्नुहोस् निम्न कमाण्ड प्रयोग गरेर, VS Code टर्मिनलमा फङ्क्शन एप प्रोजेक्टको मूल फोल्डरभित्र:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    यसले `text-to-speech` नामको HTTP ट्रिगर सिर्जना गर्नेछ।

1. [librosa](https://librosa.org) Pip प्याकेजमा अडियो पुनः नमूना गर्ने फङ्क्शनहरू छन्, त्यसैले यसलाई `requirements.txt` फाइलमा थप्नुहोस्:

    ```sh
    librosa
    ```

    एकपटक यो थपिएपछि, VS Code टर्मिनलबाट निम्न कमाण्ड प्रयोग गरेर Pip प्याकेजहरू स्थापना गर्नुहोस्:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ यदि तपाईं Linux, Raspberry Pi OS सहित, प्रयोग गर्दै हुनुहुन्छ भने, तपाईंले निम्न कमाण्ड प्रयोग गरेर `libsndfile` स्थापना गर्न आवश्यक हुन सक्छ:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. टेक्स्टलाई आवाजमा रूपान्तरण गर्न, तपाईंले स्पीच API कुञ्जीलाई सिधै प्रयोग गर्न सक्नुहुन्न, यसको सट्टा तपाईंले पहुँच टोकन अनुरोध गर्न आवश्यक छ, API कुञ्जीलाई पहुँच टोकन अनुरोध प्रमाणित गर्न प्रयोग गर्दै। `text-to-speech` फोल्डरबाट `__init__.py` फाइल खोल्नुहोस् र यसमा रहेको सबै कोडलाई निम्नसँग प्रतिस्थापन गर्नुहोस्:

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

    यसले सेटिङबाट पढिने स्थान र स्पीच कुञ्जीको लागि स्थिरांकहरू परिभाषित गर्दछ। त्यसपछि यसले `get_access_token` फङ्क्शन परिभाषित गर्दछ जसले स्पीच सेवाको लागि पहुँच टोकन प्राप्त गर्नेछ।

1. यस कोडको तल निम्न थप्नुहोस्:

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

    यसले टेक्स्टलाई आवाजमा रूपान्तरण गर्ने HTTP ट्रिगर परिभाषित गर्दछ। यसले रूपान्तरण गर्न टेक्स्ट, भाषा र आवाजलाई अनुरोधमा सेट गरिएको JSON शरीरबाट निकाल्छ, स्पीच अनुरोध गर्न SSML निर्माण गर्दछ, त्यसपछि पहुँच टोकन प्रयोग गरेर प्रमाणित गर्दै सम्बन्धित REST API कल गर्दछ। यो REST API कलले १६-बिट, ४८KHz मोनो WAV फाइलको रूपमा अडियो फर्काउँछ, जुन `playback_format` को मानद्वारा परिभाषित गरिएको छ, जुन REST API कलमा पठाइन्छ।

    त्यसपछि यसलाई `librosa` द्वारा ४८KHz नमूना दरबाट ४४.१KHz नमूना दरमा पुनः नमूना गरिन्छ, त्यसपछि यो अडियोलाई बाइनरी बफरमा बचत गरिन्छ जुन त्यसपछि फर्काइन्छ।

1. तपाईंको फङ्क्शन एपलाई स्थानीय रूपमा चलाउनुहोस्, वा क्लाउडमा तैनाथ गर्नुहोस्। त्यसपछि तपाईं यसलाई curl जस्तो उपकरण प्रयोग गरेर कल गर्न सक्नुहुन्छ, ठीक त्यस्तै जसरी तपाईंले `text-to-timer` HTTP ट्रिगर परीक्षण गर्नुभयो। सुनिश्चित गर्नुहोस् कि भाषा, आवाज र टेक्स्ट JSON शरीरको रूपमा पास गरिएको छ:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    `<language>` लाई तपाईंको भाषा, जस्तै `en-GB` वा `zh-CN` ले प्रतिस्थापन गर्नुहोस्। `<voice>` लाई तपाईंले प्रयोग गर्न चाहेको आवाजले प्रतिस्थापन गर्नुहोस्। `<text>` लाई तपाईंले आवाजमा रूपान्तरण गर्न चाहेको टेक्स्टले प्रतिस्थापन गर्नुहोस्। तपाईं आउटपुटलाई फाइलमा बचत गर्न सक्नुहुन्छ र WAV फाइल बजाउन सक्ने कुनै पनि अडियो प्लेयर प्रयोग गरेर बजाउन सक्नुहुन्छ।

    उदाहरणका लागि, "Hello" लाई US English मा Jenny Neural आवाज प्रयोग गरेर आवाजमा रूपान्तरण गर्न, फङ्क्शन एप स्थानीय रूपमा चलिरहेको अवस्थामा, तपाईं निम्न curl कमाण्ड प्रयोग गर्न सक्नुहुन्छ:

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

    यसले अडियोलाई `hello.wav` मा हालको डाइरेक्टरीमा बचत गर्नेछ।

> 💁 तपाईं यो कोड [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) फोल्डरमा फेला पार्न सक्नुहुन्छ।

### कार्य - Wio Terminal बाट आवाज प्राप्त गर्नुहोस्

1. यदि खुला छैन भने, VS Code मा `smart-timer` प्रोजेक्ट खोल्नुहोस्।

1. `config.h` हेडर फाइल खोल्नुहोस् र तपाईंको फङ्क्शन एपको URL थप्नुहोस्:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    `<URL>` लाई तपाईंको फङ्क्शन एपको `text-to-speech` HTTP ट्रिगरको URL ले प्रतिस्थापन गर्नुहोस्। यो `TEXT_TO_TIMER_FUNCTION_URL` को मानसँग समान हुनेछ, तर `text-to-timer` को सट्टा `text-to-speech` को फङ्क्शन नाम हुनेछ।

1. `text_to_speech.h` हेडर फाइल खोल्नुहोस्, र `TextToSpeech` कक्षाको `public` खण्डमा निम्न विधि थप्नुहोस्:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. `convertTextToSpeech` विधिमा, फङ्क्शन एपमा पठाउन JSON सिर्जना गर्न निम्न कोड थप्नुहोस्:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    यसले भाषा, आवाज र टेक्स्टलाई JSON दस्तावेजमा लेख्छ, त्यसपछि यसलाई स्ट्रिङमा सिरियलाइज गर्दछ।

1. यसको तल, फङ्क्शन एपलाई कल गर्न निम्न कोड थप्नुहोस्:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    यसले HTTPClient सिर्जना गर्दछ, त्यसपछि JSON दस्तावेज प्रयोग गरेर टेक्स्टलाई आवाजमा रूपान्तरण गर्ने HTTP ट्रिगरमा POST अनुरोध गर्दछ।

1. यदि कल सफल हुन्छ भने, फङ्क्शन एप कलबाट फर्काइएको कच्चा बाइनरी डेटा SD कार्डमा फाइलमा स्ट्रिम गर्न सकिन्छ। यसलाई गर्न निम्न कोड थप्नुहोस्:

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

    यो कोडले प्रतिक्रिया जाँच गर्दछ, र यदि यो २०० (सफलता) हो भने, बाइनरी डेटा SD कार्डको जडमा `SPEECH.WAV` नामक फाइलमा स्ट्रिम गरिन्छ।

1. यस विधिको अन्त्यमा, HTTP कनेक्शन बन्द गर्नुहोस्:

    ```cpp
    httpClient.end();
    ```

1. बोल्नुपर्ने टेक्स्टलाई अब अडियोमा रूपान्तरण गर्न सकिन्छ। `main.cpp` फाइलमा, `say` फङ्क्शनको अन्त्यमा निम्न लाइन थप्नुहोस् ताकि बोल्नुपर्ने टेक्स्टलाई अडियोमा रूपान्तरण गर्न सकियोस्:
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### कार्य - आफ्नो Wio Terminal बाट अडियो बजाउनुहोस्

**छिट्टै आउँदैछ**

## आफ्नो functions app क्लाउडमा डिप्लोय गर्नुहोस्

फंक्शन एप्लिकेसनलाई स्थानीय रूपमा चलाउने कारण भनेको `librosa` Pip प्याकेजले लिनक्समा एउटा लाइब्रेरीमा निर्भरता राख्छ, जुन डिफल्ट रूपमा स्थापना गरिएको हुँदैन, र फंक्शन एप्लिकेसन चलाउनुअघि यो लाइब्रेरी स्थापना गर्न आवश्यक हुन्छ। फंक्शन एप्लिकेसनहरू सर्वरलेस हुन्छन् - तपाईंले आफैं व्यवस्थापन गर्न सक्ने कुनै सर्वरहरू हुँदैनन्, त्यसैले यो लाइब्रेरी पहिले नै स्थापना गर्ने कुनै उपाय हुँदैन।

यसको समाधान भनेको आफ्नो functions app लाई Docker कन्टेनर प्रयोग गरेर डिप्लोय गर्नु हो। यो कन्टेनर क्लाउडले तब डिप्लोय गर्छ जब नयाँ instance को आवश्यकता हुन्छ (जस्तै, माग उपलब्ध स्रोतहरू भन्दा बढी हुँदा, वा फंक्शन एप्लिकेसन लामो समयसम्म प्रयोग नगरिएको अवस्थामा बन्द हुँदा)।

Linux मा कस्टम कन्टेनर प्रयोग गरेर फंक्शन बनाउने र Docker मार्फत डिप्लोय गर्ने निर्देशिका [Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python) मा पाउन सकिन्छ।

यो डिप्लोय भएपछि, तपाईं आफ्नो Wio Terminal कोडलाई यो फंक्शनमा पहुँच गर्न पोर्ट गर्न सक्नुहुन्छ:

1. Azure Functions प्रमाणपत्रलाई `config.h` मा थप्नुहोस्:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. `<WiFiClient.h>` को सबै समावेशलाई `<WiFiClientSecure.h>` मा परिवर्तन गर्नुहोस्।

1. सबै `WiFiClient` फिल्डहरूलाई `WiFiClientSecure` मा परिवर्तन गर्नुहोस्।

1. जसको `WiFiClientSecure` फिल्ड छ, त्यस्ता प्रत्येक क्लासमा एउटा कन्स्ट्रक्टर थप्नुहोस् र उक्त कन्स्ट्रक्टरमा प्रमाणपत्र सेट गर्नुहोस्:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

**अस्वीकरण**:  
यो दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) प्रयोग गरेर अनुवाद गरिएको छ। हामी शुद्धताको लागि प्रयास गर्छौं, तर कृपया ध्यान दिनुहोस् कि स्वचालित अनुवादमा त्रुटिहरू वा अशुद्धताहरू हुन सक्छ। यसको मूल भाषा मा रहेको मूल दस्तावेज़लाई आधिकारिक स्रोत मानिनुपर्छ। महत्वपूर्ण जानकारीको लागि, व्यावसायिक मानव अनुवाद सिफारिस गरिन्छ। यस अनुवादको प्रयोगबाट उत्पन्न हुने कुनै पनि गलतफहमी वा गलत व्याख्याको लागि हामी जिम्मेवार हुने छैनौं।