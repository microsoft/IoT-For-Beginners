<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-28T10:13:01+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "ro"
}
-->
# Controlează-ți lampa de veghe prin Internet - Hardware IoT virtual și Raspberry Pi

În această parte a lecției, vei trimite telemetrie cu nivelurile de lumină de la Raspberry Pi-ul tău sau dispozitivul IoT virtual către un broker MQTT.

## Publică telemetria

Următorul pas este să creezi un document JSON cu telemetria și să-l trimiți către brokerul MQTT.

### Sarcină

Publică telemetria către brokerul MQTT.

1. Deschide proiectul nightlight în VS Code.

1. Dacă folosești un dispozitiv IoT virtual, asigură-te că terminalul rulează mediul virtual. Dacă folosești un Raspberry Pi, nu vei folosi un mediu virtual.

1. Adaugă următorul import în partea de sus a fișierului `app.py`:

    ```python
    import json
    ```

    Biblioteca `json` este utilizată pentru a codifica telemetria ca document JSON.

1. Adaugă următorul cod după declarația `client_name`:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    `client_telemetry_topic` este subiectul MQTT la care dispozitivul va publica nivelurile de lumină.

1. Înlocuiește conținutul buclei `while True:` de la sfârșitul fișierului cu următorul cod:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    Acest cod împachetează nivelul de lumină într-un document JSON și îl publică către brokerul MQTT. Apoi, face o pauză pentru a reduce frecvența cu care sunt trimise mesajele.

1. Rulează codul în același mod în care ai rulat codul din partea anterioară a temei. Dacă folosești un dispozitiv IoT virtual, asigură-te că aplicația CounterFit este pornită și că senzorul de lumină și LED-ul au fost create pe pinii corecți.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 Poți găsi acest cod în folderul [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) sau în folderul [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi).

😀 Ai trimis cu succes telemetria de pe dispozitivul tău.

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.