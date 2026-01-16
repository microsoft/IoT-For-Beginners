<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "da6ae0a795cf06be33d23ca5b8493fc8",
  "translation_date": "2025-08-27T23:39:09+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-sensor.md",
  "language_code": "vi"
}
-->
# Đọc dữ liệu GPS - Wio Terminal

Trong phần này của bài học, bạn sẽ thêm một cảm biến GPS vào Wio Terminal và đọc các giá trị từ nó.

## Phần cứng

Wio Terminal cần một cảm biến GPS.

Cảm biến bạn sẽ sử dụng là [Grove GPS Air530 sensor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Cảm biến này có thể kết nối với nhiều hệ thống GPS để định vị nhanh và chính xác. Cảm biến bao gồm 2 phần - phần lõi điện tử của cảm biến và một ăng-ten ngoài được kết nối bằng một dây mỏng để thu sóng radio từ các vệ tinh.

Đây là một cảm biến UART, vì vậy nó gửi dữ liệu GPS qua UART.

### Kết nối cảm biến GPS

Cảm biến Grove GPS có thể được kết nối với Wio Terminal.

#### Nhiệm vụ - kết nối cảm biến GPS

Kết nối cảm biến GPS.

![Một cảm biến Grove GPS](../../../../../translated_images/vi/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.png)

1. Cắm một đầu của cáp Grove vào ổ cắm trên cảm biến GPS. Cáp chỉ có thể cắm theo một chiều.

1. Khi Wio Terminal chưa được kết nối với máy tính hoặc nguồn điện khác, cắm đầu còn lại của cáp Grove vào ổ cắm Grove bên trái trên Wio Terminal khi bạn nhìn vào màn hình. Đây là ổ cắm gần nút nguồn nhất.

    ![Cảm biến Grove GPS được kết nối với ổ cắm bên trái](../../../../../translated_images/vi/wio-gps-sensor.19fd52b81ce58095.webp)

1. Đặt cảm biến GPS sao cho ăng-ten gắn kèm có thể nhìn thấy bầu trời - lý tưởng nhất là gần cửa sổ mở hoặc ngoài trời. Tín hiệu sẽ rõ ràng hơn khi không có vật cản giữa ăng-ten và bầu trời.

1. Bây giờ bạn có thể kết nối Wio Terminal với máy tính của mình.

1. Cảm biến GPS có 2 đèn LED - một đèn LED màu xanh dương nhấp nháy khi dữ liệu được truyền, và một đèn LED màu xanh lá nhấp nháy mỗi giây khi nhận dữ liệu từ vệ tinh. Đảm bảo đèn LED màu xanh dương nhấp nháy khi bạn bật nguồn Wio Terminal. Sau vài phút, đèn LED màu xanh lá sẽ nhấp nháy - nếu không, bạn có thể cần điều chỉnh lại vị trí của ăng-ten.

## Lập trình cảm biến GPS

Bây giờ Wio Terminal có thể được lập trình để sử dụng cảm biến GPS đã kết nối.

### Nhiệm vụ - lập trình cảm biến GPS

Lập trình thiết bị.

1. Tạo một dự án Wio Terminal mới bằng PlatformIO. Đặt tên dự án là `gps-sensor`. Thêm mã vào hàm `setup` để cấu hình cổng nối tiếp.

1. Thêm chỉ thị include sau vào đầu tệp `main.cpp`. Điều này bao gồm một tệp tiêu đề với các hàm để cấu hình cổng Grove bên trái cho UART.

    ```cpp
    #include <wiring_private.h>
    ```

1. Bên dưới đó, thêm dòng mã sau để khai báo một kết nối cổng nối tiếp với cổng UART:

    ```cpp
    static Uart Serial3(&sercom3, PIN_WIRE_SCL, PIN_WIRE_SDA, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    ```

1. Bạn cần thêm một số mã để chuyển hướng một số trình xử lý tín hiệu nội bộ đến cổng nối tiếp này. Thêm mã sau bên dưới khai báo `Serial3`:

    ```cpp
    void SERCOM3_0_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_1_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_2_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_3_Handler()
    {
        Serial3.IrqHandler();
    }
    ```

1. Trong hàm `setup`, bên dưới nơi cổng `Serial` được cấu hình, cấu hình cổng nối tiếp UART với mã sau:

    ```cpp
    Serial3.begin(9600);

    while (!Serial3)
        ; // Wait for Serial3 to be ready

    delay(1000);
    ```

1. Bên dưới mã này trong hàm `setup`, thêm mã sau để kết nối chân Grove với cổng nối tiếp:

    ```cpp
    pinPeripheral(PIN_WIRE_SCL, PIO_SERCOM_ALT);
    ```

1. Thêm hàm sau trước hàm `loop` để gửi dữ liệu GPS đến màn hình nối tiếp:

    ```cpp
    void printGPSData()
    {
        Serial.println(Serial3.readStringUntil('\n'));
    }
    ```

1. Trong hàm `loop`, thêm mã sau để đọc từ cổng nối tiếp UART và in đầu ra lên màn hình nối tiếp:

    ```cpp
    while (Serial3.available() > 0)
    {
        printGPSData();
    }
    
    delay(1000);
    ```

    Mã này đọc từ cổng nối tiếp UART. Hàm `readStringUntil` đọc cho đến khi gặp một ký tự kết thúc, trong trường hợp này là một dòng mới. Điều này sẽ đọc toàn bộ câu NMEA (các câu NMEA được kết thúc bằng một ký tự dòng mới). Trong khi dữ liệu có thể được đọc từ cổng nối tiếp UART, nó sẽ được đọc và gửi đến màn hình nối tiếp thông qua hàm `printGPSData`. Khi không còn dữ liệu nào có thể đọc được, vòng lặp `loop` sẽ tạm dừng trong 1 giây (1.000ms).

1. Biên dịch và tải mã lên Wio Terminal.

1. Sau khi tải lên, bạn có thể theo dõi dữ liệu GPS bằng màn hình nối tiếp.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

> 💁 Bạn có thể tìm thấy mã này trong thư mục [code-gps/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps/wio-terminal).

😀 Chương trình cảm biến GPS của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.