<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-25T21:46:42+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "de"
}
-->
# Verbinden Sie Ihr IoT-Gerät mit der Cloud - Virtuelle IoT-Hardware und Raspberry Pi

In diesem Abschnitt der Lektion verbinden Sie Ihr virtuelles IoT-Gerät oder Ihren Raspberry Pi mit Ihrem IoT Hub, um Telemetrie zu senden und Befehle zu empfangen.

## Verbinden Sie Ihr Gerät mit dem IoT Hub

Der nächste Schritt besteht darin, Ihr Gerät mit dem IoT Hub zu verbinden.

### Aufgabe - Verbindung zum IoT Hub herstellen

1. Öffnen Sie den Ordner `soil-moisture-sensor` in VS Code. Stellen Sie sicher, dass die virtuelle Umgebung im Terminal läuft, wenn Sie ein virtuelles IoT-Gerät verwenden.

1. Installieren Sie einige zusätzliche Pip-Pakete:

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` ist eine Bibliothek, um mit Ihrem IoT Hub zu kommunizieren.

1. Fügen Sie die folgenden Importe oben in die Datei `app.py` ein, unterhalb der bereits vorhandenen Importe:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    Dieser Code importiert das SDK, um mit Ihrem IoT Hub zu kommunizieren.

1. Entfernen Sie die Zeile `import paho.mqtt.client as mqtt`, da diese Bibliothek nicht mehr benötigt wird. Entfernen Sie den gesamten MQTT-Code einschließlich der Themennamen, aller Codezeilen, die `mqtt_client` verwenden, und der Funktion `handle_command`. Behalten Sie die Schleife `while True:`, löschen Sie jedoch die Zeile `mqtt_client.publish` aus dieser Schleife.

1. Fügen Sie den folgenden Code unterhalb der Import-Anweisungen hinzu:

    ```python
    connection_string = "<connection string>"
    ```

    Ersetzen Sie `<connection string>` durch den Verbindungsstring, den Sie zuvor in dieser Lektion für das Gerät abgerufen haben.

    > 💁 Dies ist keine Best Practice. Verbindungsstrings sollten niemals im Quellcode gespeichert werden, da sie in die Versionskontrolle eingecheckt und von jedem gefunden werden können. Wir machen dies hier der Einfachheit halber. Idealerweise sollten Sie etwas wie eine Umgebungsvariable und ein Tool wie [`python-dotenv`](https://pypi.org/project/python-dotenv/) verwenden. Sie werden mehr darüber in einer kommenden Lektion lernen.

1. Fügen Sie unterhalb dieses Codes Folgendes hinzu, um ein Geräte-Client-Objekt zu erstellen, das mit dem IoT Hub kommunizieren kann, und verbinden Sie es:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. Führen Sie diesen Code aus. Sie werden sehen, wie Ihr Gerät sich verbindet.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## Telemetrie senden

Jetzt, da Ihr Gerät verbunden ist, können Sie Telemetrie an den IoT Hub senden, anstatt an den MQTT-Broker.

### Aufgabe - Telemetrie senden

1. Fügen Sie den folgenden Code in die Schleife `while True` ein, direkt vor die Schlafanweisung:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    Dieser Code erstellt eine IoT Hub `Message`, die die Bodenfeuchtigkeitsmessung als JSON-String enthält, und sendet diese als Gerät-zu-Cloud-Nachricht an den IoT Hub.

## Befehle verarbeiten

Ihr Gerät muss einen Befehl vom Servercode verarbeiten, um das Relais zu steuern. Dies wird als direkte Methodenanforderung gesendet.

## Aufgabe - eine direkte Methodenanforderung verarbeiten

1. Fügen Sie den folgenden Code vor der Schleife `while True` hinzu:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    Dies definiert eine Methode, `handle_method_request`, die aufgerufen wird, wenn eine direkte Methode vom IoT Hub aufgerufen wird. Jede direkte Methode hat einen Namen, und dieser Code erwartet eine Methode namens `relay_on`, um das Relais einzuschalten, und `relay_off`, um das Relais auszuschalten.

    > 💁 Dies könnte auch in einer einzigen direkten Methodenanforderung implementiert werden, indem der gewünschte Zustand des Relais in einer Nutzlast übergeben wird, die mit der Methodenanforderung übergeben und aus dem `request`-Objekt abgerufen werden kann.

1. Direkte Methoden erfordern eine Antwort, um dem aufrufenden Code mitzuteilen, dass sie verarbeitet wurden. Fügen Sie den folgenden Code am Ende der Funktion `handle_method_request` hinzu, um eine Antwort auf die Anfrage zu erstellen:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    Dieser Code sendet eine Antwort auf die direkte Methodenanforderung mit einem HTTP-Statuscode von 200 und sendet diese zurück an den IoT Hub.

1. Fügen Sie den folgenden Code unterhalb dieser Funktionsdefinition hinzu:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    Dieser Code weist den IoT Hub-Client an, die Funktion `handle_method_request` aufzurufen, wenn eine direkte Methode aufgerufen wird.

> 💁 Sie finden diesen Code im Ordner [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) oder [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device).

😀 Ihr Bodenfeuchtigkeitssensor-Programm ist mit Ihrem IoT Hub verbunden!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.