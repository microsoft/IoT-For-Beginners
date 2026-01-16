<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c640f93263fd9adbfda920739e09feb",
  "translation_date": "2025-08-27T22:33:20+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-actuator.md",
  "language_code": "id"
}
-->
# Membangun Lampu Malam - Perangkat IoT Virtual

Dalam bagian pelajaran ini, Anda akan menambahkan LED ke perangkat IoT virtual Anda dan menggunakannya untuk membuat lampu malam.

## Perangkat Keras Virtual

Lampu malam membutuhkan satu aktuator, yang dibuat di aplikasi CounterFit.

Aktuator tersebut adalah **LED**. Pada perangkat IoT fisik, ini akan menjadi [dioda pancaran cahaya](https://wikipedia.org/wiki/Light-emitting_diode) yang memancarkan cahaya ketika arus mengalir melaluinya. Ini adalah aktuator digital yang memiliki 2 keadaan, menyala dan mati. Mengirimkan nilai 1 akan menyalakan LED, dan nilai 0 akan mematikannya.

Logika lampu malam dalam pseudo-code adalah:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Menambahkan aktuator ke CounterFit

Untuk menggunakan LED virtual, Anda perlu menambahkannya ke aplikasi CounterFit.

#### Tugas - menambahkan aktuator ke CounterFit

Tambahkan LED ke aplikasi CounterFit.

1. Pastikan aplikasi web CounterFit berjalan dari bagian sebelumnya dalam tugas ini. Jika tidak, jalankan kembali dan tambahkan sensor cahaya.

1. Buat sebuah LED:

    1. Di kotak *Create actuator* pada panel *Actuator*, buka menu drop-down *Actuator type* dan pilih *LED*.

    1. Atur *Pin* ke *5*.

    1. Pilih tombol **Add** untuk membuat LED pada Pin 5.

    ![Pengaturan LED](../../../../../translated_images/id/counterfit-create-led.ba9db1c9b8c622a635d6dfae5cdc4e70c2b250635bd4f0601c6cf0bd22b7ba46.png)

    LED akan dibuat dan muncul di daftar aktuator.

    ![LED yang telah dibuat](../../../../../translated_images/id/counterfit-led.c0ab02de6d256ad84d9bad4d67a7faa709f0ea83e410cfe9b5561ef0cef30b1c.png)

    Setelah LED dibuat, Anda dapat mengubah warnanya menggunakan pemilih *Color*. Pilih tombol **Set** untuk mengubah warna setelah Anda memilihnya.

### Memprogram lampu malam

Lampu malam sekarang dapat diprogram menggunakan sensor cahaya dan LED di CounterFit.

#### Tugas - memprogram lampu malam

Program lampu malam.

1. Buka proyek lampu malam di VS Code yang Anda buat pada bagian sebelumnya dari tugas ini. Matikan dan buat ulang terminal untuk memastikan terminal berjalan menggunakan lingkungan virtual jika diperlukan.

1. Buka file `app.py`.

1. Tambahkan kode berikut ke file `app.py` untuk mengimpor pustaka yang diperlukan. Kode ini harus ditambahkan di bagian atas, di bawah baris `import` lainnya.

    ```python
    from counterfit_shims_grove.grove_led import GroveLed
    ```

    Pernyataan `from counterfit_shims_grove.grove_led import GroveLed` mengimpor `GroveLed` dari pustaka Python CounterFit Grove shim. Pustaka ini memiliki kode untuk berinteraksi dengan LED yang dibuat di aplikasi CounterFit.

1. Tambahkan kode berikut setelah deklarasi `light_sensor` untuk membuat instance dari kelas yang mengelola LED:

    ```python
    led = GroveLed(5)
    ```

    Baris `led = GroveLed(5)` membuat instance dari kelas `GroveLed` yang terhubung ke pin **5** - pin CounterFit Grove tempat LED terhubung.

1. Tambahkan pemeriksaan di dalam `while` loop, dan sebelum `time.sleep` untuk memeriksa tingkat cahaya dan menyalakan atau mematikan LED:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Kode ini memeriksa nilai `light`. Jika nilainya kurang dari 300, kode akan memanggil metode `on` dari kelas `GroveLed` yang mengirimkan nilai digital 1 ke LED, menyalakannya. Jika nilai cahaya lebih besar atau sama dengan 300, kode akan memanggil metode `off`, mengirimkan nilai digital 0 ke LED, mematikannya.

    > 💁 Kode ini harus diberi indentasi pada level yang sama dengan baris `print('Light level:', light)` agar berada di dalam loop while!

1. Dari Terminal VS Code, jalankan perintah berikut untuk menjalankan aplikasi Python Anda:

    ```sh
    python3 app.py
    ```

    Nilai cahaya akan ditampilkan di konsol.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

1. Ubah pengaturan *Value* atau *Random* untuk memvariasikan tingkat cahaya di atas dan di bawah 300. LED akan menyala dan mati.

![LED di aplikasi CounterFit menyala dan mati saat tingkat cahaya berubah](../../../../../images/virtual-device-running-assignment-1-1.gif)

> 💁 Anda dapat menemukan kode ini di folder [code-actuator/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/virtual-device).

😀 Program lampu malam Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.