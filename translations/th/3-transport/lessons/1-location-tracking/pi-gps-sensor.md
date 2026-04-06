# อ่านข้อมูล GPS - Raspberry Pi

ในส่วนนี้ของบทเรียน คุณจะเพิ่มเซ็นเซอร์ GPS ให้กับ Raspberry Pi และอ่านค่าจากเซ็นเซอร์ดังกล่าว

## ฮาร์ดแวร์

Raspberry Pi ต้องการเซ็นเซอร์ GPS

เซ็นเซอร์ที่คุณจะใช้คือ [Grove GPS Air530 sensor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html) เซ็นเซอร์นี้สามารถเชื่อมต่อกับระบบ GPS หลายระบบเพื่อให้ได้ตำแหน่งที่รวดเร็วและแม่นยำ เซ็นเซอร์นี้ประกอบด้วย 2 ส่วน - อุปกรณ์อิเล็กทรอนิกส์หลักของเซ็นเซอร์ และเสาอากาศภายนอกที่เชื่อมต่อด้วยสายบางๆ เพื่อรับคลื่นวิทยุจากดาวเทียม

นี่คือเซ็นเซอร์แบบ UART ซึ่งส่งข้อมูล GPS ผ่าน UART

## เชื่อมต่อเซ็นเซอร์ GPS

เซ็นเซอร์ Grove GPS สามารถเชื่อมต่อกับ Raspberry Pi ได้

### งาน - เชื่อมต่อเซ็นเซอร์ GPS

เชื่อมต่อเซ็นเซอร์ GPS

![เซ็นเซอร์ Grove GPS](../../../../../translated_images/th/grove-gps-sensor.247943bf69b03f0d.webp)

1. เสียบปลายด้านหนึ่งของสาย Grove เข้ากับช่องเสียบของเซ็นเซอร์ GPS สายจะเสียบได้เพียงด้านเดียวเท่านั้น

1. เมื่อ Raspberry Pi ปิดอยู่ ให้เชื่อมต่อปลายอีกด้านของสาย Grove เข้ากับช่อง UART ที่มีเครื่องหมาย **UART** บน Grove Base Hat ที่ติดตั้งอยู่บน Pi ช่องนี้อยู่ในแถวกลาง ด้านที่ใกล้กับช่องเสียบ SD Card ซึ่งอยู่ตรงข้ามกับพอร์ต USB และช่อง Ethernet

    ![เซ็นเซอร์ Grove GPS ที่เชื่อมต่อกับช่อง UART](../../../../../translated_images/th/pi-gps-sensor.1f99ee2b2f652891.webp)

1. วางเซ็นเซอร์ GPS โดยให้เสาอากาศที่เชื่อมต่อมีทัศนวิสัยต่อท้องฟ้า - โดยเฉพาะใกล้หน้าต่างที่เปิดหรือภายนอก จะง่ายขึ้นในการรับสัญญาณที่ชัดเจนเมื่อไม่มีสิ่งกีดขวางเสาอากาศ

## เขียนโปรแกรมสำหรับเซ็นเซอร์ GPS

ตอนนี้ Raspberry Pi สามารถเขียนโปรแกรมเพื่อใช้งานเซ็นเซอร์ GPS ที่เชื่อมต่อได้แล้ว

### งาน - เขียนโปรแกรมสำหรับเซ็นเซอร์ GPS

เขียนโปรแกรมสำหรับอุปกรณ์

1. เปิด Raspberry Pi และรอให้บูตเสร็จ

1. เซ็นเซอร์ GPS มีไฟ LED 2 ดวง - ไฟ LED สีน้ำเงินที่กระพริบเมื่อมีการส่งข้อมูล และไฟ LED สีเขียวที่กระพริบทุกวินาทีเมื่อรับข้อมูลจากดาวเทียม ตรวจสอบให้แน่ใจว่าไฟ LED สีน้ำเงินกระพริบเมื่อเปิด Raspberry Pi หลังจากไม่กี่นาที ไฟ LED สีเขียวจะเริ่มกระพริบ - หากไม่กระพริบ คุณอาจต้องปรับตำแหน่งเสาอากาศ

1. เปิด VS Code ไม่ว่าจะโดยตรงบน Pi หรือเชื่อมต่อผ่าน Remote SSH extension

    > ⚠️ คุณสามารถดูคำแนะนำในการตั้งค่าและเปิด VS Code ในบทเรียนที่ 1 ได้หากจำเป็น [ที่นี่](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md)

1. สำหรับ Raspberry Pi รุ่นใหม่ที่รองรับ Bluetooth จะมีปัญหาความขัดแย้งระหว่างพอร์ต serial ที่ใช้สำหรับ Bluetooth และพอร์ตที่ใช้โดย Grove UART เพื่อแก้ไขปัญหานี้ ให้ทำตามขั้นตอนดังนี้:

    1. จาก terminal ใน VS Code แก้ไขไฟล์ `/boot/config.txt` โดยใช้ `nano` ซึ่งเป็นโปรแกรมแก้ไขข้อความใน terminal ด้วยคำสั่งต่อไปนี้:

        ```sh
        sudo nano /boot/config.txt
        ```

        > ไฟล์นี้ไม่สามารถแก้ไขได้โดยตรงใน VS Code เนื่องจากต้องใช้สิทธิ์ `sudo` ซึ่งเป็นสิทธิ์ระดับสูง VS Code ไม่ทำงานด้วยสิทธิ์นี้

    1. ใช้ปุ่มลูกศรเพื่อเลื่อนไปยังท้ายไฟล์ จากนั้นคัดลอกโค้ดด้านล่างและวางลงในท้ายไฟล์:

        ```ini
        dtoverlay=pi3-miniuart-bt
        dtoverlay=pi3-disable-bt
        enable_uart=1
        ```

        คุณสามารถวางโค้ดโดยใช้คีย์ลัดปกติของอุปกรณ์ (`Ctrl+v` บน Windows, Linux หรือ Raspberry Pi OS, `Cmd+v` บน macOS)

    1. บันทึกไฟล์นี้และออกจาก nano โดยกด `Ctrl+x` กด `y` เมื่อถูกถามว่าต้องการบันทึกการเปลี่ยนแปลงหรือไม่ จากนั้นกด `enter` เพื่อยืนยันว่าต้องการเขียนทับไฟล์ `/boot/config.txt`

        > หากคุณทำผิดพลาด คุณสามารถออกโดยไม่บันทึก แล้วทำขั้นตอนนี้ใหม่อีกครั้ง

    1. แก้ไขไฟล์ `/boot/cmdline.txt` ใน nano ด้วยคำสั่งต่อไปนี้:

        ```sh
        sudo nano /boot/cmdline.txt
        ```

    1. ไฟล์นี้มีคู่คีย์/ค่าแยกด้วยช่องว่าง ลบคู่คีย์/ค่าที่มีคีย์ `console` ออก ซึ่งอาจมีลักษณะดังนี้:

        ```output
        console=serial0,115200 console=tty1 
        ```

        คุณสามารถเลื่อนไปยังรายการเหล่านี้โดยใช้ปุ่มลูกศร จากนั้นลบโดยใช้ปุ่ม `del` หรือ `backspace` ตามปกติ

        ตัวอย่างเช่น หากไฟล์ต้นฉบับมีลักษณะดังนี้:

        ```output
        console=serial0,115200 console=tty1 root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

        เวอร์ชันใหม่จะเป็น:

        ```output
        root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

    1. ทำตามขั้นตอนด้านบนเพื่อบันทึกไฟล์นี้และออกจาก nano

    1. รีบูต Raspberry Pi จากนั้นเชื่อมต่อใหม่ใน VS Code หลังจาก Pi รีบูตเสร็จ

1. จาก terminal สร้างโฟลเดอร์ใหม่ในไดเรกทอรี home ของผู้ใช้ `pi` ชื่อ `gps-sensor` สร้างไฟล์ในโฟลเดอร์นี้ชื่อ `app.py`

1. เปิดโฟลเดอร์นี้ใน VS Code

1. โมดูล GPS ส่งข้อมูล UART ผ่านพอร์ต serial ติดตั้งแพ็กเกจ Pip `pyserial` เพื่อสื่อสารกับพอร์ต serial จากโค้ด Python ของคุณ:

    ```sh
    pip3 install pyserial
    ```

1. เพิ่มโค้ดต่อไปนี้ลงในไฟล์ `app.py` ของคุณ:

    ```python
    import time
    import serial
    
    serial = serial.Serial('/dev/ttyAMA0', 9600, timeout=1)
    serial.reset_input_buffer()
    serial.flush()
    
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    โค้ดนี้นำเข้าโมดูล `serial` จากแพ็กเกจ Pip `pyserial` จากนั้นเชื่อมต่อกับพอร์ต serial `/dev/ttyAMA0` - ซึ่งเป็นที่อยู่ของพอร์ต serial ที่ Grove Pi Base Hat ใช้สำหรับพอร์ต UART จากนั้นล้างข้อมูลที่มีอยู่ในการเชื่อมต่อ serial นี้

    ต่อมา ฟังก์ชันชื่อ `print_gps_data` ถูกกำหนดขึ้นเพื่อพิมพ์บรรทัดที่ส่งเข้ามาไปยังคอนโซล

    จากนั้นโค้ดจะวนลูปตลอดไป โดยอ่านบรรทัดข้อความจากพอร์ต serial ในแต่ละลูป และเรียกใช้ฟังก์ชัน `print_gps_data` สำหรับแต่ละบรรทัด

    หลังจากอ่านข้อมูลทั้งหมดแล้ว ลูปจะหยุดพักเป็นเวลา 1 วินาที จากนั้นลองอีกครั้ง

1. รันโค้ดนี้ คุณจะเห็นผลลัพธ์ดิบจากเซ็นเซอร์ GPS ซึ่งอาจมีลักษณะดังนี้:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

    > หากคุณได้รับข้อผิดพลาดต่อไปนี้เมื่อหยุดและเริ่มโค้ดใหม่ ให้เพิ่มบล็อก `try - except` ลงในลูป while ของคุณ

      ```output
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0x93 in position 0: invalid start byte
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0xf1 in position 0: invalid continuation byte
      ```

    ```python
    while True:
        try:
            line = serial.readline().decode('utf-8')
              
            while len(line) > 0:
                print_gps_data()
                line = serial.readline().decode('utf-8')
      
        # There's a random chance the first byte being read is part way through a character.
        # Read another full line and continue.

        except UnicodeDecodeError:
            line = serial.readline().decode('utf-8')

    time.sleep(1)
    ```

> 💁 คุณสามารถค้นหาโค้ดนี้ได้ในโฟลเดอร์ [code-gps/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps/pi)

😀 โปรแกรมเซ็นเซอร์ GPS ของคุณสำเร็จแล้ว!

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้อง แต่โปรดทราบว่าการแปลโดยอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาที่เป็นต้นฉบับควรถือว่าเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความผิดที่เกิดจากการใช้การแปลนี้