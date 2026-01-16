<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "59263d094f20b302053888cd236880c3",
  "translation_date": "2025-08-27T21:28:17+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp.md",
  "language_code": "tl"
}
-->
# Sukatin ang temperatura - Wio Terminal

Sa bahaging ito ng aralin, magdadagdag ka ng temperature sensor sa iyong Wio Terminal, at babasahin ang mga halaga ng temperatura mula rito.

## Kagamitan

Kailangan ng Wio Terminal ng temperature sensor.

Ang sensor na gagamitin mo ay isang [DHT11 humidity at temperature sensor](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), na pinagsasama ang 2 sensor sa isang pakete. Ito ay medyo popular, at maraming mga sensor na komersyal na magagamit ang pinagsasama ang temperatura, halumigmig, at minsan ang atmospheric pressure. Ang temperature sensor component ay isang negative temperature coefficient (NTC) thermistor, isang thermistor kung saan bumababa ang resistance habang tumataas ang temperatura.

Ito ay isang digital sensor, kaya mayroon itong onboard ADC upang lumikha ng digital signal na naglalaman ng data ng temperatura at halumigmig na mababasa ng microcontroller.

### Ikonekta ang temperature sensor

Ang Grove temperature sensor ay maaaring ikonekta sa digital port ng Wio Terminal.

#### Gawain - ikonekta ang temperature sensor

Ikonekta ang temperature sensor.

![Isang Grove temperature sensor](../../../../../translated_images/tl/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.png)

1. Ipasok ang isang dulo ng Grove cable sa socket ng humidity at temperature sensor. Isa lang ang tamang paraan para maipasok ito.

1. Kapag ang Wio Terminal ay hindi nakakonekta sa iyong computer o ibang power supply, ikonekta ang kabilang dulo ng Grove cable sa Grove socket sa kanang bahagi ng Wio Terminal habang nakatingin ka sa screen. Ito ang socket na pinakamalayo sa power button.

![Ang Grove temperature sensor na nakakonekta sa kanang socket](../../../../../translated_images/tl/wio-temperature-sensor.2934928f38c7f79a.webp)

## I-program ang temperature sensor

Ang Wio Terminal ay maaari nang i-program upang magamit ang nakakabit na temperature sensor.

### Gawain - i-program ang temperature sensor

I-program ang device.

1. Gumawa ng bagong Wio Terminal project gamit ang PlatformIO. Tawagin ang proyektong ito na `temperature-sensor`. Magdagdag ng code sa `setup` function upang i-configure ang serial port.

    > ⚠️ Maaari kang sumangguni sa [mga tagubilin para sa paggawa ng PlatformIO project sa project 1, lesson 1 kung kinakailangan](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Magdagdag ng library dependency para sa Seeed Grove Humidity at Temperature sensor library sa `platformio.ini` file ng proyekto:

    ```ini
    lib_deps =
        seeed-studio/Grove Temperature And Humidity Sensor @ 1.0.1
    ```

    > ⚠️ Maaari kang sumangguni sa [mga tagubilin para sa pagdaragdag ng mga library sa isang PlatformIO project sa project 1, lesson 4 kung kinakailangan](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md#install-the-wifi-and-mqtt-arduino-libraries).

1. Magdagdag ng mga sumusunod na `#include` directives sa itaas ng file, sa ilalim ng umiiral na `#include <Arduino.h>`:

    ```cpp
    #include <DHT.h>
    #include <SPI.h>
    ```

    Ina-import nito ang mga file na kailangan upang makipag-ugnayan sa sensor. Ang `DHT.h` header file ay naglalaman ng code para sa sensor mismo, at ang pagdaragdag ng `SPI.h` header ay tinitiyak na ang code na kailangan upang makipag-usap sa sensor ay naka-link kapag ang app ay na-compile.

1. Bago ang `setup` function, ideklara ang DHT sensor:

    ```cpp
    DHT dht(D0, DHT11);
    ```

    Ideklara nito ang isang instance ng `DHT` class na namamahala sa **D**igital **H**umidity at **T**emperature sensor. Ito ay nakakonekta sa port `D0`, ang Grove socket sa kanang bahagi ng Wio Terminal. Ang pangalawang parameter ay nagsasabi sa code na ang sensor na ginagamit ay ang *DHT11* sensor - sinusuportahan ng library na ginagamit mo ang iba pang mga variant ng sensor na ito.

1. Sa `setup` function, magdagdag ng code upang i-set up ang serial connection:

    ```cpp
    void setup()
    {
        Serial.begin(9600);
    
        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    ```

1. Sa dulo ng `setup` function, pagkatapos ng huling `delay`, magdagdag ng tawag upang simulan ang DHT sensor:

    ```cpp
    dht.begin();
    ```

1. Sa `loop` function, magdagdag ng code upang tawagan ang sensor at i-print ang temperatura sa serial port:

    ```cpp
    void loop()
    {
        float temp_hum_val[2] = {0};
        dht.readTempAndHumidity(temp_hum_val);
        Serial.print("Temperature: ");
        Serial.print(temp_hum_val[1]);
        Serial.println ("°C");
    
        delay(10000);
    }
    ```

    Ang code na ito ay nagdedeklara ng isang walang laman na array ng 2 floats, at ipinapasa ito sa tawag sa `readTempAndHumidity` sa `DHT` instance. Ang tawag na ito ay pinupunan ang array ng 2 halaga - ang halumigmig ay napupunta sa ika-0 item sa array (tandaan na sa C++ ang mga array ay 0-based, kaya ang ika-0 item ay ang 'unang' item sa array), at ang temperatura ay napupunta sa ika-1 item.

    Ang temperatura ay binabasa mula sa ika-1 item sa array, at ini-print sa serial port.

    > 🇺🇸 Ang temperatura ay binabasa sa Celsius. Para sa mga Amerikano, upang i-convert ito sa Fahrenheit, hatiin ang halaga ng Celsius na nabasa sa 5, pagkatapos ay i-multiply sa 9, pagkatapos ay magdagdag ng 32. Halimbawa, ang temperatura na 20°C ay nagiging ((20/5)*9) + 32 = 68°F.

1. I-build at i-upload ang code sa Wio Terminal.

    > ⚠️ Maaari kang sumangguni sa [mga tagubilin para sa paggawa ng PlatformIO project sa project 1, lesson 1 kung kinakailangan](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Kapag na-upload na, maaari mong i-monitor ang temperatura gamit ang serial monitor:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 24.00°C
    ```

> 💁 Maaari mong mahanap ang code na ito sa [code-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/wio-terminal) folder.

😀 Tagumpay ang iyong temperature sensor program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.