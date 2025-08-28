<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cbb8c285bc64c5192fae3368fb5077d2",
  "translation_date": "2025-08-27T23:45:36+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/single-board-computer-gps-decode.md",
  "language_code": "vi"
}
-->
# Giải mã dữ liệu GPS - Phần cứng IoT Ảo và Raspberry Pi

Trong phần này của bài học, bạn sẽ giải mã các thông điệp NMEA được đọc từ cảm biến GPS bởi Raspberry Pi hoặc Thiết bị IoT Ảo, và trích xuất vĩ độ và kinh độ.

## Giải mã dữ liệu GPS

Khi dữ liệu NMEA thô đã được đọc từ cổng nối tiếp, nó có thể được giải mã bằng cách sử dụng thư viện NMEA mã nguồn mở.

### Nhiệm vụ - giải mã dữ liệu GPS

Lập trình thiết bị để giải mã dữ liệu GPS.

1. Mở dự án ứng dụng `gps-sensor` nếu nó chưa được mở.

1. Cài đặt gói Pip `pynmea2`. Gói này chứa mã để giải mã các thông điệp NMEA.

    ```sh
    pip3 install pynmea2
    ```

1. Thêm đoạn mã sau vào phần import trong tệp `app.py` để nhập mô-đun `pynmea2`:

    ```python
    import pynmea2
    ```

1. Thay thế nội dung của hàm `print_gps_data` bằng đoạn mã sau:

    ```python
    msg = pynmea2.parse(line)
    if msg.sentence_type == 'GGA':
        lat = pynmea2.dm_to_sd(msg.lat)
        lon = pynmea2.dm_to_sd(msg.lon)

        if msg.lat_dir == 'S':
            lat = lat * -1

        if msg.lon_dir == 'W':
            lon = lon * -1

        print(f'{lat},{lon} - from {msg.num_sats} satellites')
    ```

    Đoạn mã này sẽ sử dụng thư viện `pynmea2` để phân tích dòng dữ liệu được đọc từ cổng nối tiếp UART.

    Nếu loại câu của thông điệp là `GGA`, thì đây là một thông điệp xác định vị trí và sẽ được xử lý. Các giá trị vĩ độ và kinh độ được đọc từ thông điệp và chuyển đổi sang độ thập phân từ định dạng NMEA `(d)ddmm.mmmm`. Hàm `dm_to_sd` thực hiện việc chuyển đổi này.

    Sau đó, hướng của vĩ độ được kiểm tra, nếu vĩ độ là phía nam, giá trị sẽ được chuyển thành số âm. Tương tự với kinh độ, nếu là phía tây thì nó cũng được chuyển thành số âm.

    Cuối cùng, tọa độ được in ra màn hình, cùng với số lượng vệ tinh được sử dụng để xác định vị trí.

1. Chạy mã. Nếu bạn đang sử dụng thiết bị IoT ảo, hãy đảm bảo rằng ứng dụng CounterFit đang chạy và dữ liệu GPS đang được gửi.

    ```output
    pi@raspberrypi:~/gps-sensor $ python3 app.py 
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Bạn có thể tìm thấy đoạn mã này trong thư mục [code-gps-decode/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/virtual-device), hoặc thư mục [code-gps-decode/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/pi).

😀 Chương trình cảm biến GPS của bạn với chức năng giải mã dữ liệu đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.