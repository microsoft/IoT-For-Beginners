<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2f336726b9410e97c3aaed76cc89b0d8",
  "translation_date": "2025-08-27T23:24:57+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-audio.md",
  "language_code": "id"
}
-->
# Menangkap Audio - Wio Terminal

Dalam bagian pelajaran ini, Anda akan menulis kode untuk menangkap audio pada Wio Terminal Anda. Penangkapan audio akan dikontrol oleh salah satu tombol di bagian atas Wio Terminal.

## Memprogram perangkat untuk menangkap audio

Anda dapat menangkap audio dari mikrofon menggunakan kode C++. Wio Terminal hanya memiliki RAM sebesar 192KB, yang tidak cukup untuk menangkap lebih dari beberapa detik audio. Namun, perangkat ini memiliki memori flash sebesar 4MB, sehingga memori flash dapat digunakan untuk menyimpan audio yang ditangkap.

Mikrofon bawaan menangkap sinyal analog, yang kemudian dikonversi menjadi sinyal digital yang dapat digunakan oleh Wio Terminal. Saat menangkap audio, data perlu ditangkap pada waktu yang tepat - misalnya, untuk menangkap audio pada 16KHz, audio harus ditangkap tepat 16.000 kali per detik, dengan interval yang sama di antara setiap sampel. Daripada menggunakan kode Anda untuk melakukan ini, Anda dapat menggunakan pengontrol akses memori langsung (DMAC). DMAC adalah sirkuit yang dapat menangkap sinyal dari suatu tempat dan menulis ke memori tanpa mengganggu kode Anda yang berjalan di prosesor.

✅ Baca lebih lanjut tentang DMA di [halaman akses memori langsung di Wikipedia](https://wikipedia.org/wiki/Direct_memory_access).

![Audio dari mikrofon masuk ke ADC lalu ke DMAC. DMAC menulis ke satu buffer. Ketika buffer ini penuh, data diproses dan DMAC menulis ke buffer kedua](../../../../../translated_images/id/dmac-adc-buffers.4509aee49145c90bc2e1be472b8ed2ddfcb2b6a81ad3e559114aca55f5fff759.png)

DMAC dapat menangkap audio dari ADC pada interval tetap, seperti 16.000 kali per detik untuk audio 16KHz. DMAC dapat menulis data yang ditangkap ini ke buffer memori yang telah dialokasikan sebelumnya, dan ketika buffer ini penuh, data tersedia untuk diproses oleh kode Anda. Penggunaan memori ini dapat menunda penangkapan audio, tetapi Anda dapat mengatur beberapa buffer. DMAC menulis ke buffer 1, lalu ketika buffer ini penuh, DMAC memberi tahu kode Anda untuk memproses buffer 1, sementara DMAC menulis ke buffer 2. Ketika buffer 2 penuh, DMAC memberi tahu kode Anda, dan kembali menulis ke buffer 1. Dengan cara ini, selama Anda memproses setiap buffer dalam waktu yang lebih singkat daripada waktu yang diperlukan untuk mengisi satu buffer, Anda tidak akan kehilangan data.

Setelah setiap buffer ditangkap, data dapat ditulis ke memori flash. Memori flash perlu ditulis menggunakan alamat yang telah ditentukan, menentukan di mana menulis dan seberapa besar data yang ditulis, mirip dengan memperbarui array byte dalam memori. Memori flash memiliki granularitas, yang berarti operasi penghapusan dan penulisan bergantung tidak hanya pada ukuran tetap, tetapi juga pada penyelarasan dengan ukuran tersebut. Misalnya, jika granularitas adalah 4096 byte dan Anda meminta penghapusan pada alamat 4200, data dari alamat 4096 hingga 8192 dapat dihapus. Ini berarti ketika Anda menulis data audio ke memori flash, data harus ditulis dalam potongan dengan ukuran yang sesuai.

### Tugas - mengonfigurasi memori flash

1. Buat proyek baru Wio Terminal menggunakan PlatformIO. Beri nama proyek ini `smart-timer`. Tambahkan kode dalam fungsi `setup` untuk mengonfigurasi port serial.

1. Tambahkan dependensi pustaka berikut ke file `platformio.ini` untuk memberikan akses ke memori flash:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. Buka file `main.cpp` dan tambahkan direktif `include` berikut untuk pustaka memori flash di bagian atas file:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD adalah singkatan dari Serial Flash Universal Driver, dan merupakan pustaka yang dirancang untuk bekerja dengan semua chip memori flash.

1. Dalam fungsi `setup`, tambahkan kode berikut untuk mengatur pustaka penyimpanan flash:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    Kode ini akan terus berulang hingga pustaka SFUD diinisialisasi, lalu mengaktifkan pembacaan cepat. Memori flash bawaan dapat diakses menggunakan Queued Serial Peripheral Interface (QSPI), jenis pengontrol SPI yang memungkinkan akses berkelanjutan melalui antrean dengan penggunaan prosesor minimal. Hal ini membuat pembacaan dan penulisan ke memori flash menjadi lebih cepat.

1. Buat file baru di folder `src` bernama `flash_writer.h`.

1. Tambahkan berikut ini ke bagian atas file:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    Kode ini menyertakan beberapa file header yang diperlukan, termasuk file header untuk pustaka SFUD untuk berinteraksi dengan memori flash.

1. Definisikan kelas dalam file header baru ini bernama `FlashWriter`:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. Di bagian `private`, tambahkan kode berikut:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    Kode ini mendefinisikan beberapa bidang untuk buffer yang digunakan untuk menyimpan data sebelum menulisnya ke memori flash. Ada array byte, `_sfudBuffer`, untuk menulis data, dan ketika buffer ini penuh, data ditulis ke memori flash. Bidang `_sfudBufferPos` menyimpan lokasi saat ini untuk menulis ke buffer ini, dan `_sfudBufferWritePos` menyimpan lokasi di memori flash untuk menulis. `_flash` adalah pointer ke memori flash untuk menulis - beberapa mikrokontroler memiliki beberapa chip memori flash.

1. Tambahkan metode berikut ke bagian `public` untuk menginisialisasi kelas ini:

    ```cpp
    void init()
    {
        _flash = sfud_get_device_table() + 0;
        _sfudBufferSize = _flash->chip.erase_gran;
        _sfudBuffer = new byte[_sfudBufferSize];
        _sfudBufferPos = 0;
        _sfudBufferWritePos = 0;
    }
    ```

    Kode ini mengonfigurasi memori flash pada Wio Terminal untuk ditulis, dan mengatur buffer berdasarkan ukuran granularitas memori flash. Kode ini berada dalam metode `init`, bukan konstruktor, karena perlu dipanggil setelah memori flash diatur dalam fungsi `setup`.

1. Tambahkan kode berikut ke bagian `public`:

    ```cpp
    void writeSfudBuffer(byte b)
    {
        _sfudBuffer[_sfudBufferPos++] = b;
        if (_sfudBufferPos == _sfudBufferSize)
        {
            sfud_erase_write(_flash, _sfudBufferWritePos, _sfudBufferSize, _sfudBuffer);
            _sfudBufferWritePos += _sfudBufferSize;
            _sfudBufferPos = 0;
        }
    }

    void writeSfudBuffer(byte *b, size_t len)
    {
        for (size_t i = 0; i < len; ++i)
        {
            writeSfudBuffer(b[i]);
        }
    }

    void flushSfudBuffer()
    {
        if (_sfudBufferPos > 0)
        {
            sfud_erase_write(_flash, _sfudBufferWritePos, _sfudBufferSize, _sfudBuffer);
            _sfudBufferWritePos += _sfudBufferSize;
            _sfudBufferPos = 0;
        }
    }
    ```

    Kode ini mendefinisikan metode untuk menulis byte ke sistem penyimpanan flash. Metode ini bekerja dengan menulis ke buffer dalam memori yang ukurannya sesuai untuk memori flash, dan ketika buffer ini penuh, buffer ini ditulis ke memori flash, menghapus data yang ada di lokasi tersebut. Ada juga metode `flushSfudBuffer` untuk menulis buffer yang tidak lengkap, karena data yang ditangkap tidak akan berupa kelipatan yang tepat dari ukuran granularitas, sehingga bagian akhir data perlu ditulis.

    > 💁 Bagian akhir data akan menulis data tambahan yang tidak diinginkan, tetapi ini tidak masalah karena hanya data yang diperlukan yang akan dibaca.

### Tugas - mengatur penangkapan audio

1. Buat file baru di folder `src` bernama `config.h`.

1. Tambahkan berikut ini ke bagian atas file:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    Kode ini mengatur beberapa konstanta untuk penangkapan audio.

    | Konstanta             | Nilai  | Deskripsi |
    | --------------------- | -----: | - |
    | RATE                  | 16000  | Tingkat sampel untuk audio. 16.000 adalah 16KHz |
    | SAMPLE_LENGTH_SECONDS | 4      | Panjang audio yang akan ditangkap. Ini diatur ke 4 detik. Untuk merekam audio lebih lama, tingkatkan nilai ini. |
    | SAMPLES               | 64000  | Jumlah total sampel audio yang akan ditangkap. Diatur ke tingkat sampel * jumlah detik |
    | BUFFER_SIZE           | 128044 | Ukuran buffer audio untuk menangkap. Audio akan ditangkap sebagai file WAV, yang terdiri dari 44 byte header, lalu 128.000 byte data audio (setiap sampel adalah 2 byte) |
    | ADC_BUF_LEN           | 1600   | Ukuran buffer yang digunakan untuk menangkap audio dari DMAC |

    > 💁 Jika Anda merasa 4 detik terlalu pendek untuk meminta timer, Anda dapat meningkatkan nilai `SAMPLE_LENGTH_SECONDS`, dan semua nilai lainnya akan dihitung ulang.

1. Buat file baru di folder `src` bernama `mic.h`.

1. Tambahkan berikut ini ke bagian atas file:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    Kode ini menyertakan beberapa file header yang diperlukan, termasuk file header `config.h` dan `FlashWriter`.

1. Tambahkan berikut ini untuk mendefinisikan kelas `Mic` yang dapat menangkap dari mikrofon:

    ```cpp
    class Mic
    {
    public:
        Mic()
        {
            _isRecording = false;
            _isRecordingReady = false;
        }
    
        void startRecording()
        {
            _isRecording = true;
            _isRecordingReady = false;
        }
    
        bool isRecording()
        {
            return _isRecording;
        }
    
        bool isRecordingReady()
        {
            return _isRecordingReady;
        }
    
    private:
        volatile bool _isRecording;
        volatile bool _isRecordingReady;
        FlashWriter _writer;
    };
    
    Mic mic;
    ```

    Kelas ini saat ini hanya memiliki beberapa bidang untuk melacak apakah perekaman telah dimulai, dan apakah perekaman siap digunakan. Ketika DMAC diatur, DMAC terus menulis ke buffer memori, sehingga flag `_isRecording` menentukan apakah buffer ini harus diproses atau diabaikan. Flag `_isRecordingReady` akan diatur ketika 4 detik audio yang diperlukan telah ditangkap. Bidang `_writer` digunakan untuk menyimpan data audio ke memori flash.

    Variabel global kemudian dideklarasikan untuk instance dari kelas `Mic`.

1. Tambahkan kode berikut ke bagian `private` dari kelas `Mic`:

    ```cpp
    typedef struct
    {
        uint16_t btctrl;
        uint16_t btcnt;
        uint32_t srcaddr;
        uint32_t dstaddr;
        uint32_t descaddr;
    } dmacdescriptor;

    // Globals - DMA and ADC
    volatile dmacdescriptor _wrb[DMAC_CH_NUM] __attribute__((aligned(16)));
    dmacdescriptor _descriptor_section[DMAC_CH_NUM] __attribute__((aligned(16)));
    dmacdescriptor _descriptor __attribute__((aligned(16)));

    void configureDmaAdc()
    {
        // Configure DMA to sample from ADC at a regular interval (triggered by timer/counter)
        DMAC->BASEADDR.reg = (uint32_t)_descriptor_section;                    // Specify the location of the descriptors
        DMAC->WRBADDR.reg = (uint32_t)_wrb;                                    // Specify the location of the write back descriptors
        DMAC->CTRL.reg = DMAC_CTRL_DMAENABLE | DMAC_CTRL_LVLEN(0xf);           // Enable the DMAC peripheral
        DMAC->Channel[1].CHCTRLA.reg = DMAC_CHCTRLA_TRIGSRC(TC5_DMAC_ID_OVF) | // Set DMAC to trigger on TC5 timer overflow
                                        DMAC_CHCTRLA_TRIGACT_BURST;             // DMAC burst transfer

        _descriptor.descaddr = (uint32_t)&_descriptor_section[1];                    // Set up a circular descriptor
        _descriptor.srcaddr = (uint32_t)&ADC1->RESULT.reg;                           // Take the result from the ADC0 RESULT register
        _descriptor.dstaddr = (uint32_t)_adc_buf_0 + sizeof(uint16_t) * ADC_BUF_LEN; // Place it in the adc_buf_0 array
        _descriptor.btcnt = ADC_BUF_LEN;                                             // Beat count
        _descriptor.btctrl = DMAC_BTCTRL_BEATSIZE_HWORD |                            // Beat size is HWORD (16-bits)
                                DMAC_BTCTRL_DSTINC |                                    // Increment the destination address
                                DMAC_BTCTRL_VALID |                                     // Descriptor is valid
                                DMAC_BTCTRL_BLOCKACT_SUSPEND;                           // Suspend DMAC channel 0 after block transfer
        memcpy(&_descriptor_section[0], &_descriptor, sizeof(_descriptor));          // Copy the descriptor to the descriptor section

        _descriptor.descaddr = (uint32_t)&_descriptor_section[0];                    // Set up a circular descriptor
        _descriptor.srcaddr = (uint32_t)&ADC1->RESULT.reg;                           // Take the result from the ADC0 RESULT register
        _descriptor.dstaddr = (uint32_t)_adc_buf_1 + sizeof(uint16_t) * ADC_BUF_LEN; // Place it in the adc_buf_1 array
        _descriptor.btcnt = ADC_BUF_LEN;                                             // Beat count
        _descriptor.btctrl = DMAC_BTCTRL_BEATSIZE_HWORD |                            // Beat size is HWORD (16-bits)
                                DMAC_BTCTRL_DSTINC |                                    // Increment the destination address
                                DMAC_BTCTRL_VALID |                                     // Descriptor is valid
                                DMAC_BTCTRL_BLOCKACT_SUSPEND;                           // Suspend DMAC channel 0 after block transfer
        memcpy(&_descriptor_section[1], &_descriptor, sizeof(_descriptor));          // Copy the descriptor to the descriptor section

        // Configure NVIC
        NVIC_SetPriority(DMAC_1_IRQn, 0); // Set the Nested Vector Interrupt Controller (NVIC) priority for DMAC1 to 0 (highest)
        NVIC_EnableIRQ(DMAC_1_IRQn);      // Connect DMAC1 to Nested Vector Interrupt Controller (NVIC)

        // Activate the suspend (SUSP) interrupt on DMAC channel 1
        DMAC->Channel[1].CHINTENSET.reg = DMAC_CHINTENSET_SUSP;

        // Configure ADC
        ADC1->INPUTCTRL.bit.MUXPOS = ADC_INPUTCTRL_MUXPOS_AIN12_Val; // Set the analog input to ADC0/AIN2 (PB08 - A4 on Metro M4)
        while (ADC1->SYNCBUSY.bit.INPUTCTRL)
            ;                              // Wait for synchronization
        ADC1->SAMPCTRL.bit.SAMPLEN = 0x00; // Set max Sampling Time Length to half divided ADC clock pulse (2.66us)
        while (ADC1->SYNCBUSY.bit.SAMPCTRL)
            ;                                         // Wait for synchronization
        ADC1->CTRLA.reg = ADC_CTRLA_PRESCALER_DIV128; // Divide Clock ADC GCLK by 128 (48MHz/128 = 375kHz)
        ADC1->CTRLB.reg = ADC_CTRLB_RESSEL_12BIT |    // Set ADC resolution to 12 bits
                            ADC_CTRLB_FREERUN;          // Set ADC to free run mode
        while (ADC1->SYNCBUSY.bit.CTRLB)
            ;                       // Wait for synchronization
        ADC1->CTRLA.bit.ENABLE = 1; // Enable the ADC
        while (ADC1->SYNCBUSY.bit.ENABLE)
            ;                       // Wait for synchronization
        ADC1->SWTRIG.bit.START = 1; // Initiate a software trigger to start an ADC conversion
        while (ADC1->SYNCBUSY.bit.SWTRIG)
            ; // Wait for synchronization

        // Enable DMA channel 1
        DMAC->Channel[1].CHCTRLA.bit.ENABLE = 1;

        // Configure Timer/Counter 5
        GCLK->PCHCTRL[TC5_GCLK_ID].reg = GCLK_PCHCTRL_CHEN |     // Enable peripheral channel for TC5
                                            GCLK_PCHCTRL_GEN_GCLK1; // Connect generic clock 0 at 48MHz

        TC5->COUNT16.WAVE.reg = TC_WAVE_WAVEGEN_MFRQ; // Set TC5 to Match Frequency (MFRQ) mode
        TC5->COUNT16.CC[0].reg = 3000 - 1;            // Set the trigger to 16 kHz: (4Mhz / 16000) - 1
        while (TC5->COUNT16.SYNCBUSY.bit.CC0)
            ; // Wait for synchronization

        // Start Timer/Counter 5
        TC5->COUNT16.CTRLA.bit.ENABLE = 1; // Enable the TC5 timer
        while (TC5->COUNT16.SYNCBUSY.bit.ENABLE)
            ; // Wait for synchronization
    }

    uint16_t _adc_buf_0[ADC_BUF_LEN];
    uint16_t _adc_buf_1[ADC_BUF_LEN];
    ```

    Kode ini mendefinisikan metode `configureDmaAdc` yang mengonfigurasi DMAC, menghubungkannya ke ADC dan mengatur DMAC untuk mengisi dua buffer yang bergantian, `_adc_buf_0` dan `_adc_buf_1`.

    > 💁 Salah satu kekurangan pengembangan mikrokontroler adalah kompleksitas kode yang diperlukan untuk berinteraksi dengan perangkat keras, karena kode Anda berjalan pada tingkat yang sangat rendah berinteraksi langsung dengan perangkat keras. Kode ini lebih kompleks dibandingkan dengan yang Anda tulis untuk komputer papan tunggal atau komputer desktop karena tidak ada sistem operasi yang membantu. Ada beberapa pustaka yang tersedia yang dapat menyederhanakan ini, tetapi tetap ada banyak kompleksitas.

1. Di bawah ini, tambahkan kode berikut:

    ```cpp
    // WAV files have a header. This struct defines that header
    struct wavFileHeader
    {
        char riff[4];         /* "RIFF"                                  */
        long flength;         /* file length in bytes                    */
        char wave[4];         /* "WAVE"                                  */
        char fmt[4];          /* "fmt "                                  */
        long chunk_size;      /* size of FMT chunk in bytes (usually 16) */
        short format_tag;     /* 1=PCM, 257=Mu-Law, 258=A-Law, 259=ADPCM */
        short num_chans;      /* 1=mono, 2=stereo                        */
        long srate;           /* Sampling rate in samples per second     */
        long bytes_per_sec;   /* bytes per second = srate*bytes_per_samp */
        short bytes_per_samp; /* 2=16-bit mono, 4=16-bit stereo          */
        short bits_per_samp;  /* Number of bits per sample               */
        char data[4];         /* "data"                                  */
        long dlength;         /* data length in bytes (filelength - 44)  */
    };

    void initBufferHeader()
    {
        wavFileHeader wavh;

        strncpy(wavh.riff, "RIFF", 4);
        strncpy(wavh.wave, "WAVE", 4);
        strncpy(wavh.fmt, "fmt ", 4);
        strncpy(wavh.data, "data", 4);

        wavh.chunk_size = 16;
        wavh.format_tag = 1; // PCM
        wavh.num_chans = 1;  // mono
        wavh.srate = RATE;
        wavh.bytes_per_sec = (RATE * 1 * 16 * 1) / 8;
        wavh.bytes_per_samp = 2;
        wavh.bits_per_samp = 16;
        wavh.dlength = RATE * 2 * 1 * 16 / 2;
        wavh.flength = wavh.dlength + 44;

        _writer.writeSfudBuffer((byte *)&wavh, 44);
    }
    ```

    Kode ini mendefinisikan header WAV sebagai struct yang memakan 44 byte memori. Header ini menulis detail tentang tingkat file audio, ukuran, dan jumlah saluran. Header ini kemudian ditulis ke memori flash.

1. Di bawah kode ini, tambahkan berikut ini untuk mendeklarasikan metode yang akan dipanggil ketika buffer audio siap diproses:

    ```cpp
    void audioCallback(uint16_t *buf, uint32_t buf_len)
    {
        static uint32_t idx = 44;

        if (_isRecording)
        {
            for (uint32_t i = 0; i < buf_len; i++)
            {
                int16_t audio_value = ((int16_t)buf[i] - 2048) * 16;

                _writer.writeSfudBuffer(audio_value & 0xFF);
                _writer.writeSfudBuffer((audio_value >> 8) & 0xFF);
            }

            idx += buf_len;
                
            if (idx >= BUFFER_SIZE)
            {
                _writer.flushSfudBuffer();
                idx = 44;
                _isRecording = false;
                _isRecordingReady = true;
            }
        }
    }
    ```

    Buffer audio adalah array integer 16-bit yang berisi audio dari ADC. ADC mengembalikan nilai unsigned 12-bit (0-1023), sehingga nilai-nilai ini perlu dikonversi menjadi nilai signed 16-bit, dan kemudian dikonversi menjadi 2 byte untuk disimpan sebagai data biner mentah.

    Byte-byte ini ditulis ke buffer memori flash. Penulisan dimulai pada indeks 44 - ini adalah offset dari 44 byte yang ditulis sebagai header file WAV. Setelah semua byte yang diperlukan untuk panjang audio yang diperlukan telah ditangkap, data yang tersisa ditulis ke memori flash.

1. Di bagian `public` dari kelas `Mic`, tambahkan kode berikut:

    ```cpp
    void dmaHandler()
    {
        static uint8_t count = 0;

        if (DMAC->Channel[1].CHINTFLAG.bit.SUSP)
        {
            DMAC->Channel[1].CHCTRLB.reg = DMAC_CHCTRLB_CMD_RESUME;
            DMAC->Channel[1].CHINTFLAG.bit.SUSP = 1;

            if (count)
            {
                audioCallback(_adc_buf_0, ADC_BUF_LEN);
            }
            else
            {
                audioCallback(_adc_buf_1, ADC_BUF_LEN);
            }

            count = (count + 1) % 2;
        }
    }
    ```

    Kode ini akan dipanggil oleh DMAC untuk memberi tahu kode Anda bahwa buffer siap diproses. Kode ini memeriksa apakah ada data untuk diproses, dan memanggil metode `audioCallback` dengan buffer yang relevan.

1. Di luar kelas, setelah deklarasi `Mic mic;`, tambahkan kode berikut:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    `DMAC_1_Handler` akan dipanggil oleh DMAC ketika buffer siap diproses. Fungsi ini ditemukan berdasarkan nama, sehingga hanya perlu ada untuk dipanggil.

1. Tambahkan dua metode berikut ke bagian `public` dari kelas `Mic`:

    ```cpp
    void init()
    {
        analogReference(AR_INTERNAL2V23);

        _writer.init();

        initBufferHeader();
        configureDmaAdc();
    }

    void reset()
    {
        _isRecordingReady = false;
        _isRecording = false;

        _writer.reset();

        initBufferHeader();
    }
    ```

    Metode `init` berisi kode untuk menginisialisasi kelas `Mic`. Metode ini mengatur tegangan yang benar untuk pin Mic, mengatur penulis memori flash, menulis header file WAV, dan mengonfigurasi DMAC. Metode `reset` mengatur ulang memori flash dan menulis ulang header setelah audio ditangkap dan digunakan.

### Tugas - menangkap audio

1. Di file `main.cpp`, tambahkan direktif `include` untuk file header `mic.h`:

    ```cpp
    #include "mic.h"
    ```

1. Di fungsi `setup`, inisialisasi tombol C. Penangkapan audio akan dimulai ketika tombol ini ditekan, dan berlangsung selama 4 detik:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. Di bawah ini, inisialisasi mikrofon, lalu cetak ke konsol bahwa audio siap untuk ditangkap:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. Di atas fungsi `loop`, definisikan fungsi untuk memproses audio yang ditangkap. Untuk saat ini, fungsi ini tidak melakukan apa-apa, tetapi nanti dalam pelajaran ini akan mengirimkan ucapan untuk dikonversi menjadi teks:

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. Tambahkan berikut ini ke fungsi `loop`:

    ```cpp
    void loop()
    {
        if (digitalRead(WIO_KEY_C) == LOW && !mic.isRecording())
        {
            Serial.println("Starting recording...");
            mic.startRecording();
        }
    
        if (!mic.isRecording() && mic.isRecordingReady())
        {
            Serial.println("Finished recording");
    
            processAudio();
    
            mic.reset();
        }
    }
    ```

    Kode ini memeriksa tombol C, dan jika tombol ini ditekan dan perekaman belum dimulai, maka bidang `_isRecording` dari kelas `Mic` diatur ke true. Hal ini akan menyebabkan metode `audioCallback` dari kelas `Mic` menyimpan audio hingga 4 detik telah ditangkap. Setelah 4 detik audio ditangkap, bidang `_isRecording` diatur ke false, dan bidang `_isRecordingReady` diatur ke true. Bidang ini kemudian diperiksa dalam fungsi `loop`, dan ketika bernilai true, fungsi `processAudio` dipanggil, lalu kelas mic diatur ulang.

1. Bangun kode ini, unggah ke Wio Terminal Anda, dan uji melalui monitor serial. Tekan tombol C (yang ada di sisi kiri, paling dekat dengan sakelar daya), dan berbicaralah. Audio selama 4 detik akan ditangkap.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Ready.
    Starting recording...
    Finished recording
    ```
💁 Anda dapat menemukan kode ini di folder [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal).
😀 Program perekaman audio Anda berhasil!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan layanan penerjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Meskipun kami berusaha untuk memberikan hasil yang akurat, harap diingat bahwa terjemahan otomatis mungkin mengandung kesalahan atau ketidakakuratan. Dokumen asli dalam bahasa aslinya harus dianggap sebagai sumber yang otoritatif. Untuk informasi yang bersifat kritis, disarankan menggunakan jasa penerjemahan profesional oleh manusia. Kami tidak bertanggung jawab atas kesalahpahaman atau penafsiran yang keliru yang timbul dari penggunaan terjemahan ini.