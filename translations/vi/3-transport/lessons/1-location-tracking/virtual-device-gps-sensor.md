<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64f18a8f8aaa1fef5e7320e0992d8b3a",
  "translation_date": "2025-08-27T23:40:17+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/virtual-device-gps-sensor.md",
  "language_code": "vi"
}
-->
# Đọc dữ liệu GPS - Phần cứng IoT ảo

Trong phần này của bài học, bạn sẽ thêm cảm biến GPS vào thiết bị IoT ảo của mình và đọc các giá trị từ nó.

## Phần cứng ảo

Thiết bị IoT ảo sẽ sử dụng một cảm biến GPS mô phỏng, có thể truy cập qua UART thông qua cổng nối tiếp.

Một cảm biến GPS vật lý sẽ có một ăng-ten để thu sóng radio từ các vệ tinh GPS và chuyển đổi tín hiệu GPS thành dữ liệu GPS. Phiên bản ảo mô phỏng điều này bằng cách cho phép bạn đặt vĩ độ và kinh độ, gửi các câu NMEA thô, hoặc tải lên một tệp GPX với nhiều vị trí có thể được trả về tuần tự.

> 🎓 Các câu NMEA sẽ được đề cập sau trong bài học này

### Thêm cảm biến vào CounterFit

Để sử dụng cảm biến GPS ảo, bạn cần thêm nó vào ứng dụng CounterFit.

#### Nhiệm vụ - thêm cảm biến vào CounterFit

Thêm cảm biến GPS vào ứng dụng CounterFit.

1. Tạo một ứng dụng Python mới trên máy tính của bạn trong một thư mục có tên `gps-sensor` với một tệp duy nhất là `app.py` và một môi trường ảo Python, sau đó thêm các gói pip của CounterFit.

    > ⚠️ Bạn có thể tham khảo [hướng dẫn tạo và thiết lập dự án Python CounterFit trong bài học 1 nếu cần](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Cài đặt một gói Pip bổ sung để cài đặt một shim CounterFit có thể giao tiếp với các cảm biến dựa trên UART qua kết nối nối tiếp. Đảm bảo rằng bạn đang cài đặt từ một terminal với môi trường ảo đã được kích hoạt.

    ```sh
    pip install counterfit-shims-serial
    ```

1. Đảm bảo ứng dụng web CounterFit đang chạy.

1. Tạo một cảm biến GPS:

    1. Trong hộp *Create sensor* ở khung *Sensors*, thả xuống hộp *Sensor type* và chọn *UART GPS*.

    1. Giữ nguyên *Port* là */dev/ttyAMA0*.

    1. Chọn nút **Add** để tạo cảm biến GPS trên cổng `/dev/ttyAMA0`.

    ![Cài đặt cảm biến GPS](../../../../../translated_images/vi/counterfit-create-gps-sensor.6385dc9357d85ad1d47b4abb2525e7651fd498917d25eefc5a72feab09eedc70.png)

    Cảm biến GPS sẽ được tạo và xuất hiện trong danh sách cảm biến.

    ![Cảm biến GPS đã được tạo](../../../../../translated_images/vi/counterfit-gps-sensor.3fbb15af0a5367566f2f11324ef5a6f30861cdf2b497071a5e002b7aa473550e.png)

## Lập trình cảm biến GPS

Thiết bị IoT ảo bây giờ có thể được lập trình để sử dụng cảm biến GPS ảo.

### Nhiệm vụ - lập trình cảm biến GPS

Lập trình ứng dụng cảm biến GPS.

1. Đảm bảo ứng dụng `gps-sensor` đang mở trong VS Code.

1. Mở tệp `app.py`.

1. Thêm đoạn mã sau vào đầu `app.py` để kết nối ứng dụng với CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Thêm đoạn mã sau bên dưới để nhập một số thư viện cần thiết, bao gồm thư viện cho cổng nối tiếp CounterFit:

    ```python
    import time
    import counterfit_shims_serial
    
    serial = counterfit_shims_serial.Serial('/dev/ttyAMA0')
    ```

    Đoạn mã này nhập module `serial` từ gói Pip `counterfit_shims_serial`. Sau đó, nó kết nối với cổng nối tiếp `/dev/ttyAMA0` - đây là địa chỉ của cổng nối tiếp mà cảm biến GPS ảo sử dụng cho cổng UART.

1. Thêm đoạn mã sau bên dưới để đọc từ cổng nối tiếp và in các giá trị ra console:

    ```python
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    Một hàm có tên `print_gps_data` được định nghĩa để in dòng dữ liệu được truyền vào ra console.

    Tiếp theo, đoạn mã lặp vô hạn, đọc nhiều dòng văn bản từ cổng nối tiếp trong mỗi vòng lặp. Nó gọi hàm `print_gps_data` cho mỗi dòng.

    Sau khi đọc xong tất cả dữ liệu, vòng lặp sẽ ngủ 1 giây, sau đó thử lại.

1. Chạy đoạn mã này, đảm bảo bạn đang sử dụng một terminal khác với terminal mà ứng dụng CounterFit đang chạy, để ứng dụng CounterFit vẫn tiếp tục hoạt động.

1. Từ ứng dụng CounterFit, thay đổi giá trị của cảm biến GPS. Bạn có thể làm điều này bằng một trong các cách sau:

    * Đặt **Source** thành `Lat/Lon`, và đặt vĩ độ, kinh độ cụ thể cùng số lượng vệ tinh được sử dụng để lấy tín hiệu GPS. Giá trị này sẽ chỉ được gửi một lần, vì vậy hãy đánh dấu vào ô **Repeat** để dữ liệu lặp lại mỗi giây.

      ![Cảm biến GPS với Lat/Lon được chọn](../../../../../translated_images/vi/counterfit-gps-sensor-latlon.008c867d75464fbe7f84107cc57040df565ac07cb57d2f21db37d087d470197d.png)

    * Đặt **Source** thành `NMEA` và thêm một số câu NMEA vào hộp văn bản. Tất cả các giá trị này sẽ được gửi, với độ trễ 1 giây trước mỗi câu GGA (định vị) mới có thể được đọc.

      ![Cảm biến GPS với các câu NMEA được đặt](../../../../../translated_images/vi/counterfit-gps-sensor-nmea.c62eea442171e17e19528b051b104cfcecdc9cd18db7bc72920f29821ae63f73.png)

      Bạn có thể sử dụng công cụ như [nmeagen.org](https://www.nmeagen.org) để tạo các câu này bằng cách vẽ trên bản đồ. Các giá trị này sẽ chỉ được gửi một lần, vì vậy hãy đánh dấu vào ô **Repeat** để dữ liệu lặp lại sau mỗi giây khi tất cả đã được gửi.

    * Đặt **Source** thành tệp GPX, và tải lên một tệp GPX với các vị trí đường đi. Bạn có thể tải xuống các tệp GPX từ một số trang web bản đồ và đi bộ phổ biến, chẳng hạn như [AllTrails](https://www.alltrails.com/). Các tệp này chứa nhiều vị trí GPS dưới dạng đường đi, và cảm biến GPS sẽ trả về mỗi vị trí mới sau mỗi giây.

      ![Cảm biến GPS với tệp GPX được đặt](../../../../../translated_images/vi/counterfit-gps-sensor-gpxfile.8310b063ce8a425ccc8ebeec8306aeac5e8e55207f007d52c6e1194432a70cd9.png)

      Các giá trị này sẽ chỉ được gửi một lần, vì vậy hãy đánh dấu vào ô **Repeat** để dữ liệu lặp lại sau mỗi giây khi tất cả đã được gửi.

    Sau khi bạn đã cấu hình cài đặt GPS, chọn nút **Set** để áp dụng các giá trị này cho cảm biến.

1. Bạn sẽ thấy đầu ra thô từ cảm biến GPS, tương tự như sau:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    ```

> 💁 Bạn có thể tìm thấy đoạn mã này trong thư mục [code-gps/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps/virtual-device).

😀 Chương trình cảm biến GPS của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.