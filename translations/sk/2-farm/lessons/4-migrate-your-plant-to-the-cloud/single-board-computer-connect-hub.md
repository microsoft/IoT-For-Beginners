<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-28T11:24:11+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "sk"
}
-->
# Pripojte svoje IoT zariadenie do cloudu - Virtuálny IoT hardvér a Raspberry Pi

V tejto časti lekcie pripojíte svoje virtuálne IoT zariadenie alebo Raspberry Pi k IoT Hubu, aby ste mohli odosielať telemetriu a prijímať príkazy.

## Pripojenie zariadenia k IoT Hubu

Ďalším krokom je pripojenie vášho zariadenia k IoT Hubu.

### Úloha - pripojenie k IoT Hubu

1. Otvorte priečinok `soil-moisture-sensor` vo VS Code. Uistite sa, že virtuálne prostredie beží v termináli, ak používate virtuálne IoT zariadenie.

1. Nainštalujte niektoré ďalšie balíky Pip:

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` je knižnica na komunikáciu s vaším IoT Hubom.

1. Pridajte nasledujúce importy na začiatok súboru `app.py`, pod existujúce importy:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    Tento kód importuje SDK na komunikáciu s vaším IoT Hubom.

1. Odstráňte riadok `import paho.mqtt.client as mqtt`, pretože táto knižnica už nie je potrebná. Odstráňte všetok kód MQTT vrátane názvov tém, všetok kód, ktorý používa `mqtt_client` a `handle_command`. Zachovajte slučku `while True:`, len odstráňte riadok `mqtt_client.publish` z tejto slučky.

1. Pridajte nasledujúci kód pod importy:

    ```python
    connection_string = "<connection string>"
    ```

    Nahraďte `<connection string>` reťazcom pripojenia, ktorý ste získali pre zariadenie skôr v tejto lekcii.

    > 💁 Toto nie je najlepšia prax. Reťazce pripojenia by nikdy nemali byť uložené v zdrojovom kóde, pretože môžu byť zahrnuté do systému na kontrolu zdrojového kódu a nájdené kýmkoľvek. Robíme to tu kvôli jednoduchosti. Ideálne by ste mali použiť niečo ako premenné prostredia a nástroj ako [`python-dotenv`](https://pypi.org/project/python-dotenv/). Viac sa o tom dozviete v nadchádzajúcej lekcii.

1. Pod tento kód pridajte nasledujúci kód na vytvorenie objektu klienta zariadenia, ktorý môže komunikovať s IoT Hubom, a pripojte ho:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. Spustite tento kód. Uvidíte, že vaše zariadenie sa pripojí.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## Odosielanie telemetrie

Teraz, keď je vaše zariadenie pripojené, môžete odosielať telemetriu do IoT Hubu namiesto MQTT brokeru.

### Úloha - odosielanie telemetrie

1. Pridajte nasledujúci kód do slučky `while True`, tesne pred príkaz sleep:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    Tento kód vytvorí IoT Hub `Message`, ktorý obsahuje hodnotu vlhkosti pôdy ako JSON reťazec, a odošle ho do IoT Hubu ako správu zo zariadenia do cloudu.

## Spracovanie príkazov

Vaše zariadenie musí spracovať príkaz zo serverového kódu na ovládanie relé. Tento príkaz je odoslaný ako požiadavka na priamu metódu.

## Úloha - spracovanie požiadavky na priamu metódu

1. Pridajte nasledujúci kód pred slučku `while True`:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    Tento kód definuje metódu `handle_method_request`, ktorá bude volaná, keď IoT Hub zavolá priamu metódu. Každá priama metóda má názov a tento kód očakáva metódu nazvanú `relay_on` na zapnutie relé a `relay_off` na vypnutie relé.

    > 💁 Toto by mohlo byť implementované aj v jednej požiadavke na priamu metódu, kde by sa požadovaný stav relé odovzdal ako payload, ktorý môže byť odovzdaný s požiadavkou na metódu a dostupný z objektu `request`.

1. Priame metódy vyžadujú odpoveď, ktorá informuje volajúci kód, že boli spracované. Pridajte nasledujúci kód na koniec funkcie `handle_method_request`, aby ste vytvorili odpoveď na požiadavku:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    Tento kód odošle odpoveď na požiadavku na priamu metódu s HTTP status kódom 200 a odošle ju späť do IoT Hubu.

1. Pridajte nasledujúci kód pod definíciu tejto funkcie:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    Tento kód informuje klienta IoT Hubu, aby zavolal funkciu `handle_method_request`, keď je volaná priama metóda.

> 💁 Tento kód nájdete v priečinku [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) alebo [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device).

😀 Program vášho senzora vlhkosti pôdy je pripojený k vášmu IoT Hubu!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho rodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nie sme zodpovední za žiadne nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.