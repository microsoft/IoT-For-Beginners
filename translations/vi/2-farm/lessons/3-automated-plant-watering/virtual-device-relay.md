<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f8f541ee945545017a51aaf309aa37c3",
  "translation_date": "2025-08-27T21:38:49+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/virtual-device-relay.md",
  "language_code": "vi"
}
-->
# Điều khiển relay - Phần cứng IoT ảo

Trong phần này của bài học, bạn sẽ thêm một relay vào thiết bị IoT ảo của mình bên cạnh cảm biến độ ẩm đất, và điều khiển nó dựa trên mức độ ẩm đất.

## Phần cứng ảo

Thiết bị IoT ảo sẽ sử dụng một relay Grove mô phỏng. Điều này giúp bài thực hành này tương tự như việc sử dụng Raspberry Pi với relay Grove vật lý.

Trong một thiết bị IoT vật lý, relay sẽ là loại relay thường mở (nghĩa là mạch đầu ra sẽ mở hoặc ngắt kết nối khi không có tín hiệu gửi đến relay). Một relay như vậy có thể xử lý mạch đầu ra lên đến 250V và 10A.

### Thêm relay vào CounterFit

Để sử dụng relay ảo, bạn cần thêm nó vào ứng dụng CounterFit.

#### Nhiệm vụ

Thêm relay vào ứng dụng CounterFit.

1. Mở dự án `soil-moisture-sensor` từ bài học trước trong VS Code nếu chưa mở. Bạn sẽ thêm vào dự án này.

1. Đảm bảo ứng dụng web CounterFit đang chạy.

1. Tạo một relay:

    1. Trong hộp *Create actuator* ở bảng *Actuators*, chọn hộp *Actuator type* và chọn *Relay*.

    1. Đặt *Pin* là *5*.

    1. Nhấn nút **Add** để tạo relay trên Pin 5.

    ![Cài đặt relay](../../../../../translated_images/vi/counterfit-create-relay.fa7c40fd0f2f6afc33b35ea94fcb235085be4861e14e3fe6b9b7bcfc82d1c888.png)

    Relay sẽ được tạo và xuất hiện trong danh sách actuators.

    ![Relay đã được tạo](../../../../../translated_images/vi/counterfit-relay.bbf74c1dbdc8b9acd983367fcbd06703a402aefef6af54ddb28e11307ba8a12c.png)

## Lập trình relay

Ứng dụng cảm biến độ ẩm đất giờ đây có thể được lập trình để sử dụng relay ảo.

### Nhiệm vụ

Lập trình thiết bị ảo.

1. Mở dự án `soil-moisture-sensor` từ bài học trước trong VS Code nếu chưa mở. Bạn sẽ thêm vào dự án này.

1. Thêm đoạn mã sau vào tệp `app.py` bên dưới các dòng import hiện có:

    ```python
    from counterfit_shims_grove.grove_relay import GroveRelay
    ```

    Dòng lệnh này import `GroveRelay` từ thư viện Grove Python shim để tương tác với relay Grove ảo.

1. Thêm đoạn mã sau bên dưới khai báo lớp `ADC` để tạo một instance `GroveRelay`:

    ```python
    relay = GroveRelay(5)
    ```

    Điều này tạo một relay sử dụng pin **5**, pin mà bạn đã kết nối relay.

1. Để kiểm tra relay hoạt động, thêm đoạn mã sau vào vòng lặp `while True:`:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    Đoạn mã này bật relay, chờ 0.5 giây, sau đó tắt relay.

1. Chạy ứng dụng Python. Relay sẽ bật và tắt mỗi 10 giây, với độ trễ nửa giây giữa việc bật và tắt. Bạn sẽ thấy relay ảo trong ứng dụng CounterFit đóng và mở khi relay được bật và tắt.

    ![Relay ảo bật và tắt](../../../../../images/virtual-relay-turn-on-off.gif)

## Điều khiển relay từ độ ẩm đất

Bây giờ relay đã hoạt động, nó có thể được điều khiển dựa trên các giá trị đọc từ cảm biến độ ẩm đất.

### Nhiệm vụ

Điều khiển relay.

1. Xóa 3 dòng mã mà bạn đã thêm để kiểm tra relay. Thay thế chúng bằng đoạn mã sau:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    Đoạn mã này kiểm tra mức độ ẩm đất từ cảm biến độ ẩm đất. Nếu giá trị lớn hơn 450, nó sẽ bật relay, và tắt relay nếu giá trị nhỏ hơn 450.

    > 💁 Nhớ rằng cảm biến độ ẩm đất điện dung đọc giá trị càng thấp thì độ ẩm trong đất càng cao và ngược lại.

1. Chạy ứng dụng Python. Bạn sẽ thấy relay bật hoặc tắt tùy thuộc vào mức độ ẩm đất. Thay đổi *Value* hoặc cài đặt *Random* cho cảm biến độ ẩm đất để thấy giá trị thay đổi.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Bạn có thể tìm đoạn mã này trong thư mục [code-relay/virtual-device](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/virtual-device).

😀 Chương trình cảm biến độ ẩm đất ảo điều khiển relay của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.