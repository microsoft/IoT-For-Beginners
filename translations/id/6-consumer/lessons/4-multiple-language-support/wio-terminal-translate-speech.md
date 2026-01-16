<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f6c164e349f8989959e02a90f37908d",
  "translation_date": "2025-08-27T22:55:55+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/wio-terminal-translate-speech.md",
  "language_code": "id"
}
-->
# Menerjemahkan Ucapan - Wio Terminal

Dalam bagian pelajaran ini, Anda akan menulis kode untuk menerjemahkan teks menggunakan layanan penerjemah.

## Mengubah teks menjadi ucapan menggunakan layanan penerjemah

REST API layanan ucapan tidak mendukung terjemahan langsung, tetapi Anda dapat menggunakan layanan Translator untuk menerjemahkan teks yang dihasilkan oleh layanan ucapan ke teks, serta teks dari respons yang diucapkan. Layanan ini memiliki REST API yang dapat Anda gunakan untuk menerjemahkan teks, tetapi untuk mempermudah penggunaannya, ini akan dibungkus dalam pemicu HTTP lain di aplikasi fungsi Anda.

### Tugas - membuat fungsi serverless untuk menerjemahkan teks

1. Buka proyek `smart-timer-trigger` Anda di VS Code, dan buka terminal dengan memastikan lingkungan virtual telah diaktifkan. Jika belum, matikan dan buat ulang terminal.

1. Buka file `local.settings.json` dan tambahkan pengaturan untuk kunci API penerjemah dan lokasi:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    Ganti `<key>` dengan kunci API untuk sumber daya layanan penerjemah Anda. Ganti `<location>` dengan lokasi yang Anda gunakan saat membuat sumber daya layanan penerjemah.

1. Tambahkan pemicu HTTP baru ke aplikasi ini yang disebut `translate-text` menggunakan perintah berikut dari dalam terminal VS Code di folder root proyek aplikasi fungsi:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    Ini akan membuat pemicu HTTP yang disebut `translate-text`.

1. Ganti isi file `__init__.py` di folder `translate-text` dengan yang berikut:

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

    Kode ini mengekstrak teks dan bahasa dari permintaan HTTP. Kemudian membuat permintaan ke REST API penerjemah, melewatkan bahasa sebagai parameter untuk URL dan teks yang akan diterjemahkan sebagai isi. Akhirnya, terjemahan dikembalikan.

1. Jalankan aplikasi fungsi Anda secara lokal. Anda kemudian dapat memanggilnya menggunakan alat seperti curl dengan cara yang sama seperti Anda menguji pemicu HTTP `text-to-timer`. Pastikan untuk melewatkan teks yang akan diterjemahkan dan bahasa sebagai isi JSON:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    Contoh ini menerjemahkan *Définir une minuterie de 30 secondes* dari bahasa Prancis ke bahasa Inggris AS. Ini akan mengembalikan *Set a 30-second timer*.

> 💁 Anda dapat menemukan kode ini di folder [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions).

### Tugas - menggunakan fungsi penerjemah untuk menerjemahkan teks

1. Buka proyek `smart-timer` di VS Code jika belum terbuka.

1. Timer pintar Anda akan memiliki 2 bahasa yang diatur - bahasa server yang digunakan untuk melatih LUIS (bahasa yang sama juga digunakan untuk membangun pesan yang akan diucapkan kepada pengguna), dan bahasa yang diucapkan oleh pengguna. Perbarui konstanta `LANGUAGE` di file header `config.h` menjadi bahasa yang akan diucapkan oleh pengguna, dan tambahkan konstanta baru yang disebut `SERVER_LANGUAGE` untuk bahasa yang digunakan untuk melatih LUIS:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    Ganti `<user language>` dengan nama lokal untuk bahasa yang akan Anda gunakan, misalnya `fr-FR` untuk bahasa Prancis, atau `zn-HK` untuk bahasa Kanton.

    Ganti `<server language>` dengan nama lokal untuk bahasa yang digunakan untuk melatih LUIS.

    Anda dapat menemukan daftar bahasa yang didukung dan nama lokalnya di [Dokumentasi dukungan bahasa dan suara di Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Jika Anda tidak berbicara dalam beberapa bahasa, Anda dapat menggunakan layanan seperti [Bing Translate](https://www.bing.com/translator) atau [Google Translate](https://translate.google.com) untuk menerjemahkan dari bahasa pilihan Anda ke bahasa lain. Layanan ini kemudian dapat memutar audio dari teks yang diterjemahkan.
    >
    > Misalnya, jika Anda melatih LUIS dalam bahasa Inggris, tetapi ingin menggunakan bahasa Prancis sebagai bahasa pengguna, Anda dapat menerjemahkan kalimat seperti "set a 2 minute and 27 second timer" dari bahasa Inggris ke bahasa Prancis menggunakan Bing Translate, lalu gunakan tombol **Listen translation** untuk mengucapkan terjemahan ke mikrofon Anda.
    >
    > ![Tombol listen translation di Bing translate](../../../../../translated_images/id/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Tambahkan kunci API penerjemah dan lokasi di bawah `SPEECH_LOCATION`:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    Ganti `<KEY>` dengan kunci API untuk sumber daya layanan penerjemah Anda. Ganti `<LOCATION>` dengan lokasi yang Anda gunakan saat membuat sumber daya layanan penerjemah.

1. Tambahkan URL pemicu penerjemah di bawah `VOICE_URL`:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    Ganti `<URL>` dengan URL untuk pemicu HTTP `translate-text` di aplikasi fungsi Anda. Ini akan sama dengan nilai untuk `TEXT_TO_TIMER_FUNCTION_URL`, kecuali dengan nama fungsi `translate-text` alih-alih `text-to-timer`.

1. Tambahkan file baru ke folder `src` yang disebut `text_translator.h`.

1. File header `text_translator.h` baru ini akan berisi kelas untuk menerjemahkan teks. Tambahkan yang berikut ke file ini untuk mendeklarasikan kelas ini:

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

    Ini mendeklarasikan kelas `TextTranslator`, bersama dengan instance dari kelas ini. Kelas ini memiliki satu field untuk klien WiFi.

1. Ke bagian `public` dari kelas ini, tambahkan metode untuk menerjemahkan teks:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    Metode ini mengambil bahasa untuk diterjemahkan dari, dan bahasa untuk diterjemahkan ke. Saat menangani ucapan, ucapan akan diterjemahkan dari bahasa pengguna ke bahasa server LUIS, dan saat memberikan respons, ini akan menerjemahkan dari bahasa server LUIS ke bahasa pengguna.

1. Dalam metode ini, tambahkan kode untuk membangun isi JSON yang berisi teks yang akan diterjemahkan dan bahasa:

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

1. Di bawah ini, tambahkan kode untuk mengirim isi ke aplikasi fungsi serverless:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Selanjutnya, tambahkan kode untuk mendapatkan respons:

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

1. Akhirnya, tambahkan kode untuk menutup koneksi dan mengembalikan teks yang diterjemahkan:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### Tugas - menerjemahkan ucapan yang dikenali dan respons

1. Buka file `main.cpp`.

1. Tambahkan directive include di bagian atas file untuk file header kelas `TextTranslator`:

    ```cpp
    #include "text_translator.h"
    ```

1. Teks yang diucapkan saat timer diatur atau berakhir perlu diterjemahkan. Untuk melakukan ini, tambahkan yang berikut sebagai baris pertama dari fungsi `say`:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Ini akan menerjemahkan teks ke bahasa pengguna.

1. Dalam fungsi `processAudio`, teks diambil dari audio yang ditangkap dengan panggilan `String text = speechToText.convertSpeechToText();`. Setelah panggilan ini, terjemahkan teks:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Ini akan menerjemahkan teks dari bahasa pengguna ke bahasa yang digunakan di server.

1. Bangun kode ini, unggah ke Wio Terminal Anda, dan uji melalui serial monitor. Setelah Anda melihat `Ready` di serial monitor, tekan tombol C (yang ada di sisi kiri, paling dekat dengan saklar daya), dan berbicaralah. Pastikan aplikasi fungsi Anda berjalan, dan minta timer dalam bahasa pengguna, baik dengan berbicara dalam bahasa tersebut sendiri, atau menggunakan aplikasi penerjemah.

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

> 💁 Anda dapat menemukan kode ini di folder [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal).

😀 Program timer multibahasa Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.