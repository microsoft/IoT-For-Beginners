<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4db8a3879a53490513571df2f6cf7641",
  "translation_date": "2025-08-27T22:31:10+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-actuator.md",
  "language_code": "ms"
}
-->
# Membina lampu malam - Raspberry Pi

Dalam bahagian pelajaran ini, anda akan menambah LED pada Raspberry Pi anda dan menggunakannya untuk mencipta lampu malam.

## Perkakasan

Lampu malam kini memerlukan penggerak.

Penggerak adalah **LED**, sebuah [diod pemancar cahaya](https://wikipedia.org/wiki/Light-emitting_diode) yang memancarkan cahaya apabila arus mengalir melaluinya. Ini adalah penggerak digital yang mempunyai 2 keadaan, hidup dan mati. Menghantar nilai 1 akan menghidupkan LED, dan 0 akan mematikannya. LED adalah penggerak Grove luaran dan perlu disambungkan ke Grove Base hat pada Raspberry Pi.

Logik lampu malam dalam pseudo-kod adalah:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Sambungkan LED

Grove LED datang sebagai modul dengan pilihan LED, membolehkan anda memilih warna.

#### Tugasan - sambungkan LED

Sambungkan LED.

![A grove LED](../../../../../translated_images/ms/grove-led.6c853be93f473cf2c439cfc74bb1064732b22251a83cedf66e62f783f9cc1a79.png)

1. Pilih LED kegemaran anda dan masukkan kaki-kaki LED ke dalam dua lubang pada modul LED.

    LED adalah diod pemancar cahaya, dan diod adalah peranti elektronik yang hanya boleh membawa arus satu arah. Ini bermakna LED perlu disambungkan dengan cara yang betul, jika tidak ia tidak akan berfungsi.

    Salah satu kaki LED adalah pin positif, manakala satu lagi adalah pin negatif. LED tidak sepenuhnya bulat dan sedikit lebih rata di satu sisi. Sisi yang lebih rata adalah pin negatif. Apabila anda menyambungkan LED ke modul, pastikan pin di sisi bulat disambungkan ke soket yang ditandakan **+** di bahagian luar modul, dan sisi yang lebih rata disambungkan ke soket yang lebih dekat dengan tengah modul.

1. Modul LED mempunyai butang putar yang membolehkan anda mengawal kecerahan. Putar sepenuhnya ke atas pada permulaan dengan memutarnya berlawanan arah jam sejauh mungkin menggunakan pemutar skru kepala Phillips kecil.

1. Masukkan satu hujung kabel Grove ke dalam soket pada modul LED. Ia hanya boleh dimasukkan satu arah sahaja.

1. Dengan Raspberry Pi dimatikan, sambungkan hujung kabel Grove yang lain ke soket digital yang ditandakan **D5** pada Grove Base hat yang disambungkan ke Pi. Soket ini adalah yang kedua dari kiri, pada barisan soket bersebelahan dengan pin GPIO.

![The grove LED connected to socket D5](../../../../../translated_images/ms/pi-led.97f1d474981dc35d1c7996c7b17de355d3d0a6bc9606d79fa5f89df933415122.png)

## Program lampu malam

Lampu malam kini boleh diprogramkan menggunakan sensor cahaya Grove dan LED Grove.

### Tugasan - program lampu malam

Program lampu malam.

1. Hidupkan Pi dan tunggu sehingga ia selesai boot.

1. Buka projek lampu malam dalam VS Code yang anda cipta dalam bahagian tugasan sebelum ini, sama ada dijalankan terus pada Pi atau disambungkan menggunakan sambungan Remote SSH.

1. Tambahkan kod berikut ke fail `app.py` untuk mengimport pustaka yang diperlukan. Kod ini perlu ditambah di bahagian atas, di bawah baris `import` yang lain.

    ```python
    from grove.grove_led import GroveLed
    ```

    Pernyataan `from grove.grove_led import GroveLed` mengimport `GroveLed` daripada pustaka Python Grove. Pustaka ini mempunyai kod untuk berinteraksi dengan LED Grove.

1. Tambahkan kod berikut selepas deklarasi `light_sensor` untuk mencipta satu instance kelas yang menguruskan LED:

    ```python
    led = GroveLed(5)
    ```

    Baris `led = GroveLed(5)` mencipta satu instance kelas `GroveLed` yang disambungkan ke pin **D5** - pin Grove digital yang disambungkan kepada LED.

    > 💁 Semua soket mempunyai nombor pin unik. Pin 0, 2, 4, dan 6 adalah pin analog, manakala pin 5, 16, 18, 22, 24, dan 26 adalah pin digital.

1. Tambahkan semakan di dalam gelung `while`, dan sebelum `time.sleep` untuk memeriksa tahap cahaya dan menghidupkan atau mematikan LED:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Kod ini memeriksa nilai `light`. Jika nilai ini kurang daripada 300, ia memanggil kaedah `on` daripada kelas `GroveLed` yang menghantar nilai digital 1 kepada LED, menghidupkannya. Jika nilai cahaya adalah lebih besar atau sama dengan 300, ia memanggil kaedah `off`, menghantar nilai digital 0 kepada LED, mematikannya.

    > 💁 Kod ini perlu dijarakkan ke tahap yang sama seperti baris `print('Light level:', light)` untuk berada di dalam gelung while!

    > 💁 Apabila menghantar nilai digital kepada penggerak, nilai 0 adalah 0V, dan nilai 1 adalah voltan maksimum untuk peranti. Untuk Raspberry Pi dengan sensor dan penggerak Grove, voltan 1 adalah 3.3V.

1. Dari Terminal VS Code, jalankan arahan berikut untuk menjalankan aplikasi Python anda:

    ```sh
    python3 app.py
    ```

    Nilai cahaya akan dipaparkan di konsol.

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

1. Tutup dan buka sensor cahaya. Perhatikan bagaimana LED akan menyala jika tahap cahaya adalah 300 atau kurang, dan akan padam apabila tahap cahaya lebih besar daripada 300.

    > 💁 Jika LED tidak menyala, pastikan ia disambungkan dengan cara yang betul, dan butang putar ditetapkan sepenuhnya ke atas.

![The LED connected to the Pi turning on and off as the light level changes](../../../../../images/pi-running-assignment-1-1.gif)

> 💁 Anda boleh menemui kod ini dalam folder [code-actuator/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/pi).

😀 Program lampu malam anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.