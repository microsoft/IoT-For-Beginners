<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1a85e50c33c38dcd2cde2a97d132f248",
  "translation_date": "2025-08-27T21:18:49+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/assignment.md",
  "language_code": "ms"
}
-->
# Bina pengesan kualiti buah

## Arahan

Bina pengesan kualiti buah!

Gunakan semua yang telah anda pelajari setakat ini untuk membina prototaip pengesan kualiti buah. Aktifkan klasifikasi imej berdasarkan jarak menggunakan model AI yang berjalan di edge, simpan hasil klasifikasi dalam storan, dan kawal LED berdasarkan tahap kematangan buah.

Anda sepatutnya dapat menyusun ini menggunakan kod yang telah anda tulis dalam semua pelajaran sebelum ini.

## Rubrik

| Kriteria | Cemerlang | Memadai | Perlu Penambahbaikan |
| -------- | --------- | -------- | -------------------- |
| Konfigurasi semua perkhidmatan | Berjaya menyediakan IoT Hub, aplikasi fungsi Azure dan storan Azure | Berjaya menyediakan IoT Hub, tetapi tidak aplikasi fungsi Azure atau storan Azure | Tidak berjaya menyediakan sebarang perkhidmatan IoT internet |
| Pantau jarak dan hantar data ke IoT Hub jika objek lebih dekat daripada jarak yang telah ditetapkan dan aktifkan kamera melalui arahan | Berjaya mengukur jarak dan menghantar mesej ke IoT Hub apabila objek cukup dekat, serta menghantar arahan untuk mengaktifkan kamera | Berjaya mengukur jarak dan menghantar ke IoT Hub, tetapi tidak dapat menghantar arahan ke kamera | Tidak berjaya mengukur jarak dan menghantar mesej ke IoT Hub, atau mengaktifkan arahan |
| Tangkap imej, klasifikasikan dan hantar hasilnya ke IoT Hub | Berjaya menangkap imej, mengklasifikasikannya menggunakan peranti edge dan menghantar hasilnya ke IoT Hub | Berjaya mengklasifikasikan imej tetapi tidak menggunakan peranti edge, atau tidak berjaya menghantar hasilnya ke IoT Hub | Tidak berjaya mengklasifikasikan imej |
| Hidupkan atau matikan LED bergantung kepada hasil klasifikasi menggunakan arahan yang dihantar ke peranti | Berjaya menghidupkan LED melalui arahan jika buah tidak masak | Berjaya menghantar arahan ke peranti tetapi tidak dapat mengawal LED | Tidak berjaya menghantar arahan untuk mengawal LED |

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.