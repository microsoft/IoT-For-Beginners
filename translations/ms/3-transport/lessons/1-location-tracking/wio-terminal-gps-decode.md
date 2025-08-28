<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-27T23:50:52+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "ms"
}
-->
# Nyahkod Data GPS - Wio Terminal

Dalam bahagian pelajaran ini, anda akan nyahkod mesej NMEA yang dibaca daripada sensor GPS oleh Wio Terminal, dan mengekstrak latitud serta longitud.

## Nyahkod Data GPS

Setelah data mentah NMEA dibaca daripada port serial, ia boleh dinyahkod menggunakan perpustakaan NMEA sumber terbuka.

### Tugasan - nyahkod data GPS

Programkan peranti untuk nyahkod data GPS.

1. Buka projek aplikasi `gps-sensor` jika ia belum dibuka.

1. Tambahkan kebergantungan perpustakaan untuk perpustakaan [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) ke dalam fail `platformio.ini` projek. Perpustakaan ini mempunyai kod untuk nyahkod data NMEA.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. Dalam `main.cpp`, tambahkan arahan include untuk perpustakaan TinyGPSPlus:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. Di bawah deklarasi `Serial3`, deklarasikan objek TinyGPSPlus untuk memproses ayat NMEA:

    ```cpp
    TinyGPSPlus gps;
    ```

1. Tukar kandungan fungsi `printGPSData` kepada yang berikut:

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

    Kod ini membaca aksara seterusnya daripada port serial UART ke dalam penyahkod NMEA `gps`. Selepas setiap aksara, ia akan memeriksa sama ada penyahkod telah membaca ayat yang sah, kemudian memeriksa sama ada ia telah membaca lokasi yang sah. Jika lokasi itu sah, ia akan menghantarnya ke monitor serial, bersama dengan bilangan satelit yang menyumbang kepada penetapan ini.

1. Bina dan muat naik kod ke Wio Terminal.

1. Setelah dimuat naik, anda boleh memantau data lokasi GPS menggunakan monitor serial.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Anda boleh menemui kod ini dalam folder [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal).

😀 Program sensor GPS anda dengan nyahkod data telah berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.