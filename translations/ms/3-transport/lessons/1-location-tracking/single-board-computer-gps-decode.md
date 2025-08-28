<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cbb8c285bc64c5192fae3368fb5077d2",
  "translation_date": "2025-08-27T23:52:32+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/single-board-computer-gps-decode.md",
  "language_code": "ms"
}
-->
# Nyahkod Data GPS - Perkakasan IoT Maya dan Raspberry Pi

Dalam bahagian pelajaran ini, anda akan menyahkod mesej NMEA yang dibaca daripada sensor GPS oleh Raspberry Pi atau Peranti IoT Maya, dan mengekstrak latitud dan longitud.

## Nyahkod Data GPS

Setelah data mentah NMEA dibaca daripada port bersiri, ia boleh dinyahkod menggunakan perpustakaan NMEA sumber terbuka.

### Tugasan - nyahkod data GPS

Programkan peranti untuk menyahkod data GPS.

1. Buka projek aplikasi `gps-sensor` jika ia belum dibuka.

1. Pasang pakej Pip `pynmea2`. Pakej ini mengandungi kod untuk menyahkod mesej NMEA.

    ```sh
    pip3 install pynmea2
    ```

1. Tambahkan kod berikut ke bahagian import dalam fail `app.py` untuk mengimport modul `pynmea2`:

    ```python
    import pynmea2
    ```

1. Gantikan kandungan fungsi `print_gps_data` dengan yang berikut:

    ```python
    msg = pynmea2.parse(line)
    if msg.sentence_type == 'GGA':
        lat = pynmea2.dm_to_sd(msg.lat)
        lon = pynmea2.dm_to_sd(msg.lon)

        if msg.lat_dir == 'S':
            lat = lat * -1

        if msg.lon_dir == 'W':
            lon = lon * -1

        print(f'{lat},{lon} - from {msg.num_sats} satellites')
    ```

    Kod ini akan menggunakan perpustakaan `pynmea2` untuk menganalisis baris yang dibaca daripada port bersiri UART.

    Jika jenis ayat mesej adalah `GGA`, maka ini adalah mesej penetapan kedudukan, dan ia akan diproses. Nilai latitud dan longitud dibaca daripada mesej dan ditukar kepada darjah perpuluhan daripada format NMEA `(d)ddmm.mmmm`. Fungsi `dm_to_sd` melakukan penukaran ini.

    Arah latitud kemudian diperiksa, dan jika latitud adalah selatan, maka nilainya ditukar kepada nombor negatif. Begitu juga dengan longitud, jika ia barat maka ia ditukar kepada nombor negatif.

    Akhir sekali, koordinat dicetak ke konsol, bersama-sama dengan bilangan satelit yang digunakan untuk mendapatkan lokasi.

1. Jalankan kod. Jika anda menggunakan peranti IoT maya, pastikan aplikasi CounterFit sedang berjalan dan data GPS sedang dihantar.

    ```output
    pi@raspberrypi:~/gps-sensor $ python3 app.py 
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Anda boleh menemui kod ini dalam folder [code-gps-decode/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/virtual-device), atau folder [code-gps-decode/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/pi).

😀 Program sensor GPS anda dengan penyahkodan data berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.