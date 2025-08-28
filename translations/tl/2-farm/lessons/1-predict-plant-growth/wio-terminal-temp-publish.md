<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-27T21:29:11+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "tl"
}
-->
# I-publish ang temperatura - Wio Terminal

Sa bahaging ito ng aralin, ipapadala mo ang mga halaga ng temperatura na natukoy ng Wio Terminal gamit ang MQTT upang magamit ito sa pag-compute ng GDD sa hinaharap.

## I-publish ang temperatura

Kapag nabasa na ang temperatura, maaari itong ipadala gamit ang MQTT sa isang 'server' code na magbabasa ng mga halaga at mag-iimbak ng mga ito para magamit sa pag-compute ng GDD. Ang mga microcontroller ay hindi awtomatikong kumukuha ng oras mula sa Internet o nagtatala ng oras gamit ang real-time clock, kaya kailangang i-program ang device para gawin ito, kung mayroon itong kinakailangang hardware.

Upang gawing mas simple para sa araling ito, ang oras ay hindi ipapadala kasama ng data ng sensor. Sa halip, maaaring idagdag ito ng server code kapag natanggap na ang mga mensahe.

### Gawain

I-program ang device upang maipadala ang data ng temperatura.

1. Buksan ang proyekto ng `temperature-sensor` Wio Terminal.

1. Ulitin ang mga hakbang na ginawa mo sa aralin 4 upang kumonekta sa MQTT at magpadala ng telemetry. Gagamitin mo ang parehong pampublikong Mosquitto broker.

    Ang mga hakbang para dito ay:

    - Idagdag ang Seeed WiFi at MQTT libraries sa `.ini` file
    - Idagdag ang config file at code para kumonekta sa WiFi
    - Idagdag ang code para kumonekta sa MQTT broker
    - Idagdag ang code para mag-publish ng telemetry

    > ⚠️ Tingnan ang [mga tagubilin para sa pagkonekta sa MQTT](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) at ang [mga tagubilin para sa pagpapadala ng telemetry](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) mula sa aralin 4 kung kinakailangan.

1. Siguraduhin na ang `CLIENT_NAME` sa `config.h` header file ay tumutugma sa proyektong ito:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. Para sa telemetry, sa halip na magpadala ng light value, ipadala ang temperatura na nabasa mula sa DHT sensor bilang isang property sa JSON document na tinatawag na `temperature` sa pamamagitan ng pagbabago sa `loop` function sa `main.cpp`:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. Hindi kailangang madalas basahin ang temperatura - hindi ito masyadong magbabago sa maikling panahon, kaya itakda ang `delay` sa `loop` function sa 10 minuto:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 Ang `delay` function ay tumatanggap ng oras sa milliseconds, kaya upang gawing mas madali itong basahin, ang halaga ay ipinapasa bilang resulta ng isang kalkulasyon. 1,000ms sa isang segundo, 60s sa isang minuto, kaya 10 x (60s sa isang minuto) x (1000ms sa isang segundo) ay nagbibigay ng 10 minutong delay.

1. I-upload ito sa iyong Wio Terminal, at gamitin ang serial monitor upang makita ang temperatura na ipinapadala sa MQTT broker.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"temperature":25}
    Sending telemetry {"temperature":25}
    ```

> 💁 Makikita mo ang code na ito sa [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal) folder.

😀 Matagumpay mong naipadala ang temperatura bilang telemetry mula sa iyong device.

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.