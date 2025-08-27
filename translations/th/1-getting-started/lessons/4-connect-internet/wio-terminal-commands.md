<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-08-27T21:13:29+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "th"
}
-->
# ควบคุมไฟกลางคืนของคุณผ่านอินเทอร์เน็ต - Wio Terminal

ในส่วนนี้ของบทเรียน คุณจะสมัครรับคำสั่งที่ส่งมาจาก MQTT broker ไปยัง Wio Terminal ของคุณ

## สมัครรับคำสั่ง

ขั้นตอนถัดไปคือการสมัครรับคำสั่งที่ส่งมาจาก MQTT broker และตอบสนองต่อคำสั่งเหล่านั้น

### งานที่ต้องทำ

สมัครรับคำสั่ง

1. เปิดโปรเจกต์ไฟกลางคืนใน VS Code

1. เพิ่มโค้ดต่อไปนี้ที่ด้านล่างของไฟล์ `config.h` เพื่อกำหนดชื่อหัวข้อสำหรับคำสั่ง:

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    `SERVER_COMMAND_TOPIC` คือหัวข้อที่อุปกรณ์จะสมัครรับเพื่อรับคำสั่งควบคุม LED

1. เพิ่มบรรทัดต่อไปนี้ที่ท้ายฟังก์ชัน `reconnectMQTTClient` เพื่อสมัครรับหัวข้อคำสั่งเมื่อ MQTT client เชื่อมต่อใหม่:

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. เพิ่มโค้ดต่อไปนี้ด้านล่างฟังก์ชัน `reconnectMQTTClient`

    ```cpp
    void clientCallback(char *topic, uint8_t *payload, unsigned int length)
    {
        char buff[length + 1];
        for (int i = 0; i < length; i++)
        {
            buff[i] = (char)payload[i];
        }
        buff[length] = '\0';
    
        Serial.print("Message received:");
        Serial.println(buff);
    
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, buff);
        JsonObject obj = doc.as<JsonObject>();
    
        bool led_on = obj["led_on"];
    
        if (led_on)
            digitalWrite(D0, HIGH);
        else
            digitalWrite(D0, LOW);
    }
    ```

    ฟังก์ชันนี้จะเป็น callback ที่ MQTT client จะเรียกใช้เมื่อได้รับข้อความจากเซิร์ฟเวอร์

    ข้อความที่ได้รับจะมาในรูปแบบอาร์เรย์ของตัวเลข 8 บิตแบบ unsigned ดังนั้นจึงต้องแปลงเป็นอาร์เรย์ตัวอักษรเพื่อให้สามารถจัดการเป็นข้อความได้

    ข้อความมีเอกสาร JSON และจะถูกถอดรหัสโดยใช้ ArduinoJson library โดยจะอ่าน property `led_on` จากเอกสาร JSON และขึ้นอยู่กับค่าที่ได้รับ LED จะถูกเปิดหรือปิด

1. เพิ่มโค้ดต่อไปนี้ในฟังก์ชัน `createMQTTClient`:

    ```cpp
    client.setCallback(clientCallback);
    ```

    โค้ดนี้ตั้งค่า `clientCallback` เป็น callback ที่จะถูกเรียกใช้เมื่อมีข้อความถูกส่งมาจาก MQTT broker

    > 💁 ตัวจัดการ `clientCallback` จะถูกเรียกใช้สำหรับทุกหัวข้อที่สมัครรับ หากคุณเขียนโค้ดที่ฟังหลายหัวข้อในภายหลัง คุณสามารถรับหัวข้อที่ข้อความถูกส่งมาจากพารามิเตอร์ `topic` ที่ส่งไปยังฟังก์ชัน callback

1. อัปโหลดโค้ดไปยัง Wio Terminal ของคุณ และใช้ Serial Monitor เพื่อดูระดับแสงที่ถูกส่งไปยัง MQTT broker

1. ปรับระดับแสงที่ตรวจจับได้โดยอุปกรณ์จริงหรืออุปกรณ์เสมือน คุณจะเห็นข้อความที่ถูกส่งและคำสั่งที่ถูกส่งใน terminal นอกจากนี้คุณจะเห็น LED ถูกเปิดและปิดขึ้นอยู่กับระดับแสง

> 💁 คุณสามารถค้นหาโค้ดนี้ได้ในโฟลเดอร์ [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal)

😀 คุณได้เขียนโค้ดให้อุปกรณ์ของคุณตอบสนองต่อคำสั่งจาก MQTT broker สำเร็จแล้ว

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้องมากที่สุด แต่โปรดทราบว่าการแปลโดยอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาที่เป็นต้นฉบับควรถือว่าเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความผิดที่เกิดจากการใช้การแปลนี้