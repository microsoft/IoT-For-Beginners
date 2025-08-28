<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-28T00:09:15+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "vi"
}
-->
# Điều tra các ràng buộc hàm

## Hướng dẫn

Ràng buộc hàm cho phép mã của bạn lưu các blob vào bộ lưu trữ blob bằng cách trả về chúng từ hàm `main`. Tài khoản Azure Storage, bộ sưu tập và các chi tiết khác được cấu hình trong tệp `function.json`.

Khi làm việc với Azure hoặc các công nghệ Microsoft khác, nguồn thông tin tốt nhất là [tài liệu Microsoft tại docs.com](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn). Trong bài tập này, bạn sẽ cần đọc tài liệu về ràng buộc Azure Functions để tìm hiểu cách thiết lập ràng buộc đầu ra.

Một số trang để bắt đầu bao gồm:

* [Khái niệm về triggers và bindings trong Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Tổng quan về ràng buộc Azure Blob storage cho Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Ràng buộc đầu ra Azure Blob storage cho Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## Tiêu chí đánh giá

| Tiêu chí | Xuất sắc | Đạt yêu cầu | Cần cải thiện |
| -------- | --------- | ----------- | ------------- |
| Cấu hình ràng buộc đầu ra blob storage | Có thể cấu hình ràng buộc đầu ra, trả về blob và lưu trữ thành công trong blob storage | Có thể cấu hình ràng buộc đầu ra hoặc trả về blob nhưng không thể lưu trữ thành công trong blob storage | Không thể cấu hình ràng buộc đầu ra |

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.