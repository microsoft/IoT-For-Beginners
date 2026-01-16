<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "11f10c6760fb8202cf368422702fdf70",
  "translation_date": "2025-08-27T22:34:04+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-sensor.md",
  "language_code": "vi"
}
-->
# Xây dựng đèn ngủ - Phần cứng IoT ảo

Trong phần này của bài học, bạn sẽ thêm một cảm biến ánh sáng vào thiết bị IoT ảo của mình.

## Phần cứng ảo

Đèn ngủ cần một cảm biến, được tạo trong ứng dụng CounterFit.

Cảm biến này là **cảm biến ánh sáng**. Trong một thiết bị IoT vật lý, nó sẽ là một [photodiode](https://wikipedia.org/wiki/Photodiode) chuyển đổi ánh sáng thành tín hiệu điện. Cảm biến ánh sáng là cảm biến analog, gửi một giá trị số nguyên biểu thị lượng ánh sáng tương đối, không được ánh xạ tới bất kỳ đơn vị đo lường tiêu chuẩn nào như [lux](https://wikipedia.org/wiki/Lux).

### Thêm cảm biến vào CounterFit

Để sử dụng cảm biến ánh sáng ảo, bạn cần thêm nó vào ứng dụng CounterFit.

#### Nhiệm vụ - thêm cảm biến vào CounterFit

Thêm cảm biến ánh sáng vào ứng dụng CounterFit.

1. Đảm bảo ứng dụng web CounterFit đang chạy từ phần trước của bài tập này. Nếu không, hãy khởi động nó.

1. Tạo một cảm biến ánh sáng:

    1. Trong hộp *Create sensor* ở bảng *Sensors*, mở hộp *Sensor type* và chọn *Light*.

    1. Để *Units* ở chế độ *NoUnits*.

    1. Đảm bảo *Pin* được đặt là *0*.

    1. Chọn nút **Add** để tạo cảm biến ánh sáng trên Pin 0.

    ![Cài đặt cảm biến ánh sáng](../../../../../translated_images/vi/counterfit-create-light-sensor.9f36a5e0d4458d8d554d54b34d2c806d56093d6e49fddcda2d20f6fef7f5cce1.png)

    Cảm biến ánh sáng sẽ được tạo và xuất hiện trong danh sách cảm biến.

    ![Cảm biến ánh sáng đã được tạo](../../../../../translated_images/vi/counterfit-light-sensor.5d0f5584df56b90f6b2561910d9cb20dfbd73eeff2177c238d38f4de54aefae1.png)

## Lập trình cảm biến ánh sáng

Thiết bị giờ đây có thể được lập trình để sử dụng cảm biến ánh sáng tích hợp.

### Nhiệm vụ - lập trình cảm biến ánh sáng

Lập trình thiết bị.

1. Mở dự án đèn ngủ trong VS Code mà bạn đã tạo ở phần trước của bài tập này. Tắt và khởi động lại terminal để đảm bảo nó đang chạy bằng môi trường ảo nếu cần.

1. Mở tệp `app.py`.

1. Thêm đoạn mã sau vào đầu tệp `app.py` cùng với các câu lệnh `import` khác để kết nối và nhập một số thư viện cần thiết:

    ```python
    import time
    from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    Câu lệnh `import time` nhập module `time` của Python, sẽ được sử dụng sau trong bài tập này.

    Câu lệnh `from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor` nhập `GroveLightSensor` từ thư viện Python CounterFit Grove shim. Thư viện này chứa mã để tương tác với cảm biến ánh sáng được tạo trong ứng dụng CounterFit.

1. Thêm đoạn mã sau vào cuối tệp để tạo các đối tượng quản lý cảm biến ánh sáng:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    Dòng `light_sensor = GroveLightSensor(0)` tạo một đối tượng của lớp `GroveLightSensor` kết nối với pin **0** - pin CounterFit Grove mà cảm biến ánh sáng được kết nối.

1. Thêm một vòng lặp vô hạn sau đoạn mã trên để lấy giá trị cảm biến ánh sáng và in ra console:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Điều này sẽ đọc mức ánh sáng hiện tại bằng thuộc tính `light` của lớp `GroveLightSensor`. Thuộc tính này đọc giá trị analog từ pin. Giá trị này sau đó được in ra console.

1. Thêm một khoảng nghỉ ngắn một giây ở cuối vòng lặp `while` vì mức ánh sáng không cần được kiểm tra liên tục. Khoảng nghỉ giúp giảm tiêu thụ năng lượng của thiết bị.

    ```python
    time.sleep(1)
    ```

1. Từ Terminal của VS Code, chạy lệnh sau để chạy ứng dụng Python của bạn:

    ```sh
    python3 app.py
    ```

    Các giá trị ánh sáng sẽ được hiển thị trên console. Ban đầu giá trị này sẽ là 0.

1. Từ ứng dụng CounterFit, thay đổi giá trị của cảm biến ánh sáng sẽ được ứng dụng đọc. Bạn có thể làm điều này theo hai cách:

    * Nhập một số vào hộp *Value* của cảm biến ánh sáng, sau đó chọn nút **Set**. Số bạn nhập sẽ là giá trị được cảm biến trả về.

    * Chọn hộp *Random*, và nhập giá trị *Min* và *Max*, sau đó chọn nút **Set**. Mỗi lần cảm biến đọc giá trị, nó sẽ đọc một số ngẫu nhiên giữa *Min* và *Max*.

    Các giá trị bạn đặt sẽ được hiển thị trên console. Thay đổi *Value* hoặc cài đặt *Random* để làm giá trị thay đổi.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

> 💁 Bạn có thể tìm thấy đoạn mã này trong thư mục [code-sensor/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/virtual-device).

😀 Chương trình đèn ngủ của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, nên sử dụng dịch vụ dịch thuật chuyên nghiệp từ con người. Chúng tôi không chịu trách nhiệm về bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.