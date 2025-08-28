<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c527ce85d69b1a3875366ec61cbed8aa",
  "translation_date": "2025-08-28T00:26:15+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-commands.md",
  "language_code": "ms"
}
-->
# Kawal lampu malam anda melalui Internet - Perkakasan IoT Maya dan Raspberry Pi

Dalam bahagian pelajaran ini, anda akan melanggan arahan yang dihantar dari broker MQTT ke Raspberry Pi atau peranti IoT maya anda.

## Langgan arahan

Langkah seterusnya adalah melanggan arahan yang dihantar dari broker MQTT dan bertindak balas terhadapnya.

### Tugasan

Langgan arahan.

1. Buka projek lampu malam dalam VS Code.

1. Jika anda menggunakan peranti IoT maya, pastikan terminal menjalankan persekitaran maya. Jika anda menggunakan Raspberry Pi, anda tidak akan menggunakan persekitaran maya.

1. Tambahkan kod berikut selepas definisi `client_telemetry_topic`:

    ```python
    server_command_topic = id + '/commands'
    ```

    `server_command_topic` adalah topik MQTT yang akan dilanggan oleh peranti untuk menerima arahan LED.

1. Tambahkan kod berikut tepat di atas gelung utama, selepas baris `mqtt_client.loop_start()`:

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

    Kod ini mentakrifkan fungsi, `handle_command`, yang membaca mesej sebagai dokumen JSON dan mencari nilai sifat `led_on`. Jika ia ditetapkan kepada `True`, LED akan dihidupkan, jika tidak, ia akan dimatikan.

    Pelanggan MQTT melanggan topik yang akan dihantar oleh pelayan mesej dan menetapkan fungsi `handle_command` untuk dipanggil apabila mesej diterima.

    > 💁 Pengendali `on_message` dipanggil untuk semua topik yang dilanggan. Jika anda kemudian menulis kod yang mendengar pelbagai topik, anda boleh mendapatkan topik yang mesej dihantar daripada objek `message` yang dihantar ke fungsi pengendali.

1. Jalankan kod dengan cara yang sama seperti anda menjalankan kod dari bahagian tugasan sebelumnya. Jika anda menggunakan peranti IoT maya, pastikan aplikasi CounterFit sedang berjalan dan sensor cahaya serta LED telah dicipta pada pin yang betul.

1. Laraskan tahap cahaya yang dikesan oleh peranti fizikal atau maya anda. Mesej yang diterima dan arahan yang dihantar akan ditulis ke terminal. LED juga akan dihidupkan dan dimatikan bergantung pada tahap cahaya.

> 💁 Anda boleh menemui kod ini dalam folder [code-commands/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/virtual-device) atau folder [code-commands/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/pi).

😀 Anda telah berjaya menulis kod untuk peranti anda supaya bertindak balas terhadap arahan daripada broker MQTT.

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.