<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b73fe10ec6b580fba2affb6f6e0a5c4d",
  "translation_date": "2025-08-27T23:10:02+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/README.md",
  "language_code": "id"
}
-->
# Atur Timer dan Berikan Umpan Balik Lisan

![Sketchnote ringkasan pelajaran ini](../../../../../translated_images/id/lesson-23.f38483e1d4df4828990d3f02d60e46c978b075d384ae7cb4f7bab738e107c850.jpg)

> Sketchnote oleh [Nitya Narasimhan](https://github.com/nitya). Klik gambar untuk versi yang lebih besar.

## Kuis Pra-Pelajaran

[Kuis Pra-Pelajaran](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/45)

## Pendahuluan

Asisten pintar bukanlah perangkat komunikasi satu arah. Anda berbicara kepada mereka, dan mereka merespons:

"Alexa, atur timer selama 3 menit"

"Ok, timer Anda telah diatur selama 3 menit"

Dalam dua pelajaran terakhir, Anda telah belajar bagaimana mengambil ucapan dan mengubahnya menjadi teks, lalu mengekstrak permintaan pengaturan timer dari teks tersebut. Dalam pelajaran ini, Anda akan belajar cara mengatur timer pada perangkat IoT, merespons pengguna dengan kata-kata lisan yang mengonfirmasi timer mereka, dan memberi tahu mereka saat timer selesai.

Dalam pelajaran ini, kita akan membahas:

* [Teks ke Ucapan](../../../../../6-consumer/lessons/3-spoken-feedback)
* [Mengatur Timer](../../../../../6-consumer/lessons/3-spoken-feedback)
* [Mengonversi Teks ke Ucapan](../../../../../6-consumer/lessons/3-spoken-feedback)

## Teks ke Ucapan

Teks ke ucapan, seperti namanya, adalah proses mengonversi teks menjadi audio yang berisi kata-kata yang diucapkan. Prinsip dasarnya adalah memecah kata-kata dalam teks menjadi bunyi-bunyi penyusunnya (dikenal sebagai fonem), dan menyatukan audio untuk bunyi-bunyi tersebut, baik menggunakan audio yang telah direkam sebelumnya atau menggunakan audio yang dihasilkan oleh model AI.

![Tiga tahap sistem teks ke ucapan](../../../../../translated_images/id/tts-overview.193843cf3f5ee09f.webp)

Sistem teks ke ucapan biasanya memiliki 3 tahap:

* Analisis teks
* Analisis linguistik
* Pembuatan gelombang suara

### Analisis Teks

Analisis teks melibatkan pengambilan teks yang diberikan dan mengonversinya menjadi kata-kata yang dapat digunakan untuk menghasilkan ucapan. Sebagai contoh, jika Anda mengonversi "Hello world", tidak diperlukan analisis teks, dua kata tersebut dapat langsung diubah menjadi ucapan. Namun, jika Anda memiliki "1234", maka ini mungkin perlu diubah menjadi "Seribu dua ratus tiga puluh empat" atau "Satu, dua, tiga, empat" tergantung pada konteksnya. Untuk "Saya punya 1234 apel", maka akan menjadi "Seribu dua ratus tiga puluh empat", tetapi untuk "Anak itu menghitung 1234" maka akan menjadi "Satu, dua, tiga, empat".

Kata-kata yang dihasilkan tidak hanya bervariasi berdasarkan bahasa, tetapi juga berdasarkan lokal bahasa tersebut. Sebagai contoh, dalam Bahasa Inggris Amerika, 120 akan menjadi "One hundred twenty", sedangkan dalam Bahasa Inggris Britania akan menjadi "One hundred and twenty", dengan penggunaan "and" setelah ratusan.

✅ Beberapa contoh lain yang memerlukan analisis teks termasuk "in" sebagai singkatan dari inci, dan "st" sebagai singkatan dari santo atau jalan. Bisakah Anda memikirkan contoh lain dalam bahasa Anda tentang kata-kata yang ambigu tanpa konteks?

Setelah kata-kata didefinisikan, mereka dikirim untuk analisis linguistik.

### Analisis Linguistik

Analisis linguistik memecah kata-kata menjadi fonem. Fonem tidak hanya berdasarkan huruf yang digunakan, tetapi juga huruf lain dalam kata tersebut. Sebagai contoh, dalam Bahasa Inggris, bunyi 'a' dalam 'car' dan 'care' berbeda. Bahasa Inggris memiliki 44 fonem berbeda untuk 26 huruf dalam alfabet, beberapa berbagi fonem yang sama, seperti fonem yang sama digunakan pada awal kata 'circle' dan 'serpent'.

✅ Lakukan penelitian: Apa saja fonem dalam bahasa Anda?

Setelah kata-kata diubah menjadi fonem, fonem ini memerlukan data tambahan untuk mendukung intonasi, menyesuaikan nada atau durasi tergantung pada konteks. Salah satu contohnya adalah dalam Bahasa Inggris, peningkatan nada dapat digunakan untuk mengubah kalimat menjadi pertanyaan, dengan nada yang naik pada kata terakhir menyiratkan pertanyaan.

Sebagai contoh - kalimat "You have an apple" adalah pernyataan yang mengatakan bahwa Anda memiliki apel. Jika nada naik di akhir, meningkat pada kata "apple", itu menjadi pertanyaan "You have an apple?", menanyakan apakah Anda memiliki apel. Analisis linguistik perlu menggunakan tanda tanya di akhir untuk memutuskan menaikkan nada.

Setelah fonem dihasilkan, mereka dapat dikirim untuk pembuatan gelombang suara untuk menghasilkan output audio.

### Pembuatan Gelombang Suara

Sistem teks ke ucapan elektronik pertama menggunakan rekaman audio tunggal untuk setiap fonem, menghasilkan suara yang sangat monoton dan seperti robot. Analisis linguistik akan menghasilkan fonem, fonem ini akan dimuat dari database suara dan disatukan untuk membuat audio.

✅ Lakukan penelitian: Temukan beberapa rekaman audio dari sistem sintesis ucapan awal. Bandingkan dengan sintesis ucapan modern, seperti yang digunakan dalam asisten pintar.

Pembuatan gelombang suara modern menggunakan model pembelajaran mesin (ML) yang dibangun menggunakan pembelajaran mendalam (jaringan saraf yang sangat besar yang bertindak mirip dengan neuron di otak) untuk menghasilkan suara yang lebih alami yang sulit dibedakan dari manusia.

> 💁 Beberapa model ML ini dapat dilatih ulang menggunakan pembelajaran transfer untuk terdengar seperti orang sungguhan. Ini berarti menggunakan suara sebagai sistem keamanan, sesuatu yang semakin banyak digunakan oleh bank, bukan lagi ide yang baik karena siapa pun dengan rekaman beberapa menit suara Anda dapat meniru Anda.

Model ML besar ini sedang dilatih untuk menggabungkan ketiga langkah menjadi sistem sintesis ucapan ujung-ke-ujung.

## Mengatur Timer

Untuk mengatur timer, perangkat IoT Anda perlu memanggil endpoint REST yang Anda buat menggunakan kode serverless, lalu menggunakan jumlah detik yang dihasilkan untuk mengatur timer.

### Tugas - Memanggil fungsi serverless untuk mendapatkan waktu timer

Ikuti panduan yang relevan untuk memanggil endpoint REST dari perangkat IoT Anda dan mengatur timer untuk waktu yang diperlukan:

* [Arduino - Wio Terminal](wio-terminal-set-timer.md)
* [Komputer papan tunggal - Raspberry Pi/Perangkat IoT Virtual](single-board-computer-set-timer.md)

## Mengonversi Teks ke Ucapan

Layanan ucapan yang sama yang Anda gunakan untuk mengonversi ucapan menjadi teks dapat digunakan untuk mengonversi teks kembali menjadi ucapan, dan ini dapat diputar melalui speaker di perangkat IoT Anda. Teks yang akan dikonversi dikirim ke layanan ucapan, bersama dengan jenis audio yang diperlukan (seperti tingkat sampel), dan data biner yang berisi audio dikembalikan.

Saat Anda mengirim permintaan ini, Anda mengirimnya menggunakan *Speech Synthesis Markup Language* (SSML), bahasa markup berbasis XML untuk aplikasi sintesis ucapan. Ini tidak hanya mendefinisikan teks yang akan dikonversi, tetapi juga bahasa teks, suara yang akan digunakan, dan bahkan dapat digunakan untuk mendefinisikan kecepatan, volume, dan nada untuk beberapa atau semua kata dalam teks.

Sebagai contoh, SSML ini mendefinisikan permintaan untuk mengonversi teks "Timer Anda selama 3 menit 5 detik telah diatur" menjadi ucapan menggunakan suara Bahasa Inggris Britania bernama `en-GB-MiaNeural`

```xml
<speak version='1.0' xml:lang='en-GB'>
    <voice xml:lang='en-GB' name='en-GB-MiaNeural'>
        Your 3 minute 5 second time has been set
    </voice>
</speak>
```

> 💁 Sebagian besar sistem teks ke ucapan memiliki beberapa suara untuk berbagai bahasa, dengan aksen yang relevan seperti suara Bahasa Inggris Britania dengan aksen Inggris dan suara Bahasa Inggris Selandia Baru dengan aksen Selandia Baru.

### Tugas - Mengonversi teks ke ucapan

Kerjakan panduan yang relevan untuk mengonversi teks ke ucapan menggunakan perangkat IoT Anda:

* [Arduino - Wio Terminal](wio-terminal-text-to-speech.md)
* [Komputer papan tunggal - Raspberry Pi](pi-text-to-speech.md)
* [Komputer papan tunggal - Perangkat virtual](virtual-device-text-to-speech.md)

---

## 🚀 Tantangan

SSML memiliki cara untuk mengubah bagaimana kata-kata diucapkan, seperti menambahkan penekanan pada kata-kata tertentu, menambahkan jeda, atau mengubah nada. Cobalah beberapa dari ini, kirimkan SSML yang berbeda dari perangkat IoT Anda dan bandingkan hasilnya. Anda dapat membaca lebih lanjut tentang SSML, termasuk cara mengubah cara kata-kata diucapkan dalam [Spesifikasi Speech Synthesis Markup Language (SSML) Versi 1.1 dari World Wide Web Consortium](https://www.w3.org/TR/speech-synthesis11/).

## Kuis Pasca-Pelajaran

[Kuis Pasca-Pelajaran](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/46)

## Tinjauan & Studi Mandiri

* Baca lebih lanjut tentang sintesis ucapan di [halaman sintesis ucapan di Wikipedia](https://wikipedia.org/wiki/Speech_synthesis)
* Baca lebih lanjut tentang cara penjahat menggunakan sintesis ucapan untuk mencuri di [berita 'suara palsu membantu penjahat siber mencuri uang' di BBC](https://www.bbc.com/news/technology-48908736)
* Pelajari lebih lanjut tentang risiko bagi pengisi suara dari versi sintetis suara mereka dalam [artikel ini tentang gugatan TikTok yang menyoroti bagaimana AI merugikan pengisi suara di Vice](https://www.vice.com/en/article/z3xqwj/this-tiktok-lawsuit-is-highlighting-how-ai-is-screwing-over-voice-actors)

## Tugas

[Batalkan timer](assignment.md)

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.