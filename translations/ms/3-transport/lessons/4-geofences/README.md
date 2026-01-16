<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "078ae664c7b686bf069545e9a5fc95b2",
  "translation_date": "2025-08-27T23:36:13+00:00",
  "source_file": "3-transport/lessons/4-geofences/README.md",
  "language_code": "ms"
}
-->
# Geopagar

![Gambaran sketchnote untuk pelajaran ini](../../../../../translated_images/ms/lesson-14.63980c5150ae3c153e770fb71d044c1845dce79248d86bed9fc525adf3ede73c.jpg)

> Sketchnote oleh [Nitya Narasimhan](https://github.com/nitya). Klik gambar untuk versi yang lebih besar.

Video ini memberikan gambaran keseluruhan tentang geopagar dan cara menggunakannya dalam Azure Maps, topik yang akan dibincangkan dalam pelajaran ini:

[![Geopagar dengan Azure Maps dari rancangan Microsoft Developer IoT](https://img.youtube.com/vi/nsrgYhaYNVY/0.jpg)](https://www.youtube.com/watch?v=nsrgYhaYNVY)

> 🎥 Klik gambar di atas untuk menonton video

## Kuiz sebelum kuliah

[Kuiz sebelum kuliah](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/27)

## Pengenalan

Dalam 3 pelajaran terakhir, anda telah menggunakan IoT untuk mengesan lokasi trak yang membawa hasil tanaman anda dari ladang ke hab pemprosesan. Anda telah menangkap data GPS, menghantarnya ke awan untuk disimpan, dan memvisualisasikannya di peta. Langkah seterusnya untuk meningkatkan kecekapan rantaian bekalan anda adalah mendapatkan pemberitahuan apabila trak hampir tiba di hab pemprosesan, supaya kru yang diperlukan untuk memunggah boleh bersedia dengan forklift dan peralatan lain sebaik sahaja kenderaan tiba. Dengan cara ini, mereka boleh memunggah dengan cepat, dan anda tidak perlu membayar trak dan pemandu untuk menunggu.

Dalam pelajaran ini, anda akan mempelajari tentang geopagar - kawasan geospatial yang ditentukan seperti kawasan dalam jarak pemanduan 2km dari hab pemprosesan, dan cara menguji sama ada koordinat GPS berada di dalam atau di luar geopagar, supaya anda dapat melihat sama ada sensor GPS anda telah tiba atau meninggalkan kawasan tersebut.

Dalam pelajaran ini, kita akan membincangkan:

* [Apa itu geopagar](../../../../../3-transport/lessons/4-geofences)
* [Menentukan geopagar](../../../../../3-transport/lessons/4-geofences)
* [Menguji titik terhadap geopagar](../../../../../3-transport/lessons/4-geofences)
* [Menggunakan geopagar dari kod tanpa pelayan](../../../../../3-transport/lessons/4-geofences)

> 🗑 Ini adalah pelajaran terakhir dalam projek ini, jadi selepas menyelesaikan pelajaran ini dan tugasan, jangan lupa untuk membersihkan perkhidmatan awan anda. Anda akan memerlukan perkhidmatan tersebut untuk menyelesaikan tugasan, jadi pastikan untuk menyelesaikannya terlebih dahulu.
>
> Rujuk [panduan membersihkan projek anda](../../../clean-up.md) jika perlu untuk arahan tentang cara melakukannya.

## Apa itu Geopagar

Geopagar adalah perimeter maya untuk kawasan geografi dunia nyata. Geopagar boleh berbentuk bulatan yang ditentukan sebagai titik dan jejari (contohnya bulatan dengan lebar 100m di sekitar bangunan), atau poligon yang meliputi kawasan seperti zon sekolah, sempadan bandar, atau kampus universiti atau pejabat.

![Beberapa contoh geopagar yang menunjukkan geopagar berbentuk bulatan di sekitar kedai syarikat Microsoft, dan geopagar berbentuk poligon di sekitar kampus barat Microsoft](../../../../../translated_images/ms/geofence-examples.172fbc534665769f6e1a1ddcf75e3b25183cd10354c80cc603ba44b635390e1a.png)

> 💁 Anda mungkin telah menggunakan geopagar tanpa menyedarinya. Jika anda pernah menetapkan peringatan menggunakan aplikasi peringatan iOS atau Google Keep berdasarkan lokasi, anda telah menggunakan geopagar. Aplikasi ini akan menetapkan geopagar berdasarkan lokasi yang diberikan dan memberi amaran kepada anda apabila telefon anda memasuki geopagar.

Terdapat banyak sebab mengapa anda ingin mengetahui sama ada kenderaan berada di dalam atau di luar geopagar:

* Persediaan untuk memunggah - mendapatkan pemberitahuan bahawa kenderaan telah tiba di lokasi membolehkan kru bersedia untuk memunggah kenderaan, mengurangkan masa menunggu kenderaan. Ini boleh membolehkan pemandu membuat lebih banyak penghantaran dalam sehari dengan masa menunggu yang lebih sedikit.
* Pematuhan cukai - beberapa negara, seperti New Zealand, mengenakan cukai jalan untuk kenderaan diesel berdasarkan berat kenderaan apabila memandu di jalan awam sahaja. Menggunakan geopagar membolehkan anda menjejaki jarak perjalanan di jalan awam berbanding jalan persendirian di lokasi seperti ladang atau kawasan pembalakan.
* Pemantauan kecurian - jika kenderaan sepatutnya hanya berada di kawasan tertentu seperti di ladang, dan ia meninggalkan geopagar, ia mungkin telah dicuri.
* Pematuhan lokasi - beberapa bahagian tapak kerja, ladang atau kilang mungkin dilarang untuk kenderaan tertentu, seperti memastikan kenderaan yang membawa baja tiruan dan racun perosak tidak memasuki ladang yang menanam hasil organik. Jika geopagar dimasuki, maka kenderaan berada di luar pematuhan dan pemandu boleh diberitahu.

✅ Bolehkah anda memikirkan kegunaan lain untuk geopagar?

Azure Maps, perkhidmatan yang anda gunakan dalam pelajaran terakhir untuk memvisualisasikan data GPS, membolehkan anda menentukan geopagar, kemudian menguji sama ada titik berada di dalam atau di luar geopagar.

## Menentukan geopagar

Geopagar ditentukan menggunakan GeoJSON, sama seperti titik yang ditambahkan ke peta dalam pelajaran sebelumnya. Dalam kes ini, bukannya `FeatureCollection` nilai `Point`, ia adalah `FeatureCollection` yang mengandungi `Polygon`.

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

Setiap titik pada poligon ditentukan sebagai pasangan longitud, latitud dalam array, dan titik-titik ini berada dalam array yang ditetapkan sebagai `coordinates`. Dalam `Point` dalam pelajaran terakhir, `coordinates` adalah array yang mengandungi 2 nilai, latitud dan longitud, untuk `Polygon` ia adalah array dari array yang mengandungi 2 nilai, longitud, latitud.

> 💁 Ingat, GeoJSON menggunakan `longitud, latitud` untuk titik, bukan `latitud, longitud`

Array koordinat poligon sentiasa mempunyai 1 entri lebih banyak daripada bilangan titik pada poligon, dengan entri terakhir sama seperti yang pertama, menutup poligon. Sebagai contoh, untuk segi empat tepat akan ada 5 titik.

![Segi empat tepat dengan koordinat](../../../../../translated_images/ms/polygon-points.302193da381cb415.webp)

Dalam gambar di atas, terdapat segi empat tepat. Koordinat poligon bermula di kiri atas pada 47,-122, kemudian bergerak ke kanan ke 47,-121, kemudian ke bawah ke 46,-121, kemudian ke kiri ke 46, -122, kemudian kembali ke titik permulaan di 47, -122. Ini memberikan poligon 5 titik - kiri atas, kanan atas, kanan bawah, kiri bawah, kemudian kiri atas untuk menutupnya.

✅ Cuba buat poligon GeoJSON di sekitar rumah atau sekolah anda. Gunakan alat seperti [GeoJSON.io](https://geojson.io/).

### Tugasan - menentukan geopagar

Untuk menggunakan geopagar dalam Azure Maps, pertama ia perlu dimuat naik ke akaun Azure Maps anda. Setelah dimuat naik, anda akan mendapat ID unik yang boleh anda gunakan untuk menguji titik terhadap geopagar. Untuk memuat naik geopagar ke Azure Maps, anda perlu menggunakan API web peta. Anda boleh memanggil API web Azure Maps menggunakan alat yang dipanggil [curl](https://curl.se).

> 🎓 Curl adalah alat baris perintah untuk membuat permintaan terhadap titik akhir web

1. Jika anda menggunakan Linux, macOS, atau versi terkini Windows 10, anda mungkin sudah mempunyai curl dipasang. Jalankan arahan berikut dari terminal atau baris perintah anda untuk memeriksa:

    ```sh
    curl --version
    ```

    Jika anda tidak melihat maklumat versi untuk curl, anda perlu memasangnya dari [halaman muat turun curl](https://curl.se/download.html).

    > 💁 Jika anda berpengalaman dengan Postman, anda boleh menggunakannya sebagai alternatif jika anda mahu.

1. Buat fail GeoJSON yang mengandungi poligon. Anda akan mengujinya menggunakan sensor GPS anda, jadi buat poligon di sekitar lokasi semasa anda. Anda boleh membuatnya secara manual dengan mengedit contoh GeoJSON yang diberikan di atas, atau menggunakan alat seperti [GeoJSON.io](https://geojson.io/).

    GeoJSON perlu mengandungi `FeatureCollection`, yang mengandungi `Feature` dengan `geometry` jenis `Polygon`.

    Anda **MESTI** juga menambahkan elemen `properties` pada tahap yang sama dengan elemen `geometry`, dan ini mesti mengandungi `geometryId`:

    ```json
    "properties": {
        "geometryId": "1"
    }
    ```

    Jika anda menggunakan [GeoJSON.io](https://geojson.io/), maka anda perlu menambahkan item ini secara manual ke elemen `properties` yang kosong, sama ada selepas memuat turun fail JSON, atau dalam editor JSON dalam aplikasi.

    `geometryId` ini mesti unik dalam fail ini. Anda boleh memuat naik beberapa geopagar sebagai beberapa `Features` dalam `FeatureCollection` dalam fail GeoJSON yang sama, selagi setiap satu mempunyai `geometryId` yang berbeza. Poligon boleh mempunyai `geometryId` yang sama jika ia dimuat naik dari fail yang berbeza pada masa yang berbeza.

1. Simpan fail ini sebagai `geofence.json`, dan navigasi ke tempat ia disimpan dalam terminal atau konsol anda.

1. Jalankan arahan curl berikut untuk membuat GeoFence:

    ```sh
    curl --request POST 'https://atlas.microsoft.com/mapData/upload?api-version=1.0&dataFormat=geojson&subscription-key=<subscription_key>' \
         --header 'Content-Type: application/json' \
         --include \
         --data @geofence.json
    ```

    Gantikan `<subscription_key>` dalam URL dengan kunci API untuk akaun Azure Maps anda.

    URL digunakan untuk memuat naik data peta melalui API `https://atlas.microsoft.com/mapData/upload`. Panggilan ini termasuk parameter `api-version` untuk menentukan API Azure Maps yang digunakan, ini untuk membolehkan API berubah dari masa ke masa tetapi mengekalkan keserasian ke belakang. Format data yang dimuat naik ditetapkan kepada `geojson`.

    Ini akan menjalankan permintaan POST ke API muat naik dan mengembalikan senarai header respons yang termasuk header yang dipanggil `location`.

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

    > 🎓 Apabila memanggil titik akhir web, anda boleh menambahkan parameter ke panggilan dengan menambahkan `?` diikuti oleh pasangan kunci-nilai sebagai `key=value`, memisahkan pasangan kunci-nilai dengan `&`.

1. Azure Maps tidak memproses ini dengan segera, jadi anda perlu memeriksa untuk melihat sama ada permintaan muat naik telah selesai dengan menggunakan URL yang diberikan dalam header `location`. Buat permintaan GET ke lokasi ini untuk melihat status. Anda perlu menambahkan kunci langganan anda ke hujung URL `location` dengan menambahkan `&subscription-key=<subscription_key>` ke hujungnya, menggantikan `<subscription_key>` dengan kunci API untuk akaun Azure Maps anda. Jalankan arahan berikut:

    ```sh
    curl --request GET '<location>&subscription-key=<subscription_key>'
    ```

    Gantikan `<location>` dengan nilai header `location`, dan `<subscription_key>` dengan kunci API untuk akaun Azure Maps anda.

1. Periksa nilai `status` dalam respons. Jika ia bukan `Succeeded`, tunggu sebentar dan cuba lagi.

1. Setelah status kembali sebagai `Succeeded`, lihat pada `resourceLocation` dari respons. Ini mengandungi butiran tentang ID unik (dikenali sebagai UDID) untuk objek GeoJSON. UDID adalah nilai selepas `metadata/`, dan tidak termasuk `api-version`. Sebagai contoh, jika `resourceLocation` adalah:

    ```json
    {
      "resourceLocation": "https://us.atlas.microsoft.com/mapData/metadata/7c3776eb-da87-4c52-ae83-caadf980323a?api-version=1.0"
    }
    ```

    Maka UDID adalah `7c3776eb-da87-4c52-ae83-caadf980323a`.

    Simpan salinan UDID ini kerana anda akan memerlukannya untuk menguji geopagar.

## Menguji titik terhadap geopagar

Setelah poligon dimuat naik ke Azure Maps, anda boleh menguji titik untuk melihat sama ada ia berada di dalam atau di luar geopagar. Anda melakukan ini dengan membuat permintaan API web, menghantar UDID geopagar, dan latitud serta longitud titik untuk diuji.

Apabila anda membuat permintaan ini, anda juga boleh menghantar nilai yang dipanggil `searchBuffer`. Ini memberitahu API Peta sejauh mana ketepatan yang diperlukan apabila mengembalikan hasil. Sebabnya adalah kerana GPS tidak sempurna tepat, dan kadang-kadang lokasi boleh tersasar beberapa meter atau lebih. Lalai untuk penimbal carian adalah 50m, tetapi anda boleh menetapkan nilai dari 0m hingga 500m.

Apabila hasil dikembalikan dari panggilan API, salah satu bahagian hasil adalah `distance` yang diukur ke titik terdekat di tepi geopagar, dengan nilai positif jika titik berada di luar geopagar, nilai negatif jika ia berada di dalam geopagar. Jika jarak ini kurang daripada penimbal carian, jarak sebenar dikembalikan dalam meter, jika tidak, nilainya adalah 999 atau -999. 999 bermaksud titik berada di luar geopagar lebih daripada penimbal carian, -999 bermaksud ia berada di dalam geopagar lebih daripada penimbal carian.

![Geopagar dengan penimbal carian 50m di sekelilingnya](../../../../../translated_images/ms/search-buffer-and-distance.e6a79af3898183c7.webp)

Dalam gambar di atas, geopagar mempunyai penimbal carian 50m.

* Titik di tengah geopagar, jauh di dalam penimbal carian mempunyai jarak **-999**
* Titik jauh di luar penimbal carian mempunyai jarak **999**
* Titik di dalam geopagar dan di dalam penimbal carian, 6m dari geopagar, mempunyai jarak **6m**
* Titik di luar geopagar dan di dalam penimbal carian, 39m dari geopagar, mempunyai jarak **39m**

Adalah penting untuk mengetahui jarak ke tepi geopagar, dan menggabungkannya dengan maklumat lain seperti bacaan GPS lain, kelajuan dan data jalan raya apabila membuat keputusan berdasarkan lokasi kenderaan.

Sebagai contoh, bayangkan bacaan GPS menunjukkan kenderaan sedang memandu di sepanjang jalan yang akhirnya bersebelahan dengan geopagar. Jika satu nilai GPS tidak tepat dan meletakkan kenderaan di dalam geopagar, walaupun tiada akses kenderaan, maka ia boleh diabaikan.

![Jejak GPS menunjukkan kenderaan melalui kampus Microsoft di 520, dengan bacaan GPS di sepanjang jalan kecuali satu di kampus, di dalam geopagar](../../../../../translated_images/ms/geofence-crossing-inaccurate-gps.6a3ed911202ad9cabb66d3964888cec03a42c61d5b8f536ad5bdc99716b370f5.png)
Dalam gambar di atas, terdapat geofence yang meliputi sebahagian daripada kampus Microsoft. Garis merah menunjukkan sebuah trak yang memandu di sepanjang 520, dengan bulatan menunjukkan bacaan GPS. Kebanyakan bacaan ini adalah tepat dan berada di sepanjang 520, tetapi terdapat satu bacaan yang tidak tepat di dalam geofence. Bacaan ini tidak mungkin betul - tiada jalan untuk trak tiba-tiba menyimpang dari 520 ke dalam kampus, kemudian kembali ke 520. Kod yang memeriksa geofence ini perlu mengambil kira bacaan sebelumnya sebelum bertindak berdasarkan hasil ujian geofence.

✅ Apakah data tambahan yang anda perlukan untuk memeriksa sama ada bacaan GPS boleh dianggap betul?

### Tugasan - uji titik terhadap geofence

1. Mulakan dengan membina URL untuk pertanyaan API web. Formatnya adalah:

    ```output
    https://atlas.microsoft.com/spatial/geofence/json?api-version=1.0&deviceId=gps-sensor&subscription-key=<subscription-key>&udid=<UDID>&lat=<lat>&lon=<lon>
    ```

    Gantikan `<subscription_key>` dengan kunci API untuk akaun Azure Maps anda.

    Gantikan `<UDID>` dengan UDID geofence daripada tugasan sebelumnya.

    Gantikan `<lat>` dan `<lon>` dengan latitud dan longitud yang anda ingin uji.

    URL ini menggunakan API `https://atlas.microsoft.com/spatial/geofence/json` untuk membuat pertanyaan terhadap geofence yang ditakrifkan menggunakan GeoJSON. Ia menyasarkan versi API `1.0`. Parameter `deviceId` diperlukan dan harus menjadi nama peranti dari mana latitud dan longitud diperoleh.

    Penimbal carian lalai adalah 50m, dan anda boleh mengubahnya dengan menambahkan parameter tambahan `searchBuffer=<distance>`, menetapkan `<distance>` kepada jarak penimbal carian dalam meter, dari 0 hingga 500.

1. Gunakan curl untuk membuat permintaan GET ke URL ini:

    ```sh
    curl --request GET '<URL>'
    ```

    > 💁 Jika anda mendapat kod respons `BadRequest`, dengan ralat:
    >
    > ```output
    > Invalid GeoJSON: All feature properties should contain a geometryId, which is used for identifying the geofence.
    > ```
    >
    > maka GeoJSON anda tidak mempunyai bahagian `properties` dengan `geometryId`. Anda perlu membetulkan GeoJSON anda, kemudian ulangi langkah di atas untuk memuat naik semula dan mendapatkan UDID baharu.

1. Respons akan mengandungi senarai `geometries`, satu untuk setiap poligon yang ditakrifkan dalam GeoJSON yang digunakan untuk membuat geofence. Setiap geometri mempunyai 3 medan yang penting, `distance`, `nearestLat` dan `nearestLon`.

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

    * `nearestLat` dan `nearestLon` adalah latitud dan longitud titik di tepi geofence yang paling hampir dengan lokasi yang diuji.

    * `distance` adalah jarak dari lokasi yang diuji ke titik paling hampir di tepi geofence. Nombor negatif bermaksud di dalam geofence, nombor positif di luar. Nilai ini akan kurang daripada 50 (penimbal carian lalai), atau 999.

1. Ulangi ini beberapa kali dengan lokasi di dalam dan di luar geofence.

## Gunakan geofence daripada kod tanpa pelayan

Anda kini boleh menambah pencetus baharu pada aplikasi Functions anda untuk menguji data acara GPS IoT Hub terhadap geofence.

### Kumpulan pengguna

Seperti yang anda ingat daripada pelajaran sebelumnya, IoT Hub membolehkan anda memainkan semula acara yang telah diterima oleh hub tetapi belum diproses. Tetapi apa yang akan berlaku jika beberapa pencetus disambungkan? Bagaimana ia tahu pencetus mana yang telah memproses acara tertentu?

Jawapannya adalah ia tidak boleh! Sebaliknya, anda boleh mentakrifkan beberapa sambungan berasingan untuk membaca acara, dan setiap satu boleh menguruskan pemutaran semula mesej yang belum dibaca. Ini dipanggil *kumpulan pengguna*. Apabila anda menyambung ke titik akhir, anda boleh menentukan kumpulan pengguna mana yang anda mahu sambungkan. Setiap komponen aplikasi anda akan menyambung ke kumpulan pengguna yang berbeza.

![Satu IoT Hub dengan 3 kumpulan pengguna mengedarkan mesej yang sama kepada 3 aplikasi fungsi yang berbeza](../../../../../translated_images/ms/consumer-groups.a3262e26fc27ba2092863678ad57af15c7223416e388a23f330c058cf4358630.png)

Secara teori, sehingga 5 aplikasi boleh menyambung ke setiap kumpulan pengguna, dan semuanya akan menerima mesej apabila ia tiba. Amalan terbaik adalah hanya satu aplikasi mengakses setiap kumpulan pengguna untuk mengelakkan pemprosesan mesej yang berulang, dan memastikan apabila dimulakan semula semua mesej yang beratur diproses dengan betul. Sebagai contoh, jika anda melancarkan aplikasi Functions anda secara tempatan serta menjalankannya di awan, kedua-duanya akan memproses mesej, menyebabkan blob pendua disimpan dalam akaun storan.

Jika anda menyemak fail `function.json` untuk pencetus IoT Hub yang anda buat dalam pelajaran sebelumnya, anda akan melihat kumpulan pengguna dalam bahagian pengikatan pencetus event hub:

```json
"consumerGroup": "$Default"
```

Apabila anda mencipta IoT Hub, kumpulan pengguna `$Default` akan dicipta secara lalai. Jika anda ingin menambah pencetus tambahan, anda boleh menambah ini menggunakan kumpulan pengguna baharu.

> 💁 Dalam pelajaran ini, anda akan menggunakan fungsi yang berbeza untuk menguji geofence daripada fungsi yang digunakan untuk menyimpan data GPS. Ini adalah untuk menunjukkan cara menggunakan kumpulan pengguna dan memisahkan kod untuk memudahkan pembacaan dan pemahaman. Dalam aplikasi pengeluaran, terdapat banyak cara anda boleh merangka ini - meletakkan kedua-duanya dalam satu fungsi, menggunakan pencetus pada akaun storan untuk menjalankan fungsi untuk memeriksa geofence, atau menggunakan beberapa fungsi. Tiada 'cara yang betul', ia bergantung pada aplikasi anda yang lain dan keperluan anda.

### Tugasan - buat kumpulan pengguna baharu

1. Jalankan arahan berikut untuk membuat kumpulan pengguna baharu yang dipanggil `geofence` untuk IoT Hub anda:

    ```sh
    az iot hub consumer-group create --name geofence \
                                     --hub-name <hub_name>
    ```

    Gantikan `<hub_name>` dengan nama yang anda gunakan untuk IoT Hub anda.

1. Jika anda ingin melihat semua kumpulan pengguna untuk IoT Hub, jalankan arahan berikut:

    ```sh
    az iot hub consumer-group list --output table \
                                   --hub-name <hub_name>
    ```

    Gantikan `<hub_name>` dengan nama yang anda gunakan untuk IoT Hub anda. Ini akan menyenaraikan semua kumpulan pengguna.

    ```output
    Name      ResourceGroup
    --------  ---------------
    $Default  gps-sensor
    geofence  gps-sensor
    ```

> 💁 Apabila anda menjalankan pemantau acara IoT Hub dalam pelajaran sebelumnya, ia disambungkan ke kumpulan pengguna `$Default`. Inilah sebabnya anda tidak boleh menjalankan pemantau acara dan pencetus acara. Jika anda ingin menjalankan kedua-duanya, maka anda boleh menggunakan kumpulan pengguna lain untuk semua aplikasi fungsi anda, dan mengekalkan `$Default` untuk pemantau acara.

### Tugasan - buat pencetus IoT Hub baharu

1. Tambahkan pencetus acara IoT Hub baharu pada aplikasi fungsi `gps-trigger` yang anda buat dalam pelajaran sebelumnya. Namakan fungsi ini `geofence-trigger`.

    > ⚠️ Anda boleh merujuk kepada [arahan untuk membuat pencetus acara IoT Hub daripada projek 2, pelajaran 5 jika diperlukan](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger).

1. Konfigurasikan rentetan sambungan IoT Hub dalam fail `function.json`. Fail `local.settings.json` dikongsi antara semua pencetus dalam Aplikasi Fungsi.

1. Kemas kini nilai `consumerGroup` dalam fail `function.json` untuk merujuk kepada kumpulan pengguna `geofence` yang baharu:

    ```json
    "consumerGroup": "geofence"
    ```

1. Anda perlu menggunakan kunci langganan untuk akaun Azure Maps anda dalam pencetus ini, jadi tambahkan entri baharu ke fail `local.settings.json` yang dipanggil `MAPS_KEY`.

1. Jalankan Aplikasi Fungsi untuk memastikan ia menyambung dan memproses mesej. Pencetus `iot-hub-trigger` daripada pelajaran sebelumnya juga akan berjalan dan memuat naik blob ke storan.

    > Untuk mengelakkan bacaan GPS pendua dalam storan blob, anda boleh menghentikan Aplikasi Fungsi yang anda jalankan di awan. Untuk melakukan ini, gunakan arahan berikut:
    >
    > ```sh
    > az functionapp stop --resource-group gps-sensor \
    >                     --name <functions_app_name>
    > ```
    >
    > Gantikan `<functions_app_name>` dengan nama yang anda gunakan untuk Aplikasi Fungsi anda.
    >
    > Anda boleh memulakannya semula kemudian dengan arahan berikut:
    >
    > ```sh
    > az functionapp start --resource-group gps-sensor \
    >                     --name <functions_app_name>
    > ```
    >
    > Gantikan `<functions_app_name>` dengan nama yang anda gunakan untuk Aplikasi Fungsi anda.

### Tugasan - uji geofence daripada pencetus

Sebelum ini dalam pelajaran ini anda menggunakan curl untuk membuat pertanyaan terhadap geofence untuk melihat sama ada satu titik terletak di dalam atau di luar. Anda boleh membuat permintaan web yang serupa dari dalam pencetus anda.

1. Untuk membuat pertanyaan terhadap geofence, anda memerlukan UDID-nya. Tambahkan entri baharu ke fail `local.settings.json` yang dipanggil `GEOFENCE_UDID` dengan nilai ini.

1. Buka fail `__init__.py` daripada pencetus `geofence-trigger` yang baharu.

1. Tambahkan import berikut ke bahagian atas fail:

    ```python
    import json
    import os
    import requests
    ```

    Pakej `requests` membolehkan anda membuat panggilan API web. Azure Maps tidak mempunyai SDK Python, anda perlu membuat panggilan API web untuk menggunakannya daripada kod Python.

1. Tambahkan dua baris berikut ke permulaan kaedah `main` untuk mendapatkan kunci langganan Peta:

    ```python
    maps_key = os.environ['MAPS_KEY']
    geofence_udid = os.environ['GEOFENCE_UDID']    
    ```

1. Di dalam gelung `for event in events`, tambahkan yang berikut untuk mendapatkan latitud dan longitud daripada setiap acara:

    ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    lat = event_body['gps']['lat']
    lon = event_body['gps']['lon']
    ```

    Kod ini menukar JSON daripada badan acara kepada kamus, kemudian mengekstrak `lat` dan `lon` daripada medan `gps`.

1. Apabila menggunakan `requests`, daripada membina URL panjang seperti yang anda lakukan dengan curl, anda boleh menggunakan hanya bahagian URL dan menghantar parameter sebagai kamus. Tambahkan kod berikut untuk mentakrifkan URL untuk dipanggil dan mengkonfigurasi parameter:

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

    Item dalam kamus `params` akan sepadan dengan pasangan kunci nilai yang anda gunakan semasa memanggil API web melalui curl.

1. Tambahkan baris kod berikut untuk memanggil API web:

    ```python
    response = requests.get(url, params=params)
    response_body = json.loads(response.text)
    ```

    Ini memanggil URL dengan parameter, dan mendapatkan objek respons.

1. Tambahkan kod berikut di bawah ini:

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

    Kod ini mengandaikan 1 geometri, dan mengekstrak jarak daripada geometri tunggal itu. Ia kemudian log mesej yang berbeza berdasarkan jarak.

1. Jalankan kod ini. Anda akan melihat dalam output log sama ada koordinat GPS berada di dalam atau di luar geofence, dengan jarak jika titik berada dalam 50m. Cuba kod ini dengan geofence yang berbeza berdasarkan lokasi sensor GPS anda, cuba gerakkan sensor (contohnya disambungkan ke WiFi daripada telefon bimbit, atau dengan koordinat yang berbeza pada peranti IoT maya) untuk melihat perubahan ini.

1. Apabila anda sudah bersedia, gunakan kod ini ke aplikasi Functions anda di awan. Jangan lupa untuk menggunakan Tetapan Aplikasi yang baharu.

    > ⚠️ Anda boleh merujuk kepada [arahan untuk memuat naik Tetapan Aplikasi daripada projek 2, pelajaran 5 jika diperlukan](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings).

    > ⚠️ Anda boleh merujuk kepada [arahan untuk menggunakan aplikasi Functions anda daripada projek 2, pelajaran 5 jika diperlukan](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud).

> 💁 Anda boleh menemui kod ini dalam folder [code/functions](../../../../../3-transport/lessons/4-geofences/code/functions).

---

## 🚀 Cabaran

Dalam pelajaran ini anda menambah satu geofence menggunakan fail GeoJSON dengan satu poligon. Anda boleh memuat naik beberapa poligon pada masa yang sama, selagi ia mempunyai nilai `geometryId` yang berbeza dalam bahagian `properties`.

Cuba muat naik fail GeoJSON dengan beberapa poligon dan sesuaikan kod anda untuk mencari poligon mana yang paling hampir atau di dalam koordinat GPS.

## Kuiz selepas kuliah

[Kuiz selepas kuliah](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/28)

## Kajian & Pembelajaran Kendiri

* Baca lebih lanjut tentang geofence dan beberapa kegunaannya di [halaman Geofencing di Wikipedia](https://en.wikipedia.org/wiki/Geo-fence).
* Baca lebih lanjut tentang API geofencing Azure Maps di [dokumentasi Microsoft Azure Maps Spatial - Get Geofence](https://docs.microsoft.com/rest/api/maps/spatial/getgeofence?WT.mc_id=academic-17441-jabenn).
* Baca lebih lanjut tentang kumpulan pengguna dalam [Ciri dan istilah dalam Azure Event Hubs - dokumentasi pengguna acara di Microsoft docs](https://docs.microsoft.com/azure/event-hubs/event-hubs-features?WT.mc_id=academic-17441-jabenn#event-consumers).

## Tugasan

[Hantar pemberitahuan menggunakan Twilio](assignment.md)

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.