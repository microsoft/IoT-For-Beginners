<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ea733bd0cdf2479e082373f765a08678",
  "translation_date": "2025-08-27T22:24:56+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-sensor.md",
  "language_code": "tl"
}
-->
# Gumawa ng nightlight - Raspberry Pi

Sa bahaging ito ng aralin, magdadagdag ka ng light sensor sa iyong Raspberry Pi.

## Kagamitan

Ang sensor para sa araling ito ay isang **light sensor** na gumagamit ng [photodiode](https://wikipedia.org/wiki/Photodiode) upang i-convert ang liwanag sa isang electrical signal. Ito ay isang analog sensor na nagpapadala ng integer value mula 0 hanggang 1,000 na nagpapahiwatig ng relatibong dami ng liwanag na hindi tumutugma sa anumang standard na yunit ng pagsukat tulad ng [lux](https://wikipedia.org/wiki/Lux).

Ang light sensor ay isang external na Grove sensor at kailangang ikonekta sa Grove Base hat sa Raspberry Pi.

### Ikonekta ang light sensor

Ang Grove light sensor na ginagamit upang matukoy ang antas ng liwanag ay kailangang ikonekta sa Raspberry Pi.

#### Gawain - ikonekta ang light sensor

Ikonekta ang light sensor.

![Isang Grove light sensor](../../../../../translated_images/tl/grove-light-sensor.b8127b7c434e632d6bcdb57587a14e9ef69a268a22df95d08628f62b8fa5505c.png)

1. Ipasok ang isang dulo ng Grove cable sa socket ng light sensor module. Ito ay papasok lamang sa isang direksyon.

1. Kapag naka-off ang Raspberry Pi, ikonekta ang kabilang dulo ng Grove cable sa analog socket na may markang **A0** sa Grove Base hat na nakakabit sa Pi. Ang socket na ito ay pangalawa mula sa kanan, sa hanay ng mga socket malapit sa GPIO pins.

![Ang Grove light sensor na nakakonekta sa socket A0](../../../../../translated_images/tl/pi-light-sensor.66cc1e31fa48cd7d5f23400d4b2119aa41508275cb7c778053a7923b4e972d7e.png)

## I-program ang light sensor

Ang device ay maaari nang i-program gamit ang Grove light sensor.

### Gawain - i-program ang light sensor

I-program ang device.

1. I-on ang Pi at hintaying mag-boot ito.

1. Buksan ang nightlight project sa VS Code na ginawa mo sa nakaraang bahagi ng assignment, alinman sa direkta sa Pi o gamit ang Remote SSH extension.

1. Buksan ang `app.py` file at tanggalin ang lahat ng code dito.

1. Idagdag ang sumusunod na code sa `app.py` file upang mag-import ng ilang kinakailangang libraries:

    ```python
    import time
    from grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    Ang `import time` na statement ay nag-i-import ng `time` module na gagamitin sa susunod na bahagi ng assignment.

    Ang `from grove.grove_light_sensor_v1_2 import GroveLightSensor` na statement ay nag-i-import ng `GroveLightSensor` mula sa Grove Python libraries. Ang library na ito ay may code para makipag-ugnayan sa Grove light sensor, at na-install globally noong setup ng Pi.

1. Idagdag ang sumusunod na code pagkatapos ng code sa itaas upang lumikha ng instance ng class na namamahala sa light sensor:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    Ang linya na `light_sensor = GroveLightSensor(0)` ay lumilikha ng instance ng `GroveLightSensor` class na nakakonekta sa pin **A0** - ang analog Grove pin kung saan nakakonekta ang light sensor.

1. Magdagdag ng infinite loop pagkatapos ng code sa itaas upang basahin ang light sensor value at i-print ito sa console:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Babasahin nito ang kasalukuyang antas ng liwanag sa scale na 0-1,023 gamit ang `light` property ng `GroveLightSensor` class. Ang property na ito ay nagbabasa ng analog value mula sa pin. Ang value na ito ay ipapakita sa console.

1. Magdagdag ng maliit na sleep na isang segundo sa dulo ng `loop` dahil hindi kailangang patuloy na suriin ang antas ng liwanag. Ang sleep ay nakakatulong upang mabawasan ang power consumption ng device.

    ```python
    time.sleep(1)
    ```

1. Mula sa VS Code Terminal, patakbuhin ang sumusunod upang patakbuhin ang iyong Python app:

    ```sh
    python3 app.py
    ```

    Ang mga light values ay ipapakita sa console. Takpan at alisin ang takip sa light sensor, at magbabago ang mga values:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

> 💁 Makikita mo ang code na ito sa [code-sensor/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/pi) folder.

😀 Tagumpay ang pagdaragdag ng sensor sa iyong nightlight program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.