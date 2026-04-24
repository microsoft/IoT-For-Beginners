# จำแนกภาพ - Wio Terminal

ในส่วนนี้ของบทเรียน คุณจะส่งภาพที่ถ่ายโดยกล้องไปยังบริการ Custom Vision เพื่อจำแนกภาพ

## จำแนกภาพ

บริการ Custom Vision มี REST API ที่คุณสามารถเรียกใช้งานจาก Wio Terminal เพื่อจำแนกภาพ REST API นี้เข้าถึงได้ผ่านการเชื่อมต่อ HTTPS - การเชื่อมต่อ HTTP ที่ปลอดภัย

เมื่อมีการโต้ตอบกับปลายทาง HTTPS โค้ดฝั่งไคลเอนต์จำเป็นต้องร้องขอใบรับรองกุญแจสาธารณะจากเซิร์ฟเวอร์ที่เข้าถึง และใช้ใบรับรองนั้นเพื่อเข้ารหัสข้อมูลที่ส่งไป เบราว์เซอร์ของคุณทำสิ่งนี้โดยอัตโนมัติ แต่ไมโครคอนโทรลเลอร์ไม่สามารถทำได้ คุณจำเป็นต้องร้องขอใบรับรองนี้ด้วยตนเองและใช้มันเพื่อสร้างการเชื่อมต่อที่ปลอดภัยกับ REST API ใบรับรองเหล่านี้ไม่เปลี่ยนแปลง ดังนั้นเมื่อคุณมีใบรับรองแล้ว คุณสามารถเขียนโค้ดไว้ในแอปพลิเคชันของคุณได้

ใบรับรองเหล่านี้มีคีย์สาธารณะ และไม่จำเป็นต้องเก็บไว้เป็นความลับ คุณสามารถใช้มันในโค้ดต้นฉบับของคุณและแชร์ในที่สาธารณะ เช่น GitHub

### งาน - ตั้งค่า SSL client

1. เปิดโปรเจกต์แอป `fruit-quality-detector` หากยังไม่ได้เปิด

1. เปิดไฟล์เฮดเดอร์ `config.h` และเพิ่มโค้ดต่อไปนี้:

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

    นี่คือ *Microsoft Azure DigiCert Global Root G2 certificate* - เป็นหนึ่งในใบรับรองที่ใช้โดยบริการ Azure หลายแห่งทั่วโลก

    > 💁 เพื่อดูว่าใบรับรองนี้เป็นใบรับรองที่ต้องใช้ ให้รันคำสั่งต่อไปนี้บน macOS หรือ Linux หากคุณใช้ Windows คุณสามารถรันคำสั่งนี้ผ่าน [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn):
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > ผลลัพธ์จะระบุใบรับรอง DigiCert Global Root G2

1. เปิด `main.cpp` และเพิ่มคำสั่ง include ต่อไปนี้:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. ด้านล่างคำสั่ง include ให้ประกาศอินสแตนซ์ของ `WifiClientSecure`:

    ```cpp
    WiFiClientSecure client;
    ```

    คลาสนี้มีโค้ดสำหรับการสื่อสารกับปลายทางเว็บผ่าน HTTPS

1. ในเมธอด `connectWiFi` ตั้งค่า WiFiClientSecure ให้ใช้ใบรับรอง DigiCert Global Root G2:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### งาน - จำแนกภาพ

1. เพิ่มบรรทัดต่อไปนี้เป็นบรรทัดเพิ่มเติมในรายการ `lib_deps` ในไฟล์ `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    นี่คือการนำเข้า [ArduinoJson](https://arduinojson.org) ซึ่งเป็นไลบรารี JSON สำหรับ Arduino และจะใช้ในการถอดรหัสการตอบกลับ JSON จาก REST API

1. ใน `config.h` เพิ่มค่าคงที่สำหรับ URL การพยากรณ์และ Key จากบริการ Custom Vision:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    แทนที่ `<PREDICTION_URL>` ด้วย URL การพยากรณ์จาก Custom Vision และแทนที่ `<PREDICTION_KEY>` ด้วยคีย์การพยากรณ์

1. ใน `main.cpp` เพิ่มคำสั่ง include สำหรับไลบรารี ArduinoJson:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. เพิ่มฟังก์ชันต่อไปนี้ใน `main.cpp` ด้านบนฟังก์ชัน `buttonPressed`:

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

    โค้ดนี้เริ่มต้นด้วยการประกาศ `HTTPClient` - คลาสที่มีเมธอดสำหรับโต้ตอบกับ REST APIs จากนั้นเชื่อมต่อไคลเอนต์กับ URL การพยากรณ์โดยใช้อินสแตนซ์ `WiFiClientSecure` ที่ตั้งค่าด้วยกุญแจสาธารณะของ Azure

    เมื่อเชื่อมต่อแล้ว จะส่ง headers - ข้อมูลเกี่ยวกับคำขอที่จะทำกับ REST API header `Content-Type` ระบุว่าการเรียก API จะส่งข้อมูลไบนารีดิบ ส่วน header `Prediction-Key` ส่งคีย์การพยากรณ์ของ Custom Vision

    จากนั้นทำคำขอ POST ไปยัง HTTP client โดยอัปโหลด byte array ซึ่งจะมีภาพ JPEG ที่ถ่ายจากกล้องเมื่อเรียกใช้ฟังก์ชันนี้

    > 💁 คำขอ POST ใช้สำหรับการส่งข้อมูลและรับการตอบกลับ มีคำขอประเภทอื่น เช่น GET ที่ใช้ดึงข้อมูล GET ใช้โดยเบราว์เซอร์ของคุณในการโหลดหน้าเว็บ

    คำขอ POST จะส่งคืนรหัสสถานะการตอบกลับ ซึ่งเป็นค่าที่กำหนดไว้อย่างดี โดย 200 หมายถึง **OK** - คำขอ POST สำเร็จ

    > 💁 คุณสามารถดูรหัสสถานะการตอบกลับทั้งหมดได้ใน [หน้ารายการรหัสสถานะ HTTP บน Wikipedia](https://wikipedia.org/wiki/List_of_HTTP_status_codes)

    หากส่งคืน 200 ผลลัพธ์จะถูกอ่านจาก HTTP client ซึ่งเป็นการตอบกลับข้อความจาก REST API พร้อมผลลัพธ์การพยากรณ์ในรูปแบบเอกสาร JSON JSON มีรูปแบบดังนี้:

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

    ส่วนสำคัญคืออาร์เรย์ `predictions` ซึ่งมีการพยากรณ์ โดยแต่ละรายการมีชื่อแท็กและความน่าจะเป็น ความน่าจะเป็นที่ส่งคืนเป็นตัวเลขทศนิยมตั้งแต่ 0-1 โดย 0 หมายถึงโอกาส 0% ที่จะตรงกับแท็ก และ 1 หมายถึงโอกาส 100%

    > 💁 ตัวจำแนกภาพจะส่งคืนเปอร์เซ็นต์สำหรับแท็กทั้งหมดที่ใช้ แต่ละแท็กจะมีความน่าจะเป็นที่ภาพจะตรงกับแท็กนั้น

    JSON นี้ถูกถอดรหัส และความน่าจะเป็นสำหรับแต่ละแท็กจะถูกส่งไปยัง serial monitor

1. ในฟังก์ชัน `buttonPressed` ให้แทนที่โค้ดที่บันทึกลง SD card ด้วยการเรียก `classifyImage` หรือเพิ่มหลังจากที่ภาพถูกเขียน แต่ **ก่อน** buffer ถูกลบ:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 หากคุณแทนที่โค้ดที่บันทึกลง SD card คุณสามารถล้างโค้ดโดยลบฟังก์ชัน `setupSDCard` และ `saveToSDCard`

1. อัปโหลดและรันโค้ดของคุณ ชี้กล้องไปที่ผลไม้และกดปุ่ม C คุณจะเห็นผลลัพธ์ใน serial monitor:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    คุณจะสามารถเห็นภาพที่ถ่าย และค่าต่างๆ ในแท็บ **Predictions** ใน Custom Vision

    ![กล้วยใน Custom Vision ถูกพยากรณ์ว่าสุก 56.8% และยังไม่สุก 43.1%](../../../../../translated_images/th/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 คุณสามารถค้นหาโค้ดนี้ได้ในโฟลเดอร์ [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal)

😀 โปรแกรมจำแนกคุณภาพผลไม้ของคุณสำเร็จแล้ว!

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้องมากที่สุด แต่โปรดทราบว่าการแปลโดยอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความผิดที่เกิดจากการใช้การแปลนี้