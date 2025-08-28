<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1a85e50c33c38dcd2cde2a97d132f248",
  "translation_date": "2025-08-27T22:48:02+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/assignment.md",
  "language_code": "id"
}
-->
# Membangun Detektor Kualitas Buah

## Instruksi

Bangun detektor kualitas buah!

Gunakan semua yang telah Anda pelajari sejauh ini untuk membuat prototipe detektor kualitas buah. Aktifkan klasifikasi gambar berdasarkan kedekatan menggunakan model AI yang berjalan di perangkat edge, simpan hasil klasifikasi di penyimpanan, dan kendalikan LED berdasarkan tingkat kematangan buah.

Anda seharusnya dapat menyusun ini menggunakan kode yang telah Anda tulis di semua pelajaran sebelumnya.

## Rubrik

| Kriteria | Unggul | Memadai | Perlu Peningkatan |
| -------- | ------- | -------- | ----------------- |
| Mengonfigurasi semua layanan | Berhasil mengatur IoT Hub, aplikasi fungsi Azure, dan penyimpanan Azure | Berhasil mengatur IoT Hub, tetapi tidak aplikasi fungsi Azure atau penyimpanan Azure | Tidak berhasil mengatur layanan IoT internet apa pun |
| Memantau kedekatan dan mengirim data ke IoT Hub jika objek lebih dekat dari jarak yang telah ditentukan, serta memicu kamera melalui perintah | Berhasil mengukur jarak dan mengirim pesan ke IoT Hub saat objek cukup dekat, serta mengirim perintah untuk memicu kamera | Berhasil mengukur kedekatan dan mengirim ke IoT Hub, tetapi tidak dapat mengirim perintah ke kamera | Tidak berhasil mengukur jarak dan mengirim pesan ke IoT Hub, atau memicu perintah |
| Mengambil gambar, mengklasifikasikannya, dan mengirim hasilnya ke IoT Hub | Berhasil mengambil gambar, mengklasifikasikannya menggunakan perangkat edge, dan mengirim hasilnya ke IoT Hub | Berhasil mengklasifikasikan gambar tetapi tidak menggunakan perangkat edge, atau tidak dapat mengirim hasilnya ke IoT Hub | Tidak berhasil mengklasifikasikan gambar |
| Menyalakan atau mematikan LED tergantung pada hasil klasifikasi menggunakan perintah yang dikirim ke perangkat | Berhasil menyalakan LED melalui perintah jika buah belum matang | Berhasil mengirim perintah ke perangkat tetapi tidak dapat mengontrol LED | Tidak berhasil mengirim perintah untuk mengontrol LED |

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.