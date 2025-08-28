<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "90fb93446e03c38f3c0e4009c2471906",
  "translation_date": "2025-08-27T22:21:21+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md",
  "language_code": "vi"
}
-->
# Điều khiển đèn ngủ qua Internet - Phần cứng IoT ảo và Raspberry Pi

Thiết bị IoT cần được lập trình để giao tiếp với *test.mosquitto.org* bằng MQTT nhằm gửi các giá trị đo lường từ cảm biến ánh sáng và nhận lệnh để điều khiển đèn LED.

Trong phần này của bài học, bạn sẽ kết nối Raspberry Pi hoặc thiết bị IoT ảo của mình với một MQTT broker.

## Cài đặt gói MQTT client

Để giao tiếp với MQTT broker, bạn cần cài đặt một thư viện MQTT thông qua pip, trên Raspberry Pi của bạn hoặc trong môi trường ảo nếu bạn đang sử dụng thiết bị ảo.

### Nhiệm vụ

Cài đặt gói pip

1. Mở dự án đèn ngủ trong VS Code.

1. Nếu bạn đang sử dụng thiết bị IoT ảo, hãy đảm bảo terminal đang chạy môi trường ảo. Nếu bạn sử dụng Raspberry Pi, bạn sẽ không cần môi trường ảo.

1. Chạy lệnh sau để cài đặt gói pip MQTT:

    ```sh
    pip3 install paho-mqtt
    ```

## Lập trình thiết bị

Thiết bị đã sẵn sàng để lập trình.

### Nhiệm vụ

Viết mã cho thiết bị.

1. Thêm dòng import sau vào đầu file `app.py`:

    ```python
    import paho.mqtt.client as mqtt
    ```

    Thư viện `paho.mqtt.client` cho phép ứng dụng của bạn giao tiếp qua MQTT.

1. Thêm đoạn mã sau sau phần định nghĩa cảm biến ánh sáng và đèn LED:

    ```python
    id = '<ID>'

    client_name = id + 'nightlight_client'
    ```

    Thay thế `<ID>` bằng một ID duy nhất sẽ được sử dụng làm tên của client thiết bị này, và sau đó là các chủ đề mà thiết bị này sẽ xuất bản và đăng ký. Broker *test.mosquitto.org* là công cộng và được nhiều người sử dụng, bao gồm cả các học viên khác đang làm bài tập này. Việc có tên client MQTT và tên chủ đề duy nhất đảm bảo mã của bạn không bị xung đột với bất kỳ ai khác. Bạn cũng sẽ cần ID này khi tạo mã server sau trong bài tập này.

    > 💁 Bạn có thể sử dụng một trang web như [GUIDGen](https://www.guidgen.com) để tạo một ID duy nhất.

    `client_name` là tên duy nhất cho client MQTT này trên broker.

1. Thêm đoạn mã sau bên dưới đoạn mã mới này để tạo một đối tượng MQTT client và kết nối với MQTT broker:

    ```python
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()

    print("MQTT connected!")
    ```

    Đoạn mã này tạo đối tượng client, kết nối với MQTT broker công cộng, và bắt đầu một vòng xử lý chạy trong một luồng nền, lắng nghe các tin nhắn trên bất kỳ chủ đề nào đã đăng ký.

1. Chạy mã theo cách tương tự như bạn đã chạy mã từ phần trước của bài tập. Nếu bạn đang sử dụng thiết bị IoT ảo, hãy đảm bảo ứng dụng CounterFit đang chạy và cảm biến ánh sáng cùng đèn LED đã được tạo trên các chân đúng.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Light level: 0
    Light level: 0
    ```

> 💁 Bạn có thể tìm thấy đoạn mã này trong thư mục [code-mqtt/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/virtual-device) hoặc [code-mqtt/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/pi).

😀 Bạn đã kết nối thành công thiết bị của mình với một MQTT broker.

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, nên sử dụng dịch vụ dịch thuật chuyên nghiệp từ con người. Chúng tôi không chịu trách nhiệm về bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.