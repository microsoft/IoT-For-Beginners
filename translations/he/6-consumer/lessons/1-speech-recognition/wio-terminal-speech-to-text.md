<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-27T22:40:21+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "he"
}
-->
# דיבור לטקסט - Wio Terminal

בחלק זה של השיעור, תכתבו קוד להמרת דיבור באודיו שנלכד לטקסט באמצעות שירות הדיבור.

## שליחת האודיו לשירות הדיבור

ניתן לשלוח את האודיו לשירות הדיבור באמצעות ה-REST API. כדי להשתמש בשירות הדיבור, תחילה יש לבקש אסימון גישה, ולאחר מכן להשתמש באסימון זה כדי לגשת ל-REST API. אסימוני גישה אלו פגים לאחר 10 דקות, ולכן הקוד שלכם צריך לבקש אותם באופן קבוע כדי להבטיח שהם תמיד מעודכנים.

### משימה - קבלת אסימון גישה

1. פתחו את פרויקט `smart-timer` אם הוא עדיין לא פתוח.

1. הוסיפו את התלויות הבאות לקובץ `platformio.ini` כדי לגשת ל-WiFi ולטפל ב-JSON:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. הוסיפו את הקוד הבא לקובץ הכותרת `config.h`:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    החליפו `<SSID>` ו-`<PASSWORD>` בערכים הרלוונטיים עבור ה-WiFi שלכם.

    החליפו `<API_KEY>` במפתח ה-API של משאב שירות הדיבור שלכם. החליפו `<LOCATION>` במיקום שבו יצרתם את משאב שירות הדיבור.

    החליפו `<LANGUAGE>` בשם האזורי של השפה שבה תדברו, לדוגמה `en-GB` עבור אנגלית, או `zn-HK` עבור קנטונזית. ניתן למצוא רשימה של השפות הנתמכות ושמות האזורים שלהן בתיעוד [Language and voice support במיקרוסופט](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    הקבוע `TOKEN_URL` הוא ה-URL של מנפיק האסימונים ללא המיקום. זה ישולב עם המיקום מאוחר יותר כדי לקבל את ה-URL המלא.

1. כמו בחיבור ל-Custom Vision, תצטרכו להשתמש בחיבור HTTPS כדי להתחבר לשירות מנפיק האסימונים. הוסיפו את הקוד הבא לסוף `config.h`:

    ```cpp
    const char *TOKEN_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "MIIF8zCCBNugAwIBAgIQAueRcfuAIek/4tmDg0xQwDANBgkqhkiG9w0BAQwFADBh\r\n"
        "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\r\n"
        "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBH\r\n"
        "MjAeFw0yMDA3MjkxMjMwMDBaFw0yNDA2MjcyMzU5NTlaMFkxCzAJBgNVBAYTAlVT\r\n"
        "MR4wHAYDVQQKExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xKjAoBgNVBAMTIU1pY3Jv\r\n"
        "c29mdCBBenVyZSBUTFMgSXNzdWluZyBDQSAwNjCCAiIwDQYJKoZIhvcNAQEBBQAD\r\n"
        "ggIPADCCAgoCggIBALVGARl56bx3KBUSGuPc4H5uoNFkFH4e7pvTCxRi4j/+z+Xb\r\n"
        "wjEz+5CipDOqjx9/jWjskL5dk7PaQkzItidsAAnDCW1leZBOIi68Lff1bjTeZgMY\r\n"
        "iwdRd3Y39b/lcGpiuP2d23W95YHkMMT8IlWosYIX0f4kYb62rphyfnAjYb/4Od99\r\n"
        "ThnhlAxGtfvSbXcBVIKCYfZgqRvV+5lReUnd1aNjRYVzPOoifgSx2fRyy1+pO1Uz\r\n"
        "aMMNnIOE71bVYW0A1hr19w7kOb0KkJXoALTDDj1ukUEDqQuBfBxReL5mXiu1O7WG\r\n"
        "0vltg0VZ/SZzctBsdBlx1BkmWYBW261KZgBivrql5ELTKKd8qgtHcLQA5fl6JB0Q\r\n"
        "gs5XDaWehN86Gps5JW8ArjGtjcWAIP+X8CQaWfaCnuRm6Bk/03PQWhgdi84qwA0s\r\n"
        "sRfFJwHUPTNSnE8EiGVk2frt0u8PG1pwSQsFuNJfcYIHEv1vOzP7uEOuDydsmCjh\r\n"
        "lxuoK2n5/2aVR3BMTu+p4+gl8alXoBycyLmj3J/PUgqD8SL5fTCUegGsdia/Sa60\r\n"
        "N2oV7vQ17wjMN+LXa2rjj/b4ZlZgXVojDmAjDwIRdDUujQu0RVsJqFLMzSIHpp2C\r\n"
        "Zp7mIoLrySay2YYBu7SiNwL95X6He2kS8eefBBHjzwW/9FxGqry57i71c2cDAgMB\r\n"
        "AAGjggGtMIIBqTAdBgNVHQ4EFgQU1cFnOsKjnfR3UltZEjgp5lVou6UwHwYDVR0j\r\n"
        "BBgwFoAUTiJUIBiV5uNu5g/6+rkS7QYXjzkwDgYDVR0PAQH/BAQDAgGGMB0GA1Ud\r\n"
        "JQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjASBgNVHRMBAf8ECDAGAQH/AgEAMHYG\r\n"
        "CCsGAQUFBwEBBGowaDAkBggrBgEFBQcwAYYYaHR0cDovL29jc3AuZGlnaWNlcnQu\r\n"
        "Y29tMEAGCCsGAQUFBzAChjRodHRwOi8vY2FjZXJ0cy5kaWdpY2VydC5jb20vRGln\r\n"
        "aUNlcnRHbG9iYWxSb290RzIuY3J0MHsGA1UdHwR0MHIwN6A1oDOGMWh0dHA6Ly9j\r\n"
        "cmwzLmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5jcmwwN6A1oDOG\r\n"
        "MWh0dHA6Ly9jcmw0LmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5j\r\n"
        "cmwwHQYDVR0gBBYwFDAIBgZngQwBAgEwCAYGZ4EMAQICMBAGCSsGAQQBgjcVAQQD\r\n"
        "AgEAMA0GCSqGSIb3DQEBDAUAA4IBAQB2oWc93fB8esci/8esixj++N22meiGDjgF\r\n"
        "+rA2LUK5IOQOgcUSTGKSqF9lYfAxPjrqPjDCUPHCURv+26ad5P/BYtXtbmtxJWu+\r\n"
        "cS5BhMDPPeG3oPZwXRHBJFAkY4O4AF7RIAAUW6EzDflUoDHKv83zOiPfYGcpHc9s\r\n"
        "kxAInCedk7QSgXvMARjjOqdakor21DTmNIUotxo8kHv5hwRlGhBJwps6fEVi1Bt0\r\n"
        "trpM/3wYxlr473WSPUFZPgP1j519kLpWOJ8z09wxay+Br29irPcBYv0GMXlHqThy\r\n"
        "8y4m/HyTQeI2IMvMrQnwqPpY+rLIXyviI2vLoI+4xKE4Rn38ZZ8m\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

    זהו אותו אישור שהשתמשתם בו כאשר התחברתם ל-Custom Vision.

1. הוסיפו include עבור קובץ הכותרת של WiFi וקובץ הכותרת של config לראש קובץ `main.cpp`:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. הוסיפו קוד להתחברות ל-WiFi ב-`main.cpp` מעל הפונקציה `setup`:

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

1. קראו לפונקציה זו מתוך הפונקציה `setup` לאחר שהחיבור הסדרתי הוקם:

    ```cpp
    connectWiFi();
    ```

1. צרו קובץ כותרת חדש בתיקיית `src` בשם `speech_to_text.h`. בקובץ כותרת זה, הוסיפו את הקוד הבא:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClientSecure.h>
    
    #include "config.h"
    #include "mic.h"
    
    class SpeechToText
    {
    public:

    private:

    };

    SpeechToText speechToText;
    ```

    זה כולל כמה קבצי כותרת נחוצים לחיבור HTTP, קונפיגורציה וקובץ הכותרת `mic.h`, ומגדיר מחלקה בשם `SpeechToText`, לפני הכרזה על מופע של מחלקה זו שניתן להשתמש בו מאוחר יותר.

1. הוסיפו את שני השדות הבאים לחלק ה-`private` של מחלקה זו:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client` הוא WiFi Client שמשתמש ב-HTTPS וישמש לקבלת אסימון הגישה. אסימון זה יישמר לאחר מכן ב-`_access_token`.

1. הוסיפו את השיטה הבאה לחלק ה-`private`:

    ```cpp
    String getAccessToken()
    {
        char url[128];
        sprintf(url, TOKEN_URL, SPEECH_LOCATION);
    
        HTTPClient httpClient;
        httpClient.begin(_token_client, url);
    
        httpClient.addHeader("Ocp-Apim-Subscription-Key", SPEECH_API_KEY);
        int httpResultCode = httpClient.POST("{}");
    
        if (httpResultCode != 200)
        {
            Serial.println("Error getting access token, trying again...");
            delay(10000);
            return getAccessToken();
        }
    
        Serial.println("Got access token.");
        String result = httpClient.getString();
    
        httpClient.end();
    
        return result;
    }
    ```

    קוד זה בונה את ה-URL עבור ה-API של מנפיק האסימונים באמצעות המיקום של משאב הדיבור. לאחר מכן הוא יוצר `HTTPClient` לביצוע הבקשה, ומגדיר אותו להשתמש ב-WiFi client שהוגדר עם האישור של מנפיק האסימונים. הוא מגדיר את מפתח ה-API ככותרת לבקשה. לאחר מכן הוא מבצע בקשת POST לקבלת האישור, ומנסה שוב אם יש שגיאות. לבסוף, אסימון הגישה מוחזר.

1. לחלק ה-`public`, הוסיפו שיטה לקבלת אסימון הגישה. זה יידרש בשיעורים הבאים להמרת טקסט לדיבור.

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. לחלק ה-`public`, הוסיפו שיטת `init` שמגדירה את ה-token client:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    זה מגדיר את האישור על ה-WiFi client, ואז מקבל את אסימון הגישה.

1. ב-`main.cpp`, הוסיפו את קובץ הכותרת החדש הזה להוראות ה-include:

    ```cpp
    #include "speech_to_text.h"
    ```

1. אתחלו את מחלקת `SpeechToText` בסוף הפונקציה `setup`, לאחר הקריאה ל-`mic.init` אך לפני שכותבים `Ready` למוניטור הסדרתי:

    ```cpp
    speechToText.init();
    ```

### משימה - קריאת אודיו מזיכרון הפלאש

1. בחלק מוקדם יותר של השיעור, האודיו הוקלט לזיכרון הפלאש. אודיו זה יצטרך להישלח ל-REST API של שירות הדיבור, ולכן יש לקרוא אותו מזיכרון הפלאש. לא ניתן לטעון אותו למאגר בזיכרון מכיוון שהוא יהיה גדול מדי. מחלקת `HTTPClient` שמבצעת קריאות REST יכולה להזרים נתונים באמצעות Arduino Stream - מחלקה שיכולה לטעון נתונים בחתיכות קטנות, ולשלוח את החתיכות אחת בכל פעם כחלק מהבקשה. בכל פעם שקוראים ל-`read` על stream, הוא מחזיר את הבלוק הבא של הנתונים. ניתן ליצור Arduino stream שיכול לקרוא מזיכרון הפלאש. צרו קובץ חדש בשם `flash_stream.h` בתיקיית `src`, והוסיפו אליו את הקוד הבא:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <HTTPClient.h>
    #include <sfud.h>

    #include "config.h"
    
    class FlashStream : public Stream
    {
    public:
        virtual size_t write(uint8_t val)
        {    
        }
    
        virtual int available()
        {
        }
    
        virtual int read()
        {
        }
    
        virtual int peek()
        {
        }
    private:
    
    };
    ```

    זה מצהיר על מחלקת `FlashStream`, שיורשת ממחלקת `Stream` של Arduino. זו מחלקה מופשטת - מחלקות יורשות צריכות לממש כמה שיטות לפני שניתן יהיה ליצור מופע של המחלקה, ושיטות אלו מוגדרות במחלקה זו.

    ✅ קראו עוד על Arduino Streams בתיעוד [Arduino Stream](https://www.arduino.cc/reference/en/language/functions/communication/stream/)

1. הוסיפו את השדות הבאים לחלק ה-`private`:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    זה מגדיר מאגר זמני לאחסון נתונים שנקראו מזיכרון הפלאש, יחד עם שדות לאחסון המיקום הנוכחי בעת קריאה מהמאגר, הכתובת הנוכחית לקריאה מזיכרון הפלאש, ומכשיר זיכרון הפלאש.

1. בחלק ה-`private`, הוסיפו את השיטה הבאה:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    קוד זה קורא מזיכרון הפלאש בכתובת הנוכחית ושומר את הנתונים במאגר. לאחר מכן הוא מגדיל את הכתובת, כך שהקריאה הבאה תקרא את הבלוק הבא של הזיכרון. המאגר מוגדר בגודל המבוסס על החתיכה הגדולה ביותר ש-`HTTPClient` ישלח ל-REST API בכל פעם.

    > 💁 מחיקת זיכרון פלאש חייבת להיעשות באמצעות גודל גרעין, קריאה לעומת זאת לא.

1. בחלק ה-`public` של מחלקה זו, הוסיפו בנאי:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    בנאי זה מגדיר את כל השדות להתחיל קריאה מתחילת בלוק זיכרון הפלאש, וטוען את החתיכה הראשונה של הנתונים למאגר.

1. מימוש שיטת `write`. stream זה יקרא נתונים בלבד, ולכן ניתן להשאיר פונקציה זו ריקה ולהחזיר 0:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. מימוש שיטת `peek`. שיטה זו מחזירה את הנתונים במיקום הנוכחי מבלי להזיז את ה-stream קדימה. קריאה ל-`peek` מספר פעמים תחזיר תמיד את אותם נתונים כל עוד לא נקראו נתונים מה-stream.

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. מימוש פונקציית `available`. פונקציה זו מחזירה כמה בתים ניתן לקרוא מה-stream, או -1 אם ה-stream הושלם. עבור מחלקה זו, המקסימום הזמין לא יהיה יותר מגודל החתיכה של HTTPClient. כאשר stream זה משמש ב-HTTP client, הוא קורא לפונקציה זו כדי לראות כמה נתונים זמינים, ואז מבקש כמות זו לשליחה ל-REST API. אנחנו לא רוצים שכל חתיכה תהיה יותר מגודל החתיכה של HTTP client, ולכן אם יותר מזה זמין, גודל החתיכה מוחזר. אם פחות, אז מה שזמין מוחזר. ברגע שכל הנתונים הוזרמו, מוחזר -1.

    ```cpp
    virtual int available()
    {
        int remaining = BUFFER_SIZE - ((_flash_address - HTTP_TCP_BUFFER_SIZE) + _pos);
        int bytes_available = min(HTTP_TCP_BUFFER_SIZE, remaining);

        if (bytes_available == 0)
        {
            bytes_available = -1;
        }

        return bytes_available;
    }
    ```

1. מימוש שיטת `read` להחזרת הבת הבא מהמאגר, תוך הגדלת המיקום. אם המיקום חורג מגודל המאגר, הוא מאכלס את המאגר עם הבלוק הבא מזיכרון הפלאש ומאפס את המיקום.

    ```cpp
    virtual int read()
    {
        int retVal = _buffer[_pos++];

        if (_pos == HTTP_TCP_BUFFER_SIZE)
        {
            populateBuffer();
        }

        return retVal;
    }
    ```

1. בקובץ הכותרת `speech_to_text.h`, הוסיפו הוראת include עבור קובץ הכותרת החדש הזה:

    ```cpp
    #include "flash_stream.h"
    ```

### משימה - המרת הדיבור לטקסט

1. ניתן להמיר את הדיבור לטקסט על ידי שליחת האודיו לשירות הדיבור דרך REST API. ל-REST API זה יש אישור שונה ממנפיק האסימונים, ולכן הוסיפו את הקוד הבא לקובץ הכותרת `config.h` כדי להגדיר אישור זה:

    ```cpp
    const char *SPEECH_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "MIIF8zCCBNugAwIBAgIQCq+mxcpjxFFB6jvh98dTFzANBgkqhkiG9w0BAQwFADBh\r\n"
        "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\r\n"
        "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBH\r\n"
        "MjAeFw0yMDA3MjkxMjMwMDBaFw0yNDA2MjcyMzU5NTlaMFkxCzAJBgNVBAYTAlVT\r\n"
        "MR4wHAYDVQQKExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xKjAoBgNVBAMTIU1pY3Jv\r\n"
        "c29mdCBBenVyZSBUTFMgSXNzdWluZyBDQSAwMTCCAiIwDQYJKoZIhvcNAQEBBQAD\r\n"
        "ggIPADCCAgoCggIBAMedcDrkXufP7pxVm1FHLDNA9IjwHaMoaY8arqqZ4Gff4xyr\r\n"
        "RygnavXL7g12MPAx8Q6Dd9hfBzrfWxkF0Br2wIvlvkzW01naNVSkHp+OS3hL3W6n\r\n"
        "l/jYvZnVeJXjtsKYcXIf/6WtspcF5awlQ9LZJcjwaH7KoZuK+THpXCMtzD8XNVdm\r\n"
        "GW/JI0C/7U/E7evXn9XDio8SYkGSM63aLO5BtLCv092+1d4GGBSQYolRq+7Pd1kR\r\n"
        "EkWBPm0ywZ2Vb8GIS5DLrjelEkBnKCyy3B0yQud9dpVsiUeE7F5sY8Me96WVxQcb\r\n"
        "OyYdEY/j/9UpDlOG+vA+YgOvBhkKEjiqygVpP8EZoMMijephzg43b5Qi9r5UrvYo\r\n"
        "o19oR/8pf4HJNDPF0/FJwFVMW8PmCBLGstin3NE1+NeWTkGt0TzpHjgKyfaDP2tO\r\n"
        "4bCk1G7pP2kDFT7SYfc8xbgCkFQ2UCEXsaH/f5YmpLn4YPiNFCeeIida7xnfTvc4\r\n"
        "7IxyVccHHq1FzGygOqemrxEETKh8hvDR6eBdrBwmCHVgZrnAqnn93JtGyPLi6+cj\r\n"
        "WGVGtMZHwzVvX1HvSFG771sskcEjJxiQNQDQRWHEh3NxvNb7kFlAXnVdRkkvhjpR\r\n"
        "GchFhTAzqmwltdWhWDEyCMKC2x/mSZvZtlZGY+g37Y72qHzidwtyW7rBetZJAgMB\r\n"
        "AAGjggGtMIIBqTAdBgNVHQ4EFgQUDyBd16FXlduSzyvQx8J3BM5ygHYwHwYDVR0j\r\n"
        "BBgwFoAUTiJUIBiV5uNu5g/6+rkS7QYXjzkwDgYDVR0PAQH/BAQDAgGGMB0GA1Ud\r\n"
        "JQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjASBgNVHRMBAf8ECDAGAQH/AgEAMHYG\r\n"
        "CCsGAQUFBwEBBGowaDAkBggrBgEFBQcwAYYYaHR0cDovL29jc3AuZGlnaWNlcnQu\r\n"
        "Y29tMEAGCCsGAQUFBzAChjRodHRwOi8vY2FjZXJ0cy5kaWdpY2VydC5jb20vRGln\r\n"
        "aUNlcnRHbG9iYWxSb290RzIuY3J0MHsGA1UdHwR0MHIwN6A1oDOGMWh0dHA6Ly9j\r\n"
        "cmwzLmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5jcmwwN6A1oDOG\r\n"
        "MWh0dHA6Ly9jcmw0LmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5j\r\n"
        "cmwwHQYDVR0gBBYwFDAIBgZngQwBAgEwCAYGZ4EMAQICMBAGCSsGAQQBgjcVAQQD\r\n"
        "AgEAMA0GCSqGSIb3DQEBDAUAA4IBAQAlFvNh7QgXVLAZSsNR2XRmIn9iS8OHFCBA\r\n"
        "WxKJoi8YYQafpMTkMqeuzoL3HWb1pYEipsDkhiMnrpfeYZEA7Lz7yqEEtfgHcEBs\r\n"
        "K9KcStQGGZRfmWU07hPXHnFz+5gTXqzCE2PBMlRgVUYJiA25mJPXfB00gDvGhtYa\r\n"
        "+mENwM9Bq1B9YYLyLjRtUz8cyGsdyTIG/bBM/Q9jcV8JGqMU/UjAdh1pFyTnnHEl\r\n"
        "Y59Npi7F87ZqYYJEHJM2LGD+le8VsHjgeWX2CJQko7klXvcizuZvUEDTjHaQcs2J\r\n"
        "+kPgfyMIOY1DMJ21NxOJ2xPRC/wAh/hzSBRVtoAnyuxtkZ4VjIOh\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. הוסיפו קבוע לקובץ זה עבור ה-URL של הדיבור ללא המיקום. זה ישולב עם המיקום והשפה מאוחר יותר כדי לקבל את ה-URL המלא.

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. בקובץ הכותרת `speech_to_text.h`, בחלק ה-`private` של מחלקת `SpeechToText`, הגדירו שדה עבור WiFi Client שמשתמש באישור הדיבור:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. בשיטת `init`, הגדירו את האישור על WiFi Client זה:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. הוסיפו את הקוד הבא לחלק ה-`public` של מחלקת `SpeechToText` כדי להגדיר שיטה להמרת דיבור לטקסט:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. הוסיפו את הקוד הבא לשיטה זו כדי ליצור HTTP client באמצעות ה-WiFi client שהוגדר עם אישור הדיבור, ובשימוש ב-URL של הדיבור שהוגדר עם המיקום והשפה:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. יש להגדיר כמה כותרות על החיבור:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    זה מגדיר כותרות עבור האימות באמצעות אסימון הגישה, פורמט האודיו באמצעות קצב הדגימה, ומגדיר שהלקוח מצפה לתוצאה כ-JSON.

1. לאחר מכן, הוסיפו את הקוד הבא לביצוע קריאת REST API:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    זה יוצר `FlashStream` ומשתמש בו להזרים נתונים ל-REST API.

1. מתחת לזה, הוסיפו את הקוד הבא:

    ```cpp
    String text = "";

    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonObject obj = doc.as<JsonObject>();
        text = obj["DisplayText"].as<String>();
    }
    else if (httpResponseCode == 401)
    {
        Serial.println("Access token expired, trying again with a new token");
        _access_token = getAccessToken();
        return convertSpeechToText();
    }
    else
    {
        Serial.print("Failed to convert text to speech - error ");
        Serial.println(httpResponseCode);
    }
    ```

    קוד זה בודק את קוד התגובה.

    אם הוא 200, הקוד להצלחה, אז התוצאה נשלפת, מפוענחת מ-JSON, ותכונת `DisplayText` מוגדרת במשתנה `text`. זו התכונה שבה מוחזר הטקסט של הדיבור.

    אם קוד התגובה הוא 401, אז אסימון הגישה פג תוקף (אסימונים אלו תקפים רק ל-10 דקות). אסימון גישה חדש מתבקש, והקריאה מתבצעת שוב.

    אחרת, שגיאה נשלחת למוניטור הסדרתי, ו-`text` נשאר ריק.

1. הוסיפו את הקוד הבא לסוף שיטה זו כדי לסגור את HTTP client ולהחזיר את הטקסט:

    ```cpp
    httpClient.end();

    return text;
    ```

1. ב-`main.cpp` קראו לשיטה החדשה `convertSpeechToText` בפונקציה `processAudio`, ואז רשמו את הדיבור למוניטור הסדרתי:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. בנו את הקוד הזה, העלו אותו ל-Wio Terminal שלכם ובדקו אותו דרך המוניטור הסדרתי. ברגע שתראו `Ready` במוניטור הסדרתי, לחצו על כפתור C (הכפתור בצד השמאלי, הקרוב ביותר למתג ההפעלה), ודברו. 4 שניות של אודיו יוקלטו, ואז יומרו לטקסט.

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
    ```

> 💁 ניתן למצוא את הקוד הזה בתיקייה [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal).

😀 התוכנית להמרת דיבור לטקסט הצליחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.