<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ea733bd0cdf2479e082373f765a08678",
  "translation_date": "2025-08-28T14:14:28+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-sensor.md",
  "language_code": "hr"
}
-->
# Izradite noćno svjetlo - Raspberry Pi

U ovom dijelu lekcije dodati ćete senzor svjetla na svoj Raspberry Pi.

## Hardver

Senzor za ovu lekciju je **senzor svjetla** koji koristi [fotodiodu](https://wikipedia.org/wiki/Photodiode) za pretvaranje svjetla u električni signal. Ovo je analogni senzor koji šalje cjelobrojnu vrijednost od 0 do 1.000, označavajući relativnu količinu svjetla koja ne odgovara nijednoj standardnoj jedinici mjerenja poput [luks](https://wikipedia.org/wiki/Lux).

Senzor svjetla je vanjski Grove senzor i mora biti povezan na Grove Base hat na Raspberry Pi-ju.

### Povežite senzor svjetla

Grove senzor svjetla koji se koristi za detekciju razine svjetla mora biti povezan na Raspberry Pi.

#### Zadatak - povežite senzor svjetla

Povežite senzor svjetla.

![Grove senzor svjetla](../../../../../translated_images/hr/grove-light-sensor.b8127b7c434e632d6bcdb57587a14e9ef69a268a22df95d08628f62b8fa5505c.png)

1. Umetnite jedan kraj Grove kabela u utičnicu na modulu senzora svjetla. Kabel će ući samo na jedan način.

1. Dok je Raspberry Pi isključen, povežite drugi kraj Grove kabela s analognom utičnicom označenom **A0** na Grove Base hatu pričvršćenom na Pi. Ova utičnica je druga s desna, u redu utičnica pored GPIO pinova.

![Grove senzor svjetla povezan na utičnicu A0](../../../../../translated_images/hr/pi-light-sensor.66cc1e31fa48cd7d5f23400d4b2119aa41508275cb7c778053a7923b4e972d7e.png)

## Programirajte senzor svjetla

Uređaj sada može biti programiran pomoću Grove senzora svjetla.

### Zadatak - programirajte senzor svjetla

Programirajte uređaj.

1. Uključite Pi i pričekajte da se pokrene.

1. Otvorite projekt noćnog svjetla u VS Code koji ste kreirali u prethodnom dijelu ovog zadatka, bilo da radi direktno na Pi-ju ili je povezan pomoću Remote SSH ekstenzije.

1. Otvorite datoteku `app.py` i uklonite sav kod iz nje.

1. Dodajte sljedeći kod u datoteku `app.py` za uvoz potrebnih biblioteka:

    ```python
    import time
    from grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    Izjava `import time` uvozi modul `time` koji će se koristiti kasnije u ovom zadatku.

    Izjava `from grove.grove_light_sensor_v1_2 import GroveLightSensor` uvozi `GroveLightSensor` iz Grove Python biblioteka. Ova biblioteka sadrži kod za interakciju s Grove senzorom svjetla i instalirana je globalno tijekom postavljanja Pi-ja.

1. Dodajte sljedeći kod nakon prethodnog koda za kreiranje instance klase koja upravlja senzorom svjetla:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    Linija `light_sensor = GroveLightSensor(0)` kreira instancu klase `GroveLightSensor` povezujući se na pin **A0** - analogni Grove pin na koji je senzor svjetla povezan.

1. Dodajte beskonačnu petlju nakon prethodnog koda za očitavanje vrijednosti senzora svjetla i ispisivanje na konzolu:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Ovo će očitati trenutnu razinu svjetla na skali od 0-1.023 koristeći svojstvo `light` klase `GroveLightSensor`. Ovo svojstvo očitava analognu vrijednost s pina. Ta vrijednost se zatim ispisuje na konzolu.

1. Dodajte kratku pauzu od jedne sekunde na kraju `loop` jer razine svjetla ne trebaju biti provjeravane kontinuirano. Pauza smanjuje potrošnju energije uređaja.

    ```python
    time.sleep(1)
    ```

1. Iz terminala u VS Code-u pokrenite sljedeće za pokretanje vaše Python aplikacije:

    ```sh
    python3 app.py
    ```

    Vrijednosti svjetla će se ispisivati na konzolu. Pokrijte i otkrijte senzor svjetla, i vrijednosti će se mijenjati:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

> 💁 Ovaj kod možete pronaći u mapi [code-sensor/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/pi).

😀 Dodavanje senzora vašem programu za noćno svjetlo je bilo uspješno!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati mjerodavnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane stručnjaka. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije proizašle iz korištenja ovog prijevoda.