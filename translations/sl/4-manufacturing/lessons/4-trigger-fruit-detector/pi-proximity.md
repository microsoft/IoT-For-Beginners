<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6145a1d791731c8a9d0afd0a1bae5108",
  "translation_date": "2025-08-28T12:12:39+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/pi-proximity.md",
  "language_code": "sl"
}
-->
# Zaznavanje bližine - Raspberry Pi

V tem delu lekcije boste na svoj Raspberry Pi dodali senzor bližine in od njega prebrali razdaljo.

## Strojna oprema

Raspberry Pi potrebuje senzor bližine.

Senzor, ki ga boste uporabili, je [Grove Time of Flight senzor za merjenje razdalje](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Ta senzor uporablja laserski modul za merjenje razdalje. Ima razpon od 10 mm do 2000 mm (1 cm - 2 m) in bo v tem razponu poročal precej natančne vrednosti, pri čemer bodo razdalje nad 1000 mm poročane kot 8109 mm.

Laserski merilnik razdalje se nahaja na zadnji strani senzorja, nasprotni strani od Grove priključka.

To je I²C senzor.

### Povežite senzor Time of Flight

Grove senzor Time of Flight lahko povežete z Raspberry Pi.

#### Naloga - povežite senzor Time of Flight

Povežite senzor Time of Flight.

![Grove senzor Time of Flight](../../../../../translated_images/sl/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.png)

1. Vstavite en konec Grove kabla v priključek na senzorju Time of Flight. Kabel bo šel noter le v eni smeri.

1. Ko je Raspberry Pi izklopljen, povežite drugi konec Grove kabla z enim od I²C priključkov, označenih z **I²C**, na Grove Base hat, ki je pritrjen na Pi. Ti priključki so v spodnji vrsti, na nasprotni strani od GPIO pinov in poleg reže za kabel kamere.

![Grove senzor Time of Flight povezan z I²C priključkom](../../../../../translated_images/sl/pi-time-of-flight-sensor.58c8dc04eb3bfb57.webp)

## Programirajte senzor Time of Flight

Zdaj lahko Raspberry Pi programirate za uporabo priloženega senzorja Time of Flight.

### Naloga - programirajte senzor Time of Flight

Programirajte napravo.

1. Vklopite Pi in počakajte, da se zažene.

1. Odprite kodo `fruit-quality-detector` v VS Code, bodisi neposredno na Pi ali pa se povežite prek razširitve Remote SSH.

1. Namestite Pip paket rpi-vl53l0x, Python paket, ki omogoča interakcijo z VL53L0X senzorjem za merjenje razdalje. Namestite ga z naslednjim pip ukazom:

    ```sh
    pip install rpi-vl53l0x
    ```

1. V tem projektu ustvarite novo datoteko z imenom `distance-sensor.py`.

    > 💁 Enostaven način za simulacijo več IoT naprav je, da vsako napravo programirate v ločeni Python datoteki in jih nato zaženete hkrati.

1. V to datoteko dodajte naslednjo kodo:

    ```python
    import time
    
    from grove.i2c import Bus
    from rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Ta koda uvozi knjižnico Grove I²C bus in knjižnico za osnovno strojno opremo senzorja, vgrajeno v Grove senzor Time of Flight.

1. Pod to kodo dodajte naslednjo kodo za dostop do senzorja:

    ```python
    distance_sensor = VL53L0X(bus = Bus().bus)
    distance_sensor.begin()    
    ```

    Ta koda deklarira senzor razdalje z uporabo Grove I²C busa in nato zažene senzor.

1. Na koncu dodajte neskončno zanko za branje razdalj:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Ta koda počaka, da je vrednost pripravljena za branje s senzorja, nato pa jo izpiše v konzolo.

1. Zaženite to kodo.

    > 💁 Ne pozabite, da se ta datoteka imenuje `distance-sensor.py`! Poskrbite, da jo zaženete prek Pythona, ne `app.py`.

1. V konzoli boste videli meritve razdalje. Postavite predmete blizu senzorja in videli boste meritve razdalje:

    ```output
    pi@raspberrypi:~/fruit-quality-detector $ python3 distance_sensor.py 
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Merilnik razdalje je na zadnji strani senzorja, zato poskrbite, da boste uporabili pravo stran pri merjenju razdalje.

    ![Merilnik razdalje na zadnji strani senzorja Time of Flight, usmerjen proti banani](../../../../../translated_images/sl/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 To kodo lahko najdete v mapi [code-proximity/pi](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/pi).

😀 Vaš program za senzor bližine je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna napačna razumevanja ali napačne interpretacije, ki bi nastale zaradi uporabe tega prevoda.