<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9d4d00a47d5d0f3e6ce42c0d1020064a",
  "translation_date": "2025-08-27T22:48:06+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/pi-soil-moisture.md",
  "language_code": "sw"
}
-->
# Kupima unyevu wa udongo - Raspberry Pi

Katika sehemu hii ya somo, utaongeza kihisi cha unyevu wa udongo cha capacitive kwenye Raspberry Pi yako, na kusoma thamani kutoka kwake.

## Vifaa

Raspberry Pi inahitaji kihisi cha unyevu wa udongo cha capacitive.

Kihisi utakachotumia ni [Capacitive Soil Moisture Sensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), ambacho hupima unyevu wa udongo kwa kugundua uwezo wa udongo, mali inayobadilika kadri unyevu wa udongo unavyobadilika. Kadri unyevu wa udongo unavyoongezeka, voltage hupungua.

Hiki ni kihisi cha analogi, kwa hivyo kinatumia pini ya analogi, na ADC ya biti 10 kwenye Grove Base Hat ya Pi kubadilisha voltage kuwa ishara ya kidijitali kutoka 1-1,023. Hii kisha hutumwa kupitia I2C kupitia pini za GPIO kwenye Pi.

### Unganisha kihisi cha unyevu wa udongo

Kihisi cha unyevu wa udongo cha Grove kinaweza kuunganishwa kwenye Raspberry Pi.

#### Kazi - Unganisha kihisi cha unyevu wa udongo

Unganisha kihisi cha unyevu wa udongo.

![Kihisi cha unyevu wa udongo cha Grove](../../../../../translated_images/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.sw.png)

1. Ingiza mwisho mmoja wa kebo ya Grove kwenye soketi ya kihisi cha unyevu wa udongo. Itaingia kwa njia moja tu.

1. Ukiwa na Raspberry Pi imezimwa, unganisha mwisho mwingine wa kebo ya Grove kwenye soketi ya analogi iliyoandikwa **A0** kwenye Grove Base Hat iliyounganishwa na Pi. Soketi hii ni ya pili kutoka kulia, kwenye safu ya soketi karibu na pini za GPIO.

![Kihisi cha unyevu wa udongo cha Grove kimeunganishwa kwenye soketi ya A0](../../../../../translated_images/pi-soil-moisture-sensor.fdd7eb2393792cf6739cacf1985d9f55beda16d372f30d0b5a51d586f978a870.sw.png)

1. Ingiza kihisi cha unyevu wa udongo kwenye udongo. Kina mstari wa 'kiwango cha juu zaidi' - mstari mweupe kwenye kihisi. Ingiza kihisi hadi mstari huu lakini usivuke mstari.

![Kihisi cha unyevu wa udongo cha Grove kwenye udongo](../../../../../translated_images/soil-moisture-sensor-in-soil.bfad91002bda5e96.sw.png)

## Programu ya kihisi cha unyevu wa udongo

Sasa Raspberry Pi inaweza kupangwa kutumia kihisi cha unyevu wa udongo kilichounganishwa.

### Kazi - Programu ya kihisi cha unyevu wa udongo

Panga kifaa.

1. Washa Pi na subiri ianze.

1. Fungua VS Code, moja kwa moja kwenye Pi, au unganisha kupitia kiendelezi cha Remote SSH.

    > ⚠️ Unaweza kurejelea [maelekezo ya kusanidi na kufungua VS Code katika nightlight - somo la 1 ikiwa inahitajika](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Kutoka kwenye terminal, tengeneza folda mpya kwenye saraka ya nyumbani ya mtumiaji `pi` inayoitwa `soil-moisture-sensor`. Tengeneza faili kwenye folda hii inayoitwa `app.py`.

1. Fungua folda hii kwenye VS Code.

1. Ongeza msimbo ufuatao kwenye faili ya `app.py` ili kuingiza maktaba zinazohitajika:

    ```python
    import time
    from grove.adc import ADC
    ```

    Tamko la `import time` linaingiza moduli ya `time` ambayo itatumika baadaye katika kazi hii.

    Tamko la `from grove.adc import ADC` linaingiza `ADC` kutoka kwenye maktaba za Python za Grove. Maktaba hii ina msimbo wa kuingiliana na analogi hadi kigeuzi cha kidijitali kwenye Pi Base Hat na kusoma voltage kutoka kwa vihisi vya analogi.

1. Ongeza msimbo ufuatao chini ya hii ili kuunda mfano wa darasa la `ADC`:

    ```python
    adc = ADC()
    ```

1. Ongeza kitanzi kisicho na mwisho kinachosoma kutoka kwa ADC hii kwenye pini ya A0, na kuandika matokeo kwenye koni. Kitanzi hiki kinaweza kulala kwa sekunde 10 kati ya usomaji.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)

        time.sleep(10)
    ```

1. Endesha programu ya Python. Utaona vipimo vya unyevu wa udongo vikiandikwa kwenye koni. Ongeza maji kwenye udongo, au ondoa kihisi kutoka kwenye udongo, na uone thamani ikibadilika.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

    Katika mfano wa matokeo hapo juu, unaweza kuona voltage ikipungua kadri maji yanavyoongezwa.

> 💁 Unaweza kupata msimbo huu kwenye folda ya [code/pi](../../../../../2-farm/lessons/2-detect-soil-moisture/code/pi).

😀 Programu yako ya kihisi cha unyevu wa udongo imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutokuelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.