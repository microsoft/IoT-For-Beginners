# Otkrivanje blizine - Raspberry Pi

U ovom dijelu lekcije dodat ćete senzor blizine na svoj Raspberry Pi i očitavati udaljenost s njega.

## Hardver

Za Raspberry Pi potreban je senzor blizine.

Senzor koji ćete koristiti je [Grove Time of Flight senzor udaljenosti](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Ovaj senzor koristi modul za lasersko mjerenje udaljenosti. Ima raspon od 10 mm do 2000 mm (1 cm - 2 m) i prilično precizno prijavljuje vrijednosti unutar tog raspona, dok udaljenosti iznad 1000 mm prijavljuje kao 8109 mm.

Laserski daljinomjer nalazi se na stražnjoj strani senzora, na suprotnoj strani od Grove utičnice.

Ovo je I²C senzor.

### Povezivanje senzora Time of Flight

Grove Time of Flight senzor može se povezati s Raspberry Pi-jem.

#### Zadatak - povezivanje senzora Time of Flight

Povežite senzor Time of Flight.

![Grove Time of Flight senzor](../../../../../translated_images/hr/grove-time-of-flight-sensor.d82ff2165bfded9f.webp)

1. Umetnite jedan kraj Grove kabela u utičnicu na senzoru Time of Flight. Kabel će se umetnuti samo na jedan način.

1. Kada je Raspberry Pi isključen, spojite drugi kraj Grove kabela na jednu od I²C utičnica označenih **I²C** na Grove Base hatu pričvršćenom na Pi. Ove utičnice nalaze se u donjem redu, na suprotnom kraju od GPIO pinova i pored utora za kabel kamere.

![Grove Time of Flight senzor povezan s I²C utičnicom](../../../../../translated_images/hr/pi-time-of-flight-sensor.58c8dc04eb3bfb57.webp)

## Programiranje senzora Time of Flight

Sada se Raspberry Pi može programirati za korištenje povezanog senzora Time of Flight.

### Zadatak - programiranje senzora Time of Flight

Programirajte uređaj.

1. Uključite Pi i pričekajte da se pokrene.

1. Otvorite kod `fruit-quality-detector` u VS Code-u, bilo izravno na Pi-ju ili se povežite putem Remote SSH ekstenzije.

1. Instalirajte rpi-vl53l0x Pip paket, Python paket koji omogućuje interakciju s VL53L0X senzorom udaljenosti. Instalirajte ga pomoću ove pip naredbe:

    ```sh
    pip install rpi-vl53l0x
    ```

1. Kreirajte novu datoteku u ovom projektu pod nazivom `distance-sensor.py`.

    > 💁 Jednostavan način simulacije više IoT uređaja je kreiranje svakog u zasebnoj Python datoteci, a zatim njihovo istovremeno pokretanje.

1. Dodajte sljedeći kod u ovu datoteku:

    ```python
    import time
    
    from grove.i2c import Bus
    from rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Ovaj kod uvozi Grove I²C bus biblioteku i biblioteku senzora za osnovni hardver ugrađen u Grove Time of Flight senzor.

1. Ispod toga dodajte sljedeći kod za pristup senzoru:

    ```python
    distance_sensor = VL53L0X(bus = Bus().bus)
    distance_sensor.begin()    
    ```

    Ovaj kod deklarira senzor udaljenosti koristeći Grove I²C bus, a zatim pokreće senzor.

1. Na kraju, dodajte beskonačnu petlju za očitavanje udaljenosti:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Ovaj kod čeka da vrijednost bude spremna za očitavanje sa senzora, a zatim je ispisuje na konzolu.

1. Pokrenite ovaj kod.

    > 💁 Ne zaboravite da se ova datoteka zove `distance-sensor.py`! Obavezno je pokrenite putem Pythona, a ne `app.py`.

1. Vidjet ćete mjerenja udaljenosti na konzoli. Postavite objekte blizu senzora i vidjet ćete očitanje udaljenosti:

    ```output
    pi@raspberrypi:~/fruit-quality-detector $ python3 distance_sensor.py 
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Daljinomjer se nalazi na stražnjoj strani senzora, pa pazite da koristite ispravnu stranu prilikom mjerenja udaljenosti.

    ![Daljinomjer na stražnjoj strani senzora Time of Flight usmjeren prema banani](../../../../../translated_images/hr/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 Ovaj kod možete pronaći u mapi [code-proximity/pi](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/pi).

😀 Vaš program za senzor blizine uspješno je završen!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije koje proizlaze iz korištenja ovog prijevoda.