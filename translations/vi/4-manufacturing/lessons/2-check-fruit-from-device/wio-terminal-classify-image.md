# Phân loại hình ảnh - Wio Terminal

Trong phần này của bài học, bạn sẽ gửi hình ảnh được chụp bởi camera đến dịch vụ Custom Vision để phân loại.

## Phân loại hình ảnh

Dịch vụ Custom Vision có một REST API mà bạn có thể gọi từ Wio Terminal để phân loại hình ảnh. REST API này được truy cập qua kết nối HTTPS - một kết nối HTTP an toàn.

Khi tương tác với các điểm cuối HTTPS, mã khách hàng cần yêu cầu chứng chỉ khóa công khai từ máy chủ được truy cập và sử dụng nó để mã hóa dữ liệu gửi đi. Trình duyệt web của bạn thực hiện điều này tự động, nhưng các vi điều khiển thì không. Bạn sẽ cần yêu cầu chứng chỉ này thủ công và sử dụng nó để tạo kết nối an toàn với REST API. Các chứng chỉ này không thay đổi, vì vậy một khi bạn đã có chứng chỉ, bạn có thể mã hóa cứng nó trong ứng dụng của mình.

Các chứng chỉ này chứa khóa công khai và không cần được bảo mật. Bạn có thể sử dụng chúng trong mã nguồn của mình và chia sẻ công khai trên các nền tảng như GitHub.

### Nhiệm vụ - thiết lập một SSL client

1. Mở dự án ứng dụng `fruit-quality-detector` nếu nó chưa được mở.

1. Mở tệp tiêu đề `config.h` và thêm đoạn sau:

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

    Đây là *Microsoft Azure DigiCert Global Root G2 certificate* - một trong những chứng chỉ được sử dụng bởi nhiều dịch vụ Azure trên toàn cầu.

    > 💁 Để kiểm tra rằng đây là chứng chỉ cần sử dụng, hãy chạy lệnh sau trên macOS hoặc Linux. Nếu bạn đang sử dụng Windows, bạn có thể chạy lệnh này bằng [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn):
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > Kết quả sẽ liệt kê chứng chỉ DigiCert Global Root G2.

1. Mở `main.cpp` và thêm chỉ thị include sau:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. Bên dưới các chỉ thị include, khai báo một instance của `WifiClientSecure`:

    ```cpp
    WiFiClientSecure client;
    ```

    Lớp này chứa mã để giao tiếp với các điểm cuối web qua HTTPS.

1. Trong phương thức `connectWiFi`, thiết lập WiFiClientSecure để sử dụng chứng chỉ DigiCert Global Root G2:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### Nhiệm vụ - phân loại hình ảnh

1. Thêm dòng sau vào danh sách `lib_deps` trong tệp `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Điều này nhập [ArduinoJson](https://arduinojson.org), một thư viện JSON cho Arduino, và sẽ được sử dụng để giải mã phản hồi JSON từ REST API.

1. Trong `config.h`, thêm các hằng số cho URL dự đoán và Key từ dịch vụ Custom Vision:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    Thay `<PREDICTION_URL>` bằng URL dự đoán từ Custom Vision. Thay `<PREDICTION_KEY>` bằng khóa dự đoán.

1. Trong `main.cpp`, thêm một chỉ thị include cho thư viện ArduinoJson:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Thêm hàm sau vào `main.cpp`, phía trên hàm `buttonPressed`.

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

    Mã này bắt đầu bằng việc khai báo một `HTTPClient` - một lớp chứa các phương thức để tương tác với REST APIs. Sau đó, nó kết nối client với URL dự đoán bằng instance `WiFiClientSecure` đã được thiết lập với khóa công khai Azure.

    Sau khi kết nối, nó gửi các header - thông tin về yêu cầu sắp tới sẽ được thực hiện với REST API. Header `Content-Type` chỉ ra rằng cuộc gọi API sẽ gửi dữ liệu nhị phân thô, header `Prediction-Key` truyền khóa dự đoán của Custom Vision.

    Tiếp theo, một yêu cầu POST được thực hiện đến HTTP client, tải lên một mảng byte. Mảng này sẽ chứa hình ảnh JPEG được chụp từ camera khi hàm này được gọi.

    > 💁 Yêu cầu POST được sử dụng để gửi dữ liệu và nhận phản hồi. Có các loại yêu cầu khác như yêu cầu GET để truy xuất dữ liệu. Yêu cầu GET được trình duyệt web của bạn sử dụng để tải các trang web.

    Yêu cầu POST trả về một mã trạng thái phản hồi. Đây là các giá trị được định nghĩa rõ ràng, với 200 có nghĩa là **OK** - yêu cầu POST đã thành công.

    > 💁 Bạn có thể xem tất cả các mã trạng thái phản hồi trong [Danh sách mã trạng thái HTTP trên Wikipedia](https://wikipedia.org/wiki/List_of_HTTP_status_codes)

    Nếu mã 200 được trả về, kết quả sẽ được đọc từ HTTP client. Đây là một phản hồi văn bản từ REST API với kết quả dự đoán dưới dạng tài liệu JSON. JSON có định dạng sau:

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

    Phần quan trọng ở đây là mảng `predictions`. Mảng này chứa các dự đoán, với một mục cho mỗi thẻ bao gồm tên thẻ và xác suất. Các xác suất được trả về là các số thập phân từ 0-1, với 0 là 0% khả năng khớp với thẻ, và 1 là 100% khả năng.

    > 💁 Các bộ phân loại hình ảnh sẽ trả về phần trăm cho tất cả các thẻ đã được sử dụng. Mỗi thẻ sẽ có một xác suất rằng hình ảnh khớp với thẻ đó.

    JSON này được giải mã, và các xác suất cho mỗi thẻ được gửi đến serial monitor.

1. Trong hàm `buttonPressed`, thay thế mã lưu vào thẻ SD bằng một cuộc gọi đến `classifyImage`, hoặc thêm nó sau khi hình ảnh được ghi, nhưng **trước khi** bộ đệm bị xóa:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 Nếu bạn thay thế mã lưu vào thẻ SD, bạn có thể dọn dẹp mã của mình bằng cách xóa các hàm `setupSDCard` và `saveToSDCard`.

1. Tải lên và chạy mã của bạn. Hướng camera vào một số loại trái cây và nhấn nút C. Bạn sẽ thấy kết quả trong serial monitor:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    Bạn sẽ có thể xem hình ảnh đã chụp và các giá trị này trong tab **Predictions** của Custom Vision.

    ![Một quả chuối trong Custom Vision được dự đoán chín 56.8% và chưa chín 43.1%](../../../../../translated_images/vi/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 Bạn có thể tìm thấy mã này trong thư mục [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal).

😀 Chương trình phân loại chất lượng trái cây của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.