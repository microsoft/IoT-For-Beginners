<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "da6ae0a795cf06be33d23ca5b8493fc8",
  "translation_date": "2025-08-27T14:37:44+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-sensor.md",
  "language_code": "pa"
}
-->
# GPS ਡਾਟਾ ਪੜ੍ਹੋ - Wio Terminal

ਇਸ ਪਾਠ ਦੇ ਇਸ ਹਿੱਸੇ ਵਿੱਚ, ਤੁਸੀਂ ਆਪਣੇ Wio Terminal ਵਿੱਚ GPS ਸੈਂਸਰ ਜੋੜੋਗੇ ਅਤੇ ਇਸ ਤੋਂ ਮੁੱਲ ਪੜ੍ਹੋਗੇ।

## ਹਾਰਡਵੇਅਰ

Wio Terminal ਨੂੰ GPS ਸੈਂਸਰ ਦੀ ਲੋੜ ਹੈ।

ਤੁਸੀਂ ਜੋ ਸੈਂਸਰ ਵਰਤੋਗੇ ਉਹ [Grove GPS Air530 sensor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html) ਹੈ। ਇਹ ਸੈਂਸਰ ਕਈ GPS ਸਿਸਟਮਾਂ ਨਾਲ ਜੁੜ ਸਕਦਾ ਹੈ ਤਾਂ ਜੋ ਤੇਜ਼ ਅਤੇ ਸਹੀ ਸਥਿਤੀ ਪ੍ਰਾਪਤ ਕੀਤੀ ਜਾ ਸਕੇ। ਸੈਂਸਰ 2 ਹਿੱਸਿਆਂ ਤੋਂ ਬਣਿਆ ਹੈ - ਸੈਂਸਰ ਦੇ ਮੁੱਖ ਇਲੈਕਟ੍ਰਾਨਿਕਸ ਅਤੇ ਇੱਕ ਬਾਹਰੀ ਐਂਟੀਨਾ ਜੋ ਪਤਲੇ ਤਾਰ ਨਾਲ ਜੁੜਿਆ ਹੈ ਜੋ ਸੈਟੇਲਾਈਟ ਤੋਂ ਰੇਡੀਓ ਤਰੰਗਾਂ ਨੂੰ ਪਕੜਦਾ ਹੈ।

ਇਹ ਇੱਕ UART ਸੈਂਸਰ ਹੈ, ਇਸ ਲਈ ਇਹ GPS ਡਾਟਾ UART ਰਾਹੀਂ ਭੇਜਦਾ ਹੈ।

### GPS ਸੈਂਸਰ ਨੂੰ ਜੁੜੋ

Grove GPS ਸੈਂਸਰ ਨੂੰ Wio Terminal ਨਾਲ ਜੁੜਿਆ ਜਾ ਸਕਦਾ ਹੈ।

#### ਕੰਮ - GPS ਸੈਂਸਰ ਨੂੰ ਜੁੜੋ

GPS ਸੈਂਸਰ ਨੂੰ ਜੁੜੋ।

![A grove GPS sensor](../../../../../translated_images/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.pa.png)

1. Grove ਕੇਬਲ ਦੇ ਇੱਕ ਸਿਰੇ ਨੂੰ GPS ਸੈਂਸਰ ਦੇ ਸਾਕਟ ਵਿੱਚ ਪਾਓ। ਇਹ ਸਿਰਫ ਇੱਕ ਹੀ ਦਿਸ਼ਾ ਵਿੱਚ ਜਾਵੇਗਾ।

1. Wio Terminal ਨੂੰ ਆਪਣੇ ਕੰਪਿਊਟਰ ਜਾਂ ਹੋਰ ਪਾਵਰ ਸਪਲਾਈ ਤੋਂ ਅਲੱਗ ਰੱਖਦੇ ਹੋਏ, Grove ਕੇਬਲ ਦੇ ਦੂਜੇ ਸਿਰੇ ਨੂੰ Wio Terminal ਦੇ ਖੱਬੇ ਪਾਸੇ Grove ਸਾਕਟ ਵਿੱਚ ਪਾਓ ਜਦੋਂ ਤੁਸੀਂ ਸਕ੍ਰੀਨ ਨੂੰ ਦੇਖ ਰਹੇ ਹੋ। ਇਹ ਸਾਕਟ ਪਾਵਰ ਬਟਨ ਦੇ ਸਭ ਤੋਂ ਨੇੜੇ ਹੈ।

    ![The grove GPS sensor connected to the left hand socket](../../../../../translated_images/wio-gps-sensor.19fd52b81ce58095d5deb3d4e5a1fdd88818d76569b00b1f0d740c92dc986525.pa.png)

1. GPS ਸੈਂਸਰ ਨੂੰ ਇਸ ਤਰ੍ਹਾਂ ਸਥਿਤ ਕਰੋ ਕਿ ਜੁੜੇ ਐਂਟੀਨਾ ਨੂੰ ਅਸਮਾਨ ਦੀ ਦ੍ਰਿਸ਼ਟੀ ਹੋਵੇ - ਵਧੀਆ ਤੌਰ 'ਤੇ ਖੁੱਲੇ ਵਿੰਡੋ ਦੇ ਨੇੜੇ ਜਾਂ ਬਾਹਰ। ਐਂਟੀਨਾ ਦੇ ਰਾਹ ਵਿੱਚ ਕੁਝ ਨਾ ਹੋਣ ਨਾਲ ਸਪਸ਼ਟ ਸਿਗਨਲ ਪ੍ਰਾਪਤ ਕਰਨਾ ਆਸਾਨ ਹੈ।

1. ਹੁਣ ਤੁਸੀਂ Wio Terminal ਨੂੰ ਆਪਣੇ ਕੰਪਿਊਟਰ ਨਾਲ ਜੁੜ ਸਕਦੇ ਹੋ।

1. GPS ਸੈਂਸਰ ਵਿੱਚ 2 LEDs ਹਨ - ਇੱਕ ਨੀਲਾ LED ਜੋ ਡਾਟਾ ਭੇਜਣ ਸਮੇਂ ਚਮਕਦਾ ਹੈ, ਅਤੇ ਇੱਕ ਹਰਾ LED ਜੋ ਸੈਟੇਲਾਈਟ ਤੋਂ ਡਾਟਾ ਪ੍ਰਾਪਤ ਕਰਨ ਸਮੇਂ ਹਰ ਸਕਿੰਟ ਚਮਕਦਾ ਹੈ। ਯਕੀਨੀ ਬਣਾਓ ਕਿ Wio Terminal ਨੂੰ ਪਾਵਰ ਦੇਣ ਸਮੇਂ ਨੀਲਾ LED ਚਮਕ ਰਿਹਾ ਹੈ। ਕੁਝ ਮਿੰਟਾਂ ਬਾਅਦ ਹਰਾ LED ਚਮਕੇਗਾ - ਜੇਕਰ ਨਹੀਂ, ਤਾਂ ਤੁਹਾਨੂੰ ਐਂਟੀਨਾ ਨੂੰ ਦੁਬਾਰਾ ਸਥਿਤ ਕਰਨ ਦੀ ਲੋੜ ਹੋ ਸਕਦੀ ਹੈ।

## GPS ਸੈਂਸਰ ਨੂੰ ਪ੍ਰੋਗਰਾਮ ਕਰੋ

ਹੁਣ Wio Terminal ਨੂੰ ਜੁੜੇ GPS ਸੈਂਸਰ ਨੂੰ ਵਰਤਣ ਲਈ ਪ੍ਰੋਗਰਾਮ ਕੀਤਾ ਜਾ ਸਕਦਾ ਹੈ।

### ਕੰਮ - GPS ਸੈਂਸਰ ਨੂੰ ਪ੍ਰੋਗਰਾਮ ਕਰੋ

ਡਿਵਾਈਸ ਨੂੰ ਪ੍ਰੋਗਰਾਮ ਕਰੋ।

1. PlatformIO ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਇੱਕ ਨਵਾਂ Wio Terminal ਪ੍ਰੋਜੈਕਟ ਬਣਾਓ। ਇਸ ਪ੍ਰੋਜੈਕਟ ਨੂੰ `gps-sensor` ਨਾਮ ਦਿਓ। `setup` ਫੰਕਸ਼ਨ ਵਿੱਚ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ ਤਾਂ ਜੋ ਸੀਰੀਅਲ ਪੋਰਟ ਨੂੰ ਕਨਫਿਗਰ ਕੀਤਾ ਜਾ ਸਕੇ।

1. `main.cpp` ਫਾਈਲ ਦੇ ਉੱਪਰ ਹਿੱਸੇ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤਾ ਸ਼ਾਮਲ ਕਰਨ ਵਾਲਾ ਨਿਰਦੇਸ਼ ਸ਼ਾਮਲ ਕਰੋ। ਇਹ ਇੱਕ ਹੈਡਰ ਫਾਈਲ ਸ਼ਾਮਲ ਕਰਦਾ ਹੈ ਜਿਸ ਵਿੱਚ ਖੱਬੇ ਪਾਸੇ Grove ਪੋਰਟ ਨੂੰ UART ਲਈ ਕਨਫਿਗਰ ਕਰਨ ਦੇ ਫੰਕਸ਼ਨ ਹਨ।

    ```cpp
    #include <wiring_private.h>
    ```

1. ਇਸ ਦੇ ਹੇਠਾਂ, ਹੇਠਾਂ ਦਿੱਤੀ ਲਾਈਨ ਸ਼ਾਮਲ ਕਰੋ ਤਾਂ ਜੋ UART ਪੋਰਟ ਨਾਲ ਸੀਰੀਅਲ ਪੋਰਟ ਕਨੈਕਸ਼ਨ ਘੋਸ਼ਿਤ ਕੀਤਾ ਜਾ ਸਕੇ:

    ```cpp
    static Uart Serial3(&sercom3, PIN_WIRE_SCL, PIN_WIRE_SDA, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    ```

1. ਤੁਹਾਨੂੰ ਕੁਝ ਕੋਡ ਸ਼ਾਮਲ ਕਰਨ ਦੀ ਲੋੜ ਹੈ ਤਾਂ ਜੋ ਕੁਝ ਅੰਦਰੂਨੀ ਸਿਗਨਲ ਹੈਂਡਲਰਾਂ ਨੂੰ ਇਸ ਸੀਰੀਅਲ ਪੋਰਟ ਵੱਲ ਰੀਡਾਇਰੈਕਟ ਕੀਤਾ ਜਾ ਸਕੇ। `Serial3` ਘੋਸ਼ਣਾ ਦੇ ਹੇਠਾਂ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ:

    ```cpp
    void SERCOM3_0_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_1_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_2_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_3_Handler()
    {
        Serial3.IrqHandler();
    }
    ```

1. `setup` ਫੰਕਸ਼ਨ ਵਿੱਚ ਜਿੱਥੇ `Serial` ਪੋਰਟ ਕਨਫਿਗਰ ਕੀਤਾ ਗਿਆ ਹੈ, ਉਸ ਦੇ ਹੇਠਾਂ ਹੇਠਾਂ ਦਿੱਤੇ ਕੋਡ ਨਾਲ UART ਸੀਰੀਅਲ ਪੋਰਟ ਨੂੰ ਕਨਫਿਗਰ ਕਰੋ:

    ```cpp
    Serial3.begin(9600);

    while (!Serial3)
        ; // Wait for Serial3 to be ready

    delay(1000);
    ```

1. `setup` ਫੰਕਸ਼ਨ ਵਿੱਚ ਇਸ ਕੋਡ ਦੇ ਹੇਠਾਂ, ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ ਤਾਂ ਜੋ Grove ਪਿਨ ਨੂੰ ਸੀਰੀਅਲ ਪੋਰਟ ਨਾਲ ਜੋੜਿਆ ਜਾ ਸਕੇ:

    ```cpp
    pinPeripheral(PIN_WIRE_SCL, PIO_SERCOM_ALT);
    ```

1. `loop` ਫੰਕਸ਼ਨ ਤੋਂ ਪਹਿਲਾਂ ਹੇਠਾਂ ਦਿੱਤਾ ਫੰਕਸ਼ਨ ਸ਼ਾਮਲ ਕਰੋ ਤਾਂ ਜੋ GPS ਡਾਟਾ ਨੂੰ ਸੀਰੀਅਲ ਮਾਨੀਟਰ ਵੱਲ ਭੇਜਿਆ ਜਾ ਸਕੇ:

    ```cpp
    void printGPSData()
    {
        Serial.println(Serial3.readStringUntil('\n'));
    }
    ```

1. `loop` ਫੰਕਸ਼ਨ ਵਿੱਚ, ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ ਤਾਂ ਜੋ UART ਸੀਰੀਅਲ ਪੋਰਟ ਤੋਂ ਪੜ੍ਹਿਆ ਜਾ ਸਕੇ ਅਤੇ ਆਉਟਪੁੱਟ ਨੂੰ ਸੀਰੀਅਲ ਮਾਨੀਟਰ ਤੇ ਪ੍ਰਿੰਟ ਕੀਤਾ ਜਾ ਸਕੇ:

    ```cpp
    while (Serial3.available() > 0)
    {
        printGPSData();
    }
    
    delay(1000);
    ```

    ਇਹ ਕੋਡ UART ਸੀਰੀਅਲ ਪੋਰਟ ਤੋਂ ਪੜ੍ਹਦਾ ਹੈ। `readStringUntil` ਫੰਕਸ਼ਨ ਇੱਕ ਟਰਮੀਨੇਟਰ ਕਿਰਦਾਰ (ਇਸ ਮਾਮਲੇ ਵਿੱਚ ਨਵੀਂ ਲਾਈਨ) ਤੱਕ ਪੜ੍ਹਦਾ ਹੈ। ਇਹ ਇੱਕ ਪੂਰੀ NMEA ਵਾਕ (NMEA ਵਾਕ ਨਵੀਂ ਲਾਈਨ ਕਿਰਦਾਰ ਨਾਲ ਖਤਮ ਹੁੰਦੇ ਹਨ) ਪੜ੍ਹੇਗਾ। ਜਦੋਂ ਤੱਕ UART ਸੀਰੀਅਲ ਪੋਰਟ ਤੋਂ ਡਾਟਾ ਪੜ੍ਹਿਆ ਜਾ ਸਕਦਾ ਹੈ, ਇਹ ਪੜ੍ਹਿਆ ਜਾਂਦਾ ਹੈ ਅਤੇ `printGPSData` ਫੰਕਸ਼ਨ ਰਾਹੀਂ ਸੀਰੀਅਲ ਮਾਨੀਟਰ ਵੱਲ ਭੇਜਿਆ ਜਾਂਦਾ ਹੈ। ਜਦੋਂ ਹੋਰ ਡਾਟਾ ਪੜ੍ਹਿਆ ਨਹੀਂ ਜਾ ਸਕਦਾ, `loop` 1 ਸਕਿੰਟ (1,000ms) ਲਈ ਡੀਲੇ ਕਰਦਾ ਹੈ।

1. ਕੋਡ ਨੂੰ Wio Terminal ਵਿੱਚ ਬਣਾਓ ਅਤੇ ਅਪਲੋਡ ਕਰੋ।

1. ਅਪਲੋਡ ਕਰਨ ਤੋਂ ਬਾਅਦ, ਤੁਸੀਂ GPS ਡਾਟਾ ਨੂੰ ਸੀਰੀਅਲ ਮਾਨੀਟਰ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਮਾਨੀਟਰ ਕਰ ਸਕਦੇ ਹੋ।

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

> 💁 ਤੁਸੀਂ ਇਹ ਕੋਡ [code-gps/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps/wio-terminal) ਫੋਲਡਰ ਵਿੱਚ ਲੱਭ ਸਕਦੇ ਹੋ।

😀 ਤੁਹਾਡਾ GPS ਸੈਂਸਰ ਪ੍ਰੋਗਰਾਮ ਸਫਲ ਰਿਹਾ!

---

**ਅਸਵੀਕਾਰਨਾ**:  
ਇਹ ਦਸਤਾਵੇਜ਼ AI ਅਨੁਵਾਦ ਸੇਵਾ [Co-op Translator](https://github.com/Azure/co-op-translator) ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅਨੁਵਾਦ ਕੀਤਾ ਗਿਆ ਹੈ। ਜਦੋਂ ਕਿ ਅਸੀਂ ਸਹੀਤਾ ਲਈ ਯਤਨਸ਼ੀਲ ਹਾਂ, ਕਿਰਪਾ ਕਰਕੇ ਧਿਆਨ ਦਿਓ ਕਿ ਸਵੈਚਾਲਿਤ ਅਨੁਵਾਦਾਂ ਵਿੱਚ ਗਲਤੀਆਂ ਜਾਂ ਅਸੁਣੀਕਤਾਵਾਂ ਹੋ ਸਕਦੀਆਂ ਹਨ। ਮੂਲ ਦਸਤਾਵੇਜ਼ ਨੂੰ ਇਸਦੀ ਮੂਲ ਭਾਸ਼ਾ ਵਿੱਚ ਅਧਿਕਾਰਤ ਸਰੋਤ ਮੰਨਿਆ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ। ਮਹੱਤਵਪੂਰਨ ਜਾਣਕਾਰੀ ਲਈ, ਪੇਸ਼ੇਵਰ ਮਨੁੱਖੀ ਅਨੁਵਾਦ ਦੀ ਸਿਫਾਰਸ਼ ਕੀਤੀ ਜਾਂਦੀ ਹੈ। ਇਸ ਅਨੁਵਾਦ ਦੀ ਵਰਤੋਂ ਤੋਂ ਪੈਦਾ ਹੋਣ ਵਾਲੇ ਕਿਸੇ ਵੀ ਗਲਤਫਹਿਮੀ ਜਾਂ ਗਲਤ ਵਿਆਖਿਆ ਲਈ ਅਸੀਂ ਜ਼ਿੰਮੇਵਾਰ ਨਹੀਂ ਹਾਂ।