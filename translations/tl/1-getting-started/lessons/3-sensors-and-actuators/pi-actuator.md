<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4db8a3879a53490513571df2f6cf7641",
  "translation_date": "2025-08-28T00:47:49+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-actuator.md",
  "language_code": "tl"
}
-->
# Gumawa ng nightlight - Raspberry Pi

Sa bahaging ito ng aralin, magdadagdag ka ng LED sa iyong Raspberry Pi at gagamitin ito upang lumikha ng isang nightlight.

## Kagamitan

Kailangan na ngayon ng nightlight ng isang actuator.

Ang actuator ay isang **LED**, isang [light-emitting diode](https://wikipedia.org/wiki/Light-emitting_diode) na naglalabas ng liwanag kapag dumadaloy ang kuryente dito. Isa itong digital actuator na may dalawang estado: naka-on at naka-off. Ang pagpapadala ng halaga na 1 ay magpapailaw sa LED, at ang 0 ay magpapapatay dito. Ang LED ay isang panlabas na Grove actuator at kailangang ikonekta sa Grove Base hat sa Raspberry Pi.

Ang lohika ng nightlight sa pseudo-code ay:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Ikonekta ang LED

Ang Grove LED ay may kasamang module na may iba't ibang kulay ng LED, na nagbibigay-daan sa iyong pumili ng kulay.

#### Gawain - ikonekta ang LED

Ikonekta ang LED.

![Isang Grove LED](../../../../../translated_images/grove-led.6c853be93f473cf2c439cfc74bb1064732b22251a83cedf66e62f783f9cc1a79.tl.png)

1. Pumili ng paborito mong LED at ipasok ang mga paa nito sa dalawang butas sa LED module.

    Ang mga LED ay light-emitting diodes, at ang mga diode ay mga elektronikong aparato na maaaring magdala ng kuryente sa isang direksyon lamang. Nangangahulugan ito na kailangang maikonekta ang LED sa tamang direksyon, kung hindi, hindi ito gagana.

    Ang isa sa mga paa ng LED ay ang positibong pin, at ang isa naman ay ang negatibong pin. Ang LED ay hindi perpektong bilog at medyo patag sa isang gilid. Ang medyo patag na gilid ay ang negatibong pin. Kapag ikinonekta mo ang LED sa module, tiyaking ang pin sa bilog na gilid ay nakakonekta sa socket na may markang **+** sa labas ng module, at ang patag na gilid ay nakakonekta sa socket na mas malapit sa gitna ng module.

1. Ang LED module ay may spin button na nagbibigay-daan sa iyong kontrolin ang liwanag. Iikot ito nang pakanan hanggang sa dulo gamit ang maliit na Phillips head screwdriver upang simulan.

1. Ipasok ang isang dulo ng Grove cable sa socket ng LED module. Papasok lamang ito sa isang direksyon.

1. Kapag naka-off ang Raspberry Pi, ikonekta ang kabilang dulo ng Grove cable sa digital socket na may markang **D5** sa Grove Base hat na nakakabit sa Pi. Ang socket na ito ay ang pangalawa mula sa kaliwa, sa hanay ng mga socket na malapit sa GPIO pins.

![Ang Grove LED na nakakonekta sa socket D5](../../../../../translated_images/pi-led.97f1d474981dc35d1c7996c7b17de355d3d0a6bc9606d79fa5f89df933415122.tl.png)

## Iprograma ang nightlight

Ngayon ay maaari nang iprograma ang nightlight gamit ang Grove light sensor at Grove LED.

### Gawain - iprograma ang nightlight

Iprograma ang nightlight.

1. I-on ang Pi at hintaying mag-boot.

1. Buksan ang nightlight project sa VS Code na ginawa mo sa nakaraang bahagi ng assignment, alinman sa direkta sa Pi o gamit ang Remote SSH extension.

1. Idagdag ang sumusunod na code sa `app.py` file upang mag-import ng kinakailangang library. Idagdag ito sa itaas, sa ibaba ng iba pang `import` lines.

    ```python
    from grove.grove_led import GroveLed
    ```

    Ang `from grove.grove_led import GroveLed` na pahayag ay nag-i-import ng `GroveLed` mula sa Grove Python libraries. Ang library na ito ay may code upang makipag-ugnayan sa isang Grove LED.

1. Idagdag ang sumusunod na code pagkatapos ng deklarasyon ng `light_sensor` upang lumikha ng isang instance ng klase na namamahala sa LED:

    ```python
    led = GroveLed(5)
    ```

    Ang linyang `led = GroveLed(5)` ay lumilikha ng isang instance ng `GroveLed` class na nakakonekta sa pin **D5** - ang digital Grove pin kung saan nakakonekta ang LED.

    > 💁 Ang lahat ng socket ay may natatanging mga numero ng pin. Ang mga pin 0, 2, 4, at 6 ay analog pins, habang ang mga pin 5, 16, 18, 22, 24, at 26 ay digital pins.

1. Magdagdag ng isang tseke sa loob ng `while` loop, at bago ang `time.sleep` upang suriin ang antas ng liwanag at i-on o i-off ang LED:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Sinusuri ng code na ito ang halaga ng `light`. Kung mas mababa ito sa 300, tatawagin nito ang `on` method ng `GroveLed` class na nagpapadala ng digital na halaga na 1 sa LED, na magpapailaw dito. Kung ang halaga ng liwanag ay mas malaki o katumbas ng 300, tatawagin nito ang `off` method, na nagpapadala ng digital na halaga na 0 sa LED, na magpapapatay dito.

    > 💁 Ang code na ito ay dapat naka-indent sa parehong antas ng linyang `print('Light level:', light)` upang mapabilang sa loob ng while loop!

    > 💁 Kapag nagpapadala ng digital na halaga sa mga actuator, ang halagang 0 ay 0V, at ang halagang 1 ay ang maximum na boltahe para sa aparato. Para sa Raspberry Pi na may Grove sensors at actuators, ang boltahe ng 1 ay 3.3V.

1. Mula sa VS Code Terminal, patakbuhin ang sumusunod upang patakbuhin ang iyong Python app:

    ```sh
    python3 app.py
    ```

    Ang mga halaga ng liwanag ay ipapakita sa console.

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

1. Takpan at alisin ang takip sa light sensor. Mapapansin mo na ang LED ay iilaw kung ang antas ng liwanag ay 300 o mas mababa, at mamamatay kapag ang antas ng liwanag ay mas mataas sa 300.

    > 💁 Kung hindi iilaw ang LED, tiyaking nakakonekta ito sa tamang direksyon, at ang spin button ay nakatakda sa full on.

![Ang LED na nakakonekta sa Pi na nag-o-on at off habang nagbabago ang antas ng liwanag](../../../../../images/pi-running-assignment-1-1.gif)

> 💁 Makikita mo ang code na ito sa [code-actuator/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/pi) folder.

😀 Tagumpay ang iyong nightlight program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, pakitandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa orihinal nitong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.