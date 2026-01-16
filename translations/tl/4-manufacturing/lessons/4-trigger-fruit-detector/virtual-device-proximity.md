<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e9f05bdc50a40fd924b1d66934471bf",
  "translation_date": "2025-08-27T21:21:33+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/virtual-device-proximity.md",
  "language_code": "tl"
}
-->
# Tukuyin ang Proximity - Virtual IoT Hardware

Sa bahaging ito ng aralin, magdadagdag ka ng proximity sensor sa iyong virtual na IoT device, at babasahin ang distansya mula rito.

## Hardware

Ang virtual na IoT device ay gagamit ng simulated distance sensor.

Sa isang pisikal na IoT device, gagamit ka ng sensor na may laser ranging module upang matukoy ang distansya.

### Magdagdag ng distance sensor sa CounterFit

Upang gumamit ng virtual distance sensor, kailangan mong magdagdag ng isa sa CounterFit app.

#### Gawain - magdagdag ng distance sensor sa CounterFit

Magdagdag ng distance sensor sa CounterFit app.

1. Buksan ang `fruit-quality-detector` code sa VS Code, at tiyaking naka-activate ang virtual environment.

1. Mag-install ng karagdagang Pip package upang mag-install ng CounterFit shim na maaaring makipag-usap sa distance sensors sa pamamagitan ng pagsasagawa ng [rpi-vl53l0x Pip package](https://pypi.org/project/rpi-vl53l0x/), isang Python package na nakikipag-ugnayan sa [VL53L0X time-of-flight distance sensor](https://wiki.seeedstudio.com/Grove-Time_of_Flight_Distance_Sensor-VL53L0X/). Siguraduhing ini-install mo ito mula sa terminal na may naka-activate na virtual environment.

    ```sh
    pip install counterfit-shims-rpi-vl53l0x
    ```

1. Siguraduhing tumatakbo ang CounterFit web app.

1. Gumawa ng distance sensor:

    1. Sa *Create sensor* box sa *Sensors* pane, i-drop down ang *Sensor type* box at piliin ang *Distance*.

    1. Iwanan ang *Units* bilang `Millimeter`.

    1. Ang sensor na ito ay isang I²C sensor, kaya itakda ang address sa `0x29`. Kung gumamit ka ng pisikal na VL53L0X sensor, ito ay hardcoded sa address na ito.

    1. Piliin ang **Add** button upang gumawa ng distance sensor.

    ![Ang mga setting ng distance sensor](../../../../../translated_images/tl/counterfit-create-distance-sensor.967c9fb98f27888d95920c9784d004c972490eb71f70397fe13bd70a79a879a3.png)

    Ang distance sensor ay malilikha at lilitaw sa listahan ng mga sensor.

    ![Ang nalikhang distance sensor](../../../../../translated_images/tl/counterfit-distance-sensor.079eefeeea0b68afc36431ce8fcbe2f09a7e4916ed1cd5cb30e696db53bc18fa.png)

## I-program ang distance sensor

Ang virtual na IoT device ay maaari nang i-program upang gamitin ang simulated distance sensor.

### Gawain - i-program ang time of flight sensor

1. Gumawa ng bagong file sa `fruit-quality-detector` project na tinatawag na `distance-sensor.py`.

    > 💁 Isang madaling paraan upang mag-simulate ng maraming IoT devices ay gawin ang bawat isa sa ibang Python file, pagkatapos ay patakbuhin ang mga ito nang sabay-sabay.

1. Simulan ang koneksyon sa CounterFit gamit ang sumusunod na code:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Idagdag ang sumusunod na code sa ibaba nito:

    ```python
    import time
    
    from counterfit_shims_rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Ina-import nito ang sensor library shim para sa VL53L0X time of flight sensor.

1. Sa ibaba nito, idagdag ang sumusunod na code upang ma-access ang sensor:

    ```python
    distance_sensor = VL53L0X()
    distance_sensor.begin()
    ```

    Ang code na ito ay nagdeklara ng distance sensor, pagkatapos ay sinisimulan ang sensor.

1. Sa wakas, magdagdag ng infinite loop upang basahin ang distansya:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Ang code na ito ay naghihintay ng value na handang basahin mula sa sensor, pagkatapos ay ipinapakita ito sa console.

1. Patakbuhin ang code na ito.

    > 💁 Huwag kalimutan na ang file na ito ay tinatawag na `distance-sensor.py`! Siguraduhing patakbuhin ito gamit ang Python, hindi `app.py`.

1. Makikita mo ang mga sukat ng distansya na lumalabas sa console. Baguhin ang value sa CounterFit upang makita ang pagbabago ng value na ito, o gumamit ng random values.

    ```output
    (.venv) ➜  fruit-quality-detector python distance-sensor.py 
    Distance = 37 mm
    Distance = 42 mm
    Distance = 29 mm
    ```

> 💁 Maaari mong makita ang code na ito sa [code-proximity/virtual-iot-device](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/virtual-iot-device) folder.

😀 Tagumpay ang iyong proximity sensor program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.