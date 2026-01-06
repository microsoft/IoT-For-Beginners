<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7f4ad0ef54f248b85b92187c94cf9dcb",
  "translation_date": "2025-08-27T22:34:17+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-sensor.md",
  "language_code": "sw"
}
-->
# Ongeza kihisi - Wio Terminal

Katika sehemu hii ya somo, utatumia kihisi cha mwanga kwenye Wio Terminal yako.

## Vifaa

Kihisi cha somo hili ni **kihisi cha mwanga** kinachotumia [photodiode](https://wikipedia.org/wiki/Photodiode) kubadilisha mwanga kuwa ishara ya umeme. Hiki ni kihisi cha analogi kinachotuma thamani ya nambari kutoka 0 hadi 1,023, ikionyesha kiasi cha mwanga cha kulinganisha ambacho hakina kipimo cha kawaida kama [lux](https://wikipedia.org/wiki/Lux).

Kihisi cha mwanga kimejengwa ndani ya Wio Terminal na kinaonekana kupitia dirisha la plastiki la wazi nyuma.

![Kihisi cha mwanga nyuma ya Wio Terminal](../../../../../translated_images/wio-light-sensor.b1f529f3c95f5165.sw.png)

## Programu ya kihisi cha mwanga

Kifaa sasa kinaweza kupangwa kutumia kihisi cha mwanga kilichojengwa ndani.

### Kazi

Panga kifaa.

1. Fungua mradi wa taa ya usiku kwenye VS Code uliouunda katika sehemu ya awali ya kazi hii.

1. Ongeza mstari ufuatao chini ya kazi ya `setup`:

    ```cpp
    pinMode(WIO_LIGHT, INPUT);
    ```

    Mstari huu unaseti pini zinazotumika kuwasiliana na vifaa vya kihisi.

    Pini ya `WIO_LIGHT` ni nambari ya pini ya GPIO iliyounganishwa na kihisi cha mwanga kilichojengwa ndani. Pini hii imewekwa kuwa `INPUT`, ikimaanisha inaunganishwa na kihisi na data itasomwa kutoka kwenye pini.

1. Futa yaliyomo kwenye kazi ya `loop`.

1. Ongeza msimbo ufuatao kwenye kazi ya `loop` ambayo sasa ni tupu.

    ```cpp
    int light = analogRead(WIO_LIGHT);
    Serial.print("Light value: ");
    Serial.println(light);
    ```

    Msimbo huu unasoma thamani ya analogi kutoka kwenye pini ya `WIO_LIGHT`. Hii inasoma thamani kutoka 0-1,023 kutoka kwenye kihisi cha mwanga kilichojengwa ndani. Thamani hii kisha inatumwa kwenye bandari ya serial ili uweze kuisoma kwenye Serial Monitor wakati msimbo huu unafanya kazi. `Serial.print` inaandika maandishi bila mstari mpya mwishoni, kwa hivyo kila mstari utaanza na `Light value:` na kuishia na thamani halisi ya mwanga.

1. Ongeza ucheleweshaji mdogo wa sekunde moja (1,000ms) mwishoni mwa `loop` kwani viwango vya mwanga havihitaji kuchunguzwa kila wakati. Ucheleweshaji unapunguza matumizi ya nguvu ya kifaa.

    ```cpp
    delay(1000);
    ```

1. Unganisha tena Wio Terminal kwenye kompyuta yako, na pakia msimbo mpya kama ulivyofanya awali.

1. Unganisha Serial Monitor. Thamani za mwanga zitaonyeshwa kwenye terminal. Funika na funua kihisi cha mwanga nyuma ya Wio Terminal, na thamani zitabadilika.

    ```output
    > Executing task: platformio device monitor <

    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Light value: 4
    Light value: 5
    Light value: 4
    Light value: 158
    Light value: 343
    Light value: 348
    Light value: 344
    ```

> 💁 Unaweza kupata msimbo huu kwenye folda ya [code-sensor/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/wio-terminal).

😀 Kuongeza kihisi kwenye programu yako ya taa ya usiku kulifanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.