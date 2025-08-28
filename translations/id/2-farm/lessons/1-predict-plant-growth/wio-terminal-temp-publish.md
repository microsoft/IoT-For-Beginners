<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-27T21:28:44+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "id"
}
-->
# Publikasikan Suhu - Wio Terminal

Dalam bagian pelajaran ini, Anda akan mempublikasikan nilai suhu yang terdeteksi oleh Wio Terminal melalui MQTT sehingga dapat digunakan nanti untuk menghitung GDD.

## Publikasikan Suhu

Setelah suhu dibaca, data tersebut dapat dipublikasikan melalui MQTT ke beberapa kode 'server' yang akan membaca nilai tersebut dan menyimpannya untuk digunakan dalam perhitungan GDD. Mikrokontroler tidak secara otomatis membaca waktu dari Internet atau melacak waktu dengan real-time clock, perangkat perlu diprogram untuk melakukannya, dengan asumsi perangkat memiliki perangkat keras yang diperlukan.

Untuk menyederhanakan pelajaran ini, waktu tidak akan dikirim bersama data sensor, melainkan dapat ditambahkan oleh kode server nanti saat menerima pesan.

### Tugas

Program perangkat untuk mempublikasikan data suhu.

1. Buka proyek `temperature-sensor` Wio Terminal

1. Ulangi langkah-langkah yang Anda lakukan di pelajaran 4 untuk terhubung ke MQTT dan mengirim telemetri. Anda akan menggunakan broker Mosquitto publik yang sama.

    Langkah-langkahnya adalah:

    - Tambahkan pustaka Seeed WiFi dan MQTT ke file `.ini`
    - Tambahkan file konfigurasi dan kode untuk terhubung ke WiFi
    - Tambahkan kode untuk terhubung ke broker MQTT
    - Tambahkan kode untuk mempublikasikan telemetri

    > ⚠️ Lihat [instruksi untuk terhubung ke MQTT](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) dan [instruksi untuk mengirim telemetri](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) dari pelajaran 4 jika diperlukan.

1. Pastikan `CLIENT_NAME` di file header `config.h` mencerminkan proyek ini:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. Untuk telemetri, alih-alih mengirim nilai cahaya, kirim nilai suhu yang dibaca dari sensor DHT dalam properti pada dokumen JSON yang disebut `temperature` dengan mengubah fungsi `loop` di `main.cpp`:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. Nilai suhu tidak perlu dibaca terlalu sering - suhu tidak akan banyak berubah dalam waktu singkat, jadi atur `delay` dalam fungsi `loop` menjadi 10 menit:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 Fungsi `delay` menerima waktu dalam milidetik, sehingga untuk mempermudah pembacaan, nilai tersebut diberikan sebagai hasil dari perhitungan. 1.000ms dalam satu detik, 60 detik dalam satu menit, jadi 10 x (60 detik dalam satu menit) x (1.000ms dalam satu detik) menghasilkan penundaan 10 menit.

1. Unggah ini ke Wio Terminal Anda, dan gunakan serial monitor untuk melihat suhu yang dikirim ke broker MQTT.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"temperature":25}
    Sending telemetry {"temperature":25}
    ```

> 💁 Anda dapat menemukan kode ini di folder [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal).

😀 Anda telah berhasil mempublikasikan suhu sebagai telemetri dari perangkat Anda.

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.