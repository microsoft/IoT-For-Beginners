<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f8f541ee945545017a51aaf309aa37c3",
  "translation_date": "2025-08-27T23:28:10+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/virtual-device-relay.md",
  "language_code": "sw"
}
-->
# Kudhibiti relay - Vifaa vya IoT vya Kijumla

Katika sehemu hii ya somo, utaongeza relay kwenye kifaa chako cha IoT cha kijumla pamoja na sensa ya unyevu wa udongo, na kuikontrol kulingana na kiwango cha unyevu wa udongo.

## Vifaa vya Kijumla

Kifaa cha IoT cha kijumla kitatumia relay ya Grove iliyosimuliwa. Hii inafanya maabara hii kuwa sawa na kutumia Raspberry Pi na relay halisi ya Grove.

Katika kifaa halisi cha IoT, relay ingekuwa relay ya kawaida-iliyofunguliwa (ikimaanisha mzunguko wa pato uko wazi, au haujaunganishwa wakati hakuna ishara inayotumwa kwa relay). Relay kama hii inaweza kushughulikia mizunguko ya pato hadi 250V na 10A.

### Ongeza relay kwenye CounterFit

Ili kutumia relay ya kijumla, unahitaji kuiongeza kwenye programu ya CounterFit.

#### Kazi

Ongeza relay kwenye programu ya CounterFit.

1. Fungua mradi wa `soil-moisture-sensor` kutoka somo la mwisho kwenye VS Code ikiwa haujafunguliwa tayari. Utaongeza kwenye mradi huu.

1. Hakikisha programu ya wavuti ya CounterFit inaendelea kufanya kazi.

1. Unda relay:

    1. Katika kisanduku cha *Create actuator* kwenye paneli ya *Actuators*, shusha kisanduku cha *Actuator type* na uchague *Relay*.

    1. Weka *Pin* kuwa *5*.

    1. Chagua kitufe cha **Add** ili kuunda relay kwenye Pin 5.

    ![Mipangilio ya relay](../../../../../translated_images/sw/counterfit-create-relay.fa7c40fd0f2f6afc33b35ea94fcb235085be4861e14e3fe6b9b7bcfc82d1c888.png)

    Relay itaundwa na itaonekana kwenye orodha ya actuators.

    ![Relay iliyoundwa](../../../../../translated_images/sw/counterfit-relay.bbf74c1dbdc8b9acd983367fcbd06703a402aefef6af54ddb28e11307ba8a12c.png)

## Programu ya relay

Sasa programu ya sensa ya unyevu wa udongo inaweza kupangwa kutumia relay ya kijumla.

### Kazi

Panga kifaa cha kijumla.

1. Fungua mradi wa `soil-moisture-sensor` kutoka somo la mwisho kwenye VS Code ikiwa haujafunguliwa tayari. Utaongeza kwenye mradi huu.

1. Ongeza msimbo ufuatao kwenye faili ya `app.py` chini ya uingizaji uliopo:

    ```python
    from counterfit_shims_grove.grove_relay import GroveRelay
    ```

    Kauli hii inaingiza `GroveRelay` kutoka maktaba za Grove Python shim ili kuingiliana na relay ya Grove ya kijumla.

1. Ongeza msimbo ufuatao chini ya tamko la darasa la `ADC` ili kuunda mfano wa `GroveRelay`:

    ```python
    relay = GroveRelay(5)
    ```

    Hii inaunda relay kwa kutumia pin **5**, pin ambayo uliunganisha relay.

1. Ili kujaribu kama relay inafanya kazi, ongeza yafuatayo kwenye kitanzi cha `while True:`:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    Msimbo unawasha relay, unasubiri sekunde 0.5, kisha unazima relay.

1. Endesha programu ya Python. Relay itawashwa na kuzimwa kila sekunde 10, na kuchelewa kwa nusu sekunde kati ya kuwasha na kuzima. Utaona relay ya kijumla kwenye programu ya CounterFit ikifunga na kufungua kadri relay inavyowashwa na kuzimwa.

    ![Relay ya kijumla ikiwashwa na kuzimwa](../../../../../images/virtual-relay-turn-on-off.gif)

## Kudhibiti relay kutoka kwa unyevu wa udongo

Sasa relay inafanya kazi, inaweza kudhibitiwa kulingana na usomaji wa unyevu wa udongo.

### Kazi

Dhibiti relay.

1. Futa mistari 3 ya msimbo ambayo uliyongeza kujaribu relay. Badilisha na msimbo ufuatao mahali pake:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    Msimbo huu unakagua kiwango cha unyevu wa udongo kutoka sensa ya unyevu wa udongo. Ikiwa ni juu ya 450, inawasha relay, na kuizima ikiwa inashuka chini ya 450.

    > 💁 Kumbuka sensa ya unyevu wa udongo ya capacitive inasoma kwamba kiwango cha unyevu wa udongo kinapokuwa chini, kuna unyevu zaidi kwenye udongo na kinyume chake.

1. Endesha programu ya Python. Utaona relay ikiwashwa au kuzimwa kulingana na viwango vya unyevu wa udongo. Badilisha *Value* au mipangilio ya *Random* ya sensa ya unyevu wa udongo ili kuona thamani ikibadilika.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Unaweza kupata msimbo huu kwenye folda ya [code-relay/virtual-device](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/virtual-device).

😀 Programu yako ya sensa ya unyevu wa udongo ya kijumla inayodhibiti relay imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati asilia katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.