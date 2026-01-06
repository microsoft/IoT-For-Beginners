<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4d8e7a066d75b625e7a979c14157041d",
  "translation_date": "2025-08-28T11:19:14+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md",
  "language_code": "sk"
}
-->
# Migrujte svoju rastlinu do cloudu

![Prehľad tejto lekcie v sketchnote](../../../../../translated_images/lesson-8.3f21f3c11159e6a0a376351973ea5724d5de68fa23b4288853a174bed9ac48c3.sk.jpg)

> Sketchnote od [Nitya Narasimhan](https://github.com/nitya). Kliknite na obrázok pre väčšiu verziu.

Táto lekcia bola súčasťou [IoT pre začiatočníkov Projekt 2 - Digitálne poľnohospodárstvo](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) z [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Pripojte svoje zariadenie k cloudu pomocou Azure IoT Hub](https://img.youtube.com/vi/bNxjopXkhvk/0.jpg)](https://youtu.be/bNxjopXkhvk)

## Kvíz pred prednáškou

[Kvíz pred prednáškou](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/15)

## Úvod

V poslednej lekcii ste sa naučili, ako pripojiť svoju rastlinu k MQTT brokeru a ovládať relé pomocou serverového kódu, ktorý beží lokálne. Toto je základ internetovo pripojeného automatizovaného zavlažovacieho systému, ktorý sa používa od jednotlivých rastlín doma až po komerčné farmy.

IoT zariadenie komunikovalo s verejným MQTT brokerom ako spôsob demonštrácie princípov, ale toto nie je najspoľahlivejší ani najbezpečnejší spôsob. V tejto lekcii sa dozviete o cloude a IoT schopnostiach poskytovaných verejnými cloudovými službami. Naučíte sa tiež, ako migrovať svoju rastlinu na jednu z týchto cloudových služieb z verejného MQTT brokera.

V tejto lekcii sa budeme venovať:

* [Čo je cloud?](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Vytvorenie cloudového predplatného](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Cloudové IoT služby](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Vytvorenie IoT služby v cloude](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Komunikácia s IoT Hub](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Pripojenie zariadenia k IoT službe](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)

## Čo je cloud?

Pred cloudom, keď spoločnosť chcela poskytovať služby svojim zamestnancom (ako databázy alebo ukladanie súborov) alebo verejnosti (ako webové stránky), musela vybudovať a prevádzkovať dátové centrum. To mohlo byť od miestnosti s malým počtom počítačov až po budovu s mnohými počítačmi. Spoločnosť musela spravovať všetko, vrátane:

* Nákupu počítačov
* Údržby hardvéru
* Napájania a chladenia
* Sieťovania
* Bezpečnosti, vrátane zabezpečenia budovy a softvéru na počítačoch
* Inštalácie a aktualizácie softvéru

Toto mohlo byť veľmi drahé, vyžadovať širokú škálu kvalifikovaných zamestnancov a byť veľmi pomalé pri zmene, keď to bolo potrebné. Napríklad, ak online obchod potreboval plánovať rušnú sviatočnú sezónu, musel plánovať mesiace dopredu, aby kúpil viac hardvéru, nakonfiguroval ho, nainštaloval a pripravil softvér na prevádzku predajného procesu. Po skončení sviatočnej sezóny a poklese predaja by zostali s počítačmi, za ktoré zaplatili, ale ktoré by boli nečinné až do ďalšej rušnej sezóny.

✅ Myslíte si, že by to umožnilo spoločnostiam rýchlo reagovať? Ak by sa online predajca oblečenia náhle stal populárnym vďaka celebritám, ktoré nosia jeho oblečenie, dokázal by rýchlo zvýšiť výpočtový výkon na podporu náhleho nárastu objednávok?

### Počítač niekoho iného

Cloud sa často žartovne označuje ako „počítač niekoho iného“. Pôvodná myšlienka bola jednoduchá - namiesto nákupu počítačov si prenajmete počítač niekoho iného. Niekto iný, poskytovateľ cloud computingu, by spravoval obrovské dátové centrá. Bol by zodpovedný za nákup a inštaláciu hardvéru, správu napájania a chladenia, sieťovanie, zabezpečenie budovy, aktualizácie hardvéru a softvéru, všetko. Ako zákazník by ste si prenajali počítače, ktoré potrebujete, prenajímali viac, keď dopyt stúpa, a znižovali počet prenajatých počítačov, keď dopyt klesá. Tieto cloudové dátové centrá sú po celom svete.

![Microsoft cloudové dátové centrum](../../../../../translated_images/azure-region-existing.73f704604f2aa6cb9b5a49ed40e93d4fd81ae3f4e6af4a8ca504023902832f56.sk.png)
![Plánovaná expanzia Microsoft cloudového dátového centra](../../../../../translated_images/azure-region-planned-expansion.a5074a1e8af74f156a73552d502429e5b126ea5019274d767ecb4b9afdad442b.sk.png)

Tieto dátové centrá môžu mať rozlohu niekoľkých štvorcových kilometrov. Obrázky vyššie boli urobené pred niekoľkými rokmi v Microsoft cloudovom dátovom centre a ukazujú počiatočnú veľkosť spolu s plánovanou expanziou. Oblasť vyčistená pre expanziu má viac ako 5 štvorcových kilometrov.

> 💁 Tieto dátové centrá vyžadujú také veľké množstvo energie, že niektoré majú vlastné elektrárne. Vďaka svojej veľkosti a úrovni investícií od poskytovateľov cloudu sú zvyčajne veľmi ekologické. Sú efektívnejšie ako obrovské množstvo malých dátových centier, fungujú prevažne na obnoviteľnej energii a poskytovatelia cloudu tvrdo pracujú na znižovaní odpadu, obmedzovaní spotreby vody a znovuzalesňovaní oblastí, ktoré boli vyrúbané na výstavbu dátových centier. Viac o tom, ako jeden poskytovateľ cloudu pracuje na udržateľnosti, si môžete prečítať na [stránke o udržateľnosti Azure](https://azure.microsoft.com/global-infrastructure/sustainability/?WT.mc_id=academic-17441-jabenn).

✅ Urobte si výskum: Prečítajte si o hlavných cloudových službách, ako [Azure od Microsoftu](https://azure.microsoft.com/?WT.mc_id=academic-17441-jabenn) alebo [GCP od Google](https://cloud.google.com). Koľko dátových centier majú a kde sa nachádzajú vo svete?

Používanie cloudu znižuje náklady pre spoločnosti a umožňuje im sústrediť sa na to, čo robia najlepšie, pričom odborné znalosti v oblasti cloud computingu zostávajú v rukách poskytovateľa. Spoločnosti už nemusia prenajímať alebo kupovať priestor v dátovom centre, platiť rôznym poskytovateľom za konektivitu a energiu alebo zamestnávať odborníkov. Namiesto toho môžu platiť jeden mesačný účet poskytovateľovi cloudu, ktorý sa postará o všetko.

Poskytovateľ cloudu potom môže využiť úspory z rozsahu na zníženie nákladov, nakupovať počítače vo veľkom za nižšie ceny, investovať do nástrojov na zníženie pracovného zaťaženia pri údržbe, dokonca navrhovať a vyrábať vlastný hardvér na zlepšenie svojej cloudovej ponuky.

### Microsoft Azure

Azure je vývojársky cloud od Microsoftu a je to cloud, ktorý budete používať v týchto lekciách. Video nižšie poskytuje krátky prehľad o Azure:

[![Prehľad videa o Azure](../../../../../translated_images/what-is-azure-video-thumbnail.20174db09e03bbb8.sk.png)](https://www.microsoft.com/videoplayer/embed/RE4Ibng?WT.mc_id=academic-17441-jabenn)

## Vytvorenie cloudového predplatného

Na používanie služieb v cloude sa budete musieť prihlásiť na odber predplatného u poskytovateľa cloudu. Pre túto lekciu sa budete prihlasovať na predplatné Microsoft Azure. Ak už máte predplatné Azure, môžete túto úlohu preskočiť. Podrobnosti o predplatnom uvedené tu sú aktuálne v čase písania, ale môžu sa zmeniť.

> 💁 Ak máte prístup k týmto lekciám prostredníctvom svojej školy, možno už máte k dispozícii predplatné Azure. Skontrolujte to u svojho učiteľa.

Existujú dva rôzne typy bezplatného predplatného Azure, na ktoré sa môžete prihlásiť:

* **Azure pre študentov** - Toto je predplatné určené pre študentov vo veku 18+. Na registráciu nepotrebujete kreditnú kartu a na overenie, že ste študent, použijete svoju školskú e-mailovú adresu. Po registrácii získate 100 USD na výdavky na cloudové zdroje spolu s bezplatnými službami vrátane bezplatnej verzie IoT služby. Toto predplatné trvá 12 mesiacov a môžete ho obnoviť každý rok, keď zostanete študentom.

* **Bezplatné predplatné Azure** - Toto je predplatné pre každého, kto nie je študentom. Na registráciu budete potrebovať kreditnú kartu, ale vaša karta nebude účtovaná, slúži len na overenie, že ste skutočný človek, nie bot. Získate 200 USD kreditu na použitie počas prvých 30 dní na akúkoľvek službu spolu s bezplatnými úrovňami služieb Azure. Po vyčerpaní kreditu vám karta nebude účtovaná, pokiaľ neprejdete na predplatné s platbou podľa použitia.

> 💁 Microsoft ponúka predplatné Azure pre študentov Starter pre študentov mladších ako 18 rokov, ale v čase písania tento typ predplatného nepodporuje žiadne IoT služby.

### Úloha - registrácia na bezplatné cloudové predplatné

Ak ste študent vo veku 18+, môžete sa prihlásiť na predplatné Azure pre študentov. Budete musieť overiť svoju školskú e-mailovú adresu. Môžete to urobiť dvoma spôsobmi:

* Zaregistrujte sa na GitHub balík pre študentov na [education.github.com/pack](https://education.github.com/pack). To vám poskytne prístup k množstvu nástrojov a ponúk, vrátane GitHubu a Microsoft Azure. Po registrácii na balík pre študentov môžete aktivovať ponuku Azure pre študentov.

* Zaregistrujte sa priamo na účet Azure pre študentov na [azure.microsoft.com/free/students](https://azure.microsoft.com/free/students/?WT.mc_id=academic-17441-jabenn).

> ⚠️ Ak vaša školská e-mailová adresa nie je rozpoznaná, otvorte [problém v tomto repozitári](https://github.com/Microsoft/IoT-For-Beginners/issues) a uvidíme, či ju môžeme pridať do zoznamu povolených pre Azure pre študentov.

Ak nie ste študentom alebo nemáte platnú školskú e-mailovú adresu, môžete sa prihlásiť na bezplatné predplatné Azure.

* Zaregistrujte sa na bezplatné predplatné Azure na [azure.microsoft.com/free](https://azure.microsoft.com/free/?WT.mc_id=academic-17441-jabenn)

## Cloudové IoT služby

Verejný testovací MQTT broker, ktorý ste používali, je skvelý nástroj na učenie, ale má niekoľko nevýhod ako nástroj na použitie v komerčnom prostredí:

* Spoľahlivosť - je to bezplatná služba bez záruk, ktorá môže byť kedykoľvek vypnutá
* Bezpečnosť - je verejná, takže ktokoľvek môže počúvať vašu telemetriu alebo posielať príkazy na ovládanie vášho hardvéru
* Výkon - je navrhnutá len na niekoľko testovacích správ, takže by nezvládla veľké množstvo správ
* Zisťovanie - neexistuje spôsob, ako zistiť, aké zariadenia sú pripojené

IoT služby v cloude riešia tieto problémy. Sú spravované veľkými poskytovateľmi cloudu, ktorí investujú veľké prostriedky do spoľahlivosti a sú pripravení riešiť akékoľvek problémy, ktoré môžu vzniknúť. Majú zabudovanú bezpečnosť, ktorá zabraňuje hackerom čítať vaše dáta alebo posielať falošné príkazy. Sú tiež vysoko výkonné, schopné zvládnuť mnoho miliónov správ denne, pričom využívajú cloud na škálovanie podľa potreby.

> 💁 Hoci za tieto výhody platíte mesačným poplatkom, väčšina poskytovateľov cloudu ponúka bezplatnú verziu svojej IoT služby s obmedzeným počtom správ denne alebo zariadení, ktoré sa môžu pripojiť. Táto bezplatná verzia je zvyčajne viac než dostatočná na to, aby sa vývojár naučil o službe. V tejto lekcii budete používať bezplatnú verziu.

IoT zariadenia sa pripájajú k cloudovej službe buď pomocou SDK zariadenia (knižnice, ktorá poskytuje kód na prácu s funkciami služby), alebo priamo cez komunikačný protokol, ako je MQTT alebo HTTP. SDK zariadenia je zvyčajne najjednoduchšia cesta, pretože sa postará o všetko za vás, napríklad o to, aké témy publikovať alebo odoberať, a ako spracovať bezpečnosť.

![Zariadenia sa pripájajú k službe pomocou SDK zariadenia. Serverový kód sa tiež pripája k službe cez SDK](../../../../../translated_images/iot-service-connectivity.7e873847921a5d6fd60d0ba3a943210194518cee0d4e362476624316443275c3.sk.png)

Vaše zariadenie potom komunikuje s ostatnými časťami vašej aplikácie cez túto službu - podobne ako ste posielali telemetriu a prijímali príkazy cez MQTT. To sa zvyčajne robí pomocou SDK služby alebo podobnej knižnice. Správy prichádzajú z vášho zariadenia do služby, kde ich ostatné komponenty vašej aplikácie môžu čítať, a správy môžu byť posielané späť na vaše zariadenie.

![Zariadenia bez platného tajného kľúča sa nemôžu pripojiť k IoT službe](../../../../../translated_images/iot-service-allowed-denied-connection.818b0063ac213fb84204a7229303764d9b467ca430fb822b4ac2fca267d56726.sk.png)

Tieto služby implementujú bezpečnosť tým, že poznajú všetky zariadenia, ktoré sa môžu pripojiť a posielať dáta, buď tým, že majú zariadenia predregistrované v službe, alebo tým, že zariadeniam poskytujú tajné kľúče alebo certifikáty, ktoré môžu použiť na registráciu v službe pri prvom pripojení. Neznáme zariadenia sa nemôžu pripojiť, ak sa pokúsia, služba odmietne pripojenie a ignoruje správy od nich.

✅ Urobte si výskum: Aká je nevýhoda otvorenej IoT služby, kde sa môže pripojiť akékoľvek zariadenie alebo kód? Nájdete konkrétne príklady hackerov, ktorí využili túto situáciu?

Ostatné komponenty vašej aplikácie sa môžu pripojiť k IoT službe a dozvedieť sa o všetkých zariadeniach, ktoré sú pripojené alebo registrované, a komunikovať s nimi priamo, či už hromadne alebo individuálne.
💁 IoT služby implementujú aj ďalšie funkcie a poskytovatelia cloudových služieb ponúkajú ďalšie služby a aplikácie, ktoré je možné pripojiť k tejto službe. Napríklad, ak chcete ukladať všetky telemetrické správy odoslané všetkými zariadeniami do databázy, zvyčajne stačí len niekoľko kliknutí v konfiguračnom nástroji poskytovateľa cloudu na pripojenie služby k databáze a streamovanie údajov.
## Vytvorenie IoT služby v cloude

Teraz, keď máte predplatné Azure, môžete sa prihlásiť na IoT službu. IoT služba od Microsoftu sa nazýva Azure IoT Hub.

![Logo Azure IoT Hub](../../../../../translated_images/azure-iot-hub-logo.28a19de76d0a1932464d858f7558712bcdace3e5ec69c434d482ed7ce41c3a26.sk.png)

Video nižšie poskytuje krátky prehľad o Azure IoT Hub:

[![Prehľad videa o Azure IoT Hub](https://img.youtube.com/vi/smuZaZZXKsU/0.jpg)](https://www.youtube.com/watch?v=smuZaZZXKsU)

> 🎥 Kliknite na obrázok vyššie a pozrite si video

✅ Nájdite si chvíľu na výskum a prečítajte si prehľad IoT Hub v [dokumentácii Microsoft IoT Hub](https://docs.microsoft.com/azure/iot-hub/about-iot-hub?WT.mc_id=academic-17441-jabenn).

Cloudové služby dostupné v Azure je možné konfigurovať prostredníctvom webového portálu alebo cez rozhranie príkazového riadku (CLI). Pre túto úlohu budete používať CLI.

### Úloha - inštalácia Azure CLI

Na používanie Azure CLI ho najskôr musíte nainštalovať na svoj PC alebo Mac.

1. Postupujte podľa pokynov v [dokumentácii Azure CLI](https://docs.microsoft.com/cli/azure/install-azure-cli?WT.mc_id=academic-17441-jabenn) na inštaláciu CLI.

1. Azure CLI podporuje množstvo rozšírení, ktoré pridávajú schopnosti na správu širokého spektra služieb Azure. Nainštalujte rozšírenie IoT spustením nasledujúceho príkazu z príkazového riadku alebo terminálu:

    ```sh
    az extension add --name azure-iot
    ```

1. Z príkazového riadku alebo terminálu spustite nasledujúci príkaz na prihlásenie do svojho predplatného Azure cez Azure CLI.

    ```sh
    az login
    ```

    Vo vašom predvolenom prehliadači sa otvorí webová stránka. Prihláste sa pomocou účtu, ktorý ste použili na registráciu predplatného Azure. Po prihlásení môžete kartu prehliadača zavrieť.

1. Ak máte viacero predplatných Azure, napríklad školské predplatné a vlastné predplatné Azure for Students, budete si musieť vybrať, ktoré chcete použiť. Spustite nasledujúci príkaz na zobrazenie zoznamu všetkých predplatných, ku ktorým máte prístup:

    ```sh
    az account list --output table
    ```

    Vo výstupe uvidíte názov každého predplatného spolu s jeho `SubscriptionId`.

    ```output
    ➜  ~ az account list --output table
    Name                    CloudName    SubscriptionId                        State    IsDefault
    ----------------------  -----------  ------------------------------------  -------  -----------
    School-subscription     AzureCloud   cb30cde9-814a-42f0-a111-754cb788e4e1  Enabled  True
    Azure for Students      AzureCloud   fa51c31b-162c-4599-add6-781def2e1fbf  Enabled  False
    ```

    Na výber predplatného, ktoré chcete použiť, použite nasledujúci príkaz:

    ```sh
    az account set --subscription <SubscriptionId>
    ```

    Nahraďte `<SubscriptionId>` identifikátorom predplatného, ktoré chcete použiť. Po spustení tohto príkazu znovu spustite príkaz na zobrazenie svojich účtov. Uvidíte, že stĺpec `IsDefault` bude označený ako `True` pre predplatné, ktoré ste práve nastavili.

### Úloha - vytvorenie skupiny zdrojov

Služby Azure, ako sú inštancie IoT Hub, virtuálne počítače, databázy alebo AI služby, sa označujú ako **zdroje**. Každý zdroj musí byť umiestnený v **skupine zdrojov**, čo je logické zoskupenie jedného alebo viacerých zdrojov.

> 💁 Používanie skupín zdrojov znamená, že môžete spravovať viacero služieb naraz. Napríklad, keď dokončíte všetky lekcie pre tento projekt, môžete odstrániť skupinu zdrojov a všetky zdroje v nej budú automaticky odstránené.

1. Po celom svete existuje viacero dátových centier Azure, rozdelených do regiónov. Keď vytvárate zdroj alebo skupinu zdrojov Azure, musíte špecifikovať, kde chcete, aby bola vytvorená. Spustite nasledujúci príkaz na získanie zoznamu lokalít:

    ```sh
    az account list-locations --output table
    ```

    Uvidíte zoznam lokalít. Tento zoznam bude dlhý.

    > 💁 V čase písania tohto textu je k dispozícii 65 lokalít, do ktorých môžete nasadiť.

    ```output
        ➜  ~ az account list-locations --output table
    DisplayName               Name                 RegionalDisplayName
    ------------------------  -------------------  -------------------------------------
    East US                   eastus               (US) East US
    East US 2                 eastus2              (US) East US 2
    South Central US          southcentralus       (US) South Central US
    ...
    ```

    Poznačte si hodnotu zo stĺpca `Name` regiónu, ktorý je vám najbližší. Regióny môžete nájsť na mape na stránke [Azure geographies](https://azure.microsoft.com/global-infrastructure/geographies/?WT.mc_id=academic-17441-jabenn).

1. Spustite nasledujúci príkaz na vytvorenie skupiny zdrojov s názvom `soil-moisture-sensor`. Názvy skupín zdrojov musia byť jedinečné vo vašom predplatnom.

    ```sh
    az group create --name soil-moisture-sensor \
                    --location <location>
    ```

    Nahraďte `<location>` lokalitou, ktorú ste vybrali v predchádzajúcom kroku.

### Úloha - vytvorenie IoT Hub

Teraz môžete vytvoriť zdroj IoT Hub vo svojej skupine zdrojov.

1. Použite nasledujúci príkaz na vytvorenie zdroja IoT Hub:

    ```sh
    az iot hub create --resource-group soil-moisture-sensor \
                      --sku F1 \
                      --partition-count 2 \
                      --name <hub_name>
    ```

    Nahraďte `<hub_name>` názvom pre váš hub. Tento názov musí byť globálne jedinečný - to znamená, že žiadny iný IoT Hub vytvorený kýmkoľvek nemôže mať rovnaký názov. Tento názov sa používa v URL, ktorá smeruje na hub, takže musí byť jedinečný. Použite niečo ako `soil-moisture-sensor-` a pridajte jedinečný identifikátor na koniec, napríklad náhodné slová alebo vaše meno.

    Možnosť `--sku F1` určuje použitie bezplatnej úrovne. Bezplatná úroveň podporuje 8 000 správ denne spolu s väčšinou funkcií plne platených úrovní.

    > 🎓 Rôzne cenové úrovne služieb Azure sa označujú ako úrovne. Každá úroveň má inú cenu a poskytuje rôzne funkcie alebo objemy dát.

    > 💁 Ak sa chcete dozvedieť viac o cenách, môžete si pozrieť [príručku o cenách Azure IoT Hub](https://azure.microsoft.com/pricing/details/iot-hub/?WT.mc_id=academic-17441-jabenn).

    Možnosť `--partition-count 2` definuje, koľko dátových tokov IoT Hub podporuje. Viacero oddielov znižuje blokovanie dát, keď viaceré zariadenia čítajú a zapisujú do IoT Hub. Oddiely sú mimo rozsahu týchto lekcií, ale táto hodnota musí byť nastavená na vytvorenie bezplatnej úrovne IoT Hub.

    > 💁 Na jedno predplatné môžete mať iba jeden IoT Hub na bezplatnej úrovni.

IoT Hub bude vytvorený. Môže to trvať minútu alebo dve.

## Komunikácia s IoT Hub

V predchádzajúcej lekcii ste používali MQTT a posielali správy tam a späť na rôznych témach, pričom rôzne témy mali rôzne účely. Namiesto posielania správ cez rôzne témy má IoT Hub niekoľko definovaných spôsobov, ako môže zariadenie komunikovať s Hubom alebo Hub komunikovať so zariadením.

> 💁 Pod povrchom táto komunikácia medzi IoT Hub a vaším zariadením môže používať MQTT, HTTPS alebo AMQP.

* Správy zo zariadenia do cloudu (D2C) - ide o správy posielané zo zariadenia do IoT Hub, ako napríklad telemetria. Tieto správy potom môže čítať váš aplikačný kód.

    > 🎓 Pod povrchom IoT Hub používa službu Azure nazývanú [Event Hubs](https://docs.microsoft.com/azure/event-hubs/?WT.mc_id=academic-17441-jabenn). Keď píšete kód na čítanie správ poslaných do hubu, tieto sa často nazývajú udalosti.

* Správy z cloudu do zariadenia (C2D) - ide o správy posielané z aplikačného kódu cez IoT Hub na IoT zariadenie.

* Požiadavky na priame metódy - ide o správy posielané z aplikačného kódu cez IoT Hub na IoT zariadenie, aby zariadenie vykonalo nejakú akciu, napríklad ovládanie aktuátora. Tieto správy vyžadujú odpoveď, aby váš aplikačný kód vedel, či boli úspešne spracované.

* Dvojčatá zariadení - ide o JSON dokumenty synchronizované medzi zariadením a IoT Hub, ktoré sa používajú na ukladanie nastavení alebo iných vlastností buď hlásených zariadením, alebo nastavených na zariadení (označované ako požadované) IoT Hubom.

IoT Hub môže ukladať správy a požiadavky na priame metódy na konfigurovateľné obdobie (predvolene jeden deň), takže ak zariadenie alebo aplikačný kód stratí pripojenie, môže po opätovnom pripojení stále získať správy poslané počas jeho offline stavu. Dvojčatá zariadení sú trvalo uložené v IoT Hub, takže zariadenie sa môže kedykoľvek pripojiť a získať najnovšie dvojča zariadenia.

✅ Urobte si výskum: Prečítajte si viac o týchto typoch správ v [usmernení pre komunikáciu zo zariadenia do cloudu](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-d2c-guidance?WT.mc_id=academic-17441-jabenn) a [usmernení pre komunikáciu z cloudu do zariadenia](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-c2d-guidance?WT.mc_id=academic-17441-jabenn) v dokumentácii IoT Hub.

## Pripojenie zariadenia k IoT službe

Keď je hub vytvorený, vaše IoT zariadenie sa k nemu môže pripojiť. Pripojiť sa môžu iba registrované zariadenia, takže najskôr budete musieť zariadenie zaregistrovať. Po registrácii získate reťazec pripojenia, ktorý zariadenie môže použiť na pripojenie. Tento reťazec pripojenia je špecifický pre zariadenie a obsahuje informácie o IoT Hub, zariadení a tajný kľúč, ktorý umožní tomuto zariadeniu pripojiť sa.

> 🎓 Reťazec pripojenia je všeobecný termín pre text, ktorý obsahuje detaily pripojenia. Používajú sa pri pripojení k IoT Hubom, databázam a mnohým ďalším službám. Zvyčajne pozostávajú z identifikátora služby, ako je URL, a bezpečnostných informácií, ako je tajný kľúč. Tieto sa odovzdávajú SDK na pripojenie k službe.

> ⚠️ Reťazce pripojenia by mali byť uchovávané v bezpečí! Bezpečnosť bude podrobnejšie pokrytá v budúcej lekcii.

### Úloha - registrácia IoT zariadenia

IoT zariadenie môže byť zaregistrované vo vašom IoT Hub pomocou Azure CLI.

1. Spustite nasledujúci príkaz na registráciu zariadenia:

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor \
                                      --hub-name <hub_name>
    ```

    Nahraďte `<hub_name>` názvom, ktorý ste použili pre váš IoT Hub.

    Týmto sa vytvorí zariadenie s ID `soil-moisture-sensor`.

1. Keď sa vaše IoT zariadenie pripojí k vášmu IoT Hub pomocou SDK, musí použiť reťazec pripojenia, ktorý poskytuje URL hubu spolu s tajným kľúčom. Spustite nasledujúci príkaz na získanie reťazca pripojenia:

    ```sh
    az iot hub device-identity connection-string show --device-id soil-moisture-sensor \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    Nahraďte `<hub_name>` názvom, ktorý ste použili pre váš IoT Hub.

1. Uložte reťazec pripojenia, ktorý sa zobrazí vo výstupe, pretože ho budete potrebovať neskôr.

### Úloha - pripojenie IoT zariadenia k cloudu

Prejdite si relevantný návod na pripojenie IoT zariadenia k cloudu:

* [Arduino - Wio Terminal](wio-terminal-connect-hub.md)
* [Jednodoskový počítač - Raspberry Pi/virtuálne IoT zariadenie](single-board-computer-connect-hub.md)

### Úloha - monitorovanie udalostí

Zatiaľ nebudete aktualizovať svoj serverový kód. Namiesto toho môžete použiť Azure CLI na monitorovanie udalostí z vášho IoT zariadenia.

1. Uistite sa, že vaše IoT zariadenie beží a posiela hodnoty telemetrie vlhkosti pôdy.

1. Spustite nasledujúci príkaz vo svojom príkazovom riadku alebo termináli na monitorovanie správ poslaných do vášho IoT Hub:

    ```sh
    az iot hub monitor-events --hub-name <hub_name>
    ```

    Nahraďte `<hub_name>` názvom, ktorý ste použili pre váš IoT Hub.

    Uvidíte správy, ktoré sa zobrazia vo výstupe konzoly, keď ich vaše IoT zariadenie odošle.

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

    Obsah `payload` bude zodpovedať správe poslanej vaším IoT zariadením.

    > V čase písania tohto textu rozšírenie `az iot` nefunguje úplne na Apple Silicon. Ak používate zariadenie Apple Silicon, budete musieť monitorovať správy iným spôsobom, napríklad pomocou [Azure IoT Tools pre Visual Studio Code](https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-vscode-iot-toolkit-cloud-device-messaging).

1. Tieto správy majú množstvo vlastností automaticky pripojených, ako je časová pečiatka, kedy boli poslané. Tieto vlastnosti sú známe ako *anotácie*. Na zobrazenie všetkých anotácií správ použite nasledujúci príkaz:

    ```sh
    az iot hub monitor-events --properties anno --hub-name <hub_name>
    ```

    Nahraďte `<hub_name>` názvom, ktorý ste použili pre váš IoT Hub.

    Uvidíte správy, ktoré sa zobrazia vo výstupe konzoly, keď ich vaše IoT zariadenie odošle.

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

    Časové hodnoty v anotáciách sú v [UNIX čase](https://wikipedia.org/wiki/Unix_time), ktorý predstavuje počet sekúnd od polnoci 1. januára 1970.

    Ukončite monitor udalostí, keď skončíte.

### Úloha - ovládanie IoT zariadenia

Pomocou Azure CLI môžete tiež volať priame metódy na vašom IoT zariadení.

1. Spustite nasledujúci príkaz vo svojom príkazovom riadku alebo termináli na vyvolanie metódy `relay_on` na IoT zariadení:

    ```sh
    az iot hub invoke-device-method --device-id soil-moisture-sensor \
                                    --method-name relay_on \
                                    --method-payload '{}' \
                                    --hub-name <hub_name>
    ```

    Nahraďte `
<hub_name>
` s názvom, ktorý ste použili pre váš IoT Hub.

    Týmto sa odošle požiadavka na priamu metódu pre metódu špecifikovanú ako `method-name`. Priame metódy môžu obsahovať payload s údajmi pre metódu, ktorý je možné špecifikovať v parametri `method-payload` vo formáte JSON.

    Uvidíte, že relé sa zapne, a zodpovedajúci výstup z vášho IoT zariadenia:

    ```output
    Direct method received -  relay_on
    ```

1. Opakujte vyššie uvedený krok, ale nastavte `--method-name` na `relay_off`. Uvidíte, že relé sa vypne a zodpovedajúci výstup z IoT zariadenia.

---

## 🚀 Výzva

Bezplatná úroveň IoT Hub umožňuje 8 000 správ denne. Kód, ktorý ste napísali, odosiela telemetrické správy každých 10 sekúnd. Koľko správ denne predstavuje jedna správa každých 10 sekúnd?

Zamyslite sa, ako často by sa mali odosielať merania vlhkosti pôdy? Ako môžete zmeniť svoj kód, aby ste zostali v rámci bezplatnej úrovne, kontrolovali tak často, ako je potrebné, ale nie príliš často? Čo ak by ste chceli pridať druhé zariadenie?

## Kvíz po prednáške

[Kvíz po prednáške](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/16)

## Prehľad a samostatné štúdium

SDK pre IoT Hub je open source pre Arduino aj Python. V repozitároch kódu na GitHube nájdete množstvo ukážok, ktoré ukazujú, ako pracovať s rôznymi funkciami IoT Hub.

* Ak používate Wio Terminal, pozrite si [Arduino ukážky na GitHube](https://github.com/Azure/azure-iot-pal-arduino/tree/master/pal/samples)
* Ak používate Raspberry Pi alebo virtuálne zariadenie, pozrite si [Python ukážky na GitHube](https://github.com/Azure/azure-iot-sdk-python/tree/master/azure-iot-hub/samples)

## Zadanie

[Zistite viac o cloudových službách](assignment.md)

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho rodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nie sme zodpovední za žiadne nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.