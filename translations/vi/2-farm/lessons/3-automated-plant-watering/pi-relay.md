<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "66b81165e60f8f169bd52a401b6a0f8b",
  "translation_date": "2025-08-27T21:37:51+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/pi-relay.md",
  "language_code": "vi"
}
-->
# Điều khiển relay - Raspberry Pi

Trong phần này của bài học, bạn sẽ thêm một relay vào Raspberry Pi bên cạnh cảm biến độ ẩm đất và điều khiển nó dựa trên mức độ ẩm đất.

## Phần cứng

Raspberry Pi cần một relay.

Relay bạn sẽ sử dụng là [Grove relay](https://www.seeedstudio.com/Grove-Relay.html), một relay thường mở (nghĩa là mạch đầu ra sẽ mở hoặc ngắt kết nối khi không có tín hiệu gửi đến relay) có thể xử lý mạch đầu ra lên đến 250V và 10A.

Đây là một bộ truyền động kỹ thuật số, vì vậy nó được kết nối với một chân kỹ thuật số trên Grove Base Hat.

### Kết nối relay

Relay Grove có thể được kết nối với Raspberry Pi.

#### Nhiệm vụ

Kết nối relay.

![Một relay Grove](../../../../../translated_images/vi/grove-relay.d426958ca210fbd0fb7983d7edc069d46c73a8b0a099d94797bd756f7b6bb6be.png)

1. Cắm một đầu của cáp Grove vào ổ cắm trên relay. Cáp chỉ có thể cắm theo một chiều.

1. Khi Raspberry Pi đã tắt nguồn, kết nối đầu còn lại của cáp Grove vào ổ cắm kỹ thuật số được đánh dấu **D5** trên Grove Base Hat gắn vào Pi. Ổ cắm này là ổ thứ hai từ bên trái, nằm trên hàng ổ cắm cạnh các chân GPIO. Để cảm biến độ ẩm đất được kết nối với ổ **A0**.

![Relay Grove được kết nối với ổ D5, và cảm biến độ ẩm đất được kết nối với ổ A0](../../../../../translated_images/vi/pi-relay-and-soil-moisture-sensor.02f3198975b8c53e69ec716cd2719ce117700bd1fc933eaf93476c103c57939b.png)

1. Cắm cảm biến độ ẩm đất vào đất, nếu nó chưa được cắm từ bài học trước.

## Lập trình relay

Raspberry Pi bây giờ có thể được lập trình để sử dụng relay đã gắn.

### Nhiệm vụ

Lập trình thiết bị.

1. Bật nguồn Pi và chờ nó khởi động.

1. Mở dự án `soil-moisture-sensor` từ bài học trước trong VS Code nếu nó chưa được mở. Bạn sẽ thêm vào dự án này.

1. Thêm đoạn mã sau vào tệp `app.py` bên dưới các phần nhập hiện có:

    ```python
    from grove.grove_relay import GroveRelay
    ```

    Dòng lệnh này nhập `GroveRelay` từ thư viện Python Grove để tương tác với relay Grove.

1. Thêm đoạn mã sau bên dưới khai báo lớp `ADC` để tạo một đối tượng `GroveRelay`:

    ```python
    relay = GroveRelay(5)
    ```

    Điều này tạo một relay sử dụng chân **D5**, chân kỹ thuật số mà bạn đã kết nối relay.

1. Để kiểm tra relay hoạt động, thêm đoạn mã sau vào vòng lặp `while True:`:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    Đoạn mã này bật relay, chờ 0.5 giây, sau đó tắt relay.

1. Chạy ứng dụng Python. Relay sẽ bật và tắt mỗi 10 giây, với độ trễ nửa giây giữa việc bật và tắt. Bạn sẽ nghe thấy relay kêu "click" khi bật và "click" khi tắt. Đèn LED trên bảng Grove sẽ sáng khi relay bật và tắt khi relay tắt.

    ![Relay bật và tắt](../../../../../images/relay-turn-on-off.gif)

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

    Đoạn mã này kiểm tra mức độ ẩm đất từ cảm biến độ ẩm đất. Nếu giá trị lớn hơn 450, nó sẽ bật relay, và tắt relay khi giá trị nhỏ hơn 450.

    > 💁 Nhớ rằng cảm biến độ ẩm đất điện dung đọc giá trị càng thấp thì độ ẩm trong đất càng cao và ngược lại.

1. Chạy ứng dụng Python. Bạn sẽ thấy relay bật hoặc tắt tùy thuộc vào mức độ ẩm đất. Thử nghiệm với đất khô, sau đó thêm nước.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Bạn có thể tìm đoạn mã này trong thư mục [code-relay/pi](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/pi).

😀 Chương trình điều khiển relay từ cảm biến độ ẩm đất của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.