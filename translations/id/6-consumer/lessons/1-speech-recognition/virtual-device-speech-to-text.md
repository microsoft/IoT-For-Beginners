<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-27T23:27:57+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "id"
}
-->
# Ucapan ke Teks - Perangkat IoT Virtual

Dalam bagian pelajaran ini, Anda akan menulis kode untuk mengubah ucapan yang ditangkap dari mikrofon Anda menjadi teks menggunakan layanan ucapan.

## Mengubah ucapan menjadi teks

Di Windows, Linux, dan macOS, SDK Python layanan ucapan dapat digunakan untuk mendengarkan mikrofon Anda dan mengubah ucapan yang terdeteksi menjadi teks. SDK ini akan mendengarkan secara terus-menerus, mendeteksi tingkat audio, dan mengirimkan ucapan untuk diubah menjadi teks ketika tingkat audio menurun, seperti di akhir blok ucapan.

### Tugas - mengubah ucapan menjadi teks

1. Buat aplikasi Python baru di komputer Anda dalam folder bernama `smart-timer` dengan satu file bernama `app.py` dan lingkungan virtual Python.

1. Instal paket Pip untuk layanan ucapan. Pastikan Anda menginstalnya dari terminal dengan lingkungan virtual yang diaktifkan.

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ Jika Anda mendapatkan error berikut:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > Anda perlu memperbarui Pip. Lakukan ini dengan perintah berikut, lalu coba instal paket lagi:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Tambahkan impor berikut ke file `app.py`:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    Ini mengimpor beberapa kelas yang digunakan untuk mengenali ucapan.

1. Tambahkan kode berikut untuk mendeklarasikan beberapa konfigurasi:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    Ganti `<key>` dengan kunci API untuk layanan ucapan Anda. Ganti `<location>` dengan lokasi yang Anda gunakan saat membuat sumber daya layanan ucapan.

    Ganti `<language>` dengan nama lokal untuk bahasa yang akan Anda gunakan, misalnya `en-GB` untuk Bahasa Inggris, atau `zn-HK` untuk Bahasa Kanton. Anda dapat menemukan daftar bahasa yang didukung dan nama lokalnya di [dokumentasi dukungan bahasa dan suara di Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Konfigurasi ini kemudian digunakan untuk membuat objek `SpeechConfig` yang akan digunakan untuk mengonfigurasi layanan ucapan.

1. Tambahkan kode berikut untuk membuat pengenal ucapan:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. Pengenal ucapan berjalan di thread latar belakang, mendengarkan audio dan mengubah ucapan di dalamnya menjadi teks. Anda dapat mendapatkan teks menggunakan fungsi callback - fungsi yang Anda definisikan dan berikan ke pengenal. Setiap kali ucapan terdeteksi, callback akan dipanggil. Tambahkan kode berikut untuk mendefinisikan callback, dan berikan callback ini ke pengenal, serta mendefinisikan fungsi untuk memproses teks, menuliskannya ke konsol:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. Pengenal hanya mulai mendengarkan ketika Anda secara eksplisit memulainya. Tambahkan kode berikut untuk memulai pengenalan. Ini berjalan di latar belakang, jadi aplikasi Anda juga memerlukan loop tak terbatas yang tidur untuk menjaga aplikasi tetap berjalan.

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. Jalankan aplikasi ini. Berbicara ke mikrofon Anda dan audio yang diubah menjadi teks akan ditampilkan di konsol.

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    Cobalah berbagai jenis kalimat, bersama dengan kalimat di mana kata-kata terdengar sama tetapi memiliki arti yang berbeda. Misalnya, jika Anda berbicara dalam Bahasa Inggris, ucapkan 'I want to buy two bananas and an apple too', dan perhatikan bagaimana aplikasi akan menggunakan kata yang benar seperti to, two, dan too berdasarkan konteks kata, bukan hanya berdasarkan suaranya.

> 💁 Anda dapat menemukan kode ini di folder [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device).

😀 Program ucapan ke teks Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.