<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "bded364fc06ce37d7a76aed3be1ba73a",
  "translation_date": "2025-08-27T23:54:01+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/assignment.md",
  "language_code": "vi"
}
-->
# Điều tra dữ liệu GPS khác

## Hướng dẫn

Các câu NMEA từ cảm biến GPS của bạn chứa dữ liệu khác ngoài vị trí. Hãy điều tra dữ liệu bổ sung này và sử dụng nó trong thiết bị IoT của bạn.

Ví dụ - bạn có thể lấy ngày và giờ hiện tại không? Nếu bạn đang sử dụng vi điều khiển, bạn có thể đặt đồng hồ bằng dữ liệu GPS theo cách tương tự như bạn đã làm với tín hiệu NTP trong dự án trước không? Bạn có thể lấy độ cao (chiều cao của bạn so với mực nước biển) hoặc tốc độ hiện tại của bạn không?

Nếu bạn đang sử dụng thiết bị IoT ảo, bạn có thể lấy một số dữ liệu này bằng cách gửi các câu NMEA được tạo bằng công cụ [nmeagen.org](https://www.nmeagen.org).

## Tiêu chí đánh giá

| Tiêu chí | Xuất sắc | Đạt yêu cầu | Cần cải thiện |
| -------- | --------- | ----------- | ------------- |
| Lấy thêm dữ liệu GPS | Có thể lấy và sử dụng thêm dữ liệu GPS, hoặc làm dữ liệu telemetry hoặc để thiết lập thiết bị IoT | Có thể lấy thêm dữ liệu GPS, nhưng không thể sử dụng nó | Không thể lấy thêm dữ liệu GPS |

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.