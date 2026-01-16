<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "11f10c6760fb8202cf368422702fdf70",
  "translation_date": "2025-08-27T22:34:19+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-sensor.md",
  "language_code": "id"
}
-->
# Membangun Lampu Malam - Perangkat IoT Virtual

Dalam bagian pelajaran ini, Anda akan menambahkan sensor cahaya ke perangkat IoT virtual Anda.

## Perangkat Keras Virtual

Lampu malam membutuhkan satu sensor, yang dibuat di aplikasi CounterFit.

Sensor tersebut adalah **sensor cahaya**. Pada perangkat IoT fisik, sensor ini akan berupa [fotodioda](https://wikipedia.org/wiki/Photodiode) yang mengubah cahaya menjadi sinyal listrik. Sensor cahaya adalah sensor analog yang mengirimkan nilai integer yang menunjukkan jumlah relatif cahaya, yang tidak sesuai dengan satuan pengukuran standar seperti [lux](https://wikipedia.org/wiki/Lux).

### Menambahkan Sensor ke CounterFit

Untuk menggunakan sensor cahaya virtual, Anda perlu menambahkannya ke aplikasi CounterFit.

#### Tugas - Menambahkan Sensor ke CounterFit

Tambahkan sensor cahaya ke aplikasi CounterFit.

1. Pastikan aplikasi web CounterFit berjalan dari bagian sebelumnya dalam tugas ini. Jika tidak, jalankan kembali.

1. Buat sensor cahaya:

    1. Di kotak *Create sensor* pada panel *Sensors*, buka menu dropdown *Sensor type* dan pilih *Light*.

    1. Biarkan *Units* tetap diatur ke *NoUnits*.

    1. Pastikan *Pin* diatur ke *0*.

    1. Pilih tombol **Add** untuk membuat sensor cahaya pada Pin 0.

    ![Pengaturan sensor cahaya](../../../../../translated_images/id/counterfit-create-light-sensor.9f36a5e0d4458d8d554d54b34d2c806d56093d6e49fddcda2d20f6fef7f5cce1.png)

    Sensor cahaya akan dibuat dan muncul di daftar sensor.

    ![Sensor cahaya dibuat](../../../../../translated_images/id/counterfit-light-sensor.5d0f5584df56b90f6b2561910d9cb20dfbd73eeff2177c238d38f4de54aefae1.png)

## Memprogram Sensor Cahaya

Perangkat sekarang dapat diprogram untuk menggunakan sensor cahaya bawaan.

### Tugas - Memprogram Sensor Cahaya

Program perangkat Anda.

1. Buka proyek lampu malam di VS Code yang Anda buat pada bagian sebelumnya dalam tugas ini. Matikan dan buat ulang terminal untuk memastikan terminal berjalan menggunakan lingkungan virtual jika diperlukan.

1. Buka file `app.py`.

1. Tambahkan kode berikut ke bagian atas file `app.py` bersama dengan pernyataan `import` lainnya untuk mengimpor beberapa pustaka yang diperlukan:

    ```python
    import time
    from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    Pernyataan `import time` mengimpor modul Python `time` yang akan digunakan nanti dalam tugas ini.

    Pernyataan `from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor` mengimpor `GroveLightSensor` dari pustaka Python CounterFit Grove shim. Pustaka ini memiliki kode untuk berinteraksi dengan sensor cahaya yang dibuat di aplikasi CounterFit.

1. Tambahkan kode berikut ke bagian bawah file untuk membuat instance dari kelas yang mengelola sensor cahaya:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    Baris `light_sensor = GroveLightSensor(0)` membuat instance dari kelas `GroveLightSensor` yang terhubung ke pin **0** - pin CounterFit Grove tempat sensor cahaya terhubung.

1. Tambahkan loop tak terbatas setelah kode di atas untuk membaca nilai sensor cahaya dan mencetaknya ke konsol:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Ini akan membaca tingkat cahaya saat ini menggunakan properti `light` dari kelas `GroveLightSensor`. Properti ini membaca nilai analog dari pin. Nilai ini kemudian dicetak ke konsol.

1. Tambahkan jeda kecil selama satu detik di akhir `while` loop karena tingkat cahaya tidak perlu diperiksa secara terus-menerus. Jeda ini mengurangi konsumsi daya perangkat.

    ```python
    time.sleep(1)
    ```

1. Dari Terminal VS Code, jalankan perintah berikut untuk menjalankan aplikasi Python Anda:

    ```sh
    python3 app.py
    ```

    Nilai cahaya akan ditampilkan di konsol. Awalnya, nilai ini akan menjadi 0.

1. Dari aplikasi CounterFit, ubah nilai sensor cahaya yang akan dibaca oleh aplikasi. Anda dapat melakukannya dengan dua cara:

    * Masukkan angka di kotak *Value* untuk sensor cahaya, lalu pilih tombol **Set**. Angka yang Anda masukkan akan menjadi nilai yang dikembalikan oleh sensor.

    * Centang kotak *Random*, dan masukkan nilai *Min* dan *Max*, lalu pilih tombol **Set**. Setiap kali sensor membaca nilai, sensor akan membaca angka acak antara *Min* dan *Max*.

    Nilai yang Anda atur akan ditampilkan di konsol. Ubah *Value* atau pengaturan *Random* untuk membuat nilai berubah.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

> 💁 Anda dapat menemukan kode ini di folder [code-sensor/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/virtual-device).

😀 Program lampu malam Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.