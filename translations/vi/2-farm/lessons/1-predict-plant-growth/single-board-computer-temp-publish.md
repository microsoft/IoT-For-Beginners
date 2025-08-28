<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4efc74299e19f5d08f2f3f34451a11ba",
  "translation_date": "2025-08-28T01:46:14+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/single-board-computer-temp-publish.md",
  "language_code": "vi"
}
-->
# Xuất bản nhiệt độ - Phần cứng IoT ảo và Raspberry Pi

Trong phần này của bài học, bạn sẽ xuất bản các giá trị nhiệt độ được Raspberry Pi hoặc Thiết bị IoT ảo phát hiện qua MQTT để sau này có thể sử dụng để tính GDD.

## Xuất bản nhiệt độ

Khi nhiệt độ đã được đọc, nó có thể được xuất bản qua MQTT đến một đoạn mã 'máy chủ' để đọc các giá trị và lưu trữ chúng, sẵn sàng để sử dụng cho việc tính toán GDD.

### Nhiệm vụ - xuất bản nhiệt độ

Lập trình thiết bị để xuất bản dữ liệu nhiệt độ.

1. Mở dự án ứng dụng `temperature-sensor` nếu chưa mở.

1. Lặp lại các bước bạn đã thực hiện trong bài học 4 để kết nối với MQTT và gửi dữ liệu telemetry. Bạn sẽ sử dụng cùng một broker Mosquitto công khai.

    Các bước thực hiện như sau:

    - Thêm gói pip MQTT
    - Thêm mã để kết nối với broker MQTT
    - Thêm mã để xuất bản dữ liệu telemetry

    > ⚠️ Tham khảo [hướng dẫn kết nối với MQTT](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md) và [hướng dẫn gửi dữ liệu telemetry](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md) từ bài học 4 nếu cần.

1. Đảm bảo `client_name` phản ánh tên của dự án này:

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. Đối với dữ liệu telemetry, thay vì gửi giá trị ánh sáng, hãy gửi giá trị nhiệt độ được đọc từ cảm biến DHT trong một thuộc tính của tài liệu JSON gọi là `temperature`:

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. Giá trị nhiệt độ không cần phải được đọc thường xuyên - nó sẽ không thay đổi nhiều trong một khoảng thời gian ngắn, vì vậy hãy đặt `time.sleep` thành 10 phút:

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 Hàm `sleep` nhận thời gian tính bằng giây, vì vậy để dễ đọc hơn, giá trị được truyền dưới dạng kết quả của một phép tính. 60 giây trong một phút, vì vậy 10 x (60 giây trong một phút) sẽ tạo ra độ trễ 10 phút.

1. Chạy mã theo cách tương tự như bạn đã chạy mã từ phần trước của bài tập. Nếu bạn đang sử dụng thiết bị IoT ảo, hãy đảm bảo ứng dụng CounterFit đang chạy và các cảm biến độ ẩm và nhiệt độ đã được tạo trên các chân chính xác.

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 Bạn có thể tìm thấy mã này trong thư mục [code-publish-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/virtual-device) hoặc thư mục [code-publish-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/pi).

😀 Bạn đã xuất bản thành công nhiệt độ dưới dạng dữ liệu telemetry từ thiết bị của mình.

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.