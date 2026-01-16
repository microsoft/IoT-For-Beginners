<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "db44083b4dc6fb06eac83c4f16448940",
  "translation_date": "2025-08-27T22:32:03+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-actuator.md",
  "language_code": "id"
}
-->
# Membuat Lampu Malam - Wio Terminal

Dalam bagian pelajaran ini, Anda akan menambahkan LED ke Wio Terminal Anda dan menggunakannya untuk membuat lampu malam.

## Perangkat Keras

Lampu malam sekarang membutuhkan aktuator.

Aktuatornya adalah **LED**, sebuah [dioda pemancar cahaya](https://wikipedia.org/wiki/Light-emitting_diode) yang memancarkan cahaya ketika arus mengalir melaluinya. Ini adalah aktuator digital yang memiliki 2 keadaan, menyala dan mati. Mengirimkan nilai 1 akan menyalakan LED, dan nilai 0 akan mematikannya. Ini adalah aktuator Grove eksternal yang perlu dihubungkan ke Wio Terminal.

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

    LED adalah dioda pemancar cahaya, dan dioda adalah perangkat elektronik yang hanya dapat menghantarkan arus dalam satu arah. Ini berarti LED harus dihubungkan dengan arah yang benar, jika tidak, LED tidak akan berfungsi.

    Salah satu kaki LED adalah pin positif, dan yang lainnya adalah pin negatif. LED tidak sepenuhnya bulat, dan sedikit lebih datar di satu sisi. Sisi yang sedikit lebih datar adalah pin negatif. Saat Anda menghubungkan LED ke modul, pastikan pin di sisi yang lebih bulat terhubung ke soket yang ditandai **+** di bagian luar modul, dan sisi yang lebih datar terhubung ke soket yang lebih dekat ke tengah modul.

1. Modul LED memiliki tombol putar yang memungkinkan Anda mengontrol kecerahan. Putar tombol ini sepenuhnya ke atas dengan memutarnya berlawanan arah jarum jam sejauh mungkin menggunakan obeng kepala Phillips kecil.

1. Masukkan salah satu ujung kabel Grove ke soket pada modul LED. Kabel ini hanya dapat dimasukkan dengan satu arah.

1. Dengan Wio Terminal terputus dari komputer atau sumber daya lainnya, hubungkan ujung lain kabel Grove ke soket Grove di sisi kanan Wio Terminal saat Anda melihat layar. Ini adalah soket yang paling jauh dari tombol daya.

    > 💁 Soket Grove di sisi kanan dapat digunakan dengan sensor dan aktuator analog atau digital. Soket di sisi kiri hanya untuk sensor dan aktuator digital. C akan dibahas dalam pelajaran berikutnya.

![Grove LED terhubung ke soket kanan](../../../../../translated_images/id/wio-led.265a1897e72d7f21.webp)

## Memprogram Lampu Malam

Lampu malam sekarang dapat diprogram menggunakan sensor cahaya bawaan dan Grove LED.

### Tugas - memprogram lampu malam

Program lampu malam.

1. Buka proyek lampu malam di VS Code yang telah Anda buat pada bagian sebelumnya dari tugas ini.

1. Tambahkan baris berikut ke bagian bawah fungsi `setup`:

    ```cpp
    pinMode(D0, OUTPUT);
    ```

    Baris ini mengonfigurasi pin yang digunakan untuk berkomunikasi dengan LED melalui port Grove.

    Pin `D0` adalah pin digital untuk soket Grove di sisi kanan. Pin ini diatur ke `OUTPUT`, yang berarti pin ini terhubung ke aktuator dan data akan ditulis ke pin tersebut.

1. Tambahkan kode berikut segera sebelum `delay` di fungsi loop:

    ```cpp
    if (light < 300)
    {
        digitalWrite(D0, HIGH);
    }
    else
    {
        digitalWrite(D0, LOW);
    }
    ```

    Kode ini memeriksa nilai `light`. Jika nilainya kurang dari 300, kode ini mengirimkan nilai `HIGH` ke pin digital `D0`. Nilai `HIGH` adalah nilai 1, yang menyalakan LED. Jika nilai cahaya lebih besar atau sama dengan 300, nilai `LOW` sebesar 0 dikirimkan ke pin, yang mematikan LED.

    > 💁 Saat mengirimkan nilai digital ke aktuator, nilai LOW adalah 0v, dan nilai HIGH adalah tegangan maksimum untuk perangkat. Untuk Wio Terminal, tegangan HIGH adalah 3.3V.

1. Sambungkan kembali Wio Terminal ke komputer Anda, dan unggah kode baru seperti yang telah Anda lakukan sebelumnya.

1. Sambungkan Serial Monitor. Nilai cahaya akan ditampilkan di terminal.

    ```output
    > Executing task: platformio device monitor <

    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Light value: 4
    Light value: 5
    Light value: 4
    Light value: 158
    Light value: 343
    Light value: 348
    Light value: 344
    ```

1. Tutup dan buka sensor cahaya. Perhatikan bagaimana LED akan menyala jika tingkat cahaya 300 atau kurang, dan mati ketika tingkat cahaya lebih besar dari 300.

![LED yang terhubung ke WIO menyala dan mati saat tingkat cahaya berubah](../../../../../images/wio-running-assignment-1-1.gif)

> 💁 Anda dapat menemukan kode ini di folder [code-actuator/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/wio-terminal).

😀 Program lampu malam Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.