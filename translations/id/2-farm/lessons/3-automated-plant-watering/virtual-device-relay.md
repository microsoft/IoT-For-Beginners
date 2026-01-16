<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f8f541ee945545017a51aaf309aa37c3",
  "translation_date": "2025-08-27T21:39:01+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/virtual-device-relay.md",
  "language_code": "id"
}
-->
# Mengontrol Relay - Perangkat Keras IoT Virtual

Dalam bagian pelajaran ini, Anda akan menambahkan relay ke perangkat IoT virtual Anda selain sensor kelembapan tanah, dan mengendalikannya berdasarkan tingkat kelembapan tanah.

## Perangkat Keras Virtual

Perangkat IoT virtual akan menggunakan simulasi relay Grove. Ini membuat lab ini tetap sama seperti menggunakan Raspberry Pi dengan relay Grove fisik.

Pada perangkat IoT fisik, relay biasanya adalah relay normally-open (artinya sirkuit output terbuka, atau terputus ketika tidak ada sinyal yang dikirim ke relay). Relay seperti ini dapat menangani sirkuit output hingga 250V dan 10A.

### Menambahkan Relay ke CounterFit

Untuk menggunakan relay virtual, Anda perlu menambahkannya ke aplikasi CounterFit.

#### Tugas

Tambahkan relay ke aplikasi CounterFit.

1. Buka proyek `soil-moisture-sensor` dari pelajaran sebelumnya di VS Code jika belum terbuka. Anda akan menambahkan ke proyek ini.

1. Pastikan aplikasi web CounterFit sedang berjalan.

1. Buat relay:

    1. Di kotak *Create actuator* pada panel *Actuators*, buka menu dropdown *Actuator type* dan pilih *Relay*.

    1. Atur *Pin* ke *5*.

    1. Pilih tombol **Add** untuk membuat relay pada Pin 5.

    ![Pengaturan relay](../../../../../translated_images/id/counterfit-create-relay.fa7c40fd0f2f6afc33b35ea94fcb235085be4861e14e3fe6b9b7bcfc82d1c888.png)

    Relay akan dibuat dan muncul di daftar aktuator.

    ![Relay yang dibuat](../../../../../translated_images/id/counterfit-relay.bbf74c1dbdc8b9acd983367fcbd06703a402aefef6af54ddb28e11307ba8a12c.png)

## Memprogram Relay

Aplikasi sensor kelembapan tanah sekarang dapat diprogram untuk menggunakan relay virtual.

### Tugas

Program perangkat virtual.

1. Buka proyek `soil-moisture-sensor` dari pelajaran sebelumnya di VS Code jika belum terbuka. Anda akan menambahkan ke proyek ini.

1. Tambahkan kode berikut ke file `app.py` di bawah impor yang sudah ada:

    ```python
    from counterfit_shims_grove.grove_relay import GroveRelay
    ```

    Pernyataan ini mengimpor `GroveRelay` dari pustaka Grove Python shim untuk berinteraksi dengan relay Grove virtual.

1. Tambahkan kode berikut di bawah deklarasi kelas `ADC` untuk membuat instance `GroveRelay`:

    ```python
    relay = GroveRelay(5)
    ```

    Ini membuat relay menggunakan pin **5**, pin tempat Anda menghubungkan relay.

1. Untuk menguji apakah relay berfungsi, tambahkan kode berikut ke dalam loop `while True:`:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    Kode ini menyalakan relay, menunggu 0,5 detik, lalu mematikan relay.

1. Jalankan aplikasi Python. Relay akan menyala dan mati setiap 10 detik, dengan jeda setengah detik antara menyala dan mati. Anda akan melihat relay virtual di aplikasi CounterFit menutup dan membuka saat relay menyala dan mati.

    ![Relay virtual menyala dan mati](../../../../../images/virtual-relay-turn-on-off.gif)

## Mengontrol Relay Berdasarkan Kelembapan Tanah

Sekarang relay sudah berfungsi, relay dapat dikontrol berdasarkan pembacaan kelembapan tanah.

### Tugas

Kontrol relay.

1. Hapus 3 baris kode yang Anda tambahkan untuk menguji relay. Ganti dengan kode berikut di tempatnya:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    Kode ini memeriksa tingkat kelembapan tanah dari sensor kelembapan tanah. Jika nilainya di atas 450, relay akan menyala, dan akan mati jika nilainya di bawah 450.

    > 💁 Ingat bahwa sensor kelembapan tanah kapasitif membaca: semakin rendah tingkat kelembapan tanah, semakin banyak kelembapan yang ada di tanah, dan sebaliknya.

1. Jalankan aplikasi Python. Anda akan melihat relay menyala atau mati tergantung pada tingkat kelembapan tanah. Ubah *Value* atau pengaturan *Random* untuk sensor kelembapan tanah untuk melihat perubahan nilai.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Anda dapat menemukan kode ini di folder [code-relay/virtual-device](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/virtual-device).

😀 Program sensor kelembapan tanah virtual Anda yang mengontrol relay berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan manusia profesional. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.