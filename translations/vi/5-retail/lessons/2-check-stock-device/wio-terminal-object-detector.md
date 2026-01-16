<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4cf1421420a6fab9ab4f2c391bd523b7",
  "translation_date": "2025-08-27T20:45:56+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-object-detector.md",
  "language_code": "vi"
}
-->
# Gọi trình phát hiện đối tượng từ thiết bị IoT của bạn - Wio Terminal

Khi trình phát hiện đối tượng của bạn đã được xuất bản, bạn có thể sử dụng nó từ thiết bị IoT của mình.

## Sao chép dự án phân loại hình ảnh

Phần lớn trình phát hiện hàng hóa của bạn giống với trình phân loại hình ảnh mà bạn đã tạo trong bài học trước.

### Nhiệm vụ - sao chép dự án phân loại hình ảnh

1. Kết nối ArduCam với Wio Terminal của bạn, theo các bước từ [bài học 2 của dự án sản xuất](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera).

    Bạn cũng có thể muốn cố định camera ở một vị trí cố định, ví dụ, bằng cách treo dây cáp qua một hộp hoặc lon, hoặc gắn camera vào một hộp bằng băng keo hai mặt.

1. Tạo một dự án Wio Terminal mới hoàn toàn bằng PlatformIO. Đặt tên cho dự án này là `stock-counter`.

1. Lặp lại các bước từ [bài học 2 của dự án sản xuất](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) để chụp ảnh từ camera.

1. Lặp lại các bước từ [bài học 2 của dự án sản xuất](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) để gọi trình phân loại hình ảnh. Phần lớn mã này sẽ được tái sử dụng để phát hiện đối tượng.

## Thay đổi mã từ trình phân loại sang trình phát hiện hình ảnh

Mã bạn sử dụng để phân loại hình ảnh rất giống với mã để phát hiện đối tượng. Sự khác biệt chính là URL được gọi mà bạn đã lấy từ Custom Vision, và kết quả của cuộc gọi.

### Nhiệm vụ - thay đổi mã từ trình phân loại sang trình phát hiện hình ảnh

1. Thêm chỉ thị include sau vào đầu tệp `main.cpp`:

    ```cpp
    #include <vector>
    ```

1. Đổi tên hàm `classifyImage` thành `detectStock`, cả tên hàm và lời gọi trong hàm `buttonPressed`.

1. Phía trên hàm `detectStock`, khai báo một ngưỡng để lọc bất kỳ phát hiện nào có xác suất thấp:

    ```cpp
    const float threshold = 0.3f;
    ```

    Không giống như trình phân loại hình ảnh chỉ trả về một kết quả cho mỗi thẻ, trình phát hiện đối tượng sẽ trả về nhiều kết quả, vì vậy bất kỳ kết quả nào có xác suất thấp cần được lọc ra.

1. Phía trên hàm `detectStock`, khai báo một hàm để xử lý các dự đoán:

    ```cpp
    void processPredictions(std::vector<JsonVariant> &predictions)
    {
        for(JsonVariant prediction : predictions)
        {
            String tag = prediction["tagName"].as<String>();
            float probability = prediction["probability"].as<float>();
    
            char buff[32];
            sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
            Serial.println(buff);
        }
    }
    ```

    Hàm này nhận danh sách các dự đoán và in chúng ra màn hình serial.

1. Trong hàm `detectStock`, thay thế nội dung của vòng lặp `for` lặp qua các dự đoán bằng đoạn mã sau:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for(JsonVariant prediction : predictions) 
    {
        float probability = prediction["probability"].as<float>();
        if (probability > threshold)
        {
            passed_predictions.push_back(prediction);
        }
    }

    processPredictions(passed_predictions);
    ```

    Vòng lặp này lặp qua các dự đoán, so sánh xác suất với ngưỡng. Tất cả các dự đoán có xác suất cao hơn ngưỡng sẽ được thêm vào một `list` và truyền đến hàm `processPredictions`.

1. Tải lên và chạy mã của bạn. Hướng camera vào các đối tượng trên kệ và nhấn nút C. Bạn sẽ thấy đầu ra trên màn hình serial:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%
    tomato paste:   35.87%
    tomato paste:   34.11%
    tomato paste:   35.16%
    ```

    > 💁 Bạn có thể cần điều chỉnh giá trị `threshold` sao cho phù hợp với hình ảnh của mình.

    Bạn sẽ có thể thấy hình ảnh đã được chụp, và các giá trị này trong tab **Predictions** của Custom Vision.

    ![4 lon sốt cà chua trên kệ với các dự đoán cho 4 phát hiện lần lượt là 35.8%, 33.5%, 25.7% và 16.6%](../../../../../translated_images/vi/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 Bạn có thể tìm thấy mã này trong thư mục [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal).

😀 Chương trình đếm hàng hóa của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.