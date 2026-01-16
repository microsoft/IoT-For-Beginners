<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "bbb5aa34221fe129dd3ce4d9ec33831a",
  "translation_date": "2025-08-27T23:00:59+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/pi-translate-speech.md",
  "language_code": "ms"
}
-->
# Terjemah ucapan - Raspberry Pi

Dalam bahagian pelajaran ini, anda akan menulis kod untuk menterjemah teks menggunakan perkhidmatan penterjemah.

## Tukar teks kepada ucapan menggunakan perkhidmatan penterjemah

REST API perkhidmatan ucapan tidak menyokong terjemahan secara langsung, sebaliknya anda boleh menggunakan perkhidmatan Translator untuk menterjemah teks yang dihasilkan oleh perkhidmatan ucapan ke teks, dan teks untuk respons yang diucapkan. Perkhidmatan ini mempunyai REST API yang boleh anda gunakan untuk menterjemah teks.

### Tugasan - gunakan sumber penterjemah untuk menterjemah teks

1. Pemasa pintar anda akan mempunyai 2 bahasa yang ditetapkan - bahasa pelayan yang digunakan untuk melatih LUIS (bahasa yang sama juga digunakan untuk membina mesej untuk bercakap dengan pengguna), dan bahasa yang digunakan oleh pengguna. Kemas kini pemboleh ubah `language` kepada bahasa yang akan digunakan oleh pengguna, dan tambahkan pemboleh ubah baru yang dipanggil `server_language` untuk bahasa yang digunakan untuk melatih LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Gantikan `<user language>` dengan nama lokal untuk bahasa yang akan anda gunakan, contohnya `fr-FR` untuk Bahasa Perancis, atau `zn-HK` untuk Bahasa Kantonis.

    Gantikan `<server language>` dengan nama lokal untuk bahasa yang digunakan untuk melatih LUIS.

    Anda boleh mencari senarai bahasa yang disokong dan nama lokal mereka dalam [Dokumentasi sokongan bahasa dan suara di Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Jika anda tidak bercakap dalam pelbagai bahasa, anda boleh menggunakan perkhidmatan seperti [Bing Translate](https://www.bing.com/translator) atau [Google Translate](https://translate.google.com) untuk menterjemah daripada bahasa pilihan anda kepada bahasa lain. Perkhidmatan ini juga boleh memainkan audio teks yang diterjemahkan.
    >
    > Sebagai contoh, jika anda melatih LUIS dalam Bahasa Inggeris, tetapi ingin menggunakan Bahasa Perancis sebagai bahasa pengguna, anda boleh menterjemah ayat seperti "set a 2 minute and 27 second timer" daripada Bahasa Inggeris ke Bahasa Perancis menggunakan Bing Translate, kemudian gunakan butang **Listen translation** untuk bercakap terjemahan ke mikrofon anda.
    >
    > ![Butang listen translation pada Bing translate](../../../../../translated_images/ms/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Tambahkan kunci API penterjemah di bawah `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Gantikan `<key>` dengan kunci API untuk sumber perkhidmatan penterjemah anda.

1. Di atas fungsi `say`, tentukan fungsi `translate_text` yang akan menterjemah teks daripada bahasa pelayan kepada bahasa pengguna:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    Bahasa asal dan bahasa sasaran dihantar kepada fungsi ini - aplikasi anda perlu menukar daripada bahasa pengguna kepada bahasa pelayan semasa mengenali ucapan, dan daripada bahasa pelayan kepada bahasa pengguna semasa memberikan maklum balas yang diucapkan.

1. Di dalam fungsi ini, tentukan URL dan header untuk panggilan REST API:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL untuk API ini tidak spesifik lokasi, sebaliknya lokasi dihantar sebagai header. Kunci API digunakan secara langsung, jadi tidak seperti perkhidmatan ucapan, tiada keperluan untuk mendapatkan token akses daripada API penerbit token.

1. Di bawah ini, tentukan parameter dan badan untuk panggilan:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` menentukan parameter untuk dihantar kepada panggilan API, menghantar bahasa asal dan bahasa sasaran. Panggilan ini akan menterjemah teks dalam bahasa `from` kepada bahasa `to`.

    `body` mengandungi teks untuk diterjemahkan. Ini adalah array, kerana beberapa blok teks boleh diterjemahkan dalam satu panggilan.

1. Lakukan panggilan REST API, dan dapatkan respons:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Respons yang diterima adalah array JSON, dengan satu item yang mengandungi terjemahan. Item ini mempunyai array untuk terjemahan semua item yang dihantar dalam badan.

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

1. Kembalikan sifat `test` daripada terjemahan pertama daripada item pertama dalam array:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Kemas kini gelung `while True` untuk menterjemah teks daripada panggilan kepada `convert_speech_to_text` daripada bahasa pengguna kepada bahasa pelayan:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    Kod ini juga mencetak versi asal dan versi terjemahan teks ke konsol.

1. Kemas kini fungsi `say` untuk menterjemah teks yang akan diucapkan daripada bahasa pelayan kepada bahasa pengguna:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    Kod ini juga mencetak versi asal dan versi terjemahan teks ke konsol.

1. Jalankan kod anda. Pastikan aplikasi fungsi anda berjalan, dan minta pemasa dalam bahasa pengguna, sama ada dengan bercakap dalam bahasa tersebut sendiri, atau menggunakan aplikasi terjemahan.

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

    > 💁 Disebabkan cara yang berbeza untuk mengatakan sesuatu dalam pelbagai bahasa, anda mungkin mendapat terjemahan yang sedikit berbeza daripada contoh yang anda berikan kepada LUIS. Jika ini berlaku, tambahkan lebih banyak contoh kepada LUIS, latih semula kemudian terbitkan semula model.

> 💁 Anda boleh mencari kod ini dalam folder [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi).

😀 Program pemasa pelbagai bahasa anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.