<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e9f05bdc50a40fd924b1d66934471bf",
  "translation_date": "2025-08-27T21:21:10+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/virtual-device-proximity.md",
  "language_code": "id"
}
-->
# Deteksi Kedekatan - Perangkat IoT Virtual

Dalam bagian pelajaran ini, Anda akan menambahkan sensor kedekatan ke perangkat IoT virtual Anda, dan membaca jarak darinya.

## Perangkat Keras

Perangkat IoT virtual akan menggunakan sensor jarak yang disimulasikan.

Pada perangkat IoT fisik, Anda akan menggunakan sensor dengan modul pengukuran laser untuk mendeteksi jarak.

### Tambahkan sensor jarak ke CounterFit

Untuk menggunakan sensor jarak virtual, Anda perlu menambahkannya ke aplikasi CounterFit.

#### Tugas - tambahkan sensor jarak ke CounterFit

Tambahkan sensor jarak ke aplikasi CounterFit.

1. Buka kode `fruit-quality-detector` di VS Code, dan pastikan lingkungan virtual telah diaktifkan.

1. Instal paket Pip tambahan untuk menginstal CounterFit shim yang dapat berkomunikasi dengan sensor jarak dengan mensimulasikan [paket Pip rpi-vl53l0x](https://pypi.org/project/rpi-vl53l0x/), sebuah paket Python yang berinteraksi dengan [sensor jarak VL53L0X time-of-flight](https://wiki.seeedstudio.com/Grove-Time_of_Flight_Distance_Sensor-VL53L0X/). Pastikan Anda menginstalnya dari terminal dengan lingkungan virtual yang diaktifkan.

    ```sh
    pip install counterfit-shims-rpi-vl53l0x
    ```

1. Pastikan aplikasi web CounterFit sedang berjalan.

1. Buat sensor jarak:

    1. Di kotak *Create sensor* pada panel *Sensors*, klik dropdown pada kotak *Sensor type* dan pilih *Distance*.

    1. Biarkan *Units* sebagai `Millimeter`.

    1. Sensor ini adalah sensor I²C, jadi atur alamatnya ke `0x29`. Jika Anda menggunakan sensor VL53L0X fisik, alamat ini akan dikodekan secara tetap.

    1. Pilih tombol **Add** untuk membuat sensor jarak.

    ![Pengaturan sensor jarak](../../../../../translated_images/id/counterfit-create-distance-sensor.967c9fb98f27888d95920c9784d004c972490eb71f70397fe13bd70a79a879a3.png)

    Sensor jarak akan dibuat dan muncul dalam daftar sensor.

    ![Sensor jarak yang dibuat](../../../../../translated_images/id/counterfit-distance-sensor.079eefeeea0b68afc36431ce8fcbe2f09a7e4916ed1cd5cb30e696db53bc18fa.png)

## Program sensor jarak

Perangkat IoT virtual sekarang dapat diprogram untuk menggunakan sensor jarak yang disimulasikan.

### Tugas - program sensor time of flight

1. Buat file baru di proyek `fruit-quality-detector` bernama `distance-sensor.py`.

    > 💁 Cara mudah untuk mensimulasikan beberapa perangkat IoT adalah dengan membuat masing-masing di file Python yang berbeda, lalu menjalankannya secara bersamaan.

1. Mulai koneksi ke CounterFit dengan kode berikut:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Tambahkan kode berikut di bawahnya:

    ```python
    import time
    
    from counterfit_shims_rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Kode ini mengimpor pustaka sensor shim untuk sensor time of flight VL53L0X.

1. Di bawah ini, tambahkan kode berikut untuk mengakses sensor:

    ```python
    distance_sensor = VL53L0X()
    distance_sensor.begin()
    ```

    Kode ini mendeklarasikan sensor jarak, lalu memulai sensor.

1. Terakhir, tambahkan loop tak terbatas untuk membaca jarak:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Kode ini menunggu nilai siap untuk dibaca dari sensor, lalu mencetaknya ke konsol.

1. Jalankan kode ini.

    > 💁 Jangan lupa file ini bernama `distance-sensor.py`! Pastikan untuk menjalankannya melalui Python, bukan `app.py`.

1. Anda akan melihat pengukuran jarak muncul di konsol. Ubah nilai di CounterFit untuk melihat nilai ini berubah, atau gunakan nilai acak.

    ```output
    (.venv) ➜  fruit-quality-detector python distance-sensor.py 
    Distance = 37 mm
    Distance = 42 mm
    Distance = 29 mm
    ```

> 💁 Anda dapat menemukan kode ini di folder [code-proximity/virtual-iot-device](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/virtual-iot-device).

😀 Program sensor kedekatan Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diperhatikan bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang timbul dari penggunaan terjemahan ini.