<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2f336726b9410e97c3aaed76cc89b0d8",
  "translation_date": "2026-01-07T03:25:36+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-audio.md",
  "language_code": "te"
}
-->
# ఆడియోను క్యాప్చర్ చేయండి - Wio టెర్మినల్

పాఠం యొక్క ఈ భాగంలో, మీరు మీ Wio టెర్మినల్ పై ఆడియోను క్యాప్చర్ చేయడానికి కోడ్ రాస్తారు. ఆడియో క్యాప్చర్ Wio టెర్మినల్ పై ఉన్న టాప్‌లో ఒక బటన్ ద్వారా నియంత్రించబడుతుంది.

## డివైస్‌ను ఆడియో క్యాప్చర్ చేయడానికి ప్రోగ్రామ్ చేయండి

మీరు C++ కోడ్ ఉపయోగించి మైక్రోఫోన్ నుండి ఆడియోను క్యాప్చర్ చేయవచ్చు. Wio టెర్మినల్ కి కేవలం 192KB RAM మాత్రమే ఉంది, ఇది రెండు సెకండ్లకు ఎక్కువకాలం ఆడియో క్యాప్చర్ చేయడానికి సరిపోదు. దీనికంటే 4MB ఫ్లాష్ మెమరీ ఉంది, కాబట్టి ఇది ఉపయోగించి క్యాప్చర్ చేసిన ఆడియోను ఫ్లాష్ మెమరీలో సేవ్ చేయవచ్చు.

ఇంకో సందేశం ద్వారా మైక్రోఫోన్ అనలాగ్ సిగ్నల్‌ను క్యాప్చర్ చేస్తుంది, ఇది డిజిటల్ సిగ్నల్‌గా మార్చి Wio టెర్మినల్ ఉపయోగించేలా చేస్తుంది. ఆడియో క్యాప్చర్ చేస్తూ ఉండేటప్పుడు డేటాను కచ్చితమైన సమయంలో క్యాప్చర్ చేయాలి - ఉదాహరణకి 16KHz లో ఆడియోను క్యాప్చర్ చెయ్యాలంటే, ఆడియోను ప్రతీస్నేహం 16,000 సార్లు ఒక సెకండు పాటు చిత్తశుద్ధిగా క్యాప్చర్ చేయాలి. మీ కోడ్ ఉపయోగించి ఇది చేయకుండా, మీరు నేరుగా మెమరీ యాక్సెస్ కంట్రోలర్ (DMAC) ఉపయోగించవచ్చు. ఇది ఒక సర్క్యూటరీ, ఇది ఎక్కడైనా నుండి సిగ్నల్ క్యాప్చర్ చేసి మెమరీలో రాసే విధంగా పని చేస్తుంది, ప్రాసెసర్ పై కోడ్ నడుపుతుండగా విఘాతం కలిగించకుండా.

✅ DMA గురించి మరింత సమాచారం కోసం [వికీపీడియా డైరెక్ట్ మెమరీ యాక్సెస్ పేజీ](https://wikipedia.org/wiki/Direct_memory_access) చూడండి.

![Audio from the mic goes to an ADC then to the DMAC. This writes to one buffer. When this buffer is full, it is processed and the DMAC writes to a second buffer](../../../../../translated_images/te/dmac-adc-buffers.4509aee49145c90b.png)

DMAC ADC నుండి ఆడియోను ఖచితం సమయంలో క్యాప్చర్ చేయగలదు, ఉదాహరణకి 16KHz ఆడియోకు సెకనుకు 16,000 సార్లు. ఇది క్యాప్చర్ చేసిన డేటాను ముందు నుంచే కేటాయించిన మెమరీ బఫర్ కు రాయగలదు, ఆ బఫర్ నింపుకుపోయినప్పుడు, మీ కోడ్ కోసం ప్రాసెస్ చేయడానికి అందుబాటులో ఉంచుతుంది. ఈ మెమరీ ఉపయోగించడం ఆడియో క్యాప్చర్ చేయడంలో కొంచెం ఆలస్యం చేయవచ్చు, కాని మీరు బహు బఫర్లను సెట్ చేయవచ్చు. DMAC మొదటగా బఫర్ 1 కి రాస్తుంది, దాన్ని నింపిన తర్వాత మీ కోడ్ కు నోటిఫై చేస్తుంది, అప్పుడిడిఎమ్ఎసీఎస్ బఫర్ 2 కి రాస్తుంది. బఫర్ 2 నింపిన తర్వాత vostra కోడ్ కు నోటిఫై చేస్తుంది, అది మళ్లీ బఫర్ 1 కి రాయడం మొదలు పెడుతుంది. ఈ విధంగా మీరు ప్రతి బఫర్ కొరకు సమయానికి అందుబాటులో ఉంటే, మీరు ఏ డేటాను కోల్పోరు.

ప్రతి బఫర్ క్యాప్చర్ అయిన తర్వాత, దీన్ని ఫ్లాష్ మెమరీలో రాయవచ్చు. ఫ్లాష్ మెమరీ ఎలాగైనా రాయబడదు, మీరు ఎడ్రస్ మరియు పరిమాణం నిర్దేశించాలి, మెమరీలో బైట్స్ ఆరాయ్ అప్‌డేట్ చేసే తరహాలో. ఫ్లాష్ మెమరీకు గ్రాన్యులారిటీ ఉంది, అంటే ఈజ్ మరియు రైట్ ఆపరేషన్లు కేవలం స్థిర పరిమాణంలో మాత్రమే కాకుండా, ఆ పరిమాణానికి సరిపోయే ఎలైन्मెంట్‌తో కూడా ఉండాలి. ఉదాహరణకి, గ్రాన్యులారిటీ 4096 బైట్స్ అయితే, మీరు 4200 అడ్రస్ ఎరేస్ కోసం కోరితే, అది 4096 నుండి 8192 వరకు కాలుష్య డేటాను తొలగించవచ్చు. అందువల్ల మీరు ఆడియో డేటాను ఫ్లాష్ మెమరీకు రాస్తునప్పుడు, అది సరైన పరిమాణాల్లో ఉండాలి.

### టాస్క్ - ఫ్లాష్ మెమరీని కాన్ఫిగర్ చేయండి

1. PlatformIO ఉపయోగించి కొత్త Wio టెర్మినల్ ప్రాజెక్ట్ తయారు చేయండి. దీనికి `smart-timer` అని పేరు పెట్టండి. `setup` ఫంక్షన్స్ లో సీరియల్ పోర్ట్ కాన్ఫిగర్ చేసే కోడ్ చేర్చండి.

1. `platformio.ini` ఫైల్ లో ఫ్లాష్ మెమరీ యాక్సెస్ కోసం క్రిందిన లైబ్రరీ డిపెండెన్సీలు జోడించండి:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```


1. `main.cpp` ఫైలు ఓపెన్ చేసి, ఫ్లాష్ మెమరీ లైబ్రరీ కోసం కిందిన include డైరెక్టివ్ చేర్చండి:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD అనేది సీరియల్ ఫ్లాష్ యూనివర్సల్ డ్రైవర్, ఇది అన్ని ఫ్లాష్ మెమరీ చిప్‌లతో పని చేసేలా రూపొందించిన లైబ్రరీ.

1. `setup` ఫంక్షన్ లో క్రిందిన కోడ్ చేర్చి ఫ్లాష్ స్టోరేజ్ లైబ్రరీని సెటప్ చేయండి:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    ఇది SFUD లైబ్రరీను ఇనిషియలైజ్ అయినంతవరకు లూప్ అవుతుంది, తరువాత ఫాస్ట్ రీడ్స్ ఆన్ చేస్తుంది. Wio టెర్మినల్ లో బిల్ట్-ఇన్ ఫ్లాష్ మెమరీ QSPI ను ఉపయోగించి యాక్సెస్ చేయబడుతుంది, ఇది సీరియల్ పెరిఫెరల్ ఇంటర్‌ఫేస్‌కి చెందిన ఒక రకం SPI కంట్రోలర్, ఇది క్యూ ద్వారా నిరంతర యాక్సెస్‌ను తక్కువ ప్రాసెసర్ వాడుకతో అనుమతిస్తుంది. ఇది ఫ్లాష్ మెమరీకు చదవడం మరియు రాయడం వేగంగా చేస్తుంది.

1. `src` ఫోల్డర్ లో `flash_writer.h` అనే కొత్త ఫైల్ సృష్టించండి.

1. ఈ ఫైల్ టాప్‌లో క్రింది కోడ్ చేర్చి అవసరమైన హెడర్ ఫైల్స్, SFUD లైబ్రరీ కోసం హెడర్ ఫైల్ చేర్చండి:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    ఇది కొన్ని అవసరమైన హెడర్ ఫైల్స్ చేర్చుతుంది, వాటిలో SFUD లైబ్రరీ కూడా ఉంది, ఇది ఫ్లాష్ మెమరీతో ఇంటరాక్ట్ చేస్తుంది.

1. ఈ కొత్త హెడర్ ఫైల్‌లో `FlashWriter` అనే క్లాస్ ను నిర్వచించండి:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```


1. `private` సెక్షన్‌లో క్రింది కోడ్ చేర్చండి:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    ఇది డేటాను ఫ్లాష్ మెమరీకు రాయడానికి ఉపయోగించే బఫర్ కోసం కొన్ని ఫీల్డ్స్ నిర్వచిస్తుంది. ఒక బైట్ అర్రే `_sfudBuffer` ఉంది, దీనిలో డేటా రాస్తారు మరియు ఇది నింపిందైనప్పుడు డేటా ఫ్లాష్ మెమరీకి రాస్తారు. `_sfudBufferPos` అనే ఫీల్డ్ ప్రస్తుతం ఈ బఫర్ లో ఎక్కడ రాయాలో స్టోర్ చేస్తుంది, `_sfudBufferWritePos` ఫ్లాష్ మెమరీలో ఎక్కడ రాయాలో నిలుపుతుంది. `_flash` అనేది ఫ్లాష్ మెమరీకు పాయింటర్, కొన్ని మైక్రోకంట్రోలర్లు మల్టిపుల్ ఫ్లాష్ చిప్స్ కలిగి ఉంటాయి.

1. `public` సెక్షన్‌లో ఈ క్లాస్ ని ఇనిషియలైజ్ చేయడానికి క్రింది మిథడ్ చేర్చండి:

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

    ఇది Wio టెర్మినల్ లోని ఫ్లాష్ మెమరీని రాయడానికి కాన్ఫిగర్ చేస్తుంది, మరియు ఫ్లాష్ మెమరీ యొక్క గ్రైన్ సైజ్ ఆధారంగా బఫర్లను సెటప్ చేస్తుంది. ఇది కన్‌స్ట్రక్టర్ కాకుండా `init` మిథడ్‌గా ఉంటుంది, ఎందుకంటే ఇది `setup` ఫంక్షన్‌లో ఫ్లాష్ మెమరీ సెటప్ తరువాత పిలవాలి.

1. `public` సెక్షన్ లో క్రింది కోడ్ చేర్చి:

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

    ఈ కోడ్ బైట్స్‌ను ఫ్లాష్ స్‌స్టమ్‌లో రాయడానికి మిథడ్స్ నిర్వచిస్తుంది. ఇది మొదట ఖచ్చిత పరిమాణంలో ఒక ఇన్-మెమరీ బఫర్ లో రాయడం ద్వారా పనిచేస్తుంది, అది నింపబడిన తర్వాత ఫ్లాష్ మెమరీకి రాస్తుంది, ఆ స్థానంలో ఉన్న డేటాను తొలగిస్తుంది. అలాగే, `flushSfudBuffer` ఉంది, ఇది అసంపూర్ణ బఫర్ రాయడానికి ఉపయోగిస్తారు, ఎందుకంటే క్యాప్చర్ అయ్యే డేటా గ్రేన్ సైజ్ యొక్క సరైన గుణకాలు కాకపోవచ్చు, అందువల్ల చివరి భాగాన్ని రాయాలి.

    > 💁 ముగింపు భాగం అదనపు అవసరంలేని డేటాను రాస్తుంది, కాని ఇది సరి, ఎందుకంటే అవసరమైన డేటానే చదువుతారు.

### టాస్క్ - ఆడియో క్యాప్చర్ సెటప్ చేయండి

1. `src` ఫోల్డర్ లో `config.h` అనే కొత్త ఫైల్ సృష్టించండి.

1. ఈ ఫైల్ టాప్‌లో క్రింది కోడ్ చేర్చండి:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    ఈ కోడ్ ఆడియో క్యాప్చర్ కొరకు కొన్ని స్థిరాంకాలను సెట్ చేస్తుంది.

    | స్థిరాంకం              | విలువ  | వివరణ |
    | --------------------- | -----: | - |
    | RATE                  | 16000  | ఆడియో కోసం సాంపుల్ రేట్. 16,000 అంటే 16KHz |
    | SAMPLE_LENGTH_SECONDS | 4      | క్యాప్చర్ చేయాల్సిన ఆడియో పొడవు. ఇది 4 సెకన్లు గా సెట్ చేయబడింది. ఎక్కువ సేపు రికార్డు చేయాలంటే దీన్ని పెంచండి. |
    | SAMPLES               | 64000  | మొత్తం క్యాప్చర్ చేయాల్సిన ఆడియో సాంపుల్స్ సంఖ్య. ఇది సాంపుల్ రేట్ మరియు సెకన్ల సంఖ్య యొక్క గుణకం. |
    | BUFFER_SIZE           | 128044 | ఆడియో బఫర్ పరిమాణం. ఆడియో WAV ఫైల్ గా క్యాప్చర్ అవుతుంది, ఇది 44 బైట్ హెడర్ మరియు 128,000 బైట్ ఆడియో డేటా (ప్రతి సాంపుల్ 2 బైట్) కలిగి ఉంటుంది |
    | ADC_BUF_LEN           | 1600   | DMAC నుండి ఆడియో క్యాప్చర్ చేయడానికి ఉపయోగించే బఫర్లు పరిమాణం |

    > 💁 మీరు 4 సెకన్లు తక్కువ అనిపిస్తే `SAMPLE_LENGTH_SECONDS` విలువ పెంచవచ్చు, మరి ఇతర విలువలు ఆటోమేటిక్‌గా రీకల్క్యులేట్ అవుతాయి.

1. `src` ఫోల్డర్ లో `mic.h` అనే కొత్త ఫైల్ సృష్టించండి.

1. ఈ ఫైల్ టాప్‌లో క్రింది కోడ్ చేర్చండి:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    ఇందులో కొన్ని అవసరమైన హెడర్ ఫైల్స్ ఉన్నాయి, వాటిలో `config.h` మరియు `FlashWriter` హెడర్ ఫైల్స్ కూడా ఉన్నాయి.

1. క్రింది కోడ్ తో మైక్రోఫోన్ నుండి క్యాప్చర్ చేయగల `Mic` క్లాస్ నిర్వచించండి:

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

    ఈ క్లాస్ ప్రస్తుతం రెండు ఫీల్డ్స్ తో ఉంటుంది, రికార్డింగ్ మొదలయిందా, మరియు రికార్డింగ్ ఉపయోగించడానికి సిద్దంగా ఉందా అని ట్రాక్ చేస్తుంది. DMAC సెటప్ అవగానే ఇది నిరంతరం మెమరీ బఫర్లకు రాస్తుంది, అందుకే `_isRecording` ఫ్లాగ్ ఈ బఫర్లను ప్రాసెస్ చేయాలా లేక అవగలిగిపోవాలా అంటే చెప్తుంది. `_isRecordingReady` ఆ డేటా అవసరమైన 4 సెకన్లు క్యాప్చర్ అయినప్పుడు సెట్ అవుతుంది. `_writer` ఫీల్డ్ ఆడియో డేటాను ఫ్లాష్ మెమరీలో సేవ్ చేయడానికి ఉపయోగపడుతుంది.

    గ్లోబల్ వేరియబుల్ ఒక `Mic` క్లాస్ స్పష్టంగా డిక్లేర్ చేయబడింది.

1. `Mic` క్లాస్ యొక్క `private` సెక్షన్‌లో క్రింది కోడ్ చేర్చండి:

    ```cpp
    typedef struct
    {
        uint16_t btctrl;
        uint16_t btcnt;
        uint32_t srcaddr;
        uint32_t dstaddr;
        uint32_t descaddr;
    } dmacdescriptor;

    // గ్లోబల్స్ - DMA మరియు ADC
    volatile dmacdescriptor _wrb[DMAC_CH_NUM] __attribute__((aligned(16)));
    dmacdescriptor _descriptor_section[DMAC_CH_NUM] __attribute__((aligned(16)));
    dmacdescriptor _descriptor __attribute__((aligned(16)));

    void configureDmaAdc()
    {
        // టైమర్/కౌంటర్ ద్వారలా ప్రేరేపింపబడిన ADC నుండి నిరంతర అంతరాలలో నమూనాలు తీసుకోడానికి DMAని కాన్ఫిగర్ చేయండి
        DMAC->BASEADDR.reg = (uint32_t)_descriptor_section;                    // డిస్క్రిప్టర్ల యొక్క స్థానం నిర్దేశించండి
        DMAC->WRBADDR.reg = (uint32_t)_wrb;                                    // రైట్ బ్యాక్ డిస్క్రిప్టర్ల స్థానం నిర్దేశించండి
        DMAC->CTRL.reg = DMAC_CTRL_DMAENABLE | DMAC_CTRL_LVLEN(0xf);           // DMAC పెరిఫెరల్ ను ఎనేబుల్ చేయండి
        DMAC->Channel[1].CHCTRLA.reg = DMAC_CHCTRLA_TRIGSRC(TC5_DMAC_ID_OVF) | // TC5 టైమర్ ఓవర్‌ఫ్లోలో DMACని ట్రిగ్గర్ చేయడానికి సెట్ చేయండి
                                        DMAC_CHCTRLA_TRIGACT_BURST;             // DMAC బర్స్ ట్రాన్స్‌ఫర్

        _descriptor.descaddr = (uint32_t)&_descriptor_section[1];                    // సర్క్యులర్ డిస్క్రిప్టర్ సెటప్ చేయండి
        _descriptor.srcaddr = (uint32_t)&ADC1->RESULT.reg;                           // ADC0 RESULT రిజిస్టర్ నుండి ఫలితాన్ని తీసుకోండి
        _descriptor.dstaddr = (uint32_t)_adc_buf_0 + sizeof(uint16_t) * ADC_BUF_LEN; // adc_buf_0 అర్రే లో ఉంచాలి
        _descriptor.btcnt = ADC_BUF_LEN;                                             // బీట్ కౌంట్
        _descriptor.btctrl = DMAC_BTCTRL_BEATSIZE_HWORD |                            // బీట్ సైజ్ HWORD (16-బిట్లు)
                                DMAC_BTCTRL_DSTINC |                                    // గమ్య చిరునామాను పెంచండి
                                DMAC_BTCTRL_VALID |                                     // డిస్క్రిప్టర్ సరైనది
                                DMAC_BTCTRL_BLOCKACT_SUSPEND;                           // బ్లాక్ ట్రాన్స్‌ఫర్ తర్వాత DMAC ఛానెల్ 0ని సస్పendus చేయండి
        memcpy(&_descriptor_section[0], &_descriptor, sizeof(_descriptor));          // డిస్క్రిప్టర్ ను డిస్క్రిప్టర్ సెక్షన్‌కి కాపీ చేయండి

        _descriptor.descaddr = (uint32_t)&_descriptor_section[0];                    // సర్క్యులర్ డిస్క్రిప్టర్ సెటప్ చేయండి
        _descriptor.srcaddr = (uint32_t)&ADC1->RESULT.reg;                           // ADC0 RESULT రిజిస్టర్ నుండి ఫలితాన్ని తీసుకోండి
        _descriptor.dstaddr = (uint32_t)_adc_buf_1 + sizeof(uint16_t) * ADC_BUF_LEN; // adc_buf_1 అర్రే లో ఉంచాలి
        _descriptor.btcnt = ADC_BUF_LEN;                                             // బీట్ కౌంట్
        _descriptor.btctrl = DMAC_BTCTRL_BEATSIZE_HWORD |                            // బీట్ సైజ్ HWORD (16-బిట్లు)
                                DMAC_BTCTRL_DSTINC |                                    // గమ్య చిరునామాను పెంచండి
                                DMAC_BTCTRL_VALID |                                     // డిస్క్రిప్టర్ సరైనది
                                DMAC_BTCTRL_BLOCKACT_SUSPEND;                           // బ్లాక్ ట్రాన్స్‌ఫర్ తర్వాత DMAC ఛానెల్ 0ని సస్పendus చేయండి
        memcpy(&_descriptor_section[1], &_descriptor, sizeof(_descriptor));          // డిస్క్రిప్టర్ ను డిస్క్రిప్టర్ సెక్షన్‌కి కాపీ చేయండి

        // NVICని కాన్ఫిగర్ చేయండి
        NVIC_SetPriority(DMAC_1_IRQn, 0); // DMAC1 కోసం Nested Vector Interrupt Controller (NVIC) ప్రాధాన్యతను 0 (అత్యధికం) గా సెట్చేయండి
        NVIC_EnableIRQ(DMAC_1_IRQn);      // DMAC1ని Nested Vector Interrupt Controller (NVIC)కి కనెక్ట్ చేయండి

        // DMAC ఛానెల్ 1లో సస్పendus (SUSP) అంతరాయాన్ని యాక్టివేట్ చేయండి
        DMAC->Channel[1].CHINTENSET.reg = DMAC_CHINTENSET_SUSP;

        // ADCని కాన్ఫిగర్ చేయండి
        ADC1->INPUTCTRL.bit.MUXPOS = ADC_INPUTCTRL_MUXPOS_AIN12_Val; // అనలాగ్ ఇన్‌పుట్‌ను ADC0/AIN2 (PB08 - Metro M4లో A4)కి సెట్చేయండి
        while (ADC1->SYNCBUSY.bit.INPUTCTRL)
            ;                              // సమకూర్చుటకు వేచి ఉండండి
        ADC1->SAMPCTRL.bit.SAMPLEN = 0x00; // గరిష్ట నమూనా సమయం సగం విభజించిన ADC క్లాక్ పల్స్ (2.66us)గా సెట్ చేయండి
        while (ADC1->SYNCBUSY.bit.SAMPCTRL)
            ;                                         // సమకూర్చుటకు వేచి ఉండండి
        ADC1->CTRLA.reg = ADC_CTRLA_PRESCALER_DIV128; // ADC GCLK క్లాక్‌ను 128 ద్వారా విభజించండి (48MHz/128 = 375kHz)
        ADC1->CTRLB.reg = ADC_CTRLB_RESSEL_12BIT |    // ADC రిజల్యూషన్‌ను 12 బిట్లుగా సెట్ చేయండి
                            ADC_CTRLB_FREERUN;          // ADCని ఫ్రీ రన్ మోడ్‌లో సెట్ చేయండి
        while (ADC1->SYNCBUSY.bit.CTRLB)
            ;                       // సమకూర్చుటకు వేచి ఉండండి
        ADC1->CTRLA.bit.ENABLE = 1; // ADCని ఎనేబుల్ చేయండి
        while (ADC1->SYNCBUSY.bit.ENABLE)
            ;                       // సమకూర్చుటకు వేచి ఉండండి
        ADC1->SWTRIG.bit.START = 1; // ADC కన్వర్షన్ ప్రారంభించడానికి సాఫ్ట్‌వేర్ ట్రిగ్గర్‌ను ప్రారంభించండి
        while (ADC1->SYNCBUSY.bit.SWTRIG)
            ; // సమకూర్చుటకు వేచి ఉండండి

        // DMA ఛానెల్ 1ని ఎనేబుల్ చేయండి
        DMAC->Channel[1].CHCTRLA.bit.ENABLE = 1;

        // టైమర్/కౌంటర్ 5ని కన్ఫిగర్ చేయండి
        GCLK->PCHCTRL[TC5_GCLK_ID].reg = GCLK_PCHCTRL_CHEN |     // TC5 కోసం పెరిఫెరల్ ఛానెల్‌ను ఎనేబుల్ చేయండి
                                            GCLK_PCHCTRL_GEN_GCLK1; // జనరిక్ క్లాక్ 0ని 48MHz వద్ద కనెక్ట్ చేయండి

        TC5->COUNT16.WAVE.reg = TC_WAVE_WAVEGEN_MFRQ; // TC5ని మ్యాచ్ ఫ్రీక్వెన్సీ (MFRQ) మోడ్‌కు సెట్ చేయండి
        TC5->COUNT16.CC[0].reg = 3000 - 1;            // ట్రిగ్గర్‌ను 16 kHz గా సెట్ చేయండి: (4Mhz / 16000) - 1
        while (TC5->COUNT16.SYNCBUSY.bit.CC0)
            ; // సమకూర్చుటకు వేచి ఉండండి

        // టైమర్/కౌంటర్ 5 ని ప్రారంభించండి
        TC5->COUNT16.CTRLA.bit.ENABLE = 1; // TC5 టైమర్‌ను ఎనేబుల్ చేయండి
        while (TC5->COUNT16.SYNCBUSY.bit.ENABLE)
            ; // సమకూర్చుటకు వేచి ఉండండి
    }

    uint16_t _adc_buf_0[ADC_BUF_LEN];
    uint16_t _adc_buf_1[ADC_BUF_LEN];
    ```

    ఈ కోడ్ `configureDmaAdc` మెథడ్ నిర్వచిస్తుంది, ఇది DMAC ను ADC కి కనెక్ట్ చేసి, రెండు వేరే వేరే పరస్పరం మార్పిడి అయ్యే బఫర్లను పూరించడానికి సెటప్ చేస్తుంది, `_adc_buf_0` మరియు `_adc_buf_1`.

    > 💁 మైక్రోకంట్రోలర్ అభివృద్ధిలో ఒక లోపం ఏమంటే హార్డ్వేర్ తో ఇంటరాక్ట్ చేయడానికి చాలా క్లిష్టమైన కోడ్ అవసరం అవుతుంది, ఎందుకంటే మీ కోడ్ చాలా లోతైన స్థాయిలో నేరుగా హార్డ్వేర్ ని స్పందిస్తుంది. ఈ కోడ్ సింగిల్-బోర్డ్ కంప్యూటర్ లేదా డెస్క్‌టాప్ కంప్యూటర్ కోసం రాసే కోడ్ కంటే క్లిష్టంగా ఉంటుంది, ఎందుకంటే ఆపరేటింగ్ సిస్టం సహాయం అందించదు. కొన్ని లైబ్రరీలు ఈ క్లిష్టతను సులభతరం చేయగలవు, కాని ఇంకా చాలా క్లిష్టత ఉంటుంది.

1. ఈ కింద క్రింది కోడ్ చేర్చండి:

    ```cpp
    // WAV ఫైళ్లకు ఒక హె더ర్ ఉంటుంది. ఈ నిర్మాణం ఆ హె더ర్‌ను నిర్వచిస్తుంది
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
        wavh.num_chans = 1;  // మోనో
        wavh.srate = RATE;
        wavh.bytes_per_sec = (RATE * 1 * 16 * 1) / 8;
        wavh.bytes_per_samp = 2;
        wavh.bits_per_samp = 16;
        wavh.dlength = RATE * 2 * 1 * 16 / 2;
        wavh.flength = wavh.dlength + 44;

        _writer.writeSfudBuffer((byte *)&wavh, 44);
    }
    ```

    ఇది WAV హెడర్‌ను ఒక స్ట్రక్ట్ గా నిర్వచిస్తుంది, ఇది 44 బైట్ మెమరీ తీసుకుంటుంది. ఇది ఆడియో ఫైల్ రేట్, పరిమాణం, ఛానల్స్ సంఖ్య గురించి వివరాలు రాస్తుంది. ఈ హెడర్ ప్రతి సారి ఫ్లాష్ మెమరీకి రాయబడుతుంది.

1. ఈ క్రింది కోడ్ కింద, ఆడియో బఫర్లు ప్రాసెస్ చేయడానికి కాల్ చేయబడే మిథడ్ ప్రకటన:

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

    ఆడియో బఫర్లు 16-బిట్ ఇంతిజర్స్ అర్రేస్, ADC నుండి ఆడియోను కలిగి ఉంటాయి. ADC 12-బిట్ అన్సైన్ వాల్యూ (0-1023) ఇస్తుంది, కాబట్టి వీటిని 16-బిట్ సైన్ వాల్యూస్ గా మార్చాలి, తరువాత 2 బైట్స్ గా మార్చాలి రా బైనరీ డేటాగా నిల్వ చేసేందుకు.

    ఈ బైట్స్ ఫ్లాష్ మెమరీ బఫర్లకు రాయబడతాయి. రాయడం 44 ఇన్‌డెక్స్ నుంచి ప్రారంభమవుతుంది - ఇది WAV ఫైల్ హెడర్ 44 బైట్స్ ఆఫ్సెట్. అవసరమైన ఆడియో పొడవుకు సరిపడా బైట్స్ క్యాప్చర్ అయిన తర్వాత మిగిలిన డేటా ఫ్లాష్ మెమరీకి రాస్తారు.

1. `Mic` క్లాస్ యొక్క `public` సెక్షన్ లో క్రింది కోడ్ చేర్చండి:

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

    ఈ కోడ్ DMAC ద్వారా మీ కోడ్‌కి బఫర్‌లను ప్రాసెస్ చేయడానికి తెలియజేస్తుంది. ఇది ప్రాసెస్ చేయడానికి డేటా ఉన్నదో లేదో తనిఖీ చేస్తుంది, తరువాత సంబంధిత బఫర్ తో `audioCallback` మిథడ్ ను పిలుస్తుంది.

1. క్లాస్ వెలుపల, `Mic mic;` డిక్లరేషన్ తరువాత క్రింది కోడ్ చేర్చండి:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    DMAC 1 హ్యాండ్లర్ DMAC బఫర్లు ప్రాసెస్ చేయడానికి సిద్ధంగా ఉన్నప్పుడు పిలవబడుతుంది. ఈ ఫంక్షన్ పేరు ద్వారా కనుగొనబడుతుంది, కాబట్టి ఉండటం అవసరం.

1. `Mic` క్లాస్ యొక్క `public` సెక్షన్ లో క్రింది రెండు మిథడ్స్ చేర్చండి:

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

    `init` మిథడ్ `Mic` క్లాస్ ని ఇనిషియలైజ్ చేసే కోడ్ ను కలిగి ఉంది. దీనిలో మైక్ పిన్‌కి సరైన వోల్టేజ్ సెట్ చేయడం, ఫ్లాష్ మెమరీ రైటర్ సెటప్ చేయడం, WAV ఫైల్ హెడర్ రాయడం మరియు DMAC సెటప్ చేయడం ఉంటుంది. `reset` మిథడ్ ఆడియో క్యాప్చర్ అయిపోయిన తర్వాత ఫ్లాష్ మెమరీని రీసెట్ చేసి హెడర్ మళ్లీ రాయడానికి ఉపయోగించబడుతుంది.

### టాస్క్ - ఆడియో క్యాప్చర్ చేయండి

1. `main.cpp` లో `mic.h` హెడర్ ఫైల్ కోసం include డైరెక్టివ్ చేర్చండి:

    ```cpp
    #include "mic.h"
    ```


1. `setup` ఫంక్షన్లో C బటన్ ను ఇనిషియలైజ్ చేయండి. ఈ బటన్ నొక్కితే ఆడియో క్యాప్చర్ ప్రారంభమవుతుంది మరియు 4 సెకన్ల పాటు కొనసాగుతుంది:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```


1. దాని క్రింద, మైక్రోఫోన్‌ను ఇనిషియలైజ్ చేయండి, ఆపై కన్సోల్ లో ఆడియో క్యాప్చర్ సిద్ధంగా ఉందని ప్రింట్ చేయండి:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```


1. `loop` ఫంక్షన్కు ముందు క్యాప్చర్ చేసిన ఆడియో ప్రాసెస్ చేయడానికి ఒక ఫంక్షన్ నిర్వచించండి. ఇప్పటివరకు ఇది ఏం చేయదు, పాఠం తర్వాత ఇది వాయిస్‌ను టెక్స్ట్ గా మార్పిడి చేయడానికి ఉపయోగపడుతుంది:

    ```cpp
    void processAudio()
    {
    
    }
    ```


1. `loop` ఫంక్షన్ లో క్రింది కోడ్ చేర్చండి:

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

    ఈ కోడ్ C బటన్‌ను చెక్ చేస్తుంది, బటన్ నొక్కబడితే మరియు రికార్డింగ్ ప్రారంభం కాలేదంటే, `Mic` క్లాస్ లో `_isRecording` ఫీల్డ్ నిజమవుతుంది. ఇది ఆడియో క్యాప్చర్ చేస్తూ, 4 సెకన్ల ఆడియో పూర్తయిన తర్వాత `_isRecording` ఫీల్డ్ అబద్ధంగా, మరియు `_isRecordingReady` ఫీల్డ్ నిజంగా మలుస్తుంది. ఆపై `loop` లో ఇది చెక్ చేసి `processAudio` ఫంక్షన్ ని పిలుస్తుంది, తర్వాత మైక్ క్లాస్ రీసెట్ అవుతుంది.

1. ఈ కోడ్ ను నిర్మించి, మీ Wio టెర్మినల్ కు అప్లోడ్ చేసి సీరియల్ మానిటర్ ద్వారా పరీక్షించండి. C బటన్ (ఎడమవైపున, పవర్ స్విచ్ కి సమీపంలో ఉన్నది) నొక్కండి మరియు మాట్లాడండి. 4 సెకన్ల ఆడియో క్యాప్చర్ అవుతుంది.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Ready.
    Starting recording...
    Finished recording
    ```

> 💁 మీరు ఈ కోడ్ ను [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal) ఫోల్డర్ లో కనుగొనవచ్చు.

😀 మీ ఆడియో రికార్డింగ్ ప్రోగ్రామ్ విజయవంతంగా జరిగింది!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**అస్పష్టత**:  
ఈ పత్రాన్ని AI అనువాద సేవ [Co-op Translator](https://github.com/Azure/co-op-translator) ఉపయోగించి అనువదించబడింది. మేము సరికొత్తత కోసం ప్రయత్నిస్తున్నప్పటికీ, ఆటోమేటెడ్ అనువాదాలలో పొరపాట్లు లేదా అపరిశుద్ధతలు ఉండవచ్చు అని గమనించగలరు. మూల పత్రం దాని స్వదేశી భాషలో అర్థవంతమైన వనరుగా భావించాలి. ముఖ్యమైన సమాచారం కోసం, ప్రొఫెషనల్ మానవ అనువాదం సూచించబడుతుంది. ఈ అనువాదాన్ని ఉపయోగించడం వలన కలిగే ఏవైనా త misunderstandings గానీ దుర్వివరణల గానీ మాకు బాధ్యత ఉండదు.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->