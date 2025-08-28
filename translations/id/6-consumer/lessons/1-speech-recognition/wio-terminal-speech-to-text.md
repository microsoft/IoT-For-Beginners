<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-27T23:27:27+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "id"
}
-->
# Ucapan ke Teks - Wio Terminal

Dalam bagian pelajaran ini, Anda akan menulis kode untuk mengubah ucapan dalam audio yang ditangkap menjadi teks menggunakan layanan ucapan.

## Kirim audio ke layanan ucapan

Audio dapat dikirim ke layanan ucapan menggunakan REST API. Untuk menggunakan layanan ucapan, pertama-tama Anda perlu meminta token akses, lalu gunakan token tersebut untuk mengakses REST API. Token akses ini akan kedaluwarsa setelah 10 menit, jadi kode Anda harus memintanya secara berkala untuk memastikan token selalu diperbarui.

### Tugas - mendapatkan token akses

1. Buka proyek `smart-timer` jika belum terbuka.

1. Tambahkan dependensi pustaka berikut ke file `platformio.ini` untuk mengakses WiFi dan menangani JSON:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. Tambahkan kode berikut ke file header `config.h`:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    Ganti `<SSID>` dan `<PASSWORD>` dengan nilai yang relevan untuk WiFi Anda.

    Ganti `<API_KEY>` dengan kunci API untuk sumber daya layanan ucapan Anda. Ganti `<LOCATION>` dengan lokasi yang Anda gunakan saat membuat sumber daya layanan ucapan.

    Ganti `<LANGUAGE>` dengan nama lokal untuk bahasa yang akan Anda gunakan, misalnya `en-GB` untuk Bahasa Inggris, atau `zn-HK` untuk Bahasa Kanton. Anda dapat menemukan daftar bahasa yang didukung dan nama lokalnya di [dokumentasi dukungan bahasa dan suara di Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Konstanta `TOKEN_URL` adalah URL penerbit token tanpa lokasi. URL ini akan digabungkan dengan lokasi nanti untuk mendapatkan URL lengkap.

1. Sama seperti saat menghubungkan ke Custom Vision, Anda perlu menggunakan koneksi HTTPS untuk terhubung ke layanan penerbit token. Tambahkan kode berikut ke akhir `config.h`:

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

    Ini adalah sertifikat yang sama yang Anda gunakan saat menghubungkan ke Custom Vision.

1. Tambahkan include untuk file header WiFi dan file header config ke bagian atas file `main.cpp`:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. Tambahkan kode untuk menghubungkan ke WiFi di `main.cpp` di atas fungsi `setup`:

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

1. Panggil fungsi ini dari fungsi `setup` setelah koneksi serial telah dibuat:

    ```cpp
    connectWiFi();
    ```

1. Buat file header baru di folder `src` bernama `speech_to_text.h`. Dalam file header ini, tambahkan kode berikut:

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

    Ini mencakup beberapa file header yang diperlukan untuk koneksi HTTP, konfigurasi, dan file header `mic.h`, serta mendefinisikan kelas bernama `SpeechToText`, sebelum mendeklarasikan instance dari kelas tersebut yang dapat digunakan nanti.

1. Tambahkan 2 field berikut ke bagian `private` dari kelas ini:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    `_token_client` adalah WiFi Client yang menggunakan HTTPS dan akan digunakan untuk mendapatkan token akses. Token ini kemudian akan disimpan di `_access_token`.

1. Tambahkan metode berikut ke bagian `private`:

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

    Kode ini membangun URL untuk API penerbit token menggunakan lokasi sumber daya ucapan. Kemudian membuat `HTTPClient` untuk melakukan permintaan web, mengaturnya untuk menggunakan klien WiFi yang dikonfigurasi dengan sertifikat endpoint token. Kode ini menetapkan kunci API sebagai header untuk panggilan. Kemudian melakukan permintaan POST untuk mendapatkan sertifikat, mencoba ulang jika terjadi kesalahan. Akhirnya token akses dikembalikan.

1. Ke bagian `public`, tambahkan metode untuk mendapatkan token akses. Metode ini akan diperlukan dalam pelajaran berikutnya untuk mengubah teks menjadi ucapan.

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. Ke bagian `public`, tambahkan metode `init` yang mengatur klien token:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    Metode ini menetapkan sertifikat pada klien WiFi, lalu mendapatkan token akses.

1. Di `main.cpp`, tambahkan file header baru ini ke direktif include:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Inisialisasi kelas `SpeechToText` di akhir fungsi `setup`, setelah panggilan `mic.init` tetapi sebelum `Ready` ditulis ke monitor serial:

    ```cpp
    speechToText.init();
    ```

### Tugas - membaca audio dari memori flash

1. Pada bagian sebelumnya dari pelajaran ini, audio direkam ke memori flash. Audio ini perlu dikirim ke REST API Layanan Ucapan, sehingga perlu dibaca dari memori flash. Audio tidak dapat dimuat ke buffer dalam memori karena ukurannya terlalu besar. Kelas `HTTPClient` yang membuat panggilan REST dapat melakukan streaming data menggunakan Arduino Stream - sebuah kelas yang dapat memuat data dalam potongan kecil, mengirimkan potongan satu per satu sebagai bagian dari permintaan. Setiap kali Anda memanggil `read` pada stream, stream akan mengembalikan blok data berikutnya. Stream Arduino dapat dibuat untuk membaca dari memori flash. Buat file baru bernama `flash_stream.h` di folder `src`, dan tambahkan kode berikut ke dalamnya:

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

    Ini mendeklarasikan kelas `FlashStream`, yang diturunkan dari kelas `Stream` Arduino. Ini adalah kelas abstrak - kelas turunan harus mengimplementasikan beberapa metode sebelum kelas dapat diinstansiasi, dan metode-metode ini didefinisikan dalam kelas ini.

    ✅ Baca lebih lanjut tentang Arduino Streams di [dokumentasi Stream Arduino](https://www.arduino.cc/reference/en/language/functions/communication/stream/)

1. Tambahkan field berikut ke bagian `private`:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    Ini mendefinisikan buffer sementara untuk menyimpan data yang dibaca dari memori flash, bersama dengan field untuk menyimpan posisi saat ini saat membaca dari buffer, alamat saat ini untuk membaca dari memori flash, dan perangkat memori flash.

1. Di bagian `private`, tambahkan metode berikut:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    Kode ini membaca dari memori flash di alamat saat ini dan menyimpan data dalam buffer. Kemudian meningkatkan alamat, sehingga panggilan berikutnya membaca blok memori berikutnya. Buffer berukuran berdasarkan potongan terbesar yang akan dikirim oleh `HTTPClient` ke REST API dalam satu waktu.

    > 💁 Menghapus memori flash harus dilakukan menggunakan ukuran butir, sedangkan membaca tidak.

1. Di bagian `public` dari kelas ini, tambahkan konstruktor:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    Konstruktor ini mengatur semua field untuk mulai membaca dari awal blok memori flash, dan memuat potongan data pertama ke dalam buffer.

1. Implementasikan metode `write`. Stream ini hanya akan membaca data, jadi metode ini tidak melakukan apa-apa dan mengembalikan 0:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. Implementasikan metode `peek`. Metode ini mengembalikan data di posisi saat ini tanpa menggerakkan stream. Memanggil `peek` beberapa kali akan selalu mengembalikan data yang sama selama tidak ada data yang dibaca dari stream.

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. Implementasikan fungsi `available`. Fungsi ini mengembalikan berapa banyak byte yang dapat dibaca dari stream, atau -1 jika stream selesai. Untuk kelas ini, maksimum yang tersedia tidak akan lebih dari ukuran potongan HTTPClient. Saat stream ini digunakan dalam HTTP client, HTTP client memanggil fungsi ini untuk melihat berapa banyak data yang tersedia, lalu meminta data sebanyak itu untuk dikirim ke REST API. Kita tidak ingin setiap potongan lebih besar dari ukuran potongan HTTP client, jadi jika lebih dari itu tersedia, ukuran potongan dikembalikan. Jika kurang, maka yang tersedia dikembalikan. Setelah semua data telah di-streaming, -1 dikembalikan.

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

1. Implementasikan metode `read` untuk mengembalikan byte berikutnya dari buffer, meningkatkan posisi. Jika posisi melebihi ukuran buffer, buffer diisi dengan blok berikutnya dari memori flash dan posisi diatur ulang.

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

1. Di file header `speech_to_text.h`, tambahkan direktif include untuk file header baru ini:

    ```cpp
    #include "flash_stream.h"
    ```

### Tugas - mengubah ucapan menjadi teks

1. Ucapan dapat diubah menjadi teks dengan mengirimkan audio ke Layanan Ucapan melalui REST API. REST API ini memiliki sertifikat yang berbeda dari penerbit token, jadi tambahkan kode berikut ke file header `config.h` untuk mendefinisikan sertifikat ini:

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

1. Tambahkan konstanta ke file ini untuk URL ucapan tanpa lokasi. URL ini akan digabungkan dengan lokasi dan bahasa nanti untuk mendapatkan URL lengkap.

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. Di file header `speech_to_text.h`, di bagian `private` dari kelas `SpeechToText`, definisikan field untuk WiFi Client menggunakan sertifikat ucapan:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. Di metode `init`, tetapkan sertifikat pada WiFi Client ini:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. Tambahkan kode berikut ke bagian `public` dari kelas `SpeechToText` untuk mendefinisikan metode untuk mengubah ucapan menjadi teks:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. Tambahkan kode berikut ke metode ini untuk membuat HTTP client menggunakan WiFi client yang dikonfigurasi dengan sertifikat ucapan, dan menggunakan URL ucapan yang diatur dengan lokasi dan bahasa:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. Beberapa header perlu diatur pada koneksi:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    Header ini menetapkan otorisasi menggunakan token akses, format audio menggunakan sample rate, dan menetapkan bahwa klien mengharapkan hasil sebagai JSON.

1. Setelah ini, tambahkan kode berikut untuk melakukan panggilan REST API:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    Ini membuat `FlashStream` dan menggunakannya untuk melakukan streaming data ke REST API.

1. Di bawah ini, tambahkan kode berikut:

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

    Kode ini memeriksa kode respons.

    Jika kode respons adalah 200, kode untuk keberhasilan, maka hasilnya diambil, didekode dari JSON, dan properti `DisplayText` diatur ke variabel `text`. Properti ini adalah tempat teks versi ucapan dikembalikan.

    Jika kode respons adalah 401, maka token akses telah kedaluwarsa (token ini hanya bertahan 10 menit). Token akses baru diminta, dan panggilan dilakukan lagi.

    Jika tidak, kesalahan dikirim ke monitor serial, dan `text` dibiarkan kosong.

1. Tambahkan kode berikut ke akhir metode ini untuk menutup HTTP client dan mengembalikan teks:

    ```cpp
    httpClient.end();

    return text;
    ```

1. Di `main.cpp`, panggil metode baru `convertSpeechToText` ini di fungsi `processAudio`, lalu log ucapan ke monitor serial:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. Bangun kode ini, unggah ke Wio Terminal Anda, dan uji melalui monitor serial. Setelah Anda melihat `Ready` di monitor serial, tekan tombol C (yang ada di sisi kiri, paling dekat dengan sakelar daya), dan berbicaralah. Audio selama 4 detik akan ditangkap, lalu diubah menjadi teks.

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

> 💁 Anda dapat menemukan kode ini di folder [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal).

😀 Program ucapan ke teks Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.