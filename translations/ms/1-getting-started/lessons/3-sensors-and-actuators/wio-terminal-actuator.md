<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "db44083b4dc6fb06eac83c4f16448940",
  "translation_date": "2025-08-28T00:49:40+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-actuator.md",
  "language_code": "ms"
}
-->
# Bina Lampu Malam - Wio Terminal

Dalam bahagian pelajaran ini, anda akan menambah LED pada Wio Terminal anda dan menggunakannya untuk mencipta lampu malam.

## Perkakasan

Lampu malam kini memerlukan sebuah aktuator.

Aktuator adalah **LED**, sebuah [diod pemancar cahaya](https://wikipedia.org/wiki/Light-emitting_diode) yang memancarkan cahaya apabila arus mengalir melaluinya. Ini adalah aktuator digital yang mempunyai 2 keadaan, hidup dan mati. Menghantar nilai 1 akan menyalakan LED, dan 0 akan mematikannya. Ini adalah aktuator Grove luaran dan perlu disambungkan ke Wio Terminal.

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

#### Tugas - sambungkan LED

Sambungkan LED.

![Sebuah Grove LED](../../../../../translated_images/grove-led.6c853be93f473cf2c439cfc74bb1064732b22251a83cedf66e62f783f9cc1a79.ms.png)

1. Pilih LED kegemaran anda dan masukkan kaki-kakinya ke dalam dua lubang pada modul LED.

    LED adalah diod pemancar cahaya, dan diod adalah peranti elektronik yang hanya boleh membawa arus dalam satu arah. Ini bermakna LED perlu disambungkan dengan arah yang betul, jika tidak ia tidak akan berfungsi.

    Salah satu kaki LED adalah pin positif, dan satu lagi adalah pin negatif. LED tidak sepenuhnya bulat, dan sedikit lebih rata di satu sisi. Sisi yang sedikit lebih rata adalah pin negatif. Apabila anda menyambungkan LED ke modul, pastikan pin di sisi yang bulat disambungkan ke soket yang ditandakan **+** di bahagian luar modul, dan sisi yang lebih rata disambungkan ke soket yang lebih dekat dengan tengah modul.

1. Modul LED mempunyai butang putar yang membolehkan anda mengawal kecerahan. Putar ini sepenuhnya ke atas pada permulaan dengan memutarnya lawan arah jam sejauh yang boleh menggunakan pemutar skru kepala Phillips kecil.

1. Masukkan satu hujung kabel Grove ke dalam soket pada modul LED. Ia hanya boleh dimasukkan dalam satu arah sahaja.

1. Dengan Wio Terminal tidak disambungkan ke komputer anda atau bekalan kuasa lain, sambungkan hujung lain kabel Grove ke soket Grove di sebelah kanan Wio Terminal seperti yang anda lihat pada skrin. Ini adalah soket yang paling jauh dari butang kuasa.

    > 💁 Soket Grove di sebelah kanan boleh digunakan dengan sensor dan aktuator analog atau digital. Soket di sebelah kiri adalah untuk sensor dan aktuator digital sahaja. C akan dibincangkan dalam pelajaran seterusnya.

![Grove LED disambungkan ke soket sebelah kanan](../../../../../translated_images/wio-led.265a1897e72d7f21c753257516a4b677d8e30ce2b95fee98189458b3275ba0a6.ms.png)

## Programkan Lampu Malam

Lampu malam kini boleh diprogramkan menggunakan sensor cahaya terbina dalam dan Grove LED.

### Tugas - programkan lampu malam

Programkan lampu malam.

1. Buka projek lampu malam dalam VS Code yang anda cipta dalam bahagian sebelumnya tugasan ini.

1. Tambahkan baris berikut ke bahagian bawah fungsi `setup`:

    ```cpp
    pinMode(D0, OUTPUT);
    ```

    Baris ini mengkonfigurasi pin yang digunakan untuk berkomunikasi dengan LED melalui port Grove.

    Pin `D0` adalah pin digital untuk soket Grove di sebelah kanan. Pin ini ditetapkan kepada `OUTPUT`, bermaksud ia disambungkan ke aktuator dan data akan ditulis ke pin tersebut.

1. Tambahkan kod berikut segera sebelum `delay` dalam fungsi loop:

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

    Kod ini memeriksa nilai `light`. Jika nilai ini kurang daripada 300, ia menghantar nilai `HIGH` ke pin digital `D0`. Nilai `HIGH` ini adalah nilai 1, yang menyalakan LED. Jika cahaya adalah lebih besar atau sama dengan 300, nilai `LOW` iaitu 0 dihantar ke pin, mematikan LED.

    > 💁 Apabila menghantar nilai digital ke aktuator, nilai LOW adalah 0v, dan nilai HIGH adalah voltan maksimum untuk peranti tersebut. Untuk Wio Terminal, voltan HIGH adalah 3.3V.

1. Sambungkan semula Wio Terminal ke komputer anda, dan muat naik kod baru seperti yang anda lakukan sebelum ini.

1. Sambungkan Serial Monitor. Nilai cahaya akan dipaparkan di terminal.

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

1. Tutup dan buka sensor cahaya. Perhatikan bagaimana LED akan menyala jika tahap cahaya adalah 300 atau kurang, dan akan padam apabila tahap cahaya lebih besar daripada 300.

![LED yang disambungkan ke WIO menyala dan padam apabila tahap cahaya berubah](../../../../../images/wio-running-assignment-1-1.gif)

> 💁 Anda boleh menemui kod ini dalam folder [code-actuator/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/wio-terminal).

😀 Program lampu malam anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil maklum bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.