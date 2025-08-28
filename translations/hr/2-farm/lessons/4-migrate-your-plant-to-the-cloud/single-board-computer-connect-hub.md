<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-28T15:03:28+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "hr"
}
-->
# Povežite svoj IoT uređaj s oblakom - Virtualni IoT hardver i Raspberry Pi

U ovom dijelu lekcije, povezat ćete svoj virtualni IoT uređaj ili Raspberry Pi s IoT Hubom kako biste slali telemetriju i primali naredbe.

## Povežite svoj uređaj s IoT Hubom

Sljedeći korak je povezivanje vašeg uređaja s IoT Hubom.

### Zadatak - povezivanje s IoT Hubom

1. Otvorite mapu `soil-moisture-sensor` u VS Codeu. Provjerite je li virtualno okruženje pokrenuto u terminalu ako koristite virtualni IoT uređaj.

1. Instalirajte dodatne Pip pakete:

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` je biblioteka za komunikaciju s vašim IoT Hubom.

1. Dodajte sljedeće uvoze na vrh datoteke `app.py`, ispod postojećih uvoza:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    Ovaj kod uvozi SDK za komunikaciju s vašim IoT Hubom.

1. Uklonite liniju `import paho.mqtt.client as mqtt` jer ova biblioteka više nije potrebna. Uklonite sav MQTT kod, uključujući nazive tema, sav kod koji koristi `mqtt_client` i `handle_command`. Zadržite petlju `while True:`, samo izbrišite liniju `mqtt_client.publish` iz ove petlje.

1. Dodajte sljedeći kod ispod uvoznih izjava:

    ```python
    connection_string = "<connection string>"
    ```

    Zamijenite `<connection string>` s nizom za povezivanje koji ste ranije dobili za uređaj u ovoj lekciji.

    > 💁 Ovo nije najbolja praksa. Nizovi za povezivanje nikada ne bi trebali biti pohranjeni u izvornom kodu, jer se mogu dodati u kontrolu izvornog koda i pronaći ih bilo tko. Ovo radimo ovdje radi jednostavnosti. Idealno bi bilo koristiti nešto poput varijable okruženja i alat poput [`python-dotenv`](https://pypi.org/project/python-dotenv/). Više o tome naučit ćete u nadolazećoj lekciji.

1. Ispod ovog koda dodajte sljedeće kako biste stvorili objekt klijenta uređaja koji može komunicirati s IoT Hubom i povezati ga:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. Pokrenite ovaj kod. Vidjet ćete da se vaš uređaj povezuje.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## Slanje telemetrije

Sada kada je vaš uređaj povezan, možete slati telemetriju IoT Hubu umjesto MQTT brokeru.

### Zadatak - slanje telemetrije

1. Dodajte sljedeći kod unutar petlje `while True`, neposredno prije spavanja:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    Ovaj kod stvara IoT Hub `Message` koji sadrži očitanje vlažnosti tla kao JSON string, a zatim ga šalje IoT Hubu kao poruku od uređaja prema oblaku.

## Obrada naredbi

Vaš uređaj treba obraditi naredbu od poslužiteljskog koda za upravljanje relejem. Ovo se šalje kao zahtjev za direktnu metodu.

## Zadatak - obrada zahtjeva za direktnu metodu

1. Dodajte sljedeći kod prije petlje `while True`:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    Ovo definira metodu `handle_method_request` koja će se pozvati kada IoT Hub pozove direktnu metodu. Svaka direktna metoda ima ime, a ovaj kod očekuje metodu nazvanu `relay_on` za uključivanje releja i `relay_off` za isključivanje releja.

    > 💁 Ovo bi se također moglo implementirati u jednoj direktnoj metodi, prosljeđujući željeno stanje releja u payload koji se može proslijediti sa zahtjevom metode i biti dostupan iz objekta `request`.

1. Direktne metode zahtijevaju odgovor kako bi obavijestile pozivajući kod da su obrađene. Dodajte sljedeći kod na kraj funkcije `handle_method_request` kako biste stvorili odgovor na zahtjev:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    Ovaj kod šalje odgovor na zahtjev za direktnu metodu s HTTP statusnim kodom 200 i šalje ga natrag IoT Hubu.

1. Dodajte sljedeći kod ispod definicije ove funkcije:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    Ovaj kod govori IoT Hub klijentu da pozove funkciju `handle_method_request` kada se pozove direktna metoda.

> 💁 Ovaj kod možete pronaći u mapi [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) ili [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device).

😀 Vaš program senzora vlažnosti tla povezan je s vašim IoT Hubom!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za bilo kakva nesporazuma ili pogrešna tumačenja koja proizlaze iz korištenja ovog prijevoda.