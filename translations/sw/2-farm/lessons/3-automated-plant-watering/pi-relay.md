<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "66b81165e60f8f169bd52a401b6a0f8b",
  "translation_date": "2025-08-27T23:29:01+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/pi-relay.md",
  "language_code": "sw"
}
-->
# Kudhibiti relay - Raspberry Pi

Katika sehemu hii ya somo, utaongeza relay kwenye Raspberry Pi yako pamoja na kihisi cha unyevu wa udongo, na kuikontrol kulingana na kiwango cha unyevu wa udongo.

## Vifaa vya Kielektroniki

Raspberry Pi inahitaji relay.

Relay utakayotumia ni [Grove relay](https://www.seeedstudio.com/Grove-Relay.html), relay ya kawaida-iliyofunguliwa (inamaanisha mzunguko wa pato uko wazi, au haujaunganishwa wakati hakuna ishara inayotumwa kwa relay) ambayo inaweza kushughulikia mizunguko ya pato hadi 250V na 10A.

Hii ni actuator ya kidigitali, kwa hivyo inaunganishwa kwenye pini ya kidigitali kwenye Grove Base Hat.

### Unganisha relay

Relay ya Grove inaweza kuunganishwa kwenye Raspberry Pi.

#### Kazi

Unganisha relay.

![Relay ya Grove](../../../../../translated_images/sw/grove-relay.d426958ca210fbd0fb7983d7edc069d46c73a8b0a099d94797bd756f7b6bb6be.png)

1. Ingiza mwisho mmoja wa kebo ya Grove kwenye soketi ya relay. Itaingia kwa njia moja tu.

1. Ukiwa na Raspberry Pi imezimwa, unganisha mwisho mwingine wa kebo ya Grove kwenye soketi ya kidigitali iliyoandikwa **D5** kwenye Grove Base Hat iliyounganishwa na Pi. Soketi hii ni ya pili kutoka kushoto, kwenye safu ya soketi karibu na pini za GPIO. Acha kihisi cha unyevu wa udongo kikiwa kimeunganishwa kwenye soketi ya **A0**.

![Relay ya Grove imeunganishwa kwenye soketi ya D5, na kihisi cha unyevu wa udongo kimeunganishwa kwenye soketi ya A0](../../../../../translated_images/sw/pi-relay-and-soil-moisture-sensor.02f3198975b8c53e69ec716cd2719ce117700bd1fc933eaf93476c103c57939b.png)

1. Ingiza kihisi cha unyevu wa udongo kwenye udongo, ikiwa hakijaingizwa tayari kutoka somo la awali.

## Programu ya relay

Raspberry Pi sasa inaweza kupangwa kutumia relay iliyounganishwa.

### Kazi

Panga kifaa.

1. Washa Pi na subiri ianze.

1. Fungua mradi wa `soil-moisture-sensor` kutoka somo la mwisho kwenye VS Code ikiwa haujafunguliwa tayari. Utaongeza kwenye mradi huu.

1. Ongeza msimbo ufuatao kwenye faili ya `app.py` chini ya sehemu ya uingizaji iliyopo:

    ```python
    from grove.grove_relay import GroveRelay
    ```

    Tamko hili linaingiza `GroveRelay` kutoka maktaba za Python za Grove ili kuingiliana na relay ya Grove.

1. Ongeza msimbo ufuatao chini ya tamko la darasa la `ADC` ili kuunda mfano wa `GroveRelay`:

    ```python
    relay = GroveRelay(5)
    ```

    Hii inaunda relay kwa kutumia pini **D5**, pini ya kidigitali uliyoiunganisha na relay.

1. Ili kujaribu kama relay inafanya kazi, ongeza yafuatayo kwenye kitanzi cha `while True:`:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    Msimbo huu unawasha relay, unasubiri sekunde 0.5, kisha unazima relay.

1. Endesha programu ya Python. Relay itawashwa na kuzimwa kila sekunde 10, na kuchelewa kwa nusu sekunde kati ya kuwasha na kuzima. Utasikia relay ikibonyeza kuwasha kisha kuzima. LED kwenye bodi ya Grove itawaka wakati relay imewashwa, kisha itazima wakati relay imezimwa.

    ![Relay ikiwashwa na kuzimwa](../../../../../images/relay-turn-on-off.gif)

## Kudhibiti relay kutoka unyevu wa udongo

Sasa relay inafanya kazi, inaweza kudhibitiwa kulingana na usomaji wa unyevu wa udongo.

### Kazi

Dhibiti relay.

1. Futa mistari 3 ya msimbo uliyoongeza ili kujaribu relay. Badilisha na msimbo ufuatao:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    Msimbo huu unakagua kiwango cha unyevu wa udongo kutoka kwa kihisi cha unyevu wa udongo. Ikiwa kiko juu ya 450, inawasha relay, na inazima ikiwa kiko chini ya 450.

    > 💁 Kumbuka kihisi cha unyevu wa udongo cha capacitive husoma kwamba kiwango cha chini cha unyevu wa udongo, kuna unyevu zaidi kwenye udongo na kinyume chake.

1. Endesha programu ya Python. Utaona relay ikiwashwa au kuzimwa kulingana na kiwango cha unyevu wa udongo. Jaribu kwenye udongo mkavu, kisha ongeza maji.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Unaweza kupata msimbo huu kwenye folda ya [code-relay/pi](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/pi).

😀 Programu yako ya kihisi cha unyevu wa udongo kudhibiti relay imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.