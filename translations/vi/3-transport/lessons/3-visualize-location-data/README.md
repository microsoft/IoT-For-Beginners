<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9095c61445c2bca7245ef9b59a186a11",
  "translation_date": "2025-08-27T23:48:00+00:00",
  "source_file": "3-transport/lessons/3-visualize-location-data/README.md",
  "language_code": "vi"
}
-->
# Hình dung dữ liệu vị trí

![Tóm tắt bài học bằng sketchnote](../../../../../translated_images/vi/lesson-13.a259db1485021be7d7c72e90842fbe0ab977529e8684c179b5fb1ea75e92b3ef.jpg)

> Sketchnote bởi [Nitya Narasimhan](https://github.com/nitya). Nhấn vào hình ảnh để xem phiên bản lớn hơn.

Video này cung cấp tổng quan về Azure Maps với IoT, một dịch vụ sẽ được đề cập trong bài học này.

[![Azure Maps - Nền tảng vị trí doanh nghiệp của Microsoft Azure](https://img.youtube.com/vi/P5i2GFTtb2s/0.jpg)](https://www.youtube.com/watch?v=P5i2GFTtb2s)

> 🎥 Nhấn vào hình ảnh trên để xem video

## Câu hỏi trước bài học

[Câu hỏi trước bài học](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/25)

## Giới thiệu

Trong bài học trước, bạn đã học cách lấy dữ liệu GPS từ cảm biến và lưu trữ vào đám mây trong một container lưu trữ bằng mã serverless. Bây giờ, bạn sẽ khám phá cách hình dung các điểm đó trên bản đồ Azure. Bạn sẽ học cách tạo một bản đồ trên trang web, tìm hiểu về định dạng dữ liệu GeoJSON và cách sử dụng nó để vẽ tất cả các điểm GPS đã thu thập trên bản đồ của bạn.

Trong bài học này, chúng ta sẽ đề cập đến:

* [Hình dung dữ liệu là gì](../../../../../3-transport/lessons/3-visualize-location-data)
* [Dịch vụ bản đồ](../../../../../3-transport/lessons/3-visualize-location-data)
* [Tạo tài nguyên Azure Maps](../../../../../3-transport/lessons/3-visualize-location-data)
* [Hiển thị bản đồ trên trang web](../../../../../3-transport/lessons/3-visualize-location-data)
* [Định dạng GeoJSON](../../../../../3-transport/lessons/3-visualize-location-data)
* [Vẽ dữ liệu GPS trên bản đồ bằng GeoJSON](../../../../../3-transport/lessons/3-visualize-location-data)

> 💁 Bài học này sẽ bao gồm một lượng nhỏ HTML và JavaScript. Nếu bạn muốn tìm hiểu thêm về phát triển web bằng HTML và JavaScript, hãy xem [Phát triển web cho người mới bắt đầu](https://github.com/microsoft/Web-Dev-For-Beginners).

## Hình dung dữ liệu là gì

Hình dung dữ liệu, như tên gọi, là việc biểu diễn dữ liệu theo cách giúp con người dễ hiểu hơn. Nó thường liên quan đến biểu đồ và đồ thị, nhưng thực chất là bất kỳ cách nào biểu diễn dữ liệu bằng hình ảnh để giúp con người không chỉ hiểu rõ hơn mà còn đưa ra quyết định.

Lấy một ví dụ đơn giản - trong dự án nông trại, bạn đã thu thập các chỉ số độ ẩm đất. Một bảng dữ liệu độ ẩm đất được thu thập mỗi giờ vào ngày 1 tháng 6 năm 2021 có thể trông như sau:

| Ngày              | Chỉ số |
| ----------------- | ------: |
| 01/06/2021 00:00 |     257 |
| 01/06/2021 01:00 |     268 |
| 01/06/2021 02:00 |     295 |
| 01/06/2021 03:00 |     305 |
| 01/06/2021 04:00 |     325 |
| 01/06/2021 05:00 |     359 |
| 01/06/2021 06:00 |     398 |
| 01/06/2021 07:00 |     410 |
| 01/06/2021 08:00 |     429 |
| 01/06/2021 09:00 |     451 |
| 01/06/2021 10:00 |     460 |
| 01/06/2021 11:00 |     452 |
| 01/06/2021 12:00 |     420 |
| 01/06/2021 13:00 |     408 |
| 01/06/2021 14:00 |     431 |
| 01/06/2021 15:00 |     462 |
| 01/06/2021 16:00 |     432 |
| 01/06/2021 17:00 |     402 |
| 01/06/2021 18:00 |     387 |
| 01/06/2021 19:00 |     360 |
| 01/06/2021 20:00 |     358 |
| 01/06/2021 21:00 |     354 |
| 01/06/2021 22:00 |     356 |
| 01/06/2021 23:00 |     362 |

Đối với con người, việc hiểu dữ liệu này có thể khó khăn. Nó chỉ là một bức tường số liệu không mang ý nghĩa gì. Bước đầu tiên để hình dung dữ liệu này là vẽ nó trên biểu đồ đường:

![Biểu đồ đường của dữ liệu trên](../../../../../translated_images/vi/chart-soil-moisture.fd6d9d0cdc0b5f75e78038ecb8945dfc84b38851359de99d84b16e3336d6d7c2.png)

Điều này có thể được cải thiện thêm bằng cách thêm một đường chỉ ra khi hệ thống tưới tự động được bật ở mức độ ẩm đất là 450:

![Biểu đồ đường của độ ẩm đất với một đường ở mức 450](../../../../../translated_images/vi/chart-soil-moisture-relay.fbb391236d34a64d0abf1df396e9197e0a24df14150620b9cc820a64a55c9326.png)

Biểu đồ này nhanh chóng cho thấy không chỉ mức độ ẩm đất mà còn các điểm mà hệ thống tưới được bật.

Biểu đồ không phải là công cụ duy nhất để hình dung dữ liệu. Các thiết bị IoT theo dõi thời tiết có thể có ứng dụng web hoặc di động để hình dung điều kiện thời tiết bằng các biểu tượng, chẳng hạn như biểu tượng đám mây cho ngày nhiều mây, biểu tượng mưa cho ngày mưa, v.v. Có rất nhiều cách để hình dung dữ liệu, từ nghiêm túc đến vui nhộn.

✅ Hãy nghĩ về những cách bạn đã thấy dữ liệu được hình dung. Phương pháp nào rõ ràng nhất và giúp bạn đưa ra quyết định nhanh nhất?

Những hình dung tốt nhất cho phép con người đưa ra quyết định nhanh chóng. Ví dụ, có một bức tường đồng hồ đo hiển thị tất cả các chỉ số từ máy móc công nghiệp rất khó xử lý, nhưng một đèn đỏ nhấp nháy khi có sự cố sẽ giúp con người đưa ra quyết định. Đôi khi, hình dung tốt nhất chỉ là một đèn nhấp nháy!

Khi làm việc với dữ liệu GPS, cách hình dung rõ ràng nhất có thể là vẽ dữ liệu trên bản đồ. Một bản đồ hiển thị các xe tải giao hàng, chẳng hạn, có thể giúp nhân viên tại nhà máy xử lý biết khi nào xe tải sẽ đến. Nếu bản đồ này hiển thị không chỉ hình ảnh của các xe tải tại vị trí hiện tại mà còn cung cấp thông tin về nội dung của xe, thì nhân viên tại nhà máy có thể lên kế hoạch phù hợp - nếu họ thấy một xe tải đông lạnh gần đó, họ biết cần chuẩn bị không gian trong tủ lạnh.

## Dịch vụ bản đồ

Làm việc với bản đồ là một bài tập thú vị, và có rất nhiều dịch vụ để lựa chọn như Bing Maps, Leaflet, Open Street Maps, và Google Maps. Trong bài học này, bạn sẽ tìm hiểu về [Azure Maps](https://azure.microsoft.com/services/azure-maps/?WT.mc_id=academic-17441-jabenn) và cách chúng có thể hiển thị dữ liệu GPS của bạn.

![Logo Azure Maps](../../../../../translated_images/vi/azure-maps-logo.35d01dcfbd81fe6140e94257aaa1538f785a58c91576d14e0ebe7a2f6c694b99.png)

Azure Maps là "một tập hợp các dịch vụ không gian địa lý và SDK sử dụng dữ liệu bản đồ mới nhất để cung cấp ngữ cảnh địa lý cho các ứng dụng web và di động." Các nhà phát triển được cung cấp các công cụ để tạo ra các bản đồ đẹp, tương tác có thể làm những việc như cung cấp tuyến đường giao thông được đề xuất, thông tin về sự cố giao thông, điều hướng trong nhà, khả năng tìm kiếm, thông tin độ cao, dịch vụ thời tiết và nhiều hơn nữa.

✅ Thử nghiệm với một số [mẫu mã bản đồ](https://docs.microsoft.com/samples/browse?WT.mc_id=academic-17441-jabenn&products=azure-maps)

Bạn có thể hiển thị bản đồ dưới dạng canvas trống, ô, hình ảnh vệ tinh, hình ảnh vệ tinh với đường chồng lên, các loại bản đồ xám khác nhau, bản đồ với bóng để hiển thị độ cao, bản đồ chế độ ban đêm, và bản đồ có độ tương phản cao. Bạn có thể nhận cập nhật thời gian thực trên bản đồ của mình bằng cách tích hợp chúng với [Azure Event Grid](https://azure.microsoft.com/services/event-grid/?WT.mc_id=academic-17441-jabenn). Bạn có thể kiểm soát hành vi và giao diện của bản đồ bằng cách kích hoạt các điều khiển khác nhau để cho phép bản đồ phản ứng với các sự kiện như chụm, kéo và nhấp. Để kiểm soát giao diện của bản đồ, bạn có thể thêm các lớp bao gồm bong bóng, đường, đa giác, bản đồ nhiệt và nhiều hơn nữa. Loại bản đồ bạn triển khai phụ thuộc vào lựa chọn SDK của bạn.

Bạn có thể truy cập các API Azure Maps bằng cách sử dụng [REST API](https://docs.microsoft.com/javascript/api/azure-maps-rest/?WT.mc_id=academic-17441-jabenn&view=azure-maps-typescript-latest), [Web SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-map-control?WT.mc_id=academic-17441-jabenn), hoặc, nếu bạn đang xây dựng ứng dụng di động, [Android SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-android-map-control-library?WT.mc_id=academic-17441-jabenn&pivots=programming-language-java-android).

Trong bài học này, bạn sẽ sử dụng Web SDK để vẽ bản đồ và hiển thị đường đi của vị trí GPS từ cảm biến của bạn.

## Tạo tài nguyên Azure Maps

Bước đầu tiên của bạn là tạo một tài khoản Azure Maps.

### Nhiệm vụ - tạo tài nguyên Azure Maps

1. Chạy lệnh sau từ Terminal hoặc Command Prompt để tạo tài nguyên Azure Maps trong nhóm tài nguyên `gps-sensor`:

    ```sh
    az maps account create --name gps-sensor \
                           --resource-group gps-sensor \
                           --accept-tos \
                           --sku S1
    ```

    Điều này sẽ tạo một tài nguyên Azure Maps có tên `gps-sensor`. Tầng được sử dụng là `S1`, một tầng trả phí bao gồm nhiều tính năng, nhưng với số lượng cuộc gọi miễn phí hào phóng.

    > 💁 Để xem chi phí sử dụng Azure Maps, hãy xem [trang giá Azure Maps](https://azure.microsoft.com/pricing/details/azure-maps/?WT.mc_id=academic-17441-jabenn).

1. Bạn sẽ cần một khóa API cho tài nguyên bản đồ. Sử dụng lệnh sau để lấy khóa này:

    ```sh
    az maps account keys list --name gps-sensor \
                              --resource-group gps-sensor \
                              --output table
    ```

    Sao chép giá trị `PrimaryKey`.

## Hiển thị bản đồ trên trang web

Bây giờ bạn có thể thực hiện bước tiếp theo là hiển thị bản đồ trên trang web. Chúng ta sẽ chỉ sử dụng một tệp `html` cho ứng dụng web nhỏ của bạn; hãy nhớ rằng trong môi trường sản xuất hoặc làm việc nhóm, ứng dụng web của bạn có thể có nhiều phần phức tạp hơn!

### Nhiệm vụ - hiển thị bản đồ trên trang web

1. Tạo một tệp có tên index.html trong một thư mục nào đó trên máy tính của bạn. Thêm mã HTML để chứa bản đồ:

    ```html
    <html>
    <head>
        <style>
            #myMap {
                width:100%;
                height:100%;
            }
        </style>
    </head>
    
    <body onload="init()">
        <div id="myMap"></div>
    </body>
    </html>
    ```

    Bản đồ sẽ được tải trong `div` có tên `myMap`. Một vài kiểu dáng cho phép nó chiếm toàn bộ chiều rộng và chiều cao của trang.

    > 🎓 Một `div` là một phần của trang web có thể được đặt tên và định kiểu.

1. Dưới thẻ `<head>` mở, thêm một tệp style sheet bên ngoài để kiểm soát hiển thị bản đồ và một script bên ngoài từ Web SDK để quản lý hành vi của nó:

    ```html
    <link rel="stylesheet" href="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.css" type="text/css" />
    <script src="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.js"></script>
    ```

    Tệp style sheet này chứa các cài đặt cho cách bản đồ hiển thị, và tệp script chứa mã để tải bản đồ. Thêm mã này tương tự như việc bao gồm các tệp header trong C++ hoặc nhập các module trong Python.

1. Dưới script đó, thêm một khối script để khởi chạy bản đồ.

    ```javascript
    <script type='text/javascript'>
        function init() {
            var map = new atlas.Map('myMap', {
                center: [-122.26473, 47.73444],
                zoom: 12,
                authOptions: {
                    authType: "subscriptionKey",
                    subscriptionKey: "<subscription_key>",

                }
            });
        }
    </script>
    ```

    Thay `<subscription_key>` bằng khóa API cho tài khoản Azure Maps của bạn.

    Nếu bạn mở tệp `index.html` trong trình duyệt web, bạn sẽ thấy một bản đồ được tải và tập trung vào khu vực Seattle.

    ![Bản đồ hiển thị Seattle, một thành phố ở bang Washington, Mỹ](../../../../../translated_images/vi/map-image.8fb2c53eb23ef39c1c0a4410a5282e879b3b452b707eb066ff04c5488d3d72b7.png)

    ✅ Thử nghiệm với các tham số zoom và center để thay đổi hiển thị bản đồ. Bạn có thể thêm các tọa độ khác tương ứng với vĩ độ và kinh độ của dữ liệu để tái định tâm bản đồ.

> 💁 Một cách tốt hơn để làm việc với ứng dụng web cục bộ là cài đặt [http-server](https://www.npmjs.com/package/http-server). Bạn sẽ cần cài đặt [node.js](https://nodejs.org/) và [npm](https://www.npmjs.com/) trước khi sử dụng công cụ này. Sau khi các công cụ này được cài đặt, bạn có thể điều hướng đến vị trí của tệp `index.html` và gõ `http-server`. Ứng dụng web sẽ mở trên một máy chủ web cục bộ [http://127.0.0.1:8080/](http://127.0.0.1:8080/).

## Định dạng GeoJSON

Bây giờ bạn đã có ứng dụng web của mình với bản đồ hiển thị, bạn cần trích xuất dữ liệu GPS từ tài khoản lưu trữ và hiển thị nó trong một lớp các điểm đánh dấu trên bản đồ. Trước khi làm điều đó, hãy xem định dạng [GeoJSON](https://wikipedia.org/wiki/GeoJSON) được yêu cầu bởi Azure Maps.

[GeoJSON](https://geojson.org/) là một tiêu chuẩn JSON mở với định dạng đặc biệt được thiết kế để xử lý dữ liệu địa lý cụ thể. Bạn có thể tìm hiểu về nó bằng cách thử nghiệm dữ liệu mẫu sử dụng [geojson.io](https://geojson.io), đây cũng là một công cụ hữu ích để gỡ lỗi các tệp GeoJSON.

Dữ liệu GeoJSON mẫu trông như sau:

```json
{
  "type": "FeatureCollection",
  "features": [
    {
      "type": "Feature",
      "geometry": {
        "type": "Point",
        "coordinates": [
          -2.10237979888916,
          57.164918677004714
        ]
      }
    }
  ]
}
```

Điều đặc biệt quan trọng là cách dữ liệu được lồng vào như một `Feature` trong một `FeatureCollection`. Bên trong đối tượng đó có thể tìm thấy `geometry` với `coordinates` chỉ định vĩ độ và kinh độ.

✅ Khi xây dựng GeoJSON của bạn, hãy chú ý đến thứ tự của `latitude` và `longitude` trong đối tượng, nếu không các điểm của bạn sẽ không xuất hiện đúng vị trí! GeoJSON yêu cầu dữ liệu theo thứ tự `lon,lat` cho các điểm, không phải `lat,lon`.

`Geometry` có thể có các loại khác nhau, chẳng hạn như một điểm đơn lẻ hoặc một đa giác. Trong ví dụ này, nó là một điểm với hai tọa độ được chỉ định, kinh độ và vĩ độ.
✅ Azure Maps hỗ trợ GeoJSON tiêu chuẩn cùng với một số [tính năng mở rộng](https://docs.microsoft.com/azure/azure-maps/extend-geojson?WT.mc_id=academic-17441-jabenn), bao gồm khả năng vẽ các hình tròn và các hình học khác.

## Vẽ dữ liệu GPS trên bản đồ bằng GeoJSON

Bây giờ bạn đã sẵn sàng sử dụng dữ liệu từ bộ lưu trữ mà bạn đã xây dựng trong bài học trước. Như đã nhắc lại, dữ liệu này được lưu trữ dưới dạng một số tệp trong blob storage, vì vậy bạn sẽ cần truy xuất các tệp và phân tích chúng để Azure Maps có thể sử dụng dữ liệu.

### Nhiệm vụ - cấu hình bộ lưu trữ để truy cập từ trang web

Nếu bạn thực hiện một yêu cầu đến bộ lưu trữ của mình để lấy dữ liệu, bạn có thể ngạc nhiên khi thấy các lỗi xuất hiện trong bảng điều khiển của trình duyệt. Đó là vì bạn cần thiết lập quyền cho [CORS](https://developer.mozilla.org/docs/Web/HTTP/CORS) trên bộ lưu trữ này để cho phép các ứng dụng web bên ngoài đọc dữ liệu của nó.

> 🎓 CORS là viết tắt của "Chia sẻ tài nguyên giữa các nguồn" và thường cần được thiết lập rõ ràng trong Azure vì lý do bảo mật. Nó ngăn các trang web mà bạn không mong đợi truy cập vào dữ liệu của bạn.

1. Chạy lệnh sau để bật CORS:

    ```sh
    az storage cors add --methods GET \
                        --origins "*" \
                        --services b \
                        --account-name <storage_name> \
                        --account-key <key1>
    ```

    Thay thế `<storage_name>` bằng tên tài khoản lưu trữ của bạn. Thay thế `<key1>` bằng khóa tài khoản cho tài khoản lưu trữ của bạn.

    Lệnh này cho phép bất kỳ trang web nào (ký tự đại diện `*` có nghĩa là bất kỳ) thực hiện yêu cầu *GET*, tức là lấy dữ liệu, từ tài khoản lưu trữ của bạn. Tham số `--services b` có nghĩa là chỉ áp dụng cài đặt này cho blobs.

### Nhiệm vụ - tải dữ liệu GPS từ bộ lưu trữ

1. Thay thế toàn bộ nội dung của hàm `init` bằng đoạn mã sau:

    ```javascript
    fetch("https://<storage_name>.blob.core.windows.net/gps-data/?restype=container&comp=list")
        .then(response => response.text())
        .then(str => new window.DOMParser().parseFromString(str, "text/xml"))
        .then(xml => {
            let blobList = Array.from(xml.querySelectorAll("Url"));
                blobList.forEach(async blobUrl => {
                    loadJSON(blobUrl.innerHTML)                
        });
    })
    .then( response => {
        map = new atlas.Map('myMap', {
            center: [-122.26473, 47.73444],
            zoom: 14,
            authOptions: {
                authType: "subscriptionKey",
                subscriptionKey: "<subscription_key>",
    
            }
        });
        map.events.add('ready', function () {
            var source = new atlas.source.DataSource();
            map.sources.add(source);
            map.layers.add(new atlas.layer.BubbleLayer(source));
            source.add(features);
        })
    })
    ```

    Thay thế `<storage_name>` bằng tên tài khoản lưu trữ của bạn. Thay thế `<subscription_key>` bằng khóa API cho tài khoản Azure Maps của bạn.

    Có một số điều đang diễn ra ở đây. Đầu tiên, đoạn mã lấy dữ liệu GPS của bạn từ blob container bằng cách sử dụng một URL endpoint được xây dựng bằng tên tài khoản lưu trữ của bạn. URL này truy xuất từ `gps-data`, chỉ ra rằng loại tài nguyên là một container (`restype=container`), và liệt kê thông tin về tất cả các blobs. Danh sách này sẽ không trả về chính các blobs, mà sẽ trả về một URL cho mỗi blob có thể được sử dụng để tải dữ liệu blob.

    > 💁 Bạn có thể đặt URL này vào trình duyệt của mình để xem chi tiết của tất cả các blobs trong container của bạn. Mỗi mục sẽ có thuộc tính `Url` mà bạn cũng có thể tải trong trình duyệt để xem nội dung của blob.

    Đoạn mã này sau đó tải từng blob, gọi hàm `loadJSON`, mà bạn sẽ tạo tiếp theo. Sau đó, nó tạo điều khiển bản đồ và thêm mã vào sự kiện `ready`. Sự kiện này được gọi khi bản đồ được hiển thị trên trang web.

    Sự kiện ready tạo một nguồn dữ liệu Azure Maps - một container chứa dữ liệu GeoJSON sẽ được điền sau. Nguồn dữ liệu này sau đó được sử dụng để tạo một lớp bong bóng - tức là một tập hợp các vòng tròn trên bản đồ tập trung tại mỗi điểm trong GeoJSON.

1. Thêm hàm `loadJSON` vào khối script của bạn, bên dưới hàm `init`:

    ```javascript
    var map, features;

    function loadJSON(file) {
        var xhr = new XMLHttpRequest();
        features = [];
        xhr.onreadystatechange = function () {
            if (xhr.readyState === XMLHttpRequest.DONE) {
                if (xhr.status === 200) {
                    gps = JSON.parse(xhr.responseText)
                    features.push(
                        new atlas.data.Feature(new atlas.data.Point([parseFloat(gps.gps.lon), parseFloat(gps.gps.lat)]))
                    )
                }
            }
        };
        xhr.open("GET", file, true);
        xhr.send();
    }    
    ```

    Hàm này được gọi bởi quy trình fetch để phân tích dữ liệu JSON và chuyển đổi nó thành tọa độ kinh độ và vĩ độ dưới dạng GeoJSON. 
    Sau khi được phân tích, dữ liệu được đặt thành một `Feature` GeoJSON. Bản đồ sẽ được khởi tạo và các vòng tròn nhỏ sẽ xuất hiện xung quanh đường đi mà dữ liệu của bạn đang vẽ:

1. Tải trang HTML trong trình duyệt của bạn. Nó sẽ tải bản đồ, sau đó tải tất cả dữ liệu GPS từ bộ lưu trữ và vẽ nó trên bản đồ.

    ![Bản đồ Công viên Bang Saint Edward gần Seattle, với các vòng tròn hiển thị một đường đi xung quanh rìa công viên](../../../../../translated_images/vi/map-path.896832e72dc696ffe20650e4051027d4855442d955f93fdbb80bb417ca8a406f.png)

> 💁 Bạn có thể tìm thấy đoạn mã này trong [thư mục mã](../../../../../3-transport/lessons/3-visualize-location-data/code).

---

## 🚀 Thử thách

Thật tuyệt khi có thể hiển thị dữ liệu tĩnh trên bản đồ dưới dạng các điểm đánh dấu. Bạn có thể nâng cấp ứng dụng web này để thêm hoạt ảnh và hiển thị đường đi của các điểm đánh dấu theo thời gian, sử dụng các tệp json có dấu thời gian không? Đây là [một số mẫu](https://azuremapscodesamples.azurewebsites.net/) về cách sử dụng hoạt ảnh trong bản đồ.

## Câu đố sau bài giảng

[Câu đố sau bài giảng](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/26)

## Ôn tập & Tự học

Azure Maps đặc biệt hữu ích khi làm việc với các thiết bị IoT.

* Nghiên cứu một số ứng dụng trong [tài liệu Azure Maps trên Microsoft docs](https://docs.microsoft.com/azure/azure-maps/tutorial-iot-hub-maps?WT.mc_id=academic-17441-jabenn).
* Đào sâu kiến thức về tạo bản đồ và điểm dừng với [học phần tự hướng dẫn tạo ứng dụng tìm đường đầu tiên với Azure Maps trên Microsoft Learn](https://docs.microsoft.com/learn/modules/create-your-first-app-with-azure-maps/?WT.mc_id=academic-17441-jabenn).

## Bài tập

[Triển khai ứng dụng của bạn](assignment.md)

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.