<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ea733bd0cdf2479e082373f765a08678",
  "translation_date": "2025-08-27T22:24:28+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-sensor.md",
  "language_code": "id"
}
-->
# Membuat Lampu Malam - Raspberry Pi

Dalam bagian pelajaran ini, Anda akan menambahkan sensor cahaya ke Raspberry Pi Anda.

## Perangkat Keras

Sensor untuk pelajaran ini adalah **sensor cahaya** yang menggunakan [fotodioda](https://wikipedia.org/wiki/Photodiode) untuk mengubah cahaya menjadi sinyal listrik. Ini adalah sensor analog yang mengirimkan nilai integer dari 0 hingga 1.000 yang menunjukkan jumlah relatif cahaya, tetapi tidak sesuai dengan satuan pengukuran standar seperti [lux](https://wikipedia.org/wiki/Lux).

Sensor cahaya ini adalah sensor Grove eksternal dan perlu dihubungkan ke Grove Base hat pada Raspberry Pi.

### Hubungkan Sensor Cahaya

Sensor cahaya Grove yang digunakan untuk mendeteksi tingkat cahaya perlu dihubungkan ke Raspberry Pi.

#### Tugas - Hubungkan Sensor Cahaya

Hubungkan sensor cahaya.

![Sensor cahaya Grove](../../../../../translated_images/id/grove-light-sensor.b8127b7c434e632d6bcdb57587a14e9ef69a268a22df95d08628f62b8fa5505c.png)

1. Masukkan salah satu ujung kabel Grove ke soket pada modul sensor cahaya. Kabel hanya dapat masuk dengan satu arah.

1. Dengan Raspberry Pi dalam keadaan mati, hubungkan ujung lain kabel Grove ke soket analog yang diberi tanda **A0** pada Grove Base hat yang terpasang pada Pi. Soket ini adalah soket kedua dari kanan, pada baris soket di sebelah pin GPIO.

![Sensor cahaya Grove terhubung ke soket A0](../../../../../translated_images/id/pi-light-sensor.66cc1e31fa48cd7d5f23400d4b2119aa41508275cb7c778053a7923b4e972d7e.png)

## Program Sensor Cahaya

Perangkat sekarang dapat diprogram menggunakan sensor cahaya Grove.

### Tugas - Program Sensor Cahaya

Program perangkat.

1. Nyalakan Pi dan tunggu hingga selesai booting.

1. Buka proyek lampu malam di VS Code yang telah Anda buat pada bagian sebelumnya dari tugas ini, baik langsung di Pi atau terhubung menggunakan ekstensi Remote SSH.

1. Buka file `app.py` dan hapus semua kode di dalamnya.

1. Tambahkan kode berikut ke file `app.py` untuk mengimpor beberapa pustaka yang diperlukan:

    ```python
    import time
    from grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    Pernyataan `import time` mengimpor modul `time` yang akan digunakan nanti dalam tugas ini.

    Pernyataan `from grove.grove_light_sensor_v1_2 import GroveLightSensor` mengimpor `GroveLightSensor` dari pustaka Python Grove. Pustaka ini memiliki kode untuk berinteraksi dengan sensor cahaya Grove, dan telah diinstal secara global selama pengaturan Pi.

1. Tambahkan kode berikut setelah kode di atas untuk membuat instance dari kelas yang mengelola sensor cahaya:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    Baris `light_sensor = GroveLightSensor(0)` membuat instance dari kelas `GroveLightSensor` yang terhubung ke pin **A0** - pin analog Grove tempat sensor cahaya terhubung.

1. Tambahkan loop tak terbatas setelah kode di atas untuk membaca nilai sensor cahaya dan mencetaknya ke konsol:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Ini akan membaca tingkat cahaya saat ini dalam skala 0-1.023 menggunakan properti `light` dari kelas `GroveLightSensor`. Properti ini membaca nilai analog dari pin. Nilai ini kemudian dicetak ke konsol.

1. Tambahkan jeda kecil selama satu detik di akhir `loop` karena tingkat cahaya tidak perlu diperiksa secara terus-menerus. Jeda ini mengurangi konsumsi daya perangkat.

    ```python
    time.sleep(1)
    ```

1. Dari Terminal VS Code, jalankan perintah berikut untuk menjalankan aplikasi Python Anda:

    ```sh
    python3 app.py
    ```

    Nilai cahaya akan ditampilkan di konsol. Tutup dan buka sensor cahaya, dan nilai akan berubah:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

> 💁 Anda dapat menemukan kode ini di folder [code-sensor/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/pi).

😀 Menambahkan sensor ke program lampu malam Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.