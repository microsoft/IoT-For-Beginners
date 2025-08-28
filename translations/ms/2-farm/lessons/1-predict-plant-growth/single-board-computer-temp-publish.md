<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4efc74299e19f5d08f2f3f34451a11ba",
  "translation_date": "2025-08-28T01:46:34+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/single-board-computer-temp-publish.md",
  "language_code": "ms"
}
-->
# Terbitkan suhu - Perkakasan IoT Maya dan Raspberry Pi

Dalam bahagian pelajaran ini, anda akan menerbitkan nilai suhu yang dikesan oleh Raspberry Pi atau Peranti IoT Maya melalui MQTT supaya ia boleh digunakan kemudian untuk mengira GDD.

## Terbitkan suhu

Setelah suhu dibaca, ia boleh diterbitkan melalui MQTT kepada beberapa kod 'pelayan' yang akan membaca nilai tersebut dan menyimpannya untuk digunakan dalam pengiraan GDD.

### Tugasan - terbitkan suhu

Programkan peranti untuk menerbitkan data suhu.

1. Buka projek aplikasi `temperature-sensor` jika ia belum dibuka.

1. Ulang langkah yang anda lakukan dalam pelajaran 4 untuk menyambung ke MQTT dan menghantar telemetri. Anda akan menggunakan broker Mosquitto awam yang sama.

    Langkah-langkahnya adalah:

    - Tambahkan pakej pip MQTT
    - Tambahkan kod untuk menyambung ke broker MQTT
    - Tambahkan kod untuk menerbitkan telemetri

    > ⚠️ Rujuk kepada [arahan untuk menyambung ke MQTT](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md) dan [arahan untuk menghantar telemetri](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md) dari pelajaran 4 jika diperlukan.

1. Pastikan `client_name` mencerminkan nama projek ini:

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. Untuk telemetri, bukannya menghantar nilai cahaya, hantar nilai suhu yang dibaca dari sensor DHT dalam satu sifat pada dokumen JSON yang dipanggil `temperature`:

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. Nilai suhu tidak perlu dibaca terlalu kerap - ia tidak akan berubah banyak dalam masa yang singkat, jadi tetapkan `time.sleep` kepada 10 minit:

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 Fungsi `sleep` mengambil masa dalam saat, jadi untuk memudahkan pembacaan, nilai tersebut dihantar sebagai hasil pengiraan. 60 saat dalam satu minit, jadi 10 x (60 saat dalam satu minit) memberikan kelewatan selama 10 minit.

1. Jalankan kod dengan cara yang sama seperti anda menjalankan kod dari bahagian tugasan sebelumnya. Jika anda menggunakan peranti IoT maya, pastikan aplikasi CounterFit sedang berjalan dan sensor kelembapan serta suhu telah dicipta pada pin yang betul.

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 Anda boleh menemui kod ini dalam folder [code-publish-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/virtual-device) atau folder [code-publish-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/pi).

😀 Anda telah berjaya menerbitkan suhu sebagai telemetri daripada peranti anda.

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.