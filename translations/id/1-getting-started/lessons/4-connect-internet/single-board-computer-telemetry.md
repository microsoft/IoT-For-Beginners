<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-28T00:25:29+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "id"
}
-->
# Kendalikan Lampu Malam Anda melalui Internet - Perangkat IoT Virtual dan Raspberry Pi

Dalam bagian pelajaran ini, Anda akan mengirimkan telemetri dengan tingkat cahaya dari Raspberry Pi atau perangkat IoT virtual Anda ke broker MQTT.

## Mengirim Telemetri

Langkah berikutnya adalah membuat dokumen JSON dengan telemetri dan mengirimkannya ke broker MQTT.

### Tugas

Kirim telemetri ke broker MQTT.

1. Buka proyek lampu malam di VS Code.

1. Jika Anda menggunakan perangkat IoT virtual, pastikan terminal menjalankan lingkungan virtual. Jika Anda menggunakan Raspberry Pi, Anda tidak akan menggunakan lingkungan virtual.

1. Tambahkan impor berikut ke bagian atas file `app.py`:

    ```python
    import json
    ```

    Pustaka `json` digunakan untuk mengkodekan telemetri sebagai dokumen JSON.

1. Tambahkan yang berikut ini setelah deklarasi `client_name`:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    `client_telemetry_topic` adalah topik MQTT tempat perangkat akan mengirimkan tingkat cahaya.

1. Ganti isi dari loop `while True:` di akhir file dengan yang berikut:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    Kode ini mengemas tingkat cahaya ke dalam dokumen JSON dan mengirimkannya ke broker MQTT. Kemudian, kode ini berhenti sejenak untuk mengurangi frekuensi pengiriman pesan.

1. Jalankan kode dengan cara yang sama seperti Anda menjalankan kode dari bagian tugas sebelumnya. Jika Anda menggunakan perangkat IoT virtual, pastikan aplikasi CounterFit sedang berjalan dan sensor cahaya serta LED telah dibuat pada pin yang benar.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 Anda dapat menemukan kode ini di folder [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) atau [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi).

😀 Anda telah berhasil mengirim telemetri dari perangkat Anda.

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan manusia profesional. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.