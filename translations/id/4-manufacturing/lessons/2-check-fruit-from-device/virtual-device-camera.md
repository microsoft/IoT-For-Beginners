<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ba7150ffc4a6999f6c3cfb4906ec7df",
  "translation_date": "2025-08-27T21:03:09+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/virtual-device-camera.md",
  "language_code": "id"
}
-->
# Tangkap Gambar - Perangkat IoT Virtual

Dalam bagian pelajaran ini, Anda akan menambahkan sensor kamera ke perangkat IoT virtual Anda, dan membaca gambar darinya.

## Perangkat Keras

Perangkat IoT virtual akan menggunakan kamera simulasi yang mengirimkan gambar dari file atau webcam Anda.

### Tambahkan Kamera ke CounterFit

Untuk menggunakan kamera virtual, Anda perlu menambahkannya ke aplikasi CounterFit.

#### Tugas - Tambahkan Kamera ke CounterFit

Tambahkan kamera ke aplikasi CounterFit.

1. Buat aplikasi Python baru di komputer Anda dalam folder bernama `fruit-quality-detector` dengan satu file bernama `app.py` dan lingkungan virtual Python, lalu tambahkan paket pip CounterFit.

    > ⚠️ Anda dapat merujuk ke [instruksi untuk membuat dan mengatur proyek Python CounterFit di pelajaran 1 jika diperlukan](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Instal paket Pip tambahan untuk menginstal shim CounterFit yang dapat berkomunikasi dengan sensor Kamera dengan mensimulasikan beberapa [Paket Pip Picamera](https://pypi.org/project/picamera/). Pastikan Anda menginstalnya dari terminal dengan lingkungan virtual yang diaktifkan.

    ```sh
    pip install counterfit-shims-picamera
    ```

1. Pastikan aplikasi web CounterFit sedang berjalan.

1. Buat kamera:

    1. Di kotak *Create sensor* pada panel *Sensors*, klik dropdown pada kotak *Sensor type* dan pilih *Camera*.

    1. Atur *Name* menjadi `Picamera`.

    1. Pilih tombol **Add** untuk membuat kamera.

    ![Pengaturan kamera](../../../../../translated_images/id/counterfit-create-camera.a5de97f59c0bd3cbe0416d7e89a3cfe86d19fbae05c641c53a91286412af0a34.png)

    Kamera akan dibuat dan muncul di daftar sensor.

    ![Kamera yang telah dibuat](../../../../../translated_images/id/counterfit-camera.001ec52194c8ee5d3f617173da2c79e1df903d10882adc625cbfc493525125d4.png)

## Program Kamera

Perangkat IoT virtual sekarang dapat diprogram untuk menggunakan kamera virtual.

### Tugas - Program Kamera

Program perangkat.

1. Pastikan aplikasi `fruit-quality-detector` terbuka di VS Code.

1. Buka file `app.py`.

1. Tambahkan kode berikut ke bagian atas `app.py` untuk menghubungkan aplikasi ke CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Tambahkan kode berikut ke file `app.py` Anda:

    ```python
    import io
    from counterfit_shims_picamera import PiCamera
    ```

    Kode ini mengimpor beberapa pustaka yang diperlukan, termasuk kelas `PiCamera` dari pustaka counterfit_shims_picamera.

1. Tambahkan kode berikut di bawah ini untuk menginisialisasi kamera:

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    ```

    Kode ini membuat objek PiCamera, mengatur resolusi menjadi 640x480. Meskipun resolusi yang lebih tinggi didukung, pengklasifikasi gambar bekerja pada gambar yang jauh lebih kecil (227x227) sehingga tidak perlu menangkap dan mengirim gambar yang lebih besar.

    Baris `camera.rotation = 0` mengatur rotasi gambar dalam derajat. Jika Anda perlu memutar gambar dari webcam atau file, atur sesuai kebutuhan. Misalnya, jika Anda ingin mengubah gambar pisang di webcam dalam mode lanskap menjadi potret, atur `camera.rotation = 90`.

1. Tambahkan kode berikut di bawah ini untuk menangkap gambar sebagai data biner:

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    Kode ini membuat objek `BytesIO` untuk menyimpan data biner. Gambar dibaca dari kamera sebagai file JPEG dan disimpan dalam objek ini. Objek ini memiliki indikator posisi untuk mengetahui di mana posisinya dalam data sehingga lebih banyak data dapat ditulis di akhir jika diperlukan, sehingga baris `image.seek(0)` memindahkan posisi ini kembali ke awal agar semua data dapat dibaca nanti.

1. Di bawah ini, tambahkan kode berikut untuk menyimpan gambar ke file:

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    Kode ini membuka file bernama `image.jpg` untuk ditulis, lalu membaca semua data dari objek `BytesIO` dan menulisnya ke file.

    > 💁 Anda dapat menangkap gambar langsung ke file daripada objek `BytesIO` dengan memberikan nama file ke panggilan `camera.capture`. Alasan menggunakan objek `BytesIO` adalah agar nanti dalam pelajaran ini Anda dapat mengirim gambar ke pengklasifikasi gambar Anda.

1. Konfigurasikan gambar yang akan ditangkap oleh kamera di CounterFit. Anda dapat mengatur *Source* ke *File*, lalu mengunggah file gambar, atau mengatur *Source* ke *WebCam*, dan gambar akan ditangkap dari webcam Anda. Pastikan Anda memilih tombol **Set** setelah memilih gambar atau memilih webcam Anda.

    ![CounterFit dengan file yang diatur sebagai sumber gambar, dan webcam yang menunjukkan seseorang memegang pisang dalam pratinjau webcam](../../../../../translated_images/id/counterfit-camera-options.eb3bd5150a8e7dffbf24bc5bcaba0cf2cdef95fbe6bbe393695d173817d6b8df.png)

1. Gambar akan ditangkap dan disimpan sebagai `image.jpg` di folder saat ini. Anda akan melihat file ini di penjelajah VS Code. Pilih file untuk melihat gambar. Jika perlu rotasi, perbarui baris `camera.rotation = 0` sesuai kebutuhan dan ambil gambar lagi.

> 💁 Anda dapat menemukan kode ini di folder [code-camera/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/virtual-iot-device).

😀 Program kamera Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berupaya untuk memberikan hasil yang akurat, harap diperhatikan bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang berwenang. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan manusia profesional. Kami tidak bertanggung jawab atas kesalahpahaman atau interpretasi yang keliru yang timbul dari penggunaan terjemahan ini.