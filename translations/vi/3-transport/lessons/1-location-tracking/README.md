# Theo dõi vị trí

![Tóm tắt bài học bằng hình vẽ](../../../../../translated_images/vi/lesson-11.9fddbac4b664c6d5.webp)

> Hình vẽ minh họa bởi [Nitya Narasimhan](https://github.com/nitya). Nhấp vào hình để xem phiên bản lớn hơn.

## Câu hỏi trước bài giảng

[Câu hỏi trước bài giảng](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/21)

## Giới thiệu

Quá trình chính để đưa thực phẩm từ nông dân đến người tiêu dùng bao gồm việc chất các thùng sản phẩm lên xe tải, tàu, máy bay hoặc các phương tiện vận chuyển thương mại khác, và giao thực phẩm đến một nơi nào đó - hoặc trực tiếp đến khách hàng, hoặc đến một trung tâm hoặc kho để xử lý. Toàn bộ quy trình từ đầu đến cuối từ nông trại đến người tiêu dùng là một phần của quy trình gọi là *chuỗi cung ứng*. Video dưới đây từ Trường Kinh doanh W. P. Carey của Đại học Bang Arizona nói về khái niệm chuỗi cung ứng và cách quản lý nó chi tiết hơn.

[![Quản lý chuỗi cung ứng là gì? Video từ Trường Kinh doanh W. P. Carey của Đại học Bang Arizona](https://img.youtube.com/vi/Mi1QBxVjZAw/0.jpg)](https://www.youtube.com/watch?v=Mi1QBxVjZAw)

> 🎥 Nhấp vào hình trên để xem video

Việc thêm các thiết bị IoT có thể cải thiện đáng kể chuỗi cung ứng của bạn, cho phép bạn quản lý vị trí của các mặt hàng, lập kế hoạch vận chuyển và xử lý hàng hóa tốt hơn, và phản ứng nhanh hơn với các vấn đề.

Khi quản lý một đội xe như xe tải, việc biết vị trí của từng xe tại một thời điểm nhất định là rất hữu ích. Các xe có thể được trang bị cảm biến GPS gửi vị trí của chúng đến các hệ thống IoT, cho phép chủ sở hữu xác định vị trí, xem tuyến đường đã đi, và biết khi nào xe sẽ đến đích. Hầu hết các xe hoạt động ngoài vùng phủ sóng WiFi, vì vậy chúng sử dụng mạng di động để gửi loại dữ liệu này. Đôi khi cảm biến GPS được tích hợp vào các thiết bị IoT phức tạp hơn như sổ nhật ký điện tử. Những thiết bị này theo dõi thời gian xe tải đã di chuyển để đảm bảo tài xế tuân thủ luật pháp địa phương về giờ làm việc.

Trong bài học này, bạn sẽ học cách theo dõi vị trí của xe bằng cảm biến Hệ thống Định vị Toàn cầu (GPS).

Trong bài học này, chúng ta sẽ tìm hiểu:

* [Xe kết nối](../../../../../3-transport/lessons/1-location-tracking)
* [Tọa độ địa lý](../../../../../3-transport/lessons/1-location-tracking)
* [Hệ thống Định vị Toàn cầu (GPS)](../../../../../3-transport/lessons/1-location-tracking)
* [Đọc dữ liệu cảm biến GPS](../../../../../3-transport/lessons/1-location-tracking)
* [Dữ liệu GPS NMEA](../../../../../3-transport/lessons/1-location-tracking)
* [Giải mã dữ liệu cảm biến GPS](../../../../../3-transport/lessons/1-location-tracking)

## Xe kết nối

IoT đang thay đổi cách vận chuyển hàng hóa bằng cách tạo ra các đội xe *kết nối*. Những xe này được kết nối với các hệ thống CNTT trung tâm, báo cáo thông tin về vị trí và dữ liệu cảm biến khác. Việc có một đội xe kết nối mang lại nhiều lợi ích:

* Theo dõi vị trí - bạn có thể xác định vị trí của một xe tại bất kỳ thời điểm nào, cho phép bạn:

  * Nhận thông báo khi xe sắp đến đích để chuẩn bị đội ngũ dỡ hàng
  * Xác định vị trí xe bị đánh cắp
  * Kết hợp dữ liệu vị trí và tuyến đường với các vấn đề giao thông để cho phép bạn thay đổi tuyến đường xe giữa hành trình
  * Tuân thủ thuế. Một số quốc gia tính phí xe dựa trên số km đã đi trên đường công cộng (chẳng hạn như [RUC của New Zealand](https://www.nzta.govt.nz/vehicles/licensing-rego/road-user-charges/)), vì vậy việc biết khi nào xe đang ở trên đường công cộng so với đường tư nhân giúp dễ dàng tính toán thuế phải trả.
  * Biết nơi gửi đội bảo trì trong trường hợp xe bị hỏng

* Dữ liệu lái xe - đảm bảo tài xế tuân thủ giới hạn tốc độ, vào cua ở tốc độ phù hợp, phanh sớm và hiệu quả, và lái xe an toàn. Xe kết nối cũng có thể có camera để ghi lại các sự cố. Điều này có thể liên kết với bảo hiểm, mang lại mức phí giảm cho tài xế tốt.

* Tuân thủ giờ lái xe - đảm bảo tài xế chỉ lái xe trong giờ làm việc hợp pháp dựa trên thời gian bật và tắt động cơ.

Những lợi ích này có thể được kết hợp - ví dụ, kết hợp tuân thủ giờ lái xe với theo dõi vị trí để thay đổi tuyến đường của tài xế nếu họ không thể đến đích trong giờ lái xe cho phép. Những lợi ích này cũng có thể được kết hợp với các dữ liệu cảm biến cụ thể của xe, chẳng hạn như dữ liệu nhiệt độ từ xe tải kiểm soát nhiệt độ, cho phép xe được thay đổi tuyến đường nếu tuyến đường hiện tại khiến hàng hóa không thể được giữ ở nhiệt độ yêu cầu.

> 🎓 Logistics là quá trình vận chuyển hàng hóa từ nơi này đến nơi khác, chẳng hạn từ nông trại đến siêu thị thông qua một hoặc nhiều kho. Một nông dân đóng gói các thùng cà chua được chất lên xe tải, giao đến một kho trung tâm, và được chuyển lên một xe tải thứ hai có thể chứa hỗn hợp các loại sản phẩm khác nhau, sau đó được giao đến siêu thị.

Thành phần cốt lõi của việc theo dõi xe là GPS - cảm biến có thể xác định vị trí của chúng ở bất kỳ đâu trên Trái Đất. Trong bài học này, bạn sẽ học cách sử dụng cảm biến GPS, bắt đầu với việc tìm hiểu cách xác định vị trí trên Trái Đất.

## Tọa độ địa lý

Tọa độ địa lý được sử dụng để xác định các điểm trên bề mặt Trái Đất, tương tự như cách tọa độ được sử dụng để vẽ một pixel trên màn hình máy tính hoặc định vị các mũi khâu trong thêu chữ thập. Đối với một điểm duy nhất, bạn có một cặp tọa độ. Ví dụ, Khuôn viên Microsoft ở Redmond, Washington, Mỹ nằm tại 47.6423109, -122.1390293.

### Vĩ độ và kinh độ

Trái Đất là một hình cầu - một vòng tròn ba chiều. Vì vậy, các điểm được xác định bằng cách chia nó thành 360 độ, giống như hình học của các vòng tròn. Vĩ độ đo số độ từ bắc xuống nam, kinh độ đo số độ từ đông sang tây.

> 💁 Không ai thực sự biết lý do ban đầu tại sao các vòng tròn được chia thành 360 độ. Trang [độ (góc) trên Wikipedia](https://wikipedia.org/wiki/Degree_(angle)) đề cập đến một số lý do có thể.

![Các đường vĩ độ từ 90° tại Bắc Cực, 45° giữa Bắc Cực và xích đạo, 0° tại xích đạo, -45° giữa xích đạo và Nam Cực, và -90° tại Nam Cực](../../../../../translated_images/vi/latitude-lines.11d8d91dfb2014a5.webp)

Vĩ độ được đo bằng các đường vòng quanh Trái Đất và chạy song song với xích đạo, chia Bắc Bán Cầu và Nam Bán Cầu thành mỗi bên 90°. Xích đạo ở 0°, Bắc Cực ở 90°, còn gọi là 90° Bắc, và Nam Cực ở -90°, hoặc 90° Nam.

Kinh độ được đo bằng số độ từ đông sang tây. Điểm gốc 0° của kinh độ được gọi là *Kinh tuyến gốc*, và được xác định vào năm 1884 là một đường từ Bắc Cực đến Nam Cực đi qua [Đài Thiên văn Hoàng gia Anh ở Greenwich, Anh](https://wikipedia.org/wiki/Royal_Observatory,_Greenwich).

![Các đường kinh độ từ -180° về phía tây của Kinh tuyến gốc, đến 0° trên Kinh tuyến gốc, đến 180° về phía đông của Kinh tuyến gốc](../../../../../translated_images/vi/longitude-meridians.ab4ef1c91c064586.webp)

> 🎓 Kinh tuyến là một đường thẳng tưởng tượng đi từ Bắc Cực đến Nam Cực, tạo thành một nửa vòng tròn.

Để đo kinh độ của một điểm, bạn đo số độ vòng quanh xích đạo từ Kinh tuyến gốc đến một kinh tuyến đi qua điểm đó. Kinh độ đi từ -180°, hoặc 180° Tây, qua 0° tại Kinh tuyến gốc, đến 180°, hoặc 180° Đông. 180° và -180° chỉ cùng một điểm, gọi là kinh tuyến đối diện hoặc kinh tuyến 180. Đây là một kinh tuyến ở phía đối diện của Trái Đất so với Kinh tuyến gốc.

> 💁 Kinh tuyến đối diện không nên nhầm lẫn với Đường đổi ngày quốc tế, nằm ở vị trí gần như tương tự, nhưng không phải là một đường thẳng và thay đổi để phù hợp với các ranh giới địa chính trị.

✅ Tìm hiểu thêm: Hãy thử tìm vĩ độ và kinh độ của vị trí hiện tại của bạn.

### Độ, phút và giây so với độ thập phân

Truyền thống, các phép đo độ vĩ độ và kinh độ được thực hiện bằng cách sử dụng hệ thống số sexagesimal, hoặc cơ số-60, một hệ thống số được sử dụng bởi người Babylon cổ đại, những người đầu tiên đo lường và ghi lại thời gian và khoảng cách. Bạn sử dụng sexagesimal hàng ngày mà có thể không nhận ra - chia giờ thành 60 phút và phút thành 60 giây.

Kinh độ và vĩ độ được đo bằng độ, phút và giây, với một phút là 1/60 của một độ, và 1 giây là 1/60 phút.

Ví dụ, tại xích đạo:

* 1° vĩ độ là **111.3 km**
* 1 phút vĩ độ là 111.3/60 = **1.855 km**
* 1 giây vĩ độ là 1.855/60 = **0.031 km**

Ký hiệu cho phút là dấu nháy đơn, cho giây là dấu nháy kép. Ví dụ, 2 độ, 17 phút, và 43 giây sẽ được viết là 2°17'43". Phần của giây được viết dưới dạng số thập phân, ví dụ nửa giây là 0°0'0.5".

Máy tính không hoạt động theo cơ số-60, vì vậy các tọa độ này được đưa ra dưới dạng độ thập phân khi sử dụng dữ liệu GPS trong hầu hết các hệ thống máy tính. Ví dụ, 2°17'43" là 2.295277. Ký hiệu độ thường bị bỏ qua.

Tọa độ của một điểm luôn được đưa ra dưới dạng `vĩ độ, kinh độ`, vì vậy ví dụ trước đó về Khuôn viên Microsoft tại 47.6423109,-122.117198 có:

* Vĩ độ là 47.6423109 (47.6423109 độ về phía bắc của xích đạo)
* Kinh độ là -122.1390293 (122.1390293 độ về phía tây của Kinh tuyến gốc).

![Khuôn viên Microsoft tại 47.6423109,-122.117198](../../../../../translated_images/vi/microsoft-gps-location-world.a321d481b010f6ad.webp)

## Hệ thống Định vị Toàn cầu (GPS)

Hệ thống GPS sử dụng nhiều vệ tinh quay quanh Trái Đất để xác định vị trí của bạn. Bạn có thể đã sử dụng hệ thống GPS mà không nhận ra - để tìm vị trí của bạn trên ứng dụng bản đồ trên điện thoại như Apple Maps hoặc Google Maps, hoặc để xem xe của bạn đang ở đâu trong ứng dụng gọi xe như Uber hoặc Lyft, hoặc khi sử dụng hệ thống dẫn đường vệ tinh (sat-nav) trong xe hơi.

> 🎓 Các vệ tinh trong 'dẫn đường vệ tinh' chính là các vệ tinh GPS!

Hệ thống GPS hoạt động bằng cách có một số vệ tinh gửi tín hiệu với vị trí hiện tại của từng vệ tinh và một dấu thời gian chính xác. Những tín hiệu này được gửi qua sóng radio và được phát hiện bởi một ăng-ten trong cảm biến GPS. Một cảm biến GPS sẽ phát hiện những tín hiệu này, và sử dụng thời gian hiện tại để đo thời gian tín hiệu mất để đến cảm biến từ vệ tinh. Vì tốc độ của sóng radio là không đổi, cảm biến GPS có thể sử dụng dấu thời gian được gửi để tính toán khoảng cách từ cảm biến đến vệ tinh. Bằng cách kết hợp dữ liệu từ ít nhất 3 vệ tinh với các vị trí được gửi, cảm biến GPS có thể xác định vị trí của nó trên Trái Đất.

> 💁 Cảm biến GPS cần ăng-ten để phát hiện sóng radio. Các ăng-ten được tích hợp trong xe tải và xe hơi có GPS trên xe được đặt để nhận tín hiệu tốt, thường là trên kính chắn gió hoặc mái xe. Nếu bạn đang sử dụng hệ thống GPS riêng biệt, chẳng hạn như điện thoại thông minh hoặc thiết bị IoT, thì bạn cần đảm bảo rằng ăng-ten tích hợp trong hệ thống GPS hoặc điện thoại có tầm nhìn rõ ràng đến bầu trời, chẳng hạn như được gắn trên kính chắn gió.

![Bằng cách biết khoảng cách từ cảm biến đến nhiều vệ tinh, vị trí có thể được tính toán](../../../../../translated_images/vi/gps-satellites.04acf1148fe25fbf.webp)

Các vệ tinh GPS đang quay quanh Trái Đất, không ở một điểm cố định trên cảm biến, vì vậy dữ liệu vị trí bao gồm độ cao so với mực nước biển cũng như vĩ độ và kinh độ.

GPS từng có giới hạn về độ chính xác do quân đội Mỹ áp đặt, giới hạn độ chính xác khoảng 5 mét. Giới hạn này đã được gỡ bỏ vào năm 2000, cho phép độ chính xác đạt 30 cm. Tuy nhiên, việc đạt được độ chính xác này không phải lúc nào cũng khả thi do nhiễu tín hiệu.

✅ Nếu bạn có điện thoại thông minh, hãy mở ứng dụng bản đồ và xem độ chính xác của vị trí của bạn. Có thể mất một khoảng thời gian ngắn để điện thoại của bạn phát hiện nhiều vệ tinh để có vị trí chính xác hơn.
💁 Các vệ tinh chứa đồng hồ nguyên tử cực kỳ chính xác, nhưng chúng lệch đi 38 micro giây (0.0000038 giây) mỗi ngày so với đồng hồ nguyên tử trên Trái Đất, do thời gian chậm lại khi tốc độ tăng lên như được dự đoán bởi các lý thuyết tương đối đặc biệt và tương đối tổng quát của Einstein - các vệ tinh di chuyển nhanh hơn so với sự quay của Trái Đất. Sự lệch này đã được sử dụng để chứng minh các dự đoán của lý thuyết tương đối đặc biệt và tổng quát, và phải được điều chỉnh trong thiết kế hệ thống GPS. Thực tế, thời gian chạy chậm hơn trên một vệ tinh GPS.
Hệ thống GPS đã được phát triển và triển khai bởi nhiều quốc gia và liên minh chính trị bao gồm Mỹ, Nga, Nhật Bản, Ấn Độ, EU và Trung Quốc. Cảm biến GPS hiện đại có thể kết nối với hầu hết các hệ thống này để có được vị trí nhanh hơn và chính xác hơn.

> 🎓 Các nhóm vệ tinh trong mỗi hệ thống triển khai được gọi là chòm sao vệ tinh.

## Đọc dữ liệu cảm biến GPS

Hầu hết các cảm biến GPS gửi dữ liệu GPS qua UART.

> ⚠️ UART đã được đề cập trong [dự án 2, bài học 2](../../../2-farm/lessons/2-detect-soil-moisture/README.md#universal-asynchronous-receiver-transmitter-uart). Hãy tham khảo lại bài học đó nếu cần.

Bạn có thể sử dụng cảm biến GPS trên thiết bị IoT của mình để lấy dữ liệu GPS.

### Nhiệm vụ - kết nối cảm biến GPS và đọc dữ liệu GPS

Làm theo hướng dẫn liên quan để đọc dữ liệu GPS bằng thiết bị IoT của bạn:

* [Arduino - Wio Terminal](wio-terminal-gps-sensor.md)
* [Máy tính đơn bo - Raspberry Pi](pi-gps-sensor.md)
* [Máy tính đơn bo - Thiết bị ảo](virtual-device-gps-sensor.md)

## Dữ liệu GPS NMEA

Khi bạn chạy mã của mình, bạn có thể đã thấy những gì trông giống như các ký tự lộn xộn trong đầu ra. Thực ra đây là dữ liệu GPS tiêu chuẩn, và tất cả đều có ý nghĩa.

Cảm biến GPS xuất dữ liệu bằng các thông điệp NMEA, sử dụng tiêu chuẩn NMEA 0183. NMEA là viết tắt của [Hiệp hội Điện tử Hàng hải Quốc gia](https://www.nmea.org), một tổ chức thương mại có trụ sở tại Mỹ đặt ra tiêu chuẩn cho việc giao tiếp giữa các thiết bị điện tử hàng hải.

> 💁 Tiêu chuẩn này là độc quyền và có giá ít nhất 2.000 USD, nhưng đủ thông tin về nó đã được công khai để hầu hết tiêu chuẩn này đã được giải mã ngược và có thể được sử dụng trong mã nguồn mở và các mã không thương mại khác.

Các thông điệp này dựa trên văn bản. Mỗi thông điệp bao gồm một *câu* bắt đầu bằng ký tự `$`, tiếp theo là 2 ký tự để chỉ nguồn của thông điệp (ví dụ GP cho hệ thống GPS của Mỹ, GN cho GLONASS, hệ thống GPS của Nga), và 3 ký tự để chỉ loại thông điệp. Phần còn lại của thông điệp là các trường được phân tách bằng dấu phẩy, kết thúc bằng ký tự xuống dòng.

Một số loại thông điệp có thể nhận được là:

| Loại | Mô tả |
| ---- | ----------- |
| GGA | Dữ liệu vị trí GPS, bao gồm vĩ độ, kinh độ và độ cao của cảm biến GPS, cùng với số lượng vệ tinh trong tầm nhìn để tính toán vị trí này. |
| ZDA | Ngày và giờ hiện tại, bao gồm múi giờ địa phương |
| GSV | Chi tiết về các vệ tinh trong tầm nhìn - được định nghĩa là các vệ tinh mà cảm biến GPS có thể phát hiện tín hiệu từ |

> 💁 Dữ liệu GPS bao gồm dấu thời gian, vì vậy thiết bị IoT của bạn có thể lấy thời gian nếu cần từ cảm biến GPS, thay vì dựa vào máy chủ NTP hoặc đồng hồ thời gian thực nội bộ.

Thông điệp GGA bao gồm vị trí hiện tại sử dụng định dạng `(dd)dmm.mmmm`, cùng với một ký tự để chỉ hướng. `d` trong định dạng là độ, `m` là phút, với giây được biểu diễn dưới dạng số thập phân của phút. Ví dụ, 2°17'43" sẽ là 217.716666667 - 2 độ, 17.716666667 phút.

Ký tự chỉ hướng có thể là `N` hoặc `S` cho vĩ độ để chỉ bắc hoặc nam, và `E` hoặc `W` cho kinh độ để chỉ đông hoặc tây. Ví dụ, một vĩ độ 2°17'43" sẽ có ký tự hướng là `N`, -2°17'43" sẽ có ký tự hướng là `S`.

Ví dụ - câu NMEA `$GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67`

* Phần vĩ độ là `4738.538654,N`, chuyển đổi thành 47.6423109 ở dạng độ thập phân. `4738.538654` là 47.6423109, và hướng là `N` (bắc), vì vậy đây là vĩ độ dương.

* Phần kinh độ là `12208.341758,W`, chuyển đổi thành -122.1390293 ở dạng độ thập phân. `12208.341758` là 122.1390293°, và hướng là `W` (tây), vì vậy đây là kinh độ âm.

## Giải mã dữ liệu cảm biến GPS

Thay vì sử dụng dữ liệu NMEA thô, tốt hơn là giải mã nó thành một định dạng hữu ích hơn. Có nhiều thư viện mã nguồn mở mà bạn có thể sử dụng để giúp trích xuất dữ liệu hữu ích từ các thông điệp NMEA thô.

### Nhiệm vụ - giải mã dữ liệu cảm biến GPS

Làm theo hướng dẫn liên quan để giải mã dữ liệu cảm biến GPS bằng thiết bị IoT của bạn:

* [Arduino - Wio Terminal](wio-terminal-gps-decode.md)
* [Máy tính đơn bo - Raspberry Pi/Thiết bị IoT ảo](single-board-computer-gps-decode.md)

---

## 🚀 Thử thách

Tự viết bộ giải mã NMEA của riêng bạn! Thay vì dựa vào các thư viện của bên thứ ba để giải mã các câu NMEA, bạn có thể tự viết bộ giải mã để trích xuất vĩ độ và kinh độ từ các câu NMEA không?

## Câu hỏi sau bài học

[Câu hỏi sau bài học](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/22)

## Ôn tập & Tự học

* Đọc thêm về Tọa độ Địa lý trên [trang hệ tọa độ địa lý trên Wikipedia](https://wikipedia.org/wiki/Geographic_coordinate_system).
* Tìm hiểu về Kinh tuyến Gốc trên các thiên thể khác ngoài Trái Đất trên [trang Kinh tuyến Gốc trên Wikipedia](https://wikipedia.org/wiki/Prime_meridian#Prime_meridian_on_other_planetary_bodies).
* Nghiên cứu các hệ thống GPS khác nhau từ các chính phủ và liên minh chính trị trên thế giới như EU, Nhật Bản, Nga, Ấn Độ và Mỹ.

## Bài tập

[Khám phá dữ liệu GPS khác](assignment.md)

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.