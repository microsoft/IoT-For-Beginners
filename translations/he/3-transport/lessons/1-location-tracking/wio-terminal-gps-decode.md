<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-27T22:56:27+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "he"
}
-->
# פענוח נתוני GPS - Wio Terminal

בחלק זה של השיעור, תפענחו את הודעות NMEA שנקראו מחיישן ה-GPS על ידי ה-Wio Terminal, ותוציאו את קווי הרוחב והאורך.

## פענוח נתוני GPS

לאחר קריאת נתוני NMEA הגולמיים מהפורט הסדרתי, ניתן לפענח אותם באמצעות ספריית NMEA בקוד פתוח.

### משימה - פענוח נתוני GPS

תכנתו את המכשיר לפענח את נתוני ה-GPS.

1. פתחו את פרויקט האפליקציה `gps-sensor` אם הוא עדיין לא פתוח.

1. הוסיפו תלות בספרייה [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) לקובץ `platformio.ini` של הפרויקט. ספרייה זו מכילה קוד לפענוח נתוני NMEA.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. בקובץ `main.cpp`, הוסיפו הוראת include עבור ספריית TinyGPSPlus:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. מתחת להצהרה של `Serial3`, הכריזו על אובייקט TinyGPSPlus לעיבוד משפטי NMEA:

    ```cpp
    TinyGPSPlus gps;
    ```

1. שנו את תוכן הפונקציה `printGPSData` לתוכן הבא:

    ```cpp
    if (gps.encode(Serial3.read()))
    {
        if (gps.location.isValid())
        {
            Serial.print(gps.location.lat(), 6);
            Serial.print(F(","));
            Serial.print(gps.location.lng(), 6);
            Serial.print(" - from ");
            Serial.print(gps.satellites.value());
            Serial.println(" satellites");
        }
    }
    ```

    קוד זה קורא את התו הבא מפורט ה-UART הסדרתי לתוך מפענח ה-NMEA `gps`. לאחר כל תו, הוא יבדוק אם המפענח קרא משפט תקין, ואז יבדוק אם הוא קרא מיקום תקין. אם המיקום תקין, הוא ישלח אותו למוניטור הסדרתי, יחד עם מספר הלוויינים שתרמו לתיקון זה.

1. בנו והעלו את הקוד ל-Wio Terminal.

1. לאחר העלאה, תוכלו לעקוב אחר נתוני מיקום ה-GPS באמצעות המוניטור הסדרתי.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 תוכלו למצוא את הקוד הזה בתיקייה [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal).

😀 תוכנית חיישן ה-GPS שלכם עם פענוח נתונים הצליחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.