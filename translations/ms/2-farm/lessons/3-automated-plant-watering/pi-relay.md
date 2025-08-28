<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "66b81165e60f8f169bd52a401b6a0f8b",
  "translation_date": "2025-08-28T01:56:02+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/pi-relay.md",
  "language_code": "ms"
}
-->
# Kawal relay - Raspberry Pi

Dalam bahagian pelajaran ini, anda akan menambah relay pada Raspberry Pi anda selain sensor kelembapan tanah, dan mengawalnya berdasarkan tahap kelembapan tanah.

## Perkakasan

Raspberry Pi memerlukan relay.

Relay yang akan anda gunakan ialah [Grove relay](https://www.seeedstudio.com/Grove-Relay.html), iaitu relay jenis "normally-open" (bermaksud litar output terbuka, atau terputus apabila tiada isyarat dihantar ke relay) yang boleh mengendalikan litar output sehingga 250V dan 10A.

Ini adalah penggerak digital, jadi ia disambungkan ke pin digital pada Grove Base Hat.

### Sambungkan relay

Relay Grove boleh disambungkan ke Raspberry Pi.

#### Tugasan

Sambungkan relay.

![Relay Grove](../../../../../translated_images/grove-relay.d426958ca210fbd0fb7983d7edc069d46c73a8b0a099d94797bd756f7b6bb6be.ms.png)

1. Masukkan satu hujung kabel Grove ke soket pada relay. Ia hanya boleh dimasukkan dalam satu arah sahaja.

1. Dengan Raspberry Pi dimatikan, sambungkan hujung lain kabel Grove ke soket digital yang ditandakan **D5** pada Grove Base Hat yang disambungkan ke Pi. Soket ini adalah yang kedua dari kiri, pada barisan soket bersebelahan dengan pin GPIO. Biarkan sensor kelembapan tanah disambungkan ke soket **A0**.

![Relay Grove disambungkan ke soket D5, dan sensor kelembapan tanah disambungkan ke soket A0](../../../../../translated_images/pi-relay-and-soil-moisture-sensor.02f3198975b8c53e69ec716cd2719ce117700bd1fc933eaf93476c103c57939b.ms.png)

1. Masukkan sensor kelembapan tanah ke dalam tanah, jika ia belum dimasukkan dari pelajaran sebelumnya.

## Program relay

Raspberry Pi kini boleh diprogramkan untuk menggunakan relay yang disambungkan.

### Tugasan

Programkan peranti.

1. Hidupkan Pi dan tunggu sehingga ia selesai boot.

1. Buka projek `soil-moisture-sensor` dari pelajaran sebelumnya dalam VS Code jika ia belum dibuka. Anda akan menambah kod pada projek ini.

1. Tambahkan kod berikut ke dalam fail `app.py` di bawah import sedia ada:

    ```python
    from grove.grove_relay import GroveRelay
    ```

    Pernyataan ini mengimport `GroveRelay` dari pustaka Python Grove untuk berinteraksi dengan relay Grove.

1. Tambahkan kod berikut di bawah deklarasi kelas `ADC` untuk mencipta instance `GroveRelay`:

    ```python
    relay = GroveRelay(5)
    ```

    Ini mencipta relay menggunakan pin **D5**, iaitu pin digital yang anda sambungkan relay.

1. Untuk menguji sama ada relay berfungsi, tambahkan kod berikut ke dalam gelung `while True:`:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    Kod ini menghidupkan relay, menunggu selama 0.5 saat, kemudian mematikan relay.

1. Jalankan aplikasi Python. Relay akan hidup dan mati setiap 10 saat, dengan kelewatan setengah saat antara hidup dan mati. Anda akan mendengar bunyi klik relay ketika ia hidup dan mati. LED pada papan Grove akan menyala apabila relay hidup, dan padam apabila relay mati.

    ![Relay hidup dan mati](../../../../../images/relay-turn-on-off.gif)

## Kawal relay berdasarkan kelembapan tanah

Sekarang relay berfungsi, ia boleh dikawal berdasarkan bacaan kelembapan tanah.

### Tugasan

Kawal relay.

1. Padamkan 3 baris kod yang anda tambahkan untuk menguji relay. Gantikan dengan kod berikut:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    Kod ini memeriksa tahap kelembapan tanah dari sensor kelembapan tanah. Jika ia melebihi 450, relay akan dihidupkan, dan akan dimatikan apabila ia di bawah 450.

    > 💁 Ingat bahawa sensor kelembapan tanah kapasitif membaca: semakin rendah tahap kelembapan tanah, semakin banyak kelembapan dalam tanah, dan sebaliknya.

1. Jalankan aplikasi Python. Anda akan melihat relay hidup atau mati bergantung pada tahap kelembapan tanah. Cuba pada tanah kering, kemudian tambahkan air.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Anda boleh menemui kod ini dalam folder [code-relay/pi](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/pi).

😀 Program sensor kelembapan tanah yang mengawal relay anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.