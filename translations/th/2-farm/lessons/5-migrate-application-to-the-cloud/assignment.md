<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2025-08-27T21:52:59+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "th"
}
-->
# เพิ่มการควบคุมรีเลย์แบบแมนนวล

## คำแนะนำ

โค้ดแบบ Serverless สามารถถูกเรียกใช้งานได้จากหลายสิ่ง เช่น การร้องขอ HTTP คุณสามารถใช้ HTTP triggers เพื่อเพิ่มการควบคุมรีเลย์แบบแมนนวล ทำให้ผู้ใช้งานสามารถเปิดหรือปิดรีเลย์ผ่านการร้องขอจากเว็บได้

สำหรับงานนี้ คุณต้องเพิ่ม HTTP triggers สองตัวใน Functions App ของคุณเพื่อเปิดและปิดรีเลย์ โดยใช้สิ่งที่คุณได้เรียนรู้จากบทเรียนนี้ในการส่งคำสั่งไปยังอุปกรณ์

คำแนะนำบางประการ:

* คุณสามารถเพิ่ม HTTP trigger ใน Functions App ที่มีอยู่แล้วด้วยคำสั่งต่อไปนี้:

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    แทนที่ `<trigger name>` ด้วยชื่อสำหรับ HTTP trigger ของคุณ ใช้ชื่อเช่น `relay_on` และ `relay_off`

* HTTP triggers สามารถมีการควบคุมการเข้าถึงได้ โดยค่าเริ่มต้นจะต้องมี API key เฉพาะฟังก์ชันที่ส่งมาพร้อม URL เพื่อเรียกใช้งาน สำหรับงานนี้ คุณสามารถลบข้อจำกัดนี้ออกเพื่อให้ทุกคนสามารถเรียกใช้งานฟังก์ชันได้ โดยการอัปเดตการตั้งค่า `authLevel` ในไฟล์ `function.json` สำหรับ HTTP triggers เป็นค่าต่อไปนี้:

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 คุณสามารถอ่านเพิ่มเติมเกี่ยวกับการควบคุมการเข้าถึงใน [เอกสารเกี่ยวกับ Function access keys](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys)

* HTTP triggers รองรับการร้องขอแบบ GET และ POST โดยค่าเริ่มต้น ซึ่งหมายความว่าคุณสามารถเรียกใช้งานผ่านเว็บเบราว์เซอร์ได้ - เว็บเบราว์เซอร์จะทำการร้องขอแบบ GET

    เมื่อคุณเรียกใช้งาน Functions App ในเครื่อง คุณจะเห็น URL ของ trigger:

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    คัดลอก URL และวางลงในเบราว์เซอร์ของคุณแล้วกด `return` หรือ `Ctrl+click` (`Cmd+click` บน macOS) ลิงก์ในหน้าต่าง terminal ใน VS Code เพื่อเปิดในเบราว์เซอร์เริ่มต้นของคุณ การดำเนินการนี้จะเรียกใช้งาน trigger

    > 💁 สังเกตว่า URL มี `/api` อยู่ในนั้น - HTTP triggers จะอยู่ใน subdomain `api` โดยค่าเริ่มต้น

* เมื่อคุณ deploy Functions App URL ของ HTTP trigger จะเป็น:

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    โดยที่ `<functions app name>` คือชื่อของ Functions App ของคุณ และ `<trigger name>` คือชื่อของ trigger ของคุณ

## เกณฑ์การประเมิน

| เกณฑ์ | ดีเยี่ยม | พอใช้ | ต้องปรับปรุง |
| ------ | -------- | ------ | ------------ |
| สร้าง HTTP triggers | สร้าง triggers สองตัวเพื่อเปิดและปิดรีเลย์ พร้อมชื่อที่เหมาะสม | สร้าง trigger หนึ่งตัวพร้อมชื่อที่เหมาะสม | ไม่สามารถสร้าง triggers ได้ |
| ควบคุมรีเลย์จาก HTTP triggers | สามารถเชื่อมต่อ triggers ทั้งสองตัวกับ IoT Hub และควบคุมรีเลย์ได้อย่างเหมาะสม | สามารถเชื่อมต่อ trigger หนึ่งตัวกับ IoT Hub และควบคุมรีเลย์ได้อย่างเหมาะสม | ไม่สามารถเชื่อมต่อ triggers กับ IoT Hub ได้ |

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้อง แต่โปรดทราบว่าการแปลอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความผิดที่เกิดจากการใช้การแปลนี้