<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2bf65f162bcebd35fbcba5fd245afac4",
  "translation_date": "2025-08-28T01:15:39+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/virtual-device-soil-moisture.md",
  "language_code": "tl"
}
-->
# Sukatin ang Halumigmig ng Lupa - Virtual IoT Hardware

Sa bahaging ito ng aralin, magdadagdag ka ng capacitive soil moisture sensor sa iyong virtual IoT device, at babasahin ang mga halaga mula rito.

## Virtual Hardware

Ang virtual IoT device ay gagamit ng simulated Grove capacitive soil moisture sensor. Pinapanatili nitong pareho ang lab na ito sa paggamit ng Raspberry Pi na may pisikal na Grove capacitive soil moisture sensor.

Sa isang pisikal na IoT device, ang soil moisture sensor ay isang capacitive sensor na sumusukat sa halumigmig ng lupa sa pamamagitan ng pagtukoy sa capacitance ng lupa, isang katangian na nagbabago habang nagbabago ang halumigmig ng lupa. Kapag tumataas ang halumigmig ng lupa, bumababa ang boltahe.

Ito ay isang analog sensor, kaya gumagamit ito ng simulated 10-bit ADC upang mag-ulat ng halaga mula 1-1,023.

### Idagdag ang Soil Moisture Sensor sa CounterFit

Upang gumamit ng virtual soil moisture sensor, kailangan mo itong idagdag sa CounterFit app.

#### Gawain - Idagdag ang Soil Moisture Sensor sa CounterFit

Idagdag ang soil moisture sensor sa CounterFit app.

1. Gumawa ng bagong Python app sa iyong computer sa isang folder na tinatawag na `soil-moisture-sensor` na may isang file na tinatawag na `app.py` at isang Python virtual environment, at idagdag ang CounterFit pip packages.

    > ⚠️ Maaari kang sumangguni sa [mga tagubilin para sa paggawa at pag-set up ng CounterFit Python project sa lesson 1 kung kinakailangan](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Siguraduhing tumatakbo ang CounterFit web app.

1. Gumawa ng soil moisture sensor:

    1. Sa *Create sensor* box sa *Sensors* pane, i-drop down ang *Sensor type* box at piliin ang *Soil Moisture*.

    1. Iwanang nakatakda ang *Units* sa *NoUnits*.

    1. Siguraduhing ang *Pin* ay nakatakda sa *0*.

    1. Piliin ang **Add** button upang gumawa ng *Soil Moisture* sensor sa Pin 0.

    ![Mga setting ng soil moisture sensor](../../../../../translated_images/counterfit-create-soil-moisture-sensor.35266135a5e0ae68b29a684d7db0d2933a8098b2307d197f7c71577b724603aa.tl.png)

    Ang soil moisture sensor ay malilikha at lilitaw sa listahan ng mga sensor.

    ![Nagawa ang soil moisture sensor](../../../../../translated_images/counterfit-soil-moisture-sensor.81742b2de0e9de60a3b3b9a2ff8ecc686d428eb6d71820f27a693be26e5aceee.tl.png)

## Iprograma ang Soil Moisture Sensor App

Ang soil moisture sensor app ay maaari nang iprograma gamit ang CounterFit sensors.

### Gawain - Iprograma ang Soil Moisture Sensor App

Iprograma ang soil moisture sensor app.

1. Siguraduhing bukas ang `soil-moisture-sensor` app sa VS Code.

1. Buksan ang `app.py` file.

1. Idagdag ang sumusunod na code sa itaas ng `app.py` upang ikonekta ang app sa CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Idagdag ang sumusunod na code sa `app.py` file upang mag-import ng ilang kinakailangang library:

    ```python
    import time
    from counterfit_shims_grove.adc import ADC
    ```

    Ang `import time` na pahayag ay nag-i-import ng `time` module na gagamitin sa susunod na bahagi ng gawaing ito.

    Ang `from counterfit_shims_grove.adc import ADC` na pahayag ay nag-i-import ng `ADC` class upang makipag-ugnayan sa isang virtual analog to digital converter na maaaring kumonekta sa isang CounterFit sensor.

1. Idagdag ang sumusunod na code sa ibaba nito upang lumikha ng isang instance ng `ADC` class:

    ```python
    adc = ADC()
    ```

1. Gumawa ng isang infinite loop na nagbabasa mula sa ADC sa pin 0 at isinusulat ang resulta sa console. Ang loop na ito ay maaaring maghintay ng 10 segundo sa pagitan ng mga pagbabasa.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)
    
        time.sleep(10)
    ```

1. Mula sa CounterFit app, baguhin ang halaga ng soil moisture sensor na babasahin ng app. Maaari mo itong gawin sa dalawang paraan:

    * Maglagay ng numero sa *Value* box para sa soil moisture sensor, pagkatapos ay piliin ang **Set** button. Ang numerong inilagay mo ang magiging halagang ibabalik ng sensor.

    * Lagyan ng check ang *Random* checkbox, at maglagay ng *Min* at *Max* na halaga, pagkatapos ay piliin ang **Set** button. Sa tuwing babasahin ng sensor ang isang halaga, ito ay magbabasa ng random na numero sa pagitan ng *Min* at *Max*.

1. Patakbuhin ang Python app. Makikita mo ang mga sukat ng halumigmig ng lupa na nakasulat sa console. Baguhin ang *Value* o ang *Random* na mga setting upang makita ang pagbabago ng halaga.

    ```output
    (.venv) ➜ soil-moisture-sensor $ python app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

> 💁 Maaari mong makita ang code na ito sa [code/virtual-device](../../../../../2-farm/lessons/2-detect-soil-moisture/code/virtual-device) folder.

😀 Tagumpay ang iyong soil moisture sensor program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.