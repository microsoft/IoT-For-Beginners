<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-28T11:24:30+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "ro"
}
-->
# Conectează dispozitivul IoT la cloud - Hardware IoT virtual și Raspberry Pi

În această parte a lecției, vei conecta dispozitivul tău IoT virtual sau Raspberry Pi la IoT Hub, pentru a trimite telemetrie și a primi comenzi.

## Conectează dispozitivul la IoT Hub

Următorul pas este să conectezi dispozitivul la IoT Hub.

### Sarcină - conectează-te la IoT Hub

1. Deschide folderul `soil-moisture-sensor` în VS Code. Asigură-te că mediul virtual rulează în terminal dacă folosești un dispozitiv IoT virtual.

1. Instalează câteva pachete suplimentare Pip:

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` este o bibliotecă pentru a comunica cu IoT Hub.

1. Adaugă următoarele importuri în partea de sus a fișierului `app.py`, sub importurile existente:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    Acest cod importă SDK-ul pentru a comunica cu IoT Hub.

1. Elimină linia `import paho.mqtt.client as mqtt`, deoarece această bibliotecă nu mai este necesară. Elimină tot codul MQTT, inclusiv numele topicurilor, tot codul care folosește `mqtt_client` și `handle_command`. Păstrează bucla `while True:`, doar șterge linia `mqtt_client.publish` din această buclă.

1. Adaugă următorul cod sub declarațiile de import:

    ```python
    connection_string = "<connection string>"
    ```

    Înlocuiește `<connection string>` cu șirul de conexiune pe care l-ai obținut pentru dispozitiv mai devreme în această lecție.

    > 💁 Acesta nu este o practică recomandată. Șirurile de conexiune nu ar trebui niciodată stocate în codul sursă, deoarece pot fi introduse în controlul versiunilor și găsite de oricine. Facem acest lucru aici pentru simplitate. Ideal ar fi să folosești ceva precum o variabilă de mediu și un instrument precum [`python-dotenv`](https://pypi.org/project/python-dotenv/). Vei învăța mai multe despre acest lucru într-o lecție viitoare.

1. Sub acest cod, adaugă următorul cod pentru a crea un obiect client al dispozitivului care poate comunica cu IoT Hub și pentru a-l conecta:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. Rulează acest cod. Vei vedea cum dispozitivul tău se conectează.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## Trimite telemetrie

Acum că dispozitivul tău este conectat, poți trimite telemetrie către IoT Hub în loc de brokerul MQTT.

### Sarcină - trimite telemetrie

1. Adaugă următorul cod în interiorul buclei `while True`, chiar înainte de funcția de pauză (`sleep`):

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    Acest cod creează un `Message` IoT Hub care conține citirea umidității solului sub formă de șir JSON, apoi îl trimite către IoT Hub ca un mesaj de la dispozitiv la cloud.

## Gestionează comenzile

Dispozitivul tău trebuie să gestioneze o comandă de la codul serverului pentru a controla releul. Aceasta este trimisă ca o cerere de metodă directă.

## Sarcină - gestionează o cerere de metodă directă

1. Adaugă următorul cod înainte de bucla `while True`:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    Acesta definește o metodă, `handle_method_request`, care va fi apelată atunci când o metodă directă este apelată de IoT Hub. Fiecare metodă directă are un nume, iar acest cod așteaptă o metodă numită `relay_on` pentru a porni releul și `relay_off` pentru a opri releul.

    > 💁 Acest lucru ar putea fi implementat și într-o singură cerere de metodă directă, transmițând starea dorită a releului într-un payload care poate fi transmis cu cererea de metodă și disponibil din obiectul `request`.

1. Metodele directe necesită un răspuns pentru a informa codul apelant că au fost gestionate. Adaugă următorul cod la sfârșitul funcției `handle_method_request` pentru a crea un răspuns la cerere:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    Acest cod trimite un răspuns la cererea de metodă directă cu un cod de stare HTTP 200 și îl trimite înapoi la IoT Hub.

1. Adaugă următorul cod sub definiția acestei funcții:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    Acest cod spune clientului IoT Hub să apeleze funcția `handle_method_request` atunci când o metodă directă este apelată.

> 💁 Poți găsi acest cod în folderul [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) sau [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device).

😀 Programul senzorului de umiditate a solului este conectat la IoT Hub!

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să fiți conștienți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de oameni. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.