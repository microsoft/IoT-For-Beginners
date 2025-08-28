<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e74eb2fc7cc3b81916b52e957802f182",
  "translation_date": "2025-08-27T20:55:04+00:00",
  "source_file": "4-manufacturing/lessons/1-train-fruit-detector/assignment.md",
  "language_code": "vi"
}
-->
# Huấn luyện bộ phân loại của bạn cho nhiều loại trái cây và rau củ

## Hướng dẫn

Trong bài học này, bạn đã huấn luyện một bộ phân loại hình ảnh để có thể phân biệt giữa trái cây chín và chưa chín, nhưng chỉ với một loại trái cây. Một bộ phân loại có thể được huấn luyện để nhận diện nhiều loại trái cây, với mức độ thành công khác nhau tùy thuộc vào loại trái cây và sự khác biệt giữa chín và chưa chín.

Ví dụ, với những loại trái cây thay đổi màu sắc khi chín, các bộ phân loại hình ảnh có thể kém hiệu quả hơn so với cảm biến màu vì chúng thường hoạt động trên hình ảnh thang xám thay vì hình ảnh đầy đủ màu sắc.

Hãy huấn luyện bộ phân loại của bạn với các loại trái cây khác để xem nó hoạt động tốt như thế nào, đặc biệt khi các loại trái cây trông giống nhau. Ví dụ, táo và cà chua.

## Tiêu chí đánh giá

| Tiêu chí | Xuất sắc | Đạt yêu cầu | Cần cải thiện |
| -------- | --------- | ----------- | ------------- |
| Huấn luyện bộ phân loại cho nhiều loại trái cây | Có thể huấn luyện bộ phân loại cho nhiều loại trái cây | Có thể huấn luyện bộ phân loại cho một loại trái cây bổ sung | Không thể huấn luyện bộ phân loại cho thêm loại trái cây nào |
| Xác định mức độ hiệu quả của bộ phân loại | Có thể nhận xét chính xác về mức độ hiệu quả của bộ phân loại với các loại trái cây khác nhau | Có thể quan sát và đưa ra gợi ý về mức độ hiệu quả của nó | Không thể nhận xét về mức độ hiệu quả của bộ phân loại |

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp từ con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.