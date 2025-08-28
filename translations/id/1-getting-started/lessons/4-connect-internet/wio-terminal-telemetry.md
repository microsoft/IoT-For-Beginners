<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-28T00:26:42+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "id"
}
-->
# Kendalikan Lampu Malam Anda Melalui Internet - Wio Terminal

Dalam bagian pelajaran ini, Anda akan mengirimkan telemetri dengan tingkat cahaya dari Wio Terminal Anda ke broker MQTT.

## Instalasi Library JSON untuk Arduino

Salah satu cara populer untuk mengirim pesan melalui MQTT adalah menggunakan JSON. Ada library Arduino untuk JSON yang mempermudah membaca dan menulis dokumen JSON.

### Tugas

Instal library JSON untuk Arduino.

1. Buka proyek lampu malam di VS Code.

1. Tambahkan baris berikut sebagai tambahan pada daftar `lib_deps` di file `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Ini akan mengimpor [ArduinoJson](https://arduinojson.org), sebuah library JSON untuk Arduino.

## Mengirimkan Telemetri

Langkah berikutnya adalah membuat dokumen JSON dengan telemetri dan mengirimkannya ke broker MQTT.

### Tugas - Mengirimkan Telemetri

Kirimkan telemetri ke broker MQTT.

1. Tambahkan kode berikut ke bagian bawah file `config.h` untuk mendefinisikan nama topik telemetri untuk broker MQTT:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC` adalah topik tempat perangkat akan mengirimkan tingkat cahaya.

1. Buka file `main.cpp`.

1. Tambahkan direktif `#include` berikut di bagian atas file:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Tambahkan kode berikut di dalam fungsi `loop`, tepat sebelum `delay`:

    ```cpp
    int light = analogRead(WIO_LIGHT);

    DynamicJsonDocument doc(1024);
    doc["light"] = light;

    string telemetry;
    serializeJson(doc, telemetry);

    Serial.print("Sending telemetry ");
    Serial.println(telemetry.c_str());

    client.publish(CLIENT_TELEMETRY_TOPIC.c_str(), telemetry.c_str());
    ```

    Kode ini membaca tingkat cahaya, dan membuat dokumen JSON menggunakan ArduinoJson yang berisi tingkat tersebut. Dokumen ini kemudian diserialisasi menjadi string dan dikirimkan pada topik telemetri MQTT oleh klien MQTT.

1. Unggah kode ke Wio Terminal Anda, dan gunakan Serial Monitor untuk melihat tingkat cahaya yang dikirimkan ke broker MQTT.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 Anda dapat menemukan kode ini di folder [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal).

😀 Anda telah berhasil mengirimkan telemetri dari perangkat Anda.

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan manusia profesional. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.