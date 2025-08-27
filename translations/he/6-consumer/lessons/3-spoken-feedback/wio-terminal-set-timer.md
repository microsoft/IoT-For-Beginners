<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-27T22:27:08+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "he"
}
-->
# הגדרת טיימר - Wio Terminal

בחלק זה של השיעור, תפעיל את הקוד חסר השרת שלך כדי להבין את הדיבור, ותגדיר טיימר ב-Wio Terminal שלך על בסיס התוצאות.

## הגדרת טיימר

הטקסט שמתקבל מהקריאה לדיבור לטקסט צריך להישלח לקוד חסר השרת שלך כדי להיות מעובד על ידי LUIS, ולקבל בחזרה את מספר השניות עבור הטיימר. מספר השניות הזה יכול לשמש להגדרת טיימר.

מיקרו-בקרים אינם תומכים באופן טבעי בריבוי תהליכים ב-Arduino, ולכן אין מחלקות טיימר סטנדרטיות כמו שתמצא בעת כתיבה ב-Python או שפות ברמה גבוהה אחרות. במקום זאת, ניתן להשתמש בספריות טיימר שעובדות על ידי מדידת זמן שחלף בפונקציית `loop`, וקוראות לפונקציות כאשר הזמן נגמר.

### משימה - שליחת הטקסט לפונקציה חסרת השרת

1. פתח את פרויקט `smart-timer` ב-VS Code אם הוא לא פתוח כבר.

1. פתח את קובץ הכותרת `config.h` והוסף את ה-URL של אפליקציית הפונקציות שלך:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    החלף `<URL>` ב-URL של אפליקציית הפונקציות שלך שהשגת בשלב האחרון של השיעור הקודם, המצביע על כתובת ה-IP של המחשב המקומי שלך שמריץ את אפליקציית הפונקציות.

1. צור קובץ חדש בתיקיית `src` בשם `language_understanding.h`. קובץ זה ישמש להגדרת מחלקה לשליחת הדיבור המוכר לאפליקציית הפונקציות שלך כדי להמיר לשניות באמצעות LUIS.

1. הוסף את הדברים הבאים לראש הקובץ:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    זה כולל כמה קבצי כותרת נחוצים.

1. הגדר מחלקה בשם `LanguageUnderstanding`, והכרז על מופע של מחלקה זו:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. כדי לקרוא לאפליקציית הפונקציות שלך, עליך להכריז על לקוח WiFi. הוסף את הדברים הבאים לחלק `private` של המחלקה:

    ```cpp
    WiFiClient _client;
    ```

1. בחלק `public`, הכרז על מתודה בשם `GetTimerDuration` כדי לקרוא לאפליקציית הפונקציות:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. במתודה `GetTimerDuration`, הוסף את הקוד הבא לבניית ה-JSON שישלח לאפליקציית הפונקציות:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    זה ממיר את הטקסט שעובר למתודה `GetTimerDuration` ל-JSON הבא:

    ```json
    {
        "text" : "<text>"
    }
    ```

    כאשר `<text>` הוא הטקסט שעובר לפונקציה.

1. מתחת לזה, הוסף את הקוד הבא כדי לבצע את הקריאה לאפליקציית הפונקציות:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    זה מבצע בקשת POST לאפליקציית הפונקציות, מעביר את גוף ה-JSON ומקבל את קוד התגובה.

1. הוסף את הקוד הבא מתחת לזה:

    ```cpp
    int seconds = 0;
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonObject obj = doc.as<JsonObject>();
        seconds = obj["seconds"].as<int>();
    }
    else
    {
        Serial.print("Failed to understand text - error ");
        Serial.println(httpResponseCode);
    }
    ```

    קוד זה בודק את קוד התגובה. אם הוא 200 (הצלחה), אז מספר השניות עבור הטיימר נשלף מגוף התגובה. אחרת, שגיאה נשלחת למוניטור הסדרתי ומספר השניות מוגדר ל-0.

1. הוסף את הקוד הבא לסוף המתודה הזו כדי לסגור את חיבור ה-HTTP ולהחזיר את מספר השניות:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. בקובץ `main.cpp`, כלול את הכותרת החדשה הזו:

    ```cpp
    #include "speech_to_text.h"
    ```

1. בסוף הפונקציה `processAudio`, קרא למתודה `GetTimerDuration` כדי לקבל את משך הטיימר:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    זה ממיר את הטקסט מהקריאה למחלקה `SpeechToText` למספר השניות עבור הטיימר.

### משימה - הגדרת טיימר

מספר השניות יכול לשמש להגדרת טיימר.

1. הוסף את תלות הספרייה הבאה לקובץ `platformio.ini` כדי להוסיף ספרייה להגדרת טיימר:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. הוסף הנחיית include עבור הספרייה הזו לקובץ `main.cpp`:

    ```cpp
    #include <arduino-timer.h>
    ```

1. מעל הפונקציה `processAudio`, הוסף את הקוד הבא:

    ```cpp
    auto timer = timer_create_default();
    ```

    קוד זה מכריז על טיימר בשם `timer`.

1. מתחת לזה, הוסף את הקוד הבא:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    פונקציית `say` זו בסופו של דבר תמיר טקסט לדיבור, אך לעת עתה היא רק תכתוב את הטקסט שעובר אליה למוניטור הסדרתי.

1. מתחת לפונקציית `say`, הוסף את הקוד הבא:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    זו פונקציית callback שתיקרא כאשר טיימר יפוג. היא מקבלת הודעה לומר כאשר הטיימר פג. טיימרים יכולים לחזור על עצמם, וזה ניתן לשליטה על ידי ערך ההחזרה של פונקציית callback זו - כאן היא מחזירה `false`, כדי לומר לטיימר לא לרוץ שוב.

1. הוסף את הקוד הבא לסוף הפונקציה `processAudio`:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    קוד זה בודק את המספר הכולל של השניות, ואם הוא 0, חוזר מהקריאה לפונקציה כך שלא יוגדרו טיימרים. לאחר מכן הוא ממיר את המספר הכולל של השניות לדקות ושניות.

1. מתחת לקוד זה, הוסף את הדברים הבאים כדי ליצור הודעה לומר כאשר הטיימר מתחיל:

    ```cpp
    String begin_message;
    if (minutes > 0)
    {
        begin_message += minutes;
        begin_message += " minute ";
    }
    if (seconds > 0)
    {
        begin_message += seconds;
        begin_message += " second ";
    }

    begin_message += "timer started.";
    ```

1. מתחת לזה, הוסף קוד דומה כדי ליצור הודעה לומר כאשר הטיימר פג:

    ```cpp
    String end_message("Times up on your ");
    if (minutes > 0)
    {
        end_message += minutes;
        end_message += " minute ";
    }
    if (seconds > 0)
    {
        end_message += seconds;
        end_message += " second ";
    }

    end_message += "timer.";
    ```

1. לאחר מכן, אמור את הודעת התחלת הטיימר:

    ```cpp
    say(begin_message);
    ```

1. בסוף הפונקציה הזו, הפעל את הטיימר:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    זה מפעיל את הטיימר. הטיימר מוגדר באמצעות מילי-שניות, ולכן המספר הכולל של השניות מוכפל ב-1,000 כדי להמיר למילי-שניות. פונקציית `timerExpired` מועברת כ-callback, וההודעה `end_message` מועברת כארגומנט ל-callback. callback זה מקבל רק ארגומנטים מסוג `void *`, ולכן המחרוזת מומרת בהתאם.

1. לבסוף, הטיימר צריך *לתקתק*, וזה נעשה בפונקציית `loop`. הוסף את הקוד הבא בסוף פונקציית `loop`:

    ```cpp
    timer.tick();
    ```

1. בנה את הקוד הזה, העלה אותו ל-Wio Terminal שלך ובדוק אותו דרך המוניטור הסדרתי. ברגע שתראה `Ready` במוניטור הסדרתי, לחץ על כפתור C (זה שבצד השמאלי, הקרוב ביותר למתג ההפעלה), ודבר. 4 שניות של אודיו יוקלטו, יומרו לטקסט, ואז יישלחו לאפליקציית הפונקציות שלך, וטיימר יוגדר. ודא שאפליקציית הפונקציות שלך פועלת באופן מקומי.

    תראה מתי הטיימר מתחיל, ומתי הוא מסתיים.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Set a 2 minute and 27 second timer.","Offset":4700000,"Duration":35300000}
    Set a 2 minute and 27 second timer.
    {"seconds": 147}
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 ניתן למצוא את הקוד הזה בתיקיית [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal).

😀 תוכנית הטיימר שלך הצליחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.