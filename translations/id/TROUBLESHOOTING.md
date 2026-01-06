<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9713e21a309662f6fcb271b573d47848",
  "translation_date": "2026-01-06T10:10:42+00:00",
  "source_file": "TROUBLESHOOTING.md",
  "language_code": "id"
}
-->
# Panduan Pemecahan Masalah

Panduan ini membantu Anda menyelesaikan masalah umum saat bekerja dengan kurikulum IoT for Beginners. Masalah diorganisasi berdasarkan kategori untuk memudahkan navigasi.

## Daftar Isi

- [Masalah Instalasi](../..)
  - [Instalasi Python](../..)
  - [VS Code dan Ekstensi](../..)
  - [PlatformIO (Wio Terminal)](../..)
  - [Perpustakaan Grove](../..)
- [Masalah Perangkat Keras](../..)
  - [Raspberry Pi](../..)
  - [Wio Terminal](../..)
  - [Perangkat Virtual (CounterFit)](../..)
- [Masalah Konektivitas](../..)
  - [Koneksi WiFi](../..)
  - [Layanan Cloud](../..)
  - [MQTT](../..)
- [Masalah Sensor dan Aktuator](../..)
  - [Sensor Grove](../..)
  - [Kamera](../..)
  - [Mikrofon dan Speaker](../..)
- [Masalah Lingkungan Pengembangan](../..)
  - [VS Code](../..)
  - [Virtual Environment Python](../..)
  - [Dependencies](../..)
- [Masalah Performa](../..)
- [Pesan Kesalahan Umum](../..)
- [Mendapatkan Bantuan](../..)

---

## Masalah Instalasi

### Instalasi Python

#### Masalah: Versi Python terlalu lama
**Kesalahan:** `Python 3.6 atau lebih tinggi diperlukan`

**Solusi:**
1. Unduh Python 3 terbaru dari [python.org](https://www.python.org/downloads/)
2. Saat instalasi di Windows, centang "Add Python to PATH"
3. Verifikasi instalasi:
   ```bash
   python3 --version
   ```

#### Masalah: Banyak versi Python menyebabkan konflik
**Gejala:** Versi Python salah berjalan, paket terinstal di lokasi salah

**Solusi:**
- **Windows:** Gunakan `py -3` bukan `python` untuk memanggil Python 3 secara eksplisit
- **macOS/Linux:** Gunakan `python3` bukan `python`
- Selalu buat dan gunakan virtual environment untuk proyek

#### Masalah: Perintah pip tidak ditemukan
**Kesalahan:** `'pip' tidak dikenali sebagai perintah internal atau eksternal`

**Solusi:**
1. Coba `pip3` daripada `pip`
2. Atau gunakan `python -m pip` atau `python3 -m pip`
3. Pastikan Python sudah ditambahkan ke PATH (instal ulang Python dan centang opsi)

### VS Code dan Ekstensi

#### Masalah: Ekstensi Pylance tidak berfungsi
**Gejala:** Tidak ada IntelliSense Python, lengkap kode, atau pengecekan tipe

**Solusi:**
1. Buka Command Palette VS Code (`Ctrl+Shift+P` atau `Cmd+Shift+P`)
2. Jalankan "Python: Select Interpreter"
3. Pilih interpreter Python yang benar (virtual environment jika digunakan)
4. Muat ulang jendela VS Code

#### Masalah: VS Code tidak mendeteksi virtual environment
**Gejala:** Interpreter Python salah dipilih

**Solusi:**
1. Pastikan Anda sudah mengaktifkan virtual environment di terminal
2. Buka Command Palette dan jalankan "Python: Select Interpreter"
3. Pilih interpreter dari folder `.venv`
4. Cek status bar (bawah kiri) menunjukkan versi Python yang benar

### PlatformIO (Wio Terminal)

#### Masalah: Instalasi PlatformIO gagal
**Kesalahan:** Berbagai kesalahan saat instalasi PlatformIO

**Solusi:**
1. Pastikan VS Code sudah diperbarui
2. Instal ekstensi C/C++ terlebih dahulu
3. Restart VS Code setelah instalasi PlatformIO
4. Periksa koneksi internet Anda (PlatformIO mengunduh file besar)

#### Masalah: Board tidak terdeteksi oleh PlatformIO
**Gejala:** Tidak bisa meng-upload kode ke Wio Terminal

**Solusi:**
1. Coba kabel USB lain (beberapa kabel hanya untuk charging)
2. Cek Device Manager (Windows) atau `ls /dev/tty*` (macOS/Linux)
3. Instal atau perbarui driver USB
4. Coba port USB lain
5. Geser saklar daya di Wio Terminal dua kali dengan cepat untuk masuk mode bootloader

#### Masalah: Kesalahan kompilasi di PlatformIO
**Kesalahan:** `fatal error: Arduino.h: No such file or directory`

**Solusi:**
1. Hapus folder `.pio` di proyek Anda
2. Jalankan "PlatformIO: Rebuild" dari Command Palette
3. Pastikan `platformio.ini` punya konfigurasi board yang benar:
   ```ini
   [env:seeed_wio_terminal]
   platform = atmelsam
   board = seeed_wio_terminal
   framework = arduino
   ```

### Perpustakaan Grove

#### Masalah: Import perpustakaan Grove gagal di Raspberry Pi
**Kesalahan:** `ModuleNotFoundError: No module named 'grove'`

**Solusi:**
1. Instal ulang perpustakaan Grove:
   ```bash
   cd ~
   git clone https://github.com/Seeed-Studio/grove.py
   cd grove.py
   sudo pip3 install .
   ```
2. Jika menggunakan virtual environment, mungkin perlu instal secara global atau salin perpustakaan
3. Verifikasi I2C sudah diaktifkan: `sudo raspi-config nonint do_i2c 0`

#### Masalah: Sensor Grove tidak terdeteksi
**Kesalahan:** `IOError: [Errno 121] Remote I/O error`

**Solusi:**
1. Cek koneksi fisik (pastikan kabel Grove terpasang penuh)
2. Pastikan sensor terhubung ke port yang benar (analog, digital, I2C, UART)
3. Jalankan `i2cdetect -y 1` untuk melihat apakah perangkat muncul di bus I2C
4. Coba kabel Grove lain
5. Pastikan Grove Base Hat terpasang dengan benar pada pin GPIO Raspberry Pi

---

## Masalah Perangkat Keras

### Raspberry Pi

#### Masalah: Raspberry Pi tidak menyala
**Gejala:** Tidak ada tampilan, LED tidak menyala, atau layar pelangi

**Solusi:**
1. **Cek power supply:** Gunakan adaptor USB-C resmi 5V 3A untuk Pi 4
2. **Masalah kartu SD:** 
   - Format ulang kartu SD dan instal ulang Raspberry Pi OS
   - Coba kartu SD lain (gunakan merek yang direkomendasikan)
   - Pastikan kartu SD terpasang dengan benar
3. **Periksa koneksi HDMI:** Coba kedua port HDMI di Pi 4, gunakan port HDMI yang terdekat dengan sumber daya

#### Masalah: Tidak bisa SSH ke Raspberry Pi
**Gejala:** Koneksi ditolak atau timeout

**Solusi:**
1. Aktifkan SSH:
   - Ketika flashing kartu SD dengan Raspberry Pi Imager, konfigurasi SSH di opsi lanjutan
   - Atau buat file kosong bernama `ssh` (tanpa ekstensi) di partisi boot
2. Cari alamat IP Pi:
   - Cek perangkat yang terhubung di router Anda
   - Gunakan `ping raspberrypi.local` (jika mDNS aktif)
   - Gunakan alat pemindai jaringan seperti `nmap` atau Angry IP Scanner
3. Periksa jaringan:
   - Pastikan Pi berada di jaringan yang sama dengan komputer Anda
   - Coba koneksi ethernet daripada WiFi
4. Verifikasi username/password (default: username `pi`, password `raspberry`)

#### Masalah: Grove Base Hat tidak dikenali
**Gejala:** Sensor tidak berfungsi, kesalahan I2C

**Solusi:**
1. Pastikan Base Hat terpasang dengan benar di semua pin GPIO
2. Periksa ada tidaknya pin yang bengkok di Pi atau Base Hat
3. Aktifkan interface I2C:
   ```bash
   sudo raspi-config nonint do_i2c 0
   sudo reboot
   ```
4. Verifikasi I2C bekerja: `i2cdetect -y 1`

#### Masalah: Raspberry Pi berjalan lambat
**Gejala:** UI lag, respon lambat

**Solusi:**
1. Periksa kecepatan kartu SD (gunakan Class 10 atau lebih baik, atau SSD via USB)
2. Bebaskan ruang disk: `df -h` untuk cek, hapus file yang tidak perlu
3. Kurangi memori GPU di `raspi-config` jika tidak menggunakan kamera/tampilan berat
4. Tutup aplikasi yang tidak perlu
5. Pertimbangkan upgrade ke Pi 4 dengan lebih banyak RAM jika menggunakan Pi 3 atau lebih lama

### Wio Terminal

#### Masalah: Layar Wio Terminal tetap kosong
**Gejala:** Tidak ada tampilan setelah upload kode

**Solusi:**
1. Cek apakah kode menginisialisasi tampilan (perpustakaan TFT_eSPI)
2. Perbarui firmware Wio Terminal dari [Seeed Wiki](https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/)
3. Tambahkan kode inisialisasi tampilan:
   ```cpp
   #include <TFT_eSPI.h>
   TFT_eSPI tft;
   tft.begin();
   tft.fillScreen(TFT_BLACK);
   ```
4. Coba upload sketsa contoh dari PlatformIO untuk menguji perangkat keras

#### Masalah: WiFi tidak berfungsi di Wio Terminal
**Gejala:** Tidak bisa konek ke WiFi, kesalahan jaringan

**Solusi:**
1. **Perbarui firmware WiFi:** Ikuti panduan pembaruan firmware WiFi [Wio Terminal](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/)
2. **Cek kredensial WiFi:** Pastikan SSID dan password benar
3. **Band WiFi:** Wio Terminal hanya mendukung WiFi 2.4GHz (bukan 5GHz)
4. **Kekuatan sinyal:** Dekatkan perangkat ke router
5. **Pengaturan router:** Beberapa jaringan enterprise/WPA-Enterprise mungkin tidak kompatibel

#### Masalah: Wio Terminal tidak dikenali oleh komputer
**Gejala:** Perangkat USB tidak terdeteksi

**Solusi:**
1. **Coba kabel USB lain:** Gunakan kabel data, bukan kabel hanya untuk charging
2. **Masuk mode bootloader:** Geser saklar daya ke bawah dua kali dengan cepat
   - LED biru akan berkedip, perangkat muncul sebagai "Arduino" di Device Manager
3. **Instal driver (Windows):**
   - Unduh dan instal [driver USB Seeed](https://wiki.seeedstudio.com/Driver_for_Seeeduino/)
4. **Coba port USB lain:** Hindari hub USB, gunakan sambungan langsung
5. **Perbarui driver USB sistem**

#### Masalah: Sensor tidak berfungsi di Wio Terminal
**Gejala:** Sensor Grove tidak membaca data

**Solusi:**
1. Periksa koneksi kabel Grove
2. Pastikan menggunakan port Grove yang benar (kiri atau kanan)
3. Gunakan perpustakaan yang tepat untuk sensor
4. Cek kebutuhan daya sensor
5. Uji sensor dengan contoh kode dari perpustakaan

### Perangkat Virtual (CounterFit)

#### Masalah: Aplikasi CounterFit tidak mau mulai
**Kesalahan:** Berbagai kesalahan Python saat mulai CounterFit

**Solusi:**
1. Pastikan virtual environment sudah diaktifkan
2. Instal ulang CounterFit:
   ```bash
   pip install CounterFit
   ```
3. Periksa port 5000 belum digunakan:
   - Windows: `netstat -ano | findstr :5000`
   - macOS/Linux: `lsof -i :5000`
4. Hentikan proses yang menggunakan port 5000 atau gunakan port berbeda:
   ```bash
   counterfit --port 5001
   ```

#### Masalah: Tidak bisa konek ke CounterFit dari kode
**Kesalahan:** Koneksi ditolak atau timeout

**Solusi:**
1. Verifikasi CounterFit berjalan: Buka browser ke `http://127.0.0.1:5000`
2. Cek URL koneksi di kode sesuai alamat CounterFit
3. Pastikan firewall tidak memblokir koneksi
4. Coba restart aplikasi CounterFit dan kode Anda

#### Masalah: Sensor tidak muncul di CounterFit
**Gejala:** Sensor yang dibuat tidak tampil di UI CounterFit

**Solusi:**
1. Buat sensor di UI CounterFit sebelum menjalankan kode
2. Muat ulang halaman browser
3. Pastikan tipe sensor sesuai dengan yang diharapkan kode
4. Bersihkan cache browser

---

## Masalah Konektivitas

### Koneksi WiFi

#### Masalah: Perangkat tidak bisa konek ke WiFi
**Gejala:** Timeout koneksi, autentikasi gagal

**Solusi:**
1. **Cek SSID dan password:** Pastikan kredensial benar
2. **Band WiFi:** Sebagian besar perangkat IoT hanya mendukung 2.4GHz (bukan 5GHz)
3. **Pengaturan router:**
   - Nonaktifkan AP isolation jika aktif
   - Gunakan keamanan WPA2-PSK (hindari WPA3, WEP, atau jaringan terbuka)
   - Pastikan DHCP aktif
4. **Jaringan tersembunyi:** Jika SSID tersembunyi, Anda mungkin harus konfigurasi eksplisit
5. **Kekuatan sinyal:** Dekatkan perangkat ke router
6. **Gangguan:** Perangkat lain, microwave, atau dinding dapat mengganggu

#### Masalah: Koneksi WiFi sering putus
**Gejala:** Koneksi tidak stabil

**Solusi:**
1. Periksa stabilitas router dan pertimbangkan restart
2. Perbarui firmware perangkat
3. Gunakan IP statis daripada DHCP
4. Kurangi jarak ke router atau tambahkan ekstender WiFi
5. Cek gangguan dari perangkat lain
6. Pastikan pasokan listrik cukup (terutama untuk Raspberry Pi)

### Layanan Cloud

#### Masalah: Tidak bisa konek ke Azure IoT Hub
**Kesalahan:** Autentikasi gagal, koneksi ditolak

**Solusi:**
1. **Verifikasi kredensial:**
   - Periksa string koneksi benar
   - Pastikan tidak ada spasi atau baris baru tambahan di string koneksi
2. **Cek registrasi perangkat:** Perangkat harus terdaftar di IoT Hub
3. **Firewall/proxy:** Pastikan MQTT keluar (port 8883) atau HTTPS (port 443) diperbolehkan
4. **Wilayah IoT Hub:** Pastikan IoT Hub berjalan dan tidak berbeda wilayah sehingga menimbulkan latensi
5. **Batas kuota:** Cek apakah batas tier gratis sudah terlampaui
6. **Tes koneksi:**
   ```bash
   az iot hub device-identity show-connection-string --hub-name YourIoTHub --device-id YourDevice
   ```

#### Masalah: Azure Functions tidak terpanggil
**Gejala:** Pesan dikirim tapi fungsi tidak berjalan

**Solusi:**
1. Pastikan Function App berjalan (tidak berhenti)
2. Verifikasi string koneksi dalam pengaturan Function App
3. Periksa log fungsi di Azure Portal
4. Pastikan endpoint kompatibel Event Hub dikonfigurasi dengan benar
5. Verifikasi format pesan sesuai ekspektasi fungsi
6. Periksa rencana layanan Function App (konsumsi vs dedicated)

### MQTT
#### Masalah: Koneksi MQTT gagal  
**Kesalahan:** Koneksi ditolak, autentikasi gagal

**Solusi:**  
1. **Alamat broker:** Verifikasi URL/IP broker sudah benar  
2. **Port:** Periksa nomor port (1883 untuk tanpa enkripsi, 8883 untuk TLS)  
3. **Autentikasi:** Verifikasi username/password jika diperlukan  
4. **TLS/SSL:** Pastikan sertifikat valid dan terpercaya  
5. **Firewall:** Periksa port tidak diblokir  
6. **Tes dengan klien MQTT:** Gunakan MQTT Explorer atau mosquitto_pub/sub untuk uji coba

#### Masalah: Pesan MQTT tidak diterima  
**Gejala:** Pesan dipublikasikan tapi tidak diterima oleh subscriber

**Solusi:**  
1. **Nama topik:** Verifikasi topik subscriber sama persis dengan topik publisher  
2. **Level QoS:** Coba gunakan QoS 1 atau 2 daripada 0  
3. **Wildcard:** Periksa wildcard topik digunakan dengan benar (`+` untuk satu tingkat, `#` untuk multi-tingkat)  
4. **Pesan yang disimpan:** Publisher dapat mengatur flag retain untuk menyimpan pesan terakhir  
5. **Waktu koneksi:** Pastikan subscriber terkoneksi sebelum pesan dipublikasikan

---

## Masalah Sensor dan Aktuator

### Sensor Grove

#### Masalah: Sensor mengembalikan nilai yang salah  
**Gejala:** Pembacaan 0, -1, atau nilai tidak masuk akal

**Solusi:**  
1. **Periksa koneksi:** Pastikan sensor terhubung dengan benar  
2. **Port benar:** Verifikasi sensor berada di jenis port yang sesuai:  
   - Sensor analog → Port analog (A0, A2, A4)  
   - Sensor digital → Port digital (D5, D16, D18, dll.)  
   - Sensor I2C → Port I2C  
3. **Kalibrasi:** Beberapa sensor perlu kalibrasi (kelembaban tanah, cahaya)  
4. **Power cycle:** Putuskan lalu sambungkan kembali sensor  
5. **Datasheet sensor:** Periksa spesifikasi dan kebutuhan sensor

#### Masalah: Sensor kelembaban tanah kapasitif selalu membaca basah  
**Gejala:** Sensor menunjukkan kelembaban tinggi meskipun kering

**Solusi:**  
1. **Perlu kalibrasi:** Sensor tanah memerlukan kalibrasi:  
   - Baca nilai di udara (baseline kering)  
   - Baca nilai di air (baseline basah)  
   - Petakan pembacaan di antara nilai tersebut  
2. **Periksa lapisan sensor:** Sensor kelembaban bisa rusak jika lapisan pelindungnya tergores  
3. **Penempatan:** Pastikan sensor tertanam penuh di tanah

#### Masalah: Pembacaan sensor suhu/kelembaban salah  
**Gejala:** DHT11/DHT22 menunjukkan suhu atau kelembaban tidak benar

**Solusi:**  
1. **Penempatan sensor:** Hindari sinar matahari langsung, sumber panas, atau aliran udara  
2. **Waktu pemanasan:** Beri sensor 2 detik setelah dinyalakan sebelum membaca  
3. **Frekuensi baca:** Sensor DHT membutuhkan jeda minimal 2 detik antar pembacaan  
4. **Periksa kondensasi:** Dapat memengaruhi pembacaan  
5. **Kualitas sensor:** DHT11 kurang akurat dibandingkan DHT22

### Kamera

#### Masalah: Kamera tidak terdeteksi di Raspberry Pi  
**Kesalahan:** `mmal: mmal_vc_component_create: failed to create component 'vc.ril.camera'`

**Solusi:**  
1. **Aktifkan interface kamera:**  
   ```bash
   sudo raspi-config
   ```
   Pergi ke Interface Options → Camera → Enable  
2. **Periksa kabel pita:** Pastikan kabel kamera terpasang dengan benar  
   - Sisi biru menghadap port USB pada Pi Zero  
   - Sisi biru menghadap menjauh dari port USB pada Pi 4  
3. **Perbarui firmware:**  
   ```bash
   sudo apt update
   sudo apt full-upgrade
   sudo reboot
   ```
4. **Tes kamera:**  
   ```bash
   raspistill -o test.jpg
   ```
  
#### Masalah: Gambar kamera kualitas buruk  
**Gejala:** Gambar buram, gelap, atau pudar  

**Solusi:**  
1. **Fokus:** Lepaskan film pelindung dari lensa, sesuaikan fokus jika bisa diatur  
2. **Pencahayaan:** Pastikan pencahayaan cukup  
3. **Pengaturan kamera:** Sesuaikan eksposur, ISO, white balance di kode  
4. **Stabilitas:** Jaga kamera tetap stabil, gunakan tripod jika perlu  
5. **Resolusi:** Jangan melebihi resolusi maksimal kamera

### Mikrofon dan Speaker

#### Masalah: Tidak ada input/output audio  
**Gejala:** Mikrofon tidak merekam, speaker tidak mengeluarkan suara

**Solusi:**  
1. **Cek koneksi:** Pastikan perangkat audio terhubung dengan benar  
2. **Tes perangkat keras:**  
   - Speaker: `speaker-test -t wav -c 2`  
   - Mikrofon: `arecord -l` untuk daftar, `arecord test.wav` untuk merekam  
3. **Pengaturan volume:** Periksa dan sesuaikan volume:  
   ```bash
   alsamixer
   ```
4. **Pilih perangkat audio:** Tentukan perangkat audio yang benar di kode  
5. **Masalah driver:** Perbarui ALSA atau pasang ulang driver audio

#### Masalah: ReSpeaker hat tidak berfungsi  
**Gejala:** Perangkat audio tidak terdeteksi

**Solusi:**  
1. **Pasang driver:**  
   ```bash
   git clone https://github.com/HinTak/seeed-voicecard
   cd seeed-voicecard
   sudo ./install.sh
   sudo reboot
   ```
2. **Periksa instalasi:** `arecord -l` harus menampilkan ReSpeaker  
3. **Perbarui firmware:** Beberapa versi Pi OS perlu update driver  
4. **Periksa pemasangan:** Pastikan hat terpasang dengan benar pada pin GPIO

---

## Masalah Lingkungan Pengembangan

### VS Code

#### Masalah: Terminal tidak otomatis mengaktifkan virtual environment  
**Gejala:** Terminal terbuka tapi venv tidak aktif

**Solusi:**  
1. **Set interpreter Python:** Command Palette → "Python: Select Interpreter" → Pilih venv  
2. **Restart VS Code** setelah memilih interpreter  
3. **Periksa pengaturan:** Di `settings.json`, tambahkan:  
   ```json
   "python.terminal.activateEnvironment": true
   ```
  
#### Masalah: Kode tidak berjalan di perangkat  
**Gejala:** Kode dijalankan tapi tidak ada efek di perangkat

**Solusi:**  
1. **Pastikan kode tersimpan** (periksa titik di tab file)  
2. **Periksa Python yang berjalan:** `which python` atau `where python`  
3. **Untuk Wio Terminal:** Pastikan kode sudah di-upload via PlatformIO (klik tombol upload)  
4. **Untuk Raspberry Pi:** SSH ke Pi dan jalankan kode di sana  
5. **Periksa output window** untuk melihat kesalahan

#### Masalah: IntelliSense tidak menampilkan fungsi library  
**Gejala:** Tidak ada autocomplete untuk modul yang diimpor

**Solusi:**  
1. Pastikan library terpasang di environment saat ini  
2. Muat ulang jendela VS Code  
3. Periksa interpreter Python yang dipakai sudah benar  
4. Pasang type stub jika tersedia: `pip install types-<nama-library>`

### Virtual Environment Python

#### Masalah: Tidak bisa membuat virtual environment  
**Kesalahan:** `The virtual environment was not created successfully`

**Solusi:**  
1. **Pasang modul venv:**  
   - Ubuntu/Debian: `sudo apt install python3-venv`  
   - macOS: Sudah termasuk dalam Python  
   - Windows: Instal ulang Python dengan semua komponen  
2. **Periksa instalasi Python:** Pastikan Python terpasang dengan benar  
3. **Gunakan path lengkap:** Coba `python3 -m venv .venv` dengan pemanggilan python3 eksplisit

#### Masalah: Paket terpasang di lokasi salah  
**Gejala:** Error impor setelah memasang paket

**Solusi:**  
1. **Pastikan venv aktif:** Prompt harus menunjukkan `(.venv)`  
2. **Periksa lokasi pip:** `which pip` harus menunjuk ke `.venv/bin/pip`  
3. **Pasang ulang di venv:** Aktifkan venv, lalu `pip install <package>`  
4. **Jangan gunakan sudo** dengan pip di virtual environment

#### Masalah: Virtual environment tidak portabel  
**Gejala:** Venv tidak berfungsi setelah dipindah atau di komputer lain

**Solusi:**  
1. **Jangan pindahkan venv:** Hapus dan buat ulang di lokasi baru  
2. **Gunakan requirements.txt:**  
   ```bash
   pip freeze > requirements.txt
   pip install -r requirements.txt
   ```
3. **Buat ulang venv:**  
   ```bash
   python3 -m venv .venv
   source .venv/bin/activate  # atau activate.bat di Windows
   pip install -r requirements.txt
   ```
  
### Dependencies

#### Masalah: Instalasi paket gagal  
**Kesalahan:** Berbagai error pip saat instalasi

**Solusi:**  
1. **Perbarui pip:**  
   ```bash
   pip install --upgrade pip
   ```
2. **Pasang build tools:**  
   - Ubuntu/Debian: `sudo apt install build-essential python3-dev`  
   - macOS: `xcode-select --install`  
   - Windows: Pasang Visual Studio Build Tools  
3. **Periksa koneksi internet**  
4. **Coba indeks paket lain:** `pip install --index-url https://pypi.org/simple/ <package>`  
5. **Pasang versi spesifik:** `pip install <package>==<version>`

#### Masalah: Konflik dependency  
**Kesalahan:** `ERROR: pip's dependency resolver does not currently take into account all the packages that are installed`

**Solusi:**  
1. **Gunakan virtual environment baru** untuk setiap proyek  
2. **Perbarui paket:** `pip install --upgrade <package>`  
3. **Periksa kebutuhan paket:** Gunakan `pip check` untuk menemukan konflik  
4. **Pasang versi yang kompatibel:** Tentukan rentang versi di requirements.txt

---

## Masalah Performa

### Masalah: Kode berjalan lambat  
**Gejala:** Ada delay, timeout, atau tidak responsif

**Solusi:**  
1. **Kurangi frekuensi baca sensor:** Jangan baca sensor terlalu sering  
2. **Optimalkan loop:** Hindari busy-waiting, gunakan sleep() atau delay  
3. **Masalah memori:**  
   - Tutup aplikasi yang tidak perlu  
   - Kosongkan ruang penyimpanan  
   - Pantau dengan `top` atau `htop` di Pi  
4. **Kecepatan kartu SD:** Gunakan kartu SD atau SSD yang lebih cepat untuk Raspberry Pi  
5. **Delay jaringan:** Gunakan operasi async untuk panggilan jaringan

### Masalah: Out of memory  
**Kesalahan:** `MemoryError` atau sistem membeku

**Solusi:**  
1. **Untuk Raspberry Pi:**  
   - Tutup aplikasi yang tidak perlu  
   - Tambah ruang swap  
   - Gunakan OS yang lebih ringan (versi Lite)  
   - Upgrade RAM (Pi 4 punya opsi 2/4/8GB)  
2. **Untuk Wio Terminal:**  
   - Kurangi ukuran buffer  
   - Gunakan gambar lebih kecil  
   - Optimalkan penggunaan string  
   - Periksa kebocoran memori (memori yang tidak dibebaskan)

### Masalah: Kehilangan atau korupsi data  
**Gejala:** Pesan hilang, file rusak

**Solusi:**  
1. **Masalah kartu SD:**  
   - Gunakan kartu SD berkualitas (hindari yang murah/palsu)  
   - Backup secara rutin  
   - Matikan dengan benar (jangan cabut daya tiba-tiba)  
2. **Buffer overflow:** Perbesar buffer di kode  
3. **Keandalan jaringan:** Terapkan logika retry dan penanganan error  
4. **Kualitas Layanan:** Gunakan MQTT QoS 1 atau 2 untuk pesan penting

---

## Pesan Kesalahan Umum

### `ModuleNotFoundError: No module named 'X'`  
**Penyebab:** Paket belum terpasang atau virtual environment tidak aktif

**Solusi:**  
```bash
pip install X
```
Pastikan virtual environment sudah aktif terlebih dahulu.

### `Permission denied` di Linux/macOS  
**Penyebab:** Perlu izin lebih tinggi atau masalah hak akses file

**Solusi:**  
- Untuk operasi sistem: Gunakan `sudo`  
- Untuk pip: JANGAN gunakan sudo dengan venv, aktifkan venv dulu  
- Untuk port serial: Tambahkan user ke grup dialout: `sudo usermod -a -G dialout $USER`, kemudian logout/login

### `OSError: [Errno 98] Address already in use`  
**Penyebab:** Port sudah digunakan oleh proses lain

**Solusi:**  
1. Cari proses yang menggunakan port: `lsof -i :<port>` atau `netstat -ano | findstr :<port>`  
2. Matikan proses atau gunakan port lain di kode Anda

### `SSL: CERTIFICATE_VERIFY_FAILED`  
**Penyebab:** Validasi sertifikat SSL gagal

**Solusi:**  
1. Perbarui sertifikat: `pip install --upgrade certifi`  
2. Periksa waktu sistem sudah benar: `date`  
3. Untuk pengembangan saja (bukan produksi): Nonaktifkan verifikasi di kode

### `IndentationError: unexpected indent`  
**Penyebab:** Masalah indentasi Python (campuran tab/spasi)

**Solusi:**  
1. Gunakan indentasi konsisten (standar Python 4 spasi)  
2. Konfigurasikan editor agar pakai spasi bukan tab  
3. VS Code: Atur `"editor.insertSpaces": true` dan `"editor.tabSize": 4`

### `UnicodeDecodeError` atau `UnicodeEncodeError`  
**Penyebab:** Masalah encoding karakter

**Solusi:**  
```python
# Saat membaca file
with open('file.txt', 'r', encoding='utf-8') as f:
    content = f.read()

# Saat menulis file
with open('file.txt', 'w', encoding='utf-8') as f:
    f.write(content)
```
  
---

## Mendapatkan Bantuan

Jika Anda sudah mencoba langkah troubleshooting ini dan masih mengalami masalah:

### 1. Periksa Sumber yang Ada  
- **Dokumentasi:** Baca [README](README.md) dan instruksi pelajaran  
- **Panduan perangkat keras:** Periksa [hardware.md](hardware.md) untuk info spesifik perangkat keras  
- **Wiki Seeed Studio:** [Seeed Studio Wiki](https://wiki.seeedstudio.com/) untuk komponen Grove

### 2. Cari Masalah Serupa  
- **GitHub Issues:** Cari [issue yang ada](https://github.com/microsoft/IoT-For-Beginners/issues)  
- **Stack Overflow:** Cari pesan kesalahan  
- **Forum perangkat:** Cek forum Raspberry Pi atau Arduino

### 3. Buat Issue GitHub  
Jika tidak menemukan solusi:  
1. Pergi ke [GitHub Issues](https://github.com/microsoft/IoT-For-Beginners/issues)  
2. Klik "New Issue"  
3. Sertakan:  
   - Deskripsi masalah yang jelas  
   - Langkah reproduksi  
   - Pesan error (teks lengkap)  
   - Versi hardware/software  
   - Apa yang sudah dicoba  
   - Screenshot jika relevan

### 4. Bergabung dengan Komunitas  
- **Discord:** [Microsoft Foundry Discord](https://discord.gg/nTYy5BXMWG)  
- **Microsoft Learn:** [Microsoft Learn IoT](https://docs.microsoft.com/learn/browse/?products=azure-iot)

### 5. Berikan Laporan Bug yang Baik  
Laporan bug yang baik mencakup:
- **Lingkungan:** OS, versi Python, perangkat keras yang digunakan  
- **Langkah-langkah untuk mereproduksi:** Langkah tepat yang menyebabkan masalah  
- **Perilaku yang diharapkan:** Apa yang seharusnya terjadi  
- **Perilaku aktual:** Apa yang sebenarnya terjadi  
- **Pesan kesalahan:** Teks kesalahan lengkap, bukan tangkapan layar  
- **Kode:** Contoh kode minimal yang mereproduksi masalah  

---

## Tips untuk Pencegahan

### Praktik Terbaik Umum  
1. **Jaga cadangan:** Cadangan rutin kartu SD/kode yang berfungsi  
2. **Dokumentasikan perubahan:** Catat apa yang berhasil dalam komentar  
3. **Kontrol versi:** Gunakan git untuk melacak perubahan kode  
4. **Uji secara bertahap:** Uji perubahan kecil sebelum menggabungkan  
5. **Baca pesan kesalahan:** Seringkali memberi tahu Anda apa yang salah  
6. **Perbarui secara rutin:** Jaga perangkat lunak/firmware tetap terbaru  
7. **Gunakan komponen berkualitas:** Hindari kabel/pasokan daya murah  
8. **Daya stabil:** Gunakan pasokan daya yang sesuai (terutama Pi)  

### Alur Kerja Pengembangan  
1. **Mulai sederhana:** Mulai dengan kode contoh yang berfungsi  
2. **Satu perubahan dalam satu waktu:** Lebih mudah menemukan yang rusak  
3. **Uji sering:** Tangkap masalah lebih awal  
4. **Jaga kebersihan:** Atur file dan kode secara logis  
5. **Komentari kode:** Anda di masa depan akan menghargainya  

---

*Panduan pemecahan masalah ini dijaga oleh komunitas. Jika Anda menemukan solusi untuk masalah yang tidak tercantum di sini, mohon pertimbangkan untuk [berkontribusi](CONTRIBUTING.md) untuk membantu orang lain!*

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan terjemahan yang akurat, harap diketahui bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang penting, disarankan menggunakan terjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau interpretasi yang salah yang timbul dari penggunaan terjemahan ini.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->