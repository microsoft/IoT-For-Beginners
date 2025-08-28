<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-28T01:39:03+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "ms"
}
-->
# Sambungkan peranti IoT anda ke awan - Wio Terminal

Dalam bahagian pelajaran ini, anda akan menyambungkan Wio Terminal anda ke IoT Hub untuk menghantar telemetri dan menerima arahan.

## Sambungkan peranti anda ke IoT Hub

Langkah seterusnya adalah menyambungkan peranti anda ke IoT Hub.

### Tugas - sambungkan ke IoT Hub

1. Buka projek `soil-moisture-sensor` dalam VS Code.

1. Buka fail `platformio.ini`. Keluarkan kebergantungan pustaka `knolleary/PubSubClient`. Pustaka ini digunakan untuk menyambung ke broker MQTT awam, dan tidak diperlukan untuk menyambung ke IoT Hub.

1. Tambahkan kebergantungan pustaka berikut:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    Pustaka `Seeed Arduino RTC` menyediakan kod untuk berinteraksi dengan jam masa nyata dalam Wio Terminal, yang digunakan untuk menjejaki masa. Pustaka lain membolehkan peranti IoT anda menyambung ke IoT Hub.

1. Tambahkan yang berikut ke bahagian bawah fail `platformio.ini`:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    Ini menetapkan bendera pengkompil yang diperlukan semasa menyusun kod Arduino IoT Hub.

1. Buka fail header `config.h`. Keluarkan semua tetapan MQTT dan tambahkan pemalar berikut untuk string sambungan peranti:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    Gantikan `<connection string>` dengan string sambungan untuk peranti anda yang telah anda salin sebelum ini.

1. Sambungan ke IoT Hub menggunakan token berdasarkan masa. Ini bermaksud peranti IoT perlu mengetahui masa semasa. Tidak seperti sistem operasi seperti Windows, macOS atau Linux, mikropengawal tidak secara automatik menyegerakkan masa semasa melalui Internet. Oleh itu, anda perlu menambahkan kod untuk mendapatkan masa semasa dari pelayan [NTP](https://wikipedia.org/wiki/Network_Time_Protocol). Setelah masa diperoleh, ia boleh disimpan dalam jam masa nyata di Wio Terminal, membolehkan masa yang betul diminta pada tarikh kemudian, dengan syarat peranti tidak kehilangan kuasa. Tambahkan fail baru bernama `ntp.h` dengan kod berikut:

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

    Perincian kod ini berada di luar skop pelajaran ini. Ia mentakrifkan fungsi bernama `initTime` yang mendapatkan masa semasa dari pelayan NTP dan menggunakannya untuk menetapkan jam pada Wio Terminal.

1. Buka fail `main.cpp` dan keluarkan semua kod MQTT, termasuk fail header `PubSubClient.h`, deklarasi pemboleh ubah `PubSubClient`, kaedah `reconnectMQTTClient` dan `createMQTTClient`, serta sebarang panggilan kepada pemboleh ubah dan kaedah ini. Fail ini hanya perlu mengandungi kod untuk menyambung ke WiFi, mendapatkan kelembapan tanah, dan mencipta dokumen JSON dengannya.

1. Tambahkan arahan `#include` berikut ke bahagian atas fail `main.cpp` untuk memasukkan fail header untuk pustaka IoT Hub, dan untuk menetapkan masa:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. Tambahkan panggilan berikut ke penghujung fungsi `setup` untuk menetapkan masa semasa:

    ```cpp
    initTime();
    ```

1. Tambahkan deklarasi pemboleh ubah berikut ke bahagian atas fail, tepat di bawah arahan include:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    Ini mengisytiharkan `IOTHUB_DEVICE_CLIENT_LL_HANDLE`, iaitu pemegang untuk sambungan ke IoT Hub.

1. Di bawah ini, tambahkan kod berikut:

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

    Ini mengisytiharkan fungsi panggilan balik yang akan dipanggil apabila sambungan ke IoT Hub menukar status, seperti menyambung atau terputus. Status ini dihantar ke port bersiri.

1. Di bawah ini, tambahkan fungsi untuk menyambung ke IoT Hub:

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

    Kod ini memulakan kod pustaka IoT Hub, kemudian mencipta sambungan menggunakan string sambungan dalam fail header `config.h`. Sambungan ini berdasarkan MQTT. Jika sambungan gagal, ini dihantar ke port bersiri - jika anda melihat ini dalam output, periksa string sambungan. Akhirnya, panggilan balik status sambungan disediakan.

1. Panggil fungsi ini dalam fungsi `setup` di bawah panggilan ke `initTime`:

    ```cpp
    connectIoTHub();
    ```

1. Sama seperti dengan klien MQTT, kod ini berjalan pada satu thread, jadi memerlukan masa untuk memproses mesej yang dihantar oleh hub dan dihantar ke hub. Tambahkan yang berikut ke bahagian atas fungsi `loop` untuk melakukannya:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. Bina dan muat naik kod ini. Anda akan melihat sambungan dalam monitor bersiri:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    Dalam output, anda boleh melihat masa NTP diambil, diikuti oleh klien peranti menyambung. Ia mungkin mengambil masa beberapa saat untuk menyambung, jadi anda mungkin melihat kelembapan tanah dalam output semasa peranti menyambung.

    > 💁 Anda boleh menukar masa UNIX untuk NTP kepada versi yang lebih mudah dibaca menggunakan laman web seperti [unixtimestamp.com](https://www.unixtimestamp.com)

## Hantar telemetri

Sekarang peranti anda telah disambungkan, anda boleh menghantar telemetri ke IoT Hub dan bukannya broker MQTT.

### Tugas - hantar telemetri

1. Tambahkan fungsi berikut di atas fungsi `setup`:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    Kod ini mencipta mesej IoT Hub daripada string yang dihantar sebagai parameter, menghantarnya ke hub, kemudian membersihkan objek mesej.

1. Panggil kod ini dalam fungsi `loop`, tepat selepas baris di mana telemetri dihantar ke port bersiri:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## Tangani arahan

Peranti anda perlu menangani arahan daripada kod pelayan untuk mengawal relay. Ini dihantar sebagai permintaan kaedah langsung.

## Tugas - tangani permintaan kaedah langsung

1. Tambahkan kod berikut sebelum fungsi `connectIoTHub`:

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

    Kod ini mentakrifkan kaedah panggilan balik yang boleh dipanggil oleh pustaka IoT Hub apabila ia menerima permintaan kaedah langsung. Kaedah yang diminta dihantar dalam parameter `method_name`. Fungsi ini mencetak kaedah yang dipanggil ke port bersiri, kemudian menghidupkan atau mematikan relay bergantung pada nama kaedah.

    > 💁 Ini juga boleh dilaksanakan dalam satu permintaan kaedah langsung, dengan menghantar keadaan relay yang diinginkan dalam payload yang boleh dihantar bersama permintaan kaedah dan tersedia daripada parameter `payload`.

1. Tambahkan kod berikut ke penghujung fungsi `directMethodCallback`:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    Permintaan kaedah langsung memerlukan respons, dan respons ini terdiri daripada dua bahagian - respons sebagai teks, dan kod pemulangan. Kod ini akan mencipta hasil sebagai dokumen JSON berikut:

    ```JSON
    {
        "Result": ""
    }
    ```

    Ini kemudian disalin ke parameter `response`, dan saiz respons ini ditetapkan dalam parameter `response_size`. Kod ini kemudian mengembalikan `IOTHUB_CLIENT_OK` untuk menunjukkan kaedah telah ditangani dengan betul.

1. Sambungkan panggilan balik dengan menambahkan yang berikut ke penghujung fungsi `connectIoTHub`:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. Fungsi `loop` akan memanggil fungsi `IoTHubDeviceClient_LL_DoWork` untuk memproses acara yang dihantar oleh IoT Hub. Ini hanya dipanggil setiap 10 saat disebabkan oleh `delay`, bermakna kaedah langsung hanya diproses setiap 10 saat. Untuk menjadikannya lebih cekap, kelewatan 10 saat boleh dilaksanakan sebagai banyak kelewatan yang lebih pendek, memanggil `IoTHubDeviceClient_LL_DoWork` setiap kali. Untuk melakukannya, tambahkan kod berikut di atas fungsi `loop`:

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

    Kod ini akan mengulangi secara berulang, memanggil `IoTHubDeviceClient_LL_DoWork` dan melengahkan selama 100ms setiap kali. Ia akan melakukannya sebanyak yang diperlukan untuk melengahkan selama masa yang diberikan dalam parameter `delay_time`. Ini bermakna peranti menunggu paling lama 100ms untuk memproses permintaan kaedah langsung.

1. Dalam fungsi `loop`, keluarkan panggilan ke `IoTHubDeviceClient_LL_DoWork`, dan gantikan panggilan `delay(10000)` dengan yang berikut untuk memanggil fungsi baru ini:

    ```cpp
    work_delay(10000);
    ```

> 💁 Anda boleh menemui kod ini dalam folder [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal).

😀 Program sensor kelembapan tanah anda kini disambungkan ke IoT Hub!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat penting, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.