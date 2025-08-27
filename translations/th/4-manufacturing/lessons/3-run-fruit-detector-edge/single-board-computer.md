<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-27T20:10:55+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "th"
}
-->
# จำแนกภาพด้วยตัวจำแนกภาพบน IoT Edge - ฮาร์ดแวร์ IoT เสมือนและ Raspberry Pi

ในส่วนนี้ของบทเรียน คุณจะใช้ตัวจำแนกภาพที่ทำงานบนอุปกรณ์ IoT Edge

## ใช้ตัวจำแนกภาพบน IoT Edge

อุปกรณ์ IoT สามารถเปลี่ยนเส้นทางไปใช้ตัวจำแนกภาพบน IoT Edge ได้ โดย URL สำหรับตัวจำแนกภาพคือ `http://<IP address or name>/image` โดยแทนที่ `<IP address or name>` ด้วยที่อยู่ IP หรือชื่อโฮสต์ของคอมพิวเตอร์ที่รัน IoT Edge

ไลบรารี Python สำหรับ Custom Vision ใช้งานได้เฉพาะกับโมเดลที่โฮสต์บนคลาวด์เท่านั้น ไม่สามารถใช้งานกับโมเดลที่โฮสต์บน IoT Edge ซึ่งหมายความว่าคุณจะต้องใช้ REST API เพื่อเรียกใช้งานตัวจำแนกภาพ

### งาน - ใช้ตัวจำแนกภาพบน IoT Edge

1. เปิดโปรเจกต์ `fruit-quality-detector` ใน VS Code หากยังไม่ได้เปิด หากคุณใช้อุปกรณ์ IoT เสมือน ให้ตรวจสอบว่าได้เปิดใช้งาน virtual environment แล้ว

1. เปิดไฟล์ `app.py` และลบคำสั่ง import จาก `azure.cognitiveservices.vision.customvision.prediction` และ `msrest.authentication`

1. เพิ่มคำสั่ง import ต่อไปนี้ที่ด้านบนของไฟล์:

    ```python
    import requests
    ```

1. ลบโค้ดทั้งหมดหลังจากที่ภาพถูกบันทึกลงในไฟล์ ตั้งแต่ `image_file.write(image.read())` ไปจนถึงจบไฟล์

1. เพิ่มโค้ดต่อไปนี้ที่ท้ายไฟล์:

    ```python
    prediction_url = '<URL>'
    headers = {
        'Content-Type' : 'application/octet-stream'
    }
    image.seek(0)
    response = requests.post(prediction_url, headers=headers, data=image)
    results = response.json()
    
    for prediction in results['predictions']:
        print(f'{prediction["tagName"]}:\t{prediction["probability"] * 100:.2f}%')
    ```

    แทนที่ `<URL>` ด้วย URL สำหรับตัวจำแนกภาพของคุณ

    โค้ดนี้จะทำการส่งคำขอ REST POST ไปยังตัวจำแนกภาพ โดยส่งภาพเป็น body ของคำขอ ผลลัพธ์จะถูกส่งกลับมาในรูปแบบ JSON และจะถูกถอดรหัสเพื่อแสดงความน่าจะเป็น

1. รันโค้ดของคุณ โดยให้กล้องชี้ไปที่ผลไม้บางชนิด หรือชุดภาพที่เหมาะสม หรือผลไม้ที่มองเห็นได้ผ่านเว็บแคมของคุณ หากใช้อุปกรณ์ IoT เสมือน คุณจะเห็นผลลัพธ์ในคอนโซล:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 คุณสามารถค้นหาโค้ดนี้ได้ในโฟลเดอร์ [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) หรือ [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device)

😀 โปรแกรมตัวจำแนกคุณภาพผลไม้ของคุณประสบความสำเร็จ!

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้องมากที่สุด แต่โปรดทราบว่าการแปลอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความผิดที่เกิดจากการใช้การแปลนี้