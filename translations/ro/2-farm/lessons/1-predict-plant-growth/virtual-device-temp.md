# Măsurarea temperaturii - Hardware IoT Virtual

În această parte a lecției, vei adăuga un senzor de temperatură dispozitivului tău IoT virtual.

## Hardware Virtual

Dispozitivul IoT virtual va folosi un senzor simulat Grove Digital Humidity and Temperature. Acest lucru menține laboratorul similar cu utilizarea unui Raspberry Pi cu un senzor fizic Grove DHT11.

Senzorul combină un **senzor de temperatură** cu un **senzor de umiditate**, dar în acest laborator te vei concentra doar pe componenta senzorului de temperatură. Într-un dispozitiv IoT fizic, senzorul de temperatură ar fi un [termistor](https://wikipedia.org/wiki/Thermistor) care măsoară temperatura detectând o schimbare a rezistenței pe măsură ce temperatura se modifică. Senzorii de temperatură sunt de obicei senzori digitali care convertesc intern rezistența măsurată într-o temperatură exprimată în grade Celsius (sau Kelvin, sau Fahrenheit).

### Adăugarea senzorilor în CounterFit

Pentru a utiliza un senzor virtual de umiditate și temperatură, trebuie să adaugi cei doi senzori în aplicația CounterFit.

#### Sarcină - adaugă senzorii în CounterFit

Adaugă senzorii de umiditate și temperatură în aplicația CounterFit.

1. Creează o nouă aplicație Python pe computerul tău într-un folder numit `temperature-sensor` cu un singur fișier numit `app.py`, un mediu virtual Python și adaugă pachetele pip CounterFit.

    > ⚠️ Poți consulta [instrucțiunile pentru crearea și configurarea unui proiect Python CounterFit în lecția 1, dacă este necesar](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Instalează un pachet suplimentar Pip pentru a instala un shim CounterFit pentru senzorul DHT11. Asigură-te că instalezi acest pachet dintr-un terminal cu mediul virtual activat.

    ```sh
    pip install counterfit-shims-seeed-python-dht
    ```

1. Asigură-te că aplicația web CounterFit este pornită.

1. Creează un senzor de umiditate:

    1. În caseta *Create sensor* din panoul *Sensors*, deschide meniul derulant *Sensor type* și selectează *Humidity*.

    1. Lasă *Units* setat pe *Percentage*.

    1. Asigură-te că *Pin* este setat pe *5*.

    1. Selectează butonul **Add** pentru a crea senzorul de umiditate pe Pin 5.

    ![Setările senzorului de umiditate](../../../../../translated_images/ro/counterfit-create-humidity-sensor.2750e27b6f30e09c.webp)

    Senzorul de umiditate va fi creat și va apărea în lista de senzori.

    ![Senzorul de umiditate creat](../../../../../translated_images/ro/counterfit-humidity-sensor.7b12f7f339e430cb.webp)

1. Creează un senzor de temperatură:

    1. În caseta *Create sensor* din panoul *Sensors*, deschide meniul derulant *Sensor type* și selectează *Temperature*.

    1. Lasă *Units* setat pe *Celsius*.

    1. Asigură-te că *Pin* este setat pe *6*.

    1. Selectează butonul **Add** pentru a crea senzorul de temperatură pe Pin 6.

    ![Setările senzorului de temperatură](../../../../../translated_images/ro/counterfit-create-temperature-sensor.199350ed34f7343d.webp)

    Senzorul de temperatură va fi creat și va apărea în lista de senzori.

    ![Senzorul de temperatură creat](../../../../../translated_images/ro/counterfit-temperature-sensor.f0560236c96a9016.webp)

## Programează aplicația senzorului de temperatură

Acum poți programa aplicația senzorului de temperatură folosind senzorii CounterFit.

### Sarcină - programează aplicația senzorului de temperatură

Programează aplicația senzorului de temperatură.

1. Asigură-te că aplicația `temperature-sensor` este deschisă în VS Code.

1. Deschide fișierul `app.py`.

1. Adaugă următorul cod în partea de sus a fișierului `app.py` pentru a conecta aplicația la CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Adaugă următorul cod în fișierul `app.py` pentru a importa bibliotecile necesare:

    ```python
    import time
    from counterfit_shims_seeed_python_dht import DHT
    ```

    Instrucțiunea `from seeed_dht import DHT` importă clasa `DHT` pentru a interacționa cu un senzor virtual Grove de temperatură folosind un shim din modulul `counterfit_shims_seeed_python_dht`.

1. Adaugă următorul cod după cel de mai sus pentru a crea o instanță a clasei care gestionează senzorul virtual de umiditate și temperatură:

    ```python
    sensor = DHT("11", 5)
    ```

    Aceasta declară o instanță a clasei `DHT` care gestionează senzorul virtual de **U**miditate și **T**emperatură. Primul parametru indică faptul că senzorul utilizat este un senzor virtual *DHT11*. Al doilea parametru indică faptul că senzorul este conectat la portul `5`.

    > 💁 CounterFit simulează acest senzor combinat de umiditate și temperatură conectându-se la 2 senzori: un senzor de umiditate pe pinul specificat când este creată clasa `DHT` și un senzor de temperatură care rulează pe pinul următor. Dacă senzorul de umiditate este pe pinul 5, shim-ul se așteaptă ca senzorul de temperatură să fie pe pinul 6.

1. Adaugă un buclă infinită după codul de mai sus pentru a citi valoarea senzorului de temperatură și a o afișa în consolă:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    Apelul `sensor.read()` returnează un tuplu cu umiditatea și temperatura. Ai nevoie doar de valoarea temperaturii, așa că umiditatea este ignorată. Valoarea temperaturii este apoi afișată în consolă.

1. Adaugă o pauză scurtă de zece secunde la sfârșitul buclei, deoarece nivelurile de temperatură nu trebuie verificate continuu. O pauză reduce consumul de energie al dispozitivului.

    ```python
    time.sleep(10)
    ```

1. Din terminalul VS Code cu un mediu virtual activat, rulează următoarea comandă pentru a porni aplicația Python:

    ```sh
    python app.py
    ```

1. Din aplicația CounterFit, modifică valoarea senzorului de temperatură care va fi citită de aplicație. Poți face acest lucru în două moduri:

    * Introdu un număr în caseta *Value* pentru senzorul de temperatură, apoi selectează butonul **Set**. Numărul introdus va fi valoarea returnată de senzor.

    * Bifează caseta *Random* și introdu o valoare *Min* și *Max*, apoi selectează butonul **Set**. De fiecare dată când senzorul citește o valoare, aceasta va fi un număr aleatoriu între *Min* și *Max*.

    Ar trebui să vezi valorile setate apărând în consolă. Modifică setările *Value* sau *Random* pentru a vedea schimbarea valorii.

    ```output
    (.venv) ➜  temperature-sensor python app.py
    Temperature 28.25°C
    Temperature 30.71°C
    Temperature 25.17°C
    ```

> 💁 Poți găsi acest cod în folderul [code-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/virtual-device).

😀 Programul senzorului tău de temperatură a fost un succes!

---

**Declinarea responsabilității**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși depunem eforturi pentru a asigura acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa nativă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm răspunderea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.