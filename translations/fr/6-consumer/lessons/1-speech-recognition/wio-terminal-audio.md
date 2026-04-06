# Capturer de l'audio - Wio Terminal

Dans cette partie de la leçon, vous allez écrire du code pour capturer de l'audio sur votre Wio Terminal. La capture audio sera contrôlée par l'un des boutons situés sur le dessus du Wio Terminal.

## Programmer l'appareil pour capturer de l'audio

Vous pouvez capturer de l'audio depuis le microphone en utilisant du code C++. Le Wio Terminal dispose seulement de 192KB de RAM, ce qui n'est pas suffisant pour capturer plus de quelques secondes d'audio. Il possède également 4MB de mémoire flash, qui peut être utilisée pour sauvegarder l'audio capturé.

Le microphone intégré capture un signal analogique, qui est ensuite converti en signal numérique utilisable par le Wio Terminal. Lors de la capture audio, les données doivent être capturées au bon moment - par exemple, pour capturer de l'audio à 16KHz, les données doivent être capturées exactement 16 000 fois par seconde, avec des intervalles égaux entre chaque échantillon. Plutôt que d'utiliser votre code pour gérer cela, vous pouvez utiliser le contrôleur d'accès direct à la mémoire (DMAC). Ce circuit peut capturer un signal et l'écrire en mémoire, sans interrompre le code en cours d'exécution sur le processeur.

✅ En savoir plus sur le DMA sur la [page d'accès direct à la mémoire sur Wikipedia](https://wikipedia.org/wiki/Direct_memory_access).

![L'audio du micro passe par un ADC puis par le DMAC. Celui-ci écrit dans un buffer. Lorsque ce buffer est plein, il est traité et le DMAC écrit dans un second buffer](../../../../../translated_images/fr/dmac-adc-buffers.4509aee49145c90b.webp)

Le DMAC peut capturer de l'audio depuis l'ADC à des intervalles fixes, comme 16 000 fois par seconde pour un audio à 16KHz. Il peut écrire ces données capturées dans un buffer mémoire pré-alloué, et lorsque celui-ci est plein, le rendre disponible pour que votre code le traite. L'utilisation de cette mémoire peut retarder la capture audio, mais vous pouvez configurer plusieurs buffers. Le DMAC écrit dans le buffer 1, puis lorsqu'il est plein, il notifie votre code pour traiter le buffer 1, tandis que le DMAC écrit dans le buffer 2. Lorsque le buffer 2 est plein, il notifie votre code et revient à l'écriture dans le buffer 1. Ainsi, tant que vous traitez chaque buffer en moins de temps qu'il ne faut pour en remplir un, vous ne perdrez aucune donnée.

Une fois chaque buffer capturé, il peut être écrit dans la mémoire flash. La mémoire flash doit être écrite en utilisant des adresses définies, spécifiant où écrire et quelle taille écrire, similaire à la mise à jour d'un tableau de bytes en mémoire. La mémoire flash a une granularité, ce qui signifie que les opérations d'effacement et d'écriture dépendent non seulement d'une taille fixe, mais aussi d'un alignement sur cette taille. Par exemple, si la granularité est de 4096 bytes et que vous demandez un effacement à l'adresse 4200, cela pourrait effacer toutes les données de l'adresse 4096 à 8192. Cela signifie que lorsque vous écrivez les données audio dans la mémoire flash, elles doivent être en morceaux de la bonne taille.

### Tâche - configurer la mémoire flash

1. Créez un nouveau projet Wio Terminal en utilisant PlatformIO. Appelez ce projet `smart-timer`. Ajoutez du code dans la fonction `setup` pour configurer le port série.

1. Ajoutez les dépendances de bibliothèque suivantes au fichier `platformio.ini` pour accéder à la mémoire flash :

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. Ouvrez le fichier `main.cpp` et ajoutez la directive d'inclusion suivante pour la bibliothèque de mémoire flash en haut du fichier :

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD signifie Serial Flash Universal Driver, et est une bibliothèque conçue pour fonctionner avec tous les puces de mémoire flash.

1. Dans la fonction `setup`, ajoutez le code suivant pour configurer la bibliothèque de stockage flash :

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    Cette boucle s'exécute jusqu'à ce que la bibliothèque SFUD soit initialisée, puis active les lectures rapides. La mémoire flash intégrée peut être accédée en utilisant une interface périphérique série en file d'attente (QSPI), un type de contrôleur SPI qui permet un accès continu via une file d'attente avec une utilisation minimale du processeur. Cela rend la lecture et l'écriture dans la mémoire flash plus rapides.

1. Créez un nouveau fichier dans le dossier `src` appelé `flash_writer.h`.

1. Ajoutez ce qui suit en haut de ce fichier :

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    Cela inclut certains fichiers d'en-tête nécessaires, y compris le fichier d'en-tête de la bibliothèque SFUD pour interagir avec la mémoire flash.

1. Définissez une classe dans ce nouveau fichier d'en-tête appelée `FlashWriter` :

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. Dans la section `private`, ajoutez le code suivant :

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    Cela définit certains champs pour le buffer utilisé pour stocker les données avant de les écrire dans la mémoire flash. Il y a un tableau de bytes, `_sfudBuffer`, pour écrire les données, et lorsque celui-ci est plein, les données sont écrites dans la mémoire flash. Le champ `_sfudBufferPos` stocke la position actuelle pour écrire dans ce buffer, et `_sfudBufferWritePos` stocke la position dans la mémoire flash pour écrire. `_flash` est un pointeur vers la mémoire flash à écrire - certains microcontrôleurs ont plusieurs puces de mémoire flash.

1. Ajoutez la méthode suivante à la section `public` pour initialiser cette classe :

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

    Cela configure la mémoire flash sur le Wio Terminal pour écrire, et configure les buffers en fonction de la taille de grain de la mémoire flash. Cela se trouve dans une méthode `init`, plutôt qu'un constructeur, car cela doit être appelé après que la mémoire flash ait été configurée dans la fonction `setup`.

1. Ajoutez le code suivant à la section `public` :

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

    Ce code définit des méthodes pour écrire des bytes dans le système de stockage flash. Cela fonctionne en écrivant dans un buffer en mémoire qui est de la bonne taille pour la mémoire flash, et lorsque celui-ci est plein, il est écrit dans la mémoire flash, effaçant toutes les données existantes à cet emplacement. Il y a également une méthode `flushSfudBuffer` pour écrire un buffer incomplet, car les données capturées ne seront pas des multiples exacts de la taille de grain, donc la partie finale des données doit être écrite.

    > 💁 La partie finale des données écrira des données supplémentaires non désirées, mais cela est acceptable car seules les données nécessaires seront lues.

### Tâche - configurer la capture audio

1. Créez un nouveau fichier dans le dossier `src` appelé `config.h`.

1. Ajoutez ce qui suit en haut de ce fichier :

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    Ce code configure des constantes pour la capture audio.

    | Constante             | Valeur  | Description |
    | --------------------- | -----: | - |
    | RATE                  | 16000  | Le taux d'échantillonnage pour l'audio. 16 000 correspond à 16KHz |
    | SAMPLE_LENGTH_SECONDS | 4      | La durée de l'audio à capturer. Elle est définie à 4 secondes. Pour enregistrer un audio plus long, augmentez cette valeur. |
    | SAMPLES               | 64000  | Le nombre total d'échantillons audio qui seront capturés. Défini comme le taux d'échantillonnage * le nombre de secondes |
    | BUFFER_SIZE           | 128044 | La taille du buffer audio à capturer. L'audio sera capturé sous forme de fichier WAV, qui contient 44 bytes d'en-tête, puis 128 000 bytes de données audio (chaque échantillon fait 2 bytes) |
    | ADC_BUF_LEN           | 1600   | La taille des buffers à utiliser pour capturer l'audio depuis le DMAC |

    > 💁 Si vous trouvez que 4 secondes sont trop courtes pour demander un minuteur, vous pouvez augmenter la valeur `SAMPLE_LENGTH_SECONDS`, et toutes les autres valeurs seront recalculées.

1. Créez un nouveau fichier dans le dossier `src` appelé `mic.h`.

1. Ajoutez ce qui suit en haut de ce fichier :

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    Cela inclut certains fichiers d'en-tête nécessaires, y compris les fichiers `config.h` et `FlashWriter`.

1. Ajoutez ce qui suit pour définir une classe `Mic` qui peut capturer depuis le microphone :

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

    Cette classe contient actuellement seulement quelques champs pour suivre si l'enregistrement a commencé, et si un enregistrement est prêt à être utilisé. Lorsque le DMAC est configuré, il écrit continuellement dans des buffers mémoire, donc le drapeau `_isRecording` détermine si ces buffers doivent être traités ou ignorés. Le drapeau `_isRecordingReady` sera activé lorsque les 4 secondes d'audio requises auront été capturées. Le champ `_writer` est utilisé pour sauvegarder les données audio dans la mémoire flash.

    Une variable globale est ensuite déclarée pour une instance de la classe `Mic`.

1. Ajoutez le code suivant à la section `private` de la classe `Mic` :

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

    Ce code définit une méthode `configureDmaAdc` qui configure le DMAC, le connectant à l'ADC et le configurant pour remplir deux buffers alternants, `_adc_buf_0` et `_adc_buf_1`.

    > 💁 L'un des inconvénients du développement sur microcontrôleur est la complexité du code nécessaire pour interagir avec le matériel, car votre code fonctionne à un niveau très bas en interagissant directement avec le matériel. Ce code est plus complexe que ce que vous écririez pour un ordinateur monocarte ou un ordinateur de bureau, car il n'y a pas de système d'exploitation pour aider. Certaines bibliothèques sont disponibles pour simplifier cela, mais il reste beaucoup de complexité.

1. En dessous, ajoutez le code suivant :

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

    Ce code définit l'en-tête WAV comme une structure qui occupe 44 bytes de mémoire. Il écrit des détails dans cet en-tête concernant le taux, la taille et le nombre de canaux du fichier audio. Cet en-tête est ensuite écrit dans la mémoire flash.

1. En dessous de ce code, ajoutez ce qui suit pour déclarer une méthode appelée lorsque les buffers audio sont prêts à être traités :

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

    Les buffers audio sont des tableaux d'entiers 16 bits contenant l'audio provenant de l'ADC. L'ADC retourne des valeurs non signées sur 12 bits (0-1023), donc celles-ci doivent être converties en valeurs signées sur 16 bits, puis converties en 2 bytes pour être stockées sous forme de données binaires brutes.

    Ces bytes sont écrits dans les buffers de mémoire flash. L'écriture commence à l'index 44 - c'est le décalage des 44 bytes écrits comme en-tête du fichier WAV. Une fois tous les bytes nécessaires pour la durée audio requise capturés, les données restantes sont écrites dans la mémoire flash.

1. Dans la section `public` de la classe `Mic`, ajoutez le code suivant :

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

    Ce code sera appelé par le DMAC pour informer votre code de traiter les buffers. Il vérifie qu'il y a des données à traiter, et appelle la méthode `audioCallback` avec le buffer pertinent.

1. En dehors de la classe, après la déclaration `Mic mic;`, ajoutez le code suivant :

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    Le `DMAC_1_Handler` sera appelé par le DMAC lorsque les buffers seront prêts à être traités. Cette fonction est trouvée par son nom, donc elle doit simplement exister pour être appelée.

1. Ajoutez les deux méthodes suivantes à la section `public` de la classe `Mic` :

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

    La méthode `init` contient du code pour initialiser la classe `Mic`. Cette méthode configure la tension correcte pour la broche du microphone, configure l'écrivain de mémoire flash, écrit l'en-tête du fichier WAV, et configure le DMAC. La méthode `reset` réinitialise la mémoire flash et réécrit l'en-tête après que l'audio ait été capturé et utilisé.

### Tâche - capturer de l'audio

1. Dans le fichier `main.cpp`, ajoutez une directive d'inclusion pour le fichier d'en-tête `mic.h` :

    ```cpp
    #include "mic.h"
    ```

1. Dans la fonction `setup`, initialisez le bouton C. La capture audio commencera lorsque ce bouton sera pressé, et continuera pendant 4 secondes :

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. En dessous, initialisez le microphone, puis affichez dans la console que l'audio est prêt à être capturé :

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. Au-dessus de la fonction `loop`, définissez une fonction pour traiter l'audio capturé. Pour l'instant, cette fonction ne fait rien, mais plus tard dans cette leçon, elle enverra l'audio pour être converti en texte :

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. Ajoutez ce qui suit à la fonction `loop` :

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

    Ce code vérifie le bouton C, et si celui-ci est pressé et que l'enregistrement n'a pas commencé, alors le champ `_isRecording` de la classe `Mic` est défini sur true. Cela entraînera la méthode `audioCallback` de la classe `Mic` à stocker l'audio jusqu'à ce que 4 secondes aient été capturées. Une fois les 4 secondes d'audio capturées, le champ `_isRecording` est défini sur false, et le champ `_isRecordingReady` est défini sur true. Cela est ensuite vérifié dans la fonction `loop`, et lorsque c'est vrai, la fonction `processAudio` est appelée, puis la classe `Mic` est réinitialisée.

1. Compilez ce code, téléchargez-le sur votre Wio Terminal et testez-le via le moniteur série. Appuyez sur le bouton C (celui situé sur le côté gauche, le plus proche de l'interrupteur d'alimentation), et parlez. 4 secondes d'audio seront capturées.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Ready.
    Starting recording...
    Finished recording
    ```
💁 Vous pouvez trouver ce code dans le dossier [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal).
😀 Votre programme d'enregistrement audio a été un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de faire appel à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.