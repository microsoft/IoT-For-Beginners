<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c527ce85d69b1a3875366ec61cbed8aa",
  "translation_date": "2025-08-28T00:26:23+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-commands.md",
  "language_code": "tl"
}
-->
# Kontrolin ang iyong nightlight gamit ang Internet - Virtual IoT Hardware at Raspberry Pi

Sa bahaging ito ng aralin, magse-subscribe ka sa mga utos na ipinapadala mula sa isang MQTT broker papunta sa iyong Raspberry Pi o virtual na IoT device.

## Mag-subscribe sa mga utos

Ang susunod na hakbang ay mag-subscribe sa mga utos na ipinapadala mula sa MQTT broker at tumugon sa mga ito.

### Gawain

Mag-subscribe sa mga utos.

1. Buksan ang nightlight project sa VS Code.

1. Kung gumagamit ka ng virtual na IoT device, siguraduhing tumatakbo ang terminal sa virtual environment. Kung gumagamit ka ng Raspberry Pi, hindi mo kailangang gumamit ng virtual environment.

1. Idagdag ang sumusunod na code pagkatapos ng mga definition ng `client_telemetry_topic`:

    ```python
    server_command_topic = id + '/commands'
    ```

    Ang `server_command_topic` ay ang MQTT topic kung saan magse-subscribe ang device upang makatanggap ng mga utos para sa LED.

1. Idagdag ang sumusunod na code sa itaas ng main loop, pagkatapos ng linya na `mqtt_client.loop_start()`:

    ```python
    def handle_command(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
        if payload['led_on']:
            led.on()
        else:
            led.off()
    
    mqtt_client.subscribe(server_command_topic)
    mqtt_client.on_message = handle_command
    ```

    Ang code na ito ay nagde-define ng isang function, `handle_command`, na nagbabasa ng mensahe bilang isang JSON document at hinahanap ang halaga ng property na `led_on`. Kung ito ay nakatakda sa `True`, ang LED ay bubuksan; kung hindi, ito ay papatayin.

    Ang MQTT client ay magse-subscribe sa topic kung saan magpapadala ng mga mensahe ang server at itatakda ang function na `handle_command` upang tawagin kapag may natanggap na mensahe.

    > 💁 Ang `on_message` handler ay tinatawag para sa lahat ng mga topic na naka-subscribe. Kung sa hinaharap ay magsusulat ka ng code na nakikinig sa maraming topic, maaari mong makuha ang topic kung saan ipinadala ang mensahe mula sa `message` object na ipinasa sa handler function.

1. Patakbuhin ang code sa parehong paraan kung paano mo pinatakbo ang code mula sa nakaraang bahagi ng assignment. Kung gumagamit ka ng virtual na IoT device, siguraduhing tumatakbo ang CounterFit app at ang light sensor at LED ay nalikha sa tamang mga pin.

1. Ayusin ang mga antas ng liwanag na nadedetect ng iyong pisikal o virtual na device. Ang mga natatanggap na mensahe at ipinapadalang utos ay isusulat sa terminal. Ang LED ay bubuksan at papatayin depende sa antas ng liwanag.

> 💁 Makikita mo ang code na ito sa [code-commands/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/virtual-device) folder o sa [code-commands/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/pi) folder.

😀 Matagumpay mong na-code ang iyong device upang tumugon sa mga utos mula sa isang MQTT broker.

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.