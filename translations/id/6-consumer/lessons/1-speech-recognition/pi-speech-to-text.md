<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-27T23:31:38+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "id"
}
-->
# Ucapan ke Teks - Raspberry Pi

Dalam bagian pelajaran ini, Anda akan menulis kode untuk mengonversi ucapan dalam audio yang direkam menjadi teks menggunakan layanan ucapan.

## Kirim audio ke layanan ucapan

Audio dapat dikirim ke layanan ucapan menggunakan REST API. Untuk menggunakan layanan ucapan, pertama-tama Anda perlu meminta token akses, lalu gunakan token tersebut untuk mengakses REST API. Token akses ini akan kedaluwarsa setelah 10 menit, jadi kode Anda harus memintanya secara berkala untuk memastikan token selalu diperbarui.

### Tugas - mendapatkan token akses

1. Buka proyek `smart-timer` di Pi Anda.

1. Hapus fungsi `play_audio`. Fungsi ini tidak lagi diperlukan karena Anda tidak ingin pengatur waktu pintar mengulangi apa yang Anda katakan.

1. Tambahkan impor berikut di bagian atas file `app.py`:

    ```python
    import requests
    ```

1. Tambahkan kode berikut di atas loop `while True` untuk mendeklarasikan beberapa pengaturan untuk layanan ucapan:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    Ganti `<key>` dengan kunci API untuk sumber daya layanan ucapan Anda. Ganti `<location>` dengan lokasi yang Anda gunakan saat membuat sumber daya layanan ucapan.

    Ganti `<language>` dengan nama lokal untuk bahasa yang akan Anda gunakan, misalnya `en-GB` untuk Bahasa Inggris, atau `zn-HK` untuk Bahasa Kanton. Anda dapat menemukan daftar bahasa yang didukung dan nama lokalnya di [dokumentasi dukungan bahasa dan suara di Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

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

    Fungsi ini memanggil endpoint penerbitan token, dengan menyertakan kunci API sebagai header. Panggilan ini mengembalikan token akses yang dapat digunakan untuk memanggil layanan ucapan.

1. Di bawah ini, deklarasikan fungsi untuk mengonversi ucapan dalam audio yang direkam menjadi teks menggunakan REST API:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. Di dalam fungsi ini, atur URL REST API dan header:

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

    Fungsi ini membangun URL menggunakan lokasi sumber daya layanan ucapan. Kemudian mengisi header dengan token akses dari fungsi `get_access_token`, serta sample rate yang digunakan untuk merekam audio. Terakhir, fungsi ini mendefinisikan beberapa parameter yang akan diteruskan dengan URL yang berisi bahasa dalam audio.

1. Di bawah ini, tambahkan kode berikut untuk memanggil REST API dan mendapatkan teks kembali:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    Fungsi ini memanggil URL dan mendekode nilai JSON yang ada dalam respons. Nilai `RecognitionStatus` dalam respons menunjukkan apakah panggilan berhasil mengonversi ucapan menjadi teks, dan jika nilainya adalah `Success`, maka teks akan dikembalikan dari fungsi ini, jika tidak, string kosong akan dikembalikan.

1. Di atas loop `while True:`, definisikan fungsi untuk memproses teks yang dikembalikan dari layanan ucapan ke teks. Fungsi ini untuk sementara hanya akan mencetak teks ke konsol.

    ```python
    def process_text(text):
        print(text)
    ```

1. Terakhir, ganti pemanggilan `play_audio` dalam loop `while True` dengan pemanggilan fungsi `convert_speech_to_text`, dan teruskan teks tersebut ke fungsi `process_text`:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. Jalankan kode. Tekan tombol dan berbicaralah ke mikrofon. Lepaskan tombol saat selesai, dan audio akan dikonversi menjadi teks serta dicetak ke konsol.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    Cobalah berbagai jenis kalimat, termasuk kalimat di mana kata-kata terdengar sama tetapi memiliki arti yang berbeda. Misalnya, jika Anda berbicara dalam Bahasa Inggris, katakan 'I want to buy two bananas and an apple too', dan perhatikan bagaimana sistem akan menggunakan kata to, two, dan too yang benar berdasarkan konteks kata, bukan hanya berdasarkan bunyinya.

> 💁 Anda dapat menemukan kode ini di folder [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi).

😀 Program ucapan ke teks Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.