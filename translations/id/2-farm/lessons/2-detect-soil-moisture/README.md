<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4fb20273d299dc8d07a8f06c9cd0cdd9",
  "translation_date": "2025-08-27T21:49:30+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/README.md",
  "language_code": "id"
}
-->
C, diucapkan *I-squared-C*, adalah protokol multi-kontroler dan multi-periferal, di mana setiap perangkat yang terhubung dapat bertindak sebagai kontroler atau periferal yang berkomunikasi melalui bus I²C (nama untuk sistem komunikasi yang mentransfer data). Data dikirim dalam bentuk paket yang ditujukan untuk alamat perangkat tertentu yang terhubung.

> 💁 Model ini sebelumnya disebut master/slave, tetapi istilah ini mulai ditinggalkan karena asosiasinya dengan perbudakan. [Open Source Hardware Association telah mengadopsi istilah kontroler/periferal](https://www.oshwa.org/a-resolution-to-redefine-spi-signal-names/), meskipun Anda mungkin masih menemukan referensi ke istilah lama.

Perangkat memiliki alamat yang digunakan saat mereka terhubung ke bus I²C, dan biasanya alamat ini sudah ditentukan di perangkat. Misalnya, setiap jenis sensor Grove dari Seeed memiliki alamat yang sama, jadi semua sensor cahaya memiliki alamat yang sama, semua tombol memiliki alamat yang sama tetapi berbeda dari alamat sensor cahaya. Beberapa perangkat memiliki cara untuk mengubah alamat, seperti dengan mengubah pengaturan jumper atau menyolder pin bersama.

I²C memiliki bus yang terdiri dari 2 kabel utama, bersama dengan 2 kabel daya:

| Kabel | Nama | Deskripsi |
| ---- | --------- | ----------- |
| SDA | Serial Data | Kabel ini digunakan untuk mengirim data antar perangkat. |
| SCL | Serial Clock | Kabel ini mengirimkan sinyal jam pada kecepatan yang ditentukan oleh kontroler. |
| VCC | Voltage common collector | Sumber daya untuk perangkat. Kabel ini terhubung ke kabel SDA dan SCL untuk menyediakan daya mereka melalui resistor pull-up yang mematikan sinyal saat tidak ada perangkat yang menjadi kontroler. |
| GND | Ground | Memberikan ground umum untuk rangkaian listrik. |

![Bus I2C dengan 3 perangkat yang terhubung ke kabel SDA dan SCL, berbagi kabel ground yang sama](../../../../../translated_images/id/i2c.83da845dde02256bdd462dbe0d5145461416b74930571b89d1ae142841eeb584.png)

Untuk mengirim data, satu perangkat akan mengeluarkan kondisi mulai (start condition) untuk menunjukkan bahwa ia siap mengirim data. Perangkat tersebut kemudian menjadi kontroler. Kontroler kemudian mengirimkan alamat perangkat yang ingin dikomunikasikan, bersama dengan informasi apakah ia ingin membaca atau menulis data. Setelah data ditransmisikan, kontroler mengirimkan kondisi berhenti (stop condition) untuk menunjukkan bahwa ia telah selesai. Setelah itu, perangkat lain dapat menjadi kontroler dan mengirim atau menerima data.

2<sup>C memiliki batas kecepatan, dengan 3 mode berbeda yang berjalan pada kecepatan tetap. Mode tercepat adalah High Speed dengan kecepatan maksimum 3,4Mbps (megabit per detik), meskipun sangat sedikit perangkat yang mendukung kecepatan tersebut. Contohnya, Raspberry Pi terbatas pada mode cepat dengan kecepatan 400Kbps (kilobit per detik). Mode standar berjalan pada 100Kbps.

> 💁 Jika Anda menggunakan Raspberry Pi dengan Grove Base hat sebagai perangkat IoT Anda, Anda akan melihat sejumlah soket I<sup>2</sup>C pada papan yang dapat digunakan untuk berkomunikasi dengan sensor I<sup>2</sup>C. Sensor Grove analog juga menggunakan I<sup>2</sup>C dengan ADC untuk mengirimkan nilai analog sebagai data digital, sehingga sensor cahaya yang Anda gunakan mensimulasikan pin analog, dengan nilai yang dikirim melalui I<sup>2</sup>C karena Raspberry Pi hanya mendukung pin digital.

### Universal asynchronous receiver-transmitter (UART)

UART melibatkan sirkuit fisik yang memungkinkan dua perangkat untuk berkomunikasi. Setiap perangkat memiliki 2 pin komunikasi - transmit (Tx) dan receive (Rx), dengan pin Tx perangkat pertama terhubung ke pin Rx perangkat kedua, dan pin Tx perangkat kedua terhubung ke pin Rx perangkat pertama. Ini memungkinkan data dikirimkan dalam kedua arah.

* Perangkat 1 mengirimkan data dari pin Tx-nya, yang diterima oleh perangkat 2 di pin Rx-nya
* Perangkat 1 menerima data di pin Rx-nya yang dikirimkan oleh perangkat 2 dari pin Tx-nya

![UART dengan pin Tx pada satu chip terhubung ke pin Rx pada chip lain, dan sebaliknya](../../../../../translated_images/id/uart.d0dbd3fb9e3728c6.webp)

> 🎓 Data dikirimkan satu bit pada satu waktu, dan ini dikenal sebagai komunikasi *serial*. Sebagian besar sistem operasi dan mikrokontroler memiliki *serial ports*, yaitu koneksi yang dapat mengirim dan menerima data serial yang tersedia untuk kode Anda.

Perangkat UART memiliki [baud rate](https://wikipedia.org/wiki/Symbol_rate) (juga dikenal sebagai Symbol rate), yaitu kecepatan data akan dikirim dan diterima dalam bit per detik. Baud rate yang umum adalah 9.600, yang berarti 9.600 bit (0 dan 1) data dikirim setiap detik.

UART menggunakan bit awal dan bit akhir - yaitu mengirimkan bit awal untuk menunjukkan bahwa ia akan mengirimkan satu byte (8 bit) data, lalu bit akhir setelah mengirimkan 8 bit tersebut.

Kecepatan UART bergantung pada perangkat keras, tetapi bahkan implementasi tercepat tidak melebihi 6,5 Mbps (megabit per detik, atau jutaan bit, 0 atau 1, yang dikirim per detik).

Anda dapat menggunakan UART melalui pin GPIO - Anda dapat mengatur satu pin sebagai Tx dan pin lainnya sebagai Rx, lalu menghubungkannya ke perangkat lain.

> 💁 Jika Anda menggunakan Raspberry Pi dengan Grove Base hat sebagai perangkat IoT Anda, Anda akan melihat soket UART pada papan yang dapat digunakan untuk berkomunikasi dengan sensor yang menggunakan protokol UART.

### Serial Peripheral Interface (SPI)

SPI dirancang untuk komunikasi jarak pendek, seperti pada mikrokontroler untuk berbicara dengan perangkat penyimpanan seperti memori flash. SPI didasarkan pada model pengontrol/periferal dengan satu pengontrol (biasanya prosesor perangkat IoT) yang berinteraksi dengan beberapa periferal. Pengontrol mengendalikan semuanya dengan memilih periferal dan mengirim atau meminta data.

> 💁 Seperti I<sup>2</sup>C, istilah pengontrol dan periferal adalah perubahan terbaru, jadi Anda mungkin masih melihat istilah lama digunakan.

Pengontrol SPI menggunakan 3 kabel, bersama dengan 1 kabel tambahan per periferal. Periferal menggunakan 4 kabel. Kabel-kabel ini adalah:

| Kabel | Nama | Deskripsi |
| ---- | --------- | ----------- |
| COPI | Controller Output, Peripheral Input | Kabel ini untuk mengirim data dari pengontrol ke periferal. |
| CIPO | Controller Input, Peripheral Output | Kabel ini untuk mengirim data dari periferal ke pengontrol. |
| SCLK | Serial Clock | Kabel ini mengirimkan sinyal jam pada kecepatan yang diatur oleh pengontrol. |
| CS   | Chip Select | Pengontrol memiliki beberapa kabel, satu per periferal, dan setiap kabel terhubung ke kabel CS pada periferal yang sesuai. |

![SPI dengan satu pengontrol dan dua periferal](../../../../../translated_images/id/spi.297431d6f98b386b.webp)

Kabel CS digunakan untuk mengaktifkan satu periferal pada satu waktu, berkomunikasi melalui kabel COPI dan CIPO. Ketika pengontrol perlu mengganti periferal, ia menonaktifkan kabel CS yang terhubung ke periferal yang sedang aktif, lalu mengaktifkan kabel yang terhubung ke periferal berikutnya yang ingin diajak berkomunikasi.

SPI adalah *full-duplex*, yang berarti pengontrol dapat mengirim dan menerima data secara bersamaan dari periferal yang sama menggunakan kabel COPI dan CIPO. SPI menggunakan sinyal jam pada kabel SCLK untuk menjaga perangkat tetap sinkron, sehingga tidak memerlukan bit awal dan akhir seperti pengiriman langsung melalui UART.

Tidak ada batas kecepatan yang ditentukan untuk SPI, dengan implementasi sering kali mampu mentransmisikan beberapa megabyte data per detik.

Kit pengembang IoT sering kali mendukung SPI melalui beberapa pin GPIO. Misalnya, pada Raspberry Pi Anda dapat menggunakan pin GPIO 19, 21, 23, 24, dan 26 untuk SPI.

### Nirkabel

Beberapa sensor dapat berkomunikasi melalui protokol nirkabel standar, seperti Bluetooth (terutama Bluetooth Low Energy, atau BLE), LoRaWAN (protokol jaringan daya rendah jarak jauh), atau WiFi. Ini memungkinkan sensor jarak jauh yang tidak terhubung secara fisik ke perangkat IoT.

Salah satu contohnya adalah sensor kelembapan tanah komersial. Sensor ini akan mengukur kelembapan tanah di ladang, lalu mengirimkan data melalui LoRaWAN ke perangkat hub, yang akan memproses data atau mengirimkannya melalui Internet. Ini memungkinkan sensor berada jauh dari perangkat IoT yang mengelola data, mengurangi konsumsi daya dan kebutuhan jaringan WiFi besar atau kabel panjang.

BLE populer untuk sensor canggih seperti pelacak kebugaran yang digunakan di pergelangan tangan. Sensor ini menggabungkan beberapa sensor dan mengirimkan data sensor ke perangkat IoT dalam bentuk ponsel Anda melalui BLE.

✅ Apakah Anda memiliki sensor Bluetooth di tubuh Anda, di rumah Anda, atau di sekolah Anda? Ini mungkin termasuk sensor suhu, sensor keberadaan, pelacak perangkat, dan perangkat kebugaran.

Salah satu cara populer bagi perangkat komersial untuk terhubung adalah Zigbee. Zigbee menggunakan WiFi untuk membentuk jaringan mesh antara perangkat, di mana setiap perangkat terhubung ke sebanyak mungkin perangkat di sekitarnya, membentuk sejumlah besar koneksi seperti jaring laba-laba. Ketika satu perangkat ingin mengirim pesan ke Internet, ia dapat mengirimkannya ke perangkat terdekat, yang kemudian meneruskannya ke perangkat lain di sekitarnya, dan seterusnya, hingga mencapai koordinator dan dapat dikirim ke Internet.

> 🐝 Nama Zigbee mengacu pada tarian waggle lebah madu setelah mereka kembali ke sarang.

## Mengukur tingkat kelembapan tanah

Anda dapat mengukur tingkat kelembapan tanah menggunakan sensor kelembapan tanah, perangkat IoT, dan tanaman hias atau sebidang tanah di dekat Anda.

### Tugas - mengukur kelembapan tanah

Ikuti panduan yang relevan untuk mengukur kelembapan tanah menggunakan perangkat IoT Anda:

* [Arduino - Wio Terminal](wio-terminal-soil-moisture.md)
* [Komputer papan tunggal - Raspberry Pi](pi-soil-moisture.md)
* [Komputer papan tunggal - Perangkat virtual](virtual-device-soil-moisture.md)

## Kalibrasi sensor

Sensor bergantung pada pengukuran sifat listrik seperti resistansi atau kapasitansi.

> 🎓 Resistansi, diukur dalam ohm (Ω), adalah seberapa besar hambatan terhadap arus listrik yang mengalir melalui sesuatu. Ketika tegangan diterapkan pada suatu bahan, jumlah arus yang melewatinya bergantung pada resistansi bahan tersebut. Anda dapat membaca lebih lanjut di [halaman resistansi listrik di Wikipedia](https://wikipedia.org/wiki/Electrical_resistance_and_conductance).

> 🎓 Kapasitansi, diukur dalam farad (F), adalah kemampuan suatu komponen atau rangkaian untuk mengumpulkan dan menyimpan energi listrik. Anda dapat membaca lebih lanjut tentang kapasitansi di [halaman kapasitansi di Wikipedia](https://wikipedia.org/wiki/Capacitance).

Pengukuran ini tidak selalu berguna - bayangkan sensor suhu yang memberikan pengukuran 22,5KΩ! Sebaliknya, nilai yang diukur perlu dikonversi ke satuan yang berguna dengan dikalibrasi - yaitu mencocokkan nilai yang diukur dengan kuantitas yang diukur untuk memungkinkan pengukuran baru dikonversi ke satuan yang benar.

Beberapa sensor sudah dikalibrasi sebelumnya. Misalnya, sensor suhu yang Anda gunakan dalam pelajaran sebelumnya sudah dikalibrasi sehingga dapat mengembalikan pengukuran suhu dalam °C. Di pabrik, sensor pertama yang dibuat akan diekspos ke berbagai suhu yang diketahui dan resistansi diukur. Ini kemudian digunakan untuk membangun perhitungan yang dapat mengonversi dari nilai yang diukur dalam Ω (satuan resistansi) ke °C.

> 💁 Rumus untuk menghitung resistansi dari suhu disebut [persamaan Steinhart–Hart](https://wikipedia.org/wiki/Steinhart–Hart_equation).

### Kalibrasi sensor kelembapan tanah

Kelembapan tanah diukur menggunakan kandungan air gravimetrik atau volumetrik.

* Gravimetrik adalah berat air dalam satuan berat tanah yang diukur, sebagai jumlah kilogram air per kilogram tanah kering
* Volumetrik adalah volume air dalam satuan volume tanah yang diukur, sebagai jumlah meter kubik air per meter kubik tanah kering

> 🇺🇸 Untuk orang Amerika, karena konsistensi satuan, ini dapat diukur dalam pound alih-alih kilogram atau kaki kubik alih-alih meter kubik.

Sensor kelembapan tanah mengukur resistansi atau kapasitansi listrik - ini tidak hanya bervariasi berdasarkan kelembapan tanah, tetapi juga jenis tanah karena komponen dalam tanah dapat mengubah karakteristik listriknya. Idealnya, sensor harus dikalibrasi - yaitu mengambil pembacaan dari sensor dan membandingkannya dengan pengukuran yang ditemukan menggunakan pendekatan yang lebih ilmiah. Misalnya, sebuah laboratorium dapat menghitung kelembapan tanah gravimetrik menggunakan sampel dari ladang tertentu yang diambil beberapa kali dalam setahun, dan angka-angka ini digunakan untuk mengkalibrasi sensor, mencocokkan pembacaan sensor dengan kelembapan tanah gravimetrik.

![Grafik tegangan vs kandungan kelembapan tanah](../../../../../translated_images/id/soil-moisture-to-voltage.df86d80cda158700.webp)

Grafik di atas menunjukkan cara mengkalibrasi sensor. Tegangan diambil untuk sampel tanah yang kemudian diukur di laboratorium dengan membandingkan berat basah dengan berat kering (dengan mengukur berat basah, lalu mengeringkannya di oven dan mengukur berat kering). Setelah beberapa pembacaan diambil, ini dapat diplot pada grafik dan garis dipasang pada titik-titik tersebut. Garis ini kemudian dapat digunakan untuk mengonversi pembacaan sensor kelembapan tanah yang diambil oleh perangkat IoT menjadi pengukuran kelembapan tanah yang sebenarnya.

💁 Untuk sensor kelembapan tanah resistif, tegangan meningkat seiring dengan meningkatnya kelembapan tanah. Untuk sensor kelembapan tanah kapasitif, tegangan menurun seiring dengan meningkatnya kelembapan tanah, sehingga grafik untuk sensor ini akan miring ke bawah, bukan ke atas.

![Nilai kelembapan tanah diinterpolasi dari grafik](../../../../../translated_images/id/soil-moisture-to-voltage-with-reading.681cb3e1f8b68caf.webp)

Grafik di atas menunjukkan pembacaan tegangan dari sensor kelembapan tanah, dan dengan mengikuti garis pada grafik, kelembapan tanah yang sebenarnya dapat dihitung.

Pendekatan ini berarti petani hanya perlu mendapatkan beberapa pengukuran laboratorium untuk sebuah ladang, lalu mereka dapat menggunakan perangkat IoT untuk mengukur kelembapan tanah - secara drastis mempercepat waktu untuk mengambil pengukuran.

---

## 🚀 Tantangan

Sensor kelembapan tanah resistif dan kapasitif memiliki sejumlah perbedaan. Apa perbedaan tersebut, dan jenis mana (jika ada) yang terbaik untuk digunakan oleh petani? Apakah jawaban ini berubah antara negara berkembang dan negara maju?

## Kuis setelah kuliah

[Kuis setelah kuliah](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/12)

## Tinjauan & Studi Mandiri

Baca lebih lanjut tentang perangkat keras dan protokol yang digunakan oleh sensor dan aktuator:

* [Halaman Wikipedia GPIO](https://wikipedia.org/wiki/General-purpose_input/output)
* [Halaman Wikipedia UART](https://wikipedia.org/wiki/Universal_asynchronous_receiver-transmitter)
* [Halaman Wikipedia SPI](https://wikipedia.org/wiki/Serial_Peripheral_Interface)
* [Halaman Wikipedia I<sup>2</sup>C](https://wikipedia.org/wiki/I²C)
* [Halaman Wikipedia Zigbee](https://wikipedia.org/wiki/Zigbee)

## Tugas

[Kalibrasi sensor Anda](assignment.md)

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.