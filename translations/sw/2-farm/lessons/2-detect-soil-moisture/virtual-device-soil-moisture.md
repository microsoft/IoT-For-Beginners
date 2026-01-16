<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2bf65f162bcebd35fbcba5fd245afac4",
  "translation_date": "2025-08-27T22:53:49+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/virtual-device-soil-moisture.md",
  "language_code": "sw"
}
-->
# Pima unyevu wa udongo - Vifaa vya IoT vya Kijumlisha

Katika sehemu hii ya somo, utaongeza kihisi cha unyevu wa udongo cha capacitive kwenye kifaa chako cha IoT cha kijumlisha, na kusoma thamani kutoka kwake.

## Vifaa vya Kijumlisha

Kifaa cha IoT cha kijumlisha kitatumia kihisi cha unyevu wa udongo cha capacitive cha Grove kilichosimuliwa. Hii inafanya maabara hii kuwa sawa na kutumia Raspberry Pi na kihisi cha unyevu wa udongo cha capacitive cha Grove cha kimwili.

Katika kifaa cha IoT cha kimwili, kihisi cha unyevu wa udongo kingekuwa kihisi cha capacitive kinachopima unyevu wa udongo kwa kugundua uwezo wa udongo, mali inayobadilika kadri unyevu wa udongo unavyobadilika. Kadri unyevu wa udongo unavyoongezeka, ndivyo voltage inavyopungua.

Hiki ni kihisi cha analogi, kwa hivyo kinatumia ADC ya biti 10 iliyosimuliwa kuripoti thamani kutoka 1-1,023.

### Ongeza kihisi cha unyevu wa udongo kwenye CounterFit

Ili kutumia kihisi cha unyevu wa udongo cha kijumlisha, unahitaji kukiongeza kwenye programu ya CounterFit.

#### Kazi - Ongeza kihisi cha unyevu wa udongo kwenye CounterFit

Ongeza kihisi cha unyevu wa udongo kwenye programu ya CounterFit.

1. Unda programu mpya ya Python kwenye kompyuta yako ndani ya folda inayoitwa `soil-moisture-sensor` yenye faili moja inayoitwa `app.py` na mazingira ya kijumlisha ya Python, na ongeza vifurushi vya pip vya CounterFit.

    > ⚠️ Unaweza kurejelea [maelekezo ya kuunda na kusanidi mradi wa Python wa CounterFit katika somo la 1 ikiwa inahitajika](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Hakikisha programu ya wavuti ya CounterFit inaendelea kufanya kazi.

1. Unda kihisi cha unyevu wa udongo:

    1. Katika kisanduku cha *Create sensor* kwenye paneli ya *Sensors*, shusha kisanduku cha *Sensor type* na uchague *Soil Moisture*.

    1. Acha *Units* ziwekwe kwa *NoUnits*.

    1. Hakikisha *Pin* imewekwa kwa *0*.

    1. Chagua kitufe cha **Add** kuunda kihisi cha *Soil Moisture* kwenye Pin 0.

    ![Mipangilio ya kihisi cha unyevu wa udongo](../../../../../translated_images/sw/counterfit-create-soil-moisture-sensor.35266135a5e0ae68b29a684d7db0d2933a8098b2307d197f7c71577b724603aa.png)

    Kihisi cha unyevu wa udongo kitaundwa na kitaonekana kwenye orodha ya vihisi.

    ![Kihisi cha unyevu wa udongo kimeundwa](../../../../../translated_images/sw/counterfit-soil-moisture-sensor.81742b2de0e9de60a3b3b9a2ff8ecc686d428eb6d71820f27a693be26e5aceee.png)

## Programu ya kihisi cha unyevu wa udongo

Sasa programu ya kihisi cha unyevu wa udongo inaweza kuandikwa kwa kutumia vihisi vya CounterFit.

### Kazi - andika programu ya kihisi cha unyevu wa udongo

Andika programu ya kihisi cha unyevu wa udongo.

1. Hakikisha programu ya `soil-moisture-sensor` imefunguliwa kwenye VS Code.

1. Fungua faili ya `app.py`.

1. Ongeza msimbo ufuatao juu ya `app.py` ili kuunganisha programu na CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Ongeza msimbo ufuatao kwenye faili ya `app.py` ili kuingiza maktaba zinazohitajika:

    ```python
    import time
    from counterfit_shims_grove.adc import ADC
    ```

    Kauli ya `import time` inaingiza moduli ya `time` ambayo itatumika baadaye katika kazi hii.

    Kauli ya `from counterfit_shims_grove.adc import ADC` inaingiza darasa la `ADC` ili kuingiliana na kigeuzi cha analogi hadi dijitali cha kijumlisha kinachoweza kuunganishwa na kihisi cha CounterFit.

1. Ongeza msimbo ufuatao chini ya hii ili kuunda mfano wa darasa la `ADC`:

    ```python
    adc = ADC()
    ```

1. Ongeza kitanzi kisicho na mwisho kinachosoma kutoka kwa ADC kwenye pini 0 na kuandika matokeo kwenye koni. Kitanzi hiki kinaweza kulala kwa sekunde 10 kati ya usomaji.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)
    
        time.sleep(10)
    ```

1. Kutoka kwenye programu ya CounterFit, badilisha thamani ya kihisi cha unyevu wa udongo ambayo itasomwa na programu. Unaweza kufanya hivi kwa njia mbili:

    * Weka namba kwenye kisanduku cha *Value* cha kihisi cha unyevu wa udongo, kisha chagua kitufe cha **Set**. Namba unayoingiza itakuwa thamani inayorudishwa na kihisi.

    * Angalia kisanduku cha *Random*, na weka thamani ya *Min* na *Max*, kisha chagua kitufe cha **Set**. Kila wakati kihisi kinasoma thamani, kitasoma namba ya bahati nasibu kati ya *Min* na *Max*.

1. Endesha programu ya Python. Utaona vipimo vya unyevu wa udongo vikiandikwa kwenye koni. Badilisha mipangilio ya *Value* au *Random* ili kuona thamani ikibadilika.

    ```output
    (.venv) ➜ soil-moisture-sensor $ python app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

> 💁 Unaweza kupata msimbo huu kwenye folda ya [code/virtual-device](../../../../../2-farm/lessons/2-detect-soil-moisture/code/virtual-device).

😀 Programu yako ya kihisi cha unyevu wa udongo imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuchukuliwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.