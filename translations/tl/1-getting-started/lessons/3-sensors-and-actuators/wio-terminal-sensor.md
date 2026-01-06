<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7f4ad0ef54f248b85b92187c94cf9dcb",
  "translation_date": "2025-08-27T22:35:35+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-sensor.md",
  "language_code": "tl"
}
-->
# Magdagdag ng sensor - Wio Terminal

Sa bahaging ito ng aralin, gagamitin mo ang light sensor sa iyong Wio Terminal.

## Kagamitan

Ang sensor para sa araling ito ay isang **light sensor** na gumagamit ng [photodiode](https://wikipedia.org/wiki/Photodiode) upang i-convert ang liwanag sa isang electrical signal. Ito ay isang analog sensor na nagpapadala ng integer value mula 0 hanggang 1,023 na nagpapahiwatig ng dami ng liwanag na hindi tumutugma sa anumang standard na yunit ng pagsukat tulad ng [lux](https://wikipedia.org/wiki/Lux).

Ang light sensor ay naka-built-in sa Wio Terminal at makikita sa pamamagitan ng malinaw na plastik na bintana sa likod.

![Ang light sensor sa likod ng Wio Terminal](../../../../../translated_images/wio-light-sensor.b1f529f3c95f5165.tl.png)

## I-program ang light sensor

Ang device ay maaari nang i-program upang magamit ang built-in na light sensor.

### Gawain

I-program ang device.

1. Buksan ang nightlight project sa VS Code na ginawa mo sa nakaraang bahagi ng assignment.

1. Idagdag ang sumusunod na linya sa ilalim ng `setup` function:

    ```cpp
    pinMode(WIO_LIGHT, INPUT);
    ```

    Ang linyang ito ay nagko-configure ng mga pin na ginagamit upang makipag-ugnayan sa sensor hardware.

    Ang `WIO_LIGHT` pin ay ang numero ng GPIO pin na konektado sa on-board light sensor. Ang pin na ito ay naka-set sa `INPUT`, ibig sabihin ay nakakonekta ito sa isang sensor at ang data ay babasahin mula sa pin.

1. Tanggalin ang nilalaman ng `loop` function.

1. Idagdag ang sumusunod na code sa ngayon ay walang laman na `loop` function.

    ```cpp
    int light = analogRead(WIO_LIGHT);
    Serial.print("Light value: ");
    Serial.println(light);
    ```

    Ang code na ito ay nagbabasa ng analog value mula sa `WIO_LIGHT` pin. Binabasa nito ang value mula 0-1,023 mula sa on-board light sensor. Ang value na ito ay ipinapadala sa serial port upang mabasa mo ito sa Serial Monitor kapag tumatakbo ang code na ito. Ang `Serial.print` ay nagsusulat ng teksto nang walang bagong linya sa dulo, kaya ang bawat linya ay magsisimula sa `Light value:` at magtatapos sa aktwal na light value.

1. Magdagdag ng maliit na delay na isang segundo (1,000ms) sa dulo ng `loop` dahil hindi kailangang suriin ang light levels nang tuloy-tuloy. Ang delay ay nakakapagpababa ng power consumption ng device.

    ```cpp
    delay(1000);
    ```

1. Ikonekta muli ang Wio Terminal sa iyong computer, at i-upload ang bagong code tulad ng ginawa mo dati.

1. Ikonekta ang Serial Monitor. Ang mga light value ay ipapakita sa terminal. Takpan at alisin ang takip ng light sensor sa likod ng Wio Terminal, at magbabago ang mga value.

    ```output
    > Executing task: platformio device monitor <

    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Light value: 4
    Light value: 5
    Light value: 4
    Light value: 158
    Light value: 343
    Light value: 348
    Light value: 344
    ```

> 💁 Makikita mo ang code na ito sa [code-sensor/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/wio-terminal) folder.

😀 Tagumpay ang pagdaragdag ng sensor sa iyong nightlight program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.