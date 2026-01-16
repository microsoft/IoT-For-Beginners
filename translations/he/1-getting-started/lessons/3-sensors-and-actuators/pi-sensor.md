<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ea733bd0cdf2479e082373f765a08678",
  "translation_date": "2025-08-27T21:49:21+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-sensor.md",
  "language_code": "he"
}
-->
# בנה מנורת לילה - Raspberry Pi

בחלק זה של השיעור, תוסיף חיישן אור ל-Raspberry Pi שלך.

## חומרה

החיישן לשיעור זה הוא **חיישן אור** שמשתמש ב-[פוטודיודה](https://wikipedia.org/wiki/Photodiode) כדי להמיר אור לאות חשמלי. זהו חיישן אנלוגי ששולח ערך מספרי בין 0 ל-1,000 שמצביע על כמות יחסית של אור, אך אינו תואם ליחידת מדידה סטנדרטית כמו [לוקס](https://wikipedia.org/wiki/Lux).

חיישן האור הוא חיישן Grove חיצוני ויש לחבר אותו לכובע הבסיס של Grove על ה-Raspberry Pi.

### חיבור חיישן האור

חיישן האור של Grove, שמשמש לזיהוי רמות האור, צריך להיות מחובר ל-Raspberry Pi.

#### משימה - חיבור חיישן האור

חבר את חיישן האור

![חיישן אור Grove](../../../../../translated_images/he/grove-light-sensor.b8127b7c434e632d6bcdb57587a14e9ef69a268a22df95d08628f62b8fa5505c.png)

1. הכנס קצה אחד של כבל Grove לשקע על מודול חיישן האור. הכבל ייכנס רק בכיוון אחד.

1. כאשר ה-Raspberry Pi כבוי, חבר את הקצה השני של כבל Grove לשקע האנלוגי המסומן **A0** על כובע הבסיס של Grove שמחובר ל-Pi. שקע זה הוא השני מימין, בשורה של השקעים ליד פיני GPIO.

![חיישן האור Grove מחובר לשקע A0](../../../../../translated_images/he/pi-light-sensor.66cc1e31fa48cd7d5f23400d4b2119aa41508275cb7c778053a7923b4e972d7e.png)

## תכנות חיישן האור

כעת ניתן לתכנת את המכשיר באמצעות חיישן האור של Grove.

### משימה - תכנות חיישן האור

תכנת את המכשיר.

1. הפעל את ה-Pi והמתן עד שיסיים את תהליך האתחול.

1. פתח את פרויקט מנורת הלילה ב-VS Code שיצרת בחלק הקודם של המשימה, או ישירות על ה-Pi או באמצעות הרחבת Remote SSH.

1. פתח את הקובץ `app.py` ומחק את כל הקוד שבו.

1. הוסף את הקוד הבא לקובץ `app.py` כדי לייבא ספריות נדרשות:

    ```python
    import time
    from grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    הפקודה `import time` מייבאת את המודול `time` שישמש בהמשך המשימה.

    הפקודה `from grove.grove_light_sensor_v1_2 import GroveLightSensor` מייבאת את `GroveLightSensor` מספריות Python של Grove. ספרייה זו מכילה קוד לתקשורת עם חיישן אור Grove, והיא הותקנה באופן גלובלי במהלך הגדרת ה-Pi.

1. הוסף את הקוד הבא אחרי הקוד לעיל כדי ליצור מופע של המחלקה שמנהלת את חיישן האור:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    השורה `light_sensor = GroveLightSensor(0)` יוצרת מופע של מחלקת `GroveLightSensor` שמתחברת לפין **A0** - הפין האנלוגי של Grove שאליו מחובר חיישן האור.

1. הוסף לולאה אינסופית אחרי הקוד לעיל כדי לקרוא את ערך חיישן האור ולהדפיס אותו לקונסול:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    פעולה זו תקרא את רמת האור הנוכחית בסקאלה של 0-1,023 באמצעות המאפיין `light` של מחלקת `GroveLightSensor`. מאפיין זה קורא את הערך האנלוגי מהפין. ערך זה יודפס לקונסול.

1. הוסף השהיה קצרה של שנייה בסוף ה-`loop`, מכיוון שאין צורך לבדוק את רמות האור באופן רציף. השהיה מפחיתה את צריכת החשמל של המכשיר.

    ```python
    time.sleep(1)
    ```

1. מהטרמינל של VS Code, הרץ את הפקודה הבאה כדי להפעיל את אפליקציית Python שלך:

    ```sh
    python3 app.py
    ```

    ערכי האור יופיעו בקונסול. כסה וחשוף את חיישן האור, והערכים ישתנו:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

> 💁 תוכל למצוא את הקוד הזה בתיקיית [code-sensor/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/pi).

😀 הוספת חיישן לתוכנית מנורת הלילה שלך הייתה הצלחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.