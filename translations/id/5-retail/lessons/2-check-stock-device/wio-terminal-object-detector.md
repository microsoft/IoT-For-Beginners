<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4cf1421420a6fab9ab4f2c391bd523b7",
  "translation_date": "2025-08-27T20:46:09+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-object-detector.md",
  "language_code": "id"
}
-->
# Panggil detektor objek Anda dari perangkat IoT - Wio Terminal

Setelah detektor objek Anda dipublikasikan, Anda dapat menggunakannya dari perangkat IoT Anda.

## Salin proyek pengklasifikasi gambar

Sebagian besar detektor stok Anda sama dengan pengklasifikasi gambar yang Anda buat di pelajaran sebelumnya.

### Tugas - salin proyek pengklasifikasi gambar

1. Hubungkan ArduCam Anda ke Wio Terminal, mengikuti langkah-langkah dari [pelajaran 2 dari proyek manufaktur](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera).

    Anda mungkin juga ingin memperbaiki posisi kamera, misalnya, dengan menggantung kabel di atas kotak atau kaleng, atau menempelkan kamera ke kotak menggunakan selotip dua sisi.

1. Buat proyek Wio Terminal baru menggunakan PlatformIO. Beri nama proyek ini `stock-counter`.

1. Ikuti langkah-langkah dari [pelajaran 2 dari proyek manufaktur](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) untuk menangkap gambar dari kamera.

1. Ikuti langkah-langkah dari [pelajaran 2 dari proyek manufaktur](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) untuk memanggil pengklasifikasi gambar. Sebagian besar kode ini akan digunakan kembali untuk mendeteksi objek.

## Ubah kode dari pengklasifikasi menjadi detektor gambar

Kode yang Anda gunakan untuk mengklasifikasi gambar sangat mirip dengan kode untuk mendeteksi objek. Perbedaan utamanya adalah URL yang dipanggil yang Anda dapatkan dari Custom Vision, dan hasil dari panggilan tersebut.

### Tugas - ubah kode dari pengklasifikasi menjadi detektor gambar

1. Tambahkan directive include berikut ke bagian atas file `main.cpp`:

    ```cpp
    #include <vector>
    ```

1. Ubah nama fungsi `classifyImage` menjadi `detectStock`, baik nama fungsi maupun panggilan dalam fungsi `buttonPressed`.

1. Di atas fungsi `detectStock`, deklarasikan ambang batas untuk menyaring deteksi dengan probabilitas rendah:

    ```cpp
    const float threshold = 0.3f;
    ```

    Berbeda dengan pengklasifikasi gambar yang hanya mengembalikan satu hasil per tag, detektor objek akan mengembalikan beberapa hasil, sehingga deteksi dengan probabilitas rendah perlu disaring.

1. Di atas fungsi `detectStock`, deklarasikan fungsi untuk memproses prediksi:

    ```cpp
    void processPredictions(std::vector<JsonVariant> &predictions)
    {
        for(JsonVariant prediction : predictions)
        {
            String tag = prediction["tagName"].as<String>();
            float probability = prediction["probability"].as<float>();
    
            char buff[32];
            sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
            Serial.println(buff);
        }
    }
    ```

    Fungsi ini mengambil daftar prediksi dan mencetaknya ke monitor serial.

1. Dalam fungsi `detectStock`, ganti isi dari `for` loop yang melintasi prediksi dengan berikut ini:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for(JsonVariant prediction : predictions) 
    {
        float probability = prediction["probability"].as<float>();
        if (probability > threshold)
        {
            passed_predictions.push_back(prediction);
        }
    }

    processPredictions(passed_predictions);
    ```

    Loop ini melintasi prediksi, membandingkan probabilitas dengan ambang batas. Semua prediksi dengan probabilitas lebih tinggi dari ambang batas ditambahkan ke `list` dan diteruskan ke fungsi `processPredictions`.

1. Unggah dan jalankan kode Anda. Arahkan kamera ke objek di rak dan tekan tombol C. Anda akan melihat output di monitor serial:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%
    tomato paste:   35.87%
    tomato paste:   34.11%
    tomato paste:   35.16%
    ```

    > 💁 Anda mungkin perlu menyesuaikan `threshold` ke nilai yang sesuai untuk gambar Anda.

    Anda akan dapat melihat gambar yang diambil, dan nilai-nilai ini di tab **Predictions** di Custom Vision.

    ![4 kaleng pasta tomat di rak dengan prediksi untuk 4 deteksi sebesar 35.8%, 33.5%, 25.7%, dan 16.6%](../../../../../translated_images/id/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 Anda dapat menemukan kode ini di folder [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal).

😀 Program penghitung stok Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.