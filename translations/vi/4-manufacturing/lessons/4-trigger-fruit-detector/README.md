<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f74f4ccb61f00e5f7e9f49c3ed416e36",
  "translation_date": "2025-08-27T21:14:53+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/README.md",
  "language_code": "vi"
}
-->
# Kích hoạt phát hiện chất lượng trái cây từ cảm biến

![Tổng quan bài học qua hình vẽ](../../../../../translated_images/lesson-18.92c32ed1d354caa5a54baa4032cf0b172d4655e8e326ad5d46c558a0def15365.vi.jpg)

> Hình vẽ minh họa bởi [Nitya Narasimhan](https://github.com/nitya). Nhấp vào hình để xem phiên bản lớn hơn.

## Câu hỏi trước bài giảng

[Câu hỏi trước bài giảng](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/35)

## Giới thiệu

Một ứng dụng IoT không chỉ là một thiết bị duy nhất thu thập dữ liệu và gửi lên đám mây, mà thường là nhiều thiết bị cùng hoạt động để thu thập dữ liệu từ thế giới thực thông qua các cảm biến, đưa ra quyết định dựa trên dữ liệu đó, và tương tác lại với thế giới thực thông qua các bộ truyền động hoặc hình ảnh hóa.

Trong bài học này, bạn sẽ tìm hiểu thêm về cách thiết kế các ứng dụng IoT phức tạp, tích hợp nhiều cảm biến, nhiều dịch vụ đám mây để phân tích và lưu trữ dữ liệu, và hiển thị phản hồi thông qua bộ truyền động. Bạn sẽ học cách thiết kế một nguyên mẫu hệ thống kiểm soát chất lượng trái cây, bao gồm việc sử dụng cảm biến khoảng cách để kích hoạt ứng dụng IoT, và kiến trúc của nguyên mẫu này sẽ như thế nào.

Trong bài học này, chúng ta sẽ đề cập đến:

* [Thiết kế ứng dụng IoT phức tạp](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Thiết kế hệ thống kiểm soát chất lượng trái cây](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Kích hoạt kiểm tra chất lượng trái cây từ cảm biến](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Dữ liệu sử dụng cho bộ phát hiện chất lượng trái cây](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Sử dụng thiết bị phát triển để mô phỏng nhiều thiết bị IoT](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Chuyển sang sản xuất](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)

> 🗑 Đây là bài học cuối cùng trong dự án này, vì vậy sau khi hoàn thành bài học và bài tập, đừng quên dọn dẹp các dịch vụ đám mây của bạn. Bạn sẽ cần các dịch vụ này để hoàn thành bài tập, vì vậy hãy đảm bảo hoàn thành bài tập trước.
>
> Tham khảo [hướng dẫn dọn dẹp dự án của bạn](../../../clean-up.md) nếu cần để biết cách thực hiện.

## Thiết kế ứng dụng IoT phức tạp

Các ứng dụng IoT được tạo thành từ nhiều thành phần. Điều này bao gồm nhiều thiết bị và nhiều dịch vụ internet.

Các ứng dụng IoT có thể được mô tả là *thiết bị* gửi dữ liệu tạo ra *thông tin chi tiết*. Những *thông tin chi tiết* này tạo ra *hành động* để cải thiện một doanh nghiệp hoặc quy trình. Ví dụ, một động cơ (thiết bị) gửi dữ liệu nhiệt độ. Dữ liệu này được sử dụng để đánh giá liệu động cơ có hoạt động như mong đợi hay không (thông tin chi tiết). Thông tin chi tiết này được sử dụng để ưu tiên lịch bảo trì động cơ một cách chủ động (hành động).

* Các thiết bị khác nhau thu thập các mảnh dữ liệu khác nhau.
* Các dịch vụ IoT cung cấp thông tin chi tiết từ dữ liệu đó, đôi khi bổ sung thêm dữ liệu từ các nguồn khác.
* Những thông tin chi tiết này thúc đẩy hành động, bao gồm điều khiển các bộ truyền động trong thiết bị hoặc hình ảnh hóa dữ liệu.

### Kiến trúc IoT tham khảo

![Kiến trúc IoT tham khảo](../../../../../translated_images/iot-reference-architecture.2278b98b55c6d4e89bde18eada3688d893861d43507641804dd2f9d3079cfaa0.vi.png)

Hình trên minh họa một kiến trúc IoT tham khảo.

> 🎓 Một *kiến trúc tham khảo* là một kiến trúc ví dụ mà bạn có thể sử dụng làm tham khảo khi thiết kế các hệ thống mới. Trong trường hợp này, nếu bạn đang xây dựng một hệ thống IoT mới, bạn có thể theo dõi kiến trúc tham khảo, thay thế các thiết bị và dịch vụ của riêng bạn khi phù hợp.

* **Thiết bị** là các thiết bị thu thập dữ liệu từ cảm biến, có thể tương tác với các dịch vụ biên để diễn giải dữ liệu đó, chẳng hạn như các bộ phân loại hình ảnh để diễn giải dữ liệu hình ảnh. Dữ liệu từ các thiết bị được gửi đến một dịch vụ IoT.
* **Thông tin chi tiết** đến từ các ứng dụng không máy chủ hoặc từ phân tích dữ liệu đã lưu trữ.
* **Hành động** có thể là các lệnh gửi đến thiết bị hoặc hình ảnh hóa dữ liệu cho phép con người đưa ra quyết định.

![Kiến trúc IoT tham khảo](../../../../../translated_images/iot-reference-architecture-azure.0b8d2161af924cb18ae48a8558a19541cca47f27264851b5b7e56d7b8bb372ac.vi.png)

Hình trên minh họa một số thành phần và dịch vụ đã được đề cập trong các bài học trước và cách chúng liên kết với nhau trong một kiến trúc IoT tham khảo.

* **Thiết bị** - bạn đã viết mã thiết bị để thu thập dữ liệu từ cảm biến và phân tích hình ảnh bằng Custom Vision chạy cả trên đám mây và trên thiết bị biên. Dữ liệu này đã được gửi đến IoT Hub.
* **Thông tin chi tiết** - bạn đã sử dụng Azure Functions để phản hồi các tin nhắn gửi đến IoT Hub và lưu trữ dữ liệu để phân tích sau trong Azure Storage.
* **Hành động** - bạn đã điều khiển các bộ truyền động dựa trên các quyết định được thực hiện trên đám mây và các lệnh gửi đến thiết bị, và bạn đã hình ảnh hóa dữ liệu bằng Azure Maps.

✅ Hãy nghĩ về các thiết bị IoT khác mà bạn đã sử dụng, chẳng hạn như các thiết bị gia dụng thông minh. Những thiết bị, thông tin chi tiết và hành động nào liên quan đến thiết bị đó và phần mềm của nó?

Mô hình này có thể được mở rộng lớn hoặc nhỏ tùy theo nhu cầu, thêm nhiều thiết bị và nhiều dịch vụ hơn.

### Dữ liệu và bảo mật

Khi bạn xác định kiến trúc của hệ thống, bạn cần liên tục xem xét dữ liệu và bảo mật.

* Thiết bị của bạn gửi và nhận dữ liệu gì?
* Dữ liệu đó cần được bảo mật và bảo vệ như thế nào?
* Quyền truy cập vào thiết bị và dịch vụ đám mây nên được kiểm soát ra sao?

✅ Hãy nghĩ về bảo mật dữ liệu của bất kỳ thiết bị IoT nào bạn sở hữu. Bao nhiêu dữ liệu trong đó là cá nhân và cần được giữ riêng tư, cả khi truyền tải hoặc khi lưu trữ? Dữ liệu nào không nên được lưu trữ?

## Thiết kế hệ thống kiểm soát chất lượng trái cây

Bây giờ hãy áp dụng ý tưởng về thiết bị, thông tin chi tiết và hành động vào bộ phát hiện chất lượng trái cây để thiết kế một ứng dụng lớn hơn từ đầu đến cuối.

Hãy tưởng tượng bạn được giao nhiệm vụ xây dựng một bộ phát hiện chất lượng trái cây để sử dụng trong một nhà máy chế biến. Trái cây di chuyển trên hệ thống băng chuyền, nơi hiện tại nhân viên dành thời gian kiểm tra trái cây bằng tay và loại bỏ bất kỳ trái cây chưa chín nào khi nó đến. Để giảm chi phí, chủ nhà máy muốn có một hệ thống tự động.

✅ Một trong những xu hướng với sự phát triển của IoT (và công nghệ nói chung) là các công việc thủ công đang được thay thế bằng máy móc. Hãy nghiên cứu: Có bao nhiêu công việc được ước tính sẽ bị mất do IoT? Có bao nhiêu công việc mới sẽ được tạo ra để xây dựng các thiết bị IoT?

Bạn cần xây dựng một hệ thống nơi trái cây được phát hiện khi nó đến trên băng chuyền, sau đó được chụp ảnh và kiểm tra bằng mô hình AI chạy trên thiết bị biên. Kết quả sau đó được gửi lên đám mây để lưu trữ, và nếu trái cây chưa chín, một thông báo sẽ được gửi để trái cây chưa chín có thể được loại bỏ.

|   |   |
| - | - |
| **Thiết bị** | Bộ phát hiện trái cây đến trên băng chuyền<br>Camera để chụp ảnh và phân loại trái cây<br>Thiết bị biên chạy bộ phân loại<br>Thiết bị thông báo trái cây chưa chín |
| **Thông tin chi tiết** | Quyết định kiểm tra độ chín của trái cây<br>Lưu trữ kết quả phân loại độ chín<br>Xác định xem có cần cảnh báo về trái cây chưa chín hay không |
| **Hành động** | Gửi lệnh đến thiết bị để chụp ảnh trái cây và kiểm tra bằng bộ phân loại hình ảnh<br>Gửi lệnh đến thiết bị để cảnh báo rằng trái cây chưa chín |

### Tạo nguyên mẫu ứng dụng của bạn

![Kiến trúc IoT tham khảo cho kiểm tra chất lượng trái cây](../../../../../translated_images/iot-reference-architecture-fruit-quality.cc705f121c3b6fa71c800d9630935ac34bc08223a04601e35f41d5e9b5dd5207.vi.png)

Hình trên minh họa một kiến trúc tham khảo cho ứng dụng nguyên mẫu này.

* Một thiết bị IoT với cảm biến khoảng cách phát hiện trái cây đến. Thiết bị này gửi một tin nhắn lên đám mây để thông báo rằng trái cây đã được phát hiện.
* Một ứng dụng không máy chủ trên đám mây gửi lệnh đến một thiết bị khác để chụp ảnh và phân loại hình ảnh.
* Một thiết bị IoT với camera chụp ảnh và gửi nó đến bộ phân loại hình ảnh chạy trên thiết bị biên. Kết quả sau đó được gửi lên đám mây.
* Một ứng dụng không máy chủ trên đám mây lưu trữ thông tin này để phân tích sau nhằm xem tỷ lệ phần trăm trái cây chưa chín. Nếu trái cây chưa chín, ứng dụng gửi lệnh đến một thiết bị IoT khác để cảnh báo công nhân nhà máy về trái cây chưa chín thông qua đèn LED.

> 💁 Toàn bộ ứng dụng IoT này có thể được triển khai như một thiết bị duy nhất, với tất cả logic để bắt đầu phân loại hình ảnh và điều khiển đèn LED được tích hợp. Nó có thể sử dụng IoT Hub chỉ để theo dõi số lượng trái cây chưa chín được phát hiện và cấu hình thiết bị. Trong bài học này, nó được mở rộng để minh họa các khái niệm cho các ứng dụng IoT quy mô lớn.

Đối với nguyên mẫu, bạn sẽ triển khai tất cả điều này trên một thiết bị duy nhất. Nếu bạn đang sử dụng một vi điều khiển, bạn sẽ sử dụng một thiết bị biên riêng để chạy bộ phân loại hình ảnh. Bạn đã học hầu hết các điều cần thiết để có thể xây dựng điều này.

## Kích hoạt kiểm tra chất lượng trái cây từ cảm biến

Thiết bị IoT cần một loại kích hoạt nào đó để chỉ ra khi nào trái cây sẵn sàng được phân loại. Một kích hoạt cho việc này có thể là đo khoảng cách khi trái cây ở đúng vị trí trên băng chuyền bằng cách đo khoảng cách đến cảm biến.

![Cảm biến khoảng cách gửi tia laser đến các vật thể như quả chuối và đo thời gian tia phản xạ trở lại](../../../../../translated_images/proximity-sensor.f5cd752c77fb62fe.vi.png)

Cảm biến khoảng cách có thể được sử dụng để đo khoảng cách từ cảm biến đến một vật thể. Chúng thường phát ra một tia bức xạ điện từ như tia laser hoặc ánh sáng hồng ngoại, sau đó phát hiện bức xạ phản xạ từ vật thể. Thời gian giữa tia laser được gửi đi và tín hiệu phản xạ trở lại có thể được sử dụng để tính toán khoảng cách đến cảm biến.

> 💁 Bạn có thể đã sử dụng cảm biến khoảng cách mà không hề biết. Hầu hết các điện thoại thông minh sẽ tắt màn hình khi bạn áp sát chúng vào tai để tránh vô tình kết thúc cuộc gọi bằng dái tai, và điều này hoạt động nhờ cảm biến khoảng cách, phát hiện một vật thể gần màn hình trong cuộc gọi và vô hiệu hóa khả năng cảm ứng cho đến khi điện thoại cách xa một khoảng nhất định.

### Nhiệm vụ - kích hoạt phát hiện chất lượng trái cây từ cảm biến khoảng cách

Thực hiện theo hướng dẫn liên quan để sử dụng cảm biến khoảng cách để phát hiện một vật thể bằng thiết bị IoT của bạn:

* [Arduino - Wio Terminal](wio-terminal-proximity.md)
* [Máy tính đơn bảng - Raspberry Pi](pi-proximity.md)
* [Máy tính đơn bảng - Thiết bị ảo](virtual-device-proximity.md)

## Dữ liệu sử dụng cho bộ phát hiện chất lượng trái cây

Nguyên mẫu bộ phát hiện trái cây có nhiều thành phần giao tiếp với nhau.

![Các thành phần giao tiếp với nhau](../../../../../translated_images/fruit-quality-detector-message-flow.adf2a65da8fd8741ac7af11361574de89adc126785d67606bb4d2ec00467e380.vi.png)

* Một cảm biến khoảng cách đo khoảng cách đến một quả trái cây và gửi dữ liệu này đến IoT Hub
* Lệnh điều khiển camera được gửi từ IoT Hub đến thiết bị camera
* Kết quả phân loại hình ảnh được gửi đến IoT Hub
* Lệnh điều khiển đèn LED để cảnh báo khi trái cây chưa chín được gửi từ IoT Hub đến thiết bị có đèn LED

Việc định nghĩa cấu trúc của các tin nhắn này trước khi xây dựng ứng dụng là rất quan trọng.

> 💁 Hầu hết các nhà phát triển có kinh nghiệm đều từng dành hàng giờ, ngày hoặc thậm chí tuần để tìm kiếm lỗi do sự khác biệt giữa dữ liệu được gửi và dữ liệu được mong đợi.

Ví dụ - nếu bạn đang gửi thông tin nhiệt độ, bạn sẽ định nghĩa JSON như thế nào? Bạn có thể có một trường gọi là `temperature`, hoặc bạn có thể sử dụng viết tắt phổ biến `temp`.

```json
{
    "temperature": 20.7
}
```

so với:

```json
{
    "temp": 20.7
}
```

Bạn cũng phải xem xét đơn vị - nhiệt độ là °C hay °F? Nếu bạn đang đo nhiệt độ bằng một thiết bị tiêu dùng và họ thay đổi đơn vị hiển thị, bạn cần đảm bảo rằng các đơn vị gửi lên đám mây vẫn nhất quán.

✅ Hãy nghiên cứu: Vấn đề về đơn vị đã khiến tàu thăm dò Mars Climate Orbiter trị giá 125 triệu USD gặp sự cố như thế nào?

Hãy nghĩ về dữ liệu được gửi cho bộ phát hiện chất lượng trái cây. Bạn sẽ định nghĩa từng tin nhắn như thế nào? Bạn sẽ phân tích dữ liệu và đưa ra quyết định về dữ liệu nào cần gửi ở đâu?

Ví dụ - kích hoạt phân loại hình ảnh bằng cảm biến khoảng cách. Thiết bị IoT đo khoảng cách, nhưng quyết định được thực hiện ở đâu? Thiết bị có quyết định rằng trái cây đủ gần và gửi một tin nhắn để thông báo IoT Hub kích hoạt phân loại không? Hay nó gửi các phép đo khoảng cách và để IoT Hub quyết định?

Câu trả lời cho những câu hỏi như thế này là - tùy thuộc. Mỗi trường hợp sử dụng là khác nhau, đó là lý do tại sao với tư cách là một nhà phát triển IoT, bạn cần hiểu hệ thống bạn đang xây dựng, cách nó được sử dụng và dữ liệu được phát hiện.

* Nếu quyết định được thực hiện bởi IoT Hub, bạn cần gửi nhiều phép đo khoảng cách.
* Nếu bạn gửi quá nhiều tin nhắn, chi phí của IoT Hub sẽ tăng lên, và lượng băng thông cần thiết cho các thiết bị IoT của bạn (đặc biệt trong một nhà máy với hàng triệu thiết bị) cũng tăng lên. Điều này cũng có thể làm chậm thiết bị của bạn.
* Nếu bạn đưa ra quyết định trên thiết bị, bạn sẽ cần cung cấp một cách để cấu hình thiết bị để tinh chỉnh máy móc.

## Sử dụng thiết bị phát triển để mô phỏng nhiều thiết bị IoT

Để xây dựng nguyên mẫu của bạn, bạn sẽ cần bộ phát triển IoT của mình hoạt động như nhiều thiết bị, gửi dữ liệu và phản hồi lệnh.

### Mô phỏng nhiều thiết bị IoT trên Raspberry Pi hoặc phần cứng IoT ảo

Khi sử dụng một máy tính đơn bảng như Raspberry Pi, bạn có thể chạy nhiều ứng dụng cùng lúc. Điều này có nghĩa là bạn có thể mô phỏng nhiều thiết bị IoT bằng cách tạo nhiều ứng dụng, mỗi ứng dụng đại diện cho một 'thiết bị IoT'. Ví dụ, bạn có thể triển khai mỗi thiết bị như một tệp Python riêng biệt và chạy chúng trong các phiên terminal khác nhau.
> 💁 Lưu ý rằng một số phần cứng sẽ không hoạt động khi được truy cập bởi nhiều ứng dụng chạy đồng thời.
### Mô phỏng nhiều thiết bị trên vi điều khiển

Vi điều khiển phức tạp hơn khi mô phỏng nhiều thiết bị. Không giống như máy tính bảng đơn, bạn không thể chạy nhiều ứng dụng cùng lúc, mà phải tích hợp toàn bộ logic cho tất cả các thiết bị IoT riêng biệt vào một ứng dụng duy nhất.

Một số gợi ý để làm cho quá trình này dễ dàng hơn:

* Tạo một hoặc nhiều lớp cho mỗi thiết bị IoT - ví dụ các lớp có tên `DistanceSensor`, `ClassifierCamera`, `LEDController`. Mỗi lớp có thể có các phương thức `setup` và `loop` riêng được gọi bởi các hàm `setup` và `loop` chính.
* Xử lý các lệnh ở một nơi duy nhất và chuyển chúng đến lớp thiết bị liên quan khi cần thiết.
* Trong hàm `loop` chính, bạn cần xem xét thời gian cho từng thiết bị khác nhau. Ví dụ, nếu bạn có một lớp thiết bị cần xử lý mỗi 10 giây, và một lớp khác cần xử lý mỗi 1 giây, thì trong hàm `loop` chính, sử dụng độ trễ 1 giây. Mỗi lần gọi `loop` sẽ kích hoạt mã liên quan cho thiết bị cần xử lý mỗi giây, và sử dụng bộ đếm để đếm mỗi lần lặp, xử lý thiết bị khác khi bộ đếm đạt đến 10 (sau đó đặt lại bộ đếm).

## Chuyển sang sản xuất

Nguyên mẫu sẽ là cơ sở cho hệ thống sản xuất cuối cùng. Một số điểm khác biệt khi bạn chuyển sang sản xuất bao gồm:

* Các thành phần bền chắc - sử dụng phần cứng được thiết kế để chịu được tiếng ồn, nhiệt độ, rung động và áp lực trong nhà máy.
* Sử dụng giao tiếp nội bộ - một số thành phần sẽ giao tiếp trực tiếp, tránh việc phải gửi dữ liệu lên đám mây, chỉ gửi dữ liệu lên đám mây để lưu trữ. Cách thực hiện điều này phụ thuộc vào thiết lập nhà máy, có thể là giao tiếp trực tiếp hoặc chạy một phần dịch vụ IoT tại biên thông qua thiết bị gateway.
* Tùy chọn cấu hình - mỗi nhà máy và trường hợp sử dụng đều khác nhau, vì vậy phần cứng cần phải có khả năng cấu hình. Ví dụ, cảm biến khoảng cách có thể cần phát hiện các loại trái cây khác nhau ở các khoảng cách khác nhau. Thay vì mã hóa cứng khoảng cách để kích hoạt phân loại, bạn sẽ muốn điều này có thể cấu hình thông qua đám mây, ví dụ sử dụng device twin.
* Loại bỏ trái cây tự động - thay vì sử dụng đèn LED để cảnh báo rằng trái cây chưa chín, các thiết bị tự động sẽ loại bỏ nó.

✅ Nghiên cứu thêm: Có những cách nào khác mà thiết bị sản xuất sẽ khác biệt so với bộ công cụ dành cho nhà phát triển?

---

## 🚀 Thử thách

Trong bài học này, bạn đã học một số khái niệm cần biết để thiết kế một hệ thống IoT. Hãy nhớ lại các dự án trước đó. Làm thế nào để chúng phù hợp với kiến trúc tham chiếu được trình bày ở trên?

Chọn một trong các dự án đã thực hiện và suy nghĩ về thiết kế của một giải pháp phức tạp hơn, kết hợp nhiều khả năng vượt ra ngoài những gì đã được đề cập trong các dự án. Vẽ kiến trúc và suy nghĩ về tất cả các thiết bị và dịch vụ bạn sẽ cần.

Ví dụ - một thiết bị theo dõi phương tiện kết hợp GPS với các cảm biến để giám sát các yếu tố như nhiệt độ trong xe tải đông lạnh, thời gian bật/tắt động cơ, và danh tính của tài xế. Những thiết bị nào liên quan, những dịch vụ nào liên quan, dữ liệu nào được truyền tải và các cân nhắc về bảo mật và quyền riêng tư?

## Câu hỏi sau bài giảng

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/36)

## Ôn tập & Tự học

* Đọc thêm về kiến trúc IoT trong [tài liệu kiến trúc tham chiếu IoT của Azure trên Microsoft docs](https://docs.microsoft.com/azure/architecture/reference-architectures/iot?WT.mc_id=academic-17441-jabenn)
* Đọc thêm về device twin trong [tài liệu hướng dẫn sử dụng device twin trong IoT Hub trên Microsoft docs](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-device-twins?WT.mc_id=academic-17441-jabenn)
* Đọc về OPC-UA, một giao thức giao tiếp giữa máy với máy được sử dụng trong tự động hóa công nghiệp trên [trang OPC-UA trên Wikipedia](https://wikipedia.org/wiki/OPC_Unified_Architecture)

## Bài tập

[Build a fruit quality detector](assignment.md)

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.