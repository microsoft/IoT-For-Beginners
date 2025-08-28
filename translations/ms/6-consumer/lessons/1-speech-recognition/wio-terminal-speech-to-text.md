<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-27T23:36:21+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "ms"
}
-->
# Ucapan ke Teks - Wio Terminal

Dalam bahagian pelajaran ini, anda akan menulis kod untuk menukar ucapan dalam audio yang ditangkap kepada teks menggunakan perkhidmatan ucapan.

## Hantar audio ke perkhidmatan ucapan

Audio boleh dihantar ke perkhidmatan ucapan menggunakan REST API. Untuk menggunakan perkhidmatan ucapan, pertama anda perlu meminta token akses, kemudian gunakan token tersebut untuk mengakses REST API. Token akses ini akan tamat tempoh selepas 10 minit, jadi kod anda perlu memintanya secara berkala untuk memastikan ia sentiasa terkini.

### Tugasan - dapatkan token akses

1. Buka projek `smart-timer` jika ia belum dibuka.

1. Tambahkan kebergantungan perpustakaan berikut ke fail `platformio.ini` untuk mengakses WiFi dan mengendalikan JSON:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. Tambahkan kod berikut ke fail header `config.h`:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    Gantikan `<SSID>` dan `<PASSWORD>` dengan nilai yang relevan untuk WiFi anda.

    Gantikan `<API_KEY>` dengan kunci API untuk sumber perkhidmatan ucapan anda. Gantikan `<LOCATION>` dengan lokasi yang anda gunakan semasa mencipta sumber perkhidmatan ucapan.

    Gantikan `<LANGUAGE>` dengan nama lokal untuk bahasa yang akan anda gunakan, contohnya `en-GB` untuk Bahasa Inggeris, atau `zn-HK` untuk Bahasa Kantonis. Anda boleh mencari senarai bahasa yang disokong dan nama lokal mereka dalam [dokumentasi sokongan bahasa dan suara di Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Konstanta `TOKEN_URL` adalah URL penerbit token tanpa lokasi. Ini akan digabungkan dengan lokasi kemudian untuk mendapatkan URL penuh.

1. Sama seperti menyambung ke Custom Vision, anda perlu menggunakan sambungan HTTPS untuk menyambung ke perkhidmatan penerbit token. Tambahkan kod berikut ke akhir `config.h`:

    ```cpp
    const char *TOKEN_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "MIIF8zCCBNugAwIBAgIQAueRcfuAIek/4tmDg0xQwDANBgkqhkiG9w0BAQwFADBh\r\n"
        "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\r\n"
        "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBH\r\n"
        "MjAeFw0yMDA3MjkxMjMwMDBaFw0yNDA2MjcyMzU5NTlaMFkxCzAJBgNVBAYTAlVT\r\n"
        "MR4wHAYDVQQKExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xKjAoBgNVBAMTIU1pY3Jv\r\n"
        "c29mdCBBenVyZSBUTFMgSXNzdWluZyBDQSAwNjCCAiIwDQYJKoZIhvcNAQEBBQAD\r\n"
        "ggIPADCCAgoCggIBALVGARl56bx3KBUSGuPc4H5uoNFkFH4e7pvTCxRi4j/+z+Xb\r\n"
        "wjEz+5CipDOqjx9/jWjskL5dk7PaQkzItidsAAnDCW1leZBOIi68Lff1bjTeZgMY\r\n"
        "iwdRd3Y39b/lcGpiuP2d23W95YHkMMT8IlWosYIX0f4kYb62rphyfnAjYb/4Od99\r\n"
        "ThnhlAxGtfvSbXcBVIKCYfZgqRvV+5lReUnd1aNjRYVzPOoifgSx2fRyy1+pO1Uz\r\n"
        "aMMNnIOE71bVYW0A1hr19w7kOb0KkJXoALTDDj1ukUEDqQuBfBxReL5mXiu1O7WG\r\n"
        "0vltg0VZ/SZzctBsdBlx1BkmWYBW261KZgBivrql5ELTKKd8qgtHcLQA5fl6JB0Q\r\n"
        "gs5XDaWehN86Gps5JW8ArjGtjcWAIP+X8CQaWfaCnuRm6Bk/03PQWhgdi84qwA0s\r\n"
        "sRfFJwHUPTNSnE8EiGVk2frt0u8PG1pwSQsFuNJfcYIHEv1vOzP7uEOuDydsmCjh\r\n"
        "lxuoK2n5/2aVR3BMTu+p4+gl8alXoBycyLmj3J/PUgqD8SL5fTCUegGsdia/Sa60\r\n"
        "N2oV7vQ17wjMN+LXa2rjj/b4ZlZgXVojDmAjDwIRdDUujQu0RVsJqFLMzSIHpp2C\r\n"
        "Zp7mIoLrySay2YYBu7SiNwL95X6He2kS8eefBBHjzwW/9FxGqry57i71c2cDAgMB\r\n"
        "AAGjggGtMIIBqTAdBgNVHQ4EFgQU1cFnOsKjnfR3UltZEjgp5lVou6UwHwYDVR0j\r\n"
        "BBgwFoAUTiJUIBiV5uNu5g/6+rkS7QYXjzkwDgYDVR0PAQH/BAQDAgGGMB0GA1Ud\r\n"
        "JQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjASBgNVHRMBAf8ECDAGAQH/AgEAMHYG\r\n"
        "CCsGAQUFBwEBBGowaDAkBggrBgEFBQcwAYYYaHR0cDovL29jc3AuZGlnaWNlcnQu\r\n"
        "Y29tMEAGCCsGAQUFBzAChjRodHRwOi8vY2FjZXJ0cy5kaWdpY2VydC5jb20vRGln\r\n"
        "aUNlcnRHbG9iYWxSb290RzIuY3J0MHsGA1UdHwR0MHIwN6A1oDOGMWh0dHA6Ly9j\r\n"
        "cmwzLmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5jcmwwN6A1oDOG\r\n"
        "MWh0dHA6Ly9jcmw0LmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5j\r\n"
        "cmwwHQYDVR0gBBYwFDAIBgZngQwBAgEwCAYGZ4EMAQICMBAGCSsGAQQBgjcVAQQD\r\n"
        "AgEAMA0GCSqGSIb3DQEBDAUAA4IBAQB2oWc93fB8esci/8esixj++N22meiGDjgF\r\n"
        "+rA2LUK5IOQOgcUSTGKSqF9lYfAxPjrqPjDCUPHCURv+26ad5P/BYtXtbmtxJWu+\r\n"
        "cS5BhMDPPeG3oPZwXRHBJFAkY4O4AF7RIAAUW6EzDflUoDHKv83zOiPfYGcpHc9s\r\n"
        "kxAInCedk7QSgXvMARjjOqdakor21DTmNIUotxo8kHv5hwRlGhBJwps6fEVi1Bt0\r\n"
        "trpM/3wYxlr473WSPUFZPgP1j519kLpWOJ8z09wxay+Br29irPcBYv0GMXlHqThy\r\n"
        "8y4m/HyTQeI2IMvMrQnwqPpY+rLIXyviI2vLoI+4xKE4Rn38ZZ8m\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

    Ini adalah sijil yang sama yang anda gunakan semasa menyambung ke Custom Vision.

1. Tambahkan arahan include untuk fail header WiFi dan fail header config ke bahagian atas fail `main.cpp`:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. Tambahkan kod untuk menyambung ke WiFi dalam `main.cpp` di atas fungsi `setup`:

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

1. Panggil fungsi ini dari fungsi `setup` selepas sambungan serial telah ditubuhkan:

    ```cpp
    connectWiFi();
    ```

1. Cipta fail header baru dalam folder `src` yang dipanggil `speech_to_text.h`. Dalam fail header ini, tambahkan kod berikut:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClientSecure.h>
    
    #include "config.h"
    #include "mic.h"
    
    class SpeechToText
    {
    public:

    private:

    };

    SpeechToText speechToText;
    ```

    Ini termasuk beberapa fail header yang diperlukan untuk sambungan HTTP, konfigurasi, dan fail header `mic.h`, serta mendefinisikan kelas bernama `SpeechToText`, sebelum mengisytiharkan satu instance kelas tersebut yang boleh digunakan kemudian.

1. Tambahkan 2 medan berikut ke bahagian `private` kelas ini:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client` adalah WiFi Client yang menggunakan HTTPS dan akan digunakan untuk mendapatkan token akses. Token ini kemudian akan disimpan dalam `_access_token`.

1. Tambahkan kaedah berikut ke bahagian `private`:

    ```cpp
    String getAccessToken()
    {
        char url[128];
        sprintf(url, TOKEN_URL, SPEECH_LOCATION);
    
        HTTPClient httpClient;
        httpClient.begin(_token_client, url);
    
        httpClient.addHeader("Ocp-Apim-Subscription-Key", SPEECH_API_KEY);
        int httpResultCode = httpClient.POST("{}");
    
        if (httpResultCode != 200)
        {
            Serial.println("Error getting access token, trying again...");
            delay(10000);
            return getAccessToken();
        }
    
        Serial.println("Got access token.");
        String result = httpClient.getString();
    
        httpClient.end();
    
        return result;
    }
    ```

    Kod ini membina URL untuk API penerbit token menggunakan lokasi sumber ucapan. Ia kemudian mencipta `HTTPClient` untuk membuat permintaan web, mengkonfigurasinya untuk menggunakan WiFi client yang disediakan dengan sijil endpoint token. Ia menetapkan kunci API sebagai header untuk panggilan. Ia kemudian membuat permintaan POST untuk mendapatkan sijil, mencuba semula jika terdapat sebarang ralat. Akhirnya token akses dikembalikan.

1. Ke bahagian `public`, tambahkan kaedah untuk mendapatkan token akses. Ini akan diperlukan dalam pelajaran seterusnya untuk menukar teks kepada ucapan.

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. Ke bahagian `public`, tambahkan kaedah `init` yang menyediakan token client:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    Ini menetapkan sijil pada WiFi client, kemudian mendapatkan token akses.

1. Dalam `main.cpp`, tambahkan fail header baru ini ke arahan include:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Inisialisasi kelas `SpeechToText` di akhir fungsi `setup`, selepas panggilan `mic.init` tetapi sebelum `Ready` ditulis ke monitor serial:

    ```cpp
    speechToText.init();
    ```

### Tugasan - baca audio dari memori flash

1. Dalam bahagian pelajaran sebelumnya, audio telah direkodkan ke memori flash. Audio ini perlu dihantar ke REST API Perkhidmatan Ucapan, jadi ia perlu dibaca dari memori flash. Ia tidak boleh dimuatkan ke dalam buffer dalam memori kerana ia terlalu besar. Kelas `HTTPClient` yang membuat panggilan REST boleh menstrim data menggunakan Arduino Stream - kelas yang boleh memuatkan data dalam blok kecil, menghantar blok satu demi satu sebagai sebahagian daripada permintaan. Setiap kali anda memanggil `read` pada stream, ia mengembalikan blok data seterusnya. Stream Arduino boleh dicipta untuk membaca dari memori flash. Cipta fail baru yang dipanggil `flash_stream.h` dalam folder `src`, dan tambahkan kod berikut kepadanya:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <HTTPClient.h>
    #include <sfud.h>

    #include "config.h"
    
    class FlashStream : public Stream
    {
    public:
        virtual size_t write(uint8_t val)
        {    
        }
    
        virtual int available()
        {
        }
    
        virtual int read()
        {
        }
    
        virtual int peek()
        {
        }
    private:
    
    };
    ```

    Ini mengisytiharkan kelas `FlashStream`, yang berasal dari kelas `Stream` Arduino. Ini adalah kelas abstrak - kelas yang berasal perlu melaksanakan beberapa kaedah sebelum kelas boleh diinstansikan, dan kaedah-kaedah ini ditakrifkan dalam kelas ini.

    ✅ Baca lebih lanjut tentang Arduino Streams dalam [dokumentasi Stream Arduino](https://www.arduino.cc/reference/en/language/functions/communication/stream/)

1. Tambahkan medan berikut ke bahagian `private`:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    Ini mendefinisikan buffer sementara untuk menyimpan data yang dibaca dari memori flash, bersama dengan medan untuk menyimpan posisi semasa semasa membaca dari buffer, alamat semasa untuk membaca dari memori flash, dan peranti memori flash.

1. Dalam bahagian `private`, tambahkan kaedah berikut:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    Kod ini membaca dari memori flash pada alamat semasa dan menyimpan data dalam buffer. Ia kemudian meningkatkan alamat, jadi panggilan seterusnya membaca blok memori seterusnya. Buffer bersaiz berdasarkan blok terbesar yang akan dihantar oleh `HTTPClient` ke REST API pada satu masa.

    > 💁 Memadam memori flash perlu dilakukan menggunakan saiz grain, membaca sebaliknya tidak.

1. Dalam bahagian `public` kelas ini, tambahkan pembina:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    Pembina ini menyediakan semua medan untuk mula membaca dari permulaan blok memori flash, dan memuatkan blok data pertama ke dalam buffer.

1. Laksanakan kaedah `write`. Stream ini hanya akan membaca data, jadi ini boleh tidak melakukan apa-apa dan mengembalikan 0:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. Laksanakan kaedah `peek`. Ini mengembalikan data pada posisi semasa tanpa menggerakkan stream. Memanggil `peek` beberapa kali akan sentiasa mengembalikan data yang sama selagi tiada data dibaca dari stream.

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. Laksanakan fungsi `available`. Ini mengembalikan berapa banyak byte yang boleh dibaca dari stream, atau -1 jika stream selesai. Untuk kelas ini, maksimum yang tersedia tidak akan lebih daripada saiz chunk HTTPClient. Apabila stream ini digunakan dalam HTTP client, ia memanggil fungsi ini untuk melihat berapa banyak data yang tersedia, kemudian meminta sebanyak itu untuk dihantar ke REST API. Kita tidak mahu setiap chunk lebih daripada saiz chunk HTTP client, jadi jika lebih daripada itu tersedia, saiz chunk dikembalikan. Jika kurang, maka apa yang tersedia dikembalikan. Setelah semua data telah distrim, -1 dikembalikan.

    ```cpp
    virtual int available()
    {
        int remaining = BUFFER_SIZE - ((_flash_address - HTTP_TCP_BUFFER_SIZE) + _pos);
        int bytes_available = min(HTTP_TCP_BUFFER_SIZE, remaining);

        if (bytes_available == 0)
        {
            bytes_available = -1;
        }

        return bytes_available;
    }
    ```

1. Laksanakan kaedah `read` untuk mengembalikan byte seterusnya dari buffer, meningkatkan posisi. Jika posisi melebihi saiz buffer, ia mengisi buffer dengan blok seterusnya dari memori flash dan menetapkan semula posisi.

    ```cpp
    virtual int read()
    {
        int retVal = _buffer[_pos++];

        if (_pos == HTTP_TCP_BUFFER_SIZE)
        {
            populateBuffer();
        }

        return retVal;
    }
    ```

1. Dalam fail header `speech_to_text.h`, tambahkan arahan include untuk fail header baru ini:

    ```cpp
    #include "flash_stream.h"
    ```

### Tugasan - tukar ucapan kepada teks

1. Ucapan boleh ditukar kepada teks dengan menghantar audio ke Perkhidmatan Ucapan melalui REST API. REST API ini mempunyai sijil yang berbeza daripada penerbit token, jadi tambahkan kod berikut ke fail header `config.h` untuk mendefinisikan sijil ini:

    ```cpp
    const char *SPEECH_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "MIIF8zCCBNugAwIBAgIQCq+mxcpjxFFB6jvh98dTFzANBgkqhkiG9w0BAQwFADBh\r\n"
        "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\r\n"
        "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBH\r\n"
        "MjAeFw0yMDA3MjkxMjMwMDBaFw0yNDA2MjcyMzU5NTlaMFkxCzAJBgNVBAYTAlVT\r\n"
        "MR4wHAYDVQQKExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xKjAoBgNVBAMTIU1pY3Jv\r\n"
        "c29mdCBBenVyZSBUTFMgSXNzdWluZyBDQSAwMTCCAiIwDQYJKoZIhvcNAQEBBQAD\r\n"
        "ggIPADCCAgoCggIBAMedcDrkXufP7pxVm1FHLDNA9IjwHaMoaY8arqqZ4Gff4xyr\r\n"
        "RygnavXL7g12MPAx8Q6Dd9hfBzrfWxkF0Br2wIvlvkzW01naNVSkHp+OS3hL3W6n\r\n"
        "l/jYvZnVeJXjtsKYcXIf/6WtspcF5awlQ9LZJcjwaH7KoZuK+THpXCMtzD8XNVdm\r\n"
        "GW/JI0C/7U/E7evXn9XDio8SYkGSM63aLO5BtLCv092+1d4GGBSQYolRq+7Pd1kR\r\n"
        "EkWBPm0ywZ2Vb8GIS5DLrjelEkBnKCyy3B0yQud9dpVsiUeE7F5sY8Me96WVxQcb\r\n"
        "OyYdEY/j/9UpDlOG+vA+YgOvBhkKEjiqygVpP8EZoMMijephzg43b5Qi9r5UrvYo\r\n"
        "o19oR/8pf4HJNDPF0/FJwFVMW8PmCBLGstin3NE1+NeWTkGt0TzpHjgKyfaDP2tO\r\n"
        "4bCk1G7pP2kDFT7SYfc8xbgCkFQ2UCEXsaH/f5YmpLn4YPiNFCeeIida7xnfTvc4\r\n"
        "7IxyVccHHq1FzGygOqemrxEETKh8hvDR6eBdrBwmCHVgZrnAqnn93JtGyPLi6+cj\r\n"
        "WGVGtMZHwzVvX1HvSFG771sskcEjJxiQNQDQRWHEh3NxvNb7kFlAXnVdRkkvhjpR\r\n"
        "GchFhTAzqmwltdWhWDEyCMKC2x/mSZvZtlZGY+g37Y72qHzidwtyW7rBetZJAgMB\r\n"
        "AAGjggGtMIIBqTAdBgNVHQ4EFgQUDyBd16FXlduSzyvQx8J3BM5ygHYwHwYDVR0j\r\n"
        "BBgwFoAUTiJUIBiV5uNu5g/6+rkS7QYXjzkwDgYDVR0PAQH/BAQDAgGGMB0GA1Ud\r\n"
        "JQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjASBgNVHRMBAf8ECDAGAQH/AgEAMHYG\r\n"
        "CCsGAQUFBwEBBGowaDAkBggrBgEFBQcwAYYYaHR0cDovL29jc3AuZGlnaWNlcnQu\r\n"
        "Y29tMEAGCCsGAQUFBzAChjRodHRwOi8vY2FjZXJ0cy5kaWdpY2VydC5jb20vRGln\r\n"
        "aUNlcnRHbG9iYWxSb290RzIuY3J0MHsGA1UdHwR0MHIwN6A1oDOGMWh0dHA6Ly9j\r\n"
        "cmwzLmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5jcmwwN6A1oDOG\r\n"
        "MWh0dHA6Ly9jcmw0LmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5j\r\n"
        "cmwwHQYDVR0gBBYwFDAIBgZngQwBAgEwCAYGZ4EMAQICMBAGCSsGAQQBgjcVAQQD\r\n"
        "AgEAMA0GCSqGSIb3DQEBDAUAA4IBAQAlFvNh7QgXVLAZSsNR2XRmIn9iS8OHFCBA\r\n"
        "WxKJoi8YYQafpMTkMqeuzoL3HWb1pYEipsDkhiMnrpfeYZEA7Lz7yqEEtfgHcEBs\r\n"
        "K9KcStQGGZRfmWU07hPXHnFz+5gTXqzCE2PBMlRgVUYJiA25mJPXfB00gDvGhtYa\r\n"
        "+mENwM9Bq1B9YYLyLjRtUz8cyGsdyTIG/bBM/Q9jcV8JGqMU/UjAdh1pFyTnnHEl\r\n"
        "Y59Npi7F87ZqYYJEHJM2LGD+le8VsHjgeWX2CJQko7klXvcizuZvUEDTjHaQcs2J\r\n"
        "+kPgfyMIOY1DMJ21NxOJ2xPRC/wAh/hzSBRVtoAnyuxtkZ4VjIOh\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Tambahkan konstanta ke fail ini untuk URL ucapan tanpa lokasi. Ini akan digabungkan dengan lokasi dan bahasa kemudian untuk mendapatkan URL penuh.

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. Dalam fail header `speech_to_text.h`, dalam bahagian `private` kelas `SpeechToText`, definisikan medan untuk WiFi Client menggunakan sijil ucapan:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. Dalam kaedah `init`, tetapkan sijil pada WiFi Client ini:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. Tambahkan kod berikut ke bahagian `public` kelas `SpeechToText` untuk mendefinisikan kaedah untuk menukar ucapan kepada teks:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. Tambahkan kod berikut ke kaedah ini untuk mencipta HTTP client menggunakan WiFi client yang dikonfigurasi dengan sijil ucapan, dan menggunakan URL ucapan yang ditetapkan dengan lokasi dan bahasa:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. Beberapa header perlu ditetapkan pada sambungan:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    Ini menetapkan header untuk pengesahan menggunakan token akses, format audio menggunakan kadar sampel, dan menetapkan bahawa client mengharapkan hasil sebagai JSON.

1. Selepas ini, tambahkan kod berikut untuk membuat panggilan REST API:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    Ini mencipta `FlashStream` dan menggunakannya untuk menstrim data ke REST API.

1. Di bawah ini, tambahkan kod berikut:

    ```cpp
    String text = "";

    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonObject obj = doc.as<JsonObject>();
        text = obj["DisplayText"].as<String>();
    }
    else if (httpResponseCode == 401)
    {
        Serial.println("Access token expired, trying again with a new token");
        _access_token = getAccessToken();
        return convertSpeechToText();
    }
    else
    {
        Serial.print("Failed to convert text to speech - error ");
        Serial.println(httpResponseCode);
    }
    ```

    Kod ini memeriksa kod respons.

    Jika ia adalah 200, kod untuk kejayaan, maka hasilnya diambil, dinyahkod dari JSON, dan properti `DisplayText` ditetapkan ke dalam variabel `text`. Ini adalah properti di mana versi teks ucapan dikembalikan.

    Jika kod respons adalah 401, maka token akses telah tamat tempoh (token ini hanya bertahan selama 10 minit). Token akses baru diminta, dan panggilan dibuat semula.

    Jika tidak, ralat dihantar ke monitor serial, dan `text` dibiarkan kosong.

1. Tambahkan kod berikut ke akhir kaedah ini untuk menutup HTTP client dan mengembalikan teks:

    ```cpp
    httpClient.end();

    return text;
    ```

1. Dalam `main.cpp`, panggil kaedah baru `convertSpeechToText` ini dalam fungsi `processAudio`, kemudian log keluar ucapan ke monitor serial:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. Bina kod ini, muat naik ke Wio Terminal anda dan uji melalui monitor serial. Setelah anda melihat `Ready` dalam monitor serial, tekan butang C (yang di sebelah kiri, paling dekat dengan suis kuasa), dan bercakap. 4 saat audio akan ditangkap, kemudian ditukar kepada teks.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Set a 2 minute and 27 second timer.","Offset":4700000,"Duration":35300000}
    Set a 2 minute and 27 second timer.
    ```

> 💁 Anda boleh mencari kod ini dalam folder [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal).

😀 Program ucapan ke teks anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat penting, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.