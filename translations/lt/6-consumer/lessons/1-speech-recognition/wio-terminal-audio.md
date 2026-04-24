# Garso įrašymas - Wio Terminal

Šioje pamokos dalyje rašysite kodą, skirtą įrašyti garsą naudojant Wio Terminal. Garso įrašymas bus valdomas vienu iš mygtukų, esančių Wio Terminal viršuje.

## Įrenginio programavimas garso įrašymui

Garsą galite įrašyti iš mikrofono naudodami C++ kodą. Wio Terminal turi tik 192KB RAM, todėl neužtenka vietos įrašyti daugiau nei kelias sekundes garso. Tačiau jis turi 4MB „flash“ atminties, kurią galima naudoti įrašytam garsui saugoti.

Integruotas mikrofonas fiksuoja analoginį signalą, kuris konvertuojamas į skaitmeninį signalą, kurį gali naudoti Wio Terminal. Įrašant garsą, duomenys turi būti fiksuojami tinkamu laiku – pavyzdžiui, norint įrašyti garsą 16 kHz dažniu, duomenys turi būti fiksuojami tiksliai 16 000 kartų per sekundę, su vienodais intervalais tarp kiekvieno mėginio. Vietoj to, kad jūsų kodas tai atliktų, galite naudoti tiesioginės atminties prieigos valdiklį (DMAC). Tai yra grandinė, kuri gali fiksuoti signalą iš tam tikros vietos ir rašyti į atmintį, netrukdydama procesoriuje veikiančiam kodui.

✅ Daugiau apie DMA skaitykite [tiesioginės atminties prieigos puslapyje Vikipedijoje](https://wikipedia.org/wiki/Direct_memory_access).

![Garsas iš mikrofono eina į ADC, tada į DMAC. DMAC rašo į vieną buferį. Kai šis buferis užpildomas, jis apdorojamas, o DMAC rašo į antrą buferį](../../../../../translated_images/lt/dmac-adc-buffers.4509aee49145c90b.webp)

DMAC gali fiksuoti garsą iš ADC fiksuotais intervalais, pavyzdžiui, 16 000 kartų per sekundę 16 kHz garsui. Jis gali rašyti šiuos užfiksuotus duomenis į iš anksto paskirtą atminties buferį, o kai šis užpildomas, padaryti jį prieinamą jūsų kodui apdoroti. Naudojant šią atmintį gali būti vėluojama fiksuoti garsą, tačiau galite nustatyti kelis buferius. DMAC rašo į 1 buferį, tada, kai jis užpildomas, praneša jūsų kodui apdoroti 1 buferį, tuo tarpu DMAC rašo į 2 buferį. Kai 2 buferis užpildomas, jis praneša jūsų kodui ir grįžta rašyti į 1 buferį. Tokiu būdu, jei apdorojate kiekvieną buferį greičiau nei užtrunka užpildyti vieną, neprarasite jokių duomenų.

Kai kiekvienas buferis yra užfiksuotas, jis gali būti įrašytas į „flash“ atmintį. „Flash“ atmintis turi būti rašoma naudojant apibrėžtus adresus, nurodant, kur rašyti ir kokio dydžio rašyti, panašiai kaip atnaujinant baitų masyvą atmintyje. „Flash“ atmintis turi grūdėtumą, tai reiškia, kad trynimo ir rašymo operacijos priklauso ne tik nuo fiksuoto dydžio, bet ir nuo suderinimo su tuo dydžiu. Pavyzdžiui, jei grūdėtumas yra 4096 baitai ir jūs prašote ištrinti adresu 4200, tai gali ištrinti visus duomenis nuo adreso 4096 iki 8192. Tai reiškia, kad rašant garso duomenis į „flash“ atmintį, tai turi būti daroma tinkamo dydžio dalimis.

### Užduotis - „flash“ atminties konfigūravimas

1. Sukurkite naują Wio Terminal projektą naudodami PlatformIO. Pavadinkite šį projektą `smart-timer`. Pridėkite kodą `setup` funkcijoje, kad sukonfigūruotumėte nuoseklųjį prievadą.

1. Pridėkite šias bibliotekų priklausomybes į `platformio.ini` failą, kad gautumėte prieigą prie „flash“ atminties:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. Atidarykite `main.cpp` failą ir pridėkite šį įtraukimo direktyvą „flash“ atminties bibliotekai failo viršuje:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD reiškia Serial Flash Universal Driver ir yra biblioteka, skirta dirbti su visais „flash“ atminties lustais.

1. `setup` funkcijoje pridėkite šį kodą, kad nustatytumėte „flash“ saugojimo biblioteką:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    Šis kodas kartojasi, kol SFUD biblioteka yra inicializuota, tada įjungia greitą skaitymą. Integruota „flash“ atmintis gali būti pasiekiama naudojant eilės nuoseklųjį periferinį sąsają (QSPI), SPI valdiklio tipą, leidžiantį nuolatinę prieigą per eilę su minimaliu procesoriaus naudojimu. Tai leidžia greičiau skaityti ir rašyti į „flash“ atmintį.

1. Sukurkite naują failą `src` aplanke, pavadintą `flash_writer.h`.

1. Pridėkite šį kodą failo viršuje:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    Tai apima kai kuriuos reikalingus antraštinius failus, įskaitant SFUD bibliotekos antraštinį failą, skirtą sąveikai su „flash“ atmintimi.

1. Apibrėžkite klasę šiame naujame antraštiniame faile, pavadintą `FlashWriter`:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. Privačioje sekcijoje pridėkite šį kodą:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    Tai apibrėžia kai kuriuos laukus, skirtus buferiui naudoti duomenims saugoti prieš juos įrašant į „flash“ atmintį. Yra baitų masyvas `_sfudBuffer`, skirtas duomenims rašyti, o kai jis užpildomas, duomenys įrašomi į „flash“ atmintį. Laukas `_sfudBufferPos` saugo dabartinę vietą, kurioje rašoma šiame buferyje, o `_sfudBufferWritePos` saugo vietą „flash“ atmintyje, kurioje rašoma. `_flash` yra rodyklė į „flash“ atmintį, į kurią rašoma – kai kurie mikrovaldikliai turi kelis „flash“ atminties lustus.

1. Pridėkite šį metodą į viešąją sekciją, kad inicializuotumėte šią klasę:

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

    Šis metodas konfigūruoja „flash“ atmintį Wio Terminal, į kurią rašoma, ir nustato buferius pagal „flash“ atminties grūdėtumą. Tai yra `init` metode, o ne konstruktoriuje, nes jis turi būti iškviestas po to, kai „flash“ atmintis buvo nustatyta `setup` funkcijoje.

1. Pridėkite šį kodą į viešąją sekciją:

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

    Šis kodas apibrėžia metodus baitams rašyti į „flash“ saugojimo sistemą. Jis veikia rašydamas į atminties buferį, kuris yra tinkamo dydžio „flash“ atminčiai, o kai jis užpildomas, jis įrašomas į „flash“ atmintį, ištrinant bet kokius esamus duomenis toje vietoje. Taip pat yra `flushSfudBuffer`, skirtas neišsamiam buferiui įrašyti, nes fiksuojami duomenys nebus tikslūs grūdėtumo dydžio kartotiniai, todėl paskutinė duomenų dalis turi būti įrašyta.

    > 💁 Paskutinė duomenų dalis įrašys papildomus nereikalingus duomenis, tačiau tai yra gerai, nes bus skaitomi tik reikalingi duomenys.

### Užduotis - garso fiksavimo nustatymas

1. Sukurkite naują failą `src` aplanke, pavadintą `config.h`.

1. Pridėkite šį kodą failo viršuje:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    Šis kodas nustato kai kurias konstantas, skirtas garso fiksavimui.

    | Konstanta             | Reikšmė | Aprašymas |
    | --------------------- | ------: | - |
    | RATE                  | 16000   | Garso mėginių ėmimo dažnis. 16 000 yra 16 kHz |
    | SAMPLE_LENGTH_SECONDS | 4       | Garso įrašymo trukmė. Nustatyta 4 sekundėms. Norėdami įrašyti ilgesnį garsą, padidinkite šią reikšmę. |
    | SAMPLES               | 64000   | Bendras užfiksuotų garso mėginių skaičius. Nustatyta kaip mėginių ėmimo dažnis * sekundžių skaičius |
    | BUFFER_SIZE           | 128044  | Garso buferio dydis fiksavimui. Garsas bus fiksuojamas kaip WAV failas, kurio antraštė yra 44 baitai, o 128 000 baitų yra garso duomenys (kiekvienas mėginys yra 2 baitai) |
    | ADC_BUF_LEN           | 1600    | Buferių dydis, skirtas garso fiksavimui iš DMAC |

    > 💁 Jei manote, kad 4 sekundės yra per trumpas laikas laikmačiui nustatyti, galite padidinti `SAMPLE_LENGTH_SECONDS` reikšmę, ir visos kitos reikšmės bus perskaičiuotos.

1. Sukurkite naują failą `src` aplanke, pavadintą `mic.h`.

1. Pridėkite šį kodą failo viršuje:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    Tai apima kai kuriuos reikalingus antraštinius failus, įskaitant `config.h` ir `FlashWriter` antraštinius failus.

1. Pridėkite šį kodą, kad apibrėžtumėte `Mic` klasę, kuri gali fiksuoti garsą iš mikrofono:

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

    Ši klasė šiuo metu turi tik kelis laukus, skirtus stebėti, ar įrašymas pradėtas, ir ar įrašymas yra paruoštas naudoti. Kai DMAC yra nustatytas, jis nuolat rašo į atminties buferius, todėl `_isRecording` vėliavėlė nustato, ar šie buferiai turėtų būti apdorojami, ar ignoruojami. `_isRecordingReady` vėliavėlė bus nustatyta, kai bus užfiksuotos reikiamos 4 sekundės garso. Laukas `_writer` naudojamas garso duomenims saugoti „flash“ atmintyje.

    Tada deklaruojamas globalus kintamasis, skirtas `Mic` klasės egzemplioriui.

1. Pridėkite šį kodą į `Mic` klasės privačią sekciją:

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

    Šis kodas apibrėžia `configureDmaAdc` metodą, kuris konfigūruoja DMAC, prijungdamas jį prie ADC ir nustatydamas, kad jis užpildytų du skirtingus kintamuosius buferius, `_adc_buf_0` ir `_adc_buf_1`.

    > 💁 Vienas iš mikrovaldiklių kūrimo trūkumų yra sudėtingas kodas, reikalingas sąveikai su aparatine įranga, nes jūsų kodas veikia labai žemame lygyje, tiesiogiai sąveikaudamas su aparatine įranga. Šis kodas yra sudėtingesnis nei tas, kurį rašytumėte vienos plokštės kompiuteriui ar staliniam kompiuteriui, nes nėra operacinės sistemos, kuri padėtų. Yra keletas bibliotekų, kurios gali tai supaprastinti, tačiau vis tiek yra daug sudėtingumo.

1. Po šio kodo pridėkite šį kodą:

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

    Šis kodas apibrėžia WAV antraštę kaip struktūrą, kuri užima 44 baitus atminties. Ji įrašo informaciją apie garso failo dažnį, dydį ir kanalų skaičių. Ši antraštė tada įrašoma į „flash“ atmintį.

1. Po šio kodo pridėkite šį metodą, kuris bus iškviečiamas, kai garso buferiai bus paruošti apdoroti:

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

    Garso buferiai yra 16 bitų sveikųjų skaičių masyvai, kuriuose yra ADC gautas garsas. ADC grąžina 12 bitų nesirašytas reikšmes (0–1023), todėl jas reikia konvertuoti į 16 bitų pasirašytas reikšmes, o tada konvertuoti į 2 baitus, kad būtų saugomos kaip neapdoroti dvejetainiai duomenys.

    Šie baitai yra rašomi į „flash“ atminties buferius. Rašymas prasideda nuo 44 indekso – tai yra poslinkis nuo 44 baitų, įrašytų kaip WAV failo antraštė. Kai visi reikalingi baitai reikiamam garso ilgiui yra užfiksuoti, likę duomenys yra įrašomi į „flash“ atmintį.

1. Viešojoje `Mic` klasės sekcijoje pridėkite šį kodą:

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

    Šis kodas bus iškviečiamas DMAC, kad praneštų jūsų kodui apdoroti buferius. Jis patikrina, ar yra duomenų apdoroti, ir iškviečia `audioCallback` metodą su atitinkamu buferiu.

1. Už klasės, po `Mic mic;` deklaracijos, pridėkite šį kodą:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    `DMAC_1_Handler` bus iškviečiamas DMAC, kai buferiai bus paruošti apdoroti. Ši funkcija randama pagal pavadinimą, todėl tiesiog turi egzistuoti, kad būtų iškviesta.

1. Pridėkite šiuos du metodus į viešąją `Mic` klasės sekciją:

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

    `init` metodas turi kodą, skirtą inicializuoti `Mic` klasę. Šis metodas nustato tinkamą įtampą Mic pinui, nustato „flash“ atminties rašytuvą, įrašo WAV failo antraštę ir konfigūruoja DMAC. `reset` metodas iš naujo nustato „flash“ atmintį ir perrašo antraštę po to, kai garsas buvo užfiksuotas ir panaudotas.

### Užduotis - garso įrašymas

1. `main.cpp` faile pridėkite įtraukimo direktyvą `mic.h` antraštiniam failui:

    ```cpp
    #include "mic.h"
    ```

1. `setup` funkcijoje inicializuokite C mygtuką. Garso įrašymas prasidės, kai šis mygtukas bus paspaustas, ir tęsis 4 sekundes:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. Po to inicializuokite mikrofoną, tada išspausdinkite konsolėje, kad garsas yra paruoštas įrašymui:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. Virš `loop` funkcijos apibrėžkite funkciją, skirtą apdoroti užfiksuotą garsą. Šiuo metu ji nieko nedaro, tačiau vėliau šioje pamokoje ji bus naudojama kalbai konvertuoti į tekstą:

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. Pridėkite šį kodą į `loop` funkciją:

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

    Šis kodas tikrina C mygtuką, ir jei jis yra paspaustas ir įrašymas dar neprasidėjo, tada `Mic` klasės `_isRecording` laukas nustatomas į true. Tai sukels `Mic` klasės `audioCallback` metodą saugoti garsą, kol bus užfiksuotos 4 sekundės. Kai 4 sekundės garso bus užfiksuotos, `_isRecording` laukas nustatomas į false, o `_isRecordingReady` laukas nustatomas į true. Tai tada tikrinama `loop` funkcijoje, ir kai true, iškviečiama `processAudio` funkcija, tada `mic` klasė yra iš naujo nustatoma.

1. Sukurkite šį kodą, įkelkite jį į savo Wio Terminal ir išbandykite per nuoseklųjį monitorių. Paspauskite C mygtuką (esantį kairėje
💁 Šį kodą galite rasti [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal) aplanke.
😀 Jūsų garso įrašymo programa buvo sėkminga!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.