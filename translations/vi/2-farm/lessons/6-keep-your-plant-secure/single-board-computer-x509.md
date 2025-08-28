<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9aea84bcc7520222b0e1c50469d62d6a",
  "translation_date": "2025-08-28T01:29:34+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/single-board-computer-x509.md",
  "language_code": "vi"
}
-->
# Sử dụng chứng chỉ X.509 trong mã thiết bị của bạn - Phần cứng IoT ảo và Raspberry Pi

Trong phần này của bài học, bạn sẽ kết nối thiết bị IoT ảo hoặc Raspberry Pi của mình với IoT Hub bằng chứng chỉ X.509.

## Kết nối thiết bị của bạn với IoT Hub

Bước tiếp theo là kết nối thiết bị của bạn với IoT Hub bằng chứng chỉ X.509.

### Nhiệm vụ - kết nối với IoT Hub

1. Sao chép các tệp khóa và chứng chỉ vào thư mục chứa mã thiết bị IoT của bạn. Nếu bạn đang sử dụng Raspberry Pi thông qua VS Code Remote SSH và đã tạo các khóa trên PC hoặc Mac của mình, bạn có thể kéo và thả các tệp vào trình khám phá trong VS Code để sao chép chúng.

1. Mở tệp `app.py`

1. Để kết nối bằng chứng chỉ X.509, bạn sẽ cần tên máy chủ của IoT Hub và chứng chỉ X.509. Bắt đầu bằng cách tạo một biến chứa tên máy chủ bằng cách thêm đoạn mã sau trước khi tạo thiết bị client:

    ```python
    host_name = "<host_name>"
    ```

    Thay thế `<host_name>` bằng tên máy chủ của IoT Hub của bạn. Bạn có thể lấy thông tin này từ phần `HostName` trong `connection_string`. Đây sẽ là tên của IoT Hub của bạn, kết thúc bằng `.azure-devices.net`.

1. Bên dưới đoạn này, khai báo một biến với ID thiết bị:

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. Bạn sẽ cần một thể hiện của lớp `X509` chứa các tệp chứng chỉ X.509. Thêm `X509` vào danh sách các lớp được nhập từ mô-đun `azure.iot.device`:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. Tạo một thể hiện của lớp `X509` sử dụng các tệp chứng chỉ và khóa của bạn bằng cách thêm đoạn mã này bên dưới khai báo `host_name`:

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    Điều này sẽ tạo lớp `X509` sử dụng các tệp `soil-moisture-sensor-x509-cert.pem` và `soil-moisture-sensor-x509-key.pem` đã được tạo trước đó.

1. Thay thế dòng mã tạo `device_client` từ chuỗi kết nối bằng đoạn mã sau:

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    Điều này sẽ kết nối bằng chứng chỉ X.509 thay vì chuỗi kết nối.
    
1. Xóa dòng chứa biến `connection_string`.

1. Chạy mã của bạn. Theo dõi các tin nhắn được gửi đến IoT Hub và gửi các yêu cầu phương thức trực tiếp như trước. Bạn sẽ thấy thiết bị kết nối và gửi các chỉ số độ ẩm đất, cũng như nhận các yêu cầu phương thức trực tiếp.

> 💁 Bạn có thể tìm thấy đoạn mã này trong thư mục [code/pi](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/pi) hoặc [code/virtual-device](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/virtual-device).

😀 Chương trình cảm biến độ ẩm đất của bạn đã được kết nối với IoT Hub bằng chứng chỉ X.509!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, nên sử dụng dịch vụ dịch thuật chuyên nghiệp từ con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.