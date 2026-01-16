<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "59263d094f20b302053888cd236880c3",
  "translation_date": "2025-08-27T21:27:49+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp.md",
  "language_code": "id"
}
-->
# Mengukur Suhu - Wio Terminal

Dalam bagian pelajaran ini, Anda akan menambahkan sensor suhu ke Wio Terminal Anda, dan membaca nilai suhu darinya.

## Perangkat Keras

Wio Terminal membutuhkan sensor suhu.

Sensor yang akan Anda gunakan adalah [sensor kelembapan dan suhu DHT11](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), yang menggabungkan 2 sensor dalam satu paket. Sensor ini cukup populer, dengan banyak sensor yang tersedia secara komersial yang menggabungkan suhu, kelembapan, dan kadang-kadang tekanan atmosfer. Komponen sensor suhu adalah termistor koefisien suhu negatif (NTC), yaitu termistor di mana resistansi berkurang saat suhu meningkat.

Ini adalah sensor digital, sehingga memiliki ADC bawaan untuk membuat sinyal digital yang berisi data suhu dan kelembapan yang dapat dibaca oleh mikrokontroler.

### Menghubungkan Sensor Suhu

Sensor suhu Grove dapat dihubungkan ke port digital Wio Terminal.

#### Tugas - Menghubungkan Sensor Suhu

Hubungkan sensor suhu.

![Sensor suhu Grove](../../../../../translated_images/id/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.png)

1. Masukkan salah satu ujung kabel Grove ke soket pada sensor kelembapan dan suhu. Kabel hanya dapat masuk dengan satu arah.

1. Dengan Wio Terminal terputus dari komputer atau sumber daya lainnya, hubungkan ujung lain kabel Grove ke soket Grove di sisi kanan Wio Terminal saat Anda melihat layar. Ini adalah soket yang paling jauh dari tombol daya.

![Sensor suhu Grove terhubung ke soket sisi kanan](../../../../../translated_images/id/wio-temperature-sensor.2934928f38c7f79a.webp)

## Memprogram Sensor Suhu

Wio Terminal sekarang dapat diprogram untuk menggunakan sensor suhu yang terpasang.

### Tugas - Memprogram Sensor Suhu

Program perangkat.

1. Buat proyek Wio Terminal baru menggunakan PlatformIO. Beri nama proyek ini `temperature-sensor`. Tambahkan kode dalam fungsi `setup` untuk mengonfigurasi port serial.

    > ⚠️ Anda dapat merujuk ke [instruksi untuk membuat proyek PlatformIO di proyek 1, pelajaran 1 jika diperlukan](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Tambahkan dependensi pustaka untuk pustaka Seeed Grove Humidity and Temperature sensor ke file `platformio.ini` proyek:

    ```ini
    lib_deps =
        seeed-studio/Grove Temperature And Humidity Sensor @ 1.0.1
    ```

    > ⚠️ Anda dapat merujuk ke [instruksi untuk menambahkan pustaka ke proyek PlatformIO di proyek 1, pelajaran 4 jika diperlukan](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md#install-the-wifi-and-mqtt-arduino-libraries).

1. Tambahkan direktif `#include` berikut ke bagian atas file, di bawah `#include <Arduino.h>` yang sudah ada:

    ```cpp
    #include <DHT.h>
    #include <SPI.h>
    ```

    Ini mengimpor file yang diperlukan untuk berinteraksi dengan sensor. File header `DHT.h` berisi kode untuk sensor itu sendiri, dan menambahkan header `SPI.h` memastikan kode yang diperlukan untuk berkomunikasi dengan sensor terhubung saat aplikasi dikompilasi.

1. Sebelum fungsi `setup`, deklarasikan sensor DHT:

    ```cpp
    DHT dht(D0, DHT11);
    ```

    Ini mendeklarasikan instance dari kelas `DHT` yang mengelola sensor **D**igital **H**umidity dan **T**emperature. Sensor ini terhubung ke port `D0`, soket Grove di sisi kanan Wio Terminal. Parameter kedua memberi tahu kode bahwa sensor yang digunakan adalah sensor *DHT11* - pustaka yang Anda gunakan mendukung varian lain dari sensor ini.

1. Dalam fungsi `setup`, tambahkan kode untuk mengatur koneksi serial:

    ```cpp
    void setup()
    {
        Serial.begin(9600);
    
        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    ```

1. Di akhir fungsi `setup`, setelah `delay` terakhir, tambahkan panggilan untuk memulai sensor DHT:

    ```cpp
    dht.begin();
    ```

1. Dalam fungsi `loop`, tambahkan kode untuk memanggil sensor dan mencetak suhu ke port serial:

    ```cpp
    void loop()
    {
        float temp_hum_val[2] = {0};
        dht.readTempAndHumidity(temp_hum_val);
        Serial.print("Temperature: ");
        Serial.print(temp_hum_val[1]);
        Serial.println ("°C");
    
        delay(10000);
    }
    ```

    Kode ini mendeklarasikan array kosong berisi 2 float, dan meneruskannya ke panggilan `readTempAndHumidity` pada instance `DHT`. Panggilan ini mengisi array dengan 2 nilai - kelembapan masuk ke item ke-0 dalam array (ingat dalam C++ array berbasis 0, jadi item ke-0 adalah 'item pertama' dalam array), dan suhu masuk ke item ke-1.

    Suhu dibaca dari item ke-1 dalam array, dan dicetak ke port serial.

    > 🇺🇸 Suhu dibaca dalam Celsius. Untuk orang Amerika, untuk mengonversi ini ke Fahrenheit, bagi nilai Celsius yang dibaca dengan 5, lalu kalikan dengan 9, lalu tambahkan 32. Sebagai contoh, pembacaan suhu 20°C menjadi ((20/5)*9) + 32 = 68°F.

1. Bangun dan unggah kode ke Wio Terminal.

    > ⚠️ Anda dapat merujuk ke [instruksi untuk membuat proyek PlatformIO di proyek 1, pelajaran 1 jika diperlukan](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Setelah diunggah, Anda dapat memantau suhu menggunakan serial monitor:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 24.00°C
    ```

> 💁 Anda dapat menemukan kode ini di folder [code-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/wio-terminal).

😀 Program sensor suhu Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berupaya untuk memberikan hasil yang akurat, harap diketahui bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.