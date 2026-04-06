# Detekcia blízkosti - Virtuálny IoT hardvér

V tejto časti lekcie pridáte k svojmu virtuálnemu IoT zariadeniu senzor blízkosti a budete z neho čítať vzdialenosť.

## Hardvér

Virtuálne IoT zariadenie bude používať simulovaný senzor vzdialenosti.

Na fyzickom IoT zariadení by ste použili senzor s laserovým modulom na meranie vzdialenosti.

### Pridanie senzora vzdialenosti do CounterFit

Na použitie virtuálneho senzora vzdialenosti je potrebné pridať ho do aplikácie CounterFit.

#### Úloha - pridanie senzora vzdialenosti do CounterFit

Pridajte senzor vzdialenosti do aplikácie CounterFit.

1. Otvorte kód `fruit-quality-detector` vo VS Code a uistite sa, že virtuálne prostredie je aktivované.

1. Nainštalujte ďalší balík Pip na inštaláciu CounterFit shim, ktorý dokáže komunikovať so senzormi vzdialenosti simulovaním balíka [rpi-vl53l0x Pip](https://pypi.org/project/rpi-vl53l0x/), Python balíka, ktorý interaguje s [VL53L0X senzorom vzdialenosti typu time-of-flight](https://wiki.seeedstudio.com/Grove-Time_of_Flight_Distance_Sensor-VL53L0X/). Uistite sa, že inštalujete tento balík z terminálu s aktivovaným virtuálnym prostredím.

    ```sh
    pip install counterfit-shims-rpi-vl53l0x
    ```

1. Uistite sa, že webová aplikácia CounterFit je spustená.

1. Vytvorte senzor vzdialenosti:

    1. V poli *Create sensor* v paneli *Sensors* rozbaľte pole *Sensor type* a vyberte *Distance*.

    1. Nechajte *Units* nastavené na `Millimeter`.

    1. Tento senzor je senzor typu I²C, takže nastavte adresu na `0x29`. Ak by ste použili fyzický senzor VL53L0X, táto adresa by bola pevne nastavená.

    1. Kliknite na tlačidlo **Add**, aby ste vytvorili senzor vzdialenosti.

    ![Nastavenia senzora vzdialenosti](../../../../../translated_images/sk/counterfit-create-distance-sensor.967c9fb98f27888d.webp)

    Senzor vzdialenosti bude vytvorený a zobrazí sa v zozname senzorov.

    ![Vytvorený senzor vzdialenosti](../../../../../translated_images/sk/counterfit-distance-sensor.079eefeeea0b68af.webp)

## Programovanie senzora vzdialenosti

Virtuálne IoT zariadenie teraz môže byť naprogramované na použitie simulovaného senzora vzdialenosti.

### Úloha - programovanie senzora typu time-of-flight

1. V projekte `fruit-quality-detector` vytvorte nový súbor s názvom `distance-sensor.py`.

    > 💁 Jednoduchý spôsob simulácie viacerých IoT zariadení je vytvoriť každé v samostatnom Python súbore a potom ich spustiť súčasne.

1. Spustite pripojenie k CounterFit pomocou nasledujúceho kódu:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Pod tento kód pridajte nasledujúci:

    ```python
    import time
    
    from counterfit_shims_rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Tento kód importuje knižnicu shim pre senzor VL53L0X typu time-of-flight.

1. Pod tento kód pridajte nasledujúci kód na prístup k senzoru:

    ```python
    distance_sensor = VL53L0X()
    distance_sensor.begin()
    ```

    Tento kód deklaruje senzor vzdialenosti a potom ho spustí.

1. Nakoniec pridajte nekonečnú slučku na čítanie vzdialeností:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Tento kód čaká na hodnotu pripravenú na čítanie zo senzora a potom ju vypíše do konzoly.

1. Spustite tento kód.

    > 💁 Nezabudnite, že tento súbor sa volá `distance-sensor.py`! Uistite sa, že ho spúšťate cez Python, nie `app.py`.

1. V konzole sa zobrazia merania vzdialenosti. Zmeňte hodnotu v CounterFit, aby ste videli, ako sa táto hodnota mení, alebo použite náhodné hodnoty.

    ```output
    (.venv) ➜  fruit-quality-detector python distance-sensor.py 
    Distance = 37 mm
    Distance = 42 mm
    Distance = 29 mm
    ```

> 💁 Tento kód nájdete v priečinku [code-proximity/virtual-iot-device](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/virtual-iot-device).

😀 Program senzora blízkosti bol úspešný!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby na automatický preklad [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, upozorňujeme, že automatické preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nezodpovedáme za žiadne nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.