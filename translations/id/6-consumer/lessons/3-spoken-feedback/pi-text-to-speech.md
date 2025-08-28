<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-27T23:13:32+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "id"
}
-->
# Teks ke Ucapan - Raspberry Pi

Dalam bagian pelajaran ini, Anda akan menulis kode untuk mengubah teks menjadi ucapan menggunakan layanan ucapan.

## Mengubah teks menjadi ucapan menggunakan layanan ucapan

Teks dapat dikirim ke layanan ucapan menggunakan REST API untuk mendapatkan ucapan dalam bentuk file audio yang dapat diputar di perangkat IoT Anda. Saat meminta ucapan, Anda perlu menentukan suara yang akan digunakan karena ucapan dapat dihasilkan menggunakan berbagai suara yang berbeda.

Setiap bahasa mendukung berbagai suara, dan Anda dapat membuat permintaan REST ke layanan ucapan untuk mendapatkan daftar suara yang didukung untuk setiap bahasa.

### Tugas - mendapatkan suara

1. Buka proyek `smart-timer` di VS Code.

1. Tambahkan kode berikut di atas fungsi `say` untuk meminta daftar suara untuk suatu bahasa:

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

    Kode ini mendefinisikan fungsi bernama `get_voice` yang menggunakan layanan ucapan untuk mendapatkan daftar suara. Fungsi ini kemudian menemukan suara pertama yang cocok dengan bahasa yang digunakan.

    Fungsi ini kemudian dipanggil untuk menyimpan suara pertama, dan nama suara dicetak ke konsol. Suara ini dapat diminta sekali dan nilainya digunakan untuk setiap panggilan mengubah teks menjadi ucapan.

    > 💁 Anda dapat menemukan daftar lengkap suara yang didukung dari [dokumentasi dukungan bahasa dan suara di Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Jika Anda ingin menggunakan suara tertentu, maka Anda dapat menghapus fungsi ini dan menetapkan suara secara langsung dengan nama suara dari dokumentasi ini. Sebagai contoh:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### Tugas - mengubah teks menjadi ucapan

1. Di bawah ini, definisikan konstanta untuk format audio yang akan diambil dari layanan ucapan. Saat Anda meminta audio, Anda dapat melakukannya dalam berbagai format.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    Format yang dapat Anda gunakan tergantung pada perangkat keras Anda. Jika Anda mendapatkan kesalahan `Invalid sample rate` saat memutar audio, ubah ini ke nilai lain. Anda dapat menemukan daftar nilai yang didukung di [dokumentasi REST API teks ke ucapan di Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs). Anda perlu menggunakan audio dalam format `riff`, dan nilai yang dapat dicoba adalah `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm`, dan `riff-48khz-16bit-mono-pcm`.

1. Di bawah ini, deklarasikan fungsi bernama `get_speech` yang akan mengubah teks menjadi ucapan menggunakan REST API layanan ucapan:

    ```python
    def get_speech(text):
    ```

1. Dalam fungsi `get_speech`, definisikan URL yang akan dipanggil dan header yang akan dikirimkan:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    Ini menetapkan header untuk menggunakan token akses yang dihasilkan, menetapkan konten ke SSML, dan menentukan format audio yang diperlukan.

1. Di bawah ini, definisikan SSML yang akan dikirim ke REST API:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    SSML ini menetapkan bahasa dan suara yang akan digunakan, bersama dengan teks yang akan diubah.

1. Terakhir, tambahkan kode dalam fungsi ini untuk membuat permintaan REST dan mengembalikan data audio biner:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### Tugas - memutar audio

1. Di bawah fungsi `get_speech`, definisikan fungsi baru untuk memutar audio yang dikembalikan oleh panggilan REST API:

    ```python
    def play_speech(speech):
    ```

1. `speech` yang diteruskan ke fungsi ini adalah data audio biner yang dikembalikan dari REST API. Gunakan kode berikut untuk membuka ini sebagai file wave dan meneruskannya ke PyAudio untuk memutar audio:

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

    Kode ini menggunakan stream PyAudio, sama seperti saat menangkap audio. Perbedaannya di sini adalah stream diatur sebagai stream output, dan data dibaca dari data audio dan dikirimkan ke stream.

    Alih-alih menetapkan detail stream seperti sample rate secara langsung, detail tersebut dibaca dari data audio.

1. Ganti isi fungsi `say` dengan yang berikut:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    Kode ini mengubah teks menjadi ucapan sebagai data audio biner, dan memutar audio tersebut.

1. Jalankan aplikasi, dan pastikan aplikasi fungsi juga berjalan. Atur beberapa timer, dan Anda akan mendengar respons suara yang mengatakan bahwa timer Anda telah diatur, lalu respons suara lain saat timer selesai.

    Jika Anda mendapatkan kesalahan `Invalid sample rate`, ubah `playback_format` seperti yang dijelaskan di atas.

> 💁 Anda dapat menemukan kode ini di folder [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi).

😀 Program timer Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.