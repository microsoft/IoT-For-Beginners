<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64ad4ddb4de81a18b7252e968f10b404",
  "translation_date": "2025-08-27T23:21:30+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/single-board-computer-set-timer.md",
  "language_code": "id"
}
-->
# Atur Timer - Perangkat IoT Virtual dan Raspberry Pi

Dalam bagian pelajaran ini, Anda akan memanggil kode serverless untuk memahami ucapan, dan mengatur timer pada perangkat IoT virtual atau Raspberry Pi berdasarkan hasilnya.

## Atur Timer

Teks yang dihasilkan dari panggilan pengenalan ucapan perlu dikirim ke kode serverless Anda untuk diproses oleh LUIS, yang akan mengembalikan jumlah detik untuk timer. Jumlah detik ini dapat digunakan untuk mengatur timer.

Timer dapat diatur menggunakan kelas Python `threading.Timer`. Kelas ini menerima waktu penundaan dan sebuah fungsi, dan setelah waktu penundaan, fungsi tersebut akan dijalankan.

### Tugas - kirim teks ke fungsi serverless

1. Buka proyek `smart-timer` di VS Code, dan pastikan lingkungan virtual telah dimuat di terminal jika Anda menggunakan perangkat IoT virtual.

1. Di atas fungsi `process_text`, deklarasikan sebuah fungsi bernama `get_timer_time` untuk memanggil endpoint REST yang telah Anda buat:

    ```python
    def get_timer_time(text):
    ```

1. Tambahkan kode berikut ke fungsi ini untuk mendefinisikan URL yang akan dipanggil:

    ```python
    url = '<URL>'
    ```

    Ganti `<URL>` dengan URL endpoint REST yang telah Anda bangun di pelajaran sebelumnya, baik di komputer Anda maupun di cloud.

1. Tambahkan kode berikut untuk menetapkan teks sebagai properti yang dikirimkan dalam format JSON ke panggilan tersebut:

    ```python
    body = {
        'text': text
    }
    
    response = requests.post(url, json=body)
    ```

1. Di bawah ini, ambil `seconds` dari payload respons, dan kembalikan 0 jika panggilan gagal:

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```

    Panggilan HTTP yang berhasil mengembalikan kode status dalam rentang 200, dan kode serverless Anda mengembalikan 200 jika teks telah diproses dan dikenali sebagai intent pengaturan timer.

### Tugas - atur timer di thread latar belakang

1. Tambahkan pernyataan impor berikut di bagian atas file untuk mengimpor pustaka threading Python:

    ```python
    import threading
    ```

1. Di atas fungsi `process_text`, tambahkan fungsi untuk memberikan respons. Untuk saat ini, fungsi ini hanya akan menulis ke konsol, tetapi nanti dalam pelajaran ini fungsi ini akan mengucapkan teks.

    ```python
    def say(text):
        print(text)
    ```

1. Di bawah ini, tambahkan fungsi yang akan dipanggil oleh timer untuk mengumumkan bahwa timer telah selesai:

    ```python
    def announce_timer(minutes, seconds):
        announcement = 'Times up on your '
        if minutes > 0:
            announcement += f'{minutes} minute '
        if seconds > 0:
            announcement += f'{seconds} second '
        announcement += 'timer.'
        say(announcement)
    ```

    Fungsi ini menerima jumlah menit dan detik untuk timer, dan membangun sebuah kalimat untuk mengatakan bahwa timer telah selesai. Fungsi ini akan memeriksa jumlah menit dan detik, dan hanya menyertakan unit waktu yang memiliki nilai. Misalnya, jika jumlah menit adalah 0, maka hanya detik yang akan disertakan dalam pesan. Kalimat ini kemudian dikirim ke fungsi `say`.

1. Di bawah ini, tambahkan fungsi `create_timer` berikut untuk membuat timer:

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

    Fungsi ini menerima jumlah total detik untuk timer yang akan dikirim dalam perintah, dan mengonversinya menjadi menit dan detik. Fungsi ini kemudian membuat dan memulai objek timer menggunakan jumlah total detik, dengan meneruskan fungsi `announce_timer` dan daftar yang berisi menit dan detik. Ketika timer selesai, fungsi ini akan memanggil fungsi `announce_timer`, dan meneruskan isi daftar ini sebagai parameter - sehingga item pertama dalam daftar diteruskan sebagai parameter `minutes`, dan item kedua sebagai parameter `seconds`.

1. Di akhir fungsi `create_timer`, tambahkan beberapa kode untuk membangun pesan yang akan diucapkan kepada pengguna untuk mengumumkan bahwa timer sedang dimulai:

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

    Sekali lagi, ini hanya menyertakan unit waktu yang memiliki nilai. Kalimat ini kemudian dikirim ke fungsi `say`.

1. Tambahkan yang berikut ini di akhir fungsi `process_text` untuk mendapatkan waktu untuk timer dari teks, lalu buat timer:

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

    Timer hanya dibuat jika jumlah detik lebih besar dari 0.

1. Jalankan aplikasi, dan pastikan aplikasi fungsi juga berjalan. Atur beberapa timer, dan output akan menunjukkan timer sedang diatur, dan kemudian akan menunjukkan saat timer selesai:

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 Anda dapat menemukan kode ini di folder [code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi) atau [code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device).

😀 Program timer Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.