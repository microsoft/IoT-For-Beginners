<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4efc74299e19f5d08f2f3f34451a11ba",
  "translation_date": "2025-08-27T22:07:33+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/single-board-computer-temp-publish.md",
  "language_code": "th"
}
-->
# เผยแพร่อุณหภูมิ - ฮาร์ดแวร์ IoT เสมือนและ Raspberry Pi

ในส่วนนี้ของบทเรียน คุณจะเผยแพร่มูลค่าอุณหภูมิที่ตรวจจับได้โดย Raspberry Pi หรืออุปกรณ์ IoT เสมือนผ่าน MQTT เพื่อให้สามารถนำไปใช้คำนวณ GDD ในภายหลัง

## เผยแพร่อุณหภูมิ

เมื่ออ่านค่าอุณหภูมิแล้ว สามารถเผยแพร่ผ่าน MQTT ไปยังโค้ด 'เซิร์ฟเวอร์' ที่จะอ่านค่าและจัดเก็บไว้เพื่อใช้ในการคำนวณ GDD

### งาน - เผยแพร่อุณหภูมิ

เขียนโปรแกรมให้อุปกรณ์เผยแพร่ข้อมูลอุณหภูมิ

1. เปิดโปรเจกต์แอป `temperature-sensor` หากยังไม่ได้เปิด

1. ทำซ้ำขั้นตอนที่คุณทำในบทเรียนที่ 4 เพื่อเชื่อมต่อกับ MQTT และส่งข้อมูล คุณจะใช้ Mosquitto broker สาธารณะตัวเดิม

    ขั้นตอนสำหรับสิ่งนี้คือ:

    - เพิ่มแพ็กเกจ pip ของ MQTT
    - เพิ่มโค้ดเพื่อเชื่อมต่อกับ MQTT broker
    - เพิ่มโค้ดเพื่อเผยแพร่ข้อมูล

    > ⚠️ ดู [คำแนะนำในการเชื่อมต่อกับ MQTT](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md) และ [คำแนะนำในการส่งข้อมูล](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md) จากบทเรียนที่ 4 หากจำเป็น

1. ตรวจสอบให้แน่ใจว่า `client_name` สะท้อนชื่อโปรเจกต์นี้:

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. สำหรับข้อมูลที่ส่งออก แทนที่จะส่งค่าความสว่าง ให้ส่งค่าอุณหภูมิที่อ่านจากเซ็นเซอร์ DHT ใน property ของเอกสาร JSON ที่ชื่อว่า `temperature`:

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. ค่าอุณหภูมิไม่จำเป็นต้องอ่านบ่อยนัก - มันจะไม่เปลี่ยนแปลงมากในช่วงเวลาสั้น ๆ ดังนั้นตั้งค่า `time.sleep` เป็น 10 นาที:

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 ฟังก์ชัน `sleep` ใช้เวลาในหน่วยวินาที ดังนั้นเพื่อให้อ่านง่ายขึ้น ค่าเวลาจะถูกส่งผ่านเป็นผลลัพธ์ของการคำนวณ 60 วินาทีในหนึ่งนาที ดังนั้น 10 x (60 วินาทีในหนึ่งนาที) จะให้การหน่วงเวลา 10 นาที

1. รันโค้ดในลักษณะเดียวกับที่คุณรันโค้ดจากส่วนก่อนหน้าของงาน หากคุณใช้อุปกรณ์ IoT เสมือน ตรวจสอบให้แน่ใจว่าแอป CounterFit กำลังทำงานอยู่และเซ็นเซอร์ความชื้นและอุณหภูมิถูกสร้างขึ้นบนพินที่ถูกต้อง

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 คุณสามารถค้นหาโค้ดนี้ได้ในโฟลเดอร์ [code-publish-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/virtual-device) หรือ [code-publish-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/pi)

😀 คุณได้เผยแพร่อุณหภูมิเป็นข้อมูลจากอุปกรณ์ของคุณเรียบร้อยแล้ว

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้องมากที่สุด แต่โปรดทราบว่าการแปลอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความที่ผิดพลาดซึ่งเกิดจากการใช้การแปลนี้