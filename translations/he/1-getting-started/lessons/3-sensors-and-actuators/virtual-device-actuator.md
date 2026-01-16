<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c640f93263fd9adbfda920739e09feb",
  "translation_date": "2025-08-27T21:55:17+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-actuator.md",
  "language_code": "he"
}
-->
# בנה מנורת לילה - חומרה וירטואלית לאינטרנט של הדברים (IoT)

בחלק זה של השיעור, תוסיף נורית LED למכשיר ה-IoT הווירטואלי שלך ותשתמש בה כדי ליצור מנורת לילה.

## חומרה וירטואלית

מנורת הלילה זקוקה לאקטואטור אחד, שנוצר באפליקציית CounterFit.

האקטואטור הוא **LED**. במכשיר IoT פיזי, זו תהיה [דיודה פולטת אור](https://wikipedia.org/wiki/Light-emitting_diode) שפולטת אור כאשר זרם עובר דרכה. זהו אקטואטור דיגיטלי שיש לו שני מצבים: דלוק וכבוי. שליחת ערך של 1 מדליקה את ה-LED, ו-0 מכבה אותו.

הלוגיקה של מנורת הלילה בקוד פסאודו היא:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### הוסף את האקטואטור ל-CounterFit

כדי להשתמש ב-LED וירטואלי, עליך להוסיף אותו לאפליקציית CounterFit.

#### משימה - הוסף את האקטואטור ל-CounterFit

הוסף את ה-LED לאפליקציית CounterFit.

1. ודא שאפליקציית הווב של CounterFit פועלת מהחלק הקודם של המשימה. אם לא, הפעל אותה והוסף מחדש את חיישן האור.

1. צור LED:

    1. בתיבה *Create actuator* בלשונית *Actuator*, פתח את תיבת הבחירה *Actuator type* ובחר *LED*.

    1. הגדר את *Pin* ל-*5*.

    1. בחר בכפתור **Add** כדי ליצור את ה-LED על Pin 5.

    ![הגדרות ה-LED](../../../../../translated_images/he/counterfit-create-led.ba9db1c9b8c622a635d6dfae5cdc4e70c2b250635bd4f0601c6cf0bd22b7ba46.png)

    ה-LED ייווצר ויופיע ברשימת האקטואטורים.

    ![ה-LED נוצר](../../../../../translated_images/he/counterfit-led.c0ab02de6d256ad84d9bad4d67a7faa709f0ea83e410cfe9b5561ef0cef30b1c.png)

    לאחר שה-LED נוצר, תוכל לשנות את הצבע באמצעות בוחר הצבעים *Color*. בחר בכפתור **Set** כדי לשנות את הצבע לאחר שבחרת אותו.

### תכנת את מנורת הלילה

כעת ניתן לתכנת את מנורת הלילה באמצעות חיישן האור וה-LED של CounterFit.

#### משימה - תכנת את מנורת הלילה

תכנת את מנורת הלילה.

1. פתח את פרויקט מנורת הלילה ב-VS Code שיצרת בחלק הקודם של המשימה. סגור ופתח מחדש את הטרמינל כדי לוודא שהוא פועל באמצעות הסביבה הווירטואלית אם יש צורך.

1. פתח את הקובץ `app.py`.

1. הוסף את הקוד הבא לקובץ `app.py` כדי לייבא ספרייה נדרשת. יש להוסיף זאת בראש הקובץ, מתחת לשורות הייבוא האחרות.

    ```python
    from counterfit_shims_grove.grove_led import GroveLed
    ```

    השורה `from counterfit_shims_grove.grove_led import GroveLed` מייבאת את `GroveLed` מספריות ה-Python של CounterFit Grove shim. ספרייה זו מכילה קוד לתקשורת עם LED שנוצר באפליקציית CounterFit.

1. הוסף את הקוד הבא לאחר ההצהרה של `light_sensor` כדי ליצור מופע של המחלקה שמנהלת את ה-LED:

    ```python
    led = GroveLed(5)
    ```

    השורה `led = GroveLed(5)` יוצרת מופע של מחלקת `GroveLed` שמתחברת ל-Pin **5** - ה-Pin של CounterFit Grove שאליו מחובר ה-LED.

1. הוסף בדיקה בתוך הלולאה `while`, ולפני `time.sleep`, כדי לבדוק את רמות האור ולהדליק או לכבות את ה-LED:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    קוד זה בודק את הערך של `light`. אם הערך קטן מ-300, הוא קורא לשיטת `on` של מחלקת `GroveLed`, ששולחת ערך דיגיטלי של 1 ל-LED ומדליקה אותו. אם הערך של האור גדול או שווה ל-300, הוא קורא לשיטת `off`, ששולחת ערך דיגיטלי של 0 ל-LED ומכבה אותו.

    > 💁 קוד זה צריך להיות מוזח לאותה רמה כמו השורה `print('Light level:', light)` כדי להיות בתוך הלולאה `while`!

1. מהטרמינל של VS Code, הרץ את הפקודה הבאה כדי להפעיל את אפליקציית ה-Python שלך:

    ```sh
    python3 app.py
    ```

    ערכי האור יופיעו בקונסול.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

1. שנה את ההגדרות של *Value* או *Random* כדי לשנות את רמת האור מעל ומתחת ל-300. ה-LED יידלק וייכבה.

![ה-LED באפליקציית CounterFit נדלק ונכבה כאשר רמת האור משתנה](../../../../../images/virtual-device-running-assignment-1-1.gif)

> 💁 תוכל למצוא את הקוד הזה בתיקיית [code-actuator/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/virtual-device).

😀 תוכנית מנורת הלילה שלך הצליחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.