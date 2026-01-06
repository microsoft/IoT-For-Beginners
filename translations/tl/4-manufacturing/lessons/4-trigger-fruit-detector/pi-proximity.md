<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6145a1d791731c8a9d0afd0a1bae5108",
  "translation_date": "2025-08-27T21:19:49+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/pi-proximity.md",
  "language_code": "tl"
}
-->
# Tukuyin ang Proximity - Raspberry Pi

Sa bahaging ito ng aralin, magdadagdag ka ng proximity sensor sa iyong Raspberry Pi, at babasahin ang distansya mula rito.

## Kagamitan

Kailangan ng Raspberry Pi ng proximity sensor.

Ang sensor na gagamitin mo ay ang [Grove Time of Flight distance sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Ang sensor na ito ay gumagamit ng laser ranging module upang matukoy ang distansya. May saklaw ang sensor na 10mm hanggang 2000mm (1cm - 2m), at mag-uulat ng mga halaga sa saklaw na iyon nang medyo tumpak, na ang mga distansya na higit sa 1000mm ay iniulat bilang 8109mm.

Ang laser rangefinder ay nasa likod ng sensor, sa kabaligtaran ng Grove socket.

Ito ay isang I²C sensor.

### Ikonekta ang Time of Flight Sensor

Ang Grove time of flight sensor ay maaaring ikonekta sa Raspberry Pi.

#### Gawain - Ikonekta ang Time of Flight Sensor

Ikonekta ang time of flight sensor.

![Isang Grove time of flight sensor](../../../../../translated_images/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.tl.png)

1. Ipasok ang isang dulo ng Grove cable sa socket ng time of flight sensor. Isang paraan lamang ang tamang pagpasok nito.

1. Kapag naka-off ang Raspberry Pi, ikonekta ang kabilang dulo ng Grove cable sa isa sa mga I²C socket na may markang **I²C** sa Grove Base hat na nakakabit sa Pi. Ang mga socket na ito ay nasa ibabang hilera, sa kabaligtaran ng GPI pins at malapit sa camera cable slot.

![Ang Grove time of flight sensor na nakakonekta sa I squared C socket](../../../../../translated_images/pi-time-of-flight-sensor.58c8dc04eb3bfb57.tl.png)

## Iprograma ang Time of Flight Sensor

Ngayon ay maaaring i-program ang Raspberry Pi upang magamit ang nakakabit na time of flight sensor.

### Gawain - Iprograma ang Time of Flight Sensor

Iprograma ang device.

1. I-on ang Pi at hintaying mag-boot.

1. Buksan ang `fruit-quality-detector` code sa VS Code, alinman direkta sa Pi, o kumonekta gamit ang Remote SSH extension.

1. I-install ang rpi-vl53l0x Pip package, isang Python package na nakikipag-ugnayan sa VL53L0X time-of-flight distance sensor. I-install ito gamit ang pip command na ito:

    ```sh
    pip install rpi-vl53l0x
    ```

1. Gumawa ng bagong file sa proyektong ito na tinatawag na `distance-sensor.py`.

    > 💁 Isang madaling paraan upang mag-simulate ng maraming IoT devices ay gawin ang bawat isa sa ibang Python file, pagkatapos ay patakbuhin ang mga ito nang sabay-sabay.

1. Idagdag ang sumusunod na code sa file na ito:

    ```python
    import time
    
    from grove.i2c import Bus
    from rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Ini-import nito ang Grove I²C bus library, at isang sensor library para sa core sensor hardware na built-in sa Grove time of flight sensor.

1. Sa ibaba nito, idagdag ang sumusunod na code upang ma-access ang sensor:

    ```python
    distance_sensor = VL53L0X(bus = Bus().bus)
    distance_sensor.begin()    
    ```

    Ang code na ito ay nagdeklara ng distance sensor gamit ang Grove I²C bus, pagkatapos ay sinisimulan ang sensor.

1. Sa wakas, magdagdag ng infinite loop upang basahin ang distansya:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Ang code na ito ay naghihintay ng halaga na handang basahin mula sa sensor, pagkatapos ay ipinapakita ito sa console.

1. Patakbuhin ang code na ito.

    > 💁 Huwag kalimutan na ang file na ito ay tinatawag na `distance-sensor.py`! Siguraduhing patakbuhin ito gamit ang Python, hindi `app.py`.

1. Makikita mo ang mga sukat ng distansya na lumalabas sa console. Ilapit ang mga bagay sa sensor at makikita mo ang sukat ng distansya:

    ```output
    pi@raspberrypi:~/fruit-quality-detector $ python3 distance_sensor.py 
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Ang rangefinder ay nasa likod ng sensor, kaya siguraduhing gamitin ang tamang bahagi kapag sumusukat ng distansya.

    ![Ang rangefinder sa likod ng time of flight sensor na nakatutok sa isang saging](../../../../../translated_images/time-of-flight-banana.079921ad8b1496e4.tl.png)

> 💁 Matatagpuan mo ang code na ito sa [code-proximity/pi](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/pi) folder.

😀 Tagumpay ang iyong proximity sensor program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.