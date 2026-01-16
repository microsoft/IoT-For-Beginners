<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a4f0c166010e31fd7b6ca20bc88dec6d",
  "translation_date": "2025-08-27T22:01:45+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md",
  "language_code": "sv"
}
-->
# Wio Terminal

[Wio Terminal från Seeed Studios](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) är en Arduino-kompatibel mikrokontroller med inbyggd WiFi, sensorer och aktuatorer, samt portar för att lägga till fler sensorer och aktuatorer med hjälp av ett hårdvaruekosystem som kallas [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html).

![En Seeed Studios Wio Terminal](../../../../../translated_images/sv/wio-terminal.b8299ee16587db9a.png)

## Installation

För att använda din Wio Terminal behöver du installera viss gratisprogramvara på din dator. Du måste också uppdatera Wio Terminal-firmware innan du kan ansluta den till WiFi.

### Uppgift - installation

Installera den nödvändiga programvaran och uppdatera firmware.

1. Installera Visual Studio Code (VS Code). Detta är den editor du kommer att använda för att skriva din enhetskod i C/C++. Se [VS Code-dokumentationen](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) för instruktioner om hur du installerar VS Code.

    > 💁 Ett annat populärt IDE för Arduino-utveckling är [Arduino IDE](https://www.arduino.cc/en/software). Om du redan är bekant med detta verktyg kan du använda det istället för VS Code och PlatformIO, men lektionerna kommer att ge instruktioner baserade på användning av VS Code.

1. Installera VS Code PlatformIO-tillägget. Detta är ett tillägg för VS Code som stöder programmering av mikrokontrollers i C/C++. Se [PlatformIO-tilläggsdokumentationen](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=platformio.platformio-ide) för instruktioner om hur du installerar detta tillägg i VS Code. Detta tillägg är beroende av Microsoft C/C++-tillägget för att fungera med C- och C++-kod, och C/C++-tillägget installeras automatiskt när du installerar PlatformIO.

1. Anslut din Wio Terminal till din dator. Wio Terminal har en USB-C-port på undersidan, och denna måste anslutas till en USB-port på din dator. Wio Terminal levereras med en USB-C till USB-A-kabel, men om din dator endast har USB-C-portar behöver du antingen en USB-C-kabel eller en USB-A till USB-C-adapter.

1. Följ instruktionerna i [Wio Terminal Wiki WiFi Overview-dokumentationen](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/) för att konfigurera din Wio Terminal och uppdatera firmware.

## Hello World

Det är traditionellt när man börjar med ett nytt programmeringsspråk eller en ny teknik att skapa en 'Hello World'-applikation – en liten applikation som visar något som texten `"Hello World"` för att visa att alla verktyg är korrekt konfigurerade.

Hello World-appen för Wio Terminal säkerställer att du har Visual Studio Code korrekt installerat med PlatformIO och konfigurerat för mikrokontrollerutveckling.

### Skapa ett PlatformIO-projekt

Det första steget är att skapa ett nytt projekt med PlatformIO konfigurerat för Wio Terminal.

#### Uppgift - skapa ett PlatformIO-projekt

Skapa PlatformIO-projektet.

1. Anslut Wio Terminal till din dator

1. Starta VS Code

1. PlatformIO-ikonen finns i sidomenyn:

    ![Platform IO-menyalternativet](../../../../../translated_images/sv/vscode-platformio-menu.297be26b9733e5c4.png)

    Välj detta menyalternativ och välj sedan *PIO Home -> Open*

    ![Platform IO öppna-alternativet](../../../../../translated_images/sv/vscode-platformio-home-open.3f9a41bfd3f4da1c.png)

1. Från välkomstskärmen, välj knappen **+ New Project**

    ![Knappen för nytt projekt](../../../../../translated_images/sv/vscode-platformio-welcome-new-button.ba6fc8a4c7b78cc8.png)

1. Konfigurera projektet i *Project Wizard*:

    1. Namnge ditt projekt `nightlight`

    1. I rullgardinsmenyn *Board*, skriv in `WIO` för att filtrera korten och välj *Seeeduino Wio Terminal*

    1. Lämna *Framework* som *Arduino*

    1. Antingen lämna kryssrutan *Use default location* markerad eller avmarkera den och välj en plats för ditt projekt

    1. Välj knappen **Finish**

    ![Den färdiga projektguiden](../../../../../translated_images/sv/vscode-platformio-nightlight-project-wizard.5c64db4da6037420.png)

    PlatformIO kommer att ladda ner de komponenter som behövs för att kompilera kod för Wio Terminal och skapa ditt projekt. Detta kan ta några minuter.

### Undersök PlatformIO-projektet

VS Code Explorer visar ett antal filer och mappar som skapats av PlatformIO-guiden.

#### Mappar

* `.pio` - denna mapp innehåller temporära data som behövs av PlatformIO, såsom bibliotek eller kompilerad kod. Den återskapas automatiskt om den raderas, och du behöver inte lägga till denna i versionskontroll om du delar ditt projekt på exempelvis GitHub.
* `.vscode` - denna mapp innehåller konfigurationen som används av PlatformIO och VS Code. Den återskapas automatiskt om den raderas, och du behöver inte lägga till denna i versionskontroll om du delar ditt projekt på exempelvis GitHub.
* `include` - denna mapp är för externa headerfiler som behövs när du lägger till ytterligare bibliotek i din kod. Du kommer inte att använda denna mapp i någon av dessa lektioner.
* `lib` - denna mapp är för externa bibliotek som du vill anropa från din kod. Du kommer inte att använda denna mapp i någon av dessa lektioner.
* `src` - denna mapp innehåller huvudkällkoden för din applikation. Inledningsvis kommer den att innehålla en enda fil - `main.cpp`.
* `test` - denna mapp är där du skulle lägga eventuella enhetstester för din kod.

#### Filer

* `main.cpp` - denna fil i `src`-mappen innehåller startpunkten för din applikation. Öppna denna fil, och den kommer att innehålla följande kod:

    ```cpp
    #include <Arduino.h>
    
    void setup() {
      // put your setup code here, to run once:
    }
    
    void loop() {
      // put your main code here, to run repeatedly:
    }
    ```

    När enheten startar kommer Arduino-ramverket att köra funktionen `setup` en gång och sedan köra funktionen `loop` upprepade gånger tills enheten stängs av.

* `.gitignore` - denna fil listar de filer och kataloger som ska ignoreras när du lägger till din kod i git versionskontroll, såsom uppladdning till ett repository på GitHub.

* `platformio.ini` - denna fil innehåller konfiguration för din enhet och app. Öppna denna fil, och den kommer att innehålla följande kod:

    ```ini
    [env:seeed_wio_terminal]
    platform = atmelsam
    board = seeed_wio_terminal
    framework = arduino
    ```

    Sektionen `[env:seeed_wio_terminal]` har konfiguration för Wio Terminal. Du kan ha flera `env`-sektioner så att din kod kan kompileras för flera kort.

    De andra värdena matchar konfigurationen från projektguiden:

  * `platform = atmelsam` definierar hårdvaran som Wio Terminal använder (en ATSAMD51-baserad mikrokontroller)
  * `board = seeed_wio_terminal` definierar typen av mikrokontrollerkort (Wio Terminal)
  * `framework = arduino` definierar att detta projekt använder Arduino-ramverket.

### Skriv Hello World-appen

Nu är du redo att skriva Hello World-appen.

#### Uppgift - skriv Hello World-appen

Skriv Hello World-appen.

1. Öppna filen `main.cpp` i VS Code

1. Ändra koden så att den matchar följande:

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

    Funktionen `setup` initierar en anslutning till seriella porten – i detta fall USB-porten som används för att ansluta Wio Terminal till din dator. Parametern `9600` är [baudhastigheten](https://wikipedia.org/wiki/Symbol_rate) (även känd som symbolhastighet), eller hastigheten som data skickas över seriella porten i bitar per sekund. Denna inställning innebär att 9 600 bitar (0:or och 1:or) data skickas varje sekund. Den väntar sedan på att seriella porten ska vara redo.

    Funktionen `loop` skickar raden `Hello World!` till seriella porten, så att tecknen `Hello World!` tillsammans med ett nytt radtecken skickas. Den sover sedan i 5 000 millisekunder eller 5 sekunder. Efter att `loop` avslutas körs den igen, och igen, och så vidare så länge mikrokontrollern är påslagen.

1. Sätt din Wio Terminal i uppladdningsläge. Du måste göra detta varje gång du laddar upp ny kod till enheten:

    1. Dra ner strömbrytaren två gånger snabbt – den kommer att fjädra tillbaka till på-läget varje gång.

    1. Kontrollera den blå status-LED-lampan till höger om USB-porten. Den ska pulsera.
    
    [![En video som visar hur man sätter Wio Terminal i uppladdningsläge](https://img.youtube.com/vi/LeKU_7zLRrQ/0.jpg)](https://youtu.be/LeKU_7zLRrQ)
    
    Klicka på bilden ovan för en video som visar hur man gör detta.

1. Bygg och ladda upp koden till Wio Terminal

    1. Öppna VS Code-kommandopaletten

    1. Skriv `PlatformIO Upload` för att söka efter uppladdningsalternativet och välj *PlatformIO: Upload*

        ![PlatformIO uppladdningsalternativ i kommandopaletten](../../../../../translated_images/sv/vscode-platformio-upload-command-palette.9e0f49cf80d1f1c3.png)

        PlatformIO kommer automatiskt att bygga koden om det behövs innan uppladdning.

    1. Koden kommer att kompileras och laddas upp till Wio Terminal

        > 💁 Om du använder macOS kommer en notis om *DISK NOT EJECTED PROPERLY* att visas. Detta beror på att Wio Terminal monteras som en enhet som en del av flashprocessen, och den kopplas bort när den kompilerade koden skrivs till enheten. Du kan ignorera denna notis.

    ⚠️ Om du får felmeddelanden om att uppladdningsporten inte är tillgänglig, kontrollera först att du har Wio Terminal ansluten till din dator och påslagen med strömbrytaren på vänster sida av skärmen, och inställd i uppladdningsläge. Den gröna lampan på undersidan ska vara tänd, och den blå lampan ska pulsera. Om du fortfarande får felet, dra strömbrytaren ner två gånger snabbt igen för att tvinga Wio Terminal i uppladdningsläge och försök uppladdningen igen.

PlatformIO har en Serial Monitor som kan övervaka data som skickas över USB-kabeln från Wio Terminal. Detta gör att du kan övervaka data som skickas av `Serial.println("Hello World");`-kommandot.

1. Öppna VS Code-kommandopaletten

1. Skriv `PlatformIO Serial` för att söka efter Serial Monitor-alternativet och välj *PlatformIO: Serial Monitor*

    ![PlatformIO Serial Monitor-alternativ i kommandopaletten](../../../../../translated_images/sv/vscode-platformio-serial-monitor-command-palette.b348ec841b8a1c14.png)

    En ny terminal öppnas, och data som skickas över seriella porten kommer att strömmas in i denna terminal:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Hello World
    Hello World
    ```

    `Hello World` kommer att skrivas ut i seriella monitorn var 5:e sekund.

> 💁 Du kan hitta denna kod i [code/wio-terminal](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/wio-terminal)-mappen.

😀 Din 'Hello World'-applikation lyckades!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiska översättningar kan innehålla fel eller inexaktheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.