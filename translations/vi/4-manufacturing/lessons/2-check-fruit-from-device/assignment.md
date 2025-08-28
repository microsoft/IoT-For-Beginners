<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "022e21f8629b721424c1de25195fff67",
  "translation_date": "2025-08-27T23:04:47+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/assignment.md",
  "language_code": "vi"
}
-->
# Phản hồi kết quả phân loại

## Hướng dẫn

Thiết bị của bạn đã phân loại hình ảnh và có các giá trị cho dự đoán. Thiết bị của bạn có thể sử dụng thông tin này để thực hiện một hành động nào đó - nó có thể gửi dữ liệu đến IoT Hub để được xử lý bởi các hệ thống khác, hoặc nó có thể điều khiển một bộ truyền động như đèn LED để sáng lên khi trái cây chưa chín.

Thêm mã vào thiết bị của bạn để phản hồi theo cách bạn chọn - hoặc gửi dữ liệu đến IoT Hub, điều khiển một bộ truyền động, hoặc kết hợp cả hai và gửi dữ liệu đến IoT Hub với một đoạn mã không máy chủ để xác định xem trái cây đã chín hay chưa và gửi lại lệnh để điều khiển bộ truyền động.

## Tiêu chí đánh giá

| Tiêu chí | Xuất sắc | Đạt yêu cầu | Cần cải thiện |
| -------- | --------- | ----------- | ------------- |
| Phản hồi dự đoán | Có thể triển khai phản hồi với dự đoán hoạt động ổn định với các giá trị dự đoán giống nhau. | Có thể triển khai phản hồi không phụ thuộc vào dự đoán, chẳng hạn như chỉ gửi dữ liệu thô đến IoT Hub. | Không thể lập trình thiết bị để phản hồi dự đoán. |

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.