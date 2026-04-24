# Detectează proximitatea - Raspberry Pi

În această parte a lecției, vei adăuga un senzor de proximitate la Raspberry Pi și vei citi distanța de la acesta.

## Hardware

Raspberry Pi are nevoie de un senzor de proximitate.

Senzorul pe care îl vei folosi este un [Grove Time of Flight distance sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Acest senzor utilizează un modul de măsurare cu laser pentru a detecta distanța. Senzorul are un interval de măsurare de la 10mm la 2000mm (1cm - 2m) și va raporta valori destul de precise în acest interval, cu distanțele de peste 1000mm raportate ca 8109mm.

Telemetrul laser se află pe partea din spate a senzorului, partea opusă soclului Grove.

Acesta este un senzor I²C.

### Conectează senzorul Time of Flight

Senzorul Grove Time of Flight poate fi conectat la Raspberry Pi.

#### Sarcină - conectează senzorul Time of Flight

Conectează senzorul Time of Flight.

![Un senzor Grove Time of Flight](../../../../../translated_images/ro/grove-time-of-flight-sensor.d82ff2165bfded9f.webp)

1. Introdu un capăt al unui cablu Grove în soclul senzorului Time of Flight. Acesta va intra doar într-un singur mod.

1. Cu Raspberry Pi oprit, conectează celălalt capăt al cablului Grove la unul dintre soclurile I²C marcate **I²C** pe Grove Base Hat atașat la Pi. Aceste socluri se află pe rândul de jos, la capătul opus pinilor GPIO și lângă slotul pentru cablul camerei.

![Senzorul Grove Time of Flight conectat la soclul I²C](../../../../../translated_images/ro/pi-time-of-flight-sensor.58c8dc04eb3bfb57.webp)

## Programează senzorul Time of Flight

Raspberry Pi poate fi acum programat pentru a utiliza senzorul Time of Flight atașat.

### Sarcină - programează senzorul Time of Flight

Programează dispozitivul.

1. Pornește Pi-ul și așteaptă să se încarce.

1. Deschide codul `fruit-quality-detector` în VS Code, fie direct pe Pi, fie conectându-te prin extensia Remote SSH.

1. Instalează pachetul rpi-vl53l0x Pip, un pachet Python care interacționează cu un senzor de distanță VL53L0X Time of Flight. Instalează-l folosind această comandă pip:

    ```sh
    pip install rpi-vl53l0x
    ```

1. Creează un fișier nou în acest proiect numit `distance-sensor.py`.

    > 💁 O modalitate ușoară de a simula mai multe dispozitive IoT este să le implementezi pe fiecare într-un fișier Python separat, apoi să le rulezi simultan.

1. Adaugă următorul cod în acest fișier:

    ```python
    import time
    
    from grove.i2c import Bus
    from rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Acest cod importă biblioteca Grove I²C bus și o bibliotecă pentru hardware-ul de bază al senzorului integrat în senzorul Grove Time of Flight.

1. Sub acest cod, adaugă următorul cod pentru a accesa senzorul:

    ```python
    distance_sensor = VL53L0X(bus = Bus().bus)
    distance_sensor.begin()    
    ```

    Acest cod declară un senzor de distanță utilizând Grove I²C bus, apoi pornește senzorul.

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

1. Vei vedea măsurători ale distanței apărând în consolă. Poziționează obiecte lângă senzor și vei vedea măsurătorile distanței:

    ```output
    pi@raspberrypi:~/fruit-quality-detector $ python3 distance_sensor.py 
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Telemetrul se află pe partea din spate a senzorului, așa că asigură-te că folosești partea corectă atunci când măsori distanța.

    ![Telemetrul de pe partea din spate a senzorului Time of Flight îndreptat spre o banană](../../../../../translated_images/ro/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 Poți găsi acest cod în folderul [code-proximity/pi](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/pi).

😀 Programul tău pentru senzorul de proximitate a fost un succes!

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să fiți conștienți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.