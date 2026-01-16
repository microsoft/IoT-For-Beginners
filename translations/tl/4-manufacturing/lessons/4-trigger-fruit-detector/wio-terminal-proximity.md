<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "288aebb0c59f7be1d2719b8f9660a313",
  "translation_date": "2025-08-27T21:20:43+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/wio-terminal-proximity.md",
  "language_code": "tl"
}
-->
# Tukuyin ang Proximity - Wio Terminal

Sa bahaging ito ng aralin, magdadagdag ka ng proximity sensor sa iyong Wio Terminal, at babasahin ang distansya mula rito.

## Hardware

Kailangan ng Wio Terminal ng isang proximity sensor.

Ang sensor na gagamitin mo ay isang [Grove Time of Flight distance sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Ang sensor na ito ay gumagamit ng laser ranging module upang matukoy ang distansya. May saklaw ito mula 10mm hanggang 2000mm (1cm - 2m), at mag-uulat ng mga halaga sa saklaw na ito nang medyo tumpak, kung saan ang mga distansya na higit sa 1000mm ay iuulat bilang 8109mm.

Ang laser rangefinder ay nasa likod ng sensor, sa kabaligtaran ng Grove socket.

Ito ay isang I²C sensor.

### Ikonekta ang time of flight sensor

Ang Grove time of flight sensor ay maaaring ikonekta sa Wio Terminal.

#### Gawain - ikonekta ang time of flight sensor

Ikonekta ang time of flight sensor.

![Isang Grove time of flight sensor](../../../../../translated_images/tl/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.png)

1. Ipasok ang isang dulo ng Grove cable sa socket ng time of flight sensor. Isang paraan lamang ito maaaring ipasok.

1. Habang ang Wio Terminal ay hindi nakakonekta sa iyong computer o iba pang power supply, ikonekta ang kabilang dulo ng Grove cable sa kaliwang Grove socket ng Wio Terminal habang nakaharap ka sa screen. Ito ang socket na pinakamalapit sa power button. Ito ay isang pinagsamang digital at I²C socket.

![Ang Grove time of flight sensor na nakakonekta sa kaliwang socket](../../../../../translated_images/tl/wio-time-of-flight-sensor.c4c182131d2ea73d.webp)

1. Maaari mo nang ikonekta ang Wio Terminal sa iyong computer.

## Iprograma ang time of flight sensor

Ang Wio Terminal ay maaari nang iprograma upang magamit ang nakakonektang time of flight sensor.

### Gawain - iprograma ang time of flight sensor

1. Gumawa ng bagong Wio Terminal project gamit ang PlatformIO. Tawagin ang proyektong ito na `distance-sensor`. Magdagdag ng code sa `setup` function upang i-configure ang serial port.

1. Magdagdag ng library dependency para sa Seeed Grove time of flight distance sensor library sa `platformio.ini` file ng proyekto:

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

1. Sa `main.cpp`, idagdag ang sumusunod sa ibaba ng umiiral na mga include directives upang ideklara ang isang instance ng `Seeed_vl53l0x` class para makipag-ugnayan sa time of flight sensor:

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

1. Idagdag ang sumusunod sa ibaba ng `setup` function upang i-initialize ang sensor:

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

1. Sa `loop` function, basahin ang isang halaga mula sa sensor:

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    Ang code na ito ay nag-i-initialize ng isang data structure upang basahin ang data, pagkatapos ay ipinapasa ito sa `PerformSingleRangingMeasurement` method kung saan ito pupunuin ng sukat ng distansya.

1. Sa ibaba nito, isulat ang sukat ng distansya, pagkatapos ay mag-delay ng 1 segundo:

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

1. I-build, i-upload, at patakbuhin ang code na ito. Makikita mo ang mga sukat ng distansya gamit ang serial monitor. Ilapit ang mga bagay sa sensor at makikita mo ang sukat ng distansya:

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Ang rangefinder ay nasa likod ng sensor, kaya siguraduhing gamitin ang tamang bahagi kapag sumusukat ng distansya.

    ![Ang rangefinder sa likod ng time of flight sensor na nakaturo sa isang saging](../../../../../translated_images/tl/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 Makikita mo ang code na ito sa [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal) folder.

😀 Tagumpay ang iyong proximity sensor program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.