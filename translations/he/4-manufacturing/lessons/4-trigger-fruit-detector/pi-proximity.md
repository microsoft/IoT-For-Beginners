# זיהוי קרבה - Raspberry Pi

בחלק זה של השיעור, תוסיף חיישן קרבה ל-Raspberry Pi שלך, ותקרא ממנו מרחק.

## חומרה

ה-Raspberry Pi זקוק לחיישן קרבה.

החיישן שבו תשתמש הוא [חיישן מרחק Grove Time of Flight](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). חיישן זה משתמש במודול מדידת לייזר לזיהוי מרחק. טווח החיישן הוא בין 10 מ"מ ל-2000 מ"מ (1 ס"מ - 2 מ'), והוא ידווח על ערכים בטווח זה בדיוק גבוה למדי, כאשר מרחקים מעל 1000 מ"מ ידווחו כ-8109 מ"מ.

מד המרחק בלייזר נמצא בצד האחורי של החיישן, בצד הנגדי לשקע ה-Grove.

זהו חיישן I²C.

### חיבור חיישן Time of Flight

ניתן לחבר את חיישן ה-Time of Flight ל-Raspberry Pi.

#### משימה - חיבור חיישן ה-Time of Flight

חבר את חיישן ה-Time of Flight.

![חיישן Time of Flight מסוג Grove](../../../../../translated_images/he/grove-time-of-flight-sensor.d82ff2165bfded9f.webp)

1. הכנס קצה אחד של כבל Grove לשקע בחיישן ה-Time of Flight. הוא ייכנס רק בכיוון אחד.

1. כשה-Raspberry Pi כבוי, חבר את הקצה השני של כבל ה-Grove לאחד משקעי ה-I²C המסומנים **I²C** על ה-Grove Base Hat המחובר ל-Pi. שקעי ה-I²C נמצאים בשורה התחתונה, בצד הנגדי לפינים של ה-GPI וליד חריץ כבל המצלמה.

![חיישן Time of Flight מסוג Grove מחובר לשקע I²C](../../../../../translated_images/he/pi-time-of-flight-sensor.58c8dc04eb3bfb57.webp)

## תכנות חיישן ה-Time of Flight

כעת ניתן לתכנת את ה-Raspberry Pi לשימוש בחיישן ה-Time of Flight המחובר.

### משימה - תכנות חיישן ה-Time of Flight

תכנת את המכשיר.

1. הפעל את ה-Pi והמתן עד שיסיים את תהליך האתחול.

1. פתח את קוד `fruit-quality-detector` ב-VS Code, או ישירות על ה-Pi, או באמצעות חיבור דרך תוסף Remote SSH.

1. התקן את חבילת ה-Pip בשם rpi-vl53l0x, שהיא חבילת Python שמתקשרת עם חיישן מרחק VL53L0X מסוג Time of Flight. התקן אותה באמצעות הפקודה הבאה:

    ```sh
    pip install rpi-vl53l0x
    ```

1. צור קובץ חדש בפרויקט זה בשם `distance-sensor.py`.

    > 💁 דרך קלה לדמות מספר מכשירי IoT היא ליצור כל אחד בקובץ Python נפרד, ואז להפעיל אותם בו-זמנית.

1. הוסף את הקוד הבא לקובץ זה:

    ```python
    import time
    
    from grove.i2c import Bus
    from rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    קוד זה מייבא את ספריית ה-I²C של Grove, ואת ספריית החיישן עבור החומרה המרכזית המובנית בחיישן ה-Time of Flight של Grove.

1. מתחת לזה, הוסף את הקוד הבא לגישה לחיישן:

    ```python
    distance_sensor = VL53L0X(bus = Bus().bus)
    distance_sensor.begin()    
    ```

    קוד זה מצהיר על חיישן מרחק באמצעות ה-I²C של Grove, ואז מפעיל את החיישן.

1. לבסוף, הוסף לולאה אינסופית לקריאת מרחקים:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    קוד זה ממתין לערך מוכן לקריאה מהחיישן, ואז מדפיס אותו לקונסולה.

1. הפעל את הקוד.

    > 💁 זכור שקובץ זה נקרא `distance-sensor.py`! ודא שאתה מפעיל אותו באמצעות Python, ולא `app.py`.

1. תראה מדידות מרחק מופיעות בקונסולה. מקם אובייקטים ליד החיישן ותראה את מדידת המרחק:

    ```output
    pi@raspberrypi:~/fruit-quality-detector $ python3 distance_sensor.py 
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    מד המרחק נמצא בצד האחורי של החיישן, אז ודא שאתה משתמש בצד הנכון בעת מדידת מרחק.

    ![מד המרחק בצד האחורי של חיישן ה-Time of Flight מכוון לעבר בננה](../../../../../translated_images/he/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 תוכל למצוא את הקוד הזה בתיקיית [code-proximity/pi](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/pi).

😀 תוכנית חיישן הקרבה שלך הצליחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.