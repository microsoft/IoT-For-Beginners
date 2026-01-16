<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a4f0c166010e31fd7b6ca20bc88dec6d",
  "translation_date": "2025-08-27T22:06:31+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md",
  "language_code": "nl"
}
-->
# Wio Terminal

De [Wio Terminal van Seeed Studios](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) is een Arduino-compatibele microcontroller met ingebouwde WiFi, sensoren en actuatoren. Daarnaast heeft het poorten om meer sensoren en actuatoren toe te voegen via een hardware-ecosysteem genaamd [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html).

![Een Seeed Studios Wio Terminal](../../../../../translated_images/nl/wio-terminal.b8299ee16587db9a.webp)

## Installatie

Om de Wio Terminal te gebruiken, moet je gratis software op je computer installeren. Daarnaast moet je de firmware van de Wio Terminal bijwerken voordat je verbinding kunt maken met WiFi.

### Taak - installatie

Installeer de benodigde software en werk de firmware bij.

1. Installeer Visual Studio Code (VS Code). Dit is de editor die je zult gebruiken om je apparaatcode in C/C++ te schrijven. Raadpleeg de [VS Code-documentatie](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) voor instructies over het installeren van VS Code.

    > 💁 Een andere populaire IDE voor Arduino-ontwikkeling is de [Arduino IDE](https://www.arduino.cc/en/software). Als je al bekend bent met deze tool, kun je deze gebruiken in plaats van VS Code en PlatformIO. De lessen geven echter instructies op basis van het gebruik van VS Code.

1. Installeer de VS Code PlatformIO-extensie. Dit is een extensie voor VS Code die ondersteuning biedt voor het programmeren van microcontrollers in C/C++. Raadpleeg de [PlatformIO-extensiedocumentatie](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=platformio.platformio-ide) voor instructies over het installeren van deze extensie in VS Code. Deze extensie is afhankelijk van de Microsoft C/C++-extensie, die automatisch wordt geïnstalleerd wanneer je PlatformIO installeert.

1. Verbind je Wio Terminal met je computer. De Wio Terminal heeft een USB-C-poort aan de onderkant, die moet worden aangesloten op een USB-poort van je computer. De Wio Terminal wordt geleverd met een USB-C naar USB-A-kabel, maar als je computer alleen USB-C-poorten heeft, heb je een USB-C-kabel of een USB-A naar USB-C-adapter nodig.

1. Volg de instructies in de [Wio Terminal Wiki WiFi Overzicht-documentatie](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/) om je Wio Terminal in te stellen en de firmware bij te werken.

## Hello World

Het is gebruikelijk om bij het leren van een nieuwe programmeertaal of technologie een 'Hello World'-applicatie te maken. Dit is een kleine applicatie die bijvoorbeeld de tekst `"Hello World"` uitvoert om te laten zien dat alle tools correct zijn geconfigureerd.

De Hello World-app voor de Wio Terminal zorgt ervoor dat je Visual Studio Code correct hebt geïnstalleerd met PlatformIO en klaar bent voor microcontrollerontwikkeling.

### Maak een PlatformIO-project

De eerste stap is het maken van een nieuw project met PlatformIO, geconfigureerd voor de Wio Terminal.

#### Taak - maak een PlatformIO-project

Maak het PlatformIO-project.

1. Verbind de Wio Terminal met je computer.

1. Start VS Code.

1. Het PlatformIO-pictogram staat in de zijbalk:

    ![De PlatformIO-menuoptie](../../../../../translated_images/nl/vscode-platformio-menu.297be26b9733e5c4.webp)

    Selecteer dit menu-item en kies vervolgens *PIO Home -> Open*.

    ![De PlatformIO-openoptie](../../../../../translated_images/nl/vscode-platformio-home-open.3f9a41bfd3f4da1c.webp)

1. Selecteer op het welkomstscherm de knop **+ New Project**.

    ![De knop voor een nieuw project](../../../../../translated_images/nl/vscode-platformio-welcome-new-button.ba6fc8a4c7b78cc8.webp)

1. Configureer het project in de *Project Wizard*:

    1. Geef je project de naam `nightlight`.

    1. Typ in het *Board*-dropdownmenu `WIO` om de boards te filteren en selecteer *Seeeduino Wio Terminal*.

    1. Laat het *Framework* staan op *Arduino*.

    1. Laat het selectievakje *Use default location* aangevinkt, of vink het uit en kies een locatie voor je project.

    1. Selecteer de knop **Finish**.

    ![De voltooide projectwizard](../../../../../translated_images/nl/vscode-platformio-nightlight-project-wizard.5c64db4da6037420.webp)

    PlatformIO downloadt de benodigde componenten om code voor de Wio Terminal te compileren en maakt je project aan. Dit kan enkele minuten duren.

### Onderzoek het PlatformIO-project

De VS Code-verkenner toont een aantal bestanden en mappen die door de PlatformIO-wizard zijn aangemaakt.

#### Mappen

* `.pio` - deze map bevat tijdelijke gegevens die nodig zijn voor PlatformIO, zoals bibliotheken of gecompileerde code. Het wordt automatisch opnieuw aangemaakt als het wordt verwijderd, en je hoeft dit niet toe te voegen aan versiebeheer als je je project deelt op sites zoals GitHub.
* `.vscode` - deze map bevat de configuratie die door PlatformIO en VS Code wordt gebruikt. Het wordt automatisch opnieuw aangemaakt als het wordt verwijderd, en je hoeft dit niet toe te voegen aan versiebeheer als je je project deelt op sites zoals GitHub.
* `include` - deze map is bedoeld voor externe headerbestanden die nodig zijn bij het toevoegen van extra bibliotheken aan je code. Je zult deze map in geen van deze lessen gebruiken.
* `lib` - deze map is bedoeld voor externe bibliotheken die je vanuit je code wilt aanroepen. Je zult deze map in geen van deze lessen gebruiken.
* `src` - deze map bevat de hoofdbroncode van je applicatie. Aanvankelijk bevat het één bestand: `main.cpp`.
* `test` - deze map is bedoeld voor eventuele unit-tests van je code.

#### Bestanden

* `main.cpp` - dit bestand in de map `src` bevat het startpunt van je applicatie. Open dit bestand, en het bevat de volgende code:

    ```cpp
    #include <Arduino.h>
    
    void setup() {
      // put your setup code here, to run once:
    }
    
    void loop() {
      // put your main code here, to run repeatedly:
    }
    ```

    Wanneer het apparaat wordt opgestart, voert het Arduino-framework de `setup`-functie één keer uit en vervolgens herhaaldelijk de `loop`-functie totdat het apparaat wordt uitgeschakeld.

* `.gitignore` - dit bestand bevat een lijst van bestanden en mappen die moeten worden genegeerd bij het toevoegen van je code aan versiebeheer, zoals bij het uploaden naar een repository op GitHub.

* `platformio.ini` - dit bestand bevat de configuratie voor je apparaat en app. Open dit bestand, en het bevat de volgende code:

    ```ini
    [env:seeed_wio_terminal]
    platform = atmelsam
    board = seeed_wio_terminal
    framework = arduino
    ```

    De sectie `[env:seeed_wio_terminal]` bevat de configuratie voor de Wio Terminal. Je kunt meerdere `env`-secties hebben, zodat je code kan worden gecompileerd voor meerdere boards.

    De andere waarden komen overeen met de configuratie uit de projectwizard:

  * `platform = atmelsam` definieert de hardware die de Wio Terminal gebruikt (een ATSAMD51-gebaseerde microcontroller).
  * `board = seeed_wio_terminal` definieert het type microcontrollerboard (de Wio Terminal).
  * `framework = arduino` geeft aan dat dit project het Arduino-framework gebruikt.

### Schrijf de Hello World-app

Je bent nu klaar om de Hello World-app te schrijven.

#### Taak - schrijf de Hello World-app

Schrijf de Hello World-app.

1. Open het bestand `main.cpp` in VS Code.

1. Wijzig de code zodat deze overeenkomt met het volgende:

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

    De `setup`-functie initialiseert een verbinding met de seriële poort - in dit geval de USB-poort die wordt gebruikt om de Wio Terminal met je computer te verbinden. De parameter `9600` is de [baudrate](https://wikipedia.org/wiki/Symbol_rate) (ook wel symboolsnelheid genoemd), of de snelheid waarmee gegevens over de seriële poort worden verzonden in bits per seconde. Deze instelling betekent dat 9.600 bits (nullen en enen) gegevens per seconde worden verzonden. Vervolgens wacht het tot de seriële poort gereed is.

    De `loop`-functie stuurt de regel `Hello World!` naar de seriële poort, samen met een nieuwe regelkarakter. Vervolgens pauzeert het 5.000 milliseconden of 5 seconden. Nadat de `loop` eindigt, wordt deze opnieuw uitgevoerd, en opnieuw, en zo verder zolang de microcontroller is ingeschakeld.

1. Zet je Wio Terminal in uploadmodus. Dit moet je elke keer doen als je nieuwe code naar het apparaat uploadt:

    1. Schakel de aan/uit-schakelaar twee keer snel naar beneden - deze springt elke keer terug naar de aan-positie.

    1. Controleer de blauwe status-LED aan de rechterkant van de USB-poort. Deze zou moeten pulseren.
    
    [![Een video die laat zien hoe je de Wio Terminal in uploadmodus zet](https://img.youtube.com/vi/LeKU_7zLRrQ/0.jpg)](https://youtu.be/LeKU_7zLRrQ)
    
    Klik op de afbeelding hierboven voor een video die laat zien hoe je dit doet.

1. Bouw en upload de code naar de Wio Terminal.

    1. Open de VS Code-opdrachtpalet.

    1. Typ `PlatformIO Upload` om te zoeken naar de uploadoptie en selecteer *PlatformIO: Upload*.

        ![De PlatformIO-uploadoptie in de opdrachtpalet](../../../../../translated_images/nl/vscode-platformio-upload-command-palette.9e0f49cf80d1f1c3.webp)

        PlatformIO bouwt de code automatisch indien nodig voordat het wordt geüpload.

    1. De code wordt gecompileerd en geüpload naar de Wio Terminal.

        > 💁 Als je macOS gebruikt, verschijnt er een melding over een *SCHIJF NIET CORRECT VERWIJDERD*. Dit komt omdat de Wio Terminal als een schijf wordt gekoppeld tijdens het flashproces en wordt losgekoppeld wanneer de gecompileerde code naar het apparaat wordt geschreven. Je kunt deze melding negeren.

    ⚠️ Als je fouten krijgt over een niet-beschikbare uploadpoort, controleer dan eerst of je de Wio Terminal hebt aangesloten op je computer, hebt ingeschakeld met de schakelaar aan de linkerkant van het scherm en in uploadmodus hebt gezet. Het groene lampje aan de onderkant moet branden en het blauwe lampje moet pulseren. Als je nog steeds de fout krijgt, trek de aan/uit-schakelaar dan opnieuw twee keer snel naar beneden om de Wio Terminal in uploadmodus te forceren en probeer opnieuw te uploaden.

PlatformIO heeft een seriële monitor waarmee je gegevens kunt volgen die via de USB-kabel van de Wio Terminal worden verzonden. Hiermee kun je de gegevens volgen die door het commando `Serial.println("Hello World");` worden verzonden.

1. Open de VS Code-opdrachtpalet.

1. Typ `PlatformIO Serial` om te zoeken naar de seriële monitoroptie en selecteer *PlatformIO: Serial Monitor*.

    ![De PlatformIO-seriële monitoroptie in de opdrachtpalet](../../../../../translated_images/nl/vscode-platformio-serial-monitor-command-palette.b348ec841b8a1c14.webp)

    Er wordt een nieuwe terminal geopend en de gegevens die via de seriële poort worden verzonden, worden in deze terminal gestreamd:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Hello World
    Hello World
    ```

    `Hello World` wordt elke 5 seconden naar de seriële monitor geschreven.

> 💁 Je kunt deze code vinden in de map [code/wio-terminal](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/wio-terminal).

😀 Je 'Hello World'-programma is een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in de oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.