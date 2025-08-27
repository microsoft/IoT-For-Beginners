<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-27T20:27:26+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "th"
}
-->
# แปลงข้อความเป็นเสียง - Wio Terminal

ในส่วนนี้ของบทเรียน คุณจะเปลี่ยนข้อความเป็นเสียงเพื่อให้การตอบกลับแบบเสียงพูด

## แปลงข้อความเป็นเสียง

Speech Services SDK ที่คุณใช้ในบทเรียนก่อนหน้าเพื่อแปลงเสียงพูดเป็นข้อความ สามารถใช้เพื่อแปลงข้อความกลับเป็นเสียงพูดได้เช่นกัน

## รับรายการเสียงพูด

เมื่อร้องขอเสียงพูด คุณจำเป็นต้องระบุเสียงที่จะใช้ เนื่องจากเสียงพูดสามารถสร้างได้จากเสียงที่หลากหลาย แต่ละภาษารองรับเสียงที่แตกต่างกัน และคุณสามารถรับรายการเสียงที่รองรับสำหรับแต่ละภาษาได้จาก Speech Services SDK อย่างไรก็ตาม ข้อจำกัดของไมโครคอนโทรลเลอร์มีผลในที่นี้ - การเรียกเพื่อรับรายการเสียงที่รองรับโดยบริการแปลงข้อความเป็นเสียงจะส่งคืนเอกสาร JSON ขนาดกว่า 77KB ซึ่งใหญ่เกินไปที่จะประมวลผลโดย Wio Terminal ณ เวลาที่เขียน รายการทั้งหมดมีเสียง 215 เสียง โดยแต่ละเสียงถูกกำหนดโดยเอกสาร JSON เช่นตัวอย่างต่อไปนี้:

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

JSON นี้เป็นเสียง **Aria** ซึ่งมีหลายรูปแบบเสียง สิ่งที่จำเป็นเมื่อแปลงข้อความเป็นเสียงคือ shortname, `en-US-AriaNeural`

แทนที่จะดาวน์โหลดและถอดรหัสรายการทั้งหมดนี้บนไมโครคอนโทรลเลอร์ของคุณ คุณจำเป็นต้องเขียนโค้ดแบบ serverless เพิ่มเติมเพื่อดึงรายการเสียงสำหรับภาษาที่คุณใช้ และเรียกใช้จาก Wio Terminal ของคุณ โค้ดของคุณสามารถเลือกเสียงที่เหมาะสมจากรายการ เช่น เสียงแรกที่พบ

### งาน - สร้างฟังก์ชัน serverless เพื่อรับรายการเสียง

1. เปิดโปรเจกต์ `smart-timer-trigger` ใน VS Code และเปิด terminal โดยตรวจสอบว่า virtual environment ถูกเปิดใช้งาน หากไม่ใช่ ให้ปิดและสร้าง terminal ใหม่

1. เปิดไฟล์ `local.settings.json` และเพิ่มการตั้งค่าสำหรับ speech API key และ location:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    แทนที่ `<key>` ด้วย API key สำหรับทรัพยากร speech service ของคุณ และแทนที่ `<location>` ด้วย location ที่คุณใช้เมื่อสร้างทรัพยากร speech service

1. เพิ่ม HTTP trigger ใหม่ในแอปนี้ชื่อ `get-voices` โดยใช้คำสั่งต่อไปนี้จาก terminal ใน VS Code ในโฟลเดอร์ root ของโปรเจกต์ functions app:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    สิ่งนี้จะสร้าง HTTP trigger ชื่อ `get-voices`

1. แทนที่เนื้อหาของไฟล์ `__init__.py` ในโฟลเดอร์ `get-voices` ด้วยโค้ดต่อไปนี้:

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

    โค้ดนี้ทำการร้องขอ HTTP ไปยัง endpoint เพื่อรับรายการเสียง รายการเสียงนี้เป็นบล็อก JSON ขนาดใหญ่ที่มีเสียงสำหรับทุกภาษา ดังนั้นเสียงสำหรับภาษาที่ส่งใน request body จะถูกกรองออก จากนั้น shortname จะถูกดึงออกมาและส่งคืนเป็น JSON list shortname เป็นค่าที่จำเป็นในการแปลงข้อความเป็นเสียง ดังนั้นจะส่งคืนเฉพาะค่านี้

    > 💁 คุณสามารถเปลี่ยนตัวกรองตามความจำเป็นเพื่อเลือกเฉพาะเสียงที่คุณต้องการ

    สิ่งนี้ลดขนาดของข้อมูลจาก 77KB (ณ เวลาที่เขียน) เป็นเอกสาร JSON ที่เล็กกว่ามาก ตัวอย่างเช่น สำหรับเสียง US ขนาดนี้คือ 408 bytes

1. รันแอปฟังก์ชันของคุณในเครื่อง จากนั้นคุณสามารถเรียกใช้โดยใช้เครื่องมือเช่น curl ในลักษณะเดียวกับที่คุณทดสอบ HTTP trigger `text-to-timer` อย่าลืมส่งภาษาของคุณเป็น JSON body:

    ```json
    {
        "language":"<language>"
    }
    ```

    แทนที่ `<language>` ด้วยภาษาของคุณ เช่น `en-GB` หรือ `zh-CN`

> 💁 คุณสามารถค้นหาโค้ดนี้ได้ในโฟลเดอร์ [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions)

### งาน - ดึงเสียงจาก Wio Terminal ของคุณ

1. เปิดโปรเจกต์ `smart-timer` ใน VS Code หากยังไม่ได้เปิด

1. เปิดไฟล์ header `config.h` และเพิ่ม URL สำหรับแอปฟังก์ชันของคุณ:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    แทนที่ `<URL>` ด้วย URL สำหรับ HTTP trigger `get-voices` ในแอปฟังก์ชันของคุณ URL นี้จะเหมือนกับค่าของ `TEXT_TO_TIMER_FUNCTION_URL` ยกเว้นชื่อฟังก์ชันที่เป็น `get-voices` แทน `text-to-timer`

1. สร้างไฟล์ใหม่ในโฟลเดอร์ `src` ชื่อ `text_to_speech.h` ไฟล์นี้จะใช้เพื่อกำหนดคลาสสำหรับแปลงข้อความเป็นเสียง

1. เพิ่ม include directives ต่อไปนี้ที่ด้านบนของไฟล์ `text_to_speech.h` ใหม่:

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

1. เพิ่มโค้ดต่อไปนี้ด้านล่างเพื่อประกาศคลาส `TextToSpeech` พร้อมกับ instance ที่สามารถใช้ในแอปพลิเคชันที่เหลือ:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. เพื่อเรียกใช้แอปฟังก์ชันของคุณ คุณต้องประกาศ WiFi client เพิ่มโค้ดต่อไปนี้ในส่วน `private` ของคลาส:

    ```cpp
    WiFiClient _client;
    ```

1. ในส่วน `private` เพิ่มฟิลด์สำหรับเสียงที่เลือก:

    ```cpp
    String _voice;
    ```

1. ในส่วน `public` เพิ่มฟังก์ชัน `init` ที่จะรับเสียงแรก:

    ```cpp
    void init()
    {
    }
    ```

1. เพื่อรับเสียง JSON document จำเป็นต้องส่งไปยังแอปฟังก์ชันพร้อมภาษา เพิ่มโค้ดต่อไปนี้ในฟังก์ชัน `init` เพื่อสร้าง JSON document นี้:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. จากนั้นสร้าง `HTTPClient` และใช้มันเพื่อเรียกแอปฟังก์ชันเพื่อรับเสียง โดยโพสต์ JSON document:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. ด้านล่างนี้เพิ่มโค้ดเพื่อตรวจสอบ response code และหากเป็น 200 (success) ให้ดึงรายการเสียง โดยรับเสียงแรกจากรายการ:

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

1. หลังจากนี้ ให้ปิดการเชื่อมต่อ HTTP client:

    ```cpp
    httpClient.end();
    ```

1. เปิดไฟล์ `main.cpp` และเพิ่ม include directive ต่อไปนี้ที่ด้านบนเพื่อรวม header file ใหม่นี้:

    ```cpp
    #include "text_to_speech.h"
    ```

1. ในฟังก์ชัน `setup` ใต้การเรียก `speechToText.init();` เพิ่มโค้ดต่อไปนี้เพื่อเริ่มต้นคลาส `TextToSpeech`:

    ```cpp
    textToSpeech.init();
    ```

1. สร้างโค้ดนี้ อัปโหลดไปยัง Wio Terminal ของคุณ และทดสอบผ่าน serial monitor ตรวจสอบให้แน่ใจว่าแอปฟังก์ชันของคุณกำลังทำงาน

    คุณจะเห็นรายการเสียงที่มีอยู่ที่ส่งคืนจากแอปฟังก์ชัน พร้อมกับเสียงที่เลือก

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

## แปลงข้อความเป็นเสียง

เมื่อคุณมีเสียงที่จะใช้แล้ว คุณสามารถใช้มันเพื่อแปลงข้อความเป็นเสียง ข้อจำกัดด้านหน่วยความจำเดียวกันกับเสียงยังมีผลเมื่อแปลงเสียงเป็นข้อความ ดังนั้นคุณจำเป็นต้องเขียนเสียงลงใน SD card เพื่อเล่นผ่าน ReSpeaker

> 💁 ในบทเรียนก่อนหน้าในโปรเจกต์นี้ คุณใช้หน่วยความจำแฟลชเพื่อเก็บเสียงที่จับจากไมโครโฟน บทเรียนนี้ใช้ SD card เนื่องจากง่ายกว่าในการเล่นเสียงจากมันโดยใช้ไลบรารีเสียง Seeed

ยังมีข้อจำกัดอื่นที่ต้องพิจารณา ข้อมูลเสียงที่มีอยู่จาก speech service และรูปแบบที่ Wio Terminal รองรับ ไลบรารีเสียงสำหรับไมโครคอนโทรลเลอร์อาจมีข้อจำกัดมากในรูปแบบเสียงที่รองรับ ตัวอย่างเช่น ไลบรารี Seeed Arduino Audio ที่สามารถเล่นเสียงผ่าน ReSpeaker รองรับเสียงที่ sample rate 44.1KHz เท่านั้น Speech Services ของ Azure สามารถให้เสียงในหลายรูปแบบ แต่ไม่มีรูปแบบใดที่ใช้ sample rate นี้ พวกมันให้เฉพาะ 8KHz, 16KHz, 24KHz และ 48KHz ซึ่งหมายความว่าเสียงจำเป็นต้องถูก re-sample เป็น 44.1KHz ซึ่งต้องการทรัพยากรมากกว่า Wio Terminal มี โดยเฉพาะหน่วยความจำ

เมื่อจำเป็นต้องจัดการข้อมูลแบบนี้ มักจะดีกว่าที่จะใช้โค้ดแบบ serverless โดยเฉพาะหากข้อมูลถูกดึงผ่านการเรียกเว็บ Wio Terminal สามารถเรียกฟังก์ชัน serverless โดยส่งข้อความที่ต้องการแปลง และฟังก์ชัน serverless สามารถเรียก speech service เพื่อแปลงข้อความเป็นเสียง รวมถึง re-sample เสียงเป็น sample rate ที่ต้องการ จากนั้นสามารถส่งคืนเสียงในรูปแบบที่ Wio Terminal ต้องการเพื่อเก็บไว้ใน SD card และเล่นผ่าน ReSpeaker

### งาน - สร้างฟังก์ชัน serverless เพื่อแปลงข้อความเป็นเสียง

1. เปิดโปรเจกต์ `smart-timer-trigger` ใน VS Code และเปิด terminal โดยตรวจสอบว่า virtual environment ถูกเปิดใช้งาน หากไม่ใช่ ให้ปิดและสร้าง terminal ใหม่

1. เพิ่ม HTTP trigger ใหม่ในแอปนี้ชื่อ `text-to-speech` โดยใช้คำสั่งต่อไปนี้จาก terminal ใน VS Code ในโฟลเดอร์ root ของโปรเจกต์ functions app:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    สิ่งนี้จะสร้าง HTTP trigger ชื่อ `text-to-speech`

1. [librosa](https://librosa.org) Pip package มีฟังก์ชันสำหรับ re-sample เสียง ดังนั้นเพิ่มสิ่งนี้ในไฟล์ `requirements.txt`:

    ```sh
    librosa
    ```

    เมื่อเพิ่มแล้ว ให้ติดตั้ง Pip packages โดยใช้คำสั่งต่อไปนี้จาก terminal ใน VS Code:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ หากคุณใช้ Linux รวมถึง Raspberry Pi OS คุณอาจต้องติดตั้ง `libsndfile` ด้วยคำสั่งต่อไปนี้:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. เพื่อแปลงข้อความเป็นเสียง คุณไม่สามารถใช้ speech API key โดยตรงได้ แต่คุณต้องร้องขอ access token โดยใช้ API key เพื่อยืนยันการร้องขอ access token เปิดไฟล์ `__init__.py` จากโฟลเดอร์ `text-to-speech` และแทนที่โค้ดทั้งหมดในไฟล์ด้วยโค้ดต่อไปนี้:

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

    สิ่งนี้กำหนด constants สำหรับ location และ speech key ที่จะถูกอ่านจาก settings จากนั้นกำหนดฟังก์ชัน `get_access_token` ที่จะดึง access token สำหรับ speech service

1. ด้านล่างโค้ดนี้ เพิ่มโค้ดต่อไปนี้:

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

    สิ่งนี้กำหนด HTTP trigger ที่แปลงข้อความเป็นเสียง มันดึงข้อความที่ต้องการแปลง ภาษา และเสียงจาก JSON body ที่ส่งไปยัง request สร้าง SSML เพื่อร้องขอเสียง จากนั้นเรียก REST API ที่เกี่ยวข้องโดยยืนยันผ่าน access token การเรียก REST API นี้ส่งคืนเสียงที่เข้ารหัสเป็นไฟล์ WAV mono 16-bit, 48KHz ซึ่งกำหนดโดยค่าของ `playback_format` ที่ส่งไปยังการเรียก REST API

    จากนั้นเสียงนี้จะถูก re-sample โดย `librosa` จาก sample rate 48KHz เป็น sample rate 44.1KHz จากนั้นเสียงนี้จะถูกบันทึกลงใน binary buffer ที่จะถูกส่งคืน

1. รันแอปฟังก์ชันของคุณในเครื่อง หรือ deploy ไปยัง cloud จากนั้นคุณสามารถเรียกใช้โดยใช้เครื่องมือเช่น curl ในลักษณะเดียวกับที่คุณทดสอบ HTTP trigger `text-to-timer` อย่าลืมส่งภาษา เสียง และข้อความเป็น JSON body:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    แทนที่ `<language>` ด้วยภาษาของคุณ เช่น `en-GB` หรือ `zh-CN` แทนที่ `<voice>` ด้วยเสียงที่คุณต้องการใช้ และแทนที่ `<text>` ด้วยข้อความที่คุณต้องการแปลงเป็นเสียง คุณสามารถบันทึก output ลงในไฟล์และเล่นด้วยโปรแกรมเล่นเสียงใดๆ ที่สามารถเล่นไฟล์ WAV ได้

    ตัวอย่างเช่น เพื่อแปลง "Hello" เป็นเสียงพูดโดยใช้ US English กับเสียง Jenny Neural โดยแอปฟังก์ชันทำงานในเครื่อง คุณสามารถใช้คำสั่ง curl ต่อไปนี้:

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

    สิ่งนี้จะบันทึกเสียงลงใน `hello.wav` ในไดเรกทอรีปัจจุบัน

> 💁 คุณสามารถค้นหาโค้ดนี้ได้ในโฟลเดอร์ [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions)

### งาน - ดึงเสียงพูดจาก Wio Terminal ของคุณ

1. เปิดโปรเจกต์ `smart-timer` ใน VS Code หากยังไม่ได้เปิด

1. เปิดไฟล์ header `config.h` และเพิ่ม URL สำหรับแอปฟังก์ชันของคุณ:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    แทนที่ `<URL>` ด้วย URL สำหรับ HTTP trigger `text-to-speech` ในแอปฟังก์ชันของคุณ URL นี้จะเหมือนกับค่าของ `TEXT_TO_TIMER_FUNCTION_URL` ยกเว้นชื่อฟังก์ชันที่เป็น `text-to-speech` แทน `text-to-timer`

1. เปิดไฟล์ header `text_to_speech.h` และเพิ่ม method ต่อไปนี้ในส่วน `public` ของคลาส `TextToSpeech`:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. ใน method `convertTextToSpeech` เพิ่มโค้ดต่อไปนี้เพื่อสร้าง JSON ที่จะส่งไปยังแอปฟังก์ชัน:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    สิ่งนี้เขียนภาษา เสียง และข้อความลงใน JSON document จากนั้น serialize เป็น string

1. ด้านล่างนี้ เพิ่มโค้ดต่อไปนี้เพื่อเรียกแอปฟังก์ชัน:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    สิ่งนี้สร้าง HTTPClient จากนั้นทำ POST request โดยใช้ JSON document ไปยัง HTTP trigger `text-to-speech`

1. หากการเรียกทำงาน ข้อมูล binary raw ที่ส่งคืนจากการเรียกแอปฟังก์ชันสามารถ stream ไปยังไฟล์บน SD card ได้ เพิ่มโค้ดต่อไปนี้เพื่อทำสิ่งนี้:

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

    โค้ดนี้ตรวจสอบ response และหากเป็น 200 (success) ข้อมูล binary จะถูก stream ไปยังไฟล์ใน root ของ SD Card ชื่อ `SPEECH.WAV`

1. ที่ส่วนท้ายของ method นี้ ปิดการเชื่อมต่อ HTTP:

    ```cpp
    httpClient.end();
    ```

1. ข้อความที่ต้องการพูดสามารถแปลงเป็นเสียงได้แล้ว ในไฟล์ `main.cpp` เพิ่มบรรทัดต่อไปนี้ที่ส่วนท้ายของฟังก์ชัน `say` เพื่อแปลงข้อความที่ต้องการพูดเป็นเสียง:
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### งาน - เล่นเสียงจาก Wio Terminal ของคุณ

**เร็วๆ นี้**

## การปรับใช้แอปฟังก์ชันของคุณไปยังคลาวด์

เหตุผลที่ต้องรันแอปฟังก์ชันในเครื่องก่อนเป็นเพราะแพ็กเกจ `librosa` ของ Pip บน Linux มีการพึ่งพาไลบรารีที่ไม่ได้ติดตั้งมาโดยค่าเริ่มต้น และจำเป็นต้องติดตั้งก่อนที่แอปฟังก์ชันจะสามารถทำงานได้ แอปฟังก์ชันเป็นแบบไร้เซิร์ฟเวอร์ - คุณไม่สามารถจัดการเซิร์ฟเวอร์เองได้ ดังนั้นจึงไม่มีวิธีติดตั้งไลบรารีนี้ล่วงหน้า

วิธีแก้ไขคือการปรับใช้แอปฟังก์ชันของคุณโดยใช้ Docker container แทน คอนเทนเนอร์นี้จะถูกปรับใช้โดยคลาวด์เมื่อใดก็ตามที่ต้องการสร้างอินสแตนซ์ใหม่ของแอปฟังก์ชันของคุณ (เช่น เมื่อความต้องการเกินทรัพยากรที่มีอยู่ หรือเมื่อแอปฟังก์ชันไม่ได้ถูกใช้งานเป็นเวลานานและถูกปิดตัวลง)

คุณสามารถดูคำแนะนำในการตั้งค่าแอปฟังก์ชันและปรับใช้ผ่าน Docker ได้ที่ [เอกสารการสร้างฟังก์ชันบน Linux โดยใช้คอนเทนเนอร์แบบกำหนดเองใน Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python)

เมื่อปรับใช้เสร็จแล้ว คุณสามารถพอร์ตโค้ด Wio Terminal ของคุณเพื่อเข้าถึงฟังก์ชันนี้ได้:

1. เพิ่มใบรับรอง Azure Functions ไปที่ `config.h`:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. เปลี่ยนการ include ทั้งหมดจาก `<WiFiClient.h>` เป็น `<WiFiClientSecure.h>` 

1. เปลี่ยนฟิลด์ `WiFiClient` ทั้งหมดเป็น `WiFiClientSecure`

1. ในทุกคลาสที่มีฟิลด์ `WiFiClientSecure` ให้เพิ่ม constructor และตั้งค่าใบรับรองใน constructor นั้น:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามอย่างเต็มที่เพื่อให้การแปลมีความถูกต้อง แต่โปรดทราบว่าการแปลอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่แม่นยำ เอกสารต้นฉบับในภาษาต้นทางควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ แนะนำให้ใช้บริการแปลภาษามนุษย์ที่เป็นมืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความที่ผิดพลาดซึ่งเกิดจากการใช้การแปลนี้