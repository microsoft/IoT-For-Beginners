<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9713e21a309662f6fcb271b573d47848",
  "translation_date": "2026-01-06T10:12:24+00:00",
  "source_file": "TROUBLESHOOTING.md",
  "language_code": "ms"
}
-->
# Panduan Penyelesaian Masalah

Panduan ini membantu anda menyelesaikan masalah biasa apabila bekerja dengan kurikulum IoT untuk Pemula. Isu diatur mengikut kategori untuk navigasi yang mudah.

## Jadual Kandungan

- [Isu Pemasangan](../..)
  - [Pemasangan Python](../..)
  - [VS Code dan Sambungan](../..)
  - [PlatformIO (Wio Terminal)](../..)
  - [Perpustakaan Grove](../..)
- [Isu Perkakasan](../..)
  - [Raspberry Pi](../..)
  - [Wio Terminal](../..)
  - [Peranti Maya (CounterFit)](../..)
- [Isu Kesambungan](../..)
  - [Sambungan WiFi](../..)
  - [Perkhidmatan Awan](../..)
  - [MQTT](../..)
- [Isu Sensor dan Penggerak](../..)
  - [Sensor Grove](../..)
  - [Kamera](../..)
  - [Mikrofon dan Pembesar Suara](../..)
- [Isu Persekitaran Pembangunan](../..)
  - [VS Code](../..)
  - [Persekitaran Maya Python](../..)
  - [Kebergantungan](../..)
- [Isu Prestasi](../..)
- [Mesej Ralat Biasa](../..)
- [Mendapatkan Bantuan](../..)

---

## Isu Pemasangan

### Pemasangan Python

#### Masalah: Versi Python terlalu lama
**Ralat:** `Python 3.6 atau lebih tinggi diperlukan`

**Penyelesaian:**
1. Muat turun Python 3 terkini dari [python.org](https://www.python.org/downloads/)
2. Semasa pemasangan di Windows, tandakan "Add Python to PATH"
3. Sahkan pemasangan:
   ```bash
   python3 --version
   ```

#### Masalah: Pelbagai versi Python menyebabkan konflik
**Gejala:** Versi Python salah dijalankan, pakej dipasang ke lokasi yang salah

**Penyelesaian:**
- **Windows:** Gunakan `py -3` dan bukan `python` untuk panggil Python 3 secara jelas
- **macOS/Linux:** Gunakan `python3` dan bukan `python`
- Sentiasa cipta dan gunakan persekitaran maya untuk projek

#### Masalah: arahan pip tidak ditemui
**Ralat:** `'pip' tidak dikenali sebagai arahan dalaman atau luaran`

**Penyelesaian:**
1. Cuba `pip3` dan bukan `pip`
2. Atau gunakan `python -m pip` atau `python3 -m pip`
3. Pastikan Python ditambah ke PATH (pasang semula Python dan tandakan opsyen ini)

### VS Code dan Sambungan

#### Masalah: Sambungan Pylance tidak berfungsi
**Gejala:** Tiada IntelliSense Python, lengkapkan kod, atau semakan jenis

**Penyelesaian:**
1. Buka Command Palette VS Code (`Ctrl+Shift+P` atau `Cmd+Shift+P`)
2. Jalankan "Python: Select Interpreter"
3. Pilih interpreter Python yang betul (persekitaran maya jika digunakan)
4. Muat semula tetingkap VS Code

#### Masalah: VS Code tidak mengesan persekitaran maya
**Gejala:** Interpreter Python salah dipilih

**Penyelesaian:**
1. Pastikan anda telah mengaktifkan persekitaran maya dalam terminal
2. Buka Command Palette dan jalankan "Python: Select Interpreter"
3. Pilih interpreter dari folder `.venv`
4. Semak bar status (bawah kiri) menunjukkan versi Python yang betul

### PlatformIO (Wio Terminal)

#### Masalah: Pemasangan PlatformIO gagal
**Ralat:** Pelbagai ralat semasa pemasangan PlatformIO

**Penyelesaian:**
1. Pastikan VS Code dikemas kini
2. Pasang sambungan C/C++ terlebih dahulu
3. Mulakan semula VS Code selepas memasang PlatformIO
4. Semak sambungan internet anda (PlatformIO memuat turun fail besar)

#### Masalah: Papan tidak dikesan oleh PlatformIO
**Gejala:** Tidak boleh memuat naik kod ke Wio Terminal

**Penyelesaian:**
1. Cuba kabel USB yang lain (sesetengah kabel hanya untuk pengecasan)
2. Semak Pengurus Peranti (Windows) atau `ls /dev/tty*` (macOS/Linux)
3. Pasang atau kemas kini pemacu USB
4. Cuba port USB yang lain
5. Luncurkan suis kuasa pada Wio Terminal dua kali dengan cepat untuk masuk ke mod bootloader

#### Masalah: Ralat penyusunan dalam PlatformIO
**Ralat:** `fatal error: Arduino.h: No such file or directory`

**Penyelesaian:**
1. Padam folder `.pio` dalam projek anda
2. Jalankan "PlatformIO: Rebuild" dari Command Palette
3. Pastikan `platformio.ini` mempunyai konfigurasi papan yang betul:
   ```ini
   [env:seeed_wio_terminal]
   platform = atmelsam
   board = seeed_wio_terminal
   framework = arduino
   ```

### Perpustakaan Grove

#### Masalah: Import perpustakaan Grove gagal pada Raspberry Pi
**Ralat:** `ModuleNotFoundError: No module named 'grove'`

**Penyelesaian:**
1. Pasang semula perpustakaan Grove:
   ```bash
   cd ~
   git clone https://github.com/Seeed-Studio/grove.py
   cd grove.py
   sudo pip3 install .
   ```
2. Jika menggunakan persekitaran maya, anda mungkin perlu pasang secara global atau salin perpustakaan
3. Sahkan I2C diaktifkan: `sudo raspi-config nonint do_i2c 0`

#### Masalah: Sensor Grove tidak dikesan
**Ralat:** `IOError: [Errno 121] Remote I/O error`

**Penyelesaian:**
1. Periksa sambungan fizikal (pastikan kabel Grove dimasukkan sepenuhnya)
2. Sahkan sensor disambungkan ke port yang betul (analog, digital, I2C, UART)
3. Jalankan `i2cdetect -y 1` untuk melihat jika peranti muncul di bas I2C
4. Cuba kabel Grove yang lain
5. Pastikan Grove Base Hat duduk dengan betul pada pin GPIO Raspberry Pi

---

## Isu Perkakasan

### Raspberry Pi

#### Masalah: Raspberry Pi tidak hendak boot
**Gejala:** Tiada paparan, tiada aktiviti LED, atau skrin pelangi

**Penyelesaian:**
1. **Semak bekalan kuasa:** Gunakan bekalan kuasa USB-C rasmi 5V 3A untuk Pi 4
2. **Isu kad SD:** 
   - Format semula kad SD dan pasang semula Raspberry Pi OS
   - Cuba kad SD lain (guna jenama yang disyorkan)
   - Pastikan kad SD dimasukkan dengan betul
3. **Semak sambungan HDMI:** Cuba kedua-dua port HDMI pada Pi 4, guna port HDMI yang paling hampir dengan kuasa

#### Masalah: Tidak boleh SSH ke Raspberry Pi
**Gejala:** Sambungan ditolak atau tamat masa

**Penyelesaian:**
1. Aktifkan SSH:
   - Apabila membakar kad SD dengan Raspberry Pi Imager, konfigurasikan SSH dalam opsyen lanjutan
   - Atau cipta fail kosong bernama `ssh` (tiada sambungan) dalam partition boot
2. Cari alamat IP Pi:
   - Semak peranti yang bersambung pada penghala anda
   - Gunakan `ping raspberrypi.local` (jika mDNS berfungsi)
   - Gunakan alat imbasan rangkaian seperti `nmap` atau Angry IP Scanner
3. Semak rangkaian:
   - Pastikan Pi berada dalam rangkaian yang sama dengan komputer anda
   - Cuba sambungan ethernet dan bukannya WiFi
4. Sahkan nama pengguna/katalaluan (lalai: nama pengguna `pi`, kata laluan `raspberry`)

#### Masalah: Grove Base Hat tidak dikenali
**Gejala:** Sensor tidak berfungsi, ralat I2C

**Penyelesaian:**
1. Pastikan Base Hat duduk dengan betul pada semua pin GPIO
2. Periksa pin bengkok pada Pi atau Base Hat
3. Aktifkan antara muka I2C:
   ```bash
   sudo raspi-config nonint do_i2c 0
   sudo reboot
   ```
4. Sahkan I2C berfungsi: `i2cdetect -y 1`

#### Masalah: Raspberry Pi berjalan perlahan
**Gejala:** Antara muka lambat, tindak balas perlahan

**Penyelesaian:**
1. Semak kelajuan kad SD (guna Kelas 10 atau lebih baik, atau SSD melalui USB)
2. Kosongkan ruang cakera: `df -h` untuk semak, padam fail yang tidak perlu
3. Kurangkan memori GPU dalam `raspi-config` jika tidak menggunakan kamera/paparan secara berat
4. Tutup aplikasi yang tidak perlu
5. Pertimbangkan menaik taraf ke Pi 4 dengan RAM lebih banyak jika menggunakan Pi 3 atau lebih lama

### Wio Terminal

#### Masalah: Skrin Wio Terminal kekal kosong
**Gejala:** Tiada paparan keluar selepas memuat naik kod

**Penyelesaian:**
1. Semak jika kod menginisialisasi paparan (perpustakaan TFT_eSPI)
2. Kemas kini firmware Wio Terminal dari [Seeed Wiki](https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/)
3. Tambah kod inisialisasi paparan:
   ```cpp
   #include <TFT_eSPI.h>
   TFT_eSPI tft;
   tft.begin();
   tft.fillScreen(TFT_BLACK);
   ```
4. Cuba muat naik lakaran contoh dari PlatformIO untuk uji perkakasan

#### Masalah: WiFi tidak berfungsi pada Wio Terminal
**Gejala:** Tidak boleh sambung ke WiFi, ralat rangkaian

**Penyelesaian:**
1. **Kemas kini firmware WiFi:** Ikuti [panduan kemas kini firmware WiFi Wio Terminal](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/)
2. **Semak kelayakan WiFi:** Pastikan SSID dan kata laluan betul
3. **Band WiFi:** Wio Terminal hanya menyokong WiFi 2.4GHz (bukan 5GHz)
4. **Kekuatan isyarat:** Dekatkan peranti ke penghala
5. **Tetapan penghala:** Sesetengah rangkaian enterprise/WPA-Enterprise mungkin tidak berfungsi

#### Masalah: Wio Terminal tidak dikenali oleh komputer
**Gejala:** Peranti USB tidak dikesan

**Penyelesaian:**
1. **Cuba kabel USB lain:** Guna kabel data, bukan kabel cuma untuk pengecasan
2. **Masuk mod bootloader:** Luncurkan suis kuasa ke bawah dua kali dengan cepat
   - LED biru akan berdenyut, peranti muncul sebagai "Arduino" dalam Pengurus Peranti
3. **Pasang pemacu (Windows):**
   - Muat turun dan pasang [pemacu USB Seeed](https://wiki.seeedstudio.com/Driver_for_Seeeduino/)
4. **Cuba port USB lain:** Elak hab USB, guna sambungan terus
5. **Kemas kini pemacu USB sistem**

#### Masalah: Sensor tidak berfungsi pada Wio Terminal
**Gejala:** Sensor Grove tidak membaca data

**Penyelesaian:**
1. Semak sambungan kabel Grove
2. Sahkan anda menggunakan port Grove yang betul (kiri atau kanan)
3. Sertakan perpustakaan yang betul untuk sensor
4. Semak keperluan kuasa sensor
5. Uji sensor dengan contoh kod dari perpustakaan

### Peranti Maya (CounterFit)

#### Masalah: Aplikasi CounterFit tidak hendak bermula
**Ralat:** Pelbagai ralat Python semasa mula CounterFit

**Penyelesaian:**
1. Pastikan persekitaran maya diaktifkan
2. Pasang semula CounterFit:
   ```bash
   pip install CounterFit
   ```
3. Semak port 5000 tidak sedang digunakan:
   - Windows: `netstat -ano | findstr :5000`
   - macOS/Linux: `lsof -i :5000`
4. Bunuh proses yang menggunakan port 5000 atau guna port berbeza:
   ```bash
   counterfit --port 5001
   ```

#### Masalah: Tidak boleh sambung ke CounterFit dari kod
**Ralat:** Sambungan ditolak atau tamat masa

**Penyelesaian:**
1. Sahkan CounterFit berjalan: Buka pelayar ke `http://127.0.0.1:5000`
2. Semak URL sambungan dalam kod sepadan dengan alamat CounterFit
3. Pastikan firewall tidak menghalang sambungan
4. Cuba mulakan semula kedua-dua aplikasi CounterFit dan kod anda

#### Masalah: Sensor tidak muncul dalam CounterFit
**Gejala:** Sensor yang dicipta tidak muncul dalam UI CounterFit

**Penyelesaian:**
1. Cipta sensor dalam UI CounterFit sebelum menjalankan kod
2. Segarkan halaman pelayar
3. Semak jenis sensor sepadan dengan apa yang kod jangka
4. Kosongkan cache pelayar

---

## Isu Kesambungan

### Sambungan WiFi

#### Masalah: Peranti tidak boleh sambung ke WiFi
**Gejala:** Sambungan tamat masa, pengesahan gagal

**Penyelesaian:**
1. **Semak SSID dan kata laluan:** Sahkan kelayakan betul
2. **Band WiFi:** Kebanyakan peranti IoT hanya menyokong 2.4GHz (bukan 5GHz)
3. **Tetapan penghala:**
   - Lumpuhkan AP isolation jika diaktifkan
   - Gunakan keselamatan WPA2-PSK (elak WPA3, WEP, atau rangkaian terbuka)
   - Pastikan DHCP diaktifkan
4. **Rangkaian tersembunyi:** Jika SSID tersembunyi, anda mungkin perlu konfigurasikan secara jelas
5. **Kekuatan isyarat:** Letakkan peranti lebih dekat ke penghala
6. **Gangguan:** Peranti lain, gelombang mikro, atau dinding boleh mengganggu

#### Masalah: Sambungan WiFi sering putus
**Gejala:** Sambungan berselang

**Penyelesaian:**
1. Semak kestabilan penghala dan pertimbangkan untuk mulakan semula
2. Kemas kini firmware peranti
3. Gunakan IP statik dan bukan DHCP
4. Kurangkan jarak ke penghala atau tambah pengulang WiFi
5. Semak gangguan daripada peranti lain
6. Sahkan bekalan kuasa mencukupi (terutamanya untuk Raspberry Pi)

### Perkhidmatan Awan

#### Masalah: Tidak boleh sambung ke Azure IoT Hub
**Ralat:** Pengesahan gagal, sambungan ditolak

**Penyelesaian:**
1. **Sahkan kelayakan:**
   - Semak rentetan sambungan betul
   - Pastikan tiada ruang atau baris tambahan dalam rentetan sambungan
2. **Semak pendaftaran peranti:** Peranti mesti didaftarkan di IoT Hub
3. **Firewall/proksi:** Pastikan MQTT keluar (port 8883) atau HTTPS (port 443) dibenarkan
4. **Wilayah IoT Hub:** Pastikan IoT Hub beroperasi dan bukan di wilayah berlainan yang menyebabkan kelewatan
5. **Had kuota:** Semak jika had tier percuma terlampaui
6. **Uji sambungan:**
   ```bash
   az iot hub device-identity show-connection-string --hub-name YourIoTHub --device-id YourDevice
   ```

#### Masalah: Azure Functions tidak mencetuskan
**Gejala:** Mesej dihantar tetapi fungsi tidak dijalankan

**Penyelesaian:**
1. Semak Function App berjalan (tidak dihentikan)
2. Sahkan rentetan sambungan dalam tetapan Function App
3. Semak log fungsi dalam Portal Azure
4. Pastikan titik hujung serasi Event Hub dikonfigurasikan dengan betul
5. Sahkan format mesej sepadan dengan jangkaan fungsi
6. Semak pelan perkhidmatan Function App (penggunaan berbanding khusus)

### MQTT
#### Masalah: Sambungan MQTT gagal
**Ralat:** Sambungan ditolak, pengesahan gagal

**Penyelesaian:**
1. **Alamat broker:** Sahkan URL/IP broker adalah betul
2. **Port:** Semak nombor port (1883 untuk tanpa penyulitan, 8883 untuk TLS)
3. **Pengesahan:** Sahkan nama pengguna/katalaluan jika diperlukan
4. **TLS/SSL:** Pastikan sijil adalah sah dan dipercayai
5. **Firewall:** Semak port tidak disekat
6. **Uji dengan klien MQTT:** Gunakan MQTT Explorer atau mosquitto_pub/sub untuk menguji

#### Masalah: Mesej MQTT tidak diterima
**Gejala:** Mesej diterbitkan tetapi tidak diterima oleh pelanggan

**Penyelesaian:**
1. **Nama topik:** Sahkan topik pelanggan sepadan dengan topik penerbit dengan tepat
2. **Tahap QoS:** Cuba QoS 1 atau 2 daripada 0
3. **Wildcard:** Semak wildcard topik digunakan dengan betul (`+` untuk satu tingkat, `#` untuk berbilang tingkat)
4. **Mesej yang disimpan:** Penerbit boleh menetapkan bendera simpan untuk menyimpan mesej terakhir
5. **Masa sambungan:** Pastikan pelanggan menyambung sebelum mesej diterbitkan

---

## Isu Sensor dan Penggerak

### Sensor Grove

#### Masalah: Sensor mengembalikan nilai tidak betul
**Gejala:** Bacaan adalah 0, -1, atau nilai tidak masuk akal

**Penyelesaian:**
1. **Periksa sambungan:** Pastikan sensor bersambung dengan betul
2. **Port betul:** Sahkan sensor pada jenis port yang betul:
   - Sensor analog → Port analog (A0, A2, A4)
   - Sensor digital → Port digital (D5, D16, D18, dll.)
   - Sensor I2C → Port I2C
3. **Penentukuran:** Sesetengah sensor perlu ditentukur (kelembapan tanah, cahaya)
4. **Kitar kuasa:** Putus dan sambung semula sensor
5. **Datasheet sensor:** Periksa spesifikasi dan keperluan sensor

#### Masalah: Sensor kelembapan tanah kapasitif sentiasa membaca basah
**Gejala:** Sensor membaca kelembapan tinggi walaupun kering

**Penyelesaian:**
1. **Perlu penentukuran:** Sensor tanah perlu ditentukur:
   - Baca nilai di udara (garis asas kering)
   - Baca nilai di air (garis asas basah)
   - Peta bacaan antara nilai ini
2. **Periksa lapisan sensor:** Sensor kelembapan mungkin rosak jika lapisan terjejas
3. **Penempatan:** Pastikan sensor dimasukkan sepenuhnya ke dalam tanah

#### Masalah: Bacaan sensor suhu/kelembapan tidak betul
**Gejala:** DHT11/DHT22 menunjukkan suhu atau kelembapan salah

**Penyelesaian:**
1. **Penempatan sensor:** Elakkan cahaya matahari langsung, sumber haba, atau aliran udara
2. **Masa pemanasan:** Beri sensor 2 saat selepas dihidupkan sebelum membaca
3. **Kekerapan bacaan:** Sensor DHT memerlukan masa antara bacaan (sekurang-kurangnya 2 saat)
4. **Periksa kondensasi:** Boleh menjejaskan bacaan
5. **Kualiti sensor:** DHT11 kurang tepat berbanding DHT22

### Kamera

#### Masalah: Kamera tidak dikesan pada Raspberry Pi
**Ralat:** `mmal: mmal_vc_component_create: failed to create component 'vc.ril.camera'`

**Penyelesaian:**
1. **Dayakan antara muka kamera:**
   ```bash
   sudo raspi-config
   ```
   Pergi ke Interface Options → Camera → Enable
2. **Periksa kabel reben:** Pastikan kabel kamera dimasukkan dengan betul
   - Bahagian biru menghadap port USB pada Pi Zero
   - Bahagian biru menghadap arah bertentangan dengan port USB pada Pi 4
3. **Kemas kini firmware:**
   ```bash
   sudo apt update
   sudo apt full-upgrade
   sudo reboot
   ```
4. **Uji kamera:**
   ```bash
   raspistill -o test.jpg
   ```

#### Masalah: Gambar kamera kualiti rendah
**Gejala:** Gambar kabur, gelap, atau pudar

**Penyelesaian:**
1. **Fokus:** Tanggalkan filem pelindung dari lensa, laraskan fokus jika boleh
2. **Pencahayaan:** Pastikan pencahayaan mencukupi
3. **Tetapan kamera:** Laraskan pendedahan, ISO, imbangan putih dalam kod
4. **Kestabilan:** Kekalkan kamera stabil, guna tripod jika perlu
5. **Resolusi:** Jangan lebihkan resolusi maksimum kamera

### Mikrofon dan Pembesar Suara

#### Masalah: Tiada input/output audio
**Gejala:** Mikrofon tidak merakam, pembesar suara tidak mengeluarkan bunyi

**Penyelesaian:**
1. **Periksa sambungan:** Pastikan peranti audio disambung dengan betul
2. **Uji perkakasan:**
   - Pembesar suara: `speaker-test -t wav -c 2`
   - Mikrofon: `arecord -l` untuk senarai, `arecord test.wav` untuk rakam
3. **Tetapan kelantangan:** Semak dan laraskan kelantangan:
   ```bash
   alsamixer
   ```
4. **Pilih peranti audio:** Tentukan peranti audio betul dalam kod
5. **Isu pemacu:** Kemas kini ALSA atau pasang semula pemacu audio

#### Masalah: ReSpeaker hat tidak berfungsi
**Gejala:** Peranti audio tidak dikesan

**Penyelesaian:**
1. **Pasang pemacu:**
   ```bash
   git clone https://github.com/HinTak/seeed-voicecard
   cd seeed-voicecard
   sudo ./install.sh
   sudo reboot
   ```
2. **Periksa pemasangan:** `arecord -l` harus menunjukkan ReSpeaker
3. **Kemas kini firmware:** Sesetengah versi Pi OS memerlukan kemas kini pemacu
4. **Periksa pemasangan:** Pastikan hat dipasang dengan betul ke pin GPIO

---

## Isu Persekitaran Pembangunan

### VS Code

#### Masalah: Terminal tidak mengaktifkan persekitaran maya secara automatik
**Gejala:** Terminal dibuka tetapi venv tidak diaktifkan

**Penyelesaian:**
1. **Tetapkan interpreter Python:** Command Palette → "Python: Select Interpreter" → Pilih venv
2. **Mulakan semula VS Code** selepas memilih interpreter
3. **Periksa tetapan:** Dalam `settings.json`, tambah:
   ```json
   "python.terminal.activateEnvironment": true
   ```

#### Masalah: Kod tidak berjalan pada peranti
**Gejala:** Kod berjalan tetapi tiada apa berlaku pada peranti

**Penyelesaian:**
1. **Sahkan kod disimpan** (periksa titik pada tab fail)
2. **Periksa Python yang digunakan:** `which python` atau `where python`
3. **Untuk Wio Terminal:** Pastikan kod dimuat naik melalui PlatformIO (klik butang muat naik)
4. **Untuk Raspberry Pi:** SSH ke Pi dan jalankan kod di situ
5. **Periksa tetingkap output** untuk ralat

#### Masalah: IntelliSense tidak memaparkan fungsi perpustakaan
**Gejala:** Tiada autocomplete untuk modul yang diimport

**Penyelesaian:**
1. Pastikan perpustakaan dipasang dalam persekitaran semasa
2. Muat semula tetingkap VS Code
3. Periksa interpreter Python adalah betul
4. Pasang type stub jika ada: `pip install types-<nama-perpustakaan>`

### Persekitaran Maya Python

#### Masalah: Tidak dapat buat persekitaran maya
**Ralat:** `The virtual environment was not created successfully`

**Penyelesaian:**
1. **Pasang modul venv:**
   - Ubuntu/Debian: `sudo apt install python3-venv`
   - macOS: Perlu disertakan dengan Python
   - Windows: Pasang semula Python dengan semua komponen
2. **Periksa pemasangan Python:** Sahkan Python dipasang dengan betul
3. **Guna laluan penuh:** Cuba `python3 -m venv .venv` dengan panggilan python3 secara eksplisit

#### Masalah: Pakej dipasang di lokasi salah
**Gejala:** Import error selepas memasang pakej

**Penyelesaian:**
1. **Sahkan venv diaktifkan:** Prompt arahan patut tunjuk `(.venv)`
2. **Periksa lokasi pip:** `which pip` patut tunjuk ke `.venv/bin/pip`
3. **Pasang semula dalam venv:** Aktifkan venv, kemudian `pip install <pakej>`
4. **Jangan guna sudo dengan pip** dalam persekitaran maya

#### Masalah: Persekitaran maya tidak mudah alih
**Gejala:** Venv tidak berfungsi selepas dipindah atau di komputer berlainan

**Penyelesaian:**
1. **Jangan pindahkan venv:** Padam dan buat semula di lokasi baru
2. **Guna requirements.txt:**
   ```bash
   pip freeze > requirements.txt
   pip install -r requirements.txt
   ```
3. **Buat semula venv:**
   ```bash
   python3 -m venv .venv
   source .venv/bin/activate  # atau activate.bat pada Windows
   pip install -r requirements.txt
   ```

### Kebergantungan

#### Masalah: Pemasangan pakej gagal
**Ralat:** Pelbagai ralat pip semasa pemasangan

**Penyelesaian:**
1. **Kemas kini pip:**
   ```bash
   pip install --upgrade pip
   ```
2. **Pasang alat binaan:**
   - Ubuntu/Debian: `sudo apt install build-essential python3-dev`
   - macOS: `xcode-select --install`
   - Windows: Pasang Visual Studio Build Tools
3. **Periksa sambungan internet**
4. **Cuba indeks pakej berbeza:** `pip install --index-url https://pypi.org/simple/ <pakej>`
5. **Pasang versi tertentu:** `pip install <pakej>==<versi>`

#### Masalah: Konflik kebergantungan
**Ralat:** `ERROR: pip's dependency resolver does not currently take into account all the packages that are installed`

**Penyelesaian:**
1. **Guna persekitaran maya baru** untuk setiap projek
2. **Kemas kini pakej:** `pip install --upgrade <pakej>`
3. **Semak keperluan:** Guna `pip check` untuk cari konflik
4. **Pasang versi serasi:** Nyatakan julat versi dalam requirements.txt

---

## Isu Prestasi

### Masalah: Kod berjalan perlahan
**Gejala:** Kelewatan, tamat masa, tingkah laku tidak responsif

**Penyelesaian:**
1. **Kurangkan kekerapan bacaan sensor:** Jangan baca sensor terlalu kerap
2. **Optimumkan gelung:** Elak menunggu sibuk, guna sleep() atau kelewatan
3. **Isu memori:**
   - Tutup aplikasi yang tidak perlu
   - Bebaskan ruang storan
   - Pantau dengan `top` atau `htop` pada Pi
4. **Kelajuan kad SD:** Guna kad SD atau SSD lebih pantas untuk Raspberry Pi
5. **Kelewatan rangkaian:** Guna operasi async untuk panggilan rangkaian

### Masalah: Ralat kehabisan memori
**Ralat:** `MemoryError` atau sistem beku

**Penyelesaian:**
1. **Untuk Raspberry Pi:**
   - Tutup aplikasi yang tidak perlu
   - Tambah ruang swap
   - Guna OS yang ringan (versi Lite)
   - Tingkatkan RAM (Pi 4 ada pilihan 2/4/8GB)
2. **Untuk Wio Terminal:**
   - Kurangkan saiz buffer
   - Guna imej lebih kecil
   - Optimumkan penggunaan rentetan
   - Periksa kebocoran memori (memori tidak dilepaskan)

### Masalah: Kehilangan data atau kerosakan
**Gejala:** Mesej hilang, fail rosak

**Penyelesaian:**
1. **Isu kad SD:**
   - Guna kad SD berkualiti (elak murah/palsu)
   - Sandaran secara berkala
   - Tutup dengan betul (jangan cabut kuasa terus)
2. **Buffer overflow:** Tingkatkan saiz buffer dalam kod
3. **Kebolehpercayaan rangkaian:** Laksanakan logik cuba semula dan pengurusan ralat
4. **Kualiti Perkhidmatan:** Guna MQTT QoS 1 atau 2 untuk mesej penting

---

## Mesej Ralat Umum

### `ModuleNotFoundError: No module named 'X'`
**Sebab:** Pakej tidak dipasang atau persekitaran maya tidak diaktifkan

**Penyelesaian:**
```bash
pip install X
```
Pastikan persekitaran maya diaktifkan dahulu.

### `Permission denied` pada Linux/macOS
**Sebab:** Perlukan keizinan tinggi atau isu kebenaran fail

**Penyelesaian:**
- Untuk operasi sistem: Guna `sudo`
- Untuk pip: JANGAN guna sudo dengan venv, aktifkan venv dahulu
- Untuk port serial: Tambah pengguna ke kumpulan dialout: `sudo usermod -a -G dialout $USER`, kemudian logout/login

### `OSError: [Errno 98] Address already in use`
**Sebab:** Port sudah digunakan oleh proses lain

**Penyelesaian:**
1. Cari proses guna port: `lsof -i :<port>` atau `netstat -ano | findstr :<port>`
2. Bunuh proses atau guna port lain dalam kod anda

### `SSL: CERTIFICATE_VERIFY_FAILED`
**Sebab:** Pengesahan sijil SSL gagal

**Penyelesaian:**
1. Kemas kini sijil: `pip install --upgrade certifi`
2. Semak masa sistem betul: `date`
3. Untuk pembangunan sahaja (bukan produksi): Lumpuhkan pengesahan dalam kod

### `IndentationError: unexpected indent`
**Sebab:** Isu indentasi Python (campur tab/spasi)

**Penyelesaian:**
1. Gunakan indentasi konsisten (4 spasi adalah standard Python)
2. Konfigurasikan editor guna spasi bukan tab
3. VS Code: Tetapkan `"editor.insertSpaces": true` dan `"editor.tabSize": 4`

### `UnicodeDecodeError` or `UnicodeEncodeError`
**Sebab:** Isu pengekodan aksara

**Penyelesaian:**
```python
# Apabila membaca fail
with open('file.txt', 'r', encoding='utf-8') as f:
    content = f.read()

# Apabila menulis fail
with open('file.txt', 'w', encoding='utf-8') as f:
    f.write(content)
```

---

## Mendapatkan Bantuan

Jika anda telah mencuba langkah penyelesaian masalah ini dan masih menghadapi isu:

### 1. Semak Sumber Sedia Ada
- **Dokumentasi:** Tinjau [README](README.md) dan arahan pelajaran
- **Panduan perkakasan:** Semak [hardware.md](hardware.md) untuk maklumat khusus perkakasan
- **Seeed Studio Wiki:** [Seeed Studio Wiki](https://wiki.seeedstudio.com/) untuk komponen Grove

### 2. Cari Isu Yang Sama
- **GitHub Issues:** Cari [isu sedia ada](https://github.com/microsoft/IoT-For-Beginners/issues)
- **Stack Overflow:** Cari mesej ralat
- **Forum peranti:** Semak forum Raspberry Pi atau forum Arduino

### 3. Cipta Isu GitHub
Jika anda tidak dapat mencari penyelesaian:
1. Pergi ke [GitHub Issues](https://github.com/microsoft/IoT-For-Beginners/issues)
2. Klik "New Issue"
3. Berikan:
   - Penerangan jelas masalah
   - Langkah untuk ulangi
   - Mesej ralat (teks penuh)
   - Versi perkakasan/perisian
   - Apa yang telah anda cuba
   - Tangkapan skrin jika relevan

### 4. Sertai Komuniti
- **Discord:** [Microsoft Foundry Discord](https://discord.gg/nTYy5BXMWG)
- **Microsoft Learn:** [Microsoft Learn IoT](https://docs.microsoft.com/learn/browse/?products=azure-iot)

### 5. Berikan Laporan Pepijat Yang Baik
Laporan pepijat yang baik termasuk:
- **Persekitaran:** OS, versi Python, perkakasan yang digunakan
- **Langkah untuk mengulangi:** Langkah tepat yang menyebabkan isu
- **Kelakuan yang dijangkakan:** Apa yang sepatutnya berlaku
- **Kelakuan sebenar:** Apa yang sebenarnya berlaku
- **Mesej ralat:** Teks ralat lengkap, bukan tangkapan skrin
- **Kod:** Contoh kod minimum yang menghasilkan isu

---

## Tips Pencegahan

### Amalan Terbaik Am
1. **Simpan salinan sandaran:** Sandaran berkala kad SD/kod yang berfungsi
2. **Dokumentasikan perubahan:** Catat apa yang berfungsi dalam komen
3. **Kawalan versi:** Gunakan git untuk menjejak perubahan kod
4. **Uji secara berperingkat:** Uji perubahan kecil sebelum digabungkan
5. **Baca mesej ralat:** Ia sering memberitahu dengan tepat apa yang salah
6. **Kemas kini secara berkala:** Kekalkan perisian/firmware sentiasa terkini
7. **Gunakan komponen berkualiti:** Elakkan kabel/bekalan kuasa murah
8. **Kuasa stabil:** Gunakan bekalan kuasa yang sesuai (terutama Pi)

### Aliran Kerja Pembangunan
1. **Mula dengan mudah:** Mulakan dengan kod contoh yang berfungsi
2. **Satu perubahan pada satu masa:** Lebih mudah mencari apa yang rosak
3. **Uji secara kerap:** Tangkap isu lebih awal
4. **Pastikan teratur:** Susun fail dan kod secara logik
5. **Komen kod:** Masa depan anda akan menghargainya

---

*Panduan penyelesaian masalah ini diselenggara oleh komuniti. Jika anda menemui penyelesaian untuk masalah yang tidak disenaraikan di sini, sila pertimbangkan untuk [menyumbang](CONTRIBUTING.md) bagi membantu yang lain!*

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, harap maklum bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya hendaklah dianggap sebagai sumber yang sahih. Untuk maklumat penting, terjemahan profesional oleh manusia adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->