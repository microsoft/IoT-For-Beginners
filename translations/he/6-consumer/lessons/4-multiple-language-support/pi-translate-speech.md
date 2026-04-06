# תרגום דיבור - Raspberry Pi

בחלק זה של השיעור, תכתבו קוד לתרגום טקסט באמצעות שירות התרגום.

## המרת טקסט לדיבור באמצעות שירות התרגום

ממשק ה-REST API של שירות הדיבור אינו תומך בתרגומים ישירים. במקום זאת, ניתן להשתמש בשירות התרגום כדי לתרגם את הטקסט שנוצר על ידי שירות הדיבור לטקסט, ואת הטקסט של התגובה המדוברת. לשירות זה יש ממשק REST API שניתן להשתמש בו לתרגום הטקסט.

### משימה - שימוש במשאב התרגום לתרגום טקסט

1. לטיימר החכם שלכם יהיו שתי שפות מוגדרות - השפה של השרת ששימשה לאימון LUIS (אותה שפה משמשת גם לבניית ההודעות שמדברות עם המשתמש), והשפה המדוברת על ידי המשתמש. עדכנו את המשתנה `language` כך שיתאים לשפה שתדובר על ידי המשתמש, והוסיפו משתנה חדש בשם `server_language` עבור השפה ששימשה לאימון LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    החליפו `<user language>` בשם האזור (locale) של השפה שבה תדברו, לדוגמה `fr-FR` עבור צרפתית, או `zn-HK` עבור קנטונזית.

    החליפו `<server language>` בשם האזור של השפה ששימשה לאימון LUIS.

    ניתן למצוא רשימה של השפות הנתמכות ושמות האזורים שלהן בתיעוד [Language and voice support באתר Microsoft](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 אם אינכם דוברים מספר שפות, תוכלו להשתמש בשירות כמו [Bing Translate](https://www.bing.com/translator) או [Google Translate](https://translate.google.com) כדי לתרגם מהשפה המועדפת עליכם לשפה אחרת. שירותים אלו יכולים גם להשמיע את הטקסט המתורגם.
    >
    > לדוגמה, אם אימנתם את LUIS באנגלית, אך ברצונכם להשתמש בצרפתית כשפת המשתמש, תוכלו לתרגם משפטים כמו "set a 2 minute and 27 second timer" מאנגלית לצרפתית באמצעות Bing Translate, ואז להשתמש בכפתור **Listen translation** כדי לדבר את התרגום למיקרופון שלכם.
    >
    > ![כפתור השמעת התרגום ב-Bing Translate](../../../../../translated_images/he/bing-translate.348aa796d6efe2a9.webp)

1. הוסיפו את מפתח ה-API של שירות התרגום מתחת ל-`speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    החליפו `<key>` במפתח ה-API של משאב שירות התרגום שלכם.

1. מעל הפונקציה `say`, הגדירו פונקציה בשם `translate_text` שתתרגם טקסט משפת השרת לשפת המשתמש:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    השפות "מ-" ו-"אל" מועברות לפונקציה זו - האפליקציה שלכם צריכה להמיר משפת המשתמש לשפת השרת בעת זיהוי דיבור, ומשפת השרת לשפת המשתמש בעת מתן משוב מדובר.

1. בתוך הפונקציה, הגדירו את ה-URL והכותרות לקריאת ה-REST API:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    ה-URL של API זה אינו תלוי מיקום, במקום זאת המיקום מועבר ככותרת. מפתח ה-API משמש ישירות, כך שבניגוד לשירות הדיבור, אין צורך לקבל אסימון גישה מ-API מנפיק האסימונים.

1. מתחת לכך, הגדירו את הפרמטרים והגוף לקריאה:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` מגדיר את הפרמטרים שיש להעביר לקריאת ה-API, ומעביר את השפות "מ-" ו-"אל". קריאה זו תתרגם טקסט מהשפה "מ-" לשפה "אל".

    `body` מכיל את הטקסט לתרגום. זהו מערך, מכיוון שניתן לתרגם מספר בלוקים של טקסט באותה קריאה.

1. בצעו את קריאת ה-REST API, וקבלו את התגובה:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    התגובה שמתקבלת היא מערך JSON, עם פריט אחד שמכיל את התרגומים. פריט זה כולל מערך של תרגומים לכל הפריטים שהועברו בגוף הקריאה.

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

1. החזירו את המאפיין `text` מהתרגום הראשון מהפריט הראשון במערך:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. עדכנו את הלולאה `while True` כדי לתרגם את הטקסט מהקריאה ל-`convert_speech_to_text` משפת המשתמש לשפת השרת:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    קוד זה גם מדפיס את הגרסאות המקוריות והמתורגמות של הטקסט לקונסולה.

1. עדכנו את הפונקציה `say` כדי לתרגם את הטקסט שאומרים משפת השרת לשפת המשתמש:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    קוד זה גם מדפיס את הגרסאות המקוריות והמתורגמות של הטקסט לקונסולה.

1. הריצו את הקוד שלכם. ודאו שאפליקציית הפונקציות שלכם פועלת, ובקשו טיימר בשפת המשתמש, או על ידי דיבור בשפה זו בעצמכם, או באמצעות אפליקציית תרגום.

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

    > 💁 בשל הדרכים השונות לומר דברים בשפות שונות, ייתכן שתקבלו תרגומים השונים מעט מהדוגמאות שנתתם ל-LUIS. אם זה המקרה, הוסיפו עוד דוגמאות ל-LUIS, אימנו מחדש ואז פרסמו מחדש את המודל.

> 💁 ניתן למצוא את הקוד הזה בתיקיית [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi).

😀 תוכנית הטיימר הרב-לשונית שלכם הייתה הצלחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.