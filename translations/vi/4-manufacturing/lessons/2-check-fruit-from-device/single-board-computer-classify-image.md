# Phân loại hình ảnh - Phần cứng IoT ảo và Raspberry Pi

Trong phần này của bài học, bạn sẽ gửi hình ảnh được chụp bởi camera đến dịch vụ Custom Vision để phân loại.

## Gửi hình ảnh đến Custom Vision

Dịch vụ Custom Vision có một SDK Python mà bạn có thể sử dụng để phân loại hình ảnh.

### Nhiệm vụ - gửi hình ảnh đến Custom Vision

1. Mở thư mục `fruit-quality-detector` trong VS Code. Nếu bạn đang sử dụng thiết bị IoT ảo, hãy đảm bảo môi trường ảo đang chạy trong terminal.

1. SDK Python để gửi hình ảnh đến Custom Vision có sẵn dưới dạng gói Pip. Cài đặt nó bằng lệnh sau:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. Thêm các dòng import sau vào đầu tệp `app.py`:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    Điều này sẽ đưa vào một số module từ thư viện Custom Vision, một module để xác thực với prediction key, và một module cung cấp lớp prediction client có thể gọi Custom Vision.

1. Thêm đoạn mã sau vào cuối tệp:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    Thay thế `<prediction_url>` bằng URL bạn đã sao chép từ hộp thoại *Prediction URL* trước đó trong bài học này. Thay thế `<prediction key>` bằng prediction key bạn đã sao chép từ cùng hộp thoại.

1. URL dự đoán được cung cấp bởi hộp thoại *Prediction URL* được thiết kế để sử dụng khi gọi trực tiếp endpoint REST. SDK Python sử dụng các phần của URL ở các vị trí khác nhau. Thêm đoạn mã sau để tách URL này thành các phần cần thiết:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    Điều này sẽ tách URL, trích xuất endpoint `https://<location>.api.cognitive.microsoft.com`, ID dự án, và tên của phiên bản đã được xuất bản.

1. Tạo một đối tượng predictor để thực hiện dự đoán với đoạn mã sau:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    `prediction_credentials` bao bọc prediction key. Chúng sau đó được sử dụng để tạo một đối tượng prediction client trỏ đến endpoint.

1. Gửi hình ảnh đến Custom Vision bằng đoạn mã sau:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    Đoạn mã này tua lại hình ảnh về đầu, sau đó gửi nó đến prediction client.

1. Cuối cùng, hiển thị kết quả với đoạn mã sau:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Đoạn mã này sẽ lặp qua tất cả các dự đoán đã được trả về và hiển thị chúng trên terminal. Các xác suất được trả về là các số thập phân từ 0-1, với 0 là 0% khả năng khớp với tag, và 1 là 100% khả năng.

    > 💁 Bộ phân loại hình ảnh sẽ trả về phần trăm cho tất cả các tag đã được sử dụng. Mỗi tag sẽ có một xác suất rằng hình ảnh khớp với tag đó.

1. Chạy mã của bạn, với camera của bạn hướng vào một số loại trái cây, hoặc một bộ hình ảnh phù hợp, hoặc trái cây hiển thị trên webcam của bạn nếu sử dụng phần cứng IoT ảo. Bạn sẽ thấy đầu ra trong console:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    Bạn sẽ có thể thấy hình ảnh đã được chụp, và các giá trị này trong tab **Predictions** của Custom Vision.

    ![Một quả chuối trong Custom Vision được dự đoán chín 56.8% và chưa chín 43.1%](../../../../../translated_images/vi/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 Bạn có thể tìm thấy mã này trong thư mục [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) hoặc [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device).

😀 Chương trình phân loại chất lượng trái cây của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.