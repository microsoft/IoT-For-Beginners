<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2f336726b9410e97c3aaed76cc89b0d8",
  "translation_date": "2025-08-27T23:25:32+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-audio.md",
  "language_code": "ms"
}
-->
# Menangkap Audio - Wio Terminal

Dalam bahagian pelajaran ini, anda akan menulis kod untuk menangkap audio pada Wio Terminal anda. Penangkapan audio akan dikawal oleh salah satu butang di bahagian atas Wio Terminal.

## Programkan peranti untuk menangkap audio

Anda boleh menangkap audio dari mikrofon menggunakan kod C++. Wio Terminal hanya mempunyai 192KB RAM, yang tidak mencukupi untuk menangkap lebih daripada beberapa saat audio. Ia juga mempunyai 4MB memori flash, jadi ini boleh digunakan sebagai alternatif, dengan menyimpan audio yang ditangkap ke memori flash.

Mikrofon terbina dalam menangkap isyarat analog, yang kemudian ditukar kepada isyarat digital yang boleh digunakan oleh Wio Terminal. Semasa menangkap audio, data perlu ditangkap pada masa yang tepat - contohnya, untuk menangkap audio pada 16KHz, audio perlu ditangkap tepat 16,000 kali sesaat, dengan selang masa yang sama antara setiap sampel. Daripada menggunakan kod anda untuk melakukan ini, anda boleh menggunakan pengawal akses memori langsung (DMAC). Ini adalah litar yang boleh menangkap isyarat dari suatu tempat dan menulis ke memori, tanpa mengganggu kod anda yang sedang berjalan pada pemproses.

✅ Baca lebih lanjut tentang DMA di [halaman akses memori langsung di Wikipedia](https://wikipedia.org/wiki/Direct_memory_access).

![Audio dari mikrofon pergi ke ADC kemudian ke DMAC. DMAC menulis ke satu penimbal. Apabila penimbal ini penuh, ia diproses dan DMAC menulis ke penimbal kedua](../../../../../translated_images/ms/dmac-adc-buffers.4509aee49145c90bc2e1be472b8ed2ddfcb2b6a81ad3e559114aca55f5fff759.png)

DMAC boleh menangkap audio dari ADC pada selang masa tetap, seperti 16,000 kali sesaat untuk audio 16KHz. Ia boleh menulis data yang ditangkap ini ke penimbal memori yang telah diperuntukkan, dan apabila penuh, menjadikannya tersedia untuk kod anda untuk diproses. Menggunakan memori ini boleh melambatkan penangkapan audio, tetapi anda boleh menyediakan beberapa penimbal. DMAC menulis ke penimbal 1, kemudian apabila ia penuh, memberitahu kod anda untuk memproses penimbal 1, sementara DMAC menulis ke penimbal 2. Apabila penimbal 2 penuh, ia memberitahu kod anda, dan kembali menulis ke penimbal 1. Dengan cara ini, selagi anda memproses setiap penimbal dalam masa yang lebih singkat daripada masa yang diperlukan untuk mengisi satu, anda tidak akan kehilangan sebarang data.

Setelah setiap penimbal ditangkap, ia boleh ditulis ke memori flash. Memori flash perlu ditulis menggunakan alamat yang ditentukan, menentukan di mana untuk menulis dan berapa besar untuk ditulis, serupa dengan mengemas kini array bait dalam memori. Memori flash mempunyai granulariti, yang bermaksud operasi pemadaman dan penulisan bergantung bukan sahaja pada saiz tetap, tetapi juga penjajaran kepada saiz tersebut. Contohnya, jika granulariti adalah 4096 bait dan anda meminta pemadaman pada alamat 4200, ia boleh memadam semua data dari alamat 4096 hingga 8192. Ini bermaksud apabila anda menulis data audio ke memori flash, ia perlu dalam bahagian yang bersaiz betul.

### Tugasan - konfigurasikan memori flash

1. Buat projek Wio Terminal baru menggunakan PlatformIO. Namakan projek ini `smart-timer`. Tambahkan kod dalam fungsi `setup` untuk mengkonfigurasi port serial.

1. Tambahkan kebergantungan perpustakaan berikut ke fail `platformio.ini` untuk memberikan akses kepada memori flash:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. Buka fail `main.cpp` dan tambahkan arahan `include` berikut untuk perpustakaan memori flash di bahagian atas fail:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD bermaksud Serial Flash Universal Driver, dan merupakan perpustakaan yang direka untuk berfungsi dengan semua cip memori flash.

1. Dalam fungsi `setup`, tambahkan kod berikut untuk menyediakan perpustakaan penyimpanan flash:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    Kod ini berulang sehingga perpustakaan SFUD diinisialisasi, kemudian menghidupkan bacaan pantas. Memori flash terbina dalam boleh diakses menggunakan Queued Serial Peripheral Interface (QSPI), sejenis pengawal SPI yang membolehkan akses berterusan melalui barisan dengan penggunaan pemproses yang minimum. Ini menjadikannya lebih pantas untuk membaca dan menulis ke memori flash.

1. Buat fail baru dalam folder `src` bernama `flash_writer.h`.

1. Tambahkan yang berikut di bahagian atas fail ini:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    Kod ini termasuk beberapa fail header yang diperlukan, termasuk fail header untuk perpustakaan SFUD untuk berinteraksi dengan memori flash.

1. Tentukan kelas dalam fail header baru ini bernama `FlashWriter`:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. Dalam bahagian `private`, tambahkan kod berikut:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    Kod ini menentukan beberapa medan untuk penimbal yang digunakan untuk menyimpan data sebelum menulisnya ke memori flash. Terdapat array bait, `_sfudBuffer`, untuk menulis data, dan apabila penuh, data ditulis ke memori flash. Medan `_sfudBufferPos` menyimpan lokasi semasa untuk menulis dalam penimbal ini, dan `_sfudBufferWritePos` menyimpan lokasi dalam memori flash untuk menulis. `_flash` adalah penunjuk kepada memori flash untuk ditulis - beberapa mikrokontroler mempunyai beberapa cip memori flash.

1. Tambahkan kaedah berikut ke bahagian `public` untuk menginisialisasi kelas ini:

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

    Kod ini mengkonfigurasi memori flash pada Wio Terminal untuk ditulis, dan menyediakan penimbal berdasarkan saiz granulariti memori flash. Ini berada dalam kaedah `init`, bukan konstruktor kerana ini perlu dipanggil selepas memori flash disediakan dalam fungsi `setup`.

1. Tambahkan kod berikut ke bahagian `public`:

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

    Kod ini menentukan kaedah untuk menulis bait ke sistem penyimpanan flash. Ia berfungsi dengan menulis ke penimbal dalam memori yang bersaiz betul untuk memori flash, dan apabila penuh, ini ditulis ke memori flash, memadamkan sebarang data sedia ada di lokasi tersebut. Terdapat juga `flushSfudBuffer` untuk menulis penimbal yang tidak lengkap, kerana data yang ditangkap tidak akan menjadi gandaan tepat saiz granulariti, jadi bahagian akhir data perlu ditulis.

    > 💁 Bahagian akhir data akan menulis data tambahan yang tidak diingini, tetapi ini tidak menjadi masalah kerana hanya data yang diperlukan akan dibaca.

### Tugasan - sediakan penangkapan audio

1. Buat fail baru dalam folder `src` bernama `config.h`.

1. Tambahkan yang berikut di bahagian atas fail ini:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    Kod ini menyediakan beberapa pemalar untuk penangkapan audio.

    | Pemalar               | Nilai  | Penerangan |
    | --------------------- | -----: | - |
    | RATE                  | 16000  | Kadar sampel untuk audio. 16,000 adalah 16KHz |
    | SAMPLE_LENGTH_SECONDS | 4      | Panjang audio untuk ditangkap. Ini ditetapkan kepada 4 saat. Untuk merakam audio lebih lama, tingkatkan nilai ini. |
    | SAMPLES               | 64000  | Jumlah bilangan sampel audio yang akan ditangkap. Ditentukan oleh kadar sampel * bilangan saat |
    | BUFFER_SIZE           | 128044 | Saiz penimbal audio untuk ditangkap. Audio akan ditangkap sebagai fail WAV, yang mempunyai 44 bait header, kemudian 128,000 bait data audio (setiap sampel adalah 2 bait) |
    | ADC_BUF_LEN           | 1600   | Saiz penimbal untuk digunakan untuk menangkap audio dari DMAC |

    > 💁 Jika anda mendapati 4 saat terlalu pendek untuk meminta pemasa, anda boleh meningkatkan nilai `SAMPLE_LENGTH_SECONDS`, dan semua nilai lain akan dikira semula.

1. Buat fail baru dalam folder `src` bernama `mic.h`.

1. Tambahkan yang berikut di bahagian atas fail ini:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    Kod ini termasuk beberapa fail header yang diperlukan, termasuk fail header `config.h` dan `FlashWriter`.

1. Tambahkan yang berikut untuk menentukan kelas `Mic` yang boleh menangkap dari mikrofon:

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

    Kelas ini pada masa ini hanya mempunyai beberapa medan untuk menjejaki sama ada rakaman telah dimulakan, dan sama ada rakaman sedia untuk digunakan. Apabila DMAC disediakan, ia terus menulis ke penimbal memori, jadi bendera `_isRecording` menentukan sama ada ini perlu diproses atau diabaikan. Bendera `_isRecordingReady` akan ditetapkan apabila 4 saat audio yang diperlukan telah ditangkap. Medan `_writer` digunakan untuk menyimpan data audio ke memori flash.

    Pembolehubah global kemudian diisytiharkan untuk satu instance kelas `Mic`.

1. Tambahkan kod berikut ke bahagian `private` kelas `Mic`:

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

    Kod ini menentukan kaedah `configureDmaAdc` yang mengkonfigurasi DMAC, menyambungkannya ke ADC dan menetapkannya untuk mengisi dua penimbal bergantian, `_adc_buf_0` dan `_adc_buf_1`.

    > 💁 Salah satu kelemahan pembangunan mikrokontroler adalah kerumitan kod yang diperlukan untuk berinteraksi dengan perkakasan, kerana kod anda berjalan pada tahap yang sangat rendah berinteraksi secara langsung dengan perkakasan. Kod ini lebih kompleks daripada apa yang anda tulis untuk komputer papan tunggal atau komputer desktop kerana tiada sistem operasi untuk membantu. Terdapat beberapa perpustakaan yang tersedia yang boleh mempermudah ini, tetapi masih terdapat banyak kerumitan.

1. Di bawah ini, tambahkan kod berikut:

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

    Kod ini menentukan header WAV sebagai struktur yang mengambil 44 bait memori. Ia menulis butiran kepada header tentang kadar fail audio, saiz, dan bilangan saluran. Header ini kemudian ditulis ke memori flash.

1. Di bawah kod ini, tambahkan yang berikut untuk mengisytiharkan kaedah yang akan dipanggil apabila penimbal audio sedia untuk diproses:

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

    Penimbal audio adalah array integer 16-bit yang mengandungi audio dari ADC. ADC mengembalikan nilai tanpa tanda 12-bit (0-1023), jadi ini perlu ditukar kepada nilai bertanda 16-bit, dan kemudian ditukar kepada 2 bait untuk disimpan sebagai data binari mentah.

    Bait ini ditulis ke penimbal memori flash. Penulisan bermula pada indeks 44 - ini adalah offset dari 44 bait yang ditulis sebagai header fail WAV. Setelah semua bait yang diperlukan untuk panjang audio yang diperlukan telah ditangkap, data yang tinggal ditulis ke memori flash.

1. Dalam bahagian `public` kelas `Mic`, tambahkan kod berikut:

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

    Kod ini akan dipanggil oleh DMAC untuk memberitahu kod anda untuk memproses penimbal. Ia memeriksa bahawa terdapat data untuk diproses, dan memanggil kaedah `audioCallback` dengan penimbal yang relevan.

1. Di luar kelas, selepas deklarasi `Mic mic;`, tambahkan kod berikut:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    `DMAC_1_Handler` akan dipanggil oleh DMAC apabila penimbal sedia untuk diproses. Fungsi ini dikenalpasti melalui nama, jadi hanya perlu wujud untuk dipanggil.

1. Tambahkan dua kaedah berikut ke bahagian `public` kelas `Mic`:

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

    Kaedah `init` mengandungi kod untuk menginisialisasi kelas `Mic`. Kaedah ini menetapkan voltan yang betul untuk pin Mic, menyediakan penulis memori flash, menulis header fail WAV, dan mengkonfigurasi DMAC. Kaedah `reset` menetapkan semula memori flash dan menulis semula header selepas audio ditangkap dan digunakan.

### Tugasan - menangkap audio

1. Dalam fail `main.cpp`, tambahkan arahan `include` untuk fail header `mic.h`:

    ```cpp
    #include "mic.h"
    ```

1. Dalam fungsi `setup`, inisialisasi butang C. Penangkapan audio akan bermula apabila butang ini ditekan, dan berterusan selama 4 saat:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. Di bawah ini, inisialisasi mikrofon, kemudian cetak ke konsol bahawa audio sedia untuk ditangkap:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. Di atas fungsi `loop`, tentukan fungsi untuk memproses audio yang ditangkap. Buat masa ini fungsi ini tidak melakukan apa-apa, tetapi nanti dalam pelajaran ini ia akan menghantar ucapan untuk ditukar kepada teks:

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. Tambahkan yang berikut ke fungsi `loop`:

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

    Kod ini memeriksa butang C, dan jika ini ditekan dan rakaman belum dimulakan, maka medan `_isRecording` kelas `Mic` ditetapkan kepada true. Ini akan menyebabkan kaedah `audioCallback` kelas `Mic` menyimpan audio sehingga 4 saat telah ditangkap. Setelah 4 saat audio ditangkap, medan `_isRecording` ditetapkan kepada false, dan medan `_isRecordingReady` ditetapkan kepada true. Ini kemudian diperiksa dalam fungsi `loop`, dan apabila true fungsi `processAudio` dipanggil, kemudian kelas mic ditetapkan semula.

1. Bina kod ini, muat naik ke Wio Terminal anda dan uji melalui monitor serial. Tekan butang C (yang di sebelah kiri, paling dekat dengan suis kuasa), dan bercakap. 4 saat audio akan ditangkap.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Ready.
    Starting recording...
    Finished recording
    ```
💁 Anda boleh menemui kod ini dalam folder [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal).
😀 Program rakaman audio anda berjaya!

---

**Penafian**:  
Dokumen ini telah diterjemahkan menggunakan perkhidmatan terjemahan AI [Co-op Translator](https://github.com/Azure/co-op-translator). Walaupun kami berusaha untuk memastikan ketepatan, sila ambil perhatian bahawa terjemahan automatik mungkin mengandungi kesilapan atau ketidaktepatan. Dokumen asal dalam bahasa asalnya harus dianggap sebagai sumber yang berwibawa. Untuk maklumat penting, terjemahan manusia profesional adalah disyorkan. Kami tidak bertanggungjawab atas sebarang salah faham atau salah tafsir yang timbul daripada penggunaan terjemahan ini.