<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-27T22:22:06+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "vi"
}
-->
# Điều khiển đèn ngủ qua Internet - Wio Terminal

Thiết bị IoT cần được lập trình để giao tiếp với *test.mosquitto.org* bằng MQTT nhằm gửi các giá trị đo lường từ cảm biến ánh sáng và nhận lệnh để điều khiển đèn LED.

Trong phần này của bài học, bạn sẽ kết nối Wio Terminal của mình với một MQTT broker.

## Cài đặt thư viện WiFi và MQTT cho Arduino

Để giao tiếp với MQTT broker, bạn cần cài đặt một số thư viện Arduino để sử dụng chip WiFi trong Wio Terminal và giao tiếp với MQTT. Khi phát triển cho các thiết bị Arduino, bạn có thể sử dụng một loạt các thư viện chứa mã nguồn mở và triển khai nhiều tính năng khác nhau. Seeed cung cấp các thư viện cho Wio Terminal cho phép nó giao tiếp qua WiFi. Các nhà phát triển khác đã xuất bản các thư viện để giao tiếp với MQTT broker, và bạn sẽ sử dụng những thư viện này với thiết bị của mình.

Các thư viện này được cung cấp dưới dạng mã nguồn có thể được tự động nhập vào PlatformIO và biên dịch cho thiết bị của bạn. Bằng cách này, các thư viện Arduino sẽ hoạt động trên bất kỳ thiết bị nào hỗ trợ framework Arduino, miễn là thiết bị có phần cứng cụ thể cần thiết cho thư viện đó. Một số thư viện, chẳng hạn như thư viện WiFi của Seeed, chỉ dành riêng cho một số phần cứng nhất định.

Thư viện có thể được cài đặt toàn cầu và biên dịch nếu cần, hoặc vào một dự án cụ thể. Đối với bài tập này, các thư viện sẽ được cài đặt vào dự án.

✅ Bạn có thể tìm hiểu thêm về quản lý thư viện và cách tìm, cài đặt thư viện trong [tài liệu thư viện PlatformIO](https://docs.platformio.org/en/latest/librarymanager/index.html).

### Nhiệm vụ - cài đặt thư viện WiFi và MQTT cho Arduino

Cài đặt các thư viện Arduino.

1. Mở dự án đèn ngủ trong VS Code.

1. Thêm nội dung sau vào cuối tệp `platformio.ini`:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    Điều này nhập các thư viện WiFi của Seeed. Cú pháp `@ <number>` đề cập đến một phiên bản cụ thể của thư viện.

    > 💁 Bạn có thể loại bỏ `@ <number>` để luôn sử dụng phiên bản mới nhất của các thư viện, nhưng không có gì đảm bảo rằng các phiên bản sau sẽ hoạt động với mã bên dưới. Mã ở đây đã được kiểm tra với phiên bản này của các thư viện.

    Đây là tất cả những gì bạn cần làm để thêm các thư viện. Lần tiếp theo PlatformIO xây dựng dự án, nó sẽ tải xuống mã nguồn của các thư viện này và biên dịch vào dự án của bạn.

1. Thêm nội dung sau vào `lib_deps`:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    Điều này nhập [PubSubClient](https://github.com/knolleary/pubsubclient), một client MQTT cho Arduino.

## Kết nối với WiFi

Wio Terminal giờ đây có thể kết nối với WiFi.

### Nhiệm vụ - kết nối với WiFi

Kết nối Wio Terminal với WiFi.

1. Tạo một tệp mới trong thư mục `src` có tên `config.h`. Bạn có thể làm điều này bằng cách chọn thư mục `src`, hoặc tệp `main.cpp` bên trong, và chọn nút **New file** từ trình khám phá. Nút này chỉ xuất hiện khi con trỏ của bạn ở trên trình khám phá.

    ![Nút tạo tệp mới](../../../../../translated_images/vi/vscode-new-file-button.182702340fe6723c.png)

1. Thêm mã sau vào tệp này để định nghĩa các hằng số cho thông tin đăng nhập WiFi của bạn:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    Thay thế `<SSID>` bằng SSID của WiFi của bạn. Thay thế `<PASSWORD>` bằng mật khẩu WiFi của bạn.

1. Mở tệp `main.cpp`.

1. Thêm các chỉ thị `#include` sau vào đầu tệp:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    Điều này bao gồm các tệp header cho các thư viện bạn đã thêm trước đó, cũng như tệp header config. Các tệp header này cần thiết để yêu cầu PlatformIO đưa mã từ các thư viện vào. Nếu không bao gồm rõ ràng các tệp header này, một số mã sẽ không được biên dịch và bạn sẽ gặp lỗi biên dịch.

1. Thêm mã sau vào phía trên hàm `setup`:

    ```cpp
    void connectWiFi()
    {
        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("Connecting to WiFi..");
            WiFi.begin(SSID, PASSWORD);
            delay(500);
        }
    
        Serial.println("Connected!");
    }
    ```

    Mã này sẽ lặp lại trong khi thiết bị chưa kết nối với WiFi, và cố gắng kết nối bằng SSID và mật khẩu từ tệp header config.

1. Thêm một lệnh gọi đến hàm này ở cuối hàm `setup`, sau khi các chân đã được cấu hình.

    ```cpp
    connectWiFi();
    ```

1. Tải mã này lên thiết bị của bạn để kiểm tra kết nối WiFi có hoạt động hay không. Bạn sẽ thấy điều này trong serial monitor.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## Kết nối với MQTT

Khi Wio Terminal đã kết nối với WiFi, nó có thể kết nối với MQTT broker.

### Nhiệm vụ - kết nối với MQTT

Kết nối với MQTT broker.

1. Thêm mã sau vào cuối tệp `config.h` để định nghĩa thông tin kết nối cho MQTT broker:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    Thay thế `<ID>` bằng một ID duy nhất sẽ được sử dụng làm tên của client thiết bị này, và sau đó cho các topic mà thiết bị này sẽ publish và subscribe. Broker *test.mosquitto.org* là công cộng và được sử dụng bởi nhiều người, bao gồm cả các học viên khác đang làm bài tập này. Có một tên client MQTT và các tên topic duy nhất đảm bảo mã của bạn sẽ không xung đột với bất kỳ ai khác. Bạn cũng sẽ cần ID này khi tạo mã server sau trong bài tập này.

    > 💁 Bạn có thể sử dụng một trang web như [GUIDGen](https://www.guidgen.com) để tạo một ID duy nhất.

    `BROKER` là URL của MQTT broker.

    `CLIENT_NAME` là tên duy nhất cho client MQTT này trên broker.

1. Mở tệp `main.cpp`, và thêm mã sau bên dưới hàm `connectWiFi` và phía trên hàm `setup`:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    Mã này tạo một WiFi client sử dụng các thư viện WiFi của Wio Terminal và sử dụng nó để tạo một MQTT client.

1. Bên dưới mã này, thêm nội dung sau:

    ```cpp
    void reconnectMQTTClient()
    {
        while (!client.connected())
        {
            Serial.print("Attempting MQTT connection...");
    
            if (client.connect(CLIENT_NAME.c_str()))
            {
                Serial.println("connected");
            }
            else
            {
                Serial.print("Retying in 5 seconds - failed, rc=");
                Serial.println(client.state());
                
                delay(5000);
            }
        }
    }
    ```

    Hàm này kiểm tra kết nối với MQTT broker và kết nối lại nếu chưa kết nối. Nó lặp lại liên tục khi chưa kết nối và cố gắng kết nối bằng tên client duy nhất được định nghĩa trong tệp header config.

    Nếu kết nối thất bại, nó sẽ thử lại sau 5 giây.

1. Thêm mã sau bên dưới hàm `reconnectMQTTClient`:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    Mã này thiết lập MQTT broker cho client, cũng như thiết lập callback khi một tin nhắn được nhận. Sau đó, nó cố gắng kết nối với broker.

1. Gọi hàm `createMQTTClient` trong hàm `setup` sau khi WiFi đã được kết nối.

1. Thay thế toàn bộ hàm `loop` bằng nội dung sau:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    Mã này bắt đầu bằng việc kết nối lại với MQTT broker. Các kết nối này có thể dễ dàng bị gián đoạn, vì vậy việc kiểm tra thường xuyên và kết nối lại nếu cần là rất quan trọng. Sau đó, nó gọi phương thức `loop` trên MQTT client để xử lý bất kỳ tin nhắn nào đang đến trên topic đã subscribe. Ứng dụng này là đơn luồng, vì vậy tin nhắn không thể được nhận trên một luồng nền, do đó cần dành thời gian trên luồng chính để xử lý bất kỳ tin nhắn nào đang chờ trên kết nối mạng.

    Cuối cùng, một độ trễ 2 giây đảm bảo mức ánh sáng không được gửi quá thường xuyên và giảm tiêu thụ năng lượng của thiết bị.

1. Tải mã lên Wio Terminal của bạn, và sử dụng Serial Monitor để xem thiết bị kết nối với WiFi và MQTT.

    ```output
    > Executing task: platformio device monitor <
    
    source /Users/jimbennett/GitHub/IoT-For-Beginners/1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal/nightlight/.venv/bin/activate
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    ```

> 💁 Bạn có thể tìm thấy mã này trong thư mục [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal).

😀 Bạn đã kết nối thành công thiết bị của mình với một MQTT broker.

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.