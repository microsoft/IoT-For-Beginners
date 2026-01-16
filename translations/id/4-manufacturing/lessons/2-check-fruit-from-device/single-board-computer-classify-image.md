<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e5896207b304ce1abaf065b8acc0cc79",
  "translation_date": "2025-08-27T21:00:35+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/single-board-computer-classify-image.md",
  "language_code": "id"
}
-->
# Klasifikasi Gambar - Perangkat IoT Virtual dan Raspberry Pi

Dalam bagian pelajaran ini, Anda akan mengirimkan gambar yang diambil oleh kamera ke layanan Custom Vision untuk diklasifikasikan.

## Mengirim Gambar ke Custom Vision

Layanan Custom Vision memiliki SDK Python yang dapat Anda gunakan untuk mengklasifikasikan gambar.

### Tugas - Mengirim Gambar ke Custom Vision

1. Buka folder `fruit-quality-detector` di VS Code. Jika Anda menggunakan perangkat IoT virtual, pastikan lingkungan virtual berjalan di terminal.

1. SDK Python untuk mengirim gambar ke Custom Vision tersedia sebagai paket Pip. Instal dengan perintah berikut:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. Tambahkan pernyataan impor berikut di bagian atas file `app.py`:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    Ini membawa beberapa modul dari pustaka Custom Vision, satu untuk autentikasi dengan kunci prediksi, dan satu untuk menyediakan kelas klien prediksi yang dapat memanggil Custom Vision.

1. Tambahkan kode berikut di akhir file:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    Ganti `<prediction_url>` dengan URL yang Anda salin dari dialog *Prediction URL* sebelumnya dalam pelajaran ini. Ganti `<prediction key>` dengan kunci prediksi yang Anda salin dari dialog yang sama.

1. URL prediksi yang disediakan oleh dialog *Prediction URL* dirancang untuk digunakan saat memanggil endpoint REST secara langsung. SDK Python menggunakan bagian-bagian dari URL di tempat yang berbeda. Tambahkan kode berikut untuk memecah URL ini menjadi bagian-bagian yang diperlukan:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    Ini memecah URL, mengekstrak endpoint `https://<location>.api.cognitive.microsoft.com`, ID proyek, dan nama iterasi yang dipublikasikan.

1. Buat objek prediktor untuk melakukan prediksi dengan kode berikut:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    `prediction_credentials` membungkus kunci prediksi. Ini kemudian digunakan untuk membuat objek klien prediksi yang menunjuk ke endpoint.

1. Kirim gambar ke Custom Vision menggunakan kode berikut:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    Ini mengembalikan posisi gambar ke awal, lalu mengirimkannya ke klien prediksi.

1. Terakhir, tampilkan hasilnya dengan kode berikut:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Ini akan melakukan iterasi melalui semua prediksi yang telah dikembalikan dan menampilkannya di terminal. Probabilitas yang dikembalikan adalah angka floating point dari 0-1, dengan 0 berarti 0% kemungkinan cocok dengan tag, dan 1 berarti 100% kemungkinan.

    > 💁 Pengklasifikasi gambar akan mengembalikan persentase untuk semua tag yang telah digunakan. Setiap tag akan memiliki probabilitas bahwa gambar cocok dengan tag tersebut.

1. Jalankan kode Anda, dengan kamera Anda mengarah ke beberapa buah, atau set gambar yang sesuai, atau buah yang terlihat di webcam Anda jika menggunakan perangkat IoT virtual. Anda akan melihat output di konsol:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    Anda akan dapat melihat gambar yang diambil, dan nilai-nilai ini di tab **Predictions** di Custom Vision.

    ![Sebuah pisang di Custom Vision diprediksi matang dengan probabilitas 56.8% dan belum matang dengan probabilitas 43.1%](../../../../../translated_images/id/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 Anda dapat menemukan kode ini di folder [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) atau [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device).

😀 Program pengklasifikasi kualitas buah Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.