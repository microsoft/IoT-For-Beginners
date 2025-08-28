<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-27T21:13:47+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "id"
}
-->
# Klasifikasikan gambar menggunakan pengklasifikasi gambar berbasis IoT Edge - Wio Terminal

Dalam bagian pelajaran ini, Anda akan menggunakan Pengklasifikasi Gambar yang berjalan di perangkat IoT Edge.

## Gunakan pengklasifikasi IoT Edge

Perangkat IoT dapat diarahkan untuk menggunakan pengklasifikasi gambar IoT Edge. URL untuk Pengklasifikasi Gambar adalah `http://<IP address or name>/image`, menggantikan `<IP address or name>` dengan alamat IP atau nama host dari komputer yang menjalankan IoT Edge.

### Tugas - gunakan pengklasifikasi IoT Edge

1. Buka proyek aplikasi `fruit-quality-detector` jika belum terbuka.

1. Pengklasifikasi gambar berjalan sebagai REST API menggunakan HTTP, bukan HTTPS, sehingga panggilan perlu menggunakan klien WiFi yang hanya mendukung panggilan HTTP. Ini berarti sertifikat tidak diperlukan. Hapus `CERTIFICATE` dari file `config.h`.

1. URL prediksi di file `config.h` perlu diperbarui ke URL yang baru. Anda juga dapat menghapus `PREDICTION_KEY` karena ini tidak diperlukan.

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    Gantikan `<URL>` dengan URL untuk pengklasifikasi Anda.

1. Di `main.cpp`, ubah direktif include untuk WiFi Client Secure agar mengimpor versi HTTP standar:

    ```cpp
    #include <WiFiClient.h>
    ```

1. Ubah deklarasi `WiFiClient` menjadi versi HTTP:

    ```cpp
    WiFiClient client;
    ```

1. Pilih baris yang menetapkan sertifikat pada klien WiFi. Hapus baris `client.setCACert(CERTIFICATE);` dari fungsi `connectWiFi`.

1. Di fungsi `classifyImage`, hapus baris `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);` yang menetapkan kunci prediksi di header.

1. Unggah dan jalankan kode Anda. Arahkan kamera ke beberapa buah dan tekan tombol C. Anda akan melihat output di monitor serial:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Anda dapat menemukan kode ini di folder [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal).

😀 Program pengklasifikasi kualitas buah Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.