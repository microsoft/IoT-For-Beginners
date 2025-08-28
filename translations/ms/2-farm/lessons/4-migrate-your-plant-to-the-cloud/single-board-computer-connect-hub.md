<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-27T22:04:08+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "ms"
}
-->
# Sambungkan peranti IoT anda ke awan - Perkakasan IoT Maya dan Raspberry Pi

Dalam bahagian pelajaran ini, anda akan menyambungkan peranti IoT maya atau Raspberry Pi anda ke IoT Hub, untuk menghantar telemetri dan menerima arahan.

## Sambungkan peranti anda ke IoT Hub

Langkah seterusnya adalah menyambungkan peranti anda ke IoT Hub.

### Tugasan - sambungkan ke IoT Hub

1. Buka folder `soil-moisture-sensor` dalam VS Code. Pastikan persekitaran maya berjalan di terminal jika anda menggunakan peranti IoT maya.

1. Pasang beberapa pakej Pip tambahan:

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` adalah perpustakaan untuk berkomunikasi dengan IoT Hub anda.

1. Tambahkan import berikut di bahagian atas fail `app.py`, di bawah import yang sedia ada:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    Kod ini mengimport SDK untuk berkomunikasi dengan IoT Hub anda.

1. Padamkan baris `import paho.mqtt.client as mqtt` kerana perpustakaan ini tidak lagi diperlukan. Padamkan semua kod MQTT termasuk nama topik, semua kod yang menggunakan `mqtt_client` dan `handle_command`. Kekalkan gelung `while True:`, hanya padamkan baris `mqtt_client.publish` daripada gelung ini.

1. Tambahkan kod berikut di bawah pernyataan import:

    ```python
    connection_string = "<connection string>"
    ```

    Gantikan `<connection string>` dengan rentetan sambungan yang anda peroleh untuk peranti tersebut sebelum ini dalam pelajaran ini.

    > 💁 Ini bukan amalan terbaik. Rentetan sambungan tidak seharusnya disimpan dalam kod sumber, kerana ini boleh diperiksa ke dalam kawalan kod sumber dan ditemui oleh sesiapa sahaja. Kami melakukan ini di sini untuk tujuan kesederhanaan. Sebaiknya anda menggunakan sesuatu seperti pembolehubah persekitaran dan alat seperti [`python-dotenv`](https://pypi.org/project/python-dotenv/). Anda akan mempelajari lebih lanjut tentang ini dalam pelajaran yang akan datang.

1. Di bawah kod ini, tambahkan yang berikut untuk mencipta objek klien peranti yang boleh berkomunikasi dengan IoT Hub, dan sambungkannya:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. Jalankan kod ini. Anda akan melihat peranti anda disambungkan.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## Hantar telemetri

Sekarang peranti anda telah disambungkan, anda boleh menghantar telemetri ke IoT Hub dan bukannya broker MQTT.

### Tugasan - hantar telemetri

1. Tambahkan kod berikut di dalam gelung `while True`, tepat sebelum tidur:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    Kod ini mencipta `Message` IoT Hub yang mengandungi bacaan kelembapan tanah sebagai rentetan JSON, kemudian menghantarnya ke IoT Hub sebagai mesej peranti ke awan.

## Kendalikan arahan

Peranti anda perlu mengendalikan arahan daripada kod pelayan untuk mengawal relay. Ini dihantar sebagai permintaan kaedah langsung.

## Tugasan - kendalikan permintaan kaedah langsung

1. Tambahkan kod berikut sebelum gelung `while True`:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    Ini mentakrifkan kaedah, `handle_method_request`, yang akan dipanggil apabila kaedah langsung dipanggil oleh IoT Hub. Setiap kaedah langsung mempunyai nama, dan kod ini mengharapkan kaedah yang dipanggil `relay_on` untuk menghidupkan relay, dan `relay_off` untuk mematikan relay.

    > 💁 Ini juga boleh dilaksanakan dalam satu permintaan kaedah langsung, dengan menghantar keadaan yang diinginkan untuk relay dalam payload yang boleh dihantar bersama permintaan kaedah dan tersedia daripada objek `request`.

1. Kaedah langsung memerlukan respons untuk memberitahu kod pemanggil bahawa ia telah dikendalikan. Tambahkan kod berikut di akhir fungsi `handle_method_request` untuk mencipta respons kepada permintaan:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    Kod ini menghantar respons kepada permintaan kaedah langsung dengan kod status HTTP 200, dan menghantarnya kembali ke IoT Hub.

1. Tambahkan kod berikut di bawah definisi fungsi ini:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    Kod ini memberitahu klien IoT Hub untuk memanggil fungsi `handle_method_request` apabila kaedah langsung dipanggil.

> 💁 Anda boleh menemui kod ini dalam folder [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) atau [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device).

😀 Program sensor kelembapan tanah anda telah disambungkan ke IoT Hub anda!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.