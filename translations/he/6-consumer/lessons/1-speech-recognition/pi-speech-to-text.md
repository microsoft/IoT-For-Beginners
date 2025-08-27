<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-27T22:43:29+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "he"
}
-->
# דיבור לטקסט - Raspberry Pi

בחלק זה של השיעור, תכתבו קוד להמרת דיבור באודיו שהוקלט לטקסט באמצעות שירות הדיבור.

## שליחת האודיו לשירות הדיבור

ניתן לשלוח את האודיו לשירות הדיבור באמצעות REST API. כדי להשתמש בשירות הדיבור, תחילה עליכם לבקש אסימון גישה, ואז להשתמש באסימון זה כדי לגשת ל-REST API. אסימוני הגישה פגים לאחר 10 דקות, ולכן הקוד שלכם צריך לבקש אותם באופן קבוע כדי להבטיח שהם תמיד מעודכנים.

### משימה - קבלת אסימון גישה

1. פתחו את פרויקט `smart-timer` על ה-Pi שלכם.

1. הסירו את הפונקציה `play_audio`. אין בה צורך יותר, מכיוון שאתם לא רוצים שהטיימר החכם יחזור על מה שאמרתם.

1. הוסיפו את הייבוא הבא לראש קובץ `app.py`:

    ```python
    import requests
    ```

1. הוסיפו את הקוד הבא מעל הלולאה `while True` כדי להגדיר כמה הגדרות עבור שירות הדיבור:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    החליפו את `<key>` במפתח ה-API של משאב שירות הדיבור שלכם. החליפו את `<location>` במיקום שבו יצרתם את משאב שירות הדיבור.

    החליפו את `<language>` בשם האזור עבור השפה שבה תדברו, לדוגמה `en-GB` עבור אנגלית, או `zn-HK` עבור קנטונזית. תוכלו למצוא רשימה של השפות הנתמכות ושמות האזור שלהן בתיעוד [Language and voice support documentation on Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

1. מתחת לזה, הוסיפו את הפונקציה הבאה לקבלת אסימון גישה:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    פונקציה זו קוראת לנקודת קצה להנפקת אסימונים, ומעבירה את מפתח ה-API ככותרת. קריאה זו מחזירה אסימון גישה שניתן להשתמש בו כדי לקרוא לשירותי הדיבור.

1. מתחת לזה, הכריזו על פונקציה להמרת דיבור באודיו שהוקלט לטקסט באמצעות REST API:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. בתוך הפונקציה הזו, הגדירו את כתובת ה-URL של REST API ואת הכותרות:

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

    פונקציה זו בונה כתובת URL באמצעות המיקום של משאב שירותי הדיבור. לאחר מכן היא ממלאת את הכותרות עם אסימון הגישה מהפונקציה `get_access_token`, כמו גם את קצב הדגימה ששימש להקלטת האודיו. לבסוף, היא מגדירה כמה פרמטרים שיועברו עם כתובת ה-URL המכילים את השפה באודיו.

1. מתחת לזה, הוסיפו את הקוד הבא לקריאה ל-REST API וקבלת הטקסט:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    פונקציה זו קוראת לכתובת ה-URL ומפענחת את ערך ה-JSON שמגיע בתגובה. הערך `RecognitionStatus` בתגובה מציין אם הקריאה הצליחה להמיר דיבור לטקסט, ואם הערך הוא `Success`, הטקסט מוחזר מהפונקציה, אחרת מוחזר מחרוזת ריקה.

1. מעל הלולאה `while True:`, הגדירו פונקציה לעיבוד הטקסט שהוחזר משירות הדיבור לטקסט. פונקציה זו פשוט תדפיס את הטקסט לקונסול בשלב זה.

    ```python
    def process_text(text):
        print(text)
    ```

1. לבסוף, החליפו את הקריאה ל-`play_audio` בלולאה `while True` בקריאה לפונקציה `convert_speech_to_text`, והעבירו את הטקסט לפונקציה `process_text`:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. הריצו את הקוד. לחצו על הכפתור ודברו לתוך המיקרופון. שחררו את הכפתור כשסיימתם, והאודיו יומר לטקסט ויודפס לקונסול.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    נסו סוגים שונים של משפטים, יחד עם משפטים שבהם מילים נשמעות אותו דבר אך יש להן משמעויות שונות. לדוגמה, אם אתם מדברים באנגלית, אמרו 'I want to buy two bananas and an apple too', ושימו לב כיצד הוא ישתמש בצורה הנכונה של to, two ו-too בהתבסס על ההקשר של המילה, ולא רק על הצליל שלה.

> 💁 תוכלו למצוא את הקוד הזה בתיקיית [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi).

😀 התוכנית שלכם להמרת דיבור לטקסט הצליחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.