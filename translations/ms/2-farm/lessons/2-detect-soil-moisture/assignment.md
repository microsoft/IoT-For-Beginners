<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "506d21b544d5de47406c89ad496a21cd",
  "translation_date": "2025-08-27T21:55:04+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/assignment.md",
  "language_code": "ms"
}
-->
# Kalibrasi sensor anda

## Arahan

Dalam pelajaran ini, anda telah mengumpulkan bacaan sensor kelembapan tanah, diukur sebagai nilai dari 0-1023. Untuk menukar bacaan ini kepada bacaan kelembapan tanah sebenar, anda perlu mengkalibrasi sensor anda. Anda boleh melakukannya dengan mengambil bacaan daripada sampel tanah, kemudian mengira kandungan kelembapan tanah gravimetrik daripada sampel tersebut.

Anda perlu mengulangi langkah-langkah ini beberapa kali untuk mendapatkan bacaan yang diperlukan, dengan tahap kelembapan tanah yang berbeza setiap kali.

1. Ambil bacaan kelembapan tanah menggunakan sensor kelembapan tanah. Catatkan bacaan ini.

1. Ambil sampel tanah dan timbang beratnya. Catatkan berat ini.

1. Keringkan tanah - ketuhar hangat pada suhu 110°C (230°F) selama beberapa jam adalah cara terbaik, anda juga boleh melakukannya di bawah cahaya matahari, atau letakkan di tempat yang hangat dan kering sehingga tanah benar-benar kering. Tanah sepatutnya menjadi serbuk dan longgar.

    > 💁 Di makmal, untuk hasil yang paling tepat, anda akan mengeringkan tanah dalam ketuhar selama 48-72 jam. Jika sekolah anda mempunyai ketuhar pengering, cuba gunakan ketuhar tersebut untuk mengeringkan tanah lebih lama. Semakin lama, semakin kering sampel dan semakin tepat hasilnya.

1. Timbang tanah sekali lagi.

    > 🔥 Jika anda mengeringkannya dalam ketuhar, pastikan tanah telah sejuk terlebih dahulu!

Kelembapan tanah gravimetrik dikira sebagai:

![kelembapan tanah % ialah berat basah tolak berat kering, dibahagi dengan berat kering, darab 100](../../../../../translated_images/ms/gsm-calculation.6da38c6201eec14e7573bb2647aa18892883193553d23c9d77e5dc681522dfb2.png)

* W - berat tanah basah
* W - berat tanah kering

Sebagai contoh, katakan anda mempunyai sampel tanah yang beratnya 212g basah, dan 197g kering.

![Pengiraan diisi](../../../../../translated_images/ms/gsm-calculation-example.99f9803b4f29e97668e7c15412136c0c399ab12dbba0b89596fdae9d8aedb6fb.png)

* W = 212g
* W = 197g
* 212 - 197 = 15
* 15 / 197 = 0.076
* 0.076 * 100 = 7.6%

Dalam contoh ini, tanah mempunyai kelembapan tanah gravimetrik sebanyak 7.6%.

Setelah anda mempunyai bacaan untuk sekurang-kurangnya 3 sampel, plotkan graf kelembapan tanah % kepada bacaan sensor kelembapan tanah dan tambahkan garis yang paling sesuai dengan titik-titik tersebut. Anda kemudian boleh menggunakan ini untuk mengira kandungan kelembapan tanah gravimetrik bagi bacaan sensor tertentu dengan membaca nilai daripada garis tersebut.

## Rubrik

| Kriteria | Cemerlang | Memadai | Perlu Penambahbaikan |
| -------- | --------- | -------- | -------------------- |
| Mengumpul data kalibrasi | Mengambil sekurang-kurangnya 3 sampel kalibrasi | Mengambil sekurang-kurangnya 2 sampel kalibrasi | Mengambil sekurang-kurangnya 1 sampel kalibrasi |
| Membuat bacaan yang dikalibrasi | Berjaya memplot graf kalibrasi dan membuat bacaan daripada sensor, serta menukarkannya kepada kandungan kelembapan tanah gravimetrik | Berjaya memplot graf kalibrasi | Tidak dapat memplot graf |

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.