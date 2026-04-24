# Aptikti artumą - Virtuali IoT įranga

Šioje pamokos dalyje pridėsite artumo jutiklį prie savo virtualaus IoT įrenginio ir nuskaitysite atstumą iš jo.

## Įranga

Virtualus IoT įrenginys naudos simuliuotą atstumo jutiklį.

Fiziniame IoT įrenginyje naudotumėte jutiklį su lazeriniu atstumo matavimo moduliu, kad aptiktumėte atstumą.

### Pridėti atstumo jutiklį į CounterFit

Norėdami naudoti virtualų atstumo jutiklį, turite jį pridėti prie CounterFit programos.

#### Užduotis - pridėti atstumo jutiklį į CounterFit

Pridėkite atstumo jutiklį į CounterFit programą.

1. Atidarykite `fruit-quality-detector` kodą VS Code ir įsitikinkite, kad virtuali aplinka yra aktyvuota.

1. Įdiekite papildomą Pip paketą, kad įdiegtumėte CounterFit shim, kuris gali bendrauti su atstumo jutikliais, simuliuodamas [rpi-vl53l0x Pip paketą](https://pypi.org/project/rpi-vl53l0x/), Python paketą, kuris sąveikauja su [VL53L0X laiko skrydžio atstumo jutikliu](https://wiki.seeedstudio.com/Grove-Time_of_Flight_Distance_Sensor-VL53L0X/). Įsitikinkite, kad tai įdiegiate terminale su aktyvuota virtualia aplinka.

    ```sh
    pip install counterfit-shims-rpi-vl53l0x
    ```

1. Įsitikinkite, kad CounterFit internetinė programa veikia.

1. Sukurkite atstumo jutiklį:

    1. *Create sensor* laukelyje *Sensors* skydelyje, išskleidžiamajame *Sensor type* laukelyje pasirinkite *Distance*.

    1. Palikite *Units* kaip `Millimeter`.

    1. Šis jutiklis yra I²C jutiklis, todėl nustatykite adresą kaip `0x29`. Jei naudotumėte fizinį VL53L0X jutiklį, jis būtų užkoduotas šiuo adresu.

    1. Pasirinkite **Add** mygtuką, kad sukurtumėte atstumo jutiklį.

    ![Atstumo jutiklio nustatymai](../../../../../translated_images/lt/counterfit-create-distance-sensor.967c9fb98f27888d.webp)

    Atstumo jutiklis bus sukurtas ir pasirodys jutiklių sąraše.

    ![Sukurtas atstumo jutiklis](../../../../../translated_images/lt/counterfit-distance-sensor.079eefeeea0b68af.webp)

## Programuoti atstumo jutiklį

Dabar virtualus IoT įrenginys gali būti užprogramuotas naudoti simuliuotą atstumo jutiklį.

### Užduotis - programuoti laiko skrydžio jutiklį

1. Sukurkite naują failą `fruit-quality-detector` projekte, pavadintą `distance-sensor.py`.

    > 💁 Paprastas būdas simuliuoti kelis IoT įrenginius yra kiekvieną jų programuoti atskirame Python faile, tada paleisti juos vienu metu.

1. Pradėkite ryšį su CounterFit naudodami šį kodą:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Pridėkite šį kodą žemiau:

    ```python
    import time
    
    from counterfit_shims_rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Tai importuoja jutiklio bibliotekos shim VL53L0X laiko skrydžio jutikliui.

1. Žemiau pridėkite šį kodą, kad pasiektumėte jutiklį:

    ```python
    distance_sensor = VL53L0X()
    distance_sensor.begin()
    ```

    Šis kodas deklaruoja atstumo jutiklį, tada paleidžia jutiklį.

1. Galiausiai pridėkite begalinę kilpą, kad nuskaitytumėte atstumus:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Šis kodas laukia, kol jutiklis bus pasiruošęs nuskaityti vertę, tada išveda ją į konsolę.

1. Paleiskite šį kodą.

    > 💁 Nepamirškite, kad šis failas vadinasi `distance-sensor.py`! Įsitikinkite, kad paleidžiate jį per Python, o ne `app.py`.

1. Konsolėje pamatysite atstumo matavimus. Pakeiskite vertę CounterFit programoje, kad pamatytumėte, kaip ji keičiasi, arba naudokite atsitiktines vertes.

    ```output
    (.venv) ➜  fruit-quality-detector python distance-sensor.py 
    Distance = 37 mm
    Distance = 42 mm
    Distance = 29 mm
    ```

> 💁 Šį kodą galite rasti [code-proximity/virtual-iot-device](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/virtual-iot-device) aplanke.

😀 Jūsų artumo jutiklio programa buvo sėkminga!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama profesionali žmogaus vertimo paslauga. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius naudojant šį vertimą.