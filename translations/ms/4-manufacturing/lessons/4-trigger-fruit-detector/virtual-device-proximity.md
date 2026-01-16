<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e9f05bdc50a40fd924b1d66934471bf",
  "translation_date": "2025-08-27T21:21:21+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/virtual-device-proximity.md",
  "language_code": "ms"
}
-->
# Mengesan Kedekatan - Perkakasan IoT Maya

Dalam bahagian pelajaran ini, anda akan menambah sensor kedekatan pada peranti IoT maya anda, dan membaca jarak daripadanya.

## Perkakasan

Peranti IoT maya akan menggunakan sensor jarak yang disimulasikan.

Dalam peranti IoT fizikal, anda akan menggunakan sensor dengan modul pengukuran laser untuk mengesan jarak.

### Tambah sensor jarak ke CounterFit

Untuk menggunakan sensor jarak maya, anda perlu menambahkannya ke aplikasi CounterFit.

#### Tugasan - tambah sensor jarak ke CounterFit

Tambah sensor jarak ke aplikasi CounterFit.

1. Buka kod `fruit-quality-detector` dalam VS Code, dan pastikan persekitaran maya diaktifkan.

1. Pasang pakej Pip tambahan untuk memasang shim CounterFit yang boleh berkomunikasi dengan sensor jarak dengan mensimulasikan [pakej Pip rpi-vl53l0x](https://pypi.org/project/rpi-vl53l0x/), iaitu pakej Python yang berinteraksi dengan [sensor jarak masa-penerbangan VL53L0X](https://wiki.seeedstudio.com/Grove-Time_of_Flight_Distance_Sensor-VL53L0X/). Pastikan anda memasangnya dari terminal dengan persekitaran maya diaktifkan.

    ```sh
    pip install counterfit-shims-rpi-vl53l0x
    ```

1. Pastikan aplikasi web CounterFit sedang berjalan.

1. Cipta sensor jarak:

    1. Dalam kotak *Create sensor* di panel *Sensors*, klik menu dropdown *Sensor type* dan pilih *Distance*.

    1. Biarkan *Units* sebagai `Millimeter`.

    1. Sensor ini adalah sensor I²C, jadi tetapkan alamat kepada `0x29`. Jika anda menggunakan sensor VL53L0X fizikal, ia akan dikodkan keras kepada alamat ini.

    1. Pilih butang **Add** untuk mencipta sensor jarak.

    ![Tetapan sensor jarak](../../../../../translated_images/ms/counterfit-create-distance-sensor.967c9fb98f27888d95920c9784d004c972490eb71f70397fe13bd70a79a879a3.png)

    Sensor jarak akan dicipta dan muncul dalam senarai sensor.

    ![Sensor jarak dicipta](../../../../../translated_images/ms/counterfit-distance-sensor.079eefeeea0b68afc36431ce8fcbe2f09a7e4916ed1cd5cb30e696db53bc18fa.png)

## Programkan sensor jarak

Peranti IoT maya kini boleh diprogramkan untuk menggunakan sensor jarak yang disimulasikan.

### Tugasan - programkan sensor masa-penerbangan

1. Cipta fail baru dalam projek `fruit-quality-detector` bernama `distance-sensor.py`.

    > 💁 Cara mudah untuk mensimulasikan pelbagai peranti IoT adalah dengan melakukannya dalam fail Python yang berbeza, kemudian jalankan mereka pada masa yang sama.

1. Mulakan sambungan ke CounterFit dengan kod berikut:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Tambahkan kod berikut di bawah ini:

    ```python
    import time
    
    from counterfit_shims_rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Kod ini mengimport shim perpustakaan sensor untuk sensor masa-penerbangan VL53L0X.

1. Di bawah ini, tambahkan kod berikut untuk mengakses sensor:

    ```python
    distance_sensor = VL53L0X()
    distance_sensor.begin()
    ```

    Kod ini mengisytiharkan sensor jarak, kemudian memulakan sensor.

1. Akhir sekali, tambahkan gelung tak terhingga untuk membaca jarak:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Kod ini menunggu nilai sedia untuk dibaca dari sensor, kemudian mencetaknya ke konsol.

1. Jalankan kod ini.

    > 💁 Jangan lupa fail ini bernama `distance-sensor.py`! Pastikan untuk menjalankannya melalui Python, bukan `app.py`.

1. Anda akan melihat bacaan jarak muncul di konsol. Tukar nilai dalam CounterFit untuk melihat nilai ini berubah, atau gunakan nilai rawak.

    ```output
    (.venv) ➜  fruit-quality-detector python distance-sensor.py 
    Distance = 37 mm
    Distance = 42 mm
    Distance = 29 mm
    ```

> 💁 Anda boleh menemui kod ini dalam folder [code-proximity/virtual-iot-device](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/virtual-iot-device).

😀 Program sensor kedekatan anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.