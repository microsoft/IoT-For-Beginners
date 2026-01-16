<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2bf65f162bcebd35fbcba5fd245afac4",
  "translation_date": "2025-08-28T14:41:03+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/virtual-device-soil-moisture.md",
  "language_code": "sl"
}
-->
# Merjenje vlažnosti tal - Virtualna IoT strojna oprema

V tem delu lekcije boste svoji virtualni IoT napravi dodali kapacitivni senzor za merjenje vlažnosti tal in prebrali vrednosti iz njega.

## Virtualna strojna oprema

Virtualna IoT naprava bo uporabljala simuliran Grove kapacitivni senzor za merjenje vlažnosti tal. To omogoča, da je ta laboratorijska vaja enaka kot uporaba Raspberry Pi z dejanskim Grove kapacitivnim senzorjem za merjenje vlažnosti tal.

Pri fizični IoT napravi bi bil senzor za merjenje vlažnosti tal kapacitivni senzor, ki meri vlažnost tal z zaznavanjem kapacitivnosti tal, lastnosti, ki se spreminja glede na vlažnost tal. Ko se vlažnost tal poveča, se napetost zmanjša.

To je analogni senzor, zato uporablja simuliran 10-bitni ADC za poročanje vrednosti od 1 do 1.023.

### Dodajanje senzorja za merjenje vlažnosti tal v CounterFit

Za uporabo virtualnega senzorja za merjenje vlažnosti tal ga morate dodati v aplikacijo CounterFit.

#### Naloga - Dodajanje senzorja za merjenje vlažnosti tal v CounterFit

Dodajte senzor za merjenje vlažnosti tal v aplikacijo CounterFit.

1. Na svojem računalniku ustvarite novo Python aplikacijo v mapi `soil-moisture-sensor` z eno datoteko z imenom `app.py` in Python virtualnim okoljem ter dodajte CounterFit pip pakete.

    > ⚠️ Če potrebujete, si lahko ogledate [navodila za ustvarjanje in nastavitev CounterFit Python projekta v lekciji 1](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Prepričajte se, da je CounterFit spletna aplikacija zagnana.

1. Ustvarite senzor za merjenje vlažnosti tal:

    1. V polju *Create sensor* v podoknu *Sensors* izberite *Sensor type* in izberite *Soil Moisture*.

    1. Pustite *Units* nastavljene na *NoUnits*.

    1. Prepričajte se, da je *Pin* nastavljen na *0*.

    1. Kliknite gumb **Add**, da ustvarite senzor *Soil Moisture* na pinu 0.

    ![Nastavitve senzorja za merjenje vlažnosti tal](../../../../../translated_images/sl/counterfit-create-soil-moisture-sensor.35266135a5e0ae68b29a684d7db0d2933a8098b2307d197f7c71577b724603aa.png)

    Senzor za merjenje vlažnosti tal bo ustvarjen in se bo pojavil na seznamu senzorjev.

    ![Ustvarjen senzor za merjenje vlažnosti tal](../../../../../translated_images/sl/counterfit-soil-moisture-sensor.81742b2de0e9de60a3b3b9a2ff8ecc686d428eb6d71820f27a693be26e5aceee.png)

## Programiranje aplikacije za senzor vlažnosti tal

Zdaj lahko programirate aplikacijo za senzor vlažnosti tal z uporabo senzorjev CounterFit.

### Naloga - Programiranje aplikacije za senzor vlažnosti tal

Programirajte aplikacijo za senzor vlažnosti tal.

1. Prepričajte se, da je aplikacija `soil-moisture-sensor` odprta v VS Code.

1. Odprite datoteko `app.py`.

1. Dodajte naslednjo kodo na vrh datoteke `app.py`, da povežete aplikacijo s CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Dodajte naslednjo kodo v datoteko `app.py` za uvoz potrebnih knjižnic:

    ```python
    import time
    from counterfit_shims_grove.adc import ADC
    ```

    Ukaz `import time` uvozi modul `time`, ki bo uporabljen kasneje v tej nalogi.

    Ukaz `from counterfit_shims_grove.adc import ADC` uvozi razred `ADC` za interakcijo s simuliranim analognim-digitalnim pretvornikom, ki se lahko poveže s senzorjem CounterFit.

1. Dodajte naslednjo kodo pod to, da ustvarite instanco razreda `ADC`:

    ```python
    adc = ADC()
    ```

1. Dodajte neskončno zanko, ki bere vrednosti iz tega ADC na pinu 0 in jih zapisuje v konzolo. Ta zanka lahko nato spi 10 sekund med branji.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)
    
        time.sleep(10)
    ```

1. V aplikaciji CounterFit spremenite vrednost senzorja za merjenje vlažnosti tal, ki jo bo aplikacija prebrala. To lahko storite na dva načina:

    * Vnesite številko v polje *Value* za senzor vlažnosti tal in nato kliknite gumb **Set**. Številka, ki jo vnesete, bo vrednost, ki jo senzor vrne.

    * Označite polje *Random* in vnesite vrednosti *Min* in *Max*, nato kliknite gumb **Set**. Vsakič, ko senzor prebere vrednost, bo prebral naključno številko med *Min* in *Max*.

1. Zaženite Python aplikacijo. Videli boste meritve vlažnosti tal, zapisane v konzolo. Spremenite *Value* ali nastavitve *Random*, da vidite, kako se vrednost spreminja.

    ```output
    (.venv) ➜ soil-moisture-sensor $ python app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

> 💁 To kodo lahko najdete v mapi [code/virtual-device](../../../../../2-farm/lessons/2-detect-soil-moisture/code/virtual-device).

😀 Vaš program za senzor vlažnosti tal je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.