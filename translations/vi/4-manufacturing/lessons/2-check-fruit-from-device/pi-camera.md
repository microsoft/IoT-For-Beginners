<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c677667095f6133eee418c7e53615d05",
  "translation_date": "2025-08-27T20:58:30+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/pi-camera.md",
  "language_code": "vi"
}
-->
# Chụp ảnh - Raspberry Pi

Trong phần này của bài học, bạn sẽ thêm cảm biến camera vào Raspberry Pi và đọc hình ảnh từ nó.

## Phần cứng

Raspberry Pi cần một camera.

Camera bạn sẽ sử dụng là [Raspberry Pi Camera Module](https://www.raspberrypi.org/products/camera-module-v2/). Camera này được thiết kế để hoạt động với Raspberry Pi và kết nối thông qua một cổng chuyên dụng trên Pi.

> 💁 Camera này sử dụng [Camera Serial Interface, một giao thức từ Mobile Industry Processor Interface Alliance](https://wikipedia.org/wiki/Camera_Serial_Interface), được gọi là MIPI-CSI. Đây là một giao thức chuyên dụng để truyền hình ảnh.

## Kết nối camera

Camera có thể được kết nối với Raspberry Pi bằng cáp ruy băng.

### Nhiệm vụ - kết nối camera

![Một Raspberry Pi Camera](../../../../../translated_images/vi/pi-camera-module.4278753c31bd6e757aa2b858be97d72049f71616278cefe4fb5abb485b40a078.png)

1. Tắt nguồn Pi.

1. Kết nối cáp ruy băng đi kèm với camera vào camera. Để làm điều này, nhẹ nhàng kéo phần kẹp nhựa đen trong giá đỡ ra một chút, sau đó trượt cáp vào khe cắm, với mặt màu xanh hướng ra xa ống kính, các dải chân kim loại hướng về phía ống kính. Khi cáp đã được cắm hoàn toàn, đẩy phần kẹp nhựa đen trở lại vị trí ban đầu.

    Bạn có thể tìm thấy một hình ảnh động minh họa cách mở kẹp và chèn cáp trong [tài liệu Raspberry Pi Getting Started with the Camera module](https://projects.raspberrypi.org/en/projects/getting-started-with-picamera/2).

    ![Cáp ruy băng được chèn vào module camera](../../../../../translated_images/vi/pi-camera-ribbon-cable.0bf82acd251611c21ac616f082849413e2b322a261d0e4f8fec344248083b07e.png)

1. Tháo Grove Base Hat khỏi Pi.

1. Luồn cáp ruy băng qua khe camera trong Grove Base Hat. Đảm bảo mặt màu xanh của cáp hướng về phía các cổng analog được gắn nhãn **A0**, **A1**, v.v.

    ![Cáp ruy băng đi qua Grove Base Hat](../../../../../translated_images/vi/grove-base-hat-ribbon-cable.501fed202fcf73b11b2b68f6d246189f7d15d3e4423c572ddee79d77b4632b47.png)

1. Chèn cáp ruy băng vào cổng camera trên Pi. Một lần nữa, kéo phần kẹp nhựa đen lên, chèn cáp, sau đó đẩy kẹp trở lại. Mặt màu xanh của cáp nên hướng về phía các cổng USB và ethernet.

    ![Cáp ruy băng được kết nối với khe camera trên Pi](../../../../../translated_images/vi/pi-camera-socket-ribbon-cable.a18309920b11800911082ed7aa6fb28e6d9be3a022e4079ff990016cae3fca10.png)

1. Lắp lại Grove Base Hat.

## Lập trình camera

Raspberry Pi giờ đây có thể được lập trình để sử dụng camera bằng thư viện Python [PiCamera](https://pypi.org/project/picamera/).

### Nhiệm vụ - bật chế độ camera cũ

Đáng tiếc, với phiên bản Raspberry Pi OS Bullseye, phần mềm camera đi kèm với hệ điều hành đã thay đổi, khiến PiCamera không hoạt động theo mặc định. Hiện đang có một phiên bản thay thế, gọi là PiCamera2, nhưng nó chưa sẵn sàng để sử dụng.

Hiện tại, bạn có thể đặt Pi vào chế độ camera cũ để cho phép PiCamera hoạt động. Cổng camera cũng bị vô hiệu hóa theo mặc định, nhưng việc bật phần mềm camera cũ sẽ tự động kích hoạt cổng này.

1. Bật nguồn Pi và chờ nó khởi động.

1. Mở VS Code, trực tiếp trên Pi hoặc kết nối thông qua tiện ích Remote SSH.

1. Chạy các lệnh sau từ terminal:

    ```sh
    sudo raspi-config nonint do_legacy 0
    sudo reboot
    ```

    Lệnh này sẽ bật một cài đặt để kích hoạt phần mềm camera cũ, sau đó khởi động lại Pi để cài đặt này có hiệu lực.

1. Chờ Pi khởi động lại, sau đó mở lại VS Code.

### Nhiệm vụ - lập trình camera

Lập trình thiết bị.

1. Từ terminal, tạo một thư mục mới trong thư mục home của người dùng `pi` có tên `fruit-quality-detector`. Tạo một tệp trong thư mục này có tên `app.py`.

1. Mở thư mục này trong VS Code.

1. Để tương tác với camera, bạn có thể sử dụng thư viện Python PiCamera. Cài đặt gói Pip cho thư viện này bằng lệnh sau:

    ```sh
    pip3 install picamera
    ```

1. Thêm đoạn mã sau vào tệp `app.py` của bạn:

    ```python
    import io
    import time
    from picamera import PiCamera
    ```

    Đoạn mã này nhập một số thư viện cần thiết, bao gồm thư viện `PiCamera`.

1. Thêm đoạn mã sau bên dưới để khởi tạo camera:

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    
    time.sleep(2)
    ```

    Đoạn mã này tạo một đối tượng PiCamera, đặt độ phân giải thành 640x480. Mặc dù các độ phân giải cao hơn được hỗ trợ (lên đến 3280x2464), bộ phân loại hình ảnh hoạt động trên các hình ảnh nhỏ hơn nhiều (227x227) nên không cần chụp và gửi hình ảnh lớn hơn.

    Dòng `camera.rotation = 0` đặt góc xoay của hình ảnh. Cáp ruy băng đi vào từ phía dưới của camera, nhưng nếu camera của bạn được xoay để dễ dàng hướng vào vật thể bạn muốn phân loại, bạn có thể thay đổi dòng này thành số độ xoay.

    ![Camera treo xuống trên một lon nước uống](../../../../../translated_images/vi/pi-camera-upside-down.5376961ba31459883362124152ad6b823d5ac5fc14e85f317e22903bd681c2b6.png)

    Ví dụ, nếu bạn treo cáp ruy băng qua một vật thể để nó nằm ở phía trên của camera, hãy đặt góc xoay thành 180:

    ```python
    camera.rotation = 180
    ```

    Camera cần vài giây để khởi động, do đó dòng `time.sleep(2)` được sử dụng.

1. Thêm đoạn mã sau bên dưới để chụp hình ảnh dưới dạng dữ liệu nhị phân:

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    Đoạn mã này tạo một đối tượng `BytesIO` để lưu trữ dữ liệu nhị phân. Hình ảnh được đọc từ camera dưới dạng tệp JPEG và lưu trữ trong đối tượng này. Đối tượng này có một chỉ báo vị trí để biết nó đang ở đâu trong dữ liệu để có thể ghi thêm dữ liệu vào cuối nếu cần, vì vậy dòng `image.seek(0)` di chuyển vị trí này trở lại đầu để tất cả dữ liệu có thể được đọc sau.

1. Bên dưới đoạn mã này, thêm đoạn sau để lưu hình ảnh vào tệp:

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    Đoạn mã này mở một tệp có tên `image.jpg` để ghi, sau đó đọc tất cả dữ liệu từ đối tượng `BytesIO` và ghi vào tệp.

    > 💁 Bạn có thể chụp hình ảnh trực tiếp vào tệp thay vì đối tượng `BytesIO` bằng cách truyền tên tệp vào lệnh `camera.capture`. Lý do sử dụng đối tượng `BytesIO` là để sau này trong bài học bạn có thể gửi hình ảnh đến bộ phân loại hình ảnh của mình.

1. Hướng camera vào một vật thể và chạy đoạn mã này.

1. Một hình ảnh sẽ được chụp và lưu dưới dạng `image.jpg` trong thư mục hiện tại. Bạn sẽ thấy tệp này trong trình khám phá của VS Code. Chọn tệp để xem hình ảnh. Nếu cần xoay, cập nhật dòng `camera.rotation = 0` theo yêu cầu và chụp lại hình ảnh.

> 💁 Bạn có thể tìm thấy đoạn mã này trong thư mục [code-camera/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/pi).

😀 Chương trình camera của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.