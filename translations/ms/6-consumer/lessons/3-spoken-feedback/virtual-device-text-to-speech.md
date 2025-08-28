<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-27T23:17:47+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "ms"
}
-->
# Teks ke Ucapan - Peranti IoT Maya

Dalam bahagian pelajaran ini, anda akan menulis kod untuk menukar teks kepada ucapan menggunakan perkhidmatan ucapan.

## Tukar teks kepada ucapan

SDK perkhidmatan ucapan yang anda gunakan dalam pelajaran sebelum ini untuk menukar ucapan kepada teks juga boleh digunakan untuk menukar teks kembali kepada ucapan. Apabila meminta ucapan, anda perlu menyediakan suara yang akan digunakan kerana ucapan boleh dijana menggunakan pelbagai jenis suara.

Setiap bahasa menyokong pelbagai suara yang berbeza, dan anda boleh mendapatkan senarai suara yang disokong untuk setiap bahasa daripada SDK perkhidmatan ucapan.

### Tugasan - tukar teks kepada ucapan

1. Buka projek `smart-timer` dalam VS Code, dan pastikan persekitaran maya dimuatkan dalam terminal.

1. Import `SpeechSynthesizer` daripada pakej `azure.cognitiveservices.speech` dengan menambahkannya kepada import sedia ada:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. Di atas fungsi `say`, buat konfigurasi ucapan untuk digunakan dengan penjana ucapan:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    Ini menggunakan kunci API, lokasi, dan bahasa yang sama seperti yang digunakan oleh pengenal suara.

1. Di bawah ini, tambahkan kod berikut untuk mendapatkan suara dan menetapkannya pada konfigurasi ucapan:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    Kod ini mendapatkan senarai semua suara yang tersedia, kemudian mencari suara pertama yang sepadan dengan bahasa yang sedang digunakan.

    > 💁 Anda boleh mendapatkan senarai penuh suara yang disokong daripada [dokumentasi sokongan bahasa dan suara di Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Jika anda ingin menggunakan suara tertentu, anda boleh membuang fungsi ini dan menetapkan suara secara langsung kepada nama suara daripada dokumentasi ini. Sebagai contoh:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. Kemas kini kandungan fungsi `say` untuk menjana SSML bagi respons:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. Di bawah ini, hentikan pengenalan ucapan, ucapkan SSML, kemudian mulakan semula pengenalan:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    Pengenalan dihentikan semasa teks diucapkan untuk mengelakkan pengumuman pemasa yang dimulakan dikesan, dihantar ke LUIS, dan mungkin ditafsirkan sebagai permintaan untuk menetapkan pemasa baru.

    > 💁 Anda boleh menguji ini dengan mengulas baris untuk menghentikan dan memulakan semula pengenalan. Tetapkan satu pemasa, dan anda mungkin mendapati pengumuman menetapkan pemasa baru, yang menyebabkan pengumuman baru, yang membawa kepada pemasa baru, dan seterusnya tanpa henti!

1. Jalankan aplikasi, dan pastikan aplikasi fungsi juga berjalan. Tetapkan beberapa pemasa, dan anda akan mendengar respons yang diucapkan mengatakan bahawa pemasa anda telah ditetapkan, kemudian satu lagi respons yang diucapkan apabila pemasa selesai.

> 💁 Anda boleh menemui kod ini dalam folder [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device).

😀 Program pemasa anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.