<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2bf65f162bcebd35fbcba5fd245afac4",
  "translation_date": "2025-08-28T11:02:41+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/virtual-device-soil-moisture.md",
  "language_code": "ro"
}
-->
# Măsurarea umidității solului - Hardware IoT Virtual

În această parte a lecției, vei adăuga un senzor capacitiv de umiditate a solului la dispozitivul tău IoT virtual și vei citi valorile de la acesta.

## Hardware Virtual

Dispozitivul IoT virtual va folosi un senzor capacitiv de umiditate a solului simulat Grove. Acest lucru menține laboratorul similar cu utilizarea unui Raspberry Pi cu un senzor capacitiv de umiditate a solului fizic.

Într-un dispozitiv IoT fizic, senzorul de umiditate a solului ar fi un senzor capacitiv care măsoară umiditatea solului detectând capacitatea solului, o proprietate care se schimbă odată cu variația umidității solului. Pe măsură ce umiditatea solului crește, tensiunea scade.

Acesta este un senzor analogic, așa că folosește un ADC simulat pe 10 biți pentru a raporta o valoare între 1 și 1.023.

### Adăugarea senzorului de umiditate a solului în CounterFit

Pentru a utiliza un senzor virtual de umiditate a solului, trebuie să-l adaugi în aplicația CounterFit.

#### Sarcină - Adăugarea senzorului de umiditate a solului în CounterFit

Adaugă senzorul de umiditate a solului în aplicația CounterFit.

1. Creează o nouă aplicație Python pe computerul tău într-un folder numit `soil-moisture-sensor` cu un singur fișier numit `app.py` și un mediu virtual Python, și adaugă pachetele pip CounterFit.

    > ⚠️ Poți consulta [instrucțiunile pentru crearea și configurarea unui proiect Python CounterFit în lecția 1, dacă este necesar](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Asigură-te că aplicația web CounterFit este pornită.

1. Creează un senzor de umiditate a solului:

    1. În caseta *Create sensor* din panoul *Sensors*, deschide meniul derulant *Sensor type* și selectează *Soil Moisture*.

    1. Lasă *Units* setat pe *NoUnits*.

    1. Asigură-te că *Pin* este setat pe *0*.

    1. Selectează butonul **Add** pentru a crea senzorul *Soil Moisture* pe Pin 0.

    ![Setările senzorului de umiditate a solului](../../../../../translated_images/ro/counterfit-create-soil-moisture-sensor.35266135a5e0ae68b29a684d7db0d2933a8098b2307d197f7c71577b724603aa.png)

    Senzorul de umiditate a solului va fi creat și va apărea în lista de senzori.

    ![Senzorul de umiditate a solului creat](../../../../../translated_images/ro/counterfit-soil-moisture-sensor.81742b2de0e9de60a3b3b9a2ff8ecc686d428eb6d71820f27a693be26e5aceee.png)

## Programarea aplicației senzorului de umiditate a solului

Aplicația senzorului de umiditate a solului poate fi acum programată folosind senzorii CounterFit.

### Sarcină - Programarea aplicației senzorului de umiditate a solului

Programează aplicația senzorului de umiditate a solului.

1. Asigură-te că aplicația `soil-moisture-sensor` este deschisă în VS Code.

1. Deschide fișierul `app.py`.

1. Adaugă următorul cod în partea de sus a fișierului `app.py` pentru a conecta aplicația la CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Adaugă următorul cod în fișierul `app.py` pentru a importa câteva biblioteci necesare:

    ```python
    import time
    from counterfit_shims_grove.adc import ADC
    ```

    Instrucțiunea `import time` importă modulul `time`, care va fi utilizat mai târziu în această sarcină.

    Instrucțiunea `from counterfit_shims_grove.adc import ADC` importă clasa `ADC` pentru a interacționa cu un convertor analog-digital virtual care se poate conecta la un senzor CounterFit.

1. Adaugă următorul cod sub acesta pentru a crea o instanță a clasei `ADC`:

    ```python
    adc = ADC()
    ```

1. Adaugă un ciclu infinit care citește de la acest ADC pe pinul 0 și scrie rezultatul în consolă. Acest ciclu poate dormi timp de 10 secunde între citiri.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)
    
        time.sleep(10)
    ```

1. Din aplicația CounterFit, schimbă valoarea senzorului de umiditate a solului care va fi citită de aplicație. Poți face acest lucru în două moduri:

    * Introdu un număr în caseta *Value* pentru senzorul de umiditate a solului, apoi selectează butonul **Set**. Numărul pe care îl introduci va fi valoarea returnată de senzor.

    * Bifează caseta *Random* și introdu valori *Min* și *Max*, apoi selectează butonul **Set**. De fiecare dată când senzorul citește o valoare, va citi un număr aleatoriu între *Min* și *Max*.

1. Rulează aplicația Python. Vei vedea măsurătorile de umiditate a solului scrise în consolă. Schimbă setările *Value* sau *Random* pentru a vedea cum se modifică valoarea.

    ```output
    (.venv) ➜ soil-moisture-sensor $ python app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

> 💁 Poți găsi acest cod în folderul [code/virtual-device](../../../../../2-farm/lessons/2-detect-soil-moisture/code/virtual-device).

😀 Programul senzorului de umiditate a solului a fost un succes!

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să fiți conștienți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.