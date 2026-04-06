# แปลข้อความ - Wio Terminal

ในส่วนนี้ของบทเรียน คุณจะเขียนโค้ดเพื่อแปลข้อความโดยใช้บริการแปลภาษา

## แปลงข้อความเป็นเสียงโดยใช้บริการแปลภาษา

REST API ของบริการเสียงไม่รองรับการแปลโดยตรง แต่คุณสามารถใช้บริการแปลภาษาเพื่อแปลข้อความที่สร้างจากบริการแปลงเสียงเป็นข้อความ และข้อความที่ตอบกลับด้วยเสียง บริการนี้มี REST API ที่คุณสามารถใช้เพื่อแปลข้อความ แต่เพื่อให้ง่ายขึ้น คุณจะห่อหุ้มมันไว้ใน HTTP trigger อีกตัวในแอปฟังก์ชันของคุณ

### งาน - สร้างฟังก์ชันแบบไร้เซิร์ฟเวอร์เพื่อแปลข้อความ

1. เปิดโปรเจกต์ `smart-timer-trigger` ใน VS Code และเปิดเทอร์มินัล โดยตรวจสอบให้แน่ใจว่าสภาพแวดล้อมเสมือนถูกเปิดใช้งาน หากไม่ใช่ ให้ปิดและสร้างเทอร์มินัลใหม่

1. เปิดไฟล์ `local.settings.json` และเพิ่มการตั้งค่าสำหรับคีย์ API และตำแหน่งของบริการแปลภาษา:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    แทนที่ `<key>` ด้วยคีย์ API สำหรับทรัพยากรบริการแปลภาษา และแทนที่ `<location>` ด้วยตำแหน่งที่คุณใช้เมื่อสร้างทรัพยากรบริการแปลภาษา

1. เพิ่ม HTTP trigger ใหม่ในแอปนี้ชื่อ `translate-text` โดยใช้คำสั่งต่อไปนี้จากเทอร์มินัลใน VS Code ในโฟลเดอร์รากของโปรเจกต์แอปฟังก์ชัน:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    คำสั่งนี้จะสร้าง HTTP trigger ชื่อ `translate-text`

1. แทนที่เนื้อหาในไฟล์ `__init__.py` ในโฟลเดอร์ `translate-text` ด้วยโค้ดต่อไปนี้:

    ```python
    import logging
    import os
    import requests
    
    import azure.functions as func
    
    location = os.environ['TRANSLATOR_LOCATION']
    translator_key = os.environ['TRANSLATOR_KEY']
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        from_language = req_body['from_language']
        to_language = req_body['to_language']
        text = req_body['text']
        
        logging.info(f'Translating {text} from {from_language} to {to_language}')
    
        url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'
    
        headers = {
            'Ocp-Apim-Subscription-Key': translator_key,
            'Ocp-Apim-Subscription-Region': location,
            'Content-type': 'application/json'
        }
    
        params = {
            'from': from_language,
            'to': to_language
        }
    
        body = [{
            'text' : text
        }]
        
        response = requests.post(url, headers=headers, params=params, json=body)
        return func.HttpResponse(response.json()[0]['translations'][0]['text'])
    ```

    โค้ดนี้จะดึงข้อความและภาษาจากคำขอ HTTP จากนั้นจะส่งคำขอไปยัง REST API ของบริการแปลภาษา โดยส่งภาษาผ่านพารามิเตอร์ใน URL และข้อความที่ต้องการแปลใน body สุดท้ายจะส่งผลลัพธ์การแปลกลับมา

1. รันแอปฟังก์ชันของคุณในเครื่อง จากนั้นคุณสามารถเรียกใช้มันโดยใช้เครื่องมืออย่าง curl ในลักษณะเดียวกับที่คุณทดสอบ HTTP trigger `text-to-timer` อย่าลืมส่งข้อความที่ต้องการแปลและภาษาผ่าน JSON body:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    ตัวอย่างนี้แปล *Définir une minuterie de 30 secondes* จากภาษาฝรั่งเศสเป็นภาษาอังกฤษแบบ US ผลลัพธ์จะเป็น *Set a 30-second timer*

> 💁 คุณสามารถค้นหาโค้ดนี้ได้ในโฟลเดอร์ [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions)

### งาน - ใช้ฟังก์ชันแปลภาษาเพื่อแปลข้อความ

1. เปิดโปรเจกต์ `smart-timer` ใน VS Code หากยังไม่ได้เปิด

1. ตัวจับเวลาของคุณจะมีการตั้งค่าภาษา 2 ภาษา - ภาษาของเซิร์ฟเวอร์ที่ใช้ฝึก LUIS (ภาษาเดียวกันนี้ยังใช้สร้างข้อความที่พูดกับผู้ใช้) และภาษาที่ผู้ใช้พูด อัปเดตค่าคงที่ `LANGUAGE` ในไฟล์ header `config.h` ให้เป็นภาษาที่ผู้ใช้จะพูด และเพิ่มค่าคงที่ใหม่ชื่อ `SERVER_LANGUAGE` สำหรับภาษาที่ใช้ฝึก LUIS:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    แทนที่ `<user language>` ด้วยชื่อ locale ของภาษาที่คุณจะพูด เช่น `fr-FR` สำหรับภาษาฝรั่งเศส หรือ `zn-HK` สำหรับภาษากวางตุ้ง

    แทนที่ `<server language>` ด้วยชื่อ locale ของภาษาที่ใช้ฝึก LUIS

    คุณสามารถค้นหารายชื่อภาษาที่รองรับและชื่อ locale ได้ใน [เอกสารสนับสนุนภาษาและเสียงบน Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text)

    > 💁 หากคุณไม่พูดได้หลายภาษา คุณสามารถใช้บริการอย่าง [Bing Translate](https://www.bing.com/translator) หรือ [Google Translate](https://translate.google.com) เพื่อแปลจากภาษาที่คุณถนัดไปยังภาษาที่คุณเลือก บริการเหล่านี้สามารถเล่นเสียงของข้อความที่แปลได้
    >
    > ตัวอย่างเช่น หากคุณฝึก LUIS ในภาษาอังกฤษ แต่ต้องการใช้ภาษาฝรั่งเศสเป็นภาษาผู้ใช้ คุณสามารถแปลประโยคอย่าง "set a 2 minute and 27 second timer" จากภาษาอังกฤษเป็นภาษาฝรั่งเศสโดยใช้ Bing Translate จากนั้นใช้ปุ่ม **Listen translation** เพื่อพูดการแปลลงในไมโครโฟนของคุณ
    >
    > ![ปุ่มฟังการแปลบน Bing Translate](../../../../../translated_images/th/bing-translate.348aa796d6efe2a9.webp)

1. เพิ่มคีย์ API และตำแหน่งของบริการแปลภาษาด้านล่าง `SPEECH_LOCATION`:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    แทนที่ `<KEY>` ด้วยคีย์ API สำหรับทรัพยากรบริการแปลภาษา และแทนที่ `<LOCATION>` ด้วยตำแหน่งที่คุณใช้เมื่อสร้างทรัพยากรบริการแปลภาษา

1. เพิ่ม URL trigger ของบริการแปลภาษาด้านล่าง `VOICE_URL`:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    แทนที่ `<URL>` ด้วย URL สำหรับ HTTP trigger `translate-text` ในแอปฟังก์ชันของคุณ URL นี้จะเหมือนกับค่าของ `TEXT_TO_TIMER_FUNCTION_URL` ยกเว้นชื่อฟังก์ชันจะเป็น `translate-text` แทน `text-to-timer`

1. เพิ่มไฟล์ใหม่ในโฟลเดอร์ `src` ชื่อ `text_translator.h`

1. ไฟล์ header `text_translator.h` ใหม่นี้จะมีคลาสสำหรับแปลข้อความ เพิ่มโค้ดต่อไปนี้ในไฟล์นี้เพื่อประกาศคลาส:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    
    class TextTranslator
    {
    public:   
    private:
        WiFiClient _client;
    };
    
    TextTranslator textTranslator;
    ```

    โค้ดนี้ประกาศคลาส `TextTranslator` พร้อมกับอินสแตนซ์ของคลาสนี้ คลาสมีฟิลด์เดียวสำหรับ WiFi client

1. ในส่วน `public` ของคลาสนี้ เพิ่มเมธอดเพื่อแปลข้อความ:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    เมธอดนี้รับภาษาที่ต้องการแปลจาก และภาษาที่ต้องการแปลไป เมื่อจัดการเสียง เสียงจะถูกแปลจากภาษาผู้ใช้ไปยังภาษาของเซิร์ฟเวอร์ LUIS และเมื่อให้การตอบกลับ จะถูกแปลจากภาษาของเซิร์ฟเวอร์ LUIS ไปยังภาษาผู้ใช้

1. ในเมธอดนี้ เพิ่มโค้ดเพื่อสร้าง JSON body ที่มีข้อความที่ต้องการแปลและภาษา:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;
    doc["from_language"] = from_language;
    doc["to_language"] = to_language;

    String body;
    serializeJson(doc, body);

    Serial.print("Translating ");
    Serial.print(text);
    Serial.print(" from ");
    Serial.print(from_language);
    Serial.print(" to ");
    Serial.print(to_language);
    ```

1. ด้านล่างนี้ เพิ่มโค้ดเพื่อส่ง body ไปยังแอปฟังก์ชันแบบไร้เซิร์ฟเวอร์:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. ต่อไป เพิ่มโค้ดเพื่อรับการตอบกลับ:

    ```cpp
    String translated_text = "";

    if (httpResponseCode == 200)
    {
        translated_text = httpClient.getString();
        Serial.print("Translated: ");
        Serial.println(translated_text);
    }
    else
    {
        Serial.print("Failed to translate text - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. สุดท้าย เพิ่มโค้ดเพื่อปิดการเชื่อมต่อและส่งข้อความที่แปลกลับมา:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### งาน - แปลเสียงที่รับรู้และการตอบกลับ

1. เปิดไฟล์ `main.cpp`

1. เพิ่มคำสั่ง include ที่ด้านบนของไฟล์สำหรับไฟล์ header คลาส `TextTranslator`:

    ```cpp
    #include "text_translator.h"
    ```

1. ข้อความที่พูดเมื่อจับเวลาถูกตั้งค่าหรือหมดเวลาต้องถูกแปล เพื่อทำสิ่งนี้ เพิ่มโค้ดต่อไปนี้เป็นบรรทัดแรกในฟังก์ชัน `say`:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    โค้ดนี้จะแปลข้อความเป็นภาษาของผู้ใช้

1. ในฟังก์ชัน `processAudio` ข้อความจะถูกดึงจากเสียงที่จับได้ด้วยคำสั่ง `String text = speechToText.convertSpeechToText();` หลังจากคำสั่งนี้ ให้แปลข้อความ:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    โค้ดนี้จะแปลข้อความจากภาษาของผู้ใช้เป็นภาษาที่ใช้บนเซิร์ฟเวอร์

1. สร้างโค้ดนี้ อัปโหลดไปยัง Wio Terminal และทดสอบผ่าน serial monitor เมื่อคุณเห็นคำว่า `Ready` ใน serial monitor ให้กดปุ่ม C (ปุ่มด้านซ้ายมือ ใกล้กับสวิตช์เปิดปิด) และพูด ตรวจสอบให้แน่ใจว่าแอปฟังก์ชันของคุณกำลังทำงาน และขอจับเวลาในภาษาผู้ใช้ ไม่ว่าจะโดยการพูดภาษานั้นเอง หรือใช้แอปแปลภาษา

    ```output
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Définir une minuterie de 2 minutes 27 secondes.","Offset":9600000,"Duration":40400000}
    Translating Définir une minuterie de 2 minutes 27 secondes. from fr-FR to en-US
    Translated: Set a timer of 2 minutes 27 seconds.
    Set a timer of 2 minutes 27 seconds.
    {"seconds": 147}
    Translating 2 minute 27 second timer started. from en-US to fr-FR
    Translated: 2 minute 27 seconde minute a commencé.
    2 minute 27 seconde minute a commencé.
    Translating Times up on your 2 minute 27 second timer. from en-US to fr-FR
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

> 💁 คุณสามารถค้นหาโค้ดนี้ได้ในโฟลเดอร์ [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal)

😀 โปรแกรมจับเวลาหลายภาษาของคุณประสบความสำเร็จ!

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้อง แต่โปรดทราบว่าการแปลอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความผิดที่เกิดจากการใช้การแปลนี้