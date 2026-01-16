<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "557f4ee96b752e0651d2e6e74aa6bd14",
  "translation_date": "2025-08-27T20:56:10+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/README.md",
  "language_code": "id"
}
-->
# Periksa Kualitas Buah dari Perangkat IoT

![Gambaran sketchnote dari pelajaran ini](../../../../../translated_images/id/lesson-16.215daf18b00631fbdfd64c6fc2dc6044dff5d544288825d8076f9fb83d964c23.jpg)

> Sketchnote oleh [Nitya Narasimhan](https://github.com/nitya). Klik gambar untuk versi yang lebih besar.

## Kuis Pra-Pelajaran

[Kuis Pra-Pelajaran](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/31)

## Pendahuluan

Pada pelajaran sebelumnya, Anda telah mempelajari tentang pengklasifikasi gambar dan cara melatihnya untuk mendeteksi buah yang baik dan buruk. Untuk menggunakan pengklasifikasi gambar ini dalam aplikasi IoT, Anda perlu dapat menangkap gambar menggunakan kamera tertentu, lalu mengirimkan gambar tersebut ke cloud untuk diklasifikasikan.

Dalam pelajaran ini, Anda akan mempelajari tentang sensor kamera dan cara menggunakannya dengan perangkat IoT untuk menangkap gambar. Anda juga akan mempelajari cara memanggil pengklasifikasi gambar dari perangkat IoT Anda.

Dalam pelajaran ini, kita akan membahas:

* [Sensor kamera](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Menangkap gambar menggunakan perangkat IoT](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Menerbitkan pengklasifikasi gambar Anda](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Mengklasifikasikan gambar dari perangkat IoT Anda](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Meningkatkan model](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)

## Sensor Kamera

Sensor kamera, seperti namanya, adalah kamera yang dapat Anda hubungkan ke perangkat IoT Anda. Kamera ini dapat mengambil gambar diam atau merekam video streaming. Beberapa kamera akan mengembalikan data gambar mentah, sementara yang lain akan mengompresi data gambar menjadi file gambar seperti JPEG atau PNG. Biasanya, kamera yang digunakan dengan perangkat IoT jauh lebih kecil dan memiliki resolusi lebih rendah dibandingkan yang biasa Anda gunakan, tetapi Anda juga dapat menemukan kamera beresolusi tinggi yang sebanding dengan ponsel kelas atas. Anda juga dapat menemukan berbagai lensa yang dapat diganti, pengaturan kamera ganda, kamera termal infra-merah, atau kamera UV.

![Cahaya dari sebuah adegan melewati lensa dan difokuskan pada sensor CMOS](../../../../../translated_images/id/cmos-sensor.75f9cd74decb137149a4c9ea825251a4549497d67c0ae2776159e6102bb53aa9.png)

Sebagian besar sensor kamera menggunakan sensor gambar di mana setiap piksel adalah fotodioda. Sebuah lensa memfokuskan gambar ke sensor gambar, dan ribuan atau jutaan fotodioda mendeteksi cahaya yang jatuh pada masing-masing, lalu merekamnya sebagai data piksel.

> 💁 Lensa membalikkan gambar, dan sensor kamera kemudian membalik gambar kembali ke posisi yang benar. Hal yang sama terjadi pada mata Anda - apa yang Anda lihat terdeteksi terbalik di bagian belakang mata Anda, dan otak Anda memperbaikinya.

> 🎓 Sensor gambar dikenal sebagai Active-Pixel Sensor (APS), dan jenis APS yang paling populer adalah sensor complementary metal-oxide semiconductor, atau CMOS. Anda mungkin pernah mendengar istilah sensor CMOS digunakan untuk sensor kamera.

Sensor kamera adalah sensor digital, yang mengirimkan data gambar sebagai data digital, biasanya dengan bantuan pustaka yang menyediakan komunikasi. Kamera terhubung menggunakan protokol seperti SPI untuk memungkinkan mereka mengirimkan data dalam jumlah besar - gambar jauh lebih besar dibandingkan angka tunggal dari sensor seperti sensor suhu.

✅ Apa saja keterbatasan ukuran gambar pada perangkat IoT? Pikirkan tentang kendala terutama pada perangkat keras mikrokontroler.

## Menangkap Gambar Menggunakan Perangkat IoT

Anda dapat menggunakan perangkat IoT Anda untuk menangkap gambar yang akan diklasifikasikan.

### Tugas - menangkap gambar menggunakan perangkat IoT

Ikuti panduan yang relevan untuk menangkap gambar menggunakan perangkat IoT Anda:

* [Arduino - Wio Terminal](wio-terminal-camera.md)
* [Komputer papan tunggal - Raspberry Pi](pi-camera.md)
* [Komputer papan tunggal - Perangkat virtual](virtual-device-camera.md)

## Menerbitkan Pengklasifikasi Gambar Anda

Anda telah melatih pengklasifikasi gambar Anda pada pelajaran sebelumnya. Sebelum Anda dapat menggunakannya dari perangkat IoT Anda, Anda perlu menerbitkan model tersebut.

### Iterasi Model

Saat model Anda dilatih pada pelajaran sebelumnya, Anda mungkin memperhatikan bahwa tab **Performance** menunjukkan iterasi di sisi layar. Ketika Anda pertama kali melatih model, Anda akan melihat *Iteration 1* dalam pelatihan. Ketika Anda meningkatkan model menggunakan gambar prediksi, Anda akan melihat *Iteration 2* dalam pelatihan.

Setiap kali Anda melatih model, Anda mendapatkan iterasi baru. Ini adalah cara untuk melacak berbagai versi model Anda yang dilatih pada kumpulan data yang berbeda. Ketika Anda melakukan **Quick Test**, ada menu drop-down yang dapat Anda gunakan untuk memilih iterasi, sehingga Anda dapat membandingkan hasil di berbagai iterasi.

Ketika Anda puas dengan sebuah iterasi, Anda dapat menerbitkannya agar dapat digunakan oleh aplikasi eksternal. Dengan cara ini, Anda dapat memiliki versi yang diterbitkan yang digunakan oleh perangkat Anda, lalu bekerja pada versi baru melalui beberapa iterasi, kemudian menerbitkannya setelah Anda puas dengan hasilnya.

### Tugas - menerbitkan sebuah iterasi

Iterasi diterbitkan dari portal Custom Vision.

1. Buka portal Custom Vision di [CustomVision.ai](https://customvision.ai) dan masuk jika Anda belum membukanya. Kemudian buka proyek `fruit-quality-detector` Anda.

1. Pilih tab **Performance** dari opsi di bagian atas.

1. Pilih iterasi terbaru dari daftar *Iterations* di sisi layar.

1. Pilih tombol **Publish** untuk iterasi tersebut.

    ![Tombol publish](../../../../../translated_images/id/custom-vision-publish-button.b7174e1977b0c33b8b72d4e5b1326c779e0af196f3849d09985ee2d7d5493a39.png)

1. Dalam dialog *Publish Model*, atur *Prediction resource* ke sumber daya `fruit-quality-detector-prediction` yang Anda buat pada pelajaran sebelumnya. Biarkan nama sebagai `Iteration2`, lalu pilih tombol **Publish**.

1. Setelah diterbitkan, pilih tombol **Prediction URL**. Ini akan menampilkan detail API prediksi, dan Anda akan memerlukan ini untuk memanggil model dari perangkat IoT Anda. Bagian bawah diberi label *If you have an image file*, dan ini adalah detail yang Anda butuhkan. Salin URL yang ditampilkan, yang akan terlihat seperti:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/classify/iterations/Iteration2/image
    ```

    Di mana `<location>` adalah lokasi yang Anda gunakan saat membuat sumber daya custom vision Anda, dan `<id>` adalah ID panjang yang terdiri dari huruf dan angka.

    Juga salin nilai *Prediction-Key*. Ini adalah kunci aman yang harus Anda sertakan saat memanggil model. Hanya aplikasi yang menyertakan kunci ini yang diizinkan menggunakan model, aplikasi lain akan ditolak.

    ![Dialog API prediksi yang menunjukkan URL dan kunci](../../../../../translated_images/id/custom-vision-prediction-key-endpoint.30c569ffd0338864f319911f052d5e9b8c5066cb0800a26dd6f7ff5713130ad8.png)

✅ Ketika iterasi baru diterbitkan, iterasi tersebut akan memiliki nama yang berbeda. Bagaimana menurut Anda cara mengubah iterasi yang digunakan oleh perangkat IoT?

## Mengklasifikasikan Gambar dari Perangkat IoT Anda

Sekarang Anda dapat menggunakan detail koneksi ini untuk memanggil pengklasifikasi gambar dari perangkat IoT Anda.

### Tugas - mengklasifikasikan gambar dari perangkat IoT Anda

Ikuti panduan yang relevan untuk mengklasifikasikan gambar menggunakan perangkat IoT Anda:

* [Arduino - Wio Terminal](wio-terminal-classify-image.md)
* [Komputer papan tunggal - Raspberry Pi/Perangkat IoT virtual](single-board-computer-classify-image.md)

## Meningkatkan Model

Anda mungkin menemukan bahwa hasil yang Anda dapatkan saat menggunakan kamera yang terhubung ke perangkat IoT Anda tidak sesuai dengan yang Anda harapkan. Prediksi tidak selalu seakurat saat menggunakan gambar yang diunggah dari komputer Anda. Hal ini terjadi karena model dilatih dengan data yang berbeda dari yang digunakan untuk prediksi.

Untuk mendapatkan hasil terbaik dari pengklasifikasi gambar, Anda ingin melatih model dengan gambar yang semirip mungkin dengan gambar yang digunakan untuk prediksi. Jika Anda menggunakan kamera ponsel untuk menangkap gambar untuk pelatihan, misalnya, kualitas gambar, ketajaman, dan warnanya akan berbeda dengan kamera yang terhubung ke perangkat IoT.

![2 gambar pisang, satu dengan resolusi rendah dan pencahayaan buruk dari perangkat IoT, dan satu dengan resolusi tinggi dan pencahayaan baik dari ponsel](../../../../../translated_images/id/banana-picture-compare.174df164dc326a42cf7fb051a7497e6113c620e91552d92ca914220305d47d9a.png)

Pada gambar di atas, gambar pisang di sebelah kiri diambil menggunakan Kamera Raspberry Pi, sedangkan gambar di sebelah kanan diambil dari pisang yang sama di lokasi yang sama menggunakan iPhone. Ada perbedaan kualitas yang mencolok - gambar iPhone lebih tajam, dengan warna yang lebih cerah dan kontras yang lebih baik.

✅ Apa lagi yang mungkin menyebabkan gambar yang ditangkap oleh perangkat IoT Anda menghasilkan prediksi yang salah? Pikirkan tentang lingkungan tempat perangkat IoT mungkin digunakan, faktor apa saja yang dapat memengaruhi gambar yang ditangkap?

Untuk meningkatkan model, Anda dapat melatih ulang menggunakan gambar yang ditangkap dari perangkat IoT.

### Tugas - meningkatkan model

1. Klasifikasikan beberapa gambar buah matang dan tidak matang menggunakan perangkat IoT Anda.

1. Di portal Custom Vision, latih ulang model menggunakan gambar di tab *Predictions*.

    > ⚠️ Anda dapat merujuk ke [instruksi untuk melatih ulang pengklasifikasi Anda di pelajaran 1 jika diperlukan](../1-train-fruit-detector/README.md#retrain-your-image-classifier).

1. Jika gambar Anda terlihat sangat berbeda dari gambar asli yang digunakan untuk pelatihan, Anda dapat menghapus semua gambar asli dengan memilihnya di tab *Training Images* dan memilih tombol **Delete**. Untuk memilih gambar, arahkan kursor Anda ke atasnya dan tanda centang akan muncul, pilih tanda centang tersebut untuk memilih atau membatalkan pilihan gambar.

1. Latih iterasi baru dari model dan terbitkan menggunakan langkah-langkah di atas.

1. Perbarui URL endpoint di kode Anda, lalu jalankan ulang aplikasi.

1. Ulangi langkah-langkah ini hingga Anda puas dengan hasil prediksi.

---

## 🚀 Tantangan

Seberapa besar resolusi gambar atau pencahayaan memengaruhi prediksi?

Cobalah mengubah resolusi gambar dalam kode perangkat Anda dan lihat apakah itu memengaruhi kualitas gambar. Juga coba ubah pencahayaan.

Jika Anda ingin membuat perangkat produksi untuk dijual ke peternakan atau pabrik, bagaimana Anda memastikan perangkat tersebut memberikan hasil yang konsisten setiap saat?

## Kuis Pasca-Pelajaran

[Kuis Pasca-Pelajaran](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/32)

## Tinjauan & Studi Mandiri

Anda melatih model custom vision Anda menggunakan portal. Ini bergantung pada ketersediaan gambar - dan di dunia nyata, Anda mungkin tidak dapat memperoleh data pelatihan yang sesuai dengan apa yang ditangkap oleh kamera pada perangkat Anda. Anda dapat mengatasi ini dengan melatih langsung dari perangkat Anda menggunakan API pelatihan, untuk melatih model menggunakan gambar yang ditangkap dari perangkat IoT Anda.

* Baca lebih lanjut tentang API pelatihan di [panduan memulai cepat menggunakan Custom Vision SDK](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/quickstarts/image-classification?WT.mc_id=academic-17441-jabenn&tabs=visual-studio&pivots=programming-language-python)

## Tugas

[Tanggapi hasil klasifikasi](assignment.md)

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.