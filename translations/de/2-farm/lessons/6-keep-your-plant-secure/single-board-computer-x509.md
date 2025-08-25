<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9aea84bcc7520222b0e1c50469d62d6a",
  "translation_date": "2025-08-25T21:52:41+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/single-board-computer-x509.md",
  "language_code": "de"
}
-->
# Verwenden Sie das X.509-Zertifikat in Ihrem Gerätecode - Virtuelle IoT-Hardware und Raspberry Pi

In diesem Teil der Lektion verbinden Sie Ihr virtuelles IoT-Gerät oder Ihren Raspberry Pi mit Ihrem IoT Hub unter Verwendung des X.509-Zertifikats.

## Verbinden Sie Ihr Gerät mit dem IoT Hub

Der nächste Schritt besteht darin, Ihr Gerät mithilfe der X.509-Zertifikate mit dem IoT Hub zu verbinden.

### Aufgabe - Verbindung mit dem IoT Hub herstellen

1. Kopieren Sie die Schlüssel- und Zertifikatsdateien in den Ordner, der Ihren IoT-Gerätecode enthält. Wenn Sie einen Raspberry Pi über VS Code Remote SSH verwenden und die Schlüssel auf Ihrem PC oder Mac erstellt haben, können Sie die Dateien per Drag-and-Drop in den Explorer in VS Code ziehen, um sie zu kopieren.

1. Öffnen Sie die Datei `app.py`.

1. Um sich mit einem X.509-Zertifikat zu verbinden, benötigen Sie den Hostnamen des IoT Hubs und das X.509-Zertifikat. Beginnen Sie damit, eine Variable zu erstellen, die den Hostnamen enthält, indem Sie den folgenden Code vor der Erstellung des Geräteclients hinzufügen:

    ```python
    host_name = "<host_name>"
    ```

    Ersetzen Sie `<host_name>` durch den Hostnamen Ihres IoT Hubs. Sie finden diesen im Abschnitt `HostName` der `connection_string`. Es wird der Name Ihres IoT Hubs sein, der mit `.azure-devices.net` endet.

1. Deklarieren Sie darunter eine Variable mit der Geräte-ID:

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. Sie benötigen eine Instanz der `X509`-Klasse, die die X.509-Dateien enthält. Fügen Sie `X509` zur Liste der Klassen hinzu, die aus dem Modul `azure.iot.device` importiert werden:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. Erstellen Sie eine Instanz der `X509`-Klasse mit Ihren Zertifikats- und Schlüsseldateien, indem Sie diesen Code unter der Deklaration von `host_name` hinzufügen:

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    Dies erstellt die `X509`-Klasse unter Verwendung der Dateien `soil-moisture-sensor-x509-cert.pem` und `soil-moisture-sensor-x509-key.pem`, die zuvor erstellt wurden.

1. Ersetzen Sie die Codezeile, die den `device_client` aus einer Verbindungszeichenfolge erstellt, durch Folgendes:

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    Dadurch wird die Verbindung mithilfe des X.509-Zertifikats anstelle einer Verbindungszeichenfolge hergestellt.

1. Löschen Sie die Zeile mit der `connection_string`-Variable.

1. Führen Sie Ihren Code aus. Überwachen Sie die Nachrichten, die an den IoT Hub gesendet werden, und senden Sie wie zuvor direkte Methodenanforderungen. Sie werden sehen, wie das Gerät sich verbindet, Bodenfeuchtigkeitswerte sendet und direkte Methodenanforderungen empfängt.

> 💁 Sie finden diesen Code im Ordner [code/pi](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/pi) oder [code/virtual-device](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/virtual-device).

😀 Ihr Bodenfeuchtigkeitssensor-Programm ist jetzt mit Ihrem IoT Hub über ein X.509-Zertifikat verbunden!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.