<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64ad4ddb4de81a18b7252e968f10b404",
  "translation_date": "2025-08-27T22:24:26+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/single-board-computer-set-timer.md",
  "language_code": "he"
}
-->
# הגדרת טיימר - חומרת IoT וירטואלית ו-Raspberry Pi

בחלק זה של השיעור, תשתמשו בקוד חסר השרת שלכם כדי להבין את הדיבור ולהגדיר טיימר במכשיר ה-IoT הווירטואלי או ב-Raspberry Pi שלכם בהתאם לתוצאות.

## הגדרת טיימר

הטקסט שמתקבל מהקריאה של דיבור לטקסט צריך להישלח לקוד חסר השרת שלכם כדי לעבור עיבוד על ידי LUIS, ולקבל בחזרה את מספר השניות עבור הטיימר. מספר השניות הזה ישמש להגדרת הטיימר.

ניתן להגדיר טיימרים באמצעות מחלקת `threading.Timer` של Python. מחלקה זו מקבלת זמן השהיה ופונקציה, ולאחר זמן ההשהיה, הפונקציה מתבצעת.

### משימה - שליחת הטקסט לפונקציה חסרת השרת

1. פתחו את פרויקט `smart-timer` ב-VS Code, וודאו שסביבת העבודה הווירטואלית נטענת בטרמינל אם אתם משתמשים במכשיר IoT וירטואלי.

1. מעל הפונקציה `process_text`, הכריזו על פונקציה בשם `get_timer_time` שתבצע קריאה לנקודת הקצה של ה-REST שיצרתם:

    ```python
    def get_timer_time(text):
    ```

1. הוסיפו את הקוד הבא לפונקציה זו כדי להגדיר את ה-URL לקריאה:

    ```python
    url = '<URL>'
    ```

    החליפו `<URL>` בכתובת ה-URL של נקודת הקצה שלכם שיצרתם בשיעור הקודם, בין אם במחשב שלכם או בענן.

1. הוסיפו את הקוד הבא כדי להגדיר את הטקסט כמאפיין שעובר כ-JSON לקריאה:

    ```python
    body = {
        'text': text
    }
    
    response = requests.post(url, json=body)
    ```

1. מתחת לזה, שלפו את ה-`seconds` ממטען התגובה, והחזירו 0 אם הקריאה נכשלה:

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```

    קריאות HTTP מוצלחות מחזירות קוד סטטוס בטווח 200, והקוד חסר השרת שלכם מחזיר 200 אם הטקסט עובד וזוהה ככוונת הגדרת טיימר.

### משימה - הגדרת טיימר בתהליך רקע

1. הוסיפו את משפט הייבוא הבא בראש הקובץ כדי לייבא את ספריית ה-threading של Python:

    ```python
    import threading
    ```

1. מעל הפונקציה `process_text`, הוסיפו פונקציה שתדבר תגובה. כרגע היא רק תכתוב לקונסול, אך בהמשך השיעור היא תדבר את הטקסט.

    ```python
    def say(text):
        print(text)
    ```

1. מתחת לזה, הוסיפו פונקציה שתיקרא על ידי טיימר כדי להודיע שהטיימר הסתיים:

    ```python
    def announce_timer(minutes, seconds):
        announcement = 'Times up on your '
        if minutes > 0:
            announcement += f'{minutes} minute '
        if seconds > 0:
            announcement += f'{seconds} second '
        announcement += 'timer.'
        say(announcement)
    ```

    פונקציה זו מקבלת את מספר הדקות והשניות עבור הטיימר, ובונה משפט שאומר שהטיימר הסתיים. היא תבדוק את מספר הדקות והשניות, ותכלול כל יחידת זמן רק אם יש לה ערך. לדוגמה, אם מספר הדקות הוא 0, רק השניות ייכללו בהודעה. משפט זה נשלח לאחר מכן לפונקציה `say`.

1. מתחת לזה, הוסיפו את הפונקציה `create_timer` הבאה כדי ליצור טיימר:

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

    פונקציה זו מקבלת את המספר הכולל של השניות עבור הטיימר שישלח בפקודה, וממירה אותו לדקות ושניות. לאחר מכן היא יוצרת ומפעילה אובייקט טיימר באמצעות המספר הכולל של השניות, ומעבירה את הפונקציה `announce_timer` ורשימה המכילה את הדקות והשניות. כאשר הטיימר פג, הוא יקרא לפונקציה `announce_timer`, ויעביר את תוכן הרשימה הזו כפרמטרים - כך שהפריט הראשון ברשימה יעבור כפרמטר `minutes`, והפריט השני כפרמטר `seconds`.

1. לסוף הפונקציה `create_timer`, הוסיפו קוד לבניית הודעה שתיאמר למשתמש להודיע שהטיימר מתחיל:

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

    שוב, זה כולל רק את יחידת הזמן שיש לה ערך. משפט זה נשלח לאחר מכן לפונקציה `say`.

1. הוסיפו את הדברים הבאים לסוף הפונקציה `process_text` כדי לקבל את הזמן עבור הטיימר מהטקסט, ואז ליצור את הטיימר:

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

    הטיימר ייווצר רק אם מספר השניות גדול מ-0.

1. הפעילו את האפליקציה, וודאו שאפליקציית הפונקציה פועלת גם היא. הגדירו כמה טיימרים, והפלט יראה שהטיימר מוגדר, ולאחר מכן יראה כשהוא פג:

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 ניתן למצוא את הקוד הזה בתיקיות [code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi) או [code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device).

😀 תוכנית הטיימר שלכם הייתה הצלחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור הסמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.