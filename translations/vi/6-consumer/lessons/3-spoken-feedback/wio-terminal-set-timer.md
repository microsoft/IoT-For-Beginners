<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-27T23:19:58+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "vi"
}
-->
# Đặt hẹn giờ - Wio Terminal

Trong phần này của bài học, bạn sẽ gọi mã serverless để hiểu giọng nói và đặt hẹn giờ trên Wio Terminal dựa trên kết quả.

## Đặt hẹn giờ

Văn bản nhận được từ cuộc gọi chuyển đổi giọng nói thành văn bản cần được gửi đến mã serverless của bạn để xử lý bằng LUIS, từ đó nhận lại số giây cho hẹn giờ. Số giây này có thể được sử dụng để đặt hẹn giờ.

Vi điều khiển không hỗ trợ đa luồng trong Arduino một cách tự nhiên, vì vậy không có các lớp hẹn giờ tiêu chuẩn như bạn có thể thấy khi lập trình bằng Python hoặc các ngôn ngữ cấp cao khác. Thay vào đó, bạn có thể sử dụng các thư viện hẹn giờ hoạt động bằng cách đo thời gian đã trôi qua trong hàm `loop` và gọi các hàm khi thời gian kết thúc.

### Nhiệm vụ - gửi văn bản đến hàm serverless

1. Mở dự án `smart-timer` trong VS Code nếu chưa mở.

1. Mở tệp tiêu đề `config.h` và thêm URL cho ứng dụng hàm của bạn:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    Thay thế `<URL>` bằng URL của ứng dụng hàm mà bạn đã lấy được ở bước cuối cùng của bài học trước, trỏ đến địa chỉ IP của máy cục bộ đang chạy ứng dụng hàm.

1. Tạo một tệp mới trong thư mục `src` có tên `language_understanding.h`. Tệp này sẽ được sử dụng để định nghĩa một lớp gửi giọng nói đã nhận dạng đến ứng dụng hàm của bạn để chuyển đổi thành số giây bằng LUIS.

1. Thêm nội dung sau vào đầu tệp này:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    Điều này bao gồm một số tệp tiêu đề cần thiết.

1. Định nghĩa một lớp có tên `LanguageUnderstanding`, và khai báo một thể hiện của lớp này:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. Để gọi ứng dụng hàm của bạn, bạn cần khai báo một WiFi client. Thêm nội dung sau vào phần `private` của lớp:

    ```cpp
    WiFiClient _client;
    ```

1. Trong phần `public`, khai báo một phương thức có tên `GetTimerDuration` để gọi ứng dụng hàm:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. Trong phương thức `GetTimerDuration`, thêm mã sau để xây dựng JSON gửi đến ứng dụng hàm:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Điều này chuyển đổi văn bản được truyền vào phương thức `GetTimerDuration` thành JSON sau:

    ```json
    {
        "text" : "<text>"
    }
    ```

    trong đó `<text>` là văn bản được truyền vào hàm.

1. Bên dưới đoạn mã này, thêm mã sau để thực hiện cuộc gọi đến ứng dụng hàm:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Điều này thực hiện yêu cầu POST đến ứng dụng hàm, gửi nội dung JSON và nhận mã phản hồi.

1. Thêm mã sau bên dưới đoạn mã này:

    ```cpp
    int seconds = 0;
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonObject obj = doc.as<JsonObject>();
        seconds = obj["seconds"].as<int>();
    }
    else
    {
        Serial.print("Failed to understand text - error ");
        Serial.println(httpResponseCode);
    }
    ```

    Mã này kiểm tra mã phản hồi. Nếu là 200 (thành công), số giây cho hẹn giờ sẽ được lấy từ nội dung phản hồi. Nếu không, một lỗi sẽ được gửi đến màn hình serial và số giây sẽ được đặt thành 0.

1. Thêm mã sau vào cuối phương thức này để đóng kết nối HTTP và trả về số giây:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. Trong tệp `main.cpp`, bao gồm tiêu đề mới này:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Ở cuối hàm `processAudio`, gọi phương thức `GetTimerDuration` để lấy thời gian hẹn giờ:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    Điều này chuyển đổi văn bản từ cuộc gọi đến lớp `SpeechToText` thành số giây cho hẹn giờ.

### Nhiệm vụ - đặt hẹn giờ

Số giây có thể được sử dụng để đặt hẹn giờ.

1. Thêm phụ thuộc thư viện sau vào tệp `platformio.ini` để thêm thư viện đặt hẹn giờ:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. Thêm chỉ thị bao gồm thư viện này vào tệp `main.cpp`:

    ```cpp
    #include <arduino-timer.h>
    ```

1. Phía trên hàm `processAudio`, thêm mã sau:

    ```cpp
    auto timer = timer_create_default();
    ```

    Mã này khai báo một hẹn giờ có tên `timer`.

1. Bên dưới đoạn mã này, thêm mã sau:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    Hàm `say` này cuối cùng sẽ chuyển đổi văn bản thành giọng nói, nhưng hiện tại nó chỉ ghi văn bản được truyền vào màn hình serial.

1. Bên dưới hàm `say`, thêm mã sau:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    Đây là hàm callback sẽ được gọi khi hẹn giờ hết hạn. Nó được truyền một thông báo để nói khi hẹn giờ hết hạn. Hẹn giờ có thể lặp lại, và điều này có thể được kiểm soát bởi giá trị trả về của callback - giá trị này trả về `false`, để báo hẹn giờ không chạy lại.

1. Thêm mã sau vào cuối hàm `processAudio`:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    Mã này kiểm tra tổng số giây, và nếu là 0, trả về từ cuộc gọi hàm để không đặt hẹn giờ. Sau đó, nó chuyển đổi tổng số giây thành phút và giây.

1. Bên dưới đoạn mã này, thêm nội dung sau để tạo thông báo khi hẹn giờ bắt đầu:

    ```cpp
    String begin_message;
    if (minutes > 0)
    {
        begin_message += minutes;
        begin_message += " minute ";
    }
    if (seconds > 0)
    {
        begin_message += seconds;
        begin_message += " second ";
    }

    begin_message += "timer started.";
    ```

1. Bên dưới đoạn mã này, thêm mã tương tự để tạo thông báo khi hẹn giờ hết hạn:

    ```cpp
    String end_message("Times up on your ");
    if (minutes > 0)
    {
        end_message += minutes;
        end_message += " minute ";
    }
    if (seconds > 0)
    {
        end_message += seconds;
        end_message += " second ";
    }

    end_message += "timer.";
    ```

1. Sau đó, nói thông báo hẹn giờ bắt đầu:

    ```cpp
    say(begin_message);
    ```

1. Ở cuối hàm này, bắt đầu hẹn giờ:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    Điều này kích hoạt hẹn giờ. Hẹn giờ được đặt bằng mili giây, vì vậy tổng số giây được nhân với 1.000 để chuyển đổi thành mili giây. Hàm `timerExpired` được truyền làm callback, và `end_message` được truyền làm đối số để truyền đến callback. Callback này chỉ nhận các đối số kiểu `void *`, vì vậy chuỗi được chuyển đổi phù hợp.

1. Cuối cùng, hẹn giờ cần *tick*, và điều này được thực hiện trong hàm `loop`. Thêm mã sau vào cuối hàm `loop`:

    ```cpp
    timer.tick();
    ```

1. Biên dịch mã này, tải lên Wio Terminal của bạn và kiểm tra qua màn hình serial. Khi bạn thấy `Ready` trên màn hình serial, nhấn nút C (nút ở bên trái, gần công tắc nguồn), và nói. 4 giây âm thanh sẽ được ghi lại, chuyển đổi thành văn bản, sau đó gửi đến ứng dụng hàm của bạn, và một hẹn giờ sẽ được đặt. Đảm bảo ứng dụng hàm của bạn đang chạy cục bộ.

    Bạn sẽ thấy khi hẹn giờ bắt đầu và khi nó kết thúc.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Set a 2 minute and 27 second timer.","Offset":4700000,"Duration":35300000}
    Set a 2 minute and 27 second timer.
    {"seconds": 147}
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 Bạn có thể tìm thấy mã này trong thư mục [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal).

😀 Chương trình hẹn giờ của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.