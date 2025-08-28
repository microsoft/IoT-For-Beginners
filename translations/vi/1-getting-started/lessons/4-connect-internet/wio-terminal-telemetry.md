<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-28T00:26:34+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "vi"
}
-->
# Điều khiển đèn ngủ qua Internet - Wio Terminal

Trong phần này của bài học, bạn sẽ gửi dữ liệu đo lường với mức độ ánh sáng từ Wio Terminal đến MQTT broker.

## Cài đặt thư viện JSON cho Arduino

Một cách phổ biến để gửi tin nhắn qua MQTT là sử dụng JSON. Có một thư viện Arduino dành cho JSON giúp việc đọc và viết tài liệu JSON trở nên dễ dàng hơn.

### Nhiệm vụ

Cài đặt thư viện Arduino JSON.

1. Mở dự án đèn ngủ trong VS Code.

1. Thêm dòng sau vào danh sách `lib_deps` trong tệp `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Điều này sẽ nhập [ArduinoJson](https://arduinojson.org), một thư viện JSON dành cho Arduino.

## Gửi dữ liệu đo lường

Bước tiếp theo là tạo một tài liệu JSON với dữ liệu đo lường và gửi nó đến MQTT broker.

### Nhiệm vụ - gửi dữ liệu đo lường

Gửi dữ liệu đo lường đến MQTT broker.

1. Thêm đoạn mã sau vào cuối tệp `config.h` để định nghĩa tên chủ đề dữ liệu đo lường cho MQTT broker:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC` là chủ đề mà thiết bị sẽ gửi mức độ ánh sáng đến.

1. Mở tệp `main.cpp`

1. Thêm chỉ thị `#include` sau vào đầu tệp:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Thêm đoạn mã sau vào bên trong hàm `loop`, ngay trước `delay`:

    ```cpp
    int light = analogRead(WIO_LIGHT);

    DynamicJsonDocument doc(1024);
    doc["light"] = light;

    string telemetry;
    serializeJson(doc, telemetry);

    Serial.print("Sending telemetry ");
    Serial.println(telemetry.c_str());

    client.publish(CLIENT_TELEMETRY_TOPIC.c_str(), telemetry.c_str());
    ```

    Đoạn mã này đọc mức độ ánh sáng, tạo một tài liệu JSON sử dụng ArduinoJson chứa mức độ này. Sau đó, tài liệu này được chuyển thành chuỗi và gửi lên chủ đề dữ liệu đo lường MQTT bởi MQTT client.

1. Tải mã lên Wio Terminal của bạn, và sử dụng Serial Monitor để xem mức độ ánh sáng được gửi đến MQTT broker.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 Bạn có thể tìm thấy đoạn mã này trong thư mục [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal).

😀 Bạn đã gửi dữ liệu đo lường từ thiết bị thành công.

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp từ con người. Chúng tôi không chịu trách nhiệm về bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.