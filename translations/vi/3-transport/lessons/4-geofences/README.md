<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "078ae664c7b686bf069545e9a5fc95b2",
  "translation_date": "2025-08-27T23:33:58+00:00",
  "source_file": "3-transport/lessons/4-geofences/README.md",
  "language_code": "vi"
}
-->
# Hàng rào địa lý

![Tóm tắt bài học bằng hình vẽ](../../../../../translated_images/lesson-14.63980c5150ae3c153e770fb71d044c1845dce79248d86bed9fc525adf3ede73c.vi.jpg)

> Hình vẽ minh họa bởi [Nitya Narasimhan](https://github.com/nitya). Nhấp vào hình để xem phiên bản lớn hơn.

Video này cung cấp tổng quan về hàng rào địa lý và cách sử dụng chúng trong Azure Maps, các chủ đề sẽ được đề cập trong bài học này:

[![Hàng rào địa lý với Azure Maps từ chương trình Microsoft Developer IoT](https://img.youtube.com/vi/nsrgYhaYNVY/0.jpg)](https://www.youtube.com/watch?v=nsrgYhaYNVY)

> 🎥 Nhấp vào hình trên để xem video

## Câu hỏi trước bài học

[Câu hỏi trước bài học](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/27)

## Giới thiệu

Trong 3 bài học trước, bạn đã sử dụng IoT để định vị các xe tải chở nông sản từ trang trại của bạn đến trung tâm chế biến. Bạn đã thu thập dữ liệu GPS, gửi nó lên đám mây để lưu trữ và hiển thị trên bản đồ. Bước tiếp theo để tăng hiệu quả chuỗi cung ứng của bạn là nhận thông báo khi xe tải sắp đến trung tâm chế biến, để đội ngũ cần thiết có thể chuẩn bị xe nâng và các thiết bị khác ngay khi xe đến. Bằng cách này, họ có thể dỡ hàng nhanh chóng, và bạn không phải trả tiền cho xe tải và tài xế để chờ đợi.

Trong bài học này, bạn sẽ tìm hiểu về hàng rào địa lý - các vùng địa lý được định nghĩa như một khu vực trong phạm vi lái xe 2km từ trung tâm chế biến, và cách kiểm tra xem tọa độ GPS nằm trong hay ngoài hàng rào địa lý, để bạn có thể biết liệu cảm biến GPS của bạn đã đến hay rời khỏi khu vực.

Trong bài học này, chúng ta sẽ đề cập:

* [Hàng rào địa lý là gì](../../../../../3-transport/lessons/4-geofences)
* [Định nghĩa hàng rào địa lý](../../../../../3-transport/lessons/4-geofences)
* [Kiểm tra điểm so với hàng rào địa lý](../../../../../3-transport/lessons/4-geofences)
* [Sử dụng hàng rào địa lý từ mã không máy chủ](../../../../../3-transport/lessons/4-geofences)

> 🗑 Đây là bài học cuối cùng trong dự án này, vì vậy sau khi hoàn thành bài học và bài tập, đừng quên dọn dẹp các dịch vụ đám mây của bạn. Bạn sẽ cần các dịch vụ để hoàn thành bài tập, vì vậy hãy đảm bảo hoàn thành trước.
>
> Tham khảo [hướng dẫn dọn dẹp dự án của bạn](../../../clean-up.md) nếu cần hướng dẫn cách thực hiện.

## Hàng rào địa lý là gì

Hàng rào địa lý là một ranh giới ảo cho một khu vực địa lý thực tế. Hàng rào địa lý có thể là các vòng tròn được định nghĩa bằng một điểm và bán kính (ví dụ: một vòng tròn rộng 100m xung quanh một tòa nhà), hoặc một đa giác bao phủ một khu vực như khu vực trường học, giới hạn thành phố, hoặc khuôn viên trường đại học hoặc văn phòng.

![Một số ví dụ về hàng rào địa lý hiển thị hàng rào hình tròn xung quanh cửa hàng công ty Microsoft, và hàng rào hình đa giác xung quanh khuôn viên phía tây của Microsoft](../../../../../translated_images/geofence-examples.172fbc534665769f6e1a1ddcf75e3b25183cd10354c80cc603ba44b635390e1a.vi.png)

> 💁 Bạn có thể đã sử dụng hàng rào địa lý mà không biết. Nếu bạn đã đặt lời nhắc bằng ứng dụng nhắc nhở iOS hoặc Google Keep dựa trên vị trí, bạn đã sử dụng hàng rào địa lý. Các ứng dụng này sẽ thiết lập một hàng rào địa lý dựa trên vị trí được cung cấp và thông báo cho bạn khi điện thoại của bạn đi vào hàng rào địa lý.

Có nhiều lý do tại sao bạn muốn biết rằng một phương tiện đang ở trong hay ngoài hàng rào địa lý:

* Chuẩn bị dỡ hàng - nhận thông báo rằng một phương tiện đã đến nơi cho phép đội ngũ chuẩn bị dỡ hàng, giảm thời gian chờ đợi của phương tiện. Điều này có thể cho phép tài xế thực hiện nhiều chuyến giao hàng hơn trong một ngày với ít thời gian chờ đợi hơn.
* Tuân thủ thuế - một số quốc gia, như New Zealand, tính thuế đường bộ cho các phương tiện chạy bằng dầu diesel dựa trên trọng lượng phương tiện khi lái trên đường công cộng. Sử dụng hàng rào địa lý cho phép bạn theo dõi quãng đường đã đi trên đường công cộng so với đường riêng tại các địa điểm như trang trại hoặc khu vực khai thác gỗ.
* Giám sát trộm cắp - nếu một phương tiện chỉ nên ở trong một khu vực nhất định như trên trang trại, và nó rời khỏi hàng rào địa lý, có thể nó đã bị đánh cắp.
* Tuân thủ vị trí - một số phần của công trường, trang trại hoặc nhà máy có thể bị cấm đối với một số phương tiện, chẳng hạn như giữ các phương tiện chở phân bón nhân tạo và thuốc trừ sâu tránh xa các cánh đồng trồng sản phẩm hữu cơ. Nếu một hàng rào địa lý bị xâm nhập, thì phương tiện đang vi phạm và tài xế có thể được thông báo.

✅ Bạn có thể nghĩ ra các cách sử dụng khác cho hàng rào địa lý không?

Azure Maps, dịch vụ bạn đã sử dụng trong bài học trước để hiển thị dữ liệu GPS, cho phép bạn định nghĩa hàng rào địa lý, sau đó kiểm tra xem một điểm có nằm trong hay ngoài hàng rào địa lý.

## Định nghĩa hàng rào địa lý

Hàng rào địa lý được định nghĩa bằng GeoJSON, giống như các điểm đã được thêm vào bản đồ trong bài học trước. Trong trường hợp này, thay vì là một `FeatureCollection` của các giá trị `Point`, nó là một `FeatureCollection` chứa một `Polygon`.

```json
{
   "type": "FeatureCollection",
   "features": [
     {
       "type": "Feature",
       "geometry": {
         "type": "Polygon",
         "coordinates": [
           [
             [
               -122.13393688201903,
               47.63829579223815
             ],
             [
               -122.13389128446579,
               47.63782047131512
             ],
             [
               -122.13240802288054,
               47.63783312249837
             ],
             [
               -122.13238388299942,
               47.63829037035086
             ],
             [
               -122.13393688201903,
               47.63829579223815
             ]
           ]
         ]
       },
       "properties": {
         "geometryId": "1"
       }
     }
   ]
}
```

Mỗi điểm trên đa giác được định nghĩa là một cặp kinh độ, vĩ độ trong một mảng, và các điểm này nằm trong một mảng được đặt làm `coordinates`. Trong một `Point` ở bài học trước, `coordinates` là một mảng chứa 2 giá trị, vĩ độ và kinh độ, đối với một `Polygon` nó là một mảng của các mảng chứa 2 giá trị, kinh độ, vĩ độ.

> 💁 Nhớ rằng, GeoJSON sử dụng `kinh độ, vĩ độ` cho các điểm, không phải `vĩ độ, kinh độ`

Mảng tọa độ đa giác luôn có 1 mục nhập nhiều hơn số điểm trên đa giác, với mục nhập cuối cùng giống như mục đầu tiên, đóng đa giác. Ví dụ, đối với một hình chữ nhật sẽ có 5 điểm.

![Một hình chữ nhật với các tọa độ](../../../../../translated_images/polygon-points.302193da381cb415.vi.png)

Trong hình trên, có một hình chữ nhật. Tọa độ đa giác bắt đầu từ góc trên bên trái tại 47,-122, sau đó di chuyển sang phải đến 47,-121, sau đó xuống dưới đến 46,-121, sau đó sang trái đến 46, -122, sau đó quay lại điểm bắt đầu tại 47, -122. Điều này tạo ra đa giác với 5 điểm - góc trên bên trái, góc trên bên phải, góc dưới bên phải, góc dưới bên trái, sau đó góc trên bên trái để đóng lại.

✅ Hãy thử tạo một đa giác GeoJSON xung quanh nhà hoặc trường học của bạn. Sử dụng một công cụ như [GeoJSON.io](https://geojson.io/).

### Nhiệm vụ - định nghĩa hàng rào địa lý

Để sử dụng hàng rào địa lý trong Azure Maps, trước tiên nó phải được tải lên tài khoản Azure Maps của bạn. Sau khi tải lên, bạn sẽ nhận được một ID duy nhất mà bạn có thể sử dụng để kiểm tra một điểm so với hàng rào địa lý. Để tải lên hàng rào địa lý vào Azure Maps, bạn cần sử dụng API web của Maps. Bạn có thể gọi API web Azure Maps bằng một công cụ gọi là [curl](https://curl.se).

> 🎓 Curl là một công cụ dòng lệnh để thực hiện các yêu cầu đối với các điểm cuối web

1. Nếu bạn đang sử dụng Linux, macOS, hoặc phiên bản gần đây của Windows 10, bạn có thể đã cài đặt curl. Chạy lệnh sau từ terminal hoặc dòng lệnh để kiểm tra:

    ```sh
    curl --version
    ```

    Nếu bạn không thấy thông tin phiên bản của curl, bạn sẽ cần cài đặt nó từ [trang tải xuống curl](https://curl.se/download.html).

    > 💁 Nếu bạn có kinh nghiệm với Postman, bạn có thể sử dụng nó thay thế nếu muốn.

1. Tạo một tệp GeoJSON chứa một đa giác. Bạn sẽ kiểm tra điều này bằng cảm biến GPS của mình, vì vậy hãy tạo một đa giác xung quanh vị trí hiện tại của bạn. Bạn có thể tạo thủ công bằng cách chỉnh sửa ví dụ GeoJSON được cung cấp ở trên, hoặc sử dụng một công cụ như [GeoJSON.io](https://geojson.io/).

    GeoJSON cần chứa một `FeatureCollection`, chứa một `Feature` với một `geometry` kiểu `Polygon`.

    Bạn **PHẢI** thêm một phần tử `properties` ở cùng cấp với phần tử `geometry`, và phần tử này phải chứa một `geometryId`:

    ```json
    "properties": {
        "geometryId": "1"
    }
    ```

    Nếu bạn sử dụng [GeoJSON.io](https://geojson.io/), bạn sẽ phải thêm mục này vào phần tử `properties` trống, hoặc sau khi tải xuống tệp JSON, hoặc trong trình chỉnh sửa JSON trong ứng dụng.

    `geometryId` này phải là duy nhất trong tệp này. Bạn có thể tải lên nhiều hàng rào địa lý dưới dạng nhiều `Features` trong `FeatureCollection` trong cùng một tệp GeoJSON, miễn là mỗi cái có một `geometryId` khác nhau. Các đa giác có thể có cùng `geometryId` nếu chúng được tải lên từ một tệp khác vào thời điểm khác.

1. Lưu tệp này dưới tên `geofence.json`, và điều hướng đến nơi nó được lưu trong terminal hoặc console của bạn.

1. Chạy lệnh curl sau để tạo hàng rào địa lý:

    ```sh
    curl --request POST 'https://atlas.microsoft.com/mapData/upload?api-version=1.0&dataFormat=geojson&subscription-key=<subscription_key>' \
         --header 'Content-Type: application/json' \
         --include \
         --data @geofence.json
    ```

    Thay `<subscription_key>` trong URL bằng khóa API cho tài khoản Azure Maps của bạn.

    URL được sử dụng để tải lên dữ liệu bản đồ thông qua API `https://atlas.microsoft.com/mapData/upload`. Lệnh gọi bao gồm tham số `api-version` để chỉ định API Azure Maps nào sẽ sử dụng, điều này cho phép API thay đổi theo thời gian nhưng vẫn duy trì khả năng tương thích ngược. Định dạng dữ liệu được tải lên được đặt là `geojson`.

    Điều này sẽ chạy yêu cầu POST đến API tải lên và trả về danh sách các tiêu đề phản hồi bao gồm một tiêu đề gọi là `location`.

    ```output
    content-type: application/json
    location: https://us.atlas.microsoft.com/mapData/operations/1560ced6-3a80-46f2-84b2-5b1531820eab?api-version=1.0
    x-ms-azuremaps-region: West US 2
    x-content-type-options: nosniff
    strict-transport-security: max-age=31536000; includeSubDomains
    x-cache: CONFIG_NOCACHE
    date: Sat, 22 May 2021 21:34:57 GMT
    content-length: 0
    ```

    > 🎓 Khi gọi một điểm cuối web, bạn có thể truyền các tham số vào lệnh gọi bằng cách thêm `?` theo sau là các cặp khóa giá trị dưới dạng `key=value`, tách các cặp khóa giá trị bằng `&`.

1. Azure Maps không xử lý điều này ngay lập tức, vì vậy bạn sẽ cần kiểm tra để xem yêu cầu tải lên đã hoàn thành chưa bằng cách sử dụng URL được cung cấp trong tiêu đề `location`. Thực hiện yêu cầu GET đến vị trí này để xem trạng thái. Bạn sẽ cần thêm khóa đăng ký của mình vào cuối URL `location` bằng cách thêm `&subscription-key=<subscription_key>` vào cuối, thay `<subscription_key>` bằng khóa API cho tài khoản Azure Maps của bạn. Chạy lệnh sau:

    ```sh
    curl --request GET '<location>&subscription-key=<subscription_key>'
    ```

    Thay `<location>` bằng giá trị của tiêu đề `location`, và `<subscription_key>` bằng khóa API cho tài khoản Azure Maps của bạn.

1. Kiểm tra giá trị của `status` trong phản hồi. Nếu nó không phải là `Succeeded`, hãy đợi một phút và thử lại.

1. Khi trạng thái trả về là `Succeeded`, hãy xem `resourceLocation` từ phản hồi. Điều này chứa thông tin về ID duy nhất (được gọi là UDID) cho đối tượng GeoJSON. UDID là giá trị sau `metadata/`, và không bao gồm `api-version`. Ví dụ, nếu `resourceLocation` là:

    ```json
    {
      "resourceLocation": "https://us.atlas.microsoft.com/mapData/metadata/7c3776eb-da87-4c52-ae83-caadf980323a?api-version=1.0"
    }
    ```

    Thì UDID sẽ là `7c3776eb-da87-4c52-ae83-caadf980323a`.

    Lưu một bản sao của UDID này vì bạn sẽ cần nó để kiểm tra hàng rào địa lý.

## Kiểm tra điểm so với hàng rào địa lý

Sau khi đa giác đã được tải lên Azure Maps, bạn có thể kiểm tra một điểm để xem nó có nằm trong hay ngoài hàng rào địa lý. Bạn thực hiện điều này bằng cách thực hiện một yêu cầu API web, truyền vào UDID của hàng rào địa lý, và vĩ độ và kinh độ của điểm cần kiểm tra.

Khi bạn thực hiện yêu cầu này, bạn cũng có thể truyền một giá trị gọi là `searchBuffer`. Giá trị này cho API Maps biết mức độ chính xác khi trả về kết quả. Lý do cho điều này là GPS không hoàn toàn chính xác, và đôi khi vị trí có thể lệch vài mét hoặc hơn. Mặc định cho search buffer là 50m, nhưng bạn có thể đặt giá trị từ 0m đến 500m.

Khi kết quả được trả về từ lệnh gọi API, một trong các phần của kết quả là `distance` được đo đến điểm gần nhất trên cạnh của hàng rào địa lý, với giá trị dương nếu điểm nằm ngoài hàng rào địa lý, giá trị âm nếu nó nằm trong hàng rào địa lý. Nếu khoảng cách này nhỏ hơn search buffer, khoảng cách thực tế được trả về bằng mét, nếu không giá trị là 999 hoặc -999. 999 nghĩa là điểm nằm ngoài hàng rào địa lý hơn search buffer, -999 nghĩa là nó nằm trong hàng rào địa lý hơn search buffer.

![Một hàng rào địa lý với search buffer 50m xung quanh](../../../../../translated_images/search-buffer-and-distance.e6a79af3898183c7.vi.png)

Trong hình trên, hàng rào địa lý có search buffer 50m.

* Một điểm ở trung tâm hàng rào địa lý, nằm trong search buffer có khoảng cách là **-999**
* Một điểm nằm ngoài search buffer có khoảng cách là **999**
* Một điểm nằm trong hàng rào địa lý và trong search buffer, cách hàng rào địa lý 6m, có khoảng cách là **6m**
* Một điểm nằm ngoài hàng rào địa lý và trong search buffer, cách hàng rào địa lý 39m, có khoảng cách là **39m**

Điều quan trọng là biết khoảng cách đến cạnh của hàng rào địa lý, và kết hợp điều này với các thông tin khác như các lần đọc GPS khác, tốc độ và dữ liệu đường khi đưa ra quyết định dựa trên vị trí của phương tiện.

Ví dụ, hãy tưởng tượng các lần đọc GPS cho thấy một phương tiện đang lái trên một con đường chạy cạnh hàng rào địa lý. Nếu một giá trị GPS không chính xác và đặt phương tiện trong hàng rào địa lý, mặc dù không có lối vào cho phương tiện, thì nó có thể bị bỏ qua.

![Một đường GPS cho thấy một phương tiện đi qua khuôn viên Microsoft trên đường 520, với các lần đọc GPS dọc theo đường ngoại trừ một lần trong khuôn viên, nằm trong hàng rào địa lý](../../../../../translated_images/geofence-crossing-inaccurate-gps.6a3ed911202ad9cabb66d3964888cec03a42c61d5b8f536ad5bdc99716b370f5.vi.png)
Trong hình trên, có một hàng rào địa lý bao phủ một phần khuôn viên Microsoft. Đường màu đỏ cho thấy một chiếc xe tải đang di chuyển dọc theo đường 520, với các vòng tròn biểu thị các lần đọc GPS. Hầu hết các lần đọc này đều chính xác và nằm dọc theo đường 520, ngoại trừ một lần đọc không chính xác nằm trong hàng rào địa lý. Không có cách nào để lần đọc đó có thể đúng - không có con đường nào để xe tải đột ngột rẽ từ đường 520 vào khuôn viên, rồi quay lại đường 520. Mã kiểm tra hàng rào địa lý này sẽ cần xem xét các lần đọc trước đó trước khi hành động dựa trên kết quả kiểm tra hàng rào địa lý.

✅ Bạn cần thêm dữ liệu nào để kiểm tra xem một lần đọc GPS có thể được coi là chính xác?

### Nhiệm vụ - kiểm tra các điểm so với hàng rào địa lý

1. Bắt đầu bằng cách xây dựng URL cho truy vấn API web. Định dạng là:

    ```output
    https://atlas.microsoft.com/spatial/geofence/json?api-version=1.0&deviceId=gps-sensor&subscription-key=<subscription-key>&udid=<UDID>&lat=<lat>&lon=<lon>
    ```

    Thay thế `<subscription_key>` bằng khóa API cho tài khoản Azure Maps của bạn.

    Thay thế `<UDID>` bằng UDID của hàng rào địa lý từ nhiệm vụ trước.

    Thay thế `<lat>` và `<lon>` bằng vĩ độ và kinh độ mà bạn muốn kiểm tra.

    URL này sử dụng API `https://atlas.microsoft.com/spatial/geofence/json` để truy vấn một hàng rào địa lý được định nghĩa bằng GeoJSON. Nó nhắm đến phiên bản API `1.0`. Tham số `deviceId` là bắt buộc và nên là tên của thiết bị mà vĩ độ và kinh độ được lấy từ.

    Bộ đệm tìm kiếm mặc định là 50m, và bạn có thể thay đổi điều này bằng cách truyền thêm tham số `searchBuffer=<distance>`, đặt `<distance>` là khoảng cách bộ đệm tìm kiếm tính bằng mét, từ 0 đến 500.

1. Sử dụng curl để thực hiện yêu cầu GET đến URL này:

    ```sh
    curl --request GET '<URL>'
    ```

    > 💁 Nếu bạn nhận được mã phản hồi `BadRequest`, với lỗi:
    >
    > ```output
    > Invalid GeoJSON: All feature properties should contain a geometryId, which is used for identifying the geofence.
    > ```
    >
    > thì GeoJSON của bạn đang thiếu phần `properties` với `geometryId`. Bạn sẽ cần sửa lại GeoJSON của mình, sau đó lặp lại các bước trên để tải lên lại và nhận một UDID mới.

1. Phản hồi sẽ chứa danh sách các `geometries`, một cho mỗi đa giác được định nghĩa trong GeoJSON dùng để tạo hàng rào địa lý. Mỗi geometry có 3 trường quan trọng, `distance`, `nearestLat` và `nearestLon`.

    ```output
    {
        "geometries": [
            {
                "deviceId": "gps-sensor",
                "udId": "7c3776eb-da87-4c52-ae83-caadf980323a",
                "geometryId": "1",
                "distance": 999.0,
                "nearestLat": 47.645875,
                "nearestLon": -122.142713
            }
        ],
        "expiredGeofenceGeometryId": [],
        "invalidPeriodGeofenceGeometryId": []
    }
    ```

    * `nearestLat` và `nearestLon` là vĩ độ và kinh độ của một điểm trên cạnh của hàng rào địa lý gần nhất với vị trí đang được kiểm tra.

    * `distance` là khoảng cách từ vị trí đang được kiểm tra đến điểm gần nhất trên cạnh của hàng rào địa lý. Số âm nghĩa là bên trong hàng rào địa lý, số dương là bên ngoài. Giá trị này sẽ nhỏ hơn 50 (bộ đệm tìm kiếm mặc định), hoặc 999.

1. Lặp lại điều này nhiều lần với các vị trí bên trong và bên ngoài hàng rào địa lý.

## Sử dụng hàng rào địa lý từ mã serverless

Bây giờ bạn có thể thêm một trigger mới vào ứng dụng Functions của mình để kiểm tra dữ liệu sự kiện GPS từ IoT Hub so với hàng rào địa lý.

### Nhóm người tiêu dùng

Như bạn đã nhớ từ các bài học trước, IoT Hub sẽ cho phép bạn phát lại các sự kiện đã được nhận bởi hub nhưng chưa được xử lý. Nhưng điều gì sẽ xảy ra nếu nhiều trigger được kết nối? Làm thế nào nó biết trigger nào đã xử lý sự kiện nào.

Câu trả lời là nó không thể! Thay vào đó, bạn có thể định nghĩa nhiều kết nối riêng biệt để đọc các sự kiện, và mỗi kết nối có thể quản lý việc phát lại các tin nhắn chưa đọc. Những kết nối này được gọi là *nhóm người tiêu dùng*. Khi bạn kết nối đến endpoint, bạn có thể chỉ định nhóm người tiêu dùng mà bạn muốn kết nối. Mỗi thành phần của ứng dụng của bạn sẽ kết nối đến một nhóm người tiêu dùng khác nhau.

![Một IoT Hub với 3 nhóm người tiêu dùng phân phối cùng một tin nhắn đến 3 ứng dụng Functions khác nhau](../../../../../translated_images/consumer-groups.a3262e26fc27ba2092863678ad57af15c7223416e388a23f330c058cf4358630.vi.png)

Theo lý thuyết, tối đa 5 ứng dụng có thể kết nối đến mỗi nhóm người tiêu dùng, và tất cả sẽ nhận được tin nhắn khi chúng đến. Thực hành tốt nhất là chỉ có một ứng dụng truy cập mỗi nhóm người tiêu dùng để tránh xử lý tin nhắn trùng lặp, và đảm bảo khi khởi động lại tất cả các tin nhắn xếp hàng được xử lý đúng cách. Ví dụ, nếu bạn khởi chạy ứng dụng Functions của mình cục bộ cũng như chạy nó trên đám mây, cả hai sẽ xử lý tin nhắn, dẫn đến các blob trùng lặp được lưu trữ trong tài khoản lưu trữ.

Nếu bạn xem lại tệp `function.json` cho trigger IoT Hub mà bạn đã tạo trong bài học trước, bạn sẽ thấy nhóm người tiêu dùng trong phần ràng buộc trigger event hub:

```json
"consumerGroup": "$Default"
```

Khi bạn tạo một IoT Hub, bạn sẽ nhận được nhóm người tiêu dùng `$Default` được tạo mặc định. Nếu bạn muốn thêm một trigger bổ sung, bạn có thể thêm điều này bằng cách sử dụng một nhóm người tiêu dùng mới.

> 💁 Trong bài học này, bạn sẽ sử dụng một hàm khác để kiểm tra hàng rào địa lý so với hàm được sử dụng để lưu trữ dữ liệu GPS. Điều này nhằm minh họa cách sử dụng nhóm người tiêu dùng và tách mã để làm cho nó dễ đọc và hiểu hơn. Trong một ứng dụng sản xuất, có nhiều cách bạn có thể kiến trúc điều này - đặt cả hai trong một hàm, sử dụng trigger trên tài khoản lưu trữ để chạy một hàm kiểm tra hàng rào địa lý, hoặc sử dụng nhiều hàm. Không có 'cách đúng', nó phụ thuộc vào phần còn lại của ứng dụng của bạn và nhu cầu của bạn.

### Nhiệm vụ - tạo một nhóm người tiêu dùng mới

1. Chạy lệnh sau để tạo một nhóm người tiêu dùng mới có tên `geofence` cho IoT Hub của bạn:

    ```sh
    az iot hub consumer-group create --name geofence \
                                     --hub-name <hub_name>
    ```

    Thay thế `<hub_name>` bằng tên bạn đã sử dụng cho IoT Hub của mình.

1. Nếu bạn muốn xem tất cả các nhóm người tiêu dùng cho một IoT Hub, chạy lệnh sau:

    ```sh
    az iot hub consumer-group list --output table \
                                   --hub-name <hub_name>
    ```

    Thay thế `<hub_name>` bằng tên bạn đã sử dụng cho IoT Hub của mình. Điều này sẽ liệt kê tất cả các nhóm người tiêu dùng.

    ```output
    Name      ResourceGroup
    --------  ---------------
    $Default  gps-sensor
    geofence  gps-sensor
    ```

> 💁 Khi bạn chạy trình giám sát sự kiện IoT Hub trong bài học trước, nó đã kết nối đến nhóm người tiêu dùng `$Default`. Đây là lý do tại sao bạn không thể chạy trình giám sát sự kiện và một trigger sự kiện. Nếu bạn muốn chạy cả hai, thì bạn có thể sử dụng các nhóm người tiêu dùng khác cho tất cả các ứng dụng Functions của mình, và giữ `$Default` cho trình giám sát sự kiện.

### Nhiệm vụ - tạo một trigger IoT Hub mới

1. Thêm một trigger sự kiện IoT Hub mới vào ứng dụng `gps-trigger` mà bạn đã tạo trong bài học trước. Gọi hàm này là `geofence-trigger`.

    > ⚠️ Bạn có thể tham khảo [hướng dẫn tạo trigger sự kiện IoT Hub từ dự án 2, bài học 5 nếu cần](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger).

1. Cấu hình chuỗi kết nối IoT Hub trong tệp `function.json`. Tệp `local.settings.json` được chia sẻ giữa tất cả các trigger trong ứng dụng Functions.

1. Cập nhật giá trị của `consumerGroup` trong tệp `function.json` để tham chiếu đến nhóm người tiêu dùng `geofence` mới:

    ```json
    "consumerGroup": "geofence"
    ```

1. Bạn sẽ cần sử dụng khóa đăng ký cho tài khoản Azure Maps của mình trong trigger này, vì vậy hãy thêm một mục mới vào tệp `local.settings.json` có tên `MAPS_KEY`.

1. Chạy ứng dụng Functions để đảm bảo nó đang kết nối và xử lý tin nhắn. Trigger `iot-hub-trigger` từ bài học trước cũng sẽ chạy và tải lên các blob vào lưu trữ.

    > Để tránh các lần đọc GPS trùng lặp trong lưu trữ blob, bạn có thể dừng ứng dụng Functions mà bạn đang chạy trên đám mây. Để làm điều này, sử dụng lệnh sau:
    >
    > ```sh
    > az functionapp stop --resource-group gps-sensor \
    >                     --name <functions_app_name>
    > ```
    >
    > Thay thế `<functions_app_name>` bằng tên bạn đã sử dụng cho ứng dụng Functions của mình.
    >
    > Bạn có thể khởi động lại nó sau với lệnh sau:
    >
    > ```sh
    > az functionapp start --resource-group gps-sensor \
    >                     --name <functions_app_name>
    > ```
    >
    > Thay thế `<functions_app_name>` bằng tên bạn đã sử dụng cho ứng dụng Functions của mình.

### Nhiệm vụ - kiểm tra hàng rào địa lý từ trigger

Trước đó trong bài học này, bạn đã sử dụng curl để truy vấn một hàng rào địa lý để xem liệu một điểm có nằm bên trong hay bên ngoài. Bạn có thể thực hiện một yêu cầu web tương tự từ bên trong trigger của mình.

1. Để truy vấn hàng rào địa lý, bạn cần UDID của nó. Thêm một mục mới vào tệp `local.settings.json` có tên `GEOFENCE_UDID` với giá trị này.

1. Mở tệp `__init__.py` từ trigger `geofence-trigger` mới.

1. Thêm import sau vào đầu tệp:

    ```python
    import json
    import os
    import requests
    ```

    Gói `requests` cho phép bạn thực hiện các cuộc gọi API web. Azure Maps không có SDK Python, bạn cần thực hiện các cuộc gọi API web để sử dụng nó từ mã Python.

1. Thêm 2 dòng sau vào đầu phương thức `main` để lấy khóa đăng ký Maps:

    ```python
    maps_key = os.environ['MAPS_KEY']
    geofence_udid = os.environ['GEOFENCE_UDID']    
    ```

1. Bên trong vòng lặp `for event in events`, thêm đoạn mã sau để lấy vĩ độ và kinh độ từ mỗi sự kiện:

    ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    lat = event_body['gps']['lat']
    lon = event_body['gps']['lon']
    ```

    Đoạn mã này chuyển đổi JSON từ nội dung sự kiện thành một từ điển, sau đó trích xuất `lat` và `lon` từ trường `gps`.

1. Khi sử dụng `requests`, thay vì xây dựng một URL dài như bạn đã làm với curl, bạn có thể chỉ sử dụng phần URL và truyền các tham số dưới dạng từ điển. Thêm đoạn mã sau để định nghĩa URL để gọi và cấu hình các tham số:

    ```python
    url = 'https://atlas.microsoft.com/spatial/geofence/json'

    params = {
        'api-version': 1.0,
        'deviceId': 'gps-sensor',
        'subscription-key': maps_key,
        'udid' : geofence_udid,
        'lat' : lat,
        'lon' : lon
    }
    ```

    Các mục trong từ điển `params` sẽ khớp với các cặp khóa giá trị bạn đã sử dụng khi gọi API web qua curl.

1. Thêm các dòng mã sau để gọi API web:

    ```python
    response = requests.get(url, params=params)
    response_body = json.loads(response.text)
    ```

    Đoạn mã này gọi URL với các tham số, và nhận lại một đối tượng phản hồi.

1. Thêm đoạn mã sau bên dưới:

    ```python
    distance = response_body['geometries'][0]['distance']

    if distance == 999:
        logging.info('Point is outside geofence')
    elif distance > 0:
        logging.info(f'Point is just outside geofence by a distance of {distance}m')
    elif distance == -999:
        logging.info(f'Point is inside geofence')
    else:
        logging.info(f'Point is just inside geofence by a distance of {distance}m')
    ```

    Đoạn mã này giả định có 1 geometry, và trích xuất khoảng cách từ geometry đó. Sau đó, nó ghi nhật ký các thông báo khác nhau dựa trên khoảng cách.

1. Chạy đoạn mã này. Bạn sẽ thấy trong đầu ra nhật ký nếu các tọa độ GPS nằm bên trong hoặc bên ngoài hàng rào địa lý, với khoảng cách nếu điểm nằm trong 50m. Thử đoạn mã này với các hàng rào địa lý khác nhau dựa trên vị trí của cảm biến GPS của bạn, thử di chuyển cảm biến (ví dụ kết nối WiFi từ điện thoại di động, hoặc với các tọa độ khác trên thiết bị IoT ảo) để xem sự thay đổi này.

1. Khi bạn đã sẵn sàng, triển khai đoạn mã này lên ứng dụng Functions của bạn trên đám mây. Đừng quên triển khai các Application Settings mới.

    > ⚠️ Bạn có thể tham khảo [hướng dẫn tải lên Application Settings từ dự án 2, bài học 5 nếu cần](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings).

    > ⚠️ Bạn có thể tham khảo [hướng dẫn triển khai ứng dụng Functions của bạn từ dự án 2, bài học 5 nếu cần](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud).

> 💁 Bạn có thể tìm thấy đoạn mã này trong thư mục [code/functions](../../../../../3-transport/lessons/4-geofences/code/functions).

---

## 🚀 Thử thách

Trong bài học này, bạn đã thêm một hàng rào địa lý sử dụng tệp GeoJSON với một đa giác duy nhất. Bạn có thể tải lên nhiều đa giác cùng một lúc, miễn là chúng có các giá trị `geometryId` khác nhau trong phần `properties`.

Hãy thử tải lên một tệp GeoJSON với nhiều đa giác và điều chỉnh đoạn mã của bạn để tìm xem tọa độ GPS gần nhất hoặc nằm trong đa giác nào.

## Câu hỏi sau bài giảng

[Câu hỏi sau bài giảng](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/28)

## Ôn tập & Tự học

* Đọc thêm về hàng rào địa lý và một số trường hợp sử dụng của chúng trên [trang Geofencing trên Wikipedia](https://en.wikipedia.org/wiki/Geo-fence).
* Đọc thêm về API hàng rào địa lý của Azure Maps trên [tài liệu Microsoft Azure Maps Spatial - Get Geofence](https://docs.microsoft.com/rest/api/maps/spatial/getgeofence?WT.mc_id=academic-17441-jabenn).
* Đọc thêm về nhóm người tiêu dùng trong [Các tính năng và thuật ngữ trong Azure Event Hubs - Tài liệu người tiêu dùng sự kiện trên Microsoft docs](https://docs.microsoft.com/azure/event-hubs/event-hubs-features?WT.mc_id=academic-17441-jabenn#event-consumers).

## Bài tập

[Gửi thông báo sử dụng Twilio](assignment.md)

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn tham khảo chính thức. Đối với các thông tin quan trọng, nên sử dụng dịch vụ dịch thuật chuyên nghiệp từ con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.