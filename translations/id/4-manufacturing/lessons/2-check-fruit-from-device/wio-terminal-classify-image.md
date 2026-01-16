<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "32a1f23e7834fbe7715da8c4ebb450b9",
  "translation_date": "2025-08-27T21:01:40+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-classify-image.md",
  "language_code": "id"
}
-->
# Klasifikasi Gambar - Wio Terminal

Dalam bagian pelajaran ini, Anda akan mengirimkan gambar yang diambil oleh kamera ke layanan Custom Vision untuk diklasifikasikan.

## Klasifikasi Gambar

Layanan Custom Vision memiliki REST API yang dapat Anda panggil dari Wio Terminal untuk mengklasifikasikan gambar. REST API ini diakses melalui koneksi HTTPS - koneksi HTTP yang aman.

Saat berinteraksi dengan endpoint HTTPS, kode klien perlu meminta sertifikat kunci publik dari server yang diakses, dan menggunakannya untuk mengenkripsi lalu lintas yang dikirim. Browser web Anda melakukan ini secara otomatis, tetapi mikrokontroler tidak. Anda perlu meminta sertifikat ini secara manual dan menggunakannya untuk membuat koneksi aman ke REST API. Sertifikat ini tidak berubah, jadi setelah Anda memiliki sertifikat, sertifikat tersebut dapat dikodekan langsung dalam aplikasi Anda.

Sertifikat ini berisi kunci publik dan tidak perlu disimpan dengan aman. Anda dapat menggunakannya dalam kode sumber Anda dan membagikannya secara publik di tempat seperti GitHub.

### Tugas - Mengatur Klien SSL

1. Buka proyek aplikasi `fruit-quality-detector` jika belum terbuka.

1. Buka file header `config.h`, dan tambahkan berikut ini:

    ```cpp
    const char *CERTIFICATE =
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

    Ini adalah *Microsoft Azure DigiCert Global Root G2 certificate* - salah satu sertifikat yang digunakan oleh banyak layanan Azure secara global.

    > 💁 Untuk melihat bahwa ini adalah sertifikat yang digunakan, jalankan perintah berikut di macOS atau Linux. Jika Anda menggunakan Windows, Anda dapat menjalankan perintah ini menggunakan [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn):
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > Output akan mencantumkan sertifikat DigiCert Global Root G2.

1. Buka `main.cpp` dan tambahkan directive include berikut:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. Di bawah directive include, deklarasikan instance `WifiClientSecure`:

    ```cpp
    WiFiClientSecure client;
    ```

    Kelas ini berisi kode untuk berkomunikasi dengan endpoint web melalui HTTPS.

1. Dalam metode `connectWiFi`, atur WiFiClientSecure untuk menggunakan sertifikat DigiCert Global Root G2:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### Tugas - Klasifikasi Gambar

1. Tambahkan baris berikut sebagai tambahan ke daftar `lib_deps` dalam file `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Ini mengimpor [ArduinoJson](https://arduinojson.org), pustaka JSON untuk Arduino, yang akan digunakan untuk mendekode respons JSON dari REST API.

1. Dalam `config.h`, tambahkan konstanta untuk URL prediksi dan Key dari layanan Custom Vision:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    Ganti `<PREDICTION_URL>` dengan URL prediksi dari Custom Vision. Ganti `<PREDICTION_KEY>` dengan kunci prediksi.

1. Dalam `main.cpp`, tambahkan directive include untuk pustaka ArduinoJson:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Tambahkan fungsi berikut ke `main.cpp`, di atas fungsi `buttonPressed`.

    ```cpp
    void classifyImage(byte *buffer, uint32_t length)
    {
        HTTPClient httpClient;
        httpClient.begin(client, PREDICTION_URL);
        httpClient.addHeader("Content-Type", "application/octet-stream");
        httpClient.addHeader("Prediction-Key", PREDICTION_KEY);
    
        int httpResponseCode = httpClient.POST(buffer, length);
    
        if (httpResponseCode == 200)
        {
            String result = httpClient.getString();
    
            DynamicJsonDocument doc(1024);
            deserializeJson(doc, result.c_str());
    
            JsonObject obj = doc.as<JsonObject>();
            JsonArray predictions = obj["predictions"].as<JsonArray>();
    
            for(JsonVariant prediction : predictions) 
            {
                String tag = prediction["tagName"].as<String>();
                float probability = prediction["probability"].as<float>();
    
                char buff[32];
                sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
                Serial.println(buff);
            }
        }
    
        httpClient.end();
    }
    ```

    Kode ini dimulai dengan mendeklarasikan `HTTPClient` - kelas yang berisi metode untuk berinteraksi dengan REST API. Kemudian menghubungkan klien ke URL prediksi menggunakan instance `WiFiClientSecure` yang telah diatur dengan kunci publik Azure.

    Setelah terhubung, kode mengirimkan header - informasi tentang permintaan yang akan dilakukan terhadap REST API. Header `Content-Type` menunjukkan bahwa panggilan API akan mengirimkan data biner mentah, sedangkan header `Prediction-Key` mengirimkan kunci prediksi Custom Vision.

    Selanjutnya, permintaan POST dibuat ke klien HTTP, mengunggah array byte. Array ini akan berisi gambar JPEG yang diambil dari kamera saat fungsi ini dipanggil.

    > 💁 Permintaan POST digunakan untuk mengirim data dan mendapatkan respons. Ada jenis permintaan lain seperti permintaan GET yang mengambil data. Permintaan GET digunakan oleh browser web Anda untuk memuat halaman web.

    Permintaan POST mengembalikan kode status respons. Nilai-nilai ini telah didefinisikan dengan baik, dengan 200 berarti **OK** - permintaan POST berhasil.

    > 💁 Anda dapat melihat semua kode status respons di [Halaman Daftar Kode Status HTTP di Wikipedia](https://wikipedia.org/wiki/List_of_HTTP_status_codes)

    Jika 200 dikembalikan, hasilnya dibaca dari klien HTTP. Ini adalah respons teks dari REST API dengan hasil prediksi dalam dokumen JSON. JSON memiliki format berikut:

    ```jSON
    {
        "id":"45d614d3-7d6f-47e9-8fa2-04f237366a16",
        "project":"135607e5-efac-4855-8afb-c93af3380531",
        "iteration":"04f1c1fa-11ec-4e59-bb23-4c7aca353665",
        "created":"2021-06-10T17:58:58.959Z",
        "predictions":[
            {
                "probability":0.5582016,
                "tagId":"05a432ea-9718-4098-b14f-5f0688149d64",
                "tagName":"ripe"
            },
            {
                "probability":0.44179836,
                "tagId":"bb091037-16e5-418e-a9ea-31c6a2920f17",
                "tagName":"unripe"
            }
        ]
    }
    ```

    Bagian penting di sini adalah array `predictions`. Array ini berisi prediksi, dengan satu entri untuk setiap tag yang berisi nama tag dan probabilitasnya. Probabilitas yang dikembalikan adalah angka floating point dari 0-1, dengan 0 berarti kemungkinan 0% cocok dengan tag, dan 1 berarti kemungkinan 100%.

    > 💁 Pengklasifikasi gambar akan mengembalikan persentase untuk semua tag yang telah digunakan. Setiap tag akan memiliki probabilitas bahwa gambar cocok dengan tag tersebut.

    JSON ini didekodekan, dan probabilitas untuk setiap tag dikirim ke monitor serial.

1. Dalam fungsi `buttonPressed`, ganti kode yang menyimpan ke kartu SD dengan pemanggilan ke `classifyImage`, atau tambahkan setelah gambar ditulis, tetapi **sebelum** buffer dihapus:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 Jika Anda mengganti kode yang menyimpan ke kartu SD, Anda dapat membersihkan kode Anda dengan menghapus fungsi `setupSDCard` dan `saveToSDCard`.

1. Unggah dan jalankan kode Anda. Arahkan kamera ke beberapa buah dan tekan tombol C. Anda akan melihat output di monitor serial:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    Anda akan dapat melihat gambar yang diambil, dan nilai-nilai ini di tab **Predictions** di Custom Vision.

    ![Sebuah pisang di Custom Vision diprediksi matang dengan probabilitas 56.8% dan belum matang dengan probabilitas 43.1%](../../../../../translated_images/id/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 Anda dapat menemukan kode ini di folder [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal).

😀 Program pengklasifikasi kualitas buah Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berupaya untuk memberikan hasil yang akurat, harap diperhatikan bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang berwenang. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa terjemahan manusia profesional. Kami tidak bertanggung jawab atas kesalahpahaman atau interpretasi yang keliru yang timbul dari penggunaan terjemahan ini.