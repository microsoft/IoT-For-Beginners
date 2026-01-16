<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c677667095f6133eee418c7e53615d05",
  "translation_date": "2025-08-25T20:58:14+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/pi-camera.md",
  "language_code": "de"
}
-->
# Ein Bild aufnehmen - Raspberry Pi

In diesem Teil der Lektion fügen Sie Ihrem Raspberry Pi einen Kamerasensor hinzu und lesen Bilder davon aus.

## Hardware

Der Raspberry Pi benötigt eine Kamera.

Die Kamera, die Sie verwenden werden, ist ein [Raspberry Pi Camera Module](https://www.raspberrypi.org/products/camera-module-v2/). Diese Kamera wurde speziell für den Raspberry Pi entwickelt und wird über einen dedizierten Anschluss am Pi verbunden.

> 💁 Diese Kamera verwendet das [Camera Serial Interface, ein Protokoll der Mobile Industry Processor Interface Alliance](https://wikipedia.org/wiki/Camera_Serial_Interface), bekannt als MIPI-CSI. Dies ist ein spezielles Protokoll zur Übertragung von Bildern.

## Kamera anschließen

Die Kamera kann mit einem Flachbandkabel an den Raspberry Pi angeschlossen werden.

### Aufgabe - Kamera anschließen

![Eine Raspberry Pi Kamera](../../../../../translated_images/de/pi-camera-module.4278753c31bd6e757aa2b858be97d72049f71616278cefe4fb5abb485b40a078.png)

1. Schalten Sie den Pi aus.

1. Verbinden Sie das Flachbandkabel, das mit der Kamera geliefert wird, mit der Kamera. Ziehen Sie dazu vorsichtig an dem schwarzen Plastikclip im Halter, sodass er sich ein wenig löst. Schieben Sie dann das Kabel in die Buchse, wobei die blaue Seite vom Objektiv weg zeigt und die Metallkontakte zum Objektiv hin zeigen. Sobald das Kabel vollständig eingesteckt ist, drücken Sie den schwarzen Plastikclip wieder zurück.

    Eine Animation, die zeigt, wie man den Clip öffnet und das Kabel einsteckt, finden Sie in der [Raspberry Pi Dokumentation zum Einstieg mit dem Kameramodul](https://projects.raspberrypi.org/en/projects/getting-started-with-picamera/2).

    ![Das Flachbandkabel in das Kameramodul eingesteckt](../../../../../translated_images/de/pi-camera-ribbon-cable.0bf82acd251611c21ac616f082849413e2b322a261d0e4f8fec344248083b07e.png)

1. Entfernen Sie das Grove Base Hat vom Pi.

1. Führen Sie das Flachbandkabel durch den Kameraschlitz im Grove Base Hat. Achten Sie darauf, dass die blaue Seite des Kabels zu den analogen Ports mit der Beschriftung **A0**, **A1** usw. zeigt.

    ![Das Flachbandkabel durch das Grove Base Hat geführt](../../../../../translated_images/de/grove-base-hat-ribbon-cable.501fed202fcf73b11b2b68f6d246189f7d15d3e4423c572ddee79d77b4632b47.png)

1. Stecken Sie das Flachbandkabel in den Kameraanschluss am Pi. Ziehen Sie erneut den schwarzen Plastikclip hoch, stecken Sie das Kabel ein und drücken Sie den Clip wieder zurück. Die blaue Seite des Kabels sollte zu den USB- und Ethernet-Anschlüssen zeigen.

    ![Das Flachbandkabel am Kameraanschluss des Pi angeschlossen](../../../../../translated_images/de/pi-camera-socket-ribbon-cable.a18309920b11800911082ed7aa6fb28e6d9be3a022e4079ff990016cae3fca10.png)

1. Setzen Sie das Grove Base Hat wieder ein.

## Kamera programmieren

Der Raspberry Pi kann jetzt programmiert werden, um die Kamera mit der [PiCamera](https://pypi.org/project/picamera/) Python-Bibliothek zu verwenden.

### Aufgabe - Legacy-Kameramodus aktivieren

Leider hat sich mit der Veröffentlichung von Raspberry Pi OS Bullseye die Kamerasoftware geändert, die mit dem Betriebssystem geliefert wird. Dadurch funktioniert PiCamera standardmäßig nicht mehr. Es gibt eine Ersatzbibliothek namens PiCamera2, die sich jedoch noch in der Entwicklung befindet und derzeit nicht einsatzbereit ist.

Für den Moment können Sie Ihren Pi in den Legacy-Kameramodus versetzen, um PiCamera zu verwenden. Der Kameraanschluss ist standardmäßig deaktiviert, aber durch das Aktivieren der Legacy-Kamerasoftware wird der Anschluss automatisch aktiviert.

1. Schalten Sie den Pi ein und warten Sie, bis er hochgefahren ist.

1. Starten Sie VS Code, entweder direkt auf dem Pi oder über die Remote SSH-Erweiterung.

1. Führen Sie die folgenden Befehle in Ihrem Terminal aus:

    ```sh
    sudo raspi-config nonint do_legacy 0
    sudo reboot
    ```

    Dies aktiviert eine Einstellung, um die Legacy-Kamerasoftware zu aktivieren, und startet den Pi neu, damit die Einstellung wirksam wird.

1. Warten Sie, bis der Pi neu gestartet ist, und starten Sie dann VS Code erneut.

### Aufgabe - Kamera programmieren

Programmieren Sie das Gerät.

1. Erstellen Sie im Terminal einen neuen Ordner im Home-Verzeichnis des Benutzers `pi` mit dem Namen `fruit-quality-detector`. Erstellen Sie in diesem Ordner eine Datei namens `app.py`.

1. Öffnen Sie diesen Ordner in VS Code.

1. Um mit der Kamera zu interagieren, können Sie die PiCamera Python-Bibliothek verwenden. Installieren Sie das Pip-Paket dafür mit folgendem Befehl:

    ```sh
    pip3 install picamera
    ```

1. Fügen Sie den folgenden Code in Ihre Datei `app.py` ein:

    ```python
    import io
    import time
    from picamera import PiCamera
    ```

    Dieser Code importiert einige benötigte Bibliotheken, einschließlich der `PiCamera`-Bibliothek.

1. Fügen Sie den folgenden Code darunter ein, um die Kamera zu initialisieren:

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    
    time.sleep(2)
    ```

    Dieser Code erstellt ein PiCamera-Objekt und setzt die Auflösung auf 640x480. Obwohl höhere Auflösungen unterstützt werden (bis zu 3280x2464), arbeitet der Bildklassifikator mit viel kleineren Bildern (227x227), sodass es nicht notwendig ist, größere Bilder aufzunehmen und zu senden.

    Die Zeile `camera.rotation = 0` legt die Rotation des Bildes fest. Das Flachbandkabel kommt unten in die Kamera, aber wenn Ihre Kamera gedreht wurde, um besser auf das Objekt zu zeigen, das Sie klassifizieren möchten, können Sie diese Zeile auf die Anzahl der Rotationsgrade ändern.

    ![Die Kamera hängt über einer Getränkedose](../../../../../translated_images/de/pi-camera-upside-down.5376961ba31459883362124152ad6b823d5ac5fc14e85f317e22903bd681c2b6.png)

    Wenn Sie beispielsweise das Flachbandkabel über etwas hängen lassen, sodass es oben an der Kamera ist, setzen Sie die Rotation auf 180:

    ```python
    camera.rotation = 180
    ```

    Die Kamera benötigt einige Sekunden, um zu starten, daher die Zeile `time.sleep(2)`.

1. Fügen Sie den folgenden Code darunter ein, um das Bild als Binärdaten zu erfassen:

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    Dieser Code erstellt ein `BytesIO`-Objekt, um Binärdaten zu speichern. Das Bild wird von der Kamera als JPEG-Datei gelesen und in diesem Objekt gespeichert. Dieses Objekt hat einen Positionsindikator, um zu wissen, wo es sich in den Daten befindet, damit später weitere Daten hinzugefügt werden können. Die Zeile `image.seek(0)` setzt diese Position zurück auf den Anfang, damit alle Daten später gelesen werden können.

1. Fügen Sie darunter den folgenden Code ein, um das Bild in einer Datei zu speichern:

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    Dieser Code öffnet eine Datei namens `image.jpg` zum Schreiben, liest alle Daten aus dem `BytesIO`-Objekt und schreibt diese in die Datei.

    > 💁 Sie können das Bild direkt in einer Datei speichern, anstatt ein `BytesIO`-Objekt zu verwenden, indem Sie den Dateinamen an den `camera.capture`-Aufruf übergeben. Der Grund für die Verwendung des `BytesIO`-Objekts ist, dass Sie später in dieser Lektion das Bild an Ihren Bildklassifikator senden können.

1. Richten Sie die Kamera auf etwas und führen Sie diesen Code aus.

1. Ein Bild wird aufgenommen und als `image.jpg` im aktuellen Ordner gespeichert. Sie sehen diese Datei im VS Code Explorer. Wählen Sie die Datei aus, um das Bild anzuzeigen. Falls es gedreht werden muss, aktualisieren Sie die Zeile `camera.rotation = 0` entsprechend und machen Sie ein neues Foto.

> 💁 Sie finden diesen Code im Ordner [code-camera/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/pi).

😀 Ihr Kameraprogramm war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.