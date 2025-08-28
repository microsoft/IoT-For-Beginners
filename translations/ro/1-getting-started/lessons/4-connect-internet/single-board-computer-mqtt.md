<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "90fb93446e03c38f3c0e4009c2471906",
  "translation_date": "2025-08-28T10:14:57+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md",
  "language_code": "ro"
}
-->
# Controlează-ți lampa de veghe prin Internet - Hardware IoT Virtual și Raspberry Pi

Dispozitivul IoT trebuie să fie programat pentru a comunica cu *test.mosquitto.org* folosind MQTT, pentru a trimite valori de telemetrie cu citirea senzorului de lumină și pentru a primi comenzi pentru a controla LED-ul.

În această parte a lecției, vei conecta Raspberry Pi-ul sau dispozitivul tău IoT virtual la un broker MQTT.

## Instalează pachetul client MQTT

Pentru a comunica cu brokerul MQTT, trebuie să instalezi un pachet pip pentru biblioteca MQTT, fie pe Raspberry Pi, fie în mediul tău virtual, dacă folosești un dispozitiv virtual.

### Sarcină

Instalează pachetul pip

1. Deschide proiectul nightlight în VS Code.

1. Dacă folosești un dispozitiv IoT virtual, asigură-te că terminalul rulează mediul virtual. Dacă folosești un Raspberry Pi, nu vei folosi un mediu virtual.

1. Rulează următoarea comandă pentru a instala pachetul pip MQTT:

    ```sh
    pip3 install paho-mqtt
    ```

## Programează dispozitivul

Dispozitivul este pregătit pentru a fi programat.

### Sarcină

Scrie codul dispozitivului.

1. Adaugă următorul import în partea de sus a fișierului `app.py`:

    ```python
    import paho.mqtt.client as mqtt
    ```

    Biblioteca `paho.mqtt.client` permite aplicației tale să comunice prin MQTT.

1. Adaugă următorul cod după definițiile senzorului de lumină și ale LED-ului:

    ```python
    id = '<ID>'

    client_name = id + 'nightlight_client'
    ```

    Înlocuiește `<ID>` cu un ID unic care va fi folosit ca nume al acestui client dispozitiv și, mai târziu, pentru subiectele pe care acest dispozitiv le publică și la care se abonează. Brokerul *test.mosquitto.org* este public și utilizat de mulți oameni, inclusiv de alți studenți care lucrează la această temă. Alegerea unui nume unic pentru clientul MQTT și pentru subiecte asigură că codul tău nu va intra în conflict cu al altora. Vei avea nevoie de acest ID și atunci când creezi codul serverului mai târziu în această temă.

    > 💁 Poți folosi un site precum [GUIDGen](https://www.guidgen.com) pentru a genera un ID unic.

    `client_name` este un nume unic pentru acest client MQTT pe broker.

1. Adaugă următorul cod sub acest nou cod pentru a crea un obiect client MQTT și pentru a te conecta la brokerul MQTT:

    ```python
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()

    print("MQTT connected!")
    ```

    Acest cod creează obiectul client, se conectează la brokerul MQTT public și pornește un ciclu de procesare care rulează într-un fir de execuție în fundal, ascultând mesajele de pe orice subiecte la care s-a abonat.

1. Rulează codul în același mod în care ai rulat codul din partea anterioară a temei. Dacă folosești un dispozitiv IoT virtual, asigură-te că aplicația CounterFit rulează și că senzorul de lumină și LED-ul au fost create pe pinii corecți.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Light level: 0
    Light level: 0
    ```

> 💁 Poți găsi acest cod în folderul [code-mqtt/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/virtual-device) sau în folderul [code-mqtt/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/pi).

😀 Ai conectat cu succes dispozitivul tău la un broker MQTT.

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să fiți conștienți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.