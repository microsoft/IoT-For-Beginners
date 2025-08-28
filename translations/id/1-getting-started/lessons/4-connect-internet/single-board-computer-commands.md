<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c527ce85d69b1a3875366ec61cbed8aa",
  "translation_date": "2025-08-28T00:26:06+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-commands.md",
  "language_code": "id"
}
-->
# Kendalikan lampu malam Anda melalui Internet - Perangkat IoT Virtual dan Raspberry Pi

Dalam bagian pelajaran ini, Anda akan berlangganan perintah yang dikirim dari broker MQTT ke Raspberry Pi atau perangkat IoT virtual Anda.

## Berlangganan perintah

Langkah berikutnya adalah berlangganan perintah yang dikirim dari broker MQTT dan meresponsnya.

### Tugas

Berlangganan perintah.

1. Buka proyek lampu malam di VS Code.

1. Jika Anda menggunakan perangkat IoT virtual, pastikan terminal menjalankan lingkungan virtual. Jika Anda menggunakan Raspberry Pi, Anda tidak akan menggunakan lingkungan virtual.

1. Tambahkan kode berikut setelah definisi `client_telemetry_topic`:

    ```python
    server_command_topic = id + '/commands'
    ```

    `server_command_topic` adalah topik MQTT yang akan dilanggan oleh perangkat untuk menerima perintah LED.

1. Tambahkan kode berikut tepat di atas loop utama, setelah baris `mqtt_client.loop_start()`:

    ```python
    def handle_command(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
        if payload['led_on']:
            led.on()
        else:
            led.off()
    
    mqtt_client.subscribe(server_command_topic)
    mqtt_client.on_message = handle_command
    ```

    Kode ini mendefinisikan fungsi, `handle_command`, yang membaca pesan sebagai dokumen JSON dan mencari nilai properti `led_on`. Jika nilainya diatur ke `True`, LED akan dinyalakan, jika tidak maka akan dimatikan.

    Klien MQTT berlangganan topik tempat server akan mengirim pesan dan menetapkan fungsi `handle_command` untuk dipanggil saat pesan diterima.

    > 💁 Handler `on_message` dipanggil untuk semua topik yang dilanggan. Jika Anda nantinya menulis kode yang mendengarkan beberapa topik, Anda dapat mendapatkan topik tempat pesan dikirim dari objek `message` yang diteruskan ke fungsi handler.

1. Jalankan kode dengan cara yang sama seperti Anda menjalankan kode dari bagian tugas sebelumnya. Jika Anda menggunakan perangkat IoT virtual, pastikan aplikasi CounterFit berjalan dan sensor cahaya serta LED telah dibuat pada pin yang benar.

1. Sesuaikan tingkat cahaya yang terdeteksi oleh perangkat fisik atau virtual Anda. Pesan yang diterima dan perintah yang dikirim akan ditulis ke terminal. LED juga akan dinyalakan dan dimatikan tergantung pada tingkat cahaya.

> 💁 Anda dapat menemukan kode ini di folder [code-commands/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/virtual-device) atau folder [code-commands/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/pi).

😀 Anda telah berhasil membuat perangkat Anda merespons perintah dari broker MQTT.

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berupaya untuk memberikan hasil yang akurat, harap diketahui bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang timbul dari penggunaan terjemahan ini.