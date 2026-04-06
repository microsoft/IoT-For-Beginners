# Tallenna ääntä - Wio Terminal

Tässä oppitunnin osassa kirjoitat koodia äänen tallentamiseen Wio Terminal -laitteellasi. Äänen tallennusta ohjataan yhdellä Wio Terminalin yläosassa olevista painikkeista.

## Ohjelmoi laite tallentamaan ääntä

Voit tallentaa ääntä mikrofonista C++-koodilla. Wio Terminalissa on vain 192KB RAM-muistia, mikä ei riitä tallentamaan kuin muutaman sekunnin ääntä. Siinä on kuitenkin 4MB flash-muistia, jota voidaan käyttää tallentamalla ääni flash-muistiin.

Sisäänrakennettu mikrofoni tallentaa analogisen signaalin, joka muunnetaan digitaaliseksi signaaliksi, jota Wio Terminal voi käyttää. Kun ääntä tallennetaan, tiedot on tallennettava oikeaan aikaan – esimerkiksi 16 kHz:n äänen tallentamiseksi ääni on tallennettava tarkalleen 16 000 kertaa sekunnissa, tasaisin välein jokaisen näytteen välillä. Sen sijaan, että koodisi hoitaisi tämän, voit käyttää suoran muistin pääsyn ohjainta (DMAC). Tämä on piiri, joka voi tallentaa signaalin jostain ja kirjoittaa sen muistiin keskeyttämättä prosessorilla ajettavaa koodiasi.

✅ Lue lisää DMA:sta [Wikipedia-artikkelista suorasta muistin pääsystä](https://wikipedia.org/wiki/Direct_memory_access).

![Ääni mikrofonista menee ADC:n kautta DMAC:lle. Tämä kirjoittaa yhteen puskuriin. Kun tämä puskuri on täynnä, se käsitellään ja DMAC kirjoittaa toiseen puskuriin](../../../../../translated_images/fi/dmac-adc-buffers.4509aee49145c90b.webp)

DMAC voi tallentaa ääntä ADC:ltä kiintein välein, esimerkiksi 16 000 kertaa sekunnissa 16 kHz:n ääntä varten. Se voi kirjoittaa nämä tallennetut tiedot ennalta varattuun muistipuskuriin, ja kun tämä on täynnä, se ilmoittaa koodillesi, että puskuri on valmis käsiteltäväksi. Tämän muistin käyttö voi viivästyttää äänen tallennusta, mutta voit asettaa useita puskureita. DMAC kirjoittaa puskuriin 1, ja kun se on täynnä, se ilmoittaa koodillesi käsitellä puskuri 1, samalla kun DMAC kirjoittaa puskuriin 2. Kun puskuri 2 on täynnä, se ilmoittaa koodillesi ja palaa kirjoittamaan puskuriin 1. Näin kauan kuin käsittelet jokaisen puskurin nopeammin kuin sen täyttymiseen kuluva aika, et menetä mitään tietoja.

Kun jokainen puskuri on tallennettu, se voidaan kirjoittaa flash-muistiin. Flash-muistiin on kirjoitettava määritellyillä osoitteilla, jotka määrittävät, mihin kirjoitetaan ja kuinka paljon kirjoitetaan, mikä on samanlaista kuin tavutaulukon päivittäminen muistissa. Flash-muistilla on rakeisuus, mikä tarkoittaa, että tyhjennys- ja kirjoitustoiminnot eivät perustu vain kiinteään kokoon, vaan myös kohdistuvat siihen kokoon. Esimerkiksi, jos rakeisuus on 4096 tavua ja pyydät tyhjennystä osoitteessa 4200, se voi tyhjentää kaikki tiedot osoitteista 4096–8192. Tämä tarkoittaa, että kun kirjoitat äänitiedot flash-muistiin, niiden on oltava oikean kokoisissa paloissa.

### Tehtävä - konfiguroi flash-muisti

1. Luo uusi Wio Terminal -projekti PlatformIO:lla. Nimeä tämä projekti `smart-timer`. Lisää koodia `setup`-funktioon sarjaportin konfiguroimiseksi.

1. Lisää seuraavat kirjastoriippuvuudet `platformio.ini`-tiedostoon, jotta saat pääsyn flash-muistiin:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. Avaa `main.cpp`-tiedosto ja lisää seuraava `include`-direktiivi flash-muistikirjastolle tiedoston alkuun:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD tarkoittaa Serial Flash Universal Driveria, ja se on kirjasto, joka on suunniteltu toimimaan kaikkien flash-muistisirujen kanssa.

1. Lisää `setup`-funktioon seuraava koodi flash-muistikirjaston alustamiseksi:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    Tämä silmukoi, kunnes SFUD-kirjasto on alustettu, ja kytkee sitten päälle nopean lukemisen. Sisäänrakennettuun flash-muistiin pääsee Queued Serial Peripheral Interface (QSPI) -liitännän kautta, joka on eräänlainen SPI-ohjain, joka mahdollistaa jatkuvan pääsyn jonon kautta minimaalisella prosessorin käytöllä. Tämä tekee flash-muistin lukemisesta ja kirjoittamisesta nopeampaa.

1. Luo uusi tiedosto `src`-kansioon nimeltä `flash_writer.h`.

1. Lisää tämän tiedoston alkuun seuraava:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    Tämä sisältää tarvittavat otsikkotiedostot, mukaan lukien SFUD-kirjaston otsikkotiedoston flash-muistin kanssa vuorovaikuttamista varten.

1. Määritä uusi luokka nimeltä `FlashWriter` tässä otsikkotiedostossa:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. Lisää `private`-osioon seuraava koodi:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    Tämä määrittää kenttiä puskurille, jota käytetään tietojen tallentamiseen ennen niiden kirjoittamista flash-muistiin. Siinä on tavutaulukko, `_sfudBuffer`, johon tiedot kirjoitetaan, ja kun tämä on täynnä, tiedot kirjoitetaan flash-muistiin. Kenttä `_sfudBufferPos` tallentaa nykyisen sijainnin, johon kirjoitetaan tässä puskurissa, ja `_sfudBufferWritePos` tallentaa sijainnin flash-muistissa, johon kirjoitetaan. `_flash` on osoitin flash-muistiin, johon kirjoitetaan – joissakin mikrokontrollereissa on useita flash-muistisiruja.

1. Lisää seuraava metodi `public`-osioon tämän luokan alustamiseksi:

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

    Tämä konfiguroi Wio Terminalin flash-muistin kirjoittamista varten ja asettaa puskurit flash-muistin rakeisuuden perusteella. Tämä on `init`-metodissa, eikä konstruktorissa, koska tämä on kutsuttava sen jälkeen, kun flash-muisti on alustettu `setup`-funktiossa.

1. Lisää seuraava koodi `public`-osioon:

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

    Tämä koodi määrittää metodit tavujen kirjoittamiseen flash-muistijärjestelmään. Se toimii kirjoittamalla muistipuskuriin, joka on oikean kokoinen flash-muistille, ja kun tämä on täynnä, se kirjoitetaan flash-muistiin, tyhjentäen kaikki olemassa olevat tiedot kyseisestä sijainnista. Mukana on myös `flushSfudBuffer`, joka kirjoittaa epätäydellisen puskurin, koska tallennettavat tiedot eivät ole tarkkoja rakeisuuden monikertoja, joten tiedon loppuosa on kirjoitettava.

    > 💁 Tiedon loppuosa kirjoittaa ylimääräisiä ei-toivottuja tietoja, mutta tämä on ok, koska vain tarvittavat tiedot luetaan.

### Tehtävä - aseta äänen tallennus

1. Luo uusi tiedosto `src`-kansioon nimeltä `config.h`.

1. Lisää tämän tiedoston alkuun seuraava:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    Tämä koodi määrittää joitakin vakioita äänen tallennusta varten.

    | Vakio                 | Arvo   | Kuvaus |
    | --------------------- | -----: | - |
    | RATE                  | 16000  | Äänen näytteenottotaajuus. 16 000 on 16 kHz |
    | SAMPLE_LENGTH_SECONDS | 4      | Tallennettavan äänen pituus sekunteina. Tämä on asetettu 4 sekuntiin. Jos haluat tallentaa pidempään, lisää tätä arvoa. |
    | SAMPLES               | 64000  | Tallennettavien ääninäytteiden kokonaismäärä. Asetettu näytteenottotaajuus * sekuntien määrä |
    | BUFFER_SIZE           | 128044 | Äänipuskurin koko tallennusta varten. Ääni tallennetaan WAV-tiedostona, jossa on 44 tavun otsikko ja 128 000 tavua äänidataa (jokainen näyte on 2 tavua) |
    | ADC_BUF_LEN           | 1600   | Puskureiden koko äänen tallentamiseen DMAC:lla |

    > 💁 Jos huomaat, että 4 sekuntia on liian lyhyt ajastimen pyytämiseen, voit kasvattaa `SAMPLE_LENGTH_SECONDS`-arvoa, ja kaikki muut arvot lasketaan uudelleen.

1. Luo uusi tiedosto `src`-kansioon nimeltä `mic.h`.

1. Lisää tämän tiedoston alkuun seuraava:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    Tämä sisältää tarvittavat otsikkotiedostot, mukaan lukien `config.h`- ja `FlashWriter`-otsikkotiedostot.

1. Lisää seuraava määrittääksesi `Mic`-luokan, joka voi tallentaa mikrofonista:

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

    Tämä luokka sisältää tällä hetkellä vain muutaman kentän, joilla seurataan, onko tallennus alkanut ja onko tallennus valmis käytettäväksi. Kun DMAC on asetettu, se kirjoittaa jatkuvasti muistipuskureihin, joten `_isRecording`-lippu määrittää, pitäisikö näitä käsitellä vai ohittaa. `_isRecordingReady`-lippu asetetaan, kun tarvittavat 4 sekuntia ääntä on tallennettu. `_writer`-kenttää käytetään tallentamaan äänidata flash-muistiin.

    Globaalimuuttuja määritellään sitten `Mic`-luokan instanssille.

1. Lisää seuraava koodi `Mic`-luokan `private`-osioon:

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

    Tämä koodi määrittää `configureDmaAdc`-metodin, joka konfiguroi DMAC:n, yhdistää sen ADC:hen ja asettaa sen täyttämään kaksi vuorottelevaa puskuriä, `_adc_buf_0` ja `_adc_buf_1`.

    > 💁 Yksi mikrokontrollerikehityksen haitoista on monimutkainen koodi, jota tarvitaan laitteiston kanssa vuorovaikuttamiseen, koska koodisi toimii hyvin matalalla tasolla suoraan laitteiston kanssa. Tämä koodi on monimutkaisempaa kuin mitä kirjoittaisit yksikorttitietokoneelle tai pöytätietokoneelle, koska käyttöjärjestelmä ei auta. Joitakin kirjastoja on saatavilla tämän yksinkertaistamiseksi, mutta monimutkaisuutta on silti paljon.

1. Tämän alapuolelle lisää seuraava koodi:

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

    Tämä koodi määrittää WAV-otsikon rakenteena, joka vie 44 tavua muistia. Se kirjoittaa siihen tiedot äänitiedoston taajuudesta, koosta ja kanavien määrästä. Tämä otsikko kirjoitetaan sitten flash-muistiin.

1. Tämän koodin alapuolelle lisää seuraava metodi, joka kutsutaan, kun äänipuskurit ovat valmiita käsiteltäväksi:

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

    Äänipuskurit ovat 16-bittisten kokonaislukujen taulukoita, jotka sisältävät ADC:ltä saadun äänen. ADC palauttaa 12-bittisiä allekirjoittamattomia arvoja (0–1023), joten nämä on muunnettava 16-bittisiksi allekirjoitetuiksi arvoiksi ja sitten muunnettava 2 tavuksi, jotta ne voidaan tallentaa raakana binääridatana.

    Nämä tavut kirjoitetaan flash-muistipuskureihin. Kirjoitus alkaa indeksistä 44 – tämä on WAV-tiedoston otsikkona kirjoitettujen 44 tavun siirtymä. Kun kaikki tarvittavat näytteet äänen pituudelle on tallennettu, jäljellä olevat tiedot kirjoitetaan flash-muistiin.

1. Lisää `Mic`-luokan `public`-osioon seuraava koodi:

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

    Tämä koodi kutsutaan DMAC:n toimesta, kun puskureita on käsiteltävänä. Se tarkistaa, että käsiteltävää dataa on, ja kutsuu `audioCallback`-metodia oikealla puskurilla.

1. Luokan ulkopuolella, `Mic mic;`-määrittelyn jälkeen, lisää seuraava koodi:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    `DMAC_1_Handler` kutsutaan DMAC:n toimesta, kun puskureita on valmiina käsiteltäväksi. Tämä funktio löytyy nimen perusteella, joten sen tarvitsee vain olla olemassa, jotta sitä voidaan kutsua.

1. Lisää seuraavat kaksi metodia `Mic`-luokan `public`-osioon:

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

    `init`-metodi sisältää koodin `Mic`-luokan alustamiseen. Tämä metodi asettaa oikean jännitteen Mic-pinnille, alustaa flash-muistikirjoittimen, kirjoittaa WAV-tiedoston otsikon ja konfiguroi DMAC:n. `reset`-metodi nollaa flash-muistin ja kirjoittaa otsikon uudelleen sen jälkeen, kun ääni on tallennettu ja käytetty.

### Tehtävä - tallenna ääntä

1. Lisää `main.cpp`-tiedostoon `mic.h`-otsikkotiedoston `include`-direktiivi:

    ```cpp
    #include "mic.h"
    ```

1. Lisää `setup`-funktioon C-painikkeen alustaminen. Äänen tallennus alkaa, kun tätä painiketta painetaan, ja jatkuu 4 sekuntia:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. Tämän alapuolelle alusta mikrofoni ja tulosta konsoliin, että ääni on valmis tallennettavaksi:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. Lisää `loop`-funktion yläpuolelle funktio tallennetun äänen käsittelemiseksi. Tällä hetkellä tämä ei tee mitään, mutta myöhemmin tässä oppitunnissa se lähettää puheen tekstiksi muunnettavaksi:

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. Lisää seuraava `loop`-funktioon:

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

    Tämä koodi tarkistaa C-painikkeen, ja jos sitä painetaan eikä tallennus ole alkanut, `Mic`-luokan `_isRecording`-kenttä asetetaan todeksi. Tämä saa `Mic`-luokan `audioCallback`-metodin tallentamaan ääntä, kunnes 4 sekuntia on tallennettu. Kun 4 sekuntia ääntä on tallennettu, `_isRecording`-kenttä asetetaan epätodeksi ja `_isRecordingReady`-kenttä asetetaan todeksi. Tätä tarkistetaan `loop`-funktiossa, ja kun se on tosi, kutsutaan `processAudio`-funktiota ja sitten `mic`-luokka nollataan.

1. Käännä tämä koodi, lataa se Wio Terminal -laitteeseesi ja testaa se sarjamonitorin kautta. Paina C-painiketta (vasemmalla puolella, lähimpänä virtakytkintä) ja puhu. 4 sekuntia ääntä tallennetaan.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Ready.
    Starting recording...
    Finished recording
    ```
> 💁 Löydät tämän koodin [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal) -kansiosta.
😀 Äänitysohjelmasi oli menestys!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.