<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3dce18fab38adf93ff30b8c221b1eec5",
  "translation_date": "2025-08-27T20:35:46+00:00",
  "source_file": "hardware.md",
  "language_code": "id"
}
-->
# Perangkat Keras

**T** dalam IoT adalah **Things** yang merujuk pada perangkat yang berinteraksi dengan dunia di sekitar kita. Setiap proyek didasarkan pada perangkat keras nyata yang tersedia untuk pelajar dan penggemar. Kami memiliki dua pilihan perangkat keras IoT yang dapat digunakan tergantung pada preferensi pribadi, pengetahuan atau preferensi bahasa pemrograman, tujuan pembelajaran, dan ketersediaan. Kami juga menyediakan versi 'perangkat keras virtual' bagi mereka yang tidak memiliki akses ke perangkat keras, atau ingin belajar lebih banyak sebelum memutuskan untuk membeli.

> 💁 Anda tidak perlu membeli perangkat keras IoT untuk menyelesaikan tugas. Anda dapat melakukan semuanya menggunakan perangkat keras IoT virtual.

Pilihan perangkat keras fisik adalah Arduino atau Raspberry Pi. Setiap platform memiliki kelebihan dan kekurangan masing-masing, yang semuanya dibahas dalam salah satu pelajaran awal. Jika Anda belum memutuskan platform perangkat keras, Anda dapat meninjau [pelajaran kedua dari proyek pertama](./1-getting-started/lessons/2-deeper-dive/README.md) untuk menentukan platform perangkat keras mana yang paling menarik untuk dipelajari.

Perangkat keras spesifik dipilih untuk mengurangi kompleksitas pelajaran dan tugas. Meskipun perangkat keras lain mungkin berfungsi, kami tidak dapat menjamin semua tugas akan didukung pada perangkat Anda tanpa perangkat keras tambahan. Sebagai contoh, banyak perangkat Arduino tidak memiliki WiFi, yang diperlukan untuk terhubung ke cloud - Wio terminal dipilih karena memiliki WiFi bawaan.

Anda juga akan membutuhkan beberapa item non-teknis, seperti tanah atau tanaman pot, serta buah atau sayuran.

## Beli Kit

![Logo Seeed Studios](../../translated_images/seeed-logo.74732b6b482b6e8e.id.png)

Seeed Studios dengan sangat baik telah menyediakan semua perangkat keras dalam bentuk kit yang mudah dibeli:

### Arduino - Wio Terminal

**[IoT untuk pemula dengan Seeed dan Microsoft - Wio Terminal Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![Kit perangkat keras Wio Terminal](../../translated_images/wio-hardware-kit.4c70c48b85e4283a.id.png)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[IoT untuk pemula dengan Seeed dan Microsoft - Raspberry Pi 4 Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![Kit perangkat keras Raspberry Pi Terminal](../../translated_images/pi-hardware-kit.26dbadaedb7dd44c73b0131d5d68ea29472ed0a9744f90d5866c6d82f2d16380.id.png)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

Semua kode perangkat untuk Arduino ditulis dalam C++. Untuk menyelesaikan semua tugas, Anda akan membutuhkan hal-hal berikut:

### Perangkat keras Arduino

* [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *Opsional* - Kabel USB-C atau adaptor USB-A ke USB-C. Wio terminal memiliki port USB-C dan dilengkapi dengan kabel USB-C ke USB-A. Jika PC atau Mac Anda hanya memiliki port USB-C, Anda akan membutuhkan kabel USB-C, atau adaptor USB-A ke USB-C.

### Sensor dan aktuator khusus Arduino

Ini khusus untuk menggunakan perangkat Arduino Wio terminal, dan tidak relevan untuk menggunakan Raspberry Pi.

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [Breadboard Jumper Wires](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* Headphone atau speaker lain dengan jack 3.5mm, atau speaker JST seperti:
  * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* Kartu microSD 16GB atau kurang, bersama dengan konektor untuk menggunakan kartu SD dengan komputer Anda jika tidak memiliki slot bawaan. **NOTE** - Wio Terminal hanya mendukung kartu SD hingga 16GB, tidak mendukung kapasitas yang lebih tinggi.

## Raspberry Pi

Semua kode perangkat untuk Raspberry Pi ditulis dalam Python. Untuk menyelesaikan semua tugas, Anda akan membutuhkan hal-hal berikut:

### Perangkat keras Raspberry Pi

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 Versi dari Pi 2B dan di atasnya seharusnya berfungsi dengan tugas dalam pelajaran ini. Jika Anda berencana menjalankan VS Code langsung di Pi, maka Pi 4 dengan RAM 2GB atau lebih diperlukan. Jika Anda akan mengakses Pi secara remote, maka Pi 2B dan di atasnya akan berfungsi.
* Kartu microSD (Anda dapat membeli kit Raspberry Pi yang sudah dilengkapi dengan kartu microSD), bersama dengan konektor untuk menggunakan kartu SD dengan komputer Anda jika tidak memiliki slot bawaan.
* Catu daya USB (Anda dapat membeli kit Raspberry Pi 4 yang sudah dilengkapi dengan catu daya). Jika Anda menggunakan Raspberry Pi 4, Anda membutuhkan catu daya USB-C, perangkat sebelumnya membutuhkan catu daya micro-USB.

### Sensor dan aktuator khusus Raspberry Pi

Ini khusus untuk menggunakan Raspberry Pi, dan tidak relevan untuk menggunakan perangkat Arduino.

* [Grove Pi base hat](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Modul kamera Raspberry Pi](https://www.raspberrypi.org/products/camera-module-v2/)
* Mikrofon dan speaker:

  Gunakan salah satu dari berikut ini (atau yang setara):
  * Mikrofon USB dengan speaker USB, atau speaker dengan kabel jack 3.5mm, atau menggunakan output audio HDMI jika Raspberry Pi Anda terhubung ke monitor atau TV dengan speaker
  * Headset USB dengan mikrofon bawaan
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) dengan
    * Headphone atau speaker lain dengan jack 3.5mm, atau speaker JST seperti:
    * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [USB Speakerphone](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Sensor cahaya Grove](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Tombol Grove](https://www.seeedstudio.com/Grove-Button.html)

## Sensor dan aktuator

Sebagian besar sensor dan aktuator yang diperlukan digunakan oleh jalur pembelajaran Arduino dan Raspberry Pi:

* [Grove LED](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Sensor kelembapan dan suhu Grove](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Sensor kelembapan tanah kapasitif Grove](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Relay Grove](https://www.seeedstudio.com/Grove-Relay.html)
* [GPS Grove (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Sensor jarak Time of Flight Grove](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## Perangkat keras opsional

Pelajaran tentang penyiraman otomatis bekerja menggunakan relay. Sebagai opsi, Anda dapat menghubungkan relay ini ke pompa air yang ditenagai oleh USB menggunakan perangkat keras yang tercantum di bawah ini.

* [Pompa air 6V](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [Terminal USB](https://www.adafruit.com/product/3628)
* Pipa silikon
* Kabel merah dan hitam
* Obeng kecil kepala datar

## Perangkat keras virtual

Rute perangkat keras virtual akan menyediakan simulator untuk sensor dan aktuator, yang diimplementasikan dalam Python. Bergantung pada ketersediaan perangkat keras Anda, Anda dapat menjalankannya di perangkat pengembangan normal Anda, seperti Mac, PC, atau menjalankannya di Raspberry Pi dan hanya mensimulasikan perangkat keras yang tidak Anda miliki. Sebagai contoh, jika Anda memiliki kamera Raspberry Pi tetapi tidak memiliki sensor Grove, Anda dapat menjalankan kode perangkat virtual di Pi Anda dan mensimulasikan sensor Grove, tetapi menggunakan kamera fisik.

Perangkat keras virtual akan menggunakan proyek [CounterFit](https://github.com/CounterFit-IoT/CounterFit).

Untuk menyelesaikan pelajaran ini, Anda perlu memiliki webcam, mikrofon, dan output audio seperti speaker atau headphone. Perangkat ini dapat berupa bawaan atau eksternal, dan perlu dikonfigurasi agar berfungsi dengan sistem operasi Anda serta tersedia untuk digunakan dari semua aplikasi.

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berupaya untuk memberikan hasil yang akurat, harap diketahui bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.