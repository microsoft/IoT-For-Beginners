<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3764e089adf2d5801272bc0895f8498b",
  "translation_date": "2025-08-27T22:37:11+00:00",
  "source_file": "4-manufacturing/README.md",
  "language_code": "vi"
}
-->
# Sản xuất và chế biến - sử dụng IoT để cải thiện quy trình chế biến thực phẩm

Khi thực phẩm đến trung tâm hoặc nhà máy chế biến, không phải lúc nào cũng được chuyển thẳng đến siêu thị. Thường thì thực phẩm sẽ trải qua một số bước chế biến, chẳng hạn như phân loại theo chất lượng. Đây là một quy trình từng được thực hiện thủ công - bắt đầu từ cánh đồng khi người thu hoạch chỉ chọn những quả chín, sau đó tại nhà máy, trái cây sẽ di chuyển trên băng chuyền và nhân viên sẽ loại bỏ thủ công những quả bị dập hoặc hỏng. Từng có kinh nghiệm hái và phân loại dâu tây như một công việc mùa hè khi còn đi học, tôi có thể khẳng định rằng đây không phải là một công việc thú vị.

Các hệ thống hiện đại hơn dựa vào IoT để phân loại. Một số thiết bị đầu tiên như máy phân loại của [Weco](https://wecotek.com) sử dụng cảm biến quang học để phát hiện chất lượng sản phẩm, ví dụ như loại bỏ cà chua xanh. Những thiết bị này có thể được triển khai trên máy thu hoạch tại chính trang trại hoặc trong các nhà máy chế biến.

Khi có những tiến bộ trong Trí tuệ Nhân tạo (AI) và Học máy (ML), các máy móc này có thể trở nên tiên tiến hơn, sử dụng các mô hình ML được huấn luyện để phân biệt giữa trái cây và các vật thể lạ như đá, đất hoặc côn trùng. Các mô hình này cũng có thể được huấn luyện để phát hiện chất lượng trái cây, không chỉ là trái cây bị dập mà còn phát hiện sớm bệnh hoặc các vấn đề khác của cây trồng.

> 🎓 Thuật ngữ *mô hình ML* đề cập đến kết quả của việc huấn luyện phần mềm học máy trên một tập dữ liệu. Ví dụ, bạn có thể huấn luyện một mô hình ML để phân biệt giữa cà chua chín và chưa chín, sau đó sử dụng mô hình này trên các hình ảnh mới để xác định xem cà chua đã chín hay chưa.

Trong 4 bài học này, bạn sẽ học cách huấn luyện các mô hình AI dựa trên hình ảnh để phát hiện chất lượng trái cây, cách sử dụng chúng từ một thiết bị IoT, và cách chạy chúng trên thiết bị biên - tức là trên thiết bị IoT thay vì trên đám mây.

> 💁 Những bài học này sẽ sử dụng một số tài nguyên đám mây. Nếu bạn không hoàn thành tất cả các bài học trong dự án này, hãy đảm bảo [dọn dẹp dự án của bạn](../clean-up.md).

## Chủ đề

1. [Huấn luyện bộ phát hiện chất lượng trái cây](./lessons/1-train-fruit-detector/README.md)
1. [Kiểm tra chất lượng trái cây từ thiết bị IoT](./lessons/2-check-fruit-from-device/README.md)
1. [Chạy bộ phát hiện trái cây trên thiết bị biên](./lessons/3-run-fruit-detector-edge/README.md)
1. [Kích hoạt phát hiện chất lượng trái cây từ cảm biến](./lessons/4-trigger-fruit-detector/README.md)

## Tác giả

Tất cả các bài học được viết với ♥️ bởi [Jen Fox](https://github.com/jenfoxbot) và [Jim Bennett](https://GitHub.com/JimBobBennett)

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, nên sử dụng dịch vụ dịch thuật chuyên nghiệp từ con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.