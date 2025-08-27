<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-27T20:28:40+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "th"
}
-->
# Text to speech - Raspberry Pi

ในส่วนนี้ของบทเรียน คุณจะเขียนโค้ดเพื่อแปลงข้อความเป็นเสียงโดยใช้บริการเสียงพูด

## แปลงข้อความเป็นเสียงโดยใช้บริการเสียงพูด

ข้อความสามารถส่งไปยังบริการเสียงพูดผ่าน REST API เพื่อรับเสียงเป็นไฟล์เสียงที่สามารถเล่นบนอุปกรณ์ IoT ของคุณได้ เมื่อร้องขอเสียงพูด คุณจำเป็นต้องระบุเสียงที่จะใช้ เนื่องจากเสียงพูดสามารถสร้างได้จากเสียงที่หลากหลาย

แต่ละภาษารองรับเสียงที่แตกต่างกัน และคุณสามารถทำการร้องขอ REST กับบริการเสียงพูดเพื่อรับรายการเสียงที่รองรับสำหรับแต่ละภาษา

### งาน - รับเสียงพูด

1. เปิดโปรเจกต์ `smart-timer` ใน VS Code

1. เพิ่มโค้ดต่อไปนี้เหนือฟังก์ชัน `say` เพื่อร้องขอรายการเสียงสำหรับภาษา:

    ```python
    def get_voice():
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token()
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        first_voice = next(x for x in voices_json if x['Locale'].lower() == language.lower() and x['VoiceType'] == 'Neural')
        return first_voice['ShortName']
    
    voice = get_voice()
    print(f'Using voice {voice}')
    ```

    โค้ดนี้กำหนดฟังก์ชันที่ชื่อว่า `get_voice` ซึ่งใช้บริการเสียงพูดเพื่อรับรายการเสียง จากนั้นจะค้นหาเสียงแรกที่ตรงกับภาษาที่กำลังใช้งาน

    ฟังก์ชันนี้จะถูกเรียกเพื่อเก็บเสียงแรก และชื่อเสียงจะถูกพิมพ์ลงในคอนโซล เสียงนี้สามารถร้องขอครั้งเดียวและใช้ค่านี้สำหรับทุกการเรียกเพื่อแปลงข้อความเป็นเสียงพูด

    > 💁 คุณสามารถรับรายการเสียงที่รองรับทั้งหมดได้จาก [เอกสาร Language and voice support บน Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech) หากคุณต้องการใช้เสียงเฉพาะ คุณสามารถลบฟังก์ชันนี้และกำหนดเสียงโดยตรงจากชื่อเสียงในเอกสารนี้ ตัวอย่างเช่น:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### งาน - แปลงข้อความเป็นเสียงพูด

1. ด้านล่างนี้ ให้กำหนดค่าคงที่สำหรับรูปแบบเสียงที่จะดึงมาจากบริการเสียงพูด เมื่อคุณร้องขอเสียง คุณสามารถทำได้ในรูปแบบที่หลากหลาย

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    รูปแบบที่คุณสามารถใช้ขึ้นอยู่กับฮาร์ดแวร์ของคุณ หากคุณได้รับข้อผิดพลาด `Invalid sample rate` เมื่อเล่นเสียง ให้เปลี่ยนเป็นค่าอื่น คุณสามารถค้นหารายการค่าที่รองรับได้ใน [เอกสาร Text to speech REST API บน Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs) คุณจะต้องใช้เสียงในรูปแบบ `riff` และค่าที่ควรลองคือ `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` และ `riff-48khz-16bit-mono-pcm`

1. ด้านล่างนี้ ให้ประกาศฟังก์ชันที่ชื่อว่า `get_speech` ซึ่งจะใช้ REST API ของบริการเสียงพูดเพื่อแปลงข้อความเป็นเสียง:

    ```python
    def get_speech(text):
    ```

1. ในฟังก์ชัน `get_speech` ให้กำหนด URL ที่จะเรียกและส่วนหัวที่จะส่ง:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    ส่วนนี้กำหนดส่วนหัวเพื่อใช้โทเค็นการเข้าถึงที่สร้างขึ้น กำหนดเนื้อหาเป็น SSML และกำหนดรูปแบบเสียงที่ต้องการ

1. ด้านล่างนี้ ให้กำหนด SSML ที่จะส่งไปยัง REST API:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    SSML นี้กำหนดภาษาและเสียงที่จะใช้ พร้อมกับข้อความที่จะแปลง

1. สุดท้าย เพิ่มโค้ดในฟังก์ชันนี้เพื่อทำการร้องขอ REST และส่งคืนข้อมูลเสียงแบบไบนารี:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### งาน - เล่นเสียง

1. ด้านล่างฟังก์ชัน `get_speech` ให้กำหนดฟังก์ชันใหม่เพื่อเล่นเสียงที่ส่งคืนจากการเรียก REST API:

    ```python
    def play_speech(speech):
    ```

1. `speech` ที่ส่งไปยังฟังก์ชันนี้จะเป็นข้อมูลเสียงแบบไบนารีที่ส่งคืนจาก REST API ใช้โค้ดต่อไปนี้เพื่อเปิดเป็นไฟล์ wave และส่งไปยัง PyAudio เพื่อเล่นเสียง:

    ```python
    def play_speech(speech):
        with wave.open(speech, 'rb') as wave_file:
            stream = audio.open(format=audio.get_format_from_width(wave_file.getsampwidth()),
                                channels=wave_file.getnchannels(),
                                rate=wave_file.getframerate(),
                                output_device_index=speaker_card_number,
                                output=True)

            data = wave_file.readframes(4096)

            while len(data) > 0:
                stream.write(data)
                data = wave_file.readframes(4096)

            stream.stop_stream()
            stream.close()
    ```

    โค้ดนี้ใช้สตรีม PyAudio เช่นเดียวกับการจับเสียง ความแตกต่างคือสตรีมถูกตั้งค่าเป็นสตรีมเอาต์พุต และข้อมูลถูกอ่านจากข้อมูลเสียงและส่งไปยังสตรีม

    แทนที่จะกำหนดรายละเอียดสตรีม เช่น อัตราตัวอย่างโดยตรง รายละเอียดเหล่านี้จะถูกอ่านจากข้อมูลเสียง

1. แทนที่เนื้อหาของฟังก์ชัน `say` ด้วยโค้ดต่อไปนี้:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    โค้ดนี้แปลงข้อความเป็นเสียงเป็นข้อมูลเสียงแบบไบนารี และเล่นเสียง

1. รันแอป และตรวจสอบให้แน่ใจว่าแอปฟังก์ชันกำลังทำงานอยู่ ตั้งค่าตัวจับเวลา และคุณจะได้ยินการตอบกลับด้วยเสียงพูดที่บอกว่าตัวจับเวลาของคุณถูกตั้งค่าแล้ว และอีกครั้งเมื่อจับเวลาสิ้นสุด

    หากคุณได้รับข้อผิดพลาด `Invalid sample rate` ให้เปลี่ยน `playback_format` ตามที่อธิบายไว้ด้านบน

> 💁 คุณสามารถค้นหาโค้ดนี้ได้ใน [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi) โฟลเดอร์

😀 โปรแกรมตัวจับเวลาของคุณสำเร็จแล้ว!

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้องมากที่สุด แต่โปรดทราบว่าการแปลอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความผิดที่เกิดจากการใช้การแปลนี้