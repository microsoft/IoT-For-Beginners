<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0d55caa8c23d73635b7559102cd17b8a",
  "translation_date": "2026-01-07T05:03:31+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/wio-terminal-soil-moisture.md",
  "language_code": "kn"
}
-->
# ಮಣ್ಣು ತೇವತೆಯನ್ನು ಅಳತೆ ಮಾಡುವುದು - Wio ಟರ್ಮಿನಲ್

ಪಾಠದ ಈ ಭಾಗದಲ್ಲಿ, ನೀವು ನಿಮ್ಮ Wio ಟರ್ಮಿನಲ್‌ಗೆ ಕ್ಯಾಪಾಸಿಟಿವ್ ಮಣ್ಣು ತೇವತೆ ಸೆನ್ಸಾರ್ ಸೇರಿಸಲಿದ್ದೀರಿ ಮತ್ತು ಅದರ ಮೌಲ್ಯಗಳನ್ನು ಓದಲು ಕಲಿಯುತ್ತೀರಿ.

## ಹಾರ್ಡ್‌ವೇರ್

Wio ಟರ್ಮಿನಲ್‌ಗೆ ಕ್ಯಾಪಾಸಿಟಿವ್ ಮಣ್ಣು ತೇವತೆ ಸೆನ್ಸಾರ್ ಬೇಕಾಗುತ್ತದೆ.

ನೀವು ಬಳಸಲಿರುವ ಸೆನ್ಸಾರ್ ಒಂದು [ಕ್ಯಾಪಾಸಿಟಿವ್ ಮಣ್ಣು ತೇವತೆ ಸೆನ್ಸಾರ್](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), ಇದು ಮಣ್ಣಿನ ಕ್ಯಾಪಾಸಿಟೆನ್ಸ್ ಪತ್ತೆಮಾಡಿ ಮಣ್ಣು ತೇವತೆಯನ್ನು ಅಳೆಯುತ್ತದೆ, ಇದು ಮಣ್ಣು ತೇವತೆ ಬದಲಾದಂತೆ ಬದಲಾಗುವ ಲಕ್ಷಣವಾಗಿದೆ. ಮಣ್ಣು ತೇವತೆ ಏರುತ್ತಿರುವಾಗ, ವೋಲ್ಟ್‌ತೆ ಕಡಿಮೆಯಾಗುತ್ತದೆ.

ಇದು ಅನಾಲಾಗ್ ಸೆನ್ಸಾರ್, ಆದ್ದರಿಂದ ಇದು Wio ಟರ್ಮಿನಲ್‌ನ ಅನಾಲಾಗ್ ಪಿನ್‌ಗಳಿಗೆ ಸಂಪರ್ಕಿಸುವುದು, ಆನ್‌ಬೋರ್ಡ್ ADC ಬಳಸಿಕೊಂಡು 0-1,023 ನಡುವೆ ಮೌಲ್ಯವನ್ನು ರಚಿಸುತ್ತದೆ.

### ಮಣ್ಣು ತೇವತೆ ಸೆನ್ಸಾರ್ ಸಂಪರ್ಕಿಸಿ

ಗ್ರೋವ್ ಮಣ್ಣು ತೇವತೆ ಸೆನ್ಸಾರ್ ಅನ್ನು Wio ಟರ್ಮಿನಲ್‌ನ ಕನ್ಫಿಗರ್ ಮಾಡಬಹುದಾದ ಅನಾಲಾಗ್/ಡಿಜಿಟಲ್ ಪೋರ್ಟಿಗೆ ಸಂಪರ್ಕಿಸಬಹುದು.

#### ಕಾರ್ಯ - ಮಣ್ಣು ತೇವತೆ ಸೆನ್ಸಾರ್ ಸಂಪರ್ಕಿಸಿ

ಮಣ್ಣು ತೇವತೆ ಸೆನ್ಸಾರ್ ಸಂಪರ್ಕಿಸಿ.

![A grove soil moisture sensor](../../../../../translated_images/kn/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78b.png)

1. ಗ್ರೋವ್ ಕೇಬಲ್‌ನ ಒಂದು ಕೊನೆಯನ್ನು ಮಣ್ಣು ತೇವತೆ ಸೆನ್ಸಾರ್‌ನ ಸೊಕೆಟ್‌ಗೆ ಹಾಕಿ. ಇದು ಕೇವಲ ಒಂದು ದಿಕ್ಕಿಗೆ ಹಾಸಿಕೊಳ್ಳುತ್ತದೆ.

1. ನಿಮ್ಮ ಕಂಪ್ಯೂಟರ್ ಅಥವಾ ಇತರ ವಿದ್ಯುತ್ ಸರಬರಾಜಿನಿಂದ Wio ಟರ್ಮಿನಲ್ ಅನ್ನು ಡಿಸ್ಕನೆಕ್ಟ್ ಮಾಡಿರುವಾಗ, ಗ್ರೋವ್ ಕೇಬಲ್‌ನ ಇನ್ನೊಂದು ಕೊನೆಯನ್ನು Wio ಟರ್ಮಿನಲ್‌ನ ಬಲಭಾಗದ ಗ್ರೋವ್ ಸೊಕೆಟ್‌ಗೆ ಸಂಪರ್ಕಿಸಿ. ನೀವು ಪರದೆ ನೋಡಿ ಇದ್ದಾಗ, ಇದು ವಿದ್ಯುತ್ ಬಟನ್‌ನಿಂದ ಅತಿದೂರದಲ್ಲಿರುವ ಸೊಕೆಟ್ ಆಗಿದೆ.

![The grove soil moisture sensor connected to the right hand socket](../../../../../translated_images/kn/wio-soil-moisture-sensor.46919b61c3f6cb74.png)

1. ಮಣ್ಣು ತೇವತೆ ಸೆನ್ಸಾರ್ ಅನ್ನು ಮಣ್ಣಿಗೆ ಹಾಯಿಸಿ. ಇದರಲ್ಲಿ 'ಅತ್ಯಧಿಕ ಸ್ಥಾನ ಶ್ರೇಣಿ' ಇದ್ದು - ಒಂದು ಬಿಳಿ ರೇಖೆ ಸೆನ್ಸಾರ್ ಮುಖಾಂತರ ಹೋಗುತ್ತದೆ. ಈ ರೇಖೆಯವರೆಗೆ ಮಾತ್ರ ಸೆನ್ಸಾರ್ ಅನ್ನು ಹಾಕಿ, ಅವಳಿ ಅದರ ಪಕ್ಕಕ್ಕೆ ಹೋಗದಿರಲಿ.

![The grove soil moisture sensor in soil](../../../../../translated_images/kn/soil-moisture-sensor-in-soil.bfad91002bda5e96.png)

1. ಈಗ ನೀವು Wio ಟರ್ಮಿನಲ್ ಅನ್ನು ನಿಮ್ಮ ಕಂಪ್ಯೂಟರ್‌ಗೆ ಸಂಪರ್ಕಿಸಬಹುದು.

## ಮಣ್ಣು ತೇವತೆ ಸೆನ್ಸಾರ್ ಪ್ರೋಗ್ರಾಂ ಮಾಡುವುದು

Wio ಟರ್ಮಿನಲ್ ಈಗನು ಸಂಪರ್ಕಿಸಲಾದ ಮಣ್ಣು ತೇವತೆ ಸೆನ್ಸಾರ್ ಬಳಸಲು ಪ್ರೋಗ್ರಾಂ ಮಾಡಬಹುದು.

### ಕಾರ್ಯ - ಮಣ್ಣು ತೇವತೆ ಸೆನ್ಸಾರ್ ಪ್ರೋಗ್ರಾಂ ಮಾಡಿ

ಉಪಕರಣವನ್ನು ಪ್ರೋಗ್ರಾಂ ಮಾಡಿ.

1. PlatformIO ಬಳಸಿ ಹೊಸ Wio ಟರ್ಮಿನಲ್ ಪ್ರಾಜೆಕ್ಟ್ ಸೃಷ್ಟಿಸಿ. ಈ ಪ್ರಾಜೆಕ್ಟ್‌ಗೆ `soil-moisture-sensor` ಎಂದು ಹೆಸರಿಡಿ. ಸರಿಯಾಗಿದೆ. `setup` ಫಂಕ್ಷನ್‌ನಲ್ಲಿ ಸೀರಿಯಲ್ ಪೋರ್ಟ್ ನಡುರಷ್ಟು ಮಾಡು.

    > ⚠️ ಅಗತ್ಯವಿದ್ದರೆ, [ಪ್ರಾಜೆಕ್ಟ್ 1, ಪಾಠ 1 ರಲ್ಲಿ PlatformIO ಪ್ರಾಜೆಕ್ಟ್ ಸೃಷ್ಟಿಸುವ ನಿರ್ದೇಶನವನ್ನು ನೋಡಿ](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. ಈ ಸೆನ್ಸಾರ್‌ಗೆ ಲೈಬ್ರರಿ ಲಭ್ಯವಿಲ್ಲ, ಆದ್ದರಿಂದ ನೀವು ಅಪೇಕ್ಷಣೀಯಪಿನ್‌ನಿಂದ ಸ್ಥಾನದಲ್ಲಿರುವ Arduino [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/) ಫಂಕ್ಷನ್ ಬಳಸಿ ಓದಲು ಸಾಧ್ಯ. ಮೊದಲು ಸೀರಿಯಲ್ ಹಂತದಲ್ಲಿ ಪಿನ್ ಅನ್ನು ಇನ್ಪುಟ್ ಆಗಿ ಸಿದ್ಧಮಾಡಿ ಕೆಳಗಿನಂತೆ `setup` ಫಂಕ್ಷನ್‌ಗೆ ಸೇರಿಸಿ.

    ```cpp
    pinMode(A0, INPUT);
    ```

    ಇದು `A0` ಪಿನ್, ಸಂಯುಕ್ತ ಅನಾಲಾಗ್/ಡಿಜಿಟಲ್ ಪಿನ್, ಇನ್ಪುಟ್ ಪಿನ್ ಆಗಿ ಸಿದ್ಧಪಡಿಸುವುದರಿಂದ ವೋಲ್ಟೇಜ್ ಓದಲು ಸಾಧ್ಯವಾಗುತ್ತದೆ.

1. ಈ ಪಿನ್‌ನಿಂದ ವೋಲ್ಟೇಜ್ ಓದಿಕೊಳ್ಳಲು `loop` ಫಂಕ್ಷನ್‌ಗೆ ಕೆಳಗಿನಂತೆಯೂ ಸೇರಿಸಿ:

    ```cpp
    int soil_moisture = analogRead(A0);
    ```


1. ಈ ಕೋಡ್ ಕೆಳಗೆ ಸರಿಯಲ್ ಪೋರ್ಟಿಗೆ ಮೌಲ್ಯವನ್ನು ಮುದ್ರಣ ಮಾಡುವ ಕೋಡ್ ಸೇರಿಸಿ:

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```


1. ಕೊನೆಗೆ 10 ಸೆಕೆಂಡುಗಳ ವಿಳಂಬವನ್ನು ಸೇರಿಸಿ:

    ```cpp
    delay(10000);
    ```


1. ಕೋಡ್ ಸಂರಚಿಸಿ ಮತ್ತು Wio ಟರ್ಮಿನಲ್‌ಗೆ ಅಪ್ಲೋಡ್ ಮಾಡಿ.

    > ⚠️ ಅಗತ್ಯವಿದ್ದರೆ, [ಪ್ರಾಜೆಕ್ಟ್ 1, ಪಾಠ 1 ರಲ್ಲಿ PlatformIO ಪ್ರಾಜೆಕ್ಟ್ ಸೃಷ್ಟಿಸುವ ನಿರ್ದೇಶನವನ್ನು ನೋಡಿ](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. ಅಪ್ಲೋಡ್ ಆದ ನಂತರ, ಸರಿಯಲ್ ಮಾನಿಟರ್ ಬಳಸಿ ಮಣ್ಣು ತೇವತೆಯನ್ನು ಗಮನಿಸಬಹುದು. ಮಣ್ಣಿಗೆ ಸ್ವಲ್ಪ ನೀರು ಹಾಕಿ, ಅಥವಾ ಸೆನ್ಸಾರ್ ಅನ್ನು ಮಣ್ಣಿನಿಂದ ತೆಗೆದು ಮಾಡಿ, ಮೌಲ್ಯದಲ್ಲಿ ಬದಲಾವಣೆ ಗಮನಿಸಿ.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Soil Moisture: 526
    Soil Moisture: 529
    Soil Moisture: 521
    Soil Moisture: 494
    Soil Moisture: 454
    Soil Moisture: 456
    Soil Moisture: 395
    Soil Moisture: 388
    Soil Moisture: 394
    Soil Moisture: 391
    ```

    ಮೇಲ್ಕಂಡ ಉದಾಹರಣೆ ಇನ್‌ಪುಟ್‌ನಲ್ಲಿ ನೀರು ಹಾಕಿದಂತೆ ವೋಲ್ಟೇಜ್ ಕುಸಿತವಾಗಿದ್ದಷ್ಟೇ ನೋಡಬಹುದು.

> 💁 ನೀವು ಈ ಕೋಡ್ ಅನ್ನು [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal) ಫೋಲ್ಡರ್‌ನಲ್ಲಿ ಕಂಡುಹಿಡಿಯಬಹುದು.

😀 ನಿಮ್ಮ ಮಣ್ಣು ತೇವತೆ ಸೆನ್ಸರ್ ಪ್ರೋಗ್ರಾಂ ಯಶಸ್ವಿಯಾಗಿದೆ!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ಅಸರ್ಟ್ಮೆಂಟ್**:
ಈ ದಾಖಲೆಯನ್ನು AI ಅನುವಾದ ಸೇವೆ [Co-op Translator](https://github.com/Azure/co-op-translator) ಬಳಸಿ ಅನುವಾದಿಸಲಾಗಿದೆ. ನಾವು ಶುದ್ಧತೆಗೆ ಪ್ರಯತ್ನಿಸಿದರೂ, ಸ್ವಯಂಚಾಲಿತ ಅನುವಾದಗಳಲ್ಲಿ ದೋಷಗಳು ಅಥವಾ ತಪ್ಪುಗಳು ಇದ್ದಿರಬಹುದು ಎಂಬುದನ್ನು ಗಮನದಲ್ಲಿಟ್ಟುಕೊಳ್ಳಿ. ಮೂಲ ದಾಖಲೆ ಅದರ ಸ್ವ Countryовом ಭಾಷೆಯಲ್ಲಿ ಪ್ರಮಾಣಭರಿತ ಮೂಲವೆಂದು ಪರಿಗಣಿಸಲಾಗಬೇಕು. ಮಹತ್ವದ ಮಾಹಿತಿಗಾಗಿ, ವೃತ್ತಿಪರ ಮಾನವ ಅನುವಾದವನ್ನು ಶಿಫಾರಸು ಮಾಡಲಾಗುತ್ತದೆ. ಈ ಅನುವಾದದ ಬಳಕೆಯಿಂದ ಉಂಟಾಗಬಹುದಾದ ಯಾವುದೇ ಅರ್ಥಮಾರ್ಪಣೆಗಳಿಂದ ಅಥವಾ ತಪ್ಪುವುಗಳಿಂದ ನಾವು ಹೊಣೆಗಾರರಾಗುವುದಿಲ್ಲ.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->