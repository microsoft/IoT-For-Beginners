<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-27T20:24:05+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "th"
}
-->
# Text to speech - อุปกรณ์ IoT เสมือนจริง

ในส่วนนี้ของบทเรียน คุณจะเขียนโค้ดเพื่อแปลงข้อความเป็นเสียงโดยใช้บริการเสียงพูด

## แปลงข้อความเป็นเสียง

SDK ของบริการเสียงพูดที่คุณใช้ในบทเรียนก่อนหน้าเพื่อแปลงเสียงพูดเป็นข้อความ สามารถใช้เพื่อแปลงข้อความกลับเป็นเสียงพูดได้เช่นกัน เมื่อร้องขอเสียงพูด คุณจำเป็นต้องระบุเสียงที่จะใช้ เนื่องจากเสียงพูดสามารถสร้างได้จากเสียงที่หลากหลาย

แต่ละภาษารองรับเสียงที่แตกต่างกัน และคุณสามารถดูรายการเสียงที่รองรับสำหรับแต่ละภาษาได้จาก SDK ของบริการเสียงพูด

### งาน - แปลงข้อความเป็นเสียง

1. เปิดโปรเจกต์ `smart-timer` ใน VS Code และตรวจสอบให้แน่ใจว่าสภาพแวดล้อมเสมือนถูกโหลดในเทอร์มินัล

1. นำเข้า `SpeechSynthesizer` จากแพ็กเกจ `azure.cognitiveservices.speech` โดยเพิ่มลงในส่วนการนำเข้าที่มีอยู่:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. เหนือฟังก์ชัน `say` สร้างการตั้งค่าการพูดเพื่อใช้กับ speech synthesizer:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    การตั้งค่านี้ใช้ API key, location และ language เดียวกันกับที่ใช้โดย recognizer

1. ด้านล่างนี้ เพิ่มโค้ดต่อไปนี้เพื่อรับเสียงและตั้งค่าใน speech config:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    โค้ดนี้ดึงรายการเสียงทั้งหมดที่มีอยู่ จากนั้นค้นหาเสียงแรกที่ตรงกับภาษาที่กำลังใช้งาน

    > 💁 คุณสามารถดูรายการเสียงที่รองรับทั้งหมดได้จาก [เอกสาร Language and voice support บน Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech) หากคุณต้องการใช้เสียงเฉพาะ คุณสามารถลบฟังก์ชันนี้และกำหนดเสียงโดยตรงด้วยชื่อเสียงจากเอกสารนี้ ตัวอย่างเช่น:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. อัปเดตเนื้อหาของฟังก์ชัน `say` เพื่อสร้าง SSML สำหรับการตอบสนอง:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. ด้านล่างนี้ หยุดการรับรู้เสียงพูด พูด SSML จากนั้นเริ่มการรับรู้ใหม่อีกครั้ง:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    การรับรู้จะถูกหยุดในขณะที่ข้อความถูกพูดเพื่อหลีกเลี่ยงการที่การประกาศการเริ่มต้นตัวจับเวลาถูกตรวจจับ ส่งไปยัง LUIS และอาจถูกตีความว่าเป็นคำขอในการตั้งค่าตัวจับเวลาใหม่

    > 💁 คุณสามารถทดสอบสิ่งนี้ได้โดยการคอมเมนต์บรรทัดที่หยุดและเริ่มการรับรู้ใหม่ ตั้งค่าตัวจับเวลา และคุณอาจพบว่าการประกาศตั้งค่าตัวจับเวลาใหม่ ซึ่งทำให้เกิดการประกาศใหม่ นำไปสู่การตั้งค่าตัวจับเวลาใหม่ และวนซ้ำไปเรื่อยๆ!

1. รันแอป และตรวจสอบให้แน่ใจว่าแอปฟังก์ชันกำลังทำงานอยู่ ตั้งค่าตัวจับเวลา และคุณจะได้ยินการตอบสนองด้วยเสียงพูดที่บอกว่าตัวจับเวลาของคุณถูกตั้งค่าแล้ว จากนั้นจะมีการตอบสนองด้วยเสียงพูดอีกครั้งเมื่อตัวจับเวลาสิ้นสุด

> 💁 คุณสามารถค้นหาโค้ดนี้ได้ในโฟลเดอร์ [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device)

😀 โปรแกรมตัวจับเวลาของคุณประสบความสำเร็จ!

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้องมากที่สุด แต่โปรดทราบว่าการแปลอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความผิดที่เกิดจากการใช้การแปลนี้