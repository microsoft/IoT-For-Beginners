<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5cb65a6ec4387ed177e145347e8e308e",
  "translation_date": "2025-08-27T23:38:45+00:00",
  "source_file": "3-transport/lessons/4-geofences/assignment.md",
  "language_code": "id"
}
-->
# Kirim Notifikasi Menggunakan Twilio

## Instruksi

Dalam kode Anda sejauh ini, Anda hanya mencatat jarak ke geofence. Dalam tugas ini, Anda perlu menambahkan notifikasi, baik berupa pesan teks atau email, ketika koordinat GPS berada di dalam geofence.

Azure Functions memiliki banyak opsi untuk bindings, termasuk ke layanan pihak ketiga seperti Twilio, sebuah platform komunikasi.

* Daftar untuk akun gratis di [Twilio.com](https://www.twilio.com)
* Baca dokumentasi tentang binding Azure Functions ke Twilio SMS di [halaman dokumentasi Microsoft tentang binding Twilio untuk Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?WT.mc_id=academic-17441-jabenn&tabs=python).
* Baca dokumentasi tentang binding Azure Functions ke Twilio SendGrid untuk mengirim email di [halaman dokumentasi Microsoft tentang binding SendGrid untuk Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?WT.mc_id=academic-17441-jabenn&tabs=python).
* Tambahkan binding ke aplikasi Functions Anda untuk menerima notifikasi pada koordinat GPS yang berada di dalam atau di luar geofence - bukan keduanya.

## Rubrik

| Kriteria | Unggul | Memadai | Perlu Peningkatan |
| -------- | ------- | -------- | ----------------- |
| Mengonfigurasi bindings fungsi dan menerima email atau SMS | Berhasil mengonfigurasi bindings fungsi dan menerima email atau SMS ketika berada di dalam atau di luar geofence, tetapi bukan keduanya | Berhasil mengonfigurasi bindings tetapi tidak dapat mengirim email atau SMS, atau hanya dapat mengirim ketika koordinat berada di dalam dan di luar geofence | Tidak berhasil mengonfigurasi bindings dan mengirim email atau SMS |

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan manusia profesional. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.