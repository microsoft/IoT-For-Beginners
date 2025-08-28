<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-27T23:16:52+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "id"
}
-->
# Text to Speech - Wio Terminal

Dalam bagian pelajaran ini, Anda akan mengubah teks menjadi suara untuk memberikan umpan balik yang dapat didengar.

## Teks ke Suara

SDK layanan suara yang Anda gunakan dalam pelajaran sebelumnya untuk mengubah suara menjadi teks juga dapat digunakan untuk mengubah teks kembali menjadi suara.

## Mendapatkan Daftar Suara

Saat meminta suara, Anda perlu menentukan suara yang akan digunakan karena suara dapat dihasilkan menggunakan berbagai jenis suara. Setiap bahasa mendukung berbagai suara, dan Anda dapat mendapatkan daftar suara yang didukung untuk setiap bahasa dari SDK layanan suara. Keterbatasan mikrocontroller berperan di sini - panggilan untuk mendapatkan daftar suara yang didukung oleh layanan teks ke suara adalah dokumen JSON berukuran lebih dari 77KB, terlalu besar untuk diproses oleh Wio Terminal. Pada saat penulisan, daftar lengkap berisi 215 suara, masing-masing didefinisikan oleh dokumen JSON seperti berikut:

```json
{
    "Name": "Microsoft Server Speech Text to Speech Voice (en-US, AriaNeural)",
    "DisplayName": "Aria",
    "LocalName": "Aria",
    "ShortName": "en-US-AriaNeural",
    "Gender": "Female",
    "Locale": "en-US",
    "StyleList": [
        "chat",
        "customerservice",
        "narration-professional",
        "newscast-casual",
        "newscast-formal",
        "cheerful",
        "empathetic"
    ],
    "SampleRateHertz": "24000",
    "VoiceType": "Neural",
    "Status": "GA"
}
```

JSON ini untuk suara **Aria**, yang memiliki beberapa gaya suara. Yang diperlukan saat mengubah teks menjadi suara adalah shortname, `en-US-AriaNeural`.

Alih-alih mengunduh dan mendekode seluruh daftar ini di mikrocontroller Anda, Anda perlu menulis kode serverless untuk mengambil daftar suara untuk bahasa yang Anda gunakan, dan memanggilnya dari Wio Terminal Anda. Kode Anda kemudian dapat memilih suara yang sesuai dari daftar, seperti suara pertama yang ditemukan.

### Tugas - Membuat Fungsi Serverless untuk Mendapatkan Daftar Suara

1. Buka proyek `smart-timer-trigger` Anda di VS Code, dan buka terminal memastikan lingkungan virtual diaktifkan. Jika tidak, matikan dan buat ulang terminal.

1. Buka file `local.settings.json` dan tambahkan pengaturan untuk kunci API layanan suara dan lokasi:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    Ganti `<key>` dengan kunci API untuk sumber daya layanan suara Anda. Ganti `<location>` dengan lokasi yang Anda gunakan saat membuat sumber daya layanan suara.

1. Tambahkan pemicu HTTP baru ke aplikasi ini yang disebut `get-voices` menggunakan perintah berikut dari dalam terminal VS Code di folder root proyek aplikasi fungsi:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    Ini akan membuat pemicu HTTP yang disebut `get-voices`.

1. Ganti isi file `__init__.py` di folder `get-voices` dengan yang berikut:

    ```python
    import json
    import os
    import requests
    
    import azure.functions as func
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        location = os.environ['SPEECH_LOCATION']
        speech_key = os.environ['SPEECH_KEY']
    
        req_body = req.get_json()
        language = req_body['language']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        voices = filter(lambda x: x['Locale'].lower() == language.lower(), voices_json)
        voices = map(lambda x: x['ShortName'], voices)
    
        return func.HttpResponse(json.dumps(list(voices)), status_code=200)
    ```

    Kode ini membuat permintaan HTTP ke endpoint untuk mendapatkan suara. Daftar suara ini adalah blok besar JSON dengan suara untuk semua bahasa, sehingga suara untuk bahasa yang diteruskan dalam body permintaan difilter, kemudian shortname diekstraksi dan dikembalikan sebagai daftar JSON. Shortname adalah nilai yang diperlukan untuk mengubah teks menjadi suara, sehingga hanya nilai ini yang dikembalikan.

    > 💁 Anda dapat mengubah filter sesuai kebutuhan untuk memilih hanya suara yang Anda inginkan.

    Ini mengurangi ukuran data dari 77KB (pada saat penulisan), menjadi dokumen JSON yang jauh lebih kecil. Misalnya, untuk suara AS ini adalah 408 byte.

1. Jalankan aplikasi fungsi Anda secara lokal. Anda kemudian dapat memanggilnya menggunakan alat seperti curl dengan cara yang sama seperti Anda menguji pemicu HTTP `text-to-timer`. Pastikan untuk meneruskan bahasa Anda sebagai body JSON:

    ```json
    {
        "language":"<language>"
    }
    ```

    Ganti `<language>` dengan bahasa Anda, seperti `en-GB`, atau `zh-CN`.

> 💁 Anda dapat menemukan kode ini di folder [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Tugas - Mengambil Suara dari Wio Terminal Anda

1. Buka proyek `smart-timer` Anda di VS Code jika belum terbuka.

1. Buka file header `config.h` dan tambahkan URL untuk aplikasi fungsi Anda:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    Ganti `<URL>` dengan URL untuk pemicu HTTP `get-voices` pada aplikasi fungsi Anda. Ini akan sama dengan nilai untuk `TEXT_TO_TIMER_FUNCTION_URL`, kecuali dengan nama fungsi `get-voices` alih-alih `text-to-timer`.

1. Buat file baru di folder `src` yang disebut `text_to_speech.h`. File ini akan digunakan untuk mendefinisikan kelas untuk mengubah teks menjadi suara.

1. Tambahkan direktif include berikut ke bagian atas file `text_to_speech.h` yang baru:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <Seeed_FS.h>
    #include <SD/Seeed_SD.h>
    #include <WiFiClient.h>
    #include <WiFiClientSecure.h>
    
    #include "config.h"
    #include "speech_to_text.h"
    ```

1. Tambahkan kode berikut di bawah ini untuk mendeklarasikan kelas `TextToSpeech`, bersama dengan instance yang dapat digunakan di seluruh aplikasi:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. Untuk memanggil aplikasi fungsi Anda, Anda perlu mendeklarasikan klien WiFi. Tambahkan yang berikut ke bagian `private` dari kelas:

    ```cpp
    WiFiClient _client;
    ```

1. Di bagian `private`, tambahkan field untuk suara yang dipilih:

    ```cpp
    String _voice;
    ```

1. Ke bagian `public`, tambahkan fungsi `init` yang akan mendapatkan suara pertama:

    ```cpp
    void init()
    {
    }
    ```

1. Untuk mendapatkan suara, dokumen JSON perlu dikirim ke aplikasi fungsi dengan bahasa. Tambahkan kode berikut ke fungsi `init` untuk membuat dokumen JSON ini:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. Selanjutnya buat `HTTPClient`, lalu gunakan untuk memanggil aplikasi fungsi untuk mendapatkan suara, memposting dokumen JSON:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Di bawah ini tambahkan kode untuk memeriksa kode respons, dan jika 200 (berhasil), maka ekstrak daftar suara, mengambil suara pertama dari daftar:

    ```cpp
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonArray obj = doc.as<JsonArray>();
        _voice = obj[0].as<String>();

        Serial.print("Using voice ");
        Serial.println(_voice);
    }
    else
    {
        Serial.print("Failed to get voices - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. Setelah ini, akhiri koneksi klien HTTP:

    ```cpp
    httpClient.end();
    ```

1. Buka file `main.cpp`, dan tambahkan direktif include berikut di bagian atas untuk menyertakan file header baru ini:

    ```cpp
    #include "text_to_speech.h"
    ```

1. Di fungsi `setup`, di bawah panggilan ke `speechToText.init();`, tambahkan yang berikut untuk menginisialisasi kelas `TextToSpeech`:

    ```cpp
    textToSpeech.init();
    ```

1. Bangun kode ini, unggah ke Wio Terminal Anda, dan uji melalui serial monitor. Pastikan aplikasi fungsi Anda berjalan.

    Anda akan melihat daftar suara yang tersedia dikembalikan dari aplikasi fungsi, bersama dengan suara yang dipilih.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    ["en-US-JennyNeural", "en-US-JennyMultilingualNeural", "en-US-GuyNeural", "en-US-AriaNeural", "en-US-AmberNeural", "en-US-AnaNeural", "en-US-AshleyNeural", "en-US-BrandonNeural", "en-US-ChristopherNeural", "en-US-CoraNeural", "en-US-ElizabethNeural", "en-US-EricNeural", "en-US-JacobNeural", "en-US-MichelleNeural", "en-US-MonicaNeural", "en-US-AriaRUS", "en-US-BenjaminRUS", "en-US-GuyRUS", "en-US-ZiraRUS"]
    Using voice en-US-JennyNeural
    Ready.
    ```

## Mengubah Teks Menjadi Suara

Setelah Anda memiliki suara untuk digunakan, suara tersebut dapat digunakan untuk mengubah teks menjadi suara. Keterbatasan memori yang sama dengan suara juga berlaku saat mengubah suara menjadi teks, sehingga Anda perlu menulis suara ke kartu SD agar dapat diputar melalui ReSpeaker.

> 💁 Dalam pelajaran sebelumnya dalam proyek ini, Anda menggunakan memori flash untuk menyimpan suara yang ditangkap dari mikrofon. Pelajaran ini menggunakan kartu SD karena lebih mudah memutar audio darinya menggunakan pustaka audio Seeed.

Ada juga keterbatasan lain yang perlu dipertimbangkan, yaitu data audio yang tersedia dari layanan suara, dan format yang didukung oleh Wio Terminal. Tidak seperti komputer penuh, pustaka audio untuk mikrocontroller bisa sangat terbatas dalam format audio yang didukung. Misalnya, pustaka Seeed Arduino Audio yang dapat memutar suara melalui ReSpeaker hanya mendukung audio dengan sample rate 44.1KHz. Layanan suara Azure dapat menyediakan audio dalam sejumlah format, tetapi tidak ada yang menggunakan sample rate ini, mereka hanya menyediakan 8KHz, 16KHz, 24KHz, dan 48KHz. Ini berarti audio perlu di-resample ke 44.1KHz, sesuatu yang membutuhkan lebih banyak sumber daya daripada yang dimiliki Wio Terminal, terutama memori.

Saat perlu memanipulasi data seperti ini, sering kali lebih baik menggunakan kode serverless, terutama jika data diperoleh melalui panggilan web. Wio Terminal dapat memanggil fungsi serverless, meneruskan teks untuk diubah, dan fungsi serverless dapat memanggil layanan suara untuk mengubah teks menjadi suara, serta me-resample audio ke sample rate yang diperlukan. Fungsi ini kemudian dapat mengembalikan audio dalam bentuk yang dibutuhkan Wio Terminal untuk disimpan di kartu SD dan diputar melalui ReSpeaker.

### Tugas - Membuat Fungsi Serverless untuk Mengubah Teks Menjadi Suara

1. Buka proyek `smart-timer-trigger` Anda di VS Code, dan buka terminal memastikan lingkungan virtual diaktifkan. Jika tidak, matikan dan buat ulang terminal.

1. Tambahkan pemicu HTTP baru ke aplikasi ini yang disebut `text-to-speech` menggunakan perintah berikut dari dalam terminal VS Code di folder root proyek aplikasi fungsi:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    Ini akan membuat pemicu HTTP yang disebut `text-to-speech`.

1. Paket Pip [librosa](https://librosa.org) memiliki fungsi untuk me-resample audio, jadi tambahkan ini ke file `requirements.txt`:

    ```sh
    librosa
    ```

    Setelah ini ditambahkan, instal paket Pip menggunakan perintah berikut dari terminal VS Code:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ Jika Anda menggunakan Linux, termasuk Raspberry Pi OS, Anda mungkin perlu menginstal `libsndfile` dengan perintah berikut:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. Untuk mengubah teks menjadi suara, Anda tidak dapat menggunakan kunci API layanan suara secara langsung, melainkan Anda perlu meminta token akses, menggunakan kunci API untuk mengautentikasi permintaan token akses. Buka file `__init__.py` dari folder `text-to-speech` dan ganti semua kode di dalamnya dengan yang berikut:

    ```python
    import io
    import os
    import requests
    
    import librosa
    import soundfile as sf
    import azure.functions as func
    
    location = os.environ['SPEECH_LOCATION']
    speech_key = os.environ['SPEECH_KEY']
    
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Ini mendefinisikan konstanta untuk lokasi dan kunci suara yang akan dibaca dari pengaturan. Kemudian mendefinisikan fungsi `get_access_token` yang akan mengambil token akses untuk layanan suara.

1. Di bawah kode ini, tambahkan yang berikut:

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'

    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        language = req_body['language']
        voice = req_body['voice']
        text = req_body['text']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    
        ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
        ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
        ssml += text
        ssml += '</voice>'
        ssml += '</speak>'
    
        response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    
        raw_audio, sample_rate = librosa.load(io.BytesIO(response.content), sr=48000)
        resampled = librosa.resample(raw_audio, sample_rate, 44100)
        
        output_buffer = io.BytesIO()
        sf.write(output_buffer, resampled, 44100, 'PCM_16', format='wav')
        output_buffer.seek(0)
    
        return func.HttpResponse(output_buffer.read(), status_code=200)
    ```

    Ini mendefinisikan pemicu HTTP yang mengubah teks menjadi suara. Ini mengekstrak teks untuk diubah, bahasa, dan suara dari body JSON yang dikirim ke permintaan, membangun beberapa SSML untuk meminta suara, lalu memanggil REST API yang relevan dengan autentikasi menggunakan token akses. Panggilan REST API ini mengembalikan audio yang dikodekan sebagai file WAV mono 16-bit, 48KHz, yang didefinisikan oleh nilai `playback_format`, yang dikirim ke panggilan REST API.

    Audio ini kemudian di-resample oleh `librosa` dari sample rate 48KHz ke sample rate 44.1KHz, lalu audio ini disimpan ke buffer biner yang kemudian dikembalikan.

1. Jalankan aplikasi fungsi Anda secara lokal, atau deploy ke cloud. Anda kemudian dapat memanggilnya menggunakan alat seperti curl dengan cara yang sama seperti Anda menguji pemicu HTTP `text-to-timer`. Pastikan untuk meneruskan bahasa, suara, dan teks sebagai body JSON:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    Ganti `<language>` dengan bahasa Anda, seperti `en-GB`, atau `zh-CN`. Ganti `<voice>` dengan suara yang ingin Anda gunakan. Ganti `<text>` dengan teks yang ingin Anda ubah menjadi suara. Anda dapat menyimpan output ke file dan memutarnya dengan pemutar audio apa pun yang dapat memutar file WAV.

    Misalnya, untuk mengubah "Hello" menjadi suara menggunakan bahasa Inggris AS dengan suara Jenny Neural, dengan aplikasi fungsi berjalan secara lokal, Anda dapat menggunakan perintah curl berikut:

    ```sh
    curl -X GET 'http://localhost:7071/api/text-to-speech' \
         -H 'Content-Type: application/json' \
         -o hello.wav \
         -d '{
           "language":"en-US",
           "voice": "en-US-JennyNeural",
           "text": "Hello"
         }'
    ```

    Ini akan menyimpan audio ke `hello.wav` di direktori saat ini.

> 💁 Anda dapat menemukan kode ini di folder [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Tugas - Mengambil Suara dari Wio Terminal Anda

1. Buka proyek `smart-timer` Anda di VS Code jika belum terbuka.

1. Buka file header `config.h` dan tambahkan URL untuk aplikasi fungsi Anda:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    Ganti `<URL>` dengan URL untuk pemicu HTTP `text-to-speech` pada aplikasi fungsi Anda. Ini akan sama dengan nilai untuk `TEXT_TO_TIMER_FUNCTION_URL`, kecuali dengan nama fungsi `text-to-speech` alih-alih `text-to-timer`.

1. Buka file header `text_to_speech.h`, dan tambahkan metode berikut ke bagian `public` dari kelas `TextToSpeech`:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. Ke metode `convertTextToSpeech`, tambahkan kode berikut untuk membuat JSON yang akan dikirim ke aplikasi fungsi:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Ini menulis bahasa, suara, dan teks ke dokumen JSON, lalu menyerialkannya ke string.

1. Di bawah ini, tambahkan kode berikut untuk memanggil aplikasi fungsi:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Ini membuat `HTTPClient`, lalu membuat permintaan POST menggunakan dokumen JSON ke pemicu HTTP teks ke suara.

1. Jika panggilan berhasil, data biner mentah yang dikembalikan dari panggilan aplikasi fungsi dapat dialirkan ke file di kartu SD. Tambahkan kode berikut untuk melakukannya:

    ```cpp
    if (httpResponseCode == 200)
    {            
        File wav_file = SD.open("SPEECH.WAV", FILE_WRITE);
        httpClient.writeToStream(&wav_file);
        wav_file.close();
    }
    else
    {
        Serial.print("Failed to get speech - error ");
        Serial.println(httpResponseCode);
    }
    ```

    Kode ini memeriksa respons, dan jika 200 (berhasil), data biner dialirkan ke file di root kartu SD yang disebut `SPEECH.WAV`.

1. Di akhir metode ini, tutup koneksi HTTP:

    ```cpp
    httpClient.end();
    ```

1. Teks yang akan diucapkan sekarang dapat diubah menjadi audio. Di file `main.cpp`, tambahkan baris berikut ke akhir fungsi `say` untuk mengubah teks yang akan diucapkan menjadi audio:
### Tugas - Memutar audio dari Wio Terminal

**Segera hadir**

## Mendeploy aplikasi fungsi Anda ke cloud

Alasan menjalankan aplikasi fungsi secara lokal adalah karena paket Pip `librosa` di Linux memiliki dependensi pada sebuah pustaka yang tidak diinstal secara default, dan perlu diinstal sebelum aplikasi fungsi dapat berjalan. Aplikasi fungsi bersifat serverless - tidak ada server yang dapat Anda kelola sendiri, sehingga tidak ada cara untuk menginstal pustaka ini sebelumnya.

Cara untuk mengatasi ini adalah dengan mendeploy aplikasi fungsi Anda menggunakan kontainer Docker. Kontainer ini akan dideploy oleh cloud setiap kali perlu memulai instance baru dari aplikasi fungsi Anda (misalnya ketika permintaan melebihi sumber daya yang tersedia, atau jika aplikasi fungsi tidak digunakan untuk beberapa waktu dan ditutup).

Anda dapat menemukan instruksi untuk membuat aplikasi fungsi dan mendeploy melalui Docker di [dokumentasi membuat fungsi di Linux menggunakan kontainer kustom di Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python).

Setelah aplikasi ini dideploy, Anda dapat memporting kode Wio Terminal Anda untuk mengakses fungsi ini:

1. Tambahkan sertifikat Azure Functions ke `config.h`:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Ubah semua penyertaan `<WiFiClient.h>` menjadi `<WiFiClientSecure.h>`.

1. Ubah semua field `WiFiClient` menjadi `WiFiClientSecure`.

1. Dalam setiap kelas yang memiliki field `WiFiClientSecure`, tambahkan konstruktor dan atur sertifikat di konstruktor tersebut:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diketahui bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.