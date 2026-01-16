<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2026-01-07T02:19:29+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "kn"
}
-->
# ಇಂಟರ್ನೆಟ್ನಲ್ಲಿ ನಿಮ್ಮ ನೈಟ್‌ಲೈಟ್ ಅನ್ನು ನಿಯಂತ್ರಿಸಿ - Wio ಟರ್ಮಿನಲ್

IoT ಸಾಧನವು *test.mosquitto.org* ಬಳಸಿ MQTT ಮೂಲಕ ಬೆಳಕಿನ ಸಂವೇದಕ ಓದುವ ಜೊತೆಗೆ ಟೆಲಿಮೆಟ್ರಿ ಮೌಲ್ಯಗಳನ್ನು ಕಳುಹಿಸಲು ಮತ್ತು LED ಅನ್ನು ನಿಯಂತ್ರಿಸುವ ಆಜ್ಞೆಗಳನ್ನು ಸ್ವೀಕರಿಸಲು ಕೋಡ್ ಮಾಡಬೇಕಾಗುತ್ತದೆ.

ಪಾಠದ ಈ ಭಾಗದಲ್ಲಿ, ನೀವು ನಿಮ್ಮ Wio ಟರ್ಮಿನಲ್ ಅನ್ನು MQTT ಬ್ರೋಕರ್‌ಗೆ ಸಂಪರ್ಕಿಸುತ್ತೀರಿ.

## WiFi ಮತ್ತು MQTT ಅರ್ಡಿನೋ ಗ್ರಂಥಾಲಯಗಳನ್ನು ಸ್ಥಾಪಿಸಿ

MQTT ಬ್ರೋಕರ್‌ಗಳೊಂದಿಗೆ ಸಂವಹನ ಮಾಡಲು, ನೀವು Wio ಟರ್ಮಿನಲ್‌ನ WiFi ಚಿಪ್ ಅನ್ನು ಬಳಸಲು ಮತ್ತು MQTT ಸಮಾಧಾನವಾಗಿ ಸಂವಹನ ಮಾಡಲು ಕೆಲವು ಅರ್ಡಿನೋ ಗ್ರಂಥಾಲಯಗಳನ್ನು ಸ್ಥಾಪಿಸಬೇಕು. ಅರ್ಡಿನೋ ಸಾಧನಗಳಿಗಾಗಿ ಅಭಿವೃದ್ಧಿಪಡಿಸುವಾಗ, ನೀವು ಬಹುಮಟ್ಟಿಗೆ ಲೈಬ್ರರಿಗಳನ್ನು ಬಳಸಬಹುದು, ಅವುಗಳಲ್ಲಿ ಮುಕ್ತ ಮೂಲ ಕೋಡ್ ಮತ್ತು ವಿಶಾಲ ಶ್ರೇಣಿಯ ಸಾಮರ್ಥ್ಯಗಳನ್ನು ಕಾರ್ಯಗತಗೊಳಿಸಲಾಗಿದೆ. Seeed Wio ಟರ್ಮಿನಲ್ ಬಳಕೆದಾರರಿಗೆ WiFi ಮೂಲಕ ಸಂಪರ್ಕಿಸಲು ಗ್ರಂಥಾಲಯಗಳನ್ನು ಪ್ರಕಟಿಸಿದೆ. ಇತರೆ ಅಭಿವೃದ್ಧಿಪಡಿಸುತ್ತಿರುವವರು MQTT ಬ್ರೋಕರ್‌ಗಳೊಂದಿಗೆ ಸಂವಹನ ಮಾಡಲು ಗ್ರಂಥಾಲಯಗಳನ್ನು ಪ್ರಕಟಿಸಿದ್ದಾರೆ ಮತ್ತು ನೀವು ನಿಮ್ಮ ಸಾಧನದೊಂದಿಗೆ ಅವುಗಳನ್ನು ಬಳಸಲಿದ್ದೀರಿ.

ಈ ಗ್ರಂಥಾಲಯಗಳನ್ನು ಮೂಲ ಕೋಡ್ ರೂಪದಲ್ಲಿ PlatformIO ಗೆ ಸ್ವಯಂಶಕ್ತಿಯಾಗಿ ಆಮದುಮಾಡಿ ನಿಮ್ಮ ಸಾಧನಕ್ಕೆ ಸಂಯೋಜಿಸಲಾಗುತ್ತದೆ. ಈ ರೀತಿಯಾಗಿ, ಅರ್ಡಿನೋ ಗ್ರಂಥಾಲಯಗಳು ಅರ್ಡಿನೋ ಫ್ರೆ임್ವರ್ಕ್ ಬೆಂಬಲಿಸುವ ಯಾವುದೇ ಸಾಧನದಲ್ಲಿ ಕಾರ್ಯನಿರ್ವಹಿಸುತ್ತವೆ, ಗ್ರಂಥಾಲಯಕ್ಕೆ ನಿರ್ದಿಷ್ಟವಾಗಿ ಅಗತ್ಯವಿರುವ ಯಾವುದೇ ಹಾರ್ಡ್‌ವೇರ್ ಇದ್ದೀತೆಂದು ಅಂದುಕೊಳ್ಳುವುದಾದರೆ. ಕೆಲವು ಗ್ರಂಥಾಲಯಗಳು, ಉದಾಹರಣೆಗೆ Seeed WiFi ಗ್ರಂಥಾಲಯಗಳು, ನಿರ್ದಿಷ್ಟ ಹಾರ್ಡ್‌ವೇರ್‌ಗಳಿಗೆ ವಿಶೇಷ.

ಗ್ರಂಥಾಲಯಗಳನ್ನು ಜಾಗತಿಕವಾಗಿ ಸ್ಥಾಪಿಸಬಹುದು ಮತ್ತು ಸಂಯೋಜಿಸಬಹುದು ಅಥವಾ ವಿಶೇಷ ಯೋಜನೆಯೊಳಗೆ. ಈ ಕಾರ್ಯಕ್ಕೆ, ಗ್ರಂಥಾಲಯಗಳನ್ನು ಯೋಜನೆಯೊಳಗೆ ಸ್ಥಾಪಿಸಲಾಗುತ್ತದೆ.

✅ ಗ್ರಂಥಾಲಯ ನಿರ್ವಹಣೆ, ಗ್ರಂಥಾಲಯಗಳನ್ನು ಹುಡುಕಿ ಸ್ಥಾಪಿಸುವ ಬಗ್ಗೆ ಇನ್ನಷ್ಟು ತಿಳಿಯಲು, [PlatformIO ಗ್ರಂಥಾಲಯ ಡಾಕ್ಯುಮೆಂಟೇಶನ್](https://docs.platformio.org/en/latest/librarymanager/index.html) ನೋಡಿ.

### ಕಾರ್ಯ - WiFi ಮತ್ತು MQTT ಅರ್ಡಿನೋ ಗ್ರಂಥಾಲಯಗಳನ್ನು ಸ್ಥಾಪಿಸಿ

ಅರ್ಡಿನೋ ಗ್ರಂಥಾಲಯಗಳನ್ನು ಸ್ಥಾಪಿಸಿ.

1. VS ಕೋಡ್‌ನಲ್ಲಿ nightlight ಯೋಜನೆಯನ್ನು ತೆರೆದುಕೊಳ್ಳಿ.

1. `platformio.ini` ಫೈಲ್‌ನ ಕೊನೆಯಲ್ಲಿ ಕೆಳಗಿನ ವಿಷಯವನ್ನು ಸೇರಿಸಿ:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```
  
    ಇದು Seeed WiFi ಗ್ರಂಥಾಲಯಗಳನ್ನು ಆಮದುಮಾಡುತ್ತದೆ. `@ <number>` ಪದಚ್ಛೇದವು ಗ್ರಂಥಾಲಯದ ನಿರ್ದಿಷ್ಟ ಆವೃತ್ತಿಯನ್ನು ಸೂಚಿಸುತ್ತದೆ.

    > 💁 ನೀವು `@ <number>` ತೆಗೆದುಹಾಕಿ ಯಾವಾಗಲಾದರೂ ಹೊಸ ಆವೃತ್ತಿಯನ್ನು ಬಳಸಬಹುದು, ಆದರೆ ನಂತರದ ಆವೃತ್ತಿಗಳು ಕೆಳಗಿನ ಕೋಡ್ ಜೊತೆಗೆ ಕಾರ್ಯನಿರ್ವಹಿಸುವುದಕ್ಕೆ ಯಾವುದೇ ಭರವಸೆ ಇಲ್ಲ. ಈ ಕೋಡ್ ಈ ಆವೃತ್ತಿಯೊಂದಿಗೆ ಪರೀಕ್ಷಿಸಲಾದದ್ದು.

    ಗ್ರಂಥಾಲಯಗಳನ್ನು ಸೇರಿಸಲು ನಿಮಗೆ ಬಯಸಿದದ್ದು ಇದು ಮಾತ್ರ. ಮುಂದಿನ ಸಲ PlatformIO ಯೋಜನೆಯನ್ನು ನಿರ್ಮಿಸುವಾಗ ಈ ಗ್ರಂಥಾಲಯಗಳ ಮೂಲ ಕೋಡ್ ಡೌನ್‌ಲೋಡ್ ಮಾಡಿ ನಿಮ್ಮ ಯೋಜನೆಯಲ್ಲಿ ಸಂಯೋಜಿಸುತ್ತದೆ.

1. `lib_deps` ಗೆ ಕೆಳಗಿನತ್ತ ಸೇರಿಸಿ:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```
  
    ಇದು [PubSubClient](https://github.com/knolleary/pubsubclient), ಅರ್ಡಿನೋ MQTT ಕ್ಲಾಇಂಟ್ ಅನ್ನು ಆಮದುಮಾಡುತ್ತದೆ

## WiFi ಗೆ ಸಂಪರ್ಕ ಮಾಡಿರಿ

ಈಗ Wio ಟರ್ಮಿನಲ್ ಅನ್ನು WiFi ಗೆ ಸಂಪರ್ಕಿಸಲು ಸಿದ್ಧವಾಗಿದೆ.

### ಕಾರ್ಯ - WiFi ಗೆ ಸಂಪರ್ಕ ಮಾಡಿರಿ

Wio ಟರ್ಮಿನಲ್ ಅನ್ನು WiFi ಗೆ ಸಂಪರ್ಕಿಸಿರಿ.

1. `src` ಫೋಲ್ಡರ್‌ನಲ್ಲಿ `config.h` ಎಂಬ ಹೊಸ ಫೈಲ್ ಅನ್ನು ಸೃಷ್ಟಿಪಡಿ. ನೀವು ಇದನ್ನು `src` ಫೋಲ್ಡರ್ ಅನ್ನು ಅಥವಾ ಅದರ ಒಳಗಿನ `main.cpp` ಫೈಲ್ ಆಯ್ಕೆ ಮಾಡಿ, ಎಕ್ಸ್‌ಪ್ಲೋರರ್‌ನಿಂದ **ಹೊಸ ಫೈಲ್** ಬಟನ್ ನೀಡಿಸಿ ಮಾಡಬಹುದು. ಈ ಬಟನ್ ಕರ್ಸರ್ ಎಕ್ಸ್‌ಪ್ಲೋರರ್ ಮೇಲೆ ಇದ್ದಾಗ ಮಾತ್ರ ತೋರುತ್ತದೆ.

    ![ಹೊಸ ಫೈಲ್ ಬಟನ್](../../../../../translated_images/kn/vscode-new-file-button.182702340fe6723c.png)

1. ನಿಮಗೆ ಅಗತ್ಯವಿರುವ WiFi ದಾಖಲೆಗಳನ್ನು ವ್ಯಾಖ್ಯಾನಿಸುವ ಕಾನ್ಸ್ಟಂಟ್‌ಗಳಿಗಾಗಿ ಈ ಫೈಲ್‌ಗೆ ಕೆಳಗಿನ ಕೋಡ್ ಸೇರಿಸಿ:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // ವೈಫೈಪ್ರಮಾಣಿ೯ಗಳು
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```
  
    `<SSID>` ಅನ್ನು ನಿಮ್ಮ WiFi SSID ನೊಂದಿಗೆ ಬದಲಾಯಿಸಿ. `<PASSWORD>` ಅನ್ನು ನಿಮ್ಮ WiFi ಪಾಸ್ವರ್ಡ್‌ನೊಂದಿಗೆ ಬದಲಾಯಿಸಿ.

1. `main.cpp` ಫೈಲ್ ಅನ್ನು ತೆರೆಯಿರಿ

1. ಫೈಲ್‌ನ ಮೇಲಭಾಗದಲ್ಲಿ ಕೆಳಗಿನ `#include` ಸೂಚನೆಗಳನ್ನು ಸೇರಿಸಿ:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```
  
    ಇದು ನಿಮಗೆ ಮುಂದೆ ಸೇರಿಸಿರುವ ಗ್ರಂಥಾಲಯಗಳ ಹೆಡರ್ ಫೈಲ್‌ಗಳನ್ನು ಹಾಗೂ config ಹೆಡರ್ ಫೈಲ್‌ನ್ನು ಒಳಗೊಂಡಿರುತ್ತದೆ. ಈ ಹೆಡರ್‌ಗಳನ್ನು ಸ್ಪಷ್ಟವಾಗಿ ಸೇರಿಸದೇ ಇದ್ದರೆ, ಕೆಲವು ಕೋಡ್‌ಗಳು ಸಂಯೋಜಿಸಲಾಗುವುದಿಲ್ಲ ಮತ್ತು ಸಂಯೋಜನಾ ದೋಷಗಳು ಸಂಭವಿಸುತ್ತವೆ.

1. ಕೆಳಗಿನ ಕೋಡ್ ಅನ್ನು `setup` ಫಂಕ್ಷನ್ ಮೇಲೆ ಸೇರಿಸಿ:

    ```cpp
    void connectWiFi()
    {
        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("Connecting to WiFi..");
            WiFi.begin(SSID, PASSWORD);
            delay(500);
        }
    
        Serial.println("Connected!");
    }
    ```
  
    ಸಾಧನವು WiFi ಗೆ ಸಂಪರ್ಕ ಇಲ್ಲದಂತೆ ಇದ್ದಾಗ ಈ ಕೋಡ್ ಲೂಪ್ ಮಾಡಿ, config ಹೆಡರ್ ಫೈಲ್‌ನಿಂದ ಪಡೆಯುವ SSID ಮತ್ತು ಪಾಸ್ವರ್ಡ್ ಬಳಸಿ ಸಂಪರ್ಕಿಸಲು ಪ್ರಯತ್ನಿಸುತ್ತದೆ.

1. `setup` ಫಂಕ್ಷನ್‌ನ ಕೊನೆಯಲ್ಲಿ, ಪಿನ್‌ಗಳು ಸಂರಚನೆಯಾದ ಬಳಿಕ, ಈ ಕಾರ್ಯವಿಧಾನಕ್ಕೆ ಕರೆ ಮಾಡಿ.

    ```cpp
    connectWiFi();
    ```
  
1. WiFi ಸಂಪರ್ಕ ಕಾರ್ಯನಿರ್ವಹಿಸುತ್ತಿದೆಯೇ ಎಂದು ಪರಿಶೀಲಿಸಲು ಈ ಕೋಡ್ ಅನ್ನು ನಿಮ್ಮ ಸಾಧನಕ್ಕೆ ಅಪ್‌ಲೋಡ್ ಮಾಡಿ. ಅದನ್ನು ಸೀರಿಯಲ್ ಮಾನಿಟರ್‌ನಲ್ಲಿ ನೋಡಬಹುದು.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```
  
## MQTT ಗೆ ಸಂಪರ್ಕ ಮಾಡಿರಿ

ಒಮ್ಮೆ Wio ಟರ್ಮಿನಲ್ WiFi ಗೆ ಸಂಪರ್ಕಾದ ಮೇಲೆ, ಅದು MQTT ಬ್ರೋಕರ್‌ಗೂ ಸಂಪರ್ಕಿಸಬಹುದು.

### ಕಾರ್ಯ - MQTT ಗೆ ಸಂಪರ್ಕ ಮಾಡಿರಿ

MQTT ಬ್ರೋಕರ್‌ಗೆ ಸಂಪರ್ಕಿಸಿರಿ.

1. `config.h` ಫೈಲ್‌ನ ಕೊನೆಯಲ್ಲಿ ಕೆಳಗಿನ ಕೋಡ್ ಸೇರಿಸಿ, MQTT ಬ್ರೋಕರ್ ಸಂಪರ್ಕ ವಿವರಗಳನ್ನು ವ್ಯಾಖ್ಯಾನಿಸಲು:

    ```cpp
    // MQTT ಸೆಟ್ಟಿಂಗ್ಸ್
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```
  
    `<ID>` ಅನ್ನು ಈ ಸಾಧನ ಕ್ಲೈಂಟ್ ಹೆಸರಾಗಿ ಮತ್ತು ನಂತರ ಈ ಸಾಧನ ಪ್ರಕಟಿಸುವ ಮತ್ತು ಸಬ್ಸ್‌ಕ್ರಮ್ ಮಾಡುವ ವಿಷಯಗಳಿಗಾಗಿ ಬಳಸಲಾಗುವ ವಿಶಿಷ್ಟ ID ಯಿಂದ ಬದಲಾಯಿಸಿ. *test.mosquitto.org* ಬ್ರೋಕರ್ ಪಬ್ಲಿಕ್ ಆಗಿದ್ದು ಹಲವು ಜನರು, ಇತರ ವಿದ್ಯಾರ್ಥಿಗಳೂ ಈ ಕಾರ್ಯಮಟ್ಟವು ನಡೆಸುತ್ತಿರುವವರಿಗೆ ಬಳಸಲಾಗುತ್ತದೆ. ವಿಶಿಷ್ಟ MQTT ಕ್ಲೈಂಟ್ ಮತ್ತು ವಿಷಯ ಹೆಸರುಗಳಿರುವ ಮೂಲಕ ನಿಮ್ಮ ಕೋಡ್ ಇತರ ಯಾರು ಹೊಂದಿರುವವರೊಂದಿಗೆ ಜೋಡಣೆಯಾಗದಂತೆ ನೋಡಿಕೊಳ್ಳಬಹುದು. ಈ ID ಅನ್ನು ಈ ಟಾಸ್ಕ್‌ನ ಮುಂದಿನ ಹಂತದಲ್ಲಿ ಸರ್ವರ್ ಕೋಡ್ ರಚಿಸುವಾಗ ಸಹ ಅಗತ್ಯವಿರುತ್ತದೆ.

    > 💁 ನೀವು [GUIDGen](https://www.guidgen.com) ಅಥವಾ ಇಂತಹ ವೆಬ್ಸೈಟ್ ಉಪಯೋಗಿಸಿ ವಿಶಿಷ್ಟ ID ತಯಾರಿಸಬಹುದು.

    `BROKER` ಎನ್‌ಪಾಯಿಂಟ್ URL ಆಗಿದೆ.

    `CLIENT_NAME` ಈ MQTT ಕ್ಲೈಂಟ್‌ಗೆ ಬ್ರೋಕರ್‌ನಲ್ಲಿ ವಿಶಿಷ್ಟ ಹೆಸರು.

1. `main.cpp` ಫೈಲ್ ತೆರೆಯಿರಿ ಮತ್ತು `connectWiFi` ಕಾರ್ಯವಿಧಾನದ ಕೆಳಗೆ ಮತ್ತು `setup` ಕಾರ್ಯಗತಗೊಳಿಸಲಾಗುವ ಮೇಲೆ ಕೆಳಗಿನ ಕೋಡ್ ಸೇರಿಸಿ:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```
  
    ಇದು Wio ಟರ್ಮಿನಲ್ WiFi ಗ್ರಂಥಾಲಯಗಳು ಬಳಸಿ WiFi ಕ್ಲೈಂಟ್ ಮತ್ತು ಅದನ್ನು ಬಳಸಿ MQTT ಕ್ಲೈಂಟ್ ಸೃಷ್ಟಿಸುತ್ತದೆ.

1. ಈ ಕೋಡ್ ಕೆಳಗೆ, ಕೆಳಗಿನ ವಿಷಯ ಸೇರಿಸಿ:

    ```cpp
    void reconnectMQTTClient()
    {
        while (!client.connected())
        {
            Serial.print("Attempting MQTT connection...");
    
            if (client.connect(CLIENT_NAME.c_str()))
            {
                Serial.println("connected");
            }
            else
            {
                Serial.print("Retying in 5 seconds - failed, rc=");
                Serial.println(client.state());
                
                delay(5000);
            }
        }
    }
    ```
  
    ಈ ಕಾರ್ಯವು MQTT ಬ್ರೋಕರ್ ಸಂಪರ್ಕವನ್ನು ಪರೀಕ್ಷಿಸುತ್ತದೆ ಮತ್ತು ಸಂಪರ್ಕ ಇಲ್ಲದಿದ್ದರೆ ಪುನಃ ಸಂಪರ್ಕಿಸುವ ಪ್ರಯತ್ನ ಮಾಡುತ್ತದೆ. ಇದು ಸಂಪರ್ಕ ಇಲ್ಲದವರೆಗೂ ಲೂಪ್ ಮಾಡುತ್ತದೆ ಮತ್ತು config ಹೆಡರ್ ಫೈಲ್‌ನಲ್ಲಿ ವ್ಯಾಖ್ಯಾನಿಸಿದ ವಿಶಿಷ್ಟ ಕ್ಲೈಂಟ್ ಹೆಸರನ್ನು ಬಳಸಿ ಸಂಪರ್ಕಿಸಲು ಪ್ರಯತ್ನಿಸುತ್ತದೆ.

    ಸಂಪರ್ಕ ವಿಫಲವಾದರೆ, 5 ಸೆಕೆಂಡುಗಳ ನಂತರ ಪುನಃ ಪ್ರಯತ್ನಿಸುತ್ತದೆ.

1. `reconnectMQTTClient` ಫಂಕ್ಷನ್ ಕೆಳಗೇ ಈ ಕೋಡ್ ಸೇರಿಸಿ:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```
  
    ಈ ಕೋಡ್ MQTT ಬ್ರೋಕರ್‌ಗಾಗಿ ಕ್ಲೈಂಟ್ ಅನ್ನು ಹೊಂದಿಸಿ, ಸಂದೇಶ ಬಂದಾಗ ಕರೆಮಾಡುವ ಫಂಕ್ಷನ್ ಹೊಂದಿಸಿ, ನಂತರ ಬ್ರೋಕರಿಗೆ ಸಂಪರ್ಕ ಮಾಡಲು ಪ್ರಯತ್ನಿಸುತ್ತದೆ.

1. WiFi ಸಂಪರ್ಕವಾದ ನಂತರ `setup` ಫಂಕ್ಷನ್‌ನಲ್ಲಿ `createMQTTClient` ಕಾರ್ಯವಿದ್ಯಾನವನ್ನೇ ಕರೆ ಮಾಡಿ.

1. ಸಂಪೂರ್ಣ `loop` ಕಾರ್ಯವನ್ನು ಕೆಳಗಿನಂತೆ ಬದಲಾಯಿಸಿ:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```
  
    ಈ ಕೋಡ್ MQTT ಬ್ರೋಕರ್‌ಗೆ ಪುನಃ ಸಂಪರ್ಕಿಸುವುದರೊಂದಿಗೆ ಪ್ರಾರಂಭವಾಗುತ್ತದೆ. ಇವುಗಳ ಸಂಪರ್ಕಗಳು ಸುಲಭವಾಗಿ ಮುರಿದುಹೋಗಬಹುದು, ಆದ್ದರಿಂದ ನಿಯಮಿತವಾಗಿ ಪರಿಶೀಲಿಸಿ ಪುನಃ ಸಂಪರ್ಕಿಸಲು ಅಗತ್ಯ. ನಂತರ MQTT ಕ್ಲೈಂಟ್‌ನ `loop` ವಿಧಾನವನ್ನು ಕರೆ ಮಾಡಿ, ಇದು ಸಬ್ಸ್ಕ್ರೈಬ್ ಮಾಡಿದ ವಿಷಯಕ್ಕೆ ಬರುತ್ತಿರುವ ಎಲ್ಲ ಸಂದೇಶಗಳನ್ನು ಪ್ರಕ್ರಿಯೆ ಮಾಡುತ್ತದೆ. ಈ ಆಪ್ ಸಿಂಗಲ್-ಥ್ರೆಡ್ ಆಗಿದೆ, ಆದ್ದರಿಂದ ಸಂದೇಶಗಳನ್ನು ಯಾವುದೇ ಬ್ಯಾಕ್ಗ್ರೌಂಡ್ ತಂತಿಯಲ್ಲಿ ಸ್ವೀಕರಿಸಲಾಗುವುದಿಲ್ಲ, ಹಾಗಾಗಿ ಮುಖ್ಯ ತಂತಿಗೆ ಸಂಪರ್ಕದಿಂದ ಬಂದ ಯಾವುದೇ ಮೆಸೇಜುಗಳನ್ನು ಪ್ರಕ್ರಿಯೆ ಮಾಡಲು ಸಮಯ ನೀಡಬೇಕು.

    ಕೊನೆಗೆ, 2 ಸೆಕೆಂಡಿನ ವಿಳಂಬವು ಬೆಳಕು ಮಟ್ಟಗಳನ್ನು ಹೆಚ್ಚು ಬಾರಿ ಕಳುಹಿಸುವುದನ್ನು ತಡೆದು ಸಾಧನ ಶಕ್ತಿಣ್ವಯವನ್ನು ಕಡಿಮೆ ಮಾಡುತ್ತದೆ.

1. ಈ ಕೋಡ್‌ನ್ನು ನಿಮ್ಮ Wio ಟರ್ಮಿನಲ್‌ಗೆ ಅಪ್‌ಲೋಡ್ ಮಾಡಿ ಮತ್ತು ಸೀರಿಯಲ್ ಮಾನಿಟರ್ ಬಳಸಿ ಸಾಧನವು WiFi ಮತ್ತು MQTT ಗೆ ಸಂಪರ್ಕವಾಗುತ್ತಿರುವುದನ್ನು ನೋಡಿ.

    ```output
    > Executing task: platformio device monitor <
    
    source /Users/jimbennett/GitHub/IoT-For-Beginners/1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal/nightlight/.venv/bin/activate
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    ```
  
> 💁 ನೀವು ಈ ಕೋಡ್ ಅನ್ನು [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal) ಫೋಲ್ಡರ್‌ನಲ್ಲಿ ಕಾಣಬಹುದು.

😀 ನೀವು ಯಶಸ್ವಿಯಾಗಿ ನಿಮ್ಮ ಸಾಧನವನ್ನು MQTT ಬ್ರೋಕರ್‌ಗೆ ಸಂಪರ್ಕಿಸಿದ್ದಾರೆ.

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ಅನುವಾದ ನಿರಾಕರಣೆ**:  
ಈ ದಾಖಲೆ [Co-op Translator](https://github.com/Azure/co-op-translator) ಎಂಬ AI ಅನುವಾದ ಸೇವೆಯನ್ನು ಬಳಸಿಕೊಂಡು ಅನುವಾದಿಸಲಾಗಿದೆ. ನಾವು ಸರಿಯಾಗಿರುವುದಕ್ಕೆ ಪ್ರಯತ್ನಿಸುವುದಾಗಿದ್ದರೂ, ಸ್ವಯಂಚಾಲಿತ ಅನುವಾದಗಳಲ್ಲಿ ತಪ್ಪುಗಳು ಅಥವಾ ಅಸಮಗ್ರತೆಗಳು ಇರಬಹುದು ಎಂದು ದಯವಿಟ್ಟು ಗಮನಿಸಿ. ಮೂಲ ಭಾಷೆಯಲ್ಲಿರುವ ದಾಖಲೆಯನ್ನು ಅಧೀನ ಮೂಲವೆಂದು ಪರಿಗಣಿಸಬೇಕು. ಮಹತ್ವದ ಮಾಹಿತಿಗಾಗಿ ವೃತ್ತಿಪರ ಮಾನವ ಅನುವಾದವನ್ನು ಸಲಹೆ ಮಾಡಲಾಗುತ್ತದೆ. ಈ ಅನುವಾದ ಬಳಕೆಯಿಂದ ಉಂಟಾಗುವ ಯಾವುದೇ ತೊಂದರೆಗಳು ಅಥವಾ ತಪ್ಪು ಅಗತ್ಯಕ್ಕಾಗಿ ನಾವು ಹೊಣೆಗಾರರಲ್ಲ.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->