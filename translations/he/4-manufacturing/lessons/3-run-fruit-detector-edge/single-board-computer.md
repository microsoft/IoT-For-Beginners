<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-27T20:52:48+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "he"
}
-->
# סיווג תמונה באמצעות מסווג תמונות מבוסס IoT Edge - חומרה וירטואלית של IoT ו-Raspberry Pi

בחלק זה של השיעור, תשתמשו במסווג התמונות שפועל על מכשיר ה-IoT Edge.

## שימוש במסווג IoT Edge

ניתן להפנות את מכשיר ה-IoT לשימוש במסווג התמונות של IoT Edge. כתובת ה-URL של מסווג התמונות היא `http://<IP address or name>/image`, כאשר מחליפים את `<IP address or name>` בכתובת ה-IP או בשם המארח של המחשב שמריץ את IoT Edge.

ספריית ה-Python של Custom Vision עובדת רק עם מודלים שמתארחים בענן, ולא עם מודלים שמתארחים על IoT Edge. משמעות הדבר היא שתצטרכו להשתמש ב-REST API כדי לקרוא למסווג.

### משימה - שימוש במסווג IoT Edge

1. פתחו את פרויקט `fruit-quality-detector` ב-VS Code אם הוא עדיין לא פתוח. אם אתם משתמשים במכשיר IoT וירטואלי, ודאו שהסביבה הווירטואלית מופעלת.

1. פתחו את הקובץ `app.py`, והסירו את פקודות הייבוא מ-`azure.cognitiveservices.vision.customvision.prediction` ו-`msrest.authentication`.

1. הוסיפו את פקודת הייבוא הבאה בראש הקובץ:

    ```python
    import requests
    ```

1. מחקו את כל הקוד לאחר שהתמונה נשמרת לקובץ, החל מ-`image_file.write(image.read())` ועד סוף הקובץ.

1. הוסיפו את הקוד הבא לסוף הקובץ:

    ```python
    prediction_url = '<URL>'
    headers = {
        'Content-Type' : 'application/octet-stream'
    }
    image.seek(0)
    response = requests.post(prediction_url, headers=headers, data=image)
    results = response.json()
    
    for prediction in results['predictions']:
        print(f'{prediction["tagName"]}:\t{prediction["probability"] * 100:.2f}%')
    ```

    החליפו את `<URL>` בכתובת ה-URL של המסווג שלכם.

    קוד זה מבצע בקשת REST POST למסווג, ושולח את התמונה כגוף הבקשה. התוצאות חוזרות בפורמט JSON, והן מפוענחות כדי להציג את ההסתברויות.

1. הריצו את הקוד שלכם, כאשר המצלמה מכוונת לעבר פרי כלשהו, או סט תמונות מתאים, או פרי שנראה במצלמת הרשת שלכם אם אתם משתמשים בחומרת IoT וירטואלית. תראו את הפלט בקונסול:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 תוכלו למצוא את הקוד הזה בתיקיית [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) או [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device).

😀 תוכנית מסווג איכות הפירות שלכם הצליחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס AI [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. אנו לא נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.