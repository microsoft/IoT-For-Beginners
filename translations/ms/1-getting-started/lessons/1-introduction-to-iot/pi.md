<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "8ff0d0a1d29832bb896b9c103b69a452",
  "translation_date": "2025-08-27T22:44:48+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/pi.md",
  "language_code": "ms"
}
-->
# Raspberry Pi

[Raspberry Pi](https://raspberrypi.org) adalah komputer papan tunggal. Anda boleh menambah sensor dan aktuator menggunakan pelbagai jenis peranti dan ekosistem, dan untuk pelajaran ini, kita akan menggunakan ekosistem perkakasan yang dipanggil [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html). Anda akan menulis kod untuk Pi anda dan mengakses sensor Grove menggunakan Python.

![Raspberry Pi 4](../../../../../translated_images/ms/raspberry-pi-4.fd4590d308c3d456.webp)

## Persediaan

Jika anda menggunakan Raspberry Pi sebagai perkakasan IoT anda, terdapat dua pilihan - anda boleh mengikuti semua pelajaran ini dan menulis kod secara langsung pada Pi, atau anda boleh menyambung secara jauh ke Pi 'headless' dan menulis kod dari komputer anda.

Sebelum memulakan, anda juga perlu menyambungkan Grove Base Hat ke Pi anda.

### Tugasan - persediaan

Pasang Grove Base Hat pada Pi anda dan konfigurasikan Pi.

1. Sambungkan Grove Base Hat ke Pi anda. Soket pada hat ini sesuai dengan semua pin GPIO pada Pi, meluncur sepenuhnya ke bawah pin untuk duduk dengan kukuh pada dasar. Ia akan menutupi Pi.

    ![Memasang grove hat](../../../../../images/pi-grove-hat-fitting.gif)

1. Tentukan cara anda ingin memprogram Pi anda, dan pergi ke bahagian yang berkaitan di bawah:

    * [Kerja secara langsung pada Pi anda](../../../../../1-getting-started/lessons/1-introduction-to-iot)
    * [Akses jauh untuk menulis kod pada Pi](../../../../../1-getting-started/lessons/1-introduction-to-iot)

### Kerja secara langsung pada Pi anda

Jika anda ingin bekerja secara langsung pada Pi anda, anda boleh menggunakan versi desktop Raspberry Pi OS dan memasang semua alat yang diperlukan.

#### Tugasan - kerja secara langsung pada Pi anda

Sediakan Pi anda untuk pembangunan.

1. Ikuti arahan dalam [panduan persediaan Raspberry Pi](https://projects.raspberrypi.org/en/projects/raspberry-pi-setting-up) untuk menyediakan Pi anda, menyambungkannya ke papan kekunci/tetikus/monitor, menyambungkannya ke rangkaian WiFi atau ethernet, dan mengemas kini perisian.

Untuk memprogram Pi menggunakan sensor dan aktuator Grove, anda perlu memasang editor untuk menulis kod peranti, serta pelbagai perpustakaan dan alat yang berinteraksi dengan perkakasan Grove.

1. Setelah Pi anda dihidupkan semula, lancarkan Terminal dengan mengklik ikon **Terminal** pada bar menu atas, atau pilih *Menu -> Accessories -> Terminal*

1. Jalankan arahan berikut untuk memastikan OS dan perisian yang dipasang adalah terkini:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes
    ```

1. Jalankan arahan berikut untuk memasang semua perpustakaan yang diperlukan untuk perkakasan Grove:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Ini bermula dengan memasang Git, bersama dengan Pip untuk memasang pakej Python.

    Salah satu ciri hebat Python adalah keupayaan untuk memasang [Pip packages](https://pypi.org) - ini adalah pakej kod yang ditulis oleh orang lain dan diterbitkan di Internet. Anda boleh memasang pakej Pip ke komputer anda dengan satu arahan, kemudian menggunakan pakej tersebut dalam kod anda.

    Pakej Python Grove dari Seeed perlu dipasang dari sumber. Arahan ini akan mengklon repo yang mengandungi kod sumber untuk pakej ini, kemudian memasangnya secara tempatan.

    > 💁 Secara lalai, apabila anda memasang pakej, ia tersedia di mana-mana sahaja pada komputer anda, dan ini boleh menyebabkan masalah dengan versi pakej - seperti satu aplikasi bergantung pada satu versi pakej yang rosak apabila anda memasang versi baru untuk aplikasi lain. Untuk mengatasi masalah ini, anda boleh menggunakan [Python virtual environment](https://docs.python.org/3/library/venv.html), iaitu salinan Python dalam folder khusus, dan apabila anda memasang pakej Pip, ia hanya dipasang ke folder tersebut. Anda tidak akan menggunakan virtual environment semasa menggunakan Pi anda. Skrip pemasangan Grove memasang pakej Python Grove secara global, jadi untuk menggunakan virtual environment, anda perlu menyediakan virtual environment kemudian memasang semula pakej Grove secara manual di dalam environment tersebut. Lebih mudah untuk hanya menggunakan pakej global, terutamanya kerana ramai pembangun Pi akan mem-flash kad SD baru untuk setiap projek.

    Akhirnya, ini mengaktifkan antara muka I<sup>2</sup>C.

1. Hidupkan semula Pi sama ada menggunakan menu atau menjalankan arahan berikut dalam Terminal:

    ```sh
    sudo reboot
    ```

1. Setelah Pi dihidupkan semula, lancarkan semula Terminal dan jalankan arahan berikut untuk memasang [Visual Studio Code (VS Code)](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) - ini adalah editor yang akan anda gunakan untuk menulis kod peranti anda dalam Python.

    ```sh
    sudo apt install code
    ```

    Setelah dipasang, VS Code akan tersedia dari menu atas.

    > 💁 Anda bebas menggunakan mana-mana IDE atau editor Python untuk pelajaran ini jika anda mempunyai alat pilihan, tetapi pelajaran ini akan memberikan arahan berdasarkan penggunaan VS Code.

1. Pasang Pylance. Ini adalah sambungan untuk VS Code yang menyediakan sokongan bahasa Python. Rujuk [dokumentasi sambungan Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) untuk arahan memasang sambungan ini dalam VS Code.

### Akses jauh untuk menulis kod pada Pi

Daripada menulis kod secara langsung pada Pi, ia boleh dijalankan dalam mod 'headless', iaitu tidak disambungkan ke papan kekunci/tetikus/monitor, dan anda boleh mengkonfigurasi serta menulis kod padanya dari komputer anda menggunakan Visual Studio Code.

#### Sediakan Pi OS

Untuk menulis kod secara jauh, Pi OS perlu dipasang pada kad SD.

##### Tugasan - sediakan Pi OS

Sediakan Pi OS dalam mod headless.

1. Muat turun **Raspberry Pi Imager** dari [halaman perisian Raspberry Pi OS](https://www.raspberrypi.org/software/) dan pasangkannya.

1. Masukkan kad SD ke komputer anda, menggunakan penyesuai jika perlu.

1. Lancarkan Raspberry Pi Imager.

1. Dari Raspberry Pi Imager, pilih butang **CHOOSE OS**, kemudian pilih *Raspberry Pi OS (Other)*, diikuti oleh *Raspberry Pi OS Lite (32-bit)*.

    ![Raspberry Pi Imager dengan Raspberry Pi OS Lite dipilih](../../../../../translated_images/ms/raspberry-pi-imager.24aedeab9e233d84.webp)

    > 💁 Raspberry Pi OS Lite adalah versi Raspberry Pi OS yang tidak mempunyai UI desktop atau alat berasaskan UI. Ini tidak diperlukan untuk Pi dalam mod headless dan menjadikan pemasangan lebih kecil serta masa boot lebih cepat.

1. Pilih butang **CHOOSE STORAGE**, kemudian pilih kad SD anda.

1. Lancarkan **Advanced Options** dengan menekan `Ctrl+Shift+X`. Pilihan ini membolehkan beberapa pra-konfigurasi Raspberry Pi OS sebelum ia di-image ke kad SD.

    1. Tandakan kotak **Enable SSH**, dan tetapkan kata laluan untuk pengguna `pi`. Ini adalah kata laluan yang akan anda gunakan untuk log masuk ke Pi nanti.

    1. Jika anda merancang untuk menyambung ke Pi melalui WiFi, tandakan kotak **Configure WiFi**, dan masukkan SSID dan kata laluan WiFi anda, serta pilih negara WiFi anda. Anda tidak perlu melakukan ini jika anda akan menggunakan kabel ethernet. Pastikan rangkaian yang anda sambungkan adalah sama dengan rangkaian komputer anda.

    1. Tandakan kotak **Set locale settings**, dan tetapkan negara serta zon waktu anda.

    1. Pilih butang **SAVE**.

1. Pilih butang **WRITE** untuk menulis OS ke kad SD. Jika anda menggunakan macOS, anda akan diminta memasukkan kata laluan anda kerana alat asas yang menulis imej cakera memerlukan akses istimewa.

OS akan ditulis ke kad SD, dan setelah selesai, kad akan dikeluarkan oleh OS, dan anda akan diberitahu. Keluarkan kad SD dari komputer anda, masukkan ke dalam Pi, hidupkan Pi dan tunggu kira-kira 2 minit untuk ia boot sepenuhnya.

#### Sambung ke Pi

Langkah seterusnya adalah mengakses Pi secara jauh. Anda boleh melakukannya menggunakan `ssh`, yang tersedia pada macOS, Linux dan versi Windows terkini.

##### Tugasan - sambung ke Pi

Akses Pi secara jauh.

1. Lancarkan Terminal atau Command Prompt, dan masukkan arahan berikut untuk menyambung ke Pi:

    ```sh
    ssh pi@raspberrypi.local
    ```

    Jika anda menggunakan Windows versi lama yang tidak mempunyai `ssh` dipasang, anda boleh menggunakan OpenSSH. Anda boleh mencari arahan pemasangan dalam [dokumentasi pemasangan OpenSSH](https://docs.microsoft.com//windows-server/administration/openssh/openssh_install_firstuse?WT.mc_id=academic-17441-jabenn).

1. Ini sepatutnya menyambung ke Pi anda dan meminta kata laluan.

    Keupayaan untuk mencari komputer di rangkaian anda menggunakan `<hostname>.local` adalah tambahan yang agak baru untuk Linux dan Windows. Jika anda menggunakan Linux atau Windows dan mendapat sebarang ralat tentang Hostname tidak ditemui, anda perlu memasang perisian tambahan untuk membolehkan rangkaian ZeroConf (juga dirujuk oleh Apple sebagai Bonjour):

    1. Jika anda menggunakan Linux, pasang Avahi menggunakan arahan berikut:

        ```sh
        sudo apt-get install avahi-daemon
        ```

    1. Jika anda menggunakan Windows, cara paling mudah untuk membolehkan ZeroConf adalah dengan memasang [Bonjour Print Services for Windows](http://support.apple.com/kb/DL999). Anda juga boleh memasang [iTunes for Windows](https://www.apple.com/itunes/download/) untuk mendapatkan versi utiliti yang lebih baru (yang tidak tersedia secara berasingan).

    > 💁 Jika anda tidak dapat menyambung menggunakan `raspberrypi.local`, maka anda boleh menggunakan alamat IP Pi anda. Rujuk [dokumentasi alamat IP Raspberry Pi](https://www.raspberrypi.org/documentation/remote-access/ip-address.md) untuk arahan tentang beberapa cara mendapatkan alamat IP.

1. Masukkan kata laluan yang anda tetapkan dalam Advanced Options Raspberry Pi Imager.

#### Konfigurasi perisian pada Pi

Setelah anda disambungkan ke Pi, anda perlu memastikan OS adalah terkini, dan memasang pelbagai perpustakaan serta alat yang berinteraksi dengan perkakasan Grove.

##### Tugasan - konfigurasi perisian pada Pi

Konfigurasikan perisian Pi yang dipasang dan pasang perpustakaan Grove.

1. Dari sesi `ssh` anda, jalankan arahan berikut untuk mengemas kini kemudian reboot Pi:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes && sudo reboot
    ```

    Pi akan dikemas kini dan reboot. Sesi `ssh` akan berakhir apabila Pi reboot, jadi tunggu kira-kira 30 saat kemudian sambung semula.

1. Dari sesi `ssh` yang disambung semula, jalankan arahan berikut untuk memasang semua perpustakaan yang diperlukan untuk perkakasan Grove:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Ini bermula dengan memasang Git, bersama dengan Pip untuk memasang pakej Python.

    Salah satu ciri hebat Python adalah keupayaan untuk memasang [Pip packages](https://pypi.org) - ini adalah pakej kod yang ditulis oleh orang lain dan diterbitkan di Internet. Anda boleh memasang pakej Pip ke komputer anda dengan satu arahan, kemudian menggunakan pakej tersebut dalam kod anda.

    Pakej Python Grove dari Seeed perlu dipasang dari sumber. Arahan ini akan mengklon repo yang mengandungi kod sumber untuk pakej ini, kemudian memasangnya secara tempatan.

    > 💁 Secara lalai, apabila anda memasang pakej, ia tersedia di mana-mana sahaja pada komputer anda, dan ini boleh menyebabkan masalah dengan versi pakej - seperti satu aplikasi bergantung pada satu versi pakej yang rosak apabila anda memasang versi baru untuk aplikasi lain. Untuk mengatasi masalah ini, anda boleh menggunakan [Python virtual environment](https://docs.python.org/3/library/venv.html), iaitu salinan Python dalam folder khusus, dan apabila anda memasang pakej Pip, ia hanya dipasang ke folder tersebut. Anda tidak akan menggunakan virtual environment semasa menggunakan Pi anda. Skrip pemasangan Grove memasang pakej Python Grove secara global, jadi untuk menggunakan virtual environment, anda perlu menyediakan virtual environment kemudian memasang semula pakej Grove secara manual di dalam environment tersebut. Lebih mudah untuk hanya menggunakan pakej global, terutamanya kerana ramai pembangun Pi akan mem-flash kad SD baru untuk setiap projek.

    Akhirnya, ini mengaktifkan antara muka I<sup>2</sup>C.

1. Reboot Pi dengan menjalankan arahan berikut:

    ```sh
    sudo reboot
    ```

    Sesi `ssh` akan berakhir apabila Pi reboot. Tidak perlu menyambung semula.

#### Konfigurasi VS Code untuk akses jauh

Setelah Pi dikonfigurasi, anda boleh menyambung kepadanya menggunakan Visual Studio Code (VS Code) dari komputer anda - ini adalah editor teks pembangun percuma yang akan anda gunakan untuk menulis kod peranti anda dalam Python.

##### Tugasan - konfigurasi VS Code untuk akses jauh

Pasang perisian yang diperlukan dan sambung secara jauh ke Pi anda.

1. Pasang VS Code pada komputer anda dengan mengikuti [dokumentasi VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

1. Ikuti arahan dalam [dokumentasi Pembangunan Jauh VS Code menggunakan SSH](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) untuk memasang komponen yang diperlukan.

1. Mengikuti arahan yang sama, sambungkan VS Code ke Pi.

1. Setelah disambungkan, ikuti arahan [mengurus sambungan](https://code.visualstudio.com/docs/remote/ssh#_managing-extensions?WT.mc_id=academic-17441-jabenn) untuk memasang sambungan [Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) secara jauh ke Pi.

## Hello world
Adalah tradisi apabila memulakan dengan bahasa pengaturcaraan atau teknologi baru untuk mencipta aplikasi 'Hello World' - aplikasi kecil yang memaparkan teks seperti `"Hello World"` untuk menunjukkan bahawa semua alat telah dikonfigurasi dengan betul.

Aplikasi Hello World untuk Pi akan memastikan bahawa anda telah memasang Python dan Visual Studio Code dengan betul.

Aplikasi ini akan berada dalam folder bernama `nightlight`, dan ia akan digunakan semula dengan kod yang berbeza dalam bahagian tugasan ini untuk membina aplikasi nightlight.

### Tugasan - hello world

Cipta aplikasi Hello World.

1. Lancarkan VS Code, sama ada secara langsung pada Pi, atau pada komputer anda dan sambungkan ke Pi menggunakan sambungan Remote SSH.

1. Lancarkan Terminal VS Code dengan memilih *Terminal -> New Terminal*, atau menekan `` CTRL+` ``. Ia akan terbuka ke direktori home pengguna `pi`.

1. Jalankan arahan berikut untuk mencipta direktori untuk kod anda, dan cipta fail Python bernama `app.py` di dalam direktori tersebut:

    ```sh
    mkdir nightlight
    cd nightlight
    touch app.py
    ```

1. Buka folder ini dalam VS Code dengan memilih *File -> Open...* dan memilih folder *nightlight*, kemudian pilih **OK**.

    ![Dialog buka VS Code menunjukkan folder nightlight](../../../../../translated_images/ms/vscode-open-nightlight-remote.d3d2a4011e30d535.webp)

1. Buka fail `app.py` dari penjelajah VS Code dan tambahkan kod berikut:

    ```python
    print('Hello World!')
    ```

    Fungsi `print` akan mencetak apa sahaja yang dihantar kepadanya ke konsol.

1. Dari Terminal VS Code, jalankan arahan berikut untuk menjalankan aplikasi Python anda:

    ```sh
    python app.py
    ```

    > 💁 Anda mungkin perlu secara eksplisit memanggil `python3` untuk menjalankan kod ini jika anda mempunyai Python 2 yang dipasang selain Python 3 (versi terkini). Jika anda mempunyai Python 2 yang dipasang, maka memanggil `python` akan menggunakan Python 2 dan bukannya Python 3. Secara lalai, versi Raspberry Pi OS terkini hanya mempunyai Python 3 yang dipasang.

    Output berikut akan muncul di terminal:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py
    Hello World!
    ```

> 💁 Anda boleh menemui kod ini dalam folder [code/pi](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/pi).

😀 Program 'Hello World' anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.