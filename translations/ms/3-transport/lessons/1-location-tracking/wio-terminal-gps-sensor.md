<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "da6ae0a795cf06be33d23ca5b8493fc8",
  "translation_date": "2025-08-27T23:39:46+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-sensor.md",
  "language_code": "ms"
}
-->
# Baca Data GPS - Wio Terminal

Dalam bahagian pelajaran ini, anda akan menambah sensor GPS pada Wio Terminal anda dan membaca nilai daripadanya.

## Perkakasan

Wio Terminal memerlukan sensor GPS.

Sensor yang akan anda gunakan ialah [Grove GPS Air530 sensor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Sensor ini boleh disambungkan kepada pelbagai sistem GPS untuk mendapatkan isyarat yang pantas dan tepat. Sensor ini terdiri daripada 2 bahagian - komponen elektronik utama sensor, dan antena luaran yang disambungkan dengan wayar nipis untuk menangkap gelombang radio daripada satelit.

Ini adalah sensor UART, jadi ia menghantar data GPS melalui UART.

### Sambungkan Sensor GPS

Sensor Grove GPS boleh disambungkan kepada Wio Terminal.

#### Tugasan - sambungkan sensor GPS

Sambungkan sensor GPS.

![Sensor GPS Grove](../../../../../translated_images/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.ms.png)

1. Masukkan satu hujung kabel Grove ke dalam soket pada sensor GPS. Ia hanya boleh dimasukkan dalam satu arah sahaja.

1. Dengan Wio Terminal tidak disambungkan kepada komputer atau sumber kuasa lain, sambungkan hujung lain kabel Grove ke soket Grove di sebelah kiri Wio Terminal apabila anda melihat skrin. Ini adalah soket yang paling dekat dengan butang kuasa.

    ![Sensor GPS Grove disambungkan ke soket sebelah kiri](../../../../../translated_images/wio-gps-sensor.19fd52b81ce58095.ms.png)

1. Letakkan sensor GPS supaya antena yang disambungkan mempunyai pandangan ke langit - sebaiknya di sebelah tingkap terbuka atau di luar. Isyarat akan lebih jelas jika tiada halangan di antara antena dan langit.

1. Anda kini boleh menyambungkan Wio Terminal ke komputer anda.

1. Sensor GPS mempunyai 2 LED - LED biru yang berkelip apabila data dihantar, dan LED hijau yang berkelip setiap saat apabila menerima data daripada satelit. Pastikan LED biru berkelip apabila anda menghidupkan Wio Terminal. Selepas beberapa minit, LED hijau akan berkelip - jika tidak, anda mungkin perlu mengubah kedudukan antena.

## Programkan Sensor GPS

Wio Terminal kini boleh diprogramkan untuk menggunakan sensor GPS yang disambungkan.

### Tugasan - programkan sensor GPS

Programkan peranti.

1. Cipta projek Wio Terminal baharu menggunakan PlatformIO. Namakan projek ini `gps-sensor`. Tambahkan kod dalam fungsi `setup` untuk mengkonfigurasi port serial.

1. Tambahkan arahan include berikut di bahagian atas fail `main.cpp`. Arahan ini memasukkan fail header dengan fungsi untuk mengkonfigurasi port Grove sebelah kiri untuk UART.

    ```cpp
    #include <wiring_private.h>
    ```

1. Di bawah ini, tambahkan baris kod berikut untuk mengisytiharkan sambungan port serial ke port UART:

    ```cpp
    static Uart Serial3(&sercom3, PIN_WIRE_SCL, PIN_WIRE_SDA, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    ```

1. Anda perlu menambah beberapa kod untuk mengarahkan beberapa pengendali isyarat dalaman ke port serial ini. Tambahkan kod berikut di bawah deklarasi `Serial3`:

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

1. Dalam fungsi `setup` di bawah konfigurasi port `Serial`, konfigurasikan port serial UART dengan kod berikut:

    ```cpp
    Serial3.begin(9600);

    while (!Serial3)
        ; // Wait for Serial3 to be ready

    delay(1000);
    ```

1. Di bawah kod ini dalam fungsi `setup`, tambahkan kod berikut untuk menyambungkan pin Grove ke port serial:

    ```cpp
    pinPeripheral(PIN_WIRE_SCL, PIO_SERCOM_ALT);
    ```

1. Tambahkan fungsi berikut sebelum fungsi `loop` untuk menghantar data GPS ke monitor serial:

    ```cpp
    void printGPSData()
    {
        Serial.println(Serial3.readStringUntil('\n'));
    }
    ```

1. Dalam fungsi `loop`, tambahkan kod berikut untuk membaca dari port serial UART dan mencetak output ke monitor serial:

    ```cpp
    while (Serial3.available() > 0)
    {
        printGPSData();
    }
    
    delay(1000);
    ```

    Kod ini membaca dari port serial UART. Fungsi `readStringUntil` membaca sehingga watak pemutus, dalam kes ini baris baru. Ini akan membaca satu ayat NMEA penuh (ayat NMEA diakhiri dengan watak baris baru). Selagi data boleh dibaca dari port serial UART, ia akan dibaca dan dihantar ke monitor serial melalui fungsi `printGPSData`. Apabila tiada lagi data yang boleh dibaca, `loop` akan menunggu selama 1 saat (1,000ms).

1. Bina dan muat naik kod ke Wio Terminal.

1. Setelah dimuat naik, anda boleh memantau data GPS menggunakan monitor serial.

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

> 💁 Anda boleh menemui kod ini dalam folder [code-gps/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps/wio-terminal).

😀 Program sensor GPS anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat penting, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.