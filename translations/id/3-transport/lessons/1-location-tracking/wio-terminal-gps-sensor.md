<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "da6ae0a795cf06be33d23ca5b8493fc8",
  "translation_date": "2025-08-27T23:39:26+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-sensor.md",
  "language_code": "id"
}
-->
# Membaca Data GPS - Wio Terminal

Dalam bagian pelajaran ini, Anda akan menambahkan sensor GPS ke Wio Terminal Anda, dan membaca nilai-nilainya.

## Perangkat Keras

Wio Terminal membutuhkan sensor GPS.

Sensor yang akan Anda gunakan adalah [Grove GPS Air530 sensor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Sensor ini dapat terhubung ke beberapa sistem GPS untuk mendapatkan posisi yang cepat dan akurat. Sensor ini terdiri dari 2 bagian - komponen inti elektronik sensor, dan antena eksternal yang terhubung dengan kabel tipis untuk menangkap gelombang radio dari satelit.

Ini adalah sensor UART, sehingga mengirimkan data GPS melalui UART.

### Hubungkan Sensor GPS

Sensor GPS Grove dapat dihubungkan ke Wio Terminal.

#### Tugas - hubungkan sensor GPS

Hubungkan sensor GPS.

![Sensor GPS Grove](../../../../../translated_images/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.id.png)

1. Masukkan salah satu ujung kabel Grove ke soket pada sensor GPS. Kabel ini hanya dapat dimasukkan dengan satu arah.

1. Dengan Wio Terminal tidak terhubung ke komputer atau sumber daya lainnya, hubungkan ujung lain kabel Grove ke soket Grove di sisi kiri Wio Terminal saat Anda melihat layar. Soket ini adalah yang paling dekat dengan tombol daya.

    ![Sensor GPS Grove terhubung ke soket kiri](../../../../../translated_images/wio-gps-sensor.19fd52b81ce58095.id.png)

1. Posisikan sensor GPS sehingga antena yang terpasang memiliki visibilitas ke langit - idealnya di dekat jendela yang terbuka atau di luar ruangan. Sinyal akan lebih jelas jika tidak ada penghalang di sekitar antena.

1. Sekarang Anda dapat menghubungkan Wio Terminal ke komputer Anda.

1. Sensor GPS memiliki 2 LED - LED biru yang berkedip saat data dikirimkan, dan LED hijau yang berkedip setiap detik saat menerima data dari satelit. Pastikan LED biru berkedip saat Anda menyalakan Wio Terminal. Setelah beberapa menit, LED hijau akan berkedip - jika tidak, Anda mungkin perlu memposisikan ulang antena.

## Program Sensor GPS

Wio Terminal sekarang dapat diprogram untuk menggunakan sensor GPS yang terhubung.

### Tugas - program sensor GPS

Program perangkat.

1. Buat proyek baru untuk Wio Terminal menggunakan PlatformIO. Beri nama proyek ini `gps-sensor`. Tambahkan kode dalam fungsi `setup` untuk mengonfigurasi port serial.

1. Tambahkan directive include berikut di bagian atas file `main.cpp`. Directive ini menyertakan file header dengan fungsi untuk mengonfigurasi port Grove di sisi kiri untuk UART.

    ```cpp
    #include <wiring_private.h>
    ```

1. Di bawah ini, tambahkan baris kode berikut untuk mendeklarasikan koneksi port serial ke port UART:

    ```cpp
    static Uart Serial3(&sercom3, PIN_WIRE_SCL, PIN_WIRE_SDA, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    ```

1. Anda perlu menambahkan beberapa kode untuk mengarahkan beberapa pengendali sinyal internal ke port serial ini. Tambahkan kode berikut di bawah deklarasi `Serial3`:

    ```cpp
    void SERCOM3_0_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_1_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_2_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_3_Handler()
    {
        Serial3.IrqHandler();
    }
    ```

1. Dalam fungsi `setup` di bawah tempat port `Serial` dikonfigurasi, konfigurasikan port serial UART dengan kode berikut:

    ```cpp
    Serial3.begin(9600);

    while (!Serial3)
        ; // Wait for Serial3 to be ready

    delay(1000);
    ```

1. Di bawah kode ini dalam fungsi `setup`, tambahkan kode berikut untuk menghubungkan pin Grove ke port serial:

    ```cpp
    pinPeripheral(PIN_WIRE_SCL, PIO_SERCOM_ALT);
    ```

1. Tambahkan fungsi berikut sebelum fungsi `loop` untuk mengirim data GPS ke monitor serial:

    ```cpp
    void printGPSData()
    {
        Serial.println(Serial3.readStringUntil('\n'));
    }
    ```

1. Dalam fungsi `loop`, tambahkan kode berikut untuk membaca dari port serial UART dan mencetak output ke monitor serial:

    ```cpp
    while (Serial3.available() > 0)
    {
        printGPSData();
    }
    
    delay(1000);
    ```

    Kode ini membaca dari port serial UART. Fungsi `readStringUntil` membaca hingga karakter terminator, dalam hal ini karakter baris baru. Ini akan membaca seluruh kalimat NMEA (kalimat NMEA diakhiri dengan karakter baris baru). Selama data dapat dibaca dari port serial UART, data tersebut akan dibaca dan dikirim ke monitor serial melalui fungsi `printGPSData`. Setelah tidak ada lagi data yang dapat dibaca, fungsi `loop` akan menunda selama 1 detik (1.000ms).

1. Bangun dan unggah kode ke Wio Terminal.

1. Setelah diunggah, Anda dapat memantau data GPS menggunakan monitor serial.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

> 💁 Anda dapat menemukan kode ini di folder [code-gps/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps/wio-terminal).

😀 Program sensor GPS Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diketahui bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.