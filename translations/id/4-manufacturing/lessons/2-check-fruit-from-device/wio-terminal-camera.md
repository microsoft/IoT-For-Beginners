<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "160be8c0f558687f6686dca64f10f739",
  "translation_date": "2025-08-27T21:04:54+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md",
  "language_code": "id"
}
-->
# Menangkap Gambar - Wio Terminal

Dalam bagian pelajaran ini, Anda akan menambahkan kamera ke Wio Terminal Anda dan menangkap gambar darinya.

## Perangkat Keras

Wio Terminal membutuhkan kamera.

Kamera yang akan Anda gunakan adalah [ArduCam Mini 2MP Plus](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/). Ini adalah kamera 2 megapiksel yang menggunakan sensor gambar OV2640. Kamera ini berkomunikasi melalui antarmuka SPI untuk menangkap gambar, dan menggunakan I2C untuk mengonfigurasi sensor.

## Sambungkan Kamera

ArduCam tidak memiliki soket Grove, melainkan terhubung ke bus SPI dan I2C melalui pin GPIO pada Wio Terminal.

### Tugas - Sambungkan Kamera

Sambungkan kamera.

![Sensor ArduCam](../../../../../translated_images/arducam.20e4e4cbb268296570b5914e20d6c349fc42ddac9ed4e1b9deba2188204eebae.id.png)

1. Pin di bagian bawah ArduCam perlu dihubungkan ke pin GPIO pada Wio Terminal. Untuk mempermudah menemukan pin yang tepat, pasang stiker pin GPIO yang disertakan dengan Wio Terminal di sekitar pin:

    ![Wio Terminal dengan stiker pin GPIO terpasang](../../../../../translated_images/wio-terminal-pin-sticker.b90b1535937b84bd.id.png)

1. Gunakan kabel jumper untuk membuat koneksi berikut:

    | Pin ArduCAM | Pin Wio Terminal | Deskripsi                               |
    | ----------- | ---------------- | --------------------------------------- |
    | CS          | 24 (SPI_CS)      | SPI Chip Select                         |
    | MOSI        | 19 (SPI_MOSI)    | SPI Controller Output, Peripheral Input |
    | MISO        | 21 (SPI_MISO)    | SPI Controller Input, Peripheral Output |
    | SCK         | 23 (SPI_SCLK)    | SPI Serial Clock                        |
    | GND         | 6 (GND)          | Ground - 0V                             |
    | VCC         | 4 (5V)           | Catu daya 5V                            |
    | SDA         | 3 (I2C1_SDA)     | I2C Serial Data                         |
    | SCL         | 5 (I2C1_SCL)     | I2C Serial Clock                        |

    ![Wio Terminal terhubung ke ArduCam dengan kabel jumper](../../../../../translated_images/arducam-wio-terminal-connections.a4d5a4049bdb5ab800a2877389fc6ecf5e4ff307e6451ff56c517e6786467d0a.id.png)

    Koneksi GND dan VCC menyediakan catu daya 5V ke ArduCam. Kamera ini berjalan pada 5V, berbeda dengan sensor Grove yang berjalan pada 3V. Daya ini berasal langsung dari koneksi USB-C yang memberi daya pada perangkat.

    > 💁 Untuk koneksi SPI, label pin pada ArduCam dan nama pin Wio Terminal yang digunakan dalam kode masih menggunakan konvensi penamaan lama. Instruksi dalam pelajaran ini akan menggunakan konvensi penamaan baru, kecuali saat nama pin digunakan dalam kode.

1. Sekarang Anda dapat menghubungkan Wio Terminal ke komputer Anda.

## Program Perangkat untuk Terhubung ke Kamera

Wio Terminal sekarang dapat diprogram untuk menggunakan kamera ArduCAM yang terpasang.

### Tugas - Program Perangkat untuk Terhubung ke Kamera

1. Buat proyek baru untuk Wio Terminal menggunakan PlatformIO. Beri nama proyek ini `fruit-quality-detector`. Tambahkan kode dalam fungsi `setup` untuk mengonfigurasi port serial.

1. Tambahkan kode untuk terhubung ke WiFi, dengan kredensial WiFi Anda dalam file bernama `config.h`. Jangan lupa tambahkan pustaka yang diperlukan ke file `platformio.ini`.

1. Pustaka ArduCam tidak tersedia sebagai pustaka Arduino yang dapat diinstal dari file `platformio.ini`. Sebaliknya, pustaka ini perlu diinstal dari sumber di halaman GitHub mereka. Anda dapat mendapatkannya dengan:

    * Mengkloning repo dari [https://github.com/ArduCAM/Arduino.git](https://github.com/ArduCAM/Arduino.git)
    * Mengunjungi repo di GitHub di [github.com/ArduCAM/Arduino](https://github.com/ArduCAM/Arduino) dan mengunduh kode sebagai zip dari tombol **Code**

1. Anda hanya membutuhkan folder `ArduCAM` dari kode ini. Salin seluruh folder ke dalam folder `lib` di proyek Anda.

    > ⚠️ Seluruh folder harus disalin, sehingga kode berada di `lib/ArduCam`. Jangan hanya menyalin isi folder `ArduCam` ke dalam folder `lib`, salin seluruh folder.

1. Kode pustaka ArduCam bekerja untuk berbagai jenis kamera. Jenis kamera yang ingin Anda gunakan dikonfigurasi menggunakan flag compiler - ini membuat pustaka yang dibangun sekecil mungkin dengan menghapus kode untuk kamera yang tidak Anda gunakan. Untuk mengonfigurasi pustaka untuk kamera OV2640, tambahkan yang berikut ini ke akhir file `platformio.ini`:

    ```ini
    build_flags =
        -DARDUCAM_SHIELD_V2
        -DOV2640_CAM
    ```

    Ini menetapkan 2 flag compiler:

      * `ARDUCAM_SHIELD_V2` untuk memberi tahu pustaka bahwa kamera ada di papan Arduino, yang dikenal sebagai shield.
      * `OV2640_CAM` untuk memberi tahu pustaka hanya menyertakan kode untuk kamera OV2640.

1. Tambahkan file header ke dalam folder `src` bernama `camera.h`. File ini akan berisi kode untuk berkomunikasi dengan kamera. Tambahkan kode berikut ke file ini:

    ```cpp
    #pragma once
    
    #include <ArduCAM.h>
    #include <Wire.h>
    
    class Camera
    {
    public:
        Camera(int format, int image_size) : _arducam(OV2640, PIN_SPI_SS)
        {
            _format = format;
            _image_size = image_size;
        }
    
        bool init()
        {
            // Reset the CPLD
            _arducam.write_reg(0x07, 0x80);
            delay(100);
    
            _arducam.write_reg(0x07, 0x00);
            delay(100);
    
            // Check if the ArduCAM SPI bus is OK
            _arducam.write_reg(ARDUCHIP_TEST1, 0x55);
            if (_arducam.read_reg(ARDUCHIP_TEST1) != 0x55)
            {
                return false;
            }
                
            // Change MCU mode
            _arducam.set_mode(MCU2LCD_MODE);
    
            uint8_t vid, pid;
    
            // Check if the camera module type is OV2640
            _arducam.wrSensorReg8_8(0xff, 0x01);
            _arducam.rdSensorReg8_8(OV2640_CHIPID_HIGH, &vid);
            _arducam.rdSensorReg8_8(OV2640_CHIPID_LOW, &pid);
            if ((vid != 0x26) && ((pid != 0x41) || (pid != 0x42)))
            {
                return false;
            }
            
            _arducam.set_format(_format);
            _arducam.InitCAM();
            _arducam.OV2640_set_JPEG_size(_image_size);
            _arducam.OV2640_set_Light_Mode(Auto);
            _arducam.OV2640_set_Special_effects(Normal);
            delay(1000);
    
            return true;
        }
    
        void startCapture()
        {
            _arducam.flush_fifo();
            _arducam.clear_fifo_flag();
            _arducam.start_capture();
        }
    
        bool captureReady()
        {
            return _arducam.get_bit(ARDUCHIP_TRIG, CAP_DONE_MASK);
        }
    
        bool readImageToBuffer(byte **buffer, uint32_t &buffer_length)
        {
            if (!captureReady()) return false;
    
            // Get the image file length
            uint32_t length = _arducam.read_fifo_length();
            buffer_length = length;
    
            if (length >= MAX_FIFO_SIZE)
            {
                return false;
            }
            if (length == 0)
            {
                return false;
            }
    
            // create the buffer
            byte *buf = new byte[length];
    
            uint8_t temp = 0, temp_last = 0;
            int i = 0;
            uint32_t buffer_pos = 0;
            bool is_header = false;
    
            _arducam.CS_LOW();
            _arducam.set_fifo_burst();
            
            while (length--)
            {
                temp_last = temp;
                temp = SPI.transfer(0x00);
                //Read JPEG data from FIFO
                if ((temp == 0xD9) && (temp_last == 0xFF)) //If find the end ,break while,
                {
                    buf[buffer_pos] = temp;
    
                    buffer_pos++;
                    i++;
                    
                    _arducam.CS_HIGH();
                }
                if (is_header == true)
                {
                    //Write image data to buffer if not full
                    if (i < 256)
                    {
                        buf[buffer_pos] = temp;
                        buffer_pos++;
                        i++;
                    }
                    else
                    {
                        _arducam.CS_HIGH();
    
                        i = 0;
                        buf[buffer_pos] = temp;
    
                        buffer_pos++;
                        i++;
    
                        _arducam.CS_LOW();
                        _arducam.set_fifo_burst();
                    }
                }
                else if ((temp == 0xD8) & (temp_last == 0xFF))
                {
                    is_header = true;
    
                    buf[buffer_pos] = temp_last;
                    buffer_pos++;
                    i++;
    
                    buf[buffer_pos] = temp;
                    buffer_pos++;
                    i++;
                }
            }
            
            _arducam.clear_fifo_flag();
    
            _arducam.set_format(_format);
            _arducam.InitCAM();
            _arducam.OV2640_set_JPEG_size(_image_size);
    
            // return the buffer
            *buffer = buf;
        }
    
    private:
        ArduCAM _arducam;
        int _format;
        int _image_size;
    };
    ```

    Ini adalah kode tingkat rendah yang mengonfigurasi kamera menggunakan pustaka ArduCam, dan mengekstrak gambar saat diperlukan menggunakan bus SPI. Kode ini sangat spesifik untuk ArduCam, jadi Anda tidak perlu khawatir tentang cara kerjanya saat ini.

1. Di `main.cpp`, tambahkan kode berikut di bawah pernyataan `include` lainnya untuk menyertakan file baru ini dan membuat instance kelas kamera:

    ```cpp
    #include "camera.h"

    Camera camera = Camera(JPEG, OV2640_640x480);
    ```

    Ini membuat `Camera` yang menyimpan gambar sebagai JPEG dengan resolusi 640 x 480. Meskipun resolusi yang lebih tinggi didukung (hingga 3280x2464), pengklasifikasi gambar bekerja pada gambar yang jauh lebih kecil (227x227) sehingga tidak perlu menangkap dan mengirim gambar yang lebih besar.

1. Tambahkan kode berikut di bawah ini untuk mendefinisikan fungsi untuk mengatur kamera:

    ```cpp
    void setupCamera()
    {
        pinMode(PIN_SPI_SS, OUTPUT);
        digitalWrite(PIN_SPI_SS, HIGH);
    
        Wire.begin();
        SPI.begin();
    
        if (!camera.init())
        {
            Serial.println("Error setting up the camera!");
        }
    }
    ```

    Fungsi `setupCamera` ini dimulai dengan mengonfigurasi pin chip select SPI (`PIN_SPI_SS`) sebagai tinggi, membuat Wio Terminal menjadi pengontrol SPI. Kemudian memulai bus I2C dan SPI. Akhirnya, fungsi ini menginisialisasi kelas kamera yang mengonfigurasi pengaturan sensor kamera dan memastikan semuanya terhubung dengan benar.

1. Panggil fungsi ini di akhir fungsi `setup`:

    ```cpp
    setupCamera();
    ```

1. Bangun dan unggah kode ini, dan periksa output dari monitor serial. Jika Anda melihat `Error setting up the camera!`, periksa kabel untuk memastikan semua kabel menghubungkan pin yang benar pada ArduCam ke pin GPIO yang benar pada Wio Terminal, dan semua kabel jumper terpasang dengan benar.

## Menangkap Gambar

Wio Terminal sekarang dapat diprogram untuk menangkap gambar saat sebuah tombol ditekan.

### Tugas - Menangkap Gambar

1. Mikrokontroler menjalankan kode Anda secara terus-menerus, sehingga tidak mudah memicu sesuatu seperti mengambil foto tanpa bereaksi terhadap sensor. Wio Terminal memiliki tombol, sehingga kamera dapat diatur untuk dipicu oleh salah satu tombol. Tambahkan kode berikut ke akhir fungsi `setup` untuk mengonfigurasi tombol C (salah satu dari tiga tombol di bagian atas, yang paling dekat dengan sakelar daya).

    ![Tombol C di bagian atas dekat dengan sakelar daya](../../../../../translated_images/wio-terminal-c-button.73df3cb1c1445ea0.id.png)

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

    Mode `INPUT_PULLUP` pada dasarnya membalikkan input. Misalnya, biasanya tombol akan mengirim sinyal rendah saat tidak ditekan, dan sinyal tinggi saat ditekan. Saat diatur ke `INPUT_PULLUP`, tombol mengirim sinyal tinggi saat tidak ditekan, dan sinyal rendah saat ditekan.

1. Tambahkan fungsi kosong untuk merespons penekanan tombol sebelum fungsi `loop`:

    ```cpp
    void buttonPressed()
    {
        
    }
    ```

1. Panggil fungsi ini dalam metode `loop` saat tombol ditekan:

    ```cpp
    void loop()
    {
        if (digitalRead(WIO_KEY_C) == LOW)
        {
            buttonPressed();
            delay(2000);
        }
    
        delay(200);
    }
    ```

    Kode ini memeriksa apakah tombol ditekan. Jika ditekan, fungsi `buttonPressed` dipanggil, dan loop menunda selama 2 detik. Ini untuk memberikan waktu agar tombol dilepaskan sehingga penekanan panjang tidak terdaftar dua kali.

    > 💁 Tombol pada Wio Terminal diatur ke `INPUT_PULLUP`, sehingga mengirim sinyal tinggi saat tidak ditekan, dan sinyal rendah saat ditekan.

1. Tambahkan kode berikut ke fungsi `buttonPressed`:

    ```cpp
    camera.startCapture();
 
    while (!camera.captureReady())
        delay(100);

    Serial.println("Image captured");

    byte *buffer;
    uint32_t length;

    if (camera.readImageToBuffer(&buffer, length))
    {
        Serial.print("Image read to buffer with length ");
        Serial.println(length);

        delete(buffer);
    }
    ```

    Kode ini memulai pengambilan gambar kamera dengan memanggil `startCapture`. Perangkat keras kamera tidak bekerja dengan mengembalikan data saat Anda memintanya, melainkan Anda mengirim instruksi untuk mulai menangkap, dan kamera akan bekerja di latar belakang untuk menangkap gambar, mengonversinya menjadi JPEG, dan menyimpannya dalam buffer lokal di kamera itu sendiri. Panggilan `captureReady` kemudian memeriksa apakah pengambilan gambar telah selesai.

    Setelah pengambilan selesai, data gambar disalin dari buffer di kamera ke buffer lokal (array byte) dengan panggilan `readImageToBuffer`. Panjang buffer kemudian dikirim ke monitor serial.

1. Bangun dan unggah kode ini, dan periksa output di monitor serial. Setiap kali Anda menekan tombol C, gambar akan ditangkap dan Anda akan melihat ukuran gambar dikirim ke monitor serial.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 9224
    Image captured
    Image read to buffer with length 11272
    ```

    Gambar yang berbeda akan memiliki ukuran yang berbeda. Gambar-gambar ini dikompresi sebagai JPEG, dan ukuran file JPEG untuk resolusi tertentu bergantung pada apa yang ada di gambar.

> 💁 Anda dapat menemukan kode ini di folder [code-camera/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/wio-terminal).

😀 Anda telah berhasil menangkap gambar dengan Wio Terminal Anda.

## Opsional - Verifikasi Gambar Kamera Menggunakan Kartu SD

Cara termudah untuk melihat gambar yang ditangkap oleh kamera adalah dengan menulisnya ke kartu SD di Wio Terminal dan kemudian melihatnya di komputer Anda. Lakukan langkah ini jika Anda memiliki kartu microSD cadangan dan soket kartu microSD di komputer Anda, atau adaptor.

Wio Terminal hanya mendukung kartu microSD hingga ukuran 16GB. Jika Anda memiliki kartu SD yang lebih besar, maka tidak akan berfungsi.

### Tugas - Verifikasi Gambar Kamera Menggunakan Kartu SD

1. Format kartu microSD sebagai FAT32 atau exFAT menggunakan aplikasi yang relevan di komputer Anda (Disk Utility di macOS, File Explorer di Windows, atau menggunakan alat baris perintah di Linux).

1. Masukkan kartu microSD ke soket tepat di bawah sakelar daya. Pastikan kartu masuk sepenuhnya hingga terkunci dan tetap di tempatnya, Anda mungkin perlu mendorongnya menggunakan kuku atau alat tipis.

1. Tambahkan pernyataan `include` berikut di bagian atas file `main.cpp`:

    ```cpp
    #include "SD/Seeed_SD.h"
    #include <Seeed_FS.h>
    ```

1. Tambahkan fungsi berikut sebelum fungsi `setup`:

    ```cpp
    void setupSDCard()
    {
        while (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI))
        {
            Serial.println("SD Card Error");
        }
    }
    ```

    Fungsi ini mengonfigurasi kartu SD menggunakan bus SPI.

1. Panggil fungsi ini dari fungsi `setup`:

    ```cpp
    setupSDCard();
    ```

1. Tambahkan kode berikut di atas fungsi `buttonPressed`:

    ```cpp
    int fileNum = 1;

    void saveToSDCard(byte *buffer, uint32_t length)
    {
        char buff[16];
        sprintf(buff, "%d.jpg", fileNum);
        fileNum++;
    
        File outFile = SD.open(buff, FILE_WRITE );
        outFile.write(buffer, length);
        outFile.close();

        Serial.print("Image written to file ");
        Serial.println(buff);
    }
    ```

    Ini mendefinisikan variabel global untuk jumlah file. Variabel ini digunakan untuk nama file gambar sehingga beberapa gambar dapat ditangkap dengan nama file yang meningkat - `1.jpg`, `2.jpg`, dan seterusnya.

    Kemudian mendefinisikan fungsi `saveToSDCard` yang mengambil buffer data byte dan panjang buffer. Nama file dibuat menggunakan jumlah file, dan jumlah file ditingkatkan siap untuk file berikutnya. Data biner dari buffer kemudian ditulis ke file.

1. Panggil fungsi `saveToSDCard` dari fungsi `buttonPressed`. Panggilan ini harus **sebelum** buffer dihapus:

    ```cpp
    Serial.print("Image read to buffer with length ");
    Serial.println(length);

    saveToSDCard(buffer, length);
    
    delete(buffer);
    ```

1. Bangun dan unggah kode ini, dan periksa output di monitor serial. Setiap kali Anda menekan tombol C, gambar akan ditangkap dan disimpan ke kartu SD.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 16392
    Image written to file 1.jpg
    Image captured
    Image read to buffer with length 14344
    Image written to file 2.jpg
    ```

1. Matikan daya pada kartu microSD dan keluarkan dengan mendorongnya sedikit dan melepaskannya, dan kartu akan keluar. Anda mungkin perlu menggunakan alat tipis untuk melakukannya. Sambungkan kartu microSD ke komputer Anda untuk melihat gambar.

    ![Gambar pisang yang ditangkap menggunakan ArduCam](../../../../../translated_images/banana-arducam.be1b32d4267a8194b0fd042362e56faa431da9cd4af172051b37243ea9be0256.id.jpg)
💁 Mungkin diperlukan beberapa gambar agar keseimbangan putih kamera dapat menyesuaikan dirinya. Anda akan melihat ini berdasarkan warna gambar yang diambil, beberapa gambar pertama mungkin terlihat tidak sesuai warna. Anda selalu dapat mengatasi hal ini dengan mengubah kode untuk mengambil beberapa gambar yang diabaikan dalam fungsi `setup`.


---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.