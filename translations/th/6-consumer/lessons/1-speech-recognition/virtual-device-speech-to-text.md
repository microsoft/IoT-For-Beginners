<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-27T20:34:34+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "th"
}
-->
# การแปลงเสียงเป็นข้อความ - อุปกรณ์ IoT เสมือนจริง

ในส่วนนี้ของบทเรียน คุณจะเขียนโค้ดเพื่อแปลงเสียงที่จับได้จากไมโครโฟนของคุณเป็นข้อความโดยใช้บริการแปลงเสียง

## การแปลงเสียงเป็นข้อความ

บน Windows, Linux และ macOS คุณสามารถใช้ Speech Services Python SDK เพื่อฟังเสียงจากไมโครโฟนของคุณและแปลงเสียงที่ตรวจพบเป็นข้อความได้ SDK จะฟังเสียงอย่างต่อเนื่อง ตรวจจับระดับเสียง และส่งเสียงไปแปลงเป็นข้อความเมื่อระดับเสียงลดลง เช่น เมื่อสิ้นสุดช่วงของการพูด

### งาน - แปลงเสียงเป็นข้อความ

1. สร้างแอป Python ใหม่บนคอมพิวเตอร์ของคุณในโฟลเดอร์ชื่อ `smart-timer` โดยมีไฟล์เดียวชื่อ `app.py` และสร้างสภาพแวดล้อมเสมือนของ Python

1. ติดตั้งแพ็กเกจ Pip สำหรับ Speech Services ตรวจสอบให้แน่ใจว่าคุณกำลังติดตั้งจากเทอร์มินัลที่เปิดใช้งานสภาพแวดล้อมเสมือนแล้ว

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ หากคุณพบข้อผิดพลาดดังต่อไปนี้:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > คุณจะต้องอัปเดต Pip ทำได้โดยใช้คำสั่งต่อไปนี้ จากนั้นลองติดตั้งแพ็กเกจอีกครั้ง
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. เพิ่มการนำเข้า (imports) ต่อไปนี้ในไฟล์ `app.py`:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    การนำเข้านี้จะใช้คลาสบางตัวสำหรับการรู้จำเสียงพูด

1. เพิ่มโค้ดต่อไปนี้เพื่อประกาศการตั้งค่าบางอย่าง:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    แทนที่ `<key>` ด้วย API key สำหรับบริการแปลงเสียงของคุณ แทนที่ `<location>` ด้วยตำแหน่งที่คุณใช้เมื่อสร้างทรัพยากรบริการแปลงเสียง

    แทนที่ `<language>` ด้วยชื่อท้องถิ่น (locale name) สำหรับภาษาที่คุณจะพูด เช่น `en-GB` สำหรับภาษาอังกฤษ หรือ `zn-HK` สำหรับภาษากวางตุ้ง คุณสามารถค้นหารายชื่อภาษาที่รองรับและชื่อท้องถิ่นได้ใน [เอกสารสนับสนุนภาษาและเสียงบน Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text)

    การตั้งค่านี้จะถูกใช้เพื่อสร้างวัตถุ `SpeechConfig` ที่จะใช้ในการตั้งค่าบริการแปลงเสียง

1. เพิ่มโค้ดต่อไปนี้เพื่อสร้างตัวรู้จำเสียงพูด:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. ตัวรู้จำเสียงพูดจะทำงานบนเธรดพื้นหลัง โดยฟังเสียงและแปลงเสียงที่ตรวจพบเป็นข้อความ คุณสามารถรับข้อความได้โดยใช้ฟังก์ชัน callback ซึ่งเป็นฟังก์ชันที่คุณกำหนดและส่งไปยังตัวรู้จำเสียงพูด ทุกครั้งที่ตรวจพบเสียงพูด ฟังก์ชัน callback จะถูกเรียก ใช้โค้ดต่อไปนี้เพื่อกำหนด callback และส่ง callback นี้ไปยังตัวรู้จำเสียงพูด รวมถึงกำหนดฟังก์ชันเพื่อประมวลผลข้อความและเขียนข้อความลงในคอนโซล:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. ตัวรู้จำเสียงพูดจะเริ่มฟังเสียงก็ต่อเมื่อคุณเริ่มต้นมันโดยเฉพาะ เพิ่มโค้ดต่อไปนี้เพื่อเริ่มการรู้จำเสียงพูด โค้ดนี้จะทำงานในพื้นหลัง ดังนั้นแอปพลิเคชันของคุณจะต้องมีลูปที่ไม่มีที่สิ้นสุดซึ่งมีการพักการทำงานเพื่อให้แอปพลิเคชันทำงานต่อไป

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. รันแอปนี้ พูดผ่านไมโครโฟนของคุณ และเสียงที่แปลงเป็นข้อความจะถูกแสดงผลในคอนโซล

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    ลองพูดประโยคต่าง ๆ รวมถึงประโยคที่มีคำที่ออกเสียงเหมือนกันแต่มีความหมายต่างกัน เช่น หากคุณพูดภาษาอังกฤษ ลองพูดว่า 'I want to buy two bananas and an apple too' และสังเกตว่ามันจะใช้คำว่า to, two และ too ได้ถูกต้องตามบริบทของคำ ไม่ใช่แค่เสียงที่ได้ยิน

> 💁 คุณสามารถค้นหาโค้ดนี้ได้ในโฟลเดอร์ [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device)

😀 โปรแกรมแปลงเสียงเป็นข้อความของคุณสำเร็จแล้ว!

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้อง แต่โปรดทราบว่าการแปลโดยอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราจะไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความผิดที่เกิดจากการใช้การแปลนี้