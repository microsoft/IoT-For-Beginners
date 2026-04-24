# Mjerenje vlažnosti tla - Raspberry Pi

U ovom dijelu lekcije, dodat ćete kapacitivni senzor vlažnosti tla na svoj Raspberry Pi i očitati vrijednosti s njega.

## Hardver

Za Raspberry Pi potreban je kapacitivni senzor vlažnosti tla.

Senzor koji ćete koristiti je [Kapacitivni senzor vlažnosti tla](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), koji mjeri vlažnost tla detektiranjem kapaciteta tla, svojstva koje se mijenja s promjenom vlažnosti tla. Kako se vlažnost tla povećava, napon se smanjuje.

Ovo je analogni senzor, pa koristi analogni pin i 10-bitni ADC na Grove Base Hat-u na Raspberry Pi-ju za pretvaranje napona u digitalni signal od 1-1.023. Taj signal se zatim šalje preko I2C putem GPIO pinova na Pi-ju.

### Spojite senzor vlažnosti tla

Grove senzor vlažnosti tla može se spojiti na Raspberry Pi.

#### Zadatak - spojite senzor vlažnosti tla

Spojite senzor vlažnosti tla.

![Grove senzor vlažnosti tla](../../../../../translated_images/hr/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78b.webp)

1. Umetnite jedan kraj Grove kabela u utičnicu na senzoru vlažnosti tla. Kabel će ući samo na jedan način.

1. Dok je Raspberry Pi isključen, spojite drugi kraj Grove kabela na analogni priključak označen **A0** na Grove Base Hat-u pričvršćenom na Pi. Ovaj priključak je drugi s desne strane, u redu priključaka pored GPIO pinova.

![Grove senzor vlažnosti tla spojen na A0 priključak](../../../../../translated_images/hr/pi-soil-moisture-sensor.fdd7eb2393792cf6.webp)

1. Umetnite senzor vlažnosti tla u tlo. Na senzoru postoji oznaka 'najviša pozicija' - bijela linija preko senzora. Umetnite senzor do te linije, ali ne preko nje.

![Grove senzor vlažnosti tla u tlu](../../../../../translated_images/hr/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

## Programiranje senzora vlažnosti tla

Sada možete programirati Raspberry Pi za korištenje spojenog senzora vlažnosti tla.

### Zadatak - programirajte senzor vlažnosti tla

Programirajte uređaj.

1. Uključite Pi i pričekajte da se pokrene.

1. Pokrenite VS Code, bilo izravno na Pi-ju ili se povežite putem Remote SSH ekstenzije.

    > ⚠️ Možete se pozvati na [upute za postavljanje i pokretanje VS Code-a u nightlight - lekcija 1 ako je potrebno](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Iz terminala, stvorite novu mapu u početnom direktoriju korisnika `pi` pod nazivom `soil-moisture-sensor`. U toj mapi stvorite datoteku pod nazivom `app.py`.

1. Otvorite ovu mapu u VS Code-u.

1. Dodajte sljedeći kod u datoteku `app.py` za uvoz potrebnih biblioteka:

    ```python
    import time
    from grove.adc import ADC
    ```

    Izjava `import time` uvozi modul `time` koji će se kasnije koristiti u ovom zadatku.

    Izjava `from grove.adc import ADC` uvozi `ADC` iz Grove Python biblioteka. Ova biblioteka sadrži kod za interakciju s analognim-digitalnim pretvaračem na Pi Base Hat-u i očitavanje napona s analognih senzora.

1. Dodajte sljedeći kod ispod kako biste stvorili instancu klase `ADC`:

    ```python
    adc = ADC()
    ```

1. Dodajte beskonačnu petlju koja očitava vrijednosti s ADC-a na pinu A0 i ispisuje rezultat na konzolu. Ova petlja može zatim pauzirati 10 sekundi između očitavanja.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)

        time.sleep(10)
    ```

1. Pokrenite Python aplikaciju. Vidjet ćete očitanja vlažnosti tla ispisana na konzoli. Dodajte malo vode u tlo ili izvadite senzor iz tla i promatrajte kako se vrijednost mijenja.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

    U primjeru izlaza iznad, možete vidjeti kako napon pada kada se doda voda.

> 💁 Ovaj kod možete pronaći u mapi [code/pi](../../../../../2-farm/lessons/2-detect-soil-moisture/code/pi).

😀 Vaš program za senzor vlažnosti tla uspješno je završen!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden korištenjem AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati mjerodavnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane stručnjaka. Ne preuzimamo odgovornost za bilo kakva nesporazuma ili pogrešna tumačenja koja mogu proizaći iz korištenja ovog prijevoda.