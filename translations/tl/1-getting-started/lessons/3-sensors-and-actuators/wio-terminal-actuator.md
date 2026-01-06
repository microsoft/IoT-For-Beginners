<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "db44083b4dc6fb06eac83c4f16448940",
  "translation_date": "2025-08-27T22:32:48+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-actuator.md",
  "language_code": "tl"
}
-->
# Gumawa ng nightlight - Wio Terminal

Sa bahaging ito ng aralin, magdadagdag ka ng LED sa iyong Wio Terminal at gagamitin ito upang lumikha ng nightlight.

## Hardware

Ang nightlight ngayon ay nangangailangan ng actuator.

Ang actuator ay isang **LED**, isang [light-emitting diode](https://wikipedia.org/wiki/Light-emitting_diode) na naglalabas ng liwanag kapag dumadaloy ang kuryente dito. Ito ay isang digital actuator na may 2 estado, bukas at sarado. Ang pagpapadala ng halaga na 1 ay magpapailaw sa LED, at 0 ay magpapapatay dito. Ito ay isang panlabas na Grove actuator at kailangang ikonekta sa Wio Terminal.

Ang lohika ng nightlight sa pseudo-code ay:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Ikonekta ang LED

Ang Grove LED ay may module na may iba't ibang LED, na nagbibigay-daan sa iyo na pumili ng kulay.

#### Gawain - ikonekta ang LED

Ikonekta ang LED.

![Isang Grove LED](../../../../../translated_images/grove-led.6c853be93f473cf2c439cfc74bb1064732b22251a83cedf66e62f783f9cc1a79.tl.png)

1. Pumili ng paborito mong LED at ipasok ang mga paa nito sa dalawang butas sa LED module.

    Ang mga LED ay light-emitting diodes, at ang mga diode ay mga elektronikong aparato na maaaring magdala ng kuryente sa isang direksyon lamang. Nangangahulugan ito na ang LED ay kailangang ikonekta nang tama, kung hindi, hindi ito gagana.

    Ang isa sa mga paa ng LED ay ang positibong pin, ang isa naman ay ang negatibong pin. Ang LED ay hindi perpektong bilog, at medyo patag sa isang gilid. Ang medyo patag na gilid ay ang negatibong pin. Kapag ikinonekta mo ang LED sa module, tiyaking ang pin sa bilog na gilid ay konektado sa socket na may markang **+** sa labas ng module, at ang patag na gilid ay konektado sa socket na mas malapit sa gitna ng module.

1. Ang LED module ay may spin button na nagbibigay-daan sa iyo na kontrolin ang liwanag. I-turn ito nang todo pataas sa simula sa pamamagitan ng pag-ikot nito pakanan gamit ang maliit na Phillips head screwdriver.

1. Ipasok ang isang dulo ng Grove cable sa socket ng LED module. Ito ay papasok lamang sa isang direksyon.

1. Kapag ang Wio Terminal ay hindi nakakonekta sa iyong computer o iba pang power supply, ikonekta ang kabilang dulo ng Grove cable sa kanang bahagi ng Grove socket sa Wio Terminal habang tinitingnan mo ang screen. Ito ang socket na pinakamalayo sa power button.

    > 💁 Ang kanang Grove socket ay maaaring gamitin sa analog o digital sensors at actuators. Ang kaliwang socket ay para sa I2C at digital sensors at actuators lamang. Ang I2C ay tatalakayin sa susunod na aralin.

![Ang Grove LED na nakakonekta sa kanang socket](../../../../../translated_images/wio-led.265a1897e72d7f21.tl.png)

## I-program ang nightlight

Ang nightlight ay maaari nang i-program gamit ang built-in na light sensor at ang Grove LED.

### Gawain - i-program ang nightlight

I-program ang nightlight.

1. Buksan ang nightlight project sa VS Code na ginawa mo sa nakaraang bahagi ng assignment.

1. Idagdag ang sumusunod na linya sa ibaba ng `setup` function:

    ```cpp
    pinMode(D0, OUTPUT);
    ```

    Ang linyang ito ay nagko-configure sa pin na ginagamit upang makipag-ugnayan sa LED sa pamamagitan ng Grove port.

    Ang `D0` pin ay ang digital pin para sa kanang Grove socket. Ang pin na ito ay itinakda sa `OUTPUT`, nangangahulugang ito ay konektado sa actuator at ang data ay isusulat sa pin.

1. Idagdag ang sumusunod na code kaagad bago ang `delay` sa loop function:

    ```cpp
    if (light < 300)
    {
        digitalWrite(D0, HIGH);
    }
    else
    {
        digitalWrite(D0, LOW);
    }
    ```

    Ang code na ito ay sinusuri ang `light` value. Kung ito ay mas mababa sa 300, nagpapadala ito ng `HIGH` value sa `D0` digital pin. Ang `HIGH` ay may halagang 1, na nagpapailaw sa LED. Kung ang liwanag ay mas mataas o katumbas ng 300, isang `LOW` value na 0 ang ipinapadala sa pin, na nagpapapatay sa LED.

    > 💁 Kapag nagpapadala ng digital values sa actuators, ang LOW value ay 0v, at ang HIGH value ay ang max na boltahe para sa device. Para sa Wio Terminal, ang HIGH voltage ay 3.3V.

1. Ikonekta muli ang Wio Terminal sa iyong computer, at i-upload ang bagong code tulad ng ginawa mo dati.

1. Ikonekta ang Serial Monitor. Ang mga light values ay ipapakita sa terminal.

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

1. Takpan at alisin ang takip sa light sensor. Mapapansin mo kung paano iilaw ang LED kapag ang light level ay 300 o mas mababa, at mamamatay kapag ang light level ay mas mataas sa 300.

![Ang LED na nakakonekta sa WIO na nagbubukas at nagsasara habang nagbabago ang light level](../../../../../images/wio-running-assignment-1-1.gif)

> 💁 Makikita mo ang code na ito sa [code-actuator/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/wio-terminal) folder.

😀 Tagumpay ang iyong nightlight program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.