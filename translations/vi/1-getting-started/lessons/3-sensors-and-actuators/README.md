<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e9ee00eb5fc55922a73762acc542166b",
  "translation_date": "2025-08-27T22:25:08+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/README.md",
  "language_code": "vi"
}
-->
# Tương tác với thế giới vật lý bằng cảm biến và bộ truyền động

![Tổng quan bài học dưới dạng sketchnote](../../../../../translated_images/vi/lesson-3.cc3b7b4cd646de598698cce043c0393fd62ef42bac2eaf60e61272cd844250f4.jpg)

> Sketchnote bởi [Nitya Narasimhan](https://github.com/nitya). Nhấp vào hình ảnh để xem phiên bản lớn hơn.

Bài học này được giảng dạy trong chuỗi [Hello IoT series](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) từ [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Bài học được chia thành 2 video - một bài giảng kéo dài 1 giờ và một buổi hỏi đáp kéo dài 1 giờ để đi sâu hơn vào các phần của bài học và trả lời câu hỏi.

[![Bài học 3: Tương tác với thế giới vật lý bằng cảm biến và bộ truyền động](https://img.youtube.com/vi/Lqalu1v6aF4/0.jpg)](https://youtu.be/Lqalu1v6aF4)

[![Bài học 3: Tương tác với thế giới vật lý bằng cảm biến và bộ truyền động - Buổi hỏi đáp](https://img.youtube.com/vi/qR3ekcMlLWA/0.jpg)](https://youtu.be/qR3ekcMlLWA)

> 🎥 Nhấp vào các hình ảnh trên để xem video

## Câu hỏi trước bài giảng

[Câu hỏi trước bài giảng](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/5)

## Giới thiệu

Bài học này giới thiệu hai khái niệm quan trọng cho thiết bị IoT của bạn - cảm biến và bộ truyền động. Bạn sẽ thực hành với cả hai, thêm cảm biến ánh sáng vào dự án IoT của mình, sau đó thêm một đèn LED được điều khiển bởi mức ánh sáng, tạo ra một chiếc đèn ngủ.

Trong bài học này, chúng ta sẽ tìm hiểu:

* [Cảm biến là gì?](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Sử dụng cảm biến](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Các loại cảm biến](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Bộ truyền động là gì?](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Sử dụng bộ truyền động](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Các loại bộ truyền động](../../../../../1-getting-started/lessons/3-sensors-and-actuators)

## Cảm biến là gì?

Cảm biến là các thiết bị phần cứng cảm nhận thế giới vật lý - nghĩa là chúng đo lường một hoặc nhiều thuộc tính xung quanh và gửi thông tin đến thiết bị IoT. Cảm biến bao gồm một loạt các thiết bị vì có rất nhiều thứ có thể được đo lường, từ các thuộc tính tự nhiên như nhiệt độ không khí đến các tương tác vật lý như chuyển động.

Một số cảm biến phổ biến bao gồm:

* Cảm biến nhiệt độ - cảm nhận nhiệt độ không khí hoặc nhiệt độ của vật mà chúng tiếp xúc. Đối với người dùng và nhà phát triển, các cảm biến này thường được kết hợp với cảm biến áp suất không khí và độ ẩm trong một thiết bị duy nhất.
* Nút bấm - cảm nhận khi chúng bị nhấn.
* Cảm biến ánh sáng - phát hiện mức độ ánh sáng và có thể dành cho các màu cụ thể, ánh sáng UV, ánh sáng hồng ngoại (IR), hoặc ánh sáng nhìn thấy chung.
* Camera - cảm nhận hình ảnh của thế giới bằng cách chụp ảnh hoặc truyền video.
* Gia tốc kế - cảm nhận chuyển động theo nhiều hướng.
* Micro - cảm nhận âm thanh, có thể là mức âm thanh chung hoặc âm thanh định hướng.

✅ Hãy nghiên cứu. Điện thoại của bạn có những loại cảm biến nào?

Tất cả các cảm biến đều có một điểm chung - chúng chuyển đổi những gì chúng cảm nhận thành tín hiệu điện có thể được thiết bị IoT giải thích. Cách tín hiệu điện này được giải thích phụ thuộc vào cảm biến, cũng như giao thức truyền thông được sử dụng để giao tiếp với thiết bị IoT.

## Sử dụng cảm biến

Làm theo hướng dẫn phù hợp dưới đây để thêm cảm biến vào thiết bị IoT của bạn:

* [Arduino - Wio Terminal](wio-terminal-sensor.md)
* [Máy tính đơn bảng - Raspberry Pi](pi-sensor.md)
* [Máy tính đơn bảng - Thiết bị ảo](virtual-device-sensor.md)

## Các loại cảm biến

Cảm biến có thể là analog hoặc kỹ thuật số.

### Cảm biến analog

Một số cảm biến cơ bản nhất là cảm biến analog. Các cảm biến này nhận một điện áp từ thiết bị IoT, các thành phần cảm biến điều chỉnh điện áp này, và điện áp được trả về từ cảm biến được đo để đưa ra giá trị cảm biến.

> 🎓 Điện áp là thước đo mức độ đẩy để di chuyển điện từ nơi này sang nơi khác, chẳng hạn từ cực dương của pin đến cực âm. Ví dụ, một pin AA tiêu chuẩn là 1.5V (V là ký hiệu cho volt) và có thể đẩy điện với lực 1.5V từ cực dương đến cực âm của nó. Các phần cứng điện khác nhau yêu cầu các điện áp khác nhau để hoạt động, ví dụ, một đèn LED có thể sáng với điện áp từ 2-3V, nhưng một bóng đèn sợi đốt 100W sẽ cần 240V. Bạn có thể đọc thêm về điện áp trên [trang Wikipedia về điện áp](https://wikipedia.org/wiki/Voltage).

Một ví dụ là chiết áp. Đây là một núm xoay mà bạn có thể điều chỉnh giữa hai vị trí và cảm biến đo lường sự xoay này.

![Một chiết áp được đặt ở điểm giữa, nhận 5 volt và trả về 3.8 volt](../../../../../translated_images/vi/potentiometer.35a348b9ce22f6ec.webp)

Thiết bị IoT sẽ gửi một tín hiệu điện đến chiết áp với một điện áp, chẳng hạn 5 volt (5V). Khi chiết áp được điều chỉnh, nó thay đổi điện áp đi ra từ phía bên kia. Hãy tưởng tượng bạn có một chiết áp được gắn nhãn như một núm xoay từ 0 đến [11](https://wikipedia.org/wiki/Up_to_eleven), chẳng hạn như núm âm lượng trên một bộ khuếch đại. Khi chiết áp ở vị trí tắt hoàn toàn (0), thì 0V (0 volt) sẽ đi ra. Khi nó ở vị trí bật hoàn toàn (11), thì 5V (5 volt) sẽ đi ra.

> 🎓 Đây là một sự đơn giản hóa, và bạn có thể đọc thêm về chiết áp và điện trở biến đổi trên [trang Wikipedia về chiết áp](https://wikipedia.org/wiki/Potentiometer).

Điện áp đi ra từ cảm biến sau đó được thiết bị IoT đọc, và thiết bị có thể phản hồi lại. Tùy thuộc vào cảm biến, điện áp này có thể là một giá trị tùy ý hoặc có thể ánh xạ đến một đơn vị tiêu chuẩn. Ví dụ, một cảm biến nhiệt độ analog dựa trên [thermistor](https://wikipedia.org/wiki/Thermistor) thay đổi điện trở của nó tùy thuộc vào nhiệt độ. Điện áp đầu ra sau đó có thể được chuyển đổi thành nhiệt độ theo Kelvin, và tương ứng thành °C hoặc °F, bằng các tính toán trong mã.

✅ Bạn nghĩ điều gì sẽ xảy ra nếu cảm biến trả về điện áp cao hơn điện áp được gửi (ví dụ từ một nguồn điện bên ngoài)? ⛔️ KHÔNG thử nghiệm điều này.

#### Chuyển đổi từ analog sang kỹ thuật số

Thiết bị IoT là kỹ thuật số - chúng không thể làm việc với các giá trị analog, chúng chỉ làm việc với 0 và 1. Điều này có nghĩa là các giá trị cảm biến analog cần được chuyển đổi thành tín hiệu kỹ thuật số trước khi chúng có thể được xử lý. Nhiều thiết bị IoT có bộ chuyển đổi analog sang kỹ thuật số (ADC) để chuyển đổi các đầu vào analog thành các biểu diễn kỹ thuật số của giá trị của chúng. Các cảm biến cũng có thể làm việc với ADC thông qua một bảng kết nối. Ví dụ, trong hệ sinh thái Seeed Grove với Raspberry Pi, các cảm biến analog kết nối với các cổng cụ thể trên một 'hat' được gắn trên Pi kết nối với các chân GPIO của Pi, và hat này có một ADC để chuyển đổi điện áp thành tín hiệu kỹ thuật số có thể được gửi từ các chân GPIO của Pi.

Hãy tưởng tượng bạn có một cảm biến ánh sáng analog được kết nối với một thiết bị IoT sử dụng 3.3V và trả về giá trị 1V. Giá trị 1V này không có ý nghĩa gì trong thế giới kỹ thuật số, vì vậy cần được chuyển đổi. Điện áp sẽ được chuyển đổi thành giá trị analog bằng một thang đo tùy thuộc vào thiết bị và cảm biến. Một ví dụ là cảm biến ánh sáng Seeed Grove, cảm biến này trả về các giá trị từ 0 đến 1,023. Đối với cảm biến này chạy ở 3.3V, một đầu ra 1V sẽ là giá trị 300. Một thiết bị IoT không thể xử lý 300 như một giá trị analog, vì vậy giá trị này sẽ được chuyển đổi thành `0000000100101100`, biểu diễn nhị phân của 300 bởi hat Grove. Sau đó, giá trị này sẽ được xử lý bởi thiết bị IoT.

✅ Nếu bạn chưa biết về nhị phân, hãy nghiên cứu một chút để tìm hiểu cách các con số được biểu diễn bằng 0 và 1. [Bài học giới thiệu về nhị phân của BBC Bitesize](https://www.bbc.co.uk/bitesize/guides/zwsbwmn/revision/1) là một nơi tuyệt vời để bắt đầu.

Từ góc độ lập trình, tất cả điều này thường được xử lý bởi các thư viện đi kèm với cảm biến, vì vậy bạn không cần phải lo lắng về việc chuyển đổi này. Đối với cảm biến ánh sáng Grove, bạn sẽ sử dụng thư viện Python và gọi thuộc tính `light`, hoặc sử dụng thư viện Arduino và gọi `analogRead` để nhận giá trị 300.

### Cảm biến kỹ thuật số

Cảm biến kỹ thuật số, giống như cảm biến analog, phát hiện thế giới xung quanh bằng cách sử dụng sự thay đổi trong điện áp. Điểm khác biệt là chúng trả về tín hiệu kỹ thuật số, hoặc bằng cách chỉ đo hai trạng thái hoặc bằng cách sử dụng ADC tích hợp. Cảm biến kỹ thuật số ngày càng trở nên phổ biến để tránh việc phải sử dụng ADC trong bảng kết nối hoặc trên chính thiết bị IoT.

Cảm biến kỹ thuật số đơn giản nhất là nút bấm hoặc công tắc. Đây là cảm biến với hai trạng thái, bật hoặc tắt.

![Một nút bấm nhận 5 volt. Khi không được nhấn, nó trả về 0 volt, khi được nhấn, nó trả về 5 volt](../../../../../translated_images/vi/button.eadb560b77ac45e56f523d9d8876e40444f63b419e33eb820082d461fa79490b.png)

Các chân trên thiết bị IoT như chân GPIO có thể đo tín hiệu này trực tiếp dưới dạng 0 hoặc 1. Nếu điện áp gửi đi giống với điện áp trả về, giá trị đọc là 1, nếu không giá trị đọc là 0. Không cần phải chuyển đổi tín hiệu, nó chỉ có thể là 1 hoặc 0.

> 💁 Điện áp không bao giờ chính xác hoàn toàn, đặc biệt khi các thành phần trong cảm biến sẽ có một số điện trở, vì vậy thường có một mức dung sai. Ví dụ, các chân GPIO trên Raspberry Pi hoạt động ở 3.3V, và đọc tín hiệu trả về trên 1.8V là 1, dưới 1.8V là 0.

* 3.3V được gửi vào nút bấm. Nút bấm đang tắt nên 0V được trả về, cho giá trị 0.
* 3.3V được gửi vào nút bấm. Nút bấm đang bật nên 3.3V được trả về, cho giá trị 1.

Các cảm biến kỹ thuật số tiên tiến hơn đọc các giá trị analog, sau đó chuyển đổi chúng bằng ADC tích hợp thành tín hiệu kỹ thuật số. Ví dụ, một cảm biến nhiệt độ kỹ thuật số vẫn sử dụng cặp nhiệt điện giống như cảm biến analog, và vẫn đo sự thay đổi điện áp gây ra bởi điện trở của cặp nhiệt điện ở nhiệt độ hiện tại. Thay vì trả về giá trị analog và dựa vào thiết bị hoặc bảng kết nối để chuyển đổi thành tín hiệu kỹ thuật số, một ADC tích hợp trong cảm biến sẽ chuyển đổi giá trị và gửi nó dưới dạng một chuỗi 0 và 1 đến thiết bị IoT. Các 0 và 1 này được gửi theo cách giống như tín hiệu kỹ thuật số cho nút bấm với 1 là điện áp đầy đủ và 0 là 0V.

![Một cảm biến nhiệt độ kỹ thuật số chuyển đổi một giá trị analog thành dữ liệu nhị phân với 0 là 0 volt và 1 là 5 volt trước khi gửi nó đến thiết bị IoT](../../../../../translated_images/vi/temperature-as-digital.85004491b977bae1.webp)

Việc gửi dữ liệu kỹ thuật số cho phép các cảm biến trở nên phức tạp hơn và gửi dữ liệu chi tiết hơn, thậm chí là dữ liệu được mã hóa cho các cảm biến bảo mật. Một ví dụ là camera. Đây là một cảm biến chụp hình ảnh và gửi nó dưới dạng dữ liệu kỹ thuật số chứa hình ảnh đó, thường ở định dạng nén như JPEG, để được thiết bị IoT đọc. Nó thậm chí có thể truyền video bằng cách chụp hình ảnh và gửi hoặc toàn bộ khung hình từng khung hoặc một luồng video nén.

## Bộ truyền động là gì?

Bộ truyền động là ngược lại với cảm biến - chúng chuyển đổi tín hiệu điện từ thiết bị IoT của bạn thành một tương tác với thế giới vật lý như phát sáng, phát âm thanh, hoặc di chuyển động cơ.

Một số bộ truyền động phổ biến bao gồm:

* LED - phát sáng khi được bật.
* Loa - phát âm thanh dựa trên tín hiệu gửi đến, từ một loa đơn giản đến một loa âm thanh có thể phát nhạc.
* Động cơ bước - chuyển đổi tín hiệu thành một lượng quay xác định, chẳng hạn như xoay một núm 90°.
* Rơ-le - là các công tắc có thể được bật hoặc tắt bằng tín hiệu điện. Chúng cho phép một điện áp nhỏ từ thiết bị IoT bật các điện áp lớn hơn.
* Màn hình - là các bộ truyền động phức tạp hơn và hiển thị thông tin trên màn hình đa đoạn. Màn hình có thể từ các màn hình LED đơn giản đến các màn hình video độ phân giải cao.

✅ Hãy nghiên cứu. Điện thoại của bạn có những loại bộ truyền động nào?

## Sử dụng bộ truyền động

Làm theo hướng dẫn phù hợp dưới đây để thêm bộ truyền động vào thiết bị IoT của bạn, được điều khiển bởi cảm biến, để tạo ra một chiếc đèn ngủ IoT. Nó sẽ thu thập mức ánh sáng từ cảm biến ánh sáng và sử dụng bộ truyền động dưới dạng đèn LED để phát sáng khi mức ánh sáng được phát hiện quá thấp.

![Biểu đồ luồng của bài tập cho thấy mức ánh sáng được đọc và kiểm tra, và đèn LED được điều khiển](../../../../../translated_images/vi/assignment-1-flow.7552a51acb1a5ec858dca6e855cdbb44206434006df8ba3799a25afcdab1665d.png)

* [Arduino - Wio Terminal](wio-terminal-actuator.md)
* [Máy tính đơn bảng - Raspberry Pi](pi-actuator.md)
* [Máy tính đơn bảng - Thiết bị ảo](virtual-device-actuator.md)

## Các loại bộ truyền động

Giống như cảm biến, bộ truyền động có thể là analog hoặc kỹ thuật số.

### Bộ truyền động analog

Bộ truyền động analog nhận tín hiệu analog và chuyển đổi nó thành một loại tương tác nào đó, nơi tương tác thay đổi dựa trên điện áp được cung cấp.

Một ví dụ là đèn có thể điều chỉnh độ sáng, chẳng hạn như những chiếc đèn bạn có thể có trong nhà. Lượng điện áp được cung cấp cho đèn quyết định độ sáng của nó.
![Một bóng đèn mờ ở điện áp thấp và sáng hơn ở điện áp cao](../../../../../translated_images/vi/dimmable-light.9ceffeb195dec1a849da718b2d71b32c35171ff7dfea9c07bbf82646a67acf6b.png)

Giống như với các cảm biến, thiết bị IoT thực tế hoạt động trên tín hiệu số, không phải tín hiệu analog. Điều này có nghĩa là để gửi một tín hiệu analog, thiết bị IoT cần một bộ chuyển đổi số sang analog (DAC), hoặc trực tiếp trên thiết bị IoT, hoặc trên một bảng kết nối. Bộ chuyển đổi này sẽ chuyển đổi các số 0 và 1 từ thiết bị IoT thành điện áp analog mà bộ truyền động có thể sử dụng.

✅ Bạn nghĩ điều gì sẽ xảy ra nếu thiết bị IoT gửi một điện áp cao hơn mức mà bộ truyền động có thể xử lý?
⛔️ KHÔNG thử nghiệm điều này.

#### Điều chế độ rộng xung

Một lựa chọn khác để chuyển đổi tín hiệu số từ thiết bị IoT sang tín hiệu analog là điều chế độ rộng xung (PWM). Điều này liên quan đến việc gửi nhiều xung số ngắn hoạt động như thể đó là một tín hiệu analog.

Ví dụ, bạn có thể sử dụng PWM để điều khiển tốc độ của một động cơ.

Hãy tưởng tượng bạn đang điều khiển một động cơ với nguồn cung cấp 5V. Bạn gửi một xung ngắn đến động cơ của mình, chuyển điện áp lên cao (5V) trong hai phần trăm giây (0.02s). Trong thời gian đó, động cơ của bạn có thể quay một phần mười vòng, hoặc 36°. Sau đó tín hiệu tạm dừng trong hai phần trăm giây (0.02s), gửi tín hiệu thấp (0V). Mỗi chu kỳ bật rồi tắt kéo dài 0.04s. Chu kỳ sau đó lặp lại.

![Điều chế độ rộng xung quay động cơ ở tốc độ 150 RPM](../../../../../translated_images/vi/pwm-motor-150rpm.83347ac04ca38482.webp)

Điều này có nghĩa là trong một giây bạn có 25 xung 5V kéo dài 0.02s để quay động cơ, mỗi xung được theo sau bởi 0.02s tạm dừng ở 0V không quay động cơ. Mỗi xung quay động cơ một phần mười vòng, nghĩa là động cơ hoàn thành 2.5 vòng mỗi giây. Bạn đã sử dụng tín hiệu số để quay động cơ ở tốc độ 2.5 vòng mỗi giây, hoặc 150 [vòng mỗi phút](https://wikipedia.org/wiki/Revolutions_per_minute) (một đơn vị đo tốc độ quay không chuẩn).

```output
25 pulses per second x 0.1 rotations per pulse = 2.5 rotations per second
2.5 rotations per second x 60 seconds in a minute = 150rpm
```

> 🎓 Khi tín hiệu PWM bật trong một nửa thời gian và tắt trong một nửa thời gian, nó được gọi là [chu kỳ làm việc 50%](https://wikipedia.org/wiki/Duty_cycle). Chu kỳ làm việc được đo bằng phần trăm thời gian tín hiệu ở trạng thái bật so với trạng thái tắt.

![Điều chế độ rộng xung quay động cơ ở tốc độ 75 RPM](../../../../../translated_images/vi/pwm-motor-75rpm.a5e4c939934b6e14.webp)

Bạn có thể thay đổi tốc độ động cơ bằng cách thay đổi kích thước của các xung. Ví dụ, với cùng một động cơ, bạn có thể giữ thời gian chu kỳ là 0.04s, với xung bật giảm một nửa xuống còn 0.01s, và xung tắt tăng lên 0.03s. Bạn có cùng số lượng xung mỗi giây (25), nhưng mỗi xung bật chỉ bằng một nửa chiều dài. Một xung ngắn chỉ quay động cơ một phần hai mươi vòng, và với 25 xung mỗi giây sẽ hoàn thành 1.25 vòng mỗi giây hoặc 75rpm. Bằng cách thay đổi tốc độ xung của tín hiệu số, bạn đã giảm một nửa tốc độ của động cơ analog.

```output
25 pulses per second x 0.05 rotations per pulse = 1.25 rotations per second
1.25 rotations per second x 60 seconds in a minute = 75rpm
```

✅ Làm thế nào bạn có thể giữ cho động cơ quay mượt mà, đặc biệt ở tốc độ thấp? Bạn sẽ sử dụng một số lượng nhỏ các xung dài với các khoảng tạm dừng dài hay nhiều xung rất ngắn với các khoảng tạm dừng rất ngắn?

> 💁 Một số cảm biến cũng sử dụng PWM để chuyển đổi tín hiệu analog sang tín hiệu số.

> 🎓 Bạn có thể đọc thêm về điều chế độ rộng xung trên [trang Wikipedia về điều chế độ rộng xung](https://wikipedia.org/wiki/Pulse-width_modulation).

### Bộ truyền động số

Bộ truyền động số, giống như cảm biến số, hoặc có hai trạng thái được điều khiển bởi điện áp cao hoặc thấp, hoặc có DAC tích hợp để chuyển đổi tín hiệu số sang tín hiệu analog.

Một bộ truyền động số đơn giản là đèn LED. Khi một thiết bị gửi tín hiệu số là 1, một điện áp cao được gửi để làm sáng đèn LED. Khi tín hiệu số là 0 được gửi, điện áp giảm xuống 0V và đèn LED tắt.

![Một đèn LED tắt ở 0 volt và bật ở 5V](../../../../../translated_images/vi/led.ec6d94f66676a174ad06d9fa9ea49c2ee89beb18b312d5c6476467c66375b07f.png)

✅ Bạn có thể nghĩ đến những bộ truyền động hai trạng thái đơn giản nào khác? Một ví dụ là solenoid, một nam châm điện có thể được kích hoạt để thực hiện các việc như di chuyển chốt cửa để khóa/mở khóa cửa.

Các bộ truyền động số tiên tiến hơn, chẳng hạn như màn hình, yêu cầu dữ liệu số được gửi theo các định dạng nhất định. Chúng thường đi kèm với các thư viện giúp việc gửi dữ liệu đúng để điều khiển chúng trở nên dễ dàng hơn.

---

## 🚀 Thử thách

Thử thách trong hai bài học trước là liệt kê càng nhiều thiết bị IoT trong nhà, trường học hoặc nơi làm việc của bạn càng tốt và quyết định xem chúng được xây dựng dựa trên vi điều khiển hay máy tính bảng đơn, hoặc thậm chí là sự kết hợp của cả hai.

Đối với mỗi thiết bị bạn đã liệt kê, các cảm biến và bộ truyền động nào được kết nối với chúng? Mục đích của mỗi cảm biến và bộ truyền động được kết nối với các thiết bị này là gì?

## Câu hỏi sau bài giảng

[Câu hỏi sau bài giảng](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/6)

## Ôn tập & Tự học

* Đọc về điện và mạch trên [ThingLearn](http://thinglearn.jenlooper.com/curriculum/).
* Đọc về các loại cảm biến nhiệt độ khác nhau trên [Hướng dẫn cảm biến nhiệt độ của Seeed Studios](https://www.seeedstudio.com/blog/2019/10/14/temperature-sensors-for-arduino-projects/)
* Đọc về đèn LED trên [trang Wikipedia về đèn LED](https://wikipedia.org/wiki/Light-emitting_diode)

## Bài tập

[Nghiên cứu cảm biến và bộ truyền động](assignment.md)

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.