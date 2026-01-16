<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7f4ad0ef54f248b85b92187c94cf9dcb",
  "translation_date": "2025-08-27T22:35:05+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-sensor.md",
  "language_code": "vi"
}
-->
# Thêm cảm biến - Wio Terminal

Trong phần này của bài học, bạn sẽ sử dụng cảm biến ánh sáng trên Wio Terminal.

## Phần cứng

Cảm biến cho bài học này là **cảm biến ánh sáng** sử dụng [photodiode](https://wikipedia.org/wiki/Photodiode) để chuyển đổi ánh sáng thành tín hiệu điện. Đây là một cảm biến analog gửi giá trị số nguyên từ 0 đến 1,023, biểu thị lượng ánh sáng tương đối mà không được quy đổi sang bất kỳ đơn vị đo lường tiêu chuẩn nào như [lux](https://wikipedia.org/wiki/Lux).

Cảm biến ánh sáng được tích hợp trong Wio Terminal và có thể nhìn thấy qua cửa sổ nhựa trong suốt ở mặt sau.

![Cảm biến ánh sáng ở mặt sau của Wio Terminal](../../../../../translated_images/vi/wio-light-sensor.b1f529f3c95f5165.webp)

## Lập trình cảm biến ánh sáng

Thiết bị giờ đây có thể được lập trình để sử dụng cảm biến ánh sáng tích hợp.

### Nhiệm vụ

Lập trình thiết bị.

1. Mở dự án đèn ngủ trong VS Code mà bạn đã tạo ở phần trước của bài tập này.

1. Thêm dòng sau vào cuối hàm `setup`:

    ```cpp
    pinMode(WIO_LIGHT, INPUT);
    ```

    Dòng này cấu hình các chân được sử dụng để giao tiếp với phần cứng cảm biến.

    Chân `WIO_LIGHT` là số của chân GPIO được kết nối với cảm biến ánh sáng tích hợp. Chân này được đặt là `INPUT`, nghĩa là nó kết nối với một cảm biến và dữ liệu sẽ được đọc từ chân này.

1. Xóa nội dung của hàm `loop`.

1. Thêm đoạn mã sau vào hàm `loop` hiện đang trống.

    ```cpp
    int light = analogRead(WIO_LIGHT);
    Serial.print("Light value: ");
    Serial.println(light);
    ```

    Đoạn mã này đọc giá trị analog từ chân `WIO_LIGHT`. Giá trị này là từ 0-1,023 từ cảm biến ánh sáng tích hợp. Giá trị này sau đó được gửi đến cổng serial để bạn có thể đọc nó trong Serial Monitor khi đoạn mã này đang chạy. `Serial.print` ghi văn bản mà không có dòng mới ở cuối, vì vậy mỗi dòng sẽ bắt đầu với `Light value:` và kết thúc với giá trị ánh sáng thực tế.

1. Thêm một khoảng thời gian trễ nhỏ một giây (1,000ms) ở cuối hàm `loop` vì mức ánh sáng không cần được kiểm tra liên tục. Khoảng thời gian trễ giúp giảm tiêu thụ năng lượng của thiết bị.

    ```cpp
    delay(1000);
    ```

1. Kết nối lại Wio Terminal với máy tính của bạn và tải lên đoạn mã mới như bạn đã làm trước đó.

1. Kết nối Serial Monitor. Giá trị ánh sáng sẽ được xuất ra terminal. Che và mở cảm biến ánh sáng ở mặt sau của Wio Terminal, và các giá trị sẽ thay đổi.

    ```output
    > Executing task: platformio device monitor <

    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Light value: 4
    Light value: 5
    Light value: 4
    Light value: 158
    Light value: 343
    Light value: 348
    Light value: 344
    ```

> 💁 Bạn có thể tìm thấy đoạn mã này trong thư mục [code-sensor/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/wio-terminal).

😀 Việc thêm cảm biến vào chương trình đèn ngủ của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn tham khảo chính thức. Đối với các thông tin quan trọng, chúng tôi khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp từ con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.