# Giới thiệu về IoT

![Tóm tắt bài học bằng sketchnote](../../../../../translated_images/vi/lesson-1.2606670fa61ee904.webp)

> Sketchnote bởi [Nitya Narasimhan](https://github.com/nitya). Nhấn vào hình ảnh để xem phiên bản lớn hơn.

Bài học này được giảng dạy trong chuỗi [Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) từ [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Bài học được chia thành 2 video - một bài giảng kéo dài 1 giờ và một buổi hỏi đáp kéo dài 1 giờ để đi sâu hơn vào các phần của bài học và trả lời câu hỏi.

[![Bài học 1: Giới thiệu về IoT](https://img.youtube.com/vi/bVFfcYh6UBw/0.jpg)](https://youtu.be/bVFfcYh6UBw)

[![Bài học 1: Giới thiệu về IoT - Giờ hỏi đáp](https://img.youtube.com/vi/YI772q5v3yI/0.jpg)](https://youtu.be/YI772q5v3yI)

> 🎥 Nhấn vào các hình ảnh trên để xem video

## Câu hỏi trước bài giảng

[Câu hỏi trước bài giảng](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/1)

## Giới thiệu

Bài học này bao gồm một số chủ đề cơ bản về Internet of Things (IoT) và hướng dẫn bạn thiết lập phần cứng của mình.

Trong bài học này, chúng ta sẽ tìm hiểu:

* [Internet of Things là gì?](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Thiết bị IoT](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Thiết lập thiết bị của bạn](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Ứng dụng của IoT](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Ví dụ về các thiết bị IoT xung quanh bạn](../../../../../1-getting-started/lessons/1-introduction-to-iot)

## Internet of Things là gì?

Thuật ngữ 'Internet of Things' được đặt ra bởi [Kevin Ashton](https://wikipedia.org/wiki/Kevin_Ashton) vào năm 1999, để chỉ việc kết nối Internet với thế giới vật lý thông qua các cảm biến. Kể từ đó, thuật ngữ này được sử dụng để mô tả bất kỳ thiết bị nào tương tác với thế giới vật lý xung quanh, hoặc bằng cách thu thập dữ liệu từ cảm biến, hoặc cung cấp các tương tác thực tế thông qua các bộ truyền động (các thiết bị thực hiện hành động như bật công tắc hoặc thắp sáng đèn LED), thường được kết nối với các thiết bị khác hoặc Internet.

> **Cảm biến** thu thập thông tin từ thế giới, chẳng hạn như đo tốc độ, nhiệt độ hoặc vị trí.
>
> **Bộ truyền động** chuyển đổi tín hiệu điện thành các tương tác thực tế như kích hoạt công tắc, bật đèn, phát âm thanh, hoặc gửi tín hiệu điều khiển đến phần cứng khác, ví dụ như bật ổ cắm điện.

IoT không chỉ là các thiết bị - nó bao gồm các dịch vụ dựa trên đám mây có thể xử lý dữ liệu cảm biến hoặc gửi yêu cầu đến các bộ truyền động được kết nối với thiết bị IoT. Nó cũng bao gồm các thiết bị không có hoặc không cần kết nối Internet, thường được gọi là thiết bị biên (edge devices). Đây là các thiết bị có thể tự xử lý và phản hồi dữ liệu cảm biến, thường sử dụng các mô hình AI được huấn luyện trên đám mây.

IoT là một lĩnh vực công nghệ phát triển nhanh chóng. Ước tính đến cuối năm 2020, có 30 tỷ thiết bị IoT được triển khai và kết nối với Internet. Nhìn về tương lai, ước tính đến năm 2025, các thiết bị IoT sẽ thu thập gần 80 zettabyte dữ liệu, tương đương 80 nghìn tỷ gigabyte. Đó là một lượng dữ liệu khổng lồ!

![Biểu đồ hiển thị số lượng thiết bị IoT hoạt động theo thời gian, với xu hướng tăng từ dưới 5 tỷ vào năm 2015 lên hơn 30 tỷ vào năm 2025](../../../../../images/connected-iot-devices.svg)

✅ Nghiên cứu một chút: Bao nhiêu phần trăm dữ liệu được tạo ra bởi các thiết bị IoT thực sự được sử dụng, và bao nhiêu bị lãng phí? Tại sao lại có nhiều dữ liệu bị bỏ qua như vậy?

Dữ liệu này là chìa khóa cho sự thành công của IoT. Để trở thành một nhà phát triển IoT thành công, bạn cần hiểu dữ liệu cần thu thập, cách thu thập, cách đưa ra quyết định dựa trên dữ liệu đó, và cách sử dụng các quyết định này để tương tác với thế giới thực nếu cần.

## Thiết bị IoT

Chữ **T** trong IoT đại diện cho **Things** - các thiết bị tương tác với thế giới thực xung quanh chúng, hoặc bằng cách thu thập dữ liệu từ cảm biến, hoặc cung cấp các tương tác thực tế thông qua bộ truyền động.

Các thiết bị dành cho sản xuất hoặc sử dụng thương mại, chẳng hạn như thiết bị theo dõi sức khỏe cá nhân hoặc bộ điều khiển máy móc công nghiệp, thường được thiết kế riêng. Chúng sử dụng các bảng mạch tùy chỉnh, thậm chí có thể là bộ xử lý tùy chỉnh, được thiết kế để đáp ứng nhu cầu của một nhiệm vụ cụ thể, dù đó là nhỏ gọn để đeo trên cổ tay, hay bền bỉ để hoạt động trong môi trường nhiệt độ cao, áp lực cao hoặc rung động mạnh.

Là một nhà phát triển đang học về IoT hoặc tạo nguyên mẫu thiết bị, bạn sẽ cần bắt đầu với một bộ công cụ phát triển. Đây là các thiết bị IoT đa năng được thiết kế cho các nhà phát triển sử dụng, thường có các tính năng mà bạn sẽ không tìm thấy trên thiết bị sản xuất, chẳng hạn như các chân cắm bên ngoài để kết nối cảm biến hoặc bộ truyền động, phần cứng hỗ trợ gỡ lỗi, hoặc các tài nguyên bổ sung làm tăng chi phí không cần thiết khi sản xuất hàng loạt.

Các bộ công cụ phát triển này thường thuộc hai loại - vi điều khiển và máy tính bảng đơn. Chúng sẽ được giới thiệu ở đây, và chúng ta sẽ đi sâu hơn trong bài học tiếp theo.

> 💁 Điện thoại của bạn cũng có thể được coi là một thiết bị IoT đa năng, với các cảm biến và bộ truyền động tích hợp, với các ứng dụng khác nhau sử dụng các cảm biến và bộ truyền động theo những cách khác nhau với các dịch vụ đám mây khác nhau. Bạn thậm chí có thể tìm thấy một số hướng dẫn IoT sử dụng ứng dụng điện thoại như một thiết bị IoT.

### Vi điều khiển

Vi điều khiển (còn được gọi là MCU, viết tắt của microcontroller unit) là một máy tính nhỏ bao gồm:

🧠 Một hoặc nhiều bộ xử lý trung tâm (CPU) - 'bộ não' của vi điều khiển chạy chương trình của bạn

💾 Bộ nhớ (RAM và bộ nhớ chương trình) - nơi lưu trữ chương trình, dữ liệu và biến của bạn

🔌 Các kết nối đầu vào/đầu ra (I/O) có thể lập trình - để giao tiếp với các thiết bị ngoại vi bên ngoài (các thiết bị được kết nối) như cảm biến và bộ truyền động

Vi điều khiển thường là các thiết bị tính toán chi phí thấp, với giá trung bình cho các thiết bị được sử dụng trong phần cứng tùy chỉnh giảm xuống khoảng 0,50 USD, và một số thiết bị có giá chỉ 0,03 USD. Các bộ công cụ phát triển có thể bắt đầu từ 4 USD, với chi phí tăng lên khi bạn thêm nhiều tính năng hơn. [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html), một bộ công cụ phát triển vi điều khiển từ [Seeed studios](https://www.seeedstudio.com) có cảm biến, bộ truyền động, WiFi và màn hình, có giá khoảng 30 USD.

![Wio Terminal](../../../../../translated_images/vi/wio-terminal.b8299ee16587db9a.webp)

> 💁 Khi tìm kiếm vi điều khiển trên Internet, hãy cẩn thận khi tìm kiếm thuật ngữ **MCU** vì điều này có thể trả về rất nhiều kết quả liên quan đến Vũ trụ Điện ảnh Marvel, không phải vi điều khiển.

Vi điều khiển được thiết kế để lập trình thực hiện một số nhiệm vụ rất cụ thể, thay vì là máy tính đa năng như PC hoặc Mac. Ngoại trừ một số trường hợp rất cụ thể, bạn không thể kết nối màn hình, bàn phím và chuột để sử dụng chúng cho các nhiệm vụ đa năng.

Các bộ công cụ phát triển vi điều khiển thường đi kèm với các cảm biến và bộ truyền động bổ sung trên bo mạch. Hầu hết các bảng sẽ có một hoặc nhiều đèn LED mà bạn có thể lập trình, cùng với các thiết bị khác như các cổng tiêu chuẩn để thêm cảm biến hoặc bộ truyền động từ các hệ sinh thái của các nhà sản xuất khác nhau hoặc các cảm biến tích hợp (thường là các cảm biến phổ biến nhất như cảm biến nhiệt độ). Một số vi điều khiển có kết nối không dây tích hợp như Bluetooth hoặc WiFi hoặc có thêm vi điều khiển trên bảng để thêm kết nối này.

> 💁 Vi điều khiển thường được lập trình bằng C/C++.

### Máy tính bảng đơn

Máy tính bảng đơn là một thiết bị tính toán nhỏ có tất cả các thành phần của một máy tính hoàn chỉnh được tích hợp trên một bảng nhỏ. Đây là các thiết bị có thông số kỹ thuật gần giống với máy tính để bàn hoặc laptop, chạy một hệ điều hành đầy đủ, nhưng nhỏ gọn hơn, tiêu thụ ít năng lượng hơn và rẻ hơn đáng kể.

![Raspberry Pi 4](../../../../../translated_images/vi/raspberry-pi-4.fd4590d308c3d456.webp)

Raspberry Pi là một trong những máy tính bảng đơn phổ biến nhất.

Giống như vi điều khiển, máy tính bảng đơn có CPU, bộ nhớ và các chân đầu vào/đầu ra, nhưng chúng có thêm các tính năng như chip đồ họa để kết nối màn hình, đầu ra âm thanh, và các cổng USB để kết nối bàn phím, chuột và các thiết bị USB tiêu chuẩn khác như webcam hoặc bộ nhớ ngoài. Chương trình được lưu trữ trên thẻ SD hoặc ổ cứng cùng với hệ điều hành, thay vì một chip bộ nhớ tích hợp trên bảng.

> 🎓 Bạn có thể nghĩ máy tính bảng đơn như một phiên bản nhỏ hơn, rẻ hơn của PC hoặc Mac mà bạn đang sử dụng, với bổ sung các chân GPIO (đầu vào/đầu ra đa năng) để tương tác với cảm biến và bộ truyền động.

Máy tính bảng đơn là các máy tính đầy đủ tính năng, vì vậy có thể được lập trình bằng bất kỳ ngôn ngữ nào. Các thiết bị IoT thường được lập trình bằng Python.

### Lựa chọn phần cứng cho các bài học tiếp theo

Tất cả các bài học tiếp theo bao gồm các bài tập sử dụng thiết bị IoT để tương tác với thế giới thực và giao tiếp với đám mây. Mỗi bài học hỗ trợ 3 lựa chọn thiết bị - Arduino (sử dụng Seeed Studios Wio Terminal), hoặc một máy tính bảng đơn, có thể là thiết bị vật lý (Raspberry Pi 4) hoặc một máy tính bảng đơn ảo chạy trên PC hoặc Mac của bạn.

Bạn có thể đọc về phần cứng cần thiết để hoàn thành tất cả các bài tập trong [hướng dẫn phần cứng](../../../hardware.md).

> 💁 Bạn không cần mua bất kỳ phần cứng IoT nào để hoàn thành các bài tập, bạn có thể làm mọi thứ bằng một máy tính bảng đơn ảo.

Lựa chọn phần cứng phụ thuộc vào những gì bạn có sẵn tại nhà hoặc trường học, và ngôn ngữ lập trình bạn biết hoặc dự định học. Cả hai loại phần cứng sẽ sử dụng cùng một hệ sinh thái cảm biến, vì vậy nếu bạn bắt đầu với một lựa chọn, bạn có thể chuyển sang lựa chọn khác mà không cần thay thế hầu hết bộ công cụ. Máy tính bảng đơn ảo sẽ tương đương với việc học trên Raspberry Pi, với hầu hết mã có thể chuyển sang Pi nếu bạn cuối cùng có thiết bị và cảm biến.

### Bộ công cụ phát triển Arduino

Nếu bạn quan tâm đến việc học phát triển vi điều khiển, bạn có thể hoàn thành các bài tập bằng thiết bị Arduino. Bạn sẽ cần hiểu cơ bản về lập trình C/C++, vì các bài học chỉ dạy mã liên quan đến framework Arduino, các cảm biến và bộ truyền động được sử dụng, và các thư viện tương tác với đám mây.

Các bài tập sẽ sử dụng [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn) với [tiện ích mở rộng PlatformIO cho phát triển vi điều khiển](https://platformio.org). Bạn cũng có thể sử dụng Arduino IDE nếu bạn đã quen với công cụ này, vì hướng dẫn sẽ không được cung cấp.

### Bộ công cụ phát triển máy tính bảng đơn

Nếu bạn quan tâm đến việc học phát triển IoT sử dụng máy tính bảng đơn, bạn có thể hoàn thành các bài tập bằng Raspberry Pi hoặc một thiết bị ảo chạy trên PC hoặc Mac của bạn.

Bạn sẽ cần hiểu cơ bản về lập trình Python, vì các bài học chỉ dạy mã liên quan đến các cảm biến và bộ truyền động được sử dụng, và các thư viện tương tác với đám mây.

> 💁 Nếu bạn muốn học lập trình Python, hãy xem hai chuỗi video sau:
>
> * [Python cho người mới bắt đầu](https://channel9.msdn.com/Series/Intro-to-Python-Development?WT.mc_id=academic-17441-jabenn)
> * [Python nâng cao cho người mới bắt đầu](https://channel9.msdn.com/Series/More-Python-for-Beginners?WT.mc_id=academic-7372-jabenn)

Các bài tập sẽ sử dụng [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn).

Nếu bạn sử dụng Raspberry Pi, bạn có thể chạy Pi bằng phiên bản đầy đủ của Raspberry Pi OS và thực hiện tất cả mã hóa trực tiếp trên Pi sử dụng [phiên bản VS Code dành cho Raspberry Pi OS](https://code.visualstudio.com/docs/setup/raspberry-pi?WT.mc_id=academic-17441-jabenn), hoặc chạy Pi như một thiết bị không màn hình và mã hóa từ PC hoặc Mac của bạn sử dụng VS Code với [tiện ích mở rộng Remote SSH](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) cho phép bạn kết nối với Pi và chỉnh sửa, gỡ lỗi và chạy mã như thể bạn đang mã hóa trực tiếp trên đó.

Nếu bạn sử dụng tùy chọn thiết bị ảo, bạn sẽ mã hóa trực tiếp trên máy tính của mình. Thay vì truy cập cảm biến và bộ truyền động, bạn sẽ sử dụng một công cụ để mô phỏng phần cứng này, cung cấp các giá trị cảm biến mà bạn có thể định nghĩa và hiển thị kết quả của bộ truyền động trên màn hình.

## Thiết lập thiết bị của bạn

Trước khi bạn có thể bắt đầu lập trình thiết bị IoT của mình, bạn sẽ cần thực hiện một số bước thiết lập nhỏ. Hãy làm theo các hướng dẫn phù hợp dưới đây tùy thuộc vào thiết bị bạn sẽ sử dụng.
💁 Nếu bạn chưa có thiết bị, hãy tham khảo [hướng dẫn phần cứng](../../../hardware.md) để giúp bạn quyết định thiết bị nào sẽ được sử dụng và phần cứng bổ sung nào cần mua. Bạn không cần phải mua phần cứng, vì tất cả các dự án đều có thể chạy trên phần cứng ảo.
Các hướng dẫn này bao gồm các liên kết đến các trang web của bên thứ ba từ các nhà sản xuất phần cứng hoặc công cụ mà bạn sẽ sử dụng. Điều này nhằm đảm bảo bạn luôn sử dụng các hướng dẫn mới nhất cho các công cụ và phần cứng khác nhau.

Hãy làm theo hướng dẫn phù hợp để thiết lập thiết bị của bạn và hoàn thành dự án 'Hello World'. Đây sẽ là bước đầu tiên trong việc tạo ra một đèn ngủ IoT qua 4 bài học trong phần bắt đầu này.

* [Arduino - Wio Terminal](wio-terminal.md)
* [Máy tính đơn bảng - Raspberry Pi](pi.md)
* [Máy tính đơn bảng - Thiết bị ảo](virtual-device.md)

✅ Bạn sẽ sử dụng VS Code cho cả Arduino và máy tính đơn bảng. Nếu bạn chưa từng sử dụng trước đây, hãy đọc thêm về nó trên [trang web VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn)

## Ứng dụng của IoT

IoT bao gồm một loạt các trường hợp sử dụng, thuộc một số nhóm lớn:

* IoT tiêu dùng
* IoT thương mại
* IoT công nghiệp
* IoT hạ tầng

✅ Nghiên cứu một chút: Đối với mỗi lĩnh vực được mô tả dưới đây, hãy tìm một ví dụ cụ thể không được đề cập trong văn bản.

### IoT tiêu dùng

IoT tiêu dùng đề cập đến các thiết bị IoT mà người tiêu dùng sẽ mua và sử dụng trong gia đình. Một số thiết bị này rất hữu ích, chẳng hạn như loa thông minh, hệ thống sưởi thông minh và máy hút bụi robot. Những thiết bị khác lại gây tranh cãi về tính hữu dụng, chẳng hạn như vòi nước điều khiển bằng giọng nói khiến bạn không thể tắt nước vì điều khiển giọng nói không nghe được tiếng bạn nói qua âm thanh của nước chảy.

Các thiết bị IoT tiêu dùng đang giúp mọi người đạt được nhiều hơn trong môi trường xung quanh của họ, đặc biệt là 1 tỷ người có khuyết tật. Máy hút bụi robot có thể giúp làm sạch sàn nhà cho những người gặp khó khăn về vận động không thể tự hút bụi, lò nướng điều khiển bằng giọng nói cho phép người có thị lực hoặc khả năng vận động hạn chế làm nóng lò chỉ bằng giọng nói, các thiết bị theo dõi sức khỏe cho phép bệnh nhân tự theo dõi các bệnh mãn tính với các cập nhật thường xuyên và chi tiết hơn về tình trạng của họ. Những thiết bị này đang trở nên phổ biến đến mức ngay cả trẻ nhỏ cũng sử dụng chúng như một phần của cuộc sống hàng ngày, ví dụ như học sinh học trực tuyến trong đại dịch COVID đặt hẹn giờ trên các thiết bị nhà thông minh để theo dõi bài tập hoặc đặt báo thức nhắc nhở về các buổi học sắp tới.

✅ Bạn có những thiết bị IoT tiêu dùng nào trong người hoặc trong nhà?

### IoT thương mại

IoT thương mại bao gồm việc sử dụng IoT trong môi trường làm việc. Trong văn phòng, có thể có các cảm biến chiếm dụng và cảm biến chuyển động để quản lý ánh sáng và sưởi ấm, chỉ bật khi cần thiết, giảm chi phí và khí thải carbon. Trong nhà máy, các thiết bị IoT có thể giám sát các nguy cơ an toàn như công nhân không đội mũ bảo hộ hoặc tiếng ồn đạt mức nguy hiểm. Trong bán lẻ, các thiết bị IoT có thể đo nhiệt độ của kho lạnh, cảnh báo chủ cửa hàng nếu tủ lạnh hoặc tủ đông vượt quá phạm vi nhiệt độ yêu cầu, hoặc chúng có thể giám sát các mặt hàng trên kệ để hướng dẫn nhân viên bổ sung sản phẩm đã bán. Ngành vận tải ngày càng dựa vào IoT để giám sát vị trí phương tiện, theo dõi số km trên đường để tính phí sử dụng đường, theo dõi giờ làm việc và tuân thủ giờ nghỉ của tài xế, hoặc thông báo cho nhân viên khi một phương tiện đang đến gần kho để chuẩn bị bốc dỡ hàng.

✅ Bạn có những thiết bị IoT thương mại nào trong trường học hoặc nơi làm việc?

### IoT công nghiệp (IIoT)

IoT công nghiệp, hay IIoT, là việc sử dụng các thiết bị IoT để kiểm soát và quản lý máy móc trên quy mô lớn. Điều này bao gồm nhiều trường hợp sử dụng, từ nhà máy đến nông nghiệp kỹ thuật số.

Các nhà máy sử dụng thiết bị IoT theo nhiều cách khác nhau. Máy móc có thể được giám sát bằng nhiều cảm biến để theo dõi các thông số như nhiệt độ, độ rung và tốc độ quay. Dữ liệu này sau đó có thể được giám sát để cho phép máy móc dừng hoạt động nếu vượt quá các giới hạn nhất định - ví dụ, máy chạy quá nóng và bị tắt. Dữ liệu này cũng có thể được thu thập và phân tích theo thời gian để thực hiện bảo trì dự đoán, nơi các mô hình AI sẽ xem xét dữ liệu dẫn đến sự cố và sử dụng nó để dự đoán các sự cố khác trước khi chúng xảy ra.

Nông nghiệp kỹ thuật số rất quan trọng để nuôi sống dân số ngày càng tăng, đặc biệt là 2 tỷ người trong 500 triệu hộ gia đình sống dựa vào [nông nghiệp tự cung tự cấp](https://wikipedia.org/wiki/Subsistence_agriculture). Nông nghiệp kỹ thuật số có thể dao động từ các cảm biến giá vài đô la đến các hệ thống thương mại lớn. Một nông dân có thể bắt đầu bằng cách giám sát nhiệt độ và sử dụng [ngày độ tăng trưởng](https://wikipedia.org/wiki/Growing_degree-day) để dự đoán khi nào cây trồng sẽ sẵn sàng thu hoạch. Họ có thể kết nối giám sát độ ẩm đất với hệ thống tưới nước tự động để cung cấp cho cây trồng lượng nước cần thiết, nhưng không nhiều hơn để đảm bảo cây không bị khô mà không lãng phí nước. Nông dân thậm chí còn tiến xa hơn bằng cách sử dụng máy bay không người lái, dữ liệu vệ tinh và AI để giám sát sự phát triển của cây trồng, bệnh dịch và chất lượng đất trên diện tích lớn.

✅ Những thiết bị IoT nào khác có thể giúp nông dân?

### IoT hạ tầng

IoT hạ tầng là việc giám sát và kiểm soát cơ sở hạ tầng địa phương và toàn cầu mà mọi người sử dụng hàng ngày.

[Thành phố thông minh](https://wikipedia.org/wiki/Smart_city) là các khu vực đô thị sử dụng thiết bị IoT để thu thập dữ liệu về thành phố và sử dụng dữ liệu đó để cải thiện cách thành phố hoạt động. Những thành phố này thường được quản lý với sự hợp tác giữa chính quyền địa phương, học viện và doanh nghiệp địa phương, theo dõi và quản lý các vấn đề từ giao thông đến bãi đỗ xe và ô nhiễm. Ví dụ, ở Copenhagen, Đan Mạch, ô nhiễm không khí là vấn đề quan trọng đối với cư dân địa phương, vì vậy nó được đo lường và dữ liệu được sử dụng để cung cấp thông tin về các tuyến đường chạy bộ và đạp xe sạch nhất.

[Lưới điện thông minh](https://wikipedia.org/wiki/Smart_grid) cho phép phân tích tốt hơn về nhu cầu điện bằng cách thu thập dữ liệu sử dụng ở cấp độ từng hộ gia đình. Dữ liệu này có thể hướng dẫn các quyết định ở cấp quốc gia, bao gồm nơi xây dựng các nhà máy điện mới, và ở cấp cá nhân bằng cách cung cấp cho người dùng thông tin chi tiết về lượng điện họ sử dụng, thời điểm họ sử dụng và thậm chí các gợi ý về cách giảm chi phí, chẳng hạn như sạc xe điện vào ban đêm.

✅ Nếu bạn có thể thêm các thiết bị IoT để đo lường bất cứ điều gì nơi bạn sống, bạn sẽ chọn gì?

## Ví dụ về các thiết bị IoT bạn có thể có xung quanh mình

Bạn sẽ ngạc nhiên bởi số lượng thiết bị IoT mà bạn có xung quanh mình. Tôi đang viết điều này từ nhà và tôi có các thiết bị sau được kết nối Internet với các tính năng thông minh như điều khiển qua ứng dụng, điều khiển bằng giọng nói hoặc khả năng gửi dữ liệu đến tôi qua điện thoại:

* Nhiều loa thông minh
* Tủ lạnh, máy rửa chén, lò nướng và lò vi sóng
* Thiết bị giám sát điện cho các tấm pin mặt trời
* Ổ cắm thông minh
* Chuông cửa video và camera an ninh
* Bộ điều chỉnh nhiệt thông minh với nhiều cảm biến phòng thông minh
* Thiết bị mở cửa garage
* Hệ thống giải trí gia đình và TV điều khiển bằng giọng nói
* Đèn
* Thiết bị theo dõi sức khỏe và thể chất

Tất cả các loại thiết bị này đều có cảm biến và/hoặc bộ truyền động và kết nối với Internet. Tôi có thể biết từ điện thoại của mình nếu cửa garage đang mở, và yêu cầu loa thông minh đóng nó lại cho tôi. Tôi thậm chí có thể đặt hẹn giờ để nếu cửa vẫn mở vào ban đêm, nó sẽ tự động đóng lại. Khi chuông cửa reo, tôi có thể xem từ điện thoại của mình ai đang ở đó dù tôi ở bất cứ đâu trên thế giới, và nói chuyện với họ qua loa và micro tích hợp trong chuông cửa. Tôi có thể theo dõi đường huyết, nhịp tim và mô hình giấc ngủ của mình, tìm kiếm các xu hướng trong dữ liệu để cải thiện sức khỏe. Tôi có thể điều khiển đèn qua đám mây, và ngồi trong bóng tối khi kết nối Internet bị mất.

---

## 🚀 Thử thách

Liệt kê càng nhiều thiết bị IoT càng tốt mà bạn có trong nhà, trường học hoặc nơi làm việc - có thể nhiều hơn bạn nghĩ!

## Câu hỏi sau bài giảng

[Câu hỏi sau bài giảng](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/2)

## Ôn tập & Tự học

Tìm hiểu về lợi ích và thất bại của các dự án IoT tiêu dùng. Kiểm tra các trang tin tức để tìm các bài viết về những trường hợp thất bại, chẳng hạn như vấn đề về quyền riêng tư, vấn đề phần cứng hoặc vấn đề do thiếu kết nối.

Một số ví dụ:

* Xem tài khoản Twitter **[Internet of Sh*t](https://twitter.com/internetofshit)** *(cảnh báo ngôn từ thô tục)* để tìm một số ví dụ hay về thất bại của IoT tiêu dùng.
* [c|net - Đồng hồ Apple của tôi đã cứu mạng tôi: 5 người chia sẻ câu chuyện của họ](https://www.cnet.com/news/apple-watch-lifesaving-health-features-read-5-peoples-stories/)
* [c|net - Kỹ thuật viên ADT nhận tội theo dõi camera khách hàng trong nhiều năm](https://www.cnet.com/news/adt-home-security-technician-pleads-guilty-to-spying-on-customer-camera-feeds-for-years/) *(cảnh báo nội dung - hành vi theo dõi không được đồng ý)*

## Bài tập

[Điều tra một dự án IoT](assignment.md)

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm về bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.