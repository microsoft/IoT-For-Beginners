<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a4f0c166010e31fd7b6ca20bc88dec6d",
  "translation_date": "2025-08-25T22:18:20+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md",
  "language_code": "de"
}
-->
# Wio Terminal

Das [Wio Terminal von Seeed Studios](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) ist ein Arduino-kompatibler Mikrocontroller mit integriertem WLAN sowie einigen Sensoren und Aktoren. Außerdem verfügt es über Anschlüsse, um weitere Sensoren und Aktoren hinzuzufügen, basierend auf einem Hardware-Ökosystem namens [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html).

![Ein Seeed Studios Wio Terminal](../../../../../translated_images/de/wio-terminal.b8299ee16587db9a.webp)

## Einrichtung

Um das Wio Terminal zu verwenden, müssen Sie einige kostenlose Software auf Ihrem Computer installieren. Außerdem müssen Sie die Firmware des Wio Terminals aktualisieren, bevor Sie es mit WLAN verbinden können.

### Aufgabe - Einrichtung

Installieren Sie die erforderliche Software und aktualisieren Sie die Firmware.

1. Installieren Sie Visual Studio Code (VS Code). Dies ist der Editor, den Sie verwenden werden, um Ihren Gerätecode in C/C++ zu schreiben. Lesen Sie die [VS Code-Dokumentation](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) für Anweisungen zur Installation von VS Code.

    > 💁 Eine weitere beliebte IDE für die Arduino-Entwicklung ist die [Arduino IDE](https://www.arduino.cc/en/software). Wenn Sie bereits mit diesem Tool vertraut sind, können Sie es anstelle von VS Code und PlatformIO verwenden. Die Lektionen basieren jedoch auf Anweisungen für die Verwendung von VS Code.

1. Installieren Sie die VS Code PlatformIO-Erweiterung. Dies ist eine Erweiterung für VS Code, die die Programmierung von Mikrocontrollern in C/C++ unterstützt. Lesen Sie die [PlatformIO-Erweiterungsdokumentation](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=platformio.platformio-ide) für Anweisungen zur Installation dieser Erweiterung in VS Code. Diese Erweiterung hängt von der Microsoft C/C++-Erweiterung ab, die automatisch installiert wird, wenn Sie PlatformIO installieren.

1. Verbinden Sie Ihr Wio Terminal mit Ihrem Computer. Das Wio Terminal verfügt über einen USB-C-Anschluss an der Unterseite, der mit einem USB-Anschluss Ihres Computers verbunden werden muss. Das Wio Terminal wird mit einem USB-C-zu-USB-A-Kabel geliefert. Wenn Ihr Computer jedoch nur USB-C-Anschlüsse hat, benötigen Sie entweder ein USB-C-Kabel oder einen USB-A-zu-USB-C-Adapter.

1. Befolgen Sie die Anweisungen in der [Wio Terminal Wiki WiFi Overview-Dokumentation](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/), um Ihr Wio Terminal einzurichten und die Firmware zu aktualisieren.

## Hello World

Es ist üblich, mit einer neuen Programmiersprache oder Technologie eine 'Hello World'-Anwendung zu erstellen – eine kleine Anwendung, die beispielsweise den Text `"Hello World"` ausgibt, um zu zeigen, dass alle Werkzeuge korrekt konfiguriert sind.

Die Hello World-App für das Wio Terminal stellt sicher, dass Sie Visual Studio Code korrekt mit PlatformIO installiert und für die Mikrocontroller-Entwicklung eingerichtet haben.

### Erstellen eines PlatformIO-Projekts

Der erste Schritt besteht darin, ein neues Projekt mit PlatformIO zu erstellen, das für das Wio Terminal konfiguriert ist.

#### Aufgabe - Erstellen eines PlatformIO-Projekts

Erstellen Sie das PlatformIO-Projekt.

1. Verbinden Sie das Wio Terminal mit Ihrem Computer.

1. Starten Sie VS Code.

1. Das PlatformIO-Symbol befindet sich in der Seitenmenüleiste:

    ![Die PlatformIO-Menüoption](../../../../../translated_images/de/vscode-platformio-menu.297be26b9733e5c4.webp)

    Wählen Sie dieses Menüelement aus und dann *PIO Home -> Open*.

    ![Die PlatformIO-Öffnen-Option](../../../../../translated_images/de/vscode-platformio-home-open.3f9a41bfd3f4da1c.webp)

1. Wählen Sie auf dem Begrüßungsbildschirm die Schaltfläche **+ New Project** aus.

    ![Die Schaltfläche Neues Projekt](../../../../../translated_images/de/vscode-platformio-welcome-new-button.ba6fc8a4c7b78cc8.webp)

1. Konfigurieren Sie das Projekt im *Project Wizard*:

    1. Benennen Sie Ihr Projekt `nightlight`.

    1. Geben Sie im Dropdown-Menü *Board* `WIO` ein, um die Boards zu filtern, und wählen Sie *Seeeduino Wio Terminal* aus.

    1. Lassen Sie das *Framework* auf *Arduino* eingestellt.

    1. Lassen Sie entweder das Kontrollkästchen *Use default location* aktiviert oder deaktivieren Sie es und wählen Sie einen Speicherort für Ihr Projekt aus.

    1. Wählen Sie die Schaltfläche **Finish** aus.

    ![Der abgeschlossene Projektassistent](../../../../../translated_images/de/vscode-platformio-nightlight-project-wizard.5c64db4da6037420.webp)

    PlatformIO wird die Komponenten herunterladen, die es benötigt, um Code für das Wio Terminal zu kompilieren, und Ihr Projekt erstellen. Dies kann einige Minuten dauern.

### Untersuchen des PlatformIO-Projekts

Der VS Code Explorer zeigt eine Reihe von Dateien und Ordnern, die vom PlatformIO-Assistenten erstellt wurden.

#### Ordner

* `.pio` - Dieser Ordner enthält temporäre Daten, die von PlatformIO benötigt werden, wie Bibliotheken oder kompilierter Code. Er wird automatisch neu erstellt, wenn er gelöscht wird, und Sie müssen ihn nicht in die Quellcodeverwaltung aufnehmen, wenn Sie Ihr Projekt auf Websites wie GitHub teilen.
* `.vscode` - Dieser Ordner enthält die Konfiguration, die von PlatformIO und VS Code verwendet wird. Er wird automatisch neu erstellt, wenn er gelöscht wird, und Sie müssen ihn nicht in die Quellcodeverwaltung aufnehmen, wenn Sie Ihr Projekt auf Websites wie GitHub teilen.
* `include` - Dieser Ordner ist für externe Header-Dateien vorgesehen, die benötigt werden, wenn zusätzliche Bibliotheken zu Ihrem Code hinzugefügt werden. Sie werden diesen Ordner in keiner der Lektionen verwenden.
* `lib` - Dieser Ordner ist für externe Bibliotheken vorgesehen, die Sie von Ihrem Code aus aufrufen möchten. Sie werden diesen Ordner in keiner der Lektionen verwenden.
* `src` - Dieser Ordner enthält den Hauptquellcode Ihrer Anwendung. Zu Beginn wird er eine einzelne Datei enthalten - `main.cpp`.
* `test` - Dieser Ordner ist für Unit-Tests Ihres Codes vorgesehen.

#### Dateien

* `main.cpp` - Diese Datei im Ordner `src` enthält den Einstiegspunkt Ihrer Anwendung. Öffnen Sie diese Datei, und sie wird den folgenden Code enthalten:

    ```cpp
    #include <Arduino.h>
    
    void setup() {
      // put your setup code here, to run once:
    }
    
    void loop() {
      // put your main code here, to run repeatedly:
    }
    ```

    Wenn das Gerät startet, führt das Arduino-Framework die Funktion `setup` einmal aus und dann die Funktion `loop` wiederholt, bis das Gerät ausgeschaltet wird.

* `.gitignore` - Diese Datei listet die Dateien und Verzeichnisse auf, die ignoriert werden sollen, wenn Sie Ihren Code in die Git-Quellcodeverwaltung aufnehmen, z. B. beim Hochladen in ein Repository auf GitHub.

* `platformio.ini` - Diese Datei enthält die Konfiguration für Ihr Gerät und Ihre App. Öffnen Sie diese Datei, und sie wird den folgenden Code enthalten:

    ```ini
    [env:seeed_wio_terminal]
    platform = atmelsam
    board = seeed_wio_terminal
    framework = arduino
    ```

    Der Abschnitt `[env:seeed_wio_terminal]` enthält die Konfiguration für das Wio Terminal. Sie können mehrere `env`-Abschnitte haben, sodass Ihr Code für mehrere Boards kompiliert werden kann.

    Die anderen Werte entsprechen der Konfiguration aus dem Projektassistenten:

  * `platform = atmelsam` definiert die Hardware, die das Wio Terminal verwendet (einen ATSAMD51-basierten Mikrocontroller).
  * `board = seeed_wio_terminal` definiert den Typ des Mikrocontroller-Boards (das Wio Terminal).
  * `framework = arduino` definiert, dass dieses Projekt das Arduino-Framework verwendet.

### Schreiben der Hello World-App

Sie sind jetzt bereit, die Hello World-App zu schreiben.

#### Aufgabe - Schreiben der Hello World-App

Schreiben Sie die Hello World-App.

1. Öffnen Sie die Datei `main.cpp` in VS Code.

1. Ändern Sie den Code, sodass er dem folgenden entspricht:

    ```cpp
    #include <Arduino.h>

    void setup()
    {
        Serial.begin(9600);

        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    
    void loop()
    {
        Serial.println("Hello World");
        delay(5000);
    }
    ```

    Die Funktion `setup` initialisiert eine Verbindung zum seriellen Port – in diesem Fall der USB-Port, der verwendet wird, um das Wio Terminal mit Ihrem Computer zu verbinden. Der Parameter `9600` ist die [Baudrate](https://wikipedia.org/wiki/Symbol_rate) (auch bekannt als Symbolrate) oder die Geschwindigkeit, mit der Daten über den seriellen Port in Bits pro Sekunde gesendet werden. Diese Einstellung bedeutet, dass 9.600 Bits (0s und 1s) Daten pro Sekunde gesendet werden. Anschließend wartet sie, bis der serielle Port bereit ist.

    Die Funktion `loop` sendet die Zeile `Hello World!` an den seriellen Port, also die Zeichen von `Hello World!` zusammen mit einem neuen Zeilenzeichen. Anschließend schläft sie für 5.000 Millisekunden oder 5 Sekunden. Nachdem die `loop`-Funktion endet, wird sie erneut ausgeführt, und zwar immer wieder, solange der Mikrocontroller eingeschaltet ist.

1. Versetzen Sie Ihr Wio Terminal in den Upload-Modus. Sie müssen dies jedes Mal tun, wenn Sie neuen Code auf das Gerät hochladen:

    1. Ziehen Sie den Netzschalter zweimal schnell nach unten – er springt jedes Mal in die Ein-Position zurück.

    1. Überprüfen Sie die blaue Status-LED rechts neben dem USB-Anschluss. Sie sollte pulsieren.
    
    [![Ein Video, das zeigt, wie man das Wio Terminal in den Upload-Modus versetzt](https://img.youtube.com/vi/LeKU_7zLRrQ/0.jpg)](https://youtu.be/LeKU_7zLRrQ)
    
    Klicken Sie auf das Bild oben, um ein Video zu sehen, das zeigt, wie dies gemacht wird.

1. Kompilieren und laden Sie den Code auf das Wio Terminal hoch.

    1. Öffnen Sie die VS Code-Befehlspalette.

    1. Geben Sie `PlatformIO Upload` ein, um die Upload-Option zu suchen, und wählen Sie *PlatformIO: Upload*.

        ![Die PlatformIO-Upload-Option in der Befehlspalette](../../../../../translated_images/de/vscode-platformio-upload-command-palette.9e0f49cf80d1f1c3.webp)

        PlatformIO wird den Code automatisch kompilieren, falls erforderlich, bevor er hochgeladen wird.

    1. Der Code wird kompiliert und auf das Wio Terminal hochgeladen.

        > 💁 Wenn Sie macOS verwenden, erscheint eine Benachrichtigung über ein *DISK NOT EJECTED PROPERLY*. Dies liegt daran, dass das Wio Terminal als Laufwerk eingebunden wird, während des Flash-Prozesses jedoch getrennt wird, wenn der kompilierte Code auf das Gerät geschrieben wird. Sie können diese Benachrichtigung ignorieren.

    ⚠️ Wenn Sie Fehler über einen nicht verfügbaren Upload-Port erhalten, stellen Sie zunächst sicher, dass Sie das Wio Terminal mit Ihrem Computer verbunden haben, es mit dem Schalter auf der linken Seite des Bildschirms eingeschaltet ist und sich im Upload-Modus befindet. Die grüne LED an der Unterseite sollte leuchten, und die blaue LED sollte pulsieren. Wenn der Fehler weiterhin auftritt, ziehen Sie den Ein-/Ausschalter erneut zweimal schnell nach unten, um das Wio Terminal in den Upload-Modus zu zwingen, und versuchen Sie den Upload erneut.

PlatformIO verfügt über einen Serial Monitor, der Daten überwachen kann, die über das USB-Kabel vom Wio Terminal gesendet werden. Dies ermöglicht es Ihnen, die Daten zu überwachen, die durch den Befehl `Serial.println("Hello World");` gesendet werden.

1. Öffnen Sie die VS Code-Befehlspalette.

1. Geben Sie `PlatformIO Serial` ein, um die Serial Monitor-Option zu suchen, und wählen Sie *PlatformIO: Serial Monitor*.

    ![Die PlatformIO Serial Monitor-Option in der Befehlspalette](../../../../../translated_images/de/vscode-platformio-serial-monitor-command-palette.b348ec841b8a1c14.webp)

    Ein neues Terminal wird geöffnet, und die über den seriellen Port gesendeten Daten werden in dieses Terminal gestreamt:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Hello World
    Hello World
    ```

    `Hello World` wird alle 5 Sekunden im Serial Monitor angezeigt.

> 💁 Sie finden diesen Code im Ordner [code/wio-terminal](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/wio-terminal).

😀 Ihr 'Hello World'-Programm war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.