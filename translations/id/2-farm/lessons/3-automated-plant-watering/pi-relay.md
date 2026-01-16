<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "66b81165e60f8f169bd52a401b6a0f8b",
  "translation_date": "2025-08-27T21:38:04+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/pi-relay.md",
  "language_code": "id"
}
-->
# Mengontrol relay - Raspberry Pi

Dalam bagian pelajaran ini, Anda akan menambahkan relay ke Raspberry Pi Anda selain sensor kelembapan tanah, dan mengontrolnya berdasarkan tingkat kelembapan tanah.

## Perangkat Keras

Raspberry Pi membutuhkan relay.

Relay yang akan Anda gunakan adalah [Grove relay](https://www.seeedstudio.com/Grove-Relay.html), sebuah relay yang biasanya terbuka (artinya sirkuit output terbuka, atau terputus ketika tidak ada sinyal yang dikirim ke relay) yang dapat menangani sirkuit output hingga 250V dan 10A.

Ini adalah aktuator digital, jadi terhubung ke pin digital pada Grove Base Hat.

### Hubungkan relay

Relay Grove dapat dihubungkan ke Raspberry Pi.

#### Tugas

Hubungkan relay.

![Sebuah Grove relay](../../../../../translated_images/id/grove-relay.d426958ca210fbd0fb7983d7edc069d46c73a8b0a099d94797bd756f7b6bb6be.png)

1. Masukkan salah satu ujung kabel Grove ke soket pada relay. Kabel ini hanya dapat masuk dengan satu arah.

1. Dengan Raspberry Pi dalam keadaan mati, hubungkan ujung lain kabel Grove ke soket digital yang ditandai **D5** pada Grove Base Hat yang terpasang pada Pi. Soket ini adalah soket kedua dari kiri, pada baris soket di sebelah pin GPIO. Biarkan sensor kelembapan tanah tetap terhubung ke soket **A0**.

![Relay Grove terhubung ke soket D5, dan sensor kelembapan tanah terhubung ke soket A0](../../../../../translated_images/id/pi-relay-and-soil-moisture-sensor.02f3198975b8c53e69ec716cd2719ce117700bd1fc933eaf93476c103c57939b.png)

1. Masukkan sensor kelembapan tanah ke dalam tanah, jika belum dilakukan dari pelajaran sebelumnya.

## Program relay

Raspberry Pi sekarang dapat diprogram untuk menggunakan relay yang terpasang.

### Tugas

Program perangkat.

1. Nyalakan Pi dan tunggu hingga selesai booting.

1. Buka proyek `soil-moisture-sensor` dari pelajaran sebelumnya di VS Code jika belum terbuka. Anda akan menambahkan kode ke proyek ini.

1. Tambahkan kode berikut ke file `app.py` di bawah bagian impor yang sudah ada:

    ```python
    from grove.grove_relay import GroveRelay
    ```

    Pernyataan ini mengimpor `GroveRelay` dari pustaka Python Grove untuk berinteraksi dengan relay Grove.

1. Tambahkan kode berikut di bawah deklarasi kelas `ADC` untuk membuat instance `GroveRelay`:

    ```python
    relay = GroveRelay(5)
    ```

    Ini membuat relay menggunakan pin **D5**, pin digital tempat Anda menghubungkan relay.

1. Untuk menguji apakah relay berfungsi, tambahkan kode berikut ke dalam loop `while True:`:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    Kode ini menyalakan relay, menunggu 0,5 detik, lalu mematikan relay.

1. Jalankan aplikasi Python. Relay akan menyala dan mati setiap 10 detik, dengan jeda setengah detik antara menyala dan mati. Anda akan mendengar relay mengklik saat menyala lalu mengklik lagi saat mati. LED pada papan Grove akan menyala saat relay menyala, lalu mati saat relay mati.

    ![Relay menyala dan mati](../../../../../images/relay-turn-on-off.gif)

## Mengontrol relay berdasarkan kelembapan tanah

Sekarang relay berfungsi, relay dapat dikontrol sebagai respons terhadap pembacaan kelembapan tanah.

### Tugas

Kontrol relay.

1. Hapus 3 baris kode yang Anda tambahkan untuk menguji relay. Gantikan dengan kode berikut:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    Kode ini memeriksa tingkat kelembapan tanah dari sensor kelembapan tanah. Jika nilainya di atas 450, relay akan menyala, dan akan mati jika nilainya di bawah 450.

    > 💁 Ingat bahwa sensor kelembapan tanah kapasitif membaca semakin rendah tingkat kelembapan tanah, semakin banyak kelembapan yang ada di tanah, dan sebaliknya.

1. Jalankan aplikasi Python. Anda akan melihat relay menyala atau mati tergantung pada tingkat kelembapan tanah. Cobalah pada tanah kering, lalu tambahkan air.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Anda dapat menemukan kode ini di folder [code-relay/pi](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/pi).

😀 Program sensor kelembapan tanah yang mengontrol relay Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diketahui bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.