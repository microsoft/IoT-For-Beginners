<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "da6ae0a795cf06be33d23ca5b8493fc8",
  "translation_date": "2025-08-27T20:50:27+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-sensor.md",
  "language_code": "th"
}
-->
# อ่านข้อมูล GPS - Wio Terminal

ในส่วนนี้ของบทเรียน คุณจะเพิ่มเซ็นเซอร์ GPS ให้กับ Wio Terminal และอ่านค่าจากเซ็นเซอร์นี้

## ฮาร์ดแวร์

Wio Terminal ต้องการเซ็นเซอร์ GPS

เซ็นเซอร์ที่คุณจะใช้คือ [Grove GPS Air530 sensor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html) เซ็นเซอร์นี้สามารถเชื่อมต่อกับระบบ GPS หลายระบบเพื่อให้ได้ตำแหน่งที่รวดเร็วและแม่นยำ เซ็นเซอร์นี้ประกอบด้วย 2 ส่วน คือ อุปกรณ์อิเล็กทรอนิกส์หลักของเซ็นเซอร์ และเสาอากาศภายนอกที่เชื่อมต่อด้วยสายไฟบางๆ เพื่อรับคลื่นวิทยุจากดาวเทียม

นี่คือเซ็นเซอร์แบบ UART ซึ่งจะส่งข้อมูล GPS ผ่าน UART

### เชื่อมต่อเซ็นเซอร์ GPS

เซ็นเซอร์ Grove GPS สามารถเชื่อมต่อกับ Wio Terminal ได้

#### งาน - เชื่อมต่อเซ็นเซอร์ GPS

เชื่อมต่อเซ็นเซอร์ GPS

![เซ็นเซอร์ Grove GPS](../../../../../translated_images/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.th.png)

1. เสียบปลายด้านหนึ่งของสาย Grove เข้ากับช่องเสียบของเซ็นเซอร์ GPS สายจะเสียบได้เพียงด้านเดียวเท่านั้น

1. เมื่อ Wio Terminal ไม่ได้เชื่อมต่อกับคอมพิวเตอร์หรือแหล่งจ่ายไฟอื่น ให้เชื่อมต่อปลายอีกด้านของสาย Grove เข้ากับช่องเสียบ Grove ด้านซ้ายของ Wio Terminal (เมื่อมองที่หน้าจอ) ซึ่งเป็นช่องที่ใกล้กับปุ่มเปิด/ปิดมากที่สุด

    ![เซ็นเซอร์ Grove GPS เชื่อมต่อกับช่องเสียบด้านซ้าย](../../../../../translated_images/wio-gps-sensor.19fd52b81ce58095d5deb3d4e5a1fdd88818d76569b00b1f0d740c92dc986525.th.png)

1. วางเซ็นเซอร์ GPS ในตำแหน่งที่เสาอากาศที่เชื่อมต่อสามารถมองเห็นท้องฟ้าได้ - โดยเฉพาะใกล้หน้าต่างที่เปิดหรือภายนอกอาคาร การไม่มีสิ่งกีดขวางเสาอากาศจะช่วยให้สัญญาณชัดเจนขึ้น

1. ตอนนี้คุณสามารถเชื่อมต่อ Wio Terminal กับคอมพิวเตอร์ของคุณได้แล้ว

1. เซ็นเซอร์ GPS มีไฟ LED 2 ดวง - ไฟ LED สีน้ำเงินจะกระพริบเมื่อมีการส่งข้อมูล และไฟ LED สีเขียวจะกระพริบทุกวินาทีเมื่อรับข้อมูลจากดาวเทียม ตรวจสอบให้แน่ใจว่าไฟ LED สีน้ำเงินกระพริบเมื่อเปิด Wio Terminal หลังจากไม่กี่นาที ไฟ LED สีเขียวจะเริ่มกระพริบ - หากไม่กระพริบ คุณอาจต้องปรับตำแหน่งเสาอากาศ

## เขียนโปรแกรมสำหรับเซ็นเซอร์ GPS

ตอนนี้ Wio Terminal สามารถเขียนโปรแกรมเพื่อใช้งานเซ็นเซอร์ GPS ที่เชื่อมต่อได้แล้ว

### งาน - เขียนโปรแกรมสำหรับเซ็นเซอร์ GPS

เขียนโปรแกรมให้กับอุปกรณ์

1. สร้างโปรเจกต์ Wio Terminal ใหม่โดยใช้ PlatformIO ตั้งชื่อโปรเจกต์นี้ว่า `gps-sensor` เพิ่มโค้ดในฟังก์ชัน `setup` เพื่อกำหนดค่าพอร์ต serial

1. เพิ่มคำสั่ง include ด้านล่างนี้ที่ส่วนบนของไฟล์ `main.cpp` เพื่อรวมไฟล์ header ที่มีฟังก์ชันสำหรับกำหนดค่าพอร์ต Grove ด้านซ้ายสำหรับ UART

    ```cpp
    #include <wiring_private.h>
    ```

1. ด้านล่างนี้ ให้เพิ่มโค้ดบรรทัดต่อไปนี้เพื่อประกาศการเชื่อมต่อพอร์ต serial กับพอร์ต UART:

    ```cpp
    static Uart Serial3(&sercom3, PIN_WIRE_SCL, PIN_WIRE_SDA, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    ```

1. คุณต้องเพิ่มโค้ดบางส่วนเพื่อเปลี่ยนเส้นทางตัวจัดการสัญญาณภายในไปยังพอร์ต serial นี้ เพิ่มโค้ดด้านล่างนี้หลังจากการประกาศ `Serial3`:

    ```cpp
    void SERCOM3_0_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_1_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_2_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_3_Handler()
    {
        Serial3.IrqHandler();
    }
    ```

1. ในฟังก์ชัน `setup` ด้านล่างที่กำหนดค่าพอร์ต `Serial` ให้กำหนดค่าพอร์ต serial UART ด้วยโค้ดต่อไปนี้:

    ```cpp
    Serial3.begin(9600);

    while (!Serial3)
        ; // Wait for Serial3 to be ready

    delay(1000);
    ```

1. ด้านล่างโค้ดนี้ในฟังก์ชัน `setup` ให้เพิ่มโค้ดต่อไปนี้เพื่อเชื่อมต่อพิน Grove กับพอร์ต serial:

    ```cpp
    pinPeripheral(PIN_WIRE_SCL, PIO_SERCOM_ALT);
    ```

1. เพิ่มฟังก์ชันต่อไปนี้ก่อนฟังก์ชัน `loop` เพื่อส่งข้อมูล GPS ไปยัง serial monitor:

    ```cpp
    void printGPSData()
    {
        Serial.println(Serial3.readStringUntil('\n'));
    }
    ```

1. ในฟังก์ชัน `loop` ให้เพิ่มโค้ดต่อไปนี้เพื่ออ่านข้อมูลจากพอร์ต serial UART และพิมพ์ผลลัพธ์ไปยัง serial monitor:

    ```cpp
    while (Serial3.available() > 0)
    {
        printGPSData();
    }
    
    delay(1000);
    ```

    โค้ดนี้จะอ่านข้อมูลจากพอร์ต serial UART ฟังก์ชัน `readStringUntil` จะอ่านข้อมูลจนกว่าจะเจออักขระตัวสุดท้าย ซึ่งในกรณีนี้คือบรรทัดใหม่ (new line) โค้ดนี้จะอ่านประโยค NMEA ทั้งหมด (ประโยค NMEA จะสิ้นสุดด้วยอักขระบรรทัดใหม่) ตราบใดที่ยังสามารถอ่านข้อมูลจากพอร์ต serial UART ได้ ข้อมูลจะถูกอ่านและส่งไปยัง serial monitor ผ่านฟังก์ชัน `printGPSData` เมื่อไม่มีข้อมูลให้อ่านอีก ฟังก์ชัน `loop` จะหน่วงเวลา 1 วินาที (1,000ms)

1. สร้างและอัปโหลดโค้ดไปยัง Wio Terminal

1. เมื่ออัปโหลดเสร็จแล้ว คุณสามารถตรวจสอบข้อมูล GPS ได้โดยใช้ serial monitor

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

> 💁 คุณสามารถหาโค้ดนี้ได้ในโฟลเดอร์ [code-gps/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps/wio-terminal)

😀 โปรแกรมเซ็นเซอร์ GPS ของคุณสำเร็จแล้ว!

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้องมากที่สุด แต่โปรดทราบว่าการแปลอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความผิดที่เกิดจากการใช้การแปลนี้