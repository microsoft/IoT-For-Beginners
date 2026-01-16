<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e45d884493c5222348b43fbc4481b6a",
  "translation_date": "2025-08-25T22:49:36+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-microphone.md",
  "language_code": "de"
}
-->
# Konfigurieren Sie Ihr Mikrofon und Ihre Lautsprecher - Raspberry Pi

In diesem Teil der Lektion fügen Sie ein Mikrofon und Lautsprecher zu Ihrem Raspberry Pi hinzu.

## Hardware

Der Raspberry Pi benötigt ein Mikrofon.

Der Pi hat kein eingebautes Mikrofon, daher müssen Sie ein externes Mikrofon hinzufügen. Es gibt mehrere Möglichkeiten, dies zu tun:

* USB-Mikrofon
* USB-Headset
* USB-All-in-One-Freisprecheinrichtung
* USB-Audioadapter und Mikrofon mit 3,5-mm-Klinkenanschluss
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)

> 💁 Bluetooth-Mikrofone werden nicht alle vom Raspberry Pi unterstützt. Wenn Sie ein Bluetooth-Mikrofon oder -Headset haben, können Probleme beim Koppeln oder Erfassen von Audio auftreten.

Raspberry Pis verfügen über einen 3,5-mm-Kopfhöreranschluss. Sie können diesen verwenden, um Kopfhörer, ein Headset oder einen Lautsprecher anzuschließen. Alternativ können Sie Lautsprecher hinzufügen über:

* HDMI-Audio über einen Monitor oder Fernseher
* USB-Lautsprecher
* USB-Headset
* USB-All-in-One-Freisprecheinrichtung
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) mit einem angeschlossenen Lautsprecher, entweder über den 3,5-mm-Klinkenanschluss oder den JST-Port

## Mikrofon und Lautsprecher anschließen und konfigurieren

Das Mikrofon und die Lautsprecher müssen angeschlossen und konfiguriert werden.

### Aufgabe - Mikrofon anschließen und konfigurieren

1. Schließen Sie das Mikrofon mit der entsprechenden Methode an. Zum Beispiel über einen der USB-Anschlüsse.

1. Wenn Sie das ReSpeaker 2-Mics Pi HAT verwenden, können Sie die Grove-Basisplatine entfernen und das ReSpeaker-HAT an deren Stelle einsetzen.

    ![Ein Raspberry Pi mit einem ReSpeaker-HAT](../../../../../translated_images/de/pi-respeaker-hat.f00fabe7dd039a93e2e0aa0fc946c9af0c6a9eb17c32fa1ca097fb4e384f69f0.png)

    Später in dieser Lektion benötigen Sie einen Grove-Button, aber einer ist bereits in diesem HAT integriert, sodass die Grove-Basisplatine nicht erforderlich ist.

    Sobald das HAT angebracht ist, müssen Sie einige Treiber installieren. Lesen Sie die [Seeed-Anleitung für den Einstieg](https://wiki.seeedstudio.com/ReSpeaker_2_Mics_Pi_HAT_Raspberry/#getting-started) für Anweisungen zur Treiberinstallation.

    > ⚠️ Die Anleitung verwendet `git`, um ein Repository zu klonen. Falls `git` nicht auf Ihrem Pi installiert ist, können Sie es mit folgendem Befehl installieren:
    >
    > ```sh
    > sudo apt install git --yes
    > ```

1. Führen Sie den folgenden Befehl in Ihrem Terminal aus, entweder direkt auf dem Pi oder über eine Remote-SSH-Sitzung mit VS Code, um Informationen über das angeschlossene Mikrofon zu sehen:

    ```sh
    arecord -l
    ```

    Sie sehen eine Liste der angeschlossenen Mikrofone. Diese könnte etwa so aussehen:

    ```output
    pi@raspberrypi:~ $ arecord -l
    **** List of CAPTURE Hardware Devices ****
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    Wenn Sie nur ein Mikrofon haben, sollte nur ein Eintrag angezeigt werden. Die Konfiguration von Mikrofonen kann unter Linux kompliziert sein, daher ist es am einfachsten, nur ein Mikrofon zu verwenden und andere zu entfernen.

    Notieren Sie sich die Kartennummer, da Sie diese später benötigen. Im obigen Beispiel ist die Kartennummer 1.

### Aufgabe - Lautsprecher anschließen und konfigurieren

1. Schließen Sie die Lautsprecher mit der entsprechenden Methode an.

1. Führen Sie den folgenden Befehl in Ihrem Terminal aus, entweder direkt auf dem Pi oder über eine Remote-SSH-Sitzung mit VS Code, um Informationen über die angeschlossenen Lautsprecher zu sehen:

    ```sh
    aplay -l
    ```

    Sie sehen eine Liste der angeschlossenen Lautsprecher. Diese könnte etwa so aussehen:

    ```output
    pi@raspberrypi:~ $ aplay -l
    **** List of PLAYBACK Hardware Devices ****
    card 0: Headphones [bcm2835 Headphones], device 0: bcm2835 Headphones [bcm2835 Headphones]
      Subdevices: 8/8
      Subdevice #0: subdevice #0
      Subdevice #1: subdevice #1
      Subdevice #2: subdevice #2
      Subdevice #3: subdevice #3
      Subdevice #4: subdevice #4
      Subdevice #5: subdevice #5
      Subdevice #6: subdevice #6
      Subdevice #7: subdevice #7
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    Sie werden immer `card 0: Headphones` sehen, da dies der eingebaute Kopfhöreranschluss ist. Wenn Sie zusätzliche Lautsprecher, wie z. B. einen USB-Lautsprecher, hinzugefügt haben, wird dieser ebenfalls angezeigt.

1. Wenn Sie einen zusätzlichen Lautsprecher verwenden und nicht einen Lautsprecher oder Kopfhörer, die mit dem eingebauten Kopfhöreranschluss verbunden sind, müssen Sie diesen als Standard konfigurieren. Führen Sie dazu den folgenden Befehl aus:

    ```sh
    sudo nano /usr/share/alsa/alsa.conf
    ```

    Dadurch wird eine Konfigurationsdatei in `nano`, einem terminalbasierten Texteditor, geöffnet. Scrollen Sie mit den Pfeiltasten Ihrer Tastatur nach unten, bis Sie die folgende Zeile finden:

    ```output
    defaults.pcm.card 0
    ```

    Ändern Sie den Wert von `0` auf die Kartennummer der Karte, die Sie aus der Liste des Befehls `aplay -l` verwenden möchten. Im obigen Beispiel gibt es eine zweite Soundkarte namens `card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]`, die Karte 1 verwendet. Um diese zu verwenden, würde ich die Zeile wie folgt aktualisieren:

    ```output
    defaults.pcm.card 1
    ```

    Setzen Sie diesen Wert auf die entsprechende Kartennummer. Sie können mit den Pfeiltasten Ihrer Tastatur zur Nummer navigieren, dann die alte Nummer löschen und die neue wie gewohnt eingeben.

1. Speichern Sie die Änderungen und schließen Sie die Datei, indem Sie `Ctrl+x` drücken. Drücken Sie `y`, um die Datei zu speichern, und anschließend `Return`, um den Dateinamen auszuwählen.

### Aufgabe - Mikrofon und Lautsprecher testen

1. Führen Sie den folgenden Befehl aus, um 5 Sekunden Audio über das Mikrofon aufzunehmen:

    ```sh
    arecord --format=S16_LE --duration=5 --rate=16000 --file-type=wav out.wav
    ```

    Während dieser Befehl ausgeführt wird, machen Sie Geräusche in das Mikrofon, z. B. sprechen, singen, Beatboxen, ein Instrument spielen oder was Ihnen sonst einfällt.

1. Nach 5 Sekunden stoppt die Aufnahme. Führen Sie den folgenden Befehl aus, um die Audioaufnahme abzuspielen:

    ```sh
    aplay --format=S16_LE --rate=16000 out.wav
    ```

    Sie hören die Audioaufnahme über die Lautsprecher. Passen Sie die Lautstärke der Lautsprecher nach Bedarf an.

1. Wenn Sie die Lautstärke des eingebauten Mikrofonanschlusses oder die Verstärkung des Mikrofons anpassen müssen, können Sie das Dienstprogramm `alsamixer` verwenden. Weitere Informationen zu diesem Dienstprogramm finden Sie auf der [Linux alsamixer Man-Seite](https://linux.die.net/man/1/alsamixer).

1. Wenn beim Abspielen der Audioaufnahme Fehler auftreten, überprüfen Sie die Karte, die Sie als `defaults.pcm.card` in der Datei `alsa.conf` festgelegt haben.

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.