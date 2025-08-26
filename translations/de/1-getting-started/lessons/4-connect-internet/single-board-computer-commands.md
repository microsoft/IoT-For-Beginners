<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c527ce85d69b1a3875366ec61cbed8aa",
  "translation_date": "2025-08-25T21:54:20+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-commands.md",
  "language_code": "de"
}
-->
# Steuern Sie Ihr Nachtlicht über das Internet - Virtuelle IoT-Hardware und Raspberry Pi

In diesem Teil der Lektion abonnieren Sie Befehle, die von einem MQTT-Broker an Ihren Raspberry Pi oder Ihr virtuelles IoT-Gerät gesendet werden.

## Befehle abonnieren

Der nächste Schritt besteht darin, die vom MQTT-Broker gesendeten Befehle zu abonnieren und darauf zu reagieren.

### Aufgabe

Abonnieren Sie Befehle.

1. Öffnen Sie das Nachtlicht-Projekt in VS Code.

1. Wenn Sie ein virtuelles IoT-Gerät verwenden, stellen Sie sicher, dass das Terminal die virtuelle Umgebung ausführt. Wenn Sie einen Raspberry Pi verwenden, benötigen Sie keine virtuelle Umgebung.

1. Fügen Sie den folgenden Code nach den Definitionen des `client_telemetry_topic` hinzu:

    ```python
    server_command_topic = id + '/commands'
    ```

    Das `server_command_topic` ist das MQTT-Thema, das das Gerät abonniert, um LED-Befehle zu empfangen.

1. Fügen Sie den folgenden Code direkt über der Hauptschleife, nach der Zeile `mqtt_client.loop_start()`, hinzu:

    ```python
    def handle_command(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
        if payload['led_on']:
            led.on()
        else:
            led.off()
    
    mqtt_client.subscribe(server_command_topic)
    mqtt_client.on_message = handle_command
    ```

    Dieser Code definiert eine Funktion, `handle_command`, die eine Nachricht als JSON-Dokument liest und nach dem Wert der Eigenschaft `led_on` sucht. Wenn sie auf `True` gesetzt ist, wird die LED eingeschaltet, andernfalls wird sie ausgeschaltet.

    Der MQTT-Client abonniert das Thema, auf dem der Server Nachrichten senden wird, und legt fest, dass die Funktion `handle_command` aufgerufen wird, wenn eine Nachricht empfangen wird.

    > 💁 Der `on_message`-Handler wird für alle abonnierten Themen aufgerufen. Wenn Sie später Code schreiben, der auf mehrere Themen hört, können Sie das Thema, auf das die Nachricht gesendet wurde, aus dem `message`-Objekt abrufen, das an die Handler-Funktion übergeben wird.

1. Führen Sie den Code auf die gleiche Weise aus wie den Code aus dem vorherigen Teil der Aufgabe. Wenn Sie ein virtuelles IoT-Gerät verwenden, stellen Sie sicher, dass die CounterFit-App ausgeführt wird und der Lichtsensor und die LED an den richtigen Pins erstellt wurden.

1. Passen Sie die Lichtstärken an, die von Ihrem physischen oder virtuellen Gerät erkannt werden. Empfangene Nachrichten und gesendete Befehle werden im Terminal angezeigt. Die LED wird je nach Lichtstärke ein- und ausgeschaltet.

> 💁 Sie finden diesen Code im Ordner [code-commands/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/virtual-device) oder im Ordner [code-commands/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/pi).

😀 Sie haben Ihr Gerät erfolgreich programmiert, um auf Befehle eines MQTT-Brokers zu reagieren.

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.