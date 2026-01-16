<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2f336726b9410e97c3aaed76cc89b0d8",
  "translation_date": "2025-08-27T20:38:14+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-audio.md",
  "language_code": "el"
}
-->
# Καταγραφή ήχου - Wio Terminal

Σε αυτό το μέρος του μαθήματος, θα γράψετε κώδικα για να καταγράψετε ήχο στο Wio Terminal σας. Η καταγραφή ήχου θα ελέγχεται από ένα από τα κουμπιά στην κορυφή του Wio Terminal.

## Προγραμματίστε τη συσκευή για καταγραφή ήχου

Μπορείτε να καταγράψετε ήχο από το μικρόφωνο χρησιμοποιώντας κώδικα C++. Το Wio Terminal διαθέτει μόνο 192KB RAM, που δεν είναι αρκετή για να καταγράψει περισσότερα από λίγα δευτερόλεπτα ήχου. Ωστόσο, διαθέτει 4MB μνήμης flash, η οποία μπορεί να χρησιμοποιηθεί για την αποθήκευση του καταγεγραμμένου ήχου.

Το ενσωματωμένο μικρόφωνο καταγράφει ένα αναλογικό σήμα, το οποίο μετατρέπεται σε ψηφιακό σήμα που μπορεί να χρησιμοποιήσει το Wio Terminal. Κατά την καταγραφή ήχου, τα δεδομένα πρέπει να καταγράφονται στον σωστό χρόνο - για παράδειγμα, για καταγραφή ήχου στα 16KHz, ο ήχος πρέπει να καταγράφεται ακριβώς 16.000 φορές το δευτερόλεπτο, με ίσα διαστήματα μεταξύ κάθε δείγματος. Αντί να χρησιμοποιήσετε τον κώδικά σας για αυτό, μπορείτε να χρησιμοποιήσετε τον ελεγκτή άμεσης πρόσβασης μνήμης (DMAC). Αυτό είναι ένα κύκλωμα που μπορεί να καταγράψει ένα σήμα από κάπου και να το γράψει στη μνήμη, χωρίς να διακόπτει τον κώδικα που εκτελείται στον επεξεργαστή.

✅ Διαβάστε περισσότερα για το DMA στη [σελίδα άμεσης πρόσβασης μνήμης στη Wikipedia](https://wikipedia.org/wiki/Direct_memory_access).

![Ο ήχος από το μικρόφωνο περνάει σε έναν ADC και στη συνέχεια στον DMAC. Αυτός γράφει σε έναν buffer. Όταν αυτός ο buffer γεμίσει, επεξεργάζεται και ο DMAC γράφει σε έναν δεύτερο buffer](../../../../../translated_images/el/dmac-adc-buffers.4509aee49145c90bc2e1be472b8ed2ddfcb2b6a81ad3e559114aca55f5fff759.png)

Ο DMAC μπορεί να καταγράψει ήχο από τον ADC σε σταθερά διαστήματα, όπως 16.000 φορές το δευτερόλεπτο για ήχο 16KHz. Μπορεί να γράψει αυτά τα δεδομένα σε έναν προ-κατανεμημένο buffer μνήμης, και όταν αυτός γεμίσει, να τον κάνει διαθέσιμο στον κώδικά σας για επεξεργασία. Η χρήση αυτής της μνήμης μπορεί να καθυστερήσει την καταγραφή ήχου, αλλά μπορείτε να ρυθμίσετε πολλαπλούς buffers. Ο DMAC γράφει στον buffer 1, και όταν αυτός γεμίσει, ειδοποιεί τον κώδικά σας να επεξεργαστεί τον buffer 1, ενώ ο DMAC γράφει στον buffer 2. Όταν ο buffer 2 γεμίσει, ειδοποιεί τον κώδικά σας και επιστρέφει στη γραφή στον buffer 1. Με αυτόν τον τρόπο, όσο επεξεργάζεστε κάθε buffer σε λιγότερο χρόνο από όσο χρειάζεται για να γεμίσει ένας, δεν θα χάσετε δεδομένα.

Μόλις καταγραφεί κάθε buffer, μπορεί να γραφτεί στη μνήμη flash. Η μνήμη flash πρέπει να γράφεται χρησιμοποιώντας καθορισμένες διευθύνσεις, προσδιορίζοντας πού να γράψετε και πόσο μεγάλο να γράψετε, παρόμοια με την ενημέρωση ενός πίνακα byte στη μνήμη. Η μνήμη flash έχει granularité, που σημαίνει ότι οι λειτουργίες διαγραφής και εγγραφής βασίζονται όχι μόνο στο να είναι σταθερού μεγέθους, αλλά και στην ευθυγράμμιση με αυτό το μέγεθος. Για παράδειγμα, αν η granularité είναι 4096 byte και ζητήσετε διαγραφή στη διεύθυνση 4200, μπορεί να διαγράψει όλα τα δεδομένα από τη διεύθυνση 4096 έως 8192. Αυτό σημαίνει ότι όταν γράφετε τα δεδομένα ήχου στη μνήμη flash, πρέπει να είναι σε κομμάτια του σωστού μεγέθους.

### Εργασία - ρυθμίστε τη μνήμη flash

1. Δημιουργήστε ένα ολοκαίνουργιο έργο Wio Terminal χρησιμοποιώντας το PlatformIO. Ονομάστε αυτό το έργο `smart-timer`. Προσθέστε κώδικα στη συνάρτηση `setup` για να ρυθμίσετε τη σειριακή θύρα.

1. Προσθέστε τις ακόλουθες εξαρτήσεις βιβλιοθήκης στο αρχείο `platformio.ini` για να παρέχετε πρόσβαση στη μνήμη flash:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. Ανοίξτε το αρχείο `main.cpp` και προσθέστε την ακόλουθη οδηγία `include` για τη βιβλιοθήκη μνήμης flash στην κορυφή του αρχείου:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 Το SFUD σημαίνει Serial Flash Universal Driver και είναι μια βιβλιοθήκη σχεδιασμένη να λειτουργεί με όλα τα τσιπ μνήμης flash.

1. Στη συνάρτηση `setup`, προσθέστε τον ακόλουθο κώδικα για να ρυθμίσετε τη βιβλιοθήκη αποθήκευσης flash:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    Αυτό επαναλαμβάνεται μέχρι να αρχικοποιηθεί η βιβλιοθήκη SFUD και στη συνέχεια ενεργοποιεί τις γρήγορες αναγνώσεις. Η ενσωματωμένη μνήμη flash μπορεί να προσπελαστεί χρησιμοποιώντας ένα Queued Serial Peripheral Interface (QSPI), έναν τύπο ελεγκτή SPI που επιτρέπει συνεχή πρόσβαση μέσω μιας ουράς με ελάχιστη χρήση του επεξεργαστή. Αυτό την καθιστά ταχύτερη για ανάγνωση και εγγραφή στη μνήμη flash.

1. Δημιουργήστε ένα νέο αρχείο στον φάκελο `src` με όνομα `flash_writer.h`.

1. Προσθέστε τα ακόλουθα στην κορυφή αυτού του αρχείου:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    Αυτό περιλαμβάνει μερικά απαραίτητα αρχεία κεφαλίδας, συμπεριλαμβανομένου του αρχείου κεφαλίδας για τη βιβλιοθήκη SFUD για αλληλεπίδραση με τη μνήμη flash.

1. Ορίστε μια κλάση σε αυτό το νέο αρχείο κεφαλίδας με όνομα `FlashWriter`:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. Στην ενότητα `private`, προσθέστε τον ακόλουθο κώδικα:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    Αυτό ορίζει μερικά πεδία για τον buffer που θα χρησιμοποιηθεί για την αποθήκευση δεδομένων πριν από τη γραφή στη μνήμη flash. Υπάρχει ένας πίνακας byte, `_sfudBuffer`, για τη γραφή δεδομένων, και όταν αυτός γεμίσει, τα δεδομένα γράφονται στη μνήμη flash. Το πεδίο `_sfudBufferPos` αποθηκεύει την τρέχουσα θέση για εγγραφή σε αυτόν τον buffer, και το `_sfudBufferWritePos` αποθηκεύει τη θέση στη μνήμη flash για εγγραφή. Το `_flash` είναι ένας δείκτης στη μνήμη flash για εγγραφή - ορισμένοι μικροελεγκτές διαθέτουν πολλαπλά τσιπ μνήμης flash.

1. Προσθέστε την ακόλουθη μέθοδο στην ενότητα `public` για να αρχικοποιήσετε αυτήν την κλάση:

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

    Αυτό ρυθμίζει τη μνήμη flash στο Wio Terminal για εγγραφή και ρυθμίζει τους buffers με βάση το μέγεθος του grain της μνήμης flash. Αυτό βρίσκεται σε μια μέθοδο `init`, αντί για έναν κατασκευαστή, καθώς πρέπει να κληθεί μετά τη ρύθμιση της μνήμης flash στη συνάρτηση `setup`.

1. Προσθέστε τον ακόλουθο κώδικα στην ενότητα `public`:

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

    Αυτός ο κώδικας ορίζει μεθόδους για τη γραφή byte στο σύστημα αποθήκευσης flash. Λειτουργεί γράφοντας σε έναν buffer στη μνήμη που έχει το σωστό μέγεθος για τη μνήμη flash, και όταν αυτός γεμίσει, γράφεται στη μνήμη flash, διαγράφοντας τυχόν υπάρχοντα δεδομένα σε αυτήν τη θέση. Υπάρχει επίσης μια μέθοδος `flushSfudBuffer` για τη γραφή ενός μη ολοκληρωμένου buffer, καθώς τα δεδομένα που καταγράφονται δεν θα είναι ακριβή πολλαπλάσια του μεγέθους του grain, οπότε το τελικό μέρος των δεδομένων πρέπει να γραφτεί.

    > 💁 Το τελικό μέρος των δεδομένων θα γράψει επιπλέον ανεπιθύμητα δεδομένα, αλλά αυτό είναι εντάξει καθώς θα διαβαστούν μόνο τα απαραίτητα δεδομένα.

### Εργασία - ρυθμίστε την καταγραφή ήχου

1. Δημιουργήστε ένα νέο αρχείο στον φάκελο `src` με όνομα `config.h`.

1. Προσθέστε τα ακόλουθα στην κορυφή αυτού του αρχείου:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    Αυτός ο κώδικας ρυθμίζει μερικές σταθερές για την καταγραφή ήχου.

    | Σταθερά               | Τιμή   | Περιγραφή |
    | --------------------- | -----: | - |
    | RATE                  | 16000  | Ο ρυθμός δειγματοληψίας για τον ήχο. 16.000 είναι 16KHz |
    | SAMPLE_LENGTH_SECONDS | 4      | Η διάρκεια του ήχου που θα καταγραφεί. Αυτό έχει οριστεί σε 4 δευτερόλεπτα. Για να καταγράψετε μεγαλύτερο ήχο, αυξήστε αυτήν την τιμή. |
    | SAMPLES               | 64000  | Ο συνολικός αριθμός δειγμάτων ήχου που θα καταγραφούν. Ορίζεται ως ο ρυθμός δειγματοληψίας * ο αριθμός των δευτερολέπτων |
    | BUFFER_SIZE           | 128044 | Το μέγεθος του buffer ήχου για καταγραφή. Ο ήχος θα καταγραφεί ως αρχείο WAV, το οποίο είναι 44 byte κεφαλίδας, και στη συνέχεια 128.000 byte δεδομένων ήχου (κάθε δείγμα είναι 2 byte) |
    | ADC_BUF_LEN           | 1600   | Το μέγεθος των buffers που θα χρησιμοποιηθούν για την καταγραφή ήχου από τον DMAC |

    > 💁 Αν διαπιστώσετε ότι τα 4 δευτερόλεπτα είναι πολύ λίγα για να ζητήσετε έναν χρονοδιακόπτη, μπορείτε να αυξήσετε την τιμή `SAMPLE_LENGTH_SECONDS`, και όλες οι άλλες τιμές θα επαναϋπολογιστούν.

1. Δημιουργήστε ένα νέο αρχείο στον φάκελο `src` με όνομα `mic.h`.

1. Προσθέστε τα ακόλουθα στην κορυφή αυτού του αρχείου:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    Αυτό περιλαμβάνει μερικά απαραίτητα αρχεία κεφαλίδας, συμπεριλαμβανομένων των αρχείων `config.h` και `FlashWriter`.

1. Προσθέστε τα ακόλουθα για να ορίσετε μια κλάση `Mic` που μπορεί να καταγράψει από το μικρόφωνο:

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

    Αυτή η κλάση έχει προς το παρόν μόνο μερικά πεδία για να παρακολουθεί αν η καταγραφή έχει ξεκινήσει και αν μια καταγραφή είναι έτοιμη για χρήση. Όταν ο DMAC ρυθμιστεί, γράφει συνεχώς σε buffers μνήμης, οπότε η σημαία `_isRecording` καθορίζει αν αυτά πρέπει να επεξεργαστούν ή να αγνοηθούν. Η σημαία `_isRecordingReady` θα οριστεί όταν καταγραφούν τα απαιτούμενα 4 δευτερόλεπτα ήχου. Το πεδίο `_writer` χρησιμοποιείται για την αποθήκευση των δεδομένων ήχου στη μνήμη flash.

    Έπειτα δηλώνεται μια καθολική μεταβλητή για μια παρουσία της κλάσης `Mic`.

1. Προσθέστε τον ακόλουθο κώδικα στην ενότητα `private` της κλάσης `Mic`:

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

    Αυτός ο κώδικας ορίζει μια μέθοδο `configureDmaAdc` που ρυθμίζει τον DMAC, συνδέοντάς τον με τον ADC και ρυθμίζοντάς τον να γεμίζει δύο διαφορετικούς εναλλασσόμενους buffers, `_adc_buf_0` και `_adc_buf_1`.

    > 💁 Ένα από τα μειονεκτήματα της ανάπτυξης για μικροελεγκτές είναι η πολυπλοκότητα του κώδικα που απαιτείται για την αλληλεπίδραση με το υλικό, καθώς ο κώδικάς σας εκτελείται σε πολύ χαμηλό επίπεδο αλληλεπιδρώντας απευθείας με το υλικό. Αυτός ο κώδικας είναι πιο περίπλοκος από αυτόν που θα γράφατε για έναν υπολογιστή ή έναν υπολογιστή μονού πίνακα, καθώς δεν υπάρχει λειτουργικό σύστημα για να βοηθήσει. Υπάρχουν διαθέσιμες βιβλιοθήκες που μπορούν να απλοποιήσουν αυτό, αλλά εξακολουθεί να υπάρχει αρκετή πολυπλοκότητα.

1. Παρακάτω, προσθέστε τον ακόλουθο κώδικα:

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

    Αυτός ο κώδικας ορίζει την κεφαλίδα WAV ως μια δομή που καταλαμβάνει 44 byte μνήμης. Γράφει λεπτομέρειες σε αυτήν σχετικά με τον ρυθμό αρχείου ήχου, το μέγεθος και τον αριθμό των καναλιών. Αυτή η κεφαλίδα στη συνέχεια γράφεται στη μνήμη flash.

1. Παρακάτω από αυτόν τον κώδικα, προσθέστε τα ακόλουθα για να δηλώσετε μια μέθοδο που θα καλείται όταν οι buffers ήχου είναι έτοιμοι για επεξεργασία:

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

    Οι buffers ήχου είναι πίνακες 16-bit ακέραιων που περιέχουν τον ήχο από τον ADC. Ο ADC επιστρέφει 12-bit μη υπογεγραμμένες τιμές (0-1023), οπότε αυτές πρέπει να μετατραπούν σε 16-bit υπογεγραμμένες τιμές και στη συνέχεια να μετατραπούν σε 2 byte για να αποθηκευτούν ως ακατέργαστα δυαδικά δεδομένα.

    Αυτά τα byte γράφονται στους buffers μνήμης flash. Η εγγραφή ξεκινά από τον δείκτη 44 - αυτή είναι η μετατόπιση από τα 44 byte που γράφτηκαν ως κεφαλίδα αρχείου WAV. Μόλις καταγραφούν όλα τα byte που χρειάζονται για την απαιτούμενη διάρκεια ήχου, τα υπόλοιπα δεδομένα γράφονται στη μνήμη flash.

1. Στην ενότητα `public` της κλάσης `Mic`, προσθέστε τον ακόλουθο κώδικα:

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

    Αυτός ο κώδικας θα καλείται από τον DMAC για να ενημερώσει τον κώδικά σας να επεξεργαστεί τους buffers. Ελέγχει ότι υπάρχουν δεδομένα για επεξεργασία και καλεί τη μέθοδο `audioCallback` με τον σχετικό buffer.

1. Εκτός της κλάσης, μετά τη δήλωση `Mic mic;`, προσθέστε τον ακόλουθο κώδικα:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    Ο `DMAC_1_Handler` θα καλείται από τον DMAC όταν οι buffers είναι έτοιμοι για επεξεργασία. Αυτή η συνάρτηση εντοπίζεται με το όνομα, οπότε απλώς πρέπει να υπάρχει για να καλείται.

1. Προσθέστε τις ακόλουθες δύο μεθόδους στην ενότητα `public` της κλάσης `Mic`:

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

    Η μέθοδος `init` περιέχει κώδικα για την αρχικοποίηση της κλάσης `Mic`. Αυτή η μέθοδος ρυθμίζει τη σωστή τάση για την ακίδα του μικροφώνου, ρυθμίζει τον συγγραφέα μνήμης flash, γράφει την κεφαλίδα WAV και ρυθμίζει τον DMAC. Η μέθοδος `reset` επαναφέρει τη μνήμη flash και ξαναγράφει την κεφαλίδα μετά την καταγραφή και χρήση του ήχου.

### Εργασία - καταγράψτε ήχο

1. Στο αρχείο `main.cpp`, προσθέστε μια οδηγία `include` για το αρχείο κεφαλίδας `mic.h`:

    ```cpp
    #include "mic.h"
    ```

1. Στη συνάρτηση `setup`, αρχικοποιήστε το κουμπί C. Η καταγραφή ήχου θα ξεκινήσει όταν πατηθεί αυτό το κουμπί και θα συνεχιστεί για 4 δευτερόλεπτα:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. Παρακάτω από αυτό, αρχικοποιήστε το μικρόφωνο και στη συνέχεια εκτυπώστε στην κονσόλα ότι ο ήχος είναι έτοιμος για καταγραφή:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. Πάνω από τη συνάρτηση `loop`, ορίστε μια συνάρτηση για την επεξεργασία του καταγεγραμμένου ήχου. Προς το παρόν,
> 💁 Μπορείτε να βρείτε αυτόν τον κώδικα στον φάκελο [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal).
😀 Το πρόγραμμα ηχογράφησης ήχου σας ήταν επιτυχία!

---

**Αποποίηση ευθύνης**:  
Αυτό το έγγραφο έχει μεταφραστεί χρησιμοποιώντας την υπηρεσία αυτόματης μετάφρασης [Co-op Translator](https://github.com/Azure/co-op-translator). Παρόλο που καταβάλλουμε προσπάθειες για ακρίβεια, παρακαλούμε να έχετε υπόψη ότι οι αυτοματοποιημένες μεταφράσεις ενδέχεται να περιέχουν λάθη ή ανακρίβειες. Το πρωτότυπο έγγραφο στη μητρική του γλώσσα θα πρέπει να θεωρείται η αυθεντική πηγή. Για κρίσιμες πληροφορίες, συνιστάται επαγγελματική ανθρώπινη μετάφραση. Δεν φέρουμε ευθύνη για τυχόν παρεξηγήσεις ή εσφαλμένες ερμηνείες που προκύπτουν από τη χρήση αυτής της μετάφρασης.