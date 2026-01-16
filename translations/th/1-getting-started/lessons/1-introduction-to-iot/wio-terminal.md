<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a4f0c166010e31fd7b6ca20bc88dec6d",
  "translation_date": "2025-08-27T21:24:14+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md",
  "language_code": "th"
}
-->
# Wio Terminal

[Wio Terminal จาก Seeed Studios](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) เป็นไมโครคอนโทรลเลอร์ที่รองรับ Arduino พร้อม WiFi และเซ็นเซอร์และแอคชูเอเตอร์ในตัว รวมถึงพอร์ตสำหรับเพิ่มเซ็นเซอร์และแอคชูเอเตอร์เพิ่มเติม โดยใช้ระบบฮาร์ดแวร์ที่เรียกว่า [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html)

![Seeed studios Wio Terminal](../../../../../translated_images/th/wio-terminal.b8299ee16587db9a.png)

## การตั้งค่า

ในการใช้งาน Wio Terminal คุณจำเป็นต้องติดตั้งซอฟต์แวร์ฟรีบางตัวบนคอมพิวเตอร์ของคุณ นอกจากนี้ คุณจะต้องอัปเดตเฟิร์มแวร์ของ Wio Terminal ก่อนที่จะเชื่อมต่อกับ WiFi

### งาน - การตั้งค่า

ติดตั้งซอฟต์แวร์ที่จำเป็นและอัปเดตเฟิร์มแวร์

1. ติดตั้ง Visual Studio Code (VS Code) ซึ่งเป็นโปรแกรมแก้ไขที่คุณจะใช้เขียนโค้ดสำหรับอุปกรณ์ในภาษา C/C++ ดูคำแนะนำการติดตั้ง VS Code ได้ที่ [เอกสารประกอบของ VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn)

    > 💁 IDE ยอดนิยมอีกตัวสำหรับการพัฒนา Arduino คือ [Arduino IDE](https://www.arduino.cc/en/software) หากคุณคุ้นเคยกับเครื่องมือนี้อยู่แล้ว คุณสามารถใช้แทน VS Code และ PlatformIO ได้ แต่บทเรียนนี้จะให้คำแนะนำโดยอ้างอิงจากการใช้ VS Code

1. ติดตั้งส่วนขยาย PlatformIO สำหรับ VS Code ซึ่งเป็นส่วนขยายที่รองรับการเขียนโปรแกรมไมโครคอนโทรลเลอร์ในภาษา C/C++ ดูคำแนะนำการติดตั้งส่วนขยายนี้ได้ที่ [เอกสารประกอบของ PlatformIO](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=platformio.platformio-ide) ส่วนขยายนี้ต้องการส่วนขยาย Microsoft C/C++ เพื่อทำงานกับโค้ดภาษา C และ C++ ซึ่งจะถูกติดตั้งโดยอัตโนมัติเมื่อคุณติดตั้ง PlatformIO

1. เชื่อมต่อ Wio Terminal กับคอมพิวเตอร์ของคุณ Wio Terminal มีพอร์ต USB-C ที่ด้านล่าง ซึ่งต้องเชื่อมต่อกับพอร์ต USB บนคอมพิวเตอร์ของคุณ Wio Terminal มาพร้อมสาย USB-C ถึง USB-A แต่หากคอมพิวเตอร์ของคุณมีพอร์ต USB-C เท่านั้น คุณจะต้องใช้สาย USB-C หรืออะแดปเตอร์ USB-A ถึง USB-C

1. ทำตามคำแนะนำใน [เอกสารประกอบ Wio Terminal Wiki WiFi Overview](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/) เพื่อตั้งค่า Wio Terminal และอัปเดตเฟิร์มแวร์

## Hello World

เมื่อเริ่มต้นใช้งานภาษาโปรแกรมหรือเทคโนโลยีใหม่ มักจะมีการสร้างแอปพลิเคชัน 'Hello World' ซึ่งเป็นแอปพลิเคชันขนาดเล็กที่แสดงข้อความ เช่น `"Hello World"` เพื่อยืนยันว่าเครื่องมือทั้งหมดถูกตั้งค่าอย่างถูกต้อง

แอป Hello World สำหรับ Wio Terminal จะช่วยให้คุณมั่นใจว่า Visual Studio Code ถูกติดตั้งอย่างถูกต้องพร้อมกับ PlatformIO และตั้งค่าสำหรับการพัฒนาไมโครคอนโทรลเลอร์

### สร้างโปรเจกต์ PlatformIO

ขั้นตอนแรกคือการสร้างโปรเจกต์ใหม่โดยใช้ PlatformIO ที่ตั้งค่าสำหรับ Wio Terminal

#### งาน - สร้างโปรเจกต์ PlatformIO

สร้างโปรเจกต์ PlatformIO

1. เชื่อมต่อ Wio Terminal กับคอมพิวเตอร์ของคุณ

1. เปิด VS Code

1. ไอคอน PlatformIO จะอยู่ในแถบเมนูด้านข้าง:

    ![ตัวเลือกเมนู PlatformIO](../../../../../translated_images/th/vscode-platformio-menu.297be26b9733e5c4.png)

    เลือกเมนูนี้ จากนั้นเลือก *PIO Home -> Open*

    ![ตัวเลือกเปิด PlatformIO](../../../../../translated_images/th/vscode-platformio-home-open.3f9a41bfd3f4da1c.png)

1. จากหน้าจอต้อนรับ เลือกปุ่ม **+ New Project**

    ![ปุ่มสร้างโปรเจกต์ใหม่](../../../../../translated_images/th/vscode-platformio-welcome-new-button.ba6fc8a4c7b78cc8.png)

1. ตั้งค่าโปรเจกต์ใน *Project Wizard*:

    1. ตั้งชื่อโปรเจกต์ของคุณว่า `nightlight`

    1. จากเมนูแบบเลื่อนลง *Board* ให้พิมพ์ `WIO` เพื่อกรองบอร์ด และเลือก *Seeeduino Wio Terminal*

    1. คงค่า *Framework* เป็น *Arduino*

    1. เลือกว่าจะใช้ตำแหน่งที่ตั้งค่าเริ่มต้นหรือไม่ หากไม่ ให้ยกเลิกการเลือกและกำหนดตำแหน่งสำหรับโปรเจกต์ของคุณ

    1. เลือกปุ่ม **Finish**

    ![Project Wizard ที่เสร็จสมบูรณ์](../../../../../translated_images/th/vscode-platformio-nightlight-project-wizard.5c64db4da6037420.png)

    PlatformIO จะดาวน์โหลดส่วนประกอบที่จำเป็นสำหรับการคอมไพล์โค้ดสำหรับ Wio Terminal และสร้างโปรเจกต์ของคุณ ซึ่งอาจใช้เวลาสักครู่

### สำรวจโปรเจกต์ PlatformIO

ตัวสำรวจใน VS Code จะแสดงไฟล์และโฟลเดอร์ที่ถูกสร้างโดย PlatformIO wizard

#### โฟลเดอร์

* `.pio` - โฟลเดอร์นี้มีข้อมูลชั่วคราวที่จำเป็นสำหรับ PlatformIO เช่น ไลบรารีหรือโค้ดที่คอมไพล์แล้ว หากถูกลบจะถูกสร้างใหม่โดยอัตโนมัติ และคุณไม่จำเป็นต้องเพิ่มโฟลเดอร์นี้ในระบบควบคุมซอร์สโค้ดหากคุณแชร์โปรเจกต์บนเว็บไซต์ เช่น GitHub
* `.vscode` - โฟลเดอร์นี้มีการตั้งค่าที่ใช้โดย PlatformIO และ VS Code หากถูกลบจะถูกสร้างใหม่โดยอัตโนมัติ และคุณไม่จำเป็นต้องเพิ่มโฟลเดอร์นี้ในระบบควบคุมซอร์สโค้ดหากคุณแชร์โปรเจกต์บนเว็บไซต์ เช่น GitHub
* `include` - โฟลเดอร์นี้ใช้สำหรับไฟล์เฮดเดอร์ภายนอกที่จำเป็นเมื่อเพิ่มไลบรารีเพิ่มเติมในโค้ดของคุณ คุณจะไม่ใช้โฟลเดอร์นี้ในบทเรียนนี้
* `lib` - โฟลเดอร์นี้ใช้สำหรับไลบรารีภายนอกที่คุณต้องการเรียกใช้จากโค้ดของคุณ คุณจะไม่ใช้โฟลเดอร์นี้ในบทเรียนนี้
* `src` - โฟลเดอร์นี้มีซอร์สโค้ดหลักสำหรับแอปพลิเคชันของคุณ ในตอนแรกจะมีไฟล์เดียวคือ `main.cpp`
* `test` - โฟลเดอร์นี้ใช้สำหรับการทดสอบหน่วยของโค้ดของคุณ

#### ไฟล์

* `main.cpp` - ไฟล์นี้ในโฟลเดอร์ `src` มีจุดเริ่มต้นสำหรับแอปพลิเคชันของคุณ เปิดไฟล์นี้ และจะมีโค้ดดังนี้:

    ```cpp
    #include <Arduino.h>
    
    void setup() {
      // put your setup code here, to run once:
    }
    
    void loop() {
      // put your main code here, to run repeatedly:
    }
    ```

    เมื่ออุปกรณ์เริ่มทำงาน เฟรมเวิร์ก Arduino จะเรียกใช้ฟังก์ชัน `setup` หนึ่งครั้ง จากนั้นเรียกใช้ฟังก์ชัน `loop` ซ้ำๆ จนกว่าอุปกรณ์จะปิด

* `.gitignore` - ไฟล์นี้ระบุไฟล์และไดเรกทอรีที่ควรละเว้นเมื่อเพิ่มโค้ดในระบบควบคุมซอร์สโค้ด เช่น การอัปโหลดไปยังรีโพสิทอรีบน GitHub

* `platformio.ini` - ไฟล์นี้มีการตั้งค่าสำหรับอุปกรณ์และแอปของคุณ เปิดไฟล์นี้ และจะมีโค้ดดังนี้:

    ```ini
    [env:seeed_wio_terminal]
    platform = atmelsam
    board = seeed_wio_terminal
    framework = arduino
    ```

    ส่วน `[env:seeed_wio_terminal]` มีการตั้งค่าสำหรับ Wio Terminal คุณสามารถมีหลายส่วน `env` เพื่อให้โค้ดของคุณสามารถคอมไพล์สำหรับบอร์ดหลายตัว

    ค่าที่เหลือตรงกับการตั้งค่าจาก Project Wizard:

  * `platform = atmelsam` กำหนดฮาร์ดแวร์ที่ Wio Terminal ใช้ (ไมโครคอนโทรลเลอร์ ATSAMD51)
  * `board = seeed_wio_terminal` กำหนดประเภทของบอร์ดไมโครคอนโทรลเลอร์ (Wio Terminal)
  * `framework = arduino` กำหนดว่าโปรเจกต์นี้ใช้เฟรมเวิร์ก Arduino

### เขียนแอป Hello World

ตอนนี้คุณพร้อมที่จะเขียนแอป Hello World แล้ว

#### งาน - เขียนแอป Hello World

เขียนแอป Hello World

1. เปิดไฟล์ `main.cpp` ใน VS Code

1. เปลี่ยนโค้ดให้ตรงกับดังนี้:

    ```cpp
    #include <Arduino.h>

    void setup()
    {
        Serial.begin(9600);

        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    
    void loop()
    {
        Serial.println("Hello World");
        delay(5000);
    }
    ```

    ฟังก์ชัน `setup` จะเริ่มต้นการเชื่อมต่อกับพอร์ตอนุกรม - ในกรณีนี้คือพอร์ต USB ที่ใช้เชื่อมต่อ Wio Terminal กับคอมพิวเตอร์ของคุณ พารามิเตอร์ `9600` คือ [baud rate](https://wikipedia.org/wiki/Symbol_rate) หรือความเร็วที่ข้อมูลจะถูกส่งผ่านพอร์ตอนุกรมในหน่วยบิตต่อวินาที การตั้งค่านี้หมายถึง 9,600 บิต (0 และ 1) ของข้อมูลจะถูกส่งในแต่ละวินาที จากนั้นรอให้พอร์ตอนุกรมพร้อมใช้งาน

    ฟังก์ชัน `loop` จะส่งข้อความ `Hello World!` ไปยังพอร์ตอนุกรม พร้อมกับตัวอักขระขึ้นบรรทัดใหม่ จากนั้นจะหยุดทำงานเป็นเวลา 5,000 มิลลิวินาทีหรือ 5 วินาที หลังจากฟังก์ชัน `loop` สิ้นสุด จะถูกเรียกใช้อีกครั้ง และอีกครั้ง และต่อเนื่องไปเรื่อยๆ ตลอดเวลาที่ไมโครคอนโทรลเลอร์เปิดอยู่

1. ตั้งค่า Wio Terminal ให้อยู่ในโหมดอัปโหลด คุณจะต้องทำเช่นนี้ทุกครั้งที่อัปโหลดโค้ดใหม่ไปยังอุปกรณ์:

    1. ดึงสวิตช์เปิด/ปิดลงสองครั้งอย่างรวดเร็ว - สวิตช์จะกลับไปที่ตำแหน่งเปิดทุกครั้ง

    1. ตรวจสอบไฟสถานะสีน้ำเงินทางด้านขวาของพอร์ต USB ควรมีการกระพริบ

    [![วิดีโอแสดงวิธีตั้งค่า Wio Terminal ให้อยู่ในโหมดอัปโหลด](https://img.youtube.com/vi/LeKU_7zLRrQ/0.jpg)](https://youtu.be/LeKU_7zLRrQ)

    คลิกที่ภาพด้านบนเพื่อดูวิดีโอแสดงวิธีการทำ

1. สร้างและอัปโหลดโค้ดไปยัง Wio Terminal

    1. เปิด VS Code command palette

    1. พิมพ์ `PlatformIO Upload` เพื่อค้นหาตัวเลือกอัปโหลด และเลือก *PlatformIO: Upload*

        ![ตัวเลือกอัปโหลด PlatformIO ใน command palette](../../../../../translated_images/th/vscode-platformio-upload-command-palette.9e0f49cf80d1f1c3.png)

        PlatformIO จะสร้างโค้ดโดยอัตโนมัติหากจำเป็นก่อนอัปโหลด

    1. โค้ดจะถูกคอมไพล์และอัปโหลดไปยัง Wio Terminal

        > 💁 หากคุณใช้ macOS จะมีการแจ้งเตือนเกี่ยวกับ *DISK NOT EJECTED PROPERLY* ปรากฏขึ้น เนื่องจาก Wio Terminal ถูกเมานต์เป็นไดรฟ์ในกระบวนการแฟลช และถูกตัดการเชื่อมต่อเมื่อโค้ดที่คอมไพล์แล้วถูกเขียนไปยังอุปกรณ์ คุณสามารถละเว้นการแจ้งเตือนนี้ได้

    ⚠️ หากคุณพบข้อผิดพลาดเกี่ยวกับพอร์ตอัปโหลดที่ไม่พร้อมใช้งาน ให้ตรวจสอบว่า Wio Terminal เชื่อมต่อกับคอมพิวเตอร์ของคุณและเปิดอยู่โดยใช้สวิตช์ทางด้านซ้ายของหน้าจอ และตั้งค่าให้อยู่ในโหมดอัปโหลด ไฟสีเขียวด้านล่างควรเปิดอยู่ และไฟสีน้ำเงินควรกระพริบ หากยังพบข้อผิดพลาด ให้ดึงสวิตช์เปิด/ปิดลงสองครั้งอย่างรวดเร็วอีกครั้งเพื่อบังคับให้ Wio Terminal อยู่ในโหมดอัปโหลด และลองอัปโหลดอีกครั้ง

PlatformIO มี Serial Monitor ที่สามารถตรวจสอบข้อมูลที่ส่งผ่านสาย USB จาก Wio Terminal ซึ่งช่วยให้คุณตรวจสอบข้อมูลที่ส่งโดยคำสั่ง `Serial.println("Hello World");`

1. เปิด VS Code command palette

1. พิมพ์ `PlatformIO Serial` เพื่อค้นหาตัวเลือก Serial Monitor และเลือก *PlatformIO: Serial Monitor*

    ![ตัวเลือก Serial Monitor ของ PlatformIO ใน command palette](../../../../../translated_images/th/vscode-platformio-serial-monitor-command-palette.b348ec841b8a1c14.png)

    เทอร์มินัลใหม่จะเปิดขึ้น และข้อมูลที่ส่งผ่านพอร์ตอนุกรมจะถูกสตรีมเข้าสู่เทอร์มินัลนี้:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Hello World
    Hello World
    ```

    `Hello World` จะพิมพ์ลงใน Serial Monitor ทุกๆ 5 วินาที

> 💁 คุณสามารถค้นหาโค้ดนี้ได้ในโฟลเดอร์ [code/wio-terminal](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/wio-terminal)

😀 โปรแกรม 'Hello World' ของคุณสำเร็จแล้ว!

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้อง แต่โปรดทราบว่าการแปลอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความผิดที่เกิดจากการใช้การแปลนี้