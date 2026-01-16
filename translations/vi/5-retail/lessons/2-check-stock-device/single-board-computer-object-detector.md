<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a3fdfec1d1e2cb645ea11c2930b51299",
  "translation_date": "2025-08-27T20:39:22+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-object-detector.md",
  "language_code": "vi"
}
-->
# Gọi trình phát hiện đối tượng từ thiết bị IoT của bạn - Phần cứng IoT ảo và Raspberry Pi

Khi trình phát hiện đối tượng của bạn đã được xuất bản, nó có thể được sử dụng từ thiết bị IoT của bạn.

## Sao chép dự án phân loại hình ảnh

Phần lớn trình phát hiện hàng hóa của bạn giống với trình phân loại hình ảnh mà bạn đã tạo trong bài học trước.

### Nhiệm vụ - sao chép dự án phân loại hình ảnh

1. Tạo một thư mục có tên `stock-counter` trên máy tính của bạn nếu bạn đang sử dụng thiết bị IoT ảo, hoặc trên Raspberry Pi của bạn. Nếu bạn đang sử dụng thiết bị IoT ảo, hãy đảm bảo thiết lập môi trường ảo.

1. Thiết lập phần cứng camera.

    * Nếu bạn đang sử dụng Raspberry Pi, bạn sẽ cần lắp PiCamera. Bạn cũng có thể muốn cố định camera ở một vị trí cố định, ví dụ, bằng cách treo cáp qua một hộp hoặc lon, hoặc cố định camera vào một hộp bằng băng keo hai mặt.
    * Nếu bạn đang sử dụng thiết bị IoT ảo, bạn sẽ cần cài đặt CounterFit và CounterFit PyCamera shim. Nếu bạn định sử dụng hình ảnh tĩnh, hãy chụp một số hình ảnh mà trình phát hiện đối tượng của bạn chưa từng thấy. Nếu bạn định sử dụng webcam, hãy đảm bảo nó được đặt ở vị trí có thể nhìn thấy hàng hóa mà bạn đang phát hiện.

1. Lặp lại các bước từ [bài học 2 của dự án sản xuất](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) để chụp hình ảnh từ camera.

1. Lặp lại các bước từ [bài học 2 của dự án sản xuất](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) để gọi trình phân loại hình ảnh. Phần lớn mã này sẽ được tái sử dụng để phát hiện đối tượng.

## Thay đổi mã từ trình phân loại sang trình phát hiện hình ảnh

Mã bạn sử dụng để phân loại hình ảnh rất giống với mã để phát hiện đối tượng. Sự khác biệt chính là phương thức được gọi trên Custom Vision SDK và kết quả của cuộc gọi.

### Nhiệm vụ - thay đổi mã từ trình phân loại sang trình phát hiện hình ảnh

1. Xóa ba dòng mã phân loại hình ảnh và xử lý các dự đoán:

    ```python
    results = predictor.classify_image(project_id, iteration_name, image)
    
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Xóa ba dòng này.

1. Thêm mã sau để phát hiện đối tượng trong hình ảnh:

    ```python
    results = predictor.detect_image(project_id, iteration_name, image)

    threshold = 0.3
    
    predictions = list(prediction for prediction in results.predictions if prediction.probability > threshold)
    
    for prediction in predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Mã này gọi phương thức `detect_image` trên predictor để chạy trình phát hiện đối tượng. Sau đó, nó thu thập tất cả các dự đoán có xác suất trên ngưỡng, in chúng ra console.

    Không giống như trình phân loại hình ảnh chỉ trả về một kết quả cho mỗi thẻ, trình phát hiện đối tượng sẽ trả về nhiều kết quả, vì vậy bất kỳ kết quả nào có xác suất thấp cần được lọc ra.

1. Chạy mã này và nó sẽ chụp một hình ảnh, gửi nó đến trình phát hiện đối tượng, và in ra các đối tượng được phát hiện. Nếu bạn đang sử dụng thiết bị IoT ảo, hãy đảm bảo bạn có một hình ảnh phù hợp được đặt trong CounterFit, hoặc webcam của bạn được chọn. Nếu bạn đang sử dụng Raspberry Pi, hãy đảm bảo camera của bạn đang hướng vào các đối tượng trên kệ.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   34.13%
    tomato paste:   33.95%
    tomato paste:   35.05%
    tomato paste:   32.80%
    ```

    > 💁 Bạn có thể cần điều chỉnh `threshold` đến giá trị phù hợp với hình ảnh của bạn.

    Bạn sẽ có thể xem hình ảnh đã được chụp và các giá trị này trong tab **Predictions** trong Custom Vision.

    ![4 lon sốt cà chua trên kệ với các dự đoán cho 4 lần phát hiện là 35.8%, 33.5%, 25.7% và 16.6%](../../../../../translated_images/vi/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 Bạn có thể tìm thấy mã này trong thư mục [code-detect/pi](../../../../../5-retail/lessons/2-check-stock-device/code-detect/pi) hoặc [code-detect/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-detect/virtual-iot-device).

😀 Chương trình đếm hàng hóa của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.