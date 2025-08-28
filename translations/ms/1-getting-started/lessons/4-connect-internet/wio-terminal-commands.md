<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-08-27T22:23:54+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "ms"
}
-->
# Kawal lampu malam anda melalui Internet - Wio Terminal

Dalam bahagian pelajaran ini, anda akan melanggan arahan yang dihantar dari broker MQTT ke Wio Terminal anda.

## Langgan arahan

Langkah seterusnya adalah melanggan arahan yang dihantar dari broker MQTT, dan bertindak balas terhadapnya.

### Tugas

Langgan arahan.

1. Buka projek lampu malam dalam VS Code.

1. Tambahkan kod berikut ke bahagian bawah fail `config.h` untuk mentakrifkan nama topik bagi arahan:

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    `SERVER_COMMAND_TOPIC` adalah topik yang akan dilanggan oleh peranti untuk menerima arahan LED.

1. Tambahkan baris berikut ke penghujung fungsi `reconnectMQTTClient` untuk melanggan topik arahan apabila klien MQTT disambungkan semula:

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. Tambahkan kod berikut di bawah fungsi `reconnectMQTTClient`.

    ```cpp
    void clientCallback(char *topic, uint8_t *payload, unsigned int length)
    {
        char buff[length + 1];
        for (int i = 0; i < length; i++)
        {
            buff[i] = (char)payload[i];
        }
        buff[length] = '\0';
    
        Serial.print("Message received:");
        Serial.println(buff);
    
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, buff);
        JsonObject obj = doc.as<JsonObject>();
    
        bool led_on = obj["led_on"];
    
        if (led_on)
            digitalWrite(D0, HIGH);
        else
            digitalWrite(D0, LOW);
    }
    ```

    Fungsi ini akan menjadi callback yang akan dipanggil oleh klien MQTT apabila ia menerima mesej dari pelayan.

    Mesej diterima sebagai array integer 8-bit tanpa tanda, jadi ia perlu ditukar kepada array aksara untuk diproses sebagai teks.

    Mesej mengandungi dokumen JSON, dan ia dinyahkod menggunakan perpustakaan ArduinoJson. Properti `led_on` dalam dokumen JSON dibaca, dan bergantung pada nilainya, LED akan dihidupkan atau dimatikan.

1. Tambahkan kod berikut ke fungsi `createMQTTClient`:

    ```cpp
    client.setCallback(clientCallback);
    ```

    Kod ini menetapkan `clientCallback` sebagai callback yang akan dipanggil apabila mesej diterima dari broker MQTT.

    > 💁 Handler `clientCallback` dipanggil untuk semua topik yang dilanggan. Jika anda menulis kod yang mendengar kepada pelbagai topik kemudian, anda boleh mendapatkan topik yang mesej dihantar kepadanya dari parameter `topic` yang dihantar ke fungsi callback.

1. Muat naik kod ke Wio Terminal anda, dan gunakan Serial Monitor untuk melihat tahap cahaya yang dihantar ke broker MQTT.

1. Laraskan tahap cahaya yang dikesan oleh peranti fizikal atau maya anda. Anda akan melihat mesej diterima dan arahan dihantar dalam terminal. Anda juga akan melihat LED dihidupkan dan dimatikan bergantung pada tahap cahaya.

> 💁 Anda boleh menemui kod ini dalam folder [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal).

😀 Anda telah berjaya menulis kod untuk peranti anda supaya ia dapat bertindak balas terhadap arahan dari broker MQTT.

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil maklum bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.