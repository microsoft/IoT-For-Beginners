<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e45d884493c5222348b43fbc4481b6a",
  "translation_date": "2025-08-27T23:29:17+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-microphone.md",
  "language_code": "id"
}
-->
# Konfigurasi Mikrofon dan Speaker - Raspberry Pi

Dalam bagian pelajaran ini, Anda akan menambahkan mikrofon dan speaker ke Raspberry Pi Anda.

## Perangkat Keras

Raspberry Pi memerlukan mikrofon.

Karena Pi tidak memiliki mikrofon bawaan, Anda perlu menambahkan mikrofon eksternal. Ada beberapa cara untuk melakukannya:

* Mikrofon USB
* Headset USB
* Speakerphone USB all-in-one
* Adaptor audio USB dan mikrofon dengan jack 3.5mm
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)

> 💁 Mikrofon Bluetooth tidak semuanya didukung di Raspberry Pi, jadi jika Anda memiliki mikrofon atau headset Bluetooth, Anda mungkin mengalami masalah saat memasangkan atau merekam audio.

Raspberry Pi dilengkapi dengan jack headphone 3.5mm. Anda dapat menggunakan ini untuk menghubungkan headphone, headset, atau speaker. Anda juga dapat menambahkan speaker menggunakan:

* Audio HDMI melalui monitor atau TV
* Speaker USB
* Headset USB
* Speakerphone USB all-in-one
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) dengan speaker yang terhubung, baik ke jack 3.5mm atau port JST

## Hubungkan dan Konfigurasikan Mikrofon dan Speaker

Mikrofon dan speaker perlu dihubungkan dan dikonfigurasi.

### Tugas - Hubungkan dan Konfigurasikan Mikrofon

1. Hubungkan mikrofon menggunakan metode yang sesuai. Misalnya, hubungkan melalui salah satu port USB.

1. Jika Anda menggunakan ReSpeaker 2-Mics Pi HAT, Anda dapat melepas Grove base hat, lalu pasang ReSpeaker hat di tempatnya.

    ![Raspberry Pi dengan ReSpeaker hat](../../../../../translated_images/id/pi-respeaker-hat.f00fabe7dd039a93e2e0aa0fc946c9af0c6a9eb17c32fa1ca097fb4e384f69f0.png)

    Anda akan memerlukan tombol Grove nanti dalam pelajaran ini, tetapi tombol Grove sudah terpasang di hat ini, sehingga Grove base hat tidak diperlukan.

    Setelah hat terpasang, Anda perlu menginstal beberapa driver. Lihat [instruksi memulai dari Seeed](https://wiki.seeedstudio.com/ReSpeaker_2_Mics_Pi_HAT_Raspberry/#getting-started) untuk petunjuk instalasi driver.

    > ⚠️ Instruksi menggunakan `git` untuk mengkloning repositori. Jika Anda belum memiliki `git` diinstal di Pi Anda, Anda dapat menginstalnya dengan menjalankan perintah berikut:
    >
    > ```sh
    > sudo apt install git --yes
    > ```

1. Jalankan perintah berikut di Terminal Anda, baik di Pi atau melalui sesi SSH jarak jauh menggunakan VS Code, untuk melihat informasi tentang mikrofon yang terhubung:

    ```sh
    arecord -l
    ```

    Anda akan melihat daftar mikrofon yang terhubung. Daftarnya akan terlihat seperti berikut:

    ```output
    pi@raspberrypi:~ $ arecord -l
    **** List of CAPTURE Hardware Devices ****
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    Dengan asumsi Anda hanya memiliki satu mikrofon, Anda seharusnya hanya melihat satu entri. Konfigurasi mikrofon bisa rumit di Linux, jadi lebih mudah jika hanya menggunakan satu mikrofon dan mencabut mikrofon lainnya.

    Catat nomor kartu (card number), karena Anda akan membutuhkannya nanti. Dalam output di atas, nomor kartu adalah 1.

### Tugas - Hubungkan dan Konfigurasikan Speaker

1. Hubungkan speaker menggunakan metode yang sesuai.

1. Jalankan perintah berikut di Terminal Anda, baik di Pi atau melalui sesi SSH jarak jauh menggunakan VS Code, untuk melihat informasi tentang speaker yang terhubung:

    ```sh
    aplay -l
    ```

    Anda akan melihat daftar speaker yang terhubung. Daftarnya akan terlihat seperti berikut:

    ```output
    pi@raspberrypi:~ $ aplay -l
    **** List of PLAYBACK Hardware Devices ****
    card 0: Headphones [bcm2835 Headphones], device 0: bcm2835 Headphones [bcm2835 Headphones]
      Subdevices: 8/8
      Subdevice #0: subdevice #0
      Subdevice #1: subdevice #1
      Subdevice #2: subdevice #2
      Subdevice #3: subdevice #3
      Subdevice #4: subdevice #4
      Subdevice #5: subdevice #5
      Subdevice #6: subdevice #6
      Subdevice #7: subdevice #7
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    Anda akan selalu melihat `card 0: Headphones` karena ini adalah jack headphone bawaan. Jika Anda telah menambahkan speaker tambahan, seperti speaker USB, Anda juga akan melihatnya terdaftar.

1. Jika Anda menggunakan speaker tambahan, dan bukan speaker atau headphone yang terhubung ke jack headphone bawaan, Anda perlu mengonfigurasinya sebagai default. Untuk melakukannya, jalankan perintah berikut:

    ```sh
    sudo nano /usr/share/alsa/alsa.conf
    ```

    Ini akan membuka file konfigurasi di `nano`, editor teks berbasis terminal. Gulir ke bawah menggunakan tombol panah pada keyboard Anda hingga Anda menemukan baris berikut:

    ```output
    defaults.pcm.card 0
    ```

    Ubah nilainya dari `0` ke nomor kartu dari daftar yang muncul setelah memanggil `aplay -l`. Sebagai contoh, dalam output di atas terdapat kartu suara kedua bernama `card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]`, menggunakan kartu 1. Untuk menggunakan ini, saya akan memperbarui baris menjadi:

    ```output
    defaults.pcm.card 1
    ```

    Atur nilai ini ke nomor kartu yang sesuai. Anda dapat menavigasi ke nomor tersebut menggunakan tombol panah pada keyboard Anda, lalu hapus dan ketik nomor baru seperti biasa saat mengedit file teks.

1. Simpan perubahan dan tutup file dengan menekan `Ctrl+x`. Tekan `y` untuk menyimpan file, lalu `return` untuk memilih nama file.

### Tugas - Uji Mikrofon dan Speaker

1. Jalankan perintah berikut untuk merekam audio selama 5 detik melalui mikrofon:

    ```sh
    arecord --format=S16_LE --duration=5 --rate=16000 --file-type=wav out.wav
    ```

    Saat perintah ini berjalan, buat suara ke mikrofon seperti berbicara, bernyanyi, beatboxing, memainkan alat musik, atau apa pun yang Anda suka.

1. Setelah 5 detik, perekaman akan berhenti. Jalankan perintah berikut untuk memutar kembali audio:

    ```sh
    aplay --format=S16_LE --rate=16000 out.wav
    ```

    Anda akan mendengar audio diputar kembali melalui speaker. Sesuaikan volume output pada speaker Anda jika diperlukan.

1. Jika Anda perlu menyesuaikan volume port mikrofon bawaan, atau menyesuaikan gain mikrofon, Anda dapat menggunakan utilitas `alsamixer`. Anda dapat membaca lebih lanjut tentang utilitas ini di [halaman manual Linux alsamixer](https://linux.die.net/man/1/alsamixer).

1. Jika Anda mendapatkan kesalahan saat memutar kembali audio, periksa kartu yang Anda atur sebagai `defaults.pcm.card` di file `alsa.conf`.

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diperhatikan bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.