<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c527ce85d69b1a3875366ec61cbed8aa",
  "translation_date": "2025-08-27T22:13:17+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-commands.md",
  "language_code": "vi"
}
-->
# Điều khiển đèn ngủ qua Internet - Phần cứng IoT ảo và Raspberry Pi

Trong phần này của bài học, bạn sẽ đăng ký nhận lệnh được gửi từ một MQTT broker đến Raspberry Pi hoặc thiết bị IoT ảo của bạn.

## Đăng ký nhận lệnh

Bước tiếp theo là đăng ký nhận các lệnh được gửi từ MQTT broker và phản hồi chúng.

### Nhiệm vụ

Đăng ký nhận lệnh.

1. Mở dự án đèn ngủ trong VS Code.

1. Nếu bạn đang sử dụng thiết bị IoT ảo, hãy đảm bảo terminal đang chạy môi trường ảo. Nếu bạn sử dụng Raspberry Pi, bạn sẽ không cần sử dụng môi trường ảo.

1. Thêm đoạn mã sau vào sau phần định nghĩa của `client_telemetry_topic`:

    ```python
    server_command_topic = id + '/commands'
    ```

    `server_command_topic` là chủ đề MQTT mà thiết bị sẽ đăng ký để nhận lệnh điều khiển LED.

1. Thêm đoạn mã sau ngay phía trên vòng lặp chính, sau dòng `mqtt_client.loop_start()`:

    ```python
    def handle_command(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
        if payload['led_on']:
            led.on()
        else:
            led.off()
    
    mqtt_client.subscribe(server_command_topic)
    mqtt_client.on_message = handle_command
    ```

    Đoạn mã này định nghĩa một hàm, `handle_command`, đọc một tin nhắn dưới dạng tài liệu JSON và tìm giá trị của thuộc tính `led_on`. Nếu giá trị là `True`, đèn LED sẽ được bật, nếu không thì đèn sẽ tắt.

    MQTT client sẽ đăng ký vào chủ đề mà server sẽ gửi tin nhắn và thiết lập hàm `handle_command` để được gọi khi một tin nhắn được nhận.

    > 💁 Trình xử lý `on_message` được gọi cho tất cả các chủ đề đã đăng ký. Nếu sau này bạn viết mã để lắng nghe nhiều chủ đề, bạn có thể lấy chủ đề mà tin nhắn được gửi đến từ đối tượng `message` được truyền vào hàm xử lý.

1. Chạy mã theo cách tương tự như bạn đã chạy mã từ phần trước của bài tập. Nếu bạn đang sử dụng thiết bị IoT ảo, hãy đảm bảo ứng dụng CounterFit đang chạy và cảm biến ánh sáng cùng đèn LED đã được tạo trên các chân đúng.

1. Điều chỉnh mức độ ánh sáng được phát hiện bởi thiết bị vật lý hoặc ảo của bạn. Các tin nhắn được nhận và lệnh được gửi sẽ được ghi vào terminal. Đèn LED cũng sẽ được bật và tắt tùy thuộc vào mức độ ánh sáng.

> 💁 Bạn có thể tìm thấy đoạn mã này trong thư mục [code-commands/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/virtual-device) hoặc thư mục [code-commands/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/pi).

😀 Bạn đã lập trình thành công thiết bị của mình để phản hồi các lệnh từ một MQTT broker.

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.