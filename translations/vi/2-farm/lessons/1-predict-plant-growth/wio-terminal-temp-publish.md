<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-27T21:28:33+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "vi"
}
-->
# Xuất bản nhiệt độ - Wio Terminal

Trong phần này của bài học, bạn sẽ xuất bản giá trị nhiệt độ được Wio Terminal phát hiện qua MQTT để sau này có thể sử dụng để tính toán GDD.

## Xuất bản nhiệt độ

Khi nhiệt độ đã được đọc, nó có thể được xuất bản qua MQTT đến một đoạn mã 'máy chủ' sẽ đọc các giá trị và lưu trữ chúng để sẵn sàng sử dụng cho việc tính toán GDD. Vi điều khiển không tự động đọc thời gian từ Internet và theo dõi thời gian bằng đồng hồ thời gian thực, thiết bị cần được lập trình để làm điều này, với điều kiện nó có phần cứng cần thiết.

Để đơn giản hóa mọi thứ trong bài học này, thời gian sẽ không được gửi cùng với dữ liệu cảm biến, thay vào đó nó có thể được thêm vào bởi mã máy chủ sau khi nhận được các tin nhắn.

### Nhiệm vụ

Lập trình thiết bị để xuất bản dữ liệu nhiệt độ.

1. Mở dự án `temperature-sensor` trên Wio Terminal.

1. Lặp lại các bước bạn đã thực hiện trong bài học 4 để kết nối với MQTT và gửi dữ liệu telemetry. Bạn sẽ sử dụng cùng một Mosquitto broker công khai.

    Các bước thực hiện như sau:

    - Thêm thư viện Seeed WiFi và MQTT vào tệp `.ini`.
    - Thêm tệp cấu hình và mã để kết nối với WiFi.
    - Thêm mã để kết nối với MQTT broker.
    - Thêm mã để xuất bản dữ liệu telemetry.

    > ⚠️ Tham khảo [hướng dẫn kết nối với MQTT](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) và [hướng dẫn gửi dữ liệu telemetry](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) từ bài học 4 nếu cần.

1. Đảm bảo rằng `CLIENT_NAME` trong tệp tiêu đề `config.h` phản ánh dự án này:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. Đối với dữ liệu telemetry, thay vì gửi giá trị ánh sáng, hãy gửi giá trị nhiệt độ được đọc từ cảm biến DHT trong một thuộc tính của tài liệu JSON có tên là `temperature` bằng cách thay đổi hàm `loop` trong `main.cpp`:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. Giá trị nhiệt độ không cần phải được đọc quá thường xuyên - nó sẽ không thay đổi nhiều trong một khoảng thời gian ngắn, vì vậy hãy đặt `delay` trong hàm `loop` là 10 phút:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 Hàm `delay` nhận thời gian tính bằng mili giây, vì vậy để dễ đọc hơn, giá trị được truyền dưới dạng kết quả của một phép tính. 1.000ms trong một giây, 60 giây trong một phút, vì vậy 10 x (60 giây trong một phút) x (1.000ms trong một giây) sẽ tạo ra độ trễ 10 phút.

1. Tải lên mã này vào Wio Terminal của bạn và sử dụng serial monitor để xem nhiệt độ được gửi đến MQTT broker.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"temperature":25}
    Sending telemetry {"temperature":25}
    ```

> 💁 Bạn có thể tìm thấy mã này trong thư mục [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal).

😀 Bạn đã xuất bản thành công nhiệt độ dưới dạng dữ liệu telemetry từ thiết bị của mình.

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.