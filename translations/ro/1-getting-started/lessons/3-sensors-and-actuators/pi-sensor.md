<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ea733bd0cdf2479e082373f765a08678",
  "translation_date": "2025-08-28T10:35:45+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-sensor.md",
  "language_code": "ro"
}
-->
# Construiește o lampă de veghe - Raspberry Pi

În această parte a lecției, vei adăuga un senzor de lumină la Raspberry Pi-ul tău.

## Hardware

Senzorul utilizat în această lecție este un **senzor de lumină** care folosește un [fotodiod](https://wikipedia.org/wiki/Photodiode) pentru a converti lumina într-un semnal electric. Acesta este un senzor analogic care trimite o valoare întreagă de la 0 la 1.000, indicând o cantitate relativă de lumină care nu corespunde unei unități standard de măsură, cum ar fi [lux](https://wikipedia.org/wiki/Lux).

Senzorul de lumină este un senzor extern Grove și trebuie conectat la Grove Base hat pe Raspberry Pi.

### Conectează senzorul de lumină

Senzorul de lumină Grove utilizat pentru detectarea nivelurilor de lumină trebuie conectat la Raspberry Pi.

#### Sarcină - conectează senzorul de lumină

Conectează senzorul de lumină.

![Un senzor de lumină Grove](../../../../../translated_images/ro/grove-light-sensor.b8127b7c434e632d6bcdb57587a14e9ef69a268a22df95d08628f62b8fa5505c.png)

1. Introdu un capăt al unui cablu Grove în soclul modulului senzorului de lumină. Acesta va intra doar într-un singur mod.

1. Cu Raspberry Pi-ul oprit, conectează celălalt capăt al cablului Grove la soclul analogic marcat **A0** de pe Grove Base hat atașat la Pi. Acest soclu este al doilea din dreapta, pe rândul de socluri de lângă pini GPIO.

![Senzorul de lumină Grove conectat la soclul A0](../../../../../translated_images/ro/pi-light-sensor.66cc1e31fa48cd7d5f23400d4b2119aa41508275cb7c778053a7923b4e972d7e.png)

## Programează senzorul de lumină

Dispozitivul poate fi acum programat folosind senzorul de lumină Grove.

### Sarcină - programează senzorul de lumină

Programează dispozitivul.

1. Pornește Pi-ul și așteaptă să se încarce.

1. Deschide proiectul de lampă de veghe în VS Code pe care l-ai creat în partea anterioară a acestei teme, fie rulând direct pe Pi, fie conectându-te folosind extensia Remote SSH.

1. Deschide fișierul `app.py` și șterge tot codul din el.

1. Adaugă următorul cod în fișierul `app.py` pentru a importa câteva biblioteci necesare:

    ```python
    import time
    from grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    Instrucțiunea `import time` importă modulul `time`, care va fi utilizat mai târziu în această temă.

    Instrucțiunea `from grove.grove_light_sensor_v1_2 import GroveLightSensor` importă `GroveLightSensor` din bibliotecile Python Grove. Această bibliotecă conține cod pentru a interacționa cu un senzor de lumină Grove și a fost instalată global în timpul configurării Pi-ului.

1. Adaugă următorul cod după cel de mai sus pentru a crea o instanță a clasei care gestionează senzorul de lumină:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    Linia `light_sensor = GroveLightSensor(0)` creează o instanță a clasei `GroveLightSensor`, conectându-se la pinul **A0** - pinul analogic Grove la care este conectat senzorul de lumină.

1. Adaugă un buclă infinită după codul de mai sus pentru a interoga valoarea senzorului de lumină și a o afișa în consolă:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Aceasta va citi nivelul curent de lumină pe o scară de la 0 la 1.023 folosind proprietatea `light` a clasei `GroveLightSensor`. Această proprietate citește valoarea analogică de la pin. Această valoare este apoi afișată în consolă.

1. Adaugă o pauză scurtă de o secundă la sfârșitul buclei, deoarece nivelurile de lumină nu trebuie verificate continuu. O pauză reduce consumul de energie al dispozitivului.

    ```python
    time.sleep(1)
    ```

1. Din terminalul VS Code, rulează următoarea comandă pentru a rula aplicația Python:

    ```sh
    python3 app.py
    ```

    Valorile de lumină vor fi afișate în consolă. Acoperă și descoperă senzorul de lumină, iar valorile se vor schimba:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

> 💁 Poți găsi acest cod în folderul [code-sensor/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/pi).

😀 Adăugarea unui senzor la programul tău de lampă de veghe a fost un succes!

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.