<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7f4ad0ef54f248b85b92187c94cf9dcb",
  "translation_date": "2025-08-27T22:35:15+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-sensor.md",
  "language_code": "id"
}
-->
# Menambahkan Sensor - Wio Terminal

Dalam bagian pelajaran ini, Anda akan menggunakan sensor cahaya pada Wio Terminal Anda.

## Perangkat Keras

Sensor untuk pelajaran ini adalah **sensor cahaya** yang menggunakan [fotodioda](https://wikipedia.org/wiki/Photodiode) untuk mengubah cahaya menjadi sinyal listrik. Ini adalah sensor analog yang mengirimkan nilai integer dari 0 hingga 1.023, yang menunjukkan jumlah relatif cahaya tanpa mengacu pada satuan pengukuran standar seperti [lux](https://wikipedia.org/wiki/Lux).

Sensor cahaya ini sudah terpasang di Wio Terminal dan terlihat melalui jendela plastik transparan di bagian belakang.

![Sensor cahaya di bagian belakang Wio Terminal](../../../../../translated_images/wio-light-sensor.b1f529f3c95f5165.id.png)

## Memprogram Sensor Cahaya

Sekarang perangkat dapat diprogram untuk menggunakan sensor cahaya bawaan.

### Tugas

Program perangkat.

1. Buka proyek nightlight di VS Code yang telah Anda buat pada bagian sebelumnya dari tugas ini.

1. Tambahkan baris berikut ke bagian bawah fungsi `setup`:

    ```cpp
    pinMode(WIO_LIGHT, INPUT);
    ```

    Baris ini mengonfigurasi pin yang digunakan untuk berkomunikasi dengan perangkat keras sensor.

    Pin `WIO_LIGHT` adalah nomor pin GPIO yang terhubung ke sensor cahaya bawaan. Pin ini diatur ke `INPUT`, yang berarti pin ini terhubung ke sensor dan data akan dibaca dari pin tersebut.

1. Hapus isi dari fungsi `loop`.

1. Tambahkan kode berikut ke fungsi `loop` yang sekarang kosong.

    ```cpp
    int light = analogRead(WIO_LIGHT);
    Serial.print("Light value: ");
    Serial.println(light);
    ```

    Kode ini membaca nilai analog dari pin `WIO_LIGHT`. Nilai ini berkisar dari 0-1.023 yang berasal dari sensor cahaya bawaan. Nilai ini kemudian dikirim ke port serial sehingga Anda dapat membacanya di Serial Monitor saat kode ini berjalan. `Serial.print` menulis teks tanpa baris baru di akhir, sehingga setiap baris akan dimulai dengan `Light value:` dan diakhiri dengan nilai cahaya sebenarnya.

1. Tambahkan jeda kecil selama satu detik (1.000ms) di akhir `loop`, karena tingkat cahaya tidak perlu diperiksa secara terus-menerus. Jeda ini mengurangi konsumsi daya perangkat.

    ```cpp
    delay(1000);
    ```

1. Sambungkan kembali Wio Terminal ke komputer Anda, dan unggah kode baru seperti yang Anda lakukan sebelumnya.

1. Hubungkan Serial Monitor. Nilai cahaya akan ditampilkan di terminal. Tutup dan buka sensor cahaya di bagian belakang Wio Terminal, dan nilai-nilai tersebut akan berubah.

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

> 💁 Anda dapat menemukan kode ini di folder [code-sensor/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/wio-terminal).

😀 Menambahkan sensor ke program nightlight Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.