<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "506d21b544d5de47406c89ad496a21cd",
  "translation_date": "2025-08-27T21:54:42+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/assignment.md",
  "language_code": "id"
}
-->
# Kalibrasi Sensor Anda

## Instruksi

Dalam pelajaran ini, Anda telah mengumpulkan pembacaan sensor kelembapan tanah, diukur dengan nilai dari 0-1023. Untuk mengonversi nilai-nilai ini menjadi pembacaan kelembapan tanah yang sebenarnya, Anda perlu mengkalibrasi sensor Anda. Anda dapat melakukannya dengan mengambil pembacaan dari sampel tanah, lalu menghitung kadar kelembapan tanah gravimetrik dari sampel tersebut.

Anda perlu mengulangi langkah-langkah ini beberapa kali untuk mendapatkan pembacaan yang diperlukan, dengan tingkat kelembapan tanah yang berbeda setiap kali.

1. Ambil pembacaan kelembapan tanah menggunakan sensor kelembapan tanah. Catat pembacaan ini.

1. Ambil sampel tanah, dan timbang. Catat beratnya.

1. Keringkan tanah - oven hangat pada suhu 110°C (230°F) selama beberapa jam adalah cara terbaik, Anda juga bisa melakukannya di bawah sinar matahari, atau meletakkannya di tempat yang hangat dan kering hingga tanah benar-benar kering. Tanah harus menjadi bubuk dan lepas.

    > 💁 Di laboratorium, untuk hasil yang paling akurat, Anda akan mengeringkan tanah di oven selama 48-72 jam. Jika sekolah Anda memiliki oven pengering, lihat apakah Anda bisa menggunakannya untuk mengeringkan lebih lama. Semakin lama, semakin kering sampel dan semakin akurat hasilnya.

1. Timbang tanah lagi.

    > 🔥 Jika Anda mengeringkannya di oven, pastikan tanah sudah dingin terlebih dahulu!

Kelembapan tanah gravimetrik dihitung sebagai:

![kelembapan tanah % adalah berat basah dikurangi berat kering, dibagi berat kering, dikalikan 100](../../../../../translated_images/id/gsm-calculation.6da38c6201eec14e7573bb2647aa18892883193553d23c9d77e5dc681522dfb2.png)

* W
- berat tanah basah
* W
- berat tanah kering

Sebagai contoh, katakanlah Anda memiliki sampel tanah yang beratnya 212g basah, dan 197g kering.

![Perhitungan yang sudah diisi](../../../../../translated_images/id/gsm-calculation-example.99f9803b4f29e97668e7c15412136c0c399ab12dbba0b89596fdae9d8aedb6fb.png)

* W = 212g
* W = 197g
* 212 - 197 = 15
* 15 / 197 = 0.076
* 0.076 * 100 = 7.6%

Dalam contoh ini, tanah memiliki kelembapan tanah gravimetrik sebesar 7.6%.

Setelah Anda memiliki pembacaan untuk setidaknya 3 sampel, buat grafik persentase kelembapan tanah terhadap pembacaan sensor kelembapan tanah dan tambahkan garis yang paling sesuai dengan titik-titik tersebut. Anda kemudian dapat menggunakan ini untuk menghitung kadar kelembapan tanah gravimetrik untuk pembacaan sensor tertentu dengan membaca nilai dari garis tersebut.

## Rubrik

| Kriteria | Unggul | Memadai | Perlu Perbaikan |
| -------- | ------- | -------- | ---------------- |
| Mengumpulkan data kalibrasi | Mengambil setidaknya 3 sampel kalibrasi | Mengambil setidaknya 2 sampel kalibrasi | Mengambil setidaknya 1 sampel kalibrasi |
| Membuat pembacaan yang terkalibrasi | Berhasil membuat grafik kalibrasi dan membuat pembacaan dari sensor, serta mengonversinya ke kadar kelembapan tanah gravimetrik | Berhasil membuat grafik kalibrasi | Tidak mampu membuat grafik |

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.