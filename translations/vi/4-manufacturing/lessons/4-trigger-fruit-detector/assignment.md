<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1a85e50c33c38dcd2cde2a97d132f248",
  "translation_date": "2025-08-27T22:47:53+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/assignment.md",
  "language_code": "vi"
}
-->
# Xây dựng máy phát hiện chất lượng trái cây

## Hướng dẫn

Hãy xây dựng máy phát hiện chất lượng trái cây!

Áp dụng tất cả những gì bạn đã học được cho đến nay để tạo ra nguyên mẫu máy phát hiện chất lượng trái cây. Kích hoạt phân loại hình ảnh dựa trên khoảng cách bằng cách sử dụng mô hình AI chạy trên thiết bị biên, lưu trữ kết quả phân loại vào bộ nhớ, và điều khiển đèn LED dựa trên độ chín của trái cây.

Bạn nên có khả năng ghép nối các phần này lại với nhau bằng cách sử dụng mã mà bạn đã viết trong tất cả các bài học trước.

## Tiêu chí đánh giá

| Tiêu chí | Xuất sắc | Đạt yêu cầu | Cần cải thiện |
| -------- | --------- | ----------- | ------------- |
| Cấu hình tất cả các dịch vụ | Có thể thiết lập IoT Hub, ứng dụng Azure Functions và Azure Storage | Có thể thiết lập IoT Hub, nhưng không thiết lập được ứng dụng Azure Functions hoặc Azure Storage | Không thể thiết lập bất kỳ dịch vụ IoT nào qua internet |
| Giám sát khoảng cách và gửi dữ liệu đến IoT Hub nếu một vật thể ở gần hơn khoảng cách được định trước, và kích hoạt camera thông qua một lệnh | Có thể đo khoảng cách và gửi thông báo đến IoT Hub khi một vật thể đủ gần, và gửi lệnh để kích hoạt camera | Có thể đo khoảng cách và gửi dữ liệu đến IoT Hub, nhưng không thể gửi lệnh đến camera | Không thể đo khoảng cách và gửi thông báo đến IoT Hub, hoặc kích hoạt lệnh |
| Chụp hình ảnh, phân loại và gửi kết quả đến IoT Hub | Có thể chụp hình ảnh, phân loại bằng thiết bị biên và gửi kết quả đến IoT Hub | Có thể phân loại hình ảnh nhưng không sử dụng thiết bị biên, hoặc không thể gửi kết quả đến IoT Hub | Không thể phân loại hình ảnh |
| Bật hoặc tắt đèn LED tùy thuộc vào kết quả phân loại bằng lệnh gửi đến thiết bị | Có thể bật đèn LED thông qua lệnh nếu trái cây chưa chín | Có thể gửi lệnh đến thiết bị nhưng không điều khiển được đèn LED | Không thể gửi lệnh để điều khiển đèn LED |

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.