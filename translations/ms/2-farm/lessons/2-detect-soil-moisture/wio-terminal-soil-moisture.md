<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0d55caa8c23d73635b7559102cd17b8a",
  "translation_date": "2025-08-27T21:53:48+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/wio-terminal-soil-moisture.md",
  "language_code": "ms"
}
-->
# Ukur Kelembapan Tanah - Wio Terminal

Dalam bahagian pelajaran ini, anda akan menambah sensor kelembapan tanah kapasitif pada Wio Terminal anda, dan membaca nilai daripadanya.

## Perkakasan

Wio Terminal memerlukan sensor kelembapan tanah kapasitif.

Sensor yang akan anda gunakan ialah [Capacitive Soil Moisture Sensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), yang mengukur kelembapan tanah dengan mengesan kapasitans tanah, satu sifat yang berubah apabila kelembapan tanah berubah. Apabila kelembapan tanah meningkat, voltan akan berkurang.

Ini adalah sensor analog, jadi ia disambungkan kepada pin analog pada Wio Terminal, menggunakan ADC onboard untuk menghasilkan nilai dari 0-1,023.

### Sambungkan sensor kelembapan tanah

Sensor kelembapan tanah Grove boleh disambungkan kepada port analog/digital yang boleh dikonfigurasi pada Wio Terminal.

#### Tugasan - sambungkan sensor kelembapan tanah

Sambungkan sensor kelembapan tanah.

![Sensor kelembapan tanah Grove](../../../../../translated_images/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.ms.png)

1. Masukkan satu hujung kabel Grove ke soket pada sensor kelembapan tanah. Ia hanya boleh dimasukkan dalam satu arah sahaja.

1. Dengan Wio Terminal tidak disambungkan kepada komputer atau bekalan kuasa lain, sambungkan hujung kabel Grove yang lain ke soket Grove di sebelah kanan Wio Terminal apabila anda melihat skrin. Ini adalah soket yang paling jauh dari butang kuasa.

![Sensor kelembapan tanah Grove disambungkan ke soket sebelah kanan](../../../../../translated_images/wio-soil-moisture-sensor.46919b61c3f6cb74.ms.png)

1. Masukkan sensor kelembapan tanah ke dalam tanah. Ia mempunyai 'garis kedudukan tertinggi' - garis putih melintang pada sensor. Masukkan sensor sehingga garis ini tetapi tidak melebihi garis tersebut.

![Sensor kelembapan tanah Grove dalam tanah](../../../../../translated_images/soil-moisture-sensor-in-soil.bfad91002bda5e96.ms.png)

1. Anda kini boleh menyambungkan Wio Terminal ke komputer anda.

## Programkan sensor kelembapan tanah

Wio Terminal kini boleh diprogramkan untuk menggunakan sensor kelembapan tanah yang disambungkan.

### Tugasan - programkan sensor kelembapan tanah

Programkan peranti.

1. Cipta projek Wio Terminal baharu menggunakan PlatformIO. Namakan projek ini `soil-moisture-sensor`. Tambahkan kod dalam fungsi `setup` untuk mengkonfigurasi port serial.

    > ⚠️ Anda boleh merujuk kepada [arahan untuk mencipta projek PlatformIO dalam projek 1, pelajaran 1 jika diperlukan](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Tiada perpustakaan untuk sensor ini, sebaliknya anda boleh membaca dari pin analog menggunakan fungsi Arduino [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/) terbina dalam. Mulakan dengan mengkonfigurasi pin analog untuk input supaya nilai boleh dibaca daripadanya dengan menambahkan kod berikut ke fungsi `setup`.

    ```cpp
    pinMode(A0, INPUT);
    ```

    Ini menetapkan pin `A0`, pin gabungan analog/digital, sebagai pin input yang voltan boleh dibaca daripadanya.

1. Tambahkan kod berikut ke fungsi `loop` untuk membaca voltan dari pin ini:

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. Di bawah kod ini, tambahkan kod berikut untuk mencetak nilai ke port serial:

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. Akhir sekali, tambahkan kelewatan selama 10 saat di penghujung:

    ```cpp
    delay(10000);
    ```

1. Bina dan muat naik kod ke Wio Terminal.

    > ⚠️ Anda boleh merujuk kepada [arahan untuk mencipta projek PlatformIO dalam projek 1, pelajaran 1 jika diperlukan](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Setelah dimuat naik, anda boleh memantau kelembapan tanah menggunakan serial monitor. Tambahkan sedikit air ke tanah, atau keluarkan sensor dari tanah, dan lihat nilai berubah.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Soil Moisture: 526
    Soil Moisture: 529
    Soil Moisture: 521
    Soil Moisture: 494
    Soil Moisture: 454
    Soil Moisture: 456
    Soil Moisture: 395
    Soil Moisture: 388
    Soil Moisture: 394
    Soil Moisture: 391
    ```

    Dalam contoh output di atas, anda boleh melihat voltan menurun apabila air ditambahkan.

> 💁 Anda boleh menemui kod ini dalam folder [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal).

😀 Program sensor kelembapan tanah anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.