<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ea733bd0cdf2479e082373f765a08678",
  "translation_date": "2025-08-27T22:24:40+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-sensor.md",
  "language_code": "ms"
}
-->
# Bina Lampu Malam - Raspberry Pi

Dalam bahagian pelajaran ini, anda akan menambah sensor cahaya pada Raspberry Pi anda.

## Perkakasan

Sensor untuk pelajaran ini ialah **sensor cahaya** yang menggunakan [fotodiod](https://wikipedia.org/wiki/Photodiode) untuk menukar cahaya kepada isyarat elektrik. Ini adalah sensor analog yang menghantar nilai integer dari 0 hingga 1,000 yang menunjukkan jumlah cahaya relatif yang tidak memetakan kepada sebarang unit ukuran standard seperti [lux](https://wikipedia.org/wiki/Lux).

Sensor cahaya ini adalah sensor Grove luaran dan perlu disambungkan ke Grove Base hat pada Raspberry Pi.

### Sambungkan sensor cahaya

Sensor cahaya Grove yang digunakan untuk mengesan tahap cahaya perlu disambungkan ke Raspberry Pi.

#### Tugasan - sambungkan sensor cahaya

Sambungkan sensor cahaya

![Sensor cahaya Grove](../../../../../translated_images/ms/grove-light-sensor.b8127b7c434e632d6bcdb57587a14e9ef69a268a22df95d08628f62b8fa5505c.png)

1. Masukkan satu hujung kabel Grove ke soket pada modul sensor cahaya. Ia hanya boleh dimasukkan dalam satu arah sahaja.

1. Dengan Raspberry Pi dimatikan, sambungkan hujung lain kabel Grove ke soket analog yang ditandakan **A0** pada Grove Base hat yang disambungkan ke Pi. Soket ini adalah yang kedua dari kanan, pada barisan soket bersebelahan pin GPIO.

![Sensor cahaya Grove disambungkan ke soket A0](../../../../../translated_images/ms/pi-light-sensor.66cc1e31fa48cd7d5f23400d4b2119aa41508275cb7c778053a7923b4e972d7e.png)

## Programkan sensor cahaya

Peranti kini boleh diprogramkan menggunakan sensor cahaya Grove.

### Tugasan - programkan sensor cahaya

Programkan peranti.

1. Hidupkan Pi dan tunggu sehingga ia selesai boot.

1. Buka projek lampu malam dalam VS Code yang anda cipta dalam bahagian tugasan sebelum ini, sama ada dijalankan terus pada Pi atau disambungkan menggunakan sambungan Remote SSH.

1. Buka fail `app.py` dan keluarkan semua kod daripadanya.

1. Tambahkan kod berikut ke dalam fail `app.py` untuk mengimport beberapa pustaka yang diperlukan:

    ```python
    import time
    from grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    Pernyataan `import time` mengimport modul `time` yang akan digunakan kemudian dalam tugasan ini.

    Pernyataan `from grove.grove_light_sensor_v1_2 import GroveLightSensor` mengimport `GroveLightSensor` daripada pustaka Python Grove. Pustaka ini mengandungi kod untuk berinteraksi dengan sensor cahaya Grove, dan telah dipasang secara global semasa penyediaan Pi.

1. Tambahkan kod berikut selepas kod di atas untuk mencipta satu instance kelas yang menguruskan sensor cahaya:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    Baris `light_sensor = GroveLightSensor(0)` mencipta satu instance kelas `GroveLightSensor` yang disambungkan ke pin **A0** - pin analog Grove yang disambungkan kepada sensor cahaya.

1. Tambahkan gelung tak terhingga selepas kod di atas untuk membaca nilai sensor cahaya dan mencetaknya ke konsol:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Ini akan membaca tahap cahaya semasa pada skala 0-1,023 menggunakan sifat `light` daripada kelas `GroveLightSensor`. Sifat ini membaca nilai analog daripada pin. Nilai ini kemudian dicetak ke konsol.

1. Tambahkan jeda kecil selama satu saat di akhir `loop` kerana tahap cahaya tidak perlu diperiksa secara berterusan. Jeda ini mengurangkan penggunaan kuasa peranti.

    ```python
    time.sleep(1)
    ```

1. Dari Terminal VS Code, jalankan arahan berikut untuk menjalankan aplikasi Python anda:

    ```sh
    python3 app.py
    ```

    Nilai cahaya akan dipaparkan di konsol. Tutup dan buka sensor cahaya, dan nilai akan berubah:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

> 💁 Anda boleh menemui kod ini dalam folder [code-sensor/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/pi).

😀 Menambah sensor pada program lampu malam anda adalah satu kejayaan!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.