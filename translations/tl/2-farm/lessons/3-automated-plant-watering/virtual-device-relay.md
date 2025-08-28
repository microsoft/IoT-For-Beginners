<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f8f541ee945545017a51aaf309aa37c3",
  "translation_date": "2025-08-28T01:55:15+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/virtual-device-relay.md",
  "language_code": "tl"
}
-->
# Kontrolin ang isang relay - Virtual na IoT Hardware

Sa bahaging ito ng aralin, magdadagdag ka ng relay sa iyong virtual na IoT device bukod sa soil moisture sensor, at kokontrolin ito batay sa antas ng soil moisture.

## Virtual na Hardware

Ang virtual na IoT device ay gagamit ng simulated na Grove relay. Pinapanatili nitong pareho ang lab na ito sa paggamit ng Raspberry Pi na may pisikal na Grove relay.

Sa isang pisikal na IoT device, ang relay ay karaniwang isang normally-open relay (ibig sabihin, ang output circuit ay bukas o hindi konektado kapag walang signal na ipinapadala sa relay). Ang ganitong uri ng relay ay kayang mag-handle ng output circuits hanggang 250V at 10A.

### Idagdag ang relay sa CounterFit

Upang gumamit ng virtual na relay, kailangan mo itong idagdag sa CounterFit app.

#### Gawain

Idagdag ang relay sa CounterFit app.

1. Buksan ang proyekto na `soil-moisture-sensor` mula sa nakaraang aralin sa VS Code kung hindi pa ito nakabukas. Magdadagdag ka sa proyektong ito.

1. Siguraduhing tumatakbo ang CounterFit web app.

1. Gumawa ng relay:

    1. Sa *Create actuator* na kahon sa *Actuators* pane, i-drop down ang *Actuator type* box at piliin ang *Relay*.

    1. Itakda ang *Pin* sa *5*.

    1. Piliin ang **Add** na button upang likhain ang relay sa Pin 5.

    ![Ang mga setting ng relay](../../../../../translated_images/counterfit-create-relay.fa7c40fd0f2f6afc33b35ea94fcb235085be4861e14e3fe6b9b7bcfc82d1c888.tl.png)

    Ang relay ay malilikha at lilitaw sa listahan ng actuators.

    ![Ang nalikhang relay](../../../../../translated_images/counterfit-relay.bbf74c1dbdc8b9acd983367fcbd06703a402aefef6af54ddb28e11307ba8a12c.tl.png)

## Iprograma ang relay

Ang soil moisture sensor app ay maaari nang iprograma upang gamitin ang virtual na relay.

### Gawain

Iprograma ang virtual na device.

1. Buksan ang proyekto na `soil-moisture-sensor` mula sa nakaraang aralin sa VS Code kung hindi pa ito nakabukas. Magdadagdag ka sa proyektong ito.

1. Idagdag ang sumusunod na code sa file na `app.py` sa ibaba ng mga umiiral na imports:

    ```python
    from counterfit_shims_grove.grove_relay import GroveRelay
    ```

    Ang pahayag na ito ay nag-iimport ng `GroveRelay` mula sa Grove Python shim libraries upang makipag-ugnayan sa virtual na Grove relay.

1. Idagdag ang sumusunod na code sa ibaba ng deklarasyon ng klase na `ADC` upang lumikha ng isang `GroveRelay` instance:

    ```python
    relay = GroveRelay(5)
    ```

    Lumilikha ito ng relay gamit ang pin **5**, ang pin na konektado sa relay.

1. Upang subukan kung gumagana ang relay, idagdag ang sumusunod sa loob ng `while True:` loop:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    Ang code ay binubuksan ang relay, naghihintay ng 0.5 segundo, pagkatapos ay isinasara ang relay.

1. Patakbuhin ang Python app. Ang relay ay bubukas at magsasara tuwing 10 segundo, na may kalahating segundong delay sa pagitan ng pagbukas at pagsara. Makikita mo ang virtual na relay sa CounterFit app na magsasara at magbubukas habang ang relay ay binubuksan at isinasara.

    ![Ang virtual na relay na nagbubukas at nagsasara](../../../../../images/virtual-relay-turn-on-off.gif)

## Kontrolin ang relay mula sa soil moisture

Ngayon na gumagana na ang relay, maaari na itong kontrolin batay sa mga pagbabasa ng soil moisture.

### Gawain

Kontrolin ang relay.

1. Burahin ang 3 linya ng code na idinagdag mo upang subukan ang relay. Palitan ang mga ito ng sumusunod na code:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    Ang code na ito ay sinusuri ang antas ng soil moisture mula sa soil moisture sensor. Kung ito ay higit sa 450, binubuksan nito ang relay, at isinasara ito kung bumaba ito sa 450.

    > 💁 Tandaan na ang capacitive soil moisture sensor ay nagbabasa na mas mababa ang antas ng soil moisture, mas maraming moisture ang nasa lupa, at kabaligtaran.

1. Patakbuhin ang Python app. Makikita mo ang relay na magbubukas o magsasara depende sa antas ng soil moisture. Baguhin ang *Value* o ang *Random* na mga setting para sa soil moisture sensor upang makita ang pagbabago ng halaga.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Makikita mo ang code na ito sa [code-relay/virtual-device](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/virtual-device) folder.

😀 Tagumpay ang iyong virtual na soil moisture sensor na kumokontrol sa isang relay program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.