<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7678f7c67b97ee52d5727496dcd7d346",
  "translation_date": "2025-08-27T21:30:35+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/pi-temp.md",
  "language_code": "vi"
}
-->
# Đo nhiệt độ - Raspberry Pi

Trong phần này của bài học, bạn sẽ thêm một cảm biến nhiệt độ vào Raspberry Pi của mình.

## Phần cứng

Cảm biến bạn sẽ sử dụng là [cảm biến độ ẩm và nhiệt độ DHT11](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), kết hợp 2 cảm biến trong một gói. Đây là loại cảm biến khá phổ biến, với nhiều cảm biến thương mại kết hợp nhiệt độ, độ ẩm và đôi khi cả áp suất khí quyển. Thành phần cảm biến nhiệt độ là một nhiệt điện trở hệ số nhiệt độ âm (NTC), một loại nhiệt điện trở mà điện trở giảm khi nhiệt độ tăng.

Đây là một cảm biến kỹ thuật số, vì vậy nó có một bộ chuyển đổi ADC tích hợp để tạo tín hiệu kỹ thuật số chứa dữ liệu nhiệt độ và độ ẩm mà vi điều khiển có thể đọc.

### Kết nối cảm biến nhiệt độ

Cảm biến nhiệt độ Grove có thể được kết nối với Raspberry Pi.

#### Nhiệm vụ

Kết nối cảm biến nhiệt độ

![Một cảm biến nhiệt độ Grove](../../../../../translated_images/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.vi.png)

1. Cắm một đầu của cáp Grove vào ổ cắm trên cảm biến độ ẩm và nhiệt độ. Cáp chỉ có thể cắm theo một chiều.

1. Khi Raspberry Pi đã tắt nguồn, kết nối đầu còn lại của cáp Grove vào ổ cắm kỹ thuật số được đánh dấu **D5** trên Grove Base hat gắn vào Pi. Ổ cắm này là ổ thứ hai từ bên trái, nằm trên hàng ổ cắm cạnh các chân GPIO.

![Cảm biến nhiệt độ Grove được kết nối với ổ cắm A0](../../../../../translated_images/pi-temperature-sensor.3ff82fff672c8e56.vi.png)

## Lập trình cảm biến nhiệt độ

Thiết bị giờ đây có thể được lập trình để sử dụng cảm biến nhiệt độ đã gắn.

### Nhiệm vụ

Lập trình thiết bị.

1. Bật nguồn Pi và chờ nó khởi động.

1. Mở VS Code, trực tiếp trên Pi hoặc kết nối qua tiện ích mở rộng Remote SSH.

    > ⚠️ Bạn có thể tham khảo [hướng dẫn thiết lập và mở VS Code trong bài học 1 nếu cần](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Từ terminal, tạo một thư mục mới trong thư mục home của người dùng `pi` có tên là `temperature-sensor`. Tạo một tệp trong thư mục này có tên là `app.py`:

    ```sh
    mkdir temperature-sensor
    cd temperature-sensor
    touch app.py
    ```

1. Mở thư mục này trong VS Code.

1. Để sử dụng cảm biến nhiệt độ và độ ẩm, cần cài đặt thêm một gói Pip. Từ Terminal trong VS Code, chạy lệnh sau để cài đặt gói Pip này trên Pi:

    ```sh
    pip3 install seeed-python-dht
    ```

1. Thêm đoạn mã sau vào tệp `app.py` để nhập các thư viện cần thiết:

    ```python
    import time
    from seeed_dht import DHT
    ```

    Lệnh `from seeed_dht import DHT` nhập lớp `DHT` để tương tác với cảm biến nhiệt độ Grove từ module `seeed_dht`.

1. Thêm đoạn mã sau sau đoạn mã trên để tạo một thể hiện của lớp quản lý cảm biến nhiệt độ:

    ```python
    sensor = DHT("11", 5)
    ```

    Đoạn mã này khai báo một thể hiện của lớp `DHT` để quản lý cảm biến **D**igital **H**umidity và **T**emperature. Tham số đầu tiên cho biết cảm biến đang sử dụng là cảm biến *DHT11* - thư viện bạn đang sử dụng hỗ trợ các biến thể khác của cảm biến này. Tham số thứ hai cho biết cảm biến được kết nối với cổng kỹ thuật số `D5` trên Grove base hat.

    > ✅ Nhớ rằng, tất cả các ổ cắm đều có số chân duy nhất. Các chân 0, 2, 4 và 6 là chân analog, các chân 5, 16, 18, 22, 24 và 26 là chân kỹ thuật số.

1. Thêm một vòng lặp vô hạn sau đoạn mã trên để lấy giá trị cảm biến nhiệt độ và in ra console:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    Lệnh gọi `sensor.read()` trả về một tuple gồm độ ẩm và nhiệt độ. Bạn chỉ cần giá trị nhiệt độ, vì vậy độ ẩm sẽ bị bỏ qua. Giá trị nhiệt độ sau đó được in ra console.

1. Thêm một khoảng nghỉ nhỏ 10 giây ở cuối `loop` vì không cần kiểm tra mức nhiệt độ liên tục. Khoảng nghỉ giúp giảm tiêu thụ năng lượng của thiết bị.

    ```python
    time.sleep(10)
    ```

1. Từ Terminal của VS Code, chạy lệnh sau để chạy ứng dụng Python của bạn:

    ```sh
    python3 app.py
    ```

    Bạn sẽ thấy các giá trị nhiệt độ được hiển thị trên console. Sử dụng một vật gì đó để làm ấm cảm biến, chẳng hạn như đặt ngón tay cái lên cảm biến hoặc sử dụng quạt để thấy các giá trị thay đổi:

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py 
    Temperature 26°C
    Temperature 26°C
    Temperature 28°C
    Temperature 30°C
    Temperature 32°C
    ```

> 💁 Bạn có thể tìm thấy đoạn mã này trong thư mục [code-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/pi).

😀 Chương trình cảm biến nhiệt độ của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, nên sử dụng dịch vụ dịch thuật chuyên nghiệp từ con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.