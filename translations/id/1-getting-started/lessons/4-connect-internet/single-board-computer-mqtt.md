<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "90fb93446e03c38f3c0e4009c2471906",
  "translation_date": "2025-08-27T22:21:32+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md",
  "language_code": "id"
}
-->
# Kendalikan Lampu Malam Anda melalui Internet - Perangkat IoT Virtual dan Raspberry Pi

Perangkat IoT perlu diprogram untuk berkomunikasi dengan *test.mosquitto.org* menggunakan MQTT agar dapat mengirimkan nilai telemetri dari pembacaan sensor cahaya, serta menerima perintah untuk mengontrol LED.

Dalam bagian pelajaran ini, Anda akan menghubungkan Raspberry Pi atau perangkat IoT virtual Anda ke broker MQTT.

## Instal Paket Klien MQTT

Untuk berkomunikasi dengan broker MQTT, Anda perlu menginstal pustaka MQTT melalui paket pip, baik di Raspberry Pi Anda atau di lingkungan virtual jika Anda menggunakan perangkat virtual.

### Tugas

Instal paket pip

1. Buka proyek lampu malam di VS Code.

1. Jika Anda menggunakan perangkat IoT virtual, pastikan terminal menjalankan lingkungan virtual. Jika Anda menggunakan Raspberry Pi, Anda tidak perlu menggunakan lingkungan virtual.

1. Jalankan perintah berikut untuk menginstal paket pip MQTT:

    ```sh
    pip3 install paho-mqtt
    ```

## Program Perangkat

Perangkat siap untuk diprogram.

### Tugas

Tulis kode perangkat.

1. Tambahkan impor berikut di bagian atas file `app.py`:

    ```python
    import paho.mqtt.client as mqtt
    ```

    Pustaka `paho.mqtt.client` memungkinkan aplikasi Anda berkomunikasi melalui MQTT.

1. Tambahkan kode berikut setelah definisi sensor cahaya dan LED:

    ```python
    id = '<ID>'

    client_name = id + 'nightlight_client'
    ```

    Ganti `<ID>` dengan ID unik yang akan digunakan sebagai nama klien perangkat ini, dan nantinya untuk topik yang diterbitkan dan dilanggani oleh perangkat ini. Broker *test.mosquitto.org* bersifat publik dan digunakan oleh banyak orang, termasuk siswa lain yang mengerjakan tugas ini. Memiliki nama klien MQTT dan nama topik yang unik memastikan kode Anda tidak berbenturan dengan kode orang lain. Anda juga akan memerlukan ID ini saat membuat kode server nanti dalam tugas ini.

    > 💁 Anda dapat menggunakan situs web seperti [GUIDGen](https://www.guidgen.com) untuk menghasilkan ID unik.

    `client_name` adalah nama unik untuk klien MQTT ini di broker.

1. Tambahkan kode berikut di bawah kode baru ini untuk membuat objek klien MQTT dan menghubungkannya ke broker MQTT:

    ```python
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()

    print("MQTT connected!")
    ```

    Kode ini membuat objek klien, menghubungkan ke broker MQTT publik, dan memulai loop pemrosesan yang berjalan di thread latar belakang untuk mendengarkan pesan pada topik yang dilanggani.

1. Jalankan kode dengan cara yang sama seperti Anda menjalankan kode dari bagian tugas sebelumnya. Jika Anda menggunakan perangkat IoT virtual, pastikan aplikasi CounterFit berjalan dan sensor cahaya serta LED telah dibuat pada pin yang benar.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Light level: 0
    Light level: 0
    ```

> 💁 Anda dapat menemukan kode ini di folder [code-mqtt/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/virtual-device) atau folder [code-mqtt/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/pi).

😀 Anda telah berhasil menghubungkan perangkat Anda ke broker MQTT.

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.