<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64f18a8f8aaa1fef5e7320e0992d8b3a",
  "translation_date": "2025-08-27T23:40:55+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/virtual-device-gps-sensor.md",
  "language_code": "ms"
}
-->
# Membaca Data GPS - Perkakasan IoT Maya

Dalam bahagian pelajaran ini, anda akan menambah sensor GPS kepada peranti IoT maya anda, dan membaca nilai daripadanya.

## Perkakasan Maya

Peranti IoT maya akan menggunakan sensor GPS simulasi yang boleh diakses melalui UART melalui port serial.

Sensor GPS fizikal mempunyai antena untuk menerima gelombang radio daripada satelit GPS, dan menukar isyarat GPS kepada data GPS. Versi maya mensimulasikan ini dengan membolehkan anda sama ada menetapkan latitud dan longitud, menghantar ayat NMEA mentah, atau memuat naik fail GPX dengan pelbagai lokasi yang boleh dikembalikan secara berurutan.

> 🎓 Ayat NMEA akan dibincangkan kemudian dalam pelajaran ini

### Menambah Sensor kepada CounterFit

Untuk menggunakan sensor GPS maya, anda perlu menambah satu kepada aplikasi CounterFit.

#### Tugasan - Menambah Sensor kepada CounterFit

Tambah sensor GPS kepada aplikasi CounterFit.

1. Cipta aplikasi Python baharu pada komputer anda dalam folder bernama `gps-sensor` dengan satu fail bernama `app.py` dan persekitaran maya Python, serta tambahkan pakej pip CounterFit.

    > ⚠️ Anda boleh merujuk kepada [arahan untuk mencipta dan menyediakan projek Python CounterFit dalam pelajaran 1 jika diperlukan](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Pasang pakej Pip tambahan untuk memasang shim CounterFit yang boleh berkomunikasi dengan sensor berasaskan UART melalui sambungan serial. Pastikan anda memasangnya dari terminal dengan persekitaran maya diaktifkan.

    ```sh
    pip install counterfit-shims-serial
    ```

1. Pastikan aplikasi web CounterFit sedang berjalan.

1. Cipta sensor GPS:

    1. Dalam kotak *Create sensor* di panel *Sensors*, klik menu drop-down *Sensor type* dan pilih *UART GPS*.

    1. Biarkan *Port* ditetapkan kepada */dev/ttyAMA0*.

    1. Pilih butang **Add** untuk mencipta sensor GPS pada port `/dev/ttyAMA0`.

    ![Tetapan sensor GPS](../../../../../translated_images/ms/counterfit-create-gps-sensor.6385dc9357d85ad1d47b4abb2525e7651fd498917d25eefc5a72feab09eedc70.png)

    Sensor GPS akan dicipta dan muncul dalam senarai sensor.

    ![Sensor GPS yang telah dicipta](../../../../../translated_images/ms/counterfit-gps-sensor.3fbb15af0a5367566f2f11324ef5a6f30861cdf2b497071a5e002b7aa473550e.png)

## Memprogram Sensor GPS

Peranti IoT Maya kini boleh diprogramkan untuk menggunakan sensor GPS maya.

### Tugasan - Memprogram Sensor GPS

Program aplikasi sensor GPS.

1. Pastikan aplikasi `gps-sensor` dibuka dalam VS Code.

1. Buka fail `app.py`.

1. Tambahkan kod berikut di bahagian atas `app.py` untuk menyambungkan aplikasi kepada CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Tambahkan kod berikut di bawah ini untuk mengimport beberapa pustaka yang diperlukan, termasuk pustaka untuk port serial CounterFit:

    ```python
    import time
    import counterfit_shims_serial
    
    serial = counterfit_shims_serial.Serial('/dev/ttyAMA0')
    ```

    Kod ini mengimport modul `serial` daripada pakej Pip `counterfit_shims_serial`. Ia kemudian menyambung kepada port serial `/dev/ttyAMA0` - ini adalah alamat port serial yang digunakan oleh sensor GPS maya untuk port UART-nya.

1. Tambahkan kod berikut di bawah ini untuk membaca daripada port serial dan mencetak nilai ke konsol:

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

    Fungsi bernama `print_gps_data` didefinisikan untuk mencetak baris yang dihantar kepadanya ke konsol.

    Seterusnya, kod ini melaksanakan gelung tanpa henti, membaca sebanyak mungkin baris teks daripada port serial dalam setiap gelung. Ia memanggil fungsi `print_gps_data` untuk setiap baris.

    Selepas semua data dibaca, gelung akan tidur selama 1 saat, kemudian mencuba lagi.

1. Jalankan kod ini, pastikan anda menggunakan terminal yang berbeza daripada yang digunakan oleh aplikasi CounterFit, supaya aplikasi CounterFit kekal berjalan.

1. Dari aplikasi CounterFit, ubah nilai sensor GPS. Anda boleh melakukannya dengan salah satu cara berikut:

    * Tetapkan **Source** kepada `Lat/Lon`, dan tetapkan latitud, longitud, dan bilangan satelit yang digunakan untuk mendapatkan GPS fix. Nilai ini akan dihantar hanya sekali, jadi tandakan kotak **Repeat** untuk menghantar data berulang setiap saat.

      ![Sensor GPS dengan lat lon dipilih](../../../../../translated_images/ms/counterfit-gps-sensor-latlon.008c867d75464fbe7f84107cc57040df565ac07cb57d2f21db37d087d470197d.png)

    * Tetapkan **Source** kepada `NMEA` dan tambahkan beberapa ayat NMEA ke dalam kotak teks. Semua nilai ini akan dihantar, dengan kelewatan 1 saat sebelum setiap ayat GGA (position fix) baharu boleh dibaca.

      ![Sensor GPS dengan ayat NMEA ditetapkan](../../../../../translated_images/ms/counterfit-gps-sensor-nmea.c62eea442171e17e19528b051b104cfcecdc9cd18db7bc72920f29821ae63f73.png)

      Anda boleh menggunakan alat seperti [nmeagen.org](https://www.nmeagen.org) untuk menjana ayat ini dengan melukis pada peta. Nilai ini akan dihantar hanya sekali, jadi tandakan kotak **Repeat** untuk menghantar data berulang satu saat selepas semuanya dihantar.

    * Tetapkan **Source** kepada fail GPX, dan muat naik fail GPX dengan lokasi trek. Anda boleh memuat turun fail GPX daripada beberapa laman web pemetaan dan pendakian popular, seperti [AllTrails](https://www.alltrails.com/). Fail ini mengandungi pelbagai lokasi GPS sebagai laluan, dan sensor GPS akan mengembalikan setiap lokasi baharu pada selang 1 saat.

      ![Sensor GPS dengan fail GPX ditetapkan](../../../../../translated_images/ms/counterfit-gps-sensor-gpxfile.8310b063ce8a425ccc8ebeec8306aeac5e8e55207f007d52c6e1194432a70cd9.png)

      Nilai ini akan dihantar hanya sekali, jadi tandakan kotak **Repeat** untuk menghantar data berulang satu saat selepas semuanya dihantar.

    Setelah anda mengkonfigurasi tetapan GPS, pilih butang **Set** untuk menetapkan nilai ini kepada sensor.

1. Anda akan melihat output mentah daripada sensor GPS, sesuatu seperti berikut:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    ```

> 💁 Anda boleh menemui kod ini dalam folder [code-gps/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps/virtual-device).

😀 Program sensor GPS anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.