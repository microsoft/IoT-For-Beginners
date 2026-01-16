<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e9f05bdc50a40fd924b1d66934471bf",
  "translation_date": "2025-08-28T08:28:56+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/virtual-device-proximity.md",
  "language_code": "ro"
}
-->
# Detectează proximitatea - Hardware IoT Virtual

În această parte a lecției, vei adăuga un senzor de proximitate dispozitivului tău IoT virtual și vei citi distanța de la acesta.

## Hardware

Dispozitivul IoT virtual va folosi un senzor de distanță simulat.

Într-un dispozitiv IoT fizic, ai folosi un senzor cu un modul de măsurare cu laser pentru a detecta distanța.

### Adaugă senzorul de distanță în CounterFit

Pentru a utiliza un senzor de distanță virtual, trebuie să adaugi unul în aplicația CounterFit.

#### Sarcină - adaugă senzorul de distanță în CounterFit

Adaugă senzorul de distanță în aplicația CounterFit.

1. Deschide codul `fruit-quality-detector` în VS Code și asigură-te că mediul virtual este activat.

1. Instalează un pachet suplimentar Pip pentru a instala un shim CounterFit care poate comunica cu senzorii de distanță simulând pachetul [rpi-vl53l0x Pip](https://pypi.org/project/rpi-vl53l0x/), un pachet Python care interacționează cu [un senzor de distanță VL53L0X bazat pe timpul de zbor](https://wiki.seeedstudio.com/Grove-Time_of_Flight_Distance_Sensor-VL53L0X/). Asigură-te că instalezi acest pachet dintr-un terminal cu mediul virtual activat.

    ```sh
    pip install counterfit-shims-rpi-vl53l0x
    ```

1. Asigură-te că aplicația web CounterFit este pornită.

1. Creează un senzor de distanță:

    1. În caseta *Create sensor* din panoul *Sensors*, deschide meniul derulant *Sensor type* și selectează *Distance*.

    1. Lasă *Units* ca `Millimeter`.

    1. Acest senzor este un senzor I²C, așa că setează adresa la `0x29`. Dacă ai folosi un senzor VL53L0X fizic, acesta ar fi codificat la această adresă.

    1. Selectează butonul **Add** pentru a crea senzorul de distanță.

    ![Setările senzorului de distanță](../../../../../translated_images/ro/counterfit-create-distance-sensor.967c9fb98f27888d95920c9784d004c972490eb71f70397fe13bd70a79a879a3.png)

    Senzorul de distanță va fi creat și va apărea în lista de senzori.

    ![Senzorul de distanță creat](../../../../../translated_images/ro/counterfit-distance-sensor.079eefeeea0b68afc36431ce8fcbe2f09a7e4916ed1cd5cb30e696db53bc18fa.png)

## Programează senzorul de distanță

Dispozitivul IoT virtual poate fi acum programat pentru a utiliza senzorul de distanță simulat.

### Sarcină - programează senzorul de timp de zbor

1. Creează un fișier nou în proiectul `fruit-quality-detector` numit `distance-sensor.py`.

    > 💁 O modalitate ușoară de a simula mai multe dispozitive IoT este să le creezi pe fiecare într-un fișier Python diferit, apoi să le rulezi simultan.

1. Pornește o conexiune la CounterFit cu următorul cod:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Adaugă următorul cod dedesubt:

    ```python
    import time
    
    from counterfit_shims_rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Acesta importă biblioteca shim pentru senzorul VL53L0X bazat pe timpul de zbor.

1. Sub acest cod, adaugă următorul cod pentru a accesa senzorul:

    ```python
    distance_sensor = VL53L0X()
    distance_sensor.begin()
    ```

    Acest cod declară un senzor de distanță, apoi pornește senzorul.

1. În cele din urmă, adaugă un buclă infinită pentru a citi distanțele:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Acest cod așteaptă ca o valoare să fie gata pentru a fi citită de la senzor, apoi o afișează în consolă.

1. Rulează acest cod.

    > 💁 Nu uita că acest fișier se numește `distance-sensor.py`! Asigură-te că îl rulezi cu Python, nu cu `app.py`.

1. Vei vedea măsurători ale distanței apărând în consolă. Schimbă valoarea în CounterFit pentru a vedea cum se modifică, sau folosește valori aleatorii.

    ```output
    (.venv) ➜  fruit-quality-detector python distance-sensor.py 
    Distance = 37 mm
    Distance = 42 mm
    Distance = 29 mm
    ```

> 💁 Poți găsi acest cod în folderul [code-proximity/virtual-iot-device](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/virtual-iot-device).

😀 Programul tău pentru senzorul de proximitate a fost un succes!

---

**Declinarea responsabilității**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm răspunderea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.