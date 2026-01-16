<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-27T21:14:10+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "th"
}
-->
# ควบคุมไฟกลางคืนของคุณผ่านอินเทอร์เน็ต - Wio Terminal

อุปกรณ์ IoT จำเป็นต้องเขียนโค้ดเพื่อสื่อสารกับ *test.mosquitto.org* โดยใช้ MQTT เพื่อส่งค่าข้อมูลจากเซ็นเซอร์วัดแสง และรับคำสั่งเพื่อควบคุม LED

ในส่วนนี้ของบทเรียน คุณจะเชื่อมต่อ Wio Terminal ของคุณกับ MQTT broker

## ติดตั้งไลบรารี WiFi และ MQTT สำหรับ Arduino

เพื่อสื่อสารกับ MQTT broker คุณจำเป็นต้องติดตั้งไลบรารี Arduino บางตัวเพื่อใช้งานชิป WiFi ใน Wio Terminal และสื่อสารกับ MQTT เมื่อพัฒนาอุปกรณ์ Arduino คุณสามารถใช้ไลบรารีที่หลากหลายซึ่งมีโค้ดโอเพ่นซอร์สและรองรับความสามารถที่หลากหลาย Seeed ได้เผยแพร่ไลบรารีสำหรับ Wio Terminal ที่ช่วยให้สามารถสื่อสารผ่าน WiFi ได้ นักพัฒนาคนอื่นๆ ก็ได้เผยแพร่ไลบรารีสำหรับสื่อสารกับ MQTT broker และคุณจะใช้ไลบรารีเหล่านี้กับอุปกรณ์ของคุณ

ไลบรารีเหล่านี้มาในรูปแบบโค้ดต้นฉบับที่สามารถนำเข้าไปยัง PlatformIO และคอมไพล์สำหรับอุปกรณ์ของคุณได้โดยอัตโนมัติ ด้วยวิธีนี้ ไลบรารี Arduino จะทำงานได้บนอุปกรณ์ใดๆ ที่รองรับเฟรมเวิร์ก Arduino โดยสมมติว่าอุปกรณ์นั้นมีฮาร์ดแวร์เฉพาะที่ไลบรารีนั้นต้องการ ไลบรารีบางตัว เช่น ไลบรารี WiFi ของ Seeed จะรองรับเฉพาะฮาร์ดแวร์บางประเภทเท่านั้น

ไลบรารีสามารถติดตั้งได้ทั้งในระดับโกลบอลและคอมไพล์เมื่อจำเป็น หรือในโปรเจกต์เฉพาะ สำหรับงานนี้ ไลบรารีจะถูกติดตั้งในโปรเจกต์

✅ คุณสามารถเรียนรู้เพิ่มเติมเกี่ยวกับการจัดการไลบรารีและวิธีค้นหาและติดตั้งไลบรารีได้ใน [เอกสาร PlatformIO library](https://docs.platformio.org/en/latest/librarymanager/index.html)

### งาน - ติดตั้งไลบรารี WiFi และ MQTT สำหรับ Arduino

ติดตั้งไลบรารี Arduino

1. เปิดโปรเจกต์ nightlight ใน VS Code

1. เพิ่มโค้ดต่อไปนี้ที่ท้ายไฟล์ `platformio.ini`:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    โค้ดนี้นำเข้าไลบรารี WiFi ของ Seeed ไวยากรณ์ `@ <number>` หมายถึงหมายเลขเวอร์ชันเฉพาะของไลบรารี

    > 💁 คุณสามารถลบ `@ <number>` เพื่อใช้เวอร์ชันล่าสุดของไลบรารีได้เสมอ แต่ไม่มีการรับประกันว่าเวอร์ชันใหม่จะทำงานร่วมกับโค้ดด้านล่างได้ โค้ดที่นี่ได้รับการทดสอบกับเวอร์ชันนี้ของไลบรารีแล้ว

    นี่คือทั้งหมดที่คุณต้องทำเพื่อเพิ่มไลบรารี ครั้งต่อไปที่ PlatformIO สร้างโปรเจกต์ มันจะดาวน์โหลดโค้ดต้นฉบับของไลบรารีเหล่านี้และคอมไพล์เข้าไปในโปรเจกต์ของคุณ

1. เพิ่มโค้ดต่อไปนี้ใน `lib_deps`:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    โค้ดนี้นำเข้า [PubSubClient](https://github.com/knolleary/pubsubclient) ซึ่งเป็น Arduino MQTT client

## เชื่อมต่อกับ WiFi

ตอนนี้ Wio Terminal สามารถเชื่อมต่อกับ WiFi ได้แล้ว

### งาน - เชื่อมต่อกับ WiFi

เชื่อมต่อ Wio Terminal กับ WiFi

1. สร้างไฟล์ใหม่ในโฟลเดอร์ `src` ชื่อ `config.h` คุณสามารถทำได้โดยเลือกโฟลเดอร์ `src` หรือไฟล์ `main.cpp` ด้านใน และเลือกปุ่ม **New file** จากตัวสำรวจไฟล์ ปุ่มนี้จะปรากฏขึ้นเมื่อเคอร์เซอร์ของคุณอยู่เหนือพื้นที่ตัวสำรวจไฟล์

    ![ปุ่มสร้างไฟล์ใหม่](../../../../../translated_images/th/vscode-new-file-button.182702340fe6723c.png)

1. เพิ่มโค้ดต่อไปนี้ในไฟล์นี้เพื่อกำหนดค่าคงที่สำหรับข้อมูล WiFi ของคุณ:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    แทนที่ `<SSID>` ด้วย SSID ของ WiFi ของคุณ และแทนที่ `<PASSWORD>` ด้วยรหัสผ่าน WiFi ของคุณ

1. เปิดไฟล์ `main.cpp`

1. เพิ่มคำสั่ง `#include` ต่อไปนี้ที่ด้านบนของไฟล์:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    คำสั่งนี้นำเข้าไฟล์เฮดเดอร์สำหรับไลบรารีที่คุณเพิ่มมาก่อนหน้านี้ รวมถึงไฟล์เฮดเดอร์ config ด้วย ไฟล์เฮดเดอร์เหล่านี้จำเป็นเพื่อบอกให้ PlatformIO นำโค้ดจากไลบรารีเข้ามา หากไม่ได้เพิ่มไฟล์เฮดเดอร์เหล่านี้ โค้ดบางส่วนจะไม่ถูกคอมไพล์และคุณจะได้รับข้อผิดพลาดจากคอมไพเลอร์

1. เพิ่มโค้ดต่อไปนี้เหนือฟังก์ชัน `setup`:

    ```cpp
    void connectWiFi()
    {
        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("Connecting to WiFi..");
            WiFi.begin(SSID, PASSWORD);
            delay(500);
        }
    
        Serial.println("Connected!");
    }
    ```

    โค้ดนี้จะวนลูปในขณะที่อุปกรณ์ยังไม่ได้เชื่อมต่อกับ WiFi และพยายามเชื่อมต่อโดยใช้ SSID และรหัสผ่านจากไฟล์เฮดเดอร์ config

1. เพิ่มคำสั่งเรียกใช้ฟังก์ชันนี้ที่ท้ายฟังก์ชัน `setup` หลังจากที่กำหนดค่าพินแล้ว

    ```cpp
    connectWiFi();
    ```

1. อัปโหลดโค้ดนี้ไปยังอุปกรณ์ของคุณเพื่อตรวจสอบว่า WiFi เชื่อมต่อได้หรือไม่ คุณควรเห็นผลลัพธ์ใน serial monitor

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## เชื่อมต่อกับ MQTT

เมื่อ Wio Terminal เชื่อมต่อกับ WiFi แล้ว มันสามารถเชื่อมต่อกับ MQTT broker ได้

### งาน - เชื่อมต่อกับ MQTT

เชื่อมต่อกับ MQTT broker

1. เพิ่มโค้ดต่อไปนี้ที่ท้ายไฟล์ `config.h` เพื่อกำหนดรายละเอียดการเชื่อมต่อสำหรับ MQTT broker:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    แทนที่ `<ID>` ด้วย ID ที่ไม่ซ้ำกันซึ่งจะใช้เป็นชื่อของ client อุปกรณ์นี้ และในภายหลังสำหรับหัวข้อที่อุปกรณ์นี้เผยแพร่และสมัครรับข้อมูล *test.mosquitto.org* broker เป็นสาธารณะและมีผู้ใช้งานจำนวนมาก รวมถึงนักเรียนคนอื่นๆ ที่ทำงานในงานนี้ การมีชื่อ client MQTT และชื่อหัวข้อที่ไม่ซ้ำกันจะช่วยให้โค้ดของคุณไม่ชนกับของคนอื่น คุณจะต้องใช้ ID นี้เมื่อคุณสร้างโค้ดฝั่งเซิร์ฟเวอร์ในงานนี้ด้วย

    > 💁 คุณสามารถใช้เว็บไซต์อย่าง [GUIDGen](https://www.guidgen.com) เพื่อสร้าง ID ที่ไม่ซ้ำกันได้

    `BROKER` คือ URL ของ MQTT broker

    `CLIENT_NAME` คือชื่อที่ไม่ซ้ำกันสำหรับ client MQTT นี้บน broker

1. เปิดไฟล์ `main.cpp` และเพิ่มโค้ดต่อไปนี้ใต้ฟังก์ชัน `connectWiFi` และเหนือฟังก์ชัน `setup`:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    โค้ดนี้สร้าง WiFi client โดยใช้ไลบรารี WiFi ของ Wio Terminal และใช้มันเพื่อสร้าง MQTT client

1. เพิ่มโค้ดต่อไปนี้ใต้โค้ดด้านบน:

    ```cpp
    void reconnectMQTTClient()
    {
        while (!client.connected())
        {
            Serial.print("Attempting MQTT connection...");
    
            if (client.connect(CLIENT_NAME.c_str()))
            {
                Serial.println("connected");
            }
            else
            {
                Serial.print("Retying in 5 seconds - failed, rc=");
                Serial.println(client.state());
                
                delay(5000);
            }
        }
    }
    ```

    ฟังก์ชันนี้ทดสอบการเชื่อมต่อกับ MQTT broker และเชื่อมต่อใหม่หากยังไม่ได้เชื่อมต่อ มันจะวนลูปในขณะที่ยังไม่ได้เชื่อมต่อและพยายามเชื่อมต่อโดยใช้ชื่อ client ที่ไม่ซ้ำกันซึ่งกำหนดไว้ในไฟล์เฮดเดอร์ config

    หากการเชื่อมต่อล้มเหลว มันจะลองใหม่หลังจาก 5 วินาที

1. เพิ่มโค้ดต่อไปนี้ใต้ฟังก์ชัน `reconnectMQTTClient`:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    โค้ดนี้กำหนด MQTT broker สำหรับ client รวมถึงกำหนด callback เมื่อมีข้อความเข้ามา จากนั้นพยายามเชื่อมต่อกับ broker

1. เรียกใช้ฟังก์ชัน `createMQTTClient` ในฟังก์ชัน `setup` หลังจากที่ WiFi เชื่อมต่อแล้ว

1. แทนที่ฟังก์ชัน `loop` ทั้งหมดด้วยโค้ดต่อไปนี้:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    โค้ดนี้เริ่มต้นด้วยการเชื่อมต่อใหม่กับ MQTT broker การเชื่อมต่อเหล่านี้สามารถถูกตัดขาดได้ง่าย ดังนั้นจึงควรตรวจสอบและเชื่อมต่อใหม่เป็นประจำหากจำเป็น จากนั้นเรียกใช้เมธอด `loop` บน MQTT client เพื่อประมวลผลข้อความใดๆ ที่เข้ามาในหัวข้อที่สมัครรับข้อมูล แอปนี้เป็น single-threaded ดังนั้นข้อความไม่สามารถรับได้ใน background thread จึงต้องจัดสรรเวลาใน main thread เพื่อประมวลผลข้อความที่รออยู่ในเครือข่าย

    สุดท้าย การหน่วงเวลา 2 วินาทีช่วยให้ระดับแสงไม่ถูกส่งบ่อยเกินไปและลดการใช้พลังงานของอุปกรณ์

1. อัปโหลดโค้ดไปยัง Wio Terminal ของคุณ และใช้ Serial Monitor เพื่อตรวจสอบว่าอุปกรณ์เชื่อมต่อกับ WiFi และ MQTT ได้หรือไม่

    ```output
    > Executing task: platformio device monitor <
    
    source /Users/jimbennett/GitHub/IoT-For-Beginners/1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal/nightlight/.venv/bin/activate
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    ```

> 💁 คุณสามารถค้นหาโค้ดนี้ได้ในโฟลเดอร์ [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal)

😀 คุณได้เชื่อมต่ออุปกรณ์ของคุณกับ MQTT broker สำเร็จแล้ว

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้อง แต่โปรดทราบว่าการแปลโดยอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความผิดที่เกิดจากการใช้การแปลนี้