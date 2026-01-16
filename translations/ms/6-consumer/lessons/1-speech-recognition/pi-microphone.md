<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e45d884493c5222348b43fbc4481b6a",
  "translation_date": "2025-08-27T23:29:34+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-microphone.md",
  "language_code": "ms"
}
-->
# Konfigurasi mikrofon dan pembesar suara - Raspberry Pi

Dalam bahagian pelajaran ini, anda akan menambah mikrofon dan pembesar suara pada Raspberry Pi anda.

## Perkakasan

Raspberry Pi memerlukan mikrofon.

Pi tidak mempunyai mikrofon terbina dalam, jadi anda perlu menambah mikrofon luaran. Terdapat beberapa cara untuk melakukannya:

* Mikrofon USB
* Headset USB
* Speakerphone USB serba lengkap
* Penyesuai audio USB dan mikrofon dengan jack 3.5mm
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)

> 💁 Mikrofon Bluetooth tidak semuanya disokong pada Raspberry Pi, jadi jika anda mempunyai mikrofon atau headset Bluetooth, anda mungkin menghadapi masalah untuk menyambung atau menangkap audio.

Raspberry Pi dilengkapi dengan jack fon kepala 3.5mm. Anda boleh menggunakan ini untuk menyambungkan fon kepala, headset atau pembesar suara. Anda juga boleh menambah pembesar suara menggunakan:

* Audio HDMI melalui monitor atau TV
* Pembesar suara USB
* Headset USB
* Speakerphone USB serba lengkap
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) dengan pembesar suara yang disambungkan, sama ada ke jack 3.5mm atau port JST

## Sambung dan konfigurasi mikrofon dan pembesar suara

Mikrofon dan pembesar suara perlu disambungkan dan dikonfigurasi.

### Tugas - sambung dan konfigurasi mikrofon

1. Sambungkan mikrofon menggunakan kaedah yang sesuai. Sebagai contoh, sambungkannya melalui salah satu port USB.

1. Jika anda menggunakan ReSpeaker 2-Mics Pi HAT, anda boleh menanggalkan Grove base hat, kemudian pasangkan ReSpeaker hat di tempatnya.

    ![Raspberry Pi dengan ReSpeaker hat](../../../../../translated_images/ms/pi-respeaker-hat.f00fabe7dd039a93e2e0aa0fc946c9af0c6a9eb17c32fa1ca097fb4e384f69f0.png)

    Anda akan memerlukan butang Grove kemudian dalam pelajaran ini, tetapi satu butang sudah terbina dalam hat ini, jadi Grove base hat tidak diperlukan.

    Setelah hat dipasang, anda perlu memasang beberapa pemacu. Rujuk arahan [Seeed getting started instructions](https://wiki.seeedstudio.com/ReSpeaker_2_Mics_Pi_HAT_Raspberry/#getting-started) untuk arahan pemasangan pemacu.

    > ⚠️ Arahan menggunakan `git` untuk mengklon repositori. Jika anda tidak mempunyai `git` dipasang pada Pi anda, anda boleh memasangnya dengan menjalankan arahan berikut:
    >
    > ```sh
    > sudo apt install git --yes
    > ```

1. Jalankan arahan berikut dalam Terminal anda sama ada pada Pi, atau disambungkan menggunakan VS Code dan sesi SSH jauh untuk melihat maklumat tentang mikrofon yang disambungkan:

    ```sh
    arecord -l
    ```

    Anda akan melihat senarai mikrofon yang disambungkan. Ia akan kelihatan seperti berikut:

    ```output
    pi@raspberrypi:~ $ arecord -l
    **** List of CAPTURE Hardware Devices ****
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    Dengan andaian anda hanya mempunyai satu mikrofon, anda sepatutnya hanya melihat satu entri. Konfigurasi mikrofon boleh menjadi rumit pada Linux, jadi lebih mudah untuk hanya menggunakan satu mikrofon dan mencabut yang lain.

    Catat nombor kad, kerana anda akan memerlukannya kemudian. Dalam output di atas, nombor kad adalah 1.

### Tugas - sambung dan konfigurasi pembesar suara

1. Sambungkan pembesar suara menggunakan kaedah yang sesuai.

1. Jalankan arahan berikut dalam Terminal anda sama ada pada Pi, atau disambungkan menggunakan VS Code dan sesi SSH jauh untuk melihat maklumat tentang pembesar suara yang disambungkan:

    ```sh
    aplay -l
    ```

    Anda akan melihat senarai pembesar suara yang disambungkan. Ia akan kelihatan seperti berikut:

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

    Anda akan sentiasa melihat `card 0: Headphones` kerana ini adalah jack fon kepala terbina dalam. Jika anda telah menambah pembesar suara tambahan, seperti pembesar suara USB, anda akan melihat ini disenaraikan juga.

1. Jika anda menggunakan pembesar suara tambahan, dan bukan pembesar suara atau fon kepala yang disambungkan ke jack fon kepala terbina dalam, anda perlu mengkonfigurasinya sebagai lalai. Untuk melakukannya, jalankan arahan berikut:

    ```sh
    sudo nano /usr/share/alsa/alsa.conf
    ```

    Ini akan membuka fail konfigurasi dalam `nano`, editor teks berasaskan terminal. Tatal ke bawah menggunakan kekunci anak panah pada papan kekunci anda sehingga anda menemui baris berikut:

    ```output
    defaults.pcm.card 0
    ```

    Tukar nilai daripada `0` kepada nombor kad bagi kad yang anda ingin gunakan daripada senarai yang dikembalikan daripada panggilan kepada `aplay -l`. Sebagai contoh, dalam output di atas terdapat kad bunyi kedua yang dipanggil `card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]`, menggunakan kad 1. Untuk menggunakan ini, saya akan mengemas kini baris kepada:

    ```output
    defaults.pcm.card 1
    ```

    Tetapkan nilai ini kepada nombor kad yang sesuai. Anda boleh menavigasi ke nombor menggunakan kekunci anak panah pada papan kekunci anda, kemudian padam dan taip nombor baru seperti biasa semasa mengedit fail teks.

1. Simpan perubahan dan tutup fail dengan menekan `Ctrl+x`. Tekan `y` untuk menyimpan fail, kemudian `return` untuk memilih nama fail.

### Tugas - uji mikrofon dan pembesar suara

1. Jalankan arahan berikut untuk merakam audio selama 5 saat melalui mikrofon:

    ```sh
    arecord --format=S16_LE --duration=5 --rate=16000 --file-type=wav out.wav
    ```

    Semasa arahan ini berjalan, buat bunyi ke dalam mikrofon seperti bercakap, menyanyi, beat boxing, bermain alat muzik atau apa sahaja yang anda suka.

1. Selepas 5 saat, rakaman akan berhenti. Jalankan arahan berikut untuk memainkan semula audio:

    ```sh
    aplay --format=S16_LE --rate=16000 out.wav
    ```

    Anda akan mendengar audio dimainkan semula melalui pembesar suara. Laraskan kelantangan output pada pembesar suara anda jika perlu.

1. Jika anda perlu melaraskan kelantangan port mikrofon terbina dalam, atau melaraskan gain mikrofon, anda boleh menggunakan utiliti `alsamixer`. Anda boleh membaca lebih lanjut tentang utiliti ini di [Linux alsamixer man page](https://linux.die.net/man/1/alsamixer)

1. Jika anda mendapat ralat semasa memainkan semula audio, periksa kad yang anda tetapkan sebagai `defaults.pcm.card` dalam fail `alsa.conf`.

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.