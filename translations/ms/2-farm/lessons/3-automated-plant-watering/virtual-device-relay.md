<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f8f541ee945545017a51aaf309aa37c3",
  "translation_date": "2025-08-27T21:39:16+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/virtual-device-relay.md",
  "language_code": "ms"
}
-->
# Kawal Relay - Perkakasan IoT Maya

Dalam bahagian pelajaran ini, anda akan menambah relay kepada peranti IoT maya anda selain sensor kelembapan tanah, dan mengawalnya berdasarkan tahap kelembapan tanah.

## Perkakasan Maya

Peranti IoT maya akan menggunakan relay Grove yang disimulasikan. Ini menjadikan makmal ini sama seperti menggunakan Raspberry Pi dengan relay Grove fizikal.

Dalam peranti IoT fizikal, relay akan menjadi relay jenis terbuka secara normal (bermaksud litar output terbuka, atau terputus apabila tiada isyarat dihantar ke relay). Relay seperti ini boleh mengendalikan litar output sehingga 250V dan 10A.

### Tambah Relay ke CounterFit

Untuk menggunakan relay maya, anda perlu menambahkannya ke aplikasi CounterFit.

#### Tugas

Tambah relay ke aplikasi CounterFit.

1. Buka projek `soil-moisture-sensor` dari pelajaran lepas dalam VS Code jika ia belum dibuka. Anda akan menambah kepada projek ini.

1. Pastikan aplikasi web CounterFit sedang berjalan.

1. Cipta relay:

    1. Dalam kotak *Create actuator* di panel *Actuators*, klik menu dropdown *Actuator type* dan pilih *Relay*.

    1. Tetapkan *Pin* kepada *5*.

    1. Pilih butang **Add** untuk mencipta relay pada Pin 5.

    ![Tetapan relay](../../../../../translated_images/ms/counterfit-create-relay.fa7c40fd0f2f6afc33b35ea94fcb235085be4861e14e3fe6b9b7bcfc82d1c888.png)

    Relay akan dicipta dan muncul dalam senarai actuator.

    ![Relay yang telah dicipta](../../../../../translated_images/ms/counterfit-relay.bbf74c1dbdc8b9acd983367fcbd06703a402aefef6af54ddb28e11307ba8a12c.png)

## Programkan Relay

Aplikasi sensor kelembapan tanah kini boleh diprogramkan untuk menggunakan relay maya.

### Tugas

Programkan peranti maya.

1. Buka projek `soil-moisture-sensor` dari pelajaran lepas dalam VS Code jika ia belum dibuka. Anda akan menambah kepada projek ini.

1. Tambahkan kod berikut ke fail `app.py` di bawah import sedia ada:

    ```python
    from counterfit_shims_grove.grove_relay import GroveRelay
    ```

    Pernyataan ini mengimport `GroveRelay` dari perpustakaan Grove Python shim untuk berinteraksi dengan relay Grove maya.

1. Tambahkan kod berikut di bawah deklarasi kelas `ADC` untuk mencipta instance `GroveRelay`:

    ```python
    relay = GroveRelay(5)
    ```

    Ini mencipta relay menggunakan pin **5**, pin yang anda sambungkan relay.

1. Untuk menguji sama ada relay berfungsi, tambahkan kod berikut ke dalam gelung `while True:`:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    Kod ini menghidupkan relay, menunggu 0.5 saat, kemudian mematikan relay.

1. Jalankan aplikasi Python. Relay akan hidup dan mati setiap 10 saat, dengan kelewatan setengah saat antara hidup dan mati. Anda akan melihat relay maya dalam aplikasi CounterFit tutup dan buka apabila relay dihidupkan dan dimatikan.

    ![Relay maya hidup dan mati](../../../../../images/virtual-relay-turn-on-off.gif)

## Kawal Relay Berdasarkan Kelembapan Tanah

Sekarang relay berfungsi, ia boleh dikawal berdasarkan bacaan kelembapan tanah.

### Tugas

Kawal relay.

1. Padamkan 3 baris kod yang anda tambahkan untuk menguji relay. Gantikan dengan kod berikut di tempatnya:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    Kod ini memeriksa tahap kelembapan tanah dari sensor kelembapan tanah. Jika ia melebihi 450, ia menghidupkan relay, dan mematikannya jika ia turun di bawah 450.

    > 💁 Ingat bahawa sensor kelembapan tanah kapasitif membaca nilai yang lebih rendah apabila tahap kelembapan tanah lebih tinggi, dan sebaliknya.

1. Jalankan aplikasi Python. Anda akan melihat relay hidup atau mati bergantung pada tahap kelembapan tanah. Ubah *Value* atau tetapan *Random* untuk sensor kelembapan tanah untuk melihat perubahan nilai.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Anda boleh menemui kod ini dalam folder [code-relay/virtual-device](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/virtual-device).

😀 Program sensor kelembapan tanah maya anda yang mengawal relay telah berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.