<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d105b44deae539165855c976dcdeca99",
  "translation_date": "2025-08-27T21:24:30+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/README.md",
  "language_code": "ms"
}
-->
## Ramalkan Pertumbuhan Tumbuhan dengan IoT

![Gambaran sketchnote untuk pelajaran ini](../../../../../translated_images/ms/lesson-5.42b234299279d263143148b88ab4583861a32ddb03110c6c1120e41bb88b2592.jpg)

> Sketchnote oleh [Nitya Narasimhan](https://github.com/nitya). Klik imej untuk versi yang lebih besar.

## Kuiz Pra-Kuliah

[Kuiz Pra-Kuliah](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/9)

## Pengenalan

Tumbuhan memerlukan beberapa perkara untuk tumbuh - air, karbon dioksida, nutrien, cahaya, dan haba. Dalam pelajaran ini, anda akan belajar bagaimana mengira kadar pertumbuhan dan kematangan tumbuhan dengan mengukur suhu udara.

Dalam pelajaran ini kita akan membincangkan:

* [Pertanian digital](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Mengapa suhu penting dalam pertanian?](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Mengukur suhu persekitaran](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Hari darjah pertumbuhan (GDD)](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Mengira GDD menggunakan data sensor suhu](../../../../../2-farm/lessons/1-predict-plant-growth)

## Pertanian Digital

Pertanian Digital sedang mengubah cara kita bertani, menggunakan alat untuk mengumpul, menyimpan dan menganalisis data dari aktiviti pertanian. Kita kini berada dalam era yang digambarkan sebagai 'Revolusi Industri Keempat' oleh Forum Ekonomi Dunia, dan kebangkitan pertanian digital telah dilabelkan sebagai 'Revolusi Pertanian Keempat', atau 'Agriculture 4.0'.

> 🎓 Istilah Pertanian Digital juga merangkumi keseluruhan 'rantaian nilai pertanian', iaitu perjalanan lengkap dari ladang ke meja makan. Ia termasuk penjejakan kualiti hasil tanaman semasa penghantaran dan pemprosesan makanan, sistem gudang dan e-dagang, malah aplikasi sewaan traktor!

Perubahan ini membolehkan petani meningkatkan hasil tanaman, menggunakan kurang baja dan racun perosak, serta menggunakan air dengan lebih cekap. Walaupun kebanyakannya digunakan di negara-negara kaya, sensor dan peranti lain secara perlahan-lahan menjadi lebih murah, menjadikannya lebih mudah diakses di negara-negara membangun.

Beberapa teknik yang dimungkinkan oleh pertanian digital adalah:

* Pengukuran suhu - mengukur suhu membolehkan petani meramalkan pertumbuhan dan kematangan tumbuhan.
* Penyiraman automatik - mengukur kelembapan tanah dan menghidupkan sistem pengairan apabila tanah terlalu kering, bukannya penyiraman berjadual. Penyiraman berjadual boleh menyebabkan tanaman kekurangan air semasa cuaca panas dan kering, atau terlalu banyak air semasa hujan. Dengan menyiram hanya apabila tanah memerlukannya, petani dapat mengoptimumkan penggunaan air mereka.
* Kawalan perosak - petani boleh menggunakan kamera pada robot automatik atau dron untuk memeriksa perosak, kemudian menggunakan racun perosak hanya di kawasan yang diperlukan, mengurangkan jumlah racun perosak yang digunakan dan mengurangkan aliran racun perosak ke bekalan air tempatan.

✅ Lakukan sedikit penyelidikan. Apakah teknik lain yang digunakan untuk meningkatkan hasil pertanian?

> 🎓 Istilah 'Pertanian Tepat' digunakan untuk mendefinisikan pemerhatian, pengukuran dan tindak balas terhadap tanaman berdasarkan setiap ladang, atau bahkan pada bahagian ladang. Ini termasuk mengukur tahap air, nutrien dan perosak serta bertindak balas dengan tepat, seperti menyiram hanya sebahagian kecil ladang.

## Mengapa suhu penting dalam pertanian?

Semasa mempelajari tentang tumbuhan, kebanyakan pelajar diajar tentang keperluan air, cahaya, karbon dioksida, dan nutrien. Tumbuhan juga memerlukan kehangatan untuk tumbuh - inilah sebabnya tumbuhan berbunga pada musim bunga apabila suhu meningkat, mengapa bunga salji atau daffodil boleh tumbuh awal akibat cuaca hangat yang singkat, dan mengapa rumah panas dan rumah hijau sangat baik untuk membantu tumbuhan tumbuh.

> 🎓 Rumah panas dan rumah hijau melakukan tugas yang serupa, tetapi dengan perbezaan penting. Rumah panas dipanaskan secara buatan dan membolehkan petani mengawal suhu dengan lebih tepat, rumah hijau bergantung pada matahari untuk kehangatan dan biasanya kawalan hanya melalui tingkap atau bukaan lain untuk melepaskan haba.

Tumbuhan mempunyai suhu asas atau minimum, suhu optimum, dan suhu maksimum, semuanya berdasarkan suhu purata harian.

* Suhu asas - ini adalah suhu purata harian minimum yang diperlukan untuk tumbuhan tumbuh.
* Suhu optimum - ini adalah suhu purata harian terbaik untuk mendapatkan pertumbuhan maksimum.
* Suhu maksimum - ini adalah suhu maksimum yang boleh ditahan oleh tumbuhan. Di atas suhu ini, tumbuhan akan menghentikan pertumbuhannya untuk menjimatkan air dan terus hidup.

> 💁 Ini adalah suhu purata, yang diambil kira dari suhu siang dan malam. Tumbuhan juga memerlukan suhu yang berbeza pada siang dan malam untuk membantu mereka melakukan fotosintesis dengan lebih cekap dan menjimatkan tenaga pada waktu malam.

Setiap spesies tumbuhan mempunyai nilai yang berbeza untuk suhu asas, optimum dan maksimum mereka. Inilah sebabnya mengapa sesetengah tumbuhan berkembang di negara panas, dan yang lain di negara sejuk.

✅ Lakukan sedikit penyelidikan. Untuk mana-mana tumbuhan yang anda ada di taman, sekolah, atau taman tempatan, lihat jika anda boleh mencari suhu asasnya.

![Graf menunjukkan kadar pertumbuhan meningkat apabila suhu meningkat, kemudian menurun apabila suhu terlalu tinggi](../../../../../translated_images/ms/plant-growth-temp-graph.c6d69c9478e6ca83.webp)

Graf di atas menunjukkan contoh graf kadar pertumbuhan terhadap suhu. Sehingga suhu asas, tiada pertumbuhan berlaku. Kadar pertumbuhan meningkat sehingga suhu optimum, kemudian menurun selepas mencapai puncak ini. 

Bentuk graf ini berbeza dari satu spesies tumbuhan ke spesies lain. Ada yang mempunyai penurunan mendadak di atas suhu optimum, ada yang mempunyai peningkatan perlahan dari suhu asas ke suhu optimum.

> 💁 Untuk petani mendapatkan pertumbuhan terbaik, mereka perlu mengetahui tiga nilai suhu dan memahami bentuk graf untuk tumbuhan yang mereka tanam.

Jika seorang petani mempunyai kawalan terhadap suhu, contohnya dalam rumah panas komersial, maka mereka boleh mengoptimumkan untuk tumbuhan mereka. Sebagai contoh, rumah panas komersial yang menanam tomato akan menetapkan suhu sekitar 25°C pada siang hari dan 20°C pada waktu malam untuk mendapatkan pertumbuhan terpantas.

> 🍅 Dengan menggabungkan suhu ini dengan lampu buatan, baja dan kawalan tahap CO
Kod ini membuka fail CSV, kemudian menambah baris baru di hujungnya. Baris tersebut mengandungi tarikh dan masa semasa yang diformatkan dalam format yang mudah dibaca manusia, diikuti oleh suhu yang diterima daripada peranti IoT. Data disimpan dalam [format ISO 8601](https://wikipedia.org/wiki/ISO_8601) dengan zon waktu, tetapi tanpa mikrodetik.

1. Jalankan kod ini seperti sebelumnya, pastikan peranti IoT anda menghantar data. Fail CSV bernama `temperature.csv` akan dicipta dalam folder yang sama. Jika anda melihatnya, anda akan melihat tarikh/masa dan ukuran suhu:

    ```output
    date,temperature
    2021-04-19T17:21:36-07:00,25
    2021-04-19T17:31:36-07:00,24
    2021-04-19T17:41:36-07:00,25
    ```

1. Jalankan kod ini untuk beberapa waktu untuk menangkap data. Sebaiknya anda jalankan ini sepanjang hari untuk mengumpulkan data yang mencukupi bagi pengiraan GDD.

    
> 💁 Jika anda menggunakan Peranti IoT Maya, pilih kotak semak rawak dan tetapkan julat untuk mengelakkan mendapatkan suhu yang sama setiap kali nilai suhu dikembalikan.
    ![Pilih kotak semak rawak dan tetapkan julat](../../../../../translated_images/ms/select-the-random-checkbox-and-set-a-range.32cf4bc7c12e797f.webp) 

    > 💁 Jika anda ingin menjalankan ini sepanjang hari, maka anda perlu memastikan komputer tempat kod pelayan anda berjalan tidak akan tidur, sama ada dengan menukar tetapan kuasa anda, atau menjalankan sesuatu seperti [skrip Python ini untuk memastikan sistem aktif](https://github.com/jaqsparow/keep-system-active).
    
> 💁 Anda boleh menemui kod ini dalam folder [code-server/temperature-sensor-server](../../../../../2-farm/lessons/1-predict-plant-growth/code-server/temperature-sensor-server).

### Tugasan - kira GDD menggunakan data yang disimpan

Setelah pelayan menangkap data suhu, GDD untuk tumbuhan boleh dikira.

Langkah-langkah untuk melakukannya secara manual adalah:

1. Cari suhu asas untuk tumbuhan. Sebagai contoh, untuk strawberi suhu asasnya ialah 10°C.

1. Daripada `temperature.csv`, cari suhu tertinggi dan terendah untuk hari tersebut.

1. Gunakan pengiraan GDD yang diberikan sebelum ini untuk mengira GDD.

Sebagai contoh, jika suhu tertinggi untuk hari tersebut ialah 25°C, dan terendah ialah 12°C:

![GDD = 25 + 12 dibahagi dengan 2, kemudian tolak 10 daripada hasil memberikan 8.5](../../../../../translated_images/ms/gdd-calculation-strawberries.59f57db94b22adb8ff6efb951ace33af104a1c6ccca3ffb0f8169c14cb160c90.png)

* 25 + 12 = 37
* 37 / 2 = 18.5
* 18.5 - 10 = 8.5

Oleh itu, strawberi telah menerima **8.5** GDD. Strawberi memerlukan kira-kira 250 GDD untuk berbuah, jadi masih ada masa lagi.

---

## 🚀 Cabaran

Tumbuhan memerlukan lebih daripada haba untuk tumbuh. Apakah perkara lain yang diperlukan?

Untuk perkara ini, cari jika terdapat sensor yang boleh mengukurnya. Bagaimana pula dengan penggerak untuk mengawal tahap ini? Bagaimana anda akan menggabungkan satu atau lebih peranti IoT untuk mengoptimumkan pertumbuhan tumbuhan?

## Kuiz selepas kuliah

[Kuiz selepas kuliah](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/10)

## Ulasan & Kajian Kendiri

* Baca lebih lanjut tentang pertanian digital di [halaman Wikipedia Pertanian Digital](https://wikipedia.org/wiki/Digital_agriculture). Juga baca lebih lanjut tentang pertanian tepat di [halaman Wikipedia Pertanian Tepat](https://wikipedia.org/wiki/Precision_agriculture).
* Pengiraan hari darjah tumbuh penuh lebih rumit daripada yang dipermudahkan di sini. Baca lebih lanjut tentang persamaan yang lebih rumit dan cara menangani suhu di bawah garis dasar di [halaman Wikipedia Hari Darjah Tumbuh](https://wikipedia.org/wiki/Growing_degree-day).
* Makanan mungkin menjadi terhad pada masa depan jika kita masih menggunakan kaedah yang sama untuk bertani. Ketahui lebih lanjut tentang teknik pertanian berteknologi tinggi dalam [video Ladang Berteknologi Tinggi Masa Depan di YouTube](https://www.youtube.com/watch?v=KIEOuKD9KX8).

## Tugasan

[Visualisasikan data GDD menggunakan Jupyter Notebook](assignment.md)

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat penting, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.