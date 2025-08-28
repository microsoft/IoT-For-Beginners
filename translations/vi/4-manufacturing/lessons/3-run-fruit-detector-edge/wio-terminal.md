<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-27T22:56:31+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "vi"
}
-->
# Phân loại hình ảnh bằng bộ phân loại hình ảnh dựa trên IoT Edge - Wio Terminal

Trong phần này của bài học, bạn sẽ sử dụng Bộ Phân Loại Hình Ảnh chạy trên thiết bị IoT Edge.

## Sử dụng bộ phân loại IoT Edge

Thiết bị IoT có thể được chuyển hướng để sử dụng bộ phân loại hình ảnh IoT Edge. URL cho Bộ Phân Loại Hình Ảnh là `http://<IP address or name>/image`, thay thế `<IP address or name>` bằng địa chỉ IP hoặc tên máy chủ của máy tính chạy IoT Edge.

### Nhiệm vụ - sử dụng bộ phân loại IoT Edge

1. Mở dự án ứng dụng `fruit-quality-detector` nếu chưa mở.

1. Bộ phân loại hình ảnh đang chạy dưới dạng REST API sử dụng HTTP, không phải HTTPS, vì vậy cuộc gọi cần sử dụng một WiFi client chỉ hoạt động với các cuộc gọi HTTP. Điều này có nghĩa là chứng chỉ không cần thiết. Xóa `CERTIFICATE` khỏi tệp `config.h`.

1. URL dự đoán trong tệp `config.h` cần được cập nhật thành URL mới. Bạn cũng có thể xóa `PREDICTION_KEY` vì không cần thiết.

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    Thay thế `<URL>` bằng URL cho bộ phân loại của bạn.

1. Trong `main.cpp`, thay đổi chỉ thị include cho WiFi Client Secure để nhập phiên bản HTTP tiêu chuẩn:

    ```cpp
    #include <WiFiClient.h>
    ```

1. Thay đổi khai báo `WiFiClient` thành phiên bản HTTP:

    ```cpp
    WiFiClient client;
    ```

1. Chọn dòng thiết lập chứng chỉ trên WiFi client. Xóa dòng `client.setCACert(CERTIFICATE);` khỏi hàm `connectWiFi`.

1. Trong hàm `classifyImage`, xóa dòng `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);` thiết lập khóa dự đoán trong header.

1. Tải lên và chạy mã của bạn. Hướng camera vào một số loại trái cây và nhấn nút C. Bạn sẽ thấy kết quả trong serial monitor:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Bạn có thể tìm thấy mã này trong thư mục [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal).

😀 Chương trình phân loại chất lượng trái cây của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.