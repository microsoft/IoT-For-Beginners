# Kết nối thiết bị của bạn với Internet

![Tổng quan bài học dưới dạng sketchnote](../../../../../translated_images/vi/lesson-4.7344e074ea68fa54.webp)

> Sketchnote bởi [Nitya Narasimhan](https://github.com/nitya). Nhấp vào hình ảnh để xem phiên bản lớn hơn.

Bài học này được giảng dạy trong chuỗi [Hello IoT series](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) từ [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Bài học được chia thành 2 video - một bài giảng kéo dài 1 giờ và một buổi hỏi đáp kéo dài 1 giờ để đi sâu hơn vào các phần của bài học và trả lời câu hỏi.

[![Bài học 4: Kết nối thiết bị của bạn với Internet](https://img.youtube.com/vi/O4dd172mZhs/0.jpg)](https://youtu.be/O4dd172mZhs)

[![Bài học 4: Kết nối thiết bị của bạn với Internet - Giờ hỏi đáp](https://img.youtube.com/vi/j-cVCzRDE2Q/0.jpg)](https://youtu.be/j-cVCzRDE2Q)

> 🎥 Nhấp vào hình ảnh trên để xem video

## Câu hỏi trước bài giảng

[Câu hỏi trước bài giảng](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/7)

## Giới thiệu

Chữ **I** trong IoT là viết tắt của **Internet** - kết nối đám mây và các dịch vụ cho phép nhiều tính năng của thiết bị IoT, từ việc thu thập dữ liệu từ các cảm biến được kết nối với thiết bị, đến việc gửi tin nhắn để điều khiển các bộ truyền động. Các thiết bị IoT thường kết nối với một dịch vụ đám mây IoT duy nhất bằng một giao thức truyền thông tiêu chuẩn, và dịch vụ này được kết nối với phần còn lại của ứng dụng IoT của bạn, từ các dịch vụ AI để đưa ra quyết định thông minh dựa trên dữ liệu, đến các ứng dụng web để điều khiển hoặc báo cáo.

> 🎓 Dữ liệu thu thập từ cảm biến và gửi lên đám mây được gọi là dữ liệu đo từ xa (telemetry).

Thiết bị IoT có thể nhận tin nhắn từ đám mây. Thường thì các tin nhắn này chứa lệnh - tức là các hướng dẫn để thực hiện một hành động, có thể là nội bộ (như khởi động lại hoặc cập nhật firmware), hoặc sử dụng một bộ truyền động (như bật đèn).

Bài học này giới thiệu một số giao thức truyền thông mà thiết bị IoT có thể sử dụng để kết nối với đám mây, và các loại dữ liệu mà chúng có thể gửi hoặc nhận. Bạn cũng sẽ thực hành với cả hai, thêm điều khiển qua Internet cho đèn ngủ của bạn, chuyển logic điều khiển LED sang mã 'server' chạy cục bộ.

Trong bài học này, chúng ta sẽ tìm hiểu:

* [Giao thức truyền thông](../../../../../1-getting-started/lessons/4-connect-internet)
* [Message Queueing Telemetry Transport (MQTT)](../../../../../1-getting-started/lessons/4-connect-internet)
* [Dữ liệu đo từ xa](../../../../../1-getting-started/lessons/4-connect-internet)
* [Lệnh](../../../../../1-getting-started/lessons/4-connect-internet)

## Giao thức truyền thông

Có một số giao thức truyền thông phổ biến được sử dụng bởi các thiết bị IoT để giao tiếp với Internet. Phổ biến nhất là dựa trên mô hình xuất bản/đăng ký thông qua một loại broker nào đó. Các thiết bị IoT kết nối với broker và xuất bản dữ liệu đo từ xa, đồng thời đăng ký nhận lệnh. Các dịch vụ đám mây cũng kết nối với broker, đăng ký nhận tất cả các tin nhắn đo từ xa và xuất bản lệnh đến các thiết bị cụ thể hoặc nhóm thiết bị.

![Các thiết bị IoT kết nối với broker, xuất bản dữ liệu đo từ xa và đăng ký nhận lệnh. Các dịch vụ đám mây kết nối với broker, đăng ký nhận tất cả dữ liệu đo từ xa và gửi lệnh đến các thiết bị cụ thể.](../../../../../translated_images/vi/pub-sub.7c7ed43fe9fd15d4.webp)

MQTT là giao thức truyền thông phổ biến nhất cho các thiết bị IoT và được đề cập trong bài học này. Các giao thức khác bao gồm AMQP và HTTP/HTTPS.

## Message Queueing Telemetry Transport (MQTT)

[MQTT](http://mqtt.org) là một giao thức nhắn tin nhẹ, tiêu chuẩn mở, có thể gửi tin nhắn giữa các thiết bị. Nó được thiết kế vào năm 1999 để giám sát các đường ống dẫn dầu, trước khi được IBM phát hành dưới dạng tiêu chuẩn mở 15 năm sau đó.

MQTT có một broker duy nhất và nhiều client. Tất cả các client kết nối với broker, và broker định tuyến tin nhắn đến các client liên quan. Tin nhắn được định tuyến bằng cách sử dụng các chủ đề được đặt tên, thay vì gửi trực tiếp đến một client cụ thể. Một client có thể xuất bản lên một chủ đề, và bất kỳ client nào đăng ký chủ đề đó sẽ nhận được tin nhắn.

![Thiết bị IoT xuất bản dữ liệu đo từ xa trên chủ đề /telemetry, và dịch vụ đám mây đăng ký chủ đề đó](../../../../../translated_images/vi/mqtt.cbf7f21d9adc3e17.webp)

✅ Nghiên cứu thêm. Nếu bạn có nhiều thiết bị IoT, làm thế nào để đảm bảo broker MQTT của bạn có thể xử lý tất cả các tin nhắn?

### Kết nối thiết bị IoT của bạn với MQTT

Phần đầu tiên của việc thêm điều khiển qua Internet cho đèn ngủ của bạn là kết nối nó với một broker MQTT.

#### Nhiệm vụ

Kết nối thiết bị của bạn với một broker MQTT.

Trong phần này của bài học, bạn sẽ kết nối đèn ngủ IoT của mình với Internet để cho phép nó được điều khiển từ xa. Sau đó trong bài học này, thiết bị IoT của bạn sẽ gửi một tin nhắn đo từ xa qua MQTT đến một broker MQTT công cộng với mức độ ánh sáng, nơi nó sẽ được nhận bởi một đoạn mã server mà bạn sẽ viết. Đoạn mã này sẽ kiểm tra mức độ ánh sáng và gửi một tin nhắn lệnh trở lại thiết bị, yêu cầu bật hoặc tắt LED.

Một trường hợp sử dụng thực tế cho thiết lập như vậy có thể là thu thập dữ liệu từ nhiều cảm biến ánh sáng trước khi quyết định bật đèn, trong một địa điểm có nhiều đèn, chẳng hạn như một sân vận động. Điều này có thể ngăn đèn được bật nếu chỉ một cảm biến bị che bởi mây hoặc chim, nhưng các cảm biến khác vẫn phát hiện đủ ánh sáng.

✅ Những tình huống nào khác có thể yêu cầu dữ liệu từ nhiều cảm biến được đánh giá trước khi gửi lệnh?

Thay vì xử lý các phức tạp của việc thiết lập một broker MQTT như một phần của bài tập này, bạn có thể sử dụng một server thử nghiệm công cộng chạy [Eclipse Mosquitto](https://www.mosquitto.org), một broker MQTT mã nguồn mở. Broker thử nghiệm này có sẵn công khai tại [test.mosquitto.org](https://test.mosquitto.org), và không yêu cầu thiết lập tài khoản, làm cho nó trở thành một công cụ tuyệt vời để thử nghiệm các client và server MQTT.

> 💁 Broker thử nghiệm này là công cộng và không an toàn. Bất kỳ ai cũng có thể nghe những gì bạn xuất bản, vì vậy nó không nên được sử dụng với bất kỳ dữ liệu nào cần được giữ bí mật.

![Sơ đồ luồng của bài tập cho thấy mức độ ánh sáng được đọc và kiểm tra, và LED được điều khiển](../../../../../translated_images/vi/assignment-1-internet-flow.3256feab5f052fd2.webp)

Thực hiện bước phù hợp dưới đây để kết nối thiết bị của bạn với broker MQTT:

* [Arduino - Wio Terminal](wio-terminal-mqtt.md)
* [Máy tính đơn bảng - Raspberry Pi/Thiết bị IoT ảo](single-board-computer-mqtt.md)

### Tìm hiểu sâu hơn về MQTT

Các chủ đề có thể có cấu trúc phân cấp, và các client có thể đăng ký các cấp độ khác nhau của cấu trúc phân cấp bằng cách sử dụng ký tự đại diện. Ví dụ, bạn có thể gửi tin nhắn đo từ xa nhiệt độ đến chủ đề `/telemetry/temperature` và tin nhắn độ ẩm đến chủ đề `/telemetry/humidity`, sau đó trong ứng dụng đám mây của bạn đăng ký chủ đề `/telemetry/*` để nhận cả tin nhắn đo từ xa nhiệt độ và độ ẩm.

Tin nhắn có thể được gửi với chất lượng dịch vụ (QoS), xác định mức độ đảm bảo của việc nhận tin nhắn.

* Tối đa một lần - tin nhắn chỉ được gửi một lần và client và broker không thực hiện thêm bước nào để xác nhận việc giao tin nhắn (gửi và quên).
* Ít nhất một lần - tin nhắn được gửi lại bởi người gửi nhiều lần cho đến khi nhận được xác nhận (giao tin nhắn được xác nhận).
* Chính xác một lần - người gửi và người nhận thực hiện một quy trình bắt tay hai cấp để đảm bảo chỉ một bản sao của tin nhắn được nhận (giao tin nhắn được đảm bảo).

✅ Những tình huống nào có thể yêu cầu tin nhắn được đảm bảo giao nhận thay vì tin nhắn gửi và quên?

Mặc dù tên gọi là Message Queueing (MQTT), nó thực sự không hỗ trợ hàng đợi tin nhắn. Điều này có nghĩa là nếu một client ngắt kết nối, sau đó kết nối lại, nó sẽ không nhận được các tin nhắn được gửi trong thời gian ngắt kết nối, ngoại trừ những tin nhắn mà nó đã bắt đầu xử lý bằng quy trình QoS. Tin nhắn có thể được đặt cờ lưu giữ. Nếu cờ này được đặt, broker MQTT sẽ lưu trữ tin nhắn cuối cùng được gửi trên một chủ đề với cờ này, và gửi tin nhắn này đến bất kỳ client nào sau đó đăng ký chủ đề đó. Bằng cách này, các client sẽ luôn nhận được tin nhắn mới nhất.

MQTT cũng hỗ trợ chức năng giữ kết nối để kiểm tra xem kết nối có còn hoạt động trong các khoảng thời gian dài giữa các tin nhắn hay không.

> 🦟 [Mosquitto từ Eclipse Foundation](https://mosquitto.org) có một broker MQTT miễn phí mà bạn có thể tự chạy để thử nghiệm với MQTT, cùng với một broker MQTT công cộng mà bạn có thể sử dụng để thử nghiệm mã của mình, được lưu trữ tại [test.mosquitto.org](https://test.mosquitto.org).

Kết nối MQTT có thể là công cộng và mở, hoặc được mã hóa và bảo mật bằng tên người dùng và mật khẩu, hoặc chứng chỉ.

> 💁 MQTT giao tiếp qua TCP/IP, cùng giao thức mạng cơ bản như HTTP, nhưng trên một cổng khác. Bạn cũng có thể sử dụng MQTT qua websockets để giao tiếp với các ứng dụng web chạy trong trình duyệt, hoặc trong các tình huống mà tường lửa hoặc các quy tắc mạng khác chặn kết nối MQTT tiêu chuẩn.

## Dữ liệu đo từ xa

Từ "telemetry" bắt nguồn từ gốc Hy Lạp có nghĩa là đo lường từ xa. Dữ liệu đo từ xa là hành động thu thập dữ liệu từ các cảm biến và gửi nó lên đám mây.

> 💁 Một trong những thiết bị đo từ xa đầu tiên được phát minh ở Pháp vào năm 1874 và gửi dữ liệu thời tiết và độ sâu tuyết theo thời gian thực từ Mont Blanc đến Paris. Nó sử dụng dây vật lý vì các công nghệ không dây chưa có vào thời điểm đó.

Hãy nhìn lại ví dụ về bộ điều nhiệt thông minh từ Bài học 1.

![Bộ điều nhiệt kết nối Internet sử dụng nhiều cảm biến trong phòng](../../../../../translated_images/vi/telemetry.21e5d8b97649d2eb.webp)

Bộ điều nhiệt có các cảm biến nhiệt độ để thu thập dữ liệu đo từ xa. Nó có thể có một cảm biến nhiệt độ tích hợp, và nó có thể kết nối với nhiều cảm biến nhiệt độ bên ngoài qua một giao thức không dây như [Bluetooth Low Energy](https://wikipedia.org/wiki/Bluetooth_Low_Energy) (BLE).

Một ví dụ về dữ liệu đo từ xa mà nó có thể gửi là:

| Tên | Giá trị | Mô tả |
| ---- | ----- | ----------- |
| `thermostat_temperature` | 18°C | Nhiệt độ được đo bởi cảm biến nhiệt độ tích hợp của bộ điều nhiệt |
| `livingroom_temperature` | 19°C | Nhiệt độ được đo bởi một cảm biến nhiệt độ từ xa đã được đặt tên là `livingroom` để xác định phòng mà nó đang ở |
| `bedroom_temperature` | 21°C | Nhiệt độ được đo bởi một cảm biến nhiệt độ từ xa đã được đặt tên là `bedroom` để xác định phòng mà nó đang ở |

Dịch vụ đám mây sau đó có thể sử dụng dữ liệu đo từ xa này để đưa ra quyết định về việc gửi lệnh để điều khiển hệ thống sưởi.

### Gửi dữ liệu đo từ xa từ thiết bị IoT của bạn

Phần tiếp theo trong việc thêm điều khiển qua Internet cho đèn ngủ của bạn là gửi dữ liệu đo từ xa về mức độ ánh sáng đến broker MQTT trên một chủ đề đo từ xa.

#### Nhiệm vụ - gửi dữ liệu đo từ xa từ thiết bị IoT của bạn

Gửi dữ liệu đo từ xa về mức độ ánh sáng đến broker MQTT.

Dữ liệu được gửi được mã hóa dưới dạng JSON - viết tắt của JavaScript Object Notation, một tiêu chuẩn để mã hóa dữ liệu dưới dạng văn bản sử dụng các cặp khóa/giá trị.

✅ Nếu bạn chưa từng gặp JSON trước đây, bạn có thể tìm hiểu thêm về nó trong [tài liệu JSON.org](https://www.json.org/).

Thực hiện bước phù hợp dưới đây để gửi dữ liệu đo từ xa từ thiết bị của bạn đến broker MQTT:

* [Arduino - Wio Terminal](wio-terminal-telemetry.md)
* [Máy tính đơn bảng - Raspberry Pi/Thiết bị IoT ảo](single-board-computer-telemetry.md)

### Nhận dữ liệu đo từ xa từ broker MQTT

Không có ý nghĩa gì khi gửi dữ liệu đo từ xa nếu không có gì ở đầu bên kia để lắng nghe nó. Dữ liệu đo từ xa về mức độ ánh sáng cần một thứ gì đó lắng nghe để xử lý dữ liệu. Mã 'server' này là loại mã mà bạn sẽ triển khai lên một dịch vụ đám mây như một phần của ứng dụng IoT lớn hơn, nhưng ở đây bạn sẽ chạy mã này cục bộ trên máy tính của mình (hoặc trên Pi nếu bạn đang mã hóa trực tiếp trên đó). Mã server bao gồm một ứng dụng Python lắng nghe các tin nhắn đo từ xa qua MQTT với mức độ ánh sáng. Sau đó trong bài học này, bạn sẽ làm cho nó trả lời bằng một tin nhắn lệnh với hướng dẫn bật hoặc tắt LED.

✅ Nghiên cứu thêm: Điều gì xảy ra với các tin nhắn MQTT nếu không có người lắng nghe?

#### Cài đặt Python và VS Code

Nếu bạn chưa cài đặt Python và VS Code cục bộ, bạn sẽ cần cài đặt cả hai để viết mã server. Nếu bạn đang sử dụng thiết bị IoT ảo, hoặc đang làm việc trên Raspberry Pi của mình, bạn có thể bỏ qua bước này vì bạn đã cài đặt và cấu hình sẵn.

##### Nhiệm vụ - cài đặt Python và VS Code

Cài đặt Python và VS Code.

1. Cài đặt Python. Tham khảo [trang tải xuống Python](https://www.python.org/downloads/) để biết hướng dẫn cài đặt phiên bản mới nhất của Python.

1. Cài đặt Visual Studio Code (VS Code). Đây là trình soạn thảo bạn sẽ sử dụng để viết mã thiết bị ảo của mình bằng Python. Tham khảo [tài liệu VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) để biết hướng dẫn cài đặt VS Code.
💁 Bạn có thể tự do sử dụng bất kỳ IDE hoặc trình soạn thảo Python nào mà bạn ưa thích cho các bài học này, nhưng các bài học sẽ đưa ra hướng dẫn dựa trên việc sử dụng VS Code.
1. Cài đặt tiện ích mở rộng Pylance cho VS Code. Đây là một tiện ích mở rộng dành cho VS Code cung cấp hỗ trợ ngôn ngữ Python. Tham khảo [tài liệu tiện ích Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) để biết hướng dẫn cài đặt tiện ích này trong VS Code.

#### Cấu hình môi trường ảo Python

Một trong những tính năng mạnh mẽ của Python là khả năng cài đặt [gói pip](https://pypi.org) - đây là các gói mã được viết bởi người khác và được xuất bản lên Internet. Bạn có thể cài đặt một gói pip trên máy tính của mình chỉ với một lệnh, sau đó sử dụng gói đó trong mã của bạn. Bạn sẽ sử dụng pip để cài đặt một gói để giao tiếp qua MQTT.

Theo mặc định, khi bạn cài đặt một gói, nó sẽ có sẵn ở mọi nơi trên máy tính của bạn, và điều này có thể dẫn đến các vấn đề về phiên bản gói - chẳng hạn như một ứng dụng phụ thuộc vào một phiên bản của gói có thể bị lỗi khi bạn cài đặt phiên bản mới cho một ứng dụng khác. Để giải quyết vấn đề này, bạn có thể sử dụng [môi trường ảo Python](https://docs.python.org/3/library/venv.html), về cơ bản là một bản sao của Python trong một thư mục chuyên dụng, và khi bạn cài đặt các gói pip, chúng chỉ được cài đặt trong thư mục đó.

##### Nhiệm vụ - cấu hình môi trường ảo Python

Cấu hình môi trường ảo Python và cài đặt các gói pip MQTT.

1. Từ terminal hoặc dòng lệnh của bạn, chạy lệnh sau tại một vị trí tùy chọn để tạo và chuyển đến một thư mục mới:

    ```sh
    mkdir nightlight-server
    cd nightlight-server
    ```

1. Bây giờ chạy lệnh sau để tạo môi trường ảo trong thư mục `.venv`:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Bạn cần gọi rõ ràng `python3` để tạo môi trường ảo trong trường hợp bạn có Python 2 được cài đặt cùng với Python 3 (phiên bản mới nhất). Nếu bạn có Python 2 được cài đặt thì việc gọi `python` sẽ sử dụng Python 2 thay vì Python 3.

1. Kích hoạt môi trường ảo:

    * Trên Windows:
        * Nếu bạn đang sử dụng Command Prompt hoặc Command Prompt thông qua Windows Terminal, chạy:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Nếu bạn đang sử dụng PowerShell, chạy:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * Trên macOS hoặc Linux, chạy:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Các lệnh này nên được chạy từ cùng vị trí mà bạn đã chạy lệnh để tạo môi trường ảo. Bạn sẽ không bao giờ cần phải điều hướng vào thư mục `.venv`, bạn nên luôn chạy lệnh kích hoạt và bất kỳ lệnh nào để cài đặt gói hoặc chạy mã từ thư mục bạn đã ở khi tạo môi trường ảo.

1. Sau khi môi trường ảo được kích hoạt, lệnh `python` mặc định sẽ chạy phiên bản Python được sử dụng để tạo môi trường ảo. Chạy lệnh sau để kiểm tra phiên bản:

    ```sh
    python --version
    ```

    Kết quả đầu ra sẽ tương tự như sau:

    ```output
    (.venv) ➜  nightlight-server python --version
    Python 3.9.1
    ```

    > 💁 Phiên bản Python của bạn có thể khác - miễn là nó là phiên bản 3.6 hoặc cao hơn thì bạn ổn. Nếu không, hãy xóa thư mục này, cài đặt phiên bản Python mới hơn và thử lại.

1. Chạy các lệnh sau để cài đặt gói pip cho [Paho-MQTT](https://pypi.org/project/paho-mqtt/), một thư viện MQTT phổ biến.

    ```sh
    pip install paho-mqtt
    ```

    Gói pip này sẽ chỉ được cài đặt trong môi trường ảo và sẽ không có sẵn bên ngoài môi trường này.

#### Viết mã máy chủ

Bây giờ bạn có thể viết mã máy chủ bằng Python.

##### Nhiệm vụ - viết mã máy chủ

Viết mã máy chủ.

1. Từ terminal hoặc dòng lệnh của bạn, chạy lệnh sau bên trong môi trường ảo để tạo một tệp Python có tên `app.py`:

    * Trên Windows chạy:

        ```cmd
        type nul > app.py
        ```

    * Trên macOS hoặc Linux, chạy:

        ```cmd
        touch app.py
        ```

1. Mở thư mục hiện tại trong VS Code:

    ```sh
    code .
    ```

1. Khi VS Code khởi chạy, nó sẽ kích hoạt môi trường ảo Python. Điều này sẽ được hiển thị ở thanh trạng thái dưới cùng:

    ![VS Code hiển thị môi trường ảo đã chọn](../../../../../translated_images/vi/vscode-virtual-env.8ba42e04c3d533cf.webp)

1. Nếu Terminal của VS Code đã chạy khi VS Code khởi động, nó sẽ không có môi trường ảo được kích hoạt trong đó. Cách dễ nhất là tắt terminal bằng nút **Kill the active terminal instance**:

    ![Nút Kill the active terminal instance của VS Code](../../../../../translated_images/vi/vscode-kill-terminal.1cc4de7c6f25ee08.webp)

1. Khởi chạy một Terminal mới của VS Code bằng cách chọn *Terminal -> New Terminal*, hoặc nhấn `` CTRL+` ``. Terminal mới sẽ tải môi trường ảo, với lệnh kích hoạt xuất hiện trong terminal. Tên của môi trường ảo (`.venv`) cũng sẽ xuất hiện trong prompt:

    ```output
    ➜  nightlight-server source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Mở tệp `app.py` từ trình khám phá của VS Code và thêm mã sau:

    ```python
    import json
    import time
    
    import paho.mqtt.client as mqtt
    
    id = '<ID>'
    
    client_telemetry_topic = id + '/telemetry'
    client_name = id + 'nightlight_server'
    
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()
    
    def handle_telemetry(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
    mqtt_client.subscribe(client_telemetry_topic)
    mqtt_client.on_message = handle_telemetry
    
    while True:
        time.sleep(2)
    ```

    Thay thế `<ID>` ở dòng 6 bằng ID duy nhất bạn đã sử dụng khi tạo mã thiết bị của mình.

    ⚠️ ID này **phải** giống với ID mà bạn đã sử dụng trên thiết bị của mình, nếu không mã máy chủ sẽ không đăng ký hoặc xuất bản vào đúng chủ đề.

    Mã này tạo một client MQTT với tên duy nhất và kết nối với broker *test.mosquitto.org*. Sau đó, nó bắt đầu một vòng xử lý chạy trên một luồng nền lắng nghe các tin nhắn trên bất kỳ chủ đề nào đã đăng ký.

    Client sau đó đăng ký nhận tin nhắn trên chủ đề telemetry và định nghĩa một hàm được gọi khi một tin nhắn được nhận. Khi một tin nhắn telemetry được nhận, hàm `handle_telemetry` sẽ được gọi, in tin nhắn nhận được ra console.

    Cuối cùng, một vòng lặp vô hạn giữ cho ứng dụng chạy. Client MQTT đang lắng nghe tin nhắn trên một luồng nền và chạy suốt thời gian ứng dụng chính đang chạy.

1. Từ terminal của VS Code, chạy lệnh sau để chạy ứng dụng Python của bạn:

    ```sh
    python app.py
    ```

    Ứng dụng sẽ bắt đầu lắng nghe các tin nhắn từ thiết bị IoT.

1. Đảm bảo thiết bị của bạn đang chạy và gửi các tin nhắn telemetry. Điều chỉnh mức ánh sáng được phát hiện bởi thiết bị vật lý hoặc ảo của bạn. Các tin nhắn nhận được sẽ được in ra terminal.

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Message received: {'light': 400}
    ```

    Tệp app.py trong môi trường ảo nightlight phải đang chạy để tệp app.py trong môi trường ảo nightlight-server nhận được các tin nhắn được gửi.

> 💁 Bạn có thể tìm thấy mã này trong thư mục [code-server/server](../../../../../1-getting-started/lessons/4-connect-internet/code-server/server).

### Tần suất gửi telemetry?

Một cân nhắc quan trọng với telemetry là tần suất đo lường và gửi dữ liệu? Câu trả lời là - tùy thuộc. Nếu bạn đo thường xuyên, bạn có thể phản ứng nhanh hơn với các thay đổi trong đo lường, nhưng bạn sử dụng nhiều năng lượng hơn, nhiều băng thông hơn, tạo ra nhiều dữ liệu hơn và cần nhiều tài nguyên đám mây hơn để xử lý.

Đối với một bộ điều nhiệt, đo lường mỗi vài phút có lẽ là đủ vì nhiệt độ không thay đổi thường xuyên. Nếu bạn chỉ đo một lần mỗi ngày thì bạn có thể kết thúc việc làm nóng nhà cho nhiệt độ ban đêm vào giữa ngày nắng, trong khi nếu bạn đo mỗi giây, bạn sẽ có hàng ngàn đo lường nhiệt độ trùng lặp không cần thiết, làm giảm tốc độ và băng thông Internet của người dùng (một vấn đề đối với những người có gói băng thông hạn chế), sử dụng nhiều năng lượng hơn, điều này có thể là vấn đề đối với các thiết bị chạy bằng pin như cảm biến từ xa, và tăng chi phí tài nguyên điện toán đám mây của nhà cung cấp để xử lý và lưu trữ chúng.

Nếu bạn đang giám sát dữ liệu xung quanh một máy móc trong nhà máy mà nếu nó hỏng có thể gây ra thiệt hại nghiêm trọng và mất hàng triệu đô la doanh thu, thì đo lường nhiều lần mỗi giây có thể là cần thiết. Tốt hơn là lãng phí băng thông hơn là bỏ lỡ telemetry cho thấy rằng máy cần được dừng và sửa chữa trước khi nó hỏng.

> 💁 Trong tình huống này, bạn có thể cân nhắc sử dụng một thiết bị edge để xử lý telemetry trước nhằm giảm sự phụ thuộc vào Internet.

### Mất kết nối

Kết nối Internet có thể không ổn định, với các sự cố thường xuyên. Thiết bị IoT nên làm gì trong những trường hợp này - liệu nó nên mất dữ liệu hay lưu trữ dữ liệu cho đến khi kết nối được khôi phục? Một lần nữa, câu trả lời là tùy thuộc.

Đối với một bộ điều nhiệt, dữ liệu có thể bị mất ngay khi một đo lường nhiệt độ mới được thực hiện. Hệ thống sưởi không quan tâm rằng 20 phút trước nhiệt độ là 20.5°C nếu nhiệt độ hiện tại là 19°C, nhiệt độ hiện tại mới quyết định liệu hệ thống sưởi có nên bật hay tắt.

Đối với máy móc, bạn có thể muốn giữ lại dữ liệu, đặc biệt nếu nó được sử dụng để tìm kiếm xu hướng. Có các mô hình học máy có thể phát hiện các bất thường trong luồng dữ liệu bằng cách xem xét dữ liệu từ một khoảng thời gian xác định (chẳng hạn như giờ trước) và phát hiện dữ liệu bất thường. Điều này thường được sử dụng để bảo trì dự đoán, tìm kiếm các dấu hiệu cho thấy điều gì đó có thể hỏng sớm để bạn có thể sửa chữa hoặc thay thế trước khi điều đó xảy ra. Bạn có thể muốn mọi bit telemetry cho một máy được gửi để nó có thể được xử lý để phát hiện bất thường, vì vậy một khi thiết bị IoT có thể kết nối lại, nó sẽ gửi tất cả telemetry được tạo ra trong thời gian mất kết nối Internet.

Các nhà thiết kế thiết bị IoT cũng nên cân nhắc liệu thiết bị IoT có thể được sử dụng trong thời gian mất kết nối Internet hoặc mất tín hiệu do vị trí hay không. Một bộ điều nhiệt thông minh nên có khả năng đưa ra một số quyết định hạn chế để kiểm soát hệ thống sưởi nếu nó không thể gửi telemetry lên đám mây do sự cố.

[![Chiếc Ferrari này bị hỏng vì ai đó cố gắng nâng cấp nó dưới lòng đất nơi không có tín hiệu di động](../../../../../translated_images/vi/bricked-car.dc38f8efadc6c59d.webp)](https://twitter.com/internetofshit/status/1315736960082808832)

Để MQTT xử lý mất kết nối, mã thiết bị và máy chủ sẽ cần chịu trách nhiệm đảm bảo việc gửi tin nhắn nếu cần thiết, ví dụ bằng cách yêu cầu tất cả các tin nhắn gửi đi phải được trả lời bằng các tin nhắn bổ sung trên một chủ đề trả lời, và nếu không thì chúng được xếp hàng thủ công để phát lại sau.

## Lệnh

Lệnh là các tin nhắn được gửi từ đám mây đến thiết bị, yêu cầu nó thực hiện một hành động nào đó. Hầu hết thời gian điều này liên quan đến việc cung cấp một số loại đầu ra thông qua bộ truyền động, nhưng nó cũng có thể là một yêu cầu cho chính thiết bị, chẳng hạn như khởi động lại hoặc thu thập thêm telemetry và trả lại nó như một phản hồi cho lệnh.

![Một bộ điều nhiệt kết nối Internet nhận lệnh bật hệ thống sưởi](../../../../../translated_images/vi/commands.d6c06bbbb3a02cce.webp)

Một bộ điều nhiệt có thể nhận lệnh từ đám mây để bật hệ thống sưởi. Dựa trên dữ liệu telemetry từ tất cả các cảm biến, nếu dịch vụ đám mây đã quyết định rằng hệ thống sưởi nên bật, thì nó sẽ gửi lệnh tương ứng.

### Gửi lệnh đến MQTT broker

Bước tiếp theo cho đèn ngủ điều khiển qua Internet của chúng ta là để mã máy chủ gửi một lệnh trở lại thiết bị IoT để điều khiển ánh sáng dựa trên mức ánh sáng mà nó cảm nhận được.

1. Mở mã máy chủ trong VS Code

1. Thêm dòng sau sau khai báo của `client_telemetry_topic` để xác định chủ đề nào để gửi lệnh:

    ```python
    server_command_topic = id + '/commands'
    ```

1. Thêm mã sau vào cuối hàm `handle_telemetry`:

    ```python
    command = { 'led_on' : payload['light'] < 300 }
    print("Sending message:", command)
    
    client.publish(server_command_topic, json.dumps(command))
    ```

    Điều này gửi một tin nhắn JSON đến chủ đề lệnh với giá trị của `led_on` được đặt thành true hoặc false tùy thuộc vào việc ánh sáng có nhỏ hơn 300 hay không. Nếu ánh sáng nhỏ hơn 300, true được gửi để yêu cầu thiết bị bật LED.

1. Chạy mã như trước

1. Điều chỉnh mức ánh sáng được phát hiện bởi thiết bị vật lý hoặc ảo của bạn. Các tin nhắn nhận được và lệnh được gửi sẽ được ghi vào terminal:

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Sending message: {'led_on': True}
    Message received: {'light': 400}
    Sending message: {'led_on': False}
    ```

> 💁 Telemetry và lệnh đang được gửi trên một chủ đề duy nhất. Điều này có nghĩa là telemetry từ nhiều thiết bị sẽ xuất hiện trên cùng một chủ đề telemetry, và lệnh đến nhiều thiết bị sẽ xuất hiện trên cùng một chủ đề lệnh. Nếu bạn muốn gửi một lệnh đến một thiết bị cụ thể, bạn có thể sử dụng nhiều chủ đề, được đặt tên với một ID thiết bị duy nhất, chẳng hạn như `/commands/device1`, `/commands/device2`. Bằng cách đó, một thiết bị có thể lắng nghe các tin nhắn chỉ dành cho thiết bị đó.

> 💁 Bạn có thể tìm thấy mã này trong thư mục [code-commands/server](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/server).

### Xử lý lệnh trên thiết bị IoT

Bây giờ các lệnh đang được gửi từ máy chủ, bạn có thể thêm mã vào thiết bị IoT để xử lý chúng và điều khiển LED.

Thực hiện bước phù hợp dưới đây để lắng nghe lệnh từ MQTT broker:

* [Arduino - Wio Terminal](wio-terminal-commands.md)
* [Máy tính đơn bảng - Raspberry Pi/Thiết bị IoT ảo](single-board-computer-commands.md)

Khi mã này được viết và chạy, hãy thử nghiệm với việc thay đổi mức ánh sáng. Quan sát đầu ra từ máy chủ và thiết bị, và quan sát LED khi bạn thay đổi mức ánh sáng.

### Mất kết nối

Dịch vụ đám mây nên làm gì nếu nó cần gửi một lệnh đến thiết bị IoT đang ngoại tuyến? Một lần nữa, câu trả lời là tùy thuộc.

Nếu lệnh mới nhất ghi đè lên lệnh trước đó thì các lệnh trước đó có thể bị bỏ qua. Nếu dịch vụ đám mây gửi một lệnh để bật hệ thống sưởi, sau đó gửi một lệnh để tắt, thì lệnh bật có thể bị bỏ qua và không được gửi lại.

Nếu các lệnh cần được xử lý theo thứ tự, chẳng hạn như di chuyển cánh tay robot lên, sau đó đóng bộ kẹp, thì chúng cần được gửi theo thứ tự một khi kết nối được khôi phục.

✅ Làm thế nào mã thiết bị hoặc máy chủ có thể đảm bảo các lệnh luôn được gửi và xử lý theo thứ tự qua MQTT nếu cần thiết?

---

## 🚀 Thử thách

Thử thách trong ba bài học trước là liệt kê càng nhiều thiết bị IoT càng tốt mà bạn có trong nhà, trường học hoặc nơi làm việc và quyết định xem chúng được xây dựng dựa trên vi điều khiển hay máy tính đơn bảng, hoặc thậm chí là sự kết hợp của cả hai, và nghĩ về các cảm biến và bộ truyền động mà chúng đang sử dụng.
Hãy nghĩ về những thiết bị này, chúng có thể đang gửi hoặc nhận những thông điệp gì. Chúng gửi những dữ liệu nào? Chúng có thể nhận những thông điệp hoặc lệnh nào? Bạn có nghĩ rằng chúng an toàn không?

## Câu hỏi sau bài giảng

[Câu hỏi sau bài giảng](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/8)

## Ôn tập & Tự học

Đọc thêm về MQTT trên [trang Wikipedia về MQTT](https://wikipedia.org/wiki/MQTT).

Hãy thử chạy một MQTT broker bằng cách sử dụng [Mosquitto](https://www.mosquitto.org) và kết nối với nó từ thiết bị IoT và mã máy chủ của bạn.

> 💁 Mẹo - theo mặc định, Mosquitto không cho phép kết nối ẩn danh (tức là kết nối mà không cần tên người dùng và mật khẩu), và không cho phép kết nối từ bên ngoài máy tính mà nó đang chạy.
> Bạn có thể khắc phục điều này bằng một [tệp cấu hình `mosquitto.conf`](https://www.mosquitto.org/man/mosquitto-conf-5.html) với nội dung sau:
>
> ```sh
> listener 1883 0.0.0.0
> allow_anonymous true
> ```

## Bài tập

[So sánh và đối chiếu MQTT với các giao thức truyền thông khác](assignment.md)

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.