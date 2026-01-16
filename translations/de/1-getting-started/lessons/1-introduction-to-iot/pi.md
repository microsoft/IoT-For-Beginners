<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "8ff0d0a1d29832bb896b9c103b69a452",
  "translation_date": "2025-08-25T22:16:01+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/pi.md",
  "language_code": "de"
}
-->
# Raspberry Pi

Der [Raspberry Pi](https://raspberrypi.org) ist ein Einplatinencomputer. Sie können Sensoren und Aktoren mit einer Vielzahl von Geräten und Ökosystemen hinzufügen. Für diese Lektionen verwenden wir ein Hardware-Ökosystem namens [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html). Sie werden Ihren Pi programmieren und die Grove-Sensoren mit Python ansteuern.

![Ein Raspberry Pi 4](../../../../../translated_images/de/raspberry-pi-4.fd4590d308c3d456.webp)

## Einrichtung

Wenn Sie einen Raspberry Pi als Ihre IoT-Hardware verwenden, haben Sie zwei Möglichkeiten: Sie können alle Lektionen durchgehen und direkt auf dem Pi programmieren, oder Sie können sich mit einem „headless“ Pi verbinden und von Ihrem Computer aus programmieren.

Bevor Sie beginnen, müssen Sie außerdem das Grove Base Hat mit Ihrem Pi verbinden.

### Aufgabe - Einrichtung

Installieren Sie das Grove Base Hat auf Ihrem Pi und konfigurieren Sie den Pi.

1. Verbinden Sie das Grove Base Hat mit Ihrem Pi. Der Sockel auf dem Hat passt über alle GPIO-Pins des Pi und wird vollständig auf die Pins geschoben, sodass er fest auf der Basis sitzt. Es bedeckt den Pi vollständig.

    ![Das Grove Hat anbringen](../../../../../images/pi-grove-hat-fitting.gif)

1. Entscheiden Sie, wie Sie Ihren Pi programmieren möchten, und gehen Sie zum entsprechenden Abschnitt unten:

    * [Direkt auf Ihrem Pi arbeiten](../../../../../1-getting-started/lessons/1-introduction-to-iot)
    * [Remote-Zugriff, um den Pi zu programmieren](../../../../../1-getting-started/lessons/1-introduction-to-iot)

### Direkt auf Ihrem Pi arbeiten

Wenn Sie direkt auf Ihrem Pi arbeiten möchten, können Sie die Desktop-Version des Raspberry Pi OS verwenden und alle benötigten Tools installieren.

#### Aufgabe - Direkt auf Ihrem Pi arbeiten

Richten Sie Ihren Pi für die Entwicklung ein.

1. Folgen Sie den Anweisungen im [Raspberry Pi Setup Guide](https://projects.raspberrypi.org/en/projects/raspberry-pi-setting-up), um Ihren Pi einzurichten, ihn mit einer Tastatur/Maus/Monitor zu verbinden, ihn mit Ihrem WLAN- oder Ethernet-Netzwerk zu verbinden und die Software zu aktualisieren.

Um den Pi mit den Grove-Sensoren und -Aktoren zu programmieren, müssen Sie einen Editor installieren, mit dem Sie den Gerätecode schreiben können, sowie verschiedene Bibliotheken und Tools, die mit der Grove-Hardware interagieren.

1. Nachdem Ihr Pi neu gestartet wurde, starten Sie das Terminal, indem Sie auf das **Terminal**-Symbol in der oberen Menüleiste klicken oder *Menü -> Zubehör -> Terminal* auswählen.

1. Führen Sie den folgenden Befehl aus, um sicherzustellen, dass das Betriebssystem und die installierte Software auf dem neuesten Stand sind:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes
    ```

1. Führen Sie die folgenden Befehle aus, um alle benötigten Bibliotheken für die Grove-Hardware zu installieren:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Dies beginnt mit der Installation von Git sowie Pip, um Python-Pakete zu installieren.

    Eine der leistungsstarken Funktionen von Python ist die Möglichkeit, [Pip-Pakete](https://pypi.org) zu installieren – das sind Pakete mit Code, die von anderen Personen geschrieben und im Internet veröffentlicht wurden. Sie können ein Pip-Paket mit einem einzigen Befehl auf Ihrem Computer installieren und es dann in Ihrem Code verwenden.

    Die Seeed Grove Python-Pakete müssen aus dem Quellcode installiert werden. Diese Befehle klonen das Repository, das den Quellcode für dieses Paket enthält, und installieren es dann lokal.

    > 💁 Standardmäßig ist ein installiertes Paket überall auf Ihrem Computer verfügbar, was zu Problemen mit Paketversionen führen kann – z. B. wenn eine Anwendung von einer bestimmten Version eines Pakets abhängt, die nicht mehr funktioniert, wenn Sie eine neue Version für eine andere Anwendung installieren. Um dieses Problem zu umgehen, können Sie eine [Python-virtuelle Umgebung](https://docs.python.org/3/library/venv.html) verwenden, im Wesentlichen eine Kopie von Python in einem dedizierten Ordner. Wenn Sie Pip-Pakete installieren, werden diese nur in diesem Ordner installiert. Sie werden keine virtuellen Umgebungen verwenden, wenn Sie Ihren Pi verwenden. Das Grove-Installationsskript installiert die Grove-Python-Pakete global. Wenn Sie eine virtuelle Umgebung verwenden möchten, müssten Sie diese einrichten und die Grove-Pakete manuell in dieser Umgebung neu installieren. Es ist einfacher, globale Pakete zu verwenden, insbesondere da viele Pi-Entwickler für jedes Projekt eine saubere SD-Karte neu flashen.

    Schließlich wird die I<sup>2</sup>C-Schnittstelle aktiviert.

1. Starten Sie den Pi entweder über das Menü oder durch Ausführen des folgenden Befehls im Terminal neu:

    ```sh
    sudo reboot
    ```

1. Nachdem der Pi neu gestartet wurde, starten Sie das Terminal erneut und führen Sie den folgenden Befehl aus, um [Visual Studio Code (VS Code)](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) zu installieren – dies ist der Editor, den Sie verwenden werden, um Ihren Gerätecode in Python zu schreiben.

    ```sh
    sudo apt install code
    ```

    Nach der Installation ist VS Code über das obere Menü verfügbar.

    > 💁 Sie können für diese Lektionen auch einen anderen Python-IDE oder Editor verwenden, wenn Sie ein bevorzugtes Tool haben. Die Anweisungen in den Lektionen basieren jedoch auf der Verwendung von VS Code.

1. Installieren Sie Pylance. Dies ist eine Erweiterung für VS Code, die Unterstützung für die Python-Sprache bietet. Lesen Sie die [Pylance-Erweiterungsdokumentation](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance), um Anweisungen zur Installation dieser Erweiterung in VS Code zu erhalten.

### Remote-Zugriff, um den Pi zu programmieren

Anstatt direkt auf dem Pi zu programmieren, kann er „headless“ betrieben werden, d. h. ohne Verbindung zu einer Tastatur/Maus/Monitor. Sie können ihn von Ihrem Computer aus konfigurieren und programmieren, indem Sie Visual Studio Code verwenden.

#### Pi OS einrichten

Um remote zu programmieren, muss das Pi OS auf einer SD-Karte installiert werden.

##### Aufgabe - Pi OS einrichten

Richten Sie das headless Pi OS ein.

1. Laden Sie den **Raspberry Pi Imager** von der [Raspberry Pi OS Software-Seite](https://www.raspberrypi.org/software/) herunter und installieren Sie ihn.

1. Legen Sie eine SD-Karte in Ihren Computer ein, verwenden Sie bei Bedarf einen Adapter.

1. Starten Sie den Raspberry Pi Imager.

1. Wählen Sie im Raspberry Pi Imager die Schaltfläche **CHOOSE OS** und dann *Raspberry Pi OS (Other)*, gefolgt von *Raspberry Pi OS Lite (32-bit)*.

    ![Der Raspberry Pi Imager mit ausgewähltem Raspberry Pi OS Lite](../../../../../translated_images/de/raspberry-pi-imager.24aedeab9e233d84.webp)

    > 💁 Raspberry Pi OS Lite ist eine Version des Raspberry Pi OS ohne Desktop-Benutzeroberfläche oder UI-basierte Tools. Diese werden für einen headless Pi nicht benötigt, wodurch die Installation kleiner und die Startzeit schneller wird.

1. Wählen Sie die Schaltfläche **CHOOSE STORAGE** und dann Ihre SD-Karte aus.

1. Starten Sie die **Erweiterten Optionen**, indem Sie `Ctrl+Shift+X` drücken. Diese Optionen ermöglichen eine Vorkonfiguration des Raspberry Pi OS, bevor es auf die SD-Karte geschrieben wird.

    1. Aktivieren Sie das Kontrollkästchen **Enable SSH** und legen Sie ein Passwort für den Benutzer `pi` fest. Dieses Passwort wird später für die Anmeldung am Pi verwendet.

    1. Wenn Sie planen, den Pi über WLAN zu verbinden, aktivieren Sie das Kontrollkästchen **Configure WiFi** und geben Sie Ihre WLAN-SSID und Ihr Passwort ein. Wählen Sie außerdem Ihr WLAN-Land aus. Dies ist nicht erforderlich, wenn Sie ein Ethernet-Kabel verwenden. Stellen Sie sicher, dass das Netzwerk, mit dem Sie sich verbinden, dasselbe ist, in dem sich Ihr Computer befindet.

    1. Aktivieren Sie das Kontrollkästchen **Set locale settings** und legen Sie Ihr Land und Ihre Zeitzone fest.

    1. Wählen Sie die Schaltfläche **SAVE**.

1. Wählen Sie die Schaltfläche **WRITE**, um das Betriebssystem auf die SD-Karte zu schreiben. Wenn Sie macOS verwenden, werden Sie aufgefordert, Ihr Passwort einzugeben, da das zugrunde liegende Tool, das Disk-Images schreibt, privilegierten Zugriff benötigt.

Das Betriebssystem wird auf die SD-Karte geschrieben. Sobald der Vorgang abgeschlossen ist, wird die Karte vom Betriebssystem ausgeworfen, und Sie werden benachrichtigt. Entfernen Sie die SD-Karte aus Ihrem Computer, stecken Sie sie in den Pi, schalten Sie den Pi ein und warten Sie etwa 2 Minuten, bis er vollständig hochgefahren ist.

#### Verbindung zum Pi herstellen

Der nächste Schritt besteht darin, den Pi remote zuzugreifen. Dies kann mit `ssh` erfolgen, das auf macOS, Linux und neueren Windows-Versionen verfügbar ist.

##### Aufgabe - Verbindung zum Pi herstellen

Greifen Sie remote auf den Pi zu.

1. Starten Sie ein Terminal oder die Eingabeaufforderung und geben Sie den folgenden Befehl ein, um eine Verbindung zum Pi herzustellen:

    ```sh
    ssh pi@raspberrypi.local
    ```

    Wenn Sie Windows mit einer älteren Version verwenden, die `ssh` nicht installiert hat, können Sie OpenSSH verwenden. Die Installationsanweisungen finden Sie in der [OpenSSH-Installationsdokumentation](https://docs.microsoft.com//windows-server/administration/openssh/openssh_install_firstuse?WT.mc_id=academic-17441-jabenn).

1. Dies sollte eine Verbindung zu Ihrem Pi herstellen und nach dem Passwort fragen.

    Computer im Netzwerk mit `<hostname>.local` zu finden, ist eine relativ neue Funktion in Linux und Windows. Wenn Sie Linux oder Windows verwenden und Fehlermeldungen erhalten, dass der Hostname nicht gefunden wurde, müssen Sie zusätzliche Software installieren, um ZeroConf-Netzwerke (auch als Bonjour von Apple bezeichnet) zu aktivieren:

    1. Wenn Sie Linux verwenden, installieren Sie Avahi mit folgendem Befehl:

        ```sh
        sudo apt-get install avahi-daemon
        ```

    1. Wenn Sie Windows verwenden, ist der einfachste Weg, ZeroConf zu aktivieren, die Installation von [Bonjour Print Services for Windows](http://support.apple.com/kb/DL999). Sie können auch [iTunes für Windows](https://www.apple.com/itunes/download/) installieren, um eine neuere Version des Dienstprogramms zu erhalten (die nicht separat verfügbar ist).

    > 💁 Wenn Sie keine Verbindung mit `raspberrypi.local` herstellen können, können Sie die IP-Adresse Ihres Pi verwenden. Lesen Sie die [Raspberry Pi IP-Adresse-Dokumentation](https://www.raspberrypi.org/documentation/remote-access/ip-address.md) für Anweisungen zu verschiedenen Möglichkeiten, die IP-Adresse zu ermitteln.

1. Geben Sie das Passwort ein, das Sie in den erweiterten Optionen des Raspberry Pi Imagers festgelegt haben.

#### Software auf dem Pi konfigurieren

Sobald Sie mit dem Pi verbunden sind, müssen Sie sicherstellen, dass das Betriebssystem auf dem neuesten Stand ist, und verschiedene Bibliotheken und Tools installieren, die mit der Grove-Hardware interagieren.

##### Aufgabe - Software auf dem Pi konfigurieren

Konfigurieren Sie die installierte Pi-Software und installieren Sie die Grove-Bibliotheken.

1. Führen Sie in Ihrer `ssh`-Sitzung den folgenden Befehl aus, um den Pi zu aktualisieren und anschließend neu zu starten:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes && sudo reboot
    ```

    Der Pi wird aktualisiert und neu gestartet. Die `ssh`-Sitzung wird beendet, wenn der Pi neu gestartet wird. Warten Sie etwa 30 Sekunden und stellen Sie die Verbindung erneut her.

1. Führen Sie in der erneut verbundenen `ssh`-Sitzung die folgenden Befehle aus, um alle benötigten Bibliotheken für die Grove-Hardware zu installieren:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Dies beginnt mit der Installation von Git sowie Pip, um Python-Pakete zu installieren.

    Eine der leistungsstarken Funktionen von Python ist die Möglichkeit, [Pip-Pakete](https://pypi.org) zu installieren – das sind Pakete mit Code, die von anderen Personen geschrieben und im Internet veröffentlicht wurden. Sie können ein Pip-Paket mit einem einzigen Befehl auf Ihrem Computer installieren und es dann in Ihrem Code verwenden.

    Die Seeed Grove Python-Pakete müssen aus dem Quellcode installiert werden. Diese Befehle klonen das Repository, das den Quellcode für dieses Paket enthält, und installieren es dann lokal.

    > 💁 Standardmäßig ist ein installiertes Paket überall auf Ihrem Computer verfügbar, was zu Problemen mit Paketversionen führen kann – z. B. wenn eine Anwendung von einer bestimmten Version eines Pakets abhängt, die nicht mehr funktioniert, wenn Sie eine neue Version für eine andere Anwendung installieren. Um dieses Problem zu umgehen, können Sie eine [Python-virtuelle Umgebung](https://docs.python.org/3/library/venv.html) verwenden, im Wesentlichen eine Kopie von Python in einem dedizierten Ordner. Wenn Sie Pip-Pakete installieren, werden diese nur in diesem Ordner installiert. Sie werden keine virtuellen Umgebungen verwenden, wenn Sie Ihren Pi verwenden. Das Grove-Installationsskript installiert die Grove-Python-Pakete global. Wenn Sie eine virtuelle Umgebung verwenden möchten, müssten Sie diese einrichten und die Grove-Pakete manuell in dieser Umgebung neu installieren. Es ist einfacher, globale Pakete zu verwenden, insbesondere da viele Pi-Entwickler für jedes Projekt eine saubere SD-Karte neu flashen.

    Schließlich wird die I<sup>2</sup>C-Schnittstelle aktiviert.

1. Starten Sie den Pi neu, indem Sie den folgenden Befehl ausführen:

    ```sh
    sudo reboot
    ```

    Die `ssh`-Sitzung wird beendet, wenn der Pi neu gestartet wird. Es ist nicht erforderlich, die Verbindung erneut herzustellen.

#### VS Code für den Remote-Zugriff konfigurieren

Sobald der Pi konfiguriert ist, können Sie mit Visual Studio Code (VS Code) von Ihrem Computer aus eine Verbindung herstellen – dies ist ein kostenloser Entwickler-Texteditor, den Sie verwenden werden, um Ihren Gerätecode in Python zu schreiben.

##### Aufgabe - VS Code für den Remote-Zugriff konfigurieren

Installieren Sie die erforderliche Software und stellen Sie eine Remote-Verbindung zu Ihrem Pi her.

1. Installieren Sie VS Code auf Ihrem Computer, indem Sie der [VS Code-Dokumentation](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) folgen.

1. Folgen Sie den Anweisungen in der [VS Code Remote Development using SSH-Dokumentation](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn), um die benötigten Komponenten zu installieren.

1. Verbinden Sie VS Code gemäß denselben Anweisungen mit dem Pi.

1. Sobald die Verbindung hergestellt ist, folgen Sie den [Anweisungen zur Verwaltung von Erweiterungen](https://code.visualstudio.com/docs/remote/ssh#_managing-extensions?WT.mc_id=academic-17441-jabenn), um die [Pylance-Erweiterung](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) remote auf dem Pi zu installieren.

## Hallo Welt
Es ist üblich, beim Einstieg in eine neue Programmiersprache oder Technologie eine "Hello World"-Anwendung zu erstellen – eine kleine Anwendung, die beispielsweise den Text `"Hello World"` ausgibt, um zu zeigen, dass alle Werkzeuge korrekt eingerichtet sind.

Die Hello World-App für den Pi stellt sicher, dass Python und Visual Studio Code korrekt installiert sind.

Diese App wird in einem Ordner namens `nightlight` gespeichert und später in diesem Projekt mit unterschiedlichem Code wiederverwendet, um die Nightlight-Anwendung zu erstellen.

### Aufgabe - Hello World

Erstelle die Hello World-App.

1. Starte VS Code, entweder direkt auf dem Pi oder auf deinem Computer und verbinde dich mit dem Pi über die Remote SSH-Erweiterung.

1. Öffne das VS Code-Terminal, indem du *Terminal -> Neues Terminal* auswählst oder `` CTRL+` `` drückst. Es öffnet sich im Home-Verzeichnis des Benutzers `pi`.

1. Führe die folgenden Befehle aus, um ein Verzeichnis für deinen Code zu erstellen und eine Python-Datei namens `app.py` in diesem Verzeichnis anzulegen:

    ```sh
    mkdir nightlight
    cd nightlight
    touch app.py
    ```

1. Öffne diesen Ordner in VS Code, indem du *Datei -> Öffnen...* auswählst, den Ordner *nightlight* auswählst und dann auf **OK** klickst.

    ![Der VS Code-Dialog zum Öffnen zeigt den Nightlight-Ordner](../../../../../translated_images/de/vscode-open-nightlight-remote.d3d2a4011e30d535.webp)

1. Öffne die Datei `app.py` im VS Code-Explorer und füge den folgenden Code hinzu:

    ```python
    print('Hello World!')
    ```

    Die Funktion `print` gibt alles, was ihr übergeben wird, in der Konsole aus.

1. Führe im VS Code-Terminal Folgendes aus, um deine Python-App zu starten:

    ```sh
    python app.py
    ```

    > 💁 Möglicherweise musst du `python3` explizit aufrufen, um diesen Code auszuführen, wenn Python 2 zusätzlich zu Python 3 (der neuesten Version) installiert ist. Wenn Python 2 installiert ist, wird durch den Aufruf von `python` Python 2 anstelle von Python 3 verwendet. Standardmäßig haben die neuesten Versionen des Raspberry Pi OS nur Python 3 installiert.

    Die folgende Ausgabe erscheint im Terminal:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py
    Hello World!
    ```

> 💁 Du findest diesen Code im Ordner [code/pi](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/pi).

😀 Dein 'Hello World'-Programm war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.