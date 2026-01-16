<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2bf65f162bcebd35fbcba5fd245afac4",
  "translation_date": "2025-08-28T14:40:43+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/virtual-device-soil-moisture.md",
  "language_code": "hr"
}
-->
# Mjerenje vlažnosti tla - Virtualni IoT hardver

U ovom dijelu lekcije, dodat ćete kapacitivni senzor vlažnosti tla svom virtualnom IoT uređaju i očitati vrijednosti s njega.

## Virtualni hardver

Virtualni IoT uređaj koristit će simulirani Grove kapacitivni senzor vlažnosti tla. Ovo omogućuje da laboratorij ostane isti kao korištenje Raspberry Pi uređaja s fizičkim Grove kapacitivnim senzorom vlažnosti tla.

Na fizičkom IoT uređaju, senzor vlažnosti tla bio bi kapacitivni senzor koji mjeri vlažnost tla detektiranjem kapaciteta tla, svojstva koje se mijenja ovisno o vlažnosti tla. Kako se vlažnost tla povećava, napon se smanjuje.

Ovo je analogni senzor, pa koristi simulirani 10-bitni ADC za prijavu vrijednosti od 1 do 1.023.

### Dodavanje senzora vlažnosti tla u CounterFit

Za korištenje virtualnog senzora vlažnosti tla, potrebno ga je dodati u CounterFit aplikaciju.

#### Zadatak - Dodavanje senzora vlažnosti tla u CounterFit

Dodajte senzor vlažnosti tla u CounterFit aplikaciju.

1. Kreirajte novu Python aplikaciju na svom računalu u mapi nazvanoj `soil-moisture-sensor` s jednim datotekama nazvanim `app.py` i Python virtualnim okruženjem, te dodajte CounterFit pip pakete.

    > ⚠️ Možete se referirati na [upute za kreiranje i postavljanje CounterFit Python projekta u lekciji 1 ako je potrebno](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Provjerite je li CounterFit web aplikacija pokrenuta.

1. Kreirajte senzor vlažnosti tla:

    1. U okviru *Create sensor* u *Sensors* panelu, otvorite padajući izbornik *Sensor type* i odaberite *Soil Moisture*.

    1. Ostavite *Units* postavljen na *NoUnits*.

    1. Provjerite je li *Pin* postavljen na *0*.

    1. Kliknite gumb **Add** za kreiranje senzora *Soil Moisture* na pinu 0.

    ![Postavke senzora vlažnosti tla](../../../../../translated_images/hr/counterfit-create-soil-moisture-sensor.35266135a5e0ae68b29a684d7db0d2933a8098b2307d197f7c71577b724603aa.png)

    Senzor vlažnosti tla bit će kreiran i pojavit će se na popisu senzora.

    ![Kreirani senzor vlažnosti tla](../../../../../translated_images/hr/counterfit-soil-moisture-sensor.81742b2de0e9de60a3b3b9a2ff8ecc686d428eb6d71820f27a693be26e5aceee.png)

## Programiranje aplikacije za senzor vlažnosti tla

Aplikacija za senzor vlažnosti tla sada se može programirati koristeći CounterFit senzore.

### Zadatak - Programiranje aplikacije za senzor vlažnosti tla

Programirajte aplikaciju za senzor vlažnosti tla.

1. Provjerite je li aplikacija `soil-moisture-sensor` otvorena u VS Code.

1. Otvorite datoteku `app.py`.

1. Dodajte sljedeći kod na vrh datoteke `app.py` za povezivanje aplikacije s CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Dodajte sljedeći kod u datoteku `app.py` za uvoz potrebnih biblioteka:

    ```python
    import time
    from counterfit_shims_grove.adc import ADC
    ```

    Izjava `import time` uvozi modul `time` koji će se kasnije koristiti u ovom zadatku.

    Izjava `from counterfit_shims_grove.adc import ADC` uvozi klasu `ADC` za interakciju s virtualnim analogno-digitalnim pretvaračem koji se može povezati s CounterFit senzorom.

1. Dodajte sljedeći kod ispod ovoga za kreiranje instance klase `ADC`:

    ```python
    adc = ADC()
    ```

1. Dodajte beskonačnu petlju koja čita vrijednosti s ovog ADC-a na pinu 0 i zapisuje rezultat u konzolu. Ova petlja može zatim pauzirati 10 sekundi između očitanja.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)
    
        time.sleep(10)
    ```

1. U CounterFit aplikaciji, promijenite vrijednost senzora vlažnosti tla koju će aplikacija očitati. To možete učiniti na dva načina:

    * Unesite broj u okvir *Value* za senzor vlažnosti tla, zatim kliknite gumb **Set**. Broj koji unesete bit će vrijednost koju senzor vraća.

    * Označite kućicu *Random* i unesite *Min* i *Max* vrijednosti, zatim kliknite gumb **Set**. Svaki put kada senzor očita vrijednost, očitat će nasumični broj između *Min* i *Max*.

1. Pokrenite Python aplikaciju. Vidjet ćete mjerenja vlažnosti tla zapisana u konzolu. Promijenite *Value* ili postavke *Random* kako biste vidjeli promjenu vrijednosti.

    ```output
    (.venv) ➜ soil-moisture-sensor $ python app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

> 💁 Ovaj kod možete pronaći u mapi [code/virtual-device](../../../../../2-farm/lessons/2-detect-soil-moisture/code/virtual-device).

😀 Vaša aplikacija za senzor vlažnosti tla bila je uspješna!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za kritične informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za bilo kakva nesporazuma ili pogrešna tumačenja koja proizlaze iz korištenja ovog prijevoda.