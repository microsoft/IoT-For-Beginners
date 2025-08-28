<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4efc74299e19f5d08f2f3f34451a11ba",
  "translation_date": "2025-08-28T11:33:28+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/single-board-computer-temp-publish.md",
  "language_code": "ro"
}
-->
# Publică temperatura - Hardware IoT Virtual și Raspberry Pi

În această parte a lecției, vei publica valorile temperaturii detectate de Raspberry Pi sau Dispozitivul IoT Virtual prin MQTT, astfel încât să poată fi utilizate ulterior pentru calcularea GDD.

## Publică temperatura

Odată ce temperatura a fost citită, aceasta poate fi publicată prin MQTT către un cod 'server' care va citi valorile și le va stoca, pregătite pentru a fi utilizate în calculul GDD.

### Sarcină - publică temperatura

Programează dispozitivul să publice datele despre temperatură.

1. Deschide proiectul aplicației `temperature-sensor` dacă nu este deja deschis.

1. Repetă pașii pe care i-ai făcut în lecția 4 pentru a te conecta la MQTT și a trimite telemetrie. Vei folosi același broker public Mosquitto.

    Pașii pentru aceasta sunt:

    - Adaugă pachetul pip pentru MQTT
    - Adaugă codul pentru a te conecta la brokerul MQTT
    - Adaugă codul pentru a publica telemetrie

    > ⚠️ Consultă [instrucțiunile pentru conectarea la MQTT](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md) și [instrucțiunile pentru trimiterea telemetriei](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md) din lecția 4, dacă este necesar.

1. Asigură-te că `client_name` reflectă numele acestui proiect:

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. Pentru telemetrie, în loc să trimiți o valoare de lumină, trimite valoarea temperaturii citită de senzorul DHT într-o proprietate din documentul JSON numită `temperature`:

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. Valoarea temperaturii nu trebuie citită foarte des - nu se va schimba mult într-un interval scurt de timp, așa că setează `time.sleep` la 10 minute:

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 Funcția `sleep` ia timpul în secunde, așa că pentru a fi mai ușor de citit, valoarea este transmisă ca rezultat al unui calcul. 60s într-un minut, deci 10 x (60s într-un minut) oferă o întârziere de 10 minute.

1. Rulează codul în același mod în care ai rulat codul din partea anterioară a temei. Dacă folosești un dispozitiv IoT virtual, asigură-te că aplicația CounterFit este pornită și senzorii de umiditate și temperatură au fost creați pe pinii corecți.

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 Poți găsi acest cod în folderul [code-publish-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/virtual-device) sau în folderul [code-publish-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/pi).

😀 Ai publicat cu succes temperatura ca telemetrie de pe dispozitivul tău.

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa maternă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.