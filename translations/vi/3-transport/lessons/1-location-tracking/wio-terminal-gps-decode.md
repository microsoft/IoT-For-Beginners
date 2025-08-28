<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-27T23:47:28+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "vi"
}
-->
# Giải mã dữ liệu GPS - Wio Terminal

Trong phần này của bài học, bạn sẽ giải mã các thông điệp NMEA được đọc từ cảm biến GPS bởi Wio Terminal, và trích xuất vĩ độ và kinh độ.

## Giải mã dữ liệu GPS

Khi dữ liệu thô NMEA đã được đọc từ cổng serial, nó có thể được giải mã bằng cách sử dụng thư viện NMEA mã nguồn mở.

### Nhiệm vụ - giải mã dữ liệu GPS

Lập trình thiết bị để giải mã dữ liệu GPS.

1. Mở dự án ứng dụng `gps-sensor` nếu nó chưa được mở.

1. Thêm một thư viện phụ thuộc cho thư viện [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) vào tệp `platformio.ini` của dự án. Thư viện này có mã để giải mã dữ liệu NMEA.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. Trong `main.cpp`, thêm một chỉ thị include cho thư viện TinyGPSPlus:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. Bên dưới khai báo của `Serial3`, khai báo một đối tượng TinyGPSPlus để xử lý các câu NMEA:

    ```cpp
    TinyGPSPlus gps;
    ```

1. Thay đổi nội dung của hàm `printGPSData` thành như sau:

    ```cpp
    if (gps.encode(Serial3.read()))
    {
        if (gps.location.isValid())
        {
            Serial.print(gps.location.lat(), 6);
            Serial.print(F(","));
            Serial.print(gps.location.lng(), 6);
            Serial.print(" - from ");
            Serial.print(gps.satellites.value());
            Serial.println(" satellites");
        }
    }
    ```

    Đoạn mã này đọc ký tự tiếp theo từ cổng serial UART vào bộ giải mã NMEA `gps`. Sau mỗi ký tự, nó sẽ kiểm tra xem bộ giải mã đã đọc được một câu hợp lệ chưa, sau đó kiểm tra xem nó đã đọc được một vị trí hợp lệ chưa. Nếu vị trí hợp lệ, nó sẽ gửi dữ liệu đến màn hình serial, cùng với số lượng vệ tinh đã đóng góp vào việc xác định vị trí này.

1. Biên dịch và tải mã lên Wio Terminal.

1. Sau khi tải lên, bạn có thể theo dõi dữ liệu vị trí GPS bằng cách sử dụng màn hình serial.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Bạn có thể tìm thấy đoạn mã này trong thư mục [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal).

😀 Chương trình cảm biến GPS của bạn với việc giải mã dữ liệu đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, nên sử dụng dịch vụ dịch thuật chuyên nghiệp từ con người. Chúng tôi không chịu trách nhiệm về bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.