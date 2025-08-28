<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-28T00:25:47+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "tl"
}
-->
# Kontrolin ang iyong nightlight gamit ang Internet - Virtual na IoT Hardware at Raspberry Pi

Sa bahaging ito ng aralin, magpapadala ka ng telemetry na may mga antas ng liwanag mula sa iyong Raspberry Pi o virtual na IoT device papunta sa isang MQTT broker.

## Mag-publish ng telemetry

Ang susunod na hakbang ay gumawa ng isang JSON na dokumento na may telemetry at ipadala ito sa MQTT broker.

### Gawain

I-publish ang telemetry sa MQTT broker.

1. Buksan ang nightlight na proyekto sa VS Code.

1. Kung gumagamit ka ng virtual na IoT device, siguraduhing tumatakbo ang terminal sa virtual environment. Kung gumagamit ka ng Raspberry Pi, hindi mo kailangang gumamit ng virtual environment.

1. Idagdag ang sumusunod na import sa itaas ng file na `app.py`:

    ```python
    import json
    ```

    Ang library na `json` ay ginagamit upang i-encode ang telemetry bilang isang JSON na dokumento.

1. Idagdag ang sumusunod pagkatapos ng deklarasyon ng `client_name`:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    Ang `client_telemetry_topic` ay ang MQTT topic kung saan ipapadala ng device ang mga antas ng liwanag.

1. Palitan ang nilalaman ng `while True:` loop sa dulo ng file ng sumusunod:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    Ang code na ito ay nagbabalot ng antas ng liwanag sa isang JSON na dokumento at ipinapadala ito sa MQTT broker. Pagkatapos, ito ay magpapahinga upang bawasan ang dalas ng pagpapadala ng mga mensahe.

1. Patakbuhin ang code sa parehong paraan tulad ng ginawa mo sa nakaraang bahagi ng gawain. Kung gumagamit ka ng virtual na IoT device, siguraduhing tumatakbo ang CounterFit app at ang light sensor at LED ay nalikha sa tamang mga pin.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 Maaari mong mahanap ang code na ito sa [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) na folder o sa [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi) na folder.

😀 Matagumpay mong naipadala ang telemetry mula sa iyong device.

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.