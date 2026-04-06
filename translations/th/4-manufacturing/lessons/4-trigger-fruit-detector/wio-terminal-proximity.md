# ตรวจจับความใกล้ - Wio Terminal

ในส่วนนี้ของบทเรียน คุณจะเพิ่มเซ็นเซอร์วัดระยะทางให้กับ Wio Terminal และอ่านค่าระยะทางจากเซ็นเซอร์นั้น

## ฮาร์ดแวร์

Wio Terminal ต้องการเซ็นเซอร์วัดระยะทาง

เซ็นเซอร์ที่คุณจะใช้คือ [Grove Time of Flight distance sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html) เซ็นเซอร์นี้ใช้โมดูลเลเซอร์สำหรับการวัดระยะทาง โดยมีช่วงการวัดตั้งแต่ 10 มม. ถึง 2000 มม. (1 ซม. - 2 ม.) และสามารถรายงานค่าในช่วงนี้ได้อย่างแม่นยำ โดยค่าที่เกิน 1000 มม. จะถูกรายงานเป็น 8109 มม.

เครื่องวัดระยะด้วยเลเซอร์จะอยู่ด้านหลังของเซ็นเซอร์ ซึ่งเป็นด้านตรงข้ามกับช่องเสียบ Grove

นี่คือเซ็นเซอร์แบบ I2C

### เชื่อมต่อเซ็นเซอร์ Time of Flight

เซ็นเซอร์ Grove Time of Flight สามารถเชื่อมต่อกับ Wio Terminal ได้

#### งาน - เชื่อมต่อเซ็นเซอร์ Time of Flight

เชื่อมต่อเซ็นเซอร์ Time of Flight

![เซ็นเซอร์ Grove Time of Flight](../../../../../translated_images/th/grove-time-of-flight-sensor.d82ff2165bfded9f.webp)

1. เสียบปลายด้านหนึ่งของสาย Grove เข้ากับช่องเสียบของเซ็นเซอร์ Time of Flight สายจะเสียบได้เพียงด้านเดียว

1. เมื่อ Wio Terminal ไม่ได้เชื่อมต่อกับคอมพิวเตอร์หรือแหล่งจ่ายไฟอื่น ๆ ให้เชื่อมต่อปลายอีกด้านของสาย Grove เข้ากับช่องเสียบ Grove ด้านซ้ายของ Wio Terminal เมื่อมองที่หน้าจอ ช่องนี้อยู่ใกล้กับปุ่มเปิด/ปิดเครื่องมากที่สุด และเป็นช่องที่รองรับทั้งดิจิทัลและ I2C

![เซ็นเซอร์ Grove Time of Flight เชื่อมต่อกับช่องเสียบด้านซ้าย](../../../../../translated_images/th/wio-time-of-flight-sensor.c4c182131d2ea73d.webp)

1. ตอนนี้คุณสามารถเชื่อมต่อ Wio Terminal กับคอมพิวเตอร์ของคุณได้แล้ว

## เขียนโปรแกรมสำหรับเซ็นเซอร์ Time of Flight

ตอนนี้ Wio Terminal สามารถเขียนโปรแกรมเพื่อใช้งานเซ็นเซอร์ Time of Flight ที่เชื่อมต่ออยู่ได้

### งาน - เขียนโปรแกรมสำหรับเซ็นเซอร์ Time of Flight

1. สร้างโปรเจกต์ใหม่สำหรับ Wio Terminal โดยใช้ PlatformIO ตั้งชื่อโปรเจกต์นี้ว่า `distance-sensor` เพิ่มโค้ดในฟังก์ชัน `setup` เพื่อกำหนดค่าพอร์ตอนุกรม

1. เพิ่มการพึ่งพาไลบรารีสำหรับ Seeed Grove Time of Flight Distance Sensor ในไฟล์ `platformio.ini` ของโปรเจกต์:

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

1. ใน `main.cpp` เพิ่มโค้ดต่อไปนี้ใต้คำสั่ง include ที่มีอยู่แล้ว เพื่อประกาศอินสแตนซ์ของคลาส `Seeed_vl53l0x` สำหรับใช้งานกับเซ็นเซอร์ Time of Flight:

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

1. เพิ่มโค้ดต่อไปนี้ที่ด้านล่างของฟังก์ชัน `setup` เพื่อเริ่มต้นเซ็นเซอร์:

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

1. ในฟังก์ชัน `loop` อ่านค่าจากเซ็นเซอร์:

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    โค้ดนี้จะเริ่มต้นโครงสร้างข้อมูลเพื่ออ่านค่า จากนั้นส่งโครงสร้างข้อมูลนี้ไปยังเมธอด `PerformSingleRangingMeasurement` ซึ่งจะเติมค่าการวัดระยะทางลงไป

1. ด้านล่างนี้ ให้เขียนค่าการวัดระยะทางออกมา จากนั้นหน่วงเวลา 1 วินาที:

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

1. สร้าง อัปโหลด และรันโค้ดนี้ คุณจะสามารถเห็นค่าการวัดระยะทางใน Serial Monitor วางวัตถุใกล้กับเซ็นเซอร์ แล้วคุณจะเห็นค่าการวัดระยะทาง:

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    เครื่องวัดระยะด้วยเลเซอร์อยู่ด้านหลังของเซ็นเซอร์ ดังนั้นให้แน่ใจว่าคุณใช้ด้านที่ถูกต้องเมื่อวัดระยะทาง

    ![เครื่องวัดระยะบนด้านหลังของเซ็นเซอร์ Time of Flight ชี้ไปที่กล้วย](../../../../../translated_images/th/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 คุณสามารถหาโค้ดนี้ได้ในโฟลเดอร์ [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal)

😀 โปรแกรมเซ็นเซอร์วัดระยะทางของคุณสำเร็จแล้ว!

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้องมากที่สุด แต่โปรดทราบว่าการแปลโดยอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความผิดที่เกิดจากการใช้การแปลนี้