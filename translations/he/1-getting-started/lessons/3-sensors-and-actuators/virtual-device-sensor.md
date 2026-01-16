<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "11f10c6760fb8202cf368422702fdf70",
  "translation_date": "2025-08-27T21:56:13+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-sensor.md",
  "language_code": "he"
}
-->
# בנה מנורת לילה - חומרה וירטואלית לאינטרנט של הדברים (IoT)

בחלק זה של השיעור, תוסיף חיישן אור למכשיר ה-IoT הווירטואלי שלך.

## חומרה וירטואלית

מנורת הלילה זקוקה לחיישן אחד, שנוצר באפליקציית CounterFit.

החיישן הוא **חיישן אור**. במכשיר IoT פיזי, זה היה [פוטודיודה](https://wikipedia.org/wiki/Photodiode) שממירה אור לאות חשמלי. חיישני אור הם חיישנים אנלוגיים ששולחים ערך מספרי של כמות האור היחסית, שאינה מתאימה ליחידת מדידה סטנדרטית כמו [לוקס](https://wikipedia.org/wiki/Lux).

### הוסף את החיישנים ל-CounterFit

כדי להשתמש בחיישן אור וירטואלי, עליך להוסיף אותו לאפליקציית CounterFit.

#### משימה - הוסף את החיישנים ל-CounterFit

הוסף את חיישן האור לאפליקציית CounterFit.

1. ודא שאפליקציית הווב של CounterFit פועלת מהחלק הקודם של המשימה. אם לא, הפעל אותה.

1. צור חיישן אור:

    1. בתיבה *Create sensor* בלשונית *Sensors*, פתח את תיבת הבחירה *Sensor type* ובחר *Light*.

    1. השאר את *Units* מוגדר ל-*NoUnits*.

    1. ודא שה-*Pin* מוגדר ל-*0*.

    1. לחץ על כפתור **Add** כדי ליצור את חיישן האור על Pin 0.

    ![הגדרות חיישן האור](../../../../../translated_images/he/counterfit-create-light-sensor.9f36a5e0d4458d8d554d54b34d2c806d56093d6e49fddcda2d20f6fef7f5cce1.png)

    חיישן האור ייווצר ויופיע ברשימת החיישנים.

    ![חיישן האור נוצר](../../../../../translated_images/he/counterfit-light-sensor.5d0f5584df56b90f6b2561910d9cb20dfbd73eeff2177c238d38f4de54aefae1.png)

## תכנת את חיישן האור

כעת ניתן לתכנת את המכשיר להשתמש בחיישן האור המובנה.

### משימה - תכנת את חיישן האור

תכנת את המכשיר.

1. פתח את פרויקט מנורת הלילה ב-VS Code שיצרת בחלק הקודם של המשימה. סגור ופתח מחדש את הטרמינל כדי לוודא שהוא פועל באמצעות הסביבה הווירטואלית אם יש צורך.

1. פתח את הקובץ `app.py`.

1. הוסף את הקוד הבא לראש הקובץ `app.py` יחד עם שאר הצהרות ה-`import` כדי לייבא ספריות נדרשות:

    ```python
    import time
    from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    הצהרת `import time` מייבאת את מודול ה-`time` של Python שישמש בהמשך המשימה.

    הצהרת `from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor` מייבאת את `GroveLightSensor` מספריות ה-Python של CounterFit Grove shim. ספרייה זו מכילה קוד לתקשורת עם חיישן אור שנוצר באפליקציית CounterFit.

1. הוסף את הקוד הבא לתחתית הקובץ כדי ליצור מופעים של מחלקות שמנהלות את חיישן האור:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    השורה `light_sensor = GroveLightSensor(0)` יוצרת מופע של מחלקת `GroveLightSensor` שמתחבר ל-Pin **0** - ה-Pin של CounterFit Grove שאליו מחובר חיישן האור.

1. הוסף לולאה אינסופית אחרי הקוד לעיל כדי לקרוא את ערך חיישן האור ולהדפיס אותו לקונסול:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    פעולה זו תקרא את רמת האור הנוכחית באמצעות המאפיין `light` של מחלקת `GroveLightSensor`. מאפיין זה קורא את הערך האנלוגי מה-Pin. ערך זה יודפס לקונסול.

1. הוסף השהיה קצרה של שנייה בסוף לולאת ה-`while`, מכיוון שאין צורך לבדוק את רמות האור באופן רציף. השהיה מפחיתה את צריכת החשמל של המכשיר.

    ```python
    time.sleep(1)
    ```

1. מהטרמינל של VS Code, הרץ את הפקודה הבאה כדי להפעיל את אפליקציית ה-Python שלך:

    ```sh
    python3 app.py
    ```

    ערכי האור יופיעו בקונסול. בתחילה ערך זה יהיה 0.

1. מאפליקציית CounterFit, שנה את ערך חיישן האור שייקרא על ידי האפליקציה. ניתן לעשות זאת בשתי דרכים:

    * הזן מספר בתיבה *Value* עבור חיישן האור, ואז לחץ על כפתור **Set**. המספר שתזין יהיה הערך שהחיישן יחזיר.

    * סמן את תיבת הסימון *Random*, והזן ערכי *Min* ו-*Max*, ואז לחץ על כפתור **Set**. בכל פעם שהחיישן יקרא ערך, הוא יקרא מספר אקראי בין *Min* ל-*Max*.

    הערכים שתגדיר יופיעו בקונסול. שנה את *Value* או את הגדרות *Random* כדי לשנות את הערך.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

> 💁 ניתן למצוא את הקוד הזה בתיקיית [code-sensor/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/virtual-device).

😀 תוכנית מנורת הלילה שלך הצליחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. אנו לא נושאים באחריות לאי הבנות או פירושים שגויים הנובעים משימוש בתרגום זה.