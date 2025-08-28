<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5cb65a6ec4387ed177e145347e8e308e",
  "translation_date": "2025-08-27T23:38:52+00:00",
  "source_file": "3-transport/lessons/4-geofences/assignment.md",
  "language_code": "ms"
}
-->
# Hantar pemberitahuan menggunakan Twilio

## Arahan

Dalam kod anda setakat ini, anda hanya mencatatkan jarak ke geofence. Dalam tugasan ini, anda perlu menambah pemberitahuan, sama ada mesej teks atau emel, apabila koordinat GPS berada di dalam geofence.

Azure Functions mempunyai banyak pilihan untuk pengikatan, termasuk kepada perkhidmatan pihak ketiga seperti Twilio, sebuah platform komunikasi.

* Daftar untuk akaun percuma di [Twilio.com](https://www.twilio.com)
* Baca dokumentasi tentang pengikatan Azure Functions kepada Twilio SMS di [halaman dokumentasi Microsoft Twilio binding untuk Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?WT.mc_id=academic-17441-jabenn&tabs=python).
* Baca dokumentasi tentang pengikatan Azure Functions kepada Twilio SendGrid untuk menghantar emel di [halaman dokumentasi Microsoft Azure Functions SendGrid bindings](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?WT.mc_id=academic-17441-jabenn&tabs=python).
* Tambahkan pengikatan kepada aplikasi Functions anda untuk diberitahu tentang koordinat GPS sama ada di dalam atau di luar geofence - bukan kedua-duanya.

## Rubrik

| Kriteria | Cemerlang | Memadai | Perlu Penambahbaikan |
| -------- | --------- | -------- | -------------------- |
| Konfigurasi pengikatan fungsi dan terima emel atau SMS | Berjaya mengkonfigurasi pengikatan fungsi dan menerima emel atau SMS apabila berada di dalam atau di luar geofence, tetapi bukan kedua-duanya | Berjaya mengkonfigurasi pengikatan tetapi tidak dapat menghantar emel atau SMS, atau hanya dapat menghantar apabila koordinat berada di dalam dan di luar | Tidak berjaya mengkonfigurasi pengikatan dan menghantar emel atau SMS |

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.