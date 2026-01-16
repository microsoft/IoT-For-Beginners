<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-27T22:22:48+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "ms"
}
-->
# Kawal lampu malam anda melalui Internet - Wio Terminal

Peranti IoT perlu diprogramkan untuk berkomunikasi dengan *test.mosquitto.org* menggunakan MQTT bagi menghantar nilai telemetri dengan bacaan sensor cahaya, dan menerima arahan untuk mengawal LED.

Dalam bahagian pelajaran ini, anda akan menyambungkan Wio Terminal anda kepada broker MQTT.

## Pasang perpustakaan WiFi dan MQTT Arduino

Untuk berkomunikasi dengan broker MQTT, anda perlu memasang beberapa perpustakaan Arduino untuk menggunakan cip WiFi dalam Wio Terminal, dan berkomunikasi dengan MQTT. Semasa membangunkan untuk peranti Arduino, anda boleh menggunakan pelbagai perpustakaan yang mengandungi kod sumber terbuka dan melaksanakan pelbagai keupayaan. Seeed menerbitkan perpustakaan untuk Wio Terminal yang membolehkannya berkomunikasi melalui WiFi. Pembangun lain telah menerbitkan perpustakaan untuk berkomunikasi dengan broker MQTT, dan anda akan menggunakan perpustakaan ini dengan peranti anda.

Perpustakaan ini disediakan sebagai kod sumber yang boleh diimport secara automatik ke dalam PlatformIO dan disusun untuk peranti anda. Dengan cara ini, perpustakaan Arduino akan berfungsi pada mana-mana peranti yang menyokong rangka kerja Arduino, dengan syarat peranti tersebut mempunyai perkakasan tertentu yang diperlukan oleh perpustakaan tersebut. Beberapa perpustakaan, seperti perpustakaan WiFi Seeed, adalah khusus untuk perkakasan tertentu.

Perpustakaan boleh dipasang secara global dan disusun jika diperlukan, atau ke dalam projek tertentu. Untuk tugasan ini, perpustakaan akan dipasang ke dalam projek.

✅ Anda boleh mempelajari lebih lanjut tentang pengurusan perpustakaan dan cara mencari serta memasang perpustakaan dalam [dokumentasi perpustakaan PlatformIO](https://docs.platformio.org/en/latest/librarymanager/index.html).

### Tugasan - pasang perpustakaan WiFi dan MQTT Arduino

Pasang perpustakaan Arduino.

1. Buka projek lampu malam dalam VS Code.

1. Tambahkan perkara berikut ke penghujung fail `platformio.ini`:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    Ini mengimport perpustakaan WiFi Seeed. Sintaks `@ <number>` merujuk kepada nombor versi tertentu perpustakaan.

    > 💁 Anda boleh menghapuskan `@ <number>` untuk sentiasa menggunakan versi terkini perpustakaan, tetapi tiada jaminan versi kemudian akan berfungsi dengan kod di bawah. Kod di sini telah diuji dengan versi perpustakaan ini.

    Ini sahaja yang perlu anda lakukan untuk menambah perpustakaan. Kali seterusnya PlatformIO membina projek, ia akan memuat turun kod sumber untuk perpustakaan ini dan menyusunnya ke dalam projek anda.

1. Tambahkan perkara berikut ke `lib_deps`:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    Ini mengimport [PubSubClient](https://github.com/knolleary/pubsubclient), klien MQTT Arduino.

## Sambung ke WiFi

Wio Terminal kini boleh disambungkan ke WiFi.

### Tugasan - sambung ke WiFi

Sambungkan Wio Terminal ke WiFi.

1. Cipta fail baru dalam folder `src` bernama `config.h`. Anda boleh melakukannya dengan memilih folder `src`, atau fail `main.cpp` di dalamnya, dan memilih butang **New file** dari penjelajah. Butang ini hanya muncul apabila kursor anda berada di atas penjelajah.

    ![Butang fail baru](../../../../../translated_images/ms/vscode-new-file-button.182702340fe6723c.webp)

1. Tambahkan kod berikut ke fail ini untuk mentakrifkan pemalar untuk kelayakan WiFi anda:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    Gantikan `<SSID>` dengan SSID WiFi anda. Gantikan `<PASSWORD>` dengan kata laluan WiFi anda.

1. Buka fail `main.cpp`.

1. Tambahkan arahan `#include` berikut ke bahagian atas fail:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    Ini termasuk fail header untuk perpustakaan yang anda tambahkan sebelum ini, serta fail header konfigurasi. Fail header ini diperlukan untuk memberitahu PlatformIO untuk membawa masuk kod dari perpustakaan. Tanpa secara eksplisit memasukkan fail header ini, beberapa kod tidak akan disusun dan anda akan mendapat ralat penyusun.

1. Tambahkan kod berikut di atas fungsi `setup`:

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

    Kod ini akan berulang selagi peranti tidak disambungkan ke WiFi, dan mencuba sambungan menggunakan SSID dan kata laluan dari fail header konfigurasi.

1. Tambahkan panggilan kepada fungsi ini di bahagian bawah fungsi `setup`, selepas pin telah dikonfigurasikan.

    ```cpp
    connectWiFi();
    ```

1. Muat naik kod ini ke peranti anda untuk memeriksa sama ada sambungan WiFi berfungsi. Anda sepatutnya melihat ini dalam monitor bersiri.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## Sambung ke MQTT

Setelah Wio Terminal disambungkan ke WiFi, ia boleh disambungkan ke broker MQTT.

### Tugasan - sambung ke MQTT

Sambungkan ke broker MQTT.

1. Tambahkan kod berikut ke bahagian bawah fail `config.h` untuk mentakrifkan butiran sambungan untuk broker MQTT:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    Gantikan `<ID>` dengan ID unik yang akan digunakan sebagai nama klien peranti ini, dan kemudian untuk topik yang diterbitkan dan dilanggani oleh peranti ini. Broker *test.mosquitto.org* adalah awam dan digunakan oleh ramai orang, termasuk pelajar lain yang sedang menyelesaikan tugasan ini. Mempunyai nama klien MQTT dan nama topik yang unik memastikan kod anda tidak bertembung dengan kod orang lain. Anda juga akan memerlukan ID ini semasa mencipta kod pelayan kemudian dalam tugasan ini.

    > 💁 Anda boleh menggunakan laman web seperti [GUIDGen](https://www.guidgen.com) untuk menjana ID unik.

    `BROKER` ialah URL broker MQTT.

    `CLIENT_NAME` ialah nama unik untuk klien MQTT ini pada broker.

1. Buka fail `main.cpp`, dan tambahkan kod berikut di bawah fungsi `connectWiFi` dan di atas fungsi `setup`:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    Kod ini mencipta klien WiFi menggunakan perpustakaan WiFi Wio Terminal dan menggunakannya untuk mencipta klien MQTT.

1. Di bawah kod ini, tambahkan perkara berikut:

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

    Fungsi ini menguji sambungan ke broker MQTT dan menyambung semula jika ia tidak disambungkan. Ia akan berulang sepanjang masa ia tidak disambungkan dan cuba menyambung menggunakan nama klien unik yang ditakrifkan dalam fail header konfigurasi.

    Jika sambungan gagal, ia akan mencuba semula selepas 5 saat.

1. Tambahkan kod berikut di bawah fungsi `reconnectMQTTClient`:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    Kod ini menetapkan broker MQTT untuk klien, serta menetapkan panggilan balik apabila mesej diterima. Ia kemudian cuba menyambung ke broker.

1. Panggil fungsi `createMQTTClient` dalam fungsi `setup` selepas WiFi disambungkan.

1. Gantikan keseluruhan fungsi `loop` dengan perkara berikut:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    Kod ini bermula dengan menyambung semula ke broker MQTT. Sambungan ini mudah terputus, jadi adalah berbaloi untuk kerap memeriksa dan menyambung semula jika perlu. Ia kemudian memanggil kaedah `loop` pada klien MQTT untuk memproses sebarang mesej yang masuk pada topik yang dilanggani. Aplikasi ini adalah satu benang, jadi mesej tidak boleh diterima pada benang latar, oleh itu masa pada benang utama perlu diperuntukkan untuk memproses sebarang mesej yang menunggu pada sambungan rangkaian.

    Akhir sekali, kelewatan selama 2 saat memastikan tahap cahaya tidak dihantar terlalu kerap dan mengurangkan penggunaan kuasa peranti.

1. Muat naik kod ke Wio Terminal anda, dan gunakan Monitor Bersiri untuk melihat peranti menyambung ke WiFi dan MQTT.

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

> 💁 Anda boleh menemui kod ini dalam folder [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal).

😀 Anda telah berjaya menyambungkan peranti anda ke broker MQTT.

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.