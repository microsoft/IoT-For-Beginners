<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "70e5a428b607cd5a9a4f422c2a4df03d",
  "translation_date": "2025-08-27T21:29:41+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/virtual-device-temp.md",
  "language_code": "id"
}
-->
# Mengukur Suhu - Perangkat IoT Virtual

Dalam bagian pelajaran ini, Anda akan menambahkan sensor suhu ke perangkat IoT virtual Anda.

## Perangkat Virtual

Perangkat IoT virtual akan menggunakan sensor simulasi Grove Digital Humidity and Temperature. Ini membuat lab ini tetap sama seperti menggunakan Raspberry Pi dengan sensor fisik Grove DHT11.

Sensor ini menggabungkan **sensor suhu** dengan **sensor kelembapan**, tetapi dalam lab ini Anda hanya akan fokus pada komponen sensor suhu. Pada perangkat IoT fisik, sensor suhu biasanya berupa [termistor](https://wikipedia.org/wiki/Thermistor) yang mengukur suhu dengan mendeteksi perubahan resistansi seiring perubahan suhu. Sensor suhu biasanya merupakan sensor digital yang secara internal mengonversi resistansi yang terukur menjadi suhu dalam derajat Celsius (atau Kelvin, atau Fahrenheit).

### Menambahkan Sensor ke CounterFit

Untuk menggunakan sensor kelembapan dan suhu virtual, Anda perlu menambahkan kedua sensor tersebut ke aplikasi CounterFit.

#### Tugas - Menambahkan Sensor ke CounterFit

Tambahkan sensor kelembapan dan suhu ke aplikasi CounterFit.

1. Buat aplikasi Python baru di komputer Anda dalam folder bernama `temperature-sensor` dengan satu file bernama `app.py` dan lingkungan virtual Python, lalu tambahkan paket pip CounterFit.

    > ⚠️ Anda dapat merujuk ke [instruksi untuk membuat dan mengatur proyek Python CounterFit di pelajaran 1 jika diperlukan](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Instal paket Pip tambahan untuk menginstal shim CounterFit untuk sensor DHT11. Pastikan Anda menginstalnya dari terminal dengan lingkungan virtual yang diaktifkan.

    ```sh
    pip install counterfit-shims-seeed-python-dht
    ```

1. Pastikan aplikasi web CounterFit sedang berjalan.

1. Buat sensor kelembapan:

    1. Di kotak *Create sensor* pada panel *Sensors*, buka menu dropdown *Sensor type* dan pilih *Humidity*.

    1. Biarkan *Units* tetap diatur ke *Percentage*.

    1. Pastikan *Pin* diatur ke *5*.

    1. Pilih tombol **Add** untuk membuat sensor kelembapan pada Pin 5.

    ![Pengaturan sensor kelembapan](../../../../../translated_images/id/counterfit-create-humidity-sensor.2750e27b6f30e09cf4e22101defd5252710717620816ab41ba688f91f757c49a.png)

    Sensor kelembapan akan dibuat dan muncul di daftar sensor.

    ![Sensor kelembapan dibuat](../../../../../translated_images/id/counterfit-humidity-sensor.7b12f7f339e430cb26c8211d2dba4ef75261b353a01da0932698b5bebd693f27.png)

1. Buat sensor suhu:

    1. Di kotak *Create sensor* pada panel *Sensors*, buka menu dropdown *Sensor type* dan pilih *Temperature*.

    1. Biarkan *Units* tetap diatur ke *Celsius*.

    1. Pastikan *Pin* diatur ke *6*.

    1. Pilih tombol **Add** untuk membuat sensor suhu pada Pin 6.

    ![Pengaturan sensor suhu](../../../../../translated_images/id/counterfit-create-temperature-sensor.199350ed34f7343d79dccbe95eaf6c11d2121f03d1c35ab9613b330c23f39b29.png)

    Sensor suhu akan dibuat dan muncul di daftar sensor.

    ![Sensor suhu dibuat](../../../../../translated_images/id/counterfit-temperature-sensor.f0560236c96a9016bafce7f6f792476fe3367bc6941a1f7d5811d144d4bcbfff.png)

## Memprogram Aplikasi Sensor Suhu

Aplikasi sensor suhu sekarang dapat diprogram menggunakan sensor CounterFit.

### Tugas - Memprogram Aplikasi Sensor Suhu

Program aplikasi sensor suhu.

1. Pastikan aplikasi `temperature-sensor` terbuka di VS Code.

1. Buka file `app.py`.

1. Tambahkan kode berikut ke bagian atas `app.py` untuk menghubungkan aplikasi ke CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Tambahkan kode berikut ke file `app.py` untuk mengimpor pustaka yang diperlukan:

    ```python
    import time
    from counterfit_shims_seeed_python_dht import DHT
    ```

    Pernyataan `from seeed_dht import DHT` mengimpor kelas `DHT` untuk berinteraksi dengan sensor suhu Grove virtual menggunakan shim dari modul `counterfit_shims_seeed_python_dht`.

1. Tambahkan kode berikut setelah kode di atas untuk membuat instance kelas yang mengelola sensor kelembapan dan suhu virtual:

    ```python
    sensor = DHT("11", 5)
    ```

    Ini mendeklarasikan instance dari kelas `DHT` yang mengelola sensor **D**igital **H**umidity dan **T**emperature virtual. Parameter pertama memberi tahu kode bahwa sensor yang digunakan adalah sensor virtual *DHT11*. Parameter kedua memberi tahu kode bahwa sensor terhubung ke port `5`.

    > 💁 CounterFit mensimulasikan sensor kelembapan dan suhu gabungan ini dengan menghubungkan ke 2 sensor, sensor kelembapan pada pin yang diberikan saat kelas `DHT` dibuat, dan sensor suhu yang berjalan pada pin berikutnya. Jika sensor kelembapan ada di pin 5, shim mengharapkan sensor suhu berada di pin 6.

1. Tambahkan loop tak terbatas setelah kode di atas untuk membaca nilai sensor suhu dan mencetaknya ke konsol:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    Panggilan ke `sensor.read()` mengembalikan tuple kelembapan dan suhu. Anda hanya memerlukan nilai suhu, jadi nilai kelembapan diabaikan. Nilai suhu kemudian dicetak ke konsol.

1. Tambahkan jeda kecil selama sepuluh detik di akhir `loop` karena tingkat suhu tidak perlu diperiksa secara terus-menerus. Jeda ini mengurangi konsumsi daya perangkat.

    ```python
    time.sleep(10)
    ```

1. Dari Terminal VS Code dengan lingkungan virtual yang diaktifkan, jalankan perintah berikut untuk menjalankan aplikasi Python Anda:

    ```sh
    python app.py
    ```

1. Dari aplikasi CounterFit, ubah nilai sensor suhu yang akan dibaca oleh aplikasi. Anda dapat melakukannya dengan dua cara:

    * Masukkan angka di kotak *Value* untuk sensor suhu, lalu pilih tombol **Set**. Angka yang Anda masukkan akan menjadi nilai yang dikembalikan oleh sensor.

    * Centang kotak *Random*, lalu masukkan nilai *Min* dan *Max*, kemudian pilih tombol **Set**. Setiap kali sensor membaca nilai, sensor akan membaca angka acak antara *Min* dan *Max*.

    Anda seharusnya melihat nilai yang Anda atur muncul di konsol. Ubah pengaturan *Value* atau *Random* untuk melihat nilai berubah.

    ```output
    (.venv) ➜  temperature-sensor python app.py
    Temperature 28.25°C
    Temperature 30.71°C
    Temperature 25.17°C
    ```

> 💁 Anda dapat menemukan kode ini di folder [code-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/virtual-device).

😀 Program sensor suhu Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.