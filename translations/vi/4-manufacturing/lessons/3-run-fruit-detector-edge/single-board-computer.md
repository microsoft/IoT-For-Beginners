<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-27T21:14:14+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "vi"
}
-->
# Phân loại hình ảnh bằng bộ phân loại hình ảnh dựa trên IoT Edge - Phần cứng IoT ảo và Raspberry Pi

Trong phần này của bài học, bạn sẽ sử dụng Bộ phân loại hình ảnh chạy trên thiết bị IoT Edge.

## Sử dụng bộ phân loại IoT Edge

Thiết bị IoT có thể được chuyển hướng để sử dụng bộ phân loại hình ảnh IoT Edge. URL cho Bộ phân loại hình ảnh là `http://<IP address or name>/image`, thay thế `<IP address or name>` bằng địa chỉ IP hoặc tên máy chủ của máy tính chạy IoT Edge.

Thư viện Python cho Custom Vision chỉ hoạt động với các mô hình được lưu trữ trên đám mây, không phải các mô hình được lưu trữ trên IoT Edge. Điều này có nghĩa là bạn sẽ cần sử dụng REST API để gọi bộ phân loại.

### Nhiệm vụ - sử dụng bộ phân loại IoT Edge

1. Mở dự án `fruit-quality-detector` trong VS Code nếu chưa mở. Nếu bạn đang sử dụng thiết bị IoT ảo, hãy đảm bảo môi trường ảo đã được kích hoạt.

1. Mở tệp `app.py`, và xóa các câu lệnh import từ `azure.cognitiveservices.vision.customvision.prediction` và `msrest.authentication`.

1. Thêm câu lệnh import sau vào đầu tệp:

    ```python
    import requests
    ```

1. Xóa toàn bộ mã sau khi hình ảnh được lưu vào tệp, từ `image_file.write(image.read())` đến cuối tệp.

1. Thêm đoạn mã sau vào cuối tệp:

    ```python
    prediction_url = '<URL>'
    headers = {
        'Content-Type' : 'application/octet-stream'
    }
    image.seek(0)
    response = requests.post(prediction_url, headers=headers, data=image)
    results = response.json()
    
    for prediction in results['predictions']:
        print(f'{prediction["tagName"]}:\t{prediction["probability"] * 100:.2f}%')
    ```

    Thay thế `<URL>` bằng URL của bộ phân loại của bạn.

    Đoạn mã này thực hiện một yêu cầu REST POST tới bộ phân loại, gửi hình ảnh dưới dạng nội dung của yêu cầu. Kết quả trả về dưới dạng JSON, và được giải mã để in ra các xác suất.

1. Chạy mã của bạn, với camera hướng vào một số loại trái cây, hoặc một bộ hình ảnh phù hợp, hoặc trái cây hiển thị trên webcam của bạn nếu sử dụng phần cứng IoT ảo. Bạn sẽ thấy kết quả hiển thị trên bảng điều khiển:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Bạn có thể tìm thấy đoạn mã này trong thư mục [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) hoặc [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device).

😀 Chương trình phân loại chất lượng trái cây của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.