<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f3c5d8afa2ef6a0b425ef8ff20615cb4",
  "translation_date": "2025-08-28T01:56:37+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/wio-terminal-relay.md",
  "language_code": "vi"
}
-->
# Điều khiển relay - Wio Terminal

Trong phần này của bài học, bạn sẽ thêm một relay vào Wio Terminal bên cạnh cảm biến độ ẩm đất và điều khiển nó dựa trên mức độ ẩm đất.

## Phần cứng

Wio Terminal cần một relay.

Relay bạn sẽ sử dụng là [Grove relay](https://www.seeedstudio.com/Grove-Relay.html), một relay thường mở (nghĩa là mạch đầu ra sẽ mở hoặc ngắt kết nối khi không có tín hiệu gửi đến relay) có thể xử lý mạch đầu ra lên đến 250V và 10A.

Đây là một bộ truyền động kỹ thuật số, vì vậy nó kết nối với các chân kỹ thuật số trên Wio Terminal. Cổng kết hợp analog/kỹ thuật số đã được sử dụng với cảm biến độ ẩm đất, vì vậy relay này sẽ được cắm vào cổng còn lại, là cổng kết hợp I2C và kỹ thuật số.

### Kết nối relay

Relay Grove có thể được kết nối với cổng kỹ thuật số của Wio Terminal.

#### Nhiệm vụ

Kết nối relay.

![Một relay Grove](../../../../../translated_images/grove-relay.d426958ca210fbd0fb7983d7edc069d46c73a8b0a099d94797bd756f7b6bb6be.vi.png)

1. Cắm một đầu của cáp Grove vào ổ cắm trên relay. Nó chỉ có thể cắm theo một chiều.

1. Khi Wio Terminal đã ngắt kết nối khỏi máy tính hoặc nguồn điện khác, cắm đầu còn lại của cáp Grove vào ổ cắm Grove bên trái trên Wio Terminal khi bạn nhìn vào màn hình. Để cảm biến độ ẩm đất kết nối với ổ cắm bên phải.

![Relay Grove được kết nối với ổ cắm bên trái, và cảm biến độ ẩm đất được kết nối với ổ cắm bên phải](../../../../../translated_images/wio-relay-and-soil-moisture-sensor.ed722202d42babe0be5f4518cf13e8c2c81e8df21d37839266cbdb60cf30172d.vi.png)

1. Cắm cảm biến độ ẩm đất vào đất, nếu nó chưa được cắm từ bài học trước.

## Lập trình relay

Bây giờ Wio Terminal có thể được lập trình để sử dụng relay đã kết nối.

### Nhiệm vụ

Lập trình thiết bị.

1. Mở dự án `soil-moisture-sensor` từ bài học trước trong VS Code nếu nó chưa được mở. Bạn sẽ thêm vào dự án này.

2. Không có thư viện nào cho bộ truyền động này - đây là một bộ truyền động kỹ thuật số được điều khiển bằng tín hiệu cao hoặc thấp. Để bật nó, bạn gửi tín hiệu cao đến chân (3.3V), để tắt nó, bạn gửi tín hiệu thấp (0V). Bạn có thể làm điều này bằng cách sử dụng hàm [`digitalWrite`](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/) tích hợp sẵn của Arduino. Bắt đầu bằng cách thêm đoạn mã sau vào cuối hàm `setup` để thiết lập cổng kết hợp I2C/kỹ thuật số làm chân đầu ra để gửi điện áp đến relay:

    ```cpp
    pinMode(PIN_WIRE_SCL, OUTPUT);
    ```

    `PIN_WIRE_SCL` là số cổng cho cổng kết hợp I2C/kỹ thuật số.

1. Để kiểm tra relay hoạt động, thêm đoạn mã sau vào hàm `loop`, bên dưới lệnh `delay` cuối cùng:

    ```cpp
    digitalWrite(PIN_WIRE_SCL, HIGH);
    delay(500);
    digitalWrite(PIN_WIRE_SCL, LOW);
    ```

    Đoạn mã này gửi tín hiệu cao đến chân mà relay được kết nối để bật nó, chờ 500ms (nửa giây), sau đó gửi tín hiệu thấp để tắt relay.

1. Biên dịch và tải mã lên Wio Terminal.

1. Sau khi tải lên, relay sẽ bật và tắt mỗi 10 giây, với độ trễ nửa giây giữa bật và tắt. Bạn sẽ nghe thấy relay kêu "click" khi bật và "click" khi tắt. Đèn LED trên bảng Grove sẽ sáng khi relay bật và tắt khi relay tắt.

    ![Relay bật và tắt](../../../../../images/relay-turn-on-off.gif)

## Điều khiển relay từ độ ẩm đất

Bây giờ relay đã hoạt động, nó có thể được điều khiển dựa trên các giá trị đọc từ cảm biến độ ẩm đất.

### Nhiệm vụ

Điều khiển relay.

1. Xóa 3 dòng mã mà bạn đã thêm để kiểm tra relay. Thay thế chúng bằng đoạn mã sau:

    ```cpp
    if (soil_moisture > 450)
    {
        Serial.println("Soil Moisture is too low, turning relay on.");
        digitalWrite(PIN_WIRE_SCL, HIGH);
    }
    else
    {
        Serial.println("Soil Moisture is ok, turning relay off.");
        digitalWrite(PIN_WIRE_SCL, LOW);
    }
    ```

    Đoạn mã này kiểm tra mức độ ẩm đất từ cảm biến độ ẩm đất. Nếu giá trị lớn hơn 450, nó sẽ bật relay, và tắt relay khi giá trị nhỏ hơn 450.

    > 💁 Nhớ rằng cảm biến độ ẩm đất điện dung đọc giá trị càng thấp thì độ ẩm trong đất càng cao và ngược lại.

1. Biên dịch và tải mã lên Wio Terminal.

1. Theo dõi thiết bị qua serial monitor. Bạn sẽ thấy relay bật hoặc tắt tùy thuộc vào mức độ ẩm đất. Thử nghiệm với đất khô, sau đó thêm nước.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Bạn có thể tìm thấy đoạn mã này trong thư mục [code-relay/wio-terminal](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/wio-terminal).

😀 Chương trình điều khiển relay từ cảm biến độ ẩm đất của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp từ con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.