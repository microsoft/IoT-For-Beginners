# Izradite noćno svjetlo - Virtualni IoT hardver

U ovom dijelu lekcije dodat ćete senzor svjetla svom virtualnom IoT uređaju.

## Virtualni hardver

Noćnom svjetlu potreban je jedan senzor, kreiran u aplikaciji CounterFit.

Taj senzor je **senzor svjetla**. Na fizičkom IoT uređaju to bi bio [fotodioda](https://wikipedia.org/wiki/Photodiode) koja pretvara svjetlost u električni signal. Senzori svjetla su analogni senzori koji šalju cjelobrojnu vrijednost koja označava relativnu količinu svjetla, ali ne odgovara nijednoj standardnoj jedinici mjere poput [luks](https://wikipedia.org/wiki/Lux).

### Dodavanje senzora u CounterFit

Za korištenje virtualnog senzora svjetla, potrebno ga je dodati u aplikaciju CounterFit.

#### Zadatak - dodavanje senzora u CounterFit

Dodajte senzor svjetla u aplikaciju CounterFit.

1. Provjerite je li CounterFit web aplikacija pokrenuta iz prethodnog dijela zadatka. Ako nije, pokrenite je.

1. Kreirajte senzor svjetla:

    1. U okviru *Create sensor* u odjeljku *Sensors*, otvorite padajući izbornik *Sensor type* i odaberite *Light*.

    1. Ostavite *Units* postavljeno na *NoUnits*.

    1. Provjerite je li *Pin* postavljen na *0*.

    1. Kliknite na gumb **Add** kako biste kreirali senzor svjetla na pinu 0.

    ![Postavke senzora svjetla](../../../../../translated_images/hr/counterfit-create-light-sensor.9f36a5e0d4458d8d.webp)

    Senzor svjetla će biti kreiran i pojavit će se na popisu senzora.

    ![Kreirani senzor svjetla](../../../../../translated_images/hr/counterfit-light-sensor.5d0f5584df56b90f.webp)

## Programiranje senzora svjetla

Uređaj sada može biti programiran za korištenje ugrađenog senzora svjetla.

### Zadatak - programiranje senzora svjetla

Programirajte uređaj.

1. Otvorite projekt noćnog svjetla u VS Code koji ste kreirali u prethodnom dijelu zadatka. Ako je potrebno, zatvorite i ponovno otvorite terminal kako biste osigurali da radi s virtualnim okruženjem.

1. Otvorite datoteku `app.py`.

1. Dodajte sljedeći kod na vrh datoteke `app.py` uz ostale `import` naredbe kako biste uvezli potrebne biblioteke:

    ```python
    import time
    from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    Naredba `import time` uvozi Python modul `time` koji će se koristiti kasnije u ovom zadatku.

    Naredba `from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor` uvozi `GroveLightSensor` iz CounterFit Grove shim Python biblioteka. Ova biblioteka sadrži kod za interakciju sa senzorom svjetla kreiranim u aplikaciji CounterFit.

1. Dodajte sljedeći kod na dno datoteke kako biste kreirali instance klasa koje upravljaju senzorom svjetla:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    Linija `light_sensor = GroveLightSensor(0)` kreira instancu klase `GroveLightSensor` povezanu s pinom **0** - CounterFit Grove pin na koji je povezan senzor svjetla.

1. Dodajte beskonačnu petlju nakon gore navedenog koda kako biste očitavali vrijednost senzora svjetla i ispisivali je u konzolu:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Ovo će očitati trenutnu razinu svjetla koristeći svojstvo `light` klase `GroveLightSensor`. Ovo svojstvo očitava analognu vrijednost s pina. Ta vrijednost se zatim ispisuje u konzolu.

1. Dodajte kratku pauzu od jedne sekunde na kraju `while` petlje jer nije potrebno kontinuirano provjeravati razine svjetla. Pauza smanjuje potrošnju energije uređaja.

    ```python
    time.sleep(1)
    ```

1. Iz terminala u VS Code-u pokrenite sljedeće kako biste pokrenuli svoju Python aplikaciju:

    ```sh
    python3 app.py
    ```

    Vrijednosti svjetla će se ispisivati u konzolu. Početna vrijednost će biti 0.

1. U aplikaciji CounterFit promijenite vrijednost senzora svjetla koju će aplikacija očitati. To možete učiniti na jedan od dva načina:

    * Unesite broj u okvir *Value* za senzor svjetla, a zatim kliknite na gumb **Set**. Broj koji unesete bit će vrijednost koju senzor vraća.

    * Označite kućicu *Random* i unesite vrijednosti *Min* i *Max*, a zatim kliknite na gumb **Set**. Svaki put kada senzor očita vrijednost, očitat će nasumičan broj između *Min* i *Max*.

    Vrijednosti koje postavite ispisivat će se u konzolu. Promijenite *Value* ili postavke *Random* kako biste promijenili vrijednost.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

> 💁 Ovaj kod možete pronaći u mapi [code-sensor/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/virtual-device).

😀 Vaš program za noćno svjetlo je uspješno završen!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za kritične informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za nesporazume ili pogrešna tumačenja koja mogu proizaći iz korištenja ovog prijevoda.