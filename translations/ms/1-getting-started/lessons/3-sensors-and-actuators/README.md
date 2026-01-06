<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e9ee00eb5fc55922a73762acc542166b",
  "translation_date": "2025-08-27T22:27:05+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/README.md",
  "language_code": "ms"
}
-->
# Berinteraksi dengan Dunia Fizikal Menggunakan Sensor dan Aktuator

![Gambaran sketchnote untuk pelajaran ini](../../../../../translated_images/lesson-3.cc3b7b4cd646de598698cce043c0393fd62ef42bac2eaf60e61272cd844250f4.ms.jpg)

> Sketchnote oleh [Nitya Narasimhan](https://github.com/nitya). Klik gambar untuk versi yang lebih besar.

Pelajaran ini diajar sebagai sebahagian daripada siri [Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) dari [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Ia disampaikan dalam 2 video - satu pelajaran selama 1 jam, dan satu sesi soal jawab selama 1 jam yang mendalami bahagian pelajaran dan menjawab soalan.

[![Pelajaran 3: Berinteraksi dengan Dunia Fizikal Menggunakan Sensor dan Aktuator](https://img.youtube.com/vi/Lqalu1v6aF4/0.jpg)](https://youtu.be/Lqalu1v6aF4)

[![Pelajaran 3: Berinteraksi dengan Dunia Fizikal Menggunakan Sensor dan Aktuator - Sesi soal jawab](https://img.youtube.com/vi/qR3ekcMlLWA/0.jpg)](https://youtu.be/qR3ekcMlLWA)

> 🎥 Klik gambar di atas untuk menonton video

## Kuiz Pra-Pelajaran

[Kuiz Pra-Pelajaran](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/5)

## Pengenalan

Pelajaran ini memperkenalkan dua konsep penting untuk peranti IoT anda - sensor dan aktuator. Anda juga akan mencuba kedua-duanya secara langsung, dengan menambah sensor cahaya pada projek IoT anda, kemudian menambah LED yang dikawal oleh tahap cahaya, secara efektif membina lampu malam.

Dalam pelajaran ini, kita akan membincangkan:

* [Apa itu sensor?](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Menggunakan sensor](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Jenis sensor](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Apa itu aktuator?](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Menggunakan aktuator](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Jenis aktuator](../../../../../1-getting-started/lessons/3-sensors-and-actuators)

## Apa itu sensor?

Sensor adalah peranti perkakasan yang mengesan dunia fizikal - iaitu, ia mengukur satu atau lebih sifat di sekelilingnya dan menghantar maklumat tersebut kepada peranti IoT. Sensor meliputi pelbagai jenis peranti kerana terdapat banyak perkara yang boleh diukur, daripada sifat semula jadi seperti suhu udara kepada interaksi fizikal seperti pergerakan.

Beberapa sensor biasa termasuk:

* Sensor suhu - mengesan suhu udara atau suhu objek yang disentuhnya. Untuk penggemar dan pembangun, sensor ini sering digabungkan dengan sensor tekanan udara dan kelembapan dalam satu peranti.
* Butang - mengesan apabila ia ditekan.
* Sensor cahaya - mengesan tahap cahaya dan boleh digunakan untuk warna tertentu, cahaya UV, cahaya IR, atau cahaya yang boleh dilihat secara umum.
* Kamera - mengesan representasi visual dunia dengan mengambil gambar atau menstrim video.
* Akselerometer - mengesan pergerakan dalam pelbagai arah.
* Mikrofon - mengesan bunyi, sama ada tahap bunyi umum atau bunyi arah.

✅ Lakukan sedikit penyelidikan. Apakah sensor yang terdapat pada telefon anda?

Semua sensor mempunyai satu persamaan - ia menukar apa yang mereka kesan kepada isyarat elektrik yang boleh ditafsirkan oleh peranti IoT. Cara isyarat elektrik ini ditafsirkan bergantung pada sensor, serta protokol komunikasi yang digunakan untuk berkomunikasi dengan peranti IoT.

## Menggunakan sensor

Ikuti panduan yang berkaitan di bawah untuk menambah sensor pada peranti IoT anda:

* [Arduino - Wio Terminal](wio-terminal-sensor.md)
* [Komputer papan tunggal - Raspberry Pi](pi-sensor.md)
* [Komputer papan tunggal - Peranti maya](virtual-device-sensor.md)

## Jenis sensor

Sensor boleh menjadi analog atau digital.

### Sensor analog

Beberapa sensor yang paling asas adalah sensor analog. Sensor ini menerima voltan daripada peranti IoT, komponen sensor menyesuaikan voltan ini, dan voltan yang dikembalikan daripada sensor diukur untuk memberikan nilai sensor.

> 🎓 Voltan adalah ukuran seberapa besar daya untuk menggerakkan elektrik dari satu tempat ke tempat lain, seperti dari terminal positif bateri ke terminal negatif. Sebagai contoh, bateri AA standard adalah 1.5V (V adalah simbol untuk volt) dan boleh menolak elektrik dengan daya 1.5V dari terminal positifnya ke terminal negatifnya. Perkakasan elektrik yang berbeza memerlukan voltan yang berbeza untuk berfungsi, contohnya, LED boleh menyala dengan antara 2-3V, tetapi mentol lampu filamen 100W memerlukan 240V. Anda boleh membaca lebih lanjut tentang voltan di [halaman Voltan di Wikipedia](https://wikipedia.org/wiki/Voltage).

Satu contoh ialah potensiometer. Ini adalah dail yang boleh anda putar antara dua kedudukan dan sensor mengukur putaran tersebut.

![Potensiometer yang diset pada titik tengah dihantar 5 volt mengembalikan 3.8 volt](../../../../../translated_images/potentiometer.35a348b9ce22f6ec.ms.png)

Peranti IoT akan menghantar isyarat elektrik kepada potensiometer pada voltan tertentu, seperti 5 volt (5V). Apabila potensiometer disesuaikan, ia mengubah voltan yang keluar dari sisi lain. Bayangkan anda mempunyai potensiometer yang dilabelkan sebagai dail dari 0 hingga [11](https://wikipedia.org/wiki/Up_to_eleven), seperti tombol kelantangan pada penguat. Apabila potensiometer berada dalam kedudukan mati sepenuhnya (0), maka 0V (0 volt) akan keluar. Apabila ia berada dalam kedudukan hidup sepenuhnya (11), 5V (5 volt) akan keluar.

> 🎓 Ini adalah penyederhanaan, dan anda boleh membaca lebih lanjut tentang potensiometer dan perintang boleh ubah di [halaman Wikipedia potensiometer](https://wikipedia.org/wiki/Potentiometer).

Voltan yang keluar dari sensor kemudian dibaca oleh peranti IoT, dan peranti boleh bertindak balas terhadapnya. Bergantung pada sensor, voltan ini boleh menjadi nilai sewenang-wenangnya atau boleh dipetakan kepada unit standard. Sebagai contoh, sensor suhu analog berdasarkan [termistor](https://wikipedia.org/wiki/Thermistor) mengubah rintangannya bergantung pada suhu. Voltan keluaran kemudian boleh ditukar kepada suhu dalam Kelvin, dan seterusnya kepada °C atau °F, melalui pengiraan dalam kod.

✅ Apa yang anda fikir akan berlaku jika sensor mengembalikan voltan yang lebih tinggi daripada yang dihantar (contohnya datang dari bekalan kuasa luaran)? ⛔️ JANGAN cuba ini.

#### Penukaran analog ke digital

Peranti IoT adalah digital - ia tidak boleh berfungsi dengan nilai analog, ia hanya berfungsi dengan 0 dan 1. Ini bermakna nilai sensor analog perlu ditukar kepada isyarat digital sebelum ia boleh diproses. Banyak peranti IoT mempunyai penukar analog-ke-digital (ADC) untuk menukar input analog kepada representasi digital nilainya. Sensor juga boleh berfungsi dengan ADC melalui papan penyambung. Sebagai contoh, dalam ekosistem Seeed Grove dengan Raspberry Pi, sensor analog disambungkan ke port tertentu pada 'hat' yang diletakkan di atas Pi yang disambungkan ke pin GPIO Pi, dan hat ini mempunyai ADC untuk menukar voltan kepada isyarat digital yang boleh dihantar dari pin GPIO Pi.

Bayangkan anda mempunyai sensor cahaya analog yang disambungkan kepada peranti IoT yang menggunakan 3.3V dan mengembalikan nilai 1V. 1V ini tidak bermakna dalam dunia digital, jadi ia perlu ditukar. Voltan akan ditukar kepada nilai analog menggunakan skala bergantung pada peranti dan sensor. Satu contoh ialah sensor cahaya Seeed Grove yang mengeluarkan nilai dari 0 hingga 1,023. Untuk sensor ini yang beroperasi pada 3.3V, keluaran 1V akan menjadi nilai 300. Peranti IoT tidak boleh mengendalikan 300 sebagai nilai analog, jadi nilai itu akan ditukar kepada `0000000100101100`, representasi binari bagi 300 oleh hat Grove. Ini kemudian akan diproses oleh peranti IoT.

✅ Jika anda tidak tahu tentang binari, lakukan sedikit penyelidikan untuk belajar bagaimana nombor diwakili oleh 0 dan 1. [Pelajaran pengenalan kepada binari di BBC Bitesize](https://www.bbc.co.uk/bitesize/guides/zwsbwmn/revision/1) adalah tempat yang bagus untuk bermula.

Dari perspektif pengaturcaraan, semua ini biasanya dikendalikan oleh perpustakaan yang disertakan dengan sensor, jadi anda tidak perlu risau tentang penukaran ini sendiri. Untuk sensor cahaya Grove, anda akan menggunakan perpustakaan Python dan memanggil sifat `light`, atau menggunakan perpustakaan Arduino dan memanggil `analogRead` untuk mendapatkan nilai 300.

### Sensor digital

Sensor digital, seperti sensor analog, mengesan dunia di sekeliling mereka menggunakan perubahan dalam voltan elektrik. Perbezaannya ialah mereka mengeluarkan isyarat digital, sama ada dengan hanya mengukur dua keadaan atau dengan menggunakan ADC terbina dalam. Sensor digital semakin banyak digunakan untuk mengelakkan keperluan menggunakan ADC sama ada dalam papan penyambung atau pada peranti IoT itu sendiri.

Sensor digital yang paling mudah ialah butang atau suis. Ini adalah sensor dengan dua keadaan, hidup atau mati.

![Butang dihantar 5 volt. Apabila tidak ditekan ia mengembalikan 0 volt, apabila ditekan ia mengembalikan 5 volt](../../../../../translated_images/button.eadb560b77ac45e56f523d9d8876e40444f63b419e33eb820082d461fa79490b.ms.png)

Pin pada peranti IoT seperti pin GPIO boleh mengukur isyarat ini secara langsung sebagai 0 atau 1. Jika voltan yang dihantar sama dengan voltan yang dikembalikan, nilai yang dibaca ialah 1, jika tidak nilai yang dibaca ialah 0. Tidak perlu menukar isyarat, ia hanya boleh menjadi 1 atau 0.

> 💁 Voltan tidak pernah tepat terutamanya kerana komponen dalam sensor akan mempunyai beberapa rintangan, jadi biasanya terdapat toleransi. Sebagai contoh, pin GPIO pada Raspberry Pi berfungsi pada 3.3V, dan membaca isyarat kembali di atas 1.8V sebagai 1, di bawah 1.8V sebagai 0.

* 3.3V masuk ke dalam butang. Butang dimatikan jadi 0V keluar, memberikan nilai 0
* 3.3V masuk ke dalam butang. Butang dihidupkan jadi 3.3V keluar, memberikan nilai 1

Sensor digital yang lebih maju membaca nilai analog, kemudian menukarnya menggunakan ADC terbina dalam kepada isyarat digital. Sebagai contoh, sensor suhu digital masih menggunakan termokopel dengan cara yang sama seperti sensor analog, dan masih mengukur perubahan voltan yang disebabkan oleh rintangan termokopel pada suhu semasa. Daripada mengembalikan nilai analog dan bergantung pada peranti atau papan penyambung untuk menukar kepada isyarat digital, ADC yang dibina dalam sensor akan menukar nilai dan menghantarnya sebagai siri 0 dan 1 kepada peranti IoT. 0 dan 1 ini dihantar dengan cara yang sama seperti isyarat digital untuk butang dengan 1 sebagai voltan penuh dan 0 sebagai 0v.

![Sensor suhu digital menukar bacaan analog kepada data binari dengan 0 sebagai 0 volt dan 1 sebagai 5 volt sebelum menghantarnya ke peranti IoT](../../../../../translated_images/temperature-as-digital.85004491b977bae1.ms.png)

Menghantar data digital membolehkan sensor menjadi lebih kompleks dan menghantar data yang lebih terperinci, malah data yang disulitkan untuk sensor yang selamat. Satu contoh ialah kamera. Ini adalah sensor yang menangkap imej dan menghantarnya sebagai data digital yang mengandungi imej tersebut, biasanya dalam format termampat seperti JPEG, untuk dibaca oleh peranti IoT. Ia juga boleh menstrim video dengan menangkap imej dan menghantar sama ada imej lengkap bingkai demi bingkai atau aliran video termampat.

## Apa itu aktuator?

Aktuator adalah bertentangan dengan sensor - ia menukar isyarat elektrik daripada peranti IoT anda kepada interaksi dengan dunia fizikal seperti memancarkan cahaya atau bunyi, atau menggerakkan motor.

Beberapa aktuator biasa termasuk:

* LED - memancarkan cahaya apabila dihidupkan
* Pembesar suara - memancarkan bunyi berdasarkan isyarat yang dihantar kepada mereka, daripada buzzer asas kepada pembesar suara audio yang boleh memainkan muzik
* Motor stepper - menukar isyarat kepada jumlah putaran yang ditentukan, seperti memutar dail sebanyak 90°
* Relay - suis yang boleh dihidupkan atau dimatikan oleh isyarat elektrik. Ia membolehkan voltan kecil daripada peranti IoT menghidupkan voltan yang lebih besar.
* Skrin - aktuator yang lebih kompleks dan memaparkan maklumat pada paparan bersegmen. Skrin berbeza daripada paparan LED mudah kepada monitor video resolusi tinggi.

✅ Lakukan sedikit penyelidikan. Apakah aktuator yang terdapat pada telefon anda?

## Menggunakan aktuator

Ikuti panduan yang berkaitan di bawah untuk menambah aktuator pada peranti IoT anda, yang dikawal oleh sensor, untuk membina lampu malam IoT. Ia akan mengumpul tahap cahaya daripada sensor cahaya, dan menggunakan aktuator dalam bentuk LED untuk memancarkan cahaya apabila tahap cahaya yang dikesan terlalu rendah.

![Carta alir tugasan menunjukkan tahap cahaya dibaca dan diperiksa, dan LED dikawal](../../../../../translated_images/assignment-1-flow.7552a51acb1a5ec858dca6e855cdbb44206434006df8ba3799a25afcdab1665d.ms.png)

* [Arduino - Wio Terminal](wio-terminal-actuator.md)
* [Komputer papan tunggal - Raspberry Pi](pi-actuator.md)
* [Komputer papan tunggal - Peranti maya](virtual-device-actuator.md)

## Jenis aktuator

Seperti sensor, aktuator boleh menjadi analog atau digital.

### Aktuator analog

Aktuator analog mengambil isyarat analog dan menukarnya kepada beberapa jenis interaksi, di mana interaksi berubah berdasarkan voltan yang dibekalkan.

Satu contoh ialah lampu boleh dimalapkan, seperti yang mungkin anda ada di rumah anda. Jumlah voltan yang dibekalkan kepada lampu menentukan kecerahannya.
![Cahaya malap pada voltan rendah dan lebih terang pada voltan tinggi](../../../../../translated_images/dimmable-light.9ceffeb195dec1a849da718b2d71b32c35171ff7dfea9c07bbf82646a67acf6b.ms.png)

Seperti sensor, peranti IoT sebenar berfungsi dengan isyarat digital, bukan analog. Ini bermakna untuk menghantar isyarat analog, peranti IoT memerlukan penukar digital ke analog (DAC), sama ada secara langsung pada peranti IoT atau pada papan penyambung. Penukar ini akan menukar 0 dan 1 daripada peranti IoT kepada voltan analog yang boleh digunakan oleh penggerak.

✅ Apa yang anda fikir akan berlaku jika peranti IoT menghantar voltan lebih tinggi daripada yang boleh ditangani oleh penggerak?  
⛔️ JANGAN cuba menguji ini.

#### Modulasi Lebar Denyutan

Pilihan lain untuk menukar isyarat digital daripada peranti IoT kepada isyarat analog ialah modulasi lebar denyutan (PWM). Ini melibatkan penghantaran banyak denyutan digital pendek yang bertindak seolah-olah ia adalah isyarat analog.

Sebagai contoh, anda boleh menggunakan PWM untuk mengawal kelajuan motor.

Bayangkan anda mengawal motor dengan bekalan 5V. Anda menghantar denyutan pendek kepada motor anda, menukar voltan kepada tinggi (5V) selama dua peratus saat (0.02s). Dalam masa itu, motor anda boleh berputar satu persepuluh putaran, atau 36°. Isyarat kemudian berhenti selama dua peratus saat (0.02s), menghantar isyarat rendah (0V). Setiap kitaran hidup kemudian mati berlangsung selama 0.04s. Kitaran kemudian berulang.

![Modulasi lebar denyutan putaran motor pada 150 RPM](../../../../../translated_images/pwm-motor-150rpm.83347ac04ca38482.ms.png)

Ini bermakna dalam satu saat anda mempunyai 25 denyutan 5V selama 0.02s yang memutar motor, setiap satu diikuti oleh jeda 0.02s pada 0V yang tidak memutar motor. Setiap denyutan memutar motor satu persepuluh putaran, bermakna motor melengkapkan 2.5 putaran sesaat. Anda telah menggunakan isyarat digital untuk memutar motor pada 2.5 putaran sesaat, atau 150 [putaran per minit](https://wikipedia.org/wiki/Revolutions_per_minute) (ukuran kelajuan putaran yang tidak standard).

```output
25 pulses per second x 0.1 rotations per pulse = 2.5 rotations per second
2.5 rotations per second x 60 seconds in a minute = 150rpm
```

> 🎓 Apabila isyarat PWM hidup separuh masa, dan mati separuh masa, ia dirujuk sebagai [kitaran tugas 50%](https://wikipedia.org/wiki/Duty_cycle). Kitaran tugas diukur sebagai peratusan masa isyarat berada dalam keadaan hidup berbanding keadaan mati.

![Modulasi lebar denyutan putaran motor pada 75 RPM](../../../../../translated_images/pwm-motor-75rpm.a5e4c939934b6e14.ms.png)

Anda boleh mengubah kelajuan motor dengan mengubah saiz denyutan. Sebagai contoh, dengan motor yang sama, anda boleh mengekalkan masa kitaran yang sama iaitu 0.04s, dengan denyutan hidup dikurangkan kepada 0.01s, dan denyutan mati meningkat kepada 0.03s. Anda mempunyai jumlah denyutan yang sama setiap saat (25), tetapi setiap denyutan hidup adalah separuh panjang. Denyutan separuh panjang hanya memutar motor satu perdua puluh putaran, dan pada 25 denyutan sesaat akan melengkapkan 1.25 putaran sesaat atau 75rpm. Dengan mengubah kelajuan denyutan isyarat digital, anda telah mengurangkan separuh kelajuan motor analog.

```output
25 pulses per second x 0.05 rotations per pulse = 1.25 rotations per second
1.25 rotations per second x 60 seconds in a minute = 75rpm
```

✅ Bagaimana anda akan memastikan putaran motor lancar, terutamanya pada kelajuan rendah? Adakah anda akan menggunakan sejumlah kecil denyutan panjang dengan jeda panjang atau banyak denyutan pendek dengan jeda pendek?

> 💁 Sesetengah sensor juga menggunakan PWM untuk menukar isyarat analog kepada isyarat digital.

> 🎓 Anda boleh membaca lebih lanjut mengenai modulasi lebar denyutan di [halaman modulasi lebar denyutan di Wikipedia](https://wikipedia.org/wiki/Pulse-width_modulation).

### Penggerak Digital

Penggerak digital, seperti sensor digital, sama ada mempunyai dua keadaan yang dikawal oleh voltan tinggi atau rendah atau mempunyai DAC terbina dalam supaya boleh menukar isyarat digital kepada isyarat analog.

Satu penggerak digital yang mudah ialah LED. Apabila peranti menghantar isyarat digital 1, voltan tinggi dihantar yang menyalakan LED. Apabila isyarat digital 0 dihantar, voltan turun kepada 0V dan LED padam.

![LED padam pada 0 volt dan menyala pada 5V](../../../../../translated_images/led.ec6d94f66676a174ad06d9fa9ea49c2ee89beb18b312d5c6476467c66375b07f.ms.png)

✅ Apakah penggerak 2-keadaan mudah lain yang boleh anda fikirkan? Satu contoh ialah solenoid, iaitu elektromagnet yang boleh diaktifkan untuk melakukan perkara seperti menggerakkan bolt pintu untuk mengunci/membuka kunci pintu.

Penggerak digital yang lebih maju, seperti skrin, memerlukan data digital dihantar dalam format tertentu. Mereka biasanya disertakan dengan perpustakaan yang memudahkan penghantaran data yang betul untuk mengawal mereka.

---

## 🚀 Cabaran

Cabaran dalam dua pelajaran terakhir adalah untuk menyenaraikan sebanyak mungkin peranti IoT yang anda boleh yang terdapat di rumah, sekolah atau tempat kerja anda dan tentukan sama ada ia dibina di sekitar mikropengawal atau komputer papan tunggal, atau campuran kedua-duanya.

Untuk setiap peranti yang anda senaraikan, apakah sensor dan penggerak yang disambungkan kepadanya? Apakah tujuan setiap sensor dan penggerak yang disambungkan kepada peranti ini?

## Kuiz Selepas Kuliah

[Kuiz Selepas Kuliah](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/6)

## Ulasan & Kajian Kendiri

* Baca tentang elektrik dan litar di [ThingLearn](http://thinglearn.jenlooper.com/curriculum/).
* Baca tentang jenis sensor suhu yang berbeza di [panduan Sensor Suhu Seeed Studios](https://www.seeedstudio.com/blog/2019/10/14/temperature-sensors-for-arduino-projects/)
* Baca tentang LED di [halaman Wikipedia LED](https://wikipedia.org/wiki/Light-emitting_diode)

## Tugasan

[Kajian sensor dan penggerak](assignment.md)

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.