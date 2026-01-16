<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "11f10c6760fb8202cf368422702fdf70",
  "translation_date": "2025-08-27T22:34:50+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-sensor.md",
  "language_code": "tl"
}
-->
# Gumawa ng nightlight - Virtual na IoT Hardware

Sa bahaging ito ng aralin, magdadagdag ka ng light sensor sa iyong virtual na IoT device.

## Virtual na Hardware

Ang nightlight ay nangangailangan ng isang sensor, na ginawa sa CounterFit app.

Ang sensor ay isang **light sensor**. Sa isang pisikal na IoT device, ito ay magiging isang [photodiode](https://wikipedia.org/wiki/Photodiode) na nagko-convert ng liwanag sa isang electrical signal. Ang mga light sensor ay analog sensors na nagpapadala ng integer value na nagpapahiwatig ng relatibong dami ng liwanag, na hindi tumutugma sa anumang pamantayan ng yunit ng pagsukat tulad ng [lux](https://wikipedia.org/wiki/Lux).

### Idagdag ang mga sensor sa CounterFit

Upang gumamit ng virtual na light sensor, kailangan mo itong idagdag sa CounterFit app.

#### Gawain - idagdag ang mga sensor sa CounterFit

Idagdag ang light sensor sa CounterFit app.

1. Siguraduhing tumatakbo ang CounterFit web app mula sa nakaraang bahagi ng takdang-aralin. Kung hindi, simulan ito.

1. Gumawa ng light sensor:

    1. Sa *Create sensor* box sa *Sensors* pane, i-drop down ang *Sensor type* box at piliin ang *Light*.

    1. Iwanang nakatakda ang *Units* sa *NoUnits*.

    1. Siguraduhing ang *Pin* ay nakatakda sa *0*.

    1. Piliin ang **Add** button upang gumawa ng light sensor sa Pin 0.

    ![Ang mga setting ng light sensor](../../../../../translated_images/tl/counterfit-create-light-sensor.9f36a5e0d4458d8d554d54b34d2c806d56093d6e49fddcda2d20f6fef7f5cce1.png)

    Ang light sensor ay malilikha at lilitaw sa listahan ng mga sensor.

    ![Ang light sensor na ginawa](../../../../../translated_images/tl/counterfit-light-sensor.5d0f5584df56b90f6b2561910d9cb20dfbd73eeff2177c238d38f4de54aefae1.png)

## I-program ang light sensor

Ang device ay maaari nang i-program upang gamitin ang built-in na light sensor.

### Gawain - i-program ang light sensor

I-program ang device.

1. Buksan ang nightlight project sa VS Code na ginawa mo sa nakaraang bahagi ng takdang-aralin. Patayin at muling likhain ang terminal upang matiyak na ito ay tumatakbo gamit ang virtual environment kung kinakailangan.

1. Buksan ang `app.py` file.

1. Idagdag ang sumusunod na code sa itaas ng `app.py` file kasama ang iba pang `import` statements upang mag-import ng ilang kinakailangang libraries:

    ```python
    import time
    from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    Ang `import time` statement ay nag-i-import ng Python `time` module na gagamitin sa susunod na bahagi ng takdang-aralin.

    Ang `from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor` statement ay nag-i-import ng `GroveLightSensor` mula sa CounterFit Grove shim Python libraries. Ang library na ito ay may code upang makipag-ugnayan sa isang light sensor na ginawa sa CounterFit app.

1. Idagdag ang sumusunod na code sa ibaba ng file upang gumawa ng mga instance ng mga klase na namamahala sa light sensor:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    Ang linyang `light_sensor = GroveLightSensor(0)` ay gumagawa ng instance ng `GroveLightSensor` class na nakakonekta sa pin **0** - ang CounterFit Grove pin kung saan nakakonekta ang light sensor.

1. Magdagdag ng infinite loop pagkatapos ng code sa itaas upang basahin ang light sensor value at i-print ito sa console:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Babasahin nito ang kasalukuyang light level gamit ang `light` property ng `GroveLightSensor` class. Ang property na ito ay nagbabasa ng analog value mula sa pin. Ang value na ito ay ipi-print sa console.

1. Magdagdag ng maliit na sleep na isang segundo sa dulo ng `while` loop dahil hindi kailangang patuloy na suriin ang light levels. Ang sleep ay nakababawas sa power consumption ng device.

    ```python
    time.sleep(1)
    ```

1. Mula sa VS Code Terminal, patakbuhin ang sumusunod upang patakbuhin ang iyong Python app:

    ```sh
    python3 app.py
    ```

    Ang mga light values ay ipapakita sa console. Sa simula, ang value na ito ay magiging 0.

1. Mula sa CounterFit app, baguhin ang value ng light sensor na babasahin ng app. Maaari mo itong gawin sa dalawang paraan:

    * Maglagay ng numero sa *Value* box para sa light sensor, pagkatapos piliin ang **Set** button. Ang numero na inilagay mo ang magiging value na ibabalik ng sensor.

    * I-check ang *Random* checkbox, at maglagay ng *Min* at *Max* value, pagkatapos piliin ang **Set** button. Sa bawat pagkakataon na ang sensor ay magbabasa ng value, magbabasa ito ng random na numero sa pagitan ng *Min* at *Max*.

    Ang mga value na iyong itinakda ay ipapakita sa console. Baguhin ang *Value* o ang *Random* settings upang magbago ang value.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

> 💁 Matatagpuan mo ang code na ito sa [code-sensor/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/virtual-device) folder.

😀 Tagumpay ang iyong nightlight program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.