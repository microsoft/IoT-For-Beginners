<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4efc74299e19f5d08f2f3f34451a11ba",
  "translation_date": "2025-08-27T21:26:34+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/single-board-computer-temp-publish.md",
  "language_code": "tl"
}
-->
# I-publish ang temperatura - Virtual IoT Hardware at Raspberry Pi

Sa bahaging ito ng aralin, ipapadala mo ang mga halaga ng temperatura na natukoy ng Raspberry Pi o Virtual IoT Device gamit ang MQTT upang magamit ito sa pag-compute ng GDD sa hinaharap.

## I-publish ang temperatura

Kapag nabasa na ang temperatura, maaari itong ipadala gamit ang MQTT sa isang 'server' code na magbabasa ng mga halaga at itatabi ang mga ito para magamit sa kalkulasyon ng GDD.

### Gawain - i-publish ang temperatura

I-program ang device upang maipadala ang data ng temperatura.

1. Buksan ang proyekto ng `temperature-sensor` app kung hindi pa ito bukas.

1. Ulitin ang mga hakbang na ginawa mo sa aralin 4 upang kumonekta sa MQTT at magpadala ng telemetry. Gagamitin mo ang parehong pampublikong Mosquitto broker.

    Ang mga hakbang para dito ay:

    - Idagdag ang MQTT pip package
    - Idagdag ang code para kumonekta sa MQTT broker
    - Idagdag ang code para mag-publish ng telemetry

    > ⚠️ Tingnan ang [mga tagubilin para sa pagkonekta sa MQTT](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md) at ang [mga tagubilin para sa pagpapadala ng telemetry](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md) mula sa aralin 4 kung kinakailangan.

1. Siguraduhin na ang `client_name` ay sumasalamin sa pangalan ng proyektong ito:

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. Para sa telemetry, sa halip na magpadala ng light value, ipadala ang halaga ng temperatura na nabasa mula sa DHT sensor bilang isang property sa JSON document na tinatawag na `temperature`:

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. Hindi kailangang madalas basahin ang halaga ng temperatura - hindi ito masyadong magbabago sa maikling panahon, kaya itakda ang `time.sleep` sa 10 minuto:

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 Ang `sleep` function ay tumatanggap ng oras sa segundo, kaya upang mas madaling basahin, ang halaga ay ipinapasa bilang resulta ng isang kalkulasyon. 60 segundo sa isang minuto, kaya 10 x (60 segundo sa isang minuto) ay nagbibigay ng 10 minutong delay.

1. Patakbuhin ang code sa parehong paraan tulad ng ginawa mo sa nakaraang bahagi ng assignment. Kung gumagamit ka ng virtual IoT device, siguraduhin na ang CounterFit app ay tumatakbo at ang mga humidity at temperature sensor ay nalikha sa tamang mga pin.

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 Makikita mo ang code na ito sa [code-publish-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/virtual-device) folder o sa [code-publish-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/pi) folder.

😀 Matagumpay mong naipadala ang temperatura bilang telemetry mula sa iyong device.

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.