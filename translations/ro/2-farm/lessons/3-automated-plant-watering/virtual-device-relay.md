<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f8f541ee945545017a51aaf309aa37c3",
  "translation_date": "2025-08-28T11:41:29+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/virtual-device-relay.md",
  "language_code": "ro"
}
-->
# Controlează un releu - Hardware IoT Virtual

În această parte a lecției, vei adăuga un releu dispozitivului tău IoT virtual, pe lângă senzorul de umiditate a solului, și îl vei controla în funcție de nivelul de umiditate a solului.

## Hardware Virtual

Dispozitivul IoT virtual va folosi un releu simulat Grove. Acest lucru menține laboratorul similar cu utilizarea unui Raspberry Pi cu un releu fizic Grove.

Într-un dispozitiv IoT fizic, releul ar fi un releu normal-deschis (ceea ce înseamnă că circuitul de ieșire este deschis sau deconectat atunci când nu este trimis niciun semnal către releu). Un astfel de releu poate gestiona circuite de ieșire de până la 250V și 10A.

### Adaugă releul în CounterFit

Pentru a folosi un releu virtual, trebuie să-l adaugi în aplicația CounterFit.

#### Sarcină

Adaugă releul în aplicația CounterFit.

1. Deschide proiectul `soil-moisture-sensor` din lecția anterioară în VS Code, dacă nu este deja deschis. Vei adăuga la acest proiect.

1. Asigură-te că aplicația web CounterFit este pornită.

1. Creează un releu:

    1. În caseta *Create actuator* din panoul *Actuators*, deschide meniul derulant *Actuator type* și selectează *Relay*.

    1. Setează *Pin* la *5*.

    1. Selectează butonul **Add** pentru a crea releul pe Pin 5.

    ![Setările releului](../../../../../translated_images/ro/counterfit-create-relay.fa7c40fd0f2f6afc33b35ea94fcb235085be4861e14e3fe6b9b7bcfc82d1c888.png)

    Releul va fi creat și va apărea în lista de actuatori.

    ![Releul creat](../../../../../translated_images/ro/counterfit-relay.bbf74c1dbdc8b9acd983367fcbd06703a402aefef6af54ddb28e11307ba8a12c.png)

## Programează releul

Aplicația senzorului de umiditate a solului poate fi acum programată pentru a folosi releul virtual.

### Sarcină

Programează dispozitivul virtual.

1. Deschide proiectul `soil-moisture-sensor` din lecția anterioară în VS Code, dacă nu este deja deschis. Vei adăuga la acest proiect.

1. Adaugă următorul cod în fișierul `app.py`, sub importurile existente:

    ```python
    from counterfit_shims_grove.grove_relay import GroveRelay
    ```

    Această instrucțiune importă `GroveRelay` din bibliotecile Grove Python shim pentru a interacționa cu releul virtual Grove.

1. Adaugă următorul cod sub declarația clasei `ADC` pentru a crea o instanță `GroveRelay`:

    ```python
    relay = GroveRelay(5)
    ```

    Acest cod creează un releu folosind pinul **5**, pinul la care ai conectat releul.

1. Pentru a testa dacă releul funcționează, adaugă următorul cod în bucla `while True:`:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    Codul pornește releul, așteaptă 0,5 secunde, apoi oprește releul.

1. Rulează aplicația Python. Releul se va porni și opri la fiecare 10 secunde, cu o întârziere de jumătate de secundă între pornire și oprire. Vei vedea releul virtual din aplicația CounterFit închizându-se și deschizându-se pe măsură ce releul este pornit și oprit.

    ![Releul virtual pornind și oprindu-se](../../../../../images/virtual-relay-turn-on-off.gif)

## Controlează releul în funcție de umiditatea solului

Acum că releul funcționează, acesta poate fi controlat în funcție de citirile senzorului de umiditate a solului.

### Sarcină

Controlează releul.

1. Șterge cele 3 linii de cod pe care le-ai adăugat pentru a testa releul. Înlocuiește-le cu următorul cod:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    Acest cod verifică nivelul de umiditate a solului de la senzorul de umiditate a solului. Dacă este peste 450, pornește releul, iar dacă scade sub 450, îl oprește.

    > 💁 Reține că senzorul capacitiv de umiditate a solului citește: cu cât nivelul de umiditate a solului este mai mic, cu atât solul este mai umed și invers.

1. Rulează aplicația Python. Vei vedea releul pornindu-se sau oprindu-se în funcție de nivelurile de umiditate a solului. Schimbă setările *Value* sau *Random* pentru senzorul de umiditate a solului pentru a vedea cum se schimbă valoarea.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Poți găsi acest cod în folderul [code-relay/virtual-device](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/virtual-device).

😀 Programul tău de control al unui releu cu senzorul virtual de umiditate a solului a fost un succes!

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.