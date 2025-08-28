<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-28T01:37:04+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "id"
}
-->
# Hubungkan Perangkat IoT Anda ke Cloud - Perangkat Keras IoT Virtual dan Raspberry Pi

Dalam bagian pelajaran ini, Anda akan menghubungkan perangkat IoT virtual atau Raspberry Pi Anda ke IoT Hub, untuk mengirim telemetri dan menerima perintah.

## Hubungkan perangkat Anda ke IoT Hub

Langkah berikutnya adalah menghubungkan perangkat Anda ke IoT Hub.

### Tugas - hubungkan ke IoT Hub

1. Buka folder `soil-moisture-sensor` di VS Code. Pastikan lingkungan virtual berjalan di terminal jika Anda menggunakan perangkat IoT virtual.

1. Instal beberapa paket Pip tambahan:

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` adalah pustaka untuk berkomunikasi dengan IoT Hub Anda.

1. Tambahkan impor berikut di bagian atas file `app.py`, di bawah impor yang sudah ada:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    Kode ini mengimpor SDK untuk berkomunikasi dengan IoT Hub Anda.

1. Hapus baris `import paho.mqtt.client as mqtt` karena pustaka ini tidak lagi diperlukan. Hapus semua kode MQTT termasuk nama topik, semua kode yang menggunakan `mqtt_client`, dan `handle_command`. Pertahankan loop `while True:`, cukup hapus baris `mqtt_client.publish` dari loop ini.

1. Tambahkan kode berikut di bawah pernyataan impor:

    ```python
    connection_string = "<connection string>"
    ```

    Ganti `<connection string>` dengan string koneksi yang Anda ambil untuk perangkat sebelumnya dalam pelajaran ini.

    > 💁 Ini bukan praktik terbaik. String koneksi seharusnya tidak pernah disimpan dalam kode sumber, karena ini dapat dimasukkan ke dalam kontrol versi kode sumber dan ditemukan oleh siapa saja. Kita melakukan ini di sini demi kesederhanaan. Idealnya, Anda harus menggunakan sesuatu seperti variabel lingkungan dan alat seperti [`python-dotenv`](https://pypi.org/project/python-dotenv/). Anda akan mempelajari lebih lanjut tentang ini di pelajaran mendatang.

1. Di bawah kode ini, tambahkan yang berikut untuk membuat objek klien perangkat yang dapat berkomunikasi dengan IoT Hub, dan menghubungkannya:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. Jalankan kode ini. Anda akan melihat perangkat Anda terhubung.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## Kirim telemetri

Sekarang perangkat Anda sudah terhubung, Anda dapat mengirim telemetri ke IoT Hub alih-alih ke broker MQTT.

### Tugas - kirim telemetri

1. Tambahkan kode berikut di dalam loop `while True`, tepat sebelum perintah sleep:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    Kode ini membuat sebuah `Message` IoT Hub yang berisi pembacaan kelembapan tanah dalam bentuk string JSON, lalu mengirimkannya ke IoT Hub sebagai pesan dari perangkat ke cloud.

## Tangani perintah

Perangkat Anda perlu menangani perintah dari kode server untuk mengontrol relay. Perintah ini dikirim sebagai permintaan metode langsung.

## Tugas - tangani permintaan metode langsung

1. Tambahkan kode berikut sebelum loop `while True`:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    Kode ini mendefinisikan sebuah metode, `handle_method_request`, yang akan dipanggil ketika metode langsung dipanggil oleh IoT Hub. Setiap metode langsung memiliki nama, dan kode ini mengharapkan metode bernama `relay_on` untuk menyalakan relay, dan `relay_off` untuk mematikan relay.

    > 💁 Ini juga dapat diimplementasikan dalam satu permintaan metode langsung, dengan melewatkan status yang diinginkan dari relay dalam payload yang dapat diteruskan dengan permintaan metode dan tersedia dari objek `request`.

1. Metode langsung memerlukan respons untuk memberi tahu kode pemanggil bahwa permintaan telah ditangani. Tambahkan kode berikut di akhir fungsi `handle_method_request` untuk membuat respons terhadap permintaan:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    Kode ini mengirimkan respons terhadap permintaan metode langsung dengan kode status HTTP 200, dan mengirimkannya kembali ke IoT Hub.

1. Tambahkan kode berikut di bawah definisi fungsi ini:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    Kode ini memberi tahu klien IoT Hub untuk memanggil fungsi `handle_method_request` ketika metode langsung dipanggil.

> 💁 Anda dapat menemukan kode ini di folder [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) atau [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device).

😀 Program sensor kelembapan tanah Anda sekarang terhubung ke IoT Hub Anda!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berupaya untuk memberikan hasil yang akurat, harap diketahui bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.