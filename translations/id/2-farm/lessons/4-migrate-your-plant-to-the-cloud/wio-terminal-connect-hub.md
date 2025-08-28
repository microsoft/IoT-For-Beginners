<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-28T01:38:38+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "id"
}
-->
# Hubungkan Perangkat IoT Anda ke Cloud - Wio Terminal

Dalam bagian pelajaran ini, Anda akan menghubungkan Wio Terminal Anda ke IoT Hub untuk mengirim telemetri dan menerima perintah.

## Hubungkan perangkat Anda ke IoT Hub

Langkah berikutnya adalah menghubungkan perangkat Anda ke IoT Hub.

### Tugas - hubungkan ke IoT Hub

1. Buka proyek `soil-moisture-sensor` di VS Code.

1. Buka file `platformio.ini`. Hapus dependensi pustaka `knolleary/PubSubClient`. Pustaka ini digunakan untuk terhubung ke broker MQTT publik, dan tidak diperlukan untuk terhubung ke IoT Hub.

1. Tambahkan dependensi pustaka berikut:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    Pustaka `Seeed Arduino RTC` menyediakan kode untuk berinteraksi dengan jam waktu nyata di Wio Terminal, yang digunakan untuk melacak waktu. Pustaka lainnya memungkinkan perangkat IoT Anda terhubung ke IoT Hub.

1. Tambahkan yang berikut ini ke bagian bawah file `platformio.ini`:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    Ini menetapkan flag compiler yang diperlukan saat mengompilasi kode Arduino IoT Hub.

1. Buka file header `config.h`. Hapus semua pengaturan MQTT dan tambahkan konstanta berikut untuk string koneksi perangkat:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    Ganti `<connection string>` dengan string koneksi untuk perangkat Anda yang telah Anda salin sebelumnya.

1. Koneksi ke IoT Hub menggunakan token berbasis waktu. Ini berarti perangkat IoT perlu mengetahui waktu saat ini. Tidak seperti sistem operasi seperti Windows, macOS, atau Linux, mikrokontroler tidak secara otomatis menyinkronkan waktu saat ini melalui Internet. Ini berarti Anda perlu menambahkan kode untuk mendapatkan waktu saat ini dari [NTP](https://wikipedia.org/wiki/Network_Time_Protocol) server. Setelah waktu diperoleh, waktu tersebut dapat disimpan di jam waktu nyata di Wio Terminal, memungkinkan waktu yang benar diminta di kemudian hari, dengan asumsi perangkat tidak kehilangan daya. Tambahkan file baru bernama `ntp.h` dengan kode berikut:

    ```cpp
    #pragma once
    
    #include "DateTime.h"
    #include <time.h>
    #include "samd/NTPClientAz.h"
    #include <sys/time.h>

    static void initTime()
    {
        WiFiUDP _udp;
        time_t epochTime = (time_t)-1;
        NTPClientAz ntpClient;

        ntpClient.begin();

        while (true)
        {
            epochTime = ntpClient.getEpochTime("0.pool.ntp.org");

            if (epochTime == (time_t)-1)
            {
                Serial.println("Fetching NTP epoch time failed! Waiting 2 seconds to retry.");
                delay(2000);
            }
            else
            {
                Serial.print("Fetched NTP epoch time is: ");

                char buff[32];
                sprintf(buff, "%.f", difftime(epochTime, (time_t)0));
                Serial.println(buff);
                break;
            }
        }

        ntpClient.end();

        struct timeval tv;
        tv.tv_sec = epochTime;
        tv.tv_usec = 0;

        settimeofday(&tv, NULL);
    }
    ```

    Detail kode ini berada di luar cakupan pelajaran ini. Kode ini mendefinisikan fungsi bernama `initTime` yang mendapatkan waktu saat ini dari server NTP dan menggunakannya untuk mengatur jam di Wio Terminal.

1. Buka file `main.cpp` dan hapus semua kode MQTT, termasuk file header `PubSubClient.h`, deklarasi variabel `PubSubClient`, metode `reconnectMQTTClient` dan `createMQTTClient`, serta semua panggilan ke variabel dan metode ini. File ini hanya boleh berisi kode untuk terhubung ke WiFi, mendapatkan kelembapan tanah, dan membuat dokumen JSON darinya.

1. Tambahkan direktif `#include` berikut ke bagian atas file `main.cpp` untuk menyertakan file header untuk pustaka IoT Hub, dan untuk mengatur waktu:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. Tambahkan panggilan berikut ke akhir fungsi `setup` untuk mengatur waktu saat ini:

    ```cpp
    initTime();
    ```

1. Tambahkan deklarasi variabel berikut ke bagian atas file, tepat di bawah direktif include:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    Ini mendeklarasikan `IOTHUB_DEVICE_CLIENT_LL_HANDLE`, sebuah handle untuk koneksi ke IoT Hub.

1. Di bawah ini, tambahkan kode berikut:

    ```cpp
    static void connectionStatusCallback(IOTHUB_CLIENT_CONNECTION_STATUS result, IOTHUB_CLIENT_CONNECTION_STATUS_REASON reason, void *user_context)
    {
        if (result == IOTHUB_CLIENT_CONNECTION_AUTHENTICATED)
        {
            Serial.println("The device client is connected to iothub");
        }
        else
        {
            Serial.println("The device client has been disconnected");
        }
    }
    ```

    Ini mendeklarasikan fungsi callback yang akan dipanggil saat koneksi ke IoT Hub mengubah status, seperti terhubung atau terputus. Status ini dikirim ke port serial.

1. Di bawah ini, tambahkan fungsi untuk terhubung ke IoT Hub:

    ```cpp
    void connectIoTHub()
    {
        IoTHub_Init();
    
        _device_ll_handle = IoTHubDeviceClient_LL_CreateFromConnectionString(CONNECTION_STRING, MQTT_Protocol);
        
        if (_device_ll_handle == NULL)
        {
            Serial.println("Failure creating Iothub device. Hint: Check your connection string.");
            return;
        }
    
        IoTHubDeviceClient_LL_SetConnectionStatusCallback(_device_ll_handle, connectionStatusCallback, NULL);
    }
    ```

    Kode ini menginisialisasi kode pustaka IoT Hub, lalu membuat koneksi menggunakan string koneksi di file header `config.h`. Koneksi ini berbasis MQTT. Jika koneksi gagal, ini akan dikirim ke port serial - jika Anda melihat ini di output, periksa string koneksi. Akhirnya, callback status koneksi diatur.

1. Panggil fungsi ini di fungsi `setup` di bawah panggilan ke `initTime`:

    ```cpp
    connectIoTHub();
    ```

1. Sama seperti dengan klien MQTT, kode ini berjalan pada satu thread sehingga membutuhkan waktu untuk memproses pesan yang dikirim oleh hub, dan dikirim ke hub. Tambahkan yang berikut ini ke bagian atas fungsi `loop` untuk melakukannya:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. Bangun dan unggah kode ini. Anda akan melihat koneksi di monitor serial:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    Dalam output, Anda dapat melihat waktu NTP diambil, diikuti oleh klien perangkat yang terhubung. Mungkin butuh beberapa detik untuk terhubung, jadi Anda mungkin melihat kelembapan tanah di output sementara perangkat sedang terhubung.

    > 💁 Anda dapat mengonversi waktu UNIX untuk NTP ke versi yang lebih mudah dibaca menggunakan situs web seperti [unixtimestamp.com](https://www.unixtimestamp.com)

## Kirim telemetri

Sekarang perangkat Anda terhubung, Anda dapat mengirim telemetri ke IoT Hub alih-alih broker MQTT.

### Tugas - kirim telemetri

1. Tambahkan fungsi berikut di atas fungsi `setup`:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    Kode ini membuat pesan IoT Hub dari string yang diteruskan sebagai parameter, mengirimkannya ke hub, lalu membersihkan objek pesan.

1. Panggil kode ini di fungsi `loop`, tepat setelah baris di mana telemetri dikirim ke port serial:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## Tangani perintah

Perangkat Anda perlu menangani perintah dari kode server untuk mengontrol relay. Ini dikirim sebagai permintaan metode langsung.

## Tugas - tangani permintaan metode langsung

1. Tambahkan kode berikut sebelum fungsi `connectIoTHub`:

    ```cpp
    int directMethodCallback(const char *method_name, const unsigned char *payload, size_t size, unsigned char **response, size_t *response_size, void *userContextCallback)
    {
        Serial.printf("Direct method received %s\r\n", method_name);
    
        if (strcmp(method_name, "relay_on") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, HIGH);
        }
        else if (strcmp(method_name, "relay_off") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, LOW);
        }
    }
    ```

    Kode ini mendefinisikan metode callback yang dapat dipanggil pustaka IoT Hub saat menerima permintaan metode langsung. Metode yang diminta dikirim dalam parameter `method_name`. Fungsi ini mencetak metode yang dipanggil ke port serial, lalu menyalakan atau mematikan relay tergantung pada nama metode.

    > 💁 Ini juga dapat diimplementasikan dalam satu permintaan metode langsung, dengan meneruskan status yang diinginkan dari relay dalam payload yang dapat diteruskan dengan permintaan metode dan tersedia dari parameter `payload`.

1. Tambahkan kode berikut ke akhir fungsi `directMethodCallback`:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    Permintaan metode langsung memerlukan respons, dan respons ini terdiri dari dua bagian - respons sebagai teks, dan kode pengembalian. Kode ini akan membuat hasil sebagai dokumen JSON berikut:

    ```JSON
    {
        "Result": ""
    }
    ```

    Ini kemudian disalin ke parameter `response`, dan ukuran respons ini diatur dalam parameter `response_size`. Kode ini kemudian mengembalikan `IOTHUB_CLIENT_OK` untuk menunjukkan bahwa metode telah ditangani dengan benar.

1. Sambungkan callback dengan menambahkan yang berikut ini ke akhir fungsi `connectIoTHub`:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. Fungsi `loop` akan memanggil fungsi `IoTHubDeviceClient_LL_DoWork` untuk memproses peristiwa yang dikirim oleh IoT Hub. Fungsi ini hanya dipanggil setiap 10 detik karena `delay`, yang berarti metode langsung hanya diproses setiap 10 detik. Untuk membuat ini lebih efisien, penundaan 10 detik dapat diimplementasikan sebagai banyak penundaan yang lebih pendek, memanggil `IoTHubDeviceClient_LL_DoWork` setiap kali. Untuk melakukannya, tambahkan kode berikut di atas fungsi `loop`:

    ```cpp
    void work_delay(int delay_time)
    {
        int current = 0;
        do
        {
            IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
            delay(100);
            current += 100;
        } while (current < delay_time);
    }
    ```

    Kode ini akan mengulang berulang kali, memanggil `IoTHubDeviceClient_LL_DoWork` dan menunda selama 100ms setiap kali. Ini akan dilakukan sebanyak yang diperlukan untuk menunda selama waktu yang diberikan dalam parameter `delay_time`. Ini berarti perangkat menunggu paling lama 100ms untuk memproses permintaan metode langsung.

1. Dalam fungsi `loop`, hapus panggilan ke `IoTHubDeviceClient_LL_DoWork`, dan ganti panggilan `delay(10000)` dengan yang berikut ini untuk memanggil fungsi baru ini:

    ```cpp
    work_delay(10000);
    ```

> 💁 Anda dapat menemukan kode ini di folder [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal).

😀 Program sensor kelembapan tanah Anda sekarang terhubung ke IoT Hub!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.