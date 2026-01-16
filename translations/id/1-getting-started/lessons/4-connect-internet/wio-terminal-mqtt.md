<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-27T22:22:27+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "id"
}
-->
# Kendalikan lampu malam Anda melalui Internet - Wio Terminal

Perangkat IoT perlu diprogram untuk berkomunikasi dengan *test.mosquitto.org* menggunakan MQTT agar dapat mengirim nilai telemetri dengan pembacaan sensor cahaya, serta menerima perintah untuk mengontrol LED.

Dalam bagian pelajaran ini, Anda akan menghubungkan Wio Terminal Anda ke broker MQTT.

## Instal pustaka WiFi dan MQTT Arduino

Untuk berkomunikasi dengan broker MQTT, Anda perlu menginstal beberapa pustaka Arduino agar dapat menggunakan chip WiFi di Wio Terminal dan berkomunikasi dengan MQTT. Saat mengembangkan perangkat Arduino, Anda dapat menggunakan berbagai pustaka yang berisi kode sumber terbuka dan mengimplementasikan beragam kemampuan. Seeed menerbitkan pustaka untuk Wio Terminal yang memungkinkan perangkat ini berkomunikasi melalui WiFi. Pengembang lain telah menerbitkan pustaka untuk berkomunikasi dengan broker MQTT, dan Anda akan menggunakan pustaka ini dengan perangkat Anda.

Pustaka-pustaka ini disediakan sebagai kode sumber yang dapat diimpor secara otomatis ke PlatformIO dan dikompilasi untuk perangkat Anda. Dengan cara ini, pustaka Arduino akan berfungsi pada perangkat apa pun yang mendukung kerangka kerja Arduino, dengan asumsi perangkat tersebut memiliki perangkat keras spesifik yang diperlukan oleh pustaka tersebut. Beberapa pustaka, seperti pustaka WiFi dari Seeed, hanya berlaku untuk perangkat keras tertentu.

Pustaka dapat diinstal secara global dan dikompilasi jika diperlukan, atau ke dalam proyek tertentu. Untuk tugas ini, pustaka akan diinstal ke dalam proyek.

✅ Anda dapat mempelajari lebih lanjut tentang manajemen pustaka dan cara menemukan serta menginstal pustaka di [dokumentasi pustaka PlatformIO](https://docs.platformio.org/en/latest/librarymanager/index.html).

### Tugas - instal pustaka WiFi dan MQTT Arduino

Instal pustaka Arduino.

1. Buka proyek lampu malam di VS Code.

1. Tambahkan hal berikut ke akhir file `platformio.ini`:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    Ini mengimpor pustaka WiFi dari Seeed. Sintaks `@ <number>` merujuk pada nomor versi spesifik dari pustaka tersebut.

    > 💁 Anda dapat menghapus `@ <number>` untuk selalu menggunakan versi terbaru dari pustaka, tetapi tidak ada jaminan bahwa versi terbaru akan berfungsi dengan kode di bawah ini. Kode di sini telah diuji dengan versi pustaka ini.

    Ini adalah semua yang perlu Anda lakukan untuk menambahkan pustaka. Saat PlatformIO membangun proyek berikutnya, ia akan mengunduh kode sumber untuk pustaka ini dan mengompilasinya ke dalam proyek Anda.

1. Tambahkan hal berikut ke `lib_deps`:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    Ini mengimpor [PubSubClient](https://github.com/knolleary/pubsubclient), sebuah klien MQTT Arduino.

## Hubungkan ke WiFi

Wio Terminal sekarang dapat dihubungkan ke WiFi.

### Tugas - hubungkan ke WiFi

Hubungkan Wio Terminal ke WiFi.

1. Buat file baru di folder `src` bernama `config.h`. Anda dapat melakukannya dengan memilih folder `src`, atau file `main.cpp` di dalamnya, lalu memilih tombol **New file** dari explorer. Tombol ini hanya muncul saat kursor Anda berada di atas explorer.

    ![Tombol file baru](../../../../../translated_images/id/vscode-new-file-button.182702340fe6723c.webp)

1. Tambahkan kode berikut ke file ini untuk mendefinisikan konstanta untuk kredensial WiFi Anda:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    Ganti `<SSID>` dengan SSID WiFi Anda. Ganti `<PASSWORD>` dengan kata sandi WiFi Anda.

1. Buka file `main.cpp`.

1. Tambahkan direktif `#include` berikut ke bagian atas file:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    Ini menyertakan file header untuk pustaka yang Anda tambahkan sebelumnya, serta file header konfigurasi. File header ini diperlukan untuk memberi tahu PlatformIO agar membawa kode dari pustaka. Tanpa secara eksplisit menyertakan file header ini, beberapa kode tidak akan dikompilasi dan Anda akan mendapatkan kesalahan kompilasi.

1. Tambahkan kode berikut di atas fungsi `setup`:

    ```cpp
    void connectWiFi()
    {
        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("Connecting to WiFi..");
            WiFi.begin(SSID, PASSWORD);
            delay(500);
        }
    
        Serial.println("Connected!");
    }
    ```

    Kode ini melakukan loop saat perangkat tidak terhubung ke WiFi, dan mencoba menghubungkan menggunakan SSID dan kata sandi dari file header konfigurasi.

1. Tambahkan pemanggilan fungsi ini di bagian bawah fungsi `setup`, setelah pin dikonfigurasi.

    ```cpp
    connectWiFi();
    ```

1. Unggah kode ini ke perangkat Anda untuk memeriksa apakah koneksi WiFi berfungsi. Anda seharusnya melihat ini di monitor serial.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## Hubungkan ke MQTT

Setelah Wio Terminal terhubung ke WiFi, perangkat ini dapat terhubung ke broker MQTT.

### Tugas - hubungkan ke MQTT

Hubungkan ke broker MQTT.

1. Tambahkan kode berikut ke bagian bawah file `config.h` untuk mendefinisikan detail koneksi ke broker MQTT:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    Ganti `<ID>` dengan ID unik yang akan digunakan sebagai nama klien perangkat ini, dan nanti untuk topik yang dipublikasikan dan disubscribe oleh perangkat ini. Broker *test.mosquitto.org* bersifat publik dan digunakan oleh banyak orang, termasuk siswa lain yang sedang mengerjakan tugas ini. Memiliki nama klien MQTT dan nama topik yang unik memastikan kode Anda tidak akan berbenturan dengan kode orang lain. Anda juga akan membutuhkan ID ini saat membuat kode server nanti dalam tugas ini.

    > 💁 Anda dapat menggunakan situs web seperti [GUIDGen](https://www.guidgen.com) untuk menghasilkan ID unik.

    `BROKER` adalah URL broker MQTT.

    `CLIENT_NAME` adalah nama unik untuk klien MQTT ini di broker.

1. Buka file `main.cpp`, dan tambahkan kode berikut di bawah fungsi `connectWiFi` dan di atas fungsi `setup`:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    Kode ini membuat klien WiFi menggunakan pustaka WiFi Wio Terminal dan menggunakannya untuk membuat klien MQTT.

1. Di bawah kode ini, tambahkan hal berikut:

    ```cpp
    void reconnectMQTTClient()
    {
        while (!client.connected())
        {
            Serial.print("Attempting MQTT connection...");
    
            if (client.connect(CLIENT_NAME.c_str()))
            {
                Serial.println("connected");
            }
            else
            {
                Serial.print("Retying in 5 seconds - failed, rc=");
                Serial.println(client.state());
                
                delay(5000);
            }
        }
    }
    ```

    Fungsi ini menguji koneksi ke broker MQTT dan menyambungkan kembali jika tidak terhubung. Fungsi ini melakukan loop sepanjang waktu saat tidak terhubung dan mencoba menyambungkan menggunakan nama klien unik yang didefinisikan dalam file header konfigurasi.

    Jika koneksi gagal, fungsi ini mencoba lagi setelah 5 detik.

1. Tambahkan kode berikut di bawah fungsi `reconnectMQTTClient`:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    Kode ini menetapkan broker MQTT untuk klien, serta menetapkan callback saat pesan diterima. Kemudian mencoba menyambungkan ke broker.

1. Panggil fungsi `createMQTTClient` dalam fungsi `setup` setelah WiFi terhubung.

1. Ganti seluruh fungsi `loop` dengan hal berikut:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    Kode ini dimulai dengan menyambungkan kembali ke broker MQTT. Koneksi ini dapat dengan mudah terputus, jadi ada baiknya untuk secara rutin memeriksa dan menyambungkan kembali jika diperlukan. Kemudian memanggil metode `loop` pada klien MQTT untuk memproses pesan apa pun yang masuk pada topik yang disubscribe. Aplikasi ini bersifat single-threaded, sehingga pesan tidak dapat diterima pada thread latar belakang, oleh karena itu waktu pada thread utama perlu dialokasikan untuk memproses pesan apa pun yang menunggu pada koneksi jaringan.

    Akhirnya, penundaan selama 2 detik memastikan tingkat cahaya tidak dikirim terlalu sering dan mengurangi konsumsi daya perangkat.

1. Unggah kode ke Wio Terminal Anda, dan gunakan Serial Monitor untuk melihat perangkat terhubung ke WiFi dan MQTT.

    ```output
    > Executing task: platformio device monitor <
    
    source /Users/jimbennett/GitHub/IoT-For-Beginners/1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal/nightlight/.venv/bin/activate
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    ```

> 💁 Anda dapat menemukan kode ini di folder [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal).

😀 Anda telah berhasil menghubungkan perangkat Anda ke broker MQTT.

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.