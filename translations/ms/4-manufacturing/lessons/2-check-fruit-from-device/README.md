<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "557f4ee96b752e0651d2e6e74aa6bd14",
  "translation_date": "2025-08-27T20:56:44+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/README.md",
  "language_code": "ms"
}
-->
# Periksa Kualiti Buah Menggunakan Peranti IoT

![Gambaran sketchnote untuk pelajaran ini](../../../../../translated_images/ms/lesson-16.215daf18b00631fbdfd64c6fc2dc6044dff5d544288825d8076f9fb83d964c23.jpg)

> Sketchnote oleh [Nitya Narasimhan](https://github.com/nitya). Klik imej untuk versi yang lebih besar.

## Kuiz Pra-Kuliah

[Kuiz Pra-Kuliah](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/31)

## Pengenalan

Dalam pelajaran sebelum ini, anda telah mempelajari tentang pengklasifikasi imej dan cara melatihnya untuk mengesan buah yang baik dan buruk. Untuk menggunakan pengklasifikasi imej ini dalam aplikasi IoT, anda perlu dapat menangkap imej menggunakan kamera dan menghantar imej ini ke awan untuk dikelaskan.

Dalam pelajaran ini, anda akan mempelajari tentang sensor kamera dan cara menggunakannya dengan peranti IoT untuk menangkap imej. Anda juga akan belajar cara memanggil pengklasifikasi imej dari peranti IoT anda.

Dalam pelajaran ini, kita akan membincangkan:

* [Sensor kamera](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Tangkap imej menggunakan peranti IoT](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Terbitkan pengklasifikasi imej anda](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Klasifikasikan imej dari peranti IoT anda](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Perbaiki model](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)

## Sensor Kamera

Sensor kamera, seperti namanya, adalah kamera yang boleh disambungkan ke peranti IoT anda. Ia boleh mengambil imej pegun atau menangkap video secara langsung. Sesetengahnya akan mengembalikan data imej mentah, manakala yang lain akan memampatkan data imej ke dalam fail imej seperti JPEG atau PNG. Biasanya, kamera yang berfungsi dengan peranti IoT adalah lebih kecil dan mempunyai resolusi lebih rendah daripada yang biasa anda gunakan, tetapi anda boleh mendapatkan kamera resolusi tinggi yang setanding dengan telefon pintar kelas atas. Anda juga boleh mendapatkan pelbagai jenis lensa boleh tukar, tetapan kamera berganda, kamera termal infra-merah, atau kamera UV.

![Cahaya dari pemandangan melalui lensa dan difokuskan pada sensor CMOS](../../../../../translated_images/ms/cmos-sensor.75f9cd74decb137149a4c9ea825251a4549497d67c0ae2776159e6102bb53aa9.png)

Kebanyakan sensor kamera menggunakan sensor imej di mana setiap piksel adalah fotodiod. Lensa memfokuskan imej ke sensor imej, dan ribuan atau jutaan fotodiod mengesan cahaya yang jatuh pada setiap satu dan merekodkannya sebagai data piksel.

> 💁 Lensa membalikkan imej, dan sensor kamera kemudian membalikkan imej kembali ke arah yang betul. Ini sama seperti mata anda - apa yang anda lihat dikesan terbalik di belakang mata anda, dan otak anda membetulkannya.

> 🎓 Sensor imej dikenali sebagai Sensor Piksel Aktif (APS), dan jenis APS yang paling popular adalah sensor semikonduktor logam oksida pelengkap, atau CMOS. Anda mungkin pernah mendengar istilah sensor CMOS digunakan untuk sensor kamera.

Sensor kamera adalah sensor digital, menghantar data imej sebagai data digital, biasanya dengan bantuan perpustakaan yang menyediakan komunikasi. Kamera disambungkan menggunakan protokol seperti SPI untuk membolehkan mereka menghantar sejumlah besar data - imej jauh lebih besar daripada nombor tunggal dari sensor seperti sensor suhu.

✅ Apakah batasan saiz imej dengan peranti IoT? Fikirkan tentang kekangan terutamanya pada perkakasan mikropengawal.

## Tangkap Imej Menggunakan Peranti IoT

Anda boleh menggunakan peranti IoT anda untuk menangkap imej untuk dikelaskan.

### Tugas - Tangkap Imej Menggunakan Peranti IoT

Ikuti panduan yang berkaitan untuk menangkap imej menggunakan peranti IoT anda:

* [Arduino - Wio Terminal](wio-terminal-camera.md)
* [Komputer papan tunggal - Raspberry Pi](pi-camera.md)
* [Komputer papan tunggal - Peranti maya](virtual-device-camera.md)

## Terbitkan Pengklasifikasi Imej Anda

Anda telah melatih pengklasifikasi imej anda dalam pelajaran sebelum ini. Sebelum anda boleh menggunakannya dari peranti IoT anda, anda perlu menerbitkan model tersebut.

### Iterasi Model

Semasa model anda dilatih dalam pelajaran sebelum ini, anda mungkin perasan bahawa tab **Performance** menunjukkan iterasi di sisi. Apabila anda pertama kali melatih model, anda akan melihat *Iteration 1* dalam latihan. Apabila anda memperbaiki model menggunakan imej ramalan, anda akan melihat *Iteration 2* dalam latihan.

Setiap kali anda melatih model, anda mendapat iterasi baru. Ini adalah cara untuk menjejaki versi model anda yang dilatih pada set data yang berbeza. Apabila anda melakukan **Quick Test**, terdapat menu lungsur yang boleh anda gunakan untuk memilih iterasi, jadi anda boleh membandingkan hasil di antara pelbagai iterasi.

Apabila anda berpuas hati dengan satu iterasi, anda boleh menerbitkannya untuk menjadikannya tersedia untuk digunakan dari aplikasi luaran. Dengan cara ini, anda boleh mempunyai versi yang diterbitkan yang digunakan oleh peranti anda, kemudian bekerja pada versi baru melalui pelbagai iterasi, dan menerbitkannya apabila anda berpuas hati dengannya.

### Tugas - Terbitkan Iterasi

Iterasi diterbitkan dari portal Custom Vision.

1. Lancarkan portal Custom Vision di [CustomVision.ai](https://customvision.ai) dan log masuk jika anda belum membukanya. Kemudian buka projek `fruit-quality-detector` anda.

1. Pilih tab **Performance** dari pilihan di bahagian atas.

1. Pilih iterasi terkini dari senarai *Iterations* di sisi.

1. Pilih butang **Publish** untuk iterasi tersebut.

    ![Butang publish](../../../../../translated_images/ms/custom-vision-publish-button.b7174e1977b0c33b8b72d4e5b1326c779e0af196f3849d09985ee2d7d5493a39.png)

1. Dalam dialog *Publish Model*, tetapkan *Prediction resource* kepada sumber `fruit-quality-detector-prediction` yang anda buat dalam pelajaran sebelum ini. Biarkan nama sebagai `Iteration2`, dan pilih butang **Publish**.

1. Setelah diterbitkan, pilih butang **Prediction URL**. Ini akan menunjukkan butiran API ramalan, dan anda akan memerlukan ini untuk memanggil model dari peranti IoT anda. Bahagian bawah dilabelkan *If you have an image file*, dan ini adalah butiran yang anda perlukan. Salin URL yang ditunjukkan, yang akan kelihatan seperti:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/classify/iterations/Iteration2/image
    ```

    Di mana `<location>` adalah lokasi yang anda gunakan semasa membuat sumber visi tersuai anda, dan `<id>` adalah ID panjang yang terdiri daripada huruf dan nombor.

    Juga salin nilai *Prediction-Key*. Ini adalah kunci selamat yang perlu anda sertakan semasa memanggil model. Hanya aplikasi yang menyertakan kunci ini dibenarkan menggunakan model, aplikasi lain akan ditolak.

    ![Dialog API ramalan menunjukkan URL dan kunci](../../../../../translated_images/ms/custom-vision-prediction-key-endpoint.30c569ffd0338864f319911f052d5e9b8c5066cb0800a26dd6f7ff5713130ad8.png)

✅ Apabila iterasi baru diterbitkan, ia akan mempunyai nama yang berbeza. Bagaimana anda fikir anda akan menukar iterasi yang digunakan oleh peranti IoT?

## Klasifikasikan Imej dari Peranti IoT Anda

Anda kini boleh menggunakan butiran sambungan ini untuk memanggil pengklasifikasi imej dari peranti IoT anda.

### Tugas - Klasifikasikan Imej dari Peranti IoT Anda

Ikuti panduan yang berkaitan untuk mengklasifikasikan imej menggunakan peranti IoT anda:

* [Arduino - Wio Terminal](wio-terminal-classify-image.md)
* [Komputer papan tunggal - Raspberry Pi/Peranti IoT maya](single-board-computer-classify-image.md)

## Perbaiki Model

Anda mungkin mendapati bahawa hasil yang anda peroleh semasa menggunakan kamera yang disambungkan ke peranti IoT anda tidak sepadan dengan apa yang anda jangkakan. Ramalan tidak selalu seakurat menggunakan imej yang dimuat naik dari komputer anda. Ini kerana model dilatih pada data yang berbeza daripada yang digunakan untuk ramalan.

Untuk mendapatkan hasil terbaik untuk pengklasifikasi imej, anda ingin melatih model dengan imej yang serupa dengan imej yang digunakan untuk ramalan sebanyak mungkin. Jika anda menggunakan kamera telefon anda untuk menangkap imej untuk latihan, contohnya, kualiti imej, ketajaman, dan warna akan berbeza dengan kamera yang disambungkan ke peranti IoT.

![2 gambar pisang, satu resolusi rendah dengan pencahayaan buruk dari peranti IoT, dan satu resolusi tinggi dengan pencahayaan baik dari telefon](../../../../../translated_images/ms/banana-picture-compare.174df164dc326a42cf7fb051a7497e6113c620e91552d92ca914220305d47d9a.png)

Dalam gambar di atas, gambar pisang di sebelah kiri diambil menggunakan Kamera Raspberry Pi, manakala yang di sebelah kanan diambil dari pisang yang sama di lokasi yang sama menggunakan iPhone. Terdapat perbezaan kualiti yang ketara - gambar iPhone lebih tajam, dengan warna yang lebih terang dan kontras yang lebih tinggi.

✅ Apa lagi yang mungkin menyebabkan imej yang ditangkap oleh peranti IoT anda memberikan ramalan yang salah? Fikirkan tentang persekitaran di mana peranti IoT mungkin digunakan, faktor apa yang boleh mempengaruhi imej yang ditangkap?

Untuk memperbaiki model, anda boleh melatih semula menggunakan imej yang ditangkap dari peranti IoT.

### Tugas - Perbaiki Model

1. Klasifikasikan pelbagai imej buah masak dan tidak masak menggunakan peranti IoT anda.

1. Dalam portal Custom Vision, latih semula model menggunakan imej pada tab *Predictions*.

    > ⚠️ Anda boleh merujuk kepada [arahan untuk melatih semula pengklasifikasi anda dalam pelajaran 1 jika diperlukan](../1-train-fruit-detector/README.md#retrain-your-image-classifier).

1. Jika imej anda kelihatan sangat berbeza dengan imej asal yang digunakan untuk latihan, anda boleh memadamkan semua imej asal dengan memilihnya di tab *Training Images* dan memilih butang **Delete**. Untuk memilih imej, gerakkan kursor anda ke atasnya dan tanda semak akan muncul, pilih tanda semak itu untuk memilih atau membatalkan pilihan imej.

1. Latih iterasi baru model dan terbitkan menggunakan langkah di atas.

1. Kemas kini URL endpoint dalam kod anda, dan jalankan semula aplikasi.

1. Ulangi langkah-langkah ini sehingga anda berpuas hati dengan hasil ramalan.

---

## 🚀 Cabaran

Sejauh mana resolusi imej atau pencahayaan mempengaruhi ramalan?

Cuba ubah resolusi imej dalam kod peranti anda dan lihat jika ia membuat perbezaan pada kualiti imej. Juga cuba ubah pencahayaan.

Jika anda ingin mencipta peranti pengeluaran untuk dijual kepada ladang atau kilang, bagaimana anda akan memastikan ia memberikan hasil yang konsisten sepanjang masa?

## Kuiz Pasca-Kuliah

[Kuiz Pasca-Kuliah](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/32)

## Ulasan & Kajian Kendiri

Anda telah melatih model visi tersuai anda menggunakan portal. Ini bergantung pada ketersediaan imej - dan dalam dunia nyata, anda mungkin tidak dapat mendapatkan data latihan yang sepadan dengan apa yang ditangkap oleh kamera pada peranti anda. Anda boleh mengatasi ini dengan melatih secara langsung dari peranti anda menggunakan API latihan, untuk melatih model menggunakan imej yang ditangkap dari peranti IoT anda.

* Baca tentang API latihan dalam [panduan mula cepat menggunakan SDK Custom Vision](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/quickstarts/image-classification?WT.mc_id=academic-17441-jabenn&tabs=visual-studio&pivots=programming-language-python)

## Tugasan

[Respon kepada hasil klasifikasi](assignment.md)

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.