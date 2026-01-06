<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3dce18fab38adf93ff30b8c221b1eec5",
  "translation_date": "2025-08-27T20:36:10+00:00",
  "source_file": "hardware.md",
  "language_code": "ms"
}
-->
# Perkakasan

Huruf **T** dalam IoT merujuk kepada **Things** (Perkara) dan merujuk kepada peranti yang berinteraksi dengan dunia di sekeliling kita. Setiap projek adalah berdasarkan perkakasan dunia sebenar yang tersedia untuk pelajar dan penggemar. Kami mempunyai dua pilihan perkakasan IoT untuk digunakan bergantung pada keutamaan peribadi, pengetahuan atau keutamaan bahasa pengaturcaraan, matlamat pembelajaran, dan ketersediaan. Kami juga menyediakan versi 'perkakasan maya' untuk mereka yang tidak mempunyai akses kepada perkakasan atau ingin belajar lebih lanjut sebelum membuat pembelian.

> 💁 Anda tidak perlu membeli sebarang perkakasan IoT untuk menyelesaikan tugasan. Anda boleh melakukan semuanya menggunakan perkakasan IoT maya.

Pilihan perkakasan fizikal adalah Arduino atau Raspberry Pi. Setiap platform mempunyai kelebihan dan kekurangannya sendiri, dan semua ini dibincangkan dalam salah satu pelajaran awal. Jika anda belum memutuskan platform perkakasan, anda boleh menyemak [pelajaran kedua dalam projek pertama](./1-getting-started/lessons/2-deeper-dive/README.md) untuk menentukan platform perkakasan mana yang paling menarik untuk dipelajari.

Perkakasan tertentu dipilih untuk mengurangkan kerumitan pelajaran dan tugasan. Walaupun perkakasan lain mungkin berfungsi, kami tidak dapat menjamin semua tugasan akan disokong pada peranti anda tanpa perkakasan tambahan. Sebagai contoh, banyak peranti Arduino tidak mempunyai WiFi, yang diperlukan untuk menyambung ke awan - terminal Wio dipilih kerana ia mempunyai WiFi terbina dalam.

Anda juga memerlukan beberapa item bukan teknikal, seperti tanah atau pokok pasu, dan buah-buahan atau sayur-sayuran.

## Beli kit

![Logo Seeed Studios](../../translated_images/seeed-logo.74732b6b482b6e8e.ms.png)

Seeed Studios dengan baik hati telah menyediakan semua perkakasan sebagai kit yang mudah dibeli:

### Arduino - Wio Terminal

**[IoT untuk pemula dengan Seeed dan Microsoft - Kit Permulaan Wio Terminal](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![Kit perkakasan Wio Terminal](../../translated_images/wio-hardware-kit.4c70c48b85e4283a.ms.png)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[IoT untuk pemula dengan Seeed dan Microsoft - Kit Permulaan Raspberry Pi 4](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![Kit perkakasan Raspberry Pi Terminal](../../translated_images/pi-hardware-kit.26dbadaedb7dd44c73b0131d5d68ea29472ed0a9744f90d5866c6d82f2d16380.ms.png)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

Semua kod peranti untuk Arduino ditulis dalam C++. Untuk menyelesaikan semua tugasan, anda memerlukan perkara berikut:

### Perkakasan Arduino

* [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *Pilihan* - Kabel USB-C atau penyesuai USB-A ke USB-C. Terminal Wio mempunyai port USB-C dan disertakan dengan kabel USB-C ke USB-A. Jika PC atau Mac anda hanya mempunyai port USB-C, anda memerlukan kabel USB-C atau penyesuai USB-A ke USB-C.

### Sensor dan aktuator khusus Arduino

Ini khusus untuk menggunakan peranti Arduino Wio Terminal, dan tidak relevan untuk Raspberry Pi.

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [Wayar Jumper Breadboard](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* Fon kepala atau pembesar suara lain dengan jack 3.5mm, atau pembesar suara JST seperti:
  * [Pembesar Suara Mono Tertutup - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* Kad microSD 16GB atau kurang, bersama dengan penyambung untuk menggunakan kad SD dengan komputer anda jika anda tidak mempunyai satu terbina dalam. **NOTA** - Terminal Wio hanya menyokong kad SD sehingga 16GB, ia tidak menyokong kapasiti yang lebih tinggi.

## Raspberry Pi

Semua kod peranti untuk Raspberry Pi ditulis dalam Python. Untuk menyelesaikan semua tugasan, anda memerlukan perkara berikut:

### Perkakasan Raspberry Pi

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 Versi dari Pi 2B dan ke atas sepatutnya berfungsi dengan tugasan dalam pelajaran ini. Jika anda merancang untuk menjalankan VS Code terus pada Pi, maka Pi 4 dengan RAM 2GB atau lebih diperlukan. Jika anda akan mengakses Pi dari jauh, maka mana-mana Pi 2B dan ke atas akan berfungsi.
* Kad microSD (Anda boleh mendapatkan kit Raspberry Pi yang disertakan dengan kad microSD), bersama dengan penyambung untuk menggunakan kad SD dengan komputer anda jika anda tidak mempunyai satu terbina dalam.
* Bekalan kuasa USB (Anda boleh mendapatkan kit Raspberry Pi 4 yang disertakan dengan bekalan kuasa). Jika anda menggunakan Raspberry Pi 4, anda memerlukan bekalan kuasa USB-C, manakala peranti terdahulu memerlukan bekalan kuasa micro-USB.

### Sensor dan aktuator khusus Raspberry Pi

Ini khusus untuk menggunakan Raspberry Pi, dan tidak relevan untuk peranti Arduino.

* [Grove Pi base hat](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Modul Kamera Raspberry Pi](https://www.raspberrypi.org/products/camera-module-v2/)
* Mikrofon dan pembesar suara:

  Gunakan salah satu daripada berikut (atau setara):
  * Mana-mana mikrofon USB dengan mana-mana pembesar suara USB, atau pembesar suara dengan kabel jack 3.5mm, atau menggunakan output audio HDMI jika Raspberry Pi anda disambungkan ke monitor atau TV dengan pembesar suara
  * Mana-mana set kepala USB dengan mikrofon terbina dalam
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) dengan
    * Fon kepala atau pembesar suara lain dengan jack 3.5mm, atau pembesar suara JST seperti:
    * [Pembesar Suara Mono Tertutup - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [Speakerphone USB](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Sensor Cahaya Grove](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Butang Grove](https://www.seeedstudio.com/Grove-Button.html)

## Sensor dan aktuator

Kebanyakan sensor dan aktuator yang diperlukan digunakan oleh kedua-dua laluan pembelajaran Arduino dan Raspberry Pi:

* [Grove LED](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Sensor kelembapan dan suhu Grove](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Sensor kelembapan tanah kapasitif Grove](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Relay Grove](https://www.seeedstudio.com/Grove-Relay.html)
* [Grove GPS (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Sensor Jarak Masa Penerbangan Grove](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## Perkakasan pilihan

Pelajaran tentang penyiraman automatik berfungsi menggunakan relay. Sebagai pilihan, anda boleh menyambungkan relay ini ke pam air yang dikuasakan oleh USB menggunakan perkakasan yang disenaraikan di bawah.

* [Pam air 6V](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [Terminal USB](https://www.adafruit.com/product/3628)
* Paip silikon
* Wayar merah dan hitam
* Pemutar skru kepala rata kecil

## Perkakasan maya

Laluan perkakasan maya akan menyediakan simulator untuk sensor dan aktuator, yang dilaksanakan dalam Python. Bergantung pada ketersediaan perkakasan anda, anda boleh menjalankannya pada peranti pembangunan biasa anda, seperti Mac, PC, atau menjalankannya pada Raspberry Pi dan mensimulasikan hanya perkakasan yang anda tidak miliki. Sebagai contoh, jika anda mempunyai kamera Raspberry Pi tetapi tidak mempunyai sensor Grove, anda boleh menjalankan kod peranti maya pada Pi anda dan mensimulasikan sensor Grove, tetapi menggunakan kamera fizikal.

Perkakasan maya akan menggunakan projek [CounterFit](https://github.com/CounterFit-IoT/CounterFit).

Untuk menyelesaikan pelajaran ini, anda perlu mempunyai kamera web, mikrofon, dan output audio seperti pembesar suara atau fon kepala. Peranti ini boleh terbina dalam atau luaran, dan perlu dikonfigurasikan untuk berfungsi dengan sistem operasi anda serta tersedia untuk digunakan dari semua aplikasi.

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.