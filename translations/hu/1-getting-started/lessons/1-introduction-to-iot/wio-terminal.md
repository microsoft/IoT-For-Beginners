<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a4f0c166010e31fd7b6ca20bc88dec6d",
  "translation_date": "2025-08-27T22:24:35+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md",
  "language_code": "hu"
}
-->
# Wio Terminal

A [Seeed Studios Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) egy Arduino-kompatibilis mikrokontroller, beépített WiFi-vel, néhány érzékelővel és aktuátorral, valamint portokkal, amelyek lehetővé teszik további érzékelők és aktuátorok csatlakoztatását a [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html) nevű hardveres ökoszisztéma segítségével.

![A Seeed studios Wio Terminal](../../../../../translated_images/wio-terminal.b8299ee16587db9a.hu.png)

## Beállítás

A Wio Terminal használatához telepítened kell néhány ingyenes szoftvert a számítógépedre. Emellett frissítened kell a Wio Terminal firmware-jét, mielőtt csatlakoztatnád WiFi-hez.

### Feladat - beállítás

Telepítsd a szükséges szoftvereket és frissítsd a firmware-t.

1. Telepítsd a Visual Studio Code (VS Code) programot. Ez lesz az a szerkesztő, amelyben a készülékedhez C/C++ kódot fogsz írni. A telepítési útmutatóért tekintsd meg a [VS Code dokumentációját](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

    > 💁 Egy másik népszerű IDE az Arduino fejlesztéshez az [Arduino IDE](https://www.arduino.cc/en/software). Ha már ismered ezt az eszközt, akkor használhatod a VS Code és PlatformIO helyett, de a leckék a VS Code használatára vonatkozó utasításokat tartalmaznak.

1. Telepítsd a VS Code PlatformIO bővítményt. Ez egy olyan bővítmény, amely támogatja a mikrokontrollerek programozását C/C++ nyelven. A telepítési útmutatóért tekintsd meg a [PlatformIO bővítmény dokumentációját](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=platformio.platformio-ide). Ez a bővítmény a Microsoft C/C++ bővítményre támaszkodik, amely automatikusan települ a PlatformIO telepítésekor.

1. Csatlakoztasd a Wio Terminalt a számítógépedhez. A Wio Terminal alján található egy USB-C port, amelyet egy USB porthoz kell csatlakoztatni a számítógépen. A Wio Terminalhoz tartozik egy USB-C - USB-A kábel, de ha a számítógépeden csak USB-C portok vannak, akkor szükséged lesz egy USB-C kábelre vagy egy USB-A - USB-C adapterre.

1. Kövesd a [Wio Terminal Wiki WiFi Overview dokumentációjában](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/) található utasításokat a Wio Terminal beállításához és a firmware frissítéséhez.

## Hello World

Hagyományosan, amikor egy új programozási nyelvet vagy technológiát kezdünk el használni, létrehozunk egy 'Hello World' alkalmazást - egy kis alkalmazást, amely például a `"Hello World"` szöveget jeleníti meg, hogy megbizonyosodjunk arról, hogy minden eszköz megfelelően van konfigurálva.

A Wio Terminal Hello World alkalmazása biztosítja, hogy a Visual Studio Code megfelelően telepítve van PlatformIO-val, és be van állítva mikrokontroller fejlesztéshez.

### PlatformIO projekt létrehozása

Az első lépés egy új projekt létrehozása PlatformIO-val, amely a Wio Terminalhoz van konfigurálva.

#### Feladat - PlatformIO projekt létrehozása

Hozd létre a PlatformIO projektet.

1. Csatlakoztasd a Wio Terminalt a számítógépedhez.

1. Indítsd el a VS Code-ot.

1. A PlatformIO ikon a bal oldali menüsávon található:

    ![A Platform IO menü opció](../../../../../translated_images/vscode-platformio-menu.297be26b9733e5c4.hu.png)

    Válaszd ki ezt a menüpontot, majd válaszd a *PIO Home -> Open* lehetőséget.

    ![A Platform IO open opció](../../../../../translated_images/vscode-platformio-home-open.3f9a41bfd3f4da1c.hu.png)

1. A kezdőképernyőn válaszd ki a **+ New Project** gombot.

    ![Az új projekt gomb](../../../../../translated_images/vscode-platformio-welcome-new-button.ba6fc8a4c7b78cc8.hu.png)

1. Konfiguráld a projektet a *Project Wizard*-ban:

    1. Nevezd el a projektet `nightlight`.

    1. A *Board* legördülő menüben írd be, hogy `WIO`, hogy szűkítsd a listát, majd válaszd ki a *Seeeduino Wio Terminal*-t.

    1. Hagyd a *Framework*-ot *Arduino*-ként.

    1. Hagyd bejelölve a *Use default location* jelölőnégyzetet, vagy töröld a jelölést, és válassz egy helyet a projekt számára.

    1. Kattints a **Finish** gombra.

    ![A kitöltött projekt varázsló](../../../../../translated_images/vscode-platformio-nightlight-project-wizard.5c64db4da6037420.hu.png)

    A PlatformIO letölti a szükséges komponenseket a Wio Terminal kódjának fordításához, és létrehozza a projektet. Ez néhány percet igénybe vehet.

### PlatformIO projekt vizsgálata

A VS Code felfedezője megjeleníti a PlatformIO varázsló által létrehozott fájlokat és mappákat.

#### Mappák

* `.pio` - ez a mappa ideiglenes adatokat tartalmaz, amelyeket a PlatformIO használ, például könyvtárakat vagy lefordított kódot. Automatikusan újra létrejön, ha törlöd, és nem kell hozzáadnod a forráskód vezérléshez, ha megosztod a projektet például a GitHubon.
* `.vscode` - ez a mappa a PlatformIO és a VS Code által használt konfigurációt tartalmazza. Automatikusan újra létrejön, ha törlöd, és nem kell hozzáadnod a forráskód vezérléshez, ha megosztod a projektet például a GitHubon.
* `include` - ez a mappa külső fejlécfájlok számára van, amelyeket további könyvtárak hozzáadásakor használsz a kódodban. Ebben a leckében nem fogod használni ezt a mappát.
* `lib` - ez a mappa külső könyvtárak számára van, amelyeket a kódodban szeretnél meghívni. Ebben a leckében nem fogod használni ezt a mappát.
* `src` - ez a mappa tartalmazza az alkalmazásod fő forráskódját. Kezdetben egyetlen fájlt tartalmaz - `main.cpp`.
* `test` - ez a mappa az egységtesztek számára van, amelyeket a kódodhoz írsz.

#### Fájlok

* `main.cpp` - ez a fájl a `src` mappában található, és az alkalmazás belépési pontját tartalmazza. Nyisd meg ezt a fájlt, és a következő kódot fogja tartalmazni:

    ```cpp
    #include <Arduino.h>
    
    void setup() {
      // put your setup code here, to run once:
    }
    
    void loop() {
      // put your main code here, to run repeatedly:
    }
    ```

    Amikor az eszköz elindul, az Arduino keretrendszer egyszer futtatja a `setup` függvényt, majd folyamatosan futtatja a `loop` függvényt, amíg az eszköz ki nem kapcsol.

* `.gitignore` - ez a fájl felsorolja azokat a fájlokat és mappákat, amelyeket figyelmen kívül kell hagyni, amikor a kódot hozzáadod a git forráskód vezérléshez, például egy GitHubon lévő tárolóba való feltöltéskor.

* `platformio.ini` - ez a fájl tartalmazza az eszköz és az alkalmazás konfigurációját. Nyisd meg ezt a fájlt, és a következő kódot fogja tartalmazni:

    ```ini
    [env:seeed_wio_terminal]
    platform = atmelsam
    board = seeed_wio_terminal
    framework = arduino
    ```

    A `[env:seeed_wio_terminal]` szekció tartalmazza a Wio Terminal konfigurációját. Több `env` szekciót is létrehozhatsz, hogy a kódod több táblára is lefordítható legyen.

    A többi érték megegyezik a projekt varázslóban megadott konfigurációval:

  * `platform = atmelsam` meghatározza a Wio Terminal által használt hardvert (egy ATSAMD51-alapú mikrokontroller)
  * `board = seeed_wio_terminal` meghatározza a mikrokontroller típusát (a Wio Terminal)
  * `framework = arduino` meghatározza, hogy ez a projekt az Arduino keretrendszert használja.

### Írd meg a Hello World alkalmazást

Most készen állsz arra, hogy megírd a Hello World alkalmazást.

#### Feladat - Hello World alkalmazás írása

Írd meg a Hello World alkalmazást.

1. Nyisd meg a `main.cpp` fájlt a VS Code-ban.

1. Módosítsd a kódot az alábbiak szerint:

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

    A `setup` függvény inicializálja a kapcsolatot a soros porttal - ebben az esetben az USB porttal, amelyet a Wio Terminal csatlakoztatására használsz a számítógépedhez. A `9600` paraméter a [baud rate](https://wikipedia.org/wiki/Symbol_rate) (más néven szimbólumsebesség), vagyis az adatátvitel sebessége a soros porton másodpercenkénti bitekben. Ez a beállítás azt jelenti, hogy másodpercenként 9,600 bit (0 és 1) adat kerül továbbításra. Ezután várja, hogy a soros port készen álljon.

    A `loop` függvény elküldi a `Hello World!` sort a soros porton keresztül, így a `Hello World!` karakterek egy új sor karakterrel együtt továbbítódnak. Ezután 5,000 milliszekundumig, azaz 5 másodpercig várakozik. Miután a `loop` véget ér, újra és újra fut, amíg a mikrokontroller be van kapcsolva.

1. Állítsd a Wio Terminalt feltöltési módba. Ezt minden alkalommal meg kell tenned, amikor új kódot töltesz fel az eszközre:

    1. Kétszer gyorsan húzd le a bekapcsoló kapcsolót - az vissza fog ugrani az "on" pozícióba minden alkalommal.

    1. Ellenőrizd a kék állapotjelző LED-et az USB port jobb oldalán. Pulzálnia kell.
    
    [![Egy videó, amely bemutatja, hogyan állítsd feltöltési módba a Wio Terminalt](https://img.youtube.com/vi/LeKU_7zLRrQ/0.jpg)](https://youtu.be/LeKU_7zLRrQ)
    
    Kattints a fenti képre, hogy megnézd a videót.

1. Fordítsd le és töltsd fel a kódot a Wio Terminalra.

    1. Nyisd meg a VS Code parancspalettáját.

    1. Írd be, hogy `PlatformIO Upload`, hogy megkeresd a feltöltési opciót, majd válaszd a *PlatformIO: Upload* lehetőséget.

        ![A PlatformIO feltöltési opció a parancspalettán](../../../../../translated_images/vscode-platformio-upload-command-palette.9e0f49cf80d1f1c3.hu.png)

        A PlatformIO automatikusan lefordítja a kódot, ha szükséges, mielőtt feltölti.

    1. A kód lefordításra kerül, majd feltöltődik a Wio Terminalra.

        > 💁 Ha macOS-t használsz, egy értesítés jelenik meg a *DISK NOT EJECTED PROPERLY* üzenettel. Ez azért van, mert a Wio Terminal meghajtóként csatlakozik a villogási folyamat részeként, és lecsatlakozik, amikor a lefordított kódot az eszközre írják. Ezt az értesítést figyelmen kívül hagyhatod.

    ⚠️ Ha hibát kapsz arról, hogy a feltöltési port nem elérhető, először győződj meg arról, hogy a Wio Terminal csatlakoztatva van a számítógépedhez, és be van kapcsolva a képernyő bal oldalán lévő kapcsolóval, valamint feltöltési módba van állítva. Az alsó zöld fénynek világítania kell, és a kék fénynek pulzálnia kell. Ha továbbra is hibát kapsz, húzd le kétszer gyorsan a be-/kikapcsoló kapcsolót, hogy kényszerítsd a Wio Terminalt feltöltési módba, majd próbáld újra a feltöltést.

A PlatformIO rendelkezik egy Soros Monitorral, amely figyelheti az USB kábelen keresztül a Wio Terminal által küldött adatokat. Ez lehetővé teszi, hogy figyeld a `Serial.println("Hello World");` parancs által küldött adatokat.

1. Nyisd meg a VS Code parancspalettáját.

1. Írd be, hogy `PlatformIO Serial`, hogy megkeresd a Soros Monitor opciót, majd válaszd a *PlatformIO: Serial Monitor* lehetőséget.

    ![A PlatformIO Soros Monitor opció a parancspalettán](../../../../../translated_images/vscode-platformio-serial-monitor-command-palette.b348ec841b8a1c14.hu.png)

    Egy új terminál nyílik meg, és a soros porton keresztül küldött adatok ebbe a terminálba kerülnek:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Hello World
    Hello World
    ```

    A `Hello World` minden 5 másodpercben megjelenik a soros monitoron.

> 💁 Ezt a kódot megtalálod a [code/wio-terminal](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/wio-terminal) mappában.

😀 A 'Hello World' programod sikeres volt!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.