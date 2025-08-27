<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-27T21:06:20+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "he"
}
-->
# פרסום טמפרטורה - Wio Terminal

בחלק זה של השיעור, תפרסמו את ערכי הטמפרטורה שנמדדו על ידי ה-Wio Terminal באמצעות MQTT, כך שניתן יהיה להשתמש בהם מאוחר יותר לחישוב GDD.

## פרסום הטמפרטורה

לאחר קריאת הטמפרטורה, ניתן לפרסם אותה באמצעות MQTT לקוד 'שרת' שיקרא את הערכים וישמור אותם לשימוש בחישוב GDD. מיקרו-בקרים אינם קוראים את הזמן מהאינטרנט או עוקבים אחר הזמן עם שעון זמן אמת באופן מובנה, ולכן יש לתכנת את המכשיר לעשות זאת, בהנחה שיש לו את החומרה הנדרשת.

כדי לפשט את הדברים בשיעור זה, הזמן לא יישלח עם נתוני החיישן, אלא יתווסף מאוחר יותר על ידי קוד השרת כאשר הוא יקבל את ההודעות.

### משימה

תכנתו את המכשיר לפרסם את נתוני הטמפרטורה.

1. פתחו את פרויקט `temperature-sensor` של Wio Terminal.

1. חזרו על השלבים שביצעתם בשיעור 4 כדי להתחבר ל-MQTT ולשלוח טלמטריה. תשתמשו באותו Mosquitto broker ציבורי.

    השלבים לכך הם:

    - הוסיפו את ספריות Seeed WiFi ו-MQTT לקובץ `.ini`.
    - הוסיפו את קובץ הקונפיגורציה וקוד להתחברות ל-WiFi.
    - הוסיפו את הקוד להתחברות ל-MQTT broker.
    - הוסיפו את הקוד לפרסום טלמטריה.

    > ⚠️ עיינו ב[הוראות להתחברות ל-MQTT](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) וב[הוראות לשליחת טלמטריה](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) משיעור 4 אם יש צורך.

1. ודאו ש-`CLIENT_NAME` בקובץ הכותרת `config.h` משקף את הפרויקט הזה:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. עבור הטלמטריה, במקום לשלוח ערך אור, שלחו את ערך הטמפרטורה שנקרא מחיישן DHT בתכונה במסמך JSON שנקראת `temperature` על ידי שינוי הפונקציה `loop` ב-`main.cpp`:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. אין צורך לקרוא את ערך הטמפרטורה לעיתים קרובות - הוא לא ישתנה הרבה בזמן קצר, לכן הגדירו את ה-`delay` בפונקציה `loop` ל-10 דקות:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 פונקציית `delay` מקבלת את הזמן במילישניות, ולכן כדי להקל על הקריאה הערך מועבר כתוצאה מחישוב. 1,000ms בשנייה, 60 שניות בדקה, כך ש-10 x (60 שניות בדקה) x (1000ms בשנייה) נותן עיכוב של 10 דקות.

1. העלו את הקוד ל-Wio Terminal שלכם, והשתמשו במוניטור הסריאלי כדי לראות את הטמפרטורה נשלחת ל-MQTT broker.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"temperature":25}
    Sending telemetry {"temperature":25}
    ```

> 💁 תוכלו למצוא את הקוד הזה בתיקיית [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal).

😀 הצלחתם לפרסם את הטמפרטורה כטלמטריה מהמכשיר שלכם.

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.