<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "8df310a42f902139a01417dacb1ffbef",
  "translation_date": "2025-08-27T20:47:33+00:00",
  "source_file": "5-retail/lessons/1-train-stock-detector/README.md",
  "language_code": "id"
}
-->
# Melatih Detektor Stok

![Ikhtisar sketchnote dari pelajaran ini](../../../../../translated_images/id/lesson-19.cf6973cecadf080c4b526310620dc4d6f5994c80fb0139c6f378cc9ca2d435cd.jpg)

> Sketchnote oleh [Nitya Narasimhan](https://github.com/nitya). Klik gambar untuk versi yang lebih besar.

Video ini memberikan gambaran tentang Deteksi Objek menggunakan layanan Azure Custom Vision, layanan yang akan dibahas dalam pelajaran ini.

[![Custom Vision 2 - Object Detection Made Easy | The Xamarin Show](https://img.youtube.com/vi/wtTYSyBUpFc/0.jpg)](https://www.youtube.com/watch?v=wtTYSyBUpFc)

> 🎥 Klik gambar di atas untuk menonton video

## Kuis sebelum pelajaran

[Kuis sebelum pelajaran](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/37)

## Pengantar

Dalam proyek sebelumnya, Anda menggunakan AI untuk melatih pengklasifikasi gambar - model yang dapat menentukan apakah sebuah gambar mengandung sesuatu, seperti buah matang atau buah yang belum matang. Jenis model AI lain yang dapat digunakan dengan gambar adalah deteksi objek. Model ini tidak mengklasifikasikan gambar berdasarkan tag, melainkan dilatih untuk mengenali objek, dan dapat menemukannya dalam gambar, tidak hanya mendeteksi bahwa gambar tersebut ada, tetapi juga mendeteksi di mana objek tersebut berada dalam gambar. Hal ini memungkinkan Anda untuk menghitung jumlah objek dalam gambar.

Dalam pelajaran ini, Anda akan mempelajari tentang deteksi objek, termasuk bagaimana hal itu dapat digunakan dalam ritel. Anda juga akan belajar cara melatih detektor objek di cloud.

Dalam pelajaran ini kita akan membahas:

* [Deteksi objek](../../../../../5-retail/lessons/1-train-stock-detector)
* [Menggunakan deteksi objek dalam ritel](../../../../../5-retail/lessons/1-train-stock-detector)
* [Melatih detektor objek](../../../../../5-retail/lessons/1-train-stock-detector)
* [Menguji detektor objek Anda](../../../../../5-retail/lessons/1-train-stock-detector)
* [Melatih ulang detektor objek Anda](../../../../../5-retail/lessons/1-train-stock-detector)

## Deteksi objek

Deteksi objek melibatkan pendeteksian objek dalam gambar menggunakan AI. Berbeda dengan pengklasifikasi gambar yang Anda latih dalam proyek terakhir, deteksi objek bukan tentang memprediksi tag terbaik untuk keseluruhan gambar, tetapi untuk menemukan satu atau lebih objek dalam gambar.

### Deteksi objek vs klasifikasi gambar

Klasifikasi gambar adalah tentang mengklasifikasikan keseluruhan gambar - apa probabilitas bahwa keseluruhan gambar cocok dengan setiap tag. Anda akan mendapatkan kembali probabilitas untuk setiap tag yang digunakan untuk melatih model.

![Klasifikasi gambar kacang mete dan pasta tomat](../../../../../translated_images/id/image-classifier-cashews-tomato.bc2e16ab8f05cf9ac0f59f73e32efc4227f9a5b601b90b2c60f436694547a965.png)

Dalam contoh di atas, dua gambar diklasifikasikan menggunakan model yang dilatih untuk mengklasifikasikan wadah kacang mete atau kaleng pasta tomat. Gambar pertama adalah wadah kacang mete, dan memiliki dua hasil dari pengklasifikasi gambar:

| Tag            | Probabilitas |
| -------------- | ----------: |
| `kacang mete`  | 98.4%       |
| `pasta tomat`  | 1.6%        |

Gambar kedua adalah kaleng pasta tomat, dan hasilnya adalah:

| Tag            | Probabilitas |
| -------------- | ----------: |
| `kacang mete`  | 0.7%        |
| `pasta tomat`  | 99.3%       |

Anda dapat menggunakan nilai-nilai ini dengan persentase ambang batas untuk memprediksi apa yang ada dalam gambar. Tetapi bagaimana jika sebuah gambar berisi beberapa kaleng pasta tomat, atau baik kacang mete maupun pasta tomat? Hasilnya mungkin tidak memberikan apa yang Anda inginkan. Di sinilah deteksi objek berperan.

Deteksi objek melibatkan pelatihan model untuk mengenali objek. Alih-alih memberikan gambar yang berisi objek dan memberitahunya bahwa setiap gambar adalah satu tag atau lainnya, Anda menyoroti bagian gambar yang berisi objek tertentu, dan memberi tag pada bagian tersebut. Anda dapat memberi tag pada satu objek dalam gambar atau beberapa objek. Dengan cara ini model belajar seperti apa objek itu sendiri, bukan hanya seperti apa gambar yang berisi objek tersebut.

Ketika Anda kemudian menggunakannya untuk memprediksi gambar, alih-alih mendapatkan kembali daftar tag dan persentase, Anda mendapatkan kembali daftar objek yang terdeteksi, dengan kotak pembatas dan probabilitas bahwa objek tersebut cocok dengan tag yang diberikan.

> 🎓 *Kotak pembatas* adalah kotak di sekitar objek.

![Deteksi objek kacang mete dan pasta tomat](../../../../../translated_images/id/object-detector-cashews-tomato.1af7c26686b4db0e709754aeb196f4e73271f54e2085db3bcccb70d4a0d84d97.png)

Gambar di atas berisi wadah kacang mete dan tiga kaleng pasta tomat. Detektor objek mendeteksi kacang mete, mengembalikan kotak pembatas yang berisi kacang mete dengan persentase kemungkinan bahwa kotak pembatas berisi objek, dalam hal ini 97.6%. Detektor objek juga mendeteksi tiga kaleng pasta tomat, dan memberikan tiga kotak pembatas terpisah, satu untuk setiap kaleng yang terdeteksi, dan masing-masing memiliki probabilitas persentase bahwa kotak pembatas berisi kaleng pasta tomat.

✅ Pikirkan beberapa skenario berbeda di mana Anda mungkin ingin menggunakan model AI berbasis gambar. Mana yang membutuhkan klasifikasi, dan mana yang membutuhkan deteksi objek?

### Bagaimana deteksi objek bekerja

Deteksi objek menggunakan model ML yang kompleks. Model ini bekerja dengan membagi gambar menjadi beberapa sel, lalu memeriksa apakah pusat kotak pembatas adalah pusat gambar yang cocok dengan salah satu gambar yang digunakan untuk melatih model. Anda dapat menganggap ini seperti menjalankan pengklasifikasi gambar di berbagai bagian gambar untuk mencari kecocokan.

> 💁 Ini adalah penyederhanaan yang sangat drastis. Ada banyak teknik untuk deteksi objek, dan Anda dapat membaca lebih lanjut tentangnya di [halaman Deteksi Objek di Wikipedia](https://wikipedia.org/wiki/Object_detection).

Ada sejumlah model berbeda yang dapat melakukan deteksi objek. Salah satu model yang terkenal adalah [YOLO (You only look once)](https://pjreddie.com/darknet/yolo/), yang sangat cepat dan dapat mendeteksi 20 kelas objek berbeda, seperti orang, anjing, botol, dan mobil.

✅ Baca lebih lanjut tentang model YOLO di [pjreddie.com/darknet/yolo/](https://pjreddie.com/darknet/yolo/)

Model deteksi objek dapat dilatih ulang menggunakan transfer learning untuk mendeteksi objek khusus.

## Menggunakan deteksi objek dalam ritel

Deteksi objek memiliki banyak kegunaan dalam ritel. Beberapa di antaranya termasuk:

* **Pemeriksaan dan penghitungan stok** - mengenali ketika stok rendah di rak. Jika stok terlalu rendah, notifikasi dapat dikirim ke staf atau robot untuk mengisi ulang rak.
* **Deteksi masker** - di toko dengan kebijakan masker selama acara kesehatan masyarakat, deteksi objek dapat mengenali orang dengan masker dan tanpa masker.
* **Penagihan otomatis** - mendeteksi barang yang diambil dari rak di toko otomatis dan menagih pelanggan dengan tepat.
* **Deteksi bahaya** - mengenali barang yang rusak di lantai, atau cairan yang tumpah, dan memberi tahu kru pembersih.

✅ Lakukan penelitian: Apa saja kegunaan lain dari deteksi objek dalam ritel?

## Melatih detektor objek

Anda dapat melatih detektor objek menggunakan Custom Vision, dengan cara yang mirip dengan bagaimana Anda melatih pengklasifikasi gambar.

### Tugas - membuat detektor objek

1. Buat Resource Group untuk proyek ini dengan nama `stock-detector`.

1. Buat sumber daya pelatihan Custom Vision gratis, dan sumber daya prediksi Custom Vision gratis di grup sumber daya `stock-detector`. Beri nama mereka `stock-detector-training` dan `stock-detector-prediction`.

    > 💁 Anda hanya dapat memiliki satu sumber daya pelatihan dan prediksi gratis, jadi pastikan Anda telah membersihkan proyek dari pelajaran sebelumnya.

    > ⚠️ Anda dapat merujuk ke [instruksi untuk membuat sumber daya pelatihan dan prediksi dari proyek 4, pelajaran 1 jika diperlukan](../../../4-manufacturing/lessons/1-train-fruit-detector/README.md#task---create-a-cognitive-services-resource).

1. Luncurkan portal Custom Vision di [CustomVision.ai](https://customvision.ai), dan masuk dengan akun Microsoft yang Anda gunakan untuk akun Azure Anda.

1. Ikuti [Bagian Buat Proyek Baru dari panduan cepat Membangun detektor objek di dokumen Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#create-a-new-project) untuk membuat proyek Custom Vision baru. UI dapat berubah dan dokumen ini selalu menjadi referensi yang paling mutakhir.

    Beri nama proyek Anda `stock-detector`.

    Saat Anda membuat proyek Anda, pastikan untuk menggunakan sumber daya `stock-detector-training` yang Anda buat sebelumnya. Gunakan tipe proyek *Object Detection*, dan domain *Products on Shelves*.

    ![Pengaturan untuk proyek Custom Vision dengan nama diatur ke fruit-quality-detector, tanpa deskripsi, sumber daya diatur ke fruit-quality-detector-training, tipe proyek diatur ke classification, tipe klasifikasi diatur ke multi class dan domain diatur ke food](../../../../../translated_images/id/custom-vision-create-object-detector-project.32d4fb9aa8e7e7375f8a799bfce517aca970f2cb65e42d4245c5e635c734ab29.png)

    ✅ Domain produk di rak secara khusus ditargetkan untuk mendeteksi stok di rak toko. Baca lebih lanjut tentang berbagai domain di [Dokumentasi Pilih Domain di Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/select-domain?WT.mc_id=academic-17441-jabenn#object-detection)

✅ Luangkan waktu untuk menjelajahi UI Custom Vision untuk detektor objek Anda.

### Tugas - melatih detektor objek Anda

Untuk melatih model Anda, Anda akan membutuhkan serangkaian gambar yang berisi objek yang ingin Anda deteksi.

1. Kumpulkan gambar yang berisi objek untuk dideteksi. Anda akan membutuhkan setidaknya 15 gambar yang berisi setiap objek untuk dideteksi dari berbagai sudut dan dalam kondisi pencahayaan yang berbeda, tetapi semakin banyak semakin baik. Detektor objek ini menggunakan domain *Products on shelves*, jadi cobalah untuk mengatur objek seolah-olah mereka berada di rak toko. Anda juga akan membutuhkan beberapa gambar untuk menguji model. Jika Anda mendeteksi lebih dari satu objek, Anda akan membutuhkan beberapa gambar pengujian yang berisi semua objek.

    > 💁 Gambar dengan beberapa objek berbeda dihitung terhadap minimum 15 gambar untuk semua objek dalam gambar.

    Gambar Anda harus berupa png atau jpeg, lebih kecil dari 6MB. Jika Anda membuatnya dengan iPhone misalnya, mereka mungkin berupa gambar HEIC resolusi tinggi, jadi perlu dikonversi dan mungkin diperkecil. Semakin banyak gambar semakin baik, dan Anda harus memiliki jumlah yang serupa untuk objek matang dan belum matang.

    Model ini dirancang untuk produk di rak, jadi cobalah untuk mengambil foto objek di rak.

    Anda dapat menemukan beberapa gambar contoh yang dapat Anda gunakan di folder [images](../../../../../5-retail/lessons/1-train-stock-detector/images) dari kacang mete dan pasta tomat yang dapat Anda gunakan.

1. Ikuti [Bagian Unggah dan beri tag gambar dari panduan cepat Membangun detektor objek di dokumen Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#upload-and-tag-images) untuk mengunggah gambar pelatihan Anda. Buat tag yang relevan tergantung pada jenis objek yang ingin Anda deteksi.

    ![Dialog unggahan menunjukkan unggahan gambar pisang matang dan belum matang](../../../../../translated_images/id/image-upload-object-detector.77c7892c3093cb59b79018edecd678749a75d71a099bc8a2d2f2f76320f88a5b.png)

    Saat Anda menggambar kotak pembatas untuk objek, buatlah kotak tersebut pas di sekitar objek. Mungkin membutuhkan waktu untuk menggambar semua gambar, tetapi alat ini akan mendeteksi apa yang dianggap sebagai kotak pembatas, membuatnya lebih cepat.

    ![Memberi tag pada beberapa pasta tomat](../../../../../translated_images/id/object-detector-tag-tomato-paste.f47c362fb0f0eb582f3bc68cf3855fb43a805106395358d41896a269c210b7b4.png)

    > 💁 Jika Anda memiliki lebih dari 15 gambar untuk setiap objek, Anda dapat melatih setelah 15 gambar lalu menggunakan fitur **Suggested tags**. Fitur ini akan menggunakan model yang dilatih untuk mendeteksi objek dalam gambar yang belum diberi tag. Anda kemudian dapat mengonfirmasi objek yang terdeteksi, atau menolak dan menggambar ulang kotak pembatas. Ini dapat menghemat *banyak* waktu.

1. Ikuti [Bagian Latih detektor dari panduan cepat Membangun detektor objek di dokumen Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#train-the-detector) untuk melatih detektor objek pada gambar yang telah diberi tag.

    Anda akan diberikan pilihan jenis pelatihan. Pilih **Quick Training**.

Detektor objek kemudian akan dilatih. Pelatihan akan memakan waktu beberapa menit untuk selesai.

## Menguji detektor objek Anda

Setelah detektor objek Anda dilatih, Anda dapat mengujinya dengan memberikan gambar baru untuk mendeteksi objek di dalamnya.

### Tugas - menguji detektor objek Anda

1. Gunakan tombol **Quick Test** untuk mengunggah gambar pengujian dan memverifikasi objek yang terdeteksi. Gunakan gambar pengujian yang Anda buat sebelumnya, bukan gambar yang Anda gunakan untuk pelatihan.

    ![3 kaleng pasta tomat terdeteksi dengan probabilitas 38%, 35.5%, dan 34.6%](../../../../../translated_images/id/object-detector-detected-tomato-paste.52656fe87af4c37b4ee540526d63e73ed075da2e54a9a060aa528e0c562fb1b6.png)

1. Cobalah semua gambar pengujian yang Anda miliki dan amati probabilitasnya.

## Melatih ulang detektor objek Anda

Ketika Anda menguji detektor objek Anda, mungkin hasilnya tidak sesuai dengan yang Anda harapkan, sama seperti dengan pengklasifikasi gambar dalam proyek sebelumnya. Anda dapat meningkatkan detektor objek Anda dengan melatih ulang menggunakan gambar yang salah.

Setiap kali Anda membuat prediksi menggunakan opsi pengujian cepat, gambar dan hasilnya disimpan. Anda dapat menggunakan gambar-gambar ini untuk melatih ulang model Anda.

1. Gunakan tab **Predictions** untuk menemukan gambar yang Anda gunakan untuk pengujian.

1. Konfirmasi deteksi yang akurat, hapus yang salah, dan tambahkan objek yang hilang.

1. Latih ulang dan uji kembali model.

---

## 🚀 Tantangan

Apa yang akan terjadi jika Anda menggunakan detektor objek dengan barang yang terlihat mirip, seperti kaleng pasta tomat dan tomat cincang dari merek yang sama?

Jika Anda memiliki barang yang terlihat mirip, cobalah dengan menambahkan gambar mereka ke detektor objek Anda.

## Kuis setelah pelajaran
[Quiz setelah kuliah](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/38)

## Tinjauan & Belajar Mandiri

* Ketika Anda melatih pendeteksi objek Anda, Anda akan melihat nilai *Precision*, *Recall*, dan *mAP* yang menilai model yang telah dibuat. Pelajari lebih lanjut tentang apa arti nilai-nilai ini dengan membaca [bagian Evaluasi pendeteksi pada panduan cepat Membangun pendeteksi objek di dokumen Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#evaluate-the-detector)
* Baca lebih lanjut tentang deteksi objek di [halaman Deteksi objek di Wikipedia](https://wikipedia.org/wiki/Object_detection)

## Tugas

[Bandingkan domain](assignment.md)

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.