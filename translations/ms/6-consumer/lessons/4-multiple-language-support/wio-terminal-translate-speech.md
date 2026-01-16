<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f6c164e349f8989959e02a90f37908d",
  "translation_date": "2025-08-27T22:56:15+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/wio-terminal-translate-speech.md",
  "language_code": "ms"
}
-->
# Terjemah Ucapan - Wio Terminal

Dalam bahagian pelajaran ini, anda akan menulis kod untuk menterjemah teks menggunakan perkhidmatan penterjemah.

## Tukar teks kepada ucapan menggunakan perkhidmatan penterjemah

REST API perkhidmatan ucapan tidak menyokong terjemahan secara langsung, tetapi anda boleh menggunakan perkhidmatan Translator untuk menterjemah teks yang dihasilkan oleh perkhidmatan ucapan ke teks, serta teks respons yang diucapkan. Perkhidmatan ini mempunyai REST API yang boleh digunakan untuk menterjemah teks, tetapi untuk memudahkan penggunaannya, ia akan dibungkus dalam satu lagi pencetus HTTP dalam aplikasi fungsi anda.

### Tugasan - buat fungsi tanpa pelayan untuk menterjemah teks

1. Buka projek `smart-timer-trigger` anda dalam VS Code, dan buka terminal dengan memastikan persekitaran maya diaktifkan. Jika tidak, matikan dan buat semula terminal.

1. Buka fail `local.settings.json` dan tambahkan tetapan untuk kunci API penterjemah dan lokasi:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    Gantikan `<key>` dengan kunci API untuk sumber perkhidmatan penterjemah anda. Gantikan `<location>` dengan lokasi yang anda gunakan semasa mencipta sumber perkhidmatan penterjemah.

1. Tambahkan pencetus HTTP baharu ke aplikasi ini yang dipanggil `translate-text` menggunakan arahan berikut dari dalam terminal VS Code di folder akar projek aplikasi fungsi:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    Ini akan mencipta pencetus HTTP yang dipanggil `translate-text`.

1. Gantikan kandungan fail `__init__.py` dalam folder `translate-text` dengan yang berikut:

    ```python
    import logging
    import os
    import requests
    
    import azure.functions as func
    
    location = os.environ['TRANSLATOR_LOCATION']
    translator_key = os.environ['TRANSLATOR_KEY']
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        from_language = req_body['from_language']
        to_language = req_body['to_language']
        text = req_body['text']
        
        logging.info(f'Translating {text} from {from_language} to {to_language}')
    
        url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'
    
        headers = {
            'Ocp-Apim-Subscription-Key': translator_key,
            'Ocp-Apim-Subscription-Region': location,
            'Content-type': 'application/json'
        }
    
        params = {
            'from': from_language,
            'to': to_language
        }
    
        body = [{
            'text' : text
        }]
        
        response = requests.post(url, headers=headers, params=params, json=body)
        return func.HttpResponse(response.json()[0]['translations'][0]['text'])
    ```

    Kod ini mengekstrak teks dan bahasa daripada permintaan HTTP. Ia kemudian membuat permintaan kepada REST API penterjemah, menghantar bahasa sebagai parameter untuk URL dan teks untuk diterjemahkan sebagai badan. Akhirnya, terjemahan dikembalikan.

1. Jalankan aplikasi fungsi anda secara tempatan. Anda kemudian boleh memanggilnya menggunakan alat seperti curl dengan cara yang sama seperti anda menguji pencetus HTTP `text-to-timer`. Pastikan untuk menghantar teks untuk diterjemahkan dan bahasa sebagai badan JSON:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    Contoh ini menterjemah *Définir une minuterie de 30 secondes* daripada bahasa Perancis ke bahasa Inggeris AS. Ia akan mengembalikan *Set a 30-second timer*.

> 💁 Anda boleh menemui kod ini dalam folder [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions).

### Tugasan - gunakan fungsi penterjemah untuk menterjemah teks

1. Buka projek `smart-timer` dalam VS Code jika ia belum dibuka.

1. Pemasa pintar anda akan mempunyai 2 bahasa yang ditetapkan - bahasa pelayan yang digunakan untuk melatih LUIS (bahasa yang sama juga digunakan untuk membina mesej untuk bercakap dengan pengguna), dan bahasa yang dituturkan oleh pengguna. Kemas kini pemalar `LANGUAGE` dalam fail header `config.h` kepada bahasa yang akan dituturkan oleh pengguna, dan tambahkan pemalar baharu yang dipanggil `SERVER_LANGUAGE` untuk bahasa yang digunakan untuk melatih LUIS:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    Gantikan `<user language>` dengan nama lokal untuk bahasa yang akan anda gunakan, contohnya `fr-FR` untuk bahasa Perancis, atau `zn-HK` untuk bahasa Kantonis.

    Gantikan `<server language>` dengan nama lokal untuk bahasa yang digunakan untuk melatih LUIS.

    Anda boleh menemui senarai bahasa yang disokong dan nama lokal mereka dalam [dokumentasi sokongan bahasa dan suara di Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Jika anda tidak bercakap dalam pelbagai bahasa, anda boleh menggunakan perkhidmatan seperti [Bing Translate](https://www.bing.com/translator) atau [Google Translate](https://translate.google.com) untuk menterjemah daripada bahasa pilihan anda kepada bahasa pilihan lain. Perkhidmatan ini kemudian boleh memainkan audio teks yang diterjemahkan.
    >
    > Sebagai contoh, jika anda melatih LUIS dalam bahasa Inggeris, tetapi ingin menggunakan bahasa Perancis sebagai bahasa pengguna, anda boleh menterjemah ayat seperti "set a 2 minute and 27 second timer" daripada bahasa Inggeris ke bahasa Perancis menggunakan Bing Translate, kemudian gunakan butang **Listen translation** untuk bercakap terjemahan ke mikrofon anda.
    >
    > ![Butang listen translation pada Bing translate](../../../../../translated_images/ms/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Tambahkan kunci API penterjemah dan lokasi di bawah `SPEECH_LOCATION`:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    Gantikan `<KEY>` dengan kunci API untuk sumber perkhidmatan penterjemah anda. Gantikan `<LOCATION>` dengan lokasi yang anda gunakan semasa mencipta sumber perkhidmatan penterjemah.

1. Tambahkan URL pencetus penterjemah di bawah `VOICE_URL`:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    Gantikan `<URL>` dengan URL untuk pencetus HTTP `translate-text` pada aplikasi fungsi anda. Ini akan sama dengan nilai untuk `TEXT_TO_TIMER_FUNCTION_URL`, kecuali dengan nama fungsi `translate-text` dan bukannya `text-to-timer`.

1. Tambahkan fail baharu ke folder `src` yang dipanggil `text_translator.h`.

1. Fail header `text_translator.h` baharu ini akan mengandungi kelas untuk menterjemah teks. Tambahkan yang berikut ke fail ini untuk mengisytiharkan kelas ini:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    
    class TextTranslator
    {
    public:   
    private:
        WiFiClient _client;
    };
    
    TextTranslator textTranslator;
    ```

    Ini mengisytiharkan kelas `TextTranslator`, bersama dengan satu contoh kelas ini. Kelas ini mempunyai satu medan untuk klien WiFi.

1. Pada bahagian `public` kelas ini, tambahkan kaedah untuk menterjemah teks:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    Kaedah ini mengambil bahasa untuk diterjemahkan daripada, dan bahasa untuk diterjemahkan kepada. Apabila mengendalikan ucapan, ucapan akan diterjemahkan daripada bahasa pengguna kepada bahasa pelayan LUIS, dan apabila memberikan respons, ia akan diterjemahkan daripada bahasa pelayan LUIS kepada bahasa pengguna.

1. Dalam kaedah ini, tambahkan kod untuk membina badan JSON yang mengandungi teks untuk diterjemahkan dan bahasa:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;
    doc["from_language"] = from_language;
    doc["to_language"] = to_language;

    String body;
    serializeJson(doc, body);

    Serial.print("Translating ");
    Serial.print(text);
    Serial.print(" from ");
    Serial.print(from_language);
    Serial.print(" to ");
    Serial.print(to_language);
    ```

1. Di bawah ini, tambahkan kod untuk menghantar badan ke aplikasi fungsi tanpa pelayan:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Seterusnya, tambahkan kod untuk mendapatkan respons:

    ```cpp
    String translated_text = "";

    if (httpResponseCode == 200)
    {
        translated_text = httpClient.getString();
        Serial.print("Translated: ");
        Serial.println(translated_text);
    }
    else
    {
        Serial.print("Failed to translate text - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. Akhir sekali, tambahkan kod untuk menutup sambungan dan mengembalikan teks yang diterjemahkan:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### Tugasan - terjemah ucapan yang dikenali dan respons

1. Buka fail `main.cpp`.

1. Tambahkan arahan include di bahagian atas fail untuk fail header kelas `TextTranslator`:

    ```cpp
    #include "text_translator.h"
    ```

1. Teks yang diucapkan apabila pemasa ditetapkan atau tamat perlu diterjemahkan. Untuk melakukan ini, tambahkan yang berikut sebagai baris pertama fungsi `say`:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Ini akan menterjemah teks kepada bahasa pengguna.

1. Dalam fungsi `processAudio`, teks diperoleh daripada audio yang ditangkap dengan panggilan `String text = speechToText.convertSpeechToText();`. Selepas panggilan ini, terjemahkan teks:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Ini akan menterjemah teks daripada bahasa pengguna ke bahasa yang digunakan pada pelayan.

1. Bina kod ini, muat naik ke Wio Terminal anda dan uji melalui monitor bersiri. Sebaik sahaja anda melihat `Ready` dalam monitor bersiri, tekan butang C (yang di sebelah kiri, paling dekat dengan suis kuasa), dan bercakap. Pastikan aplikasi fungsi anda berjalan, dan minta pemasa dalam bahasa pengguna, sama ada dengan bercakap dalam bahasa itu sendiri, atau menggunakan aplikasi terjemahan.

    ```output
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Définir une minuterie de 2 minutes 27 secondes.","Offset":9600000,"Duration":40400000}
    Translating Définir une minuterie de 2 minutes 27 secondes. from fr-FR to en-US
    Translated: Set a timer of 2 minutes 27 seconds.
    Set a timer of 2 minutes 27 seconds.
    {"seconds": 147}
    Translating 2 minute 27 second timer started. from en-US to fr-FR
    Translated: 2 minute 27 seconde minute a commencé.
    2 minute 27 seconde minute a commencé.
    Translating Times up on your 2 minute 27 second timer. from en-US to fr-FR
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

> 💁 Anda boleh menemui kod ini dalam folder [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal).

😀 Program pemasa pelbagai bahasa anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.