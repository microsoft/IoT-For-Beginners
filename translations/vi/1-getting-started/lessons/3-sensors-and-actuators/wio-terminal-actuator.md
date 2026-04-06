# Xây dựng đèn ngủ - Wio Terminal

Trong phần này của bài học, bạn sẽ thêm một đèn LED vào Wio Terminal của mình và sử dụng nó để tạo một chiếc đèn ngủ.

## Phần cứng

Đèn ngủ bây giờ cần một bộ truyền động.

Bộ truyền động là một **LED**, một [điốt phát sáng](https://wikipedia.org/wiki/Light-emitting_diode) phát ra ánh sáng khi dòng điện chạy qua nó. Đây là một bộ truyền động kỹ thuật số có 2 trạng thái: bật và tắt. Gửi giá trị 1 sẽ bật LED, và 0 sẽ tắt nó. Đây là một bộ truyền động Grove bên ngoài và cần được kết nối với Wio Terminal.

Logic của đèn ngủ dưới dạng mã giả là:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Kết nối LED

Đèn LED Grove đi kèm dưới dạng một module với nhiều lựa chọn LED, cho phép bạn chọn màu sắc.

#### Nhiệm vụ - kết nối LED

Kết nối đèn LED.

![Một đèn LED Grove](../../../../../translated_images/vi/grove-led.6c853be93f473cf2.webp)

1. Chọn đèn LED yêu thích của bạn và cắm các chân vào hai lỗ trên module LED.

    LED là điốt phát sáng, và điốt là các thiết bị điện tử chỉ cho phép dòng điện chạy theo một chiều. Điều này có nghĩa là LED cần được kết nối đúng chiều, nếu không nó sẽ không hoạt động.

    Một trong các chân của LED là chân dương, chân còn lại là chân âm. LED không hoàn toàn tròn và hơi phẳng hơn ở một bên. Bên hơi phẳng hơn là chân âm. Khi bạn kết nối LED với module, hãy đảm bảo chân ở phía tròn được kết nối với ổ cắm được đánh dấu **+** ở bên ngoài module, và bên phẳng hơn được kết nối với ổ cắm gần giữa module hơn.

1. Module LED có một nút xoay cho phép bạn điều chỉnh độ sáng. Ban đầu, hãy vặn nút này hết cỡ bằng cách xoay ngược chiều kim đồng hồ bằng một tua vít đầu Phillips nhỏ.

1. Cắm một đầu của cáp Grove vào ổ cắm trên module LED. Nó chỉ có thể cắm vào theo một chiều.

1. Khi Wio Terminal đã được ngắt kết nối khỏi máy tính hoặc nguồn điện khác, hãy kết nối đầu còn lại của cáp Grove vào ổ cắm Grove bên phải trên Wio Terminal khi bạn nhìn vào màn hình. Đây là ổ cắm xa nhất so với nút nguồn.

    > 💁 Ổ cắm Grove bên phải có thể được sử dụng với các cảm biến và bộ truyền động tương tự hoặc kỹ thuật số. Ổ cắm bên trái chỉ dành cho các cảm biến và bộ truyền động kỹ thuật số.

![Đèn LED Grove được kết nối với ổ cắm bên phải](../../../../../translated_images/vi/wio-led.265a1897e72d7f21.webp)

## Lập trình đèn ngủ

Bây giờ bạn có thể lập trình đèn ngủ bằng cảm biến ánh sáng tích hợp và đèn LED Grove.

### Nhiệm vụ - lập trình đèn ngủ

Lập trình đèn ngủ.

1. Mở dự án đèn ngủ trong VS Code mà bạn đã tạo ở phần trước của bài tập này.

1. Thêm dòng sau vào cuối hàm `setup`:

    ```cpp
    pinMode(D0, OUTPUT);
    ```

    Dòng này cấu hình chân được sử dụng để giao tiếp với LED qua cổng Grove.

    Chân `D0` là chân kỹ thuật số cho ổ cắm Grove bên phải. Chân này được đặt thành `OUTPUT`, nghĩa là nó kết nối với một bộ truyền động và dữ liệu sẽ được ghi vào chân này.

1. Thêm đoạn mã sau ngay trước `delay` trong hàm vòng lặp:

    ```cpp
    if (light < 300)
    {
        digitalWrite(D0, HIGH);
    }
    else
    {
        digitalWrite(D0, LOW);
    }
    ```

    Đoạn mã này kiểm tra giá trị `light`. Nếu giá trị này nhỏ hơn 300, nó sẽ gửi giá trị `HIGH` đến chân kỹ thuật số `D0`. Giá trị `HIGH` là 1, bật LED. Nếu ánh sáng lớn hơn hoặc bằng 300, giá trị `LOW` là 0 sẽ được gửi đến chân, tắt LED.

    > 💁 Khi gửi các giá trị kỹ thuật số đến bộ truyền động, giá trị LOW là 0v, và giá trị HIGH là điện áp tối đa cho thiết bị. Đối với Wio Terminal, điện áp HIGH là 3.3V.

1. Kết nối lại Wio Terminal với máy tính của bạn và tải lên mã mới như bạn đã làm trước đó.

1. Kết nối Serial Monitor. Các giá trị ánh sáng sẽ được xuất ra terminal.

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

1. Che và mở cảm biến ánh sáng. Lưu ý rằng đèn LED sẽ sáng nếu mức ánh sáng là 300 hoặc thấp hơn, và tắt khi mức ánh sáng lớn hơn 300.

![Đèn LED kết nối với WIO bật và tắt khi mức ánh sáng thay đổi](../../../../../images/wio-running-assignment-1-1.gif)

> 💁 Bạn có thể tìm thấy mã này trong thư mục [code-actuator/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/wio-terminal).

😀 Chương trình đèn ngủ của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, nên sử dụng dịch vụ dịch thuật chuyên nghiệp từ con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.