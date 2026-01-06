<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6145a1d791731c8a9d0afd0a1bae5108",
  "translation_date": "2025-08-27T21:19:20+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/pi-proximity.md",
  "language_code": "id"
}
-->
# Deteksi Kedekatan - Raspberry Pi

Dalam bagian pelajaran ini, Anda akan menambahkan sensor kedekatan ke Raspberry Pi Anda, dan membaca jarak darinya.

## Perangkat Keras

Raspberry Pi membutuhkan sensor kedekatan.

Sensor yang akan Anda gunakan adalah [Grove Time of Flight distance sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Sensor ini menggunakan modul pengukuran laser untuk mendeteksi jarak. Sensor ini memiliki jangkauan 10mm hingga 2000mm (1cm - 2m), dan akan melaporkan nilai dalam rentang tersebut dengan cukup akurat, dengan jarak di atas 1000mm dilaporkan sebagai 8109mm.

Pengukur jarak laser berada di bagian belakang sensor, sisi yang berlawanan dengan soket Grove.

Ini adalah sensor I²C.

### Hubungkan Sensor Time of Flight

Sensor Grove time of flight dapat dihubungkan ke Raspberry Pi.

#### Tugas - Hubungkan Sensor Time of Flight

Hubungkan sensor time of flight.

![Sensor time of flight Grove](../../../../../translated_images/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.id.png)

1. Masukkan salah satu ujung kabel Grove ke soket pada sensor time of flight. Kabel hanya dapat masuk dengan satu arah.

1. Dengan Raspberry Pi dalam keadaan mati, hubungkan ujung lain kabel Grove ke salah satu soket I²C yang ditandai **I²C** pada Grove Base hat yang terpasang pada Pi. Soket ini berada di baris bawah, di ujung yang berlawanan dengan pin GPIO dan di sebelah slot kabel kamera.

![Sensor time of flight Grove terhubung ke soket I²C](../../../../../translated_images/pi-time-of-flight-sensor.58c8dc04eb3bfb57.id.png)

## Program Sensor Time of Flight

Raspberry Pi sekarang dapat diprogram untuk menggunakan sensor time of flight yang terpasang.

### Tugas - Program Sensor Time of Flight

Program perangkatnya.

1. Nyalakan Pi dan tunggu hingga selesai booting.

1. Buka kode `fruit-quality-detector` di VS Code, baik langsung di Pi, atau sambungkan melalui ekstensi Remote SSH.

1. Instal paket Pip rpi-vl53l0x, sebuah paket Python yang berinteraksi dengan sensor jarak time-of-flight VL53L0X. Instal menggunakan perintah pip berikut:

    ```sh
    pip install rpi-vl53l0x
    ```

1. Buat file baru dalam proyek ini bernama `distance-sensor.py`.

    > 💁 Cara mudah untuk mensimulasikan beberapa perangkat IoT adalah dengan membuat masing-masing di file Python yang berbeda, lalu menjalankannya secara bersamaan.

1. Tambahkan kode berikut ke file ini:

    ```python
    import time
    
    from grove.i2c import Bus
    from rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Kode ini mengimpor pustaka Grove I²C bus, dan pustaka sensor untuk perangkat keras inti yang ada di dalam sensor Grove time of flight.

1. Di bawah ini, tambahkan kode berikut untuk mengakses sensor:

    ```python
    distance_sensor = VL53L0X(bus = Bus().bus)
    distance_sensor.begin()    
    ```

    Kode ini mendeklarasikan sensor jarak menggunakan Grove I²C bus, lalu memulai sensor.

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

1. Anda akan melihat pengukuran jarak muncul di konsol. Posisikan objek di dekat sensor dan Anda akan melihat pengukuran jarak:

    ```output
    pi@raspberrypi:~/fruit-quality-detector $ python3 distance_sensor.py 
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Pengukur jarak berada di bagian belakang sensor, jadi pastikan Anda menggunakan sisi yang benar saat mengukur jarak.

    ![Pengukur jarak di bagian belakang sensor time of flight mengarah ke pisang](../../../../../translated_images/time-of-flight-banana.079921ad8b1496e4.id.png)

> 💁 Anda dapat menemukan kode ini di folder [code-proximity/pi](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/pi).

😀 Program sensor kedekatan Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.