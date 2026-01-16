<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9bae08314d8487cb76ddf3d8797e1544",
  "translation_date": "2025-08-27T22:36:57+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/README.md",
  "language_code": "id"
}
-->
# Pengantar IoT

![Gambaran sketchnote dari pelajaran ini](../../../../../translated_images/id/lesson-1.2606670fa61ee904687da5d6fa4e726639d524d064c895117da1b95b9ff6251d.jpg)

> Sketchnote oleh [Nitya Narasimhan](https://github.com/nitya). Klik gambar untuk versi yang lebih besar.

Pelajaran ini diajarkan sebagai bagian dari [seri Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) dari [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Pelajaran ini disampaikan dalam 2 video - pelajaran berdurasi 1 jam, dan sesi tanya jawab berdurasi 1 jam yang membahas lebih dalam bagian-bagian pelajaran serta menjawab pertanyaan.

[![Pelajaran 1: Pengantar IoT](https://img.youtube.com/vi/bVFfcYh6UBw/0.jpg)](https://youtu.be/bVFfcYh6UBw)

[![Pelajaran 1: Pengantar IoT - Sesi tanya jawab](https://img.youtube.com/vi/YI772q5v3yI/0.jpg)](https://youtu.be/YI772q5v3yI)

> 🎥 Klik gambar di atas untuk menonton video

## Kuis sebelum pelajaran

[Kuis sebelum pelajaran](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/1)

## Pengantar

Pelajaran ini mencakup beberapa topik pengantar tentang Internet of Things, dan membantu Anda memulai dengan menyiapkan perangkat keras Anda.

Dalam pelajaran ini kita akan membahas:

* [Apa itu 'Internet of Things'?](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Perangkat IoT](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Menyiapkan perangkat Anda](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Aplikasi IoT](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Contoh perangkat IoT di sekitar Anda](../../../../../1-getting-started/lessons/1-introduction-to-iot)

## Apa itu 'Internet of Things'?

Istilah 'Internet of Things' pertama kali diperkenalkan oleh [Kevin Ashton](https://wikipedia.org/wiki/Kevin_Ashton) pada tahun 1999, untuk merujuk pada penghubungan Internet dengan dunia fisik melalui sensor. Sejak itu, istilah ini digunakan untuk menggambarkan perangkat apa pun yang berinteraksi dengan dunia fisik di sekitarnya, baik dengan mengumpulkan data dari sensor, atau memberikan interaksi dunia nyata melalui aktuator (perangkat yang melakukan sesuatu seperti menyalakan saklar atau menyalakan LED), yang biasanya terhubung ke perangkat lain atau Internet.

> **Sensor** mengumpulkan informasi dari dunia, seperti mengukur kecepatan, suhu, atau lokasi.
>
> **Aktuator** mengubah sinyal listrik menjadi interaksi dunia nyata seperti memicu saklar, menyalakan lampu, menghasilkan suara, atau mengirim sinyal kontrol ke perangkat keras lain, misalnya untuk menyalakan soket listrik.

IoT sebagai bidang teknologi lebih dari sekadar perangkat - ini mencakup layanan berbasis cloud yang dapat memproses data sensor, atau mengirim permintaan ke aktuator yang terhubung ke perangkat IoT. Ini juga mencakup perangkat yang tidak memiliki atau tidak memerlukan konektivitas Internet, yang sering disebut sebagai perangkat edge. Perangkat ini dapat memproses dan merespons data sensor sendiri, biasanya menggunakan model AI yang dilatih di cloud.

IoT adalah bidang teknologi yang berkembang pesat. Diperkirakan pada akhir tahun 2020, ada 30 miliar perangkat IoT yang telah diterapkan dan terhubung ke Internet. Melihat ke masa depan, diperkirakan pada tahun 2025, perangkat IoT akan mengumpulkan hampir 80 zettabyte data atau 80 triliun gigabyte. Itu adalah jumlah data yang sangat besar!

![Grafik yang menunjukkan perangkat IoT aktif dari waktu ke waktu, dengan tren meningkat dari kurang dari 5 miliar pada tahun 2015 menjadi lebih dari 30 miliar pada tahun 2025](../../../../../images/connected-iot-devices.svg)

✅ Lakukan sedikit penelitian: Berapa banyak data yang dihasilkan oleh perangkat IoT yang benar-benar digunakan, dan berapa banyak yang terbuang? Mengapa begitu banyak data diabaikan?

Data ini adalah kunci keberhasilan IoT. Untuk menjadi pengembang IoT yang sukses, Anda perlu memahami data yang perlu dikumpulkan, cara mengumpulkannya, cara membuat keputusan berdasarkan data tersebut, dan cara menggunakan keputusan tersebut untuk berinteraksi dengan dunia fisik jika diperlukan.

## Perangkat IoT

Huruf **T** dalam IoT adalah singkatan dari **Things** - perangkat yang berinteraksi dengan dunia fisik di sekitarnya baik dengan mengumpulkan data dari sensor atau memberikan interaksi dunia nyata melalui aktuator.

Perangkat untuk produksi atau penggunaan komersial, seperti pelacak kebugaran konsumen, atau pengontrol mesin industri, biasanya dibuat khusus. Mereka menggunakan papan sirkuit khusus, bahkan mungkin prosesor khusus, yang dirancang untuk memenuhi kebutuhan tugas tertentu, apakah itu cukup kecil untuk dipasang di pergelangan tangan, atau cukup tangguh untuk bekerja di lingkungan pabrik dengan suhu tinggi, tekanan tinggi, atau getaran tinggi.

Sebagai pengembang yang sedang belajar tentang IoT atau membuat prototipe perangkat, Anda perlu memulai dengan kit pengembang. Ini adalah perangkat IoT serbaguna yang dirancang untuk digunakan oleh pengembang, sering kali dengan fitur yang tidak akan ada pada perangkat produksi, seperti serangkaian pin eksternal untuk menghubungkan sensor atau aktuator, perangkat keras untuk mendukung debugging, atau sumber daya tambahan yang akan menambah biaya yang tidak perlu saat melakukan produksi massal.

Kit pengembang ini biasanya terbagi dalam dua kategori - mikrokontroler dan komputer papan tunggal. Keduanya akan diperkenalkan di sini, dan kita akan membahasnya lebih detail di pelajaran berikutnya.

> 💁 Ponsel Anda juga dapat dianggap sebagai perangkat IoT serbaguna, dengan sensor dan aktuator bawaan, dengan berbagai aplikasi yang menggunakan sensor dan aktuator tersebut dengan cara yang berbeda menggunakan layanan cloud yang berbeda. Anda bahkan dapat menemukan beberapa tutorial IoT yang menggunakan aplikasi ponsel sebagai perangkat IoT.

### Mikrokontroler

Mikrokontroler (juga disebut sebagai MCU, singkatan dari microcontroller unit) adalah komputer kecil yang terdiri dari:

🧠 Satu atau lebih unit pemrosesan pusat (CPU) - 'otak' dari mikrokontroler yang menjalankan program Anda

💾 Memori (RAM dan memori program) - tempat program, data, dan variabel Anda disimpan

🔌 Koneksi input/output (I/O) yang dapat diprogram - untuk berkomunikasi dengan perangkat eksternal (perangkat yang terhubung) seperti sensor dan aktuator

Mikrokontroler biasanya merupakan perangkat komputasi berbiaya rendah, dengan harga rata-rata untuk yang digunakan dalam perangkat keras khusus turun hingga sekitar US$0,50, dan beberapa perangkat semurah US$0,03. Kit pengembang dapat dimulai dari harga US$4, dengan biaya meningkat seiring penambahan fitur. [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html), sebuah kit pengembang mikrokontroler dari [Seeed studios](https://www.seeedstudio.com) yang memiliki sensor, aktuator, WiFi, dan layar, harganya sekitar US$30.

![Wio Terminal](../../../../../translated_images/id/wio-terminal.b8299ee16587db9a.webp)

> 💁 Saat mencari mikrokontroler di Internet, berhati-hatilah saat mencari istilah **MCU** karena ini akan menghasilkan banyak hasil tentang Marvel Cinematic Universe, bukan mikrokontroler.

Mikrokontroler dirancang untuk diprogram untuk melakukan sejumlah tugas yang sangat spesifik, daripada menjadi komputer serbaguna seperti PC atau Mac. Kecuali untuk skenario yang sangat spesifik, Anda tidak dapat menghubungkan monitor, keyboard, dan mouse untuk menggunakannya untuk tugas-tugas umum.

Kit pengembang mikrokontroler biasanya dilengkapi dengan sensor dan aktuator tambahan di papan. Sebagian besar papan akan memiliki satu atau lebih LED yang dapat Anda program, bersama dengan perangkat lain seperti colokan standar untuk menambahkan lebih banyak sensor atau aktuator menggunakan ekosistem berbagai produsen atau sensor bawaan (biasanya yang paling populer seperti sensor suhu). Beberapa mikrokontroler memiliki konektivitas nirkabel bawaan seperti Bluetooth atau WiFi atau memiliki mikrokontroler tambahan di papan untuk menambahkan konektivitas ini.

> 💁 Mikrokontroler biasanya diprogram menggunakan C/C++.

### Komputer papan tunggal

Komputer papan tunggal adalah perangkat komputasi kecil yang memiliki semua elemen komputer lengkap yang terkandung dalam satu papan kecil. Perangkat ini memiliki spesifikasi yang mendekati PC atau Mac desktop atau laptop, menjalankan sistem operasi penuh, tetapi berukuran kecil, menggunakan daya lebih sedikit, dan jauh lebih murah.

![Raspberry Pi 4](../../../../../translated_images/id/raspberry-pi-4.fd4590d308c3d456.webp)

Raspberry Pi adalah salah satu komputer papan tunggal yang paling populer.

Seperti mikrokontroler, komputer papan tunggal memiliki CPU, memori, dan pin input/output, tetapi mereka memiliki fitur tambahan seperti chip grafis untuk memungkinkan Anda menghubungkan monitor, output audio, dan port USB untuk menghubungkan keyboard, mouse, dan perangkat USB standar lainnya seperti webcam atau penyimpanan eksternal. Program disimpan di kartu SD atau hard drive bersama dengan sistem operasi, bukan chip memori yang terpasang di papan.

> 🎓 Anda dapat menganggap komputer papan tunggal sebagai versi yang lebih kecil dan lebih murah dari PC atau Mac yang sedang Anda gunakan, dengan tambahan pin GPIO (general-purpose input/output) untuk berinteraksi dengan sensor dan aktuator.

Komputer papan tunggal adalah komputer yang sepenuhnya berfitur lengkap, sehingga dapat diprogram dalam bahasa apa pun. Perangkat IoT biasanya diprogram menggunakan Python.

### Pilihan perangkat keras untuk pelajaran berikutnya

Semua pelajaran berikutnya mencakup tugas menggunakan perangkat IoT untuk berinteraksi dengan dunia fisik dan berkomunikasi dengan cloud. Setiap pelajaran mendukung 3 pilihan perangkat - Arduino (menggunakan Seeed Studios Wio Terminal), atau komputer papan tunggal, baik perangkat fisik (Raspberry Pi 4) atau komputer papan tunggal virtual yang berjalan di PC atau Mac Anda.

Anda dapat membaca tentang perangkat keras yang diperlukan untuk menyelesaikan semua tugas di [panduan perangkat keras](../../../hardware.md).

> 💁 Anda tidak perlu membeli perangkat keras IoT untuk menyelesaikan tugas, Anda dapat melakukan semuanya menggunakan komputer papan tunggal virtual.

Pilihan perangkat keras yang Anda gunakan tergantung pada apa yang tersedia di rumah atau sekolah Anda, dan bahasa pemrograman yang Anda ketahui atau rencanakan untuk dipelajari. Kedua varian perangkat keras akan menggunakan ekosistem sensor yang sama, sehingga jika Anda memulai dengan satu jalur, Anda dapat beralih ke jalur lain tanpa harus mengganti sebagian besar kit. Komputer papan tunggal virtual akan setara dengan belajar menggunakan Raspberry Pi, dengan sebagian besar kode dapat ditransfer ke Pi jika Anda akhirnya mendapatkan perangkat dan sensor.

### Kit pengembang Arduino

Jika Anda tertarik untuk belajar pengembangan mikrokontroler, Anda dapat menyelesaikan tugas menggunakan perangkat Arduino. Anda akan membutuhkan pemahaman dasar tentang pemrograman C/C++, karena pelajaran hanya akan mengajarkan kode yang relevan dengan kerangka kerja Arduino, sensor dan aktuator yang digunakan, serta pustaka yang berinteraksi dengan cloud.

Tugas akan menggunakan [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn) dengan [ekstensi PlatformIO untuk pengembangan mikrokontroler](https://platformio.org). Anda juga dapat menggunakan Arduino IDE jika Anda sudah berpengalaman dengan alat ini, karena instruksi tidak akan disediakan.

### Kit pengembang komputer papan tunggal

Jika Anda tertarik untuk belajar pengembangan IoT menggunakan komputer papan tunggal, Anda dapat menyelesaikan tugas menggunakan Raspberry Pi, atau perangkat virtual yang berjalan di PC atau Mac Anda.

Anda akan membutuhkan pemahaman dasar tentang pemrograman Python, karena pelajaran hanya akan mengajarkan kode yang relevan dengan sensor dan aktuator yang digunakan, serta pustaka yang berinteraksi dengan cloud.

> 💁 Jika Anda ingin belajar pemrograman Python, lihat dua seri video berikut:
>
> * [Python untuk pemula](https://channel9.msdn.com/Series/Intro-to-Python-Development?WT.mc_id=academic-17441-jabenn)
> * [Lebih banyak Python untuk pemula](https://channel9.msdn.com/Series/More-Python-for-Beginners?WT.mc_id=academic-7372-jabenn)

Tugas akan menggunakan [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn).

Jika Anda menggunakan Raspberry Pi, Anda dapat menjalankan Pi Anda menggunakan versi desktop penuh dari Raspberry Pi OS, dan melakukan semua pengkodean langsung di Pi menggunakan [versi Raspberry Pi OS dari VS Code](https://code.visualstudio.com/docs/setup/raspberry-pi?WT.mc_id=academic-17441-jabenn), atau menjalankan Pi Anda sebagai perangkat tanpa kepala dan mengkode dari PC atau Mac Anda menggunakan VS Code dengan [ekstensi Remote SSH](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) yang memungkinkan Anda terhubung ke Pi dan mengedit, debugging, serta menjalankan kode seolah-olah Anda sedang mengkode langsung di perangkat tersebut.

Jika Anda menggunakan opsi perangkat virtual, Anda akan mengkode langsung di komputer Anda. Alih-alih mengakses sensor dan aktuator, Anda akan menggunakan alat untuk mensimulasikan perangkat keras ini dengan menyediakan nilai sensor yang dapat Anda tentukan, dan menampilkan hasil aktuator di layar.

## Menyiapkan perangkat Anda

Sebelum Anda dapat mulai memprogram perangkat IoT Anda, Anda perlu melakukan sedikit pengaturan. Ikuti instruksi yang relevan di bawah ini tergantung pada perangkat yang akan Anda gunakan.
💁 Jika Anda belum memiliki perangkat, lihat [panduan perangkat keras](../../../hardware.md) untuk membantu menentukan perangkat mana yang akan Anda gunakan, dan perangkat keras tambahan apa yang perlu Anda beli. Anda tidak perlu membeli perangkat keras, karena semua proyek dapat dijalankan pada perangkat keras virtual.
Instruksi ini mencakup tautan ke situs web pihak ketiga dari pembuat perangkat keras atau alat yang akan Anda gunakan. Tujuannya adalah untuk memastikan Anda selalu menggunakan instruksi terbaru untuk berbagai alat dan perangkat keras.

Ikuti panduan yang relevan untuk mengatur perangkat Anda dan menyelesaikan proyek 'Hello World'. Ini akan menjadi langkah pertama dalam menciptakan lampu malam IoT selama 4 pelajaran dalam bagian pengenalan ini.

* [Arduino - Wio Terminal](wio-terminal.md)
* [Single-board computer - Raspberry Pi](pi.md)
* [Single-board computer - Virtual device](virtual-device.md)

✅ Anda akan menggunakan VS Code untuk Arduino dan komputer papan tunggal. Jika Anda belum pernah menggunakannya sebelumnya, baca lebih lanjut di [situs VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

## Aplikasi IoT

IoT mencakup berbagai macam kasus penggunaan, yang dapat dikelompokkan ke dalam beberapa kategori besar:

* IoT Konsumen
* IoT Komersial
* IoT Industri
* IoT Infrastruktur

✅ Lakukan sedikit riset: Untuk setiap area yang dijelaskan di bawah ini, temukan satu contoh konkret yang tidak disebutkan dalam teks.

### IoT Konsumen

IoT Konsumen mengacu pada perangkat IoT yang dibeli dan digunakan oleh konsumen di rumah. Beberapa perangkat ini sangat berguna, seperti speaker pintar, sistem pemanas pintar, dan penyedot debu robot. Namun, ada juga perangkat yang kegunaannya dipertanyakan, seperti keran yang dikontrol suara yang kemudian tidak bisa dimatikan karena kontrol suara tidak dapat mendengar Anda di tengah suara air yang mengalir.

Perangkat IoT Konsumen memberdayakan orang untuk mencapai lebih banyak di lingkungan mereka, terutama 1 miliar orang yang memiliki disabilitas. Penyedot debu robot dapat memberikan lantai yang bersih bagi orang-orang dengan masalah mobilitas yang tidak dapat menyedot debu sendiri, oven yang dikontrol suara memungkinkan orang dengan keterbatasan penglihatan atau kontrol motorik untuk memanaskan oven mereka hanya dengan suara, monitor kesehatan memungkinkan pasien untuk memantau kondisi kronis mereka sendiri dengan pembaruan yang lebih teratur dan lebih rinci tentang kondisi mereka. Perangkat ini menjadi sangat umum sehingga bahkan anak-anak kecil menggunakannya sebagai bagian dari kehidupan sehari-hari mereka, misalnya, siswa yang melakukan sekolah virtual selama pandemi COVID menggunakan perangkat rumah pintar untuk mengatur timer untuk melacak pekerjaan sekolah mereka atau alarm untuk mengingatkan mereka tentang pertemuan kelas yang akan datang.

✅ Perangkat IoT Konsumen apa yang Anda miliki di rumah atau yang Anda gunakan secara pribadi?

### IoT Komersial

IoT Komersial mencakup penggunaan IoT di tempat kerja. Di lingkungan kantor, mungkin ada sensor okupansi dan detektor gerakan untuk mengelola pencahayaan dan pemanas agar hanya menyala saat dibutuhkan, mengurangi biaya dan emisi karbon. Di pabrik, perangkat IoT dapat memantau bahaya keselamatan seperti pekerja yang tidak mengenakan helm atau kebisingan yang telah mencapai tingkat berbahaya. Di ritel, perangkat IoT dapat mengukur suhu penyimpanan dingin, memberi tahu pemilik toko jika lemari es atau freezer berada di luar rentang suhu yang diperlukan, atau mereka dapat memantau barang di rak untuk mengarahkan karyawan mengisi ulang produk yang telah terjual. Industri transportasi semakin mengandalkan IoT untuk memantau lokasi kendaraan, melacak jarak tempuh di jalan untuk pengenaan biaya pengguna jalan, melacak jam kerja pengemudi dan kepatuhan istirahat, atau memberi tahu staf saat kendaraan mendekati depot untuk persiapan pemuatan atau pembongkaran.

✅ Perangkat IoT Komersial apa yang Anda miliki di sekolah atau tempat kerja Anda?

### IoT Industri (IIoT)

IoT Industri, atau IIoT, adalah penggunaan perangkat IoT untuk mengontrol dan mengelola mesin dalam skala besar. Ini mencakup berbagai macam kasus penggunaan, mulai dari pabrik hingga pertanian digital.

Pabrik menggunakan perangkat IoT dalam berbagai cara. Mesin dapat dipantau dengan beberapa sensor untuk melacak hal-hal seperti suhu, getaran, dan kecepatan rotasi. Data ini kemudian dapat dipantau untuk memungkinkan mesin dihentikan jika berada di luar toleransi tertentu - misalnya, jika terlalu panas, mesin akan dimatikan. Data ini juga dapat dikumpulkan dan dianalisis dari waktu ke waktu untuk melakukan pemeliharaan prediktif, di mana model AI akan melihat data yang mengarah pada kegagalan, dan menggunakannya untuk memprediksi kegagalan lain sebelum terjadi.

Pertanian digital sangat penting untuk memberi makan populasi yang terus bertambah, terutama bagi 2 miliar orang di 500 juta rumah tangga yang bergantung pada [pertanian subsisten](https://wikipedia.org/wiki/Subsistence_agriculture). Pertanian digital dapat berkisar dari sensor dengan harga beberapa dolar hingga pengaturan komersial besar. Seorang petani dapat memulai dengan memantau suhu dan menggunakan [hari derajat pertumbuhan](https://wikipedia.org/wiki/Growing_degree-day) untuk memprediksi kapan tanaman akan siap panen. Mereka dapat menghubungkan pemantauan kelembapan tanah ke sistem penyiraman otomatis untuk memberikan tanaman mereka air sebanyak yang dibutuhkan, tetapi tidak lebih untuk memastikan tanaman mereka tidak mengering tanpa membuang air. Petani bahkan melangkah lebih jauh dengan menggunakan drone, data satelit, dan AI untuk memantau pertumbuhan tanaman, penyakit, dan kualitas tanah di area pertanian yang luas.

✅ Perangkat IoT apa lagi yang dapat membantu petani?

### IoT Infrastruktur

IoT Infrastruktur adalah pemantauan dan pengendalian infrastruktur lokal dan global yang digunakan orang setiap hari.

[Kota Pintar](https://wikipedia.org/wiki/Smart_city) adalah area perkotaan yang menggunakan perangkat IoT untuk mengumpulkan data tentang kota dan menggunakannya untuk meningkatkan cara kota tersebut berjalan. Kota-kota ini biasanya dijalankan dengan kolaborasi antara pemerintah lokal, akademisi, dan bisnis lokal, melacak dan mengelola berbagai hal mulai dari transportasi hingga parkir dan polusi. Misalnya, di Kopenhagen, Denmark, polusi udara penting bagi penduduk setempat, sehingga diukur dan data tersebut digunakan untuk memberikan informasi tentang rute bersepeda dan jogging yang paling bersih.

[Smart power grids](https://wikipedia.org/wiki/Smart_grid) memungkinkan analitik yang lebih baik tentang permintaan daya dengan mengumpulkan data penggunaan di tingkat rumah individu. Data ini dapat memandu keputusan di tingkat negara termasuk di mana membangun pembangkit listrik baru, dan di tingkat pribadi dengan memberikan pengguna wawasan tentang berapa banyak daya yang mereka gunakan, kapan mereka menggunakannya, dan bahkan saran tentang cara mengurangi biaya, seperti mengisi daya mobil listrik di malam hari.

✅ Jika Anda dapat menambahkan perangkat IoT untuk mengukur sesuatu di tempat tinggal Anda, apa yang akan Anda ukur?

## Contoh perangkat IoT yang mungkin ada di sekitar Anda

Anda akan terkejut dengan berapa banyak perangkat IoT yang ada di sekitar Anda. Saya menulis ini dari rumah dan saya memiliki perangkat berikut yang terhubung ke Internet dengan fitur pintar seperti kontrol aplikasi, kontrol suara, atau kemampuan mengirim data kepada saya melalui ponsel:

* Beberapa speaker pintar
* Kulkas, mesin pencuci piring, oven, dan microwave
* Monitor listrik untuk panel surya
* Colokan pintar
* Bel pintu video dan kamera keamanan
* Termostat pintar dengan beberapa sensor ruangan pintar
* Pembuka pintu garasi
* Sistem hiburan rumah dan TV yang dikontrol suara
* Lampu
* Pelacak kebugaran dan kesehatan

Semua jenis perangkat ini memiliki sensor dan/atau aktuator dan berbicara ke Internet. Saya dapat mengetahui dari ponsel saya apakah pintu garasi saya terbuka, dan meminta speaker pintar saya untuk menutupnya. Saya bahkan dapat mengatur timer sehingga jika pintu masih terbuka di malam hari, pintu akan menutup secara otomatis. Ketika bel pintu saya berbunyi, saya dapat melihat dari ponsel saya siapa yang ada di sana di mana pun saya berada di dunia, dan berbicara dengan mereka melalui speaker dan mikrofon yang terpasang di bel pintu. Saya dapat memantau glukosa darah, detak jantung, dan pola tidur saya, mencari pola dalam data untuk meningkatkan kesehatan saya. Saya dapat mengontrol lampu saya melalui cloud, dan duduk dalam gelap ketika koneksi Internet saya terputus.

---

## 🚀 Tantangan

Daftar sebanyak mungkin perangkat IoT yang ada di rumah, sekolah, atau tempat kerja Anda - mungkin lebih banyak dari yang Anda pikirkan!

## Kuis setelah pelajaran

[Kuis setelah pelajaran](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/2)

## Tinjauan & Studi Mandiri

Baca tentang manfaat dan kegagalan proyek IoT konsumen. Periksa situs berita untuk artikel tentang saat proyek tersebut gagal, seperti masalah privasi, masalah perangkat keras, atau masalah yang disebabkan oleh kurangnya konektivitas.

Beberapa contoh:

* Lihat akun Twitter **[Internet of Sh*t](https://twitter.com/internetofshit)** *(peringatan: bahasa kasar)* untuk beberapa contoh kegagalan proyek IoT konsumen.
* [c|net - Jam tangan Apple saya menyelamatkan hidup saya: 5 orang berbagi cerita mereka](https://www.cnet.com/news/apple-watch-lifesaving-health-features-read-5-peoples-stories/)
* [c|net - Teknisi ADT mengaku bersalah karena memata-matai umpan kamera pelanggan selama bertahun-tahun](https://www.cnet.com/news/adt-home-security-technician-pleads-guilty-to-spying-on-customer-camera-feeds-for-years/) *(peringatan: voyeurisme tanpa izin)*

## Tugas

[Investigasi proyek IoT](assignment.md)

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.