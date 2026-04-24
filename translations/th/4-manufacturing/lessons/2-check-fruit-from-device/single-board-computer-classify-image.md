# จำแนกภาพ - ฮาร์ดแวร์ IoT เสมือนและ Raspberry Pi

ในส่วนนี้ของบทเรียน คุณจะส่งภาพที่ถ่ายโดยกล้องไปยังบริการ Custom Vision เพื่อจำแนกภาพ

## ส่งภาพไปยัง Custom Vision

บริการ Custom Vision มี Python SDK ที่คุณสามารถใช้เพื่อจำแนกภาพได้

### งาน - ส่งภาพไปยัง Custom Vision

1. เปิดโฟลเดอร์ `fruit-quality-detector` ใน VS Code หากคุณใช้ฮาร์ดแวร์ IoT เสมือน ตรวจสอบให้แน่ใจว่าสภาพแวดล้อมเสมือนกำลังทำงานอยู่ในเทอร์มินัล

1. Python SDK สำหรับส่งภาพไปยัง Custom Vision มีให้ใช้งานในรูปแบบแพ็กเกจ Pip ติดตั้งด้วยคำสั่งต่อไปนี้:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. เพิ่มคำสั่งนำเข้าต่อไปนี้ที่ด้านบนของไฟล์ `app.py`:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    คำสั่งนี้นำเข้าบางโมดูลจากไลบรารี Custom Vision หนึ่งโมดูลสำหรับการตรวจสอบสิทธิ์ด้วย prediction key และอีกโมดูลสำหรับการสร้าง prediction client class ที่สามารถเรียก Custom Vision ได้

1. เพิ่มโค้ดต่อไปนี้ที่ท้ายไฟล์:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    แทนที่ `<prediction_url>` ด้วย URL ที่คุณคัดลอกมาจากหน้าต่าง *Prediction URL* ก่อนหน้านี้ในบทเรียนนี้ และแทนที่ `<prediction key>` ด้วย prediction key ที่คุณคัดลอกมาจากหน้าต่างเดียวกัน

1. URL การทำนายที่ได้จากหน้าต่าง *Prediction URL* ถูกออกแบบมาให้ใช้เมื่อเรียก REST endpoint โดยตรง Python SDK ใช้ส่วนต่าง ๆ ของ URL ในตำแหน่งที่แตกต่างกัน เพิ่มโค้ดต่อไปนี้เพื่อแยก URL ออกเป็นส่วนที่จำเป็น:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    โค้ดนี้จะแยก URL โดยดึง endpoint `https://<location>.api.cognitive.microsoft.com` ออกมา รวมถึง project ID และชื่อของ iteration ที่เผยแพร่

1. สร้าง predictor object เพื่อทำการทำนายด้วยโค้ดต่อไปนี้:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    `prediction_credentials` จะครอบคลุม prediction key ซึ่งจะถูกใช้เพื่อสร้าง prediction client object ที่ชี้ไปยัง endpoint

1. ส่งภาพไปยัง Custom Vision ด้วยโค้ดต่อไปนี้:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    โค้ดนี้จะย้อนภาพกลับไปที่จุดเริ่มต้น จากนั้นส่งไปยัง prediction client

1. สุดท้าย แสดงผลลัพธ์ด้วยโค้ดต่อไปนี้:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    โค้ดนี้จะวนลูปผ่านการทำนายทั้งหมดที่ถูกส่งกลับมาและแสดงผลในเทอร์มินัล ความน่าจะเป็นที่ส่งกลับมาจะเป็นตัวเลขทศนิยมระหว่าง 0-1 โดย 0 หมายถึงโอกาส 0% ที่จะตรงกับแท็ก และ 1 หมายถึงโอกาส 100% ที่จะตรงกับแท็ก

    > 💁 ตัวจำแนกภาพจะส่งกลับเปอร์เซ็นต์สำหรับแท็กทั้งหมดที่ถูกใช้ แต่ละแท็กจะมีความน่าจะเป็นที่ภาพจะตรงกับแท็กนั้น

1. รันโค้ดของคุณ โดยให้กล้องชี้ไปที่ผลไม้บางชนิด หรือชุดภาพที่เหมาะสม หรือผลไม้ที่มองเห็นได้ผ่านเว็บแคมของคุณหากใช้ฮาร์ดแวร์ IoT เสมือน คุณจะเห็นผลลัพธ์ในคอนโซล:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    คุณจะสามารถเห็นภาพที่ถูกถ่าย และค่าต่าง ๆ เหล่านี้ในแท็บ **Predictions** ใน Custom Vision

    ![กล้วยใน Custom Vision ถูกทำนายว่าเป็นกล้วยสุกที่ 56.8% และกล้วยดิบที่ 43.1%](../../../../../translated_images/th/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 คุณสามารถค้นหาโค้ดนี้ได้ในโฟลเดอร์ [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) หรือ [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device)

😀 โปรแกรมจำแนกคุณภาพผลไม้ของคุณประสบความสำเร็จ!

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามอย่างเต็มที่เพื่อความถูกต้อง แต่โปรดทราบว่าการแปลอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่แม่นยำ เอกสารต้นฉบับในภาษาต้นทางควรถูกพิจารณาเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ แนะนำให้ใช้บริการแปลภาษามนุษย์ที่เป็นมืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความที่ผิดพลาดซึ่งเกิดจากการใช้การแปลนี้