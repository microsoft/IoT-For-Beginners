<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "52ed2bd997d08040f79a1a6ef2bac958",
  "translation_date": "2025-08-27T23:42:27+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/README.md",
  "language_code": "id"
}
-->
# Pelacakan Lokasi

![Gambaran sketchnote dari pelajaran ini](../../../../../translated_images/id/lesson-11.9fddbac4b664c6d50ab7ac9bb32f1fc3f945f03760e72f7f43938073762fb017.jpg)

> Sketchnote oleh [Nitya Narasimhan](https://github.com/nitya). Klik gambar untuk versi yang lebih besar.

## Kuis Pra-Kuliah

[Kuis Pra-Kuliah](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/21)

## Pendahuluan

Proses utama untuk mengirimkan makanan dari petani ke konsumen melibatkan pemuatan kotak hasil panen ke truk, kapal, pesawat, atau kendaraan transportasi komersial lainnya, dan mengantarkan makanan tersebut ke suatu tempat - baik langsung ke pelanggan, atau ke pusat distribusi atau gudang untuk diproses. Seluruh proses dari awal hingga akhir, dari petani ke konsumen, adalah bagian dari proses yang disebut *rantai pasokan*. Video di bawah ini dari W. P. Carey School of Business di Arizona State University menjelaskan lebih lanjut tentang konsep rantai pasokan dan bagaimana pengelolaannya.

[![Apa itu Manajemen Rantai Pasokan? Video dari W. P. Carey School of Business di Arizona State University](https://img.youtube.com/vi/Mi1QBxVjZAw/0.jpg)](https://www.youtube.com/watch?v=Mi1QBxVjZAw)

> 🎥 Klik gambar di atas untuk menonton video

Menambahkan perangkat IoT dapat secara drastis meningkatkan rantai pasokan Anda, memungkinkan Anda mengelola lokasi barang, merencanakan transportasi dan penanganan barang dengan lebih baik, serta merespons masalah dengan lebih cepat.

Ketika mengelola armada kendaraan seperti truk, sangat membantu untuk mengetahui di mana setiap kendaraan berada pada waktu tertentu. Kendaraan dapat dilengkapi dengan sensor GPS yang mengirimkan lokasinya ke sistem IoT, memungkinkan pemilik untuk mengetahui lokasi kendaraan, melihat rute yang telah dilalui, dan mengetahui kapan kendaraan akan tiba di tujuan. Sebagian besar kendaraan beroperasi di luar jangkauan WiFi, sehingga mereka menggunakan jaringan seluler untuk mengirimkan data semacam ini. Kadang-kadang sensor GPS terintegrasi dalam perangkat IoT yang lebih kompleks seperti buku catatan elektronik. Perangkat ini melacak berapa lama truk telah dalam perjalanan untuk memastikan pengemudi mematuhi peraturan lokal tentang jam kerja.

Dalam pelajaran ini, Anda akan belajar cara melacak lokasi kendaraan menggunakan sensor Sistem Pemosisian Global (GPS).

Dalam pelajaran ini, kita akan membahas:

* [Kendaraan yang terhubung](../../../../../3-transport/lessons/1-location-tracking)
* [Koordinat geospasial](../../../../../3-transport/lessons/1-location-tracking)
* [Sistem Pemosisian Global (GPS)](../../../../../3-transport/lessons/1-location-tracking)
* [Membaca data sensor GPS](../../../../../3-transport/lessons/1-location-tracking)
* [Data GPS NMEA](../../../../../3-transport/lessons/1-location-tracking)
* [Mendekode data sensor GPS](../../../../../3-transport/lessons/1-location-tracking)

## Kendaraan yang Terhubung

IoT mengubah cara barang diangkut dengan menciptakan armada *kendaraan yang terhubung*. Kendaraan ini terhubung ke sistem TI pusat yang melaporkan informasi tentang lokasi mereka, serta data sensor lainnya. Memiliki armada kendaraan yang terhubung memberikan berbagai manfaat:

* Pelacakan lokasi - Anda dapat mengetahui lokasi kendaraan kapan saja, memungkinkan Anda untuk:

  * Mendapatkan pemberitahuan ketika kendaraan hampir tiba di tujuan untuk mempersiapkan kru pembongkaran
  * Menemukan kendaraan yang dicuri
  * Menggabungkan data lokasi dan rute dengan masalah lalu lintas untuk memungkinkan Anda mengalihkan rute kendaraan di tengah perjalanan
  * Mematuhi pajak. Beberapa negara mengenakan biaya pada kendaraan berdasarkan jarak tempuh di jalan umum (seperti [RUC Selandia Baru](https://www.nzta.govt.nz/vehicles/licensing-rego/road-user-charges/)), sehingga mengetahui kapan kendaraan berada di jalan umum vs jalan pribadi memudahkan perhitungan pajak yang harus dibayar.
  * Mengetahui di mana harus mengirim kru perbaikan jika terjadi kerusakan

* Telemetri pengemudi - Memastikan pengemudi mematuhi batas kecepatan, menikung dengan kecepatan yang sesuai, mengerem lebih awal dan efisien, serta mengemudi dengan aman. Kendaraan yang terhubung juga dapat dilengkapi kamera untuk merekam insiden. Ini dapat dikaitkan dengan asuransi, memberikan tarif yang lebih rendah untuk pengemudi yang baik.

* Kepatuhan jam kerja pengemudi - Memastikan pengemudi hanya mengemudi selama jam kerja yang diizinkan secara hukum berdasarkan waktu mesin dinyalakan dan dimatikan.

Manfaat ini dapat digabungkan - misalnya, menggabungkan kepatuhan jam kerja pengemudi dengan pelacakan lokasi untuk mengalihkan rute pengemudi jika mereka tidak dapat mencapai tujuan dalam jam kerja yang diizinkan. Ini juga dapat digabungkan dengan telemetri kendaraan lainnya, seperti data suhu dari truk berpendingin, memungkinkan kendaraan untuk dialihkan jika rute saat ini akan menyebabkan barang tidak dapat disimpan pada suhu yang sesuai.

> 🎓 Logistik adalah proses mengangkut barang dari satu tempat ke tempat lain, seperti dari petani ke supermarket melalui satu atau lebih gudang. Seorang petani mengemas kotak tomat yang dimuat ke truk, dikirim ke gudang pusat, dan dimuat ke truk kedua yang mungkin berisi campuran berbagai jenis hasil panen yang kemudian dikirim ke supermarket.

Komponen inti dari pelacakan kendaraan adalah GPS - sensor yang dapat menentukan lokasi mereka di mana saja di Bumi. Dalam pelajaran ini, Anda akan belajar cara menggunakan sensor GPS, dimulai dengan mempelajari cara mendefinisikan lokasi di Bumi.

## Koordinat Geospasial

Koordinat geospasial digunakan untuk menentukan titik-titik di permukaan Bumi, mirip dengan bagaimana koordinat dapat digunakan untuk menggambar piksel di layar komputer atau memposisikan jahitan dalam bordir silang. Untuk satu titik, Anda memiliki sepasang koordinat. Sebagai contoh, Kampus Microsoft di Redmond, Washington, AS terletak di 47.6423109, -122.1390293.

### Lintang dan Bujur

Bumi adalah sebuah bola - lingkaran tiga dimensi. Karena itu, titik-titik didefinisikan dengan membaginya menjadi 360 derajat, sama seperti geometri lingkaran. Lintang mengukur jumlah derajat dari utara ke selatan, bujur mengukur jumlah derajat dari timur ke barat.

> 💁 Tidak ada yang benar-benar tahu alasan asli mengapa lingkaran dibagi menjadi 360 derajat. Halaman [derajat (sudut) di Wikipedia](https://wikipedia.org/wiki/Degree_(angle)) mencakup beberapa kemungkinan alasannya.

![Garis lintang dari 90° di Kutub Utara, 45° di tengah antara Kutub Utara dan ekuator, 0° di ekuator, -45° di tengah antara ekuator dan Kutub Selatan, dan -90° di Kutub Selatan](../../../../../translated_images/id/latitude-lines.11d8d91dfb2014a57437272d7db7fd6607243098e8685f06e0c5f1ec984cb7eb.png)

Lintang diukur menggunakan garis-garis yang melingkari Bumi dan sejajar dengan ekuator, membagi Belahan Bumi Utara dan Selatan menjadi masing-masing 90°. Ekuator berada di 0°, Kutub Utara di 90°, juga dikenal sebagai 90° Utara, dan Kutub Selatan di -90°, atau 90° Selatan.

Bujur diukur sebagai jumlah derajat yang diukur ke timur dan barat. Titik asal 0° bujur disebut *Meridian Utama*, dan didefinisikan pada tahun 1884 sebagai garis dari Kutub Utara ke Kutub Selatan yang melewati [Observatorium Kerajaan Inggris di Greenwich, Inggris](https://wikipedia.org/wiki/Royal_Observatory,_Greenwich).

![Garis bujur yang membentang dari -180° di barat Meridian Utama, ke 0° di Meridian Utama, hingga 180° di timur Meridian Utama](../../../../../translated_images/id/longitude-meridians.ab4ef1c91c064586b0185a3c8d39e585903696c6a7d28c098a93a629cddb5d20.png)

> 🎓 Sebuah meridian adalah garis lurus imajiner yang membentang dari Kutub Utara ke Kutub Selatan, membentuk setengah lingkaran.

Untuk mengukur bujur suatu titik, Anda mengukur jumlah derajat di sekitar ekuator dari Meridian Utama ke meridian yang melewati titik tersebut. Bujur berkisar dari -180°, atau 180° Barat, melalui 0° di Meridian Utama, hingga 180°, atau 180° Timur. 180° dan -180° merujuk pada titik yang sama, yaitu antimeridian atau meridian ke-180. Ini adalah meridian di sisi Bumi yang berlawanan dengan Meridian Utama.

> 💁 Antimeridian tidak sama dengan Garis Tanggal Internasional, yang berada di posisi yang hampir sama, tetapi tidak berupa garis lurus dan bervariasi untuk menyesuaikan dengan batas-batas geopolitik.

✅ Lakukan penelitian: Coba temukan lintang dan bujur lokasi Anda saat ini.

### Derajat, Menit, dan Detik vs Derajat Desimal

Secara tradisional, pengukuran derajat lintang dan bujur dilakukan menggunakan sistem penomoran seksagesimal, atau basis-60, sistem penomoran yang digunakan oleh Bangsa Babilonia Kuno yang pertama kali melakukan pengukuran dan pencatatan waktu serta jarak. Anda mungkin menggunakan sistem seksagesimal setiap hari tanpa menyadarinya - membagi jam menjadi 60 menit dan menit menjadi 60 detik.

Bujur dan lintang diukur dalam derajat, menit, dan detik, dengan satu menit setara dengan 1/60 derajat, dan 1 detik setara dengan 1/60 menit.

Sebagai contoh, di ekuator:

* 1° lintang adalah **111,3 kilometer**
* 1 menit lintang adalah 111,3/60 = **1,855 kilometer**
* 1 detik lintang adalah 1,855/60 = **0,031 kilometer**

Simbol untuk menit adalah tanda kutip tunggal, untuk detik adalah tanda kutip ganda. Sebagai contoh, 2 derajat, 17 menit, dan 43 detik akan ditulis sebagai 2°17'43". Bagian dari detik diberikan sebagai desimal, misalnya setengah detik adalah 0°0'0.5".

Komputer tidak bekerja dalam basis-60, sehingga koordinat ini diberikan sebagai derajat desimal saat menggunakan data GPS di sebagian besar sistem komputer. Sebagai contoh, 2°17'43" adalah 2.295277. Simbol derajat biasanya dihilangkan.

Koordinat untuk suatu titik selalu diberikan sebagai `lintang, bujur`, sehingga contoh sebelumnya dari Kampus Microsoft di 47.6423109,-122.117198 memiliki:

* Lintang 47.6423109 (47.6423109 derajat di utara ekuator)
* Bujur -122.1390293 (122.1390293 derajat di barat Meridian Utama).

![Kampus Microsoft di 47.6423109,-122.117198](../../../../../translated_images/id/microsoft-gps-location-world.a321d481b010f6adfcca139b2ba0adc53b79f58a540495b8e2ce7f779ea64bfe.png)

## Sistem Pemosisian Global (GPS)

Sistem GPS menggunakan beberapa satelit yang mengorbit Bumi untuk menentukan posisi Anda. Anda mungkin pernah menggunakan sistem GPS tanpa menyadarinya - untuk menemukan lokasi Anda di aplikasi peta di ponsel seperti Apple Maps atau Google Maps, atau untuk melihat di mana kendaraan Anda berada di aplikasi pemesanan kendaraan seperti Uber atau Lyft, atau saat menggunakan navigasi satelit (sat-nav) di mobil Anda.

> 🎓 Satelit dalam 'navigasi satelit' adalah satelit GPS!

Sistem GPS bekerja dengan memiliki sejumlah satelit yang mengirimkan sinyal dengan posisi masing-masing satelit saat ini, dan stempel waktu yang akurat. Sinyal ini dikirim melalui gelombang radio dan dideteksi oleh antena di sensor GPS. Sensor GPS akan mendeteksi sinyal ini, dan menggunakan waktu saat ini untuk mengukur berapa lama waktu yang dibutuhkan sinyal untuk mencapai sensor dari satelit. Karena kecepatan gelombang radio konstan, sensor GPS dapat menggunakan stempel waktu yang dikirim untuk menghitung seberapa jauh sensor dari satelit. Dengan menggabungkan data dari setidaknya 3 satelit dengan posisi yang dikirimkan, sensor GPS dapat menentukan lokasinya di Bumi.

> 💁 Sensor GPS memerlukan antena untuk mendeteksi gelombang radio. Antena yang terpasang di truk dan mobil dengan GPS bawaan diposisikan untuk mendapatkan sinyal yang baik, biasanya di kaca depan atau atap. Jika Anda menggunakan sistem GPS terpisah, seperti ponsel pintar atau perangkat IoT, maka Anda perlu memastikan bahwa antena yang terpasang di sistem GPS atau ponsel memiliki pandangan yang jelas ke langit, seperti dipasang di kaca depan.

![Dengan mengetahui jarak dari sensor ke beberapa satelit, lokasi dapat dihitung](../../../../../translated_images/id/gps-satellites.04acf1148fe25fbf1586bc2e8ba698e8d79b79a50c36824b38417dd13372b90f.png)

Satelit GPS mengelilingi Bumi, tidak berada di titik tetap di atas sensor, sehingga data lokasi mencakup ketinggian di atas permukaan laut serta lintang dan bujur.

GPS dulunya memiliki keterbatasan akurasi yang diberlakukan oleh militer AS, membatasi akurasi hingga sekitar 5 meter. Keterbatasan ini dihapus pada tahun 2000, memungkinkan akurasi hingga 30 sentimeter. Mendapatkan akurasi ini tidak selalu memungkinkan karena gangguan pada sinyal.

✅ Jika Anda memiliki ponsel pintar, buka aplikasi peta dan lihat seberapa akurat lokasi Anda. Mungkin perlu beberapa saat bagi ponsel Anda untuk mendeteksi beberapa satelit untuk mendapatkan lokasi yang lebih akurat.
💁 Satelit-satelit tersebut memiliki jam atom yang sangat akurat, tetapi mereka melenceng sebesar 38 mikrodetik (0,0000038 detik) per hari dibandingkan dengan jam atom di Bumi, karena waktu melambat seiring dengan meningkatnya kecepatan seperti yang diprediksi oleh teori relativitas khusus dan umum Einstein - satelit-satelit tersebut bergerak lebih cepat daripada rotasi Bumi. Penyimpangan ini telah digunakan untuk membuktikan prediksi relativitas khusus dan umum, dan harus disesuaikan dalam desain sistem GPS. Secara harfiah, waktu berjalan lebih lambat di satelit GPS.
Sistem GPS telah dikembangkan dan digunakan oleh sejumlah negara dan serikat politik termasuk AS, Rusia, Jepang, India, Uni Eropa, dan China. Sensor GPS modern dapat terhubung ke sebagian besar sistem ini untuk mendapatkan lokasi yang lebih cepat dan akurat.

> 🎓 Kelompok satelit dalam setiap sistem disebut sebagai konstelasi.

## Membaca data sensor GPS

Sebagian besar sensor GPS mengirimkan data GPS melalui UART.

> ⚠️ UART telah dibahas di [proyek 2, pelajaran 2](../../../2-farm/lessons/2-detect-soil-moisture/README.md#universal-asynchronous-receiver-transmitter-uart). Kembali ke pelajaran tersebut jika diperlukan.

Anda dapat menggunakan sensor GPS pada perangkat IoT Anda untuk mendapatkan data GPS.

### Tugas - menghubungkan sensor GPS dan membaca data GPS

Ikuti panduan yang relevan untuk membaca data GPS menggunakan perangkat IoT Anda:

* [Arduino - Wio Terminal](wio-terminal-gps-sensor.md)
* [Komputer papan tunggal - Raspberry Pi](pi-gps-sensor.md)
* [Komputer papan tunggal - Perangkat virtual](virtual-device-gps-sensor.md)

## Data GPS NMEA

Saat Anda menjalankan kode Anda, Anda mungkin melihat sesuatu yang tampak seperti kode acak di output. Ini sebenarnya adalah data GPS standar, dan semuanya memiliki arti.

Sensor GPS mengeluarkan data menggunakan pesan NMEA, sesuai dengan standar NMEA 0183. NMEA adalah singkatan dari [National Marine Electronics Association](https://www.nmea.org), sebuah organisasi perdagangan berbasis di AS yang menetapkan standar komunikasi antar perangkat elektronik kelautan.

> 💁 Standar ini bersifat proprietary dan dijual dengan harga setidaknya US$2,000, tetapi cukup banyak informasi tentangnya yang tersedia di domain publik sehingga sebagian besar standar telah direkayasa balik dan dapat digunakan dalam kode sumber terbuka dan non-komersial lainnya.

Pesan-pesan ini berbasis teks. Setiap pesan terdiri dari *kalimat* yang dimulai dengan karakter `$`, diikuti oleh 2 karakter untuk menunjukkan sumber pesan (misalnya GP untuk sistem GPS AS, GN untuk GLONASS, sistem GPS Rusia), dan 3 karakter untuk menunjukkan jenis pesan. Sisa pesan adalah bidang-bidang yang dipisahkan oleh koma, diakhiri dengan karakter baris baru.

Beberapa jenis pesan yang dapat diterima adalah:

| Jenis | Deskripsi |
| ---- | ----------- |
| GGA | Data Fix GPS, termasuk lintang, bujur, dan ketinggian sensor GPS, bersama dengan jumlah satelit yang terlihat untuk menghitung lokasi ini. |
| ZDA | Tanggal dan waktu saat ini, termasuk zona waktu lokal |
| GSV | Detail satelit yang terlihat - didefinisikan sebagai satelit yang dapat dideteksi sinyalnya oleh sensor GPS |

> 💁 Data GPS mencakup cap waktu, sehingga perangkat IoT Anda dapat mendapatkan waktu jika diperlukan dari sensor GPS, daripada mengandalkan server NTP atau jam waktu nyata internal.

Pesan GGA mencakup lokasi saat ini menggunakan format `(dd)dmm.mmmm`, bersama dengan satu karakter untuk menunjukkan arah. `d` dalam format adalah derajat, `m` adalah menit, dengan detik sebagai desimal dari menit. Misalnya, 2°17'43" akan menjadi 217.716666667 - 2 derajat, 17.716666667 menit.

Karakter arah dapat berupa `N` atau `S` untuk lintang untuk menunjukkan utara atau selatan, dan `E` atau `W` untuk bujur untuk menunjukkan timur atau barat. Misalnya, lintang 2°17'43" akan memiliki karakter arah `N`, -2°17'43" akan memiliki karakter arah `S`.

Sebagai contoh - kalimat NMEA `$GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67`

* Bagian lintang adalah `4738.538654,N`, yang dikonversi menjadi 47.6423109 dalam derajat desimal. `4738.538654` adalah 47.6423109, dan arah adalah `N` (utara), sehingga lintang positif.

* Bagian bujur adalah `12208.341758,W`, yang dikonversi menjadi -122.1390293 dalam derajat desimal. `12208.341758` adalah 122.1390293°, dan arah adalah `W` (barat), sehingga bujur negatif.

## Mendekode data sensor GPS

Daripada menggunakan data NMEA mentah, lebih baik mendekodenya ke format yang lebih berguna. Ada banyak pustaka sumber terbuka yang dapat Anda gunakan untuk membantu mengekstrak data berguna dari pesan NMEA mentah.

### Tugas - mendekode data sensor GPS

Ikuti panduan yang relevan untuk mendekode data sensor GPS menggunakan perangkat IoT Anda:

* [Arduino - Wio Terminal](wio-terminal-gps-decode.md)
* [Komputer papan tunggal - Raspberry Pi/Perangkat IoT virtual](single-board-computer-gps-decode.md)

---

## 🚀 Tantangan

Tulis decoder NMEA Anda sendiri! Daripada mengandalkan pustaka pihak ketiga untuk mendekode kalimat NMEA, bisakah Anda menulis decoder Anda sendiri untuk mengekstrak lintang dan bujur dari kalimat NMEA?

## Kuis setelah pelajaran

[Kuis setelah pelajaran](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/22)

## Tinjauan & Studi Mandiri

* Baca lebih lanjut tentang Koordinat Geospasial di [halaman sistem koordinat geografis di Wikipedia](https://wikipedia.org/wiki/Geographic_coordinate_system).
* Pelajari tentang Meridian Utama pada benda langit selain Bumi di [halaman Meridian Utama di Wikipedia](https://wikipedia.org/wiki/Prime_meridian#Prime_meridian_on_other_planetary_bodies)
* Teliti berbagai sistem GPS dari berbagai pemerintah dunia dan serikat politik seperti Uni Eropa, Jepang, Rusia, India, dan AS.

## Tugas

[Selidiki data GPS lainnya](assignment.md)

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.