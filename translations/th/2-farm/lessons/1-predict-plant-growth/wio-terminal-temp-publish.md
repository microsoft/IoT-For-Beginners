<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-27T22:06:39+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "th"
}
-->
# เผยแพร่อุณหภูมิ - Wio Terminal

ในส่วนนี้ของบทเรียน คุณจะเผยแพร่อุณหภูมิที่ตรวจจับได้โดย Wio Terminal ผ่าน MQTT เพื่อให้สามารถนำไปใช้คำนวณ GDD ในภายหลังได้

## เผยแพร่อุณหภูมิ

เมื่ออ่านค่าอุณหภูมิได้แล้ว คุณสามารถเผยแพร่ข้อมูลผ่าน MQTT ไปยังโค้ด 'เซิร์ฟเวอร์' ที่จะอ่านค่าและจัดเก็บข้อมูลเพื่อใช้ในการคำนวณ GDD ได้ ไมโครคอนโทรลเลอร์ไม่ได้อ่านเวลาจากอินเทอร์เน็ตหรือมีนาฬิกาเรียลไทม์ในตัวโดยอัตโนมัติ อุปกรณ์จำเป็นต้องถูกโปรแกรมให้ทำสิ่งนี้ หากมีฮาร์ดแวร์ที่จำเป็น

เพื่อให้ง่ายขึ้นสำหรับบทเรียนนี้ จะไม่มีการส่งเวลาพร้อมกับข้อมูลเซ็นเซอร์ แต่สามารถเพิ่มเวลาได้ในโค้ดเซิร์ฟเวอร์เมื่อได้รับข้อความ

### งานที่ต้องทำ

โปรแกรมอุปกรณ์เพื่อเผยแพร่ข้อมูลอุณหภูมิ

1. เปิดโปรเจกต์ `temperature-sensor` ของ Wio Terminal

1. ทำซ้ำขั้นตอนที่คุณทำในบทเรียนที่ 4 เพื่อเชื่อมต่อกับ MQTT และส่งข้อมูลเทเลเมทรี โดยคุณจะใช้ Mosquitto broker สาธารณะตัวเดิม

    ขั้นตอนสำหรับสิ่งนี้คือ:

    - เพิ่มไลบรารี Seeed WiFi และ MQTT ลงในไฟล์ `.ini`
    - เพิ่มไฟล์การตั้งค่าและโค้ดเพื่อเชื่อมต่อกับ WiFi
    - เพิ่มโค้ดเพื่อเชื่อมต่อกับ MQTT broker
    - เพิ่มโค้ดเพื่อเผยแพร่ข้อมูลเทเลเมทรี

    > ⚠️ ดู [คำแนะนำในการเชื่อมต่อกับ MQTT](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) และ [คำแนะนำในการส่งข้อมูลเทเลเมทรี](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) จากบทเรียนที่ 4 หากจำเป็น

1. ตรวจสอบให้แน่ใจว่า `CLIENT_NAME` ในไฟล์เฮดเดอร์ `config.h` สะท้อนถึงโปรเจกต์นี้:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. สำหรับข้อมูลเทเลเมทรี แทนที่จะส่งค่าความสว่าง ให้ส่งค่าอุณหภูมิที่อ่านได้จากเซ็นเซอร์ DHT ในคุณสมบัติของเอกสาร JSON ที่เรียกว่า `temperature` โดยเปลี่ยนฟังก์ชัน `loop` ใน `main.cpp`:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. ค่าอุณหภูมิไม่จำเป็นต้องอ่านบ่อยนัก เพราะมันจะไม่เปลี่ยนแปลงมากในช่วงเวลาสั้น ๆ ดังนั้นตั้งค่า `delay` ในฟังก์ชัน `loop` เป็น 10 นาที:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 ฟังก์ชัน `delay` ใช้เวลาในหน่วยมิลลิวินาที ดังนั้นเพื่อให้อ่านค่าได้ง่ายขึ้น ค่าจะถูกส่งผ่านเป็นผลลัพธ์ของการคำนวณ 1,000ms ใน 1 วินาที, 60 วินาทีใน 1 นาที ดังนั้น 10 x (60 วินาทีใน 1 นาที) x (1000ms ใน 1 วินาที) จะให้ค่าหน่วงเวลา 10 นาที

1. อัปโหลดโปรแกรมนี้ไปยัง Wio Terminal ของคุณ และใช้ serial monitor เพื่อตรวจสอบว่าอุณหภูมิถูกส่งไปยัง MQTT broker หรือไม่

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"temperature":25}
    Sending telemetry {"temperature":25}
    ```

> 💁 คุณสามารถค้นหาโค้ดนี้ได้ในโฟลเดอร์ [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal)

😀 คุณได้เผยแพร่อุณหภูมิเป็นข้อมูลเทเลเมทรีจากอุปกรณ์ของคุณสำเร็จแล้ว

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้อง แต่โปรดทราบว่าการแปลโดยอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความผิดที่เกิดจากการใช้การแปลนี้