<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2025-08-28T01:24:00+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "vi"
}
-->
# Thêm điều khiển rơ-le thủ công

## Hướng dẫn

Code serverless có thể được kích hoạt bởi nhiều yếu tố khác nhau, bao gồm các yêu cầu HTTP. Bạn có thể sử dụng các HTTP trigger để thêm chức năng điều khiển thủ công cho rơ-le, cho phép ai đó bật hoặc tắt rơ-le thông qua một yêu cầu web.

Trong bài tập này, bạn cần thêm hai HTTP trigger vào Functions App của mình để bật và tắt rơ-le, sử dụng lại những gì bạn đã học từ bài học này để gửi lệnh đến thiết bị.

Một số gợi ý:

* Bạn có thể thêm một HTTP trigger vào Functions App hiện có của mình bằng lệnh sau:

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    Thay thế `<trigger name>` bằng tên cho HTTP trigger của bạn. Sử dụng tên như `relay_on` và `relay_off`.

* HTTP trigger có thể có kiểm soát truy cập. Theo mặc định, chúng yêu cầu một API key cụ thể của function được truyền cùng với URL để chạy. Trong bài tập này, bạn có thể loại bỏ hạn chế này để bất kỳ ai cũng có thể chạy function. Để làm điều này, hãy cập nhật cài đặt `authLevel` trong tệp `function.json` cho các HTTP trigger thành:

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 Bạn có thể đọc thêm về kiểm soát truy cập này trong [tài liệu về Function access keys](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys).

* HTTP trigger mặc định hỗ trợ các yêu cầu GET và POST. Điều này có nghĩa là bạn có thể gọi chúng bằng trình duyệt web - trình duyệt web thực hiện các yêu cầu GET.

    Khi bạn chạy Functions App của mình cục bộ, bạn sẽ thấy URL của trigger:

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    Dán URL vào trình duyệt của bạn và nhấn `return`, hoặc `Ctrl+click` (`Cmd+click` trên macOS) vào liên kết trong cửa sổ terminal của VS Code để mở nó trong trình duyệt mặc định của bạn. Điều này sẽ chạy trigger.

    > 💁 Lưu ý rằng URL có `/api` trong đó - HTTP trigger mặc định nằm trong subdomain `api`.

* Khi bạn triển khai Functions App, URL của HTTP trigger sẽ là:

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    Trong đó `<functions app name>` là tên của Functions App của bạn, và `<trigger name>` là tên của trigger.

## Tiêu chí đánh giá

| Tiêu chí | Xuất sắc | Đạt yêu cầu | Cần cải thiện |
| -------- | --------- | ----------- | ------------- |
| Tạo HTTP trigger | Tạo 2 trigger để bật và tắt rơ-le, với tên phù hợp | Tạo một trigger với tên phù hợp | Không thể tạo bất kỳ trigger nào |
| Điều khiển rơ-le từ HTTP trigger | Có thể kết nối cả hai trigger với IoT Hub và điều khiển rơ-le một cách phù hợp | Có thể kết nối một trigger với IoT Hub và điều khiển rơ-le một cách phù hợp | Không thể kết nối các trigger với IoT Hub |

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.