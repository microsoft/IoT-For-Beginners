<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a4f0c166010e31fd7b6ca20bc88dec6d",
  "translation_date": "2025-08-27T22:46:47+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md",
  "language_code": "id"
}
-->
# Wio Terminal

[Wio Terminal dari Seeed Studios](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) adalah mikrokontroler yang kompatibel dengan Arduino, dilengkapi dengan WiFi serta beberapa sensor dan aktuator bawaan, serta port untuk menambahkan lebih banyak sensor dan aktuator menggunakan ekosistem perangkat keras yang disebut [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html).

![Wio Terminal dari Seeed Studios](../../../../../translated_images/wio-terminal.b8299ee16587db9a.id.png)

## Persiapan

Untuk menggunakan Wio Terminal Anda, Anda perlu menginstal beberapa perangkat lunak gratis di komputer Anda. Anda juga perlu memperbarui firmware Wio Terminal sebelum dapat menghubungkannya ke WiFi.

### Tugas - Persiapan

Instal perangkat lunak yang diperlukan dan perbarui firmware.

1. Instal Visual Studio Code (VS Code). Ini adalah editor yang akan Anda gunakan untuk menulis kode perangkat Anda dalam C/C++. Lihat [dokumentasi VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) untuk petunjuk tentang cara menginstal VS Code.

    > 💁 IDE populer lainnya untuk pengembangan Arduino adalah [Arduino IDE](https://www.arduino.cc/en/software). Jika Anda sudah terbiasa dengan alat ini, Anda dapat menggunakannya sebagai pengganti VS Code dan PlatformIO, tetapi pelajaran ini akan memberikan instruksi berdasarkan penggunaan VS Code.

1. Instal ekstensi PlatformIO untuk VS Code. Ini adalah ekstensi untuk VS Code yang mendukung pemrograman mikrokontroler dalam C/C++. Lihat [dokumentasi ekstensi PlatformIO](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=platformio.platformio-ide) untuk petunjuk tentang cara menginstal ekstensi ini di VS Code. Ekstensi ini bergantung pada ekstensi Microsoft C/C++ untuk bekerja dengan kode C dan C++, dan ekstensi C/C++ akan diinstal secara otomatis saat Anda menginstal PlatformIO.

1. Hubungkan Wio Terminal Anda ke komputer. Wio Terminal memiliki port USB-C di bagian bawah, yang perlu dihubungkan ke port USB di komputer Anda. Wio Terminal dilengkapi dengan kabel USB-C ke USB-A, tetapi jika komputer Anda hanya memiliki port USB-C, Anda akan memerlukan kabel USB-C atau adaptor USB-A ke USB-C.

1. Ikuti petunjuk di [dokumentasi Wio Terminal Wiki WiFi Overview](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/) untuk menyiapkan Wio Terminal Anda dan memperbarui firmware.

## Hello World

Tradisi saat memulai dengan bahasa pemrograman atau teknologi baru adalah membuat aplikasi 'Hello World' - aplikasi kecil yang menampilkan teks seperti `"Hello World"` untuk memastikan semua alat telah dikonfigurasi dengan benar.

Aplikasi Hello World untuk Wio Terminal akan memastikan bahwa Anda telah menginstal Visual Studio Code dengan benar bersama PlatformIO dan siap untuk pengembangan mikrokontroler.

### Membuat Proyek PlatformIO

Langkah pertama adalah membuat proyek baru menggunakan PlatformIO yang dikonfigurasi untuk Wio Terminal.

#### Tugas - Membuat Proyek PlatformIO

Buat proyek PlatformIO.

1. Hubungkan Wio Terminal ke komputer Anda.

1. Buka VS Code.

1. Ikon PlatformIO akan muncul di bilah menu samping:

    ![Opsi menu Platform IO](../../../../../translated_images/vscode-platformio-menu.297be26b9733e5c4.id.png)

    Pilih item menu ini, lalu pilih *PIO Home -> Open*.

    ![Opsi buka Platform IO](../../../../../translated_images/vscode-platformio-home-open.3f9a41bfd3f4da1c.id.png)

1. Dari layar selamat datang, pilih tombol **+ New Project**.

    ![Tombol proyek baru](../../../../../translated_images/vscode-platformio-welcome-new-button.ba6fc8a4c7b78cc8.id.png)

1. Konfigurasikan proyek di *Project Wizard*:

    1. Beri nama proyek Anda `nightlight`.

    1. Dari dropdown *Board*, ketik `WIO` untuk memfilter papan, lalu pilih *Seeeduino Wio Terminal*.

    1. Biarkan *Framework* sebagai *Arduino*.

    1. Biarkan kotak centang *Use default location* tetap dicentang, atau hapus centang dan pilih lokasi untuk proyek Anda.

    1. Pilih tombol **Finish**.

    ![Wizard proyek yang telah selesai](../../../../../translated_images/vscode-platformio-nightlight-project-wizard.5c64db4da6037420.id.png)

    PlatformIO akan mengunduh komponen yang dibutuhkan untuk mengompilasi kode untuk Wio Terminal dan membuat proyek Anda. Proses ini mungkin memakan waktu beberapa menit.

### Menyelidiki Proyek PlatformIO

Penjelajah VS Code akan menampilkan sejumlah file dan folder yang dibuat oleh wizard PlatformIO.

#### Folder

* `.pio` - folder ini berisi data sementara yang dibutuhkan oleh PlatformIO seperti pustaka atau kode yang telah dikompilasi. Folder ini akan dibuat ulang secara otomatis jika dihapus, dan Anda tidak perlu menambahkannya ke kontrol kode sumber jika Anda membagikan proyek Anda di situs seperti GitHub.
* `.vscode` - folder ini berisi konfigurasi yang digunakan oleh PlatformIO dan VS Code. Folder ini akan dibuat ulang secara otomatis jika dihapus, dan Anda tidak perlu menambahkannya ke kontrol kode sumber jika Anda membagikan proyek Anda di situs seperti GitHub.
* `include` - folder ini untuk file header eksternal yang dibutuhkan saat menambahkan pustaka tambahan ke kode Anda. Anda tidak akan menggunakan folder ini dalam pelajaran ini.
* `lib` - folder ini untuk pustaka eksternal yang ingin Anda panggil dari kode Anda. Anda tidak akan menggunakan folder ini dalam pelajaran ini.
* `src` - folder ini berisi kode sumber utama untuk aplikasi Anda. Awalnya, folder ini hanya akan berisi satu file - `main.cpp`.
* `test` - folder ini adalah tempat Anda akan meletakkan pengujian unit untuk kode Anda.

#### File

* `main.cpp` - file ini berada di folder `src` dan berisi titik masuk untuk aplikasi Anda. Buka file ini, dan akan berisi kode berikut:

    ```cpp
    #include <Arduino.h>
    
    void setup() {
      // put your setup code here, to run once:
    }
    
    void loop() {
      // put your main code here, to run repeatedly:
    }
    ```

    Ketika perangkat dinyalakan, kerangka kerja Arduino akan menjalankan fungsi `setup` sekali, lalu menjalankan fungsi `loop` berulang kali hingga perangkat dimatikan.

* `.gitignore` - file ini mencantumkan file dan direktori yang diabaikan saat menambahkan kode Anda ke kontrol sumber git, seperti mengunggah ke repositori di GitHub.

* `platformio.ini` - file ini berisi konfigurasi untuk perangkat dan aplikasi Anda. Buka file ini, dan akan berisi kode berikut:

    ```ini
    [env:seeed_wio_terminal]
    platform = atmelsam
    board = seeed_wio_terminal
    framework = arduino
    ```

    Bagian `[env:seeed_wio_terminal]` memiliki konfigurasi untuk Wio Terminal. Anda dapat memiliki beberapa bagian `env` sehingga kode Anda dapat dikompilasi untuk beberapa papan.

    Nilai lainnya sesuai dengan konfigurasi dari wizard proyek:

  * `platform = atmelsam` mendefinisikan perangkat keras yang digunakan oleh Wio Terminal (mikrokontroler berbasis ATSAMD51).
  * `board = seeed_wio_terminal` mendefinisikan jenis papan mikrokontroler (Wio Terminal).
  * `framework = arduino` mendefinisikan bahwa proyek ini menggunakan kerangka kerja Arduino.

### Menulis Aplikasi Hello World

Sekarang Anda siap untuk menulis aplikasi Hello World.

#### Tugas - Menulis Aplikasi Hello World

Tulis aplikasi Hello World.

1. Buka file `main.cpp` di VS Code.

1. Ubah kode agar sesuai dengan berikut ini:

    ```cpp
    #include <Arduino.h>

    void setup()
    {
        Serial.begin(9600);

        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    
    void loop()
    {
        Serial.println("Hello World");
        delay(5000);
    }
    ```

    Fungsi `setup` menginisialisasi koneksi ke port serial - dalam hal ini, port USB yang digunakan untuk menghubungkan Wio Terminal ke komputer Anda. Parameter `9600` adalah [baud rate](https://wikipedia.org/wiki/Symbol_rate) (juga dikenal sebagai Symbol rate), atau kecepatan data yang akan dikirim melalui port serial dalam bit per detik. Pengaturan ini berarti 9.600 bit (0 dan 1) data dikirim setiap detik. Kemudian menunggu port serial siap.

    Fungsi `loop` mengirimkan baris `Hello World!` ke port serial, sehingga karakter `Hello World!` bersama dengan karakter baris baru. Kemudian tidur selama 5.000 milidetik atau 5 detik. Setelah `loop` selesai, fungsi ini dijalankan lagi, dan lagi, dan seterusnya selama mikrokontroler menyala.

1. Masukkan Wio Terminal Anda ke mode upload. Anda perlu melakukan ini setiap kali mengunggah kode baru ke perangkat:

    1. Tarik ke bawah dua kali dengan cepat pada sakelar daya - sakelar akan kembali ke posisi on setiap kali.

    1. Periksa LED status biru di sisi kanan port USB. LED harus berkedip perlahan.
    
    [![Video cara memasukkan Wio Terminal ke mode upload](https://img.youtube.com/vi/LeKU_7zLRrQ/0.jpg)](https://youtu.be/LeKU_7zLRrQ)
    
    Klik gambar di atas untuk melihat video cara melakukannya.

1. Bangun dan unggah kode ke Wio Terminal.

    1. Buka palet perintah VS Code.

    1. Ketik `PlatformIO Upload` untuk mencari opsi upload, lalu pilih *PlatformIO: Upload*.

        ![Opsi upload PlatformIO di palet perintah](../../../../../translated_images/vscode-platformio-upload-command-palette.9e0f49cf80d1f1c3.id.png)

        PlatformIO akan secara otomatis membangun kode jika diperlukan sebelum mengunggah.

    1. Kode akan dikompilasi dan diunggah ke Wio Terminal.

        > 💁 Jika Anda menggunakan macOS, notifikasi tentang *DISK NOT EJECTED PROPERLY* akan muncul. Ini terjadi karena Wio Terminal dipasang sebagai drive selama proses flashing, dan terputus saat kode yang dikompilasi ditulis ke perangkat. Anda dapat mengabaikan notifikasi ini.

    ⚠️ Jika Anda mendapatkan kesalahan tentang port upload yang tidak tersedia, pertama pastikan Wio Terminal Anda terhubung ke komputer, dinyalakan menggunakan sakelar di sisi kiri layar, dan diatur ke mode upload. Lampu hijau di bagian bawah harus menyala, dan lampu biru harus berkedip perlahan. Jika Anda masih mendapatkan kesalahan, tarik sakelar on/off ke bawah dua kali dengan cepat lagi untuk memaksa Wio Terminal ke mode upload dan coba unggah lagi.

PlatformIO memiliki Serial Monitor yang dapat memantau data yang dikirim melalui kabel USB dari Wio Terminal. Ini memungkinkan Anda memantau data yang dikirim oleh perintah `Serial.println("Hello World");`.

1. Buka palet perintah VS Code.

1. Ketik `PlatformIO Serial` untuk mencari opsi Serial Monitor, lalu pilih *PlatformIO: Serial Monitor*.

    ![Opsi Serial Monitor PlatformIO di palet perintah](../../../../../translated_images/vscode-platformio-serial-monitor-command-palette.b348ec841b8a1c14.id.png)

    Terminal baru akan terbuka, dan data yang dikirim melalui port serial akan ditampilkan di terminal ini:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Hello World
    Hello World
    ```

    `Hello World` akan dicetak ke serial monitor setiap 5 detik.

> 💁 Anda dapat menemukan kode ini di folder [code/wio-terminal](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/wio-terminal).

😀 Program 'Hello World' Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.