<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "288aebb0c59f7be1d2719b8f9660a313",
  "translation_date": "2025-08-27T21:20:04+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/wio-terminal-proximity.md",
  "language_code": "vi"
}
-->
# Phát hiện khoảng cách gần - Wio Terminal

Trong phần này của bài học, bạn sẽ thêm cảm biến khoảng cách vào Wio Terminal và đọc khoảng cách từ nó.

## Phần cứng

Wio Terminal cần một cảm biến khoảng cách.

Cảm biến bạn sẽ sử dụng là [Grove Time of Flight distance sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Cảm biến này sử dụng một module đo khoảng cách bằng laser để phát hiện khoảng cách. Cảm biến này có phạm vi từ 10mm đến 2000mm (1cm - 2m) và sẽ báo cáo giá trị trong phạm vi đó khá chính xác, với các khoảng cách trên 1000mm được báo cáo là 8109mm.

Máy đo khoảng cách laser nằm ở mặt sau của cảm biến, đối diện với cổng Grove.

Đây là một cổng I2C.

### Kết nối cảm biến Time of Flight

Cảm biến Grove Time of Flight có thể được kết nối với Wio Terminal.

#### Nhiệm vụ - kết nối cảm biến Time of Flight

Kết nối cảm biến Time of Flight.

![Một cảm biến Grove Time of Flight](../../../../../translated_images/vi/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.png)

1. Cắm một đầu của cáp Grove vào cổng trên cảm biến Time of Flight. Nó chỉ có thể cắm theo một chiều.

1. Khi Wio Terminal chưa được kết nối với máy tính hoặc nguồn điện khác, cắm đầu còn lại của cáp Grove vào cổng Grove bên trái trên Wio Terminal khi bạn nhìn vào màn hình. Đây là cổng gần nút nguồn nhất. Đây là một cổng kết hợp kỹ thuật số và I2C.

![Cảm biến Grove Time of Flight được kết nối với cổng bên trái](../../../../../translated_images/vi/wio-time-of-flight-sensor.c4c182131d2ea73d.webp)

1. Bây giờ bạn có thể kết nối Wio Terminal với máy tính của mình.

## Lập trình cảm biến Time of Flight

Wio Terminal bây giờ có thể được lập trình để sử dụng cảm biến Time of Flight đã được gắn.

### Nhiệm vụ - lập trình cảm biến Time of Flight

1. Tạo một dự án Wio Terminal mới bằng PlatformIO. Đặt tên dự án là `distance-sensor`. Thêm mã vào hàm `setup` để cấu hình cổng serial.

1. Thêm một thư viện phụ thuộc cho thư viện cảm biến khoảng cách Seeed Grove Time of Flight vào tệp `platformio.ini` của dự án:

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

1. Trong `main.cpp`, thêm đoạn mã sau bên dưới các chỉ thị include hiện có để khai báo một instance của lớp `Seeed_vl53l0x` để tương tác với cảm biến Time of Flight:

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

1. Thêm đoạn mã sau vào cuối hàm `setup` để khởi tạo cảm biến:

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

1. Trong hàm `loop`, đọc một giá trị từ cảm biến:

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    Đoạn mã này khởi tạo một cấu trúc dữ liệu để đọc dữ liệu vào, sau đó truyền nó vào phương thức `PerformSingleRangingMeasurement`, nơi nó sẽ được điền với giá trị đo khoảng cách.

1. Bên dưới đoạn mã này, ghi ra giá trị đo khoảng cách, sau đó chờ 1 giây:

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

1. Biên dịch, tải lên và chạy đoạn mã này. Bạn sẽ có thể thấy các giá trị đo khoảng cách trên serial monitor. Đặt các vật thể gần cảm biến và bạn sẽ thấy giá trị đo khoảng cách:

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Máy đo khoảng cách nằm ở mặt sau của cảm biến, vì vậy hãy đảm bảo bạn sử dụng đúng mặt khi đo khoảng cách.

    ![Máy đo khoảng cách ở mặt sau của cảm biến Time of Flight hướng về một quả chuối](../../../../../translated_images/vi/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 Bạn có thể tìm thấy đoạn mã này trong thư mục [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal).

😀 Chương trình cảm biến khoảng cách của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.