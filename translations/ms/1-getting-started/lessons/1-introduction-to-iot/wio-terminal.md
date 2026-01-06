<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a4f0c166010e31fd7b6ca20bc88dec6d",
  "translation_date": "2025-08-27T22:47:13+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md",
  "language_code": "ms"
}
-->
# Wio Terminal

[Wio Terminal dari Seeed Studios](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) adalah mikrokontroler yang serasi dengan Arduino, dilengkapi dengan WiFi serta beberapa sensor dan aktuator terbina, serta port untuk menambah lebih banyak sensor dan aktuator menggunakan ekosistem perkakasan yang dipanggil [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html).

![Wio Terminal dari Seeed Studios](../../../../../translated_images/wio-terminal.b8299ee16587db9a.ms.png)

## Persediaan

Untuk menggunakan Wio Terminal anda, anda perlu memasang beberapa perisian percuma pada komputer anda. Anda juga perlu mengemas kini firmware Wio Terminal sebelum dapat menyambungkannya ke WiFi.

### Tugasan - persediaan

Pasang perisian yang diperlukan dan kemas kini firmware.

1. Pasang Visual Studio Code (VS Code). Ini adalah editor yang akan anda gunakan untuk menulis kod peranti anda dalam C/C++. Rujuk [dokumentasi VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) untuk arahan memasang VS Code.

    > 💁 IDE popular lain untuk pembangunan Arduino ialah [Arduino IDE](https://www.arduino.cc/en/software). Jika anda sudah biasa dengan alat ini, anda boleh menggunakannya sebagai ganti VS Code dan PlatformIO, tetapi pelajaran ini akan memberikan arahan berdasarkan penggunaan VS Code.

1. Pasang sambungan PlatformIO untuk VS Code. Ini adalah sambungan untuk VS Code yang menyokong pengaturcaraan mikrokontroler dalam C/C++. Rujuk [dokumentasi sambungan PlatformIO](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=platformio.platformio-ide) untuk arahan memasang sambungan ini dalam VS Code. Sambungan ini bergantung pada sambungan Microsoft C/C++ untuk bekerja dengan kod C dan C++, dan sambungan C/C++ akan dipasang secara automatik apabila anda memasang PlatformIO.

1. Sambungkan Wio Terminal anda ke komputer. Wio Terminal mempunyai port USB-C di bahagian bawah, dan ini perlu disambungkan ke port USB pada komputer anda. Wio Terminal disertakan dengan kabel USB-C ke USB-A, tetapi jika komputer anda hanya mempunyai port USB-C, anda perlu menggunakan kabel USB-C atau penyesuai USB-A ke USB-C.

1. Ikuti arahan dalam [dokumentasi Wio Terminal Wiki WiFi Overview](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/) untuk menyediakan Wio Terminal anda dan mengemas kini firmware.

## Hello World

Adalah tradisi apabila memulakan dengan bahasa pengaturcaraan atau teknologi baru untuk mencipta aplikasi 'Hello World' - aplikasi kecil yang mengeluarkan sesuatu seperti teks `"Hello World"` untuk menunjukkan bahawa semua alat telah dikonfigurasi dengan betul.

Aplikasi Hello World untuk Wio Terminal akan memastikan bahawa anda telah memasang Visual Studio Code dengan betul bersama PlatformIO dan disediakan untuk pembangunan mikrokontroler.

### Cipta projek PlatformIO

Langkah pertama adalah mencipta projek baru menggunakan PlatformIO yang dikonfigurasi untuk Wio Terminal.

#### Tugasan - cipta projek PlatformIO

Cipta projek PlatformIO.

1. Sambungkan Wio Terminal ke komputer anda

1. Lancarkan VS Code

1. Ikon PlatformIO akan berada di bar menu sisi:

    ![Pilihan menu PlatformIO](../../../../../translated_images/vscode-platformio-menu.297be26b9733e5c4.ms.png)

    Pilih item menu ini, kemudian pilih *PIO Home -> Open*

    ![Pilihan buka PlatformIO](../../../../../translated_images/vscode-platformio-home-open.3f9a41bfd3f4da1c.ms.png)

1. Dari skrin selamat datang, pilih butang **+ New Project**

    ![Butang projek baru](../../../../../translated_images/vscode-platformio-welcome-new-button.ba6fc8a4c7b78cc8.ms.png)

1. Konfigurasikan projek dalam *Project Wizard*:

    1. Namakan projek anda `nightlight`

    1. Dari dropdown *Board*, taipkan `WIO` untuk menapis papan, dan pilih *Seeeduino Wio Terminal*

    1. Biarkan *Framework* sebagai *Arduino*

    1. Sama ada biarkan kotak semak *Use default location* ditandai, atau nyah tanda dan pilih lokasi untuk projek anda

    1. Pilih butang **Finish**

    ![Wizard projek yang lengkap](../../../../../translated_images/vscode-platformio-nightlight-project-wizard.5c64db4da6037420.ms.png)

    PlatformIO akan memuat turun komponen yang diperlukan untuk menyusun kod untuk Wio Terminal dan mencipta projek anda. Ini mungkin mengambil masa beberapa minit.

### Selidiki projek PlatformIO

Penjelajah VS Code akan menunjukkan beberapa fail dan folder yang dicipta oleh wizard PlatformIO.

#### Folder

* `.pio` - folder ini mengandungi data sementara yang diperlukan oleh PlatformIO seperti perpustakaan atau kod yang disusun. Ia akan dicipta semula secara automatik jika dipadamkan, dan anda tidak perlu menambah ini ke kawalan kod sumber jika anda berkongsi projek anda di laman seperti GitHub.
* `.vscode` - folder ini mengandungi konfigurasi yang digunakan oleh PlatformIO dan VS Code. Ia akan dicipta semula secara automatik jika dipadamkan, dan anda tidak perlu menambah ini ke kawalan kod sumber jika anda berkongsi projek anda di laman seperti GitHub.
* `include` - folder ini adalah untuk fail header luaran yang diperlukan apabila menambah perpustakaan tambahan ke kod anda. Anda tidak akan menggunakan folder ini dalam mana-mana pelajaran ini.
* `lib` - folder ini adalah untuk perpustakaan luaran yang ingin anda panggil dari kod anda. Anda tidak akan menggunakan folder ini dalam mana-mana pelajaran ini.
* `src` - folder ini mengandungi kod sumber utama untuk aplikasi anda. Pada mulanya, ia akan mengandungi satu fail - `main.cpp`.
* `test` - folder ini adalah tempat anda meletakkan sebarang ujian unit untuk kod anda.

#### Fail

* `main.cpp` - fail ini dalam folder `src` mengandungi titik masuk untuk aplikasi anda. Buka fail ini, dan ia akan mengandungi kod berikut:

    ```cpp
    #include <Arduino.h>
    
    void setup() {
      // put your setup code here, to run once:
    }
    
    void loop() {
      // put your main code here, to run repeatedly:
    }
    ```

    Apabila peranti dimulakan, kerangka Arduino akan menjalankan fungsi `setup` sekali, kemudian menjalankan fungsi `loop` berulang kali sehingga peranti dimatikan.

* `.gitignore` - fail ini menyenaraikan fail dan direktori yang akan diabaikan apabila menambah kod anda ke kawalan kod git, seperti memuat naik ke repositori di GitHub.

* `platformio.ini` - fail ini mengandungi konfigurasi untuk peranti dan aplikasi anda. Buka fail ini, dan ia akan mengandungi kod berikut:

    ```ini
    [env:seeed_wio_terminal]
    platform = atmelsam
    board = seeed_wio_terminal
    framework = arduino
    ```

    Bahagian `[env:seeed_wio_terminal]` mempunyai konfigurasi untuk Wio Terminal. Anda boleh mempunyai beberapa bahagian `env` supaya kod anda boleh disusun untuk beberapa papan.

    Nilai lain sepadan dengan konfigurasi dari wizard projek:

  * `platform = atmelsam` mentakrifkan perkakasan yang digunakan oleh Wio Terminal (mikrokontroler berasaskan ATSAMD51)
  * `board = seeed_wio_terminal` mentakrifkan jenis papan mikrokontroler (Wio Terminal)
  * `framework = arduino` mentakrifkan bahawa projek ini menggunakan kerangka Arduino.

### Tulis aplikasi Hello World

Anda kini bersedia untuk menulis aplikasi Hello World.

#### Tugasan - tulis aplikasi Hello World

Tulis aplikasi Hello World.

1. Buka fail `main.cpp` dalam VS Code

1. Tukar kod untuk sepadan dengan berikut:

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

    Fungsi `setup` memulakan sambungan ke port serial - dalam kes ini, port USB yang digunakan untuk menyambungkan Wio Terminal ke komputer anda. Parameter `9600` adalah [baud rate](https://wikipedia.org/wiki/Symbol_rate) (juga dikenali sebagai kadar simbol), atau kelajuan data akan dihantar melalui port serial dalam bit sesaat. Tetapan ini bermaksud 9,600 bit (0s dan 1s) data dihantar setiap saat. Ia kemudian menunggu port serial untuk bersedia.

    Fungsi `loop` menghantar baris `Hello World!` ke port serial, jadi aksara `Hello World!` bersama dengan aksara baris baru. Ia kemudian tidur selama 5,000 milisaat atau 5 saat. Selepas `loop` berakhir, ia dijalankan semula, dan lagi, dan seterusnya sepanjang masa mikrokontroler dihidupkan.

1. Letakkan Wio Terminal anda dalam mod muat naik. Anda perlu melakukan ini setiap kali anda memuat naik kod baru ke peranti:

    1. Tarik turun dua kali dengan cepat pada suis kuasa - ia akan kembali ke posisi hidup setiap kali.

    1. Periksa LED status biru di sebelah kanan port USB. Ia sepatutnya berdenyut.
    
    [![Video menunjukkan cara meletakkan Wio Terminal dalam mod muat naik](https://img.youtube.com/vi/LeKU_7zLRrQ/0.jpg)](https://youtu.be/LeKU_7zLRrQ)
    
    Klik imej di atas untuk video menunjukkan cara melakukannya.

1. Bina dan muat naik kod ke Wio Terminal

    1. Buka palet arahan VS Code

    1. Taip `PlatformIO Upload` untuk mencari pilihan muat naik, dan pilih *PlatformIO: Upload*

        ![Pilihan muat naik PlatformIO dalam palet arahan](../../../../../translated_images/vscode-platformio-upload-command-palette.9e0f49cf80d1f1c3.ms.png)

        PlatformIO akan secara automatik membina kod jika diperlukan sebelum memuat naik.

    1. Kod akan disusun dan dimuat naik ke Wio Terminal

        > 💁 Jika anda menggunakan macOS, pemberitahuan tentang *DISK NOT EJECTED PROPERLY* akan muncul. Ini kerana Wio Terminal dipasang sebagai pemacu sebagai sebahagian daripada proses flashing, dan ia diputuskan apabila kod yang disusun ditulis ke peranti. Anda boleh mengabaikan pemberitahuan ini.

    ⚠️ Jika anda mendapat ralat tentang port muat naik tidak tersedia, pertama pastikan anda telah menyambungkan Wio Terminal ke komputer anda, dan dihidupkan menggunakan suis di sebelah kiri skrin, dan diletakkan dalam mod muat naik. Lampu hijau di bahagian bawah sepatutnya menyala, dan lampu biru sepatutnya berdenyut. Jika anda masih mendapat ralat, tarik suis hidup/mati ke bawah dua kali dengan cepat lagi untuk memaksa Wio Terminal ke mod muat naik dan cuba muat naik semula.

PlatformIO mempunyai Serial Monitor yang boleh memantau data yang dihantar melalui kabel USB dari Wio Terminal. Ini membolehkan anda memantau data yang dihantar oleh arahan `Serial.println("Hello World");`.

1. Buka palet arahan VS Code

1. Taip `PlatformIO Serial` untuk mencari pilihan Serial Monitor, dan pilih *PlatformIO: Serial Monitor*

    ![Pilihan Serial Monitor PlatformIO dalam palet arahan](../../../../../translated_images/vscode-platformio-serial-monitor-command-palette.b348ec841b8a1c14.ms.png)

    Terminal baru akan dibuka, dan data yang dihantar melalui port serial akan disiarkan ke terminal ini:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Hello World
    Hello World
    ```

    `Hello World` akan dicetak ke serial monitor setiap 5 saat.

> 💁 Anda boleh menemui kod ini dalam folder [code/wio-terminal](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/wio-terminal).

😀 Program 'Hello World' anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil maklum bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat penting, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.