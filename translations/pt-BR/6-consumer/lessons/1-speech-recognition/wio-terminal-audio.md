# Capturar áudio - Wio Terminal

Nesta parte da lição, você escreverá código para capturar áudio no seu Wio Terminal. A captura de áudio será controlada por um dos botões na parte superior do Wio Terminal.

## Programar o dispositivo para capturar áudio

Você pode capturar áudio do microfone usando código em C++. O Wio Terminal possui apenas 192KB de RAM, o que não é suficiente para capturar mais do que alguns segundos de áudio. Ele também possui 4MB de memória flash, que pode ser usada para salvar o áudio capturado.

O microfone embutido captura um sinal analógico, que é convertido em um sinal digital que o Wio Terminal pode usar. Ao capturar áudio, os dados precisam ser capturados no momento correto - por exemplo, para capturar áudio a 16KHz, o áudio precisa ser capturado exatamente 16.000 vezes por segundo, com intervalos iguais entre cada amostra. Em vez de usar seu código para fazer isso, você pode usar o controlador de acesso direto à memória (DMAC). Este é um circuito que pode capturar um sinal de algum lugar e gravá-lo na memória, sem interromper o código que está sendo executado no processador.

✅ Leia mais sobre DMA na [página de acesso direto à memória na Wikipedia](https://wikipedia.org/wiki/Direct_memory_access).

![O áudio do microfone vai para um ADC e depois para o DMAC. Este escreve em um buffer. Quando este buffer está cheio, ele é processado e o DMAC escreve em um segundo buffer](../../../../../translated_images/pt-BR/dmac-adc-buffers.4509aee49145c90b.webp)

O DMAC pode capturar áudio do ADC em intervalos fixos, como 16.000 vezes por segundo para áudio de 16KHz. Ele pode gravar esses dados capturados em um buffer de memória pré-alocado e, quando este estiver cheio, torná-lo disponível para o seu código processar. Usar essa memória pode atrasar a captura de áudio, mas você pode configurar múltiplos buffers. O DMAC escreve no buffer 1 e, quando este está cheio, notifica seu código para processar o buffer 1, enquanto o DMAC escreve no buffer 2. Quando o buffer 2 está cheio, ele notifica seu código e volta a escrever no buffer 1. Dessa forma, desde que você processe cada buffer em menos tempo do que leva para preencher um, você não perderá nenhum dado.

Uma vez que cada buffer tenha sido capturado, ele pode ser gravado na memória flash. A memória flash precisa ser gravada usando endereços definidos, especificando onde gravar e o tamanho da gravação, semelhante à atualização de um array de bytes na memória. A memória flash possui granularidade, o que significa que as operações de apagar e gravar dependem não apenas de serem de um tamanho fixo, mas de estarem alinhadas a esse tamanho. Por exemplo, se a granularidade for de 4096 bytes e você solicitar um apagamento no endereço 4200, isso pode apagar todos os dados do endereço 4096 ao 8192. Isso significa que, ao gravar os dados de áudio na memória flash, eles precisam estar em blocos do tamanho correto.

### Tarefa - configurar a memória flash

1. Crie um novo projeto Wio Terminal usando o PlatformIO. Chame este projeto de `smart-timer`. Adicione código na função `setup` para configurar a porta serial.

1. Adicione as seguintes dependências de biblioteca ao arquivo `platformio.ini` para fornecer acesso à memória flash:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. Abra o arquivo `main.cpp` e adicione a seguinte diretiva de inclusão para a biblioteca de memória flash no topo do arquivo:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD significa Serial Flash Universal Driver, e é uma biblioteca projetada para funcionar com todos os chips de memória flash.

1. Na função `setup`, adicione o seguinte código para configurar a biblioteca de armazenamento flash:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    Este código faz um loop até que a biblioteca SFUD seja inicializada e, em seguida, ativa leituras rápidas. A memória flash embutida pode ser acessada usando uma Interface Serial Periférica em Fila (QSPI), um tipo de controlador SPI que permite acesso contínuo via fila com uso mínimo do processador. Isso torna mais rápido ler e gravar na memória flash.

1. Crie um novo arquivo na pasta `src` chamado `flash_writer.h`.

1. Adicione o seguinte ao topo deste arquivo:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    Isso inclui alguns arquivos de cabeçalho necessários, incluindo o arquivo de cabeçalho da biblioteca SFUD para interagir com a memória flash.

1. Defina uma classe neste novo arquivo de cabeçalho chamada `FlashWriter`:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. Na seção `private`, adicione o seguinte código:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    Isso define alguns campos para o buffer usado para armazenar dados antes de gravá-los na memória flash. Há um array de bytes, `_sfudBuffer`, para gravar dados, e quando este está cheio, os dados são gravados na memória flash. O campo `_sfudBufferPos` armazena a posição atual para gravar neste buffer, e `_sfudBufferWritePos` armazena a posição na memória flash para gravar. `_flash` é um ponteiro para a memória flash onde os dados serão gravados - alguns microcontroladores possuem múltiplos chips de memória flash.

1. Adicione o seguinte método à seção `public` para inicializar esta classe:

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

    Isso configura a memória flash no Wio Terminal para gravar e define os buffers com base no tamanho de granularidade da memória flash. Isso está em um método `init`, em vez de um construtor, pois precisa ser chamado após a memória flash ter sido configurada na função `setup`.

1. Adicione o seguinte código à seção `public`:

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

    Este código define métodos para gravar bytes no sistema de armazenamento flash. Ele funciona gravando em um buffer na memória que tem o tamanho correto para a memória flash e, quando este está cheio, é gravado na memória flash, apagando quaisquer dados existentes naquele local. Há também um método `flushSfudBuffer` para gravar um buffer incompleto, já que os dados capturados não serão múltiplos exatos do tamanho de granularidade, então a parte final dos dados precisa ser gravada.

    > 💁 A parte final dos dados gravará dados adicionais indesejados, mas isso não é um problema, pois apenas os dados necessários serão lidos.

### Tarefa - configurar a captura de áudio

1. Crie um novo arquivo na pasta `src` chamado `config.h`.

1. Adicione o seguinte ao topo deste arquivo:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    Este código configura algumas constantes para a captura de áudio.

    | Constante             | Valor  | Descrição |
    | --------------------- | -----: | - |
    | RATE                  | 16000  | A taxa de amostragem do áudio. 16.000 é 16KHz |
    | SAMPLE_LENGTH_SECONDS | 4      | A duração do áudio a ser capturado. Está configurado para 4 segundos. Para gravar áudio mais longo, aumente este valor. |
    | SAMPLES               | 64000  | O número total de amostras de áudio que serão capturadas. Configurado para a taxa de amostragem * o número de segundos |
    | BUFFER_SIZE           | 128044 | O tamanho do buffer de áudio a ser capturado. O áudio será capturado como um arquivo WAV, que possui 44 bytes de cabeçalho e 128.000 bytes de dados de áudio (cada amostra tem 2 bytes) |
    | ADC_BUF_LEN           | 1600   | O tamanho dos buffers usados para capturar áudio do DMAC |

    > 💁 Se você achar que 4 segundos é muito curto para solicitar um temporizador, pode aumentar o valor de `SAMPLE_LENGTH_SECONDS`, e todos os outros valores serão recalculados.

1. Crie um novo arquivo na pasta `src` chamado `mic.h`.

1. Adicione o seguinte ao topo deste arquivo:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    Isso inclui alguns arquivos de cabeçalho necessários, incluindo os arquivos `config.h` e `FlashWriter`.

1. Adicione o seguinte para definir uma classe `Mic` que pode capturar do microfone:

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

    Esta classe atualmente possui apenas alguns campos para rastrear se a gravação foi iniciada e se uma gravação está pronta para ser usada. Quando o DMAC é configurado, ele escreve continuamente em buffers de memória, então o sinalizador `_isRecording` determina se esses devem ser processados ou ignorados. O sinalizador `_isRecordingReady` será definido quando os 4 segundos necessários de áudio tiverem sido capturados. O campo `_writer` é usado para salvar os dados de áudio na memória flash.

    Uma variável global é então declarada para uma instância da classe `Mic`.

1. Adicione o seguinte código à seção `private` da classe `Mic`:

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

    Este código define um método `configureDmaAdc` que configura o DMAC, conectando-o ao ADC e configurando-o para preencher dois buffers alternados, `_adc_buf_0` e `_adc_buf_1`.

    > 💁 Uma das desvantagens do desenvolvimento para microcontroladores é a complexidade do código necessário para interagir com o hardware, já que seu código opera em um nível muito baixo, interagindo diretamente com o hardware. Este código é mais complexo do que o que você escreveria para um computador de placa única ou desktop, pois não há sistema operacional para ajudar. Existem algumas bibliotecas disponíveis que podem simplificar isso, mas ainda há muita complexidade.

1. Abaixo disso, adicione o seguinte código:

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

    Este código define o cabeçalho WAV como uma estrutura que ocupa 44 bytes de memória. Ele escreve detalhes sobre a taxa, tamanho e número de canais do arquivo de áudio. Este cabeçalho é então gravado na memória flash.

1. Abaixo deste código, adicione o seguinte para declarar um método a ser chamado quando os buffers de áudio estiverem prontos para serem processados:

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

    Os buffers de áudio são arrays de inteiros de 16 bits contendo o áudio do ADC. O ADC retorna valores sem sinal de 12 bits (0-1023), então estes precisam ser convertidos em valores de 16 bits com sinal e, em seguida, convertidos em 2 bytes para serem armazenados como dados binários brutos.

    Esses bytes são gravados nos buffers de memória flash. A gravação começa no índice 44 - este é o deslocamento dos 44 bytes gravados como o cabeçalho do arquivo WAV. Uma vez que todos os bytes necessários para a duração do áudio tenham sido capturados, os dados restantes são gravados na memória flash.

1. Na seção `public` da classe `Mic`, adicione o seguinte código:

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

    Este código será chamado pelo DMAC para informar ao seu código que os buffers estão prontos para serem processados. Ele verifica se há dados para processar e chama o método `audioCallback` com o buffer relevante.

1. Fora da classe, após a declaração `Mic mic;`, adicione o seguinte código:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    O `DMAC_1_Handler` será chamado pelo DMAC quando os buffers estiverem prontos para serem processados. Esta função é encontrada pelo nome, então só precisa existir para ser chamada.

1. Adicione os seguintes dois métodos à seção `public` da classe `Mic`:

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

    O método `init` contém código para inicializar a classe `Mic`. Este método define a voltagem correta para o pino do microfone, configura o gravador de memória flash, escreve o cabeçalho do arquivo WAV e configura o DMAC. O método `reset` redefine a memória flash e reescreve o cabeçalho após o áudio ter sido capturado e usado.

### Tarefa - capturar áudio

1. No arquivo `main.cpp`, adicione uma diretiva de inclusão para o arquivo de cabeçalho `mic.h`:

    ```cpp
    #include "mic.h"
    ```

1. Na função `setup`, inicialize o botão C. A captura de áudio começará quando este botão for pressionado e continuará por 4 segundos:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. Abaixo disso, inicialize o microfone e, em seguida, imprima no console que o áudio está pronto para ser capturado:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. Acima da função `loop`, defina uma função para processar o áudio capturado. Por enquanto, esta função não faz nada, mas mais tarde nesta lição ela enviará o áudio para ser convertido em texto:

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. Adicione o seguinte à função `loop`:

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

    Este código verifica o botão C e, se este for pressionado e a gravação não tiver começado, o campo `_isRecording` da classe `Mic` é definido como verdadeiro. Isso fará com que o método `audioCallback` da classe `Mic` armazene o áudio até que 4 segundos tenham sido capturados. Uma vez que 4 segundos de áudio tenham sido capturados, o campo `_isRecording` é definido como falso e o campo `_isRecordingReady` é definido como verdadeiro. Isso é então verificado na função `loop` e, quando verdadeiro, a função `processAudio` é chamada e a classe `Mic` é redefinida.

1. Compile este código, carregue-o no seu Wio Terminal e teste-o através do monitor serial. Pressione o botão C (o botão do lado esquerdo, mais próximo do interruptor de energia) e fale. 4 segundos de áudio serão capturados.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Ready.
    Starting recording...
    Finished recording
    ```
💁 Você pode encontrar este código na pasta [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal).
😀 Seu programa de gravação de áudio foi um sucesso!

---

**Aviso Legal**:  
Este documento foi traduzido utilizando o serviço de tradução por IA [Co-op Translator](https://github.com/Azure/co-op-translator). Embora nos esforcemos para garantir a precisão, esteja ciente de que traduções automáticas podem conter erros ou imprecisões. O documento original em seu idioma nativo deve ser considerado a fonte oficial. Para informações críticas, recomenda-se a tradução profissional feita por humanos. Não nos responsabilizamos por quaisquer mal-entendidos ou interpretações equivocadas decorrentes do uso desta tradução.