<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "288aebb0c59f7be1d2719b8f9660a313",
  "translation_date": "2025-08-27T21:20:19+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/wio-terminal-proximity.md",
  "language_code": "id"
}
-->
# Deteksi Kedekatan - Wio Terminal

Dalam bagian pelajaran ini, Anda akan menambahkan sensor kedekatan ke Wio Terminal Anda, dan membaca jarak darinya.

## Perangkat Keras

Wio Terminal membutuhkan sensor kedekatan.

Sensor yang akan Anda gunakan adalah [Grove Time of Flight distance sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Sensor ini menggunakan modul pengukuran laser untuk mendeteksi jarak. Sensor ini memiliki jangkauan dari 10mm hingga 2000mm (1cm - 2m), dan akan melaporkan nilai dalam rentang tersebut dengan cukup akurat, dengan jarak di atas 1000mm dilaporkan sebagai 8109mm.

Pengukur jarak laser berada di bagian belakang sensor, sisi yang berlawanan dengan soket Grove.

Ini adalah soket I²C.

### Hubungkan sensor time of flight

Sensor Grove time of flight dapat dihubungkan ke Wio Terminal.

#### Tugas - hubungkan sensor time of flight

Hubungkan sensor time of flight.

![Sensor Grove time of flight](../../../../../translated_images/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.id.png)

1. Masukkan salah satu ujung kabel Grove ke soket pada sensor time of flight. Kabel hanya dapat masuk dengan satu arah.

1. Dengan Wio Terminal terputus dari komputer atau sumber daya lainnya, hubungkan ujung lain kabel Grove ke soket Grove di sisi kiri Wio Terminal saat Anda melihat layar. Soket ini adalah yang paling dekat dengan tombol daya. Soket ini adalah soket gabungan digital dan I²C.

![Sensor Grove time of flight terhubung ke soket kiri](../../../../../translated_images/wio-time-of-flight-sensor.c4c182131d2ea73d.id.png)

1. Sekarang Anda dapat menghubungkan Wio Terminal ke komputer Anda.

## Program sensor time of flight

Wio Terminal sekarang dapat diprogram untuk menggunakan sensor time of flight yang terpasang.

### Tugas - program sensor time of flight

1. Buat proyek Wio Terminal baru menggunakan PlatformIO. Beri nama proyek ini `distance-sensor`. Tambahkan kode di fungsi `setup` untuk mengonfigurasi port serial.

1. Tambahkan dependensi pustaka untuk pustaka sensor jarak Seeed Grove time of flight ke file `platformio.ini` proyek:

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

1. Di `main.cpp`, tambahkan berikut ini di bawah direktif include yang ada untuk mendeklarasikan instance dari kelas `Seeed_vl53l0x` untuk berinteraksi dengan sensor time of flight:

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

1. Tambahkan berikut ini ke bagian bawah fungsi `setup` untuk menginisialisasi sensor:

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

1. Di fungsi `loop`, baca nilai dari sensor:

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    Kode ini menginisialisasi struktur data untuk membaca data, lalu meneruskannya ke metode `PerformSingleRangingMeasurement` di mana data akan diisi dengan pengukuran jarak.

1. Di bawah ini, tuliskan pengukuran jarak, lalu tunggu selama 1 detik:

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

1. Bangun, unggah, dan jalankan kode ini. Anda akan dapat melihat pengukuran jarak dengan monitor serial. Tempatkan objek di dekat sensor dan Anda akan melihat pengukuran jarak:

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Pengukur jarak berada di bagian belakang sensor, jadi pastikan Anda menggunakan sisi yang benar saat mengukur jarak.

    ![Pengukur jarak di bagian belakang sensor time of flight mengarah ke pisang](../../../../../translated_images/time-of-flight-banana.079921ad8b1496e4.id.png)

> 💁 Anda dapat menemukan kode ini di folder [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal).

😀 Program sensor kedekatan Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.