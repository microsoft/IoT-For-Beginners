<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-27T22:13:57+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "vi"
}
-->
# Điều khiển đèn ngủ qua Internet - Phần cứng IoT ảo và Raspberry Pi

Trong phần này của bài học, bạn sẽ gửi dữ liệu đo lường với mức độ ánh sáng từ Raspberry Pi hoặc thiết bị IoT ảo của mình đến một MQTT broker.

## Gửi dữ liệu đo lường

Bước tiếp theo là tạo một tài liệu JSON chứa dữ liệu đo lường và gửi nó đến MQTT broker.

### Nhiệm vụ

Gửi dữ liệu đo lường đến MQTT broker.

1. Mở dự án đèn ngủ trong VS Code.

1. Nếu bạn đang sử dụng thiết bị IoT ảo, hãy đảm bảo terminal đang chạy môi trường ảo. Nếu bạn sử dụng Raspberry Pi, bạn sẽ không cần sử dụng môi trường ảo.

1. Thêm dòng import sau vào đầu file `app.py`:

    ```python
    import json
    ```

    Thư viện `json` được sử dụng để mã hóa dữ liệu đo lường dưới dạng tài liệu JSON.

1. Thêm đoạn mã sau sau khai báo `client_name`:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    `client_telemetry_topic` là chủ đề MQTT mà thiết bị sẽ sử dụng để gửi mức độ ánh sáng.

1. Thay thế nội dung của vòng lặp `while True:` ở cuối file bằng đoạn mã sau:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    Đoạn mã này đóng gói mức độ ánh sáng vào một tài liệu JSON và gửi nó đến MQTT broker. Sau đó, chương trình sẽ tạm dừng để giảm tần suất gửi tin nhắn.

1. Chạy mã theo cách bạn đã chạy mã từ phần trước của bài tập. Nếu bạn đang sử dụng thiết bị IoT ảo, hãy đảm bảo ứng dụng CounterFit đang chạy và cảm biến ánh sáng cùng đèn LED đã được tạo trên các chân đúng.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 Bạn có thể tìm thấy đoạn mã này trong thư mục [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) hoặc [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi).

😀 Bạn đã gửi dữ liệu đo lường thành công từ thiết bị của mình.

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, nên sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.