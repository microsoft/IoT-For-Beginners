# แปลข้อความ - Raspberry Pi

ในส่วนนี้ของบทเรียน คุณจะเขียนโค้ดเพื่อแปลข้อความโดยใช้บริการแปลภาษา

## แปลงข้อความเป็นเสียงโดยใช้บริการแปลภาษา

REST API ของบริการเสียงไม่รองรับการแปลโดยตรง แต่คุณสามารถใช้บริการ Translator เพื่อแปลข้อความที่สร้างจากบริการแปลงเสียงเป็นข้อความ และข้อความที่ตอบกลับด้วยเสียง บริการนี้มี REST API ที่คุณสามารถใช้เพื่อแปลข้อความได้

### งาน - ใช้ทรัพยากร Translator เพื่อแปลข้อความ

1. ตัวจับเวลาสมาร์ทของคุณจะมีการตั้งค่าภาษาสองภาษา - ภาษาของเซิร์ฟเวอร์ที่ใช้ฝึก LUIS (ภาษาเดียวกันนี้ยังใช้สร้างข้อความเพื่อพูดกับผู้ใช้) และภาษาที่ผู้ใช้พูด อัปเดตตัวแปร `language` ให้เป็นภาษาที่ผู้ใช้จะพูด และเพิ่มตัวแปรใหม่ชื่อ `server_language` สำหรับภาษาที่ใช้ฝึก LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    แทนที่ `<user language>` ด้วยชื่อโลเคลของภาษาที่คุณจะพูด เช่น `fr-FR` สำหรับภาษาฝรั่งเศส หรือ `zn-HK` สำหรับภาษากวางตุ้ง

    แทนที่ `<server language>` ด้วยชื่อโลเคลของภาษาที่ใช้ฝึก LUIS

    คุณสามารถค้นหารายชื่อภาษาที่รองรับและชื่อโลเคลได้ใน [เอกสารสนับสนุนภาษาและเสียงบน Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text)

    > 💁 หากคุณไม่พูดได้หลายภาษา คุณสามารถใช้บริการอย่าง [Bing Translate](https://www.bing.com/translator) หรือ [Google Translate](https://translate.google.com) เพื่อแปลจากภาษาที่คุณถนัดไปยังภาษาที่คุณเลือก บริการเหล่านี้สามารถเล่นเสียงของข้อความที่แปลได้
    >
    > ตัวอย่างเช่น หากคุณฝึก LUIS ในภาษาอังกฤษ แต่ต้องการใช้ภาษาฝรั่งเศสเป็นภาษาผู้ใช้ คุณสามารถแปลประโยคเช่น "ตั้งเวลาสองนาทีและยี่สิบเจ็ดวินาที" จากภาษาอังกฤษเป็นภาษาฝรั่งเศสโดยใช้ Bing Translate จากนั้นใช้ปุ่ม **ฟังการแปล** เพื่อพูดการแปลผ่านไมโครโฟนของคุณ
    >
    > ![ปุ่มฟังการแปลบน Bing Translate](../../../../../translated_images/th/bing-translate.348aa796d6efe2a9.webp)

1. เพิ่มคีย์ API ของ Translator ใต้ `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    แทนที่ `<key>` ด้วยคีย์ API สำหรับทรัพยากรบริการแปลภาษาของคุณ

1. เหนือฟังก์ชัน `say` ให้กำหนดฟังก์ชัน `translate_text` ที่จะใช้แปลข้อความจากภาษาของเซิร์ฟเวอร์ไปยังภาษาของผู้ใช้:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    ภาษาต้นทางและปลายทางจะถูกส่งไปยังฟังก์ชันนี้ - แอปของคุณต้องแปลงจากภาษาผู้ใช้เป็นภาษาของเซิร์ฟเวอร์เมื่อรับรู้เสียง และจากภาษาของเซิร์ฟเวอร์เป็นภาษาผู้ใช้เมื่อให้คำตอบด้วยเสียง

1. ภายในฟังก์ชันนี้ ให้กำหนด URL และ headers สำหรับการเรียก REST API:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL สำหรับ API นี้ไม่ขึ้นอยู่กับตำแหน่งที่ตั้ง แต่ตำแหน่งที่ตั้งจะถูกส่งเป็น header คีย์ API ถูกใช้โดยตรง ดังนั้นไม่จำเป็นต้องรับโทเค็นการเข้าถึงจาก API ผู้ออกโทเค็นเหมือนบริการเสียง

1. ใต้ส่วนนี้ กำหนดพารามิเตอร์และ body สำหรับการเรียก:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` กำหนดพารามิเตอร์ที่จะส่งไปยังการเรียก API โดยส่งภาษาต้นทางและปลายทาง การเรียกนี้จะแปลข้อความในภาษาต้นทางเป็นภาษาปลายทาง

    `body` ประกอบด้วยข้อความที่จะถูกแปล ซึ่งเป็นอาร์เรย์ เนื่องจากสามารถแปลข้อความหลายบล็อกในคำสั่งเดียวกันได้

1. ทำการเรียก REST API และรับการตอบกลับ:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    การตอบกลับที่ได้รับกลับมาเป็น JSON array โดยมีหนึ่งรายการที่มีการแปล รายการนี้มีอาร์เรย์สำหรับการแปลของทุกรายการที่ส่งใน body

    ```json
    [
        {
            "translations": [
                {
                    "text": "Set a 2 minute 27 second timer.",
                    "to": "en"
                }
            ]
        }
    ]
    ```

1. ส่งคืนคุณสมบัติ `test` จากการแปลแรกในรายการแรกของอาร์เรย์:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. อัปเดตลูป `while True` เพื่อแปลข้อความจากการเรียก `convert_speech_to_text` จากภาษาผู้ใช้เป็นภาษาของเซิร์ฟเวอร์:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    โค้ดนี้ยังพิมพ์ข้อความต้นฉบับและข้อความที่แปลลงในคอนโซลด้วย

1. อัปเดตฟังก์ชัน `say` เพื่อแปลข้อความที่จะพูดจากภาษาของเซิร์ฟเวอร์เป็นภาษาผู้ใช้:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    โค้ดนี้ยังพิมพ์ข้อความต้นฉบับและข้อความที่แปลลงในคอนโซลด้วย

1. รันโค้ดของคุณ ตรวจสอบให้แน่ใจว่าแอปฟังก์ชันของคุณกำลังทำงาน และขอตั้งเวลาผ่านภาษาผู้ใช้ ไม่ว่าจะโดยการพูดภาษานั้นเอง หรือใช้แอปแปลภาษา

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py
    Connecting
    Connected
    Using voice fr-FR-DeniseNeural
    Original: Définir une minuterie de 2 minutes et 27 secondes.
    Translated: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 เนื่องจากวิธีการพูดบางอย่างในภาษาต่างๆ อาจแตกต่างกัน คุณอาจได้รับการแปลที่แตกต่างจากตัวอย่างที่คุณให้กับ LUIS หากเป็นกรณีนี้ ให้เพิ่มตัวอย่างเพิ่มเติมใน LUIS ฝึกใหม่ แล้วเผยแพร่โมเดลอีกครั้ง

> 💁 คุณสามารถค้นหาโค้ดนี้ได้ใน [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi) โฟลเดอร์

😀 โปรแกรมจับเวลาหลายภาษาของคุณประสบความสำเร็จ!

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้อง แต่โปรดทราบว่าการแปลโดยอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความผิดที่เกิดจากการใช้การแปลนี้