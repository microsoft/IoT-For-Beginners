<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a4f0c166010e31fd7b6ca20bc88dec6d",
  "translation_date": "2025-08-27T22:02:21+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md",
  "language_code": "da"
}
-->
# Wio Terminal

[Wio Terminal fra Seeed Studios](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) er en Arduino-kompatibel mikrocontroller med indbygget WiFi, sensorer og aktuatorer samt porte til at tilføje flere sensorer og aktuatorer via et hardwareøkosystem kaldet [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html).

![En Seeed Studios Wio Terminal](../../../../../translated_images/da/wio-terminal.b8299ee16587db9a.png)

## Opsætning

For at bruge din Wio Terminal skal du installere noget gratis software på din computer. Du skal også opdatere Wio Terminal-firmwaren, før du kan forbinde den til WiFi.

### Opgave - opsætning

Installer den nødvendige software og opdater firmwaren.

1. Installer Visual Studio Code (VS Code). Dette er den editor, du vil bruge til at skrive din enhedskode i C/C++. Se [VS Code-dokumentationen](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) for instruktioner om installation af VS Code.

    > 💁 En anden populær IDE til Arduino-udvikling er [Arduino IDE](https://www.arduino.cc/en/software). Hvis du allerede er bekendt med dette værktøj, kan du bruge det i stedet for VS Code og PlatformIO, men lektionerne vil give instruktioner baseret på brugen af VS Code.

1. Installer VS Code PlatformIO-udvidelsen. Dette er en udvidelse til VS Code, der understøtter programmering af mikrocontrollere i C/C++. Se [PlatformIO-udvidelsesdokumentationen](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=platformio.platformio-ide) for instruktioner om installation af denne udvidelse i VS Code. Denne udvidelse afhænger af Microsoft C/C++-udvidelsen for at arbejde med C- og C++-kode, og C/C++-udvidelsen installeres automatisk, når du installerer PlatformIO.

1. Tilslut din Wio Terminal til din computer. Wio Terminal har en USB-C-port i bunden, som skal forbindes til en USB-port på din computer. Wio Terminal leveres med et USB-C til USB-A-kabel, men hvis din computer kun har USB-C-porte, skal du enten bruge et USB-C-kabel eller en USB-A til USB-C-adapter.

1. Følg instruktionerne i [Wio Terminal Wiki WiFi Overview-dokumentationen](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/) for at opsætte din Wio Terminal og opdatere firmwaren.

## Hello World

Det er traditionelt, når man starter med et nyt programmeringssprog eller en ny teknologi, at lave en 'Hello World'-applikation - en lille applikation, der viser tekst som `"Hello World"` for at sikre, at alle værktøjer er korrekt konfigureret.

Hello World-appen til Wio Terminal vil sikre, at du har Visual Studio Code korrekt installeret med PlatformIO og opsat til mikrocontrollerudvikling.

### Opret et PlatformIO-projekt

Det første skridt er at oprette et nyt projekt ved hjælp af PlatformIO, konfigureret til Wio Terminal.

#### Opgave - opret et PlatformIO-projekt

Opret PlatformIO-projektet.

1. Tilslut Wio Terminal til din computer

1. Start VS Code

1. PlatformIO-ikonet vil være på sidemenuen:

    ![PlatformIO-menuvalgmuligheden](../../../../../translated_images/da/vscode-platformio-menu.297be26b9733e5c4.png)

    Vælg dette menuemne, og vælg derefter *PIO Home -> Open*

    ![PlatformIO-åbningsvalgmuligheden](../../../../../translated_images/da/vscode-platformio-home-open.3f9a41bfd3f4da1c.png)

1. Fra velkomstskærmen skal du vælge knappen **+ New Project**

    ![Knappen til nyt projekt](../../../../../translated_images/da/vscode-platformio-welcome-new-button.ba6fc8a4c7b78cc8.png)

1. Konfigurer projektet i *Project Wizard*:

    1. Navngiv dit projekt `nightlight`

    1. Fra *Board*-dropdownmenuen skal du skrive `WIO` for at filtrere boards og vælge *Seeeduino Wio Terminal*

    1. Lad *Framework* være *Arduino*

    1. Enten lad *Use default location*-afkrydsningsfeltet være markeret, eller fjern markeringen og vælg en placering til dit projekt

    1. Vælg knappen **Finish**

    ![Den færdige projektguide](../../../../../translated_images/da/vscode-platformio-nightlight-project-wizard.5c64db4da6037420.png)

    PlatformIO vil downloade de komponenter, der er nødvendige for at kompilere kode til Wio Terminal og oprette dit projekt. Dette kan tage et par minutter.

### Undersøg PlatformIO-projektet

VS Code-udforskeren vil vise en række filer og mapper, der er oprettet af PlatformIO-guiden.

#### Mapper

* `.pio` - denne mappe indeholder midlertidige data, der er nødvendige for PlatformIO, såsom biblioteker eller kompileret kode. Den genskabes automatisk, hvis den slettes, og du behøver ikke tilføje den til kildekodekontrol, hvis du deler dit projekt på sider som GitHub.
* `.vscode` - denne mappe indeholder konfigurationen, der bruges af PlatformIO og VS Code. Den genskabes automatisk, hvis den slettes, og du behøver ikke tilføje den til kildekodekontrol, hvis du deler dit projekt på sider som GitHub.
* `include` - denne mappe er til eksterne headerfiler, der er nødvendige, når du tilføjer yderligere biblioteker til din kode. Du vil ikke bruge denne mappe i nogen af disse lektioner.
* `lib` - denne mappe er til eksterne biblioteker, som du vil kalde fra din kode. Du vil ikke bruge denne mappe i nogen af disse lektioner.
* `src` - denne mappe indeholder hovedkildekoden til din applikation. Oprindeligt vil den indeholde en enkelt fil - `main.cpp`.
* `test` - denne mappe er, hvor du vil placere eventuelle enhedstests for din kode.

#### Filer

* `main.cpp` - denne fil i `src`-mappen indeholder indgangspunktet for din applikation. Åbn denne fil, og den vil indeholde følgende kode:

    ```cpp
    #include <Arduino.h>
    
    void setup() {
      // put your setup code here, to run once:
    }
    
    void loop() {
      // put your main code here, to run repeatedly:
    }
    ```

    Når enheden starter op, vil Arduino-frameworket køre `setup`-funktionen én gang og derefter køre `loop`-funktionen gentagne gange, indtil enheden slukkes.

* `.gitignore` - denne fil lister de filer og mapper, der skal ignoreres, når du tilføjer din kode til git kildekodekontrol, såsom upload til et repository på GitHub.

* `platformio.ini` - denne fil indeholder konfigurationen for din enhed og app. Åbn denne fil, og den vil indeholde følgende kode:

    ```ini
    [env:seeed_wio_terminal]
    platform = atmelsam
    board = seeed_wio_terminal
    framework = arduino
    ```

    Sektionen `[env:seeed_wio_terminal]` har konfigurationen for Wio Terminal. Du kan have flere `env`-sektioner, så din kode kan kompileres til flere boards.

    De øvrige værdier matcher konfigurationen fra projektguiden:

  * `platform = atmelsam` definerer den hardware, som Wio Terminal bruger (en ATSAMD51-baseret mikrocontroller)
  * `board = seeed_wio_terminal` definerer typen af mikrocontrollerboard (Wio Terminal)
  * `framework = arduino` definerer, at dette projekt bruger Arduino-frameworket.

### Skriv Hello World-appen

Du er nu klar til at skrive Hello World-appen.

#### Opgave - skriv Hello World-appen

Skriv Hello World-appen.

1. Åbn filen `main.cpp` i VS Code

1. Ændr koden, så den matcher følgende:

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

    `setup`-funktionen initialiserer en forbindelse til den serielle port - i dette tilfælde USB-porten, der bruges til at forbinde Wio Terminal til din computer. Parameteren `9600` er [baudraten](https://wikipedia.org/wiki/Symbol_rate), eller hastigheden, som data sendes over den serielle port i bits per sekund. Denne indstilling betyder, at 9.600 bits (0'er og 1'er) data sendes hvert sekund. Den venter derefter på, at den serielle port er klar.

    `loop`-funktionen sender linjen `Hello World!` til den serielle port, så tegnene `Hello World!` sammen med et linjeskift. Den sover derefter i 5.000 millisekunder eller 5 sekunder. Efter `loop` afsluttes, køres den igen og igen, så længe mikrocontrolleren er tændt.

1. Sæt din Wio Terminal i upload-tilstand. Du skal gøre dette hver gang, du uploader ny kode til enheden:

    1. Træk hurtigt ned to gange på tænd/sluk-knappen - den springer tilbage til tændt position hver gang.

    1. Tjek den blå status-LED til højre for USB-porten. Den skal pulsere.
    
    [![En video, der viser, hvordan man sætter Wio Terminal i upload-tilstand](https://img.youtube.com/vi/LeKU_7zLRrQ/0.jpg)](https://youtu.be/LeKU_7zLRrQ)
    
    Klik på billedet ovenfor for en video, der viser, hvordan man gør dette.

1. Byg og upload koden til Wio Terminal

    1. Åbn VS Code-kommandopaletten

    1. Skriv `PlatformIO Upload` for at søge efter upload-muligheden, og vælg *PlatformIO: Upload*

        ![PlatformIO-upload-muligheden i kommandopaletten](../../../../../translated_images/da/vscode-platformio-upload-command-palette.9e0f49cf80d1f1c3.png)

        PlatformIO vil automatisk bygge koden, hvis det er nødvendigt, før den uploades.

    1. Koden vil blive kompileret og uploadet til Wio Terminal

        > 💁 Hvis du bruger macOS, vil en notifikation om *DISK NOT EJECTED PROPERLY* dukke op. Dette skyldes, at Wio Terminal bliver monteret som et drev som en del af flash-processen, og det afbrydes, når den kompilerede kode skrives til enheden. Du kan ignorere denne notifikation.

    ⚠️ Hvis du får fejl om, at upload-porten ikke er tilgængelig, skal du først sikre dig, at du har Wio Terminal tilsluttet din computer, tændt med kontakten på venstre side af skærmen og sat i upload-tilstand. Det grønne lys i bunden skal være tændt, og det blå lys skal pulsere. Hvis du stadig får fejlen, skal du trække tænd/sluk-knappen ned to gange hurtigt igen for at tvinge Wio Terminal i upload-tilstand og prøve uploaden igen.

PlatformIO har en Serial Monitor, der kan overvåge data sendt over USB-kablet fra Wio Terminal. Dette giver dig mulighed for at overvåge de data, der sendes af `Serial.println("Hello World");`-kommandoen.

1. Åbn VS Code-kommandopaletten

1. Skriv `PlatformIO Serial` for at søge efter Serial Monitor-muligheden, og vælg *PlatformIO: Serial Monitor*

    ![PlatformIO Serial Monitor-muligheden i kommandopaletten](../../../../../translated_images/da/vscode-platformio-serial-monitor-command-palette.b348ec841b8a1c14.png)

    Et nyt terminalvindue åbnes, og data sendt over den serielle port vil blive streamet ind i dette terminalvindue:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Hello World
    Hello World
    ```

    `Hello World` vil blive printet til den serielle monitor hvert 5. sekund.

> 💁 Du kan finde denne kode i [code/wio-terminal](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/wio-terminal)-mappen.

😀 Din 'Hello World'-program var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.