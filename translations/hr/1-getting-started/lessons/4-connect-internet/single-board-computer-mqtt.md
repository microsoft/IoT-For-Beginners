<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "90fb93446e03c38f3c0e4009c2471906",
  "translation_date": "2025-08-28T13:53:58+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md",
  "language_code": "hr"
}
-->
# Kontrolirajte svoju noćnu lampu putem Interneta - Virtualni IoT uređaj i Raspberry Pi

IoT uređaj treba biti programiran da komunicira s *test.mosquitto.org* koristeći MQTT za slanje telemetrijskih vrijednosti očitanja senzora svjetla i primanje naredbi za upravljanje LED-om.

U ovom dijelu lekcije povezat ćete svoj Raspberry Pi ili virtualni IoT uređaj s MQTT brokerom.

## Instalirajte MQTT klijentski paket

Za komunikaciju s MQTT brokerom potrebno je instalirati MQTT knjižnicu putem pip paketa, bilo na vašem Raspberry Pi-ju ili u virtualnom okruženju ako koristite virtualni uređaj.

### Zadatak

Instalirajte pip paket

1. Otvorite projekt noćne lampe u VS Code-u.

1. Ako koristite virtualni IoT uređaj, provjerite je li terminal pokrenut u virtualnom okruženju. Ako koristite Raspberry Pi, nećete koristiti virtualno okruženje.

1. Pokrenite sljedeću naredbu za instalaciju MQTT pip paketa:

    ```sh
    pip3 install paho-mqtt
    ```

## Programirajte uređaj

Uređaj je spreman za programiranje.

### Zadatak

Napišite kod za uređaj.

1. Dodajte sljedeći uvoz na vrh datoteke `app.py`:

    ```python
    import paho.mqtt.client as mqtt
    ```

    Knjižnica `paho.mqtt.client` omogućuje vašoj aplikaciji komunikaciju putem MQTT-a.

1. Dodajte sljedeći kod nakon definicija senzora svjetla i LED-a:

    ```python
    id = '<ID>'

    client_name = id + 'nightlight_client'
    ```

    Zamijenite `<ID>` jedinstvenim ID-om koji će se koristiti kao naziv ovog klijenta uređaja, a kasnije i za teme koje ovaj uređaj objavljuje i na koje se pretplaćuje. Broker *test.mosquitto.org* je javni i koristi ga mnogo ljudi, uključujući druge studente koji rade na ovom zadatku. Imati jedinstveno ime MQTT klijenta i nazive tema osigurava da vaš kod neće doći u sukob s kodom drugih korisnika. Također će vam trebati ovaj ID kada budete kreirali kod za server kasnije u ovom zadatku.

    > 💁 Možete koristiti web stranicu poput [GUIDGen](https://www.guidgen.com) za generiranje jedinstvenog ID-a.

    `client_name` je jedinstveno ime za ovog MQTT klijenta na brokeru.

1. Dodajte sljedeći kod ispod ovog novog koda za kreiranje MQTT klijentskog objekta i povezivanje s MQTT brokerom:

    ```python
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()

    print("MQTT connected!")
    ```

    Ovaj kod kreira klijentski objekt, povezuje se s javnim MQTT brokerom i pokreće procesnu petlju koja radi u pozadinskoj niti, slušajući poruke na svim pretplaćenim temama.

1. Pokrenite kod na isti način kao što ste pokrenuli kod iz prethodnog dijela zadatka. Ako koristite virtualni IoT uređaj, provjerite je li aplikacija CounterFit pokrenuta i jesu li senzor svjetla i LED kreirani na odgovarajućim pinovima.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Light level: 0
    Light level: 0
    ```

> 💁 Ovaj kod možete pronaći u mapi [code-mqtt/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/virtual-device) ili mapi [code-mqtt/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/pi).

😀 Uspješno ste povezali svoj uređaj s MQTT brokerom.

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za bilo kakva nesporazuma ili pogrešna tumačenja koja proizlaze iz korištenja ovog prijevoda.