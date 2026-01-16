<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a4f0c166010e31fd7b6ca20bc88dec6d",
  "translation_date": "2025-08-27T22:25:12+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md",
  "language_code": "cs"
}
-->
# Wio Terminal

[Wio Terminal od Seeed Studios](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) je mikrokontrolér kompatibilní s Arduino, který má vestavěné WiFi, několik senzorů a akčních členů, a také porty pro připojení dalších senzorů a akčních členů pomocí hardwarového ekosystému zvaného [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html).

![Wio Terminal od Seeed Studios](../../../../../translated_images/cs/wio-terminal.b8299ee16587db9a.webp)

## Nastavení

Abyste mohli používat Wio Terminal, budete muset nainstalovat bezplatný software na svůj počítač. Také bude nutné aktualizovat firmware Wio Terminalu, než jej připojíte k WiFi.

### Úkol - nastavení

Nainstalujte požadovaný software a aktualizujte firmware.

1. Nainstalujte Visual Studio Code (VS Code). To je editor, který budete používat k psaní kódu pro zařízení v jazyce C/C++. Pokyny k instalaci VS Code najdete v [dokumentaci k VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

    > 💁 Dalším oblíbeným IDE pro vývoj v Arduino je [Arduino IDE](https://www.arduino.cc/en/software). Pokud již tento nástroj znáte, můžete jej použít místo VS Code a PlatformIO, ale lekce budou obsahovat pokyny založené na použití VS Code.

1. Nainstalujte rozšíření PlatformIO pro VS Code. Toto rozšíření podporuje programování mikrokontrolérů v jazyce C/C++. Pokyny k instalaci tohoto rozšíření najdete v [dokumentaci k rozšíření PlatformIO](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=platformio.platformio-ide). Toto rozšíření závisí na rozšíření Microsoft C/C++, které se automaticky nainstaluje při instalaci PlatformIO.

1. Připojte Wio Terminal k počítači. Wio Terminal má na spodní straně port USB-C, který je třeba připojit k USB portu na vašem počítači. Wio Terminal je dodáván s kabelem USB-C na USB-A, ale pokud váš počítač má pouze USB-C porty, budete potřebovat buď USB-C kabel, nebo adaptér USB-A na USB-C.

1. Postupujte podle pokynů v [dokumentaci Wio Terminal Wiki WiFi Overview](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/) pro nastavení Wio Terminalu a aktualizaci firmwaru.

## Hello world

Je tradicí při začátcích s novým programovacím jazykem nebo technologií vytvořit aplikaci 'Hello World' – malou aplikaci, která vypíše text jako `"Hello World"`, aby se ověřilo, že všechny nástroje jsou správně nastaveny.

Aplikace Hello World pro Wio Terminal zajistí, že máte správně nainstalovaný Visual Studio Code s PlatformIO a nastavený pro vývoj mikrokontrolérů.

### Vytvoření projektu PlatformIO

Prvním krokem je vytvoření nového projektu pomocí PlatformIO nakonfigurovaného pro Wio Terminal.

#### Úkol - vytvoření projektu PlatformIO

Vytvořte projekt PlatformIO.

1. Připojte Wio Terminal k počítači.

1. Spusťte VS Code.

1. Na bočním panelu se zobrazí ikona PlatformIO:

    ![Možnost menu PlatformIO](../../../../../translated_images/cs/vscode-platformio-menu.297be26b9733e5c4.webp)

    Vyberte tuto položku menu a poté vyberte *PIO Home -> Open*.

    ![Možnost otevření PlatformIO](../../../../../translated_images/cs/vscode-platformio-home-open.3f9a41bfd3f4da1c.webp)

1. Na uvítací obrazovce vyberte tlačítko **+ New Project**.

    ![Tlačítko pro nový projekt](../../../../../translated_images/cs/vscode-platformio-welcome-new-button.ba6fc8a4c7b78cc8.webp)

1. Nakonfigurujte projekt v *Průvodci projektem*:

    1. Pojmenujte svůj projekt `nightlight`.

    1. V rozbalovacím seznamu *Board* napište `WIO` pro filtrování desek a vyberte *Seeeduino Wio Terminal*.

    1. Nechte *Framework* nastavený na *Arduino*.

    1. Buď ponechte zaškrtnuté políčko *Use default location*, nebo jej odškrtněte a vyberte umístění pro svůj projekt.

    1. Vyberte tlačítko **Finish**.

    ![Dokončený průvodce projektem](../../../../../translated_images/cs/vscode-platformio-nightlight-project-wizard.5c64db4da6037420.webp)

    PlatformIO stáhne komponenty potřebné ke kompilaci kódu pro Wio Terminal a vytvoří váš projekt. Tento proces může trvat několik minut.

### Prozkoumání projektu PlatformIO

Průzkumník VS Code zobrazí několik souborů a složek vytvořených průvodcem PlatformIO.

#### Složky

* `.pio` - tato složka obsahuje dočasná data potřebná pro PlatformIO, jako jsou knihovny nebo zkompilovaný kód. Pokud ji smažete, automaticky se znovu vytvoří, a není třeba ji přidávat do správy zdrojového kódu, pokud sdílíte svůj projekt na stránkách jako GitHub.
* `.vscode` - tato složka obsahuje konfiguraci používanou PlatformIO a VS Code. Pokud ji smažete, automaticky se znovu vytvoří, a není třeba ji přidávat do správy zdrojového kódu, pokud sdílíte svůj projekt na stránkách jako GitHub.
* `include` - tato složka je určena pro externí hlavičkové soubory potřebné při přidávání dalších knihoven do vašeho kódu. V těchto lekcích tuto složku nebudete používat.
* `lib` - tato složka je určena pro externí knihovny, které chcete volat ze svého kódu. V těchto lekcích tuto složku nebudete používat.
* `src` - tato složka obsahuje hlavní zdrojový kód vaší aplikace. Zpočátku bude obsahovat jediný soubor - `main.cpp`.
* `test` - tato složka je určena pro umístění jednotkových testů vašeho kódu.

#### Soubory

* `main.cpp` - tento soubor ve složce `src` obsahuje vstupní bod vaší aplikace. Otevřete tento soubor, který bude obsahovat následující kód:

    ```cpp
    #include <Arduino.h>
    
    void setup() {
      // put your setup code here, to run once:
    }
    
    void loop() {
      // put your main code here, to run repeatedly:
    }
    ```

    Když se zařízení spustí, framework Arduino spustí funkci `setup` jednou, poté opakovaně spouští funkci `loop`, dokud není zařízení vypnuto.

* `.gitignore` - tento soubor obsahuje seznam souborů a složek, které mají být ignorovány při přidávání vašeho kódu do správy zdrojového kódu, například při nahrávání do repozitáře na GitHubu.

* `platformio.ini` - tento soubor obsahuje konfiguraci pro vaše zařízení a aplikaci. Otevřete tento soubor, který bude obsahovat následující kód:

    ```ini
    [env:seeed_wio_terminal]
    platform = atmelsam
    board = seeed_wio_terminal
    framework = arduino
    ```

    Sekce `[env:seeed_wio_terminal]` obsahuje konfiguraci pro Wio Terminal. Můžete mít více sekcí `env`, takže váš kód může být kompilován pro více desek.

    Ostatní hodnoty odpovídají konfiguraci z průvodce projektem:

  * `platform = atmelsam` definuje hardware, který Wio Terminal používá (mikrokontrolér založený na ATSAMD51).
  * `board = seeed_wio_terminal` definuje typ desky mikrokontroléru (Wio Terminal).
  * `framework = arduino` definuje, že tento projekt používá framework Arduino.

### Napsání aplikace Hello World

Nyní jste připraveni napsat aplikaci Hello World.

#### Úkol - napsání aplikace Hello World

Napište aplikaci Hello World.

1. Otevřete soubor `main.cpp` ve VS Code.

1. Změňte kód tak, aby odpovídal následujícímu:

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

    Funkce `setup` inicializuje připojení k sériovému portu – v tomto případě k USB portu, který se používá k připojení Wio Terminalu k vašemu počítači. Parametr `9600` je [baudová rychlost](https://wikipedia.org/wiki/Symbol_rate) (také známá jako symbolová rychlost), což je rychlost, jakou budou data odesílána přes sériový port v bitech za sekundu. Toto nastavení znamená, že se každou sekundu odešle 9 600 bitů (0 a 1) dat. Poté čeká, až bude sériový port připraven.

    Funkce `loop` odešle řádek `Hello World!` na sériový port, tedy znaky `Hello World!` spolu s novým řádkem. Poté usne na 5 000 milisekund, tedy 5 sekund. Po skončení funkce `loop` se znovu spustí, a tak stále dokola, dokud je mikrokontrolér zapnutý.

1. Uveďte Wio Terminal do režimu nahrávání. To bude nutné provést pokaždé, když nahrajete nový kód do zařízení:

    1. Dvakrát rychle přepněte vypínač dolů – pokaždé se vrátí do polohy zapnuto.

    1. Zkontrolujte modrou stavovou LED diodu napravo od USB portu. Měla by pulzovat.
    
    [![Video ukazující, jak uvést Wio Terminal do režimu nahrávání](https://img.youtube.com/vi/LeKU_7zLRrQ/0.jpg)](https://youtu.be/LeKU_7zLRrQ)
    
    Klikněte na obrázek výše pro zhlédnutí videa, jak to provést.

1. Zkompilujte a nahrajte kód do Wio Terminalu.

    1. Otevřete příkazovou paletu VS Code.

    1. Zadejte `PlatformIO Upload` pro vyhledání možnosti nahrání a vyberte *PlatformIO: Upload*.

        ![Možnost nahrání PlatformIO v příkazové paletě](../../../../../translated_images/cs/vscode-platformio-upload-command-palette.9e0f49cf80d1f1c3.webp)

        PlatformIO automaticky zkompiluje kód, pokud je to potřeba, před jeho nahráním.

    1. Kód bude zkompilován a nahrán do Wio Terminalu.

        > 💁 Pokud používáte macOS, zobrazí se upozornění na *DISK NOT EJECTED PROPERLY*. To je způsobeno tím, že se Wio Terminal připojí jako disk během procesu nahrávání a při zápisu zkompilovaného kódu do zařízení se odpojí. Toto upozornění můžete ignorovat.

    ⚠️ Pokud se objeví chyby o nedostupném nahrávacím portu, nejprve se ujistěte, že máte Wio Terminal připojený k počítači, zapnutý pomocí přepínače na levé straně obrazovky a nastavený do režimu nahrávání. Zelená kontrolka na spodní straně by měla svítit a modrá kontrolka by měla pulzovat. Pokud chyba přetrvává, znovu rychle dvakrát přepněte vypínač dolů, abyste Wio Terminal přinutili přejít do režimu nahrávání, a zkuste nahrání znovu.

PlatformIO má Sériový monitor, který může sledovat data odesílaná přes USB kabel z Wio Terminalu. To vám umožní sledovat data odesílaná příkazem `Serial.println("Hello World");`.

1. Otevřete příkazovou paletu VS Code.

1. Zadejte `PlatformIO Serial` pro vyhledání možnosti Sériového monitoru a vyberte *PlatformIO: Serial Monitor*.

    ![Možnost Sériového monitoru PlatformIO v příkazové paletě](../../../../../translated_images/cs/vscode-platformio-serial-monitor-command-palette.b348ec841b8a1c14.webp)

    Otevře se nový terminál a data odesílaná přes sériový port budou streamována do tohoto terminálu:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Hello World
    Hello World
    ```

    `Hello World` se bude tisknout do sériového monitoru každých 5 sekund.

> 💁 Tento kód najdete ve složce [code/wio-terminal](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/wio-terminal).

😀 Vaše aplikace 'Hello World' byla úspěšná!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.