<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3764e089adf2d5801272bc0895f8498b",
  "translation_date": "2025-08-27T20:50:36+00:00",
  "source_file": "4-manufacturing/README.md",
  "language_code": "ms"
}
-->
# Pembuatan dan pemprosesan - menggunakan IoT untuk meningkatkan pemprosesan makanan

Apabila makanan tiba di hab pusat atau kilang pemprosesan, ia tidak semestinya terus dihantar ke pasar raya. Selalunya, makanan melalui beberapa langkah pemprosesan, seperti pengasingan mengikut kualiti. Ini adalah proses yang dahulunya dilakukan secara manual - ia bermula di ladang apabila pemetik hanya memilih buah yang masak, kemudian di kilang, buah-buahan akan bergerak di atas tali sawat dan pekerja akan secara manual membuang buah yang lebam atau busuk. Setelah pernah memetik dan mengasingkan strawberi sendiri sebagai kerja musim panas semasa sekolah, saya boleh mengesahkan bahawa ini bukanlah kerja yang menyeronokkan.

Susunan yang lebih moden bergantung pada IoT untuk pengasingan. Beberapa peranti terawal seperti pengasing dari [Weco](https://wecotek.com) menggunakan sensor optik untuk mengesan kualiti hasil, contohnya menolak tomato hijau. Peranti ini boleh digunakan pada mesin penuai di ladang itu sendiri, atau di kilang pemprosesan.

Dengan kemajuan dalam Kecerdasan Buatan (AI) dan Pembelajaran Mesin (ML), mesin-mesin ini boleh menjadi lebih canggih, menggunakan model ML yang dilatih untuk membezakan antara buah dan objek asing seperti batu, tanah atau serangga. Model ini juga boleh dilatih untuk mengesan kualiti buah, bukan sahaja buah yang lebam tetapi juga pengesanan awal penyakit atau masalah tanaman lain.

> 🎓 Istilah *model ML* merujuk kepada output daripada latihan perisian pembelajaran mesin pada satu set data. Sebagai contoh, anda boleh melatih model ML untuk membezakan antara tomato masak dan tidak masak, kemudian menggunakan model tersebut pada imej baharu untuk melihat sama ada tomato itu masak atau tidak.

Dalam 4 pelajaran ini, anda akan belajar cara melatih model AI berasaskan imej untuk mengesan kualiti buah, cara menggunakannya daripada peranti IoT, dan cara menjalankannya di edge - iaitu pada peranti IoT dan bukannya di awan.

> 💁 Pelajaran ini akan menggunakan beberapa sumber awan. Jika anda tidak melengkapkan semua pelajaran dalam projek ini, pastikan anda [membersihkan projek anda](../clean-up.md).

## Topik

1. [Melatih pengesan kualiti buah](./lessons/1-train-fruit-detector/README.md)
1. [Periksa kualiti buah dari peranti IoT](./lessons/2-check-fruit-from-device/README.md)
1. [Jalankan pengesan buah anda di edge](./lessons/3-run-fruit-detector-edge/README.md)
1. [Cetuskan pengesanan kualiti buah dari sensor](./lessons/4-trigger-fruit-detector/README.md)

## Kredit

Semua pelajaran ditulis dengan ♥️ oleh [Jen Fox](https://github.com/jenfoxbot) dan [Jim Bennett](https://GitHub.com/JimBobBennett)

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.