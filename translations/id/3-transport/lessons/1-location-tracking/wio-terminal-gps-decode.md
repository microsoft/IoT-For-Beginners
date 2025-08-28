<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-27T23:50:44+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "id"
}
-->
# Memecahkan Data GPS - Wio Terminal

Dalam bagian pelajaran ini, Anda akan memecahkan pesan NMEA yang dibaca dari sensor GPS oleh Wio Terminal, dan mengekstrak data lintang dan bujur.

## Memecahkan Data GPS

Setelah data mentah NMEA dibaca dari port serial, data tersebut dapat dipecahkan menggunakan pustaka NMEA sumber terbuka.

### Tugas - Memecahkan Data GPS

Programkan perangkat untuk memecahkan data GPS.

1. Buka proyek aplikasi `gps-sensor` jika belum terbuka.

1. Tambahkan dependensi pustaka untuk pustaka [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) ke file `platformio.ini` proyek. Pustaka ini memiliki kode untuk memecahkan data NMEA.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. Dalam `main.cpp`, tambahkan direktif include untuk pustaka TinyGPSPlus:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. Di bawah deklarasi `Serial3`, deklarasikan objek TinyGPSPlus untuk memproses kalimat NMEA:

    ```cpp
    TinyGPSPlus gps;
    ```

1. Ubah isi fungsi `printGPSData` menjadi seperti berikut:

    ```cpp
    if (gps.encode(Serial3.read()))
    {
        if (gps.location.isValid())
        {
            Serial.print(gps.location.lat(), 6);
            Serial.print(F(","));
            Serial.print(gps.location.lng(), 6);
            Serial.print(" - from ");
            Serial.print(gps.satellites.value());
            Serial.println(" satellites");
        }
    }
    ```

    Kode ini membaca karakter berikutnya dari port serial UART ke dalam decoder NMEA `gps`. Setelah setiap karakter, kode akan memeriksa apakah decoder telah membaca kalimat yang valid, lalu memeriksa apakah lokasi yang valid telah dibaca. Jika lokasi valid, data tersebut akan dikirim ke monitor serial, bersama dengan jumlah satelit yang berkontribusi pada perhitungan ini.

1. Bangun dan unggah kode ke Wio Terminal.

1. Setelah diunggah, Anda dapat memantau data lokasi GPS menggunakan monitor serial.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Anda dapat menemukan kode ini di folder [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal).

😀 Program sensor GPS Anda dengan pemecahan data berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.