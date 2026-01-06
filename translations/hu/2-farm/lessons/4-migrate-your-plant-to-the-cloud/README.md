<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4d8e7a066d75b625e7a979c14157041d",
  "translation_date": "2025-08-27T23:09:24+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md",
  "language_code": "hu"
}
-->
# Migráld a növényedet a felhőbe

![A leckéről készült sketchnote áttekintése](../../../../../translated_images/lesson-8.3f21f3c11159e6a0a376351973ea5724d5de68fa23b4288853a174bed9ac48c3.hu.jpg)

> Sketchnote készítette: [Nitya Narasimhan](https://github.com/nitya). Kattints a képre a nagyobb verzióért.

Ez a lecke a [IoT for Beginners Project 2 - Digital Agriculture sorozat](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) részeként került bemutatásra a [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn) keretében.

[![Csatlakoztasd az eszközödet a felhőhöz az Azure IoT Hub segítségével](https://img.youtube.com/vi/bNxjopXkhvk/0.jpg)](https://youtu.be/bNxjopXkhvk)

## Előadás előtti kvíz

[Előadás előtti kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/15)

## Bevezetés

Az előző leckében megtanultad, hogyan csatlakoztasd a növényedet egy MQTT brokerhez, és hogyan irányíts egy relét egy helyben futó szerver kód segítségével. Ez képezi az alapját annak a fajta internetkapcsolattal rendelkező automatizált öntözőrendszernek, amelyet otthoni növényektől egészen a kereskedelmi farmokig használnak.

Az IoT eszköz egy nyilvános MQTT brokerrel kommunikált, hogy bemutassa az alapelveket, de ez nem a legmegbízhatóbb vagy legbiztonságosabb megoldás. Ebben a leckében megismerkedsz a felhővel és a nyilvános felhőszolgáltatások által nyújtott IoT lehetőségekkel. Megtanulod, hogyan migráld a növényedet egy ilyen felhőszolgáltatásra a nyilvános MQTT broker helyett.

Ebben a leckében az alábbiakat fogjuk áttekinteni:

* [Mi az a felhő?](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Felhő előfizetés létrehozása](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Felhő IoT szolgáltatások](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [IoT szolgáltatás létrehozása a felhőben](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Kommunikáció az IoT Hubbal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Eszköz csatlakoztatása az IoT szolgáltatáshoz](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)

## Mi az a felhő?

A felhő előtt, amikor egy vállalat szolgáltatásokat akart nyújtani az alkalmazottainak (például adatbázisokat vagy fájltárolást), vagy a nyilvánosságnak (például weboldalakat), adatközpontot épített és üzemeltetett. Ez lehetett egy kis szobányi számítógép, vagy egy épület tele számítógépekkel. A vállalat mindent maga kezelt, beleértve:

* Számítógépek vásárlása
* Hardver karbantartása
* Áramellátás és hűtés
* Hálózatkezelés
* Biztonság, beleértve az épület és a számítógépek szoftverének védelmét
* Szoftver telepítése és frissítése

Ez nagyon drága lehetett, széles körű szakértelmet igényelt, és lassú volt a változtatások végrehajtásában. Például, ha egy online áruháznak fel kellett készülnie egy forgalmas ünnepi szezonra, hónapokkal előre kellett terveznie, hogy több hardvert vásároljon, konfigurálja, telepítse, és telepítse a szoftvert az értékesítési folyamatok futtatásához. Az ünnepi szezon után, amikor az értékesítés visszaesett, a megvásárolt számítógépek kihasználatlanul álltak a következő forgalmas időszakig.

✅ Gondolod, hogy ez lehetővé tette a vállalatok számára, hogy gyorsan reagáljanak? Ha egy online ruházati kiskereskedő hirtelen népszerűvé válik, mert egy híresség az ő ruháit viseli, képesek lennének elég gyorsan növelni a számítástechnikai kapacitásukat, hogy támogassák a hirtelen megnövekedett rendeléseket?

### Valaki más számítógépe

A felhőt gyakran viccesen "valaki más számítógépének" nevezik. Az alapötlet egyszerű volt - a számítógépek vásárlása helyett bérelj valaki más számítógépét. Valaki más, egy felhőszolgáltató, hatalmas adatközpontokat üzemeltetne. Ők felelnének a hardver vásárlásáért és telepítéséért, az áramellátásért és hűtésért, a hálózatért, az épület biztonságáért, a hardver és szoftver frissítésekért, mindenért. Ügyfélként bérelhetnéd a szükséges számítógépeket, bérelhetnél többet, amikor a kereslet megugrik, majd csökkenthetnéd a bérlést, ha a kereslet visszaesik. Ezek az adatközpontok világszerte megtalálhatók.

![Egy Microsoft felhő adatközpont](../../../../../translated_images/azure-region-existing.73f704604f2aa6cb9b5a49ed40e93d4fd81ae3f4e6af4a8ca504023902832f56.hu.png)
![Egy Microsoft felhő adatközpont tervezett bővítése](../../../../../translated_images/azure-region-planned-expansion.a5074a1e8af74f156a73552d502429e5b126ea5019274d767ecb4b9afdad442b.hu.png)

Ezek az adatközpontok akár több négyzetkilométeresek is lehetnek. A fenti képek néhány évvel ezelőtt készültek egy Microsoft felhő adatközpontban, és az eredeti méretet, valamint a tervezett bővítést mutatják. A bővítéshez előkészített terület több mint 5 négyzetkilométer.

> 💁 Ezek az adatközpontok olyan nagy mennyiségű energiát igényelnek, hogy néhánynak saját erőműve van. Méretük és a felhőszolgáltatók befektetései miatt általában nagyon környezetbarátak. Hatékonyabbak, mint sok kis adatközpont, főként megújuló energiával működnek, és a felhőszolgáltatók keményen dolgoznak a hulladék csökkentésén, a vízhasználat minimalizálásán, és az erdők újratelepítésén, hogy pótolják azokat, amelyeket az adatközpontok építéséhez kivágtak. További információt arról, hogyan dolgozik egy felhőszolgáltató a fenntarthatóság érdekében, az [Azure fenntarthatósági oldalán](https://azure.microsoft.com/global-infrastructure/sustainability/?WT.mc_id=academic-17441-jabenn) találhatsz.

✅ Kutass egy kicsit: Olvass utána a nagyobb felhőszolgáltatóknak, mint például [Microsoft Azure](https://azure.microsoft.com/?WT.mc_id=academic-17441-jabenn) vagy [Google GCP](https://cloud.google.com). Hány adatközpontjuk van, és hol találhatók a világban?

A felhő használata csökkenti a vállalatok költségeit, és lehetővé teszi számukra, hogy arra koncentráljanak, amit a legjobban csinálnak, miközben a felhőszolgáltató kezeli a számítástechnikai szakértelmet. A vállalatoknak már nem kell adatközpont helyet bérelniük vagy vásárolniuk, különböző szolgáltatókat fizetniük a kapcsolatokért és az áramért, vagy szakértőket alkalmazniuk. Ehelyett egyetlen havi számlát fizethetnek a felhőszolgáltatónak, hogy mindenről gondoskodjanak.

A felhőszolgáltató pedig a méretgazdaságosságot kihasználva csökkentheti a költségeket, nagy mennyiségben vásárolhat számítógépeket alacsonyabb áron, befektethet eszközökbe a karbantartási munka csökkentése érdekében, sőt saját hardvert is tervezhet és építhet, hogy javítsa a felhőszolgáltatást.

### Microsoft Azure

Az Azure a Microsoft fejlesztői felhője, és ez az a felhő, amelyet ezekben a leckékben használni fogsz. Az alábbi videó rövid áttekintést nyújt az Azure-ról:

[![Azure áttekintő videó](../../../../../translated_images/what-is-azure-video-thumbnail.20174db09e03bbb8.hu.png)](https://www.microsoft.com/videoplayer/embed/RE4Ibng?WT.mc_id=academic-17441-jabenn)

## Felhő előfizetés létrehozása

Ahhoz, hogy szolgáltatásokat használj a felhőben, elő kell fizetned egy felhőszolgáltatónál. Ebben a leckében egy Microsoft Azure előfizetést fogsz létrehozni. Ha már van Azure előfizetésed, kihagyhatod ezt a feladatot. Az itt leírt előfizetési részletek az írás idején érvényesek, de változhatnak.

> 💁 Ha ezeket a leckéket az iskoládon keresztül éred el, lehet, hogy már van elérhető Azure előfizetésed. Ellenőrizd a tanároddal.

Két különböző típusú ingyenes Azure előfizetésre lehet jelentkezni:

* **Azure for Students** - Ez egy 18 év feletti diákok számára tervezett előfizetés. Nem szükséges hitelkártya a regisztrációhoz, és az iskolai e-mail címeddel igazolhatod, hogy diák vagy. Regisztrációkor 100 USD-t kapsz, amit felhőforrásokra költhetsz, valamint ingyenes szolgáltatásokat, beleértve egy IoT szolgáltatás ingyenes verzióját. Ez 12 hónapig tart, és minden évben megújítható, amíg diák maradsz.

* **Azure ingyenes előfizetés** - Ez bárki számára elérhető, aki nem diák. Hitelkártyára lesz szükséged a regisztrációhoz, de a kártyádat nem terhelik meg, csak arra használják, hogy igazolják, valódi ember vagy, nem pedig bot. Az első 30 napban 200 USD kreditet kapsz, amit bármely szolgáltatásra felhasználhatsz, valamint az Azure szolgáltatások ingyenes szintjeit. Miután a kredited elfogyott, a kártyádat nem terhelik meg, hacsak nem váltasz fizetős előfizetésre.

> 💁 A Microsoft kínál egy Azure for Students Starter előfizetést 18 év alatti diákok számára, de az írás idején ez nem támogatja az IoT szolgáltatásokat.

### Feladat - ingyenes felhő előfizetés létrehozása

Ha 18 év feletti diák vagy, akkor regisztrálhatsz egy Azure for Students előfizetésre. Ehhez iskolai e-mail címmel kell igazolnod magad. Ezt kétféleképpen teheted meg:

* Regisztrálj a GitHub diákfejlesztői csomagra a [education.github.com/pack](https://education.github.com/pack) oldalon. Ez számos eszközhöz és ajánlathoz biztosít hozzáférést, beleértve a GitHubot és a Microsoft Azure-t. Miután regisztráltál a fejlesztői csomagra, aktiválhatod az Azure for Students ajánlatot.

* Regisztrálj közvetlenül egy Azure for Students fiókra a [azure.microsoft.com/free/students](https://azure.microsoft.com/free/students/?WT.mc_id=academic-17441-jabenn) oldalon.

> ⚠️ Ha az iskolai e-mail címedet nem ismerik fel, nyiss egy [hibajegyet ebben a repóban](https://github.com/Microsoft/IoT-For-Beginners/issues), és megnézzük, hogy hozzáadható-e az Azure for Students engedélyezési listájához.

Ha nem vagy diák, vagy nincs érvényes iskolai e-mail címed, akkor regisztrálhatsz egy Azure ingyenes előfizetésre.

* Regisztrálj egy Azure ingyenes előfizetésre a [azure.microsoft.com/free](https://azure.microsoft.com/free/?WT.mc_id=academic-17441-jabenn) oldalon.

## Felhő IoT szolgáltatások

A nyilvános teszt MQTT broker, amelyet eddig használtál, nagyszerű eszköz tanuláshoz, de számos hátránya van, ha kereskedelmi környezetben szeretnéd használni:

* Megbízhatóság - ez egy ingyenes szolgáltatás, amely nem garantált, és bármikor leállítható
* Biztonság - nyilvános, így bárki hallgathatja a telemetriádat, vagy parancsokat küldhet az eszközeid irányítására
* Teljesítmény - csak néhány tesztüzenetre tervezték, így nem bírná el a nagy mennyiségű üzenetküldést
* Felfedezés - nincs mód arra, hogy megtudd, milyen eszközök vannak csatlakoztatva

A felhő IoT szolgáltatások megoldják ezeket a problémákat. Ezeket nagy felhőszolgáltatók tartják fenn, akik jelentős összegeket fektetnek a megbízhatóságba, és készen állnak arra, hogy megoldják az esetleges problémákat. Beépített biztonsággal rendelkeznek, hogy megakadályozzák a hackerek adatlopását vagy hamis parancsok küldését. Emellett nagy teljesítményűek, képesek napi több millió üzenetet kezelni, és a felhő segítségével szükség szerint skálázódnak.

> 💁 Bár ezekért a szolgáltatásokért havi díjat kell fizetni, a legtöbb felhőszolgáltató kínál egy ingyenes verziót az IoT szolgáltatásából, amely korlátozott számú napi üzenetet vagy csatlakoztatható eszközt engedélyez. Ez az ingyenes verzió általában bőven elegendő egy fejlesztő számára, hogy megismerje a szolgáltatást. Ebben a leckében az ingyenes verziót fogod használni.

Az IoT eszközök egy felhőszolgáltatáshoz csatlakoznak, vagy egy eszköz SDK (egy könyvtár, amely kódot biztosít a szolgáltatás funkcióinak használatához), vagy közvetlenül egy kommunikációs protokoll, például MQTT vagy HTTP segítségével. Az eszköz SDK általában a legegyszerűbb út, mivel mindent kezel, például tudja, milyen témákra kell publikálni vagy feliratkozni, és hogyan kell kezelni a biztonságot.

![Az eszközök egy eszköz SDK segítségével csatlakoznak a szolgáltatáshoz. A szerver kód szintén egy SDK-n keresztül csatlakozik a szolgáltatáshoz](../../../../../translated_images/iot-service-connectivity.7e873847921a5d6fd60d0ba3a943210194518cee0d4e362476624316443275c3.hu.png)

Az eszközöd ezután az alkalmazásod más részeivel kommunikál ezen a szolgáltatáson keresztül - hasonlóan ahhoz, ahogy telemetriát küldtél és parancsokat fogadtál az MQTT-n keresztül. Ez általában egy szolgáltatás SDK vagy egy hasonló könyvtár segítségével történik. Az üzenetek az eszközödről a szolgáltatáshoz érkeznek, ahol az alkalmazásod más komponensei elolvashatják őket, majd üzeneteket küldhetnek vissza az eszközödre.

![Az érvényes titkos kulccsal nem rendelkező eszközök nem tudnak csatlakozni az IoT szolgáltatáshoz](../../../../../translated_images/iot-service-allowed-denied-connection.818b0063ac213fb84204a7229303764d9b467ca430fb822b4ac2fca267d56726.hu.png)

Ezek a szolgáltatások biztonságot valósítanak meg azáltal, hogy ismerik az összes eszközt, amely csatlakozhat és adatokat küldhet, akár úgy, hogy az eszközöket előzetesen regisztrálják a szolgáltatásban, akár úgy, hogy az eszközök titkos kulcsokat vagy tanúsítványokat kapnak, amelyeket az első csatlakozáskor használhatnak a szolgáltatásba való reg
💁 Az IoT-szolgáltatások további képességeket is megvalósítanak, és a felhőszolgáltatók további szolgáltatásokat és alkalmazásokat kínálnak, amelyek csatlakoztathatók a szolgáltatáshoz. Például, ha az összes eszköz által küldött telemetriai üzeneteket egy adatbázisban szeretné tárolni, általában csak néhány kattintás szükséges a felhőszolgáltató konfigurációs eszközében, hogy a szolgáltatást csatlakoztassa az adatbázishoz, és az adatokat oda továbbítsa.
## Hozz létre egy IoT szolgáltatást a felhőben

Most, hogy van Azure-előfizetésed, regisztrálhatsz egy IoT szolgáltatásra. A Microsoft IoT szolgáltatása az Azure IoT Hub.

![Az Azure IoT Hub logója](../../../../../translated_images/azure-iot-hub-logo.28a19de76d0a1932464d858f7558712bcdace3e5ec69c434d482ed7ce41c3a26.hu.png)

Az alábbi videó rövid áttekintést nyújt az Azure IoT Hubról:

[![Azure IoT Hub áttekintő videó](https://img.youtube.com/vi/smuZaZZXKsU/0.jpg)](https://www.youtube.com/watch?v=smuZaZZXKsU)

> 🎥 Kattints a fenti képre a videó megtekintéséhez

✅ Szánj egy kis időt kutatásra, és olvasd el az IoT Hub áttekintését a [Microsoft IoT Hub dokumentációjában](https://docs.microsoft.com/azure/iot-hub/about-iot-hub?WT.mc_id=academic-17441-jabenn).

Az Azure-ban elérhető felhőszolgáltatások konfigurálhatók egy webes portálon keresztül vagy egy parancssori felületen (CLI) keresztül. Ehhez a feladathoz a CLI-t fogod használni.

### Feladat - Telepítsd az Azure CLI-t

Az Azure CLI használatához először telepítened kell a PC-dre vagy Mac-edre.

1. Kövesd az [Azure CLI dokumentációjában](https://docs.microsoft.com/cli/azure/install-azure-cli?WT.mc_id=academic-17441-jabenn) található utasításokat a CLI telepítéséhez.

1. Az Azure CLI számos bővítményt támogat, amelyek lehetővé teszik az Azure szolgáltatások széles körének kezelését. Telepítsd az IoT bővítményt az alábbi parancs futtatásával a parancssorban vagy terminálban:

    ```sh
    az extension add --name azure-iot
    ```

1. A parancssorban vagy terminálban futtasd az alábbi parancsot, hogy bejelentkezz az Azure-előfizetésedbe az Azure CLI-n keresztül.

    ```sh
    az login
    ```

    Egy weboldal fog megnyílni az alapértelmezett böngésződben. Jelentkezz be azzal a fiókkal, amelyet az Azure-előfizetésedhez használtál. Miután bejelentkeztél, bezárhatod a böngészőlapot.

1. Ha több Azure-előfizetésed van, például egy iskolai előfizetés és egy saját Azure for Students előfizetés, ki kell választanod, melyiket szeretnéd használni. Futtasd az alábbi parancsot, hogy listázd az összes előfizetést, amelyhez hozzáférsz:

    ```sh
    az account list --output table
    ```

    A kimenetben látni fogod az egyes előfizetések nevét és `SubscriptionId`-ját.

    ```output
    ➜  ~ az account list --output table
    Name                    CloudName    SubscriptionId                        State    IsDefault
    ----------------------  -----------  ------------------------------------  -------  -----------
    School-subscription     AzureCloud   cb30cde9-814a-42f0-a111-754cb788e4e1  Enabled  True
    Azure for Students      AzureCloud   fa51c31b-162c-4599-add6-781def2e1fbf  Enabled  False
    ```

    Az előfizetés kiválasztásához, amelyet használni szeretnél, használd az alábbi parancsot:

    ```sh
    az account set --subscription <SubscriptionId>
    ```

    Cseréld ki `<SubscriptionId>`-t az előfizetés azonosítójára, amelyet használni szeretnél. A parancs futtatása után futtasd újra a parancsot az előfizetések listázásához. Látni fogod, hogy az `IsDefault` oszlop `True` értéket kap az általad beállított előfizetésnél.

### Feladat - Hozz létre egy erőforráscsoportot

Az Azure szolgáltatásokat, például IoT Hub példányokat, virtuális gépeket, adatbázisokat vagy AI szolgáltatásokat **erőforrásoknak** nevezzük. Minden erőforrásnak egy **erőforráscsoportban** kell lennie, amely egy vagy több erőforrás logikai csoportosítása.

> 💁 Az erőforráscsoportok használatával egyszerre több szolgáltatást is kezelhetsz. Például, miután befejezted az összes leckét ehhez a projekthez, törölheted az erőforráscsoportot, és az összes benne lévő erőforrás automatikusan törlődik.

1. Az Azure adatközpontjai világszerte több régióra vannak felosztva. Amikor létrehozol egy Azure erőforrást vagy erőforráscsoportot, meg kell adnod, hogy hol szeretnéd létrehozni. Futtasd az alábbi parancsot a helyszínek listájának lekéréséhez:

    ```sh
    az account list-locations --output table
    ```

    Látni fogsz egy helyszínlistát. Ez a lista hosszú lesz.

    > 💁 A cikk írásakor 65 helyszín érhető el.

    ```output
        ➜  ~ az account list-locations --output table
    DisplayName               Name                 RegionalDisplayName
    ------------------------  -------------------  -------------------------------------
    East US                   eastus               (US) East US
    East US 2                 eastus2              (US) East US 2
    South Central US          southcentralus       (US) South Central US
    ...
    ```

    Jegyezd fel a régióhoz legközelebb eső `Name` oszlop értékét. A régiókat térképen megtalálhatod az [Azure geográfiai oldalán](https://azure.microsoft.com/global-infrastructure/geographies/?WT.mc_id=academic-17441-jabenn).

1. Futtasd az alábbi parancsot egy `soil-moisture-sensor` nevű erőforráscsoport létrehozásához. Az erőforráscsoport neveinek egyedinek kell lenniük az előfizetésedben.

    ```sh
    az group create --name soil-moisture-sensor \
                    --location <location>
    ```

    Cseréld ki `<location>`-t az előző lépésben kiválasztott helyszínre.

### Feladat - Hozz létre egy IoT Hubot

Most létrehozhatsz egy IoT Hub erőforrást az erőforráscsoportodban.

1. Használd az alábbi parancsot az IoT Hub erőforrás létrehozásához:

    ```sh
    az iot hub create --resource-group soil-moisture-sensor \
                      --sku F1 \
                      --partition-count 2 \
                      --name <hub_name>
    ```

    Cseréld ki `<hub_name>`-t az IoT Hub nevére. Ennek a névnek globálisan egyedinek kell lennie - azaz senki más nem hozhat létre ugyanilyen nevű IoT Hubot. Ez a név egy URL-ben szerepel, amely az IoT Hubra mutat, ezért kell egyedinek lennie. Használj például `soil-moisture-sensor-` nevet, és adj hozzá egy egyedi azonosítót, például véletlenszerű szavakat vagy a nevedet.

    Az `--sku F1` opció azt jelzi, hogy ingyenes szintet használ. Az ingyenes szint napi 8,000 üzenetet támogat, valamint a teljes árú szintek legtöbb funkcióját.

    > 🎓 Az Azure szolgáltatások különböző árazási szintjeit szinteknek nevezzük. Minden szintnek különböző költségei vannak, és különböző funkciókat vagy adatvolumeneket biztosít.

    > 💁 Ha többet szeretnél megtudni az árazásról, nézd meg az [Azure IoT Hub árazási útmutatót](https://azure.microsoft.com/pricing/details/iot-hub/?WT.mc_id=academic-17441-jabenn).

    Az `--partition-count 2` opció meghatározza, hogy az IoT Hub hány adatfolyamot támogat. Több partíció csökkenti az adatblokkolást, amikor több eszköz olvas és ír az IoT Hubba. A partíciók kívül esnek ezeknek a leckéknek a hatókörén, de ezt az értéket be kell állítani az ingyenes szintű IoT Hub létrehozásához.

    > 💁 Egy előfizetésben csak egy ingyenes szintű IoT Hub lehet.

Az IoT Hub létrejön. Ez egy percet vagy többet is igénybe vehet.

## Kommunikáció az IoT Hubbal

Az előző leckében MQTT-t használtál, és üzeneteket küldtél különböző témákra, amelyeknek különböző céljaik voltak. Az IoT Hubban nem különböző témákra küldesz üzeneteket, hanem meghatározott módokon kommunikál az eszköz a Hubbal, vagy a Hub az eszközzel.

> 💁 A háttérben az IoT Hub és az eszköz közötti kommunikáció MQTT-t, HTTPS-t vagy AMQP-t használhat.

* Eszköz-felhő (D2C) üzenetek - ezek az üzenetek az eszközről az IoT Hubba küldött üzenetek, például telemetria. Ezeket az alkalmazáskód olvashatja ki az IoT Hubból.

    > 🎓 A háttérben az IoT Hub egy Azure szolgáltatást használ, amelyet [Event Hubs](https://docs.microsoft.com/azure/event-hubs/?WT.mc_id=academic-17441-jabenn) néven ismerünk. Amikor kódot írsz az IoT Hubba küldött üzenetek olvasására, ezeket gyakran eseményeknek nevezik.

* Felhő-eszköz (C2D) üzenetek - ezek az üzenetek az alkalmazáskódból, egy IoT Hubon keresztül az IoT eszközre küldött üzenetek.

* Közvetlen módszerhívások - ezek az üzenetek az alkalmazáskódból, egy IoT Hubon keresztül az IoT eszközre küldött üzenetek, amelyek arra kérik az eszközt, hogy tegyen valamit, például vezéreljen egy aktuátort. Ezek az üzenetek választ igényelnek, hogy az alkalmazáskód megállapíthassa, sikeresen feldolgozták-e.

* Eszköz ikrek - ezek JSON dokumentumok, amelyeket az eszköz és az IoT Hub között szinkronizálnak, és beállításokat vagy más tulajdonságokat tárolnak, amelyeket az eszköz jelentett, vagy amelyeket az IoT Hubnak kell beállítania az eszközön (ezeket kívánt tulajdonságoknak nevezik).

Az IoT Hub üzeneteket és közvetlen módszerhívásokat tárolhat egy konfigurálható időtartamig (alapértelmezés szerint egy napig), így ha egy eszköz vagy alkalmazáskód elveszíti a kapcsolatot, akkor is visszanyerheti az offline állapotban küldött üzeneteket, miután újra csatlakozik. Az eszköz ikrek tartósan az IoT Hubban maradnak, így bármikor újra csatlakozhat egy eszköz, és megkaphatja az eszköz ikrek legfrissebb állapotát.

✅ Kutass egy kicsit: Olvass többet ezekről az üzenettípusokról a [Device-to-cloud kommunikációs útmutatóban](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-d2c-guidance?WT.mc_id=academic-17441-jabenn), és a [Cloud-to-device kommunikációs útmutatóban](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-c2d-guidance?WT.mc_id=academic-17441-jabenn) az IoT Hub dokumentációjában.

## Csatlakoztasd az eszközödet az IoT szolgáltatáshoz

Miután létrejött a Hub, az IoT eszközöd csatlakozhat hozzá. Csak regisztrált eszközök csatlakozhatnak a szolgáltatáshoz, ezért először regisztrálnod kell az eszközödet. A regisztráció során visszakaphatsz egy kapcsolati karakterláncot, amelyet az eszköz használhat a csatlakozáshoz. Ez a kapcsolati karakterlánc eszközspecifikus, és tartalmazza az IoT Hub, az eszköz adatait, valamint egy titkos kulcsot, amely lehetővé teszi az eszköz számára a csatlakozást.

> 🎓 A kapcsolati karakterlánc egy általános kifejezés egy szövegrészre, amely tartalmazza a kapcsolati adatokat. Ezeket IoT Hubokhoz, adatbázisokhoz és sok más szolgáltatáshoz való csatlakozáskor használják. Általában tartalmaznak egy azonosítót a szolgáltatáshoz, például egy URL-t, és biztonsági információkat, például egy titkos kulcsot. Ezeket SDK-khoz adják át a szolgáltatáshoz való csatlakozáshoz.

> ⚠️ A kapcsolati karakterláncokat biztonságban kell tartani! A biztonságról részletesebben egy későbbi leckében lesz szó.

### Feladat - Regisztráld az IoT eszközödet

Az IoT eszköz regisztrálható az IoT Hubban az Azure CLI használatával.

1. Futtasd az alábbi parancsot az eszköz regisztrálásához:

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor \
                                      --hub-name <hub_name>
    ```

    Cseréld ki `<hub_name>`-t az IoT Hub nevére, amelyet használtál.

    Ez létrehoz egy eszközt `soil-moisture-sensor` azonosítóval.

1. Amikor az IoT eszközöd az SDK használatával csatlakozik az IoT Hubhoz, egy kapcsolati karakterláncot kell használnia, amely megadja a Hub URL-jét, valamint egy titkos kulcsot. Futtasd az alábbi parancsot a kapcsolati karakterlánc lekéréséhez:

    ```sh
    az iot hub device-identity connection-string show --device-id soil-moisture-sensor \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    Cseréld ki `<hub_name>`-t az IoT Hub nevére, amelyet használtál.

1. Tárold el a kimenetben megjelenő kapcsolati karakterláncot, mert később szükséged lesz rá.

### Feladat - Csatlakoztasd az IoT eszközödet a felhőhöz

Dolgozd végig a megfelelő útmutatót, hogy csatlakoztasd az IoT eszközödet a felhőhöz:

* [Arduino - Wio Terminal](wio-terminal-connect-hub.md)
* [Egylapkás számítógép - Raspberry Pi/Virtual IoT eszköz](single-board-computer-connect-hub.md)

### Feladat - Események figyelése

Egyelőre nem fogod frissíteni a szerverkódodat. Ehelyett az Azure CLI-t használhatod az IoT eszközödről érkező események figyelésére.

1. Győződj meg róla, hogy az IoT eszközöd fut, és küldi a talajnedvesség telemetriai értékeket.

1. Futtasd az alábbi parancsot a parancssorban vagy terminálban, hogy figyeld az IoT Hubba küldött üzeneteket:

    ```sh
    az iot hub monitor-events --hub-name <hub_name>
    ```

    Cseréld ki `<hub_name>`-t az IoT Hub nevére, amelyet használtál.

    Látni fogod, hogy üzenetek jelennek meg a konzol kimenetében, ahogy az IoT eszközöd küldi őket.

    ```output
    Starting event monitor, use ctrl-c to stop...
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "payload": "{\"soil_moisture\": 376}"
        }
    },
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "payload": "{\"soil_moisture\": 381}"
        }
    }
    ```

    A `payload` tartalma megegyezik az IoT eszközöd által küldött üzenettel.

    > A cikk írásakor az `az iot` bővítmény nem működik teljesen Apple Silicon eszközökön. Ha Apple Silicon eszközt használsz, más módon kell figyelned az üzeneteket, például az [Azure IoT Tools for Visual Studio Code](https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-vscode-iot-toolkit-cloud-device-messaging) használatával.

1. Ezek az üzenetek automatikusan számos tulajdonságot kapnak, például az időbélyeget, amikor elküldték őket. Ezeket *annotációknak* nevezzük. Az összes üzenet annotáció megtekintéséhez használd az alábbi parancsot:

    ```sh
    az iot hub monitor-events --properties anno --hub-name <hub_name>
    ```

    Cseréld ki `<hub_name>`-t az IoT Hub nevére, amelyet használtál.

    Látni fogod, hogy üzenetek jelennek meg a konzol kimenetében, ahogy az IoT eszközöd küldi őket.

    ```output
    Starting event monitor, use ctrl-c to stop...
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "properties": {},
            "annotations": {
                "iothub-connection-device-id": "soil-moisture-sensor",
                "iothub-connection-auth-method": "{\"scope\":\"device\",\"type\":\"sas\",\"issuer\":\"iothub\",\"acceptingIpFilterRule\":null}",
                "iothub-connection-auth-generation-id": "637553997165220462",
                "iothub-enqueuedtime": 1619976150288,
                "iothub-message-source": "Telemetry",
                "x-opt-sequence-number": 1379,
                "x-opt-offset": "550576",
                "x-opt-enqueued-time": 1619976150277
            },
            "payload": "{\"soil_moisture\": 381}"
        }
    }
    ```

    Az annotációkban szereplő időértékek [UNIX idő](https://wikipedia.org/wiki/Unix_time) formátumban vannak, amely az 1970. január 1-jén éjfél óta eltelt másodpercek számát jelenti.

    Lépj ki az eseményfigyelőből, amikor végeztél.

### Feladat - Az IoT eszközöd vezérlése

Az Azure CLI-t használhatod arra is, hogy közvetlen módszereket hívj meg az IoT eszközödön.

1. Futtasd az alábbi parancsot a parancssorban vagy terminálban, hogy meghívd az `relay_on` módszert az IoT eszközön:

    ```sh
    az iot hub invoke-device-method --device-id soil-moisture-sensor \
                                    --method-name relay_on \
                                    --method-payload '{}' \
                                    --hub-name <hub_name>
    ```

    Cseréld ki `
<hub_name>
` az iot hub invoke-device-method --hub-name <iot-hub-name> --device-id <device-id> --method-name relay_on --method-payload '{}' ` parancsot, ahol `<iot-hub-name>` helyére az IoT Hub nevét írd, amit használsz.

Ez egy közvetlen metódushívást küld a `method-name` paraméterben megadott metódusra. A közvetlen metódusokhoz tartozhat egy payload, amely adatokat tartalmaz a metódus számára, és ezt JSON formátumban lehet megadni a `method-payload` paraméterben.

Látni fogod, hogy a relé bekapcsol, és az IoT eszközöd megfelelő kimenetet ad:

```output
    Direct method received -  relay_on
    ```

1. Ismételd meg a fenti lépést, de állítsd a `--method-name` paramétert `relay_off` értékre. Látni fogod, hogy a relé kikapcsol, és az IoT eszköz megfelelő kimenetet ad.

---

## 🚀 Kihívás

Az IoT Hub ingyenes csomagja napi 8,000 üzenetet engedélyez. Az általad írt kód 10 másodpercenként küld telemetriai üzeneteket. Hány üzenetet jelent ez naponta, ha 10 másodpercenként küldesz egyet?

Gondold át, milyen gyakran kellene a talajnedvesség-méréseket elküldeni? Hogyan tudnád módosítani a kódodat, hogy az ingyenes csomagon belül maradj, és olyan gyakran ellenőrizz, amennyire szükséges, de ne túl gyakran? Mi lenne, ha egy második eszközt is hozzáadnál?

## Előadás utáni kvíz

[Előadás utáni kvíz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/16)

## Áttekintés és önálló tanulás

Az IoT Hub SDK nyílt forráskódú mind Arduino, mind Python esetében. A GitHub kód-repozitóriumokban számos példa található, amelyek bemutatják, hogyan lehet különböző IoT Hub funkciókkal dolgozni.

* Ha Wio Terminalt használsz, nézd meg az [Arduino példákat a GitHubon](https://github.com/Azure/azure-iot-pal-arduino/tree/master/pal/samples)
* Ha Raspberry Pi-t vagy virtuális eszközt használsz, nézd meg a [Python példákat a GitHubon](https://github.com/Azure/azure-iot-sdk-python/tree/master/azure-iot-hub/samples)

## Feladat

[Tanulj a felhőszolgáltatásokról](assignment.md)

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.