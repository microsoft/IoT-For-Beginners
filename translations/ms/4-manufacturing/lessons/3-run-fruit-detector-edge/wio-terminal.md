<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-27T22:56:49+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "ms"
}
-->
# Klasifikasikan imej menggunakan pengelas imej berasaskan IoT Edge - Wio Terminal

Dalam bahagian pelajaran ini, anda akan menggunakan Pengelas Imej yang berjalan pada peranti IoT Edge.

## Gunakan pengelas IoT Edge

Peranti IoT boleh diarahkan semula untuk menggunakan pengelas imej IoT Edge. URL untuk Pengelas Imej ialah `http://<IP address or name>/image`, menggantikan `<IP address or name>` dengan alamat IP atau nama hos komputer yang menjalankan IoT Edge.

### Tugas - gunakan pengelas IoT Edge

1. Buka projek aplikasi `fruit-quality-detector` jika ia belum dibuka.

1. Pengelas imej berjalan sebagai REST API menggunakan HTTP, bukan HTTPS, jadi panggilan perlu menggunakan klien WiFi yang hanya berfungsi dengan panggilan HTTP. Ini bermakna sijil tidak diperlukan. Padamkan `CERTIFICATE` daripada fail `config.h`.

1. URL ramalan dalam fail `config.h` perlu dikemas kini kepada URL baharu. Anda juga boleh memadamkan `PREDICTION_KEY` kerana ia tidak diperlukan.

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    Gantikan `<URL>` dengan URL untuk pengelas anda.

1. Dalam `main.cpp`, ubah arahan include untuk WiFi Client Secure kepada versi HTTP standard:

    ```cpp
    #include <WiFiClient.h>
    ```

1. Ubah deklarasi `WiFiClient` kepada versi HTTP:

    ```cpp
    WiFiClient client;
    ```

1. Pilih baris yang menetapkan sijil pada klien WiFi. Padamkan baris `client.setCACert(CERTIFICATE);` daripada fungsi `connectWiFi`.

1. Dalam fungsi `classifyImage`, padamkan baris `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);` yang menetapkan kunci ramalan dalam header.

1. Muat naik dan jalankan kod anda. Arahkan kamera ke beberapa buah-buahan dan tekan butang C. Anda akan melihat output dalam monitor bersiri:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Anda boleh menemui kod ini dalam folder [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal).

😀 Program pengelas kualiti buah anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.