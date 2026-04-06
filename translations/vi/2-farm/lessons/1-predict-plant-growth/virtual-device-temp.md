# Đo nhiệt độ - Phần cứng IoT ảo

Trong phần này của bài học, bạn sẽ thêm một cảm biến nhiệt độ vào thiết bị IoT ảo của mình.

## Phần cứng ảo

Thiết bị IoT ảo sẽ sử dụng một cảm biến độ ẩm và nhiệt độ Grove Digital được mô phỏng. Điều này giúp bài thực hành này tương tự như khi sử dụng Raspberry Pi với cảm biến Grove DHT11 thực tế.

Cảm biến này kết hợp một **cảm biến nhiệt độ** với một **cảm biến độ ẩm**, nhưng trong bài thực hành này, bạn chỉ quan tâm đến thành phần cảm biến nhiệt độ. Trong một thiết bị IoT thực tế, cảm biến nhiệt độ sẽ là một [thermistor](https://wikipedia.org/wiki/Thermistor) đo nhiệt độ bằng cách cảm nhận sự thay đổi điện trở khi nhiệt độ thay đổi. Các cảm biến nhiệt độ thường là cảm biến kỹ thuật số, tự động chuyển đổi điện trở đo được thành nhiệt độ theo độ C (hoặc Kelvin, hoặc Fahrenheit).

### Thêm cảm biến vào CounterFit

Để sử dụng cảm biến độ ẩm và nhiệt độ ảo, bạn cần thêm hai cảm biến này vào ứng dụng CounterFit.

#### Nhiệm vụ - thêm cảm biến vào CounterFit

Thêm cảm biến độ ẩm và nhiệt độ vào ứng dụng CounterFit.

1. Tạo một ứng dụng Python mới trên máy tính của bạn trong một thư mục có tên `temperature-sensor` với một tệp duy nhất có tên `app.py` và một môi trường ảo Python, sau đó thêm các gói pip của CounterFit.

    > ⚠️ Bạn có thể tham khảo [hướng dẫn tạo và thiết lập dự án Python CounterFit trong bài học 1 nếu cần](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Cài đặt một gói Pip bổ sung để cài đặt một shim CounterFit cho cảm biến DHT11. Đảm bảo rằng bạn đang cài đặt từ terminal với môi trường ảo đã được kích hoạt.

    ```sh
    pip install counterfit-shims-seeed-python-dht
    ```

1. Đảm bảo ứng dụng web CounterFit đang chạy.

1. Tạo một cảm biến độ ẩm:

    1. Trong hộp *Create sensor* ở bảng *Sensors*, thả xuống hộp *Sensor type* và chọn *Humidity*.

    1. Giữ nguyên *Units* là *Percentage*.

    1. Đảm bảo *Pin* được đặt là *5*.

    1. Chọn nút **Add** để tạo cảm biến độ ẩm trên Pin 5.

    ![Cài đặt cảm biến độ ẩm](../../../../../translated_images/vi/counterfit-create-humidity-sensor.2750e27b6f30e09c.webp)

    Cảm biến độ ẩm sẽ được tạo và xuất hiện trong danh sách cảm biến.

    ![Cảm biến độ ẩm đã được tạo](../../../../../translated_images/vi/counterfit-humidity-sensor.7b12f7f339e430cb.webp)

1. Tạo một cảm biến nhiệt độ:

    1. Trong hộp *Create sensor* ở bảng *Sensors*, thả xuống hộp *Sensor type* và chọn *Temperature*.

    1. Giữ nguyên *Units* là *Celsius*.

    1. Đảm bảo *Pin* được đặt là *6*.

    1. Chọn nút **Add** để tạo cảm biến nhiệt độ trên Pin 6.

    ![Cài đặt cảm biến nhiệt độ](../../../../../translated_images/vi/counterfit-create-temperature-sensor.199350ed34f7343d.webp)

    Cảm biến nhiệt độ sẽ được tạo và xuất hiện trong danh sách cảm biến.

    ![Cảm biến nhiệt độ đã được tạo](../../../../../translated_images/vi/counterfit-temperature-sensor.f0560236c96a9016.webp)

## Lập trình ứng dụng cảm biến nhiệt độ

Ứng dụng cảm biến nhiệt độ giờ đây có thể được lập trình bằng cách sử dụng các cảm biến CounterFit.

### Nhiệm vụ - lập trình ứng dụng cảm biến nhiệt độ

Lập trình ứng dụng cảm biến nhiệt độ.

1. Đảm bảo ứng dụng `temperature-sensor` đang được mở trong VS Code.

1. Mở tệp `app.py`.

1. Thêm đoạn mã sau vào đầu tệp `app.py` để kết nối ứng dụng với CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Thêm đoạn mã sau vào tệp `app.py` để nhập các thư viện cần thiết:

    ```python
    import time
    from counterfit_shims_seeed_python_dht import DHT
    ```

    Lệnh `from seeed_dht import DHT` nhập lớp `DHT` để tương tác với cảm biến nhiệt độ Grove ảo bằng một shim từ module `counterfit_shims_seeed_python_dht`.

1. Thêm đoạn mã sau sau đoạn mã trên để tạo một thể hiện của lớp quản lý cảm biến độ ẩm và nhiệt độ ảo:

    ```python
    sensor = DHT("11", 5)
    ```

    Điều này khai báo một thể hiện của lớp `DHT` quản lý cảm biến **D**igital **H**umidity và **T**emperature ảo. Tham số đầu tiên cho biết cảm biến đang được sử dụng là cảm biến *DHT11* ảo. Tham số thứ hai cho biết cảm biến được kết nối với cổng `5`.

    > 💁 CounterFit mô phỏng cảm biến độ ẩm và nhiệt độ kết hợp này bằng cách kết nối với 2 cảm biến, một cảm biến độ ẩm trên pin được chỉ định khi lớp `DHT` được tạo, và một cảm biến nhiệt độ chạy trên pin tiếp theo. Nếu cảm biến độ ẩm ở pin 5, shim sẽ mong đợi cảm biến nhiệt độ ở pin 6.

1. Thêm một vòng lặp vô hạn sau đoạn mã trên để lấy giá trị cảm biến nhiệt độ và in ra console:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    Lệnh gọi `sensor.read()` trả về một tuple gồm độ ẩm và nhiệt độ. Bạn chỉ cần giá trị nhiệt độ, vì vậy giá trị độ ẩm sẽ bị bỏ qua. Giá trị nhiệt độ sau đó được in ra console.

1. Thêm một khoảng nghỉ nhỏ mười giây ở cuối vòng lặp `loop` vì không cần kiểm tra mức nhiệt độ liên tục. Khoảng nghỉ giúp giảm mức tiêu thụ năng lượng của thiết bị.

    ```python
    time.sleep(10)
    ```

1. Từ Terminal của VS Code với môi trường ảo đã được kích hoạt, chạy lệnh sau để chạy ứng dụng Python của bạn:

    ```sh
    python app.py
    ```

1. Từ ứng dụng CounterFit, thay đổi giá trị của cảm biến nhiệt độ mà ứng dụng sẽ đọc. Bạn có thể thực hiện điều này theo hai cách:

    * Nhập một số vào hộp *Value* của cảm biến nhiệt độ, sau đó chọn nút **Set**. Số bạn nhập sẽ là giá trị được cảm biến trả về.

    * Đánh dấu vào ô *Random*, và nhập giá trị *Min* và *Max*, sau đó chọn nút **Set**. Mỗi lần cảm biến đọc giá trị, nó sẽ đọc một số ngẫu nhiên giữa *Min* và *Max*.

    Bạn sẽ thấy các giá trị bạn đặt xuất hiện trong console. Thay đổi *Value* hoặc cài đặt *Random* để thấy giá trị thay đổi.

    ```output
    (.venv) ➜  temperature-sensor python app.py
    Temperature 28.25°C
    Temperature 30.71°C
    Temperature 25.17°C
    ```

> 💁 Bạn có thể tìm thấy đoạn mã này trong thư mục [code-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/virtual-device).

😀 Chương trình cảm biến nhiệt độ của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.