<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a94fbab1ba737e9bd6cc6c64f114fa0",
  "translation_date": "2025-08-27T20:34:16+00:00",
  "source_file": "clean-up.md",
  "language_code": "ms"
}
-->
# Bersihkan projek anda

Selepas anda menyelesaikan setiap projek, adalah baik untuk memadamkan sumber awan anda.

Dalam pelajaran untuk setiap projek, anda mungkin telah mencipta beberapa perkara berikut:

* Kumpulan Sumber
* IoT Hub
* Pendaftaran peranti IoT
* Akaun Penyimpanan
* Aplikasi Fungsi
* Akaun Azure Maps
* Projek penglihatan tersuai
* Pendaftaran Kontena Azure
* Sumber perkhidmatan kognitif

Kebanyakan sumber ini tidak akan dikenakan kos - sama ada ia percuma sepenuhnya, atau anda menggunakan tahap percuma. Untuk perkhidmatan yang memerlukan tahap berbayar, anda mungkin telah menggunakannya pada tahap yang termasuk dalam elaun percuma, atau hanya akan dikenakan beberapa sen sahaja.

Walaupun kosnya agak rendah, adalah berbaloi untuk memadamkan sumber ini apabila anda selesai. Sebagai contoh, anda hanya boleh mempunyai satu IoT Hub menggunakan tahap percuma, jadi jika anda ingin mencipta yang lain, anda perlu menggunakan tahap berbayar.

Semua perkhidmatan anda telah dicipta di dalam Kumpulan Sumber, dan ini memudahkan pengurusan. Anda boleh memadamkan Kumpulan Sumber, dan semua perkhidmatan dalam Kumpulan Sumber tersebut akan dipadamkan bersama-sama dengannya.

Untuk memadamkan Kumpulan Sumber, jalankan arahan berikut dalam terminal atau command prompt anda:

```sh
az group delete --name <resource-group-name>
```

Gantikan `<resource-group-name>` dengan nama Kumpulan Sumber yang anda ingin padamkan.

Satu pengesahan akan muncul:

```output
Are you sure you want to perform this operation? (y/n): 
```

Masukkan `y` untuk mengesahkan dan memadamkan Kumpulan Sumber.

Ia akan mengambil masa untuk memadamkan semua perkhidmatan.

> 💁 Anda boleh membaca lebih lanjut tentang memadamkan kumpulan sumber di [dokumentasi pengurusan kumpulan sumber dan pemadaman sumber Azure Resource Manager di Microsoft Docs](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli)

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.