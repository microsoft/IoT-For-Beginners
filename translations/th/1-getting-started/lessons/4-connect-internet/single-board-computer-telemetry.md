<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-27T21:14:47+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "th"
}
-->
# ควบคุมไฟกลางคืนของคุณผ่านอินเทอร์เน็ต - ฮาร์ดแวร์ IoT เสมือนและ Raspberry Pi

ในส่วนนี้ของบทเรียน คุณจะส่งข้อมูลเทเลเมทรีเกี่ยวกับระดับแสงจาก Raspberry Pi หรืออุปกรณ์ IoT เสมือนไปยัง MQTT broker

## ส่งข้อมูลเทเลเมทรี

ขั้นตอนถัดไปคือการสร้างเอกสาร JSON ที่มีข้อมูลเทเลเมทรีและส่งไปยัง MQTT broker

### งานที่ต้องทำ

ส่งข้อมูลเทเลเมทรีไปยัง MQTT broker

1. เปิดโปรเจกต์ไฟกลางคืนใน VS Code

1. หากคุณใช้อุปกรณ์ IoT เสมือน ให้ตรวจสอบว่าเทอร์มินัลกำลังรันสภาพแวดล้อมเสมือนอยู่ หากคุณใช้ Raspberry Pi คุณจะไม่ต้องใช้สภาพแวดล้อมเสมือน

1. เพิ่มการนำเข้า (import) ต่อไปนี้ที่ด้านบนของไฟล์ `app.py`:

    ```python
    import json
    ```

    ไลบรารี `json` ใช้สำหรับเข้ารหัสข้อมูลเทเลเมทรีให้อยู่ในรูปแบบเอกสาร JSON

1. เพิ่มโค้ดต่อไปนี้หลังจากการประกาศ `client_name`:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    `client_telemetry_topic` คือ MQTT topic ที่อุปกรณ์จะใช้ในการส่งข้อมูลระดับแสง

1. แทนที่เนื้อหาภายในลูป `while True:` ที่อยู่ท้ายไฟล์ด้วยโค้ดต่อไปนี้:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    โค้ดนี้จะบรรจุระดับแสงลงในเอกสาร JSON และส่งไปยัง MQTT broker จากนั้นจะหยุดพักเพื่อช่วยลดความถี่ในการส่งข้อความ

1. รันโค้ดในลักษณะเดียวกับที่คุณรันโค้ดในส่วนก่อนหน้าของงาน หากคุณใช้อุปกรณ์ IoT เสมือน ให้ตรวจสอบว่าแอป CounterFit กำลังทำงานอยู่ และเซ็นเซอร์แสงและ LED ได้ถูกสร้างขึ้นในพินที่ถูกต้องแล้ว

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 คุณสามารถค้นหาโค้ดนี้ได้ในโฟลเดอร์ [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) หรือ [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi)

😀 คุณได้ส่งข้อมูลเทเลเมทรีจากอุปกรณ์ของคุณสำเร็จแล้ว

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้อง แต่โปรดทราบว่าการแปลอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความผิดที่เกิดจากการใช้การแปลนี้