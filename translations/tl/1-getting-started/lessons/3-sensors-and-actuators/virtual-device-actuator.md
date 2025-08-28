<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c640f93263fd9adbfda920739e09feb",
  "translation_date": "2025-08-28T00:46:33+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-actuator.md",
  "language_code": "tl"
}
-->
# Gumawa ng nightlight - Virtual na IoT Hardware

Sa bahaging ito ng aralin, magdadagdag ka ng LED sa iyong virtual na IoT device at gagamitin ito upang lumikha ng nightlight.

## Virtual na Hardware

Ang nightlight ay nangangailangan ng isang actuator, na ginawa sa CounterFit app.

Ang actuator ay isang **LED**. Sa isang pisikal na IoT device, ito ay isang [light-emitting diode](https://wikipedia.org/wiki/Light-emitting_diode) na naglalabas ng liwanag kapag dumadaloy ang kuryente dito. Ito ay isang digital actuator na may 2 estado, bukas (on) at patay (off). Ang pagpapadala ng halaga na 1 ay magbubukas ng LED, at 0 ay magpapapatay nito.

Ang lohika ng nightlight sa pseudo-code ay:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Idagdag ang actuator sa CounterFit

Upang magamit ang virtual na LED, kailangan mo itong idagdag sa CounterFit app.

#### Gawain - idagdag ang actuator sa CounterFit

Idagdag ang LED sa CounterFit app.

1. Siguraduhing tumatakbo ang CounterFit web app mula sa nakaraang bahagi ng takdang-aralin. Kung hindi, simulan ito at muling idagdag ang light sensor.

1. Gumawa ng LED:

    1. Sa *Create actuator* box sa *Actuator* pane, i-drop down ang *Actuator type* box at piliin ang *LED*.

    1. Itakda ang *Pin* sa *5*

    1. Piliin ang **Add** button upang lumikha ng LED sa Pin 5

    ![Ang mga setting ng LED](../../../../../translated_images/counterfit-create-led.ba9db1c9b8c622a635d6dfae5cdc4e70c2b250635bd4f0601c6cf0bd22b7ba46.tl.png)

    Ang LED ay malilikha at lilitaw sa listahan ng mga actuator.

    ![Ang LED na nalikha](../../../../../translated_images/counterfit-led.c0ab02de6d256ad84d9bad4d67a7faa709f0ea83e410cfe9b5561ef0cef30b1c.tl.png)

    Kapag nalikha na ang LED, maaari mong baguhin ang kulay gamit ang *Color* picker. Piliin ang **Set** button upang baguhin ang kulay pagkatapos mong piliin ito.

### I-program ang nightlight

Ang nightlight ay maaari nang i-program gamit ang CounterFit light sensor at LED.

#### Gawain - i-program ang nightlight

I-program ang nightlight.

1. Buksan ang nightlight project sa VS Code na ginawa mo sa nakaraang bahagi ng takdang-aralin. Patayin at muling likhain ang terminal upang matiyak na ito ay tumatakbo gamit ang virtual environment kung kinakailangan.

1. Buksan ang `app.py` file.

1. Idagdag ang sumusunod na code sa `app.py` file upang mag-import ng kinakailangang library. Ito ay dapat idagdag sa itaas, sa ilalim ng iba pang `import` lines.

    ```python
    from counterfit_shims_grove.grove_led import GroveLed
    ```

    Ang `from counterfit_shims_grove.grove_led import GroveLed` na pahayag ay nag-i-import ng `GroveLed` mula sa CounterFit Grove shim Python libraries. Ang library na ito ay may code upang makipag-ugnayan sa isang LED na ginawa sa CounterFit app.

1. Idagdag ang sumusunod na code pagkatapos ng deklarasyon ng `light_sensor` upang lumikha ng instance ng klase na namamahala sa LED:

    ```python
    led = GroveLed(5)
    ```

    Ang linyang `led = GroveLed(5)` ay lumilikha ng instance ng `GroveLed` class na kumokonekta sa pin **5** - ang CounterFit Grove pin kung saan nakakonekta ang LED.

1. Magdagdag ng check sa loob ng `while` loop, at bago ang `time.sleep` upang suriin ang light levels at buksan o patayin ang LED:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Ang code na ito ay sinusuri ang halaga ng `light`. Kung ito ay mas mababa sa 300, tatawagin nito ang `on` method ng `GroveLed` class na nagpapadala ng digital na halaga na 1 sa LED, na binubuksan ito. Kung ang halaga ng liwanag ay mas mataas o katumbas ng 300, tatawagin nito ang `off` method, na nagpapadala ng digital na halaga na 0 sa LED, na pinapatay ito.

    > 💁 Ang code na ito ay dapat naka-indent sa parehong antas ng linyang `print('Light level:', light)` upang mapabilang sa loob ng while loop!

1. Mula sa VS Code Terminal, patakbuhin ang sumusunod upang patakbuhin ang iyong Python app:

    ```sh
    python3 app.py
    ```

    Ang mga halaga ng liwanag ay ipapakita sa console.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

1. Baguhin ang *Value* o ang *Random* settings upang mag-iba ang light level sa itaas at ibaba ng 300. Ang LED ay magbubukas at magpapapatay.

![Ang LED sa CounterFit app na nagbubukas at nagpapapatay habang nagbabago ang light level](../../../../../images/virtual-device-running-assignment-1-1.gif)

> 💁 Makikita mo ang code na ito sa [code-actuator/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/virtual-device) folder.

😀 Tagumpay ang iyong nightlight program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.