<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4d8e7a066d75b625e7a979c14157041d",
  "translation_date": "2025-08-27T23:11:01+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md",
  "language_code": "cs"
}
-->
# Přesuňte svou rostlinu do cloudu

![Přehled této lekce ve formě sketchnote](../../../../../translated_images/lesson-8.3f21f3c11159e6a0a376351973ea5724d5de68fa23b4288853a174bed9ac48c3.cs.jpg)

> Sketchnote od [Nitya Narasimhan](https://github.com/nitya). Klikněte na obrázek pro větší verzi.

Tato lekce byla součástí [IoT for Beginners Project 2 - série Digitální zemědělství](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) od [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Připojte své zařízení ke cloudu pomocí Azure IoT Hub](https://img.youtube.com/vi/bNxjopXkhvk/0.jpg)](https://youtu.be/bNxjopXkhvk)

## Kvíz před lekcí

[Kvíz před lekcí](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/15)

## Úvod

V minulé lekci jste se naučili, jak připojit svou rostlinu k MQTT brokeru a ovládat relé pomocí serverového kódu běžícího lokálně. To tvoří základ internetově propojeného automatizovaného zavlažovacího systému, který se používá od jednotlivých rostlin doma až po komerční farmy.

IoT zařízení komunikovalo s veřejným MQTT brokerem jako způsob demonstrace principů, ale to není nejspolehlivější ani nejbezpečnější metoda. V této lekci se dozvíte o cloudu a IoT funkcích poskytovaných veřejnými cloudovými službami. Také se naučíte, jak přesunout svou rostlinu z veřejného MQTT brokeru na jednu z těchto cloudových služeb.

V této lekci se budeme zabývat:

* [Co je cloud?](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Vytvoření cloudového předplatného](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Cloudové IoT služby](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Vytvoření IoT služby v cloudu](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Komunikace s IoT Hub](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Připojení zařízení k IoT službě](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)

## Co je cloud?

Před cloudem, když chtěla firma poskytovat služby svým zaměstnancům (například databáze nebo úložiště souborů) nebo veřejnosti (například webové stránky), musela vybudovat a provozovat datové centrum. To mohlo být od místnosti s několika počítači až po budovu s mnoha počítači. Firma musela spravovat vše, včetně:

* Nákupu počítačů
* Údržby hardwaru
* Napájení a chlazení
* Síťové infrastruktury
* Zabezpečení, včetně zabezpečení budovy a softwaru na počítačích
* Instalace a aktualizace softwaru

To mohlo být velmi drahé, vyžadovalo širokou škálu kvalifikovaných zaměstnanců a bylo velmi pomalé při změnách, když to bylo potřeba. Například pokud by online obchod potřeboval plánovat na rušnou sváteční sezónu, musel by plánovat měsíce dopředu, aby nakoupil více hardwaru, nakonfiguroval ho, nainstaloval software a spustil prodejní proces. Po skončení sváteční sezóny, kdy prodeje opět klesnou, by zůstaly počítače, za které zaplatili, nevyužité až do další rušné sezóny.

✅ Myslíte si, že by to umožnilo firmám rychle reagovat? Pokud by se online prodejce oblečení náhle stal populárním díky celebritě, která byla viděna v jejich oblečení, dokázali by rychle zvýšit výpočetní výkon, aby zvládli náhlý příliv objednávek?

### Počítač někoho jiného

Cloud je často žertovně označován jako "počítač někoho jiného". Původní myšlenka byla jednoduchá - místo nákupu počítačů si pronajmete počítač někoho jiného. Někdo jiný, poskytovatel cloudových služeb, by spravoval obrovská datová centra. Byl by zodpovědný za nákup a instalaci hardwaru, správu napájení a chlazení, síťovou infrastrukturu, zabezpečení budovy, aktualizace hardwaru a softwaru, vše. Jako zákazník byste si pronajali počítače, které potřebujete, pronajímali více, když poptávka stoupá, a snižovali počet pronajatých počítačů, když poptávka klesá. Tato cloudová datová centra jsou po celém světě.

![Microsoft cloudové datové centrum](../../../../../translated_images/azure-region-existing.73f704604f2aa6cb9b5a49ed40e93d4fd81ae3f4e6af4a8ca504023902832f56.cs.png)
![Plánovaná expanze Microsoft cloudového datového centra](../../../../../translated_images/azure-region-planned-expansion.a5074a1e8af74f156a73552d502429e5b126ea5019274d767ecb4b9afdad442b.cs.png)

Tato datová centra mohou mít rozlohu několika čtverečních kilometrů. Obrázky výše byly pořízeny před několika lety v Microsoft cloudovém datovém centru a ukazují počáteční velikost spolu s plánovanou expanzí. Oblast vyčištěná pro expanzi má přes 5 čtverečních kilometrů.

> 💁 Tato datová centra vyžadují tak velké množství energie, že některá mají vlastní elektrárny. Díky své velikosti a úrovni investic od poskytovatelů cloudových služeb jsou obvykle velmi ekologická. Jsou efektivnější než obrovské množství malých datových center, běží převážně na obnovitelnou energii a poskytovatelé cloudových služeb se snaží snižovat odpad, omezovat spotřebu vody a znovu vysazovat lesy, aby nahradili ty, které byly vykáceny kvůli výstavbě datových center. Více o tom, jak jeden poskytovatel cloudových služeb pracuje na udržitelnosti, si můžete přečíst na [stránkách o udržitelnosti Azure](https://azure.microsoft.com/global-infrastructure/sustainability/?WT.mc_id=academic-17441-jabenn).

✅ Udělejte si průzkum: Přečtěte si o hlavních cloudových službách, jako je [Azure od Microsoftu](https://azure.microsoft.com/?WT.mc_id=academic-17441-jabenn) nebo [GCP od Googlu](https://cloud.google.com). Kolik datových center mají a kde se nacházejí?

Používání cloudu snižuje náklady pro firmy a umožňuje jim soustředit se na to, co dělají nejlépe, přičemž odborné znalosti v oblasti cloud computingu zůstávají v rukou poskytovatele. Firmy již nemusí pronajímat nebo kupovat prostor v datovém centru, platit různým poskytovatelům za konektivitu a energii nebo zaměstnávat odborníky. Místo toho mohou platit jeden měsíční účet poskytovateli cloudových služeb, který se postará o vše.

Poskytovatel cloudových služeb pak může využít úspory z rozsahu ke snížení nákladů, nakupovat počítače ve velkém za nižší ceny, investovat do nástrojů pro snížení pracovní zátěže při údržbě, dokonce navrhovat a vyrábět vlastní hardware pro zlepšení své cloudové nabídky.

### Microsoft Azure

Azure je cloud pro vývojáře od Microsoftu a je to cloud, který budete používat v těchto lekcích. Video níže poskytuje krátký přehled o Azure:

[![Video přehled Azure](../../../../../translated_images/what-is-azure-video-thumbnail.20174db09e03bbb8.cs.png)](https://www.microsoft.com/videoplayer/embed/RE4Ibng?WT.mc_id=academic-17441-jabenn)

## Vytvoření cloudového předplatného

Abyste mohli používat služby v cloudu, budete si muset zaregistrovat předplatné u poskytovatele cloudových služeb. Pro tuto lekci si zaregistrujete předplatné Microsoft Azure. Pokud již máte předplatné Azure, můžete tento úkol přeskočit. Podrobnosti o předplatném popsané zde jsou aktuální v době psaní, ale mohou se změnit.

> 💁 Pokud máte k těmto lekcím přístup prostřednictvím své školy, možná již máte k dispozici předplatné Azure. Zkontrolujte to u svého učitele.

Existují dva různé typy bezplatného předplatného Azure, které si můžete zaregistrovat:

* **Azure pro studenty** - Toto je předplatné určené pro studenty starší 18 let. K registraci nepotřebujete kreditní kartu a použijete svou školní e-mailovou adresu k ověření, že jste student. Po registraci získáte 100 USD na výdaje za cloudové zdroje spolu s bezplatnými službami, včetně bezplatné verze IoT služby. Toto předplatné trvá 12 měsíců a můžete ho obnovit každý rok, kdy zůstanete studentem.

* **Bezplatné předplatné Azure** - Toto je předplatné pro kohokoli, kdo není studentem. K registraci budete potřebovat kreditní kartu, ale vaše karta nebude účtována, slouží pouze k ověření, že jste skutečný člověk, nikoli bot. Získáte 200 USD kreditu na použití během prvních 30 dní na jakékoli služby spolu s bezplatnými úrovněmi služeb Azure. Jakmile váš kredit vyprší, vaše karta nebude účtována, pokud nepřevedete předplatné na režim platby za použití.

> 💁 Microsoft nabízí předplatné Azure pro studenty Starter pro studenty mladší 18 let, ale v době psaní tento typ předplatného nepodporuje žádné IoT služby.

### Úkol - registrace bezplatného cloudového předplatného

Pokud jste student starší 18 let, můžete si zaregistrovat předplatné Azure pro studenty. Budete muset ověřit svou školní e-mailovou adresu. Můžete to udělat dvěma způsoby:

* Zaregistrujte se do GitHub student developer pack na [education.github.com/pack](https://education.github.com/pack). To vám poskytne přístup k řadě nástrojů a nabídek, včetně GitHubu a Microsoft Azure. Po registraci do developer pack můžete aktivovat nabídku Azure pro studenty.

* Zaregistrujte se přímo na účet Azure pro studenty na [azure.microsoft.com/free/students](https://azure.microsoft.com/free/students/?WT.mc_id=academic-17441-jabenn).

> ⚠️ Pokud vaše školní e-mailová adresa není rozpoznána, vytvořte [problém v tomto repozitáři](https://github.com/Microsoft/IoT-For-Beginners/issues) a zjistíme, zda ji lze přidat do seznamu povolených adres Azure pro studenty.

Pokud nejste student nebo nemáte platnou školní e-mailovou adresu, můžete si zaregistrovat bezplatné předplatné Azure.

* Zaregistrujte se na bezplatné předplatné Azure na [azure.microsoft.com/free](https://azure.microsoft.com/free/?WT.mc_id=academic-17441-jabenn)

## Cloudové IoT služby

Veřejný testovací MQTT broker, který jste používali, je skvělý nástroj při učení, ale má několik nevýhod jako nástroj pro komerční použití:

* Spolehlivost - je to bezplatná služba bez záruk, která může být kdykoli vypnuta
* Zabezpečení - je veřejná, takže kdokoli může poslouchat vaši telemetrii nebo posílat příkazy k ovládání vašeho hardwaru
* Výkon - je navržena pouze pro několik testovacích zpráv, takže by nezvládla velké množství zpráv
* Objevování - neexistuje způsob, jak zjistit, jaká zařízení jsou připojena

IoT služby v cloudu tyto problémy řeší. Jsou spravovány velkými poskytovateli cloudových služeb, kteří investují do spolehlivosti a jsou připraveni řešit případné problémy. Mají zabudované zabezpečení, které brání hackerům číst vaše data nebo posílat falešné příkazy. Jsou také vysoce výkonné, schopné zvládnout mnoho milionů zpráv každý den, využívajíce cloud ke škálování podle potřeby.

> 💁 I když za tyto výhody platíte měsíčním poplatkem, většina poskytovatelů cloudových služeb nabízí bezplatnou verzi své IoT služby s omezeným počtem zpráv za den nebo zařízení, která se mohou připojit. Tato bezplatná verze je obvykle více než dostatečná pro vývojáře, aby se o službě naučil. V této lekci budete používat bezplatnou verzi.

IoT zařízení se připojují ke cloudové službě buď pomocí SDK zařízení (knihovny, která poskytuje kód pro práci s funkcemi služby), nebo přímo prostřednictvím komunikačního protokolu, jako je MQTT nebo HTTP. SDK zařízení je obvykle nejjednodušší cesta, protože se postará o vše, například o to, jaké témata publikovat nebo odebírat, a jak řešit zabezpečení.

![Zařízení se připojují ke službě pomocí SDK zařízení. Serverový kód se také připojuje ke službě prostřednictvím SDK](../../../../../translated_images/iot-service-connectivity.7e873847921a5d6fd60d0ba3a943210194518cee0d4e362476624316443275c3.cs.png)

Vaše zařízení pak komunikuje s ostatními částmi vaší aplikace prostřednictvím této služby - podobně jako jste posílali telemetrii a přijímali příkazy přes MQTT. To se obvykle děje pomocí SDK služby nebo podobné knihovny. Zprávy přicházejí z vašeho zařízení do služby, kde je ostatní komponenty vaší aplikace mohou číst, a zprávy mohou být posílány zpět na vaše zařízení.

![Zařízení bez platného tajného klíče se nemohou připojit k IoT službě](../../../../../translated_images/iot-service-allowed-denied-connection.818b0063ac213fb84204a7229303764d9b467ca430fb822b4ac2fca267d56726.cs.png)

Tyto služby implementují zabezpečení tím, že znají všechna zařízení, která se mohou připojit a posílat data, buď tím, že jsou zařízení předem registrována u služby, nebo tím, že zařízení mají tajné klíče nebo certifikáty, které mohou použít k registraci u služby při prvním připojení. Neznámá zařízení se nemohou připojit, pokud se o to pokusí, služba připojení odmítne a ignoruje zprávy, které posílají.

✅ Udělejte si průzkum: Jaká je nevýhoda otevřené IoT služby, kde se může připojit jakékoli zařízení nebo kód? Můžete najít konkrétní příklady hackerů, kteří toho využili?

Ostatní komponenty vaší aplikace se mohou připojit k IoT službě a zjistit všechna připojená nebo registrovaná zařízení a komunikovat s nimi přímo, buď hromadně, nebo jednotlivě.
💁 IoT služby také implementují další funkce a poskytovatelé cloudových služeb mají další služby a aplikace, které lze připojit k této službě. Například pokud chcete uložit všechny telemetrické zprávy zaslané všemi zařízeními do databáze, obvykle stačí jen několik kliknutí v konfiguračním nástroji poskytovatele cloudu, abyste službu připojili k databázi a začali streamovat data.
## Vytvoření IoT služby v cloudu

Nyní, když máte předplatné Azure, můžete se přihlásit k IoT službě. IoT služba od Microsoftu se nazývá Azure IoT Hub.

![Logo Azure IoT Hub](../../../../../translated_images/azure-iot-hub-logo.28a19de76d0a1932464d858f7558712bcdace3e5ec69c434d482ed7ce41c3a26.cs.png)

Níže uvedené video poskytuje krátký přehled o Azure IoT Hub:

[![Video o přehledu Azure IoT Hub](https://img.youtube.com/vi/smuZaZZXKsU/0.jpg)](https://www.youtube.com/watch?v=smuZaZZXKsU)

> 🎥 Klikněte na obrázek výše a podívejte se na video

✅ Udělejte si chvíli na průzkum a přečtěte si přehled IoT Hub v [dokumentaci Microsoft IoT Hub](https://docs.microsoft.com/azure/iot-hub/about-iot-hub?WT.mc_id=academic-17441-jabenn).

Cloudové služby dostupné v Azure lze konfigurovat prostřednictvím webového portálu nebo pomocí rozhraní příkazového řádku (CLI). Pro tento úkol budete používat CLI.

### Úkol - instalace Azure CLI

Abyste mohli používat Azure CLI, musíte jej nejprve nainstalovat na svůj PC nebo Mac.

1. Postupujte podle pokynů v [dokumentaci Azure CLI](https://docs.microsoft.com/cli/azure/install-azure-cli?WT.mc_id=academic-17441-jabenn) a nainstalujte CLI.

1. Azure CLI podporuje řadu rozšíření, která přidávají možnosti pro správu široké škály služeb Azure. Nainstalujte rozšíření IoT spuštěním následujícího příkazu z příkazového řádku nebo terminálu:

    ```sh
    az extension add --name azure-iot
    ```

1. Z příkazového řádku nebo terminálu spusťte následující příkaz pro přihlášení k vašemu předplatnému Azure prostřednictvím Azure CLI.

    ```sh
    az login
    ```

    Ve vašem výchozím prohlížeči se otevře webová stránka. Přihlaste se pomocí účtu, který jste použili k registraci předplatného Azure. Po přihlášení můžete zavřít kartu prohlížeče.

1. Pokud máte více předplatných Azure, například školní předplatné a vlastní předplatné Azure for Students, budete muset vybrat to, které chcete použít. Spusťte následující příkaz pro zobrazení všech předplatných, ke kterým máte přístup:

    ```sh
    az account list --output table
    ```

    Ve výstupu uvidíte název každého předplatného spolu s jeho `SubscriptionId`.

    ```output
    ➜  ~ az account list --output table
    Name                    CloudName    SubscriptionId                        State    IsDefault
    ----------------------  -----------  ------------------------------------  -------  -----------
    School-subscription     AzureCloud   cb30cde9-814a-42f0-a111-754cb788e4e1  Enabled  True
    Azure for Students      AzureCloud   fa51c31b-162c-4599-add6-781def2e1fbf  Enabled  False
    ```

    Chcete-li vybrat předplatné, které chcete použít, použijte následující příkaz:

    ```sh
    az account set --subscription <SubscriptionId>
    ```

    Nahraďte `<SubscriptionId>` ID předplatného, které chcete použít. Po spuštění tohoto příkazu znovu spusťte příkaz pro zobrazení vašich účtů. Uvidíte, že sloupec `IsDefault` bude označen jako `True` pro předplatné, které jste právě nastavili.

### Úkol - vytvoření skupiny prostředků

Služby Azure, jako jsou instance IoT Hub, virtuální počítače, databáze nebo AI služby, se označují jako **prostředky**. Každý prostředek musí být umístěn ve **skupině prostředků**, což je logické seskupení jednoho nebo více prostředků.

> 💁 Používání skupin prostředků znamená, že můžete spravovat více služeb najednou. Například po dokončení všech lekcí tohoto projektu můžete skupinu prostředků smazat a všechny prostředky v ní budou automaticky odstraněny.

1. Po celém světě existuje několik datových center Azure, rozdělených do regionů. Když vytvoříte prostředek nebo skupinu prostředků Azure, musíte určit, kde chcete, aby byla vytvořena. Spusťte následující příkaz pro získání seznamu lokalit:

    ```sh
    az account list-locations --output table
    ```

    Uvidíte seznam lokalit. Tento seznam bude dlouhý.

    > 💁 V době psaní tohoto textu je k dispozici 65 lokalit, kam můžete nasadit.

    ```output
        ➜  ~ az account list-locations --output table
    DisplayName               Name                 RegionalDisplayName
    ------------------------  -------------------  -------------------------------------
    East US                   eastus               (US) East US
    East US 2                 eastus2              (US) East US 2
    South Central US          southcentralus       (US) South Central US
    ...
    ```

    Poznamenejte si hodnotu ze sloupce `Name` regionu, který je vám nejblíže. Regiony můžete najít na mapě na stránce [Azure geographies](https://azure.microsoft.com/global-infrastructure/geographies/?WT.mc_id=academic-17441-jabenn).

1. Spusťte následující příkaz pro vytvoření skupiny prostředků nazvané `soil-moisture-sensor`. Názvy skupin prostředků musí být v rámci vašeho předplatného jedinečné.

    ```sh
    az group create --name soil-moisture-sensor \
                    --location <location>
    ```

    Nahraďte `<location>` lokalitou, kterou jste vybrali v předchozím kroku.

### Úkol - vytvoření IoT Hub

Nyní můžete vytvořit prostředek IoT Hub ve vaší skupině prostředků.

1. Použijte následující příkaz pro vytvoření prostředku IoT Hub:

    ```sh
    az iot hub create --resource-group soil-moisture-sensor \
                      --sku F1 \
                      --partition-count 2 \
                      --name <hub_name>
    ```

    Nahraďte `<hub_name>` názvem vašeho hubu. Tento název musí být globálně jedinečný - žádný jiný IoT Hub vytvořený kýmkoli jiným nemůže mít stejný název. Tento název se používá v URL, která odkazuje na hub, takže musí být jedinečný. Použijte něco jako `soil-moisture-sensor-` a přidejte jedinečný identifikátor na konec, například nějaká náhodná slova nebo vaše jméno.

    Možnost `--sku F1` říká, že se použije bezplatná úroveň. Bezplatná úroveň podporuje 8 000 zpráv denně spolu s většinou funkcí placených úrovní.

    > 🎓 Různé cenové úrovně služeb Azure se označují jako úrovně. Každá úroveň má jinou cenu a poskytuje různé funkce nebo objemy dat.

    > 💁 Pokud se chcete dozvědět více o cenách, můžete se podívat na [průvodce cenami Azure IoT Hub](https://azure.microsoft.com/pricing/details/iot-hub/?WT.mc_id=academic-17441-jabenn).

    Možnost `--partition-count 2` definuje, kolik datových proudů IoT Hub podporuje. Více oddílů snižuje blokování dat, když více zařízení čte a zapisuje do IoT Hub. Oddíly jsou mimo rozsah těchto lekcí, ale tato hodnota musí být nastavena pro vytvoření IoT Hub v bezplatné úrovni.

    > 💁 Na jedno předplatné můžete mít pouze jeden IoT Hub v bezplatné úrovni.

IoT Hub bude vytvořen. Dokončení může trvat minutu nebo dvě.

## Komunikace s IoT Hub

V předchozí lekci jste použili MQTT a posílali zprávy tam a zpět na různých tématech, přičemž různá témata měla různé účely. Místo posílání zpráv přes různá témata má IoT Hub několik definovaných způsobů, jak zařízení komunikovat s hubem nebo hub komunikovat se zařízením.

> 💁 Pod povrchem může tato komunikace mezi IoT Hub a vaším zařízením používat MQTT, HTTPS nebo AMQP.

* Zprávy z zařízení do cloudu (D2C) - to jsou zprávy posílané z zařízení do IoT Hub, například telemetrie. Tyto zprávy pak může vaše aplikační kód číst z IoT Hub.

    > 🎓 Pod povrchem IoT Hub používá službu Azure nazvanou [Event Hubs](https://docs.microsoft.com/azure/event-hubs/?WT.mc_id=academic-17441-jabenn). Když píšete kód pro čtení zpráv poslaných do hubu, často se nazývají události.

* Zprávy z cloudu do zařízení (C2D) - to jsou zprávy posílané z aplikačního kódu přes IoT Hub do IoT zařízení.

* Požadavky na přímé metody - to jsou zprávy posílané z aplikačního kódu přes IoT Hub do IoT zařízení, které požadují, aby zařízení něco provedlo, například ovládání aktuátoru. Tyto zprávy vyžadují odpověď, aby váš aplikační kód mohl zjistit, zda byly úspěšně zpracovány.

* Device twins - to jsou JSON dokumenty synchronizované mezi zařízením a IoT Hub, které se používají k ukládání nastavení nebo jiných vlastností buď hlášených zařízením, nebo nastavených na zařízení (známé jako požadované) IoT Hubem.

IoT Hub může ukládat zprávy a požadavky na přímé metody po konfigurovatelnou dobu (výchozí je jeden den), takže pokud zařízení nebo aplikační kód ztratí připojení, může po opětovném připojení stále získat zprávy poslané během offline režimu. Device twins jsou v IoT Hub uchovávány trvale, takže zařízení se může kdykoli znovu připojit a získat nejnovější device twin.

✅ Udělejte si průzkum: Přečtěte si více o těchto typech zpráv v [pokynech pro komunikaci z zařízení do cloudu](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-d2c-guidance?WT.mc_id=academic-17441-jabenn) a [pokynech pro komunikaci z cloudu do zařízení](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-c2d-guidance?WT.mc_id=academic-17441-jabenn) v dokumentaci IoT Hub.

## Připojení vašeho zařízení k IoT službě

Jakmile je hub vytvořen, vaše IoT zařízení se k němu může připojit. Připojit se mohou pouze registrovaná zařízení, takže budete muset nejprve zařízení zaregistrovat. Po registraci získáte zpět připojovací řetězec, který zařízení může použít k připojení. Tento připojovací řetězec je specifický pro zařízení a obsahuje informace o IoT Hubu, zařízení a tajný klíč, který umožní tomuto zařízení připojení.

> 🎓 Připojovací řetězec je obecný termín pro text, který obsahuje podrobnosti o připojení. Používají se při připojení k IoT Hubům, databázím a mnoha dalším službám. Obvykle se skládají z identifikátoru služby, jako je URL, a bezpečnostních informací, jako je tajný klíč. Tyto informace se předávají SDK pro připojení ke službě.

> ⚠️ Připojovací řetězce by měly být uchovávány v bezpečí! Bezpečnost bude podrobněji pokryta v budoucí lekci.

### Úkol - registrace vašeho IoT zařízení

IoT zařízení může být registrováno s vaším IoT Hubem pomocí Azure CLI.

1. Spusťte následující příkaz pro registraci zařízení:

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor \
                                      --hub-name <hub_name>
    ```

    Nahraďte `<hub_name>` názvem, který jste použili pro váš IoT Hub.

    Tím vytvoříte zařízení s ID `soil-moisture-sensor`.

1. Když se vaše IoT zařízení připojuje k vašemu IoT Hubu pomocí SDK, musí použít připojovací řetězec, který poskytuje URL hubu spolu s tajným klíčem. Spusťte následující příkaz pro získání připojovacího řetězce:

    ```sh
    az iot hub device-identity connection-string show --device-id soil-moisture-sensor \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    Nahraďte `<hub_name>` názvem, který jste použili pro váš IoT Hub.

1. Uložte připojovací řetězec, který se zobrazí ve výstupu, protože jej budete potřebovat později.

### Úkol - připojení vašeho IoT zařízení k cloudu

Projděte si relevantní průvodce pro připojení vašeho IoT zařízení k cloudu:

* [Arduino - Wio Terminal](wio-terminal-connect-hub.md)
* [Jednodeskový počítač - Raspberry Pi/virtuální IoT zařízení](single-board-computer-connect-hub.md)

### Úkol - monitorování událostí

Prozatím nebudete aktualizovat váš serverový kód. Místo toho můžete použít Azure CLI k monitorování událostí z vašeho IoT zařízení.

1. Ujistěte se, že vaše IoT zařízení běží a odesílá hodnoty telemetrie vlhkosti půdy.

1. Spusťte následující příkaz ve vašem příkazovém řádku nebo terminálu pro monitorování zpráv posílaných do vašeho IoT Hubu:

    ```sh
    az iot hub monitor-events --hub-name <hub_name>
    ```

    Nahraďte `<hub_name>` názvem, který jste použili pro váš IoT Hub.

    Uvidíte zprávy, které se objeví ve výstupu konzole, jakmile je vaše IoT zařízení odešle.

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

    Obsah `payload` bude odpovídat zprávě odeslané vaším IoT zařízením.

    > V době psaní tohoto textu rozšíření `az iot` nefunguje plně na Apple Silicon. Pokud používáte zařízení Apple Silicon, budete muset monitorovat zprávy jiným způsobem, například pomocí [Azure IoT Tools pro Visual Studio Code](https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-vscode-iot-toolkit-cloud-device-messaging).

1. Tyto zprávy mají automaticky připojené různé vlastnosti, jako je časové razítko, kdy byly odeslány. Tyto vlastnosti se nazývají *anotace*. Pro zobrazení všech anotací zpráv použijte následující příkaz:

    ```sh
    az iot hub monitor-events --properties anno --hub-name <hub_name>
    ```

    Nahraďte `<hub_name>` názvem, který jste použili pro váš IoT Hub.

    Uvidíte zprávy, které se objeví ve výstupu konzole, jakmile je vaše IoT zařízení odešle.

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

    Časové hodnoty v anotacích jsou v [UNIX čase](https://wikipedia.org/wiki/Unix_time), což představuje počet sekund od půlnoci 1. ledna 1970.

    Ukončete monitor událostí, když budete hotovi.

### Úkol - ovládání vašeho IoT zařízení

Pomocí Azure CLI můžete také volat přímé metody na vašem IoT zařízení.

1. Spusťte následující příkaz ve vašem příkazovém řádku nebo terminálu pro vyvolání metody `relay_on` na IoT zařízení:

    ```sh
    az iot hub invoke-device-method --device-id soil-moisture-sensor \
                                    --method-name relay_on \
                                    --method-payload '{}' \
                                    --hub-name <hub_name>
    ```

    Nahraďte `
<hub_name>
` se jménem, které jste použili pro svůj IoT Hub.

    Tímto odešlete požadavek na přímou metodu pro metodu specifikovanou jako `method-name`. Přímé metody mohou obsahovat datový payload pro metodu, který lze specifikovat v parametru `method-payload` jako JSON.

    Uvidíte, že relé se zapne, a odpovídající výstup z vašeho IoT zařízení:

    ```output
    Direct method received -  relay_on
    ```

1. Opakujte výše uvedený krok, ale nastavte `--method-name` na `relay_off`. Uvidíte, že relé se vypne a odpovídající výstup z IoT zařízení.

---

## 🚀 Výzva

Bezplatná úroveň IoT Hub umožňuje 8 000 zpráv denně. Kód, který jste napsali, odesílá telemetrické zprávy každých 10 sekund. Kolik zpráv denně to znamená, pokud je jedna zpráva každých 10 sekund?

Zamyslete se, jak často by mělo být odesíláno měření vlhkosti půdy? Jak můžete změnit svůj kód, abyste zůstali v rámci bezplatné úrovně, kontrolovali tak často, jak je potřeba, ale ne příliš často? Co kdybyste chtěli přidat druhé zařízení?

## Kvíz po přednášce

[Kvíz po přednášce](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/16)

## Přehled a samostudium

SDK pro IoT Hub je open source jak pro Arduino, tak pro Python. V repozitářích kódu na GitHubu je řada ukázek, které ukazují, jak pracovat s různými funkcemi IoT Hubu.

* Pokud používáte Wio Terminal, podívejte se na [Arduino ukázky na GitHubu](https://github.com/Azure/azure-iot-pal-arduino/tree/master/pal/samples)
* Pokud používáte Raspberry Pi nebo virtuální zařízení, podívejte se na [Python ukázky na GitHubu](https://github.com/Azure/azure-iot-sdk-python/tree/master/azure-iot-hub/samples)

## Zadání

[Zjistěte více o cloudových službách](assignment.md)

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádné nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.