# Huấn luyện bộ phát hiện hàng hóa

![Tóm tắt bài học qua sketchnote](../../../../../translated_images/vi/lesson-19.cf6973cecadf080c.webp)

> Sketchnote bởi [Nitya Narasimhan](https://github.com/nitya). Nhấp vào hình ảnh để xem phiên bản lớn hơn.

Video này cung cấp tổng quan về Dịch vụ Azure Custom Vision cho phát hiện đối tượng, một dịch vụ sẽ được đề cập trong bài học này.

[![Custom Vision 2 - Phát hiện đối tượng dễ dàng | The Xamarin Show](https://img.youtube.com/vi/wtTYSyBUpFc/0.jpg)](https://www.youtube.com/watch?v=wtTYSyBUpFc)

> 🎥 Nhấp vào hình ảnh trên để xem video

## Câu hỏi trước bài giảng

[Câu hỏi trước bài giảng](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/37)

## Giới thiệu

Trong dự án trước, bạn đã sử dụng AI để huấn luyện một bộ phân loại hình ảnh - một mô hình có thể xác định xem một hình ảnh có chứa thứ gì đó, chẳng hạn như trái cây chín hay chưa chín. Một loại mô hình AI khác có thể được sử dụng với hình ảnh là phát hiện đối tượng. Các mô hình này không phân loại hình ảnh bằng thẻ, thay vào đó chúng được huấn luyện để nhận diện các đối tượng và có thể tìm thấy chúng trong hình ảnh, không chỉ phát hiện rằng đối tượng có mặt mà còn xác định vị trí của nó trong hình ảnh. Điều này cho phép bạn đếm số lượng đối tượng trong hình ảnh.

Trong bài học này, bạn sẽ tìm hiểu về phát hiện đối tượng, bao gồm cách nó có thể được sử dụng trong bán lẻ. Bạn cũng sẽ học cách huấn luyện một bộ phát hiện đối tượng trên đám mây.

Trong bài học này, chúng ta sẽ đề cập đến:

* [Phát hiện đối tượng](../../../../../5-retail/lessons/1-train-stock-detector)
* [Sử dụng phát hiện đối tượng trong bán lẻ](../../../../../5-retail/lessons/1-train-stock-detector)
* [Huấn luyện bộ phát hiện đối tượng](../../../../../5-retail/lessons/1-train-stock-detector)
* [Kiểm tra bộ phát hiện đối tượng của bạn](../../../../../5-retail/lessons/1-train-stock-detector)
* [Huấn luyện lại bộ phát hiện đối tượng của bạn](../../../../../5-retail/lessons/1-train-stock-detector)

## Phát hiện đối tượng

Phát hiện đối tượng liên quan đến việc phát hiện các đối tượng trong hình ảnh bằng AI. Không giống như bộ phân loại hình ảnh bạn đã huấn luyện trong dự án trước, phát hiện đối tượng không nhằm dự đoán thẻ tốt nhất cho toàn bộ hình ảnh, mà là tìm một hoặc nhiều đối tượng trong hình ảnh.

### Phát hiện đối tượng so với phân loại hình ảnh

Phân loại hình ảnh là việc phân loại toàn bộ hình ảnh - xác định xác suất rằng toàn bộ hình ảnh khớp với từng thẻ. Bạn nhận được các xác suất cho mỗi thẻ được sử dụng để huấn luyện mô hình.

![Phân loại hình ảnh hạt điều và sốt cà chua](../../../../../translated_images/vi/image-classifier-cashews-tomato.bc2e16ab8f05cf9a.webp)

Trong ví dụ trên, hai hình ảnh được phân loại bằng một mô hình được huấn luyện để phân loại hộp hạt điều hoặc lon sốt cà chua. Hình ảnh đầu tiên là một hộp hạt điều và có hai kết quả từ bộ phân loại hình ảnh:

| Thẻ            | Xác suất     |
| -------------- | ----------: |
| `hạt điều`     | 98.4%       |
| `sốt cà chua`  | 1.6%        |

Hình ảnh thứ hai là một lon sốt cà chua, và kết quả là:

| Thẻ            | Xác suất     |
| -------------- | ----------: |
| `hạt điều`     | 0.7%        |
| `sốt cà chua`  | 99.3%       |

Bạn có thể sử dụng các giá trị này với một ngưỡng phần trăm để dự đoán nội dung trong hình ảnh. Nhưng nếu một hình ảnh chứa nhiều lon sốt cà chua, hoặc cả hạt điều và sốt cà chua? Kết quả có thể không cung cấp cho bạn điều bạn muốn. Đây là lúc phát hiện đối tượng trở nên hữu ích.

Phát hiện đối tượng liên quan đến việc huấn luyện một mô hình để nhận diện các đối tượng. Thay vì cung cấp cho nó hình ảnh chứa đối tượng và nói rằng mỗi hình ảnh là một thẻ này hay thẻ khác, bạn làm nổi bật phần của hình ảnh chứa đối tượng cụ thể và gắn thẻ đó. Bạn có thể gắn thẻ một đối tượng duy nhất trong một hình ảnh hoặc nhiều đối tượng. Bằng cách này, mô hình học được hình dạng của chính đối tượng, không chỉ hình dạng của hình ảnh chứa đối tượng.

Khi bạn sử dụng nó để dự đoán hình ảnh, thay vì nhận được danh sách các thẻ và phần trăm, bạn nhận được danh sách các đối tượng được phát hiện, với hộp bao quanh và xác suất rằng hộp bao quanh khớp với thẻ được gắn.

> 🎓 *Hộp bao quanh* là các hộp xung quanh một đối tượng.

![Phát hiện đối tượng hạt điều và sốt cà chua](../../../../../translated_images/vi/object-detector-cashews-tomato.1af7c26686b4db0e.webp)

Hình ảnh trên chứa cả một hộp hạt điều và ba lon sốt cà chua. Bộ phát hiện đối tượng đã phát hiện hạt điều, trả về hộp bao quanh chứa hạt điều với xác suất rằng hộp bao quanh chứa đối tượng, trong trường hợp này là 97.6%. Bộ phát hiện đối tượng cũng đã phát hiện ba lon sốt cà chua và cung cấp ba hộp bao quanh riêng biệt, mỗi hộp cho một lon được phát hiện, và mỗi hộp có xác suất rằng hộp bao quanh chứa một lon sốt cà chua.

✅ Hãy nghĩ về một số tình huống khác mà bạn có thể muốn sử dụng các mô hình AI dựa trên hình ảnh. Tình huống nào cần phân loại, và tình huống nào cần phát hiện đối tượng?

### Cách hoạt động của phát hiện đối tượng

Phát hiện đối tượng sử dụng các mô hình ML phức tạp. Các mô hình này hoạt động bằng cách chia hình ảnh thành nhiều ô, sau đó kiểm tra xem trung tâm của hộp bao quanh có phải là trung tâm của một hình ảnh khớp với một trong các hình ảnh được sử dụng để huấn luyện mô hình hay không. Bạn có thể nghĩ về điều này như việc chạy một bộ phân loại hình ảnh trên các phần khác nhau của hình ảnh để tìm các kết quả khớp.

> 💁 Đây là một sự đơn giản hóa rất lớn. Có nhiều kỹ thuật để phát hiện đối tượng, và bạn có thể đọc thêm về chúng trên [trang Phát hiện đối tượng trên Wikipedia](https://wikipedia.org/wiki/Object_detection).

Có một số mô hình khác nhau có thể thực hiện phát hiện đối tượng. Một mô hình đặc biệt nổi tiếng là [YOLO (You only look once)](https://pjreddie.com/darknet/yolo/), rất nhanh và có thể phát hiện 20 loại đối tượng khác nhau, chẳng hạn như người, chó, chai và xe hơi.

✅ Đọc thêm về mô hình YOLO tại [pjreddie.com/darknet/yolo/](https://pjreddie.com/darknet/yolo/)

Các mô hình phát hiện đối tượng có thể được huấn luyện lại bằng cách sử dụng học chuyển giao để phát hiện các đối tượng tùy chỉnh.

## Sử dụng phát hiện đối tượng trong bán lẻ

Phát hiện đối tượng có nhiều ứng dụng trong bán lẻ. Một số bao gồm:

* **Kiểm tra và đếm hàng hóa** - nhận diện khi hàng hóa trên kệ bị thiếu. Nếu hàng hóa quá ít, thông báo có thể được gửi đến nhân viên hoặc robot để bổ sung kệ.
* **Phát hiện khẩu trang** - trong các cửa hàng có chính sách đeo khẩu trang trong các sự kiện sức khỏe cộng đồng, phát hiện đối tượng có thể nhận diện người có khẩu trang và người không có.
* **Thanh toán tự động** - phát hiện các mặt hàng được lấy khỏi kệ trong các cửa hàng tự động và tính phí khách hàng một cách phù hợp.
* **Phát hiện nguy hiểm** - nhận diện các vật dụng bị vỡ trên sàn, hoặc chất lỏng bị đổ, cảnh báo đội vệ sinh.

✅ Nghiên cứu thêm: Những ứng dụng khác của phát hiện đối tượng trong bán lẻ là gì?

## Huấn luyện bộ phát hiện đối tượng

Bạn có thể huấn luyện một bộ phát hiện đối tượng bằng Custom Vision, tương tự như cách bạn đã huấn luyện một bộ phân loại hình ảnh.

### Nhiệm vụ - tạo một bộ phát hiện đối tượng

1. Tạo một Nhóm Tài nguyên cho dự án này có tên `stock-detector`.

1. Tạo một tài nguyên huấn luyện Custom Vision miễn phí và một tài nguyên dự đoán Custom Vision miễn phí trong nhóm tài nguyên `stock-detector`. Đặt tên chúng là `stock-detector-training` và `stock-detector-prediction`.

    > 💁 Bạn chỉ có thể có một tài nguyên huấn luyện và dự đoán miễn phí, vì vậy hãy đảm bảo bạn đã dọn dẹp dự án từ các bài học trước.

    > ⚠️ Bạn có thể tham khảo [hướng dẫn tạo tài nguyên huấn luyện và dự đoán từ dự án 4, bài học 1 nếu cần](../../../4-manufacturing/lessons/1-train-fruit-detector/README.md#task---create-a-cognitive-services-resource).

1. Mở cổng Custom Vision tại [CustomVision.ai](https://customvision.ai), và đăng nhập bằng tài khoản Microsoft bạn đã sử dụng cho tài khoản Azure của mình.

1. Làm theo [phần Tạo một dự án mới trong hướng dẫn nhanh Xây dựng bộ phát hiện đối tượng trên tài liệu Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#create-a-new-project) để tạo một dự án Custom Vision mới. Giao diện người dùng có thể thay đổi và tài liệu này luôn là tài liệu tham khảo cập nhật nhất.

    Đặt tên dự án của bạn là `stock-detector`.

    Khi bạn tạo dự án, hãy đảm bảo sử dụng tài nguyên `stock-detector-training` bạn đã tạo trước đó. Sử dụng loại dự án *Phát hiện đối tượng* và miền *Sản phẩm trên kệ*.

    ![Cài đặt cho dự án Custom Vision với tên được đặt là fruit-quality-detector, không có mô tả, tài nguyên được đặt là fruit-quality-detector-training, loại dự án được đặt là phân loại, loại phân loại được đặt là đa lớp và miền được đặt là thực phẩm](../../../../../translated_images/vi/custom-vision-create-object-detector-project.32d4fb9aa8e7e737.webp)

    ✅ Miền sản phẩm trên kệ được thiết kế đặc biệt để phát hiện hàng hóa trên kệ cửa hàng. Đọc thêm về các miền khác nhau trong [tài liệu Chọn miền trên Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/select-domain?WT.mc_id=academic-17441-jabenn#object-detection)

✅ Dành thời gian khám phá giao diện người dùng Custom Vision cho bộ phát hiện đối tượng của bạn.

### Nhiệm vụ - huấn luyện bộ phát hiện đối tượng của bạn

Để huấn luyện mô hình của bạn, bạn sẽ cần một tập hợp hình ảnh chứa các đối tượng bạn muốn phát hiện.

1. Thu thập hình ảnh chứa đối tượng cần phát hiện. Bạn sẽ cần ít nhất 15 hình ảnh chứa mỗi đối tượng cần phát hiện từ nhiều góc độ khác nhau và trong các điều kiện ánh sáng khác nhau, nhưng càng nhiều càng tốt. Bộ phát hiện đối tượng này sử dụng miền *Sản phẩm trên kệ*, vì vậy hãy cố gắng sắp xếp các đối tượng như thể chúng đang ở trên kệ cửa hàng. Bạn cũng sẽ cần một vài hình ảnh để kiểm tra mô hình. Nếu bạn đang phát hiện nhiều hơn một đối tượng, bạn sẽ muốn một số hình ảnh kiểm tra chứa tất cả các đối tượng.

    > 💁 Hình ảnh chứa nhiều đối tượng khác nhau được tính vào số lượng tối thiểu 15 hình ảnh cho tất cả các đối tượng trong hình ảnh.

    Hình ảnh của bạn nên là png hoặc jpeg, nhỏ hơn 6MB. Nếu bạn tạo chúng bằng iPhone chẳng hạn, chúng có thể là hình ảnh HEIC độ phân giải cao, vì vậy sẽ cần được chuyển đổi và có thể thu nhỏ. Càng nhiều hình ảnh càng tốt, và bạn nên có số lượng tương tự cho cả trái cây chín và chưa chín.

    Mô hình được thiết kế cho sản phẩm trên kệ, vì vậy hãy cố gắng chụp ảnh các đối tượng trên kệ.

    Bạn có thể tìm thấy một số hình ảnh ví dụ mà bạn có thể sử dụng trong thư mục [images](../../../../../5-retail/lessons/1-train-stock-detector/images) của hạt điều và sốt cà chua mà bạn có thể sử dụng.

1. Làm theo [phần Tải lên và gắn thẻ hình ảnh trong hướng dẫn nhanh Xây dựng bộ phát hiện đối tượng trên tài liệu Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#upload-and-tag-images) để tải lên hình ảnh huấn luyện của bạn. Tạo các thẻ phù hợp tùy thuộc vào loại đối tượng bạn muốn phát hiện.

    ![Hộp thoại tải lên hiển thị việc tải lên hình ảnh chuối chín và chưa chín](../../../../../translated_images/vi/image-upload-object-detector.77c7892c3093cb59.webp)

    Khi bạn vẽ các hộp bao quanh cho các đối tượng, hãy giữ chúng chặt chẽ xung quanh đối tượng. Việc này có thể mất một thời gian để vẽ tất cả các hình ảnh, nhưng công cụ sẽ phát hiện những gì nó nghĩ là các hộp bao quanh, làm cho quá trình nhanh hơn.

    ![Gắn thẻ một số sốt cà chua](../../../../../translated_images/vi/object-detector-tag-tomato-paste.f47c362fb0f0eb58.webp)

    > 💁 Nếu bạn có hơn 15 hình ảnh cho mỗi đối tượng, bạn có thể huấn luyện sau 15 hình ảnh rồi sử dụng tính năng **Thẻ được đề xuất**. Tính năng này sẽ sử dụng mô hình đã huấn luyện để phát hiện các đối tượng trong hình ảnh chưa được gắn thẻ. Bạn có thể xác nhận các đối tượng được phát hiện hoặc từ chối và vẽ lại các hộp bao quanh. Điều này có thể tiết kiệm *rất nhiều* thời gian.

1. Làm theo [phần Huấn luyện bộ phát hiện trong hướng dẫn nhanh Xây dựng bộ phát hiện đối tượng trên tài liệu Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#train-the-detector) để huấn luyện bộ phát hiện đối tượng trên các hình ảnh đã gắn thẻ của bạn.

    Bạn sẽ được chọn loại huấn luyện. Chọn **Huấn luyện nhanh**.

Bộ phát hiện đối tượng sẽ bắt đầu huấn luyện. Quá trình này sẽ mất vài phút để hoàn thành.

## Kiểm tra bộ phát hiện đối tượng của bạn

Khi bộ phát hiện đối tượng của bạn đã được huấn luyện, bạn có thể kiểm tra nó bằng cách cung cấp các hình ảnh mới để phát hiện các đối tượng trong đó.

### Nhiệm vụ - kiểm tra bộ phát hiện đối tượng của bạn

1. Sử dụng nút **Kiểm tra nhanh** để tải lên hình ảnh kiểm tra và xác minh các đối tượng được phát hiện. Sử dụng các hình ảnh kiểm tra bạn đã tạo trước đó, không sử dụng bất kỳ hình ảnh nào bạn đã sử dụng để huấn luyện.

    ![3 lon sốt cà chua được phát hiện với xác suất lần lượt là 38%, 35.5% và 34.6%](../../../../../translated_images/vi/object-detector-detected-tomato-paste.52656fe87af4c37b.webp)

1. Thử tất cả các hình ảnh kiểm tra bạn có và quan sát các xác suất.

## Huấn luyện lại bộ phát hiện đối tượng của bạn

Khi bạn kiểm tra bộ phát hiện đối tượng của mình, nó có thể không đưa ra kết quả như mong đợi, giống như với các bộ phân loại hình ảnh trong dự án trước. Bạn có thể cải thiện bộ phát hiện đối tượng của mình bằng cách huấn luyện lại nó với các hình ảnh mà nó dự đoán sai.

Mỗi lần bạn thực hiện một dự đoán bằng tùy chọn kiểm tra nhanh, hình ảnh và kết quả sẽ được lưu trữ. Bạn có thể sử dụng các hình ảnh này để huấn luyện lại mô hình của mình.

1. Sử dụng tab **Dự đoán** để tìm các hình ảnh bạn đã sử dụng để kiểm tra.

1. Xác nhận bất kỳ phát hiện chính xác nào, xóa các phát hiện sai và thêm bất kỳ đối tượng nào bị thiếu.

1. Huấn luyện lại và kiểm tra lại mô hình.

---

## 🚀 Thử thách

Điều gì sẽ xảy ra nếu bạn sử dụng bộ phát hiện đối tượng với các mặt hàng có hình dáng tương tự, chẳng hạn như lon sốt cà chua và lon cà chua cắt nhỏ cùng thương hiệu?

Nếu bạn có bất kỳ mặt hàng nào có hình dáng tương tự, hãy thử nghiệm bằng cách thêm hình ảnh của chúng vào bộ phát hiện đối tượng của bạn.

## Câu hỏi sau bài giảng
[Quiz sau bài giảng](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/38)

## Ôn tập & Tự học

* Khi bạn huấn luyện bộ phát hiện đối tượng, bạn sẽ thấy các giá trị như *Precision* (Độ chính xác), *Recall* (Độ nhạy), và *mAP* (Mean Average Precision) để đánh giá mô hình đã được tạo ra. Hãy tìm hiểu thêm về các giá trị này bằng cách đọc [phần Đánh giá bộ phát hiện trong phần Bắt đầu nhanh: Xây dựng bộ phát hiện đối tượng trên tài liệu Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#evaluate-the-detector)
* Đọc thêm về phát hiện đối tượng trên [trang Phát hiện đối tượng trên Wikipedia](https://wikipedia.org/wiki/Object_detection)

## Bài tập

[So sánh các miền](assignment.md)

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.