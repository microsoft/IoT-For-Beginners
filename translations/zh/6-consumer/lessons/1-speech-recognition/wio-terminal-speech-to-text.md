<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-25T00:27:32+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "zh"
}
-->
# 语音转文本 - Wio Terminal

在本课程的这一部分中，您将编写代码，将捕获的音频中的语音转换为文本，使用语音服务完成此任务。

## 将音频发送到语音服务

可以通过 REST API 将音频发送到语音服务。要使用语音服务，首先需要请求一个访问令牌，然后使用该令牌访问 REST API。这些访问令牌的有效期为10分钟，因此您的代码需要定期请求它们，以确保令牌始终是最新的。

### 任务 - 获取访问令牌

1. 如果尚未打开，请打开 `smart-timer` 项目。

1. 在 `platformio.ini` 文件中添加以下库依赖项，以访问 WiFi 并处理 JSON：

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. 在 `config.h` 头文件中添加以下代码：

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    将 `<SSID>` 和 `<PASSWORD>` 替换为您的 WiFi 的相关值。

    将 `<API_KEY>` 替换为您的语音服务资源的 API 密钥。将 `<LOCATION>` 替换为您创建语音服务资源时使用的位置。

    将 `<LANGUAGE>` 替换为您将使用的语言的区域名称，例如 `en-GB` 表示英语，或 `zn-HK` 表示粤语。您可以在 [Microsoft 文档上的语言和语音支持文档](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) 中找到支持的语言及其区域名称的列表。

    `TOKEN_URL` 常量是令牌发行者的 URL，不包含位置。稍后将与位置结合以获取完整的 URL。

1. 与连接到 Custom Vision 类似，您需要使用 HTTPS 连接来连接到令牌发行服务。在 `config.h` 的末尾添加以下代码：

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

    这是您在连接到 Custom Vision 时使用的相同证书。

1. 在 `main.cpp` 文件顶部添加 WiFi 头文件和配置头文件的 include 指令：

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. 在 `main.cpp` 中的 `setup` 函数上方添加代码以连接到 WiFi：

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

1. 在 `setup` 函数中建立串行连接后调用此函数：

    ```cpp
    connectWiFi();
    ```

1. 在 `src` 文件夹中创建一个新的头文件，命名为 `speech_to_text.h`。在此头文件中添加以下代码：

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

    这包括一些用于 HTTP 连接、配置和 `mic.h` 头文件的必要头文件，并定义了一个名为 `SpeechToText` 的类，然后声明了一个稍后可以使用的该类的实例。

1. 在此类的 `private` 部分添加以下两个字段：

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client` 是一个使用 HTTPS 的 WiFi 客户端，将用于获取访问令牌。此令牌随后将存储在 `_access_token` 中。

1. 在 `private` 部分添加以下方法：

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

    此代码使用语音资源的位置构建令牌发行者 API 的 URL。然后创建一个 `HTTPClient` 来发起网络请求，设置它以使用配置了令牌端点证书的 WiFi 客户端。它将 API 密钥设置为调用的头信息。然后发起一个 POST 请求以获取证书，如果出现错误则重试。最后返回访问令牌。

1. 在 `public` 部分添加一个方法以获取访问令牌。此方法将在后续课程中用于将文本转换为语音。

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. 在 `public` 部分添加一个 `init` 方法，用于设置令牌客户端：

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    此方法在 WiFi 客户端上设置证书，然后获取访问令牌。

1. 在 `main.cpp` 中，将此新头文件添加到 include 指令中：

    ```cpp
    #include "speech_to_text.h"
    ```

1. 在 `setup` 函数的末尾初始化 `SpeechToText` 类，在 `mic.init` 调用之后但在将 `Ready` 写入串行监视器之前：

    ```cpp
    speechToText.init();
    ```

### 任务 - 从闪存中读取音频

1. 在本课程的早期部分，音频已记录到闪存中。此音频需要发送到语音服务 REST API，因此需要从闪存中读取。由于音频太大，无法加载到内存缓冲区中，因此可以使用 Arduino Stream 类以小块数据的形式流式传输数据。每次调用 `read` 方法时，它都会返回流中的下一块数据。可以创建一个 Arduino 流来从闪存中读取数据。在 `src` 文件夹中创建一个名为 `flash_stream.h` 的新文件，并添加以下代码：

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

    这声明了 `FlashStream` 类，继承自 Arduino 的 `Stream` 类。这是一个抽象类——派生类必须实现一些方法后才能实例化，而这些方法在此类中定义。

    ✅ 在 [Arduino Stream 文档](https://www.arduino.cc/reference/en/language/functions/communication/stream/) 中了解更多关于 Arduino Streams 的信息。

1. 在 `private` 部分添加以下字段：

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    这定义了一个临时缓冲区，用于存储从闪存中读取的数据，以及用于存储当前读取位置、当前读取地址和闪存设备的字段。

1. 在 `private` 部分添加以下方法：

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    此代码从当前地址的闪存中读取数据并将其存储在缓冲区中。然后递增地址，以便下一次调用读取下一块内存。缓冲区的大小基于 `HTTPClient` 一次发送到 REST API 的最大块大小。

    > 💁 擦除闪存必须使用粒度大小，而读取则不需要。

1. 在此类的 `public` 部分添加一个构造函数：

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    此构造函数设置所有字段以从闪存块的起始位置开始读取，并将第一块数据加载到缓冲区中。

1. 实现 `write` 方法。此流仅用于读取数据，因此此方法可以不执行任何操作并返回 0：

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. 实现 `peek` 方法。此方法返回当前位置的数据而不移动流。多次调用 `peek` 将始终返回相同的数据，只要没有从流中读取数据。

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. 实现 `available` 方法。此方法返回流中可以读取的字节数，如果流已完成则返回 -1。对于此类，最大可用字节数不会超过 HTTPClient 的块大小。当此流用于 HTTP 客户端时，它会调用此方法以查看有多少数据可用，然后请求该数量的数据以发送到 REST API。我们不希望每块数据超过 HTTP 客户端的块大小，因此如果可用数据超过块大小，则返回块大小；如果少于块大小，则返回实际可用数据。一旦所有数据都已流式传输，则返回 -1。

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

1. 实现 `read` 方法以返回缓冲区中的下一个字节，并递增位置。如果位置超过缓冲区大小，则用闪存中的下一块数据填充缓冲区并重置位置。

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

1. 在 `speech_to_text.h` 头文件中，为此新头文件添加 include 指令：

    ```cpp
    #include "flash_stream.h"
    ```

### 任务 - 将语音转换为文本

1. 可以通过将音频发送到语音服务的 REST API 来将语音转换为文本。此 REST API 使用的证书与令牌发行者不同，因此在 `config.h` 头文件中添加以下代码以定义此证书：

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

1. 在此文件中添加一个常量，用于语音 URL（不包含位置）。稍后将与位置和语言结合以获取完整的 URL。

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. 在 `speech_to_text.h` 头文件中，在 `SpeechToText` 类的 `private` 部分定义一个字段，用于使用语音证书的 WiFi 客户端：

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. 在 `init` 方法中，在此 WiFi 客户端上设置证书：

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. 在 `SpeechToText` 类的 `public` 部分添加以下代码以定义一个方法，将语音转换为文本：

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. 在此方法中添加以下代码，以使用配置了语音证书的 WiFi 客户端创建 HTTP 客户端，并使用设置了位置和语言的语音 URL：

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. 在连接上设置一些头信息：

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    这设置了授权头信息，使用访问令牌；音频格式，使用采样率；并设置客户端期望结果为 JSON 格式。

1. 在此之后，添加以下代码以发起 REST API 调用：

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    这创建了一个 `FlashStream` 并使用它将数据流式传输到 REST API。

1. 在此代码下方添加以下代码：

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

    此代码检查响应代码。

    如果响应代码为 200（成功代码），则检索结果，从 JSON 解码，并将 `DisplayText` 属性设置到 `text` 变量中。此属性返回语音的文本版本。

    如果响应代码为 401，则访问令牌已过期（这些令牌仅有效10分钟）。请求一个新的访问令牌，然后再次发起调用。

    否则，将错误发送到串行监视器，并将 `text` 保留为空。

1. 在此方法的末尾添加以下代码以关闭 HTTP 客户端并返回文本：

    ```cpp
    httpClient.end();

    return text;
    ```

1. 在 `main.cpp` 中，在 `processAudio` 函数中调用此新的 `convertSpeechToText` 方法，然后将语音日志输出到串行监视器：

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. 构建此代码，将其上传到您的 Wio Terminal，并通过串行监视器进行测试。当您在串行监视器中看到 `Ready` 时，按下 C 按钮（左侧靠近电源开关的按钮），然后开始说话。将捕获4秒的音频，然后将其转换为文本。

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

> 💁 您可以在 [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal) 文件夹中找到此代码。

😀 您的语音转文本程序成功了！

**免责声明**：  
本文档使用AI翻译服务[Co-op Translator](https://github.com/Azure/co-op-translator)进行翻译。尽管我们努力确保准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原始语言的文档作为权威来源。对于关键信息，建议使用专业人工翻译。因使用本翻译而导致的任何误解或误读，我们概不负责。