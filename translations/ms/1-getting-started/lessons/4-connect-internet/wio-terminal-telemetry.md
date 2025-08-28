<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-27T22:20:28+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "ms"
}
-->
# Kawal lampu malam anda melalui Internet - Wio Terminal

Dalam bahagian pelajaran ini, anda akan menghantar telemetri dengan tahap cahaya dari Wio Terminal anda ke broker MQTT.

## Pasang perpustakaan JSON Arduino

Satu cara popular untuk menghantar mesej melalui MQTT adalah dengan menggunakan JSON. Terdapat perpustakaan Arduino untuk JSON yang memudahkan pembacaan dan penulisan dokumen JSON.

### Tugas

Pasang perpustakaan Arduino JSON.

1. Buka projek lampu malam dalam VS Code.

1. Tambahkan baris berikut sebagai baris tambahan ke senarai `lib_deps` dalam fail `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Ini mengimport [ArduinoJson](https://arduinojson.org), sebuah perpustakaan JSON untuk Arduino.

## Terbitkan telemetri

Langkah seterusnya adalah untuk mencipta dokumen JSON dengan telemetri dan menghantarnya ke broker MQTT.

### Tugas - terbitkan telemetri

Terbitkan telemetri ke broker MQTT.

1. Tambahkan kod berikut ke bahagian bawah fail `config.h` untuk menentukan nama topik telemetri untuk broker MQTT:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC` adalah topik di mana peranti akan menerbitkan tahap cahaya.

1. Buka fail `main.cpp`

1. Tambahkan arahan `#include` berikut ke bahagian atas fail:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Tambahkan kod berikut di dalam fungsi `loop`, tepat sebelum `delay`:

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

    Kod ini membaca tahap cahaya, dan mencipta dokumen JSON menggunakan ArduinoJson yang mengandungi tahap ini. Dokumen ini kemudian diserialkan ke dalam bentuk string dan diterbitkan pada topik telemetri MQTT oleh klien MQTT.

1. Muat naik kod ke Wio Terminal anda, dan gunakan Serial Monitor untuk melihat tahap cahaya yang dihantar ke broker MQTT.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 Anda boleh menemui kod ini dalam folder [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal).

😀 Anda telah berjaya menghantar telemetri dari peranti anda.

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil maklum bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat penting, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.