<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c677667095f6133eee418c7e53615d05",
  "translation_date": "2025-08-27T20:58:53+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/pi-camera.md",
  "language_code": "id"
}
-->
# Menangkap Gambar - Raspberry Pi

Dalam bagian pelajaran ini, Anda akan menambahkan sensor kamera ke Raspberry Pi dan membaca gambar darinya.

## Perangkat Keras

Raspberry Pi membutuhkan kamera.

Kamera yang akan Anda gunakan adalah [Raspberry Pi Camera Module](https://www.raspberrypi.org/products/camera-module-v2/). Kamera ini dirancang untuk bekerja dengan Raspberry Pi dan terhubung melalui konektor khusus di Pi.

> 💁 Kamera ini menggunakan [Camera Serial Interface, sebuah protokol dari Mobile Industry Processor Interface Alliance](https://wikipedia.org/wiki/Camera_Serial_Interface), yang dikenal sebagai MIPI-CSI. Ini adalah protokol khusus untuk mengirimkan gambar.

## Menghubungkan Kamera

Kamera dapat dihubungkan ke Raspberry Pi menggunakan kabel pita.

### Tugas - Menghubungkan Kamera

![Kamera Raspberry Pi](../../../../../translated_images/id/pi-camera-module.4278753c31bd6e757aa2b858be97d72049f71616278cefe4fb5abb485b40a078.png)

1. Matikan daya Pi.

1. Hubungkan kabel pita yang disertakan dengan kamera ke kamera. Untuk melakukannya, tarik perlahan klip plastik hitam di penahan sehingga keluar sedikit, lalu geser kabel ke dalam soket, dengan sisi biru menghadap jauh dari lensa, dan strip pin logam menghadap ke lensa. Setelah kabel masuk sepenuhnya, dorong klip plastik hitam kembali ke tempatnya.

    Anda dapat menemukan animasi yang menunjukkan cara membuka klip dan memasukkan kabel di [dokumentasi Memulai dengan Modul Kamera Raspberry Pi](https://projects.raspberrypi.org/en/projects/getting-started-with-picamera/2).

    ![Kabel pita dimasukkan ke modul kamera](../../../../../translated_images/id/pi-camera-ribbon-cable.0bf82acd251611c21ac616f082849413e2b322a261d0e4f8fec344248083b07e.png)

1. Lepaskan Grove Base Hat dari Pi.

1. Lewatkan kabel pita melalui slot kamera di Grove Base Hat. Pastikan sisi biru kabel menghadap ke port analog yang diberi label **A0**, **A1**, dll.

    ![Kabel pita melewati Grove Base Hat](../../../../../translated_images/id/grove-base-hat-ribbon-cable.501fed202fcf73b11b2b68f6d246189f7d15d3e4423c572ddee79d77b4632b47.png)

1. Masukkan kabel pita ke port kamera di Pi. Sekali lagi, tarik klip plastik hitam ke atas, masukkan kabel, lalu dorong klip kembali ke tempatnya. Sisi biru kabel harus menghadap ke port USB dan ethernet.

    ![Kabel pita terhubung ke soket kamera di Pi](../../../../../translated_images/id/pi-camera-socket-ribbon-cable.a18309920b11800911082ed7aa6fb28e6d9be3a022e4079ff990016cae3fca10.png)

1. Pasang kembali Grove Base Hat.

## Memprogram Kamera

Raspberry Pi sekarang dapat diprogram untuk menggunakan kamera menggunakan pustaka Python [PiCamera](https://pypi.org/project/picamera/).

### Tugas - Mengaktifkan Mode Kamera Legacy

Sayangnya, dengan dirilisnya Raspberry Pi OS Bullseye, perangkat lunak kamera yang disertakan dengan OS berubah, sehingga secara default PiCamera tidak lagi berfungsi. Ada pengganti yang sedang dikembangkan, bernama PiCamera2, tetapi ini belum siap untuk digunakan.

Untuk saat ini, Anda dapat mengatur Pi ke mode kamera legacy agar PiCamera dapat berfungsi. Soket kamera juga dinonaktifkan secara default, tetapi mengaktifkan perangkat lunak kamera legacy secara otomatis mengaktifkan soket.

1. Nyalakan Pi dan tunggu hingga selesai booting.

1. Luncurkan VS Code, baik langsung di Pi, atau sambungkan melalui ekstensi Remote SSH.

1. Jalankan perintah berikut dari terminal Anda:

    ```sh
    sudo raspi-config nonint do_legacy 0
    sudo reboot
    ```

    Perintah ini akan mengubah pengaturan untuk mengaktifkan perangkat lunak kamera legacy, lalu me-reboot Pi agar pengaturan tersebut berlaku.

1. Tunggu Pi untuk reboot, lalu luncurkan kembali VS Code.

### Tugas - Memprogram Kamera

Program perangkat.

1. Dari terminal, buat folder baru di direktori home pengguna `pi` bernama `fruit-quality-detector`. Buat file di folder ini bernama `app.py`.

1. Buka folder ini di VS Code.

1. Untuk berinteraksi dengan kamera, Anda dapat menggunakan pustaka Python PiCamera. Instal paket Pip untuk ini dengan perintah berikut:

    ```sh
    pip3 install picamera
    ```

1. Tambahkan kode berikut ke file `app.py` Anda:

    ```python
    import io
    import time
    from picamera import PiCamera
    ```

    Kode ini mengimpor beberapa pustaka yang diperlukan, termasuk pustaka `PiCamera`.

1. Tambahkan kode berikut di bawah ini untuk menginisialisasi kamera:

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    
    time.sleep(2)
    ```

    Kode ini membuat objek PiCamera, mengatur resolusi ke 640x480. Meskipun resolusi yang lebih tinggi didukung (hingga 3280x2464), pengklasifikasi gambar bekerja pada gambar yang jauh lebih kecil (227x227) sehingga tidak perlu menangkap dan mengirim gambar yang lebih besar.

    Baris `camera.rotation = 0` mengatur rotasi gambar. Kabel pita masuk ke bagian bawah kamera, tetapi jika kamera Anda diputar agar lebih mudah mengarah ke objek yang ingin Anda klasifikasikan, maka Anda dapat mengubah baris ini ke jumlah derajat rotasi.

    ![Kamera menggantung di atas kaleng minuman](../../../../../translated_images/id/pi-camera-upside-down.5376961ba31459883362124152ad6b823d5ac5fc14e85f317e22903bd681c2b6.png)

    Misalnya, jika Anda menggantung kabel pita di atas sesuatu sehingga berada di bagian atas kamera, maka atur rotasi menjadi 180:

    ```python
    camera.rotation = 180
    ```

    Kamera membutuhkan beberapa detik untuk memulai, oleh karena itu baris `time.sleep(2)`.

1. Tambahkan kode berikut di bawah ini untuk menangkap gambar sebagai data biner:

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    Kode ini membuat objek `BytesIO` untuk menyimpan data biner. Gambar dibaca dari kamera sebagai file JPEG dan disimpan di objek ini. Objek ini memiliki indikator posisi untuk mengetahui di mana posisinya dalam data sehingga lebih banyak data dapat ditulis di akhir jika diperlukan, jadi baris `image.seek(0)` memindahkan posisi ini kembali ke awal sehingga semua data dapat dibaca nanti.

1. Di bawah ini, tambahkan kode berikut untuk menyimpan gambar ke file:

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    Kode ini membuka file bernama `image.jpg` untuk ditulis, lalu membaca semua data dari objek `BytesIO` dan menulisnya ke file.

    > 💁 Anda dapat menangkap gambar langsung ke file alih-alih objek `BytesIO` dengan memberikan nama file ke panggilan `camera.capture`. Alasan menggunakan objek `BytesIO` adalah agar nanti dalam pelajaran ini Anda dapat mengirim gambar ke pengklasifikasi gambar Anda.

1. Arahkan kamera ke sesuatu dan jalankan kode ini.

1. Gambar akan ditangkap dan disimpan sebagai `image.jpg` di folder saat ini. Anda akan melihat file ini di penjelajah VS Code. Pilih file untuk melihat gambar. Jika perlu rotasi, perbarui baris `camera.rotation = 0` sesuai kebutuhan dan ambil gambar lagi.

> 💁 Anda dapat menemukan kode ini di folder [code-camera/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/pi).

😀 Program kamera Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.