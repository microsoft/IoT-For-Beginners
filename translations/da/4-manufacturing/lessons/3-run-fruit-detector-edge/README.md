<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2625af24587465c5547ae33d6cc000a5",
  "translation_date": "2025-08-27T20:34:58+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/README.md",
  "language_code": "da"
}
-->
# Kør din frugtdetektor på kanten

![En sketchnote-oversigt over denne lektion](../../../../../translated_images/da/lesson-17.bc333c3c35ba8e42cce666cfffa82b915f787f455bd94e006aea2b6f2722421a.jpg)

> Sketchnote af [Nitya Narasimhan](https://github.com/nitya). Klik på billedet for en større version.

Denne video giver en oversigt over, hvordan man kører billedklassifikatorer på IoT-enheder, emnet der dækkes i denne lektion.

[![Custom Vision AI på Azure IoT Edge](https://img.youtube.com/vi/_K5fqGLO8us/0.jpg)](https://www.youtube.com/watch?v=_K5fqGLO8us)

## Quiz før lektionen

[Quiz før lektionen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/33)

## Introduktion

I den sidste lektion brugte du din billedklassifikator til at klassificere modne og umodne frugter ved at sende et billede taget af kameraet på din IoT-enhed over internettet til en cloud-tjeneste. Disse kald tager tid, koster penge og kan, afhængigt af hvilken type billeddata du bruger, have privatlivsmæssige konsekvenser.

I denne lektion vil du lære, hvordan man kører maskinlæringsmodeller (ML) på kanten - på IoT-enheder, der kører på dit eget netværk i stedet for i skyen. Du vil lære om fordelene og ulemperne ved edge computing kontra cloud computing, hvordan du implementerer din AI-model på kanten, og hvordan du får adgang til den fra din IoT-enhed.

I denne lektion dækker vi:

* [Edge computing](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Azure IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Registrer en IoT Edge-enhed](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Opsæt en IoT Edge-enhed](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Eksportér din model](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Forbered din container til implementering](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Implementér din container](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Brug din IoT Edge-enhed](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)

## Edge computing

Edge computing indebærer, at computere behandler IoT-data så tæt som muligt på det sted, hvor dataene genereres. I stedet for at have denne behandling i skyen, flyttes den til kanten af skyen - dit interne netværk.

![Et arkitekturdiagram, der viser internettjenester i skyen og IoT-enheder på et lokalt netværk](../../../../../translated_images/da/cloud-without-edge.b4da641f6022c95ed6b91fde8b5323abd2f94e0d52073ad54172ae8f5dac90e9.png)

I de tidligere lektioner har du haft enheder, der indsamler data og sender data til skyen for at blive analyseret, hvor serverløse funktioner eller AI-modeller kører i skyen.

![Et arkitekturdiagram, der viser IoT-enheder på et lokalt netværk, der forbinder til edge-enheder, og disse edge-enheder forbinder til skyen](../../../../../translated_images/da/cloud-with-edge.1e26462c62c126fe150bd15a5714ddf0be599f09bacbad08b85be02b76ea1ae1.png)

Edge computing indebærer at flytte nogle af cloud-tjenesterne væk fra skyen og over på computere, der kører på samme netværk som IoT-enhederne, og kun kommunikere med skyen, hvis det er nødvendigt. For eksempel kan du køre AI-modeller på edge-enheder for at analysere frugtens modenhed og kun sende analyser tilbage til skyen, såsom antallet af modne frugter kontra umodne.

✅ Tænk over de IoT-applikationer, du har bygget indtil nu. Hvilke dele af dem kunne flyttes til kanten?

### Fordele

Fordelene ved edge computing er:

1. **Hastighed** - edge computing er ideel til tidsfølsomme data, da handlinger udføres på samme netværk som enheden, i stedet for at foretage kald over internettet. Dette muliggør højere hastigheder, da interne netværk kan køre væsentligt hurtigere end internetforbindelser, med data, der rejser meget kortere afstande.

    > 💁 Selvom optiske kabler bruges til internetforbindelser, der tillader data at rejse med lysets hastighed, kan det tage tid for data at rejse rundt om i verden til cloud-udbydere. For eksempel, hvis du sender data fra Europa til cloud-tjenester i USA, tager det mindst 28 ms for dataene at krydse Atlanten i et optisk kabel, og det er uden at tage højde for tiden, det tager at få dataene til det transatlantiske kabel, konvertere fra elektriske til lys-signaler og tilbage igen på den anden side, og derefter fra det optiske kabel til cloud-udbyderen.

    Edge computing kræver også mindre netværkstrafik, hvilket reducerer risikoen for, at dine data bliver langsommere på grund af overbelastning på den begrænsede båndbredde, der er tilgængelig for en internetforbindelse.

1. **Fjernadgang** - edge computing fungerer, når du har begrænset eller ingen forbindelse, eller når forbindelsen er for dyr til at bruge kontinuerligt. For eksempel i humanitære katastrofeområder, hvor infrastrukturen er begrænset, eller i udviklingslande.

1. **Lavere omkostninger** - ved at udføre dataindsamling, lagring, analyse og udløsning af handlinger på edge-enheder reduceres brugen af cloud-tjenester, hvilket kan reducere de samlede omkostninger ved din IoT-applikation. Der har været en nylig stigning i enheder designet til edge computing, såsom AI-acceleratorboards som [Jetson Nano fra NVIDIA](https://developer.nvidia.com/embedded/jetson-nano-developer-kit), der kan køre AI-arbejdsbelastninger ved hjælp af GPU-baseret hardware på enheder, der koster mindre end 100 USD.

1. **Privatliv og sikkerhed** - med edge computing forbliver data på dit netværk og uploades ikke til skyen. Dette foretrækkes ofte for følsomme og personligt identificerbare oplysninger, især fordi data ikke behøver at blive gemt efter at være blevet analyseret, hvilket i høj grad reducerer risikoen for datalækager. Eksempler inkluderer medicinske data og optagelser fra sikkerhedskameraer.

1. **Håndtering af usikre enheder** - hvis du har enheder med kendte sikkerhedsfejl, som du ikke ønsker at forbinde direkte til dit netværk eller internettet, kan du forbinde dem til et separat netværk via en gateway IoT Edge-enhed. Denne edge-enhed kan derefter også have en forbindelse til dit bredere netværk eller internettet og administrere dataflowet frem og tilbage.

1. **Support til inkompatible enheder** - hvis du har enheder, der ikke kan forbinde til IoT Hub, for eksempel enheder, der kun kan forbinde via HTTP-forbindelser eller enheder, der kun har Bluetooth, kan du bruge en IoT Edge-enhed som en gateway-enhed, der videresender beskeder til IoT Hub.

✅ Lav noget research: Hvilke andre fordele kunne der være ved edge computing?

### Ulemper

Der er også ulemper ved edge computing, hvor skyen kan være en foretrukken løsning:

1. **Skalering og fleksibilitet** - cloud computing kan tilpasse sig netværks- og databehov i realtid ved at tilføje eller reducere servere og andre ressourcer. For at tilføje flere edge-computere kræves manuel tilføjelse af flere enheder.

1. **Pålidelighed og robusthed** - cloud computing tilbyder flere servere, ofte på flere lokationer, for redundans og katastrofeberedskab. For at opnå samme niveau af redundans på kanten kræves store investeringer og meget konfigurationsarbejde.

1. **Vedligeholdelse** - cloud-tjenesteudbydere sørger for systemvedligeholdelse og opdateringer.

✅ Lav noget research: Hvilke andre ulemper kunne der være ved edge computing?

Ulemperne er i virkeligheden det modsatte af fordelene ved at bruge skyen - du skal selv bygge og administrere disse enheder i stedet for at stole på ekspertisen og skalaen fra cloud-udbydere.

Nogle af risiciene afbødes af selve naturen af edge computing. For eksempel, hvis du har en edge-enhed, der kører i en fabrik og indsamler data fra maskiner, behøver du ikke tænke på visse katastrofeberedskabsscenarier. Hvis strømmen til fabrikken går, behøver du ikke en backup-edge-enhed, da maskinerne, der genererer de data, edge-enheden behandler, også vil være uden strøm.

For IoT-systemer vil du ofte have en blanding af cloud- og edge computing, hvor du udnytter hver tjeneste baseret på systemets behov, dets kunder og dets vedligeholdere.

## Azure IoT Edge

![Azure IoT Edge-logoet](../../../../../translated_images/da/azure-iot-edge-logo.c1c076749b5cba2e8755262fadc2f19ca1146b948d76990b1229199ac2292d79.png)

Azure IoT Edge er en tjeneste, der kan hjælpe dig med at flytte arbejdsbelastninger ud af skyen og til kanten. Du opsætter en enhed som en edge-enhed, og fra skyen kan du implementere kode på den edge-enhed. Dette giver dig mulighed for at blande skyens og kantens kapaciteter.

> 🎓 *Arbejdsbelastninger* er et udtryk for enhver tjeneste, der udfører en form for arbejde, såsom AI-modeller, applikationer eller serverløse funktioner.

For eksempel kan du træne en billedklassifikator i skyen og derefter implementere den fra skyen til en edge-enhed. Din IoT-enhed sender derefter billeder til edge-enheden til klassifikation i stedet for at sende billederne over internettet. Hvis du har brug for at implementere en ny iteration af modellen, kan du træne den i skyen og bruge IoT Edge til at opdatere modellen på edge-enheden til din nye iteration.

> 🎓 Software, der implementeres på IoT Edge, kaldes *moduler*. Som standard kører IoT Edge moduler, der kommunikerer med IoT Hub, såsom `edgeAgent` og `edgeHub` modulerne. Når du implementerer en billedklassifikator, implementeres dette som et ekstra modul.

IoT Edge er indbygget i IoT Hub, så du kan administrere edge-enheder ved hjælp af den samme tjeneste, som du ville bruge til at administrere IoT-enheder, med samme sikkerhedsniveau.

IoT Edge kører kode fra *containere* - selvstændige applikationer, der kører isoleret fra resten af applikationerne på din computer. Når du kører en container, fungerer den som en separat computer, der kører inde i din computer, med sin egen software, tjenester og applikationer. De fleste gange kan containere ikke få adgang til noget på din computer, medmindre du vælger at dele ting som en mappe med containeren. Containeren eksponerer derefter tjenester via en åben port, som du kan forbinde til eller eksponere for dit netværk.

![En webanmodning omdirigeret til en container](../../../../../translated_images/da/container-web-browser.4ee81dd4f0d8838ce622b2a0d600b6a4322b5d4fe43159facd87b7b34f84d66a.png)

For eksempel kan du have en container med et websted, der kører på port 80, standard HTTP-porten, og du kan derefter eksponere den fra din computer også på port 80.

✅ Lav noget research: Læs om containere og tjenester som Docker eller Moby.

Du kan bruge Custom Vision til at downloade billedklassifikatorer og implementere dem som containere, enten direkte på en enhed eller implementeret via IoT Edge. Når de kører i en container, kan de tilgås ved hjælp af den samme REST API som cloud-versionen, men med endpointet, der peger på edge-enheden, der kører containeren.

## Registrer en IoT Edge-enhed

For at bruge en IoT Edge-enhed skal den registreres i IoT Hub.

### Opgave - registrer en IoT Edge-enhed

1. Opret en IoT Hub i `fruit-quality-detector`-ressourcegruppen. Giv den et unikt navn baseret på `fruit-quality-detector`.

1. Registrer en IoT Edge-enhed kaldet `fruit-quality-detector-edge` i din IoT Hub. Kommandoen til at gøre dette ligner den, der bruges til at registrere en ikke-edge-enhed, bortset fra at du tilføjer flaget `--edge-enabled`.

    ```sh
    az iot hub device-identity create --edge-enabled \
                                      --device-id fruit-quality-detector-edge \
                                      --hub-name <hub_name>
    ```

    Erstat `<hub_name>` med navnet på din IoT Hub.

1. Hent forbindelsesstrengen til din enhed ved hjælp af følgende kommando:

    ```sh
    az iot hub device-identity connection-string show --device-id fruit-quality-detector-edge \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    Erstat `<hub_name>` med navnet på din IoT Hub.

    Tag en kopi af forbindelsesstrengen, der vises i outputtet.

## Opsæt en IoT Edge-enhed

Når du har oprettet edge-enhedsregistreringen i din IoT Hub, kan du opsætte edge-enheden.

### Opgave - Installer og start IoT Edge Runtime

**IoT Edge runtime kører kun Linux-containere.** Det kan køre på Linux eller på Windows ved hjælp af Linux Virtual Machines.

* Hvis du bruger en Raspberry Pi som din IoT-enhed, kører denne en understøttet version af Linux og kan være vært for IoT Edge runtime. Følg [installationsguiden til Azure IoT Edge for Linux på Microsoft Docs](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) for at installere IoT Edge og indstille forbindelsesstrengen.

    > 💁 Husk, at Raspberry Pi OS er en variant af Debian Linux.

* Hvis du ikke bruger en Raspberry Pi, men har en Linux-computer, kan du køre IoT Edge runtime. Følg [installationsguiden til Azure IoT Edge for Linux på Microsoft Docs](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) for at installere IoT Edge og indstille forbindelsesstrengen.

* Hvis du bruger Windows, kan du installere IoT Edge runtime i en Linux Virtual Machine ved at følge [installations- og startsektionen for IoT Edge runtime i quickstart-guiden til implementering af dit første IoT Edge-modul på en Windows-enhed på Microsoft Docs](https://docs.microsoft.com/azure/iot-edge/quickstart?WT.mc_id=academic-17441-jabenn#install-and-start-the-iot-edge-runtime). Du kan stoppe, når du når sektionen *Deploy a module*.

* Hvis du bruger macOS, kan du oprette en virtuel maskine (VM) i skyen til brug som din IoT Edge-enhed. Disse er computere, du kan oprette i skyen og få adgang til via internettet. Du kan oprette en Linux VM, der har IoT Edge installeret. Følg [guiden til oprettelse af en virtuel maskine, der kører IoT Edge](vm-iotedge.md) for instruktioner om, hvordan du gør dette.

## Eksportér din model

For at køre klassifikatoren på kanten skal den eksporteres fra Custom Vision. Custom Vision kan generere to typer modeller - standardmodeller og kompakte modeller. Kompakte modeller bruger forskellige teknikker til at reducere modellens størrelse, hvilket gør den lille nok til at blive downloadet og implementeret på IoT-enheder.

Da du oprettede billedklassifikatoren, brugte du *Food*-domænet, en version af modellen, der er optimeret til træning på madbilleder. I Custom Vision kan du ændre domænet for dit projekt og bruge dine træningsdata til at træne en ny model med det nye domæne. Alle de domæner, der understøttes af Custom Vision, er tilgængelige som standard og kompakte.

### Opgave - træn din model ved hjælp af Food (kompakt) domænet
1. Åbn Custom Vision-portalen på [CustomVision.ai](https://customvision.ai) og log ind, hvis du ikke allerede har den åben. Åbn derefter dit projekt `fruit-quality-detector`.

1. Vælg knappen **Indstillinger** (⚙-ikonet).

1. I listen *Domæner* skal du vælge *Food (compact)*.

1. Under *Eksportmuligheder* skal du sikre dig, at *Basic platforms (Tensorflow, CoreML, ONNX, ...)* er valgt.

1. Nederst på siden med indstillinger skal du vælge **Gem ændringer**.

1. Gen-træn modellen ved at klikke på knappen **Træn**, og vælg *Hurtig træning*.

### Opgave - eksporter din model

Når modellen er blevet trænet, skal den eksporteres som en container.

1. Vælg fanen **Ydelse**, og find din seneste iteration, der blev trænet med det kompakte domæne.

1. Klik på knappen **Eksporter** øverst.

1. Vælg **DockerFile**, og vælg derefter en version, der passer til din edge-enhed:

    * Hvis du kører IoT Edge på en Linux-computer, en Windows-computer eller en virtuel maskine, skal du vælge *Linux*-versionen.
    * Hvis du kører IoT Edge på en Raspberry Pi, skal du vælge *ARM (Raspberry Pi 3)*-versionen.

> 🎓 Docker er et af de mest populære værktøjer til at håndtere containere, og en DockerFile er et sæt instruktioner til, hvordan containeren skal opsættes.

1. Vælg **Eksporter** for at få Custom Vision til at oprette de relevante filer, og derefter **Download** for at hente dem som en zip-fil.

1. Gem filerne på din computer, og udpak mappen.

## Forbered din container til implementering

![Containere bygges og pushes derefter til et containerregister, hvorefter de implementeres fra containerregisteret til en edge-enhed ved hjælp af IoT Edge](../../../../../translated_images/da/container-edge-flow.c246050dd60ceefdb6ace026a4ce5c6aa4112bb5898ae23fbb2ab4be29ae3e1b.png)

Når du har downloadet din model, skal den bygges som en container og derefter pushes til et containerregister - et online sted, hvor du kan gemme containere. IoT Edge kan derefter downloade containeren fra registeret og sende den til din enhed.

![Azure Container Registry-logoet](../../../../../translated_images/da/azure-container-registry-logo.09494206991d4b295025ebff7d4e2900325e527a59184ffbc8464b6ab59654be.png)

Det containerregister, du vil bruge i denne lektion, er Azure Container Registry. Dette er ikke en gratis tjeneste, så for at spare penge skal du sørge for at [rydde op i dit projekt](../../../clean-up.md), når du er færdig.

> 💁 Du kan se omkostningerne ved at bruge et Azure Container Registry på [Azure Container Registry-prissiden](https://azure.microsoft.com/pricing/details/container-registry/?WT.mc_id=academic-17441-jabenn).

### Opgave - installer Docker

For at bygge og implementere klassifikatoren skal du muligvis installere [Docker](https://www.docker.com/).

Du skal kun gøre dette, hvis du planlægger at bygge din container fra en anden enhed end den, hvor du installerede IoT Edge - som en del af installationen af IoT Edge bliver Docker installeret for dig.

1. Hvis du bygger Docker-containeren på en anden enhed end din IoT Edge-enhed, skal du følge installationsvejledningen på [Docker install-siden](https://www.docker.com/products/docker-desktop) for at installere Docker Desktop eller Docker-motoren. Sørg for, at den kører efter installationen.

### Opgave - opret en containerregisterressource

1. Kør følgende kommando fra din terminal eller kommandoprompt for at oprette en Azure Container Registry-ressource:

    ```sh
    az acr create --resource-group fruit-quality-detector \
                  --sku Basic \
                  --name <Container registry name>
    ```

    Erstat `<Container registry name>` med et unikt navn til dit containerregister, kun med bogstaver og tal. Brug navnet `fruitqualitydetector` som udgangspunkt. Dette navn bliver en del af URL'en til at få adgang til containerregisteret, så det skal være globalt unikt.

1. Log ind på Azure Container Registry med følgende kommando:

    ```sh
    az acr login --name <Container registry name>
    ```

    Erstat `<Container registry name>` med det navn, du brugte til dit containerregister.

1. Sæt containerregisteret i admin-tilstand, så du kan generere en adgangskode med følgende kommando:

    ```sh
    az acr update --admin-enabled true \
                 --name <Container registry name>
    ```

    Erstat `<Container registry name>` med det navn, du brugte til dit containerregister.

1. Generer adgangskoder til dit containerregister med følgende kommando:

    ```sh
     az acr credential renew --password-name password \
                             --output table \
                             --name <Container registry name>
    ```

    Erstat `<Container registry name>` med det navn, du brugte til dit containerregister.

    Tag en kopi af værdien `PASSWORD`, da du får brug for den senere.

### Opgave - byg din container

Det, du downloadede fra Custom Vision, var en DockerFile med instruktioner om, hvordan containeren skal bygges, sammen med applikationskode, der vil blive kørt inde i containeren for at hoste din Custom Vision-model og en REST API til at kalde den. Du kan bruge Docker til at bygge en tagget container fra DockerFile og derefter pushe den til dit containerregister.

> 🎓 Containere får et tag, der definerer et navn og en version for dem. Når du skal opdatere en container, kan du bygge den med det samme tag, men med en nyere version.

1. Åbn din terminal eller kommandoprompt, og naviger til den udpakkede model, du downloadede fra Custom Vision.

1. Kør følgende kommando for at bygge og tagge billedet:

    ```sh
    docker build --platform <platform> -t <Container registry name>.azurecr.io/classifier:v1 .
    ```

    Erstat `<platform>` med den platform, som denne container skal køre på. Hvis du kører IoT Edge på en Raspberry Pi, skal du sætte dette til `linux/armhf`, ellers skal du sætte det til `linux/amd64`.

    > 💁 Hvis du kører denne kommando fra den enhed, hvor du kører IoT Edge, som f.eks. fra din Raspberry Pi, kan du udelade `--platform <platform>`-delen, da den som standard bruger den aktuelle platform.

    Erstat `<Container registry name>` med det navn, du brugte til dit containerregister.

    > 💁 Hvis du kører på Linux eller Raspberry Pi OS, skal du muligvis bruge `sudo` til at køre denne kommando.

    Docker vil bygge billedet og konfigurere al nødvendig software. Billedet vil derefter blive tagget som `classifier:v1`.

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

### Opgave - push din container til dit containerregister

1. Brug følgende kommando til at pushe din container til dit containerregister:

    ```sh
    docker push <Container registry name>.azurecr.io/classifier:v1
    ```

    Erstat `<Container registry name>` med det navn, du brugte til dit containerregister.

    > 💁 Hvis du kører Linux, skal du muligvis bruge `sudo` til at køre denne kommando.

    Containeren vil blive pushet til containerregisteret.

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

1. For at verificere pushet kan du liste containerne i dit register med følgende kommando:

    ```sh
    az acr repository list --output table \
                           --name <Container registry name> 
    ```

    Erstat `<Container registry name>` med det navn, du brugte til dit containerregister.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux az acr repository list --name fruitqualitydetectorjimb --output table
    Result
    ----------
    classifier
    ```

    Du vil se din klassifikator opført i outputtet.

## Implementer din container

Din container kan nu implementeres på din IoT Edge-enhed. For at implementere skal du definere et implementeringsmanifest - et JSON-dokument, der lister de moduler, der skal implementeres på edge-enheden.

### Opgave - opret implementeringsmanifestet

1. Opret en ny fil kaldet `deployment.json` et sted på din computer.

1. Tilføj følgende til denne fil:

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

    > 💁 Du kan finde denne fil i mappen [code-deployment/deployment](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-deployment/deployment).

    Erstat de tre forekomster af `<Container registry name>` med det navn, du brugte til dit containerregister. Én er i sektionen `ImageClassifier`-modul, de andre to er i sektionen `registryCredentials`.

    Erstat `<Container registry password>` i sektionen `registryCredentials` med din containerregister-adgangskode.

1. Fra mappen, der indeholder dit implementeringsmanifest, skal du køre følgende kommando:

    ```sh
    az iot edge set-modules --device-id fruit-quality-detector-edge \
                            --content deployment.json \
                            --hub-name <hub_name>
    ```

    Erstat `<hub_name>` med navnet på din IoT Hub.

    Image classifier-modulet vil blive implementeret på din edge-enhed.

### Opgave - verificer, at klassifikatoren kører

1. Forbind til IoT Edge-enheden:

    * Hvis du bruger en Raspberry Pi til at køre IoT Edge, skal du forbinde via ssh enten fra din terminal eller via en fjern-SSH-session i VS Code.
    * Hvis du kører IoT Edge i en Linux-container på Windows, skal du følge trinnene i [vejledningen til at verificere succesfuld konfiguration](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge-on-windows?WT.mc_id=academic-17441-jabenn&view=iotedge-2018-06&tabs=powershell#verify-successful-configuration) for at forbinde til IoT Edge-enheden.
    * Hvis du kører IoT Edge på en virtuel maskine, kan du SSH'e ind i maskinen ved hjælp af `adminUsername` og `password`, som du satte, da du oprettede VM'en, og bruge enten IP-adressen eller DNS-navnet:

        ```sh
        ssh <adminUsername>@<IP address>
        ```

        Eller:

        ```sh
        ssh <adminUsername>@<DNS Name>
        ```

        Indtast din adgangskode, når du bliver bedt om det.

1. Når du er forbundet, skal du køre følgende kommando for at få listen over IoT Edge-moduler:

    ```sh
    iotedge list
    ```

    > 💁 Du skal muligvis køre denne kommando med `sudo`.

    Du vil se de kørende moduler:

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge list
    NAME             STATUS           DESCRIPTION      CONFIG
    ImageClassifier  running          Up 42 minutes    fruitqualitydetectorjimb.azurecr.io/classifier:v1
    edgeAgent        running          Up 42 minutes    mcr.microsoft.com/azureiotedge-agent:1.1
    edgeHub          running          Up 42 minutes    mcr.microsoft.com/azureiotedge-hub:1.1
    ```

1. Tjek logfilerne for Image classifier-modulet med følgende kommando:

    ```sh
    iotedge logs ImageClassifier
    ```

    > 💁 Du skal muligvis køre denne kommando med `sudo`.

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

### Opgave - test billedklassifikatoren

1. Du kan bruge CURL til at teste billedklassifikatoren ved hjælp af IP-adressen eller værtsnavnet på computeren, der kører IoT Edge-agenten. Find IP-adressen:

    * Hvis du er på samme maskine, som IoT Edge kører på, kan du bruge `localhost` som værtsnavn.
    * Hvis du bruger en VM, kan du bruge enten IP-adressen eller DNS-navnet på VM'en.
    * Ellers kan du finde IP-adressen på maskinen, der kører IoT Edge:
      * På Windows 10, følg [vejledningen til at finde din IP-adresse](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn).
      * På macOS, følg [vejledningen til at finde din IP-adresse på en Mac](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac).
      * På Linux, følg sektionen om at finde din private IP-adresse i [vejledningen til at finde din IP-adresse i Linux](https://opensource.com/article/18/5/how-find-ip-address-linux).

1. Du kan teste containeren med en lokal fil ved at køre følgende curl-kommando:

    ```sh
    curl --location \
         --request POST 'http://<IP address or name>/image' \
         --header 'Content-Type: image/png' \
         --data-binary '@<file_Name>' 
    ```

    Erstat `<IP address or name>` med IP-adressen eller værtsnavnet på computeren, der kører IoT Edge. Erstat `<file_Name>` med navnet på filen, der skal testes.

    Du vil se forudsigelsesresultaterne i outputtet:

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

    > 💁 Der er ikke behov for at angive en forudsigelsesnøgle her, da dette ikke bruger en Azure-ressource. I stedet vil sikkerheden blive konfigureret på det interne netværk baseret på interne sikkerhedsbehov, frem for at stole på et offentligt endpoint og en API-nøgle.

## Brug din IoT Edge-enhed

Nu hvor din Image Classifier er blevet implementeret på en IoT Edge-enhed, kan du bruge den fra din IoT-enhed.

### Opgave - brug din IoT Edge-enhed

Gennemgå den relevante vejledning for at klassificere billeder ved hjælp af IoT Edge-klassifikatoren:

* [Arduino - Wio Terminal](wio-terminal.md)
* [Single-board computer - Raspberry Pi/Virtual IoT device](single-board-computer.md)

### Model-gen-træning

En af ulemperne ved at køre billedklassifikatorer på IoT Edge er, at de ikke er forbundet til dit Custom Vision-projekt. Hvis du ser på fanen **Forudsigelser** i Custom Vision, vil du ikke se de billeder, der blev klassificeret ved hjælp af Edge-baserede klassifikatoren.

Dette er forventet adfærd - billeder sendes ikke til skyen for klassifikation, så de vil ikke være tilgængelige i skyen. En af fordelene ved at bruge IoT Edge er privatliv, der sikrer, at billeder ikke forlader dit netværk, en anden er muligheden for at arbejde offline, så du ikke er afhængig af at uploade billeder, når enheden ikke har internetforbindelse. Ulempen er at forbedre din model - du skal implementere en anden måde at gemme billeder på, som kan klassificeres manuelt for at forbedre og gen-træne billedklassifikatoren.

✅ Tænk over måder at uploade billeder til at gen-træne klassifikatoren.

---

## 🚀 Udfordring

At køre AI-modeller på edge-enheder kan være hurtigere end i skyen - netværkshoppen er kortere. De kan også være langsommere, da hardwaren, der kører modellen, måske ikke er så kraftfuld som skyen.

Tag nogle tidstagninger og sammenlign, om kaldet til din edge-enhed er hurtigere eller langsommere end kaldet til skyen? Tænk over årsager til at forklare forskellen eller manglen på forskel. Undersøg måder at køre AI-modeller hurtigere på edge-enheder ved hjælp af specialiseret hardware.

## Quiz efter lektionen

[Quiz efter lektionen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/34)

## Gennemgang & Selvstudie

* Læs mere om containere på [siden om OS-niveau virtualisering på Wikipedia](https://wikipedia.org/wiki/OS-level_virtualization).
* Læs mere om edge computing, med fokus på hvordan 5G kan hjælpe med at udvide edge computing i [hvad er edge computing, og hvorfor er det vigtigt? artiklen på NetworkWorld](https://www.networkworld.com/article/3224893/what-is-edge-computing-and-how-its-changing-the-network.html)
* Lær mere om at køre AI-tjenester i IoT Edge ved at se [lær hvordan du bruger Azure IoT Edge på en forudbygget AI-tjeneste på Edge til at udføre sprogdetektion-episoden af Learn Live på Microsoft Channel9](https://channel9.msdn.com/Shows/Learn-Live/Sharpen-Your-AI-Edge-Skills-Episode-4-Learn-How-to-Use-Azure-IoT-Edge-on-a-Pre-Built-AI-Service-on-t?WT.mc_id=academic-17441-jabenn)

## Opgave

[Kør andre tjenester på kanten](assignment.md)

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.