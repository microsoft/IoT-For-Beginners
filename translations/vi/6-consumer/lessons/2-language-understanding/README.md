# Hiểu ngôn ngữ

![Tổng quan bài học dưới dạng sketchnote](../../../../../translated_images/vi/lesson-22.6148ea28500d9e00.webp)

> Sketchnote bởi [Nitya Narasimhan](https://github.com/nitya). Nhấp vào hình ảnh để xem phiên bản lớn hơn.

## Câu hỏi trước bài giảng

[Câu hỏi trước bài giảng](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/43)

## Giới thiệu

Trong bài học trước, bạn đã chuyển đổi giọng nói thành văn bản. Để sử dụng điều này để lập trình một bộ hẹn giờ thông minh, mã của bạn cần phải hiểu được những gì đã được nói. Bạn có thể giả định rằng người dùng sẽ nói một cụm từ cố định, chẳng hạn như "Đặt hẹn giờ 3 phút", và phân tích cụm từ đó để biết thời gian hẹn giờ, nhưng điều này không thân thiện với người dùng. Nếu người dùng nói "Đặt hẹn giờ trong 3 phút", bạn hoặc tôi sẽ hiểu ý nghĩa của họ, nhưng mã của bạn thì không, vì nó đang mong đợi một cụm từ cố định.

Đây là lúc hiểu ngôn ngữ xuất hiện, sử dụng các mô hình AI để diễn giải văn bản và trả về các chi tiết cần thiết, ví dụ như có thể hiểu cả "Đặt hẹn giờ 3 phút" và "Đặt hẹn giờ trong 3 phút", và nhận ra rằng cần đặt hẹn giờ trong 3 phút.

Trong bài học này, bạn sẽ tìm hiểu về các mô hình hiểu ngôn ngữ, cách tạo, huấn luyện và sử dụng chúng từ mã của bạn.

Trong bài học này, chúng ta sẽ đề cập đến:

* [Hiểu ngôn ngữ](../../../../../6-consumer/lessons/2-language-understanding)
* [Tạo mô hình hiểu ngôn ngữ](../../../../../6-consumer/lessons/2-language-understanding)
* [Ý định và thực thể](../../../../../6-consumer/lessons/2-language-understanding)
* [Sử dụng mô hình hiểu ngôn ngữ](../../../../../6-consumer/lessons/2-language-understanding)

## Hiểu ngôn ngữ

Con người đã sử dụng ngôn ngữ để giao tiếp hàng trăm ngàn năm. Chúng ta giao tiếp bằng từ ngữ, âm thanh hoặc hành động và hiểu được những gì được nói, không chỉ ý nghĩa của từ ngữ, âm thanh hoặc hành động, mà còn cả ngữ cảnh của chúng. Chúng ta hiểu được sự chân thành và sự mỉa mai, cho phép cùng một từ ngữ mang ý nghĩa khác nhau tùy thuộc vào giọng điệu của chúng ta.

✅ Hãy nghĩ về một số cuộc trò chuyện bạn đã có gần đây. Bao nhiêu phần của cuộc trò chuyện sẽ khó để máy tính hiểu vì nó cần ngữ cảnh?

Hiểu ngôn ngữ, còn được gọi là hiểu ngôn ngữ tự nhiên, là một phần của lĩnh vực trí tuệ nhân tạo gọi là xử lý ngôn ngữ tự nhiên (NLP), và liên quan đến việc đọc hiểu, cố gắng hiểu chi tiết của từ ngữ hoặc câu. Nếu bạn sử dụng trợ lý giọng nói như Alexa hoặc Siri, bạn đã sử dụng các dịch vụ hiểu ngôn ngữ. Đây là các dịch vụ AI hoạt động phía sau, chuyển đổi "Alexa, phát album mới nhất của Taylor Swift" thành cảnh con gái tôi nhảy múa quanh phòng khách với những bài hát yêu thích của cô ấy.

> 💁 Máy tính, mặc dù đã có nhiều tiến bộ, vẫn còn một chặng đường dài để thực sự hiểu văn bản. Khi chúng ta nói về hiểu ngôn ngữ với máy tính, chúng ta không có ý nghĩa gì gần với giao tiếp của con người, thay vào đó chúng ta nói về việc lấy một số từ và trích xuất các chi tiết chính.

Là con người, chúng ta hiểu ngôn ngữ mà không cần phải suy nghĩ nhiều. Nếu tôi yêu cầu một người khác "phát album mới nhất của Taylor Swift", họ sẽ hiểu ngay ý tôi. Đối với máy tính, điều này khó hơn. Nó sẽ phải lấy các từ, chuyển đổi từ giọng nói thành văn bản, và xác định các thông tin sau:

* Cần phát nhạc
* Nhạc thuộc về nghệ sĩ Taylor Swift
* Nhạc cụ thể là một album gồm nhiều bài hát theo thứ tự
* Taylor Swift có nhiều album, vì vậy chúng cần được sắp xếp theo thứ tự thời gian và album mới nhất là album cần thiết

✅ Hãy nghĩ về một số câu khác mà bạn đã nói khi đưa ra yêu cầu, chẳng hạn như gọi cà phê hoặc yêu cầu một thành viên gia đình đưa cho bạn thứ gì đó. Hãy thử phân tích chúng thành các thông tin mà máy tính cần trích xuất để hiểu câu nói.

Các mô hình hiểu ngôn ngữ là các mô hình AI được huấn luyện để trích xuất các chi tiết nhất định từ ngôn ngữ, và sau đó được huấn luyện cho các nhiệm vụ cụ thể bằng cách sử dụng học chuyển giao, giống như cách bạn đã huấn luyện một mô hình Custom Vision bằng một tập hợp nhỏ các hình ảnh. Bạn có thể lấy một mô hình, sau đó huấn luyện nó bằng văn bản mà bạn muốn nó hiểu.

## Tạo mô hình hiểu ngôn ngữ

![Logo của LUIS](../../../../../translated_images/vi/luis-logo.5cb4f3e88c020ee6.webp)

Bạn có thể tạo các mô hình hiểu ngôn ngữ bằng LUIS, một dịch vụ hiểu ngôn ngữ từ Microsoft thuộc Cognitive Services.

### Nhiệm vụ - tạo tài nguyên tác giả

Để sử dụng LUIS, bạn cần tạo một tài nguyên tác giả.

1. Sử dụng lệnh sau để tạo tài nguyên tác giả trong nhóm tài nguyên `smart-timer` của bạn:

    ```python
    az cognitiveservices account create --name smart-timer-luis-authoring \
                                        --resource-group smart-timer \
                                        --kind LUIS.Authoring \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Thay thế `<location>` bằng vị trí bạn đã sử dụng khi tạo Nhóm Tài nguyên.

    > ⚠️ LUIS không có sẵn ở tất cả các khu vực, vì vậy nếu bạn nhận được lỗi sau:
    >
    > ```output
    > InvalidApiSetId: The account type 'LUIS.Authoring' is either invalid or unavailable in given region.
    > ```
    >
    > hãy chọn một khu vực khác.

    Điều này sẽ tạo một tài nguyên tác giả LUIS miễn phí.

### Nhiệm vụ - tạo ứng dụng hiểu ngôn ngữ

1. Mở cổng LUIS tại [luis.ai](https://luis.ai?WT.mc_id=academic-17441-jabenn) trong trình duyệt của bạn, và đăng nhập bằng cùng tài khoản bạn đã sử dụng cho Azure.

1. Làm theo hướng dẫn trên hộp thoại để chọn đăng ký Azure của bạn, sau đó chọn tài nguyên `smart-timer-luis-authoring` mà bạn vừa tạo.

1. Từ danh sách *Ứng dụng hội thoại*, chọn nút **Ứng dụng mới** để tạo một ứng dụng mới. Đặt tên ứng dụng mới là `smart-timer`, và đặt *Văn hóa* thành ngôn ngữ của bạn.

    > 💁 Có một trường dành cho tài nguyên dự đoán. Bạn có thể tạo một tài nguyên thứ hai chỉ dành cho dự đoán, nhưng tài nguyên tác giả miễn phí cho phép 1.000 dự đoán mỗi tháng, đủ cho phát triển, vì vậy bạn có thể để trống trường này.

1. Đọc qua hướng dẫn xuất hiện sau khi bạn tạo ứng dụng để hiểu các bước bạn cần thực hiện để huấn luyện mô hình hiểu ngôn ngữ. Đóng hướng dẫn này khi bạn đã hoàn tất.

## Ý định và thực thể

Hiểu ngôn ngữ dựa trên *ý định* và *thực thể*. Ý định là mục đích của từ ngữ, ví dụ như phát nhạc, đặt hẹn giờ, hoặc gọi món ăn. Thực thể là những gì ý định đang đề cập đến, chẳng hạn như album, thời gian hẹn giờ, hoặc loại món ăn. Mỗi câu mà mô hình diễn giải nên có ít nhất một ý định, và tùy chọn một hoặc nhiều thực thể.

Một số ví dụ:

| Câu nói                                            | Ý định           | Thực thể                                   |
| -------------------------------------------------- | ---------------- | ------------------------------------------ |
| "Phát album mới nhất của Taylor Swift"             | *phát nhạc*      | *album mới nhất của Taylor Swift*          |
| "Đặt hẹn giờ 3 phút"                               | *đặt hẹn giờ*    | *3 phút*                                   |
| "Hủy hẹn giờ của tôi"                              | *hủy hẹn giờ*    | Không có                                   |
| "Gọi 3 pizza lớn dứa và một salad caesar"          | *gọi món ăn*     | *3 pizza lớn dứa*, *salad caesar*          |

✅ Với các câu bạn đã nghĩ đến trước đó, ý định và các thực thể trong câu đó sẽ là gì?

Để huấn luyện LUIS, trước tiên bạn đặt các thực thể. Đây có thể là danh sách cố định các thuật ngữ, hoặc học từ văn bản. Ví dụ, bạn có thể cung cấp một danh sách cố định các món ăn có sẵn từ thực đơn của bạn, với các biến thể (hoặc từ đồng nghĩa) của mỗi từ, chẳng hạn như *cà tím* và *aubergine* là các biến thể của *aubergine*. LUIS cũng có các thực thể được xây dựng sẵn có thể được sử dụng, chẳng hạn như số và địa điểm.

Đối với việc đặt hẹn giờ, bạn có thể có một thực thể sử dụng các thực thể số được xây dựng sẵn cho thời gian, và một thực thể khác cho các đơn vị, chẳng hạn như phút và giây. Mỗi đơn vị sẽ có nhiều biến thể để bao phủ các dạng số ít và số nhiều - chẳng hạn như phút và phút.

Sau khi các thực thể được định nghĩa, bạn tạo các ý định. Những ý định này được mô hình học dựa trên các câu ví dụ mà bạn cung cấp (được gọi là các câu nói). Ví dụ, đối với ý định *đặt hẹn giờ*, bạn có thể cung cấp các câu sau:

* `đặt hẹn giờ 1 giây`
* `đặt hẹn giờ 1 phút 12 giây`
* `đặt hẹn giờ 3 phút`
* `đặt hẹn giờ 9 phút 30 giây`

Sau đó, bạn nói với LUIS các phần của những câu này ánh xạ đến các thực thể:

![Câu nói "đặt hẹn giờ 1 phút 12 giây" được chia thành các thực thể](../../../../../translated_images/vi/sentence-as-intent-entities.301401696f992259.webp)

Câu `đặt hẹn giờ 1 phút 12 giây` có ý định là `đặt hẹn giờ`. Nó cũng có 2 thực thể với 2 giá trị mỗi thực thể:

|            | thời gian | đơn vị   |
| ---------- | -------: | -------- |
| 1 phút     | 1        | phút     |
| 12 giây    | 12       | giây     |

Để huấn luyện một mô hình tốt, bạn cần một loạt các câu ví dụ khác nhau để bao phủ nhiều cách khác nhau mà ai đó có thể yêu cầu cùng một điều.

> 💁 Như với bất kỳ mô hình AI nào, dữ liệu càng nhiều và càng chính xác để huấn luyện, mô hình càng tốt.

✅ Hãy nghĩ về các cách khác nhau mà bạn có thể yêu cầu cùng một điều và mong đợi một người hiểu.

### Nhiệm vụ - thêm thực thể vào mô hình hiểu ngôn ngữ

Đối với hẹn giờ, bạn cần thêm 2 thực thể - một cho đơn vị thời gian (phút hoặc giây), và một cho số phút hoặc giây.

Bạn có thể tìm thấy hướng dẫn sử dụng cổng LUIS trong [Quickstart: Build your app in LUIS portal documentation on Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/luis/luis-get-started-create-app?WT.mc_id=academic-17441-jabenn).

1. Từ cổng LUIS, chọn tab *Thực thể* và thêm thực thể *số* được xây dựng sẵn bằng cách chọn nút **Thêm thực thể được xây dựng sẵn**, sau đó chọn *số* từ danh sách.

1. Tạo một thực thể mới cho đơn vị thời gian bằng nút **Tạo**. Đặt tên thực thể là `đơn vị thời gian` và đặt loại là *Danh sách*. Thêm các giá trị cho `phút` và `giây` vào danh sách *Giá trị chuẩn hóa*, thêm các dạng số ít và số nhiều vào danh sách *từ đồng nghĩa*. Nhấn `return` sau khi thêm mỗi từ đồng nghĩa để thêm nó vào danh sách.

    | Giá trị chuẩn hóa | Từ đồng nghĩa        |
    | ----------------- | -------------------- |
    | phút              | phút, phút           |
    | giây              | giây, giây           |

### Nhiệm vụ - thêm ý định vào mô hình hiểu ngôn ngữ

1. Từ tab *Ý định*, chọn nút **Tạo** để tạo một ý định mới. Đặt tên ý định này là `đặt hẹn giờ`.

1. Trong các ví dụ, nhập các cách khác nhau để đặt hẹn giờ sử dụng cả phút, giây và kết hợp phút và giây. Các ví dụ có thể là:

    * `đặt hẹn giờ 1 giây`
    * `đặt hẹn giờ 4 phút`
    * `đặt hẹn giờ bốn phút sáu giây`
    * `đặt hẹn giờ 9 phút 30 giây`
    * `đặt hẹn giờ 1 phút 12 giây`
    * `đặt hẹn giờ 3 phút`
    * `đặt hẹn giờ 3 phút 1 giây`
    * `đặt hẹn giờ ba phút một giây`
    * `đặt hẹn giờ 1 phút 1 giây`
    * `đặt hẹn giờ 30 giây`
    * `đặt hẹn giờ 1 giây`

    Trộn lẫn số dưới dạng từ và số để mô hình học cách xử lý cả hai.

1. Khi bạn nhập từng ví dụ, LUIS sẽ bắt đầu phát hiện các thực thể, và sẽ gạch chân và gắn nhãn bất kỳ thực thể nào mà nó tìm thấy.

    ![Các ví dụ với các số và đơn vị thời gian được gạch chân bởi LUIS](../../../../../translated_images/vi/luis-intent-examples.25716580b2d2723c.webp)

### Nhiệm vụ - huấn luyện và kiểm tra mô hình

1. Khi các thực thể và ý định đã được cấu hình, bạn có thể huấn luyện mô hình bằng cách sử dụng nút **Huấn luyện** trên menu trên cùng. Chọn nút này, và mô hình sẽ được huấn luyện trong vài giây. Nút sẽ bị mờ đi trong khi huấn luyện, và được kích hoạt lại khi hoàn tất.

1. Chọn nút **Kiểm tra** từ menu trên cùng để kiểm tra mô hình hiểu ngôn ngữ. Nhập văn bản như `đặt hẹn giờ 5 phút 4 giây` và nhấn return. Câu nói sẽ xuất hiện trong một hộp dưới hộp văn bản mà bạn đã nhập vào, và bên dưới đó sẽ là *ý định hàng đầu*, hoặc ý định được phát hiện với xác suất cao nhất. Điều này nên là `đặt hẹn giờ`. Tên ý định sẽ được theo sau bởi xác suất rằng ý định được phát hiện là đúng.

1. Chọn tùy chọn **Kiểm tra** để xem phân tích kết quả. Bạn sẽ thấy ý định có điểm cao nhất với xác suất phần trăm của nó, cùng với danh sách các thực thể được phát hiện.

1. Đóng bảng *Kiểm tra* khi bạn đã hoàn tất kiểm tra.

### Nhiệm vụ - xuất bản mô hình

Để sử dụng mô hình này từ mã, bạn cần xuất bản nó. Khi xuất bản từ LUIS, bạn có thể xuất bản đến môi trường thử nghiệm để kiểm tra, hoặc môi trường sản phẩm để phát hành đầy đủ. Trong bài học này, môi trường thử nghiệm là đủ.

1. Từ cổng LUIS, chọn nút **Xuất bản** từ menu trên cùng.

1. Đảm bảo *Vị trí thử nghiệm* được chọn, sau đó chọn **Hoàn tất**. Bạn sẽ thấy thông báo khi ứng dụng được xuất bản.

1. Bạn có thể kiểm tra điều này bằng cách sử dụng curl. Để xây dựng lệnh curl, bạn cần ba giá trị - điểm cuối, ID ứng dụng (App ID) và khóa API. Những giá trị này có thể được truy cập từ tab **QUẢN LÝ** có thể được chọn từ menu trên cùng.

    1. Từ phần *Cài đặt*, sao chép App ID
1. Từ phần *Azure Resources*, chọn *Authoring Resource*, và sao chép *Primary Key* và *Endpoint URL*.

1. Chạy lệnh curl sau trong command prompt hoặc terminal của bạn:

    ```sh
    curl "<endpoint url>/luis/prediction/v3.0/apps/<app id>/slots/staging/predict" \
          --request GET \
          --get \
          --data "subscription-key=<primary key>" \
          --data "verbose=false" \
          --data "show-all-intents=true" \
          --data-urlencode "query=<sentence>"
    ```

    Thay thế `<endpoint url>` bằng Endpoint URL từ phần *Azure Resources*.

    Thay thế `<app id>` bằng App ID từ phần *Settings*.

    Thay thế `<primary key>` bằng Primary Key từ phần *Azure Resources*.

    Thay thế `<sentence>` bằng câu bạn muốn kiểm tra.

1. Kết quả của lệnh này sẽ là một tài liệu JSON chi tiết hóa truy vấn, ý định chính (top intent), và danh sách các thực thể được phân loại theo loại.

    ```JSON
    {
        "query": "set a timer for 45 minutes and 12 seconds",
        "prediction": {
            "topIntent": "set timer",
            "intents": {
                "set timer": {
                    "score": 0.97031575
                },
                "None": {
                    "score": 0.02205793
                }
            },
            "entities": {
                "number": [
                    45,
                    12
                ],
                "time-unit": [
                    [
                        "minute"
                    ],
                    [
                        "second"
                    ]
                ]
            }
        }
    }
    ```

    JSON trên được tạo ra từ truy vấn với `set a timer for 45 minutes and 12 seconds`:

    * `set timer` là ý định chính với xác suất 97%.
    * Hai thực thể *number* được phát hiện, `45` và `12`.
    * Hai thực thể *time-unit* được phát hiện, `minute` và `second`.

## Sử dụng mô hình hiểu ngôn ngữ

Khi đã được xuất bản, mô hình LUIS có thể được gọi từ mã. Trong các bài học trước, bạn đã sử dụng IoT Hub để xử lý giao tiếp với các dịch vụ đám mây, gửi dữ liệu đo lường và lắng nghe lệnh. Điều này rất không đồng bộ - khi dữ liệu đo lường được gửi đi, mã của bạn không chờ phản hồi, và nếu dịch vụ đám mây bị gián đoạn, bạn sẽ không biết.

Đối với một bộ hẹn giờ thông minh, chúng ta muốn có phản hồi ngay lập tức để thông báo cho người dùng rằng bộ hẹn giờ đã được đặt, hoặc cảnh báo rằng các dịch vụ đám mây không khả dụng. Để làm điều này, thiết bị IoT của chúng ta sẽ gọi trực tiếp một endpoint web, thay vì dựa vào IoT Hub.

Thay vì gọi LUIS từ thiết bị IoT, bạn có thể sử dụng mã serverless với một loại trigger khác - HTTP trigger. Điều này cho phép ứng dụng function của bạn lắng nghe các yêu cầu REST và phản hồi chúng. Chức năng này sẽ là một endpoint REST mà thiết bị của bạn có thể gọi.

> 💁 Mặc dù bạn có thể gọi LUIS trực tiếp từ thiết bị IoT của mình, nhưng tốt hơn là sử dụng mã serverless. Bằng cách này, khi bạn muốn thay đổi ứng dụng LUIS mà bạn gọi, ví dụ khi bạn huấn luyện một mô hình tốt hơn hoặc huấn luyện một mô hình bằng ngôn ngữ khác, bạn chỉ cần cập nhật mã đám mây của mình, thay vì triển khai lại mã cho hàng nghìn hoặc hàng triệu thiết bị IoT.

### Nhiệm vụ - tạo ứng dụng serverless functions

1. Tạo một ứng dụng Azure Functions có tên `smart-timer-trigger`, và mở nó trong VS Code.

1. Thêm một HTTP trigger vào ứng dụng này có tên `speech-trigger` bằng cách sử dụng lệnh sau từ bên trong terminal của VS Code:

    ```sh
    func new --name text-to-timer --template "HTTP trigger"
    ```

    Lệnh này sẽ tạo một HTTP trigger có tên `text-to-timer`.

1. Kiểm tra HTTP trigger bằng cách chạy ứng dụng functions. Khi ứng dụng chạy, bạn sẽ thấy endpoint được liệt kê trong output:

    ```output
    Functions:
    
            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    ```

    Kiểm tra điều này bằng cách tải URL [http://localhost:7071/api/text-to-timer](http://localhost:7071/api/text-to-timer) trong trình duyệt của bạn.

    ```output
    This HTTP triggered function executed successfully. Pass a name in the query string or in the request body for a personalized response.
    ```

### Nhiệm vụ - sử dụng mô hình hiểu ngôn ngữ

1. SDK cho LUIS có sẵn thông qua gói Pip. Thêm dòng sau vào tệp `requirements.txt` để thêm phụ thuộc vào gói này:

    ```sh
    azure-cognitiveservices-language-luis
    ```

1. Đảm bảo terminal của VS Code đã kích hoạt môi trường ảo, và chạy lệnh sau để cài đặt các gói Pip:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 Nếu bạn gặp lỗi, bạn có thể cần nâng cấp pip bằng lệnh sau:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Thêm các mục nhập mới vào tệp `local.settings.json` cho LUIS API Key, Endpoint URL, và App ID từ tab **MANAGE** của cổng LUIS:

    ```JSON
    "LUIS_KEY": "<primary key>",
    "LUIS_ENDPOINT_URL": "<endpoint url>",
    "LUIS_APP_ID": "<app id>"
    ```

    Thay thế `<endpoint url>` bằng Endpoint URL từ phần *Azure Resources* của tab **MANAGE**. URL này sẽ là `https://<location>.api.cognitive.microsoft.com/`.

    Thay thế `<app id>` bằng App ID từ phần *Settings* của tab **MANAGE**.

    Thay thế `<primary key>` bằng Primary Key từ phần *Azure Resources* của tab **MANAGE**.

1. Thêm các import sau vào tệp `__init__.py`:

    ```python
    import json
    import os
    from azure.cognitiveservices.language.luis.runtime import LUISRuntimeClient
    from msrest.authentication import CognitiveServicesCredentials
    ```

    Điều này sẽ import một số thư viện hệ thống, cũng như các thư viện để tương tác với LUIS.

1. Xóa nội dung của phương thức `main`, và thêm đoạn mã sau:

    ```python
    luis_key = os.environ['LUIS_KEY']
    endpoint_url = os.environ['LUIS_ENDPOINT_URL']
    app_id = os.environ['LUIS_APP_ID']
    
    credentials = CognitiveServicesCredentials(luis_key)
    client = LUISRuntimeClient(endpoint=endpoint_url, credentials=credentials)
    ```

    Đoạn mã này tải các giá trị bạn đã thêm vào tệp `local.settings.json` cho ứng dụng LUIS của bạn, tạo một đối tượng credentials với API key của bạn, sau đó tạo một đối tượng LUIS client để tương tác với ứng dụng LUIS của bạn.

1. HTTP trigger này sẽ được gọi với văn bản cần hiểu dưới dạng JSON, với văn bản trong một thuộc tính có tên `text`. Đoạn mã sau sẽ trích xuất giá trị từ body của yêu cầu HTTP và ghi log nó vào console. Thêm đoạn mã này vào hàm `main`:

    ```python
    req_body = req.get_json()
    text = req_body['text']
    logging.info(f'Request - {text}')
    ```

1. Dự đoán được yêu cầu từ LUIS bằng cách gửi một yêu cầu dự đoán - một tài liệu JSON chứa văn bản cần dự đoán. Tạo tài liệu này với đoạn mã sau:

    ```python
    prediction_request = { 'query' : text }
    ```

1. Yêu cầu này sau đó có thể được gửi đến LUIS, sử dụng staging slot mà ứng dụng của bạn đã được xuất bản:

    ```python
    prediction_response = client.prediction.get_slot_prediction(app_id, 'Staging', prediction_request)
    ```

1. Phản hồi dự đoán chứa ý định chính - ý định có điểm dự đoán cao nhất, cùng với các thực thể. Nếu ý định chính là `set timer`, thì các thực thể có thể được đọc để lấy thời gian cần thiết cho bộ hẹn giờ:

    ```python
    if prediction_response.prediction.top_intent == 'set timer':
        numbers = prediction_response.prediction.entities['number']
        time_units = prediction_response.prediction.entities['time unit']
        total_seconds = 0
    ```

    Các thực thể `number` sẽ là một mảng các số. Ví dụ, nếu bạn nói *"Set a four minute 17 second timer."*, thì mảng `number` sẽ chứa 2 số nguyên - 4 và 17.

    Các thực thể `time unit` sẽ là một mảng các mảng chuỗi, với mỗi đơn vị thời gian là một mảng chuỗi bên trong mảng. Ví dụ, nếu bạn nói *"Set a four minute 17 second timer."*, thì mảng `time unit` sẽ chứa 2 mảng với mỗi mảng có một giá trị - `['minute']` và `['second']`.

    Phiên bản JSON của các thực thể này cho *"Set a four minute 17 second timer."* là:

    ```json
    {
        "number": [4, 17],
        "time unit": [
            ["minute"],
            ["second"]
        ]
    }
    ```

    Đoạn mã này cũng định nghĩa một biến đếm cho tổng thời gian của bộ hẹn giờ tính bằng giây. Biến này sẽ được điền giá trị từ các thực thể.

1. Các thực thể không được liên kết, nhưng chúng ta có thể đưa ra một số giả định về chúng. Chúng sẽ theo thứ tự được nói, vì vậy vị trí trong mảng có thể được sử dụng để xác định số nào khớp với đơn vị thời gian nào. Ví dụ:

    * *"Set a 30 second timer"* - điều này sẽ có một số, `30`, và một đơn vị thời gian, `second`, vì vậy số duy nhất sẽ khớp với đơn vị thời gian duy nhất.
    * *"Set a 2 minute and 30 second timer"* - điều này sẽ có hai số, `2` và `30`, và hai đơn vị thời gian, `minute` và `second`, vì vậy số đầu tiên sẽ dành cho đơn vị thời gian đầu tiên (2 phút), và số thứ hai cho đơn vị thời gian thứ hai (30 giây).

    Đoạn mã sau lấy số lượng mục trong các thực thể số, và sử dụng số lượng này để trích xuất mục đầu tiên từ mỗi mảng, sau đó là mục thứ hai, và cứ thế. Thêm đoạn mã này vào bên trong khối `if`.

    ```python
    for i in range(0, len(numbers)):
        number = numbers[i]
        time_unit = time_units[i][0]
    ```

    Với *"Set a four minute 17 second timer."*, đoạn mã này sẽ lặp hai lần, cho các giá trị sau:

    | Lần lặp | `number` | `time_unit` |
    | -------:| --------:| ----------- |
    | 0       | 4        | minute      |
    | 1       | 17       | second      |

1. Bên trong vòng lặp này, sử dụng số và đơn vị thời gian để tính tổng thời gian cho bộ hẹn giờ, thêm 60 giây cho mỗi phút, và số giây cho bất kỳ giây nào.

    ```python
    if time_unit == 'minute':
        total_seconds += number * 60
    else:
        total_seconds += number
    ```

1. Bên ngoài vòng lặp qua các thực thể, ghi log tổng thời gian cho bộ hẹn giờ:

    ```python
    logging.info(f'Timer required for {total_seconds} seconds')
    ```

1. Số giây cần được trả về từ hàm dưới dạng phản hồi HTTP. Ở cuối khối `if`, thêm đoạn mã sau:

    ```python
    payload = {
        'seconds': total_seconds
    }
    return func.HttpResponse(json.dumps(payload), status_code=200)
    ```

    Đoạn mã này tạo một payload chứa tổng số giây cho bộ hẹn giờ, chuyển đổi nó thành chuỗi JSON và trả về nó dưới dạng kết quả HTTP với mã trạng thái 200, nghĩa là cuộc gọi thành công.

1. Cuối cùng, bên ngoài khối `if`, xử lý trường hợp ý định không được nhận diện bằng cách trả về mã lỗi:

    ```python
    return func.HttpResponse(status_code=404)
    ```

    404 là mã trạng thái cho *không tìm thấy*.

1. Chạy ứng dụng function và kiểm tra nó bằng cách sử dụng curl.

    ```sh
    curl --request POST 'http://localhost:7071/api/text-to-timer' \
         --header 'Content-Type: application/json' \
         --include \
         --data '{"text":"<text>"}'
    ```

    Thay thế `<text>` bằng văn bản yêu cầu của bạn, ví dụ `set a 2 minutes 27 second timer`.

    Bạn sẽ thấy output sau từ ứng dụng functions:

    ```output
    Functions:

            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    
    For detailed output, run func with --verbose flag.
    [2021-06-26T19:45:14.502Z] Worker process started and initialized.
    [2021-06-26T19:45:19.338Z] Host lock lease acquired by instance ID '000000000000000000000000951CAE4E'.
    [2021-06-26T19:45:52.059Z] Executing 'Functions.text-to-timer' (Reason='This function was programmatically called via the host APIs.', Id=f68bfb90-30e4-47a5-99da-126b66218e81)
    [2021-06-26T19:45:53.577Z] Timer required for 147 seconds
    [2021-06-26T19:45:53.746Z] Executed 'Functions.text-to-timer' (Succeeded, Id=f68bfb90-30e4-47a5-99da-126b66218e81, Duration=1750ms)
    ```

    Cuộc gọi curl sẽ trả về kết quả sau:

    ```output
    HTTP/1.1 200 OK
    Date: Tue, 29 Jun 2021 01:14:11 GMT
    Content-Type: text/plain; charset=utf-8
    Server: Kestrel
    Transfer-Encoding: chunked
    
    {"seconds": 147}
    ```

    Số giây cho bộ hẹn giờ nằm trong giá trị `"seconds"`.

> 💁 Bạn có thể tìm thấy đoạn mã này trong thư mục [code/functions](../../../../../6-consumer/lessons/2-language-understanding/code/functions).

### Nhiệm vụ - làm cho function của bạn khả dụng cho thiết bị IoT của bạn

1. Để thiết bị IoT của bạn gọi endpoint REST của bạn, nó sẽ cần biết URL. Khi bạn truy cập nó trước đó, bạn đã sử dụng `localhost`, đây là một cách tắt để truy cập các endpoint REST trên máy cục bộ của bạn. Để thiết bị IoT của bạn có thể truy cập, bạn cần hoặc xuất bản lên đám mây, hoặc lấy địa chỉ IP của bạn để truy cập cục bộ.

    > ⚠️ Nếu bạn đang sử dụng Wio Terminal, dễ dàng hơn để chạy ứng dụng function cục bộ, vì sẽ có sự phụ thuộc vào các thư viện khiến bạn không thể triển khai ứng dụng function theo cách bạn đã làm trước đó. Chạy ứng dụng function cục bộ và truy cập nó qua địa chỉ IP của máy tính của bạn. Nếu bạn muốn triển khai lên đám mây, thông tin sẽ được cung cấp trong bài học sau về cách thực hiện điều này.

    * Xuất bản ứng dụng Functions - làm theo hướng dẫn trong các bài học trước để xuất bản ứng dụng functions của bạn lên đám mây. Khi đã xuất bản, URL sẽ là `https://<APP_NAME>.azurewebsites.net/api/text-to-timer`, trong đó `<APP_NAME>` sẽ là tên của ứng dụng functions của bạn. Đảm bảo cũng xuất bản các cài đặt cục bộ của bạn.

      Khi làm việc với HTTP triggers, chúng được bảo mật mặc định với một function app key. Để lấy key này, chạy lệnh sau:

      ```sh
      az functionapp keys list --resource-group smart-timer \
                               --name <APP_NAME>                               
      ```

      Sao chép giá trị của mục `default` từ phần `functionKeys`.

      ```output
      {
        "functionKeys": {
          "default": "sQO1LQaeK9N1qYD6SXeb/TctCmwQEkToLJU6Dw8TthNeUH8VA45hlA=="
        },
        "masterKey": "RSKOAIlyvvQEQt9dfpabJT018scaLpQu9p1poHIMCxx5LYrIQZyQ/g==",
        "systemKeys": {}
      }
      ```

      Key này cần được thêm vào dưới dạng tham số truy vấn vào URL, vì vậy URL cuối cùng sẽ là `https://<APP_NAME>.azurewebsites.net/api/text-to-timer?code=<FUNCTION_KEY>`, trong đó `<APP_NAME>` sẽ là tên của ứng dụng functions của bạn, và `<FUNCTION_KEY>` sẽ là function key mặc định của bạn.

      > 💁 Bạn có thể thay đổi loại ủy quyền của HTTP trigger bằng cách sử dụng cài đặt `authlevel` trong tệp `function.json`. Bạn có thể đọc thêm về điều này trong [phần cấu hình của tài liệu Azure Functions HTTP trigger trên Microsoft docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python#configuration).

    * Chạy ứng dụng functions cục bộ, và truy cập bằng địa chỉ IP - bạn có thể lấy địa chỉ IP của máy tính của bạn trên mạng cục bộ, và sử dụng địa chỉ đó để xây dựng URL.

      Tìm địa chỉ IP của bạn:

      * Trên Windows 10, làm theo hướng dẫn [tìm địa chỉ IP của bạn](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn).
      * Trên macOS, làm theo hướng dẫn [cách tìm địa chỉ IP trên Mac](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac).
      * Trên Linux, làm theo phần tìm địa chỉ IP riêng trong hướng dẫn [cách tìm địa chỉ IP trong Linux](https://opensource.com/article/18/5/how-find-ip-address-linux).

      Khi bạn đã có địa chỉ IP của mình, bạn sẽ có thể truy cập function tại `http://`.

:7071/api/text-to-timer`, nơi `<IP_ADDRESS>` sẽ là địa chỉ IP của bạn, ví dụ `http://192.168.1.10:7071/api/text-to-timer`.

      > 💁 Lưu ý rằng điều này sử dụng cổng 7071, vì vậy sau địa chỉ IP bạn cần thêm `:7071`.

      > 💁 Điều này chỉ hoạt động nếu thiết bị IoT của bạn nằm trong cùng mạng với máy tính của bạn.

1. Kiểm tra endpoint bằng cách truy cập nó sử dụng curl.

---

## 🚀 Thử thách

Có nhiều cách để yêu cầu cùng một việc, chẳng hạn như đặt hẹn giờ. Hãy nghĩ đến các cách khác nhau để làm điều này và sử dụng chúng làm ví dụ trong ứng dụng LUIS của bạn. Kiểm tra những cách này để xem mô hình của bạn có thể xử lý tốt như thế nào với nhiều cách yêu cầu hẹn giờ.

## Câu hỏi sau bài giảng

[Câu hỏi sau bài giảng](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/44)

## Ôn tập & Tự học

* Đọc thêm về LUIS và các khả năng của nó trên [trang tài liệu Language Understanding (LUIS) trên Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/luis/?WT.mc_id=academic-17441-jabenn)
* Đọc thêm về hiểu ngôn ngữ trên [trang hiểu ngôn ngữ tự nhiên trên Wikipedia](https://wikipedia.org/wiki/Natural-language_understanding)
* Đọc thêm về HTTP triggers trong [tài liệu về Azure Functions HTTP trigger trên Microsoft docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python)

## Bài tập

[Hủy hẹn giờ](assignment.md)

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm về bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.