<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cbb8c285bc64c5192fae3368fb5077d2",
  "translation_date": "2025-08-27T23:52:23+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/single-board-computer-gps-decode.md",
  "language_code": "id"
}
-->
# Memecahkan Data GPS - Perangkat Keras IoT Virtual dan Raspberry Pi

Dalam bagian pelajaran ini, Anda akan memecahkan pesan NMEA yang dibaca dari sensor GPS oleh Raspberry Pi atau Perangkat IoT Virtual, dan mengekstrak nilai lintang dan bujur.

## Memecahkan Data GPS

Setelah data mentah NMEA dibaca dari port serial, data tersebut dapat dipecahkan menggunakan pustaka NMEA sumber terbuka.

### Tugas - Memecahkan Data GPS

Program perangkat untuk memecahkan data GPS.

1. Buka proyek aplikasi `gps-sensor` jika belum terbuka.

1. Instal paket Pip `pynmea2`. Paket ini memiliki kode untuk memecahkan pesan NMEA.

    ```sh
    pip3 install pynmea2
    ```

1. Tambahkan kode berikut ke bagian impor di file `app.py` untuk mengimpor modul `pynmea2`:

    ```python
    import pynmea2
    ```

1. Ganti isi fungsi `print_gps_data` dengan yang berikut:

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

    Kode ini akan menggunakan pustaka `pynmea2` untuk mem-parsing baris yang dibaca dari port serial UART.

    Jika tipe kalimat dari pesan adalah `GGA`, maka ini adalah pesan perbaikan posisi, dan akan diproses. Nilai lintang dan bujur dibaca dari pesan dan dikonversi ke derajat desimal dari format NMEA `(d)ddmm.mmmm`. Fungsi `dm_to_sd` melakukan konversi ini.

    Arah lintang kemudian diperiksa, dan jika lintang berada di selatan, maka nilainya dikonversi menjadi angka negatif. Hal yang sama berlaku untuk bujur, jika berada di barat maka akan dikonversi menjadi angka negatif.

    Akhirnya, koordinat dicetak ke konsol, bersama dengan jumlah satelit yang digunakan untuk mendapatkan lokasi.

1. Jalankan kode. Jika Anda menggunakan perangkat IoT virtual, pastikan aplikasi CounterFit berjalan dan data GPS sedang dikirim.

    ```output
    pi@raspberrypi:~/gps-sensor $ python3 app.py 
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Anda dapat menemukan kode ini di folder [code-gps-decode/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/virtual-device), atau di folder [code-gps-decode/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/pi).

😀 Program sensor GPS Anda dengan pemecahan data berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.