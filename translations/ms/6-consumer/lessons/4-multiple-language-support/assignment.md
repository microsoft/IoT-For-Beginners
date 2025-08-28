<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "701f4a4466f9309b6e1d863077df0c06",
  "translation_date": "2025-08-27T23:44:45+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/assignment.md",
  "language_code": "ms"
}
-->
# Bina penterjemah sejagat

## Arahan

Penterjemah sejagat ialah peranti yang boleh menterjemah antara pelbagai bahasa, membolehkan orang yang bercakap dalam bahasa berbeza untuk berkomunikasi. Gunakan apa yang telah anda pelajari dalam beberapa pelajaran lepas untuk membina penterjemah sejagat menggunakan 2 peranti IoT.

> Jika anda tidak mempunyai 2 peranti, ikuti langkah-langkah dalam beberapa pelajaran sebelumnya untuk menyediakan peranti IoT maya sebagai salah satu peranti IoT.

Anda perlu mengkonfigurasi satu peranti untuk satu bahasa, dan satu lagi untuk bahasa lain. Setiap peranti perlu menerima pertuturan, menukarnya kepada teks, menghantarnya ke peranti lain melalui IoT Hub dan aplikasi Functions, kemudian menterjemahkannya dan memainkan pertuturan yang telah diterjemahkan.

> 💁 Tip: Apabila menghantar pertuturan dari satu peranti ke peranti lain, hantarkan juga bahasa asalnya, supaya lebih mudah untuk diterjemahkan. Anda juga boleh membuat setiap peranti mendaftar menggunakan IoT Hub dan aplikasi Functions terlebih dahulu, dengan menghantar bahasa yang mereka sokong untuk disimpan dalam Azure Storage. Anda kemudian boleh menggunakan aplikasi Functions untuk melakukan terjemahan, dan menghantar teks yang telah diterjemahkan ke peranti IoT.

## Rubrik

| Kriteria | Cemerlang | Memadai | Perlu Penambahbaikan |
| -------- | --------- | -------- | -------------------- |
| Membina penterjemah sejagat | Berjaya membina penterjemah sejagat, menukar pertuturan yang dikesan oleh satu peranti kepada pertuturan yang dimainkan oleh peranti lain dalam bahasa yang berbeza | Berjaya membuat beberapa komponen berfungsi, seperti menangkap pertuturan atau menterjemah, tetapi tidak dapat membina penyelesaian menyeluruh | Tidak berjaya membina mana-mana bahagian penterjemah sejagat yang berfungsi |

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.