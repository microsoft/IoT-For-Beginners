# Sukurkite naktinę lemputę - Virtuali IoT aparatinė įranga

Šioje pamokos dalyje pridėsite LED prie savo virtualaus IoT įrenginio ir naudosite jį naktinei lemputei sukurti.

## Virtuali aparatinė įranga

Naktinei lemputei reikalingas vienas aktuatorius, sukurtas CounterFit programėlėje.

Aktuatorius yra **LED**. Fizinėje IoT įrangoje tai būtų [šviesos diodas](https://wikipedia.org/wiki/Light-emitting_diode), kuris skleidžia šviesą, kai per jį teka srovė. Tai yra skaitmeninis aktuatorius, turintis 2 būsenas: įjungta ir išjungta. Siunčiant reikšmę 1, LED įsijungia, o siunčiant 0 – išsijungia.

Naktinės lemputės logika pseudo-kode:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Pridėkite aktuatorių į CounterFit

Norėdami naudoti virtualų LED, turite jį pridėti prie CounterFit programėlės.

#### Užduotis - pridėti aktuatorių į CounterFit

Pridėkite LED į CounterFit programėlę.

1. Įsitikinkite, kad CounterFit internetinė programėlė veikia nuo ankstesnės užduoties dalies. Jei ne, paleiskite ją iš naujo ir pridėkite šviesos jutiklį.

1. Sukurkite LED:

    1. *Create actuator* laukelyje, esančiame *Actuator* skydelyje, išskleiskite *Actuator type* laukelį ir pasirinkite *LED*.

    1. Nustatykite *Pin* į *5*.

    1. Paspauskite mygtuką **Add**, kad sukurtumėte LED ant 5 kaiščio.

    ![LED nustatymai](../../../../../translated_images/lt/counterfit-create-led.ba9db1c9b8c622a6.webp)

    LED bus sukurtas ir pasirodys aktuatorių sąraše.

    ![Sukurtas LED](../../../../../translated_images/lt/counterfit-led.c0ab02de6d256ad8.webp)

    Kai LED bus sukurtas, galite pakeisti jo spalvą naudodami *Color* pasirinkimo įrankį. Pasirinkite mygtuką **Set**, kad pakeistumėte spalvą po jos pasirinkimo.

### Programuokite naktinę lemputę

Dabar naktinė lemputė gali būti programuojama naudojant CounterFit šviesos jutiklį ir LED.

#### Užduotis - programuokite naktinę lemputę

Programuokite naktinę lemputę.

1. Atidarykite naktinės lemputės projektą VS Code, kurį sukūrėte ankstesnėje užduoties dalyje. Jei reikia, uždarykite ir iš naujo paleiskite terminalą, kad įsitikintumėte, jog jis veikia naudojant virtualią aplinką.

1. Atidarykite `app.py` failą.

1. Pridėkite šį kodą į `app.py` failo viršų, po kitomis `import` eilutėmis, kad importuotumėte reikalingą biblioteką.

    ```python
    from counterfit_shims_grove.grove_led import GroveLed
    ```

    `from counterfit_shims_grove.grove_led import GroveLed` eilutė importuoja `GroveLed` iš CounterFit Grove shim Python bibliotekų. Ši biblioteka turi kodą, skirtą sąveikai su LED, sukurtu CounterFit programėlėje.

1. Pridėkite šį kodą po `light_sensor` deklaracija, kad sukurtumėte klasės egzempliorių, kuris valdo LED:

    ```python
    led = GroveLed(5)
    ```

    Eilutė `led = GroveLed(5)` sukuria `GroveLed` klasės egzempliorių, prijungtą prie **5** kaiščio – CounterFit Grove kaiščio, prie kurio prijungtas LED.

1. Pridėkite patikrinimą `while` ciklo viduje, prieš `time.sleep`, kad patikrintumėte šviesos lygį ir įjungtumėte arba išjungtumėte LED:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Šis kodas tikrina `light` reikšmę. Jei ji mažesnė nei 300, kviečia `on` metodą iš `GroveLed` klasės, kuris siunčia skaitmeninę reikšmę 1 į LED, įjungdamas jį. Jei šviesos reikšmė yra didesnė arba lygi 300, kviečia `off` metodą, siunčiant skaitmeninę reikšmę 0 į LED, išjungdamas jį.

    > 💁 Šis kodas turėtų būti įtrauktas į tą patį lygį kaip `print('Light level:', light)` eilutė, kad būtų `while` ciklo viduje!

1. VS Code terminale paleiskite šią komandą, kad paleistumėte savo Python programą:

    ```sh
    python3 app.py
    ```

    Šviesos reikšmės bus išvestos į konsolę.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

1. Pakeiskite *Value* arba *Random* nustatymus, kad šviesos lygis kistų virš ir žemiau 300. LED įsijungs ir išsijungs.

![LED CounterFit programėlėje įsijungia ir išsijungia keičiantis šviesos lygiui](../../../../../images/virtual-device-running-assignment-1-1.gif)

> 💁 Šį kodą galite rasti [code-actuator/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/virtual-device) aplanke.

😀 Jūsų naktinės lemputės programa buvo sėkminga!

---

**Atsakomybės atsisakymas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.