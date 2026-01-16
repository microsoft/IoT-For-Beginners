<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "32a1f23e7834fbe7715da8c4ebb450b9",
  "translation_date": "2025-08-27T21:02:00+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-classify-image.md",
  "language_code": "ms"
}
-->
# Klasifikasi imej - Wio Terminal

Dalam bahagian pelajaran ini, anda akan menghantar imej yang ditangkap oleh kamera ke perkhidmatan Custom Vision untuk mengklasifikasikannya.

## Klasifikasi imej

Perkhidmatan Custom Vision mempunyai REST API yang boleh dipanggil dari Wio Terminal untuk mengklasifikasikan imej. REST API ini diakses melalui sambungan HTTPS - sambungan HTTP yang selamat.

Apabila berinteraksi dengan titik akhir HTTPS, kod klien perlu meminta sijil kunci awam daripada pelayan yang diakses, dan menggunakannya untuk menyulitkan trafik yang dihantar. Pelayar web anda melakukan ini secara automatik, tetapi mikropengawal tidak. Anda perlu meminta sijil ini secara manual dan menggunakannya untuk mencipta sambungan selamat ke REST API. Sijil ini tidak berubah, jadi setelah anda mempunyai sijil, ia boleh dikodkan secara tetap dalam aplikasi anda.

Sijil ini mengandungi kunci awam dan tidak perlu disimpan dengan selamat. Anda boleh menggunakannya dalam kod sumber anda dan berkongsi secara terbuka di tempat seperti GitHub.

### Tugas - menyediakan klien SSL

1. Buka projek aplikasi `fruit-quality-detector` jika belum dibuka.

1. Buka fail header `config.h`, dan tambahkan perkara berikut:

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

    Ini adalah *Microsoft Azure DigiCert Global Root G2 certificate* - salah satu sijil yang digunakan oleh banyak perkhidmatan Azure di seluruh dunia.

    > 💁 Untuk melihat bahawa ini adalah sijil yang perlu digunakan, jalankan arahan berikut pada macOS atau Linux. Jika anda menggunakan Windows, anda boleh menjalankan arahan ini menggunakan [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn):
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > Output akan menyenaraikan sijil DigiCert Global Root G2.

1. Buka `main.cpp` dan tambahkan arahan include berikut:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. Di bawah arahan include, isytiharkan satu instance `WifiClientSecure`:

    ```cpp
    WiFiClientSecure client;
    ```

    Kelas ini mengandungi kod untuk berkomunikasi dengan titik akhir web melalui HTTPS.

1. Dalam kaedah `connectWiFi`, tetapkan WiFiClientSecure untuk menggunakan sijil DigiCert Global Root G2:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### Tugas - klasifikasikan imej

1. Tambahkan perkara berikut sebagai baris tambahan ke senarai `lib_deps` dalam fail `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Ini mengimport [ArduinoJson](https://arduinojson.org), perpustakaan JSON Arduino, dan akan digunakan untuk menyahkod respons JSON daripada REST API.

1. Dalam `config.h`, tambahkan pemalar untuk URL ramalan dan Kunci daripada perkhidmatan Custom Vision:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    Gantikan `<PREDICTION_URL>` dengan URL ramalan daripada Custom Vision. Gantikan `<PREDICTION_KEY>` dengan kunci ramalan.

1. Dalam `main.cpp`, tambahkan arahan include untuk perpustakaan ArduinoJson:

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

    Kod ini bermula dengan mengisytiharkan `HTTPClient` - kelas yang mengandungi kaedah untuk berinteraksi dengan REST API. Ia kemudian menyambungkan klien ke URL ramalan menggunakan instance `WiFiClientSecure` yang telah disediakan dengan kunci awam Azure.

    Setelah disambungkan, ia menghantar header - maklumat tentang permintaan yang akan datang terhadap REST API. Header `Content-Type` menunjukkan panggilan API akan menghantar data binari mentah, sementara header `Prediction-Key` menghantar kunci ramalan Custom Vision.

    Seterusnya, permintaan POST dibuat kepada klien HTTP, memuat naik array byte. Ini akan mengandungi imej JPEG yang ditangkap dari kamera apabila fungsi ini dipanggil.

    > 💁 Permintaan POST bertujuan untuk menghantar data dan mendapatkan respons. Terdapat jenis permintaan lain seperti permintaan GET yang mengambil data. Permintaan GET digunakan oleh pelayar web anda untuk memuatkan halaman web.

    Permintaan POST mengembalikan kod status respons. Ini adalah nilai yang ditentukan dengan baik, dengan 200 bermaksud **OK** - permintaan POST berjaya.

    > 💁 Anda boleh melihat semua kod status respons dalam [Senarai kod status HTTP di Wikipedia](https://wikipedia.org/wiki/List_of_HTTP_status_codes)

    Jika 200 dikembalikan, hasilnya dibaca dari klien HTTP. Ini adalah respons teks daripada REST API dengan hasil ramalan sebagai dokumen JSON. JSON adalah dalam format berikut:

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

    Bahagian penting di sini adalah array `predictions`. Ini mengandungi ramalan, dengan satu entri untuk setiap tag yang mengandungi nama tag dan kebarangkalian. Kebarangkalian yang dikembalikan adalah nombor titik terapung dari 0-1, dengan 0 bermaksud 0% peluang untuk sepadan dengan tag, dan 1 bermaksud 100% peluang.

    > 💁 Pengklasifikasi imej akan mengembalikan peratusan untuk semua tag yang telah digunakan. Setiap tag akan mempunyai kebarangkalian bahawa imej sepadan dengan tag tersebut.

    JSON ini disahkod, dan kebarangkalian untuk setiap tag dihantar ke monitor serial.

1. Dalam fungsi `buttonPressed`, gantikan kod yang menyimpan ke kad SD dengan panggilan ke `classifyImage`, atau tambahkan selepas imej ditulis, tetapi **sebelum** buffer dipadamkan:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 Jika anda menggantikan kod yang menyimpan ke kad SD, anda boleh membersihkan kod anda dengan membuang fungsi `setupSDCard` dan `saveToSDCard`.

1. Muat naik dan jalankan kod anda. Arahkan kamera ke beberapa buah-buahan dan tekan butang C. Anda akan melihat output di monitor serial:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    Anda akan dapat melihat imej yang diambil, dan nilai-nilai ini dalam tab **Predictions** di Custom Vision.

    ![Sebuah pisang dalam Custom Vision diramalkan matang pada 56.8% dan tidak matang pada 43.1%](../../../../../translated_images/ms/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 Anda boleh mencari kod ini dalam folder [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal).

😀 Program pengklasifikasi kualiti buah anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.