<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-27T22:36:56+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "he"
}
-->
# דיבור לטקסט - מכשיר IoT וירטואלי

בחלק זה של השיעור, תכתבו קוד להמרת דיבור שנקלט מהמיקרופון שלכם לטקסט באמצעות שירות הדיבור.

## המרת דיבור לטקסט

במערכות Windows, Linux ו-macOS, ניתן להשתמש ב-SDK של שירותי הדיבור עבור Python כדי להאזין למיקרופון שלכם ולהמיר כל דיבור שמזוהה לטקסט. הוא יאזין באופן רציף, יזהה את רמות האודיו וישלח את הדיבור להמרה לטקסט כאשר רמת האודיו יורדת, כמו בסיום בלוק של דיבור.

### משימה - המרת דיבור לטקסט

1. צרו אפליקציית Python חדשה במחשב שלכם בתיקייה בשם `smart-timer` עם קובץ יחיד בשם `app.py` וסביבת עבודה וירטואלית של Python.

1. התקינו את חבילת Pip עבור שירותי הדיבור. ודאו שאתם מתקינים זאת מתוך טרמינל שבו סביבת העבודה הווירטואלית מופעלת.

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ אם אתם מקבלים את השגיאה הבאה:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > תצטרכו לעדכן את Pip. עשו זאת באמצעות הפקודה הבאה, ואז נסו להתקין את החבילה שוב:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. הוסיפו את הייבוא הבא לקובץ `app.py`:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    זה מייבא כמה מחלקות המשמשות לזיהוי דיבור.

1. הוסיפו את הקוד הבא להצהרה על כמה הגדרות:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    החליפו `<key>` במפתח ה-API של שירות הדיבור שלכם. החליפו `<location>` במיקום שבו יצרתם את משאב שירות הדיבור.

    החליפו `<language>` בשם האזור עבור השפה שבה תדברו, לדוגמה `en-GB` עבור אנגלית, או `zn-HK` עבור קנטונזית. תוכלו למצוא רשימה של השפות הנתמכות ושמות האזורים שלהן בתיעוד [תמיכה בשפה וקול במיקרוסופט](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    הגדרות אלו משמשות ליצירת אובייקט `SpeechConfig` שישמש להגדרת שירותי הדיבור.

1. הוסיפו את הקוד הבא ליצירת מזהה דיבור:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. מזהה הדיבור פועל על שרשור רקע, מאזין לאודיו וממיר כל דיבור שבו לטקסט. ניתן לקבל את הטקסט באמצעות פונקציית callback - פונקציה שאתם מגדירים ומעבירים למזהה. בכל פעם שמזוהה דיבור, הפונקציה נקראת. הוסיפו את הקוד הבא להגדרת פונקציית callback, והעבירו את הפונקציה הזו למזהה, כמו גם הגדרת פונקציה לעיבוד הטקסט, שתכתוב אותו לקונסול:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. המזהה מתחיל להאזין רק כאשר אתם מפעילים אותו באופן מפורש. הוסיפו את הקוד הבא כדי להתחיל את הזיהוי. זה פועל ברקע, ולכן האפליקציה שלכם תצטרך גם לולאה אינסופית שתישן כדי לשמור על האפליקציה פעילה.

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. הריצו את האפליקציה הזו. דברו למיקרופון שלכם והאודיו שהומר לטקסט יופיע בקונסול.

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    נסו סוגים שונים של משפטים, יחד עם משפטים שבהם מילים נשמעות אותו דבר אך יש להן משמעויות שונות. לדוגמה, אם אתם מדברים באנגלית, אמרו 'I want to buy two bananas and an apple too', ושימו לב כיצד הוא ישתמש בצורה הנכונה של to, two ו-too בהתבסס על ההקשר של המילה, ולא רק על הצליל שלה.

> 💁 תוכלו למצוא את הקוד הזה בתיקייה [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device).

😀 תוכנית הדיבור לטקסט שלכם הצליחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.