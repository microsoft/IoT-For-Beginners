<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "701f4a4466f9309b6e1d863077df0c06",
  "translation_date": "2025-08-27T23:44:36+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/assignment.md",
  "language_code": "id"
}
-->
# Membangun penerjemah universal

## Instruksi

Penerjemah universal adalah perangkat yang dapat menerjemahkan antara berbagai bahasa, memungkinkan orang yang berbicara dalam bahasa berbeda untuk berkomunikasi. Gunakan apa yang telah Anda pelajari selama beberapa pelajaran terakhir untuk membangun penerjemah universal menggunakan 2 perangkat IoT.

> Jika Anda tidak memiliki 2 perangkat, ikuti langkah-langkah dalam beberapa pelajaran sebelumnya untuk mengatur perangkat IoT virtual sebagai salah satu perangkat IoT.

Anda harus mengonfigurasi satu perangkat untuk satu bahasa, dan satu perangkat untuk bahasa lainnya. Setiap perangkat harus menerima ucapan, mengonversinya menjadi teks, mengirimkannya ke perangkat lain melalui IoT Hub dan aplikasi Functions, lalu menerjemahkannya dan memutar ucapan yang telah diterjemahkan.

> 💁 Tip: Saat mengirim ucapan dari satu perangkat ke perangkat lain, kirimkan juga informasi tentang bahasa yang digunakan, sehingga lebih mudah untuk diterjemahkan. Anda bahkan dapat membuat setiap perangkat mendaftar menggunakan IoT Hub dan aplikasi Functions terlebih dahulu, dengan mengirimkan bahasa yang mereka dukung untuk disimpan di Azure Storage. Anda kemudian dapat menggunakan aplikasi Functions untuk melakukan terjemahan, mengirimkan teks yang telah diterjemahkan ke perangkat IoT.

## Rubrik

| Kriteria | Unggul | Memadai | Perlu Peningkatan |
| -------- | ------- | -------- | ----------------- |
| Membuat penerjemah universal | Berhasil membangun penerjemah universal, mengonversi ucapan yang terdeteksi oleh satu perangkat menjadi ucapan yang diputar oleh perangkat lain dalam bahasa yang berbeda | Berhasil membuat beberapa komponen bekerja, seperti menangkap ucapan atau menerjemahkan, tetapi tidak berhasil membangun solusi menyeluruh | Tidak berhasil membuat bagian apa pun dari penerjemah universal yang berfungsi |

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.