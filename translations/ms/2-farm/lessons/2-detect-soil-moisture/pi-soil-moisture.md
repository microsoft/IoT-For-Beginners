<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9d4d00a47d5d0f3e6ce42c0d1020064a",
  "translation_date": "2025-08-28T01:07:43+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/pi-soil-moisture.md",
  "language_code": "ms"
}
-->
# Ukur Kelembapan Tanah - Raspberry Pi

Dalam bahagian pelajaran ini, anda akan menambah sensor kelembapan tanah kapasitif pada Raspberry Pi anda, dan membaca nilai daripadanya.

## Perkakasan

Raspberry Pi memerlukan sensor kelembapan tanah kapasitif.

Sensor yang akan anda gunakan ialah [Capacitive Soil Moisture Sensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), yang mengukur kelembapan tanah dengan mengesan kapasitans tanah, satu sifat yang berubah apabila kelembapan tanah berubah. Apabila kelembapan tanah meningkat, voltan akan menurun.

Ini adalah sensor analog, jadi ia menggunakan pin analog, dan ADC 10-bit dalam Grove Base Hat pada Pi untuk menukar voltan kepada isyarat digital dari 1-1,023. Isyarat ini kemudian dihantar melalui I

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.