<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5cb65a6ec4387ed177e145347e8e308e",
  "translation_date": "2025-08-27T23:59:12+00:00",
  "source_file": "3-transport/lessons/4-geofences/assignment.md",
  "language_code": "vi"
}
-->
# Gửi thông báo bằng Twilio

## Hướng dẫn

Trong mã của bạn cho đến nay, bạn chỉ ghi lại khoảng cách đến hàng rào địa lý. Trong bài tập này, bạn sẽ cần thêm một thông báo, có thể là tin nhắn văn bản hoặc email, khi tọa độ GPS nằm trong hàng rào địa lý.

Azure Functions cung cấp nhiều tùy chọn ràng buộc, bao gồm cả các dịch vụ bên thứ ba như Twilio, một nền tảng giao tiếp.

* Đăng ký tài khoản miễn phí tại [Twilio.com](https://www.twilio.com)
* Đọc tài liệu về cách ràng buộc Azure Functions với Twilio SMS trên [trang tài liệu Microsoft về ràng buộc Twilio cho Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?WT.mc_id=academic-17441-jabenn&tabs=python).
* Đọc tài liệu về cách ràng buộc Azure Functions với Twilio SendGrid để gửi email trên [trang tài liệu Microsoft về ràng buộc Azure Functions SendGrid](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?WT.mc_id=academic-17441-jabenn&tabs=python).
* Thêm ràng buộc vào ứng dụng Functions của bạn để nhận thông báo khi tọa độ GPS nằm trong hoặc ngoài hàng rào địa lý - không phải cả hai.

## Tiêu chí đánh giá

| Tiêu chí | Xuất sắc | Đạt yêu cầu | Cần cải thiện |
| -------- | --------- | ----------- | ------------- |
| Cấu hình ràng buộc functions và nhận email hoặc SMS | Có thể cấu hình ràng buộc functions và nhận email hoặc SMS khi tọa độ nằm trong hoặc ngoài hàng rào địa lý, nhưng không phải cả hai | Có thể cấu hình ràng buộc nhưng không thể gửi email hoặc SMS, hoặc chỉ có thể gửi khi tọa độ nằm cả trong và ngoài hàng rào địa lý | Không thể cấu hình ràng buộc và gửi email hoặc SMS |

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.