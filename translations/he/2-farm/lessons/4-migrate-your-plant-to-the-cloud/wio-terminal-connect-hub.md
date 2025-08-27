<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-27T21:34:14+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "he"
}
-->
# חבר את מכשיר ה-IoT שלך לענן - Wio Terminal

בחלק זה של השיעור, תחבר את ה-Wio Terminal שלך ל-IoT Hub, כדי לשלוח טלמטריה ולקבל פקודות.

## חיבור המכשיר ל-IoT Hub

השלב הבא הוא לחבר את המכשיר שלך ל-IoT Hub.

### משימה - חיבור ל-IoT Hub

1. פתח את פרויקט `soil-moisture-sensor` ב-VS Code.

1. פתח את קובץ `platformio.ini`. הסר את תלות הספרייה `knolleary/PubSubClient`. ספרייה זו שימשה לחיבור לשרת MQTT ציבורי, ואינה נחוצה לחיבור ל-IoT Hub.

1. הוסף את תלות הספריות הבאות:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    ספריית `Seeed Arduino RTC` מספקת קוד לתקשורת עם שעון זמן אמת ב-Wio Terminal, המשמש למעקב אחר הזמן. שאר הספריות מאפשרות למכשיר ה-IoT שלך להתחבר ל-IoT Hub.

1. הוסף את השורה הבאה לתחתית קובץ `platformio.ini`:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    זה מגדיר דגל קומפילציה הנדרש בעת קומפילציה של קוד Arduino IoT Hub.

1. פתח את קובץ הכותרת `config.h`. הסר את כל הגדרות ה-MQTT והוסף את הקבוע הבא עבור מחרוזת החיבור של המכשיר:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    החלף את `<connection string>` במחרוזת החיבור של המכשיר שהעתקת קודם.

1. החיבור ל-IoT Hub משתמש בטוקן מבוסס זמן. משמעות הדבר היא שמכשיר ה-IoT צריך לדעת את הזמן הנוכחי. בניגוד למערכות הפעלה כמו Windows, macOS או Linux, מיקרו-בקרים אינם מסנכרנים את הזמן הנוכחי באופן אוטומטי דרך האינטרנט. לכן תצטרך להוסיף קוד לקבלת הזמן הנוכחי משרת [NTP](https://wikipedia.org/wiki/Network_Time_Protocol). לאחר שהזמן התקבל, ניתן לאחסן אותו בשעון זמן אמת ב-Wio Terminal, מה שמאפשר לבקש את הזמן הנכון במועד מאוחר יותר, בהנחה שהמכשיר לא איבד כוח. הוסף קובץ חדש בשם `ntp.h` עם הקוד הבא:

    ```cpp
    #pragma once
    
    #include "DateTime.h"
    #include <time.h>
    #include "samd/NTPClientAz.h"
    #include <sys/time.h>

    static void initTime()
    {
        WiFiUDP _udp;
        time_t epochTime = (time_t)-1;
        NTPClientAz ntpClient;

        ntpClient.begin();

        while (true)
        {
            epochTime = ntpClient.getEpochTime("0.pool.ntp.org");

            if (epochTime == (time_t)-1)
            {
                Serial.println("Fetching NTP epoch time failed! Waiting 2 seconds to retry.");
                delay(2000);
            }
            else
            {
                Serial.print("Fetched NTP epoch time is: ");

                char buff[32];
                sprintf(buff, "%.f", difftime(epochTime, (time_t)0));
                Serial.println(buff);
                break;
            }
        }

        ntpClient.end();

        struct timeval tv;
        tv.tv_sec = epochTime;
        tv.tv_usec = 0;

        settimeofday(&tv, NULL);
    }
    ```

    פרטי הקוד הזה אינם במסגרת השיעור. הוא מגדיר פונקציה בשם `initTime` שמקבלת את הזמן הנוכחי משרת NTP ומשתמשת בו כדי להגדיר את השעון ב-Wio Terminal.

1. פתח את קובץ `main.cpp` והסר את כל קוד ה-MQTT, כולל קובץ הכותרת `PubSubClient.h`, הכרזת המשתנה `PubSubClient`, השיטות `reconnectMQTTClient` ו-`createMQTTClient`, וכל קריאה למשתנים ולשיטות אלו. קובץ זה צריך להכיל רק קוד לחיבור ל-WiFi, קבלת לחות הקרקע ויצירת מסמך JSON עם הנתונים.

1. הוסף את הוראות `#include` הבאות לראש קובץ `main.cpp` כדי לכלול קובצי כותרת עבור ספריות IoT Hub ולצורך הגדרת הזמן:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. הוסף את הקריאה הבאה לסוף פונקציית `setup` כדי להגדיר את הזמן הנוכחי:

    ```cpp
    initTime();
    ```

1. הוסף את הכרזת המשתנה הבאה לראש הקובץ, ממש מתחת להוראות ה-`include`:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    זה מכריז על `IOTHUB_DEVICE_CLIENT_LL_HANDLE`, ידית לחיבור ל-IoT Hub.

1. מתחת לכך, הוסף את הקוד הבא:

    ```cpp
    static void connectionStatusCallback(IOTHUB_CLIENT_CONNECTION_STATUS result, IOTHUB_CLIENT_CONNECTION_STATUS_REASON reason, void *user_context)
    {
        if (result == IOTHUB_CLIENT_CONNECTION_AUTHENTICATED)
        {
            Serial.println("The device client is connected to iothub");
        }
        else
        {
            Serial.println("The device client has been disconnected");
        }
    }
    ```

    זה מגדיר פונקציית callback שתיקרא כאשר החיבור ל-IoT Hub משנה סטטוס, כמו התחברות או ניתוק. הסטטוס נשלח לפורט הסדרתי.

1. מתחת לכך, הוסף פונקציה לחיבור ל-IoT Hub:

    ```cpp
    void connectIoTHub()
    {
        IoTHub_Init();
    
        _device_ll_handle = IoTHubDeviceClient_LL_CreateFromConnectionString(CONNECTION_STRING, MQTT_Protocol);
        
        if (_device_ll_handle == NULL)
        {
            Serial.println("Failure creating Iothub device. Hint: Check your connection string.");
            return;
        }
    
        IoTHubDeviceClient_LL_SetConnectionStatusCallback(_device_ll_handle, connectionStatusCallback, NULL);
    }
    ```

    קוד זה מאתחל את קוד ספריית IoT Hub, ואז יוצר חיבור באמצעות מחרוזת החיבור בקובץ הכותרת `config.h`. חיבור זה מבוסס על MQTT. אם החיבור נכשל, הדבר נשלח לפורט הסדרתי - אם אתה רואה זאת בפלט, בדוק את מחרוזת החיבור. לבסוף, מוגדר ה-callback לסטטוס החיבור.

1. קרא לפונקציה זו בפונקציית `setup` מתחת לקריאה ל-`initTime`:

    ```cpp
    connectIoTHub();
    ```

1. בדיוק כמו עם לקוח ה-MQTT, קוד זה פועל על שרשור יחיד ולכן זקוק לזמן לעיבוד הודעות שנשלחות על ידי ה-hub ול-hub. הוסף את השורה הבאה לראש פונקציית `loop` כדי לעשות זאת:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. בנה והעלה את הקוד הזה. תראה את החיבור במוניטור הסדרתי:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    בפלט תוכל לראות את זמן ה-NTP מתקבל, ואחריו חיבור לקוח המכשיר. זה יכול לקחת כמה שניות להתחבר, כך שתוכל לראות את לחות הקרקע בפלט בזמן שהמכשיר מתחבר.

    > 💁 תוכל להמיר את זמן ה-UNIX של ה-NTP לגרסה קריאה יותר באמצעות אתר כמו [unixtimestamp.com](https://www.unixtimestamp.com)

## שליחת טלמטריה

עכשיו כשהמכשיר שלך מחובר, תוכל לשלוח טלמטריה ל-IoT Hub במקום לשרת ה-MQTT.

### משימה - שליחת טלמטריה

1. הוסף את הפונקציה הבאה מעל פונקציית `setup`:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    קוד זה יוצר הודעת IoT Hub ממחרוזת שעוברת כפרמטר, שולח אותה ל-hub, ואז מנקה את אובייקט ההודעה.

1. קרא לקוד זה בפונקציית `loop`, מיד לאחר השורה שבה הטלמטריה נשלחת לפורט הסדרתי:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## טיפול בפקודות

המכשיר שלך צריך לטפל בפקודה מהקוד בשרת כדי לשלוט בממסר. זה נשלח כבקשת שיטה ישירה.

### משימה - טיפול בבקשת שיטה ישירה

1. הוסף את הקוד הבא לפני פונקציית `connectIoTHub`:

    ```cpp
    int directMethodCallback(const char *method_name, const unsigned char *payload, size_t size, unsigned char **response, size_t *response_size, void *userContextCallback)
    {
        Serial.printf("Direct method received %s\r\n", method_name);
    
        if (strcmp(method_name, "relay_on") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, HIGH);
        }
        else if (strcmp(method_name, "relay_off") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, LOW);
        }
    }
    ```

    קוד זה מגדיר פונקציית callback שהספרייה של IoT Hub יכולה לקרוא כאשר היא מקבלת בקשת שיטה ישירה. השיטה המבוקשת נשלחת בפרמטר `method_name`. פונקציה זו מדפיסה את השיטה שנקראה לפורט הסדרתי, ואז מדליקה או מכבה את הממסר בהתאם לשם השיטה.

    > 💁 ניתן גם ליישם זאת בשיטה ישירה אחת בלבד, על ידי העברת מצב הרצוי של הממסר במטען שניתן להעביר עם בקשת השיטה וזמין מהפרמטר `payload`.

1. הוסף את הקוד הבא לסוף פונקציית `directMethodCallback`:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    בקשות שיטה ישירה זקוקות לתגובה, והתגובה מורכבת משני חלקים - תגובה כטקסט וקוד חזרה. קוד זה ייצור תוצאה כמסמך JSON הבא:

    ```JSON
    {
        "Result": ""
    }
    ```

    זה מועתק לאחר מכן לפרמטר `response`, וגודל התגובה מוגדר בפרמטר `response_size`. קוד זה מחזיר `IOTHUB_CLIENT_OK` כדי להראות שהשיטה טופלה כראוי.

1. חבר את ה-callback על ידי הוספת השורה הבאה לסוף פונקציית `connectIoTHub`:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. פונקציית `loop` תקרא לפונקציה `IoTHubDeviceClient_LL_DoWork` כדי לעבד אירועים שנשלחים על ידי IoT Hub. זה נקרא רק כל 10 שניות בגלל ה-`delay`, כלומר שיטות ישירות מעובדות רק כל 10 שניות. כדי להפוך זאת ליעיל יותר, ניתן ליישם את ההשהיה של 10 שניות כהשהיות קצרות רבות, תוך קריאה ל-`IoTHubDeviceClient_LL_DoWork` בכל פעם. לשם כך, הוסף את הקוד הבא מעל פונקציית `loop`:

    ```cpp
    void work_delay(int delay_time)
    {
        int current = 0;
        do
        {
            IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
            delay(100);
            current += 100;
        } while (current < delay_time);
    }
    ```

    קוד זה יפעל בלולאה חוזרת, יקרא ל-`IoTHubDeviceClient_LL_DoWork` ויעכב למשך 100ms בכל פעם. הוא יעשה זאת כמה פעמים שצריך כדי לעכב למשך הזמן שניתן בפרמטר `delay_time`. משמעות הדבר היא שהמכשיר ממתין לכל היותר 100ms לעיבוד בקשות שיטה ישירה.

1. בפונקציית `loop`, הסר את הקריאה ל-`IoTHubDeviceClient_LL_DoWork`, והחלף את הקריאה ל-`delay(10000)` בקוד הבא כדי לקרוא לפונקציה החדשה הזו:

    ```cpp
    work_delay(10000);
    ```

> 💁 תוכל למצוא את הקוד הזה בתיקיית [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal).

😀 תוכנית חיישן לחות הקרקע שלך מחוברת ל-IoT Hub!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.