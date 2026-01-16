<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "93d352de36526b8990e41dd538100324",
  "translation_date": "2025-08-25T22:50:25+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-microphone.md",
  "language_code": "de"
}
-->
# Konfigurieren Sie Ihr Mikrofon und Ihre Lautsprecher - Wio Terminal

In diesem Abschnitt der Lektion fügen Sie Lautsprecher zu Ihrem Wio Terminal hinzu. Das Wio Terminal verfügt bereits über ein eingebautes Mikrofon, das zur Sprachaufnahme verwendet werden kann.

## Hardware

Das Wio Terminal hat bereits ein eingebautes Mikrofon, das zur Audioaufnahme für die Spracherkennung verwendet werden kann.

![Das Mikrofon des Wio Terminals](../../../../../translated_images/de/wio-mic.3f8c843dbe8ad917.webp)

Um einen Lautsprecher hinzuzufügen, können Sie das [ReSpeaker 2-Mics Pi Hat](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) verwenden. Dies ist eine externe Platine, die zwei MEMS-Mikrofone, einen Lautsprecheranschluss und eine Kopfhörerbuchse enthält.

![Das ReSpeaker 2-Mics Pi Hat](../../../../../translated_images/de/respeaker.f5d19d1c6b14ab16.webp)

Sie benötigen entweder Kopfhörer, einen Lautsprecher mit einem 3,5-mm-Stecker oder einen Lautsprecher mit einer JST-Verbindung wie den [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html).

Um das ReSpeaker 2-Mics Pi Hat anzuschließen, benötigen Sie 40 Pin-to-Pin (auch als Male-to-Male bezeichnet) Jumper-Kabel.

> 💁 Wenn Sie mit Löten vertraut sind, können Sie das [40 Pin Raspberry Pi Hat Adapter Board For Wio Terminal](https://www.seeedstudio.com/40-Pin-Raspberry-Pi-Hat-Adapter-Board-For-Wio-Terminal-p-4730.html) verwenden, um das ReSpeaker anzuschließen.

Sie benötigen außerdem eine SD-Karte, um Audio herunterzuladen und abzuspielen. Das Wio Terminal unterstützt nur SD-Karten bis zu 16 GB, die als FAT32 oder exFAT formatiert sein müssen.

### Aufgabe - ReSpeaker Pi Hat anschließen

1. Schalten Sie das Wio Terminal aus und verbinden Sie das ReSpeaker 2-Mics Pi Hat mit dem Wio Terminal, indem Sie die Jumper-Kabel und die GPIO-Anschlüsse auf der Rückseite des Wio Terminals verwenden:

    Die Pins müssen wie folgt verbunden werden:

    ![Ein Pin-Diagramm](../../../../../translated_images/de/wio-respeaker-wiring-0.767f80aa65081038.webp)

1. Positionieren Sie das ReSpeaker und das Wio Terminal so, dass die GPIO-Anschlüsse nach oben zeigen und sich auf der linken Seite befinden.

1. Beginnen Sie mit dem Anschluss oben links am GPIO-Anschluss des ReSpeakers. Verbinden Sie ein Pin-to-Pin-Jumper-Kabel vom oberen linken Anschluss des ReSpeakers mit dem oberen linken Anschluss des Wio Terminals.

1. Wiederholen Sie dies für alle Anschlüsse entlang der linken Seite der GPIO-Anschlüsse. Stellen Sie sicher, dass die Pins fest sitzen.

    ![Ein ReSpeaker mit den linken Pins, die mit den linken Pins des Wio Terminals verbunden sind](../../../../../translated_images/de/wio-respeaker-wiring-1.8d894727f2ba2400.webp)

    ![Ein ReSpeaker mit den linken Pins, die mit den linken Pins des Wio Terminals verbunden sind](../../../../../translated_images/de/wio-respeaker-wiring-2.329e1cbd306e754f.webp)

    > 💁 Wenn Ihre Jumper-Kabel zu Bändern zusammengefasst sind, lassen Sie sie zusammen - das erleichtert es, sicherzustellen, dass alle Kabel in der richtigen Reihenfolge verbunden sind.

1. Wiederholen Sie den Vorgang mit den rechten GPIO-Anschlüssen des ReSpeakers und des Wio Terminals. Diese Kabel müssen um die bereits vorhandenen Kabel herumgeführt werden.

    ![Ein ReSpeaker mit den rechten Pins, die mit den rechten Pins des Wio Terminals verbunden sind](../../../../../translated_images/de/wio-respeaker-wiring-3.75b0be447e2fa930.webp)

    ![Ein ReSpeaker mit den rechten Pins, die mit den rechten Pins des Wio Terminals verbunden sind](../../../../../translated_images/de/wio-respeaker-wiring-4.aa9cd434d8779437.webp)

    > 💁 Wenn Ihre Jumper-Kabel zu Bändern zusammengefasst sind, teilen Sie sie in zwei Bänder. Führen Sie jeweils eines auf jeder Seite der vorhandenen Kabel entlang.

    > 💁 Sie können Klebeband verwenden, um die Pins zu einem Block zu fixieren, damit sie beim Anschließen nicht herausfallen.
    >
    > ![Die Pins mit Klebeband fixiert](../../../../../translated_images/de/wio-respeaker-wiring-5.af117c20acf622f3.webp)

1. Sie müssen einen Lautsprecher hinzufügen.

    * Wenn Sie einen Lautsprecher mit einem JST-Kabel verwenden, verbinden Sie ihn mit dem JST-Anschluss des ReSpeakers.

      ![Ein Lautsprecher, der mit einem JST-Kabel an den ReSpeaker angeschlossen ist](../../../../../translated_images/de/respeaker-jst-speaker.a441d177809df945.webp)

    * Wenn Sie einen Lautsprecher mit einem 3,5-mm-Stecker oder Kopfhörer verwenden, stecken Sie diese in die 3,5-mm-Buchse.

      ![Ein Lautsprecher, der über die 3,5-mm-Buchse an den ReSpeaker angeschlossen ist](../../../../../translated_images/de/respeaker-35mm-speaker.ad79ef4f128c7751.webp)

### Aufgabe - SD-Karte einrichten

1. Schließen Sie die SD-Karte an Ihren Computer an, verwenden Sie einen externen Kartenleser, falls Ihr Computer keinen SD-Kartensteckplatz hat.

1. Formatieren Sie die SD-Karte mit dem entsprechenden Tool auf Ihrem Computer und stellen Sie sicher, dass Sie das Dateisystem FAT32 oder exFAT verwenden.

1. Stecken Sie die SD-Karte in den SD-Kartensteckplatz auf der linken Seite des Wio Terminals, direkt unterhalb des Netzschalters. Stellen Sie sicher, dass die Karte vollständig eingesteckt ist und einrastet - möglicherweise benötigen Sie ein dünnes Werkzeug oder eine andere SD-Karte, um sie vollständig einzuschieben.

    ![Einsetzen der SD-Karte in den SD-Kartensteckplatz unterhalb des Netzschalters](../../../../../translated_images/de/wio-sd-card.acdcbe322fa4ee7f.webp)

    > 💁 Um die SD-Karte auszuwerfen, müssen Sie sie leicht eindrücken, damit sie auswirft. Sie benötigen ein dünnes Werkzeug wie einen Flachkopfschraubendreher oder eine andere SD-Karte, um dies zu tun.

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.