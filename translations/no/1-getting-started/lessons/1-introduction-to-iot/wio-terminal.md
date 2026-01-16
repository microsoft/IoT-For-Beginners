<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a4f0c166010e31fd7b6ca20bc88dec6d",
  "translation_date": "2025-08-27T22:02:53+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md",
  "language_code": "no"
}
-->
# Wio Terminal

[Wio Terminal fra Seeed Studios](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) er en Arduino-kompatibel mikrokontroller med innebygd WiFi, sensorer og aktuatorer, samt porter for å legge til flere sensorer og aktuatorer ved hjelp av et maskinvareøkosystem kalt [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html).

![En Seeed Studios Wio Terminal](../../../../../translated_images/no/wio-terminal.b8299ee16587db9a.webp)

## Oppsett

For å bruke din Wio Terminal må du installere gratis programvare på datamaskinen din. Du må også oppdatere Wio Terminal-firmware før du kan koble den til WiFi.

### Oppgave - oppsett

Installer nødvendig programvare og oppdater firmware.

1. Installer Visual Studio Code (VS Code). Dette er editoren du vil bruke til å skrive kode for enheten din i C/C++. Se [VS Code-dokumentasjonen](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) for instruksjoner om hvordan du installerer VS Code.

    > 💁 En annen populær IDE for Arduino-utvikling er [Arduino IDE](https://www.arduino.cc/en/software). Hvis du allerede er kjent med dette verktøyet, kan du bruke det i stedet for VS Code og PlatformIO, men leksjonene vil gi instruksjoner basert på bruk av VS Code.

1. Installer VS Code PlatformIO-utvidelsen. Dette er en utvidelse for VS Code som støtter programmering av mikrokontrollere i C/C++. Se [PlatformIO-utvidelsesdokumentasjonen](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=platformio.platformio-ide) for instruksjoner om hvordan du installerer denne utvidelsen i VS Code. Denne utvidelsen er avhengig av Microsoft C/C++-utvidelsen for å fungere med C- og C++-kode, og C/C++-utvidelsen installeres automatisk når du installerer PlatformIO.

1. Koble din Wio Terminal til datamaskinen. Wio Terminal har en USB-C-port på bunnen, og denne må kobles til en USB-port på datamaskinen din. Wio Terminal leveres med en USB-C til USB-A-kabel, men hvis datamaskinen din bare har USB-C-porter, trenger du enten en USB-C-kabel eller en USB-A til USB-C-adapter.

1. Følg instruksjonene i [Wio Terminal Wiki WiFi Overview-dokumentasjonen](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/) for å sette opp din Wio Terminal og oppdatere firmware.

## Hello world

Det er tradisjonelt når man starter med et nytt programmeringsspråk eller teknologi å lage en 'Hello World'-applikasjon – en liten applikasjon som viser tekst som `"Hello World"` for å bekrefte at alle verktøyene er riktig konfigurert.

Hello World-appen for Wio Terminal vil sikre at du har installert Visual Studio Code korrekt med PlatformIO og satt opp for mikrokontrollerutvikling.

### Opprett et PlatformIO-prosjekt

Første steg er å opprette et nytt prosjekt ved hjelp av PlatformIO konfigurert for Wio Terminal.

#### Oppgave - opprett et PlatformIO-prosjekt

Opprett PlatformIO-prosjektet.

1. Koble Wio Terminal til datamaskinen din

1. Start VS Code

1. PlatformIO-ikonet vil være på sidemenyen:

    ![Platform IO-menyvalget](../../../../../translated_images/no/vscode-platformio-menu.297be26b9733e5c4.webp)

    Velg dette menyvalget, og deretter *PIO Home -> Open*

    ![Platform IO-åpningsvalget](../../../../../translated_images/no/vscode-platformio-home-open.3f9a41bfd3f4da1c.webp)

1. Fra velkomstskjermen, velg **+ New Project**-knappen

    ![Ny prosjekt-knapp](../../../../../translated_images/no/vscode-platformio-welcome-new-button.ba6fc8a4c7b78cc8.webp)

1. Konfigurer prosjektet i *Project Wizard*:

    1. Navngi prosjektet ditt `nightlight`

    1. Fra *Board*-nedtrekksmenyen, skriv inn `WIO` for å filtrere kortene, og velg *Seeeduino Wio Terminal*

    1. La *Framework* stå som *Arduino*

    1. Enten la *Use default location*-avkrysningsboksen være krysset av, eller fjern krysset og velg en plassering for prosjektet ditt

    1. Velg **Finish**-knappen

    ![Fullført prosjektveiviser](../../../../../translated_images/no/vscode-platformio-nightlight-project-wizard.5c64db4da6037420.webp)

    PlatformIO vil laste ned komponentene det trenger for å kompilere kode for Wio Terminal og opprette prosjektet ditt. Dette kan ta noen minutter.

### Utforsk PlatformIO-prosjektet

VS Code Explorer vil vise en rekke filer og mapper opprettet av PlatformIO-veiviseren.

#### Mapper

* `.pio` - denne mappen inneholder midlertidige data som trengs av PlatformIO, som biblioteker eller kompilert kode. Den opprettes automatisk på nytt hvis den slettes, og du trenger ikke legge denne til kildekodekontroll hvis du deler prosjektet ditt på nettsteder som GitHub.
* `.vscode` - denne mappen inneholder konfigurasjonen brukt av PlatformIO og VS Code. Den opprettes automatisk på nytt hvis den slettes, og du trenger ikke legge denne til kildekodekontroll hvis du deler prosjektet ditt på nettsteder som GitHub.
* `include` - denne mappen er for eksterne header-filer som trengs når du legger til ekstra biblioteker i koden din. Du vil ikke bruke denne mappen i noen av disse leksjonene.
* `lib` - denne mappen er for eksterne biblioteker som du vil kalle fra koden din. Du vil ikke bruke denne mappen i noen av disse leksjonene.
* `src` - denne mappen inneholder hovedkildekoden for applikasjonen din. Opprinnelig vil den inneholde én fil - `main.cpp`.
* `test` - denne mappen er der du kan legge eventuelle enhetstester for koden din.

#### Filer

* `main.cpp` - denne filen i `src`-mappen inneholder startpunktet for applikasjonen din. Åpne denne filen, og den vil inneholde følgende kode:

    ```cpp
    #include <Arduino.h>
    
    void setup() {
      // put your setup code here, to run once:
    }
    
    void loop() {
      // put your main code here, to run repeatedly:
    }
    ```

    Når enheten starter opp, vil Arduino-rammeverket kjøre `setup`-funksjonen én gang, og deretter kjøre `loop`-funksjonen gjentatte ganger til enheten slås av.

* `.gitignore` - denne filen lister opp filer og kataloger som skal ignoreres når du legger koden din til git kildekodekontroll, som for eksempel opplasting til et GitHub-repositorium.

* `platformio.ini` - denne filen inneholder konfigurasjon for enheten og appen din. Åpne denne filen, og den vil inneholde følgende kode:

    ```ini
    [env:seeed_wio_terminal]
    platform = atmelsam
    board = seeed_wio_terminal
    framework = arduino
    ```

    Seksjonen `[env:seeed_wio_terminal]` har konfigurasjon for Wio Terminal. Du kan ha flere `env`-seksjoner slik at koden din kan kompileres for flere kort.

    De andre verdiene samsvarer med konfigurasjonen fra prosjektveiviseren:

  * `platform = atmelsam` definerer maskinvaren som Wio Terminal bruker (en ATSAMD51-basert mikrokontroller)
  * `board = seeed_wio_terminal` definerer typen mikrokontrollerkort (Wio Terminal)
  * `framework = arduino` definerer at dette prosjektet bruker Arduino-rammeverket.

### Skriv Hello World-appen

Du er nå klar til å skrive Hello World-appen.

#### Oppgave - skriv Hello World-appen

Skriv Hello World-appen.

1. Åpne `main.cpp`-filen i VS Code

1. Endre koden til å samsvare med følgende:

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

    `setup`-funksjonen initialiserer en tilkobling til den serielle porten – i dette tilfellet USB-porten som brukes til å koble Wio Terminal til datamaskinen din. Parameteren `9600` er [baud rate](https://wikipedia.org/wiki/Symbol_rate) (også kjent som symbolrate), eller hastigheten som data sendes over den serielle porten i biter per sekund. Denne innstillingen betyr at 9,600 biter (0-er og 1-ere) av data sendes hvert sekund. Den venter deretter på at den serielle porten skal være klar.

    `loop`-funksjonen sender linjen `Hello World!` til den serielle porten, slik at tegnene `Hello World!` sammen med et linjeskift sendes. Den sover deretter i 5,000 millisekunder eller 5 sekunder. Etter at `loop` avsluttes, kjøres den igjen, og igjen, og så videre hele tiden mens mikrokontrolleren er slått på.

1. Sett Wio Terminal i opplastingsmodus. Du må gjøre dette hver gang du laster opp ny kode til enheten:

    1. Skyv strømbryteren ned to ganger raskt – den vil sprette tilbake til på-posisjonen hver gang.

    1. Sjekk den blå status-LED-en til høyre for USB-porten. Den skal pulsere.
    
    [![En video som viser hvordan du setter Wio Terminal i opplastingsmodus](https://img.youtube.com/vi/LeKU_7zLRrQ/0.jpg)](https://youtu.be/LeKU_7zLRrQ)
    
    Klikk på bildet over for en video som viser hvordan du gjør dette.

1. Bygg og last opp koden til Wio Terminal

    1. Åpne VS Code-kommandopaletten

    1. Skriv `PlatformIO Upload` for å søke etter opplastingsvalget, og velg *PlatformIO: Upload*

        ![PlatformIO-opplastingsvalget i kommandopaletten](../../../../../translated_images/no/vscode-platformio-upload-command-palette.9e0f49cf80d1f1c3.webp)

        PlatformIO vil automatisk bygge koden hvis nødvendig før opplasting.

    1. Koden vil bli kompilert og lastet opp til Wio Terminal

        > 💁 Hvis du bruker macOS, vil en melding om *DISK NOT EJECTED PROPERLY* vises. Dette skyldes at Wio Terminal blir montert som en stasjon som en del av flash-prosessen, og den kobles fra når den kompilerte koden skrives til enheten. Du kan ignorere denne meldingen.

    ⚠️ Hvis du får feil om at opplastingsporten ikke er tilgjengelig, må du først sørge for at Wio Terminal er koblet til datamaskinen din, slått på med bryteren på venstre side av skjermen, og satt i opplastingsmodus. Det grønne lyset på bunnen skal være på, og det blå lyset skal pulsere. Hvis du fortsatt får feilen, skyv på/av-bryteren ned to ganger raskt igjen for å tvinge Wio Terminal inn i opplastingsmodus og prøv opplastingen på nytt.

PlatformIO har en Serial Monitor som kan overvåke data sendt over USB-kabelen fra Wio Terminal. Dette lar deg overvåke data sendt av `Serial.println("Hello World");`-kommandoen.

1. Åpne VS Code-kommandopaletten

1. Skriv `PlatformIO Serial` for å søke etter Serial Monitor-valget, og velg *PlatformIO: Serial Monitor*

    ![PlatformIO Serial Monitor-valget i kommandopaletten](../../../../../translated_images/no/vscode-platformio-serial-monitor-command-palette.b348ec841b8a1c14.webp)

    En ny terminal vil åpne seg, og data sendt over den serielle porten vil bli strømmet inn i denne terminalen:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Hello World
    Hello World
    ```

    `Hello World` vil skrives ut til den serielle monitoren hvert 5. sekund.

> 💁 Du finner denne koden i [code/wio-terminal](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/wio-terminal)-mappen.

😀 Din 'Hello World'-program var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.