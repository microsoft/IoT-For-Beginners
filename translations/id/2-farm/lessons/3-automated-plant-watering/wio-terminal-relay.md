<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f3c5d8afa2ef6a0b425ef8ff20615cb4",
  "translation_date": "2025-08-28T01:56:58+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/wio-terminal-relay.md",
  "language_code": "id"
}
-->
# Mengontrol Relay - Wio Terminal

Dalam bagian pelajaran ini, Anda akan menambahkan relay ke Wio Terminal Anda selain sensor kelembapan tanah, dan mengontrolnya berdasarkan tingkat kelembapan tanah.

## Perangkat Keras

Wio Terminal membutuhkan relay.

Relay yang akan Anda gunakan adalah [Grove relay](https://www.seeedstudio.com/Grove-Relay.html), relay yang biasanya terbuka (artinya sirkuit output terbuka atau terputus ketika tidak ada sinyal yang dikirim ke relay) yang dapat menangani sirkuit output hingga 250V dan 10A.

Ini adalah aktuator digital, jadi terhubung ke pin digital pada Wio Terminal. Port gabungan analog/digital sudah digunakan dengan sensor kelembapan tanah, jadi relay ini akan terhubung ke port lainnya, yaitu port gabungan I

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diperhatikan bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.