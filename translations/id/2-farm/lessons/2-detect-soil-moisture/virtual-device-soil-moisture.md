<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2bf65f162bcebd35fbcba5fd245afac4",
  "translation_date": "2025-08-27T21:55:42+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/virtual-device-soil-moisture.md",
  "language_code": "id"
}
-->
# Mengukur Kelembapan Tanah - Perangkat Keras IoT Virtual

Dalam bagian pelajaran ini, Anda akan menambahkan sensor kelembapan tanah kapasitif ke perangkat IoT virtual Anda, dan membaca nilai dari sensor tersebut.

## Perangkat Keras Virtual

Perangkat IoT virtual akan menggunakan simulasi sensor kelembapan tanah kapasitif Grove. Ini membuat lab ini tetap sama seperti menggunakan Raspberry Pi dengan sensor kelembapan tanah kapasitif Grove fisik.

Pada perangkat IoT fisik, sensor kelembapan tanah adalah sensor kapasitif yang mengukur kelembapan tanah dengan mendeteksi kapasitansi tanah, sebuah sifat yang berubah seiring dengan perubahan kelembapan tanah. Ketika kelembapan tanah meningkat, tegangan akan menurun.

Ini adalah sensor analog, sehingga menggunakan ADC 10-bit yang disimulasikan untuk melaporkan nilai dari 1-1.023.

### Menambahkan Sensor Kelembapan Tanah ke CounterFit

Untuk menggunakan sensor kelembapan tanah virtual, Anda perlu menambahkannya ke aplikasi CounterFit.

#### Tugas - Menambahkan Sensor Kelembapan Tanah ke CounterFit

Tambahkan sensor kelembapan tanah ke aplikasi CounterFit.

1. Buat aplikasi Python baru di komputer Anda dalam folder bernama `soil-moisture-sensor` dengan satu file bernama `app.py` dan lingkungan virtual Python, lalu tambahkan paket pip CounterFit.

    > ⚠️ Anda dapat merujuk ke [instruksi untuk membuat dan mengatur proyek Python CounterFit di pelajaran 1 jika diperlukan](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Pastikan aplikasi web CounterFit sedang berjalan.

1. Buat sensor kelembapan tanah:

    1. Di kotak *Create sensor* pada panel *Sensors*, buka menu dropdown *Sensor type* dan pilih *Soil Moisture*.

    1. Biarkan *Units* tetap diatur ke *NoUnits*.

    1. Pastikan *Pin* diatur ke *0*.

    1. Pilih tombol **Add** untuk membuat sensor *Soil Moisture* pada Pin 0.

    ![Pengaturan sensor kelembapan tanah](../../../../../translated_images/id/counterfit-create-soil-moisture-sensor.35266135a5e0ae68b29a684d7db0d2933a8098b2307d197f7c71577b724603aa.png)

    Sensor kelembapan tanah akan dibuat dan muncul di daftar sensor.

    ![Sensor kelembapan tanah telah dibuat](../../../../../translated_images/id/counterfit-soil-moisture-sensor.81742b2de0e9de60a3b3b9a2ff8ecc686d428eb6d71820f27a693be26e5aceee.png)

## Memprogram Aplikasi Sensor Kelembapan Tanah

Aplikasi sensor kelembapan tanah sekarang dapat diprogram menggunakan sensor CounterFit.

### Tugas - Memprogram Aplikasi Sensor Kelembapan Tanah

Program aplikasi sensor kelembapan tanah.

1. Pastikan aplikasi `soil-moisture-sensor` terbuka di VS Code.

1. Buka file `app.py`.

1. Tambahkan kode berikut di bagian atas `app.py` untuk menghubungkan aplikasi ke CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Tambahkan kode berikut ke file `app.py` untuk mengimpor beberapa pustaka yang diperlukan:

    ```python
    import time
    from counterfit_shims_grove.adc import ADC
    ```

    Pernyataan `import time` mengimpor modul `time` yang akan digunakan nanti dalam tugas ini.

    Pernyataan `from counterfit_shims_grove.adc import ADC` mengimpor kelas `ADC` untuk berinteraksi dengan konverter analog ke digital virtual yang dapat terhubung ke sensor CounterFit.

1. Tambahkan kode berikut di bawah ini untuk membuat instance dari kelas `ADC`:

    ```python
    adc = ADC()
    ```

1. Tambahkan loop tak terbatas yang membaca dari ADC ini pada pin 0 dan menuliskan hasilnya ke konsol. Loop ini kemudian dapat berhenti selama 10 detik di antara pembacaan.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)
    
        time.sleep(10)
    ```

1. Dari aplikasi CounterFit, ubah nilai sensor kelembapan tanah yang akan dibaca oleh aplikasi. Anda dapat melakukannya dengan dua cara:

    * Masukkan angka di kotak *Value* untuk sensor kelembapan tanah, lalu pilih tombol **Set**. Angka yang Anda masukkan akan menjadi nilai yang dikembalikan oleh sensor.

    * Centang kotak *Random*, dan masukkan nilai *Min* dan *Max*, lalu pilih tombol **Set**. Setiap kali sensor membaca nilai, sensor akan membaca angka acak antara *Min* dan *Max*.

1. Jalankan aplikasi Python. Anda akan melihat pengukuran kelembapan tanah ditulis ke konsol. Ubah pengaturan *Value* atau *Random* untuk melihat perubahan nilai.

    ```output
    (.venv) ➜ soil-moisture-sensor $ python app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

> 💁 Anda dapat menemukan kode ini di folder [code/virtual-device](../../../../../2-farm/lessons/2-detect-soil-moisture/code/virtual-device).

😀 Program sensor kelembapan tanah Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.