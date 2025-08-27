<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-27T20:52:19+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "he"
}
-->
# סיווג תמונה באמצעות מסווג תמונות מבוסס IoT Edge - Wio Terminal

בחלק זה של השיעור, תשתמשו במסווג התמונות שפועל על מכשיר ה-IoT Edge.

## שימוש במסווג IoT Edge

ניתן להפנות את מכשיר ה-IoT לשימוש במסווג התמונות של IoT Edge. כתובת ה-URL של מסווג התמונות היא `http://<IP address or name>/image`, כאשר מחליפים את `<IP address or name>` בכתובת ה-IP או בשם המארח של המחשב שמריץ את IoT Edge.

### משימה - שימוש במסווג IoT Edge

1. פתחו את פרויקט האפליקציה `fruit-quality-detector` אם הוא עדיין לא פתוח.

1. מסווג התמונות פועל כ-API מסוג REST באמצעות HTTP, ולא HTTPS, ולכן הקריאה צריכה להשתמש בלקוח WiFi שעובד רק עם קריאות HTTP. המשמעות היא שאין צורך בתעודה. מחקו את `CERTIFICATE` מקובץ `config.h`.

1. כתובת ה-URL של התחזית בקובץ `config.h` צריכה להתעדכן לכתובת החדשה. ניתן גם למחוק את `PREDICTION_KEY` מכיוון שאין בו צורך.

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    החליפו את `<URL>` בכתובת ה-URL של המסווג שלכם.

1. בקובץ `main.cpp`, שנו את ההוראה שמייבאת את WiFi Client Secure כך שתייבא את גרסת ה-HTTP הרגילה:

    ```cpp
    #include <WiFiClient.h>
    ```

1. שנו את ההצהרה של `WiFiClient` לגרסת ה-HTTP:

    ```cpp
    WiFiClient client;
    ```

1. בחרו את השורה שמגדירה את התעודה בלקוח ה-WiFi. מחקו את השורה `client.setCACert(CERTIFICATE);` מפונקציית `connectWiFi`.

1. בפונקציה `classifyImage`, מחקו את השורה `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);` שמגדירה את מפתח התחזית בכותרת.

1. העלו והריצו את הקוד שלכם. כוונו את המצלמה לעבר פרי ולחצו על כפתור C. תוכלו לראות את הפלט בצג הסדרתי:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 ניתן למצוא את הקוד הזה בתיקיית [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal).

😀 תוכנית מסווג איכות הפירות שלכם הצליחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.