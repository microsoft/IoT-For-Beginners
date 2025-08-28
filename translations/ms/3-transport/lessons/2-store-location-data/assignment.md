<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-27T23:57:18+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "ms"
}
-->
# Menyiasat Pengikatan Fungsi

## Arahan

Pengikatan fungsi membolehkan kod anda menyimpan blob ke storan blob dengan mengembalikannya daripada fungsi `main`. Akaun Azure Storage, koleksi, dan butiran lain dikonfigurasi dalam fail `function.json`.

Apabila bekerja dengan Azure atau teknologi Microsoft lain, sumber maklumat terbaik ialah [dokumentasi Microsoft di docs.com](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn). Dalam tugasan ini, anda perlu membaca dokumentasi pengikatan Azure Functions untuk memahami cara menyediakan pengikatan output.

Beberapa halaman untuk memulakan ialah:

* [Konsep pencetus dan pengikatan Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Gambaran keseluruhan pengikatan storan Blob Azure untuk Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Pengikatan output storan Blob Azure untuk Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## Rubrik

| Kriteria | Cemerlang | Memadai | Perlu Penambahbaikan |
| -------- | --------- | -------- | -------------------- |
| Mengkonfigurasi pengikatan output storan blob | Berjaya mengkonfigurasi pengikatan output, mengembalikan blob dan menyimpannya ke dalam storan blob dengan jayanya | Berjaya mengkonfigurasi pengikatan output, atau mengembalikan blob tetapi tidak berjaya menyimpannya ke dalam storan blob | Tidak berjaya mengkonfigurasi pengikatan output |

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.