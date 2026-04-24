# Di chuyển cây của bạn lên đám mây

![Tổng quan bài học dưới dạng sketchnote](../../../../../translated_images/vi/lesson-8.3f21f3c11159e6a0.webp)

> Sketchnote bởi [Nitya Narasimhan](https://github.com/nitya). Nhấp vào hình ảnh để xem phiên bản lớn hơn.

Bài học này được giảng dạy trong [IoT for Beginners Project 2 - Digital Agriculture series](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) từ [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Kết nối thiết bị của bạn với đám mây bằng Azure IoT Hub](https://img.youtube.com/vi/bNxjopXkhvk/0.jpg)](https://youtu.be/bNxjopXkhvk)

## Câu hỏi trước bài giảng

[Câu hỏi trước bài giảng](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/15)

## Giới thiệu

Trong bài học trước, bạn đã học cách kết nối cây của mình với một MQTT broker và điều khiển relay từ mã máy chủ chạy cục bộ. Đây là nền tảng của hệ thống tưới nước tự động kết nối internet, được sử dụng từ cây cá nhân tại nhà đến các trang trại thương mại.

Thiết bị IoT đã giao tiếp với một MQTT broker công cộng để minh họa nguyên lý, nhưng đây không phải là cách đáng tin cậy hoặc an toàn nhất. Trong bài học này, bạn sẽ tìm hiểu về đám mây và các khả năng IoT được cung cấp bởi các dịch vụ đám mây công cộng. Bạn cũng sẽ học cách di chuyển cây của mình từ MQTT broker công cộng sang một trong các dịch vụ đám mây này.

Trong bài học này, chúng ta sẽ đề cập đến:

* [Đám mây là gì?](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Tạo một đăng ký đám mây](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Dịch vụ IoT trên đám mây](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Tạo một dịch vụ IoT trên đám mây](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Giao tiếp với IoT Hub](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Kết nối thiết bị của bạn với dịch vụ IoT](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)

## Đám mây là gì?

Trước khi có đám mây, khi một công ty muốn cung cấp dịch vụ cho nhân viên của họ (như cơ sở dữ liệu hoặc lưu trữ tệp), hoặc cho công chúng (như các trang web), họ sẽ xây dựng và vận hành một trung tâm dữ liệu. Điều này có thể là một phòng với một số ít máy tính, hoặc một tòa nhà với nhiều máy tính. Công ty sẽ quản lý mọi thứ, bao gồm:

* Mua máy tính
* Bảo trì phần cứng
* Cung cấp điện và làm mát
* Mạng lưới
* Bảo mật, bao gồm bảo vệ tòa nhà và phần mềm trên máy tính
* Cài đặt và cập nhật phần mềm

Điều này có thể rất tốn kém, yêu cầu một đội ngũ nhân viên có kỹ năng đa dạng, và rất chậm để thay đổi khi cần thiết. Ví dụ, nếu một cửa hàng trực tuyến cần chuẩn bị cho mùa lễ bận rộn, họ sẽ phải lên kế hoạch trước vài tháng để mua thêm phần cứng, cấu hình, cài đặt và cài đặt phần mềm để vận hành quy trình bán hàng. Sau khi mùa lễ kết thúc và doanh số giảm xuống, họ sẽ còn lại những máy tính đã trả tiền nhưng không sử dụng cho đến mùa bận rộn tiếp theo.

✅ Bạn có nghĩ rằng điều này sẽ cho phép các công ty di chuyển nhanh chóng không? Nếu một nhà bán lẻ quần áo trực tuyến bất ngờ trở nên nổi tiếng nhờ một người nổi tiếng mặc đồ của họ, liệu họ có thể tăng sức mạnh tính toán đủ nhanh để hỗ trợ lượng đơn hàng tăng đột biến không?

### Máy tính của người khác

Đám mây thường được đùa gọi là "máy tính của người khác". Ý tưởng ban đầu rất đơn giản - thay vì mua máy tính, bạn thuê máy tính của người khác. Một nhà cung cấp dịch vụ đám mây sẽ quản lý các trung tâm dữ liệu khổng lồ. Họ sẽ chịu trách nhiệm mua và cài đặt phần cứng, quản lý điện và làm mát, mạng lưới, bảo mật tòa nhà, cập nhật phần cứng và phần mềm, mọi thứ. Là khách hàng, bạn sẽ thuê các máy tính bạn cần, thuê thêm khi nhu cầu tăng đột biến, sau đó giảm số lượng thuê nếu nhu cầu giảm. Các trung tâm dữ liệu đám mây này có mặt khắp thế giới.

![Một trung tâm dữ liệu đám mây của Microsoft](../../../../../translated_images/vi/azure-region-existing.73f704604f2aa6cb.webp)
![Một kế hoạch mở rộng trung tâm dữ liệu đám mây của Microsoft](../../../../../translated_images/vi/azure-region-planned-expansion.a5074a1e8af74f15.webp)

Các trung tâm dữ liệu này có thể rộng hàng km vuông. Các hình ảnh trên được chụp vài năm trước tại một trung tâm dữ liệu đám mây của Microsoft, và cho thấy kích thước ban đầu, cùng với kế hoạch mở rộng. Khu vực được dọn sạch cho việc mở rộng rộng hơn 5 km vuông.

> 💁 Các trung tâm dữ liệu này yêu cầu lượng điện năng lớn đến mức một số có nhà máy điện riêng. Vì kích thước và mức đầu tư từ các nhà cung cấp đám mây, chúng thường rất thân thiện với môi trường. Chúng hiệu quả hơn nhiều so với số lượng lớn các trung tâm dữ liệu nhỏ, chạy chủ yếu bằng năng lượng tái tạo, và các nhà cung cấp đám mây làm việc chăm chỉ để giảm lãng phí, cắt giảm sử dụng nước, và trồng lại rừng để bù đắp cho những khu vực bị chặt phá để xây dựng trung tâm dữ liệu. Bạn có thể đọc thêm về cách một nhà cung cấp đám mây đang làm việc về tính bền vững trên [trang web bền vững của Azure](https://azure.microsoft.com/global-infrastructure/sustainability/?WT.mc_id=academic-17441-jabenn).

✅ Tìm hiểu thêm: Đọc về các đám mây lớn như [Azure từ Microsoft](https://azure.microsoft.com/?WT.mc_id=academic-17441-jabenn) hoặc [GCP từ Google](https://cloud.google.com). Họ có bao nhiêu trung tâm dữ liệu, và chúng nằm ở đâu trên thế giới?

Sử dụng đám mây giúp các công ty giảm chi phí và tập trung vào những gì họ làm tốt nhất, để chuyên môn về điện toán đám mây nằm trong tay nhà cung cấp. Các công ty không còn cần thuê hoặc mua không gian trung tâm dữ liệu, trả tiền cho các nhà cung cấp khác nhau về kết nối và điện, hoặc thuê chuyên gia. Thay vào đó, họ có thể trả một hóa đơn hàng tháng cho nhà cung cấp đám mây để mọi thứ được chăm sóc.

Nhà cung cấp đám mây sau đó có thể sử dụng quy mô kinh tế để giảm chi phí, mua máy tính với số lượng lớn với giá thấp hơn, đầu tư vào công cụ để giảm khối lượng công việc bảo trì, thậm chí thiết kế và xây dựng phần cứng riêng để cải thiện dịch vụ đám mây của họ.

### Microsoft Azure

Azure là đám mây dành cho nhà phát triển từ Microsoft, và đây là đám mây bạn sẽ sử dụng cho các bài học này. Video dưới đây cung cấp một cái nhìn tổng quan ngắn về Azure:

[![Video tổng quan về Azure](../../../../../translated_images/vi/what-is-azure-video-thumbnail.20174db09e03bbb8.webp)](https://www.microsoft.com/videoplayer/embed/RE4Ibng?WT.mc_id=academic-17441-jabenn)

## Tạo một đăng ký đám mây

Để sử dụng các dịch vụ trên đám mây, bạn sẽ cần đăng ký với một nhà cung cấp đám mây. Trong bài học này, bạn sẽ đăng ký một tài khoản Microsoft Azure. Nếu bạn đã có tài khoản Azure, bạn có thể bỏ qua nhiệm vụ này. Các chi tiết đăng ký được mô tả ở đây là chính xác tại thời điểm viết, nhưng có thể thay đổi.

> 💁 Nếu bạn đang truy cập các bài học này thông qua trường học, bạn có thể đã có một tài khoản Azure. Kiểm tra với giáo viên của bạn.

Có hai loại tài khoản Azure miễn phí mà bạn có thể đăng ký:

* **Azure for Students** - Đây là tài khoản dành cho sinh viên từ 18 tuổi trở lên. Bạn không cần thẻ tín dụng để đăng ký, và bạn sử dụng địa chỉ email trường học để xác nhận rằng bạn là sinh viên. Khi đăng ký, bạn nhận được 100 USD để sử dụng cho các tài nguyên đám mây, cùng với các dịch vụ miễn phí bao gồm phiên bản miễn phí của một dịch vụ IoT. Tài khoản này kéo dài 12 tháng, và bạn có thể gia hạn mỗi năm nếu vẫn là sinh viên.

* **Azure free subscription** - Đây là tài khoản dành cho bất kỳ ai không phải là sinh viên. Bạn sẽ cần thẻ tín dụng để đăng ký tài khoản, nhưng thẻ của bạn sẽ không bị tính phí, chỉ được sử dụng để xác minh bạn là người thật, không phải bot. Bạn nhận được 200 USD tín dụng để sử dụng trong 30 ngày đầu tiên cho bất kỳ dịch vụ nào, cùng với các tầng miễn phí của các dịch vụ Azure. Sau khi tín dụng của bạn đã được sử dụng hết, thẻ của bạn sẽ không bị tính phí trừ khi bạn chuyển đổi sang tài khoản trả theo mức sử dụng.

> 💁 Microsoft cũng cung cấp tài khoản Azure for Students Starter cho sinh viên dưới 18 tuổi, nhưng tại thời điểm viết bài này, tài khoản này không hỗ trợ bất kỳ dịch vụ IoT nào.

### Nhiệm vụ - đăng ký tài khoản đám mây miễn phí

Nếu bạn là sinh viên từ 18 tuổi trở lên, bạn có thể đăng ký tài khoản Azure for Students. Bạn sẽ cần xác nhận bằng địa chỉ email trường học. Bạn có thể làm điều này theo hai cách:

* Đăng ký gói nhà phát triển sinh viên GitHub tại [education.github.com/pack](https://education.github.com/pack). Điều này cung cấp cho bạn quyền truy cập vào một loạt các công cụ và ưu đãi, bao gồm GitHub và Microsoft Azure. Sau khi đăng ký gói nhà phát triển, bạn có thể kích hoạt ưu đãi Azure for Students.

* Đăng ký trực tiếp tài khoản Azure for Students tại [azure.microsoft.com/free/students](https://azure.microsoft.com/free/students/?WT.mc_id=academic-17441-jabenn).

> ⚠️ Nếu địa chỉ email trường học của bạn không được nhận diện, hãy tạo một [vấn đề trong repo này](https://github.com/Microsoft/IoT-For-Beginners/issues) và chúng tôi sẽ xem liệu nó có thể được thêm vào danh sách cho phép của Azure for Students hay không.

Nếu bạn không phải là sinh viên, hoặc bạn không có địa chỉ email trường học hợp lệ, bạn có thể đăng ký tài khoản Azure Free.

* Đăng ký tài khoản Azure Free tại [azure.microsoft.com/free](https://azure.microsoft.com/free/?WT.mc_id=academic-17441-jabenn)

## Dịch vụ IoT trên đám mây

MQTT broker công cộng mà bạn đã sử dụng là một công cụ tuyệt vời khi học tập, nhưng có một số nhược điểm khi sử dụng trong môi trường thương mại:

* Độ tin cậy - đây là một dịch vụ miễn phí không có đảm bảo, và có thể bị tắt bất cứ lúc nào
* Bảo mật - nó là công cộng, vì vậy bất kỳ ai cũng có thể nghe dữ liệu của bạn hoặc gửi lệnh để điều khiển phần cứng của bạn
* Hiệu suất - nó được thiết kế chỉ cho một số ít tin nhắn thử nghiệm, vì vậy sẽ không thể xử lý lượng lớn tin nhắn được gửi
* Khám phá - không có cách nào để biết thiết bị nào đang được kết nối

Các dịch vụ IoT trên đám mây giải quyết những vấn đề này. Chúng được duy trì bởi các nhà cung cấp đám mây lớn, những người đầu tư mạnh vào độ tin cậy và luôn sẵn sàng khắc phục bất kỳ vấn đề nào có thể phát sinh. Chúng có bảo mật tích hợp để ngăn hacker đọc dữ liệu của bạn hoặc gửi lệnh giả mạo. Chúng cũng có hiệu suất cao, có thể xử lý hàng triệu tin nhắn mỗi ngày, tận dụng đám mây để mở rộng khi cần thiết.

> 💁 Mặc dù bạn phải trả phí hàng tháng cho những lợi ích này, hầu hết các nhà cung cấp đám mây đều cung cấp phiên bản miễn phí của dịch vụ IoT với số lượng tin nhắn hoặc thiết bị kết nối giới hạn mỗi ngày. Phiên bản miễn phí này thường đủ cho một nhà phát triển học về dịch vụ. Trong bài học này, bạn sẽ sử dụng phiên bản miễn phí.

Thiết bị IoT kết nối với dịch vụ đám mây thông qua SDK thiết bị (một thư viện cung cấp mã để làm việc với các tính năng của dịch vụ), hoặc trực tiếp qua giao thức giao tiếp như MQTT hoặc HTTP. SDK thiết bị thường là cách dễ nhất vì nó xử lý mọi thứ cho bạn, chẳng hạn như biết các chủ đề cần xuất bản hoặc đăng ký, và cách xử lý bảo mật.

![Thiết bị kết nối với dịch vụ bằng SDK thiết bị. Mã máy chủ cũng kết nối với dịch vụ qua SDK](../../../../../translated_images/vi/iot-service-connectivity.7e873847921a5d6f.webp)

Thiết bị của bạn sau đó giao tiếp với các phần khác của ứng dụng thông qua dịch vụ này - tương tự như cách bạn gửi dữ liệu và nhận lệnh qua MQTT. Điều này thường sử dụng SDK dịch vụ hoặc thư viện tương tự. Tin nhắn từ thiết bị của bạn đến dịch vụ, nơi các thành phần khác của ứng dụng có thể đọc chúng, và tin nhắn có thể được gửi trở lại thiết bị của bạn.

![Thiết bị không có khóa bí mật hợp lệ không thể kết nối với dịch vụ IoT](../../../../../translated_images/vi/iot-service-allowed-denied-connection.818b0063ac213fb8.webp)

Các dịch vụ này thực hiện bảo mật bằng cách biết về tất cả các thiết bị có thể kết nối và gửi dữ liệu, hoặc bằng cách đăng ký trước các thiết bị với dịch vụ, hoặc bằng cách cung cấp cho các thiết bị khóa bí mật hoặc chứng chỉ mà chúng có thể sử dụng để tự đăng ký với dịch vụ lần đầu tiên chúng kết nối. Các thiết bị không xác định không thể kết nối, nếu chúng cố gắng, dịch vụ sẽ từ chối kết nối và bỏ qua các tin nhắn được gửi bởi chúng.

✅ Tìm hiểu thêm: Nhược điểm của việc có một dịch vụ IoT mở mà bất kỳ thiết bị hoặc mã nào cũng có thể kết nối là gì? Bạn có thể tìm thấy các ví dụ cụ thể về hacker lợi dụng điều này không?

Các thành phần khác của ứng dụng của bạn có thể kết nối với dịch vụ IoT và tìm hiểu về tất cả các thiết bị đang được kết nối hoặc đăng ký, và giao tiếp trực tiếp với chúng theo nhóm hoặc riêng lẻ.
💁 Các dịch vụ IoT cũng triển khai các khả năng bổ sung, và các nhà cung cấp đám mây có thêm các dịch vụ và ứng dụng có thể được kết nối với dịch vụ. Ví dụ, nếu bạn muốn lưu trữ tất cả các thông điệp đo lường được gửi bởi tất cả các thiết bị vào một cơ sở dữ liệu, thường chỉ cần vài cú nhấp chuột trong công cụ cấu hình của nhà cung cấp đám mây để kết nối dịch vụ với cơ sở dữ liệu và truyền dữ liệu vào.
## Tạo dịch vụ IoT trên đám mây

Bây giờ bạn đã có một đăng ký Azure, bạn có thể đăng ký một dịch vụ IoT. Dịch vụ IoT từ Microsoft được gọi là Azure IoT Hub.

![Logo của Azure IoT Hub](../../../../../translated_images/vi/azure-iot-hub-logo.28a19de76d0a1932.webp)

Video dưới đây cung cấp một cái nhìn tổng quan ngắn gọn về Azure IoT Hub:

[![Video tổng quan về Azure IoT Hub](https://img.youtube.com/vi/smuZaZZXKsU/0.jpg)](https://www.youtube.com/watch?v=smuZaZZXKsU)

> 🎥 Nhấp vào hình ảnh trên để xem video

✅ Dành một chút thời gian để nghiên cứu và đọc tổng quan về IoT Hub trong [tài liệu Microsoft IoT Hub](https://docs.microsoft.com/azure/iot-hub/about-iot-hub?WT.mc_id=academic-17441-jabenn).

Các dịch vụ đám mây có sẵn trong Azure có thể được cấu hình thông qua một cổng web hoặc qua giao diện dòng lệnh (CLI). Trong nhiệm vụ này, bạn sẽ sử dụng CLI.

### Nhiệm vụ - cài đặt Azure CLI

Để sử dụng Azure CLI, trước tiên bạn cần cài đặt nó trên PC hoặc Mac của mình.

1. Làm theo hướng dẫn trong [tài liệu Azure CLI](https://docs.microsoft.com/cli/azure/install-azure-cli?WT.mc_id=academic-17441-jabenn) để cài đặt CLI.

1. Azure CLI hỗ trợ một số tiện ích mở rộng bổ sung khả năng quản lý nhiều dịch vụ Azure khác nhau. Cài đặt tiện ích mở rộng IoT bằng cách chạy lệnh sau từ dòng lệnh hoặc terminal của bạn:

    ```sh
    az extension add --name azure-iot
    ```

1. Từ dòng lệnh hoặc terminal của bạn, chạy lệnh sau để đăng nhập vào đăng ký Azure của bạn từ Azure CLI.

    ```sh
    az login
    ```

    Một trang web sẽ được mở trong trình duyệt mặc định của bạn. Đăng nhập bằng tài khoản bạn đã sử dụng để đăng ký Azure. Sau khi đăng nhập, bạn có thể đóng tab trình duyệt.

1. Nếu bạn có nhiều đăng ký Azure, chẳng hạn như một đăng ký do trường học cung cấp và một đăng ký Azure for Students của riêng bạn, bạn sẽ cần chọn đăng ký bạn muốn sử dụng. Chạy lệnh sau để liệt kê tất cả các đăng ký mà bạn có quyền truy cập:

    ```sh
    az account list --output table
    ```

    Trong kết quả, bạn sẽ thấy tên của mỗi đăng ký cùng với `SubscriptionId`.

    ```output
    ➜  ~ az account list --output table
    Name                    CloudName    SubscriptionId                        State    IsDefault
    ----------------------  -----------  ------------------------------------  -------  -----------
    School-subscription     AzureCloud   cb30cde9-814a-42f0-a111-754cb788e4e1  Enabled  True
    Azure for Students      AzureCloud   fa51c31b-162c-4599-add6-781def2e1fbf  Enabled  False
    ```

    Để chọn đăng ký bạn muốn sử dụng, sử dụng lệnh sau:

    ```sh
    az account set --subscription <SubscriptionId>
    ```

    Thay thế `<SubscriptionId>` bằng Id của đăng ký bạn muốn sử dụng. Sau khi chạy lệnh này, chạy lại lệnh để liệt kê các tài khoản của bạn. Bạn sẽ thấy cột `IsDefault` được đánh dấu là `True` cho đăng ký bạn vừa thiết lập.

### Nhiệm vụ - tạo nhóm tài nguyên

Các dịch vụ Azure, chẳng hạn như các phiên bản IoT Hub, máy ảo, cơ sở dữ liệu hoặc dịch vụ AI, được gọi là **tài nguyên**. Mỗi tài nguyên phải nằm trong một **Nhóm Tài nguyên**, một nhóm logic của một hoặc nhiều tài nguyên.

> 💁 Sử dụng nhóm tài nguyên có nghĩa là bạn có thể quản lý nhiều dịch vụ cùng một lúc. Ví dụ, sau khi hoàn thành tất cả các bài học cho dự án này, bạn có thể xóa nhóm tài nguyên và tất cả các tài nguyên trong đó sẽ tự động bị xóa.

1. Có nhiều trung tâm dữ liệu Azure trên khắp thế giới, được chia thành các khu vực. Khi bạn tạo một tài nguyên hoặc nhóm tài nguyên Azure, bạn phải chỉ định nơi bạn muốn tạo nó. Chạy lệnh sau để lấy danh sách các vị trí:

    ```sh
    az account list-locations --output table
    ```

    Bạn sẽ thấy một danh sách các vị trí. Danh sách này sẽ rất dài.

    > 💁 Tại thời điểm viết bài, có 65 vị trí mà bạn có thể triển khai.

    ```output
        ➜  ~ az account list-locations --output table
    DisplayName               Name                 RegionalDisplayName
    ------------------------  -------------------  -------------------------------------
    East US                   eastus               (US) East US
    East US 2                 eastus2              (US) East US 2
    South Central US          southcentralus       (US) South Central US
    ...
    ```

    Ghi lại giá trị từ cột `Name` của khu vực gần bạn nhất. Bạn có thể tìm thấy các khu vực trên bản đồ tại [trang địa lý Azure](https://azure.microsoft.com/global-infrastructure/geographies/?WT.mc_id=academic-17441-jabenn).

1. Chạy lệnh sau để tạo một nhóm tài nguyên có tên `soil-moisture-sensor`. Tên nhóm tài nguyên phải là duy nhất trong đăng ký của bạn.

    ```sh
    az group create --name soil-moisture-sensor \
                    --location <location>
    ```

    Thay thế `<location>` bằng vị trí bạn đã chọn ở bước trước.

### Nhiệm vụ - tạo một IoT Hub

Bây giờ bạn có thể tạo một tài nguyên IoT Hub trong nhóm tài nguyên của mình.

1. Sử dụng lệnh sau để tạo tài nguyên IoT Hub của bạn:

    ```sh
    az iot hub create --resource-group soil-moisture-sensor \
                      --sku F1 \
                      --partition-count 2 \
                      --name <hub_name>
    ```

    Thay thế `<hub_name>` bằng một tên cho hub của bạn. Tên này cần phải là duy nhất trên toàn cầu - nghĩa là không có IoT Hub nào khác được tạo bởi bất kỳ ai có cùng tên. Tên này được sử dụng trong một URL trỏ đến hub, vì vậy cần phải duy nhất. Sử dụng một cái gì đó như `soil-moisture-sensor-` và thêm một định danh duy nhất vào cuối, chẳng hạn như một số từ ngẫu nhiên hoặc tên của bạn.

    Tùy chọn `--sku F1` cho biết sử dụng gói miễn phí. Gói miễn phí hỗ trợ 8.000 tin nhắn mỗi ngày cùng với hầu hết các tính năng của các gói trả phí đầy đủ.

    > 🎓 Các mức giá khác nhau của các dịch vụ Azure được gọi là các gói. Mỗi gói có chi phí khác nhau và cung cấp các tính năng hoặc khối lượng dữ liệu khác nhau.

    > 💁 Nếu bạn muốn tìm hiểu thêm về giá cả, bạn có thể xem [hướng dẫn giá Azure IoT Hub](https://azure.microsoft.com/pricing/details/iot-hub/?WT.mc_id=academic-17441-jabenn).

    Tùy chọn `--partition-count 2` xác định số luồng dữ liệu mà IoT Hub hỗ trợ, nhiều phân vùng hơn giảm thiểu tắc nghẽn dữ liệu khi nhiều thiết bị đọc và ghi từ IoT Hub. Phân vùng nằm ngoài phạm vi của các bài học này, nhưng giá trị này cần được thiết lập để tạo một IoT Hub gói miễn phí.

    > 💁 Bạn chỉ có thể có một IoT Hub gói miễn phí cho mỗi đăng ký.

IoT Hub sẽ được tạo. Quá trình này có thể mất một phút hoặc lâu hơn để hoàn thành.

## Giao tiếp với IoT Hub

Trong bài học trước, bạn đã sử dụng MQTT và gửi tin nhắn qua lại trên các chủ đề khác nhau, với các chủ đề khác nhau có mục đích khác nhau. Thay vì gửi tin nhắn qua các chủ đề khác nhau, IoT Hub có một số cách được định nghĩa để thiết bị giao tiếp với Hub, hoặc Hub giao tiếp với thiết bị.

> 💁 Ở cấp độ kỹ thuật, giao tiếp giữa IoT Hub và thiết bị của bạn có thể sử dụng MQTT, HTTPS hoặc AMQP.

* Tin nhắn từ thiết bị đến đám mây (D2C) - đây là các tin nhắn được gửi từ thiết bị đến IoT Hub, chẳng hạn như dữ liệu đo lường. Chúng sau đó có thể được đọc từ IoT Hub bởi mã ứng dụng của bạn.

    > 🎓 Ở cấp độ kỹ thuật, IoT Hub sử dụng một dịch vụ Azure gọi là [Event Hubs](https://docs.microsoft.com/azure/event-hubs/?WT.mc_id=academic-17441-jabenn). Khi bạn viết mã để đọc tin nhắn được gửi đến hub, chúng thường được gọi là sự kiện.

* Tin nhắn từ đám mây đến thiết bị (C2D) - đây là các tin nhắn được gửi từ mã ứng dụng, thông qua IoT Hub đến thiết bị IoT.

* Yêu cầu phương thức trực tiếp - đây là các tin nhắn được gửi từ mã ứng dụng thông qua IoT Hub đến thiết bị IoT để yêu cầu thiết bị thực hiện một hành động nào đó, chẳng hạn như điều khiển một bộ truyền động. Những tin nhắn này yêu cầu một phản hồi để mã ứng dụng của bạn có thể biết liệu nó đã được xử lý thành công hay chưa.

* Device twins - đây là các tài liệu JSON được đồng bộ hóa giữa thiết bị và IoT Hub, và được sử dụng để lưu trữ cài đặt hoặc các thuộc tính khác được báo cáo bởi thiết bị, hoặc cần được thiết lập trên thiết bị (được gọi là desired) bởi IoT Hub.

IoT Hub có thể lưu trữ tin nhắn và yêu cầu phương thức trực tiếp trong một khoảng thời gian có thể cấu hình (mặc định là một ngày), vì vậy nếu một thiết bị hoặc mã ứng dụng mất kết nối, nó vẫn có thể truy xuất các tin nhắn được gửi trong khi nó ngoại tuyến sau khi kết nối lại. Device twins được lưu trữ vĩnh viễn trong IoT Hub, vì vậy bất kỳ lúc nào thiết bị có thể kết nối lại và nhận được device twin mới nhất.

✅ Nghiên cứu thêm: Đọc thêm về các loại tin nhắn này trong [hướng dẫn giao tiếp từ thiết bị đến đám mây](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-d2c-guidance?WT.mc_id=academic-17441-jabenn), và [hướng dẫn giao tiếp từ đám mây đến thiết bị](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-c2d-guidance?WT.mc_id=academic-17441-jabenn) trong tài liệu IoT Hub.

## Kết nối thiết bị của bạn với dịch vụ IoT

Khi hub đã được tạo, thiết bị IoT của bạn có thể kết nối với nó. Chỉ các thiết bị đã được đăng ký mới có thể kết nối với dịch vụ, vì vậy bạn sẽ cần đăng ký thiết bị của mình trước. Khi bạn đăng ký, bạn sẽ nhận được một chuỗi kết nối mà thiết bị có thể sử dụng để kết nối. Chuỗi kết nối này là duy nhất cho từng thiết bị và chứa thông tin về IoT Hub, thiết bị, và một khóa bí mật cho phép thiết bị này kết nối.

> 🎓 Chuỗi kết nối là một thuật ngữ chung cho một đoạn văn bản chứa thông tin kết nối. Chúng được sử dụng khi kết nối với IoT Hub, cơ sở dữ liệu và nhiều dịch vụ khác. Chúng thường bao gồm một định danh cho dịch vụ, chẳng hạn như URL, và thông tin bảo mật như khóa bí mật. Chúng được truyền vào SDK để kết nối với dịch vụ.

> ⚠️ Chuỗi kết nối cần được giữ bảo mật! Bảo mật sẽ được đề cập chi tiết hơn trong bài học sau.

### Nhiệm vụ - đăng ký thiết bị IoT của bạn

Thiết bị IoT có thể được đăng ký với IoT Hub của bạn bằng Azure CLI.

1. Chạy lệnh sau để đăng ký một thiết bị:

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor \
                                      --hub-name <hub_name>
    ```

    Thay thế `<hub_name>` bằng tên bạn đã sử dụng cho IoT Hub của mình.

    Điều này sẽ tạo một thiết bị với ID là `soil-moisture-sensor`.

1. Khi thiết bị IoT của bạn kết nối với IoT Hub của bạn bằng SDK, nó cần sử dụng một chuỗi kết nối cung cấp URL của hub, cùng với một khóa bí mật. Chạy lệnh sau để lấy chuỗi kết nối:

    ```sh
    az iot hub device-identity connection-string show --device-id soil-moisture-sensor \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    Thay thế `<hub_name>` bằng tên bạn đã sử dụng cho IoT Hub của mình.

1. Lưu chuỗi kết nối được hiển thị trong kết quả vì bạn sẽ cần nó sau này.

### Nhiệm vụ - kết nối thiết bị IoT của bạn với đám mây

Làm theo hướng dẫn phù hợp để kết nối thiết bị IoT của bạn với đám mây:

* [Arduino - Wio Terminal](wio-terminal-connect-hub.md)
* [Máy tính bảng đơn - Raspberry Pi/Thiết bị IoT ảo](single-board-computer-connect-hub.md)

### Nhiệm vụ - giám sát sự kiện

Hiện tại, bạn sẽ không cập nhật mã máy chủ của mình. Thay vào đó, bạn có thể sử dụng Azure CLI để giám sát các sự kiện từ thiết bị IoT của mình.

1. Đảm bảo thiết bị IoT của bạn đang chạy và gửi các giá trị đo độ ẩm đất.

1. Chạy lệnh sau trong dòng lệnh hoặc terminal của bạn để giám sát các tin nhắn được gửi đến IoT Hub của bạn:

    ```sh
    az iot hub monitor-events --hub-name <hub_name>
    ```

    Thay thế `<hub_name>` bằng tên bạn đã sử dụng cho IoT Hub của mình.

    Bạn sẽ thấy các tin nhắn xuất hiện trong kết quả console khi chúng được gửi bởi thiết bị IoT của bạn.

    ```output
    Starting event monitor, use ctrl-c to stop...
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "payload": "{\"soil_moisture\": 376}"
        }
    },
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "payload": "{\"soil_moisture\": 381}"
        }
    }
    ```

    Nội dung của `payload` sẽ khớp với tin nhắn được gửi bởi thiết bị IoT của bạn.

    > Tại thời điểm viết bài, tiện ích mở rộng `az iot` chưa hoạt động hoàn chỉnh trên Apple Silicon. Nếu bạn đang sử dụng thiết bị Apple Silicon, bạn sẽ cần giám sát các tin nhắn theo cách khác, chẳng hạn như sử dụng [Azure IoT Tools cho Visual Studio Code](https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-vscode-iot-toolkit-cloud-device-messaging).

1. Các tin nhắn này có một số thuộc tính được gắn tự động, chẳng hạn như dấu thời gian khi chúng được gửi. Những thuộc tính này được gọi là *annotations*. Để xem tất cả các annotations của tin nhắn, sử dụng lệnh sau:

    ```sh
    az iot hub monitor-events --properties anno --hub-name <hub_name>
    ```

    Thay thế `<hub_name>` bằng tên bạn đã sử dụng cho IoT Hub của mình.

    Bạn sẽ thấy các tin nhắn xuất hiện trong kết quả console khi chúng được gửi bởi thiết bị IoT của bạn.

    ```output
    Starting event monitor, use ctrl-c to stop...
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "properties": {},
            "annotations": {
                "iothub-connection-device-id": "soil-moisture-sensor",
                "iothub-connection-auth-method": "{\"scope\":\"device\",\"type\":\"sas\",\"issuer\":\"iothub\",\"acceptingIpFilterRule\":null}",
                "iothub-connection-auth-generation-id": "637553997165220462",
                "iothub-enqueuedtime": 1619976150288,
                "iothub-message-source": "Telemetry",
                "x-opt-sequence-number": 1379,
                "x-opt-offset": "550576",
                "x-opt-enqueued-time": 1619976150277
            },
            "payload": "{\"soil_moisture\": 381}"
        }
    }
    ```

    Các giá trị thời gian trong annotations được tính theo [thời gian UNIX](https://wikipedia.org/wiki/Unix_time), đại diện cho số giây kể từ nửa đêm ngày 1 tháng 1 năm 1970.

    Thoát khỏi trình giám sát sự kiện khi bạn hoàn thành.

### Nhiệm vụ - điều khiển thiết bị IoT của bạn

Bạn cũng có thể sử dụng Azure CLI để gọi các phương thức trực tiếp trên thiết bị IoT của mình.

1. Chạy lệnh sau trong dòng lệnh hoặc terminal của bạn để gọi phương thức `relay_on` trên thiết bị IoT:

    ```sh
    az iot hub invoke-device-method --device-id soil-moisture-sensor \
                                    --method-name relay_on \
                                    --method-payload '{}' \
                                    --hub-name <hub_name>
    ```

    Thay thế `
<hub_name>
` với tên bạn đã sử dụng cho IoT Hub của mình.

Điều này gửi một yêu cầu phương thức trực tiếp cho phương thức được chỉ định bởi `method-name`. Các phương thức trực tiếp có thể nhận một payload chứa dữ liệu cho phương thức, và điều này có thể được chỉ định trong tham số `method-payload` dưới dạng JSON.

Bạn sẽ thấy relay bật lên và đầu ra tương ứng từ thiết bị IoT của bạn:

```output
    Direct method received -  relay_on
    ```

1. Lặp lại bước trên, nhưng đặt `--method-name` thành `relay_off`. Bạn sẽ thấy relay tắt và đầu ra tương ứng từ thiết bị IoT.

---

## 🚀 Thử thách

Gói miễn phí của IoT Hub cho phép 8.000 tin nhắn mỗi ngày. Mã bạn đã viết gửi các tin nhắn telemetry mỗi 10 giây. Một tin nhắn mỗi 10 giây sẽ tạo ra bao nhiêu tin nhắn mỗi ngày?

Hãy suy nghĩ về tần suất cần gửi các đo lường độ ẩm đất? Làm thế nào bạn có thể thay đổi mã của mình để nằm trong giới hạn của gói miễn phí và kiểm tra thường xuyên như cần thiết nhưng không quá thường xuyên? Nếu bạn muốn thêm một thiết bị thứ hai thì sao?

## Câu hỏi sau bài giảng

[Câu hỏi sau bài giảng](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/16)

## Ôn tập & Tự học

SDK IoT Hub là mã nguồn mở cho cả Arduino và Python. Trong các kho mã trên GitHub, có một số mẫu cho thấy cách làm việc với các tính năng khác nhau của IoT Hub.

* Nếu bạn đang sử dụng Wio Terminal, hãy xem [các mẫu Arduino trên GitHub](https://github.com/Azure/azure-iot-pal-arduino/tree/master/pal/samples)
* Nếu bạn đang sử dụng Raspberry Pi hoặc thiết bị ảo, hãy xem [các mẫu Python trên GitHub](https://github.com/Azure/azure-iot-sdk-python/tree/master/azure-iot-hub/samples)

## Bài tập

[Tìm hiểu về các dịch vụ đám mây](assignment.md)

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.