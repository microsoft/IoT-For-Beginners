# Đo nhiệt độ - Wio Terminal

Trong phần này của bài học, bạn sẽ thêm một cảm biến nhiệt độ vào Wio Terminal và đọc giá trị nhiệt độ từ nó.

## Phần cứng

Wio Terminal cần một cảm biến nhiệt độ.

Cảm biến bạn sẽ sử dụng là [cảm biến độ ẩm và nhiệt độ DHT11](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), kết hợp 2 cảm biến trong một gói. Đây là loại cảm biến khá phổ biến, với nhiều cảm biến thương mại kết hợp nhiệt độ, độ ẩm và đôi khi cả áp suất khí quyển. Thành phần cảm biến nhiệt độ là một nhiệt điện trở hệ số nhiệt độ âm (NTC), một loại nhiệt điện trở mà điện trở giảm khi nhiệt độ tăng.

Đây là một cảm biến kỹ thuật số, vì vậy nó có một ADC tích hợp để tạo tín hiệu kỹ thuật số chứa dữ liệu nhiệt độ và độ ẩm mà vi điều khiển có thể đọc.

### Kết nối cảm biến nhiệt độ

Cảm biến nhiệt độ Grove có thể được kết nối với cổng kỹ thuật số của Wio Terminal.

#### Nhiệm vụ - kết nối cảm biến nhiệt độ

Kết nối cảm biến nhiệt độ.

![Một cảm biến nhiệt độ Grove](../../../../../translated_images/vi/grove-dht11.07f8eafceee17004.webp)

1. Cắm một đầu của cáp Grove vào ổ cắm trên cảm biến độ ẩm và nhiệt độ. Nó chỉ có thể cắm theo một chiều.

1. Khi Wio Terminal chưa được kết nối với máy tính hoặc nguồn điện khác, cắm đầu còn lại của cáp Grove vào ổ cắm Grove bên phải trên Wio Terminal khi bạn nhìn vào màn hình. Đây là ổ cắm xa nhất từ nút nguồn.

![Cảm biến nhiệt độ Grove được kết nối với ổ cắm bên phải](../../../../../translated_images/vi/wio-temperature-sensor.2934928f38c7f79a.webp)

## Lập trình cảm biến nhiệt độ

Bây giờ Wio Terminal có thể được lập trình để sử dụng cảm biến nhiệt độ đã được kết nối.

### Nhiệm vụ - lập trình cảm biến nhiệt độ

Lập trình thiết bị.

1. Tạo một dự án Wio Terminal mới hoàn toàn bằng PlatformIO. Gọi dự án này là `temperature-sensor`. Thêm mã vào hàm `setup` để cấu hình cổng serial.

    > ⚠️ Bạn có thể tham khảo [hướng dẫn tạo dự án PlatformIO trong dự án 1, bài học 1 nếu cần](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Thêm một thư viện phụ thuộc cho thư viện cảm biến độ ẩm và nhiệt độ Seeed Grove vào tệp `platformio.ini` của dự án:

    ```ini
    lib_deps =
        seeed-studio/Grove Temperature And Humidity Sensor @ 1.0.1
    ```

    > ⚠️ Bạn có thể tham khảo [hướng dẫn thêm thư viện vào dự án PlatformIO trong dự án 1, bài học 4 nếu cần](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md#install-the-wifi-and-mqtt-arduino-libraries).

1. Thêm các chỉ thị `#include` sau vào đầu tệp, dưới dòng `#include <Arduino.h>` hiện có:

    ```cpp
    #include <DHT.h>
    #include <SPI.h>
    ```

    Điều này nhập các tệp cần thiết để tương tác với cảm biến. Tệp tiêu đề `DHT.h` chứa mã cho cảm biến, và việc thêm tiêu đề `SPI.h` đảm bảo mã cần thiết để giao tiếp với cảm biến được liên kết khi ứng dụng được biên dịch.

1. Trước hàm `setup`, khai báo cảm biến DHT:

    ```cpp
    DHT dht(D0, DHT11);
    ```

    Điều này khai báo một đối tượng của lớp `DHT` để quản lý cảm biến **D**igital **H**umidity và **T**emperature. Cảm biến này được kết nối với cổng `D0`, ổ cắm Grove bên phải trên Wio Terminal. Tham số thứ hai cho biết cảm biến được sử dụng là cảm biến *DHT11* - thư viện bạn đang sử dụng hỗ trợ các biến thể khác của cảm biến này.

1. Trong hàm `setup`, thêm mã để thiết lập kết nối serial:

    ```cpp
    void setup()
    {
        Serial.begin(9600);
    
        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    ```

1. Ở cuối hàm `setup`, sau lệnh `delay` cuối cùng, thêm một lệnh gọi để khởi động cảm biến DHT:

    ```cpp
    dht.begin();
    ```

1. Trong hàm `loop`, thêm mã để gọi cảm biến và in nhiệt độ ra cổng serial:

    ```cpp
    void loop()
    {
        float temp_hum_val[2] = {0};
        dht.readTempAndHumidity(temp_hum_val);
        Serial.print("Temperature: ");
        Serial.print(temp_hum_val[1]);
        Serial.println ("°C");
    
        delay(10000);
    }
    ```

    Mã này khai báo một mảng rỗng gồm 2 số thực và truyền nó vào lệnh gọi `readTempAndHumidity` trên đối tượng `DHT`. Lệnh gọi này sẽ điền mảng với 2 giá trị - độ ẩm được đặt vào phần tử thứ 0 của mảng (hãy nhớ rằng trong C++ mảng bắt đầu từ 0, vì vậy phần tử thứ 0 là phần tử 'đầu tiên' trong mảng), và nhiệt độ được đặt vào phần tử thứ 1.

    Nhiệt độ được đọc từ phần tử thứ 1 của mảng và được in ra cổng serial.

    > 🇺🇸 Nhiệt độ được đọc theo độ C. Đối với người Mỹ, để chuyển đổi sang độ F, chia giá trị độ C đọc được cho 5, sau đó nhân với 9, rồi cộng thêm 32. Ví dụ, một giá trị nhiệt độ đọc được là 20°C sẽ trở thành ((20/5)*9) + 32 = 68°F.

1. Biên dịch và tải mã lên Wio Terminal.

    > ⚠️ Bạn có thể tham khảo [hướng dẫn tạo dự án PlatformIO trong dự án 1, bài học 1 nếu cần](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Sau khi tải lên, bạn có thể theo dõi nhiệt độ bằng cách sử dụng serial monitor:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 24.00°C
    ```

> 💁 Bạn có thể tìm thấy mã này trong thư mục [code-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/wio-terminal).

😀 Chương trình cảm biến nhiệt độ của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.