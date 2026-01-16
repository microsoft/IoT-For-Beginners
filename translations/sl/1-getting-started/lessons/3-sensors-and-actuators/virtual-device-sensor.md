<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "11f10c6760fb8202cf368422702fdf70",
  "translation_date": "2025-08-28T14:17:00+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-sensor.md",
  "language_code": "sl"
}
-->
# Ustvarite nočno lučko - Virtualna IoT strojna oprema

V tem delu lekcije boste svoji virtualni IoT napravi dodali svetlobni senzor.

## Virtualna strojna oprema

Nočna lučka potrebuje en senzor, ustvarjen v aplikaciji CounterFit.

Senzor je **svetlobni senzor**. Pri fizični IoT napravi bi to bil [fotodiod](https://wikipedia.org/wiki/Photodiode), ki pretvarja svetlobo v električni signal. Svetlobni senzorji so analogni senzorji, ki pošiljajo celoštevilsko vrednost, ki označuje relativno količino svetlobe, vendar ta vrednost ni povezana z nobeno standardno mersko enoto, kot je [lux](https://wikipedia.org/wiki/Lux).

### Dodajte senzorje v CounterFit

Za uporabo virtualnega svetlobnega senzorja ga morate dodati v aplikacijo CounterFit.

#### Naloga - dodajte senzorje v CounterFit

Dodajte svetlobni senzor v aplikacijo CounterFit.

1. Prepričajte se, da spletna aplikacija CounterFit deluje iz prejšnjega dela naloge. Če ne, jo zaženite.

1. Ustvarite svetlobni senzor:

    1. V polju *Create sensor* v podoknu *Sensors* odprite spustni meni *Sensor type* in izberite *Light*.

    1. Pustite *Units* nastavljeno na *NoUnits*.

    1. Prepričajte se, da je *Pin* nastavljen na *0*.

    1. Kliknite gumb **Add**, da ustvarite svetlobni senzor na pinu 0.

    ![Nastavitve svetlobnega senzorja](../../../../../translated_images/sl/counterfit-create-light-sensor.9f36a5e0d4458d8d554d54b34d2c806d56093d6e49fddcda2d20f6fef7f5cce1.png)

    Svetlobni senzor bo ustvarjen in se bo pojavil na seznamu senzorjev.

    ![Ustvarjen svetlobni senzor](../../../../../translated_images/sl/counterfit-light-sensor.5d0f5584df56b90f6b2561910d9cb20dfbd73eeff2177c238d38f4de54aefae1.png)

## Programirajte svetlobni senzor

Zdaj lahko napravo programirate za uporabo vgrajenega svetlobnega senzorja.

### Naloga - programirajte svetlobni senzor

Programirajte napravo.

1. Odprite projekt nočne lučke v VS Code, ki ste ga ustvarili v prejšnjem delu naloge. Če je potrebno, ustavite in ponovno ustvarite terminal, da zagotovite, da deluje z virtualnim okoljem.

1. Odprite datoteko `app.py`.

1. Dodajte naslednjo kodo na vrh datoteke `app.py` skupaj z ostalimi stavki `import`, da uvozite potrebne knjižnice:

    ```python
    import time
    from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    Ukaz `import time` uvozi Pythonovo knjižnico `time`, ki bo uporabljena kasneje v tej nalogi.

    Ukaz `from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor` uvozi `GroveLightSensor` iz Pythonovih knjižnic CounterFit Grove shim. Ta knjižnica vsebuje kodo za interakcijo s svetlobnim senzorjem, ustvarjenim v aplikaciji CounterFit.

1. Dodajte naslednjo kodo na dno datoteke, da ustvarite primerek razreda, ki upravlja svetlobni senzor:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    Vrstica `light_sensor = GroveLightSensor(0)` ustvari primerek razreda `GroveLightSensor`, ki se poveže na pin **0** - CounterFit Grove pin, na katerega je povezan svetlobni senzor.

1. Dodajte neskončno zanko po zgornji kodi, da pridobite vrednost svetlobnega senzorja in jo izpišete v konzolo:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    To bo prebralo trenutno raven svetlobe z uporabo lastnosti `light` razreda `GroveLightSensor`. Ta lastnost prebere analogno vrednost iz pina. Ta vrednost se nato izpiše v konzolo.

1. Dodajte majhen premor enega sekunda na koncu zanke `while`, saj ni potrebno neprekinjeno preverjati ravni svetlobe. Premor zmanjša porabo energije naprave.

    ```python
    time.sleep(1)
    ```

1. V terminalu VS Code zaženite naslednji ukaz, da zaženete svojo Python aplikacijo:

    ```sh
    python3 app.py
    ```

    Vrednosti svetlobe bodo izpisane v konzolo. Na začetku bo ta vrednost 0.

1. V aplikaciji CounterFit spremenite vrednost svetlobnega senzorja, ki jo bo prebrala aplikacija. To lahko storite na dva načina:

    * Vnesite številko v polje *Value* za svetlobni senzor in nato kliknite gumb **Set**. Številka, ki jo vnesete, bo vrednost, ki jo senzor vrne.

    * Označite polje *Random* in vnesite vrednosti *Min* in *Max*, nato kliknite gumb **Set**. Vsakič, ko senzor prebere vrednost, bo prebral naključno številko med *Min* in *Max*.

    Vrednosti, ki jih nastavite, bodo izpisane v konzolo. Spremenite *Value* ali nastavitve *Random*, da se vrednost spremeni.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

> 💁 To kodo lahko najdete v mapi [code-sensor/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/virtual-device).

😀 Vaš program za nočno lučko je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna napačna razumevanja ali napačne interpretacije, ki bi nastale zaradi uporabe tega prevoda.