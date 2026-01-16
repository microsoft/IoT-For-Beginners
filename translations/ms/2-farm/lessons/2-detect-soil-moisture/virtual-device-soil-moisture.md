<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2bf65f162bcebd35fbcba5fd245afac4",
  "translation_date": "2025-08-27T21:55:58+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/virtual-device-soil-moisture.md",
  "language_code": "ms"
}
-->
# Ukur Kelembapan Tanah - Perkakasan IoT Maya

Dalam bahagian pelajaran ini, anda akan menambah sensor kelembapan tanah kapasitif ke peranti IoT maya anda, dan membaca nilai daripadanya.

## Perkakasan Maya

Peranti IoT maya akan menggunakan sensor kelembapan tanah kapasitif Grove yang disimulasikan. Ini memastikan makmal ini sama seperti menggunakan Raspberry Pi dengan sensor kelembapan tanah kapasitif fizikal.

Dalam peranti IoT fizikal, sensor kelembapan tanah adalah sensor kapasitif yang mengukur kelembapan tanah dengan mengesan kapasitans tanah, iaitu sifat yang berubah apabila kelembapan tanah berubah. Apabila kelembapan tanah meningkat, voltan akan berkurang.

Ini adalah sensor analog, jadi ia menggunakan ADC 10-bit yang disimulasikan untuk melaporkan nilai dari 1-1,023.

### Tambah sensor kelembapan tanah ke CounterFit

Untuk menggunakan sensor kelembapan tanah maya, anda perlu menambahkannya ke aplikasi CounterFit.

#### Tugas - Tambah sensor kelembapan tanah ke CounterFit

Tambah sensor kelembapan tanah ke aplikasi CounterFit.

1. Cipta aplikasi Python baru pada komputer anda dalam folder bernama `soil-moisture-sensor` dengan satu fail bernama `app.py` dan persekitaran maya Python, serta tambahkan pakej pip CounterFit.

    > ⚠️ Anda boleh merujuk kepada [arahan untuk mencipta dan menyediakan projek Python CounterFit dalam pelajaran 1 jika diperlukan](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Pastikan aplikasi web CounterFit sedang berjalan.

1. Cipta sensor kelembapan tanah:

    1. Dalam kotak *Create sensor* di panel *Sensors*, klik menu dropdown *Sensor type* dan pilih *Soil Moisture*.

    1. Biarkan *Units* ditetapkan kepada *NoUnits*.

    1. Pastikan *Pin* ditetapkan kepada *0*.

    1. Pilih butang **Add** untuk mencipta sensor *Soil Moisture* pada Pin 0.

    ![Tetapan sensor kelembapan tanah](../../../../../translated_images/ms/counterfit-create-soil-moisture-sensor.35266135a5e0ae68b29a684d7db0d2933a8098b2307d197f7c71577b724603aa.png)

    Sensor kelembapan tanah akan dicipta dan muncul dalam senarai sensor.

    ![Sensor kelembapan tanah dicipta](../../../../../translated_images/ms/counterfit-soil-moisture-sensor.81742b2de0e9de60a3b3b9a2ff8ecc686d428eb6d71820f27a693be26e5aceee.png)

## Program aplikasi sensor kelembapan tanah

Aplikasi sensor kelembapan tanah kini boleh diprogramkan menggunakan sensor CounterFit.

### Tugas - program aplikasi sensor kelembapan tanah

Program aplikasi sensor kelembapan tanah.

1. Pastikan aplikasi `soil-moisture-sensor` dibuka dalam VS Code.

1. Buka fail `app.py`.

1. Tambahkan kod berikut di bahagian atas `app.py` untuk menyambungkan aplikasi ke CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Tambahkan kod berikut ke fail `app.py` untuk mengimport beberapa pustaka yang diperlukan:

    ```python
    import time
    from counterfit_shims_grove.adc import ADC
    ```

    Pernyataan `import time` mengimport modul `time` yang akan digunakan kemudian dalam tugasan ini.

    Pernyataan `from counterfit_shims_grove.adc import ADC` mengimport kelas `ADC` untuk berinteraksi dengan penukar analog ke digital maya yang boleh disambungkan ke sensor CounterFit.

1. Tambahkan kod berikut di bawah ini untuk mencipta satu instance kelas `ADC`:

    ```python
    adc = ADC()
    ```

1. Tambahkan gelung tak terhingga yang membaca dari ADC ini pada pin 0 dan menulis hasilnya ke konsol. Gelung ini kemudian boleh berhenti selama 10 saat antara bacaan.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)
    
        time.sleep(10)
    ```

1. Dari aplikasi CounterFit, ubah nilai sensor kelembapan tanah yang akan dibaca oleh aplikasi. Anda boleh melakukannya dengan dua cara:

    * Masukkan nombor dalam kotak *Value* untuk sensor kelembapan tanah, kemudian pilih butang **Set**. Nombor yang anda masukkan akan menjadi nilai yang dikembalikan oleh sensor.

    * Tandakan kotak *Random*, dan masukkan nilai *Min* dan *Max*, kemudian pilih butang **Set**. Setiap kali sensor membaca nilai, ia akan membaca nombor rawak antara *Min* dan *Max*.

1. Jalankan aplikasi Python. Anda akan melihat bacaan kelembapan tanah ditulis ke konsol. Ubah *Value* atau tetapan *Random* untuk melihat perubahan nilai.

    ```output
    (.venv) ➜ soil-moisture-sensor $ python app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

> 💁 Anda boleh menemui kod ini dalam folder [code/virtual-device](../../../../../2-farm/lessons/2-detect-soil-moisture/code/virtual-device).

😀 Program sensor kelembapan tanah anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.