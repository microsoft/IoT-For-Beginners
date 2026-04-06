# Huấn luyện bộ phát hiện chất lượng trái cây

![Tóm tắt bài học bằng hình vẽ](../../../../../translated_images/vi/lesson-15.843d21afdc6fb2bb.webp)

> Hình vẽ minh họa bởi [Nitya Narasimhan](https://github.com/nitya). Nhấp vào hình để xem phiên bản lớn hơn.

Video này cung cấp cái nhìn tổng quan về dịch vụ Azure Custom Vision, một dịch vụ sẽ được đề cập trong bài học này.

[![Custom Vision – Machine Learning Made Easy | The Xamarin Show](https://img.youtube.com/vi/TETcDLJlWR4/0.jpg)](https://www.youtube.com/watch?v=TETcDLJlWR4)

> 🎥 Nhấp vào hình trên để xem video

## Câu hỏi trước bài học

[Câu hỏi trước bài học](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/29)

## Giới thiệu

Sự phát triển gần đây của Trí tuệ Nhân tạo (AI) và Học máy (ML) đang mang lại nhiều khả năng đa dạng cho các nhà phát triển ngày nay. Các mô hình ML có thể được huấn luyện để nhận diện các đối tượng khác nhau trong hình ảnh, bao gồm cả trái cây chưa chín, và điều này có thể được sử dụng trong các thiết bị IoT để giúp phân loại nông sản khi thu hoạch hoặc trong quá trình xử lý tại nhà máy hoặc kho hàng.

Trong bài học này, bạn sẽ tìm hiểu về phân loại hình ảnh - sử dụng các mô hình ML để phân biệt giữa các hình ảnh của các đối tượng khác nhau. Bạn sẽ học cách huấn luyện một bộ phân loại hình ảnh để phân biệt giữa trái cây tốt và trái cây xấu, chẳng hạn như trái cây chưa chín, quá chín, bị dập hoặc bị thối.

Trong bài học này, chúng ta sẽ đề cập đến:

* [Sử dụng AI và ML để phân loại thực phẩm](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Phân loại hình ảnh qua Học máy](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Huấn luyện một bộ phân loại hình ảnh](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Kiểm tra bộ phân loại hình ảnh của bạn](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Huấn luyện lại bộ phân loại hình ảnh của bạn](../../../../../4-manufacturing/lessons/1-train-fruit-detector)

## Sử dụng AI và ML để phân loại thực phẩm

Nuôi sống dân số toàn cầu là một nhiệm vụ khó khăn, đặc biệt là với mức giá khiến thực phẩm trở nên phải chăng cho tất cả mọi người. Một trong những chi phí lớn nhất là lao động, vì vậy các nông dân ngày càng chuyển sang sử dụng tự động hóa và các công cụ như IoT để giảm chi phí lao động. Thu hoạch bằng tay rất tốn công (và thường là công việc nặng nhọc), và đang dần được thay thế bằng máy móc, đặc biệt ở các quốc gia giàu có. Mặc dù việc sử dụng máy móc để thu hoạch giúp tiết kiệm chi phí, nhưng có một nhược điểm - khả năng phân loại thực phẩm khi thu hoạch.

Không phải tất cả các loại cây trồng đều chín đều. Ví dụ, cà chua có thể vẫn còn một số quả xanh trên cây khi phần lớn đã sẵn sàng để thu hoạch. Mặc dù việc thu hoạch sớm những quả này là lãng phí, nhưng đối với nông dân, việc thu hoạch tất cả bằng máy móc và loại bỏ những quả chưa chín sau đó lại rẻ và dễ dàng hơn.

✅ Hãy quan sát các loại trái cây hoặc rau củ khác nhau, có thể đang được trồng gần bạn ở các trang trại hoặc trong vườn, hoặc trong các cửa hàng. Chúng có chín đều không, hay bạn thấy có sự khác biệt?

Sự phát triển của thu hoạch tự động đã chuyển việc phân loại nông sản từ giai đoạn thu hoạch sang nhà máy. Thực phẩm sẽ di chuyển trên các băng chuyền dài với các nhóm người nhặt ra những sản phẩm không đạt tiêu chuẩn chất lượng. Việc thu hoạch trở nên rẻ hơn nhờ máy móc, nhưng vẫn có chi phí cho việc phân loại thực phẩm thủ công.

![Nếu phát hiện cà chua đỏ, nó tiếp tục hành trình mà không bị gián đoạn. Nếu phát hiện cà chua xanh, nó sẽ bị gạt vào thùng rác bằng một cần gạt](../../../../../translated_images/vi/optical-tomato-sorting.61aa134bdda4e5b1.webp)

Sự phát triển tiếp theo là sử dụng máy móc để phân loại, hoặc được tích hợp vào máy thu hoạch, hoặc trong các nhà máy chế biến. Thế hệ đầu tiên của những máy này sử dụng cảm biến quang học để phát hiện màu sắc, điều khiển các bộ phận đẩy cà chua xanh vào thùng rác bằng cần gạt hoặc luồng khí, để lại cà chua đỏ tiếp tục trên mạng lưới băng chuyền.

Trong video này, khi cà chua rơi từ một băng chuyền sang băng chuyền khác, cà chua xanh được phát hiện và gạt vào thùng bằng cần gạt.

✅ Những điều kiện nào bạn cần trong nhà máy hoặc trên cánh đồng để các cảm biến quang học này hoạt động chính xác?

Sự phát triển mới nhất của các máy phân loại này tận dụng AI và ML, sử dụng các mô hình được huấn luyện để phân biệt nông sản tốt và xấu, không chỉ dựa vào sự khác biệt rõ ràng về màu sắc như cà chua xanh và đỏ, mà còn dựa vào những khác biệt tinh tế hơn trong hình dáng có thể chỉ ra bệnh hoặc vết dập.

## Phân loại hình ảnh qua Học máy

Lập trình truyền thống là khi bạn lấy dữ liệu, áp dụng một thuật toán vào dữ liệu, và nhận được kết quả đầu ra. Ví dụ, trong dự án trước, bạn đã lấy tọa độ GPS và một hàng rào địa lý, áp dụng một thuật toán được cung cấp bởi Azure Maps, và nhận được kết quả liệu điểm đó nằm trong hay ngoài hàng rào địa lý. Bạn nhập thêm dữ liệu, bạn nhận được thêm kết quả đầu ra.

![Phát triển truyền thống lấy đầu vào và thuật toán để cho ra đầu ra. Học máy sử dụng dữ liệu đầu vào và đầu ra đã biết để huấn luyện một mô hình, và mô hình này có thể nhận dữ liệu đầu vào mới để tạo ra đầu ra mới](../../../../../translated_images/vi/traditional-vs-ml.5c20c169621fa539.webp)

Học máy đảo ngược quy trình này - bạn bắt đầu với dữ liệu và các kết quả đầu ra đã biết, và thuật toán học máy sẽ học từ dữ liệu đó. Sau đó, bạn có thể sử dụng thuật toán đã được huấn luyện, gọi là *mô hình học máy* hoặc *mô hình*, và nhập dữ liệu mới để nhận được kết quả đầu ra mới.

> 🎓 Quá trình một thuật toán học máy học từ dữ liệu được gọi là *huấn luyện*. Các đầu vào và kết quả đầu ra đã biết được gọi là *dữ liệu huấn luyện*.

Ví dụ, bạn có thể cung cấp cho một mô hình hàng triệu bức ảnh chuối chưa chín làm dữ liệu huấn luyện đầu vào, với kết quả huấn luyện được đặt là `chưa chín`, và hàng triệu bức ảnh chuối chín làm dữ liệu huấn luyện với kết quả là `chín`. Thuật toán ML sau đó sẽ tạo ra một mô hình dựa trên dữ liệu này. Sau đó, bạn cung cấp cho mô hình này một bức ảnh mới của một quả chuối và nó sẽ dự đoán liệu bức ảnh mới là chuối chín hay chưa chín.

> 🎓 Kết quả của các mô hình ML được gọi là *dự đoán*

![2 quả chuối, một quả chín với dự đoán 99.7% chín, 0.3% chưa chín, và một quả chưa chín với dự đoán 1.4% chín, 98.6% chưa chín](../../../../../translated_images/vi/bananas-ripe-vs-unripe-predictions.8d0e2034014aa50e.webp)

Các mô hình ML không đưa ra câu trả lời nhị phân, thay vào đó chúng đưa ra xác suất. Ví dụ, một mô hình có thể được cung cấp một bức ảnh của một quả chuối và dự đoán `chín` với 99.7% và `chưa chín` với 0.3%. Mã của bạn sau đó sẽ chọn dự đoán tốt nhất và quyết định rằng quả chuối đã chín.

Mô hình ML được sử dụng để phát hiện hình ảnh như thế này được gọi là *bộ phân loại hình ảnh* - nó được cung cấp các hình ảnh có nhãn, và sau đó phân loại các hình ảnh mới dựa trên các nhãn này.

> 💁 Đây là một sự đơn giản hóa, và có nhiều cách khác để huấn luyện mô hình mà không cần các kết quả đầu ra có nhãn, chẳng hạn như học không giám sát. Nếu bạn muốn tìm hiểu thêm về ML, hãy tham khảo [ML for beginners, một chương trình học 24 bài về Học máy](https://aka.ms/ML-beginners).

## Huấn luyện một bộ phân loại hình ảnh

Để huấn luyện thành công một bộ phân loại hình ảnh, bạn cần hàng triệu hình ảnh. Tuy nhiên, khi bạn đã có một bộ phân loại hình ảnh được huấn luyện trên hàng triệu hoặc hàng tỷ hình ảnh đa dạng, bạn có thể tái sử dụng nó và huấn luyện lại nó bằng một tập hợp nhỏ hình ảnh để đạt được kết quả tốt, sử dụng một quy trình gọi là *học chuyển giao*.

> 🎓 Học chuyển giao là khi bạn chuyển giao kiến thức từ một mô hình ML hiện có sang một mô hình mới dựa trên dữ liệu mới.

Khi một bộ phân loại hình ảnh đã được huấn luyện cho một loạt hình ảnh đa dạng, các thành phần bên trong của nó rất giỏi trong việc nhận diện hình dạng, màu sắc và hoa văn. Học chuyển giao cho phép mô hình sử dụng những gì nó đã học được trong việc nhận diện các phần của hình ảnh, và sử dụng điều đó để nhận diện các hình ảnh mới.

![Khi bạn có thể nhận diện các hình dạng, chúng có thể được sắp xếp thành các cấu hình khác nhau để tạo thành một chiếc thuyền hoặc một con mèo](../../../../../translated_images/vi/shapes-to-images.1a309f0ea88dd66f.webp)

Bạn có thể nghĩ về điều này giống như sách hình dạng dành cho trẻ em, nơi mà khi bạn có thể nhận diện một nửa hình tròn, một hình chữ nhật và một hình tam giác, bạn có thể nhận diện một chiếc thuyền buồm hoặc một con mèo tùy thuộc vào cách sắp xếp các hình dạng này. Bộ phân loại hình ảnh có thể nhận diện các hình dạng, và học chuyển giao dạy nó cách kết hợp nào tạo thành một chiếc thuyền hoặc một con mèo - hoặc một quả chuối chín.

Có rất nhiều công cụ có thể giúp bạn làm điều này, bao gồm các dịch vụ dựa trên đám mây có thể giúp bạn huấn luyện mô hình của mình, sau đó sử dụng nó qua các API web.

> 💁 Việc huấn luyện các mô hình này cần rất nhiều sức mạnh tính toán, thường thông qua các Đơn vị Xử lý Đồ họa (GPU). Phần cứng chuyên dụng tương tự làm cho các trò chơi trên Xbox của bạn trông tuyệt vời cũng có thể được sử dụng để huấn luyện các mô hình học máy. Bằng cách sử dụng đám mây, bạn có thể thuê thời gian trên các máy tính mạnh mẽ với GPU để huấn luyện các mô hình này, có được sức mạnh tính toán bạn cần, chỉ trong thời gian bạn cần.

## Custom Vision

Custom Vision là một công cụ dựa trên đám mây để huấn luyện các bộ phân loại hình ảnh. Nó cho phép bạn huấn luyện một bộ phân loại chỉ với một số lượng nhỏ hình ảnh. Bạn có thể tải lên hình ảnh qua cổng web, API web hoặc SDK, gán cho mỗi hình ảnh một *thẻ* đại diện cho phân loại của hình ảnh đó. Sau đó, bạn huấn luyện mô hình và kiểm tra nó để xem hiệu suất của nó. Khi bạn hài lòng với mô hình, bạn có thể xuất bản các phiên bản của nó để truy cập qua API web hoặc SDK.

![Logo Azure Custom Vision](../../../../../translated_images/vi/custom-vision-logo.d3d4e7c8a87ec9da.webp)

> 💁 Bạn có thể huấn luyện một mô hình Custom Vision chỉ với 5 hình ảnh cho mỗi phân loại, nhưng càng nhiều càng tốt. Bạn sẽ có kết quả tốt hơn với ít nhất 30 hình ảnh.

Custom Vision là một phần của một loạt các công cụ AI từ Microsoft gọi là Cognitive Services. Đây là các công cụ AI có thể được sử dụng mà không cần huấn luyện hoặc chỉ cần một lượng nhỏ huấn luyện. Chúng bao gồm nhận diện và dịch giọng nói, hiểu ngôn ngữ và phân tích hình ảnh. Các công cụ này có sẵn với một gói miễn phí như các dịch vụ trong Azure.

> 💁 Gói miễn phí là đủ để tạo một mô hình, huấn luyện nó, sau đó sử dụng nó cho công việc phát triển. Bạn có thể đọc về giới hạn của gói miễn phí trên [trang Giới hạn và hạn mức của Custom Vision trên tài liệu Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/limits-and-quotas?WT.mc_id=academic-17441-jabenn).

### Nhiệm vụ - tạo một tài nguyên Cognitive Services

Để sử dụng Custom Vision, trước tiên bạn cần tạo hai tài nguyên Cognitive Services trong Azure bằng Azure CLI, một cho huấn luyện Custom Vision và một cho dự đoán Custom Vision.

1. Tạo một Nhóm Tài nguyên cho dự án này có tên `fruit-quality-detector`.

1. Sử dụng lệnh sau để tạo một tài nguyên huấn luyện Custom Vision miễn phí:

    ```sh
    az cognitiveservices account create --name fruit-quality-detector-training \
                                        --resource-group fruit-quality-detector \
                                        --kind CustomVision.Training \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Thay `<location>` bằng vị trí bạn đã sử dụng khi tạo Nhóm Tài nguyên.

    Lệnh này sẽ tạo một tài nguyên huấn luyện Custom Vision trong Nhóm Tài nguyên của bạn. Nó sẽ được gọi là `fruit-quality-detector-training` và sử dụng SKU `F0`, là gói miễn phí. Tùy chọn `--yes` có nghĩa là bạn đồng ý với các điều khoản và điều kiện của dịch vụ Cognitive Services.

> 💁 Sử dụng SKU `S0` nếu bạn đã có một tài khoản miễn phí sử dụng bất kỳ dịch vụ Cognitive Services nào.

1. Sử dụng lệnh sau để tạo một tài nguyên dự đoán Custom Vision miễn phí:

    ```sh
    az cognitiveservices account create --name fruit-quality-detector-prediction \
                                        --resource-group fruit-quality-detector \
                                        --kind CustomVision.Prediction \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Thay `<location>` bằng vị trí bạn đã sử dụng khi tạo Nhóm Tài nguyên.

    Lệnh này sẽ tạo một tài nguyên dự đoán Custom Vision trong Nhóm Tài nguyên của bạn. Nó sẽ được gọi là `fruit-quality-detector-prediction` và sử dụng SKU `F0`, là gói miễn phí. Tùy chọn `--yes` có nghĩa là bạn đồng ý với các điều khoản và điều kiện của dịch vụ Cognitive Services.

### Nhiệm vụ - tạo một dự án bộ phân loại hình ảnh

1. Truy cập cổng Custom Vision tại [CustomVision.ai](https://customvision.ai), và đăng nhập bằng tài khoản Microsoft bạn đã sử dụng cho tài khoản Azure của mình.

1. Làm theo [phần tạo một dự án mới trong hướng dẫn nhanh xây dựng bộ phân loại trên tài liệu Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#create-a-new-project) để tạo một dự án Custom Vision mới. Giao diện người dùng có thể thay đổi và tài liệu này luôn là tài liệu tham khảo cập nhật nhất.

    Đặt tên dự án của bạn là `fruit-quality-detector`.

    Khi bạn tạo dự án, hãy chắc chắn sử dụng tài nguyên `fruit-quality-detector-training` mà bạn đã tạo trước đó. Sử dụng loại dự án *Classification*, loại phân loại *Multiclass*, và miền *Food*.

    ![Cài đặt cho dự án Custom Vision với tên được đặt là fruit-quality-detector, không có mô tả, tài nguyên được đặt là fruit-quality-detector-training, loại dự án được đặt là classification, loại phân loại được đặt là multi class và miền được đặt là food](../../../../../translated_images/vi/custom-vision-create-project.cf46325b92d8b131.webp)

✅ Dành thời gian để khám phá giao diện người dùng Custom Vision cho bộ phân loại hình ảnh của bạn.

### Nhiệm vụ - huấn luyện dự án bộ phân loại hình ảnh của bạn

Để huấn luyện một bộ phân loại hình ảnh, bạn sẽ cần nhiều bức ảnh về trái cây, cả chất lượng tốt và xấu để gắn thẻ là tốt và xấu, chẳng hạn như một quả chuối chín và một quả chuối quá chín.
💁 Những bộ phân loại này có thể phân loại hình ảnh của bất kỳ thứ gì, vì vậy nếu bạn không có trái cây với chất lượng khác nhau, bạn có thể sử dụng hai loại trái cây khác nhau, hoặc mèo và chó!
Mỗi bức ảnh lý tưởng nên chỉ có hình quả, với nền đồng nhất hoặc đa dạng. Đảm bảo không có gì trong nền liên quan đến trạng thái chín hay chưa chín của quả.

> 💁 Điều quan trọng là không có nền cụ thể hoặc các vật thể không liên quan đến thứ đang được phân loại trong mỗi nhãn, nếu không bộ phân loại có thể chỉ phân loại dựa trên nền. Đã từng có một bộ phân loại ung thư da được huấn luyện trên các nốt ruồi bình thường và ung thư, và các nốt ung thư đều có thước đo kích thước bên cạnh. Kết quả là bộ phân loại gần như chính xác 100% trong việc nhận diện thước đo trong ảnh, chứ không phải nốt ruồi ung thư.

Bộ phân loại hình ảnh hoạt động ở độ phân giải rất thấp. Ví dụ, Custom Vision có thể nhận ảnh huấn luyện và dự đoán lên đến 10240x10240, nhưng huấn luyện và chạy mô hình trên ảnh ở kích thước 227x227. Các ảnh lớn hơn sẽ được thu nhỏ về kích thước này, vì vậy hãy đảm bảo đối tượng bạn đang phân loại chiếm phần lớn trong ảnh, nếu không nó có thể quá nhỏ trong ảnh nhỏ được sử dụng bởi bộ phân loại.

1. Thu thập ảnh cho bộ phân loại của bạn. Bạn sẽ cần ít nhất 5 ảnh cho mỗi nhãn để huấn luyện bộ phân loại, nhưng càng nhiều càng tốt. Bạn cũng sẽ cần một vài ảnh bổ sung để kiểm tra bộ phân loại. Những ảnh này nên là các ảnh khác nhau của cùng một đối tượng. Ví dụ:

    * Sử dụng 2 quả chuối chín, chụp một số ảnh của mỗi quả từ các góc độ khác nhau, chụp ít nhất 7 ảnh (5 để huấn luyện, 2 để kiểm tra), nhưng lý tưởng là nhiều hơn.

        ![Ảnh của 2 quả chuối khác nhau](../../../../../translated_images/vi/banana-training-images.530eb203346d73bc.webp)

    * Lặp lại quy trình tương tự với 2 quả chuối chưa chín.

    Bạn nên có ít nhất 10 ảnh huấn luyện, với ít nhất 5 ảnh chuối chín và 5 ảnh chuối chưa chín, và 4 ảnh kiểm tra, 2 ảnh chuối chín, 2 ảnh chuối chưa chín. Ảnh của bạn nên ở định dạng png hoặc jpeg, nhỏ hơn 6MB. Nếu bạn tạo ảnh bằng iPhone chẳng hạn, chúng có thể là ảnh HEIC độ phân giải cao, vì vậy cần được chuyển đổi và có thể thu nhỏ. Càng nhiều ảnh càng tốt, và bạn nên có số lượng ảnh chuối chín và chưa chín tương đương.

    Nếu bạn không có cả chuối chín và chưa chín, bạn có thể sử dụng các loại quả khác, hoặc bất kỳ hai vật thể nào bạn có sẵn. Bạn cũng có thể tìm một số ảnh mẫu trong thư mục [images](../../../../../4-manufacturing/lessons/1-train-fruit-detector/images) của chuối chín và chưa chín mà bạn có thể sử dụng.

1. Thực hiện theo [phần tải lên và gắn thẻ ảnh trong hướng dẫn nhanh xây dựng bộ phân loại trên tài liệu Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#upload-and-tag-images) để tải lên ảnh huấn luyện của bạn. Gắn thẻ quả chín là `ripe`, và quả chưa chín là `unripe`.

    ![Hộp thoại tải lên hiển thị việc tải ảnh chuối chín và chưa chín](../../../../../translated_images/vi/image-upload-bananas.0751639f3815e0ec.webp)

1. Thực hiện theo [phần huấn luyện bộ phân loại trong hướng dẫn nhanh xây dựng bộ phân loại trên tài liệu Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#train-the-classifier) để huấn luyện bộ phân loại hình ảnh trên các ảnh đã tải lên.

    Bạn sẽ được chọn loại huấn luyện. Chọn **Quick Training**.

Bộ phân loại sau đó sẽ được huấn luyện. Quá trình này sẽ mất vài phút để hoàn thành.

> 🍌 Nếu bạn quyết định ăn quả trong khi bộ phân loại đang huấn luyện, hãy đảm bảo bạn có đủ ảnh để kiểm tra trước!

## Kiểm tra bộ phân loại hình ảnh của bạn

Khi bộ phân loại của bạn đã được huấn luyện, bạn có thể kiểm tra nó bằng cách cung cấp một ảnh mới để phân loại.

### Nhiệm vụ - kiểm tra bộ phân loại hình ảnh của bạn

1. Thực hiện theo [tài liệu kiểm tra mô hình trên tài liệu Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/test-your-model?WT.mc_id=academic-17441-jabenn#test-your-model) để kiểm tra bộ phân loại hình ảnh của bạn. Sử dụng các ảnh kiểm tra bạn đã tạo trước đó, không sử dụng bất kỳ ảnh nào bạn đã dùng để huấn luyện.

    ![Một quả chuối chưa chín được dự đoán là chưa chín với xác suất 98.9%, chín với xác suất 1.1%](../../../../../translated_images/vi/banana-unripe-quick-test-prediction.dae9b5e1c4ef7c64.webp)

1. Thử tất cả các ảnh kiểm tra bạn có và quan sát các xác suất.

## Huấn luyện lại bộ phân loại hình ảnh của bạn

Khi bạn kiểm tra bộ phân loại, nó có thể không đưa ra kết quả như mong đợi. Bộ phân loại hình ảnh sử dụng học máy để đưa ra dự đoán về những gì có trong ảnh, dựa trên xác suất rằng các đặc điểm cụ thể của ảnh có nghĩa là nó khớp với một nhãn cụ thể. Nó không hiểu những gì có trong ảnh - nó không biết chuối là gì hoặc hiểu điều gì làm cho một quả chuối là chuối thay vì một chiếc thuyền. Bạn có thể cải thiện bộ phân loại của mình bằng cách huấn luyện lại nó với các ảnh mà nó dự đoán sai.

Mỗi lần bạn thực hiện một dự đoán bằng tùy chọn kiểm tra nhanh, ảnh và kết quả sẽ được lưu trữ. Bạn có thể sử dụng các ảnh này để huấn luyện lại mô hình của mình.

### Nhiệm vụ - huấn luyện lại bộ phân loại hình ảnh của bạn

1. Thực hiện theo [tài liệu sử dụng ảnh dự đoán để huấn luyện trên tài liệu Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/test-your-model?WT.mc_id=academic-17441-jabenn#use-the-predicted-image-for-training) để huấn luyện lại mô hình của bạn, sử dụng nhãn đúng cho mỗi ảnh.

1. Khi mô hình của bạn đã được huấn luyện lại, kiểm tra với các ảnh mới.

---

## 🚀 Thử thách

Bạn nghĩ điều gì sẽ xảy ra nếu bạn sử dụng một bức ảnh dâu tây với mô hình được huấn luyện trên chuối, hoặc một bức ảnh chuối bơm hơi, hoặc một người mặc bộ đồ chuối, hoặc thậm chí một nhân vật hoạt hình màu vàng như ai đó trong gia đình Simpsons?

Hãy thử và xem các dự đoán là gì. Bạn có thể tìm ảnh để thử nghiệm bằng [Bing Image search](https://www.bing.com/images/trending).

## Câu hỏi sau bài giảng

[Câu hỏi sau bài giảng](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/30)

## Ôn tập & Tự học

* Khi bạn huấn luyện bộ phân loại của mình, bạn sẽ thấy các giá trị *Precision*, *Recall*, và *AP* đánh giá mô hình được tạo ra. Tìm hiểu về các giá trị này bằng cách đọc [phần đánh giá bộ phân loại trong hướng dẫn nhanh xây dựng bộ phân loại trên tài liệu Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#evaluate-the-classifier)
* Tìm hiểu cách cải thiện bộ phân loại của bạn từ [cách cải thiện mô hình Custom Vision trên tài liệu Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-improving-your-classifier?WT.mc_id=academic-17441-jabenn)

## Bài tập

[Huấn luyện bộ phân loại của bạn cho nhiều loại trái cây và rau củ](assignment.md)

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, nên sử dụng dịch vụ dịch thuật chuyên nghiệp từ con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.