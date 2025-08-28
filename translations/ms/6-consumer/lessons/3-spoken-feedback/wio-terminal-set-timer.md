<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-27T23:20:36+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "ms"
}
-->
# Tetapkan Pemasa - Wio Terminal

Dalam bahagian pelajaran ini, anda akan memanggil kod tanpa pelayan anda untuk memahami ucapan, dan menetapkan pemasa pada Wio Terminal berdasarkan hasilnya.

## Tetapkan Pemasa

Teks yang kembali daripada panggilan ucapan ke teks perlu dihantar ke kod tanpa pelayan anda untuk diproses oleh LUIS, mendapatkan kembali bilangan saat untuk pemasa. Bilangan saat ini boleh digunakan untuk menetapkan pemasa.

Mikrokontroler tidak secara asli menyokong pelbagai benang dalam Arduino, jadi tiada kelas pemasa standard seperti yang mungkin anda temui semasa menulis kod dalam Python atau bahasa tahap tinggi lain. Sebaliknya, anda boleh menggunakan perpustakaan pemasa yang berfungsi dengan mengukur masa yang berlalu dalam fungsi `loop`, dan memanggil fungsi apabila masa tamat.

### Tugas - hantar teks ke fungsi tanpa pelayan

1. Buka projek `smart-timer` dalam VS Code jika ia belum dibuka.

1. Buka fail header `config.h` dan tambahkan URL untuk aplikasi fungsi anda:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    Gantikan `<URL>` dengan URL untuk aplikasi fungsi anda yang diperoleh dalam langkah terakhir pelajaran sebelumnya, menunjuk kepada alamat IP mesin tempatan anda yang menjalankan aplikasi fungsi.

1. Buat fail baru dalam folder `src` bernama `language_understanding.h`. Fail ini akan digunakan untuk mentakrifkan kelas bagi menghantar ucapan yang dikenali ke aplikasi fungsi anda untuk ditukar kepada saat menggunakan LUIS.

1. Tambahkan perkara berikut di bahagian atas fail ini:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    Ini termasuk beberapa fail header yang diperlukan.

1. Takrifkan kelas bernama `LanguageUnderstanding`, dan isytiharkan satu instans kelas ini:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. Untuk memanggil aplikasi fungsi anda, anda perlu mengisytiharkan klien WiFi. Tambahkan perkara berikut ke bahagian `private` kelas:

    ```cpp
    WiFiClient _client;
    ```

1. Dalam bahagian `public`, isytiharkan kaedah bernama `GetTimerDuration` untuk memanggil aplikasi fungsi:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. Dalam kaedah `GetTimerDuration`, tambahkan kod berikut untuk membina JSON yang akan dihantar ke aplikasi fungsi:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Ini menukar teks yang dihantar ke kaedah `GetTimerDuration` menjadi JSON berikut:

    ```json
    {
        "text" : "<text>"
    }
    ```

    di mana `<text>` adalah teks yang dihantar ke fungsi.

1. Di bawah ini, tambahkan kod berikut untuk membuat panggilan ke aplikasi fungsi:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Ini membuat permintaan POST ke aplikasi fungsi, menghantar badan JSON dan mendapatkan kod respons.

1. Tambahkan kod berikut di bawah ini:

    ```cpp
    int seconds = 0;
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonObject obj = doc.as<JsonObject>();
        seconds = obj["seconds"].as<int>();
    }
    else
    {
        Serial.print("Failed to understand text - error ");
        Serial.println(httpResponseCode);
    }
    ```

    Kod ini memeriksa kod respons. Jika ia adalah 200 (berjaya), maka bilangan saat untuk pemasa diambil daripada badan respons. Jika tidak, ralat dihantar ke monitor serial dan bilangan saat ditetapkan kepada 0.

1. Tambahkan kod berikut di akhir kaedah ini untuk menutup sambungan HTTP dan mengembalikan bilangan saat:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. Dalam fail `main.cpp`, sertakan header baru ini:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Di akhir fungsi `processAudio`, panggil kaedah `GetTimerDuration` untuk mendapatkan tempoh pemasa:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    Ini menukar teks daripada panggilan ke kelas `SpeechToText` menjadi bilangan saat untuk pemasa.

### Tugas - tetapkan pemasa

Bilangan saat boleh digunakan untuk menetapkan pemasa.

1. Tambahkan pergantungan perpustakaan berikut ke fail `platformio.ini` untuk menambahkan perpustakaan bagi menetapkan pemasa:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. Tambahkan arahan sertakan untuk perpustakaan ini ke fail `main.cpp`:

    ```cpp
    #include <arduino-timer.h>
    ```

1. Di atas fungsi `processAudio`, tambahkan kod berikut:

    ```cpp
    auto timer = timer_create_default();
    ```

    Kod ini mengisytiharkan pemasa bernama `timer`.

1. Di bawah ini, tambahkan kod berikut:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    Fungsi `say` ini akhirnya akan menukar teks kepada ucapan, tetapi buat masa ini ia hanya akan menulis teks yang dihantar ke monitor serial.

1. Di bawah fungsi `say`, tambahkan kod berikut:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    Ini adalah fungsi panggilan balik yang akan dipanggil apabila pemasa tamat. Ia dihantar mesej untuk diucapkan apabila pemasa tamat. Pemasa boleh berulang, dan ini boleh dikawal oleh nilai pulangan fungsi panggilan balik ini - ini mengembalikan `false`, untuk memberitahu pemasa supaya tidak berjalan lagi.

1. Tambahkan kod berikut di akhir fungsi `processAudio`:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    Kod ini memeriksa jumlah bilangan saat, dan jika ia adalah 0, kembali daripada panggilan fungsi supaya tiada pemasa ditetapkan. Ia kemudian menukar jumlah bilangan saat menjadi minit dan saat.

1. Di bawah kod ini, tambahkan perkara berikut untuk mencipta mesej untuk diucapkan apabila pemasa dimulakan:

    ```cpp
    String begin_message;
    if (minutes > 0)
    {
        begin_message += minutes;
        begin_message += " minute ";
    }
    if (seconds > 0)
    {
        begin_message += seconds;
        begin_message += " second ";
    }

    begin_message += "timer started.";
    ```

1. Di bawah ini, tambahkan kod serupa untuk mencipta mesej untuk diucapkan apabila pemasa tamat:

    ```cpp
    String end_message("Times up on your ");
    if (minutes > 0)
    {
        end_message += minutes;
        end_message += " minute ";
    }
    if (seconds > 0)
    {
        end_message += seconds;
        end_message += " second ";
    }

    end_message += "timer.";
    ```

1. Selepas ini, ucapkan mesej pemasa dimulakan:

    ```cpp
    say(begin_message);
    ```

1. Di akhir fungsi ini, mulakan pemasa:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    Ini mencetuskan pemasa. Pemasa ditetapkan menggunakan milisaat, jadi jumlah bilangan saat didarabkan dengan 1,000 untuk ditukar kepada milisaat. Fungsi `timerExpired` dihantar sebagai panggilan balik, dan `end_message` dihantar sebagai argumen untuk dihantar ke panggilan balik. Panggilan balik ini hanya mengambil argumen `void *`, jadi string ditukar dengan sewajarnya.

1. Akhir sekali, pemasa perlu *berdetik*, dan ini dilakukan dalam fungsi `loop`. Tambahkan kod berikut di akhir fungsi `loop`:

    ```cpp
    timer.tick();
    ```

1. Bina kod ini, muat naik ke Wio Terminal anda dan uji melalui monitor serial. Sebaik sahaja anda melihat `Ready` dalam monitor serial, tekan butang C (yang di sebelah kiri, paling dekat dengan suis kuasa), dan bercakap. 4 saat audio akan ditangkap, ditukar kepada teks, kemudian dihantar ke aplikasi fungsi anda, dan pemasa akan ditetapkan. Pastikan aplikasi fungsi anda berjalan secara tempatan.

    Anda akan melihat apabila pemasa dimulakan, dan apabila ia tamat.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Set a 2 minute and 27 second timer.","Offset":4700000,"Duration":35300000}
    Set a 2 minute and 27 second timer.
    {"seconds": 147}
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 Anda boleh menemui kod ini dalam folder [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal).

😀 Program pemasa anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.