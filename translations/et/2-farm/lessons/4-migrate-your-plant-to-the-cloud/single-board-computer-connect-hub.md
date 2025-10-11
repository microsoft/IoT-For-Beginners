<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-10-11T12:32:16+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "et"
}
-->
# Ühenda oma IoT-seade pilvega - Virtuaalne IoT-riistvara ja Raspberry Pi

Selles õppetunni osas ühendad oma virtuaalse IoT-seadme või Raspberry Pi oma IoT Hubiga, et saata telemeetriat ja vastu võtta käske.

## Ühenda oma seade IoT Hubiga

Järgmine samm on ühendada oma seade IoT Hubiga.

### Ülesanne - ühendamine IoT Hubiga

1. Ava `soil-moisture-sensor` kaust VS Code'is. Veendu, et virtuaalne keskkond töötab terminalis, kui kasutad virtuaalset IoT-seadet.

1. Paigalda mõned täiendavad Pip-paketid:

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` on teek, mis võimaldab suhelda IoT Hubiga.

1. Lisa järgmised impordid `app.py` faili ülaossa, olemasolevate importide alla:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    See kood impordib SDK, et suhelda IoT Hubiga.

1. Eemalda rida `import paho.mqtt.client as mqtt`, kuna seda teeki pole enam vaja. Eemalda kogu MQTT-kood, sealhulgas teemanimed, kogu kood, mis kasutab `mqtt_client` ja `handle_command`. Jäta alles `while True:` tsükkel, kuid kustuta selle tsükli seest rida `mqtt_client.publish`.

1. Lisa järgmine kood importide alla:

    ```python
    connection_string = "<connection string>"
    ```

    Asenda `<connection string>` ühenduse stringiga, mille sa varem selles õppetunnis seadme jaoks hankisid.

    > 💁 See ei ole parim praktika. Ühenduse stringe ei tohiks kunagi salvestada lähtekoodi, kuna need võivad sattuda versioonihaldusse ja olla kättesaadavad kõigile. Me teeme seda siin lihtsuse huvides. Ideaalis peaksid kasutama midagi sellist nagu keskkonnamuutuja ja tööriista nagu [`python-dotenv`](https://pypi.org/project/python-dotenv/). Sa õpid sellest rohkem tulevases õppetunnis.

1. Lisa selle koodi alla järgmine, et luua seadme kliendi objekt, mis saab IoT Hubiga suhelda, ja ühenda see:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. Käivita see kood. Näed, kuidas su seade ühendub.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## Telemeetria saatmine

Nüüd, kui su seade on ühendatud, saad saata telemeetriat IoT Hubi asemel MQTT-brokerile.

### Ülesanne - telemeetria saatmine

1. Lisa järgmine kood `while True` tsükli sisse, vahetult enne `sleep`-i:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    See kood loob IoT Hubi `Message` objekti, mis sisaldab mulla niiskuse näitu JSON-stringina, ja saadab selle IoT Hubi seadme-pilve sõnumina.

## Käskude käsitlemine

Su seade peab käsitlema serveri koodi käsku, et juhtida releed. See saadetakse otsese meetodi päringuna.

## Ülesanne - otsese meetodi päringu käsitlemine

1. Lisa järgmine kood enne `while True` tsüklit:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    See määratleb meetodi `handle_method_request`, mida kutsutakse, kui IoT Hub kutsub otsest meetodit. Igal otsesel meetodil on nimi, ja see kood ootab meetodit nimega `relay_on`, et relee sisse lülitada, ja `relay_off`, et relee välja lülitada.

    > 💁 Seda võiks rakendada ka ühe otsese meetodi päringuna, edastades soovitud relee oleku koormuses, mida saab päringuga kaasa anda ja mis on saadaval `request` objektist.

1. Otsesed meetodid vajavad vastust, et teavitada kutsuvat koodi, et need on käsitletud. Lisa järgmine kood `handle_method_request` funktsiooni lõppu, et luua päringule vastus:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    See kood saadab otsese meetodi päringule vastuse HTTP staatusekoodiga 200 ja edastab selle tagasi IoT Hubile.

1. Lisa järgmine kood selle funktsiooni definitsiooni alla:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    See kood ütleb IoT Hubi kliendile, et kutsuda `handle_method_request` funktsiooni, kui otsest meetodit kutsutakse.

> 💁 Selle koodi leiad [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) või [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device) kaustast.

😀 Su mulla niiskuse sensori programm on ühendatud IoT Hubiga!

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.