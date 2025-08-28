<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "da5d9360fe02fdcc1e91a725016c846d",
  "translation_date": "2025-08-27T23:22:13+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/assignment.md",
  "language_code": "vi"
}
-->
# Hủy bộ hẹn giờ

## Hướng dẫn

Trong bài tập của bài học trước, bạn đã thêm một ý định hủy bộ hẹn giờ vào LUIS. Trong bài tập này, bạn cần xử lý ý định này trong mã serverless, gửi một lệnh đến thiết bị IoT, sau đó hủy bộ hẹn giờ.

## Tiêu chí đánh giá

| Tiêu chí | Xuất sắc | Đạt yêu cầu | Cần cải thiện |
| -------- | --------- | ----------- | ------------- |
| Xử lý ý định trong mã serverless và gửi lệnh | Có thể xử lý ý định và gửi lệnh đến thiết bị | Có thể xử lý ý định nhưng không gửi được lệnh đến thiết bị | Không thể xử lý ý định |
| Hủy bộ hẹn giờ trên thiết bị | Có thể nhận lệnh và hủy bộ hẹn giờ | Có thể nhận lệnh nhưng không hủy được bộ hẹn giờ | Không thể nhận lệnh |

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, chúng tôi khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp từ con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.