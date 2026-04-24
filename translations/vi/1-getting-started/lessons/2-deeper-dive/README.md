# Tìm hiểu sâu hơn về IoT

![Tổng quan bài học dưới dạng sketchnote](../../../../../translated_images/vi/lesson-2.324b0580d620c25e.webp)

> Sketchnote bởi [Nitya Narasimhan](https://github.com/nitya). Nhấn vào hình để xem phiên bản lớn hơn.

Bài học này được giảng dạy trong chuỗi [Hello IoT series](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) từ [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Bài học được chia thành 2 video - một bài giảng kéo dài 1 giờ và một buổi hỏi đáp kéo dài 1 giờ để tìm hiểu sâu hơn về các phần của bài học và trả lời câu hỏi.

[![Bài học 2: Tìm hiểu sâu hơn về IoT](https://img.youtube.com/vi/t0SySWw3z9M/0.jpg)](https://youtu.be/t0SySWw3z9M)

[![Bài học 2: Tìm hiểu sâu hơn về IoT - Giờ hỏi đáp](https://img.youtube.com/vi/tTZYf9EST1E/0.jpg)](https://youtu.be/tTZYf9EST1E)

> 🎥 Nhấn vào các hình trên để xem video

## Câu hỏi trước bài giảng

[Câu hỏi trước bài giảng](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/3)

## Giới thiệu

Bài học này đi sâu hơn vào một số khái niệm đã được đề cập trong bài học trước.

Trong bài học này, chúng ta sẽ tìm hiểu:

* [Các thành phần của một ứng dụng IoT](../../../../../1-getting-started/lessons/2-deeper-dive)
* [Tìm hiểu sâu hơn về vi điều khiển](../../../../../1-getting-started/lessons/2-deeper-dive)
* [Tìm hiểu sâu hơn về máy tính bảng đơn](../../../../../1-getting-started/lessons/2-deeper-dive)

## Các thành phần của một ứng dụng IoT

Hai thành phần chính của một ứng dụng IoT là *Internet* và *thiết bị*. Hãy cùng tìm hiểu chi tiết hơn về hai thành phần này.

### Thiết bị

![Một Raspberry Pi 4](../../../../../translated_images/vi/raspberry-pi-4.fd4590d308c3d456.webp)

Phần **Thiết bị** trong IoT đề cập đến một thiết bị có thể tương tác với thế giới vật lý. Những thiết bị này thường là các máy tính nhỏ, giá rẻ, hoạt động ở tốc độ thấp và tiêu thụ ít năng lượng - ví dụ, các vi điều khiển đơn giản với bộ nhớ RAM chỉ vài kilobyte (so với gigabyte trên PC), chạy ở tốc độ chỉ vài trăm megahertz (so với gigahertz trên PC), nhưng tiêu thụ năng lượng ít đến mức có thể hoạt động trong nhiều tuần, tháng hoặc thậm chí nhiều năm chỉ với pin.

Những thiết bị này tương tác với thế giới vật lý, hoặc bằng cách sử dụng cảm biến để thu thập dữ liệu từ môi trường xung quanh, hoặc bằng cách điều khiển các đầu ra hoặc bộ truyền động để tạo ra các thay đổi vật lý. Ví dụ điển hình là một bộ điều nhiệt thông minh - một thiết bị có cảm biến nhiệt độ, một phương tiện để đặt nhiệt độ mong muốn như núm xoay hoặc màn hình cảm ứng, và một kết nối với hệ thống sưởi hoặc làm mát có thể được bật khi nhiệt độ phát hiện nằm ngoài phạm vi mong muốn. Cảm biến nhiệt độ phát hiện rằng phòng quá lạnh và một bộ truyền động sẽ bật hệ thống sưởi.

![Sơ đồ hiển thị nhiệt độ và núm xoay làm đầu vào cho thiết bị IoT, và điều khiển hệ thống sưởi làm đầu ra](../../../../../translated_images/vi/basic-thermostat.a923217fd1f37e5a.webp)

Có rất nhiều loại thiết bị khác nhau có thể hoạt động như thiết bị IoT, từ phần cứng chuyên dụng chỉ cảm nhận một thứ, đến các thiết bị đa năng, thậm chí cả điện thoại thông minh của bạn! Một chiếc điện thoại thông minh có thể sử dụng cảm biến để phát hiện thế giới xung quanh và bộ truyền động để tương tác với thế giới - ví dụ, sử dụng cảm biến GPS để phát hiện vị trí của bạn và loa để cung cấp hướng dẫn điều hướng đến một điểm đến.

✅ Hãy nghĩ về các hệ thống khác xung quanh bạn có thể đọc dữ liệu từ cảm biến và sử dụng dữ liệu đó để đưa ra quyết định. Một ví dụ là bộ điều nhiệt trên lò nướng. Bạn có thể tìm thêm ví dụ nào không?

### Internet

Phần **Internet** của một ứng dụng IoT bao gồm các ứng dụng mà thiết bị IoT có thể kết nối để gửi và nhận dữ liệu, cũng như các ứng dụng khác có thể xử lý dữ liệu từ thiết bị IoT và hỗ trợ đưa ra quyết định về các yêu cầu gửi đến các bộ truyền động của thiết bị IoT.

Một cấu hình điển hình là có một loại dịch vụ đám mây nào đó mà thiết bị IoT kết nối, và dịch vụ đám mây này xử lý các vấn đề như bảo mật, nhận tin nhắn từ thiết bị IoT và gửi tin nhắn trở lại thiết bị. Dịch vụ đám mây này sau đó sẽ kết nối với các ứng dụng khác có thể xử lý hoặc lưu trữ dữ liệu cảm biến, hoặc sử dụng dữ liệu cảm biến cùng với dữ liệu từ các hệ thống khác để đưa ra quyết định.

Các thiết bị cũng không phải lúc nào cũng kết nối trực tiếp với Internet qua WiFi hoặc kết nối có dây. Một số thiết bị sử dụng mạng lưới để giao tiếp với nhau qua các công nghệ như Bluetooth, kết nối qua một thiết bị trung tâm có kết nối Internet.

Với ví dụ về bộ điều nhiệt thông minh, bộ điều nhiệt sẽ kết nối qua WiFi gia đình đến một dịch vụ đám mây chạy trên đám mây. Nó sẽ gửi dữ liệu nhiệt độ đến dịch vụ đám mây này, và từ đó dữ liệu sẽ được ghi vào một cơ sở dữ liệu nào đó, cho phép chủ nhà kiểm tra nhiệt độ hiện tại và quá khứ qua một ứng dụng điện thoại. Một dịch vụ khác trên đám mây sẽ biết nhiệt độ mà chủ nhà mong muốn và gửi tin nhắn trở lại thiết bị IoT qua dịch vụ đám mây để yêu cầu hệ thống sưởi bật hoặc tắt.

![Sơ đồ hiển thị nhiệt độ và núm xoay làm đầu vào cho thiết bị IoT, thiết bị IoT có kết nối hai chiều với đám mây, đám mây có kết nối hai chiều với điện thoại, và điều khiển hệ thống sưởi làm đầu ra từ thiết bị IoT](../../../../../translated_images/vi/mobile-controlled-thermostat.4a994010473d8d6a.webp)

Một phiên bản thông minh hơn có thể sử dụng AI trên đám mây với dữ liệu từ các cảm biến khác kết nối với các thiết bị IoT khác như cảm biến phát hiện phòng nào đang được sử dụng, cũng như dữ liệu như thời tiết và thậm chí cả lịch của bạn, để đưa ra quyết định về cách đặt nhiệt độ một cách thông minh. Ví dụ, nó có thể tắt hệ thống sưởi nếu đọc từ lịch của bạn rằng bạn đang đi nghỉ, hoặc tắt hệ thống sưởi theo từng phòng tùy thuộc vào phòng nào bạn sử dụng, học hỏi từ dữ liệu để ngày càng chính xác hơn theo thời gian.

![Sơ đồ hiển thị nhiều cảm biến nhiệt độ và núm xoay làm đầu vào cho thiết bị IoT, thiết bị IoT có kết nối hai chiều với đám mây, đám mây có kết nối hai chiều với điện thoại, lịch và dịch vụ thời tiết, và điều khiển hệ thống sưởi làm đầu ra từ thiết bị IoT](../../../../../translated_images/vi/smarter-thermostat.a75855f15d2d9e63.webp)

✅ Những dữ liệu nào khác có thể giúp làm cho bộ điều nhiệt kết nối Internet trở nên thông minh hơn?

### IoT trên Edge

Mặc dù chữ I trong IoT là viết tắt của Internet, nhưng các thiết bị này không nhất thiết phải kết nối với Internet. Trong một số trường hợp, các thiết bị có thể kết nối với các thiết bị 'edge' - các thiết bị cổng chạy trên mạng cục bộ của bạn, cho phép bạn xử lý dữ liệu mà không cần thực hiện cuộc gọi qua Internet. Điều này có thể nhanh hơn khi bạn có nhiều dữ liệu hoặc kết nối Internet chậm, cho phép bạn hoạt động ngoại tuyến khi không thể kết nối Internet như trên tàu hoặc trong khu vực thảm họa khi ứng phó với khủng hoảng nhân đạo, và cho phép bạn giữ dữ liệu riêng tư. Một số thiết bị sẽ chứa mã xử lý được tạo bằng các công cụ đám mây và chạy mã này cục bộ để thu thập và phản hồi dữ liệu mà không cần sử dụng kết nối Internet để đưa ra quyết định.

Một ví dụ về điều này là các thiết bị nhà thông minh như Apple HomePod, Amazon Alexa hoặc Google Home, sẽ lắng nghe giọng nói của bạn bằng các mô hình AI được huấn luyện trên đám mây, nhưng chạy cục bộ trên thiết bị. Những thiết bị này sẽ 'thức dậy' khi một từ hoặc cụm từ nhất định được nói, và chỉ sau đó gửi giọng nói của bạn qua Internet để xử lý. Thiết bị sẽ ngừng gửi giọng nói tại một thời điểm thích hợp, chẳng hạn khi phát hiện một khoảng dừng trong lời nói của bạn. Mọi thứ bạn nói trước khi đánh thức thiết bị bằng từ đánh thức, và mọi thứ bạn nói sau khi thiết bị ngừng lắng nghe sẽ không được gửi qua Internet đến nhà cung cấp thiết bị, do đó sẽ được giữ riêng tư.

✅ Hãy nghĩ về các tình huống khác mà quyền riêng tư là quan trọng, vì vậy việc xử lý dữ liệu sẽ tốt hơn nếu được thực hiện trên edge thay vì trên đám mây. Gợi ý - hãy nghĩ về các thiết bị IoT có camera hoặc các thiết bị hình ảnh khác.

### Bảo mật IoT

Với bất kỳ kết nối Internet nào, bảo mật là một yếu tố quan trọng cần cân nhắc. Có một câu nói đùa cũ rằng 'chữ S trong IoT là viết tắt của Security' - nhưng thực tế không có chữ 'S' trong IoT, ngụ ý rằng nó không an toàn.

Các thiết bị IoT kết nối với một dịch vụ đám mây, và do đó chỉ an toàn như dịch vụ đám mây đó - nếu dịch vụ đám mây của bạn cho phép bất kỳ thiết bị nào kết nối, thì dữ liệu độc hại có thể được gửi, hoặc các cuộc tấn công virus có thể xảy ra. Điều này có thể gây ra hậu quả rất thực tế vì các thiết bị IoT tương tác và điều khiển các thiết bị khác. Ví dụ, [sâu Stuxnet](https://wikipedia.org/wiki/Stuxnet) đã thao túng các van trong máy ly tâm để làm hỏng chúng. Tin tặc cũng đã lợi dụng [bảo mật kém để truy cập vào các màn hình trẻ em](https://www.npr.org/sections/thetwo-way/2018/06/05/617196788/s-c-mom-says-baby-monitor-was-hacked-experts-say-many-devices-are-vulnerable) và các thiết bị giám sát gia đình khác.

> 💁 Đôi khi các thiết bị IoT và thiết bị edge chạy trên một mạng hoàn toàn cách ly khỏi Internet để giữ dữ liệu riêng tư và an toàn. Điều này được gọi là [air-gapping](https://wikipedia.org/wiki/Air_gap_(networking)).

## Tìm hiểu sâu hơn về vi điều khiển

Trong bài học trước, chúng ta đã giới thiệu về vi điều khiển. Bây giờ hãy tìm hiểu sâu hơn về chúng.

### CPU

CPU là 'bộ não' của vi điều khiển. Đây là bộ xử lý chạy mã của bạn và có thể gửi dữ liệu đến và nhận dữ liệu từ bất kỳ thiết bị kết nối nào. CPU có thể chứa một hoặc nhiều lõi - về cơ bản là một hoặc nhiều CPU có thể làm việc cùng nhau để chạy mã của bạn.

CPU dựa vào một đồng hồ để đánh dấu hàng triệu hoặc hàng tỷ lần mỗi giây. Mỗi lần đánh dấu, hoặc chu kỳ, đồng bộ hóa các hành động mà CPU có thể thực hiện. Với mỗi lần đánh dấu, CPU có thể thực thi một lệnh từ chương trình, chẳng hạn như lấy dữ liệu từ một thiết bị bên ngoài hoặc thực hiện một phép tính toán học. Chu kỳ đều đặn này cho phép tất cả các hành động được hoàn thành trước khi lệnh tiếp theo được xử lý.

Tốc độ chu kỳ đồng hồ càng nhanh, càng nhiều lệnh có thể được xử lý mỗi giây, và do đó CPU càng nhanh. Tốc độ CPU được đo bằng [Hertz (Hz)](https://wikipedia.org/wiki/Hertz), một đơn vị tiêu chuẩn mà 1 Hz có nghĩa là một chu kỳ hoặc đánh dấu đồng hồ mỗi giây.

> 🎓 Tốc độ CPU thường được đưa ra bằng MHz hoặc GHz. 1MHz là 1 triệu Hz, 1GHz là 1 tỷ Hz.

> 💁 CPU thực thi chương trình bằng [chu trình lấy-gỡ-thực thi](https://wikipedia.org/wiki/Instruction_cycle). Với mỗi lần đánh dấu đồng hồ, CPU sẽ lấy lệnh tiếp theo từ bộ nhớ, giải mã nó, sau đó thực thi nó, chẳng hạn như sử dụng đơn vị logic số học (ALU) để cộng 2 số. Một số lệnh thực thi sẽ mất nhiều lần đánh dấu để chạy, vì vậy chu trình tiếp theo sẽ chạy ở lần đánh dấu tiếp theo sau khi lệnh đã hoàn thành.

![Chu trình lấy-gỡ-thực thi hiển thị việc lấy lệnh từ chương trình được lưu trữ trong RAM, sau đó giải mã và thực thi nó trên CPU](../../../../../translated_images/vi/fetch-decode-execute.2fd6f150f6280392.webp)

Vi điều khiển có tốc độ đồng hồ thấp hơn nhiều so với máy tính để bàn hoặc laptop, hoặc thậm chí hầu hết các điện thoại thông minh. Ví dụ, Wio Terminal có CPU chạy ở tốc độ 120MHz hoặc 120.000.000 chu kỳ mỗi giây.

✅ Một máy tính PC hoặc Mac trung bình có CPU với nhiều lõi chạy ở nhiều GigaHertz, nghĩa là đồng hồ đánh dấu hàng tỷ lần mỗi giây. Hãy nghiên cứu tốc độ đồng hồ của máy tính của bạn và so sánh xem nó nhanh hơn bao nhiêu lần so với Wio Terminal.

Mỗi chu kỳ đồng hồ tiêu thụ năng lượng và tạo ra nhiệt. Tốc độ đánh dấu càng nhanh, năng lượng tiêu thụ càng nhiều và nhiệt tạo ra càng lớn. Máy tính PC có tản nhiệt và quạt để loại bỏ nhiệt, nếu không chúng sẽ quá nóng và tắt trong vài giây. Vi điều khiển thường không có cả hai vì chúng chạy mát hơn nhiều và do đó chậm hơn nhiều. Máy tính PC chạy bằng nguồn điện chính hoặc pin lớn trong vài giờ, trong khi vi điều khiển có thể chạy trong nhiều ngày, tháng hoặc thậm chí nhiều năm chỉ với pin nhỏ. Vi điều khiển cũng có thể có các lõi chạy ở các tốc độ khác nhau, chuyển sang các lõi chậm hơn tiêu thụ ít năng lượng hơn khi nhu cầu trên CPU thấp để giảm tiêu thụ năng lượng.

> 💁 Một số máy tính PC và Mac đang áp dụng cùng một sự kết hợp giữa các lõi hiệu suất cao và lõi hiệu quả thấp, chuyển đổi để tiết kiệm pin. Ví dụ, chip M1 trong các laptop Apple mới nhất có thể chuyển đổi giữa 4 lõi hiệu suất và 4 lõi hiệu quả để tối ưu hóa thời lượng pin hoặc tốc độ tùy thuộc vào tác vụ đang chạy.

✅ Tìm hiểu thêm: Đọc về CPU trong [bài viết CPU trên Wikipedia](https://wikipedia.org/wiki/Central_processing_unit)

#### Nhiệm vụ

Khám phá Wio Terminal.

Nếu bạn đang sử dụng Wio Terminal cho các bài học này, hãy thử tìm CPU. Tìm phần *Hardware Overview* trên [trang sản phẩm Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) để xem hình ảnh bên trong, và thử tìm CPU qua cửa sổ nhựa trong suốt ở mặt sau.

### Bộ nhớ

Vi điều khiển thường có hai loại bộ nhớ - bộ nhớ chương trình và bộ nhớ truy cập ngẫu nhiên (RAM).

Bộ nhớ chương trình là không bay hơi, nghĩa là bất cứ thứ gì được ghi vào đó sẽ tồn tại khi không có nguồn điện cho thiết bị. Đây là bộ nhớ lưu trữ mã chương trình của bạn.

RAM là bộ nhớ được chương trình sử dụng để chạy, chứa các biến được phân bổ bởi chương trình của bạn và dữ liệu thu thập từ các thiết bị ngoại vi. RAM là bay hơi, khi mất điện nội dung sẽ bị mất, về cơ bản đặt lại chương trình của bạn.
> 🎓 Bộ nhớ chương trình lưu trữ mã của bạn và vẫn giữ nguyên khi không có nguồn điện.
🎓 RAM được sử dụng để chạy chương trình của bạn và sẽ được đặt lại khi không có nguồn điện

Giống như CPU, bộ nhớ trên vi điều khiển nhỏ hơn rất nhiều so với PC hoặc Mac. Một PC thông thường có thể có 8 Gigabyte (GB) RAM, tương đương 8.000.000.000 byte, mỗi byte đủ để lưu trữ một chữ cái hoặc một số từ 0-255. Một vi điều khiển thường chỉ có Kilobyte (KB) RAM, với một kilobyte là 1.000 byte. Wio Terminal được đề cập ở trên có 192KB RAM, tương đương 192.000 byte - ít hơn hơn 40.000 lần so với một PC trung bình!

Biểu đồ dưới đây cho thấy sự khác biệt về kích thước tương đối giữa 192KB và 8GB - dấu chấm nhỏ ở trung tâm đại diện cho 192KB.

![So sánh giữa 192KB và 8GB - lớn hơn 40.000 lần](../../../../../translated_images/vi/ram-comparison.6beb73541b42ac6f.webp)

Dung lượng lưu trữ chương trình cũng nhỏ hơn so với PC. Một PC thông thường có thể có ổ cứng 500GB để lưu trữ chương trình, trong khi một vi điều khiển có thể chỉ có kilobyte hoặc vài megabyte (MB) dung lượng lưu trữ (1MB là 1.000KB, hoặc 1.000.000 byte). Wio Terminal có 4MB dung lượng lưu trữ chương trình.

✅ Tìm hiểu thêm: Máy tính bạn đang sử dụng để đọc nội dung này có bao nhiêu RAM và dung lượng lưu trữ? So sánh điều này với một vi điều khiển như thế nào?

### Input/Output

Vi điều khiển cần các kết nối đầu vào và đầu ra (I/O) để đọc dữ liệu từ cảm biến và gửi tín hiệu điều khiển đến các bộ truyền động. Chúng thường chứa một số chân đầu vào/đầu ra đa dụng (GPIO). Các chân này có thể được cấu hình trong phần mềm để làm đầu vào (nhận tín hiệu) hoặc đầu ra (gửi tín hiệu).

🧠⬅️ Các chân đầu vào được sử dụng để đọc giá trị từ cảm biến

🧠➡️ Các chân đầu ra gửi hướng dẫn đến bộ truyền động

✅ Bạn sẽ tìm hiểu thêm về điều này trong bài học tiếp theo.

#### Nhiệm vụ

Khám phá Wio Terminal.

Nếu bạn đang sử dụng Wio Terminal cho các bài học này, hãy tìm các chân GPIO. Tìm phần *Pinout diagram* trên [trang sản phẩm Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) để biết chân nào là chân nào. Wio Terminal đi kèm với một nhãn dán mà bạn có thể gắn ở mặt sau với số chân, hãy thêm nó ngay nếu bạn chưa làm.

### Kích thước vật lý

Vi điều khiển thường có kích thước nhỏ, với loại nhỏ nhất, [Freescale Kinetis KL03 MCU đủ nhỏ để nằm trong lõm của một quả bóng golf](https://www.edn.com/tiny-arm-cortex-m0-based-mcu-shrinks-package/). Chỉ riêng CPU trong một PC có thể đo được 40mm x 40mm, chưa kể đến các bộ tản nhiệt và quạt cần thiết để đảm bảo CPU có thể chạy hơn vài giây mà không bị quá nhiệt, lớn hơn đáng kể so với một vi điều khiển hoàn chỉnh. Bộ phát triển Wio Terminal với vi điều khiển, vỏ, màn hình và một loạt các kết nối và thành phần không lớn hơn nhiều so với một CPU Intel i9 trần, và nhỏ hơn đáng kể so với CPU với bộ tản nhiệt và quạt!

| Thiết bị                        | Kích thước            |
| ------------------------------- | --------------------- |
| Freescale Kinetis KL03          | 1.6mm x 2mm x 1mm     |
| Wio Terminal                    | 72mm x 57mm x 12mm    |
| Intel i9 CPU, Tản nhiệt và quạt | 136mm x 145mm x 103mm |

### Frameworks và hệ điều hành

Do tốc độ và kích thước bộ nhớ thấp, vi điều khiển không chạy hệ điều hành (OS) theo nghĩa của máy tính để bàn. Hệ điều hành giúp máy tính của bạn hoạt động (Windows, Linux hoặc macOS) cần rất nhiều bộ nhớ và sức mạnh xử lý để chạy các tác vụ hoàn toàn không cần thiết đối với vi điều khiển. Hãy nhớ rằng vi điều khiển thường được lập trình để thực hiện một hoặc nhiều nhiệm vụ rất cụ thể, không giống như máy tính đa năng như PC hoặc Mac cần hỗ trợ giao diện người dùng, phát nhạc hoặc phim, cung cấp công cụ để viết tài liệu hoặc mã, chơi trò chơi hoặc duyệt Internet.

Để lập trình một vi điều khiển mà không cần OS, bạn cần một số công cụ để xây dựng mã của mình theo cách mà vi điều khiển có thể chạy, sử dụng các API có thể giao tiếp với bất kỳ thiết bị ngoại vi nào. Mỗi vi điều khiển là khác nhau, vì vậy các nhà sản xuất thường hỗ trợ các framework tiêu chuẩn cho phép bạn làm theo một 'công thức' tiêu chuẩn để xây dựng mã của mình và chạy nó trên bất kỳ vi điều khiển nào hỗ trợ framework đó.

Bạn có thể lập trình vi điều khiển bằng một OS - thường được gọi là hệ điều hành thời gian thực (RTOS), vì chúng được thiết kế để xử lý việc gửi dữ liệu đến và từ các thiết bị ngoại vi trong thời gian thực. Các hệ điều hành này rất nhẹ và cung cấp các tính năng như:

* Đa luồng, cho phép mã của bạn chạy nhiều khối mã cùng một lúc, hoặc trên nhiều lõi hoặc luân phiên trên một lõi
* Kết nối mạng để giao tiếp qua Internet một cách an toàn
* Các thành phần giao diện người dùng đồ họa (GUI) để xây dựng giao diện người dùng (UI) trên các thiết bị có màn hình.

✅ Tìm hiểu về một số RTOS khác nhau: [Azure RTOS](https://azure.microsoft.com/services/rtos/?WT.mc_id=academic-17441-jabenn), [FreeRTOS](https://www.freertos.org), [Zephyr](https://www.zephyrproject.org)

#### Arduino

![Logo Arduino](../../../../../images/arduino-logo.svg)

[Arduino](https://www.arduino.cc) có lẽ là framework vi điều khiển phổ biến nhất, đặc biệt là trong giới học sinh, người đam mê và nhà sáng tạo. Arduino là một nền tảng điện tử mã nguồn mở kết hợp phần mềm và phần cứng. Bạn có thể mua các bo mạch tương thích Arduino từ chính Arduino hoặc từ các nhà sản xuất khác, sau đó lập trình bằng framework Arduino.

Các bo mạch Arduino được lập trình bằng C hoặc C++. Sử dụng C/C++ cho phép mã của bạn được biên dịch rất nhỏ và chạy nhanh, điều cần thiết trên một thiết bị bị hạn chế như vi điều khiển. Phần cốt lõi của một ứng dụng Arduino được gọi là sketch và là mã C/C++ với 2 hàm - `setup` và `loop`. Khi bo mạch khởi động, mã framework Arduino sẽ chạy hàm `setup` một lần, sau đó nó sẽ chạy hàm `loop` liên tục cho đến khi nguồn điện bị tắt.

Bạn sẽ viết mã khởi tạo của mình trong hàm `setup`, chẳng hạn như kết nối với WiFi và dịch vụ đám mây hoặc khởi tạo các chân cho đầu vào và đầu ra. Mã vòng lặp của bạn sau đó sẽ chứa mã xử lý, chẳng hạn như đọc từ cảm biến và gửi giá trị lên đám mây. Bạn thường thêm một khoảng thời gian chờ trong mỗi vòng lặp, ví dụ, nếu bạn chỉ muốn dữ liệu cảm biến được gửi mỗi 10 giây, bạn sẽ thêm một khoảng thời gian chờ 10 giây ở cuối vòng lặp để vi điều khiển có thể ngủ, tiết kiệm năng lượng, sau đó chạy lại vòng lặp khi cần sau 10 giây.

![Một sketch Arduino chạy setup trước, sau đó chạy loop liên tục](../../../../../translated_images/vi/arduino-sketch.79590cb837ff7a7c.webp)

✅ Kiến trúc chương trình này được gọi là *vòng lặp sự kiện* hoặc *vòng lặp thông điệp*. Nhiều ứng dụng sử dụng điều này dưới nền và đây là tiêu chuẩn cho hầu hết các ứng dụng máy tính để bàn chạy trên các hệ điều hành như Windows, macOS hoặc Linux. Hàm `loop` lắng nghe các thông điệp từ các thành phần giao diện người dùng như nút bấm, hoặc các thiết bị như bàn phím, và phản hồi chúng. Bạn có thể đọc thêm trong [bài viết về vòng lặp sự kiện](https://wikipedia.org/wiki/Event_loop).

Arduino cung cấp các thư viện tiêu chuẩn để tương tác với vi điều khiển và các chân I/O, với các triển khai khác nhau dưới nền để chạy trên các vi điều khiển khác nhau. Ví dụ, hàm [`delay`](https://www.arduino.cc/reference/en/language/functions/time/delay/) sẽ tạm dừng chương trình trong một khoảng thời gian nhất định, hàm [`digitalRead`](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/) sẽ đọc giá trị `HIGH` hoặc `LOW` từ chân được chỉ định, bất kể mã được chạy trên bo mạch nào. Các thư viện tiêu chuẩn này có nghĩa là mã Arduino được viết cho một bo mạch có thể được biên dịch lại cho bất kỳ bo mạch Arduino nào khác và sẽ chạy, miễn là các chân giống nhau và các bo mạch hỗ trợ các tính năng tương tự.

Có một hệ sinh thái lớn các thư viện Arduino của bên thứ ba cho phép bạn thêm các tính năng bổ sung vào các dự án Arduino của mình, chẳng hạn như sử dụng cảm biến và bộ truyền động hoặc kết nối với các dịch vụ IoT đám mây.

##### Nhiệm vụ

Khám phá Wio Terminal.

Nếu bạn đang sử dụng Wio Terminal cho các bài học này, hãy đọc lại mã bạn đã viết trong bài học trước. Tìm hàm `setup` và `loop`. Theo dõi đầu ra serial để xem hàm loop được gọi liên tục. Thử thêm mã vào hàm `setup` để ghi vào cổng serial và quan sát rằng mã này chỉ được gọi một lần mỗi khi bạn khởi động lại. Thử khởi động lại thiết bị của bạn bằng công tắc nguồn ở bên cạnh để cho thấy mã này được gọi mỗi lần thiết bị khởi động lại.

## Tìm hiểu sâu hơn về máy tính bo mạch đơn

Trong bài học trước, chúng ta đã giới thiệu về máy tính bo mạch đơn. Bây giờ hãy tìm hiểu sâu hơn về chúng.

### Raspberry Pi

![Logo Raspberry Pi](../../../../../translated_images/vi/raspberry-pi-logo.4efaa16605cee054.webp)

[Raspberry Pi Foundation](https://www.raspberrypi.org) là một tổ chức từ thiện tại Anh được thành lập vào năm 2009 nhằm thúc đẩy việc học tập khoa học máy tính, đặc biệt ở cấp độ trường học. Là một phần của sứ mệnh này, họ đã phát triển một máy tính bo mạch đơn, gọi là Raspberry Pi. Raspberry Pi hiện có 3 biến thể - phiên bản đầy đủ kích thước, phiên bản nhỏ hơn Pi Zero, và một module tính toán có thể được tích hợp vào thiết bị IoT cuối cùng của bạn.

![Raspberry Pi 4](../../../../../translated_images/vi/raspberry-pi-4.fd4590d308c3d456.webp)

Phiên bản mới nhất của Raspberry Pi đầy đủ kích thước là Raspberry Pi 4B. Nó có CPU lõi tứ (4 lõi) chạy ở tốc độ 1.5GHz, RAM 2, 4 hoặc 8GB, ethernet gigabit, WiFi, 2 cổng HDMI hỗ trợ màn hình 4k, một cổng âm thanh và video composite, các cổng USB (2 USB 2.0, 2 USB 3.0), 40 chân GPIO, một cổng kết nối camera cho module camera Raspberry Pi, và một khe cắm thẻ SD. Tất cả điều này trên một bo mạch có kích thước 88mm x 58mm x 19.5mm và được cấp nguồn bởi nguồn USB-C 3A. Giá khởi điểm là 35 USD, rẻ hơn nhiều so với PC hoặc Mac.

> 💁 Cũng có một Pi400, một máy tính tất cả trong một với Pi4 được tích hợp vào bàn phím.

![Raspberry Pi Zero](../../../../../translated_images/vi/raspberry-pi-zero.f7a4133e1e7d54bb.webp)

Pi Zero nhỏ hơn nhiều, với công suất thấp hơn. Nó có CPU lõi đơn 1GHz, RAM 512MB, WiFi (trong model Zero W), một cổng HDMI duy nhất, một cổng micro-USB, 40 chân GPIO, một cổng kết nối camera cho module camera Raspberry Pi, và một khe cắm thẻ SD. Nó có kích thước 65mm x 30mm x 5mm, và tiêu thụ rất ít năng lượng. Pi Zero có giá 5 USD, với phiên bản W có WiFi giá 10 USD.

> 🎓 CPU trong cả hai đều là bộ xử lý ARM, khác với bộ xử lý Intel/AMD x86 hoặc x64 mà bạn tìm thấy trong hầu hết các PC và Mac. Chúng tương tự như các CPU bạn tìm thấy trong một số vi điều khiển, cũng như gần như tất cả các điện thoại di động, Microsoft Surface X, và các máy Mac Apple Silicon mới.

Tất cả các biến thể của Raspberry Pi đều chạy một phiên bản Debian Linux gọi là Raspberry Pi OS. Phiên bản này có sẵn dưới dạng phiên bản nhẹ không có giao diện desktop, rất phù hợp cho các dự án 'headless' nơi bạn không cần màn hình, hoặc phiên bản đầy đủ với môi trường desktop đầy đủ, bao gồm trình duyệt web, ứng dụng văn phòng, công cụ lập trình và trò chơi. Vì hệ điều hành là một phiên bản của Debian Linux, bạn có thể cài đặt bất kỳ ứng dụng hoặc công cụ nào chạy trên Debian và được xây dựng cho bộ xử lý ARM bên trong Pi.

#### Nhiệm vụ

Khám phá Raspberry Pi.

Nếu bạn đang sử dụng Raspberry Pi cho các bài học này, hãy tìm hiểu về các thành phần phần cứng khác nhau trên bo mạch.

* Bạn có thể tìm thấy thông tin chi tiết về các bộ xử lý được sử dụng trên [trang tài liệu phần cứng Raspberry Pi](https://www.raspberrypi.org/documentation/hardware/raspberrypi/). Tìm hiểu về bộ xử lý được sử dụng trong Pi mà bạn đang sử dụng.
* Xác định vị trí các chân GPIO. Đọc thêm về chúng trên [tài liệu GPIO Raspberry Pi](https://www.raspberrypi.org/documentation/hardware/raspberrypi/gpio/README.md). Sử dụng [hướng dẫn sử dụng chân GPIO](https://www.raspberrypi.org/documentation/usage/gpio/README.md) để xác định các chân khác nhau trên Pi của bạn.

### Lập trình máy tính bo mạch đơn

Máy tính bo mạch đơn là máy tính đầy đủ, chạy một hệ điều hành đầy đủ. Điều này có nghĩa là có một loạt các ngôn ngữ lập trình, framework và công cụ bạn có thể sử dụng để lập trình chúng, không giống như vi điều khiển phụ thuộc vào hỗ trợ cho bo mạch trong các framework như Arduino. Hầu hết các ngôn ngữ lập trình đều có thư viện có thể truy cập các chân GPIO để gửi và nhận dữ liệu từ cảm biến và bộ truyền động.

✅ Bạn quen thuộc với những ngôn ngữ lập trình nào? Chúng có được hỗ trợ trên Linux không?

Ngôn ngữ lập trình phổ biến nhất để xây dựng các ứng dụng IoT trên Raspberry Pi là Python. Có một hệ sinh thái lớn các phần cứng được thiết kế cho Pi, và gần như tất cả các phần cứng này đều bao gồm mã cần thiết để sử dụng chúng dưới dạng thư viện Python. Một số hệ sinh thái này dựa trên 'hats' - được gọi như vậy vì chúng nằm trên Pi như một chiếc mũ và kết nối với một ổ cắm lớn đến 40 chân GPIO. Những hats này cung cấp các khả năng bổ sung, chẳng hạn như màn hình, cảm biến, xe điều khiển từ xa, hoặc bộ chuyển đổi để cho phép bạn cắm các cảm biến với cáp tiêu chuẩn.
### Sử dụng máy tính bảng đơn trong triển khai IoT chuyên nghiệp

Máy tính bảng đơn được sử dụng trong các triển khai IoT chuyên nghiệp, không chỉ đơn thuần là các bộ công cụ dành cho nhà phát triển. Chúng có thể cung cấp một cách mạnh mẽ để điều khiển phần cứng và thực hiện các tác vụ phức tạp như chạy các mô hình học máy. Ví dụ, có một [module tính toán Raspberry Pi 4](https://www.raspberrypi.org/blog/raspberry-pi-compute-module-4/) cung cấp toàn bộ sức mạnh của Raspberry Pi 4 nhưng ở dạng nhỏ gọn và rẻ hơn, không có hầu hết các cổng, được thiết kế để lắp đặt vào phần cứng tùy chỉnh.

---

## 🚀 Thử thách

Thử thách trong bài học trước là liệt kê càng nhiều thiết bị IoT trong nhà, trường học hoặc nơi làm việc của bạn càng tốt. Với mỗi thiết bị trong danh sách này, bạn nghĩ chúng được xây dựng dựa trên vi điều khiển, máy tính bảng đơn, hay thậm chí là sự kết hợp của cả hai?

## Câu hỏi sau bài giảng

[Câu hỏi sau bài giảng](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/4)

## Ôn tập & Tự học

* Đọc [hướng dẫn bắt đầu với Arduino](https://www.arduino.cc/en/Guide/Introduction) để hiểu thêm về nền tảng Arduino.
* Đọc [giới thiệu về Raspberry Pi 4](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/) để tìm hiểu thêm về Raspberry Pi.
* Tìm hiểu thêm về một số khái niệm và từ viết tắt trong bài viết [What the FAQ are CPUs, MPUs, MCUs, and GPUs trên Electrical Engineering Journal](https://www.eejournal.com/article/what-the-faq-are-cpus-mpus-mcus-and-gpus/).

✅ Sử dụng các hướng dẫn này, cùng với chi phí được hiển thị bằng cách theo các liên kết trong [hướng dẫn phần cứng](../../../hardware.md) để quyết định nền tảng phần cứng bạn muốn sử dụng, hoặc liệu bạn có muốn sử dụng một thiết bị ảo hay không.

## Bài tập

[So sánh và đối chiếu vi điều khiển và máy tính bảng đơn](assignment.md)

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn tham khảo chính thức. Đối với các thông tin quan trọng, chúng tôi khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp từ con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.