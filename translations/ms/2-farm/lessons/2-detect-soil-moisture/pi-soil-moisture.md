<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9d4d00a47d5d0f3e6ce42c0d1020064a",
  "translation_date": "2025-08-27T21:57:07+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/pi-soil-moisture.md",
  "language_code": "ms"
}
-->
# Ukur Kelembapan Tanah - Raspberry Pi

Dalam bahagian pelajaran ini, anda akan menambah sensor kelembapan tanah kapasitif pada Raspberry Pi anda, dan membaca nilai daripadanya.

## Perkakasan

Raspberry Pi memerlukan sensor kelembapan tanah kapasitif.

Sensor yang akan anda gunakan ialah [Capacitive Soil Moisture Sensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), yang mengukur kelembapan tanah dengan mengesan kapasitans tanah, satu sifat yang berubah apabila kelembapan tanah berubah. Apabila kelembapan tanah meningkat, voltan akan menurun.

Ini adalah sensor analog, jadi ia menggunakan pin analog, dan ADC 10-bit dalam Grove Base Hat pada Pi untuk menukar voltan kepada isyarat digital dari 1-1,023. Isyarat ini kemudian dihantar melalui I²C menggunakan pin GPIO pada Pi.

### Sambungkan sensor kelembapan tanah

Sensor kelembapan tanah Grove boleh disambungkan ke Raspberry Pi.

#### Tugasan - sambungkan sensor kelembapan tanah

Sambungkan sensor kelembapan tanah.

![Sensor kelembapan tanah Grove](../../../../../translated_images/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.ms.png)

1. Masukkan satu hujung kabel Grove ke dalam soket pada sensor kelembapan tanah. Ia hanya boleh dimasukkan dalam satu arah sahaja.

1. Dengan Raspberry Pi dimatikan, sambungkan hujung lain kabel Grove ke soket analog yang ditandakan **A0** pada Grove Base Hat yang dipasang pada Pi. Soket ini adalah yang kedua dari kanan, pada barisan soket bersebelahan dengan pin GPIO.

![Sensor kelembapan tanah Grove disambungkan ke soket A0](../../../../../translated_images/pi-soil-moisture-sensor.fdd7eb2393792cf6739cacf1985d9f55beda16d372f30d0b5a51d586f978a870.ms.png)

1. Masukkan sensor kelembapan tanah ke dalam tanah. Ia mempunyai 'garis kedudukan tertinggi' - satu garis putih melintang pada sensor. Masukkan sensor sehingga ke garis ini tetapi jangan melebihi garis tersebut.

![Sensor kelembapan tanah Grove dalam tanah](../../../../../translated_images/soil-moisture-sensor-in-soil.bfad91002bda5e96.ms.png)

## Programkan sensor kelembapan tanah

Raspberry Pi kini boleh diprogramkan untuk menggunakan sensor kelembapan tanah yang disambungkan.

### Tugasan - programkan sensor kelembapan tanah

Programkan peranti.

1. Hidupkan Pi dan tunggu sehingga ia selesai boot.

1. Lancarkan VS Code, sama ada secara langsung pada Pi, atau sambung menggunakan sambungan Remote SSH.

    > ⚠️ Anda boleh merujuk kepada [arahan untuk menyediakan dan melancarkan VS Code dalam nightlight - pelajaran 1 jika diperlukan](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Dari terminal, buat folder baru dalam direktori rumah pengguna `pi` yang dinamakan `soil-moisture-sensor`. Buat fail dalam folder ini yang dinamakan `app.py`.

1. Buka folder ini dalam VS Code.

1. Tambahkan kod berikut ke fail `app.py` untuk mengimport beberapa pustaka yang diperlukan:

    ```python
    import time
    from grove.adc import ADC
    ```

    Pernyataan `import time` mengimport modul `time` yang akan digunakan kemudian dalam tugasan ini.

    Pernyataan `from grove.adc import ADC` mengimport `ADC` daripada pustaka Python Grove. Pustaka ini mengandungi kod untuk berinteraksi dengan penukar analog ke digital pada Pi Base Hat dan membaca voltan daripada sensor analog.

1. Tambahkan kod berikut di bawah ini untuk mencipta satu instance kelas `ADC`:

    ```python
    adc = ADC()
    ```

1. Tambahkan gelung tak terhingga yang membaca daripada ADC ini pada pin A0, dan menulis hasilnya ke konsol. Gelung ini kemudian boleh berhenti selama 10 saat antara bacaan.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)

        time.sleep(10)
    ```

1. Jalankan aplikasi Python. Anda akan melihat bacaan kelembapan tanah ditulis ke konsol. Tambahkan air ke tanah, atau keluarkan sensor daripada tanah, dan lihat nilai berubah.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

    Dalam contoh output di atas, anda boleh melihat voltan menurun apabila air ditambah.

> 💁 Anda boleh menemui kod ini dalam folder [code/pi](../../../../../2-farm/lessons/2-detect-soil-moisture/code/pi).

😀 Program sensor kelembapan tanah anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil maklum bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat penting, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.