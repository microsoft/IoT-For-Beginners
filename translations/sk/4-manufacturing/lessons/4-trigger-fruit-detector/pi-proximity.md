<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6145a1d791731c8a9d0afd0a1bae5108",
  "translation_date": "2025-08-28T08:25:41+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/pi-proximity.md",
  "language_code": "sk"
}
-->
# Detekcia blízkosti - Raspberry Pi

V tejto časti lekcie pridáte k svojmu Raspberry Pi senzor blízkosti a budete z neho čítať vzdialenosť.

## Hardvér

Raspberry Pi potrebuje senzor blízkosti.

Senzor, ktorý budete používať, je [Grove Time of Flight distance sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Tento senzor používa laserový modul na meranie vzdialenosti. Má rozsah od 10 mm do 2000 mm (1 cm - 2 m) a hodnoty v tomto rozsahu hlási pomerne presne, pričom vzdialenosti nad 1000 mm sú hlásené ako 8109 mm.

Laserový diaľkomer sa nachádza na zadnej strane senzora, na opačnej strane ako konektor Grove.

Toto je I²C senzor.

### Pripojenie senzora Time of Flight

Senzor Grove Time of Flight je možné pripojiť k Raspberry Pi.

#### Úloha - pripojenie senzora Time of Flight

Pripojte senzor Time of Flight.

![Senzor Grove Time of Flight](../../../../../translated_images/sk/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.png)

1. Zasuňte jeden koniec Grove kábla do konektora na senzore Time of Flight. Kábel sa dá zasunúť iba jedným spôsobom.

1. Pri vypnutom Raspberry Pi pripojte druhý koniec Grove kábla do jedného z I²C konektorov označených **I²C** na Grove Base hat pripojenom k Pi. Tieto konektory sa nachádzajú v dolnom rade, na opačnom konci ako GPIO piny a vedľa slotu pre kamerový kábel.

![Senzor Grove Time of Flight pripojený k I²C konektoru](../../../../../translated_images/sk/pi-time-of-flight-sensor.58c8dc04eb3bfb57.webp)

## Naprogramovanie senzora Time of Flight

Raspberry Pi teraz môže byť naprogramované na používanie pripojeného senzora Time of Flight.

### Úloha - naprogramovanie senzora Time of Flight

Naprogramujte zariadenie.

1. Zapnite Pi a počkajte, kým sa nespustí.

1. Otvorte kód `fruit-quality-detector` vo VS Code, buď priamo na Pi, alebo sa pripojte cez rozšírenie Remote SSH.

1. Nainštalujte balík rpi-vl53l0x cez Pip, čo je Python balík na interakciu so senzorom vzdialenosti VL53L0X. Nainštalujte ho pomocou tohto príkazu pip:

    ```sh
    pip install rpi-vl53l0x
    ```

1. Vytvorte nový súbor v tomto projekte s názvom `distance-sensor.py`.

    > 💁 Jednoduchý spôsob, ako simulovať viacero IoT zariadení, je vytvoriť pre každé zariadenie samostatný Python súbor a spustiť ich súčasne.

1. Pridajte do tohto súboru nasledujúci kód:

    ```python
    import time
    
    from grove.i2c import Bus
    from rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Tento kód importuje knižnicu Grove I²C bus a knižnicu senzora pre základný hardvér zabudovaný do senzora Grove Time of Flight.

1. Pod tento kód pridajte nasledujúci kód na prístup k senzoru:

    ```python
    distance_sensor = VL53L0X(bus = Bus().bus)
    distance_sensor.begin()    
    ```

    Tento kód deklaruje senzor vzdialenosti pomocou Grove I²C bus a potom senzor spustí.

1. Nakoniec pridajte nekonečnú slučku na čítanie vzdialeností:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Tento kód čaká, kým bude hodnota pripravená na čítanie zo senzora, a potom ju vypíše do konzoly.

1. Spustite tento kód.

    > 💁 Nezabudnite, že tento súbor sa volá `distance-sensor.py`! Uistite sa, že ho spúšťate cez Python, nie `app.py`.

1. V konzole sa zobrazia merania vzdialenosti. Umiestnite objekty blízko senzora a uvidíte meranie vzdialenosti:

    ```output
    pi@raspberrypi:~/fruit-quality-detector $ python3 distance_sensor.py 
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Diaľkomer sa nachádza na zadnej strane senzora, takže pri meraní vzdialenosti používajte správnu stranu.

    ![Diaľkomer na zadnej strane senzora Time of Flight smerujúci na banán](../../../../../translated_images/sk/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 Tento kód nájdete v priečinku [code-proximity/pi](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/pi).

😀 Program senzora blízkosti bol úspešný!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby na automatický preklad [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, upozorňujeme, že automatické preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nezodpovedáme za žiadne nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.