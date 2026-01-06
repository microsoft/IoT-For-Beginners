<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f3c5d8afa2ef6a0b425ef8ff20615cb4",
  "translation_date": "2025-08-27T21:37:02+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/wio-terminal-relay.md",
  "language_code": "ms"
}
-->
# Kawal Relay - Wio Terminal

Dalam bahagian pelajaran ini, anda akan menambah relay pada Wio Terminal anda selain sensor kelembapan tanah, dan mengawalnya berdasarkan tahap kelembapan tanah.

## Perkakasan

Wio Terminal memerlukan relay.

Relay yang akan digunakan ialah [Grove relay](https://www.seeedstudio.com/Grove-Relay.html), relay jenis terbuka biasa (bermaksud litar output terbuka atau terputus apabila tiada isyarat dihantar ke relay) yang boleh mengendalikan litar output sehingga 250V dan 10A.

Ini adalah penggerak digital, jadi ia disambungkan ke pin digital pada Wio Terminal. Port gabungan analog/digital sudah digunakan dengan sensor kelembapan tanah, jadi relay ini disambungkan ke port lain, iaitu port gabungan I2C dan digital.

### Sambungkan relay

Relay Grove boleh disambungkan ke port digital Wio Terminal.

#### Tugasan

Sambungkan relay.

![Relay Grove](../../../../../translated_images/grove-relay.d426958ca210fbd0fb7983d7edc069d46c73a8b0a099d94797bd756f7b6bb6be.ms.png)

1. Masukkan satu hujung kabel Grove ke soket pada relay. Ia hanya boleh dimasukkan dalam satu arah sahaja.

1. Dengan Wio Terminal tidak disambungkan ke komputer atau bekalan kuasa lain, sambungkan hujung lain kabel Grove ke soket Grove di sebelah kiri Wio Terminal seperti yang dilihat pada skrin. Biarkan sensor kelembapan tanah disambungkan ke soket sebelah kanan.

![Relay Grove disambungkan ke soket kiri, dan sensor kelembapan tanah disambungkan ke soket kanan](../../../../../translated_images/wio-relay-and-soil-moisture-sensor.ed722202d42babe0.ms.png)

1. Masukkan sensor kelembapan tanah ke dalam tanah, jika ia belum dimasukkan dari pelajaran sebelumnya.

## Programkan relay

Wio Terminal kini boleh diprogramkan untuk menggunakan relay yang disambungkan.

### Tugasan

Programkan peranti.

1. Buka projek `soil-moisture-sensor` dari pelajaran sebelumnya dalam VS Code jika belum dibuka. Anda akan menambah kod pada projek ini.

2. Tiada perpustakaan untuk penggerak ini - ia adalah penggerak digital yang dikawal oleh isyarat tinggi atau rendah. Untuk menghidupkannya, anda menghantar isyarat tinggi ke pin (3.3V), untuk mematikannya anda menghantar isyarat rendah (0V). Anda boleh melakukannya menggunakan fungsi Arduino [`digitalWrite`](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/) terbina. Mulakan dengan menambah kod berikut di bahagian bawah fungsi `setup` untuk menetapkan port gabungan I2C/digital sebagai pin output untuk menghantar voltan ke relay:

    ```cpp
    pinMode(PIN_WIRE_SCL, OUTPUT);
    ```

    `PIN_WIRE_SCL` ialah nombor port untuk port gabungan I2C/digital.

1. Untuk menguji relay berfungsi, tambahkan kod berikut ke fungsi `loop`, di bawah `delay` terakhir:

    ```cpp
    digitalWrite(PIN_WIRE_SCL, HIGH);
    delay(500);
    digitalWrite(PIN_WIRE_SCL, LOW);
    ```

    Kod ini menghantar isyarat tinggi ke pin yang disambungkan ke relay untuk menghidupkannya, menunggu 500ms (setengah saat), kemudian menghantar isyarat rendah untuk mematikan relay.

1. Bina dan muat naik kod ke Wio Terminal.

1. Setelah dimuat naik, relay akan hidup dan mati setiap 10 saat, dengan kelewatan setengah saat antara hidup dan mati. Anda akan mendengar bunyi klik relay ketika hidup dan mati. LED pada papan Grove akan menyala apabila relay hidup, dan padam apabila relay mati.

    ![Relay hidup dan mati](../../../../../images/relay-turn-on-off.gif)

## Kawal relay berdasarkan kelembapan tanah

Sekarang relay berfungsi, ia boleh dikawal sebagai tindak balas kepada bacaan kelembapan tanah.

### Tugasan

Kawal relay.

1. Padamkan 3 baris kod yang anda tambahkan untuk menguji relay. Gantikan dengan kod berikut:

    ```cpp
    if (soil_moisture > 450)
    {
        Serial.println("Soil Moisture is too low, turning relay on.");
        digitalWrite(PIN_WIRE_SCL, HIGH);
    }
    else
    {
        Serial.println("Soil Moisture is ok, turning relay off.");
        digitalWrite(PIN_WIRE_SCL, LOW);
    }
    ```

    Kod ini memeriksa tahap kelembapan tanah dari sensor kelembapan tanah. Jika ia melebihi 450, relay akan dihidupkan, dan dimatikan apabila ia turun di bawah 450.

    > 💁 Ingat bahawa sensor kelembapan tanah kapasitif membaca tahap kelembapan tanah yang lebih rendah, semakin banyak kelembapan dalam tanah dan sebaliknya.

1. Bina dan muat naik kod ke Wio Terminal.

1. Pantau peranti melalui serial monitor. Anda akan melihat relay hidup atau mati bergantung pada tahap kelembapan tanah. Cuba pada tanah kering, kemudian tambahkan air.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Anda boleh menemui kod ini dalam folder [code-relay/wio-terminal](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/wio-terminal).

😀 Program sensor kelembapan tanah yang mengawal relay anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat penting, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.