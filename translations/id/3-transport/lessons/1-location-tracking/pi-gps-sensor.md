<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3b2448c7ab4e9673e77e35a50c5e350d",
  "translation_date": "2025-08-27T23:46:31+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/pi-gps-sensor.md",
  "language_code": "id"
}
-->
# Membaca Data GPS - Raspberry Pi

Dalam bagian pelajaran ini, Anda akan menambahkan sensor GPS ke Raspberry Pi dan membaca nilai-nilai darinya.

## Perangkat Keras

Raspberry Pi membutuhkan sensor GPS.

Sensor yang akan Anda gunakan adalah [Grove GPS Air530 sensor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Sensor ini dapat terhubung ke beberapa sistem GPS untuk mendapatkan posisi yang cepat dan akurat. Sensor ini terdiri dari 2 bagian - komponen inti elektronik sensor, dan antena eksternal yang terhubung dengan kabel tipis untuk menangkap gelombang radio dari satelit.

Ini adalah sensor UART, sehingga mengirimkan data GPS melalui UART.

## Menghubungkan Sensor GPS

Sensor GPS Grove dapat dihubungkan ke Raspberry Pi.

### Tugas - Menghubungkan Sensor GPS

Hubungkan sensor GPS.

![Sensor GPS Grove](../../../../../translated_images/id/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.png)

1. Masukkan salah satu ujung kabel Grove ke soket pada sensor GPS. Kabel ini hanya dapat masuk dengan satu arah.

1. Dengan Raspberry Pi dalam keadaan mati, hubungkan ujung lain kabel Grove ke soket UART yang ditandai **UART** pada Grove Base hat yang terpasang di Pi. Soket ini berada di baris tengah, di sisi yang paling dekat dengan slot kartu SD, ujung yang berlawanan dari port USB dan soket ethernet.

    ![Sensor GPS Grove terhubung ke soket UART](../../../../../translated_images/id/pi-gps-sensor.1f99ee2b2f6528915047ec78967bd362e0e4ee0ed594368a3837b9cf9cdaca64.png)

1. Posisikan sensor GPS sehingga antena yang terpasang memiliki visibilitas ke langit - idealnya di dekat jendela yang terbuka atau di luar ruangan. Sinyal akan lebih jelas jika tidak ada penghalang di sekitar antena.

## Memprogram Sensor GPS

Raspberry Pi sekarang dapat diprogram untuk menggunakan sensor GPS yang terpasang.

### Tugas - Memprogram Sensor GPS

Program perangkat.

1. Nyalakan Pi dan tunggu hingga selesai booting.

1. Sensor GPS memiliki 2 LED - LED biru yang berkedip saat data dikirimkan, dan LED hijau yang berkedip setiap detik saat menerima data dari satelit. Pastikan LED biru berkedip saat Anda menyalakan Pi. Setelah beberapa menit, LED hijau akan mulai berkedip - jika tidak, Anda mungkin perlu memposisikan ulang antena.

1. Luncurkan VS Code, baik langsung di Pi, atau sambungkan melalui ekstensi Remote SSH.

    > ⚠️ Anda dapat merujuk ke [instruksi untuk mengatur dan meluncurkan VS Code di pelajaran 1 jika diperlukan](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Dengan versi Raspberry Pi yang lebih baru yang mendukung Bluetooth, terdapat konflik antara port serial yang digunakan untuk Bluetooth dan yang digunakan oleh port Grove UART. Untuk mengatasi ini, lakukan langkah-langkah berikut:

    1. Dari terminal VS Code, edit file `/boot/config.txt` menggunakan `nano`, editor teks bawaan terminal, dengan perintah berikut:

        ```sh
        sudo nano /boot/config.txt
        ```

        > File ini tidak dapat diedit oleh VS Code karena Anda perlu mengeditnya dengan izin `sudo`, yaitu izin yang lebih tinggi. VS Code tidak berjalan dengan izin ini.

    1. Gunakan tombol panah untuk menavigasi ke akhir file, lalu salin kode di bawah ini dan tempelkan di akhir file:

        ```ini
        dtoverlay=pi3-miniuart-bt
        dtoverlay=pi3-disable-bt
        enable_uart=1
        ```

        Anda dapat menempelkan menggunakan pintasan keyboard normal untuk perangkat Anda (`Ctrl+v` di Windows, Linux, atau Raspberry Pi OS, `Cmd+v` di macOS).

    1. Simpan file ini dan keluar dari nano dengan menekan `Ctrl+x`. Tekan `y` saat ditanya apakah Anda ingin menyimpan buffer yang telah dimodifikasi, lalu tekan `enter` untuk mengonfirmasi bahwa Anda ingin menimpa `/boot/config.txt`.

        > Jika Anda membuat kesalahan, Anda dapat keluar tanpa menyimpan, lalu ulangi langkah-langkah ini.

    1. Edit file `/boot/cmdline.txt` di nano dengan perintah berikut:

        ```sh
        sudo nano /boot/cmdline.txt
        ```

    1. File ini memiliki sejumlah pasangan kunci/nilai yang dipisahkan oleh spasi. Hapus pasangan kunci/nilai untuk kunci `console`. Mereka mungkin terlihat seperti ini:

        ```output
        console=serial0,115200 console=tty1 
        ```

        Anda dapat menavigasi ke entri ini menggunakan tombol panah, lalu menghapusnya menggunakan tombol `del` atau `backspace`.

        Sebagai contoh, jika file asli Anda terlihat seperti ini:

        ```output
        console=serial0,115200 console=tty1 root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

        Versi baru akan menjadi:

        ```output
        root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

    1. Ikuti langkah-langkah di atas untuk menyimpan file ini dan keluar dari nano.

    1. Restart Pi Anda, lalu sambungkan kembali di VS Code setelah Pi selesai reboot.

1. Dari terminal, buat folder baru di direktori home pengguna `pi` bernama `gps-sensor`. Buat file di folder ini bernama `app.py`.

1. Buka folder ini di VS Code.

1. Modul GPS mengirimkan data UART melalui port serial. Instal paket Pip `pyserial` untuk berkomunikasi dengan port serial dari kode Python Anda:

    ```sh
    pip3 install pyserial
    ```

1. Tambahkan kode berikut ke file `app.py` Anda:

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

    Kode ini mengimpor modul `serial` dari paket Pip `pyserial`. Kemudian terhubung ke port serial `/dev/ttyAMA0` - ini adalah alamat port serial yang digunakan oleh Grove Pi Base Hat untuk port UART-nya. Kode ini kemudian membersihkan data yang ada dari koneksi serial ini.

    Selanjutnya, sebuah fungsi bernama `print_gps_data` didefinisikan yang mencetak baris yang diteruskan kepadanya ke konsol.

    Kemudian kode ini melakukan loop selamanya, membaca sebanyak mungkin baris teks dari port serial dalam setiap loop. Kode ini memanggil fungsi `print_gps_data` untuk setiap baris.

    Setelah semua data dibaca, loop akan tidur selama 1 detik, lalu mencoba lagi.

1. Jalankan kode ini. Anda akan melihat output mentah dari sensor GPS, sesuatu seperti berikut:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

    > Jika Anda mendapatkan salah satu dari kesalahan berikut saat menghentikan dan memulai ulang kode Anda, tambahkan blok `try - except` ke dalam loop `while` Anda.

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

> 💁 Anda dapat menemukan kode ini di folder [code-gps/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps/pi).

😀 Program sensor GPS Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diperhatikan bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.