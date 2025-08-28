<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cc7ad255517f5f618f9c8899e6ff6783",
  "translation_date": "2025-08-27T21:12:13+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/assignment.md",
  "language_code": "vi"
}
-->
# Chạy các dịch vụ khác trên edge

## Hướng dẫn

Không chỉ các bộ phân loại hình ảnh có thể chạy trên edge, bất kỳ thứ gì có thể được đóng gói vào một container đều có thể triển khai trên thiết bị IoT Edge. Mã không máy chủ chạy dưới dạng Azure Functions, chẳng hạn như các triggers bạn đã tạo trong các bài học trước, có thể chạy trong container và do đó trên IoT Edge.

Hãy chọn một trong các bài học trước và thử chạy ứng dụng Azure Functions trong một container IoT Edge. Bạn có thể tìm thấy hướng dẫn chỉ cách thực hiện điều này bằng cách sử dụng một dự án ứng dụng Functions khác trong [Hướng dẫn: Triển khai Azure Functions dưới dạng các module IoT Edge trên tài liệu Microsoft](https://docs.microsoft.com/azure/iot-edge/tutorial-deploy-function?WT.mc_id=academic-17441-jabenn&view=iotedge-2020-11).

## Tiêu chí đánh giá

| Tiêu chí | Xuất sắc | Đạt yêu cầu | Cần cải thiện |
| -------- | --------- | ----------- | ------------- |
| Triển khai ứng dụng Azure Functions lên IoT Edge | Có thể triển khai ứng dụng Azure Functions lên IoT Edge và sử dụng nó với thiết bị IoT để kích hoạt trigger từ dữ liệu IoT | Có thể triển khai ứng dụng Functions lên IoT Edge, nhưng không thể kích hoạt trigger | Không thể triển khai ứng dụng Functions lên IoT Edge |

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.