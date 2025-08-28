<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-27T23:26:57+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "vi"
}
-->
# Chuyển giọng nói thành văn bản - Wio Terminal

Trong phần này của bài học, bạn sẽ viết mã để chuyển đổi giọng nói trong âm thanh đã thu thành văn bản bằng cách sử dụng dịch vụ giọng nói.

## Gửi âm thanh đến dịch vụ giọng nói

Âm thanh có thể được gửi đến dịch vụ giọng nói bằng cách sử dụng REST API. Để sử dụng dịch vụ giọng nói, trước tiên bạn cần yêu cầu một mã truy cập, sau đó sử dụng mã đó để truy cập REST API. Các mã truy cập này hết hạn sau 10 phút, vì vậy mã của bạn cần yêu cầu chúng thường xuyên để đảm bảo chúng luôn được cập nhật.

### Nhiệm vụ - lấy mã truy cập

1. Mở dự án `smart-timer` nếu nó chưa được mở.

1. Thêm các thư viện phụ thuộc sau vào tệp `platformio.ini` để truy cập WiFi và xử lý JSON:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. Thêm mã sau vào tệp tiêu đề `config.h`:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    Thay thế `<SSID>` và `<PASSWORD>` bằng các giá trị tương ứng cho WiFi của bạn.

    Thay thế `<API_KEY>` bằng khóa API cho tài nguyên dịch vụ giọng nói của bạn. Thay thế `<LOCATION>` bằng vị trí bạn đã sử dụng khi tạo tài nguyên dịch vụ giọng nói.

    Thay thế `<LANGUAGE>` bằng tên ngôn ngữ mà bạn sẽ nói, ví dụ `en-GB` cho tiếng Anh, hoặc `zn-HK` cho tiếng Quảng Đông. Bạn có thể tìm danh sách các ngôn ngữ được hỗ trợ và tên ngôn ngữ của chúng trong [tài liệu hỗ trợ ngôn ngữ và giọng nói trên Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Hằng số `TOKEN_URL` là URL của nhà phát hành mã mà không có vị trí. URL này sẽ được kết hợp với vị trí sau để tạo URL đầy đủ.

1. Tương tự như kết nối với Custom Vision, bạn sẽ cần sử dụng kết nối HTTPS để kết nối với dịch vụ phát hành mã. Thêm mã sau vào cuối `config.h`:

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

    Đây là chứng chỉ giống như bạn đã sử dụng khi kết nối với Custom Vision.

1. Thêm một chỉ thị bao gồm tệp tiêu đề WiFi và tệp tiêu đề cấu hình vào đầu tệp `main.cpp`:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. Thêm mã để kết nối với WiFi trong `main.cpp` phía trên hàm `setup`:

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

1. Gọi hàm này từ hàm `setup` sau khi kết nối serial đã được thiết lập:

    ```cpp
    connectWiFi();
    ```

1. Tạo một tệp tiêu đề mới trong thư mục `src` có tên `speech_to_text.h`. Trong tệp tiêu đề này, thêm mã sau:

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

    Điều này bao gồm một số tệp tiêu đề cần thiết cho kết nối HTTP, cấu hình và tệp tiêu đề `mic.h`, và định nghĩa một lớp có tên `SpeechToText`, trước khi khai báo một thể hiện của lớp này để sử dụng sau.

1. Thêm 2 trường sau vào phần `private` của lớp này:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client` là một WiFi Client sử dụng HTTPS và sẽ được sử dụng để lấy mã truy cập. Mã này sau đó sẽ được lưu trữ trong `_access_token`.

1. Thêm phương thức sau vào phần `private`:

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

    Mã này xây dựng URL cho API nhà phát hành mã bằng cách sử dụng vị trí của tài nguyên giọng nói. Sau đó, nó tạo một `HTTPClient` để thực hiện yêu cầu web, thiết lập nó để sử dụng WiFi client được cấu hình với chứng chỉ của điểm cuối mã. Nó đặt khóa API làm tiêu đề cho cuộc gọi. Sau đó, nó thực hiện yêu cầu POST để lấy chứng chỉ, thử lại nếu gặp lỗi. Cuối cùng, mã truy cập được trả về.

1. Trong phần `public`, thêm một phương thức để lấy mã truy cập. Phương thức này sẽ được sử dụng trong các bài học sau để chuyển đổi văn bản thành giọng nói.

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. Trong phần `public`, thêm một phương thức `init` để thiết lập client mã:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    Phương thức này đặt chứng chỉ trên WiFi client, sau đó lấy mã truy cập.

1. Trong `main.cpp`, thêm tệp tiêu đề mới này vào các chỉ thị bao gồm:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Khởi tạo lớp `SpeechToText` ở cuối hàm `setup`, sau khi gọi `mic.init` nhưng trước khi `Ready` được ghi vào serial monitor:

    ```cpp
    speechToText.init();
    ```

### Nhiệm vụ - đọc âm thanh từ bộ nhớ flash

1. Trong phần trước của bài học, âm thanh đã được ghi vào bộ nhớ flash. Âm thanh này sẽ cần được gửi đến REST API của Dịch vụ Giọng nói, vì vậy nó cần được đọc từ bộ nhớ flash. Nó không thể được tải vào bộ đệm trong bộ nhớ vì sẽ quá lớn. Lớp `HTTPClient` thực hiện các cuộc gọi REST có thể truyền dữ liệu bằng một Arduino Stream - một lớp có thể tải dữ liệu theo từng phần nhỏ, gửi từng phần một tại một thời điểm như một phần của yêu cầu. Mỗi lần bạn gọi `read` trên một stream, nó trả về khối dữ liệu tiếp theo. Một Arduino stream có thể được tạo để đọc từ bộ nhớ flash. Tạo một tệp mới có tên `flash_stream.h` trong thư mục `src`, và thêm mã sau vào đó:

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

    Điều này khai báo lớp `FlashStream`, kế thừa từ lớp `Stream` của Arduino. Đây là một lớp trừu tượng - các lớp kế thừa phải triển khai một vài phương thức trước khi lớp có thể được khởi tạo, và các phương thức này được định nghĩa trong lớp này.

    ✅ Đọc thêm về Arduino Streams trong [tài liệu Arduino Stream](https://www.arduino.cc/reference/en/language/functions/communication/stream/)

1. Thêm các trường sau vào phần `private`:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    Điều này định nghĩa một bộ đệm tạm thời để lưu trữ dữ liệu đọc từ bộ nhớ flash, cùng với các trường để lưu trữ vị trí hiện tại khi đọc từ bộ đệm, địa chỉ hiện tại để đọc từ bộ nhớ flash, và thiết bị bộ nhớ flash.

1. Trong phần `private`, thêm phương thức sau:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    Mã này đọc từ bộ nhớ flash tại địa chỉ hiện tại và lưu dữ liệu vào bộ đệm. Sau đó, nó tăng địa chỉ, để lần gọi tiếp theo đọc khối bộ nhớ tiếp theo. Bộ đệm được định kích thước dựa trên khối lớn nhất mà `HTTPClient` sẽ gửi đến REST API tại một thời điểm.

    > 💁 Xóa bộ nhớ flash phải được thực hiện bằng kích thước hạt, trong khi đọc thì không.

1. Trong phần `public` của lớp này, thêm một constructor:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    Constructor này thiết lập tất cả các trường để bắt đầu đọc từ đầu khối bộ nhớ flash, và tải khối dữ liệu đầu tiên vào bộ đệm.

1. Triển khai phương thức `write`. Stream này chỉ đọc dữ liệu, vì vậy phương thức này có thể không làm gì và trả về 0:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. Triển khai phương thức `peek`. Phương thức này trả về dữ liệu tại vị trí hiện tại mà không di chuyển stream. Gọi `peek` nhiều lần sẽ luôn trả về cùng một dữ liệu miễn là không có dữ liệu nào được đọc từ stream.

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. Triển khai hàm `available`. Hàm này trả về số byte có thể đọc từ stream, hoặc -1 nếu stream đã hoàn thành. Đối với lớp này, số byte tối đa có thể đọc sẽ không lớn hơn kích thước khối của HTTPClient. Khi stream này được sử dụng trong HTTP client, nó gọi hàm này để xem có bao nhiêu dữ liệu có sẵn, sau đó yêu cầu lượng dữ liệu đó để gửi đến REST API. Chúng ta không muốn mỗi khối lớn hơn kích thước khối của HTTP client, vì vậy nếu có nhiều hơn kích thước khối, kích thước khối sẽ được trả về. Nếu ít hơn, thì lượng dữ liệu có sẵn sẽ được trả về. Khi tất cả dữ liệu đã được truyền, -1 sẽ được trả về.

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

1. Triển khai phương thức `read` để trả về byte tiếp theo từ bộ đệm, tăng vị trí. Nếu vị trí vượt quá kích thước của bộ đệm, nó sẽ tải bộ đệm với khối tiếp theo từ bộ nhớ flash và đặt lại vị trí.

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

1. Trong tệp tiêu đề `speech_to_text.h`, thêm một chỉ thị bao gồm tệp tiêu đề mới này:

    ```cpp
    #include "flash_stream.h"
    ```

### Nhiệm vụ - chuyển đổi giọng nói thành văn bản

1. Giọng nói có thể được chuyển đổi thành văn bản bằng cách gửi âm thanh đến Dịch vụ Giọng nói thông qua REST API. REST API này có chứng chỉ khác với nhà phát hành mã, vì vậy thêm mã sau vào tệp tiêu đề `config.h` để định nghĩa chứng chỉ này:

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

1. Thêm một hằng số vào tệp này cho URL giọng nói mà không có vị trí. URL này sẽ được kết hợp với vị trí và ngôn ngữ sau để tạo URL đầy đủ.

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. Trong tệp tiêu đề `speech_to_text.h`, trong phần `private` của lớp `SpeechToText`, định nghĩa một trường cho WiFi Client sử dụng chứng chỉ giọng nói:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. Trong phương thức `init`, đặt chứng chỉ trên WiFi Client này:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. Thêm mã sau vào phần `public` của lớp `SpeechToText` để định nghĩa một phương thức chuyển đổi giọng nói thành văn bản:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. Thêm mã sau vào phương thức này để tạo một HTTP client sử dụng WiFi client được cấu hình với chứng chỉ giọng nói, và sử dụng URL giọng nói được đặt với vị trí và ngôn ngữ:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. Một số tiêu đề cần được đặt trên kết nối:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    Điều này đặt các tiêu đề cho việc ủy quyền sử dụng mã truy cập, định dạng âm thanh sử dụng tốc độ mẫu, và đặt rằng client mong đợi kết quả dưới dạng JSON.

1. Sau đó, thêm mã sau để thực hiện cuộc gọi REST API:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    Điều này tạo một `FlashStream` và sử dụng nó để truyền dữ liệu đến REST API.

1. Bên dưới đoạn mã này, thêm mã sau:

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

    Mã này kiểm tra mã phản hồi.

    Nếu mã phản hồi là 200, mã cho thành công, thì kết quả được lấy, giải mã từ JSON, và thuộc tính `DisplayText` được đặt vào biến `text`. Đây là thuộc tính mà phiên bản văn bản của giọng nói được trả về.

    Nếu mã phản hồi là 401, thì mã truy cập đã hết hạn (các mã này chỉ tồn tại trong 10 phút). Một mã truy cập mới được yêu cầu, và cuộc gọi được thực hiện lại.

    Nếu không, một lỗi được gửi đến serial monitor, và `text` được để trống.

1. Thêm mã sau vào cuối phương thức này để đóng HTTP client và trả về văn bản:

    ```cpp
    httpClient.end();

    return text;
    ```

1. Trong `main.cpp`, gọi phương thức `convertSpeechToText` mới này trong hàm `processAudio`, sau đó ghi giọng nói ra serial monitor:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. Biên dịch mã này, tải nó lên Wio Terminal của bạn và kiểm tra qua serial monitor. Khi bạn thấy `Ready` trong serial monitor, nhấn nút C (nút ở bên trái, gần công tắc nguồn nhất), và nói. 4 giây âm thanh sẽ được thu, sau đó chuyển đổi thành văn bản.

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

> 💁 Bạn có thể tìm mã này trong thư mục [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal).

😀 Chương trình chuyển đổi giọng nói thành văn bản của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.