<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-10-11T12:06:19+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "ta"
}
-->
# உரையை குரலாக மாற்றுதல் - Wio Terminal

இந்த பாடத்தின் இந்த பகுதியில், உரையை குரலாக மாற்றி பேசும் பின்னூட்டத்தை வழங்கப் போகிறீர்கள்.

## உரையை குரலாக மாற்றுதல்

முந்தைய பாடத்தில் நீங்கள் உரையை குரலாக மாற்ற பயன்படுத்திய Speech Services SDK-ஐ, உரையை மீண்டும் குரலாக மாற்றவும் பயன்படுத்தலாம்.

## குரல்களின் பட்டியலைப் பெறுதல்

குரலை உருவாக்கும்போது, பயன்படுத்த வேண்டிய குரலை நீங்கள் குறிப்பிட வேண்டும், ஏனெனில் பல்வேறு குரல்களைப் பயன்படுத்தி குரல் உருவாக்க முடியும். ஒவ்வொரு மொழிக்கும் பல்வேறு குரல்கள் கிடைக்கின்றன, மேலும் ஒவ்வொரு மொழிக்கும் ஆதரவு அளிக்கப்படும் குரல்களின் பட்டியலை Speech Services SDK-இல் இருந்து பெறலாம். மைக்ரோகண்ட்ரோலர்களின் வரம்புகள் இங்கு முக்கியமாகின்றன - உரையை குரலாக மாற்றும் சேவைகளால் ஆதரிக்கப்படும் குரல்களின் பட்டியலைப் பெறுவதற்கான அழைப்பு 77KB அளவிலான JSON ஆவணமாகும், இது Wio Terminal மூலம் செயலாக்க முடியாத அளவுக்கு பெரியதாகும். இந்த ஆவணத்தை எழுதும் நேரத்தில், முழு பட்டியலில் 215 குரல்கள் உள்ளன, ஒவ்வொன்றும் பின்வரும் JSON ஆவணத்தால் வரையறுக்கப்பட்டுள்ளது:

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

இந்த JSON **Aria** குரலுக்கானது, இது பல குரல் பாணிகளை கொண்டுள்ளது. உரையை குரலாக மாற்றும்போது தேவைப்படும் அனைத்தும் `en-US-AriaNeural` என்ற shortname ஆகும்.

இந்த முழு பட்டியலை உங்கள் மைக்ரோகண்ட்ரோலரில் பதிவிறக்கம் செய்து டிகோடு செய்வதற்குப் பதிலாக, நீங்கள் பயன்படுத்தும் மொழிக்கான குரல்களின் பட்டியலை பெற சில serverless குறியீடுகளை எழுத வேண்டும், மேலும் இதை உங்கள் Wio Terminal-இல் இருந்து அழைக்க வேண்டும். உங்கள் குறியீடு பின்னர் பட்டியலிலிருந்து ஏதாவது ஒரு பொருத்தமான குரலை தேர்வு செய்யலாம், உதாரணமாக அது கண்டுபிடிக்கும் முதல் ஒன்றை.

### பணிகள் - குரல்களின் பட்டியலைப் பெற serverless செயல்பாட்டை உருவாக்கவும்

1. உங்கள் `smart-timer-trigger` திட்டத்தை VS Code-ல் திறக்கவும், மற்றும் டெர்மினலை திறந்து, மெய்நிகர் சூழல் செயல்பாட்டில் உள்ளது என்பதை உறுதிப்படுத்தவும். இல்லையெனில், டெர்மினலை முடித்து மீண்டும் உருவாக்கவும்.

1. `local.settings.json` கோப்பைத் திறந்து, Speech API key மற்றும் location-க்கு அமைப்புகளைச் சேர்க்கவும்:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

   `<key>` ஐ உங்கள் Speech Service resource-க்கான API key-யால் மாற்றவும். `<location>` ஐ நீங்கள் Speech Service resource-ஐ உருவாக்கிய இடத்தால் மாற்றவும்.

1. இந்த செயலியில் `get-voices` என்ற புதிய HTTP trigger-ஐ கீழே உள்ள கட்டளையை பயன்படுத்தி உருவாக்கவும்:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

   இது `get-voices` என்ற HTTP trigger-ஐ உருவாக்கும்.

1. `get-voices` கோப்பகத்தில் உள்ள `__init__.py` கோப்பின் உள்ளடக்கத்தை பின்வரும் குறியீட்டால் மாற்றவும்:

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

   இந்த குறியீடு குரல்களைப் பெறும் endpoint-க்கு HTTP கோரிக்கையை உருவாக்குகிறது. இந்த குரல்களின் பட்டியல் அனைத்து மொழிகளுக்குமான குரல்களுடன் பெரிய JSON தொகுப்பாகும், எனவே கோரிக்கையின் உடலில் அனுப்பப்பட்ட மொழிக்கான குரல்கள் வடிகட்டப்படுகின்றன, பின்னர் shortname எடுக்கப்பட்டு JSON பட்டியலாக திருப்பி அனுப்பப்படுகிறது. உரையை குரலாக மாற்ற shortname தேவைப்படும், எனவே இந்த மதிப்பு மட்டுமே திருப்பி அனுப்பப்படுகிறது.

   > 💁 நீங்கள் விரும்பிய குரல்களை மட்டும் தேர்வு செய்ய, இந்த வடிகட்டலை தேவையானபடி மாற்றலாம்.

   இது 77KB (இந்த ஆவணத்தை எழுதும் நேரத்தில்) அளவிலிருந்து, மிகவும் சிறிய JSON ஆவணமாக தரவின் அளவைக் குறைக்கிறது. உதாரணமாக, US குரல்களுக்கு இது 408 bytes ஆகும்.

1. உங்கள் function app-ஐ உள்ளூர் முறையில் இயக்கவும். பின்னர், உங்கள் `text-to-timer` HTTP trigger-ஐ சோதித்தது போலவே, curl போன்ற ஒரு கருவியைப் பயன்படுத்தி இதை அழைக்கலாம். உங்கள் மொழியை JSON உடலாக அனுப்புவது உறுதிப்படுத்தவும்:

    ```json
    {
        "language":"<language>"
    }
    ```

   `<language>` ஐ உங்கள் மொழியால் மாற்றவும், உதாரணமாக `en-GB` அல்லது `zh-CN`.

> 💁 இந்த குறியீட்டை [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) கோப்பகத்தில் காணலாம்.

### பணிகள் - உங்கள் Wio Terminal-இல் இருந்து குரலைப் பெறுதல்

1. உங்கள் `smart-timer` திட்டத்தை VS Code-ல் திறக்கவும், அது ஏற்கனவே திறக்கப்படவில்லை என்றால்.

1. `config.h` தலைப்பு கோப்பைத் திறந்து, உங்கள் function app-க்கான URL-ஐச் சேர்க்கவும்:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

   `<URL>` ஐ உங்கள் function app-ல் உள்ள `get-voices` HTTP trigger-க்கான URL-ஆல் மாற்றவும். இது `TEXT_TO_TIMER_FUNCTION_URL` மதிப்புடன் ஒரே மாதிரியாக இருக்கும், ஆனால் `text-to-timer` என்பதற்குப் பதிலாக `get-voices` என்ற function பெயருடன் இருக்கும்.

1. `src` கோப்பகத்தில் புதிய கோப்பை உருவாக்கி, அதற்கு `text_to_speech.h` என்று பெயரிடவும். இது உரையை குரலாக மாற்ற ஒரு வகுப்பை வரையறுக்க பயன்படுத்தப்படும்.

1. புதிய `text_to_speech.h` கோப்பின் மேல் பின்வரும் include இயக்கங்களைச் சேர்க்கவும்:

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

1. இதற்கு கீழே பின்வரும் குறியீட்டைச் சேர்த்து, `TextToSpeech` வகுப்பை அறிவிக்கவும், மேலும் பயன்பாட்டின் மீதமுள்ள பகுதிகளில் பயன்படுத்தக்கூடிய ஒரு எடுத்துக்காட்டை அறிவிக்கவும்:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. உங்கள் functions app-ஐ அழைக்க, ஒரு WiFi client-ஐ அறிவிக்க வேண்டும். வகுப்பின் `private` பிரிவில் பின்வரும் குறியீட்டைச் சேர்க்கவும்:

    ```cpp
    WiFiClient _client;
    ```

1. `private` பிரிவில், தேர்ந்தெடுக்கப்பட்ட குரலுக்கான ஒரு புலத்தைச் சேர்க்கவும்:

    ```cpp
    String _voice;
    ```

1. `public` பிரிவில், முதல் குரலைப் பெற ஒரு `init` செயல்பாட்டைச் சேர்க்கவும்:

    ```cpp
    void init()
    {
    }
    ```

1. குரல்களைப் பெற, மொழியுடன் JSON ஆவணத்தை function app-க்கு அனுப்ப வேண்டும். இந்த JSON ஆவணத்தை உருவாக்க `init` செயல்பாட்டில் பின்வரும் குறியீட்டைச் சேர்க்கவும்:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. அடுத்ததாக ஒரு `HTTPClient` உருவாக்கி, function app-ஐ அழைக்கவும், JSON ஆவணத்தைப் பதிவேற்றவும்:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. இதற்கு கீழே, பதிலளிப்பு குறியீவைச் சரிபார்க்கவும், அது 200 (வெற்றி) என்றால், குரல்களின் பட்டியலை எடுத்து, பட்டியலிலிருந்து முதல் ஒன்றை மீட்டெடுக்கவும்:

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

1. இதற்குப் பிறகு, HTTP client இணைப்பை முடிக்கவும்:

    ```cpp
    httpClient.end();
    ```

1. `main.cpp` கோப்பைத் திறக்கவும், மேலும் இந்த புதிய தலைப்பு கோப்பை சேர்க்க பின்வரும் include இயக்கத்தை மேலே சேர்க்கவும்:

    ```cpp
    #include "text_to_speech.h"
    ```

1. `setup` செயல்பாட்டில், `speechToText.init();` அழைப்பின் கீழ், `TextToSpeech` வகுப்பை ஆரம்பிக்க பின்வருமாறு சேர்க்கவும்:

    ```cpp
    textToSpeech.init();
    ```

1. இந்த குறியீட்டை உருவாக்கி, அதை உங்கள் Wio Terminal-க்கு பதிவேற்றவும், மேலும் அதை சீரியல் மானிட்டர் மூலம் சோதிக்கவும். உங்கள் function app இயங்குவதை உறுதிப்படுத்தவும்.

   function app-ல் இருந்து திரும்பிய குரல்களின் பட்டியலையும், தேர்ந்தெடுக்கப்பட்ட குரலையும் நீங்கள் காணலாம்.

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

## உரையை குரலாக மாற்றுதல்

ஒரு குரலைப் பயன்படுத்த நீங்கள் தேர்வு செய்த பிறகு, அதை உரையை குரலாக மாற்ற பயன்படுத்தலாம். குரல்களுடன் உள்ள நினைவக வரம்புகள், உரையை குரலாக மாற்றும்போதும் பொருந்தும், எனவே நீங்கள் குரலை SD கார்டில் எழுத வேண்டும், பின்னர் அதை ReSpeaker மூலம் இயக்க வேண்டும்.

> 💁 இந்த திட்டத்தின் முந்தைய பாடங்களில், நீங்கள் மைக்ரோஃபோனில் இருந்து பிடிக்கப்பட்ட குரலை சேமிக்க flash memory-ஐ பயன்படுத்தினீர்கள். இந்த பாடத்தில், Seeed ஆடியோ நூலகங்களைப் பயன்படுத்தி SD கார்டிலிருந்து ஆடியோவை இயக்குவது எளிதாக இருப்பதால், SD கார்டை பயன்படுத்துகிறது.

மேலும் ஒரு வரம்பை கருத்தில் கொள்ள வேண்டும், அது Speech Service வழங்கும் கிடைக்கும் ஆடியோ தரவுகள் மற்றும் Wio Terminal ஆதரிக்கும் வடிவங்கள். முழு கணினிகளுக்கு மாறாக, மைக்ரோகண்ட்ரோலர்களுக்கான ஆடியோ நூலகங்கள் ஆதரிக்கும் ஆடியோ வடிவங்கள் மிகவும் வரையறுக்கப்பட்டவை. உதாரணமாக, ReSpeaker மூலம் ஒலியை இயக்கக்கூடிய Seeed Arduino Audio நூலகம் 44.1KHz மாதிரியின் வீதத்தில் மட்டுமே ஒலியை ஆதரிக்கிறது. Azure Speech Services பல வடிவங்களில் ஆடியோவை வழங்க முடியும், ஆனால் அவற்றில் எதுவும் இந்த மாதிரியின் வீதத்தைப் பயன்படுத்தாது, அவை 8KHz, 16KHz, 24KHz மற்றும் 48KHz மட்டுமே வழங்குகின்றன. எனவே, ஆடியோவை 44.1KHz-க்கு மீண்டும் மாதிரி எடுக்க வேண்டும், இது குறிப்பாக நினைவகத்தைப் பொருத்தவரை Wio Terminal-க்கு அதிகமான வளங்களை தேவைப்படும்.

இந்த மாதிரியான தரவுகளை கையாள வேண்டிய போது, குறிப்பாக வலை அழைப்பின் மூலம் தரவுகள் பெறப்பட்டால், serverless குறியீடுகளைப் பயன்படுத்துவது சிறந்தது. Wio Terminal ஒரு serverless function-ஐ அழைக்க முடியும், உரையை மாற்றுவதற்கான உரையை அனுப்பி, serverless function உரையை குரலாக மாற்ற Speech Service-ஐ அழைக்க முடியும், மேலும் ஆடியோவை தேவையான மாதிரி வீதத்திற்கு மீண்டும் மாதிரி எடுக்க முடியும். பின்னர், Wio Terminal தேவைப்படும் வடிவத்தில் ஆடியோவை திருப்பி அனுப்பி, அதை SD கார்டில் சேமித்து ReSpeaker மூலம் இயக்க முடியும்.

### பணிகள் - உரையை குரலாக மாற்ற serverless செயல்பாட்டை உருவாக்கவும்

1. உங்கள் `smart-timer-trigger` திட்டத்தை VS Code-ல் திறக்கவும், மற்றும் டெர்மினலை திறந்து, மெய்நிகர் சூழல் செயல்பாட்டில் உள்ளது என்பதை உறுதிப்படுத்தவும். இல்லையெனில், டெர்மினலை முடித்து மீண்டும் உருவாக்கவும்.

1. இந்த செயலியில் `text-to-speech` என்ற புதிய HTTP trigger-ஐ கீழே உள்ள கட்டளையை பயன்படுத்தி உருவாக்கவும்:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

   இது `text-to-speech` என்ற HTTP trigger-ஐ உருவாக்கும்.

1. [librosa](https://librosa.org) என்ற Pip package-ல் ஆடியோவை மீண்டும் மாதிரி எடுக்க செயல்பாடுகள் உள்ளன, எனவே இதை `requirements.txt` கோப்பில் சேர்க்கவும்:

    ```sh
    librosa
    ```

   இதைச் சேர்த்த பிறகு, VS Code டெர்மினலில் பின்வரும் கட்டளையைப் பயன்படுத்தி Pip packages-ஐ நிறுவவும்:

    ```sh
    pip install -r requirements.txt
    ```

   > ⚠️ நீங்கள் Linux, குறிப்பாக Raspberry Pi OS-ஐப் பயன்படுத்தினால், பின்வரும் கட்டளையைப் பயன்படுத்தி `libsndfile` ஐ நிறுவ வேண்டும்:
   >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. உரையை குரலாக மாற்ற, Speech API key-ஐ நேரடியாகப் பயன்படுத்த முடியாது, அதற்கு பதிலாக, API key-ஐ பயன்படுத்தி Access Token கோரிக்கையை அங்கீகரிக்க வேண்டும். `text-to-speech` கோப்பகத்தில் உள்ள `__init__.py` கோப்பைத் திறந்து, அதில் உள்ள அனைத்து குறியீடுகளையும் பின்வரும் குறியீட்டால் மாற்றவும்:

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

   இது settings-ல் இருந்து location மற்றும் speech key-க்கு நிரந்தரங்களை வரையறுக்கிறது. பின்னர், Speech Service-க்கு Access Token-ஐ பெற `get_access_token` செயல்பாட்டை வரையறுக்கிறது.

1. இந்தக் குறியீட்டின் கீழே பின்வரும் குறியீட்டைச் சேர்க்கவும்:

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

   இது உரையை குரலாக மாற்றும் HTTP trigger-ஐ வரையறுக்கிறது. இது உரையை மாற்ற, மொழி மற்றும் குரலை JSON உடலிலிருந்து எடுத்து, SSML-ஐ உருவாக்கி, Access Token-ஐப் பயன்படுத்தி REST API அழைப்பைச் செய்கிறது. இந்த REST API அழைப்பு 16-bit, 48KHz mono WAV கோப்பாக குறியாக்கப்பட்ட ஆடியோவை திருப்பி அனுப்புகிறது, இது `playback_format` மதிப்பால் வரையறுக்கப்பட்டுள்ளது.

   பின்னர், இது `librosa` மூலம் 48KHz மாதிரி வீதத்திலிருந்து 44.1KHz மாதிரி வீதத்திற்கு மீண்டும் மாதிரி எடுக்கப்படுகிறது, பின்னர் இந்த ஆடியோ ஒரு பைனரி பஃபரில் சேமிக்கப்படுகிறது, பின்னர் இது திருப்பி அனுப்பப்படுகிறது.

1. உங்கள் function app-ஐ உள்ளூர் முறையில் இயக்கவும் அல்லது மேகத்துக்கு அனுப்பவும். பின்னர், உங்கள் `text-to-timer` HTTP trigger-ஐ சோதித்தது போலவே, curl போன்ற ஒரு கருவியைப் பயன்படுத்தி இதை அழைக்கலாம். மொழி, குரல் மற்றும் உரையை JSON உடலாக அனுப்புவது உறுதிப்படுத்தவும்:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

   `<language>` ஐ உங்கள் மொழியால் மாற்றவும், உதாரணமாக `en-GB` அல்லது `zh-CN`. `<voice>` ஐ நீங்கள் பயன்படுத்த விரும்பும் குரலால் மாற்றவும். `<text>` ஐ நீங்கள் குரலாக மாற்ற விரும்பும் உரையால் மாற்றவும். வெளியீட்டை ஒரு கோப்பில் சேமித்து, எந்தவொரு WAV ஆடியோ பிளேயரிலும் அதை இயக்கலாம்.

   உதாரணமாக, "Hello" என்பதை US English-ல் Jenny Neural குரலுடன் குரலாக மாற்ற, function app உள்ளூர் முறையில் இயங்கும்போது, பின்வரும் curl கட்டளையைப் பயன்படுத்தலாம்:

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

   இது `hello.wav` என்ற பெயரில் தற்போதைய அடைவில் ஆடியோவை சேமிக்கும்.

> 💁 இந்த குறியீட்டை [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) கோப்பகத்தில் காணலாம்.

### பணிகள் - உங்கள் Wio Terminal-இல் இருந்து குரலைப் பெறுதல்

1. உங்கள் `smart-timer` திட்டத்தை VS Code-ல் திறக்கவும், அது ஏற்கனவே திறக்கப்படவில்லை என்றால்.

1. `config.h` தலைப்பு கோப்பைத் திறந்து, உங்கள் function app-க்கான URL-ஐச் சேர்க்கவும்:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

   `<URL>` ஐ உங்கள் function app-ல் உள்ள `text-to-speech` HTTP trigger-க்கான URL-ஆல் மாற்றவும். இது `TEXT_TO_TIMER_FUNCTION_URL` மதிப்புடன் ஒரே மாதிரியாக இருக்கும், ஆனால் `text-to-timer` என்பதற்குப் பதிலாக `text-to-speech` என்ற function பெயருடன் இருக்கும்.

1. `text_to_speech.h` தலைப்பு கோப்பைத் திறந்து, `TextToSpeech` வகுப்பின் `public` பிரிவில் பின்வரும் முறைசார்ந்த செயல்பாட்டைச் சேர்க்கவும்:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. `convertTextToSpeech` முறையில், function app-க்கு அனுப்ப JSON-ஐ உருவாக்க பின்வரும் குறியீட்டைச் சேர்க்கவும்:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

   இது மொழி, குரல் மற்றும் உரையை JSON ஆவணத்தில் எழுதுகிறது, பின்னர் அதை ஒரு சரியாக மாற்றுகிறது.

1. இதற்கு கீழே, function app-ஐ அழைக்க பின்வரும் குறியீட்டைச் சேர்க்கவும்:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

   இது ஒரு HTTPClient-ஐ உருவாக்கி, பின்னர் JSON ஆவணத்தைப் பயன்படுத்தி text to speech HTTP trigger-க்கு POST கோரிக்கையைச் செய்கிறது.

1. அழைப்பு வேலை செய்கின்றது என்றால், function app அழைப்பிலிருந்து திரும்பிய பைனரி தரவை SD கார்டில் உள்ள ஒரு கோப்புக்கு ஸ்ட்ரீம் செய்யலாம். இதைச் செய்ய பின்வரும் குறியீட்டைச் சேர்க்கவும்:

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

   இந்த குறியீடு பதிலளிப்பைச் சரிபார்க்கிறது, மேலும் அது 200 (வெற்றி) என்றால், பைனரி தரவை SD கார்டின் மூலத்தில் உள்ள `SPEECH.WAV` என்ற கோப்புக்கு ஸ்ட்ரீம் செய்கிறது.

1. இந்த முறையின் முடிவில், HTTP இணைப்பை மூடவும்:

    ```cpp
    httpClient.end();
    ```

1. பேச வேண்டிய உரை இப்போது ஆடியோவாக மாற்றப்படலாம். `main.cpp` கோப்பில், `say` செயல்பாட்டின் இறுதியில் கீழே உள்ள வரியை சேர்த்து உரையை ஆடியோவாக மாற்றவும்:

    ```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### பணிகள் - உங்கள் Wio Terminal-ல் ஆடியோவை இயக்கவும்

**விரைவில் வரும்**

## உங்கள் functions app-ஐ மேகத்தில் பிரசுரித்தல்

Functions app-ஐ உள்ளூரில் இயக்குவதற்கான காரணம், Linux-ல் உள்ள `librosa` Pip package ஒரு dependency library-ஐ கொண்டுள்ளது, இது இயல்பாக நிறுவப்படவில்லை, மேலும் function app இயங்குவதற்கு முன் நிறுவப்பட வேண்டும். Function apps serverless ஆகும் - நீங்கள் நிர்வகிக்கக்கூடிய server-கள் இல்லை, எனவே இந்த library-ஐ முன்கூட்டியே நிறுவ வழியில்லை.

இதற்கான வழி, functions app-ஐ Docker container-ஐ பயன்படுத்தி பிரசுரிப்பதாகும். இந்த container, function app-க்கு புதிய instance-ஐ உருவாக்க தேவையான போது (உதாரணமாக, demand கிடைக்கக்கூடிய resources-ஐ மீறும்போது, அல்லது function app சில காலமாக பயன்படுத்தப்படாமல் இருந்தால் மற்றும் மூடப்பட்டால்) மேகத்தால் பிரசுரிக்கப்படுகிறது.

Linux-ல் custom container-ஐ பயன்படுத்தி function app-ஐ உருவாக்கி Docker மூலம் deploy செய்யும் வழிமுறைகளை [Microsoft Docs-ல் உள்ள Linux custom container documentation](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python) இல் காணலாம்.

இதை deploy செய்த பிறகு, உங்கள் Wio Terminal code-ஐ இந்த function-ஐ அணுக port செய்யலாம்:

1. Azure Functions சான்றிதழை `config.h`-க்கு சேர்க்கவும்:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. `<WiFiClient.h>` உள்ளீடுகளை `<WiFiClientSecure.h>`-க்கு மாற்றவும்.

1. அனைத்து `WiFiClient` புலங்களை `WiFiClientSecure`-க்கு மாற்றவும்.

1. `WiFiClientSecure` புலம் கொண்ட ஒவ்வொரு வகுப்பிலும், ஒரு constructor-ஐ சேர்த்து, அந்த constructor-ல் சான்றிதழை அமைக்கவும்:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

**குறிப்பு**:  
இந்த ஆவணம் [Co-op Translator](https://github.com/Azure/co-op-translator) என்ற AI மொழிபெயர்ப்பு சேவையைப் பயன்படுத்தி மொழிபெயர்க்கப்பட்டுள்ளது. நாங்கள் துல்லியத்திற்காக முயற்சிக்கின்றோம், ஆனால் தானியங்கி மொழிபெயர்ப்புகளில் பிழைகள் அல்லது தவறான தகவல்கள் இருக்கக்கூடும் என்பதை கவனத்தில் கொள்ளவும். அதன் தாய்மொழியில் உள்ள மூல ஆவணம் அதிகாரப்பூர்வ ஆதாரமாக கருதப்பட வேண்டும். முக்கியமான தகவல்களுக்கு, தொழில்முறை மனித மொழிபெயர்ப்பு பரிந்துரைக்கப்படுகிறது. இந்த மொழிபெயர்ப்பைப் பயன்படுத்துவதால் ஏற்படும் எந்த தவறான புரிதல்கள் அல்லது தவறான விளக்கங்களுக்கு நாங்கள் பொறுப்பல்ல.