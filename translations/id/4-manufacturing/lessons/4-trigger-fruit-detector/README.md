<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f74f4ccb61f00e5f7e9f49c3ed416e36",
  "translation_date": "2025-08-27T21:15:43+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/README.md",
  "language_code": "id"
}
-->
# Memicu Deteksi Kualitas Buah dari Sensor

![Gambaran sketchnote dari pelajaran ini](../../../../../translated_images/lesson-18.92c32ed1d354caa5a54baa4032cf0b172d4655e8e326ad5d46c558a0def15365.id.jpg)

> Sketchnote oleh [Nitya Narasimhan](https://github.com/nitya). Klik gambar untuk versi yang lebih besar.

## Kuis Pra-Pelajaran

[Kuis Pra-Pelajaran](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/35)

## Pendahuluan

Aplikasi IoT bukan hanya satu perangkat yang menangkap data dan mengirimkannya ke cloud, tetapi sering kali melibatkan banyak perangkat yang bekerja bersama untuk menangkap data dari dunia fisik menggunakan sensor, membuat keputusan berdasarkan data tersebut, dan berinteraksi kembali dengan dunia fisik melalui aktuator atau visualisasi.

Dalam pelajaran ini, Anda akan mempelajari lebih lanjut tentang merancang aplikasi IoT yang kompleks, mengintegrasikan beberapa sensor, beberapa layanan cloud untuk menganalisis dan menyimpan data, serta menunjukkan respons melalui aktuator. Anda akan belajar bagaimana merancang prototipe sistem kontrol kualitas buah, termasuk penggunaan sensor jarak untuk memicu aplikasi IoT, dan seperti apa arsitektur prototipe ini.

Dalam pelajaran ini, kita akan membahas:

* [Merancang aplikasi IoT yang kompleks](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Merancang sistem kontrol kualitas buah](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Memicu pemeriksaan kualitas buah dari sensor](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Data yang digunakan untuk detektor kualitas buah](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Menggunakan perangkat pengembang untuk mensimulasikan beberapa perangkat IoT](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Berpindah ke produksi](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)

> 🗑 Ini adalah pelajaran terakhir dalam proyek ini, jadi setelah menyelesaikan pelajaran dan tugas ini, jangan lupa untuk membersihkan layanan cloud Anda. Anda akan membutuhkan layanan tersebut untuk menyelesaikan tugas, jadi pastikan untuk menyelesaikannya terlebih dahulu.
>
> Lihat [panduan membersihkan proyek Anda](../../../clean-up.md) jika diperlukan untuk instruksi tentang cara melakukannya.

## Merancang Aplikasi IoT yang Kompleks

Aplikasi IoT terdiri dari banyak komponen. Ini mencakup berbagai hal dan berbagai layanan internet.

Aplikasi IoT dapat digambarkan sebagai *things* (perangkat) yang mengirimkan data yang menghasilkan *insights*. *Insights* ini menghasilkan *actions* untuk meningkatkan bisnis atau proses. Contohnya adalah mesin (thing) yang mengirimkan data suhu. Data ini digunakan untuk mengevaluasi apakah mesin bekerja sesuai harapan (*insight*). *Insight* ini digunakan untuk memprioritaskan jadwal perawatan mesin secara proaktif (*action*).

* Perangkat yang berbeda mengumpulkan potongan data yang berbeda.
* Layanan IoT memberikan wawasan atas data tersebut, terkadang melengkapinya dengan data dari sumber tambahan.
* Wawasan ini mendorong tindakan, termasuk mengontrol aktuator di perangkat, atau memvisualisasikan data.

### Arsitektur Referensi IoT

![Arsitektur referensi IoT](../../../../../translated_images/iot-reference-architecture.2278b98b55c6d4e89bde18eada3688d893861d43507641804dd2f9d3079cfaa0.id.png)

Diagram di atas menunjukkan arsitektur referensi IoT.

> 🎓 *Arsitektur referensi* adalah contoh arsitektur yang dapat Anda gunakan sebagai acuan saat merancang sistem baru. Dalam hal ini, jika Anda membangun sistem IoT baru, Anda dapat mengikuti arsitektur referensi, mengganti perangkat dan layanan Anda sendiri sesuai kebutuhan.

* **Things** adalah perangkat yang mengumpulkan data dari sensor, mungkin berinteraksi dengan layanan edge untuk menafsirkan data tersebut, seperti pengklasifikasi gambar untuk menafsirkan data gambar. Data dari perangkat dikirim ke layanan IoT.
* **Insights** berasal dari aplikasi tanpa server, atau dari analisis yang dijalankan pada data yang disimpan.
* **Actions** dapat berupa perintah yang dikirim ke perangkat, atau visualisasi data yang memungkinkan manusia membuat keputusan.

![Arsitektur referensi IoT di Azure](../../../../../translated_images/iot-reference-architecture-azure.0b8d2161af924cb18ae48a8558a19541cca47f27264851b5b7e56d7b8bb372ac.id.png)

Diagram di atas menunjukkan beberapa komponen dan layanan yang telah dibahas sejauh ini dalam pelajaran ini dan bagaimana mereka terhubung dalam arsitektur referensi IoT.

* **Things** - Anda telah menulis kode perangkat untuk menangkap data dari sensor, dan menganalisis gambar menggunakan Custom Vision yang berjalan baik di cloud maupun di perangkat edge. Data ini dikirim ke IoT Hub.
* **Insights** - Anda telah menggunakan Azure Functions untuk merespons pesan yang dikirim ke IoT Hub, dan menyimpan data untuk analisis lebih lanjut di Azure Storage.
* **Actions** - Anda telah mengontrol aktuator berdasarkan keputusan yang dibuat di cloud dan perintah yang dikirim ke perangkat, serta memvisualisasikan data menggunakan Azure Maps.

✅ Pikirkan tentang perangkat IoT lain yang pernah Anda gunakan, seperti peralatan rumah pintar. Apa saja *things*, *insights*, dan *actions* yang terlibat dalam perangkat dan perangkat lunaknya?

Pola ini dapat diskalakan sebesar atau sekecil yang Anda butuhkan, dengan menambahkan lebih banyak perangkat dan layanan.

### Data dan Keamanan

Saat Anda mendefinisikan arsitektur sistem Anda, Anda perlu terus mempertimbangkan data dan keamanan.

* Data apa yang dikirim dan diterima perangkat Anda?
* Bagaimana data tersebut harus diamankan dan dilindungi?
* Bagaimana akses ke perangkat dan layanan cloud harus dikontrol?

✅ Pikirkan tentang keamanan data dari perangkat IoT yang Anda miliki. Seberapa banyak data tersebut bersifat pribadi dan harus dijaga kerahasiaannya, baik saat dikirim maupun saat disimpan? Data apa yang tidak boleh disimpan?

## Merancang Sistem Kontrol Kualitas Buah

Sekarang mari kita terapkan konsep *things*, *insights*, dan *actions* ini pada detektor kualitas buah untuk merancang aplikasi ujung-ke-ujung yang lebih besar.

Bayangkan Anda diberi tugas untuk membangun detektor kualitas buah yang akan digunakan di pabrik pengolahan. Buah bergerak di atas sistem ban berjalan di mana saat ini karyawan memeriksa buah secara manual dan mengeluarkan buah yang belum matang saat tiba. Untuk mengurangi biaya, pemilik pabrik menginginkan sistem otomatis.

✅ Salah satu tren dengan meningkatnya IoT (dan teknologi secara umum) adalah pekerjaan manual digantikan oleh mesin. Lakukan penelitian: Berapa banyak pekerjaan yang diperkirakan akan hilang karena IoT? Berapa banyak pekerjaan baru yang akan tercipta untuk membangun perangkat IoT?

Anda perlu membangun sistem di mana buah terdeteksi saat tiba di ban berjalan, kemudian difoto dan diperiksa menggunakan model AI yang berjalan di perangkat edge. Hasilnya kemudian dikirim ke cloud untuk disimpan, dan jika buah belum matang, notifikasi diberikan agar buah yang belum matang dapat dikeluarkan.

|   |   |
| - | - |
| **Things** | Detektor untuk mendeteksi buah yang tiba di ban berjalan<br>Kamera untuk memotret dan mengklasifikasikan buah<br>Perangkat edge yang menjalankan pengklasifikasi<br>Perangkat untuk memberi notifikasi tentang buah yang belum matang |
| **Insights** | Memutuskan untuk memeriksa kematangan buah<br>Menyimpan hasil klasifikasi kematangan<br>Menentukan apakah perlu memberi peringatan tentang buah yang belum matang |
| **Actions** | Mengirim perintah ke perangkat untuk memotret buah dan memeriksanya dengan pengklasifikasi gambar<br>Mengirim perintah ke perangkat untuk memberi peringatan bahwa buah belum matang |

### Membuat Prototipe Aplikasi Anda

![Arsitektur referensi IoT untuk pemeriksaan kualitas buah](../../../../../translated_images/iot-reference-architecture-fruit-quality.cc705f121c3b6fa71c800d9630935ac34bc08223a04601e35f41d5e9b5dd5207.id.png)

Diagram di atas menunjukkan arsitektur referensi untuk aplikasi prototipe ini.

* Perangkat IoT dengan sensor jarak mendeteksi kedatangan buah. Ini mengirim pesan ke cloud untuk memberi tahu bahwa buah telah terdeteksi.
* Aplikasi tanpa server di cloud mengirim perintah ke perangkat lain untuk mengambil foto dan mengklasifikasikan gambar.
* Perangkat IoT dengan kamera mengambil gambar dan mengirimkannya ke pengklasifikasi gambar yang berjalan di perangkat edge. Hasilnya kemudian dikirim ke cloud.
* Aplikasi tanpa server di cloud menyimpan informasi ini untuk dianalisis nanti untuk melihat persentase buah yang belum matang. Jika buah belum matang, aplikasi mengirim perintah ke perangkat IoT lain untuk memberi tahu pekerja pabrik melalui LED bahwa ada buah yang belum matang.

> 💁 Seluruh aplikasi IoT ini dapat diimplementasikan sebagai satu perangkat, dengan semua logika untuk memulai klasifikasi gambar dan mengontrol LED yang terintegrasi. Perangkat ini dapat menggunakan IoT Hub hanya untuk melacak jumlah buah yang belum matang yang terdeteksi dan mengonfigurasi perangkat. Dalam pelajaran ini, aplikasi diperluas untuk mendemonstrasikan konsep untuk aplikasi IoT skala besar.

Untuk prototipe, Anda akan mengimplementasikan semua ini pada satu perangkat. Jika Anda menggunakan mikrokontroler, maka Anda akan menggunakan perangkat edge terpisah untuk menjalankan pengklasifikasi gambar. Anda telah mempelajari sebagian besar hal yang Anda perlukan untuk membangun ini.

## Memicu Pemeriksaan Kualitas Buah dari Sensor

Perangkat IoT memerlukan semacam pemicu untuk menunjukkan kapan buah siap diklasifikasikan. Salah satu pemicu untuk ini adalah mengukur kapan buah berada di lokasi yang tepat di ban berjalan dengan mengukur jarak ke sensor.

![Sensor jarak mengirimkan sinar laser ke objek seperti pisang dan mengukur waktu hingga sinar dipantulkan kembali](../../../../../translated_images/proximity-sensor.f5cd752c77fb62fe.id.png)

Sensor jarak dapat digunakan untuk mengukur jarak dari sensor ke suatu objek. Biasanya, sensor ini memancarkan sinar radiasi elektromagnetik seperti sinar laser atau cahaya infra-merah, lalu mendeteksi radiasi yang dipantulkan dari objek. Waktu antara sinar laser yang dikirim dan sinyal yang dipantulkan kembali dapat digunakan untuk menghitung jarak ke sensor.

> 💁 Anda mungkin pernah menggunakan sensor jarak tanpa menyadarinya. Sebagian besar ponsel pintar akan mematikan layar saat Anda mendekatkannya ke telinga untuk mencegah Anda secara tidak sengaja mengakhiri panggilan dengan daun telinga Anda. Ini bekerja menggunakan sensor jarak, yang mendeteksi objek dekat layar selama panggilan dan menonaktifkan kemampuan sentuh hingga ponsel berada pada jarak tertentu.

### Tugas - Memicu Deteksi Kualitas Buah dari Sensor Jarak

Ikuti panduan yang relevan untuk menggunakan sensor jarak untuk mendeteksi objek menggunakan perangkat IoT Anda:

* [Arduino - Wio Terminal](wio-terminal-proximity.md)
* [Komputer papan tunggal - Raspberry Pi](pi-proximity.md)
* [Komputer papan tunggal - Perangkat virtual](virtual-device-proximity.md)

## Data yang Digunakan untuk Detektor Kualitas Buah

Prototipe detektor buah memiliki beberapa komponen yang saling berkomunikasi.

![Komponen yang saling berkomunikasi](../../../../../translated_images/fruit-quality-detector-message-flow.adf2a65da8fd8741ac7af11361574de89adc126785d67606bb4d2ec00467e380.id.png)

* Sensor jarak mengukur jarak ke buah dan mengirimkannya ke IoT Hub
* Perintah untuk mengontrol kamera berasal dari IoT Hub ke perangkat kamera
* Hasil klasifikasi gambar dikirim ke IoT Hub
* Perintah untuk mengontrol LED untuk memberi tahu saat buah belum matang dikirim dari IoT Hub ke perangkat dengan LED

Sebaiknya definisikan struktur pesan ini terlebih dahulu, sebelum Anda membangun aplikasi.

> 💁 Hampir setiap pengembang berpengalaman pernah menghabiskan waktu berjam-jam, berhari-hari, atau bahkan berminggu-minggu mengejar bug yang disebabkan oleh perbedaan antara data yang dikirim dan yang diharapkan.

Sebagai contoh - jika Anda mengirim informasi suhu, bagaimana Anda akan mendefinisikan JSON-nya? Anda bisa memiliki field bernama `temperature`, atau menggunakan singkatan umum `temp`.

```json
{
    "temperature": 20.7
}
```

dibandingkan dengan:

```json
{
    "temp": 20.7
}
```

Anda juga harus mempertimbangkan satuan - apakah suhu dalam °C atau °F? Jika Anda mengukur suhu menggunakan perangkat konsumen dan mereka mengubah satuan tampilan, Anda perlu memastikan satuan yang dikirim ke cloud tetap konsisten.

✅ Lakukan penelitian: Bagaimana masalah satuan menyebabkan Mars Climate Orbiter senilai $125 juta mengalami kegagalan?

Pikirkan tentang data yang dikirim untuk detektor kualitas buah. Bagaimana Anda akan mendefinisikan setiap pesan? Di mana Anda akan menganalisis data dan membuat keputusan tentang data apa yang akan dikirim?

Sebagai contoh - memicu klasifikasi gambar menggunakan sensor jarak. Perangkat IoT mengukur jarak, tetapi di mana keputusan dibuat? Apakah perangkat memutuskan bahwa buah sudah cukup dekat dan mengirim pesan untuk memberi tahu IoT Hub untuk memicu klasifikasi? Atau apakah perangkat mengirimkan pengukuran jarak dan membiarkan IoT Hub yang memutuskan?

Jawaban untuk pertanyaan seperti ini adalah - tergantung. Setiap kasus penggunaan berbeda, itulah sebabnya sebagai pengembang IoT Anda perlu memahami sistem yang Anda bangun, bagaimana sistem tersebut digunakan, dan data yang terdeteksi.

* Jika keputusan dibuat oleh IoT Hub, Anda perlu mengirim beberapa pengukuran jarak.
* Jika Anda mengirim terlalu banyak pesan, ini akan meningkatkan biaya IoT Hub, dan jumlah bandwidth yang dibutuhkan oleh perangkat IoT Anda (terutama di pabrik dengan jutaan perangkat). Ini juga dapat memperlambat perangkat Anda.
* Jika Anda membuat keputusan di perangkat, Anda perlu menyediakan cara untuk mengonfigurasi perangkat agar dapat menyetel mesin dengan lebih baik.

## Menggunakan Perangkat Pengembang untuk Mensimulasikan Beberapa Perangkat IoT

Untuk membangun prototipe Anda, Anda perlu perangkat pengembang IoT Anda untuk bertindak seperti beberapa perangkat, mengirim telemetri dan merespons perintah.

### Mensimulasikan Beberapa Perangkat IoT pada Raspberry Pi atau Perangkat IoT Virtual

Saat menggunakan komputer papan tunggal seperti Raspberry Pi, Anda dapat menjalankan beberapa aplikasi sekaligus. Ini berarti Anda dapat mensimulasikan beberapa perangkat IoT dengan membuat beberapa aplikasi, satu untuk setiap 'perangkat IoT'. Sebagai contoh, Anda dapat mengimplementasikan setiap perangkat sebagai file Python terpisah dan menjalankannya di sesi terminal yang berbeda.
> 💁 Perlu diketahui bahwa beberapa perangkat keras tidak akan berfungsi jika diakses oleh beberapa aplikasi yang berjalan secara bersamaan.
### Mensimulasikan beberapa perangkat pada mikrokontroler

Mikrokontroler lebih rumit untuk mensimulasikan beberapa perangkat. Tidak seperti komputer papan tunggal, Anda tidak dapat menjalankan beberapa aplikasi sekaligus; Anda harus memasukkan semua logika untuk setiap perangkat IoT dalam satu aplikasi.

Beberapa saran untuk mempermudah proses ini adalah:

* Buat satu atau lebih kelas untuk setiap perangkat IoT - misalnya kelas bernama `DistanceSensor`, `ClassifierCamera`, `LEDController`. Masing-masing dapat memiliki metode `setup` dan `loop` sendiri yang dipanggil oleh fungsi `setup` dan `loop` utama.
* Tangani perintah di satu tempat, dan arahkan ke kelas perangkat yang relevan sesuai kebutuhan.
* Dalam fungsi `loop` utama, Anda perlu mempertimbangkan waktu untuk setiap perangkat yang berbeda. Misalnya, jika Anda memiliki satu kelas perangkat yang perlu diproses setiap 10 detik, dan yang lain setiap 1 detik, maka dalam fungsi `loop` utama gunakan penundaan 1 detik. Setiap panggilan `loop` memicu kode yang relevan untuk perangkat yang perlu diproses setiap detik, dan gunakan penghitung untuk menghitung setiap loop, memproses perangkat lain saat penghitung mencapai 10 (mengatur ulang penghitung setelahnya).

## Beralih ke produksi

Prototipe akan menjadi dasar sistem produksi akhir. Beberapa perbedaan saat Anda beralih ke produksi adalah:

* Komponen yang diperkuat - menggunakan perangkat keras yang dirancang untuk tahan terhadap kebisingan, panas, getaran, dan tekanan di pabrik.
* Menggunakan komunikasi internal - beberapa komponen akan berkomunikasi langsung tanpa perlu mengirim data ke cloud, hanya mengirim data ke cloud untuk disimpan. Bagaimana ini dilakukan tergantung pada pengaturan pabrik, baik melalui komunikasi langsung, atau dengan menjalankan sebagian layanan IoT di edge menggunakan perangkat gateway.
* Opsi konfigurasi - setiap pabrik dan kasus penggunaan berbeda, sehingga perangkat keras perlu dapat dikonfigurasi. Misalnya, sensor jarak mungkin perlu mendeteksi buah yang berbeda pada jarak yang berbeda. Daripada mengkodekan jarak untuk memicu klasifikasi, Anda ingin ini dapat dikonfigurasi melalui cloud, misalnya menggunakan device twin.
* Penghapusan buah otomatis - alih-alih LED untuk memberi tahu bahwa buah belum matang, perangkat otomatis akan menghapusnya.

✅ Lakukan penelitian: Dalam cara apa lagi perangkat produksi berbeda dari kit pengembang?

---

## 🚀 Tantangan

Dalam pelajaran ini, Anda telah mempelajari beberapa konsep yang perlu Anda ketahui tentang cara merancang sistem IoT. Ingat kembali proyek sebelumnya. Bagaimana mereka cocok dengan arsitektur referensi yang ditunjukkan di atas?

Pilih salah satu proyek sejauh ini dan pikirkan desain solusi yang lebih rumit dengan menggabungkan beberapa kemampuan di luar yang telah dibahas dalam proyek. Gambarlah arsitekturnya dan pikirkan semua perangkat dan layanan yang Anda perlukan.

Sebagai contoh - perangkat pelacak kendaraan yang menggabungkan GPS dengan sensor untuk memantau hal-hal seperti suhu di truk berpendingin, waktu mesin menyala dan mati, serta identitas pengemudi. Apa saja perangkat yang terlibat, layanan yang terlibat, data yang dikirimkan, dan pertimbangan keamanan serta privasi?

## Kuis setelah kuliah

[Kuis setelah kuliah](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/36)

## Tinjauan & Studi Mandiri

* Baca lebih lanjut tentang arsitektur IoT di [dokumentasi arsitektur referensi Azure IoT di Microsoft docs](https://docs.microsoft.com/azure/architecture/reference-architectures/iot?WT.mc_id=academic-17441-jabenn)
* Baca lebih lanjut tentang device twin di [pahami dan gunakan device twin dalam dokumentasi IoT Hub di Microsoft docs](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-device-twins?WT.mc_id=academic-17441-jabenn)
* Baca tentang OPC-UA, protokol komunikasi mesin-ke-mesin yang digunakan dalam otomatisasi industri di [halaman OPC-UA di Wikipedia](https://wikipedia.org/wiki/OPC_Unified_Architecture)

## Tugas

[Bangun detektor kualitas buah](assignment.md)

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diketahui bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.