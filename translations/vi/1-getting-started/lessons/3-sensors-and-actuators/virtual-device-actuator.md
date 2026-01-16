<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c640f93263fd9adbfda920739e09feb",
  "translation_date": "2025-08-27T22:33:04+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-actuator.md",
  "language_code": "vi"
}
-->
# Xây dựng đèn ngủ - Phần cứng IoT ảo

Trong phần này của bài học, bạn sẽ thêm một đèn LED vào thiết bị IoT ảo của mình và sử dụng nó để tạo một đèn ngủ.

## Phần cứng ảo

Đèn ngủ cần một bộ truyền động, được tạo trong ứng dụng CounterFit.

Bộ truyền động là một **đèn LED**. Trong một thiết bị IoT vật lý, nó sẽ là một [đi-ốt phát sáng](https://wikipedia.org/wiki/Light-emitting_diode) phát ra ánh sáng khi dòng điện chạy qua. Đây là một bộ truyền động kỹ thuật số có 2 trạng thái: bật và tắt. Gửi giá trị 1 sẽ bật đèn LED, và 0 sẽ tắt nó.

Logic của đèn ngủ dưới dạng mã giả là:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Thêm bộ truyền động vào CounterFit

Để sử dụng đèn LED ảo, bạn cần thêm nó vào ứng dụng CounterFit.

#### Nhiệm vụ - thêm bộ truyền động vào CounterFit

Thêm đèn LED vào ứng dụng CounterFit.

1. Đảm bảo ứng dụng web CounterFit đang chạy từ phần trước của bài tập này. Nếu không, hãy khởi động lại và thêm lại cảm biến ánh sáng.

1. Tạo một đèn LED:

    1. Trong hộp *Create actuator* trong khung *Actuator*, thả xuống hộp *Actuator type* và chọn *LED*.

    1. Đặt *Pin* thành *5*.

    1. Chọn nút **Add** để tạo đèn LED trên Pin 5.

    ![Cài đặt đèn LED](../../../../../translated_images/vi/counterfit-create-led.ba9db1c9b8c622a635d6dfae5cdc4e70c2b250635bd4f0601c6cf0bd22b7ba46.png)

    Đèn LED sẽ được tạo và xuất hiện trong danh sách các bộ truyền động.

    ![Đèn LED đã được tạo](../../../../../translated_images/vi/counterfit-led.c0ab02de6d256ad84d9bad4d67a7faa709f0ea83e410cfe9b5561ef0cef30b1c.png)

    Sau khi đèn LED được tạo, bạn có thể thay đổi màu sắc bằng cách sử dụng bộ chọn *Color*. Chọn nút **Set** để thay đổi màu sau khi bạn đã chọn.

### Lập trình đèn ngủ

Bây giờ bạn có thể lập trình đèn ngủ bằng cách sử dụng cảm biến ánh sáng và đèn LED trong CounterFit.

#### Nhiệm vụ - lập trình đèn ngủ

Lập trình đèn ngủ.

1. Mở dự án đèn ngủ trong VS Code mà bạn đã tạo ở phần trước của bài tập này. Tắt và tạo lại terminal để đảm bảo nó đang chạy bằng môi trường ảo nếu cần.

1. Mở tệp `app.py`.

1. Thêm đoạn mã sau vào tệp `app.py` để nhập một thư viện cần thiết. Đoạn mã này nên được thêm vào đầu tệp, bên dưới các dòng `import` khác.

    ```python
    from counterfit_shims_grove.grove_led import GroveLed
    ```

    Câu lệnh `from counterfit_shims_grove.grove_led import GroveLed` nhập `GroveLed` từ thư viện Python CounterFit Grove shim. Thư viện này chứa mã để tương tác với đèn LED được tạo trong ứng dụng CounterFit.

1. Thêm đoạn mã sau sau khai báo `light_sensor` để tạo một thể hiện của lớp quản lý đèn LED:

    ```python
    led = GroveLed(5)
    ```

    Dòng `led = GroveLed(5)` tạo một thể hiện của lớp `GroveLed` kết nối với pin **5** - pin CounterFit Grove mà đèn LED được kết nối.

1. Thêm một kiểm tra bên trong vòng lặp `while`, trước `time.sleep` để kiểm tra mức ánh sáng và bật hoặc tắt đèn LED:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Đoạn mã này kiểm tra giá trị `light`. Nếu giá trị này nhỏ hơn 300, nó gọi phương thức `on` của lớp `GroveLed`, gửi giá trị kỹ thuật số 1 đến đèn LED, bật nó lên. Nếu giá trị ánh sáng lớn hơn hoặc bằng 300, nó gọi phương thức `off`, gửi giá trị kỹ thuật số 0 đến đèn LED, tắt nó đi.

    > 💁 Đoạn mã này nên được thụt lề cùng mức với dòng `print('Light level:', light)` để nằm bên trong vòng lặp while!

1. Từ Terminal của VS Code, chạy lệnh sau để chạy ứng dụng Python của bạn:

    ```sh
    python3 app.py
    ```

    Các giá trị ánh sáng sẽ được hiển thị trên console.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

1. Thay đổi cài đặt *Value* hoặc *Random* để điều chỉnh mức ánh sáng lên trên và xuống dưới 300. Đèn LED sẽ bật và tắt.

![Đèn LED trong ứng dụng CounterFit bật và tắt khi mức ánh sáng thay đổi](../../../../../images/virtual-device-running-assignment-1-1.gif)

> 💁 Bạn có thể tìm thấy mã này trong thư mục [code-actuator/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/virtual-device).

😀 Chương trình đèn ngủ của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, nên sử dụng dịch vụ dịch thuật chuyên nghiệp từ con người. Chúng tôi không chịu trách nhiệm về bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.