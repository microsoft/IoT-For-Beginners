<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2f336726b9410e97c3aaed76cc89b0d8",
  "translation_date": "2026-01-07T03:27:37+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-audio.md",
  "language_code": "ml"
}
-->
# ഓഡിയോ കപ്ചർ ചെയ്യുക - Wio ടെർമിനൽ

പാഠത്തിന്റെ ഈ ഭാഗത്തിൽ, നിങ്ങളുടെ Wio ടെർമിനലിൽ ഓഡിയോ കപ്ചർ ചെയ്യാൻ കോഡ് എഴുതും. ഓഡിയോ കപ്ചർ Wio ടെർമിനലിന്റെ മുകളിൽ ഉള്ള ബട്ടണുകളിൽ ഒന്ന് കൊണ്ട് നിയന്ത്രിക്കും.

## ഡിവൈസിനെ ഓഡിയോ കപ്ചർ ചെയ്യാൻ പ്രോഗ്രാം ചെയ്യുക

C++ കോഡ് ഉപയോഗിച്ച് മൈക്രോഫോൺ നിന്ന് ഓഡിയോ കപ്ചർ ചെയ്യാം. Wio ടെർമിനലിന് 192KB രാം മാത്രമേ ഉള്ളൂ, അതുകൊണ്ട് രണ്ടുവർഷം കൂടുതൽ ഓഡിയോ കപ്ചർ ചെയ്യാൻ സാധിക്കുന്നില്ല. പക്ഷേ, 4MB ഫ്ലാഷ് മെമ്മറി ഉള്ളതിനാൽ, ക്യാപ്ചർ ചെയ്ത ഓഡിയോ ഫ്ലാഷ് മെമ്മറിയിലേക്ക് സേവ് ചെയ്യാൻ ഇതുപയോഗിക്കാം.

ഇൻബിൽറ്റ് മൈക്രോഫോൺ അനലോഗ് സിഗ്നൽ കപ്ചർ ചെയ്യുന്നു, ഇത് ഡിജിറ്റൽ സിഗ്നലായി മാറ്റുകയും അതു Wio ടെർമിനൽ ഉപയോഗിക്കാനാകുകയും ചെയ്യും. ഓഡിയോ കപ്ചർ ചെയ്യുമ്പോൾ, ഡാറ്റ ശരിയായ സമയത്ത് കപ്ചർ ചെയ്യേണ്ടതാണ് - ഉദാഹരണത്തിന് 16KHz ഓഡിയോ കപ്ചർ ചെയ്യാനെങ്കിൽ, ഓഡിയോ മനസ്സിലുള്ളതെല്ലാം секундിൽ 16,000 തവണയും സമതുല്യ ഇടവേളകളോടെ വേണം കപ്ചർ ചെയ്യുക. നിങ്ങളുടെ കോഡ് ഇതിനു പകരം, ഡയറക്ട് മെമ്മറി ആക്സസ് കൺട്രോളർ (DMAC) ഉപയോഗിക്കാം. ഇത് ഒരു സർക്ക്യൂട്ട് ആണ്, സിഗ്നൽ എവിടെങ്കിലും നിന്നു മെമ്മറിയിൽ എഴുതാൻ കഴിയും, പ്രോസസ്സറിൽ കോഡ് പ്രവർത്തനം തടസ്സപ്പെടുത്താതെ.

✅ [വിക്കിപീഡിയയിൽ ഡയറക്ട് മെമ്മറി ആക്സസ് പേജ്](https://wikipedia.org/wiki/Direct_memory_access) ൽ DMA ന്റെ സന്ദർശനം കൂടുതൽ വായിക്കുക.

![മൈക്കിൽ നിന്ന് ഓഡിയോ ADC യിലേക്കും അതു DMAC യിലേക്കും പോകുന്നു. ഇത് ഒര_BUF_ ഫ്രററിലേക്ക് എഴുതുന്നു. ഈ BUF_ പൂര്ണ്ണമായാൽ, ഇത് പ്രോസസ് ചെയ്ത് DMAC രണ്ടാമത്തെ BUF_ യിൽ എഴുതും](../../../../../translated_images/ml/dmac-adc-buffers.4509aee49145c90b.png)

DMAC 16KHz ഓഡിയോയ്ക്ക് വേണ്ടി 16,000 തവണ സ്ഥിരമായി ADC ൽ നിന്ന് ഓഡിയോ കപ്ചർ ചെയ്യാം. ഇത് ക്യാപ്ചർ ചെയ്ത ഡാറ്റ പ്രീ-അലോക്കേറ്റ് ചെയ്ത മെമ്മറി ബഫറിൽ എഴുതാനും, ഇത് പൂര്ണ്ണമായപ്പോൾ നിങ്ങളുടെ കോഡിന് പ്രോസസ് ചെയ്യാൻ അനുവദിക്കാനും കഴിയും. ഈ മെമ്മറി ഉപയോഗിക്കുന്നത് കപ്ചർ ചെയ്യുന്നതിൽ കുറച്ചു വൈകിപ്പിക്കാമെങ്കിലും, നിങ്ങള്ക്ക് ബഫറുകൾ പലതും സജ്ജമാക്കാം. DMAC ആദ്യം ബഫർ 1 ല് എഴുതും, ഇത് പൂര്ണ്ണമായപ്പോൾ നിങ്ങളുടെ കോഡ് ബഫർ 1 പ്രോസസ് ചെയ്യാൻ അറിയിക്കുകയും DMAC ബഫർ 2 യിൽ എഴുതുകയും ചെയ്യും. ബഫർ 2 പൂര്ണ്ണമായാൽ, നിങ്ങളുടെ കോഡ് അറിയിക്കുകയും വീണ്ടും ബഫർ 1 ലേഖനം ആരംഭിക്കുകയും ചെയ്യും. ഒര BUF_ പൂര്ണ്ണമായതിന് കുറവ് സമയത്ത് നിങ്ങൾ പ്രോസസ് ചെയ്യുന്നതിങ്ങനെ, ഒരു ഡാറ്റയും നഷ്ടമാകില്ല.

ഓരോ ബഫറും കപ്ചർ ചെയ്ത ശേഷം, ഫ്ലാഷ് മെമ്മറിയിൽ എഴുതാം. ഫ്ലാഷ് മെമ്മറി നിർദ്ദേശിച്ച വിലാസങ്ങൾ ഉപയോഗിച്ച് എഴുതണം, എവിടെ എഴുതണമെന്നും എത്ര വലുത് എഴുതണമെന്ന് വ്യക്തമാക്കണം, മെമ്മറിയിലെ ബൈറ്റുകളുടെ അടുക്കൾ പുതുക്കുന്നതുപോലെ. ഫ്ലാഷ് മെമ്മറിക്ക് ഗ്രാനുലാരിറ്റി ഉണ്ട്, അർഥাৎ ഒരു നിർദ്ദിഷ്ട വലുപ്പത്തിൽ മാത്രമല്ല, അത് വലുപ്പത്തിലേക്ക് ലൈൻ ആക്കുന്നതിലും ആശ്രയിക്കുന്നു. ഉദാഹരണത്തിന്, ഗ്രാനുലാരിറ്റി 4096 ബൈറ്റ്സ് ആണെങ്കിൽ, 4200 വിലാസത്തിൽ മുറിച്ചുമാറ്റാൻ ആവശ്യപ്പെടുമ്പോൾ അത് 4096 മുതൽ 8192 വരെ ഡാറ്റ നീക്കം ചെയ്യാം. അതിനാൽ ഓഡിയോ ഡാറ്റ ഫ്ലാഷ് മെമ്മറിയിൽ എഴുതുമ്പോൾ ശരിയായ വലുപ്പത്തിലെ ചങ്കുകളായി വേണം.

### ടാസ്ക് - ഫ്ലാഷ് മെമ്മറി കോൺഫിഗർ ചെയ്യുക

1. PlatformIO ഉപയോഗിച്ച് പുത്തൻ Wio ടെർമിനൽ പ്രൊജക്റ്റ് ഉണ്ടാക്കുക. ഈ പ്രൊജക്റ്റിന് `smart-timer` എന്ന് പേര് നല്‍കുക. `setup` ഫംഗ്‌ഷനിൽ സീരിയൽ പോർട്ട് കോൺഫിഗർ ചെയ്യാനുള്ള കോഡ് ചേർക്കുക.

1. ഫ്ലാഷ് മെമ്മറിയിലേക്ക് ആക്സസ് നൽകാൻ `platformio.ini` ഫയലില് താഴെ പറയുന്ന ലൈബ്രറി ആശ്രിതങ്ങൾ ചേർക്കുക:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. `main.cpp` ഫയൽ തുറന്ന്, ഫ്ലാഷ് മെമ്മറി ലൈബ്രറിയുടെ ഇൻക്ലൂഡ് ഡയറക്ടീവ് ടോപ്പിൽ ചേർക്കുക:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD అంటే Serial Flash Universal Driver, എല്ലാ ഫ്ലാഷ് മെമ്മറി ചിപുകളുമായും പ്രവർത്തിക്കാൻ രൂപകൽപ്പന ചെയ്ത ഒരു ലൈബ്രറിയാണ്

1. `setup` ഫംഗ്‌ഷനിൽ താഴെ പറയുന്ന കോഡ് ചേർത്ത് ഫ്ലാഷ് സ്റ്റോറേജ് ലൈബ്രറി സജ്ജമാക്കുക:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    SFUD ലൈബ്രറി ഇൻഷിയലൈസ് വരെയും ഈ ലൂപ്പ് തുടരുന്നു, പിന്നീട് ഫാസ്റ്റ് റീഡുകൾ സജ്ജമാക്കുന്നു. ഇൻബിൽറ്റ് ഫ്ലാഷ് മെമ്മറിയിലേക്ക് ക്യൂഡ് സീരിയൽ പെർഫിഫറൽ ഇന്റർഫേസ് (QSPI) ഉപയോഗിച്ച് ആക്‌സസ് ചെയ്യാം, SPI കൺട്രോളറിന്റെ ഒരു തരമാണിത്, ഇത് പ്രോസസർ ഉപയോഗച്ച കുറച്ചു കൊണ്ട് തുടർച്ചയായ ആക്സസ് അനുവദിക്കുന്നു. അതിനാൽ ഫ്ലാഷ് മെമ്മറിയിൽ വായിക്കാനും എഴുതാനും ഇത് വേഗത്തിലാണ്.

1. `src` ഫോൾഡറിൽ പുതിയ ഒരു ഫയൽ `flash_writer.h` എന്ന് ഉണ്ടാക്കുക.

1. ഈ ഫയൽ മുകളിൽ താഴെ പറയുന്ന കോഡ് ചേർക്കുക:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    ഫ്ലാഷ് മെമ്മറിയുമായി സംവദിക്കാൻ SFUD ലൈബ്രറിയുടെ ഹെഡർ ഫയലും ഉൾപ്പെടെ ചില ആവശ്യമായ ഹെഡർ ഫയലുകൾ ഇതിൽ ഉണ്ട്

1. ഈ പുതിയ ഹെഡർ ഫയലിൽ `FlashWriter` എന്ന ക്ലാസ് നിർവചിക്കുക:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. `private` സെക്ഷനിൽ താഴെ പറയുന്ന കോഡ് ചേർക്കുക:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    ഇത് ഫ്ലാഷ് മെമ്മറിയിൽ എഴുതുന്നതിന് മുമ്പ് ഡാറ്റ സംഭരിക്കാൻ ബഫറിന് ആവശ്യമായ ഫീൽഡുകൾ നിർവചിക്കുന്നു. ബൈറ്റുകൾ സঞ্চയിക്കാൻ `_sfudBuffer` ബൈറ്റ് അരേ ഉണ്ട്, ഇത് പൂര്ണ്ണമായാൽ ഡാറ്റ ഫ്ലാഷിൽ എഴുതും. `_sfudBufferPos` ഫീൽഡ് ബഫറിലെ ഇപ്പോഴത്തെ എഴുത്ത് സ്ഥാനത്തെ സൂചിപ്പിക്കുന്നു, `_sfudBufferWritePos` ഫ്ലാഷ് മെമ്മറിയിലെ എഴുതേണ്ട വിലാസം സൂചിപ്പിക്കുന്നു. `_flash` ഫ്ലാഷ് മെമ്മറിയിലേക്കുള്ള പോയിന്ററാണ് - ചില മൈക്രോകൺട്രോളറുകൾക്ക് ഒന്നിൽ കൂടുതൽ ഫ്ലാഷ് മെമ്മറി ചിപുകൾ ഉണ്ടാകാം.

1. `public` സെക്ഷനിൽ ഈ ക്ലാസ് ഇൻഷിയലൈസ് ചെയ്യാൻ താഴെ പറയുന്ന മെത്തഡ് ചേർക്കുക:

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

    ഇത് Wio ടെർമിനലിലെ ഫ്ലാഷ് മെമ്മറി എഴുതാനായി കോൺഫിഗർ ചെയ്യുകയും ബഫറുകൾ ഫ്ലാഷ് മെമ്മറിയുടെ ഗ്രെയിൻ സൈസ് പ്രകാരം സജ്ജമാക്കുകയും ചെയ്യുന്നു. ഇത് കൺസ്ട്രക്ടറിന് പകരം `init` മെത്തഡാണ്, കാരണം ഇത് ഫ്ലാഷ് മെമ്മറി `setup` ഫംഗ്‌ഷനിൽ സജ്ജമാക്കിയതിന് ശേഷം വിളിക്കേണ്ടതാണ്.

1. `public` സെക്ഷനിൽ താഴെ പറയുന്ന കോഡ് ചേർക്കുക:

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

    ഈ കോഡ് ഫ്ലാഷ് സ്റ്റോറേജ് സിസ്റ്റത്തിലേക്ക് ബൈറ്റുകൾ എഴുതാനുള്ള മെത്തഡുകൾ നിർവചിക്കുന്നു. ഫ്ലാഷ് മെമ്മറിയുടെ ശരിയായ വലുപ്പത്തിലുള്ള ഇൻ-മെമ്മറി ബഫറിലേക്ക് എഴുതുന്നു, അത് പൂര്ണ്ണമായാൽ ഫ്ലാഷ് മെമ്മറിയിലേക്ക് എഴുതി പതിഞ്ഞ ഡാറ്റ ഇല്ലാതാക്കുന്നു. ഫ്ലാഷ് മെമ്മറിയിലേക്ക് അപൂർണ്ണ ബഫർ എഴുതാൻ `flushSfudBuffer` ഉണ്ട്, കാരണം കപ്ചർ ചെയ്ത ഡാറ്റ ഗ്രെയിൻ സൈസിന്റെ കൂട്ട് ആയിരിക്കില്ല, അതുകൊണ്ട് അവസാനം ഭാഗം നിലവിലുള്ള മുഴുവൻ ഡാറ്റ എഴുതി പിൻവാങ്ങുന്നു.

    > 💁 ഡാറ്റയുടെ അവസാനം അധികമായ അനാവശ്യ ഡാറ്റ എഴുതിയെപ്പൊഴും, ആവശ്യമായ ഡാറ്റ മാത്രമേ വായിക്കപ്പെടുകയുള്ളൂ, അതുകൊണ്ട് പ്രശ്നമില്ല.

### ടാസ്ക് - ഓഡിയോ കപ്ചർ സജ്ജമാക്കുക

1. `src` ഫോൾഡറിൽ പുതിയ ഫയൽ `config.h` എന്ന് ഉണ്ടാക്കുക.

1. ഈ ഫയൽ മുകളിൽ ചുവടെ പറയുന്ന കോഡ് ചേർക്കുക:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    ഇത് ഓഡിയോ കപ്ചറിനായുള്ള ചില കോൺസ്റ്റന്റുകൾ സജ്ജമാക്കുന്നു.

    | കോൺസ്റ്റന്റ്           | മൂല്യം  | വിവരണം |
    | -------------------- | ------: | - |
    | RATE                 | 16000   | ഓഡിയോ സാംപിൾ നിരക്ക്. 16,000 എന്നത് 16KHz ആണ് |
    | SAMPLE_LENGTH_SECONDS| 4       | കപ്ചർ ചെയ്യേണ്ട ഓഡിയോ ദൈർഘ്യം. ഇത് 4 സെക്കൻഡായി സജ്ജമാക്കിയിരിക്കുന്നു. നീട്ടി റെക്കോർഡ് ചെയ്യാൻ ഇത് കൂട്ടാം. |
    | SAMPLES              | 64000   | കപ്ചർ ചെയ്യേണ്ട ഓഡിയോ സാംപിളുകളുടെ ആകെ എണ്ണം. സാംപിൾ നിരക്കും സെക്കൻഡുകളുടെ എണ്ണം വർദ്ധിപ്പിച്ചിട്ടാണ് സജ്ജമാക്കിയത് |
    | BUFFER_SIZE          | 128044  | ഓഡിയോ ബഫറിന്റെ വലുപ്പം. ഓഡിയോ WAV ഫയലായി കപ്ചർ ചെയ്യും, ഇതൊയ് 44 ബൈറ്റ്സ് ഹെഡറും, 128,000 ബൈറ്റ്സ് ഓഡിയോ ഡാറ്റയും (ഒരു സാംപിൾ 2 ബൈറ്റുകൾ) അൾക്കുന്നു |
    | ADC_BUF_LEN          | 1600    | DMAC നിന്ന് ഓഡിയോ കപ്ചർ ചെയ്യാൻ ഉപയോഗിക്കുന്ന ബഫറുകളുടെ വലുപ്പം |

    > 💁 4 സെക്കൻഡ് സമയ പരിധി കുറവാണെങ്കിൽ, `SAMPLE_LENGTH_SECONDS` മൂല്യം കൂട്ടാം, എല്ലാ വളയണവുമുള്ളതാണ്.

1. `src` ഫോൾഡറിൽ പുതിയ ഫയൽ `mic.h` ഉണ്ടാക്കുക.

1. ഈ ഫയൽ മുകളിൽ താഴെ പറയുന്ന കോഡ് ചേർക്കുക:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    ഇത് ചില ആവശ്യമായ ഹെഡർ ഫയലുകൾ ഉൾക്കൊള്ളുന്നു, അതിൽ `config.h` കൂടാതെ `FlashWriter` ഹെഡറും ഉണ്ട്.

1. മൈക്രോഫോണിൽ നിന്ന് കപ്ചർ ചെയ്യാനുളള `Mic` ക്ലാസ് നിർവചിയ്ക്കാൻ താഴെ പറയുന്ന കോഡ് ചേർക്കുക:

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

    ഈ ക്ലാസിന് നിലവിൽ റെക്കോർഡിംഗ് തുടങ്ങിയിട്ടുണ്ടോ എന്ന് കാണാനുള്ള രണ്ട് ഫീൽഡുകൾ മാത്രമേ ഉള്ളൂ, കൂടാതെ റെക്കോർഡിംഗ് ഉപയോഗിക്കാൻ തയ്യാറായിട്ടുണ്ടോ എന്നും സൂചിപ്പിക്കുന്നു. DMAC സജ്ജമാക്കിയാൽ തുടർച്ചയായി മെമ്മറി ബഫറുകളിൽ എഴുതും, അതിനാൽ `_isRecording` ഫ്ലാഗ് പ്രോസസ് ചെയ്യണോ ഇല്ലയോ ആണെങ്കില് നിർണ്ണയിക്കും. 4 സെക്കൻഡ് ഓഡിയോ കപ്ചർ ചെയ്താൽ `_isRecordingReady` ഫ്ലാഗ് true ആയും സജ്ജമാകും. `_writer` ഫീൽഡ് ഓഡിയോ ഡാറ്റ ഫ്ലാഷ് മെമ്മറിയിലേക്ക് സേവ് ചെയ്യാൻ ഉപയോഗിക്കും.

    `Mic` ക്ലാസിന്റെ ഒരു ഗ്ലോബൽ ഇൻസ്റ്റൻസ് പിന്നീട് പ്രഖ്യാപിക്കുന്നു.

1. `Mic` ക്ലാസ് `private` സെക്ഷനിൽ താഴെ പറയുന്ന കോഡ് ചേർക്കുക:

    ```cpp
    typedef struct
    {
        uint16_t btctrl;
        uint16_t btcnt;
        uint32_t srcaddr;
        uint32_t dstaddr;
        uint32_t descaddr;
    } dmacdescriptor;

    // ഗ്ലോബൽസ് - DMA ആന്റ് ADC
    volatile dmacdescriptor _wrb[DMAC_CH_NUM] __attribute__((aligned(16)));
    dmacdescriptor _descriptor_section[DMAC_CH_NUM] __attribute__((aligned(16)));
    dmacdescriptor _descriptor __attribute__((aligned(16)));

    void configureDmaAdc()
    {
        // DMA നെ എഡിസി നിന്നും ഒരു സ്ഥിരമായ ഇടവേളയില്‍ സാമ്പിള്‍ ചെയ്യാന്‍ കോൺഫിഗർ ചെയ്യുക (ടൈമർ/കൗണ്ടർ വഴി ട്രിഗ്ഗർ ചെയ്യുന്നു)
        DMAC->BASEADDR.reg = (uint32_t)_descriptor_section;                    // ഡിസ്ക്രിപ്റ്ററുകളുടെ സ്ഥലം വ്യക്തമാക്കുക
        DMAC->WRBADDR.reg = (uint32_t)_wrb;                                    // റൈറ്റ് ബാക്ക് ഡിസ്ക്രിപ്റ്ററുകളുടെ സ്ഥലം വ്യക്തമാക്കുക
        DMAC->CTRL.reg = DMAC_CTRL_DMAENABLE | DMAC_CTRL_LVLEN(0xf);           // DMAC പെരിഫെറൽ സജീവമാക്കുക
        DMAC->Channel[1].CHCTRLA.reg = DMAC_CHCTRLA_TRIGSRC(TC5_DMAC_ID_OVF) | // TC5 ടൈമർ ഓവർഫ്ലോയിൽ DMAC ട്രിഗ്ഗർ ചെയ്യുക
                                        DMAC_CHCTRLA_TRIGACT_BURST;             // DMAC ബർസ്റ്റ് ട്രാൻസ്ഫർ

        _descriptor.descaddr = (uint32_t)&_descriptor_section[1];                    // ഒരു സർക്കുലർ ഡിസ്ക്രിപ്റ്റർ ക്രമീകരിക്കുക
        _descriptor.srcaddr = (uint32_t)&ADC1->RESULT.reg;                           // ADC0 RESULT രജിസ്റ്ററിൽ നിന്നും ഫലം എടുക്കുക
        _descriptor.dstaddr = (uint32_t)_adc_buf_0 + sizeof(uint16_t) * ADC_BUF_LEN; // അത് adc_buf_0 അറെയിൽ ഇടുക
        _descriptor.btcnt = ADC_BUF_LEN;                                             // ബീറ്റ് എണ്ണிக்கை
        _descriptor.btctrl = DMAC_BTCTRL_BEATSIZE_HWORD |                            // ബീറ്റ് വലുപ്പം HWORD (16-ബിറ്റുകൾ) ആണ്
                                DMAC_BTCTRL_DSTINC |                                    // ഗമ്യസ്ഥാനം വിലാസം വർദ്ധിപ്പിക്കുക
                                DMAC_BTCTRL_VALID |                                     // ഡിസ്ക്രിപ്റ്റർ സാധുവാണ്
                                DMAC_BTCTRL_BLOCKACT_SUSPEND;                           // ബ്ലോക്ക് ട്രാൻസ്ഫർ കഴിഞ്ഞ് DMAC ചാനൽ 0 താൽക്കാലികമായി നിർത്തുക
        memcpy(&_descriptor_section[0], &_descriptor, sizeof(_descriptor));          // ഡിസ്ക്രിപ്റ്റർ ഡിസ്ക്രിപ്റ്റർ ഭാഗത്തിലേക്ക് നകല്‍ ചെയ്യുക

        _descriptor.descaddr = (uint32_t)&_descriptor_section[0];                    // ഒരു സർക്കുലർ ഡിസ്ക്രിപ്റ്റർ ക്രമീകരിക്കുക
        _descriptor.srcaddr = (uint32_t)&ADC1->RESULT.reg;                           // ADC0 RESULT രജിസ്റ്ററിൽ നിന്നും ഫലം എടുക്കുക
        _descriptor.dstaddr = (uint32_t)_adc_buf_1 + sizeof(uint16_t) * ADC_BUF_LEN; // അത് adc_buf_1 അറെയിൽ ഇടുക
        _descriptor.btcnt = ADC_BUF_LEN;                                             // ബീറ്റ് എണ്ണிக்கை
        _descriptor.btctrl = DMAC_BTCTRL_BEATSIZE_HWORD |                            // ബീറ്റ് വലുപ്പം HWORD (16-ബിറ്റുകൾ) ആണ്
                                DMAC_BTCTRL_DSTINC |                                    // ഗമ്യസ്ഥാനം വിലാസം വർദ്ധിപ്പിക്കുക
                                DMAC_BTCTRL_VALID |                                     // ഡിസ്ക്രിപ്റ്റർ സാധുവാണ്
                                DMAC_BTCTRL_BLOCKACT_SUSPEND;                           // ബ്ലോക്ക് ട്രാൻസ്ഫർ കഴിഞ്ഞ് DMAC ചാനൽ 0 താൽക്കാലികമായി നിർത്തുക
        memcpy(&_descriptor_section[1], &_descriptor, sizeof(_descriptor));          // ഡിസ്ക്രിപ്റ്റർ ഡിസ്ക്രിപ്റ്റർ ഭാഗത്തിലേക്ക് നകല്‍ ചെയ്യുക

        // NVIC കോൺഫിഗർ ചെയ്യുക
        NVIC_SetPriority(DMAC_1_IRQn, 0); // DMAC1 ന് Nested Vector Interrupt Controller (NVIC) മുൻഗണന 0 (അത്യധികം) എന്ന് ക്രമീകരിക്കുക
        NVIC_EnableIRQ(DMAC_1_IRQn);      // DMAC1 നെ Nested Vector Interrupt Controller (NVIC) യുമായി ബന്ധിപ്പിക്കുക

        // DMAC ചാനൽ 1 ല്‍ സസ്പെന്റ് (SUSP) ഇന്റർപ്റ്റ് സജീവമാക്കുക
        DMAC->Channel[1].CHINTENSET.reg = DMAC_CHINTENSET_SUSP;

        // ADC കോൺഫിഗർ ചെയ്യുക
        ADC1->INPUTCTRL.bit.MUXPOS = ADC_INPUTCTRL_MUXPOS_AIN12_Val; // അനാലോഗ് ഇൻപുട്ട് ADC0/AIN2 (PB08 - Metro M4 ന് A4) ആയി ക്രമീകരിക്കുക
        while (ADC1->SYNCBUSY.bit.INPUTCTRL)
            ;                              // സിങ്ക്രണൈസേഷനായി കാത്തിരിക്കുക
        ADC1->SAMPCTRL.bit.SAMPLEN = 0x00; // പരമാവധി സാമ്പിളിംഗ് സമയം ADC ക്ലോക്ക് പൾസ് അর্ধഭാഗം (2.66us) ആയി ക്രമീകരിക്കുക
        while (ADC1->SYNCBUSY.bit.SAMPCTRL)
            ;                                         // സിങ്ക്രണൈസേഷനായി കാത്തിരിക്കുക
        ADC1->CTRLA.reg = ADC_CTRLA_PRESCALER_DIV128; // ADC GCLK 128 നും 48MHz/128 = 375kHz ആയി ക്ലോക്ക് വിഭജിക്കുക
        ADC1->CTRLB.reg = ADC_CTRLB_RESSEL_12BIT |    // ADC റെസലൂഷൻ 12-ബിറ്റ് ആയി ക്രമീകരിക്കുക
                            ADC_CTRLB_FREERUN;          // ADC ഫ്രീ റൺ മോഡായി ക്രമീകരിക്കുക
        while (ADC1->SYNCBUSY.bit.CTRLB)
            ;                       // സിങ്ക്രണൈസേഷനായി കാത്തിരിക്കുക
        ADC1->CTRLA.bit.ENABLE = 1; // ADC സജീവമാക്കുക
        while (ADC1->SYNCBUSY.bit.ENABLE)
            ;                       // സിങ്ക്രണൈസേഷനായി കാത്തിരിക്കുക
        ADC1->SWTRIG.bit.START = 1; // ADC കൺവെർഷൻ തുടങ്ങാൻ സോഫ്റ്റ്വേർ ട്രിഗ്ഗർ തുടങ്ങുക
        while (ADC1->SYNCBUSY.bit.SWTRIG)
            ; // സിങ്ക്രണൈസേഷനായി കാത്തിരിക്കുക

        // DMA ചാനൽ 1 സജീവമാക്കുക
        DMAC->Channel[1].CHCTRLA.bit.ENABLE = 1;

        // ടൈമർ/കൗണ്ടർ 5 ക്രമീകരിക്കുക
        GCLK->PCHCTRL[TC5_GCLK_ID].reg = GCLK_PCHCTRL_CHEN |     // TC5 സജീവമുള്ള പെരിഫെറൽ ചാനൽ സജ്ജമാക്കുക
                                            GCLK_PCHCTRL_GEN_GCLK1; // ജനറിക് ക്ലോക്ക് 0 നു 48MHz കണക്റ്റ് ചെയ്യുക

        TC5->COUNT16.WAVE.reg = TC_WAVE_WAVEGEN_MFRQ; // TC5 നെ മാച്ച് ഫ്രീക്വൻസി (MFRQ) മോഡിലേക്ക് ക്രമീകരിക്കുക
        TC5->COUNT16.CC[0].reg = 3000 - 1;            // 16 kHz ട്രിഗ്ഗർ ക്രമീകരിക്കുക: (4Mhz / 16000) - 1
        while (TC5->COUNT16.SYNCBUSY.bit.CC0)
            ; // സിങ്ക്രണൈസേഷനായി കാത്തിരിക്കുക

        // ടൈമർ/കൗണ്ടർ 5 ആരംഭിക്കുക
        TC5->COUNT16.CTRLA.bit.ENABLE = 1; // TC5 ടൈമർ സജീവമാക്കുക
        while (TC5->COUNT16.SYNCBUSY.bit.ENABLE)
            ; // സിങ്ക്രണൈസേഷനായി കാത്തിരിക്കുക
    }

    uint16_t _adc_buf_0[ADC_BUF_LEN];
    uint16_t _adc_buf_1[ADC_BUF_LEN];
    ```

    ഇവിടെ `configureDmaAdc` മെത്തഡെഴുതി DMAC കോൺഫിഗർ ചെയ്യുന്നു, ADC യുമായി ബന്ധിപ്പിച്ച്, രണ്ട് വേറിട്ട ബഫറുകൾ `_adc_buf_0`, `_adc_buf_1` 번갈아 ഉപയോഗിക്കാൻ സജ്ജമാക്കുന്നു.

    > 💁 മൈക്രോcontroller ഡെവലപ്പ്മെന്റിന്റെ ഒരു ലീമ്പാട് കോഡ് ഹാർഡ്വെയർ കേന്ദ്രീകരിച്ച് വളരെ താഴ്ന്ന സ്ത്ധായിയിൽ പ്രവർത്തിക്കുന്നതിനാൽ കോഡ് വളരെ സങ്കീർണമാണ്. സിംഗിൾ-ബോർഡ് കമ്പ്യൂട്ടർ അല്ലെങ്കിൽ വ്യവസായ കമ്പ്യൂട്ടറിനു തുല്യമായ ഓപ്പറേറ്റിംഗ് സിസ്റ്റം ഇല്ല. കൺസിമ്പിളിഫൈ ചെയ്യാൻ ചില ലൈബ്രറികൾ ഉണ്ട്, പക്ഷേ അതും അസുഖകരമാണ്.

1. ഇതിനുശേഷം താഴെ പറയുന്ന കോഡ് ചേർക്കുക:

    ```cpp
    // WAV ഫയലുകൾക്ക് ഒരു ഹെഡർ ഉണ്ട്. ഈ ഘടന ആ ഹെഡർ നിർവ്വചിക്കുന്നു
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
        wavh.num_chans = 1;  // മൊനോ
        wavh.srate = RATE;
        wavh.bytes_per_sec = (RATE * 1 * 16 * 1) / 8;
        wavh.bytes_per_samp = 2;
        wavh.bits_per_samp = 16;
        wavh.dlength = RATE * 2 * 1 * 16 / 2;
        wavh.flength = wavh.dlength + 44;

        _writer.writeSfudBuffer((byte *)&wavh, 44);
    }
    ```

    ഈ കോഡ് 44 ബൈറ്റിന്റെ മെമ്മറിയുള്ള WAV ഹെഡർ സ്ട്രക്ചർ ആയി നിർവചിക്കുന്നു. ഇത് ഓഡിയോ ഫയൽ നിരക്ക്, വലുപ്പം, ചാനലുകളുടെ എണ്ണം മുതലായവയെ കുറിച്ച് വിവരങ്ങൾ എഴുതുന്നു. പിന്നീട് ഈ ഹെഡർ ഫ്ലാഷ് മെമ്മറിയിൽ എഴുതുന്നു.

1. ഇതിന് താഴെ, ഓഡിയോ ബഫറുകൾ പ്രോസസ് ചെയ്യേണ്ട സമയത്ത് വിളിക്കാൻ ഒരു മെത്തഡിന്റെ പ്രഖ്യാപനം ചേർക്കുക:

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

    ഓഡിയോ ബഫറുകൾ 16-ബിറ്റ് ഇന്റിജറുകളുടെ അരേകൾ ആണ് ADC നിന്നുള്ള ഓഡിയോ ഉൾക്കൊള്ളുന്ന. ADC 12-ബിറ്റ് അൺസൈനഡ് മൂല്യങ്ങൾ (0-1023) നൽകുന്നു, അതിനാൽ ഇവ 16-ബിറ്റ് സൈൻഡ് മൂല്യങ്ങളായി മാറ്റി, പിന്നീട് 2 ബൈറ്റുകളായി മാറ്റി റാവ് ബൈനറി ഡാറ്റ ആക്കുന്നു.

    ഈ ബൈറ്റുകൾ ഫ്ലാഷ് മെമ്മറി ബഫറുകളിൽ എഴുതുന്നു. എഴുത്ത് 44 സ്ഥാനത്തോടെ തുടങ്ങുന്നു - ഇത് WAV ഫയൽ ഹെഡർ എഴുതിയ 44 ബൈറ്റസ് ഓഫ്സെറ്റാണ്. ആവശ്യമുള്ള ഓഡിയോ ദൈർഘ്യത്തിന് ആവശ്യമായ ബൈറ്റുകൾ കപ്ചർ ചെയ്താൽ ബാക്കി ഡാറ്റ ഫ്ലാഷിലേക്ക് എഴുതും.

1. `Mic` ക്ലാസ് `public` സെക്ഷനിൽ താഴെ പറയുന്ന കോഡ് ചേർക്കുക:

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

    ഈ കോഡ് DMAC വി ബി എൻ വേണ്ടി ബഫറുകൾ പ്രോസസ് ചെയ്യാൻ പറയും. ഡാറ്റ പ്രോസസ് ചെയ്യാൻ ഡാറ്റ ഉണ്ടോ എന്ന് പരിശോധിച്ചു `audioCallback` മെത്തഡ് ബന്ധപ്പെട്ട ബഫറോടൊപ്പം വിളിക്കും.

1. `Mic mic;` പ്രഖ്യാപനത്തിനുശേഷം ഈ കോഡ് ചേർക്കുക:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    DMAC_1_Handler DMAC ബഫറുകൾ പ്രോസസ് ചെയ്യേണ്ടപ്പോൾ വിളിക്കും. ഈ ഫംഗ്ഷൻ നാമം കൊണ്ടു മാത്രം തിരയപ്പെടും, അതിനാൽ ഇത് നിലവിലുണ്ടായിരിക്കണം.

1. `Mic` ക്ലാസിന്റെ `public` സെക്ഷനിൽ താഴെ പറയുന്ന രണ്ട് മെത്തഡുകൾ ചേർക്കുക:

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

    `init` മെത്തഡിൽ `Mic` ക്ലാസ്സ് ഇൻഷിയലൈസ് ചെയ്യാനുള്ള കോഡ് ഉണ്ട്. ഇത് മൈക്ക് പിനിന്റെ ശരിയായ വോൾട്ടേജ് സജ്ജമാക്കുമ്പോൾ, ഫ്ലാഷ് റൈറ്റർ സജ്ജമാക്കുകയും WAV ഫയൽ ഹെഡർ എഴുതുകയും DMAC കോൺഫിഗർ ചെയ്യുകയും ചെയ്യുന്നു. `reset` മെത്തഡ് ഓഡിയോ കപ്ചർ ചെയ്ത് ഉപയോഗിച്ച ശേഷം ഫ്ലാഷ് മെമ്മറി റീസെറ്റ് ചെയ്ത് ഹെഡർ വീണ്ടും എഴുതുന്നു.

### ടാസ്ക് - ഓഡിയോ കപ്ചർ ചെയ്യുക

1. `main.cpp` ഫയലിൽ `mic.h` ഹെഡർ ഫയൽ ഉൾപ്പെടുത്തുക:

    ```cpp
    #include "mic.h"
    ```

1. `setup` ഫംഗ്‌ഷനിൽ C ബട്ടൺ ഇൻഷിയലൈസ് ചെയ്യുക. ഈ ബട്ടൺ അമർത്തുമ്പോൾ ഓഡിയോ കപ്ചർ 4 സെക്കൻഡसम्म ആരംഭിക്കും:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. ഇതിന് താഴെ മൈക്രോഫോൺ ഇൻഷിയലൈസ് ചെയ്യുക, പിന്നെ കോൺസോളിൽ ഓഡിയോ കപ്ചർ തയ്യാറാണെന്ന് പ്രിന്റ് ചെയ്യുക:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. `loop` ഫംഗ്‌ഷനിന് മുകളിൽ കപ്ചർ ചെയ്ത ഓഡിയോ പ്രോസസ് ചെയ്യാനുള്ള ഒരു ഫംഗ്ഷൻ നിർവചിക്കുക. ഇപ്പോൾ ഇത് ഒന്നും ചെയ്യാറില്ല, പക്ഷേ ഈ പാഠത്തിന്റെ ശേഷം ഇത് സ്പീച്ച് ടെക്സ്റ്റിൽ മാറ്റാൻ ഉപയോഗിക്കും:

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. `loop` ഫംഗ്‌ഷനിൽ താഴെ പറയുന്ന കോഡ് ചേർക്കുക:

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

    ഈ കോഡ് C ബട്ടൺ പരിശോധിച്ച് അമർത്തിയാൽ, റെക്കോർഡിംഗ് തുടങ്ങിയിട്ടില്ലെങ്കിൽ‌ മാത്രം `Mic` ക്ലാസിന്റെ `_isRecording` ഫീൽഡ് true ആയി സജ്ജമാക്കും. ഇതുവഴി `audioCallback` മാത്രം 4 സെക്കൻഡിനുള്ള ഓഡിയോ സംഭരിക്കും. 4 സെക്കൻഡ് ഓഡിയോ കപ്ചർ ചെയ്താൽ `_isRecording` false ആയും `_isRecordingReady` true ആയും സജ്ജമാകും. ഇത് `loop` ഫംഗ്‌ഷനിൽ പരിശോധിച്ച് true ആണെങ്കിൽ `processAudio` ഫംഗ്ക്ഷൻ വിളിക്കും, പിന്നീട് മൈക്ക് ക്ലാസ് റീസെറ്റ് ചെയ്യും.

1. ഈ കോഡ് ബിൽഡ് ചെയ്ത്, നിങ്ങളുടെ Wio ടെർമിനലിലേക്ക് അപ്‌ലോഡ് ചെയ്ത് സീരിയൽ മോണിറ്ററിൽ പരീക്ഷിക്കുക. C ബട്ടൺ (ഇടതുവശത്തുള്ള, പവർ സ്വിച്ച് ഏറ്റവും അടുത്തുള്ളത്) അമർത്തി സംസാരിക്കുക. 4 സെക്കൻഡിന്റെ ഓഡിയോ കപ്ചർ ചെയ്യും.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Ready.
    Starting recording...
    Finished recording
    ```

> 💁 ഈ കോഡ് [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal) ഫോൾഡറിൽ കണ്ടെത്താം.

😀 നിങ്ങളുടെ ഓഡിയോ റെക്കോർഡിംഗ് പ്രോഗ്രാം വിജയിച്ചു!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**അസ്വീകാര്യീകരണം**:  
ഈ രേഖ AI പരിഭാഷാ സേവനമായ [Co-op Translator](https://github.com/Azure/co-op-translator) ഉപയോഗിച്ച് പരിഭാഷ ചെയ്തതാണ്. നാം കാര്യക്ഷമതയ്ക്ക് ശ്രമിക്കുന്നിട്ടുണ്ടെങ്കിലും, ഓട്ടോമേറ്റഡ് പരിഭാഷകളിൽ പിഴവുകളും തർക്കങ്ങളുമുണ്ടാകാമെന്ന് ദയവായി ശ്രദ്ധിക്കൂ. സ്വന്ത ഭാഷയിലെ മൂല രേഖയാണ് അധികാരമുള്ള ഉറവിടം എന്ന് കരുതണമെന്നും, നിർണായക വിവരങ്ങൾക്കായി പ്രൊഫഷണൽ മനുഷ്യ പരിഭാഷ ശുപാർശ ചെയ്യപ്പെടുന്നു. ഈ പരിഭാഷ ഉപയോഗിച്ചതിനാൽ ഉണ്ടായാകാവുന്ന ഏതെങ്കിലും തെറ്റ് മനസ്സിലാക്കലുകളോ ദുര്ഭാഷ്യങ്ങളോ വരുത്തിപ്പോകുന്നതിന് ഞങ്ങൾ ഉത്തരവാദിത്വം വഹിക്കുന്നില്ല.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->