# Introduktion til IoT

![En sketchnote oversigt over denne lektion](../../../../../translated_images/da/lesson-1.2606670fa61ee904.webp)

> Sketchnote af [Nitya Narasimhan](https://github.com/nitya). Klik på billedet for en større version.

Denne lektion blev undervist som en del af [Hello IoT-serien](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) fra [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Lektionen blev præsenteret i 2 videoer - en 1-times lektion og en 1-times spørgetime, hvor dele af lektionen blev uddybet, og spørgsmål blev besvaret.

[![Lektion 1: Introduktion til IoT](https://img.youtube.com/vi/bVFfcYh6UBw/0.jpg)](https://youtu.be/bVFfcYh6UBw)

[![Lektion 1: Introduktion til IoT - Spørgetime](https://img.youtube.com/vi/YI772q5v3yI/0.jpg)](https://youtu.be/YI772q5v3yI)

> 🎥 Klik på billederne ovenfor for at se videoerne

## Quiz før lektionen

[Quiz før lektionen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/1)

## Introduktion

Denne lektion dækker nogle af de grundlæggende emner omkring Internet of Things og hjælper dig med at komme i gang med at opsætte din hardware.

I denne lektion vil vi gennemgå:

* [Hvad er 'Internet of Things'?](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [IoT-enheder](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Opsæt din enhed](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Anvendelser af IoT](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Eksempler på IoT-enheder omkring dig](../../../../../1-getting-started/lessons/1-introduction-to-iot)

## Hvad er 'Internet of Things'?

Begrebet 'Internet of Things' blev opfundet af [Kevin Ashton](https://wikipedia.org/wiki/Kevin_Ashton) i 1999 for at beskrive forbindelsen mellem internettet og den fysiske verden via sensorer. Siden da er begrebet blevet brugt til at beskrive enhver enhed, der interagerer med den fysiske verden omkring den, enten ved at indsamle data fra sensorer eller ved at levere interaktioner i den virkelige verden via aktuatorer (enheder, der udfører handlinger som at tænde en kontakt eller lyse en LED), ofte forbundet med andre enheder eller internettet.

> **Sensorer** indsamler information fra verden, såsom måling af hastighed, temperatur eller placering.
>
> **Aktuatorer** konverterer elektriske signaler til interaktioner i den virkelige verden, såsom at aktivere en kontakt, tænde lys, lave lyde eller sende kontrolsignaler til andet hardware, for eksempel for at tænde en stikkontakt.

IoT som teknologiområde er mere end bare enheder - det inkluderer cloud-baserede tjenester, der kan behandle sensordata eller sende anmodninger til aktuatorer forbundet med IoT-enheder. Det inkluderer også enheder, der ikke har eller ikke behøver internetforbindelse, ofte kaldet edge-enheder. Disse enheder kan selv behandle og reagere på sensordata, normalt ved hjælp af AI-modeller, der er trænet i skyen.

IoT er et hurtigt voksende teknologiområde. Det anslås, at der ved udgangen af 2020 var 30 milliarder IoT-enheder implementeret og forbundet til internettet. Ser vi fremad, anslås det, at IoT-enheder i 2025 vil indsamle næsten 80 zettabytes data eller 80 billioner gigabytes. Det er en enorm mængde data!

![En graf, der viser aktive IoT-enheder over tid, med en opadgående tendens fra under 5 milliarder i 2015 til over 30 milliarder i 2025](../../../../../images/connected-iot-devices.svg)

✅ Lav lidt research: Hvor meget af de data, der genereres af IoT-enheder, bliver faktisk brugt, og hvor meget går til spilde? Hvorfor bliver så mange data ignoreret?

Disse data er nøglen til IoT's succes. For at blive en succesfuld IoT-udvikler skal du forstå, hvilke data du skal indsamle, hvordan du indsamler dem, hvordan du træffer beslutninger baseret på dem, og hvordan du bruger disse beslutninger til at interagere med den fysiske verden, hvis det er nødvendigt.

## IoT-enheder

**T** i IoT står for **Things** - enheder, der interagerer med den fysiske verden omkring dem, enten ved at indsamle data fra sensorer eller levere interaktioner i den virkelige verden via aktuatorer.

Enheder til produktion eller kommerciel brug, såsom fitness-trackere til forbrugere eller industrielle maskinstyringer, er normalt specialfremstillede. De bruger skræddersyede kredsløb, måske endda specialdesignede processorer, der er designet til at opfylde behovene for en bestemt opgave, hvad enten det er at være lille nok til at passe på et håndled eller robust nok til at fungere i et miljø med høj temperatur, højt stress eller høj vibration.

Som udvikler, der enten lærer om IoT eller skaber en prototype, skal du starte med et udviklersæt. Disse er generelle IoT-enheder designet til udviklere, ofte med funktioner, som du ikke ville have på en produktionsenhed, såsom eksterne pins til at forbinde sensorer eller aktuatorer, hardware til debugging eller ekstra ressourcer, der ville tilføje unødvendige omkostninger ved masseproduktion.

Disse udviklersæt falder normalt i to kategorier - mikrocontrollere og single-board computere. Disse vil blive introduceret her, og vi vil gå mere i detaljer i den næste lektion.

> 💁 Din telefon kan også betragtes som en generel IoT-enhed med indbyggede sensorer og aktuatorer, hvor forskellige apps bruger sensorer og aktuatorer på forskellige måder med forskellige cloud-tjenester. Du kan endda finde nogle IoT-tutorials, der bruger en telefonapp som en IoT-enhed.

### Mikrocontrollere

En mikrocontroller (ofte kaldet MCU, kort for microcontroller unit) er en lille computer bestående af:

🧠 En eller flere centralenheder (CPU'er) - mikrocontrollerens 'hjerne', der kører dit program

💾 Hukommelse (RAM og programhukommelse) - hvor dit program, data og variabler gemmes

🔌 Programmerbare input/output (I/O) forbindelser - til at kommunikere med eksterne enheder (tilsluttede enheder) såsom sensorer og aktuatorer

Mikrocontrollere er typisk lavpris computerenheder, med gennemsnitspriser for dem, der bruges i specialfremstillet hardware, der falder til omkring US$0.50, og nogle enheder så billige som US$0.03. Udviklersæt kan starte så lavt som US$4, med omkostninger, der stiger, når du tilføjer flere funktioner. [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html), et mikrocontroller-udviklersæt fra [Seeed studios](https://www.seeedstudio.com), der har sensorer, aktuatorer, WiFi og en skærm, koster omkring US$30.

![En Wio Terminal](../../../../../translated_images/da/wio-terminal.b8299ee16587db9a.webp)

> 💁 Når du søger på internettet efter mikrocontrollere, skal du være opmærksom på at søge efter termen **MCU**, da dette vil give mange resultater for Marvel Cinematic Universe, ikke mikrocontrollere.

Mikrocontrollere er designet til at blive programmeret til at udføre et begrænset antal meget specifikke opgaver, snarere end at være generelle computere som PC'er eller Mac'er. Bortset fra meget specifikke scenarier kan du ikke tilslutte en skærm, tastatur og mus og bruge dem til generelle opgaver.

Udviklersæt til mikrocontrollere kommer normalt med ekstra sensorer og aktuatorer ombord. De fleste boards vil have en eller flere LED'er, du kan programmere, sammen med andre enheder såsom standardstik til at tilføje flere sensorer eller aktuatorer ved hjælp af forskellige producenters økosystemer eller indbyggede sensorer (normalt de mest populære som temperatursensorer). Nogle mikrocontrollere har indbygget trådløs forbindelse såsom Bluetooth eller WiFi eller har ekstra mikrocontrollere på boardet for at tilføje denne forbindelse.

> 💁 Mikrocontrollere programmeres normalt i C/C++.

### Single-board computere

En single-board computer er en lille computerenhed, der har alle elementerne i en komplet computer samlet på et enkelt lille board. Disse enheder har specifikationer, der minder om en desktop eller laptop PC eller Mac, kører et fuldt operativsystem, men er små, bruger mindre strøm og er betydeligt billigere.

![En Raspberry Pi 4](../../../../../translated_images/da/raspberry-pi-4.fd4590d308c3d456.webp)

Raspberry Pi er en af de mest populære single-board computere.

Ligesom en mikrocontroller har single-board computere en CPU, hukommelse og input/output pins, men de har ekstra funktioner såsom en grafikchip, der gør det muligt at tilslutte skærme, lydudgange og USB-porte til at tilslutte tastaturer, mus og andre standard USB-enheder som webcams eller eksterne lagringsenheder. Programmer gemmes på SD-kort eller harddiske sammen med et operativsystem, i stedet for en hukommelseschip indbygget i boardet.

> 🎓 Du kan tænke på en single-board computer som en mindre, billigere version af den PC eller Mac, du læser dette på, med tilføjelsen af GPIO (general-purpose input/output) pins til at interagere med sensorer og aktuatorer.

Single-board computere er fuldt udstyrede computere, så de kan programmeres i ethvert sprog. IoT-enheder programmeres typisk i Python.

### Hardwarevalg til resten af lektionerne

Alle de efterfølgende lektioner inkluderer opgaver, der bruger en IoT-enhed til at interagere med den fysiske verden og kommunikere med skyen. Hver lektion understøtter 3 hardwarevalg - Arduino (ved hjælp af en Seeed Studios Wio Terminal) eller en single-board computer, enten en fysisk enhed (en Raspberry Pi 4) eller en virtuel single-board computer, der kører på din PC eller Mac.

Du kan læse om den hardware, der er nødvendig for at fuldføre alle opgaverne, i [hardwareguiden](../../../hardware.md).

> 💁 Du behøver ikke købe nogen IoT-hardware for at fuldføre opgaverne; du kan gøre alt ved hjælp af en virtuel single-board computer.

Hvilken hardware du vælger, afhænger af, hvad du har til rådighed enten derhjemme eller på din skole, og hvilket programmeringssprog du kender eller planlægger at lære. Begge hardwarevarianter vil bruge det samme sensor-økosystem, så hvis du starter med én vej, kan du skifte til den anden uden at skulle udskifte det meste af udstyret. Den virtuelle single-board computer vil være det samme som at lære på en Raspberry Pi, med det meste af koden overførbar til Pi'en, hvis du senere får en enhed og sensorer.

### Arduino udviklersæt

Hvis du er interesseret i at lære mikrocontroller-udvikling, kan du fuldføre opgaverne ved hjælp af en Arduino-enhed. Du skal have en grundlæggende forståelse af C/C++-programmering, da lektionerne kun vil undervise i kode, der er relevant for Arduino-frameworket, de sensorer og aktuatorer, der bruges, og de biblioteker, der interagerer med skyen.

Opgaverne vil bruge [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn) med [PlatformIO-udvidelsen til mikrocontroller-udvikling](https://platformio.org). Du kan også bruge Arduino IDE, hvis du er erfaren med dette værktøj, da der ikke vil blive givet instruktioner.

### Single-board computer udviklersæt

Hvis du er interesseret i at lære IoT-udvikling ved hjælp af single-board computere, kan du fuldføre opgaverne ved hjælp af en Raspberry Pi eller en virtuel enhed, der kører på din PC eller Mac.

Du skal have en grundlæggende forståelse af Python-programmering, da lektionerne kun vil undervise i kode, der er relevant for de sensorer og aktuatorer, der bruges, og de biblioteker, der interagerer med skyen.

> 💁 Hvis du vil lære at programmere i Python, kan du tjekke følgende to videoserier:
>
> * [Python for begyndere](https://channel9.msdn.com/Series/Intro-to-Python-Development?WT.mc_id=academic-17441-jabenn)
> * [Mere Python for begyndere](https://channel9.msdn.com/Series/More-Python-for-Beginners?WT.mc_id=academic-7372-jabenn)

Opgaverne vil bruge [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn).

Hvis du bruger en Raspberry Pi, kan du enten køre din Pi med den fulde desktopversion af Raspberry Pi OS og lave al kodning direkte på Pi'en ved hjælp af [Raspberry Pi OS-versionen af VS Code](https://code.visualstudio.com/docs/setup/raspberry-pi?WT.mc_id=academic-17441-jabenn), eller køre din Pi som en headless enhed og kode fra din PC eller Mac ved hjælp af VS Code med [Remote SSH-udvidelsen](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn), der giver dig mulighed for at forbinde til din Pi og redigere, debugge og køre kode, som om du kodede direkte på den.

Hvis du bruger den virtuelle enhedsmulighed, vil du kode direkte på din computer. I stedet for at tilgå sensorer og aktuatorer vil du bruge et værktøj til at simulere denne hardware, der leverer sensorværdier, som du kan definere, og viser resultaterne af aktuatorer på skærmen.

## Opsæt din enhed

Før du kan komme i gang med at programmere din IoT-enhed, skal du lave en lille opsætning. Følg de relevante instruktioner nedenfor afhængigt af, hvilken enhed du vil bruge.
> 💁 Hvis du endnu ikke har en enhed, kan du se [hardwareguiden](../../../hardware.md) for at få hjælp til at beslutte, hvilken enhed du vil bruge, og hvilket ekstra hardware du skal købe. Du behøver ikke at købe hardware, da alle projekterne kan køre på virtuel hardware.
Disse instruktioner inkluderer links til tredjepartswebsites fra skaberne af den hardware eller de værktøjer, du vil bruge. Dette er for at sikre, at du altid bruger de mest opdaterede instruktioner til de forskellige værktøjer og hardware.

Gennemgå den relevante vejledning for at opsætte din enhed og fuldføre et 'Hello World'-projekt. Dette vil være det første skridt i at skabe en IoT-natlampe over de 4 lektioner i denne introduktionsdel.

* [Arduino - Wio Terminal](wio-terminal.md)
* [Single-board computer - Raspberry Pi](pi.md)
* [Single-board computer - Virtuel enhed](virtual-device.md)

✅ Du vil bruge VS Code til både Arduino og single-board computere. Hvis du ikke har brugt det før, kan du læse mere om det på [VS Code-siden](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn)

## Anvendelser af IoT

IoT dækker et enormt udvalg af anvendelsesområder, fordelt på nogle brede kategorier:

* Forbruger-IoT
* Kommerciel IoT
* Industriel IoT
* Infrastruktur-IoT

✅ Lav lidt research: Find et konkret eksempel for hver af de områder, der er beskrevet nedenfor, som ikke er nævnt i teksten.

### Forbruger-IoT

Forbruger-IoT refererer til IoT-enheder, som forbrugere køber og bruger i hjemmet. Nogle af disse enheder er utroligt nyttige, såsom smarte højttalere, smarte varmesystemer og robotstøvsugere. Andre er mere tvivlsomme i deres nytte, såsom stemmestyrede vandhaner, der gør det umuligt at slukke for vandet, fordi stemmestyringen ikke kan høre dig over lyden af rindende vand.

Forbruger-IoT-enheder giver folk mulighed for at opnå mere i deres omgivelser, især de 1 milliard mennesker, der har en funktionsnedsættelse. Robotstøvsugere kan give rene gulve til personer med mobilitetsproblemer, der ikke selv kan støvsuge, stemmestyrede ovne giver personer med begrænset syn eller motorisk kontrol mulighed for at opvarme deres ovne med kun deres stemme, og sundhedsmonitorer giver patienter mulighed for at overvåge kroniske tilstande med mere regelmæssige og detaljerede opdateringer om deres helbred. Disse enheder bliver så udbredte, at selv små børn bruger dem som en del af deres daglige liv, for eksempel elever, der under COVID-pandemien satte timere på smarte hjemmeenheder for at holde styr på deres skolearbejde eller alarmer for at minde dem om kommende klassemøder.

✅ Hvilke forbruger-IoT-enheder har du på dig eller i dit hjem?

### Kommerciel IoT

Kommerciel IoT dækker brugen af IoT på arbejdspladsen. På et kontor kan der være sensorer for tilstedeværelse og bevægelsesdetektorer til at styre belysning og opvarmning, så lys og varme kun er tændt, når det er nødvendigt, hvilket reducerer omkostninger og CO2-udledning. På en fabrik kan IoT-enheder overvåge sikkerhedsrisici, såsom arbejdere, der ikke bærer sikkerhedshjelme, eller støjniveauer, der er blevet farlige. I detailhandlen kan IoT-enheder måle temperaturen i køleopbevaring og advare butiksejeren, hvis et køleskab eller en fryser er uden for det krævede temperaturområde, eller de kan overvåge varer på hylderne for at dirigere medarbejdere til at genopfylde produkter, der er blevet solgt. Transportindustrien bruger i stigende grad IoT til at overvåge køretøjers placering, spore kørte kilometer for vejafgifter, overvåge chaufførers arbejdstimer og pauser eller give besked til personalet, når et køretøj nærmer sig en terminal for at forberede lastning eller losning.

✅ Hvilke kommercielle IoT-enheder har du på din skole eller arbejdsplads?

### Industriel IoT (IIoT)

Industriel IoT, eller IIoT, er brugen af IoT-enheder til at styre og administrere maskiner i stor skala. Dette dækker en bred vifte af anvendelsesområder, fra fabrikker til digitalt landbrug.

Fabrikker bruger IoT-enheder på mange forskellige måder. Maskiner kan overvåges med flere sensorer for at spore ting som temperatur, vibration og rotationshastighed. Disse data kan derefter overvåges for at stoppe maskinen, hvis den går uden for visse tolerancer - for eksempel hvis den bliver for varm og skal slukkes. Disse data kan også indsamles og analyseres over tid for at udføre prædiktiv vedligeholdelse, hvor AI-modeller analyserer dataene op til en fejl og bruger det til at forudsige andre fejl, før de opstår.

Digitalt landbrug er vigtigt, hvis planeten skal brødføde den voksende befolkning, især de 2 milliarder mennesker i 500 millioner husstande, der lever af [subsistenslandbrug](https://wikipedia.org/wiki/Subsistence_agriculture). Digitalt landbrug kan variere fra få sensorer til få dollars til massive kommercielle opsætninger. En landmand kan starte med at overvåge temperaturer og bruge [vækstgrad-dage](https://wikipedia.org/wiki/Growing_degree-day) til at forudsige, hvornår en afgrøde vil være klar til høst. De kan forbinde jordfugtighedsmonitorer til automatiske vandingssystemer for at give deres planter så meget vand, som de har brug for, men ikke mere, for at sikre, at deres afgrøder ikke tørrer ud uden at spilde vand. Landmænd går endda videre og bruger droner, satellitdata og AI til at overvåge afgrødeudvikling, sygdomme og jordkvalitet over store områder af landbrugsjord.

✅ Hvilke andre IoT-enheder kunne hjælpe landmænd?

### Infrastruktur-IoT

Infrastruktur-IoT handler om at overvåge og styre den lokale og globale infrastruktur, som folk bruger hver dag.

[Smart Cities](https://wikipedia.org/wiki/Smart_city) er byområder, der bruger IoT-enheder til at indsamle data om byen og bruge det til at forbedre, hvordan byen fungerer. Disse byer drives normalt med samarbejder mellem lokale myndigheder, akademia og lokale virksomheder, der sporer og styrer ting som transport, parkering og forurening. For eksempel er luftforurening vigtigt for beboerne i København, Danmark, så det måles, og dataene bruges til at give information om de reneste cykel- og løberuter.

[Smart power grids](https://wikipedia.org/wiki/Smart_grid) giver bedre analyser af energibehov ved at indsamle brugsdata på niveau med individuelle hjem. Disse data kan vejlede beslutninger på landsniveau, herunder hvor nye kraftværker skal bygges, og på personligt niveau ved at give brugerne indsigt i, hvor meget strøm de bruger, hvornår de bruger den, og endda forslag til, hvordan de kan reducere omkostninger, såsom at oplade elektriske biler om natten.

✅ Hvis du kunne tilføje IoT-enheder til at måle noget der, hvor du bor, hvad skulle det være?

## Eksempler på IoT-enheder, du måske har omkring dig

Du vil blive overrasket over, hvor mange IoT-enheder du har omkring dig. Jeg skriver dette hjemmefra, og jeg har følgende enheder forbundet til internettet med smarte funktioner såsom app-styring, stemmestyring eller evnen til at sende data til mig via min telefon:

* Flere smarte højttalere
* Køleskab, opvaskemaskine, ovn og mikrobølgeovn
* Elektricitetsmonitor til solpaneler
* Smarte stik
* Videodørklokke og sikkerhedskameraer
* Smart termostat med flere smarte rumfølere
* Garageportåbner
* Hjemmeunderholdningssystemer og stemmestyrede TV'er
* Lys
* Fitness- og sundhedstrackere

Alle disse typer enheder har sensorer og/eller aktuatorer og kommunikerer med internettet. Jeg kan fra min telefon se, om min garageport er åben, og bede min smarte højttaler om at lukke den for mig. Jeg kan endda sætte den på en timer, så hvis den stadig er åben om natten, lukker den automatisk. Når min dørklokke ringer, kan jeg se fra min telefon, hvem der er der, uanset hvor jeg er i verden, og tale med dem via en højttaler og mikrofon indbygget i dørklokken. Jeg kan overvåge mit blodsukker, min puls og mine søvnmønstre og lede efter mønstre i dataene for at forbedre mit helbred. Jeg kan styre mine lys via skyen og sidde i mørke, når min internetforbindelse går ned.

---

## 🚀 Udfordring

Lav en liste over så mange IoT-enheder som muligt, der er i dit hjem, din skole eller din arbejdsplads - der er måske flere, end du tror!

## Quiz efter lektionen

[Quiz efter lektionen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/2)

## Gennemgang & Selvstudie

Læs om fordelene og fejltagelserne ved forbruger-IoT-projekter. Tjek nyhedssider for artikler om, hvornår det er gået galt, såsom privatlivsproblemer, hardwareproblemer eller problemer forårsaget af manglende forbindelse.

Nogle eksempler:

* Tjek Twitter-kontoen **[Internet of Sh*t](https://twitter.com/internetofshit)** *(advarsel om bandeord)* for nogle gode eksempler på fejltagelser med forbruger-IoT.
* [c|net - Mit Apple Watch reddede mit liv: 5 personer deler deres historier](https://www.cnet.com/news/apple-watch-lifesaving-health-features-read-5-peoples-stories/)
* [c|net - ADT-tekniker erkender sig skyldig i at have spioneret på kunders kamerafeeds i årevis](https://www.cnet.com/news/adt-home-security-technician-pleads-guilty-to-spying-on-customer-camera-feeds-for-years/) *(advarsel - ikke-samtykkebaseret voyeurisme)*

## Opgave

[Undersøg et IoT-projekt](assignment.md)

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.