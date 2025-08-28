<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0ccdc1faa676a485c4c6ecbddb9f9067",
  "translation_date": "2025-08-27T23:51:24+00:00",
  "source_file": "3-transport/lessons/3-visualize-location-data/assignment.md",
  "language_code": "vi"
}
-->
# Triển khai ứng dụng của bạn

## Hướng dẫn

Có nhiều cách để bạn triển khai ứng dụng của mình để chia sẻ với mọi người, bao gồm sử dụng GitHub Pages hoặc một trong nhiều nhà cung cấp dịch vụ khác. Một cách thực sự tuyệt vời để làm điều này là sử dụng Azure Static Web Apps. Trong bài tập này, hãy xây dựng ứng dụng web của bạn và triển khai nó lên đám mây bằng cách làm theo [hướng dẫn này](https://github.com/Azure/static-web-apps-cli) hoặc xem [các video này](https://www.youtube.com/watch?v=ADVGIXciYn8&list=PLlrxD0HtieHgMPeBaDQFx9yNuFxx6S1VG&index=3).  
Một lợi ích của việc sử dụng Azure Static Web Apps là bạn có thể ẩn bất kỳ khóa API nào trong cổng thông tin, vì vậy hãy tận dụng cơ hội này để tái cấu trúc subscriptionKey của bạn thành một biến và lưu trữ nó trên đám mây.

## Tiêu chí đánh giá

| Tiêu chí  | Xuất sắc                                                                                                                               | Đạt yêu cầu                                                                                                        | Cần cải thiện                                     |
| --------- | --------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------ | ------------------------------------------------ |
|           | Một ứng dụng web hoạt động được trình bày trong một kho lưu trữ GitHub có tài liệu, với subscriptionKey được lưu trữ trên đám mây và gọi qua một biến | Một ứng dụng web hoạt động được trình bày trong một kho lưu trữ GitHub có tài liệu nhưng subscriptionKey không được lưu trữ trên đám mây | Ứng dụng web có lỗi hoặc không hoạt động đúng cách |

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp từ con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.