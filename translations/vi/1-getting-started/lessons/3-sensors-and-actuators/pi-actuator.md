# Xây dựng đèn ngủ - Raspberry Pi

Trong phần này của bài học, bạn sẽ thêm một đèn LED vào Raspberry Pi và sử dụng nó để tạo một chiếc đèn ngủ.

## Phần cứng

Chiếc đèn ngủ bây giờ cần một bộ truyền động.

Bộ truyền động là một **đèn LED**, một [đi-ốt phát sáng](https://wikipedia.org/wiki/Light-emitting_diode) phát ra ánh sáng khi dòng điện chạy qua nó. Đây là một bộ truyền động kỹ thuật số có 2 trạng thái: bật và tắt. Gửi giá trị 1 sẽ bật đèn LED, và giá trị 0 sẽ tắt nó. Đèn LED là một bộ truyền động Grove bên ngoài và cần được kết nối với mũ Grove Base trên Raspberry Pi.

Logic của đèn ngủ dưới dạng mã giả là:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Kết nối đèn LED

Đèn LED Grove đi kèm dưới dạng một module với nhiều lựa chọn màu sắc, cho phép bạn chọn màu yêu thích.

#### Nhiệm vụ - kết nối đèn LED

Kết nối đèn LED.

![Một đèn LED Grove](../../../../../translated_images/vi/grove-led.6c853be93f473cf2.webp)

1. Chọn đèn LED yêu thích của bạn và cắm các chân vào hai lỗ trên module đèn LED.

    Đèn LED là đi-ốt phát sáng, và đi-ốt là các thiết bị điện tử chỉ cho phép dòng điện chạy theo một chiều. Điều này có nghĩa là đèn LED cần được kết nối đúng chiều, nếu không nó sẽ không hoạt động.

    Một trong các chân của đèn LED là chân dương, chân còn lại là chân âm. Đèn LED không hoàn toàn tròn và có một mặt hơi phẳng. Mặt hơi phẳng này là chân âm. Khi bạn kết nối đèn LED với module, hãy đảm bảo chân ở phía tròn được kết nối với ổ cắm được đánh dấu **+** ở bên ngoài module, và mặt phẳng được kết nối với ổ cắm gần giữa module hơn.

1. Module đèn LED có một nút xoay cho phép bạn điều chỉnh độ sáng. Ban đầu, hãy xoay nút này hết cỡ theo chiều ngược kim đồng hồ bằng cách sử dụng một tua vít đầu Phillips nhỏ.

1. Cắm một đầu của cáp Grove vào ổ cắm trên module đèn LED. Cáp chỉ có thể cắm vào theo một chiều.

1. Khi Raspberry Pi đã tắt nguồn, kết nối đầu còn lại của cáp Grove vào ổ cắm kỹ thuật số được đánh dấu **D5** trên mũ Grove Base gắn vào Pi. Ổ cắm này là ổ thứ hai từ bên trái, trên hàng ổ cắm cạnh các chân GPIO.

![Đèn LED Grove được kết nối với ổ D5](../../../../../translated_images/vi/pi-led.97f1d474981dc35d.webp)

## Lập trình đèn ngủ

Bây giờ bạn có thể lập trình đèn ngủ bằng cảm biến ánh sáng Grove và đèn LED Grove.

### Nhiệm vụ - lập trình đèn ngủ

Lập trình đèn ngủ.

1. Bật nguồn cho Pi và chờ nó khởi động.

1. Mở dự án đèn ngủ trong VS Code mà bạn đã tạo ở phần trước của bài tập này, chạy trực tiếp trên Pi hoặc kết nối bằng tiện ích mở rộng Remote SSH.

1. Thêm đoạn mã sau vào tệp `app.py` để nhập thư viện cần thiết. Đoạn mã này nên được thêm vào đầu tệp, bên dưới các dòng `import` khác.

    ```python
    from grove.grove_led import GroveLed
    ```

    Dòng lệnh `from grove.grove_led import GroveLed` nhập `GroveLed` từ thư viện Python Grove. Thư viện này chứa mã để tương tác với đèn LED Grove.

1. Thêm đoạn mã sau sau khai báo `light_sensor` để tạo một thể hiện của lớp quản lý đèn LED:

    ```python
    led = GroveLed(5)
    ```

    Dòng lệnh `led = GroveLed(5)` tạo một thể hiện của lớp `GroveLed` kết nối với chân **D5** - chân Grove kỹ thuật số mà đèn LED được kết nối.

    > 💁 Tất cả các ổ cắm đều có số chân duy nhất. Các chân 0, 2, 4 và 6 là chân analog, các chân 5, 16, 18, 22, 24 và 26 là chân kỹ thuật số.

1. Thêm một kiểm tra bên trong vòng lặp `while`, trước dòng `time.sleep` để kiểm tra mức ánh sáng và bật hoặc tắt đèn LED:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Đoạn mã này kiểm tra giá trị `light`. Nếu giá trị này nhỏ hơn 300, nó gọi phương thức `on` của lớp `GroveLed`, gửi giá trị kỹ thuật số 1 đến đèn LED, bật nó lên. Nếu giá trị ánh sáng lớn hơn hoặc bằng 300, nó gọi phương thức `off`, gửi giá trị kỹ thuật số 0 đến đèn LED, tắt nó đi.

    > 💁 Đoạn mã này nên được thụt lề cùng mức với dòng `print('Light level:', light)` để nằm bên trong vòng lặp while!

    > 💁 Khi gửi các giá trị kỹ thuật số đến bộ truyền động, giá trị 0 tương ứng với 0V, và giá trị 1 tương ứng với điện áp tối đa của thiết bị. Đối với Raspberry Pi với các cảm biến và bộ truyền động Grove, điện áp 1 là 3.3V.

1. Từ Terminal của VS Code, chạy lệnh sau để chạy ứng dụng Python của bạn:

    ```sh
    python3 app.py
    ```

    Các giá trị ánh sáng sẽ được xuất ra console.

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

1. Che và mở cảm biến ánh sáng. Chú ý cách đèn LED sẽ sáng lên nếu mức ánh sáng là 300 hoặc thấp hơn, và tắt khi mức ánh sáng lớn hơn 300.

    > 💁 Nếu đèn LED không sáng, hãy đảm bảo nó được kết nối đúng chiều và nút xoay được đặt ở mức tối đa.

![Đèn LED kết nối với Pi bật và tắt khi mức ánh sáng thay đổi](../../../../../images/pi-running-assignment-1-1.gif)

> 💁 Bạn có thể tìm thấy đoạn mã này trong thư mục [code-actuator/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/pi).

😀 Chương trình đèn ngủ của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.