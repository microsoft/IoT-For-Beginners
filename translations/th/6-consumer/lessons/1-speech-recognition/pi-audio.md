# บันทึกเสียง - Raspberry Pi

ในส่วนนี้ของบทเรียน คุณจะเขียนโค้ดเพื่อบันทึกเสียงบน Raspberry Pi การบันทึกเสียงจะถูกควบคุมด้วยปุ่มกด

## ฮาร์ดแวร์

Raspberry Pi ต้องการปุ่มกดเพื่อควบคุมการบันทึกเสียง

ปุ่มที่คุณจะใช้คือปุ่ม Grove ซึ่งเป็นเซ็นเซอร์ดิจิทัลที่สามารถเปิดหรือปิดสัญญาณได้ ปุ่มเหล่านี้สามารถตั้งค่าให้ส่งสัญญาณสูงเมื่อกดปุ่ม และส่งสัญญาณต่ำเมื่อไม่ได้กด หรือส่งสัญญาณต่ำเมื่อกด และส่งสัญญาณสูงเมื่อไม่ได้กด

หากคุณใช้ ReSpeaker 2-Mics Pi HAT เป็นไมโครโฟน คุณไม่จำเป็นต้องเชื่อมต่อปุ่มกด เนื่องจาก HAT นี้มีปุ่มติดตั้งมาให้แล้ว ข้ามไปยังส่วนถัดไปได้เลย

### เชื่อมต่อปุ่มกด

ปุ่มกดสามารถเชื่อมต่อกับ Grove base hat ได้

#### งาน - เชื่อมต่อปุ่มกด

![ปุ่ม Grove](../../../../../translated_images/th/grove-button.a70cfbb809a85636.webp)

1. เสียบปลายสาย Grove ด้านหนึ่งเข้ากับช่องเสียบบนโมดูลปุ่มกด สายจะเสียบได้เพียงด้านเดียว

1. เมื่อ Raspberry Pi ปิดอยู่ ให้เชื่อมต่อปลายสาย Grove อีกด้านเข้ากับช่องดิจิทัลที่มีเครื่องหมาย **D5** บน Grove Base hat ที่ติดตั้งอยู่บน Pi ช่องนี้เป็นช่องที่สองจากซ้ายในแถวของช่องที่อยู่ถัดจาก GPIO pins

![ปุ่ม Grove เชื่อมต่อกับช่อง D5](../../../../../translated_images/th/pi-button.c7a1a4f55943341c.webp)

## บันทึกเสียง

คุณสามารถบันทึกเสียงจากไมโครโฟนโดยใช้โค้ด Python

### งาน - บันทึกเสียง

1. เปิด Raspberry Pi และรอให้บูตเสร็จ

1. เปิด VS Code ไม่ว่าจะเปิดโดยตรงบน Pi หรือเชื่อมต่อผ่าน Remote SSH extension

1. PyAudio Pip package มีฟังก์ชันสำหรับบันทึกและเล่นเสียง แพ็กเกจนี้ต้องการไลบรารีเสียงบางตัวที่ต้องติดตั้งก่อน รันคำสั่งต่อไปนี้ในเทอร์มินัลเพื่อติดตั้ง:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. ติดตั้ง PyAudio Pip package

    ```sh
    pip3 install pyaudio
    ```

1. สร้างโฟลเดอร์ใหม่ชื่อ `smart-timer` และเพิ่มไฟล์ชื่อ `app.py` ในโฟลเดอร์นี้

1. เพิ่มการนำเข้า (imports) ต่อไปนี้ที่ด้านบนของไฟล์:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    การนำเข้านี้จะนำเข้าโมดูล `pyaudio` โมดูล Python มาตรฐานบางตัวสำหรับจัดการไฟล์ wave และโมดูล `grove.factory` เพื่อสร้างคลาสปุ่ม

1. ด้านล่างนี้ ให้เพิ่มโค้ดเพื่อสร้างปุ่ม Grove

    หากคุณใช้ ReSpeaker 2-Mics Pi HAT ให้ใช้โค้ดต่อไปนี้:

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    โค้ดนี้จะสร้างปุ่มบนพอร์ต **D17** ซึ่งเป็นพอร์ตที่ปุ่มบน ReSpeaker 2-Mics Pi HAT เชื่อมต่ออยู่ ปุ่มนี้ถูกตั้งค่าให้ส่งสัญญาณต่ำเมื่อกด

    หากคุณไม่ได้ใช้ ReSpeaker 2-Mics Pi HAT และใช้ปุ่ม Grove ที่เชื่อมต่อกับ base hat ให้ใช้โค้ดนี้:

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    โค้ดนี้จะสร้างปุ่มบนพอร์ต **D5** ซึ่งถูกตั้งค่าให้ส่งสัญญาณสูงเมื่อกด

1. ด้านล่างนี้ ให้สร้างอินสแตนซ์ของคลาส PyAudio เพื่อจัดการเสียง:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. กำหนดหมายเลขการ์ดฮาร์ดแวร์สำหรับไมโครโฟนและลำโพง หมายเลขนี้จะเป็นหมายเลขของการ์ดที่คุณพบจากการรันคำสั่ง `arecord -l` และ `aplay -l` ก่อนหน้านี้ในบทเรียน

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    แทนที่ `<microphone card number>` ด้วยหมายเลขการ์ดของไมโครโฟนของคุณ

    แทนที่ `<speaker card number>` ด้วยหมายเลขการ์ดของลำโพงของคุณ ซึ่งเป็นหมายเลขเดียวกับที่คุณตั้งค่าในไฟล์ `alsa.conf`

1. ด้านล่างนี้ กำหนดอัตราการสุ่มตัวอย่าง (sample rate) ที่จะใช้สำหรับการบันทึกและเล่นเสียง คุณอาจต้องเปลี่ยนค่านี้ขึ้นอยู่กับฮาร์ดแวร์ที่คุณใช้

    ```python
    rate = 48000 #48KHz
    ```

    หากคุณพบข้อผิดพลาดเกี่ยวกับอัตราการสุ่มตัวอย่างเมื่อรันโค้ดนี้ในภายหลัง ให้เปลี่ยนค่านี้เป็น `44100` หรือ `16000` ค่ายิ่งสูง คุณภาพเสียงยิ่งดี

1. ด้านล่างนี้ สร้างฟังก์ชันใหม่ชื่อ `capture_audio` ฟังก์ชันนี้จะถูกเรียกเพื่อบันทึกเสียงจากไมโครโฟน:

    ```python
    def capture_audio():
    ```

1. ภายในฟังก์ชันนี้ เพิ่มโค้ดต่อไปนี้เพื่อบันทึกเสียง:

    ```python
    stream = audio.open(format = pyaudio.paInt16,
                        rate = rate,
                        channels = 1, 
                        input_device_index = microphone_card_number,
                        input = True,
                        frames_per_buffer = 4096)

    frames = []

    while button.is_pressed():
        frames.append(stream.read(4096))

    stream.stop_stream()
    stream.close()
    ```

    โค้ดนี้จะเปิดสตรีมอินพุตเสียงโดยใช้วัตถุ PyAudio สตรีมนี้จะบันทึกเสียงจากไมโครโฟนที่ 16KHz โดยบันทึกในบัฟเฟอร์ขนาด 4096 ไบต์

    โค้ดจะวนลูปในขณะที่ปุ่ม Grove ถูกกด โดยอ่านบัฟเฟอร์ขนาด 4096 ไบต์เหล่านี้ลงในอาร์เรย์ในแต่ละครั้ง

    > 💁 คุณสามารถอ่านเพิ่มเติมเกี่ยวกับตัวเลือกที่ส่งไปยังเมธอด `open` ได้ใน [เอกสาร PyAudio](https://people.csail.mit.edu/hubert/pyaudio/docs/)

    เมื่อปล่อยปุ่ม สตรีมจะหยุดและปิด

1. เพิ่มโค้ดต่อไปนี้ที่ท้ายฟังก์ชันนี้:

    ```python
    wav_buffer = io.BytesIO()
    with wave.open(wav_buffer, 'wb') as wavefile:
        wavefile.setnchannels(1)
        wavefile.setsampwidth(audio.get_sample_size(pyaudio.paInt16))
        wavefile.setframerate(rate)
        wavefile.writeframes(b''.join(frames))
        wav_buffer.seek(0)

    return wav_buffer
    ```

    โค้ดนี้จะสร้างบัฟเฟอร์ไบนารี และเขียนเสียงที่บันทึกทั้งหมดลงในบัฟเฟอร์นี้ในรูปแบบ [WAV file](https://wikipedia.org/wiki/WAV) ซึ่งเป็นวิธีมาตรฐานในการเขียนเสียงที่ไม่ถูกบีบอัดลงในไฟล์ จากนั้นบัฟเฟอร์นี้จะถูกส่งคืน

1. เพิ่มฟังก์ชัน `play_audio` ต่อไปนี้เพื่อเล่นเสียงจากบัฟเฟอร์:

    ```python
    def play_audio(buffer):
        stream = audio.open(format = pyaudio.paInt16,
                            rate = rate,
                            channels = 1,
                            output_device_index = speaker_card_number,
                            output = True)
    
        with wave.open(buffer, 'rb') as wf:
            data = wf.readframes(4096)
    
            while len(data) > 0:
                stream.write(data)
                data = wf.readframes(4096)
    
            stream.close()
    ```

    ฟังก์ชันนี้จะเปิดสตรีมเสียงอีกตัวหนึ่ง คราวนี้สำหรับเอาต์พุต - เพื่อเล่นเสียง โดยใช้การตั้งค่าเดียวกับสตรีมอินพุต บัฟเฟอร์จะถูกเปิดเป็นไฟล์ wave และเขียนลงในสตรีมเอาต์พุตในชิ้นส่วนขนาด 4096 ไบต์เพื่อเล่นเสียง จากนั้นสตรีมจะถูกปิด

1. เพิ่มโค้ดต่อไปนี้ด้านล่างฟังก์ชัน `capture_audio` เพื่อวนลูปจนกว่าปุ่มจะถูกกด เมื่อปุ่มถูกกด เสียงจะถูกบันทึกและเล่น

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. รันโค้ด กดปุ่มและพูดใส่ไมโครโฟน ปล่อยปุ่มเมื่อเสร็จ และคุณจะได้ยินการบันทึก

    คุณอาจพบข้อผิดพลาด ALSA บางอย่างเมื่อสร้างอินสแตนซ์ PyAudio ข้อผิดพลาดนี้เกิดจากการตั้งค่าบน Pi สำหรับอุปกรณ์เสียงที่คุณไม่มี คุณสามารถละเว้นข้อผิดพลาดเหล่านี้ได้

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    หากคุณพบข้อผิดพลาดต่อไปนี้:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    ให้เปลี่ยน `rate` เป็น 44100 หรือ 16000

> 💁 คุณสามารถค้นหาโค้ดนี้ได้ในโฟลเดอร์ [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi)

😀 โปรแกรมบันทึกเสียงของคุณสำเร็จแล้ว!

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้องมากที่สุด แต่โปรดทราบว่าการแปลอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาที่เป็นต้นฉบับควรถือว่าเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความผิดที่เกิดจากการใช้การแปลนี้