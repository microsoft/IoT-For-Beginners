<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3764e089adf2d5801272bc0895f8498b",
  "translation_date": "2025-08-27T20:50:24+00:00",
  "source_file": "4-manufacturing/README.md",
  "language_code": "id"
}
-->
# Manufaktur dan Pemrosesan - menggunakan IoT untuk meningkatkan pemrosesan makanan

Setelah makanan mencapai pusat distribusi atau pabrik pengolahan, makanan tersebut tidak selalu langsung dikirim ke supermarket. Sering kali, makanan melalui sejumlah langkah pemrosesan, seperti penyortiran berdasarkan kualitas. Ini adalah proses yang dulunya dilakukan secara manual - dimulai di ladang ketika para pemetik hanya memetik buah yang matang, lalu di pabrik buah tersebut akan berjalan di atas ban berjalan dan karyawan secara manual akan mengeluarkan buah yang memar atau busuk. Setelah pernah memetik dan menyortir stroberi sendiri sebagai pekerjaan musim panas saat sekolah, saya bisa bersaksi bahwa ini bukan pekerjaan yang menyenangkan.

Pengaturan yang lebih modern mengandalkan IoT untuk penyortiran. Beberapa perangkat paling awal seperti penyortir dari [Weco](https://wecotek.com) menggunakan sensor optik untuk mendeteksi kualitas hasil panen, misalnya menolak tomat hijau. Perangkat ini dapat digunakan di mesin pemanen di ladang itu sendiri, atau di pabrik pengolahan.

Seiring dengan kemajuan dalam Kecerdasan Buatan (AI) dan Pembelajaran Mesin (ML), mesin-mesin ini dapat menjadi lebih canggih, menggunakan model ML yang dilatih untuk membedakan antara buah dan benda asing seperti batu, tanah, atau serangga. Model ini juga dapat dilatih untuk mendeteksi kualitas buah, tidak hanya buah yang memar tetapi juga deteksi dini penyakit atau masalah tanaman lainnya.

> 🎓 Istilah *model ML* mengacu pada hasil pelatihan perangkat lunak pembelajaran mesin pada satu set data. Sebagai contoh, Anda dapat melatih model ML untuk membedakan antara tomat matang dan belum matang, lalu menggunakan model tersebut pada gambar baru untuk melihat apakah tomat tersebut matang atau tidak.

Dalam 4 pelajaran ini, Anda akan belajar cara melatih model AI berbasis gambar untuk mendeteksi kualitas buah, cara menggunakan model ini dari perangkat IoT, dan cara menjalankannya di edge - yaitu pada perangkat IoT daripada di cloud.

> 💁 Pelajaran ini akan menggunakan beberapa sumber daya cloud. Jika Anda tidak menyelesaikan semua pelajaran dalam proyek ini, pastikan Anda [membersihkan proyek Anda](../clean-up.md).

## Topik

1. [Melatih detektor kualitas buah](./lessons/1-train-fruit-detector/README.md)
1. [Memeriksa kualitas buah dari perangkat IoT](./lessons/2-check-fruit-from-device/README.md)
1. [Menjalankan detektor buah Anda di edge](./lessons/3-run-fruit-detector-edge/README.md)
1. [Memicu deteksi kualitas buah dari sensor](./lessons/4-trigger-fruit-detector/README.md)

## Kredit

Semua pelajaran ditulis dengan ♥️ oleh [Jen Fox](https://github.com/jenfoxbot) dan [Jim Bennett](https://GitHub.com/JimBobBennett)

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.