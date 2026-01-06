<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-27T21:47:51+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "he"
}
-->
# שלוט באור הלילה שלך דרך האינטרנט - Wio Terminal

מכשיר ה-IoT צריך להיות מתוכנת לתקשר עם *test.mosquitto.org* באמצעות MQTT כדי לשלוח ערכי טלמטריה עם קריאת חיישן האור, ולקבל פקודות לשליטה בנורית ה-LED.

בחלק זה של השיעור, תחבר את ה-Wio Terminal שלך לשרת MQTT.

## התקנת ספריות WiFi ו-MQTT עבור Arduino

כדי לתקשר עם שרת ה-MQTT, יש להתקין כמה ספריות Arduino כדי להשתמש בשבב ה-WiFi ב-Wio Terminal ולתקשר עם MQTT. בעת פיתוח עבור מכשירי Arduino, ניתן להשתמש במגוון רחב של ספריות המכילות קוד בקוד פתוח ומאפשרות מגוון רחב של יכולות. חברת Seeed מפרסמת ספריות עבור ה-Wio Terminal שמאפשרות לו לתקשר דרך WiFi. מפתחים אחרים פרסמו ספריות לתקשורת עם שרתי MQTT, ואתה תשתמש בהן עם המכשיר שלך.

הספריות הללו מסופקות כקוד מקור שניתן לייבא באופן אוטומטי ל-PlatformIO ולתרגם עבור המכשיר שלך. כך ספריות Arduino יעבדו על כל מכשיר שתומך במסגרת Arduino, בהנחה שלמכשיר יש את החומרה הספציפית הנדרשת על ידי הספרייה. חלק מהספריות, כמו ספריות ה-WiFi של Seeed, הן ספציפיות לחומרה מסוימת.

ניתן להתקין ספריות באופן גלובלי ולתרגם אותן אם יש צורך, או בפרויקט ספציפי. עבור משימה זו, הספריות יותקנו בפרויקט.

✅ ניתן ללמוד עוד על ניהול ספריות וכיצד למצוא ולהתקין ספריות בתיעוד הספריות של [PlatformIO](https://docs.platformio.org/en/latest/librarymanager/index.html).

### משימה - התקנת ספריות WiFi ו-MQTT עבור Arduino

התקן את ספריות ה-Arduino.

1. פתח את פרויקט אור הלילה ב-VS Code.

1. הוסף את השורות הבאות לסוף קובץ `platformio.ini`:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    זה מייבא את ספריות ה-WiFi של Seeed. התחביר `@ <number>` מתייחס לגרסה ספציפית של הספרייה.

    > 💁 ניתן להסיר את `@ <number>` כדי להשתמש תמיד בגרסה העדכנית ביותר של הספריות, אך אין ערובה שגרסאות מאוחרות יותר יעבדו עם הקוד שלמטה. הקוד כאן נבדק עם גרסה זו של הספריות.

    זה כל מה שצריך לעשות כדי להוסיף את הספריות. בפעם הבאה ש-PlatformIO יבנה את הפרויקט, הוא יוריד את קוד המקור של הספריות הללו ויתרגם אותו לפרויקט שלך.

1. הוסף את השורות הבאות ל-`lib_deps`:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    זה מייבא את [PubSubClient](https://github.com/knolleary/pubsubclient), לקוח MQTT עבור Arduino.

## התחברות ל-WiFi

כעת ניתן לחבר את ה-Wio Terminal ל-WiFi.

### משימה - התחברות ל-WiFi

חבר את ה-Wio Terminal ל-WiFi.

1. צור קובץ חדש בתיקיית `src` בשם `config.h`. ניתן לעשות זאת על ידי בחירת תיקיית `src`, או קובץ `main.cpp` שבתוכה, ולחיצה על כפתור **New file** בסייר הקבצים. כפתור זה מופיע רק כאשר הסמן נמצא מעל סייר הקבצים.

    ![כפתור יצירת קובץ חדש](../../../../../translated_images/vscode-new-file-button.182702340fe6723c.he.png)

1. הוסף את הקוד הבא לקובץ זה כדי להגדיר קבועים עבור פרטי ה-WiFi שלך:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    החלף `<SSID>` בשם רשת ה-WiFi שלך. החלף `<PASSWORD>` בסיסמת ה-WiFi שלך.

1. פתח את קובץ `main.cpp`.

1. הוסף את הוראות `#include` הבאות לראש הקובץ:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    זה כולל קבצי כותרת עבור הספריות שהוספת קודם, כמו גם את קובץ הכותרת של הקונפיגורציה. קבצי הכותרת הללו נחוצים כדי להורות ל-PlatformIO להכניס את הקוד מהספריות. ללא הכללה מפורשת של קבצי הכותרת הללו, חלק מהקוד לא ייכנס לתהליך התרגום ותקבל שגיאות קומפילציה.

1. הוסף את הקוד הבא מעל פונקציית `setup`:

    ```cpp
    void connectWiFi()
    {
        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("Connecting to WiFi..");
            WiFi.begin(SSID, PASSWORD);
            delay(500);
        }
    
        Serial.println("Connected!");
    }
    ```

    קוד זה מבצע לולאה בזמן שהמכשיר אינו מחובר ל-WiFi, ומנסה להתחבר באמצעות ה-SSID והסיסמה מקובץ הכותרת של הקונפיגורציה.

1. הוסף קריאה לפונקציה זו בתחתית פונקציית `setup`, לאחר שהפינים הוגדרו.

    ```cpp
    connectWiFi();
    ```

1. העלה את הקוד למכשיר שלך כדי לבדוק שהחיבור ל-WiFi עובד. אתה אמור לראות זאת בצג הסדרתי.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## התחברות ל-MQTT

לאחר שה-Wio Terminal מחובר ל-WiFi, הוא יכול להתחבר לשרת ה-MQTT.

### משימה - התחברות ל-MQTT

חבר את ה-Wio Terminal לשרת ה-MQTT.

1. הוסף את הקוד הבא לתחתית קובץ `config.h` כדי להגדיר את פרטי החיבור לשרת ה-MQTT:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    החלף `<ID>` ב-ID ייחודי שישמש כשם לקוח המכשיר הזה, ובהמשך לנושאים שהמכשיר הזה מפרסם ומנוי אליהם. שרת *test.mosquitto.org* הוא ציבורי ומשמש אנשים רבים, כולל תלמידים אחרים שעובדים על משימה זו. שימוש בשם לקוח MQTT ייחודי ושמות נושאים ייחודיים מבטיח שהקוד שלך לא יתנגש עם קוד של אחרים. תזדקק ל-ID זה גם כאשר תיצור את קוד השרת בהמשך משימה זו.

    > 💁 ניתן להשתמש באתר כמו [GUIDGen](https://www.guidgen.com) כדי ליצור ID ייחודי.

    `BROKER` הוא כתובת ה-URL של שרת ה-MQTT.

    `CLIENT_NAME` הוא שם ייחודי עבור לקוח ה-MQTT הזה בשרת.

1. פתח את קובץ `main.cpp`, והוסף את הקוד הבא מתחת לפונקציה `connectWiFi` ומעל פונקציית `setup`:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    קוד זה יוצר לקוח WiFi באמצעות ספריות ה-WiFi של Wio Terminal ומשתמש בו כדי ליצור לקוח MQTT.

1. מתחת לקוד זה, הוסף את השורות הבאות:

    ```cpp
    void reconnectMQTTClient()
    {
        while (!client.connected())
        {
            Serial.print("Attempting MQTT connection...");
    
            if (client.connect(CLIENT_NAME.c_str()))
            {
                Serial.println("connected");
            }
            else
            {
                Serial.print("Retying in 5 seconds - failed, rc=");
                Serial.println(client.state());
                
                delay(5000);
            }
        }
    }
    ```

    פונקציה זו בודקת את החיבור לשרת ה-MQTT ומתחברת מחדש אם החיבור אינו פעיל. היא מבצעת לולאה כל הזמן שהחיבור אינו פעיל ומנסה להתחבר באמצעות שם הלקוח הייחודי שהוגדר בקובץ הכותרת של הקונפיגורציה.

    אם החיבור נכשל, היא מנסה שוב לאחר 5 שניות.

1. הוסף את הקוד הבא מתחת לפונקציה `reconnectMQTTClient`:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    קוד זה מגדיר את שרת ה-MQTT עבור הלקוח, כמו גם את ההגדרה של פונקציית callback כאשר מתקבלת הודעה. לאחר מכן הוא מנסה להתחבר לשרת.

1. קרא לפונקציה `createMQTTClient` בתוך פונקציית `setup` לאחר שהחיבור ל-WiFi הושלם.

1. החלף את כל פונקציית `loop` בקוד הבא:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    קוד זה מתחיל בבדיקה מחדש של החיבור לשרת ה-MQTT. חיבורים אלו יכולים להישבר בקלות, ולכן כדאי לבדוק באופן קבוע ולהתחבר מחדש אם יש צורך. לאחר מכן הוא קורא לפונקציה `loop` של לקוח ה-MQTT כדי לעבד הודעות שמגיעות בנושא שהלקוח מנוי אליו. אפליקציה זו היא חד-תהליכית, ולכן הודעות אינן יכולות להתקבל בתהליך רקע, ולכן יש להקצות זמן בתהליך הראשי לעיבוד הודעות שממתינות בחיבור הרשת.

    לבסוף, עיכוב של 2 שניות מבטיח שרמות האור לא יישלחו בתדירות גבוהה מדי ומפחית את צריכת החשמל של המכשיר.

1. העלה את הקוד ל-Wio Terminal שלך, והשתמש בצג הסדרתי כדי לראות את המכשיר מתחבר ל-WiFi ול-MQTT.

    ```output
    > Executing task: platformio device monitor <
    
    source /Users/jimbennett/GitHub/IoT-For-Beginners/1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal/nightlight/.venv/bin/activate
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    ```

> 💁 ניתן למצוא את הקוד הזה בתיקיית [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal).

😀 הצלחת לחבר את המכשיר שלך לשרת MQTT.

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.