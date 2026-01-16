<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a3fdfec1d1e2cb645ea11c2930b51299",
  "translation_date": "2025-08-27T20:39:36+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-object-detector.md",
  "language_code": "id"
}
-->
# Panggil detektor objek Anda dari perangkat IoT - Perangkat Keras IoT Virtual dan Raspberry Pi

Setelah detektor objek Anda dipublikasikan, Anda dapat menggunakannya dari perangkat IoT Anda.

## Salin proyek pengklasifikasi gambar

Sebagian besar detektor stok Anda sama dengan pengklasifikasi gambar yang Anda buat di pelajaran sebelumnya.

### Tugas - salin proyek pengklasifikasi gambar

1. Buat folder bernama `stock-counter` di komputer Anda jika Anda menggunakan perangkat IoT virtual, atau di Raspberry Pi Anda. Jika Anda menggunakan perangkat IoT virtual, pastikan Anda mengatur lingkungan virtual.

1. Siapkan perangkat keras kamera.

    * Jika Anda menggunakan Raspberry Pi, Anda perlu memasang PiCamera. Anda mungkin juga ingin memposisikan kamera di tempat tetap, misalnya, dengan menggantung kabel di atas kotak atau kaleng, atau menempelkan kamera ke kotak dengan selotip dua sisi.
    * Jika Anda menggunakan perangkat IoT virtual, Anda perlu menginstal CounterFit dan CounterFit PyCamera shim. Jika Anda akan menggunakan gambar diam, ambil beberapa gambar yang belum pernah dilihat oleh detektor objek Anda. Jika Anda akan menggunakan webcam, pastikan posisinya memungkinkan untuk melihat stok yang Anda deteksi.

1. Ikuti langkah-langkah dari [pelajaran 2 dari proyek manufaktur](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) untuk menangkap gambar dari kamera.

1. Ikuti langkah-langkah dari [pelajaran 2 dari proyek manufaktur](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) untuk memanggil pengklasifikasi gambar. Sebagian besar kode ini akan digunakan kembali untuk mendeteksi objek.

## Ubah kode dari pengklasifikasi menjadi detektor gambar

Kode yang Anda gunakan untuk mengklasifikasi gambar sangat mirip dengan kode untuk mendeteksi objek. Perbedaan utamanya adalah metode yang dipanggil pada Custom Vision SDK, dan hasil dari panggilan tersebut.

### Tugas - ubah kode dari pengklasifikasi menjadi detektor gambar

1. Hapus tiga baris kode yang mengklasifikasi gambar dan memproses prediksi:

    ```python
    results = predictor.classify_image(project_id, iteration_name, image)
    
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Hapus tiga baris ini.

1. Tambahkan kode berikut untuk mendeteksi objek dalam gambar:

    ```python
    results = predictor.detect_image(project_id, iteration_name, image)

    threshold = 0.3
    
    predictions = list(prediction for prediction in results.predictions if prediction.probability > threshold)
    
    for prediction in predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Kode ini memanggil metode `detect_image` pada predictor untuk menjalankan detektor objek. Kemudian, kode ini mengumpulkan semua prediksi dengan probabilitas di atas ambang batas, dan mencetaknya ke konsol.

    Berbeda dengan pengklasifikasi gambar yang hanya mengembalikan satu hasil per tag, detektor objek akan mengembalikan beberapa hasil, sehingga prediksi dengan probabilitas rendah perlu disaring.

1. Jalankan kode ini, dan kode tersebut akan menangkap gambar, mengirimkannya ke detektor objek, dan mencetak objek yang terdeteksi. Jika Anda menggunakan perangkat IoT virtual, pastikan Anda memiliki gambar yang sesuai di CounterFit, atau webcam Anda telah dipilih. Jika Anda menggunakan Raspberry Pi, pastikan kamera Anda mengarah ke objek di rak.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   34.13%
    tomato paste:   33.95%
    tomato paste:   35.05%
    tomato paste:   32.80%
    ```

    > 💁 Anda mungkin perlu menyesuaikan `threshold` ke nilai yang sesuai untuk gambar Anda.

    Anda akan dapat melihat gambar yang diambil, dan nilai-nilai ini di tab **Predictions** di Custom Vision.

    ![4 kaleng pasta tomat di rak dengan prediksi untuk 4 deteksi masing-masing 35.8%, 33.5%, 25.7%, dan 16.6%](../../../../../translated_images/id/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 Anda dapat menemukan kode ini di folder [code-detect/pi](../../../../../5-retail/lessons/2-check-stock-device/code-detect/pi) atau [code-detect/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-detect/virtual-iot-device).

😀 Program penghitung stok Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diketahui bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.