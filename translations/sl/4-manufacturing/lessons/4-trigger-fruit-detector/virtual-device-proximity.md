<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e9f05bdc50a40fd924b1d66934471bf",
  "translation_date": "2025-08-28T12:15:22+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/virtual-device-proximity.md",
  "language_code": "sl"
}
-->
# Zaznavanje bližine - Virtualna IoT strojna oprema

V tem delu lekcije boste svoji virtualni IoT napravi dodali senzor bližine in prebrali razdaljo z njega.

## Strojna oprema

Virtualna IoT naprava bo uporabljala simuliran senzor razdalje.

Pri fizični IoT napravi bi uporabili senzor z laserskim merilnim modulom za zaznavanje razdalje.

### Dodajanje senzorja razdalje v CounterFit

Za uporabo virtualnega senzorja razdalje ga morate dodati v aplikacijo CounterFit.

#### Naloga - dodajte senzor razdalje v CounterFit

Dodajte senzor razdalje v aplikacijo CounterFit.

1. Odprite kodo `fruit-quality-detector` v VS Code in se prepričajte, da je virtualno okolje aktivirano.

1. Namestite dodatni Pip paket za namestitev CounterFit shima, ki lahko komunicira s senzorji razdalje s simulacijo [rpi-vl53l0x Pip paketa](https://pypi.org/project/rpi-vl53l0x/), Python paketa, ki deluje z [VL53L0X senzorjem razdalje na osnovi časa leta](https://wiki.seeedstudio.com/Grove-Time_of_Flight_Distance_Sensor-VL53L0X/). Prepričajte se, da to nameščate iz terminala z aktiviranim virtualnim okoljem.

    ```sh
    pip install counterfit-shims-rpi-vl53l0x
    ```

1. Prepričajte se, da je spletna aplikacija CounterFit zagnana.

1. Ustvarite senzor razdalje:

    1. V polju *Create sensor* v podoknu *Sensors* odprite spustni meni *Sensor type* in izberite *Distance*.

    1. Pustite *Units* kot `Millimeter`.

    1. Ta senzor je I²C senzor, zato nastavite naslov na `0x29`. Če bi uporabili fizični VL53L0X senzor, bi bil ta naslov trdo kodiran.

    1. Izberite gumb **Add**, da ustvarite senzor razdalje.

    ![Nastavitve senzorja razdalje](../../../../../translated_images/sl/counterfit-create-distance-sensor.967c9fb98f27888d95920c9784d004c972490eb71f70397fe13bd70a79a879a3.png)

    Senzor razdalje bo ustvarjen in se bo pojavil na seznamu senzorjev.

    ![Ustvarjen senzor razdalje](../../../../../translated_images/sl/counterfit-distance-sensor.079eefeeea0b68afc36431ce8fcbe2f09a7e4916ed1cd5cb30e696db53bc18fa.png)

## Programiranje senzorja razdalje

Virtualna IoT naprava je zdaj pripravljena za programiranje, da uporablja simuliran senzor razdalje.

### Naloga - programirajte senzor časa leta

1. Ustvarite novo datoteko v projektu `fruit-quality-detector` z imenom `distance-sensor.py`.

    > 💁 Enostaven način za simulacijo več IoT naprav je, da vsako ustvarite v ločeni Python datoteki in jih nato zaženete hkrati.

1. Začnite povezavo s CounterFit z naslednjo kodo:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Pod to kodo dodajte naslednje:

    ```python
    import time
    
    from counterfit_shims_rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    To uvozi knjižnico shima za senzor VL53L0X časa leta.

1. Pod to kodo dodajte naslednje za dostop do senzorja:

    ```python
    distance_sensor = VL53L0X()
    distance_sensor.begin()
    ```

    Ta koda deklarira senzor razdalje in nato zažene senzor.

1. Na koncu dodajte neskončno zanko za branje razdalj:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Ta koda počaka, da je vrednost pripravljena za branje s senzorja, nato pa jo izpiše v konzolo.

1. Zaženite to kodo.

    > 💁 Ne pozabite, da se ta datoteka imenuje `distance-sensor.py`! Prepričajte se, da jo zaženete s Pythonom, ne z `app.py`.

1. V konzoli boste videli meritve razdalje. Spremenite vrednost v CounterFit, da vidite, kako se ta vrednost spremeni, ali uporabite naključne vrednosti.

    ```output
    (.venv) ➜  fruit-quality-detector python distance-sensor.py 
    Distance = 37 mm
    Distance = 42 mm
    Distance = 29 mm
    ```

> 💁 To kodo lahko najdete v mapi [code-proximity/virtual-iot-device](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/virtual-iot-device).

😀 Vaš program za senzor bližine je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za strojno prevajanje [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas opozarjamo, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo strokovno človeško prevajanje. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki izhajajo iz uporabe tega prevoda.