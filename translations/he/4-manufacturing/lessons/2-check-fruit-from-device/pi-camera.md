<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c677667095f6133eee418c7e53615d05",
  "translation_date": "2025-08-27T20:41:38+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/pi-camera.md",
  "language_code": "he"
}
-->
# לצלם תמונה - Raspberry Pi

בחלק זה של השיעור, תוסיפו חיישן מצלמה ל-Raspberry Pi שלכם ותצלמו תמונות באמצעותו.

## חומרה

ה-Raspberry Pi זקוק למצלמה.

המצלמה שתשתמשו בה היא [מודול מצלמה של Raspberry Pi](https://www.raspberrypi.org/products/camera-module-v2/). מצלמה זו תוכננה לעבוד עם ה-Raspberry Pi ומתחברת באמצעות מחבר ייעודי על הלוח.

> 💁 מצלמה זו משתמשת ב-[Camera Serial Interface, פרוטוקול של Mobile Industry Processor Interface Alliance](https://wikipedia.org/wiki/Camera_Serial_Interface), הידוע כ-MIPI-CSI. זהו פרוטוקול ייעודי לשליחת תמונות.

## חיבור המצלמה

ניתן לחבר את המצלמה ל-Raspberry Pi באמצעות כבל סרט.

### משימה - חיבור המצלמה

![מצלמת Raspberry Pi](../../../../../translated_images/he/pi-camera-module.4278753c31bd6e757aa2b858be97d72049f71616278cefe4fb5abb485b40a078.png)

1. כבו את ה-Pi.

1. חברו את כבל הסרט שמגיע עם המצלמה למצלמה. לשם כך, משכו בעדינות את הקליפס השחור במחזיק כך שייצא מעט, ואז החליקו את הכבל לתוך השקע, כאשר הצד הכחול פונה הרחק מהעדשה, והפסים המתכתיים פונים לכיוון העדשה. לאחר שהכבל נכנס עד הסוף, דחפו את הקליפס השחור חזרה למקומו.

    ניתן למצוא אנימציה שמראה כיצד לפתוח את הקליפס ולהכניס את הכבל בתיעוד [Raspberry Pi Getting Started with the Camera module](https://projects.raspberrypi.org/en/projects/getting-started-with-picamera/2).

    ![כבל הסרט מוכנס למודול המצלמה](../../../../../translated_images/he/pi-camera-ribbon-cable.0bf82acd251611c21ac616f082849413e2b322a261d0e4f8fec344248083b07e.png)

1. הסירו את ה-Grove Base Hat מה-Pi.

1. העבירו את כבל הסרט דרך החריץ למצלמה ב-Grove Base Hat. ודאו שהצד הכחול של הכבל פונה לכיוון הפורטים האנלוגיים המסומנים **A0**, **A1** וכו'.

    ![כבל הסרט עובר דרך ה-Grove Base Hat](../../../../../translated_images/he/grove-base-hat-ribbon-cable.501fed202fcf73b11b2b68f6d246189f7d15d3e4423c572ddee79d77b4632b47.png)

1. הכניסו את כבל הסרט לשקע המצלמה ב-Pi. שוב, משכו את הקליפס השחור למעלה, הכניסו את הכבל, ואז דחפו את הקליפס חזרה. הצד הכחול של הכבל צריך לפנות לכיוון פורטי ה-USB והאת'רנט.

    ![כבל הסרט מחובר לשקע המצלמה ב-Pi](../../../../../translated_images/he/pi-camera-socket-ribbon-cable.a18309920b11800911082ed7aa6fb28e6d9be3a022e4079ff990016cae3fca10.png)

1. החזירו את ה-Grove Base Hat למקומו.

## תכנות המצלמה

כעת ניתן לתכנת את ה-Raspberry Pi לשימוש במצלמה באמצעות ספריית Python בשם [PiCamera](https://pypi.org/project/picamera/).

### משימה - הפעלת מצב מצלמה ישן

לצערנו, עם שחרור מערכת ההפעלה Raspberry Pi OS Bullseye, תוכנת המצלמה שהגיעה עם המערכת השתנתה, ולכן כברירת מחדל PiCamera לא עובדת. ישנו תחליף בפיתוח, בשם PiCamera2, אך הוא עדיין לא מוכן לשימוש.

בינתיים, ניתן להגדיר את ה-Pi למצב מצלמה ישן כדי לאפשר ל-PiCamera לעבוד. שקע המצלמה גם מושבת כברירת מחדל, אך הפעלת תוכנת המצלמה הישנה תפעיל אותו אוטומטית.

1. הפעילו את ה-Pi והמתינו עד שיסיים את תהליך האתחול.

1. הפעילו את VS Code, או ישירות על ה-Pi, או באמצעות תוסף Remote SSH.

1. הריצו את הפקודות הבאות מהטרמינל:

    ```sh
    sudo raspi-config nonint do_legacy 0
    sudo reboot
    ```

    פקודות אלו יפעילו הגדרה שתאפשר את תוכנת המצלמה הישנה, ואז יאתחלו את ה-Pi כדי שההגדרה תיכנס לתוקף.

1. המתינו שה-Pi יאתחל מחדש, ואז הפעילו מחדש את VS Code.

### משימה - תכנות המצלמה

תכנתו את המכשיר.

1. מהטרמינל, צרו תיקייה חדשה בספריית הבית של המשתמש `pi` בשם `fruit-quality-detector`. צרו קובץ בתיקייה זו בשם `app.py`.

1. פתחו את התיקייה הזו ב-VS Code.

1. כדי לעבוד עם המצלמה, ניתן להשתמש בספריית Python בשם PiCamera. התקינו את חבילת ה-Pip שלה עם הפקודה הבאה:

    ```sh
    pip3 install picamera
    ```

1. הוסיפו את הקוד הבא לקובץ `app.py` שלכם:

    ```python
    import io
    import time
    from picamera import PiCamera
    ```

    קוד זה מייבא כמה ספריות נחוצות, כולל ספריית `PiCamera`.

1. הוסיפו את הקוד הבא מתחת לזה כדי לאתחל את המצלמה:

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    
    time.sleep(2)
    ```

    קוד זה יוצר אובייקט PiCamera, מגדיר את הרזולוציה ל-640x480. למרות שרזולוציות גבוהות יותר נתמכות (עד 3280x2464), מסווג התמונות עובד על תמונות קטנות בהרבה (227x227), ולכן אין צורך לצלם ולשלוח תמונות גדולות יותר.

    השורה `camera.rotation = 0` מגדירה את סיבוב התמונה. כבל הסרט נכנס לתחתית המצלמה, אך אם המצלמה שלכם סובבה כדי להקל על הצבעתה על האובייקט שברצונכם לסווג, תוכלו לשנות שורה זו למספר מעלות הסיבוב.

    ![המצלמה תלויה מעל פחית שתייה](../../../../../translated_images/he/pi-camera-upside-down.5376961ba31459883362124152ad6b823d5ac5fc14e85f317e22903bd681c2b6.png)

    לדוגמה, אם תתלו את כבל הסרט מעל משהו כך שהוא יהיה בחלק העליון של המצלמה, הגדירו את הסיבוב ל-180:

    ```python
    camera.rotation = 180
    ```

    המצלמה לוקחת כמה שניות כדי להתחיל לפעול, ולכן השימוש ב-`time.sleep(2)`.

1. הוסיפו את הקוד הבא מתחת לזה כדי לצלם את התמונה כנתונים בינאריים:

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    קוד זה יוצר אובייקט `BytesIO` לאחסון נתונים בינאריים. התמונה נקראת מהמצלמה כקובץ JPEG ונשמרת באובייקט זה. לאובייקט זה יש מצביע מיקום כדי לדעת היכן הוא נמצא בנתונים כך שניתן להוסיף נתונים נוספים בסוף אם צריך, ולכן השורה `image.seek(0)` מחזירה את המצביע להתחלה כדי שניתן יהיה לקרוא את כל הנתונים מאוחר יותר.

1. מתחת לזה, הוסיפו את הקוד הבא כדי לשמור את התמונה לקובץ:

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    קוד זה פותח קובץ בשם `image.jpg` לכתיבה, ואז קורא את כל הנתונים מאובייקט `BytesIO` וכותב אותם לקובץ.

    > 💁 ניתן לצלם את התמונה ישירות לקובץ במקום לאובייקט `BytesIO` על ידי העברת שם הקובץ לקריאה של `camera.capture`. הסיבה לשימוש באובייקט `BytesIO` היא כדי שבהמשך השיעור תוכלו לשלוח את התמונה למסווג התמונות שלכם.

1. כוונו את המצלמה למשהו והריצו את הקוד הזה.

1. תמונה תצולם ותישמר כ-`image.jpg` בתיקייה הנוכחית. תוכלו לראות קובץ זה בסייר של VS Code. בחרו את הקובץ כדי לצפות בתמונה. אם יש צורך בסיבוב, עדכנו את השורה `camera.rotation = 0` בהתאם וצילמו תמונה נוספת.

> 💁 תוכלו למצוא את הקוד הזה בתיקייה [code-camera/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/pi).

😀 תוכנית המצלמה שלכם הצליחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.