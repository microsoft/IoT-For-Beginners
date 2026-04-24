# Ses Kaydetme - Wio Terminal

Bu dersin bu bölümünde, Wio Terminal'inizde ses kaydetmek için kod yazacaksınız. Ses kaydı, Wio Terminal'in üst kısmındaki düğmelerden biriyle kontrol edilecektir.

## Cihazı ses kaydetmek için programlama

Mikrofondan ses kaydetmek için C++ kodu kullanabilirsiniz. Wio Terminal yalnızca 192KB RAM'e sahiptir, bu da birkaç saniyeden fazla ses kaydetmek için yeterli değildir. Ancak 4MB flash belleği vardır, bu nedenle kaydedilen ses flash belleğe kaydedilebilir.

Dahili mikrofon, analog bir sinyal yakalar ve bu sinyal, Wio Terminal'in kullanabileceği dijital bir sinyale dönüştürülür. Ses kaydederken, verilerin doğru zamanda yakalanması gerekir - örneğin, 16KHz'de ses kaydetmek için sesin saniyede tam olarak 16.000 kez, her örnek arasında eşit aralıklarla yakalanması gerekir. Bunu yapmak için kodunuzu kullanmak yerine, doğrudan bellek erişim denetleyicisini (DMAC) kullanabilirsiniz. Bu, bir sinyali bir yerden yakalayıp belleğe yazabilen ve işlemcide çalışan kodunuzu kesintiye uğratmayan bir devredir.

✅ DMA hakkında daha fazla bilgi için [Wikipedia'daki doğrudan bellek erişimi sayfasını](https://wikipedia.org/wiki/Direct_memory_access) okuyun.

![Mikrofondan gelen ses ADC'ye, ardından DMAC'ye gider. Bu, bir arabelleğe yazar. Bu arabellek dolduğunda işlenir ve DMAC ikinci bir arabelleğe yazar](../../../../../translated_images/tr/dmac-adc-buffers.4509aee49145c90b.webp)

DMAC, ADC'den sabit aralıklarla ses yakalayabilir, örneğin 16KHz ses için saniyede 16.000 kez. Bu yakalanan verileri önceden ayrılmış bir bellek arabelleğine yazabilir ve bu dolduğunda, işlenmesi için kodunuza sunabilir. Bu belleği kullanmak ses kaydını geciktirebilir, ancak birden fazla arabellek ayarlayabilirsiniz. DMAC, arabellek 1'e yazar, ardından bu dolduğunda, kodunuza arabellek 1'i işlemesi için bildirimde bulunur ve DMAC arabellek 2'ye yazar. Arabellek 2 dolduğunda, kodunuza bildirimde bulunur ve tekrar arabellek 1'e yazmaya başlar. Bu şekilde, her bir arabelleği doldurmak için geçen süreden daha kısa sürede işlerseniz, hiçbir veri kaybetmezsiniz.

Her bir arabellek yakalandıktan sonra, flash belleğe yazılabilir. Flash belleğe, nereye yazılacağını ve ne kadar yazılacağını belirten tanımlı adresler kullanılarak yazılması gerekir; bu, bellekte bir bayt dizisini güncellemeye benzer. Flash belleğin granülerliği vardır, bu da silme ve yazma işlemlerinin yalnızca sabit bir boyutta olmasına değil, aynı zamanda bu boyuta hizalanmasına bağlı olduğu anlamına gelir. Örneğin, granülerlik 4096 bayt ise ve adres 4200'de bir silme işlemi isterseniz, bu 4096 ile 8192 adresleri arasındaki tüm verileri silebilir. Bu, ses verilerini flash belleğe yazarken doğru boyuttaki parçalara bölünmesi gerektiği anlamına gelir.

### Görev - Flash belleği yapılandırma

1. PlatformIO kullanarak yeni bir Wio Terminal projesi oluşturun. Bu projeye `smart-timer` adını verin. `setup` fonksiyonuna seri portu yapılandırmak için kod ekleyin.

1. Flash belleğe erişim sağlamak için aşağıdaki kütüphane bağımlılıklarını `platformio.ini` dosyasına ekleyin:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. `main.cpp` dosyasını açın ve dosyanın en üstüne flash bellek kütüphanesi için aşağıdaki include yönergesini ekleyin:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD, Seri Flash Evrensel Sürücü anlamına gelir ve tüm flash bellek çipleriyle çalışmak üzere tasarlanmış bir kütüphanedir.

1. `setup` fonksiyonunda, flash depolama kütüphanesini ayarlamak için aşağıdaki kodu ekleyin:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    Bu, SFUD kütüphanesi başlatılana kadar döngü yapar, ardından hızlı okuma işlemlerini etkinleştirir. Dahili flash bellek, bir Kuyruklu Seri Çevresel Arayüz (QSPI) kullanılarak erişilebilir; bu, bir kuyruğu kullanarak sürekli erişime izin veren ve işlemci kullanımını en aza indiren bir SPI denetleyicisidir. Bu, flash belleği okumayı ve yazmayı daha hızlı hale getirir.

1. `src` klasöründe `flash_writer.h` adında yeni bir dosya oluşturun.

1. Bu dosyanın en üstüne aşağıdakileri ekleyin:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    Bu, flash bellekle etkileşim kurmak için SFUD kütüphanesi için başlık dosyası da dahil olmak üzere bazı gerekli başlık dosyalarını içerir.

1. Bu yeni başlık dosyasında `FlashWriter` adında bir sınıf tanımlayın:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. `private` bölümüne aşağıdaki kodu ekleyin:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    Bu, flash belleğe yazmadan önce verileri depolamak için kullanılacak arabellek için bazı alanları tanımlar. `_sfudBuffer` adlı bir bayt dizisi, verileri yazmak için kullanılır ve bu dolduğunda, veriler flash belleğe yazılır. `_sfudBufferPos` alanı, bu arabellekte yazılacak mevcut konumu saklar ve `_sfudBufferWritePos` flash bellekte yazılacak konumu saklar. `_flash`, yazılacak flash belleğe işaret eden bir işaretçidir - bazı mikrodenetleyiciler birden fazla flash bellek çipine sahiptir.

1. Bu sınıfı başlatmak için `public` bölümüne aşağıdaki yöntemi ekleyin:

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

    Bu, Wio Terminal'deki flash belleği yazmak için yapılandırır ve flash belleğin tane boyutuna göre arabellekleri ayarlar. Bu, bir kurucu yerine bir `init` yöntemi olarak yapılır çünkü bu, flash bellek `setup` fonksiyonunda ayarlandıktan sonra çağrılmalıdır.

1. `public` bölümüne aşağıdaki kodu ekleyin:

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

    Bu kod, baytları flash depolama sistemine yazmak için yöntemler tanımlar. Bu, flash bellek için doğru boyutta olan bir bellek arabelleğine yazılarak çalışır ve bu dolduğunda, bu flash belleğe yazılır ve o konumdaki mevcut veriler silinir. Ayrıca, eksik bir arabelleği yazmak için bir `flushSfudBuffer` yöntemi vardır, çünkü yakalanan veriler tane boyutunun tam katları olmayacaktır, bu nedenle verilerin son kısmı yazılmalıdır.

    > 💁 Verilerin son kısmı, istenmeyen ek veriler yazacaktır, ancak bu sorun değildir çünkü yalnızca gereken veriler okunacaktır.

### Görev - Ses kaydını ayarlama

1. `src` klasöründe `config.h` adında yeni bir dosya oluşturun.

1. Bu dosyanın en üstüne aşağıdakileri ekleyin:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    Bu kod, ses kaydı için bazı sabitleri ayarlar.

    | Sabit                | Değer  | Açıklama |
    | --------------------- | -----: | - |
    | RATE                  | 16000  | Ses için örnekleme oranı. 16.000, 16KHz'dir |
    | SAMPLE_LENGTH_SECONDS | 4      | Kaydedilecek sesin uzunluğu. Bu, 4 saniye olarak ayarlanmıştır. Daha uzun ses kaydetmek için bunu artırabilirsiniz. |
    | SAMPLES               | 64000  | Kaydedilecek toplam ses örneği sayısı. Örnekleme oranı * saniye sayısı olarak ayarlanır |
    | BUFFER_SIZE           | 128044 | Sesin yakalanacağı arabellek boyutu. Ses bir WAV dosyası olarak yakalanacaktır, bu da 44 bayt başlık ve ardından 128.000 bayt ses verisi (her örnek 2 bayttır) içerir |
    | ADC_BUF_LEN           | 1600   | DMAC'den ses yakalamak için kullanılacak arabelleklerin boyutu |

    > 💁 Eğer 4 saniye bir zamanlayıcı istemek için çok kısa gelirse, `SAMPLE_LENGTH_SECONDS` değerini artırabilirsiniz ve diğer tüm değerler yeniden hesaplanacaktır.

1. `src` klasöründe `mic.h` adında yeni bir dosya oluşturun.

1. Bu dosyanın en üstüne aşağıdakileri ekleyin:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    Bu, bazı gerekli başlık dosyalarını içerir, bunlar arasında `config.h` ve `FlashWriter` başlık dosyaları da vardır.

1. Mikrofondan yakalama yapabilen bir `Mic` sınıfını tanımlamak için aşağıdakileri ekleyin:

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

    Bu sınıf şu anda yalnızca kaydın başlatılıp başlatılmadığını ve bir kaydın kullanıma hazır olup olmadığını izlemek için birkaç alana sahiptir. DMAC ayarlandığında, sürekli olarak bellek arabelleklerine yazar, bu nedenle `_isRecording` bayrağı, bunların işlenip işlenmeyeceğini belirler. `_isRecordingReady` bayrağı, gerekli 4 saniyelik ses kaydedildiğinde ayarlanır. `_writer` alanı, ses verilerini flash belleğe kaydetmek için kullanılır.

    Daha sonra `Mic` sınıfının bir örneği için bir global değişken tanımlanır.

1. `Mic` sınıfının `private` bölümüne aşağıdaki kodu ekleyin:

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

    Bu kod, DMAC'yi yapılandıran bir `configureDmaAdc` yöntemi tanımlar, bunu ADC'ye bağlar ve `_adc_buf_0` ve `_adc_buf_1` adlı iki farklı alternatif arabelleği dolduracak şekilde ayarlar.

    > 💁 Mikrodenetleyici geliştirme, donanımla doğrudan etkileşim kuran kod yazmayı gerektirdiği için karmaşıktır. Bu kod, bir tek kartlı bilgisayar veya masaüstü bilgisayar için yazacağınızdan daha karmaşıktır çünkü yardımcı olacak bir işletim sistemi yoktur. Bu süreci basitleştiren bazı kütüphaneler mevcuttur, ancak yine de karmaşıklık vardır.

1. Bunun altına aşağıdaki kodu ekleyin:

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

    Bu kod, 44 baytlık bir bellek alanı kaplayan bir WAV başlığını bir yapı olarak tanımlar. Ses dosyası oranı, boyutu ve kanal sayısı gibi ayrıntıları bu başlığa yazar. Bu başlık daha sonra flash belleğe yazılır.

1. Bu kodun altına, ses arabellekleri işlenmeye hazır olduğunda çağrılacak bir yöntemi bildirmek için aşağıdakileri ekleyin:

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

    Ses arabellekleri, ADC'den gelen sesi içeren 16 bitlik tamsayı dizileridir. ADC, 12 bitlik işaretsiz değerler (0-1023) döndürür, bu nedenle bunların 16 bitlik işaretli değerlere dönüştürülmesi ve ardından ham ikili veri olarak saklanacak 2 bayta dönüştürülmesi gerekir.

    Bu baytlar, flash bellek arabelleklerine yazılır. Yazma işlemi, WAV dosyası başlığı olarak yazılan 44 baytlık ofsetten başlar. Gerekli ses uzunluğu için gereken tüm baytlar yakalandığında, kalan veriler flash belleğe yazılır.

1. `Mic` sınıfının `public` bölümüne aşağıdaki kodu ekleyin:

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

    Bu kod, DMAC tarafından arabelleklerin işlenmesi için kodunuza bilgi vermek için çağrılır. İşlenecek veri olup olmadığını kontrol eder ve ilgili arabellekle `audioCallback` yöntemini çağırır.

1. Sınıfın dışında, `Mic mic;` bildiriminin ardından aşağıdaki kodu ekleyin:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    `DMAC_1_Handler`, arabelleklerin işlenmeye hazır olduğu durumlarda DMAC tarafından çağrılacaktır. Bu işlev, adıyla bulunur, bu nedenle yalnızca var olması yeterlidir.

1. `Mic` sınıfının `public` bölümüne aşağıdaki iki yöntemi ekleyin:

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

    `init` yöntemi, `Mic` sınıfını başlatmak için kod içerir. Bu yöntem, Mic pininin doğru voltajını ayarlar, flash bellek yazıcısını ayarlar, WAV dosyası başlığını yazar ve DMAC'yi yapılandırır. `reset` yöntemi, ses kaydedilip kullanıldıktan sonra flash belleği sıfırlar ve başlığı yeniden yazar.

### Görev - Ses kaydetme

1. `main.cpp` dosyasında, `mic.h` başlık dosyası için bir include yönergesi ekleyin:

    ```cpp
    #include "mic.h"
    ```

1. `setup` fonksiyonunda, C düğmesini başlatın. Ses kaydı, bu düğmeye basıldığında başlayacak ve 4 saniye boyunca devam edecektir:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. Bunun altına, mikrofonu başlatın ve ardından sesin kaydedilmeye hazır olduğunu konsola yazdırın:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. `loop` fonksiyonunun üstüne, yakalanan sesi işlemek için bir işlev tanımlayın. Şimdilik bu işlev hiçbir şey yapmaz, ancak bu dersin ilerleyen bölümlerinde konuşmayı metne dönüştürmek için kullanılacaktır:

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. `loop` fonksiyonuna aşağıdakileri ekleyin:

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

    Bu kod, C düğmesini kontrol eder ve bu düğmeye basılmışsa ve kayıt başlamamışsa, `Mic` sınıfının `_isRecording` alanını true olarak ayarlar. Bu, `Mic` sınıfının `audioCallback` yönteminin 4 saniye boyunca ses depolamasına neden olur. 4 saniyelik ses kaydedildiğinde, `_isRecording` alanı false olarak ayarlanır ve `_isRecordingReady` alanı true olarak ayarlanır. Bu, `loop` fonksiyonunda kontrol edilir ve true olduğunda `processAudio` işlevi çağrılır, ardından mic sınıfı sıfırlanır.

1. Bu kodu derleyin, Wio Terminal'inize yükleyin ve seri monitör üzerinden test edin. C düğmesine (sol tarafta, güç anahtarına en yakın olan düğme) basın ve konuşun. 4 saniyelik ses kaydedilecektir.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Ready.
    Starting recording...
    Finished recording
    ```
💁 Bu kodu [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal) klasöründe bulabilirsiniz.
😀 Ses kaydı programınız başarılı oldu!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalardan sorumlu değiliz.