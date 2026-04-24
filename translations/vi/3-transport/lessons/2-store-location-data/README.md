# Lưu trữ dữ liệu vị trí

![Tổng quan bài học dưới dạng sketchnote](../../../../../translated_images/vi/lesson-12.ca7f53039712a3ec.webp)

> Sketchnote bởi [Nitya Narasimhan](https://github.com/nitya). Nhấn vào hình ảnh để xem phiên bản lớn hơn.

## Câu hỏi trước bài học

[Câu hỏi trước bài học](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/23)

## Giới thiệu

Trong bài học trước, bạn đã học cách sử dụng cảm biến GPS để thu thập dữ liệu vị trí. Để sử dụng dữ liệu này nhằm hình dung vị trí của một xe tải chở thực phẩm và hành trình của nó, dữ liệu cần được gửi đến một dịch vụ IoT trên đám mây và sau đó được lưu trữ ở đâu đó.

Trong bài học này, bạn sẽ tìm hiểu về các cách khác nhau để lưu trữ dữ liệu IoT và học cách lưu trữ dữ liệu từ dịch vụ IoT của bạn bằng mã không máy chủ.

Trong bài học này, chúng ta sẽ đề cập đến:

* [Dữ liệu có cấu trúc và không có cấu trúc](../../../../../3-transport/lessons/2-store-location-data)
* [Gửi dữ liệu GPS đến IoT Hub](../../../../../3-transport/lessons/2-store-location-data)
* [Đường dẫn nóng, ấm và lạnh](../../../../../3-transport/lessons/2-store-location-data)
* [Xử lý sự kiện GPS bằng mã không máy chủ](../../../../../3-transport/lessons/2-store-location-data)
* [Tài khoản lưu trữ Azure](../../../../../3-transport/lessons/2-store-location-data)
* [Kết nối mã không máy chủ của bạn với lưu trữ](../../../../../3-transport/lessons/2-store-location-data)

## Dữ liệu có cấu trúc và không có cấu trúc

Hệ thống máy tính xử lý dữ liệu, và dữ liệu này có nhiều hình dạng và kích thước khác nhau. Nó có thể là các con số đơn lẻ, lượng lớn văn bản, video và hình ảnh, hoặc dữ liệu IoT. Dữ liệu thường được chia thành hai loại - *dữ liệu có cấu trúc* và *dữ liệu không có cấu trúc*.

* **Dữ liệu có cấu trúc** là dữ liệu có cấu trúc rõ ràng, cứng nhắc, không thay đổi và thường được ánh xạ vào các bảng dữ liệu có mối quan hệ. Một ví dụ là thông tin cá nhân của một người bao gồm tên, ngày sinh và địa chỉ của họ.

* **Dữ liệu không có cấu trúc** là dữ liệu không có cấu trúc rõ ràng, cứng nhắc, bao gồm cả dữ liệu có thể thay đổi cấu trúc thường xuyên. Một ví dụ là các tài liệu như văn bản viết hoặc bảng tính.

✅ Nghiên cứu thêm: Bạn có thể nghĩ ra một số ví dụ khác về dữ liệu có cấu trúc và không có cấu trúc không?

> 💁 Ngoài ra còn có dữ liệu bán cấu trúc, có cấu trúc nhưng không phù hợp với các bảng dữ liệu cố định.

Dữ liệu IoT thường được coi là dữ liệu không có cấu trúc.

Hãy tưởng tượng bạn đang thêm các thiết bị IoT vào một đội xe của một trang trại thương mại lớn. Bạn có thể muốn sử dụng các thiết bị khác nhau cho các loại xe khác nhau. Ví dụ:

* Đối với các phương tiện nông nghiệp như máy kéo, bạn muốn dữ liệu GPS để đảm bảo chúng đang làm việc trên các cánh đồng đúng.
* Đối với xe tải giao hàng vận chuyển thực phẩm đến kho, bạn muốn dữ liệu GPS cũng như dữ liệu tốc độ và gia tốc để đảm bảo tài xế lái xe an toàn, và dữ liệu nhận dạng tài xế và thời gian bắt đầu/kết thúc để đảm bảo tuân thủ luật pháp địa phương về giờ làm việc.
* Đối với xe tải đông lạnh, bạn cũng muốn dữ liệu nhiệt độ để đảm bảo thực phẩm không bị quá nóng hoặc quá lạnh và hỏng trong quá trình vận chuyển.

Dữ liệu này có thể thay đổi liên tục. Ví dụ, nếu thiết bị IoT nằm trong cabin xe tải, thì dữ liệu mà nó gửi có thể thay đổi khi rơ-moóc thay đổi, ví dụ chỉ gửi dữ liệu nhiệt độ khi sử dụng rơ-moóc đông lạnh.

✅ Dữ liệu IoT nào khác có thể được thu thập? Hãy nghĩ về các loại hàng hóa mà xe tải có thể chở, cũng như dữ liệu bảo trì.

Dữ liệu này thay đổi từ xe này sang xe khác, nhưng tất cả đều được gửi đến cùng một dịch vụ IoT để xử lý. Dịch vụ IoT cần có khả năng xử lý dữ liệu không có cấu trúc này, lưu trữ nó theo cách cho phép tìm kiếm hoặc phân tích, nhưng vẫn hoạt động với các cấu trúc khác nhau của dữ liệu này.

### Lưu trữ SQL và NoSQL

Cơ sở dữ liệu là các dịch vụ cho phép bạn lưu trữ và truy vấn dữ liệu. Cơ sở dữ liệu có hai loại - SQL và NoSQL.

#### Cơ sở dữ liệu SQL

Các cơ sở dữ liệu đầu tiên là Hệ thống Quản lý Cơ sở dữ liệu Quan hệ (RDBMS), hay cơ sở dữ liệu quan hệ. Chúng còn được gọi là cơ sở dữ liệu SQL theo ngôn ngữ Structured Query Language (SQL) được sử dụng để tương tác với chúng nhằm thêm, xóa, cập nhật hoặc truy vấn dữ liệu. Các cơ sở dữ liệu này bao gồm một lược đồ - một tập hợp các bảng dữ liệu được định nghĩa rõ ràng, tương tự như bảng tính. Mỗi bảng có nhiều cột được đặt tên. Khi bạn chèn dữ liệu, bạn thêm một hàng vào bảng, đặt giá trị vào từng cột. Điều này giữ cho dữ liệu có cấu trúc rất cứng nhắc - mặc dù bạn có thể để trống các cột, nếu bạn muốn thêm một cột mới, bạn phải thực hiện điều này trên cơ sở dữ liệu, điền giá trị cho các hàng hiện có. Các cơ sở dữ liệu này có tính quan hệ - nghĩa là một bảng có thể có mối quan hệ với bảng khác.

![Một cơ sở dữ liệu quan hệ với ID của bảng Người dùng liên quan đến cột ID người dùng của bảng mua hàng, và ID của bảng sản phẩm liên quan đến cột ID sản phẩm của bảng mua hàng](../../../../../translated_images/vi/sql-database.be160f12bfccefd3.webp)

Ví dụ, nếu bạn lưu trữ thông tin cá nhân của người dùng trong một bảng, bạn sẽ có một số ID duy nhất nội bộ cho mỗi người dùng được sử dụng trong một hàng trong bảng chứa tên và địa chỉ của người dùng. Nếu bạn muốn lưu trữ các chi tiết khác về người dùng đó, chẳng hạn như các giao dịch mua của họ, trong một bảng khác, bạn sẽ có một cột trong bảng mới cho ID của người dùng đó. Khi bạn tra cứu một người dùng, bạn có thể sử dụng ID của họ để lấy thông tin cá nhân từ một bảng và các giao dịch mua của họ từ bảng khác.

Cơ sở dữ liệu SQL lý tưởng để lưu trữ dữ liệu có cấu trúc và khi bạn muốn đảm bảo dữ liệu khớp với lược đồ của bạn.

✅ Nếu bạn chưa từng sử dụng SQL trước đây, hãy dành chút thời gian để đọc về nó trên [trang SQL trên Wikipedia](https://wikipedia.org/wiki/SQL).

Một số cơ sở dữ liệu SQL nổi tiếng là Microsoft SQL Server, MySQL và PostgreSQL.

✅ Nghiên cứu thêm: Đọc về một số cơ sở dữ liệu SQL này và khả năng của chúng.

#### Cơ sở dữ liệu NoSQL

Cơ sở dữ liệu NoSQL được gọi là NoSQL vì chúng không có cấu trúc cứng nhắc như cơ sở dữ liệu SQL. Chúng cũng được gọi là cơ sở dữ liệu tài liệu vì chúng có thể lưu trữ dữ liệu không có cấu trúc như tài liệu.

> 💁 Mặc dù tên gọi của chúng, một số cơ sở dữ liệu NoSQL cho phép bạn sử dụng SQL để truy vấn dữ liệu.

![Tài liệu trong các thư mục trong cơ sở dữ liệu NoSQL](../../../../../translated_images/vi/noqsl-database.62d24ccf5b73f60d.webp)

Cơ sở dữ liệu NoSQL không có lược đồ được định nghĩa trước giới hạn cách dữ liệu được lưu trữ, thay vào đó bạn có thể chèn bất kỳ dữ liệu không có cấu trúc nào, thường sử dụng tài liệu JSON. Các tài liệu này có thể được tổ chức thành các thư mục, tương tự như các tệp trên máy tính của bạn. Mỗi tài liệu có thể có các trường khác nhau so với các tài liệu khác - ví dụ, nếu bạn đang lưu trữ dữ liệu IoT từ các phương tiện nông trại của bạn, một số có thể có các trường cho dữ liệu gia tốc và tốc độ, trong khi các tài liệu khác có thể có các trường cho nhiệt độ trong rơ-moóc. Nếu bạn thêm một loại xe tải mới, chẳng hạn như một loại có cân tích hợp để theo dõi trọng lượng hàng hóa, thì thiết bị IoT của bạn có thể thêm trường mới này và nó có thể được lưu trữ mà không cần thay đổi cơ sở dữ liệu.

Một số cơ sở dữ liệu NoSQL nổi tiếng bao gồm Azure CosmosDB, MongoDB và CouchDB.

✅ Nghiên cứu thêm: Đọc về một số cơ sở dữ liệu NoSQL này và khả năng của chúng.

Trong bài học này, bạn sẽ sử dụng lưu trữ NoSQL để lưu trữ dữ liệu IoT.

## Gửi dữ liệu GPS đến IoT Hub

Trong bài học trước, bạn đã thu thập dữ liệu GPS từ cảm biến GPS được kết nối với thiết bị IoT của bạn. Để lưu trữ dữ liệu IoT này trên đám mây, bạn cần gửi nó đến một dịch vụ IoT. Một lần nữa, bạn sẽ sử dụng Azure IoT Hub, cùng dịch vụ IoT trên đám mây mà bạn đã sử dụng trong dự án trước.

![Gửi dữ liệu GPS từ thiết bị IoT đến IoT Hub](../../../../../translated_images/vi/gps-telemetry-iot-hub.8115335d51cd2c12.webp)

### Nhiệm vụ - gửi dữ liệu GPS đến IoT Hub

1. Tạo một IoT Hub mới sử dụng gói miễn phí.

    > ⚠️ Bạn có thể tham khảo [hướng dẫn tạo IoT Hub từ dự án 2, bài học 4](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#create-an-iot-service-in-the-cloud) nếu cần.

    Hãy nhớ tạo một Nhóm Tài nguyên mới. Đặt tên Nhóm Tài nguyên mới là `gps-sensor`, và IoT Hub mới một tên duy nhất dựa trên `gps-sensor`, chẳng hạn như `gps-sensor-<tên của bạn>`.

    > 💁 Nếu bạn vẫn còn IoT Hub từ dự án trước, bạn có thể sử dụng lại nó. Hãy nhớ sử dụng tên của IoT Hub này và Nhóm Tài nguyên mà nó nằm trong khi tạo các dịch vụ khác.

1. Thêm một thiết bị mới vào IoT Hub. Gọi thiết bị này là `gps-sensor`. Lấy chuỗi kết nối cho thiết bị.

1. Cập nhật mã thiết bị của bạn để gửi dữ liệu GPS đến IoT Hub mới sử dụng chuỗi kết nối thiết bị từ bước trước.

    > ⚠️ Bạn có thể tham khảo [hướng dẫn kết nối thiết bị của bạn với IoT từ dự án 2, bài học 4](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#connect-your-device-to-the-iot-service) nếu cần.

1. Khi bạn gửi dữ liệu GPS, hãy làm điều đó dưới dạng JSON theo định dạng sau:

    ```json
    {
        "gps" :
        {
            "lat" : <latitude>,
            "lon" : <longitude>
        }
    }
    ```

1. Gửi dữ liệu GPS mỗi phút để không sử dụng hết hạn mức tin nhắn hàng ngày của bạn.

Nếu bạn đang sử dụng Wio Terminal, hãy nhớ thêm tất cả các thư viện cần thiết và đặt thời gian bằng máy chủ NTP. Mã của bạn cũng cần đảm bảo rằng nó đã đọc tất cả dữ liệu từ cổng nối tiếp trước khi gửi vị trí GPS, sử dụng mã hiện có từ bài học trước. Sử dụng mã sau để tạo tài liệu JSON:

```cpp
DynamicJsonDocument doc(1024);
doc["gps"]["lat"] = gps.location.lat();
doc["gps"]["lon"] = gps.location.lng();
```

Nếu bạn đang sử dụng thiết bị IoT ảo, hãy nhớ cài đặt tất cả các thư viện cần thiết bằng môi trường ảo.

Đối với cả Raspberry Pi và thiết bị IoT ảo, sử dụng mã hiện có từ bài học trước để lấy giá trị vĩ độ và kinh độ, sau đó gửi chúng theo định dạng JSON đúng với mã sau:

```python
message_json = { "gps" : { "lat":lat, "lon":lon } }
print("Sending telemetry", message_json)
message = Message(json.dumps(message_json))
```

> 💁 Bạn có thể tìm thấy mã này trong thư mục [code/wio-terminal](../../../../../3-transport/lessons/2-store-location-data/code/wio-terminal), [code/pi](../../../../../3-transport/lessons/2-store-location-data/code/pi) hoặc [code/virtual-device](../../../../../3-transport/lessons/2-store-location-data/code/virtual-device).

Chạy mã thiết bị của bạn và đảm bảo các tin nhắn đang được gửi vào IoT Hub bằng lệnh CLI `az iot hub monitor-events`.

## Đường dẫn nóng, ấm và lạnh

Dữ liệu chảy từ thiết bị IoT đến đám mây không phải lúc nào cũng được xử lý ngay lập tức. Một số dữ liệu cần được xử lý theo thời gian thực, dữ liệu khác có thể được xử lý sau một thời gian ngắn, và dữ liệu khác có thể được xử lý sau một thời gian dài. Luồng dữ liệu đến các dịch vụ khác nhau xử lý dữ liệu tại các thời điểm khác nhau được gọi là đường dẫn nóng, ấm và lạnh.

### Đường dẫn nóng

Đường dẫn nóng đề cập đến dữ liệu cần được xử lý theo thời gian thực hoặc gần thời gian thực. Bạn sẽ sử dụng dữ liệu đường dẫn nóng cho các cảnh báo, chẳng hạn như nhận cảnh báo rằng một phương tiện đang đến gần kho, hoặc rằng nhiệt độ trong xe tải đông lạnh quá cao.

Để sử dụng dữ liệu đường dẫn nóng, mã của bạn sẽ phản hồi các sự kiện ngay khi chúng được nhận bởi các dịch vụ đám mây của bạn.

### Đường dẫn ấm

Đường dẫn ấm đề cập đến dữ liệu có thể được xử lý sau một thời gian ngắn sau khi được nhận, ví dụ như để báo cáo hoặc phân tích ngắn hạn. Bạn sẽ sử dụng dữ liệu đường dẫn ấm cho các báo cáo hàng ngày về quãng đường xe chạy, sử dụng dữ liệu thu thập được vào ngày hôm trước.

Dữ liệu đường dẫn ấm được lưu trữ ngay khi nó được nhận bởi dịch vụ đám mây trong một loại lưu trữ nào đó có thể được truy cập nhanh chóng.

### Đường dẫn lạnh

Đường dẫn lạnh đề cập đến dữ liệu lịch sử, lưu trữ dữ liệu trong dài hạn để được xử lý khi cần. Ví dụ, bạn có thể sử dụng đường dẫn lạnh để lấy các báo cáo quãng đường hàng năm cho các phương tiện, hoặc chạy phân tích trên các tuyến đường để tìm tuyến đường tối ưu nhất nhằm giảm chi phí nhiên liệu.

Dữ liệu đường dẫn lạnh được lưu trữ trong các kho dữ liệu - cơ sở dữ liệu được thiết kế để lưu trữ lượng lớn dữ liệu không thay đổi và có thể được truy vấn nhanh chóng và dễ dàng. Bạn thường sẽ có một công việc định kỳ trong ứng dụng đám mây của mình chạy vào một thời điểm cố định mỗi ngày, tuần hoặc tháng để chuyển dữ liệu từ lưu trữ đường dẫn ấm vào kho dữ liệu.

✅ Hãy nghĩ về dữ liệu bạn đã thu thập cho đến nay trong các bài học này. Nó là dữ liệu đường dẫn nóng, ấm hay lạnh?

## Xử lý sự kiện GPS bằng mã không máy chủ

Khi dữ liệu đang chảy vào IoT Hub, bạn có thể viết một số mã không máy chủ để lắng nghe các sự kiện được xuất bản đến điểm cuối tương thích Event-Hub. Đây là đường dẫn ấm - dữ liệu này sẽ được lưu trữ và sử dụng trong bài học tiếp theo để báo cáo về hành trình.

![Gửi dữ liệu GPS từ thiết bị IoT đến IoT Hub, sau đó đến Azure Functions thông qua trình kích hoạt event hub](../../../../../translated_images/vi/gps-telemetry-iot-hub-functions.24d3fa5592455e9f.webp)

### Nhiệm vụ - xử lý sự kiện GPS bằng mã không máy chủ

1. Tạo một ứng dụng Azure Functions sử dụng CLI Azure Functions. Sử dụng runtime Python, và tạo nó trong một thư mục có tên `gps-trigger`, và sử dụng cùng tên cho tên dự án Functions App. Hãy chắc chắn rằng bạn tạo một môi trường ảo để sử dụng cho việc này.
> ⚠️ Bạn có thể tham khảo [hướng dẫn tạo Dự án Azure Functions từ dự án 2, bài học 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-a-serverless-application) nếu cần.
1. Thêm một trình kích hoạt sự kiện IoT Hub sử dụng endpoint tương thích Event Hub của IoT Hub.

    > ⚠️ Bạn có thể tham khảo [hướng dẫn tạo trình kích hoạt sự kiện IoT Hub từ dự án 2, bài học 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger) nếu cần.

1. Đặt chuỗi kết nối endpoint tương thích Event Hub trong tệp `local.settings.json`, và sử dụng khóa cho mục nhập đó trong tệp `function.json`.

1. Sử dụng ứng dụng Azurite làm trình giả lập lưu trữ cục bộ.

1. Chạy ứng dụng Functions của bạn để đảm bảo nó nhận được các sự kiện từ thiết bị GPS của bạn. Đảm bảo thiết bị IoT của bạn cũng đang chạy và gửi dữ liệu GPS.

    ```output
    Python EventHub trigger processed an event: {"gps": {"lat": 47.73481, "lon": -122.25701}}
    ```

## Tài khoản lưu trữ Azure

![Logo Azure Storage](../../../../../translated_images/vi/azure-storage-logo.605c0f602c640d48.webp)

Azure Storage Accounts là một dịch vụ lưu trữ đa năng có thể lưu trữ dữ liệu theo nhiều cách khác nhau. Bạn có thể lưu trữ dữ liệu dưới dạng blob, trong hàng đợi, trong bảng, hoặc dưới dạng tệp, và tất cả cùng một lúc.

### Lưu trữ Blob

Từ *Blob* có nghĩa là các đối tượng nhị phân lớn, nhưng đã trở thành thuật ngữ cho bất kỳ dữ liệu không có cấu trúc nào. Bạn có thể lưu trữ bất kỳ dữ liệu nào trong lưu trữ blob, từ các tài liệu JSON chứa dữ liệu IoT, đến các tệp hình ảnh và video. Lưu trữ blob có khái niệm *container*, là các thùng được đặt tên để bạn lưu trữ dữ liệu, tương tự như các bảng trong cơ sở dữ liệu quan hệ. Các container này có thể có một hoặc nhiều thư mục để lưu trữ blob, và mỗi thư mục có thể chứa các thư mục khác, tương tự như cách các tệp được lưu trữ trên ổ cứng máy tính của bạn.

Bạn sẽ sử dụng lưu trữ blob trong bài học này để lưu trữ dữ liệu IoT.

✅ Nghiên cứu thêm: Đọc về [Azure Blob Storage](https://docs.microsoft.com/azure/storage/blobs/storage-blobs-overview?WT.mc_id=academic-17441-jabenn)

### Lưu trữ bảng

Lưu trữ bảng cho phép bạn lưu trữ dữ liệu bán cấu trúc. Lưu trữ bảng thực chất là một cơ sở dữ liệu NoSQL, vì vậy không yêu cầu một tập hợp bảng được định nghĩa trước, nhưng nó được thiết kế để lưu trữ dữ liệu trong một hoặc nhiều bảng, với các khóa duy nhất để xác định từng hàng.

✅ Nghiên cứu thêm: Đọc về [Azure Table Storage](https://docs.microsoft.com/azure/storage/tables/table-storage-overview?WT.mc_id=academic-17441-jabenn)

### Lưu trữ hàng đợi

Lưu trữ hàng đợi cho phép bạn lưu trữ các tin nhắn có kích thước lên đến 64KB trong một hàng đợi. Bạn có thể thêm tin nhắn vào cuối hàng đợi và đọc chúng từ đầu hàng đợi. Hàng đợi lưu trữ tin nhắn vô thời hạn miễn là vẫn còn không gian lưu trữ, cho phép tin nhắn được lưu trữ lâu dài và đọc khi cần. Ví dụ, nếu bạn muốn chạy một công việc hàng tháng để xử lý dữ liệu GPS, bạn có thể thêm nó vào hàng đợi mỗi ngày trong một tháng, sau đó vào cuối tháng xử lý tất cả các tin nhắn từ hàng đợi.

✅ Nghiên cứu thêm: Đọc về [Azure Queue Storage](https://docs.microsoft.com/azure/storage/queues/storage-queues-introduction?WT.mc_id=academic-17441-jabenn)

### Lưu trữ tệp

Lưu trữ tệp là lưu trữ các tệp trên đám mây, và bất kỳ ứng dụng hoặc thiết bị nào cũng có thể kết nối bằng các giao thức tiêu chuẩn của ngành. Bạn có thể ghi tệp vào lưu trữ tệp, sau đó gắn nó như một ổ đĩa trên PC hoặc Mac của bạn.

✅ Nghiên cứu thêm: Đọc về [Azure File Storage](https://docs.microsoft.com/azure/storage/files/storage-files-introduction?WT.mc_id=academic-17441-jabenn)

## Kết nối mã serverless của bạn với lưu trữ

Ứng dụng Functions của bạn bây giờ cần kết nối với lưu trữ blob để lưu trữ các tin nhắn từ IoT Hub. Có 2 cách để làm điều này:

* Bên trong mã function, kết nối với lưu trữ blob bằng SDK Python của blob storage và ghi dữ liệu dưới dạng blob.
* Sử dụng một ràng buộc đầu ra function để ràng buộc giá trị trả về của function với lưu trữ blob và tự động lưu blob.

Trong bài học này, bạn sẽ sử dụng SDK Python để xem cách tương tác với lưu trữ blob.

![Gửi dữ liệu GPS từ thiết bị IoT đến IoT Hub, sau đó đến Azure Functions qua trình kích hoạt event hub, rồi lưu vào lưu trữ blob](../../../../../translated_images/vi/save-telemetry-to-storage-from-functions.ed3b1820980097f1.webp)

Dữ liệu sẽ được lưu dưới dạng một blob JSON với định dạng sau:

```json
{
    "device_id": <device_id>,
    "timestamp" : <time>,
    "gps" :
    {
        "lat" : <latitude>,
        "lon" : <longitude>
    }
}
```

### Nhiệm vụ - kết nối mã serverless của bạn với lưu trữ

1. Tạo một tài khoản lưu trữ Azure. Đặt tên nó như `gps<tên của bạn>`.

    > ⚠️ Bạn có thể tham khảo [hướng dẫn tạo tài khoản lưu trữ từ dự án 2, bài học 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources) nếu cần.

    Nếu bạn vẫn còn một tài khoản lưu trữ từ dự án trước, bạn có thể tái sử dụng nó.

    > 💁 Bạn sẽ có thể sử dụng cùng một tài khoản lưu trữ để triển khai ứng dụng Azure Functions của bạn sau trong bài học này.

1. Chạy lệnh sau để lấy chuỗi kết nối cho tài khoản lưu trữ:

    ```sh
    az storage account show-connection-string --output table \
                                              --name <storage_name>
    ```

    Thay `<storage_name>` bằng tên của tài khoản lưu trữ bạn đã tạo ở bước trước.

1. Thêm một mục nhập mới vào tệp `local.settings.json` cho chuỗi kết nối tài khoản lưu trữ của bạn, sử dụng giá trị từ bước trước. Đặt tên nó là `STORAGE_CONNECTION_STRING`.

1. Thêm nội dung sau vào tệp `requirements.txt` để cài đặt các gói Pip của Azure storage:

    ```sh
    azure-storage-blob
    ```

    Cài đặt các gói từ tệp này trong môi trường ảo của bạn.

    > Nếu bạn gặp lỗi, hãy nâng cấp phiên bản Pip trong môi trường ảo của bạn lên phiên bản mới nhất bằng lệnh sau, sau đó thử lại:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Trong tệp `__init__.py` cho `iot-hub-trigger`, thêm các câu lệnh import sau:

    ```python
    import json
    import os
    import uuid
    from azure.storage.blob import BlobServiceClient, PublicAccess
    ```

    Module hệ thống `json` sẽ được sử dụng để đọc và ghi JSON, module hệ thống `os` sẽ được sử dụng để đọc chuỗi kết nối, module hệ thống `uuid` sẽ được sử dụng để tạo ID duy nhất cho dữ liệu GPS.

    Gói `azure.storage.blob` chứa SDK Python để làm việc với lưu trữ blob.

1. Trước phương thức `main`, thêm hàm trợ giúp sau:

    ```python
    def get_or_create_container(name):
        connection_str = os.environ['STORAGE_CONNECTION_STRING']
        blob_service_client = BlobServiceClient.from_connection_string(connection_str)
    
        for container in blob_service_client.list_containers():
            if container.name == name:
                return blob_service_client.get_container_client(container.name)
        
        return blob_service_client.create_container(name, public_access=PublicAccess.Container)
    ```

    SDK blob Python không có phương thức trợ giúp để tạo container nếu nó không tồn tại. Mã này sẽ tải chuỗi kết nối từ tệp `local.settings.json` (hoặc Application Settings khi được triển khai lên đám mây), sau đó tạo một lớp `BlobServiceClient` từ đó để tương tác với tài khoản lưu trữ blob. Nó sau đó lặp qua tất cả các container của tài khoản lưu trữ blob, tìm kiếm một container với tên được cung cấp - nếu tìm thấy, nó sẽ trả về một lớp `ContainerClient` có thể tương tác với container để tạo blob. Nếu không tìm thấy, container sẽ được tạo và client cho container mới sẽ được trả về.

    Khi container mới được tạo, quyền truy cập công khai được cấp để truy vấn các blob trong container. Điều này sẽ được sử dụng trong bài học tiếp theo để hiển thị dữ liệu GPS trên bản đồ.

1. Không giống như với độ ẩm đất, với mã này chúng ta muốn lưu trữ mọi sự kiện, vì vậy thêm mã sau bên trong vòng lặp `for event in events:` trong hàm `main`, bên dưới câu lệnh `logging`:

    ```python
    device_id = event.iothub_metadata['connection-device-id']
    blob_name = f'{device_id}/{str(uuid.uuid1())}.json'
    ```

    Mã này lấy ID thiết bị từ metadata của sự kiện, sau đó sử dụng nó để tạo tên blob. Các blob có thể được lưu trữ trong các thư mục, và ID thiết bị sẽ được sử dụng làm tên thư mục, vì vậy mỗi thiết bị sẽ có tất cả các sự kiện GPS của nó trong một thư mục. Tên blob là thư mục này, theo sau là tên tài liệu, được phân tách bằng dấu gạch chéo, tương tự như các đường dẫn trên Linux và macOS (cũng tương tự trên Windows, nhưng Windows sử dụng dấu gạch chéo ngược). Tên tài liệu là một ID duy nhất được tạo bằng module `uuid` của Python, với loại tệp là `json`.

    Ví dụ, đối với ID thiết bị `gps-sensor`, tên blob có thể là `gps-sensor/a9487ac2-b9cf-11eb-b5cd-1e00621e3648.json`.

1. Thêm mã sau bên dưới đoạn này:

    ```python
    container_client = get_or_create_container('gps-data')
    blob = container_client.get_blob_client(blob_name)
    ```

    Mã này lấy client container bằng cách sử dụng hàm trợ giúp `get_or_create_container`, và sau đó lấy một đối tượng client blob bằng cách sử dụng tên blob. Các client blob này có thể tham chiếu đến các blob hiện có, hoặc như trong trường hợp này, đến blob mới.

1. Thêm mã sau sau đoạn này:

    ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    blob_body = {
        'device_id' : device_id,
        'timestamp' : event.iothub_metadata['enqueuedtime'],
        'gps': event_body['gps']
    }
    ```

    Mã này xây dựng nội dung của blob sẽ được ghi vào lưu trữ blob. Đây là một tài liệu JSON chứa ID thiết bị, thời gian mà dữ liệu được gửi đến IoT Hub, và tọa độ GPS từ dữ liệu.

    > 💁 Điều quan trọng là sử dụng thời gian hàng đợi của tin nhắn thay vì thời gian hiện tại để lấy thời gian mà tin nhắn được gửi. Tin nhắn có thể nằm trên hub một thời gian trước khi được xử lý nếu ứng dụng Functions không chạy.

1. Thêm đoạn mã sau bên dưới:

    ```python
    logging.info(f'Writing blob to {blob_name} - {blob_body}')
    blob.upload_blob(json.dumps(blob_body).encode('utf-8'))
    ```

    Mã này ghi log rằng một blob sắp được ghi với các chi tiết của nó, sau đó tải nội dung blob làm nội dung của blob mới.

1. Chạy ứng dụng Functions. Bạn sẽ thấy các blob được ghi cho tất cả các sự kiện GPS trong đầu ra:

    ```output
    [2021-05-21T01:31:14.325Z] Python EventHub trigger processed an event: {"gps": {"lat": 47.73092, "lon": -122.26206}}
    ...
    [2021-05-21T01:31:14.351Z] Writing blob to gps-sensor/4b6089fe-ba8d-11eb-bc7b-1e00621e3648.json - {'device_id': 'gps-sensor', 'timestamp': '2021-05-21T00:57:53.878Z', 'gps': {'lat': 47.73092, 'lon': -122.26206}}
    ```

    > 💁 Đảm bảo bạn không chạy trình giám sát sự kiện IoT Hub cùng lúc.

> 💁 Bạn có thể tìm thấy mã này trong thư mục [code/functions](../../../../../3-transport/lessons/2-store-location-data/code/functions).

### Nhiệm vụ - xác minh các blob đã tải lên

1. Để xem các blob đã tạo, bạn có thể sử dụng [Azure Storage Explorer](https://azure.microsoft.com/features/storage-explorer/?WT.mc_id=academic-17441-jabenn), một công cụ miễn phí cho phép bạn xem và quản lý các tài khoản lưu trữ của mình, hoặc từ CLI.

    1. Để sử dụng CLI, trước tiên bạn cần một khóa tài khoản. Chạy lệnh sau để lấy khóa này:

        ```sh
        az storage account keys list --output table \
                                     --account-name <storage_name>
        ```

        Thay `<storage_name>` bằng tên của tài khoản lưu trữ.

        Sao chép giá trị của `key1`.

    1. Chạy lệnh sau để liệt kê các blob trong container:

        ```sh
        az storage blob list --container-name gps-data \
                             --output table \
                             --account-name <storage_name> \
                             --account-key <key1>
        ```

        Thay `<storage_name>` bằng tên của tài khoản lưu trữ, và `<key1>` bằng giá trị của `key1` bạn đã sao chép ở bước trước.

        Điều này sẽ liệt kê tất cả các blob trong container:

        ```output
        Name                                                  Blob Type    Blob Tier    Length    Content Type              Last Modified              Snapshot
        ----------------------------------------------------  -----------  -----------  --------  ------------------------  -------------------------  ----------
        gps-sensor/1810d55e-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:27+00:00
        gps-sensor/18293e46-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1844549c-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1894d714-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        ```

    1. Tải xuống một trong các blob bằng lệnh sau:

        ```sh
        az storage blob download --container-name gps-data \
                                 --account-name <storage_name> \
                                 --account-key <key1> \
                                 --name <blob_name> \
                                 --file <file_name>
        ```

        Thay `<storage_name>` bằng tên của tài khoản lưu trữ, và `<key1>` bằng giá trị của `key1` bạn đã sao chép ở bước trước.

        Thay `<blob_name>` bằng tên đầy đủ từ cột `Name` của đầu ra bước trước, bao gồm cả tên thư mục. Thay `<file_name>` bằng tên của một tệp cục bộ để lưu blob vào.

    Sau khi tải xuống, bạn có thể mở tệp JSON trong VS Code, và bạn sẽ thấy blob chứa chi tiết vị trí GPS:

    ```json
    {"device_id": "gps-sensor", "timestamp": "2021-05-21T00:57:53.878Z", "gps": {"lat": 47.73092, "lon": -122.26206}}
    ```

### Nhiệm vụ - triển khai ứng dụng Functions của bạn lên đám mây

Bây giờ ứng dụng Functions của bạn đã hoạt động, bạn có thể triển khai nó lên đám mây.

1. Tạo một ứng dụng Azure Functions mới, sử dụng tài khoản lưu trữ bạn đã tạo trước đó. Đặt tên ứng dụng này như `gps-sensor-` và thêm một định danh duy nhất vào cuối, như một số từ ngẫu nhiên hoặc tên của bạn.

    > ⚠️ Bạn có thể tham khảo [hướng dẫn tạo ứng dụng Functions từ dự án 2, bài học 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources) nếu cần.

1. Tải lên các giá trị `IOT_HUB_CONNECTION_STRING` và `STORAGE_CONNECTION_STRING` vào Application Settings.

    > ⚠️ Bạn có thể tham khảo [hướng dẫn tải lên Application Settings từ dự án 2, bài học 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings) nếu cần.

1. Triển khai ứng dụng Functions cục bộ của bạn lên đám mây.
> ⚠️ Bạn có thể tham khảo [hướng dẫn triển khai ứng dụng Functions từ dự án 2, bài học 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud) nếu cần.
---

## 🚀 Thử thách

Dữ liệu GPS không hoàn toàn chính xác, và các vị trí được phát hiện có thể lệch vài mét, thậm chí nhiều hơn, đặc biệt là trong các đường hầm và khu vực có nhiều tòa nhà cao tầng.

Hãy suy nghĩ về cách hệ thống định vị vệ tinh có thể khắc phục điều này? Dữ liệu nào mà hệ thống định vị của bạn có thể sử dụng để đưa ra dự đoán tốt hơn về vị trí của bạn?

## Câu hỏi sau bài giảng

[Câu hỏi sau bài giảng](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/24)

## Ôn tập & Tự học

* Đọc về dữ liệu có cấu trúc trên [trang mô hình dữ liệu của Wikipedia](https://wikipedia.org/wiki/Data_model)
* Đọc về dữ liệu bán cấu trúc trên [trang dữ liệu bán cấu trúc của Wikipedia](https://wikipedia.org/wiki/Semi-structured_data)
* Đọc về dữ liệu không cấu trúc trên [trang dữ liệu không cấu trúc của Wikipedia](https://wikipedia.org/wiki/Unstructured_data)
* Tìm hiểu thêm về Azure Storage và các loại lưu trữ khác nhau trong [tài liệu Azure Storage](https://docs.microsoft.com/azure/storage/?WT.mc_id=academic-17441-jabenn)

## Bài tập

[Khám phá các ràng buộc hàm](assignment.md)

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.