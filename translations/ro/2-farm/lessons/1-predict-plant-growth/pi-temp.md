# Măsurarea temperaturii - Raspberry Pi

În această parte a lecției, vei adăuga un senzor de temperatură la Raspberry Pi-ul tău.

## Hardware

Senzorul pe care îl vei folosi este un [senzor de umiditate și temperatură DHT11](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), care combină 2 senzori într-un singur dispozitiv. Acesta este destul de popular, existând numeroși senzori comerciali care combină măsurarea temperaturii, umidității și, uneori, a presiunii atmosferice. Componenta de măsurare a temperaturii este un termistor cu coeficient de temperatură negativ (NTC), un tip de termistor a cărui rezistență scade pe măsură ce temperatura crește.

Acesta este un senzor digital, ceea ce înseamnă că are un ADC integrat pentru a genera un semnal digital care conține datele despre temperatură și umiditate, pe care microcontrolerul le poate citi.

### Conectarea senzorului de temperatură

Senzorul de temperatură Grove poate fi conectat la Raspberry Pi.

#### Sarcină

Conectează senzorul de temperatură

![Un senzor de temperatură Grove](../../../../../translated_images/ro/grove-dht11.07f8eafceee17004.webp)

1. Introdu un capăt al unui cablu Grove în mufa senzorului de umiditate și temperatură. Acesta va intra doar într-un singur sens.

1. Cu Raspberry Pi-ul oprit, conectează celălalt capăt al cablului Grove la mufa digitală marcată **D5** de pe Grove Base Hat atașat la Pi. Această mufă este a doua de la stânga, pe rândul de mufe de lângă pini GPIO.

![Senzorul de temperatură Grove conectat la mufa A0](../../../../../translated_images/ro/pi-temperature-sensor.3ff82fff672c8e56.webp)

## Programarea senzorului de temperatură

Dispozitivul poate fi acum programat pentru a utiliza senzorul de temperatură atașat.

### Sarcină

Programează dispozitivul.

1. Pornește Raspberry Pi-ul și așteaptă să se încarce sistemul.

1. Lansează VS Code, fie direct pe Pi, fie conectându-te prin extensia Remote SSH.

    > ⚠️ Poți consulta [instrucțiunile pentru configurarea și lansarea VS Code din lecția 1, dacă este necesar](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Din terminal, creează un nou folder în directorul home al utilizatorului `pi`, numit `temperature-sensor`. Creează un fișier în acest folder numit `app.py`:

    ```sh
    mkdir temperature-sensor
    cd temperature-sensor
    touch app.py
    ```

1. Deschide acest folder în VS Code.

1. Pentru a utiliza senzorul de temperatură și umiditate, trebuie instalat un pachet suplimentar Pip. Din terminalul din VS Code, rulează următoarea comandă pentru a instala acest pachet Pip pe Pi:

    ```sh
    pip3 install seeed-python-dht
    ```

1. Adaugă următorul cod în fișierul `app.py` pentru a importa bibliotecile necesare:

    ```python
    import time
    from seeed_dht import DHT
    ```

    Instrucțiunea `from seeed_dht import DHT` importă clasa `DHT` pentru a interacționa cu un senzor de temperatură Grove din modulul `seeed_dht`.

1. Adaugă următorul cod după cel de mai sus pentru a crea o instanță a clasei care gestionează senzorul de temperatură:

    ```python
    sensor = DHT("11", 5)
    ```

    Aceasta declară o instanță a clasei `DHT` care gestionează senzorul digital de umiditate și temperatură (**D**igital **H**umidity and **T**emperature). Primul parametru indică faptul că senzorul utilizat este *DHT11* - biblioteca pe care o folosești suportă și alte variante ale acestui senzor. Al doilea parametru indică faptul că senzorul este conectat la portul digital `D5` de pe Grove Base Hat.

    > ✅ Reține, toate mufele au numere de pini unice. Pinii 0, 2, 4 și 6 sunt pini analogici, iar pinii 5, 16, 18, 22, 24 și 26 sunt pini digitali.

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

1. Din terminalul VS Code, rulează următoarea comandă pentru a porni aplicația Python:

    ```sh
    python3 app.py
    ```

    Ar trebui să vezi valorile temperaturii afișate în consolă. Folosește ceva pentru a încălzi senzorul, cum ar fi apăsarea cu degetul pe el sau utilizarea unui ventilator, pentru a observa schimbările valorilor:

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py 
    Temperature 26°C
    Temperature 26°C
    Temperature 28°C
    Temperature 30°C
    Temperature 32°C
    ```

> 💁 Poți găsi acest cod în folderul [code-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/pi).

😀 Programul tău pentru senzorul de temperatură a fost un succes!

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să fiți conștienți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.