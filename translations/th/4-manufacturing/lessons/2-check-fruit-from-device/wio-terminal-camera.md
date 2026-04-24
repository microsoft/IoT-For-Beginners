# ถ่ายภาพ - Wio Terminal

ในส่วนนี้ของบทเรียน คุณจะเพิ่มกล้องให้กับ Wio Terminal และถ่ายภาพจากกล้องนั้น

## ฮาร์ดแวร์

Wio Terminal ต้องการกล้อง

กล้องที่คุณจะใช้คือ [ArduCam Mini 2MP Plus](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/) ซึ่งเป็นกล้องความละเอียด 2 ล้านพิกเซลที่ใช้เซ็นเซอร์ภาพ OV2640 กล้องนี้สื่อสารผ่าน SPI interface เพื่อถ่ายภาพ และใช้ I2C ในการตั้งค่าเซ็นเซอร์

## เชื่อมต่อกล้อง

ArduCam ไม่มี Grove socket แต่จะเชื่อมต่อกับ SPI และ I2C buses ผ่าน GPIO pins บน Wio Terminal

### งาน - เชื่อมต่อกล้อง

เชื่อมต่อกล้อง

![เซ็นเซอร์ ArduCam](../../../../../translated_images/th/arducam.20e4e4cbb2682965.webp)

1. ขา (pins) ที่ฐานของ ArduCam ต้องเชื่อมต่อกับ GPIO pins บน Wio Terminal เพื่อให้ง่ายต่อการหาขาที่ถูกต้อง ให้ติดสติกเกอร์ GPIO pin ที่มาพร้อมกับ Wio Terminal รอบๆ ขา:

    ![Wio Terminal พร้อมสติกเกอร์ GPIO pin](../../../../../translated_images/th/wio-terminal-pin-sticker.b90b1535937b84bd.webp)

1. ใช้สายจัมเปอร์ (jumper wires) เชื่อมต่อดังนี้:

    | ขา ArduCAM | ขา Wio Terminal | คำอธิบาย                              |
    | ----------- | ---------------- | --------------------------------------- |
    | CS          | 24 (SPI_CS)      | SPI Chip Select                         |
    | MOSI        | 19 (SPI_MOSI)    | SPI Controller Output, Peripheral Input |
    | MISO        | 21 (SPI_MISO)    | SPI Controller Input, Peripheral Output |
    | SCK         | 23 (SPI_SCLK)    | SPI Serial Clock                        |
    | GND         | 6 (GND)          | Ground - 0V                             |
    | VCC         | 4 (5V)           | 5V power supply                         |
    | SDA         | 3 (I2C1_SDA)     | I2C Serial Data                         |
    | SCL         | 5 (I2C1_SCL)     | I2C Serial Clock                        |

    ![Wio Terminal เชื่อมต่อกับ ArduCam ด้วยสายจัมเปอร์](../../../../../translated_images/th/arducam-wio-terminal-connections.a4d5a4049bdb5ab8.webp)

    การเชื่อมต่อ GND และ VCC ให้พลังงาน 5V กับ ArduCam กล้องนี้ทำงานที่ 5V ซึ่งแตกต่างจาก Grove sensors ที่ทำงานที่ 3V พลังงานนี้มาจากการเชื่อมต่อ USB-C ที่จ่ายพลังงานให้กับอุปกรณ์

    > 💁 สำหรับการเชื่อมต่อ SPI ป้ายชื่อขาบน ArduCam และชื่อขา Wio Terminal ที่ใช้ในโค้ดยังคงใช้ชื่อแบบเก่า คำแนะนำในบทเรียนนี้จะใช้ชื่อแบบใหม่ ยกเว้นเมื่อชื่อขาถูกใช้ในโค้ด

1. ตอนนี้คุณสามารถเชื่อมต่อ Wio Terminal กับคอมพิวเตอร์ของคุณได้แล้ว

## เขียนโปรแกรมให้เชื่อมต่อกับกล้อง

ตอนนี้ Wio Terminal สามารถเขียนโปรแกรมเพื่อใช้งานกล้อง ArduCAM ที่เชื่อมต่ออยู่ได้แล้ว

### งาน - เขียนโปรแกรมให้เชื่อมต่อกับกล้อง

1. สร้างโปรเจกต์ใหม่สำหรับ Wio Terminal โดยใช้ PlatformIO ตั้งชื่อโปรเจกต์ว่า `fruit-quality-detector` เพิ่มโค้ดในฟังก์ชัน `setup` เพื่อกำหนดค่าพอร์ต serial

1. เพิ่มโค้ดเพื่อเชื่อมต่อ WiFi โดยใช้ข้อมูล WiFi ของคุณในไฟล์ `config.h` อย่าลืมเพิ่มไลบรารีที่จำเป็นในไฟล์ `platformio.ini`

1. ไลบรารี ArduCam ไม่สามารถติดตั้งเป็น Arduino library จากไฟล์ `platformio.ini` ได้ แต่ต้องติดตั้งจาก source code ในหน้า GitHub ของพวกเขา คุณสามารถทำได้โดย:

    * โคลน repo จาก [https://github.com/ArduCAM/Arduino.git](https://github.com/ArduCAM/Arduino.git)
    * ไปที่ repo บน GitHub ที่ [github.com/ArduCAM/Arduino](https://github.com/ArduCAM/Arduino) และดาวน์โหลดโค้ดเป็น zip จากปุ่ม **Code**

1. คุณต้องใช้เฉพาะโฟลเดอร์ `ArduCAM` จากโค้ดนี้ คัดลอกทั้งโฟลเดอร์ไปยังโฟลเดอร์ `lib` ในโปรเจกต์ของคุณ

    > ⚠️ ต้องคัดลอกทั้งโฟลเดอร์ ดังนั้นโค้ดจะอยู่ใน `lib/ArduCam` อย่าคัดลอกเฉพาะเนื้อหาในโฟลเดอร์ `ArduCam` ไปยังโฟลเดอร์ `lib` ให้คัดลอกทั้งโฟลเดอร์

1. โค้ดไลบรารี ArduCam ทำงานกับกล้องหลายประเภท ประเภทของกล้องที่คุณต้องการใช้จะถูกกำหนดโดย compiler flags ซึ่งช่วยลดขนาดของไลบรารีที่สร้างขึ้นโดยการลบโค้ดสำหรับกล้องที่คุณไม่ได้ใช้ เพื่อกำหนดไลบรารีสำหรับกล้อง OV2640 ให้เพิ่มสิ่งนี้ที่ท้ายไฟล์ `platformio.ini`:

    ```ini
    build_flags =
        -DARDUCAM_SHIELD_V2
        -DOV2640_CAM
    ```

    นี่เป็นการตั้งค่า compiler flags สองตัว:

      * `ARDUCAM_SHIELD_V2` เพื่อบอกไลบรารีว่ากล้องอยู่บนบอร์ด Arduino ที่เรียกว่า shield
      * `OV2640_CAM` เพื่อบอกไลบรารีให้รวมเฉพาะโค้ดสำหรับกล้อง OV2640

1. เพิ่มไฟล์ header ในโฟลเดอร์ `src` ชื่อ `camera.h` ไฟล์นี้จะมีโค้ดสำหรับสื่อสารกับกล้อง เพิ่มโค้ดต่อไปนี้ในไฟล์นี้:

    ```cpp
    #pragma once
    
    #include <ArduCAM.h>
    #include <Wire.h>
    
    class Camera
    {
    public:
        Camera(int format, int image_size) : _arducam(OV2640, PIN_SPI_SS)
        {
            _format = format;
            _image_size = image_size;
        }
    
        bool init()
        {
            // Reset the CPLD
            _arducam.write_reg(0x07, 0x80);
            delay(100);
    
            _arducam.write_reg(0x07, 0x00);
            delay(100);
    
            // Check if the ArduCAM SPI bus is OK
            _arducam.write_reg(ARDUCHIP_TEST1, 0x55);
            if (_arducam.read_reg(ARDUCHIP_TEST1) != 0x55)
            {
                return false;
            }
                
            // Change MCU mode
            _arducam.set_mode(MCU2LCD_MODE);
    
            uint8_t vid, pid;
    
            // Check if the camera module type is OV2640
            _arducam.wrSensorReg8_8(0xff, 0x01);
            _arducam.rdSensorReg8_8(OV2640_CHIPID_HIGH, &vid);
            _arducam.rdSensorReg8_8(OV2640_CHIPID_LOW, &pid);
            if ((vid != 0x26) && ((pid != 0x41) || (pid != 0x42)))
            {
                return false;
            }
            
            _arducam.set_format(_format);
            _arducam.InitCAM();
            _arducam.OV2640_set_JPEG_size(_image_size);
            _arducam.OV2640_set_Light_Mode(Auto);
            _arducam.OV2640_set_Special_effects(Normal);
            delay(1000);
    
            return true;
        }
    
        void startCapture()
        {
            _arducam.flush_fifo();
            _arducam.clear_fifo_flag();
            _arducam.start_capture();
        }
    
        bool captureReady()
        {
            return _arducam.get_bit(ARDUCHIP_TRIG, CAP_DONE_MASK);
        }
    
        bool readImageToBuffer(byte **buffer, uint32_t &buffer_length)
        {
            if (!captureReady()) return false;
    
            // Get the image file length
            uint32_t length = _arducam.read_fifo_length();
            buffer_length = length;
    
            if (length >= MAX_FIFO_SIZE)
            {
                return false;
            }
            if (length == 0)
            {
                return false;
            }
    
            // create the buffer
            byte *buf = new byte[length];
    
            uint8_t temp = 0, temp_last = 0;
            int i = 0;
            uint32_t buffer_pos = 0;
            bool is_header = false;
    
            _arducam.CS_LOW();
            _arducam.set_fifo_burst();
            
            while (length--)
            {
                temp_last = temp;
                temp = SPI.transfer(0x00);
                //Read JPEG data from FIFO
                if ((temp == 0xD9) && (temp_last == 0xFF)) //If find the end ,break while,
                {
                    buf[buffer_pos] = temp;
    
                    buffer_pos++;
                    i++;
                    
                    _arducam.CS_HIGH();
                }
                if (is_header == true)
                {
                    //Write image data to buffer if not full
                    if (i < 256)
                    {
                        buf[buffer_pos] = temp;
                        buffer_pos++;
                        i++;
                    }
                    else
                    {
                        _arducam.CS_HIGH();
    
                        i = 0;
                        buf[buffer_pos] = temp;
    
                        buffer_pos++;
                        i++;
    
                        _arducam.CS_LOW();
                        _arducam.set_fifo_burst();
                    }
                }
                else if ((temp == 0xD8) & (temp_last == 0xFF))
                {
                    is_header = true;
    
                    buf[buffer_pos] = temp_last;
                    buffer_pos++;
                    i++;
    
                    buf[buffer_pos] = temp;
                    buffer_pos++;
                    i++;
                }
            }
            
            _arducam.clear_fifo_flag();
    
            _arducam.set_format(_format);
            _arducam.InitCAM();
            _arducam.OV2640_set_JPEG_size(_image_size);
    
            // return the buffer
            *buffer = buf;
        }
    
    private:
        ArduCAM _arducam;
        int _format;
        int _image_size;
    };
    ```

    นี่เป็นโค้ดระดับต่ำที่กำหนดค่ากล้องโดยใช้ไลบรารี ArduCam และดึงภาพเมื่อจำเป็นโดยใช้ SPI bus โค้ดนี้เฉพาะเจาะจงกับ ArduCam ดังนั้นคุณไม่จำเป็นต้องกังวลเกี่ยวกับวิธีการทำงานในตอนนี้

1. ใน `main.cpp` เพิ่มโค้ดต่อไปนี้ใต้คำสั่ง `include` อื่นๆ เพื่อรวมไฟล์ใหม่นี้และสร้าง instance ของคลาสกล้อง:

    ```cpp
    #include "camera.h"

    Camera camera = Camera(JPEG, OV2640_640x480);
    ```

    นี่เป็นการสร้าง `Camera` ที่บันทึกภาพเป็น JPEGs ที่ความละเอียด 640x480 แม้ว่าจะรองรับความละเอียดที่สูงกว่า (สูงสุด 3280x2464) แต่ image classifier ทำงานกับภาพที่เล็กกว่ามาก (227x227) ดังนั้นจึงไม่มีความจำเป็นที่จะถ่ายภาพและส่งภาพที่ใหญ่กว่า

1. เพิ่มโค้ดต่อไปนี้ด้านล่างเพื่อกำหนดฟังก์ชันสำหรับตั้งค่ากล้อง:

    ```cpp
    void setupCamera()
    {
        pinMode(PIN_SPI_SS, OUTPUT);
        digitalWrite(PIN_SPI_SS, HIGH);
    
        Wire.begin();
        SPI.begin();
    
        if (!camera.init())
        {
            Serial.println("Error setting up the camera!");
        }
    }
    ```

    ฟังก์ชัน `setupCamera` เริ่มต้นด้วยการกำหนดค่าขา SPI chip select (`PIN_SPI_SS`) เป็น high ทำให้ Wio Terminal เป็น SPI controller จากนั้นเริ่มต้น I2C และ SPI buses สุดท้ายจะเริ่มต้นคลาสกล้องซึ่งกำหนดค่าเซ็นเซอร์กล้องและตรวจสอบให้แน่ใจว่าทุกอย่างเชื่อมต่ออย่างถูกต้อง

1. เรียกฟังก์ชันนี้ที่ท้ายฟังก์ชัน `setup`:

    ```cpp
    setupCamera();
    ```

1. สร้างและอัปโหลดโค้ดนี้ และตรวจสอบผลลัพธ์จาก serial monitor หากคุณเห็นข้อความ `Error setting up the camera!` ให้ตรวจสอบการเชื่อมต่อสายเพื่อให้แน่ใจว่าสายทั้งหมดเชื่อมต่อขาที่ถูกต้องบน ArduCam กับ GPIO pins ที่ถูกต้องบน Wio Terminal และสายจัมเปอร์ทั้งหมดเชื่อมต่ออย่างแน่นหนา

## ถ่ายภาพ

ตอนนี้ Wio Terminal สามารถเขียนโปรแกรมเพื่อถ่ายภาพเมื่อกดปุ่มได้แล้ว

### งาน - ถ่ายภาพ

1. Microcontrollers ทำงานโค้ดของคุณอย่างต่อเนื่อง ดังนั้นจึงไม่ง่ายที่จะเรียกใช้งานบางอย่างเช่นการถ่ายภาพโดยไม่ตอบสนองต่อเซ็นเซอร์ Wio Terminal มีปุ่ม ดังนั้นกล้องสามารถตั้งค่าให้ถูกเรียกใช้งานโดยหนึ่งในปุ่มได้ เพิ่มโค้ดต่อไปนี้ที่ท้ายฟังก์ชัน `setup` เพื่อกำหนดค่าปุ่ม C (หนึ่งในสามปุ่มด้านบน ปุ่มที่ใกล้กับสวิตช์เปิดปิดมากที่สุด)

    ![ปุ่ม C ด้านบนใกล้กับสวิตช์เปิดปิด](../../../../../translated_images/th/wio-terminal-c-button.73df3cb1c1445ea0.webp)

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

    โหมด `INPUT_PULLUP` จะกลับค่าของ input ตัวอย่างเช่น ปกติปุ่มจะส่งสัญญาณต่ำเมื่อไม่ได้กด และส่งสัญญาณสูงเมื่อกด เมื่อตั้งค่าเป็น `INPUT_PULLUP` ปุ่มจะส่งสัญญาณสูงเมื่อไม่ได้กด และส่งสัญญาณต่ำเมื่อกด

1. เพิ่มฟังก์ชันว่างเปล่าเพื่อตอบสนองต่อการกดปุ่มก่อนฟังก์ชัน `loop`:

    ```cpp
    void buttonPressed()
    {
        
    }
    ```

1. เรียกฟังก์ชันนี้ในเมธอด `loop` เมื่อปุ่มถูกกด:

    ```cpp
    void loop()
    {
        if (digitalRead(WIO_KEY_C) == LOW)
        {
            buttonPressed();
            delay(2000);
        }
    
        delay(200);
    }
    ```

    โค้ดนี้ตรวจสอบว่าปุ่มถูกกดหรือไม่ หากถูกกด ฟังก์ชัน `buttonPressed` จะถูกเรียก และ loop จะหน่วงเวลา 2 วินาที เพื่อให้มีเวลาปล่อยปุ่มเพื่อไม่ให้การกดปุ่มนานถูกลงทะเบียนสองครั้ง

    > 💁 ปุ่มบน Wio Terminal ถูกตั้งค่าเป็น `INPUT_PULLUP` ดังนั้นจะส่งสัญญาณสูงเมื่อไม่ได้กด และส่งสัญญาณต่ำเมื่อกด

1. เพิ่มโค้ดต่อไปนี้ในฟังก์ชัน `buttonPressed`:

    ```cpp
    camera.startCapture();
 
    while (!camera.captureReady())
        delay(100);

    Serial.println("Image captured");

    byte *buffer;
    uint32_t length;

    if (camera.readImageToBuffer(&buffer, length))
    {
        Serial.print("Image read to buffer with length ");
        Serial.println(length);

        delete(buffer);
    }
    ```

    โค้ดนี้เริ่มต้นการถ่ายภาพโดยเรียก `startCapture` ฮาร์ดแวร์กล้องไม่ได้ทำงานโดยการคืนค่าข้อมูลเมื่อคุณร้องขอ แต่คุณส่งคำสั่งเพื่อเริ่มการถ่ายภาพ และกล้องจะทำงานในพื้นหลังเพื่อถ่ายภาพ แปลงเป็น JPEG และเก็บไว้ใน buffer บนกล้องเอง การเรียก `captureReady` จะตรวจสอบว่าการถ่ายภาพเสร็จสิ้นหรือไม่

    เมื่อการถ่ายภาพเสร็จสิ้น ข้อมูลภาพจะถูกคัดลอกจาก buffer บนกล้องไปยัง buffer ท้องถิ่น (array ของ bytes) ด้วยการเรียก `readImageToBuffer` ความยาวของ buffer จะถูกส่งไปยัง serial monitor

1. สร้างและอัปโหลดโค้ดนี้ และตรวจสอบผลลัพธ์บน serial monitor ทุกครั้งที่คุณกดปุ่ม C ภาพจะถูกถ่ายและคุณจะเห็นขนาดของภาพที่ส่งไปยัง serial monitor

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 9224
    Image captured
    Image read to buffer with length 11272
    ```

    ภาพต่างๆ จะมีขนาดแตกต่างกัน ภาพถูกบีบอัดเป็น JPEG และขนาดของไฟล์ JPEG สำหรับความละเอียดที่กำหนดขึ้นอยู่กับสิ่งที่อยู่ในภาพ

> 💁 คุณสามารถหาโค้ดนี้ได้ในโฟลเดอร์ [code-camera/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/wio-terminal)

😀 คุณได้ถ่ายภาพด้วย Wio Terminal สำเร็จแล้ว

## ตัวเลือก - ตรวจสอบภาพกล้องโดยใช้ SD card

วิธีที่ง่ายที่สุดในการดูภาพที่ถ่ายโดยกล้องคือการเขียนภาพลงใน SD card ใน Wio Terminal และดูภาพบนคอมพิวเตอร์ของคุณ ทำขั้นตอนนี้หากคุณมี microSD card สำรองและช่องเสียบ microSD card ในคอมพิวเตอร์ของคุณ หรืออะแดปเตอร์

Wio Terminal รองรับ microSD card ขนาดสูงสุด 16GB หากคุณมี SD card ที่ใหญ่กว่านี้จะไม่สามารถใช้งานได้

### งาน - ตรวจสอบภาพกล้องโดยใช้ SD card

1. ฟอร์แมต microSD card เป็น FAT32 หรือ exFAT โดยใช้แอปพลิเคชันที่เกี่ยวข้องบนคอมพิวเตอร์ของคุณ (Disk Utility บน macOS, File Explorer บน Windows หรือใช้เครื่องมือ command line ใน Linux)

1. ใส่ microSD card ในช่องเสียบที่อยู่ใต้สวิตช์เปิดปิด ตรวจสอบให้แน่ใจว่าใส่จนสุดจนคลิกและอยู่ในตำแหน่ง คุณอาจต้องใช้เล็บหรือเครื่องมือบางอย่างเพื่อดันเข้าไป

1. เพิ่มคำสั่ง include ต่อไปนี้ที่ด้านบนของไฟล์ `main.cpp`:

    ```cpp
    #include "SD/Seeed_SD.h"
    #include <Seeed_FS.h>
    ```

1. เพิ่มฟังก์ชันต่อไปนี้ก่อนฟังก์ชัน `setup`:

    ```cpp
    void setupSDCard()
    {
        while (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI))
        {
            Serial.println("SD Card Error");
        }
    }
    ```

    ฟังก์ชันนี้กำหนดค่า SD card โดยใช้ SPI bus

1. เรียกฟังก์ชันนี้จากฟังก์ชัน `setup`:

    ```cpp
    setupSDCard();
    ```

1. เพิ่มโค้ดต่อไปนี้เหนือฟังก์ชัน `buttonPressed`:

    ```cpp
    int fileNum = 1;

    void saveToSDCard(byte *buffer, uint32_t length)
    {
        char buff[16];
        sprintf(buff, "%d.jpg", fileNum);
        fileNum++;
    
        File outFile = SD.open(buff, FILE_WRITE );
        outFile.write(buffer, length);
        outFile.close();

        Serial.print("Image written to file ");
        Serial.println(buff);
    }
    ```

    โค้ดนี้กำหนดตัวแปร global สำหรับ file count ซึ่งใช้สำหรับชื่อไฟล์ภาพเพื่อให้สามารถถ่ายภาพหลายภาพได้โดยมีชื่อไฟล์เพิ่มขึ้นเรื่อยๆ เช่น `1.jpg`, `2.jpg` และอื่นๆ

    จากนั้นกำหนดฟังก์ชัน `saveToSDCard` ที่รับ buffer ของข้อมูล byte และความยาวของ buffer ชื่อไฟล์จะถูกสร้างโดยใช้ file count และ file count จะเพิ่มขึ้นพร้อมสำหรับไฟล์ถัดไป ข้อมูล binary จาก buffer จะถูกเขียนลงในไฟล์

1. เรียกฟังก์ชัน `saveToSDCard` จากฟังก์ชัน `buttonPressed` การเรียกควรอยู่ **ก่อน** buffer ถูกลบ:

    ```cpp
    Serial.print("Image read to buffer with length ");
    Serial.println(length);

    saveToSDCard(buffer, length);
    
    delete(buffer);
    ```

1. สร้างและอัปโหลดโค้ดนี้ และตรวจสอบผลลัพธ์บน serial monitor ทุกครั้งที่คุณกดปุ่ม C ภาพจะถูกถ่ายและบันทึกลงใน SD card

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 16392
    Image written to file 1.jpg
    Image captured
    Image read to buffer with length 14344
    Image written to file 2.jpg
    ```

1. ปิดเครื่องและถอด microSD card โดยการดันเข้าเล็กน้อยและปล่อย และมันจะเด้งออกมา คุณอาจต้องใช้เครื่องมือบางอย่างเพื่อทำเช่นนี้ เสียบ microSD card เข้ากับคอมพิวเตอร์ของคุณเพื่อดูภาพ

    ![ภาพของกล้วยที่ถ่ายโดยใช้ ArduCam](../../../../../translated_images/th/banana-arducam.be1b32d4267a8194.webp)
💁 อาจใช้เวลาสักครู่สำหรับกล้องในการปรับสมดุลแสงสีขาว คุณจะสังเกตเห็นสิ่งนี้จากสีของภาพที่ถ่าย ภาพแรกๆ อาจดูสีผิดเพี้ยน คุณสามารถแก้ไขปัญหานี้ได้โดยการเปลี่ยนโค้ดเพื่อถ่ายภาพบางภาพที่ถูกละเว้นในฟังก์ชัน `setup`


---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้องมากที่สุด แต่โปรดทราบว่าการแปลอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความผิดที่เกิดจากการใช้การแปลนี้