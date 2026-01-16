<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2625af24587465c5547ae33d6cc000a5",
  "translation_date": "2025-08-27T20:33:41+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/README.md",
  "language_code": "sv"
}
-->
# Kör din fruktdetektor på kanten

![En sketchnote-översikt av denna lektion](../../../../../translated_images/sv/lesson-17.bc333c3c35ba8e42cce666cfffa82b915f787f455bd94e006aea2b6f2722421a.jpg)

> Sketchnote av [Nitya Narasimhan](https://github.com/nitya). Klicka på bilden för en större version.

Den här videon ger en översikt över hur man kör bildklassificerare på IoT-enheter, ämnet som behandlas i denna lektion.

[![Custom Vision AI på Azure IoT Edge](https://img.youtube.com/vi/_K5fqGLO8us/0.jpg)](https://www.youtube.com/watch?v=_K5fqGLO8us)

## Quiz före föreläsningen

[Quiz före föreläsningen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/33)

## Introduktion

I den förra lektionen använde du din bildklassificerare för att klassificera mogen och omogen frukt, genom att skicka en bild som tagits av kameran på din IoT-enhet via internet till en molntjänst. Dessa samtal tar tid, kostar pengar och kan, beroende på vilken typ av bilddata du använder, ha integritetsimplikationer.

I denna lektion kommer du att lära dig hur man kör maskininlärningsmodeller (ML) på kanten - på IoT-enheter som körs på ditt eget nätverk istället för i molnet. Du kommer att lära dig fördelarna och nackdelarna med edge computing jämfört med molnberäkning, hur man distribuerar din AI-modell till kanten och hur man får åtkomst till den från din IoT-enhet.

I denna lektion kommer vi att behandla:

* [Edge computing](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Azure IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Registrera en IoT Edge-enhet](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Ställ in en IoT Edge-enhet](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Exportera din modell](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Förbered din container för distribution](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Distribuera din container](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Använd din IoT Edge-enhet](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)

## Edge computing

Edge computing innebär att ha datorer som bearbetar IoT-data så nära som möjligt där data genereras. Istället för att ha denna bearbetning i molnet flyttas den till kanten av molnet - ditt interna nätverk.

![En arkitekturdiagram som visar internettjänster i molnet och IoT-enheter på ett lokalt nätverk](../../../../../translated_images/sv/cloud-without-edge.b4da641f6022c95ed6b91fde8b5323abd2f94e0d52073ad54172ae8f5dac90e9.png)

I de tidigare lektionerna har du haft enheter som samlar in data och skickar data till molnet för att analyseras, och kör serverlösa funktioner eller AI-modeller i molnet.

![En arkitekturdiagram som visar IoT-enheter på ett lokalt nätverk som ansluter till edge-enheter, och dessa edge-enheter ansluter till molnet](../../../../../translated_images/sv/cloud-with-edge.1e26462c62c126fe150bd15a5714ddf0be599f09bacbad08b85be02b76ea1ae1.png)

Edge computing innebär att flytta vissa av molntjänsterna från molnet till datorer som körs på samma nätverk som IoT-enheterna, och endast kommunicera med molnet vid behov. Till exempel kan du köra AI-modeller på edge-enheter för att analysera fruktens mognad och endast skicka analysdata tillbaka till molnet, såsom antalet mogna frukter jämfört med omogna.

✅ Fundera på de IoT-applikationer du har byggt hittills. Vilka delar av dem skulle kunna flyttas till kanten?

### Fördelar

Fördelarna med edge computing är:

1. **Hastighet** - edge computing är idealiskt för tidskänslig data eftersom åtgärder utförs på samma nätverk som enheten, istället för att göra samtal över internet. Detta möjliggör högre hastigheter eftersom interna nätverk kan köras betydligt snabbare än internetanslutningar, med data som reser mycket kortare avstånd.

    > 💁 Trots att optiska kablar används för internetanslutningar som tillåter data att resa med ljusets hastighet, kan det ta tid för data att resa runt världen till molnleverantörer. Till exempel, om du skickar data från Europa till molntjänster i USA tar det minst 28 ms för data att korsa Atlanten i en optisk kabel, och det är utan att räkna med tiden det tar att få data till den transatlantiska kabeln, konvertera från elektriska till ljussignaler och tillbaka igen på andra sidan, och sedan från den optiska kabeln till molnleverantören.

    Edge computing kräver också mindre nätverkstrafik, vilket minskar risken för att din data saktar ner på grund av trängsel på den begränsade bandbredden som finns tillgänglig för en internetanslutning.

1. **Fjärråtkomst** - edge computing fungerar när du har begränsad eller ingen anslutning, eller när anslutning är för dyr för att använda kontinuerligt. Till exempel vid arbete i humanitära katastrofområden där infrastrukturen är begränsad, eller i utvecklingsländer.

1. **Lägre kostnader** - att samla in, lagra, analysera och utlösa åtgärder på edge-enheter minskar användningen av molntjänster, vilket kan minska de totala kostnaderna för din IoT-applikation. Det har nyligen skett en ökning av enheter som är designade för edge computing, såsom AI-acceleratorer som [Jetson Nano från NVIDIA](https://developer.nvidia.com/embedded/jetson-nano-developer-kit), som kan köra AI-arbetsbelastningar med GPU-baserad hårdvara på enheter som kostar mindre än 100 USD.

1. **Integritet och säkerhet** - med edge computing stannar data på ditt nätverk och laddas inte upp till molnet. Detta föredras ofta för känslig och personligt identifierbar information, särskilt eftersom data inte behöver lagras efter att den har analyserats, vilket kraftigt minskar risken för dataläckor. Exempel inkluderar medicinsk data och säkerhetskamerabilder.

1. **Hantering av osäkra enheter** - om du har enheter med kända säkerhetsbrister som du inte vill ansluta direkt till ditt nätverk eller internet, kan du ansluta dem till ett separat nätverk via en gateway IoT Edge-enhet. Denna edge-enhet kan sedan också ha en anslutning till ditt bredare nätverk eller internet och hantera dataflöden fram och tillbaka.

1. **Stöd för inkompatibla enheter** - om du har enheter som inte kan ansluta till IoT Hub, till exempel enheter som endast kan ansluta via HTTP-anslutningar eller enheter som endast har Bluetooth för anslutning, kan du använda en IoT Edge-enhet som en gateway-enhet som vidarebefordrar meddelanden till IoT Hub.

✅ Gör lite research: Vilka andra fördelar kan det finnas med edge computing?

### Nackdelar

Det finns nackdelar med edge computing, där molnet kan vara ett föredraget alternativ:

1. **Skalbarhet och flexibilitet** - molnberäkning kan anpassa sig till nätverks- och databehov i realtid genom att lägga till eller minska servrar och andra resurser. För att lägga till fler edge-datorer krävs att fler enheter läggs till manuellt.

1. **Tillförlitlighet och motståndskraft** - molnberäkning tillhandahåller flera servrar, ofta på flera platser, för redundans och katastrofåterställning. För att ha samma nivå av redundans på kanten krävs stora investeringar och mycket konfigurationsarbete.

1. **Underhåll** - molntjänstleverantörer tillhandahåller systemunderhåll och uppdateringar.

✅ Gör lite research: Vilka andra nackdelar kan det finnas med edge computing?

Nackdelarna är egentligen motsatsen till fördelarna med att använda molnet - du måste bygga och hantera dessa enheter själv, istället för att förlita dig på expertisen och skalan hos molnleverantörer.

Vissa av riskerna mildras av själva naturen av edge computing. Till exempel, om du har en edge-enhet som körs i en fabrik och samlar in data från maskiner, behöver du inte tänka på vissa katastrofåterställningsscenarier. Om strömmen till fabriken går ut behöver du inte en reserv-edge-enhet eftersom maskinerna som genererar data som edge-enheten bearbetar också kommer att vara utan ström.

För IoT-system vill du ofta ha en blandning av moln- och edge computing, och utnyttja varje tjänst baserat på systemets behov, dess kunder och dess underhållare.

## Azure IoT Edge

![Azure IoT Edge-logotypen](../../../../../translated_images/sv/azure-iot-edge-logo.c1c076749b5cba2e8755262fadc2f19ca1146b948d76990b1229199ac2292d79.png)

Azure IoT Edge är en tjänst som kan hjälpa dig att flytta arbetsbelastningar från molnet till kanten. Du ställer in en enhet som en edge-enhet och från molnet kan du distribuera kod till den edge-enheten. Detta gör att du kan blanda molnets och kantens kapabiliteter.

> 🎓 *Arbetsbelastningar* är en term för alla tjänster som utför någon form av arbete, såsom AI-modeller, applikationer eller serverlösa funktioner.

Till exempel kan du träna en bildklassificerare i molnet och sedan från molnet distribuera den till en edge-enhet. Din IoT-enhet skickar sedan bilder till edge-enheten för klassificering, istället för att skicka bilderna över internet. Om du behöver distribuera en ny iteration av modellen kan du träna den i molnet och använda IoT Edge för att uppdatera modellen på edge-enheten till din nya iteration.

> 🎓 Programvara som distribueras till IoT Edge kallas *moduler*. Som standard kör IoT Edge moduler som kommunicerar med IoT Hub, såsom `edgeAgent` och `edgeHub`-modulerna. När du distribuerar en bildklassificerare distribueras detta som en extra modul.

IoT Edge är inbyggt i IoT Hub, så du kan hantera edge-enheter med samma tjänst som du skulle använda för att hantera IoT-enheter, med samma säkerhetsnivå.

IoT Edge kör kod från *containers* - självständiga applikationer som körs isolerat från resten av applikationerna på din dator. När du kör en container fungerar den som en separat dator som körs inuti din dator, med sin egen programvara, tjänster och applikationer. Oftast kan containers inte komma åt något på din dator om du inte väljer att dela saker som en mapp med containern. Containern exponerar sedan tjänster via en öppen port som du kan ansluta till eller exponera för ditt nätverk.

![En webbförfrågan omdirigerad till en container](../../../../../translated_images/sv/container-web-browser.4ee81dd4f0d8838ce622b2a0d600b6a4322b5d4fe43159facd87b7b34f84d66a.png)

Till exempel kan du ha en container med en webbplats som körs på port 80, standardporten för HTTP, och du kan sedan exponera den från din dator också på port 80.

✅ Gör lite research: Läs om containers och tjänster som Docker eller Moby.

Du kan använda Custom Vision för att ladda ner bildklassificerare och distribuera dem som containers, antingen direkt till en enhet eller distribuerade via IoT Edge. När de körs i en container kan de nås med samma REST API som molnversionen, men med slutpunkten pekande på edge-enheten som kör containern.

## Registrera en IoT Edge-enhet

För att använda en IoT Edge-enhet måste den registreras i IoT Hub.

### Uppgift - registrera en IoT Edge-enhet

1. Skapa en IoT Hub i resursgruppen `fruit-quality-detector`. Ge den ett unikt namn baserat på `fruit-quality-detector`.

1. Registrera en IoT Edge-enhet som heter `fruit-quality-detector-edge` i din IoT Hub. Kommandot för att göra detta är liknande det som används för att registrera en icke-edge-enhet, förutom att du skickar flaggan `--edge-enabled`.

    ```sh
    az iot hub device-identity create --edge-enabled \
                                      --device-id fruit-quality-detector-edge \
                                      --hub-name <hub_name>
    ```

    Ersätt `<hub_name>` med namnet på din IoT Hub.

1. Hämta anslutningssträngen för din enhet med följande kommando:

    ```sh
    az iot hub device-identity connection-string show --device-id fruit-quality-detector-edge \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    Ersätt `<hub_name>` med namnet på din IoT Hub.

    Ta en kopia av anslutningssträngen som visas i utdata.

## Ställ in en IoT Edge-enhet

När du har skapat edge-enhetsregistreringen i din IoT Hub kan du ställa in edge-enheten.

### Uppgift - Installera och starta IoT Edge Runtime

**IoT Edge Runtime kör endast Linux-containers.** Det kan köras på Linux eller på Windows med Linux Virtual Machines.

* Om du använder en Raspberry Pi som din IoT-enhet, kör den en stödd version av Linux och kan vara värd för IoT Edge Runtime. Följ [installationsguiden för Azure IoT Edge för Linux på Microsoft Docs](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) för att installera IoT Edge och ställa in anslutningssträngen.

    > 💁 Kom ihåg att Raspberry Pi OS är en variant av Debian Linux.

* Om du inte använder en Raspberry Pi, men har en Linux-dator, kan du köra IoT Edge Runtime. Följ [installationsguiden för Azure IoT Edge för Linux på Microsoft Docs](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) för att installera IoT Edge och ställa in anslutningssträngen.

* Om du använder Windows kan du installera IoT Edge Runtime i en Linux Virtual Machine genom att följa [installations- och startsektionen för IoT Edge Runtime i snabbstarten för att distribuera din första IoT Edge-modul till en Windows-enhet på Microsoft Docs](https://docs.microsoft.com/azure/iot-edge/quickstart?WT.mc_id=academic-17441-jabenn#install-and-start-the-iot-edge-runtime). Du kan sluta när du når avsnittet *Distribuera en modul*.

* Om du använder macOS kan du skapa en virtuell maskin (VM) i molnet för att använda som din IoT Edge-enhet. Dessa är datorer du kan skapa i molnet och komma åt via internet. Du kan skapa en Linux-VM som har IoT Edge installerat. Följ [guiden för att skapa en virtuell maskin som kör IoT Edge](vm-iotedge.md) för instruktioner om hur du gör detta.

## Exportera din modell

För att köra klassificeraren på kanten måste den exporteras från Custom Vision. Custom Vision kan generera två typer av modeller - standardmodeller och kompakta modeller. Kompakta modeller använder olika tekniker för att minska modellens storlek, vilket gör den tillräckligt liten för att laddas ner och distribueras på IoT-enheter.

När du skapade bildklassificeraren använde du *Food*-domänen, en version av modellen som är optimerad för träning på matbilder. I Custom Vision ändrar du domänen för ditt projekt och använder din träningsdata för att träna en ny modell med den nya domänen. Alla domäner som stöds av Custom Vision är tillgängliga som standard och kompakta.

### Uppgift - träna din modell med Food (compact)-domänen
1. Öppna Custom Vision-portalen på [CustomVision.ai](https://customvision.ai) och logga in om du inte redan har den öppen. Öppna sedan ditt projekt `fruit-quality-detector`.

1. Välj knappen **Settings** (⚙-ikonen).

1. I listan *Domains*, välj *Food (compact)*.

1. Under *Export Capabilities*, se till att *Basic platforms (Tensorflow, CoreML, ONNX, ...)* är vald.

1. Längst ner på inställningssidan, välj **Save Changes**.

1. Träna om modellen med knappen **Train**, och välj *Quick training*.

### Uppgift - exportera din modell

När modellen har tränats behöver den exporteras som en container.

1. Välj fliken **Performance** och hitta din senaste iteration som tränades med det kompakta domänet.

1. Välj knappen **Export** högst upp.

1. Välj **DockerFile** och välj en version som matchar din edge-enhet:

    * Om du kör IoT Edge på en Linux-dator, Windows-dator eller en virtuell maskin, välj *Linux*-versionen.
    * Om du kör IoT Edge på en Raspberry Pi, välj *ARM (Raspberry Pi 3)*-versionen.

> 🎓 Docker är ett av de mest populära verktygen för att hantera containrar, och en DockerFile är en uppsättning instruktioner för hur containern ska konfigureras.

1. Välj **Export** för att låta Custom Vision skapa relevanta filer, och sedan **Download** för att ladda ner dem som en zip-fil.

1. Spara filerna på din dator och packa upp mappen.

## Förbered din container för distribution

![Containrar byggs och skickas till ett containerregister, och distribueras sedan från registret till en edge-enhet med IoT Edge](../../../../../translated_images/sv/container-edge-flow.c246050dd60ceefdb6ace026a4ce5c6aa4112bb5898ae23fbb2ab4be29ae3e1b.png)

När du har laddat ner din modell behöver den byggas till en container och skickas till ett containerregister - en onlineplats där du kan lagra containrar. IoT Edge kan sedan ladda ner containern från registret och skicka den till din enhet.

![Azure Container Registry-logotypen](../../../../../translated_images/sv/azure-container-registry-logo.09494206991d4b295025ebff7d4e2900325e527a59184ffbc8464b6ab59654be.png)

Containerregistret du kommer att använda för denna lektion är Azure Container Registry. Detta är inte en gratis tjänst, så för att spara pengar, se till att [städa upp ditt projekt](../../../clean-up.md) när du är klar.

> 💁 Du kan se kostnaderna för att använda Azure Container Registry på [Azure Container Registry-prissidan](https://azure.microsoft.com/pricing/details/container-registry/?WT.mc_id=academic-17441-jabenn).

### Uppgift - installera Docker

För att bygga och distribuera klassificeraren kan du behöva installera [Docker](https://www.docker.com/).

Du behöver bara göra detta om du planerar att bygga din container från en annan enhet än den du installerade IoT Edge på - som en del av IoT Edge-installationen installeras Docker åt dig.

1. Om du bygger Docker-containern på en annan enhet än din IoT Edge-enhet, följ installationsinstruktionerna på [Docker install-sidan](https://www.docker.com/products/docker-desktop) för att installera Docker Desktop eller Docker-motorn. Se till att den körs efter installationen.

### Uppgift - skapa en containerregisterresurs

1. Kör följande kommando från din terminal eller kommandotolk för att skapa en Azure Container Registry-resurs:

    ```sh
    az acr create --resource-group fruit-quality-detector \
                  --sku Basic \
                  --name <Container registry name>
    ```

    Ersätt `<Container registry name>` med ett unikt namn för ditt containerregister, med endast bokstäver och siffror. Basera detta på `fruitqualitydetector`. Detta namn blir en del av URL:en för att komma åt containerregistret, så det måste vara globalt unikt.

1. Logga in på Azure Container Registry med följande kommando:

    ```sh
    az acr login --name <Container registry name>
    ```

    Ersätt `<Container registry name>` med namnet du använde för ditt containerregister.

1. Aktivera administratörsläge för containerregistret så att du kan generera ett lösenord med följande kommando:

    ```sh
    az acr update --admin-enabled true \
                 --name <Container registry name>
    ```

    Ersätt `<Container registry name>` med namnet du använde för ditt containerregister.

1. Generera lösenord för ditt containerregister med följande kommando:

    ```sh
     az acr credential renew --password-name password \
                             --output table \
                             --name <Container registry name>
    ```

    Ersätt `<Container registry name>` med namnet du använde för ditt containerregister.

    Ta en kopia av värdet för `PASSWORD`, eftersom du kommer att behöva detta senare.

### Uppgift - bygg din container

Det du laddade ner från Custom Vision var en DockerFile som innehåller instruktioner om hur containern ska byggas, tillsammans med applikationskod som kommer att köras inuti containern för att vara värd för din Custom Vision-modell, samt en REST API för att anropa den. Du kan använda Docker för att bygga en taggad container från DockerFile och sedan skicka den till ditt containerregister.

> 🎓 Containrar får en tagg som definierar ett namn och en version för dem. När du behöver uppdatera en container kan du bygga den med samma tagg men en nyare version.

1. Öppna din terminal eller kommandotolk och navigera till den uppackade modellen som du laddade ner från Custom Vision.

1. Kör följande kommando för att bygga och tagga bilden:

    ```sh
    docker build --platform <platform> -t <Container registry name>.azurecr.io/classifier:v1 .
    ```

    Ersätt `<platform>` med plattformen som denna container kommer att köras på. Om du kör IoT Edge på en Raspberry Pi, sätt detta till `linux/armhf`, annars sätt detta till `linux/amd64`.

    > 💁 Om du kör detta kommando från enheten du kör IoT Edge från, som att köra detta från din Raspberry Pi, kan du utelämna `--platform <platform>`-delen eftersom det standardmässigt använder den aktuella plattformen.

    Ersätt `<Container registry name>` med namnet du använde för ditt containerregister.

    > 💁 Om du kör på Linux eller Raspberry Pi OS kan du behöva använda `sudo` för att köra detta kommando.

    Docker kommer att bygga bilden och konfigurera all nödvändig programvara. Bilden kommer sedan att taggas som `classifier:v1`.

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

### Uppgift - skicka din container till ditt containerregister

1. Använd följande kommando för att skicka din container till ditt containerregister:

    ```sh
    docker push <Container registry name>.azurecr.io/classifier:v1
    ```

    Ersätt `<Container registry name>` med namnet du använde för ditt containerregister.

    > 💁 Om du kör Linux kan du behöva använda `sudo` för att köra detta kommando.

    Containern kommer att skickas till containerregistret.

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

1. För att verifiera att det skickades, kan du lista containrarna i ditt register med följande kommando:

    ```sh
    az acr repository list --output table \
                           --name <Container registry name> 
    ```

    Ersätt `<Container registry name>` med namnet du använde för ditt containerregister.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux az acr repository list --name fruitqualitydetectorjimb --output table
    Result
    ----------
    classifier
    ```

    Du kommer att se din klassificerare listad i utdata.

## Distribuera din container

Din container kan nu distribueras till din IoT Edge-enhet. För att distribuera behöver du definiera ett distributionsmanifest - ett JSON-dokument som listar modulerna som kommer att distribueras till edge-enheten.

### Uppgift - skapa distributionsmanifestet

1. Skapa en ny fil som heter `deployment.json` någonstans på din dator.

1. Lägg till följande i denna fil:

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

    > 💁 Du kan hitta denna fil i mappen [code-deployment/deployment](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-deployment/deployment).

    Ersätt de tre instanserna av `<Container registry name>` med namnet du använde för ditt containerregister. En är i sektionen `ImageClassifier`-modul, de andra två är i sektionen `registryCredentials`.

    Ersätt `<Container registry password>` i sektionen `registryCredentials` med ditt containerregisterlösenord.

1. Från mappen som innehåller ditt distributionsmanifest, kör följande kommando:

    ```sh
    az iot edge set-modules --device-id fruit-quality-detector-edge \
                            --content deployment.json \
                            --hub-name <hub_name>
    ```

    Ersätt `<hub_name>` med namnet på din IoT Hub.

    Bildklassificeringsmodulen kommer att distribueras till din edge-enhet.

### Uppgift - verifiera att klassificeraren körs

1. Anslut till IoT Edge-enheten:

    * Om du använder en Raspberry Pi för att köra IoT Edge, anslut med ssh antingen från din terminal eller via en fjärr-SSH-session i VS Code.
    * Om du kör IoT Edge i en Linux-container på Windows, följ stegen i [guiden för att verifiera lyckad konfiguration](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge-on-windows?WT.mc_id=academic-17441-jabenn&view=iotedge-2018-06&tabs=powershell#verify-successful-configuration) för att ansluta till IoT Edge-enheten.
    * Om du kör IoT Edge på en virtuell maskin kan du SSH:a in i maskinen med `adminUsername` och `password` du angav när du skapade VM:n, och använda antingen IP-adressen eller DNS-namnet:

        ```sh
        ssh <adminUsername>@<IP address>
        ```

        Eller:

        ```sh
        ssh <adminUsername>@<DNS Name>
        ```

        Ange ditt lösenord när du blir ombedd.

1. När du är ansluten, kör följande kommando för att få listan över IoT Edge-moduler:

    ```sh
    iotedge list
    ```

    > 💁 Du kan behöva köra detta kommando med `sudo`.

    Du kommer att se de körande modulerna:

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge list
    NAME             STATUS           DESCRIPTION      CONFIG
    ImageClassifier  running          Up 42 minutes    fruitqualitydetectorjimb.azurecr.io/classifier:v1
    edgeAgent        running          Up 42 minutes    mcr.microsoft.com/azureiotedge-agent:1.1
    edgeHub          running          Up 42 minutes    mcr.microsoft.com/azureiotedge-hub:1.1
    ```

1. Kontrollera loggarna för bildklassificeringsmodulen med följande kommando:

    ```sh
    iotedge logs ImageClassifier
    ```

    > 💁 Du kan behöva köra detta kommando med `sudo`.

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

### Uppgift - testa bildklassificeraren

1. Du kan använda CURL för att testa bildklassificeraren med hjälp av IP-adressen eller värdnamnet för datorn som kör IoT Edge-agenten. Hitta IP-adressen:

    * Om du är på samma maskin som IoT Edge körs på kan du använda `localhost` som värdnamn.
    * Om du använder en VM kan du använda antingen IP-adressen eller DNS-namnet för VM:n.
    * Annars kan du få IP-adressen för maskinen som kör IoT Edge:
      * På Windows 10, följ [guiden för att hitta din IP-adress](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn).
      * På macOS, följ [guiden för att hitta din IP-adress på Mac](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac).
      * På Linux, följ sektionen om att hitta din privata IP-adress i [guiden för att hitta din IP-adress i Linux](https://opensource.com/article/18/5/how-find-ip-address-linux).

1. Du kan testa containern med en lokal fil genom att köra följande curl-kommando:

    ```sh
    curl --location \
         --request POST 'http://<IP address or name>/image' \
         --header 'Content-Type: image/png' \
         --data-binary '@<file_Name>' 
    ```

    Ersätt `<IP address or name>` med IP-adressen eller värdnamnet för datorn som kör IoT Edge. Ersätt `<file_Name>` med namnet på filen som ska testas.

    Du kommer att se förutsägelseresultaten i utdata:

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

    > 💁 Det finns inget behov av att ange en förutsägelsenyckel här, eftersom detta inte använder en Azure-resurs. Istället skulle säkerheten konfigureras på det interna nätverket baserat på interna säkerhetsbehov, snarare än att förlita sig på en offentlig endpoint och en API-nyckel.

## Använd din IoT Edge-enhet

Nu när din bildklassificerare har distribuerats till en IoT Edge-enhet kan du använda den från din IoT-enhet.

### Uppgift - använd din IoT Edge-enhet

Arbeta igenom den relevanta guiden för att klassificera bilder med IoT Edge-klassificeraren:

* [Arduino - Wio Terminal](wio-terminal.md)
* [Enkorts-dator - Raspberry Pi/Virtual IoT-enhet](single-board-computer.md)

### Modellträning

En av nackdelarna med att köra bildklassificerare på IoT Edge är att de inte är anslutna till ditt Custom Vision-projekt. Om du tittar på fliken **Predictions** i Custom Vision kommer du inte att se bilderna som klassificerades med Edge-baserade klassificeraren.

Detta är förväntat beteende - bilder skickas inte till molnet för klassificering, så de kommer inte att vara tillgängliga i molnet. En av fördelarna med att använda IoT Edge är integritet, vilket säkerställer att bilder inte lämnar ditt nätverk, en annan är att kunna arbeta offline, så att du inte behöver förlita dig på att ladda upp bilder när enheten saknar internetanslutning. Nackdelen är att förbättra din modell - du skulle behöva implementera ett annat sätt att lagra bilder som kan klassificeras manuellt för att förbättra och träna om bildklassificeraren.

✅ Fundera på sätt att ladda upp bilder för att träna om klassificeraren.

---

## 🚀 Utmaning

Att köra AI-modeller på edge-enheter kan vara snabbare än i molnet - nätverkshoppet är kortare. De kan också vara långsammare eftersom hårdvaran som kör modellen kanske inte är lika kraftfull som molnet.

Gör några tidmätningar och jämför om anropet till din edge-enhet är snabbare eller långsammare än anropet till molnet? Fundera på orsaker som kan förklara skillnaden, eller avsaknaden av skillnad. Undersök sätt att köra AI-modeller snabbare på edge med specialiserad hårdvara.

## Quiz efter föreläsningen

[Quiz efter föreläsningen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/34)

## Granskning & Självstudier

* Läs mer om containrar på [OS-nivå virtualiseringssidan på Wikipedia](https://wikipedia.org/wiki/OS-level_virtualization).
* Läs mer om edge computing, med fokus på hur 5G kan hjälpa till att expandera edge computing i [vad är edge computing och varför är det viktigt? artikeln på NetworkWorld](https://www.networkworld.com/article/3224893/what-is-edge-computing-and-how-its-changing-the-network.html)
* Lär dig mer om att köra AI-tjänster i IoT Edge genom att titta på [lär dig hur du använder Azure IoT Edge på en förbyggd AI-tjänst på Edge för att utföra språkdetection-avsnittet av Learn Live på Microsoft Channel9](https://channel9.msdn.com/Shows/Learn-Live/Sharpen-Your-AI-Edge-Skills-Episode-4-Learn-How-to-Use-Azure-IoT-Edge-on-a-Pre-Built-AI-Service-on-t?WT.mc_id=academic-17441-jabenn)

## Uppgift

[Kör andra tjänster på edge](assignment.md)

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiska översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.