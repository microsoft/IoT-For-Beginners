<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d620a470d9dd8614d99824832978360a",
  "translation_date": "2025-08-27T23:02:14+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/virtual-device-translate-speech.md",
  "language_code": "ms"
}
-->
# Terjemah Ucapan - Peranti IoT Maya

Dalam bahagian pelajaran ini, anda akan menulis kod untuk menterjemah ucapan semasa menukarnya kepada teks menggunakan perkhidmatan ucapan, kemudian menterjemah teks menggunakan perkhidmatan Translator sebelum menghasilkan respons dalam bentuk ucapan.

## Gunakan perkhidmatan ucapan untuk menterjemah ucapan

Perkhidmatan ucapan boleh mengambil ucapan dan bukan sahaja menukarnya kepada teks dalam bahasa yang sama, tetapi juga menterjemahkan output kepada bahasa lain.

### Tugasan - gunakan perkhidmatan ucapan untuk menterjemah ucapan

1. Buka projek `smart-timer` dalam VS Code, dan pastikan persekitaran maya dimuatkan dalam terminal.

1. Tambahkan pernyataan import berikut di bawah import sedia ada:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    Ini mengimport kelas yang digunakan untuk menterjemah ucapan, dan perpustakaan `requests` yang akan digunakan untuk membuat panggilan kepada perkhidmatan Translator kemudian dalam pelajaran ini.

1. Pemasa pintar anda akan mempunyai 2 bahasa yang ditetapkan - bahasa pelayan yang digunakan untuk melatih LUIS (bahasa yang sama juga digunakan untuk membina mesej untuk bercakap dengan pengguna), dan bahasa yang digunakan oleh pengguna. Kemas kini pembolehubah `language` kepada bahasa yang akan digunakan oleh pengguna, dan tambahkan pembolehubah baru yang dipanggil `server_language` untuk bahasa yang digunakan untuk melatih LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Gantikan `<user language>` dengan nama lokal untuk bahasa yang akan anda gunakan, contohnya `fr-FR` untuk Bahasa Perancis, atau `zn-HK` untuk Bahasa Kantonis.

    Gantikan `<server language>` dengan nama lokal untuk bahasa yang digunakan untuk melatih LUIS.

    Anda boleh mencari senarai bahasa yang disokong dan nama lokal mereka dalam [dokumentasi sokongan bahasa dan suara di Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Jika anda tidak bercakap dalam pelbagai bahasa, anda boleh menggunakan perkhidmatan seperti [Bing Translate](https://www.bing.com/translator) atau [Google Translate](https://translate.google.com) untuk menterjemah daripada bahasa pilihan anda kepada bahasa lain. Perkhidmatan ini kemudian boleh memainkan audio teks yang diterjemahkan. Perlu diingat bahawa pengenal ucapan akan mengabaikan beberapa output audio daripada peranti anda, jadi anda mungkin perlu menggunakan peranti tambahan untuk memainkan teks yang diterjemahkan.
    >
    > Sebagai contoh, jika anda melatih LUIS dalam Bahasa Inggeris, tetapi ingin menggunakan Bahasa Perancis sebagai bahasa pengguna, anda boleh menterjemah ayat seperti "set a 2 minute and 27 second timer" daripada Bahasa Inggeris ke Bahasa Perancis menggunakan Bing Translate, kemudian gunakan butang **Listen translation** untuk bercakap terjemahan ke dalam mikrofon anda.
    >
    > ![Butang listen translation pada Bing translate](../../../../../translated_images/ms/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Gantikan deklarasi `recognizer_config` dan `recognizer` dengan yang berikut:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    Ini mencipta konfigurasi terjemahan untuk mengenali ucapan dalam bahasa pengguna, dan mencipta terjemahan dalam bahasa pengguna dan pelayan. Ia kemudian menggunakan konfigurasi ini untuk mencipta pengenal terjemahan - pengenal ucapan yang boleh menterjemah output pengenalan ucapan kepada pelbagai bahasa.

    > 💁 Bahasa asal perlu dinyatakan dalam `target_languages`, jika tidak, anda tidak akan mendapat sebarang terjemahan.

1. Kemas kini fungsi `recognized`, gantikan keseluruhan kandungan fungsi dengan yang berikut:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    Kod ini memeriksa sama ada acara yang dikenali dicetuskan kerana ucapan diterjemahkan (acara ini boleh dicetuskan pada masa lain, seperti apabila ucapan dikenali tetapi tidak diterjemahkan). Jika ucapan diterjemahkan, ia mencari terjemahan dalam kamus `args.result.translations` yang sepadan dengan bahasa pelayan.

    Kamus `args.result.translations` menggunakan kunci bahagian bahasa daripada tetapan lokal, bukan keseluruhan tetapan. Sebagai contoh, jika anda meminta terjemahan ke dalam `fr-FR` untuk Bahasa Perancis, kamus akan mengandungi entri untuk `fr`, bukan `fr-FR`.

    Teks yang diterjemahkan kemudian dihantar ke IoT Hub.

1. Jalankan kod ini untuk menguji terjemahan. Pastikan aplikasi fungsi anda berjalan, dan minta pemasa dalam bahasa pengguna, sama ada dengan bercakap dalam bahasa itu sendiri, atau menggunakan aplikasi terjemahan.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## Menterjemah teks menggunakan perkhidmatan Translator

Perkhidmatan ucapan tidak menyokong terjemahan teks kembali kepada ucapan, sebaliknya anda boleh menggunakan perkhidmatan Translator untuk menterjemah teks. Perkhidmatan ini mempunyai REST API yang boleh anda gunakan untuk menterjemah teks.

### Tugasan - gunakan sumber Translator untuk menterjemah teks

1. Tambahkan kunci API Translator di bawah `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Gantikan `<key>` dengan kunci API untuk sumber perkhidmatan Translator anda.

1. Di atas fungsi `say`, tentukan fungsi `translate_text` yang akan menterjemah teks daripada bahasa pelayan kepada bahasa pengguna:

    ```python
    def translate_text(text):
    ```

1. Di dalam fungsi ini, tentukan URL dan header untuk panggilan REST API:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL untuk API ini tidak khusus lokasi, sebaliknya lokasi dihantar sebagai header. Kunci API digunakan secara langsung, jadi tidak seperti perkhidmatan ucapan, tiada keperluan untuk mendapatkan token akses daripada API penerbit token.

1. Di bawah ini, tentukan parameter dan badan untuk panggilan:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` menentukan parameter untuk dihantar kepada panggilan API, menghantar bahasa asal dan bahasa sasaran. Panggilan ini akan menterjemah teks dalam bahasa `from` kepada bahasa `to`.

    `body` mengandungi teks untuk diterjemahkan. Ini adalah array, kerana beberapa blok teks boleh diterjemahkan dalam panggilan yang sama.

1. Buat panggilan kepada REST API, dan dapatkan respons:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Respons yang diterima kembali adalah array JSON, dengan satu item yang mengandungi terjemahan. Item ini mempunyai array untuk terjemahan semua item yang dihantar dalam badan.

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

1. Kembalikan sifat `text` daripada terjemahan pertama daripada item pertama dalam array:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Kemas kini fungsi `say` untuk menterjemah teks sebelum SSML dihasilkan:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    Kod ini juga mencetak versi asal dan terjemahan teks ke konsol.

1. Jalankan kod anda. Pastikan aplikasi fungsi anda berjalan, dan minta pemasa dalam bahasa pengguna, sama ada dengan bercakap dalam bahasa itu sendiri, atau menggunakan aplikasi terjemahan.

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

    > 💁 Disebabkan cara yang berbeza untuk mengatakan sesuatu dalam pelbagai bahasa, anda mungkin mendapat terjemahan yang sedikit berbeza daripada contoh yang anda berikan kepada LUIS. Jika ini berlaku, tambahkan lebih banyak contoh kepada LUIS, latih semula, kemudian terbitkan semula model.

> 💁 Anda boleh menemui kod ini dalam folder [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device).

😀 Program pemasa berbilang bahasa anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.