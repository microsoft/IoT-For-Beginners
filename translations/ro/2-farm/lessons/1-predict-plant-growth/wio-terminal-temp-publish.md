<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-28T11:32:08+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "ro"
}
-->
# Publică temperatura - Wio Terminal

În această parte a lecției, vei publica valorile temperaturii detectate de Wio Terminal prin MQTT, astfel încât să poată fi utilizate ulterior pentru a calcula GDD.

## Publică temperatura

Odată ce temperatura a fost citită, aceasta poate fi publicată prin MQTT către un cod 'server' care va citi valorile și le va stoca, pregătite pentru a fi utilizate în calculul GDD. Microcontrolerele nu citesc ora de pe Internet și nu urmăresc timpul cu un ceas în timp real din fabrică; dispozitivul trebuie programat pentru a face acest lucru, presupunând că are hardware-ul necesar.

Pentru a simplifica lucrurile în această lecție, ora nu va fi trimisă împreună cu datele senzorului; în schimb, aceasta poate fi adăugată ulterior de codul serverului când primește mesajele.

### Sarcină

Programează dispozitivul să publice datele despre temperatură.

1. Deschide proiectul `temperature-sensor` pentru Wio Terminal.

1. Repetă pașii pe care i-ai făcut în lecția 4 pentru a te conecta la MQTT și a trimite telemetrie. Vei folosi același broker public Mosquitto.

    Pașii pentru aceasta sunt:

    - Adaugă bibliotecile Seeed WiFi și MQTT în fișierul `.ini`
    - Adaugă fișierul de configurare și codul pentru conectarea la WiFi
    - Adaugă codul pentru conectarea la brokerul MQTT
    - Adaugă codul pentru publicarea telemetriei

    > ⚠️ Consultă [instrucțiunile pentru conectarea la MQTT](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) și [instrucțiunile pentru trimiterea telemetriei](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) din lecția 4, dacă este necesar.

1. Asigură-te că `CLIENT_NAME` din fișierul header `config.h` reflectă acest proiect:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. Pentru telemetrie, în loc să trimiți o valoare de lumină, trimite valoarea temperaturii citită de senzorul DHT într-o proprietate a documentului JSON numită `temperature`, modificând funcția `loop` din `main.cpp`:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. Valoarea temperaturii nu trebuie citită foarte des - nu se va schimba mult într-un timp scurt, așa că setează `delay` în funcția `loop` la 10 minute:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 Funcția `delay` primește timpul în milisecunde, așa că, pentru a face mai ușor de citit, valoarea este transmisă ca rezultat al unui calcul. 1.000ms într-o secundă, 60s într-un minut, deci 10 x (60s într-un minut) x (1.000ms într-o secundă) oferă o întârziere de 10 minute.

1. Încarcă acest cod pe Wio Terminal și folosește monitorul serial pentru a vedea temperatura trimisă către brokerul MQTT.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"temperature":25}
    Sending telemetry {"temperature":25}
    ```

> 💁 Poți găsi acest cod în folderul [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal).

😀 Ai publicat cu succes temperatura ca telemetrie de pe dispozitivul tău.

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să fiți conștienți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.