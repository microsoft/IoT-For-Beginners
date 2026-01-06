<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9dd7f645ad1c6f20b72fee512987f772",
  "translation_date": "2025-08-27T22:51:18+00:00",
  "source_file": "1-getting-started/lessons/2-deeper-dive/README.md",
  "language_code": "ms"
}
-->
# Penyelaman Mendalam ke dalam IoT

![Gambaran sketchnote untuk pelajaran ini](../../../../../translated_images/lesson-2.324b0580d620c25e0a24fb7fddfc0b29a846dd4b82c08e7a9466d580ee78ce51.ms.jpg)

> Sketchnote oleh [Nitya Narasimhan](https://github.com/nitya). Klik imej untuk versi yang lebih besar.

Pelajaran ini diajar sebagai sebahagian daripada siri [Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) dari [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Pelajaran ini disampaikan dalam 2 video - satu pelajaran selama 1 jam, dan satu sesi selama 1 jam untuk mendalami bahagian pelajaran serta menjawab soalan.

[![Pelajaran 2: Penyelaman mendalam ke dalam IoT](https://img.youtube.com/vi/t0SySWw3z9M/0.jpg)](https://youtu.be/t0SySWw3z9M)

[![Pelajaran 2: Penyelaman mendalam ke dalam IoT - Waktu pejabat](https://img.youtube.com/vi/tTZYf9EST1E/0.jpg)](https://youtu.be/tTZYf9EST1E)

> 🎥 Klik imej di atas untuk menonton video

## Kuiz Pra-Pelajaran

[Kuiz Pra-Pelajaran](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/3)

## Pengenalan

Pelajaran ini mendalami beberapa konsep yang telah dibincangkan dalam pelajaran sebelumnya.

Dalam pelajaran ini kita akan membincangkan:

* [Komponen aplikasi IoT](../../../../../1-getting-started/lessons/2-deeper-dive)
* [Penyelaman mendalam ke dalam mikropengawal](../../../../../1-getting-started/lessons/2-deeper-dive)
* [Penyelaman mendalam ke dalam komputer papan tunggal](../../../../../1-getting-started/lessons/2-deeper-dive)

## Komponen aplikasi IoT

Dua komponen utama aplikasi IoT adalah *Internet* dan *peranti*. Mari kita lihat kedua-dua komponen ini dengan lebih terperinci.

### Peranti

![Raspberry Pi 4](../../../../../translated_images/raspberry-pi-4.fd4590d308c3d456.ms.jpg)

Bahagian **Peranti** dalam IoT merujuk kepada peranti yang boleh berinteraksi dengan dunia fizikal. Peranti ini biasanya adalah komputer kecil, berharga rendah, beroperasi pada kelajuan rendah dan menggunakan kuasa yang rendah - contohnya, mikropengawal mudah dengan RAM dalam kilobyte (berbanding gigabyte dalam PC) yang beroperasi hanya pada beberapa ratus megahertz (berbanding gigahertz dalam PC), tetapi kadang-kadang menggunakan kuasa yang sangat sedikit sehingga boleh beroperasi selama berminggu-minggu, berbulan-bulan atau bahkan bertahun-tahun dengan bateri.

Peranti ini berinteraksi dengan dunia fizikal, sama ada dengan menggunakan sensor untuk mengumpul data dari persekitaran mereka atau dengan mengawal output atau aktuator untuk membuat perubahan fizikal. Contoh biasa adalah termostat pintar - peranti yang mempunyai sensor suhu, cara untuk menetapkan suhu yang diingini seperti dail atau skrin sentuh, dan sambungan kepada sistem pemanasan atau penyejukan yang boleh dihidupkan apabila suhu yang dikesan berada di luar julat yang diingini. Sensor suhu mengesan bahawa bilik terlalu sejuk dan aktuator menghidupkan pemanasan.

![Rajah menunjukkan suhu dan dail sebagai input kepada peranti IoT, dan kawalan pemanas sebagai output](../../../../../translated_images/basic-thermostat.a923217fd1f37e5a6f3390396a65c22a387419ea2dd17e518ec24315ba6ae9a8.ms.png)

Terdapat pelbagai jenis peranti yang boleh bertindak sebagai peranti IoT, daripada perkakasan khusus yang mengesan satu perkara, kepada peranti tujuan umum, malah telefon pintar anda! Telefon pintar boleh menggunakan sensor untuk mengesan dunia di sekelilingnya, dan aktuator untuk berinteraksi dengan dunia - contohnya menggunakan sensor GPS untuk mengesan lokasi anda dan pembesar suara untuk memberikan arahan navigasi ke destinasi.

✅ Fikirkan sistem lain di sekeliling anda yang membaca data daripada sensor dan menggunakannya untuk membuat keputusan. Satu contoh adalah termostat pada ketuhar. Bolehkah anda mencari lebih banyak contoh?

### Internet

Bahagian **Internet** dalam aplikasi IoT terdiri daripada aplikasi yang peranti IoT boleh sambungkan untuk menghantar dan menerima data, serta aplikasi lain yang boleh memproses data daripada peranti IoT dan membantu membuat keputusan tentang permintaan yang perlu dihantar kepada aktuator peranti IoT.

Satu susunan biasa adalah mempunyai beberapa jenis perkhidmatan awan yang peranti IoT sambungkan, dan perkhidmatan awan ini mengendalikan perkara seperti keselamatan, serta menerima mesej daripada peranti IoT, dan menghantar mesej kembali kepada peranti. Perkhidmatan awan ini kemudian akan bersambung kepada aplikasi lain yang boleh memproses atau menyimpan data sensor, atau menggunakan data sensor bersama data daripada sistem lain untuk membuat keputusan.

Peranti juga tidak selalu bersambung terus ke Internet melalui WiFi atau sambungan berwayar. Sesetengah peranti menggunakan rangkaian mesh untuk berkomunikasi antara satu sama lain melalui teknologi seperti Bluetooth, bersambung melalui peranti hab yang mempunyai sambungan Internet.

Sebagai contoh termostat pintar, termostat akan bersambung menggunakan WiFi rumah kepada perkhidmatan awan yang berjalan di awan. Ia akan menghantar data suhu kepada perkhidmatan awan ini, dan dari situ ia akan ditulis ke pangkalan data yang membolehkan pemilik rumah memeriksa suhu semasa dan suhu lalu menggunakan aplikasi telefon. Perkhidmatan lain di awan akan mengetahui suhu yang diingini oleh pemilik rumah, dan menghantar mesej kembali kepada peranti IoT melalui perkhidmatan awan untuk memberitahu sistem pemanasan untuk dihidupkan atau dimatikan.

![Rajah menunjukkan suhu dan dail sebagai input kepada peranti IoT, peranti IoT dengan komunikasi dua hala ke awan, yang seterusnya mempunyai komunikasi dua hala ke telefon, dan kawalan pemanas sebagai output daripada peranti IoT](../../../../../translated_images/mobile-controlled-thermostat.4a994010473d8d6a52ba68c67e5f02dc8928c717e93ca4b9bc55525aa75bbb60.ms.png)

Versi yang lebih pintar boleh menggunakan AI di awan dengan data daripada sensor lain yang bersambung kepada peranti IoT lain seperti sensor kehadiran yang mengesan bilik mana yang digunakan, serta data seperti cuaca dan juga kalendar anda, untuk membuat keputusan tentang cara menetapkan suhu dengan cara yang pintar. Contohnya, ia boleh mematikan pemanasan jika ia membaca daripada kalendar anda bahawa anda sedang bercuti, atau mematikan pemanasan berdasarkan bilik demi bilik bergantung pada bilik mana yang anda gunakan, belajar daripada data untuk menjadi lebih tepat dari semasa ke semasa.

![Rajah menunjukkan pelbagai sensor suhu dan dail sebagai input kepada peranti IoT, peranti IoT dengan komunikasi dua hala ke awan, yang seterusnya mempunyai komunikasi dua hala ke telefon, kalendar dan perkhidmatan cuaca, dan kawalan pemanas sebagai output daripada peranti IoT](../../../../../translated_images/smarter-thermostat.a75855f15d2d9e63.ms.png)

✅ Apakah data lain yang boleh membantu menjadikan termostat bersambung Internet lebih pintar?

### IoT di Tepi

Walaupun huruf I dalam IoT bermaksud Internet, peranti ini tidak semestinya perlu bersambung ke Internet. Dalam sesetengah kes, peranti boleh bersambung kepada peranti 'tepi' - peranti gerbang yang berjalan di rangkaian tempatan anda yang membolehkan anda memproses data tanpa membuat panggilan melalui Internet. Ini boleh menjadi lebih pantas apabila anda mempunyai banyak data atau sambungan Internet yang perlahan, ia membolehkan anda beroperasi secara luar talian di mana sambungan Internet tidak mungkin seperti di atas kapal atau di kawasan bencana semasa bertindak balas terhadap krisis kemanusiaan, dan membolehkan anda menyimpan data secara peribadi. Sesetengah peranti akan mengandungi kod pemprosesan yang dicipta menggunakan alat awan dan menjalankan ini secara tempatan untuk mengumpul dan bertindak balas kepada data tanpa menggunakan sambungan Internet untuk membuat keputusan.

Satu contoh adalah peranti rumah pintar seperti Apple HomePod, Amazon Alexa, atau Google Home, yang akan mendengar suara anda menggunakan model AI yang dilatih di awan, tetapi berjalan secara tempatan pada peranti. Peranti ini akan 'bangun' apabila perkataan atau frasa tertentu disebut, dan hanya kemudian menghantar ucapan anda melalui Internet untuk diproses. Peranti akan berhenti menghantar ucapan pada titik yang sesuai seperti apabila ia mengesan jeda dalam ucapan anda. Segala yang anda katakan sebelum membangunkan peranti dengan perkataan bangun, dan segala yang anda katakan selepas peranti berhenti mendengar tidak akan dihantar melalui Internet kepada penyedia peranti, dan oleh itu akan kekal peribadi.

✅ Fikirkan senario lain di mana privasi adalah penting supaya pemprosesan data lebih baik dilakukan di tepi daripada di awan. Sebagai petunjuk - fikirkan peranti IoT dengan kamera atau peranti pengimejan lain padanya.

### Keselamatan IoT

Dengan mana-mana sambungan Internet, keselamatan adalah pertimbangan penting. Terdapat jenaka lama bahawa 'huruf S dalam IoT bermaksud Keselamatan' - tiada 'S' dalam IoT, yang menunjukkan ia tidak selamat.

Peranti IoT bersambung kepada perkhidmatan awan, dan oleh itu hanya selamat seperti perkhidmatan awan itu - jika perkhidmatan awan anda membenarkan mana-mana peranti untuk bersambung maka data berniat jahat boleh dihantar, atau serangan virus boleh berlaku. Ini boleh mempunyai akibat dunia sebenar kerana peranti IoT berinteraksi dan mengawal peranti lain. Contohnya, [cacing Stuxnet](https://wikipedia.org/wiki/Stuxnet) memanipulasi injap dalam centrifuge untuk merosakkannya. Penggodam juga telah mengambil kesempatan daripada [keselamatan yang lemah untuk mengakses monitor bayi](https://www.npr.org/sections/thetwo-way/2018/06/05/617196788/s-c-mom-says-baby-monitor-was-hacked-experts-say-many-devices-are-vulnerable) dan peranti pengawasan rumah lain.

> 💁 Kadang-kadang peranti IoT dan peranti tepi berjalan pada rangkaian yang benar-benar terasing daripada Internet untuk memastikan data peribadi dan selamat. Ini dikenali sebagai [air-gapping](https://wikipedia.org/wiki/Air_gap_(networking)).

## Penyelaman mendalam ke dalam mikropengawal

Dalam pelajaran sebelumnya, kita telah memperkenalkan mikropengawal. Sekarang mari kita lihat lebih mendalam ke dalamnya.

### CPU

CPU adalah 'otak' mikropengawal. Ia adalah pemproses yang menjalankan kod anda dan boleh menghantar data kepada dan menerima data daripada mana-mana peranti yang disambungkan. CPU boleh mengandungi satu atau lebih teras - pada dasarnya satu atau lebih CPU yang boleh bekerjasama untuk menjalankan kod anda.

CPU bergantung pada jam untuk berdetik berjuta-juta atau berbilion kali sesaat. Setiap detik, atau kitaran, menyelaraskan tindakan yang boleh diambil oleh CPU. Dengan setiap detik, CPU boleh melaksanakan arahan daripada program, seperti mendapatkan data daripada peranti luaran atau melakukan pengiraan matematik. Kitaran tetap ini membolehkan semua tindakan diselesaikan sebelum arahan seterusnya diproses.

Semakin pantas kitaran jam, semakin banyak arahan yang boleh diproses setiap saat, dan oleh itu semakin pantas CPU. Kelajuan CPU diukur dalam [Hertz (Hz)](https://wikipedia.org/wiki/Hertz), unit standard di mana 1 Hz bermaksud satu kitaran atau detik jam sesaat.

> 🎓 Kelajuan CPU sering diberikan dalam MHz atau GHz. 1MHz adalah 1 juta Hz, 1GHz adalah 1 bilion Hz.

> 💁 CPU melaksanakan program menggunakan [kitaran fetch-decode-execute](https://wikipedia.org/wiki/Instruction_cycle). Untuk setiap detik jam, CPU akan mengambil arahan seterusnya daripada memori, menyahkodnya, kemudian melaksanakannya seperti menggunakan unit logik aritmetik (ALU) untuk menambah 2 nombor. Sesetengah pelaksanaan akan mengambil masa beberapa detik untuk dijalankan, jadi kitaran seterusnya akan berjalan pada detik seterusnya selepas arahan selesai.

![Kitaran fetch decode execute menunjukkan fetch mengambil arahan daripada program yang disimpan dalam RAM, kemudian menyahkod dan melaksanakannya pada CPU](../../../../../translated_images/fetch-decode-execute.2fd6f150f6280392807f4475382319abd0cee0b90058e1735444d6baa6f2078c.ms.png)

Mikropengawal mempunyai kelajuan jam yang jauh lebih rendah daripada komputer meja atau komputer riba, atau bahkan kebanyakan telefon pintar. Contohnya, Wio Terminal mempunyai CPU yang berjalan pada 120MHz atau 120,000,000 kitaran sesaat.

✅ Komputer PC atau Mac biasa mempunyai CPU dengan pelbagai teras yang berjalan pada pelbagai GigaHertz, bermakna detik jam berlaku berbilion kali sesaat. Selidik kelajuan jam komputer anda dan bandingkan berapa kali lebih pantas ia berbanding Wio Terminal.

Setiap kitaran jam menggunakan kuasa dan menghasilkan haba. Semakin pantas detik, semakin banyak kuasa digunakan dan semakin banyak haba dihasilkan. PC mempunyai sink haba dan kipas untuk mengeluarkan haba, tanpanya ia akan terlalu panas dan berhenti dalam beberapa saat. Mikropengawal selalunya tidak mempunyai kedua-duanya kerana ia berjalan lebih sejuk dan oleh itu lebih perlahan. PC berjalan dengan kuasa utama atau bateri besar selama beberapa jam, mikropengawal boleh berjalan selama berhari-hari, berbulan-bulan, atau bahkan bertahun-tahun dengan bateri kecil. Mikropengawal juga boleh mempunyai teras yang berjalan pada kelajuan berbeza, beralih kepada teras kuasa rendah yang lebih perlahan apabila permintaan pada CPU rendah untuk mengurangkan penggunaan kuasa.

> 💁 Sesetengah PC dan Mac mula mengguna pakai campuran teras kuasa tinggi yang pantas dan teras kuasa rendah yang lebih perlahan, beralih untuk menjimatkan bateri. Contohnya, cip M1 dalam komputer riba Apple terkini boleh beralih antara 4 teras prestasi dan 4 teras kecekapan untuk mengoptimumkan hayat bateri atau kelajuan bergantung pada tugas yang dijalankan.

✅ Lakukan sedikit penyelidikan: Baca tentang CPU dalam [artikel Wikipedia CPU](https://wikipedia.org/wiki/Central_processing_unit)

#### Tugasan

Selidik Wio Terminal.

Jika anda menggunakan Wio Terminal untuk pelajaran ini, cuba cari CPU. Cari bahagian *Hardware Overview* pada [halaman produk Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) untuk gambar dalaman, dan cuba cari CPU melalui tingkap plastik lutsinar di bahagian belakang.

### Memori

Mikropengawal biasanya mempunyai dua jenis memori - memori program dan memori capaian rawak (RAM).

Memori program adalah tidak mudah hilang, yang bermaksud apa sahaja yang ditulis padanya akan kekal apabila tiada kuasa pada peranti. Ini adalah memori yang menyimpan kod program anda.

RAM adalah memori yang digunakan oleh program untuk berjalan, mengandungi pembolehubah yang diperuntukkan oleh program anda dan data yang dikumpulkan daripada peranti luaran. RAM adalah mudah hilang, apabila kuasa terputus kandungannya akan hilang, secara efektif menetapkan semula program anda.
> 🎓 Memori program menyimpan kod anda dan kekal walaupun tiada kuasa.
🎓 RAM digunakan untuk menjalankan program anda dan akan direset apabila tiada kuasa

Seperti CPU, memori pada mikrokontroler jauh lebih kecil berbanding PC atau Mac. Sebuah PC biasa mungkin mempunyai 8 Gigabyte (GB) RAM, atau 8,000,000,000 bait, dengan setiap bait cukup ruang untuk menyimpan satu huruf atau nombor dari 0-255. Mikrokontroler biasanya hanya mempunyai Kilobyte (KB) RAM, dengan satu kilobyte bersamaan 1,000 bait. Wio terminal yang disebutkan di atas mempunyai 192KB RAM, atau 192,000 bait - lebih kecil 40,000 kali ganda berbanding PC biasa!

Rajah di bawah menunjukkan perbezaan saiz relatif antara 192KB dan 8GB - titik kecil di tengah mewakili 192KB.

![Perbandingan antara 192KB dan 8GB - lebih besar 40,000 kali ganda](../../../../../translated_images/ram-comparison.6beb73541b42ac6f.ms.png)

Storan program juga lebih kecil berbanding PC. Sebuah PC biasa mungkin mempunyai cakera keras 500GB untuk storan program, manakala mikrokontroler mungkin hanya mempunyai kilobyte atau beberapa megabyte (MB) storan (1MB adalah 1,000KB, atau 1,000,000 bait). Wio terminal mempunyai 4MB storan program.

✅ Lakukan sedikit penyelidikan: Berapa banyak RAM dan storan yang dimiliki komputer yang anda gunakan untuk membaca ini? Bagaimana ia dibandingkan dengan mikrokontroler?

### Input/Output

Mikrokontroler memerlukan sambungan input dan output (I/O) untuk membaca data dari sensor dan menghantar isyarat kawalan kepada aktuator. Ia biasanya mengandungi beberapa pin input/output tujuan umum (GPIO). Pin ini boleh dikonfigurasi dalam perisian untuk menjadi input (iaitu menerima isyarat), atau output (menghantar isyarat).

🧠⬅️ Pin input digunakan untuk membaca nilai dari sensor

🧠➡️ Pin output menghantar arahan kepada aktuator

✅ Anda akan belajar lebih lanjut tentang ini dalam pelajaran seterusnya.

#### Tugasan

Selidiki Wio Terminal.

Jika anda menggunakan Wio Terminal untuk pelajaran ini, cari pin GPIO. Cari bahagian *Pinout diagram* pada [halaman produk Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) untuk mengetahui pin mana yang mana. Wio Terminal dilengkapi dengan pelekat yang boleh anda pasang di belakang dengan nombor pin, jadi pasang ini sekarang jika anda belum melakukannya.

### Saiz fizikal

Mikrokontroler biasanya kecil saiznya, dengan yang terkecil, [Freescale Kinetis KL03 MCU cukup kecil untuk muat dalam lekuk bola golf](https://www.edn.com/tiny-arm-cortex-m0-based-mcu-shrinks-package/). CPU dalam PC sahaja boleh berukuran 40mm x 40mm, dan itu tidak termasuk sink haba dan kipas yang diperlukan untuk memastikan CPU dapat berjalan lebih dari beberapa saat tanpa terlalu panas, jauh lebih besar daripada mikrokontroler lengkap. Kit pembangun Wio terminal dengan mikrokontroler, casing, skrin dan pelbagai sambungan serta komponen tidak jauh lebih besar daripada CPU Intel i9 kosong, dan jauh lebih kecil daripada CPU dengan sink haba dan kipas!

| Peranti                          | Saiz                  |
| -------------------------------- | --------------------- |
| Freescale Kinetis KL03           | 1.6mm x 2mm x 1mm     |
| Wio terminal                     | 72mm x 57mm x 12mm    |
| Intel i9 CPU, Sink haba dan kipas | 136mm x 145mm x 103mm |

### Kerangka kerja dan sistem operasi

Disebabkan kelajuan dan saiz memori yang rendah, mikrokontroler tidak menjalankan sistem operasi (OS) dalam erti kata desktop. Sistem operasi yang membuat komputer anda berjalan (Windows, Linux atau macOS) memerlukan banyak memori dan kuasa pemprosesan untuk menjalankan tugas yang sama sekali tidak diperlukan oleh mikrokontroler. Ingat bahawa mikrokontroler biasanya diprogramkan untuk melaksanakan satu atau lebih tugas yang sangat spesifik, tidak seperti komputer serba guna seperti PC atau Mac yang perlu menyokong antara muka pengguna, memainkan muzik atau filem, menyediakan alat untuk menulis dokumen atau kod, bermain permainan, atau melayari Internet.

Untuk memprogram mikrokontroler tanpa OS, anda memerlukan beberapa alat untuk membolehkan anda membina kod anda dengan cara yang dapat dijalankan oleh mikrokontroler, menggunakan API yang dapat berkomunikasi dengan mana-mana periferal. Setiap mikrokontroler berbeza, jadi pengeluar biasanya menyokong kerangka kerja standard yang membolehkan anda mengikuti 'resipi' standard untuk membina kod anda dan menjalankannya pada mana-mana mikrokontroler yang menyokong kerangka kerja tersebut.

Anda boleh memprogram mikrokontroler menggunakan OS - sering dirujuk sebagai sistem operasi masa nyata (RTOS), kerana ia direka untuk mengendalikan penghantaran data ke dan dari periferal secara masa nyata. Sistem operasi ini sangat ringan dan menyediakan ciri seperti:

* Multi-threading, membolehkan kod anda menjalankan lebih daripada satu blok kod pada masa yang sama, sama ada pada pelbagai teras atau bergilir-gilir pada satu teras
* Rangkaian untuk membolehkan komunikasi melalui Internet dengan selamat
* Komponen antara muka pengguna grafik (GUI) untuk membina antara muka pengguna (UI) pada peranti yang mempunyai skrin.

✅ Baca tentang beberapa RTOS yang berbeza: [Azure RTOS](https://azure.microsoft.com/services/rtos/?WT.mc_id=academic-17441-jabenn), [FreeRTOS](https://www.freertos.org), [Zephyr](https://www.zephyrproject.org)

#### Arduino

![Logo Arduino](../../../../../images/arduino-logo.svg)

[Arduino](https://www.arduino.cc) mungkin merupakan kerangka kerja mikrokontroler yang paling popular, terutamanya di kalangan pelajar, penggemar dan pembuat. Arduino adalah platform elektronik sumber terbuka yang menggabungkan perisian dan perkakasan. Anda boleh membeli papan yang serasi dengan Arduino daripada Arduino sendiri atau daripada pengeluar lain, kemudian kod menggunakan kerangka kerja Arduino.

Papan Arduino dikodkan dalam C atau C++. Menggunakan C/C++ membolehkan kod anda dikompilasi dengan sangat kecil dan berjalan pantas, sesuatu yang diperlukan pada peranti terhad seperti mikrokontroler. Inti aplikasi Arduino dirujuk sebagai sketch dan merupakan kod C/C++ dengan 2 fungsi - `setup` dan `loop`. Apabila papan dihidupkan, kod kerangka kerja Arduino akan menjalankan fungsi `setup` sekali, kemudian ia akan menjalankan fungsi `loop` berulang kali, menjalankannya secara berterusan sehingga kuasa dimatikan.

Anda akan menulis kod persediaan anda dalam fungsi `setup`, seperti menyambung ke WiFi dan perkhidmatan awan atau memulakan pin untuk input dan output. Kod gelung anda kemudian akan mengandungi kod pemprosesan, seperti membaca dari sensor dan menghantar nilai ke awan. Anda biasanya akan memasukkan kelewatan dalam setiap gelung, contohnya, jika anda hanya mahu data sensor dihantar setiap 10 saat, anda akan menambah kelewatan 10 saat pada akhir gelung supaya mikrokontroler dapat tidur, menjimatkan kuasa, kemudian menjalankan gelung semula apabila diperlukan 10 saat kemudian.

![Sketch Arduino menjalankan setup terlebih dahulu, kemudian menjalankan loop berulang kali](../../../../../translated_images/arduino-sketch.79590cb837ff7a7c6a68d1afda6cab83fd53d3bb1bd9a8bf2eaf8d693a4d3ea6.ms.png)

✅ Seni bina program ini dikenali sebagai *event loop* atau *message loop*. Banyak aplikasi menggunakan ini di belakang tabir dan ia adalah standard untuk kebanyakan aplikasi desktop yang berjalan pada OS seperti Windows, macOS atau Linux. `loop` mendengar mesej daripada komponen antara muka pengguna seperti butang, atau peranti seperti papan kekunci, dan bertindak balas terhadapnya. Anda boleh membaca lebih lanjut dalam [artikel tentang event loop](https://wikipedia.org/wiki/Event_loop).

Arduino menyediakan perpustakaan standard untuk berinteraksi dengan mikrokontroler dan pin I/O, dengan pelbagai implementasi di belakang tabir untuk dijalankan pada mikrokontroler yang berbeza. Sebagai contoh, fungsi [`delay`](https://www.arduino.cc/reference/en/language/functions/time/delay/) akan menghentikan program untuk tempoh masa tertentu, fungsi [`digitalRead`](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/) akan membaca nilai `HIGH` atau `LOW` daripada pin yang diberikan, tanpa mengira papan mana kod itu dijalankan. Perpustakaan standard ini bermakna kod Arduino yang ditulis untuk satu papan boleh dikompilasi semula untuk mana-mana papan Arduino lain dan akan berjalan, dengan syarat pin adalah sama dan papan menyokong ciri yang sama.

Terdapat ekosistem besar perpustakaan Arduino pihak ketiga yang membolehkan anda menambah ciri tambahan pada projek Arduino anda, seperti menggunakan sensor dan aktuator atau menyambung ke perkhidmatan IoT awan.

##### Tugasan

Selidiki Wio Terminal.

Jika anda menggunakan Wio Terminal untuk pelajaran ini, baca semula kod yang anda tulis dalam pelajaran terakhir. Cari fungsi `setup` dan `loop`. Pantau output serial untuk fungsi loop yang dipanggil berulang kali. Cuba tambahkan kod ke fungsi `setup` untuk menulis ke port serial dan perhatikan bahawa kod ini hanya dipanggil sekali setiap kali anda reboot. Cuba reboot peranti anda dengan suis kuasa di sisi untuk menunjukkan bahawa ini dipanggil setiap kali peranti dihidupkan semula.

## Penyelidikan mendalam tentang komputer papan tunggal

Dalam pelajaran terakhir, kami memperkenalkan komputer papan tunggal. Sekarang mari kita lihat lebih mendalam tentangnya.

### Raspberry Pi

![Logo Raspberry Pi](../../../../../translated_images/raspberry-pi-logo.4efaa16605cee054.ms.png)

[The Raspberry Pi Foundation](https://www.raspberrypi.org) adalah sebuah badan amal dari UK yang ditubuhkan pada tahun 2009 untuk mempromosikan kajian sains komputer, terutamanya di peringkat sekolah. Sebagai sebahagian daripada misi ini, mereka membangunkan komputer papan tunggal, yang dipanggil Raspberry Pi. Raspberry Pi kini tersedia dalam 3 varian - versi bersaiz penuh, Pi Zero yang lebih kecil, dan modul pengkomputeran yang boleh dibina ke dalam peranti IoT akhir anda.

![Raspberry Pi 4](../../../../../translated_images/raspberry-pi-4.fd4590d308c3d456.ms.jpg)

Iterasi terbaru Raspberry Pi bersaiz penuh ialah Raspberry Pi 4B. Ia mempunyai CPU quad-core (4 teras) yang berjalan pada 1.5GHz, 2, 4, atau 8GB RAM, gigabit ethernet, WiFi, 2 port HDMI yang menyokong skrin 4k, port audio dan video komposit, port USB (2 USB 2.0, 2 USB 3.0), 40 pin GPIO, penyambung kamera untuk modul kamera Raspberry Pi, dan slot kad SD. Semua ini pada papan yang berukuran 88mm x 58mm x 19.5mm dan dikuasakan oleh bekalan kuasa USB-C 3A. Harga bermula dari US$35, jauh lebih murah daripada PC atau Mac.

> 💁 Terdapat juga Pi400, komputer semua dalam satu dengan Pi4 yang dibina ke dalam papan kekunci.

![Raspberry Pi Zero](../../../../../translated_images/raspberry-pi-zero.f7a4133e1e7d54bb.ms.jpg)

Pi Zero jauh lebih kecil, dengan kuasa yang lebih rendah. Ia mempunyai CPU teras tunggal 1GHz, 512MB RAM, WiFi (dalam model Zero W), satu port HDMI, satu port mikro-USB, 40 pin GPIO, penyambung kamera untuk modul kamera Raspberry Pi, dan slot kad SD. Ia berukuran 65mm x 30mm x 5mm, dan menggunakan kuasa yang sangat sedikit. Zero berharga US$5, dengan versi W yang mempunyai WiFi berharga US$10.

> 🎓 CPU dalam kedua-duanya adalah pemproses ARM, berbanding pemproses Intel/AMD x86 atau x64 yang anda temui dalam kebanyakan PC dan Mac. Ini serupa dengan CPU yang anda temui dalam beberapa mikrokontroler, serta hampir semua telefon bimbit, Microsoft Surface X, dan Apple Mac berasaskan Apple Silicon yang baru.

Semua varian Raspberry Pi menjalankan versi Debian Linux yang dipanggil Raspberry Pi OS. Ini tersedia sebagai versi lite tanpa desktop, yang sesuai untuk projek 'headless' di mana anda tidak memerlukan skrin, atau versi penuh dengan persekitaran desktop penuh, dengan pelayar web, aplikasi pejabat, alat pengkodan dan permainan. Oleh kerana OS adalah versi Debian Linux, anda boleh memasang mana-mana aplikasi atau alat yang berjalan pada Debian dan dibina untuk pemproses ARM di dalam Pi.

#### Tugasan

Selidiki Raspberry Pi.

Jika anda menggunakan Raspberry Pi untuk pelajaran ini, baca tentang komponen perkakasan yang berbeza pada papan.

* Anda boleh mendapatkan butiran tentang pemproses yang digunakan pada [halaman dokumentasi perkakasan Raspberry Pi](https://www.raspberrypi.org/documentation/hardware/raspberrypi/). Baca tentang pemproses yang digunakan dalam Pi yang anda gunakan.
* Cari pin GPIO. Baca lebih lanjut tentangnya di [dokumentasi GPIO Raspberry Pi](https://www.raspberrypi.org/documentation/hardware/raspberrypi/gpio/README.md). Gunakan [Panduan Penggunaan Pin GPIO](https://www.raspberrypi.org/documentation/usage/gpio/README.md) untuk mengenal pasti pin yang berbeza pada Pi anda.

### Memprogram komputer papan tunggal

Komputer papan tunggal adalah komputer penuh, menjalankan OS penuh. Ini bermakna terdapat pelbagai bahasa pengaturcaraan, kerangka kerja dan alat yang boleh anda gunakan untuk mengkodnya, tidak seperti mikrokontroler yang bergantung pada sokongan untuk papan dalam kerangka kerja seperti Arduino. Kebanyakan bahasa pengaturcaraan mempunyai perpustakaan yang boleh mengakses pin GPIO untuk menghantar dan menerima data daripada sensor dan aktuator.

✅ Apakah bahasa pengaturcaraan yang anda biasa gunakan? Adakah ia disokong pada Linux?

Bahasa pengaturcaraan yang paling biasa untuk membina aplikasi IoT pada Raspberry Pi ialah Python. Terdapat ekosistem besar perkakasan yang direka untuk Pi, dan hampir semua ini termasuk kod yang relevan yang diperlukan untuk menggunakannya sebagai perpustakaan Python. Sebahagian daripada ekosistem ini berdasarkan 'hats' - dipanggil begitu kerana ia duduk di atas Pi seperti topi dan disambungkan dengan soket besar ke 40 pin GPIO. Hats ini menyediakan keupayaan tambahan, seperti skrin, sensor, kereta kawalan jauh, atau penyesuai untuk membolehkan anda menyambungkan sensor dengan kabel standard.
### Penggunaan komputer papan tunggal dalam pelaksanaan IoT profesional

Komputer papan tunggal digunakan untuk pelaksanaan IoT profesional, bukan sekadar sebagai kit pembangun. Ia boleh menjadi cara yang berkuasa untuk mengawal perkakasan dan menjalankan tugas-tugas kompleks seperti menjalankan model pembelajaran mesin. Sebagai contoh, terdapat [modul Raspberry Pi 4 compute](https://www.raspberrypi.org/blog/raspberry-pi-compute-module-4/) yang menyediakan semua keupayaan Raspberry Pi 4 tetapi dalam bentuk yang lebih padat dan murah tanpa kebanyakan port, direka untuk dipasang ke dalam perkakasan tersuai.

---

## 🚀 Cabaran

Cabaran dalam pelajaran terakhir adalah untuk menyenaraikan sebanyak mungkin peranti IoT yang anda boleh temui di rumah, sekolah atau tempat kerja anda. Untuk setiap peranti dalam senarai ini, adakah anda fikir ia dibina menggunakan mikropengawal atau komputer papan tunggal, atau mungkin gabungan kedua-duanya?

## Kuiz selepas kuliah

[Kuiz selepas kuliah](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/4)

## Ulasan & Kajian Kendiri

* Baca [panduan memulakan Arduino](https://www.arduino.cc/en/Guide/Introduction) untuk memahami lebih lanjut tentang platform Arduino.
* Baca [pengenalan kepada Raspberry Pi 4](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/) untuk mengetahui lebih lanjut tentang Raspberry Pi.
* Pelajari lebih lanjut tentang beberapa konsep dan akronim dalam artikel [What the FAQ are CPUs, MPUs, MCUs, and GPUs dalam Electrical Engineering Journal](https://www.eejournal.com/article/what-the-faq-are-cpus-mpus-mcus-and-gpus/).

✅ Gunakan panduan-panduan ini, bersama dengan kos yang ditunjukkan melalui pautan dalam [panduan perkakasan](../../../hardware.md) untuk membuat keputusan tentang platform perkakasan yang anda ingin gunakan, atau jika anda lebih suka menggunakan peranti maya.

## Tugasan

[Bandingkan dan bezakan mikropengawal dan komputer papan tunggal](assignment.md)

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.