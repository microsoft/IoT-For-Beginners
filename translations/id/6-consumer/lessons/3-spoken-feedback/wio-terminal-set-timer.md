<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-27T23:20:16+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "id"
}
-->
# Atur Timer - Wio Terminal

Dalam bagian pelajaran ini, Anda akan memanggil kode serverless Anda untuk memahami ucapan, dan mengatur timer pada Wio Terminal berdasarkan hasilnya.

## Atur Timer

Teks yang dihasilkan dari panggilan speech-to-text perlu dikirim ke kode serverless Anda untuk diproses oleh LUIS, yang akan mengembalikan jumlah detik untuk timer. Jumlah detik ini dapat digunakan untuk mengatur timer.

Mikrokontroler secara bawaan tidak mendukung multiple threads di Arduino, sehingga tidak ada kelas timer standar seperti yang mungkin Anda temukan saat coding di Python atau bahasa tingkat tinggi lainnya. Sebagai gantinya, Anda dapat menggunakan pustaka timer yang bekerja dengan mengukur waktu yang telah berlalu di fungsi `loop`, dan memanggil fungsi ketika waktu habis.

### Tugas - Kirim teks ke fungsi serverless

1. Buka proyek `smart-timer` di VS Code jika belum terbuka.

1. Buka file header `config.h` dan tambahkan URL untuk aplikasi fungsi Anda:

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    Ganti `<URL>` dengan URL untuk aplikasi fungsi Anda yang diperoleh pada langkah terakhir dari pelajaran sebelumnya, mengarah ke alamat IP mesin lokal Anda yang menjalankan aplikasi fungsi.

1. Buat file baru di folder `src` bernama `language_understanding.h`. File ini akan digunakan untuk mendefinisikan sebuah kelas untuk mengirim ucapan yang dikenali ke aplikasi fungsi Anda agar dikonversi menjadi detik menggunakan LUIS.

1. Tambahkan hal berikut ke bagian atas file ini:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    Ini mencakup beberapa file header yang diperlukan.

1. Definisikan sebuah kelas bernama `LanguageUnderstanding`, dan deklarasikan sebuah instance dari kelas ini:

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. Untuk memanggil aplikasi fungsi Anda, Anda perlu mendeklarasikan klien WiFi. Tambahkan hal berikut ke bagian `private` dari kelas:

    ```cpp
    WiFiClient _client;
    ```

1. Di bagian `public`, deklarasikan sebuah metode bernama `GetTimerDuration` untuk memanggil aplikasi fungsi:

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. Dalam metode `GetTimerDuration`, tambahkan kode berikut untuk membangun JSON yang akan dikirim ke aplikasi fungsi:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Ini mengonversi teks yang diteruskan ke metode `GetTimerDuration` menjadi JSON berikut:

    ```json
    {
        "text" : "<text>"
    }
    ```

    di mana `<text>` adalah teks yang diteruskan ke fungsi.

1. Di bawah ini, tambahkan kode berikut untuk membuat panggilan ke aplikasi fungsi:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Ini membuat permintaan POST ke aplikasi fungsi, mengirimkan body JSON dan mendapatkan kode respons.

1. Tambahkan kode berikut di bawah ini:

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

    Kode ini memeriksa kode respons. Jika 200 (berhasil), maka jumlah detik untuk timer diambil dari body respons. Jika tidak, sebuah error dikirim ke serial monitor dan jumlah detik diatur ke 0.

1. Tambahkan kode berikut ke akhir metode ini untuk menutup koneksi HTTP dan mengembalikan jumlah detik:

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. Dalam file `main.cpp`, sertakan header baru ini:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Di akhir fungsi `processAudio`, panggil metode `GetTimerDuration` untuk mendapatkan durasi timer:

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    Ini mengonversi teks dari panggilan ke kelas `SpeechToText` menjadi jumlah detik untuk timer.

### Tugas - Atur Timer

Jumlah detik dapat digunakan untuk mengatur timer.

1. Tambahkan dependensi pustaka berikut ke file `platformio.ini` untuk menambahkan pustaka untuk mengatur timer:

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. Tambahkan direktif include untuk pustaka ini ke file `main.cpp`:

    ```cpp
    #include <arduino-timer.h>
    ```

1. Di atas fungsi `processAudio`, tambahkan kode berikut:

    ```cpp
    auto timer = timer_create_default();
    ```

    Kode ini mendeklarasikan sebuah timer bernama `timer`.

1. Di bawah ini, tambahkan kode berikut:

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    Fungsi `say` ini nantinya akan mengonversi teks menjadi ucapan, tetapi untuk saat ini hanya akan menulis teks yang diteruskan ke serial monitor.

1. Di bawah fungsi `say`, tambahkan kode berikut:

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    Ini adalah fungsi callback yang akan dipanggil ketika timer habis. Fungsi ini menerima pesan untuk diucapkan ketika timer habis. Timer dapat diulang, dan ini dapat dikontrol oleh nilai pengembalian dari callback ini - ini mengembalikan `false`, untuk memberi tahu timer agar tidak berjalan lagi.

1. Tambahkan kode berikut ke akhir fungsi `processAudio`:

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    Kode ini memeriksa jumlah total detik, dan jika 0, keluar dari panggilan fungsi sehingga tidak ada timer yang diatur. Kemudian mengonversi jumlah total detik menjadi menit dan detik.

1. Di bawah kode ini, tambahkan hal berikut untuk membuat pesan yang akan diucapkan ketika timer dimulai:

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

1. Di bawah ini, tambahkan kode serupa untuk membuat pesan yang akan diucapkan ketika timer habis:

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

1. Setelah ini, ucapkan pesan timer dimulai:

    ```cpp
    say(begin_message);
    ```

1. Di akhir fungsi ini, mulai timer:

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    Ini memicu timer. Timer diatur menggunakan milidetik, sehingga jumlah total detik dikalikan dengan 1.000 untuk dikonversi menjadi milidetik. Fungsi `timerExpired` diteruskan sebagai callback, dan `end_message` diteruskan sebagai argumen untuk diteruskan ke callback. Callback ini hanya menerima argumen `void *`, sehingga string dikonversi dengan tepat.

1. Terakhir, timer perlu *berjalan*, dan ini dilakukan di fungsi `loop`. Tambahkan kode berikut di akhir fungsi `loop`:

    ```cpp
    timer.tick();
    ```

1. Bangun kode ini, unggah ke Wio Terminal Anda, dan uji melalui serial monitor. Setelah Anda melihat `Ready` di serial monitor, tekan tombol C (yang ada di sisi kiri, paling dekat dengan sakelar daya), dan berbicaralah. 4 detik audio akan direkam, dikonversi menjadi teks, lalu dikirim ke aplikasi fungsi Anda, dan timer akan diatur. Pastikan aplikasi fungsi Anda berjalan secara lokal.

    Anda akan melihat kapan timer dimulai, dan kapan berakhir.

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

> 💁 Anda dapat menemukan kode ini di folder [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal).

😀 Program timer Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.