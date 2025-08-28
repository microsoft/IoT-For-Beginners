<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f5e63c916d2dd97d58be12aaf76bd9f1",
  "translation_date": "2025-08-27T22:40:11+00:00",
  "source_file": "4-manufacturing/lessons/1-train-fruit-detector/README.md",
  "language_code": "ms"
}
-->
# Melatih Pengesan Kualiti Buah

![Gambaran sketchnote untuk pelajaran ini](../../../../../translated_images/lesson-15.843d21afdc6fb2bba70cd9db7b7d2f91598859fafda2078b0bdc44954194b6c0.ms.jpg)

> Sketchnote oleh [Nitya Narasimhan](https://github.com/nitya). Klik gambar untuk versi yang lebih besar.

Video ini memberikan gambaran keseluruhan tentang perkhidmatan Azure Custom Vision, yang akan dibincangkan dalam pelajaran ini.

[![Custom Vision – Pembelajaran Mesin Jadi Mudah | The Xamarin Show](https://img.youtube.com/vi/TETcDLJlWR4/0.jpg)](https://www.youtube.com/watch?v=TETcDLJlWR4)

> 🎥 Klik gambar di atas untuk menonton video

## Kuiz Sebelum Pelajaran

[Kuiz Sebelum Pelajaran](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/29)

## Pengenalan

Kebangkitan terkini dalam Kecerdasan Buatan (AI) dan Pembelajaran Mesin (ML) memberikan pelbagai keupayaan kepada pembangun masa kini. Model ML boleh dilatih untuk mengenali pelbagai perkara dalam imej, termasuk buah yang belum masak, dan ini boleh digunakan dalam peranti IoT untuk membantu menyusun hasil sama ada semasa penuaian atau semasa pemprosesan di kilang atau gudang.

Dalam pelajaran ini, anda akan mempelajari tentang klasifikasi imej - menggunakan model ML untuk membezakan antara imej pelbagai perkara. Anda akan belajar bagaimana melatih pengklasifikasi imej untuk membezakan antara buah yang baik dan buah yang buruk, sama ada terlalu masak, lebam, atau busuk.

Dalam pelajaran ini, kita akan membincangkan:

* [Menggunakan AI dan ML untuk menyusun makanan](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Klasifikasi imej melalui Pembelajaran Mesin](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Melatih pengklasifikasi imej](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Menguji pengklasifikasi imej anda](../../../../../4-manufacturing/lessons/1-train-fruit-detector)
* [Melatih semula pengklasifikasi imej anda](../../../../../4-manufacturing/lessons/1-train-fruit-detector)

## Menggunakan AI dan ML untuk menyusun makanan

Memberi makan kepada populasi global adalah tugas yang sukar, terutamanya pada harga yang mampu milik untuk semua. Salah satu kos terbesar adalah buruh, jadi petani semakin beralih kepada automasi dan alat seperti IoT untuk mengurangkan kos buruh mereka. Penuaian secara manual memerlukan banyak tenaga kerja (dan sering kali kerja yang memenatkan), dan kini digantikan oleh mesin, terutamanya di negara-negara kaya. Walaupun penggunaan mesin untuk menuai menjimatkan kos, terdapat kelemahan - keupayaan untuk menyusun makanan semasa ia dituai.

Tidak semua tanaman masak secara seragam. Sebagai contoh, tomato masih boleh mempunyai buah hijau pada pokoknya apabila sebahagian besar sudah sedia untuk dituai. Walaupun menuai buah yang belum masak adalah pembaziran, ia lebih murah dan mudah bagi petani untuk menuai semuanya menggunakan mesin dan membuang hasil yang belum masak kemudian.

✅ Lihatlah pelbagai buah atau sayuran, sama ada yang tumbuh berhampiran anda di ladang atau di taman anda, atau di kedai. Adakah semuanya masak pada tahap yang sama, atau adakah anda melihat variasi?

Kebangkitan penuaian automatik memindahkan proses penyusunan hasil dari ladang ke kilang. Makanan akan bergerak di atas tali sawat panjang dengan pasukan pekerja yang memilih hasil yang tidak memenuhi standard kualiti yang diperlukan. Penuaian menjadi lebih murah berkat mesin, tetapi masih ada kos untuk menyusun makanan secara manual.

![Jika tomato merah dikesan, ia terus bergerak tanpa gangguan. Jika tomato hijau dikesan, ia akan ditolak ke dalam tong sampah oleh tuas](../../../../../translated_images/optical-tomato-sorting.61aa134bdda4e5b1bfb16a212c1e35a6ef0c426cbb8b1c975f79d7bfbf48d068.ms.png)

Evolusi seterusnya adalah menggunakan mesin untuk menyusun, sama ada dibina dalam mesin penuaian atau di kilang pemprosesan. Generasi pertama mesin ini menggunakan sensor optik untuk mengesan warna, mengawal penggerak untuk menolak tomato hijau ke dalam tong sampah menggunakan tuas atau hembusan udara, meninggalkan tomato merah untuk terus bergerak di atas rangkaian tali sawat.

Dalam video ini, semasa tomato jatuh dari satu tali sawat ke tali sawat lain, tomato hijau dikesan dan ditolak ke dalam tong menggunakan tuas.

✅ Apakah keadaan yang diperlukan di kilang atau di ladang untuk sensor optik ini berfungsi dengan betul?

Evolusi terkini mesin penyusunan ini memanfaatkan AI dan ML, menggunakan model yang dilatih untuk membezakan hasil yang baik daripada yang buruk, bukan hanya berdasarkan perbezaan warna yang jelas seperti tomato hijau vs merah, tetapi juga perbezaan penampilan yang lebih halus yang boleh menunjukkan penyakit atau lebam.

## Klasifikasi imej melalui Pembelajaran Mesin

Pengaturcaraan tradisional adalah di mana anda mengambil data, menggunakan algoritma pada data, dan mendapatkan output. Sebagai contoh, dalam projek terakhir anda mengambil koordinat GPS dan geofence, menggunakan algoritma yang disediakan oleh Azure Maps, dan mendapat hasil sama ada titik itu berada di dalam atau di luar geofence. Anda memasukkan lebih banyak data, anda mendapat lebih banyak output.

![Pembangunan tradisional mengambil input dan algoritma dan memberikan output. Pembelajaran mesin menggunakan data input dan output untuk melatih model, dan model ini boleh mengambil data input baru untuk menghasilkan output baru](../../../../../translated_images/traditional-vs-ml.5c20c169621fa539ca84a2cd9a49f6ff7410b3a6c6b46c97ff2af3f99db3c66b.ms.png)

Pembelajaran mesin membalikkan proses ini - anda bermula dengan data dan output yang diketahui, dan algoritma pembelajaran mesin belajar daripada data tersebut. Anda kemudian boleh mengambil algoritma yang telah dilatih ini, yang dipanggil *model pembelajaran mesin* atau *model*, dan memasukkan data baru untuk mendapatkan output baru.

> 🎓 Proses algoritma pembelajaran mesin belajar daripada data dipanggil *latihan*. Input dan output yang diketahui dipanggil *data latihan*.

Sebagai contoh, anda boleh memberikan model berjuta-juta gambar pisang yang belum masak sebagai data latihan input, dengan output latihan ditetapkan sebagai `belum masak`, dan berjuta-juta gambar pisang masak sebagai data latihan dengan output ditetapkan sebagai `masak`. Algoritma ML kemudian akan mencipta model berdasarkan data ini. Anda kemudian memberikan model ini gambar baru pisang dan ia akan meramalkan sama ada gambar baru itu adalah pisang masak atau belum masak.

> 🎓 Hasil daripada model ML dipanggil *ramalan*

![2 pisang, satu masak dengan ramalan 99.7% masak, 0.3% belum masak, dan satu belum masak dengan ramalan 1.4% masak, 98.6% belum masak](../../../../../translated_images/bananas-ripe-vs-unripe-predictions.8d0e2034014aa50ece4e4589e724b142da0681f35470fe3db3f7d51240f69c85.ms.png)

Model ML tidak memberikan jawapan binari, sebaliknya ia memberikan kebarangkalian. Sebagai contoh, model mungkin diberikan gambar pisang dan meramalkan `masak` pada 99.7% dan `belum masak` pada 0.3%. Kod anda kemudian akan memilih ramalan terbaik dan memutuskan bahawa pisang itu masak.

Model ML yang digunakan untuk mengesan imej seperti ini dipanggil *pengklasifikasi imej* - ia diberikan imej yang dilabel, dan kemudian mengklasifikasikan imej baru berdasarkan label ini.

> 💁 Ini adalah penyederhanaan, dan terdapat banyak cara lain untuk melatih model yang tidak selalu memerlukan output yang dilabel, seperti pembelajaran tanpa pengawasan. Jika anda ingin belajar lebih lanjut tentang ML, lihat [ML untuk pemula, kurikulum 24 pelajaran tentang Pembelajaran Mesin](https://aka.ms/ML-beginners).

## Melatih pengklasifikasi imej

Untuk berjaya melatih pengklasifikasi imej, anda memerlukan berjuta-juta imej. Namun, setelah anda mempunyai pengklasifikasi imej yang dilatih pada berjuta-juta atau berbilion imej pelbagai, anda boleh menggunakannya semula dan melatih semula menggunakan set imej kecil untuk mendapatkan hasil yang baik, menggunakan proses yang dipanggil *pembelajaran pemindahan*.

> 🎓 Pembelajaran pemindahan adalah di mana anda memindahkan pembelajaran daripada model ML sedia ada kepada model baru berdasarkan data baru.

Setelah pengklasifikasi imej dilatih untuk pelbagai imej, bahagian dalamannya sangat baik dalam mengenali bentuk, warna, dan corak. Pembelajaran pemindahan membolehkan model menggunakan apa yang telah dipelajarinya dalam mengenali bahagian imej, dan menggunakannya untuk mengenali imej baru.

![Setelah anda dapat mengenali bentuk, bentuk tersebut boleh disusun dalam konfigurasi yang berbeza untuk membuat bot atau kucing](../../../../../translated_images/shapes-to-images.1a309f0ea88dd66fafa4da6d38e88806ce174cc6a88081efb32852230ed55de8.ms.png)

Anda boleh menganggap ini seperti buku bentuk kanak-kanak, di mana setelah anda dapat mengenali separuh bulatan, segi empat tepat, dan segitiga, anda dapat mengenali bot layar atau kucing bergantung pada konfigurasi bentuk ini. Pengklasifikasi imej dapat mengenali bentuk, dan pembelajaran pemindahan mengajarnya kombinasi apa yang membentuk bot atau kucing - atau pisang masak.

Terdapat pelbagai alat yang boleh membantu anda melakukan ini, termasuk perkhidmatan berasaskan awan yang boleh membantu anda melatih model anda, kemudian menggunakannya melalui API web.

> 💁 Melatih model ini memerlukan banyak kuasa komputer, biasanya melalui Unit Pemprosesan Grafik, atau GPU. Perkakasan khusus yang sama yang menjadikan permainan di Xbox anda kelihatan hebat juga boleh digunakan untuk melatih model pembelajaran mesin. Dengan menggunakan awan, anda boleh menyewa masa pada komputer berkuasa dengan GPU untuk melatih model ini, mendapatkan akses kepada kuasa pengkomputeran yang anda perlukan, hanya untuk masa yang anda perlukan.

## Custom Vision

Custom Vision adalah alat berasaskan awan untuk melatih pengklasifikasi imej. Ia membolehkan anda melatih pengklasifikasi menggunakan hanya sejumlah kecil imej. Anda boleh memuat naik imej melalui portal web, API web, atau SDK, memberikan setiap imej *tag* yang mengklasifikasikan imej tersebut. Anda kemudian melatih model, dan mengujinya untuk melihat sejauh mana prestasinya. Setelah anda berpuas hati dengan model tersebut, anda boleh menerbitkan versi yang boleh diakses melalui API web atau SDK.

![Logo Azure Custom Vision](../../../../../translated_images/custom-vision-logo.d3d4e7c8a87ec9daf825e72e210576c3cbf60312577be7a139e22dd97ab7f1e6.ms.png)

> 💁 Anda boleh melatih model Custom Vision dengan hanya 5 imej bagi setiap klasifikasi, tetapi lebih banyak adalah lebih baik. Anda boleh mendapatkan hasil yang lebih baik dengan sekurang-kurangnya 30 imej.

Custom Vision adalah sebahagian daripada rangkaian alat AI dari Microsoft yang dipanggil Cognitive Services. Ini adalah alat AI yang boleh digunakan sama ada tanpa latihan atau dengan sedikit latihan. Ia termasuk pengecaman dan terjemahan ucapan, pemahaman bahasa, dan analisis imej. Alat ini tersedia dengan tahap percuma sebagai perkhidmatan di Azure.

> 💁 Tahap percuma lebih daripada mencukupi untuk mencipta model, melatihnya, kemudian menggunakannya untuk kerja pembangunan. Anda boleh membaca tentang had tahap percuma di [Halaman Had dan Kuota Custom Vision di dokumen Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/limits-and-quotas?WT.mc_id=academic-17441-jabenn).

### Tugasan - mencipta sumber perkhidmatan kognitif

Untuk menggunakan Custom Vision, anda perlu mencipta dua sumber perkhidmatan kognitif di Azure menggunakan Azure CLI, satu untuk latihan Custom Vision dan satu lagi untuk ramalan Custom Vision.

1. Cipta Kumpulan Sumber untuk projek ini yang dipanggil `fruit-quality-detector`.

1. Gunakan perintah berikut untuk mencipta sumber latihan Custom Vision percuma:

    ```sh
    az cognitiveservices account create --name fruit-quality-detector-training \
                                        --resource-group fruit-quality-detector \
                                        --kind CustomVision.Training \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Gantikan `<location>` dengan lokasi yang anda gunakan semasa mencipta Kumpulan Sumber.

    Ini akan mencipta sumber latihan Custom Vision dalam Kumpulan Sumber anda. Ia akan dipanggil `fruit-quality-detector-training` dan menggunakan sku `F0`, yang merupakan tahap percuma. Pilihan `--yes` bermaksud anda bersetuju dengan terma dan syarat perkhidmatan kognitif.

> 💁 Gunakan sku `S0` jika anda sudah mempunyai akaun percuma yang menggunakan mana-mana Perkhidmatan Kognitif.

1. Gunakan perintah berikut untuk mencipta sumber ramalan Custom Vision percuma:

    ```sh
    az cognitiveservices account create --name fruit-quality-detector-prediction \
                                        --resource-group fruit-quality-detector \
                                        --kind CustomVision.Prediction \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Gantikan `<location>` dengan lokasi yang anda gunakan semasa mencipta Kumpulan Sumber.

    Ini akan mencipta sumber ramalan Custom Vision dalam Kumpulan Sumber anda. Ia akan dipanggil `fruit-quality-detector-prediction` dan menggunakan sku `F0`, yang merupakan tahap percuma. Pilihan `--yes` bermaksud anda bersetuju dengan terma dan syarat perkhidmatan kognitif.

### Tugasan - mencipta projek pengklasifikasi imej

1. Lancarkan portal Custom Vision di [CustomVision.ai](https://customvision.ai), dan log masuk dengan akaun Microsoft yang anda gunakan untuk akaun Azure anda.

1. Ikuti [bahagian mencipta projek baru dalam panduan pantas membina pengklasifikasi di dokumen Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#create-a-new-project) untuk mencipta projek Custom Vision baru. Antaramuka pengguna mungkin berubah dan dokumen ini sentiasa menjadi rujukan terkini.

    Namakan projek anda `fruit-quality-detector`.

    Semasa mencipta projek anda, pastikan untuk menggunakan sumber `fruit-quality-detector-training` yang anda cipta sebelum ini. Gunakan jenis projek *Classification*, jenis klasifikasi *Multiclass*, dan domain *Food*.

    ![Tetapan untuk projek Custom Vision dengan nama ditetapkan kepada fruit-quality-detector, tiada deskripsi, sumber ditetapkan kepada fruit-quality-detector-training, jenis projek ditetapkan kepada classification, jenis klasifikasi ditetapkan kepada multi class dan domain ditetapkan kepada food](../../../../../translated_images/custom-vision-create-project.cf46325b92d8b131089f6647cf5e07b664cb77850e106d66e3c057b6b69756c6.ms.png)

✅ Luangkan masa untuk meneroka antaramuka pengguna Custom Vision untuk pengklasifikasi imej anda.

### Tugasan - melatih projek pengklasifikasi imej anda

Untuk melatih pengklasifikasi imej, anda memerlukan pelbagai gambar buah, baik yang berkualiti baik mahupun buruk untuk ditandai sebagai baik dan buruk, seperti pisang masak dan pisang terlalu masak.
💁 Pengelas ini boleh mengklasifikasikan imej apa sahaja, jadi jika anda tidak mempunyai buah dengan kualiti berbeza, anda boleh gunakan dua jenis buah yang berbeza, atau kucing dan anjing!
Setiap gambar sebaiknya hanya menunjukkan buah tersebut, dengan latar belakang yang konsisten atau pelbagai latar belakang. Pastikan tiada elemen dalam latar belakang yang menunjukkan perbezaan antara buah masak dan tidak masak.

> 💁 Penting untuk tidak menggunakan latar belakang tertentu, atau elemen yang tidak berkaitan dengan perkara yang diklasifikasikan untuk setiap tag. Jika tidak, pengklasifikasi mungkin hanya membuat klasifikasi berdasarkan latar belakang. Terdapat satu pengklasifikasi untuk kanser kulit yang dilatih menggunakan gambar tahi lalat biasa dan kanser. Gambar tahi lalat kanser semuanya mempunyai pembaris untuk mengukur saiz. Akhirnya, pengklasifikasi tersebut hampir 100% tepat mengenal pasti pembaris dalam gambar, bukan tahi lalat kanser.

Pengklasifikasi imej beroperasi pada resolusi yang sangat rendah. Sebagai contoh, Custom Vision boleh menerima gambar latihan dan ramalan sehingga 10240x10240, tetapi melatih dan menjalankan model pada gambar bersaiz 227x227. Gambar yang lebih besar akan dikecilkan ke saiz ini, jadi pastikan objek yang anda klasifikasikan memenuhi sebahagian besar gambar. Jika tidak, ia mungkin terlalu kecil dalam gambar yang lebih kecil yang digunakan oleh pengklasifikasi.

1. Kumpulkan gambar untuk pengklasifikasi anda. Anda memerlukan sekurang-kurangnya 5 gambar untuk setiap label bagi melatih pengklasifikasi, tetapi lebih banyak adalah lebih baik. Anda juga memerlukan beberapa gambar tambahan untuk menguji pengklasifikasi. Gambar-gambar ini mestilah gambar yang berbeza untuk objek yang sama. Sebagai contoh:

    * Gunakan 2 pisang masak, ambil beberapa gambar setiap satu dari pelbagai sudut, sekurang-kurangnya 7 gambar (5 untuk latihan, 2 untuk ujian), tetapi lebih banyak adalah lebih baik.

        ![Gambar 2 pisang yang berbeza](../../../../../translated_images/banana-training-images.530eb203346d73bc23b8b990fb4609470bf4ff7c942ccc13d4cfffeed9be1ad4.ms.png)

    * Ulang proses yang sama menggunakan 2 pisang yang tidak masak.

    Anda sepatutnya mempunyai sekurang-kurangnya 10 gambar latihan, dengan sekurang-kurangnya 5 gambar pisang masak dan 5 gambar pisang tidak masak, serta 4 gambar ujian, 2 masak, 2 tidak masak. Gambar anda mestilah dalam format png atau jpeg, dan bersaiz kurang daripada 6MB. Jika anda mengambil gambar menggunakan iPhone, contohnya, ia mungkin dalam format resolusi tinggi HEIC, jadi perlu ditukar dan mungkin dikecilkan. Lebih banyak gambar adalah lebih baik, dan anda sepatutnya mempunyai bilangan gambar masak dan tidak masak yang hampir sama.

    Jika anda tidak mempunyai kedua-dua buah masak dan tidak masak, anda boleh menggunakan buah-buahan lain, atau mana-mana dua objek yang anda ada. Anda juga boleh mencari beberapa gambar contoh dalam folder [images](../../../../../4-manufacturing/lessons/1-train-fruit-detector/images) untuk pisang masak dan tidak masak yang boleh anda gunakan.

1. Ikuti [bahagian muat naik dan tag gambar dalam panduan pantas membina pengklasifikasi di dokumen Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#upload-and-tag-images) untuk memuat naik gambar latihan anda. Tag buah masak sebagai `ripe`, dan buah tidak masak sebagai `unripe`.

    ![Dialog muat naik menunjukkan muat naik gambar pisang masak dan tidak masak](../../../../../translated_images/image-upload-bananas.0751639f3815e0ec42bdbc6254d1e4357a185834d1ae10c9948a0e7d6d336695.ms.png)

1. Ikuti [bahagian melatih pengklasifikasi dalam panduan pantas membina pengklasifikasi di dokumen Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#train-the-classifier) untuk melatih pengklasifikasi imej menggunakan gambar yang telah dimuat naik.

    Anda akan diberikan pilihan jenis latihan. Pilih **Latihan Pantas**.

Pengklasifikasi akan mula dilatih. Proses ini akan mengambil masa beberapa minit untuk diselesaikan.

> 🍌 Jika anda memutuskan untuk makan buah anda semasa pengklasifikasi sedang dilatih, pastikan anda mempunyai cukup gambar untuk ujian terlebih dahulu!

## Uji pengklasifikasi imej anda

Setelah pengklasifikasi anda dilatih, anda boleh mengujinya dengan memberikan gambar baru untuk diklasifikasikan.

### Tugasan - uji pengklasifikasi imej anda

1. Ikuti [dokumentasi ujian model anda di dokumen Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/test-your-model?WT.mc_id=academic-17441-jabenn#test-your-model) untuk menguji pengklasifikasi imej anda. Gunakan gambar ujian yang anda cipta sebelum ini, bukan mana-mana gambar yang digunakan untuk latihan.

    ![Pisang tidak masak diramalkan sebagai tidak masak dengan kebarangkalian 98.9%, masak dengan kebarangkalian 1.1%](../../../../../translated_images/banana-unripe-quick-test-prediction.dae9b5e1c4ef7c64886422438850ea14f0be6ac918c217ea3b255c685abfabe7.ms.png)

1. Cuba semua gambar ujian yang anda ada dan perhatikan kebarangkalian yang diberikan.

## Latih semula pengklasifikasi imej anda

Apabila anda menguji pengklasifikasi anda, ia mungkin tidak memberikan hasil seperti yang anda harapkan. Pengklasifikasi imej menggunakan pembelajaran mesin untuk membuat ramalan tentang apa yang ada dalam gambar, berdasarkan kebarangkalian bahawa ciri tertentu dalam gambar bermaksud ia sepadan dengan label tertentu. Ia tidak memahami apa yang ada dalam gambar - ia tidak tahu apa itu pisang atau memahami apa yang membezakan pisang daripada bot. Anda boleh meningkatkan pengklasifikasi anda dengan melatih semula menggunakan gambar yang salah diklasifikasikan.

Setiap kali anda membuat ramalan menggunakan pilihan ujian pantas, gambar dan hasilnya akan disimpan. Anda boleh menggunakan gambar-gambar ini untuk melatih semula model anda.

### Tugasan - latih semula pengklasifikasi imej anda

1. Ikuti [dokumentasi menggunakan gambar yang diramalkan untuk latihan di dokumen Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/test-your-model?WT.mc_id=academic-17441-jabenn#use-the-predicted-image-for-training) untuk melatih semula model anda, menggunakan tag yang betul untuk setiap gambar.

1. Setelah model anda dilatih semula, uji dengan gambar baru.

---

## 🚀 Cabaran

Apa yang anda fikir akan berlaku jika anda menggunakan gambar strawberi dengan model yang dilatih pada pisang, atau gambar pisang tiup, atau seseorang dalam kostum pisang, atau bahkan watak kartun kuning seperti seseorang dari Simpsons?

Cuba dan lihat apa ramalannya. Anda boleh mencari gambar untuk mencuba menggunakan [Bing Image search](https://www.bing.com/images/trending).

## Kuiz selepas kuliah

[Kuiz selepas kuliah](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/30)

## Ulasan & Kajian Kendiri

* Semasa anda melatih pengklasifikasi anda, anda akan melihat nilai untuk *Precision*, *Recall*, dan *AP* yang menilai model yang telah dicipta. Baca tentang apa nilai-nilai ini menggunakan [bahagian menilai pengklasifikasi dalam panduan pantas membina pengklasifikasi di dokumen Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#evaluate-the-classifier)
* Baca tentang cara meningkatkan pengklasifikasi anda dari [cara meningkatkan model Custom Vision anda di dokumen Microsoft](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-improving-your-classifier?WT.mc_id=academic-17441-jabenn)

## Tugasan

[Latih pengklasifikasi anda untuk pelbagai buah-buahan dan sayur-sayuran](assignment.md)

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.