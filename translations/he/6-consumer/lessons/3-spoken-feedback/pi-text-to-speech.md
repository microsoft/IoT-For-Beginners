<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-27T22:28:01+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "he"
}
-->
# טקסט לדיבור - Raspberry Pi

בחלק זה של השיעור, תכתבו קוד להמרת טקסט לדיבור באמצעות שירות הדיבור.

## המרת טקסט לדיבור באמצעות שירות הדיבור

ניתן לשלוח טקסט לשירות הדיבור באמצעות REST API כדי לקבל דיבור כקובץ שמע שניתן להשמיע במכשיר ה-IoT שלכם. כאשר מבקשים דיבור, יש לספק את הקול שבו יש להשתמש, שכן ניתן לייצר דיבור באמצעות מגוון קולות שונים.

כל שפה תומכת במגוון קולות שונים, וניתן לבצע בקשת REST לשירות הדיבור כדי לקבל את רשימת הקולות הנתמכים עבור כל שפה.

### משימה - קבלת קול

1. פתחו את פרויקט `smart-timer` ב-VS Code.

1. הוסיפו את הקוד הבא מעל הפונקציה `say` כדי לבקש את רשימת הקולות עבור שפה מסוימת:

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

    קוד זה מגדיר פונקציה בשם `get_voice` שמשתמשת בשירות הדיבור כדי לקבל רשימת קולות. לאחר מכן, היא מוצאת את הקול הראשון שמתאים לשפה שבה משתמשים.

    פונקציה זו נקראת כדי לשמור את הקול הראשון, ושם הקול מודפס לקונסול. ניתן לבקש קול זה פעם אחת ולהשתמש בערך עבור כל קריאה להמרת טקסט לדיבור.

    > 💁 ניתן לקבל את הרשימה המלאה של הקולות הנתמכים מתוך [התיעוד על תמיכה בשפות וקולות ב-Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). אם ברצונכם להשתמש בקול מסוים, תוכלו להסיר פונקציה זו ולכתוב את שם הקול ישירות מתוך התיעוד. לדוגמה:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### משימה - המרת טקסט לדיבור

1. מתחת לכך, הגדירו קבוע עבור פורמט השמע שיתקבל משירותי הדיבור. כאשר מבקשים שמע, ניתן לעשות זאת במגוון פורמטים שונים.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    הפורמט שבו ניתן להשתמש תלוי בחומרה שלכם. אם אתם מקבלים שגיאות `Invalid sample rate` בעת השמעת השמע, שנו זאת לערך אחר. ניתן למצוא את רשימת הערכים הנתמכים ב-[תיעוד REST API של טקסט לדיבור ב-Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs). תצטרכו להשתמש בפורמט שמע `riff`, והערכים שכדאי לנסות הם `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` ו-`riff-48khz-16bit-mono-pcm`.

1. מתחת לכך, הכריזו על פונקציה בשם `get_speech` שתמיר את הטקסט לדיבור באמצעות REST API של שירות הדיבור:

    ```python
    def get_speech(text):
    ```

1. בתוך הפונקציה `get_speech`, הגדירו את ה-URL לקריאה ואת הכותרות להעברה:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    זה מגדיר את הכותרות לשימוש בטוקן גישה שנוצר, מגדיר את התוכן כ-SSML ומגדיר את פורמט השמע הנדרש.

1. מתחת לכך, הגדירו את ה-SSML לשליחה ל-REST API:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    ה-SSML הזה מגדיר את השפה והקול לשימוש, יחד עם הטקסט להמרה.

1. לבסוף, הוסיפו קוד בפונקציה זו לביצוע בקשת REST והחזרת נתוני השמע הבינאריים:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### משימה - השמעת השמע

1. מתחת לפונקציה `get_speech`, הגדירו פונקציה חדשה להשמעת השמע שהוחזר מקריאת REST API:

    ```python
    def play_speech(speech):
    ```

1. ה-`speech` שמועבר לפונקציה זו יהיה נתוני השמע הבינאריים שהוחזרו מ-REST API. השתמשו בקוד הבא כדי לפתוח זאת כקובץ wave ולהעביר אותו ל-PyAudio להשמעת השמע:

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

    קוד זה משתמש בזרם PyAudio, בדומה ללכידת שמע. ההבדל כאן הוא שהזרם מוגדר כזרם פלט, ונתונים נקראים מנתוני השמע ומועברים לזרם.

    במקום לקבוע מראש את פרטי הזרם כמו קצב הדגימה, הם נקראים מתוך נתוני השמע.

1. החליפו את תוכן הפונקציה `say` בתוכן הבא:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    קוד זה ממיר את הטקסט לדיבור כנתוני שמע בינאריים ומשמיע את השמע.

1. הריצו את האפליקציה, וודאו שאפליקציית הפונקציה פועלת גם היא. הגדירו כמה טיימרים, ותשמעו תגובה קולית שאומרת שהטיימר שלכם הוגדר, ולאחר מכן תגובה קולית נוספת כשהטיימר מסתיים.

    אם אתם מקבלים שגיאות `Invalid sample rate`, שנו את ה-`playback_format` כפי שתואר למעלה.

> 💁 ניתן למצוא את הקוד הזה בתיקייה [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi).

😀 תוכנית הטיימר שלכם הייתה הצלחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו אחראים לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.