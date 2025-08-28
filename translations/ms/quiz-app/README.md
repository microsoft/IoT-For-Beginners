<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2a459ea9177fb0508ca96068ae1009d2",
  "translation_date": "2025-08-27T23:58:47+00:00",
  "source_file": "quiz-app/README.md",
  "language_code": "ms"
}
-->
# Kuiz

Kuiz-kuiz ini adalah kuiz sebelum dan selepas kuliah untuk kurikulum IoT untuk Pemula di https://aka.ms/iot-beginners

## Tetapan Projek

```
npm install
```

### Kompilasi dan muat semula secara langsung untuk pembangunan

```
npm run serve
```

### Kompilasi dan kecilkan untuk pengeluaran

```
npm run build
```

### Lakukan lint dan perbaiki fail

```
npm run lint
```

### Sesuaikan konfigurasi

Lihat [Rujukan Konfigurasi](https://cli.vuejs.org/config/).

Kredit: Terima kasih kepada versi asal aplikasi kuiz ini: https://github.com/arpan45/simple-quiz-vue


## Melancarkan ke Azure

Berikut adalah panduan langkah demi langkah untuk membantu anda bermula:

1. Fork Repositori GitHub  
Pastikan kod aplikasi web statik anda berada dalam repositori GitHub anda. Fork repositori ini.

2. Cipta Aplikasi Web Statik Azure  
- Cipta akaun [Azure](http://azure.microsoft.com)  
- Pergi ke [portal Azure](https://portal.azure.com)  
- Klik “Create a resource” dan cari “Static Web App”.  
- Klik “Create”.  

3. Konfigurasikan Aplikasi Web Statik  
- Asas:  
  - Langganan: Pilih langganan Azure anda.  
  - Kumpulan Sumber: Cipta kumpulan sumber baru atau gunakan yang sedia ada.  
  - Nama: Berikan nama untuk aplikasi web statik anda.  
  - Wilayah: Pilih wilayah yang paling dekat dengan pengguna anda.  

- #### Butiran Penghantaran:  
  - Sumber: Pilih “GitHub”.  
  - Akaun GitHub: Benarkan Azure mengakses akaun GitHub anda.  
  - Organisasi: Pilih organisasi GitHub anda.  
  - Repositori: Pilih repositori yang mengandungi aplikasi web statik anda.  
  - Cawangan: Pilih cawangan yang anda ingin gunakan untuk penghantaran.  

- #### Butiran Binaan:  
  - Preset Binaan: Pilih rangka kerja yang digunakan oleh aplikasi anda (contohnya, React, Angular, Vue, dll.).  
  - Lokasi Aplikasi: Nyatakan folder yang mengandungi kod aplikasi anda (contohnya, / jika berada di root).  
  - Lokasi API: Jika anda mempunyai API, nyatakan lokasinya (pilihan).  
  - Lokasi Output: Nyatakan folder di mana output binaan dihasilkan (contohnya, build atau dist).  

4. Semak dan Cipta  
Semak tetapan anda dan klik “Create”. Azure akan menyediakan sumber yang diperlukan dan mencipta fail aliran kerja GitHub Actions dalam repositori anda.

5. Aliran Kerja GitHub Actions  
Azure akan secara automatik mencipta fail aliran kerja GitHub Actions dalam repositori anda (.github/workflows/azure-static-web-apps-<name>.yml). Fail ini akan mengendalikan proses binaan dan penghantaran.

6. Pantau Penghantaran  
Pergi ke tab “Actions” dalam repositori GitHub anda.  
Anda sepatutnya melihat aliran kerja sedang berjalan. Aliran kerja ini akan membina dan menghantar aplikasi web statik anda ke Azure.  
Setelah aliran kerja selesai, aplikasi anda akan tersedia secara langsung di URL Azure yang disediakan.

### Contoh Fail Aliran Kerja

Berikut adalah contoh bagaimana fail aliran kerja GitHub Actions mungkin kelihatan:  
name: Azure Static Web Apps CI/CD  
```
on:
  push:
    branches:
      - main
  pull_request:
    types: [opened, synchronize, reopened, closed]
    branches:
      - main

jobs:
  build_and_deploy_job:
    runs-on: ubuntu-latest
    name: Build and Deploy Job
    steps:
      - uses: actions/checkout@v2
      - name: Build And Deploy
        id: builddeploy
        uses: Azure/static-web-apps-deploy@v1
        with:
          azure_static_web_apps_api_token: ${{ secrets.AZURE_STATIC_WEB_APPS_API_TOKEN }}
          repo_token: ${{ secrets.GITHUB_TOKEN }}
          action: "upload"
          app_location: "quiz-app" #App source code path
          api_location: ""API source code path optional
          output_location: "dist" #Built app content directory - optional
```

### Sumber Tambahan
- [Dokumentasi Azure Static Web Apps](https://learn.microsoft.com/azure/static-web-apps/getting-started)  
- [Dokumentasi GitHub Actions](https://docs.github.com/actions/use-cases-and-examples/deploying/deploying-to-azure-static-web-app)  

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat penting, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.