<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-27T21:15:34+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "th"
}
-->
# ควบคุมไฟกลางคืนของคุณผ่านอินเทอร์เน็ต - Wio Terminal

ในส่วนนี้ของบทเรียน คุณจะส่งข้อมูลเทเลเมทรีเกี่ยวกับระดับแสงจาก Wio Terminal ของคุณไปยัง MQTT broker

## ติดตั้งไลบรารี JSON สำหรับ Arduino

วิธีที่นิยมในการส่งข้อความผ่าน MQTT คือการใช้ JSON มีไลบรารีสำหรับ Arduino ที่ช่วยให้อ่านและเขียนเอกสาร JSON ได้ง่ายขึ้น

### งานที่ต้องทำ

ติดตั้งไลบรารี JSON สำหรับ Arduino

1. เปิดโปรเจกต์ไฟกลางคืนใน VS Code

1. เพิ่มบรรทัดต่อไปนี้เป็นบรรทัดเพิ่มเติมในรายการ `lib_deps` ในไฟล์ `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    สิ่งนี้จะนำเข้า [ArduinoJson](https://arduinojson.org) ซึ่งเป็นไลบรารี JSON สำหรับ Arduino

## ส่งข้อมูลเทเลเมทรี

ขั้นตอนต่อไปคือการสร้างเอกสาร JSON ที่มีข้อมูลเทเลเมทรีและส่งไปยัง MQTT broker

### งานที่ต้องทำ - ส่งข้อมูลเทเลเมทรี

ส่งข้อมูลเทเลเมทรีไปยัง MQTT broker

1. เพิ่มโค้ดต่อไปนี้ที่ด้านล่างของไฟล์ `config.h` เพื่อกำหนดชื่อหัวข้อเทเลเมทรีสำหรับ MQTT broker:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC` คือหัวข้อที่อุปกรณ์จะใช้ในการส่งระดับแสง

1. เปิดไฟล์ `main.cpp`

1. เพิ่มคำสั่ง `#include` ต่อไปนี้ที่ด้านบนของไฟล์:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. เพิ่มโค้ดต่อไปนี้ภายในฟังก์ชัน `loop` ก่อนคำสั่ง `delay`:

    ```cpp
    int light = analogRead(WIO_LIGHT);

    DynamicJsonDocument doc(1024);
    doc["light"] = light;

    string telemetry;
    serializeJson(doc, telemetry);

    Serial.print("Sending telemetry ");
    Serial.println(telemetry.c_str());

    client.publish(CLIENT_TELEMETRY_TOPIC.c_str(), telemetry.c_str());
    ```

    โค้ดนี้จะอ่านระดับแสงและสร้างเอกสาร JSON โดยใช้ ArduinoJson ซึ่งมีข้อมูลระดับแสงนี้ จากนั้นจะถูกแปลงเป็นสตริงและส่งไปยังหัวข้อเทเลเมทรี MQTT โดย MQTT client

1. อัปโหลดโค้ดไปยัง Wio Terminal ของคุณ และใช้ Serial Monitor เพื่อดูระดับแสงที่ถูกส่งไปยัง MQTT broker

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 คุณสามารถค้นหาโค้ดนี้ได้ในโฟลเดอร์ [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal)

😀 คุณได้ส่งข้อมูลเทเลเมทรีจากอุปกรณ์ของคุณสำเร็จแล้ว

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้อง แต่โปรดทราบว่าการแปลโดยอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความผิดที่เกิดจากการใช้การแปลนี้