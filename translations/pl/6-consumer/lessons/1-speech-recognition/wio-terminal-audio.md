<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2f336726b9410e97c3aaed76cc89b0d8",
  "translation_date": "2025-08-26T07:24:26+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-audio.md",
  "language_code": "pl"
}
-->
# Przechwytywanie dźwięku - Wio Terminal

W tej części lekcji napiszesz kod do przechwytywania dźwięku na swoim Wio Terminal. Przechwytywanie dźwięku będzie kontrolowane za pomocą jednego z przycisków na górze urządzenia.

## Programowanie urządzenia do przechwytywania dźwięku

Możesz przechwytywać dźwięk z mikrofonu za pomocą kodu w C++. Wio Terminal ma tylko 192KB pamięci RAM, co wystarcza na przechwycenie zaledwie kilku sekund dźwięku. Posiada również 4MB pamięci flash, która może być użyta do zapisywania przechwyconego dźwięku.

Wbudowany mikrofon przechwytuje sygnał analogowy, który jest konwertowany na sygnał cyfrowy, z którym Wio Terminal może pracować. Podczas przechwytywania dźwięku dane muszą być zbierane w odpowiednich odstępach czasu - na przykład, aby przechwycić dźwięk w częstotliwości 16 kHz, dane muszą być zbierane dokładnie 16 000 razy na sekundę, w równych odstępach. Zamiast używać kodu do tego celu, można skorzystać z kontrolera bezpośredniego dostępu do pamięci (DMAC). Jest to układ, który może przechwytywać sygnał z określonego miejsca i zapisywać go w pamięci, nie przerywając działania kodu na procesorze.

✅ Przeczytaj więcej o DMA na [stronie o bezpośrednim dostępie do pamięci na Wikipedii](https://wikipedia.org/wiki/Direct_memory_access).

![Dźwięk z mikrofonu trafia do ADC, a następnie do DMAC. DMAC zapisuje dane do jednego bufora. Gdy bufor jest pełny, dane są przetwarzane, a DMAC zapisuje do drugiego bufora](../../../../../translated_images/pl/dmac-adc-buffers.4509aee49145c90bc2e1be472b8ed2ddfcb2b6a81ad3e559114aca55f5fff759.png)

DMAC może przechwytywać dźwięk z ADC w stałych odstępach czasu, na przykład 16 000 razy na sekundę dla dźwięku o częstotliwości 16 kHz. Może zapisywać te dane do wcześniej przydzielonego bufora pamięci, a gdy bufor jest pełny, udostępnia go kodowi do przetworzenia. Korzystanie z tej pamięci może opóźnić przechwytywanie dźwięku, ale można skonfigurować wiele buforów. DMAC zapisuje dane do bufora 1, a gdy ten jest pełny, powiadamia kod o konieczności przetworzenia bufora 1, podczas gdy DMAC zapisuje dane do bufora 2. Gdy bufor 2 jest pełny, powiadamia kod, a następnie wraca do zapisywania danych do bufora 1. Dzięki temu, jeśli przetwarzanie każdego bufora zajmuje mniej czasu niż jego wypełnienie, dane nie zostaną utracone.

Po przechwyceniu każdego bufora dane mogą być zapisane do pamięci flash. Pamięć flash musi być zapisywana przy użyciu określonych adresów, wskazując miejsce zapisu i rozmiar danych, podobnie jak aktualizacja tablicy bajtów w pamięci. Pamięć flash ma granularność, co oznacza, że operacje kasowania i zapisu zależą nie tylko od ustalonego rozmiaru, ale także od wyrównania do tego rozmiaru. Na przykład, jeśli granularność wynosi 4096 bajtów, a żądanie kasowania dotyczy adresu 4200, może zostać skasowane całe dane od adresu 4096 do 8192. Oznacza to, że podczas zapisywania danych audio do pamięci flash, muszą być one podzielone na odpowiednie fragmenty.

### Zadanie - konfiguracja pamięci flash

1. Utwórz nowy projekt Wio Terminal za pomocą PlatformIO. Nazwij ten projekt `smart-timer`. Dodaj kod w funkcji `setup`, aby skonfigurować port szeregowy.

1. Dodaj następujące zależności biblioteczne do pliku `platformio.ini`, aby uzyskać dostęp do pamięci flash:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. Otwórz plik `main.cpp` i dodaj następującą dyrektywę `include` dla biblioteki pamięci flash na początku pliku:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD oznacza Serial Flash Universal Driver, czyli bibliotekę zaprojektowaną do pracy ze wszystkimi układami pamięci flash.

1. W funkcji `setup` dodaj następujący kod, aby skonfigurować bibliotekę pamięci flash:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    Kod ten działa w pętli, dopóki biblioteka SFUD nie zostanie zainicjowana, a następnie włącza szybki odczyt. Wbudowana pamięć flash może być dostępna za pomocą Queued Serial Peripheral Interface (QSPI), rodzaju kontrolera SPI, który umożliwia ciągły dostęp za pomocą kolejki przy minimalnym wykorzystaniu procesora. Dzięki temu odczyt i zapis do pamięci flash są szybsze.

1. Utwórz nowy plik w folderze `src` o nazwie `flash_writer.h`.

1. Dodaj następujący kod na początku tego pliku:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    Kod ten zawiera potrzebne pliki nagłówkowe, w tym plik nagłówkowy biblioteki SFUD do interakcji z pamięcią flash.

1. Zdefiniuj klasę w tym nowym pliku nagłówkowym o nazwie `FlashWriter`:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. W sekcji `private` dodaj następujący kod:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    Kod ten definiuje pola dla bufora używanego do przechowywania danych przed zapisaniem ich do pamięci flash. Jest to tablica bajtów `_sfudBuffer`, do której zapisywane są dane, a gdy jest pełna, dane są zapisywane do pamięci flash. Pole `_sfudBufferPos` przechowuje bieżącą pozycję zapisu w tym buforze, a `_sfudBufferWritePos` przechowuje pozycję w pamięci flash, do której dane mają być zapisane. `_flash` to wskaźnik na pamięć flash, do której dane mają być zapisane - niektóre mikrokontrolery mają wiele układów pamięci flash.

1. Dodaj następującą metodę do sekcji `public`, aby zainicjować tę klasę:

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

    Kod ten konfiguruje pamięć flash na Wio Terminal do zapisu i ustawia bufor na podstawie rozmiaru granularności pamięci flash. Jest to metoda `init`, a nie konstruktor, ponieważ musi być wywołana po skonfigurowaniu pamięci flash w funkcji `setup`.

1. Dodaj następujący kod do sekcji `public`:

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

    Kod ten definiuje metody do zapisywania bajtów w systemie pamięci flash. Działa poprzez zapis do bufora w pamięci, który ma odpowiedni rozmiar dla pamięci flash, a gdy jest pełny, dane są zapisywane do pamięci flash, kasując wszelkie istniejące dane w tym miejscu. Istnieje również metoda `flushSfudBuffer`, która zapisuje niekompletny bufor, ponieważ przechwytywane dane nie będą dokładnymi wielokrotnościami rozmiaru granularności, więc końcowa część danych musi być zapisana.

    > 💁 Końcowa część danych zapisze dodatkowe niepotrzebne dane, ale jest to w porządku, ponieważ odczytane zostaną tylko potrzebne dane.

### Zadanie - konfiguracja przechwytywania dźwięku

1. Utwórz nowy plik w folderze `src` o nazwie `config.h`.

1. Dodaj następujący kod na początku tego pliku:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    Kod ten ustawia kilka stałych dla przechwytywania dźwięku.

    | Stała                 | Wartość | Opis |
    | --------------------- | ------: | - |
    | RATE                  | 16000   | Częstotliwość próbkowania dźwięku. 16 000 to 16 kHz |
    | SAMPLE_LENGTH_SECONDS | 4       | Długość przechwytywanego dźwięku. Ustawiona na 4 sekundy. Aby nagrać dłuższy dźwięk, zwiększ tę wartość. |
    | SAMPLES               | 64000   | Całkowita liczba próbek dźwięku, które zostaną przechwycone. Ustawiona na częstotliwość próbkowania * liczbę sekund |
    | BUFFER_SIZE           | 128044  | Rozmiar bufora dźwięku do przechwytywania. Dźwięk będzie przechwytywany jako plik WAV, który ma 44 bajty nagłówka, a następnie 128 000 bajtów danych audio (każda próbka to 2 bajty) |
    | ADC_BUF_LEN           | 1600    | Rozmiar buforów używanych do przechwytywania dźwięku z DMAC |

    > 💁 Jeśli 4 sekundy są zbyt krótkie, aby poprosić o timer, możesz zwiększyć wartość `SAMPLE_LENGTH_SECONDS`, a wszystkie inne wartości zostaną przeliczone.

1. Utwórz nowy plik w folderze `src` o nazwie `mic.h`.

1. Dodaj następujący kod na początku tego pliku:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    Kod ten zawiera potrzebne pliki nagłówkowe, w tym pliki `config.h` i `FlashWriter`.

1. Dodaj następujący kod, aby zdefiniować klasę `Mic`, która może przechwytywać dane z mikrofonu:

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

    Klasa ta ma obecnie tylko kilka pól do śledzenia, czy nagrywanie zostało rozpoczęte i czy nagranie jest gotowe do użycia. Gdy DMAC jest skonfigurowany, ciągle zapisuje dane do buforów pamięci, więc flaga `_isRecording` określa, czy dane te powinny być przetwarzane, czy ignorowane. Flaga `_isRecordingReady` zostanie ustawiona, gdy wymagane 4 sekundy dźwięku zostaną przechwycone. Pole `_writer` służy do zapisywania danych audio w pamięci flash.

    Następnie deklarowana jest globalna zmienna dla instancji klasy `Mic`.

1. Dodaj następujący kod do sekcji `private` klasy `Mic`:

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

    Kod ten definiuje metodę `configureDmaAdc`, która konfiguruje DMAC, łącząc go z ADC i ustawiając na wypełnianie dwóch różnych naprzemiennych buforów, `_adc_buf_0` i `_adc_buf_1`.

    > 💁 Jednym z minusów programowania mikrokontrolerów jest złożoność kodu potrzebnego do interakcji ze sprzętem, ponieważ kod działa na bardzo niskim poziomie, bezpośrednio współpracując ze sprzętem. Kod ten jest bardziej skomplikowany niż ten, który napisałbyś dla komputera jednopłytkowego lub stacjonarnego, ponieważ nie ma systemu operacyjnego, który by pomagał. Istnieją biblioteki, które mogą to uprościć, ale nadal jest dużo złożoności.

1. Poniżej dodaj następujący kod:

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

    Kod ten definiuje nagłówek WAV jako strukturę zajmującą 44 bajty pamięci. Zapisuje szczegóły dotyczące częstotliwości pliku audio, rozmiaru i liczby kanałów. Ten nagłówek jest następnie zapisywany w pamięci flash.

1. Poniżej tego kodu dodaj następujący kod, aby zadeklarować metodę wywoływaną, gdy bufory audio są gotowe do przetworzenia:

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

    Bufory audio to tablice 16-bitowych liczb całkowitych zawierających dane audio z ADC. ADC zwraca 12-bitowe wartości bez znaku (0-1023), więc muszą one zostać przekonwertowane na 16-bitowe wartości ze znakiem, a następnie na 2 bajty, aby zostały zapisane jako surowe dane binarne.

    Te bajty są zapisywane w buforach pamięci flash. Zapis rozpoczyna się od indeksu 44 - jest to przesunięcie od 44 bajtów zapisanych jako nagłówek pliku WAV. Gdy wszystkie bajty potrzebne do wymaganej długości dźwięku zostaną przechwycone, pozostałe dane są zapisywane w pamięci flash.

1. W sekcji `public` klasy `Mic` dodaj następujący kod:

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

    Kod ten będzie wywoływany przez DMAC, aby poinformować kod o konieczności przetworzenia buforów. Sprawdza, czy są dane do przetworzenia, i wywołuje metodę `audioCallback` z odpowiednim buforem.

1. Po klasie, po deklaracji `Mic mic;`, dodaj następujący kod:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    Funkcja `DMAC_1_Handler` będzie wywoływana przez DMAC, gdy bufory będą gotowe do przetworzenia. Funkcja ta jest znajdowana po nazwie, więc wystarczy, że istnieje, aby została wywołana.

1. Dodaj następujące dwie metody do sekcji `public` klasy `Mic`:

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

    Metoda `init` zawiera kod do inicjalizacji klasy `Mic`. Ustawia odpowiednie napięcie dla pinu mikrofonu, konfiguruje zapis do pamięci flash, zapisuje nagłówek pliku WAV i konfiguruje DMAC. Metoda `reset` resetuje pamięć flash i ponownie zapisuje nagłówek po przechwyceniu i użyciu danych audio.

### Zadanie - przechwytywanie dźwięku

1. W pliku `main.cpp` dodaj dyrektywę `include` dla pliku nagłówkowego `mic.h`:

    ```cpp
    #include "mic.h"
    ```

1. W funkcji `setup` zainicjalizuj przycisk C. Przechwytywanie dźwięku rozpocznie się po naciśnięciu tego przycisku i będzie trwało przez 4 sekundy:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. Poniżej tego kodu zainicjalizuj mikrofon, a następnie wydrukuj na konsoli informację, że dźwięk jest gotowy do przechwycenia:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. Nad funkcją `loop` zdefiniuj funkcję do przetwarzania przechwyconego dźwięku. Na razie nic nie robi, ale później w tej lekcji będzie wysyłać mowę do konwersji na tekst:

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. Dodaj następujący kod do funkcji `loop`:

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

    Kod ten sprawdza przycisk C, a jeśli jest naciśnięty i nagrywanie nie zostało rozpoczęte, pole `_isRecording` klasy `Mic` zostaje ustawione na `true`. Spowoduje to, że metoda `audioCallback` klasy `Mic` będzie przechowywać dane audio, dopóki nie zostanie przechwycone 4 sekundy. Gdy 4 sekundy dźwięku zostaną przechwycone, pole `_isRecording` zostaje ustawione na `false`, a pole `_isRecordingReady` na `true`. Następnie jest to sprawdzane w funkcji `loop`, a gdy wartość jest `true`, wywoływana jest funkcja `processAudio`, a następnie klasa mikrofonu jest resetowana.

1. Zbuduj ten kod, wgraj go na swój Wio Terminal i przetestuj za pomocą monitora szeregowego. Naciśnij przycisk C (ten po lewej stronie, najbliżej przełącznika zasilania) i mów. Zostanie przechwycone 4 sekundy dźwięku.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Ready.
    Starting recording...
    Finished recording
    ```
💁 Ten kod znajdziesz w folderze [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal).
Twój program do nagrywania dźwięku odniósł sukces!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.