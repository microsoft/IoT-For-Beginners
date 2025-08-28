<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-27T23:17:28+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "ms"
}
-->
# Teks ke Ucapan - Wio Terminal

Dalam bahagian pelajaran ini, anda akan menukar teks kepada ucapan untuk memberikan maklum balas secara lisan.

## Teks ke Ucapan

SDK perkhidmatan ucapan yang anda gunakan dalam pelajaran sebelumnya untuk menukar ucapan kepada teks juga boleh digunakan untuk menukar teks kembali kepada ucapan.

## Dapatkan Senarai Suara

Apabila meminta ucapan, anda perlu menyediakan suara yang akan digunakan kerana ucapan boleh dihasilkan menggunakan pelbagai suara yang berbeza. Setiap bahasa menyokong pelbagai suara, dan anda boleh mendapatkan senarai suara yang disokong untuk setiap bahasa daripada SDK perkhidmatan ucapan. Keterbatasan mikrokontroler memainkan peranan di sini - panggilan untuk mendapatkan senarai suara yang disokong oleh perkhidmatan teks ke ucapan adalah dokumen JSON berukuran lebih daripada 77KB, terlalu besar untuk diproses oleh Wio Terminal. Pada masa penulisan, senarai penuh mengandungi 215 suara, setiap satu ditakrifkan oleh dokumen JSON seperti berikut:

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

JSON ini adalah untuk suara **Aria**, yang mempunyai pelbagai gaya suara. Apa yang diperlukan apabila menukar teks kepada ucapan hanyalah nama pendek, `en-US-AriaNeural`.

Daripada memuat turun dan menyahkod keseluruhan senarai ini pada mikrokontroler anda, anda perlu menulis beberapa kod tanpa pelayan untuk mendapatkan senarai suara bagi bahasa yang anda gunakan, dan memanggilnya dari Wio Terminal anda. Kod anda kemudian boleh memilih suara yang sesuai daripada senarai, seperti suara pertama yang ditemui.

### Tugasan - buat fungsi tanpa pelayan untuk mendapatkan senarai suara

1. Buka projek `smart-timer-trigger` anda dalam VS Code, dan buka terminal memastikan persekitaran maya diaktifkan. Jika tidak, matikan dan buat semula terminal.

1. Buka fail `local.settings.json` dan tambahkan tetapan untuk kunci API ucapan dan lokasi:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    Gantikan `<key>` dengan kunci API untuk sumber perkhidmatan ucapan anda. Gantikan `<location>` dengan lokasi yang anda gunakan semasa anda membuat sumber perkhidmatan ucapan.

1. Tambahkan pencetus HTTP baharu kepada aplikasi ini yang dipanggil `get-voices` menggunakan arahan berikut dari dalam terminal VS Code di folder root projek aplikasi fungsi:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    Ini akan membuat pencetus HTTP yang dipanggil `get-voices`.

1. Gantikan kandungan fail `__init__.py` dalam folder `get-voices` dengan yang berikut:

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

    Kod ini membuat permintaan HTTP ke titik akhir untuk mendapatkan suara. Senarai suara ini adalah blok besar JSON dengan suara untuk semua bahasa, jadi suara untuk bahasa yang dihantar dalam badan permintaan ditapis keluar, kemudian nama pendek diekstrak dan dikembalikan sebagai senarai JSON. Nama pendek adalah nilai yang diperlukan untuk menukar teks kepada ucapan, jadi hanya nilai ini yang dikembalikan.

    > 💁 Anda boleh mengubah penapis mengikut keperluan untuk memilih hanya suara yang anda inginkan.

    Ini mengurangkan saiz data daripada 77KB (pada masa penulisan), kepada dokumen JSON yang jauh lebih kecil. Sebagai contoh, untuk suara AS ini adalah 408 bait.

1. Jalankan aplikasi fungsi anda secara tempatan. Anda kemudian boleh memanggilnya menggunakan alat seperti curl dengan cara yang sama seperti anda menguji pencetus HTTP `text-to-timer` anda. Pastikan untuk menghantar bahasa anda sebagai badan JSON:

    ```json
    {
        "language":"<language>"
    }
    ```

    Gantikan `<language>` dengan bahasa anda, seperti `en-GB`, atau `zh-CN`.

> 💁 Anda boleh menemui kod ini dalam folder [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Tugasan - dapatkan suara dari Wio Terminal anda

1. Buka projek `smart-timer` anda dalam VS Code jika belum dibuka.

1. Buka fail header `config.h` dan tambahkan URL untuk aplikasi fungsi anda:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    Gantikan `<URL>` dengan URL untuk pencetus HTTP `get-voices` pada aplikasi fungsi anda. Ini akan sama dengan nilai untuk `TEXT_TO_TIMER_FUNCTION_URL`, kecuali dengan nama fungsi `get-voices` dan bukannya `text-to-timer`.

1. Buat fail baharu dalam folder `src` yang dipanggil `text_to_speech.h`. Ini akan digunakan untuk mentakrifkan kelas untuk menukar dari teks kepada ucapan.

1. Tambahkan arahan include berikut di bahagian atas fail `text_to_speech.h` yang baharu:

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

1. Tambahkan kod berikut di bawah ini untuk mengisytiharkan kelas `TextToSpeech`, bersama dengan satu instance yang boleh digunakan dalam aplikasi yang lain:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. Untuk memanggil aplikasi fungsi anda, anda perlu mengisytiharkan klien WiFi. Tambahkan yang berikut ke bahagian `private` kelas:

    ```cpp
    WiFiClient _client;
    ```

1. Dalam bahagian `private`, tambahkan medan untuk suara yang dipilih:

    ```cpp
    String _voice;
    ```

1. Ke bahagian `public`, tambahkan fungsi `init` yang akan mendapatkan suara pertama:

    ```cpp
    void init()
    {
    }
    ```

1. Untuk mendapatkan suara, dokumen JSON perlu dihantar ke aplikasi fungsi dengan bahasa. Tambahkan kod berikut ke fungsi `init` untuk membuat dokumen JSON ini:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. Seterusnya buat `HTTPClient`, kemudian gunakan untuk memanggil aplikasi fungsi untuk mendapatkan suara, menghantar dokumen JSON:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Di bawah ini tambahkan kod untuk memeriksa kod respons, dan jika ia adalah 200 (berjaya), maka ekstrak senarai suara, mendapatkan suara pertama dari senarai:

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

1. Selepas ini, tamatkan sambungan klien HTTP:

    ```cpp
    httpClient.end();
    ```

1. Buka fail `main.cpp`, dan tambahkan arahan include berikut di bahagian atas untuk memasukkan fail header yang baharu ini:

    ```cpp
    #include "text_to_speech.h"
    ```

1. Dalam fungsi `setup`, di bawah panggilan kepada `speechToText.init();`, tambahkan yang berikut untuk memulakan kelas `TextToSpeech`:

    ```cpp
    textToSpeech.init();
    ```

1. Bina kod ini, muat naik ke Wio Terminal anda dan uji melalui monitor serial. Pastikan aplikasi fungsi anda sedang berjalan.

    Anda akan melihat senarai suara yang tersedia dikembalikan dari aplikasi fungsi, bersama dengan suara yang dipilih.

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

## Tukar Teks kepada Ucapan

Setelah anda mempunyai suara untuk digunakan, ia boleh digunakan untuk menukar teks kepada ucapan. Keterbatasan memori yang sama dengan suara juga berlaku semasa menukar ucapan kepada teks, jadi anda perlu menulis ucapan ke kad SD untuk dimainkan melalui ReSpeaker.

> 💁 Dalam pelajaran sebelumnya dalam projek ini, anda menggunakan memori flash untuk menyimpan ucapan yang ditangkap dari mikrofon. Pelajaran ini menggunakan kad SD kerana lebih mudah untuk memainkan audio daripadanya menggunakan perpustakaan audio Seeed.

Terdapat juga satu lagi keterbatasan yang perlu dipertimbangkan, data audio yang tersedia dari perkhidmatan ucapan, dan format yang disokong oleh Wio Terminal. Tidak seperti komputer penuh, perpustakaan audio untuk mikrokontroler boleh sangat terhad dalam format audio yang mereka sokong. Sebagai contoh, perpustakaan Seeed Arduino Audio yang boleh memainkan bunyi melalui ReSpeaker hanya menyokong audio pada kadar sampel 44.1KHz. Perkhidmatan ucapan Azure boleh menyediakan audio dalam beberapa format, tetapi tiada satu pun menggunakan kadar sampel ini, mereka hanya menyediakan 8KHz, 16KHz, 24KHz dan 48KHz. Ini bermakna audio perlu disampel semula kepada 44.1KHz, sesuatu yang memerlukan lebih banyak sumber daripada yang dimiliki oleh Wio Terminal, terutamanya memori.

Apabila perlu memanipulasi data seperti ini, sering kali lebih baik menggunakan kod tanpa pelayan, terutamanya jika data diperoleh melalui panggilan web. Wio Terminal boleh memanggil fungsi tanpa pelayan, menghantar teks untuk ditukar, dan fungsi tanpa pelayan boleh memanggil perkhidmatan ucapan untuk menukar teks kepada ucapan, serta menyampel semula audio kepada kadar sampel yang diperlukan. Ia kemudian boleh mengembalikan audio dalam bentuk yang diperlukan oleh Wio Terminal untuk disimpan di kad SD dan dimainkan melalui ReSpeaker.

### Tugasan - buat fungsi tanpa pelayan untuk menukar teks kepada ucapan

1. Buka projek `smart-timer-trigger` anda dalam VS Code, dan buka terminal memastikan persekitaran maya diaktifkan. Jika tidak, matikan dan buat semula terminal.

1. Tambahkan pencetus HTTP baharu kepada aplikasi ini yang dipanggil `text-to-speech` menggunakan arahan berikut dari dalam terminal VS Code di folder root projek aplikasi fungsi:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    Ini akan membuat pencetus HTTP yang dipanggil `text-to-speech`.

1. Pakej Pip [librosa](https://librosa.org) mempunyai fungsi untuk menyampel semula audio, jadi tambahkan ini ke fail `requirements.txt`:

    ```sh
    librosa
    ```

    Setelah ini ditambahkan, pasang pakej Pip menggunakan arahan berikut dari terminal VS Code:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ Jika anda menggunakan Linux, termasuk Raspberry Pi OS, anda mungkin perlu memasang `libsndfile` dengan arahan berikut:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. Untuk menukar teks kepada ucapan, anda tidak boleh menggunakan kunci API ucapan secara langsung, sebaliknya anda perlu meminta token akses, menggunakan kunci API untuk mengesahkan permintaan token akses. Buka fail `__init__.py` dari folder `text-to-speech` dan gantikan semua kod di dalamnya dengan yang berikut:

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

    Ini mentakrifkan pemalar untuk lokasi dan kunci ucapan yang akan dibaca dari tetapan. Ia kemudian mentakrifkan fungsi `get_access_token` yang akan mendapatkan token akses untuk perkhidmatan ucapan.

1. Di bawah kod ini, tambahkan yang berikut:

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

    Ini mentakrifkan pencetus HTTP yang menukar teks kepada ucapan. Ia mengekstrak teks untuk ditukar, bahasa dan suara dari badan JSON yang dihantar kepada permintaan, membina beberapa SSML untuk meminta ucapan, kemudian memanggil REST API yang relevan dengan pengesahan menggunakan token akses. Panggilan REST API ini mengembalikan audio yang dikodkan sebagai fail WAV mono 16-bit, 48KHz, yang ditakrifkan oleh nilai `playback_format`, yang dihantar kepada panggilan REST API.

    Audio ini kemudian disampel semula oleh `librosa` dari kadar sampel 48KHz kepada kadar sampel 44.1KHz, kemudian audio ini disimpan ke penyangga binari yang kemudian dikembalikan.

1. Jalankan aplikasi fungsi anda secara tempatan, atau muat naik ke awan. Anda kemudian boleh memanggilnya menggunakan alat seperti curl dengan cara yang sama seperti anda menguji pencetus HTTP `text-to-timer` anda. Pastikan untuk menghantar bahasa, suara dan teks sebagai badan JSON:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    Gantikan `<language>` dengan bahasa anda, seperti `en-GB`, atau `zh-CN`. Gantikan `<voice>` dengan suara yang anda ingin gunakan. Gantikan `<text>` dengan teks yang anda ingin tukar kepada ucapan. Anda boleh menyimpan output ke fail dan memainkannya dengan mana-mana pemain audio yang boleh memainkan fail WAV.

    Sebagai contoh, untuk menukar "Hello" kepada ucapan menggunakan Bahasa Inggeris AS dengan suara Jenny Neural, dengan aplikasi fungsi berjalan secara tempatan, anda boleh menggunakan arahan curl berikut:

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

    Ini akan menyimpan audio ke `hello.wav` dalam direktori semasa.

> 💁 Anda boleh menemui kod ini dalam folder [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Tugasan - dapatkan ucapan dari Wio Terminal anda

1. Buka projek `smart-timer` anda dalam VS Code jika belum dibuka.

1. Buka fail header `config.h` dan tambahkan URL untuk aplikasi fungsi anda:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    Gantikan `<URL>` dengan URL untuk pencetus HTTP `text-to-speech` pada aplikasi fungsi anda. Ini akan sama dengan nilai untuk `TEXT_TO_TIMER_FUNCTION_URL`, kecuali dengan nama fungsi `text-to-speech` dan bukannya `text-to-timer`.

1. Buka fail header `text_to_speech.h`, dan tambahkan kaedah berikut ke bahagian `public` kelas `TextToSpeech`:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. Ke kaedah `convertTextToSpeech`, tambahkan kod berikut untuk membuat JSON untuk dihantar ke aplikasi fungsi:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Ini menulis bahasa, suara dan teks ke dokumen JSON, kemudian menyahkodnya ke string.

1. Di bawah ini, tambahkan kod berikut untuk memanggil aplikasi fungsi:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Ini membuat HTTPClient, kemudian membuat permintaan POST menggunakan dokumen JSON ke pencetus HTTP teks ke ucapan.

1. Jika panggilan berjaya, data binari mentah yang dikembalikan dari panggilan aplikasi fungsi boleh dialirkan ke fail pada kad SD. Tambahkan kod berikut untuk melakukannya:

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

    Kod ini memeriksa respons, dan jika ia adalah 200 (berjaya), data binari dialirkan ke fail di root Kad SD yang dipanggil `SPEECH.WAV`.

1. Pada akhir kaedah ini, tutup sambungan HTTP:

    ```cpp
    httpClient.end();
    ```

1. Teks yang akan diucapkan kini boleh ditukar kepada audio. Dalam fail `main.cpp`, tambahkan baris berikut ke akhir fungsi `say` untuk menukar teks yang akan diucapkan kepada audio:
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### Tugas - mainkan audio dari Wio Terminal anda

**Akan datang**

## Menyebarkan aplikasi fungsi anda ke awan

Sebab menjalankan aplikasi fungsi secara tempatan adalah kerana pakej Pip `librosa` pada Linux mempunyai kebergantungan pada perpustakaan yang tidak dipasang secara lalai, dan perlu dipasang sebelum aplikasi fungsi dapat dijalankan. Aplikasi fungsi adalah tanpa pelayan - tiada pelayan yang boleh anda uruskan sendiri, jadi tiada cara untuk memasang perpustakaan ini terlebih dahulu.

Cara untuk melakukannya adalah dengan menyebarkan aplikasi fungsi anda menggunakan bekas Docker. Bekas ini akan disebarkan oleh awan setiap kali ia perlu memulakan instans baru aplikasi fungsi anda (seperti apabila permintaan melebihi sumber yang tersedia, atau jika aplikasi fungsi tidak digunakan untuk beberapa waktu dan ditutup).

Anda boleh mencari arahan untuk menyediakan aplikasi fungsi dan menyebarkan melalui Docker dalam [dokumentasi buat fungsi pada Linux menggunakan bekas tersuai di Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python).

Setelah ini disebarkan, anda boleh memindahkan kod Wio Terminal anda untuk mengakses fungsi ini:

1. Tambahkan sijil Azure Functions ke `config.h`:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Tukar semua penyertaan `<WiFiClient.h>` kepada `<WiFiClientSecure.h>`.

1. Tukar semua medan `WiFiClient` kepada `WiFiClientSecure`.

1. Dalam setiap kelas yang mempunyai medan `WiFiClientSecure`, tambahkan pembina dan tetapkan sijil dalam pembina tersebut:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.