<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64ad4ddb4de81a18b7252e968f10b404",
  "translation_date": "2025-08-25T22:34:20+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/single-board-computer-set-timer.md",
  "language_code": "de"
}
-->
# Einen Timer einstellen - Virtuelle IoT-Hardware und Raspberry Pi

In diesem Teil der Lektion rufst du deinen serverlosen Code auf, um die Sprache zu verstehen, und stellst basierend auf den Ergebnissen einen Timer auf deinem virtuellen IoT-Gerät oder Raspberry Pi ein.

## Einen Timer einstellen

Der Text, der aus dem Sprach-zu-Text-Aufruf zurückkommt, muss an deinen serverlosen Code gesendet werden, um von LUIS verarbeitet zu werden. Dabei wird die Anzahl der Sekunden für den Timer zurückgegeben. Diese Anzahl an Sekunden kann verwendet werden, um einen Timer einzustellen.

Timer können mit der Python-Klasse `threading.Timer` eingestellt werden. Diese Klasse nimmt eine Verzögerungszeit und eine Funktion entgegen, und nach Ablauf der Verzögerungszeit wird die Funktion ausgeführt.

### Aufgabe - Den Text an die serverlose Funktion senden

1. Öffne das Projekt `smart-timer` in VS Code und stelle sicher, dass die virtuelle Umgebung im Terminal geladen ist, falls du ein virtuelles IoT-Gerät verwendest.

1. Deklariere oberhalb der Funktion `process_text` eine Funktion namens `get_timer_time`, um den REST-Endpunkt aufzurufen, den du erstellt hast:

    ```python
    def get_timer_time(text):
    ```

1. Füge dieser Funktion den folgenden Code hinzu, um die URL zu definieren, die aufgerufen werden soll:

    ```python
    url = '<URL>'
    ```

    Ersetze `<URL>` durch die URL deines REST-Endpunkts, den du in der letzten Lektion entweder auf deinem Computer oder in der Cloud erstellt hast.

1. Füge den folgenden Code hinzu, um den Text als Eigenschaft festzulegen, die als JSON an den Aufruf übergeben wird:

    ```python
    body = {
        'text': text
    }
    
    response = requests.post(url, json=body)
    ```

1. Hole darunter die `seconds` aus der Antwort-Payload und gib 0 zurück, falls der Aufruf fehlgeschlagen ist:

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```

    Erfolgreiche HTTP-Aufrufe geben einen Statuscode im Bereich 200 zurück, und dein serverloser Code gibt 200 zurück, wenn der Text verarbeitet und als Timer-Intent erkannt wurde.

### Aufgabe - Einen Timer in einem Hintergrund-Thread einstellen

1. Füge die folgende Import-Anweisung am Anfang der Datei hinzu, um die Python-Bibliothek `threading` zu importieren:

    ```python
    import threading
    ```

1. Füge oberhalb der Funktion `process_text` eine Funktion hinzu, um eine Antwort auszugeben. Diese wird vorerst nur in die Konsole schreiben, später in dieser Lektion wird sie den Text sprechen.

    ```python
    def say(text):
        print(text)
    ```

1. Füge darunter eine Funktion hinzu, die vom Timer aufgerufen wird, um anzukündigen, dass der Timer abgelaufen ist:

    ```python
    def announce_timer(minutes, seconds):
        announcement = 'Times up on your '
        if minutes > 0:
            announcement += f'{minutes} minute '
        if seconds > 0:
            announcement += f'{seconds} second '
        announcement += 'timer.'
        say(announcement)
    ```

    Diese Funktion nimmt die Anzahl der Minuten und Sekunden für den Timer und erstellt einen Satz, der besagt, dass der Timer abgelaufen ist. Sie überprüft die Anzahl der Minuten und Sekunden und schließt jede Zeiteinheit nur ein, wenn sie einen Wert hat. Zum Beispiel, wenn die Anzahl der Minuten 0 ist, werden nur die Sekunden in die Nachricht aufgenommen. Dieser Satz wird dann an die Funktion `say` gesendet.

1. Füge darunter die folgende Funktion `create_timer` hinzu, um einen Timer zu erstellen:

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

    Diese Funktion nimmt die Gesamtanzahl der Sekunden für den Timer, die im Befehl übergeben werden, und konvertiert diese in Minuten und Sekunden. Anschließend erstellt und startet sie ein Timer-Objekt mit der Gesamtanzahl der Sekunden, wobei die Funktion `announce_timer` und eine Liste mit den Minuten und Sekunden übergeben werden. Wenn der Timer abläuft, wird die Funktion `announce_timer` aufgerufen und der Inhalt dieser Liste als Parameter übergeben - das erste Element der Liste wird als Parameter `minutes` und das zweite Element als Parameter `seconds` übergeben.

1. Füge am Ende der Funktion `create_timer` Code hinzu, um eine Nachricht zu erstellen, die dem Benutzer mitteilt, dass der Timer gestartet wird:

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

    Auch hier wird nur die Zeiteinheit einbezogen, die einen Wert hat. Dieser Satz wird dann an die Funktion `say` gesendet.

1. Füge am Ende der Funktion `process_text` Folgendes hinzu, um die Zeit für den Timer aus dem Text zu erhalten und dann den Timer zu erstellen:

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

    Der Timer wird nur erstellt, wenn die Anzahl der Sekunden größer als 0 ist.

1. Führe die App aus und stelle sicher, dass die Funktions-App ebenfalls läuft. Stelle einige Timer ein, und die Ausgabe zeigt, dass der Timer eingestellt wurde und dann anzeigt, wenn er abläuft:

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 Du findest diesen Code im Ordner [code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi) oder [code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device).

😀 Dein Timer-Programm war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.