<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "db44083b4dc6fb06eac83c4f16448940",
  "translation_date": "2025-08-27T21:54:27+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-actuator.md",
  "language_code": "he"
}
-->
# בנה מנורת לילה - Wio Terminal

בחלק זה של השיעור, תוסיף נורת LED ל-Wio Terminal שלך ותשתמש בה כדי ליצור מנורת לילה.

## חומרה

מנורת הלילה זקוקה כעת למפעיל.

המפעיל הוא **LED**, [דיודה פולטת אור](https://wikipedia.org/wiki/Light-emitting_diode) שפולטת אור כאשר זרם עובר דרכה. זהו מפעיל דיגיטלי שיש לו שני מצבים: דלוק וכבוי. שליחת ערך של 1 מדליקה את ה-LED, ו-0 מכבה אותו. זהו מפעיל Grove חיצוני ויש לחבר אותו ל-Wio Terminal.

הלוגיקה של מנורת הלילה בקוד פסאודו היא:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### חבר את ה-LED

ה-LED של Grove מגיע כמודול עם מבחר נורות LED, שמאפשר לך לבחור את הצבע.

#### משימה - חבר את ה-LED

חבר את ה-LED.

![נורת Grove LED](../../../../../translated_images/he/grove-led.6c853be93f473cf2c439cfc74bb1064732b22251a83cedf66e62f783f9cc1a79.png)

1. בחר את ה-LED המועדף עליך והכנס את הרגליים לשני החורים במודול ה-LED.

    נורות LED הן דיודות פולטות אור, ודיודות הן רכיבים אלקטרוניים שיכולים להעביר זרם רק בכיוון אחד. משמעות הדבר היא שה-LED חייב להיות מחובר בכיוון הנכון, אחרת הוא לא יעבוד.

    אחת מהרגליים של ה-LED היא הפין החיובי, והשנייה היא הפין השלילי. ה-LED אינו עגול לחלוטין ויש לו צד שטוח מעט. הצד השטוח מעט הוא הפין השלילי. כאשר אתה מחבר את ה-LED למודול, ודא שהפין בצד המעוגל מחובר לשקע המסומן **+** בצד החיצוני של המודול, והצד השטוח מחובר לשקע הקרוב יותר למרכז המודול.

1. למודול ה-LED יש כפתור סיבוב שמאפשר לך לשלוט על הבהירות. סובב אותו עד הסוף בהתחלה על ידי סיבוב נגד כיוון השעון ככל האפשר באמצעות מברג קטן מסוג פיליפס.

1. הכנס קצה אחד של כבל Grove לשקע במודול ה-LED. הוא ייכנס רק בכיוון אחד.

1. כאשר ה-Wio Terminal מנותק מהמחשב או ממקור כוח אחר, חבר את הקצה השני של כבל Grove לשקע הימני של Grove ב-Wio Terminal כפי שאתה רואה את המסך. זהו השקע הרחוק ביותר מכפתור ההפעלה.

    > 💁 השקע הימני של Grove יכול לשמש עם חיישנים ומפעילים אנלוגיים או דיגיטליים. השקע השמאלי מיועד לחיישנים ומפעילים דיגיטליים בלבד. C יכוסה בשיעור מאוחר יותר.

![ה-LED של Grove מחובר לשקע הימני](../../../../../translated_images/he/wio-led.265a1897e72d7f21.webp)

## תכנת את מנורת הלילה

כעת ניתן לתכנת את מנורת הלילה באמצעות חיישן האור המובנה וה-LED של Grove.

### משימה - תכנת את מנורת הלילה

תכנת את מנורת הלילה.

1. פתח את פרויקט מנורת הלילה ב-VS Code שיצרת בחלק הקודם של המשימה.

1. הוסף את השורה הבאה לתחתית פונקציית `setup`:

    ```cpp
    pinMode(D0, OUTPUT);
    ```

    שורה זו מגדירה את הפין המשמש לתקשורת עם ה-LED דרך שקע Grove.

    הפין `D0` הוא הפין הדיגיטלי עבור שקע Grove הימני. פין זה מוגדר כ-`OUTPUT`, כלומר הוא מתחבר למפעיל ונתונים ייכתבו לפין.

1. הוסף את הקוד הבא מיד לפני ה-`delay` בפונקציית הלולאה:

    ```cpp
    if (light < 300)
    {
        digitalWrite(D0, HIGH);
    }
    else
    {
        digitalWrite(D0, LOW);
    }
    ```

    קוד זה בודק את ערך ה-`light`. אם הוא קטן מ-300, הוא שולח ערך `HIGH` לפין הדיגיטלי `D0`. ערך `HIGH` הוא ערך של 1, שמדליק את ה-LED. אם האור גדול או שווה ל-300, ערך `LOW` של 0 נשלח לפין, שמכבה את ה-LED.

    > 💁 כאשר שולחים ערכים דיגיטליים למפעילים, ערך LOW הוא 0v, וערך HIGH הוא המתח המרבי עבור המכשיר. עבור ה-Wio Terminal, מתח HIGH הוא 3.3V.

1. חבר מחדש את ה-Wio Terminal למחשב שלך, והעלה את הקוד החדש כפי שעשית קודם.

1. חבר את Serial Monitor. ערכי האור יופיעו בטרמינל.

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

1. כסה וחשוף את חיישן האור. שים לב כיצד ה-LED נדלק אם רמת האור היא 300 או פחות, ונכבה כאשר רמת האור גבוהה מ-300.

![ה-LED המחובר ל-WIO נדלק ונכבה כאשר רמת האור משתנה](../../../../../images/wio-running-assignment-1-1.gif)

> 💁 תוכל למצוא את הקוד הזה בתיקיית [code-actuator/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/wio-terminal).

😀 תוכנית מנורת הלילה שלך הצליחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.