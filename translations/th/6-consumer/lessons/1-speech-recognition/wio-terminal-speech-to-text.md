<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-27T20:40:41+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "th"
}
-->
# การแปลงเสียงเป็นข้อความ - Wio Terminal

ในส่วนนี้ของบทเรียน คุณจะเขียนโค้ดเพื่อแปลงเสียงในไฟล์เสียงที่บันทึกไว้เป็นข้อความโดยใช้บริการแปลงเสียงเป็นข้อความ

## ส่งไฟล์เสียงไปยังบริการแปลงเสียงเป็นข้อความ

ไฟล์เสียงสามารถส่งไปยังบริการแปลงเสียงเป็นข้อความได้โดยใช้ REST API ในการใช้บริการนี้ คุณต้องขอ access token ก่อน จากนั้นใช้ token นี้เพื่อเข้าถึง REST API โดย token เหล่านี้จะหมดอายุภายใน 10 นาที ดังนั้นโค้ดของคุณควรขอ token ใหม่เป็นประจำเพื่อให้แน่ใจว่า token จะอัปเดตอยู่เสมอ

### งาน - ขอ access token

1. เปิดโปรเจกต์ `smart-timer` หากยังไม่ได้เปิด

1. เพิ่มไลบรารีที่จำเป็นต่อการเข้าถึง WiFi และจัดการ JSON ลงในไฟล์ `platformio.ini`:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. เพิ่มโค้ดต่อไปนี้ลงในไฟล์ header `config.h`:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    แทนที่ `<SSID>` และ `<PASSWORD>` ด้วยค่าที่เกี่ยวข้องสำหรับ WiFi ของคุณ

    แทนที่ `<API_KEY>` ด้วย API key สำหรับทรัพยากรบริการแปลงเสียงเป็นข้อความ และแทนที่ `<LOCATION>` ด้วยตำแหน่งที่คุณใช้เมื่อสร้างทรัพยากรบริการแปลงเสียงเป็นข้อความ

    แทนที่ `<LANGUAGE>` ด้วยชื่อภาษาที่คุณจะพูด เช่น `en-GB` สำหรับภาษาอังกฤษ หรือ `zn-HK` สำหรับภาษากวางตุ้ง คุณสามารถดูรายการภาษาที่รองรับและชื่อภาษาของพวกเขาได้ใน [เอกสารสนับสนุนภาษาและเสียงบน Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text)

    ค่าคงที่ `TOKEN_URL` คือ URL ของ token issuer โดยไม่รวมตำแหน่ง ซึ่งจะถูกรวมกับตำแหน่งในภายหลังเพื่อสร้าง URL เต็ม

1. เช่นเดียวกับการเชื่อมต่อกับ Custom Vision คุณจะต้องใช้การเชื่อมต่อ HTTPS เพื่อเชื่อมต่อกับบริการออก token เพิ่มโค้ดต่อไปนี้ลงในท้ายไฟล์ `config.h`:

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

    นี่คือใบรับรองเดียวกันที่คุณใช้เมื่อเชื่อมต่อกับ Custom Vision

1. เพิ่ม include สำหรับไฟล์ header WiFi และไฟล์ header config ที่ด้านบนของไฟล์ `main.cpp`:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. เพิ่มโค้ดเพื่อเชื่อมต่อกับ WiFi ใน `main.cpp` เหนือฟังก์ชัน `setup`:

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

1. เรียกใช้ฟังก์ชันนี้จากฟังก์ชัน `setup` หลังจากที่การเชื่อมต่อ serial ถูกตั้งค่าแล้ว:

    ```cpp
    connectWiFi();
    ```

1. สร้างไฟล์ header ใหม่ในโฟลเดอร์ `src` ชื่อ `speech_to_text.h` ในไฟล์ header นี้ เพิ่มโค้ดต่อไปนี้:

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

    โค้ดนี้รวมไฟล์ header ที่จำเป็นสำหรับการเชื่อมต่อ HTTP, การตั้งค่า และไฟล์ header `mic.h` และกำหนดคลาสชื่อ `SpeechToText` ก่อนที่จะประกาศ instance ของคลาสนี้เพื่อใช้งานในภายหลัง

1. เพิ่มฟิลด์ 2 ฟิลด์ต่อไปนี้ในส่วน `private` ของคลาสนี้:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client` คือ WiFi Client ที่ใช้ HTTPS และจะถูกใช้เพื่อขอ access token ซึ่ง token นี้จะถูกเก็บไว้ใน `_access_token`

1. เพิ่มเมธอดต่อไปนี้ในส่วน `private`:

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

    โค้ดนี้สร้าง URL สำหรับ token issuer API โดยใช้ตำแหน่งของทรัพยากรบริการแปลงเสียงเป็นข้อความ จากนั้นสร้าง `HTTPClient` เพื่อทำการร้องขอเว็บ โดยตั้งค่าให้ใช้ WiFi client ที่กำหนดค่าด้วยใบรับรองของ token endpoint และตั้งค่า API key เป็น header สำหรับการเรียกใช้ จากนั้นทำการ POST request เพื่อรับใบรับรอง และหากเกิดข้อผิดพลาดจะทำการ retry สุดท้าย access token จะถูกส่งคืน

1. ในส่วน `public` เพิ่มเมธอดเพื่อรับ access token ซึ่งจะถูกใช้ในบทเรียนถัดไปเพื่อแปลงข้อความเป็นเสียง

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. ในส่วน `public` เพิ่มเมธอด `init` ที่ตั้งค่า token client:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    โค้ดนี้ตั้งค่าใบรับรองบน WiFi client จากนั้นรับ access token

1. ใน `main.cpp` เพิ่มไฟล์ header ใหม่นี้ใน include directives:

    ```cpp
    #include "speech_to_text.h"
    ```

1. เริ่มต้นคลาส `SpeechToText` ที่ท้ายฟังก์ชัน `setup` หลังจากเรียก `mic.init` แต่ก่อนที่จะเขียน `Ready` ลงใน serial monitor:

    ```cpp
    speechToText.init();
    ```

### งาน - อ่านไฟล์เสียงจากหน่วยความจำแฟลช

1. ในส่วนก่อนหน้าของบทเรียน ไฟล์เสียงถูกบันทึกลงในหน่วยความจำแฟลช ไฟล์เสียงนี้จะต้องถูกส่งไปยัง REST API ของ Speech Services ดังนั้นจึงต้องอ่านจากหน่วยความจำแฟลช ไม่สามารถโหลดลงในบัฟเฟอร์ในหน่วยความจำได้เนื่องจากมีขนาดใหญ่เกินไป คลาส `HTTPClient` ที่ทำ REST calls สามารถสตรีมข้อมูลโดยใช้ Arduino Stream - คลาสที่สามารถโหลดข้อมูลเป็นชิ้นเล็ก ๆ และส่งทีละชิ้นในคำร้องขอ สร้างไฟล์ใหม่ชื่อ `flash_stream.h` ในโฟลเดอร์ `src` และเพิ่มโค้ดต่อไปนี้ลงในไฟล์:

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

    โค้ดนี้ประกาศคลาส `FlashStream` ซึ่งสืบทอดมาจากคลาส `Stream` ของ Arduino คลาสนี้เป็นคลาสแบบ abstract - คลาสที่สืบทอดมาต้อง implement เมธอดบางตัวก่อนที่คลาสจะสามารถถูกสร้าง instance ได้ และเมธอดเหล่านี้ถูกกำหนดในคลาสนี้

    ✅ อ่านเพิ่มเติมเกี่ยวกับ Arduino Streams ใน [เอกสาร Arduino Stream](https://www.arduino.cc/reference/en/language/functions/communication/stream/)

1. เพิ่มฟิลด์ต่อไปนี้ในส่วน `private`:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    โค้ดนี้กำหนดบัฟเฟอร์ชั่วคราวเพื่อเก็บข้อมูลที่อ่านจากหน่วยความจำแฟลช พร้อมกับฟิลด์เพื่อเก็บตำแหน่งปัจจุบันเมื่ออ่านจากบัฟเฟอร์ ที่อยู่ปัจจุบันที่จะอ่านจากหน่วยความจำแฟลช และอุปกรณ์หน่วยความจำแฟลช

1. ในส่วน `private` เพิ่มเมธอดต่อไปนี้:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    โค้ดนี้อ่านจากหน่วยความจำแฟลชที่อยู่ปัจจุบันและเก็บข้อมูลในบัฟเฟอร์ จากนั้นเพิ่มที่อยู่เพื่อให้การเรียกครั้งถัดไปอ่านบล็อกถัดไปของหน่วยความจำ บัฟเฟอร์ถูกกำหนดขนาดตามชิ้นส่วนที่ใหญ่ที่สุดที่ `HTTPClient` จะส่งไปยัง REST API ในครั้งเดียว

    > 💁 การลบหน่วยความจำแฟลชต้องทำโดยใช้ grain size แต่การอ่านไม่จำเป็นต้องทำเช่นนั้น

1. ในส่วน `public` ของคลาสนี้ เพิ่ม constructor:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    Constructor นี้ตั้งค่าฟิลด์ทั้งหมดเพื่อเริ่มอ่านจากจุดเริ่มต้นของบล็อกหน่วยความจำแฟลช และโหลดชิ้นส่วนแรกของข้อมูลลงในบัฟเฟอร์

1. Implement เมธอด `write` คลาสนี้จะอ่านข้อมูลเท่านั้น ดังนั้นเมธอดนี้สามารถทำอะไรไม่ได้และคืนค่า 0:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. Implement เมธอด `peek` เมธอดนี้คืนค่าข้อมูลที่ตำแหน่งปัจจุบันโดยไม่เลื่อน stream ไปข้างหน้า การเรียก `peek` หลายครั้งจะคืนค่าข้อมูลเดิมตราบใดที่ไม่มีข้อมูลถูกอ่านจาก stream

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. Implement ฟังก์ชัน `available` ฟังก์ชันนี้คืนค่าจำนวนไบต์ที่สามารถอ่านจาก stream หรือ -1 หาก stream เสร็จสิ้น สำหรับคลาสนี้ ค่าสูงสุดที่สามารถใช้ได้จะไม่เกิน chunk size ของ HTTPClient เมื่อ stream นี้ถูกใช้ใน HTTP client มันจะเรียกฟังก์ชันนี้เพื่อดูว่ามีข้อมูลเท่าใดที่สามารถใช้ได้ จากนั้นร้องขอข้อมูลเท่านั้นเพื่อส่งไปยัง REST API เราไม่ต้องการให้แต่ละชิ้นใหญ่เกิน chunk size ของ HTTP client ดังนั้นหากมีมากกว่านั้น chunk size จะถูกคืนค่า หากน้อยกว่านั้น จำนวนที่มีอยู่จะถูกคืนค่า เมื่อข้อมูลทั้งหมดถูกสตรีมแล้ว -1 จะถูกคืนค่า

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

1. Implement เมธอด `read` เพื่อคืนค่าไบต์ถัดไปจากบัฟเฟอร์ โดยเพิ่มตำแหน่ง หากตำแหน่งเกินขนาดของบัฟเฟอร์ จะโหลดบัฟเฟอร์ด้วยบล็อกถัดไปจากหน่วยความจำแฟลชและรีเซ็ตตำแหน่ง

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

1. ในไฟล์ header `speech_to_text.h` เพิ่ม include directive สำหรับไฟล์ header ใหม่นี้:

    ```cpp
    #include "flash_stream.h"
    ```

### งาน - แปลงเสียงเป็นข้อความ

1. เสียงสามารถแปลงเป็นข้อความได้โดยการส่งไฟล์เสียงไปยัง Speech Service ผ่าน REST API REST API นี้มีใบรับรองที่แตกต่างจาก token issuer ดังนั้นเพิ่มโค้ดต่อไปนี้ลงในไฟล์ header `config.h` เพื่อกำหนดใบรับรองนี้:

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

1. เพิ่มค่าคงที่ในไฟล์นี้สำหรับ speech URL โดยไม่รวมตำแหน่ง ซึ่งจะถูกรวมกับตำแหน่งและภาษาภายหลังเพื่อสร้าง URL เต็ม

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. ในไฟล์ header `speech_to_text.h` ในส่วน `private` ของคลาส `SpeechToText` กำหนดฟิลด์สำหรับ WiFi Client ที่ใช้ใบรับรอง speech:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. ในเมธอด `init` ตั้งค่าใบรับรองบน WiFi Client นี้:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. เพิ่มโค้ดต่อไปนี้ในส่วน `public` ของคลาส `SpeechToText` เพื่อกำหนดเมธอดสำหรับแปลงเสียงเป็นข้อความ:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. เพิ่มโค้ดต่อไปนี้ในเมธอดนี้เพื่อสร้าง HTTP client โดยใช้ WiFi client ที่กำหนดค่าด้วยใบรับรอง speech และใช้ speech URL ที่ตั้งค่าด้วยตำแหน่งและภาษา:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. ต้องตั้งค่า headers บางตัวบนการเชื่อมต่อ:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    โค้ดนี้ตั้งค่า headers สำหรับการอนุญาตโดยใช้ access token รูปแบบเสียงโดยใช้ sample rate และตั้งค่าที่ client คาดหวังผลลัพธ์เป็น JSON

1. หลังจากนี้ เพิ่มโค้ดต่อไปนี้เพื่อทำ REST API call:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    โค้ดนี้สร้าง `FlashStream` และใช้มันเพื่อสตรีมข้อมูลไปยัง REST API

1. ด้านล่างนี้ เพิ่มโค้ดต่อไปนี้:

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

    โค้ดนี้ตรวจสอบ response code

    หาก response code คือ 200 ซึ่งเป็นโค้ดสำหรับความสำเร็จ ผลลัพธ์จะถูกดึงมา ถอดรหัสจาก JSON และ property `DisplayText` จะถูกตั้งค่าในตัวแปร `text` ซึ่งเป็น property ที่ข้อความเวอร์ชันของเสียงจะถูกส่งคืน

    หาก response code คือ 401 หมายความว่า access token หมดอายุ (token เหล่านี้มีอายุเพียง 10 นาที) จะมีการขอ access token ใหม่ และทำการเรียกอีกครั้ง

    มิฉะนั้น ข้อผิดพลาดจะถูกส่งไปยัง serial monitor และ `text` จะถูกปล่อยว่างไว้

1. เพิ่มโค้ดต่อไปนี้ที่ท้ายเมธอดนี้เพื่อปิด HTTP client และคืนค่า text:

    ```cpp
    httpClient.end();

    return text;
    ```

1. ใน `main.cpp` เรียกใช้เมธอด `convertSpeechToText` ใหม่ในฟังก์ชัน `processAudio` จากนั้นล็อกข้อความที่แปลงแล้วลงใน serial monitor:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. สร้างโค้ดนี้ อัปโหลดไปยัง Wio Terminal ของคุณ และทดสอบผ่าน serial monitor เมื่อคุณเห็นคำว่า `Ready` ใน serial monitor ให้กดปุ่ม C (ปุ่มด้านซ้ายมือใกล้กับสวิตช์เปิดปิด) และพูด ไฟล์เสียง 4 วินาทีจะถูกบันทึก จากนั้นแปลงเป็นข้อความ

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

> 💁 คุณสามารถค้นหาโค้ดนี้ได้ใน [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal) โฟลเดอร์

😀 โปรแกรมแปลงเสียงเป็นข้อความของคุณสำเร็จแล้ว!

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้อง แต่โปรดทราบว่าการแปลโดยอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษาจากผู้เชี่ยวชาญ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความผิดที่เกิดจากการใช้การแปลนี้