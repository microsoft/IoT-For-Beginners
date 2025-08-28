<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "90fb93446e03c38f3c0e4009c2471906",
  "translation_date": "2025-08-28T00:27:32+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md",
  "language_code": "ms"
}
-->
# Kawal lampu malam anda melalui Internet - Perkakasan IoT Maya dan Raspberry Pi

Peranti IoT perlu diprogramkan untuk berkomunikasi dengan *test.mosquitto.org* menggunakan MQTT bagi menghantar nilai telemetri dengan bacaan sensor cahaya, dan menerima arahan untuk mengawal LED.

Dalam bahagian pelajaran ini, anda akan menyambungkan Raspberry Pi atau peranti IoT maya anda kepada broker MQTT.

## Pasang pakej klien MQTT

Untuk berkomunikasi dengan broker MQTT, anda perlu memasang pakej perpustakaan MQTT pip sama ada pada Pi anda, atau dalam persekitaran maya jika anda menggunakan peranti maya.

### Tugasan

Pasang pakej pip

1. Buka projek lampu malam dalam VS Code.

1. Jika anda menggunakan peranti IoT maya, pastikan terminal sedang menjalankan persekitaran maya. Jika anda menggunakan Raspberry Pi, anda tidak akan menggunakan persekitaran maya.

1. Jalankan arahan berikut untuk memasang pakej pip MQTT:

    ```sh
    pip3 install paho-mqtt
    ```

## Programkan peranti

Peranti sudah bersedia untuk diprogramkan.

### Tugasan

Tulis kod untuk peranti.

1. Tambahkan import berikut di bahagian atas fail `app.py`:

    ```python
    import paho.mqtt.client as mqtt
    ```

    Perpustakaan `paho.mqtt.client` membolehkan aplikasi anda berkomunikasi melalui MQTT.

1. Tambahkan kod berikut selepas definisi sensor cahaya dan LED:

    ```python
    id = '<ID>'

    client_name = id + 'nightlight_client'
    ```

    Gantikan `<ID>` dengan ID unik yang akan digunakan sebagai nama klien peranti ini, dan kemudian untuk topik yang diterbitkan dan dilanggan oleh peranti ini. Broker *test.mosquitto.org* adalah awam dan digunakan oleh ramai orang, termasuk pelajar lain yang sedang menyelesaikan tugasan ini. Mempunyai nama klien MQTT dan nama topik yang unik memastikan kod anda tidak bertembung dengan kod orang lain. Anda juga akan memerlukan ID ini apabila anda mencipta kod pelayan kemudian dalam tugasan ini.

    > 💁 Anda boleh menggunakan laman web seperti [GUIDGen](https://www.guidgen.com) untuk menjana ID unik.

    `client_name` adalah nama unik untuk klien MQTT ini pada broker.

1. Tambahkan kod berikut di bawah kod baru ini untuk mencipta objek klien MQTT dan menyambung kepada broker MQTT:

    ```python
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()

    print("MQTT connected!")
    ```

    Kod ini mencipta objek klien, menyambung kepada broker MQTT awam, dan memulakan gelung pemprosesan yang berjalan dalam benang latar mendengar mesej pada mana-mana topik yang dilanggan.

1. Jalankan kod dengan cara yang sama seperti anda menjalankan kod dari bahagian tugasan sebelumnya. Jika anda menggunakan peranti IoT maya, pastikan aplikasi CounterFit sedang berjalan dan sensor cahaya serta LED telah dicipta pada pin yang betul.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Light level: 0
    Light level: 0
    ```

> 💁 Anda boleh menemui kod ini dalam folder [code-mqtt/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/virtual-device) atau folder [code-mqtt/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/pi).

😀 Anda telah berjaya menyambungkan peranti anda kepada broker MQTT.

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat penting, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.