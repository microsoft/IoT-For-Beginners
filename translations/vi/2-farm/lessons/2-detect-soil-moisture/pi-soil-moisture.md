# Đo độ ẩm đất - Raspberry Pi

Trong phần này của bài học, bạn sẽ thêm cảm biến độ ẩm đất điện dung vào Raspberry Pi và đọc các giá trị từ nó.

## Phần cứng

Raspberry Pi cần một cảm biến độ ẩm đất điện dung.

Cảm biến bạn sẽ sử dụng là [Cảm biến độ ẩm đất điện dung](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), đo độ ẩm đất bằng cách phát hiện điện dung của đất, một thuộc tính thay đổi khi độ ẩm đất thay đổi. Khi độ ẩm đất tăng, điện áp giảm.

Đây là một cảm biến analog, vì vậy nó sử dụng một chân analog và bộ chuyển đổi ADC 10-bit trong Grove Base Hat trên Pi để chuyển đổi điện áp thành tín hiệu số từ 1-1.023. Sau đó, tín hiệu này được gửi qua I2C thông qua các chân GPIO trên Pi.

### Kết nối cảm biến độ ẩm đất

Cảm biến độ ẩm đất Grove có thể được kết nối với Raspberry Pi.

#### Nhiệm vụ - kết nối cảm biến độ ẩm đất

Kết nối cảm biến độ ẩm đất.

![Một cảm biến độ ẩm đất Grove](../../../../../translated_images/vi/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78b.webp)

1. Cắm một đầu của cáp Grove vào ổ cắm trên cảm biến độ ẩm đất. Nó chỉ có thể cắm theo một chiều.

1. Khi Raspberry Pi đã tắt nguồn, kết nối đầu còn lại của cáp Grove vào ổ cắm analog được đánh dấu **A0** trên Grove Base Hat gắn vào Pi. Ổ cắm này là ổ thứ hai từ bên phải, trên hàng ổ cắm cạnh các chân GPIO.

![Cảm biến độ ẩm đất Grove được kết nối với ổ A0](../../../../../translated_images/vi/pi-soil-moisture-sensor.fdd7eb2393792cf6.webp)

1. Cắm cảm biến độ ẩm đất vào đất. Nó có một 'đường giới hạn cao nhất' - một đường trắng ngang qua cảm biến. Cắm cảm biến đến nhưng không vượt qua đường này.

![Cảm biến độ ẩm đất Grove trong đất](../../../../../translated_images/vi/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

## Lập trình cảm biến độ ẩm đất

Raspberry Pi giờ đây có thể được lập trình để sử dụng cảm biến độ ẩm đất đã gắn.

### Nhiệm vụ - lập trình cảm biến độ ẩm đất

Lập trình thiết bị.

1. Bật nguồn Pi và chờ nó khởi động.

1. Mở VS Code, hoặc trực tiếp trên Pi, hoặc kết nối qua tiện ích mở rộng Remote SSH.

    > ⚠️ Bạn có thể tham khảo [hướng dẫn thiết lập và mở VS Code trong nightlight - bài học 1 nếu cần](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Từ terminal, tạo một thư mục mới trong thư mục chính của người dùng `pi` có tên là `soil-moisture-sensor`. Tạo một tệp trong thư mục này có tên là `app.py`.

1. Mở thư mục này trong VS Code.

1. Thêm đoạn mã sau vào tệp `app.py` để nhập một số thư viện cần thiết:

    ```python
    import time
    from grove.adc import ADC
    ```

    Lệnh `import time` nhập mô-đun `time` sẽ được sử dụng sau trong bài tập này.

    Lệnh `from grove.adc import ADC` nhập `ADC` từ thư viện Python của Grove. Thư viện này có mã để tương tác với bộ chuyển đổi analog sang số trên Pi Base Hat và đọc điện áp từ các cảm biến analog.

1. Thêm đoạn mã sau bên dưới để tạo một thể hiện của lớp `ADC`:

    ```python
    adc = ADC()
    ```

1. Thêm một vòng lặp vô hạn để đọc từ ADC trên chân A0 và ghi kết quả ra console. Vòng lặp này sau đó có thể tạm dừng 10 giây giữa các lần đọc.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)

        time.sleep(10)
    ```

1. Chạy ứng dụng Python. Bạn sẽ thấy các giá trị đo độ ẩm đất được ghi ra console. Thêm một ít nước vào đất hoặc rút cảm biến ra khỏi đất và quan sát giá trị thay đổi.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

    Trong ví dụ đầu ra trên, bạn có thể thấy điện áp giảm khi nước được thêm vào.

> 💁 Bạn có thể tìm thấy mã này trong thư mục [code/pi](../../../../../2-farm/lessons/2-detect-soil-moisture/code/pi).

😀 Chương trình cảm biến độ ẩm đất của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp từ con người. Chúng tôi không chịu trách nhiệm về bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.