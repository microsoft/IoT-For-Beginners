<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-27T20:43:27+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "vi"
}
-->
# Đếm hàng tồn kho từ thiết bị IoT của bạn - Wio Terminal

Kết hợp giữa các dự đoán và hộp giới hạn của chúng có thể được sử dụng để đếm hàng tồn kho trong một hình ảnh.

## Đếm hàng tồn kho

![4 lon sốt cà chua với các hộp giới hạn xung quanh mỗi lon](../../../../../translated_images/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.vi.jpg)

Trong hình ảnh trên, các hộp giới hạn có một chút chồng lấn. Nếu sự chồng lấn này lớn hơn nhiều, thì các hộp giới hạn có thể chỉ ra cùng một đối tượng. Để đếm các đối tượng một cách chính xác, bạn cần bỏ qua các hộp có sự chồng lấn đáng kể.

### Nhiệm vụ - đếm hàng tồn kho bỏ qua sự chồng lấn

1. Mở dự án `stock-counter` của bạn nếu nó chưa được mở.

1. Phía trên hàm `processPredictions`, thêm đoạn mã sau:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    Điều này định nghĩa phần trăm chồng lấn được phép trước khi các hộp giới hạn được coi là cùng một đối tượng. 0.20 định nghĩa mức chồng lấn 20%.

1. Bên dưới đoạn này, và phía trên hàm `processPredictions`, thêm đoạn mã sau để tính toán sự chồng lấn giữa hai hình chữ nhật:

    ```cpp
    struct Point {
        float x, y;
    };

    struct Rect {
        Point topLeft, bottomRight;
    };

    float area(Rect rect)
    {
        return abs(rect.bottomRight.x - rect.topLeft.x) * abs(rect.bottomRight.y - rect.topLeft.y);
    }
     
    float overlappingArea(Rect rect1, Rect rect2)
    {
        float left = max(rect1.topLeft.x, rect2.topLeft.x);
        float right = min(rect1.bottomRight.x, rect2.bottomRight.x);
        float top = max(rect1.topLeft.y, rect2.topLeft.y);
        float bottom = min(rect1.bottomRight.y, rect2.bottomRight.y);
    
    
        if ( right > left && bottom > top )
        {
            return (right-left)*(bottom-top);
        }
        
        return 0.0f;
    }
    ```

    Đoạn mã này định nghĩa một cấu trúc `Point` để lưu trữ các điểm trên hình ảnh, và một cấu trúc `Rect` để định nghĩa một hình chữ nhật bằng cách sử dụng tọa độ góc trên bên trái và góc dưới bên phải. Sau đó, nó định nghĩa một hàm `area` để tính diện tích của một hình chữ nhật từ tọa độ góc trên bên trái và góc dưới bên phải.

    Tiếp theo, nó định nghĩa một hàm `overlappingArea` để tính diện tích chồng lấn của 2 hình chữ nhật. Nếu chúng không chồng lấn, hàm trả về 0.

1. Bên dưới hàm `overlappingArea`, khai báo một hàm để chuyển đổi một hộp giới hạn thành một `Rect`:

    ```cpp
    Rect rectFromBoundingBox(JsonVariant prediction)
    {
        JsonObject bounding_box = prediction["boundingBox"].as<JsonObject>();
    
        float left = bounding_box["left"].as<float>();
        float top = bounding_box["top"].as<float>();
        float width = bounding_box["width"].as<float>();
        float height = bounding_box["height"].as<float>();
    
        Point topLeft = {left, top};
        Point bottomRight = {left + width, top + height};
    
        return {topLeft, bottomRight};
    }
    ```

    Hàm này lấy một dự đoán từ bộ phát hiện đối tượng, trích xuất hộp giới hạn và sử dụng các giá trị trên hộp giới hạn để định nghĩa một hình chữ nhật. Cạnh phải được tính từ cạnh trái cộng với chiều rộng. Cạnh dưới được tính từ cạnh trên cộng với chiều cao.

1. Các dự đoán cần được so sánh với nhau, và nếu 2 dự đoán có sự chồng lấn lớn hơn ngưỡng, một trong số chúng cần được xóa. Ngưỡng chồng lấn là một phần trăm, vì vậy cần được nhân với kích thước của hộp giới hạn nhỏ nhất để kiểm tra xem sự chồng lấn có vượt quá phần trăm đã cho của hộp giới hạn hay không, chứ không phải phần trăm của toàn bộ hình ảnh. Bắt đầu bằng cách xóa nội dung của hàm `processPredictions`.

1. Thêm đoạn mã sau vào hàm `processPredictions` trống:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for (int i = 0; i < predictions.size(); ++i)
    {
        Rect prediction_1_rect = rectFromBoundingBox(predictions[i]);
        float prediction_1_area = area(prediction_1_rect);
        bool passed = true;

        for (int j = i + 1; j < predictions.size(); ++j)
        {
            Rect prediction_2_rect = rectFromBoundingBox(predictions[j]);
            float prediction_2_area = area(prediction_2_rect);

            float overlap = overlappingArea(prediction_1_rect, prediction_2_rect);
            float smallest_area = min(prediction_1_area, prediction_2_area);

            if (overlap > (overlap_threshold * smallest_area))
            {
                passed = false;
                break;
            }
        }

        if (passed)
        {
            passed_predictions.push_back(predictions[i]);
        }
    }
    ```

    Đoạn mã này khai báo một vector để lưu trữ các dự đoán không chồng lấn. Sau đó, nó lặp qua tất cả các dự đoán, tạo một `Rect` từ hộp giới hạn.

    Tiếp theo, đoạn mã này lặp qua các dự đoán còn lại, bắt đầu từ dự đoán sau dự đoán hiện tại. Điều này ngăn các dự đoán được so sánh nhiều lần - một khi 1 và 2 đã được so sánh, không cần so sánh 2 với 1 nữa, chỉ cần so sánh với 3, 4, v.v.

    Đối với mỗi cặp dự đoán, diện tích chồng lấn được tính toán. Sau đó, diện tích này được so sánh với diện tích của hộp giới hạn nhỏ nhất - nếu sự chồng lấn vượt quá ngưỡng phần trăm của hộp giới hạn nhỏ nhất, dự đoán được đánh dấu là không đạt. Nếu sau khi so sánh tất cả các sự chồng lấn, dự đoán vượt qua các kiểm tra, nó được thêm vào tập hợp `passed_predictions`.

    > 💁 Đây là một cách rất đơn giản để loại bỏ sự chồng lấn, chỉ loại bỏ cái đầu tiên trong một cặp chồng lấn. Đối với mã sản xuất, bạn sẽ muốn thêm nhiều logic hơn vào đây, chẳng hạn như xem xét sự chồng lấn giữa nhiều đối tượng, hoặc nếu một hộp giới hạn nằm trong một hộp khác.

1. Sau đó, thêm đoạn mã sau để gửi chi tiết của các dự đoán đã vượt qua đến màn hình nối tiếp:

    ```cpp
    for(JsonVariant prediction : passed_predictions)
    {
        String boundingBox = prediction["boundingBox"].as<String>();
        String tag = prediction["tagName"].as<String>();
        float probability = prediction["probability"].as<float>();

        char buff[32];
        sprintf(buff, "%s:\t%.2f%%\t%s", tag.c_str(), probability * 100.0, boundingBox.c_str());
        Serial.println(buff);
    }
    ```

    Đoạn mã này lặp qua các dự đoán đã vượt qua và in chi tiết của chúng lên màn hình nối tiếp.

1. Bên dưới đoạn này, thêm mã để in số lượng mục đã đếm được lên màn hình nối tiếp:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    Điều này sau đó có thể được gửi đến một dịch vụ IoT để cảnh báo nếu mức tồn kho thấp.

1. Tải lên và chạy mã của bạn. Hướng camera vào các đối tượng trên kệ và nhấn nút C. Thử điều chỉnh giá trị `overlap_threshold` để xem các dự đoán bị bỏ qua.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%  {"left":0.395631,"top":0.215897,"width":0.180768,"height":0.359364}
    tomato paste:   35.87%  {"left":0.378554,"top":0.583012,"width":0.14824,"height":0.359382}
    tomato paste:   34.11%  {"left":0.699024,"top":0.592617,"width":0.124411,"height":0.350456}
    tomato paste:   35.16%  {"left":0.513006,"top":0.647853,"width":0.187472,"height":0.325817}
    Counted 4 stock items.
    ```

> 💁 Bạn có thể tìm thấy đoạn mã này trong thư mục [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal).

😀 Chương trình đếm hàng tồn kho của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.