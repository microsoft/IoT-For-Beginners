<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c16de27b0074abe81d6a8bad5e5b1a6b",
  "translation_date": "2025-08-27T22:57:49+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/README.md",
  "language_code": "id"
}
-->
# Mendukung Banyak Bahasa

![Sketchnote ringkasan pelajaran ini](../../../../../translated_images/id/lesson-24.4246968ed058510ab275052e87ef9aa89c7b2f938915d103c605c04dc6cd5bb7.jpg)

> Sketchnote oleh [Nitya Narasimhan](https://github.com/nitya). Klik gambar untuk versi yang lebih besar.

Video ini memberikan gambaran umum tentang layanan suara Azure, mencakup konversi suara ke teks dan teks ke suara dari pelajaran sebelumnya, serta menerjemahkan suara, topik yang dibahas dalam pelajaran ini:

[![Mengenali suara dengan beberapa baris Python dari Microsoft Build 2020](https://img.youtube.com/vi/h6xbpMPSGEA/0.jpg)](https://www.youtube.com/watch?v=h6xbpMPSGEA)

> 🎥 Klik gambar di atas untuk menonton video

## Kuis Sebelum Pelajaran

[Kuis sebelum pelajaran](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/47)

## Pendahuluan

Dalam 3 pelajaran terakhir, Anda telah mempelajari tentang mengubah suara menjadi teks, memahami bahasa, dan mengubah teks menjadi suara, semuanya didukung oleh AI. Salah satu area komunikasi manusia lainnya yang dapat dibantu oleh AI adalah penerjemahan bahasa - mengubah dari satu bahasa ke bahasa lain, seperti dari Bahasa Inggris ke Bahasa Prancis.

Dalam pelajaran ini, Anda akan belajar tentang menggunakan AI untuk menerjemahkan teks, memungkinkan timer pintar Anda berinteraksi dengan pengguna dalam berbagai bahasa.

Dalam pelajaran ini kita akan membahas:

* [Menerjemahkan teks](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Layanan penerjemahan](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Membuat sumber daya penerjemah](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Mendukung banyak bahasa dalam aplikasi dengan penerjemahan](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Menerjemahkan teks menggunakan layanan AI](../../../../../6-consumer/lessons/4-multiple-language-support)

> 🗑 Ini adalah pelajaran terakhir dalam proyek ini, jadi setelah menyelesaikan pelajaran dan tugas ini, jangan lupa untuk membersihkan layanan cloud Anda. Anda akan membutuhkan layanan tersebut untuk menyelesaikan tugas, jadi pastikan untuk menyelesaikannya terlebih dahulu.
>
> Lihat [panduan membersihkan proyek Anda](../../../clean-up.md) jika diperlukan untuk instruksi tentang cara melakukannya.

## Menerjemahkan Teks

Penerjemahan teks telah menjadi masalah ilmu komputer yang telah diteliti selama lebih dari 70 tahun, dan baru sekarang berkat kemajuan AI dan kekuatan komputer, hampir dapat diselesaikan hingga mendekati kualitas penerjemah manusia.

> 💁 Asal-usulnya dapat ditelusuri lebih jauh, hingga [Al-Kindi](https://wikipedia.org/wiki/Al-Kindi), seorang kriptografer Arab abad ke-9 yang mengembangkan teknik untuk penerjemahan bahasa.

### Penerjemahan Mesin

Penerjemahan teks dimulai sebagai teknologi yang dikenal sebagai Penerjemahan Mesin (MT), yang dapat menerjemahkan antara pasangan bahasa yang berbeda. MT bekerja dengan mengganti kata-kata dalam satu bahasa dengan bahasa lain, menambahkan teknik untuk memilih cara yang tepat dalam menerjemahkan frasa atau bagian kalimat ketika penerjemahan kata-per-kata sederhana tidak masuk akal.

> 🎓 Ketika penerjemah mendukung penerjemahan antara satu bahasa dan bahasa lain, ini dikenal sebagai *pasangan bahasa*. Alat yang berbeda mendukung pasangan bahasa yang berbeda, dan ini mungkin tidak lengkap. Misalnya, penerjemah mungkin mendukung Bahasa Inggris ke Bahasa Spanyol sebagai pasangan bahasa, dan Bahasa Spanyol ke Bahasa Italia sebagai pasangan bahasa, tetapi tidak mendukung Bahasa Inggris ke Bahasa Italia.

Sebagai contoh, menerjemahkan "Hello world" dari Bahasa Inggris ke Bahasa Prancis dapat dilakukan dengan substitusi - "Bonjour" untuk "Hello", dan "le monde" untuk "world", menghasilkan terjemahan yang benar "Bonjour le monde".

Substitusi tidak bekerja ketika bahasa yang berbeda menggunakan cara yang berbeda untuk mengatakan hal yang sama. Misalnya, kalimat Bahasa Inggris "My name is Jim", diterjemahkan menjadi "Je m'appelle Jim" dalam Bahasa Prancis - secara harfiah "Saya memanggil diri saya Jim". "Je" adalah Bahasa Prancis untuk "Saya", "moi" adalah saya, tetapi digabungkan dengan kata kerja karena dimulai dengan huruf vokal, sehingga menjadi "m'", "appelle" adalah memanggil, dan "Jim" tidak diterjemahkan karena itu adalah nama, dan bukan kata yang dapat diterjemahkan. Urutan kata juga menjadi masalah - substitusi sederhana "Je m'appelle Jim" menjadi "I myself call Jim", dengan urutan kata yang berbeda dari Bahasa Inggris.

> 💁 Beberapa kata tidak pernah diterjemahkan - nama saya adalah Jim terlepas dari bahasa yang digunakan untuk memperkenalkan saya. Ketika menerjemahkan ke bahasa yang menggunakan alfabet yang berbeda, atau menggunakan huruf yang berbeda untuk suara yang berbeda, maka kata-kata dapat *ditransliterasi*, yaitu memilih huruf atau karakter yang memberikan suara yang sesuai untuk terdengar sama seperti kata yang diberikan.

Ungkapan juga menjadi masalah dalam penerjemahan. Ini adalah frasa yang memiliki makna yang dipahami yang berbeda dari interpretasi langsung kata-kata. Misalnya, dalam Bahasa Inggris ungkapan "I've got ants in my pants" tidak secara harfiah merujuk pada memiliki semut di pakaian Anda, tetapi pada menjadi gelisah. Jika Anda menerjemahkan ini ke Bahasa Jerman, Anda akan membingungkan pendengar, karena versi Bahasa Jerman adalah "Saya memiliki lebah di bagian bawah".

> 💁 Lokasi yang berbeda menambahkan kompleksitas yang berbeda. Dengan ungkapan "ants in your pants", dalam Bahasa Inggris Amerika "pants" merujuk pada pakaian luar, dalam Bahasa Inggris Britania, "pants" adalah pakaian dalam.

✅ Jika Anda berbicara beberapa bahasa, pikirkan beberapa frasa yang tidak langsung diterjemahkan.

Sistem penerjemahan mesin mengandalkan basis data besar aturan yang menjelaskan cara menerjemahkan frasa dan ungkapan tertentu, bersama dengan metode statistik untuk memilih terjemahan yang sesuai dari opsi yang mungkin. Metode statistik ini menggunakan basis data besar karya yang diterjemahkan oleh manusia ke dalam berbagai bahasa untuk memilih terjemahan yang paling mungkin, sebuah teknik yang disebut *penerjemahan mesin statistik*. Beberapa di antaranya menggunakan representasi bahasa perantara, memungkinkan satu bahasa diterjemahkan ke perantara, lalu dari perantara ke bahasa lain. Dengan cara ini menambahkan lebih banyak bahasa melibatkan penerjemahan ke dan dari perantara, bukan ke dan dari semua bahasa lainnya.

### Penerjemahan Neural

Penerjemahan neural melibatkan penggunaan kekuatan AI untuk menerjemahkan, biasanya menerjemahkan seluruh kalimat menggunakan satu model. Model-model ini dilatih pada kumpulan data besar yang telah diterjemahkan oleh manusia, seperti halaman web, buku, dan dokumentasi Perserikatan Bangsa-Bangsa.

Model penerjemahan neural biasanya lebih kecil daripada model penerjemahan mesin karena tidak membutuhkan basis data besar frasa dan ungkapan. Layanan AI modern yang menyediakan penerjemahan sering kali mencampur berbagai teknik, mencampur penerjemahan mesin statistik dan penerjemahan neural.

Tidak ada terjemahan 1:1 untuk pasangan bahasa mana pun. Model penerjemahan yang berbeda akan menghasilkan hasil yang sedikit berbeda tergantung pada data yang digunakan untuk melatih model. Terjemahan tidak selalu simetris - dalam arti jika Anda menerjemahkan sebuah kalimat dari satu bahasa ke bahasa lain, lalu kembali ke bahasa pertama, Anda mungkin melihat kalimat yang sedikit berbeda sebagai hasilnya.

✅ Coba berbagai penerjemah online seperti [Bing Translate](https://www.bing.com/translator), [Google Translate](https://translate.google.com), atau aplikasi penerjemah Apple. Bandingkan versi terjemahan dari beberapa kalimat. Juga coba menerjemahkan di satu, lalu menerjemahkan kembali di yang lain.

## Layanan Penerjemahan

Ada sejumlah layanan AI yang dapat digunakan dari aplikasi Anda untuk menerjemahkan suara dan teks.

### Layanan Suara Cognitive Services

![Logo layanan suara](../../../../../translated_images/id/azure-speech-logo.a1f08c4befb0159f2cb5d692d3baf5b599e7b44759d316da907bda1508f46a4a.png)

Layanan suara yang telah Anda gunakan selama beberapa pelajaran terakhir memiliki kemampuan penerjemahan untuk pengenalan suara. Ketika Anda mengenali suara, Anda dapat meminta tidak hanya teks dari suara dalam bahasa yang sama, tetapi juga dalam bahasa lain.

> 💁 Ini hanya tersedia dari SDK suara, API REST tidak memiliki penerjemahan bawaan.

### Layanan Penerjemah Cognitive Services

![Logo layanan penerjemah](../../../../../translated_images/id/azure-translator-logo.c6ed3a4a433edfd2f11577eca105412c50b8396b194cbbd730723dd1d0793bcd.png)

Layanan Penerjemah adalah layanan penerjemahan khusus yang dapat menerjemahkan teks dari satu bahasa, ke satu atau lebih bahasa target. Selain menerjemahkan, layanan ini mendukung berbagai fitur tambahan termasuk menyembunyikan kata-kata kasar. Layanan ini juga memungkinkan Anda memberikan terjemahan khusus untuk kata atau kalimat tertentu, untuk bekerja dengan istilah yang tidak ingin Anda terjemahkan, atau memiliki terjemahan yang terkenal.

Sebagai contoh, ketika menerjemahkan kalimat "I have a Raspberry Pi", yang merujuk pada komputer papan tunggal, ke bahasa lain seperti Bahasa Prancis, Anda ingin mempertahankan nama "Raspberry Pi" seperti apa adanya, dan tidak menerjemahkannya, menghasilkan "J’ai un Raspberry Pi" daripada "J’ai une pi aux framboises".

## Membuat Sumber Daya Penerjemah

Untuk pelajaran ini, Anda akan membutuhkan sumber daya Penerjemah. Anda akan menggunakan API REST untuk menerjemahkan teks.

### Tugas - membuat sumber daya penerjemah

1. Dari terminal atau command prompt Anda, jalankan perintah berikut untuk membuat sumber daya penerjemah dalam grup sumber daya `smart-timer` Anda.

    ```sh
    az cognitiveservices account create --name smart-timer-translator \
                                        --resource-group smart-timer \
                                        --kind TextTranslation \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Ganti `<location>` dengan lokasi yang Anda gunakan saat membuat Grup Sumber Daya.

1. Dapatkan kunci untuk layanan penerjemah:

    ```sh
    az cognitiveservices account keys list --name smart-timer-translator \
                                           --resource-group smart-timer \
                                           --output table
    ```

    Salin salah satu kunci.

## Mendukung Banyak Bahasa dalam Aplikasi dengan Penerjemahan

Dalam dunia yang ideal, seluruh aplikasi Anda harus memahami sebanyak mungkin bahasa yang berbeda, mulai dari mendengarkan suara, memahami bahasa, hingga merespons dengan suara. Ini adalah banyak pekerjaan, jadi layanan penerjemahan dapat mempercepat waktu pengiriman aplikasi Anda.

![Arsitektur timer pintar menerjemahkan Bahasa Jepang ke Bahasa Inggris, memproses dalam Bahasa Inggris lalu menerjemahkan kembali ke Bahasa Jepang](../../../../../translated_images/id/translated-smart-timer.08ac20057fdc5c37.webp)

Bayangkan Anda sedang membangun timer pintar yang menggunakan Bahasa Inggris dari awal hingga akhir, memahami Bahasa Inggris yang diucapkan dan mengubahnya menjadi teks, menjalankan pemahaman bahasa dalam Bahasa Inggris, membangun respons dalam Bahasa Inggris, dan merespons dengan suara Bahasa Inggris. Jika Anda ingin menambahkan dukungan untuk Bahasa Jepang, Anda dapat memulai dengan menerjemahkan Bahasa Jepang yang diucapkan ke teks Bahasa Inggris, lalu menjaga inti aplikasi tetap sama, lalu menerjemahkan teks respons ke Bahasa Jepang sebelum mengucapkan respons. Ini akan memungkinkan Anda untuk dengan cepat menambahkan dukungan Bahasa Jepang, dan Anda dapat memperluas untuk menyediakan dukungan Bahasa Jepang penuh dari awal hingga akhir nanti.

> 💁 Kekurangan dari mengandalkan penerjemahan mesin adalah bahwa bahasa dan budaya yang berbeda memiliki cara yang berbeda untuk mengatakan hal yang sama, sehingga terjemahan mungkin tidak sesuai dengan ekspresi yang Anda harapkan.

Penerjemahan mesin juga membuka kemungkinan untuk aplikasi dan perangkat yang dapat menerjemahkan konten yang dibuat pengguna saat dibuat. Fiksi ilmiah secara teratur menampilkan 'penerjemah universal', perangkat yang dapat menerjemahkan dari bahasa alien ke (biasanya) Bahasa Inggris Amerika. Perangkat ini lebih seperti fakta ilmiah daripada fiksi ilmiah, jika Anda mengabaikan bagian alien. Sudah ada aplikasi dan perangkat yang menyediakan penerjemahan waktu nyata dari suara dan teks tertulis, menggunakan kombinasi layanan suara dan penerjemahan.

Salah satu contohnya adalah aplikasi ponsel [Microsoft Translator](https://www.microsoft.com/translator/apps/?WT.mc_id=academic-17441-jabenn), yang didemonstrasikan dalam video ini:

[![Fitur langsung Microsoft Translator dalam aksi](https://img.youtube.com/vi/16yAGeP2FuM/0.jpg)](https://www.youtube.com/watch?v=16yAGeP2FuM)

> 🎥 Klik gambar di atas untuk menonton video

Bayangkan memiliki perangkat seperti itu tersedia untuk Anda, terutama saat bepergian atau berinteraksi dengan orang-orang yang bahasanya tidak Anda ketahui. Memiliki perangkat penerjemahan otomatis di bandara atau rumah sakit akan memberikan peningkatan aksesibilitas yang sangat dibutuhkan.

✅ Lakukan penelitian: Apakah ada perangkat IoT penerjemahan yang tersedia secara komersial? Bagaimana dengan kemampuan penerjemahan yang terintegrasi ke dalam perangkat pintar?

> 👽 Meskipun tidak ada penerjemah universal sejati yang memungkinkan kita berbicara dengan alien, [Microsoft Translator mendukung Klingon](https://www.microsoft.com/translator/blog/2013/05/14/announcing-klingon-for-bing-translator/?WT.mc_id=academic-17441-jabenn). Qapla’!

## Menerjemahkan Teks Menggunakan Layanan AI

Anda dapat menggunakan layanan AI untuk menambahkan kemampuan penerjemahan ini ke timer pintar Anda.

### Tugas - menerjemahkan teks menggunakan layanan AI

Kerjakan panduan yang relevan untuk mengonversi teks terjemahan pada perangkat IoT Anda:

* [Arduino - Wio Terminal](wio-terminal-translate-speech.md)
* [Komputer papan tunggal - Raspberry Pi](pi-translate-speech.md)
* [Komputer papan tunggal - Perangkat virtual](virtual-device-translate-speech.md)

---

## 🚀 Tantangan

Bagaimana penerjemahan mesin dapat bermanfaat bagi aplikasi IoT lainnya selain perangkat pintar? Pikirkan berbagai cara penerjemahan dapat membantu, tidak hanya dengan kata yang diucapkan tetapi juga dengan teks.

## Kuis Setelah Pelajaran

[Kuis setelah pelajaran](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/48)

## Tinjauan & Studi Mandiri

* Baca lebih lanjut tentang penerjemahan mesin di [halaman penerjemahan mesin di Wikipedia](https://wikipedia.org/wiki/Machine_translation)
* Baca lebih lanjut tentang penerjemahan mesin neural di [halaman penerjemahan mesin neural di Wikipedia](https://wikipedia.org/wiki/Neural_machine_translation)
* Lihat daftar bahasa yang didukung untuk layanan suara Microsoft di [dukungan bahasa dan suara untuk dokumentasi layanan suara di Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn)

## Tugas

[Membangun penerjemah universal](assignment.md)

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.