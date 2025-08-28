<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4efc74299e19f5d08f2f3f34451a11ba",
  "translation_date": "2025-08-27T21:26:10+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/single-board-computer-temp-publish.md",
  "language_code": "id"
}
-->
# Publikasikan Suhu - Perangkat IoT Virtual dan Raspberry Pi

Dalam bagian pelajaran ini, Anda akan mempublikasikan nilai suhu yang terdeteksi oleh Raspberry Pi atau Perangkat IoT Virtual melalui MQTT sehingga dapat digunakan nanti untuk menghitung GDD.

## Publikasikan Suhu

Setelah suhu dibaca, data tersebut dapat dipublikasikan melalui MQTT ke beberapa kode 'server' yang akan membaca nilai tersebut dan menyimpannya untuk digunakan dalam perhitungan GDD.

### Tugas - Publikasikan Suhu

Program perangkat untuk mempublikasikan data suhu.

1. Buka proyek aplikasi `temperature-sensor` jika belum terbuka.

1. Ulangi langkah-langkah yang Anda lakukan di pelajaran 4 untuk terhubung ke MQTT dan mengirim telemetri. Anda akan menggunakan broker Mosquitto publik yang sama.

    Langkah-langkahnya adalah:

    - Tambahkan paket pip MQTT
    - Tambahkan kode untuk terhubung ke broker MQTT
    - Tambahkan kode untuk mempublikasikan telemetri

    > ⚠️ Lihat [instruksi untuk terhubung ke MQTT](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md) dan [instruksi untuk mengirim telemetri](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md) dari pelajaran 4 jika diperlukan.

1. Pastikan `client_name` mencerminkan nama proyek ini:

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. Untuk telemetri, alih-alih mengirim nilai cahaya, kirim nilai suhu yang dibaca dari sensor DHT dalam properti pada dokumen JSON yang disebut `temperature`:

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. Nilai suhu tidak perlu dibaca terlalu sering - suhu tidak akan banyak berubah dalam waktu singkat, jadi atur `time.sleep` menjadi 10 menit:

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 Fungsi `sleep` menerima waktu dalam detik, sehingga untuk mempermudah pembacaan, nilai tersebut diberikan sebagai hasil dari perhitungan. 60 detik dalam satu menit, jadi 10 x (60 detik dalam satu menit) memberikan jeda 10 menit.

1. Jalankan kode dengan cara yang sama seperti Anda menjalankan kode dari bagian tugas sebelumnya. Jika Anda menggunakan perangkat IoT virtual, pastikan aplikasi CounterFit berjalan dan sensor kelembapan serta suhu telah dibuat pada pin yang benar.

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 Anda dapat menemukan kode ini di folder [code-publish-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/virtual-device) atau folder [code-publish-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/pi).

😀 Anda telah berhasil mempublikasikan suhu sebagai telemetri dari perangkat Anda.

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.