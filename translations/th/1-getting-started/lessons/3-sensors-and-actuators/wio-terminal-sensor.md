<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7f4ad0ef54f248b85b92187c94cf9dcb",
  "translation_date": "2025-08-27T21:31:56+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-sensor.md",
  "language_code": "th"
}
-->
# เพิ่มเซ็นเซอร์ - Wio Terminal

ในส่วนนี้ของบทเรียน คุณจะใช้เซ็นเซอร์วัดแสงบน Wio Terminal ของคุณ

## ฮาร์ดแวร์

เซ็นเซอร์สำหรับบทเรียนนี้คือ **เซ็นเซอร์วัดแสง** ที่ใช้ [โฟโตไดโอด](https://wikipedia.org/wiki/Photodiode) ในการแปลงแสงเป็นสัญญาณไฟฟ้า นี่คือเซ็นเซอร์แบบแอนะล็อกที่ส่งค่าจำนวนเต็มตั้งแต่ 0 ถึง 1,023 ซึ่งแสดงถึงปริมาณแสงโดยเปรียบเทียบ แต่ไม่ได้อ้างอิงกับหน่วยมาตรฐานใด ๆ เช่น [ลักซ์](https://wikipedia.org/wiki/Lux)

เซ็นเซอร์วัดแสงนี้ถูกติดตั้งอยู่ในตัว Wio Terminal และสามารถมองเห็นได้ผ่านหน้าต่างพลาสติกใสที่ด้านหลัง

![เซ็นเซอร์วัดแสงที่ด้านหลังของ Wio Terminal](../../../../../translated_images/th/wio-light-sensor.b1f529f3c95f5165.png)

## เขียนโปรแกรมสำหรับเซ็นเซอร์วัดแสง

ตอนนี้คุณสามารถเขียนโปรแกรมให้ใช้งานเซ็นเซอร์วัดแสงในตัวได้แล้ว

### งานที่ต้องทำ

เขียนโปรแกรมให้กับอุปกรณ์

1. เปิดโปรเจกต์ nightlight ใน VS Code ที่คุณสร้างไว้ในส่วนก่อนหน้าของงานนี้

1. เพิ่มบรรทัดต่อไปนี้ที่ด้านล่างของฟังก์ชัน `setup`:

    ```cpp
    pinMode(WIO_LIGHT, INPUT);
    ```

    บรรทัดนี้ใช้กำหนดค่าขา (pins) ที่ใช้สื่อสารกับฮาร์ดแวร์เซ็นเซอร์

    ขา `WIO_LIGHT` คือหมายเลขของ GPIO pin ที่เชื่อมต่อกับเซ็นเซอร์วัดแสงในตัว ขานี้ถูกตั้งค่าเป็น `INPUT` หมายความว่ามันเชื่อมต่อกับเซ็นเซอร์และจะอ่านข้อมูลจากขานี้

1. ลบเนื้อหาทั้งหมดในฟังก์ชัน `loop`

1. เพิ่มโค้ดต่อไปนี้ในฟังก์ชัน `loop` ที่ว่างเปล่าในตอนนี้

    ```cpp
    int light = analogRead(WIO_LIGHT);
    Serial.print("Light value: ");
    Serial.println(light);
    ```

    โค้ดนี้จะอ่านค่าจากขา `WIO_LIGHT` แบบแอนะล็อก ซึ่งจะได้ค่าตั้งแต่ 0-1,023 จากเซ็นเซอร์วัดแสงในตัว ค่านี้จะถูกส่งไปยังพอร์ตอนุกรม (Serial Port) เพื่อให้คุณสามารถอ่านค่าได้ใน Serial Monitor เมื่อโค้ดนี้กำลังทำงาน `Serial.print` จะเขียนข้อความโดยไม่มีการขึ้นบรรทัดใหม่ ดังนั้นแต่ละบรรทัดจะเริ่มต้นด้วย `Light value:` และลงท้ายด้วยค่าของแสงจริง

1. เพิ่มดีเลย์เล็กน้อยหนึ่งวินาที (1,000ms) ที่ท้ายฟังก์ชัน `loop` เนื่องจากไม่จำเป็นต้องตรวจสอบระดับแสงอย่างต่อเนื่อง การเพิ่มดีเลย์ช่วยลดการใช้พลังงานของอุปกรณ์

    ```cpp
    delay(1000);
    ```

1. เชื่อมต่อ Wio Terminal กับคอมพิวเตอร์ของคุณอีกครั้ง และอัปโหลดโค้ดใหม่เหมือนที่คุณทำในครั้งก่อน

1. เปิด Serial Monitor ค่าของแสงจะถูกแสดงในเทอร์มินัล ลองปิดและเปิดเซ็นเซอร์วัดแสงที่ด้านหลังของ Wio Terminal แล้วค่าจะเปลี่ยนไป

    ```output
    > Executing task: platformio device monitor <

    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Light value: 4
    Light value: 5
    Light value: 4
    Light value: 158
    Light value: 343
    Light value: 348
    Light value: 344
    ```

> 💁 คุณสามารถหาโค้ดนี้ได้ในโฟลเดอร์ [code-sensor/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/wio-terminal)

😀 การเพิ่มเซ็นเซอร์ในโปรแกรม nightlight ของคุณสำเร็จแล้ว!

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้องมากที่สุด แต่โปรดทราบว่าการแปลอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความที่ผิดพลาดซึ่งเกิดจากการใช้การแปลนี้