<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7678f7c67b97ee52d5727496dcd7d346",
  "translation_date": "2025-08-27T21:31:17+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/pi-temp.md",
  "language_code": "tl"
}
-->
# Sukatin ang temperatura - Raspberry Pi

Sa bahaging ito ng aralin, magdadagdag ka ng temperature sensor sa iyong Raspberry Pi.

## Kagamitan

Ang sensor na gagamitin mo ay isang [DHT11 humidity at temperature sensor](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), na pinagsasama ang 2 sensor sa isang pakete. Ito ay medyo popular, at maraming mga sensor na komersyal na magagamit ang pinagsasama ang temperatura, halumigmig, at minsan ang atmospheric pressure. Ang temperature sensor component ay isang negative temperature coefficient (NTC) thermistor, isang thermistor kung saan bumababa ang resistance habang tumataas ang temperatura.

Ito ay isang digital sensor, kaya mayroon itong onboard ADC upang lumikha ng digital signal na naglalaman ng data ng temperatura at halumigmig na mababasa ng microcontroller.

### Ikonekta ang temperature sensor

Ang Grove temperature sensor ay maaaring ikonekta sa Raspberry Pi.

#### Gawain

Ikonekta ang temperature sensor

![Isang Grove temperature sensor](../../../../../translated_images/tl/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.png)

1. Ipasok ang isang dulo ng Grove cable sa socket ng humidity at temperature sensor. Isa lang ang tamang paraan para maipasok ito.

1. Kapag naka-off ang Raspberry Pi, ikonekta ang kabilang dulo ng Grove cable sa digital socket na may markang **D5** sa Grove Base hat na nakakabit sa Pi. Ang socket na ito ay pangalawa mula sa kaliwa, sa hanay ng mga socket malapit sa GPIO pins.

![Ang Grove temperature sensor na nakakonekta sa socket A0](../../../../../translated_images/tl/pi-temperature-sensor.3ff82fff672c8e56.webp)

## Iprograma ang temperature sensor

Ang device ay maaari nang iprograma upang magamit ang nakakabit na temperature sensor.

### Gawain

Iprograma ang device.

1. I-on ang Pi at hintaying mag-boot ito.

1. I-launch ang VS Code, direkta sa Pi, o kumonekta gamit ang Remote SSH extension.

    > ⚠️ Maaari mong tingnan ang [mga instruksyon para sa pag-setup at pag-launch ng VS Code sa aralin 1 kung kinakailangan](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Mula sa terminal, gumawa ng bagong folder sa home directory ng `pi` user na tinatawag na `temperature-sensor`. Gumawa ng file sa folder na ito na tinatawag na `app.py`:

    ```sh
    mkdir temperature-sensor
    cd temperature-sensor
    touch app.py
    ```

1. Buksan ang folder na ito sa VS Code.

1. Upang magamit ang temperature at humidity sensor, kailangang mag-install ng karagdagang Pip package. Mula sa Terminal sa VS Code, patakbuhin ang sumusunod na command upang i-install ang Pip package na ito sa Pi:

    ```sh
    pip3 install seeed-python-dht
    ```

1. Idagdag ang sumusunod na code sa `app.py` file upang i-import ang mga kinakailangang library:

    ```python
    import time
    from seeed_dht import DHT
    ```

    Ang `from seeed_dht import DHT` na statement ay nag-i-import ng `DHT` sensor class upang makipag-ugnayan sa Grove temperature sensor mula sa `seeed_dht` module.

1. Idagdag ang sumusunod na code pagkatapos ng code sa itaas upang lumikha ng instance ng klase na namamahala sa temperature sensor:

    ```python
    sensor = DHT("11", 5)
    ```

    Ito ay nagdeklara ng instance ng `DHT` class na namamahala sa **D**igital **H**umidity at **T**emperature sensor. Ang unang parameter ay nagsasabi sa code na ang sensor na ginagamit ay ang *DHT11* sensor - sinusuportahan ng library na ginagamit mo ang iba pang variant ng sensor na ito. Ang pangalawang parameter ay nagsasabi sa code na ang sensor ay nakakonekta sa digital port `D5` sa Grove base hat.

    > ✅ Tandaan, ang lahat ng socket ay may natatanging pin numbers. Ang pins 0, 2, 4, at 6 ay analog pins, ang pins 5, 16, 18, 22, 24, at 26 ay digital pins.

1. Magdagdag ng infinite loop pagkatapos ng code sa itaas upang kunin ang temperature sensor value at i-print ito sa console:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    Ang tawag sa `sensor.read()` ay nagbabalik ng tuple ng humidity at temperature. Kailangan mo lang ang temperature value, kaya ang humidity ay hindi papansinin. Ang temperature value ay pagkatapos ay ipi-print sa console.

1. Magdagdag ng maliit na sleep na sampung segundo sa dulo ng `loop` dahil hindi kailangang suriin ang temperature levels nang tuloy-tuloy. Ang sleep ay nakababawas sa power consumption ng device.

    ```python
    time.sleep(10)
    ```

1. Mula sa VS Code Terminal, patakbuhin ang sumusunod upang patakbuhin ang iyong Python app:

    ```sh
    python3 app.py
    ```

    Makikita mo ang mga temperature values na lumalabas sa console. Gumamit ng isang bagay upang painitin ang sensor, tulad ng pagdiin ng iyong hinlalaki dito, o paggamit ng fan upang makita ang pagbabago ng mga values:

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py 
    Temperature 26°C
    Temperature 26°C
    Temperature 28°C
    Temperature 30°C
    Temperature 32°C
    ```

> 💁 Maaari mong makita ang code na ito sa [code-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/pi) folder.

😀 Tagumpay ang iyong temperature sensor program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.