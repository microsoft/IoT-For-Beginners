<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "70e5a428b607cd5a9a4f422c2a4df03d",
  "translation_date": "2025-08-27T21:30:00+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/virtual-device-temp.md",
  "language_code": "ms"
}
-->
# Mengukur suhu - Perkakasan IoT Maya

Dalam bahagian pelajaran ini, anda akan menambah sensor suhu pada peranti IoT maya anda.

## Perkakasan Maya

Peranti IoT maya akan menggunakan sensor Grove Digital Humidity and Temperature yang disimulasikan. Ini menjadikan makmal ini sama seperti menggunakan Raspberry Pi dengan sensor fizikal Grove DHT11.

Sensor ini menggabungkan **sensor suhu** dengan **sensor kelembapan**, tetapi dalam makmal ini anda hanya akan fokus pada komponen sensor suhu. Dalam peranti IoT fizikal, sensor suhu biasanya adalah [termistor](https://wikipedia.org/wiki/Thermistor) yang mengukur suhu dengan mengesan perubahan rintangan apabila suhu berubah. Sensor suhu biasanya adalah sensor digital yang secara dalaman menukar rintangan yang diukur kepada suhu dalam darjah Celsius (atau Kelvin, atau Fahrenheit).

### Tambah sensor pada CounterFit

Untuk menggunakan sensor kelembapan dan suhu maya, anda perlu menambah kedua-dua sensor ini pada aplikasi CounterFit.

#### Tugasan - tambah sensor pada CounterFit

Tambah sensor kelembapan dan suhu pada aplikasi CounterFit.

1. Cipta aplikasi Python baharu pada komputer anda dalam folder bernama `temperature-sensor` dengan satu fail bernama `app.py` dan persekitaran maya Python, serta tambahkan pakej pip CounterFit.

    > ⚠️ Anda boleh merujuk kepada [arahan untuk mencipta dan menyediakan projek Python CounterFit dalam pelajaran 1 jika diperlukan](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Pasang pakej Pip tambahan untuk memasang shim CounterFit bagi sensor DHT11. Pastikan anda memasangnya dari terminal dengan persekitaran maya diaktifkan.

    ```sh
    pip install counterfit-shims-seeed-python-dht
    ```

1. Pastikan aplikasi web CounterFit sedang berjalan.

1. Cipta sensor kelembapan:

    1. Dalam kotak *Create sensor* di panel *Sensors*, klik kotak *Sensor type* dan pilih *Humidity*.

    1. Biarkan *Units* ditetapkan kepada *Percentage*.

    1. Pastikan *Pin* ditetapkan kepada *5*.

    1. Pilih butang **Add** untuk mencipta sensor kelembapan pada Pin 5.

    ![Tetapan sensor kelembapan](../../../../../translated_images/ms/counterfit-create-humidity-sensor.2750e27b6f30e09cf4e22101defd5252710717620816ab41ba688f91f757c49a.png)

    Sensor kelembapan akan dicipta dan muncul dalam senarai sensor.

    ![Sensor kelembapan yang telah dicipta](../../../../../translated_images/ms/counterfit-humidity-sensor.7b12f7f339e430cb26c8211d2dba4ef75261b353a01da0932698b5bebd693f27.png)

1. Cipta sensor suhu:

    1. Dalam kotak *Create sensor* di panel *Sensors*, klik kotak *Sensor type* dan pilih *Temperature*.

    1. Biarkan *Units* ditetapkan kepada *Celsius*.

    1. Pastikan *Pin* ditetapkan kepada *6*.

    1. Pilih butang **Add** untuk mencipta sensor suhu pada Pin 6.

    ![Tetapan sensor suhu](../../../../../translated_images/ms/counterfit-create-temperature-sensor.199350ed34f7343d79dccbe95eaf6c11d2121f03d1c35ab9613b330c23f39b29.png)

    Sensor suhu akan dicipta dan muncul dalam senarai sensor.

    ![Sensor suhu yang telah dicipta](../../../../../translated_images/ms/counterfit-temperature-sensor.f0560236c96a9016bafce7f6f792476fe3367bc6941a1f7d5811d144d4bcbfff.png)

## Program aplikasi sensor suhu

Aplikasi sensor suhu kini boleh diprogramkan menggunakan sensor CounterFit.

### Tugasan - program aplikasi sensor suhu

Programkan aplikasi sensor suhu.

1. Pastikan aplikasi `temperature-sensor` dibuka dalam VS Code.

1. Buka fail `app.py`.

1. Tambahkan kod berikut di bahagian atas `app.py` untuk menyambungkan aplikasi ke CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Tambahkan kod berikut ke fail `app.py` untuk mengimport pustaka yang diperlukan:

    ```python
    import time
    from counterfit_shims_seeed_python_dht import DHT
    ```

    Pernyataan `from seeed_dht import DHT` mengimport kelas `DHT` untuk berinteraksi dengan sensor suhu Grove maya menggunakan shim dari modul `counterfit_shims_seeed_python_dht`.

1. Tambahkan kod berikut selepas kod di atas untuk mencipta satu instance kelas yang menguruskan sensor kelembapan dan suhu maya:

    ```python
    sensor = DHT("11", 5)
    ```

    Ini mengisytiharkan satu instance kelas `DHT` yang menguruskan sensor **D**igital **H**umidity dan **T**emperature maya. Parameter pertama memberitahu kod bahawa sensor yang digunakan adalah sensor *DHT11* maya. Parameter kedua memberitahu kod bahawa sensor disambungkan ke port `5`.

    > 💁 CounterFit mensimulasikan sensor kelembapan dan suhu gabungan ini dengan menyambung kepada 2 sensor, satu sensor kelembapan pada pin yang diberikan apabila kelas `DHT` dicipta, dan satu sensor suhu yang berjalan pada pin seterusnya. Jika sensor kelembapan berada pada pin 5, shim mengharapkan sensor suhu berada pada pin 6.

1. Tambahkan gelung tak terhingga selepas kod di atas untuk membaca nilai sensor suhu dan mencetaknya ke konsol:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    Panggilan kepada `sensor.read()` mengembalikan tuple kelembapan dan suhu. Anda hanya memerlukan nilai suhu, jadi kelembapan diabaikan. Nilai suhu kemudian dicetak ke konsol.

1. Tambahkan jeda kecil selama sepuluh saat di akhir `loop` kerana tahap suhu tidak perlu diperiksa secara berterusan. Jeda mengurangkan penggunaan kuasa peranti.

    ```python
    time.sleep(10)
    ```

1. Dari Terminal VS Code dengan persekitaran maya diaktifkan, jalankan arahan berikut untuk menjalankan aplikasi Python anda:

    ```sh
    python app.py
    ```

1. Dari aplikasi CounterFit, ubah nilai sensor suhu yang akan dibaca oleh aplikasi. Anda boleh melakukannya dengan dua cara:

    * Masukkan nombor dalam kotak *Value* untuk sensor suhu, kemudian pilih butang **Set**. Nombor yang anda masukkan akan menjadi nilai yang dikembalikan oleh sensor.

    * Tandakan kotak *Random*, dan masukkan nilai *Min* dan *Max*, kemudian pilih butang **Set**. Setiap kali sensor membaca nilai, ia akan membaca nombor rawak antara *Min* dan *Max*.

    Anda seharusnya melihat nilai yang anda tetapkan muncul di konsol. Ubah *Value* atau tetapan *Random* untuk melihat perubahan nilai.

    ```output
    (.venv) ➜  temperature-sensor python app.py
    Temperature 28.25°C
    Temperature 30.71°C
    Temperature 25.17°C
    ```

> 💁 Anda boleh menemui kod ini dalam folder [code-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/virtual-device).

😀 Program sensor suhu anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.