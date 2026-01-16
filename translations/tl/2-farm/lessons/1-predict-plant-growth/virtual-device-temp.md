<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "70e5a428b607cd5a9a4f422c2a4df03d",
  "translation_date": "2025-08-27T21:30:17+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/virtual-device-temp.md",
  "language_code": "tl"
}
-->
# Sukatin ang Temperatura - Virtual na IoT Hardware

Sa bahaging ito ng aralin, magdadagdag ka ng sensor ng temperatura sa iyong virtual na IoT device.

## Virtual na Hardware

Ang virtual na IoT device ay gagamit ng simulated Grove Digital Humidity and Temperature sensor. Pinapanatili nitong pareho ang lab na ito sa paggamit ng Raspberry Pi na may pisikal na Grove DHT11 sensor.

Ang sensor ay pinagsasama ang **sensor ng temperatura** at **sensor ng halumigmig**, ngunit sa lab na ito, ang interes mo lamang ay ang bahagi ng sensor ng temperatura. Sa isang pisikal na IoT device, ang sensor ng temperatura ay isang [thermistor](https://wikipedia.org/wiki/Thermistor) na sumusukat sa temperatura sa pamamagitan ng pag-detect ng pagbabago sa resistance habang nagbabago ang temperatura. Karaniwang digital ang mga sensor ng temperatura na internal na nagko-convert ng resistance na nasukat sa temperatura sa degrees Celsius (o Kelvin, o Fahrenheit).

### Idagdag ang mga sensor sa CounterFit

Upang gumamit ng virtual na sensor ng halumigmig at temperatura, kailangan mong idagdag ang dalawang sensor sa CounterFit app.

#### Gawain - idagdag ang mga sensor sa CounterFit

Idagdag ang mga sensor ng halumigmig at temperatura sa CounterFit app.

1. Gumawa ng bagong Python app sa iyong computer sa isang folder na tinatawag na `temperature-sensor` na may isang file na tinatawag na `app.py` at isang Python virtual environment, at idagdag ang CounterFit pip packages.

    > ⚠️ Maaari mong tingnan ang [mga instruksyon para sa paggawa at pag-setup ng CounterFit Python project sa aralin 1 kung kinakailangan](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Mag-install ng karagdagang Pip package upang mag-install ng CounterFit shim para sa DHT11 sensor. Siguraduhing ini-install mo ito mula sa terminal na may activated na virtual environment.

    ```sh
    pip install counterfit-shims-seeed-python-dht
    ```

1. Siguraduhing tumatakbo ang CounterFit web app.

1. Gumawa ng sensor ng halumigmig:

    1. Sa *Create sensor* box sa *Sensors* pane, i-drop down ang *Sensor type* box at piliin ang *Humidity*.

    1. Iwanang nakatakda ang *Units* sa *Percentage*.

    1. Siguraduhing ang *Pin* ay nakatakda sa *5*.

    1. Piliin ang **Add** button upang gumawa ng sensor ng halumigmig sa Pin 5.

    ![Ang mga setting ng sensor ng halumigmig](../../../../../translated_images/tl/counterfit-create-humidity-sensor.2750e27b6f30e09cf4e22101defd5252710717620816ab41ba688f91f757c49a.png)

    Ang sensor ng halumigmig ay malilikha at lilitaw sa listahan ng mga sensor.

    ![Ang sensor ng halumigmig na nalikha](../../../../../translated_images/tl/counterfit-humidity-sensor.7b12f7f339e430cb26c8211d2dba4ef75261b353a01da0932698b5bebd693f27.png)

1. Gumawa ng sensor ng temperatura:

    1. Sa *Create sensor* box sa *Sensors* pane, i-drop down ang *Sensor type* box at piliin ang *Temperature*.

    1. Iwanang nakatakda ang *Units* sa *Celsius*.

    1. Siguraduhing ang *Pin* ay nakatakda sa *6*.

    1. Piliin ang **Add** button upang gumawa ng sensor ng temperatura sa Pin 6.

    ![Ang mga setting ng sensor ng temperatura](../../../../../translated_images/tl/counterfit-create-temperature-sensor.199350ed34f7343d79dccbe95eaf6c11d2121f03d1c35ab9613b330c23f39b29.png)

    Ang sensor ng temperatura ay malilikha at lilitaw sa listahan ng mga sensor.

    ![Ang sensor ng temperatura na nalikha](../../../../../translated_images/tl/counterfit-temperature-sensor.f0560236c96a9016bafce7f6f792476fe3367bc6941a1f7d5811d144d4bcbfff.png)

## I-program ang temperature sensor app

Ang temperature sensor app ay maaari nang i-program gamit ang CounterFit sensors.

### Gawain - i-program ang temperature sensor app

I-program ang temperature sensor app.

1. Siguraduhing bukas ang `temperature-sensor` app sa VS Code.

1. Buksan ang file na `app.py`.

1. Idagdag ang sumusunod na code sa itaas ng `app.py` upang ikonekta ang app sa CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Idagdag ang sumusunod na code sa file na `app.py` upang i-import ang mga kinakailangang library:

    ```python
    import time
    from counterfit_shims_seeed_python_dht import DHT
    ```

    Ang `from seeed_dht import DHT` na statement ay nag-i-import ng `DHT` sensor class upang makipag-ugnayan sa isang virtual Grove temperature sensor gamit ang shim mula sa `counterfit_shims_seeed_python_dht` module.

1. Idagdag ang sumusunod na code pagkatapos ng code sa itaas upang gumawa ng instance ng class na namamahala sa virtual na sensor ng halumigmig at temperatura:

    ```python
    sensor = DHT("11", 5)
    ```

    Ito ay nagdeklara ng instance ng `DHT` class na namamahala sa virtual na **D**igital **H**umidity at **T**emperature sensor. Ang unang parameter ay nagsasabi sa code na ang sensor na ginagamit ay isang virtual na *DHT11* sensor. Ang pangalawang parameter ay nagsasabi sa code na ang sensor ay nakakonekta sa port `5`.

    > 💁 Ang CounterFit ay nagsi-simulate ng pinagsamang sensor ng halumigmig at temperatura sa pamamagitan ng pagkonekta sa 2 sensor, isang sensor ng halumigmig sa pin na ibinigay kapag ang `DHT` class ay nalikha, at isang sensor ng temperatura na tumatakbo sa susunod na pin. Kung ang sensor ng halumigmig ay nasa pin 5, inaasahan ng shim na ang sensor ng temperatura ay nasa pin 6.

1. Magdagdag ng infinite loop pagkatapos ng code sa itaas upang i-poll ang halaga ng sensor ng temperatura at i-print ito sa console:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    Ang tawag sa `sensor.read()` ay nagbabalik ng tuple ng halumigmig at temperatura. Kailangan mo lamang ang halaga ng temperatura, kaya ang halumigmig ay hindi pinapansin. Ang halaga ng temperatura ay pagkatapos ay ipinapakita sa console.

1. Magdagdag ng maliit na sleep na sampung segundo sa dulo ng `loop` dahil hindi kailangang patuloy na suriin ang mga antas ng temperatura. Ang sleep ay nagpapababa ng power consumption ng device.

    ```python
    time.sleep(10)
    ```

1. Mula sa VS Code Terminal na may activated na virtual environment, patakbuhin ang sumusunod upang patakbuhin ang iyong Python app:

    ```sh
    python app.py
    ```

1. Mula sa CounterFit app, baguhin ang halaga ng sensor ng temperatura na babasahin ng app. Maaari mo itong gawin sa dalawang paraan:

    * Maglagay ng numero sa *Value* box para sa sensor ng temperatura, pagkatapos ay piliin ang **Set** button. Ang numerong inilagay mo ang magiging halaga na ibabalik ng sensor.

    * I-check ang *Random* checkbox, at maglagay ng *Min* at *Max* na halaga, pagkatapos ay piliin ang **Set** button. Tuwing babasahin ng sensor ang halaga, magbabasa ito ng random na numero sa pagitan ng *Min* at *Max*.

    Makikita mo ang mga halagang inilagay mo na lumalabas sa console. Baguhin ang *Value* o ang *Random* settings upang makita ang pagbabago ng halaga.

    ```output
    (.venv) ➜  temperature-sensor python app.py
    Temperature 28.25°C
    Temperature 30.71°C
    Temperature 25.17°C
    ```

> 💁 Maaari mong makita ang code na ito sa [code-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/virtual-device) folder.

😀 Tagumpay ang iyong temperature sensor program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.