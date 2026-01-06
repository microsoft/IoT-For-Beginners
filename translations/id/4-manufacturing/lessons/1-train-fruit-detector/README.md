<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f5e63c916d2dd97d58be12aaf76bd9f1",
  "translation_date": "2025-08-27T20:52:13+00:00",
  "source_file": "4-manufacturing/lessons/1-train-fruit-detector/README.md",
  "language_code": "id"
}
-->
# Melatih Detektor Kualitas Buah

![Gambaran sketchnote dari pelajaran ini](../../../../../translated_images/lesson-15.843d21afdc6fb2bba70cd9db7b7d2f91598859fafda2078b0bdc44954194b6c0.id.jpg)

> Sketchnote oleh [Nitya Narasimhan](https://github.com/nitya). Klik gambar untuk versi yang lebih besar.

Video ini memberikan gambaran tentang layanan Azure Custom Vision, sebuah layanan yang akan dibahas dalam pelajaran ini.

[![Custom Vision – Machine Learning Made Easy | The Xamarin Show](https://img.youtube.com/vi/TETcDLJlWR4/0.jpg)](https://www.youtube.com/watch?v=TETcDLJlWR4)

> 🎥 Klik gambar di atas untuk menonton video

## Kuis sebelum pelajaran

[Kuis sebelum pelajaran](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/29)

## Pendahuluan

Kenaikan terbaru dalam Kecerdasan Buatan (AI) dan Pembelajaran Mesin (ML) memberikan berbagai kemampuan kepada pengembang masa kini. Model ML dapat dilatih untuk mengenali berbagai hal dalam gambar, termasuk buah yang belum matang, dan ini dapat digunakan dalam perangkat IoT untuk membantu menyortir hasil panen baik saat dipanen maupun selama pemrosesan di pabrik atau gudang.

Dalam pelajaran ini, Anda akan belajar tentang klasifikasi gambar - menggunakan model ML untuk membedakan antara gambar dari berbagai objek. Anda akan belajar cara melatih pengklasifikasi gambar untuk membedakan antara buah yang baik dan buah yang buruk, baik yang terlalu matang, memar, atau busuk.

Dalam pelajaran ini kita akan membahas:

* [Menggunakan AI dan ML untuk menyortir makanan](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Klasifikasi gambar melalui Pembelajaran Mesin](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Melatih pengklasifikasi gambar](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Menguji pengklasifikasi gambar Anda](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Melatih ulang pengklasifikasi gambar Anda](../../../../../4-manufacturing/lessons/1-train-fruit-detector)

## Menggunakan AI dan ML untuk menyortir makanan

Memberi makan populasi global adalah tantangan besar, terutama dengan harga yang membuat makanan terjangkau untuk semua. Salah satu biaya terbesar adalah tenaga kerja, sehingga petani semakin beralih ke otomatisasi dan alat seperti IoT untuk mengurangi biaya tenaga kerja mereka. Memanen secara manual sangat intensif tenaga kerja (dan sering kali melelahkan), dan digantikan oleh mesin, terutama di negara-negara kaya. Meskipun biaya memanen menggunakan mesin lebih murah, ada kelemahan - kemampuan untuk menyortir makanan saat dipanen.

Tidak semua tanaman matang secara merata. Tomat, misalnya, masih bisa memiliki beberapa buah hijau di pohon ketika sebagian besar sudah siap dipanen. Meskipun memanen buah yang belum matang adalah pemborosan, lebih murah dan lebih mudah bagi petani untuk memanen semuanya menggunakan mesin dan membuang hasil panen yang belum matang nanti.

✅ Lihatlah berbagai buah atau sayuran, baik yang tumbuh di dekat Anda di ladang atau di kebun Anda, atau di toko. Apakah semuanya memiliki tingkat kematangan yang sama, atau apakah Anda melihat variasi?

Kenaikan penggunaan mesin panen otomatis memindahkan proses penyortiran hasil panen dari ladang ke pabrik. Makanan akan bergerak di atas sabuk konveyor panjang dengan tim orang yang memeriksa hasil panen dan menghapus apa pun yang tidak memenuhi standar kualitas yang diperlukan. Memanen menjadi lebih murah berkat mesin, tetapi masih ada biaya untuk menyortir makanan secara manual.

![Jika tomat merah terdeteksi, ia melanjutkan perjalanannya tanpa gangguan. Jika tomat hijau terdeteksi, ia dilempar ke tempat sampah oleh tuas](../../../../../translated_images/optical-tomato-sorting.61aa134bdda4e5b1bfb16a212c1e35a6ef0c426cbb8b1c975f79d7bfbf48d068.id.png)

Evolusi berikutnya adalah menggunakan mesin untuk menyortir, baik yang terintegrasi dalam mesin panen, atau di pabrik pengolahan. Generasi pertama dari mesin ini menggunakan sensor optik untuk mendeteksi warna, mengontrol aktuator untuk mendorong tomat hijau ke tempat sampah menggunakan tuas atau semburan udara, meninggalkan tomat merah untuk melanjutkan perjalanan di jaringan sabuk konveyor.

Dalam video ini, saat tomat jatuh dari satu sabuk konveyor ke sabuk lainnya, tomat hijau terdeteksi dan dilempar ke tempat sampah menggunakan tuas.

✅ Kondisi apa yang Anda perlukan di pabrik atau di ladang agar sensor optik ini berfungsi dengan baik?

Evolusi terbaru dari mesin penyortir ini memanfaatkan AI dan ML, menggunakan model yang dilatih untuk membedakan hasil panen yang baik dari yang buruk, tidak hanya berdasarkan perbedaan warna yang jelas seperti tomat hijau vs merah, tetapi juga berdasarkan perbedaan penampilan yang lebih halus yang dapat menunjukkan penyakit atau memar.

## Klasifikasi gambar melalui Pembelajaran Mesin

Pemrograman tradisional adalah ketika Anda mengambil data, menerapkan algoritma ke data, dan mendapatkan output. Misalnya, dalam proyek terakhir Anda mengambil koordinat GPS dan geofence, menerapkan algoritma yang disediakan oleh Azure Maps, dan mendapatkan hasil apakah titik tersebut berada di dalam atau di luar geofence. Anda memasukkan lebih banyak data, Anda mendapatkan lebih banyak output.

![Pengembangan tradisional mengambil input dan algoritma dan memberikan output. Pembelajaran mesin menggunakan data input dan output untuk melatih model, dan model ini dapat mengambil data input baru untuk menghasilkan output baru](../../../../../translated_images/traditional-vs-ml.5c20c169621fa539.id.png)

Pembelajaran mesin membalikkan proses ini - Anda memulai dengan data dan output yang diketahui, dan algoritma pembelajaran mesin belajar dari data tersebut. Anda kemudian dapat mengambil algoritma yang telah dilatih, yang disebut *model pembelajaran mesin* atau *model*, dan memasukkan data baru untuk mendapatkan output baru.

> 🎓 Proses algoritma pembelajaran mesin belajar dari data disebut *pelatihan*. Input dan output yang diketahui disebut *data pelatihan*.

Misalnya, Anda dapat memberikan model jutaan gambar pisang yang belum matang sebagai data pelatihan input, dengan output pelatihan diatur sebagai `belum matang`, dan jutaan gambar pisang matang sebagai data pelatihan dengan output diatur sebagai `matang`. Algoritma ML kemudian akan membuat model berdasarkan data ini. Anda kemudian memberikan model ini gambar baru dari pisang dan model akan memprediksi apakah gambar baru tersebut adalah pisang matang atau belum matang.

> 🎓 Hasil dari model ML disebut *prediksi*

![2 pisang, satu matang dengan prediksi 99.7% matang, 0.3% belum matang, dan satu belum matang dengan prediksi 1.4% matang, 98.6% belum matang](../../../../../translated_images/bananas-ripe-vs-unripe-predictions.8d0e2034014aa50ece4e4589e724b142da0681f35470fe3db3f7d51240f69c85.id.png)

Model ML tidak memberikan jawaban biner, melainkan memberikan probabilitas. Misalnya, sebuah model dapat diberikan gambar pisang dan memprediksi `matang` dengan probabilitas 99.7% dan `belum matang` dengan probabilitas 0.3%. Kode Anda kemudian akan memilih prediksi terbaik dan memutuskan bahwa pisang tersebut matang.

Model ML yang digunakan untuk mendeteksi gambar seperti ini disebut *pengklasifikasi gambar* - model ini diberikan gambar yang diberi label, dan kemudian mengklasifikasikan gambar baru berdasarkan label tersebut.

> 💁 Ini adalah penyederhanaan, dan ada banyak cara lain untuk melatih model yang tidak selalu membutuhkan output yang diberi label, seperti pembelajaran tanpa pengawasan. Jika Anda ingin belajar lebih banyak tentang ML, lihat [ML untuk pemula, kurikulum 24 pelajaran tentang Pembelajaran Mesin](https://aka.ms/ML-beginners).

## Melatih pengklasifikasi gambar

Untuk melatih pengklasifikasi gambar dengan sukses, Anda membutuhkan jutaan gambar. Ternyata, setelah Anda memiliki pengklasifikasi gambar yang dilatih dengan jutaan atau miliaran gambar beragam, Anda dapat menggunakannya kembali dan melatih ulang menggunakan sejumlah kecil gambar dan mendapatkan hasil yang baik, menggunakan proses yang disebut *transfer learning*.

> 🎓 Transfer learning adalah proses mentransfer pembelajaran dari model ML yang ada ke model baru berdasarkan data baru.

Setelah pengklasifikasi gambar dilatih untuk berbagai macam gambar, bagian internalnya sangat baik dalam mengenali bentuk, warna, dan pola. Transfer learning memungkinkan model untuk menggunakan apa yang telah dipelajari dalam mengenali bagian gambar, dan menggunakannya untuk mengenali gambar baru.

![Setelah Anda dapat mengenali bentuk, bentuk tersebut dapat disusun dalam konfigurasi berbeda untuk membuat perahu atau kucing](../../../../../translated_images/shapes-to-images.1a309f0ea88dd66f.id.png)

Anda dapat menganggap ini seperti buku bentuk anak-anak, di mana setelah Anda dapat mengenali setengah lingkaran, persegi panjang, dan segitiga, Anda dapat mengenali perahu layar atau kucing tergantung pada konfigurasi bentuk-bentuk tersebut. Pengklasifikasi gambar dapat mengenali bentuk-bentuk tersebut, dan transfer learning mengajarkannya kombinasi apa yang membuat perahu atau kucing - atau pisang matang.

Ada berbagai alat yang dapat membantu Anda melakukan ini, termasuk layanan berbasis cloud yang dapat membantu Anda melatih model Anda, lalu menggunakannya melalui API web.

> 💁 Melatih model ini membutuhkan banyak daya komputer, biasanya melalui Graphics Processing Units, atau GPU. Perangkat keras khusus yang sama yang membuat game di Xbox Anda terlihat luar biasa juga dapat digunakan untuk melatih model pembelajaran mesin. Dengan menggunakan cloud, Anda dapat menyewa waktu di komputer yang kuat dengan GPU untuk melatih model ini, mendapatkan akses ke daya komputasi yang Anda butuhkan, hanya untuk waktu yang Anda perlukan.

## Custom Vision

Custom Vision adalah alat berbasis cloud untuk melatih pengklasifikasi gambar. Alat ini memungkinkan Anda melatih pengklasifikasi hanya dengan sejumlah kecil gambar. Anda dapat mengunggah gambar melalui portal web, API web, atau SDK, memberikan setiap gambar *tag* yang merupakan klasifikasi dari gambar tersebut. Anda kemudian melatih model, dan mengujinya untuk melihat seberapa baik kinerjanya. Setelah Anda puas dengan model tersebut, Anda dapat mempublikasikan versi yang dapat diakses melalui API web atau SDK.

![Logo Azure Custom Vision](../../../../../translated_images/custom-vision-logo.d3d4e7c8a87ec9daf825e72e210576c3cbf60312577be7a139e22dd97ab7f1e6.id.png)

> 💁 Anda dapat melatih model Custom Vision dengan hanya 5 gambar per klasifikasi, tetapi lebih banyak lebih baik. Anda dapat mendapatkan hasil yang lebih baik dengan setidaknya 30 gambar.

Custom Vision adalah bagian dari rangkaian alat AI dari Microsoft yang disebut Cognitive Services. Ini adalah alat AI yang dapat digunakan baik tanpa pelatihan apa pun, atau dengan sedikit pelatihan. Alat ini mencakup pengenalan dan terjemahan suara, pemahaman bahasa, dan analisis gambar. Alat ini tersedia dengan tingkat gratis sebagai layanan di Azure.

> 💁 Tingkat gratis lebih dari cukup untuk membuat model, melatihnya, lalu menggunakannya untuk pekerjaan pengembangan. Anda dapat membaca tentang batasan tingkat gratis di [Halaman Batas dan Kuota Custom Vision di dokumen Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/limits-and-quotas?WT.mc_id=academic-17441-jabenn).

### Tugas - membuat sumber daya cognitive services

Untuk menggunakan Custom Vision, Anda pertama-tama perlu membuat dua sumber daya cognitive services di Azure menggunakan Azure CLI, satu untuk pelatihan Custom Vision dan satu untuk prediksi Custom Vision.

1. Buat Resource Group untuk proyek ini bernama `fruit-quality-detector`.

1. Gunakan perintah berikut untuk membuat sumber daya pelatihan Custom Vision gratis:

    ```sh
    az cognitiveservices account create --name fruit-quality-detector-training \
                                        --resource-group fruit-quality-detector \
                                        --kind CustomVision.Training \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Ganti `<location>` dengan lokasi yang Anda gunakan saat membuat Resource Group.

    Ini akan membuat sumber daya pelatihan Custom Vision di Resource Group Anda. Sumber daya ini akan disebut `fruit-quality-detector-training` dan menggunakan sku `F0`, yang merupakan tingkat gratis. Opsi `--yes` berarti Anda menyetujui syarat dan ketentuan cognitive services.

> 💁 Gunakan sku `S0` jika Anda sudah memiliki akun gratis yang menggunakan salah satu Cognitive Services.

1. Gunakan perintah berikut untuk membuat sumber daya prediksi Custom Vision gratis:

    ```sh
    az cognitiveservices account create --name fruit-quality-detector-prediction \
                                        --resource-group fruit-quality-detector \
                                        --kind CustomVision.Prediction \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Ganti `<location>` dengan lokasi yang Anda gunakan saat membuat Resource Group.

    Ini akan membuat sumber daya prediksi Custom Vision di Resource Group Anda. Sumber daya ini akan disebut `fruit-quality-detector-prediction` dan menggunakan sku `F0`, yang merupakan tingkat gratis. Opsi `--yes` berarti Anda menyetujui syarat dan ketentuan cognitive services.

### Tugas - membuat proyek pengklasifikasi gambar

1. Luncurkan portal Custom Vision di [CustomVision.ai](https://customvision.ai), dan masuk dengan akun Microsoft yang Anda gunakan untuk akun Azure Anda.

1. Ikuti [bagian membuat proyek baru dari panduan cepat membangun pengklasifikasi di dokumen Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#create-a-new-project) untuk membuat proyek Custom Vision baru. UI mungkin berubah dan dokumen ini selalu menjadi referensi yang paling mutakhir.

    Beri nama proyek Anda `fruit-quality-detector`.

    Saat Anda membuat proyek Anda, pastikan untuk menggunakan sumber daya `fruit-quality-detector-training` yang Anda buat sebelumnya. Gunakan tipe proyek *Classification*, tipe klasifikasi *Multiclass*, dan domain *Food*.

    ![Pengaturan untuk proyek Custom Vision dengan nama diatur ke fruit-quality-detector, tanpa deskripsi, sumber daya diatur ke fruit-quality-detector-training, tipe proyek diatur ke classification, tipe klasifikasi diatur ke multi class dan domain diatur ke food](../../../../../translated_images/custom-vision-create-project.cf46325b92d8b131089f6647cf5e07b664cb77850e106d66e3c057b6b69756c6.id.png)

✅ Luangkan waktu untuk menjelajahi UI Custom Vision untuk pengklasifikasi gambar Anda.

### Tugas - melatih proyek pengklasifikasi gambar Anda

Untuk melatih pengklasifikasi gambar, Anda akan membutuhkan beberapa gambar buah, baik yang berkualitas baik maupun buruk untuk diberi tag sebagai baik dan buruk, seperti pisang matang dan pisang terlalu matang.
💁 Pengklasifikasi ini dapat mengklasifikasikan gambar apa saja, jadi jika Anda tidak memiliki buah dengan kualitas berbeda, Anda bisa menggunakan dua jenis buah yang berbeda, atau kucing dan anjing!
Setiap gambar idealnya hanya menampilkan buahnya saja, dengan latar belakang yang konsisten atau beragam. Pastikan tidak ada elemen di latar belakang yang menunjukkan perbedaan antara buah matang dan tidak matang.

> 💁 Penting untuk tidak memiliki latar belakang spesifik atau elemen yang tidak terkait dengan objek yang diklasifikasikan untuk setiap label. Jika tidak, pengklasifikasi mungkin hanya mengklasifikasikan berdasarkan latar belakang. Ada sebuah pengklasifikasi untuk kanker kulit yang dilatih menggunakan gambar tahi lalat normal dan kanker, di mana gambar tahi lalat kanker selalu memiliki penggaris untuk mengukur ukurannya. Ternyata pengklasifikasi tersebut hampir 100% akurat dalam mengenali penggaris di gambar, bukan tahi lalat kanker.

Pengklasifikasi gambar bekerja pada resolusi yang sangat rendah. Misalnya, Custom Vision dapat menerima gambar pelatihan dan prediksi hingga 10240x10240, tetapi melatih dan menjalankan model pada gambar berukuran 227x227. Gambar yang lebih besar akan diperkecil ke ukuran ini, jadi pastikan objek yang Anda klasifikasikan memenuhi sebagian besar gambar. Jika tidak, objek tersebut mungkin terlalu kecil dalam gambar yang digunakan oleh pengklasifikasi.

1. Kumpulkan gambar untuk pengklasifikasi Anda. Anda memerlukan setidaknya 5 gambar untuk setiap label untuk melatih pengklasifikasi, tetapi semakin banyak semakin baik. Anda juga memerlukan beberapa gambar tambahan untuk menguji pengklasifikasi. Gambar-gambar ini harus merupakan gambar yang berbeda dari objek yang sama. Contohnya:

    * Gunakan 2 pisang matang, ambil beberapa gambar dari masing-masing pisang dari berbagai sudut, setidaknya 7 gambar (5 untuk pelatihan, 2 untuk pengujian), tetapi idealnya lebih banyak.

        ![Foto 2 pisang yang berbeda](../../../../../translated_images/banana-training-images.530eb203346d73bc23b8b990fb4609470bf4ff7c942ccc13d4cfffeed9be1ad4.id.png)

    * Ulangi proses yang sama menggunakan 2 pisang yang belum matang.

    Anda harus memiliki setidaknya 10 gambar pelatihan, dengan setidaknya 5 pisang matang dan 5 pisang belum matang, serta 4 gambar pengujian, 2 pisang matang, 2 pisang belum matang. Gambar Anda harus berupa png atau jpeg, dengan ukuran kurang dari 6MB. Jika Anda membuatnya menggunakan iPhone, misalnya, gambar tersebut mungkin berupa gambar HEIC beresolusi tinggi, sehingga perlu dikonversi dan mungkin diperkecil. Semakin banyak gambar semakin baik, dan Anda harus memiliki jumlah gambar matang dan belum matang yang serupa.

    Jika Anda tidak memiliki buah matang dan belum matang, Anda dapat menggunakan buah yang berbeda, atau objek lain yang tersedia. Anda juga dapat menemukan beberapa gambar contoh di folder [images](../../../../../4-manufacturing/lessons/1-train-fruit-detector/images) berupa pisang matang dan belum matang yang dapat Anda gunakan.

1. Ikuti [bagian unggah dan beri label gambar dari panduan cepat membangun pengklasifikasi di Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#upload-and-tag-images) untuk mengunggah gambar pelatihan Anda. Beri label buah matang sebagai `ripe`, dan buah belum matang sebagai `unripe`.

    ![Dialog unggah yang menunjukkan pengunggahan gambar pisang matang dan belum matang](../../../../../translated_images/image-upload-bananas.0751639f3815e0ec42bdbc6254d1e4357a185834d1ae10c9948a0e7d6d336695.id.png)

1. Ikuti [bagian latih pengklasifikasi dari panduan cepat membangun pengklasifikasi di Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#train-the-classifier) untuk melatih pengklasifikasi gambar menggunakan gambar yang telah Anda unggah.

    Anda akan diberikan pilihan jenis pelatihan. Pilih **Quick Training**.

Pengklasifikasi kemudian akan dilatih. Proses pelatihan akan memakan waktu beberapa menit.

> 🍌 Jika Anda memutuskan untuk memakan buah Anda saat pengklasifikasi sedang dilatih, pastikan Anda memiliki cukup gambar untuk pengujian terlebih dahulu!

## Uji pengklasifikasi gambar Anda

Setelah pengklasifikasi Anda dilatih, Anda dapat mengujinya dengan memberikan gambar baru untuk diklasifikasikan.

### Tugas - uji pengklasifikasi gambar Anda

1. Ikuti [dokumentasi uji model Anda di Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/test-your-model?WT.mc_id=academic-17441-jabenn#test-your-model) untuk menguji pengklasifikasi gambar Anda. Gunakan gambar pengujian yang telah Anda buat sebelumnya, bukan gambar yang digunakan untuk pelatihan.

    ![Pisang belum matang diprediksi sebagai belum matang dengan probabilitas 98.9%, matang dengan probabilitas 1.1%](../../../../../translated_images/banana-unripe-quick-test-prediction.dae9b5e1c4ef7c64886422438850ea14f0be6ac918c217ea3b255c685abfabe7.id.png)

1. Coba semua gambar pengujian yang Anda miliki dan amati probabilitasnya.

## Latih ulang pengklasifikasi gambar Anda

Ketika Anda menguji pengklasifikasi Anda, hasilnya mungkin tidak sesuai dengan yang Anda harapkan. Pengklasifikasi gambar menggunakan pembelajaran mesin untuk membuat prediksi tentang apa yang ada dalam gambar, berdasarkan probabilitas bahwa fitur tertentu dari gambar tersebut cocok dengan label tertentu. Pengklasifikasi tidak memahami apa yang ada dalam gambar - ia tidak tahu apa itu pisang atau memahami apa yang membuat pisang menjadi pisang, bukan perahu. Anda dapat meningkatkan pengklasifikasi Anda dengan melatih ulang menggunakan gambar yang salah diklasifikasikan.

Setiap kali Anda membuat prediksi menggunakan opsi uji cepat, gambar dan hasilnya akan disimpan. Anda dapat menggunakan gambar-gambar ini untuk melatih ulang model Anda.

### Tugas - latih ulang pengklasifikasi gambar Anda

1. Ikuti [dokumentasi gunakan gambar yang diprediksi untuk pelatihan di Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/test-your-model?WT.mc_id=academic-17441-jabenn#use-the-predicted-image-for-training) untuk melatih ulang model Anda, menggunakan label yang benar untuk setiap gambar.

1. Setelah model Anda dilatih ulang, uji dengan gambar baru.

---

## 🚀 Tantangan

Apa yang Anda pikirkan jika Anda menggunakan gambar stroberi dengan model yang dilatih untuk pisang, atau gambar pisang tiup, atau seseorang yang mengenakan kostum pisang, atau bahkan karakter kartun kuning seperti seseorang dari Simpsons?

Cobalah dan lihat apa prediksinya. Anda dapat menemukan gambar untuk dicoba menggunakan [Pencarian Gambar Bing](https://www.bing.com/images/trending).

## Kuis setelah kuliah

[Kuis setelah kuliah](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/30)

## Tinjauan & Studi Mandiri

* Ketika Anda melatih pengklasifikasi Anda, Anda akan melihat nilai untuk *Precision*, *Recall*, dan *AP* yang menilai model yang dibuat. Bacalah tentang apa arti nilai-nilai ini menggunakan [bagian evaluasi pengklasifikasi dari panduan cepat membangun pengklasifikasi di Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#evaluate-the-classifier)
* Bacalah tentang cara meningkatkan pengklasifikasi Anda dari [cara meningkatkan model Custom Vision Anda di Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-improving-your-classifier?WT.mc_id=academic-17441-jabenn)

## Tugas

[Latih pengklasifikasi Anda untuk berbagai buah dan sayuran](assignment.md)

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.