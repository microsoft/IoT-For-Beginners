<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "022e21f8629b721424c1de25195fff67",
  "translation_date": "2025-08-27T20:58:09+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/assignment.md",
  "language_code": "id"
}
-->
# Menanggapi hasil klasifikasi

## Instruksi

Perangkat Anda telah mengklasifikasikan gambar dan memiliki nilai untuk prediksi. Perangkat Anda dapat menggunakan informasi ini untuk melakukan sesuatu - misalnya mengirimkannya ke IoT Hub untuk diproses oleh sistem lain, atau mengontrol aktuator seperti LED untuk menyala ketika buah belum matang.

Tambahkan kode ke perangkat Anda untuk merespons dengan cara yang Anda pilih - baik mengirim data ke IoT Hub, mengontrol aktuator, atau menggabungkan keduanya dan mengirim data ke IoT Hub dengan beberapa kode tanpa server yang menentukan apakah buah sudah matang atau belum, lalu mengirimkan perintah kembali untuk mengontrol aktuator.

## Rubrik

| Kriteria | Unggul | Memadai | Perlu Perbaikan |
| -------- | ------ | -------- | --------------- |
| Menanggapi prediksi | Mampu mengimplementasikan respons terhadap prediksi yang bekerja secara konsisten dengan prediksi bernilai sama. | Mampu mengimplementasikan respons yang tidak bergantung pada prediksi, seperti hanya mengirim data mentah ke IoT Hub. | Tidak mampu memprogram perangkat untuk merespons prediksi. |

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.