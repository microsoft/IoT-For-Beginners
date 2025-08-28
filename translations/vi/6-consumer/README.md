<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5de7dc1e2ddc402d415473bb795568d4",
  "translation_date": "2025-08-27T23:07:20+00:00",
  "source_file": "6-consumer/README.md",
  "language_code": "vi"
}
-->
# IoT tiêu dùng - xây dựng trợ lý giọng nói thông minh

Thực phẩm đã được trồng, vận chuyển đến nhà máy chế biến, phân loại chất lượng, bán tại cửa hàng và giờ là lúc nấu ăn! Một trong những công cụ cốt lõi của bất kỳ nhà bếp nào là bộ hẹn giờ. Ban đầu, chúng được thiết kế như đồng hồ cát - thực phẩm của bạn được nấu chín khi toàn bộ cát chảy xuống bóng đèn dưới cùng. Sau đó, chúng chuyển sang cơ khí, rồi điện tử.

Phiên bản mới nhất hiện nay là một phần của các thiết bị thông minh. Trong các nhà bếp trên khắp thế giới, bạn sẽ nghe thấy các đầu bếp hét lên "Hey Siri - đặt hẹn giờ 10 phút", hoặc "Alexa - hủy hẹn giờ bánh mì của tôi". Không còn cần phải quay lại nhà bếp để kiểm tra hẹn giờ, bạn có thể làm điều đó từ điện thoại hoặc chỉ cần gọi lớn từ khắp phòng.

Trong 4 bài học này, bạn sẽ học cách xây dựng một bộ hẹn giờ thông minh, sử dụng AI để nhận diện giọng nói của bạn, hiểu những gì bạn yêu cầu, và phản hồi thông tin về hẹn giờ của bạn. Bạn cũng sẽ thêm hỗ trợ cho nhiều ngôn ngữ.

> ⚠️ Làm việc với dữ liệu giọng nói và micro sử dụng rất nhiều bộ nhớ, điều này có thể dễ dàng vượt quá giới hạn trên các vi điều khiển. Dự án này đã tìm cách giải quyết các vấn đề đó, nhưng hãy lưu ý rằng các bài thực hành với Wio Terminal khá phức tạp và có thể mất nhiều thời gian hơn các bài thực hành khác trong chương trình học này.

> 💁 Các bài học này sẽ sử dụng một số tài nguyên đám mây. Nếu bạn không hoàn thành tất cả các bài học trong dự án này, hãy đảm bảo [dọn dẹp dự án của bạn](../clean-up.md).

## Chủ đề

1. [Nhận diện giọng nói với thiết bị IoT](./lessons/1-speech-recognition/README.md)
1. [Hiểu ngôn ngữ](./lessons/2-language-understanding/README.md)
1. [Đặt hẹn giờ và cung cấp phản hồi bằng giọng nói](./lessons/3-spoken-feedback/README.md)
1. [Hỗ trợ nhiều ngôn ngữ](./lessons/4-multiple-language-support/README.md)

## Tín dụng

Tất cả các bài học được viết với ♥️ bởi [Jim Bennett](https://GitHub.com/JimBobBennett)

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.