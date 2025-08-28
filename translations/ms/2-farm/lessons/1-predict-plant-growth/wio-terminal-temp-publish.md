<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-27T21:28:55+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "ms"
}
-->
# Terbitkan suhu - Wio Terminal

Dalam bahagian pelajaran ini, anda akan menerbitkan nilai suhu yang dikesan oleh Wio Terminal melalui MQTT supaya ia boleh digunakan kemudian untuk mengira GDD.

## Terbitkan suhu

Setelah suhu dibaca, ia boleh diterbitkan melalui MQTT kepada kod 'server' yang akan membaca nilai tersebut dan menyimpannya untuk digunakan dalam pengiraan GDD. Mikrokontroler tidak membaca masa dari Internet dan menjejaki masa dengan jam masa nyata secara automatik, peranti perlu diprogramkan untuk melakukan ini, dengan andaian ia mempunyai perkakasan yang diperlukan.

Untuk mempermudahkan pelajaran ini, masa tidak akan dihantar bersama data sensor, sebaliknya ia boleh ditambah oleh kod server kemudian apabila mesej diterima.

### Tugas

Programkan peranti untuk menerbitkan data suhu.

1. Buka projek `temperature-sensor` Wio Terminal

1. Ulang langkah yang anda lakukan dalam pelajaran 4 untuk menyambung ke MQTT dan menghantar telemetri. Anda akan menggunakan broker Mosquitto awam yang sama.

    Langkah-langkahnya adalah:

    - Tambahkan perpustakaan Seeed WiFi dan MQTT ke fail `.ini`
    - Tambahkan fail konfigurasi dan kod untuk menyambung ke WiFi
    - Tambahkan kod untuk menyambung ke broker MQTT
    - Tambahkan kod untuk menerbitkan telemetri

    > ⚠️ Rujuk [arahan untuk menyambung ke MQTT](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) dan [arahan untuk menghantar telemetri](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) dari pelajaran 4 jika diperlukan.

1. Pastikan `CLIENT_NAME` dalam fail header `config.h` mencerminkan projek ini:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. Untuk telemetri, bukannya menghantar nilai cahaya, hantar nilai suhu yang dibaca dari sensor DHT dalam satu sifat pada dokumen JSON yang dipanggil `temperature` dengan mengubah fungsi `loop` dalam `main.cpp`:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. Nilai suhu tidak perlu dibaca terlalu kerap - ia tidak akan berubah banyak dalam masa yang singkat, jadi tetapkan `delay` dalam fungsi `loop` kepada 10 minit:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 Fungsi `delay` mengambil masa dalam milisaat, jadi untuk mempermudah pembacaan, nilai tersebut dihantar sebagai hasil pengiraan. 1,000ms dalam satu saat, 60s dalam satu minit, jadi 10 x (60s dalam satu minit) x (1000ms dalam satu saat) memberikan kelewatan 10 minit.

1. Muat naik ini ke Wio Terminal anda, dan gunakan monitor serial untuk melihat suhu yang dihantar ke broker MQTT.

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

> 💁 Anda boleh menemui kod ini dalam folder [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal).

😀 Anda telah berjaya menerbitkan suhu sebagai telemetri dari peranti anda.

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat penting, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.