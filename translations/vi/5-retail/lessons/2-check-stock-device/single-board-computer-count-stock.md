<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c4320311c0f2c1884a6a21265d98a51",
  "translation_date": "2025-08-27T20:44:30+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-count-stock.md",
  "language_code": "vi"
}
-->
# Đếm hàng tồn kho từ thiết bị IoT của bạn - Phần cứng IoT ảo và Raspberry Pi

Kết hợp giữa các dự đoán và hộp giới hạn có thể được sử dụng để đếm hàng tồn kho trong một hình ảnh.

## Hiển thị hộp giới hạn

Như một bước gỡ lỗi hữu ích, bạn không chỉ có thể in ra các hộp giới hạn mà còn có thể vẽ chúng lên hình ảnh đã được lưu vào đĩa khi hình ảnh được chụp.

### Nhiệm vụ - in hộp giới hạn

1. Đảm bảo dự án `stock-counter` đang được mở trong VS Code, và môi trường ảo đã được kích hoạt nếu bạn đang sử dụng thiết bị IoT ảo.

1. Thay đổi câu lệnh `print` trong vòng lặp `for` thành như sau để in các hộp giới hạn ra console:

    ```python
    print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%\t{prediction.bounding_box}')
    ```

1. Chạy ứng dụng với camera hướng vào một số hàng hóa trên kệ. Các hộp giới hạn sẽ được in ra console, với các giá trị trái, trên, rộng và cao từ 0-1.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   33.42%  {'additional_properties': {}, 'left': 0.3455171, 'top': 0.09916268, 'width': 0.14175442, 'height': 0.29405564}
    tomato paste:   34.41%  {'additional_properties': {}, 'left': 0.48283678, 'top': 0.10242918, 'width': 0.11782813, 'height': 0.27467814}
    tomato paste:   31.25%  {'additional_properties': {}, 'left': 0.4923783, 'top': 0.35007596, 'width': 0.13668466, 'height': 0.28304994}
    tomato paste:   31.05%  {'additional_properties': {}, 'left': 0.36416405, 'top': 0.37494493, 'width': 0.14024884, 'height': 0.26880276}
    ```

### Nhiệm vụ - vẽ hộp giới hạn lên hình ảnh

1. Gói Pip [Pillow](https://pypi.org/project/Pillow/) có thể được sử dụng để vẽ lên hình ảnh. Cài đặt gói này bằng lệnh sau:

    ```sh
    pip3 install pillow
    ```

    Nếu bạn đang sử dụng thiết bị IoT ảo, hãy đảm bảo chạy lệnh này từ bên trong môi trường ảo đã được kích hoạt.

1. Thêm câu lệnh import sau vào đầu tệp `app.py`:

    ```python
    from PIL import Image, ImageDraw, ImageColor
    ```

    Câu lệnh này nhập mã cần thiết để chỉnh sửa hình ảnh.

1. Thêm đoạn mã sau vào cuối tệp `app.py`:

    ```python
    with Image.open('image.jpg') as im:
        draw = ImageDraw.Draw(im)
    
        for prediction in predictions:
            scale_left = prediction.bounding_box.left
            scale_top = prediction.bounding_box.top
            scale_right = prediction.bounding_box.left + prediction.bounding_box.width
            scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
            
            left = scale_left * im.width
            top = scale_top * im.height
            right = scale_right * im.width
            bottom = scale_bottom * im.height
    
            draw.rectangle([left, top, right, bottom], outline=ImageColor.getrgb('red'), width=2)
    
        im.save('image.jpg')
    ```

    Đoạn mã này mở hình ảnh đã được lưu trước đó để chỉnh sửa. Sau đó, nó lặp qua các dự đoán để lấy các hộp giới hạn và tính toán tọa độ góc dưới bên phải bằng cách sử dụng các giá trị hộp giới hạn từ 0-1. Các giá trị này sau đó được chuyển đổi thành tọa độ hình ảnh bằng cách nhân với kích thước tương ứng của hình ảnh. Ví dụ, nếu giá trị trái là 0.5 trên một hình ảnh rộng 600 pixel, giá trị này sẽ được chuyển đổi thành 300 (0.5 x 600 = 300).

    Mỗi hộp giới hạn được vẽ lên hình ảnh bằng một đường màu đỏ. Cuối cùng, hình ảnh đã chỉnh sửa được lưu lại, ghi đè lên hình ảnh gốc.

1. Chạy ứng dụng với camera hướng vào một số hàng hóa trên kệ. Bạn sẽ thấy tệp `image.jpg` trong trình khám phá của VS Code, và bạn có thể chọn nó để xem các hộp giới hạn.

    ![4 hộp sốt cà chua với hộp giới hạn xung quanh mỗi hộp](../../../../../translated_images/vi/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.jpg)

## Đếm hàng tồn kho

Trong hình ảnh được hiển thị ở trên, các hộp giới hạn có một chút chồng lấn. Nếu sự chồng lấn này lớn hơn nhiều, thì các hộp giới hạn có thể chỉ ra cùng một đối tượng. Để đếm các đối tượng một cách chính xác, bạn cần bỏ qua các hộp có sự chồng lấn đáng kể.

### Nhiệm vụ - đếm hàng tồn kho bỏ qua sự chồng lấn

1. Gói Pip [Shapely](https://pypi.org/project/Shapely/) có thể được sử dụng để tính toán sự giao nhau. Nếu bạn đang sử dụng Raspberry Pi, bạn sẽ cần cài đặt một thư viện phụ thuộc trước:

    ```sh
    sudo apt install libgeos-dev
    ```

1. Cài đặt gói Pip Shapely:

    ```sh
    pip3 install shapely
    ```

    Nếu bạn đang sử dụng thiết bị IoT ảo, hãy đảm bảo chạy lệnh này từ bên trong môi trường ảo đã được kích hoạt.

1. Thêm câu lệnh import sau vào đầu tệp `app.py`:

    ```python
    from shapely.geometry import Polygon
    ```

    Câu lệnh này nhập mã cần thiết để tạo các đa giác nhằm tính toán sự chồng lấn.

1. Phía trên đoạn mã vẽ các hộp giới hạn, thêm đoạn mã sau:

    ```python
    overlap_threshold = 0.20
    ```

    Đoạn mã này định nghĩa tỷ lệ phần trăm chồng lấn được phép trước khi các hộp giới hạn được coi là cùng một đối tượng. 0.20 định nghĩa mức chồng lấn 20%.

1. Để tính toán sự chồng lấn bằng Shapely, các hộp giới hạn cần được chuyển đổi thành các đa giác Shapely. Thêm hàm sau để thực hiện điều này:

    ```python
    def create_polygon(prediction):
        scale_left = prediction.bounding_box.left
        scale_top = prediction.bounding_box.top
        scale_right = prediction.bounding_box.left + prediction.bounding_box.width
        scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
    
        return Polygon([(scale_left, scale_top), (scale_right, scale_top), (scale_right, scale_bottom), (scale_left, scale_bottom)])
    ```

    Hàm này tạo một đa giác bằng cách sử dụng hộp giới hạn của một dự đoán.

1. Logic để loại bỏ các đối tượng chồng lấn liên quan đến việc so sánh tất cả các hộp giới hạn và nếu bất kỳ cặp dự đoán nào có hộp giới hạn chồng lấn vượt quá ngưỡng, một trong các dự đoán sẽ bị xóa. Để so sánh tất cả các dự đoán, bạn so sánh dự đoán 1 với 2, 3, 4, v.v., sau đó 2 với 3, 4, v.v. Đoạn mã sau thực hiện điều này:

    ```python
    to_delete = []

    for i in range(0, len(predictions)):
        polygon_1 = create_polygon(predictions[i])
    
        for j in range(i+1, len(predictions)):
            polygon_2 = create_polygon(predictions[j])
            overlap = polygon_1.intersection(polygon_2).area

            smallest_area = min(polygon_1.area, polygon_2.area)
    
            if overlap > (overlap_threshold * smallest_area):
                to_delete.append(predictions[i])
                break
    
    for d in to_delete:
        predictions.remove(d)

    print(f'Counted {len(predictions)} stock items')
    ```

    Sự chồng lấn được tính toán bằng phương pháp `Polygon.intersection` của Shapely, phương pháp này trả về một đa giác có sự chồng lấn. Diện tích sau đó được tính toán từ đa giác này. Ngưỡng chồng lấn không phải là một giá trị tuyệt đối, mà cần phải là tỷ lệ phần trăm của hộp giới hạn, vì vậy hộp giới hạn nhỏ nhất được tìm, và ngưỡng chồng lấn được sử dụng để tính toán diện tích mà sự chồng lấn có thể không vượt quá tỷ lệ phần trăm ngưỡng chồng lấn của hộp giới hạn nhỏ nhất. Nếu sự chồng lấn vượt quá mức này, dự đoán sẽ được đánh dấu để xóa.

    Một khi một dự đoán đã được đánh dấu để xóa, nó không cần phải được kiểm tra lại, vì vậy vòng lặp bên trong sẽ thoát ra để kiểm tra dự đoán tiếp theo. Bạn không thể xóa các mục khỏi danh sách trong khi đang lặp qua nó, vì vậy các hộp giới hạn chồng lấn vượt quá ngưỡng sẽ được thêm vào danh sách `to_delete`, sau đó bị xóa ở cuối.

    Cuối cùng, số lượng hàng tồn kho được in ra console. Điều này sau đó có thể được gửi đến một dịch vụ IoT để cảnh báo nếu mức hàng tồn kho thấp. Tất cả đoạn mã này nằm trước khi các hộp giới hạn được vẽ, vì vậy bạn sẽ thấy các dự đoán hàng tồn kho không có sự chồng lấn trên các hình ảnh được tạo.

    > 💁 Đây là cách rất đơn giản để loại bỏ sự chồng lấn, chỉ xóa đối tượng đầu tiên trong một cặp chồng lấn. Đối với mã sản xuất, bạn sẽ muốn thêm nhiều logic hơn vào đây, chẳng hạn như xem xét sự chồng lấn giữa nhiều đối tượng, hoặc nếu một hộp giới hạn nằm trong một hộp giới hạn khác.

1. Chạy ứng dụng với camera hướng vào một số hàng hóa trên kệ. Kết quả đầu ra sẽ chỉ ra số lượng hộp giới hạn không có sự chồng lấn vượt quá ngưỡng. Thử điều chỉnh giá trị `overlap_threshold` để xem các dự đoán bị bỏ qua.

> 💁 Bạn có thể tìm thấy đoạn mã này trong thư mục [code-count/pi](../../../../../5-retail/lessons/2-check-stock-device/code-count/pi) hoặc [code-count/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-count/virtual-iot-device).

😀 Chương trình đếm hàng tồn kho của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.