# អត្ថបទទៅសំឡេង - Wio Terminal

នៅផ្នែកនេះនៃមេរៀន អ្នកនឹងបម្លែងអត្ថបទទៅសំឡេង ដើម្បីផ្តល់ព័ត៌មានត្រឡប់ជាពាក្យនិយាយ។

## អត្ថបទទៅសំឡេង

SDK សេវាសំឡេងដែលអ្នកបានប្រើនៅមេរៀនមុន ដើម្បីបម្លែងសំឡេងទៅអត្ថបទ អាចប្រើបានដើម្បីបម្លែងអត្ថបទទៅសំឡេងវិញ។

## ទទួលបានបញ្ជីសំឡេង

នៅពេលស្នើសុំសំឡេង អ្នកត្រូវផ្តល់សំឡេងដែលត្រូវប្រើ ដោយសំឡេងអាចត្រូវបង្កើតដោយប្រើសំឡេងផ្សេងៗគ្នាជាច្រើន។ ភាសាក្នុងមួយក្នុងសមស្សម៍គាំទ្រសំឡេងផ្សេងៗនានា ហើយអ្នកអាចទទួលបានបញ្ជីសំឡេងដែលគាំទ្រសម្រាប់ភាសាទាំងនោះពី SDK សេវាសំឡេង។ ការដាក់បញ្ចូលរបស់មីក្រូកុងតូឡឺរ មានកំណត់នៅទីនេះ - ការ អូសបញ្ជីសំឡេងដែលគាំទ្រដោយសេវាអត្ថបទទៅសំឡេងគឺជា​ឯកសារ JSON ដែលមានទំហំលើស ៧៧KB ដែលធំពេកសម្រាប់ Wio Terminal ដំណើរការ។ នៅពេលសរសេរ បញ្ជីពេញរួមមានសំឡេង ២១៥ នាក់ មួយៗត្រូវបានកំណត់ដោយឯកសារ JSON ដូចខាងក្រោម៖

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

JSON នេះសម្រាប់សំឡេង **Aria** ដែលមានរចនាប័ទ្មសំឡេងច្រើន។ អ្វីដែលត្រូវការនៅពេលបម្លែងអត្ថបទទៅសំឡេងគឺហៅជា shortname, `en-US-AriaNeural`។

ជំនួសការទាញយកនិងដកលេខចេញពីបញ្ជីនេះទាំងមូលនៅលើមីក្រូកុងតូឡឺរ របស់អ្នក អ្នកត្រូវតែសរសេរកូដ serverless បន្ថែម មួយកូដ ដើម្បីទាញបញ្ជីសំឡេងសម្រាប់ភាសាដែលអ្នកប្រើ ហើយហៅវាពី Wio Terminal របស់អ្នក។ កូដរបស់អ្នកអាចបញ្ជ្រើសសំឡេងដែលសមរម្យពីបញ្ជី ដូចជាសំឡេងដំបូងដែលវាចាប់បាន។

### កិច្ចការ - បង្កើតក័ណកម្មមិនមានម៉ាស៊ីនមេដើម្បីទទួលបញ្ជីសំឡេង

1. បើកគម្រោង `smart-timer-trigger` របស់អ្នកក្នុង VS Code ហើយបើក terminal ដើម្បីប្រាកដថាវបើកបរិយាកាសវីរិយៈ។ ប្រសិនបើគ្មាន សូមបិទហើយបើក terminal ថ្មីឡើងវិញ។

1. បើកឯកសារ `local.settings.json` ហើយបន្ថែមការកំណត់ៈសម្រាប់ speech API សោនិងទីតាំង៖

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    ជំនួស `<key>` ជាមួយសោ API សម្រាប់ធនធានសេវាសំឡេងរបស់អ្នក។ ជំនួស `<location>` ជាមួយទីតាំងដែលអ្នកបានប្រើពេលបង្កើតធនធានសេវាសំឡេង។

1. បន្ថែមសោHTTP trigger ថ្មីមួយឈ្មោះ `get-voices` សម្រាប់កម្មវិធីនេះ ដោយប្រើពាក្យបញ្ជាខាងក្រោមពីក្នុង terminal VS Code នៅកំណត់តិបថėមគម្រោង functions app ដែលជារាងកំណត់ផ្សេងៗ៖

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    នេះនឹងបង្កើត HTTP trigger មួយឈ្មោះ `get-voices`។

1. ជំនួសមាតិកានៃឯកសារ `__init__.py` នៅក្នុងថត `get-voices` ជាមួយ​ស្នាដៃខាងក្រោម៖

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

    កូដនេះធ្វើសំណើ HTTP ទៅផ្លូវចូលបង្ហាញសំឡេង។ បញ្ជីសំឡេងនេះជាប្លក់ JSON ធំសម្រាប់សំឡេងសម្រាប់ភាសាទាំងអស់ ដូច្នេះសំឡេងសម្រាប់ភាសាដែលបានផ្ញើក្នុងខ្លឹមសារស្នើសុំត្រូវបានតម្រៀបចេញ ហើយបន្ទាប់មក shortname ត្រូវបានដកចេញ ហើយត្រឡប់មកជាបញ្ជី JSON។ shortname គឺជាតំលៃដែលចាំបាច់ក្នុងការបម្លែងអត្ថបទទៅសំឡេង ដូច្នេះត្រឹមតែតំលៃនេះត្រូវបានត្រឡប់តែប៉ុណ្ណោះ។

    > 💁 អ្នកអាចផ្លាស់ប្ដូរតម្រងទៅតាមតម្រូវការ ដើម្បីជ្រើសរើសតែសំឡេងដែលអ្នកចង់បាន។

    នេះកាត់បន្ថយទំហំទិន្នន័យពី ៧៧KB (នៅពេលសរសេរ) ទៅឯកសារ JSON ដែលតូចជាងនេះយ៉ាងខ្លាំង។ ឧទាហរណ៍ សំឡេងសម្រាប់ US គឺមានទំហំ ៤០៨ បៃ។

1. ដំណើរការកម្មវិធី function app របស់អ្នកនៅក្នុងកន្លែង។ បន្ទាប់មក អ្នកអាចហៅវា ដោយប្រើឧបករណ៍ដូចជា curl ដូចជាវិធីសាស្រ្តដែលអ្នកបានសាកល្បង `text-to-timer` HTTP trigger។ ប្រាកដថាអ្នកផ្ញើភាសារបស់អ្នកជាគ្រឿងខាង JSON៖

    ```json
    {
        "language":"<language>"
    }
    ```

    ជំនួស `<language>` ជាមួយភាសារបស់អ្នក ដូចជា `en-GB` ឬ `zh-CN`។

> 💁 អ្នកអាចស្វែងរកកូដនេះនៅក្នុងថត [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions)។

### កិច្ចការ - ទាញយកសំឡេងពី Wio Terminal របស់អ្នក

1. បើកគម្រោង `smart-timer` ក្នុង VS Code ប្រសិនបើវាមិនទាន់បើកជាមួយទេ។

1. បើកឯកសារ header `config.h` ហើយបន្ថែម URL សម្រាប់កម្មវិធី function app របស់អ្នក៖

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    ជំនួស `<URL>` ជាមួយ URL សម្រាប់ `get-voices` HTTP trigger នៅលើកម្មវិធី function app របស់អ្នក។ នេះគឺដូចដែលមានតម្លៃសម្រាប់ `TEXT_TO_TIMER_FUNCTION_URL` ប៉ុន្តែជាមួយឈ្មោះ function ជា `get-voices` ជំនួស `text-to-timer`។

1. បង្កើតឯកសារថ្មីក្នុងថត `src` ឈ្មោះ `text_to_speech.h`។ វានឹងត្រូវប្រើសម្រាប់កំណត់ក្លាសផ្លាស់ប្តូរពីអត្ថបទទៅសំឡេង។

1. បន្ថែមការបញ្ចូលដូចខាងក្រោមនៅលើបន្ទាត់ថ្មី `text_to_speech.h` ថ្មី៖

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

1. បន្ថែមកូដខាងក្រោមនេះដើម្បីប្រកាសក្លាស `TextToSpeech` រួមជាមួយវត្ថុមួយដែលអាចប្រើបាននៅក្នុងកម្មវិធីភាគច្រើន៖

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. ដើម្បីហៅកម្មវិធី functions app របស់អ្នក អ្នកត្រូវប្រកាស WiFi client។ បន្ថែមកូដខាងក្រោមទៅផ្នែក `private` របស់ក្លាស៖

    ```cpp
    WiFiClient _client;
    ```

1. នៅផ្នែក `private` បន្ថែមវាលមួយសម្រាប់សំឡេងដែលបានជ្រើសរើស៖

    ```cpp
    String _voice;
    ```

1. ទៅផ្នែក `public` បន្ថែមមុខងារ `init` មួយដែលនឹងទទួលសំឡេងដំបូង៖

    ```cpp
    void init()
    {
    }
    ```

1. ដើម្បីទទួលបានសំឡេង មួយឯកសារ JSON ត្រូវបានផ្ញើទៅកម្មវិធី function app ជាមួយភាសា។ បន្ថែមកូដខាងក្រោមទៅមុខងារ `init` ដើម្បីបង្កើតឯកសារ JSON នេះ៖

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. បន្ទាប់បង្កើត `HTTPClient` ហើយប្រើវាហៅ function app ដើម្បីទទួលសំឡេងដោយបញ្ជូនឯកសារ JSON ៖

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. ខាងក្រោមនេះ បន្ថែមកូដត្រួតពិនិត្យលេខកូដចំលើយ ប្រសិនបើវាគឺ ២០០ (ជោគជ័យ) ដកបញ្ជីសំឡេង ហើយយកសំឡេងដំបូងក្នុងបញ្ជី៖

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

1. បន្ទាប់មក បញ្ចប់ការតភ្ជាប់ HTTP client៖

    ```cpp
    httpClient.end();
    ```

1. បើកឯកសារ `main.cpp` ហើយបន្ថែមការបញ្ចូលខាងក្រោមនៅចំណុចខ្ពស់ដើម្បីបញ្ចូលឯកសារ header ថ្មីនេះ៖

    ```cpp
    #include "text_to_speech.h"
    ```

1. នៅមុខងារ `setup` ក្រោមការហៅ `speechToText.init();` បន្ថែមខាងក្រោមដើម្បីធ្វើការចាប់ផ្តើមក្លាស `TextToSpeech`៖

    ```cpp
    textToSpeech.init();
    ```

1. សង់កូដនេះ ផ្ទុកវាទៅកាន់ Wio Terminal របស់អ្នក ហើយសាកល្បងតាមរយៈផ្ទាំងម៉ូនីទ័រ serial។ ប្រាកដថាកម្មវិធី function app របស់អ្នកកំពុងដំណើរការ។

    អ្នកនឹងឃើញបញ្ជីសំឡេងដែលអាចប្រើប្រាស់បានត្រឡប់មកពី function app រួមជាមួយសំឡេងដែលបានជ្រើសរើស។

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

## បម្លែងអត្ថបទទៅសំឡេង

ពេលដែលអ្នកមានសំឡេងដែលចង់ប្រើ វាអាចប្រើសម្រាប់បម្លែងអត្ថបទទៅសំឡេង។ កំណត់ចំណុចវាំងននជាមួយសំឡេងក៏មាននៅពេលបម្លែងសំឡេងទៅអត្ថបទដែរ ដូច្នេះអ្នកត្រូវតែរាយការណ៍សំឡេងទៅកាត SD ដើម្បីអាចចាក់សំឡេងតាម ReSpeaker។

> 💁 នៅមេរៀនមុនក្នុងគម្រោងនេះ អ្នកបានប្រើ flash memory ដើម្បីផ្ទុកសំឡេងដែលបានចាប់ពីមីក្រូហ្វូន។ មេរៀននេះប្រើកាត SD ព្រោះវាសមរម្យជាងសម្រាប់ចាក់សំឡេងដោយប្រើបណ្ណាល័យសំឡេង Seeed។

មានកំណត់បន្ថែមមួយទៀតដែលត្រូវគិតទុក ដូចជា ទិន្នន័យសំឡេងដែលមានពីសេវាសំឡេង និងទ្រង់ទ្រាយដែល Wio Terminal គាំទ្រ។ ខុសពីកុំព្យូទ័រពេញលេញ បណ្ណាល័យសំឡេងសម្រាប់មីក្រូកុងតូឡឺរអាចមានកំណត់ខ្លាំងខាងទ្រង់ទ្រាយសំឡេង។ ឧទាហរណ៍ បណ្ណាល័យ Seeed Arduino Audio ដែលអាចចាក់សំឡេងតាម ReSpeaker គឺគាំទ្រសំឡេង Sample rate 44.1KHz តែប៉ុណ្ណោះ។ សេវាសំឡេង Azure អាចផ្តល់សំឡេងក្នុងទ្រង់ទ្រាយមួយចំនួន ប៉ុន្តែមិនមានទ្រង់ទ្រាយ 44.1KHz ទេ វាផ្តល់តែ 8KHz, 16KHz, 24KHz និង 48KHz។ នេះមានន័យថាសំឡេងត្រូវបាន sample rate សារភាពទៅ 44.1KHz ដែលត្រូវការធនធានលើស Wio Terminal មាន ជាពិសេសផ្នែកអង្គចងចាំ។

ពេលត្រូវកែប្រែទិន្នន័យដូចនេះ ជាជាងប្រើ Wio Terminal ដោយផ្ទាល់ គឺល្អប្រសើរជាងក្នុងការប្រើកូដ serverless។ Wio Terminal អាចហៅក័ណកម្មមិនមានម៉ាស៊ីនមេមួយ ដោយផ្ញើអត្ថបទដែលត្រូវបម្លែង ហើយក័ណកម្មនេះអាចហៅសេវាសំឡេងដើម្បីបម្លែងអត្ថបទទៅសំឡេង និងអាច sample rate ជាថ្មីទៅ 44.1KHz។ បន្ទាប់មក វាអាចត្រឡប់សំឡេងនោះក្នុងទ្រង់ទ្រាយដែល Wio Terminal នឹងផ្ទុកនៅលើកាត SD ហើយចាក់តាម ReSpeaker។

### កិច្ចការ - បង្កើតក័ណកម្មមិនមានម៉ាស៊ីនមេដើម្បីបម្លែងអត្ថបទទៅសំឡេង

1. បើកគម្រោង `smart-timer-trigger` របស់អ្នកក្នុង VS Code ហើយបើក terminal ដើម្បីប្រាកដថាបរិយាកាសវីរិយៈត្រូវបានបើក។ ប្រសិនបើគ្មាន សូមបិទហើយបើក terminal ថ្មីឡើងវិញ។

1. បន្ថែម HTTP trigger ថ្មីមួយឈ្មោះ `text-to-speech` សម្រាប់កម្មវិធីនេះ ដោយប្រើពាក្យបញ្ជាខាងក្រោមពីក្នុង terminal VS Code នៅកំណត់តិបថėមគម្រោង functions app៖

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    នេះនឹងបង្កើត HTTP trigger ឈ្មោះ `text-to-speech`។

1. package Pip នៃ [librosa](https://librosa.org) មានមុខងារសម្រាប់ធ្វើការបម្រុងសំឡេង sample rate ដូច្នេះបន្ថែមវាទៅឯកសារ `requirements.txt`៖

    ```sh
    librosa
    ```

    បន្ទាប់បន្ថែមរួច តំឡើង package Pip ដោយប្រើពាក្យបញ្ជាខាងក្រោមពីក្នុង terminal VS Code៖

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ ប្រសិនបើអ្នកប្រើ Linux រួមទាំង Raspberry Pi OS អ្នកអាចត្រូវតំឡើង `libsndfile` ដោយប្រើពាក្យបញ្ជាខាងក្រោម៖
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. ដើម្បីបម្លែងអត្ថបទទៅសំឡេង អ្នកមិនអាចប្រើកូនសោ API speech ទៅដោយផ្ទាល់ទេ ត្រូវស្នើសុំ token ចូល ប្រើកូនសោ API ដើម្បីផ្ទៀងផ្ទាត់សំណើសុំ token។ បើកឯកសារ `__init__.py` នៅក្នុងថត `text-to-speech` ហើយជំនួសកូដទាំងអស់ក្នុងឯកសារនេះជាមួយកូដខាងក្រោម៖

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

    នេះកំណត់អថេរតំបន់ និងសោសំឡេង ដែលនឹងត្រូវអានពីការកំណត់។ បន្ទាប់មកកំណត់មុខងារ `get_access_token` ដែលនឹងទាញយក access token សម្រាប់សេវាសំឡេង។

1. ខាងក្រោមកូដនេះ បន្ថែម៖

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

    នេះកំណត់ HTTP trigger ដែលបម្លែងអត្ថបទទៅសំឡេង។ វាដកអត្ថបទដែលត្រូវបម្លែង ភាសា និងសំឡេងពីខ្លឹមសារបញ្ជូន JSON ទៅសំណើ ហើយកសាង SSML ដើម្បីស្នើសុំសំឡេង បន្ទាប់ហៅ REST API ដោយផ្ទៀងផ្ទាត់ការចូលប្រើគ្រប់គ្រាន់។ ការហៅ REST API នេះត្រឡប់តម្លៃសំឡេងដែល encode ជា 16-bit, 48KHz mono WAV ដែលកំណត់ដោយតម្លៃ `playback_format` ដែលបញ្ជូនទៅ REST API call។

    វាត្រូវបានធ្វើ sample rate ជាថ្មីដោយ `librosa` ពី sample rate 48KHz ទៅ 44.1KHz បន្ទាប់សំឡេងត្រូវបានរក្សាទុកទៅក្នុងបណ្ដាលីង binary buffer ហើយត្រូវបានត្រឡប់ត្រឡប់ពី function។

1. ដំណើរការកម្មវិធី function app របស់អ្នកនៅក្នុងកន្លែង ឬបង្ហោះវាទៅពពក។ បន្ទាប់មក អ្នកអាចហៅវា ដោយប្រើ ឧបករណ៍ដូចជាគឺ curl ដូចដែលបានសាកល្បង `text-to-timer` HTTP trigger។ ប្រាកដថាអ្នកផ្ញើភាសា សំឡេង និងអត្ថបទ ជាគ្រឿង JSON body៖

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    ជំនួស `<language>` ជាមួយភាសារបស់អ្នក ដូចជា `en-GB` ឬ `zh-CN`។ ជំនួស `<voice>` ជាមួយសំឡេងដែលអ្នកចង់ប្រើ។ ជំនួស `<text>` ជាមួយអត្ថបទដែលអ្នកចង់បម្លែងទៅសំឡេង។ អ្នកអាចរក្សាទុកលទ្ធផលទៅឯកសារ ហើយចាក់វាជាមួយកម្មវិធីចាក់សំឡេងណាមួយដែលអាចចាក់ឯកសារ WAV បាន។

    ឧទាហរណ៍ ដើម្បីបម្លែង "Hello" ទៅសំឡេងជាភាសា អង់គ្លេស US ជាមួយសំឡេង Jenny Neural ដែល function app កំពុងដំណើរការអោយនៅក្នុងកន្លែង អ្នកអាចប្រើពាក្យបញ្ជា curl ខាងក្រោម៖

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

    នេះនឹងរក្សាសំឡេងទៅឯកសារ `hello.wav` នៅក្នុងថតបច្ចុប្បន្ន។

> 💁 អ្នកអាចស្វែងរកកូដនេះនៅក្នុងថត [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions)។

### កិច្ចការ - ទាញយកសំឡេងពី Wio Terminal របស់អ្នក

1. បើកគម្រោង `smart-timer` ក្នុង VS Code ប្រសិនបើវាមិនទាន់បើកប្រើទេ។

1. បើកឯកសារ header `config.h` ហើយបន្ថែម URL សម្រាប់កម្មវិធី function app របស់អ្នក៖

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    ជំនួស `<URL>` ជាមួយ URL សម្រាប់ `text-to-speech` HTTP trigger នៅលើកម្មវិធី function app របស់អ្នក។ នេះគឺដូចដែលមានតម្លៃសម្រាប់ `TEXT_TO_TIMER_FUNCTION_URL` ប៉ុន្តែជាមួយឈ្មោះ function ជា `text-to-speech` ជំនួស `text-to-timer`។

1. បើកឯកសារ header `text_to_speech.h` ហើយបន្ថែមមុខងារខាងក្រោមទៅផ្នែក `public` របស់ក្លាស `TextToSpeech`៖

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. ទៅមុខងារ `convertTextToSpeech` បន្ថែមកូដខាងក្រោមដើម្បីបង្កើត JSON សម្រាប់ផ្ញើទៅ function app៖

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    នេះសរសេរភាសា សំឡេង និងអត្ថបទទៅឯកសារ JSON បន្ទាប់ serialize វាទៅជាស្ទ្រង់។

1. ខាងក្រោមនេះ បន្ថែមកូដហៅ function app៖

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    នេះបង្កើត HTTPClient បន្ទាប់ធ្វើសំណើ POST ដោយប្រើ JSON ទៅ http trigger text to speech ។

1. ប្រសិនបើការហៅនេះជោគជ័យ ទិន្នន័យ binary ចុងក្រោយដែលបានត្រឡប់ពី function app អាចត្រូវបានផ្សព្វផ្សាយទៅឯកសារមួយនៅលើកាត SD។ បន្ថែមកូដខាងក្រោមសម្រាប់ធ្វើដូច្នេះ៖

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

    កូដនេះពិនិត្យសំណើចំលើយ ប្រសិនបើវាជា ២០០ (ជោគជ័យ) ទិន្នន័យ binary នឹងត្រូវផ្សព្វផ្សាយទៅឯកសារ `SPEECH.WAV` នៅក្នុងថតស្ដាំឬ root នៃកាត SD។

1. នៅចុងបញ្ចប់មុខងារនេះ បិទការតភ្ជាប់ HTTP៖

    ```cpp
    httpClient.end();
    ```

1. អត្ថបទដែលត្រូវនិយាយឥឡូវនេះអាចត្រូវបានបម្លែងទៅសំឡេង។ នៅក្នុងឯកសារ `main.cpp` បន្ថែមបន្ទាត់ខាងក្រោមនៅចុងមុខងារ `say` ដើម្បីបម្លែងអត្ថបទឲ្យទៅជា សំឡេង៖

    ```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### កិច្ចការ - ចាក់សំឡេងពី Wio Terminal របស់អ្នក

**មកឆាប់ៗนี้**
## ការដាក់ពាក្យកម្មវិធី functions របស់អ្នកទៅកាន់ពពក

ហេតុផលសម្រាប់ការរត់កម្មវិធី functions នៅក្នុងមូលដ្ឋានគឺដោយសារបណ្ណាល័យ `librosa` Pip នៅលើ linux មានការពឹងផ្អែកលើបណ្ណាល័យមួយដែលមិនត្រូវបានដំឡើងដោយលំនាំដើម ហើយត្រូវការត្រូវបានដំឡើងមុនពេលកម្មវិធី function អាចរត់បាន។ កម្មវិធី function គឺជាបណ្តាញមិនមានម៉ាស៊ីនបម្រើ - មិនមានម៉ាស៊ីនបម្រើដែលអ្នកអាចគ្រប់គ្រងដោយខ្លួនឯងទេ ដូច្នេះមិនមានវិធីណាដើម្បីដំឡើងបណ្ណាល័យនេះជាមុនទេ។

វិធីធ្វើនេះគឺជាការដាក់ពាក្យកម្មវិធី functions របស់អ្នកតាមរយៈធុង Docker មួយ។ ធុងនេះត្រូវបានដាក់បង្ហោះដោយពពករាល់ពេលវាត្រូវការបើកឱ្យមានឯកត្តិកម្មថ្មីមួយសម្រាប់កម្មវិធី function របស់អ្នក (ដូចជា ពេលដែលការទាមទារលើសធនធានដែលមានស្រាប់ ឬបើកម្មវិធី function មិនបានប្រើប្រាស់រយៈពេលខ្លះហើយត្រូវបានបិទ)។

អ្នកអាចស្វែងរកការណែនាំដើម្បីដំឡើងកម្មវិធី function និងដាក់បង្ហោះតាមរយៈ Docker នៅក្នុង [ការបង្កើត function លើ Linux ប្រើ ធុងផ្ទាល់ខ្លួន ដោយឯកសារ Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python)។

ពេលនេះបន្ទាប់ពីបានដាក់បង្ហោះហើយ អ្នកអាចផ្ទេរកូដ Wio Terminal របស់អ្នកដើម្បីចូលដំណើរការមុខងារនេះ៖

1. បន្ថែមវិញ្ញាបនបត្រ Azure Functions ទៅកាន់ `config.h`:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "MIIFWjCCBEKgAwIBAgIQDxSWXyAgaZlP1ceseIlB4jANBgkqhkiG9w0BAQsFADBa\r\n"
        "MQswCQYDVQQGEwJJRTESMBAGA1UEChMJQmFsdGltb3JlMRMwEQYDVQQLEwpDeWJl\r\n"
        "clRydXN0MSIwIAYDVQQDExlCYWx0aW1vcmUgQ3liZXJUcnVzdCBSb290MB4XDTIw\r\n"
        "MDcyMTIzMDAwMFoXDTI0MTAwODA3MDAwMFowTzELMAkGA1UEBhMCVVMxHjAcBgNV\r\n"
        "BAoTFU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjEgMB4GA1UEAxMXTWljcm9zb2Z0IFJT\r\n"
        "QSBUTFMgQ0EgMDEwggIiMA0GCSqGSIb3DQEBAQUAA4ICDwAwggIKAoICAQCqYnfP\r\n"
        "mmOyBoTzkDb0mfMUUavqlQo7Rgb9EUEf/lsGWMk4bgj8T0RIzTqk970eouKVuL5R\r\n"
        "IMW/snBjXXgMQ8ApzWRJCZbar879BV8rKpHoAW4uGJssnNABf2n17j9TiFy6BWy+\r\n"
        "IhVnFILyLNK+W2M3zK9gheiWa2uACKhuvgCca5Vw/OQYErEdG7LBEzFnMzTmJcli\r\n"
        "W1iCdXby/vI/OxbfqkKD4zJtm45DJvC9Dh+hpzqvLMiK5uo/+aXSJY+SqhoIEpz+\r\n"
        "rErHw+uAlKuHFtEjSeeku8eR3+Z5ND9BSqc6JtLqb0bjOHPm5dSRrgt4nnil75bj\r\n"
        "c9j3lWXpBb9PXP9Sp/nPCK+nTQmZwHGjUnqlO9ebAVQD47ZisFonnDAmjrZNVqEX\r\n"
        "F3p7laEHrFMxttYuD81BdOzxAbL9Rb/8MeFGQjE2Qx65qgVfhH+RsYuuD9dUw/3w\r\n"
        "ZAhq05yO6nk07AM9c+AbNtRoEcdZcLCHfMDcbkXKNs5DJncCqXAN6LhXVERCw/us\r\n"
        "G2MmCMLSIx9/kwt8bwhUmitOXc6fpT7SmFvRAtvxg84wUkg4Y/Gx++0j0z6StSeN\r\n"
        "0EJz150jaHG6WV4HUqaWTb98Tm90IgXAU4AW2GBOlzFPiU5IY9jt+eXC2Q6yC/Zp\r\n"
        "TL1LAcnL3Qa/OgLrHN0wiw1KFGD51WRPQ0Sh7QIDAQABo4IBJTCCASEwHQYDVR0O\r\n"
        "BBYEFLV2DDARzseSQk1Mx1wsyKkM6AtkMB8GA1UdIwQYMBaAFOWdWTCCR1jMrPoI\r\n"
        "VDaGezq1BE3wMA4GA1UdDwEB/wQEAwIBhjAdBgNVHSUEFjAUBggrBgEFBQcDAQYI\r\n"
        "KwYBBQUHAwIwEgYDVR0TAQH/BAgwBgEB/wIBADA0BggrBgEFBQcBAQQoMCYwJAYI\r\n"
        "KwYBBQUHMAGGGGh0dHA6Ly9vY3NwLmRpZ2ljZXJ0LmNvbTA6BgNVHR8EMzAxMC+g\r\n"
        "LaArhilodHRwOi8vY3JsMy5kaWdpY2VydC5jb20vT21uaXJvb3QyMDI1LmNybDAq\r\n"
        "BgNVHSAEIzAhMAgGBmeBDAECATAIBgZngQwBAgIwCwYJKwYBBAGCNyoBMA0GCSqG\r\n"
        "SIb3DQEBCwUAA4IBAQCfK76SZ1vae4qt6P+dTQUO7bYNFUHR5hXcA2D59CJWnEj5\r\n"
        "na7aKzyowKvQupW4yMH9fGNxtsh6iJswRqOOfZYC4/giBO/gNsBvwr8uDW7t1nYo\r\n"
        "DYGHPpvnpxCM2mYfQFHq576/TmeYu1RZY29C4w8xYBlkAA8mDJfRhMCmehk7cN5F\r\n"
        "JtyWRj2cZj/hOoI45TYDBChXpOlLZKIYiG1giY16vhCRi6zmPzEwv+tk156N6cGS\r\n"
        "Vm44jTQ/rs1sa0JSYjzUaYngoFdZC4OfxnIkQvUIA4TOFmPzNPEFdjcZsgbeEz4T\r\n"
        "cGHTBPK4R28F44qIMCtHRV55VMX53ev6P3hRddJb\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. ផ្លាស់ប្តូរជម្រើសទាំងអស់ `<WiFiClient.h>` ទៅជា `<WiFiClientSecure.h>`។

1. ផ្លាស់ប្តូរផ្នែកទាំងអស់ `WiFiClient` ទៅជា `WiFiClientSecure`។

1. នៅក្នុងថ្នាក់រាល់ថ្នាក់ដែលមានផ្នែក `WiFiClientSecure` បន្ថែម constructor មួយ ហើយកំណត់វិញ្ញាបនបត្រនៅក្នុង constructor នោះ៖

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ការបដិសេធ**៖  
ឯកសារនេះត្រូវបានបកប្រែដោយប្រើសេវាបកប្រែ AI [Co-op Translator](https://github.com/Azure/co-op-translator)។ នៅពេលដែលយើងខិតខំរកភាពត្រឹមត្រូវ សូមយកចិត្តទុកដាក់ថាការបកប្រែដោយស្វ័យប្រវត្តិក្នុងករណីមួយចំនួនអាចមានកំហុស ឬការខុសពីការពិត។ ឯកសារដើមនៅក្នុងភាសាមេគួរត្រូវបានយកជាអនុសាសន៍សំខាន់។ សម្រាប់ព័ត៌មានសំខាន់ៗ គួរត្រូវបានបកប្រែដោយមនុស្សដែលមានជំនាញ។ យើងមិនទទួលខុសត្រូវចំពោះការយល់ច្រឡំ ឬការបកស្រាយខុសណាមួយដែលកើតមានពីការប្រើប្រាស់ការបកប្រែនេះ។
<!-- CO-OP TRANSLATOR DISCLAIMER END -->