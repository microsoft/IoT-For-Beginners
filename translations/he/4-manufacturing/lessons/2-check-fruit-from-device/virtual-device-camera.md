<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ba7150ffc4a6999f6c3cfb4906ec7df",
  "translation_date": "2025-08-27T20:44:23+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/virtual-device-camera.md",
  "language_code": "he"
}
-->
# לכידת תמונה - חומרה וירטואלית לאינטרנט של הדברים (IoT)

בחלק זה של השיעור, תוסיפו חיישן מצלמה למכשיר ה-IoT הווירטואלי שלכם, ותקראו תמונות ממנו.

## חומרה

מכשיר ה-IoT הווירטואלי ישתמש במצלמה מדומה ששולחת תמונות מקבצים או מהמצלמה שלכם.

### הוספת מצלמה ל-CounterFit

כדי להשתמש במצלמה וירטואלית, עליכם להוסיף אחת לאפליקציית CounterFit.

#### משימה - הוספת מצלמה ל-CounterFit

הוסיפו מצלמה לאפליקציית CounterFit.

1. צרו אפליקציית Python חדשה במחשב שלכם בתיקייה בשם `fruit-quality-detector` עם קובץ יחיד בשם `app.py` וסביבת עבודה וירטואלית של Python, והוסיפו את חבילות ה-Pip של CounterFit.

    > ⚠️ ניתן לעיין [בהוראות ליצירה והגדרה של פרויקט Python ב-CounterFit בשיעור הראשון אם יש צורך](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. התקינו חבילת Pip נוספת כדי להוסיף CounterFit shim שיכול לתקשר עם חיישני מצלמה על ידי סימולציה של חלק מחבילת [Picamera Pip](https://pypi.org/project/picamera/). ודאו שאתם מתקינים זאת מתוך טרמינל עם סביבת העבודה הווירטואלית מופעלת.

    ```sh
    pip install counterfit-shims-picamera
    ```

1. ודאו שאפליקציית ה-Web של CounterFit פועלת.

1. צרו מצלמה:

    1. בתיבה *Create sensor* בלשונית *Sensors*, פתחו את תיבת *Sensor type* ובחרו *Camera*.

    1. הגדירו את *Name* ל-`Picamera`.

    1. בחרו בכפתור **Add** כדי ליצור את המצלמה.

    ![הגדרות המצלמה](../../../../../translated_images/he/counterfit-create-camera.a5de97f59c0bd3cbe0416d7e89a3cfe86d19fbae05c641c53a91286412af0a34.png)

    המצלמה תיווצר ותופיע ברשימת החיישנים.

    ![המצלמה שנוצרה](../../../../../translated_images/he/counterfit-camera.001ec52194c8ee5d3f617173da2c79e1df903d10882adc625cbfc493525125d4.png)

## תכנות המצלמה

כעת ניתן לתכנת את מכשיר ה-IoT הווירטואלי להשתמש במצלמה הווירטואלית.

### משימה - תכנות המצלמה

תכנתו את המכשיר.

1. ודאו שאפליקציית `fruit-quality-detector` פתוחה ב-VS Code.

1. פתחו את קובץ `app.py`.

1. הוסיפו את הקוד הבא לראש הקובץ `app.py` כדי לחבר את האפליקציה ל-CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. הוסיפו את הקוד הבא לקובץ `app.py` שלכם:

    ```python
    import io
    from counterfit_shims_picamera import PiCamera
    ```

    קוד זה מייבא כמה ספריות נחוצות, כולל המחלקה `PiCamera` מתוך הספרייה counterfit_shims_picamera.

1. הוסיפו את הקוד הבא מתחת לזה כדי לאתחל את המצלמה:

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    ```

    קוד זה יוצר אובייקט PiCamera, מגדיר את הרזולוציה ל-640x480. למרות שרזולוציות גבוהות יותר נתמכות, מסווג התמונות עובד על תמונות קטנות בהרבה (227x227), ולכן אין צורך ללכוד ולשלוח תמונות גדולות יותר.

    השורה `camera.rotation = 0` מגדירה את סיבוב התמונה במעלות. אם יש צורך לסובב את התמונה מהמצלמה או מהקובץ, הגדירו זאת בהתאם. לדוגמה, אם תרצו לשנות תמונה של בננה במצב נוף למצב פורטרט, הגדירו `camera.rotation = 90`.

1. הוסיפו את הקוד הבא מתחת לזה כדי ללכוד את התמונה כנתונים בינאריים:

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    קוד זה יוצר אובייקט `BytesIO` לאחסון נתונים בינאריים. התמונה נקראת מהמצלמה כקובץ JPEG ונשמרת באובייקט זה. לאובייקט זה יש אינדיקטור מיקום כדי לדעת היכן הוא נמצא בנתונים כך שניתן לכתוב עוד נתונים בסוף אם יש צורך, ולכן השורה `image.seek(0)` מחזירה את המיקום להתחלה כך שכל הנתונים יוכלו להיקרא מאוחר יותר.

1. מתחת לזה, הוסיפו את הקוד הבא כדי לשמור את התמונה בקובץ:

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    קוד זה פותח קובץ בשם `image.jpg` לכתיבה, ואז קורא את כל הנתונים מתוך אובייקט `BytesIO` וכותב אותם לקובץ.

    > 💁 ניתן ללכוד את התמונה ישירות לקובץ במקום לאובייקט `BytesIO` על ידי העברת שם הקובץ לקריאה של `camera.capture`. הסיבה לשימוש באובייקט `BytesIO` היא כדי שבשלב מאוחר יותר בשיעור תוכלו לשלוח את התמונה למסווג התמונות שלכם.

1. הגדירו את התמונה שהמצלמה ב-CounterFit תצלם. תוכלו להגדיר את *Source* ל-*File*, ואז להעלות קובץ תמונה, או להגדיר את *Source* ל-*WebCam*, ותמונות יילכדו מהמצלמה שלכם. ודאו שאתם לוחצים על כפתור **Set** לאחר בחירת תמונה או בחירת המצלמה.

    ![CounterFit עם קובץ מוגדר כמקור תמונה, ומצלמת רשת שמראה אדם מחזיק בננה בתצוגה מקדימה של המצלמה](../../../../../translated_images/he/counterfit-camera-options.eb3bd5150a8e7dffbf24bc5bcaba0cf2cdef95fbe6bbe393695d173817d6b8df.png)

1. תמונה תילכד ותישמר כ-`image.jpg` בתיקייה הנוכחית. תוכלו לראות את הקובץ הזה בסייר של VS Code. בחרו בקובץ כדי לצפות בתמונה. אם יש צורך בסיבוב, עדכנו את השורה `camera.rotation = 0` בהתאם וצילמו תמונה נוספת.

> 💁 תוכלו למצוא את הקוד הזה בתיקייה [code-camera/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/virtual-iot-device).

😀 תוכנית המצלמה שלכם הצליחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.