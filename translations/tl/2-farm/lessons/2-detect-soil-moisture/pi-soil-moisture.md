<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9d4d00a47d5d0f3e6ce42c0d1020064a",
  "translation_date": "2025-08-28T01:07:58+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/pi-soil-moisture.md",
  "language_code": "tl"
}
-->
# Sukatin ang Halumigmig ng Lupa - Raspberry Pi

Sa bahaging ito ng aralin, magdadagdag ka ng capacitive soil moisture sensor sa iyong Raspberry Pi, at babasahin ang mga halaga mula rito.

## Kagamitan

Kailangan ng Raspberry Pi ng isang capacitive soil moisture sensor.

Ang sensor na gagamitin mo ay isang [Capacitive Soil Moisture Sensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), na sumusukat sa halumigmig ng lupa sa pamamagitan ng pagtukoy sa capacitance ng lupa, isang katangian na nagbabago habang nagbabago ang halumigmig ng lupa. Kapag tumataas ang halumigmig ng lupa, bumababa ang boltahe.

Ito ay isang analog sensor, kaya gumagamit ito ng analog pin, at ang 10-bit ADC sa Grove Base Hat sa Pi upang i-convert ang boltahe sa isang digital na signal mula 1-1,023. Ang signal na ito ay ipinapadala sa pamamagitan ng I2C gamit ang GPIO pins sa Pi.

### Ikonekta ang soil moisture sensor

Ang Grove soil moisture sensor ay maaaring ikonekta sa Raspberry Pi.

#### Gawain - ikonekta ang soil moisture sensor

Ikonekta ang soil moisture sensor.

![Isang Grove soil moisture sensor](../../../../../translated_images/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.tl.png)

1. Ipasok ang isang dulo ng Grove cable sa socket ng soil moisture sensor. Isang paraan lamang ang tamang pagpasok nito.

1. Kapag naka-off ang Raspberry Pi, ikonekta ang kabilang dulo ng Grove cable sa analog socket na may markang **A0** sa Grove Base Hat na nakakabit sa Pi. Ang socket na ito ay ang pangalawa mula sa kanan, sa hanay ng mga socket na malapit sa GPIO pins.

![Ang Grove soil moisture sensor na nakakonekta sa A0 socket](../../../../../translated_images/pi-soil-moisture-sensor.fdd7eb2393792cf6739cacf1985d9f55beda16d372f30d0b5a51d586f978a870.tl.png)

1. Ipasok ang soil moisture sensor sa lupa. Mayroon itong 'highest position line' - isang puting linya sa sensor. Ipasok ang sensor hanggang sa linyang ito ngunit huwag lalampas.

![Ang Grove soil moisture sensor sa lupa](../../../../../translated_images/soil-moisture-sensor-in-soil.bfad91002bda5e960f8c51ee64b02ee59b32c8c717e3515a2c945f33e614e403.tl.png)

## Iprograma ang soil moisture sensor

Ngayon ay maaaring iprograma ang Raspberry Pi upang magamit ang nakakabit na soil moisture sensor.

### Gawain - iprograma ang soil moisture sensor

Iprograma ang device.

1. I-on ang Pi at hintayin itong mag-boot.

1. Ilunsad ang VS Code, alinman nang direkta sa Pi, o kumonekta gamit ang Remote SSH extension.

    > ⚠️ Maaari kang sumangguni sa [mga tagubilin para sa pag-set up at paglulunsad ng VS Code sa nightlight - lesson 1 kung kinakailangan](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Mula sa terminal, gumawa ng bagong folder sa home directory ng user na `pi` na tinatawag na `soil-moisture-sensor`. Gumawa ng file sa folder na ito na tinatawag na `app.py`.

1. Buksan ang folder na ito sa VS Code.

1. Idagdag ang sumusunod na code sa file na `app.py` upang mag-import ng ilang kinakailangang library:

    ```python
    import time
    from grove.adc import ADC
    ```

    Ang `import time` na pahayag ay nag-i-import ng `time` module na gagamitin sa susunod na bahagi ng gawaing ito.

    Ang `from grove.adc import ADC` na pahayag ay nag-i-import ng `ADC` mula sa Grove Python libraries. Ang library na ito ay may code upang makipag-ugnayan sa analog to digital converter sa Pi base hat at basahin ang boltahe mula sa mga analog sensor.

1. Idagdag ang sumusunod na code sa ibaba nito upang lumikha ng isang instance ng `ADC` class:

    ```python
    adc = ADC()
    ```

1. Magdagdag ng isang infinite loop na nagbabasa mula sa ADC sa A0 pin, at isinusulat ang resulta sa console. Ang loop na ito ay maaaring mag-pause ng 10 segundo sa pagitan ng mga pagbabasa.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)

        time.sleep(10)
    ```

1. Patakbuhin ang Python app. Makikita mo ang mga sukat ng halumigmig ng lupa na isinusulat sa console. Magdagdag ng tubig sa lupa, o alisin ang sensor mula sa lupa, at tingnan ang pagbabago ng halaga.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

    Sa halimbawa ng output sa itaas, makikita mo ang pagbaba ng boltahe habang dinadagdagan ang tubig.

> 💁 Maaari mong makita ang code na ito sa [code/pi](../../../../../2-farm/lessons/2-detect-soil-moisture/code/pi) folder.

😀 Tagumpay ang iyong soil moisture sensor program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.