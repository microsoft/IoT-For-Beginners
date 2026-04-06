# Phát hiện khoảng cách gần - Raspberry Pi

Trong phần này của bài học, bạn sẽ thêm một cảm biến khoảng cách vào Raspberry Pi và đọc khoảng cách từ nó.

## Phần cứng

Raspberry Pi cần một cảm biến khoảng cách.

Cảm biến bạn sẽ sử dụng là [Grove Time of Flight distance sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Cảm biến này sử dụng một module đo khoảng cách bằng laser để phát hiện khoảng cách. Cảm biến này có phạm vi từ 10mm đến 2000mm (1cm - 2m) và sẽ báo cáo giá trị trong phạm vi đó khá chính xác, với khoảng cách trên 1000mm được báo cáo là 8109mm.

Máy đo khoảng cách laser nằm ở mặt sau của cảm biến, đối diện với ổ cắm Grove.

Đây là một cảm biến I²C.

### Kết nối cảm biến Time of Flight

Cảm biến Time of Flight Grove có thể được kết nối với Raspberry Pi.

#### Nhiệm vụ - kết nối cảm biến Time of Flight

Kết nối cảm biến Time of Flight.

![Một cảm biến Time of Flight Grove](../../../../../translated_images/vi/grove-time-of-flight-sensor.d82ff2165bfded9f.webp)

1. Cắm một đầu của cáp Grove vào ổ cắm trên cảm biến Time of Flight. Cáp chỉ có thể cắm theo một chiều.

1. Khi Raspberry Pi đã tắt nguồn, kết nối đầu còn lại của cáp Grove vào một trong các ổ cắm I²C được đánh dấu **I²C** trên Grove Base hat gắn vào Pi. Các ổ cắm này nằm ở hàng dưới cùng, đối diện với các chân GPIO và gần khe cắm cáp camera.

![Cảm biến Time of Flight Grove được kết nối với ổ cắm I²C](../../../../../translated_images/vi/pi-time-of-flight-sensor.58c8dc04eb3bfb57.webp)

## Lập trình cảm biến Time of Flight

Raspberry Pi giờ đây có thể được lập trình để sử dụng cảm biến Time of Flight đã được gắn.

### Nhiệm vụ - lập trình cảm biến Time of Flight

Lập trình thiết bị.

1. Bật nguồn Pi và chờ nó khởi động.

1. Mở mã `fruit-quality-detector` trong VS Code, trực tiếp trên Pi hoặc kết nối qua tiện ích mở rộng Remote SSH.

1. Cài đặt gói rpi-vl53l0x Pip, một gói Python tương tác với cảm biến khoảng cách VL53L0X Time of Flight. Cài đặt nó bằng lệnh pip sau:

    ```sh
    pip install rpi-vl53l0x
    ```

1. Tạo một tệp mới trong dự án này có tên là `distance-sensor.py`.

    > 💁 Một cách dễ dàng để mô phỏng nhiều thiết bị IoT là thực hiện mỗi thiết bị trong một tệp Python khác nhau, sau đó chạy chúng cùng lúc.

1. Thêm đoạn mã sau vào tệp này:

    ```python
    import time
    
    from grove.i2c import Bus
    from rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Đoạn mã này nhập thư viện Grove I²C bus và một thư viện cảm biến cho phần cứng cảm biến cốt lõi được tích hợp trong cảm biến Time of Flight Grove.

1. Bên dưới đoạn mã này, thêm đoạn mã sau để truy cập cảm biến:

    ```python
    distance_sensor = VL53L0X(bus = Bus().bus)
    distance_sensor.begin()    
    ```

    Đoạn mã này khai báo một cảm biến khoảng cách sử dụng Grove I²C bus, sau đó khởi động cảm biến.

1. Cuối cùng, thêm một vòng lặp vô hạn để đọc khoảng cách:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Đoạn mã này chờ một giá trị sẵn sàng để đọc từ cảm biến, sau đó in nó ra màn hình console.

1. Chạy đoạn mã này.

    > 💁 Đừng quên tệp này có tên là `distance-sensor.py`! Hãy chắc chắn chạy nó bằng Python, không phải `app.py`.

1. Bạn sẽ thấy các phép đo khoảng cách xuất hiện trên màn hình console. Đặt các vật thể gần cảm biến và bạn sẽ thấy phép đo khoảng cách:

    ```output
    pi@raspberrypi:~/fruit-quality-detector $ python3 distance_sensor.py 
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Máy đo khoảng cách nằm ở mặt sau của cảm biến, vì vậy hãy chắc chắn sử dụng đúng mặt khi đo khoảng cách.

    ![Máy đo khoảng cách ở mặt sau của cảm biến Time of Flight đang hướng vào một quả chuối](../../../../../translated_images/vi/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 Bạn có thể tìm thấy đoạn mã này trong thư mục [code-proximity/pi](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/pi).

😀 Chương trình cảm biến khoảng cách của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.