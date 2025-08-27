<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c527ce85d69b1a3875366ec61cbed8aa",
  "translation_date": "2025-08-27T21:15:12+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-commands.md",
  "language_code": "th"
}
-->
# ควบคุมไฟกลางคืนของคุณผ่านอินเทอร์เน็ต - ฮาร์ดแวร์ IoT เสมือนและ Raspberry Pi

ในส่วนนี้ของบทเรียน คุณจะสมัครรับคำสั่งที่ส่งมาจาก MQTT broker ไปยัง Raspberry Pi หรืออุปกรณ์ IoT เสมือนของคุณ

## สมัครรับคำสั่ง

ขั้นตอนต่อไปคือการสมัครรับคำสั่งที่ส่งมาจาก MQTT broker และตอบสนองต่อคำสั่งเหล่านั้น

### งานที่ต้องทำ

สมัครรับคำสั่ง

1. เปิดโปรเจกต์ไฟกลางคืนใน VS Code

1. หากคุณใช้อุปกรณ์ IoT เสมือน ตรวจสอบให้แน่ใจว่าเทอร์มินัลกำลังทำงานในสภาพแวดล้อมเสมือน หากคุณใช้ Raspberry Pi คุณจะไม่ต้องใช้สภาพแวดล้อมเสมือน

1. เพิ่มโค้ดต่อไปนี้หลังจากการกำหนดค่า `client_telemetry_topic`:

    ```python
    server_command_topic = id + '/commands'
    ```

    `server_command_topic` คือ MQTT topic ที่อุปกรณ์จะสมัครรับเพื่อรับคำสั่งควบคุม LED

1. เพิ่มโค้ดต่อไปนี้เหนือ loop หลัก หลังจากบรรทัด `mqtt_client.loop_start()`:

    ```python
    def handle_command(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
        if payload['led_on']:
            led.on()
        else:
            led.off()
    
    mqtt_client.subscribe(server_command_topic)
    mqtt_client.on_message = handle_command
    ```

    โค้ดนี้กำหนดฟังก์ชัน `handle_command` ซึ่งอ่านข้อความในรูปแบบเอกสาร JSON และค้นหาค่าของ property `led_on` หากตั้งค่าเป็น `True` LED จะเปิด หากไม่ใช่ LED จะปิด

    MQTT client จะสมัครรับ topic ที่เซิร์ฟเวอร์จะส่งข้อความ และตั้งค่าให้ฟังก์ชัน `handle_command` ถูกเรียกเมื่อมีข้อความเข้ามา

    > 💁 ตัวจัดการ `on_message` จะถูกเรียกใช้สำหรับทุก topic ที่สมัครรับ หากคุณเขียนโค้ดที่ฟังหลาย topic ในภายหลัง คุณสามารถดึง topic ที่ข้อความถูกส่งมาจาก object `message` ที่ถูกส่งไปยังฟังก์ชันจัดการ

1. รันโค้ดในลักษณะเดียวกับที่คุณรันโค้ดจากส่วนก่อนหน้าของงาน หากคุณใช้อุปกรณ์ IoT เสมือน ตรวจสอบให้แน่ใจว่าแอป CounterFit กำลังทำงาน และเซ็นเซอร์แสงและ LED ถูกสร้างขึ้นบนพินที่ถูกต้อง

1. ปรับระดับแสงที่ตรวจจับได้โดยอุปกรณ์จริงหรืออุปกรณ์เสมือน ข้อความที่ได้รับและคำสั่งที่ส่งจะถูกเขียนลงในเทอร์มินัล LED จะเปิดและปิดตามระดับแสง

> 💁 คุณสามารถค้นหาโค้ดนี้ได้ในโฟลเดอร์ [code-commands/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/virtual-device) หรือ [code-commands/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/pi)

😀 คุณได้เขียนโค้ดให้อุปกรณ์ของคุณตอบสนองต่อคำสั่งจาก MQTT broker สำเร็จแล้ว

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้องมากที่สุด แต่โปรดทราบว่าการแปลอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความผิดที่เกิดจากการใช้การแปลนี้