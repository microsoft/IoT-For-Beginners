# Đo độ ẩm đất - Wio Terminal

Trong phần này của bài học, bạn sẽ thêm một cảm biến độ ẩm đất điện dung vào Wio Terminal và đọc các giá trị từ nó.

## Phần cứng

Wio Terminal cần một cảm biến độ ẩm đất điện dung.

Cảm biến bạn sẽ sử dụng là [Cảm biến độ ẩm đất điện dung](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), đo độ ẩm đất bằng cách phát hiện điện dung của đất, một thuộc tính thay đổi khi độ ẩm đất thay đổi. Khi độ ẩm đất tăng, điện áp giảm.

Đây là một cảm biến analog, vì vậy nó kết nối với các chân analog trên Wio Terminal, sử dụng một ADC tích hợp để tạo ra giá trị từ 0-1.023.

### Kết nối cảm biến độ ẩm đất

Cảm biến độ ẩm đất Grove có thể được kết nối với cổng analog/digital có thể cấu hình của Wio Terminal.

#### Nhiệm vụ - kết nối cảm biến độ ẩm đất

Kết nối cảm biến độ ẩm đất.

![Một cảm biến độ ẩm đất Grove](../../../../../translated_images/vi/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78b.webp)

1. Cắm một đầu của cáp Grove vào ổ cắm trên cảm biến độ ẩm đất. Nó chỉ có thể cắm theo một chiều.

1. Khi Wio Terminal chưa được kết nối với máy tính hoặc nguồn điện khác, kết nối đầu còn lại của cáp Grove vào ổ cắm Grove bên phải trên Wio Terminal khi bạn nhìn vào màn hình. Đây là ổ cắm xa nhất so với nút nguồn.

![Cảm biến độ ẩm đất Grove được kết nối với ổ cắm bên phải](../../../../../translated_images/vi/wio-soil-moisture-sensor.46919b61c3f6cb74.webp)

1. Cắm cảm biến độ ẩm đất vào đất. Nó có một 'đường giới hạn cao nhất' - một đường trắng ngang qua cảm biến. Cắm cảm biến đến đường này nhưng không vượt qua nó.

![Cảm biến độ ẩm đất Grove trong đất](../../../../../translated_images/vi/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

1. Bây giờ bạn có thể kết nối Wio Terminal với máy tính của mình.

## Lập trình cảm biến độ ẩm đất

Wio Terminal bây giờ có thể được lập trình để sử dụng cảm biến độ ẩm đất đã kết nối.

### Nhiệm vụ - lập trình cảm biến độ ẩm đất

Lập trình thiết bị.

1. Tạo một dự án Wio Terminal mới bằng PlatformIO. Đặt tên dự án này là `soil-moisture-sensor`. Thêm mã vào hàm `setup` để cấu hình cổng serial.

    > ⚠️ Bạn có thể tham khảo [hướng dẫn tạo dự án PlatformIO trong dự án 1, bài học 1 nếu cần](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Không có thư viện nào cho cảm biến này, thay vào đó bạn có thể đọc từ chân analog bằng cách sử dụng hàm [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/) tích hợp của Arduino. Bắt đầu bằng cách cấu hình chân analog để nhận đầu vào, để có thể đọc giá trị từ nó, bằng cách thêm đoạn mã sau vào hàm `setup`.

    ```cpp
    pinMode(A0, INPUT);
    ```

    Đoạn mã này thiết lập chân `A0`, chân analog/digital kết hợp, làm chân đầu vào để có thể đọc điện áp từ đó.

1. Thêm đoạn mã sau vào hàm `loop` để đọc điện áp từ chân này:

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. Bên dưới đoạn mã này, thêm đoạn mã sau để in giá trị ra cổng serial:

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. Cuối cùng, thêm một khoảng trễ 10 giây ở cuối:

    ```cpp
    delay(10000);
    ```

1. Biên dịch và tải mã lên Wio Terminal.

    > ⚠️ Bạn có thể tham khảo [hướng dẫn tạo dự án PlatformIO trong dự án 1, bài học 1 nếu cần](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Sau khi tải lên, bạn có thể theo dõi độ ẩm đất bằng serial monitor. Thêm một ít nước vào đất hoặc rút cảm biến ra khỏi đất và quan sát giá trị thay đổi.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Soil Moisture: 526
    Soil Moisture: 529
    Soil Moisture: 521
    Soil Moisture: 494
    Soil Moisture: 454
    Soil Moisture: 456
    Soil Moisture: 395
    Soil Moisture: 388
    Soil Moisture: 394
    Soil Moisture: 391
    ```

    Trong ví dụ đầu ra trên, bạn có thể thấy điện áp giảm khi thêm nước.

> 💁 Bạn có thể tìm thấy đoạn mã này trong thư mục [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal).

😀 Chương trình cảm biến độ ẩm đất của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.