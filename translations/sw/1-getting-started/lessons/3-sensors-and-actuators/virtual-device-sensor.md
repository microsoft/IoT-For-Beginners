<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "11f10c6760fb8202cf368422702fdf70",
  "translation_date": "2025-08-27T22:33:03+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-sensor.md",
  "language_code": "sw"
}
-->
# Jenga taa ya usiku - Vifaa vya IoT vya Kijumla

Katika sehemu hii ya somo, utaongeza kihisi cha mwanga kwenye kifaa chako cha IoT cha kijumla.

## Vifaa vya Kijumla

Taa ya usiku inahitaji kihisi kimoja, kilichoundwa katika programu ya CounterFit.

Kihisi ni **kihisi cha mwanga**. Katika kifaa halisi cha IoT, kingekuwa [photodiode](https://wikipedia.org/wiki/Photodiode) kinachobadilisha mwanga kuwa ishara ya umeme. Vihisi vya mwanga ni vihisi vya analogi vinavyotuma thamani ya nambari nzima inayoonyesha kiasi cha mwanga, ambacho hakilingani na kipimo chochote cha kawaida kama [lux](https://wikipedia.org/wiki/Lux).

### Ongeza vihisi kwenye CounterFit

Ili kutumia kihisi cha mwanga cha kijumla, unahitaji kukiongeza kwenye programu ya CounterFit.

#### Kazi - ongeza vihisi kwenye CounterFit

Ongeza kihisi cha mwanga kwenye programu ya CounterFit.

1. Hakikisha programu ya wavuti ya CounterFit inaendelea kutoka sehemu ya awali ya kazi hii. Ikiwa haijaanza, ianzishe.

1. Unda kihisi cha mwanga:

    1. Katika kisanduku cha *Create sensor* kwenye paneli ya *Sensors*, shusha kisanduku cha *Sensor type* na uchague *Light*.

    1. Acha *Units* zikiwa zimewekwa kwa *NoUnits*.

    1. Hakikisha *Pin* imewekwa kwa *0*.

    1. Chagua kitufe cha **Add** ili kuunda kihisi cha mwanga kwenye Pin 0.

    ![Mipangilio ya kihisi cha mwanga](../../../../../translated_images/sw/counterfit-create-light-sensor.9f36a5e0d4458d8d554d54b34d2c806d56093d6e49fddcda2d20f6fef7f5cce1.png)

    Kihisi cha mwanga kitatengenezwa na kuonekana kwenye orodha ya vihisi.

    ![Kihisi cha mwanga kilichoundwa](../../../../../translated_images/sw/counterfit-light-sensor.5d0f5584df56b90f6b2561910d9cb20dfbd73eeff2177c238d38f4de54aefae1.png)

## Programu ya kihisi cha mwanga

Sasa kifaa kinaweza kupangwa kutumia kihisi cha mwanga kilichojengwa ndani.

### Kazi - panga kihisi cha mwanga

Panga kifaa.

1. Fungua mradi wa taa ya usiku katika VS Code uliounda katika sehemu ya awali ya kazi hii. Zima na unda upya terminal ili kuhakikisha inafanya kazi kwa kutumia mazingira ya kijumla ikiwa ni lazima.

1. Fungua faili `app.py`.

1. Ongeza msimbo ufuatao juu ya faili `app.py` pamoja na kauli nyingine za `import` ili kuunganisha maktaba zinazohitajika:

    ```python
    import time
    from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    Kauli ya `import time` inaingiza moduli ya Python `time` ambayo itatumika baadaye katika kazi hii.

    Kauli ya `from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor` inaingiza `GroveLightSensor` kutoka maktaba za Python za CounterFit Grove shim. Maktaba hii ina msimbo wa kuingiliana na kihisi cha mwanga kilichoundwa katika programu ya CounterFit.

1. Ongeza msimbo ufuatao chini ya faili ili kuunda matukio ya madarasa yanayosimamia kihisi cha mwanga:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    Mstari `light_sensor = GroveLightSensor(0)` unaunda tukio la darasa la `GroveLightSensor` linalounganishwa na pin **0** - pin ya CounterFit Grove ambayo kihisi cha mwanga kimeunganishwa.

1. Ongeza kitanzi kisicho na mwisho baada ya msimbo hapo juu ili kuchunguza thamani ya kihisi cha mwanga na kuitoa kwenye koni:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Hii itasoma kiwango cha mwanga cha sasa kwa kutumia mali ya `light` ya darasa la `GroveLightSensor`. Mali hii inasoma thamani ya analogi kutoka kwa pin. Thamani hii kisha inachapishwa kwenye koni.

1. Ongeza muda mfupi wa sekunde moja mwishoni mwa kitanzi cha `while` kwani viwango vya mwanga havihitaji kuchunguzwa kila wakati. Muda wa kulala unapunguza matumizi ya nguvu ya kifaa.

    ```python
    time.sleep(1)
    ```

1. Kutoka kwa Terminal ya VS Code, endesha yafuatayo ili kuendesha programu yako ya Python:

    ```sh
    python3 app.py
    ```

    Thamani za mwanga zitatolewa kwenye koni. Awali thamani hii itakuwa 0.

1. Kutoka kwa programu ya CounterFit, badilisha thamani ya kihisi cha mwanga ambayo itasomwa na programu. Unaweza kufanya hivi kwa njia mbili:

    * Ingiza nambari kwenye kisanduku cha *Value* cha kihisi cha mwanga, kisha chagua kitufe cha **Set**. Nambari unayoingiza itakuwa thamani inayorejeshwa na kihisi.

    * Angalia kisanduku cha *Random*, na ingiza thamani ya *Min* na *Max*, kisha chagua kitufe cha **Set**. Kila wakati kihisi kinasoma thamani, kitasoma nambari ya nasibu kati ya *Min* na *Max*.

    Thamani unazoweka zitatolewa kwenye koni. Badilisha *Value* au mipangilio ya *Random* ili kufanya thamani ibadilike.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

> 💁 Unaweza kupata msimbo huu katika folda ya [code-sensor/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/virtual-device).

😀 Programu yako ya taa ya usiku imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.