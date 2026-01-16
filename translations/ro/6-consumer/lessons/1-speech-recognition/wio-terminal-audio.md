<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2f336726b9410e97c3aaed76cc89b0d8",
  "translation_date": "2025-08-28T09:19:23+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-audio.md",
  "language_code": "ro"
}
-->
# Capturarea audio - Wio Terminal

În această parte a lecției, vei scrie cod pentru a captura audio pe Wio Terminal. Capturarea audio va fi controlată de unul dintre butoanele de pe partea superioară a dispozitivului Wio Terminal.

## Programează dispozitivul pentru a captura audio

Poți captura audio de la microfon folosind cod C++. Wio Terminal are doar 192KB de RAM, insuficient pentru a captura mai mult de câteva secunde de audio. Totuși, are 4MB de memorie flash, care poate fi utilizată pentru a salva audio-ul capturat.

Microfonul încorporat captează un semnal analogic, care este convertit într-un semnal digital utilizabil de Wio Terminal. Când capturezi audio, datele trebuie capturate la momentul potrivit - de exemplu, pentru a captura audio la 16KHz, trebuie să captezi exact 16.000 de mostre pe secundă, la intervale egale. În loc să folosești codul tău pentru a face acest lucru, poți utiliza controlerul de acces direct la memorie (DMAC). Acesta este un circuit care poate captura un semnal și îl poate scrie în memorie, fără a întrerupe codul care rulează pe procesor.

✅ Citește mai multe despre DMA pe [pagina despre accesul direct la memorie de pe Wikipedia](https://wikipedia.org/wiki/Direct_memory_access).

![Audio-ul de la microfon merge la un ADC, apoi la DMAC. Acesta scrie într-un buffer. Când acest buffer este plin, este procesat, iar DMAC scrie într-un al doilea buffer](../../../../../translated_images/ro/dmac-adc-buffers.4509aee49145c90bc2e1be472b8ed2ddfcb2b6a81ad3e559114aca55f5fff759.png)

DMAC poate captura audio de la ADC la intervale fixe, cum ar fi de 16.000 de ori pe secundă pentru audio la 16KHz. Poate scrie aceste date capturate într-un buffer de memorie pre-alocat, iar când acesta este plin, îl face disponibil pentru procesarea codului tău. Utilizarea acestei memorii poate întârzia capturarea audio, dar poți configura mai multe buffere. DMAC scrie în bufferul 1, iar când acesta este plin, notifică codul tău să proceseze bufferul 1, în timp ce DMAC scrie în bufferul 2. Când bufferul 2 este plin, notifică codul tău și revine la scrierea în bufferul 1. Astfel, atâta timp cât procesezi fiecare buffer într-un timp mai scurt decât cel necesar pentru a umple unul, nu vei pierde date.

Odată ce fiecare buffer a fost capturat, acesta poate fi scris în memoria flash. Memoria flash trebuie scrisă folosind adrese definite, specificând unde și cât de mult să scrii, similar cu actualizarea unui array de bytes în memorie. Memoria flash are granularitate, ceea ce înseamnă că operațiunile de ștergere și scriere depind nu doar de o dimensiune fixă, ci și de alinierea la acea dimensiune. De exemplu, dacă granularitatea este de 4096 bytes și soliciți o ștergere la adresa 4200, aceasta ar putea șterge toate datele de la adresa 4096 la 8192. Acest lucru înseamnă că atunci când scrii datele audio în memoria flash, trebuie să fie în bucăți de dimensiunea corectă.

### Sarcină - configurarea memoriei flash

1. Creează un proiect nou pentru Wio Terminal folosind PlatformIO. Denumește acest proiect `smart-timer`. Adaugă cod în funcția `setup` pentru a configura portul serial.

1. Adaugă următoarele dependențe de bibliotecă în fișierul `platformio.ini` pentru a avea acces la memoria flash:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. Deschide fișierul `main.cpp` și adaugă următoarea directivă de includere pentru biblioteca de memorie flash în partea de sus a fișierului:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD înseamnă Serial Flash Universal Driver și este o bibliotecă proiectată să funcționeze cu toate cipurile de memorie flash.

1. În funcția `setup`, adaugă următorul cod pentru a configura biblioteca de stocare flash:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    Acest cod rulează în buclă până când biblioteca SFUD este inițializată, apoi activează citirile rapide. Memoria flash încorporată poate fi accesată folosind o Interfață Serială Periferică Cu Cozi (QSPI), un tip de controler SPI care permite acces continuu printr-o coadă cu utilizare minimă a procesorului. Acest lucru face ca citirea și scrierea în memoria flash să fie mai rapide.

1. Creează un fișier nou în folderul `src` numit `flash_writer.h`.

1. Adaugă următoarele la începutul acestui fișier:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    Acest lucru include câteva fișiere header necesare, inclusiv fișierul header pentru biblioteca SFUD pentru a interacționa cu memoria flash.

1. Definește o clasă în acest nou fișier header numită `FlashWriter`:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. În secțiunea `private`, adaugă următorul cod:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    Acest cod definește câmpuri pentru bufferul utilizat pentru a stoca datele înainte de a le scrie în memoria flash. Este prezent un array de bytes, `_sfudBuffer`, pentru a scrie datele, iar când acesta este plin, datele sunt scrise în memoria flash. Câmpul `_sfudBufferPos` stochează locația curentă pentru scriere în acest buffer, iar `_sfudBufferWritePos` stochează locația din memoria flash pentru scriere. `_flash` este un pointer către memoria flash în care se scrie - unele microcontrolere au mai multe cipuri de memorie flash.

1. Adaugă următoarea metodă în secțiunea `public` pentru a inițializa această clasă:

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

    Aceasta configurează memoria flash de pe Wio Terminal pentru scriere și setează bufferele pe baza dimensiunii granulelor memoriei flash. Este într-o metodă `init`, mai degrabă decât un constructor, deoarece trebuie apelată după ce memoria flash a fost configurată în funcția `setup`.

1. Adaugă următorul cod în secțiunea `public`:

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

    Acest cod definește metode pentru a scrie bytes în sistemul de stocare flash. Funcționează prin scrierea într-un buffer în memorie care are dimensiunea corectă pentru memoria flash, iar când acesta este plin, este scris în memoria flash, ștergând orice date existente la acea locație. Există și o metodă `flushSfudBuffer` pentru a scrie un buffer incomplet, deoarece datele capturate nu vor fi multipli exacți ai dimensiunii granulelor, astfel încât partea finală a datelor trebuie scrisă.

    > 💁 Partea finală a datelor va scrie date suplimentare nedorite, dar acest lucru este în regulă, deoarece doar datele necesare vor fi citite.

### Sarcină - configurarea capturii audio

1. Creează un fișier nou în folderul `src` numit `config.h`.

1. Adaugă următoarele la începutul acestui fișier:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    Acest cod configurează câteva constante pentru capturarea audio.

    | Constantă             | Valoare | Descriere |
    | --------------------- | ------: | - |
    | RATE                  | 16000   | Rata de eșantionare pentru audio. 16.000 este 16KHz |
    | SAMPLE_LENGTH_SECONDS | 4       | Durata audio-ului capturat. Este setată la 4 secunde. Pentru a înregistra mai mult, mărește această valoare. |
    | SAMPLES               | 64000   | Numărul total de mostre audio care vor fi capturate. Setat la rata de eșantionare * numărul de secunde |
    | BUFFER_SIZE           | 128044  | Dimensiunea bufferului audio pentru capturare. Audio-ul va fi capturat ca un fișier WAV, care are 44 bytes de header, apoi 128.000 bytes de date audio (fiecare mostră are 2 bytes) |
    | ADC_BUF_LEN           | 1600    | Dimensiunea bufferelor utilizate pentru a captura audio de la DMAC |

    > 💁 Dacă consideri că 4 secunde sunt prea puține pentru a solicita un timer, poți mări valoarea `SAMPLE_LENGTH_SECONDS`, iar toate celelalte valori vor fi recalculate.

1. Creează un fișier nou în folderul `src` numit `mic.h`.

1. Adaugă următoarele la începutul acestui fișier:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    Acest lucru include câteva fișiere header necesare, inclusiv fișierele `config.h` și `FlashWriter`.

1. Adaugă următoarele pentru a defini o clasă `Mic` care poate captura de la microfon:

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

    Această clasă are în prezent doar câteva câmpuri pentru a urmări dacă înregistrarea a început și dacă o înregistrare este gata de utilizare. Când DMAC este configurat, acesta scrie continuu în bufferele de memorie, astfel încât flag-ul `_isRecording` determină dacă acestea ar trebui procesate sau ignorate. Flag-ul `_isRecordingReady` va fi setat când cele 4 secunde necesare de audio au fost capturate. Câmpul `_writer` este utilizat pentru a salva datele audio în memoria flash.

    Este apoi declarată o variabilă globală pentru o instanță a clasei `Mic`.

1. Adaugă următorul cod în secțiunea `private` a clasei `Mic`:

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

    Acest cod definește o metodă `configureDmaAdc` care configurează DMAC, conectându-l la ADC și setându-l să populeze două buffere alternante, `_adc_buf_0` și `_adc_buf_1`.

    > 💁 Unul dintre dezavantajele dezvoltării pentru microcontrolere este complexitatea codului necesar pentru a interacționa cu hardware-ul, deoarece codul tău rulează la un nivel foarte jos, interacționând direct cu hardware-ul. Acest cod este mai complex decât ceea ce ai scrie pentru un computer cu placă unică sau un computer desktop, deoarece nu există un sistem de operare care să ajute. Există unele biblioteci disponibile care pot simplifica acest lucru, dar tot există multă complexitate.

1. Mai jos, adaugă următorul cod:

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

    Acest cod definește header-ul WAV ca o structură care ocupă 44 bytes de memorie. Scrie detalii despre rata fișierului audio, dimensiune și numărul de canale. Acest header este apoi scris în memoria flash.

1. Mai jos de acest cod, adaugă următoarele pentru a declara o metodă care va fi apelată când bufferele audio sunt gata de procesare:

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

    Bufferele audio sunt array-uri de întregi pe 16 biți care conțin audio-ul de la ADC. ADC-ul returnează valori nesemnate pe 12 biți (0-1023), astfel încât acestea trebuie convertite în valori semnate pe 16 biți, apoi convertite în 2 bytes pentru a fi stocate ca date binare brute.

    Acești bytes sunt scriși în bufferele de memorie flash. Scrierea începe la indexul 44 - acesta este offset-ul de la cei 44 bytes scriși ca header al fișierului WAV. Odată ce toate bytes-urile necesare pentru lungimea audio-ului dorit au fost capturate, datele rămase sunt scrise în memoria flash.

1. În secțiunea `public` a clasei `Mic`, adaugă următorul cod:

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

    Acest cod va fi apelat de DMAC pentru a spune codului tău să proceseze bufferele. Verifică dacă există date de procesat și apelează metoda `audioCallback` cu bufferul relevant.

1. În afara clasei, după declarația `Mic mic;`, adaugă următorul cod:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    `DMAC_1_Handler` va fi apelat de DMAC când bufferele sunt gata de procesare. Această funcție este găsită după nume, astfel încât trebuie doar să existe pentru a fi apelată.

1. Adaugă următoarele două metode în secțiunea `public` a clasei `Mic`:

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

    Metoda `init` conține cod pentru a inițializa clasa `Mic`. Această metodă setează tensiunea corectă pentru pinul microfonului, configurează scriitorul de memorie flash, scrie header-ul fișierului WAV și configurează DMAC. Metoda `reset` resetează memoria flash și rescrie header-ul după ce audio-ul a fost capturat și utilizat.

### Sarcină - capturarea audio-ului

1. În fișierul `main.cpp`, adaugă o directivă de includere pentru fișierul header `mic.h`:

    ```cpp
    #include "mic.h"
    ```

1. În funcția `setup`, inițializează butonul C. Capturarea audio va începe când acest buton este apăsat și va continua timp de 4 secunde:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. Mai jos, inițializează microfonul, apoi afișează în consolă că audio-ul este gata de capturat:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. Deasupra funcției `loop`, definește o funcție pentru a procesa audio-ul capturat. Deocamdată, aceasta nu face nimic, dar mai târziu în această lecție va trimite vorbirea pentru a fi convertită în text:

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. Adaugă următoarele în funcția `loop`:

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

    Acest cod verifică butonul C, iar dacă acesta este apăsat și înregistrarea nu a început, atunci câmpul `_isRecording` al clasei `Mic` este setat la true. Acest lucru va face ca metoda `audioCallback` a clasei `Mic` să stocheze audio-ul până când 4 secunde au fost capturate. Odată ce cele 4 secunde de audio au fost capturate, câmpul `_isRecording` este setat la false, iar câmpul `_isRecordingReady` este setat la true. Acest lucru este apoi verificat în funcția `loop`, iar când este true, funcția `processAudio` este apelată, apoi clasa `Mic` este resetată.

1. Construiește acest cod, încarcă-l pe Wio Terminal și testează-l prin monitorul serial. Apasă butonul C (cel din partea stângă, cel mai aproape de comutatorul de alimentare) și vorbește. Vor fi capturate 4 secunde de audio.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Ready.
    Starting recording...
    Finished recording
    ```
> 💁 Puteți găsi acest cod în folderul [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal).
😀 Programul tău de înregistrare audio a fost un succes!

---

**Declinarea responsabilității**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși depunem eforturi pentru a asigura acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa nativă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm răspunderea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.