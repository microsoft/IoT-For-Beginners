<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2f336726b9410e97c3aaed76cc89b0d8",
  "translation_date": "2025-08-28T13:00:17+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-audio.md",
  "language_code": "hr"
}
-->
# Snimanje zvuka - Wio Terminal

U ovom dijelu lekcije napisat ćete kod za snimanje zvuka na svom Wio Terminalu. Snimanje zvuka kontrolirat će se pomoću jednog od gumba na vrhu Wio Terminala.

## Programiranje uređaja za snimanje zvuka

Zvuk možete snimiti s mikrofona koristeći C++ kod. Wio Terminal ima samo 192KB RAM-a, što nije dovoljno za snimanje više od nekoliko sekundi zvuka. Međutim, ima 4MB flash memorije, koja se može koristiti za spremanje snimljenog zvuka.

Ugrađeni mikrofon snima analogni signal, koji se zatim pretvara u digitalni signal koji Wio Terminal može koristiti. Prilikom snimanja zvuka, podaci se moraju snimati u točno određenim vremenskim intervalima - na primjer, za snimanje zvuka na 16 kHz, zvuk se mora snimati točno 16.000 puta u sekundi, s jednakim razmacima između svakog uzorka. Umjesto da koristite svoj kod za to, možete koristiti kontroler za izravan pristup memoriji (DMAC). Ovo je sklop koji može snimiti signal i zapisati ga u memoriju, bez prekidanja koda koji se izvodi na procesoru.

✅ Pročitajte više o DMA na [stranici o izravnom pristupu memoriji na Wikipediji](https://wikipedia.org/wiki/Direct_memory_access).

![Zvuk s mikrofona ide u ADC, zatim u DMAC. DMAC zapisuje u jedan međuspremnik. Kada se taj međuspremnik napuni, obrađuje se, a DMAC zapisuje u drugi međuspremnik](../../../../../translated_images/hr/dmac-adc-buffers.4509aee49145c90bc2e1be472b8ed2ddfcb2b6a81ad3e559114aca55f5fff759.png)

DMAC može snimati zvuk s ADC-a u fiksnim intervalima, primjerice 16.000 puta u sekundi za zvuk od 16 kHz. Može zapisivati te snimljene podatke u unaprijed dodijeljeni memorijski međuspremnik, a kada se on napuni, obavještava vaš kod da ga obradi. Korištenje ovog međuspremnika može odgoditi snimanje zvuka, ali možete postaviti više međuspremnika. DMAC zapisuje u međuspremnik 1, a kada se on napuni, obavještava vaš kod da obradi međuspremnik 1, dok DMAC zapisuje u međuspremnik 2. Kada se međuspremnik 2 napuni, obavještava vaš kod i vraća se na zapisivanje u međuspremnik 1. Na taj način, sve dok obrađujete svaki međuspremnik u kraćem vremenu nego što je potrebno da se jedan napuni, nećete izgubiti podatke.

Nakon što se svaki međuspremnik snimi, može se zapisati u flash memoriju. Flash memorija mora se zapisivati koristeći definirane adrese, specificirajući gdje i koliko zapisati, slično ažuriranju niza bajtova u memoriji. Flash memorija ima granularnost, što znači da operacije brisanja i zapisivanja ovise ne samo o fiksnoj veličini, već i o poravnanju s tom veličinom. Na primjer, ako je granularnost 4096 bajtova i zatražite brisanje na adresi 4200, moglo bi se izbrisati sve od adrese 4096 do 8192. To znači da kada zapisujete audio podatke u flash memoriju, to mora biti u ispravnim veličinama blokova.

### Zadatak - konfiguriranje flash memorije

1. Napravite potpuno novi projekt za Wio Terminal koristeći PlatformIO. Nazovite ovaj projekt `smart-timer`. Dodajte kod u funkciju `setup` za konfiguriranje serijskog porta.

1. Dodajte sljedeće ovisnosti biblioteke u datoteku `platformio.ini` kako biste omogućili pristup flash memoriji:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. Otvorite datoteku `main.cpp` i dodajte sljedeću direktivu za uključivanje biblioteke za flash memoriju na vrh datoteke:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD označava Serial Flash Universal Driver, biblioteku dizajniranu za rad sa svim čipovima flash memorije.

1. U funkciji `setup`, dodajte sljedeći kod za postavljanje biblioteke za flash memoriju:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    Ovaj kod se ponavlja dok se SFUD biblioteka ne inicijalizira, a zatim uključuje brzo čitanje. Ugrađena flash memorija može se pristupiti koristeći Queued Serial Peripheral Interface (QSPI), vrstu SPI kontrolera koji omogućuje kontinuirani pristup putem reda s minimalnim korištenjem procesora. Ovo omogućuje brže čitanje i zapisivanje u flash memoriju.

1. Napravite novu datoteku u mapi `src` pod nazivom `flash_writer.h`.

1. Dodajte sljedeće na vrh ove datoteke:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    Ovo uključuje potrebne zaglavne datoteke, uključujući zaglavnu datoteku za SFUD biblioteku za interakciju s flash memorijom.

1. Definirajte klasu u ovom novom zaglavlju pod nazivom `FlashWriter`:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. U privatni dio dodajte sljedeći kod:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    Ovo definira neka polja za međuspremnik koji će se koristiti za pohranu podataka prije zapisivanja u flash memoriju. Postoji niz bajtova `_sfudBuffer` za zapisivanje podataka, a kada se on napuni, podaci se zapisuju u flash memoriju. Polje `_sfudBufferPos` pohranjuje trenutnu lokaciju za zapisivanje u ovom međuspremniku, a `_sfudBufferWritePos` pohranjuje lokaciju u flash memoriji za zapisivanje. `_flash` je pokazivač na flash memoriju za zapisivanje - neki mikrokontroleri imaju više čipova flash memorije.

1. Dodajte sljedeću metodu u javni dio za inicijalizaciju ove klase:

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

    Ova metoda konfigurira flash memoriju na Wio Terminalu za zapisivanje i postavlja međuspremnike na temelju veličine bloka flash memorije. Ovo je u metodi `init`, a ne u konstruktoru, jer se mora pozvati nakon što je flash memorija postavljena u funkciji `setup`.

1. Dodajte sljedeći kod u javni dio:

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

    Ovaj kod definira metode za zapisivanje bajtova u sustav za pohranu flash memorije. Funkcionira tako da zapisuje u međuspremnik u memoriji koji je odgovarajuće veličine za flash memoriju, a kada se on napuni, zapisuje se u flash memoriju, brišući sve postojeće podatke na toj lokaciji. Također postoji metoda `flushSfudBuffer` za zapisivanje nepotpunog međuspremnika, jer podaci koji se snimaju neće biti točno višekratnici veličine bloka, pa se završni dio podataka mora zapisati.

    > 💁 Završni dio podataka zapisat će dodatne neželjene podatke, ali to je u redu jer će se čitati samo potrebni podaci.

### Zadatak - postavljanje snimanja zvuka

1. Napravite novu datoteku u mapi `src` pod nazivom `config.h`.

1. Dodajte sljedeće na vrh ove datoteke:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    Ovaj kod postavlja neke konstante za snimanje zvuka.

    | Konstanta             | Vrijednost | Opis |
    | --------------------- | ---------: | - |
    | RATE                  | 16000      | Brzina uzorkovanja zvuka. 16.000 je 16 kHz |
    | SAMPLE_LENGTH_SECONDS | 4          | Duljina zvuka za snimanje. Postavljeno na 4 sekunde. Za dulje snimanje povećajte ovu vrijednost. |
    | SAMPLES               | 64000      | Ukupan broj audio uzoraka koji će se snimiti. Postavljeno na brzinu uzorkovanja * broj sekundi |
    | BUFFER_SIZE           | 128044     | Veličina međuspremnika za snimanje zvuka. Zvuk će se snimati kao WAV datoteka, koja ima 44 bajta zaglavlja, zatim 128.000 bajtova audio podataka (svaki uzorak ima 2 bajta) |
    | ADC_BUF_LEN           | 1600       | Veličina međuspremnika za snimanje zvuka iz DMAC-a |

    > 💁 Ako smatrate da su 4 sekunde prekratke za zahtjev za tajmer, možete povećati vrijednost `SAMPLE_LENGTH_SECONDS`, a sve ostale vrijednosti će se ponovno izračunati.

1. Napravite novu datoteku u mapi `src` pod nazivom `mic.h`.

1. Dodajte sljedeće na vrh ove datoteke:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    Ovo uključuje potrebne zaglavne datoteke, uključujući `config.h` i `FlashWriter` zaglavne datoteke.

1. Dodajte sljedeće za definiranje klase `Mic` koja može snimati s mikrofona:

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

    Ova klasa trenutno ima samo nekoliko polja za praćenje je li snimanje započelo i je li snimanje spremno za korištenje. Kada se DMAC postavi, kontinuirano zapisuje u memorijske međuspremnike, pa zastavica `_isRecording` određuje trebaju li se ti međuspremnici obrađivati ili ignorirati. Zastavica `_isRecordingReady` postavit će se kada se snimi potrebnih 4 sekunde zvuka. Polje `_writer` koristi se za spremanje audio podataka u flash memoriju.

    Zatim se deklarira globalna varijabla za instancu klase `Mic`.

1. Dodajte sljedeći kod u privatni dio klase `Mic`:

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

    Ovaj kod definira metodu `configureDmaAdc` koja konfigurira DMAC, povezujući ga s ADC-om i postavljajući ga za popunjavanje dva različita međuspremnika naizmjenično, `_adc_buf_0` i `_adc_buf_1`.

    > 💁 Jedan od nedostataka razvoja za mikrokontrolere je složenost koda potrebnog za interakciju s hardverom, jer vaš kod radi na vrlo niskoj razini, izravno komunicirajući s hardverom. Ovaj kod je složeniji nego što biste napisali za jednopločne ili stolna računala jer ne postoji operativni sustav koji bi pomogao. Postoje neke biblioteke koje to mogu pojednostaviti, ali i dalje postoji mnogo složenosti.

1. Ispod ovoga dodajte sljedeći kod:

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

    Ovaj kod definira WAV zaglavlje kao strukturu koja zauzima 44 bajta memorije. U njega se upisuju detalji o brzini, veličini i broju kanala audio datoteke. Ovo zaglavlje se zatim zapisuje u flash memoriju.

1. Ispod ovog koda dodajte sljedeće za deklariranje metode koja će se pozvati kada su audio međuspremnici spremni za obradu:

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

    Audio međuspremnici su nizovi 16-bitnih cijelih brojeva koji sadrže zvuk iz ADC-a. ADC vraća 12-bitne neoznačene vrijednosti (0-1023), pa ih treba pretvoriti u 16-bitne označene vrijednosti, a zatim pretvoriti u 2 bajta za pohranu kao sirovi binarni podaci.

    Ti bajtovi se zapisuju u međuspremnike flash memorije. Zapisivanje počinje na indeksu 44 - ovo je pomak od 44 bajta zapisanih kao WAV zaglavlje. Nakon što se snime svi potrebni bajtovi za traženu duljinu zvuka, preostali podaci se zapisuju u flash memoriju.

1. U javni dio klase `Mic` dodajte sljedeći kod:

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

    Ovaj kod će pozvati DMAC kako bi vaš kod obradio međuspremnike. Provjerava ima li podataka za obradu i poziva metodu `audioCallback` s relevantnim međuspremnikom.

1. Izvan klase, nakon deklaracije `Mic mic;`, dodajte sljedeći kod:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    Funkcija `DMAC_1_Handler` pozvat će DMAC kada su međuspremnici spremni za obradu. Ova funkcija se pronalazi prema imenu, pa samo treba postojati da bi se pozvala.

1. Dodajte sljedeće dvije metode u javni dio klase `Mic`:

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

    Metoda `init` sadrži kod za inicijalizaciju klase `Mic`. Ova metoda postavlja ispravan napon za pin mikrofona, postavlja flash memoriju, zapisuje WAV zaglavlje i konfigurira DMAC. Metoda `reset` resetira flash memoriju i ponovno zapisuje zaglavlje nakon što se zvuk snimi i iskoristi.

### Zadatak - snimanje zvuka

1. U datoteci `main.cpp`, dodajte direktivu za uključivanje zaglavne datoteke `mic.h`:

    ```cpp
    #include "mic.h"
    ```

1. U funkciji `setup`, inicijalizirajte gumb C. Snimanje zvuka započet će kada se pritisne ovaj gumb i trajat će 4 sekunde:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. Ispod ovoga, inicijalizirajte mikrofon, a zatim ispišite na konzolu da je zvuk spreman za snimanje:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. Iznad funkcije `loop`, definirajte funkciju za obradu snimljenog zvuka. Za sada ova funkcija ne radi ništa, ali kasnije u lekciji poslat će govor na pretvorbu u tekst:

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. Dodajte sljedeće u funkciju `loop`:

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

    Ovaj kod provjerava gumb C, i ako je pritisnut, a snimanje nije započelo, tada se polje `_isRecording` klase `Mic` postavlja na true. Ovo će uzrokovati da metoda `audioCallback` klase `Mic` pohranjuje zvuk dok se ne snimi 4 sekunde. Kada se snimi 4 sekunde zvuka, polje `_isRecording` postavlja se na false, a polje `_isRecordingReady` postavlja se na true. Ovo se zatim provjerava u funkciji `loop`, i kada je true, poziva se funkcija `processAudio`, a zatim se klasa `Mic` resetira.

1. Sastavite ovaj kod, učitajte ga na svoj Wio Terminal i testirajte putem serijskog monitora. Pritisnite gumb C (onaj na lijevoj strani, najbliži prekidaču za uključivanje) i govorite. Snimit će se 4 sekunde zvuka.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Ready.
    Starting recording...
    Finished recording
    ```
💁 Ovaj kod možete pronaći u mapi [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal).
😀 Vaš program za snimanje zvuka bio je uspješan!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za nesporazume ili pogrešna tumačenja koja mogu proizaći iz korištenja ovog prijevoda.