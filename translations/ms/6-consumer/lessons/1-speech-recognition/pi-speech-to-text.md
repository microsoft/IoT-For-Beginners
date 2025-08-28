<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-27T23:31:56+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "ms"
}
-->
# Ucapan ke Teks - Raspberry Pi

Dalam bahagian pelajaran ini, anda akan menulis kod untuk menukar ucapan dalam audio yang dirakam kepada teks menggunakan perkhidmatan ucapan.

## Hantar audio ke perkhidmatan ucapan

Audio boleh dihantar ke perkhidmatan ucapan menggunakan REST API. Untuk menggunakan perkhidmatan ucapan, pertama anda perlu meminta token akses, kemudian gunakan token tersebut untuk mengakses REST API. Token akses ini akan tamat tempoh selepas 10 minit, jadi kod anda perlu memintanya secara berkala untuk memastikan ia sentiasa terkini.

### Tugasan - dapatkan token akses

1. Buka projek `smart-timer` pada Pi anda.

1. Buang fungsi `play_audio`. Fungsi ini tidak lagi diperlukan kerana anda tidak mahu pemasa pintar mengulangi apa yang anda katakan.

1. Tambahkan import berikut di bahagian atas fail `app.py`:

    ```python
    import requests
    ```

1. Tambahkan kod berikut di atas gelung `while True` untuk mengisytiharkan beberapa tetapan untuk perkhidmatan ucapan:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    Gantikan `<key>` dengan kunci API untuk sumber perkhidmatan ucapan anda. Gantikan `<location>` dengan lokasi yang anda gunakan semasa mencipta sumber perkhidmatan ucapan.

    Gantikan `<language>` dengan nama lokal untuk bahasa yang akan anda gunakan, contohnya `en-GB` untuk Bahasa Inggeris, atau `zn-HK` untuk Bahasa Kantonis. Anda boleh mencari senarai bahasa yang disokong dan nama lokal mereka dalam [dokumentasi sokongan bahasa dan suara di Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

1. Di bawah ini, tambahkan fungsi berikut untuk mendapatkan token akses:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Fungsi ini memanggil endpoint pengeluaran token, menghantar kunci API sebagai header. Panggilan ini mengembalikan token akses yang boleh digunakan untuk memanggil perkhidmatan ucapan.

1. Di bawah ini, isytiharkan fungsi untuk menukar ucapan dalam audio yang dirakam kepada teks menggunakan REST API:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. Di dalam fungsi ini, tetapkan URL REST API dan header:

    ```python
    url = f'https://{location}.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1'

    headers = {
        'Authorization': 'Bearer ' + get_access_token(),
        'Content-Type': f'audio/wav; codecs=audio/pcm; samplerate={rate}',
        'Accept': 'application/json;text/xml'
    }

    params = {
        'language': language
    }
    ```

    Fungsi ini membina URL menggunakan lokasi sumber perkhidmatan ucapan. Ia kemudian mengisi header dengan token akses daripada fungsi `get_access_token`, serta kadar sampel yang digunakan untuk merakam audio. Akhirnya, ia mentakrifkan beberapa parameter untuk dihantar bersama URL yang mengandungi bahasa dalam audio.

1. Di bawah ini, tambahkan kod berikut untuk memanggil REST API dan mendapatkan teks:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    Fungsi ini memanggil URL dan menyahkod nilai JSON yang datang dalam respons. Nilai `RecognitionStatus` dalam respons menunjukkan sama ada panggilan berjaya mengekstrak ucapan kepada teks, dan jika ia adalah `Success`, maka teks akan dikembalikan daripada fungsi, jika tidak, ia akan mengembalikan string kosong.

1. Di atas gelung `while True:`, tentukan fungsi untuk memproses teks yang dikembalikan daripada perkhidmatan ucapan ke teks. Buat masa ini, fungsi ini hanya akan mencetak teks ke konsol.

    ```python
    def process_text(text):
        print(text)
    ```

1. Akhir sekali, gantikan panggilan kepada `play_audio` dalam gelung `while True` dengan panggilan kepada fungsi `convert_speech_to_text`, menghantar teks kepada fungsi `process_text`:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. Jalankan kod. Tekan butang dan bercakap ke mikrofon. Lepaskan butang apabila selesai, dan audio akan ditukar kepada teks dan dicetak ke konsol.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    Cuba pelbagai jenis ayat, termasuk ayat di mana perkataan berbunyi sama tetapi mempunyai makna yang berbeza. Sebagai contoh, jika anda bercakap dalam Bahasa Inggeris, katakan 'I want to buy two bananas and an apple too', dan perhatikan bagaimana ia menggunakan to, two dan too yang betul berdasarkan konteks perkataan, bukan hanya bunyinya.

> 💁 Anda boleh mencari kod ini dalam folder [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi).

😀 Program ucapan ke teks anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.