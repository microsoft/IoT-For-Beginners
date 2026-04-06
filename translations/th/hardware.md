# ฮาร์ดแวร์

**T** ใน IoT หมายถึง **Things** หรืออุปกรณ์ที่มีปฏิสัมพันธ์กับโลกภายนอก โครงการแต่ละโครงการจะใช้ฮาร์ดแวร์จริงที่นักเรียนและผู้ที่สนใจสามารถเข้าถึงได้ เรามีตัวเลือกฮาร์ดแวร์ IoT สองแบบให้เลือกตามความชอบส่วนตัว ความรู้หรือความถนัดในภาษาโปรแกรม เป้าหมายการเรียนรู้ และความพร้อมใช้งาน นอกจากนี้ เรายังมีตัวเลือก 'ฮาร์ดแวร์เสมือน' สำหรับผู้ที่ไม่มีฮาร์ดแวร์ หรืออยากเรียนรู้เพิ่มเติมก่อนตัดสินใจซื้อ

> 💁 คุณไม่จำเป็นต้องซื้อฮาร์ดแวร์ IoT เพื่อทำแบบฝึกหัด คุณสามารถทำทุกอย่างได้โดยใช้ฮาร์ดแวร์เสมือน

ตัวเลือกฮาร์ดแวร์จริงคือ Arduino หรือ Raspberry Pi แต่ละแพลตฟอร์มมีข้อดีและข้อเสียของตัวเอง ซึ่งจะถูกอธิบายในบทเรียนแรก ๆ หากคุณยังไม่ได้ตัดสินใจเลือกแพลตฟอร์มฮาร์ดแวร์ คุณสามารถดู [บทเรียนที่สองของโครงการแรก](./1-getting-started/lessons/2-deeper-dive/README.md) เพื่อช่วยตัดสินใจว่าคุณสนใจเรียนรู้แพลตฟอร์มใดมากที่สุด

ฮาร์ดแวร์ที่เลือกใช้ถูกคัดสรรมาเพื่อลดความซับซ้อนของบทเรียนและแบบฝึกหัด แม้ว่าฮาร์ดแวร์อื่นอาจใช้งานได้ แต่เราไม่สามารถรับประกันได้ว่าแบบฝึกหัดทั้งหมดจะรองรับอุปกรณ์ของคุณโดยไม่ต้องมีฮาร์ดแวร์เพิ่มเติม ตัวอย่างเช่น อุปกรณ์ Arduino หลายตัวไม่มี WiFi ซึ่งจำเป็นสำหรับการเชื่อมต่อกับคลาวด์ - Wio terminal ถูกเลือกเพราะมี WiFi ในตัว

คุณจะต้องมีอุปกรณ์ที่ไม่ใช่เทคนิคบางอย่าง เช่น ดินหรือกระถางต้นไม้ และผลไม้หรือผัก

## ซื้อชุดอุปกรณ์

![โลโก้ Seeed Studios](../../translated_images/th/seeed-logo.74732b6b482b6e8e.webp)

Seeed Studios ได้จัดเตรียมฮาร์ดแวร์ทั้งหมดไว้ในรูปแบบชุดอุปกรณ์ที่ซื้อได้ง่าย:

### Arduino - Wio Terminal

**[IoT สำหรับผู้เริ่มต้นกับ Seeed และ Microsoft - Wio Terminal Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![ชุดฮาร์ดแวร์ Wio Terminal](../../translated_images/th/wio-hardware-kit.4c70c48b85e4283a.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[IoT สำหรับผู้เริ่มต้นกับ Seeed และ Microsoft - Raspberry Pi 4 Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![ชุดฮาร์ดแวร์ Raspberry Pi Terminal](../../translated_images/th/pi-hardware-kit.26dbadaedb7dd44c.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

โค้ดสำหรับอุปกรณ์ Arduino เขียนด้วยภาษา C++ ในการทำแบบฝึกหัดทั้งหมด คุณจะต้องมีสิ่งต่อไปนี้:

### ฮาร์ดแวร์ Arduino

* [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *ตัวเลือกเพิ่มเติม* - สาย USB-C หรืออะแดปเตอร์ USB-A เป็น USB-C Wio terminal มีพอร์ต USB-C และมาพร้อมสาย USB-C เป็น USB-A หากคอมพิวเตอร์หรือ Mac ของคุณมีพอร์ต USB-C เท่านั้น คุณจะต้องมีสาย USB-C หรืออะแดปเตอร์ USB-A เป็น USB-C

### เซ็นเซอร์และแอคทูเอเตอร์เฉพาะของ Arduino

สิ่งเหล่านี้เป็นอุปกรณ์เฉพาะสำหรับการใช้งาน Wio terminal Arduino และไม่เกี่ยวข้องกับ Raspberry Pi

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [สายจัมเปอร์สำหรับ Breadboard](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* หูฟังหรือลำโพงอื่นที่มีแจ็ค 3.5 มม. หรือลำโพง JST เช่น:
  * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* microSD Card ขนาด 16GB หรือน้อยกว่า พร้อมตัวเชื่อมต่อเพื่อใช้ SD card กับคอมพิวเตอร์ของคุณหากไม่มีในตัว **หมายเหตุ** - Wio Terminal รองรับ SD card สูงสุด 16GB เท่านั้น ไม่รองรับความจุที่สูงกว่า

## Raspberry Pi

โค้ดสำหรับอุปกรณ์ Raspberry Pi เขียนด้วยภาษา Python ในการทำแบบฝึกหัดทั้งหมด คุณจะต้องมีสิ่งต่อไปนี้:

### ฮาร์ดแวร์ Raspberry Pi

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 รุ่นตั้งแต่ Pi 2B ขึ้นไปควรใช้งานได้กับแบบฝึกหัดในบทเรียนเหล่านี้ หากคุณวางแผนที่จะใช้งาน VS Code โดยตรงบน Pi คุณจะต้องใช้ Pi 4 ที่มี RAM 2GB หรือมากกว่า หากคุณจะเข้าถึง Pi จากระยะไกล Pi 2B ขึ้นไปจะใช้งานได้
* microSD Card (คุณสามารถซื้อชุด Raspberry Pi ที่มาพร้อม microSD Card) พร้อมตัวเชื่อมต่อเพื่อใช้ SD card กับคอมพิวเตอร์ของคุณหากไม่มีในตัว
* อุปกรณ์จ่ายไฟ USB (คุณสามารถซื้อชุด Raspberry Pi 4 ที่มาพร้อมอุปกรณ์จ่ายไฟ) หากคุณใช้ Raspberry Pi 4 คุณจะต้องใช้อุปกรณ์จ่ายไฟ USB-C อุปกรณ์รุ่นก่อนหน้าต้องใช้อุปกรณ์จ่ายไฟ micro-USB

### เซ็นเซอร์และแอคทูเอเตอร์เฉพาะของ Raspberry Pi

สิ่งเหล่านี้เป็นอุปกรณ์เฉพาะสำหรับการใช้งาน Raspberry Pi และไม่เกี่ยวข้องกับอุปกรณ์ Arduino

* [Grove Pi base hat](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [โมดูลกล้อง Raspberry Pi](https://www.raspberrypi.org/products/camera-module-v2/)
* ไมโครโฟนและลำโพง:

  ใช้หนึ่งในตัวเลือกต่อไปนี้ (หรือเทียบเท่า):
  * ไมโครโฟน USB และลำโพง USB หรือ ลำโพงที่มีสายแจ็ค 3.5 มม. หรือใช้ HDMI audio output หาก Raspberry Pi ของคุณเชื่อมต่อกับจอภาพหรือทีวีที่มีลำโพง
  * ชุดหูฟัง USB ที่มีไมโครโฟนในตัว
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) พร้อม
    * หูฟังหรือลำโพงอื่นที่มีแจ็ค 3.5 มม. หรือ ลำโพง JST เช่น:
    * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [USB Speakerphone](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [เซ็นเซอร์แสง Grove](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [ปุ่ม Grove](https://www.seeedstudio.com/Grove-Button.html)

## เซ็นเซอร์และแอคทูเอเตอร์

เซ็นเซอร์และแอคทูเอเตอร์ส่วนใหญ่ที่จำเป็นใช้ร่วมกันระหว่างเส้นทางการเรียนรู้ Arduino และ Raspberry Pi:

* [Grove LED](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [เซ็นเซอร์ความชื้นและอุณหภูมิ Grove](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [เซ็นเซอร์ความชื้นในดินแบบ capacitive Grove](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [รีเลย์ Grove](https://www.seeedstudio.com/Grove-Relay.html)
* [GPS Grove (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [เซ็นเซอร์วัดระยะทาง Grove Time of Flight](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## ฮาร์ดแวร์เพิ่มเติม

บทเรียนเกี่ยวกับการรดน้ำอัตโนมัติใช้รีเลย์เป็นหลัก หากต้องการ คุณสามารถเชื่อมต่อรีเลย์นี้กับปั๊มน้ำที่ใช้พลังงาน USB โดยใช้ฮาร์ดแวร์ที่ระบุด้านล่าง

* [ปั๊มน้ำ 6V](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [USB terminal](https://www.adafruit.com/product/3628)
* ท่อซิลิโคน
* สายไฟสีแดงและดำ
* ไขควงหัวแบนขนาดเล็ก

## ฮาร์ดแวร์เสมือน

เส้นทางฮาร์ดแวร์เสมือนจะมีตัวจำลองสำหรับเซ็นเซอร์และแอคทูเอเตอร์ ซึ่งถูกพัฒนาใน Python ขึ้นอยู่กับความพร้อมใช้งานของฮาร์ดแวร์ คุณสามารถใช้งานบนอุปกรณ์พัฒนาปกติ เช่น Mac, PC หรือใช้งานบน Raspberry Pi และจำลองเฉพาะฮาร์ดแวร์ที่คุณไม่มี ตัวอย่างเช่น หากคุณมีกล้อง Raspberry Pi แต่ไม่มีเซ็นเซอร์ Grove คุณจะสามารถรันโค้ดอุปกรณ์เสมือนบน Pi และจำลองเซ็นเซอร์ Grove แต่ใช้กล้องจริง

ฮาร์ดแวร์เสมือนจะใช้ [โครงการ CounterFit](https://github.com/CounterFit-IoT/CounterFit)

ในการทำบทเรียนเหล่านี้ คุณจะต้องมีเว็บแคม ไมโครโฟน และอุปกรณ์เสียง เช่น ลำโพงหรือหูฟัง อุปกรณ์เหล่านี้สามารถเป็นแบบในตัวหรือแบบภายนอก และต้องตั้งค่าให้ใช้งานได้กับระบบปฏิบัติการของคุณและพร้อมใช้งานจากทุกแอปพลิเคชัน

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้อง แต่โปรดทราบว่าการแปลอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความผิดที่เกิดจากการใช้การแปลนี้