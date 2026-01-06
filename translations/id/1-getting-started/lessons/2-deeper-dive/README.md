<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9dd7f645ad1c6f20b72fee512987f772",
  "translation_date": "2025-08-27T22:49:47+00:00",
  "source_file": "1-getting-started/lessons/2-deeper-dive/README.md",
  "language_code": "id"
}
-->
# Penjelajahan Lebih Dalam ke IoT

![Gambaran sketchnote dari pelajaran ini](../../../../../translated_images/lesson-2.324b0580d620c25e0a24fb7fddfc0b29a846dd4b82c08e7a9466d580ee78ce51.id.jpg)

> Sketchnote oleh [Nitya Narasimhan](https://github.com/nitya). Klik gambar untuk versi yang lebih besar.

Pelajaran ini diajarkan sebagai bagian dari seri [Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) dari [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Pelajaran ini disampaikan dalam 2 video - satu pelajaran berdurasi 1 jam, dan satu sesi tanya jawab berdurasi 1 jam yang membahas lebih dalam bagian-bagian dari pelajaran serta menjawab pertanyaan.

[![Pelajaran 2: Penjelajahan Lebih Dalam ke IoT](https://img.youtube.com/vi/t0SySWw3z9M/0.jpg)](https://youtu.be/t0SySWw3z9M)

[![Pelajaran 2: Penjelajahan Lebih Dalam ke IoT - Sesi Tanya Jawab](https://img.youtube.com/vi/tTZYf9EST1E/0.jpg)](https://youtu.be/tTZYf9EST1E)

> 🎥 Klik gambar di atas untuk menonton video

## Kuis Sebelum Pelajaran

[Kuis Sebelum Pelajaran](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/3)

## Pendahuluan

Pelajaran ini membahas lebih dalam beberapa konsep yang telah dibahas pada pelajaran sebelumnya.

Dalam pelajaran ini, kita akan membahas:

* [Komponen dari aplikasi IoT](../../../../../1-getting-started/lessons/2-deeper-dive)
* [Penjelajahan lebih dalam tentang mikrokontroler](../../../../../1-getting-started/lessons/2-deeper-dive)
* [Penjelajahan lebih dalam tentang komputer papan tunggal](../../../../../1-getting-started/lessons/2-deeper-dive)

## Komponen dari Aplikasi IoT

Dua komponen utama dari aplikasi IoT adalah *Internet* dan *perangkat*. Mari kita lihat kedua komponen ini lebih detail.

### Perangkat

![Raspberry Pi 4](../../../../../translated_images/raspberry-pi-4.fd4590d308c3d456.id.jpg)

Bagian **Perangkat** dari IoT mengacu pada perangkat yang dapat berinteraksi dengan dunia fisik. Perangkat ini biasanya berupa komputer kecil dengan harga terjangkau, berjalan pada kecepatan rendah, dan menggunakan daya yang rendah - misalnya, mikrokontroler sederhana dengan RAM dalam ukuran kilobyte (berbeda dengan gigabyte pada PC) yang berjalan hanya pada beberapa ratus megahertz (berbeda dengan gigahertz pada PC), tetapi mengonsumsi daya yang sangat kecil sehingga dapat berjalan selama berminggu-minggu, berbulan-bulan, atau bahkan bertahun-tahun dengan baterai.

Perangkat ini berinteraksi dengan dunia fisik, baik dengan menggunakan sensor untuk mengumpulkan data dari lingkungan sekitar atau dengan mengontrol keluaran atau aktuator untuk membuat perubahan fisik. Contoh khasnya adalah termostat pintar - perangkat yang memiliki sensor suhu, alat untuk mengatur suhu yang diinginkan seperti dial atau layar sentuh, dan koneksi ke sistem pemanas atau pendingin yang dapat dihidupkan ketika suhu yang terdeteksi berada di luar rentang yang diinginkan. Sensor suhu mendeteksi bahwa ruangan terlalu dingin, dan aktuator menghidupkan pemanas.

![Diagram yang menunjukkan suhu dan dial sebagai input ke perangkat IoT, dan kontrol pemanas sebagai output](../../../../../translated_images/basic-thermostat.a923217fd1f37e5a6f3390396a65c22a387419ea2dd17e518ec24315ba6ae9a8.id.png)

Ada berbagai macam perangkat yang dapat bertindak sebagai perangkat IoT, mulai dari perangkat keras khusus yang mendeteksi satu hal, hingga perangkat serbaguna, bahkan ponsel pintar Anda! Ponsel pintar dapat menggunakan sensor untuk mendeteksi dunia di sekitarnya, dan aktuator untuk berinteraksi dengan dunia - misalnya menggunakan sensor GPS untuk mendeteksi lokasi Anda dan speaker untuk memberikan instruksi navigasi ke tujuan.

✅ Pikirkan sistem lain di sekitar Anda yang membaca data dari sensor dan menggunakannya untuk membuat keputusan. Salah satu contohnya adalah termostat pada oven. Bisakah Anda menemukan lebih banyak contoh?

### Internet

Sisi **Internet** dari aplikasi IoT terdiri dari aplikasi yang dapat dihubungkan oleh perangkat IoT untuk mengirim dan menerima data, serta aplikasi lain yang dapat memproses data dari perangkat IoT dan membantu membuat keputusan tentang permintaan apa yang akan dikirim ke aktuator perangkat IoT.

Salah satu pengaturan yang umum adalah memiliki semacam layanan cloud yang dihubungkan oleh perangkat IoT, dan layanan cloud ini menangani hal-hal seperti keamanan, menerima pesan dari perangkat IoT, dan mengirim pesan kembali ke perangkat. Layanan cloud ini kemudian terhubung ke aplikasi lain yang dapat memproses atau menyimpan data sensor, atau menggunakan data sensor bersama data dari sistem lain untuk membuat keputusan.

Perangkat juga tidak selalu terhubung langsung ke Internet melalui WiFi atau koneksi kabel. Beberapa perangkat menggunakan jaringan mesh untuk saling berkomunikasi melalui teknologi seperti Bluetooth, yang terhubung melalui perangkat hub yang memiliki koneksi Internet.

Dalam contoh termostat pintar, termostat akan terhubung menggunakan WiFi rumah ke layanan cloud yang berjalan di cloud. Termostat akan mengirim data suhu ke layanan cloud ini, dan dari sana data akan ditulis ke semacam basis data yang memungkinkan pemilik rumah untuk memeriksa suhu saat ini dan suhu sebelumnya menggunakan aplikasi ponsel. Layanan lain di cloud akan mengetahui suhu yang diinginkan oleh pemilik rumah, dan mengirim pesan kembali ke perangkat IoT melalui layanan cloud untuk memberi tahu sistem pemanas untuk menyala atau mati.

![Diagram yang menunjukkan suhu dan dial sebagai input ke perangkat IoT, perangkat IoT dengan komunikasi dua arah ke cloud, yang pada gilirannya memiliki komunikasi dua arah ke ponsel, dan kontrol pemanas sebagai output dari perangkat IoT](../../../../../translated_images/mobile-controlled-thermostat.4a994010473d8d6a52ba68c67e5f02dc8928c717e93ca4b9bc55525aa75bbb60.id.png)

Versi yang lebih pintar bahkan dapat menggunakan AI di cloud dengan data dari sensor lain yang terhubung ke perangkat IoT lain seperti sensor keberadaan yang mendeteksi ruangan mana yang digunakan, serta data seperti cuaca dan bahkan kalender Anda, untuk membuat keputusan tentang bagaimana mengatur suhu secara cerdas. Misalnya, AI dapat mematikan pemanas jika membaca dari kalender Anda bahwa Anda sedang berlibur, atau mematikan pemanas berdasarkan ruangan demi ruangan tergantung pada ruangan mana yang Anda gunakan, belajar dari data untuk menjadi semakin akurat seiring waktu.

![Diagram yang menunjukkan beberapa sensor suhu dan dial sebagai input ke perangkat IoT, perangkat IoT dengan komunikasi dua arah ke cloud, yang pada gilirannya memiliki komunikasi dua arah ke ponsel, kalender, dan layanan cuaca, serta kontrol pemanas sebagai output dari perangkat IoT](../../../../../translated_images/smarter-thermostat.a75855f15d2d9e63.id.png)

✅ Data apa lagi yang dapat membantu membuat termostat yang terhubung ke Internet menjadi lebih pintar?

### IoT di Edge

Meskipun huruf I dalam IoT berarti Internet, perangkat ini tidak harus terhubung ke Internet. Dalam beberapa kasus, perangkat dapat terhubung ke perangkat 'edge' - perangkat gateway yang berjalan di jaringan lokal Anda sehingga Anda dapat memproses data tanpa harus mengirimkannya melalui Internet. Ini bisa lebih cepat jika Anda memiliki banyak data atau koneksi Internet yang lambat, memungkinkan Anda untuk bekerja secara offline di tempat di mana konektivitas Internet tidak memungkinkan seperti di kapal atau di area bencana saat merespons krisis kemanusiaan, dan memungkinkan Anda menjaga data tetap pribadi. Beberapa perangkat akan menjalankan kode pemrosesan yang dibuat menggunakan alat cloud dan menjalankannya secara lokal untuk mengumpulkan dan merespons data tanpa menggunakan koneksi Internet untuk membuat keputusan.

Salah satu contohnya adalah perangkat rumah pintar seperti Apple HomePod, Amazon Alexa, atau Google Home, yang akan mendengarkan suara Anda menggunakan model AI yang dilatih di cloud, tetapi berjalan secara lokal di perangkat. Perangkat ini akan 'bangun' ketika kata atau frasa tertentu diucapkan, dan hanya kemudian mengirimkan ucapan Anda melalui Internet untuk diproses. Perangkat akan berhenti mengirimkan ucapan pada titik yang sesuai seperti ketika mendeteksi jeda dalam ucapan Anda. Semua yang Anda katakan sebelum membangunkan perangkat dengan kata bangun, dan semua yang Anda katakan setelah perangkat berhenti mendengarkan tidak akan dikirim melalui Internet ke penyedia perangkat, dan oleh karena itu akan tetap bersifat pribadi.

✅ Pikirkan skenario lain di mana privasi penting sehingga pemrosesan data lebih baik dilakukan di edge daripada di cloud. Sebagai petunjuk - pikirkan perangkat IoT dengan kamera atau perangkat pencitraan lainnya.

### Keamanan IoT

Dengan setiap koneksi Internet, keamanan adalah pertimbangan penting. Ada lelucon lama yang mengatakan 'huruf S dalam IoT berarti Security' - tidak ada huruf 'S' dalam IoT, yang menyiratkan bahwa IoT tidak aman.

Perangkat IoT terhubung ke layanan cloud, dan oleh karena itu hanya seaman layanan cloud tersebut - jika layanan cloud Anda memungkinkan perangkat apa pun untuk terhubung, maka data berbahaya dapat dikirim, atau serangan virus dapat terjadi. Ini dapat memiliki konsekuensi dunia nyata yang sangat nyata karena perangkat IoT berinteraksi dan mengontrol perangkat lain. Misalnya, [worm Stuxnet](https://wikipedia.org/wiki/Stuxnet) memanipulasi katup dalam sentrifugal untuk merusaknya. Peretas juga telah memanfaatkan [keamanan yang buruk untuk mengakses monitor bayi](https://www.npr.org/sections/thetwo-way/2018/06/05/617196788/s-c-mom-says-baby-monitor-was-hacked-experts-say-many-devices-are-vulnerable) dan perangkat pengawasan rumah lainnya.

> 💁 Kadang-kadang perangkat IoT dan perangkat edge berjalan di jaringan yang sepenuhnya terisolasi dari Internet untuk menjaga data tetap pribadi dan aman. Ini dikenal sebagai [air-gapping](https://wikipedia.org/wiki/Air_gap_(networking)).

## Penjelajahan Lebih Dalam tentang Mikrokontroler

Pada pelajaran sebelumnya, kita telah memperkenalkan mikrokontroler. Sekarang mari kita lihat lebih dalam.

### CPU

CPU adalah 'otak' dari mikrokontroler. Ini adalah prosesor yang menjalankan kode Anda dan dapat mengirim data ke dan menerima data dari perangkat yang terhubung. CPU dapat memiliki satu atau lebih inti - pada dasarnya satu atau lebih CPU yang dapat bekerja bersama untuk menjalankan kode Anda.

CPU bergantung pada clock yang berdetak jutaan atau miliaran kali per detik. Setiap detak, atau siklus, menyinkronkan tindakan yang dapat dilakukan oleh CPU. Dengan setiap detak, CPU dapat menjalankan instruksi dari program, seperti mengambil data dari perangkat eksternal atau melakukan perhitungan matematis. Siklus reguler ini memungkinkan semua tindakan diselesaikan sebelum instruksi berikutnya diproses.

Semakin cepat siklus clock, semakin banyak instruksi yang dapat diproses setiap detik, dan oleh karena itu semakin cepat CPU. Kecepatan CPU diukur dalam [Hertz (Hz)](https://wikipedia.org/wiki/Hertz), satuan standar di mana 1 Hz berarti satu siklus atau detak clock per detik.

> 🎓 Kecepatan CPU sering diberikan dalam MHz atau GHz. 1MHz adalah 1 juta Hz, 1GHz adalah 1 miliar Hz.

> 💁 CPU menjalankan program menggunakan [siklus fetch-decode-execute](https://wikipedia.org/wiki/Instruction_cycle). Untuk setiap detak clock, CPU akan mengambil instruksi berikutnya dari memori, mendekodenya, lalu menjalankannya seperti menggunakan unit logika aritmatika (ALU) untuk menambahkan 2 angka. Beberapa eksekusi akan memakan waktu beberapa detak untuk dijalankan, sehingga siklus berikutnya akan berjalan pada detak berikutnya setelah instruksi selesai.

![Siklus fetch-decode-execute yang menunjukkan fetch mengambil instruksi dari program yang disimpan di RAM, lalu mendekode dan mengeksekusinya di CPU](../../../../../translated_images/fetch-decode-execute.2fd6f150f6280392807f4475382319abd0cee0b90058e1735444d6baa6f2078c.id.png)

Mikrokontroler memiliki kecepatan clock yang jauh lebih rendah dibandingkan komputer desktop atau laptop, atau bahkan sebagian besar ponsel pintar. Misalnya, Wio Terminal memiliki CPU yang berjalan pada 120MHz atau 120.000.000 siklus per detik.

✅ Komputer PC atau Mac rata-rata memiliki CPU dengan beberapa inti yang berjalan pada beberapa GigaHertz, yang berarti clock berdetak miliaran kali per detik. Cari tahu kecepatan clock komputer Anda dan bandingkan seberapa banyak lebih cepat dibandingkan Wio Terminal.

Setiap siklus clock menarik daya dan menghasilkan panas. Semakin cepat detaknya, semakin banyak daya yang dikonsumsi dan semakin banyak panas yang dihasilkan. PC memiliki heat sink dan kipas untuk menghilangkan panas, tanpa itu mereka akan terlalu panas dan mati dalam hitungan detik. Mikrokontroler sering kali tidak memiliki keduanya karena mereka berjalan jauh lebih dingin dan oleh karena itu jauh lebih lambat. PC berjalan dengan daya listrik atau baterai besar selama beberapa jam, sedangkan mikrokontroler dapat berjalan selama berhari-hari, berbulan-bulan, atau bahkan bertahun-tahun dengan baterai kecil. Mikrokontroler juga dapat memiliki inti yang berjalan pada kecepatan berbeda, beralih ke inti yang lebih lambat dan hemat daya ketika permintaan pada CPU rendah untuk mengurangi konsumsi daya.

> 💁 Beberapa PC dan Mac mengadopsi campuran inti daya tinggi yang cepat dan inti daya rendah yang lebih lambat, beralih untuk menghemat baterai. Misalnya, chip M1 di laptop Apple terbaru dapat beralih antara 4 inti kinerja dan 4 inti efisiensi untuk mengoptimalkan masa pakai baterai atau kecepatan tergantung pada tugas yang dijalankan.

✅ Lakukan sedikit penelitian: Baca tentang CPU di [artikel Wikipedia tentang CPU](https://wikipedia.org/wiki/Central_processing_unit)

#### Tugas

Selidiki Wio Terminal.

Jika Anda menggunakan Wio Terminal untuk pelajaran ini, coba temukan CPU-nya. Temukan bagian *Hardware Overview* di [halaman produk Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) untuk melihat gambar bagian dalamnya, dan coba temukan CPU melalui jendela plastik transparan di bagian belakang.

### Memori

Mikrokontroler biasanya memiliki dua jenis memori - memori program dan memori akses acak (RAM).

Memori program bersifat non-volatile, yang berarti apa pun yang ditulis ke dalamnya akan tetap ada meskipun perangkat tidak memiliki daya. Memori ini menyimpan kode program Anda.

RAM adalah memori yang digunakan oleh program untuk berjalan, berisi variabel yang dialokasikan oleh program Anda dan data yang dikumpulkan dari perangkat periferal. RAM bersifat volatile, sehingga ketika daya mati, isinya akan hilang, yang secara efektif mereset program Anda.
🎓 Memori program menyimpan kode Anda dan tetap ada meskipun tidak ada daya.
> 🎓 RAM digunakan untuk menjalankan program Anda dan akan direset ketika tidak ada daya

Seperti halnya CPU, memori pada mikrokontroler jauh lebih kecil dibandingkan dengan PC atau Mac. Sebuah PC biasa mungkin memiliki 8 Gigabyte (GB) RAM, atau 8.000.000.000 byte, di mana setiap byte cukup untuk menyimpan satu huruf atau angka dari 0-255. Sebuah mikrokontroler biasanya hanya memiliki Kilobyte (KB) RAM, dengan satu kilobyte setara dengan 1.000 byte. Wio Terminal yang disebutkan di atas memiliki 192KB RAM, atau 192.000 byte - lebih dari 40.000 kali lebih kecil dibandingkan PC rata-rata!

Diagram di bawah ini menunjukkan perbedaan ukuran relatif antara 192KB dan 8GB - titik kecil di tengah mewakili 192KB.

![Perbandingan antara 192KB dan 8GB - lebih dari 40.000 kali lebih besar](../../../../../translated_images/ram-comparison.6beb73541b42ac6f.id.png)

Penyimpanan program juga lebih kecil dibandingkan PC. Sebuah PC biasa mungkin memiliki hard drive 500GB untuk penyimpanan program, sedangkan mikrokontroler mungkin hanya memiliki kilobyte atau beberapa megabyte (MB) penyimpanan (1MB adalah 1.000KB, atau 1.000.000 byte). Wio Terminal memiliki 4MB penyimpanan program.

✅ Lakukan sedikit riset: Berapa banyak RAM dan penyimpanan yang dimiliki komputer yang Anda gunakan untuk membaca ini? Bagaimana perbandingannya dengan mikrokontroler?

### Input/Output

Mikrokontroler membutuhkan koneksi input dan output (I/O) untuk membaca data dari sensor dan mengirim sinyal kontrol ke aktuator. Biasanya, mikrokontroler memiliki sejumlah pin input/output serbaguna (GPIO). Pin ini dapat dikonfigurasi melalui perangkat lunak sebagai input (menerima sinyal) atau output (mengirim sinyal).

🧠⬅️ Pin input digunakan untuk membaca nilai dari sensor

🧠➡️ Pin output mengirim instruksi ke aktuator

✅ Anda akan mempelajari lebih lanjut tentang ini di pelajaran berikutnya.

#### Tugas

Teliti Wio Terminal.

Jika Anda menggunakan Wio Terminal untuk pelajaran ini, temukan pin GPIO. Cari bagian *Pinout diagram* di [halaman produk Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) untuk mengetahui pin mana yang mana. Wio Terminal dilengkapi dengan stiker yang dapat Anda pasang di bagian belakang dengan nomor pin, jadi pasang sekarang jika belum.

### Ukuran fisik

Mikrokontroler biasanya berukuran kecil, dengan yang terkecil, [Freescale Kinetis KL03 MCU cukup kecil untuk muat di lekukan bola golf](https://www.edn.com/tiny-arm-cortex-m0-based-mcu-shrinks-package/). Hanya CPU di PC saja bisa berukuran 40mm x 40mm, dan itu belum termasuk heat sink dan kipas yang diperlukan agar CPU dapat berjalan lebih dari beberapa detik tanpa kepanasan, yang jauh lebih besar dibandingkan mikrokontroler lengkap. Kit pengembang Wio Terminal dengan mikrokontroler, casing, layar, dan berbagai koneksi serta komponen tidak jauh lebih besar dari CPU Intel i9 tanpa heat sink dan kipas!

| Perangkat                       | Ukuran                |
| ------------------------------- | --------------------- |
| Freescale Kinetis KL03          | 1.6mm x 2mm x 1mm     |
| Wio Terminal                    | 72mm x 57mm x 12mm    |
| Intel i9 CPU, Heat sink dan kipas | 136mm x 145mm x 103mm |

### Framework dan sistem operasi

Karena kecepatan dan ukuran memori yang rendah, mikrokontroler tidak menjalankan sistem operasi (OS) dalam pengertian desktop. Sistem operasi yang membuat komputer Anda berjalan (Windows, Linux, atau macOS) membutuhkan banyak memori dan daya pemrosesan untuk menjalankan tugas-tugas yang sama sekali tidak diperlukan oleh mikrokontroler. Ingat bahwa mikrokontroler biasanya diprogram untuk melakukan satu atau lebih tugas yang sangat spesifik, berbeda dengan komputer umum seperti PC atau Mac yang perlu mendukung antarmuka pengguna, memutar musik atau film, menyediakan alat untuk menulis dokumen atau kode, bermain game, atau menjelajahi Internet.

Untuk memprogram mikrokontroler tanpa OS, Anda memerlukan beberapa alat untuk membangun kode Anda agar dapat dijalankan oleh mikrokontroler, menggunakan API yang dapat berkomunikasi dengan periferal. Setiap mikrokontroler berbeda, jadi produsen biasanya mendukung framework standar yang memungkinkan Anda mengikuti 'resep' standar untuk membangun kode Anda dan menjalankannya di mikrokontroler mana pun yang mendukung framework tersebut.

Anda juga dapat memprogram mikrokontroler menggunakan OS - sering disebut sebagai sistem operasi waktu nyata (RTOS), karena dirancang untuk menangani pengiriman data ke dan dari periferal secara waktu nyata. Sistem operasi ini sangat ringan dan menyediakan fitur seperti:

* Multi-threading, memungkinkan kode Anda menjalankan lebih dari satu blok kode secara bersamaan, baik pada beberapa inti atau secara bergantian pada satu inti
* Jaringan untuk memungkinkan komunikasi melalui Internet secara aman
* Komponen antarmuka pengguna grafis (GUI) untuk membangun antarmuka pengguna (UI) pada perangkat yang memiliki layar.

✅ Baca lebih lanjut tentang beberapa RTOS yang berbeda: [Azure RTOS](https://azure.microsoft.com/services/rtos/?WT.mc_id=academic-17441-jabenn), [FreeRTOS](https://www.freertos.org), [Zephyr](https://www.zephyrproject.org)

#### Arduino

![Logo Arduino](../../../../../images/arduino-logo.svg)

[Arduino](https://www.arduino.cc) mungkin adalah framework mikrokontroler yang paling populer, terutama di kalangan pelajar, hobiis, dan pembuat. Arduino adalah platform elektronik open source yang menggabungkan perangkat lunak dan perangkat keras. Anda dapat membeli papan kompatibel Arduino dari Arduino sendiri atau dari produsen lain, lalu memprogramnya menggunakan framework Arduino.

Papan Arduino diprogram dalam C atau C++. Menggunakan C/C++ memungkinkan kode Anda dikompilasi menjadi sangat kecil dan berjalan cepat, sesuatu yang diperlukan pada perangkat terbatas seperti mikrokontroler. Inti dari aplikasi Arduino disebut sebagai sketch dan merupakan kode C/C++ dengan 2 fungsi - `setup` dan `loop`. Ketika papan dinyalakan, kode framework Arduino akan menjalankan fungsi `setup` sekali, lalu menjalankan fungsi `loop` berulang kali, terus-menerus hingga daya dimatikan.

Anda akan menulis kode setup Anda di fungsi `setup`, seperti menghubungkan ke WiFi dan layanan cloud atau menginisialisasi pin untuk input dan output. Kode loop Anda kemudian akan berisi kode pemrosesan, seperti membaca dari sensor dan mengirimkan nilainya ke cloud. Biasanya Anda akan menyertakan penundaan di setiap loop, misalnya, jika Anda hanya ingin data sensor dikirim setiap 10 detik, Anda akan menambahkan penundaan 10 detik di akhir loop sehingga mikrokontroler dapat tidur, menghemat daya, lalu menjalankan loop lagi saat diperlukan 10 detik kemudian.

![Sebuah sketch Arduino menjalankan setup terlebih dahulu, lalu menjalankan loop berulang kali](../../../../../translated_images/arduino-sketch.79590cb837ff7a7c6a68d1afda6cab83fd53d3bb1bd9a8bf2eaf8d693a4d3ea6.id.png)

✅ Arsitektur program ini dikenal sebagai *event loop* atau *message loop*. Banyak aplikasi menggunakan ini di balik layar dan ini adalah standar untuk sebagian besar aplikasi desktop yang berjalan di OS seperti Windows, macOS, atau Linux. Fungsi `loop` mendengarkan pesan dari komponen antarmuka pengguna seperti tombol, atau perangkat seperti keyboard, dan meresponsnya. Anda dapat membaca lebih lanjut di [artikel tentang event loop](https://wikipedia.org/wiki/Event_loop).

Arduino menyediakan pustaka standar untuk berinteraksi dengan mikrokontroler dan pin I/O, dengan implementasi berbeda di balik layar untuk dijalankan pada mikrokontroler yang berbeda. Misalnya, fungsi [`delay`](https://www.arduino.cc/reference/en/language/functions/time/delay/) akan menghentikan program untuk jangka waktu tertentu, fungsi [`digitalRead`](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/) akan membaca nilai `HIGH` atau `LOW` dari pin tertentu, terlepas dari papan mana kode tersebut dijalankan. Pustaka standar ini berarti bahwa kode Arduino yang ditulis untuk satu papan dapat dikompilasi ulang untuk papan Arduino lainnya dan akan berjalan, asalkan pin sama dan papan mendukung fitur yang sama.

Ada ekosistem besar pustaka Arduino pihak ketiga yang memungkinkan Anda menambahkan fitur tambahan ke proyek Arduino Anda, seperti menggunakan sensor dan aktuator atau menghubungkan ke layanan IoT cloud.

##### Tugas

Teliti Wio Terminal.

Jika Anda menggunakan Wio Terminal untuk pelajaran ini, baca ulang kode yang Anda tulis di pelajaran sebelumnya. Temukan fungsi `setup` dan `loop`. Pantau output serial untuk melihat fungsi loop dipanggil berulang kali. Cobalah menambahkan kode ke fungsi `setup` untuk menulis ke port serial dan amati bahwa kode ini hanya dipanggil sekali setiap kali Anda me-reboot. Cobalah me-reboot perangkat Anda dengan sakelar daya di samping untuk menunjukkan bahwa ini dipanggil setiap kali perangkat di-reboot.

## Penjelajahan lebih dalam tentang komputer papan tunggal

Pada pelajaran sebelumnya, kita telah memperkenalkan komputer papan tunggal. Sekarang mari kita lihat lebih dalam.

### Raspberry Pi

![Logo Raspberry Pi](../../../../../translated_images/raspberry-pi-logo.4efaa16605cee054.id.png)

[Raspberry Pi Foundation](https://www.raspberrypi.org) adalah sebuah badan amal dari Inggris yang didirikan pada tahun 2009 untuk mempromosikan studi ilmu komputer, terutama di tingkat sekolah. Sebagai bagian dari misi ini, mereka mengembangkan komputer papan tunggal yang disebut Raspberry Pi. Raspberry Pi saat ini tersedia dalam 3 varian - versi ukuran penuh, Pi Zero yang lebih kecil, dan modul komputasi yang dapat dibangun ke dalam perangkat IoT akhir Anda.

![Raspberry Pi 4](../../../../../translated_images/raspberry-pi-4.fd4590d308c3d456.id.jpg)

Iterasi terbaru dari Raspberry Pi ukuran penuh adalah Raspberry Pi 4B. Ini memiliki CPU quad-core (4 inti) yang berjalan pada 1,5GHz, RAM 2, 4, atau 8GB, ethernet gigabit, WiFi, 2 port HDMI yang mendukung layar 4k, port output audio dan video komposit, port USB (2 USB 2.0, 2 USB 3.0), 40 pin GPIO, konektor kamera untuk modul kamera Raspberry Pi, dan slot kartu SD. Semua ini ada pada papan berukuran 88mm x 58mm x 19,5mm dan ditenagai oleh catu daya USB-C 3A. Harganya mulai dari US$35, jauh lebih murah dibandingkan PC atau Mac.

> 💁 Ada juga Pi400, komputer all-in-one dengan Pi4 yang terintegrasi ke dalam keyboard.

![Raspberry Pi Zero](../../../../../translated_images/raspberry-pi-zero.f7a4133e1e7d54bb.id.jpg)

Pi Zero jauh lebih kecil, dengan daya yang lebih rendah. Ini memiliki CPU single-core 1GHz, RAM 512MB, WiFi (pada model Zero W), satu port HDMI, satu port micro-USB, 40 pin GPIO, konektor kamera untuk modul kamera Raspberry Pi, dan slot kartu SD. Ukurannya 65mm x 30mm x 5mm, dan menggunakan daya yang sangat kecil. Pi Zero dihargai US$5, dengan versi W yang memiliki WiFi dihargai US$10.

> 🎓 CPU di kedua perangkat ini adalah prosesor ARM, berbeda dengan prosesor Intel/AMD x86 atau x64 yang Anda temukan di sebagian besar PC dan Mac. Prosesor ini mirip dengan yang ditemukan di beberapa mikrokontroler, serta hampir semua ponsel, Microsoft Surface X, dan Apple Mac berbasis Apple Silicon yang baru.

Semua varian Raspberry Pi menjalankan versi Debian Linux yang disebut Raspberry Pi OS. Ini tersedia dalam versi lite tanpa desktop, yang sempurna untuk proyek 'headless' di mana Anda tidak memerlukan layar, atau versi penuh dengan lingkungan desktop lengkap, termasuk browser web, aplikasi perkantoran, alat pemrograman, dan game. Karena OS ini adalah versi Debian Linux, Anda dapat menginstal aplikasi atau alat apa pun yang berjalan di Debian dan dibangun untuk prosesor ARM di dalam Pi.

#### Tugas

Teliti Raspberry Pi.

Jika Anda menggunakan Raspberry Pi untuk pelajaran ini, baca tentang berbagai komponen perangkat keras di papan.

* Anda dapat menemukan detail tentang prosesor yang digunakan di [halaman dokumentasi perangkat keras Raspberry Pi](https://www.raspberrypi.org/documentation/hardware/raspberrypi/). Baca tentang prosesor yang digunakan di Pi Anda.
* Temukan pin GPIO. Baca lebih lanjut tentang pin ini di [dokumentasi GPIO Raspberry Pi](https://www.raspberrypi.org/documentation/hardware/raspberrypi/gpio/README.md). Gunakan [Panduan Penggunaan Pin GPIO](https://www.raspberrypi.org/documentation/usage/gpio/README.md) untuk mengidentifikasi pin yang berbeda pada Pi Anda.

### Pemrograman komputer papan tunggal

Komputer papan tunggal adalah komputer lengkap yang menjalankan OS penuh. Ini berarti ada berbagai bahasa pemrograman, framework, dan alat yang dapat Anda gunakan untuk memprogramnya, berbeda dengan mikrokontroler yang bergantung pada dukungan framework seperti Arduino. Sebagian besar bahasa pemrograman memiliki pustaka yang dapat mengakses pin GPIO untuk mengirim dan menerima data dari sensor dan aktuator.

✅ Bahasa pemrograman apa yang Anda kuasai? Apakah bahasa tersebut didukung di Linux?

Bahasa pemrograman yang paling umum digunakan untuk membangun aplikasi IoT di Raspberry Pi adalah Python. Ada ekosistem besar perangkat keras yang dirancang untuk Pi, dan hampir semuanya menyertakan kode yang relevan untuk digunakan sebagai pustaka Python. Beberapa ekosistem ini berbasis 'hats' - disebut demikian karena mereka dipasang di atas Pi seperti topi dan terhubung dengan soket besar ke 40 pin GPIO. Hats ini menyediakan kemampuan tambahan, seperti layar, sensor, mobil remote control, atau adaptor untuk memungkinkan Anda menyambungkan sensor dengan kabel standar.
### Penggunaan komputer papan tunggal dalam penerapan IoT profesional

Komputer papan tunggal digunakan dalam penerapan IoT profesional, bukan hanya sebagai kit pengembang. Perangkat ini dapat menjadi cara yang kuat untuk mengontrol perangkat keras dan menjalankan tugas-tugas kompleks seperti menjalankan model pembelajaran mesin. Sebagai contoh, terdapat [modul komputasi Raspberry Pi 4](https://www.raspberrypi.org/blog/raspberry-pi-compute-module-4/) yang menyediakan semua kemampuan Raspberry Pi 4 tetapi dalam bentuk yang lebih ringkas dan lebih murah tanpa sebagian besar port, dirancang untuk dipasang ke dalam perangkat keras khusus.

---

## 🚀 Tantangan

Tantangan pada pelajaran terakhir adalah mencatat sebanyak mungkin perangkat IoT yang ada di rumah, sekolah, atau tempat kerja Anda. Untuk setiap perangkat dalam daftar ini, menurut Anda apakah perangkat tersebut dibangun menggunakan mikrokontroler, komputer papan tunggal, atau bahkan campuran keduanya?

## Kuis setelah kuliah

[Kuis setelah kuliah](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/4)

## Tinjauan & Studi Mandiri

* Baca [panduan memulai Arduino](https://www.arduino.cc/en/Guide/Introduction) untuk memahami lebih lanjut tentang platform Arduino.
* Baca [pengantar Raspberry Pi 4](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/) untuk mempelajari lebih lanjut tentang Raspberry Pi.
* Pelajari lebih lanjut beberapa konsep dan akronim dalam artikel [Apa itu CPU, MPU, MCU, dan GPU di Electrical Engineering Journal](https://www.eejournal.com/article/what-the-faq-are-cpus-mpus-mcus-and-gpus/).

✅ Gunakan panduan-panduan ini, bersama dengan informasi biaya yang ditunjukkan melalui tautan di [panduan perangkat keras](../../../hardware.md) untuk memutuskan platform perangkat keras apa yang ingin Anda gunakan, atau apakah Anda lebih memilih menggunakan perangkat virtual.

## Tugas

[Bandingkan dan bedakan mikrokontroler dan komputer papan tunggal](assignment.md)

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diketahui bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.