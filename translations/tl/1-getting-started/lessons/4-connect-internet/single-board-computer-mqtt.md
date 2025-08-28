<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "90fb93446e03c38f3c0e4009c2471906",
  "translation_date": "2025-08-28T00:27:41+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md",
  "language_code": "tl"
}
-->
# Kontrolin ang Iyong Nightlight sa Internet - Virtual na IoT Hardware at Raspberry Pi

Kailangang i-code ang IoT device upang makipag-ugnayan sa *test.mosquitto.org* gamit ang MQTT para magpadala ng telemetry values mula sa light sensor reading, at tumanggap ng mga utos para kontrolin ang LED.

Sa bahaging ito ng aralin, ikokonekta mo ang iyong Raspberry Pi o virtual na IoT device sa isang MQTT broker.

## I-install ang MQTT client package

Upang makipag-ugnayan sa MQTT broker, kailangan mong mag-install ng MQTT library pip package sa iyong Pi, o sa iyong virtual environment kung gumagamit ka ng virtual na device.

### Gawain

I-install ang pip package

1. Buksan ang nightlight project sa VS Code.

1. Kung gumagamit ka ng virtual na IoT device, siguraduhing tumatakbo ang terminal sa virtual environment. Kung gumagamit ka ng Raspberry Pi, hindi mo kailangang gumamit ng virtual environment.

1. Patakbuhin ang sumusunod na command upang i-install ang MQTT pip package:

    ```sh
    pip3 install paho-mqtt
    ```

## I-code ang device

Handa nang i-code ang device.

### Gawain

Isulat ang code para sa device.

1. Idagdag ang sumusunod na import sa itaas ng file na `app.py`:

    ```python
    import paho.mqtt.client as mqtt
    ```

    Ang `paho.mqtt.client` library ay nagbibigay-daan sa iyong app na makipag-ugnayan gamit ang MQTT.

1. Idagdag ang sumusunod na code pagkatapos ng mga definition ng light sensor at LED:

    ```python
    id = '<ID>'

    client_name = id + 'nightlight_client'
    ```

    Palitan ang `<ID>` ng isang natatanging ID na gagamitin bilang pangalan ng device client na ito, at sa kalaunan para sa mga topic na ipo-publish at susuportahan ng device na ito. Ang *test.mosquitto.org* broker ay pampubliko at ginagamit ng maraming tao, kabilang ang ibang mga estudyante na gumagawa ng parehong assignment. Ang pagkakaroon ng natatanging MQTT client name at topic names ay nagsisiguro na hindi magka-clash ang iyong code sa iba. Kakailanganin mo rin ang ID na ito kapag gumagawa ka na ng server code sa susunod na bahagi ng assignment.

    > 💁 Maaari kang gumamit ng website tulad ng [GUIDGen](https://www.guidgen.com) upang makabuo ng natatanging ID.

    Ang `client_name` ay isang natatanging pangalan para sa MQTT client na ito sa broker.

1. Idagdag ang sumusunod na code sa ibaba ng bagong code na ito upang lumikha ng isang MQTT client object at kumonekta sa MQTT broker:

    ```python
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()

    print("MQTT connected!")
    ```

    Ang code na ito ay lumilikha ng client object, kumokonekta sa pampublikong MQTT broker, at nagsisimula ng isang processing loop na tumatakbo sa isang background thread na nakikinig para sa mga mensahe sa anumang subscribed topics.

1. Patakbuhin ang code sa parehong paraan tulad ng pagpapatakbo ng code mula sa nakaraang bahagi ng assignment. Kung gumagamit ka ng virtual na IoT device, siguraduhing tumatakbo ang CounterFit app at ang light sensor at LED ay nalikha sa tamang mga pin.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Light level: 0
    Light level: 0
    ```

> 💁 Makikita mo ang code na ito sa [code-mqtt/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/virtual-device) folder o sa [code-mqtt/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/pi) folder.

😀 Matagumpay mong naikonekta ang iyong device sa isang MQTT broker.

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, pakitandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa orihinal nitong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.