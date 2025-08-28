<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-27T23:13:48+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "ms"
}
-->
# Teks ke Ucapan - Raspberry Pi

Dalam bahagian pelajaran ini, anda akan menulis kod untuk menukar teks kepada ucapan menggunakan perkhidmatan ucapan.

## Tukar teks kepada ucapan menggunakan perkhidmatan ucapan

Teks boleh dihantar ke perkhidmatan ucapan menggunakan REST API untuk mendapatkan ucapan sebagai fail audio yang boleh dimainkan semula pada peranti IoT anda. Apabila meminta ucapan, anda perlu menyediakan suara yang akan digunakan kerana ucapan boleh dihasilkan menggunakan pelbagai jenis suara.

Setiap bahasa menyokong pelbagai suara, dan anda boleh membuat permintaan REST terhadap perkhidmatan ucapan untuk mendapatkan senarai suara yang disokong bagi setiap bahasa.

### Tugasan - dapatkan suara

1. Buka projek `smart-timer` dalam VS Code.

1. Tambahkan kod berikut di atas fungsi `say` untuk meminta senarai suara bagi sesuatu bahasa:

    ```python
    def get_voice():
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token()
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        first_voice = next(x for x in voices_json if x['Locale'].lower() == language.lower() and x['VoiceType'] == 'Neural')
        return first_voice['ShortName']
    
    voice = get_voice()
    print(f'Using voice {voice}')
    ```

    Kod ini mentakrifkan fungsi bernama `get_voice` yang menggunakan perkhidmatan ucapan untuk mendapatkan senarai suara. Ia kemudian mencari suara pertama yang sepadan dengan bahasa yang sedang digunakan.

    Fungsi ini kemudian dipanggil untuk menyimpan suara pertama, dan nama suara dicetak ke konsol. Suara ini boleh diminta sekali dan nilainya digunakan untuk setiap panggilan bagi menukar teks kepada ucapan.

    > 💁 Anda boleh mendapatkan senarai penuh suara yang disokong daripada [Dokumentasi sokongan bahasa dan suara di Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Jika anda ingin menggunakan suara tertentu, anda boleh membuang fungsi ini dan menetapkan suara secara langsung kepada nama suara daripada dokumentasi ini. Sebagai contoh:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### Tugasan - tukar teks kepada ucapan

1. Di bawah ini, takrifkan satu pemalar untuk format audio yang akan diperoleh daripada perkhidmatan ucapan. Apabila anda meminta audio, anda boleh melakukannya dalam pelbagai format.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    Format yang boleh anda gunakan bergantung pada perkakasan anda. Jika anda mendapat ralat `Invalid sample rate` semasa memainkan audio, tukar ini kepada nilai lain. Anda boleh mencari senarai nilai yang disokong dalam [Dokumentasi REST API teks ke ucapan di Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs). Anda perlu menggunakan audio format `riff`, dan nilai yang boleh dicuba ialah `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` dan `riff-48khz-16bit-mono-pcm`.

1. Di bawah ini, isytiharkan fungsi bernama `get_speech` yang akan menukar teks kepada ucapan menggunakan REST API perkhidmatan ucapan:

    ```python
    def get_speech(text):
    ```

1. Dalam fungsi `get_speech`, takrifkan URL untuk dipanggil dan tajuk untuk dihantar:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    Ini menetapkan tajuk untuk menggunakan token akses yang dijana, menetapkan kandungan kepada SSML dan menentukan format audio yang diperlukan.

1. Di bawah ini, takrifkan SSML untuk dihantar ke REST API:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    SSML ini menetapkan bahasa dan suara yang akan digunakan, bersama-sama dengan teks untuk ditukar.

1. Akhir sekali, tambahkan kod dalam fungsi ini untuk membuat permintaan REST dan mengembalikan data audio binari:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### Tugasan - mainkan audio

1. Di bawah fungsi `get_speech`, takrifkan fungsi baru untuk memainkan audio yang dikembalikan oleh panggilan REST API:

    ```python
    def play_speech(speech):
    ```

1. `speech` yang dihantar ke fungsi ini akan menjadi data audio binari yang dikembalikan daripada REST API. Gunakan kod berikut untuk membuka ini sebagai fail wave dan menghantarnya ke PyAudio untuk memainkan audio:

    ```python
    def play_speech(speech):
        with wave.open(speech, 'rb') as wave_file:
            stream = audio.open(format=audio.get_format_from_width(wave_file.getsampwidth()),
                                channels=wave_file.getnchannels(),
                                rate=wave_file.getframerate(),
                                output_device_index=speaker_card_number,
                                output=True)

            data = wave_file.readframes(4096)

            while len(data) > 0:
                stream.write(data)
                data = wave_file.readframes(4096)

            stream.stop_stream()
            stream.close()
    ```

    Kod ini menggunakan aliran PyAudio, sama seperti menangkap audio. Perbezaannya di sini ialah aliran ditetapkan sebagai aliran output, dan data dibaca daripada data audio dan dihantar ke aliran.

    Daripada menetapkan butiran aliran seperti kadar sampel secara langsung, ia dibaca daripada data audio.

1. Gantikan kandungan fungsi `say` dengan yang berikut:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    Kod ini menukar teks kepada ucapan sebagai data audio binari, dan memainkan audio.

1. Jalankan aplikasi, dan pastikan aplikasi fungsi juga berjalan. Tetapkan beberapa pemasa, dan anda akan mendengar respons yang diucapkan mengatakan bahawa pemasa anda telah ditetapkan, kemudian satu lagi respons yang diucapkan apabila pemasa selesai.

    Jika anda mendapat ralat `Invalid sample rate`, ubah `playback_format` seperti yang diterangkan di atas.

> 💁 Anda boleh mencari kod ini dalam folder [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi).

😀 Program pemasa anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.