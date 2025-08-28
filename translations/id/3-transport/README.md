<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e978534a245b000725ed2a048f943213",
  "translation_date": "2025-08-27T23:45:15+00:00",
  "source_file": "3-transport/README.md",
  "language_code": "id"
}
-->
# Transportasi dari peternakan ke pabrik - menggunakan IoT untuk melacak pengiriman makanan

Banyak petani menanam makanan untuk dijual - baik mereka adalah petani komersial yang menjual semua hasil panennya, atau petani subsisten yang menjual hasil panen berlebih untuk membeli kebutuhan. Bagaimanapun, makanan harus sampai dari peternakan ke konsumen, dan biasanya ini bergantung pada transportasi massal dari peternakan, ke pusat atau pabrik pengolahan, lalu ke toko. Sebagai contoh, seorang petani tomat akan memanen tomat, mengemasnya ke dalam kotak, memuat kotak ke dalam truk, lalu mengirimkannya ke pabrik pengolahan. Tomat tersebut kemudian akan disortir, dan dari sana dikirimkan ke konsumen dalam bentuk makanan olahan, penjualan ritel, atau dikonsumsi di restoran.

IoT dapat membantu rantai pasokan ini dengan melacak makanan selama transit - memastikan pengemudi pergi ke tempat yang seharusnya, memantau lokasi kendaraan, dan mendapatkan pemberitahuan saat kendaraan tiba sehingga makanan dapat dibongkar dan siap untuk diproses secepat mungkin.

> 🎓 *Rantai pasokan* adalah rangkaian aktivitas untuk membuat dan mengirimkan sesuatu. Sebagai contoh, dalam pertanian tomat, ini mencakup benih, tanah, pasokan pupuk dan air, menanam tomat, mengirimkan tomat ke pusat utama, mengangkutnya ke pusat lokal supermarket, mengangkut ke supermarket individu, menempatkannya di rak pajangan, lalu dijual ke konsumen dan dibawa pulang untuk dimakan. Setiap langkah seperti mata rantai dalam sebuah rantai.

> 🎓 Bagian transportasi dari rantai pasokan dikenal sebagai *logistik*.

Dalam 4 pelajaran ini, Anda akan belajar bagaimana menerapkan Internet of Things untuk meningkatkan rantai pasokan dengan memantau makanan saat dimuat ke dalam truk (virtual), yang dilacak saat bergerak menuju tujuannya. Anda akan belajar tentang pelacakan GPS, cara menyimpan dan memvisualisasikan data GPS, dan cara mendapatkan pemberitahuan saat truk tiba di tujuannya.

> 💁 Pelajaran ini akan menggunakan beberapa sumber daya cloud. Jika Anda tidak menyelesaikan semua pelajaran dalam proyek ini, pastikan Anda [Membersihkan proyek Anda](../clean-up.md).

## Topik

1. [Pelacakan lokasi](lessons/1-location-tracking/README.md)
1. [Menyimpan data lokasi](lessons/2-store-location-data/README.md)
1. [Memvisualisasikan data lokasi](lessons/3-visualize-location-data/README.md)
1. [Geofences](lessons/4-geofences/README.md)

## Kredit

Semua pelajaran ditulis dengan ♥️ oleh [Jen Looper](https://github.com/jlooper) dan [Jim Bennett](https://GitHub.com/JimBobBennett)

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.