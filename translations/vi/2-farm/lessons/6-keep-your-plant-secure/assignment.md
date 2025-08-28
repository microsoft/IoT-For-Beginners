<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "34010c663d96d5f419eda6ac2366a78d",
  "translation_date": "2025-08-27T22:10:34+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/assignment.md",
  "language_code": "vi"
}
-->
# Xây dựng một thiết bị IoT mới

## Hướng dẫn

Trong 6 bài học vừa qua, bạn đã học về nông nghiệp số và cách sử dụng các thiết bị IoT để thu thập dữ liệu nhằm dự đoán sự phát triển của cây trồng, cũng như tự động tưới nước dựa trên các chỉ số độ ẩm của đất.

Hãy sử dụng những gì bạn đã học để xây dựng một thiết bị IoT mới bằng cách sử dụng cảm biến và bộ truyền động mà bạn chọn. Gửi dữ liệu telemetry đến IoT Hub và sử dụng dữ liệu đó để điều khiển bộ truyền động thông qua mã serverless. Bạn có thể sử dụng cảm biến và bộ truyền động mà bạn đã sử dụng trong dự án này hoặc dự án trước, hoặc nếu bạn có phần cứng khác, hãy thử nghiệm với thứ mới.

## Tiêu chí đánh giá

| Tiêu chí | Xuất sắc | Đạt yêu cầu | Cần cải thiện |
| -------- | --------- | ----------- | ------------- |
| Lập trình thiết bị IoT để sử dụng cảm biến và bộ truyền động | Lập trình thiết bị IoT hoạt động với cả cảm biến và bộ truyền động | Lập trình thiết bị IoT hoạt động với cảm biến hoặc bộ truyền động | Không thể lập trình thiết bị IoT để sử dụng cảm biến hoặc bộ truyền động |
| Kết nối thiết bị IoT với IoT Hub | Có thể triển khai IoT Hub, gửi dữ liệu telemetry đến đó và nhận lệnh từ đó | Có thể triển khai IoT Hub và gửi dữ liệu telemetry hoặc nhận lệnh | Không thể triển khai IoT Hub và giao tiếp với nó từ thiết bị IoT |
| Điều khiển bộ truyền động bằng mã serverless | Có thể triển khai Azure Function để điều khiển thiết bị được kích hoạt bởi sự kiện telemetry | Có thể triển khai Azure Function được kích hoạt bởi sự kiện telemetry nhưng không thể điều khiển bộ truyền động | Không thể triển khai Azure Function |

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, nên sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.