<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-26T15:38:39+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "hk"
}
-->
# 語音轉文字 - Wio Terminal

在本課程的這部分，你將撰寫程式碼，使用語音服務將捕獲的音訊轉換為文字。

## 將音訊發送到語音服務

可以使用 REST API 將音訊發送到語音服務。要使用語音服務，首先需要請求一個存取權杖，然後使用該權杖訪問 REST API。這些存取權杖在 10 分鐘後會過期，因此你的程式碼應定期請求它們，以確保它們始終是最新的。

### 任務 - 獲取存取權杖

1. 如果尚未打開 `smart-timer` 專案，請將其打開。

1. 在 `platformio.ini` 文件中新增以下庫依賴項，以訪問 WiFi 並處理 JSON：

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. 在 `config.h` 標頭文件中新增以下程式碼：

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    將 `<SSID>` 和 `<PASSWORD>` 替換為你的 WiFi 的相關值。

    將 `<API_KEY>` 替換為你的語音服務資源的 API 金鑰。將 `<LOCATION>` 替換為你創建語音服務資源時使用的位置。

    將 `<LANGUAGE>` 替換為你將使用的語言的地區名稱，例如英語為 `en-GB`，粵語為 `zn-HK`。你可以在 [Microsoft Docs 的語言和語音支持文檔](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) 中找到支持的語言及其地區名稱的列表。

    `TOKEN_URL` 常數是權杖發行者的 URL，不包含位置。稍後將與位置結合以獲取完整的 URL。

1. 與連接到 Custom Vision 一樣，你需要使用 HTTPS 連接來連接到權杖發行服務。在 `config.h` 的末尾新增以下程式碼：

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

    這與連接到 Custom Vision 時使用的證書相同。

1. 在 `main.cpp` 文件的頂部新增 WiFi 標頭文件和 config 標頭文件的 include 指令：

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. 在 `main.cpp` 中的 `setup` 函數上方新增程式碼以連接到 WiFi：

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

1. 在 `setup` 函數中，建立序列連接後調用此函數：

    ```cpp
    connectWiFi();
    ```

1. 在 `src` 資料夾中創建一個名為 `speech_to_text.h` 的新標頭文件。在此標頭文件中新增以下程式碼：

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

    這包括一些 HTTP 連接、配置和 `mic.h` 標頭文件所需的標頭文件，並定義了一個名為 `SpeechToText` 的類，然後聲明了一個稍後可以使用的該類的實例。

1. 在此類的 `private` 部分新增以下兩個欄位：

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client` 是一個使用 HTTPS 的 WiFi 客戶端，將用於獲取存取權杖。該權杖隨後將存儲在 `_access_token` 中。

1. 在 `private` 部分新增以下方法：

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

    此程式碼使用語音資源的位置構建權杖發行者 API 的 URL。然後創建一個 `HTTPClient` 來進行網絡請求，並將其設置為使用配置了權杖端點證書的 WiFi 客戶端。它將 API 金鑰設置為呼叫的標頭。然後它進行 POST 請求以獲取證書，如果出現任何錯誤則重試。最後返回存取權杖。

1. 在 `public` 部分新增一個方法以獲取存取權杖。在後續課程中，這將用於將文字轉換為語音。

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. 在 `public` 部分新增一個 `init` 方法來設置權杖客戶端：

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    這將證書設置在 WiFi 客戶端上，然後獲取存取權杖。

1. 在 `main.cpp` 中，將此新標頭文件新增到 include 指令中：

    ```cpp
    #include "speech_to_text.h"
    ```

1. 在 `setup` 函數的末尾初始化 `SpeechToText` 類，在 `mic.init` 調用之後但在將 `Ready` 寫入序列監視器之前：

    ```cpp
    speechToText.init();
    ```

### 任務 - 從閃存記憶體讀取音訊

1. 在本課程的早期部分，音訊已錄製到閃存記憶體中。這些音訊需要發送到語音服務的 REST API，因此需要從閃存記憶體中讀取。由於音訊太大，無法加載到內存緩衝區中，因此可以使用 Arduino Stream 類來流式傳輸數據。每次調用 `read` 時，它會返回下一塊數據。可以創建一個 Arduino Stream 類來從閃存記憶體中讀取數據。在 `src` 資料夾中創建一個名為 `flash_stream.h` 的新文件，並新增以下程式碼：

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

    這聲明了 `FlashStream` 類，繼承自 Arduino 的 `Stream` 類。這是一個抽象類 - 派生類必須實現一些方法才能實例化該類，這些方法在此類中定義。

    ✅ 在 [Arduino Stream 文檔](https://www.arduino.cc/reference/en/language/functions/communication/stream/) 中了解更多有關 Arduino Streams 的資訊。

1. 在 `private` 部分新增以下欄位：

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    這定義了一個臨時緩衝區來存儲從閃存記憶體中讀取的數據，以及用於存儲當前讀取位置、當前讀取地址和閃存記憶體設備的欄位。

1. 在 `private` 部分新增以下方法：

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    此程式碼從當前地址的閃存記憶體中讀取數據並將其存儲在緩衝區中。然後遞增地址，因此下一次調用會讀取下一塊記憶體。緩衝區的大小基於 `HTTPClient` 將一次發送到 REST API 的最大塊大小。

    > 💁 擦除閃存記憶體必須使用粒度大小，但讀取則不需要。

1. 在此類的 `public` 部分新增一個構造函數：

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    此構造函數設置所有欄位以從閃存記憶體塊的起始位置開始讀取，並將第一塊數據加載到緩衝區中。

1. 實現 `write` 方法。此流僅讀取數據，因此此方法可以不執行任何操作並返回 0：

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. 實現 `peek` 方法。此方法返回當前位置的數據而不移動流。只要未從流中讀取數據，多次調用 `peek` 將始終返回相同的數據。

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. 實現 `available` 函數。此函數返回可以從流中讀取的字節數，或者如果流已完成則返回 -1。對於此類，最大可用數量不會超過 HTTPClient 的塊大小。當此流用於 HTTP 客戶端時，它會調用此函數以查看有多少數據可用，然後請求該數量的數據以發送到 REST API。我們不希望每個塊超過 HTTP 客戶端的塊大小，因此如果可用數據超過該大小，則返回塊大小。如果少於該大小，則返回可用數據量。一旦所有數據都已流式傳輸，則返回 -1。

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

1. 實現 `read` 方法以返回緩衝區中的下一個字節，並遞增位置。如果位置超過緩衝區的大小，則用閃存記憶體中的下一塊數據填充緩衝區並重置位置。

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

1. 在 `speech_to_text.h` 標頭文件中，新增此新標頭文件的 include 指令：

    ```cpp
    #include "flash_stream.h"
    ```

### 任務 - 將語音轉換為文字

1. 可以通過將音訊發送到語音服務的 REST API 來將語音轉換為文字。此 REST API 與權杖發行者使用不同的證書，因此在 `config.h` 標頭文件中新增以下程式碼以定義此證書：

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

1. 在此文件中新增一個常數，用於不包含位置的語音 URL。稍後將與位置和語言結合以獲取完整的 URL。

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. 在 `speech_to_text.h` 標頭文件中，在 `SpeechToText` 類的 `private` 部分，定義一個使用語音證書的 WiFi 客戶端欄位：

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. 在 `init` 方法中，將此 WiFi 客戶端的證書設置好：

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. 在 `SpeechToText` 類的 `public` 部分新增以下程式碼以定義一個將語音轉換為文字的方法：

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. 在此方法中新增以下程式碼以使用配置了語音證書的 WiFi 客戶端創建 HTTP 客戶端，並使用設置了位置和語言的語音 URL：

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. 需要在連接上設置一些標頭：

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    這設置了授權標頭（使用存取權杖）、音訊格式（使用採樣率），並設置客戶端期望結果為 JSON。

1. 在此之後新增以下程式碼以進行 REST API 呼叫：

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    這創建了一個 `FlashStream`，並使用它將數據流式傳輸到 REST API。

1. 在此之下新增以下程式碼：

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

    此程式碼檢查響應代碼。

    如果是 200（成功代碼），則檢索結果，從 JSON 解碼，並將 `DisplayText` 屬性設置到 `text` 變數中。這是返回語音文字版本的屬性。

    如果響應代碼是 401，則存取權杖已過期（這些權杖僅持續 10 分鐘）。請求一個新的存取權杖，然後再次進行呼叫。

    否則，將錯誤發送到序列監視器，並將 `text` 保持為空白。

1. 在此方法的末尾新增以下程式碼以關閉 HTTP 客戶端並返回文字：

    ```cpp
    httpClient.end();

    return text;
    ```

1. 在 `main.cpp` 中，在 `processAudio` 函數中調用此新的 `convertSpeechToText` 方法，然後將語音文字記錄到序列監視器中：

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. 編譯此程式碼，將其上傳到你的 Wio Terminal，並通過序列監視器進行測試。一旦你在序列監視器中看到 `Ready`，按下 C 按鈕（左側最靠近電源開關的按鈕），然後說話。將捕獲 4 秒的音訊，然後轉換為文字。

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

> 💁 你可以在 [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal) 資料夾中找到此程式碼。

😀 你的語音轉文字程式成功了！

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始語言的文件應被視為權威來源。對於重要資訊，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。