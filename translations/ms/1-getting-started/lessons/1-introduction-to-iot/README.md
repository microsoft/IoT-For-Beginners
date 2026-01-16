<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9bae08314d8487cb76ddf3d8797e1544",
  "translation_date": "2025-08-27T22:37:50+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/README.md",
  "language_code": "ms"
}
-->
# Pengenalan kepada IoT

![Gambaran sketchnote untuk pelajaran ini](../../../../../translated_images/ms/lesson-1.2606670fa61ee904687da5d6fa4e726639d524d064c895117da1b95b9ff6251d.jpg)

> Sketchnote oleh [Nitya Narasimhan](https://github.com/nitya). Klik imej untuk versi yang lebih besar.

Pelajaran ini diajar sebagai sebahagian daripada siri [Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) dari [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Pelajaran ini disampaikan dalam 2 video - satu pelajaran selama 1 jam, dan satu sesi soal jawab selama 1 jam yang mendalami bahagian pelajaran dan menjawab soalan.

[![Pelajaran 1: Pengenalan kepada IoT](https://img.youtube.com/vi/bVFfcYh6UBw/0.jpg)](https://youtu.be/bVFfcYh6UBw)

[![Pelajaran 1: Pengenalan kepada IoT - Sesi soal jawab](https://img.youtube.com/vi/YI772q5v3yI/0.jpg)](https://youtu.be/YI772q5v3yI)

> 🎥 Klik imej di atas untuk menonton video

## Kuiz sebelum pelajaran

[Kuiz sebelum pelajaran](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/1)

## Pengenalan

Pelajaran ini merangkumi beberapa topik pengenalan berkaitan Internet of Things, dan membantu anda memulakan persediaan perkakasan anda.

Dalam pelajaran ini, kita akan membincangkan:

* [Apakah 'Internet of Things'?](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Peranti IoT](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Sediakan peranti anda](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Aplikasi IoT](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Contoh peranti IoT di sekeliling anda](../../../../../1-getting-started/lessons/1-introduction-to-iot)

## Apakah 'Internet of Things'?

Istilah 'Internet of Things' diperkenalkan oleh [Kevin Ashton](https://wikipedia.org/wiki/Kevin_Ashton) pada tahun 1999, untuk merujuk kepada penyambungan Internet dengan dunia fizikal melalui sensor. Sejak itu, istilah ini digunakan untuk menggambarkan mana-mana peranti yang berinteraksi dengan dunia fizikal di sekelilingnya, sama ada dengan mengumpul data daripada sensor, atau menyediakan interaksi dunia nyata melalui aktuator (peranti yang melakukan sesuatu seperti menghidupkan suis atau menyalakan LED), biasanya disambungkan kepada peranti lain atau Internet.

> **Sensor** mengumpul maklumat dari dunia, seperti mengukur kelajuan, suhu atau lokasi.
>
> **Aktuator** menukar isyarat elektrik kepada interaksi dunia nyata seperti menghidupkan suis, menyalakan lampu, menghasilkan bunyi, atau menghantar isyarat kawalan kepada perkakasan lain, contohnya, untuk menghidupkan soket kuasa.

IoT sebagai bidang teknologi lebih daripada sekadar peranti - ia merangkumi perkhidmatan berasaskan awan yang boleh memproses data sensor, atau menghantar permintaan kepada aktuator yang disambungkan kepada peranti IoT. Ia juga merangkumi peranti yang tidak mempunyai atau tidak memerlukan sambungan Internet, yang sering dirujuk sebagai peranti tepi. Ini adalah peranti yang boleh memproses dan bertindak balas terhadap data sensor sendiri, biasanya menggunakan model AI yang dilatih di awan.

IoT adalah bidang teknologi yang berkembang pesat. Dianggarkan menjelang akhir tahun 2020, 30 bilion peranti IoT telah digunakan dan disambungkan ke Internet. Melihat ke masa depan, dianggarkan menjelang 2025, peranti IoT akan mengumpul hampir 80 zettabait data atau 80 trilion gigabait. Itu adalah jumlah data yang sangat besar!

![Graf menunjukkan peranti IoT aktif dari masa ke masa, dengan trend menaik dari bawah 5 bilion pada 2015 kepada lebih 30 bilion pada 2025](../../../../../images/connected-iot-devices.svg)

✅ Lakukan sedikit penyelidikan: Berapa banyak data yang dihasilkan oleh peranti IoT sebenarnya digunakan, dan berapa banyak yang terbuang? Mengapa begitu banyak data diabaikan?

Data ini adalah kunci kepada kejayaan IoT. Untuk menjadi pembangun IoT yang berjaya, anda perlu memahami data yang perlu dikumpulkan, cara mengumpulkannya, cara membuat keputusan berdasarkan data tersebut, dan cara menggunakan keputusan tersebut untuk berinteraksi dengan dunia fizikal jika diperlukan.

## Peranti IoT

Huruf **T** dalam IoT merujuk kepada **Things** - peranti yang berinteraksi dengan dunia fizikal di sekelilingnya sama ada dengan mengumpul data daripada sensor atau menyediakan interaksi dunia nyata melalui aktuator.

Peranti untuk kegunaan pengeluaran atau komersial, seperti penjejak kecergasan pengguna, atau pengawal mesin industri, biasanya dibuat khusus. Ia menggunakan papan litar khusus, mungkin juga pemproses khusus, yang direka untuk memenuhi keperluan tugas tertentu, sama ada cukup kecil untuk dipakai di pergelangan tangan, atau cukup tahan lasak untuk berfungsi dalam persekitaran kilang yang bersuhu tinggi, tekanan tinggi atau getaran tinggi.

Sebagai pembangun yang sama ada sedang belajar tentang IoT atau mencipta prototaip peranti, anda perlu bermula dengan kit pembangun. Ini adalah peranti IoT serba guna yang direka untuk pembangun gunakan, selalunya dengan ciri-ciri yang tidak akan ada pada peranti pengeluaran, seperti set pin luaran untuk menyambungkan sensor atau aktuator, perkakasan untuk menyokong penyahpepijatan, atau sumber tambahan yang akan menambah kos yang tidak perlu semasa pengeluaran besar-besaran.

Kit pembangun ini biasanya terbahagi kepada dua kategori - mikropengawal dan komputer papan tunggal. Ini akan diperkenalkan di sini, dan kita akan membincangkannya dengan lebih terperinci dalam pelajaran seterusnya.

> 💁 Telefon anda juga boleh dianggap sebagai peranti IoT serba guna, dengan sensor dan aktuator terbina dalam, dengan aplikasi yang berbeza menggunakan sensor dan aktuator dengan cara yang berbeza bersama perkhidmatan awan yang berbeza. Anda juga boleh menemui beberapa tutorial IoT yang menggunakan aplikasi telefon sebagai peranti IoT.

### Mikropengawal

Mikropengawal (juga dirujuk sebagai MCU, singkatan untuk unit mikropengawal) adalah komputer kecil yang terdiri daripada:

🧠 Satu atau lebih unit pemprosesan pusat (CPU) - 'otak' mikropengawal yang menjalankan program anda

💾 Memori (RAM dan memori program) - tempat program, data dan pembolehubah anda disimpan

🔌 Sambungan input/output (I/O) yang boleh diprogramkan - untuk berkomunikasi dengan peranti luaran (peranti yang disambungkan) seperti sensor dan aktuator

Mikropengawal biasanya adalah peranti pengkomputeran kos rendah, dengan harga purata untuk yang digunakan dalam perkakasan khusus menurun kepada sekitar AS$0.50, dan beberapa peranti serendah AS$0.03. Kit pembangun boleh bermula serendah AS$4, dengan kos meningkat apabila anda menambah lebih banyak ciri. [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html), sebuah kit pembangun mikropengawal dari [Seeed studios](https://www.seeedstudio.com) yang mempunyai sensor, aktuator, WiFi dan skrin berharga sekitar AS$30.

![Wio Terminal](../../../../../translated_images/ms/wio-terminal.b8299ee16587db9a.webp)

> 💁 Apabila mencari mikropengawal di Internet, berhati-hati mencari istilah **MCU** kerana ini akan membawa banyak hasil untuk Marvel Cinematic Universe, bukan mikropengawal.

Mikropengawal direka untuk diprogramkan untuk melakukan sejumlah kecil tugas yang sangat spesifik, bukannya menjadi komputer serba guna seperti PC atau Mac. Kecuali untuk senario yang sangat spesifik, anda tidak boleh menyambungkan monitor, papan kekunci dan tetikus dan menggunakannya untuk tugas serba guna.

Kit pembangun mikropengawal biasanya dilengkapi dengan sensor dan aktuator tambahan di atas papan. Kebanyakan papan akan mempunyai satu atau lebih LED yang boleh anda programkan, bersama dengan peranti lain seperti palam standard untuk menambah lebih banyak sensor atau aktuator menggunakan ekosistem pelbagai pengeluar atau sensor terbina dalam (biasanya yang paling popular seperti sensor suhu). Sesetengah mikropengawal mempunyai sambungan tanpa wayar terbina dalam seperti Bluetooth atau WiFi atau mempunyai mikropengawal tambahan di atas papan untuk menambah sambungan ini.

> 💁 Mikropengawal biasanya diprogramkan dalam C/C++.

### Komputer papan tunggal

Komputer papan tunggal adalah peranti pengkomputeran kecil yang mempunyai semua elemen komputer lengkap yang terkandung pada satu papan kecil. Ini adalah peranti yang mempunyai spesifikasi hampir dengan PC atau Mac desktop atau komputer riba, menjalankan sistem pengendalian penuh, tetapi kecil, menggunakan kuasa yang lebih rendah, dan jauh lebih murah.

![Raspberry Pi 4](../../../../../translated_images/ms/raspberry-pi-4.fd4590d308c3d456.webp)

Raspberry Pi adalah salah satu komputer papan tunggal yang paling popular.

Seperti mikropengawal, komputer papan tunggal mempunyai CPU, memori dan pin input/output, tetapi ia mempunyai ciri tambahan seperti cip grafik untuk membolehkan anda menyambungkan monitor, output audio, dan port USB untuk menyambungkan papan kekunci, tetikus dan peranti USB standard lain seperti kamera web atau storan luaran. Program disimpan pada kad SD atau cakera keras bersama sistem pengendalian, bukannya cip memori yang dibina ke dalam papan.

> 🎓 Anda boleh menganggap komputer papan tunggal sebagai versi lebih kecil dan lebih murah daripada PC atau Mac yang anda gunakan sekarang, dengan tambahan pin GPIO (input/output serba guna) untuk berinteraksi dengan sensor dan aktuator.

Komputer papan tunggal adalah komputer yang lengkap, jadi boleh diprogramkan dalam mana-mana bahasa. Peranti IoT biasanya diprogramkan dalam Python.

### Pilihan perkakasan untuk pelajaran seterusnya

Semua pelajaran seterusnya termasuk tugasan menggunakan peranti IoT untuk berinteraksi dengan dunia fizikal dan berkomunikasi dengan awan. Setiap pelajaran menyokong 3 pilihan peranti - Arduino (menggunakan Seeed Studios Wio Terminal), atau komputer papan tunggal, sama ada peranti fizikal (Raspberry Pi 4) atau komputer papan tunggal maya yang dijalankan pada PC atau Mac anda.

Anda boleh membaca tentang perkakasan yang diperlukan untuk melengkapkan semua tugasan dalam [panduan perkakasan](../../../hardware.md).

> 💁 Anda tidak perlu membeli sebarang perkakasan IoT untuk melengkapkan tugasan, anda boleh melakukan semuanya menggunakan komputer papan tunggal maya.

Pilihan perkakasan yang anda pilih bergantung kepada apa yang anda ada di rumah atau di sekolah, dan bahasa pengaturcaraan yang anda tahu atau ingin pelajari. Kedua-dua varian perkakasan akan menggunakan ekosistem sensor yang sama, jadi jika anda memulakan satu laluan, anda boleh beralih ke laluan lain tanpa perlu menggantikan kebanyakan kit. Komputer papan tunggal maya akan menjadi setara dengan belajar menggunakan Raspberry Pi, dengan kebanyakan kod boleh dipindahkan ke Pi jika anda akhirnya mendapatkan peranti dan sensor.

### Kit pembangun Arduino

Jika anda berminat untuk mempelajari pembangunan mikropengawal, anda boleh melengkapkan tugasan menggunakan peranti Arduino. Anda memerlukan pemahaman asas tentang pengaturcaraan C/C++, kerana pelajaran hanya akan mengajar kod yang berkaitan dengan kerangka Arduino, sensor dan aktuator yang digunakan, serta perpustakaan yang berinteraksi dengan awan.

Tugasan akan menggunakan [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn) dengan [sambungan PlatformIO untuk pembangunan mikropengawal](https://platformio.org). Anda juga boleh menggunakan Arduino IDE jika anda berpengalaman dengan alat ini, kerana arahan tidak akan disediakan.

### Kit pembangun komputer papan tunggal

Jika anda berminat untuk mempelajari pembangunan IoT menggunakan komputer papan tunggal, anda boleh melengkapkan tugasan menggunakan Raspberry Pi, atau peranti maya yang dijalankan pada PC atau Mac anda.

Anda memerlukan pemahaman asas tentang pengaturcaraan Python, kerana pelajaran hanya akan mengajar kod yang berkaitan dengan sensor dan aktuator yang digunakan, serta perpustakaan yang berinteraksi dengan awan.

> 💁 Jika anda ingin belajar mengatur kod dalam Python, lihat dua siri video berikut:
>
> * [Python untuk pemula](https://channel9.msdn.com/Series/Intro-to-Python-Development?WT.mc_id=academic-17441-jabenn)
> * [Lebih banyak Python untuk pemula](https://channel9.msdn.com/Series/More-Python-for-Beginners?WT.mc_id=academic-7372-jabenn)

Tugasan akan menggunakan [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn).

Jika anda menggunakan Raspberry Pi, anda boleh menjalankan Pi anda menggunakan versi desktop penuh Raspberry Pi OS, dan melakukan semua pengaturcaraan terus pada Pi menggunakan [versi Raspberry Pi OS VS Code](https://code.visualstudio.com/docs/setup/raspberry-pi?WT.mc_id=academic-17441-jabenn), atau menjalankan Pi anda sebagai peranti tanpa kepala dan mengatur kod dari PC atau Mac anda menggunakan VS Code dengan [sambungan Remote SSH](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) yang membolehkan anda menyambung ke Pi anda dan mengedit, menyahpepijat dan menjalankan kod seolah-olah anda mengatur kod terus pada Pi.

Jika anda menggunakan pilihan peranti maya, anda akan mengatur kod terus pada komputer anda. Sebagai ganti mengakses sensor dan aktuator, anda akan menggunakan alat untuk mensimulasikan perkakasan ini dengan menyediakan nilai sensor yang anda boleh tentukan, dan menunjukkan hasil aktuator pada skrin.

## Sediakan peranti anda

Sebelum anda boleh memulakan pengaturcaraan peranti IoT anda, anda perlu melakukan sedikit persediaan. Ikuti arahan yang berkaitan di bawah bergantung pada peranti yang akan anda gunakan.
💁 Jika anda belum mempunyai peranti, rujuk [panduan perkakasan](../../../hardware.md) untuk membantu menentukan peranti yang akan anda gunakan, dan perkakasan tambahan yang perlu anda beli. Anda tidak perlu membeli perkakasan, kerana semua projek boleh dijalankan pada perkakasan maya.
Arahan ini termasuk pautan ke laman web pihak ketiga daripada pencipta perkakasan atau alat yang akan anda gunakan. Ini bertujuan untuk memastikan anda sentiasa menggunakan arahan terkini untuk pelbagai alat dan perkakasan.

Ikuti panduan yang berkaitan untuk menyediakan peranti anda dan selesaikan projek 'Hello World'. Ini akan menjadi langkah pertama dalam mencipta lampu malam IoT sepanjang 4 pelajaran dalam bahagian pengenalan ini.

* [Arduino - Wio Terminal](wio-terminal.md)
* [Komputer papan tunggal - Raspberry Pi](pi.md)
* [Komputer papan tunggal - Peranti maya](virtual-device.md)

✅ Anda akan menggunakan VS Code untuk kedua-dua Arduino dan komputer papan tunggal. Jika anda belum pernah menggunakannya sebelum ini, baca lebih lanjut di [laman VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn)

## Aplikasi IoT

IoT meliputi pelbagai kegunaan, merangkumi beberapa kumpulan utama:

* IoT Pengguna
* IoT Komersial
* IoT Industri
* IoT Infrastruktur

✅ Lakukan sedikit penyelidikan: Untuk setiap kawasan yang diterangkan di bawah, cari satu contoh konkrit yang tidak diberikan dalam teks.

### IoT Pengguna

IoT Pengguna merujuk kepada peranti IoT yang dibeli dan digunakan oleh pengguna di rumah. Beberapa peranti ini sangat berguna, seperti pembesar suara pintar, sistem pemanasan pintar dan pembersih vakum robotik. Yang lain pula dipersoalkan kegunaannya, seperti paip yang dikawal suara yang menyebabkan anda tidak dapat mematikannya kerana kawalan suara tidak dapat mendengar anda di atas bunyi air yang mengalir.

Peranti IoT Pengguna memberi kuasa kepada orang ramai untuk mencapai lebih banyak dalam persekitaran mereka, terutamanya 1 bilion orang yang mempunyai kecacatan. Pembersih vakum robotik boleh menyediakan lantai yang bersih kepada mereka yang mempunyai masalah mobiliti yang tidak dapat membersihkan sendiri, ketuhar yang dikawal suara membolehkan mereka yang mempunyai penglihatan atau kawalan motor yang terhad untuk memanaskan ketuhar mereka hanya dengan suara, monitor kesihatan membolehkan pesakit memantau keadaan kronik mereka sendiri dengan kemas kini yang lebih kerap dan lebih terperinci tentang keadaan mereka. Peranti ini menjadi sangat meluas sehingga kanak-kanak kecil juga menggunakannya sebagai sebahagian daripada kehidupan harian mereka, contohnya, pelajar yang menjalani pembelajaran maya semasa pandemik COVID menetapkan pemasa pada peranti rumah pintar untuk menjejaki kerja sekolah mereka atau penggera untuk mengingatkan mereka tentang mesyuarat kelas yang akan datang.

✅ Apakah peranti IoT Pengguna yang anda miliki di rumah atau pada diri anda?

### IoT Komersial

IoT Komersial meliputi penggunaan IoT di tempat kerja. Dalam persekitaran pejabat, mungkin terdapat sensor penghunian dan pengesan gerakan untuk menguruskan pencahayaan dan pemanasan supaya lampu dan pemanasan hanya dihidupkan apabila diperlukan, mengurangkan kos dan pelepasan karbon. Di kilang, peranti IoT boleh memantau bahaya keselamatan seperti pekerja yang tidak memakai topi keledar atau bunyi yang telah mencapai tahap berbahaya. Dalam peruncitan, peranti IoT boleh mengukur suhu penyimpanan sejuk, memberi amaran kepada pemilik kedai jika peti sejuk atau pembeku berada di luar julat suhu yang diperlukan, atau mereka boleh memantau item di rak untuk mengarahkan pekerja mengisi semula produk yang telah dijual. Industri pengangkutan semakin bergantung pada IoT untuk memantau lokasi kenderaan, menjejaki jarak perjalanan di jalan raya untuk caj pengguna jalan raya, menjejaki jam pemandu dan pematuhan rehat, atau memberitahu kakitangan apabila kenderaan menghampiri depot untuk persediaan memuat atau memunggah.

✅ Apakah peranti IoT Komersial yang anda miliki di sekolah atau tempat kerja anda?

### IoT Industri (IIoT)

IoT Industri, atau IIoT, adalah penggunaan peranti IoT untuk mengawal dan menguruskan mesin pada skala besar. Ini meliputi pelbagai kegunaan, dari kilang hingga pertanian digital.

Kilang menggunakan peranti IoT dalam pelbagai cara. Mesin boleh dipantau dengan pelbagai sensor untuk menjejaki perkara seperti suhu, getaran dan kelajuan putaran. Data ini kemudian boleh dipantau untuk membolehkan mesin dihentikan jika ia berada di luar toleransi tertentu - contohnya, ia terlalu panas dan dimatikan. Data ini juga boleh dikumpulkan dan dianalisis dari masa ke masa untuk penyelenggaraan ramalan, di mana model AI akan melihat data sebelum kegagalan, dan menggunakannya untuk meramalkan kegagalan lain sebelum ia berlaku.

Pertanian digital adalah penting jika planet ini ingin memberi makan kepada populasi yang semakin meningkat, terutamanya untuk 2 bilion orang dalam 500 juta isi rumah yang bergantung kepada [pertanian sara diri](https://wikipedia.org/wiki/Subsistence_agriculture). Pertanian digital boleh berkisar daripada sensor bernilai beberapa dolar kepada sistem komersial yang besar. Seorang petani boleh bermula dengan memantau suhu dan menggunakan [hari darjah pertumbuhan](https://wikipedia.org/wiki/Growing_degree-day) untuk meramalkan bila tanaman akan siap dituai. Mereka boleh menyambungkan pemantauan kelembapan tanah kepada sistem penyiraman automatik untuk memberikan tanaman mereka sebanyak air yang diperlukan, tetapi tidak lebih untuk memastikan tanaman mereka tidak kering tanpa membazirkan air. Petani bahkan membawa ini lebih jauh dengan menggunakan dron, data satelit dan AI untuk memantau pertumbuhan tanaman, penyakit dan kualiti tanah di kawasan ladang yang luas.

✅ Apakah peranti IoT lain yang boleh membantu petani?

### IoT Infrastruktur

IoT Infrastruktur adalah pemantauan dan kawalan infrastruktur tempatan dan global yang digunakan oleh orang ramai setiap hari.

[Bandar Pintar](https://wikipedia.org/wiki/Smart_city) adalah kawasan bandar yang menggunakan peranti IoT untuk mengumpul data tentang bandar dan menggunakannya untuk memperbaiki cara bandar itu berfungsi. Bandar-bandar ini biasanya dijalankan dengan kerjasama antara kerajaan tempatan, akademia dan perniagaan tempatan, menjejaki dan menguruskan perkara yang berbeza seperti pengangkutan, tempat letak kereta dan pencemaran. Sebagai contoh, di Copenhagen, Denmark, pencemaran udara adalah penting kepada penduduk tempatan, jadi ia diukur dan data digunakan untuk memberikan maklumat tentang laluan berbasikal dan berjoging yang paling bersih.

[Grid kuasa pintar](https://wikipedia.org/wiki/Smart_grid) membolehkan analitik yang lebih baik tentang permintaan kuasa dengan mengumpul data penggunaan di peringkat rumah individu. Data ini boleh membimbing keputusan di peringkat negara termasuk di mana untuk membina stesen janakuasa baru, dan di peringkat peribadi dengan memberikan pengguna pandangan tentang berapa banyak kuasa yang mereka gunakan, bila mereka menggunakannya, dan juga cadangan tentang cara mengurangkan kos, seperti mengecas kereta elektrik pada waktu malam.

✅ Jika anda boleh menambah peranti IoT untuk mengukur apa-apa di tempat anda tinggal, apakah yang akan anda ukur?

## Contoh peranti IoT yang mungkin ada di sekitar anda

Anda akan terkejut dengan betapa banyak peranti IoT yang anda miliki di sekitar anda. Saya menulis ini dari rumah dan saya mempunyai peranti berikut yang disambungkan ke Internet dengan ciri pintar seperti kawalan aplikasi, kawalan suara, atau keupayaan untuk menghantar data kepada saya melalui telefon:

* Pelbagai pembesar suara pintar
* Peti sejuk, mesin basuh pinggan mangkuk, ketuhar dan ketuhar gelombang mikro
* Pemantau elektrik untuk panel solar
* Palam pintar
* Loceng pintu video dan kamera keselamatan
* Termostat pintar dengan pelbagai sensor bilik pintar
* Pembuka pintu garaj
* Sistem hiburan rumah dan TV yang dikawal suara
* Lampu
* Penjejak kecergasan dan kesihatan

Semua jenis peranti ini mempunyai sensor dan/atau aktuator dan bercakap dengan Internet. Saya boleh mengetahui dari telefon saya jika pintu garaj saya terbuka, dan meminta pembesar suara pintar saya untuk menutupnya untuk saya. Saya juga boleh menetapkannya pada pemasa supaya jika ia masih terbuka pada waktu malam, ia akan ditutup secara automatik. Apabila loceng pintu saya berbunyi, saya boleh melihat dari telefon saya siapa yang berada di sana di mana sahaja saya berada di dunia, dan bercakap dengan mereka melalui pembesar suara dan mikrofon yang dibina dalam loceng pintu. Saya boleh memantau glukosa darah, kadar jantung dan corak tidur saya, mencari corak dalam data untuk meningkatkan kesihatan saya. Saya boleh mengawal lampu saya melalui awan, dan duduk dalam gelap apabila sambungan Internet saya terputus.

---

## 🚀 Cabaran

Senaraikan sebanyak mungkin peranti IoT yang anda boleh yang terdapat di rumah, sekolah atau tempat kerja anda - mungkin lebih banyak daripada yang anda fikirkan!

## Kuiz selepas kuliah

[Kuiz selepas kuliah](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/2)

## Ulasan & Kajian Kendiri

Baca tentang manfaat dan kegagalan projek IoT pengguna. Semak laman berita untuk artikel tentang apabila ia gagal, seperti isu privasi, masalah perkakasan atau masalah yang disebabkan oleh kekurangan sambungan.

Beberapa contoh:

* Lihat akaun Twitter **[Internet of Sh*t](https://twitter.com/internetofshit)** *(amaran bahasa kasar)* untuk beberapa contoh kegagalan dengan IoT pengguna.
* [c|net - Jam Tangan Apple saya menyelamatkan nyawa saya: 5 orang berkongsi kisah mereka](https://www.cnet.com/news/apple-watch-lifesaving-health-features-read-5-peoples-stories/)
* [c|net - Juruteknik ADT mengaku bersalah mengintip suapan kamera pelanggan selama bertahun-tahun](https://www.cnet.com/news/adt-home-security-technician-pleads-guilty-to-spying-on-customer-camera-feeds-for-years/) *(amaran pencetus - voyeurisme tanpa persetujuan)*

## Tugasan

[Selidik projek IoT](assignment.md)

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.