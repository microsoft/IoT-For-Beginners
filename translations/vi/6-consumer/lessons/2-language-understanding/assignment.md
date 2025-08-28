<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a7262a0c48dfacdfe1ff91b20bf16fd",
  "translation_date": "2025-08-27T23:12:48+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/assignment.md",
  "language_code": "vi"
}
-->
# Hủy hẹn giờ

## Hướng dẫn

Trong bài học này, bạn đã huấn luyện một mô hình để hiểu cách đặt hẹn giờ. Một tính năng hữu ích khác là hủy hẹn giờ - có thể bánh mì của bạn đã chín và có thể lấy ra khỏi lò trước khi hẹn giờ kết thúc.

Thêm một ý định mới vào ứng dụng LUIS của bạn để hủy hẹn giờ. Ý định này không cần bất kỳ thực thể nào, nhưng sẽ cần một số câu ví dụ. Xử lý điều này trong mã serverless của bạn nếu đây là ý định hàng đầu, ghi lại rằng ý định đã được nhận diện và trả về một phản hồi phù hợp.

## Tiêu chí đánh giá

| Tiêu chí | Xuất sắc | Đạt yêu cầu | Cần cải thiện |
| -------- | --------- | ----------- | ------------- |
| Thêm ý định hủy hẹn giờ vào ứng dụng LUIS | Có thể thêm ý định và huấn luyện mô hình | Có thể thêm ý định nhưng không huấn luyện được mô hình | Không thể thêm ý định và huấn luyện mô hình |
| Xử lý ý định trong ứng dụng serverless | Có thể nhận diện ý định là ý định hàng đầu và ghi lại | Có thể nhận diện ý định là ý định hàng đầu | Không thể nhận diện ý định là ý định hàng đầu |

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.