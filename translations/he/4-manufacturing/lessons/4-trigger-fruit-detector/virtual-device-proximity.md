<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e9f05bdc50a40fd924b1d66934471bf",
  "translation_date": "2025-08-27T20:58:07+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/virtual-device-proximity.md",
  "language_code": "he"
}
-->
# זיהוי קרבה - חומרה וירטואלית ל-IoT

בחלק זה של השיעור, תוסיפו חיישן קרבה למכשיר ה-IoT הווירטואלי שלכם, ותקראו ממנו מרחק.

## חומרה

מכשיר ה-IoT הווירטואלי ישתמש בחיישן מרחק מדומה.

במכשיר IoT פיזי, הייתם משתמשים בחיישן עם מודול מדידת לייזר לזיהוי מרחק.

### הוספת חיישן המרחק ל-CounterFit

כדי להשתמש בחיישן מרחק וירטואלי, עליכם להוסיף אחד לאפליקציית CounterFit.

#### משימה - הוספת חיישן המרחק ל-CounterFit

הוסיפו את חיישן המרחק לאפליקציית CounterFit.

1. פתחו את הקוד של `fruit-quality-detector` ב-VS Code, וודאו שהסביבה הווירטואלית מופעלת.

1. התקינו חבילת Pip נוספת כדי להתקין שכבת CounterFit שיכולה לתקשר עם חיישני מרחק על ידי סימולציה של [חבילת Pip rpi-vl53l0x](https://pypi.org/project/rpi-vl53l0x/), חבילת Python שמתקשרת עם [חיישן מרחק VL53L0X](https://wiki.seeedstudio.com/Grove-Time_of_Flight_Distance_Sensor-VL53L0X/). וודאו שאתם מתקינים זאת מתוך טרמינל שבו הסביבה הווירטואלית מופעלת.

    ```sh
    pip install counterfit-shims-rpi-vl53l0x
    ```

1. וודאו שאפליקציית הווב של CounterFit פועלת.

1. צרו חיישן מרחק:

    1. בתיבה *Create sensor* בלשונית *Sensors*, פתחו את התפריט הנפתח של *Sensor type* ובחרו *Distance*.

    1. השאירו את *Units* כ-`Millimeter`.

    1. החיישן הזה הוא חיישן I²C, לכן הגדירו את הכתובת ל-`0x29`. אם הייתם משתמשים בחיישן VL53L0X פיזי, הכתובת הזו הייתה מוגדרת מראש.

    1. לחצו על כפתור **Add** כדי ליצור את חיישן המרחק.

    ![הגדרות חיישן המרחק](../../../../../translated_images/he/counterfit-create-distance-sensor.967c9fb98f27888d95920c9784d004c972490eb71f70397fe13bd70a79a879a3.png)

    חיישן המרחק ייווצר ויופיע ברשימת החיישנים.

    ![חיישן המרחק שנוצר](../../../../../translated_images/he/counterfit-distance-sensor.079eefeeea0b68afc36431ce8fcbe2f09a7e4916ed1cd5cb30e696db53bc18fa.png)

## תכנות חיישן המרחק

כעת ניתן לתכנת את מכשיר ה-IoT הווירטואלי לשימוש בחיישן המרחק המדומה.

### משימה - תכנות חיישן זמן הטיסה

1. צרו קובץ חדש בפרויקט `fruit-quality-detector` בשם `distance-sensor.py`.

    > 💁 דרך קלה לסמלץ מספר מכשירי IoT היא לעשות זאת בכל קובץ Python נפרד, ואז להריץ אותם בו-זמנית.

1. התחילו חיבור ל-CounterFit עם הקוד הבא:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. הוסיפו את הקוד הבא מתחת לזה:

    ```python
    import time
    
    from counterfit_shims_rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    קוד זה מייבא את שכבת הספרייה של חיישן VL53L0X לזמן טיסה.

1. מתחת לזה, הוסיפו את הקוד הבא לגישה לחיישן:

    ```python
    distance_sensor = VL53L0X()
    distance_sensor.begin()
    ```

    קוד זה מצהיר על חיישן מרחק, ואז מפעיל את החיישן.

1. לבסוף, הוסיפו לולאה אינסופית לקריאת מרחקים:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    קוד זה ממתין לערך מוכן לקריאה מהחיישן, ואז מדפיס אותו לקונסול.

1. הריצו את הקוד.

    > 💁 אל תשכחו שהקובץ הזה נקרא `distance-sensor.py`! וודאו שאתם מריצים אותו דרך Python, ולא `app.py`.

1. תראו מדידות מרחק מופיעות בקונסול. שנו את הערך ב-CounterFit כדי לראות את השינוי, או השתמשו בערכים אקראיים.

    ```output
    (.venv) ➜  fruit-quality-detector python distance-sensor.py 
    Distance = 37 mm
    Distance = 42 mm
    Distance = 29 mm
    ```

> 💁 תוכלו למצוא את הקוד הזה בתיקייה [code-proximity/virtual-iot-device](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/virtual-iot-device).

😀 תוכנית חיישן הקרבה שלכם הצליחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). בעוד שאנו שואפים לדיוק, יש להיות מודעים לכך שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.