<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c677667095f6133eee418c7e53615d05",
  "translation_date": "2025-08-27T20:59:25+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/pi-camera.md",
  "language_code": "ms"
}
-->
# Tangkap Imej - Raspberry Pi

Dalam bahagian pelajaran ini, anda akan menambah sensor kamera pada Raspberry Pi anda, dan membaca imej daripadanya.

## Perkakasan

Raspberry Pi memerlukan kamera.

Kamera yang akan anda gunakan ialah [Raspberry Pi Camera Module](https://www.raspberrypi.org/products/camera-module-v2/). Kamera ini direka untuk berfungsi dengan Raspberry Pi dan disambungkan melalui penyambung khusus pada Pi.

> 💁 Kamera ini menggunakan [Camera Serial Interface, protokol daripada Mobile Industry Processor Interface Alliance](https://wikipedia.org/wiki/Camera_Serial_Interface), dikenali sebagai MIPI-CSI. Ini adalah protokol khusus untuk menghantar imej.

## Sambungkan kamera

Kamera boleh disambungkan ke Raspberry Pi menggunakan kabel reben.

### Tugas - sambungkan kamera

![Kamera Raspberry Pi](../../../../../translated_images/ms/pi-camera-module.4278753c31bd6e757aa2b858be97d72049f71616278cefe4fb5abb485b40a078.png)

1. Matikan kuasa Pi.

1. Sambungkan kabel reben yang disertakan dengan kamera ke kamera. Untuk melakukannya, tarik perlahan klip plastik hitam pada pemegang supaya ia keluar sedikit, kemudian gelongsorkan kabel ke dalam soket, dengan bahagian biru menghadap jauh dari lensa, dan jalur pin logam menghadap ke arah lensa. Setelah kabel dimasukkan sepenuhnya, tolak klip plastik hitam kembali ke tempatnya.

   Anda boleh melihat animasi yang menunjukkan cara membuka klip dan memasukkan kabel pada [dokumentasi Raspberry Pi Getting Started with the Camera module](https://projects.raspberrypi.org/en/projects/getting-started-with-picamera/2).

   ![Kabel reben dimasukkan ke dalam modul kamera](../../../../../translated_images/ms/pi-camera-ribbon-cable.0bf82acd251611c21ac616f082849413e2b322a261d0e4f8fec344248083b07e.png)

1. Tanggalkan Grove Base Hat dari Pi.

1. Lalukan kabel reben melalui slot kamera di Grove Base Hat. Pastikan bahagian biru kabel menghadap ke arah port analog yang dilabelkan **A0**, **A1** dan sebagainya.

   ![Kabel reben melalui Grove Base Hat](../../../../../translated_images/ms/grove-base-hat-ribbon-cable.501fed202fcf73b11b2b68f6d246189f7d15d3e4423c572ddee79d77b4632b47.png)

1. Masukkan kabel reben ke dalam port kamera pada Pi. Sekali lagi, tarik klip plastik hitam ke atas, masukkan kabel, kemudian tolak klip kembali ke tempatnya. Bahagian biru kabel harus menghadap ke port USB dan ethernet.

   ![Kabel reben disambungkan ke soket kamera pada Pi](../../../../../translated_images/ms/pi-camera-socket-ribbon-cable.a18309920b11800911082ed7aa6fb28e6d9be3a022e4079ff990016cae3fca10.png)

1. Pasang semula Grove Base Hat.

## Programkan kamera

Raspberry Pi kini boleh diprogramkan untuk menggunakan kamera dengan menggunakan pustaka Python [PiCamera](https://pypi.org/project/picamera/).

### Tugas - aktifkan mod kamera legasi

Malangnya, dengan keluaran Raspberry Pi OS Bullseye, perisian kamera yang disertakan dengan OS telah berubah, menyebabkan PiCamera tidak berfungsi secara lalai. Terdapat pengganti yang sedang dibangunkan, dipanggil PiCamera2, tetapi ia belum sedia untuk digunakan.

Buat masa ini, anda boleh menetapkan Pi anda ke mod kamera legasi untuk membolehkan PiCamera berfungsi. Soket kamera juga dilumpuhkan secara lalai, tetapi menghidupkan perisian kamera legasi secara automatik akan mengaktifkan soket tersebut.

1. Hidupkan Pi dan tunggu sehingga ia selesai boot.

1. Lancarkan VS Code, sama ada terus pada Pi, atau sambung melalui sambungan Remote SSH.

1. Jalankan arahan berikut dari terminal anda:

    ```sh
    sudo raspi-config nonint do_legacy 0
    sudo reboot
    ```

    Ini akan menukar tetapan untuk mengaktifkan perisian kamera legasi, kemudian reboot Pi untuk membuat tetapan itu berkuat kuasa.

1. Tunggu Pi untuk reboot, kemudian lancarkan semula VS Code.

### Tugas - programkan kamera

Programkan peranti.

1. Dari terminal, buat folder baru dalam direktori rumah pengguna `pi` yang dipanggil `fruit-quality-detector`. Buat fail dalam folder ini yang dipanggil `app.py`.

1. Buka folder ini dalam VS Code.

1. Untuk berinteraksi dengan kamera, anda boleh menggunakan pustaka Python PiCamera. Pasang pakej Pip untuk ini dengan arahan berikut:

    ```sh
    pip3 install picamera
    ```

1. Tambahkan kod berikut ke fail `app.py` anda:

    ```python
    import io
    import time
    from picamera import PiCamera
    ```

    Kod ini mengimport beberapa pustaka yang diperlukan, termasuk pustaka `PiCamera`.

1. Tambahkan kod berikut di bawah ini untuk memulakan kamera:

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    
    time.sleep(2)
    ```

    Kod ini mencipta objek PiCamera, menetapkan resolusi kepada 640x480. Walaupun resolusi yang lebih tinggi disokong (sehingga 3280x2464), pengelas imej berfungsi pada imej yang jauh lebih kecil (227x227) jadi tidak perlu menangkap dan menghantar imej yang lebih besar.

    Baris `camera.rotation = 0` menetapkan putaran imej. Kabel reben masuk ke bahagian bawah kamera, tetapi jika kamera anda diputar untuk memudahkannya mengarah ke item yang ingin anda klasifikasikan, maka anda boleh menukar baris ini kepada bilangan darjah putaran.

    ![Kamera tergantung di atas tin minuman](../../../../../translated_images/ms/pi-camera-upside-down.5376961ba31459883362124152ad6b823d5ac5fc14e85f317e22903bd681c2b6.png)

    Sebagai contoh, jika anda menggantung kabel reben di atas sesuatu supaya ia berada di bahagian atas kamera, maka tetapkan putaran kepada 180:

    ```python
    camera.rotation = 180
    ```

    Kamera mengambil masa beberapa saat untuk memulakan, oleh itu baris `time.sleep(2)`.

1. Tambahkan kod berikut di bawah ini untuk menangkap imej sebagai data binari:

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    Kod ini mencipta objek `BytesIO` untuk menyimpan data binari. Imej dibaca dari kamera sebagai fail JPEG dan disimpan dalam objek ini. Objek ini mempunyai penunjuk kedudukan untuk mengetahui di mana ia berada dalam data supaya lebih banyak data boleh ditulis ke hujung jika diperlukan, jadi baris `image.seek(0)` menggerakkan kedudukan ini kembali ke permulaan supaya semua data boleh dibaca kemudian.

1. Di bawah ini, tambahkan kod berikut untuk menyimpan imej ke fail:

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    Kod ini membuka fail yang dipanggil `image.jpg` untuk penulisan, kemudian membaca semua data dari objek `BytesIO` dan menulisnya ke fail.

    > 💁 Anda boleh menangkap imej terus ke fail dan bukannya objek `BytesIO` dengan memberikan nama fail kepada panggilan `camera.capture`. Sebab menggunakan objek `BytesIO` adalah supaya kemudian dalam pelajaran ini anda boleh menghantar imej ke pengelas imej anda.

1. Arahkan kamera ke sesuatu dan jalankan kod ini.

1. Imej akan ditangkap dan disimpan sebagai `image.jpg` dalam folder semasa. Anda akan melihat fail ini dalam penjelajah VS Code. Pilih fail untuk melihat imej. Jika ia memerlukan putaran, kemas kini baris `camera.rotation = 0` seperti yang diperlukan dan ambil gambar lain.

> 💁 Anda boleh menemui kod ini dalam folder [code-camera/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/pi).

😀 Program kamera anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil maklum bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.