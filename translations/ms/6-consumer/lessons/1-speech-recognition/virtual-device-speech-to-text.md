<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-27T23:23:51+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "ms"
}
-->
# Ucapan ke Teks - Peranti IoT Maya

Dalam bahagian pelajaran ini, anda akan menulis kod untuk menukar ucapan yang ditangkap dari mikrofon anda kepada teks menggunakan perkhidmatan ucapan.

## Tukar ucapan kepada teks

Di Windows, Linux, dan macOS, SDK Python perkhidmatan ucapan boleh digunakan untuk mendengar mikrofon anda dan menukar sebarang ucapan yang dikesan kepada teks. Ia akan mendengar secara berterusan, mengesan tahap audio dan menghantar ucapan untuk ditukar kepada teks apabila tahap audio menurun, seperti di akhir blok ucapan.

### Tugasan - tukar ucapan kepada teks

1. Cipta aplikasi Python baharu di komputer anda dalam folder bernama `smart-timer` dengan satu fail bernama `app.py` dan persekitaran maya Python.

1. Pasang pakej Pip untuk perkhidmatan ucapan. Pastikan anda memasangnya dari terminal dengan persekitaran maya diaktifkan.

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ Jika anda mendapat ralat berikut:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > Anda perlu mengemas kini Pip. Lakukan ini dengan arahan berikut, kemudian cuba pasang pakej sekali lagi:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Tambahkan import berikut ke fail `app.py`:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    Ini mengimport beberapa kelas yang digunakan untuk mengenali ucapan.

1. Tambahkan kod berikut untuk mengisytiharkan beberapa konfigurasi:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    Gantikan `<key>` dengan kunci API untuk perkhidmatan ucapan anda. Gantikan `<location>` dengan lokasi yang anda gunakan semasa mencipta sumber perkhidmatan ucapan.

    Gantikan `<language>` dengan nama lokal untuk bahasa yang akan anda gunakan, contohnya `en-GB` untuk Bahasa Inggeris, atau `zn-HK` untuk Bahasa Kantonis. Anda boleh mencari senarai bahasa yang disokong dan nama lokal mereka dalam [dokumentasi sokongan bahasa dan suara di Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Konfigurasi ini kemudian digunakan untuk mencipta objek `SpeechConfig` yang akan digunakan untuk mengkonfigurasi perkhidmatan ucapan.

1. Tambahkan kod berikut untuk mencipta pengenal ucapan:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. Pengenal ucapan berjalan di latar belakang, mendengar audio dan menukar sebarang ucapan di dalamnya kepada teks. Anda boleh mendapatkan teks menggunakan fungsi panggil balik - fungsi yang anda tentukan dan serahkan kepada pengenal. Setiap kali ucapan dikesan, fungsi panggil balik akan dipanggil. Tambahkan kod berikut untuk menentukan fungsi panggil balik, dan serahkan fungsi ini kepada pengenal, serta menentukan fungsi untuk memproses teks, menulisnya ke konsol:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. Pengenal hanya mula mendengar apabila anda memulakannya secara eksplisit. Tambahkan kod berikut untuk memulakan pengenalan. Ini berjalan di latar belakang, jadi aplikasi anda juga memerlukan gelung tak terhingga yang tidur untuk memastikan aplikasi terus berjalan.

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. Jalankan aplikasi ini. Bercakap ke mikrofon anda dan audio yang ditukar kepada teks akan dipaparkan di konsol.

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    Cuba pelbagai jenis ayat, bersama dengan ayat di mana perkataan berbunyi sama tetapi mempunyai makna yang berbeza. Contohnya, jika anda bercakap dalam Bahasa Inggeris, sebut 'I want to buy two bananas and an apple too', dan perhatikan bagaimana ia menggunakan to, two dan too yang betul berdasarkan konteks perkataan, bukan hanya bunyinya.

> 💁 Anda boleh mencari kod ini dalam folder [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device).

😀 Program ucapan ke teks anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.