<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9095c61445c2bca7245ef9b59a186a11",
  "translation_date": "2025-08-27T23:49:44+00:00",
  "source_file": "3-transport/lessons/3-visualize-location-data/README.md",
  "language_code": "ms"
}
-->
# Visualisasi data lokasi

![Gambaran sketchnote untuk pelajaran ini](../../../../../translated_images/ms/lesson-13.a259db1485021be7d7c72e90842fbe0ab977529e8684c179b5fb1ea75e92b3ef.jpg)

> Sketchnote oleh [Nitya Narasimhan](https://github.com/nitya). Klik imej untuk versi yang lebih besar.

Video ini memberikan gambaran tentang Azure Maps dengan IoT, perkhidmatan yang akan dibincangkan dalam pelajaran ini.

[![Azure Maps - Platform Lokasi Enterprise Microsoft Azure](https://img.youtube.com/vi/P5i2GFTtb2s/0.jpg)](https://www.youtube.com/watch?v=P5i2GFTtb2s)

> 🎥 Klik imej di atas untuk menonton video

## Kuiz sebelum kuliah

[Kuiz sebelum kuliah](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/25)

## Pengenalan

Dalam pelajaran sebelumnya, anda telah belajar cara mendapatkan data GPS daripada sensor anda untuk disimpan di awan dalam bekas storan menggunakan kod tanpa pelayan. Sekarang anda akan belajar cara memvisualisasikan titik-titik tersebut pada peta Azure. Anda akan belajar cara mencipta peta di laman web, memahami format data GeoJSON, dan cara menggunakannya untuk memplot semua titik GPS yang ditangkap pada peta anda.

Dalam pelajaran ini, kita akan membincangkan:

* [Apa itu visualisasi data](../../../../../3-transport/lessons/3-visualize-location-data)
* [Perkhidmatan peta](../../../../../3-transport/lessons/3-visualize-location-data)
* [Cipta sumber Azure Maps](../../../../../3-transport/lessons/3-visualize-location-data)
* [Paparkan peta di laman web](../../../../../3-transport/lessons/3-visualize-location-data)
* [Format GeoJSON](../../../../../3-transport/lessons/3-visualize-location-data)
* [Plot data GPS pada peta menggunakan GeoJSON](../../../../../3-transport/lessons/3-visualize-location-data)

> 💁 Pelajaran ini akan melibatkan sedikit HTML dan JavaScript. Jika anda ingin belajar lebih lanjut tentang pembangunan web menggunakan HTML dan JavaScript, lihat [Pembangunan web untuk pemula](https://github.com/microsoft/Web-Dev-For-Beginners).

## Apa itu visualisasi data

Visualisasi data, seperti namanya, adalah tentang memvisualisasikan data dengan cara yang memudahkan manusia untuk memahaminya. Ia biasanya dikaitkan dengan carta dan graf, tetapi ia adalah apa-apa cara untuk mewakili data secara bergambar untuk membantu manusia bukan sahaja memahami data dengan lebih baik tetapi juga membuat keputusan.

Mengambil contoh mudah - dalam projek ladang anda sebelum ini, anda menangkap bacaan kelembapan tanah. Jadual data kelembapan tanah yang ditangkap setiap jam pada 1 Jun 2021 mungkin seperti berikut:

| Tarikh           | Bacaan  |
| ---------------- | ------: |
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

Sebagai manusia, memahami data ini boleh menjadi sukar. Ia adalah dinding nombor tanpa makna. Sebagai langkah pertama untuk memvisualisasikan data ini, ia boleh diplotkan pada carta garis:

![Carta garis data di atas](../../../../../translated_images/ms/chart-soil-moisture.fd6d9d0cdc0b5f75e78038ecb8945dfc84b38851359de99d84b16e3336d6d7c2.png)

Ini boleh dipertingkatkan lagi dengan menambah garis untuk menunjukkan bila sistem penyiraman automatik dihidupkan pada bacaan kelembapan tanah 450:

![Carta garis kelembapan tanah dengan garis pada 450](../../../../../translated_images/ms/chart-soil-moisture-relay.fbb391236d34a64d0abf1df396e9197e0a24df14150620b9cc820a64a55c9326.png)

Carta ini menunjukkan dengan cepat bukan sahaja tahap kelembapan tanah tetapi juga titik di mana sistem penyiraman dihidupkan.

Carta bukan satu-satunya alat untuk memvisualisasikan data. Peranti IoT yang menjejaki cuaca boleh mempunyai aplikasi web atau aplikasi mudah alih yang memvisualisasikan keadaan cuaca menggunakan simbol, seperti simbol awan untuk hari mendung, awan hujan untuk hari hujan, dan sebagainya. Terdapat banyak cara untuk memvisualisasikan data, ada yang serius, ada yang menyeronokkan.

✅ Fikirkan tentang cara anda pernah melihat data divisualisasikan. Kaedah mana yang paling jelas dan membolehkan anda membuat keputusan dengan cepat?

Visualisasi terbaik membolehkan manusia membuat keputusan dengan cepat. Sebagai contoh, mempunyai dinding tolok yang menunjukkan pelbagai bacaan daripada mesin industri adalah sukar untuk diproses, tetapi lampu merah berkelip apabila sesuatu tidak kena membolehkan manusia membuat keputusan. Kadang-kadang visualisasi terbaik adalah lampu berkelip!

Apabila bekerja dengan data GPS, visualisasi yang paling jelas adalah memplot data pada peta. Peta yang menunjukkan trak penghantaran, sebagai contoh, boleh membantu pekerja di kilang pemprosesan melihat bila trak akan tiba. Jika peta ini menunjukkan lebih daripada sekadar gambar trak di lokasi semasa mereka tetapi memberikan idea tentang kandungan trak, maka pekerja di kilang boleh merancang dengan sewajarnya - jika mereka melihat trak berpendingin berhampiran, mereka tahu untuk menyediakan ruang dalam peti sejuk.

## Perkhidmatan peta

Bekerja dengan peta adalah satu latihan yang menarik, dan terdapat banyak pilihan seperti Bing Maps, Leaflet, Open Street Maps, dan Google Maps. Dalam pelajaran ini, anda akan belajar tentang [Azure Maps](https://azure.microsoft.com/services/azure-maps/?WT.mc_id=academic-17441-jabenn) dan cara ia boleh memaparkan data GPS anda.

![Logo Azure Maps](../../../../../translated_images/ms/azure-maps-logo.35d01dcfbd81fe6140e94257aaa1538f785a58c91576d14e0ebe7a2f6c694b99.png)

Azure Maps adalah "koleksi perkhidmatan geospatial dan SDK yang menggunakan data peta terkini untuk memberikan konteks geografi kepada aplikasi web dan mudah alih." Pembangun disediakan dengan alat untuk mencipta peta interaktif yang cantik yang boleh melakukan perkara seperti memberikan laluan trafik yang disyorkan, memberikan maklumat tentang insiden trafik, navigasi dalaman, keupayaan carian, maklumat ketinggian, perkhidmatan cuaca, dan banyak lagi.

✅ Cuba beberapa [contoh kod pemetaan](https://docs.microsoft.com/samples/browse?WT.mc_id=academic-17441-jabenn&products=azure-maps)

Anda boleh memaparkan peta sebagai kanvas kosong, jubin, imej satelit, imej satelit dengan jalan yang ditindih, pelbagai jenis peta skala kelabu, peta dengan relief teduhan untuk menunjukkan ketinggian, peta pandangan malam, dan peta kontras tinggi. Anda boleh mendapatkan kemas kini masa nyata pada peta anda dengan mengintegrasikannya dengan [Azure Event Grid](https://azure.microsoft.com/services/event-grid/?WT.mc_id=academic-17441-jabenn). Anda boleh mengawal tingkah laku dan rupa peta anda dengan membolehkan pelbagai kawalan untuk membolehkan peta bertindak balas terhadap acara seperti cubit, seret, dan klik. Untuk mengawal rupa peta anda, anda boleh menambah lapisan yang termasuk gelembung, garis, poligon, peta haba, dan banyak lagi. Gaya peta yang anda laksanakan bergantung pada pilihan SDK anda.

Anda boleh mengakses API Azure Maps dengan memanfaatkan [REST API](https://docs.microsoft.com/javascript/api/azure-maps-rest/?WT.mc_id=academic-17441-jabenn&view=azure-maps-typescript-latest), [Web SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-map-control?WT.mc_id=academic-17441-jabenn), atau, jika anda membina aplikasi mudah alih, [Android SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-android-map-control-library?WT.mc_id=academic-17441-jabenn&pivots=programming-language-java-android).

Dalam pelajaran ini, anda akan menggunakan web SDK untuk melukis peta dan memaparkan laluan lokasi GPS sensor anda.

## Cipta sumber Azure Maps

Langkah pertama anda adalah mencipta akaun Azure Maps.

### Tugasan - cipta sumber Azure Maps

1. Jalankan arahan berikut dari Terminal atau Command Prompt anda untuk mencipta sumber Azure Maps dalam kumpulan sumber `gps-sensor` anda:

    ```sh
    az maps account create --name gps-sensor \
                           --resource-group gps-sensor \
                           --accept-tos \
                           --sku S1
    ```

    Ini akan mencipta sumber Azure Maps yang dipanggil `gps-sensor`. Tahap yang digunakan adalah `S1`, yang merupakan tahap berbayar yang merangkumi pelbagai ciri, tetapi dengan jumlah panggilan yang murah hati secara percuma.

    > 💁 Untuk melihat kos menggunakan Azure Maps, lihat [halaman harga Azure Maps](https://azure.microsoft.com/pricing/details/azure-maps/?WT.mc_id=academic-17441-jabenn).

1. Anda akan memerlukan kunci API untuk sumber peta. Gunakan arahan berikut untuk mendapatkan kunci ini:

    ```sh
    az maps account keys list --name gps-sensor \
                              --resource-group gps-sensor \
                              --output table
    ```

    Salin nilai `PrimaryKey`.

## Paparkan peta di laman web

Sekarang anda boleh mengambil langkah seterusnya iaitu memaparkan peta anda di laman web. Kita akan menggunakan hanya satu fail `html` untuk aplikasi web kecil anda; ingat bahawa dalam persekitaran pengeluaran atau pasukan, aplikasi web anda kemungkinan besar akan mempunyai lebih banyak bahagian yang bergerak!

### Tugasan - paparkan peta di laman web

1. Cipta fail bernama index.html dalam folder di komputer tempatan anda. Tambahkan markup HTML untuk memegang peta:

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

    Peta akan dimuatkan dalam `div` `myMap`. Beberapa gaya membolehkan ia merangkumi lebar dan tinggi halaman.

    > 🎓 `div` adalah bahagian laman web yang boleh dinamakan dan digayakan.

1. Di bawah tag pembuka `<head>`, tambahkan lembaran gaya luaran untuk mengawal paparan peta, dan skrip luaran dari Web SDK untuk mengurus tingkah lakunya:

    ```html
    <link rel="stylesheet" href="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.css" type="text/css" />
    <script src="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.js"></script>
    ```

    Lembaran gaya ini mengandungi tetapan untuk bagaimana peta kelihatan, dan fail skrip mengandungi kod untuk memuatkan peta. Menambahkan kod ini adalah serupa dengan memasukkan fail header C++ atau mengimport modul Python.

1. Di bawah skrip itu, tambahkan blok skrip untuk melancarkan peta.

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

    Gantikan `<subscription_key>` dengan kunci API untuk akaun Azure Maps anda.

    Jika anda membuka halaman `index.html` anda dalam pelayar web, anda sepatutnya melihat peta dimuatkan, dan difokuskan pada kawasan Seattle.

    ![Peta menunjukkan Seattle, sebuah bandar di Negeri Washington, AS](../../../../../translated_images/ms/map-image.8fb2c53eb23ef39c1c0a4410a5282e879b3b452b707eb066ff04c5488d3d72b7.png)

    ✅ Cuba bereksperimen dengan parameter zoom dan center untuk mengubah paparan peta anda. Anda boleh menambah koordinat yang berbeza yang sepadan dengan latitud dan longitud data anda untuk memusatkan semula peta.

> 💁 Cara yang lebih baik untuk bekerja dengan aplikasi web secara tempatan adalah dengan memasang [http-server](https://www.npmjs.com/package/http-server). Anda akan memerlukan [node.js](https://nodejs.org/) dan [npm](https://www.npmjs.com/) dipasang sebelum menggunakan alat ini. Setelah alat tersebut dipasang, anda boleh menavigasi ke lokasi fail `index.html` anda dan taipkan `http-server`. Aplikasi web akan dibuka pada pelayan web tempatan [http://127.0.0.1:8080/](http://127.0.0.1:8080/).

## Format GeoJSON

Sekarang anda mempunyai aplikasi web anda dengan peta yang dipaparkan, anda perlu mengekstrak data GPS daripada akaun storan anda dan memaparkannya dalam lapisan penanda di atas peta. Sebelum kita melakukan itu, mari kita lihat format [GeoJSON](https://wikipedia.org/wiki/GeoJSON) yang diperlukan oleh Azure Maps.

[GeoJSON](https://geojson.org/) adalah spesifikasi JSON standard terbuka dengan format khas yang direka untuk mengendalikan data khusus geografi. Anda boleh mempelajarinya dengan menguji data sampel menggunakan [geojson.io](https://geojson.io), yang juga merupakan alat berguna untuk menyahpepijat fail GeoJSON.

Data GeoJSON sampel kelihatan seperti ini:

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

Yang menarik perhatian adalah cara data disusun sebagai `Feature` dalam `FeatureCollection`. Dalam objek itu terdapat `geometry` dengan `coordinates` yang menunjukkan latitud dan longitud.

✅ Apabila membina geoJSON anda, perhatikan susunan `latitude` dan `longitude` dalam objek, atau titik anda tidak akan muncul di tempat yang sepatutnya! GeoJSON mengharapkan data dalam susunan `lon,lat` untuk titik, bukan `lat,lon`.

`Geometry` boleh mempunyai jenis yang berbeza, seperti satu titik atau poligon. Dalam contoh ini, ia adalah titik dengan dua koordinat yang ditentukan, longitud, dan latitud.
✅ Azure Maps menyokong GeoJSON standard serta beberapa [ciri tambahan](https://docs.microsoft.com/azure/azure-maps/extend-geojson?WT.mc_id=academic-17441-jabenn) termasuk keupayaan untuk melukis bulatan dan geometri lain.

## Plot Data GPS pada Peta menggunakan GeoJSON

Sekarang anda bersedia untuk menggunakan data daripada storan yang anda bina dalam pelajaran sebelumnya. Sebagai peringatan, data ini disimpan sebagai beberapa fail dalam storan blob, jadi anda perlu mendapatkan fail-fail tersebut dan memprosesnya supaya Azure Maps dapat menggunakan data tersebut.

### Tugasan - konfigurasikan storan untuk diakses dari laman web

Jika anda membuat panggilan ke storan anda untuk mendapatkan data, anda mungkin terkejut melihat ralat muncul di konsol pelayar anda. Ini kerana anda perlu menetapkan kebenaran untuk [CORS](https://developer.mozilla.org/docs/Web/HTTP/CORS) pada storan ini untuk membenarkan aplikasi web luaran membaca datanya.

> 🎓 CORS bermaksud "Cross-Origin Resource Sharing" dan biasanya perlu ditetapkan secara eksplisit dalam Azure atas sebab keselamatan. Ia menghalang laman web yang tidak dijangka daripada dapat mengakses data anda.

1. Jalankan arahan berikut untuk mengaktifkan CORS:

    ```sh
    az storage cors add --methods GET \
                        --origins "*" \
                        --services b \
                        --account-name <storage_name> \
                        --account-key <key1>
    ```

    Gantikan `<storage_name>` dengan nama akaun storan anda. Gantikan `<key1>` dengan kunci akaun untuk akaun storan anda.

    Arahan ini membenarkan mana-mana laman web (wildcard `*` bermaksud mana-mana) untuk membuat permintaan *GET*, iaitu mendapatkan data, daripada akaun storan anda. `--services b` bermaksud hanya terpakai untuk blob sahaja.

### Tugasan - muatkan data GPS daripada storan

1. Gantikan keseluruhan kandungan fungsi `init` dengan kod berikut:

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

    Gantikan `<storage_name>` dengan nama akaun storan anda. Gantikan `<subscription_key>` dengan kunci API untuk akaun Azure Maps anda.

    Terdapat beberapa perkara yang berlaku di sini. Pertama, kod ini mendapatkan data GPS anda daripada bekas blob menggunakan URL endpoint yang dibina menggunakan nama akaun storan anda. URL ini mendapatkan data daripada `gps-data`, menunjukkan jenis sumber adalah bekas (`restype=container`), dan menyenaraikan maklumat tentang semua blob. Senarai ini tidak akan mengembalikan blob itu sendiri, tetapi akan mengembalikan URL untuk setiap blob yang boleh digunakan untuk memuatkan data blob.

    > 💁 Anda boleh memasukkan URL ini ke dalam pelayar anda untuk melihat butiran semua blob dalam bekas anda. Setiap item akan mempunyai sifat `Url` yang juga boleh anda muatkan dalam pelayar anda untuk melihat kandungan blob.

    Kod ini kemudian memuatkan setiap blob, memanggil fungsi `loadJSON`, yang akan dicipta seterusnya. Ia kemudian mencipta kawalan peta, dan menambah kod kepada acara `ready`. Acara ini dipanggil apabila peta dipaparkan pada laman web.

    Acara ready mencipta sumber data Azure Maps - bekas yang mengandungi data GeoJSON yang akan diisi kemudian. Sumber data ini kemudian digunakan untuk mencipta lapisan gelembung - iaitu satu set bulatan pada peta yang berpusat di atas setiap titik dalam GeoJSON.

1. Tambahkan fungsi `loadJSON` ke dalam blok skrip anda, di bawah fungsi `init`:

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

    Fungsi ini dipanggil oleh rutin fetch untuk memproses data JSON dan menukarnya supaya dapat dibaca sebagai koordinat longitud dan latitud sebagai geoJSON. 
    Setelah diproses, data ini ditetapkan sebagai sebahagian daripada `Feature` geoJSON. Peta akan diinisialisasi dan gelembung kecil akan muncul di sekitar laluan yang data anda plotkan:

1. Muatkan halaman HTML dalam pelayar anda. Ia akan memuatkan peta, kemudian memuatkan semua data GPS daripada storan dan memplotkannya pada peta.

    ![Peta Saint Edward State Park berhampiran Seattle, dengan bulatan menunjukkan laluan di sekitar tepi taman](../../../../../translated_images/ms/map-path.896832e72dc696ffe20650e4051027d4855442d955f93fdbb80bb417ca8a406f.png)

> 💁 Anda boleh menemui kod ini dalam [kod](../../../../../3-transport/lessons/3-visualize-location-data/code) folder.

---

## 🚀 Cabaran

Adalah menarik untuk dapat memaparkan data statik pada peta sebagai penanda. Bolehkah anda meningkatkan aplikasi web ini untuk menambah animasi dan menunjukkan laluan penanda dari masa ke masa, menggunakan fail json yang bertanda masa? Berikut adalah [beberapa contoh](https://azuremapscodesamples.azurewebsites.net/) menggunakan animasi dalam peta.

## Kuiz Selepas Kuliah

[Kuiz Selepas Kuliah](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/26)

## Ulasan & Kajian Kendiri

Azure Maps sangat berguna untuk bekerja dengan peranti IoT.

* Selidiki beberapa kegunaannya dalam [dokumentasi Azure Maps di Microsoft docs](https://docs.microsoft.com/azure/azure-maps/tutorial-iot-hub-maps?WT.mc_id=academic-17441-jabenn).
* Perluaskan pengetahuan anda tentang pembuatan peta dan titik laluan dengan [modul pembelajaran kendiri membuat aplikasi laluan pertama anda dengan Azure Maps di Microsoft Learn](https://docs.microsoft.com/learn/modules/create-your-first-app-with-azure-maps/?WT.mc_id=academic-17441-jabenn).

## Tugasan

[Terbitkan aplikasi anda](assignment.md)

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil maklum bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat penting, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.