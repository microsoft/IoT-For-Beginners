# Măsurarea umidității solului - Raspberry Pi

În această parte a lecției, vei adăuga un senzor capacitiv de umiditate a solului la Raspberry Pi și vei citi valorile acestuia.

## Hardware

Raspberry Pi are nevoie de un senzor capacitiv de umiditate a solului.

Senzorul pe care îl vei folosi este un [Senzor Capacitiv de Umiditate a Solului](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), care măsoară umiditatea solului detectând capacitatea acestuia, o proprietate care se modifică pe măsură ce umiditatea solului se schimbă. Pe măsură ce umiditatea solului crește, tensiunea scade.

Acesta este un senzor analogic, astfel că folosește un pin analogic și convertorul ADC pe 10 biți din Grove Base Hat de pe Pi pentru a transforma tensiunea într-un semnal digital între 1 și 1.023. Acest semnal este apoi trimis prin I²C prin pinii GPIO de pe Pi.

### Conectează senzorul de umiditate a solului

Senzorul Grove de umiditate a solului poate fi conectat la Raspberry Pi.

#### Sarcină - conectează senzorul de umiditate a solului

Conectează senzorul de umiditate a solului.

![Un senzor Grove de umiditate a solului](../../../../../translated_images/ro/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78b.webp)

1. Introdu un capăt al unui cablu Grove în mufa senzorului de umiditate a solului. Acesta va intra doar într-un singur mod.

1. Cu Raspberry Pi oprit, conectează celălalt capăt al cablului Grove la mufa analogică marcată **A0** de pe Grove Base Hat atașat la Pi. Această mufă este a doua din dreapta, pe rândul de mufe de lângă pinii GPIO.

![Senzorul Grove de umiditate a solului conectat la mufa A0](../../../../../translated_images/ro/pi-soil-moisture-sensor.fdd7eb2393792cf6.webp)

1. Introdu senzorul de umiditate a solului în pământ. Acesta are o „linie de poziție maximă” - o linie albă trasată pe senzor. Introdu senzorul până la această linie, dar nu mai mult.

![Senzorul Grove de umiditate a solului în pământ](../../../../../translated_images/ro/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

## Programează senzorul de umiditate a solului

Acum Raspberry Pi poate fi programat pentru a utiliza senzorul de umiditate a solului atașat.

### Sarcină - programează senzorul de umiditate a solului

Programează dispozitivul.

1. Pornește Pi-ul și așteaptă să se încarce.

1. Lansează VS Code, fie direct pe Pi, fie conectându-te prin extensia Remote SSH.

    > ⚠️ Poți consulta [instrucțiunile pentru configurarea și lansarea VS Code în lecția despre nightlight - lecția 1, dacă este necesar](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Din terminal, creează un nou folder în directorul home al utilizatorului `pi`, numit `soil-moisture-sensor`. Creează un fișier în acest folder numit `app.py`.

1. Deschide acest folder în VS Code.

1. Adaugă următorul cod în fișierul `app.py` pentru a importa câteva biblioteci necesare:

    ```python
    import time
    from grove.adc import ADC
    ```

    Instrucțiunea `import time` importă modulul `time`, care va fi utilizat mai târziu în această sarcină.

    Instrucțiunea `from grove.adc import ADC` importă `ADC` din bibliotecile Python Grove. Această bibliotecă conține cod pentru a interacționa cu convertorul analog-digital de pe Grove Base Hat și pentru a citi tensiunile de la senzorii analogici.

1. Adaugă următorul cod mai jos pentru a crea o instanță a clasei `ADC`:

    ```python
    adc = ADC()
    ```

1. Adaugă un buclă infinită care citește de la acest ADC pe pinul A0 și afișează rezultatul în consolă. Această buclă poate apoi să aștepte 10 secunde între citiri.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)

        time.sleep(10)
    ```

1. Rulează aplicația Python. Vei vedea măsurătorile umidității solului afișate în consolă. Adaugă apă în sol sau scoate senzorul din sol și observă cum se schimbă valoarea.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

    În exemplul de ieșire de mai sus, poți observa cum tensiunea scade pe măsură ce se adaugă apă.

> 💁 Poți găsi acest cod în folderul [code/pi](../../../../../2-farm/lessons/2-detect-soil-moisture/code/pi).

😀 Programul pentru senzorul de umiditate a solului a fost un succes!

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa maternă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.