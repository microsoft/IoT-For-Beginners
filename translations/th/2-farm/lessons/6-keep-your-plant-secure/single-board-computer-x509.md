<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9aea84bcc7520222b0e1c50469d62d6a",
  "translation_date": "2025-08-27T21:56:57+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/single-board-computer-x509.md",
  "language_code": "th"
}
-->
# ใช้ใบรับรอง X.509 ในโค้ดอุปกรณ์ของคุณ - Virtual IoT Hardware และ Raspberry Pi

ในส่วนนี้ของบทเรียน คุณจะเชื่อมต่ออุปกรณ์ IoT เสมือนหรือ Raspberry Pi ของคุณกับ IoT Hub โดยใช้ใบรับรอง X.509

## เชื่อมต่ออุปกรณ์ของคุณกับ IoT Hub

ขั้นตอนถัดไปคือการเชื่อมต่ออุปกรณ์ของคุณกับ IoT Hub โดยใช้ใบรับรอง X.509

### งาน - เชื่อมต่อกับ IoT Hub

1. คัดลอกไฟล์คีย์และใบรับรองไปยังโฟลเดอร์ที่มีโค้ดอุปกรณ์ IoT ของคุณ หากคุณใช้ Raspberry Pi ผ่าน VS Code Remote SSH และสร้างคีย์บน PC หรือ Mac ของคุณ คุณสามารถลากและวางไฟล์ลงใน explorer ใน VS Code เพื่อคัดลอกไฟล์ได้

1. เปิดไฟล์ `app.py`

1. ในการเชื่อมต่อโดยใช้ใบรับรอง X.509 คุณจะต้องใช้ชื่อโฮสต์ของ IoT Hub และใบรับรอง X.509 เริ่มต้นด้วยการสร้างตัวแปรที่มีชื่อโฮสต์โดยเพิ่มโค้ดต่อไปนี้ก่อนการสร้าง device client:

    ```python
    host_name = "<host_name>"
    ```

    แทนที่ `<host_name>` ด้วยชื่อโฮสต์ของ IoT Hub ของคุณ คุณสามารถดูได้จากส่วน `HostName` ใน `connection_string` ซึ่งจะเป็นชื่อของ IoT Hub ของคุณและลงท้ายด้วย `.azure-devices.net`

1. ด้านล่างนี้ ให้ประกาศตัวแปรที่มี device ID:

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. คุณจะต้องมีอินสแตนซ์ของคลาส `X509` ที่มีไฟล์ใบรับรอง X.509 เพิ่ม `X509` ลงในรายการคลาสที่นำเข้าจากโมดูล `azure.iot.device`:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. สร้างอินสแตนซ์ของคลาส `X509` โดยใช้ไฟล์ใบรับรองและคีย์ของคุณโดยเพิ่มโค้ดนี้ด้านล่างการประกาศ `host_name`:

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    โค้ดนี้จะสร้างคลาส `X509` โดยใช้ไฟล์ `soil-moisture-sensor-x509-cert.pem` และ `soil-moisture-sensor-x509-key.pem` ที่สร้างไว้ก่อนหน้านี้

1. แทนที่บรรทัดโค้ดที่สร้าง `device_client` จาก connection string ด้วยโค้ดต่อไปนี้:

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    โค้ดนี้จะเชื่อมต่อโดยใช้ใบรับรอง X.509 แทน connection string

1. ลบบรรทัดที่มีตัวแปร `connection_string`

1. รันโค้ดของคุณ ตรวจสอบข้อความที่ส่งไปยัง IoT Hub และส่งคำขอ direct method เช่นเดิม คุณจะเห็นอุปกรณ์เชื่อมต่อและส่งค่าความชื้นในดิน รวมถึงรับคำขอ direct method

> 💁 คุณสามารถดูโค้ดนี้ได้ในโฟลเดอร์ [code/pi](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/pi) หรือ [code/virtual-device](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/virtual-device)

😀 โปรแกรมเซ็นเซอร์ความชื้นในดินของคุณเชื่อมต่อกับ IoT Hub โดยใช้ใบรับรอง X.509 แล้ว!

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้องมากที่สุด แต่โปรดทราบว่าการแปลอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความผิดที่เกิดจากการใช้การแปลนี้