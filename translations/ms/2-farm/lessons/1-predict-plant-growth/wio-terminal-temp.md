<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "59263d094f20b302053888cd236880c3",
  "translation_date": "2025-08-27T21:28:03+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp.md",
  "language_code": "ms"
}
-->
# Ukur suhu - Wio Terminal

Dalam bahagian pelajaran ini, anda akan menambah sensor suhu pada Wio Terminal anda, dan membaca nilai suhu daripadanya.

## Perkakasan

Wio Terminal memerlukan sensor suhu.

Sensor yang akan anda gunakan ialah [sensor kelembapan dan suhu DHT11](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), yang menggabungkan 2 sensor dalam satu pakej. Sensor ini agak popular, dengan beberapa sensor yang tersedia secara komersial menggabungkan suhu, kelembapan, dan kadangkala tekanan atmosfera. Komponen sensor suhu adalah termistor koefisien suhu negatif (NTC), iaitu termistor di mana rintangan berkurang apabila suhu meningkat.

Ini adalah sensor digital, jadi ia mempunyai ADC onboard untuk menghasilkan isyarat digital yang mengandungi data suhu dan kelembapan yang boleh dibaca oleh mikrokontroler.

### Sambungkan sensor suhu

Sensor suhu Grove boleh disambungkan ke port digital Wio Terminal.

#### Tugasan - sambungkan sensor suhu

Sambungkan sensor suhu.

![Sensor suhu Grove](../../../../../translated_images/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.ms.png)

1. Masukkan satu hujung kabel Grove ke soket pada sensor kelembapan dan suhu. Ia hanya boleh dimasukkan dalam satu arah sahaja.

1. Dengan Wio Terminal tidak disambungkan ke komputer atau bekalan kuasa lain, sambungkan hujung kabel Grove yang lain ke soket Grove di sebelah kanan Wio Terminal apabila anda melihat skrin. Ini adalah soket yang paling jauh dari butang kuasa.

![Sensor suhu Grove disambungkan ke soket sebelah kanan](../../../../../translated_images/wio-temperature-sensor.2934928f38c7f79a.ms.png)

## Programkan sensor suhu

Wio Terminal kini boleh diprogramkan untuk menggunakan sensor suhu yang disambungkan.

### Tugasan - programkan sensor suhu

Programkan peranti.

1. Buat projek Wio Terminal baru menggunakan PlatformIO. Namakan projek ini `temperature-sensor`. Tambahkan kod dalam fungsi `setup` untuk mengkonfigurasi port serial.

    > ⚠️ Anda boleh merujuk kepada [arahan untuk membuat projek PlatformIO dalam projek 1, pelajaran 1 jika diperlukan](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Tambahkan kebergantungan perpustakaan untuk perpustakaan Seeed Grove Humidity and Temperature sensor ke fail `platformio.ini` projek:

    ```ini
    lib_deps =
        seeed-studio/Grove Temperature And Humidity Sensor @ 1.0.1
    ```

    > ⚠️ Anda boleh merujuk kepada [arahan untuk menambah perpustakaan ke projek PlatformIO dalam projek 1, pelajaran 4 jika diperlukan](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md#install-the-wifi-and-mqtt-arduino-libraries).

1. Tambahkan arahan `#include` berikut ke bahagian atas fail, di bawah `#include <Arduino.h>` yang sedia ada:

    ```cpp
    #include <DHT.h>
    #include <SPI.h>
    ```

    Ini mengimport fail yang diperlukan untuk berinteraksi dengan sensor. Fail header `DHT.h` mengandungi kod untuk sensor itu sendiri, dan menambahkan header `SPI.h` memastikan kod yang diperlukan untuk berkomunikasi dengan sensor disertakan semasa aplikasi dikompilasi.

1. Sebelum fungsi `setup`, isytiharkan sensor DHT:

    ```cpp
    DHT dht(D0, DHT11);
    ```

    Ini mengisytiharkan satu instance kelas `DHT` yang menguruskan sensor **D**igital **H**umidity dan **T**emperature. Sensor ini disambungkan ke port `D0`, iaitu soket Grove di sebelah kanan Wio Terminal. Parameter kedua memberitahu kod bahawa sensor yang digunakan ialah sensor *DHT11* - perpustakaan yang anda gunakan menyokong varian lain sensor ini.

1. Dalam fungsi `setup`, tambahkan kod untuk menyediakan sambungan serial:

    ```cpp
    void setup()
    {
        Serial.begin(9600);
    
        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    ```

1. Di akhir fungsi `setup`, selepas `delay` terakhir, tambahkan panggilan untuk memulakan sensor DHT:

    ```cpp
    dht.begin();
    ```

1. Dalam fungsi `loop`, tambahkan kod untuk memanggil sensor dan mencetak suhu ke port serial:

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

    Kod ini mengisytiharkan array kosong yang mengandungi 2 float, dan menghantar array ini kepada panggilan `readTempAndHumidity` pada instance `DHT`. Panggilan ini mengisi array dengan 2 nilai - kelembapan dimasukkan ke item ke-0 dalam array (ingat dalam C++ array adalah berasaskan 0, jadi item ke-0 adalah 'item pertama' dalam array), dan suhu dimasukkan ke item ke-1.

    Suhu dibaca dari item ke-1 dalam array, dan dicetak ke port serial.

    > 🇺🇸 Suhu dibaca dalam Celsius. Untuk orang Amerika, untuk menukar ini kepada Fahrenheit, bahagikan nilai Celsius yang dibaca dengan 5, kemudian darabkan dengan 9, kemudian tambah 32. Sebagai contoh, bacaan suhu 20°C menjadi ((20/5)*9) + 32 = 68°F.

1. Bina dan muat naik kod ke Wio Terminal.

    > ⚠️ Anda boleh merujuk kepada [arahan untuk membuat projek PlatformIO dalam projek 1, pelajaran 1 jika diperlukan](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Setelah dimuat naik, anda boleh memantau suhu menggunakan serial monitor:

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

> 💁 Anda boleh menemui kod ini dalam folder [code-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/wio-terminal).

😀 Program sensor suhu anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.