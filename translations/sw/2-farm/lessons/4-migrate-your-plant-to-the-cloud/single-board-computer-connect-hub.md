<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-27T23:12:18+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "sw"
}
-->
# Unganisha kifaa chako cha IoT na wingu - Vifaa vya IoT vya Kijumla na Raspberry Pi

Katika sehemu hii ya somo, utaunganisha kifaa chako cha IoT cha kijumla au Raspberry Pi na IoT Hub yako, ili kutuma telemetry na kupokea amri.

## Unganisha kifaa chako na IoT Hub

Hatua inayofuata ni kuunganisha kifaa chako na IoT Hub.

### Kazi - Unganisha na IoT Hub

1. Fungua folda ya `soil-moisture-sensor` kwenye VS Code. Hakikisha mazingira ya kijumla yanafanya kazi kwenye terminal ikiwa unatumia kifaa cha IoT cha kijumla.

1. Sakinisha baadhi ya pakiti za ziada za Pip:

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` ni maktaba ya kuwasiliana na IoT Hub yako.

1. Ongeza uingizaji ufuatao juu ya faili ya `app.py`, chini ya uingizaji uliopo:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    Msimbo huu unaingiza SDK ya kuwasiliana na IoT Hub yako.

1. Ondoa mstari wa `import paho.mqtt.client as mqtt` kwani maktaba hii haitahitajika tena. Ondoa msimbo wote wa MQTT ikiwa ni pamoja na majina ya mada, msimbo wote unaotumia `mqtt_client` na `handle_command`. Weka kitanzi cha `while True:`, lakini futa mstari wa `mqtt_client.publish` kutoka kwenye kitanzi hiki.

1. Ongeza msimbo ufuatao chini ya taarifa za uingizaji:

    ```python
    connection_string = "<connection string>"
    ```

    Badilisha `<connection string>` na kamba ya muunganisho uliyoipata kwa kifaa mapema katika somo hili.

    > 💁 Hii si mbinu bora. Kamba za muunganisho hazipaswi kuhifadhiwa kwenye msimbo wa chanzo, kwani zinaweza kuingizwa kwenye udhibiti wa msimbo wa chanzo na kupatikana na yeyote. Tunafanya hivi hapa kwa urahisi. Kwa kawaida unapaswa kutumia kitu kama variable ya mazingira na zana kama [`python-dotenv`](https://pypi.org/project/python-dotenv/). Utajifunza zaidi kuhusu hili katika somo lijalo.

1. Chini ya msimbo huu, ongeza yafuatayo ili kuunda kitu cha mteja wa kifaa kinachoweza kuwasiliana na IoT Hub, na kuunganisha:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. Endesha msimbo huu. Utaona kifaa chako kimeunganishwa.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## Tuma telemetry

Sasa kifaa chako kimeunganishwa, unaweza kutuma telemetry kwa IoT Hub badala ya MQTT broker.

### Kazi - Tuma telemetry

1. Ongeza msimbo ufuatao ndani ya kitanzi cha `while True`, kabla tu ya kulala:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    Msimbo huu unaunda `Message` ya IoT Hub inayojumuisha usomaji wa unyevu wa udongo kama kamba ya JSON, kisha inaituma kwa IoT Hub kama ujumbe wa kifaa kwenda wingu.

## Shughulikia amri

Kifaa chako kinahitaji kushughulikia amri kutoka kwa msimbo wa seva ili kudhibiti relay. Hii inatumwa kama ombi la mbinu ya moja kwa moja.

## Kazi - Shughulikia ombi la mbinu ya moja kwa moja

1. Ongeza msimbo ufuatao kabla ya kitanzi cha `while True`:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    Hii inafafanua mbinu, `handle_method_request`, ambayo itaitwa wakati mbinu ya moja kwa moja inaitwa na IoT Hub. Kila mbinu ya moja kwa moja ina jina, na msimbo huu unatarajia mbinu inayoitwa `relay_on` kuwasha relay, na `relay_off` kuzima relay.

    > 💁 Hii pia inaweza kutekelezwa katika ombi moja la mbinu ya moja kwa moja, kwa kupitisha hali inayotakiwa ya relay katika mzigo ambao unaweza kupitishwa na ombi la mbinu na kupatikana kutoka kwa kitu cha `request`.

1. Mbinu za moja kwa moja zinahitaji majibu ili kuambia msimbo unaoitwa kwamba zimeshughulikiwa. Ongeza msimbo ufuatao mwishoni mwa kazi ya `handle_method_request` ili kuunda jibu kwa ombi:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    Msimbo huu unatuma jibu kwa ombi la mbinu ya moja kwa moja na msimbo wa hali ya HTTP wa 200, na kuutuma tena kwa IoT Hub.

1. Ongeza msimbo ufuatao chini ya ufafanuzi wa kazi hii:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    Msimbo huu unaiambia mteja wa IoT Hub kuita kazi ya `handle_method_request` wakati mbinu ya moja kwa moja inaitwa.

> 💁 Unaweza kupata msimbo huu katika folda ya [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) au [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device).

😀 Programu yako ya sensor ya unyevu wa udongo imeunganishwa na IoT Hub yako!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.