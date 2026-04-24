# Phát hiện khoảng cách - Phần cứng IoT ảo

Trong phần này của bài học, bạn sẽ thêm một cảm biến khoảng cách vào thiết bị IoT ảo và đọc khoảng cách từ nó.

## Phần cứng

Thiết bị IoT ảo sẽ sử dụng một cảm biến khoảng cách được mô phỏng.

Trong một thiết bị IoT vật lý, bạn sẽ sử dụng một cảm biến với mô-đun đo khoảng cách bằng laser để phát hiện khoảng cách.

### Thêm cảm biến khoảng cách vào CounterFit

Để sử dụng cảm biến khoảng cách ảo, bạn cần thêm một cảm biến vào ứng dụng CounterFit.

#### Nhiệm vụ - thêm cảm biến khoảng cách vào CounterFit

Thêm cảm biến khoảng cách vào ứng dụng CounterFit.

1. Mở mã `fruit-quality-detector` trong VS Code và đảm bảo môi trường ảo đã được kích hoạt.

1. Cài đặt một gói Pip bổ sung để cài đặt một CounterFit shim có thể giao tiếp với cảm biến khoảng cách bằng cách mô phỏng gói Pip [rpi-vl53l0x](https://pypi.org/project/rpi-vl53l0x/), một gói Python tương tác với [cảm biến khoảng cách VL53L0X](https://wiki.seeedstudio.com/Grove-Time_of_Flight_Distance_Sensor-VL53L0X/). Đảm bảo bạn đang cài đặt từ terminal với môi trường ảo đã được kích hoạt.

    ```sh
    pip install counterfit-shims-rpi-vl53l0x
    ```

1. Đảm bảo ứng dụng web CounterFit đang chạy.

1. Tạo một cảm biến khoảng cách:

    1. Trong hộp *Create sensor* ở bảng *Sensors*, thả xuống hộp *Sensor type* và chọn *Distance*.

    1. Để *Units* là `Millimeter`.

    1. Cảm biến này là cảm biến I²C, vì vậy hãy đặt địa chỉ là `0x29`. Nếu bạn sử dụng cảm biến VL53L0X vật lý, nó sẽ được mã hóa cứng với địa chỉ này.

    1. Chọn nút **Add** để tạo cảm biến khoảng cách.

    ![Cài đặt cảm biến khoảng cách](../../../../../translated_images/vi/counterfit-create-distance-sensor.967c9fb98f27888d.webp)

    Cảm biến khoảng cách sẽ được tạo và xuất hiện trong danh sách cảm biến.

    ![Cảm biến khoảng cách đã được tạo](../../../../../translated_images/vi/counterfit-distance-sensor.079eefeeea0b68af.webp)

## Lập trình cảm biến khoảng cách

Thiết bị IoT ảo giờ đây có thể được lập trình để sử dụng cảm biến khoảng cách được mô phỏng.

### Nhiệm vụ - lập trình cảm biến đo thời gian bay

1. Tạo một tệp mới trong dự án `fruit-quality-detector` có tên `distance-sensor.py`.

    > 💁 Một cách dễ dàng để mô phỏng nhiều thiết bị IoT là thực hiện mỗi thiết bị trong một tệp Python khác nhau, sau đó chạy chúng cùng lúc.

1. Bắt đầu kết nối với CounterFit bằng đoạn mã sau:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Thêm đoạn mã sau bên dưới:

    ```python
    import time
    
    from counterfit_shims_rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Đoạn mã này nhập thư viện shim cho cảm biến đo thời gian bay VL53L0X.

1. Bên dưới đoạn mã này, thêm đoạn mã sau để truy cập cảm biến:

    ```python
    distance_sensor = VL53L0X()
    distance_sensor.begin()
    ```

    Đoạn mã này khai báo một cảm biến khoảng cách, sau đó khởi động cảm biến.

1. Cuối cùng, thêm một vòng lặp vô hạn để đọc khoảng cách:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Đoạn mã này chờ một giá trị sẵn sàng để đọc từ cảm biến, sau đó in giá trị đó ra console.

1. Chạy đoạn mã này.

    > 💁 Đừng quên tệp này có tên là `distance-sensor.py`! Đảm bảo chạy nó bằng Python, không phải `app.py`.

1. Bạn sẽ thấy các giá trị đo khoảng cách xuất hiện trong console. Thay đổi giá trị trong CounterFit để thấy giá trị này thay đổi, hoặc sử dụng các giá trị ngẫu nhiên.

    ```output
    (.venv) ➜  fruit-quality-detector python distance-sensor.py 
    Distance = 37 mm
    Distance = 42 mm
    Distance = 29 mm
    ```

> 💁 Bạn có thể tìm thấy đoạn mã này trong thư mục [code-proximity/virtual-iot-device](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/virtual-iot-device).

😀 Chương trình cảm biến khoảng cách của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.