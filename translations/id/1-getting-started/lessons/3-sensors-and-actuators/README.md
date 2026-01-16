<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e9ee00eb5fc55922a73762acc542166b",
  "translation_date": "2025-08-27T22:26:10+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/README.md",
  "language_code": "id"
}
-->
# Berinteraksi dengan Dunia Fisik Menggunakan Sensor dan Aktuator

![Gambaran sketchnote dari pelajaran ini](../../../../../translated_images/id/lesson-3.cc3b7b4cd646de598698cce043c0393fd62ef42bac2eaf60e61272cd844250f4.jpg)

> Sketchnote oleh [Nitya Narasimhan](https://github.com/nitya). Klik gambar untuk versi yang lebih besar.

Pelajaran ini diajarkan sebagai bagian dari seri [Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) dari [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Materi ini disampaikan dalam 2 video - satu sesi pelajaran selama 1 jam, dan satu sesi tanya jawab selama 1 jam yang membahas lebih dalam bagian-bagian dari pelajaran serta menjawab pertanyaan.

[![Pelajaran 3: Berinteraksi dengan Dunia Fisik Menggunakan Sensor dan Aktuator](https://img.youtube.com/vi/Lqalu1v6aF4/0.jpg)](https://youtu.be/Lqalu1v6aF4)

[![Pelajaran 3: Berinteraksi dengan Dunia Fisik Menggunakan Sensor dan Aktuator - Sesi Tanya Jawab](https://img.youtube.com/vi/qR3ekcMlLWA/0.jpg)](https://youtu.be/qR3ekcMlLWA)

> 🎥 Klik gambar di atas untuk menonton video

## Kuis Sebelum Pelajaran

[Kuis Sebelum Pelajaran](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/5)

## Pendahuluan

Pelajaran ini memperkenalkan dua konsep penting untuk perangkat IoT Anda - sensor dan aktuator. Anda juga akan langsung mempraktikkannya, menambahkan sensor cahaya ke proyek IoT Anda, lalu menambahkan LED yang dikendalikan oleh tingkat cahaya, sehingga secara efektif membangun lampu malam.

Dalam pelajaran ini kita akan membahas:

* [Apa itu sensor?](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Menggunakan sensor](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Jenis-jenis sensor](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Apa itu aktuator?](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Menggunakan aktuator](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Jenis-jenis aktuator](../../../../../1-getting-started/lessons/3-sensors-and-actuators)

## Apa itu sensor?

Sensor adalah perangkat keras yang mendeteksi dunia fisik - yaitu, mereka mengukur satu atau lebih properti di sekitarnya dan mengirimkan informasi tersebut ke perangkat IoT. Sensor mencakup berbagai perangkat karena ada begitu banyak hal yang dapat diukur, mulai dari sifat alami seperti suhu udara hingga interaksi fisik seperti gerakan.

Beberapa sensor umum meliputi:

* Sensor suhu - mendeteksi suhu udara atau suhu benda yang disentuhnya. Untuk hobi dan pengembang, sensor ini sering digabungkan dengan sensor tekanan udara dan kelembapan dalam satu perangkat.
* Tombol - mendeteksi saat tombol ditekan.
* Sensor cahaya - mendeteksi tingkat cahaya dan dapat mendeteksi warna tertentu, cahaya UV, cahaya IR, atau cahaya tampak umum.
* Kamera - mendeteksi representasi visual dunia dengan mengambil foto atau streaming video.
* Akselerometer - mendeteksi gerakan dalam berbagai arah.
* Mikrofon - mendeteksi suara, baik tingkat suara umum maupun suara terarah.

✅ Lakukan penelitian. Sensor apa saja yang dimiliki ponsel Anda?

Semua sensor memiliki satu kesamaan - mereka mengubah apa yang mereka deteksi menjadi sinyal listrik yang dapat diinterpretasikan oleh perangkat IoT. Cara sinyal listrik ini diinterpretasikan tergantung pada sensor, serta protokol komunikasi yang digunakan untuk berkomunikasi dengan perangkat IoT.

## Menggunakan sensor

Ikuti panduan yang relevan di bawah ini untuk menambahkan sensor ke perangkat IoT Anda:

* [Arduino - Wio Terminal](wio-terminal-sensor.md)
* [Komputer papan tunggal - Raspberry Pi](pi-sensor.md)
* [Komputer papan tunggal - Perangkat virtual](virtual-device-sensor.md)

## Jenis-jenis sensor

Sensor dapat berupa analog atau digital.

### Sensor analog

Beberapa sensor paling dasar adalah sensor analog. Sensor ini menerima tegangan dari perangkat IoT, komponen sensor menyesuaikan tegangan ini, dan tegangan yang dikembalikan dari sensor diukur untuk memberikan nilai sensor.

> 🎓 Tegangan adalah ukuran seberapa besar dorongan untuk memindahkan listrik dari satu tempat ke tempat lain, seperti dari terminal positif baterai ke terminal negatif. Misalnya, baterai AA standar adalah 1,5V (V adalah simbol untuk volt) dan dapat mendorong listrik dengan kekuatan 1,5V dari terminal positifnya ke terminal negatifnya. Perangkat keras listrik yang berbeda membutuhkan tegangan yang berbeda untuk bekerja, misalnya, LED dapat menyala dengan tegangan antara 2-3V, tetapi bola lampu filamen 100W membutuhkan 240V. Anda dapat membaca lebih lanjut tentang tegangan di [halaman Tegangan di Wikipedia](https://wikipedia.org/wiki/Voltage).

Salah satu contohnya adalah potensiometer. Ini adalah kenop yang dapat Anda putar di antara dua posisi, dan sensor mengukur rotasi tersebut.

![Potensiometer diatur ke titik tengah, menerima 5 volt, dan mengembalikan 3,8 volt](../../../../../translated_images/id/potentiometer.35a348b9ce22f6ec.webp)

Perangkat IoT akan mengirimkan sinyal listrik ke potensiometer pada tegangan tertentu, misalnya 5 volt (5V). Saat potensiometer disesuaikan, tegangan yang keluar dari sisi lain akan berubah. Bayangkan Anda memiliki potensiometer yang diberi label sebagai kenop yang berkisar dari 0 hingga [11](https://wikipedia.org/wiki/Up_to_eleven), seperti kenop volume pada amplifier. Ketika potensiometer berada di posisi mati penuh (0), maka 0V (0 volt) akan keluar. Ketika berada di posisi nyala penuh (11), 5V (5 volt) akan keluar.

> 🎓 Ini adalah penyederhanaan, dan Anda dapat membaca lebih lanjut tentang potensiometer dan resistor variabel di [halaman Wikipedia potensiometer](https://wikipedia.org/wiki/Potentiometer).

Tegangan yang keluar dari sensor kemudian dibaca oleh perangkat IoT, dan perangkat dapat meresponsnya. Bergantung pada sensor, tegangan ini bisa berupa nilai sembarang atau dapat dipetakan ke satuan standar. Misalnya, sensor suhu analog berbasis [termistor](https://wikipedia.org/wiki/Thermistor) mengubah resistansinya tergantung pada suhu. Tegangan keluaran kemudian dapat dikonversi menjadi suhu dalam Kelvin, dan selanjutnya ke °C atau °F, melalui perhitungan dalam kode.

✅ Menurut Anda, apa yang terjadi jika sensor mengembalikan tegangan yang lebih tinggi daripada yang dikirimkan (misalnya berasal dari sumber daya eksternal)? ⛔️ JANGAN coba ini.

#### Konversi analog ke digital

Perangkat IoT bersifat digital - mereka tidak dapat bekerja dengan nilai analog, hanya dengan 0 dan 1. Ini berarti bahwa nilai sensor analog perlu dikonversi menjadi sinyal digital sebelum dapat diproses. Banyak perangkat IoT memiliki konverter analog-ke-digital (ADC) untuk mengubah input analog menjadi representasi digital dari nilainya. Sensor juga dapat bekerja dengan ADC melalui papan konektor. Misalnya, dalam ekosistem Seeed Grove dengan Raspberry Pi, sensor analog terhubung ke port tertentu pada 'hat' yang dipasang di Pi yang terhubung ke pin GPIO Pi, dan hat ini memiliki ADC untuk mengonversi tegangan menjadi sinyal digital yang dapat dikirim dari pin GPIO Pi.

Bayangkan Anda memiliki sensor cahaya analog yang terhubung ke perangkat IoT yang menggunakan 3,3V dan mengembalikan nilai 1V. Tegangan 1V ini tidak berarti apa-apa di dunia digital, jadi perlu dikonversi. Tegangan akan dikonversi menjadi nilai analog menggunakan skala tergantung pada perangkat dan sensor. Salah satu contohnya adalah sensor cahaya Seeed Grove yang menghasilkan nilai dari 0 hingga 1.023. Untuk sensor ini yang berjalan pada 3,3V, keluaran 1V akan menjadi nilai 300. Perangkat IoT tidak dapat menangani 300 sebagai nilai analog, jadi nilai tersebut akan dikonversi menjadi `0000000100101100`, representasi biner dari 300 oleh Grove hat. Nilai ini kemudian akan diproses oleh perangkat IoT.

✅ Jika Anda tidak tahu tentang biner, lakukan sedikit penelitian untuk mempelajari bagaimana angka direpresentasikan oleh 0 dan 1. [Pelajaran pengantar biner dari BBC Bitesize](https://www.bbc.co.uk/bitesize/guides/zwsbwmn/revision/1) adalah tempat yang bagus untuk memulai.

Dari perspektif pemrograman, semua ini biasanya ditangani oleh pustaka yang disertakan dengan sensor, jadi Anda tidak perlu khawatir tentang konversi ini sendiri. Untuk sensor cahaya Grove, Anda akan menggunakan pustaka Python dan memanggil properti `light`, atau menggunakan pustaka Arduino dan memanggil `analogRead` untuk mendapatkan nilai 300.

### Sensor digital

Sensor digital, seperti sensor analog, mendeteksi dunia di sekitar mereka menggunakan perubahan tegangan listrik. Perbedaannya adalah mereka menghasilkan sinyal digital, baik dengan hanya mengukur dua keadaan atau dengan menggunakan ADC bawaan. Sensor digital semakin umum untuk menghindari kebutuhan menggunakan ADC baik di papan konektor atau di perangkat IoT itu sendiri.

Sensor digital paling sederhana adalah tombol atau saklar. Ini adalah sensor dengan dua keadaan, hidup atau mati.

![Tombol menerima 5 volt. Saat tidak ditekan, mengembalikan 0 volt; saat ditekan, mengembalikan 5 volt](../../../../../translated_images/id/button.eadb560b77ac45e56f523d9d8876e40444f63b419e33eb820082d461fa79490b.png)

Pin pada perangkat IoT seperti pin GPIO dapat mengukur sinyal ini secara langsung sebagai 0 atau 1. Jika tegangan yang dikirim sama dengan tegangan yang dikembalikan, nilai yang dibaca adalah 1, jika tidak nilai yang dibaca adalah 0. Tidak perlu mengonversi sinyal, sinyal hanya bisa berupa 1 atau 0.

> 💁 Tegangan tidak pernah benar-benar tepat terutama karena komponen dalam sensor memiliki resistansi tertentu, jadi biasanya ada toleransi. Misalnya, pin GPIO pada Raspberry Pi bekerja pada 3,3V, dan membaca sinyal balik di atas 1,8V sebagai 1, di bawah 1,8V sebagai 0.

* 3,3V masuk ke tombol. Tombol mati sehingga 0V keluar, memberikan nilai 0
* 3,3V masuk ke tombol. Tombol menyala sehingga 3,3V keluar, memberikan nilai 1

Sensor digital yang lebih canggih membaca nilai analog, lalu mengonversinya menggunakan ADC bawaan menjadi sinyal digital. Misalnya, sensor suhu digital masih menggunakan termokopel dengan cara yang sama seperti sensor analog, dan masih mengukur perubahan tegangan yang disebabkan oleh resistansi termokopel pada suhu saat ini. Alih-alih mengembalikan nilai analog dan mengandalkan perangkat atau papan konektor untuk mengonversi menjadi sinyal digital, ADC yang dibangun ke dalam sensor akan mengonversi nilai tersebut dan mengirimkannya sebagai serangkaian 0 dan 1 ke perangkat IoT. 0 dan 1 ini dikirim dengan cara yang sama seperti sinyal digital untuk tombol dengan 1 sebagai tegangan penuh dan 0 sebagai 0V.

![Sensor suhu digital mengonversi pembacaan analog menjadi data biner dengan 0 sebagai 0 volt dan 1 sebagai 5 volt sebelum mengirimkannya ke perangkat IoT](../../../../../translated_images/id/temperature-as-digital.85004491b977bae1.webp)

Mengirim data digital memungkinkan sensor menjadi lebih kompleks dan mengirimkan data yang lebih rinci, bahkan data terenkripsi untuk sensor yang aman. Salah satu contohnya adalah kamera. Ini adalah sensor yang menangkap gambar dan mengirimkannya sebagai data digital yang berisi gambar tersebut, biasanya dalam format terkompresi seperti JPEG, untuk dibaca oleh perangkat IoT. Kamera bahkan dapat melakukan streaming video dengan menangkap gambar dan mengirimkan gambar lengkap frame demi frame atau aliran video terkompresi.

## Apa itu aktuator?

Aktuator adalah kebalikan dari sensor - mereka mengubah sinyal listrik dari perangkat IoT Anda menjadi interaksi dengan dunia fisik seperti memancarkan cahaya atau suara, atau menggerakkan motor.

Beberapa aktuator umum meliputi:

* LED - memancarkan cahaya saat dinyalakan
* Speaker - memancarkan suara berdasarkan sinyal yang dikirimkan, mulai dari buzzer sederhana hingga speaker audio yang dapat memutar musik
* Motor stepper - mengubah sinyal menjadi jumlah rotasi tertentu, seperti memutar kenop 90°
* Relay - saklar yang dapat dinyalakan atau dimatikan oleh sinyal listrik. Relay memungkinkan tegangan kecil dari perangkat IoT untuk menyalakan tegangan yang lebih besar.
* Layar - aktuator yang lebih kompleks yang menampilkan informasi pada tampilan multi-segmen. Layar bervariasi dari tampilan LED sederhana hingga monitor video resolusi tinggi.

✅ Lakukan penelitian. Aktuator apa saja yang dimiliki ponsel Anda?

## Menggunakan aktuator

Ikuti panduan yang relevan di bawah ini untuk menambahkan aktuator ke perangkat IoT Anda, yang dikendalikan oleh sensor, untuk membangun lampu malam IoT. Lampu ini akan mengumpulkan tingkat cahaya dari sensor cahaya, dan menggunakan aktuator berupa LED untuk memancarkan cahaya saat tingkat cahaya yang terdeteksi terlalu rendah.

![Diagram alur tugas menunjukkan tingkat cahaya yang dibaca dan diperiksa, serta LED yang dikendalikan](../../../../../translated_images/id/assignment-1-flow.7552a51acb1a5ec858dca6e855cdbb44206434006df8ba3799a25afcdab1665d.png)

* [Arduino - Wio Terminal](wio-terminal-actuator.md)
* [Komputer papan tunggal - Raspberry Pi](pi-actuator.md)
* [Komputer papan tunggal - Perangkat virtual](virtual-device-actuator.md)

## Jenis-jenis aktuator

Seperti sensor, aktuator dapat berupa analog atau digital.

### Aktuator analog

Aktuator analog menerima sinyal analog dan mengubahnya menjadi semacam interaksi, di mana interaksi tersebut berubah berdasarkan tegangan yang diberikan.

Salah satu contohnya adalah lampu yang dapat diredupkan, seperti yang mungkin Anda miliki di rumah Anda. Jumlah tegangan yang diberikan ke lampu menentukan seberapa terang lampu tersebut.
![Cahaya redup pada tegangan rendah dan lebih terang pada tegangan tinggi](../../../../../translated_images/id/dimmable-light.9ceffeb195dec1a849da718b2d71b32c35171ff7dfea9c07bbf82646a67acf6b.png)

Seperti halnya sensor, perangkat IoT sebenarnya bekerja dengan sinyal digital, bukan analog. Ini berarti untuk mengirimkan sinyal analog, perangkat IoT memerlukan konverter digital ke analog (DAC), baik langsung pada perangkat IoT atau pada papan konektor. Konverter ini akan mengubah 0 dan 1 dari perangkat IoT menjadi tegangan analog yang dapat digunakan oleh aktuator.

✅ Apa yang menurutmu akan terjadi jika perangkat IoT mengirimkan tegangan lebih tinggi daripada yang dapat ditangani oleh aktuator?
⛔️ JANGAN coba-coba melakukan ini.

#### Modulasi Lebar Pulsa

Pilihan lain untuk mengubah sinyal digital dari perangkat IoT menjadi sinyal analog adalah modulasi lebar pulsa (PWM). Ini melibatkan pengiriman banyak pulsa digital pendek yang bertindak seolah-olah itu adalah sinyal analog.

Sebagai contoh, kamu dapat menggunakan PWM untuk mengontrol kecepatan motor.

Bayangkan kamu mengontrol motor dengan suplai 5V. Kamu mengirimkan pulsa pendek ke motor, mengubah tegangan menjadi tinggi (5V) selama dua per seratus detik (0,02s). Dalam waktu tersebut, motor dapat berputar sepersepuluh putaran, atau 36°. Sinyal kemudian berhenti selama dua per seratus detik (0,02s), mengirimkan sinyal rendah (0V). Setiap siklus nyala lalu mati berlangsung selama 0,04s. Siklus ini kemudian berulang.

![Rotasi motor dengan modulasi lebar pulsa pada 150 RPM](../../../../../translated_images/id/pwm-motor-150rpm.83347ac04ca38482.webp)

Ini berarti dalam satu detik kamu memiliki 25 pulsa 5V selama 0,02s yang memutar motor, masing-masing diikuti oleh jeda 0,02s dengan 0V yang tidak memutar motor. Setiap pulsa memutar motor sepersepuluh putaran, yang berarti motor menyelesaikan 2,5 putaran per detik. Kamu telah menggunakan sinyal digital untuk memutar motor pada 2,5 putaran per detik, atau 150 [putaran per menit](https://wikipedia.org/wiki/Revolutions_per_minute) (ukuran kecepatan rotasi yang tidak standar).

```output
25 pulses per second x 0.1 rotations per pulse = 2.5 rotations per second
2.5 rotations per second x 60 seconds in a minute = 150rpm
```

> 🎓 Ketika sinyal PWM menyala selama setengah waktu, dan mati selama setengah waktu, ini disebut sebagai [siklus tugas 50%](https://wikipedia.org/wiki/Duty_cycle). Siklus tugas diukur sebagai persentase waktu sinyal berada dalam keadaan nyala dibandingkan dengan keadaan mati.

![Rotasi motor dengan modulasi lebar pulsa pada 75 RPM](../../../../../translated_images/id/pwm-motor-75rpm.a5e4c939934b6e14.webp)

Kamu dapat mengubah kecepatan motor dengan mengubah ukuran pulsa. Sebagai contoh, dengan motor yang sama kamu dapat mempertahankan waktu siklus yang sama yaitu 0,04s, dengan pulsa nyala dipotong setengah menjadi 0,01s, dan pulsa mati meningkat menjadi 0,03s. Kamu memiliki jumlah pulsa per detik yang sama (25), tetapi setiap pulsa nyala hanya setengah panjangnya. Pulsa setengah panjang hanya memutar motor seperdua puluh putaran, dan pada 25 pulsa per detik akan menyelesaikan 1,25 putaran per detik atau 75rpm. Dengan mengubah kecepatan pulsa sinyal digital, kamu telah mengurangi kecepatan motor analog menjadi setengahnya.

```output
25 pulses per second x 0.05 rotations per pulse = 1.25 rotations per second
1.25 rotations per second x 60 seconds in a minute = 75rpm
```

✅ Bagaimana kamu akan menjaga rotasi motor tetap halus, terutama pada kecepatan rendah? Apakah kamu akan menggunakan sejumlah kecil pulsa panjang dengan jeda panjang atau banyak pulsa sangat pendek dengan jeda sangat pendek?

> 💁 Beberapa sensor juga menggunakan PWM untuk mengubah sinyal analog menjadi sinyal digital.

> 🎓 Kamu dapat membaca lebih lanjut tentang modulasi lebar pulsa di [halaman modulasi lebar pulsa di Wikipedia](https://wikipedia.org/wiki/Pulse-width_modulation).

### Aktuator Digital

Aktuator digital, seperti sensor digital, memiliki dua keadaan yang dikontrol oleh tegangan tinggi atau rendah atau memiliki DAC bawaan sehingga dapat mengubah sinyal digital menjadi sinyal analog.

Salah satu aktuator digital sederhana adalah LED. Ketika perangkat mengirimkan sinyal digital 1, tegangan tinggi dikirimkan yang menyalakan LED. Ketika sinyal digital 0 dikirimkan, tegangan turun menjadi 0V dan LED mati.

![LED mati pada 0 volt dan menyala pada 5V](../../../../../translated_images/id/led.ec6d94f66676a174ad06d9fa9ea49c2ee89beb18b312d5c6476467c66375b07f.png)

✅ Aktuator 2-keadaan sederhana apa lagi yang bisa kamu pikirkan? Salah satu contohnya adalah solenoid, yang merupakan elektromagnet yang dapat diaktifkan untuk melakukan hal-hal seperti menggerakkan baut pintu untuk mengunci/membuka kunci pintu.

Aktuator digital yang lebih canggih, seperti layar, memerlukan data digital untuk dikirimkan dalam format tertentu. Mereka biasanya dilengkapi dengan pustaka yang mempermudah pengiriman data yang benar untuk mengontrolnya.

---

## 🚀 Tantangan

Tantangan dalam dua pelajaran terakhir adalah untuk mencantumkan sebanyak mungkin perangkat IoT yang ada di rumah, sekolah, atau tempat kerja kamu dan menentukan apakah perangkat tersebut dibangun di sekitar mikrokontroler atau komputer papan tunggal, atau bahkan campuran keduanya.

Untuk setiap perangkat yang kamu cantumkan, sensor dan aktuator apa yang terhubung dengannya? Apa tujuan dari setiap sensor dan aktuator yang terhubung ke perangkat tersebut?

## Kuis Pasca-Pelajaran

[Kuis Pasca-Pelajaran](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/6)

## Tinjauan & Studi Mandiri

* Bacalah tentang listrik dan sirkuit di [ThingLearn](http://thinglearn.jenlooper.com/curriculum/).
* Bacalah tentang berbagai jenis sensor suhu di [Panduan Sensor Suhu Seeed Studios](https://www.seeedstudio.com/blog/2019/10/14/temperature-sensors-for-arduino-projects/)
* Bacalah tentang LED di [halaman LED Wikipedia](https://wikipedia.org/wiki/Light-emitting_diode)

## Tugas

[Penelitian sensor dan aktuator](assignment.md)

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.