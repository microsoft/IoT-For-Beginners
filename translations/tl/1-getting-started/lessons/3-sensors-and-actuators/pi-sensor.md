<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ea733bd0cdf2479e082373f765a08678",
  "translation_date": "2025-08-28T00:48:52+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-sensor.md",
  "language_code": "tl"
}
-->
# Gumawa ng nightlight - Raspberry Pi

Sa bahaging ito ng aralin, magdadagdag ka ng light sensor sa iyong Raspberry Pi.

## Kagamitan

Ang sensor para sa araling ito ay isang **light sensor** na gumagamit ng [photodiode](https://wikipedia.org/wiki/Photodiode) upang gawing electrical signal ang liwanag. Isa itong analog sensor na nagpapadala ng integer value mula 0 hanggang 1,000 na nagpapakita ng relatibong dami ng liwanag, ngunit hindi ito tumutugma sa anumang standard na yunit ng pagsukat tulad ng [lux](https://wikipedia.org/wiki/Lux).

Ang light sensor ay isang external na Grove sensor at kailangang ikonekta sa Grove Base hat sa Raspberry Pi.

### Ikonekta ang light sensor

Ang Grove light sensor na ginagamit upang matukoy ang antas ng liwanag ay kailangang ikonekta sa Raspberry Pi.

#### Gawain - ikonekta ang light sensor

Ikonekta ang light sensor.

![Isang Grove light sensor](../../../../../translated_images/grove-light-sensor.b8127b7c434e632d6bcdb57587a14e9ef69a268a22df95d08628f62b8fa5505c.tl.png)

1. Ipasok ang isang dulo ng Grove cable sa socket ng light sensor module. Isang paraan lamang ang tamang pagpasok nito.

1. Kapag naka-off ang Raspberry Pi, ikonekta ang kabilang dulo ng Grove cable sa analog socket na may markang **A0** sa Grove Base hat na nakakabit sa Pi. Ang socket na ito ay ang pangalawa mula sa kanan, sa hanay ng mga socket na malapit sa GPIO pins.

![Ang Grove light sensor na nakakonekta sa socket A0](../../../../../translated_images/pi-light-sensor.66cc1e31fa48cd7d5f23400d4b2119aa41508275cb7c778053a7923b4e972d7e.tl.png)

## Iprograma ang light sensor

Ngayon ay maaari nang iprograma ang device gamit ang Grove light sensor.

### Gawain - iprograma ang light sensor

Iprograma ang device.

1. I-on ang Pi at hintaying mag-boot.

1. Buksan ang nightlight project sa VS Code na ginawa mo sa nakaraang bahagi ng gawaing ito, maaaring direkta sa Pi o gamit ang Remote SSH extension.

1. Buksan ang `app.py` file at tanggalin ang lahat ng code dito.

1. Idagdag ang sumusunod na code sa `app.py` file upang mag-import ng ilang kinakailangang library:

    ```python
    import time
    from grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    Ang `import time` na pahayag ay nag-i-import ng `time` module na gagamitin sa susunod na bahagi ng gawaing ito.

    Ang `from grove.grove_light_sensor_v1_2 import GroveLightSensor` na pahayag ay nag-i-import ng `GroveLightSensor` mula sa Grove Python libraries. Ang library na ito ay may code upang makipag-ugnayan sa isang Grove light sensor, at na-install ito globally noong setup ng Pi.

1. Idagdag ang sumusunod na code pagkatapos ng code sa itaas upang lumikha ng isang instance ng klase na namamahala sa light sensor:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    Ang linyang `light_sensor = GroveLightSensor(0)` ay lumilikha ng isang instance ng `GroveLightSensor` class na nakakonekta sa pin **A0** - ang analog Grove pin kung saan nakakonekta ang light sensor.

1. Magdagdag ng isang infinite loop pagkatapos ng code sa itaas upang basahin ang halaga ng light sensor at i-print ito sa console:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Babasahin nito ang kasalukuyang antas ng liwanag sa sukatang 0-1,023 gamit ang `light` property ng `GroveLightSensor` class. Ang property na ito ay nagbabasa ng analog value mula sa pin. Ang halagang ito ay ipi-print sa console.

1. Magdagdag ng maliit na sleep na isang segundo sa dulo ng `loop` dahil hindi kailangang tuloy-tuloy na suriin ang antas ng liwanag. Ang sleep ay nakakatulong upang mabawasan ang power consumption ng device.

    ```python
    time.sleep(1)
    ```

1. Mula sa VS Code Terminal, patakbuhin ang sumusunod upang patakbuhin ang iyong Python app:

    ```sh
    python3 app.py
    ```

    Ang mga halaga ng liwanag ay ipapakita sa console. Takpan at alisin ang takip sa light sensor, at magbabago ang mga halaga:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

> 💁 Maaari mong makita ang code na ito sa [code-sensor/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/pi) folder.

😀 Tagumpay ang pagdaragdag ng sensor sa iyong nightlight program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.