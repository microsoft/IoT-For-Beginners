<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "022e21f8629b721424c1de25195fff67",
  "translation_date": "2025-08-27T20:58:00+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/assignment.md",
  "language_code": "vi"
}
-->
# Phản hồi kết quả phân loại

## Hướng dẫn

Thiết bị của bạn đã phân loại hình ảnh và có các giá trị dự đoán. Thiết bị của bạn có thể sử dụng thông tin này để thực hiện một hành động nào đó - chẳng hạn gửi dữ liệu đến IoT Hub để các hệ thống khác xử lý, hoặc điều khiển một thiết bị như đèn LED để sáng lên khi trái cây chưa chín.

Thêm mã vào thiết bị của bạn để phản hồi theo cách bạn chọn - có thể gửi dữ liệu đến IoT Hub, điều khiển một thiết bị, hoặc kết hợp cả hai bằng cách gửi dữ liệu đến IoT Hub với một đoạn mã serverless để xác định trái cây đã chín hay chưa và gửi lại lệnh để điều khiển thiết bị.

## Tiêu chí đánh giá

| Tiêu chí | Xuất sắc | Đạt yêu cầu | Cần cải thiện |
| -------- | --------- | ----------- | ------------- |
| Phản hồi dự đoán | Có thể triển khai phản hồi với dự đoán hoạt động nhất quán với các giá trị dự đoán tương tự. | Có thể triển khai phản hồi không phụ thuộc vào dự đoán, chẳng hạn chỉ gửi dữ liệu thô đến IoT Hub. | Không thể lập trình thiết bị để phản hồi dự đoán. |

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm về bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.