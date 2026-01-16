<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3b2448c7ab4e9673e77e35a50c5e350d",
  "translation_date": "2025-08-27T23:46:47+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/pi-gps-sensor.md",
  "language_code": "ms"
}
-->
# Baca Data GPS - Raspberry Pi

Dalam bahagian pelajaran ini, anda akan menambah sensor GPS pada Raspberry Pi anda dan membaca nilai daripadanya.

## Perkakasan

Raspberry Pi memerlukan sensor GPS.

Sensor yang akan anda gunakan ialah [Grove GPS Air530 sensor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Sensor ini boleh berhubung dengan pelbagai sistem GPS untuk mendapatkan lokasi dengan cepat dan tepat. Sensor ini terdiri daripada 2 bahagian - elektronik utama sensor, dan antena luaran yang disambungkan dengan wayar nipis untuk menerima gelombang radio dari satelit.

Ini adalah sensor UART, jadi ia menghantar data GPS melalui UART.

## Sambungkan Sensor GPS

Sensor Grove GPS boleh disambungkan kepada Raspberry Pi.

### Tugasan - sambungkan sensor GPS

Sambungkan sensor GPS.

![Sensor GPS Grove](../../../../../translated_images/ms/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.png)

1. Masukkan satu hujung kabel Grove ke soket pada sensor GPS. Ia hanya boleh dimasukkan dalam satu arah sahaja.

1. Dengan Raspberry Pi dimatikan, sambungkan hujung lain kabel Grove ke soket UART yang ditandakan **UART** pada Grove Base hat yang disambungkan kepada Pi. Soket ini berada di barisan tengah, di sisi yang paling dekat dengan slot kad SD, bertentangan dengan port USB dan soket ethernet.

    ![Sensor GPS Grove disambungkan ke soket UART](../../../../../translated_images/ms/pi-gps-sensor.1f99ee2b2f6528915047ec78967bd362e0e4ee0ed594368a3837b9cf9cdaca64.png)

1. Letakkan sensor GPS supaya antena yang disambungkan mempunyai pandangan ke langit - sebaiknya di sebelah tingkap terbuka atau di luar. Ia lebih mudah untuk mendapatkan isyarat yang jelas tanpa halangan di hadapan antena.

## Program Sensor GPS

Raspberry Pi kini boleh diprogramkan untuk menggunakan sensor GPS yang disambungkan.

### Tugasan - program sensor GPS

Programkan peranti.

1. Hidupkan Pi dan tunggu sehingga ia selesai boot.

1. Sensor GPS mempunyai 2 LED - LED biru yang berkelip apabila data dihantar, dan LED hijau yang berkelip setiap saat apabila menerima data dari satelit. Pastikan LED biru berkelip apabila anda menghidupkan Pi. Selepas beberapa minit, LED hijau akan berkelip - jika tidak, anda mungkin perlu mengubah kedudukan antena.

1. Lancarkan VS Code, sama ada secara langsung pada Pi, atau sambungkan melalui sambungan Remote SSH.

    > ⚠️ Anda boleh merujuk kepada [arahan untuk menyediakan dan melancarkan VS Code dalam pelajaran 1 jika diperlukan](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Dengan versi Raspberry Pi yang lebih baru yang menyokong Bluetooth, terdapat konflik antara port serial yang digunakan untuk Bluetooth dan yang digunakan oleh port Grove UART. Untuk menyelesaikan masalah ini, lakukan langkah berikut:

    1. Dari terminal VS Code, edit fail `/boot/config.txt` menggunakan `nano`, editor teks terminal terbina dalam dengan arahan berikut:

        ```sh
        sudo nano /boot/config.txt
        ```

        > Fail ini tidak boleh diedit oleh VS Code kerana anda perlu mengeditnya dengan kebenaran `sudo`, iaitu kebenaran yang lebih tinggi. VS Code tidak dijalankan dengan kebenaran ini.

    1. Gunakan kekunci kursor untuk navigasi ke penghujung fail, kemudian salin kod di bawah dan tampal di penghujung fail:

        ```ini
        dtoverlay=pi3-miniuart-bt
        dtoverlay=pi3-disable-bt
        enable_uart=1
        ```

        Anda boleh menampal menggunakan pintasan papan kekunci biasa untuk peranti anda (`Ctrl+v` pada Windows, Linux atau Raspberry Pi OS, `Cmd+v` pada macOS).

    1. Simpan fail ini dan keluar dari nano dengan menekan `Ctrl+x`. Tekan `y` apabila ditanya sama ada anda ingin menyimpan buffer yang diubah, kemudian tekan `enter` untuk mengesahkan anda ingin menimpa `/boot/config.txt`.

        > Jika anda membuat kesilapan, anda boleh keluar tanpa menyimpan, kemudian ulangi langkah-langkah ini.

    1. Edit fail `/boot/cmdline.txt` dalam nano dengan arahan berikut:

        ```sh
        sudo nano /boot/cmdline.txt
        ```

    1. Fail ini mempunyai beberapa pasangan kunci/nilai yang dipisahkan oleh ruang. Padamkan mana-mana pasangan kunci/nilai untuk kunci `console`. Ia mungkin kelihatan seperti ini:

        ```output
        console=serial0,115200 console=tty1 
        ```

        Anda boleh navigasi ke entri ini menggunakan kekunci kursor, kemudian padam menggunakan kekunci `del` atau `backspace` biasa.

        Sebagai contoh, jika fail asal anda kelihatan seperti ini:

        ```output
        console=serial0,115200 console=tty1 root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

        Versi baru akan menjadi:

        ```output
        root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

    1. Ikuti langkah-langkah di atas untuk menyimpan fail ini dan keluar dari nano.

    1. Reboot Pi anda, kemudian sambung semula dalam VS Code selepas Pi selesai reboot.

1. Dari terminal, buat folder baru dalam direktori rumah pengguna `pi` bernama `gps-sensor`. Buat fail dalam folder ini bernama `app.py`.

1. Buka folder ini dalam VS Code.

1. Modul GPS menghantar data UART melalui port serial. Pasang pakej Pip `pyserial` untuk berkomunikasi dengan port serial dari kod Python anda:

    ```sh
    pip3 install pyserial
    ```

1. Tambahkan kod berikut ke fail `app.py` anda:

    ```python
    import time
    import serial
    
    serial = serial.Serial('/dev/ttyAMA0', 9600, timeout=1)
    serial.reset_input_buffer()
    serial.flush()
    
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    Kod ini mengimport modul `serial` dari pakej Pip `pyserial`. Ia kemudian menyambung ke port serial `/dev/ttyAMA0` - ini adalah alamat port serial yang digunakan oleh Grove Pi Base Hat untuk port UART-nya. Ia kemudian membersihkan sebarang data sedia ada dari sambungan serial ini.

    Seterusnya, fungsi bernama `print_gps_data` ditakrifkan yang mencetak baris yang dihantar kepadanya ke konsol.

    Seterusnya, kod ini melaksanakan gelung selama-lamanya, membaca sebanyak mungkin baris teks dari port serial dalam setiap gelung. Ia memanggil fungsi `print_gps_data` untuk setiap baris.

    Selepas semua data dibaca, gelung ini tidur selama 1 saat, kemudian mencuba lagi.

1. Jalankan kod ini. Anda akan melihat output mentah dari sensor GPS, sesuatu seperti berikut:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

    > Jika anda mendapat salah satu daripada ralat berikut apabila menghentikan dan memulakan semula kod anda, tambahkan blok `try - except` ke gelung `while` anda.

      ```output
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0x93 in position 0: invalid start byte
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0xf1 in position 0: invalid continuation byte
      ```

    ```python
    while True:
        try:
            line = serial.readline().decode('utf-8')
              
            while len(line) > 0:
                print_gps_data()
                line = serial.readline().decode('utf-8')
      
        # There's a random chance the first byte being read is part way through a character.
        # Read another full line and continue.

        except UnicodeDecodeError:
            line = serial.readline().decode('utf-8')

    time.sleep(1)
    ```

> 💁 Anda boleh menemui kod ini dalam folder [code-gps/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps/pi).

😀 Program sensor GPS anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat yang kritikal, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.