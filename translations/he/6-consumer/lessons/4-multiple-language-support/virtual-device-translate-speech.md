<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d620a470d9dd8614d99824832978360a",
  "translation_date": "2025-08-27T22:18:29+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/virtual-device-translate-speech.md",
  "language_code": "he"
}
-->
# תרגום דיבור - התקן IoT וירטואלי

בחלק זה של השיעור, תכתבו קוד לתרגום דיבור בעת המרתו לטקסט באמצעות שירות הדיבור, ולאחר מכן תתרגמו את הטקסט באמצעות שירות התרגום לפני יצירת תגובה מדוברת.

## שימוש בשירות הדיבור לתרגום דיבור

שירות הדיבור יכול לקחת דיבור ולהמיר אותו לא רק לטקסט באותה שפה, אלא גם לתרגם את הפלט לשפות אחרות.

### משימה - שימוש בשירות הדיבור לתרגום דיבור

1. פתחו את פרויקט `smart-timer` ב-VS Code, וודאו שהסביבה הווירטואלית נטענה בטרמינל.

1. הוסיפו את פקודות הייבוא הבאות מתחת לפקודות הייבוא הקיימות:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    פקודות אלו מייבאות מחלקות המשמשות לתרגום דיבור, וספריית `requests` שתשמש לביצוע קריאה לשירות התרגום בהמשך השיעור.

1. הטיימר החכם שלכם יוגדר עם שתי שפות - השפה של השרת ששימשה לאימון LUIS (אותה שפה משמשת גם לבניית ההודעות המדוברות למשתמש), והשפה המדוברת על ידי המשתמש. עדכנו את המשתנה `language` לשפה שתדובר על ידי המשתמש, והוסיפו משתנה חדש בשם `server_language` עבור השפה ששימשה לאימון LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    החליפו את `<user language>` בשם האזור של השפה שבה תדברו, לדוגמה `fr-FR` עבור צרפתית, או `zn-HK` עבור קנטונזית.

    החליפו את `<server language>` בשם האזור של השפה ששימשה לאימון LUIS.

    תוכלו למצוא רשימה של השפות הנתמכות ושמות האזורים שלהן בתיעוד [Language and voice support](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) באתר Microsoft Docs.

    > 💁 אם אינכם דוברים מספר שפות, תוכלו להשתמש בשירות כמו [Bing Translate](https://www.bing.com/translator) או [Google Translate](https://translate.google.com) כדי לתרגם מהשפה המועדפת עליכם לשפה אחרת. שירותים אלו יכולים גם להשמיע את הטקסט המתורגם. שימו לב שמזהה הדיבור עשוי להתעלם מחלק מהפלט הקולי של המכשיר שלכם, ולכן ייתכן שתצטרכו להשתמש במכשיר נוסף כדי להשמיע את הטקסט המתורגם.
    >
    > לדוגמה, אם אימנתם את LUIS באנגלית, אך ברצונכם להשתמש בצרפתית כשפת המשתמש, תוכלו לתרגם משפטים כמו "הגדר טיימר של 2 דקות ו-27 שניות" מאנגלית לצרפתית באמצעות Bing Translate, ואז להשתמש בכפתור **Listen translation** כדי לדבר את התרגום למיקרופון שלכם.
    >
    > ![כפתור האזנה לתרגום ב-Bing Translate](../../../../../translated_images/he/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. החליפו את ההצהרות `recognizer_config` ו-`recognizer` עם הבאות:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    קוד זה יוצר תצורת תרגום לזיהוי דיבור בשפת המשתמש, ויצירת תרגומים בשפת המשתמש ובשפת השרת. לאחר מכן, הוא משתמש בתצורה זו כדי ליצור מזהה תרגום - מזהה דיבור שיכול לתרגם את הפלט של זיהוי הדיבור לשפות מרובות.

    > 💁 יש לציין את השפה המקורית ב-`target_languages`, אחרת לא תקבלו תרגומים.

1. עדכנו את הפונקציה `recognized`, והחליפו את כל תוכן הפונקציה עם הבאות:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    קוד זה בודק אם האירוע של זיהוי הופעל בגלל שדיבור תורגם (אירוע זה יכול להיות מופעל בזמנים אחרים, כמו כאשר הדיבור זוהה אך לא תורגם). אם הדיבור תורגם, הוא מוצא את התרגום במילון `args.result.translations` שמתאים לשפת השרת.

    מילון `args.result.translations` מקודד לפי חלק השפה של הגדרת האזור, ולא לפי ההגדרה המלאה. לדוגמה, אם תבקשו תרגום ל-`fr-FR` עבור צרפתית, המילון יכיל ערך עבור `fr`, ולא `fr-FR`.

    הטקסט המתורגם נשלח לאחר מכן ל-IoT Hub.

1. הריצו את הקוד כדי לבדוק את התרגומים. וודאו שהאפליקציה הפונקציונלית שלכם פועלת, ובקשו טיימר בשפת המשתמש, או על ידי דיבור בשפה זו בעצמכם, או באמצעות אפליקציית תרגום.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## תרגום טקסט באמצעות שירות התרגום

שירות הדיבור אינו תומך בתרגום טקסט חזרה לדיבור, במקום זאת תוכלו להשתמש בשירות התרגום כדי לתרגם את הטקסט. לשירות זה יש ממשק API REST שתוכלו להשתמש בו לתרגום הטקסט.

### משימה - שימוש במשאב התרגום לתרגום טקסט

1. הוסיפו את מפתח ה-API של שירות התרגום מתחת ל-`speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    החליפו את `<key>` במפתח ה-API של משאב שירות התרגום שלכם.

1. מעל הפונקציה `say`, הגדירו פונקציה בשם `translate_text` שתתרגם טקסט משפת השרת לשפת המשתמש:

    ```python
    def translate_text(text):
    ```

1. בתוך הפונקציה הזו, הגדירו את ה-URL והכותרות לקריאת ה-API REST:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    ה-URL עבור API זה אינו תלוי מיקום, במקום זאת המיקום מועבר ככותרת. מפתח ה-API משמש ישירות, ולכן בניגוד לשירות הדיבור אין צורך לקבל אסימון גישה מ-API מנפיק האסימונים.

1. מתחת לכך, הגדירו את הפרמטרים והגוף לקריאה:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` מגדיר את הפרמטרים שיש להעביר לקריאת ה-API, ומעביר את השפות המקורית והיעד. קריאה זו תתרגם טקסט בשפה `from` לשפה `to`.

    `body` מכיל את הטקסט לתרגום. זהו מערך, שכן ניתן לתרגם מספר בלוקים של טקסט באותה קריאה.

1. בצעו את הקריאה ל-API REST, וקבלו את התגובה:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    התגובה שמתקבלת היא מערך JSON, עם פריט אחד שמכיל את התרגומים. פריט זה כולל מערך של תרגומים לכל הפריטים שהועברו בגוף הקריאה.

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

1. החזירו את המאפיין `text` מהתרגום הראשון מהפריט הראשון במערך:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. עדכנו את הפונקציה `say` כדי לתרגם את הטקסט לפני יצירת ה-SSML:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    קוד זה גם מדפיס את הגרסאות המקוריות והמתורגמות של הטקסט לקונסול.

1. הריצו את הקוד שלכם. וודאו שהאפליקציה הפונקציונלית שלכם פועלת, ובקשו טיימר בשפת המשתמש, או על ידי דיבור בשפה זו בעצמכם, או באמצעות אפליקציית תרגום.

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

    > 💁 בשל הדרכים השונות לומר דברים בשפות שונות, ייתכן שתקבלו תרגומים השונים מעט מהדוגמאות שנתתם ל-LUIS. אם זה המקרה, הוסיפו עוד דוגמאות ל-LUIS, אימנו מחדש ואז פרסמו את המודל מחדש.

> 💁 תוכלו למצוא את הקוד הזה בתיקיית [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device).

😀 תוכנית הטיימר הרב-לשונית שלכם הייתה הצלחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.