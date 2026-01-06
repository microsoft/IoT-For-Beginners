<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6d6aa1be033625d201a190fc9c5cbfb4",
  "translation_date": "2025-08-27T23:20:20+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/README.md",
  "language_code": "id"
}
-->
# Mengenali Ucapan dengan Perangkat IoT

![Gambaran sketchnote dari pelajaran ini](../../../../../translated_images/lesson-21.e34de51354d6606fb5ee08d8c89d0222eea0a2a7aaf744a8805ae847c4f69dc4.id.jpg)

> Sketchnote oleh [Nitya Narasimhan](https://github.com/nitya). Klik gambar untuk versi yang lebih besar.

Video ini memberikan gambaran tentang layanan ucapan Azure, topik yang akan dibahas dalam pelajaran ini:

[![Cara memulai menggunakan sumber daya Cognitive Services Speech dari saluran YouTube Microsoft Azure](https://img.youtube.com/vi/iW0Fw0l3mrA/0.jpg)](https://www.youtube.com/watch?v=iW0Fw0l3mrA)

> 🎥 Klik gambar di atas untuk menonton video

## Kuis Sebelum Pelajaran

[Kuis Sebelum Pelajaran](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/41)

## Pendahuluan

'Alexa, atur timer 12 menit'

'Alexa, status timer'

'Alexa, atur timer 8 menit bernama kukus brokoli'

Perangkat pintar semakin banyak digunakan. Tidak hanya sebagai speaker pintar seperti HomePods, Echos, dan Google Homes, tetapi juga tertanam di ponsel, jam tangan, bahkan lampu dan termostat.

> 💁 Saya memiliki setidaknya 19 perangkat di rumah saya yang memiliki asisten suara, dan itu hanya yang saya ketahui!

Kontrol suara meningkatkan aksesibilitas dengan memungkinkan orang dengan keterbatasan gerak untuk berinteraksi dengan perangkat. Baik itu disabilitas permanen seperti lahir tanpa lengan, disabilitas sementara seperti lengan patah, atau tangan penuh dengan belanjaan atau anak kecil, kemampuan untuk mengontrol rumah kita dengan suara alih-alih tangan membuka dunia akses baru. Berteriak 'Hey Siri, tutup pintu garasi saya' sambil mengurus bayi dan balita yang sulit diatur bisa menjadi perbaikan kecil namun efektif dalam hidup.

Salah satu penggunaan asisten suara yang paling populer adalah mengatur timer, terutama timer dapur. Kemampuan untuk mengatur beberapa timer hanya dengan suara Anda sangat membantu di dapur - tidak perlu berhenti menguleni adonan, mengaduk sup, atau membersihkan tangan dari isian pangsit untuk menggunakan timer fisik.

Dalam pelajaran ini, Anda akan belajar tentang membangun pengenalan suara ke dalam perangkat IoT. Anda akan belajar tentang mikrofon sebagai sensor, cara menangkap audio dari mikrofon yang terhubung ke perangkat IoT, dan cara menggunakan AI untuk mengubah apa yang didengar menjadi teks. Sepanjang proyek ini, Anda akan membangun timer dapur pintar, yang dapat mengatur timer menggunakan suara Anda dalam berbagai bahasa.

Dalam pelajaran ini kita akan membahas:

* [Mikrofon](../../../../../6-consumer/lessons/1-speech-recognition)
* [Menangkap audio dari perangkat IoT Anda](../../../../../6-consumer/lessons/1-speech-recognition)
* [Ucapan ke teks](../../../../../6-consumer/lessons/1-speech-recognition)
* [Mengonversi ucapan ke teks](../../../../../6-consumer/lessons/1-speech-recognition)

## Mikrofon

Mikrofon adalah sensor analog yang mengubah gelombang suara menjadi sinyal listrik. Getaran di udara menyebabkan komponen dalam mikrofon bergerak dalam jumlah kecil, dan ini menyebabkan perubahan kecil pada sinyal listrik. Perubahan ini kemudian diperkuat untuk menghasilkan keluaran listrik.

### Jenis Mikrofon

Mikrofon tersedia dalam berbagai jenis:

* Dinamis - Mikrofon dinamis memiliki magnet yang terpasang pada diafragma yang bergerak dalam kumparan kawat, menciptakan arus listrik. Ini adalah kebalikan dari sebagian besar speaker, yang menggunakan arus listrik untuk menggerakkan magnet dalam kumparan kawat, menggerakkan diafragma untuk menciptakan suara. Ini berarti speaker dapat digunakan sebagai mikrofon dinamis, dan mikrofon dinamis dapat digunakan sebagai speaker. Dalam perangkat seperti interkom, di mana pengguna hanya mendengarkan atau berbicara, tetapi tidak keduanya, satu perangkat dapat berfungsi sebagai speaker dan mikrofon.

    Mikrofon dinamis tidak memerlukan daya untuk bekerja, sinyal listrik sepenuhnya dihasilkan dari mikrofon.

    ![Patti Smith bernyanyi ke mikrofon Shure SM58 (jenis cardioid dinamis)](../../../../../translated_images/dynamic-mic.8babac890a2d80dfb0874b5bf37d4b851fe2aeb9da6fd72945746176978bf3bb.id.jpg)

* Pita - Mikrofon pita mirip dengan mikrofon dinamis, kecuali mereka memiliki pita logam alih-alih diafragma. Pita ini bergerak dalam medan magnet, menghasilkan arus listrik. Seperti mikrofon dinamis, mikrofon pita tidak memerlukan daya untuk bekerja.

    ![Edmund Lowe, aktor Amerika, berdiri di mikrofon radio (berlabel untuk (NBC) Blue Network), memegang naskah, 1942](../../../../../translated_images/ribbon-mic.eacc8e092c7441ca.id.jpg)

* Kondensor - Mikrofon kondensor memiliki diafragma logam tipis dan pelat belakang logam tetap. Listrik diterapkan pada keduanya, dan saat diafragma bergetar, muatan statis antara pelat berubah, menghasilkan sinyal. Mikrofon kondensor memerlukan daya untuk bekerja - disebut *Phantom power*.

    ![Mikrofon kondensor diafragma kecil C451B oleh AKG Acoustics](../../../../../translated_images/condenser-mic.6f6ed5b76ca19e0ec3fd0c544601542d4479a6cb7565db336de49fbbf69f623e.id.jpg)

* MEMS - Mikrofon sistem mikroelektromekanis, atau MEMS, adalah mikrofon pada chip. Mereka memiliki diafragma sensitif tekanan yang diukir pada chip silikon, dan bekerja mirip dengan mikrofon kondensor. Mikrofon ini bisa sangat kecil dan terintegrasi ke dalam sirkuit.

    ![Mikrofon MEMS pada papan sirkuit](../../../../../translated_images/mems-microphone.80574019e1f5e4d9ee72fed720ecd25a39fc2969c91355d17ebb24ba4159e4c4.id.png)

    Pada gambar di atas, chip berlabel **LEFT** adalah mikrofon MEMS, dengan diafragma kecil kurang dari satu milimeter lebar.

✅ Lakukan penelitian: Mikrofon apa yang Anda miliki di sekitar Anda - baik di komputer, ponsel, headset, atau perangkat lainnya. Jenis mikrofon apa yang mereka gunakan?

### Audio Digital

Audio adalah sinyal analog yang membawa informasi sangat rinci. Untuk mengonversi sinyal ini ke digital, audio perlu diambil sampelnya ribuan kali per detik.

> 🎓 Sampling adalah mengonversi sinyal audio menjadi nilai digital yang mewakili sinyal pada titik waktu tertentu.

![Grafik garis yang menunjukkan sinyal, dengan titik-titik diskrit pada interval tetap](../../../../../translated_images/sampling.6f4fadb3f2d9dfe7.id.png)

Audio digital diambil sampelnya menggunakan Pulse Code Modulation, atau PCM. PCM melibatkan pembacaan tegangan sinyal, dan memilih nilai diskrit terdekat dengan tegangan tersebut menggunakan ukuran yang telah ditentukan.

> 💁 Anda dapat menganggap PCM sebagai versi sensor dari modulasi lebar pulsa, atau PWM (PWM dibahas kembali di [pelajaran 3 dari proyek memulai](../../../1-getting-started/lessons/3-sensors-and-actuators/README.md#pulse-width-modulation)). PCM melibatkan konversi sinyal analog ke digital, PWM melibatkan konversi sinyal digital ke analog.

Sebagai contoh, sebagian besar layanan musik streaming menawarkan audio 16-bit atau 24-bit. Ini berarti mereka mengonversi tegangan menjadi nilai yang sesuai dengan bilangan bulat 16-bit, atau bilangan bulat 24-bit. Audio 16-bit sesuai dengan nilai dalam rentang -32.768 hingga 32.767, sedangkan 24-bit dalam rentang −8.388.608 hingga 8.388.607. Semakin banyak bit, semakin dekat sampel dengan apa yang sebenarnya didengar telinga kita.

> 💁 Anda mungkin pernah mendengar tentang audio 8-bit, sering disebut sebagai LoFi. Ini adalah audio yang diambil sampelnya hanya dengan 8-bit, jadi -128 hingga 127. Audio komputer pertama kali dibatasi pada 8 bit karena keterbatasan perangkat keras, sehingga ini sering terlihat dalam permainan retro.

Sampel ini diambil ribuan kali per detik, menggunakan tingkat sampel yang terdefinisi dengan baik yang diukur dalam KHz (ribuan pembacaan per detik). Layanan musik streaming menggunakan 48KHz untuk sebagian besar audio, tetapi beberapa audio 'lossless' menggunakan hingga 96KHz atau bahkan 192KHz. Semakin tinggi tingkat sampel, semakin dekat dengan aslinya audio tersebut, hingga batas tertentu. Ada perdebatan apakah manusia dapat membedakan di atas 48KHz.

✅ Lakukan penelitian: Jika Anda menggunakan layanan musik streaming, tingkat sampel dan ukuran apa yang digunakan? Jika Anda menggunakan CD, berapa tingkat sampel dan ukuran audio CD?

Ada sejumlah format berbeda untuk data audio. Anda mungkin pernah mendengar tentang file mp3 - data audio yang dikompresi untuk membuatnya lebih kecil tanpa kehilangan kualitas. Audio yang tidak dikompresi sering disimpan sebagai file WAV - ini adalah file dengan 44 byte informasi header, diikuti oleh data audio mentah. Header berisi informasi seperti tingkat sampel (misalnya 16000 untuk 16KHz) dan ukuran sampel (16 untuk 16-bit), serta jumlah saluran. Setelah header, file WAV berisi data audio mentah.

> 🎓 Saluran mengacu pada berapa banyak aliran audio berbeda yang membentuk audio. Misalnya, untuk audio stereo dengan kiri dan kanan, akan ada 2 saluran. Untuk suara surround 7.1 untuk sistem home theater, ini akan menjadi 8.

### Ukuran Data Audio

Data audio relatif besar. Sebagai contoh, menangkap audio 16-bit yang tidak dikompresi pada 16KHz (tingkat yang cukup baik untuk digunakan dengan model ucapan ke teks), membutuhkan 32KB data untuk setiap detik audio:

* 16-bit berarti 2 byte per sampel (1 byte adalah 8 bit).
* 16KHz adalah 16.000 sampel per detik.
* 16.000 x 2 byte = 32.000 byte per detik.

Ini terdengar seperti jumlah data yang kecil, tetapi jika Anda menggunakan mikrokontroler dengan memori terbatas, ini bisa menjadi banyak. Sebagai contoh, Wio Terminal memiliki memori 192KB, dan itu perlu menyimpan kode program dan variabel. Bahkan jika kode program Anda sangat kecil, Anda tidak dapat menangkap lebih dari 5 detik audio.

Mikrokontroler dapat mengakses penyimpanan tambahan, seperti kartu SD atau memori flash. Saat membangun perangkat IoT yang menangkap audio, Anda perlu memastikan tidak hanya Anda memiliki penyimpanan tambahan, tetapi kode Anda menulis audio yang ditangkap dari mikrofon langsung ke penyimpanan tersebut, dan saat mengirimkannya ke cloud, Anda mengalirkan dari penyimpanan ke permintaan web. Dengan cara ini, Anda dapat menghindari kehabisan memori dengan mencoba menahan seluruh blok data audio di memori sekaligus.

## Menangkap Audio dari Perangkat IoT Anda

Perangkat IoT Anda dapat dihubungkan ke mikrofon untuk menangkap audio, siap untuk dikonversi menjadi teks. Perangkat ini juga dapat dihubungkan ke speaker untuk output audio. Dalam pelajaran selanjutnya, ini akan digunakan untuk memberikan umpan balik audio, tetapi berguna untuk mengatur speaker sekarang untuk menguji mikrofon.

### Tugas - Konfigurasikan Mikrofon dan Speaker Anda

Ikuti panduan yang relevan untuk mengonfigurasi mikrofon dan speaker untuk perangkat IoT Anda:

* [Arduino - Wio Terminal](wio-terminal-microphone.md)
* [Komputer papan tunggal - Raspberry Pi](pi-microphone.md)
* [Komputer papan tunggal - Perangkat virtual](virtual-device-microphone.md)

### Tugas - Menangkap Audio

Ikuti panduan yang relevan untuk menangkap audio pada perangkat IoT Anda:

* [Arduino - Wio Terminal](wio-terminal-audio.md)
* [Komputer papan tunggal - Raspberry Pi](pi-audio.md)
* [Komputer papan tunggal - Perangkat virtual](virtual-device-audio.md)

## Ucapan ke Teks

Ucapan ke teks, atau pengenalan ucapan, melibatkan penggunaan AI untuk mengonversi kata-kata dalam sinyal audio menjadi teks.

### Model Pengenalan Ucapan

Untuk mengonversi ucapan menjadi teks, sampel dari sinyal audio dikelompokkan bersama dan dimasukkan ke dalam model pembelajaran mesin berbasis Recurrent Neural Network (RNN). Ini adalah jenis model pembelajaran mesin yang dapat menggunakan data sebelumnya untuk membuat keputusan tentang data yang masuk. Misalnya, RNN dapat mendeteksi satu blok sampel audio sebagai suara 'Hel', dan ketika menerima blok lain yang dianggap sebagai suara 'lo', ia dapat menggabungkan ini dengan suara sebelumnya, menemukan bahwa 'Hello' adalah kata yang valid, dan memilihnya sebagai hasil.

Model ML selalu menerima data dengan ukuran yang sama setiap kali. Pengklasifikasi gambar yang Anda buat dalam pelajaran sebelumnya mengubah ukuran gambar menjadi ukuran tetap dan memprosesnya. Hal yang sama berlaku untuk model ucapan, mereka harus memproses potongan audio dengan ukuran tetap. Model ucapan perlu dapat menggabungkan keluaran dari beberapa prediksi untuk mendapatkan jawaban, memungkinkan mereka membedakan antara 'Hi' dan 'Highway', atau 'flock' dan 'floccinaucinihilipilification'.

Model ucapan juga cukup canggih untuk memahami konteks, dan dapat memperbaiki kata-kata yang mereka deteksi saat lebih banyak suara diproses. Misalnya, jika Anda mengatakan "Saya pergi ke toko untuk membeli dua pisang dan sebuah apel juga", Anda akan menggunakan tiga kata yang terdengar sama, tetapi dieja berbeda - to, two, dan too. Model ucapan mampu memahami konteks dan menggunakan ejaan kata yang sesuai.
💁 Beberapa layanan suara memungkinkan penyesuaian agar dapat bekerja lebih baik di lingkungan yang bising seperti pabrik, atau dengan kata-kata khusus industri seperti nama-nama bahan kimia. Penyesuaian ini dilatih dengan menyediakan sampel audio dan transkripsi, dan bekerja menggunakan transfer learning, sama seperti cara Anda melatih pengklasifikasi gambar hanya dengan beberapa gambar di pelajaran sebelumnya.
### Privasi

Saat menggunakan fitur pengenalan suara pada perangkat IoT konsumen, privasi menjadi sangat penting. Perangkat ini mendengarkan audio secara terus-menerus, sehingga sebagai konsumen, Anda tidak ingin semua yang Anda ucapkan dikirim ke cloud dan diubah menjadi teks. Selain akan menggunakan banyak bandwidth internet, hal ini juga memiliki dampak besar terhadap privasi, terutama ketika beberapa pembuat perangkat pintar secara acak memilih audio untuk [divalidasi oleh manusia terhadap teks yang dihasilkan guna meningkatkan model mereka](https://www.theverge.com/2019/4/10/18305378/amazon-alexa-ai-voice-assistant-annotation-listen-private-recordings).

Anda hanya ingin perangkat pintar Anda mengirim audio ke cloud untuk diproses saat Anda menggunakannya, bukan saat perangkat mendengar audio di rumah Anda, yang bisa saja termasuk rapat pribadi atau interaksi intim. Cara kerja sebagian besar perangkat pintar adalah dengan menggunakan *wake word*, yaitu frasa kunci seperti "Alexa", "Hey Siri", atau "OK Google" yang membuat perangkat 'bangun' dan mendengarkan apa yang Anda ucapkan hingga mendeteksi jeda dalam ucapan Anda, yang menunjukkan bahwa Anda telah selesai berbicara dengan perangkat tersebut.

> 🎓 Deteksi wake word juga dikenal sebagai *Keyword spotting* atau *Keyword recognition*.

Wake word ini dideteksi pada perangkat, bukan di cloud. Perangkat pintar ini memiliki model AI kecil yang berjalan di perangkat untuk mendengarkan wake word, dan ketika terdeteksi, mulai mengalirkan audio ke cloud untuk pengenalan. Model ini sangat khusus dan hanya mendengarkan wake word.

> 💁 Beberapa perusahaan teknologi menambahkan lebih banyak privasi ke perangkat mereka dengan melakukan sebagian konversi suara ke teks di perangkat. Apple telah mengumumkan bahwa sebagai bagian dari pembaruan iOS dan macOS 2021 mereka, mereka akan mendukung konversi suara ke teks di perangkat, dan dapat menangani banyak permintaan tanpa perlu menggunakan cloud. Hal ini dimungkinkan berkat prosesor yang kuat di perangkat mereka yang dapat menjalankan model ML.

✅ Menurut Anda, apa dampak privasi dan etika dari menyimpan audio yang dikirim ke cloud? Haruskah audio ini disimpan, dan jika ya, bagaimana caranya? Apakah penggunaan rekaman untuk penegakan hukum merupakan pertukaran yang baik untuk kehilangan privasi?

Deteksi wake word biasanya menggunakan teknik yang dikenal sebagai TinyML, yaitu mengubah model ML agar dapat berjalan pada mikrokontroler. Model ini berukuran kecil dan mengonsumsi daya yang sangat sedikit untuk dijalankan.

Untuk menghindari kompleksitas pelatihan dan penggunaan model wake word, timer pintar yang Anda buat dalam pelajaran ini akan menggunakan tombol untuk mengaktifkan pengenalan suara.

> 💁 Jika Anda ingin mencoba membuat model deteksi wake word untuk dijalankan di Wio Terminal atau Raspberry Pi, lihat [tutorial merespons suara Anda oleh Edge Impulse](https://docs.edgeimpulse.com/docs/responding-to-your-voice). Jika Anda ingin menggunakan komputer Anda untuk melakukan ini, Anda dapat mencoba [panduan memulai cepat Custom Keyword di Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/keyword-recognition-overview?WT.mc_id=academic-17441-jabenn).

## Mengubah suara menjadi teks

![Logo layanan suara](../../../../../translated_images/azure-speech-logo.a1f08c4befb0159f2cb5d692d3baf5b599e7b44759d316da907bda1508f46a4a.id.png)

Sama seperti klasifikasi gambar dalam proyek sebelumnya, ada layanan AI yang sudah dibuat yang dapat mengambil suara sebagai file audio dan mengubahnya menjadi teks. Salah satu layanan tersebut adalah Speech Service, bagian dari Cognitive Services, layanan AI yang sudah dibuat yang dapat Anda gunakan dalam aplikasi Anda.

### Tugas - mengonfigurasi sumber daya AI suara

1. Buat Resource Group untuk proyek ini dengan nama `smart-timer`.

1. Gunakan perintah berikut untuk membuat sumber daya suara gratis:

    ```sh
    az cognitiveservices account create --name smart-timer \
                                        --resource-group smart-timer \
                                        --kind SpeechServices \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Ganti `<location>` dengan lokasi yang Anda gunakan saat membuat Resource Group.

1. Anda akan membutuhkan API key untuk mengakses sumber daya suara dari kode Anda. Jalankan perintah berikut untuk mendapatkan kunci:

    ```sh
    az cognitiveservices account keys list --name smart-timer \
                                           --resource-group smart-timer \
                                           --output table
    ```

    Salin salah satu kunci tersebut.

### Tugas - mengubah suara menjadi teks

Ikuti panduan yang relevan untuk mengubah suara menjadi teks pada perangkat IoT Anda:

* [Arduino - Wio Terminal](wio-terminal-speech-to-text.md)
* [Komputer papan tunggal - Raspberry Pi](pi-speech-to-text.md)
* [Komputer papan tunggal - Perangkat virtual](virtual-device-speech-to-text.md)

---

## 🚀 Tantangan

Pengenalan suara telah ada sejak lama dan terus berkembang. Teliti kemampuan terkini dan bandingkan bagaimana teknologi ini telah berkembang dari waktu ke waktu, termasuk seberapa akurat transkripsi mesin dibandingkan dengan manusia.

Menurut Anda, apa yang akan terjadi di masa depan untuk pengenalan suara?

## Kuis setelah kuliah

[Kuis setelah kuliah](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/42)

## Tinjauan & Studi Mandiri

* Baca tentang berbagai jenis mikrofon dan cara kerjanya di [artikel tentang perbedaan antara mikrofon dinamis dan kondensor di Musician's HQ](https://musicianshq.com/whats-the-difference-between-dynamic-and-condenser-microphones/).
* Baca lebih lanjut tentang layanan suara Cognitive Services di [dokumentasi layanan suara di Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/?WT.mc_id=academic-17441-jabenn).
* Baca tentang keyword spotting di [dokumentasi pengenalan kata kunci di Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/keyword-recognition-overview?WT.mc_id=academic-17441-jabenn).

## Tugas

[](assignment.md)

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.