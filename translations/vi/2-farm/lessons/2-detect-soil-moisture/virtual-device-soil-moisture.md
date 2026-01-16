<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2bf65f162bcebd35fbcba5fd245afac4",
  "translation_date": "2025-08-27T21:55:27+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/virtual-device-soil-moisture.md",
  "language_code": "vi"
}
-->
# Đo độ ẩm đất - Phần cứng IoT ảo

Trong phần này của bài học, bạn sẽ thêm cảm biến độ ẩm đất điện dung vào thiết bị IoT ảo của mình và đọc giá trị từ nó.

## Phần cứng ảo

Thiết bị IoT ảo sẽ sử dụng một cảm biến độ ẩm đất điện dung mô phỏng từ Grove. Điều này giúp bài thực hành này giống như sử dụng Raspberry Pi với cảm biến độ ẩm đất điện dung thực tế từ Grove.

Trong một thiết bị IoT thực tế, cảm biến độ ẩm đất sẽ là một cảm biến điện dung đo độ ẩm đất bằng cách phát hiện điện dung của đất, một thuộc tính thay đổi khi độ ẩm đất thay đổi. Khi độ ẩm đất tăng, điện áp giảm.

Đây là một cảm biến analog, vì vậy nó sử dụng một bộ chuyển đổi ADC 10-bit mô phỏng để báo cáo giá trị từ 1-1,023.

### Thêm cảm biến độ ẩm đất vào CounterFit

Để sử dụng cảm biến độ ẩm đất ảo, bạn cần thêm nó vào ứng dụng CounterFit.

#### Nhiệm vụ - Thêm cảm biến độ ẩm đất vào CounterFit

Thêm cảm biến độ ẩm đất vào ứng dụng CounterFit.

1. Tạo một ứng dụng Python mới trên máy tính của bạn trong một thư mục có tên `soil-moisture-sensor` với một tệp duy nhất có tên `app.py` và một môi trường ảo Python, sau đó thêm các gói pip của CounterFit.

    > ⚠️ Bạn có thể tham khảo [hướng dẫn tạo và thiết lập dự án Python CounterFit trong bài học 1 nếu cần](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Đảm bảo ứng dụng web CounterFit đang chạy.

1. Tạo một cảm biến độ ẩm đất:

    1. Trong hộp *Create sensor* ở bảng *Sensors*, chọn hộp thả xuống *Sensor type* và chọn *Soil Moisture*.

    1. Để *Units* ở chế độ *NoUnits*.

    1. Đảm bảo *Pin* được đặt là *0*.

    1. Chọn nút **Add** để tạo cảm biến *Soil Moisture* trên Pin 0.

    ![Cài đặt cảm biến độ ẩm đất](../../../../../translated_images/vi/counterfit-create-soil-moisture-sensor.35266135a5e0ae68b29a684d7db0d2933a8098b2307d197f7c71577b724603aa.png)

    Cảm biến độ ẩm đất sẽ được tạo và xuất hiện trong danh sách cảm biến.

    ![Cảm biến độ ẩm đất đã được tạo](../../../../../translated_images/vi/counterfit-soil-moisture-sensor.81742b2de0e9de60a3b3b9a2ff8ecc686d428eb6d71820f27a693be26e5aceee.png)

## Lập trình ứng dụng cảm biến độ ẩm đất

Ứng dụng cảm biến độ ẩm đất giờ đây có thể được lập trình bằng cách sử dụng các cảm biến CounterFit.

### Nhiệm vụ - Lập trình ứng dụng cảm biến độ ẩm đất

Lập trình ứng dụng cảm biến độ ẩm đất.

1. Đảm bảo ứng dụng `soil-moisture-sensor` đang mở trong VS Code.

1. Mở tệp `app.py`.

1. Thêm đoạn mã sau vào đầu tệp `app.py` để kết nối ứng dụng với CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Thêm đoạn mã sau vào tệp `app.py` để nhập một số thư viện cần thiết:

    ```python
    import time
    from counterfit_shims_grove.adc import ADC
    ```

    Lệnh `import time` nhập module `time` sẽ được sử dụng sau trong bài tập này.

    Lệnh `from counterfit_shims_grove.adc import ADC` nhập lớp `ADC` để tương tác với bộ chuyển đổi analog sang số ảo có thể kết nối với cảm biến CounterFit.

1. Thêm đoạn mã sau bên dưới để tạo một instance của lớp `ADC`:

    ```python
    adc = ADC()
    ```

1. Thêm một vòng lặp vô hạn để đọc từ ADC trên pin 0 và ghi kết quả ra console. Vòng lặp này sau đó có thể nghỉ 10 giây giữa các lần đọc.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)
    
        time.sleep(10)
    ```

1. Từ ứng dụng CounterFit, thay đổi giá trị của cảm biến độ ẩm đất sẽ được ứng dụng đọc. Bạn có thể làm điều này theo hai cách:

    * Nhập một số vào hộp *Value* cho cảm biến độ ẩm đất, sau đó chọn nút **Set**. Số bạn nhập sẽ là giá trị được cảm biến trả về.

    * Chọn hộp *Random*, sau đó nhập giá trị *Min* và *Max*, sau đó chọn nút **Set**. Mỗi lần cảm biến đọc giá trị, nó sẽ đọc một số ngẫu nhiên giữa *Min* và *Max*.

1. Chạy ứng dụng Python. Bạn sẽ thấy các giá trị đo độ ẩm đất được ghi ra console. Thay đổi *Value* hoặc cài đặt *Random* để thấy giá trị thay đổi.

    ```output
    (.venv) ➜ soil-moisture-sensor $ python app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

> 💁 Bạn có thể tìm thấy đoạn mã này trong thư mục [code/virtual-device](../../../../../2-farm/lessons/2-detect-soil-moisture/code/virtual-device).

😀 Chương trình cảm biến độ ẩm đất của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.