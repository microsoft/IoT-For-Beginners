<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "8ff0d0a1d29832bb896b9c103b69a452",
  "translation_date": "2025-08-27T22:44:03+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/pi.md",
  "language_code": "id"
}
-->
# Raspberry Pi

[Raspberry Pi](https://raspberrypi.org) adalah komputer papan tunggal. Anda dapat menambahkan sensor dan aktuator menggunakan berbagai perangkat dan ekosistem, dan untuk pelajaran ini, kita akan menggunakan ekosistem perangkat keras bernama [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html). Anda akan memprogram Pi Anda dan mengakses sensor Grove menggunakan Python.

![Raspberry Pi 4](../../../../../translated_images/raspberry-pi-4.fd4590d308c3d456.id.jpg)

## Persiapan

Jika Anda menggunakan Raspberry Pi sebagai perangkat keras IoT Anda, ada dua pilihan - Anda dapat menyelesaikan semua pelajaran ini dan memprogram langsung di Pi, atau Anda dapat menghubungkan secara jarak jauh ke Pi 'headless' dan memprogram dari komputer Anda.

Sebelum memulai, Anda juga perlu menghubungkan Grove Base Hat ke Pi Anda.

### Tugas - Persiapan

Pasang Grove Base Hat pada Pi Anda dan konfigurasikan Pi.

1. Hubungkan Grove Base Hat ke Pi Anda. Soket pada hat ini pas di atas semua pin GPIO pada Pi, meluncur ke bawah hingga duduk dengan kokoh di dasar. Hat ini menutupi Pi.

    ![Memasang Grove Hat](../../../../../images/pi-grove-hat-fitting.gif)

1. Tentukan bagaimana Anda ingin memprogram Pi Anda, lalu buka bagian yang relevan di bawah ini:

    * [Bekerja langsung di Pi Anda](../../../../../1-getting-started/lessons/1-introduction-to-iot)
    * [Akses jarak jauh untuk memprogram Pi](../../../../../1-getting-started/lessons/1-introduction-to-iot)

### Bekerja langsung di Pi Anda

Jika Anda ingin bekerja langsung di Pi Anda, Anda dapat menggunakan versi desktop Raspberry Pi OS dan menginstal semua alat yang diperlukan.

#### Tugas - Bekerja langsung di Pi Anda

Siapkan Pi Anda untuk pengembangan.

1. Ikuti instruksi dalam [panduan pengaturan Raspberry Pi](https://projects.raspberrypi.org/en/projects/raspberry-pi-setting-up) untuk menyiapkan Pi Anda, menghubungkannya ke keyboard/mouse/monitor, menghubungkannya ke jaringan WiFi atau ethernet Anda, dan memperbarui perangkat lunak.

Untuk memprogram Pi menggunakan sensor dan aktuator Grove, Anda perlu menginstal editor untuk menulis kode perangkat, serta berbagai pustaka dan alat yang berinteraksi dengan perangkat keras Grove.

1. Setelah Pi Anda reboot, buka Terminal dengan mengklik ikon **Terminal** di bilah menu atas, atau pilih *Menu -> Accessories -> Terminal*.

1. Jalankan perintah berikut untuk memastikan OS dan perangkat lunak yang diinstal sudah diperbarui:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes
    ```

1. Jalankan perintah berikut untuk menginstal semua pustaka yang diperlukan untuk perangkat keras Grove:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Ini dimulai dengan menginstal Git, bersama dengan Pip untuk menginstal paket Python.

    Salah satu fitur kuat Python adalah kemampuan untuk menginstal [paket Pip](https://pypi.org) - ini adalah paket kode yang ditulis oleh orang lain dan dipublikasikan di Internet. Anda dapat menginstal paket Pip ke komputer Anda dengan satu perintah, lalu menggunakan paket tersebut dalam kode Anda.

    Pustaka Python Seeed Grove perlu diinstal dari sumber. Perintah ini akan mengkloning repositori yang berisi kode sumber untuk paket ini, lalu menginstalnya secara lokal.

    > 💁 Secara default, ketika Anda menginstal paket, paket tersebut tersedia di seluruh komputer Anda, dan ini dapat menyebabkan masalah dengan versi paket - seperti satu aplikasi bergantung pada satu versi paket yang rusak ketika Anda menginstal versi baru untuk aplikasi lain. Untuk mengatasi masalah ini, Anda dapat menggunakan [lingkungan virtual Python](https://docs.python.org/3/library/venv.html), yang pada dasarnya adalah salinan Python di folder khusus, dan ketika Anda menginstal paket Pip, paket tersebut hanya diinstal di folder tersebut. Anda tidak akan menggunakan lingkungan virtual saat menggunakan Pi Anda. Skrip instalasi Grove menginstal pustaka Python Grove secara global, jadi untuk menggunakan lingkungan virtual, Anda perlu menyiapkan lingkungan virtual lalu menginstal ulang pustaka Grove secara manual di dalam lingkungan tersebut. Lebih mudah menggunakan paket global, terutama karena banyak pengembang Pi akan mem-flash ulang kartu SD bersih untuk setiap proyek.

    Akhirnya, ini mengaktifkan antarmuka I<sup>2</sup>C.

1. Reboot Pi menggunakan menu atau jalankan perintah berikut di Terminal:

    ```sh
    sudo reboot
    ```

1. Setelah Pi reboot, buka kembali Terminal dan jalankan perintah berikut untuk menginstal [Visual Studio Code (VS Code)](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) - ini adalah editor yang akan Anda gunakan untuk menulis kode perangkat Anda dalam Python.

    ```sh
    sudo apt install code
    ```

    Setelah diinstal, VS Code akan tersedia dari bilah menu atas.

    > 💁 Anda bebas menggunakan IDE atau editor Python apa pun untuk pelajaran ini jika Anda memiliki alat yang disukai, tetapi instruksi dalam pelajaran akan didasarkan pada penggunaan VS Code.

1. Instal Pylance. Ini adalah ekstensi untuk VS Code yang menyediakan dukungan bahasa Python. Lihat [dokumentasi ekstensi Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) untuk instruksi tentang cara menginstal ekstensi ini di VS Code.

### Akses jarak jauh untuk memprogram Pi

Daripada memprogram langsung di Pi, Anda dapat menjalankannya dalam mode 'headless', yaitu tidak terhubung ke keyboard/mouse/monitor, dan mengonfigurasi serta memprogramnya dari komputer Anda menggunakan Visual Studio Code.

#### Siapkan Pi OS

Untuk memprogram secara jarak jauh, Pi OS perlu diinstal pada kartu SD.

##### Tugas - Siapkan Pi OS

Siapkan Pi OS dalam mode headless.

1. Unduh **Raspberry Pi Imager** dari [halaman perangkat lunak Raspberry Pi OS](https://www.raspberrypi.org/software/) dan instal.

1. Masukkan kartu SD ke komputer Anda, gunakan adaptor jika diperlukan.

1. Jalankan Raspberry Pi Imager.

1. Dari Raspberry Pi Imager, pilih tombol **CHOOSE OS**, lalu pilih *Raspberry Pi OS (Other)*, diikuti dengan *Raspberry Pi OS Lite (32-bit)*.

    ![Raspberry Pi Imager dengan Raspberry Pi OS Lite dipilih](../../../../../translated_images/raspberry-pi-imager.24aedeab9e233d84.id.png)

    > 💁 Raspberry Pi OS Lite adalah versi Raspberry Pi OS yang tidak memiliki antarmuka pengguna desktop atau alat berbasis UI. Ini tidak diperlukan untuk Pi headless dan membuat instalasi lebih kecil serta waktu boot lebih cepat.

1. Pilih tombol **CHOOSE STORAGE**, lalu pilih kartu SD Anda.

1. Buka **Advanced Options** dengan menekan `Ctrl+Shift+X`. Opsi ini memungkinkan beberapa konfigurasi awal Raspberry Pi OS sebelum diinstal ke kartu SD.

    1. Centang kotak **Enable SSH**, dan atur kata sandi untuk pengguna `pi`. Ini adalah kata sandi yang akan Anda gunakan untuk masuk ke Pi nanti.

    1. Jika Anda berencana untuk menghubungkan ke Pi melalui WiFi, centang kotak **Configure WiFi**, dan masukkan SSID dan kata sandi WiFi Anda, serta pilih negara WiFi Anda. Anda tidak perlu melakukan ini jika akan menggunakan kabel ethernet. Pastikan jaringan yang Anda hubungkan sama dengan jaringan komputer Anda.

    1. Centang kotak **Set locale settings**, dan atur negara serta zona waktu Anda.

    1. Pilih tombol **SAVE**.

1. Pilih tombol **WRITE** untuk menulis OS ke kartu SD. Jika Anda menggunakan macOS, Anda akan diminta memasukkan kata sandi karena alat yang menulis gambar disk memerlukan akses istimewa.

OS akan ditulis ke kartu SD, dan setelah selesai, kartu akan dikeluarkan oleh OS, dan Anda akan diberi tahu. Lepaskan kartu SD dari komputer Anda, masukkan ke Pi, nyalakan Pi, dan tunggu sekitar 2 menit agar boot dengan benar.

#### Hubungkan ke Pi

Langkah berikutnya adalah mengakses Pi secara jarak jauh. Anda dapat melakukannya menggunakan `ssh`, yang tersedia di macOS, Linux, dan versi terbaru Windows.

##### Tugas - Hubungkan ke Pi

Akses Pi secara jarak jauh.

1. Buka Terminal atau Command Prompt, dan masukkan perintah berikut untuk terhubung ke Pi:

    ```sh
    ssh pi@raspberrypi.local
    ```

    Jika Anda menggunakan Windows versi lama yang tidak memiliki `ssh` terinstal, Anda dapat menggunakan OpenSSH. Anda dapat menemukan instruksi instalasi di [dokumentasi instalasi OpenSSH](https://docs.microsoft.com//windows-server/administration/openssh/openssh_install_firstuse?WT.mc_id=academic-17441-jabenn).

1. Ini akan menghubungkan Anda ke Pi dan meminta kata sandi.

    Kemampuan untuk menemukan komputer di jaringan Anda menggunakan `<hostname>.local` adalah tambahan yang cukup baru untuk Linux dan Windows. Jika Anda menggunakan Linux atau Windows dan mendapatkan kesalahan tentang Hostname yang tidak ditemukan, Anda perlu menginstal perangkat lunak tambahan untuk mengaktifkan jaringan ZeroConf (juga disebut oleh Apple sebagai Bonjour):

    1. Jika Anda menggunakan Linux, instal Avahi menggunakan perintah berikut:

        ```sh
        sudo apt-get install avahi-daemon
        ```

    1. Jika Anda menggunakan Windows, cara termudah untuk mengaktifkan ZeroConf adalah dengan menginstal [Bonjour Print Services for Windows](http://support.apple.com/kb/DL999). Anda juga dapat menginstal [iTunes for Windows](https://www.apple.com/itunes/download/) untuk mendapatkan versi utilitas yang lebih baru (yang tidak tersedia secara terpisah).

    > 💁 Jika Anda tidak dapat terhubung menggunakan `raspberrypi.local`, maka Anda dapat menggunakan alamat IP Pi Anda. Lihat [dokumentasi alamat IP Raspberry Pi](https://www.raspberrypi.org/documentation/remote-access/ip-address.md) untuk instruksi tentang beberapa cara mendapatkan alamat IP.

1. Masukkan kata sandi yang Anda atur di Advanced Options Raspberry Pi Imager.

#### Konfigurasikan perangkat lunak di Pi

Setelah Anda terhubung ke Pi, Anda perlu memastikan OS sudah diperbarui, dan menginstal berbagai pustaka serta alat yang berinteraksi dengan perangkat keras Grove.

##### Tugas - Konfigurasikan perangkat lunak di Pi

Konfigurasikan perangkat lunak Pi yang diinstal dan instal pustaka Grove.

1. Dari sesi `ssh` Anda, jalankan perintah berikut untuk memperbarui lalu reboot Pi:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes && sudo reboot
    ```

    Pi akan diperbarui dan reboot. Sesi `ssh` akan berakhir saat Pi reboot, jadi tunggu sekitar 30 detik lalu sambungkan kembali.

1. Dari sesi `ssh` yang tersambung kembali, jalankan perintah berikut untuk menginstal semua pustaka yang diperlukan untuk perangkat keras Grove:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Ini dimulai dengan menginstal Git, bersama dengan Pip untuk menginstal paket Python.

    Salah satu fitur kuat Python adalah kemampuan untuk menginstal [paket Pip](https://pypi.org) - ini adalah paket kode yang ditulis oleh orang lain dan dipublikasikan di Internet. Anda dapat menginstal paket Pip ke komputer Anda dengan satu perintah, lalu menggunakan paket tersebut dalam kode Anda.

    Pustaka Python Seeed Grove perlu diinstal dari sumber. Perintah ini akan mengkloning repositori yang berisi kode sumber untuk paket ini, lalu menginstalnya secara lokal.

    > 💁 Secara default, ketika Anda menginstal paket, paket tersebut tersedia di seluruh komputer Anda, dan ini dapat menyebabkan masalah dengan versi paket - seperti satu aplikasi bergantung pada satu versi paket yang rusak ketika Anda menginstal versi baru untuk aplikasi lain. Untuk mengatasi masalah ini, Anda dapat menggunakan [lingkungan virtual Python](https://docs.python.org/3/library/venv.html), yang pada dasarnya adalah salinan Python di folder khusus, dan ketika Anda menginstal paket Pip, paket tersebut hanya diinstal di folder tersebut. Anda tidak akan menggunakan lingkungan virtual saat menggunakan Pi Anda. Skrip instalasi Grove menginstal pustaka Python Grove secara global, jadi untuk menggunakan lingkungan virtual, Anda perlu menyiapkan lingkungan virtual lalu menginstal ulang pustaka Grove secara manual di dalam lingkungan tersebut. Lebih mudah menggunakan paket global, terutama karena banyak pengembang Pi akan mem-flash ulang kartu SD bersih untuk setiap proyek.

    Akhirnya, ini mengaktifkan antarmuka I<sup>2</sup>C.

1. Reboot Pi dengan menjalankan perintah berikut:

    ```sh
    sudo reboot
    ```

    Sesi `ssh` akan berakhir saat Pi reboot. Tidak perlu menyambungkan kembali.

#### Konfigurasikan VS Code untuk akses jarak jauh

Setelah Pi dikonfigurasi, Anda dapat menghubungkannya menggunakan Visual Studio Code (VS Code) dari komputer Anda - ini adalah editor teks pengembang gratis yang akan Anda gunakan untuk menulis kode perangkat Anda dalam Python.

##### Tugas - Konfigurasikan VS Code untuk akses jarak jauh

Instal perangkat lunak yang diperlukan dan sambungkan secara jarak jauh ke Pi Anda.

1. Instal VS Code di komputer Anda dengan mengikuti [dokumentasi VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

1. Ikuti instruksi dalam [dokumentasi pengembangan jarak jauh VS Code menggunakan SSH](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) untuk menginstal komponen yang diperlukan.

1. Mengikuti instruksi yang sama, sambungkan VS Code ke Pi.

1. Setelah tersambung, ikuti instruksi [mengelola ekstensi](https://code.visualstudio.com/docs/remote/ssh#_managing-extensions?WT.mc_id=academic-17441-jabenn) untuk menginstal [ekstensi Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) secara jarak jauh ke Pi.

## Hello world
Adalah hal yang umum ketika memulai dengan bahasa pemrograman atau teknologi baru untuk membuat aplikasi 'Hello World' - sebuah aplikasi kecil yang menampilkan teks seperti `"Hello World"` untuk memastikan bahwa semua alat telah dikonfigurasi dengan benar.

Aplikasi Hello World untuk Pi akan memastikan bahwa Python dan Visual Studio Code telah terinstal dengan benar.

Aplikasi ini akan berada di dalam folder bernama `nightlight`, dan akan digunakan kembali dengan kode yang berbeda di bagian-bagian selanjutnya dari tugas ini untuk membangun aplikasi nightlight.

### Tugas - hello world

Buat aplikasi Hello World.

1. Buka VS Code, baik langsung di Pi, atau di komputer Anda dan terhubung ke Pi menggunakan ekstensi Remote SSH.

1. Buka Terminal VS Code dengan memilih *Terminal -> New Terminal*, atau menekan `` CTRL+` ``. Terminal akan terbuka di direktori home pengguna `pi`.

1. Jalankan perintah berikut untuk membuat direktori untuk kode Anda, dan buat file Python bernama `app.py` di dalam direktori tersebut:

    ```sh
    mkdir nightlight
    cd nightlight
    touch app.py
    ```

1. Buka folder ini di VS Code dengan memilih *File -> Open...* dan memilih folder *nightlight*, lalu pilih **OK**.

    ![Dialog buka file di VS Code yang menunjukkan folder nightlight](../../../../../translated_images/vscode-open-nightlight-remote.d3d2a4011e30d535.id.png)

1. Buka file `app.py` dari penjelajah VS Code dan tambahkan kode berikut:

    ```python
    print('Hello World!')
    ```

    Fungsi `print` mencetak apa pun yang diberikan kepadanya ke konsol.

1. Dari Terminal VS Code, jalankan perintah berikut untuk menjalankan aplikasi Python Anda:

    ```sh
    python app.py
    ```

    > 💁 Anda mungkin perlu secara eksplisit memanggil `python3` untuk menjalankan kode ini jika Anda memiliki Python 2 yang terinstal selain Python 3 (versi terbaru). Jika Anda memiliki Python 2 yang terinstal, maka memanggil `python` akan menggunakan Python 2, bukan Python 3. Secara default, versi terbaru Raspberry Pi OS hanya memiliki Python 3 yang terinstal.

    Output berikut akan muncul di terminal:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py
    Hello World!
    ```

> 💁 Anda dapat menemukan kode ini di folder [code/pi](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/pi).

😀 Program 'Hello World' Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.