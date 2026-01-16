<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d620a470d9dd8614d99824832978360a",
  "translation_date": "2025-08-27T23:01:55+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/virtual-device-translate-speech.md",
  "language_code": "id"
}
-->
# Terjemahkan Ucapan - Perangkat IoT Virtual

Dalam bagian pelajaran ini, Anda akan menulis kode untuk menerjemahkan ucapan saat mengonversinya menjadi teks menggunakan layanan ucapan, lalu menerjemahkan teks menggunakan layanan Translator sebelum menghasilkan respons yang diucapkan.

## Gunakan layanan ucapan untuk menerjemahkan ucapan

Layanan ucapan dapat mengambil ucapan dan tidak hanya mengonversinya menjadi teks dalam bahasa yang sama, tetapi juga menerjemahkan output ke bahasa lain.

### Tugas - gunakan layanan ucapan untuk menerjemahkan ucapan

1. Buka proyek `smart-timer` di VS Code, dan pastikan lingkungan virtual telah dimuat di terminal.

1. Tambahkan pernyataan impor berikut di bawah impor yang sudah ada:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    Ini mengimpor kelas yang digunakan untuk menerjemahkan ucapan, dan pustaka `requests` yang akan digunakan untuk melakukan panggilan ke layanan Translator nanti dalam pelajaran ini.

1. Timer pintar Anda akan memiliki 2 bahasa yang diatur - bahasa server yang digunakan untuk melatih LUIS (bahasa yang sama juga digunakan untuk membangun pesan yang akan diucapkan kepada pengguna), dan bahasa yang diucapkan oleh pengguna. Perbarui variabel `language` menjadi bahasa yang akan diucapkan oleh pengguna, dan tambahkan variabel baru bernama `server_language` untuk bahasa yang digunakan untuk melatih LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Ganti `<user language>` dengan nama lokal untuk bahasa yang akan Anda gunakan, misalnya `fr-FR` untuk bahasa Prancis, atau `zn-HK` untuk bahasa Kanton.

    Ganti `<server language>` dengan nama lokal untuk bahasa yang digunakan untuk melatih LUIS.

    Anda dapat menemukan daftar bahasa yang didukung dan nama lokalnya di [dokumentasi dukungan bahasa dan suara di Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Jika Anda tidak berbicara dalam beberapa bahasa, Anda dapat menggunakan layanan seperti [Bing Translate](https://www.bing.com/translator) atau [Google Translate](https://translate.google.com) untuk menerjemahkan dari bahasa pilihan Anda ke bahasa lain. Layanan ini kemudian dapat memutar audio dari teks yang diterjemahkan. Perlu diketahui bahwa pengenal ucapan akan mengabaikan beberapa output audio dari perangkat Anda, jadi Anda mungkin perlu menggunakan perangkat tambahan untuk memutar teks yang diterjemahkan.
    >
    > Sebagai contoh, jika Anda melatih LUIS dalam bahasa Inggris, tetapi ingin menggunakan bahasa Prancis sebagai bahasa pengguna, Anda dapat menerjemahkan kalimat seperti "set a 2 minute and 27 second timer" dari bahasa Inggris ke bahasa Prancis menggunakan Bing Translate, lalu gunakan tombol **Listen translation** untuk mengucapkan terjemahan ke mikrofon Anda.
    >
    > ![Tombol listen translation di Bing translate](../../../../../translated_images/id/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Ganti deklarasi `recognizer_config` dan `recognizer` dengan yang berikut:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    Ini membuat konfigurasi terjemahan untuk mengenali ucapan dalam bahasa pengguna, dan membuat terjemahan dalam bahasa pengguna dan server. Kemudian menggunakan konfigurasi ini untuk membuat pengenal terjemahan - pengenal ucapan yang dapat menerjemahkan output pengenalan ucapan ke beberapa bahasa.

    > 💁 Bahasa asli perlu ditentukan dalam `target_languages`, jika tidak, Anda tidak akan mendapatkan terjemahan apa pun.

1. Perbarui fungsi `recognized`, ganti seluruh isi fungsi dengan yang berikut:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    Kode ini memeriksa apakah acara yang dikenali dipicu karena ucapan diterjemahkan (acara ini dapat dipicu pada waktu lain, seperti saat ucapan dikenali tetapi tidak diterjemahkan). Jika ucapan diterjemahkan, kode ini menemukan terjemahan dalam kamus `args.result.translations` yang cocok dengan bahasa server.

    Kamus `args.result.translations` menggunakan bagian bahasa dari pengaturan lokal, bukan seluruh pengaturan. Sebagai contoh, jika Anda meminta terjemahan ke `fr-FR` untuk bahasa Prancis, kamus akan berisi entri untuk `fr`, bukan `fr-FR`.

    Teks yang diterjemahkan kemudian dikirim ke IoT Hub.

1. Jalankan kode ini untuk menguji terjemahan. Pastikan aplikasi fungsi Anda berjalan, dan minta timer dalam bahasa pengguna, baik dengan berbicara dalam bahasa tersebut sendiri, atau menggunakan aplikasi terjemahan.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## Terjemahkan teks menggunakan layanan Translator

Layanan ucapan tidak mendukung terjemahan teks kembali ke ucapan, sebagai gantinya Anda dapat menggunakan layanan Translator untuk menerjemahkan teks. Layanan ini memiliki REST API yang dapat Anda gunakan untuk menerjemahkan teks.

### Tugas - gunakan sumber daya Translator untuk menerjemahkan teks

1. Tambahkan kunci API Translator di bawah `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Ganti `<key>` dengan kunci API untuk sumber daya layanan Translator Anda.

1. Di atas fungsi `say`, definisikan fungsi `translate_text` yang akan menerjemahkan teks dari bahasa server ke bahasa pengguna:

    ```python
    def translate_text(text):
    ```

1. Di dalam fungsi ini, definisikan URL dan header untuk panggilan REST API:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL untuk API ini tidak spesifik lokasi, sebagai gantinya lokasi diteruskan sebagai header. Kunci API digunakan langsung, jadi tidak seperti layanan ucapan, tidak perlu mendapatkan token akses dari API penerbit token.

1. Di bawah ini, definisikan parameter dan isi untuk panggilan:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` mendefinisikan parameter untuk diteruskan ke panggilan API, meneruskan bahasa asal dan tujuan. Panggilan ini akan menerjemahkan teks dalam bahasa `from` ke bahasa `to`.

    `body` berisi teks yang akan diterjemahkan. Ini adalah array, karena beberapa blok teks dapat diterjemahkan dalam panggilan yang sama.

1. Lakukan panggilan ke REST API, dan dapatkan responsnya:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Respons yang diterima adalah array JSON, dengan satu item yang berisi terjemahan. Item ini memiliki array untuk terjemahan dari semua item yang diteruskan dalam isi.

    ```json
    [
        {
            "translations": [
                {
                    "text": "Chronométrant votre minuterie de 2 minutes 27 secondes.",
                    "to": "fr"
                }
            ]
        }
    ]
    ```

1. Kembalikan properti `text` dari terjemahan pertama dari item pertama dalam array:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Perbarui fungsi `say` untuk menerjemahkan teks yang akan diucapkan sebelum SSML dibuat:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    Kode ini juga mencetak versi asli dan terjemahan dari teks ke konsol.

1. Jalankan kode Anda. Pastikan aplikasi fungsi Anda berjalan, dan minta timer dalam bahasa pengguna, baik dengan berbicara dalam bahasa tersebut sendiri, atau menggunakan aplikasi terjemahan.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 Karena cara berbeda untuk mengatakan sesuatu dalam berbagai bahasa, Anda mungkin mendapatkan terjemahan yang sedikit berbeda dari contoh yang Anda berikan kepada LUIS. Jika ini terjadi, tambahkan lebih banyak contoh ke LUIS, latih ulang, lalu publikasikan ulang modelnya.

> 💁 Anda dapat menemukan kode ini di folder [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device).

😀 Program timer multibahasa Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan terjemahan yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.