<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-08-28T00:23:15+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "id"
}
-->
# Kendalikan lampu malam Anda melalui Internet - Wio Terminal

Dalam bagian pelajaran ini, Anda akan berlangganan perintah yang dikirim dari broker MQTT ke Wio Terminal Anda.

## Berlangganan perintah

Langkah berikutnya adalah berlangganan perintah yang dikirim dari broker MQTT, dan meresponsnya.

### Tugas

Berlangganan perintah.

1. Buka proyek lampu malam di VS Code.

1. Tambahkan kode berikut ke bagian bawah file `config.h` untuk mendefinisikan nama topik untuk perintah:

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    `SERVER_COMMAND_TOPIC` adalah topik yang akan dilanggan oleh perangkat untuk menerima perintah LED.

1. Tambahkan baris berikut ke akhir fungsi `reconnectMQTTClient` untuk berlangganan topik perintah saat klien MQTT tersambung kembali:

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. Tambahkan kode berikut di bawah fungsi `reconnectMQTTClient`.

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

    Fungsi ini akan menjadi callback yang akan dipanggil oleh klien MQTT saat menerima pesan dari server.

    Pesan diterima sebagai array bilangan bulat 8-bit tak bertanda, sehingga perlu dikonversi menjadi array karakter agar dapat diperlakukan sebagai teks.

    Pesan berisi dokumen JSON, dan didekode menggunakan pustaka ArduinoJson. Properti `led_on` dari dokumen JSON dibaca, dan tergantung pada nilainya, LED akan dinyalakan atau dimatikan.

1. Tambahkan kode berikut ke fungsi `createMQTTClient`:

    ```cpp
    client.setCallback(clientCallback);
    ```

    Kode ini menetapkan `clientCallback` sebagai callback yang akan dipanggil saat pesan diterima dari broker MQTT.

    > 💁 Handler `clientCallback` dipanggil untuk semua topik yang dilanggan. Jika Anda nanti menulis kode yang mendengarkan beberapa topik, Anda dapat mendapatkan topik tempat pesan dikirim dari parameter `topic` yang diteruskan ke fungsi callback.

1. Unggah kode ke Wio Terminal Anda, dan gunakan Serial Monitor untuk melihat tingkat cahaya yang dikirim ke broker MQTT.

1. Sesuaikan tingkat cahaya yang terdeteksi oleh perangkat fisik atau virtual Anda. Anda akan melihat pesan diterima dan perintah dikirim di terminal. Anda juga akan melihat LED dinyalakan dan dimatikan tergantung pada tingkat cahaya.

> 💁 Anda dapat menemukan kode ini di folder [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal).

😀 Anda telah berhasil memprogram perangkat Anda untuk merespons perintah dari broker MQTT.

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diketahui bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.