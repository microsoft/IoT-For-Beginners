<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2625af24587465c5547ae33d6cc000a5",
  "translation_date": "2025-08-27T21:06:55+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/README.md",
  "language_code": "vi"
}
-->
# Chạy trình phát hiện trái cây của bạn trên thiết bị biên

![Tóm tắt bài học bằng sketchnote](../../../../../translated_images/vi/lesson-17.bc333c3c35ba8e42cce666cfffa82b915f787f455bd94e006aea2b6f2722421a.jpg)

> Sketchnote bởi [Nitya Narasimhan](https://github.com/nitya). Nhấp vào hình ảnh để xem phiên bản lớn hơn.

Video này cung cấp cái nhìn tổng quan về việc chạy các bộ phân loại hình ảnh trên các thiết bị IoT, chủ đề được đề cập trong bài học này.

[![Custom Vision AI trên Azure IoT Edge](https://img.youtube.com/vi/_K5fqGLO8us/0.jpg)](https://www.youtube.com/watch?v=_K5fqGLO8us)

## Câu hỏi trước bài giảng

[Câu hỏi trước bài giảng](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/33)

## Giới thiệu

Trong bài học trước, bạn đã sử dụng bộ phân loại hình ảnh của mình để phân loại trái cây chín và chưa chín, gửi một hình ảnh được chụp bởi camera trên thiết bị IoT của bạn qua internet đến một dịch vụ đám mây. Những cuộc gọi này mất thời gian, tốn chi phí và tùy thuộc vào loại dữ liệu hình ảnh bạn đang sử dụng, có thể gây ra các vấn đề về quyền riêng tư.

Trong bài học này, bạn sẽ học cách chạy các mô hình học máy (ML) trên thiết bị biên - trên các thiết bị IoT hoạt động trong mạng nội bộ của bạn thay vì trên đám mây. Bạn sẽ tìm hiểu lợi ích và hạn chế của điện toán biên so với điện toán đám mây, cách triển khai mô hình AI của bạn lên thiết bị biên và cách truy cập nó từ thiết bị IoT của bạn.

Trong bài học này, chúng ta sẽ đề cập đến:

* [Điện toán biên](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Azure IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Đăng ký một thiết bị IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Cài đặt một thiết bị IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Xuất mô hình của bạn](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Chuẩn bị container của bạn để triển khai](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Triển khai container của bạn](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Sử dụng thiết bị IoT Edge của bạn](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)

## Điện toán biên

Điện toán biên liên quan đến việc sử dụng các máy tính để xử lý dữ liệu IoT gần nhất có thể với nơi dữ liệu được tạo ra. Thay vì xử lý dữ liệu trên đám mây, nó được chuyển đến biên của đám mây - mạng nội bộ của bạn.

![Sơ đồ kiến trúc hiển thị các dịch vụ internet trên đám mây và các thiết bị IoT trên mạng nội bộ](../../../../../translated_images/vi/cloud-without-edge.b4da641f6022c95ed6b91fde8b5323abd2f94e0d52073ad54172ae8f5dac90e9.png)

Trong các bài học trước, bạn đã có các thiết bị thu thập dữ liệu và gửi dữ liệu đến đám mây để phân tích, chạy các hàm serverless hoặc mô hình AI trên đám mây.

![Sơ đồ kiến trúc hiển thị các thiết bị IoT trên mạng nội bộ kết nối với các thiết bị biên, và các thiết bị biên này kết nối với đám mây](../../../../../translated_images/vi/cloud-with-edge.1e26462c62c126fe150bd15a5714ddf0be599f09bacbad08b85be02b76ea1ae1.png)

Điện toán biên liên quan đến việc chuyển một số dịch vụ đám mây ra khỏi đám mây và lên các máy tính chạy trên cùng mạng với các thiết bị IoT, chỉ giao tiếp với đám mây khi cần thiết. Ví dụ, bạn có thể chạy các mô hình AI trên các thiết bị biên để phân tích độ chín của trái cây, và chỉ gửi phân tích trở lại đám mây, chẳng hạn như số lượng trái cây chín so với chưa chín.

✅ Hãy suy nghĩ về các ứng dụng IoT mà bạn đã xây dựng cho đến nay. Những phần nào của chúng có thể được chuyển đến thiết bị biên?

### Ưu điểm

Các ưu điểm của điện toán biên bao gồm:

1. **Tốc độ** - điện toán biên lý tưởng cho dữ liệu nhạy cảm về thời gian vì các hành động được thực hiện trên cùng mạng với thiết bị, thay vì thực hiện các cuộc gọi qua internet. Điều này cho phép tốc độ cao hơn vì mạng nội bộ có thể chạy nhanh hơn đáng kể so với kết nối internet, với dữ liệu di chuyển khoảng cách ngắn hơn nhiều.

    > 💁 Mặc dù cáp quang được sử dụng cho kết nối internet cho phép dữ liệu di chuyển với tốc độ ánh sáng, dữ liệu vẫn cần thời gian để di chuyển vòng quanh thế giới đến các nhà cung cấp đám mây. Ví dụ, nếu bạn gửi dữ liệu từ châu Âu đến các dịch vụ đám mây ở Mỹ, sẽ mất ít nhất 28ms để dữ liệu vượt qua Đại Tây Dương qua cáp quang, chưa kể thời gian để đưa dữ liệu đến cáp quang, chuyển đổi từ tín hiệu điện sang ánh sáng và ngược lại ở phía bên kia, sau đó từ cáp quang đến nhà cung cấp đám mây.

    Điện toán biên cũng yêu cầu ít lưu lượng mạng hơn, giảm nguy cơ dữ liệu của bạn bị chậm lại do tắc nghẽn trên băng thông hạn chế của kết nối internet.

1. **Khả năng truy cập từ xa** - điện toán biên hoạt động khi bạn có kết nối hạn chế hoặc không có kết nối, hoặc kết nối quá đắt để sử dụng liên tục. Ví dụ, khi làm việc trong các khu vực thảm họa nhân đạo nơi cơ sở hạ tầng bị hạn chế, hoặc ở các quốc gia đang phát triển.

1. **Chi phí thấp hơn** - việc thu thập, lưu trữ, phân tích dữ liệu và kích hoạt hành động trên thiết bị biên giảm việc sử dụng các dịch vụ đám mây, điều này có thể giảm chi phí tổng thể của ứng dụng IoT của bạn. Gần đây đã có sự gia tăng các thiết bị được thiết kế cho điện toán biên, chẳng hạn như các bảng tăng tốc AI như [Jetson Nano từ NVIDIA](https://developer.nvidia.com/embedded/jetson-nano-developer-kit), có thể chạy các khối lượng công việc AI bằng phần cứng dựa trên GPU trên các thiết bị có giá dưới 100 USD.

1. **Quyền riêng tư và bảo mật** - với điện toán biên, dữ liệu ở lại trên mạng của bạn và không được tải lên đám mây. Điều này thường được ưu tiên cho thông tin nhạy cảm và nhận dạng cá nhân, đặc biệt vì dữ liệu không cần được lưu trữ sau khi đã được phân tích, điều này giảm đáng kể nguy cơ rò rỉ dữ liệu. Ví dụ bao gồm dữ liệu y tế và cảnh quay từ camera an ninh.

1. **Xử lý các thiết bị không an toàn** - nếu bạn có các thiết bị với các lỗ hổng bảo mật đã biết mà bạn không muốn kết nối trực tiếp với mạng hoặc internet của mình, bạn có thể kết nối chúng với một mạng riêng biệt thông qua một thiết bị IoT Edge làm cổng. Thiết bị biên này sau đó cũng có thể có kết nối với mạng rộng hơn của bạn hoặc internet, và quản lý luồng dữ liệu qua lại.

1. **Hỗ trợ các thiết bị không tương thích** - nếu bạn có các thiết bị không thể kết nối với IoT Hub, ví dụ như các thiết bị chỉ có thể kết nối bằng kết nối HTTP hoặc chỉ có Bluetooth, bạn có thể sử dụng một thiết bị IoT Edge làm thiết bị cổng, chuyển tiếp các tin nhắn đến IoT Hub.

✅ Nghiên cứu thêm: Những ưu điểm khác của điện toán biên có thể là gì?

### Nhược điểm

Có những nhược điểm của điện toán biên, nơi mà đám mây có thể là lựa chọn ưu tiên:

1. **Quy mô và tính linh hoạt** - điện toán đám mây có thể điều chỉnh theo nhu cầu mạng và dữ liệu trong thời gian thực bằng cách thêm hoặc giảm các máy chủ và tài nguyên khác. Để thêm nhiều máy tính biên yêu cầu thêm thiết bị thủ công.

1. **Độ tin cậy và khả năng phục hồi** - điện toán đám mây cung cấp nhiều máy chủ thường ở nhiều địa điểm để dự phòng và khôi phục thảm họa. Để có cùng mức độ dự phòng trên thiết bị biên yêu cầu đầu tư lớn và nhiều công việc cấu hình.

1. **Bảo trì** - các nhà cung cấp dịch vụ đám mây cung cấp bảo trì hệ thống và cập nhật.

✅ Nghiên cứu thêm: Những nhược điểm khác của điện toán biên có thể là gì?

Những nhược điểm thực sự là đối lập với các ưu điểm của việc sử dụng đám mây - bạn phải tự xây dựng và quản lý các thiết bị này, thay vì dựa vào chuyên môn và quy mô của các nhà cung cấp đám mây.

Một số rủi ro được giảm thiểu bởi chính bản chất của điện toán biên. Ví dụ, nếu bạn có một thiết bị biên chạy trong một nhà máy thu thập dữ liệu từ máy móc, bạn không cần phải nghĩ về một số kịch bản khôi phục thảm họa. Nếu nhà máy mất điện, bạn không cần một thiết bị biên dự phòng vì các máy móc tạo ra dữ liệu mà thiết bị biên xử lý cũng sẽ không có điện.

Đối với các hệ thống IoT, bạn thường muốn một sự kết hợp giữa điện toán đám mây và điện toán biên, tận dụng từng dịch vụ dựa trên nhu cầu của hệ thống, khách hàng và người bảo trì.

## Azure IoT Edge

![Logo Azure IoT Edge](../../../../../translated_images/vi/azure-iot-edge-logo.c1c076749b5cba2e8755262fadc2f19ca1146b948d76990b1229199ac2292d79.png)

Azure IoT Edge là một dịch vụ có thể giúp bạn chuyển các khối lượng công việc ra khỏi đám mây và đến thiết bị biên. Bạn thiết lập một thiết bị làm thiết bị biên, và từ đám mây bạn có thể triển khai mã lên thiết bị biên đó. Điều này cho phép bạn kết hợp khả năng của đám mây và thiết bị biên.

> 🎓 *Khối lượng công việc* là thuật ngữ chỉ bất kỳ dịch vụ nào thực hiện một loại công việc nào đó, chẳng hạn như các mô hình AI, ứng dụng hoặc các hàm serverless.

Ví dụ, bạn có thể huấn luyện một bộ phân loại hình ảnh trên đám mây, sau đó từ đám mây triển khai nó lên một thiết bị biên. Thiết bị IoT của bạn sau đó gửi hình ảnh đến thiết bị biên để phân loại, thay vì gửi hình ảnh qua internet. Nếu bạn cần triển khai một phiên bản mới của mô hình, bạn có thể huấn luyện nó trên đám mây và sử dụng IoT Edge để cập nhật mô hình trên thiết bị biên với phiên bản mới của bạn.

> 🎓 Phần mềm được triển khai lên IoT Edge được gọi là *module*. Theo mặc định, IoT Edge chạy các module giao tiếp với IoT Hub, chẳng hạn như các module `edgeAgent` và `edgeHub`. Khi bạn triển khai một bộ phân loại hình ảnh, nó được triển khai như một module bổ sung.

IoT Edge được tích hợp vào IoT Hub, vì vậy bạn có thể quản lý các thiết bị biên bằng cùng một dịch vụ mà bạn sẽ sử dụng để quản lý các thiết bị IoT, với cùng mức độ bảo mật.

IoT Edge chạy mã từ *container* - các ứng dụng tự chứa được chạy cách ly với các ứng dụng khác trên máy tính của bạn. Khi bạn chạy một container, nó hoạt động như một máy tính riêng biệt chạy bên trong máy tính của bạn, với phần mềm, dịch vụ và ứng dụng riêng của nó. Hầu hết thời gian, các container không thể truy cập bất cứ thứ gì trên máy tính của bạn trừ khi bạn chọn chia sẻ, chẳng hạn như một thư mục với container. Container sau đó cung cấp các dịch vụ thông qua một cổng mở mà bạn có thể kết nối hoặc cung cấp cho mạng của mình.

![Một yêu cầu web được chuyển hướng đến một container](../../../../../translated_images/vi/container-web-browser.4ee81dd4f0d8838ce622b2a0d600b6a4322b5d4fe43159facd87b7b34f84d66a.png)

Ví dụ, bạn có thể có một container với một trang web chạy trên cổng 80, cổng HTTP mặc định, và sau đó bạn có thể cung cấp nó từ máy tính của mình cũng trên cổng 80.

✅ Nghiên cứu thêm: Đọc thêm về container và các dịch vụ như Docker hoặc Moby.

Bạn có thể sử dụng Custom Vision để tải xuống các bộ phân loại hình ảnh và triển khai chúng dưới dạng container, hoặc chạy trực tiếp trên thiết bị hoặc triển khai qua IoT Edge. Khi chúng đang chạy trong một container, chúng có thể được truy cập bằng cùng REST API như phiên bản đám mây, nhưng với endpoint trỏ đến thiết bị biên đang chạy container.

## Đăng ký một thiết bị IoT Edge

Để sử dụng một thiết bị IoT Edge, nó cần được đăng ký trong IoT Hub.

### Nhiệm vụ - đăng ký một thiết bị IoT Edge

1. Tạo một IoT Hub trong nhóm tài nguyên `fruit-quality-detector`. Đặt cho nó một tên duy nhất dựa trên `fruit-quality-detector`.

1. Đăng ký một thiết bị IoT Edge có tên `fruit-quality-detector-edge` trong IoT Hub của bạn. Lệnh để làm điều này tương tự như lệnh được sử dụng để đăng ký một thiết bị không phải biên, ngoại trừ bạn cần thêm cờ `--edge-enabled`.

    ```sh
    az iot hub device-identity create --edge-enabled \
                                      --device-id fruit-quality-detector-edge \
                                      --hub-name <hub_name>
    ```

    Thay `<hub_name>` bằng tên của IoT Hub của bạn.

1. Lấy chuỗi kết nối cho thiết bị của bạn bằng lệnh sau:

    ```sh
    az iot hub device-identity connection-string show --device-id fruit-quality-detector-edge \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    Thay `<hub_name>` bằng tên của IoT Hub của bạn.

    Sao chép chuỗi kết nối được hiển thị trong đầu ra.

## Cài đặt một thiết bị IoT Edge

Khi bạn đã tạo đăng ký thiết bị biên trong IoT Hub, bạn có thể cài đặt thiết bị biên.

### Nhiệm vụ - Cài đặt và khởi động IoT Edge Runtime

**IoT Edge runtime chỉ chạy các container Linux.** Nó có thể chạy trên Linux hoặc trên Windows sử dụng các máy ảo Linux.

* Nếu bạn đang sử dụng Raspberry Pi làm thiết bị IoT của mình, thì nó chạy một phiên bản Linux được hỗ trợ và có thể lưu trữ IoT Edge runtime. Làm theo [hướng dẫn cài đặt Azure IoT Edge cho Linux trên tài liệu Microsoft](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) để cài đặt IoT Edge và thiết lập chuỗi kết nối.

    > 💁 Nhớ rằng, Raspberry Pi OS là một biến thể của Debian Linux.

* Nếu bạn không sử dụng Raspberry Pi, nhưng có một máy tính Linux, bạn có thể chạy IoT Edge runtime. Làm theo [hướng dẫn cài đặt Azure IoT Edge cho Linux trên tài liệu Microsoft](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) để cài đặt IoT Edge và thiết lập chuỗi kết nối.

* Nếu bạn đang sử dụng Windows, bạn có thể cài đặt IoT Edge runtime trong một máy ảo Linux bằng cách làm theo [phần cài đặt và khởi động IoT Edge runtime trong hướng dẫn triển khai module IoT Edge đầu tiên của bạn lên thiết bị Windows trên tài liệu Microsoft](https://docs.microsoft.com/azure/iot-edge/quickstart?WT.mc_id=academic-17441-jabenn#install-and-start-the-iot-edge-runtime). Bạn có thể dừng lại khi đến phần *Triển khai một module*.

* Nếu bạn đang sử dụng macOS, bạn có thể tạo một máy ảo (VM) trên đám mây để sử dụng làm thiết bị IoT Edge của mình. Đây là các máy tính bạn có thể tạo trên đám mây và truy cập qua internet. Bạn có thể tạo một VM Linux có cài đặt IoT Edge. Làm theo [hướng dẫn tạo một máy ảo chạy IoT Edge](vm-iotedge.md) để biết cách thực hiện điều này.

## Xuất mô hình của bạn

Để chạy bộ phân loại trên thiết bị biên, nó cần được xuất từ Custom Vision. Custom Vision có thể tạo hai loại mô hình - mô hình tiêu chuẩn và mô hình nhỏ gọn. Mô hình nhỏ gọn sử dụng các kỹ thuật khác nhau để giảm kích thước của mô hình, làm cho nó đủ nhỏ để tải xuống và triển khai trên các thiết bị IoT.

Khi bạn tạo bộ phân loại hình ảnh, bạn đã sử dụng miền *Food*, một phiên bản của mô hình được tối ưu hóa để huấn luyện trên hình ảnh thực phẩm. Trong Custom Vision, bạn thay đổi miền của dự án của mình, sử dụng dữ liệu huấn luyện của bạn để huấn luyện một mô hình mới với miền mới. Tất cả các miền được Custom Vision hỗ trợ đều có sẵn dưới dạng tiêu chuẩn và nhỏ gọn.

### Nhiệm vụ - huấn luyện mô hình của bạn bằng miền Food (compact)
1. Mở cổng Custom Vision tại [CustomVision.ai](https://customvision.ai) và đăng nhập nếu bạn chưa mở. Sau đó, mở dự án `fruit-quality-detector` của bạn.

1. Chọn nút **Settings** (biểu tượng ⚙).

1. Trong danh sách *Domains*, chọn *Food (compact)*.

1. Dưới mục *Export Capabilities*, đảm bảo đã chọn *Basic platforms (Tensorflow, CoreML, ONNX, ...)*.

1. Ở cuối trang Settings, chọn **Save Changes**.

1. Huấn luyện lại mô hình bằng nút **Train**, chọn *Quick training*.

### Nhiệm vụ - xuất mô hình của bạn

Sau khi mô hình đã được huấn luyện, cần xuất nó dưới dạng container.

1. Chọn tab **Performance**, và tìm phiên bản mới nhất của bạn đã được huấn luyện bằng compact domain.

1. Chọn nút **Export** ở trên cùng.

1. Chọn **DockerFile**, sau đó chọn phiên bản phù hợp với thiết bị edge của bạn:

    * Nếu bạn đang chạy IoT Edge trên máy tính Linux, máy tính Windows hoặc máy ảo, chọn phiên bản *Linux*.
    * Nếu bạn đang chạy IoT Edge trên Raspberry Pi, chọn phiên bản *ARM (Raspberry Pi 3)*.

    
> 🎓 Docker là một trong những công cụ phổ biến nhất để quản lý container, và DockerFile là tập hợp các hướng dẫn về cách thiết lập container.

1. Chọn **Export** để Custom Vision tạo các tệp liên quan, sau đó chọn **Download** để tải chúng về dưới dạng tệp zip.

1. Lưu các tệp vào máy tính của bạn, sau đó giải nén thư mục.

## Chuẩn bị container của bạn để triển khai

![Containers được xây dựng sau đó đẩy lên container registry, rồi triển khai từ container registry đến thiết bị edge bằng IoT Edge](../../../../../translated_images/vi/container-edge-flow.c246050dd60ceefdb6ace026a4ce5c6aa4112bb5898ae23fbb2ab4be29ae3e1b.png)

Sau khi bạn đã tải xuống mô hình của mình, nó cần được xây dựng thành container, sau đó đẩy lên container registry - một vị trí trực tuyến nơi bạn có thể lưu trữ container. IoT Edge sau đó có thể tải container từ registry và đẩy nó đến thiết bị của bạn.

![Logo Azure Container Registry](../../../../../translated_images/vi/azure-container-registry-logo.09494206991d4b295025ebff7d4e2900325e527a59184ffbc8464b6ab59654be.png)

Container registry mà bạn sẽ sử dụng cho bài học này là Azure Container Registry. Đây không phải là dịch vụ miễn phí, vì vậy để tiết kiệm chi phí, hãy đảm bảo [dọn dẹp dự án của bạn](../../../clean-up.md) sau khi hoàn thành.

> 💁 Bạn có thể xem chi phí sử dụng Azure Container Registry trên [trang giá Azure Container Registry](https://azure.microsoft.com/pricing/details/container-registry/?WT.mc_id=academic-17441-jabenn).

### Nhiệm vụ - cài đặt Docker

Để xây dựng và triển khai bộ phân loại, bạn có thể cần cài đặt [Docker](https://www.docker.com/).

Bạn chỉ cần làm điều này nếu bạn dự định xây dựng container từ một thiết bị khác với thiết bị mà bạn đã cài đặt IoT Edge - vì khi cài đặt IoT Edge, Docker đã được cài đặt cho bạn.

1. Nếu bạn xây dựng container Docker trên một thiết bị khác với thiết bị IoT Edge của bạn, hãy làm theo hướng dẫn cài đặt Docker trên [trang cài đặt Docker](https://www.docker.com/products/docker-desktop) để cài đặt Docker Desktop hoặc Docker engine. Đảm bảo nó đang chạy sau khi cài đặt.

### Nhiệm vụ - tạo tài nguyên container registry

1. Chạy lệnh sau từ Terminal hoặc command prompt để tạo tài nguyên Azure Container Registry:

    ```sh
    az acr create --resource-group fruit-quality-detector \
                  --sku Basic \
                  --name <Container registry name>
    ```

    Thay thế `<Container registry name>` bằng một tên duy nhất cho container registry của bạn, chỉ sử dụng chữ cái và số. Dựa vào `fruitqualitydetector`. Tên này sẽ trở thành một phần của URL để truy cập container registry, vì vậy cần phải là duy nhất trên toàn cầu.

1. Đăng nhập vào Azure Container Registry bằng lệnh sau:

    ```sh
    az acr login --name <Container registry name>
    ```

    Thay thế `<Container registry name>` bằng tên bạn đã sử dụng cho container registry của mình.

1. Đặt container registry vào chế độ admin để bạn có thể tạo mật khẩu bằng lệnh sau:

    ```sh
    az acr update --admin-enabled true \
                 --name <Container registry name>
    ```

    Thay thế `<Container registry name>` bằng tên bạn đã sử dụng cho container registry của mình.

1. Tạo mật khẩu cho container registry của bạn bằng lệnh sau:

    ```sh
     az acr credential renew --password-name password \
                             --output table \
                             --name <Container registry name>
    ```

    Thay thế `<Container registry name>` bằng tên bạn đã sử dụng cho container registry của mình.

    Sao chép giá trị của `PASSWORD`, vì bạn sẽ cần nó sau này.

### Nhiệm vụ - xây dựng container của bạn

Những gì bạn tải xuống từ Custom Vision là một DockerFile chứa các hướng dẫn về cách container nên được xây dựng, cùng với mã ứng dụng sẽ chạy bên trong container để lưu trữ mô hình Custom Vision của bạn, cùng với REST API để gọi nó. Bạn có thể sử dụng Docker để xây dựng một container được gắn thẻ từ DockerFile, sau đó đẩy nó lên container registry.

> 🎓 Container được gắn thẻ để xác định tên và phiên bản của chúng. Khi bạn cần cập nhật container, bạn có thể xây dựng nó với cùng thẻ nhưng phiên bản mới hơn.

1. Mở terminal hoặc command prompt của bạn và điều hướng đến mô hình đã giải nén mà bạn đã tải xuống từ Custom Vision.

1. Chạy lệnh sau để xây dựng và gắn thẻ hình ảnh:

    ```sh
    docker build --platform <platform> -t <Container registry name>.azurecr.io/classifier:v1 .
    ```

    Thay thế `<platform>` bằng nền tảng mà container này sẽ chạy trên đó. Nếu bạn đang chạy IoT Edge trên Raspberry Pi, đặt giá trị này là `linux/armhf`, nếu không thì đặt là `linux/amd64`.

    > 💁 Nếu bạn đang chạy lệnh này từ thiết bị mà bạn đang chạy IoT Edge, chẳng hạn như chạy từ Raspberry Pi của bạn, bạn có thể bỏ qua phần `--platform <platform>` vì nó mặc định là nền tảng hiện tại.

    Thay thế `<Container registry name>` bằng tên bạn đã sử dụng cho container registry của mình.

    > 💁 Nếu bạn đang chạy trên Linux hoặc Raspberry Pi OS, bạn có thể cần sử dụng `sudo` để chạy lệnh này.

    Docker sẽ xây dựng hình ảnh, cấu hình tất cả phần mềm cần thiết. Hình ảnh sau đó sẽ được gắn thẻ là `classifier:v1`.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux docker build --platform linux/amd64 -t  fruitqualitydetectorjimb.azurecr.io/classifier:v1 .
    [+] Building 102.4s (11/11) FINISHED
     => [internal] load build definition from Dockerfile
     => => transferring dockerfile: 131B
     => [internal] load .dockerignore
     => => transferring context: 2B
     => [internal] load metadata for docker.io/library/python:3.7-slim
     => [internal] load build context
     => => transferring context: 905B
     => [1/6] FROM docker.io/library/python:3.7-slim@sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6
     => => resolve docker.io/library/python:3.7-slim@sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6
     => => sha256:b4d181a07f8025e00e0cb28f1cc14613da2ce26450b80c54aea537fa93cf3bda 27.15MB / 27.15MB
     => => sha256:de8ecf497b753094723ccf9cea8a46076e7cb845f333df99a6f4f397c93c6ea9 2.77MB / 2.77MB
     => => sha256:707b80804672b7c5d8f21e37c8396f319151e1298d976186b4f3b76ead9f10c8 10.06MB / 10.06MB
     => => sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6 1.86kB / 1.86kB
     => => sha256:44073386687709c437586676b572ff45128ff1f1570153c2f727140d4a9accad 1.37kB / 1.37kB
     => => sha256:3d94f0f2ca798607808b771a7766f47ae62a26f820e871dd488baeccc69838d1 8.31kB / 8.31kB
     => => sha256:283715715396fd56d0e90355125fd4ec57b4f0773f306fcd5fa353b998beeb41 233B / 233B
     => => sha256:8353afd48f6b84c3603ea49d204bdcf2a1daada15f5d6cad9cc916e186610a9f 2.64MB / 2.64MB
     => => extracting sha256:b4d181a07f8025e00e0cb28f1cc14613da2ce26450b80c54aea537fa93cf3bda
     => => extracting sha256:de8ecf497b753094723ccf9cea8a46076e7cb845f333df99a6f4f397c93c6ea9
     => => extracting sha256:707b80804672b7c5d8f21e37c8396f319151e1298d976186b4f3b76ead9f10c8
     => => extracting sha256:283715715396fd56d0e90355125fd4ec57b4f0773f306fcd5fa353b998beeb41
     => => extracting sha256:8353afd48f6b84c3603ea49d204bdcf2a1daada15f5d6cad9cc916e186610a9f
     => [2/6] RUN pip install -U pip
     => [3/6] RUN pip install --no-cache-dir numpy~=1.17.5 tensorflow~=2.0.2 flask~=1.1.2 pillow~=7.2.0
     => [4/6] RUN pip install --no-cache-dir mscviplib==2.200731.16
     => [5/6] COPY app /app
     => [6/6] WORKDIR /app
     => exporting to image
     => => exporting layers
     => => writing image sha256:1846b6f134431f78507ba7c079358ed66d944c0e185ab53428276bd822400386
     => => naming to fruitqualitydetectorjimb.azurecr.io/classifier:v1
    ```

### Nhiệm vụ - đẩy container của bạn lên container registry

1. Sử dụng lệnh sau để đẩy container của bạn lên container registry:

    ```sh
    docker push <Container registry name>.azurecr.io/classifier:v1
    ```

    Thay thế `<Container registry name>` bằng tên bạn đã sử dụng cho container registry của mình.

    > 💁 Nếu bạn đang chạy Linux, bạn có thể cần sử dụng `sudo` để chạy lệnh này.

    Container sẽ được đẩy lên container registry.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux docker push fruitqualitydetectorjimb.azurecr.io/classifier:v1
    The push refers to repository [fruitqualitydetectorjimb.azurecr.io/classifier]
    5f70bf18a086: Pushed 
    8a1ba9294a22: Pushed 
    56cf27184a76: Pushed 
    b32154f3f5dd: Pushed 
    36103e9a3104: Pushed 
    e2abb3cacca0: Pushed 
    4213fd357bbe: Pushed 
    7ea163ba4dce: Pushed 
    537313a13d90: Pushed 
    764055ebc9a7: Pushed 
    v1: digest: sha256:ea7894652e610de83a5a9e429618e763b8904284253f4fa0c9f65f0df3a5ded8 size: 2423
    ```

1. Để xác minh việc đẩy, bạn có thể liệt kê các container trong registry của mình bằng lệnh sau:

    ```sh
    az acr repository list --output table \
                           --name <Container registry name> 
    ```

    Thay thế `<Container registry name>` bằng tên bạn đã sử dụng cho container registry của mình.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux az acr repository list --name fruitqualitydetectorjimb --output table
    Result
    ----------
    classifier
    ```

    Bạn sẽ thấy bộ phân loại của mình được liệt kê trong kết quả.

## Triển khai container của bạn

Container của bạn bây giờ có thể được triển khai đến thiết bị IoT Edge của bạn. Để triển khai, bạn cần định nghĩa một deployment manifest - một tài liệu JSON liệt kê các module sẽ được triển khai đến thiết bị edge.

### Nhiệm vụ - tạo deployment manifest

1. Tạo một tệp mới có tên `deployment.json` ở đâu đó trên máy tính của bạn.

1. Thêm nội dung sau vào tệp này:

    ```json
    {
        "content": {
            "modulesContent": {
                "$edgeAgent": {
                    "properties.desired": {
                        "schemaVersion": "1.1",
                        "runtime": {
                            "type": "docker",
                            "settings": {
                                "minDockerVersion": "v1.25",
                                "loggingOptions": "",
                                "registryCredentials": {
                                    "ClassifierRegistry": {
                                        "username": "<Container registry name>",
                                        "password": "<Container registry password>",
                                        "address": "<Container registry name>.azurecr.io"
                                      }
                                }
                            }
                        },
                        "systemModules": {
                            "edgeAgent": {
                                "type": "docker",
                                "settings": {
                                    "image": "mcr.microsoft.com/azureiotedge-agent:1.1",
                                    "createOptions": "{}"
                                }
                            },
                            "edgeHub": {
                                "type": "docker",
                                "status": "running",
                                "restartPolicy": "always",
                                "settings": {
                                    "image": "mcr.microsoft.com/azureiotedge-hub:1.1",
                                    "createOptions": "{\"HostConfig\":{\"PortBindings\":{\"5671/tcp\":[{\"HostPort\":\"5671\"}],\"8883/tcp\":[{\"HostPort\":\"8883\"}],\"443/tcp\":[{\"HostPort\":\"443\"}]}}}"
                                }
                            }
                        },
                        "modules": {
                            "ImageClassifier": {
                                "version": "1.0",
                                "type": "docker",
                                "status": "running",
                                "restartPolicy": "always",
                                "settings": {
                                    "image": "<Container registry name>.azurecr.io/classifier:v1",
                                    "createOptions": "{\"ExposedPorts\": {\"80/tcp\": {}},\"HostConfig\": {\"PortBindings\": {\"80/tcp\": [{\"HostPort\": \"80\"}]}}}"
                                }
                            }
                        }
                    }
                },
                "$edgeHub": {
                    "properties.desired": {
                        "schemaVersion": "1.1",
                        "routes": {
                            "upstream": "FROM /messages/* INTO $upstream"
                        },
                        "storeAndForwardConfiguration": {
                            "timeToLiveSecs": 7200
                        }
                    }
                }
            }
        }
    }
    ```

    > 💁 Bạn có thể tìm thấy tệp này trong thư mục [code-deployment/deployment](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-deployment/deployment).

    Thay thế ba trường hợp của `<Container registry name>` bằng tên bạn đã sử dụng cho container registry của mình. Một trường nằm trong phần module `ImageClassifier`, hai trường còn lại nằm trong phần `registryCredentials`.

    Thay thế `<Container registry password>` trong phần `registryCredentials` bằng mật khẩu container registry của bạn.

1. Từ thư mục chứa deployment manifest của bạn, chạy lệnh sau:

    ```sh
    az iot edge set-modules --device-id fruit-quality-detector-edge \
                            --content deployment.json \
                            --hub-name <hub_name>
    ```

    Thay thế `<hub_name>` bằng tên của IoT Hub của bạn.

    Module bộ phân loại hình ảnh sẽ được triển khai đến thiết bị edge của bạn.

### Nhiệm vụ - xác minh bộ phân loại đang chạy

1. Kết nối với thiết bị IoT Edge:

    * Nếu bạn đang sử dụng Raspberry Pi để chạy IoT Edge, kết nối bằng ssh từ terminal của bạn hoặc qua phiên SSH từ xa trong VS Code.
    * Nếu bạn đang chạy IoT Edge trong container Linux trên Windows, làm theo các bước trong [hướng dẫn xác minh cấu hình thành công](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge-on-windows?WT.mc_id=academic-17441-jabenn&view=iotedge-2018-06&tabs=powershell#verify-successful-configuration) để kết nối với thiết bị IoT Edge.
    * Nếu bạn đang chạy IoT Edge trên máy ảo, bạn có thể SSH vào máy bằng `adminUsername` và `password` bạn đã đặt khi tạo VM, và sử dụng địa chỉ IP hoặc tên DNS:

        ```sh
        ssh <adminUsername>@<IP address>
        ```

        Hoặc:

        ```sh
        ssh <adminUsername>@<DNS Name>
        ```

        Nhập mật khẩu của bạn khi được yêu cầu.

1. Sau khi bạn đã kết nối, chạy lệnh sau để lấy danh sách các module IoT Edge:

    ```sh
    iotedge list
    ```

    > 💁 Bạn có thể cần chạy lệnh này với `sudo`.

    Bạn sẽ thấy các module đang chạy:

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge list
    NAME             STATUS           DESCRIPTION      CONFIG
    ImageClassifier  running          Up 42 minutes    fruitqualitydetectorjimb.azurecr.io/classifier:v1
    edgeAgent        running          Up 42 minutes    mcr.microsoft.com/azureiotedge-agent:1.1
    edgeHub          running          Up 42 minutes    mcr.microsoft.com/azureiotedge-hub:1.1
    ```

1. Kiểm tra nhật ký cho module bộ phân loại hình ảnh bằng lệnh sau:

    ```sh
    iotedge logs ImageClassifier
    ```

    > 💁 Bạn có thể cần chạy lệnh này với `sudo`.

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge logs ImageClassifier
    2021-07-05 20:30:15.387144: I tensorflow/core/platform/cpu_feature_guard.cc:142] Your CPU supports instructions that this TensorFlow binary was not compiled to use: AVX2 FMA
    2021-07-05 20:30:15.392185: I tensorflow/core/platform/profile_utils/cpu_utils.cc:94] CPU Frequency: 2394450000 Hz
    2021-07-05 20:30:15.392712: I tensorflow/compiler/xla/service/service.cc:168] XLA service 0x55ed9ac83470 executing computations on platform Host. Devices:
    2021-07-05 20:30:15.392806: I tensorflow/compiler/xla/service/service.cc:175]   StreamExecutor device (0): Host, Default Version
    Loading model...Success!
    Loading labels...2 found. Success!
     * Serving Flask app "app" (lazy loading)
     * Environment: production
       WARNING: This is a development server. Do not use it in a production deployment.
       Use a production WSGI server instead.
     * Debug mode: off
     * Running on http://0.0.0.0:80/ (Press CTRL+C to quit)
    ```

### Nhiệm vụ - kiểm tra bộ phân loại hình ảnh

1. Bạn có thể sử dụng CURL để kiểm tra bộ phân loại hình ảnh bằng địa chỉ IP hoặc tên máy của máy tính đang chạy IoT Edge agent. Tìm địa chỉ IP:

    * Nếu bạn đang trên cùng máy mà IoT Edge đang chạy, bạn có thể sử dụng `localhost` làm tên máy.
    * Nếu bạn đang sử dụng VM, bạn có thể sử dụng địa chỉ IP hoặc tên DNS của VM.
    * Nếu không, bạn có thể lấy địa chỉ IP của máy đang chạy IoT Edge:
      * Trên Windows 10, làm theo [hướng dẫn tìm địa chỉ IP của bạn](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn).
      * Trên macOS, làm theo [hướng dẫn cách tìm địa chỉ IP trên Mac](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac).
      * Trên Linux, làm theo phần tìm địa chỉ IP riêng trong [hướng dẫn cách tìm địa chỉ IP trên Linux](https://opensource.com/article/18/5/how-find-ip-address-linux).

1. Bạn có thể kiểm tra container với một tệp cục bộ bằng cách chạy lệnh curl sau:

    ```sh
    curl --location \
         --request POST 'http://<IP address or name>/image' \
         --header 'Content-Type: image/png' \
         --data-binary '@<file_Name>' 
    ```

    Thay thế `<IP address or name>` bằng địa chỉ IP hoặc tên máy của máy tính đang chạy IoT Edge. Thay thế `<file_Name>` bằng tên của tệp để kiểm tra.

    Bạn sẽ thấy kết quả dự đoán trong đầu ra:

    ```output
    {
        "created": "2021-07-05T21:44:39.573181",
        "id": "",
        "iteration": "",
        "predictions": [
            {
                "boundingBox": null,
                "probability": 0.9995615482330322,
                "tagId": "",
                "tagName": "ripe"
            },
            {
                "boundingBox": null,
                "probability": 0.0004384400090202689,
                "tagId": "",
                "tagName": "unripe"
            }
        ],
        "project": ""
    }
    ```

    > 💁 Không cần cung cấp khóa dự đoán ở đây, vì điều này không sử dụng tài nguyên Azure. Thay vào đó, bảo mật sẽ được cấu hình trên mạng nội bộ dựa trên nhu cầu bảo mật nội bộ, thay vì dựa vào endpoint công cộng và khóa API.

## Sử dụng thiết bị IoT Edge của bạn

Bây giờ bộ phân loại hình ảnh của bạn đã được triển khai đến thiết bị IoT Edge, bạn có thể sử dụng nó từ thiết bị IoT của mình.

### Nhiệm vụ - sử dụng thiết bị IoT Edge của bạn

Làm theo hướng dẫn phù hợp để phân loại hình ảnh bằng bộ phân loại IoT Edge:

* [Arduino - Wio Terminal](wio-terminal.md)
* [Máy tính đơn bảng - Raspberry Pi/Thiết bị IoT ảo](single-board-computer.md)

### Huấn luyện lại mô hình

Một trong những hạn chế của việc chạy bộ phân loại hình ảnh trên IoT Edge là chúng không được kết nối với dự án Custom Vision của bạn. Nếu bạn xem tab **Predictions** trong Custom Vision, bạn sẽ không thấy các hình ảnh đã được phân loại bằng bộ phân loại dựa trên Edge.

Đây là hành vi mong đợi - hình ảnh không được gửi lên cloud để phân loại, vì vậy chúng sẽ không có sẵn trên cloud. Một trong những lợi ích của việc sử dụng IoT Edge là quyền riêng tư, đảm bảo rằng hình ảnh không rời khỏi mạng của bạn, lợi ích khác là khả năng làm việc offline, không phụ thuộc vào việc tải lên hình ảnh khi thiết bị không có kết nối internet. Hạn chế là cải thiện mô hình của bạn - bạn sẽ cần triển khai một cách khác để lưu trữ hình ảnh có thể được phân loại lại thủ công để cải thiện và huấn luyện lại bộ phân loại hình ảnh.

✅ Hãy suy nghĩ về cách tải lên hình ảnh để huấn luyện lại bộ phân loại.

---

## 🚀 Thử thách

Chạy các mô hình AI trên thiết bị edge có thể nhanh hơn so với trên cloud - khoảng cách mạng ngắn hơn. Tuy nhiên, chúng cũng có thể chậm hơn vì phần cứng chạy mô hình có thể không mạnh bằng cloud.

Hãy thực hiện một số phép đo thời gian và so sánh xem việc gọi đến thiết bị edge của bạn nhanh hơn hay chậm hơn so với gọi đến cloud? Hãy suy nghĩ về các lý do giải thích sự khác biệt, hoặc không có sự khác biệt. Nghiên cứu các cách để chạy mô hình AI nhanh hơn trên edge bằng phần cứng chuyên dụng.

## Câu hỏi sau bài giảng

[Câu hỏi sau bài giảng](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/34)

## Ôn tập & Tự học

* Đọc thêm về container trên [trang ảo hóa cấp hệ điều hành trên Wikipedia](https://wikipedia.org/wiki/OS-level_virtualization).
* Tìm hiểu thêm về điện toán biên, với trọng tâm là cách 5G có thể giúp mở rộng điện toán biên trong [bài viết về điện toán biên là gì và tại sao nó quan trọng? trên NetworkWorld](https://www.networkworld.com/article/3224893/what-is-edge-computing-and-how-its-changing-the-network.html)
* Tìm hiểu thêm về việc chạy các dịch vụ AI trên IoT Edge bằng cách xem [tập học cách sử dụng Azure IoT Edge trên một dịch vụ AI được xây dựng sẵn trên Edge để phát hiện ngôn ngữ trong Learn Live trên Microsoft Channel9](https://channel9.msdn.com/Shows/Learn-Live/Sharpen-Your-AI-Edge-Skills-Episode-4-Learn-How-to-Use-Azure-IoT-Edge-on-a-Pre-Built-AI-Service-on-t?WT.mc_id=academic-17441-jabenn)

## Bài tập

[Chạy các dịch vụ khác trên biên](assignment.md)

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.