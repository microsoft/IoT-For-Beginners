<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7f4ad0ef54f248b85b92187c94cf9dcb",
  "translation_date": "2025-08-27T21:56:52+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-sensor.md",
  "language_code": "he"
}
-->
# הוספת חיישן - Wio Terminal

בחלק זה של השיעור, תשתמשו בחיישן האור המובנה ב-Wio Terminal.

## חומרה

החיישן לשיעור זה הוא **חיישן אור** שמשתמש ב-[פוטודיודה](https://wikipedia.org/wiki/Photodiode) כדי להמיר אור לאות חשמלי. זהו חיישן אנלוגי ששולח ערך שלם בין 0 ל-1,023 שמציין כמות יחסית של אור, אך אינו תואם לשום יחידת מידה סטנדרטית כמו [לוקס](https://wikipedia.org/wiki/Lux).

חיישן האור מובנה בתוך ה-Wio Terminal וניתן לראותו דרך החלון השקוף בגב המכשיר.

![חיישן האור בגב ה-Wio Terminal](../../../../../translated_images/he/wio-light-sensor.b1f529f3c95f5165.png)

## תכנות חיישן האור

כעת ניתן לתכנת את המכשיר לשימוש בחיישן האור המובנה.

### משימה

תכנתו את המכשיר.

1. פתחו את פרויקט ה-nightlight ב-VS Code שיצרתם בחלק הקודם של המשימה.

1. הוסיפו את השורה הבאה לתחתית הפונקציה `setup`:

    ```cpp
    pinMode(WIO_LIGHT, INPUT);
    ```

    שורה זו מגדירה את הפינים המשמשים לתקשורת עם חומרת החיישן.

    הפין `WIO_LIGHT` הוא מספר הפין של GPIO שמחובר לחיישן האור המובנה. פין זה מוגדר כ-`INPUT`, כלומר הוא מתחבר לחיישן ונתונים ייקראו ממנו.

1. מחקו את התוכן של הפונקציה `loop`.

1. הוסיפו את הקוד הבא לפונקציה `loop` הריקה כעת.

    ```cpp
    int light = analogRead(WIO_LIGHT);
    Serial.print("Light value: ");
    Serial.println(light);
    ```

    קוד זה קורא ערך אנלוגי מהפין `WIO_LIGHT`. הוא קורא ערך בין 0 ל-1,023 מחיישן האור המובנה. ערך זה נשלח לאחר מכן לפורט הסריאלי כך שתוכלו לקרוא אותו ב-Serial Monitor כשהקוד הזה פועל. `Serial.print` כותב את הטקסט ללא ירידת שורה בסוף, כך שכל שורה תתחיל ב-`Light value:` ותסתיים בערך האור בפועל.

1. הוסיפו השהיה קצרה של שנייה אחת (1,000ms) בסוף הפונקציה `loop`, מכיוון שאין צורך לבדוק את רמות האור באופן רציף. השהיה מפחיתה את צריכת החשמל של המכשיר.

    ```cpp
    delay(1000);
    ```

1. חברו מחדש את ה-Wio Terminal למחשב שלכם, והעלו את הקוד החדש כפי שעשיתם קודם.

1. התחברו ל-Serial Monitor. ערכי האור יופיעו בטרמינל. כסו וחשפו את חיישן האור בגב ה-Wio Terminal, ותראו שהערכים משתנים.

    ```output
    > Executing task: platformio device monitor <

    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Light value: 4
    Light value: 5
    Light value: 4
    Light value: 158
    Light value: 343
    Light value: 348
    Light value: 344
    ```

> 💁 ניתן למצוא את הקוד הזה בתיקייה [code-sensor/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/wio-terminal).

😀 הוספת חיישן לתוכנית ה-nightlight שלכם הייתה הצלחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). בעוד שאנו שואפים לדיוק, יש להיות מודעים לכך שתרגומים אוטומטיים עשויים להכיל שגיאות או אי-דיוקים. המסמך המקורי בשפתו המקורית נחשב למקור הסמכותי. למידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי מתרגם אנושי. איננו נושאים באחריות לכל אי-הבנה או פרשנות שגויה הנובעת משימוש בתרגום זה.