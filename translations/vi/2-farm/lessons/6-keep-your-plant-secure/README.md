# Giữ an toàn cho cây trồng của bạn

![Một bản vẽ tóm tắt bài học này](../../../../../translated_images/vi/lesson-10.829c86b80b9403bb.webp)

> Bản vẽ bởi [Nitya Narasimhan](https://github.com/nitya). Nhấp vào hình ảnh để xem phiên bản lớn hơn.

## Câu hỏi trước bài giảng

[Câu hỏi trước bài giảng](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/19)

## Giới thiệu

Trong những bài học trước, bạn đã tạo một thiết bị IoT giám sát đất và kết nối nó với đám mây. Nhưng điều gì sẽ xảy ra nếu các hacker làm việc cho một nông dân đối thủ chiếm quyền kiểm soát thiết bị IoT của bạn? Điều gì sẽ xảy ra nếu họ gửi các chỉ số độ ẩm đất cao để cây của bạn không bao giờ được tưới, hoặc bật hệ thống tưới nước liên tục, làm cây chết vì tưới quá nhiều và khiến bạn tốn một khoản tiền lớn cho nước?

Trong bài học này, bạn sẽ học cách bảo mật các thiết bị IoT. Vì đây là bài học cuối cùng của dự án này, bạn cũng sẽ học cách dọn dẹp tài nguyên đám mây của mình, giảm thiểu các chi phí tiềm năng.

Trong bài học này, chúng ta sẽ đề cập đến:

* [Tại sao bạn cần bảo mật thiết bị IoT?](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Mật mã học](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Bảo mật thiết bị IoT của bạn](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Tạo và sử dụng chứng chỉ X.509](../../../../../2-farm/lessons/6-keep-your-plant-secure)

> 🗑 Đây là bài học cuối cùng trong dự án này, vì vậy sau khi hoàn thành bài học và bài tập, đừng quên dọn dẹp các dịch vụ đám mây của bạn. Bạn sẽ cần các dịch vụ này để hoàn thành bài tập, vì vậy hãy đảm bảo hoàn thành trước.
>
> Tham khảo [hướng dẫn dọn dẹp dự án của bạn](../../../clean-up.md) nếu cần để biết cách thực hiện.

## Tại sao bạn cần bảo mật thiết bị IoT?

Bảo mật IoT liên quan đến việc đảm bảo rằng chỉ các thiết bị được mong đợi mới có thể kết nối với dịch vụ IoT đám mây của bạn và gửi dữ liệu, và chỉ dịch vụ đám mây của bạn mới có thể gửi lệnh đến các thiết bị. Dữ liệu IoT cũng có thể mang tính cá nhân, bao gồm dữ liệu y tế hoặc nhạy cảm, vì vậy toàn bộ ứng dụng của bạn cần xem xét bảo mật để ngăn chặn việc rò rỉ dữ liệu này.

Nếu ứng dụng IoT của bạn không được bảo mật, có một số rủi ro:

* Một thiết bị giả mạo có thể gửi dữ liệu sai, khiến ứng dụng của bạn phản hồi không chính xác. Ví dụ, họ có thể gửi các chỉ số độ ẩm đất cao liên tục, khiến hệ thống tưới nước của bạn không bao giờ bật và cây của bạn chết vì thiếu nước.
* Người dùng trái phép có thể đọc dữ liệu từ các thiết bị IoT, bao gồm dữ liệu cá nhân hoặc quan trọng đối với doanh nghiệp.
* Hacker có thể gửi lệnh để điều khiển thiết bị theo cách gây hư hại cho thiết bị hoặc phần cứng kết nối.
* Bằng cách kết nối với một thiết bị IoT, hacker có thể sử dụng điều này để truy cập các mạng khác và xâm nhập vào các hệ thống riêng tư.
* Người dùng độc hại có thể truy cập dữ liệu cá nhân và sử dụng nó để tống tiền.

Đây là những tình huống thực tế và xảy ra thường xuyên. Một số ví dụ đã được đưa ra trong các bài học trước, nhưng đây là một số ví dụ khác:

* Năm 2018, hacker đã sử dụng một điểm truy cập WiFi mở trên bộ điều nhiệt bể cá để xâm nhập vào mạng của một sòng bạc và đánh cắp dữ liệu. [The Hacker News - Casino Gets Hacked Through Its Internet-Connected Fish Tank Thermometer](https://thehackernews.com/2018/04/iot-hacking-thermometer.html)
* Năm 2016, botnet Mirai đã phát động một cuộc tấn công từ chối dịch vụ (DDoS) vào Dyn, một nhà cung cấp dịch vụ Internet, làm gián đoạn một phần lớn Internet. Botnet này sử dụng phần mềm độc hại để kết nối với các thiết bị IoT như DVR và camera sử dụng tên người dùng và mật khẩu mặc định, từ đó phát động cuộc tấn công. [The Guardian - DDoS attack that disrupted internet was largest of its kind in history, experts say](https://www.theguardian.com/technology/2016/oct/26/ddos-attack-dyn-mirai-botnet)
* Spiral Toys có một cơ sở dữ liệu người dùng của đồ chơi CloudPets được kết nối bị công khai trên Internet. [Troy Hunt - Data from connected CloudPets teddy bears leaked and ransomed, exposing kids' voice messages](https://www.troyhunt.com/data-from-connected-cloudpets-teddy-bears-leaked-and-ransomed-exposing-kids-voice-messages/).
* Strava gắn thẻ các vận động viên chạy bộ mà bạn chạy qua và hiển thị lộ trình của họ, cho phép người lạ dễ dàng biết nơi bạn sống. [Kim Komndo - Fitness app could lead a stranger right to your home — change this setting](https://www.komando.com/security-privacy/strava-fitness-app-privacy/755349/).

✅ Nghiên cứu thêm: Tìm kiếm thêm các ví dụ về các vụ hack IoT và rò rỉ dữ liệu IoT, đặc biệt là với các thiết bị cá nhân như bàn chải đánh răng hoặc cân kết nối Internet. Hãy suy nghĩ về tác động của những vụ hack này đối với nạn nhân hoặc khách hàng.

> 💁 Bảo mật là một chủ đề rất lớn, và bài học này chỉ đề cập đến một số khía cạnh cơ bản liên quan đến việc kết nối thiết bị của bạn với đám mây. Các chủ đề khác sẽ không được đề cập bao gồm giám sát thay đổi dữ liệu trong quá trình truyền, hack trực tiếp vào thiết bị, hoặc thay đổi cấu hình thiết bị. Hack IoT là một mối đe dọa lớn đến mức các công cụ như [Azure Defender for IoT](https://azure.microsoft.com/services/azure-defender-for-iot/?WT.mc_id=academic-17441-jabenn) đã được phát triển. Các công cụ này tương tự như các công cụ chống virus và bảo mật mà bạn có thể có trên máy tính của mình, nhưng được thiết kế cho các thiết bị IoT nhỏ, tiêu thụ ít năng lượng.

## Mật mã học

Khi một thiết bị kết nối với một dịch vụ IoT, nó sử dụng một ID để xác định chính nó. Vấn đề là ID này có thể bị sao chép - một hacker có thể thiết lập một thiết bị độc hại sử dụng cùng ID với thiết bị thật nhưng gửi dữ liệu giả mạo.

![Cả thiết bị hợp lệ và thiết bị độc hại đều có thể sử dụng cùng ID để gửi dữ liệu](../../../../../translated_images/vi/iot-device-and-hacked-device-connecting.e0671675df74d6d9.webp)

Cách giải quyết vấn đề này là chuyển đổi dữ liệu được gửi thành một định dạng bị mã hóa, sử dụng một giá trị nào đó để mã hóa dữ liệu mà chỉ thiết bị và đám mây biết. Quá trình này được gọi là *mã hóa*, và giá trị được sử dụng để mã hóa dữ liệu được gọi là *khóa mã hóa*.

![Nếu sử dụng mã hóa, chỉ các tin nhắn được mã hóa mới được chấp nhận, các tin nhắn khác sẽ bị từ chối](../../../../../translated_images/vi/iot-device-and-hacked-device-connecting-encryption.5941aff601fc978f.webp)

Dịch vụ đám mây sau đó có thể chuyển đổi dữ liệu trở lại định dạng có thể đọc được, sử dụng một quá trình gọi là *giải mã*, sử dụng cùng một khóa mã hóa hoặc một *khóa giải mã*. Nếu tin nhắn mã hóa không thể được giải mã bằng khóa, thiết bị đã bị hack và tin nhắn sẽ bị từ chối.

Kỹ thuật để thực hiện mã hóa và giải mã được gọi là *mật mã học*.

### Mật mã học thời kỳ đầu

Các loại mật mã học sớm nhất là các mã thay thế, có từ 3.500 năm trước. Mã thay thế liên quan đến việc thay thế một chữ cái bằng một chữ cái khác. Ví dụ, [mã Caesar](https://wikipedia.org/wiki/Caesar_cipher) liên quan đến việc dịch chuyển bảng chữ cái theo một số lượng xác định, chỉ người gửi tin nhắn mã hóa và người nhận dự kiến biết số lượng chữ cái cần dịch chuyển.

[Mã Vigenère](https://wikipedia.org/wiki/Vigenère_cipher) đã phát triển hơn bằng cách sử dụng các từ để mã hóa văn bản, sao cho mỗi chữ cái trong văn bản gốc được dịch chuyển bởi một số lượng khác nhau, thay vì luôn dịch chuyển cùng một số lượng chữ cái.

Mật mã học được sử dụng cho nhiều mục đích khác nhau, chẳng hạn như bảo vệ công thức men gốm ở Mesopotamia cổ đại, viết các ghi chú tình yêu bí mật ở Ấn Độ, hoặc giữ bí mật các câu thần chú cổ đại của Ai Cập.

### Mật mã học hiện đại

Mật mã học hiện đại tiên tiến hơn nhiều, khiến việc phá mã khó khăn hơn so với các phương pháp thời kỳ đầu. Mật mã học hiện đại sử dụng toán học phức tạp để mã hóa dữ liệu với số lượng khóa có thể quá lớn để các cuộc tấn công brute force có thể thực hiện được.

Mật mã học được sử dụng trong nhiều cách khác nhau để giao tiếp an toàn. Nếu bạn đang đọc trang này trên GitHub, bạn có thể nhận thấy địa chỉ trang web bắt đầu bằng *HTTPS*, nghĩa là giao tiếp giữa trình duyệt của bạn và máy chủ web của GitHub được mã hóa. Nếu ai đó có thể đọc lưu lượng internet giữa trình duyệt của bạn và GitHub, họ sẽ không thể đọc được dữ liệu vì nó đã được mã hóa. Máy tính của bạn thậm chí có thể mã hóa toàn bộ dữ liệu trên ổ cứng để nếu ai đó đánh cắp nó, họ sẽ không thể đọc được bất kỳ dữ liệu nào của bạn mà không có mật khẩu.

> 🎓 HTTPS là viết tắt của HyperText Transfer Protocol **Secure**

Thật không may, không phải mọi thứ đều an toàn. Một số thiết bị không có bảo mật, một số khác được bảo mật bằng các khóa dễ bị phá mã, hoặc đôi khi tất cả các thiết bị cùng loại sử dụng cùng một khóa. Đã có những trường hợp các thiết bị IoT rất cá nhân đều có cùng một mật khẩu để kết nối qua WiFi hoặc Bluetooth. Nếu bạn có thể kết nối với thiết bị của mình, bạn cũng có thể kết nối với thiết bị của người khác. Một khi đã kết nối, bạn có thể truy cập một số dữ liệu rất riêng tư hoặc kiểm soát thiết bị của họ.

> 💁 Mặc dù mật mã học hiện đại rất phức tạp và có tuyên bố rằng việc phá mã có thể mất hàng tỷ năm, sự phát triển của máy tính lượng tử đã dẫn đến khả năng phá vỡ tất cả các mã hóa hiện tại trong một thời gian rất ngắn!

### Khóa đối xứng và bất đối xứng

Mã hóa có hai loại - đối xứng và bất đối xứng.

**Mã hóa đối xứng** sử dụng cùng một khóa để mã hóa và giải mã dữ liệu. Cả người gửi và người nhận đều cần biết cùng một khóa. Đây là loại ít an toàn nhất, vì khóa cần được chia sẻ bằng cách nào đó. Để người gửi gửi một tin nhắn mã hóa cho người nhận, người gửi trước tiên có thể phải gửi khóa cho người nhận.

![Mã hóa đối xứng sử dụng cùng một khóa để mã hóa và giải mã tin nhắn](../../../../../translated_images/vi/send-message-symmetric-key.a2e8ad0d495896ff.webp)

Nếu khóa bị đánh cắp trong quá trình truyền, hoặc người gửi hoặc người nhận bị hack và khóa bị lộ, mã hóa có thể bị phá.

![Mã hóa đối xứng chỉ an toàn nếu hacker không lấy được khóa - nếu có, họ có thể chặn và giải mã tin nhắn](../../../../../translated_images/vi/send-message-symmetric-key-hacker.e7cb53db1707adfb.webp)

**Mã hóa bất đối xứng** sử dụng 2 khóa - một khóa mã hóa và một khóa giải mã, được gọi là cặp khóa công khai/riêng tư. Khóa công khai được sử dụng để mã hóa tin nhắn, nhưng không thể được sử dụng để giải mã, khóa riêng tư được sử dụng để giải mã tin nhắn nhưng không thể được sử dụng để mã hóa.

![Mã hóa bất đối xứng sử dụng một khóa khác để mã hóa và giải mã. Khóa mã hóa được gửi cho bất kỳ người gửi tin nhắn nào để họ có thể mã hóa tin nhắn trước khi gửi cho người nhận sở hữu các khóa](../../../../../translated_images/vi/send-message-asymmetric.7abe327c62615b8c.webp)

Người nhận chia sẻ khóa công khai của họ, và người gửi sử dụng khóa này để mã hóa tin nhắn. Sau khi tin nhắn được gửi, người nhận giải mã nó bằng khóa riêng tư của họ. Mã hóa bất đối xứng an toàn hơn vì khóa riêng tư được giữ bí mật bởi người nhận và không bao giờ được chia sẻ. Bất kỳ ai cũng có thể có khóa công khai vì nó chỉ có thể được sử dụng để mã hóa tin nhắn.

Mã hóa đối xứng nhanh hơn mã hóa bất đối xứng, mã hóa bất đối xứng an toàn hơn. Một số hệ thống sẽ sử dụng cả hai - sử dụng mã hóa bất đối xứng để mã hóa và chia sẻ khóa đối xứng, sau đó sử dụng khóa đối xứng để mã hóa tất cả dữ liệu. Điều này làm cho việc chia sẻ khóa đối xứng giữa người gửi và người nhận an toàn hơn, và nhanh hơn khi mã hóa và giải mã dữ liệu.

## Bảo mật thiết bị IoT của bạn

Thiết bị IoT có thể được bảo mật bằng cách sử dụng mã hóa đối xứng hoặc bất đối xứng. Mã hóa đối xứng dễ thực hiện hơn, nhưng ít an toàn hơn.

### Khóa đối xứng

Khi bạn thiết lập thiết bị IoT của mình để tương tác với IoT Hub, bạn đã sử dụng một chuỗi kết nối. Một ví dụ về chuỗi kết nối là:

```output
HostName=soil-moisture-sensor.azure-devices.net;DeviceId=soil-moisture-sensor;SharedAccessKey=Bhry+ind7kKEIDxubK61RiEHHRTrPl7HUow8cEm/mU0=
```

Chuỗi kết nối này bao gồm ba phần được phân tách bằng dấu chấm phẩy, với mỗi phần là một cặp khóa và giá trị:

| Khóa | Giá trị | Mô tả |
| --- | ----- | ----------- |
| HostName | `soil-moisture-sensor.azure-devices.net` | URL của IoT Hub |
| DeviceId | `soil-moisture-sensor` | ID duy nhất của thiết bị |
| SharedAccessKey | `Bhry+ind7kKEIDxubK61RiEHHRTrPl7HUow8cEm/mU0=` | Một khóa đối xứng được biết bởi thiết bị và IoT Hub |

Phần cuối cùng của chuỗi kết nối này, `SharedAccessKey`, là khóa đối xứng được biết bởi cả thiết bị và IoT Hub. Khóa này không bao giờ được gửi từ thiết bị đến đám mây, hoặc từ đám mây đến thiết bị. Thay vào đó, nó được sử dụng để mã hóa dữ liệu được gửi hoặc nhận.

✅ Thực hiện một thí nghiệm. Bạn nghĩ điều gì sẽ xảy ra nếu bạn thay đổi phần `SharedAccessKey` của chuỗi kết nối khi kết nối thiết bị IoT của mình? Hãy thử xem.

Khi thiết bị lần đầu tiên cố gắng kết nối, nó gửi một mã thông báo chữ ký truy cập chia sẻ (SAS) bao gồm URL của IoT Hub, một dấu thời gian mà chữ ký truy cập sẽ hết hạn (thường là 1 ngày kể từ thời điểm hiện tại), và một chữ ký. Chữ ký này bao gồm URL và thời gian hết hạn được mã hóa bằng khóa truy cập chia sẻ từ chuỗi kết nối.

IoT Hub giải mã chữ ký này bằng khóa truy cập chia sẻ, và nếu giá trị giải mã khớp với URL và thời gian hết hạn, thiết bị được phép kết nối. Nó cũng xác minh rằng thời gian hiện tại là trước thời gian hết hạn, để ngăn chặn một thiết bị độc hại bắt giữ mã thông báo SAS của một thiết bị thật và sử dụng nó.

Đây là một cách tinh tế để xác minh rằng người gửi là thiết bị chính xác. Bằng cách gửi một số dữ liệu đã biết ở cả dạng không mã hóa và mã hóa, máy chủ có thể xác minh thiết bị bằng cách đảm bảo khi nó giải mã dữ liệu mã hóa, kết quả khớp với phiên bản không mã hóa đã được gửi. Nếu khớp, thì cả người gửi và người nhận đều có cùng một khóa mã hóa đối xứng.
💁 Vì thời gian hết hạn, thiết bị IoT của bạn cần biết thời gian chính xác, thường được lấy từ máy chủ [NTP](https://wikipedia.org/wiki/Network_Time_Protocol). Nếu thời gian không chính xác, kết nối sẽ thất bại.
Sau khi kết nối, tất cả dữ liệu gửi đến IoT Hub từ thiết bị hoặc từ IoT Hub đến thiết bị sẽ được mã hóa bằng khóa truy cập chia sẻ.

✅ Bạn nghĩ điều gì sẽ xảy ra nếu nhiều thiết bị sử dụng chung chuỗi kết nối?

> 💁 Đây là một thực hành bảo mật không tốt khi lưu trữ khóa này trong mã. Nếu hacker lấy được mã nguồn của bạn, họ có thể lấy được khóa của bạn. Ngoài ra, việc phát hành mã cũng trở nên khó khăn hơn vì bạn sẽ cần biên dịch lại với khóa được cập nhật cho mỗi thiết bị. Tốt hơn là tải khóa này từ một mô-đun bảo mật phần cứng - một con chip trên thiết bị IoT lưu trữ các giá trị được mã hóa mà mã của bạn có thể đọc được.
>
> Khi học IoT, thường dễ dàng hơn khi đặt khóa trong mã, như bạn đã làm trong bài học trước, nhưng bạn phải đảm bảo rằng khóa này không được kiểm tra vào hệ thống kiểm soát mã nguồn công khai.

Các thiết bị có 2 khóa và 2 chuỗi kết nối tương ứng. Điều này cho phép bạn xoay vòng các khóa - tức là chuyển từ một khóa sang khóa khác nếu khóa đầu tiên bị xâm phạm và tạo lại khóa đầu tiên.

### Chứng chỉ X.509

Khi bạn sử dụng mã hóa bất đối xứng với cặp khóa công khai/khóa riêng, bạn cần cung cấp khóa công khai của mình cho bất kỳ ai muốn gửi dữ liệu cho bạn. Vấn đề là, làm thế nào để người nhận khóa của bạn chắc chắn rằng đó thực sự là khóa công khai của bạn, không phải của ai đó giả mạo bạn? Thay vì cung cấp một khóa, bạn có thể cung cấp khóa công khai của mình bên trong một chứng chỉ đã được xác minh bởi một bên thứ ba đáng tin cậy, gọi là chứng chỉ X.509.

Chứng chỉ X.509 là các tài liệu kỹ thuật số chứa phần khóa công khai của cặp khóa công khai/khóa riêng. Chúng thường được cấp bởi một trong số các tổ chức đáng tin cậy gọi là [Certification authorities](https://wikipedia.org/wiki/Certificate_authority) (CAs) và được ký số bởi CA để chỉ ra rằng khóa là hợp lệ và đến từ bạn. Bạn tin tưởng chứng chỉ và rằng khóa công khai là từ người mà chứng chỉ nói rằng nó đến từ, bởi vì bạn tin tưởng CA, tương tự như cách bạn tin tưởng hộ chiếu hoặc bằng lái xe vì bạn tin tưởng quốc gia cấp nó. Chứng chỉ có chi phí, vì vậy bạn cũng có thể 'tự ký', tức là tạo một chứng chỉ tự mình ký để sử dụng cho mục đích thử nghiệm.

> 💁 Bạn không bao giờ nên sử dụng chứng chỉ tự ký cho một phiên bản sản xuất.

Các chứng chỉ này có một số trường, bao gồm thông tin về người sở hữu khóa công khai, chi tiết của CA đã cấp chứng chỉ, thời gian hiệu lực và chính khóa công khai. Trước khi sử dụng một chứng chỉ, thực hành tốt là xác minh nó bằng cách kiểm tra xem nó đã được ký bởi CA gốc hay chưa.

✅ Bạn có thể đọc danh sách đầy đủ các trường trong chứng chỉ tại [Microsoft Understanding X.509 Public Key Certificates tutorial](https://docs.microsoft.com/azure/iot-hub/tutorial-x509-certificates?WT.mc_id=academic-17441-jabenn#certificate-fields)

Khi sử dụng chứng chỉ X.509, cả người gửi và người nhận đều có khóa công khai và khóa riêng của riêng mình, cũng như cả hai đều có chứng chỉ X.509 chứa khóa công khai. Sau đó, họ trao đổi chứng chỉ X.509 bằng cách nào đó, sử dụng khóa công khai của nhau để mã hóa dữ liệu họ gửi và khóa riêng của mình để giải mã dữ liệu họ nhận.

![Thay vì chia sẻ một khóa công khai, bạn có thể chia sẻ một chứng chỉ. Người sử dụng chứng chỉ có thể xác minh rằng nó đến từ bạn bằng cách kiểm tra với cơ quan cấp chứng chỉ đã ký nó.](../../../../../translated_images/vi/send-message-certificate.9cc576ac1e46b76e.webp)

Một lợi thế lớn của việc sử dụng chứng chỉ X.509 là chúng có thể được chia sẻ giữa các thiết bị. Bạn có thể tạo một chứng chỉ, tải nó lên IoT Hub và sử dụng nó cho tất cả các thiết bị của mình. Mỗi thiết bị sau đó chỉ cần biết khóa riêng để giải mã các tin nhắn nhận được từ IoT Hub.

Chứng chỉ được sử dụng bởi thiết bị của bạn để mã hóa các tin nhắn gửi đến IoT Hub được Microsoft công bố. Đây là chứng chỉ mà nhiều dịch vụ Azure sử dụng và đôi khi được tích hợp sẵn trong các SDK.

> 💁 Hãy nhớ rằng, một khóa công khai chỉ đơn giản là công khai. Khóa công khai của Azure chỉ có thể được sử dụng để mã hóa dữ liệu gửi đến Azure, không phải để giải mã, vì vậy nó có thể được chia sẻ ở mọi nơi, bao gồm cả trong mã nguồn. Ví dụ, bạn có thể thấy nó trong [Azure IoT C SDK source code](https://github.com/Azure/azure-iot-sdk-c/blob/master/certs/certs.c).

✅ Có rất nhiều thuật ngữ liên quan đến chứng chỉ X.509. Bạn có thể đọc định nghĩa của một số thuật ngữ bạn có thể gặp phải trong [The layman’s guide to X.509 certificate jargon](https://techcommunity.microsoft.com/t5/internet-of-things/the-layman-s-guide-to-x-509-certificate-jargon/ba-p/2203540?WT.mc_id=academic-17441-jabenn)

## Tạo và sử dụng chứng chỉ X.509

Các bước để tạo một chứng chỉ X.509 là:

1. Tạo một cặp khóa công khai/khóa riêng. Một trong những thuật toán được sử dụng rộng rãi nhất để tạo cặp khóa công khai/khóa riêng được gọi là [Rivest–Shamir–Adleman](https://wikipedia.org/wiki/RSA_(cryptosystem))(RSA).

1. Gửi khóa công khai cùng với dữ liệu liên quan để ký, bởi CA hoặc tự ký.

Azure CLI có các lệnh để tạo một danh tính thiết bị mới trong IoT Hub và tự động tạo cặp khóa công khai/khóa riêng và tạo một chứng chỉ tự ký.

> 💁 Nếu bạn muốn xem các bước chi tiết, thay vì sử dụng Azure CLI, bạn có thể tìm thấy chúng trong [Using OpenSSL to create self-signed certificates tutorial in the Microsoft IoT Hub documentation](https://docs.microsoft.com/azure/iot-hub/tutorial-x509-self-sign?WT.mc_id=academic-17441-jabenn)

### Nhiệm vụ - tạo danh tính thiết bị sử dụng chứng chỉ X.509

1. Chạy lệnh sau để đăng ký danh tính thiết bị mới, tự động tạo các khóa và chứng chỉ:

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor-x509 \
                                      --am x509_thumbprint \
                                      --output-dir . \
                                      --hub-name <hub_name>
    ```

    Thay thế `<hub_name>` bằng tên bạn đã sử dụng cho IoT Hub của mình.

    Lệnh này sẽ tạo một thiết bị với ID `soil-moisture-sensor-x509` để phân biệt với danh tính thiết bị bạn đã tạo trong bài học trước. Lệnh này cũng sẽ tạo 2 tệp trong thư mục hiện tại:

    * `soil-moisture-sensor-x509-key.pem` - tệp này chứa khóa riêng cho thiết bị.
    * `soil-moisture-sensor-x509-cert.pem` - đây là tệp chứng chỉ X.509 cho thiết bị.

    Hãy giữ các tệp này an toàn! Tệp khóa riêng không nên được kiểm tra vào hệ thống kiểm soát mã nguồn công khai.

### Nhiệm vụ - sử dụng chứng chỉ X.509 trong mã thiết bị của bạn

Làm theo hướng dẫn phù hợp để kết nối thiết bị IoT của bạn với đám mây bằng chứng chỉ X.509:

* [Arduino - Wio Terminal](wio-terminal-x509.md)
* [Máy tính đơn bảng - Raspberry Pi/Thiết bị IoT ảo](single-board-computer-x509.md)

---

## 🚀 Thử thách

Có nhiều cách để tạo, quản lý và xóa các dịch vụ Azure như Resource Groups và IoT Hubs. Một cách là [Azure Portal](https://portal.azure.com?WT.mc_id=academic-17441-jabenn) - giao diện web cung cấp GUI để quản lý các dịch vụ Azure của bạn.

Truy cập [portal.azure.com](https://portal.azure.com?WT.mc_id=academic-17441-jabenn) và khám phá cổng thông tin. Xem liệu bạn có thể tạo một IoT Hub bằng cổng thông tin, sau đó xóa nó.

**Gợi ý** - khi tạo dịch vụ qua cổng thông tin, bạn không cần tạo Resource Group trước, một nhóm có thể được tạo khi bạn tạo dịch vụ. Hãy đảm bảo xóa nó khi bạn hoàn thành!

Bạn có thể tìm thấy nhiều tài liệu, hướng dẫn và hướng dẫn về Azure Portal trong [Azure portal documentation](https://docs.microsoft.com/azure/azure-portal/?WT.mc_id=academic-17441-jabenn).

## Câu hỏi sau bài giảng

[Câu hỏi sau bài giảng](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/20)

## Ôn tập & Tự học

* Tìm hiểu về lịch sử mật mã trên [History of cryptography page on Wikipedia](https://wikipedia.org/wiki/History_of_cryptography).
* Tìm hiểu về chứng chỉ X.509 trên [X.509 page on Wikipedia](https://wikipedia.org/wiki/X.509).

## Bài tập

[Tạo một thiết bị IoT mới](assignment.md)

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.