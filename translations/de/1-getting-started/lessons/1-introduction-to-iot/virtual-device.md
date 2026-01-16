<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "52b4de6144b2efdced7797a5339d6035",
  "translation_date": "2025-08-25T22:13:55+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/virtual-device.md",
  "language_code": "de"
}
-->
# Virtueller Einplatinencomputer

Anstatt ein IoT-Gerät zusammen mit Sensoren und Aktoren zu kaufen, können Sie Ihren Computer nutzen, um IoT-Hardware zu simulieren. Das [CounterFit-Projekt](https://github.com/CounterFit-IoT/CounterFit) ermöglicht es Ihnen, eine App lokal auszuführen, die IoT-Hardware wie Sensoren und Aktoren simuliert. Sie können auf diese Sensoren und Aktoren mit lokalem Python-Code zugreifen, der genauso geschrieben wird wie der Code, den Sie auf einem Raspberry Pi mit physischer Hardware schreiben würden.

## Einrichtung

Um CounterFit zu nutzen, müssen Sie einige kostenlose Software auf Ihrem Computer installieren.

### Aufgabe

Installieren Sie die erforderliche Software.

1. Installieren Sie Python. Besuchen Sie die [Python-Downloadseite](https://www.python.org/downloads/), um Anweisungen zur Installation der neuesten Python-Version zu erhalten.

1. Installieren Sie Visual Studio Code (VS Code). Dies ist der Editor, den Sie verwenden werden, um Ihren virtuellen Gerätecode in Python zu schreiben. Besuchen Sie die [VS Code-Dokumentation](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn), um Anweisungen zur Installation von VS Code zu erhalten.

    > 💁 Sie können für diese Lektionen auch ein anderes bevorzugtes Python-IDE oder einen Editor verwenden, aber die Anweisungen basieren auf der Nutzung von VS Code.

1. Installieren Sie die VS Code Pylance-Erweiterung. Diese Erweiterung bietet Unterstützung für die Python-Programmiersprache in VS Code. Besuchen Sie die [Pylance-Erweiterungsdokumentation](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance), um Anweisungen zur Installation dieser Erweiterung in VS Code zu erhalten.

Die Anweisungen zur Installation und Konfiguration der CounterFit-App werden zu einem späteren Zeitpunkt in den Aufgabenanweisungen gegeben, da sie projektbezogen installiert wird.

## Hallo Welt

Es ist üblich, bei der Arbeit mit einer neuen Programmiersprache oder Technologie eine "Hallo Welt"-Anwendung zu erstellen – eine kleine Anwendung, die beispielsweise den Text `"Hello World"` ausgibt, um zu zeigen, dass alle Werkzeuge korrekt konfiguriert sind.

Die "Hallo Welt"-App für die virtuelle IoT-Hardware stellt sicher, dass Python und Visual Studio Code korrekt installiert sind. Sie wird auch eine Verbindung zu CounterFit herstellen, um die virtuellen IoT-Sensoren und -Aktoren zu nutzen. Es wird keine Hardware verwendet, sondern lediglich eine Verbindung hergestellt, um zu beweisen, dass alles funktioniert.

Diese App wird in einem Ordner namens `nightlight` gespeichert und später mit unterschiedlichem Code wiederverwendet, um die Nachtlicht-Anwendung zu erstellen.

### Konfigurieren einer Python-virtuellen Umgebung

Eine der leistungsstarken Funktionen von Python ist die Möglichkeit, [Pip-Pakete](https://pypi.org) zu installieren – das sind Codepakete, die von anderen Personen geschrieben und im Internet veröffentlicht wurden. Sie können ein Pip-Paket mit einem einzigen Befehl auf Ihrem Computer installieren und es dann in Ihrem Code verwenden. Sie werden Pip verwenden, um ein Paket zu installieren, das mit CounterFit kommuniziert.

Standardmäßig ist ein installiertes Paket überall auf Ihrem Computer verfügbar, was zu Problemen mit Paketversionen führen kann – beispielsweise wenn eine Anwendung von einer bestimmten Version eines Pakets abhängt, die nicht mehr funktioniert, wenn Sie eine neue Version für eine andere Anwendung installieren. Um dieses Problem zu umgehen, können Sie eine [Python-virtuelle Umgebung](https://docs.python.org/3/library/venv.html) verwenden, im Wesentlichen eine Kopie von Python in einem dedizierten Ordner. Wenn Sie Pip-Pakete installieren, werden diese nur in diesem Ordner installiert.

> 💁 Wenn Sie einen Raspberry Pi verwenden, haben Sie auf diesem Gerät keine virtuelle Umgebung eingerichtet, um Pip-Pakete zu verwalten. Stattdessen verwenden Sie globale Pakete, da die Grove-Pakete global durch das Installationsskript installiert werden.

#### Aufgabe – Konfigurieren einer Python-virtuellen Umgebung

Konfigurieren Sie eine Python-virtuelle Umgebung und installieren Sie die Pip-Pakete für CounterFit.

1. Führen Sie in Ihrem Terminal oder der Befehlszeile Folgendes an einem Ort Ihrer Wahl aus, um ein neues Verzeichnis zu erstellen und zu wechseln:

    ```sh
    mkdir nightlight
    cd nightlight
    ```

1. Führen Sie nun Folgendes aus, um eine virtuelle Umgebung im Ordner `.venv` zu erstellen:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Sie müssen explizit `python3` aufrufen, um die virtuelle Umgebung zu erstellen, falls Sie Python 2 zusätzlich zu Python 3 (der neuesten Version) installiert haben. Wenn Python 2 installiert ist, wird durch den Aufruf von `python` Python 2 anstelle von Python 3 verwendet.

1. Aktivieren Sie die virtuelle Umgebung:

    * Unter Windows:
        * Wenn Sie die Eingabeaufforderung oder die Eingabeaufforderung über Windows Terminal verwenden, führen Sie Folgendes aus:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Wenn Sie PowerShell verwenden, führen Sie Folgendes aus:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

            > Wenn Sie eine Fehlermeldung erhalten, dass das Ausführen von Skripten auf diesem System deaktiviert ist, müssen Sie das Ausführen von Skripten durch Festlegen einer geeigneten Ausführungsrichtlinie aktivieren. Sie können dies tun, indem Sie PowerShell als Administrator starten und dann den folgenden Befehl ausführen:

            ```powershell
            Set-ExecutionPolicy -ExecutionPolicy Unrestricted
            ```

            Geben Sie `Y` ein, wenn Sie zur Bestätigung aufgefordert werden. Starten Sie dann PowerShell neu und versuchen Sie es erneut.

            Sie können diese Ausführungsrichtlinie später bei Bedarf zurücksetzen. Weitere Informationen finden Sie auf der [Seite zu Ausführungsrichtlinien in der Microsoft-Dokumentation](https://docs.microsoft.com/powershell/module/microsoft.powershell.core/about/about_execution_policies?WT.mc_id=academic-17441-jabenn).

    * Unter macOS oder Linux führen Sie Folgendes aus:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Diese Befehle sollten von demselben Ort aus ausgeführt werden, an dem Sie den Befehl zum Erstellen der virtuellen Umgebung ausgeführt haben. Sie müssen niemals in den `.venv`-Ordner navigieren. Sie sollten immer den Aktivierungsbefehl und alle Befehle zum Installieren von Paketen oder Ausführen von Code von dem Ordner ausführen, in dem Sie die virtuelle Umgebung erstellt haben.

1. Sobald die virtuelle Umgebung aktiviert ist, wird der Standardbefehl `python` die Version von Python ausführen, die zum Erstellen der virtuellen Umgebung verwendet wurde. Führen Sie Folgendes aus, um die Version zu überprüfen:

    ```sh
    python --version
    ```

    Die Ausgabe sollte Folgendes enthalten:

    ```output
    (.venv) ➜  nightlight python --version
    Python 3.9.1
    ```

    > 💁 Ihre Python-Version kann unterschiedlich sein – solange es Version 3.6 oder höher ist, ist alles in Ordnung. Wenn nicht, löschen Sie diesen Ordner, installieren Sie eine neuere Version von Python und versuchen Sie es erneut.

1. Führen Sie die folgenden Befehle aus, um die Pip-Pakete für CounterFit zu installieren. Diese Pakete umfassen die Haupt-CounterFit-App sowie Shims für Grove-Hardware. Diese Shims ermöglichen es Ihnen, Code zu schreiben, als ob Sie physische Sensoren und Aktoren aus dem Grove-Ökosystem programmieren würden, die jedoch mit virtuellen IoT-Geräten verbunden sind.

    ```sh
    pip install CounterFit
    pip install counterfit-connection
    pip install counterfit-shims-grove
    ```

    Diese Pip-Pakete werden nur in der virtuellen Umgebung installiert und sind außerhalb dieser nicht verfügbar.

### Schreiben Sie den Code

Sobald die Python-virtuelle Umgebung bereit ist, können Sie den Code für die "Hallo Welt"-Anwendung schreiben.

#### Aufgabe – Schreiben Sie den Code

Erstellen Sie eine Python-Anwendung, die `"Hello World"` in der Konsole ausgibt.

1. Führen Sie in Ihrem Terminal oder der Befehlszeile Folgendes innerhalb der virtuellen Umgebung aus, um eine Python-Datei namens `app.py` zu erstellen:

    * Unter Windows führen Sie Folgendes aus:

        ```cmd
        type nul > app.py
        ```

    * Unter macOS oder Linux führen Sie Folgendes aus:

        ```cmd
        touch app.py
        ```

1. Öffnen Sie den aktuellen Ordner in VS Code:

    ```sh
    code .
    ```

    > 💁 Wenn Ihr Terminal unter macOS `command not found` zurückgibt, bedeutet dies, dass VS Code nicht zu Ihrem PATH hinzugefügt wurde. Sie können VS Code zu Ihrem PATH hinzufügen, indem Sie den Anweisungen im Abschnitt [Starten von der Befehlszeile aus der VS Code-Dokumentation](https://code.visualstudio.com/docs/setup/mac?WT.mc_id=academic-17441-jabenn#_launching-from-the-command-line) folgen und den Befehl anschließend ausführen. Unter Windows und Linux wird VS Code standardmäßig zu Ihrem PATH hinzugefügt.

1. Wenn VS Code startet, wird die Python-virtuelle Umgebung aktiviert. Die ausgewählte virtuelle Umgebung wird in der unteren Statusleiste angezeigt:

    ![VS Code zeigt die ausgewählte virtuelle Umgebung an](../../../../../translated_images/de/vscode-virtual-env.8ba42e04c3d533cf.webp)

1. Wenn das VS Code-Terminal bereits läuft, wenn VS Code startet, wird die virtuelle Umgebung darin nicht aktiviert. Am einfachsten ist es, das Terminal mit der Schaltfläche **Aktives Terminal beenden** zu schließen:

    ![VS Code-Schaltfläche zum Beenden des aktiven Terminals](../../../../../translated_images/de/vscode-kill-terminal.1cc4de7c6f25ee08.webp)

    Sie können erkennen, ob das Terminal die virtuelle Umgebung aktiviert hat, da der Name der virtuellen Umgebung ein Präfix in der Terminal-Eingabeaufforderung ist. Zum Beispiel könnte es so aussehen:

    ```sh
    (.venv) ➜  nightlight
    ```

    Wenn `.venv` nicht als Präfix in der Eingabeaufforderung angezeigt wird, ist die virtuelle Umgebung im Terminal nicht aktiv.

1. Starten Sie ein neues VS Code-Terminal, indem Sie *Terminal -> Neues Terminal* auswählen oder `` CTRL+` `` drücken. Das neue Terminal lädt die virtuelle Umgebung, und der Aufruf zur Aktivierung wird im Terminal angezeigt. Die Eingabeaufforderung enthält auch den Namen der virtuellen Umgebung (`.venv`):

    ```output
    ➜  nightlight source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Öffnen Sie die Datei `app.py` aus dem VS Code-Explorer und fügen Sie den folgenden Code hinzu:

    ```python
    print('Hello World!')
    ```

    Die Funktion `print` gibt alles, was ihr übergeben wird, in der Konsole aus.

1. Führen Sie im VS Code-Terminal Folgendes aus, um Ihre Python-App auszuführen:

    ```sh
    python app.py
    ```

    Die folgende Ausgabe wird angezeigt:

    ```output
    (.venv) ➜  nightlight python app.py 
    Hello World!
    ```

😀 Ihr "Hallo Welt"-Programm war ein Erfolg!

### Verbinden Sie die "Hardware"

Als zweiten "Hallo Welt"-Schritt starten Sie die CounterFit-App und verbinden Ihren Code damit. Dies ist das virtuelle Äquivalent zum Anschließen von IoT-Hardware an ein Entwicklungsboard.

#### Aufgabe – Verbinden Sie die "Hardware"

1. Starten Sie die CounterFit-App aus dem VS Code-Terminal mit folgendem Befehl:

    ```sh
    counterfit
    ```

    Die App wird gestartet und in Ihrem Webbrowser geöffnet:

    ![Die CounterFit-App läuft in einem Browser](../../../../../translated_images/de/counterfit-first-run.433326358b669b31d0e99c3513cb01bfbb13724d162c99cdcc8f51ecf5f9c779.png)

    Sie wird als *Disconnected* (Getrennt) angezeigt, und die LED in der oberen rechten Ecke ist ausgeschaltet.

1. Fügen Sie den folgenden Code oben in `app.py` ein:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

    Dieser Code importiert die Klasse `CounterFitConnection` aus dem Modul `counterfit_connection`, das aus dem zuvor installierten Pip-Paket `counterfit-connection` stammt. Anschließend wird eine Verbindung zur CounterFit-App hergestellt, die auf `127.0.0.1` (eine IP-Adresse, die immer für den Zugriff auf Ihren lokalen Computer verwendet werden kann, oft als *localhost* bezeichnet) auf Port 5000 läuft.

    > 💁 Wenn andere Apps auf Port 5000 laufen, können Sie dies ändern, indem Sie den Port im Code aktualisieren und CounterFit mit `CounterFit --port <port_number>` starten, wobei `<port_number>` durch den gewünschten Port ersetzt wird.

1. Sie müssen ein neues VS Code-Terminal starten, indem Sie die Schaltfläche **Neues integriertes Terminal erstellen** auswählen. Dies liegt daran, dass die CounterFit-App im aktuellen Terminal läuft.

    ![VS Code-Schaltfläche zum Erstellen eines neuen integrierten Terminals](../../../../../translated_images/de/vscode-new-terminal.77db8fc0f9cd3182.webp)

1. Führen Sie in diesem neuen Terminal die Datei `app.py` wie zuvor aus. Der Status von CounterFit ändert sich zu **Connected**, und die LED leuchtet auf.

    ![CounterFit zeigt den Status "Connected" an](../../../../../translated_images/de/counterfit-connected.ed30b46d8f79b0921f3fc70be10366e596a89dca3f80c2224a9d9fc98fccf884.png)

> 💁 Sie finden diesen Code im Ordner [code/virtual-device](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/virtual-device).

😀 Ihre Verbindung zur Hardware war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.