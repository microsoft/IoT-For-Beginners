<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6145a1d791731c8a9d0afd0a1bae5108",
  "translation_date": "2025-08-27T20:03:17+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/pi-proximity.md",
  "language_code": "th"
}
-->
# ตรวจจับความใกล้ - Raspberry Pi

ในส่วนนี้ของบทเรียน คุณจะเพิ่มเซ็นเซอร์ตรวจจับความใกล้ให้กับ Raspberry Pi และอ่านค่าระยะทางจากเซ็นเซอร์นั้น

## ฮาร์ดแวร์

Raspberry Pi ต้องการเซ็นเซอร์ตรวจจับความใกล้

เซ็นเซอร์ที่คุณจะใช้คือ [Grove Time of Flight distance sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html) เซ็นเซอร์นี้ใช้โมดูลเลเซอร์ในการวัดระยะทาง โดยมีช่วงการวัดตั้งแต่ 10 มม. ถึง 2000 มม. (1 ซม. - 2 ม.) และสามารถรายงานค่าระยะทางในช่วงนี้ได้อย่างแม่นยำ โดยระยะทางที่เกิน 1000 มม. จะรายงานเป็น 8109 มม.

ตัววัดระยะเลเซอร์อยู่ด้านหลังของเซ็นเซอร์ ซึ่งเป็นด้านตรงข้ามกับช่องเสียบ Grove

นี่คือเซ็นเซอร์แบบ I²C

### เชื่อมต่อเซ็นเซอร์ Time of Flight

เซ็นเซอร์ Time of Flight ของ Grove สามารถเชื่อมต่อกับ Raspberry Pi ได้

#### งาน - เชื่อมต่อเซ็นเซอร์ Time of Flight

เชื่อมต่อเซ็นเซอร์ Time of Flight

![เซ็นเซอร์ Time of Flight ของ Grove](../../../../../translated_images/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.th.png)

1. เสียบปลายด้านหนึ่งของสาย Grove เข้ากับช่องเสียบของเซ็นเซอร์ Time of Flight สายจะเสียบได้เพียงด้านเดียวเท่านั้น

1. เมื่อ Raspberry Pi ปิดอยู่ ให้เชื่อมต่อปลายอีกด้านของสาย Grove เข้ากับหนึ่งในช่องเสียบ I²C ที่ระบุว่า **I²C** บน Grove Base Hat ที่ติดตั้งอยู่บน Pi ช่องเสียบเหล่านี้อยู่แถวล่างสุด ตรงข้ามกับพิน GPIO และอยู่ใกล้กับช่องเสียบสายกล้อง

![เซ็นเซอร์ Time of Flight ของ Grove เชื่อมต่อกับช่องเสียบ I²C](../../../../../translated_images/pi-time-of-flight-sensor.58c8dc04eb3bfb57a7c3019f031433ef4d798d4d7603d565afbf6f3802840dba.th.png)

## เขียนโปรแกรมเซ็นเซอร์ Time of Flight

ตอนนี้ Raspberry Pi สามารถเขียนโปรแกรมเพื่อใช้งานเซ็นเซอร์ Time of Flight ที่เชื่อมต่ออยู่ได้แล้ว

### งาน - เขียนโปรแกรมเซ็นเซอร์ Time of Flight

เขียนโปรแกรมสำหรับอุปกรณ์

1. เปิด Raspberry Pi และรอให้บูตเสร็จ

1. เปิดโค้ด `fruit-quality-detector` ใน VS Code ไม่ว่าจะเปิดโดยตรงบน Pi หรือเชื่อมต่อผ่าน Remote SSH extension

1. ติดตั้งแพ็กเกจ rpi-vl53l0x ผ่าน Pip ซึ่งเป็นแพ็กเกจ Python ที่ใช้ในการทำงานร่วมกับเซ็นเซอร์วัดระยะ VL53L0X ติดตั้งโดยใช้คำสั่ง pip นี้:

    ```sh
    pip install rpi-vl53l0x
    ```

1. สร้างไฟล์ใหม่ในโปรเจกต์นี้ชื่อว่า `distance-sensor.py`

    > 💁 วิธีง่ายๆ ในการจำลองอุปกรณ์ IoT หลายตัวคือการเขียนแต่ละตัวในไฟล์ Python แยกกัน แล้วรันไฟล์เหล่านั้นพร้อมกัน

1. เพิ่มโค้ดต่อไปนี้ลงในไฟล์:

    ```python
    import time
    
    from grove.i2c import Bus
    from rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    โค้ดนี้นำเข้าไลบรารี Grove I²C bus และไลบรารีเซ็นเซอร์สำหรับฮาร์ดแวร์หลักที่อยู่ในเซ็นเซอร์ Time of Flight ของ Grove

1. ด้านล่างนี้ ให้เพิ่มโค้ดต่อไปนี้เพื่อเข้าถึงเซ็นเซอร์:

    ```python
    distance_sensor = VL53L0X(bus = Bus().bus)
    distance_sensor.begin()    
    ```

    โค้ดนี้ประกาศเซ็นเซอร์วัดระยะโดยใช้ Grove I²C bus จากนั้นเริ่มต้นเซ็นเซอร์

1. สุดท้าย เพิ่มลูปแบบไม่สิ้นสุดเพื่ออ่านค่าระยะทาง:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    โค้ดนี้รอค่าที่พร้อมอ่านจากเซ็นเซอร์ จากนั้นพิมพ์ค่าลงในคอนโซล

1. รันโค้ดนี้

    > 💁 อย่าลืมว่าไฟล์นี้ชื่อ `distance-sensor.py`! ตรวจสอบให้แน่ใจว่ารันไฟล์นี้ผ่าน Python ไม่ใช่ `app.py`

1. คุณจะเห็นค่าการวัดระยะทางปรากฏในคอนโซล ลองวางวัตถุใกล้เซ็นเซอร์แล้วคุณจะเห็นค่าการวัดระยะทาง:

    ```output
    pi@raspberrypi:~/fruit-quality-detector $ python3 distance_sensor.py 
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    ตัววัดระยะเลเซอร์อยู่ด้านหลังของเซ็นเซอร์ ดังนั้นตรวจสอบให้แน่ใจว่าใช้ด้านที่ถูกต้องเมื่อวัดระยะทาง

    ![ตัววัดระยะเลเซอร์ด้านหลังเซ็นเซอร์ Time of Flight ชี้ไปที่กล้วย](../../../../../translated_images/time-of-flight-banana.079921ad8b1496e4525dc26b4cdc71a076407aba3e72ba113ba2e38febae92c5.th.png)

> 💁 คุณสามารถหาโค้ดนี้ได้ในโฟลเดอร์ [code-proximity/pi](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/pi)

😀 โปรแกรมเซ็นเซอร์ตรวจจับความใกล้ของคุณสำเร็จแล้ว!

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้องมากที่สุด แต่โปรดทราบว่าการแปลโดยอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความที่ผิดพลาดซึ่งเกิดจากการใช้การแปลนี้