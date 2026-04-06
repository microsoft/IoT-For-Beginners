# Spusťte detektor ovoce na okraji

![Přehled této lekce ve formě sketchnote](../../../../../translated_images/cs/lesson-17.bc333c3c35ba8e42.webp)

> Sketchnote od [Nitya Narasimhan](https://github.com/nitya). Klikněte na obrázek pro větší verzi.

Toto video poskytuje přehled o spuštění klasifikátorů obrázků na IoT zařízeních, což je téma této lekce.

[![Custom Vision AI na Azure IoT Edge](https://img.youtube.com/vi/_K5fqGLO8us/0.jpg)](https://www.youtube.com/watch?v=_K5fqGLO8us)

## Kvíz před přednáškou

[Kvíz před přednáškou](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/33)

## Úvod

V minulé lekci jste použili svůj klasifikátor obrázků k rozlišení zralého a nezralého ovoce, přičemž jste odesílali obrázky zachycené kamerou na vašem IoT zařízení přes internet do cloudové služby. Tyto požadavky zabírají čas, stojí peníze a v závislosti na typu obrazových dat, která používáte, mohou mít dopady na soukromí.

V této lekci se naučíte, jak spouštět modely strojového učení (ML) na okraji - na IoT zařízeních, která běží ve vaší vlastní síti, nikoli v cloudu. Naučíte se výhody a nevýhody edge computingu oproti cloud computingu, jak nasadit svůj AI model na okraj a jak k němu přistupovat z vašeho IoT zařízení.

V této lekci se zaměříme na:

* [Edge computing](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Azure IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Registrace IoT Edge zařízení](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Nastavení IoT Edge zařízení](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Export vašeho modelu](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Příprava kontejneru pro nasazení](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Nasazení kontejneru](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Použití IoT Edge zařízení](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)

## Edge computing

Edge computing zahrnuje použití počítačů, které zpracovávají data IoT co nejblíže místu, kde jsou data generována. Místo zpracování v cloudu se přesouvá na okraj cloudu - do vaší interní sítě.

![Diagram architektury zobrazující internetové služby v cloudu a IoT zařízení v lokální síti](../../../../../translated_images/cs/cloud-without-edge.b4da641f6022c95e.webp)

V dosavadních lekcích jste měli zařízení, která shromažďovala data a odesílala je do cloudu k analýze, kde běžely serverless funkce nebo AI modely.

![Diagram architektury zobrazující IoT zařízení v lokální síti připojená k edge zařízením, která se připojují k cloudu](../../../../../translated_images/cs/cloud-with-edge.1e26462c62c126fe.webp)

Edge computing zahrnuje přesun některých cloudových služeb z cloudu na počítače běžící ve stejné síti jako IoT zařízení, přičemž komunikace s cloudem probíhá pouze v případě potřeby. Například můžete spouštět AI modely na edge zařízeních pro analýzu zralosti ovoce a do cloudu odesílat pouze analytická data, jako je počet zralých kusů ovoce oproti nezralým.

✅ Zamyslete se nad IoT aplikacemi, které jste dosud vytvořili. Které jejich části by mohly být přesunuty na okraj?

### Výhody

Výhody edge computingu jsou:

1. **Rychlost** - edge computing je ideální pro časově citlivá data, protože akce se provádějí ve stejné síti jako zařízení, místo aby se volaly přes internet. To umožňuje vyšší rychlosti, protože interní sítě mohou běžet podstatně rychleji než internetové připojení, přičemž data cestují mnohem kratší vzdálenost.

    > 💁 Přestože optické kabely používané pro internetové připojení umožňují přenos dat rychlostí světla, data mohou potřebovat čas na cestu kolem světa k poskytovatelům cloudových služeb. Například pokud odesíláte data z Evropy do cloudových služeb v USA, trvá to minimálně 28 ms, než data překonají Atlantik v optickém kabelu, a to bez započítání času potřebného k přenosu dat do transatlantického kabelu, konverzi z elektrických na světelné signály a zpět na druhé straně, a následně z optického kabelu k poskytovateli cloudových služeb.

    Edge computing také vyžaduje méně síťového provozu, což snižuje riziko zpomalení dat kvůli přetížení omezené šířky pásma dostupné pro internetové připojení.

1. **Dostupnost v odlehlých oblastech** - edge computing funguje, když máte omezené nebo žádné připojení, nebo je připojení příliš drahé na neustálé používání. Například při práci v oblastech postižených humanitárními katastrofami, kde je infrastruktura omezená, nebo v rozvojových zemích.

1. **Nižší náklady** - shromažďování, ukládání, analýza dat a spouštění akcí na edge zařízení snižuje využití cloudových služeb, což může snížit celkové náklady na vaši IoT aplikaci. V poslední době se objevily zařízení navržená pro edge computing, jako jsou AI akcelerátory, například [Jetson Nano od NVIDIA](https://developer.nvidia.com/embedded/jetson-nano-developer-kit), které mohou spouštět AI úlohy pomocí hardwaru založeného na GPU na zařízeních, která stojí méně než 100 USD.

1. **Soukromí a bezpečnost** - s edge computingem data zůstávají ve vaší síti a nejsou nahrávána do cloudu. To je často preferováno pro citlivé a osobně identifikovatelné informace, zejména proto, že data nemusí být ukládána po jejich analýze, což výrazně snižuje riziko úniku dat. Příklady zahrnují lékařská data a záznamy z bezpečnostních kamer.

1. **Řešení problémů s nebezpečnými zařízeními** - pokud máte zařízení s známými bezpečnostními chybami, která nechcete připojit přímo k vaší síti nebo internetu, můžete je připojit k samostatné síti k bráně IoT Edge zařízení. Toto edge zařízení může mít také připojení k vaší širší síti nebo internetu a spravovat tok dat tam a zpět.

1. **Podpora nekompatibilních zařízení** - pokud máte zařízení, která se nemohou připojit k IoT Hubu, například zařízení, která se mohou připojit pouze pomocí HTTP nebo mají pouze Bluetooth, můžete použít IoT Edge zařízení jako bránu, která přeposílá zprávy do IoT Hubu.

✅ Proveďte výzkum: Jaké další výhody by mohl mít edge computing?

### Nevýhody

Existují nevýhody edge computingu, kdy může být cloud preferovanou volbou:

1. **Škálovatelnost a flexibilita** - cloud computing se může přizpůsobit potřebám sítě a dat v reálném čase přidáním nebo snížením serverů a dalších zdrojů. Přidání více edge počítačů vyžaduje manuální přidání dalších zařízení.

1. **Spolehlivost a odolnost** - cloud computing poskytuje více serverů často na více místech pro redundanci a obnovu po havárii. Pro dosažení stejné úrovně redundance na okraji jsou potřeba velké investice a mnoho konfigurační práce.

1. **Údržba** - poskytovatelé cloudových služeb zajišťují údržbu systému a aktualizace.

✅ Proveďte výzkum: Jaké další nevýhody by mohl mít edge computing?

Nevýhody jsou vlastně opakem výhod používání cloudu - musíte tato zařízení sami budovat a spravovat, místo abyste se spoléhali na odborné znalosti a škálovatelnost poskytovatelů cloudových služeb.

Některá rizika jsou zmírněna samotnou povahou edge computingu. Například pokud máte edge zařízení běžící ve výrobním závodě, které shromažďuje data ze strojů, nemusíte přemýšlet o některých scénářích obnovy po havárii. Pokud dojde k výpadku elektrické energie v závodě, nepotřebujete záložní edge zařízení, protože stroje, které generují data, která edge zařízení zpracovává, budou také bez energie.

Pro IoT systémy budete často chtít kombinaci cloudového a edge computingu, využívající každou službu na základě potřeb systému, jeho zákazníků a jeho správců.

## Azure IoT Edge

![Logo Azure IoT Edge](../../../../../translated_images/cs/azure-iot-edge-logo.c1c076749b5cba2e.webp)

Azure IoT Edge je služba, která vám může pomoci přesunout pracovní zátěže z cloudu na okraj. Nastavíte zařízení jako edge zařízení a z cloudu můžete na toto edge zařízení nasadit kód. To vám umožňuje kombinovat schopnosti cloudu a okraje.

> 🎓 *Pracovní zátěže* je termín pro jakoukoli službu, která provádí nějakou práci, jako jsou AI modely, aplikace nebo serverless funkce.

Například můžete trénovat klasifikátor obrázků v cloudu a poté jej z cloudu nasadit na edge zařízení. Vaše IoT zařízení pak odesílá obrázky na edge zařízení ke klasifikaci, místo aby je odesílalo přes internet. Pokud potřebujete nasadit novou iteraci modelu, můžete ji trénovat v cloudu a pomocí IoT Edge aktualizovat model na edge zařízení na novou iteraci.

> 🎓 Software, který je nasazen na IoT Edge, je známý jako *moduly*. Ve výchozím nastavení IoT Edge spouští moduly, které komunikují s IoT Hubem, jako jsou moduly `edgeAgent` a `edgeHub`. Když nasadíte klasifikátor obrázků, je nasazen jako další modul.

IoT Edge je součástí IoT Hubu, takže můžete spravovat edge zařízení pomocí stejné služby, kterou byste použili ke správě IoT zařízení, se stejnou úrovní zabezpečení.

IoT Edge spouští kód z *kontejnerů* - samostatných aplikací, které běží izolovaně od ostatních aplikací na vašem počítači. Když spustíte kontejner, chová se jako samostatný počítač běžící uvnitř vašeho počítače, se svým vlastním softwarem, službami a aplikacemi. Většinou kontejnery nemohou přistupovat k ničemu na vašem počítači, pokud se nerozhodnete sdílet například složku s kontejnerem. Kontejner pak zpřístupňuje služby prostřednictvím otevřeného portu, ke kterému se můžete připojit nebo jej zpřístupnit vaší síti.

![Webový požadavek přesměrovaný do kontejneru](../../../../../translated_images/cs/container-web-browser.4ee81dd4f0d8838c.webp)

Například můžete mít kontejner s webovou stránkou běžící na portu 80, což je výchozí HTTP port, a můžete jej zpřístupnit z vašeho počítače také na portu 80.

✅ Proveďte výzkum: Přečtěte si o kontejnerech a službách, jako je Docker nebo Moby.

Custom Vision umožňuje stáhnout klasifikátory obrázků a nasadit je jako kontejnery, buď přímo na zařízení, nebo prostřednictvím IoT Edge. Jakmile běží v kontejneru, lze k nim přistupovat pomocí stejného REST API jako u cloudové verze, ale s endpointem směřujícím na edge zařízení, které kontejner provozuje.

## Registrace IoT Edge zařízení

Pro použití IoT Edge zařízení je třeba jej zaregistrovat v IoT Hubu.

### Úkol - registrace IoT Edge zařízení

1. Vytvořte IoT Hub ve skupině prostředků `fruit-quality-detector`. Dejte mu jedinečný název založený na `fruit-quality-detector`.

1. Zaregistrujte IoT Edge zařízení s názvem `fruit-quality-detector-edge` ve vašem IoT Hubu. Příkaz k tomu je podobný tomu, který se používá k registraci zařízení bez edge, kromě toho, že přidáte příznak `--edge-enabled`.

    ```sh
    az iot hub device-identity create --edge-enabled \
                                      --device-id fruit-quality-detector-edge \
                                      --hub-name <hub_name>
    ```

    Nahraďte `<hub_name>` názvem vašeho IoT Hubu.

1. Získejte připojovací řetězec pro vaše zařízení pomocí následujícího příkazu:

    ```sh
    az iot hub device-identity connection-string show --device-id fruit-quality-detector-edge \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    Nahraďte `<hub_name>` názvem vašeho IoT Hubu.

    Zkopírujte připojovací řetězec, který se zobrazí ve výstupu.

## Nastavení IoT Edge zařízení

Jakmile vytvoříte registraci edge zařízení ve vašem IoT Hubu, můžete nastavit edge zařízení.

### Úkol - Instalace a spuštění IoT Edge Runtime

**IoT Edge runtime běží pouze na Linuxových kontejnerech.** Může být spuštěn na Linuxu nebo na Windows pomocí Linuxových virtuálních strojů.

* Pokud používáte Raspberry Pi jako vaše IoT zařízení, pak toto zařízení běží na podporované verzi Linuxu a může hostovat IoT Edge runtime. Postupujte podle [průvodce instalací Azure IoT Edge pro Linux na Microsoft Docs](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) pro instalaci IoT Edge a nastavení připojovacího řetězce.

    > 💁 Pamatujte, Raspberry Pi OS je varianta Debian Linuxu.

* Pokud nepoužíváte Raspberry Pi, ale máte Linuxový počítač, můžete spustit IoT Edge runtime. Postupujte podle [průvodce instalací Azure IoT Edge pro Linux na Microsoft Docs](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) pro instalaci IoT Edge a nastavení připojovacího řetězce.

* Pokud používáte Windows, můžete nainstalovat IoT Edge runtime v Linuxovém virtuálním stroji podle [sekce instalace a spuštění IoT Edge runtime v rychlém startu nasazení prvního IoT Edge modulu na Windows zařízení na Microsoft Docs](https://docs.microsoft.com/azure/iot-edge/quickstart?WT.mc_id=academic-17441-jabenn#install-and-start-the-iot-edge-runtime). Můžete přestat, když dosáhnete sekce *Nasazení modulu*.

* Pokud používáte macOS, můžete vytvořit virtuální stroj (VM) v cloudu, který použijete jako vaše IoT Edge zařízení. Tyto počítače můžete vytvořit v cloudu a přistupovat k nim přes internet. Můžete vytvořit Linuxový VM, který má nainstalovaný IoT Edge. Postupujte podle [průvodce vytvořením virtuálního stroje běžícího IoT Edge](vm-iotedge.md) pro pokyny, jak to udělat.

## Export vašeho modelu

Pro spuštění klasifikátoru na okraji je třeba jej exportovat z Custom Vision. Custom Vision může generovat dva typy modelů - standardní modely a kompaktní modely. Kompaktní modely používají různé techniky ke snížení velikosti modelu, což jej činí dostatečně malým pro stažení a nasazení na IoT zařízení.

Když jste vytvořili klasifikátor obrázků, použili jste doménu *Food*, verzi modelu optimalizovanou pro trénování na obrázcích jídla. V Custom Vision změníte doménu svého projektu, použijete svá tréninková data k trénování nového modelu s novou doménou. Všechny domény podporované Custom Vision jsou dostupné jako standardní i kompaktní.

### Úkol - trénujte svůj model pomocí domény Food (kompaktní)
1. Spusťte portál Custom Vision na [CustomVision.ai](https://customvision.ai) a přihlaste se, pokud jej ještě nemáte otevřený. Poté otevřete svůj projekt `fruit-quality-detector`.

1. Vyberte tlačítko **Settings** (ikona ⚙).

1. V seznamu *Domains* vyberte *Food (compact)*.

1. V části *Export Capabilities* se ujistěte, že je vybrána možnost *Basic platforms (Tensorflow, CoreML, ONNX, ...)*.

1. Na spodní části stránky Nastavení vyberte **Save Changes**.

1. Znovu natrénujte model pomocí tlačítka **Train**, přičemž zvolte *Quick training*.

### Úkol - exportujte svůj model

Jakmile je model natrénován, je třeba jej exportovat jako kontejner.

1. Vyberte kartu **Performance** a najděte svou nejnovější iteraci, která byla natrénována pomocí kompaktní domény.

1. Klikněte na tlačítko **Export** nahoře.

1. Vyberte **DockerFile** a zvolte verzi, která odpovídá vašemu edge zařízení:

    * Pokud provozujete IoT Edge na počítači s Linuxem, Windows nebo na virtuálním stroji, vyberte verzi *Linux*.
    * Pokud provozujete IoT Edge na Raspberry Pi, vyberte verzi *ARM (Raspberry Pi 3)*.

> 🎓 Docker je jedním z nejpopulárnějších nástrojů pro správu kontejnerů a DockerFile je sada instrukcí, jak nastavit kontejner.

1. Klikněte na **Export**, aby Custom Vision vytvořil příslušné soubory, a poté na **Download**, abyste je stáhli jako zip soubor.

1. Uložte soubory do svého počítače a rozbalte složku.

## Příprava kontejneru pro nasazení

![Kontejnery jsou vytvořeny, poté nahrány do registru kontejnerů a nasazeny na edge zařízení pomocí IoT Edge](../../../../../translated_images/cs/container-edge-flow.c246050dd60ceefd.webp)

Jakmile stáhnete svůj model, je třeba jej sestavit do kontejneru a poté nahrát do registru kontejnerů – online úložiště, kde můžete kontejnery uchovávat. IoT Edge poté může stáhnout kontejner z registru a nasadit jej na vaše zařízení.

![Logo Azure Container Registry](../../../../../translated_images/cs/azure-container-registry-logo.09494206991d4b29.webp)

Registr kontejnerů, který budete používat v této lekci, je Azure Container Registry. Tato služba není zdarma, takže abyste ušetřili peníze, ujistěte se, že [vyčistíte svůj projekt](../../../clean-up.md), jakmile skončíte.

> 💁 Náklady na používání Azure Container Registry si můžete prohlédnout na [stránce s cenami Azure Container Registry](https://azure.microsoft.com/pricing/details/container-registry/?WT.mc_id=academic-17441-jabenn).

### Úkol - instalace Dockeru

Pro sestavení a nasazení klasifikátoru možná budete muset nainstalovat [Docker](https://www.docker.com/).

Toto budete potřebovat pouze v případě, že plánujete sestavit svůj kontejner na jiném zařízení, než na kterém jste nainstalovali IoT Edge – součástí instalace IoT Edge je i instalace Dockeru.

1. Pokud sestavujete docker kontejner na jiném zařízení než na vašem IoT Edge zařízení, postupujte podle pokynů k instalaci Dockeru na [stránce instalace Dockeru](https://www.docker.com/products/docker-desktop) a nainstalujte Docker Desktop nebo Docker engine. Po instalaci se ujistěte, že Docker běží.

### Úkol - vytvoření zdroje registru kontejnerů

1. Spusťte následující příkaz z vašeho terminálu nebo příkazového řádku pro vytvoření zdroje Azure Container Registry:

    ```sh
    az acr create --resource-group fruit-quality-detector \
                  --sku Basic \
                  --name <Container registry name>
    ```

    Nahraďte `<Container registry name>` jedinečným názvem pro váš registr kontejnerů, použijte pouze písmena a čísla. Základem může být `fruitqualitydetector`. Tento název se stane součástí URL pro přístup k registru kontejnerů, takže musí být globálně jedinečný.

1. Přihlaste se do Azure Container Registry pomocí následujícího příkazu:

    ```sh
    az acr login --name <Container registry name>
    ```

    Nahraďte `<Container registry name>` názvem, který jste použili pro váš registr kontejnerů.

1. Nastavte registr kontejnerů do režimu správce, abyste mohli vygenerovat heslo pomocí následujícího příkazu:

    ```sh
    az acr update --admin-enabled true \
                 --name <Container registry name>
    ```

    Nahraďte `<Container registry name>` názvem, který jste použili pro váš registr kontejnerů.

1. Vygenerujte hesla pro váš registr kontejnerů pomocí následujícího příkazu:

    ```sh
     az acr credential renew --password-name password \
                             --output table \
                             --name <Container registry name>
    ```

    Nahraďte `<Container registry name>` názvem, který jste použili pro váš registr kontejnerů.

    Zkopírujte hodnotu `PASSWORD`, protože ji budete později potřebovat.

### Úkol - sestavení vašeho kontejneru

To, co jste stáhli z Custom Vision, byl DockerFile obsahující instrukce, jak by měl být kontejner sestaven, spolu s aplikačním kódem, který bude spuštěn uvnitř kontejneru pro hostování vašeho modelu Custom Vision, spolu s REST API pro jeho volání. Pomocí Dockeru můžete sestavit označený kontejner z DockerFile a poté jej nahrát do vašeho registru kontejnerů.

> 🎓 Kontejnery jsou označeny tagem, který definuje jejich název a verzi. Když potřebujete aktualizovat kontejner, můžete jej sestavit se stejným tagem, ale s novější verzí.

1. Otevřete svůj terminál nebo příkazový řádek a přejděte do rozbalené složky modelu, kterou jste stáhli z Custom Vision.

1. Spusťte následující příkaz pro sestavení a označení obrazu:

    ```sh
    docker build --platform <platform> -t <Container registry name>.azurecr.io/classifier:v1 .
    ```

    Nahraďte `<platform>` platformou, na které bude tento kontejner spuštěn. Pokud provozujete IoT Edge na Raspberry Pi, nastavte to na `linux/armhf`, jinak nastavte na `linux/amd64`.

    > 💁 Pokud tento příkaz spouštíte ze zařízení, na kterém provozujete IoT Edge, například z Raspberry Pi, můžete vynechat část `--platform <platform>`, protože výchozí hodnota je aktuální platforma.

    Nahraďte `<Container registry name>` názvem, který jste použili pro váš registr kontejnerů.

    > 💁 Pokud používáte Linux nebo Raspberry Pi OS, možná budete muset použít `sudo` pro spuštění tohoto příkazu.

    Docker sestaví obraz, nakonfiguruje veškerý potřebný software. Obraz bude poté označen jako `classifier:v1`.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux docker build --platform linux/amd64 -t  fruitqualitydetectorjimb.azurecr.io/classifier:v1 .
    [+] Building 102.4s (11/11) FINISHED
     => [internal] load build definition from Dockerfile
     => => transferring dockerfile: 131B
     => [internal] load .dockerignore
     => => transferring context: 2B
     => [internal] load metadata for docker.io/library/python:3.7-slim
     => [internal] load build context
     => => transferring context: 905B
     => [1/6] FROM docker.io/library/python:3.7-slim@sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6
     => => resolve docker.io/library/python:3.7-slim@sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6
     => => sha256:b4d181a07f8025e00e0cb28f1cc14613da2ce26450b80c54aea537fa93cf3bda 27.15MB / 27.15MB
     => => sha256:de8ecf497b753094723ccf9cea8a46076e7cb845f333df99a6f4f397c93c6ea9 2.77MB / 2.77MB
     => => sha256:707b80804672b7c5d8f21e37c8396f319151e1298d976186b4f3b76ead9f10c8 10.06MB / 10.06MB
     => => sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6 1.86kB / 1.86kB
     => => sha256:44073386687709c437586676b572ff45128ff1f1570153c2f727140d4a9accad 1.37kB / 1.37kB
     => => sha256:3d94f0f2ca798607808b771a7766f47ae62a26f820e871dd488baeccc69838d1 8.31kB / 8.31kB
     => => sha256:283715715396fd56d0e90355125fd4ec57b4f0773f306fcd5fa353b998beeb41 233B / 233B
     => => sha256:8353afd48f6b84c3603ea49d204bdcf2a1daada15f5d6cad9cc916e186610a9f 2.64MB / 2.64MB
     => => extracting sha256:b4d181a07f8025e00e0cb28f1cc14613da2ce26450b80c54aea537fa93cf3bda
     => => extracting sha256:de8ecf497b753094723ccf9cea8a46076e7cb845f333df99a6f4f397c93c6ea9
     => => extracting sha256:707b80804672b7c5d8f21e37c8396f319151e1298d976186b4f3b76ead9f10c8
     => => extracting sha256:283715715396fd56d0e90355125fd4ec57b4f0773f306fcd5fa353b998beeb41
     => => extracting sha256:8353afd48f6b84c3603ea49d204bdcf2a1daada15f5d6cad9cc916e186610a9f
     => [2/6] RUN pip install -U pip
     => [3/6] RUN pip install --no-cache-dir numpy~=1.17.5 tensorflow~=2.0.2 flask~=1.1.2 pillow~=7.2.0
     => [4/6] RUN pip install --no-cache-dir mscviplib==2.200731.16
     => [5/6] COPY app /app
     => [6/6] WORKDIR /app
     => exporting to image
     => => exporting layers
     => => writing image sha256:1846b6f134431f78507ba7c079358ed66d944c0e185ab53428276bd822400386
     => => naming to fruitqualitydetectorjimb.azurecr.io/classifier:v1
    ```

### Úkol - nahrání vašeho kontejneru do registru kontejnerů

1. Použijte následující příkaz pro nahrání vašeho kontejneru do registru kontejnerů:

    ```sh
    docker push <Container registry name>.azurecr.io/classifier:v1
    ```

    Nahraďte `<Container registry name>` názvem, který jste použili pro váš registr kontejnerů.

    > 💁 Pokud používáte Linux, možná budete muset použít `sudo` pro spuštění tohoto příkazu.

    Kontejner bude nahrán do registru kontejnerů.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux docker push fruitqualitydetectorjimb.azurecr.io/classifier:v1
    The push refers to repository [fruitqualitydetectorjimb.azurecr.io/classifier]
    5f70bf18a086: Pushed 
    8a1ba9294a22: Pushed 
    56cf27184a76: Pushed 
    b32154f3f5dd: Pushed 
    36103e9a3104: Pushed 
    e2abb3cacca0: Pushed 
    4213fd357bbe: Pushed 
    7ea163ba4dce: Pushed 
    537313a13d90: Pushed 
    764055ebc9a7: Pushed 
    v1: digest: sha256:ea7894652e610de83a5a9e429618e763b8904284253f4fa0c9f65f0df3a5ded8 size: 2423
    ```

1. Pro ověření nahrání můžete vypsat kontejnery ve vašem registru pomocí následujícího příkazu:

    ```sh
    az acr repository list --output table \
                           --name <Container registry name> 
    ```

    Nahraďte `<Container registry name>` názvem, který jste použili pro váš registr kontejnerů.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux az acr repository list --name fruitqualitydetectorjimb --output table
    Result
    ----------
    classifier
    ```

    Ve výstupu uvidíte váš klasifikátor.

## Nasazení vašeho kontejneru

Váš kontejner nyní může být nasazen na vaše IoT Edge zařízení. Pro nasazení je třeba definovat nasazovací manifest – JSON dokument, který uvádí moduly, které budou nasazeny na edge zařízení.

### Úkol - vytvoření nasazovacího manifestu

1. Vytvořte nový soubor s názvem `deployment.json` někde na vašem počítači.

1. Přidejte do tohoto souboru následující:

    ```json
    {
        "content": {
            "modulesContent": {
                "$edgeAgent": {
                    "properties.desired": {
                        "schemaVersion": "1.1",
                        "runtime": {
                            "type": "docker",
                            "settings": {
                                "minDockerVersion": "v1.25",
                                "loggingOptions": "",
                                "registryCredentials": {
                                    "ClassifierRegistry": {
                                        "username": "<Container registry name>",
                                        "password": "<Container registry password>",
                                        "address": "<Container registry name>.azurecr.io"
                                      }
                                }
                            }
                        },
                        "systemModules": {
                            "edgeAgent": {
                                "type": "docker",
                                "settings": {
                                    "image": "mcr.microsoft.com/azureiotedge-agent:1.1",
                                    "createOptions": "{}"
                                }
                            },
                            "edgeHub": {
                                "type": "docker",
                                "status": "running",
                                "restartPolicy": "always",
                                "settings": {
                                    "image": "mcr.microsoft.com/azureiotedge-hub:1.1",
                                    "createOptions": "{\"HostConfig\":{\"PortBindings\":{\"5671/tcp\":[{\"HostPort\":\"5671\"}],\"8883/tcp\":[{\"HostPort\":\"8883\"}],\"443/tcp\":[{\"HostPort\":\"443\"}]}}}"
                                }
                            }
                        },
                        "modules": {
                            "ImageClassifier": {
                                "version": "1.0",
                                "type": "docker",
                                "status": "running",
                                "restartPolicy": "always",
                                "settings": {
                                    "image": "<Container registry name>.azurecr.io/classifier:v1",
                                    "createOptions": "{\"ExposedPorts\": {\"80/tcp\": {}},\"HostConfig\": {\"PortBindings\": {\"80/tcp\": [{\"HostPort\": \"80\"}]}}}"
                                }
                            }
                        }
                    }
                },
                "$edgeHub": {
                    "properties.desired": {
                        "schemaVersion": "1.1",
                        "routes": {
                            "upstream": "FROM /messages/* INTO $upstream"
                        },
                        "storeAndForwardConfiguration": {
                            "timeToLiveSecs": 7200
                        }
                    }
                }
            }
        }
    }
    ```

    > 💁 Tento soubor najdete ve složce [code-deployment/deployment](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-deployment/deployment).

    Nahraďte tři instance `<Container registry name>` názvem, který jste použili pro váš registr kontejnerů. Jeden je v sekci modulu `ImageClassifier`, další dva jsou v sekci `registryCredentials`.

    Nahraďte `<Container registry password>` v sekci `registryCredentials` vaším heslem k registru kontejnerů.

1. Ze složky obsahující váš nasazovací manifest spusťte následující příkaz:

    ```sh
    az iot edge set-modules --device-id fruit-quality-detector-edge \
                            --content deployment.json \
                            --hub-name <hub_name>
    ```

    Nahraďte `<hub_name>` názvem vašeho IoT Hubu.

    Modul klasifikátoru obrázků bude nasazen na vaše edge zařízení.

### Úkol - ověření, že klasifikátor běží

1. Připojte se k IoT Edge zařízení:

    * Pokud používáte Raspberry Pi pro provoz IoT Edge, připojte se pomocí ssh buď z vašeho terminálu, nebo prostřednictvím vzdálené SSH relace ve VS Code.
    * Pokud provozujete IoT Edge v Linuxovém kontejneru na Windows, postupujte podle kroků v [průvodci ověřením úspěšné konfigurace](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge-on-windows?WT.mc_id=academic-17441-jabenn&view=iotedge-2018-06&tabs=powershell#verify-successful-configuration) pro připojení k IoT Edge zařízení.
    * Pokud provozujete IoT Edge na virtuálním stroji, můžete se připojit pomocí SSH na stroj pomocí `adminUsername` a `password`, které jste nastavili při vytváření VM, a pomocí IP adresy nebo DNS názvu:

        ```sh
        ssh <adminUsername>@<IP address>
        ```

        Nebo:

        ```sh
        ssh <adminUsername>@<DNS Name>
        ```

        Zadejte své heslo, když budete vyzváni.

1. Jakmile jste připojeni, spusťte následující příkaz pro získání seznamu modulů IoT Edge:

    ```sh
    iotedge list
    ```

    > 💁 Možná budete muset tento příkaz spustit s `sudo`.

    Uvidíte běžící moduly:

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge list
    NAME             STATUS           DESCRIPTION      CONFIG
    ImageClassifier  running          Up 42 minutes    fruitqualitydetectorjimb.azurecr.io/classifier:v1
    edgeAgent        running          Up 42 minutes    mcr.microsoft.com/azureiotedge-agent:1.1
    edgeHub          running          Up 42 minutes    mcr.microsoft.com/azureiotedge-hub:1.1
    ```

1. Zkontrolujte logy modulu Image classifier pomocí následujícího příkazu:

    ```sh
    iotedge logs ImageClassifier
    ```

    > 💁 Možná budete muset tento příkaz spustit s `sudo`.

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge logs ImageClassifier
    2021-07-05 20:30:15.387144: I tensorflow/core/platform/cpu_feature_guard.cc:142] Your CPU supports instructions that this TensorFlow binary was not compiled to use: AVX2 FMA
    2021-07-05 20:30:15.392185: I tensorflow/core/platform/profile_utils/cpu_utils.cc:94] CPU Frequency: 2394450000 Hz
    2021-07-05 20:30:15.392712: I tensorflow/compiler/xla/service/service.cc:168] XLA service 0x55ed9ac83470 executing computations on platform Host. Devices:
    2021-07-05 20:30:15.392806: I tensorflow/compiler/xla/service/service.cc:175]   StreamExecutor device (0): Host, Default Version
    Loading model...Success!
    Loading labels...2 found. Success!
     * Serving Flask app "app" (lazy loading)
     * Environment: production
       WARNING: This is a development server. Do not use it in a production deployment.
       Use a production WSGI server instead.
     * Debug mode: off
     * Running on http://0.0.0.0:80/ (Press CTRL+C to quit)
    ```

### Úkol - testování klasifikátoru obrázků

1. Můžete použít CURL pro testování klasifikátoru obrázků pomocí IP adresy nebo názvu hostitele počítače, na kterém běží IoT Edge agent. Najděte IP adresu:

    * Pokud jste na stejném zařízení, na kterém běží IoT Edge, můžete použít `localhost` jako název hostitele.
    * Pokud používáte VM, můžete použít buď IP adresu, nebo DNS název VM.
    * Jinak můžete získat IP adresu zařízení, na kterém běží IoT Edge:
      * Na Windows 10 postupujte podle [průvodce nalezením IP adresy](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn).
      * Na macOS postupujte podle [průvodce nalezením IP adresy na Macu](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac).
      * Na Linuxu postupujte podle sekce o nalezení soukromé IP adresy v [průvodci nalezením IP adresy v Linuxu](https://opensource.com/article/18/5/how-find-ip-address-linux).

1. Kontejner můžete otestovat s lokálním souborem spuštěním následujícího příkazu curl:

    ```sh
    curl --location \
         --request POST 'http://<IP address or name>/image' \
         --header 'Content-Type: image/png' \
         --data-binary '@<file_Name>' 
    ```

    Nahraďte `<IP address or name>` IP adresou nebo názvem hostitele počítače, na kterém běží IoT Edge. Nahraďte `<file_Name>` názvem souboru, který chcete otestovat.

    Ve výstupu uvidíte výsledky predikce:

    ```output
    {
        "created": "2021-07-05T21:44:39.573181",
        "id": "",
        "iteration": "",
        "predictions": [
            {
                "boundingBox": null,
                "probability": 0.9995615482330322,
                "tagId": "",
                "tagName": "ripe"
            },
            {
                "boundingBox": null,
                "probability": 0.0004384400090202689,
                "tagId": "",
                "tagName": "unripe"
            }
        ],
        "project": ""
    }
    ```

    > 💁 Zde není třeba poskytovat klíč predikce, protože se nejedná o použití Azure zdroje. Místo toho by byla bezpečnost nakonfigurována na interní síti na základě interních bezpečnostních potřeb, spíše než spoléhání na veřejný endpoint a API klíč.

## Použití vašeho IoT Edge zařízení

Nyní, když byl váš klasifikátor obrázků nasazen na IoT Edge zařízení, můžete jej používat ze svého IoT zařízení.

### Úkol - použití vašeho IoT Edge zařízení

Projděte si relevantní průvodce pro klasifikaci obrázků pomocí IoT Edge klasifikátoru:

* [Arduino - Wio Terminal](wio-terminal.md)
* [Jednodeskový počítač - Raspberry Pi/virtuální IoT zařízení](single-board-computer.md)

### Přetrénování modelu

Jednou z nevýhod provozování klasifikátorů obrázků na IoT Edge je, že nejsou propojeny s vaším projektem Custom Vision. Pokud se podíváte na kartu **Predictions** v Custom Vision, neuvidíte obrázky, které byly klasifikovány pomocí klasifikátoru na Edge.

Toto je očekávané chování – obrázky nejsou odesílány do cloudu pro klasifikaci, takže nebudou dostupné v cloudu. Jednou z výhod používání IoT Edge je ochrana soukromí, která zajišťuje, že obrázky neopustí vaši síť, další výhodou je možnost pracovat offline, takže není nutné nahrávat obrázky, když zařízení nemá připojení k internetu. Nevýhodou je zlepšování vašeho modelu – museli byste implementovat jiný způsob ukládání obrázků, které lze ručně překlasifikovat pro zlepšení a přetrénování klasifikátoru obrázků.

✅ Přemýšlejte o způsobech, jak nahrávat obrázky pro přetrénování klasifikátoru.

---

## 🚀 Výzva

Provozování AI modelů na edge zařízeních může být rychlejší než v cloudu – síťový přenos je kratší. Mohou být ale také pomalejší, protože hardware, na kterém model běží, nemusí být tak výkonný jako cloud.

Proveďte měření a porovnejte, zda je volání vašeho edge zařízení rychlejší nebo pomalejší než volání do cloudu? Přemýšlejte o důvodech, které vysvětlují rozdíl, nebo jeho absenci. Prozkoumejte způsoby, jak spouštět AI modely rychleji na edge pomocí specializovaného hardwaru.

## Kvíz po přednášce

[Kvíz po přednášce](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/34)

## Recenze a samostudium

* Přečtěte si více o kontejnerech na [stránce o virtualizaci na úrovni OS na Wikipedii](https://wikipedia.org/wiki/OS-level_virtualization).
* Přečtěte si více o edge computingu, se zaměřením na to, jak může 5G pomoci rozšířit edge computing, v [článku na NetworkWorld: Co je edge computing a proč na něm záleží?](https://www.networkworld.com/article/3224893/what-is-edge-computing-and-how-its-changing-the-network.html)
* Zjistěte více o provozování AI služeb na IoT Edge sledováním [epizody Learn Live na Microsoft Channel9: Naučte se používat Azure IoT Edge na předem připravené AI službě na Edge pro detekci jazyka](https://channel9.msdn.com/Shows/Learn-Live/Sharpen-Your-AI-Edge-Skills-Episode-4-Learn-How-to-Use-Azure-IoT-Edge-on-a-Pre-Built-AI-Service-on-t?WT.mc_id=academic-17441-jabenn)

## Úkol

[Provozujte další služby na edge](assignment.md)

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Neodpovídáme za žádné nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.