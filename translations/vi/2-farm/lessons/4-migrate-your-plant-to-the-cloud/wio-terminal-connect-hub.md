<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-28T01:38:14+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "vi"
}
-->
# Kết nối thiết bị IoT của bạn với đám mây - Wio Terminal

Trong phần này của bài học, bạn sẽ kết nối Wio Terminal của mình với IoT Hub để gửi dữ liệu đo lường và nhận lệnh.

## Kết nối thiết bị của bạn với IoT Hub

Bước tiếp theo là kết nối thiết bị của bạn với IoT Hub.

### Nhiệm vụ - kết nối với IoT Hub

1. Mở dự án `soil-moisture-sensor` trong VS Code.

1. Mở tệp `platformio.ini`. Xóa thư viện phụ thuộc `knolleary/PubSubClient`. Thư viện này được sử dụng để kết nối với MQTT broker công cộng, nhưng không cần thiết để kết nối với IoT Hub.

1. Thêm các thư viện phụ thuộc sau:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    Thư viện `Seeed Arduino RTC` cung cấp mã để tương tác với đồng hồ thời gian thực trong Wio Terminal, được sử dụng để theo dõi thời gian. Các thư viện còn lại cho phép thiết bị IoT của bạn kết nối với IoT Hub.

1. Thêm đoạn mã sau vào cuối tệp `platformio.ini`:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    Điều này thiết lập một cờ trình biên dịch cần thiết khi biên dịch mã Arduino IoT Hub.

1. Mở tệp tiêu đề `config.h`. Xóa tất cả các cài đặt MQTT và thêm hằng số sau cho chuỗi kết nối thiết bị:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    Thay thế `<connection string>` bằng chuỗi kết nối cho thiết bị của bạn mà bạn đã sao chép trước đó.

1. Kết nối với IoT Hub sử dụng token dựa trên thời gian. Điều này có nghĩa là thiết bị IoT cần biết thời gian hiện tại. Không giống như các hệ điều hành như Windows, macOS hoặc Linux, vi điều khiển không tự động đồng bộ hóa thời gian hiện tại qua Internet. Điều này có nghĩa là bạn cần thêm mã để lấy thời gian hiện tại từ một [NTP](https://wikipedia.org/wiki/Network_Time_Protocol) server. Sau khi thời gian được lấy, nó có thể được lưu trữ trong đồng hồ thời gian thực của Wio Terminal, cho phép yêu cầu thời gian chính xác vào một ngày sau đó, giả sử thiết bị không bị mất nguồn. Thêm một tệp mới có tên `ntp.h` với đoạn mã sau:

    ```cpp
    #pragma once
    
    #include "DateTime.h"
    #include <time.h>
    #include "samd/NTPClientAz.h"
    #include <sys/time.h>

    static void initTime()
    {
        WiFiUDP _udp;
        time_t epochTime = (time_t)-1;
        NTPClientAz ntpClient;

        ntpClient.begin();

        while (true)
        {
            epochTime = ntpClient.getEpochTime("0.pool.ntp.org");

            if (epochTime == (time_t)-1)
            {
                Serial.println("Fetching NTP epoch time failed! Waiting 2 seconds to retry.");
                delay(2000);
            }
            else
            {
                Serial.print("Fetched NTP epoch time is: ");

                char buff[32];
                sprintf(buff, "%.f", difftime(epochTime, (time_t)0));
                Serial.println(buff);
                break;
            }
        }

        ntpClient.end();

        struct timeval tv;
        tv.tv_sec = epochTime;
        tv.tv_usec = 0;

        settimeofday(&tv, NULL);
    }
    ```

    Chi tiết của đoạn mã này nằm ngoài phạm vi của bài học. Nó định nghĩa một hàm gọi là `initTime` để lấy thời gian hiện tại từ một NTP server và sử dụng nó để thiết lập đồng hồ trên Wio Terminal.

1. Mở tệp `main.cpp` và xóa tất cả mã MQTT, bao gồm tệp tiêu đề `PubSubClient.h`, khai báo biến `PubSubClient`, các phương thức `reconnectMQTTClient` và `createMQTTClient`, và bất kỳ lời gọi nào đến các biến và phương thức này. Tệp này chỉ nên chứa mã để kết nối với WiFi, lấy độ ẩm đất và tạo tài liệu JSON từ đó.

1. Thêm các chỉ thị `#include` sau vào đầu tệp `main.cpp` để bao gồm các tệp tiêu đề cho thư viện IoT Hub và để thiết lập thời gian:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. Thêm lời gọi sau vào cuối hàm `setup` để thiết lập thời gian hiện tại:

    ```cpp
    initTime();
    ```

1. Thêm khai báo biến sau vào đầu tệp, ngay dưới các chỉ thị include:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    Điều này khai báo một `IOTHUB_DEVICE_CLIENT_LL_HANDLE`, một handle để kết nối với IoT Hub.

1. Bên dưới đó, thêm đoạn mã sau:

    ```cpp
    static void connectionStatusCallback(IOTHUB_CLIENT_CONNECTION_STATUS result, IOTHUB_CLIENT_CONNECTION_STATUS_REASON reason, void *user_context)
    {
        if (result == IOTHUB_CLIENT_CONNECTION_AUTHENTICATED)
        {
            Serial.println("The device client is connected to iothub");
        }
        else
        {
            Serial.println("The device client has been disconnected");
        }
    }
    ```

    Điều này khai báo một hàm callback sẽ được gọi khi kết nối với IoT Hub thay đổi trạng thái, chẳng hạn như kết nối hoặc ngắt kết nối. Trạng thái sẽ được gửi đến cổng serial.

1. Bên dưới đó, thêm một hàm để kết nối với IoT Hub:

    ```cpp
    void connectIoTHub()
    {
        IoTHub_Init();
    
        _device_ll_handle = IoTHubDeviceClient_LL_CreateFromConnectionString(CONNECTION_STRING, MQTT_Protocol);
        
        if (_device_ll_handle == NULL)
        {
            Serial.println("Failure creating Iothub device. Hint: Check your connection string.");
            return;
        }
    
        IoTHubDeviceClient_LL_SetConnectionStatusCallback(_device_ll_handle, connectionStatusCallback, NULL);
    }
    ```

    Đoạn mã này khởi tạo mã thư viện IoT Hub, sau đó tạo một kết nối sử dụng chuỗi kết nối trong tệp tiêu đề `config.h`. Kết nối này dựa trên MQTT. Nếu kết nối thất bại, thông tin này sẽ được gửi đến cổng serial - nếu bạn thấy điều này trong đầu ra, hãy kiểm tra chuỗi kết nối. Cuối cùng, callback trạng thái kết nối được thiết lập.

1. Gọi hàm này trong hàm `setup` bên dưới lời gọi đến `initTime`:

    ```cpp
    connectIoTHub();
    ```

1. Giống như với MQTT client, mã này chạy trên một luồng duy nhất nên cần thời gian để xử lý các tin nhắn được gửi bởi hub và gửi đến hub. Thêm đoạn mã sau vào đầu hàm `loop` để thực hiện điều này:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. Biên dịch và tải lên đoạn mã này. Bạn sẽ thấy kết nối trong serial monitor:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    Trong đầu ra, bạn có thể thấy thời gian NTP được lấy, sau đó là client thiết bị kết nối. Có thể mất vài giây để kết nối, vì vậy bạn có thể thấy độ ẩm đất trong đầu ra trong khi thiết bị đang kết nối.

    > 💁 Bạn có thể chuyển đổi thời gian UNIX của NTP sang phiên bản dễ đọc hơn bằng cách sử dụng một trang web như [unixtimestamp.com](https://www.unixtimestamp.com)

## Gửi dữ liệu đo lường

Bây giờ thiết bị của bạn đã được kết nối, bạn có thể gửi dữ liệu đo lường đến IoT Hub thay vì MQTT broker.

### Nhiệm vụ - gửi dữ liệu đo lường

1. Thêm hàm sau vào phía trên hàm `setup`:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    Đoạn mã này tạo một tin nhắn IoT Hub từ một chuỗi được truyền làm tham số, gửi nó đến hub, sau đó dọn dẹp đối tượng tin nhắn.

1. Gọi đoạn mã này trong hàm `loop`, ngay sau dòng nơi dữ liệu đo lường được gửi đến cổng serial:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## Xử lý lệnh

Thiết bị của bạn cần xử lý một lệnh từ mã server để điều khiển relay. Lệnh này được gửi dưới dạng yêu cầu phương thức trực tiếp.

## Nhiệm vụ - xử lý yêu cầu phương thức trực tiếp

1. Thêm đoạn mã sau trước hàm `connectIoTHub`:

    ```cpp
    int directMethodCallback(const char *method_name, const unsigned char *payload, size_t size, unsigned char **response, size_t *response_size, void *userContextCallback)
    {
        Serial.printf("Direct method received %s\r\n", method_name);
    
        if (strcmp(method_name, "relay_on") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, HIGH);
        }
        else if (strcmp(method_name, "relay_off") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, LOW);
        }
    }
    ```

    Đoạn mã này định nghĩa một hàm callback mà thư viện IoT Hub có thể gọi khi nhận được yêu cầu phương thức trực tiếp. Phương thức được yêu cầu được gửi trong tham số `method_name`. Hàm này in phương thức được gọi ra cổng serial, sau đó bật hoặc tắt relay tùy thuộc vào tên phương thức.

    > 💁 Điều này cũng có thể được triển khai trong một yêu cầu phương thức trực tiếp duy nhất, truyền trạng thái mong muốn của relay trong payload có thể được truyền với yêu cầu phương thức và có sẵn từ tham số `payload`.

1. Thêm đoạn mã sau vào cuối hàm `directMethodCallback`:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    Yêu cầu phương thức trực tiếp cần một phản hồi, và phản hồi này gồm hai phần - phản hồi dưới dạng văn bản và mã trả về. Đoạn mã này sẽ tạo một kết quả dưới dạng tài liệu JSON sau:

    ```JSON
    {
        "Result": ""
    }
    ```

    Sau đó, tài liệu này được sao chép vào tham số `response`, và kích thước của phản hồi này được thiết lập trong tham số `response_size`. Đoạn mã này sau đó trả về `IOTHUB_CLIENT_OK` để cho thấy phương thức đã được xử lý thành công.

1. Kết nối callback bằng cách thêm đoạn mã sau vào cuối hàm `connectIoTHub`:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. Hàm `loop` sẽ gọi hàm `IoTHubDeviceClient_LL_DoWork` để xử lý các sự kiện được gửi bởi IoT Hub. Hàm này chỉ được gọi mỗi 10 giây do `delay`, nghĩa là các phương thức trực tiếp chỉ được xử lý mỗi 10 giây. Để làm cho điều này hiệu quả hơn, việc trì hoãn 10 giây có thể được triển khai dưới dạng nhiều lần trì hoãn ngắn hơn, gọi `IoTHubDeviceClient_LL_DoWork` mỗi lần. Để thực hiện điều này, thêm đoạn mã sau vào phía trên hàm `loop`:

    ```cpp
    void work_delay(int delay_time)
    {
        int current = 0;
        do
        {
            IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
            delay(100);
            current += 100;
        } while (current < delay_time);
    }
    ```

    Đoạn mã này sẽ lặp lại liên tục, gọi `IoTHubDeviceClient_LL_DoWork` và trì hoãn 100ms mỗi lần. Nó sẽ thực hiện điều này nhiều lần như cần thiết để trì hoãn trong khoảng thời gian được cung cấp trong tham số `delay_time`. Điều này có nghĩa là thiết bị đang chờ tối đa 100ms để xử lý các yêu cầu phương thức trực tiếp.

1. Trong hàm `loop`, xóa lời gọi đến `IoTHubDeviceClient_LL_DoWork`, và thay thế lời gọi `delay(10000)` bằng đoạn mã sau để gọi hàm mới này:

    ```cpp
    work_delay(10000);
    ```

> 💁 Bạn có thể tìm thấy đoạn mã này trong thư mục [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal).

😀 Chương trình cảm biến độ ẩm đất của bạn đã được kết nối với IoT Hub!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.