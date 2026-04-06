# סיווג תמונה - Wio Terminal

בחלק זה של השיעור, תשלחו את התמונה שצולמה על ידי המצלמה לשירות Custom Vision כדי לסווג אותה.

## סיווג תמונה

שירות Custom Vision כולל API מסוג REST שניתן לקרוא לו מ-Wio Terminal כדי לסווג תמונות. ה-REST API נגיש דרך חיבור HTTPS - חיבור HTTP מאובטח.

כאשר מתקשרים עם נקודות קצה של HTTPS, קוד הלקוח צריך לבקש את תעודת המפתח הציבורי מהשרת שאליו ניגשים, ולהשתמש בה כדי להצפין את התעבורה שהוא שולח. דפדפן האינטרנט שלכם עושה זאת באופן אוטומטי, אך מיקרו-בקרים לא. תצטרכו לבקש את התעודה הזו באופן ידני ולהשתמש בה כדי ליצור חיבור מאובטח ל-REST API. תעודות אלו אינן משתנות, ולכן לאחר שיש לכם תעודה, ניתן להטמיע אותה בקוד האפליקציה שלכם.

תעודות אלו מכילות מפתחות ציבוריים, ואין צורך לשמור עליהן מאובטחות. ניתן להשתמש בהן בקוד המקור ולשתף אותן בפומבי במקומות כמו GitHub.

### משימה - הגדרת לקוח SSL

1. פתחו את פרויקט האפליקציה `fruit-quality-detector` אם הוא עדיין לא פתוח.

1. פתחו את קובץ הכותרת `config.h`, והוסיפו את השורות הבאות:

    ```cpp
    const char *CERTIFICATE =
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

    זוהי *תעודת Microsoft Azure DigiCert Global Root G2* - אחת מהתעודות המשמשות שירותי Azure רבים ברחבי העולם.

    > 💁 כדי לראות שזו התעודה שיש להשתמש בה, הריצו את הפקודה הבאה ב-macOS או Linux. אם אתם משתמשים ב-Windows, תוכלו להריץ את הפקודה הזו באמצעות [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn):
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > הפלט יציג את תעודת DigiCert Global Root G2.

1. פתחו את `main.cpp` והוסיפו את הוראת ההכללה הבאה:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. מתחת להוראות ההכללה, הכריזו על מופע של `WifiClientSecure`:

    ```cpp
    WiFiClientSecure client;
    ```

    מחלקה זו מכילה קוד לתקשורת עם נקודות קצה של רשת באמצעות HTTPS.

1. בתוך המתודה `connectWiFi`, הגדירו את ה-WiFiClientSecure לשימוש בתעודת DigiCert Global Root G2:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### משימה - סיווג תמונה

1. הוסיפו את השורה הבאה כרשומה נוספת לרשימת `lib_deps` בקובץ `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    זה מייבא את [ArduinoJson](https://arduinojson.org), ספריית JSON עבור Arduino, שתשמש לפענוח תגובת ה-JSON מה-REST API.

1. ב-`config.h`, הוסיפו קבועים עבור כתובת ה-URL של התחזית והמפתח משירות Custom Vision:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    החליפו `<PREDICTION_URL>` בכתובת ה-URL של התחזית מ-Custom Vision. החליפו `<PREDICTION_KEY>` במפתח התחזית.

1. ב-`main.cpp`, הוסיפו הוראת הכללה עבור ספריית ArduinoJson:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. הוסיפו את הפונקציה הבאה ל-`main.cpp`, מעל הפונקציה `buttonPressed`.

    ```cpp
    void classifyImage(byte *buffer, uint32_t length)
    {
        HTTPClient httpClient;
        httpClient.begin(client, PREDICTION_URL);
        httpClient.addHeader("Content-Type", "application/octet-stream");
        httpClient.addHeader("Prediction-Key", PREDICTION_KEY);
    
        int httpResponseCode = httpClient.POST(buffer, length);
    
        if (httpResponseCode == 200)
        {
            String result = httpClient.getString();
    
            DynamicJsonDocument doc(1024);
            deserializeJson(doc, result.c_str());
    
            JsonObject obj = doc.as<JsonObject>();
            JsonArray predictions = obj["predictions"].as<JsonArray>();
    
            for(JsonVariant prediction : predictions) 
            {
                String tag = prediction["tagName"].as<String>();
                float probability = prediction["probability"].as<float>();
    
                char buff[32];
                sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
                Serial.println(buff);
            }
        }
    
        httpClient.end();
    }
    ```

    קוד זה מתחיל בהכרזה על `HTTPClient` - מחלקה המכילה מתודות לתקשורת עם REST APIs. לאחר מכן הוא מתחבר לכתובת התחזית באמצעות מופע `WiFiClientSecure` שהוגדר עם המפתח הציבורי של Azure.

    לאחר החיבור, הוא שולח כותרות - מידע על הבקשה הקרובה שתתבצע מול ה-REST API. כותרת `Content-Type` מציינת שהקריאה ל-API תשלח נתונים בינאריים גולמיים, וכותרת `Prediction-Key` מעבירה את מפתח התחזית של Custom Vision.

    לאחר מכן מתבצעת בקשת POST ללקוח ה-HTTP, תוך העלאת מערך בתים. מערך זה יכיל את תמונת ה-JPEG שצולמה על ידי המצלמה כאשר פונקציה זו נקראת.

    > 💁 בקשות POST מיועדות לשליחת נתונים וקבלת תגובה. ישנם סוגי בקשות נוספים כמו בקשות GET שמחזירות נתונים. בקשות GET משמשות את דפדפן האינטרנט שלכם לטעינת דפי אינטרנט.

    בקשת ה-POST מחזירה קוד סטטוס תגובה. אלו ערכים מוגדרים היטב, כאשר 200 פירושו **OK** - בקשת ה-POST הצליחה.

    > 💁 תוכלו לראות את כל קודי סטטוס התגובה בדף [רשימת קודי סטטוס HTTP בוויקיפדיה](https://wikipedia.org/wiki/List_of_HTTP_status_codes)

    אם מוחזר 200, התוצאה נקראת מלקוח ה-HTTP. זוהי תגובת טקסט מה-REST API עם תוצאות התחזית כקובץ JSON. ה-JSON בפורמט הבא:

    ```jSON
    {
        "id":"45d614d3-7d6f-47e9-8fa2-04f237366a16",
        "project":"135607e5-efac-4855-8afb-c93af3380531",
        "iteration":"04f1c1fa-11ec-4e59-bb23-4c7aca353665",
        "created":"2021-06-10T17:58:58.959Z",
        "predictions":[
            {
                "probability":0.5582016,
                "tagId":"05a432ea-9718-4098-b14f-5f0688149d64",
                "tagName":"ripe"
            },
            {
                "probability":0.44179836,
                "tagId":"bb091037-16e5-418e-a9ea-31c6a2920f17",
                "tagName":"unripe"
            }
        ]
    }
    ```

    החלק החשוב כאן הוא מערך `predictions`. הוא מכיל את התחזיות, עם רשומה אחת לכל תג הכוללת את שם התג וההסתברות. ההסתברויות המוחזרות הן מספרים עשרוניים בין 0 ל-1, כאשר 0 משמעו 0% סיכוי להתאמה לתג, ו-1 משמעו 100% סיכוי.

    > 💁 מסווגי תמונות יחזירו את האחוזים עבור כל התגים שהוגדרו. לכל תג תהיה הסתברות שהתמונה תואמת לו.

    ה-JSON מפוענח, וההסתברויות עבור כל תג נשלחות לצג הסריאלי.

1. בפונקציה `buttonPressed`, החליפו את הקוד ששומר לכרטיס ה-SD בקריאה ל-`classifyImage`, או הוסיפו אותו לאחר שהתמונה נכתבה, אך **לפני** שמוחקים את המאגר:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 אם תחליפו את הקוד ששומר לכרטיס ה-SD, תוכלו לנקות את הקוד שלכם על ידי הסרת הפונקציות `setupSDCard` ו-`saveToSDCard`.

1. העלו והריצו את הקוד שלכם. כוונו את המצלמה לעבר פרי ולחצו על כפתור C. תראו את הפלט בצג הסריאלי:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    תוכלו לראות את התמונה שצולמה, ואת הערכים הללו בלשונית **Predictions** ב-Custom Vision.

    ![בננה ב-Custom Vision עם תחזית של 56.8% בשלה ו-43.1% לא בשלה](../../../../../translated_images/he/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 תוכלו למצוא את הקוד הזה בתיקייה [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal).

😀 תוכנית מסווג איכות הפירות שלכם הייתה הצלחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.