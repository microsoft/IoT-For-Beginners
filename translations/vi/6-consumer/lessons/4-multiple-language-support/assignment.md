<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "701f4a4466f9309b6e1d863077df0c06",
  "translation_date": "2025-08-27T22:59:49+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/assignment.md",
  "language_code": "vi"
}
-->
# Xây dựng một bộ dịch ngôn ngữ toàn cầu

## Hướng dẫn

Bộ dịch ngôn ngữ toàn cầu là một thiết bị có thể dịch giữa nhiều ngôn ngữ, cho phép những người nói các ngôn ngữ khác nhau có thể giao tiếp với nhau. Sử dụng những gì bạn đã học trong các bài học trước để xây dựng một bộ dịch ngôn ngữ toàn cầu bằng cách sử dụng 2 thiết bị IoT.

> Nếu bạn không có 2 thiết bị, hãy làm theo các bước trong vài bài học trước để thiết lập một thiết bị IoT ảo làm một trong các thiết bị IoT.

Bạn nên cấu hình một thiết bị cho một ngôn ngữ và thiết bị còn lại cho ngôn ngữ khác. Mỗi thiết bị cần nhận dạng giọng nói, chuyển đổi thành văn bản, gửi đến thiết bị kia thông qua IoT Hub và ứng dụng Functions, sau đó dịch và phát lại giọng nói đã được dịch.

> 💁 Mẹo: Khi gửi giọng nói từ một thiết bị sang thiết bị khác, hãy gửi kèm ngôn ngữ của nó, giúp việc dịch dễ dàng hơn. Bạn thậm chí có thể để mỗi thiết bị đăng ký sử dụng IoT Hub và ứng dụng Functions trước, truyền ngôn ngữ mà chúng hỗ trợ để lưu trữ trong Azure Storage. Sau đó, bạn có thể sử dụng ứng dụng Functions để thực hiện việc dịch, gửi văn bản đã dịch đến thiết bị IoT.

## Tiêu chí đánh giá

| Tiêu chí | Xuất sắc | Đạt yêu cầu | Cần cải thiện |
| -------- | --------- | ----------- | ------------- |
| Tạo bộ dịch ngôn ngữ toàn cầu | Có thể xây dựng một bộ dịch ngôn ngữ toàn cầu, chuyển đổi giọng nói được nhận dạng bởi một thiết bị thành giọng nói được phát bởi thiết bị khác bằng ngôn ngữ khác | Có thể làm cho một số thành phần hoạt động, chẳng hạn như nhận dạng giọng nói hoặc dịch, nhưng không thể xây dựng giải pháp hoàn chỉnh từ đầu đến cuối | Không thể xây dựng bất kỳ phần nào của bộ dịch ngôn ngữ toàn cầu hoạt động |

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.