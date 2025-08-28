<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "8df310a42f902139a01417dacb1ffbef",
  "translation_date": "2025-08-28T00:56:53+00:00",
  "source_file": "5-retail/lessons/1-train-stock-detector/README.md",
  "language_code": "ms"
}
-->
# Latih Pengesan Stok

![Gambaran sketchnote untuk pelajaran ini](../../../../../translated_images/lesson-19.cf6973cecadf080c4b526310620dc4d6f5994c80fb0139c6f378cc9ca2d435cd.ms.jpg)

> Sketchnote oleh [Nitya Narasimhan](https://github.com/nitya). Klik imej untuk versi yang lebih besar.

Video ini memberikan gambaran tentang Pengesanan Objek menggunakan perkhidmatan Azure Custom Vision, yang akan dibincangkan dalam pelajaran ini.

[![Custom Vision 2 - Object Detection Made Easy | The Xamarin Show](https://img.youtube.com/vi/wtTYSyBUpFc/0.jpg)](https://www.youtube.com/watch?v=wtTYSyBUpFc)

> 🎥 Klik imej di atas untuk menonton video

## Kuiz sebelum kuliah

[Kuiz sebelum kuliah](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/37)

## Pengenalan

Dalam projek sebelumnya, anda menggunakan AI untuk melatih pengklasifikasi imej - model yang boleh menentukan sama ada imej mengandungi sesuatu, seperti buah yang masak atau tidak masak. Satu lagi jenis model AI yang boleh digunakan dengan imej ialah pengesanan objek. Model-model ini tidak mengklasifikasikan imej berdasarkan tag, sebaliknya mereka dilatih untuk mengenali objek dan boleh mencarinya dalam imej, bukan sahaja mengesan bahawa imej itu wujud, tetapi juga mengesan di mana objek itu berada dalam imej. Ini membolehkan anda mengira objek dalam imej.

Dalam pelajaran ini, anda akan belajar tentang pengesanan objek, termasuk bagaimana ia boleh digunakan dalam peruncitan. Anda juga akan belajar cara melatih pengesan objek di awan.

Dalam pelajaran ini, kita akan membincangkan:

* [Pengesanan objek](../../../../../5-retail/lessons/1-train-stock-detector)
* [Gunakan pengesanan objek dalam peruncitan](../../../../../5-retail/lessons/1-train-stock-detector)
* [Latih pengesan objek](../../../../../5-retail/lessons/1-train-stock-detector)
* [Uji pengesan objek anda](../../../../../5-retail/lessons/1-train-stock-detector)
* [Latih semula pengesan objek anda](../../../../../5-retail/lessons/1-train-stock-detector)

## Pengesanan objek

Pengesanan objek melibatkan pengesanan objek dalam imej menggunakan AI. Tidak seperti pengklasifikasi imej yang anda latih dalam projek terakhir, pengesanan objek bukan tentang meramalkan tag terbaik untuk keseluruhan imej, tetapi untuk mencari satu atau lebih objek dalam imej.

### Pengesanan objek vs pengklasifikasi imej

Pengklasifikasi imej adalah tentang mengklasifikasikan keseluruhan imej - apakah kebarangkalian bahawa keseluruhan imej sepadan dengan setiap tag. Anda akan menerima kebarangkalian untuk setiap tag yang digunakan untuk melatih model.

![Pengklasifikasi imej kacang gajus dan pes tomato](../../../../../translated_images/image-classifier-cashews-tomato.bc2e16ab8f05cf9ac0f59f73e32efc4227f9a5b601b90b2c60f436694547a965.ms.png)

Dalam contoh di atas, dua imej diklasifikasikan menggunakan model yang dilatih untuk mengklasifikasikan bekas kacang gajus atau tin pes tomato. Imej pertama adalah bekas kacang gajus, dan mempunyai dua hasil daripada pengklasifikasi imej:

| Tag            | Kebarangkalian |
| -------------- | -------------: |
| `kacang gajus` | 98.4%          |
| `pes tomato`   | 1.6%           |

Imej kedua adalah tin pes tomato, dan hasilnya adalah:

| Tag            | Kebarangkalian |
| -------------- | -------------: |
| `kacang gajus` | 0.7%           |
| `pes tomato`   | 99.3%          |

Anda boleh menggunakan nilai-nilai ini dengan peratusan ambang untuk meramalkan apa yang ada dalam imej. Tetapi bagaimana jika imej mengandungi beberapa tin pes tomato, atau kedua-dua kacang gajus dan pes tomato? Hasilnya mungkin tidak memberikan apa yang anda inginkan. Di sinilah pengesanan objek memainkan peranan.

Pengesanan objek melibatkan melatih model untuk mengenali objek. Daripada memberikan imej yang mengandungi objek dan memberitahu bahawa setiap imej adalah satu tag atau yang lain, anda menonjolkan bahagian imej yang mengandungi objek tertentu, dan menandainya. Anda boleh menandai satu objek dalam imej atau beberapa objek. Dengan cara ini, model belajar bagaimana rupa objek itu sendiri, bukan hanya bagaimana rupa imej yang mengandungi objek itu.

Apabila anda menggunakannya untuk meramalkan imej, bukannya menerima senarai tag dan peratusan, anda akan menerima senarai objek yang dikesan, dengan kotak sempadan dan kebarangkalian bahawa objek itu sepadan dengan tag yang diberikan.

> 🎓 *Kotak sempadan* adalah kotak di sekitar objek.

![Pengesanan objek kacang gajus dan pes tomato](../../../../../translated_images/object-detector-cashews-tomato.1af7c26686b4db0e709754aeb196f4e73271f54e2085db3bcccb70d4a0d84d97.ms.png)

Imej di atas mengandungi bekas kacang gajus dan tiga tin pes tomato. Pengesan objek mengesan kacang gajus, mengembalikan kotak sempadan yang mengandungi kacang gajus dengan kebarangkalian bahawa kotak sempadan mengandungi objek, dalam kes ini 97.6%. Pengesan objek juga mengesan tiga tin pes tomato, dan menyediakan tiga kotak sempadan berasingan, satu untuk setiap tin yang dikesan, dan setiap satu mempunyai kebarangkalian bahawa kotak sempadan mengandungi tin pes tomato.

✅ Fikirkan beberapa senario berbeza di mana anda mungkin ingin menggunakan model AI berasaskan imej. Mana yang memerlukan pengklasifikasi, dan mana yang memerlukan pengesanan objek?

### Bagaimana pengesanan objek berfungsi

Pengesanan objek menggunakan model ML yang kompleks. Model-model ini berfungsi dengan membahagikan imej kepada beberapa sel, kemudian memeriksa sama ada pusat kotak sempadan adalah pusat imej yang sepadan dengan salah satu imej yang digunakan untuk melatih model. Anda boleh menganggap ini seperti menjalankan pengklasifikasi imej ke atas bahagian-bahagian imej yang berbeza untuk mencari padanan.

> 💁 Ini adalah penyederhanaan yang sangat besar. Terdapat banyak teknik untuk pengesanan objek, dan anda boleh membaca lebih lanjut mengenainya di [halaman Pengesanan Objek di Wikipedia](https://wikipedia.org/wiki/Object_detection).

Terdapat beberapa model berbeza yang boleh melakukan pengesanan objek. Salah satu model yang terkenal ialah [YOLO (You only look once)](https://pjreddie.com/darknet/yolo/), yang sangat pantas dan boleh mengesan 20 kelas objek yang berbeza, seperti manusia, anjing, botol dan kereta.

✅ Baca tentang model YOLO di [pjreddie.com/darknet/yolo/](https://pjreddie.com/darknet/yolo/)

Model pengesanan objek boleh dilatih semula menggunakan pembelajaran pemindahan untuk mengesan objek tersuai.

## Gunakan pengesanan objek dalam peruncitan

Pengesanan objek mempunyai pelbagai kegunaan dalam peruncitan. Antaranya termasuk:

* **Pemeriksaan dan pengiraan stok** - mengenali apabila stok rendah di rak. Jika stok terlalu rendah, pemberitahuan boleh dihantar kepada kakitangan atau robot untuk mengisi semula rak.
* **Pengesanan pelitup muka** - di kedai dengan polisi pelitup muka semasa acara kesihatan awam, pengesanan objek boleh mengenali orang dengan pelitup muka dan tanpa pelitup muka.
* **Pengebilan automatik** - mengesan barang yang diambil dari rak di kedai automatik dan mengenakan bayaran kepada pelanggan dengan sewajarnya.
* **Pengesanan bahaya** - mengenali barang yang pecah di lantai, atau cecair yang tumpah, memberi amaran kepada kru pembersihan.

✅ Lakukan sedikit penyelidikan: Apakah beberapa lagi kegunaan pengesanan objek dalam peruncitan?

## Latih pengesan objek

Anda boleh melatih pengesan objek menggunakan Custom Vision, dengan cara yang serupa seperti anda melatih pengklasifikasi imej.

### Tugas - buat pengesan objek

1. Buat Kumpulan Sumber untuk projek ini yang dipanggil `stock-detector`

1. Buat sumber latihan Custom Vision percuma, dan sumber ramalan Custom Vision percuma dalam kumpulan sumber `stock-detector`. Namakan mereka `stock-detector-training` dan `stock-detector-prediction`.

    > 💁 Anda hanya boleh mempunyai satu sumber latihan dan ramalan percuma, jadi pastikan anda telah membersihkan projek anda dari pelajaran sebelumnya.

    > ⚠️ Anda boleh merujuk kepada [arahan untuk membuat sumber latihan dan ramalan dari projek 4, pelajaran 1 jika diperlukan](../../../4-manufacturing/lessons/1-train-fruit-detector/README.md#task---create-a-cognitive-services-resource).

1. Lancarkan portal Custom Vision di [CustomVision.ai](https://customvision.ai), dan log masuk dengan akaun Microsoft yang anda gunakan untuk akaun Azure anda.

1. Ikuti [Bahagian Buat Projek Baru dari panduan pantas Bangunkan pengesan objek di dokumen Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#create-a-new-project) untuk membuat projek Custom Vision baru. UI mungkin berubah dan dokumen ini sentiasa menjadi rujukan terkini.

    Namakan projek anda `stock-detector`.

    Apabila anda membuat projek anda, pastikan untuk menggunakan sumber `stock-detector-training` yang anda buat sebelum ini. Gunakan jenis projek *Object Detection*, dan domain *Products on Shelves*.

    ![Tetapan untuk projek Custom Vision dengan nama ditetapkan kepada fruit-quality-detector, tiada deskripsi, sumber ditetapkan kepada fruit-quality-detector-training, jenis projek ditetapkan kepada classification, jenis klasifikasi ditetapkan kepada multi class dan domain ditetapkan kepada food](../../../../../translated_images/custom-vision-create-object-detector-project.32d4fb9aa8e7e7375f8a799bfce517aca970f2cb65e42d4245c5e635c734ab29.ms.png)

    ✅ Domain produk di rak secara khusus disasarkan untuk mengesan stok di rak kedai. Baca lebih lanjut tentang domain yang berbeza dalam [Dokumentasi Pilih Domain di Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/select-domain?WT.mc_id=academic-17441-jabenn#object-detection)

✅ Luangkan masa untuk meneroka UI Custom Vision untuk pengesan objek anda.

### Tugas - latih pengesan objek anda

Untuk melatih model anda, anda memerlukan satu set imej yang mengandungi objek yang ingin anda kesan.

1. Kumpulkan imej yang mengandungi objek untuk dikesan. Anda memerlukan sekurang-kurangnya 15 imej yang mengandungi setiap objek untuk dikesan dari pelbagai sudut dan dalam keadaan pencahayaan yang berbeza, tetapi lebih banyak lebih baik. Pengesan objek ini menggunakan domain *Products on shelves*, jadi cuba susun objek seolah-olah mereka berada di rak kedai. Anda juga memerlukan beberapa imej untuk menguji model. Jika anda mengesan lebih daripada satu objek, anda akan memerlukan beberapa imej ujian yang mengandungi semua objek.

    > 💁 Imej dengan pelbagai objek yang berbeza dikira ke arah minimum 15 imej untuk semua objek dalam imej.

    Imej anda harus dalam format png atau jpeg, lebih kecil daripada 6MB. Jika anda menciptanya dengan iPhone sebagai contoh, mereka mungkin imej HEIC resolusi tinggi, jadi perlu ditukar dan mungkin dikecilkan. Lebih banyak imej lebih baik, dan anda harus mempunyai bilangan yang serupa untuk masak dan tidak masak.

    Model ini direka untuk produk di rak, jadi cuba ambil gambar objek di rak.

    Anda boleh mencari beberapa imej contoh yang boleh anda gunakan dalam folder [images](../../../../../5-retail/lessons/1-train-stock-detector/images) yang mengandungi kacang gajus dan pes tomato yang boleh anda gunakan.

1. Ikuti [Bahagian Muat Naik dan Tandai Imej dari panduan pantas Bangunkan pengesan objek di dokumen Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#upload-and-tag-images) untuk memuat naik imej latihan anda. Buat tag yang relevan bergantung pada jenis objek yang ingin anda kesan.

    ![Dialog muat naik menunjukkan muat naik gambar pisang masak dan tidak masak](../../../../../translated_images/image-upload-object-detector.77c7892c3093cb59b79018edecd678749a75d71a099bc8a2d2f2f76320f88a5b.ms.png)

    Apabila anda melukis kotak sempadan untuk objek, pastikan ia ketat di sekitar objek. Ia boleh mengambil masa untuk menggariskan semua imej, tetapi alat ini akan mengesan apa yang dianggap sebagai kotak sempadan, menjadikannya lebih cepat.

    ![Menandai pes tomato](../../../../../translated_images/object-detector-tag-tomato-paste.f47c362fb0f0eb582f3bc68cf3855fb43a805106395358d41896a269c210b7b4.ms.png)

    > 💁 Jika anda mempunyai lebih daripada 15 imej untuk setiap objek, anda boleh melatih selepas 15 kemudian menggunakan ciri **Suggested tags**. Ini akan menggunakan model yang dilatih untuk mengesan objek dalam imej yang tidak ditandai. Anda kemudian boleh mengesahkan objek yang dikesan, atau menolak dan melukis semula kotak sempadan. Ini boleh menjimatkan *banyak* masa.

1. Ikuti [Bahagian Latih Pengesan dari panduan pantas Bangunkan pengesan objek di dokumen Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#train-the-detector) untuk melatih pengesan objek pada imej yang ditandai.

    Anda akan diberikan pilihan jenis latihan. Pilih **Quick Training**.

Pengesan objek kemudian akan dilatih. Ia akan mengambil masa beberapa minit untuk latihan selesai.

## Uji pengesan objek anda

Setelah pengesan objek anda dilatih, anda boleh mengujinya dengan memberikan imej baru untuk mengesan objek di dalamnya.

### Tugas - uji pengesan objek anda

1. Gunakan butang **Quick Test** untuk memuat naik imej ujian dan mengesahkan objek yang dikesan. Gunakan imej ujian yang anda buat sebelum ini, bukan mana-mana imej yang anda gunakan untuk latihan.

    ![3 tin pes tomato dikesan dengan kebarangkalian 38%, 35.5% dan 34.6%](../../../../../translated_images/object-detector-detected-tomato-paste.52656fe87af4c37b4ee540526d63e73ed075da2e54a9a060aa528e0c562fb1b6.ms.png)

1. Cuba semua imej ujian yang anda ada dan perhatikan kebarangkalian.

## Latih semula pengesan objek anda

Apabila anda menguji pengesan objek anda, ia mungkin tidak memberikan hasil yang anda harapkan, sama seperti pengklasifikasi imej dalam projek sebelumnya. Anda boleh meningkatkan pengesan objek anda dengan melatih semula menggunakan imej yang salah.

Setiap kali anda membuat ramalan menggunakan pilihan ujian cepat, imej dan hasilnya disimpan. Anda boleh menggunakan imej-imej ini untuk melatih semula model anda.

1. Gunakan tab **Predictions** untuk mencari imej yang anda gunakan untuk ujian

1. Sahkan sebarang pengesanan yang tepat, hapuskan yang salah dan tambahkan objek yang hilang.

1. Latih semula dan uji semula model.

---

## 🚀 Cabaran

Apa yang akan berlaku jika anda menggunakan pengesan objek dengan barang yang kelihatan serupa, seperti tin pes tomato dan tin tomato cincang dari jenama yang sama?

Jika anda mempunyai barang yang kelihatan serupa, cuba uji dengan menambahkan imej mereka ke pengesan objek anda.

## Kuiz selepas kuliah
[Kuiz selepas kuliah](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/38)

## Ulang Kaji & Kajian Kendiri

* Semasa anda melatih pengesan objek anda, anda mungkin telah melihat nilai untuk *Precision*, *Recall*, dan *mAP* yang menilai model yang telah dicipta. Baca lebih lanjut tentang apa nilai-nilai ini menggunakan [bahagian Evaluate the detector dalam panduan Build an object detector quickstart di dokumen Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#evaluate-the-detector)
* Baca lebih lanjut tentang pengesanan objek di [halaman Object detection di Wikipedia](https://wikipedia.org/wiki/Object_detection)

## Tugasan

[Bandingkan domain](assignment.md)

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.