<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0ac0afcfb40cb5970ef4cb74f01c32e9",
  "translation_date": "2025-08-27T23:18:50+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-audio.md",
  "language_code": "ms"
}
-->
# Tangkap audio - Raspberry Pi

Dalam bahagian pelajaran ini, anda akan menulis kod untuk menangkap audio pada Raspberry Pi anda. Tangkap audio akan dikawal oleh butang.

## Perkakasan

Raspberry Pi memerlukan butang untuk mengawal tangkap audio.

Butang yang akan anda gunakan ialah butang Grove. Ini adalah sensor digital yang menghidupkan atau mematikan isyarat. Butang ini boleh dikonfigurasikan untuk menghantar isyarat tinggi apabila butang ditekan, dan rendah apabila tidak, atau rendah apabila ditekan dan tinggi apabila tidak.

Jika anda menggunakan ReSpeaker 2-Mics Pi HAT sebagai mikrofon, maka tidak perlu menyambungkan butang kerana HAT ini sudah mempunyai butang. Langkau ke bahagian seterusnya.

### Sambungkan butang

Butang boleh disambungkan ke Grove base hat.

#### Tugasan - sambungkan butang

![Butang Grove](../../../../../translated_images/ms/grove-button.a70cfbb809a8563681003250cf5b06d68cdcc68624f9e2f493d5a534ae2da1e5.png)

1. Masukkan satu hujung kabel Grove ke soket pada modul butang. Ia hanya boleh dimasukkan satu arah sahaja.

1. Dengan Raspberry Pi dimatikan, sambungkan hujung kabel Grove yang lain ke soket digital yang ditandakan **D5** pada Grove Base hat yang disambungkan ke Pi. Soket ini adalah yang kedua dari kiri, pada barisan soket bersebelahan dengan pin GPIO.

![Butang Grove disambungkan ke soket D5](../../../../../translated_images/ms/pi-button.c7a1a4f55943341ce1baf1057658e9a205804d4131d258e820c93f951df0abf3.png)

## Tangkap audio

Anda boleh menangkap audio dari mikrofon menggunakan kod Python.

### Tugasan - tangkap audio

1. Hidupkan Pi dan tunggu sehingga ia selesai boot.

1. Lancarkan VS Code, sama ada secara langsung pada Pi, atau sambungkan melalui sambungan Remote SSH.

1. Pakej PyAudio Pip mempunyai fungsi untuk merakam dan memainkan semula audio. Pakej ini bergantung pada beberapa perpustakaan audio yang perlu dipasang terlebih dahulu. Jalankan arahan berikut dalam terminal untuk memasangnya:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. Pasang pakej PyAudio Pip.

    ```sh
    pip3 install pyaudio
    ```

1. Buat folder baru bernama `smart-timer` dan tambahkan fail bernama `app.py` ke folder ini.

1. Tambahkan import berikut ke bahagian atas fail ini:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    Ini mengimport modul `pyaudio`, beberapa modul Python standard untuk mengendalikan fail wave, dan modul `grove.factory` untuk mengimport `Factory` bagi mencipta kelas butang.

1. Di bawah ini, tambahkan kod untuk mencipta butang Grove.

    Jika anda menggunakan ReSpeaker 2-Mics Pi HAT, gunakan kod berikut:

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    Ini mencipta butang pada port **D17**, port yang disambungkan ke butang pada ReSpeaker 2-Mics Pi HAT. Butang ini ditetapkan untuk menghantar isyarat rendah apabila ditekan.

    Jika anda tidak menggunakan ReSpeaker 2-Mics Pi HAT, dan menggunakan butang Grove yang disambungkan ke base hat, gunakan kod ini.

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    Ini mencipta butang pada port **D5** yang ditetapkan untuk menghantar isyarat tinggi apabila ditekan.

1. Di bawah ini, cipta instance kelas PyAudio untuk mengendalikan audio:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. Nyatakan nombor kad perkakasan untuk mikrofon dan pembesar suara. Ini akan menjadi nombor kad yang anda dapati dengan menjalankan `arecord -l` dan `aplay -l` sebelum ini dalam pelajaran ini.

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    Gantikan `<microphone card number>` dengan nombor kad mikrofon anda.

    Gantikan `<speaker card number>` dengan nombor kad pembesar suara anda, nombor yang sama yang anda tetapkan dalam fail `alsa.conf`.

1. Di bawah ini, nyatakan kadar sampel untuk digunakan bagi tangkap dan main semula audio. Anda mungkin perlu mengubah ini bergantung pada perkakasan yang anda gunakan.

    ```python
    rate = 48000 #48KHz
    ```

    Jika anda mendapat ralat kadar sampel semasa menjalankan kod ini nanti, ubah nilai ini kepada `44100` atau `16000`. Semakin tinggi nilainya, semakin baik kualiti bunyi.

1. Di bawah ini, cipta fungsi baru bernama `capture_audio`. Fungsi ini akan dipanggil untuk menangkap audio dari mikrofon:

    ```python
    def capture_audio():
    ```

1. Di dalam fungsi ini, tambahkan yang berikut untuk menangkap audio:

    ```python
    stream = audio.open(format = pyaudio.paInt16,
                        rate = rate,
                        channels = 1, 
                        input_device_index = microphone_card_number,
                        input = True,
                        frames_per_buffer = 4096)

    frames = []

    while button.is_pressed():
        frames.append(stream.read(4096))

    stream.stop_stream()
    stream.close()
    ```

    Kod ini membuka aliran input audio menggunakan objek PyAudio. Aliran ini akan menangkap audio dari mikrofon pada 16KHz, menangkapnya dalam buffer bersaiz 4096 byte.

    Kod ini kemudian berulang semasa butang Grove ditekan, membaca buffer 4096 byte ini ke dalam array setiap kali.

    > 💁 Anda boleh membaca lebih lanjut tentang pilihan yang diberikan kepada kaedah `open` dalam [dokumentasi PyAudio](https://people.csail.mit.edu/hubert/pyaudio/docs/).

    Setelah butang dilepaskan, aliran dihentikan dan ditutup.

1. Tambahkan yang berikut ke akhir fungsi ini:

    ```python
    wav_buffer = io.BytesIO()
    with wave.open(wav_buffer, 'wb') as wavefile:
        wavefile.setnchannels(1)
        wavefile.setsampwidth(audio.get_sample_size(pyaudio.paInt16))
        wavefile.setframerate(rate)
        wavefile.writeframes(b''.join(frames))
        wav_buffer.seek(0)

    return wav_buffer
    ```

    Kod ini mencipta buffer binari, dan menulis semua audio yang ditangkap ke dalamnya sebagai fail [WAV](https://wikipedia.org/wiki/WAV). Ini adalah cara standard untuk menulis audio tidak termampat ke fail. Buffer ini kemudian dikembalikan.

1. Tambahkan fungsi `play_audio` berikut untuk memainkan semula buffer audio:

    ```python
    def play_audio(buffer):
        stream = audio.open(format = pyaudio.paInt16,
                            rate = rate,
                            channels = 1,
                            output_device_index = speaker_card_number,
                            output = True)
    
        with wave.open(buffer, 'rb') as wf:
            data = wf.readframes(4096)
    
            while len(data) > 0:
                stream.write(data)
                data = wf.readframes(4096)
    
            stream.close()
    ```

    Fungsi ini membuka aliran audio lain, kali ini untuk output - untuk memainkan audio. Ia menggunakan tetapan yang sama seperti aliran input. Buffer kemudian dibuka sebagai fail wave dan ditulis ke aliran output dalam potongan 4096 byte, memainkan audio. Aliran kemudian ditutup.

1. Tambahkan kod berikut di bawah fungsi `capture_audio` untuk berulang sehingga butang ditekan. Setelah butang ditekan, audio ditangkap, kemudian dimainkan.

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. Jalankan kod. Tekan butang dan bercakap ke mikrofon. Lepaskan butang apabila selesai, dan anda akan mendengar rakaman.

    Anda mungkin mendapat beberapa ralat ALSA semasa instance PyAudio dicipta. Ini disebabkan oleh konfigurasi pada Pi untuk peranti audio yang anda tidak miliki. Anda boleh mengabaikan ralat ini.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    Jika anda mendapat ralat berikut:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    maka ubah `rate` kepada sama ada 44100 atau 16000.

> 💁 Anda boleh menemui kod ini dalam folder [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi).

😀 Program rakaman audio anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.