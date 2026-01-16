<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "11f10c6760fb8202cf368422702fdf70",
  "translation_date": "2025-08-27T22:34:33+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-sensor.md",
  "language_code": "ms"
}
-->
# Bina Lampu Malam - Perkakasan IoT Maya

Dalam bahagian pelajaran ini, anda akan menambah sensor cahaya pada peranti IoT maya anda.

## Perkakasan Maya

Lampu malam memerlukan satu sensor, yang dicipta dalam aplikasi CounterFit.

Sensor tersebut ialah **sensor cahaya**. Dalam peranti IoT fizikal, ia akan menjadi [fotodiod](https://wikipedia.org/wiki/Photodiode) yang menukar cahaya kepada isyarat elektrik. Sensor cahaya adalah sensor analog yang menghantar nilai integer yang menunjukkan jumlah cahaya relatif, yang tidak memetakan kepada sebarang unit piawai seperti [lux](https://wikipedia.org/wiki/Lux).

### Tambah sensor ke CounterFit

Untuk menggunakan sensor cahaya maya, anda perlu menambahkannya ke aplikasi CounterFit.

#### Tugasan - tambah sensor ke CounterFit

Tambah sensor cahaya ke aplikasi CounterFit.

1. Pastikan aplikasi web CounterFit sedang berjalan dari bahagian tugasan sebelumnya. Jika tidak, mulakan ia.

1. Cipta sensor cahaya:

    1. Dalam kotak *Create sensor* di panel *Sensors*, klik kotak dropdown *Sensor type* dan pilih *Light*.

    1. Biarkan *Units* ditetapkan kepada *NoUnits*.

    1. Pastikan *Pin* ditetapkan kepada *0*.

    1. Pilih butang **Add** untuk mencipta sensor cahaya pada Pin 0.

    ![Tetapan sensor cahaya](../../../../../translated_images/ms/counterfit-create-light-sensor.9f36a5e0d4458d8d554d54b34d2c806d56093d6e49fddcda2d20f6fef7f5cce1.png)

    Sensor cahaya akan dicipta dan muncul dalam senarai sensor.

    ![Sensor cahaya dicipta](../../../../../translated_images/ms/counterfit-light-sensor.5d0f5584df56b90f6b2561910d9cb20dfbd73eeff2177c238d38f4de54aefae1.png)

## Programkan sensor cahaya

Peranti kini boleh diprogramkan untuk menggunakan sensor cahaya terbina.

### Tugasan - programkan sensor cahaya

Programkan peranti.

1. Buka projek lampu malam dalam VS Code yang anda cipta dalam bahagian tugasan sebelumnya. Matikan dan cipta semula terminal untuk memastikan ia berjalan menggunakan persekitaran maya jika perlu.

1. Buka fail `app.py`.

1. Tambahkan kod berikut di bahagian atas fail `app.py` bersama dengan pernyataan `import` lain untuk mengimport beberapa pustaka yang diperlukan:

    ```python
    import time
    from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    Pernyataan `import time` mengimport modul Python `time` yang akan digunakan kemudian dalam tugasan ini.

    Pernyataan `from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor` mengimport `GroveLightSensor` daripada pustaka Python CounterFit Grove shim. Pustaka ini mengandungi kod untuk berinteraksi dengan sensor cahaya yang dicipta dalam aplikasi CounterFit.

1. Tambahkan kod berikut di bahagian bawah fail untuk mencipta instance kelas yang menguruskan sensor cahaya:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    Baris `light_sensor = GroveLightSensor(0)` mencipta instance kelas `GroveLightSensor` yang disambungkan ke pin **0** - pin CounterFit Grove yang disambungkan kepada sensor cahaya.

1. Tambahkan gelung tak terhingga selepas kod di atas untuk membaca nilai sensor cahaya dan mencetaknya ke konsol:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Ini akan membaca tahap cahaya semasa menggunakan sifat `light` daripada kelas `GroveLightSensor`. Sifat ini membaca nilai analog daripada pin. Nilai ini kemudian dicetak ke konsol.

1. Tambahkan jeda kecil selama satu saat di akhir gelung `while` kerana tahap cahaya tidak perlu diperiksa secara berterusan. Jeda ini mengurangkan penggunaan kuasa peranti.

    ```python
    time.sleep(1)
    ```

1. Dari Terminal VS Code, jalankan arahan berikut untuk menjalankan aplikasi Python anda:

    ```sh
    python3 app.py
    ```

    Nilai cahaya akan dipaparkan di konsol. Pada mulanya, nilai ini akan menjadi 0.

1. Dari aplikasi CounterFit, ubah nilai sensor cahaya yang akan dibaca oleh aplikasi. Anda boleh melakukannya dengan dua cara:

    * Masukkan nombor dalam kotak *Value* untuk sensor cahaya, kemudian pilih butang **Set**. Nombor yang anda masukkan akan menjadi nilai yang dikembalikan oleh sensor.

    * Tandakan kotak *Random*, dan masukkan nilai *Min* dan *Max*, kemudian pilih butang **Set**. Setiap kali sensor membaca nilai, ia akan membaca nombor rawak antara *Min* dan *Max*.

    Nilai yang anda tetapkan akan dipaparkan di konsol. Ubah *Value* atau tetapan *Random* untuk membuat nilai berubah.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

> 💁 Anda boleh menemui kod ini dalam folder [code-sensor/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/virtual-device).

😀 Program lampu malam anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.