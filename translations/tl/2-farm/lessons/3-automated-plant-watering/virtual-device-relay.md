<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f8f541ee945545017a51aaf309aa37c3",
  "translation_date": "2025-08-27T21:39:30+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/virtual-device-relay.md",
  "language_code": "tl"
}
-->
# Kontrolin ang isang relay - Virtual na IoT Hardware

Sa bahaging ito ng aralin, magdadagdag ka ng relay sa iyong virtual na IoT device bukod sa soil moisture sensor, at kokontrolin ito batay sa antas ng soil moisture.

## Virtual na Hardware

Ang virtual na IoT device ay gagamit ng simulated Grove relay. Pinapanatili nitong pareho ang lab na ito sa paggamit ng Raspberry Pi na may pisikal na Grove relay.

Sa isang pisikal na IoT device, ang relay ay karaniwang-open relay (ibig sabihin, ang output circuit ay bukas o hindi konektado kapag walang signal na ipinadala sa relay). Ang ganitong relay ay maaaring mag-handle ng output circuits hanggang 250V at 10A.

### Idagdag ang relay sa CounterFit

Upang gumamit ng virtual na relay, kailangan mo itong idagdag sa CounterFit app.

#### Gawain

Idagdag ang relay sa CounterFit app.

1. Buksan ang proyekto na `soil-moisture-sensor` mula sa nakaraang aralin sa VS Code kung hindi pa ito bukas. Magdadagdag ka sa proyektong ito.

1. Siguraduhing tumatakbo ang CounterFit web app.

1. Gumawa ng relay:

    1. Sa *Create actuator* box sa *Actuators* pane, i-drop down ang *Actuator type* box at piliin ang *Relay*.

    1. Itakda ang *Pin* sa *5*.

    1. Piliin ang **Add** button upang gumawa ng relay sa Pin 5.

    ![Ang mga setting ng relay](../../../../../translated_images/tl/counterfit-create-relay.fa7c40fd0f2f6afc33b35ea94fcb235085be4861e14e3fe6b9b7bcfc82d1c888.png)

    Ang relay ay malilikha at lilitaw sa listahan ng actuators.

    ![Ang relay na nalikha](../../../../../translated_images/tl/counterfit-relay.bbf74c1dbdc8b9acd983367fcbd06703a402aefef6af54ddb28e11307ba8a12c.png)

## I-program ang relay

Ang soil moisture sensor app ay maaari nang i-program upang gamitin ang virtual na relay.

### Gawain

I-program ang virtual na device.

1. Buksan ang proyekto na `soil-moisture-sensor` mula sa nakaraang aralin sa VS Code kung hindi pa ito bukas. Magdadagdag ka sa proyektong ito.

1. Idagdag ang sumusunod na code sa file na `app.py` sa ibaba ng mga umiiral na imports:

    ```python
    from counterfit_shims_grove.grove_relay import GroveRelay
    ```

    Ang pahayag na ito ay nag-i-import ng `GroveRelay` mula sa Grove Python shim libraries upang makipag-ugnayan sa virtual na Grove relay.

1. Idagdag ang sumusunod na code sa ibaba ng deklarasyon ng klase na `ADC` upang gumawa ng instance ng `GroveRelay`:

    ```python
    relay = GroveRelay(5)
    ```

    Gumagawa ito ng relay gamit ang pin **5**, ang pin na konektado mo sa relay.

1. Upang subukan kung gumagana ang relay, idagdag ang sumusunod sa `while True:` loop:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    Ang code ay i-o-on ang relay, maghihintay ng 0.5 segundo, pagkatapos ay i-o-off ang relay.

1. Patakbuhin ang Python app. Ang relay ay mag-o-on at mag-o-off tuwing 10 segundo, na may kalahating segundo na delay sa pagitan ng pag-on at pag-off. Makikita mo ang virtual na relay sa CounterFit app na mag-close at mag-open habang ang relay ay nag-o-on at nag-o-off.

    ![Ang virtual na relay na nag-o-on at nag-o-off](../../../../../images/virtual-relay-turn-on-off.gif)

## Kontrolin ang relay mula sa soil moisture

Ngayon na gumagana ang relay, maaari na itong kontrolin batay sa mga readings ng soil moisture.

### Gawain

Kontrolin ang relay.

1. Tanggalin ang 3 linya ng code na idinagdag mo upang subukan ang relay. Palitan ang mga ito ng sumusunod na code sa parehong lugar:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    Ang code na ito ay sinusuri ang antas ng soil moisture mula sa soil moisture sensor. Kapag ito ay higit sa 450, i-o-on nito ang relay, at i-o-off ito kapag bumaba sa 450.

    > 💁 Tandaan na ang capacitive soil moisture sensor ay nagbabasa ng mas mababang antas ng soil moisture kapag mas maraming moisture ang nasa lupa, at kabaliktaran.

1. Patakbuhin ang Python app. Makikita mo ang relay na mag-o-on o mag-o-off depende sa antas ng soil moisture. Baguhin ang *Value* o ang *Random* settings para sa soil moisture sensor upang makita ang pagbabago ng halaga.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Makikita mo ang code na ito sa [code-relay/virtual-device](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/virtual-device) folder.

😀 Tagumpay ang iyong virtual na soil moisture sensor na kumokontrol sa relay program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.