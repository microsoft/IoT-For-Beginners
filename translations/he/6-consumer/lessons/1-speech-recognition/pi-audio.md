# לכידת שמע - Raspberry Pi

בחלק זה של השיעור, תכתבו קוד ללכידת שמע ב-Raspberry Pi שלכם. לכידת השמע תתבצע באמצעות לחצן.

## חומרה

ה-Raspberry Pi זקוק ללחצן כדי לשלוט בלכידת השמע.

הלחצן שבו תשתמשו הוא לחצן Grove. זהו חיישן דיגיטלי שמפעיל או מכבה אות. ניתן להגדיר את הלחצנים הללו כך שישלחו אות גבוה כאשר הלחצן נלחץ, ואות נמוך כאשר הוא לא נלחץ, או אות נמוך כאשר נלחץ ואות גבוה כאשר לא.

אם אתם משתמשים ב-ReSpeaker 2-Mics Pi HAT כמיקרופון, אין צורך לחבר לחצן, מכיוון שכבר יש לחצן מובנה בכובע זה. דלגו לחלק הבא.

### חיבור הלחצן

ניתן לחבר את הלחצן לכובע הבסיס של Grove.

#### משימה - חיבור הלחצן

![לחצן Grove](../../../../../translated_images/he/grove-button.a70cfbb809a85636.webp)

1. הכניסו קצה אחד של כבל Grove לשקע במודול הלחצן. הוא ייכנס רק בכיוון אחד.

1. כאשר ה-Raspberry Pi כבוי, חברו את הקצה השני של כבל Grove לשקע הדיגיטלי המסומן **D5** בכובע הבסיס של Grove המחובר ל-Pi. שקע זה הוא השני משמאל, בשורה של השקעים ליד פיני GPIO.

![לחצן Grove מחובר לשקע D5](../../../../../translated_images/he/pi-button.c7a1a4f55943341c.webp)

## לכידת שמע

ניתן ללכוד שמע מהמיקרופון באמצעות קוד Python.

### משימה - לכידת שמע

1. הפעילו את ה-Pi והמתינו עד שיסיים את תהליך האתחול.

1. פתחו את VS Code, או ישירות על ה-Pi, או התחברו באמצעות הרחבת Remote SSH.

1. חבילת ה-PyAudio של Pip מכילה פונקציות להקלטה והשמעה של שמע. חבילה זו תלויה בכמה ספריות שמע שצריך להתקין תחילה. הריצו את הפקודות הבאות בטרמינל כדי להתקין אותן:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. התקינו את חבילת ה-PyAudio של Pip.

    ```sh
    pip3 install pyaudio
    ```

1. צרו תיקייה חדשה בשם `smart-timer` והוסיפו קובץ בשם `app.py` לתיקייה זו.

1. הוסיפו את הייבוא הבא לראש הקובץ:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    ייבוא זה כולל את המודול `pyaudio`, כמה מודולים סטנדרטיים של Python לטיפול בקבצי wave, ואת המודול `grove.factory` לייבוא `Factory` ליצירת מחלקת לחצן.

1. מתחת לכך, הוסיפו קוד ליצירת לחצן Grove.

    אם אתם משתמשים ב-ReSpeaker 2-Mics Pi HAT, השתמשו בקוד הבא:

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    קוד זה יוצר לחצן על פורט **D17**, הפורט שאליו מחובר הלחצן ב-ReSpeaker 2-Mics Pi HAT. לחצן זה מוגדר לשלוח אות נמוך כאשר נלחץ.

    אם אינכם משתמשים ב-ReSpeaker 2-Mics Pi HAT, אלא בלחצן Grove המחובר לכובע הבסיס, השתמשו בקוד זה:

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    קוד זה יוצר לחצן על פורט **D5** שמוגדר לשלוח אות גבוה כאשר נלחץ.

1. מתחת לכך, צרו מופע של מחלקת PyAudio לטיפול בשמע:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. הכריזו על מספר כרטיס החומרה עבור המיקרופון והרמקול. זה יהיה המספר של הכרטיס שמצאתם על ידי הרצת `arecord -l` ו-`aplay -l` מוקדם יותר בשיעור.

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    החליפו `<microphone card number>` במספר של כרטיס המיקרופון שלכם.

    החליפו `<speaker card number>` במספר של כרטיס הרמקול שלכם, אותו מספר שהגדרתם בקובץ `alsa.conf`.

1. מתחת לכך, הכריזו על קצב הדגימה לשימוש בלכידת והשמעת השמע. ייתכן שתצטרכו לשנות זאת בהתאם לחומרה שבה אתם משתמשים.

    ```python
    rate = 48000 #48KHz
    ```

    אם אתם מקבלים שגיאות קצב דגימה כאשר אתם מריצים את הקוד מאוחר יותר, שנו ערך זה ל-`44100` או `16000`. ככל שהערך גבוה יותר, איכות הצליל תהיה טובה יותר.

1. מתחת לכך, צרו פונקציה חדשה בשם `capture_audio`. פונקציה זו תופעל כדי ללכוד שמע מהמיקרופון:

    ```python
    def capture_audio():
    ```

1. בתוך הפונקציה, הוסיפו את הקוד הבא ללכידת השמע:

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

    קוד זה פותח זרם קלט שמע באמצעות אובייקט PyAudio. זרם זה ילכוד שמע מהמיקרופון ב-16KHz, ויקלוט אותו במאגרי נתונים בגודל 4096 בתים.

    הקוד לאחר מכן מבצע לולאה בזמן שלחצן Grove נלחץ, וקורא את מאגרי הנתונים הללו בגודל 4096 בתים למערך בכל פעם.

    > 💁 ניתן לקרוא עוד על האפשרויות המועברות לשיטת `open` בתיעוד [PyAudio](https://people.csail.mit.edu/hubert/pyaudio/docs/).

    ברגע שהלחצן משתחרר, הזרם נעצר ונסגר.

1. הוסיפו את הקוד הבא לסוף הפונקציה:

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

    קוד זה יוצר מאגר בינארי, וכותב את כל השמע שנלכד אליו כ-[קובץ WAV](https://wikipedia.org/wiki/WAV). זהו פורמט סטנדרטי לכתיבת שמע לא דחוס לקובץ. מאגר זה מוחזר לאחר מכן.

1. הוסיפו את הפונקציה `play_audio` הבאה להשמעת מאגר השמע:

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

    פונקציה זו פותחת זרם שמע נוסף, הפעם לפלט - להשמעת השמע. היא משתמשת באותן הגדרות כמו זרם הקלט. המאגר נפתח כקובץ wave ונכתב לזרם הפלט במאגרי נתונים בגודל 4096 בתים, ומשמיע את השמע. הזרם נסגר לאחר מכן.

1. הוסיפו את הקוד הבא מתחת לפונקציה `capture_audio` כדי לבצע לולאה עד שהלחצן נלחץ. ברגע שהלחצן נלחץ, השמע נלכד ואז מושמע.

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. הריצו את הקוד. לחצו על הלחצן ודברו אל המיקרופון. שחררו את הלחצן כאשר סיימתם, ותשמעו את ההקלטה.

    ייתכן שתקבלו כמה שגיאות ALSA כאשר מופע PyAudio נוצר. זה נובע מהגדרות ב-Pi עבור התקני שמע שאין לכם. ניתן להתעלם משגיאות אלו.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    אם אתם מקבלים את השגיאה הבאה:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    אז שנו את ה-`rate` ל-44100 או 16000.

> 💁 ניתן למצוא את הקוד הזה בתיקיית [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi).

😀 תוכנית הקלטת השמע שלכם הצליחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.