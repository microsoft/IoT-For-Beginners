<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-27T12:34:10+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "pa"
}
-->
# ਇੰਟਰਨੈਟ ਰਾਹੀਂ ਆਪਣੀ ਨਾਈਟਲਾਈਟ ਨੂੰ ਕੰਟਰੋਲ ਕਰੋ - Wio Terminal

IoT ਡਿਵਾਈਸ ਨੂੰ *test.mosquitto.org* ਨਾਲ MQTT ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਸੰਚਾਰ ਕਰਨ ਲਈ ਕੋਡ ਕੀਤਾ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ, ਤਾਂ ਜੋ ਲਾਈਟ ਸੈਂਸਰ ਦੀ ਰੀਡਿੰਗ ਨਾਲ ਟੈਲੀਮੀਟਰੀ ਮੁੱਲ ਭੇਜੇ ਜਾ ਸਕਣ ਅਤੇ LED ਨੂੰ ਕੰਟਰੋਲ ਕਰਨ ਲਈ ਕਮਾਂਡ ਪ੍ਰਾਪਤ ਕੀਤੀਆਂ ਜਾ ਸਕਣ।

ਇਸ ਪਾਠ ਦੇ ਇਸ ਭਾਗ ਵਿੱਚ, ਤੁਸੀਂ ਆਪਣੇ Wio Terminal ਨੂੰ ਇੱਕ MQTT ਬ੍ਰੋਕਰ ਨਾਲ ਕਨੈਕਟ ਕਰੋਗੇ।

## WiFi ਅਤੇ MQTT Arduino ਲਾਇਬ੍ਰੇਰੀਆਂ ਇੰਸਟਾਲ ਕਰੋ

MQTT ਬ੍ਰੋਕਰ ਨਾਲ ਸੰਚਾਰ ਕਰਨ ਲਈ, ਤੁਹਾਨੂੰ ਕੁਝ Arduino ਲਾਇਬ੍ਰੇਰੀਆਂ ਇੰਸਟਾਲ ਕਰਨ ਦੀ ਲੋੜ ਹੈ, ਤਾਂ ਜੋ Wio Terminal ਵਿੱਚ WiFi ਚਿਪ ਦੀ ਵਰਤੋਂ ਕੀਤੀ ਜਾ ਸਕੇ ਅਤੇ MQTT ਨਾਲ ਸੰਚਾਰ ਕੀਤਾ ਜਾ ਸਕੇ। ਜਦੋਂ Arduino ਡਿਵਾਈਸਾਂ ਲਈ ਵਿਕਾਸ ਕੀਤਾ ਜਾਂਦਾ ਹੈ, ਤਾਂ ਤੁਸੀਂ ਖੁੱਲ੍ਹੇ ਸਰੋਤ ਕੋਡ ਵਾਲੀਆਂ ਅਤੇ ਵੱਖ-ਵੱਖ ਸਮਰੱਥਾਵਾਂ ਨੂੰ ਲਾਗੂ ਕਰਨ ਵਾਲੀਆਂ ਲਾਇਬ੍ਰੇਰੀਆਂ ਦੀ ਇੱਕ ਵੱਡੀ ਰੇਂਜ ਦੀ ਵਰਤੋਂ ਕਰ ਸਕਦੇ ਹੋ। Seeed Wio Terminal ਲਈ ਲਾਇਬ੍ਰੇਰੀਆਂ ਪ੍ਰਕਾਸ਼ਿਤ ਕਰਦਾ ਹੈ ਜੋ ਇਸਨੂੰ WiFi ਰਾਹੀਂ ਸੰਚਾਰ ਕਰਨ ਦੀ ਆਗਿਆ ਦਿੰਦੀ ਹੈ। ਹੋਰ ਵਿਕਾਸਕਾਰਾਂ ਨੇ MQTT ਬ੍ਰੋਕਰਾਂ ਨਾਲ ਸੰਚਾਰ ਕਰਨ ਲਈ ਲਾਇਬ੍ਰੇਰੀਆਂ ਪ੍ਰਕਾਸ਼ਿਤ ਕੀਤੀਆਂ ਹਨ, ਅਤੇ ਤੁਸੀਂ ਆਪਣੇ ਡਿਵਾਈਸ ਨਾਲ ਇਨ੍ਹਾਂ ਦੀ ਵਰਤੋਂ ਕਰੋਗੇ।

ਇਹ ਲਾਇਬ੍ਰੇਰੀਆਂ ਸਰੋਤ ਕੋਡ ਦੇ ਰੂਪ ਵਿੱਚ ਪ੍ਰਦਾਨ ਕੀਤੀਆਂ ਜਾਂਦੀਆਂ ਹਨ, ਜਿਨ੍ਹਾਂ ਨੂੰ PlatformIO ਵਿੱਚ ਆਟੋਮੈਟਿਕ ਤੌਰ 'ਤੇ ਇੰਪੋਰਟ ਕੀਤਾ ਜਾ ਸਕਦਾ ਹੈ ਅਤੇ ਤੁਹਾਡੇ ਡਿਵਾਈਸ ਲਈ ਕੰਪਾਇਲ ਕੀਤਾ ਜਾ ਸਕਦਾ ਹੈ। ਇਸ ਤਰੀਕੇ ਨਾਲ Arduino ਲਾਇਬ੍ਰੇਰੀਆਂ ਕਿਸੇ ਵੀ ਡਿਵਾਈਸ 'ਤੇ ਕੰਮ ਕਰਨਗੀਆਂ ਜੋ Arduino ਫਰੇਮਵਰਕ ਦਾ ਸਮਰਥਨ ਕਰਦਾ ਹੈ, ਜੇਕਰ ਉਸ ਡਿਵਾਈਸ ਵਿੱਚ ਉਸ ਲਾਇਬ੍ਰੇਰੀ ਦੁਆਰਾ ਲੋੜੀਂਦਾ ਵਿਸ਼ੇਸ਼ ਹਾਰਡਵੇਅਰ ਹੈ। ਕੁਝ ਲਾਇਬ੍ਰੇਰੀਆਂ, ਜਿਵੇਂ ਕਿ Seeed WiFi ਲਾਇਬ੍ਰੇਰੀਆਂ, ਖਾਸ ਹਾਰਡਵੇਅਰ ਲਈ ਵਿਸ਼ੇਸ਼ ਹੁੰਦੀਆਂ ਹਨ।

ਲਾਇਬ੍ਰੇਰੀਆਂ ਨੂੰ ਗਲੋਬਲ ਤੌਰ 'ਤੇ ਇੰਸਟਾਲ ਕੀਤਾ ਜਾ ਸਕਦਾ ਹੈ ਅਤੇ ਜਰੂਰਤ ਪੈਣ 'ਤੇ ਕੰਪਾਇਲ ਕੀਤਾ ਜਾ ਸਕਦਾ ਹੈ, ਜਾਂ ਕਿਸੇ ਖਾਸ ਪ੍ਰੋਜੈਕਟ ਵਿੱਚ। ਇਸ ਅਸਾਈਨਮੈਂਟ ਲਈ, ਲਾਇਬ੍ਰੇਰੀਆਂ ਨੂੰ ਪ੍ਰੋਜੈਕਟ ਵਿੱਚ ਇੰਸਟਾਲ ਕੀਤਾ ਜਾਵੇਗਾ।

✅ ਤੁਸੀਂ ਲਾਇਬ੍ਰੇਰੀ ਪ੍ਰਬੰਧਨ ਅਤੇ ਲਾਇਬ੍ਰੇਰੀਆਂ ਨੂੰ ਖੋਜਣ ਅਤੇ ਇੰਸਟਾਲ ਕਰਨ ਬਾਰੇ ਹੋਰ ਜਾਣਕਾਰੀ [PlatformIO ਲਾਇਬ੍ਰੇਰੀ ਡੌਕਯੂਮੈਂਟੇਸ਼ਨ](https://docs.platformio.org/en/latest/librarymanager/index.html) ਵਿੱਚ ਪ੍ਰਾਪਤ ਕਰ ਸਕਦੇ ਹੋ।

### ਕੰਮ - WiFi ਅਤੇ MQTT Arduino ਲਾਇਬ੍ਰੇਰੀਆਂ ਇੰਸਟਾਲ ਕਰੋ

Arduino ਲਾਇਬ੍ਰੇਰੀਆਂ ਇੰਸਟਾਲ ਕਰੋ।

1. VS Code ਵਿੱਚ ਨਾਈਟਲਾਈਟ ਪ੍ਰੋਜੈਕਟ ਖੋਲ੍ਹੋ।

1. `platformio.ini` ਫਾਈਲ ਦੇ ਅੰਤ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤਾ ਗਇਆ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    ਇਹ Seeed WiFi ਲਾਇਬ੍ਰੇਰੀਆਂ ਨੂੰ ਇੰਪੋਰਟ ਕਰਦਾ ਹੈ। `@ <number>` ਸਿੰਟੈਕਸ ਲਾਇਬ੍ਰੇਰੀ ਦੇ ਖਾਸ ਵਰਜਨ ਨੰਬਰ ਨੂੰ ਦਰਸਾਉਂਦਾ ਹੈ।

    > 💁 ਤੁਸੀਂ ਹਮੇਸ਼ਾ ਲਾਇਬ੍ਰੇਰੀਆਂ ਦੇ ਨਵੇਂਤਮ ਵਰਜਨ ਦੀ ਵਰਤੋਂ ਕਰਨ ਲਈ `@ <number>` ਨੂੰ ਹਟਾ ਸਕਦੇ ਹੋ, ਪਰ ਇਸ ਗੱਲ ਦੀ ਕੋਈ ਗਾਰੰਟੀ ਨਹੀਂ ਹੈ ਕਿ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਬਾਅਦ ਦੇ ਵਰਜਨਾਂ ਨਾਲ ਕੰਮ ਕਰੇਗਾ। ਇੱਥੇ ਦਿੱਤਾ ਕੋਡ ਇਸ ਵਰਜਨ ਨਾਲ ਟੈਸਟ ਕੀਤਾ ਗਿਆ ਹੈ।

    ਇਹ ਲਾਇਬ੍ਰੇਰੀਆਂ ਸ਼ਾਮਲ ਕਰਨ ਲਈ ਤੁਹਾਨੂੰ ਸਿਰਫ ਇਹੀ ਕਰਨ ਦੀ ਲੋੜ ਹੈ। ਜਦੋਂ ਅਗਲੀ ਵਾਰ PlatformIO ਪ੍ਰੋਜੈਕਟ ਨੂੰ ਬਣਾਉਂਦਾ ਹੈ, ਤਾਂ ਇਹ ਲਾਇਬ੍ਰੇਰੀਆਂ ਲਈ ਸਰੋਤ ਕੋਡ ਡਾਊਨਲੋਡ ਕਰੇਗਾ ਅਤੇ ਇਸਨੂੰ ਤੁਹਾਡੇ ਪ੍ਰੋਜੈਕਟ ਵਿੱਚ ਕੰਪਾਇਲ ਕਰੇਗਾ।

1. `lib_deps` ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤਾ ਸ਼ਾਮਲ ਕਰੋ:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    ਇਹ [PubSubClient](https://github.com/knolleary/pubsubclient), ਇੱਕ Arduino MQTT ਕਲਾਇੰਟ ਨੂੰ ਇੰਪੋਰਟ ਕਰਦਾ ਹੈ।

## WiFi ਨਾਲ ਕਨੈਕਟ ਕਰੋ

ਹੁਣ Wio Terminal ਨੂੰ WiFi ਨਾਲ ਕਨੈਕਟ ਕੀਤਾ ਜਾ ਸਕਦਾ ਹੈ।

### ਕੰਮ - WiFi ਨਾਲ ਕਨੈਕਟ ਕਰੋ

Wio Terminal ਨੂੰ WiFi ਨਾਲ ਕਨੈਕਟ ਕਰੋ।

1. `src` ਫੋਲਡਰ ਵਿੱਚ ਇੱਕ ਨਵੀਂ ਫਾਈਲ ਬਣਾਓ ਜਿਸਦਾ ਨਾਮ `config.h` ਰੱਖੋ। ਤੁਸੀਂ ਇਹ `src` ਫੋਲਡਰ ਜਾਂ `main.cpp` ਫਾਈਲ ਨੂੰ ਚੁਣ ਕੇ ਅਤੇ ਐਕਸਪਲੋਰਰ ਵਿੱਚ **ਨਵੀਂ ਫਾਈਲ** ਬਟਨ ਚੁਣ ਕੇ ਕਰ ਸਕਦੇ ਹੋ। ਇਹ ਬਟਨ ਸਿਰਫ਼ ਉਸ ਸਮੇਂ ਦਿਖਾਈ ਦਿੰਦਾ ਹੈ ਜਦੋਂ ਤੁਹਾਡਾ ਕਰਸਰ ਐਕਸਪਲੋਰਰ 'ਤੇ ਹੁੰਦਾ ਹੈ।

    ![ਨਵੀਂ ਫਾਈਲ ਬਟਨ](../../../../../translated_images/pa/vscode-new-file-button.182702340fe6723c.png)

1. ਇਸ ਫਾਈਲ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ, ਤਾਂ ਜੋ ਤੁਹਾਡੇ WiFi ਕ੍ਰੈਡੈਂਸ਼ਲ ਲਈ ਕਾਂਸਟੈਂਟਸ ਨੂੰ ਪਰਿਭਾਸ਼ਿਤ ਕੀਤਾ ਜਾ ਸਕੇ:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    `<SSID>` ਨੂੰ ਆਪਣੇ WiFi ਦੇ SSID ਨਾਲ ਬਦਲੋ। `<PASSWORD>` ਨੂੰ ਆਪਣੇ WiFi ਪਾਸਵਰਡ ਨਾਲ ਬਦਲੋ।

1. `main.cpp` ਫਾਈਲ ਖੋਲ੍ਹੋ।

1. ਫਾਈਲ ਦੇ ਉੱਪਰ ਹੇਠਾਂ ਦਿੱਤੇ `#include` ਨਿਰਦੇਸ਼ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    ਇਹ ਉਹ ਹੈਡਰ ਫਾਈਲਾਂ ਸ਼ਾਮਲ ਕਰਦਾ ਹੈ ਜੋ ਤੁਸੀਂ ਪਹਿਲਾਂ ਸ਼ਾਮਲ ਕੀਤੀਆਂ ਲਾਇਬ੍ਰੇਰੀਆਂ ਲਈ ਹਨ, ਨਾਲ ਹੀ ਕਨਫਿਗ ਹੈਡਰ ਫਾਈਲ। ਇਹ ਹੈਡਰ ਫਾਈਲਾਂ ਲੋੜੀਂਦੀਆਂ ਹਨ ਤਾਂ ਜੋ PlatformIO ਨੂੰ ਲਾਇਬ੍ਰੇਰੀਆਂ ਤੋਂ ਕੋਡ ਲਿਆਉਣ ਲਈ ਕਿਹਾ ਜਾ ਸਕੇ। ਇਹ ਹੈਡਰ ਫਾਈਲਾਂ ਸਪਸ਼ਟ ਤੌਰ 'ਤੇ ਸ਼ਾਮਲ ਕੀਤੀਆਂ ਬਿਨਾਂ, ਕੁਝ ਕੋਡ ਕੰਪਾਇਲ ਨਹੀਂ ਕੀਤਾ ਜਾਵੇਗਾ ਅਤੇ ਤੁਹਾਨੂੰ ਕੰਪਾਇਲਰ ਐਰਰ ਮਿਲਣਗੇ।

1. `setup` ਫੰਕਸ਼ਨ ਤੋਂ ਉੱਪਰ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

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

    ਇਹ ਕੋਡ ਉਸ ਸਮੇਂ ਤੱਕ ਲੂਪ ਕਰਦਾ ਹੈ ਜਦੋਂ ਤੱਕ ਡਿਵਾਈਸ WiFi ਨਾਲ ਕਨੈਕਟ ਨਹੀਂ ਹੁੰਦਾ, ਅਤੇ ਕਨਫਿਗ ਹੈਡਰ ਫਾਈਲ ਤੋਂ SSID ਅਤੇ ਪਾਸਵਰਡ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਕਨੈਕਟ ਕਰਨ ਦੀ ਕੋਸ਼ਿਸ਼ ਕਰਦਾ ਹੈ।

1. ਇਸ ਫੰਕਸ਼ਨ ਨੂੰ `setup` ਫੰਕਸ਼ਨ ਦੇ ਤਲ 'ਤੇ ਕਾਲ ਕਰੋ, ਪਿੰਸ ਨੂੰ ਕਨਫਿਗਰ ਕਰਨ ਤੋਂ ਬਾਅਦ।

    ```cpp
    connectWiFi();
    ```

1. ਇਸ ਕੋਡ ਨੂੰ ਆਪਣੇ ਡਿਵਾਈਸ 'ਤੇ ਅੱਪਲੋਡ ਕਰੋ, ਤਾਂ ਜੋ WiFi ਕਨੈਕਸ਼ਨ ਚੈੱਕ ਕੀਤਾ ਜਾ ਸਕੇ। ਤੁਸੀਂ ਇਹ ਸੀਰੀਅਲ ਮਾਨੀਟਰ ਵਿੱਚ ਦੇਖ ਸਕਦੇ ਹੋ।

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## MQTT ਨਾਲ ਕਨੈਕਟ ਕਰੋ

ਜਦੋਂ Wio Terminal WiFi ਨਾਲ ਕਨੈਕਟ ਹੋ ਜਾਂਦਾ ਹੈ, ਤਾਂ ਇਹ MQTT ਬ੍ਰੋਕਰ ਨਾਲ ਕਨੈਕਟ ਹੋ ਸਕਦਾ ਹੈ।

### ਕੰਮ - MQTT ਨਾਲ ਕਨੈਕਟ ਕਰੋ

MQTT ਬ੍ਰੋਕਰ ਨਾਲ ਕਨੈਕਟ ਕਰੋ।

1. `config.h` ਫਾਈਲ ਦੇ ਤਲ 'ਤੇ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ, ਤਾਂ ਜੋ MQTT ਬ੍ਰੋਕਰ ਲਈ ਕਨੈਕਸ਼ਨ ਵੇਰਵੇ ਪਰਿਭਾਸ਼ਿਤ ਕੀਤੇ ਜਾ ਸਕਣ:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    `<ID>` ਨੂੰ ਇੱਕ ਵਿਲੱਖਣ ID ਨਾਲ ਬਦਲੋ ਜੋ ਇਸ ਡਿਵਾਈਸ ਕਲਾਇੰਟ ਦੇ ਨਾਮ ਵਜੋਂ ਵਰਤੀ ਜਾਵੇਗੀ, ਅਤੇ ਬਾਅਦ ਵਿੱਚ ਉਹ ਵਿਸ਼ਿਆਂ ਲਈ ਜੋ ਇਹ ਡਿਵਾਈਸ ਪ੍ਰਕਾਸ਼ਿਤ ਅਤੇ ਸਬਸਕ੍ਰਾਈਬ ਕਰਦਾ ਹੈ। *test.mosquitto.org* ਬ੍ਰੋਕਰ ਜਨਤਕ ਹੈ ਅਤੇ ਕਈ ਲੋਕਾਂ ਦੁਆਰਾ ਵਰਤਿਆ ਜਾਂਦਾ ਹੈ, ਜਿਸ ਵਿੱਚ ਇਸ ਅਸਾਈਨਮੈਂਟ 'ਤੇ ਕੰਮ ਕਰ ਰਹੇ ਹੋਰ ਵਿਦਿਆਰਥੀ ਵੀ ਸ਼ਾਮਲ ਹਨ। ਇੱਕ ਵਿਲੱਖਣ MQTT ਕਲਾਇੰਟ ਨਾਮ ਅਤੇ ਵਿਸ਼ਿਆਂ ਦੇ ਨਾਮ ਇਹ ਯਕੀਨੀ ਬਣਾਉਂਦੇ ਹਨ ਕਿ ਤੁਹਾਡਾ ਕੋਡ ਕਿਸੇ ਹੋਰ ਦੇ ਨਾਲ ਟਕਰਾਏਗਾ ਨਹੀਂ। ਤੁਹਾਨੂੰ ਇਹ ID ਇਸ ਅਸਾਈਨਮੈਂਟ ਵਿੱਚ ਬਾਅਦ ਵਿੱਚ ਸਰਵਰ ਕੋਡ ਬਣਾਉਂਦੇ ਸਮੇਂ ਵੀ ਲੋੜੀਂਦੀ ਹੋਵੇਗੀ।

    > 💁 ਤੁਸੀਂ [GUIDGen](https://www.guidgen.com) ਵਰਗੇ ਵੈਬਸਾਈਟ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਇੱਕ ਵਿਲੱਖਣ ID ਤਿਆਰ ਕਰ ਸਕਦੇ ਹੋ।

    `BROKER` MQTT ਬ੍ਰੋਕਰ ਦਾ URL ਹੈ।

    `CLIENT_NAME` ਇਸ MQTT ਕਲਾਇੰਟ ਲਈ ਬ੍ਰੋਕਰ 'ਤੇ ਇੱਕ ਵਿਲੱਖਣ ਨਾਮ ਹੈ।

1. `main.cpp` ਫਾਈਲ ਖੋਲ੍ਹੋ, ਅਤੇ `connectWiFi` ਫੰਕਸ਼ਨ ਤੋਂ ਹੇਠਾਂ ਅਤੇ `setup` ਫੰਕਸ਼ਨ ਤੋਂ ਉੱਪਰ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    ਇਹ ਕੋਡ Wio Terminal WiFi ਲਾਇਬ੍ਰੇਰੀਆਂ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਇੱਕ WiFi ਕਲਾਇੰਟ ਬਣਾਉਂਦਾ ਹੈ ਅਤੇ ਇਸਨੂੰ ਵਰਤ ਕੇ ਇੱਕ MQTT ਕਲਾਇੰਟ ਬਣਾਉਂਦਾ ਹੈ।

1. ਇਸ ਕੋਡ ਦੇ ਹੇਠਾਂ ਹੇਠਾਂ ਦਿੱਤਾ ਸ਼ਾਮਲ ਕਰੋ:

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

    ਇਹ ਫੰਕਸ਼ਨ MQTT ਬ੍ਰੋਕਰ ਨਾਲ ਕਨੈਕਸ਼ਨ ਦੀ ਜਾਂਚ ਕਰਦਾ ਹੈ ਅਤੇ ਜੇਕਰ ਇਹ ਕਨੈਕਟ ਨਹੀਂ ਹੈ ਤਾਂ ਦੁਬਾਰਾ ਕਨੈਕਟ ਕਰਦਾ ਹੈ। ਇਹ ਉਸ ਸਮੇਂ ਤੱਕ ਲੂਪ ਕਰਦਾ ਹੈ ਜਦੋਂ ਤੱਕ ਇਹ ਕਨੈਕਟ ਨਹੀਂ ਹੁੰਦਾ ਅਤੇ ਕਨਫਿਗ ਹੈਡਰ ਫਾਈਲ ਵਿੱਚ ਪਰਿਭਾਸ਼ਿਤ ਵਿਲੱਖਣ ਕਲਾਇੰਟ ਨਾਮ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਕਨੈਕਟ ਕਰਨ ਦੀ ਕੋਸ਼ਿਸ਼ ਕਰਦਾ ਹੈ।

    ਜੇਕਰ ਕਨੈਕਸ਼ਨ ਫੇਲ ਹੋ ਜਾਂਦਾ ਹੈ, ਤਾਂ ਇਹ 5 ਸਕਿੰਟ ਬਾਅਦ ਦੁਬਾਰਾ ਕੋਸ਼ਿਸ਼ ਕਰਦਾ ਹੈ।

1. `reconnectMQTTClient` ਫੰਕਸ਼ਨ ਦੇ ਹੇਠਾਂ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    ਇਹ ਕੋਡ ਕਲਾਇੰਟ ਲਈ MQTT ਬ੍ਰੋਕਰ ਸੈੱਟ ਕਰਦਾ ਹੈ, ਨਾਲ ਹੀ ਇੱਕ ਕਾਲਬੈਕ ਸੈੱਟ ਕਰਦਾ ਹੈ ਜਦੋਂ ਕੋਈ ਸੁਨੇਹਾ ਪ੍ਰਾਪਤ ਹੁੰਦਾ ਹੈ। ਫਿਰ ਇਹ ਬ੍ਰੋਕਰ ਨਾਲ ਕਨੈਕਟ ਕਰਨ ਦੀ ਕੋਸ਼ਿਸ਼ ਕਰਦਾ ਹੈ।

1. WiFi ਨਾਲ ਕਨੈਕਟ ਹੋਣ ਤੋਂ ਬਾਅਦ `setup` ਫੰਕਸ਼ਨ ਵਿੱਚ `createMQTTClient` ਫੰਕਸ਼ਨ ਨੂੰ ਕਾਲ ਕਰੋ।

1. ਪੂਰੇ `loop` ਫੰਕਸ਼ਨ ਨੂੰ ਹੇਠਾਂ ਦਿੱਤੇ ਨਾਲ ਬਦਲੋ:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    ਇਹ ਕੋਡ ਪਹਿਲਾਂ MQTT ਬ੍ਰੋਕਰ ਨਾਲ ਦੁਬਾਰਾ ਕਨੈਕਟ ਕਰਦਾ ਹੈ। ਇਹ ਕਨੈਕਸ਼ਨ ਆਸਾਨੀ ਨਾਲ ਟੁੱਟ ਸਕਦੇ ਹਨ, ਇਸ ਲਈ ਇਹ ਨਿਯਮਿਤ ਤੌਰ 'ਤੇ ਜਾਂਚ ਕਰਨ ਅਤੇ ਜਰੂਰਤ ਪੈਣ 'ਤੇ ਦੁਬਾਰਾ ਕਨੈਕਟ ਕਰਨ ਯੋਗ ਹੈ। ਫਿਰ ਇਹ MQTT ਕਲਾਇੰਟ 'ਤੇ `loop` ਵਿਧੀ ਨੂੰ ਕਾਲ ਕਰਦਾ ਹੈ, ਤਾਂ ਜੋ ਕਿਸੇ ਵੀ ਸੁਨੇਹੇ ਨੂੰ ਪ੍ਰਕਿਰਿਆਸ਼ੀਲ ਕੀਤਾ ਜਾ ਸਕੇ ਜੋ ਸਬਸਕ੍ਰਾਈਬ ਕੀਤੇ ਵਿਸ਼ੇ 'ਤੇ ਆ ਰਹੇ ਹਨ। ਇਹ ਐਪ ਸਿੰਗਲ-ਥ੍ਰੇਡਡ ਹੈ, ਇਸ ਲਈ ਸੁਨੇਹੇ ਬੈਕਗ੍ਰਾਊਂਡ ਥ੍ਰੇਡ 'ਤੇ ਪ੍ਰਾਪਤ ਨਹੀਂ ਕੀਤੇ ਜਾ ਸਕਦੇ, ਇਸ ਲਈ ਮੁੱਖ ਥ੍ਰੇਡ 'ਤੇ ਨੈੱਟਵਰਕ ਕਨੈਕਸ਼ਨ 'ਤੇ ਉਡੀਕ ਰਹੇ ਸੁਨੇਹਿਆਂ ਨੂੰ ਪ੍ਰਕਿਰਿਆਸ਼ੀਲ ਕਰਨ ਲਈ ਸਮਾਂ ਦਿੱਤਾ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ।

    ਆਖਰ ਵਿੱਚ, 2 ਸਕਿੰਟ ਦੀ ਦੇਰੀ ਇਹ ਯਕੀਨੀ ਬਣਾਉਂਦੀ ਹੈ ਕਿ ਲਾਈਟ ਲੈਵਲ ਬਹੁਤ ਜ਼ਿਆਦਾ ਵਾਰ ਨਹੀਂ ਭੇਜੇ ਜਾਂਦੇ ਅਤੇ ਡਿਵਾਈਸ ਦੀ ਪਾਵਰ ਖਪਤ ਘਟਦੀ ਹੈ।

1. ਆਪਣੇ Wio Terminal 'ਤੇ ਕੋਡ ਅੱਪਲੋਡ ਕਰੋ, ਅਤੇ ਡਿਵਾਈਸ ਨੂੰ WiFi ਅਤੇ MQTT ਨਾਲ ਕਨੈਕਟ ਹੁੰਦਾ ਦੇਖਣ ਲਈ ਸੀਰੀਅਲ ਮਾਨੀਟਰ ਦੀ ਵਰਤੋਂ ਕਰੋ।

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

> 💁 ਤੁਸੀਂ ਇਹ ਕੋਡ [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal) ਫੋਲਡਰ ਵਿੱਚ ਪ੍ਰਾਪਤ ਕਰ ਸਕਦੇ ਹੋ।

😀 ਤੁਸੀਂ ਸਫਲਤਾਪੂਰਵਕ ਆਪਣੇ ਡਿਵਾਈਸ ਨੂੰ ਇੱਕ MQTT ਬ੍ਰੋਕਰ ਨਾਲ ਕਨੈਕਟ ਕਰ ਲਿਆ ਹੈ।

---

**ਅਸਵੀਕਾਰਨਾ**:  
ਇਹ ਦਸਤਾਵੇਜ਼ AI ਅਨੁਵਾਦ ਸੇਵਾ [Co-op Translator](https://github.com/Azure/co-op-translator) ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅਨੁਵਾਦ ਕੀਤਾ ਗਿਆ ਹੈ। ਜਦੋਂ ਕਿ ਅਸੀਂ ਸਹੀਤਾ ਲਈ ਯਤਨਸ਼ੀਲ ਹਾਂ, ਕਿਰਪਾ ਕਰਕੇ ਧਿਆਨ ਦਿਓ ਕਿ ਸਵੈਚਾਲਿਤ ਅਨੁਵਾਦਾਂ ਵਿੱਚ ਗਲਤੀਆਂ ਜਾਂ ਅਸੁਚਨਾਵਾਂ ਹੋ ਸਕਦੀਆਂ ਹਨ। ਮੂਲ ਦਸਤਾਵੇਜ਼, ਜੋ ਇਸਦੀ ਮੂਲ ਭਾਸ਼ਾ ਵਿੱਚ ਹੈ, ਨੂੰ ਅਧਿਕਾਰਤ ਸਰੋਤ ਮੰਨਿਆ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ। ਮਹੱਤਵਪੂਰਨ ਜਾਣਕਾਰੀ ਲਈ, ਪੇਸ਼ੇਵਰ ਮਨੁੱਖੀ ਅਨੁਵਾਦ ਦੀ ਸਿਫਾਰਸ਼ ਕੀਤੀ ਜਾਂਦੀ ਹੈ। ਇਸ ਅਨੁਵਾਦ ਦੀ ਵਰਤੋਂ ਤੋਂ ਪੈਦਾ ਹੋਣ ਵਾਲੇ ਕਿਸੇ ਵੀ ਗਲਤਫਹਿਮੀ ਜਾਂ ਗਲਤ ਵਿਆਖਿਆ ਲਈ ਅਸੀਂ ਜ਼ਿੰਮੇਵਾਰ ਨਹੀਂ ਹਾਂ।