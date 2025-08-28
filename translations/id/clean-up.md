<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a94fbab1ba737e9bd6cc6c64f114fa0",
  "translation_date": "2025-08-27T22:35:00+00:00",
  "source_file": "clean-up.md",
  "language_code": "id"
}
-->
# Bersihkan proyek Anda

Setelah Anda menyelesaikan setiap proyek, ada baiknya untuk menghapus sumber daya cloud Anda.

Dalam pelajaran untuk setiap proyek, Anda mungkin telah membuat beberapa hal berikut:

* Sebuah Resource Group
* Sebuah IoT Hub
* Registrasi perangkat IoT
* Sebuah Storage Account
* Sebuah Functions App
* Sebuah akun Azure Maps
* Sebuah proyek custom vision
* Sebuah Azure Container Registry
* Sebuah sumber daya cognitive services

Sebagian besar sumber daya ini tidak akan dikenakan biaya - baik sepenuhnya gratis, atau Anda menggunakan tingkat gratis. Untuk layanan yang memerlukan tingkat berbayar, Anda mungkin telah menggunakannya pada tingkat yang termasuk dalam kuota gratis, atau hanya akan dikenakan biaya beberapa sen.

Meskipun biayanya relatif rendah, ada baiknya untuk menghapus sumber daya ini ketika Anda selesai. Misalnya, Anda hanya dapat memiliki satu IoT Hub yang menggunakan tingkat gratis, jadi jika Anda ingin membuat yang lain, Anda perlu menggunakan tingkat berbayar.

Semua layanan Anda dibuat di dalam Resource Groups, dan ini membuatnya lebih mudah untuk dikelola. Anda dapat menghapus Resource Group, dan semua layanan di dalam Resource Group tersebut akan dihapus bersamaan.

Untuk menghapus Resource Group, jalankan perintah berikut di terminal atau command prompt Anda:

```sh
az group delete --name <resource-group-name>
```

Ganti `<resource-group-name>` dengan nama Resource Group yang ingin Anda hapus.

Sebuah konfirmasi akan muncul:

```output
Are you sure you want to perform this operation? (y/n): 
```

Masukkan `y` untuk mengonfirmasi dan menghapus Resource Group.

Proses penghapusan semua layanan akan memakan waktu.

> 💁 Anda dapat membaca lebih lanjut tentang penghapusan Resource Group di [dokumentasi penghapusan Resource Group dan sumber daya Azure Resource Manager di Microsoft Docs](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli)

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berupaya untuk memberikan hasil yang akurat, harap diperhatikan bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang berwenang. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan manusia profesional. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.