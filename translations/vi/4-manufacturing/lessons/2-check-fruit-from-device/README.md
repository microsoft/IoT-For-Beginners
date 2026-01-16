<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "557f4ee96b752e0651d2e6e74aa6bd14",
  "translation_date": "2025-08-27T20:55:39+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/README.md",
  "language_code": "vi"
}
-->
# Kiểm tra chất lượng trái cây từ thiết bị IoT

![Tổng quan bài học qua sketchnote](../../../../../translated_images/vi/lesson-16.215daf18b00631fbdfd64c6fc2dc6044dff5d544288825d8076f9fb83d964c23.jpg)

> Sketchnote bởi [Nitya Narasimhan](https://github.com/nitya). Nhấp vào hình ảnh để xem phiên bản lớn hơn.

## Câu hỏi trước bài giảng

[Câu hỏi trước bài giảng](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/31)

## Giới thiệu

Trong bài học trước, bạn đã tìm hiểu về bộ phân loại hình ảnh và cách huấn luyện chúng để phát hiện trái cây tốt và xấu. Để sử dụng bộ phân loại hình ảnh này trong một ứng dụng IoT, bạn cần có khả năng chụp hình ảnh bằng một loại camera nào đó và gửi hình ảnh này lên đám mây để phân loại.

Trong bài học này, bạn sẽ tìm hiểu về cảm biến camera và cách sử dụng chúng với thiết bị IoT để chụp hình ảnh. Bạn cũng sẽ học cách gọi bộ phân loại hình ảnh từ thiết bị IoT của mình.

Trong bài học này, chúng ta sẽ đề cập đến:

* [Cảm biến camera](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Chụp hình ảnh bằng thiết bị IoT](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Xuất bản bộ phân loại hình ảnh của bạn](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Phân loại hình ảnh từ thiết bị IoT của bạn](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Cải thiện mô hình](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)

## Cảm biến camera

Cảm biến camera, như tên gọi, là các camera mà bạn có thể kết nối với thiết bị IoT của mình. Chúng có thể chụp ảnh tĩnh hoặc quay video trực tiếp. Một số sẽ trả về dữ liệu hình ảnh thô, trong khi những loại khác sẽ nén dữ liệu hình ảnh thành tệp hình ảnh như JPEG hoặc PNG. Thông thường, các camera hoạt động với thiết bị IoT nhỏ hơn và có độ phân giải thấp hơn so với những gì bạn có thể quen thuộc, nhưng bạn cũng có thể tìm thấy các camera có độ phân giải cao tương đương với các điện thoại cao cấp. Bạn có thể sử dụng nhiều loại ống kính thay thế, thiết lập nhiều camera, camera nhiệt hồng ngoại hoặc camera UV.

![Ánh sáng từ một cảnh đi qua ống kính và được tập trung vào cảm biến CMOS](../../../../../translated_images/vi/cmos-sensor.75f9cd74decb137149a4c9ea825251a4549497d67c0ae2776159e6102bb53aa9.png)

Hầu hết các cảm biến camera sử dụng cảm biến hình ảnh, nơi mỗi pixel là một photodiode. Một ống kính tập trung hình ảnh lên cảm biến hình ảnh, và hàng ngàn hoặc hàng triệu photodiode phát hiện ánh sáng chiếu vào từng cái và ghi lại dưới dạng dữ liệu pixel.

> 💁 Ống kính làm đảo ngược hình ảnh, sau đó cảm biến camera lật hình ảnh lại đúng chiều. Điều này cũng giống như trong mắt bạn - những gì bạn nhìn thấy được phát hiện ngược trên mặt sau của mắt và não của bạn sẽ điều chỉnh lại.

> 🎓 Cảm biến hình ảnh được gọi là Cảm biến Pixel Hoạt động (APS), và loại APS phổ biến nhất là cảm biến bán dẫn oxit kim loại bổ sung, hay CMOS. Bạn có thể đã nghe thuật ngữ cảm biến CMOS được sử dụng cho cảm biến camera.

Cảm biến camera là cảm biến kỹ thuật số, gửi dữ liệu hình ảnh dưới dạng dữ liệu kỹ thuật số, thường với sự hỗ trợ của một thư viện cung cấp giao tiếp. Camera kết nối bằng các giao thức như SPI để cho phép chúng gửi lượng lớn dữ liệu - hình ảnh lớn hơn đáng kể so với các số liệu đơn lẻ từ cảm biến như cảm biến nhiệt độ.

✅ Những hạn chế nào liên quan đến kích thước hình ảnh với thiết bị IoT? Hãy suy nghĩ về các giới hạn, đặc biệt là trên phần cứng vi điều khiển.

## Chụp hình ảnh bằng thiết bị IoT

Bạn có thể sử dụng thiết bị IoT của mình để chụp hình ảnh để phân loại.

### Nhiệm vụ - chụp hình ảnh bằng thiết bị IoT

Thực hiện theo hướng dẫn liên quan để chụp hình ảnh bằng thiết bị IoT của bạn:

* [Arduino - Wio Terminal](wio-terminal-camera.md)
* [Máy tính đơn bảng - Raspberry Pi](pi-camera.md)
* [Máy tính đơn bảng - Thiết bị ảo](virtual-device-camera.md)

## Xuất bản bộ phân loại hình ảnh của bạn

Bạn đã huấn luyện bộ phân loại hình ảnh của mình trong bài học trước. Trước khi bạn có thể sử dụng nó từ thiết bị IoT của mình, bạn cần xuất bản mô hình.

### Các lần lặp mô hình

Khi mô hình của bạn được huấn luyện trong bài học trước, bạn có thể nhận thấy rằng tab **Hiệu suất** hiển thị các lần lặp ở bên cạnh. Khi bạn lần đầu tiên huấn luyện mô hình, bạn sẽ thấy *Lần lặp 1* trong quá trình huấn luyện. Khi bạn cải thiện mô hình bằng cách sử dụng hình ảnh dự đoán, bạn sẽ thấy *Lần lặp 2* trong quá trình huấn luyện.

Mỗi lần bạn huấn luyện mô hình, bạn sẽ có một lần lặp mới. Đây là cách để theo dõi các phiên bản khác nhau của mô hình được huấn luyện trên các tập dữ liệu khác nhau. Khi bạn thực hiện **Kiểm tra nhanh**, có một menu thả xuống mà bạn có thể sử dụng để chọn lần lặp, để bạn có thể so sánh kết quả giữa nhiều lần lặp.

Khi bạn hài lòng với một lần lặp, bạn có thể xuất bản nó để làm cho nó có thể được sử dụng từ các ứng dụng bên ngoài. Bằng cách này, bạn có thể có một phiên bản đã xuất bản được sử dụng bởi các thiết bị của bạn, sau đó làm việc trên một phiên bản mới qua nhiều lần lặp, sau đó xuất bản nó khi bạn hài lòng với nó.

### Nhiệm vụ - xuất bản một lần lặp

Các lần lặp được xuất bản từ cổng Custom Vision.

1. Mở cổng Custom Vision tại [CustomVision.ai](https://customvision.ai) và đăng nhập nếu bạn chưa mở nó. Sau đó mở dự án `fruit-quality-detector` của bạn.

1. Chọn tab **Hiệu suất** từ các tùy chọn ở trên cùng.

1. Chọn lần lặp mới nhất từ danh sách *Lần lặp* ở bên cạnh.

1. Chọn nút **Xuất bản** cho lần lặp.

    ![Nút xuất bản](../../../../../translated_images/vi/custom-vision-publish-button.b7174e1977b0c33b8b72d4e5b1326c779e0af196f3849d09985ee2d7d5493a39.png)

1. Trong hộp thoại *Xuất bản mô hình*, đặt *Nguồn dự đoán* thành tài nguyên `fruit-quality-detector-prediction` mà bạn đã tạo trong bài học trước. Giữ tên là `Iteration2`, và chọn nút **Xuất bản**.

1. Sau khi xuất bản, chọn nút **URL dự đoán**. Điều này sẽ hiển thị chi tiết của API dự đoán, và bạn sẽ cần những thông tin này để gọi mô hình từ thiết bị IoT của mình. Phần dưới được gắn nhãn *Nếu bạn có một tệp hình ảnh*, và đây là chi tiết bạn cần. Sao chép URL được hiển thị, sẽ giống như:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/classify/iterations/Iteration2/image
    ```

    Trong đó `<location>` sẽ là vị trí bạn đã sử dụng khi tạo tài nguyên Custom Vision của mình, và `<id>` sẽ là một ID dài gồm các chữ cái và số.

    Cũng sao chép giá trị *Prediction-Key*. Đây là một khóa bảo mật mà bạn phải truyền khi gọi mô hình. Chỉ các ứng dụng truyền khóa này mới được phép sử dụng mô hình, các ứng dụng khác sẽ bị từ chối.

    ![Hộp thoại API dự đoán hiển thị URL và khóa](../../../../../translated_images/vi/custom-vision-prediction-key-endpoint.30c569ffd0338864f319911f052d5e9b8c5066cb0800a26dd6f7ff5713130ad8.png)

✅ Khi một lần lặp mới được xuất bản, nó sẽ có một tên khác. Bạn nghĩ làm thế nào để thay đổi lần lặp mà thiết bị IoT đang sử dụng?

## Phân loại hình ảnh từ thiết bị IoT của bạn

Bây giờ bạn có thể sử dụng các chi tiết kết nối này để gọi bộ phân loại hình ảnh từ thiết bị IoT của mình.

### Nhiệm vụ - phân loại hình ảnh từ thiết bị IoT của bạn

Thực hiện theo hướng dẫn liên quan để phân loại hình ảnh bằng thiết bị IoT của bạn:

* [Arduino - Wio Terminal](wio-terminal-classify-image.md)
* [Máy tính đơn bảng - Raspberry Pi/Thiết bị IoT ảo](single-board-computer-classify-image.md)

## Cải thiện mô hình

Bạn có thể nhận thấy rằng kết quả bạn nhận được khi sử dụng camera kết nối với thiết bị IoT của mình không khớp với những gì bạn mong đợi. Các dự đoán không phải lúc nào cũng chính xác như khi sử dụng hình ảnh tải lên từ máy tính của bạn. Điều này là do mô hình được huấn luyện trên dữ liệu khác với dữ liệu được sử dụng để dự đoán.

Để có kết quả tốt nhất cho bộ phân loại hình ảnh, bạn muốn huấn luyện mô hình với các hình ảnh càng giống với hình ảnh được sử dụng để dự đoán càng tốt. Nếu bạn sử dụng camera điện thoại của mình để chụp hình ảnh để huấn luyện, ví dụ, chất lượng hình ảnh, độ sắc nét và màu sắc sẽ khác với camera kết nối với thiết bị IoT.

![2 hình ảnh quả chuối, một hình ảnh có độ phân giải thấp với ánh sáng kém từ thiết bị IoT, và một hình ảnh có độ phân giải cao với ánh sáng tốt từ điện thoại](../../../../../translated_images/vi/banana-picture-compare.174df164dc326a42cf7fb051a7497e6113c620e91552d92ca914220305d47d9a.png)

Trong hình ảnh trên, hình ảnh quả chuối bên trái được chụp bằng Camera Raspberry Pi, hình ảnh bên phải được chụp cùng quả chuối ở cùng vị trí bằng iPhone. Có sự khác biệt rõ rệt về chất lượng - hình ảnh iPhone sắc nét hơn, với màu sắc sáng hơn và độ tương phản cao hơn.

✅ Điều gì khác có thể khiến hình ảnh được chụp bởi thiết bị IoT của bạn có dự đoán không chính xác? Hãy suy nghĩ về môi trường mà thiết bị IoT có thể được sử dụng, những yếu tố nào có thể ảnh hưởng đến hình ảnh được chụp?

Để cải thiện mô hình, bạn có thể huấn luyện lại nó bằng cách sử dụng hình ảnh được chụp từ thiết bị IoT.

### Nhiệm vụ - cải thiện mô hình

1. Phân loại nhiều hình ảnh của cả trái cây chín và chưa chín bằng thiết bị IoT của bạn.

1. Trong cổng Custom Vision, huấn luyện lại mô hình bằng cách sử dụng hình ảnh trên tab *Dự đoán*.

    > ⚠️ Bạn có thể tham khảo [hướng dẫn huấn luyện lại bộ phân loại của bạn trong bài học 1 nếu cần](../1-train-fruit-detector/README.md#retrain-your-image-classifier).

1. Nếu hình ảnh của bạn trông rất khác so với những hình ảnh ban đầu được sử dụng để huấn luyện, bạn có thể xóa tất cả các hình ảnh ban đầu bằng cách chọn chúng trong tab *Hình ảnh huấn luyện* và chọn nút **Xóa**. Để chọn một hình ảnh, di chuyển con trỏ của bạn qua nó và một dấu tick sẽ xuất hiện, chọn dấu tick đó để chọn hoặc bỏ chọn hình ảnh.

1. Huấn luyện một lần lặp mới của mô hình và xuất bản nó bằng các bước ở trên.

1. Cập nhật URL điểm cuối trong mã của bạn và chạy lại ứng dụng.

1. Lặp lại các bước này cho đến khi bạn hài lòng với kết quả của các dự đoán.

---

## 🚀 Thử thách

Độ phân giải hình ảnh hoặc ánh sáng ảnh hưởng đến dự đoán như thế nào?

Hãy thử thay đổi độ phân giải của hình ảnh trong mã thiết bị của bạn và xem liệu nó có tạo ra sự khác biệt đối với chất lượng hình ảnh hay không. Cũng thử thay đổi ánh sáng.

Nếu bạn tạo một thiết bị sản xuất để bán cho các trang trại hoặc nhà máy, bạn sẽ đảm bảo nó cho kết quả nhất quán mọi lúc như thế nào?

## Câu hỏi sau bài giảng

[Câu hỏi sau bài giảng](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/32)

## Ôn tập & Tự học

Bạn đã huấn luyện mô hình Custom Vision của mình bằng cổng. Điều này dựa vào việc có hình ảnh sẵn có - và trong thực tế, bạn có thể không thể lấy dữ liệu huấn luyện phù hợp với những gì camera trên thiết bị của bạn chụp. Bạn có thể khắc phục điều này bằng cách huấn luyện trực tiếp từ thiết bị của bạn bằng API huấn luyện, để huấn luyện một mô hình sử dụng hình ảnh được chụp từ thiết bị IoT của bạn.

* Đọc thêm về API huấn luyện trong [hướng dẫn bắt đầu nhanh sử dụng SDK Custom Vision](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/quickstarts/image-classification?WT.mc_id=academic-17441-jabenn&tabs=visual-studio&pivots=programming-language-python)

## Bài tập

[Phản hồi kết quả phân loại](assignment.md)

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.