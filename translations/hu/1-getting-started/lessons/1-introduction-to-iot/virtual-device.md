<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "52b4de6144b2efdced7797a5339d6035",
  "translation_date": "2025-08-27T22:19:46+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/virtual-device.md",
  "language_code": "hu"
}
-->
# Virtuális egykártyás számítógép

Ahelyett, hogy IoT eszközt, szenzorokat és aktuátorokat vásárolnál, a számítógépedet is használhatod IoT hardver szimulálására. A [CounterFit projekt](https://github.com/CounterFit-IoT/CounterFit) lehetővé teszi, hogy helyben futtass egy alkalmazást, amely szimulálja az IoT hardvert, például szenzorokat és aktuátorokat, és hozzáférj ezekhez a helyi Python kódból, ugyanúgy, ahogy fizikai hardverrel, például Raspberry Pi-vel dolgoznál.

## Beállítás

A CounterFit használatához néhány ingyenes szoftvert kell telepítened a számítógépedre.

### Feladat

Telepítsd a szükséges szoftvereket.

1. Telepítsd a Python-t. A legújabb Python verzió telepítéséhez lásd a [Python letöltési oldalát](https://www.python.org/downloads/).

1. Telepítsd a Visual Studio Code-ot (VS Code). Ez lesz az editor, amelyben a virtuális eszköz kódját Pythonban írod. A telepítési útmutatóért lásd a [VS Code dokumentációját](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

    > 💁 Szabadon használhatsz bármilyen Python IDE-t vagy editort, ha van kedvenc eszközöd, de a leckék a VS Code használatára vonatkozó utasításokat tartalmaznak.

1. Telepítsd a VS Code Pylance bővítményt. Ez egy VS Code bővítmény, amely Python nyelvi támogatást nyújt. A telepítési útmutatóért lásd a [Pylance bővítmény dokumentációját](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance).

A CounterFit alkalmazás telepítésére és konfigurálására vonatkozó utasításokat a megfelelő időben, a feladat utasításai között találod, mivel ez projektalapon kerül telepítésre.

## Hello világ

Hagyomány, hogy egy új programozási nyelv vagy technológia elsajátításakor egy 'Hello World' alkalmazással kezdünk - egy kis alkalmazással, amely például a `"Hello World"` szöveget jeleníti meg, hogy megbizonyosodjunk arról, hogy minden eszköz megfelelően van konfigurálva.

A virtuális IoT hardverhez készült Hello World alkalmazás biztosítja, hogy a Python és a Visual Studio Code helyesen legyen telepítve. Emellett csatlakozik a CounterFit-hez a virtuális IoT szenzorok és aktuátorok számára. Nem használ semmilyen hardvert, csak csatlakozik, hogy bizonyítsa, minden működik.

Ez az alkalmazás egy `nightlight` nevű mappában lesz, és később, a feladat további részeiben újra felhasználásra kerül a nightlight alkalmazás építéséhez.

### Python virtuális környezet konfigurálása

A Python egyik erőteljes funkciója a [Pip csomagok](https://pypi.org) telepítésének lehetősége - ezek olyan kódcsomagok, amelyeket mások írtak és publikáltak az interneten. Egy Pip csomagot egyetlen paranccsal telepíthetsz a számítógépedre, majd használhatod azt a kódodban. A CounterFit-hez való kommunikációhoz egy csomagot fogsz telepíteni Pip segítségével.

Alapértelmezés szerint, amikor telepítesz egy csomagot, az mindenhol elérhető a számítógépeden, ami problémákat okozhat a csomagverziókkal - például egy alkalmazás egy csomag egyik verziójától függ, amely megszakad, ha egy másik alkalmazáshoz új verziót telepítesz. Ennek a problémának a megoldására használhatsz egy [Python virtuális környezetet](https://docs.python.org/3/library/venv.html), amely lényegében egy Python másolat egy dedikált mappában, és amikor Pip csomagokat telepítesz, azok csak abba a mappába kerülnek telepítésre.

> 💁 Ha Raspberry Pi-t használsz, akkor nem állítottál be virtuális környezetet azon az eszközön a Pip csomagok kezelésére, hanem globális csomagokat használsz, mivel a Grove csomagok globálisan kerülnek telepítésre a telepítő szkript által.

#### Feladat - Python virtuális környezet konfigurálása

Konfiguráld a Python virtuális környezetet, és telepítsd a CounterFit-hez szükséges Pip csomagokat.

1. A terminálodban vagy parancssorodban futtasd a következő parancsokat egy általad választott helyen, hogy létrehozz és navigálj egy új könyvtárba:

    ```sh
    mkdir nightlight
    cd nightlight
    ```

1. Most futtasd a következőt, hogy létrehozz egy virtuális környezetet a `.venv` mappában:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Kifejezetten a `python3`-at kell hívnod a virtuális környezet létrehozásához, arra az esetre, ha Python 2 is telepítve van a Python 3 mellett (a legújabb verzió). Ha Python 2 telepítve van, akkor a `python` hívása Python 2-t fog használni Python 3 helyett.

1. Aktiváld a virtuális környezetet:

    * Windows esetén:
        * Ha a Command Promptot vagy a Windows Terminalon keresztül a Command Promptot használod, futtasd:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Ha PowerShellt használsz, futtasd:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

            > Ha hibaüzenetet kapsz arról, hogy a szkriptek futtatása le van tiltva ezen a rendszeren, engedélyezned kell a szkriptek futtatását egy megfelelő végrehajtási szabályzat beállításával. Ezt úgy teheted meg, hogy rendszergazdaként indítod el a PowerShellt, majd futtatod a következő parancsot:

            ```powershell
            Set-ExecutionPolicy -ExecutionPolicy Unrestricted
            ```

            Nyomj `Y`-t a megerősítéshez. Ezután indítsd újra a PowerShellt, és próbáld újra.

            Ha szükséges, később visszaállíthatod ezt a végrehajtási szabályzatot. Erről többet olvashatsz a [Microsoft Docs végrehajtási szabályzatok oldalán](https://docs.microsoft.com/powershell/module/microsoft.powershell.core/about/about_execution_policies?WT.mc_id=academic-17441-jabenn).

    * macOS vagy Linux esetén futtasd:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Ezeket a parancsokat ugyanabból a helyről kell futtatnod, ahol a virtuális környezet létrehozására vonatkozó parancsot futtattad. Soha nem kell belépned a `.venv` mappába, mindig az aktiváló parancsot és a csomagok telepítésére vagy kód futtatására vonatkozó parancsokat kell futtatnod abból a mappából, ahol a virtuális környezetet létrehoztad.

1. Miután a virtuális környezet aktiválva lett, az alapértelmezett `python` parancs azt a Python verziót fogja futtatni, amelyet a virtuális környezet létrehozásához használtál. Futtasd a következőt a verzió lekéréséhez:

    ```sh
    python --version
    ```

    A kimenetnek a következőt kell tartalmaznia:

    ```output
    (.venv) ➜  nightlight python --version
    Python 3.9.1
    ```

    > 💁 A Python verziód eltérő lehet - amíg 3.6 vagy magasabb verziójú, minden rendben. Ha nem, töröld ezt a mappát, telepíts egy újabb Python verziót, és próbáld újra.

1. Futtasd a következő parancsokat a CounterFit-hez szükséges Pip csomagok telepítéséhez. Ezek a csomagok tartalmazzák a fő CounterFit alkalmazást, valamint Grove hardverhez való shimeket. Ezek a shimek lehetővé teszik, hogy úgy írj kódot, mintha fizikai szenzorokat és aktuátorokat programoznál a Grove ökoszisztémából, de virtuális IoT eszközökhöz csatlakozva.

    ```sh
    pip install CounterFit
    pip install counterfit-connection
    pip install counterfit-shims-grove
    ```

    Ezek a pip csomagok csak a virtuális környezetben lesznek telepítve, és azon kívül nem lesznek elérhetők.

### Írd meg a kódot

Miután a Python virtuális környezet készen áll, megírhatod a 'Hello World' alkalmazás kódját.

#### Feladat - írd meg a kódot

Hozz létre egy Python alkalmazást, amely kiírja a `"Hello World"` szöveget a konzolra.

1. A terminálodban vagy parancssorodban futtasd a következőt a virtuális környezeten belül, hogy létrehozz egy `app.py` nevű Python fájlt:

    * Windows esetén futtasd:

        ```cmd
        type nul > app.py
        ```

    * macOS vagy Linux esetén futtasd:

        ```cmd
        touch app.py
        ```

1. Nyisd meg az aktuális mappát a VS Code-ban:

    ```sh
    code .
    ```

    > 💁 Ha a terminálod `command not found` üzenetet ad vissza macOS-en, az azt jelenti, hogy a VS Code nincs hozzáadva a PATH-hoz. A VS Code-ot hozzáadhatod a PATH-hoz a [VS Code dokumentációjának Parancssorból indítás szakaszában](https://code.visualstudio.com/docs/setup/mac?WT.mc_id=academic-17441-jabenn#_launching-from-the-command-line) található utasítások követésével, majd futtasd a parancsot utána. A VS Code alapértelmezés szerint hozzáadódik a PATH-hoz Windows és Linux rendszeren.

1. Amikor a VS Code elindul, aktiválja a Python virtuális környezetet. A kiválasztott virtuális környezet megjelenik az alsó állapotsávban:

    ![VS Code a kiválasztott virtuális környezettel](../../../../../translated_images/hu/vscode-virtual-env.8ba42e04c3d533cf.webp)

1. Ha a VS Code terminál már fut, amikor a VS Code elindul, akkor nem lesz aktiválva benne a virtuális környezet. A legegyszerűbb megoldás az, ha bezárod a terminált a **Kill the active terminal instance** gombbal:

    ![VS Code Kill the active terminal instance gomb](../../../../../translated_images/hu/vscode-kill-terminal.1cc4de7c6f25ee08.webp)

    Megállapíthatod, hogy a terminálban aktiválva van-e a virtuális környezet, ha a terminál promptjának előtagja a virtuális környezet neve. Például lehet:

    ```sh
    (.venv) ➜  nightlight
    ```

    Ha nincs `.venv` előtag a prompton, akkor a virtuális környezet nincs aktiválva a terminálban.

1. Indíts egy új VS Code terminált a *Terminal -> New Terminal* menüpont kiválasztásával, vagy a `` CTRL+` `` billentyűkombinációval. Az új terminál betölti a virtuális környezetet, és az aktiválásra vonatkozó hívás megjelenik a terminálban. A prompton is megjelenik a virtuális környezet neve (`.venv`):

    ```output
    ➜  nightlight source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Nyisd meg az `app.py` fájlt a VS Code explorerből, és add hozzá a következő kódot:

    ```python
    print('Hello World!')
    ```

    A `print` függvény kiírja a konzolra azt, amit átadnak neki.

1. A VS Code terminálból futtasd a következőt a Python alkalmazás futtatásához:

    ```sh
    python app.py
    ```

    A kimenetben a következő lesz:

    ```output
    (.venv) ➜  nightlight python app.py 
    Hello World!
    ```

😀 A 'Hello World' programod sikeres volt!

### Csatlakoztasd a 'hardvert'

Második 'Hello World' lépésként futtatni fogod a CounterFit alkalmazást, és csatlakoztatod hozzá a kódodat. Ez a virtuális megfelelője annak, hogy IoT hardvert csatlakoztatsz egy fejlesztői készlethez.

#### Feladat - csatlakoztasd a 'hardvert'

1. A VS Code terminálból indítsd el a CounterFit alkalmazást a következő paranccsal:

    ```sh
    counterfit
    ```

    Az alkalmazás elindul, és megnyílik a webböngésződben:

    ![A Counter Fit alkalmazás futása böngészőben](../../../../../translated_images/hu/counterfit-first-run.433326358b669b31d0e99c3513cb01bfbb13724d162c99cdcc8f51ecf5f9c779.png)

    *Disconnected* állapotban lesz, a jobb felső sarokban lévő LED ki lesz kapcsolva.

1. Add hozzá a következő kódot az `app.py` fájl tetejéhez:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

    Ez a kód importálja a `CounterFitConnection` osztályt a `counterfit_connection` modulból, amely a korábban telepített `counterfit-connection` pip csomagból származik. Ezután inicializál egy kapcsolatot a CounterFit alkalmazáshoz, amely a `127.0.0.1` címen fut, ami egy IP-cím, amelyet mindig használhatsz a helyi számítógéped eléréséhez (*localhost* néven is ismert), az 5000-es porton.

    > 💁 Ha más alkalmazások futnak az 5000-es porton, ezt megváltoztathatod a kódban a port frissítésével, és a CounterFit futtatásával `CounterFit --port <port_number>` paranccsal, ahol `<port_number>` helyére az általad használni kívánt portot írod.

1. Új VS Code terminált kell indítanod a **Create a new integrated terminal** gombbal. Ez azért szükséges, mert a CounterFit alkalmazás a jelenlegi terminálban fut.

    ![VS Code Create a new integrated terminal gomb](../../../../../translated_images/hu/vscode-new-terminal.77db8fc0f9cd3182.webp)

1. Ebben az új terminálban futtasd az `app.py` fájlt, ahogy korábban. A CounterFit állapota **Connected**-re változik, és a LED világítani fog.

    ![Counter Fit csatlakoztatva](../../../../../translated_images/hu/counterfit-connected.ed30b46d8f79b0921f3fc70be10366e596a89dca3f80c2224a9d9fc98fccf884.png)

> 💁 Ezt a kódot megtalálod a [code/virtual-device](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/virtual-device) mappában.

😀 A hardverhez való csatlakozásod sikeres volt!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.