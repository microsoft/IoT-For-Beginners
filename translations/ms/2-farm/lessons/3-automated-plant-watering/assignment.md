<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ed0fbd6aed084bfba7d5e2f206968c50",
  "translation_date": "2025-08-27T21:36:07+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/assignment.md",
  "language_code": "ms"
}
-->
# Membina Kitaran Penyiraman yang Lebih Efisien

## Arahan

Pelajaran ini membincangkan cara mengawal relay menggunakan data sensor, dan relay tersebut boleh mengawal pam untuk sistem pengairan. Untuk sekumpulan tanah yang ditentukan, menjalankan pam untuk tempoh masa tertentu seharusnya memberikan kesan yang sama pada kelembapan tanah. Ini bermakna anda boleh mendapatkan gambaran tentang berapa saat pengairan yang bersamaan dengan penurunan tertentu dalam bacaan kelembapan tanah. Dengan menggunakan data ini, anda boleh membina sistem pengairan yang lebih terkawal.

Untuk tugasan ini, anda akan mengira berapa lama pam perlu dijalankan untuk peningkatan tertentu dalam kelembapan tanah.

> ⚠️ Jika anda menggunakan perkakasan IoT maya, anda boleh melalui proses ini, tetapi simulasi hasilnya dengan meningkatkan bacaan kelembapan tanah secara manual dengan jumlah tetap setiap saat relay dihidupkan.

1. Mulakan dengan tanah yang kering. Ukur kelembapan tanah.

1. Tambahkan jumlah air yang tetap, sama ada dengan menjalankan pam selama 1 saat atau dengan menuangkan jumlah tetap.

    > Pam harus sentiasa beroperasi pada kadar yang tetap, jadi setiap saat pam beroperasi ia harus membekalkan jumlah air yang sama.

1. Tunggu sehingga tahap kelembapan tanah stabil dan ambil bacaan.

1. Ulangi langkah ini beberapa kali dan buat jadual hasilnya. Contoh jadual diberikan di bawah.

    | Jumlah Masa Pam | Kelembapan Tanah | Penurunan |
    | --- | --: | -: |
    | Kering | 643 |  0 |
    | 1s  | 621 | 22 |
    | 2s  | 601 | 20 |
    | 3s  | 579 | 22 |
    | 4s  | 560 | 19 |
    | 5s  | 539 | 21 |
    | 6s  | 521 | 18 |

1. Kira purata peningkatan kelembapan tanah setiap saat air. Dalam contoh di atas, setiap saat air menurunkan bacaan dengan purata 20.3.

1. Gunakan data ini untuk meningkatkan kecekapan kod pelayan anda, menjalankan pam untuk masa yang diperlukan bagi mencapai tahap kelembapan tanah yang diinginkan.

## Rubrik

| Kriteria | Cemerlang | Memadai | Perlu Penambahbaikan |
| -------- | --------- | -------- | -------------------- |
| Menangkap data kelembapan tanah | Berjaya menangkap pelbagai bacaan selepas menambah jumlah air yang tetap | Berjaya menangkap beberapa bacaan dengan jumlah air yang tetap | Hanya mampu menangkap satu atau dua bacaan, atau tidak dapat menggunakan jumlah air yang tetap |
| Menentukur kod pelayan | Berjaya mengira purata penurunan bacaan kelembapan tanah dan mengemas kini kod pelayan untuk menggunakannya | Berjaya mengira purata penurunan, tetapi tidak dapat mengemas kini kod pelayan, atau tidak dapat mengira purata dengan betul tetapi menggunakan nilai ini untuk mengemas kini kod pelayan dengan betul | Tidak dapat mengira purata, atau mengemas kini kod pelayan |

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil maklum bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.