<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-27T20:11:18+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "th"
}
-->
# ใช้ IoT Edge ในการจำแนกภาพด้วย Image Classifier - Wio Terminal

ในส่วนนี้ของบทเรียน คุณจะใช้ Image Classifier ที่ทำงานบนอุปกรณ์ IoT Edge

## ใช้ IoT Edge classifier

อุปกรณ์ IoT สามารถถูกกำหนดให้ใช้ Image Classifier ของ IoT Edge ได้ โดย URL สำหรับ Image Classifier คือ `http://<IP address or name>/image` โดยแทนที่ `<IP address or name>` ด้วย IP address หรือชื่อโฮสต์ของคอมพิวเตอร์ที่กำลังใช้งาน IoT Edge

### งาน - ใช้ IoT Edge classifier

1. เปิดโปรเจกต์แอป `fruit-quality-detector` หากยังไม่ได้เปิด

1. Image Classifier ทำงานเป็น REST API โดยใช้ HTTP ไม่ใช่ HTTPS ดังนั้นการเรียกใช้งานต้องใช้ WiFi client ที่รองรับเฉพาะการเรียก HTTP เท่านั้น ซึ่งหมายความว่าไม่จำเป็นต้องใช้ใบรับรอง (certificate) ลบ `CERTIFICATE` ออกจากไฟล์ `config.h`

1. URL สำหรับการพยากรณ์ในไฟล์ `config.h` ต้องถูกอัปเดตเป็น URL ใหม่ คุณสามารถลบ `PREDICTION_KEY` ได้เช่นกัน เนื่องจากไม่จำเป็นต้องใช้

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    แทนที่ `<URL>` ด้วย URL สำหรับ classifier ของคุณ

1. ในไฟล์ `main.cpp` เปลี่ยนคำสั่ง include สำหรับ WiFi Client Secure ให้เป็นเวอร์ชัน HTTP มาตรฐาน:

    ```cpp
    #include <WiFiClient.h>
    ```

1. เปลี่ยนการประกาศ `WiFiClient` ให้เป็นเวอร์ชัน HTTP:

    ```cpp
    WiFiClient client;
    ```

1. เลือกบรรทัดที่ตั้งค่าใบรับรองบน WiFi client ลบบรรทัด `client.setCACert(CERTIFICATE);` ออกจากฟังก์ชัน `connectWiFi`

1. ในฟังก์ชัน `classifyImage` ลบบรรทัด `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);` ที่ตั้งค่า prediction key ใน header

1. อัปโหลดและรันโค้ดของคุณ ชี้กล้องไปที่ผลไม้และกดปุ่ม C คุณจะเห็นผลลัพธ์ใน serial monitor:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 คุณสามารถหาโค้ดนี้ได้ในโฟลเดอร์ [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal)

😀 โปรแกรมจำแนกคุณภาพผลไม้ของคุณสำเร็จแล้ว!

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้อง แต่โปรดทราบว่าการแปลอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความผิดที่เกิดจากการใช้การแปลนี้