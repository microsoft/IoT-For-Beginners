# Valdykite relę - Raspberry Pi

Šioje pamokos dalyje pridėsite relę prie savo Raspberry Pi kartu su dirvožemio drėgmės jutikliu ir valdysite ją pagal dirvožemio drėgmės lygį.

## Aparatinė įranga

Raspberry Pi reikalinga relė.

Naudosite [Grove relę](https://www.seeedstudio.com/Grove-Relay.html), kuri yra paprastai atvira relė (tai reiškia, kad išėjimo grandinė yra atvira arba atjungta, kai į relę nėra siunčiamas signalas), galinti valdyti išėjimo grandines iki 250V ir 10A.

Tai yra skaitmeninis aktuatorius, todėl jis jungiamas prie skaitmeninio kaiščio ant Grove Base Hat.

### Prijunkite relę

Grove relę galima prijungti prie Raspberry Pi.

#### Užduotis

Prijunkite relę.

![Grove relė](../../../../../translated_images/lt/grove-relay.d426958ca210fbd0.webp)

1. Įkiškite vieną Grove kabelio galą į relės lizdą. Jis įsistatys tik viena kryptimi.

1. Išjungus Raspberry Pi, prijunkite kitą Grove kabelio galą prie skaitmeninio lizdo, pažymėto **D5**, esančio ant Grove Base Hat, prijungto prie Pi. Šis lizdas yra antras iš kairės, eilėje šalia GPIO kaiščių. Palikite dirvožemio drėgmės jutiklį prijungtą prie **A0** lizdo.

![Grove relė prijungta prie D5 lizdo, o dirvožemio drėgmės jutiklis prijungtas prie A0 lizdo](../../../../../translated_images/lt/pi-relay-and-soil-moisture-sensor.02f3198975b8c53e.webp)

1. Įkiškite dirvožemio drėgmės jutiklį į dirvą, jei jis dar nėra įkištas iš ankstesnės pamokos.

## Programuokite relę

Dabar Raspberry Pi galima užprogramuoti naudoti prijungtą relę.

### Užduotis

Programuokite įrenginį.

1. Įjunkite Pi ir palaukite, kol jis įsijungs.

1. Atidarykite `soil-moisture-sensor` projektą iš ankstesnės pamokos VS Code, jei jis dar neatidarytas. Jūs papildysite šį projektą.

1. Pridėkite šį kodą į `app.py` failą po esamų importų:

    ```python
    from grove.grove_relay import GroveRelay
    ```

    Šis sakinys importuoja `GroveRelay` iš Grove Python bibliotekų, kad galėtumėte sąveikauti su Grove rele.

1. Pridėkite šį kodą po `ADC` klasės deklaracijos, kad sukurtumėte `GroveRelay` egzempliorių:

    ```python
    relay = GroveRelay(5)
    ```

    Tai sukuria relę, naudojant **D5** kaištį, prie kurio prijungėte relę.

1. Norėdami patikrinti, ar relė veikia, pridėkite šį kodą į `while True:` ciklą:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    Kodas įjungia relę, laukia 0,5 sekundės, tada išjungia relę.

1. Paleiskite Python programą. Relė įsijungs ir išsijungs kas 10 sekundžių, su pusės sekundės pertrauka tarp įjungimo ir išjungimo. Išgirsite, kaip relė spragteli įsijungdama ir išsijungdama. Grove plokštės LED užsidegs, kai relė bus įjungta, ir užges, kai relė bus išjungta.

    ![Relė įsijungia ir išsijungia](../../../../../images/relay-turn-on-off.gif)

## Valdykite relę pagal dirvožemio drėgmę

Dabar, kai relė veikia, ją galima valdyti pagal dirvožemio drėgmės rodmenis.

### Užduotis

Valdykite relę.

1. Ištrinkite 3 kodo eilutes, kurias pridėjote, kad patikrintumėte relę. Pakeiskite jas šiuo kodu:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    Šis kodas tikrina dirvožemio drėgmės lygį iš dirvožemio drėgmės jutiklio. Jei jis viršija 450, relė įjungiama, o jei nukrenta žemiau 450, relė išjungiama.

    > 💁 Atminkite, kad talpinis dirvožemio drėgmės jutiklis rodo: kuo mažesnis dirvožemio drėgmės lygis, tuo daugiau drėgmės yra dirvoje, ir atvirkščiai.

1. Paleiskite Python programą. Pamatysite, kaip relė įsijungia arba išsijungia, priklausomai nuo dirvožemio drėgmės lygio. Išbandykite sausame dirvožemyje, tada pridėkite vandens.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Šį kodą galite rasti [code-relay/pi](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/pi) aplanke.

😀 Jūsų programa, valdanti relę pagal dirvožemio drėgmės jutiklį, buvo sėkminga!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant dirbtinio intelekto vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, atkreipiame dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus aiškinimus, kylančius dėl šio vertimo naudojimo.