<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "bbb5aa34221fe129dd3ce4d9ec33831a",
  "translation_date": "2025-08-27T23:00:46+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/pi-translate-speech.md",
  "language_code": "id"
}
-->
# Menerjemahkan Ucapan - Raspberry Pi

Dalam bagian pelajaran ini, Anda akan menulis kode untuk menerjemahkan teks menggunakan layanan penerjemah.

## Mengubah teks menjadi ucapan menggunakan layanan penerjemah

REST API layanan ucapan tidak mendukung terjemahan langsung, tetapi Anda dapat menggunakan layanan Translator untuk menerjemahkan teks yang dihasilkan oleh layanan ucapan ke teks, serta teks dari respons yang diucapkan. Layanan ini memiliki REST API yang dapat Anda gunakan untuk menerjemahkan teks.

### Tugas - menggunakan sumber daya penerjemah untuk menerjemahkan teks

1. Timer pintar Anda akan memiliki 2 bahasa yang diatur - bahasa server yang digunakan untuk melatih LUIS (bahasa yang sama juga digunakan untuk membangun pesan yang akan diucapkan kepada pengguna), dan bahasa yang diucapkan oleh pengguna. Perbarui variabel `language` menjadi bahasa yang akan diucapkan oleh pengguna, dan tambahkan variabel baru bernama `server_language` untuk bahasa yang digunakan untuk melatih LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Ganti `<user language>` dengan nama lokal untuk bahasa yang akan Anda gunakan, misalnya `fr-FR` untuk bahasa Prancis, atau `zn-HK` untuk bahasa Kanton.

    Ganti `<server language>` dengan nama lokal untuk bahasa yang digunakan untuk melatih LUIS.

    Anda dapat menemukan daftar bahasa yang didukung dan nama lokalnya di [Dokumentasi dukungan bahasa dan suara di Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Jika Anda tidak berbicara dalam banyak bahasa, Anda dapat menggunakan layanan seperti [Bing Translate](https://www.bing.com/translator) atau [Google Translate](https://translate.google.com) untuk menerjemahkan dari bahasa pilihan Anda ke bahasa lain. Layanan ini kemudian dapat memutar audio dari teks yang diterjemahkan.
    >
    > Sebagai contoh, jika Anda melatih LUIS dalam bahasa Inggris, tetapi ingin menggunakan bahasa Prancis sebagai bahasa pengguna, Anda dapat menerjemahkan kalimat seperti "set a 2 minute and 27 second timer" dari bahasa Inggris ke bahasa Prancis menggunakan Bing Translate, lalu gunakan tombol **Dengarkan terjemahan** untuk mengucapkan terjemahan ke mikrofon Anda.
    >
    > ![Tombol dengarkan terjemahan di Bing Translate](../../../../../translated_images/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.id.png)

1. Tambahkan kunci API penerjemah di bawah `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Ganti `<key>` dengan kunci API untuk sumber daya layanan penerjemah Anda.

1. Di atas fungsi `say`, definisikan fungsi `translate_text` yang akan menerjemahkan teks dari bahasa server ke bahasa pengguna:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    Bahasa asal dan tujuan diteruskan ke fungsi ini - aplikasi Anda perlu mengonversi dari bahasa pengguna ke bahasa server saat mengenali ucapan, dan dari bahasa server ke bahasa pengguna saat memberikan umpan balik yang diucapkan.

1. Di dalam fungsi ini, definisikan URL dan header untuk panggilan REST API:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL untuk API ini tidak spesifik lokasi, melainkan lokasi diteruskan sebagai header. Kunci API digunakan secara langsung, jadi tidak seperti layanan ucapan, tidak perlu mendapatkan token akses dari API penerbit token.

1. Di bawah ini, definisikan parameter dan isi untuk panggilan:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` mendefinisikan parameter yang akan diteruskan ke panggilan API, dengan meneruskan bahasa asal dan tujuan. Panggilan ini akan menerjemahkan teks dalam bahasa `from` ke bahasa `to`.

    `body` berisi teks yang akan diterjemahkan. Ini adalah array, karena beberapa blok teks dapat diterjemahkan dalam satu panggilan.

1. Lakukan panggilan REST API, dan dapatkan responsnya:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Respons yang diterima kembali adalah array JSON, dengan satu item yang berisi terjemahan. Item ini memiliki array untuk terjemahan dari semua item yang diteruskan dalam body.

    ```json
    [
        {
            "translations": [
                {
                    "text": "Set a 2 minute 27 second timer.",
                    "to": "en"
                }
            ]
        }
    ]
    ```

1. Kembalikan properti `test` dari terjemahan pertama dari item pertama dalam array:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Perbarui loop `while True` untuk menerjemahkan teks dari panggilan ke `convert_speech_to_text` dari bahasa pengguna ke bahasa server:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    Kode ini juga mencetak versi asli dan terjemahan teks ke konsol.

1. Perbarui fungsi `say` untuk menerjemahkan teks yang akan diucapkan dari bahasa server ke bahasa pengguna:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    Kode ini juga mencetak versi asli dan terjemahan teks ke konsol.

1. Jalankan kode Anda. Pastikan aplikasi fungsi Anda berjalan, dan minta timer dalam bahasa pengguna, baik dengan berbicara dalam bahasa tersebut sendiri, atau menggunakan aplikasi terjemahan.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py
    Connecting
    Connected
    Using voice fr-FR-DeniseNeural
    Original: Définir une minuterie de 2 minutes et 27 secondes.
    Translated: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 Karena cara mengucapkan sesuatu yang berbeda dalam berbagai bahasa, Anda mungkin mendapatkan terjemahan yang sedikit berbeda dari contoh yang Anda berikan kepada LUIS. Jika demikian, tambahkan lebih banyak contoh ke LUIS, latih ulang, lalu publikasikan ulang modelnya.

> 💁 Anda dapat menemukan kode ini di folder [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi).

😀 Program timer multibahasa Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.