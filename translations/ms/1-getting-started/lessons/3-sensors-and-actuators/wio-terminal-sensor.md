<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7f4ad0ef54f248b85b92187c94cf9dcb",
  "translation_date": "2025-08-27T22:35:25+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-sensor.md",
  "language_code": "ms"
}
-->
# Tambah sensor - Wio Terminal

Dalam bahagian pelajaran ini, anda akan menggunakan sensor cahaya pada Wio Terminal anda.

## Perkakasan

Sensor untuk pelajaran ini adalah **sensor cahaya** yang menggunakan [fotodiod](https://wikipedia.org/wiki/Photodiode) untuk menukar cahaya kepada isyarat elektrik. Ini adalah sensor analog yang menghantar nilai integer dari 0 hingga 1,023 yang menunjukkan jumlah cahaya relatif yang tidak dipetakan kepada sebarang unit ukuran standard seperti [lux](https://wikipedia.org/wiki/Lux).

Sensor cahaya ini terbina dalam Wio Terminal dan boleh dilihat melalui tingkap plastik jernih di bahagian belakang.

![Sensor cahaya di bahagian belakang Wio Terminal](../../../../../translated_images/ms/wio-light-sensor.b1f529f3c95f5165.webp)

## Programkan sensor cahaya

Peranti kini boleh diprogramkan untuk menggunakan sensor cahaya terbina dalam.

### Tugas

Programkan peranti.

1. Buka projek lampu malam dalam VS Code yang anda cipta dalam bahagian tugasan sebelumnya.

1. Tambahkan baris berikut di bahagian bawah fungsi `setup`:

    ```cpp
    pinMode(WIO_LIGHT, INPUT);
    ```

    Baris ini mengkonfigurasi pin yang digunakan untuk berkomunikasi dengan perkakasan sensor.

    Pin `WIO_LIGHT` adalah nombor pin GPIO yang disambungkan kepada sensor cahaya terbina dalam. Pin ini ditetapkan kepada `INPUT`, bermaksud ia disambungkan kepada sensor dan data akan dibaca dari pin tersebut.

1. Padamkan kandungan fungsi `loop`.

1. Tambahkan kod berikut ke dalam fungsi `loop` yang kini kosong.

    ```cpp
    int light = analogRead(WIO_LIGHT);
    Serial.print("Light value: ");
    Serial.println(light);
    ```

    Kod ini membaca nilai analog dari pin `WIO_LIGHT`. Ia membaca nilai dari 0-1,023 dari sensor cahaya terbina dalam. Nilai ini kemudian dihantar ke port serial supaya anda boleh membacanya dalam Serial Monitor apabila kod ini dijalankan. `Serial.print` menulis teks tanpa baris baru di hujungnya, jadi setiap baris akan bermula dengan `Light value:` dan diakhiri dengan nilai cahaya sebenar.

1. Tambahkan kelewatan kecil selama satu saat (1,000ms) di hujung `loop` kerana tahap cahaya tidak perlu diperiksa secara berterusan. Kelewatan mengurangkan penggunaan kuasa peranti.

    ```cpp
    delay(1000);
    ```

1. Sambungkan semula Wio Terminal ke komputer anda, dan muat naik kod baru seperti yang anda lakukan sebelum ini.

1. Sambungkan Serial Monitor. Nilai cahaya akan dipaparkan di terminal. Tutup dan buka sensor cahaya di bahagian belakang Wio Terminal, dan nilai akan berubah.

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

> 💁 Anda boleh menemui kod ini dalam folder [code-sensor/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/wio-terminal).

😀 Menambah sensor kepada program lampu malam anda adalah satu kejayaan!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.