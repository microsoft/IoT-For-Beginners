# Zajem zvoka - Wio Terminal

V tem delu lekcije boste napisali kodo za zajem zvoka na vašem Wio Terminalu. Zajem zvoka bo nadzorovan z enim od gumbov na vrhu Wio Terminala.

## Programiranje naprave za zajem zvoka

Zvok lahko zajamete z mikrofona z uporabo kode v jeziku C++. Wio Terminal ima le 192 KB RAM-a, kar ni dovolj za zajem več kot nekaj sekund zvoka. Ima pa tudi 4 MB flash pomnilnika, ki ga lahko uporabite za shranjevanje zajetega zvoka.

Vgrajeni mikrofon zajema analogni signal, ki se pretvori v digitalni signal, ki ga lahko uporabi Wio Terminal. Pri zajemu zvoka je treba podatke zajeti ob pravem času - na primer, če želite zajeti zvok pri 16 kHz, je treba zvok zajeti natanko 16.000-krat na sekundo, z enakimi intervali med vzorci. Namesto da bi vaša koda to počela, lahko uporabite krmilnik za neposreden dostop do pomnilnika (DMAC). To je vezje, ki lahko zajame signal od nekod in ga zapiše v pomnilnik, ne da bi prekinilo izvajanje vaše kode na procesorju.

✅ Preberite več o DMA na [strani o neposrednem dostopu do pomnilnika na Wikipediji](https://wikipedia.org/wiki/Direct_memory_access).

![Zvok iz mikrofona gre v ADC, nato v DMAC. Ta piše v en medpomnilnik. Ko je ta poln, se obdela, DMAC pa piše v drugi medpomnilnik](../../../../../translated_images/sl/dmac-adc-buffers.4509aee49145c90b.webp)

DMAC lahko zajame zvok iz ADC-ja v fiksnih intervalih, na primer 16.000-krat na sekundo za zvok pri 16 kHz. Zajete podatke lahko zapiše v vnaprej dodeljen pomnilniški medpomnilnik, in ko je ta poln, jih vaša koda lahko obdela. Uporaba tega pomnilnika lahko povzroči zamudo pri zajemu zvoka, vendar lahko nastavite več medpomnilnikov. DMAC piše v medpomnilnik 1, nato pa, ko je ta poln, obvesti vašo kodo, da obdela medpomnilnik 1, medtem ko DMAC piše v medpomnilnik 2. Ko je medpomnilnik 2 poln, obvesti vašo kodo in se vrne k pisanju v medpomnilnik 1. Na ta način, dokler obdelate vsak medpomnilnik v krajšem času, kot je potreben za polnjenje enega, ne boste izgubili nobenih podatkov.

Ko je vsak medpomnilnik zajet, ga lahko zapišete v flash pomnilnik. Flash pomnilnik je treba zapisati z določenimi naslovi, pri čemer določite, kam in koliko zapisati, podobno kot pri posodabljanju polja bajtov v pomnilniku. Flash pomnilnik ima granularnost, kar pomeni, da operacije brisanja in pisanja ne temeljijo le na fiksni velikosti, temveč tudi na poravnavi s to velikostjo. Na primer, če je granularnost 4096 bajtov in zahtevate brisanje na naslovu 4200, lahko izbriše vse podatke od naslova 4096 do 8192. To pomeni, da je treba pri zapisovanju podatkov o zvoku v flash pomnilnik to storiti v ustrezno velikih kosih.

### Naloga - konfiguracija flash pomnilnika

1. Ustvarite povsem nov projekt za Wio Terminal z uporabo PlatformIO. Projekt poimenujte `smart-timer`. Dodajte kodo v funkcijo `setup` za konfiguracijo serijskega porta.

1. Dodajte naslednje knjižnične odvisnosti v datoteko `platformio.ini`, da omogočite dostop do flash pomnilnika:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. Odprite datoteko `main.cpp` in na vrh datoteke dodajte naslednjo direktivo za vključitev knjižnice flash pomnilnika:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD pomeni Serial Flash Universal Driver in je knjižnica, zasnovana za delo z vsemi čipi flash pomnilnika.

1. V funkciji `setup` dodajte naslednjo kodo za nastavitev knjižnice za flash pomnilnik:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    Ta koda se izvaja, dokler knjižnica SFUD ni inicializirana, nato pa omogoči hitrejše branje. Vgrajeni flash pomnilnik je mogoče dostopati z uporabo Queued Serial Peripheral Interface (QSPI), vrste SPI krmilnika, ki omogoča neprekinjen dostop prek vrste z minimalno uporabo procesorja. To omogoča hitrejše branje in pisanje v flash pomnilnik.

1. Ustvarite novo datoteko v mapi `src`, imenovano `flash_writer.h`.

1. Na vrh te datoteke dodajte naslednje:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    To vključuje nekaj potrebnih glavičnih datotek, vključno z glavično datoteko za knjižnico SFUD za interakcijo s flash pomnilnikom.

1. V tej novi glavični datoteki definirajte razred z imenom `FlashWriter`:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. V razdelku `private` dodajte naslednjo kodo:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    To definira nekaj polj za medpomnilnik, ki se uporablja za shranjevanje podatkov pred zapisovanjem v flash pomnilnik. Obstaja polje bajtov `_sfudBuffer`, kamor se zapisujejo podatki, in ko je to polno, se podatki zapišejo v flash pomnilnik. Polje `_sfudBufferPos` shranjuje trenutno lokacijo za zapisovanje v ta medpomnilnik, `_sfudBufferWritePos` pa lokacijo v flash pomnilniku za zapisovanje. `_flash` je kazalec na flash pomnilnik za zapisovanje - nekateri mikrokrmilniki imajo več čipov flash pomnilnika.

1. Dodajte naslednjo metodo v razdelek `public` za inicializacijo tega razreda:

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

    To konfigurira flash pomnilnik na Wio Terminalu za zapisovanje in nastavi medpomnilnike glede na velikost granularnosti flash pomnilnika. To je v metodi `init`, namesto v konstruktorju, saj je treba to poklicati po tem, ko je flash pomnilnik nastavljen v funkciji `setup`.

1. Dodajte naslednjo kodo v razdelek `public`:

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

    Ta koda definira metode za zapisovanje bajtov v sistem za shranjevanje flash pomnilnika. Deluje tako, da zapisuje v medpomnilnik v pomnilniku, ki je prave velikosti za flash pomnilnik, in ko je ta poln, se zapiše v flash pomnilnik, pri čemer izbriše vse obstoječe podatke na tej lokaciji. Obstaja tudi metoda `flushSfudBuffer` za zapisovanje nepopolnega medpomnilnika, saj zajeti podatki ne bodo natančno večkratniki velikosti granularnosti, zato je treba zapisati končni del podatkov.

    > 💁 Končni del podatkov bo zapisal dodatne neželene podatke, vendar je to v redu, saj se bodo prebrali le potrebni podatki.

### Naloga - nastavitev zajema zvoka

1. Ustvarite novo datoteko v mapi `src`, imenovano `config.h`.

1. Na vrh te datoteke dodajte naslednje:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    Ta koda nastavi nekaj konstant za zajem zvoka.

    | Konstantna            | Vrednost | Opis |
    | --------------------- | -------: | - |
    | RATE                  | 16000    | Vzorec za zajem zvoka. 16.000 je 16 kHz |
    | SAMPLE_LENGTH_SECONDS | 4        | Dolžina zajetega zvoka. Nastavljeno na 4 sekunde. Če želite zajeti daljši zvok, povečajte to vrednost. |
    | SAMPLES               | 64000    | Skupno število vzorcev zvoka, ki bodo zajeti. Nastavljeno na vzorec * število sekund |
    | BUFFER_SIZE           | 128044   | Velikost medpomnilnika za zajem zvoka. Zvok bo zajet kot datoteka WAV, ki ima 44 bajtov glave, nato pa 128.000 bajtov podatkov o zvoku (vsak vzorec je 2 bajta) |
    | ADC_BUF_LEN           | 1600     | Velikost medpomnilnikov za zajem zvoka iz DMAC |

    > 💁 Če ugotovite, da so 4 sekunde prekratke za zahtevo časovnika, lahko povečate vrednost `SAMPLE_LENGTH_SECONDS`, in vse druge vrednosti se bodo preračunale.

1. Ustvarite novo datoteko v mapi `src`, imenovano `mic.h`.

1. Na vrh te datoteke dodajte naslednje:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    To vključuje nekaj potrebnih glavičnih datotek, vključno z glavičnimi datotekami `config.h` in `FlashWriter`.

1. Dodajte naslednje za definiranje razreda `Mic`, ki lahko zajema zvok iz mikrofona:

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

    Ta razred trenutno vsebuje le nekaj polj za sledenje, ali je snemanje začelo, in ali je posnetek pripravljen za uporabo. Ko je DMAC nastavljen, neprekinjeno piše v pomnilniške medpomnilnike, zato zastavica `_isRecording` določa, ali naj se ti obdelajo ali ignorirajo. Zastavica `_isRecordingReady` bo nastavljena, ko bo zajetih potrebnih 4 sekunde zvoka. Polje `_writer` se uporablja za shranjevanje podatkov o zvoku v flash pomnilnik.

    Nato je deklarirana globalna spremenljivka za instanco razreda `Mic`.

1. Dodajte naslednjo kodo v razdelek `private` razreda `Mic`:

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

    Ta koda definira metodo `configureDmaAdc`, ki konfigurira DMAC, ga poveže z ADC-jem in nastavi, da izmenično polni dva različna medpomnilnika, `_adc_buf_0` in `_adc_buf_1`.

    > 💁 Ena od slabosti razvoja za mikrokrmilnike je kompleksnost kode, potrebne za interakcijo s strojno opremo, saj vaša koda deluje na zelo nizki ravni in neposredno komunicira s strojno opremo. Ta koda je bolj zapletena kot tista, ki bi jo napisali za enojno ploščo ali namizni računalnik, saj ni operacijskega sistema, ki bi pomagal. Na voljo so nekatere knjižnice, ki lahko to poenostavijo, vendar je še vedno veliko kompleksnosti.

1. Pod to kodo dodajte naslednje:

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

    Ta koda definira glavo datoteke WAV kot strukturo, ki zavzame 44 bajtov pomnilnika. V glavo zapiše podrobnosti o hitrosti datoteke zvoka, velikosti in številu kanalov. Nato se ta glava zapiše v flash pomnilnik.

1. Pod to kodo dodajte naslednje za deklaracijo metode, ki se bo poklicala, ko bodo medpomnilniki zvoka pripravljeni za obdelavo:

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

    Medpomnilniki zvoka so polja 16-bitnih celih števil, ki vsebujejo zvok iz ADC-ja. ADC vrne 12-bitne nenegativne vrednosti (0-1023), zato jih je treba pretvoriti v 16-bitne predznačene vrednosti, nato pa pretvoriti v 2 bajta za shranjevanje kot surovi binarni podatki.

    Ti bajti se zapišejo v medpomnilnike flash pomnilnika. Zapis se začne na indeksu 44 - to je odmik od 44 bajtov, zapisanih kot glava datoteke WAV. Ko so zajeti vsi bajti, potrebni za zahtevano dolžino zvoka, se preostali podatki zapišejo v flash pomnilnik.

1. V razdelek `public` razreda `Mic` dodajte naslednjo kodo:

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

    Ta koda bo poklicana s strani DMAC, da vaši kodi sporoči, da so medpomnilniki pripravljeni za obdelavo. Preveri, ali so podatki za obdelavo, in pokliče metodo `audioCallback` z ustreznim medpomnilnikom.

1. Zunaj razreda, po deklaraciji `Mic mic;`, dodajte naslednjo kodo:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    Funkcija `DMAC_1_Handler` bo poklicana s strani DMAC, ko bodo medpomnilniki pripravljeni za obdelavo. Ta funkcija se najde po imenu, zato mora samo obstajati, da se pokliče.

1. Dodajte naslednji dve metodi v razdelek `public` razreda `Mic`:

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

    Metoda `init` vsebuje kodo za inicializacijo razreda `Mic`. Ta metoda nastavi pravilno napetost za pin mikrofona, nastavi pisalnik flash pomnilnika, zapiše glavo datoteke WAV in konfigurira DMAC. Metoda `reset` ponastavi flash pomnilnik in ponovno zapiše glavo po tem, ko je zvok zajet in uporabljen.

### Naloga - zajem zvoka

1. V datoteki `main.cpp` dodajte direktivo za vključitev glavične datoteke `mic.h`:

    ```cpp
    #include "mic.h"
    ```

1. V funkciji `setup` inicializirajte gumb C. Zajem zvoka se bo začel, ko bo ta gumb pritisnjen, in trajal 4 sekunde:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. Pod tem inicializirajte mikrofon, nato pa na konzolo natisnite, da je zvok pripravljen za zajem:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. Nad funkcijo `loop` definirajte funkcijo za obdelavo zajetega zvoka. Za zdaj ta ne počne ničesar, vendar bo kasneje v tej lekciji poslala govor za pretvorbo v besedilo:

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. V funkcijo `loop` dodajte naslednje:

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

    Ta koda preveri gumb C, in če je ta pritisnjen in snemanje ni začelo, se polje `_isRecording` razreda `Mic` nastavi na true. To bo povzročilo, da metoda `audioCallback` razreda `Mic` shrani zvok, dokler ni zajetih 4 sekunde. Ko je zajetih 4 sekunde zvoka, se polje `_isRecording` nastavi na false, polje `_isRecordingReady` pa na true. To se nato preveri v funkciji `loop`, in ko je true, se pokliče funkcija `processAudio`, nato pa se razred `Mic` ponastavi.

1. Sestavite to kodo, naložite jo na vaš Wio Terminal in jo preizkusite prek serijskega monitorja. Pritisnite gumb C (tisti na levi strani, najbližje stikalu za vklop), in govorite. Zajetih bo 4 sekunde zvoka.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Ready.
    Starting recording...
    Finished recording
    ```
💁 Ta koda se nahaja v mapi [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal).
😀 Vaš program za snemanje zvoka je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna napačna razumevanja ali napačne interpretacije, ki izhajajo iz uporabe tega prevoda.