<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-27T23:57:10+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "id"
}
-->
# Menyelidiki pengikatan fungsi

## Instruksi

Pengikatan fungsi memungkinkan kode Anda menyimpan blob ke penyimpanan blob dengan mengembalikannya dari fungsi `main`. Akun Azure Storage, koleksi, dan detail lainnya dikonfigurasi dalam file `function.json`.

Saat bekerja dengan Azure atau teknologi Microsoft lainnya, sumber informasi terbaik adalah [dokumentasi Microsoft di docs.com](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn). Dalam tugas ini, Anda perlu membaca dokumentasi pengikatan Azure Functions untuk memahami cara mengatur pengikatan output.

Beberapa halaman yang dapat Anda lihat untuk memulai adalah:

* [Konsep pemicu dan pengikatan Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Ikhtisar pengikatan penyimpanan blob untuk Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Pengikatan output penyimpanan blob untuk Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## Rubrik

| Kriteria | Unggul | Memadai | Perlu Peningkatan |
| -------- | ------- | -------- | ----------------- |
| Mengonfigurasi pengikatan output penyimpanan blob | Berhasil mengonfigurasi pengikatan output, mengembalikan blob, dan menyimpannya di penyimpanan blob dengan sukses | Berhasil mengonfigurasi pengikatan output, atau mengembalikan blob tetapi tidak berhasil menyimpannya di penyimpanan blob | Tidak berhasil mengonfigurasi pengikatan output |

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.