<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "db44083b4dc6fb06eac83c4f16448940",
  "translation_date": "2025-08-28T20:09:34+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-actuator.md",
  "language_code": "lt"
}
-->
# Sukurkite naktinę lemputę - Wio Terminal

Šioje pamokos dalyje pridėsite LED prie savo Wio Terminal ir naudosite jį naktinei lemputei sukurti.

## Aparatinė įranga

Dabar naktinei lemputei reikia vykdyklio.

Vykdyklis yra **LED**, [šviesos diodas](https://wikipedia.org/wiki/Light-emitting_diode), kuris skleidžia šviesą, kai per jį teka srovė. Tai yra skaitmeninis vykdyklis, turintis 2 būsenas: įjungta ir išjungta. Siunčiant reikšmę 1, LED įsijungia, o siunčiant 0 - išsijungia. Tai yra išorinis Grove vykdyklis, kurį reikia prijungti prie Wio Terminal.

Naktinės lemputės logika pseudo-kode yra tokia:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Prijunkite LED

Grove LED pateikiamas kaip modulis su kelių spalvų LED pasirinkimu, leidžiančiu pasirinkti norimą spalvą.

#### Užduotis - prijunkite LED

Prijunkite LED.

![Grove LED](../../../../../translated_images/lt/grove-led.6c853be93f473cf2c439cfc74bb1064732b22251a83cedf66e62f783f9cc1a79.png)

1. Pasirinkite mėgstamą LED ir įstatykite jo kojeles į dvi skyles LED modulyje.

    LED yra šviesos diodai, o diodai yra elektroniniai įrenginiai, kurie leidžia srovei tekėti tik viena kryptimi. Tai reiškia, kad LED turi būti prijungtas tinkama kryptimi, kitaip jis neveiks.

    Viena iš LED kojelių yra teigiamas kontaktas, kita - neigiamas. LED nėra visiškai apvalus ir viena jo pusė yra šiek tiek plokštesnė. Ši plokštesnė pusė yra neigiamas kontaktas. Prijungdami LED prie modulio, įsitikinkite, kad kojelė prie apvalesnės pusės yra prijungta prie lizdo, pažymėto **+** modulio išorėje, o plokštesnė pusė - prie lizdo, esančio arčiau modulio vidurio.

1. LED modulis turi sukamą mygtuką, leidžiantį reguliuoti ryškumą. Pradžioje pasukite jį iki galo prieš laikrodžio rodyklę, naudodami mažą kryžminį atsuktuvą.

1. Įstatykite vieną Grove kabelio galą į LED modulio lizdą. Jis įsistatys tik viena kryptimi.

1. Atjungę Wio Terminal nuo kompiuterio ar kito maitinimo šaltinio, prijunkite kitą Grove kabelio galą prie dešiniojo Grove lizdo Wio Terminal, žiūrint į ekraną. Tai yra lizdas, esantis toliausiai nuo maitinimo mygtuko.

    > 💁 Dešinysis Grove lizdas gali būti naudojamas su analoginiais arba skaitmeniniais jutikliais ir vykdykliais. Kairysis lizdas skirtas tik skaitmeniniams jutikliams ir vykdykliams. C bus aptarta vėlesnėje pamokoje.

![Grove LED prijungtas prie dešiniojo lizdo](../../../../../translated_images/lt/wio-led.265a1897e72d7f21.webp)

## Užprogramuokite naktinę lemputę

Dabar naktinę lemputę galima užprogramuoti naudojant įmontuotą šviesos jutiklį ir Grove LED.

### Užduotis - užprogramuokite naktinę lemputę

Užprogramuokite naktinę lemputę.

1. Atidarykite naktinės lemputės projektą VS Code, kurį sukūrėte ankstesnėje šios užduoties dalyje.

1. Pridėkite šią eilutę į `setup` funkcijos apačią:

    ```cpp
    pinMode(D0, OUTPUT);
    ```

    Ši eilutė konfigūruoja piną, naudojamą bendrauti su LED per Grove portą.

    `D0` pinas yra skaitmeninis pinas dešiniajam Grove lizdui. Šis pinas nustatytas kaip `OUTPUT`, tai reiškia, kad jis jungiasi prie vykdyklio, ir duomenys bus rašomi į šį piną.

1. Pridėkite šį kodą iškart prieš `delay` funkciją cikle:

    ```cpp
    if (light < 300)
    {
        digitalWrite(D0, HIGH);
    }
    else
    {
        digitalWrite(D0, LOW);
    }
    ```

    Šis kodas tikrina `light` reikšmę. Jei ji yra mažesnė nei 300, į `D0` skaitmeninį piną siunčiama `HIGH` reikšmė. Ši `HIGH` reikšmė yra 1, įjungiant LED. Jei šviesos lygis yra didesnis arba lygus 300, į piną siunčiama `LOW` reikšmė, išjungiant LED.

    > 💁 Siunčiant skaitmenines reikšmes vykdykliams, LOW reikšmė yra 0V, o HIGH reikšmė yra maksimali įrenginio įtampa. Wio Terminal atveju HIGH įtampa yra 3.3V.

1. Prijunkite Wio Terminal prie kompiuterio ir įkelkite naują kodą, kaip darėte anksčiau.

1. Prijunkite Serial Monitor. Šviesos reikšmės bus išvedamos į terminalą.

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

1. Uždenkite ir atidenkite šviesos jutiklį. Pastebėkite, kaip LED įsijungia, jei šviesos lygis yra 300 ar mažesnis, ir išsijungia, kai šviesos lygis yra didesnis nei 300.

![LED, prijungtas prie WIO, įsijungia ir išsijungia keičiantis šviesos lygiui](../../../../../images/wio-running-assignment-1-1.gif)

> 💁 Šį kodą galite rasti [code-actuator/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/wio-terminal) aplanke.

😀 Jūsų naktinės lemputės programa pavyko!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama profesionali žmogaus vertimo paslauga. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius naudojant šį vertimą.