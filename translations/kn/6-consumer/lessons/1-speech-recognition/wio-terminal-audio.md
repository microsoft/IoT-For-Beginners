<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2f336726b9410e97c3aaed76cc89b0d8",
  "translation_date": "2026-01-07T03:29:30+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-audio.md",
  "language_code": "kn"
}
-->
# ಧ್ವನಿ ಹಿಡಿಯಿರಿ - Wio Terminal

ಪಾಠದ ಈ ಭಾಗದಲ್ಲಿ, ನೀವು ನಿಮ್ಮ Wio Terminal ನಲ್ಲಿ ಧ್ವನಿ ಹಿಡಿಯಲು ಕೋಡ್ ಬರೆಯುತ್ತೀರಿ. ಧ್ವನಿ ಹಿಡಿಯುವಿಕೆಯನ್ನು Wio Terminal ಮೇಲ್ಭಾಗದ ಒಂದು ಬಟನ್ ಮೂಲಕ ನಿಯಂತ್ರಿಸಲಾಗುತ್ತದೆ.

## ಸಾಧನವನ್ನು ಧ್ವನಿ ಹಿಡಿಯಲು ಪ್ರೋಗ್ರಾಮ್ ಮಾಡಿ

ನೀವು C++ ಕೋಡ್ ಬಳಸಿ ಮೈಕ್ರೋಫೋನ್‌ನಿಂದ ಧ್ವನಿಯನ್ನು ಹಿಡಿಯಬಹುದು. Wio Terminal ನಲ್ಲಿ ಕೇವಲ 192KB RAM ಇದೆ, ಇದು ಕೆಲವು ಸೆಕೆಂಡುಗಳಿಂತ ಹೆಚ್ಚು ಧ್ವನಿಯನ್ನು ಹಿಡಿಯಲು ಸಾಕಾಗುವುದಿಲ್ಲ. ಇದಕ್ಕೂ 4MB ಫ್ಲಾಷ್ ಮೆಮೊರಿ ಇದೆ, ಆದ್ದರಿಂದ ಬದಲಾಗಿ ಇದನ್ನು ಬಳಸಬಹುದು, ಹಿಡಿದ ಧ್ವನಿಯನ್ನು ಫ್ಲಾಷ್ ಮೆಮೋರಿಗೆ ಉಳಿಸಬಹುದು.

ನಿರ್ಮಿತ ಮೈಕ್ರೋಫೋನ್ ಅನಾಲಾಗ್ ಸಂಕೇತವನ್ನು ಹಿಡಿಯುತ್ತದೆ, ಅದು Wio Terminal ಬಳಸಬಹುದಾದ ಡಿಜಿಟಲ್ ಸಂಕೇತಕ್ಕೆ ಪರಿವರ್ತಿಸಲಾಗುತ್ತದೆ. ಧ್ವನಿ ಹಿಡಿಯುವಾಗ, ಡೇಟಾವನ್ನು ಸರಿಯಾದ ವೇಳೆಯಲ್ಲಿ ಹಿಡಿಯಲಾಗಬೇಕು – ಉದಾಹರಣೆಗೆ 16KHz ನಲ್ಲಿ ಧ್ವನಿಯನ್ನು ಹಿಡಿಯಲು, ಪ್ರತಿ ಸೆಕೆಂಡಿಗೆ ಸರಿಯಾಗಿ 16,000 ಬಾರಿ ಧ್ವನಿಯನ್ನು ಹಿಡಿಯಬೇಕು, ಪ್ರತಿ ಮಾದರಿಗೂ ಸಮಾನ ಅಂತರ ಬೇಕಾಗುತ್ತದೆ. ನಿಮ್ಮ ಕೋಡ್ ಇದನ್ನು ಮಾಡಲು ಬದಲು, ನೀವು ಡೈರೆಕ್ಟ್ ಮೆಮೊರಿ ಆಕ್ಸೆಸ್ ನಿಯಂತ್ರಕ (DMAC) ಅನ್ನು ಬಳಸಿಬಹುದು. ಇದು ಪ್ರೊಸೆಸರ್ ಮೇಲೆ ನಿಮ್ಮ ಕೋಡ್ ಅನ್ನು ವ್ಯತ್ಯಯ ಮಾಡದೆ, ಎಲ್ಲಿಗಾದರೂ ಸಂಕೇತವನ್ನು ಹಿಡಿದು ಮೆಮೊರಿಯಲ್ಲಿ ಬರೆಯುವ ಸರ್ಕ್ಯೂಟ್ರೀ ಆಗಿದೆ.

✅ ಡೈರೆಕ್ಟ್ ಮೆಮೊರಿ ಆಕ್ಸೆಸ್ ಕುರಿತು ಹೆಚ್ಚಿನ ಮಾಹಿತಿಗಾಗಿ [ವಿಕಿಪೀಡಿಯದ ಡೈರೆಕ್ಟ್ ಮೆಮೊರಿ ಆಕ್ಸೆಸ್ ಪುಟ](https://wikipedia.org/wiki/Direct_memory_access) ನೋಡಿ.

![ಮೈಕ್‌ನಿಂದ ಧ್ವನಿ ADC ಗೆ ಹೋಗುತ್ತದೆ ನಂತರ DMAC ಗೆ. ಇದು ಒಂದು ಬಫರ್‌ಗೆ ಬರೆಯುತ್ತದೆ. ಈ ಬಫರ್ ತುಂಬಿದಾಗ, ಪ್ರಕ್ರಿಯೆಗೊಳ್ಳುತ್ತದೆ ಮತ್ತು DMAC ದ್ವಿತೀಯ ಬಫರ್‌ಗೆ ಬರೆಯುತ್ತದೆ](../../../../../translated_images/kn/dmac-adc-buffers.4509aee49145c90b.png)

DMAC 16KHz ಧ್ವನಿಗಾಗಿ ಪ್ರತಿ ಸೆಕೆಂಡಿಗೆ 16,000 ಬಾರಿ ADC ನಿಂದ ಧ್ವನಿಯನ್ನು ಹಿಡಿಯಬಹುದು. ಇದು ಹಿಂದಿನಂತೆ ನಿರ್ದಿಷ್ಟ ಮೆಮೊರಿ ಬಫರ್‌ಗೆ ಹಿಡಿದ ಡೇಟಾವನ್ನು ಬರೆದಿಡಬಹುದು, ಮತ್ತು ಬಫರ್ ತುಂಬಿದಾಗ, ನಿಮ್ಮ ಕೋಡ್ ಪ್ರಕ್ರಿಯೆ ಮಾಡಲು ಲಭ್ಯವಾಗುತ್ತದೆ. ಈ ಮೆಮೊರಿಯನ್ನು ಬಳಕೆ ಮಾತಿನ ಹಿಡಿಯುವಿಕೆಯಲ್ಲಿ ಕೆಲವು ತಡತಿಗೆ ಕಾರಣವಾಗಬಹುದು, ಆದರೆ ನೀವು ಹಲವಾರು ಬಫರ್ಗಳನ್ನು ಹೊಂದಿಸಬಹುದು. DMAC ಮೊದಲು ಬಫರ್ 1ಕ್ಕೆ ಬರೆಯುತ್ತದೆ, ಅದು ತುಂಬಿದಾಗ ನಿಮ್ಮ ಕೋಡ್ ಅನ್ನು ಸೂಚಿಸುತ್ತದೆ, ಮತ್ತು DMAC ಬಫರ್ 2 ಗೆ ಬರೆಯಲು ಮುಂದಾಗುತ್ತದೆ. ಬಫರ್ 2 ಕೂಡ ತುಂಬಿದಾಗ, ನಿಮ್ಮ ಕೋಡ್ ಗೆ ಸೂಚನೆ ನೀಡುತ್ತದೆ ಮತ್ತು DMAC ಮತ್ತೆ ಬಫರ್ 1 ಗೆ ಬರೆಯಲು ಹಿಂತಿರುಗುತ್ತದೆ. ಹೀಗೆ ಪ್ರತಿಯೊಂದು ಬಫರ್ ಪ್ರಕ್ರಿಯೆ ಮಾಡಲು ತೆಗೆದುಕೊಳ್ಳುವ ಸಮಯದಲ್ಲಿ ಬಫರ್ ತುಂಬಲು ತಕ್ಕಷ್ಟು ಕಡಿಮೆ ಇರೋ ಸಮಯ ಇರುವಂತೆ ನೀವು ಪ್ರಕ್ರಿಯೆ ಮಾಡುತ್ತಿದ್ದರೆ, ಯಾವುದೇ ಡೇಟಾ ತಪ್ಪಿಸಿಕೊಳ್ಳುವುದಿಲ್ಲ.

ಪ್ರತಿ ಬಫರ್ ಹಿಡಿದ ನಂತರ, ಅದು ಫ್ಲಾಷ್ ಮೆಮೊರಿಯಲ್ಲಿ ಬರೆಯಬಹುದು. ಫ್ಲಾಷ್ ಮೆಮೊರಿಯನ್ನು ಬರೆಯಲು ನಿರ್ದಿಷ್ಟ ವಿಳಾಸಗಳನ್ನು ಬಳಸಬೇಕಾಗುತ್ತದೆ, ಯಾವ ಸ್ಥಳದಲ್ಲಿ ಬರೆವುದು ಮತ್ತು ಎಷ್ಟು ದೊಡ್ಡದಾಗಿ ಬರೆಯುವುದು ಎಂಬುದನ್ನು ಸೂಚಿಸಿ, ಮೆಮೊರಿಯಲ್ಲಿನ ಬೈಟ್ ಅರೇ ಸರಣಿಯನ್ನು ಅಪ್ಡೇಟ್ ಮಾಡುವಂತಿದೆ. ಫ್ಲಾಷ್ ಮೆಮೊರಿಯ ಗ್ರಾನ್ಯುಲಾರಿಟಿಂಟೆ, ಅಂದರೆ ಅಳಿಸುವಿಕೆ ಮತ್ತು ಬರವಣಿಗೆ ಕಾರ್ಯಾಚರಣೆಗಳು ಸ್ಥಿರ ಗಾತ್ರ ಕರೆಯುವುದಎದುರಾಗಿ, ಆ ಗಾತ್ರಕ್ಕೆ ಹೊಂದಿಕೆಯಾಗಿರಬೇಕು. ಉದಾಹರಣೆಗೆ, ಗ್ರಾನ್ಯುಲಾರಿಟಿ 4096 ಬೈಟ್ಸ್ ಆಗಿದ್ದರೆ, ಮತ್ತು ನೀವು 4200 ವಿಳಾಸದಲ್ಲಿ ಅಳಿಸಲು ಕೇಳಿದರೆ, ಅದು 4096 ರಿಂದ 8192ವರೆಗೆ ಡೇಟಾ ಅಳಿಸಬಹುದು. ಇದರರ್ಥ ಧ್ವನಿ ಡೇಟಾವನ್ನು ಫ್ಲಾಷ್ ಮೆಮೊರಿಯಲ್ಲಿ ಬರೆಯುವಾಗ, ಅದು ಸರಿಯಾದ ಗಾತ್ರದ ತುಂಡುಗಳಲ್ಲಿರಬೇಕು.

### ಕಾರ್ಯ - ಫ್ಲಾಷ್ ಮೆಮೊರಿ ಸಂರಚಿಸಿ

1. PlatformIO ಬಳಸಿ ಹತ್ತಿರದ ನೂತನ Wio Terminal ಪ್ರಾಜೆಕ್ಟ್ ರಚಿಸಿ. ಈ ಪ್ರಾಜೆಕ್ಟ್‌ಗೆ `smart-timer` ಎಂದು ಹೆಸರಿಸಿರಿ. `setup` ಫಂಕ್ಷನ್‌ನಲ್ಲಿ ಸೀರಿಯಲ್ ಪೋರ್ಟ್ ಸಂರಚಿಸಲು ಕೋಡ್ ಸೇರಿಸಿ.

1. ಫ್ಲಾಷ್ ಮೆಮೊರಿಗೆ ಪ್ರವೇಶ ನೀಡಲು `platformio.ini` ಫೈಲ್‌ಗೆ ಕೆಳಗಿನ ಲೈಬ್ರರಿ ಅವಲಂಬನೆಗಳನ್ನು ಸೇರಿಸಿ:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. `main.cpp` ಫೈಲ್ ತೆರೆಯಿರಿ ಮತ್ತು ಫೈಲ್ ಮೇಲ್ಭಾಗದಲ್ಲಿ ಫ್ಲಾಷ್ ಮೆಮೊರಿ ಲೈಬ್ರರಿಗೆ ಕೆಳಗಿನ ಸೂಚನೆಯನ್ನು ಸೇರಿಸಿ:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD ಅಂದರೆ ಸೀರಿಯಲ್ ಫ್ಲಾಷ್ ಯುನಿವರ್ಸಲ್ ಡ್ರೈರಿವರ್, ಮತ್ತು ಇದು ಎಲ್ಲಾ ಫ್ಲಾಷ್ ಮೆಮೊರಿ чಿಪ್ಗಳೊಂದಿಗೆ ಕೆಲಸ ಮಾಡಲು ವಿನ್ಯಾಸಗೊಳಿಸಿದ ಲೈಬ್ರರಿ

1. `setup` ಫಂಕ್ಷನ್‌ನಲ್ಲಿ ಫ್ಲಾಷ್ ಸಂರಕ್ಷಣ ಲೈಬ್ರರಿಯನ್ನು ಸ್ಥಾಪಿಸಲು ಕೆಳಗಿನ ಕೋಡ್ ಸೇರಿಸಿ:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    ಇದು SFUD ಲೈಬ್ರರಿ ಪ್ರಾರಂಭವಾಗುವವರೆಗೆ ಲೂಪ್ ಮಾಡುತ್ತದೆ, ನಂತರ ವೇಗವಾಗಿ ಓದುಗಾಗಿ ಆನ್ಮಾಡುತ್ತದೆ. ನಿರ್ಮಿತ ఫ್ಲాష್ ಮೆಮೊರಿಯನ್ನು Queued Serial Peripheral Interface (QSPI) ಬಳಸಿ ಪ್ರವೇಶಿಸಲಾಗಬಹುದು, ಇದು ಪ್ರಕ್ರಿಯಾಪಾರ್ಟರ್ ಬಳಕೆಯನ್ನು ಕನಿಷ್ಟಗೊಳಿಸುವ ತಳಹದಿಯೊಂದಿಗೆ ಕ್ಯೂ ಮೂಲಕ ನೈತಿಕವಾಗಿ ನಿರಂತರ ಪ್ರವೇಶವನ್ನು ಅನುಮತಿಸುತ್ತದೆ. ಇದರಿಂದ ಫ್ಲಾಷ್ ಮೆಮೊರಿ ಓದಲು ಮತ್ತು ಬರೆಯಲು ವೇಗವಾಗುತ್ತದೆ.

1. `src` ಫೋಲ್ಡರಿನಲ್ಲಿ `flash_writer.h` ಎಂಬ ಹೆಸರಿನ ಹೊಸ ಫೈಲ್ ರಚಿಸಿ.

1. ಈ ಫೈಲ್ ಮೇಲ್ಭಾಗದಲ್ಲಿ ಕೆಳಗಿನ ಕೋಡ್ ಸೇರಿಸಿ:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    ಇದರಲ್ಲಿ ಕೆಲವು ಅಗತ್ಯ ಹಿಡಿವ ಫೈಲ್‌ಗಳು ಸೇರಿದ್ದು, SFUD ಲೈಬ್ರರಿಯ ಹೆಡರ್ ಫೈಲ್ ಕೂಡ ಫ್ಲಾಷ್ ಮೆಮೊರಿಯೊಂದಿಗೆ ಸಂವಹನ ಮಾಡಲು ಸೇರಿಸಲಾಗಿದೆ

1. ಈ ಹೊಸ ಹೆಡರ್ ಫೈಲ್‌ನಲ್ಲಿ `FlashWriter` ಎಂಬ ಕ್ಲಾಸ್ ಅನ್ನು ವ್ಯಾಖ್ಯಾನಿಸಿ:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. `private` ವಿಭಾಗದಲ್ಲಿ ಕೆಳಗಿನ ಕೋಡ್ ಸೇರಿಸಿ:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    ಇದು ಡೇಟಾವನ್ನು ಫ್ಲಾಷ್ ಮೆಮೊರಿಗೆ ಬರೆಯುವ ಮುನ್ನ ಸಂಗ್ರಹಿಸಲು ಬಫರ್ ಬಳಸಲು ಕೆಲವು ಕ್ಷೇತ್ರಗಳನ್ನು ವ್ಯಾಖ್ಯಾನಿಸುತ್ತದೆ. `_sfudBuffer` ಎಂಬ ಬೈಟ್ ಅರೇ ಇದೆ, ಇದಕ್ಕೆ ಡೇಟಾ ಬರೆಯಲಾಗುತ್ತದೆ, ಮತ್ತು ಅದು ತುಂಬಿದಾಗ, ಡೇಟಾವನ್ನು ಫ್ಲಾಷ್ ಮೆಮೊರಿಗೆ ಬರೆಯಲಾಗುತ್ತದೆ. `_sfudBufferPos` ಕ್ಷೇತ್ರವು ಈ ಬಫರ್‌ನಲ್ಲಿ ಈಗಾಗಲೇ ಬರೆಯಬೇಕಾಗಿರುವ ಸ್ಥಳವನ್ನು ಸಂಗ್ರಹಿಸುತ್ತದೆ, ಮತ್ತು `_sfudBufferWritePos` ಫ್ಲಾಷ್ ಮೆಮೊರಿಯಲ್ಲಿ ಬರೆಯಲಿರುವ ಸ್ಥಳವನ್ನು ಸಂಗ್ರಹಿಸುತ್ತದೆ. `_flash` ಎಂಬುದು ಬರೆಯಬೇಕಾಗಿರುವ ಫ್ಲಾಷ್ ಮೆಮೊರಿಯ ಸೂಚಿಕೆಯನ್ನು ಹೊಂದಿದೆ - ಕೆಲವು ಮೈಕ್ರೋಕುಂಟ್ರೋಲರ್‌ಗಳಿಗೊಂದು ಅಥವಾ ಅನೇಕ ಫ್ಲಾಷ್ ಮೆಮೊರಿ ಚಿಪ್‌ಗಳಿರಬಹುದು.

1. `public` ವಿಭಾಗಕ್ಕೆ ಈ ಕ್ಲಾಸ್ ಆರಂಭಿಸಲು ಕೆಳಗಿನ ವಿಧಾನ ಸೇರಿಸಿ:

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

    ಇದು Wio Terminal ನಲ್ಲಿ ಬರೆಯಲು ಫ್ಲಾಷ್ ಮೆಮೊರಿಯನ್ನು ಸಂರಚಿಸುತ್ತದೆ, ಮತ್ತು ಫ್ಲಾಷ್ ಮೆಮೊರಿಯ ದಾಣಾ ಗಾತ್ರದ ಮೇಲೆ ಆಧಾರಿತವಾಗಿ ಬಫರ್ಗಳನ್ನು ಹೊಂದಿಸುತ್ತದೆ. ಇದು `init` ವಿಧಾನದಲ್ಲಿ ಇದೆ, ನಿರ್ಮಾಪಕ ಅಲ್ಲ, ಏಕೆಂದರೆ ಇದು `setup` ಫಂಕ್ಷನ್‌ನಲ್ಲಿ ಫ್ಲಾಷ್ ಮೆಮೊರಿ ಸ್ಥಾಪನೆಯಾದ ನಂತರ ಕರೆ ಮಾಡಬೇಕಾಗುತ್ತದೆ.

1. `public` ವಿಭಾಗಕ್ಕೆ ಕೆಳಗಿನ ಕೋಡ್ ಸೇರಿಸಿ:

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

    ಈ ಕೋಡ್ ಫ್ಲಾಷ್ ಸಂರಕ್ಷಣ ವ್ಯವಸ್ಥೆಗೆ ಬೈಟ್‌ಗಳನ್ನು ಬರೆಯಲು ವಿಧಾನವನ್ನು ವ್ಯಾಖ್ಯಾನಿಸುತ್ತದೆ. ಇದು ಮೊದಲಿಗೆ ಸರಿ ಗಾತ್ರದ ಸ್ವಯಂ-ಮೆಮೊರಿ ಬಫರ್‌ಗೆ ಬರೆಯುತ್ತದೆ, ಮತ್ತು ಅದು ತುಂಬಿದಾಗ, ಈ ಬಫರ್ ಫ್ಲಾಷ್ ಮೆಮೊರಿಗೆ ಬರೆಯಲಾಗುತ್ತದೆ, ಅದು ಆ ವಿಳಾಸದಲ್ಲಿ ಇರುವ ಡೇಟಾವನ್ನು ಅಳಿಸುತ್ತದೆ. `flushSfudBuffer` ಕೂಡ ಇದೆ, ಅಲ್ಪ ಪೂರ್ಣ ಬಫರ್ ಅನ್ನು ಬರೆಯಲು, ಏಕೆಂದ್ರೆ ಪಡೆದುಕೊಳ್ಳುತ್ತಿರುವ ಡೇಟಾ ದಾಣಾ ಗಾತ್ರದ ಬಹು ಗುಣಾಕಾರಗಳಲ್ಲಿರುವುದಿಲ್ಲ, ಆದ್ದರಿಂದ ಕೊನೆಯ ಭಾಗವನ್ನು ಬರೆಯಬೇಕಾಗುತ್ತದೆ.

    > 💁 ಡೇಟಾ ಕೊನೆಯ ಭಾಗದಲ್ಲಿ ಹೆಚ್ಚುವರಿ ಅನಗತ್ಯ ಡೇಟಾ ಬರೆಯಬಹುದು, ಆದರೆ ಬೇಕಾದ ಡೇಟಾ ಮಾತ್ರ ಓದಲಾಗುವುದರಿಂದ ಇದು ಬಂದುಕೊಳ್ಳಬಹುದಾಗಿದೆ.

### ಕಾರ್ಯ - ಧ್ವನಿ ಹಿಡಿಯುವಿಕೆಯನ್ನು ಹೊಂದಿಸಿ

1. `src` ಫೋಲ್ಡரில் `config.h` ಎಂಬ ಹೆಸರಿನ ಹೊಸ ಫೈಲ್ ರಚಿಸಿ.

1. ಈ ಫೈಲ್ ಮೇಲ್ಭಾಗದಲ್ಲಿ ಕೆಳಗಿನ ಕೋಡ್ ಸೇರಿಸಿ:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    ಈ ಕೋಡ್ ಧ್ವನಿ ಹಿಡಿಯಲು ಕೆಲ ಸ್ಥಿರಾಂಕಗಳನ್ನು ಹೊಂದಿಸುತ್ತದೆ.

    | ಸ್ಥಿರಾಂಕ               | ಮೌಲ್ಯ  | ವಿವರಣೆ |
    | --------------------- | -----: | - |
    | RATE                  | 16000  | ಧ್ವನಿಗಾಗಿ ಮಾದರಿ ದರ. 16,000 ಅಂದರೆ 16KHz |
    | SAMPLE_LENGTH_SECONDS | 4      | ಹಿಡಿಯುವ ಧ್ವನಿಯ ಅವಧಿ. ಇದನ್ನು 4 ಸೆಕೆಂಡುಗಳಾಗಿಸಿದೆ. ಹೆಚ್ಚು ಧ್ವನಿ ದಾಖಲಿಸಲು ಇದನ್ನು ಹೆಚ್ಚಿಸಿ. |
    | SAMPLES               | 64000  | ಹಿಡಿಯಲಾದ ಒಟ್ಟು ಧ್ವನಿ ಮಾದರಿಗಳ ಸಂಖ್ಯೆ. ಮಾದರಿ ದರ × ಸೆಕೆಂಡುಗಳ ಸಂಖ್ಯೆ ಆಗಿದೆ |
    | BUFFER_SIZE           | 128044 | ಹಿಡಿಯುವ ಧ್ವನಿ ಬಫರ್ ಗಾತ್ರ. ಧ್ವನಿಯನ್ನು WAV ಫೈಲ್ ಆಗಿ ಹಿಡಿಜದೆ, ಇದು 44 ಬೈಟ್ ಹೆಡರ್ ಮತ್ತು ನಂತರ 128,000 ಬೈಟ್ ಧ್ವನಿ ಡೇಟಾ (ಪ್ರತಿ ಮಾದರಿ 2 ಬೈಟ್) |
    | ADC_BUF_LEN           | 1600   | DMAC ನಿಂದ ಧ್ವನಿಯನ್ನು ಹಿಡಿಯಲು ಬಳಸುವ ಬಫರ್ ಗಾತ್ರ |

    > 💁 ನಿಮಗೆ 4 ಸೆಕೆಂಡುಗಳು ಟೈಮರ್ ಕೇಳಲು ಕಡಿಮೆ ಅನಿಸುವದಾದರೆ, `SAMPLE_LENGTH_SECONDS` ಮೌಲ್ಯವನ್ನು ಹೆಚ್ಚಿಸಿ, ಮತ್ತು ಇತರ ಮೌಲ್ಯಗಳು ಪುನಃ ಲೆಕ್ಕಿಸಲಾಗುತ್ತವೆ.

1. `src` ಫೋಲ್ಡರ್‌ನಲ್ಲಿ `mic.h` ಎಂಬ ಹೊಸ ಫೈಲ್ ರಚಿಸಿ.

1. ಈ ಫೈಲ್ ಮೇಲ್ಭಾಗದಲ್ಲಿ ಕೆಳಗಿನ ಕೋಡ್ ಸೇರಿಸಿ:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    ಇದು ಕೆಲವು ಅಗತ್ಯ ಹೆಡರ್ ಫೈಲ್ ಗಳನ್ನು ಸೇರಿಸಿದೆ, ಸಹಿತ `config.h` ಮತ್ತು `FlashWriter` ಹೆಡರ್ ಫೈಲ್ ಗಳನ್ನು.

1. ಮೈಕ್ರೋಫೋನ್‌ನಿಂದ ಹಿಡಿಯಲು `Mic` ಎಂಬ ಕ್ಲಾಸ್ ಅನ್ನು ವ್ಯಾಖ್ಯಾನಿಸಲು ಕೆಳಗಿನ ಕೋಡ್ ಸೇರಿಸಿ:

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

    ಈ ಕ್ಲಾಸ್ ಪ್ರಸ್ತುತ ರೆಕಾರ್ಡಿಂಗ್ ಪ್ರಾರಂಭಗೊಂಡಿದೆಯೇ ಮತ್ತು ರೆಕಾರ್ಡಿಂಗ್ ಬಳಕೆಗಾಗಿ ಸಿದ್ಧವಿದೆಯೇ ಎಂಬ ಆ ಎರಡು ಕ್ಷೇತ್ರಗಳನ್ನು ಮಾತ್ರ ಹೊಂದಿದೆ. DMAC ಸಿದ್ಧಪಡಿಸಿದಾಗ, ಇದು ನಿರಂತರವಾಗಿ ಮೆಮೊರಿ ಬಫರ್ಗಳಿಗೆ ಬರೆಯುತ್ತದೆ, ಆದ್ದರಿಂದ `_isRecording` ಫ್ಲ್ಯಾಗ್ ಈ ಬಫರ್ಗಳನ್ನು ಪ್ರಕ್ರಿಯೆ ಮಾಡಬೇಕೆ ಅಥವಾ ನಿರ್ಲಕ್ಷಿಸಬೇಕೆ ಎಂಬುದನ್ನು ವಿವರಿಸುತ್ತದೆ. `_isRecordingReady` ಫ್ಲ್ಯಾಗ್ ಅಗತ್ಯ 4 ಸೆಕೆಂಡಿನ ಧ್ವನಿ ಹಿಡಿದ ನಂತರ ಸೆಟ್ ಮಾಡಲಾಗುತ್ತದೆ. `_writer` ಕ್ಷೇತ್ರವು ಧ್ವನಿ ಡೇಟಾವನ್ನು ಫ್ಲಾಷ್ ಮೆಮೊರಿಯಲ್ಲಿ ಉಳಿಸಲು ಬಳಕೆಯಾಗುತ್ತದೆ.

    ನಂತರ `Mic` ಕ್ಲಾಸ್‌ನ ಉದಾಹರಣೆಗೆ ಜಾಗತಿಕ ಚರವನ್ನು ಘೋಷಿಸಲಾಗಿದೆ.

1. `Mic` ಕ್ಲಾಸ್‌ನ `private` ವಿಭಾಗಕ್ಕೆ ಕೆಳಗಿನ ಕೋಡ್ ಸೇರಿಸಿ:

    ```cpp
    typedef struct
    {
        uint16_t btctrl;
        uint16_t btcnt;
        uint32_t srcaddr;
        uint32_t dstaddr;
        uint32_t descaddr;
    } dmacdescriptor;

    // ಜಾಗತಿಕಗಳು - DMA ಮತ್ತು ADC
    volatile dmacdescriptor _wrb[DMAC_CH_NUM] __attribute__((aligned(16)));
    dmacdescriptor _descriptor_section[DMAC_CH_NUM] __attribute__((aligned(16)));
    dmacdescriptor _descriptor __attribute__((aligned(16)));

    void configureDmaAdc()
    {
        // DMA ಅನ್ನು ನಿಯಮಿತ ಅವಧಿಯಲ್ಲಿ ADC ಯಿಂದ ಮಾದರಿ ಸ೦ಗ್ರಹಿಸಲು ಸಂರಚಿಸಿ (ಟೈಮರ್/ಕೌಂಟರ್ ಮೂಲಕ ಪ್ರೇರಿತ)
        DMAC->BASEADDR.reg = (uint32_t)_descriptor_section;                    // ವಿವರಣೆಕಾರರ ಸ್ಥಳವನ್ನು ನಿರ್ದಿಷ್ಟಪಡಿಸಿ
        DMAC->WRBADDR.reg = (uint32_t)_wrb;                                    // ಬರಹ ಹಿನ್ನಡೆ ವಿವರಣೆಕಾರರ ಸ್ಥಳವನ್ನು ನಿರ್ದಿಷ್ಟಪಡಿಸಿ
        DMAC->CTRL.reg = DMAC_CTRL_DMAENABLE | DMAC_CTRL_LVLEN(0xf);           // DMAC ಮುಖ್ಯಕ vliegtuig ಸಕ್ರಿಯಗೊಳಿಸಿ
        DMAC->Channel[1].CHCTRLA.reg = DMAC_CHCTRLA_TRIGSRC(TC5_DMAC_ID_OVF) | // TC5 ಟೈಮರ್ ಓವರ್‌ಫ್ಲೋನಲ್ಲಿ DMAC ಅನ್ನು ಪ್ರೇರೇಪಿಸಿ
                                        DMAC_CHCTRLA_TRIGACT_BURST;             // DMAC ಬರ್ಸ್ಟ್ ವರ್ಗಾವಣೆ

        _descriptor.descaddr = (uint32_t)&_descriptor_section[1];                    // ವೃತ್ತಾಕಾರ ವಿವರಣೆಕಾರರನ್ನು ಹೊಂದಿಸಿ
        _descriptor.srcaddr = (uint32_t)&ADC1->RESULT.reg;                           // ADC0 ಫಲಿತಾಂಶ ರಿಜಿಸ್ಟರ್‌ನಿಂದ ಫಲಿತಾಂಶವನ್ನು ಪಡೆದು ಕೊಳ್ಳಿ
        _descriptor.dstaddr = (uint32_t)_adc_buf_0 + sizeof(uint16_t) * ADC_BUF_LEN; // ಅದನ್ನು adc_buf_0 ಸರಣಿಯಲ್ಲಿ ಇಡು
        _descriptor.btcnt = ADC_BUF_LEN;                                             // ಬೀಟ್ ಗಣನೆ
        _descriptor.btctrl = DMAC_BTCTRL_BEATSIZE_HWORD |                            // ಬೀಟ್ ಗಾತ್ರ HWORD (16-ಬಿಟ್‌ಗಳು) ಆಗಿದೆ
                                DMAC_BTCTRL_DSTINC |                                    // ಗಮ್ಯಸ್ಥಾನ ವಿಳಾಸವನ್ನು ಹೆಚ್ಚಿಸಿ
                                DMAC_BTCTRL_VALID |                                     // ವಿವರಣೆಕಾರ ಮಾನ್ಯವಾಗಿದೆ
                                DMAC_BTCTRL_BLOCKACT_SUSPEND;                           // ಬ್ಲಾಕ್ ವರ್ಗಾವಣೆಯ ನಂತರ DMAC ಚಾನೆಲ್ 0 ಅನ್ನು ನಿಂತುಕೊಳ್ಳಿಸಿ
        memcpy(&_descriptor_section[0], &_descriptor, sizeof(_descriptor));          // ವಿವರಣೆಕಾರವನ್ನು ವಿವರಣೆಕಾರ ವಿಭಾಗಕ್ಕೆ ನಕಲು ಮಾಡು

        _descriptor.descaddr = (uint32_t)&_descriptor_section[0];                    // ವೃತ್ತಾಕಾರ ವಿವರಣೆಕಾರರನ್ನೂ ಹೊಂದಿಸಿ
        _descriptor.srcaddr = (uint32_t)&ADC1->RESULT.reg;                           // ADC0 ಫಲಿತಾಂಶ ರಿಜಿಸ್ಟರ್‌ನಿಂದ ಫಲಿತಾಂಶವನ್ನು ಪಡೆದು ಕೊಳ್ಳಿ
        _descriptor.dstaddr = (uint32_t)_adc_buf_1 + sizeof(uint16_t) * ADC_BUF_LEN; // ಅದನ್ನು adc_buf_1 ಸರಣಿಯಲ್ಲಿ ಇಡು
        _descriptor.btcnt = ADC_BUF_LEN;                                             // ಬೀಟ್ ಗಣನೆ
        _descriptor.btctrl = DMAC_BTCTRL_BEATSIZE_HWORD |                            // ಬೀಟ್ ಗಾತ್ರ HWORD (16-ಬಿಟ್‌ಗಳು) ಆಗಿದೆ
                                DMAC_BTCTRL_DSTINC |                                    // ಗಮ್ಯಸ್ಥಾನ ವಿಳಾಸವನ್ನು ಹೆಚ್ಚಿಸಿ
                                DMAC_BTCTRL_VALID |                                     // ವಿವರಣೆಕಾರ ಮಾನ್ಯವಾಗಿದೆ
                                DMAC_BTCTRL_BLOCKACT_SUSPEND;                           // ಬ್ಲಾಕ್ ವರ್ಗಾವಣೆಯ ನಂತರ DMAC ಚಾನೆಲ್ 0 ಅನ್ನು ನಿಂತುಕೊಳ್ಳಿಸಿ
        memcpy(&_descriptor_section[1], &_descriptor, sizeof(_descriptor));          // ವಿವರಣೆಕಾರವನ್ನು ವಿವರಣೆಕಾರ ವಿಭಾಗಕ್ಕೆ ನಕಲು ಮಾಡು

        // NVIC ಅನ್ನು ಸಂರಚಿಸಿ
        NVIC_SetPriority(DMAC_1_IRQn, 0); // DMAC1 ನ_nested ವೆಕ್ಟರ್ ಇಂಟರ್ಪ್ಟ್ ಕನ್ಟ್ರೋಲರ್ (NVIC) ಪ್ರಾಧಾನ್ಯತೆಯನ್ನು 0 (ಅತ್ಯಂತ ಮೇಲು ಸ್ಥಾನ) ಆಗಿ ಸೆಟ್ ಮಾಡಿ
        NVIC_EnableIRQ(DMAC_1_IRQn);      // DMAC1 ಅನ್ನು Nested Vector Interrupt Controller (NVIC) ಗೆ ಸಂಪರ್ಕಿಸಿ

        // DMAC ಚಾನೆಲ್ 1 ನಲ್ಲಿ ನಿಂತುಕೊಳ್ಳುವ (SUSP) ಇಂಟರ್ಪ್ಟ್ ಅನ್ನು ಸಕ್ರಿಯಗೊಳಿಸಿ
        DMAC->Channel[1].CHINTENSET.reg = DMAC_CHINTENSET_SUSP;

        // ADC ಅನ್ನು ಸಂರಚಿಸಿ
        ADC1->INPUTCTRL.bit.MUXPOS = ADC_INPUTCTRL_MUXPOS_AIN12_Val; // ವಿದ್ಯುನ್ಮಾನ ಇನ್ಪುಟ್ ಅನ್ನು ADC0/AIN2 (PB08 - ಮೆಟ್ರೋ M4 ನಲ್ಲಿ A4) ಆಗಿ ಸೆಟ್ ಮಾಡಿ
        while (ADC1->SYNCBUSY.bit.INPUTCTRL)
            ;                              // ಸಮಕಾಲೀಕರಣಕ್ಕಾಗಿ ಕಾಯಿರಿ
        ADC1->SAMPCTRL.bit.SAMPLEN = 0x00; // ಗರಿಷ್ಠ ಸ್ಯಾಂಪ್ಲಿಂಗ್ ಸಮಯವನ್ನು ಅರ್ಧ ವಿಭಾಗಿತ ADC ಘಡಿಯ ಅಲ್ಪಾವಧಿಗೆ (2.66us) ಸೆಟ್ ಮಾಡಿ
        while (ADC1->SYNCBUSY.bit.SAMPCTRL)
            ;                                         // ಸಮಕಾಲೀಕರಣಕ್ಕಾಗಿ ಕಾಯಿರಿ
        ADC1->CTRLA.reg = ADC_CTRLA_PRESCALER_DIV128; // ADC GTCLK ಅನ್ನು 128 ನಲ್ಲಿ ಹಂಚಿ (48MHz/128 = 375kHz)
        ADC1->CTRLB.reg = ADC_CTRLB_RESSEL_12BIT |    // ADC ರೆಸಲ್ಯೂಶನ್ ಅನ್ನು 12 ಬಿಟ್ ಒಳಗೊಂಡಂತೆ ಸೆಟ್ ಮಾಡಿ
                            ADC_CTRLB_FREERUN;          // ADC ಅನ್ನು ಫ್ರೀ ರನ್ ಮೋಡ್ ಗೆ ಸೆಟ್ ಮಾಡಿ
        while (ADC1->SYNCBUSY.bit.CTRLB)
            ;                       // ಸಮಕಾಲೀಕರಣಕ್ಕಾಗಿ ಕಾಯಿರಿ
        ADC1->CTRLA.bit.ENABLE = 1; // ADC ಅನ್ನು ಸಕ್ರಿಯಗೊಳಿಸಿ
        while (ADC1->SYNCBUSY.bit.ENABLE)
            ;                       // ಸಮಕಾಲೀಕರಣಕ್ಕಾಗಿ ಕಾಯಿರಿ
        ADC1->SWTRIG.bit.START = 1; // ADC ಪರಿವರ್ತನೆಯನ್ನು ಪ್ರಾರಂಭಿಸಲು ಸಾಫ್ಟ್‌ವೇರ್ ಟ್ರಿಗರ್‌ನ ಆರಂಭ ಮಾಡಿ
        while (ADC1->SYNCBUSY.bit.SWTRIG)
            ; // ಸಮಕಾಲೀಕರಣಕ್ಕಾಗಿ ಕಾಯಿರಿ

        // DMA ಚಾನೆಲ್ 1 ಅನ್ನು ಸಕ್ರಿಯಗೊಳಿಸಿ
        DMAC->Channel[1].CHCTRLA.bit.ENABLE = 1;

        // ಟೈಮರ್/ಕೌಂಟರ್ 5 ಅನ್ನು ಸಂರಚಿಸಿ
        GCLK->PCHCTRL[TC5_GCLK_ID].reg = GCLK_PCHCTRL_CHEN |     // TC5 ಗೆ ಪೆರಿಫೆರಲ್ ಚಾನೆಲ್ ಅನ್ನು ಸಕ್ರಿಯಗೊಳಿಸಿ
                                            GCLK_PCHCTRL_GEN_GCLK1; // 48MHz ನಲ್ಲಿ ಜನರಿಕ್ ಕ್ಲಾಕ್ 0 ಅನ್ನು ಸಂಪರ್ಕಿಸಿ

        TC5->COUNT16.WAVE.reg = TC_WAVE_WAVEGEN_MFRQ; // TC5 ಅನ್ನು మ్యాచ్ ಫ್ರೆಕ್ವೆನ್ಸಿ (MFRQ) ಮೋಡ್ ಗೆ ಸೆಟ್ ಮಾಡಿ
        TC5->COUNT16.CC[0].reg = 3000 - 1;            // ಟ್ರಿಗರ್ ಅನ್ನು 16 kHz ಗೆ ಸೆಟ್ ಮಾಡಿ: (4MHz / 16000) - 1
        while (TC5->COUNT16.SYNCBUSY.bit.CC0)
            ; // ಸಮಕಾಲೀಕರಣಕ್ಕಾಗಿ ಕಾಯಿರಿ

        // ಟೈಮರ್/ಕೌಂಟರ್ 5 ಅನ್ನು ಪ್ರಾರಂಭಿಸಿ
        TC5->COUNT16.CTRLA.bit.ENABLE = 1; // TC5 ಟೈಮರ್ ಅನ್ನು ಸಕ್ರಿಯಗೊಳಿಸಿ
        while (TC5->COUNT16.SYNCBUSY.bit.ENABLE)
            ; // ಸಮಕಾಲೀಕರಣಕ್ಕಾಗಿ ಕಾಯಿರಿ
    }

    uint16_t _adc_buf_0[ADC_BUF_LEN];
    uint16_t _adc_buf_1[ADC_BUF_LEN];
    ```

    ಈ ಕೋಡ್ `configureDmaAdc` ವಿಧಾನವನ್ನು ವ್ಯಾಖ್ಯಾನಿಸುತ್ತದೆ, ಇದು DMAC ಅನ್ನು ಸಂರಚಿಸುತ್ತದೆ, ADC ಗೆ ಸಂಪರ್ಕಿಸುತ್ತದೆ ಮತ್ತು ಎರಡು ಬದಲಾಗುವ ಬಫರ್ಗಳಾದ `_adc_buf_0` ಮತ್ತು `_adc_buf_1` ಅನ್ನು ತುಂಬುವಂತೆ ಸ್ಥಾಪಿಸುತ್ತದೆ.

    > 💁 ಮೈಕ್ರೋಕ್ವಂಟ್ರೋಲರ್ ಅಭಿವೃದ್ಧಿಯ ದುರ್ಬಲತೆಗಳಲ್ಲಿ ಒಂದು, ಅತಿ ಕಡಿಮೆ ಮಟ್ಟದಲ್ಲಿ ಹಾರ್ಡ್‌ವೇರ್ ನೊಂದಿಗೆ ಸಂವಹನ ಮಾಡುವಷ್ಟಕ್ಕೆ ಅಗತ್ಯವಿರುವ ಸಂಕೀರ್ಣತೆ. ಈ ಕೋಡ್ ಒಂದು ಸೆingle-ಬೋರ್ಡ್ ಕಂಪ್ಯೂಟರ್ ಅಥವಾ ಡೆಸ್ಕ್‌ಟಾಪ್ ಕಂಪ್ಯೂಟರಿ ಎದುರಿಸುವíodh ಊದು, ಏಕೆಂದ್ರೆ ಆಪರೇಟಿಂಗ್ ಸಿಸ್ಟಂ ಇಲ್ಲ, ಸಹಾಯಕ್ಕೆ ಇರುತ್ತದೆ. ಕೆಲವು ಲೈಬ್ರರಿಗಳು ಇದನ್ನು ಸರಳಗೊಳಿಸಲು ಲಭ್ಯವಿವೆ, ಆದರೆ ಇನ್ನೂ ಸಾಕಷ್ಟು ಸಂಕೀರ್ಣತೆ ಇದೆ.

1. ಇದರ ಕೆಳಗೆ ಕೆಳಗಿನ ಕೋಡ್ ಸೇರಿಸಿ:

    ```cpp
    // WAV ಫೈಲ್‌ಗಳಲ್ಲಿ ಒಂದು ಹೆಡರ್ ಇರುತ್ತದೆ. ಈ ಸ್ಟ್ರಕ್ಟ್ ಆ ಹೆಡರ್‌ನ್ನು ವ್ಯಾಖ್ಯಾನಿಸುತ್ತದೆ
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
        wavh.num_chans = 1;  // ಮೊನೋ
        wavh.srate = RATE;
        wavh.bytes_per_sec = (RATE * 1 * 16 * 1) / 8;
        wavh.bytes_per_samp = 2;
        wavh.bits_per_samp = 16;
        wavh.dlength = RATE * 2 * 1 * 16 / 2;
        wavh.flength = wavh.dlength + 44;

        _writer.writeSfudBuffer((byte *)&wavh, 44);
    }
    ```

    ಈ ಕೋಡ್ 44 ಬೈಟ್ ಗಳಿನ ನಿಮ್ಮ ಧ್ವನಿ ಫೈಲ್ ವಿವರಗಳಾದ ಹೀಡರ್ ಅನ್ನು ವೆವ್ ಎನ್ನುವ ಸಾರಾಂಶ ರೂಪದಲ್ಲಿ ರಚಿಸುತ್ತದೆ. ಇದು ಧ್ವನಿ ಫೈಲ್ ದರ, ಗಾತ್ರ ಮತ್ತು ಚಾನೆಲ್‌ಗಳ ಸಂಖ್ಯೆಯನ್ನು ಬರೆಯುತ್ತದೆ. ಈ ಹೀಡರ್ ಅನ್ನು ಫ್ಲಾಷ್ ಮೆಮೊರಿಗೆ ಬರೆಯಲಾಗುತ್ತದೆ.

1. ಈ ಕೋಡ್ ಕೆಳಗೆ, ಆಡಿಯೋ ಬಫರ್ಗಳನ್ನು ಪ್ರಕ್ರಿಯೆ ಮಾಡಲು ಕರೆಮಾಡುವ ವಿಧಾನವನ್ನು ಘೋಷಿಸಲು ಕೆಳಗಿನ ಕೋಡ್ ಸೇರಿಸಿ:

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

    ಆಡಿಯೋ ಬಫರ್ಗಳು 16-ಬಿಟ್ ಪೂರ್ಣಾಂಕಗಳ ಸೆರಳಾಗಿದೆ, ಇದು ADC ಲಿಂದಿಲಾದ ಧ್ವನಿ ಮಾಹಿತಿ. ADC 12-ಬಿಟ್ ಅನ್‌ಸೈನ್‌ಡ್ ಮೌಲ್ಯಗಳನ್ನು (0-1023) ನೀಡುತ್ತದೆ, ಆದ್ದರಿಂದ ಅವು 16-ಬಿಟ್ ಸೈನ್‌ಡ್ ಮೌಲ್ಯಗಳಿಗೆ ಪರಿವರ್ತನೆ ಮಾಡಬೇಕು, ನಂತರ 2 ಬೈಟ್ ಗಳಾಗಿ ಪರಿವರ್ತಿಸಿ ಕಚ್ಚಾ ಬೈನರಿ ಡೇಟಾ ಆಗಿ ಸಂಗ್ರಹಿಸಬೇಕು.

    ಈ ಬೈಟ್ಸ್ ಫ್ಲಾಷ್ ಮೆಮೊರಿ ಬಫರ್ಗಳಿಗೆ ಬರೆಯಲಾಗುತ್ತವೆ. ಬರವಣಿಗೆ ಇಂದೆಕ್ಸ್ 44 ರಿಂದ ಆರಂಭವಾಗುತ್ತದೆ – ಇದು 44 ಬೈಟ್ ವೆವ್ ಫೈಲ್ ಹೀಡರ್‌ನ ಔಟ್‌ಸೆಟ್. ಅಗತ್ಯ ಧ್ವನಿ ಅವಧಿಗೆ ಬೇಕಾದ ಎಲ್ಲಾ ಬೈಟ್ಸ್ ಹಿಡಿದ ನಂತರ, ಉಳಿದ ಡೇಟಾವನ್ನು ಫ್ಲಾಷ್ ಮೆಮೊರಿಗೆ ಬರೆಯಲಾಗುತ್ತದೆ.

1. `Mic` ಕ್ಲಾಸ್‌ನ `public` ವಿಭಾಗಕ್ಕೆ ಕೆಳಗಿನ ಕೋಡ್ ಸೇರಿಸಿ:

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

    ಈ ಕೋಡ್ ನಿಮ್ಮ ಕೋಡ್ ಅನ್ನು ಪ್ರಕ್ರಿಯೆ ಮಾಡಲು DMAC ಕರೆದಾಗ ಕರೆಯಲಾಗುತ್ತದೆ. ಇದು ಪ್ರಕ್ರಿಯೆಗೆ ಡೇಟಾ ಇದೆ ಎಂದು ಪರಿಶೀಲಿಸಿ, ಸಂಬಂಧಿತ ಬಫರ್ನೊಂದಿಗೆ `audioCallback` ವಿಧಾನವನ್ನು ಕರೆಮಾಡುತ್ತದೆ.

1. ಕ್ಲಾಸ್ ಹೊರಗೆ, `Mic mic;` ಘೋಷಣೆಯ ನಂತರ ಕೆಳಗಿನ ಕೋಡ್ ಸೇರಿಸಿ:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    `DMAC_1_Handler` DMAC ಬಫರ್ಗಳು ಪ್ರಕ್ರಿಯೆಗೆ ಸಿದ್ಧವಾಗಿದ್ದಾಗ DMAC ಕರೆದಿರುತ್ತದೆ. ಈ ಫಂಕ್ಷನ್ ಹೆಸರು ಮೂಲಕ ಕಂಡುಹಿಡಿಯಲಾಗುತ್ತದೆ ಮತ್ತು ಇದ್ದರೆ ಕರೆಮಾಡಲಾಗುತ್ತದೆ.

1. `Mic` ಕ್ಲಾಸ್‌ನ `public` ವಿಭಾಗಕ್ಕೆ ಈ ಎರಡು ವಿಧಾನಗಳನ್ನು ಸೇರಿಸಿ:

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

    `init` ವಿಧಾನವು `Mic` ಕ್ಲಾಸ್ ಅನ್ನು ಆರಂಭಿಸುವ ಕೋಡ್ ಒಳಗೊಂಡಿದೆ. ಈ ವಿಧಾನ Mic ಪಿನ್‌ಗಾಗಿ ಸರಿಯಾದ ವೋಲ್ಟೇಜ್ ಸೆಟ್ ಮಾಡುತ್ತದೆ, ಫ್ಲಾಷ್ ಮೆಮೊರಿ ಬರೆಯುವಾನೇ ವನ್ನು ಸಿದ್ಧಪಡಿಸುತ್ತದೆ, WAV ಫೈಲ್ ಹೀಡರ್ ಬರೆಯುತ್ತದೆ ಮತ್ತು DMAC ಅನ್ನು ಸಂರಚಿಸುತ್ತದೆ. `reset` ವಿಧಾನವು ಫ್ಲಾಷ್ ಮೆಮೊರಿಯನ್ನು ನೋಡಮಾಡುತ್ತದೆ ಹಾಗೂ ಧ್ವನಿ ಹಿಡಿದ ಬಳಿಕ ಹೀಡರ್ ಅನ್ನು ಮತ್ತೆ ಬರೆಯುತ್ತದೆ.

### ಕಾರ್ಯ - ಧ್ವನಿ ಹಿಡಿಯಿರಿ

1. `main.cpp` ಫೈಲ್‌ನಲ್ಲಿ `mic.h` ಹೆಡರ್ ಫೈಲ್ ಸೇರಿಸಲು ಸೂಚನೆ ಸೇರಿಸಿ:

    ```cpp
    #include "mic.h"
    ```

1. `setup` ಫಂಕ್ಷನ್‌ನಲ್ಲಿ C ಬಟನ್ ಅನ್ನು ಆರಂಭಿಸಿ. C ಬಟನ್ ಒತ್ತಿದಾಗ ಧ್ವನಿ ಹಿಡಿಯುವಿಕೆಯನ್ನು ಆರಂಭಿಸಿ, 4 ಸೆಕೆಂಡುಗಳ ಕಾಲ ಮುಂದುವರಿಯುತ್ತದೆ:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. ಇದಕ್ಕಿಂತ ಕೆಳಗೆ ಮೈಕ್ರೋಫೋನ್ ಅನ್ನು ಆರಂಭಿಸಿ ಮತ್ತು ಕಾನ್ಸೋಲ್‌ನಲ್ಲಿ ಧ್ವನಿ ಹಿಡಿಯಲು ಸಿದ್ಧವಾಗಿದೆ ಎಂದು ಮುದ್ರಿಸಿ:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. `loop` ಫಂಕ್ಷನ್ ಮೇಲ್ಭಾಗದಲ್ಲಿ ಹಿಡಿದ ಧ್ವನಿಯನ್ನು ಪ್ರಕ್ರಿಯೆಗೊಳಿಸುವ ಫಂಕ್ಷನ್ ವ್ಯಾಖ್ಯಾನಿಸಿ. ಈಗಿಗೆ ಇದು ಏನೂ անումದು, ಆದರೆ ನಂತರ ಈ ಪಾಠದಲ್ಲಿ ಮಾತಿನ ಸಂಭಾಷಣೆಯನ್ನು ಪಠ್ಯವಾಗಿ ಪರಿವರ್ತಿಸಲು ಬಳಸಲಾಗುತ್ತದೆ:

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. `loop` ಫಂಕ್ಷನ್‌ಗೆ ಕೆಳಗಿನ ಕೋಡ್ ಸೇರಿಸಿ:

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

    ಈ ಕೋಡ್ C ಬಟನ್‌ನ ಸ್ಥಿತಿಯನ್ನು ಪರಿಶೀಲಿಸುತ್ತದೆ, ಮತ್ತು ಒತ್ತಿದಾಗ ಮತ್ತು ರೆಕಾರ್ಡಿಂಗ್ ಆರಂಭವಾಗದಿದ್ದರೆ, `Mic` ಕ್ಲಾಸ್‌ನ `_isRecording` ಕ್ಷೇತ್ರವನ್ನು true ಗೆ ಸೆಟ್ ಮಾಡುತ್ತದೆ. ಇದರಿಂದ `audioCallback` ವಿಧಾನವು 4 ಸೆಕೆಂಡುಗಳ ಧ್ವನಿಯನ್ನು ಸಂಗ್ರಹಿಸುತ್ತದೆ. 4 ಸೆಕೆಂಡುಗಳ ಧ್ವನಿಯನ್ನು ಹಿಡಿದ ನಂತರ, `_isRecording` false ಆಗಿ ಸೆಟ್ ಮಾಡುತ್ತದೆ ಮತ್ತು `_isRecordingReady` true ಆಗಿ ಹೊಂದುತ್ತದೆ. ಇದನ್ನು `loop` ನಲ್ಲಿ ಪರಿಶೀಲಿಸಿ, ಸತ್ಯವಾದಾಗ `processAudio` ಫಂಕ್ಷನ್ ಅನ್ನು ಕರೆಮಾಡುತ್ತದೆ, ನಂತರ ಮೈಕ್ ಕ್ಲಾಸ್ ಅನ್ನು ರೀಸೆಟ್ ಮಾಡುತ್ತದೆ.

1. ಈ ಕೋಡ್ ನಿರ್ಮಿಸಿ, ನಿಮ್ಮ Wio Terminal ಗೆ ಅಪ್ಲೋಡ್ ಮಾಡಿ ಮತ್ತು ಸೀರಿಯಲ್ ಮಾನಿಟರ್ ಮೂಲಕ ಪರೀಕ್ಷಿಸಿ. C ಬಟನ್ (ಎಡ ಬದಿ ಬಟನ್, ಪವರ್ ಸ್ವಿಚ್ ಗೆ ಅತ್ಯಂತ ಹತ್ತಿರದಲ್ಲಿರುವುದು) ಒತ್ತಿ, ಮತ್ತು ಮಾತಾಡಿ. 4 ಸೆಕಿಂಡುಗಳ ಧ್ವನಿ ಹಿಡಿಯಲಾಗುತ್ತದೆ.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Ready.
    Starting recording...
    Finished recording
    ```

> 💁 ನೀವು ಈ ಕೋಡ್ ಅನ್ನು [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal) ಫೋಲ್ಡರ್‌ನಲ್ಲಿ ಹುಡುಕಬಹುದು.

😀 ನಿಮ್ಮ ಧ್ವನಿ ದಾಖಲೆ ಕಾರ್ಯಕ್ರಮ ಯಶಸ್ವಿಯಾದದ್ದು!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ಐಚ್ಛಿಕ ಮೇಲ್ಮnosis**:  
ಈ ಡಾಕ್ಯುಮೆಂಟ್ ಅನ್ನು AI ಅನುವಾದ ಸೇವೆ [Co-op Translator](https://github.com/Azure/co-op-translator) ಬಳಸಿ ಅನುವಾದಿಸಲಾಗಿದೆ. ನಾವು ಶುದ್ಧತೆಯ ನಿಟ್ಟಿನಲ್ಲಿ ಪ್ರಯತ್ನಿಸುತ್ತಿದ್ದರೂ, ಸ್ವಯಂಚಾಲಿತ ಅನುವಾದಗಳಲ್ಲಿ ದೋಷಗಳು ಅಥವಾ ತಪ್ಪುಿಗಳು ಇರಬಹುದು ಎಂದು ದಯವಿಟ್ಟು ಗಮನಿಸಿ. ಮೂಲ ಡಾಕ್ಯುಮೆಂಟ್ ಅದರ ಅಸ್ಥಾನಿಕ ಭಾಷೆಯಲ್ಲಿ ಅಧಿಕೃತ ಮೂಲವೆಂದು ಪರಿಗಣಿಸಬೇಕು. ಮಹತ್ವಪೂರ್ಣ ಮಾಹಿತಿಗಾಗಿ ವೃತ್ತಿಪರ ಮಾನವ ಅನುವಾದವನ್ನು ಶಿಫಾರಸು ಮಾಡಲಾಗುತ್ತದೆ. ಈ ಅನುವಾದದ ಬಳಕೆಯಿಂದ ಉಂಟಾಗುವ ಯಾವುದೇ ತರ್ಕತಲ್ಲತೆಗಳು ಅಥವಾ ತಪ್ಪುಗ್ರಹಣಕ್ಕಾಗಿ ನಾವು ಹೊಣೆಗಾರರಲ್ಲ.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->