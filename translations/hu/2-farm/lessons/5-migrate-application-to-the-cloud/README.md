<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f2d2f4a5a023c93ab34a0cc5b47c0c4",
  "translation_date": "2025-08-27T22:58:34+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/README.md",
  "language_code": "hu"
}
-->
# Alkalmazáslogika áthelyezése a felhőbe

![A lecke vázlatos áttekintése](../../../../../translated_images/lesson-9.dfe99c8e891f48e179724520da9f5794392cf9a625079281ccdcbf09bd85e1b6.hu.jpg)

> Vázlatrajz: [Nitya Narasimhan](https://github.com/nitya). Kattints a képre a nagyobb verzióért.

Ez a lecke a [IoT for Beginners Project 2 - Digital Agriculture sorozat](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) részeként került bemutatásra a [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn) keretében.

[![IoT eszköz vezérlése szerver nélküli kóddal](https://img.youtube.com/vi/VVZDcs5u1_I/0.jpg)](https://youtu.be/VVZDcs5u1_I)

## Előzetes kvíz

[Előzetes kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/17)

## Bevezetés

Az előző leckében megtanultad, hogyan csatlakoztasd a növény talajnedvesség-figyelőjét és a relévezérlést egy felhőalapú IoT szolgáltatáshoz. A következő lépés a relé időzítését vezérlő szerver kódjának áthelyezése a felhőbe. Ebben a leckében megtanulod, hogyan teheted ezt meg szerver nélküli funkciók segítségével.

Ebben a leckében a következőket tárgyaljuk:

* [Mi az a szerver nélküli?](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Szerver nélküli alkalmazás létrehozása](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [IoT Hub eseményindító létrehozása](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Közvetlen metóduskérések küldése szerver nélküli kódból](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Szerver nélküli kód telepítése a felhőbe](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)

## Mi az a szerver nélküli?

A szerver nélküli, vagy szerver nélküli számítástechnika kis kódrészletek létrehozását jelenti, amelyek a felhőben futnak különböző események hatására. Amikor az esemény bekövetkezik, a kódod lefut, és megkapja az esemény adatait. Ezek az események sokféle forrásból származhatnak, például webes kérésekből, sorba helyezett üzenetekből, adatbázisban történt változásokból vagy IoT eszközök által küldött üzenetekből.

![Események küldése egy IoT szolgáltatásból egy szerver nélküli szolgáltatásba, amelyeket egyszerre több funkció dolgoz fel](../../../../../translated_images/iot-messages-to-serverless.0194da1cc0732bb7d0f823aed3fce54735c6b1ad3bf36089804d8aaefc0a774f.hu.png)

> 💁 Ha már használtál adatbázis-triggereket, gondolj erre úgy, mint egy hasonló dologra: kódot indít el egy esemény, például egy sor beszúrása.

![Amikor sok esemény érkezik egyszerre, a szerver nélküli szolgáltatás skálázódik, hogy mindet egyszerre futtassa](../../../../../translated_images/serverless-scaling.f8c769adf0413fd1.hu.png)

A kódod csak akkor fut, amikor az esemény bekövetkezik, máskor nem marad aktív. Az esemény bekövetkezik, a kódod betöltődik és lefut. Ez a szerver nélküli megoldást nagyon skálázhatóvá teszi – ha sok esemény történik egyszerre, a felhőszolgáltató annyiszor futtatja a funkciódat, ahányszor szükséges, a rendelkezésre álló szervereken. Ennek hátránya, hogy ha információt kell megosztanod az események között, azt valahol el kell tárolnod, például egy adatbázisban, nem pedig memóriában.

A kódod egy olyan funkcióként van megírva, amely paraméterként kapja meg az esemény részleteit. Számos programozási nyelvet használhatsz ezeknek a szerver nélküli funkcióknak a megírásához.

> 🎓 A szerver nélküli megoldást gyakran Funkciók mint szolgáltatás (FaaS) néven is emlegetik, mivel minden eseményindítót egy funkcióként valósítanak meg a kódban.

A név ellenére a szerver nélküli megoldás valójában használ szervereket. Az elnevezés arra utal, hogy fejlesztőként nem kell foglalkoznod a kódod futtatásához szükséges szerverekkel, csak azzal, hogy a kódod lefut az esemény hatására. A felhőszolgáltató egy szerver nélküli *futtatókörnyezetet* biztosít, amely kezeli a szerverek, hálózatok, tárolók, CPU, memória és minden más szükséges erőforrás kiosztását. Ez a modell azt jelenti, hogy nem szerverenként fizetsz a szolgáltatásért, mivel nincs szerver. Ehelyett a kódod futási ideje és a felhasznált memória alapján fizetsz.

> 💰 A szerver nélküli megoldás az egyik legolcsóbb módja a kód futtatásának a felhőben. Például, az írás idején az egyik felhőszolgáltató lehetővé teszi, hogy az összes szerver nélküli funkciód havonta összesen 1 000 000 alkalommal fusson le díjmentesen, és ezután 0,20 USD-t számítanak fel minden további 1 000 000 futtatásért. Amikor a kódod nem fut, nem fizetsz.

IoT fejlesztőként a szerver nélküli modell ideális. Írhatsz egy funkciót, amelyet bármely IoT eszköz által küldött üzenet hatására hívnak meg, amely csatlakozik a felhőben hosztolt IoT szolgáltatásodhoz. A kódod minden elküldött üzenetet kezel, de csak akkor fut, amikor szükséges.

✅ Nézd vissza a kódot, amelyet szerverkódként írtál az MQTT üzenetek figyelésére. Hogyan futtatható ez a felhőben szerver nélküli megoldással? Hogyan kellene módosítani a kódot, hogy támogassa a szerver nélküli számítástechnikát?

> 💁 A szerver nélküli modell más felhőszolgáltatásokra is terjed, nemcsak kód futtatására. Például a felhőben elérhetők szerver nélküli adatbázisok is, amelyek szerver nélküli árazási modellt használnak, ahol a lekérdezések vagy beszúrások alapján fizetsz, általában az elvégzett munka mennyisége alapján. Például egyetlen sor lekérdezése egy elsődleges kulcs alapján kevesebbe kerül, mint egy bonyolult művelet, amely sok táblát csatlakoztat és több ezer sort ad vissza.

## Szerver nélküli alkalmazás létrehozása

A Microsoft szerver nélküli számítástechnikai szolgáltatása az Azure Functions.

![Az Azure Functions logója](../../../../../translated_images/azure-functions-logo.1cfc8e3204c9c44aaf80fcf406fc8544d80d7f00f8d3e8ed6fed764563e17564.hu.png)

Az alábbi rövid videó áttekintést nyújt az Azure Functions-ről:

[![Azure Functions áttekintő videó](https://img.youtube.com/vi/8-jz5f_JyEQ/0.jpg)](https://www.youtube.com/watch?v=8-jz5f_JyEQ)

> 🎥 Kattints a fenti képre a videó megtekintéséhez.

✅ Szánj egy kis időt arra, hogy kutass, és olvasd el az Azure Functions áttekintését a [Microsoft Azure Functions dokumentációjában](https://docs.microsoft.com/azure/azure-functions/functions-overview?WT.mc_id=academic-17441-jabenn).

Az Azure Functions írásához egy Azure Functions alkalmazással kell kezdened, a választott programozási nyelven. Az Azure Functions alapértelmezés szerint támogatja a Python, JavaScript, TypeScript, C#, F#, Java és Powershell nyelveket. Ebben a leckében megtanulod, hogyan írj Azure Functions alkalmazást Pythonban.

> 💁 Az Azure Functions egyedi kezelőket is támogat, így bármilyen nyelven írhatsz funkciókat, amely támogatja a HTTP kéréseket, beleértve az olyan régebbi nyelveket is, mint a COBOL.

A funkciós alkalmazások egy vagy több *indítót* tartalmaznak – funkciókat, amelyek eseményekre reagálnak. Egy funkciós alkalmazásban több indító is lehet, amelyek közös konfigurációt osztanak meg. Például a funkciós alkalmazás konfigurációs fájljában megadhatod az IoT Hub csatlakozási adatait, és az alkalmazás összes funkciója használhatja ezeket az események figyelésére.

### Feladat - Az Azure Functions eszközök telepítése

> Az írás idején az Azure Functions kódolási eszközei nem teljesen működnek Apple Silicon gépeken Python projektek esetén. Ehelyett Intel-alapú Mac-et, Windows PC-t vagy Linux PC-t kell használnod.

Az Azure Functions egyik nagyszerű tulajdonsága, hogy helyben is futtathatók. Ugyanaz a futtatókörnyezet, amely a felhőben fut, a számítógépeden is futtatható, lehetővé téve, hogy kódot írj, amely IoT üzenetekre reagál, és helyben futtasd. Még a kódot is hibakeresheted, miközben az eseményeket kezeli. Ha elégedett vagy a kódoddal, telepítheted a felhőbe.

Az Azure Functions eszközkészlet CLI-ként érhető el, amelyet Azure Functions Core Tools néven ismerünk.

1. Telepítsd az Azure Functions Core Tools-t a [Azure Functions Core Tools dokumentációjában](https://docs.microsoft.com/azure/azure-functions/functions-run-local?WT.mc_id=academic-17441-jabenn) található utasítások követésével.

1. Telepítsd az Azure Functions bővítményt a VS Code-hoz. Ez a bővítmény támogatja az Azure Functions létrehozását, hibakeresését és telepítését. A telepítési utasításokat a [Azure Functions bővítmény dokumentációjában](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-azuretools.vscode-azurefunctions) találod.

Amikor az Azure Functions alkalmazásodat telepíted a felhőbe, egy kis mennyiségű felhőtárhelyre lesz szüksége az alkalmazásfájlok és naplófájlok tárolásához. Amikor helyben futtatod a Functions alkalmazásodat, akkor is csatlakoznod kell a felhőtárhelyhez, de a tényleges felhőtárhely helyett használhatod az [Azurite](https://github.com/Azure/Azurite) nevű tárolóemulátort. Ez helyben fut, de úgy viselkedik, mint a felhőtárhely.

> 🎓 Az Azure-ban az Azure Functions által használt tároló egy Azure Storage Account. Ezek a fiókok fájlokat, blobokat, táblázatokban lévő adatokat vagy sorokban lévő adatokat tárolhatnak. Egy tárolófiókot több alkalmazás is megoszthat, például egy Functions alkalmazás és egy webalkalmazás.

1. Az Azurite egy Node.js alkalmazás, ezért telepítened kell a Node.js-t. A letöltési és telepítési utasításokat a [Node.js weboldalán](https://nodejs.org/) találod. Ha Mac-et használsz, a [Homebrew](https://formulae.brew.sh/formula/node) segítségével is telepítheted.

1. Telepítsd az Azurite-ot a következő paranccsal (`npm` a Node.js telepítésekor kerül a gépedre):

    ```sh
    npm install -g azurite
    ```

1. Hozz létre egy `azurite` nevű mappát az Azurite által használt adatok tárolására:

    ```sh
    mkdir azurite
    ```

1. Indítsd el az Azurite-ot, és add meg neki az új mappát:

    ```sh
    azurite --location azurite
    ```

    Az Azurite tárolóemulátor elindul, és készen áll arra, hogy a helyi Functions futtatókörnyezet csatlakozzon hozzá.

    ```output
    ➜  ~ azurite --location azurite  
    Azurite Blob service is starting at http://127.0.0.1:10000
    Azurite Blob service is successfully listening at http://127.0.0.1:10000
    Azurite Queue service is starting at http://127.0.0.1:10001
    Azurite Queue service is successfully listening at http://127.0.0.1:10001
    Azurite Table service is starting at http://127.0.0.1:10002
    Azurite Table service is successfully listening at http://127.0.0.1:10002
    ```

### Feladat - Azure Functions projekt létrehozása

Az Azure Functions CLI segítségével új Functions alkalmazást hozhatsz létre.

1. Hozz létre egy mappát a Functions alkalmazásod számára, és lépj be ebbe a mappába. Nevezd el `soil-moisture-trigger`-nek:

    ```sh
    mkdir soil-moisture-trigger
    cd soil-moisture-trigger
    ```

1. Hozz létre egy Python virtuális környezetet ebben a mappában:

    ```sh
    python3 -m venv .venv
    ```

1. Aktiváld a virtuális környezetet:

    * Windows rendszeren:
        * Ha a Parancssort vagy a Windows Terminalon keresztüli Parancssort használod, futtasd:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Ha PowerShellt használsz, futtasd:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * macOS vagy Linux rendszeren futtasd:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Ezeket a parancsokat abból a helyről kell futtatnod, ahol a virtuális környezetet létrehoztad. Soha nem kell belépned a `.venv` mappába, mindig az aktiváló parancsot és a csomagok telepítésére vagy kód futtatására vonatkozó parancsokat kell futtatnod abból a mappából, ahol a virtuális környezetet létrehoztad.

1. Futtasd a következő parancsot egy Functions alkalmazás létrehozásához ebben a mappában:

    ```sh
    func init --worker-runtime python soil-moisture-trigger
    ```

    Ez három fájlt hoz létre az aktuális mappában:

    * `host.json` - ez a JSON dokumentum tartalmazza a Functions alkalmazás beállításait. Ezeket a beállításokat nem kell módosítanod.
    * `local.settings.json` - ez a JSON dokumentum tartalmazza az alkalmazás helyi futtatásakor használt beállításokat, például az IoT Hub csatlakozási karakterláncait. Ezek a beállítások csak helyben érvényesek, és nem kerülnek forráskódvezérlés alá. Amikor az alkalmazást telepíted a felhőbe, ezek a beállítások nem kerülnek telepítésre, helyette az alkalmazásbeállításokból töltődnek be. Erről később lesz szó ebben a leckében.
    * `requirements.txt` - ez egy [Pip követelményfájl](https://pip.pypa.io/en/stable/user_guide/#requirements-files), amely tartalmazza a Functions alkalmazás futtatásához szükséges Pip csomagokat.

1. A `local.settings.json` fájlban van egy beállítás a Functions alkalmazás által használt tárolófiókhoz. Ez alapértelmezés szerint üres, ezért be kell állítani. Az Azurite helyi tárolóemulátorhoz való csatlakozáshoz állítsd be az értéket a következőre:

    ```json
    "AzureWebJobsStorage": "UseDevelopmentStorage=true",
    ```

1. Telepítsd a szükséges Pip csomagokat a követelményfájl segítségével:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 A szükséges Pip csomagoknak ebben a fájlban kell lenniük, hogy amikor a Functions alkalmazást telepíted a felhőbe, a futtatókörnyezet biztosítani tudja a megfelelő csomagok telepítését.

1. Annak teszteléséhez, hogy minden megfelelően működik-e, indítsd el a Functions futtatókörnyezetet. Futtasd a következő parancsot:

    ```sh
    func start
    ```

    Látni fogod, hogy a futtatókörnyezet elindul, és jelzi, hogy nem talált munkafunkciókat (indítókat).

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    [2021-05-05T01:24:46.795Z] No job functions found.
    ```
> ⚠️ Ha tűzfal értesítést kap, engedélyezze a hozzáférést, mivel a `func` alkalmazásnak olvasási és írási jogokra van szüksége a hálózatához.
> ⚠️ Ha macOS-t használsz, előfordulhatnak figyelmeztetések a kimenetben:
>
> ```output
    > (.venv) ➜  soil-moisture-trigger func start
    > Found Python version 3.9.1 (python3).
    >
    > Azure Functions Core Tools
    > Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    > Function Runtime Version: 3.0.15417.0
    >
    > [2021-06-16T08:18:28.315Z] Cannot create directory for shared memory usage: /dev/shm/AzureFunctions
    > [2021-06-16T08:18:28.316Z] System.IO.FileSystem: Access to the path '/dev/shm/AzureFunctions' is denied. Operation not permitted.
    > [2021-06-16T08:18:30.361Z] No job functions found.
    > ```
>
> Ezeket figyelmen kívül hagyhatod, amennyiben a Functions alkalmazás helyesen indul el, és listázza a futó funkciókat. Ahogy [ebben a Microsoft Docs Q&A kérdésben](https://docs.microsoft.com/answers/questions/396617/azure-functions-core-tools-error-osx-devshmazurefu.html?WT.mc_id=academic-17441-jabenn) is említik, ezek figyelmen kívül hagyhatók.

1. Állítsd le a Functions alkalmazást a `ctrl+c` billentyűkombinációval.

1. Nyisd meg az aktuális mappát a VS Code-ban, akár úgy, hogy megnyitod a VS Code-ot, majd megnyitod ezt a mappát, vagy futtasd a következőt:

    ```sh
    code .
    ```

    A VS Code felismeri a Functions projektedet, és egy értesítést jelenít meg, amely ezt mondja:

    ```output
    Detected an Azure Functions Project in folder "soil-moisture-trigger" that may have been created outside of
    VS Code. Initialize for optimal use with VS Code?
    ```

    ![Az értesítés](../../../../../translated_images/vscode-azure-functions-init-notification.bd19b49229963edb.hu.png)

    Válaszd az **Igen** lehetőséget az értesítésben.

1. Győződj meg róla, hogy a Python virtuális környezet fut a VS Code termináljában. Ha szükséges, állítsd le, majd indítsd újra.

## IoT Hub eseményindító létrehozása

A Functions alkalmazás a szerver nélküli kódod kerete. Az IoT Hub eseményeire való reagáláshoz hozzáadhatsz egy IoT Hub indítót ehhez az alkalmazáshoz. Ez az indító csatlakozik az IoT Hubhoz küldött üzenetek adatfolyamához, és reagál rájuk. Az üzenetek adatfolyamának eléréséhez az indítónak csatlakoznia kell az IoT Hub *Event Hub kompatibilis végpontjához*.

Az IoT Hub az Azure Event Hubs nevű másik Azure szolgáltatáson alapul. Az Event Hubs lehetővé teszi üzenetek küldését és fogadását, az IoT Hub pedig kiterjeszti ezt az IoT eszközökre vonatkozó funkciókkal. Az IoT Hub üzeneteinek olvasásához ugyanúgy kell csatlakozni, mintha Event Hubs-t használnál.

✅ Kutatás: Olvasd el az Event Hubs áttekintését az [Azure Event Hubs dokumentációban](https://docs.microsoft.com/azure/event-hubs/event-hubs-about?WT.mc_id=academic-17441-jabenn). Hogyan hasonlíthatók össze az alapvető funkciók az IoT Hubbal?

Ahhoz, hogy egy IoT eszköz csatlakozhasson az IoT Hubhoz, titkos kulcsot kell használnia, amely biztosítja, hogy csak engedélyezett eszközök csatlakozhassanak. Ugyanez vonatkozik az üzenetek olvasására is: a kódodnak egy titkos kulcsot tartalmazó kapcsolatkarakterláncra lesz szüksége, valamint az IoT Hub részleteire.

> 💁 Az alapértelmezett kapcsolatkarakterlánc, amelyet kapsz, **iothubowner** jogosultságokkal rendelkezik, ami teljes hozzáférést biztosít az IoT Hubhoz minden kód számára, amely ezt használja. Ideális esetben a lehető legalacsonyabb szintű jogosultságokkal kell csatlakozni. Erről a következő leckében lesz szó.

Miután az indító csatlakozott, a funkcióban lévő kód minden egyes, az IoT Hubhoz küldött üzenet esetén meghívásra kerül, függetlenül attól, hogy melyik eszköz küldte azt. Az indító paraméterként kapja meg az üzenetet.

### Feladat - Szerezd meg az Event Hub kompatibilis végpont kapcsolatkarakterláncát

1. A VS Code termináljában futtasd a következő parancsot az IoT Hub Event Hub kompatibilis végpontjának kapcsolatkarakterláncának megszerzéséhez:

    ```sh
    az iot hub connection-string show --default-eventhub \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Cseréld le a `<hub_name>` helyére az IoT Hub nevedet.

1. A VS Code-ban nyisd meg a `local.settings.json` fájlt. Adj hozzá egy új értéket a `Values` szekcióban:

    ```json
    "IOT_HUB_CONNECTION_STRING": "<connection string>"
    ```

    Cseréld le a `<connection string>` helyére az előző lépésben kapott értéket. Az érvényes JSON formátum érdekében vesszőt kell hozzáadnod az előző sor után.

### Feladat - Eseményindító létrehozása

Most már készen állsz az eseményindító létrehozására.

1. A VS Code termináljában futtasd a következő parancsot a `soil-moisture-trigger` mappán belül:

    ```sh
    func new --name iot-hub-trigger --template "Azure Event Hub trigger"
    ```

    Ez létrehoz egy új funkciót `iot-hub-trigger` néven. Az indító az IoT Hub Event Hub kompatibilis végpontjához csatlakozik, így egy Event Hub indítót használhatsz. Nincs külön IoT Hub indító.

Ez létrehoz egy mappát a `soil-moisture-trigger` mappán belül `iot-hub-trigger` néven, amely tartalmazza ezt a funkciót. Ez a mappa a következő fájlokat tartalmazza:

* `__init__.py` - Ez a Python kód fájl, amely az indítót tartalmazza, a szokásos Python fájlnév-konvenciót követve, hogy ez a mappa Python modul legyen.

    Ez a fájl a következő kódot tartalmazza:

    ```python
    import logging

    import azure.functions as func


    def main(event: func.EventHubEvent):
        logging.info('Python EventHub trigger processed an event: %s',
                    event.get_body().decode('utf-8'))
    ```

    Az indító magja a `main` függvény. Ez a függvény hívódik meg az IoT Hub eseményeivel. A függvénynek van egy `event` nevű paramétere, amely egy `EventHubEvent`-et tartalmaz. Minden alkalommal, amikor egy üzenet érkezik az IoT Hubhoz, ez a függvény meghívásra kerül, és az üzenetet az `event` paraméterként kapja meg, valamint azokat a tulajdonságokat, amelyek megegyeznek az előző leckében látott annotációkkal.

    A függvény magja az esemény naplózása.

* `function.json` - Ez az indító konfigurációját tartalmazza. A fő konfiguráció egy `bindings` nevű szekcióban található. A binding az Azure Functions és más Azure szolgáltatások közötti kapcsolatot jelenti. Ez a funkció egy bemeneti bindingot tartalmaz egy Event Hubhoz - csatlakozik egy Event Hubhoz, és adatokat fogad.

    > 💁 Kimeneti bindingok is léteznek, így a funkció kimenete egy másik szolgáltatásba kerülhet. Például hozzáadhatsz egy kimeneti bindingot egy adatbázishoz, és az IoT Hub eseményét visszaadhatod a funkcióból, amely automatikusan bekerül az adatbázisba.

    ✅ Kutatás: Olvass utána a bindingoknak az [Azure Functions triggers and bindings concepts dokumentációban](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python).

    A `bindings` szekció tartalmazza a binding konfigurációját. Az érdekes értékek a következők:

  * `"type": "eventHubTrigger"` - Ez jelzi a funkciónak, hogy Event Hub eseményeket kell figyelnie.
  * `"name": "events"` - Ez az Event Hub események paraméter neve. Ez megegyezik a Python kódban a `main` függvény paraméter nevével.
  * `"direction": "in"` - Ez egy bemeneti binding, az Event Hubból érkező adat a funkcióba kerül.
  * `"connection": ""` - Ez határozza meg, hogy melyik beállításból olvassa ki a kapcsolatkarakterláncot. Helyi futtatáskor ezt a beállítást a `local.settings.json` fájlból olvassa ki.

    > 💁 A kapcsolatkarakterlánc nem tárolható a `function.json` fájlban, azt a beállításokból kell kiolvasni. Ez megakadályozza, hogy véletlenül felfedd a kapcsolatkarakterláncot.

1. Az [Azure Functions sablon hibája](https://github.com/Azure/azure-functions-templates/issues/1250) miatt a `function.json` fájlban a `cardinality` mező értéke helytelen. Frissítsd ezt az értéket `many`-ról `one`-ra:

    ```json
    "cardinality": "one",
    ```

1. Frissítsd a `"connection"` értékét a `function.json` fájlban, hogy az újonnan hozzáadott értékre mutasson a `local.settings.json` fájlban:

    ```json
    "connection": "IOT_HUB_CONNECTION_STRING",
    ```

    > 💁 Ne feledd - ennek a beállításra kell mutatnia, nem tartalmazhatja a tényleges kapcsolatkarakterláncot.

1. A kapcsolatkarakterlánc tartalmazza az `eventHubName` értéket, így ennek az értéknek a `function.json` fájlban üres karakterláncra kell változnia. Frissítsd ezt az értéket üres karakterláncra:

    ```json
    "eventHubName": "",
    ```

### Feladat - Az eseményindító futtatása

1. Győződj meg róla, hogy az IoT Hub eseménymonitor nem fut. Ha ez az alkalmazás egyidejűleg fut a Functions alkalmazással, akkor a Functions alkalmazás nem tud csatlakozni és eseményeket feldolgozni.

    > 💁 Több alkalmazás is csatlakozhat az IoT Hub végpontjaihoz különböző *fogyasztói csoportok* használatával. Ezekről egy későbbi leckében lesz szó.

1. A Functions alkalmazás futtatásához futtasd a következő parancsot a VS Code termináljában:

    ```sh
    func start
    ```

    A Functions alkalmazás elindul, és felismeri az `iot-hub-trigger` funkciót. Ezután feldolgozza az IoT Hubhoz az elmúlt napban küldött eseményeket.

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    Functions:
    
            iot-hub-trigger: eventHubTrigger
    
    For detailed output, run func with --verbose flag.
    [2021-05-05T02:44:07.517Z] Worker process started and initialized.
    [2021-05-05T02:44:09.202Z] Executing 'Functions.iot-hub-trigger' (Reason='(null)', Id=802803a5-eae9-4401-a1f4-176631456ce4)
    [2021-05-05T02:44:09.205Z] Trigger Details: PartitionId: 0, Offset: 1011240-1011632, EnqueueTimeUtc: 2021-05-04T19:04:04.2030000Z-2021-05-04T19:04:04.3900000Z, SequenceNumber: 2546-2547, Count: 2
    [2021-05-05T02:44:09.352Z] Python EventHub trigger processed an event: {"soil_moisture":628}
    [2021-05-05T02:44:09.354Z] Python EventHub trigger processed an event: {"soil_moisture":624}
    [2021-05-05T02:44:09.395Z] Executed 'Functions.iot-hub-trigger' (Succeeded, Id=802803a5-eae9-4401-a1f4-176631456ce4, Duration=245ms)
    ```

    Minden funkcióhívást egy `Executing 'Functions.iot-hub-trigger'`/`Executed 'Functions.iot-hub-trigger'` blokk vesz körül a kimenetben, így láthatod, hány üzenetet dolgozott fel minden egyes funkcióhívás.

1. Győződj meg róla, hogy az IoT eszközöd fut. Új talajnedvesség-üzeneteket fogsz látni megjelenni a Functions alkalmazásban.

1. Állítsd le, majd indítsd újra a Functions alkalmazást. Látni fogod, hogy nem dolgozza fel újra a korábbi üzeneteket, csak az újakat.

> 💁 A VS Code támogatja a Functions hibakeresését is. Beállíthatsz töréspontokat, ha a kód sorának elején lévő szegélyre kattintasz, vagy a kurzort egy kódsorra helyezed, és kiválasztod a *Futtatás -> Töréspont beállítása* lehetőséget, vagy megnyomod az `F9` billentyűt. A hibakeresőt a *Futtatás -> Hibakeresés indítása* lehetőséggel, az `F5` billentyűvel, vagy a *Futtatás és hibakeresés* panelen a **Hibakeresés indítása** gombbal indíthatod el. Ezzel láthatod a feldolgozott események részleteit.

#### Hibakeresés

* Ha a következő hibát kapod:

    ```output
    The listener for function 'Functions.iot-hub-trigger' was unable to start. Microsoft.WindowsAzure.Storage: Connection refused. System.Net.Http: Connection refused. System.Private.CoreLib: Connection refused.
    ```

    Ellenőrizd, hogy az Azurite fut-e, és hogy az `AzureWebJobsStorage` beállítást a `local.settings.json` fájlban `UseDevelopmentStorage=true` értékre állítottad-e.

* Ha a következő hibát kapod:

    ```output
    System.Private.CoreLib: Exception while executing function: Functions.iot-hub-trigger. System.Private.CoreLib: Result: Failure Exception: AttributeError: 'list' object has no attribute 'get_body'
    ```

    Ellenőrizd, hogy a `function.json` fájlban a `cardinality` értékét `one`-ra állítottad-e.

* Ha a következő hibát kapod:

    ```output
    Azure.Messaging.EventHubs: The path to an Event Hub may be specified as part of the connection string or as a separate value, but not both.  Please verify that your connection string does not have the `EntityPath` token if you are passing an explicit Event Hub name. (Parameter 'connectionString').
    ```

    Ellenőrizd, hogy a `function.json` fájlban az `eventHubName` értékét üres karakterláncra állítottad-e.

## Közvetlen metóduskérések küldése szerver nélküli kódból

Eddig a Functions alkalmazás az Event Hub kompatibilis végpontot használva hallgatta az IoT Hub üzeneteit. Most parancsokat kell küldened az IoT eszköznek. Ezt az IoT Hubhoz való csatlakozással, a *Registry Manager* segítségével teheted meg. A Registry Manager egy eszköz, amely lehetővé teszi, hogy lásd, mely eszközök vannak regisztrálva az IoT Hubban, és kommunikálj ezekkel az eszközökkel felhőből eszközre üzenetek, közvetlen metóduskérések küldésével vagy az eszköz ikerének frissítésével. Ezenkívül használhatod eszközök regisztrálására, frissítésére vagy törlésére az IoT Hubban.

A Registry Managerhez való csatlakozáshoz kapcsolatkarakterláncra van szükséged.

### Feladat - Szerezd meg a Registry Manager kapcsolatkarakterláncát

1. A kapcsolatkarakterlánc megszerzéséhez futtasd a következő parancsot:

    ```sh
    az iot hub connection-string show --policy-name service \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Cseréld le a `<hub_name>` helyére az IoT Hub nevedet.

    A kapcsolatkarakterláncot a *ServiceConnect* házirendhez kérjük a `--policy-name service` paraméter használatával. Amikor kapcsolatkarakterláncot kérsz, megadhatod, hogy milyen jogosultságokat engedélyezzen az adott kapcsolatkarakterlánc. A ServiceConnect házirend lehetővé teszi a kódod számára, hogy csatlakozzon és üzeneteket küldjön IoT eszközöknek.

    ✅ Kutatás: Olvass utána a különböző házirendeknek az [IoT Hub jogosultságok dokumentációjában](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-security#iot-hub-permissions?WT.mc_id=academic-17441-jabenn).

1. A VS Code-ban nyisd meg a `local.settings.json` fájlt. Adj hozzá egy új értéket a `Values` szekcióban:

    ```json
    "REGISTRY_MANAGER_CONNECTION_STRING": "<connection string>"
    ```

    Cseréld le a `<connection string>` helyére az előző lépésben kapott értéket. Az érvényes JSON formátum érdekében vesszőt kell hozzáadnod az előző sor után.

### Feladat - Közvetlen metóduskérés küldése egy eszköznek

1. A Registry Manager SDK elérhető egy Pip csomagon keresztül. Add hozzá a következő sort a `requirements.txt` fájlhoz, hogy hozzáadd a csomag függőségét:

    ```sh
    azure-iot-hub
    ```

1. Győződj meg róla, hogy a VS Code termináljában a virtuális környezet aktiválva van, majd futtasd a következő parancsot a Pip csomagok telepítéséhez:

    ```sh
    pip install -r requirements.txt
    ```

1. Add hozzá a következő importokat az `__init__.py` fájlhoz:

    ```python
    import json
    import os
    from azure.iot.hub import IoTHubRegistryManager
    from azure.iot.hub.models import CloudToDeviceMethod
    ```

    Ez importál néhány rendszerkönyvtárat, valamint a Registry Managerrel való interakcióhoz és közvetlen metóduskérések küldéséhez szükséges könyvtárakat.

1. Távolítsd el a kódot a `main` metódus belsejéből, de hagyd meg magát a metódust.

1. A `main` metódusban add hozzá a következő kódot:

    ```python
    body = json.loads(event.get_body().decode('utf-8'))
    device_id = event.iothub_metadata['connection-device-id']

    logging.info(f'Received message: {body} from {device_id}')
    ```

    Ez a kód kinyeri az esemény törzsét, amely tartalmazza az IoT eszköz által küldött JSON üzenetet.

    Ezután megszerzi az eszközazonosítót az üzenethez mellékelt annotációkból. Az esemény törzse tartalmazza a telemetriának küldött üzenetet, az `iothub_metadata` szótár pedig az IoT Hub által beállított tulajdonságokat, például az üzenet küldőjének eszközazonosítóját és az üzenet küldésének idejét.

    Ez az információ naplózásra kerül. Ezt a naplózást látni fogod a terminálban, amikor helyileg futtatod a Functions alkalmazást.

1. Ez alá add hozzá a következő kódot:

    ```python
    soil_moisture = body['soil_moisture']

    if soil_moisture > 450:
        direct_method = CloudToDeviceMethod(method_name='relay_on', payload='{}')
    else:
        direct_method = CloudToDeviceMethod(method_name='relay_off', payload='{}')
    ```

    Ez a kód megszerzi az üzenetből a talajnedvesség értékét. Ezután ellenőrzi a talajnedvességet, és az értéktől függően létrehoz egy segédosztályt a `relay_on` vagy `relay_off` közvetlen metóduskéréshez. A
Ez a kód betölti a `REGISTRY_MANAGER_CONNECTION_STRING` értéket a `local.settings.json` fájlból. A fájlban található értékek környezeti változóként érhetők el, amelyeket az `os.environ` függvénnyel lehet olvasni. Ez a függvény egy szótárat ad vissza az összes környezeti változóról.

> 💁 Amikor ezt a kódot a felhőbe telepítik, a `local.settings.json` fájlban lévő értékek *Alkalmazásbeállításokként* lesznek beállítva, és ezek környezeti változókból olvashatók.

Ezután a kód létrehoz egy példányt a Registry Manager segédosztályból a kapcsolat karakterlánc segítségével.

1. Ez alá illessze be a következő kódot:

    ```python
    registry_manager.invoke_device_method(device_id, direct_method)

    logging.info('Direct method request sent!')
    ```

    Ez a kód utasítja a registry managert, hogy küldje el a közvetlen metódushívást annak az eszköznek, amelyik a telemetriát küldte.

    > 💁 Az alkalmazás korábbi verzióiban, amelyeket az MQTT használatával hozott létre, a relévezérlő parancsokat minden eszköznek elküldték. A kód feltételezte, hogy csak egy eszköze van. A kód ezen verziója egyetlen eszköznek küldi el a metódushívást, így akkor is működik, ha több nedvességérzékelő és relé van telepítve, és a megfelelő közvetlen metódushívást küldi a megfelelő eszköznek.

1. Futtassa a Functions alkalmazást, és győződjön meg róla, hogy az IoT eszköz adatokat küld. Látni fogja, hogy az üzenetek feldolgozásra kerülnek, és a közvetlen metódushívások elküldésre kerülnek. Mozgassa a talajnedvesség-érzékelőt a talajba és ki belőle, hogy lássa az értékek változását, valamint a relé ki- és bekapcsolását.

> 💁 Ezt a kódot megtalálja a [code/functions](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud/code/functions) mappában.

## Telepítse a szerver nélküli kódját a felhőbe

A kódja most már helyben működik, így a következő lépés a Functions App felhőbe telepítése.

### Feladat - felhő erőforrások létrehozása

A Functions alkalmazásának egy Azure Functions App erőforrásba kell települnie, amely az IoT Hub számára létrehozott Erőforráscsoportban található. Szüksége lesz egy Azure-ban létrehozott Storage Account-ra is, amely helyettesíti a helyben futó emulált tárolót.

1. Futtassa a következő parancsot egy tárolófiók létrehozásához:

    ```sh
    az storage account create --resource-group soil-moisture-sensor \
                              --sku Standard_LRS \
                              --name <storage_name> 
    ```

    Cserélje ki `<storage_name>`-t a tárolófiók nevére. Ennek globálisan egyedinek kell lennie, mivel az URL része lesz, amelyet a tárolófiók elérésére használnak. Csak kisbetűket és számokat használhat ehhez a névhez, más karakterek nem megengedettek, és a név legfeljebb 24 karakter hosszú lehet. Használjon például `sms`-t, és adjon hozzá egy egyedi azonosítót, például véletlenszerű szavakat vagy a nevét.

    A `--sku Standard_LRS` kiválasztja az árkategóriát, a legalacsonyabb költségű általános célú fiókot választva. Nincs ingyenes tárolási szint, és csak az igénybe vett szolgáltatásokért fizet. A költségek viszonylag alacsonyak, a legdrágább tárolás kevesebb mint 0,05 USD havonta gigabájtonként.

    ✅ Olvasson utána az árképzésnek az [Azure Storage Account árképzési oldalán](https://azure.microsoft.com/pricing/details/storage/?WT.mc_id=academic-17441-jabenn).

1. Futtassa a következő parancsot egy Functions App létrehozásához:

    ```sh
    az functionapp create --resource-group soil-moisture-sensor \
                          --runtime python \
                          --functions-version 3 \
                          --os-type Linux \
                          --consumption-plan-location <location> \
                          --storage-account <storage_name> \
                          --name <functions_app_name>
    ```

    Cserélje ki `<location>`-t arra a helyre, amelyet az Erőforráscsoport létrehozásakor használt az előző leckében.

    Cserélje ki `<storage_name>`-t a tárolófiók nevére, amelyet az előző lépésben hozott létre.

    Cserélje ki `<functions_app_name>`-t egy egyedi névre a Functions App számára. Ennek globálisan egyedinek kell lennie, mivel az URL része lesz, amelyet a Functions App elérésére használnak. Használjon például `soil-moisture-sensor-`-t, és adjon hozzá egy egyedi azonosítót, például véletlenszerű szavakat vagy a nevét.

    A `--functions-version 3` opció beállítja az Azure Functions verzióját. A 3-as verzió a legújabb.

    A `--os-type Linux` megadja, hogy a Functions runtime Linuxot használjon az alkalmazások futtatásához. Az alkalmazások Linuxon vagy Windowson futtathatók, a használt programozási nyelvtől függően. A Python alkalmazások csak Linuxon támogatottak.

### Feladat - alkalmazásbeállítások feltöltése

Amikor a Functions App-et fejlesztette, néhány beállítást tárolt a `local.settings.json` fájlban az IoT Hub kapcsolat karakterláncaihoz. Ezeket az értékeket az Azure-ban található Functions App Alkalmazásbeállításokba kell írni, hogy a kód használni tudja őket.

> 🎓 A `local.settings.json` fájl csak helyi fejlesztési beállításokra szolgál, és nem szabad forráskódvezérlésbe, például GitHubba feltölteni. Felhőbe telepítve Alkalmazásbeállításokat használnak. Az Alkalmazásbeállítások kulcs/érték párok, amelyek a felhőben vannak tárolva, és környezeti változókból olvashatók ki, akár a kódban, akár a runtime által, amikor a kódot az IoT Hubhoz csatlakoztatja.

1. Futtassa a következő parancsot az `IOT_HUB_CONNECTION_STRING` beállítás megadásához a Functions App Alkalmazásbeállításokban:

    ```sh
    az functionapp config appsettings set --resource-group soil-moisture-sensor \
                                          --name <functions_app_name> \
                                          --settings "IOT_HUB_CONNECTION_STRING=<connection string>"
    ```

    Cserélje ki `<functions_app_name>`-t a Functions App nevére, amelyet megadott.

    Cserélje ki `<connection string>`-t az `IOT_HUB_CONNECTION_STRING` értékére a `local.settings.json` fájlból.

1. Ismételje meg az előző lépést, de állítsa be a `REGISTRY_MANAGER_CONNECTION_STRING` értékét a `local.settings.json` fájl megfelelő értékére.

Amikor ezeket a parancsokat futtatja, a Functions App összes Alkalmazásbeállításának listáját is kiírja. Ezt használhatja annak ellenőrzésére, hogy az értékek helyesen vannak-e beállítva.

> 💁 Már látni fog egy értéket az `AzureWebJobsStorage` számára. A `local.settings.json` fájlban ez egy helyi tároló emulátor használatára volt beállítva. Amikor létrehozta a Functions App-et, a tárolófiókot paraméterként adta meg, és ez automatikusan beállításra került ebben a beállításban.

### Feladat - Functions App telepítése a felhőbe

Most, hogy a Functions App készen áll, a kód telepíthető.

1. Futtassa a következő parancsot a VS Code terminálból a Functions App közzétételéhez:

    ```sh
    func azure functionapp publish <functions_app_name>
    ```

    Cserélje ki `<functions_app_name>`-t a Functions App nevére, amelyet megadott.

A kód csomagolásra kerül, és elküldik a Functions App-nek, ahol telepítésre és elindításra kerül. Sok konzol kimenet lesz, amely a telepítés megerősítésével és a telepített funkciók listájával zárul. Ebben az esetben a lista csak a trigger-t fogja tartalmazni.

```output
Deployment successful.
Remote build succeeded!
Syncing triggers...
Functions in soil-moisture-sensor:
    iot-hub-trigger - [eventHubTrigger]
```

Győződjön meg róla, hogy az IoT eszköz fut. Változtassa meg a nedvességszintet a talajnedvesség állításával, vagy az érzékelő mozgatásával a talajba és ki belőle. Látni fogja, hogy a relé ki- és bekapcsol, ahogy a talajnedvesség változik.

---

## 🚀 Kihívás

Az előző leckében a relé időzítését úgy kezelte, hogy leiratkozott az MQTT üzenetekről, amíg a relé be volt kapcsolva, és rövid ideig azután, hogy kikapcsolt. Ezt a módszert itt nem használhatja - nem tud leiratkozni az IoT Hub triggeréről.

Gondoljon különböző módokra, hogyan kezelhetné ezt a Functions App-ben.

## Utólagos kvíz

[Utólagos kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/18)

## Áttekintés és önálló tanulás

* Olvasson a szerver nélküli számítástechnikáról a [Szerver nélküli számítástechnika Wikipedia oldalán](https://wikipedia.org/wiki/Serverless_computing).
* Olvasson az Azure-ban történő szerver nélküli használatról, beleértve további példákat is, a [Go serverless for your IoT needs Azure blogbejegyzésben](https://azure.microsoft.com/blog/go-serverless-for-your-iot-needs/?WT.mc_id=academic-17441-jabenn).
* Tudjon meg többet az Azure Functions-ről az [Azure Functions YouTube csatornán](https://www.youtube.com/c/AzureFunctions).

## Feladat

[Kézi relévezérlés hozzáadása](assignment.md)

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.