<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-27T20:29:30+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "th"
}
-->
# ตั้งเวลานับถอยหลัง - Wio Terminal

ในส่วนนี้ของบทเรียน คุณจะเรียกใช้โค้ดแบบเซิร์ฟเวอร์เลสเพื่อแปลงคำพูดเป็นข้อความ และตั้งเวลานับถอยหลังบน Wio Terminal ตามผลลัพธ์ที่ได้

## ตั้งเวลานับถอยหลัง

ข้อความที่ได้จากการแปลงคำพูดเป็นข้อความจะต้องถูกส่งไปยังโค้ดเซิร์ฟเวอร์เลสของคุณเพื่อให้ LUIS ประมวลผล และส่งกลับมาด้วยจำนวนวินาทีสำหรับตั้งเวลา จำนวนวินาทีนี้จะถูกใช้ในการตั้งเวลานับถอยหลัง

ไมโครคอนโทรลเลอร์ไม่มีการรองรับการทำงานแบบมัลติเธรดใน Arduino โดยตรง ดังนั้นจึงไม่มีคลาสตั้งเวลาแบบมาตรฐานเหมือนที่คุณอาจพบใน Python หรือภาษาโปรแกรมระดับสูงอื่น ๆ แต่คุณสามารถใช้ไลบรารีตั้งเวลาที่ทำงานโดยการวัดเวลาที่ผ่านไปในฟังก์ชัน `loop` และเรียกใช้ฟังก์ชันเมื่อเวลาหมด

### งาน - ส่งข้อความไปยังฟังก์ชันเซิร์ฟเวอร์เลส

1. เปิดโปรเจกต์ `smart-timer` ใน VS Code หากยังไม่ได้เปิด

1. เปิดไฟล์เฮดเดอร์ `config.h` และเพิ่ม URL สำหรับแอปฟังก์ชันของคุณ:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    แทนที่ `<URL>` ด้วย URL ของแอปฟังก์ชันที่คุณได้จากขั้นตอนสุดท้ายของบทเรียนก่อนหน้า โดยชี้ไปยังที่อยู่ IP ของเครื่องที่รันแอปฟังก์ชัน

1. สร้างไฟล์ใหม่ในโฟลเดอร์ `src` ชื่อ `language_understanding.h` ไฟล์นี้จะถูกใช้เพื่อกำหนดคลาสสำหรับส่งข้อความที่แปลงจากคำพูดไปยังแอปฟังก์ชันเพื่อแปลงเป็นวินาทีโดยใช้ LUIS

1. เพิ่มโค้ดต่อไปนี้ที่ด้านบนของไฟล์นี้:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    โค้ดนี้รวมไฟล์เฮดเดอร์ที่จำเป็น

1. กำหนดคลาสชื่อ `LanguageUnderstanding` และประกาศอินสแตนซ์ของคลาสนี้:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. เพื่อเรียกใช้แอปฟังก์ชันของคุณ คุณต้องประกาศ WiFi client เพิ่มโค้ดต่อไปนี้ในส่วน `private` ของคลาส:

    ```cpp
    WiFiClient _client;
    ```

1. ในส่วน `public` ให้ประกาศเมธอดชื่อ `GetTimerDuration` เพื่อเรียกใช้แอปฟังก์ชัน:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. ในเมธอด `GetTimerDuration` เพิ่มโค้ดต่อไปนี้เพื่อสร้าง JSON ที่จะถูกส่งไปยังแอปฟังก์ชัน:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    โค้ดนี้แปลงข้อความที่ส่งไปยังเมธอด `GetTimerDuration` ให้เป็น JSON ดังนี้:

    ```json
    {
        "text" : "<text>"
    }
    ```

    โดยที่ `<text>` คือข้อความที่ส่งไปยังฟังก์ชัน

1. ด้านล่างนี้ เพิ่มโค้ดต่อไปนี้เพื่อเรียกใช้แอปฟังก์ชัน:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    โค้ดนี้ทำการ POST request ไปยังแอปฟังก์ชัน โดยส่ง JSON body และรับ response code

1. เพิ่มโค้ดต่อไปนี้ด้านล่าง:

    ```cpp
    int seconds = 0;
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonObject obj = doc.as<JsonObject>();
        seconds = obj["seconds"].as<int>();
    }
    else
    {
        Serial.print("Failed to understand text - error ");
        Serial.println(httpResponseCode);
    }
    ```

    โค้ดนี้ตรวจสอบ response code หากเป็น 200 (สำเร็จ) จะดึงจำนวนวินาทีจาก response body มิฉะนั้นจะส่งข้อผิดพลาดไปยัง serial monitor และตั้งจำนวนวินาทีเป็น 0

1. เพิ่มโค้ดต่อไปนี้ที่ท้ายเมธอดนี้เพื่อปิดการเชื่อมต่อ HTTP และคืนค่าจำนวนวินาที:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. ในไฟล์ `main.cpp` ให้ include เฮดเดอร์ใหม่นี้:

    ```cpp
    #include "speech_to_text.h"
    ```

1. ที่ท้ายฟังก์ชัน `processAudio` เรียกใช้เมธอด `GetTimerDuration` เพื่อรับค่าระยะเวลาของตัวจับเวลา:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    โค้ดนี้แปลงข้อความจากการเรียกใช้คลาส `SpeechToText` เป็นจำนวนวินาทีสำหรับตั้งเวลา

### งาน - ตั้งเวลานับถอยหลัง

จำนวนวินาทีสามารถใช้ในการตั้งเวลานับถอยหลังได้

1. เพิ่มไลบรารีที่ต้องการในไฟล์ `platformio.ini` เพื่อเพิ่มไลบรารีสำหรับตั้งเวลา:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. เพิ่มคำสั่ง include สำหรับไลบรารีนี้ในไฟล์ `main.cpp`:

    ```cpp
    #include <arduino-timer.h>
    ```

1. เหนือฟังก์ชัน `processAudio` เพิ่มโค้ดต่อไปนี้:

    ```cpp
    auto timer = timer_create_default();
    ```

    โค้ดนี้ประกาศตัวจับเวลาชื่อ `timer`

1. ด้านล่างนี้ เพิ่มโค้ดต่อไปนี้:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    ฟังก์ชัน `say` นี้ในอนาคตจะถูกใช้เพื่อแปลงข้อความเป็นเสียงพูด แต่ตอนนี้จะเพียงแค่เขียนข้อความที่ส่งเข้ามาไปยัง serial monitor

1. ด้านล่างฟังก์ชัน `say` เพิ่มโค้ดต่อไปนี้:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    นี่คือฟังก์ชัน callback ที่จะถูกเรียกเมื่อเวลาหมด ฟังก์ชันนี้จะรับข้อความเพื่อพูดเมื่อเวลาหมด ตัวจับเวลาสามารถทำซ้ำได้ และสามารถควบคุมได้ด้วยค่าที่ return จาก callback - โค้ดนี้ return `false` เพื่อบอกให้ตัวจับเวลาไม่ทำงานซ้ำ

1. เพิ่มโค้ดต่อไปนี้ที่ท้ายฟังก์ชัน `processAudio`:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    โค้ดนี้ตรวจสอบจำนวนวินาทีทั้งหมด และหากเป็น 0 จะ return ออกจากฟังก์ชันเพื่อไม่ให้ตั้งเวลา จากนั้นจะแปลงจำนวนวินาทีทั้งหมดเป็นนาทีและวินาที

1. ด้านล่างโค้ดนี้ เพิ่มโค้ดต่อไปนี้เพื่อสร้างข้อความที่จะแจ้งเมื่อเริ่มตั้งเวลา:

    ```cpp
    String begin_message;
    if (minutes > 0)
    {
        begin_message += minutes;
        begin_message += " minute ";
    }
    if (seconds > 0)
    {
        begin_message += seconds;
        begin_message += " second ";
    }

    begin_message += "timer started.";
    ```

1. ด้านล่างนี้ เพิ่มโค้ดที่คล้ายกันเพื่อสร้างข้อความที่จะแจ้งเมื่อเวลาหมด:

    ```cpp
    String end_message("Times up on your ");
    if (minutes > 0)
    {
        end_message += minutes;
        end_message += " minute ";
    }
    if (seconds > 0)
    {
        end_message += seconds;
        end_message += " second ";
    }

    end_message += "timer.";
    ```

1. หลังจากนี้ ให้พูดข้อความแจ้งเริ่มตั้งเวลา:

    ```cpp
    say(begin_message);
    ```

1. ที่ท้ายฟังก์ชันนี้ เริ่มตัวจับเวลา:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    โค้ดนี้เริ่มตัวจับเวลา ตัวจับเวลาถูกตั้งค่าโดยใช้มิลลิวินาที ดังนั้นจำนวนวินาทีทั้งหมดจะถูกคูณด้วย 1,000 เพื่อแปลงเป็นมิลลิวินาที ฟังก์ชัน `timerExpired` ถูกส่งเป็น callback และ `end_message` ถูกส่งเป็นอาร์กิวเมนต์ไปยัง callback ซึ่ง callback นี้รับเฉพาะอาร์กิวเมนต์แบบ `void *` ดังนั้นข้อความจึงถูกแปลงให้เหมาะสม

1. สุดท้าย ตัวจับเวลาจำเป็นต้อง *tick* และสิ่งนี้ทำในฟังก์ชัน `loop` เพิ่มโค้ดต่อไปนี้ที่ท้ายฟังก์ชัน `loop`:

    ```cpp
    timer.tick();
    ```

1. สร้างโค้ดนี้ อัปโหลดไปยัง Wio Terminal ของคุณ และทดสอบผ่าน serial monitor เมื่อคุณเห็นคำว่า `Ready` ใน serial monitor ให้กดปุ่ม C (ปุ่มด้านซ้ายมือ ใกล้กับสวิตช์เปิดปิด) และพูด เสียงพูด 4 วินาทีจะถูกจับ แปลงเป็นข้อความ จากนั้นส่งไปยังแอปฟังก์ชันของคุณ และตั้งเวลานับถอยหลัง ตรวจสอบให้แน่ใจว่าแอปฟังก์ชันของคุณกำลังทำงานอยู่ในเครื่อง

    คุณจะเห็นเมื่อเวลานับถอยหลังเริ่มต้น และเมื่อเวลาหมด

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Set a 2 minute and 27 second timer.","Offset":4700000,"Duration":35300000}
    Set a 2 minute and 27 second timer.
    {"seconds": 147}
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 คุณสามารถหาโค้ดนี้ได้ในโฟลเดอร์ [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal)

😀 โปรแกรมตั้งเวลาของคุณสำเร็จแล้ว!

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามอย่างเต็มที่เพื่อความถูกต้อง แต่โปรดทราบว่าการแปลอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่แม่นยำ เอกสารต้นฉบับในภาษาต้นทางควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ แนะนำให้ใช้บริการแปลภาษามนุษย์ที่เป็นมืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความที่ผิดพลาดซึ่งเกิดจากการใช้การแปลนี้