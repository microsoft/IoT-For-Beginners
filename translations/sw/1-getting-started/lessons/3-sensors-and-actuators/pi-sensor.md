<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ea733bd0cdf2479e082373f765a08678",
  "translation_date": "2025-08-27T22:30:51+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-sensor.md",
  "language_code": "sw"
}
-->
# Jenga taa ya usiku - Raspberry Pi

Katika sehemu hii ya somo, utaongeza kihisi cha mwanga kwenye Raspberry Pi yako.

## Vifaa

Kihisi cha somo hili ni **kihisi cha mwanga** kinachotumia [photodiode](https://wikipedia.org/wiki/Photodiode) kubadilisha mwanga kuwa ishara ya umeme. Hiki ni kihisi cha analogi kinachotuma thamani ya nambari nzima kutoka 0 hadi 1,000, ikionyesha kiwango cha mwanga ambacho hakihusiani na kipimo chochote cha kawaida kama [lux](https://wikipedia.org/wiki/Lux).

Kihisi cha mwanga ni kihisi cha nje cha Grove na kinahitaji kuunganishwa kwenye kofia ya Grove Base kwenye Raspberry Pi.

### Unganisha kihisi cha mwanga

Kihisi cha mwanga cha Grove kinachotumika kugundua viwango vya mwanga kinahitaji kuunganishwa kwenye Raspberry Pi.

#### Kazi - unganisha kihisi cha mwanga

Unganisha kihisi cha mwanga

![Kihisi cha mwanga cha Grove](../../../../../translated_images/sw/grove-light-sensor.b8127b7c434e632d6bcdb57587a14e9ef69a268a22df95d08628f62b8fa5505c.png)

1. Ingiza mwisho mmoja wa kebo ya Grove kwenye soketi ya moduli ya kihisi cha mwanga. Itaingia kwa njia moja tu.

1. Ukiwa na Raspberry Pi imezimwa, unganisha mwisho mwingine wa kebo ya Grove kwenye soketi ya analogi iliyoandikwa **A0** kwenye kofia ya Grove Base iliyounganishwa na Pi. Soketi hii ni ya pili kutoka kulia, kwenye safu ya soketi karibu na pini za GPIO.

![Kihisi cha mwanga cha Grove kimeunganishwa kwenye soketi A0](../../../../../translated_images/sw/pi-light-sensor.66cc1e31fa48cd7d5f23400d4b2119aa41508275cb7c778053a7923b4e972d7e.png)

## Programu ya kihisi cha mwanga

Kifaa sasa kinaweza kupangwa kwa kutumia kihisi cha mwanga cha Grove.

### Kazi - panga kihisi cha mwanga

Panga kifaa.

1. Washa Pi na subiri ianze.

1. Fungua mradi wa taa ya usiku kwenye VS Code uliouunda katika sehemu ya awali ya kazi hii, iwe unaendesha moja kwa moja kwenye Pi au umeunganishwa kwa kutumia kiendelezi cha Remote SSH.

1. Fungua faili `app.py` na ondoa msimbo wote kutoka ndani yake.

1. Ongeza msimbo ufuatao kwenye faili `app.py` ili kuingiza maktaba zinazohitajika:

    ```python
    import time
    from grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    Tamko `import time` linaingiza moduli ya `time` ambayo itatumika baadaye katika kazi hii.

    Tamko `from grove.grove_light_sensor_v1_2 import GroveLightSensor` linaingiza `GroveLightSensor` kutoka kwenye maktaba za Python za Grove. Maktaba hii ina msimbo wa kuingiliana na kihisi cha mwanga cha Grove, na ilifungwa kimataifa wakati wa usanidi wa Pi.

1. Ongeza msimbo ufuatao baada ya msimbo hapo juu ili kuunda mfano wa darasa linalosimamia kihisi cha mwanga:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    Mstari `light_sensor = GroveLightSensor(0)` unaunda mfano wa darasa la `GroveLightSensor` linalounganishwa na pini **A0** - pini ya analogi ya Grove ambayo kihisi cha mwanga kimeunganishwa.

1. Ongeza kitanzi kisicho na mwisho baada ya msimbo hapo juu ili kuchukua thamani ya kihisi cha mwanga na kuichapisha kwenye koni:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Hii itasoma kiwango cha sasa cha mwanga kwa kipimo cha 0-1,023 kwa kutumia mali ya `light` ya darasa la `GroveLightSensor`. Mali hii inasoma thamani ya analogi kutoka kwenye pini. Thamani hii kisha inachapishwa kwenye koni.

1. Ongeza muda mfupi wa kulala wa sekunde moja mwishoni mwa `loop` kwani viwango vya mwanga havihitaji kuchunguzwa kila wakati. Kulala kunapunguza matumizi ya nguvu ya kifaa.

    ```python
    time.sleep(1)
    ```

1. Kutoka kwenye Terminal ya VS Code, endesha yafuatayo ili kuendesha programu yako ya Python:

    ```sh
    python3 app.py
    ```

    Thamani za mwanga zitaonyeshwa kwenye koni. Funika na funua kihisi cha mwanga, na thamani zitabadilika:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

> 💁 Unaweza kupata msimbo huu kwenye folda ya [code-sensor/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/pi).

😀 Kuongeza kihisi kwenye programu yako ya taa ya usiku ilikuwa mafanikio!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.