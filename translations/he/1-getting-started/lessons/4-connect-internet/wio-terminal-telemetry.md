<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-27T21:45:47+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "he"
}
-->
# שלוט בתאורת הלילה שלך דרך האינטרנט - Wio Terminal

בחלק זה של השיעור, תשלח נתוני טלמטריה עם רמות אור מה-Wio Terminal שלך ל-MQTT broker.

## התקנת ספריות JSON עבור Arduino

אחת הדרכים הפופולריות לשלוח הודעות דרך MQTT היא באמצעות JSON. קיימת ספריית Arduino עבור JSON שמקלה על קריאה וכתיבה של מסמכי JSON.

### משימה

התקן את ספריית Arduino JSON.

1. פתח את פרויקט תאורת הלילה ב-VS Code.

1. הוסף את השורה הבאה כרשומה נוספת לרשימת `lib_deps` בקובץ `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    זה מייבא את [ArduinoJson](https://arduinojson.org), ספריית JSON עבור Arduino.

## פרסום טלמטריה

השלב הבא הוא ליצור מסמך JSON עם נתוני טלמטריה ולשלוח אותו ל-MQTT broker.

### משימה - פרסום טלמטריה

פרסם נתוני טלמטריה ל-MQTT broker.

1. הוסף את הקוד הבא לתחתית קובץ `config.h` כדי להגדיר את שם נושא הטלמטריה עבור ה-MQTT broker:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC` הוא הנושא שבו המכשיר יפרסם את רמות האור.

1. פתח את קובץ `main.cpp`.

1. הוסף את הוראת `#include` הבאה לראש הקובץ:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. הוסף את הקוד הבא בתוך הפונקציה `loop`, ממש לפני `delay`:

    ```cpp
    int light = analogRead(WIO_LIGHT);

    DynamicJsonDocument doc(1024);
    doc["light"] = light;

    string telemetry;
    serializeJson(doc, telemetry);

    Serial.print("Sending telemetry ");
    Serial.println(telemetry.c_str());

    client.publish(CLIENT_TELEMETRY_TOPIC.c_str(), telemetry.c_str());
    ```

    קוד זה קורא את רמת האור, יוצר מסמך JSON באמצעות ArduinoJson שמכיל את הרמה הזו. לאחר מכן המסמך מסודר למחרוזת ונשלח לנושא הטלמטריה של MQTT על ידי לקוח ה-MQTT.

1. העלה את הקוד ל-Wio Terminal שלך, והשתמש ב-Serial Monitor כדי לראות את רמות האור שנשלחות ל-MQTT broker.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 תוכל למצוא את הקוד הזה בתיקייה [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal).

😀 הצלחת לשלוח נתוני טלמטריה מהמכשיר שלך.

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.