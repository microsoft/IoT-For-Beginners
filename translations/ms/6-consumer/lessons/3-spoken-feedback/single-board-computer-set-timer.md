<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64ad4ddb4de81a18b7252e968f10b404",
  "translation_date": "2025-08-27T23:21:43+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/single-board-computer-set-timer.md",
  "language_code": "ms"
}
-->
# Tetapkan Pemasa - Perkakasan IoT Maya dan Raspberry Pi

Dalam bahagian pelajaran ini, anda akan memanggil kod tanpa pelayan anda untuk memahami pertuturan, dan menetapkan pemasa pada peranti IoT maya atau Raspberry Pi berdasarkan hasilnya.

## Tetapkan Pemasa

Teks yang diterima daripada panggilan pertuturan ke teks perlu dihantar ke kod tanpa pelayan anda untuk diproses oleh LUIS, dan mendapatkan kembali bilangan saat untuk pemasa. Bilangan saat ini boleh digunakan untuk menetapkan pemasa.

Pemasa boleh ditetapkan menggunakan kelas Python `threading.Timer`. Kelas ini memerlukan masa kelewatan dan fungsi, dan selepas masa kelewatan, fungsi tersebut akan dilaksanakan.

### Tugas - hantar teks ke fungsi tanpa pelayan

1. Buka projek `smart-timer` dalam VS Code, dan pastikan persekitaran maya dimuatkan dalam terminal jika anda menggunakan peranti IoT maya.

1. Di atas fungsi `process_text`, isytiharkan fungsi yang dipanggil `get_timer_time` untuk memanggil titik akhir REST yang anda cipta:

    ```python
    def get_timer_time(text):
    ```

1. Tambahkan kod berikut ke fungsi ini untuk menentukan URL yang akan dipanggil:

    ```python
    url = '<URL>'
    ```

    Gantikan `<URL>` dengan URL titik akhir REST anda yang dibina dalam pelajaran sebelumnya, sama ada pada komputer anda atau di awan.

1. Tambahkan kod berikut untuk menetapkan teks sebagai sifat yang dihantar sebagai JSON kepada panggilan:

    ```python
    body = {
        'text': text
    }
    
    response = requests.post(url, json=body)
    ```

1. Di bawah ini, ambil `seconds` daripada payload respons, dan kembalikan 0 jika panggilan gagal:

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```

    Panggilan HTTP yang berjaya mengembalikan kod status dalam julat 200, dan kod tanpa pelayan anda mengembalikan 200 jika teks diproses dan dikenali sebagai niat menetapkan pemasa.

### Tugas - tetapkan pemasa pada thread latar belakang

1. Tambahkan pernyataan import berikut di bahagian atas fail untuk mengimport pustaka threading Python:

    ```python
    import threading
    ```

1. Di atas fungsi `process_text`, tambahkan fungsi untuk menyampaikan respons. Buat masa ini, fungsi ini hanya akan menulis ke konsol, tetapi nanti dalam pelajaran ini ia akan menyampaikan teks.

    ```python
    def say(text):
        print(text)
    ```

1. Di bawah ini, tambahkan fungsi yang akan dipanggil oleh pemasa untuk mengumumkan bahawa pemasa telah selesai:

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

    Fungsi ini mengambil bilangan minit dan saat untuk pemasa, dan membina ayat untuk mengatakan bahawa pemasa telah selesai. Ia akan memeriksa bilangan minit dan saat, dan hanya memasukkan setiap unit masa jika ia mempunyai nilai. Sebagai contoh, jika bilangan minit adalah 0, maka hanya saat yang dimasukkan dalam mesej. Ayat ini kemudian dihantar ke fungsi `say`.

1. Di bawah ini, tambahkan fungsi `create_timer` berikut untuk mencipta pemasa:

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

    Fungsi ini mengambil jumlah bilangan saat untuk pemasa yang akan dihantar dalam arahan, dan menukarkannya kepada minit dan saat. Ia kemudian mencipta dan memulakan objek pemasa menggunakan jumlah bilangan saat, menghantar fungsi `announce_timer` dan senarai yang mengandungi minit dan saat. Apabila pemasa tamat, ia akan memanggil fungsi `announce_timer`, dan menghantar kandungan senarai ini sebagai parameter - jadi item pertama dalam senarai dihantar sebagai parameter `minutes`, dan item kedua sebagai parameter `seconds`.

1. Pada akhir fungsi `create_timer`, tambahkan beberapa kod untuk membina mesej yang akan disampaikan kepada pengguna untuk mengumumkan bahawa pemasa sedang bermula:

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

    Sekali lagi, ini hanya memasukkan unit masa yang mempunyai nilai. Ayat ini kemudian dihantar ke fungsi `say`.

1. Tambahkan perkara berikut pada akhir fungsi `process_text` untuk mendapatkan masa untuk pemasa daripada teks, kemudian cipta pemasa:

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

    Pemasa hanya dicipta jika bilangan saat lebih besar daripada 0.

1. Jalankan aplikasi, dan pastikan aplikasi fungsi juga berjalan. Tetapkan beberapa pemasa, dan output akan menunjukkan pemasa sedang ditetapkan, dan kemudian akan menunjukkan apabila ia tamat:

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 Anda boleh menemui kod ini dalam folder [code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi) atau [code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device).

😀 Program pemasa anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.