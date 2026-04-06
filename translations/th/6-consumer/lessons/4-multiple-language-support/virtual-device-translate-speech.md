# แปลคำพูด - อุปกรณ์ IoT เสมือน

ในส่วนนี้ของบทเรียน คุณจะเขียนโค้ดเพื่อแปลคำพูดเมื่อแปลงเป็นข้อความโดยใช้บริการคำพูด จากนั้นแปลข้อความโดยใช้บริการ Translator ก่อนสร้างการตอบกลับด้วยเสียง

## ใช้บริการคำพูดเพื่อแปลคำพูด

บริการคำพูดสามารถรับคำพูดและไม่เพียงแค่แปลงเป็นข้อความในภาษาเดียวกัน แต่ยังสามารถแปลผลลัพธ์เป็นภาษาอื่นได้ด้วย

### งาน - ใช้บริการคำพูดเพื่อแปลคำพูด

1. เปิดโปรเจกต์ `smart-timer` ใน VS Code และตรวจสอบให้แน่ใจว่าสภาพแวดล้อมเสมือนถูกโหลดในเทอร์มินัล

1. เพิ่มคำสั่งนำเข้าต่อไปนี้ด้านล่างคำสั่งนำเข้าที่มีอยู่:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    นี่คือการนำเข้าคลาสที่ใช้ในการแปลคำพูด และไลบรารี `requests` ที่จะใช้ในการเรียกใช้บริการ Translator ในบทเรียนนี้

1. ตัวจับเวลาสมาร์ทของคุณจะมีการตั้งค่าภาษา 2 ภาษา - ภาษาของเซิร์ฟเวอร์ที่ใช้ฝึก LUIS (ภาษาเดียวกันนี้ยังใช้สร้างข้อความเพื่อพูดกับผู้ใช้) และภาษาที่ผู้ใช้พูด อัปเดตตัวแปร `language` ให้เป็นภาษาที่ผู้ใช้จะพูด และเพิ่มตัวแปรใหม่ชื่อ `server_language` สำหรับภาษาที่ใช้ฝึก LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    แทนที่ `<user language>` ด้วยชื่อโลแคลของภาษาที่คุณจะพูด เช่น `fr-FR` สำหรับภาษาฝรั่งเศส หรือ `zn-HK` สำหรับภาษากวางตุ้ง

    แทนที่ `<server language>` ด้วยชื่อโลแคลของภาษาที่ใช้ฝึก LUIS

    คุณสามารถค้นหารายชื่อภาษาที่รองรับและชื่อโลแคลได้ใน [เอกสารสนับสนุนภาษาและเสียงบน Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text)

    > 💁 หากคุณไม่พูดได้หลายภาษา คุณสามารถใช้บริการอย่าง [Bing Translate](https://www.bing.com/translator) หรือ [Google Translate](https://translate.google.com) เพื่อแปลจากภาษาที่คุณถนัดไปยังภาษาที่คุณเลือก บริการเหล่านี้สามารถเล่นเสียงของข้อความที่แปลได้ โปรดทราบว่าตัวจดจำคำพูดอาจไม่รับเสียงบางส่วนจากอุปกรณ์ของคุณ ดังนั้นคุณอาจต้องใช้อุปกรณ์เพิ่มเติมเพื่อเล่นข้อความที่แปล
    >
    > ตัวอย่างเช่น หากคุณฝึก LUIS เป็นภาษาอังกฤษ แต่ต้องการใช้ภาษาฝรั่งเศสเป็นภาษาผู้ใช้ คุณสามารถแปลประโยคเช่น "set a 2 minute and 27 second timer" จากภาษาอังกฤษเป็นภาษาฝรั่งเศสโดยใช้ Bing Translate จากนั้นใช้ปุ่ม **Listen translation** เพื่อพูดการแปลลงในไมโครโฟนของคุณ
    >
    > ![ปุ่ม Listen translation บน Bing Translate](../../../../../translated_images/th/bing-translate.348aa796d6efe2a9.webp)

1. แทนที่การประกาศ `recognizer_config` และ `recognizer` ด้วยโค้ดต่อไปนี้:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    นี่คือการสร้างการตั้งค่าการแปลเพื่อจดจำคำพูดในภาษาผู้ใช้ และสร้างการแปลในภาษาผู้ใช้และภาษาเซิร์ฟเวอร์ จากนั้นใช้การตั้งค่านี้เพื่อสร้างตัวจดจำการแปล - ตัวจดจำคำพูดที่สามารถแปลผลลัพธ์ของการจดจำคำพูดเป็นหลายภาษา

    > 💁 ภาษาต้นฉบับจำเป็นต้องระบุใน `target_languages` มิฉะนั้นคุณจะไม่ได้รับการแปลใด ๆ

1. อัปเดตฟังก์ชัน `recognized` โดยแทนที่เนื้อหาทั้งหมดของฟังก์ชันด้วยโค้ดต่อไปนี้:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    โค้ดนี้ตรวจสอบว่ากิจกรรมที่จดจำได้ถูกเรียกใช้เพราะคำพูดถูกแปลหรือไม่ (กิจกรรมนี้สามารถถูกเรียกใช้ในเวลาอื่น เช่น เมื่อคำพูดถูกจดจำแต่ไม่ได้แปล) หากคำพูดถูกแปล จะค้นหาการแปลในพจนานุกรม `args.result.translations` ที่ตรงกับภาษาเซิร์ฟเวอร์

    พจนานุกรม `args.result.translations` จะใช้คีย์เป็นส่วนของภาษาจากการตั้งค่าโลแคล ไม่ใช่การตั้งค่าทั้งหมด ตัวอย่างเช่น หากคุณขอการแปลเป็น `fr-FR` สำหรับภาษาฝรั่งเศส พจนานุกรมจะมีรายการสำหรับ `fr` ไม่ใช่ `fr-FR`

    ข้อความที่แปลแล้วจะถูกส่งไปยัง IoT Hub

1. รันโค้ดนี้เพื่อทดสอบการแปล ตรวจสอบให้แน่ใจว่าแอปฟังก์ชันของคุณกำลังทำงาน และขอตัวจับเวลาในภาษาผู้ใช้ โดยพูดภาษานั้นด้วยตัวคุณเองหรือใช้แอปแปลภาษา

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## แปลข้อความโดยใช้บริการ Translator

บริการคำพูดไม่รองรับการแปลข้อความกลับเป็นคำพูด แต่คุณสามารถใช้บริการ Translator เพื่อแปลข้อความได้ บริการนี้มี REST API ที่คุณสามารถใช้เพื่อแปลข้อความ

### งาน - ใช้ทรัพยากร Translator เพื่อแปลข้อความ

1. เพิ่มคีย์ API ของ Translator ด้านล่าง `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    แทนที่ `<key>` ด้วยคีย์ API สำหรับทรัพยากรบริการ Translator ของคุณ

1. ด้านบนฟังก์ชัน `say` ให้กำหนดฟังก์ชัน `translate_text` ที่จะแปลข้อความจากภาษาเซิร์ฟเวอร์เป็นภาษาผู้ใช้:

    ```python
    def translate_text(text):
    ```

1. ภายในฟังก์ชันนี้ ให้กำหนด URL และ headers สำหรับการเรียก REST API:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL สำหรับ API นี้ไม่ขึ้นอยู่กับตำแหน่งที่ตั้ง แต่ตำแหน่งที่ตั้งจะถูกส่งผ่านเป็น header คีย์ API ถูกใช้โดยตรง ดังนั้นไม่จำเป็นต้องรับโทเค็นการเข้าถึงจาก API ผู้ออกโทเค็นเหมือนบริการคำพูด

1. ด้านล่างนี้ให้กำหนดพารามิเตอร์และ body สำหรับการเรียก:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` กำหนดพารามิเตอร์ที่จะส่งไปยังการเรียก API โดยส่งภาษาต้นทางและภาษาปลายทาง การเรียกนี้จะแปลข้อความในภาษาต้นทางเป็นภาษาปลายทาง

    `body` มีข้อความที่จะแปล นี่คืออาร์เรย์ เนื่องจากสามารถแปลข้อความหลายบล็อกได้ในการเรียกเดียว

1. เรียก REST API และรับการตอบกลับ:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    การตอบกลับที่กลับมาคือ JSON array โดยมีหนึ่งรายการที่มีการแปล รายการนี้มีอาร์เรย์สำหรับการแปลของรายการทั้งหมดที่ส่งใน body

    ```json
    [
        {
            "translations": [
                {
                    "text": "Chronométrant votre minuterie de 2 minutes 27 secondes.",
                    "to": "fr"
                }
            ]
        }
    ]
    ```

1. ส่งคืนคุณสมบัติ `text` จากการแปลแรกจากรายการแรกในอาร์เรย์:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. อัปเดตฟังก์ชัน `say` เพื่อแปลข้อความที่จะพูดก่อนสร้าง SSML:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    โค้ดนี้ยังพิมพ์ข้อความต้นฉบับและข้อความที่แปลลงในคอนโซลด้วย

1. รันโค้ดของคุณ ตรวจสอบให้แน่ใจว่าแอปฟังก์ชันของคุณกำลังทำงาน และขอตัวจับเวลาในภาษาผู้ใช้ โดยพูดภาษานั้นด้วยตัวคุณเองหรือใช้แอปแปลภาษา

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 เนื่องจากวิธีการพูดบางอย่างในภาษาต่าง ๆ อาจแตกต่างกัน คุณอาจได้รับการแปลที่แตกต่างจากตัวอย่างที่คุณให้กับ LUIS หากเป็นกรณีนี้ ให้เพิ่มตัวอย่างเพิ่มเติมใน LUIS ฝึกใหม่แล้วเผยแพร่โมเดลอีกครั้ง

> 💁 คุณสามารถค้นหาโค้ดนี้ได้ในโฟลเดอร์ [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device)

😀 โปรแกรมตัวจับเวลาหลายภาษาของคุณประสบความสำเร็จ!

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้องมากที่สุด แต่โปรดทราบว่าการแปลอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความผิดที่เกิดจากการใช้การแปลนี้