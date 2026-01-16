<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4db8a3879a53490513571df2f6cf7641",
  "translation_date": "2025-08-27T21:53:40+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-actuator.md",
  "language_code": "he"
}
-->
# בנה מנורת לילה - Raspberry Pi

בחלק זה של השיעור, תוסיף נורת LED ל-Raspberry Pi שלך ותשתמש בה כדי ליצור מנורת לילה.

## חומרה

מנורת הלילה זקוקה כעת למפעיל.

המפעיל הוא **LED**, [דיודה פולטת אור](https://wikipedia.org/wiki/Light-emitting_diode) שפולטת אור כאשר זרם עובר דרכה. זהו מפעיל דיגיטלי שיש לו שני מצבים: דלוק וכבוי. שליחת ערך של 1 מדליקה את ה-LED, ו-0 מכבה אותו. ה-LED הוא מפעיל חיצוני מסוג Grove ויש לחבר אותו לכובע הבסיס של Grove על ה-Raspberry Pi.

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

![נורת LED מסוג Grove](../../../../../translated_images/he/grove-led.6c853be93f473cf2c439cfc74bb1064732b22251a83cedf66e62f783f9cc1a79.png)

1. בחר את ה-LED המועדף עליך והכנס את הרגליים לשני החורים שבמודול ה-LED.

    נורות LED הן דיודות פולטות אור, ודיודות הן רכיבים אלקטרוניים שיכולים להעביר זרם רק בכיוון אחד. משמעות הדבר היא שה-LED חייב להיות מחובר בכיוון הנכון, אחרת הוא לא יעבוד.

    אחת מהרגליים של ה-LED היא הפין החיובי, והשנייה היא הפין השלילי. ה-LED אינו עגול לחלוטין ויש לו צד שטוח מעט. הצד השטוח מעט הוא הפין השלילי. כאשר אתה מחבר את ה-LED למודול, ודא שהפין בצד המעוגל מחובר לשקע המסומן **+** בצד החיצוני של המודול, והצד השטוח מחובר לשקע הקרוב יותר למרכז המודול.

1. למודול ה-LED יש כפתור סיבוב שמאפשר לך לשלוט בעוצמת האור. סובב אותו עד הסוף בהתחלה על ידי סיבוב נגד כיוון השעון עד כמה שניתן באמצעות מברג קטן מסוג פיליפס.

1. הכנס קצה אחד של כבל Grove לשקע שבמודול ה-LED. הוא ייכנס רק בכיוון אחד.

1. כאשר ה-Raspberry Pi כבוי, חבר את הקצה השני של כבל Grove לשקע הדיגיטלי המסומן **D5** על כובע הבסיס של Grove שמחובר ל-Pi. שקע זה הוא השני משמאל, בשורה של השקעים ליד פיני GPIO.

![ה-LED של Grove מחובר לשקע D5](../../../../../translated_images/he/pi-led.97f1d474981dc35d1c7996c7b17de355d3d0a6bc9606d79fa5f89df933415122.png)

## תכנת את מנורת הלילה

כעת ניתן לתכנת את מנורת הלילה באמצעות חיישן האור של Grove וה-LED של Grove.

### משימה - תכנת את מנורת הלילה

תכנת את מנורת הלילה.

1. הפעל את ה-Pi והמתן עד שיסיים את תהליך האתחול.

1. פתח את פרויקט מנורת הלילה ב-VS Code שיצרת בחלק הקודם של המשימה, או ישירות על ה-Pi או באמצעות הרחבת Remote SSH.

1. הוסף את הקוד הבא לקובץ `app.py` כדי לייבא ספרייה נדרשת. יש להוסיף זאת למעלה, מתחת לשורות ה-`import` האחרות.

    ```python
    from grove.grove_led import GroveLed
    ```

    השורה `from grove.grove_led import GroveLed` מייבאת את `GroveLed` מספריות ה-Python של Grove. ספרייה זו מכילה קוד לתקשורת עם נורת LED מסוג Grove.

1. הוסף את הקוד הבא אחרי ההצהרה על `light_sensor` כדי ליצור מופע של המחלקה שמנהלת את ה-LED:

    ```python
    led = GroveLed(5)
    ```

    השורה `led = GroveLed(5)` יוצרת מופע של מחלקת `GroveLed` שמתחברת לפין **D5** - הפין הדיגיטלי של Grove שאליו מחובר ה-LED.

    > 💁 לכל השקעים יש מספרי פינים ייחודיים. פינים 0, 2, 4, ו-6 הם פינים אנלוגיים, ופינים 5, 16, 18, 22, 24, ו-26 הם פינים דיגיטליים.

1. הוסף בדיקה בתוך הלולאה `while`, ולפני ה-`time.sleep`, כדי לבדוק את רמות האור ולהדליק או לכבות את ה-LED:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    קוד זה בודק את הערך של `light`. אם הערך קטן מ-300, הוא קורא לשיטת `on` של מחלקת `GroveLed`, ששולחת ערך דיגיטלי של 1 ל-LED ומדליקה אותו. אם ערך האור גדול או שווה ל-300, הוא קורא לשיטת `off`, ששולחת ערך דיגיטלי של 0 ל-LED ומכבה אותו.

    > 💁 קוד זה צריך להיות מוזח לאותה רמה כמו השורה `print('Light level:', light)` כדי להיות בתוך הלולאה while!

    > 💁 כאשר שולחים ערכים דיגיטליים למפעילים, ערך 0 הוא 0V, וערך 1 הוא המתח המרבי של המכשיר. עבור ה-Raspberry Pi עם חיישנים ומפעילים מסוג Grove, המתח של ערך 1 הוא 3.3V.

1. מתוך הטרמינל של VS Code, הרץ את הפקודה הבאה כדי להפעיל את אפליקציית ה-Python שלך:

    ```sh
    python3 app.py
    ```

    ערכי האור יופיעו בקונסולה.

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

1. כסה וחשוף את חיישן האור. שים לב כיצד ה-LED נדלק אם רמת האור היא 300 או פחות, ונכבה כאשר רמת האור גדולה מ-300.

    > 💁 אם ה-LED לא נדלק, ודא שהוא מחובר בכיוון הנכון וכפתור הסיבוב מוגדר לעוצמה מלאה.

![ה-LED מחובר ל-Pi נדלק ונכבה כאשר רמת האור משתנה](../../../../../images/pi-running-assignment-1-1.gif)

> 💁 תוכל למצוא את הקוד הזה בתיקיית [code-actuator/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/pi).

😀 תוכנית מנורת הלילה שלך הצליחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.