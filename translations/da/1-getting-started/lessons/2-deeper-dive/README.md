# En dybere indsigt i IoT

![En sketchnote oversigt over denne lektion](../../../../../translated_images/da/lesson-2.324b0580d620c25e.webp)

> Sketchnote af [Nitya Narasimhan](https://github.com/nitya). Klik på billedet for en større version.

Denne lektion blev undervist som en del af [Hello IoT-serien](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) fra [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Lektionen blev præsenteret i 2 videoer - en 1-times lektion og en 1-times spørgetime, hvor der blev dykket dybere ned i dele af lektionen og besvaret spørgsmål.

[![Lektion 2: En dybere indsigt i IoT](https://img.youtube.com/vi/t0SySWw3z9M/0.jpg)](https://youtu.be/t0SySWw3z9M)

[![Lektion 2: En dybere indsigt i IoT - Spørgetime](https://img.youtube.com/vi/tTZYf9EST1E/0.jpg)](https://youtu.be/tTZYf9EST1E)

> 🎥 Klik på billederne ovenfor for at se videoerne

## Quiz før lektionen

[Quiz før lektionen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/3)

## Introduktion

Denne lektion går dybere ned i nogle af de begreber, der blev dækket i den sidste lektion.

I denne lektion vil vi dække:

* [Komponenter i en IoT-applikation](../../../../../1-getting-started/lessons/2-deeper-dive)
* [Dybere indsigt i mikrocontrollere](../../../../../1-getting-started/lessons/2-deeper-dive)
* [Dybere indsigt i single-board computere](../../../../../1-getting-started/lessons/2-deeper-dive)

## Komponenter i en IoT-applikation

De to komponenter i en IoT-applikation er *Internet* og *ting*. Lad os se nærmere på disse to komponenter.

### Tingen

![En Raspberry Pi 4](../../../../../translated_images/da/raspberry-pi-4.fd4590d308c3d456.webp)

**Tingen** i IoT refererer til en enhed, der kan interagere med den fysiske verden. Disse enheder er normalt små, prisvenlige computere, der kører med lav hastighed og bruger lidt strøm - for eksempel simple mikrocontrollere med kilobyte RAM (i modsætning til gigabyte i en PC), der kører med kun et par hundrede megahertz (i modsætning til gigahertz i en PC), men som nogle gange bruger så lidt strøm, at de kan køre i uger, måneder eller endda år på batterier.

Disse enheder interagerer med den fysiske verden, enten ved at bruge sensorer til at indsamle data fra deres omgivelser eller ved at kontrollere output eller aktuatorer for at foretage fysiske ændringer. Et typisk eksempel er en smart termostat - en enhed, der har en temperatursensor, en måde at indstille en ønsket temperatur på, såsom en drejeknap eller touchscreen, og en forbindelse til et varme- eller kølesystem, der kan tændes, når den registrerede temperatur er uden for det ønskede område. Temperatursensoren registrerer, at rummet er for koldt, og en aktuator tænder for varmen.

![Et diagram, der viser temperatur og en drejeknap som input til en IoT-enhed, og kontrol af en varmeenhed som output](../../../../../translated_images/da/basic-thermostat.a923217fd1f37e5a.webp)

Der findes et enormt udvalg af forskellige ting, der kan fungere som IoT-enheder, fra dedikeret hardware, der registrerer én ting, til generelle enheder, endda din smartphone! En smartphone kan bruge sensorer til at registrere verden omkring sig og aktuatorer til at interagere med verden - for eksempel ved at bruge en GPS-sensor til at registrere din placering og en højttaler til at give dig navigationsinstruktioner til en destination.

✅ Tænk på andre systemer, du har omkring dig, der læser data fra en sensor og bruger det til at træffe beslutninger. Et eksempel kunne være termostaten i en ovn. Kan du finde flere?

### Internettet

**Internet**-delen af en IoT-applikation består af applikationer, som IoT-enheden kan forbinde til for at sende og modtage data, samt andre applikationer, der kan behandle data fra IoT-enheden og hjælpe med at træffe beslutninger om, hvilke anmodninger der skal sendes til IoT-enhedens aktuatorer.

En typisk opsætning kunne være at have en slags cloud-tjeneste, som IoT-enheden forbinder til, og denne cloud-tjeneste håndterer ting som sikkerhed, modtager beskeder fra IoT-enheden og sender beskeder tilbage til enheden. Denne cloud-tjeneste ville derefter forbinde til andre applikationer, der kan behandle eller gemme sensordata, eller bruge sensordata sammen med data fra andre systemer til at træffe beslutninger.

Enheder forbinder heller ikke altid direkte til internettet via WiFi eller kabelforbindelser. Nogle enheder bruger mesh-netværk til at tale med hinanden via teknologier som Bluetooth, og forbinder via en hub-enhed, der har en internetforbindelse.

Med eksemplet med en smart termostat ville termostaten forbinde via hjemmets WiFi til en cloud-tjeneste, der kører i skyen. Den ville sende temperaturdata til denne cloud-tjeneste, og derfra ville dataene blive skrevet til en slags database, der gør det muligt for husejeren at tjekke aktuelle og tidligere temperaturer via en telefonapp. En anden tjeneste i skyen ville vide, hvilken temperatur husejeren ønsker, og sende beskeder tilbage til IoT-enheden via cloud-tjenesten for at fortælle varmesystemet, om det skal tændes eller slukkes.

![Et diagram, der viser temperatur og en drejeknap som input til en IoT-enhed, IoT-enheden med tovejskommunikation til skyen, som igen har tovejskommunikation til en telefon, og kontrol af en varmeenhed som output fra IoT-enheden](../../../../../translated_images/da/mobile-controlled-thermostat.4a994010473d8d6a.webp)

En endnu smartere version kunne bruge AI i skyen med data fra andre sensorer, der er forbundet til andre IoT-enheder, såsom bevægelsessensorer, der registrerer, hvilke rum der er i brug, samt data som vejr og endda din kalender, for at træffe beslutninger om, hvordan temperaturen skal indstilles på en intelligent måde. For eksempel kunne den slukke for varmen, hvis den læser fra din kalender, at du er på ferie, eller slukke for varmen rum for rum afhængigt af, hvilke rum du bruger, og lære af dataene for at blive mere og mere præcis over tid.

![Et diagram, der viser flere temperatursensorer og en drejeknap som input til en IoT-enhed, IoT-enheden med tovejskommunikation til skyen, som igen har tovejskommunikation til en telefon, en kalender og en vejrtjeneste, og kontrol af en varmeenhed som output fra IoT-enheden](../../../../../translated_images/da/smarter-thermostat.a75855f15d2d9e63.webp)

✅ Hvilke andre data kunne hjælpe med at gøre en internetforbundet termostat smartere?

### IoT på kanten

Selvom I'et i IoT står for Internet, behøver disse enheder ikke at være forbundet til internettet. I nogle tilfælde kan enheder forbinde til 'edge'-enheder - gateway-enheder, der kører på dit lokale netværk, hvilket betyder, at du kan behandle data uden at lave et opkald over internettet. Dette kan være hurtigere, når du har mange data eller en langsom internetforbindelse, det giver dig mulighed for at køre offline, hvor internetforbindelse ikke er mulig, såsom på et skib eller i et katastrofeområde, når du reagerer på en humanitær krise, og det giver dig mulighed for at holde data private. Nogle enheder vil indeholde behandlingskode, der er oprettet ved hjælp af cloud-værktøjer, og køre dette lokalt for at indsamle og reagere på data uden at bruge en internetforbindelse til at træffe en beslutning.

Et eksempel på dette er en smart hjemmeenhed såsom en Apple HomePod, Amazon Alexa eller Google Home, som vil lytte til din stemme ved hjælp af AI-modeller, der er trænet i skyen, men som kører lokalt på enheden. Disse enheder vil 'vågne op', når et bestemt ord eller en sætning bliver sagt, og først derefter sende din tale over internettet til behandling. Enheden vil stoppe med at sende tale på et passende tidspunkt, såsom når den registrerer en pause i din tale. Alt, hvad du siger før du vækker enheden med vækkeordet, og alt, hvad du siger efter enheden er stoppet med at lytte, vil ikke blive sendt over internettet til enhedens udbyder og vil derfor være privat.

✅ Tænk på andre scenarier, hvor privatliv er vigtigt, så behandling af data ville være bedre udført på kanten frem for i skyen. Som et hint - tænk på IoT-enheder med kameraer eller andre billedbehandlingsenheder.

### IoT-sikkerhed

Med enhver internetforbindelse er sikkerhed en vigtig overvejelse. Der er en gammel joke, der siger, at 'S'et i IoT står for sikkerhed' - der er intet 'S' i IoT, hvilket antyder, at det ikke er sikkert.

IoT-enheder forbinder til en cloud-tjeneste og er derfor kun så sikre som den cloud-tjeneste - hvis din cloud-tjeneste tillader enhver enhed at forbinde, kan der sendes skadelige data, eller virusangreb kan finde sted. Dette kan have meget reelle konsekvenser, da IoT-enheder interagerer og kontrollerer andre enheder. For eksempel manipulerede [Stuxnet-ormen](https://wikipedia.org/wiki/Stuxnet) ventiler i centrifuger for at beskadige dem. Hackere har også udnyttet [dårlig sikkerhed til at få adgang til babyalarmer](https://www.npr.org/sections/thetwo-way/2018/06/05/617196788/s-c-mom-says-baby-monitor-was-hacked-experts-say-many-devices-are-vulnerable) og andre hjemmeovervågningsenheder.

> 💁 Nogle gange kører IoT-enheder og edge-enheder på et netværk, der er helt isoleret fra internettet for at holde data private og sikre. Dette kaldes [air-gapping](https://wikipedia.org/wiki/Air_gap_(networking)).

## Dybere indsigt i mikrocontrollere

I den sidste lektion introducerede vi mikrocontrollere. Lad os nu se nærmere på dem.

### CPU

CPU'en er 'hjernen' i mikrocontrolleren. Det er processoren, der kører din kode og kan sende data til og modtage data fra tilsluttede enheder. CPU'er kan indeholde en eller flere kerner - i bund og grund en eller flere CPU'er, der kan arbejde sammen for at køre din kode.

CPU'er er afhængige af en clock, der tikker mange millioner eller milliarder gange i sekundet. Hver tik, eller cyklus, synkroniserer de handlinger, som CPU'en kan udføre. Ved hver tik kan CPU'en udføre en instruktion fra et program, såsom at hente data fra en ekstern enhed eller udføre en matematisk beregning. Denne regelmæssige cyklus gør det muligt for alle handlinger at blive afsluttet, før den næste instruktion behandles.

Jo hurtigere clock-cyklussen er, jo flere instruktioner kan behandles pr. sekund, og derfor jo hurtigere CPU'en er. CPU-hastigheder måles i [Hertz (Hz)](https://wikipedia.org/wiki/Hertz), en standardenhed, hvor 1 Hz betyder én cyklus eller clock-tik pr. sekund.

> 🎓 CPU-hastigheder angives ofte i MHz eller GHz. 1MHz er 1 million Hz, 1GHz er 1 milliard Hz.

> 💁 CPU'er udfører programmer ved hjælp af [fetch-decode-execute-cyklussen](https://wikipedia.org/wiki/Instruction_cycle). For hver clock-tik vil CPU'en hente den næste instruktion fra hukommelsen, afkode den og derefter udføre den, såsom at bruge en aritmetisk logisk enhed (ALU) til at lægge 2 tal sammen. Nogle udførelser vil tage flere tik at køre, så den næste cyklus vil køre ved næste tik, efter instruktionen er afsluttet.

![Fetch-decode-execute-cyklussen, der viser, hvordan fetch henter en instruktion fra programmet, der er gemt i RAM, og derefter afkoder og udfører den på en CPU](../../../../../translated_images/da/fetch-decode-execute.2fd6f150f6280392.webp)

Mikrocontrollere har meget lavere clock-hastigheder end stationære eller bærbare computere eller endda de fleste smartphones. Wio Terminal har for eksempel en CPU, der kører ved 120MHz eller 120.000.000 cyklusser pr. sekund.

✅ En gennemsnitlig PC eller Mac har en CPU med flere kerner, der kører ved flere gigahertz, hvilket betyder, at clocken tikker milliarder af gange i sekundet. Undersøg clock-hastigheden på din computer og sammenlign, hvor mange gange hurtigere den er end Wio Terminal.

Hver clock-cyklus bruger strøm og genererer varme. Jo hurtigere tik, jo mere strøm forbruges og jo mere varme genereres. PC'er har køleplader og blæsere til at fjerne varme, uden hvilke de ville overophede og lukke ned inden for få sekunder. Mikrocontrollere har ofte ingen af delene, da de kører meget køligere og derfor meget langsommere. PC'er kører på netstrøm eller store batterier i et par timer, mikrocontrollere kan køre i dage, måneder eller endda år på små batterier. Mikrocontrollere kan også have kerner, der kører ved forskellige hastigheder, og skifte til langsommere lavstrømskerner, når CPU-belastningen er lav, for at reducere strømforbruget.

> 💁 Nogle PC'er og Mac'er begynder at anvende den samme blanding af hurtige højstrømskerner og langsommere lavstrømskerner, der skifter for at spare batteri. For eksempel kan M1-chippen i de nyeste Apple-laptops skifte mellem 4 performance-kerner og 4 effektivitetskerner for at optimere batterilevetid eller hastighed afhængigt af den opgave, der udføres.

✅ Lav lidt research: Læs om CPU'er på [Wikipedia CPU-artiklen](https://wikipedia.org/wiki/Central_processing_unit)

#### Opgave

Undersøg Wio Terminal.

Hvis du bruger en Wio Terminal til disse lektioner, så prøv at finde CPU'en. Find afsnittet *Hardware Overview* på [Wio Terminal-produktets side](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) for et billede af de interne dele, og prøv at finde CPU'en gennem det klare plastvindue på bagsiden.

### Hukommelse

Mikrocontrollere har normalt to typer hukommelse - programhukommelse og random-access memory (RAM).

Programhukommelse er ikke-flygtig, hvilket betyder, at det, der er skrevet til den, forbliver, når der ikke er strøm til enheden. Dette er hukommelsen, der gemmer din programkode.

RAM er den hukommelse, der bruges af programmet til at køre, og indeholder variabler, der er tildelt af dit program, og data, der er indsamlet fra perifere enheder. RAM er flygtig, og når strømmen går ud, går indholdet tabt, hvilket effektivt nulstiller dit program.
🎓 Programhukommelse gemmer din kode og forbliver, selv når der ikke er strøm.
🎓 RAM bruges til at køre dit program og nulstilles, når der ikke er strøm

Ligesom med CPU'en er hukommelsen i en mikrocontroller mange gange mindre end i en PC eller Mac. En typisk PC kan have 8 Gigabyte (GB) RAM, eller 8.000.000.000 bytes, hvor hver byte har plads nok til at gemme et enkelt bogstav eller et tal fra 0-255. En mikrocontroller har derimod kun kilobytes (KB) RAM, hvor en kilobyte er 1.000 bytes. Wio-terminalen, der er nævnt ovenfor, har 192KB RAM, eller 192.000 bytes - mere end 40.000 gange mindre end en gennemsnitlig PC!

Diagrammet nedenfor viser den relative størrelsesforskel mellem 192KB og 8GB - den lille prik i midten repræsenterer 192KB.

![En sammenligning mellem 192KB og 8GB - mere end 40.000 gange større](../../../../../translated_images/da/ram-comparison.6beb73541b42ac6f.webp)

Programlagring er også mindre end på en PC. En typisk PC kan have en harddisk på 500GB til programlagring, mens en mikrocontroller måske kun har kilobytes eller måske et par megabytes (MB) lagerplads (1MB er 1.000KB, eller 1.000.000 bytes). Wio-terminalen har 4MB programlagring.

✅ Lav lidt research: Hvor meget RAM og lagerplads har den computer, du bruger til at læse dette? Hvordan sammenlignes det med en mikrocontroller?

### Input/Output

Mikrocontrollere har brug for input- og outputforbindelser (I/O) til at læse data fra sensorer og sende styresignaler til aktuatorer. De indeholder normalt et antal generelle input/output (GPIO)-pins. Disse pins kan konfigureres i software til at være input (dvs. de modtager et signal) eller output (de sender et signal).

🧠⬅️ Input-pins bruges til at læse værdier fra sensorer

🧠➡️ Output-pins sender instruktioner til aktuatorer

✅ Du vil lære mere om dette i en senere lektion.

#### Opgave

Undersøg Wio-terminalen.

Hvis du bruger en Wio-terminal til disse lektioner, så find GPIO-pinsene. Find sektionen *Pinout diagram* på [Wio Terminal produktets side](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) for at lære, hvilke pins der er hvilke. Wio-terminalen leveres med et klistermærke, som du kan sætte på bagsiden med pin-numre, så sæt det på nu, hvis du ikke allerede har gjort det.

### Fysisk størrelse

Mikrocontrollere er typisk små i størrelse, hvor den mindste, en [Freescale Kinetis KL03 MCU, er lille nok til at passe i fordybningen af en golfbold](https://www.edn.com/tiny-arm-cortex-m0-based-mcu-shrinks-package/). Bare CPU'en i en PC kan måle 40mm x 40mm, og det er uden at inkludere køleplader og blæsere, der er nødvendige for at sikre, at CPU'en kan køre i mere end et par sekunder uden at overophede, hvilket gør den væsentligt større end en komplet mikrocontroller. Wio-terminalens udviklingskit med en mikrocontroller, et kabinet, en skærm og en række forbindelser og komponenter er ikke meget større end en bar Intel i9 CPU og væsentligt mindre end CPU'en med en køleplade og blæser!

| Enhed                           | Størrelse              |
| ------------------------------- | ---------------------- |
| Freescale Kinetis KL03          | 1,6mm x 2mm x 1mm      |
| Wio-terminal                    | 72mm x 57mm x 12mm     |
| Intel i9 CPU, køleplade og blæser | 136mm x 145mm x 103mm |

### Frameworks og operativsystemer

På grund af deres lave hastighed og hukommelsesstørrelse kører mikrocontrollere ikke et operativsystem (OS) i den forstand, som vi kender det fra desktops. Operativsystemet, der får din computer til at køre (Windows, Linux eller macOS), kræver meget hukommelse og processorkraft for at udføre opgaver, der er helt unødvendige for en mikrocontroller. Husk, at mikrocontrollere normalt er programmeret til at udføre en eller flere meget specifikke opgaver, i modsætning til en generel computer som en PC eller Mac, der skal understøtte en brugergrænseflade, afspille musik eller film, give værktøjer til at skrive dokumenter eller kode, spille spil eller surfe på internettet.

For at programmere en mikrocontroller uden et OS har du brug for nogle værktøjer, der gør det muligt at bygge din kode på en måde, som mikrocontrolleren kan køre, ved hjælp af API'er, der kan kommunikere med eventuelle perifere enheder. Hver mikrocontroller er forskellig, så producenter understøtter normalt standardframeworks, der giver dig mulighed for at følge en standard 'opskrift' for at bygge din kode og få den til at køre på enhver mikrocontroller, der understøtter det framework.

Du kan programmere mikrocontrollere ved hjælp af et OS - ofte kaldet et realtidsoperativsystem (RTOS), da disse er designet til at håndtere dataudveksling med perifere enheder i realtid. Disse operativsystemer er meget lette og tilbyder funktioner som:

* Multitråding, der gør det muligt for din kode at køre mere end én kodeblok på samme tid, enten på flere kerner eller ved at tage ture på én kerne
* Netværk, der gør det muligt at kommunikere sikkert over internettet
* Grafiske brugergrænsefladekomponenter (GUI) til at bygge brugergrænseflader (UI) på enheder med skærme.

✅ Læs om nogle forskellige RTOS'er: [Azure RTOS](https://azure.microsoft.com/services/rtos/?WT.mc_id=academic-17441-jabenn), [FreeRTOS](https://www.freertos.org), [Zephyr](https://www.zephyrproject.org)

#### Arduino

![Arduino-logoet](../../../../../images/arduino-logo.svg)

[Arduino](https://www.arduino.cc) er sandsynligvis det mest populære mikrocontroller-framework, især blandt studerende, hobbyister og gør-det-selv-entusiaster. Arduino er en open source elektronikplatform, der kombinerer software og hardware. Du kan købe Arduino-kompatible boards fra Arduino selv eller fra andre producenter og derefter kode ved hjælp af Arduino-frameworket.

Arduino-boards programmeres i C eller C++. Brug af C/C++ gør det muligt at kompilere din kode meget lille og køre hurtigt, hvilket er nødvendigt på en begrænset enhed som en mikrocontroller. Kernen i en Arduino-applikation kaldes en sketch og er C/C++-kode med 2 funktioner - `setup` og `loop`. Når boardet starter op, vil Arduino-frameworket køre `setup`-funktionen én gang, og derefter vil det køre `loop`-funktionen igen og igen, kontinuerligt, indtil strømmen slukkes.

Du vil skrive din opsætningskode i `setup`-funktionen, såsom at oprette forbindelse til WiFi og cloud-tjenester eller initialisere pins til input og output. Din loop-kode vil derefter indeholde behandlingskode, såsom at læse fra en sensor og sende værdien til skyen. Du vil normalt inkludere en forsinkelse i hver loop, for eksempel hvis du kun vil sende sensordata hvert 10. sekund, vil du tilføje en forsinkelse på 10 sekunder i slutningen af loopen, så mikrocontrolleren kan sove og spare strøm, og derefter køre loopen igen, når det er nødvendigt 10 sekunder senere.

![En Arduino-sketch, der kører setup først og derefter kører loop gentagne gange](../../../../../translated_images/da/arduino-sketch.79590cb837ff7a7c.webp)

✅ Denne programarkitektur kaldes en *event loop* eller *message loop*. Mange applikationer bruger dette under motorhjelmen og er standarden for de fleste desktop-applikationer, der kører på OS'er som Windows, macOS eller Linux. `loop` lytter efter beskeder fra brugergrænsefladekomponenter som knapper eller enheder som tastaturet og reagerer på dem. Du kan læse mere i denne [artikel om event loops](https://wikipedia.org/wiki/Event_loop).

Arduino tilbyder standardbiblioteker til at interagere med mikrocontrollere og I/O-pins, med forskellige implementeringer under motorhjelmen for at køre på forskellige mikrocontrollere. For eksempel vil [`delay`-funktionen](https://www.arduino.cc/reference/en/language/functions/time/delay/) pause programmet i en given periode, og [`digitalRead`-funktionen](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/) vil læse en værdi af `HIGH` eller `LOW` fra den givne pin, uanset hvilket board koden kører på. Disse standardbiblioteker betyder, at Arduino-kode skrevet til ét board kan genkompileres til ethvert andet Arduino-board og vil køre, forudsat at pinsene er de samme, og at boardene understøtter de samme funktioner.

Der er et stort økosystem af tredjeparts Arduino-biblioteker, der giver dig mulighed for at tilføje ekstra funktioner til dine Arduino-projekter, såsom at bruge sensorer og aktuatorer eller oprette forbindelse til cloud IoT-tjenester.

##### Opgave

Undersøg Wio-terminalen.

Hvis du bruger en Wio-terminal til disse lektioner, så genlæs den kode, du skrev i den sidste lektion. Find `setup`- og `loop`-funktionen. Overvåg den serielle output for at se, at `loop`-funktionen kaldes gentagne gange. Prøv at tilføje kode til `setup`-funktionen for at skrive til den serielle port, og observer, at denne kode kun kaldes én gang hver gang, du genstarter. Prøv at genstarte din enhed med tænd/sluk-knappen på siden for at vise, at dette kaldes hver gang enheden genstarter.

## Dybdegående kig på enkeltkortcomputere

I den sidste lektion introducerede vi enkeltkortcomputere. Lad os nu kigge nærmere på dem.

### Raspberry Pi

![Raspberry Pi-logoet](../../../../../translated_images/da/raspberry-pi-logo.4efaa16605cee054.webp)

[Raspberry Pi Foundation](https://www.raspberrypi.org) er en velgørenhedsorganisation fra Storbritannien, der blev grundlagt i 2009 for at fremme studiet af datalogi, især på skoleplan. Som en del af denne mission udviklede de en enkeltkortcomputer, kaldet Raspberry Pi. Raspberry Pi fås i øjeblikket i 3 varianter - en fuld størrelse version, den mindre Pi Zero og en compute-modul, der kan bygges ind i din endelige IoT-enhed.

![En Raspberry Pi 4](../../../../../translated_images/da/raspberry-pi-4.fd4590d308c3d456.webp)

Den nyeste iteration af den fulde størrelse Raspberry Pi er Raspberry Pi 4B. Den har en quad-core (4 kerner) CPU, der kører ved 1,5GHz, 2, 4 eller 8GB RAM, gigabit ethernet, WiFi, 2 HDMI-porte, der understøtter 4k-skærme, en lyd- og kompositvideo-udgangsport, USB-porte (2 USB 2.0, 2 USB 3.0), 40 GPIO-pins, en kameraforbindelse til et Raspberry Pi-kameramodul og en SD-kortplads. Alt dette på et board, der måler 88mm x 58mm x 19,5mm og drives af en 3A USB-C strømforsyning. Disse starter ved US$35, hvilket er meget billigere end en PC eller Mac.

> 💁 Der findes også en Pi400 alt-i-en-computer med en Pi4 indbygget i et tastatur.

![En Raspberry Pi Zero](../../../../../translated_images/da/raspberry-pi-zero.f7a4133e1e7d54bb.webp)

Pi Zero er meget mindre og har lavere strømforbrug. Den har en enkeltkerne 1GHz CPU, 512MB RAM, WiFi (i Zero W-modellen), en enkelt HDMI-port, en mikro-USB-port, 40 GPIO-pins, en kameraforbindelse til et Raspberry Pi-kameramodul og en SD-kortplads. Den måler 65mm x 30mm x 5mm og bruger meget lidt strøm. Zero koster US$5, mens W-versionen med WiFi koster US$10.

> 🎓 CPU'erne i begge disse er ARM-processorer, i modsætning til Intel/AMD x86 eller x64 processorer, som du finder i de fleste PC'er og Mac'er. Disse ligner de CPU'er, du finder i nogle mikrocontrollere, såvel som næsten alle mobiltelefoner, Microsoft Surface X og de nye Apple Silicon-baserede Apple Mac'er.

Alle varianter af Raspberry Pi kører en version af Debian Linux kaldet Raspberry Pi OS. Dette fås som en let version uden desktop, hvilket er perfekt til 'headless'-projekter, hvor du ikke har brug for en skærm, eller en fuld version med et komplet desktopmiljø, inklusive webbrowser, kontorapplikationer, kodningsværktøjer og spil. Da operativsystemet er en version af Debian Linux, kan du installere enhver applikation eller værktøj, der kører på Debian og er bygget til ARM-processoren i Pi.

#### Opgave

Undersøg Raspberry Pi.

Hvis du bruger en Raspberry Pi til disse lektioner, så læs om de forskellige hardwarekomponenter på boardet.

* Du kan finde detaljer om processorerne, der bruges, på [Raspberry Pi hardware dokumentationssiden](https://www.raspberrypi.org/documentation/hardware/raspberrypi/). Læs om processoren, der bruges i den Pi, du bruger.
* Find GPIO-pinsene. Læs mere om dem på [Raspberry Pi GPIO dokumentationen](https://www.raspberrypi.org/documentation/hardware/raspberrypi/gpio/README.md). Brug [GPIO Pin Usage guide](https://www.raspberrypi.org/documentation/usage/gpio/README.md) til at identificere de forskellige pins på din Pi.

### Programmering af enkeltkortcomputere

Enkeltkortcomputere er fulde computere, der kører et fuldt operativsystem. Dette betyder, at der er et bredt udvalg af programmeringssprog, frameworks og værktøjer, du kan bruge til at kode dem, i modsætning til mikrocontrollere, der er afhængige af understøttelse af boardet i frameworks som Arduino. De fleste programmeringssprog har biblioteker, der kan få adgang til GPIO-pins for at sende og modtage data fra sensorer og aktuatorer.

✅ Hvilke programmeringssprog er du bekendt med? Understøttes de på Linux?

Det mest almindelige programmeringssprog til at bygge IoT-applikationer på en Raspberry Pi er Python. Der er et stort økosystem af hardware designet til Pi, og næsten alle disse inkluderer den nødvendige kode for at bruge dem som Python-biblioteker. Nogle af disse økosystemer er baseret på 'hats' - såkaldte, fordi de sidder oven på Pi som en hat og forbinder med en stor sokkel til de 40 GPIO-pins. Disse hats giver ekstra funktioner, såsom skærme, sensorer, fjernstyrede biler eller adaptere, der gør det muligt at tilslutte sensorer med standardiserede kabler.
### Brug af single-board computere i professionelle IoT-implementeringer

Single-board computere bruges til professionelle IoT-implementeringer, ikke kun som udviklingskits. De kan være en kraftfuld måde at styre hardware og udføre komplekse opgaver, såsom at køre maskinlæringsmodeller. For eksempel findes der en [Raspberry Pi 4 compute module](https://www.raspberrypi.org/blog/raspberry-pi-compute-module-4/), som tilbyder al kraften fra en Raspberry Pi 4, men i en kompakt og billigere formfaktor uden de fleste porte, designet til at blive installeret i specialtilpasset hardware.

---

## 🚀 Udfordring

Udfordringen i den sidste lektion var at liste så mange IoT-enheder som muligt, der findes i dit hjem, skole eller arbejdsplads. For hver enhed på denne liste, tror du, de er bygget omkring mikrocontrollere eller single-board computere, eller måske en blanding af begge dele?

## Quiz efter lektionen

[Quiz efter lektionen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/4)

## Gennemgang & Selvstudie

* Læs [Arduino introduktionsguide](https://www.arduino.cc/en/Guide/Introduction) for at forstå mere om Arduino-platformen.
* Læs [introduktionen til Raspberry Pi 4](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/) for at lære mere om Raspberry Pis.
* Lær mere om nogle af begreberne og akronymerne i [What the FAQ are CPUs, MPUs, MCUs, and GPUs artikel i Electrical Engineering Journal](https://www.eejournal.com/article/what-the-faq-are-cpus-mpus-mcus-and-gpus/).

✅ Brug disse guides sammen med de viste omkostninger ved at følge linkene i [hardwareguiden](../../../hardware.md) for at beslutte, hvilken hardwareplatform du vil bruge, eller om du hellere vil bruge en virtuel enhed.

## Opgave

[Sammenlign og kontraster mikrocontrollere og single-board computere](assignment.md)

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på at sikre nøjagtighed, skal det bemærkes, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.