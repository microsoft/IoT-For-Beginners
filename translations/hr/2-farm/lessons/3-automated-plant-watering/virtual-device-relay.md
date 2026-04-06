# Upravljanje relejem - Virtualni IoT uređaj

U ovom dijelu lekcije, dodat ćete relej svom virtualnom IoT uređaju uz senzor vlažnosti tla i upravljati njime na temelju razine vlažnosti tla.

## Virtualni hardver

Virtualni IoT uređaj koristit će simulirani Grove relej. Ovo omogućuje da laboratorij ostane isti kao korištenje Raspberry Pi-ja s fizičkim Grove relejem.

Na fizičkom IoT uređaju, relej bi bio relej koji je normalno otvoren (što znači da je izlazni krug otvoren ili odspojen kada relej ne prima signal). Takav relej može podnijeti izlazne krugove do 250V i 10A.

### Dodavanje releja u CounterFit

Za korištenje virtualnog releja, potrebno ga je dodati u CounterFit aplikaciju.

#### Zadatak

Dodajte relej u CounterFit aplikaciju.

1. Otvorite projekt `soil-moisture-sensor` iz prošle lekcije u VS Code-u ako već nije otvoren. Dodat ćete na ovaj projekt.

1. Provjerite je li CounterFit web aplikacija pokrenuta.

1. Kreirajte relej:

    1. U okviru *Create actuator* u panelu *Actuators*, otvorite padajući izbornik *Actuator type* i odaberite *Relay*.

    1. Postavite *Pin* na *5*.

    1. Kliknite gumb **Add** za kreiranje releja na pinu 5.

    ![Postavke releja](../../../../../translated_images/hr/counterfit-create-relay.fa7c40fd0f2f6afc.webp)

    Relej će biti kreiran i pojavit će se na popisu aktuatora.

    ![Kreirani relej](../../../../../translated_images/hr/counterfit-relay.bbf74c1dbdc8b9ac.webp)

## Programiranje releja

Aplikacija za senzor vlažnosti tla sada se može programirati za korištenje virtualnog releja.

### Zadatak

Programirajte virtualni uređaj.

1. Otvorite projekt `soil-moisture-sensor` iz prošle lekcije u VS Code-u ako već nije otvoren. Dodat ćete na ovaj projekt.

1. Dodajte sljedeći kod u datoteku `app.py` ispod postojećih uveza:

    ```python
    from counterfit_shims_grove.grove_relay import GroveRelay
    ```

    Ova naredba uvozi `GroveRelay` iz Grove Python shim biblioteka za interakciju s virtualnim Grove relejem.

1. Dodajte sljedeći kod ispod deklaracije klase `ADC` za kreiranje instance `GroveRelay`:

    ```python
    relay = GroveRelay(5)
    ```

    Ovo kreira relej koristeći pin **5**, pin na koji ste povezali relej.

1. Za testiranje rada releja, dodajte sljedeće u petlju `while True:`:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    Kod uključuje relej, čeka 0.5 sekundi, zatim isključuje relej.

1. Pokrenite Python aplikaciju. Relej će se uključivati i isključivati svakih 10 sekundi, s pola sekunde kašnjenja između uključivanja i isključivanja. Vidjet ćete kako se virtualni relej u CounterFit aplikaciji zatvara i otvara dok se relej uključuje i isključuje.

    ![Virtualni relej se uključuje i isključuje](../../../../../images/virtual-relay-turn-on-off.gif)

## Upravljanje relejem na temelju vlažnosti tla

Sada kada relej radi, može se kontrolirati na temelju očitanja vlažnosti tla.

### Zadatak

Kontrolirajte relej.

1. Obrišite 3 linije koda koje ste dodali za testiranje releja. Zamijenite ih sljedećim kodom na istom mjestu:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    Ovaj kod provjerava razinu vlažnosti tla iz senzora vlažnosti tla. Ako je iznad 450, uključuje relej, a isključuje ga ako padne ispod 450.

    > 💁 Zapamtite, kapacitivni senzor vlažnosti tla očitava: što je niža razina vlažnosti tla, to je više vlage u tlu i obrnuto.

1. Pokrenite Python aplikaciju. Vidjet ćete kako se relej uključuje ili isključuje ovisno o razini vlažnosti tla. Promijenite *Value* ili *Random* postavke za senzor vlažnosti tla kako biste vidjeli promjenu vrijednosti.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Ovaj kod možete pronaći u mapi [code-relay/virtual-device](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/virtual-device).

😀 Vaš program za virtualni senzor vlažnosti tla koji kontrolira relej bio je uspješan!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za nesporazume ili pogrešna tumačenja koja mogu proizaći iz korištenja ovog prijevoda.