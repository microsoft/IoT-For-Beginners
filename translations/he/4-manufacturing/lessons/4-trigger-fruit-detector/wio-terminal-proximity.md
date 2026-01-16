<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "288aebb0c59f7be1d2719b8f9660a313",
  "translation_date": "2025-08-27T20:57:22+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/wio-terminal-proximity.md",
  "language_code": "he"
}
-->
# זיהוי קרבה - Wio Terminal

בחלק זה של השיעור, תוסיף חיישן קרבה ל-Wio Terminal שלך ותמדוד מרחק באמצעותו.

## חומרה

ה-Wio Terminal זקוק לחיישן קרבה.

החיישן שבו תשתמש הוא [חיישן מרחק Grove Time of Flight](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). חיישן זה משתמש במודול לייזר למדידת מרחק. טווח החיישן הוא בין 10 מ"מ ל-2000 מ"מ (1 ס"מ - 2 מ'), והוא מדווח ערכים בטווח זה בדיוק גבוה, כאשר מרחקים מעל 1000 מ"מ מדווחים כ-8109 מ"מ.

מד המרחק בלייזר נמצא בצד האחורי של החיישן, בצד ההפוך לשקע Grove.

זהו שקע I2C.

### חיבור חיישן Time of Flight

ניתן לחבר את חיישן Time of Flight ל-Wio Terminal.

#### משימה - חיבור חיישן Time of Flight

חבר את חיישן Time of Flight.

![חיישן Grove Time of Flight](../../../../../translated_images/he/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.png)

1. הכנס קצה אחד של כבל Grove לשקע בחיישן Time of Flight. הכבל ייכנס רק בכיוון אחד.

1. כאשר ה-Wio Terminal מנותק מהמחשב או ממקור כוח אחר, חבר את הקצה השני של כבל Grove לשקע Grove בצד השמאלי של ה-Wio Terminal כשאתה מסתכל על המסך. זהו השקע הקרוב ביותר לכפתור ההפעלה. זהו שקע משולב דיגיטלי ו-I2C.

![חיישן Grove Time of Flight מחובר לשקע השמאלי](../../../../../translated_images/he/wio-time-of-flight-sensor.c4c182131d2ea73d.webp)

1. כעת תוכל לחבר את ה-Wio Terminal למחשב שלך.

## תכנות חיישן Time of Flight

כעת ניתן לתכנת את ה-Wio Terminal לשימוש בחיישן Time of Flight המחובר.

### משימה - תכנות חיישן Time of Flight

1. צור פרויקט חדש ל-Wio Terminal באמצעות PlatformIO. קרא לפרויקט זה `distance-sensor`. הוסף קוד לפונקציה `setup` כדי להגדיר את יציאת הסריאל.

1. הוסף תלות ספרייה עבור ספריית חיישן המרחק Seeed Grove Time of Flight לקובץ `platformio.ini` של הפרויקט:

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

1. בקובץ `main.cpp`, הוסף את הקוד הבא מתחת להוראות ה-include הקיימות כדי להכריז על מופע של מחלקת `Seeed_vl53l0x` לצורך אינטראקציה עם חיישן Time of Flight:

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

1. הוסף את הקוד הבא לתחתית פונקציית `setup` כדי לאתחל את החיישן:

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

1. בפונקציית `loop`, קרא ערך מהחיישן:

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    קוד זה מאתחל מבנה נתונים לקריאה, ואז מעביר אותו לשיטת `PerformSingleRangingMeasurement` שבה הוא יתמלא במדידת המרחק.

1. מתחת לכך, כתוב את מדידת המרחק ולאחר מכן הוסף השהיה של שנייה אחת:

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

1. בנה, העלה והרץ את הקוד הזה. תוכל לראות מדידות מרחק באמצעות צג הסריאל. מקם אובייקטים ליד החיישן ותראה את מדידת המרחק:

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    מד המרחק נמצא בצד האחורי של החיישן, אז וודא שאתה משתמש בצד הנכון בעת מדידת מרחק.

    ![מד המרחק בצד האחורי של חיישן Time of Flight מכוון לבננה](../../../../../translated_images/he/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 תוכל למצוא את הקוד הזה בתיקיית [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal).

😀 תוכנית חיישן הקרבה שלך הצליחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). בעוד שאנו שואפים לדיוק, יש להיות מודעים לכך שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.