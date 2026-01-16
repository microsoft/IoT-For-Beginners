<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9d4d00a47d5d0f3e6ce42c0d1020064a",
  "translation_date": "2025-08-27T21:56:54+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/pi-soil-moisture.md",
  "language_code": "id"
}
-->
# Mengukur Kelembapan Tanah - Raspberry Pi

Dalam bagian pelajaran ini, Anda akan menambahkan sensor kelembapan tanah kapasitif ke Raspberry Pi, dan membaca nilai dari sensor tersebut.

## Perangkat Keras

Raspberry Pi membutuhkan sensor kelembapan tanah kapasitif.

Sensor yang akan Anda gunakan adalah [Capacitive Soil Moisture Sensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), yang mengukur kelembapan tanah dengan mendeteksi kapasitansi tanah, sebuah sifat yang berubah seiring perubahan kelembapan tanah. Ketika kelembapan tanah meningkat, tegangan akan menurun.

Sensor ini adalah sensor analog, sehingga menggunakan pin analog, dan ADC 10-bit di Grove Base Hat pada Pi untuk mengonversi tegangan menjadi sinyal digital dari 1-1.023. Sinyal ini kemudian dikirim melalui I²C menggunakan pin GPIO pada Pi.

### Hubungkan Sensor Kelembapan Tanah

Sensor kelembapan tanah Grove dapat dihubungkan ke Raspberry Pi.

#### Tugas - Hubungkan Sensor Kelembapan Tanah

Hubungkan sensor kelembapan tanah.

![Sensor kelembapan tanah Grove](../../../../../translated_images/id/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.png)

1. Masukkan salah satu ujung kabel Grove ke soket pada sensor kelembapan tanah. Kabel hanya dapat masuk dengan satu arah.

1. Dengan Raspberry Pi dalam keadaan mati, hubungkan ujung kabel Grove lainnya ke soket analog yang ditandai **A0** pada Grove Base Hat yang terpasang di Pi. Soket ini adalah soket kedua dari kanan, pada baris soket di sebelah pin GPIO.

![Sensor kelembapan tanah Grove terhubung ke soket A0](../../../../../translated_images/id/pi-soil-moisture-sensor.fdd7eb2393792cf6739cacf1985d9f55beda16d372f30d0b5a51d586f978a870.png)

1. Masukkan sensor kelembapan tanah ke dalam tanah. Sensor memiliki 'garis posisi tertinggi' - garis putih melintang pada sensor. Masukkan sensor hingga garis ini, tetapi jangan melebihi garis tersebut.

![Sensor kelembapan tanah Grove di dalam tanah](../../../../../translated_images/id/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

## Program Sensor Kelembapan Tanah

Raspberry Pi sekarang dapat diprogram untuk menggunakan sensor kelembapan tanah yang terpasang.

### Tugas - Program Sensor Kelembapan Tanah

Program perangkat.

1. Nyalakan Pi dan tunggu hingga selesai booting.

1. Luncurkan VS Code, baik langsung di Pi, atau sambungkan melalui ekstensi Remote SSH.

    > ⚠️ Anda dapat merujuk ke [instruksi untuk menyiapkan dan meluncurkan VS Code di nightlight - pelajaran 1 jika diperlukan](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Dari terminal, buat folder baru di direktori home pengguna `pi` bernama `soil-moisture-sensor`. Buat file di folder ini bernama `app.py`.

1. Buka folder ini di VS Code.

1. Tambahkan kode berikut ke file `app.py` untuk mengimpor beberapa pustaka yang diperlukan:

    ```python
    import time
    from grove.adc import ADC
    ```

    Pernyataan `import time` mengimpor modul `time` yang akan digunakan nanti dalam tugas ini.

    Pernyataan `from grove.adc import ADC` mengimpor `ADC` dari pustaka Python Grove. Pustaka ini memiliki kode untuk berinteraksi dengan konverter analog ke digital pada Pi Base Hat dan membaca tegangan dari sensor analog.

1. Tambahkan kode berikut di bawah ini untuk membuat instance dari kelas `ADC`:

    ```python
    adc = ADC()
    ```

1. Tambahkan loop tak terbatas yang membaca dari ADC ini pada pin A0, dan menulis hasilnya ke konsol. Loop ini kemudian dapat tidur selama 10 detik di antara pembacaan.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)

        time.sleep(10)
    ```

1. Jalankan aplikasi Python. Anda akan melihat pengukuran kelembapan tanah ditulis ke konsol. Tambahkan air ke tanah, atau keluarkan sensor dari tanah, dan lihat nilai berubah.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

    Dalam contoh output di atas, Anda dapat melihat tegangan turun saat air ditambahkan.

> 💁 Anda dapat menemukan kode ini di folder [code/pi](../../../../../2-farm/lessons/2-detect-soil-moisture/code/pi).

😀 Program sensor kelembapan tanah Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.