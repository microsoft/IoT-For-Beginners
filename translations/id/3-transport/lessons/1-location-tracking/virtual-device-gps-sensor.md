<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64f18a8f8aaa1fef5e7320e0992d8b3a",
  "translation_date": "2025-08-27T23:40:37+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/virtual-device-gps-sensor.md",
  "language_code": "id"
}
-->
# Membaca Data GPS - Perangkat IoT Virtual

Dalam bagian pelajaran ini, Anda akan menambahkan sensor GPS ke perangkat IoT virtual Anda, dan membaca nilai-nilainya.

## Perangkat Virtual

Perangkat IoT virtual akan menggunakan sensor GPS yang disimulasikan, yang dapat diakses melalui UART melalui port serial.

Sensor GPS fisik memiliki antena untuk menangkap gelombang radio dari satelit GPS, dan mengubah sinyal GPS menjadi data GPS. Versi virtual mensimulasikan ini dengan memungkinkan Anda untuk mengatur lintang dan bujur, mengirim kalimat NMEA mentah, atau mengunggah file GPX dengan beberapa lokasi yang dapat dikembalikan secara berurutan.

> 🎓 Kalimat NMEA akan dibahas lebih lanjut dalam pelajaran ini

### Menambahkan Sensor ke CounterFit

Untuk menggunakan sensor GPS virtual, Anda perlu menambahkannya ke aplikasi CounterFit.

#### Tugas - Menambahkan Sensor ke CounterFit

Tambahkan sensor GPS ke aplikasi CounterFit.

1. Buat aplikasi Python baru di komputer Anda dalam folder bernama `gps-sensor` dengan satu file bernama `app.py` dan lingkungan virtual Python, lalu tambahkan paket pip CounterFit.

    > ⚠️ Anda dapat merujuk ke [instruksi untuk membuat dan mengatur proyek Python CounterFit di pelajaran 1 jika diperlukan](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Instal paket Pip tambahan untuk menginstal shim CounterFit yang dapat berkomunikasi dengan sensor berbasis UART melalui koneksi serial. Pastikan Anda menginstalnya dari terminal dengan lingkungan virtual yang diaktifkan.

    ```sh
    pip install counterfit-shims-serial
    ```

1. Pastikan aplikasi web CounterFit sedang berjalan.

1. Buat sensor GPS:

    1. Di kotak *Create sensor* pada panel *Sensors*, klik dropdown pada kotak *Sensor type* dan pilih *UART GPS*.

    1. Biarkan *Port* tetap diatur ke */dev/ttyAMA0*

    1. Pilih tombol **Add** untuk membuat sensor GPS pada port `/dev/ttyAMA0`.

    ![Pengaturan sensor GPS](../../../../../translated_images/id/counterfit-create-gps-sensor.6385dc9357d85ad1d47b4abb2525e7651fd498917d25eefc5a72feab09eedc70.png)

    Sensor GPS akan dibuat dan muncul dalam daftar sensor.

    ![Sensor GPS telah dibuat](../../../../../translated_images/id/counterfit-gps-sensor.3fbb15af0a5367566f2f11324ef5a6f30861cdf2b497071a5e002b7aa473550e.png)

## Memprogram Sensor GPS

Perangkat IoT virtual sekarang dapat diprogram untuk menggunakan sensor GPS virtual.

### Tugas - Memprogram Sensor GPS

Program aplikasi sensor GPS.

1. Pastikan aplikasi `gps-sensor` terbuka di VS Code.

1. Buka file `app.py`.

1. Tambahkan kode berikut di bagian atas `app.py` untuk menghubungkan aplikasi ke CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Tambahkan kode berikut di bawahnya untuk mengimpor beberapa pustaka yang diperlukan, termasuk pustaka untuk port serial CounterFit:

    ```python
    import time
    import counterfit_shims_serial
    
    serial = counterfit_shims_serial.Serial('/dev/ttyAMA0')
    ```

    Kode ini mengimpor modul `serial` dari paket Pip `counterfit_shims_serial`. Kemudian menghubungkan ke port serial `/dev/ttyAMA0` - ini adalah alamat port serial yang digunakan sensor GPS virtual untuk port UART-nya.

1. Tambahkan kode berikut di bawahnya untuk membaca dari port serial dan mencetak nilai ke konsol:

    ```python
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    Fungsi bernama `print_gps_data` didefinisikan untuk mencetak baris yang diteruskan kepadanya ke konsol.

    Selanjutnya, kode melakukan loop tanpa henti, membaca sebanyak mungkin baris teks dari port serial dalam setiap loop. Fungsi `print_gps_data` dipanggil untuk setiap baris.

    Setelah semua data dibaca, loop akan tidur selama 1 detik, lalu mencoba lagi.

1. Jalankan kode ini, pastikan Anda menggunakan terminal yang berbeda dari yang digunakan aplikasi CounterFit agar aplikasi CounterFit tetap berjalan.

1. Dari aplikasi CounterFit, ubah nilai sensor GPS. Anda dapat melakukannya dengan salah satu cara berikut:

    * Atur **Source** ke `Lat/Lon`, dan tetapkan lintang, bujur, dan jumlah satelit yang digunakan untuk mendapatkan posisi GPS. Nilai ini hanya akan dikirim sekali, jadi centang kotak **Repeat** agar data dikirim ulang setiap detik.

      ![Sensor GPS dengan lat lon dipilih](../../../../../translated_images/id/counterfit-gps-sensor-latlon.008c867d75464fbe7f84107cc57040df565ac07cb57d2f21db37d087d470197d.png)

    * Atur **Source** ke `NMEA` dan tambahkan beberapa kalimat NMEA ke kotak teks. Semua nilai ini akan dikirim, dengan jeda 1 detik sebelum setiap kalimat GGA (posisi) baru dapat dibaca.

      ![Sensor GPS dengan kalimat NMEA diatur](../../../../../translated_images/id/counterfit-gps-sensor-nmea.c62eea442171e17e19528b051b104cfcecdc9cd18db7bc72920f29821ae63f73.png)

      Anda dapat menggunakan alat seperti [nmeagen.org](https://www.nmeagen.org) untuk menghasilkan kalimat ini dengan menggambar di peta. Nilai-nilai ini hanya akan dikirim sekali, jadi centang kotak **Repeat** agar data dikirim ulang satu detik setelah semuanya dikirim.

    * Atur **Source** ke file GPX, dan unggah file GPX dengan lokasi lintasan. Anda dapat mengunduh file GPX dari sejumlah situs pemetaan dan hiking populer, seperti [AllTrails](https://www.alltrails.com/). File ini berisi beberapa lokasi GPS sebagai jalur, dan sensor GPS akan mengembalikan setiap lokasi baru dalam interval 1 detik.

      ![Sensor GPS dengan file GPX diatur](../../../../../translated_images/id/counterfit-gps-sensor-gpxfile.8310b063ce8a425ccc8ebeec8306aeac5e8e55207f007d52c6e1194432a70cd9.png)

      Nilai-nilai ini hanya akan dikirim sekali, jadi centang kotak **Repeat** agar data dikirim ulang satu detik setelah semuanya dikirim.

    Setelah Anda mengatur pengaturan GPS, pilih tombol **Set** untuk menyimpan nilai-nilai ini ke sensor.

1. Anda akan melihat output mentah dari sensor GPS, seperti berikut:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    ```

> 💁 Anda dapat menemukan kode ini di folder [code-gps/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps/virtual-device).

😀 Program sensor GPS Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.