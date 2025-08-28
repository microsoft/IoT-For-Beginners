<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ed0fbd6aed084bfba7d5e2f206968c50",
  "translation_date": "2025-08-27T21:35:54+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/assignment.md",
  "language_code": "id"
}
-->
# Membangun Siklus Penyiraman yang Lebih Efisien

## Instruksi

Pelajaran ini membahas cara mengontrol relay menggunakan data sensor, di mana relay tersebut dapat mengontrol pompa untuk sistem irigasi. Untuk sebidang tanah tertentu, menjalankan pompa selama waktu tertentu seharusnya selalu memiliki dampak yang sama pada kelembapan tanah. Ini berarti Anda dapat memperkirakan berapa detik irigasi yang diperlukan untuk menghasilkan penurunan tertentu pada pembacaan kelembapan tanah. Dengan data ini, Anda dapat membangun sistem irigasi yang lebih terkontrol.

Untuk tugas ini, Anda akan menghitung berapa lama pompa harus berjalan untuk menghasilkan peningkatan tertentu pada kelembapan tanah.

> ⚠️ Jika Anda menggunakan perangkat IoT virtual, Anda dapat mengikuti proses ini, tetapi hasilnya disimulasikan dengan meningkatkan pembacaan kelembapan tanah secara manual dengan jumlah tetap per detik saat relay menyala.

1. Mulailah dengan tanah yang kering. Ukur kelembapan tanah.

1. Tambahkan sejumlah air tetap, baik dengan menjalankan pompa selama 1 detik atau dengan menuangkan jumlah tetap.

    > Pompa harus selalu berjalan pada kecepatan konstan, sehingga setiap detik pompa berjalan, ia harus menyuplai jumlah air yang sama.

1. Tunggu hingga tingkat kelembapan tanah stabil dan ambil pembacaan.

1. Ulangi langkah ini beberapa kali dan buat tabel hasilnya. Contoh tabel diberikan di bawah ini.

    | Total Waktu Pompa | Kelembapan Tanah | Penurunan |
    | --- | --: | -: |
    | Kering | 643 |  0 |
    | 1s  | 621 | 22 |
    | 2s  | 601 | 20 |
    | 3s  | 579 | 22 |
    | 4s  | 560 | 19 |
    | 5s  | 539 | 21 |
    | 6s  | 521 | 18 |

1. Hitung rata-rata peningkatan kelembapan tanah per detik air. Dalam contoh di atas, setiap detik air menurunkan pembacaan rata-rata sebesar 20,3.

1. Gunakan data ini untuk meningkatkan efisiensi kode server Anda, dengan menjalankan pompa selama waktu yang diperlukan untuk mencapai tingkat kelembapan tanah yang diinginkan.

## Rubrik

| Kriteria | Unggul | Memadai | Perlu Peningkatan |
| -------- | ------- | -------- | ----------------- |
| Menangkap data kelembapan tanah | Mampu menangkap beberapa pembacaan setelah menambahkan jumlah air tetap | Mampu menangkap beberapa pembacaan dengan jumlah air tetap | Hanya mampu menangkap satu atau dua pembacaan, atau tidak dapat menggunakan jumlah air tetap |
| Kalibrasi kode server | Mampu menghitung rata-rata penurunan pembacaan kelembapan tanah dan memperbarui kode server untuk menggunakannya | Mampu menghitung rata-rata penurunan, tetapi tidak dapat memperbarui kode server, atau tidak dapat menghitung rata-rata dengan benar, tetapi menggunakan nilai ini untuk memperbarui kode server dengan benar | Tidak mampu menghitung rata-rata, atau memperbarui kode server |

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.