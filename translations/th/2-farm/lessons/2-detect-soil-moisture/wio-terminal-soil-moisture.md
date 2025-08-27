<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0d55caa8c23d73635b7559102cd17b8a",
  "translation_date": "2025-08-27T21:46:53+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/wio-terminal-soil-moisture.md",
  "language_code": "th"
}
-->
# วัดความชื้นในดิน - Wio Terminal

ในส่วนนี้ของบทเรียน คุณจะเพิ่มเซ็นเซอร์วัดความชื้นในดินแบบ capacitive เข้ากับ Wio Terminal และอ่านค่าจากเซ็นเซอร์นี้

## ฮาร์ดแวร์

Wio Terminal ต้องการเซ็นเซอร์วัดความชื้นในดินแบบ capacitive

เซ็นเซอร์ที่คุณจะใช้คือ [Capacitive Soil Moisture Sensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html) ซึ่งวัดความชื้นในดินโดยการตรวจจับค่าความจุไฟฟ้าของดิน ซึ่งเป็นคุณสมบัติที่เปลี่ยนแปลงไปตามความชื้นในดิน เมื่อความชื้นในดินเพิ่มขึ้น ค่าแรงดันไฟฟ้าจะลดลง

เซ็นเซอร์นี้เป็นเซ็นเซอร์แบบอนาล็อก ดังนั้นจึงเชื่อมต่อกับขาอนาล็อกบน Wio Terminal โดยใช้ ADC บนบอร์ดเพื่อสร้างค่าตั้งแต่ 0-1,023

### เชื่อมต่อเซ็นเซอร์วัดความชื้นในดิน

เซ็นเซอร์วัดความชื้นในดินแบบ Grove สามารถเชื่อมต่อกับพอร์ตอนาล็อก/ดิจิทัลที่ปรับแต่งได้ของ Wio Terminal

#### งาน - เชื่อมต่อเซ็นเซอร์วัดความชื้นในดิน

เชื่อมต่อเซ็นเซอร์วัดความชื้นในดิน

![เซ็นเซอร์วัดความชื้นในดินแบบ Grove](../../../../../translated_images/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.th.png)

1. เสียบปลายด้านหนึ่งของสาย Grove เข้ากับช่องเสียบของเซ็นเซอร์วัดความชื้นในดิน สายจะเสียบได้เพียงด้านเดียว

1. เมื่อ Wio Terminal ไม่ได้เชื่อมต่อกับคอมพิวเตอร์หรือแหล่งจ่ายไฟอื่น ให้เชื่อมต่อปลายอีกด้านของสาย Grove เข้ากับช่องเสียบ Grove ด้านขวาบน Wio Terminal เมื่อมองที่หน้าจอ ช่องนี้อยู่ไกลจากปุ่มเปิด/ปิดมากที่สุด

![เซ็นเซอร์วัดความชื้นในดินแบบ Grove เชื่อมต่อกับช่องเสียบด้านขวา](../../../../../translated_images/wio-soil-moisture-sensor.46919b61c3f6cb7497662251b29038ee0e57a4c8b9d071feb996c3b0d7f65aaf.th.png)

1. เสียบเซ็นเซอร์วัดความชื้นในดินลงในดิน เซ็นเซอร์มี 'เส้นตำแหน่งสูงสุด' - เส้นสีขาวที่พาดผ่านเซ็นเซอร์ เสียบเซ็นเซอร์ลงไปจนถึงเส้นนี้แต่ไม่เกินเส้นนี้

![เซ็นเซอร์วัดความชื้นในดินแบบ Grove ในดิน](../../../../../translated_images/soil-moisture-sensor-in-soil.bfad91002bda5e960f8c51ee64b02ee59b32c8c717e3515a2c945f33e614e403.th.png)

1. ตอนนี้คุณสามารถเชื่อมต่อ Wio Terminal กับคอมพิวเตอร์ของคุณได้แล้ว

## เขียนโปรแกรมสำหรับเซ็นเซอร์วัดความชื้นในดิน

ตอนนี้ Wio Terminal สามารถเขียนโปรแกรมเพื่อใช้งานเซ็นเซอร์วัดความชื้นในดินที่เชื่อมต่ออยู่ได้

### งาน - เขียนโปรแกรมสำหรับเซ็นเซอร์วัดความชื้นในดิน

เขียนโปรแกรมสำหรับอุปกรณ์

1. สร้างโปรเจกต์ใหม่สำหรับ Wio Terminal โดยใช้ PlatformIO ตั้งชื่อโปรเจกต์นี้ว่า `soil-moisture-sensor` เพิ่มโค้ดในฟังก์ชัน `setup` เพื่อกำหนดค่าพอร์ตอนุกรม

    > ⚠️ คุณสามารถดู [คำแนะนำในการสร้างโปรเจกต์ PlatformIO ในโปรเจกต์ 1 บทเรียน 1 ได้หากจำเป็น](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project)

1. ไม่มีไลบรารีสำหรับเซ็นเซอร์นี้ แต่คุณสามารถอ่านค่าจากขาอนาล็อกโดยใช้ฟังก์ชัน [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/) ที่มีอยู่ใน Arduino เริ่มต้นด้วยการกำหนดค่าขาอนาล็อกสำหรับการรับค่าเพื่อให้สามารถอ่านค่าแรงดันไฟฟ้าจากขาได้ โดยเพิ่มโค้ดต่อไปนี้ในฟังก์ชัน `setup`

    ```cpp
    pinMode(A0, INPUT);
    ```

    โค้ดนี้กำหนดให้ขา `A0` ซึ่งเป็นขาอนาล็อก/ดิจิทัลรวมกัน เป็นขาสำหรับรับค่าแรงดันไฟฟ้า

1. เพิ่มโค้ดต่อไปนี้ในฟังก์ชัน `loop` เพื่ออ่านค่าแรงดันไฟฟ้าจากขานี้:

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. ด้านล่างโค้ดนี้ เพิ่มโค้ดต่อไปนี้เพื่อพิมพ์ค่าที่อ่านได้ไปยังพอร์ตอนุกรม:

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. สุดท้าย เพิ่มคำสั่งหน่วงเวลา 10 วินาทีที่ท้ายโค้ด:

    ```cpp
    delay(10000);
    ```

1. สร้างและอัปโหลดโค้ดไปยัง Wio Terminal

    > ⚠️ คุณสามารถดู [คำแนะนำในการสร้างโปรเจกต์ PlatformIO ในโปรเจกต์ 1 บทเรียน 1 ได้หากจำเป็น](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app)

1. เมื่ออัปโหลดเสร็จแล้ว คุณสามารถตรวจสอบค่าความชื้นในดินได้โดยใช้ serial monitor เติมน้ำลงในดิน หรือดึงเซ็นเซอร์ออกจากดิน แล้วดูค่าที่เปลี่ยนแปลง

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Soil Moisture: 526
    Soil Moisture: 529
    Soil Moisture: 521
    Soil Moisture: 494
    Soil Moisture: 454
    Soil Moisture: 456
    Soil Moisture: 395
    Soil Moisture: 388
    Soil Moisture: 394
    Soil Moisture: 391
    ```

    ในตัวอย่างผลลัพธ์ด้านบน คุณจะเห็นค่าแรงดันไฟฟ้าลดลงเมื่อเติมน้ำ

> 💁 คุณสามารถค้นหาโค้ดนี้ได้ในโฟลเดอร์ [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal)

😀 โปรแกรมเซ็นเซอร์วัดความชื้นในดินของคุณสำเร็จแล้ว!

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้องมากที่สุด แต่โปรดทราบว่าการแปลโดยอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความผิดที่เกิดจากการใช้การแปลนี้