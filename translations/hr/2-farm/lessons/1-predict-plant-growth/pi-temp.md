<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7678f7c67b97ee52d5727496dcd7d346",
  "translation_date": "2025-08-28T15:06:44+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/pi-temp.md",
  "language_code": "hr"
}
-->
# Mjerenje temperature - Raspberry Pi

U ovom dijelu lekcije, dodat ćete senzor temperature na svoj Raspberry Pi.

## Hardver

Senzor koji ćete koristiti je [DHT11 senzor za vlagu i temperaturu](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), koji kombinira dva senzora u jednom paketu. Ovo je prilično popularan senzor, a postoji i niz komercijalno dostupnih senzora koji kombiniraju mjerenje temperature, vlage, a ponekad i atmosferskog tlaka. Komponenta za mjerenje temperature je termistor s negativnim temperaturnim koeficijentom (NTC), što znači da se otpor smanjuje kako temperatura raste.

Ovo je digitalni senzor, što znači da ima ugrađeni ADC (analogno-digitalni pretvarač) koji stvara digitalni signal s podacima o temperaturi i vlazi koje mikrokontroler može očitati.

### Povezivanje senzora temperature

Grove senzor temperature može se povezati s Raspberry Pi-jem.

#### Zadatak

Povežite senzor temperature.

![Grove senzor temperature](../../../../../translated_images/hr/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.png)

1. Umetnite jedan kraj Grove kabela u utičnicu na senzoru za vlagu i temperaturu. Kabel će ući samo na jedan način.

1. Dok je Raspberry Pi isključen, spojite drugi kraj Grove kabela na digitalnu utičnicu označenu **D5** na Grove Base hat-u koji je povezan s Pi-jem. Ova utičnica je druga s lijeva, u redu utičnica pored GPIO pinova.

![Grove senzor temperature povezan na utičnicu A0](../../../../../translated_images/hr/pi-temperature-sensor.3ff82fff672c8e565ef25a39d26d111de006b825a7e0867227ef4e7fbff8553c.png)

## Programiranje senzora temperature

Sada možete programirati uređaj za korištenje povezanog senzora temperature.

### Zadatak

Programirajte uređaj.

1. Uključite Raspberry Pi i pričekajte da se pokrene.

1. Pokrenite VS Code, bilo izravno na Pi-ju ili se povežite putem Remote SSH ekstenzije.

    > ⚠️ Možete se pozvati na [upute za postavljanje i pokretanje VS Code-a u lekciji 1 ako je potrebno](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Iz terminala, stvorite novu mapu u početnom direktoriju korisnika `pi` pod nazivom `temperature-sensor`. U toj mapi stvorite datoteku pod nazivom `app.py`:

    ```sh
    mkdir temperature-sensor
    cd temperature-sensor
    touch app.py
    ```

1. Otvorite ovu mapu u VS Code-u.

1. Za korištenje senzora za vlagu i temperaturu potrebno je instalirati dodatni Pip paket. Iz terminala u VS Code-u pokrenite sljedeću naredbu kako biste instalirali ovaj Pip paket na Pi:

    ```sh
    pip3 install seeed-python-dht
    ```

1. Dodajte sljedeći kod u datoteku `app.py` kako biste uvezli potrebne biblioteke:

    ```python
    import time
    from seeed_dht import DHT
    ```

    Izjava `from seeed_dht import DHT` uvozi klasu `DHT` za interakciju s Grove senzorom temperature iz modula `seeed_dht`.

1. Dodajte sljedeći kod nakon prethodnog kako biste stvorili instancu klase koja upravlja senzorom temperature:

    ```python
    sensor = DHT("11", 5)
    ```

    Ovo deklarira instancu klase `DHT` koja upravlja **D**igitalnim senzorom za **V**lagu i **T**emperaturu. Prvi parametar govori kodu da se koristi senzor *DHT11* - biblioteka koju koristite podržava i druge varijante ovog senzora. Drugi parametar govori kodu da je senzor povezan na digitalni port `D5` na Grove Base hat-u.

    > ✅ Zapamtite, sve utičnice imaju jedinstvene brojeve pinova. Pinovi 0, 2, 4 i 6 su analogni pinovi, dok su pinovi 5, 16, 18, 22, 24 i 26 digitalni pinovi.

1. Dodajte beskonačnu petlju nakon prethodnog koda kako biste očitavali vrijednosti senzora temperature i ispisivali ih u konzolu:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    Poziv `sensor.read()` vraća tuple s podacima o vlazi i temperaturi. Potrebna vam je samo vrijednost temperature, pa se vlaga ignorira. Vrijednost temperature zatim se ispisuje u konzolu.

1. Dodajte kratku pauzu od deset sekundi na kraju `loop`-a jer nije potrebno kontinuirano provjeravati razine temperature. Pauza smanjuje potrošnju energije uređaja.

    ```python
    time.sleep(10)
    ```

1. Iz terminala u VS Code-u pokrenite sljedeće kako biste pokrenuli svoj Python program:

    ```sh
    python3 app.py
    ```

    Trebali biste vidjeti vrijednosti temperature koje se ispisuju u konzolu. Koristite nešto za zagrijavanje senzora, poput pritiska palca na njega ili ventilatora, kako biste vidjeli promjene vrijednosti:

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py 
    Temperature 26°C
    Temperature 26°C
    Temperature 28°C
    Temperature 30°C
    Temperature 32°C
    ```

> 💁 Ovaj kod možete pronaći u mapi [code-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/pi).

😀 Vaš program za senzor temperature uspješno je završen!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za bilo kakva nesporazuma ili pogrešna tumačenja koja proizlaze iz korištenja ovog prijevoda.