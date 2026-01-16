<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "11f10c6760fb8202cf368422702fdf70",
  "translation_date": "2025-08-28T10:38:23+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-sensor.md",
  "language_code": "ro"
}
-->
# Construiește o lampă de veghe - Hardware IoT Virtual

În această parte a lecției, vei adăuga un senzor de lumină dispozitivului tău IoT virtual.

## Hardware Virtual

Lampa de veghe necesită un senzor, creat în aplicația CounterFit.

Senzorul este un **senzor de lumină**. Într-un dispozitiv IoT fizic, acesta ar fi un [fotodiod](https://wikipedia.org/wiki/Photodiode) care transformă lumina într-un semnal electric. Senzorii de lumină sunt senzori analogici care trimit o valoare întreagă ce indică o cantitate relativă de lumină, fără a se raporta la o unitate standard de măsură, cum ar fi [lux](https://wikipedia.org/wiki/Lux).

### Adaugă senzorii în CounterFit

Pentru a utiliza un senzor de lumină virtual, trebuie să-l adaugi în aplicația CounterFit.

#### Sarcină - adaugă senzorii în CounterFit

Adaugă senzorul de lumină în aplicația CounterFit.

1. Asigură-te că aplicația web CounterFit rulează din partea anterioară a acestui exercițiu. Dacă nu, pornește-o.

1. Creează un senzor de lumină:

    1. În caseta *Create sensor* din panoul *Sensors*, deschide lista derulantă *Sensor type* și selectează *Light*.

    1. Lasă *Units* setat pe *NoUnits*.

    1. Asigură-te că *Pin* este setat pe *0*.

    1. Selectează butonul **Add** pentru a crea senzorul de lumină pe Pin 0.

    ![Setările senzorului de lumină](../../../../../translated_images/ro/counterfit-create-light-sensor.9f36a5e0d4458d8d554d54b34d2c806d56093d6e49fddcda2d20f6fef7f5cce1.png)

    Senzorul de lumină va fi creat și va apărea în lista de senzori.

    ![Senzorul de lumină creat](../../../../../translated_images/ro/counterfit-light-sensor.5d0f5584df56b90f6b2561910d9cb20dfbd73eeff2177c238d38f4de54aefae1.png)

## Programează senzorul de lumină

Dispozitivul poate fi acum programat pentru a utiliza senzorul de lumină integrat.

### Sarcină - programează senzorul de lumină

Programează dispozitivul.

1. Deschide proiectul lămpii de veghe în VS Code pe care l-ai creat în partea anterioară a acestui exercițiu. Oprește și recreează terminalul pentru a te asigura că rulează folosind mediul virtual, dacă este necesar.

1. Deschide fișierul `app.py`.

1. Adaugă următorul cod în partea de sus a fișierului `app.py`, alături de celelalte declarații `import`, pentru a importa biblioteci necesare:

    ```python
    import time
    from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    Declarația `import time` importă modulul Python `time`, care va fi utilizat mai târziu în acest exercițiu.

    Declarația `from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor` importă `GroveLightSensor` din bibliotecile Python CounterFit Grove shim. Această bibliotecă conține cod pentru a interacționa cu un senzor de lumină creat în aplicația CounterFit.

1. Adaugă următorul cod la sfârșitul fișierului pentru a crea instanțe ale claselor care gestionează senzorul de lumină:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    Linia `light_sensor = GroveLightSensor(0)` creează o instanță a clasei `GroveLightSensor`, conectându-se la pinul **0** - pinul CounterFit Grove la care este conectat senzorul de lumină.

1. Adaugă un ciclu infinit după codul de mai sus pentru a interoga valoarea senzorului de lumină și a o afișa în consolă:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Acest cod va citi nivelul curent de lumină folosind proprietatea `light` a clasei `GroveLightSensor`. Această proprietate citește valoarea analogică de la pin. Valoarea este apoi afișată în consolă.

1. Adaugă o pauză scurtă de o secundă la sfârșitul buclei `while`, deoarece nivelurile de lumină nu trebuie verificate continuu. O pauză reduce consumul de energie al dispozitivului.

    ```python
    time.sleep(1)
    ```

1. Din terminalul VS Code, rulează următoarea comandă pentru a rula aplicația Python:

    ```sh
    python3 app.py
    ```

    Valorile luminii vor fi afișate în consolă. Inițial, această valoare va fi 0.

1. Din aplicația CounterFit, modifică valoarea senzorului de lumină care va fi citită de aplicație. Poți face acest lucru în două moduri:

    * Introdu un număr în caseta *Value* pentru senzorul de lumină, apoi selectează butonul **Set**. Numărul introdus va fi valoarea returnată de senzor.

    * Bifează caseta *Random* și introdu valori *Min* și *Max*, apoi selectează butonul **Set**. De fiecare dată când senzorul citește o valoare, aceasta va fi un număr aleator între *Min* și *Max*.

    Valorile setate vor fi afișate în consolă. Modifică setările *Value* sau *Random* pentru a face ca valoarea să se schimbe.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

> 💁 Poți găsi acest cod în folderul [code-sensor/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/virtual-device).

😀 Programul tău pentru lampă de veghe a fost un succes!

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa maternă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.