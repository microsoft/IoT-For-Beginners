<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c640f93263fd9adbfda920739e09feb",
  "translation_date": "2025-08-27T22:28:56+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-actuator.md",
  "language_code": "sw"
}
-->
# Jenga taa ya usiku - Vifaa vya IoT vya Kijumla

Katika sehemu hii ya somo, utaongeza LED kwenye kifaa chako cha IoT cha kijumla na kuitumia kuunda taa ya usiku.

## Vifaa vya Kijumla

Taa ya usiku inahitaji kiendeshaji kimoja, kilichoundwa katika programu ya CounterFit.

Kiendeshaji ni **LED**. Katika kifaa halisi cha IoT, ingekuwa [diode inayotoa mwanga](https://wikipedia.org/wiki/Light-emitting_diode) ambayo hutoa mwanga wakati umeme unapita ndani yake. Hii ni kiendeshaji cha kidijitali chenye hali mbili, kuwashwa na kuzimwa. Kutuma thamani ya 1 huwasha LED, na 0 huzima.

Mantiki ya taa ya usiku katika pseudo-code ni:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Ongeza kiendeshaji kwenye CounterFit

Ili kutumia LED ya kijumla, unahitaji kuiongeza kwenye programu ya CounterFit.

#### Kazi - ongeza kiendeshaji kwenye CounterFit

Ongeza LED kwenye programu ya CounterFit.

1. Hakikisha programu ya wavuti ya CounterFit inaendelea kutoka sehemu ya awali ya kazi hii. Ikiwa haipo, ianzishe tena na ongeza tena kihisi mwanga.

1. Unda LED:

    1. Katika kisanduku cha *Create actuator* kwenye paneli ya *Actuator*, shusha kisanduku cha *Actuator type* na chagua *LED*.

    1. Weka *Pin* kuwa *5*.

    1. Chagua kitufe cha **Add** kuunda LED kwenye Pin 5.

    ![Mipangilio ya LED](../../../../../translated_images/sw/counterfit-create-led.ba9db1c9b8c622a635d6dfae5cdc4e70c2b250635bd4f0601c6cf0bd22b7ba46.png)

    LED itaundwa na itaonekana kwenye orodha ya viendeshaji.

    ![LED iliyoundwa](../../../../../translated_images/sw/counterfit-led.c0ab02de6d256ad84d9bad4d67a7faa709f0ea83e410cfe9b5561ef0cef30b1c.png)

    Mara LED inapoundwa, unaweza kubadilisha rangi kwa kutumia kiondoa rangi cha *Color*. Chagua kitufe cha **Set** kubadilisha rangi baada ya kuchagua.

### Programu ya taa ya usiku

Sasa taa ya usiku inaweza kupangwa kwa kutumia kihisi mwanga na LED ya CounterFit.

#### Kazi - panga taa ya usiku

Panga taa ya usiku.

1. Fungua mradi wa taa ya usiku katika VS Code uliouunda katika sehemu ya awali ya kazi hii. Zima na unda tena terminal ili kuhakikisha inafanya kazi kwa kutumia mazingira ya kijumla ikiwa ni lazima.

1. Fungua faili `app.py`.

1. Ongeza msimbo ufuatao kwenye faili `app.py` ili kuingiza maktaba inayohitajika. Hii inapaswa kuongezwa juu, chini ya mistari mingine ya `import`.

    ```python
    from counterfit_shims_grove.grove_led import GroveLed
    ```

    Kauli `from counterfit_shims_grove.grove_led import GroveLed` inaingiza `GroveLed` kutoka maktaba za Python za CounterFit Grove shim. Maktaba hii ina msimbo wa kuingiliana na LED iliyoundwa katika programu ya CounterFit.

1. Ongeza msimbo ufuatao baada ya tamko la `light_sensor` ili kuunda mfano wa darasa linalosimamia LED:

    ```python
    led = GroveLed(5)
    ```

    Mstari `led = GroveLed(5)` unaunda mfano wa darasa la `GroveLed` linalounganishwa na pini **5** - pini ya CounterFit Grove ambayo LED imeunganishwa.

1. Ongeza ukaguzi ndani ya kitanzi cha `while`, na kabla ya `time.sleep` ili kukagua viwango vya mwanga na kuwasha au kuzima LED:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Msimbo huu hukagua thamani ya `light`. Ikiwa ni chini ya 300, inaita njia ya `on` ya darasa la `GroveLed` ambayo hutuma thamani ya kidijitali ya 1 kwa LED, kuiwasha. Ikiwa thamani ya mwanga ni kubwa au sawa na 300, inaita njia ya `off`, ikituma thamani ya kidijitali ya 0 kwa LED, kuiwasha.

    > 💁 Msimbo huu unapaswa kupangwa kwa kiwango sawa na mstari wa `print('Light level:', light)` ili kuwa ndani ya kitanzi cha while!

1. Kutoka kwenye Terminal ya VS Code, endesha amri ifuatayo kuendesha programu yako ya Python:

    ```sh
    python3 app.py
    ```

    Thamani za mwanga zitaonyeshwa kwenye terminal.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

1. Badilisha mipangilio ya *Value* au *Random* ili kubadilisha kiwango cha mwanga juu na chini ya 300. LED itawaka na kuzima.

![LED katika programu ya CounterFit ikiwaka na kuzima kadri kiwango cha mwanga kinavyobadilika](../../../../../images/virtual-device-running-assignment-1-1.gif)

> 💁 Unaweza kupata msimbo huu katika folda ya [code-actuator/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/virtual-device).

😀 Programu yako ya taa ya usiku imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuchukuliwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.