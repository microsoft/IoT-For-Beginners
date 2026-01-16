<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4db8a3879a53490513571df2f6cf7641",
  "translation_date": "2025-08-27T22:29:48+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-actuator.md",
  "language_code": "sw"
}
-->
# Jenga taa ya usiku - Raspberry Pi

Katika sehemu hii ya somo, utaongeza LED kwenye Raspberry Pi yako na kuitumia kuunda taa ya usiku.

## Vifaa

Taa ya usiku sasa inahitaji kifaa cha kutekeleza.

Kifaa cha kutekeleza ni **LED**, [diode inayotoa mwanga](https://wikipedia.org/wiki/Light-emitting_diode) ambayo hutoa mwanga wakati umeme unapita ndani yake. Hiki ni kifaa cha kidijitali chenye hali mbili, kuwashwa na kuzimwa. Kutuma thamani ya 1 huwasha LED, na 0 huzima. LED ni kifaa cha nje cha Grove na inahitaji kuunganishwa kwenye Grove Base hat kwenye Raspberry Pi.

Mantiki ya taa ya usiku katika pseudo-code ni:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Unganisha LED

LED ya Grove inakuja kama moduli yenye chaguo la LEDs, ikikuruhusu kuchagua rangi.

#### Kazi - unganisha LED

Unganisha LED.

![LED ya Grove](../../../../../translated_images/sw/grove-led.6c853be93f473cf2c439cfc74bb1064732b22251a83cedf66e62f783f9cc1a79.png)

1. Chagua LED unayoipenda na ingiza miguu yake kwenye mashimo mawili kwenye moduli ya LED.

    LEDs ni diodi zinazotoa mwanga, na diodi ni vifaa vya kielektroniki vinavyoweza kubeba umeme kwa njia moja tu. Hii inamaanisha kuwa LED inahitaji kuunganishwa kwa njia sahihi, vinginevyo haitafanya kazi.

    Moja ya miguu ya LED ni pini ya chanya, na nyingine ni pini ya hasi. LED si mviringo kabisa na ina upande mmoja ulio bapa kidogo. Upande ulio bapa kidogo ni pini ya hasi. Unapounganisha LED kwenye moduli, hakikisha pini iliyo karibu na upande wa mviringo imeunganishwa kwenye soketi iliyoandikwa **+** upande wa nje wa moduli, na upande ulio bapa umeunganishwa kwenye soketi iliyo karibu na katikati ya moduli.

1. Moduli ya LED ina kitufe cha kuzungusha kinachokuruhusu kudhibiti mwangaza. Anza kwa kukizungusha kabisa kwa kuzungusha kinyume na saa kwa kutumia bisibisi ndogo ya kichwa cha Phillips.

1. Ingiza mwisho mmoja wa kebo ya Grove kwenye soketi kwenye moduli ya LED. Itaingia kwa njia moja tu.

1. Ukiwa na Raspberry Pi imezimwa, unganisha mwisho mwingine wa kebo ya Grove kwenye soketi ya kidijitali iliyoandikwa **D5** kwenye Grove Base hat iliyounganishwa na Pi. Soketi hii ni ya pili kutoka kushoto, kwenye safu ya soketi karibu na pini za GPIO.

![LED ya Grove imeunganishwa kwenye soketi D5](../../../../../translated_images/sw/pi-led.97f1d474981dc35d1c7996c7b17de355d3d0a6bc9606d79fa5f89df933415122.png)

## Programu ya taa ya usiku

Taa ya usiku sasa inaweza kupangwa kwa kutumia sensor ya mwanga ya Grove na LED ya Grove.

### Kazi - panga taa ya usiku

Panga taa ya usiku.

1. Washa Pi na subiri ianze.

1. Fungua mradi wa taa ya usiku kwenye VS Code uliouunda katika sehemu ya awali ya kazi hii, iwe inafanya kazi moja kwa moja kwenye Pi au imeunganishwa kwa kutumia kiendelezi cha Remote SSH.

1. Ongeza msimbo ufuatao kwenye faili `app.py` ili kuingiza maktaba inayohitajika. Hii inapaswa kuongezwa juu, chini ya mistari mingine ya `import`.

    ```python
    from grove.grove_led import GroveLed
    ```

    Kauli `from grove.grove_led import GroveLed` inaingiza `GroveLed` kutoka kwenye maktaba za Python za Grove. Maktaba hii ina msimbo wa kuingiliana na LED ya Grove.

1. Ongeza msimbo ufuatao baada ya tamko la `light_sensor` ili kuunda mfano wa darasa linalosimamia LED:

    ```python
    led = GroveLed(5)
    ```

    Mstari `led = GroveLed(5)` huunda mfano wa darasa la `GroveLed` linalounganishwa na pini **D5** - pini ya kidijitali ya Grove ambayo LED imeunganishwa nayo.

    > 💁 Soketi zote zina namba za pini za kipekee. Pini 0, 2, 4, na 6 ni pini za analogi, pini 5, 16, 18, 22, 24, na 26 ni pini za kidijitali.

1. Ongeza ukaguzi ndani ya kitanzi cha `while`, na kabla ya `time.sleep` ili kukagua viwango vya mwanga na kuwasha au kuzima LED:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Msimbo huu hukagua thamani ya `light`. Ikiwa ni chini ya 300, inaita njia ya `on` ya darasa la `GroveLed` ambayo hutuma thamani ya kidijitali ya 1 kwa LED, kuiwasha. Ikiwa thamani ya mwanga ni kubwa au sawa na 300, inaita njia ya `off`, ikituma thamani ya kidijitali ya 0 kwa LED, kuizima.

    > 💁 Msimbo huu unapaswa kupangwa kwa kiwango sawa na mstari wa `print('Light level:', light)` ili uwe ndani ya kitanzi cha while!

    > 💁 Unapotuma thamani za kidijitali kwa vifaa vya kutekeleza, thamani ya 0 ni 0V, na thamani ya 1 ni voltage ya juu kwa kifaa. Kwa Raspberry Pi yenye sensor na vifaa vya Grove, voltage ya 1 ni 3.3V.

1. Kutoka kwenye Terminal ya VS Code, endesha yafuatayo ili kuendesha programu yako ya Python:

    ```sh
    python3 app.py
    ```

    Thamani za mwanga zitaonyeshwa kwenye koni.

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

1. Funika na funua sensor ya mwanga. Angalia jinsi LED inavyowaka ikiwa kiwango cha mwanga ni 300 au chini, na kuzima wakati kiwango cha mwanga ni zaidi ya 300.

    > 💁 Ikiwa LED haijawaka, hakikisha imeunganishwa kwa njia sahihi, na kitufe cha kuzungusha kimewekwa kwenye kiwango cha juu kabisa.

![LED imeunganishwa na Pi ikiwaka na kuzima kulingana na mabadiliko ya kiwango cha mwanga](../../../../../images/pi-running-assignment-1-1.gif)

> 💁 Unaweza kupata msimbo huu kwenye folda ya [code-actuator/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/pi).

😀 Programu yako ya taa ya usiku imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.