<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6145a1d791731c8a9d0afd0a1bae5108",
  "translation_date": "2025-08-27T21:19:34+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/pi-proximity.md",
  "language_code": "ms"
}
-->
# Mengesan Kedekatan - Raspberry Pi

Dalam bahagian pelajaran ini, anda akan menambah sensor kedekatan pada Raspberry Pi anda, dan membaca jarak daripadanya.

## Perkakasan

Raspberry Pi memerlukan sensor kedekatan.

Sensor yang akan anda gunakan ialah [Grove Time of Flight distance sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Sensor ini menggunakan modul pengukuran laser untuk mengesan jarak. Sensor ini mempunyai julat dari 10mm hingga 2000mm (1cm - 2m), dan akan melaporkan nilai dalam julat tersebut dengan agak tepat, dengan jarak melebihi 1000mm dilaporkan sebagai 8109mm.

Pencari jarak laser terletak di bahagian belakang sensor, bertentangan dengan soket Grove.

Ini adalah sensor I²C.

### Sambungkan sensor time of flight

Sensor Grove time of flight boleh disambungkan ke Raspberry Pi.

#### Tugas - sambungkan sensor time of flight

Sambungkan sensor time of flight.

![Sensor Grove time of flight](../../../../../translated_images/ms/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.png)

1. Masukkan satu hujung kabel Grove ke dalam soket pada sensor time of flight. Ia hanya boleh dimasukkan dalam satu arah sahaja.

1. Dengan Raspberry Pi dimatikan, sambungkan hujung lain kabel Grove ke salah satu soket I²C yang ditandakan **I²C** pada Grove Base hat yang dipasang pada Pi. Soket ini berada di baris bawah, bertentangan dengan pin GPIO dan bersebelahan dengan slot kabel kamera.

![Sensor Grove time of flight disambungkan ke soket I²C](../../../../../translated_images/ms/pi-time-of-flight-sensor.58c8dc04eb3bfb57.webp)

## Programkan sensor time of flight

Raspberry Pi kini boleh diprogramkan untuk menggunakan sensor time of flight yang disambungkan.

### Tugas - programkan sensor time of flight

Programkan peranti.

1. Hidupkan Pi dan tunggu sehingga ia selesai boot.

1. Buka kod `fruit-quality-detector` dalam VS Code, sama ada secara langsung pada Pi, atau sambung melalui sambungan Remote SSH.

1. Pasang pakej rpi-vl53l0x Pip, iaitu pakej Python yang berinteraksi dengan sensor jarak time-of-flight VL53L0X. Pasang menggunakan arahan pip ini:

    ```sh
    pip install rpi-vl53l0x
    ```

1. Cipta fail baru dalam projek ini bernama `distance-sensor.py`.

    > 💁 Cara mudah untuk mensimulasikan pelbagai peranti IoT adalah dengan melakukannya dalam fail Python yang berbeza, kemudian jalankan mereka pada masa yang sama.

1. Tambahkan kod berikut ke fail ini:

    ```python
    import time
    
    from grove.i2c import Bus
    from rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Kod ini mengimport perpustakaan Grove I²C bus, dan perpustakaan sensor untuk perkakasan sensor teras yang terbina dalam sensor Grove time of flight.

1. Di bawah ini, tambahkan kod berikut untuk mengakses sensor:

    ```python
    distance_sensor = VL53L0X(bus = Bus().bus)
    distance_sensor.begin()    
    ```

    Kod ini mengisytiharkan sensor jarak menggunakan Grove I²C bus, kemudian memulakan sensor.

1. Akhir sekali, tambahkan gelung infiniti untuk membaca jarak:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Kod ini menunggu nilai sedia untuk dibaca dari sensor, kemudian mencetaknya ke konsol.

1. Jalankan kod ini.

    > 💁 Jangan lupa fail ini bernama `distance-sensor.py`! Pastikan untuk menjalankannya melalui Python, bukan `app.py`.

1. Anda akan melihat bacaan jarak muncul di konsol. Letakkan objek berhampiran sensor dan anda akan melihat bacaan jarak:

    ```output
    pi@raspberrypi:~/fruit-quality-detector $ python3 distance_sensor.py 
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Pencari jarak terletak di bahagian belakang sensor, jadi pastikan anda menggunakan bahagian yang betul semasa mengukur jarak.

    ![Pencari jarak di bahagian belakang sensor time of flight menghala ke pisang](../../../../../translated_images/ms/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 Anda boleh menemui kod ini dalam folder [code-proximity/pi](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/pi).

😀 Program sensor kedekatan anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.