<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9bae08314d8487cb76ddf3d8797e1544",
  "translation_date": "2025-08-27T21:56:23+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/README.md",
  "language_code": "no"
}
-->
# Introduksjon til IoT

![En sketchnote-oversikt over denne leksjonen](../../../../../translated_images/lesson-1.2606670fa61ee904687da5d6fa4e726639d524d064c895117da1b95b9ff6251d.no.jpg)

> Sketchnote av [Nitya Narasimhan](https://github.com/nitya). Klikk på bildet for en større versjon.

Denne leksjonen ble undervist som en del av [Hello IoT-serien](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) fra [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Leksjonen ble presentert i to videoer - en én times leksjon og en én times kontortid der man gikk dypere inn i deler av leksjonen og besvarte spørsmål.

[![Leksjon 1: Introduksjon til IoT](https://img.youtube.com/vi/bVFfcYh6UBw/0.jpg)](https://youtu.be/bVFfcYh6UBw)

[![Leksjon 1: Introduksjon til IoT - Kontortid](https://img.youtube.com/vi/YI772q5v3yI/0.jpg)](https://youtu.be/YI772q5v3yI)

> 🎥 Klikk på bildene ovenfor for å se videoene

## Quiz før leksjonen

[Quiz før leksjonen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/1)

## Introduksjon

Denne leksjonen dekker noen av de grunnleggende temaene rundt Internet of Things (IoT) og hjelper deg med å sette opp maskinvaren din.

I denne leksjonen skal vi gå gjennom:

* [Hva er 'Internet of Things'?](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [IoT-enheter](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Sett opp enheten din](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Anvendelser av IoT](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Eksempler på IoT-enheter du kanskje har rundt deg](../../../../../1-getting-started/lessons/1-introduction-to-iot)

## Hva er 'Internet of Things'?

Begrepet 'Internet of Things' ble introdusert av [Kevin Ashton](https://wikipedia.org/wiki/Kevin_Ashton) i 1999 for å beskrive koblingen mellom Internett og den fysiske verden via sensorer. Siden den gang har begrepet blitt brukt til å beskrive enhver enhet som interagerer med den fysiske verden rundt seg, enten ved å samle inn data fra sensorer eller ved å tilby interaksjoner i den virkelige verden via aktuatorer (enheter som utfører handlinger som å slå på en bryter eller tenne en LED), vanligvis koblet til andre enheter eller Internett.

> **Sensorer** samler informasjon fra verden, som å måle hastighet, temperatur eller plassering.
>
> **Aktuatorer** konverterer elektriske signaler til interaksjoner i den virkelige verden, som å utløse en bryter, slå på lys, lage lyder eller sende kontrollsignaler til annen maskinvare, for eksempel for å slå på en stikkontakt.

IoT som teknologiområde handler om mer enn bare enheter - det inkluderer skybaserte tjenester som kan behandle sensordata eller sende forespørsler til aktuatorer koblet til IoT-enheter. Det inkluderer også enheter som ikke har eller ikke trenger Internett-tilkobling, ofte referert til som edge-enheter. Dette er enheter som kan behandle og reagere på sensordata selv, vanligvis ved hjelp av AI-modeller trent i skyen.

IoT er et raskt voksende teknologiområde. Det er anslått at innen utgangen av 2020 var 30 milliarder IoT-enheter distribuert og koblet til Internett. Ser vi fremover, er det anslått at innen 2025 vil IoT-enheter samle inn nesten 80 zettabyte med data, eller 80 billioner gigabyte. Det er mye data!

![En graf som viser aktive IoT-enheter over tid, med en oppadgående trend fra under 5 milliarder i 2015 til over 30 milliarder i 2025](../../../../../images/connected-iot-devices.svg)

✅ Gjør litt research: Hvor mye av dataene generert av IoT-enheter blir faktisk brukt, og hvor mye går til spille? Hvorfor blir så mye data ignorert?

Disse dataene er nøkkelen til IoTs suksess. For å bli en vellykket IoT-utvikler må du forstå hvilke data du trenger å samle inn, hvordan du samler dem inn, hvordan du tar beslutninger basert på dem, og hvordan du bruker disse beslutningene til å interagere med den fysiske verden hvis nødvendig.

## IoT-enheter

**T** i IoT står for **Things** - enheter som interagerer med den fysiske verden rundt seg, enten ved å samle inn data fra sensorer eller ved å tilby interaksjoner i den virkelige verden via aktuatorer.

Enheter for produksjon eller kommersiell bruk, som forbruker-fitness-trackere eller industrielle maskinkontrollere, er vanligvis spesiallaget. De bruker spesialtilpassede kretskort, kanskje til og med spesialtilpassede prosessorer, designet for å møte behovene til en bestemt oppgave, enten det er å være liten nok til å passe på et håndledd eller robust nok til å fungere i et høytemperatur-, høy-stress- eller høyvibrasjonsfabrikkmiljø.

Som utvikler som enten lærer om IoT eller lager en enhetsprototype, må du starte med et utviklersett. Dette er generelle IoT-enheter designet for utviklere, ofte med funksjoner som du ikke ville hatt på en produksjonsenhet, som et sett med eksterne pinner for å koble sensorer eller aktuatorer til, maskinvare for å støtte feilsøking, eller ekstra ressurser som ville ha lagt til unødvendige kostnader ved en stor produksjonsserie.

Disse utviklersettene faller vanligvis inn i to kategorier - mikrokontrollere og enkeltkortsdatamaskiner. Disse vil bli introdusert her, og vi vil gå mer i detalj i neste leksjon.

> 💁 Telefonen din kan også betraktes som en generell IoT-enhet, med innebygde sensorer og aktuatorer, der forskjellige apper bruker sensorene og aktuatorene på forskjellige måter med forskjellige skytjenester. Du kan til og med finne noen IoT-tutorials som bruker en telefonapp som en IoT-enhet.

### Mikrokontrollere

En mikrokontroller (ofte referert til som MCU, kort for microcontroller unit) er en liten datamaskin bestående av:

🧠 En eller flere sentrale prosesseringsenheter (CPUer) - 'hjernen' til mikrokontrolleren som kjører programmet ditt

💾 Minne (RAM og programminne) - der programmet, dataene og variablene dine lagres

🔌 Programmerbare inn-/utgangsforbindelser (I/O) - for å kommunisere med eksterne enheter (tilkoblede enheter) som sensorer og aktuatorer

Mikrokontrollere er typisk lavkost-datamaskiner, med gjennomsnittspriser for de som brukes i spesialtilpasset maskinvare som faller til rundt US$0.50, og noen enheter så billige som US$0.03. Utviklersett kan starte så lavt som US$4, med kostnader som øker etter hvert som du legger til flere funksjoner. [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html), et mikrokontroller-utviklersett fra [Seeed studios](https://www.seeedstudio.com) som har sensorer, aktuatorer, WiFi og en skjerm, koster rundt US$30.

![En Wio Terminal](../../../../../translated_images/wio-terminal.b8299ee16587db9a.no.png)

> 💁 Når du søker på Internett etter mikrokontrollere, vær forsiktig med å søke etter begrepet **MCU**, da dette vil gi mange resultater for Marvel Cinematic Universe, ikke mikrokontrollere.

Mikrokontrollere er designet for å bli programmert til å utføre et begrenset antall svært spesifikke oppgaver, i stedet for å være generelle datamaskiner som PC-er eller Mac-er. Bortsett fra svært spesifikke scenarier, kan du ikke koble til en skjerm, tastatur og mus og bruke dem til generelle oppgaver.

Utviklersett for mikrokontrollere kommer vanligvis med ekstra sensorer og aktuatorer om bord. De fleste kort vil ha en eller flere LED-lys du kan programmere, sammen med andre enheter som standardplugger for å legge til flere sensorer eller aktuatorer ved hjelp av ulike produsenters økosystemer eller innebygde sensorer (vanligvis de mest populære som temperatursensorer). Noen mikrokontrollere har innebygd trådløs tilkobling som Bluetooth eller WiFi, eller har ekstra mikrokontrollere på kortet for å legge til denne tilkoblingen.

> 💁 Mikrokontrollere programmeres vanligvis i C/C++.

### Enkeltkortsdatamaskiner

En enkeltkortsdatamaskin er en liten datamaskin som har alle elementene til en komplett datamaskin samlet på et enkelt lite kort. Dette er enheter som har spesifikasjoner som ligner på en stasjonær eller bærbar PC eller Mac, kjører et fullt operativsystem, men er små, bruker mindre strøm og er betydelig billigere.

![En Raspberry Pi 4](../../../../../translated_images/raspberry-pi-4.fd4590d308c3d456.no.jpg)

Raspberry Pi er en av de mest populære enkeltkortsdatamaskinene.

Som en mikrokontroller har enkeltkortsdatamaskiner en CPU, minne og inn-/utgangspinner, men de har ekstra funksjoner som en grafikkbrikke for å koble til skjermer, lydutganger og USB-porter for å koble til tastaturer, mus og andre standard USB-enheter som webkameraer eller ekstern lagring. Programmer lagres på SD-kort eller harddisker sammen med et operativsystem, i stedet for en minnebrikke innebygd i kortet.

> 🎓 Du kan tenke på en enkeltkortsdatamaskin som en mindre, billigere versjon av PC-en eller Mac-en du leser dette på, med tillegg av GPIO (general-purpose input/output)-pinner for å interagere med sensorer og aktuatorer.

Enkeltkortsdatamaskiner er fullt utstyrte datamaskiner, så de kan programmeres i hvilket som helst språk. IoT-enheter programmeres typisk i Python.

### Maskinvarevalg for resten av leksjonene

Alle de påfølgende leksjonene inkluderer oppgaver som bruker en IoT-enhet til å interagere med den fysiske verden og kommunisere med skyen. Hver leksjon støtter tre maskinvarevalg - Arduino (ved bruk av Seeed Studios Wio Terminal), eller en enkeltkortsdatamaskin, enten en fysisk enhet (en Raspberry Pi 4) eller en virtuell enkeltkortsdatamaskin som kjører på din PC eller Mac.

Du kan lese om maskinvaren som trengs for å fullføre alle oppgavene i [maskinvareguiden](../../../hardware.md).

> 💁 Du trenger ikke å kjøpe noen IoT-maskinvare for å fullføre oppgavene, du kan gjøre alt ved hjelp av en virtuell enkeltkortsdatamaskin.

Hvilken maskinvare du velger er opp til deg - det avhenger av hva du har tilgjengelig hjemme eller på skolen, og hvilket programmeringsspråk du kan eller planlegger å lære. Begge maskinvarevariantene vil bruke det samme sensorekosystemet, så hvis du starter med én vei, kan du bytte til den andre uten å måtte erstatte mesteparten av utstyret. Den virtuelle enkeltkortsdatamaskinen vil være ekvivalent med å lære på en Raspberry Pi, med mesteparten av koden overførbar til Pi hvis du til slutt får en enhet og sensorer.

### Arduino utviklersett

Hvis du er interessert i å lære mikrokontrollerutvikling, kan du fullføre oppgavene ved hjelp av en Arduino-enhet. Du vil trenge en grunnleggende forståelse av C/C++-programmering, da leksjonene kun vil lære kode som er relevant for Arduino-rammeverket, sensorene og aktuatorene som brukes, og bibliotekene som interagerer med skyen.

Oppgavene vil bruke [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn) med [PlatformIO-utvidelsen for mikrokontrollerutvikling](https://platformio.org). Du kan også bruke Arduino IDE hvis du er erfaren med dette verktøyet, da instruksjoner ikke vil bli gitt.

### Enkeltkortsdatamaskin utviklersett

Hvis du er interessert i å lære IoT-utvikling ved hjelp av enkeltkortsdatamaskiner, kan du fullføre oppgavene ved hjelp av en Raspberry Pi eller en virtuell enhet som kjører på din PC eller Mac.

Du vil trenge en grunnleggende forståelse av Python-programmering, da leksjonene kun vil lære kode som er relevant for sensorene og aktuatorene som brukes, og bibliotekene som interagerer med skyen.

> 💁 Hvis du vil lære å programmere i Python, sjekk ut følgende to videoserier:
>
> * [Python for nybegynnere](https://channel9.msdn.com/Series/Intro-to-Python-Development?WT.mc_id=academic-17441-jabenn)
> * [Mer Python for nybegynnere](https://channel9.msdn.com/Series/More-Python-for-Beginners?WT.mc_id=academic-7372-jabenn)

Oppgavene vil bruke [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn).

Hvis du bruker en Raspberry Pi, kan du enten kjøre Pi-en din med den fullstendige desktopversjonen av Raspberry Pi OS og gjøre all koding direkte på Pi-en ved hjelp av [Raspberry Pi OS-versjonen av VS Code](https://code.visualstudio.com/docs/setup/raspberry-pi?WT.mc_id=academic-17441-jabenn), eller kjøre Pi-en som en headless-enhet og kode fra din PC eller Mac ved hjelp av VS Code med [Remote SSH-utvidelsen](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) som lar deg koble til Pi-en din og redigere, feilsøke og kjøre kode som om du kodet direkte på den.

Hvis du bruker det virtuelle enhetsalternativet, vil du kode direkte på datamaskinen din. I stedet for å få tilgang til sensorer og aktuatorer, vil du bruke et verktøy for å simulere denne maskinvaren, gi sensordata som du kan definere, og vise resultatene av aktuatorer på skjermen.

## Sett opp enheten din

Før du kan komme i gang med programmering av IoT-enheten din, må du gjøre litt oppsett. Følg de relevante instruksjonene nedenfor avhengig av hvilken enhet du skal bruke.
💁 Hvis du ikke har en enhet ennå, kan du se [hardwareguiden](../../../hardware.md) for å få hjelp til å velge hvilken enhet du skal bruke, og hvilket ekstrautstyr du eventuelt må kjøpe. Du trenger ikke å kjøpe maskinvare, da alle prosjektene kan kjøres på virtuell maskinvare.
Disse instruksjonene inkluderer lenker til tredjeparts nettsteder fra skaperne av maskinvaren eller verktøyene du vil bruke. Dette er for å sikre at du alltid bruker de mest oppdaterte instruksjonene for de ulike verktøyene og maskinvaren.

Jobb deg gjennom den relevante guiden for å sette opp enheten din og fullføre et "Hello World"-prosjekt. Dette vil være det første steget i å lage en IoT-nattlampe gjennom de fire leksjonene i denne introduksjonsdelen.

* [Arduino - Wio Terminal](wio-terminal.md)
* [Enkeltkortdatamaskin - Raspberry Pi](pi.md)
* [Enkeltkortdatamaskin - Virtuell enhet](virtual-device.md)

✅ Du vil bruke VS Code for både Arduino og enkeltkortdatamaskiner. Hvis du ikke har brukt dette før, kan du lese mer om det på [VS Code-nettstedet](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn)

## Anvendelser av IoT

IoT dekker et stort spekter av bruksområder, fordelt på noen brede grupper:

* Forbruker-IoT
* Kommersiell IoT
* Industriell IoT
* Infrastruktur-IoT

✅ Gjør litt research: For hvert av områdene beskrevet nedenfor, finn ett konkret eksempel som ikke er nevnt i teksten.

### Forbruker-IoT

Forbruker-IoT refererer til IoT-enheter som forbrukere kjøper og bruker hjemme. Noen av disse enhetene er utrolig nyttige, som smarte høyttalere, smarte varmesystemer og robotstøvsugere. Andre er mer tvilsomme når det gjelder nytteverdi, som stemmestyrte kraner som gjør at du ikke kan slå dem av fordi stemmestyringen ikke hører deg over lyden av rennende vann.

Forbruker-IoT-enheter gir folk muligheten til å oppnå mer i sine omgivelser, spesielt de 1 milliardene som har en funksjonsnedsettelse. Robotstøvsugere kan gi rene gulv til personer med mobilitetsproblemer som ikke kan støvsuge selv, stemmestyrte ovner lar personer med begrenset syn eller motorisk kontroll varme opp ovnene sine kun med stemmen, helsemålere kan la pasienter overvåke kroniske tilstander selv med mer regelmessige og detaljerte oppdateringer om tilstanden deres. Disse enhetene blir så utbredt at selv små barn bruker dem som en del av hverdagen, for eksempel elever som driver med virtuell skolegang under COVID-pandemien og setter timere på smarthjem-enheter for å holde styr på skolearbeidet eller alarmer for å minne dem om kommende klassemøter.

✅ Hvilke forbruker-IoT-enheter har du på deg eller i hjemmet ditt?

### Kommersiell IoT

Kommersiell IoT dekker bruken av IoT på arbeidsplassen. På et kontor kan det være beleggssensorer og bevegelsesdetektorer for å styre belysning og oppvarming, slik at lys og varme kun er på når det er nødvendig, noe som reduserer kostnader og karbonutslipp. På en fabrikk kan IoT-enheter overvåke sikkerhetsfarer som arbeidere som ikke bruker hjelm eller støy som har nådd farlige nivåer. I detaljhandel kan IoT-enheter måle temperaturen i kjølelager og varsle butikkansvarlig hvis et kjøleskap eller fryser er utenfor det nødvendige temperaturområdet, eller de kan overvåke varer på hyllene for å dirigere ansatte til å fylle opp produkter som er solgt. Transportindustrien bruker i økende grad IoT for å overvåke kjøretøyplasseringer, spore kjørelengde for veibruksavgifter, spore førertimer og pauser, eller varsle ansatte når et kjøretøy nærmer seg et depot for å forberede lasting eller lossing.

✅ Hvilke kommersielle IoT-enheter har du på skolen eller arbeidsplassen din?

### Industriell IoT (IIoT)

Industriell IoT, eller IIoT, er bruken av IoT-enheter for å kontrollere og administrere maskineri i stor skala. Dette dekker et bredt spekter av bruksområder, fra fabrikker til digitalt landbruk.

Fabrikker bruker IoT-enheter på mange forskjellige måter. Maskineri kan overvåkes med flere sensorer for å spore ting som temperatur, vibrasjon og rotasjonshastighet. Disse dataene kan deretter overvåkes for å stoppe maskinen hvis den går utenfor visse toleranser - for eksempel hvis den blir for varm og må stanses. Dataene kan også samles inn og analyseres over tid for å utføre prediktivt vedlikehold, der AI-modeller ser på dataene som leder opp til en feil, og bruker dette til å forutsi andre feil før de oppstår.

Digitalt landbruk er viktig hvis planeten skal kunne brødfø den voksende befolkningen, spesielt for de 2 milliardene mennesker i 500 millioner husholdninger som lever av [subsistensjordbruk](https://wikipedia.org/wiki/Subsistence_agriculture). Digitalt landbruk kan variere fra noen få sensorer til noen få dollar til massive kommersielle oppsett. En bonde kan begynne med å overvåke temperaturer og bruke [vekstgrad-dager](https://wikipedia.org/wiki/Growing_degree-day) for å forutsi når en avling vil være klar for innhøsting. De kan koble jordfuktighetsovervåking til automatiserte vanningssystemer for å gi plantene sine så mye vann som trengs, men ikke mer, for å sikre at avlingene ikke tørker ut uten å sløse med vann. Bønder tar det enda lenger og bruker droner, satellittdata og AI for å overvåke avlingsvekst, sykdom og jordkvalitet over store områder med jordbruksland.

✅ Hvilke andre IoT-enheter kan hjelpe bønder?

### Infrastruktur-IoT

Infrastruktur-IoT handler om å overvåke og kontrollere den lokale og globale infrastrukturen som folk bruker hver dag.

[Smarte byer](https://wikipedia.org/wiki/Smart_city) er urbane områder som bruker IoT-enheter for å samle inn data om byen og bruke det til å forbedre hvordan byen drives. Disse byene styres vanligvis med samarbeid mellom lokale myndigheter, akademia og lokale bedrifter, og sporer og administrerer ting som transport, parkering og forurensning. For eksempel, i København, Danmark, er luftforurensning viktig for lokalbefolkningen, så det måles og dataene brukes til å gi informasjon om de reneste sykkel- og joggerutene.

[Smarte strømnett](https://wikipedia.org/wiki/Smart_grid) gir bedre analyser av strømforbruk ved å samle inn bruksdata på nivå med individuelle hjem. Disse dataene kan veilede beslutninger på landsnivå, inkludert hvor man skal bygge nye kraftstasjoner, og på personlig nivå ved å gi brukere innsikt i hvor mye strøm de bruker, når de bruker den, og til og med forslag til hvordan de kan redusere kostnader, som å lade elektriske biler om natten.

✅ Hvis du kunne legge til IoT-enheter for å måle noe der du bor, hva ville det vært?

## Eksempler på IoT-enheter du kanskje har rundt deg

Du vil bli overrasket over hvor mange IoT-enheter du har rundt deg. Jeg skriver dette hjemmefra, og jeg har følgende enheter koblet til Internett med smarte funksjoner som appkontroll, stemmekontroll eller muligheten til å sende data til meg via telefonen:

* Flere smarte høyttalere
* Kjøleskap, oppvaskmaskin, ovn og mikrobølgeovn
* Elektrisitetsmåler for solcellepaneler
* Smarte stikkontakter
* Videodørklokke og sikkerhetskameraer
* Smart termostat med flere smarte romsensorer
* Garasjeportåpner
* Hjemmeunderholdningssystemer og stemmestyrte TV-er
* Lys
* Trenings- og helsemonitorer

Alle disse typene enheter har sensorer og/eller aktuatorer og snakker med Internett. Jeg kan se fra telefonen min om garasjeporten er åpen, og be den smarte høyttaleren min om å lukke den for meg. Jeg kan til og med sette den på en timer, slik at hvis den fortsatt er åpen om natten, vil den lukkes automatisk. Når dørklokken ringer, kan jeg se fra telefonen min hvem som er der, uansett hvor jeg er i verden, og snakke med dem via en høyttaler og mikrofon innebygd i dørklokken. Jeg kan overvåke blodsukkeret mitt, hjertefrekvensen og søvnmønstrene mine, og se etter mønstre i dataene for å forbedre helsen min. Jeg kan kontrollere lysene mine via skyen, og sitte i mørket når Internett-tilkoblingen går ned.

---

## 🚀 Utfordring

List opp så mange IoT-enheter du kan som finnes i hjemmet ditt, skolen eller arbeidsplassen din – det kan være flere enn du tror!

## Quiz etter forelesning

[Quiz etter forelesning](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/2)

## Gjennomgang og selvstudium

Les om fordelene og feilene ved forbruker-IoT-prosjekter. Sjekk nyhetssider for artikler om når det har gått galt, som personvernproblemer, maskinvareproblemer eller problemer forårsaket av manglende tilkobling.

Noen eksempler:

* Sjekk ut Twitter-kontoen **[Internet of Sh*t](https://twitter.com/internetofshit)** *(advarsel om banning)* for noen gode eksempler på feil med forbruker-IoT.
* [c|net - Min Apple Watch reddet livet mitt: 5 personer deler sine historier](https://www.cnet.com/news/apple-watch-lifesaving-health-features-read-5-peoples-stories/)
* [c|net - ADT-tekniker erklærer seg skyldig i å ha spionert på kunders kamerafeeder i årevis](https://www.cnet.com/news/adt-home-security-technician-pleads-guilty-to-spying-on-customer-camera-feeds-for-years/) *(advarsel - ikke-samtykkende voyeurisme)*

## Oppgave

[Undersøk et IoT-prosjekt](assignment.md)

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi tilstreber nøyaktighet, vennligst vær oppmerksom på at automatiske oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for eventuelle misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.