<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ba7150ffc4a6999f6c3cfb4906ec7df",
  "translation_date": "2025-08-27T21:02:50+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/virtual-device-camera.md",
  "language_code": "vi"
}
-->
# Chụp ảnh - Phần cứng IoT ảo

Trong phần này của bài học, bạn sẽ thêm cảm biến camera vào thiết bị IoT ảo và đọc hình ảnh từ nó.

## Phần cứng

Thiết bị IoT ảo sẽ sử dụng một camera mô phỏng, gửi hình ảnh từ tệp hoặc từ webcam của bạn.

### Thêm camera vào CounterFit

Để sử dụng camera ảo, bạn cần thêm một camera vào ứng dụng CounterFit.

#### Nhiệm vụ - thêm camera vào CounterFit

Thêm camera vào ứng dụng CounterFit.

1. Tạo một ứng dụng Python mới trên máy tính của bạn trong một thư mục có tên `fruit-quality-detector` với một tệp duy nhất tên là `app.py` và một môi trường ảo Python, sau đó thêm các gói pip của CounterFit.

    > ⚠️ Bạn có thể tham khảo [hướng dẫn tạo và thiết lập dự án Python CounterFit trong bài học 1 nếu cần](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Cài đặt một gói Pip bổ sung để cài đặt một CounterFit shim có thể giao tiếp với cảm biến Camera bằng cách mô phỏng một số chức năng của [gói Picamera Pip](https://pypi.org/project/picamera/). Đảm bảo rằng bạn đang cài đặt từ terminal với môi trường ảo đã được kích hoạt.

    ```sh
    pip install counterfit-shims-picamera
    ```

1. Đảm bảo rằng ứng dụng web CounterFit đang chạy.

1. Tạo một camera:

    1. Trong hộp *Create sensor* ở bảng *Sensors*, chọn hộp *Sensor type* và chọn *Camera*.

    1. Đặt *Name* thành `Picamera`.

    1. Chọn nút **Add** để tạo camera.

    ![Cài đặt camera](../../../../../translated_images/vi/counterfit-create-camera.a5de97f59c0bd3cbe0416d7e89a3cfe86d19fbae05c641c53a91286412af0a34.png)

    Camera sẽ được tạo và xuất hiện trong danh sách cảm biến.

    ![Camera đã được tạo](../../../../../translated_images/vi/counterfit-camera.001ec52194c8ee5d3f617173da2c79e1df903d10882adc625cbfc493525125d4.png)

## Lập trình camera

Thiết bị IoT ảo giờ đây có thể được lập trình để sử dụng camera ảo.

### Nhiệm vụ - lập trình camera

Lập trình thiết bị.

1. Đảm bảo rằng ứng dụng `fruit-quality-detector` đang mở trong VS Code.

1. Mở tệp `app.py`.

1. Thêm đoạn mã sau vào đầu tệp `app.py` để kết nối ứng dụng với CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Thêm đoạn mã sau vào tệp `app.py` của bạn:

    ```python
    import io
    from counterfit_shims_picamera import PiCamera
    ```

    Đoạn mã này nhập một số thư viện cần thiết, bao gồm lớp `PiCamera` từ thư viện counterfit_shims_picamera.

1. Thêm đoạn mã sau bên dưới để khởi tạo camera:

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    ```

    Đoạn mã này tạo một đối tượng PiCamera, đặt độ phân giải thành 640x480. Mặc dù các độ phân giải cao hơn được hỗ trợ, bộ phân loại hình ảnh hoạt động trên hình ảnh nhỏ hơn nhiều (227x227), vì vậy không cần chụp và gửi hình ảnh lớn hơn.

    Dòng `camera.rotation = 0` đặt góc xoay của hình ảnh theo độ. Nếu bạn cần xoay hình ảnh từ webcam hoặc tệp, hãy đặt giá trị này phù hợp. Ví dụ, nếu bạn muốn thay đổi hình ảnh của một quả chuối trên webcam ở chế độ ngang thành chế độ dọc, hãy đặt `camera.rotation = 90`.

1. Thêm đoạn mã sau bên dưới để chụp hình ảnh dưới dạng dữ liệu nhị phân:

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    Đoạn mã này tạo một đối tượng `BytesIO` để lưu trữ dữ liệu nhị phân. Hình ảnh được đọc từ camera dưới dạng tệp JPEG và được lưu trữ trong đối tượng này. Đối tượng này có một chỉ báo vị trí để biết nó đang ở đâu trong dữ liệu, vì vậy dòng `image.seek(0)` di chuyển vị trí này trở lại đầu để tất cả dữ liệu có thể được đọc sau.

1. Bên dưới đoạn mã này, thêm đoạn mã sau để lưu hình ảnh vào tệp:

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    Đoạn mã này mở một tệp có tên `image.jpg` để ghi, sau đó đọc tất cả dữ liệu từ đối tượng `BytesIO` và ghi vào tệp.

    > 💁 Bạn có thể chụp hình ảnh trực tiếp vào tệp thay vì đối tượng `BytesIO` bằng cách truyền tên tệp vào lệnh `camera.capture`. Lý do sử dụng đối tượng `BytesIO` là để sau này trong bài học, bạn có thể gửi hình ảnh đến bộ phân loại hình ảnh của mình.

1. Cấu hình hình ảnh mà camera trong CounterFit sẽ chụp. Bạn có thể đặt *Source* thành *File*, sau đó tải lên một tệp hình ảnh, hoặc đặt *Source* thành *WebCam*, và hình ảnh sẽ được chụp từ webcam của bạn. Đảm bảo rằng bạn chọn nút **Set** sau khi chọn một hình ảnh hoặc chọn webcam của bạn.

    ![CounterFit với tệp được đặt làm nguồn hình ảnh và webcam hiển thị một người cầm quả chuối trong bản xem trước của webcam](../../../../../translated_images/vi/counterfit-camera-options.eb3bd5150a8e7dffbf24bc5bcaba0cf2cdef95fbe6bbe393695d173817d6b8df.png)

1. Một hình ảnh sẽ được chụp và lưu dưới dạng `image.jpg` trong thư mục hiện tại. Bạn sẽ thấy tệp này trong trình khám phá của VS Code. Chọn tệp để xem hình ảnh. Nếu cần xoay, cập nhật dòng `camera.rotation = 0` phù hợp và chụp lại hình ảnh.

> 💁 Bạn có thể tìm thấy đoạn mã này trong thư mục [code-camera/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/virtual-iot-device).

😀 Chương trình camera của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.