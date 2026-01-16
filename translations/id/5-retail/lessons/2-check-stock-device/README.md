<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1c9e5fa8b7be726c75a97232b1e41c97",
  "translation_date": "2025-08-27T20:41:00+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/README.md",
  "language_code": "id"
}
-->
# Periksa Stok dari Perangkat IoT

![Gambaran sketchnote dari pelajaran ini](../../../../../translated_images/id/lesson-20.0211df9551a8abb300fc8fcf7dc2789468dea2eabe9202273ac077b0ba37f15e.jpg)

> Sketchnote oleh [Nitya Narasimhan](https://github.com/nitya). Klik gambar untuk versi yang lebih besar.

## Kuis Pra-Pelajaran

[Kuis Pra-Pelajaran](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/39)

## Pendahuluan

Pada pelajaran sebelumnya, Anda telah mempelajari berbagai penggunaan deteksi objek dalam ritel. Anda juga telah belajar cara melatih detektor objek untuk mengidentifikasi stok. Dalam pelajaran ini, Anda akan mempelajari cara menggunakan detektor objek Anda dari perangkat IoT untuk menghitung stok.

Dalam pelajaran ini, kita akan membahas:

* [Menghitung stok](../../../../../5-retail/lessons/2-check-stock-device)
* [Memanggil detektor objek dari perangkat IoT Anda](../../../../../5-retail/lessons/2-check-stock-device)
* [Kotak pembatas](../../../../../5-retail/lessons/2-check-stock-device)
* [Melatih ulang model](../../../../../5-retail/lessons/2-check-stock-device)
* [Menghitung stok](../../../../../5-retail/lessons/2-check-stock-device)

> 🗑 Ini adalah pelajaran terakhir dalam proyek ini, jadi setelah menyelesaikan pelajaran dan tugas ini, jangan lupa untuk membersihkan layanan cloud Anda. Anda akan membutuhkan layanan tersebut untuk menyelesaikan tugas, jadi pastikan untuk menyelesaikannya terlebih dahulu.
>
> Lihat [panduan membersihkan proyek Anda](../../../clean-up.md) jika diperlukan untuk instruksi tentang cara melakukannya.

## Menghitung Stok

Detektor objek dapat digunakan untuk memeriksa stok, baik untuk menghitung stok atau memastikan stok berada di tempat yang seharusnya. Perangkat IoT dengan kamera dapat ditempatkan di seluruh toko untuk memantau stok, dimulai dari area penting di mana pengisian ulang barang sangat penting, seperti area dengan barang bernilai tinggi dalam jumlah kecil.

Sebagai contoh, jika sebuah kamera mengarah ke rak yang dapat menampung 8 kaleng pasta tomat, dan detektor objek hanya mendeteksi 7 kaleng, maka satu kaleng hilang dan perlu diisi ulang.

![7 kaleng pasta tomat di rak, 4 di baris atas, 3 di bawah](../../../../../translated_images/id/stock-7-cans-tomato-paste.f86059cc573d7bec.webp)

Pada gambar di atas, detektor objek telah mendeteksi 7 kaleng pasta tomat di rak yang dapat menampung 8 kaleng. Tidak hanya perangkat IoT dapat mengirimkan notifikasi kebutuhan pengisian ulang, tetapi juga dapat memberikan indikasi lokasi barang yang hilang, data penting jika Anda menggunakan robot untuk mengisi ulang rak.

> 💁 Tergantung pada toko dan popularitas barang, pengisian ulang mungkin tidak dilakukan jika hanya 1 kaleng yang hilang. Anda perlu membangun algoritma yang menentukan kapan harus mengisi ulang berdasarkan produk, pelanggan, dan kriteria lainnya.

✅ Dalam skenario lain apa Anda dapat menggabungkan deteksi objek dan robot?

Terkadang stok yang salah bisa berada di rak. Ini bisa terjadi karena kesalahan manusia saat mengisi ulang, atau pelanggan yang berubah pikiran dan meletakkan barang di tempat pertama yang tersedia. Jika ini adalah barang non-perishable seperti makanan kaleng, ini hanya menjadi gangguan. Namun, jika ini adalah barang perishable seperti makanan beku atau dingin, produk tersebut mungkin tidak dapat dijual lagi karena sulit untuk mengetahui berapa lama barang tersebut berada di luar freezer.

Deteksi objek dapat digunakan untuk mendeteksi barang yang tidak sesuai, dan memberi tahu manusia atau robot untuk segera mengembalikan barang tersebut.

![Sebuah kaleng jagung bayi yang salah tempat di rak pasta tomat](../../../../../translated_images/id/stock-rogue-corn.be1f3ada8c457854.webp)

Pada gambar di atas, sebuah kaleng jagung bayi telah diletakkan di rak pasta tomat. Detektor objek telah mendeteksi ini, memungkinkan perangkat IoT memberi tahu manusia atau robot untuk mengembalikan kaleng tersebut ke lokasi yang benar.

## Memanggil Detektor Objek dari Perangkat IoT Anda

Detektor objek yang Anda latih pada pelajaran sebelumnya dapat dipanggil dari perangkat IoT Anda.

### Tugas - Menerbitkan Iterasi Detektor Objek Anda

Iterasi diterbitkan dari portal Custom Vision.

1. Buka portal Custom Vision di [CustomVision.ai](https://customvision.ai) dan masuk jika Anda belum membukanya. Kemudian buka proyek `stock-detector` Anda.

1. Pilih tab **Performance** dari opsi di bagian atas.

1. Pilih iterasi terbaru dari daftar *Iterations* di sisi kiri.

1. Pilih tombol **Publish** untuk iterasi tersebut.

    ![Tombol publish](../../../../../translated_images/id/custom-vision-object-detector-publish-button.34ee379fc650ccb9856c3868d0003f413b9529f102fc73c37168c98d721cc293.png)

1. Dalam dialog *Publish Model*, atur *Prediction resource* ke sumber daya `stock-detector-prediction` yang Anda buat pada pelajaran sebelumnya. Biarkan nama sebagai `Iteration2`, dan pilih tombol **Publish**.

1. Setelah diterbitkan, pilih tombol **Prediction URL**. Ini akan menampilkan detail API prediksi, dan Anda akan membutuhkan ini untuk memanggil model dari perangkat IoT Anda. Bagian bawah diberi label *If you have an image file*, dan ini adalah detail yang Anda butuhkan. Salin URL yang ditampilkan, yang akan terlihat seperti:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/detect/iterations/Iteration2/image
    ```

    Di mana `<location>` adalah lokasi yang Anda gunakan saat membuat sumber daya Custom Vision Anda, dan `<id>` adalah ID panjang yang terdiri dari huruf dan angka.

    Juga salin nilai *Prediction-Key*. Ini adalah kunci aman yang harus Anda sertakan saat memanggil model. Hanya aplikasi yang menyertakan kunci ini yang diizinkan menggunakan model, aplikasi lain akan ditolak.

    ![Dialog API prediksi yang menunjukkan URL dan kunci](../../../../../translated_images/id/custom-vision-prediction-key-endpoint.30c569ffd0338864f319911f052d5e9b8c5066cb0800a26dd6f7ff5713130ad8.png)

✅ Ketika iterasi baru diterbitkan, iterasi tersebut akan memiliki nama yang berbeda. Bagaimana menurut Anda cara mengubah iterasi yang digunakan perangkat IoT?

### Tugas - Memanggil Detektor Objek Anda dari Perangkat IoT

Ikuti panduan yang relevan di bawah ini untuk menggunakan detektor objek dari perangkat IoT Anda:

* [Arduino - Wio Terminal](wio-terminal-object-detector.md)
* [Komputer papan tunggal - Raspberry Pi/Perangkat virtual](single-board-computer-object-detector.md)

## Kotak Pembatas

Saat Anda menggunakan detektor objek, Anda tidak hanya mendapatkan kembali objek yang terdeteksi dengan tag dan probabilitasnya, tetapi juga kotak pembatas dari objek tersebut. Kotak ini mendefinisikan di mana detektor objek mendeteksi objek dengan probabilitas tertentu.

> 💁 Kotak pembatas adalah kotak yang mendefinisikan area yang berisi objek yang terdeteksi, kotak yang mendefinisikan batas untuk objek tersebut.

Hasil prediksi di tab **Predictions** di Custom Vision memiliki kotak pembatas yang digambar pada gambar yang dikirim untuk prediksi.

![4 kaleng pasta tomat di rak dengan prediksi untuk 4 deteksi masing-masing 35.8%, 33.5%, 25.7%, dan 16.6%](../../../../../translated_images/id/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

Pada gambar di atas, 4 kaleng pasta tomat terdeteksi. Dalam hasilnya, kotak merah ditampilkan untuk setiap objek yang terdeteksi dalam gambar, menunjukkan kotak pembatas untuk gambar tersebut.

✅ Buka prediksi di Custom Vision dan periksa kotak pembatas.

Kotak pembatas didefinisikan dengan 4 nilai - atas, kiri, tinggi, dan lebar. Nilai-nilai ini berada dalam skala 0-1, mewakili posisi sebagai persentase dari ukuran gambar. Titik asal (posisi 0,0) adalah sudut kiri atas gambar, sehingga nilai atas adalah jarak dari atas, dan bagian bawah kotak pembatas adalah nilai atas ditambah tinggi.

![Kotak pembatas di sekitar kaleng pasta tomat](../../../../../translated_images/id/bounding-box.1420a7ea0d3d15f71e1ffb5cf4b2271d184fac051f990abc541975168d163684.png)

Gambar di atas memiliki lebar 600 piksel dan tinggi 800 piksel. Kotak pembatas dimulai pada 320 piksel ke bawah, memberikan koordinat atas 0.4 (800 x 0.4 = 320). Dari kiri, kotak pembatas dimulai pada 240 piksel ke samping, memberikan koordinat kiri 0.4 (600 x 0.4 = 240). Tinggi kotak pembatas adalah 240 piksel, memberikan nilai tinggi 0.3 (800 x 0.3 = 240). Lebar kotak pembatas adalah 120 piksel, memberikan nilai lebar 0.2 (600 x 0.2 = 120).

| Koordinat | Nilai |
| ---------- | ----: |
| Atas       | 0.4   |
| Kiri       | 0.4   |
| Tinggi     | 0.3   |
| Lebar      | 0.2   |

Menggunakan nilai persentase dari 0-1 berarti tidak peduli seberapa besar gambar diubah ukurannya, kotak pembatas dimulai 0.4 dari panjang dan lebar, dan memiliki tinggi 0.3 serta lebar 0.2.

Anda dapat menggunakan kotak pembatas yang dikombinasikan dengan probabilitas untuk mengevaluasi seberapa akurat suatu deteksi. Sebagai contoh, detektor objek dapat mendeteksi beberapa objek yang saling tumpang tindih, misalnya mendeteksi satu kaleng di dalam kaleng lainnya. Kode Anda dapat memeriksa kotak pembatas, memahami bahwa ini tidak mungkin, dan mengabaikan objek apa pun yang memiliki tumpang tindih signifikan dengan objek lain.

![Dua kotak pembatas tumpang tindih pada kaleng pasta tomat](../../../../../translated_images/id/overlap-object-detection.d431e03cae75072a2760430eca7f2c5fdd43045bfd72dadcbf12711f7cd6c2ae.png)

Dalam contoh di atas, satu kotak pembatas menunjukkan prediksi kaleng pasta tomat dengan probabilitas 78.3%. Kotak pembatas kedua sedikit lebih kecil, dan berada di dalam kotak pembatas pertama dengan probabilitas 64.3%. Kode Anda dapat memeriksa kotak pembatas, melihat bahwa mereka sepenuhnya tumpang tindih, dan mengabaikan probabilitas yang lebih rendah karena tidak mungkin satu kaleng berada di dalam kaleng lainnya.

✅ Bisakah Anda memikirkan situasi di mana valid untuk mendeteksi satu objek di dalam objek lain?

## Melatih Ulang Model

Seperti pada pengklasifikasi gambar, Anda dapat melatih ulang model Anda menggunakan data yang ditangkap oleh perangkat IoT Anda. Menggunakan data dunia nyata ini akan memastikan model Anda bekerja dengan baik saat digunakan dari perangkat IoT Anda.

Berbeda dengan pengklasifikasi gambar, Anda tidak bisa hanya memberi tag pada gambar. Sebaliknya, Anda perlu meninjau setiap kotak pembatas yang terdeteksi oleh model. Jika kotak tersebut mengelilingi hal yang salah, maka kotak tersebut perlu dihapus, jika lokasinya salah, maka perlu disesuaikan.

### Tugas - Melatih Ulang Model

1. Pastikan Anda telah menangkap berbagai gambar menggunakan perangkat IoT Anda.

1. Dari tab **Predictions**, pilih sebuah gambar. Anda akan melihat kotak merah yang menunjukkan kotak pembatas dari objek yang terdeteksi.

1. Tinjau setiap kotak pembatas. Pilih kotak tersebut dan Anda akan melihat pop-up yang menunjukkan tag. Gunakan pegangan di sudut kotak pembatas untuk menyesuaikan ukurannya jika diperlukan. Jika tag salah, hapus dengan tombol **X** dan tambahkan tag yang benar. Jika kotak pembatas tidak berisi objek, hapus dengan tombol tempat sampah.

1. Tutup editor setelah selesai dan gambar akan berpindah dari tab **Predictions** ke tab **Training Images**. Ulangi proses ini untuk semua prediksi.

1. Gunakan tombol **Train** untuk melatih ulang model Anda. Setelah selesai dilatih, terbitkan iterasi dan perbarui perangkat IoT Anda untuk menggunakan URL dari iterasi baru.

1. Terapkan ulang kode Anda dan uji perangkat IoT Anda.

## Menghitung Stok

Dengan menggabungkan jumlah objek yang terdeteksi dan kotak pembatas, Anda dapat menghitung stok di rak.

### Tugas - Menghitung Stok

Ikuti panduan yang relevan di bawah ini untuk menghitung stok menggunakan hasil dari detektor objek dari perangkat IoT Anda:

* [Arduino - Wio Terminal](wio-terminal-count-stock.md)
* [Komputer papan tunggal - Raspberry Pi/Perangkat virtual](single-board-computer-count-stock.md)

---

## 🚀 Tantangan

Bisakah Anda mendeteksi stok yang salah? Latih model Anda pada beberapa objek, lalu perbarui aplikasi Anda untuk memberi tahu Anda jika stok yang salah terdeteksi.

Mungkin bahkan bawa ini lebih jauh dan deteksi stok yang berdampingan di rak yang sama, dan lihat apakah sesuatu telah diletakkan di tempat yang salah dengan mendefinisikan batas pada kotak pembatas.

## Kuis Pasca-Pelajaran

[Kuis Pasca-Pelajaran](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/40)

## Tinjauan & Studi Mandiri

* Pelajari lebih lanjut tentang cara merancang sistem deteksi stok ujung ke ujung dari [panduan pola deteksi stok habis di edge pada Microsoft Docs](https://docs.microsoft.com/hybrid/app-solutions/pattern-out-of-stock-at-edge?WT.mc_id=academic-17441-jabenn)
* Pelajari cara lain untuk membangun solusi ritel ujung ke ujung yang menggabungkan berbagai layanan IoT dan cloud dengan menonton [Behind the scenes of a retail solution - Hands On! video di YouTube](https://www.youtube.com/watch?v=m3Pc300x2Mw).

## Tugas

[Gunakan detektor objek Anda di edge](assignment.md)

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.