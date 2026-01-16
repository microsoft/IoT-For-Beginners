<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e5896207b304ce1abaf065b8acc0cc79",
  "translation_date": "2025-08-27T20:42:31+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/single-board-computer-classify-image.md",
  "language_code": "he"
}
-->
# סיווג תמונה - חומרה וירטואלית של IoT ו-Raspberry Pi

בחלק זה של השיעור, תשלחו את התמונה שצולמה על ידי המצלמה לשירות Custom Vision כדי לסווג אותה.

## שליחת תמונות ל-Custom Vision

לשירות Custom Vision יש SDK של Python שניתן להשתמש בו לסיווג תמונות.

### משימה - שליחת תמונות ל-Custom Vision

1. פתחו את תיקיית `fruit-quality-detector` ב-VS Code. אם אתם משתמשים במכשיר IoT וירטואלי, ודאו שהסביבה הווירטואלית פועלת בטרמינל.

1. ה-SDK של Python לשליחת תמונות ל-Custom Vision זמין כחבילת Pip. התקינו אותו באמצעות הפקודה הבאה:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. הוסיפו את הצהרות הייבוא הבאות בראש קובץ `app.py`:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    זה מביא כמה מודולים מספריות Custom Vision, אחד לאימות עם מפתח התחזית, ואחד שמספק מחלקת לקוח תחזיות שיכולה לקרוא ל-Custom Vision.

1. הוסיפו את הקוד הבא לסוף הקובץ:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    החליפו את `<prediction_url>` בכתובת ה-URL שהעתקתם מדיאלוג *Prediction URL* מוקדם יותר בשיעור זה. החליפו את `<prediction key>` במפתח התחזית שהעתקתם מאותו דיאלוג.

1. כתובת ה-URL של התחזית שסופקה על ידי דיאלוג *Prediction URL* מיועדת לשימוש כאשר קוראים לנקודת הקצה של REST ישירות. ה-SDK של Python משתמש בחלקים שונים של ה-URL במקומות שונים. הוסיפו את הקוד הבא כדי לפרק את ה-URL לחלקים הנדרשים:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    זה מפרק את ה-URL, ומחלץ את נקודת הקצה `https://<location>.api.cognitive.microsoft.com`, את מזהה הפרויקט, ואת שם האיטרציה שפורסמה.

1. צרו אובייקט תחזית כדי לבצע את התחזית באמצעות הקוד הבא:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    `prediction_credentials` עוטף את מפתח התחזית. אלו משמשים לאחר מכן ליצירת אובייקט לקוח תחזיות שמצביע על נקודת הקצה.

1. שלחו את התמונה ל-Custom Vision באמצעות הקוד הבא:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    זה מחזיר את התמונה להתחלה, ואז שולח אותה ללקוח התחזיות.

1. לבסוף, הציגו את התוצאות באמצעות הקוד הבא:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    זה יעבור דרך כל התחזיות שהוחזרו ויציג אותן בטרמינל. ההסתברויות המוחזרות הן מספרים עשרוניים בין 0 ל-1, כאשר 0 מייצג סיכוי של 0% להתאמה לתג, ו-1 מייצג סיכוי של 100%.

    > 💁 מסווגי תמונות יחזירו את האחוזים עבור כל התגים שהיו בשימוש. לכל תג תהיה הסתברות שהתמונה תואמת לתג זה.

1. הריצו את הקוד שלכם, כאשר המצלמה מצביעה על פרי כלשהו, או על סט תמונות מתאים, או פרי שנראה במצלמת הרשת שלכם אם אתם משתמשים בחומרת IoT וירטואלית. תוכלו לראות את הפלט בקונסולה:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    תוכלו לראות את התמונה שצולמה, ואת הערכים הללו בלשונית **Predictions** ב-Custom Vision.

    ![בננה ב-Custom Vision שסווגה כבשלה ב-56.8% ולא בשלה ב-43.1%](../../../../../translated_images/he/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 תוכלו למצוא את הקוד הזה בתיקיית [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) או [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device).

😀 תוכנית סיווג איכות הפירות שלכם הייתה הצלחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.