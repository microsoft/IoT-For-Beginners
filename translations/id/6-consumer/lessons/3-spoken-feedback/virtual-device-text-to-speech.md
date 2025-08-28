<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-27T23:13:30+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "id"
}
-->
# Teks ke Ucapan - Perangkat IoT Virtual

Dalam bagian pelajaran ini, Anda akan menulis kode untuk mengonversi teks menjadi ucapan menggunakan layanan ucapan.

## Mengonversi teks menjadi ucapan

SDK layanan ucapan yang Anda gunakan pada pelajaran sebelumnya untuk mengonversi ucapan menjadi teks juga dapat digunakan untuk mengonversi teks kembali menjadi ucapan. Saat meminta ucapan, Anda perlu menentukan suara yang akan digunakan karena ucapan dapat dihasilkan menggunakan berbagai jenis suara.

Setiap bahasa mendukung berbagai suara, dan Anda dapat memperoleh daftar suara yang didukung untuk setiap bahasa dari SDK layanan ucapan.

### Tugas - mengonversi teks menjadi ucapan

1. Buka proyek `smart-timer` di VS Code, dan pastikan lingkungan virtual telah dimuat di terminal.

1. Impor `SpeechSynthesizer` dari paket `azure.cognitiveservices.speech` dengan menambahkannya ke impor yang sudah ada:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. Di atas fungsi `say`, buat konfigurasi ucapan untuk digunakan dengan speech synthesizer:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    Ini menggunakan kunci API, lokasi, dan bahasa yang sama seperti yang digunakan oleh recognizer.

1. Di bawah ini, tambahkan kode berikut untuk mendapatkan suara dan menetapkannya pada konfigurasi ucapan:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    Kode ini mengambil daftar semua suara yang tersedia, lalu menemukan suara pertama yang sesuai dengan bahasa yang digunakan.

    > 💁 Anda dapat melihat daftar lengkap suara yang didukung dari [dokumentasi dukungan bahasa dan suara di Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Jika Anda ingin menggunakan suara tertentu, Anda dapat menghapus fungsi ini dan menetapkan suara secara langsung dengan nama suara dari dokumentasi tersebut. Sebagai contoh:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. Perbarui isi fungsi `say` untuk menghasilkan SSML untuk respons:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. Di bawah ini, hentikan pengenalan ucapan, ucapkan SSML, lalu mulai pengenalan kembali:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    Pengenalan dihentikan sementara teks diucapkan untuk menghindari pengumuman bahwa timer telah dimulai terdeteksi, dikirim ke LUIS, dan mungkin diinterpretasikan sebagai permintaan untuk mengatur timer baru.

    > 💁 Anda dapat menguji ini dengan mengomentari baris untuk menghentikan dan memulai kembali pengenalan. Atur satu timer, dan Anda mungkin menemukan bahwa pengumuman tersebut mengatur timer baru, yang menyebabkan pengumuman baru, yang mengarah ke timer baru, dan seterusnya tanpa henti!

1. Jalankan aplikasi, dan pastikan aplikasi fungsi juga berjalan. Atur beberapa timer, dan Anda akan mendengar respons yang diucapkan yang mengatakan bahwa timer Anda telah diatur, lalu respons lain yang diucapkan saat timer selesai.

> 💁 Anda dapat menemukan kode ini di folder [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device).

😀 Program timer Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.