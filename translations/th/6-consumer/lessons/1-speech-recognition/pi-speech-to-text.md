<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-27T20:36:40+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "th"
}
-->
# การแปลงเสียงเป็นข้อความ - Raspberry Pi

ในส่วนนี้ของบทเรียน คุณจะเขียนโค้ดเพื่อแปลงเสียงในไฟล์เสียงที่บันทึกไว้เป็นข้อความโดยใช้บริการแปลงเสียง

## ส่งไฟล์เสียงไปยังบริการแปลงเสียง

ไฟล์เสียงสามารถส่งไปยังบริการแปลงเสียงได้โดยใช้ REST API ในการใช้บริการแปลงเสียง คุณต้องขอ access token ก่อน จากนั้นใช้ token นั้นเพื่อเข้าถึง REST API โดย access token จะหมดอายุภายใน 10 นาที ดังนั้นโค้ดของคุณควรขอ token เป็นประจำเพื่อให้แน่ใจว่า token จะอัปเดตอยู่เสมอ

### งาน - ขอ access token

1. เปิดโปรเจกต์ `smart-timer` บน Raspberry Pi ของคุณ

1. ลบฟังก์ชัน `play_audio` ออก เนื่องจากไม่จำเป็นอีกต่อไป เพราะคุณไม่ต้องการให้ smart timer พูดซ้ำสิ่งที่คุณพูด

1. เพิ่มการ import ต่อไปนี้ที่ด้านบนของไฟล์ `app.py`:

    ```python
    import requests
    ```

1. เพิ่มโค้ดต่อไปนี้เหนือ loop `while True` เพื่อกำหนดค่าการตั้งค่าสำหรับบริการแปลงเสียง:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    แทนที่ `<key>` ด้วย API key สำหรับทรัพยากรบริการแปลงเสียงของคุณ แทนที่ `<location>` ด้วยตำแหน่งที่คุณใช้เมื่อสร้างทรัพยากรบริการแปลงเสียง

    แทนที่ `<language>` ด้วยชื่อ locale สำหรับภาษาที่คุณจะพูด เช่น `en-GB` สำหรับภาษาอังกฤษ หรือ `zn-HK` สำหรับภาษากวางตุ้ง คุณสามารถค้นหารายชื่อภาษาที่รองรับและชื่อ locale ได้ใน [เอกสารสนับสนุนภาษาและเสียงบน Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text)

1. ด้านล่างนี้ เพิ่มฟังก์ชันต่อไปนี้เพื่อขอ access token:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    ฟังก์ชันนี้เรียก endpoint สำหรับออก token โดยส่ง API key เป็น header การเรียกนี้จะส่งคืน access token ที่สามารถใช้เรียกบริการแปลงเสียงได้

1. ด้านล่างนี้ กำหนดฟังก์ชันเพื่อแปลงเสียงในไฟล์เสียงที่บันทึกไว้เป็นข้อความโดยใช้ REST API:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. ภายในฟังก์ชันนี้ ตั้งค่า URL และ headers สำหรับ REST API:

    ```python
    url = f'https://{location}.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1'

    headers = {
        'Authorization': 'Bearer ' + get_access_token(),
        'Content-Type': f'audio/wav; codecs=audio/pcm; samplerate={rate}',
        'Accept': 'application/json;text/xml'
    }

    params = {
        'language': language
    }
    ```

    โค้ดนี้สร้าง URL โดยใช้ตำแหน่งของทรัพยากรบริการแปลงเสียง จากนั้นเติม headers ด้วย access token จากฟังก์ชัน `get_access_token` รวมถึง sample rate ที่ใช้ในการบันทึกเสียง สุดท้ายกำหนดพารามิเตอร์บางอย่างที่จะส่งไปพร้อมกับ URL ซึ่งระบุภาษาที่อยู่ในไฟล์เสียง

1. ด้านล่างนี้ เพิ่มโค้ดต่อไปนี้เพื่อเรียก REST API และรับข้อความกลับมา:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    โค้ดนี้เรียก URL และถอดรหัสค่า JSON ที่มาจากการตอบกลับ ค่า `RecognitionStatus` ในการตอบกลับระบุว่าการเรียกสามารถแปลงเสียงเป็นข้อความได้สำเร็จหรือไม่ และหากค่าเป็น `Success` ข้อความจะถูกส่งคืนจากฟังก์ชัน มิฉะนั้นจะส่งคืนสตริงว่าง

1. เหนือ loop `while True:` กำหนดฟังก์ชันเพื่อประมวลผลข้อความที่ส่งคืนจากบริการแปลงเสียงเป็นข้อความ ฟังก์ชันนี้จะพิมพ์ข้อความลงในคอนโซลในตอนนี้

    ```python
    def process_text(text):
        print(text)
    ```

1. สุดท้าย แทนที่การเรียก `play_audio` ใน loop `while True` ด้วยการเรียกฟังก์ชัน `convert_speech_to_text` โดยส่งข้อความไปยังฟังก์ชัน `process_text`:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. รันโค้ด กดปุ่มและพูดใส่ไมโครโฟน ปล่อยปุ่มเมื่อคุณพูดเสร็จ และไฟล์เสียงจะถูกแปลงเป็นข้อความและพิมพ์ลงในคอนโซล

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    ลองพูดประโยคต่าง ๆ รวมถึงประโยคที่มีคำที่ออกเสียงเหมือนกันแต่มีความหมายต่างกัน ตัวอย่างเช่น หากคุณพูดภาษาอังกฤษ ให้พูดว่า 'I want to buy two bananas and an apple too' และสังเกตว่ามันจะใช้คำว่า to, two และ too ได้ถูกต้องตามบริบทของคำ ไม่ใช่แค่เสียงของคำ

> 💁 คุณสามารถค้นหาโค้ดนี้ได้ใน [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi) โฟลเดอร์

😀 โปรแกรมแปลงเสียงเป็นข้อความของคุณสำเร็จแล้ว!

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้องมากที่สุด แต่โปรดทราบว่าการแปลโดยระบบอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามนุษย์ที่มีความเชี่ยวชาญ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความที่ผิดพลาดซึ่งเกิดจากการใช้การแปลนี้