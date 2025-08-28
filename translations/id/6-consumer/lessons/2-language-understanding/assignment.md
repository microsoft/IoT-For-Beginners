<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a7262a0c48dfacdfe1ff91b20bf16fd",
  "translation_date": "2025-08-27T23:08:12+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/assignment.md",
  "language_code": "id"
}
-->
# Batalkan Timer

## Instruksi

Sejauh ini dalam pelajaran ini, Anda telah melatih model untuk memahami pengaturan timer. Fitur lain yang berguna adalah membatalkan timer - mungkin roti Anda sudah matang dan bisa dikeluarkan dari oven sebelum timer selesai.

Tambahkan intent baru ke aplikasi LUIS Anda untuk membatalkan timer. Intent ini tidak memerlukan entitas apa pun, tetapi memerlukan beberapa contoh kalimat. Tangani ini dalam kode serverless Anda jika intent ini terdeteksi sebagai intent utama, catat bahwa intent telah dikenali, dan kembalikan respons yang sesuai.

## Rubrik

| Kriteria | Unggul | Memadai | Perlu Perbaikan |
| -------- | ------- | -------- | ---------------- |
| Menambahkan intent batalkan timer ke aplikasi LUIS | Berhasil menambahkan intent dan melatih model | Berhasil menambahkan intent tetapi tidak melatih model | Tidak berhasil menambahkan intent dan melatih model |
| Menangani intent di aplikasi serverless | Berhasil mendeteksi intent sebagai intent utama dan mencatatnya | Berhasil mendeteksi intent sebagai intent utama | Tidak berhasil mendeteksi intent sebagai intent utama |

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.