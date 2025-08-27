<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-27T20:49:56+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "th"
}
-->
# ถอดรหัสข้อมูล GPS - Wio Terminal

ในส่วนนี้ของบทเรียน คุณจะถอดรหัสข้อความ NMEA ที่อ่านจากเซ็นเซอร์ GPS โดย Wio Terminal และดึงค่าละติจูดและลองจิจูดออกมา

## ถอดรหัสข้อมูล GPS

เมื่อข้อมูล NMEA ดิบถูกอ่านจากพอร์ตอนุกรมแล้ว สามารถถอดรหัสได้โดยใช้ไลบรารี NMEA แบบโอเพ่นซอร์ส

### งาน - ถอดรหัสข้อมูล GPS

เขียนโปรแกรมให้กับอุปกรณ์เพื่อถอดรหัสข้อมูล GPS

1. เปิดโปรเจกต์แอป `gps-sensor` หากยังไม่ได้เปิด

1. เพิ่มการพึ่งพาไลบรารีสำหรับไลบรารี [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) ลงในไฟล์ `platformio.ini` ของโปรเจกต์ ไลบรารีนี้มีโค้ดสำหรับถอดรหัสข้อมูล NMEA

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. ในไฟล์ `main.cpp` ให้เพิ่มคำสั่ง include สำหรับไลบรารี TinyGPSPlus:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. ด้านล่างการประกาศ `Serial3` ให้ประกาศออบเจ็กต์ TinyGPSPlus เพื่อประมวลผลประโยค NMEA:

    ```cpp
    TinyGPSPlus gps;
    ```

1. เปลี่ยนเนื้อหาของฟังก์ชัน `printGPSData` เป็นดังนี้:

    ```cpp
    if (gps.encode(Serial3.read()))
    {
        if (gps.location.isValid())
        {
            Serial.print(gps.location.lat(), 6);
            Serial.print(F(","));
            Serial.print(gps.location.lng(), 6);
            Serial.print(" - from ");
            Serial.print(gps.satellites.value());
            Serial.println(" satellites");
        }
    }
    ```

    โค้ดนี้จะอ่านตัวอักษรถัดไปจากพอร์ตอนุกรม UART ลงในตัวถอดรหัส NMEA `gps` หลังจากอ่านตัวอักษรแต่ละตัว มันจะตรวจสอบว่าตัวถอดรหัสได้อ่านประโยคที่ถูกต้องหรือไม่ จากนั้นตรวจสอบว่ามีการอ่านตำแหน่งที่ถูกต้องหรือไม่ หากตำแหน่งถูกต้อง มันจะส่งข้อมูลไปยังหน้าจออนุกรม พร้อมกับจำนวนดาวเทียมที่มีส่วนร่วมในตำแหน่งนี้

1. สร้างและอัปโหลดโค้ดไปยัง Wio Terminal

1. เมื่ออัปโหลดเสร็จแล้ว คุณสามารถตรวจสอบข้อมูลตำแหน่ง GPS ได้โดยใช้หน้าจออนุกรม

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 คุณสามารถค้นหาโค้ดนี้ได้ในโฟลเดอร์ [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal)

😀 โปรแกรมเซ็นเซอร์ GPS ของคุณพร้อมการถอดรหัสข้อมูลสำเร็จแล้ว!

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้อง แต่โปรดทราบว่าการแปลโดยอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความผิดที่เกิดจากการใช้การแปลนี้