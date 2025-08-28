<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-27T22:56:02+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "id"
}
-->
# Klasifikasikan gambar menggunakan pengklasifikasi gambar berbasis IoT Edge - Perangkat Keras Virtual IoT dan Raspberry Pi

Dalam bagian pelajaran ini, Anda akan menggunakan Pengklasifikasi Gambar yang berjalan di perangkat IoT Edge.

## Gunakan pengklasifikasi IoT Edge

Perangkat IoT dapat diarahkan untuk menggunakan pengklasifikasi gambar IoT Edge. URL untuk Pengklasifikasi Gambar adalah `http://<IP address or name>/image`, mengganti `<IP address or name>` dengan alamat IP atau nama host dari komputer yang menjalankan IoT Edge.

Pustaka Python untuk Custom Vision hanya berfungsi dengan model yang di-host di cloud, bukan model yang di-host di IoT Edge. Ini berarti Anda perlu menggunakan REST API untuk memanggil pengklasifikasi.

### Tugas - gunakan pengklasifikasi IoT Edge

1. Buka proyek `fruit-quality-detector` di VS Code jika belum terbuka. Jika Anda menggunakan perangkat IoT virtual, pastikan lingkungan virtual telah diaktifkan.

1. Buka file `app.py`, dan hapus pernyataan impor dari `azure.cognitiveservices.vision.customvision.prediction` dan `msrest.authentication`.

1. Tambahkan impor berikut di bagian atas file:

    ```python
    import requests
    ```

1. Hapus semua kode setelah gambar disimpan ke file, mulai dari `image_file.write(image.read())` hingga akhir file.

1. Tambahkan kode berikut di akhir file:

    ```python
    prediction_url = '<URL>'
    headers = {
        'Content-Type' : 'application/octet-stream'
    }
    image.seek(0)
    response = requests.post(prediction_url, headers=headers, data=image)
    results = response.json()
    
    for prediction in results['predictions']:
        print(f'{prediction["tagName"]}:\t{prediction["probability"] * 100:.2f}%')
    ```

    Ganti `<URL>` dengan URL untuk pengklasifikasi Anda.

    Kode ini membuat permintaan REST POST ke pengklasifikasi, mengirimkan gambar sebagai isi permintaan. Hasilnya akan kembali dalam format JSON, dan ini didekodekan untuk mencetak probabilitas.

1. Jalankan kode Anda, dengan kamera Anda mengarah ke beberapa buah, atau set gambar yang sesuai, atau buah yang terlihat di webcam Anda jika menggunakan perangkat keras IoT virtual. Anda akan melihat output di konsol:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Anda dapat menemukan kode ini di folder [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) atau [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device).

😀 Program pengklasifikasi kualitas buah Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diperhatikan bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.