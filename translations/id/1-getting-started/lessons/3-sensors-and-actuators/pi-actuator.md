<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4db8a3879a53490513571df2f6cf7641",
  "translation_date": "2025-08-27T22:30:47+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-actuator.md",
  "language_code": "id"
}
-->
# Membuat Lampu Malam - Raspberry Pi

Dalam bagian pelajaran ini, Anda akan menambahkan LED ke Raspberry Pi Anda dan menggunakannya untuk membuat lampu malam.

## Perangkat Keras

Lampu malam sekarang membutuhkan aktuator.

Aktuatornya adalah **LED**, sebuah [dioda pemancar cahaya](https://wikipedia.org/wiki/Light-emitting_diode) yang memancarkan cahaya ketika arus mengalir melaluinya. Ini adalah aktuator digital yang memiliki 2 keadaan, menyala dan mati. Mengirimkan nilai 1 akan menyalakan LED, dan nilai 0 akan mematikannya. LED adalah aktuator eksternal Grove dan perlu dihubungkan ke Grove Base hat pada Raspberry Pi.

Logika lampu malam dalam pseudo-code adalah:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Hubungkan LED

Grove LED hadir sebagai modul dengan beberapa pilihan LED, memungkinkan Anda memilih warna.

#### Tugas - hubungkan LED

Hubungkan LED.

![Sebuah Grove LED](../../../../../translated_images/id/grove-led.6c853be93f473cf2c439cfc74bb1064732b22251a83cedf66e62f783f9cc1a79.png)

1. Pilih LED favorit Anda dan masukkan kaki-kakinya ke dalam dua lubang pada modul LED.

    LED adalah dioda pemancar cahaya, dan dioda adalah perangkat elektronik yang hanya dapat menghantarkan arus satu arah. Ini berarti LED harus dihubungkan dengan arah yang benar, jika tidak, LED tidak akan berfungsi.

    Salah satu kaki LED adalah pin positif, dan yang lainnya adalah pin negatif. LED tidak sepenuhnya bulat dan sedikit lebih datar di satu sisi. Sisi yang sedikit lebih datar adalah pin negatif. Saat Anda menghubungkan LED ke modul, pastikan pin di sisi yang bulat terhubung ke soket yang ditandai **+** di bagian luar modul, dan sisi yang lebih datar terhubung ke soket yang lebih dekat ke tengah modul.

1. Modul LED memiliki tombol putar yang memungkinkan Anda mengontrol kecerahan. Putar tombol ini sepenuhnya ke atas terlebih dahulu dengan memutarnya berlawanan arah jarum jam sejauh mungkin menggunakan obeng kepala Phillips kecil.

1. Masukkan salah satu ujung kabel Grove ke soket pada modul LED. Kabel ini hanya dapat masuk dengan satu arah.

1. Dengan Raspberry Pi dalam keadaan mati, hubungkan ujung lain kabel Grove ke soket digital yang ditandai **D5** pada Grove Base hat yang terpasang pada Pi. Soket ini adalah soket kedua dari kiri, pada baris soket di sebelah pin GPIO.

![Grove LED terhubung ke soket D5](../../../../../translated_images/id/pi-led.97f1d474981dc35d1c7996c7b17de355d3d0a6bc9606d79fa5f89df933415122.png)

## Program Lampu Malam

Lampu malam sekarang dapat diprogram menggunakan sensor cahaya Grove dan LED Grove.

### Tugas - program lampu malam

Program lampu malam.

1. Nyalakan Pi dan tunggu hingga selesai booting.

1. Buka proyek lampu malam di VS Code yang telah Anda buat pada bagian sebelumnya dari tugas ini, baik yang dijalankan langsung di Pi atau yang terhubung menggunakan ekstensi Remote SSH.

1. Tambahkan kode berikut ke file `app.py` untuk mengimpor pustaka yang diperlukan. Kode ini harus ditambahkan di bagian atas, di bawah baris `import` lainnya.

    ```python
    from grove.grove_led import GroveLed
    ```

    Pernyataan `from grove.grove_led import GroveLed` mengimpor `GroveLed` dari pustaka Python Grove. Pustaka ini memiliki kode untuk berinteraksi dengan Grove LED.

1. Tambahkan kode berikut setelah deklarasi `light_sensor` untuk membuat instance dari kelas yang mengelola LED:

    ```python
    led = GroveLed(5)
    ```

    Baris `led = GroveLed(5)` membuat instance dari kelas `GroveLed` yang terhubung ke pin **D5** - pin digital Grove tempat LED terhubung.

    > 💁 Semua soket memiliki nomor pin unik. Pin 0, 2, 4, dan 6 adalah pin analog, sedangkan pin 5, 16, 18, 22, 24, dan 26 adalah pin digital.

1. Tambahkan pemeriksaan di dalam `while` loop, dan sebelum `time.sleep` untuk memeriksa tingkat cahaya dan menyalakan atau mematikan LED:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Kode ini memeriksa nilai `light`. Jika nilainya kurang dari 300, kode akan memanggil metode `on` dari kelas `GroveLed` yang mengirimkan nilai digital 1 ke LED, menyalakannya. Jika nilai cahaya lebih besar atau sama dengan 300, kode akan memanggil metode `off`, mengirimkan nilai digital 0 ke LED, mematikannya.

    > 💁 Kode ini harus diberi indentasi pada tingkat yang sama dengan baris `print('Light level:', light)` agar berada di dalam while loop!

    > 💁 Saat mengirimkan nilai digital ke aktuator, nilai 0 adalah 0V, dan nilai 1 adalah tegangan maksimum untuk perangkat. Untuk Raspberry Pi dengan sensor dan aktuator Grove, tegangan 1 adalah 3.3V.

1. Dari Terminal VS Code, jalankan perintah berikut untuk menjalankan aplikasi Python Anda:

    ```sh
    python3 app.py
    ```

    Nilai cahaya akan ditampilkan di konsol.

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

1. Tutup dan buka sensor cahaya. Perhatikan bagaimana LED akan menyala jika tingkat cahaya 300 atau kurang, dan mati ketika tingkat cahaya lebih besar dari 300.

    > 💁 Jika LED tidak menyala, pastikan LED terhubung dengan arah yang benar, dan tombol putar diatur ke posisi penuh menyala.

![LED yang terhubung ke Pi menyala dan mati sesuai perubahan tingkat cahaya](../../../../../images/pi-running-assignment-1-1.gif)

> 💁 Anda dapat menemukan kode ini di folder [code-actuator/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/pi).

😀 Program lampu malam Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berupaya untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.