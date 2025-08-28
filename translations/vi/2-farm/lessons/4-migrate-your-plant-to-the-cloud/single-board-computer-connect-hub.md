<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-28T01:36:50+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "vi"
}
-->
# Kết nối thiết bị IoT của bạn với đám mây - Phần cứng IoT ảo và Raspberry Pi

Trong phần này của bài học, bạn sẽ kết nối thiết bị IoT ảo hoặc Raspberry Pi của mình với IoT Hub để gửi dữ liệu đo lường và nhận lệnh.

## Kết nối thiết bị của bạn với IoT Hub

Bước tiếp theo là kết nối thiết bị của bạn với IoT Hub.

### Nhiệm vụ - kết nối với IoT Hub

1. Mở thư mục `soil-moisture-sensor` trong VS Code. Đảm bảo môi trường ảo đang chạy trong terminal nếu bạn đang sử dụng thiết bị IoT ảo.

1. Cài đặt một số gói Pip bổ sung:

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` là một thư viện để giao tiếp với IoT Hub của bạn.

1. Thêm các dòng import sau vào đầu tệp `app.py`, bên dưới các dòng import hiện có:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    Đoạn mã này import SDK để giao tiếp với IoT Hub của bạn.

1. Xóa dòng `import paho.mqtt.client as mqtt` vì thư viện này không còn cần thiết. Xóa toàn bộ mã MQTT bao gồm tên chủ đề, tất cả mã sử dụng `mqtt_client` và `handle_command`. Giữ vòng lặp `while True:`, chỉ cần xóa dòng `mqtt_client.publish` trong vòng lặp này.

1. Thêm đoạn mã sau bên dưới các dòng import:

    ```python
    connection_string = "<connection string>"
    ```

    Thay thế `<connection string>` bằng chuỗi kết nối mà bạn đã lấy cho thiết bị trước đó trong bài học này.

    > 💁 Đây không phải là cách làm tốt nhất. Chuỗi kết nối không bao giờ nên được lưu trữ trong mã nguồn, vì chúng có thể được kiểm tra vào hệ thống kiểm soát mã nguồn và bị phát hiện bởi bất kỳ ai. Chúng tôi làm điều này ở đây để đơn giản hóa. Lý tưởng nhất, bạn nên sử dụng một biến môi trường và một công cụ như [`python-dotenv`](https://pypi.org/project/python-dotenv/). Bạn sẽ học thêm về điều này trong bài học sắp tới.

1. Bên dưới đoạn mã này, thêm đoạn mã sau để tạo một đối tượng client thiết bị có thể giao tiếp với IoT Hub và kết nối nó:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. Chạy đoạn mã này. Bạn sẽ thấy thiết bị của mình kết nối.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## Gửi dữ liệu đo lường

Bây giờ thiết bị của bạn đã được kết nối, bạn có thể gửi dữ liệu đo lường đến IoT Hub thay vì MQTT broker.

### Nhiệm vụ - gửi dữ liệu đo lường

1. Thêm đoạn mã sau vào bên trong vòng lặp `while True`, ngay trước lệnh sleep:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    Đoạn mã này tạo một `Message` của IoT Hub chứa dữ liệu độ ẩm đất dưới dạng chuỗi JSON, sau đó gửi nó đến IoT Hub như một thông điệp từ thiết bị đến đám mây.

## Xử lý lệnh

Thiết bị của bạn cần xử lý một lệnh từ mã máy chủ để điều khiển relay. Lệnh này được gửi dưới dạng yêu cầu phương thức trực tiếp.

## Nhiệm vụ - xử lý yêu cầu phương thức trực tiếp

1. Thêm đoạn mã sau trước vòng lặp `while True`:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    Đoạn mã này định nghĩa một phương thức, `handle_method_request`, sẽ được gọi khi một phương thức trực tiếp được gọi bởi IoT Hub. Mỗi phương thức trực tiếp có một tên, và đoạn mã này mong đợi một phương thức có tên `relay_on` để bật relay, và `relay_off` để tắt relay.

    > 💁 Điều này cũng có thể được triển khai trong một yêu cầu phương thức trực tiếp duy nhất, truyền trạng thái mong muốn của relay trong payload có thể được truyền cùng với yêu cầu phương thức và có sẵn từ đối tượng `request`.

1. Các phương thức trực tiếp yêu cầu một phản hồi để thông báo cho mã gọi rằng chúng đã được xử lý. Thêm đoạn mã sau vào cuối hàm `handle_method_request` để tạo phản hồi cho yêu cầu:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    Đoạn mã này gửi một phản hồi cho yêu cầu phương thức trực tiếp với mã trạng thái HTTP là 200, và gửi phản hồi này trở lại IoT Hub.

1. Thêm đoạn mã sau bên dưới định nghĩa hàm này:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    Đoạn mã này thông báo cho client IoT Hub gọi hàm `handle_method_request` khi một phương thức trực tiếp được gọi.

> 💁 Bạn có thể tìm thấy đoạn mã này trong thư mục [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) hoặc [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device).

😀 Chương trình cảm biến độ ẩm đất của bạn đã được kết nối với IoT Hub!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.