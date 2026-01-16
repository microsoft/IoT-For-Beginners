<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "288aebb0c59f7be1d2719b8f9660a313",
  "translation_date": "2025-08-27T21:20:30+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/wio-terminal-proximity.md",
  "language_code": "ms"
}
-->
# Mengesan Kedekatan - Wio Terminal

Dalam bahagian pelajaran ini, anda akan menambah sensor kedekatan pada Wio Terminal anda, dan membaca jarak daripadanya.

## Perkakasan

Wio Terminal memerlukan sensor kedekatan.

Sensor yang akan anda gunakan ialah [Grove Time of Flight distance sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Sensor ini menggunakan modul pengukuran laser untuk mengesan jarak. Sensor ini mempunyai julat dari 10mm hingga 2000mm (1cm - 2m), dan akan melaporkan nilai dalam julat tersebut dengan tepat, dengan jarak melebihi 1000mm dilaporkan sebagai 8109mm.

Pencari jarak laser terletak di bahagian belakang sensor, bertentangan dengan soket Grove.

Ini adalah soket I²C.

### Sambungkan sensor time of flight

Sensor Grove time of flight boleh disambungkan ke Wio Terminal.

#### Tugasan - sambungkan sensor time of flight

Sambungkan sensor time of flight.

![Sensor Grove time of flight](../../../../../translated_images/ms/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.png)

1. Masukkan satu hujung kabel Grove ke dalam soket pada sensor time of flight. Ia hanya boleh dimasukkan dalam satu arah sahaja.

1. Dengan Wio Terminal tidak disambungkan ke komputer atau sumber kuasa lain, sambungkan hujung lain kabel Grove ke soket Grove di sebelah kiri Wio Terminal apabila anda melihat skrin. Ini adalah soket yang paling dekat dengan butang kuasa. Ini adalah soket gabungan digital dan I²C.

![Sensor Grove time of flight disambungkan ke soket sebelah kiri](../../../../../translated_images/ms/wio-time-of-flight-sensor.c4c182131d2ea73d.webp)

1. Anda kini boleh menyambungkan Wio Terminal ke komputer anda.

## Programkan sensor time of flight

Wio Terminal kini boleh diprogramkan untuk menggunakan sensor time of flight yang disambungkan.

### Tugasan - programkan sensor time of flight

1. Cipta projek Wio Terminal baharu menggunakan PlatformIO. Namakan projek ini `distance-sensor`. Tambahkan kod dalam fungsi `setup` untuk mengkonfigurasi port serial.

1. Tambahkan kebergantungan perpustakaan untuk perpustakaan Seeed Grove time of flight distance sensor ke dalam fail `platformio.ini` projek:

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

1. Dalam `main.cpp`, tambahkan yang berikut di bawah arahan include sedia ada untuk mengisytiharkan satu instance kelas `Seeed_vl53l0x` untuk berinteraksi dengan sensor time of flight:

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

1. Tambahkan yang berikut ke bahagian bawah fungsi `setup` untuk memulakan sensor:

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

1. Dalam fungsi `loop`, baca nilai daripada sensor:

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    Kod ini memulakan struktur data untuk membaca data, kemudian menghantarnya ke kaedah `PerformSingleRangingMeasurement` di mana ia akan diisi dengan ukuran jarak.

1. Di bawah ini, tulis ukuran jarak, kemudian tunggu selama 1 saat:

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

1. Bina, muat naik dan jalankan kod ini. Anda akan dapat melihat ukuran jarak menggunakan monitor serial. Letakkan objek berhampiran sensor dan anda akan melihat ukuran jarak:

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Pencari jarak terletak di bahagian belakang sensor, jadi pastikan anda menggunakan sisi yang betul semasa mengukur jarak.

    ![Pencari jarak di bahagian belakang sensor time of flight menghala ke arah pisang](../../../../../translated_images/ms/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 Anda boleh menemui kod ini dalam folder [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal).

😀 Program sensor kedekatan anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.