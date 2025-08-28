<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-08-28T00:23:04+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "vi"
}
-->
# Điều khiển đèn ngủ qua Internet - Wio Terminal

Trong phần này của bài học, bạn sẽ đăng ký nhận lệnh được gửi từ một MQTT broker đến Wio Terminal của bạn.

## Đăng ký nhận lệnh

Bước tiếp theo là đăng ký nhận các lệnh được gửi từ MQTT broker và phản hồi chúng.

### Nhiệm vụ

Đăng ký nhận lệnh.

1. Mở dự án đèn ngủ trong VS Code.

1. Thêm đoạn mã sau vào cuối tệp `config.h` để định nghĩa tên chủ đề (topic) cho các lệnh:

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    `SERVER_COMMAND_TOPIC` là chủ đề mà thiết bị sẽ đăng ký để nhận các lệnh điều khiển LED.

1. Thêm dòng sau vào cuối hàm `reconnectMQTTClient` để đăng ký chủ đề lệnh khi MQTT client được kết nối lại:

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. Thêm đoạn mã sau bên dưới hàm `reconnectMQTTClient`.

    ```cpp
    void clientCallback(char *topic, uint8_t *payload, unsigned int length)
    {
        char buff[length + 1];
        for (int i = 0; i < length; i++)
        {
            buff[i] = (char)payload[i];
        }
        buff[length] = '\0';
    
        Serial.print("Message received:");
        Serial.println(buff);
    
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, buff);
        JsonObject obj = doc.as<JsonObject>();
    
        bool led_on = obj["led_on"];
    
        if (led_on)
            digitalWrite(D0, HIGH);
        else
            digitalWrite(D0, LOW);
    }
    ```

    Hàm này sẽ là callback mà MQTT client gọi khi nhận được một tin nhắn từ server.

    Tin nhắn được nhận dưới dạng một mảng các số nguyên 8-bit không dấu, vì vậy cần được chuyển đổi thành một mảng ký tự để xử lý như văn bản.

    Tin nhắn chứa một tài liệu JSON và được giải mã bằng thư viện ArduinoJson. Thuộc tính `led_on` của tài liệu JSON được đọc, và tùy thuộc vào giá trị, LED sẽ được bật hoặc tắt.

1. Thêm đoạn mã sau vào hàm `createMQTTClient`:

    ```cpp
    client.setCallback(clientCallback);
    ```

    Đoạn mã này thiết lập `clientCallback` làm callback được gọi khi một tin nhắn được nhận từ MQTT broker.

    > 💁 Trình xử lý `clientCallback` được gọi cho tất cả các chủ đề đã đăng ký. Nếu sau này bạn viết mã để lắng nghe nhiều chủ đề, bạn có thể lấy chủ đề mà tin nhắn được gửi đến từ tham số `topic` được truyền vào hàm callback.

1. Tải mã lên Wio Terminal của bạn và sử dụng Serial Monitor để xem mức độ ánh sáng được gửi đến MQTT broker.

1. Điều chỉnh mức độ ánh sáng được phát hiện bởi thiết bị vật lý hoặc ảo của bạn. Bạn sẽ thấy các tin nhắn được nhận và các lệnh được gửi trong terminal. Bạn cũng sẽ thấy LED được bật hoặc tắt tùy thuộc vào mức độ ánh sáng.

> 💁 Bạn có thể tìm thấy đoạn mã này trong thư mục [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal).

😀 Bạn đã lập trình thành công thiết bị của mình để phản hồi các lệnh từ một MQTT broker.

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.