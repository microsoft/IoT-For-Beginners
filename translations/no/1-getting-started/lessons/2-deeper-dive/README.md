<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9dd7f645ad1c6f20b72fee512987f772",
  "translation_date": "2025-08-27T21:43:36+00:00",
  "source_file": "1-getting-started/lessons/2-deeper-dive/README.md",
  "language_code": "no"
}
-->
# En dypere titt på IoT

![En sketchnote-oversikt over denne leksjonen](../../../../../translated_images/no/lesson-2.324b0580d620c25e0a24fb7fddfc0b29a846dd4b82c08e7a9466d580ee78ce51.jpg)

> Sketchnote av [Nitya Narasimhan](https://github.com/nitya). Klikk på bildet for en større versjon.

Denne leksjonen ble undervist som en del av [Hello IoT-serien](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) fra [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Leksjonen ble delt opp i to videoer - en 1-times leksjon og en 1-times kontortid for å gå dypere inn i deler av leksjonen og svare på spørsmål.

[![Leksjon 2: En dypere titt på IoT](https://img.youtube.com/vi/t0SySWw3z9M/0.jpg)](https://youtu.be/t0SySWw3z9M)

[![Leksjon 2: En dypere titt på IoT - Kontortid](https://img.youtube.com/vi/tTZYf9EST1E/0.jpg)](https://youtu.be/tTZYf9EST1E)

> 🎥 Klikk på bildene ovenfor for å se videoene

## Quiz før leksjonen

[Quiz før leksjonen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/3)

## Introduksjon

Denne leksjonen går dypere inn i noen av konseptene som ble dekket i forrige leksjon.

I denne leksjonen skal vi dekke:

* [Komponenter i en IoT-applikasjon](../../../../../1-getting-started/lessons/2-deeper-dive)
* [Dypere titt på mikrokontrollere](../../../../../1-getting-started/lessons/2-deeper-dive)
* [Dypere titt på enkortsdatorer](../../../../../1-getting-started/lessons/2-deeper-dive)

## Komponenter i en IoT-applikasjon

De to hovedkomponentene i en IoT-applikasjon er *Internett* og *tingen*. La oss se nærmere på disse to komponentene.

### Tingen

![En Raspberry Pi 4](../../../../../translated_images/no/raspberry-pi-4.fd4590d308c3d456.webp)

**Tingen** i IoT refererer til en enhet som kan samhandle med den fysiske verden. Disse enhetene er vanligvis små, rimelige datamaskiner som kjører på lave hastigheter og bruker lite strøm - for eksempel enkle mikrokontrollere med kilobyte RAM (i motsetning til gigabyte i en PC) som kjører på bare noen få hundre megahertz (i motsetning til gigahertz i en PC), men som noen ganger bruker så lite strøm at de kan kjøre i uker, måneder eller til og med år på batterier.

Disse enhetene samhandler med den fysiske verden enten ved å bruke sensorer for å samle inn data fra omgivelsene eller ved å kontrollere utganger eller aktuatorer for å gjøre fysiske endringer. Et typisk eksempel på dette er en smart termostat - en enhet som har en temperatursensor, en måte å sette ønsket temperatur på, som en dreieknapp eller berøringsskjerm, og en tilkobling til et varme- eller kjølesystem som kan slås på når temperaturen som oppdages er utenfor ønsket område. Temperatursensoren oppdager at rommet er for kaldt, og en aktuator slår på varmen.

![Et diagram som viser temperatur og en dreieknapp som innganger til en IoT-enhet, og kontroll av en varmeovn som en utgang](../../../../../translated_images/no/basic-thermostat.a923217fd1f37e5a6f3390396a65c22a387419ea2dd17e518ec24315ba6ae9a8.png)

Det finnes et enormt utvalg av forskjellige ting som kan fungere som IoT-enheter, fra dedikert maskinvare som måler én ting, til generelle enheter, til og med smarttelefonen din! En smarttelefon kan bruke sensorer for å oppdage verden rundt seg og aktuatorer for å samhandle med verden - for eksempel ved å bruke en GPS-sensor for å oppdage posisjonen din og en høyttaler for å gi deg navigasjonsinstruksjoner til en destinasjon.

✅ Tenk på andre systemer du har rundt deg som leser data fra en sensor og bruker det til å ta beslutninger. Et eksempel kan være termostaten i en ovn. Kan du finne flere?

### Internett

**Internett**-delen av en IoT-applikasjon består av applikasjoner som IoT-enheten kan koble til for å sende og motta data, samt andre applikasjoner som kan behandle data fra IoT-enheten og hjelpe til med å ta beslutninger om hvilke forespørsler som skal sendes til IoT-enhetens aktuatorer.

En typisk oppsett kan være å ha en slags skytjeneste som IoT-enheten kobler seg til. Denne skytjenesten håndterer ting som sikkerhet, mottar meldinger fra IoT-enheten og sender meldinger tilbake til enheten. Denne skytjenesten kan deretter koble seg til andre applikasjoner som kan behandle eller lagre sensordata, eller bruke sensordata sammen med data fra andre systemer for å ta beslutninger.

Enheter kobler seg heller ikke alltid direkte til Internett via WiFi eller kablede tilkoblinger. Noen enheter bruker mesh-nettverk for å kommunisere med hverandre via teknologier som Bluetooth, og kobler seg til Internett via en hub-enhet.

I eksempelet med en smart termostat vil termostaten koble seg til hjemmets WiFi og en skytjeneste. Den vil sende temperaturdata til denne skytjenesten, og derfra vil dataene bli skrevet til en database som lar huseieren sjekke nåværende og tidligere temperaturer via en telefonapp. En annen tjeneste i skyen vil vite hvilken temperatur huseieren ønsker, og sende meldinger tilbake til IoT-enheten via skytjenesten for å fortelle varmesystemet om det skal slås på eller av.

![Et diagram som viser temperatur og en dreieknapp som innganger til en IoT-enhet, IoT-enheten med toveis kommunikasjon til skyen, som igjen har toveis kommunikasjon til en telefon, og kontroll av en varmeovn som en utgang fra IoT-enheten](../../../../../translated_images/no/mobile-controlled-thermostat.4a994010473d8d6a52ba68c67e5f02dc8928c717e93ca4b9bc55525aa75bbb60.png)

En enda smartere versjon kan bruke AI i skyen med data fra andre sensorer koblet til andre IoT-enheter, som bevegelsessensorer som oppdager hvilke rom som er i bruk, samt data som vær og til og med kalenderen din, for å ta beslutninger om hvordan temperaturen skal settes på en smart måte. For eksempel kan den slå av varmen hvis den leser fra kalenderen din at du er på ferie, eller slå av varmen rom for rom avhengig av hvilke rom du bruker, og lære fra dataene for å bli mer og mer nøyaktig over tid.

![Et diagram som viser flere temperatursensorer og en dreieknapp som innganger til en IoT-enhet, IoT-enheten med toveis kommunikasjon til skyen, som igjen har toveis kommunikasjon til en telefon, en kalender og en værmeldingstjeneste, og kontroll av en varmeovn som en utgang fra IoT-enheten](../../../../../translated_images/no/smarter-thermostat.a75855f15d2d9e63.webp)

✅ Hvilke andre data kan gjøre en Internett-tilkoblet termostat smartere?

### IoT på kanten

Selv om I-en i IoT står for Internett, trenger ikke disse enhetene å koble seg til Internett. I noen tilfeller kan enheter koble seg til 'edge'-enheter - gateway-enheter som kjører på ditt lokale nettverk, noe som betyr at du kan behandle data uten å måtte sende dem over Internett. Dette kan være raskere når du har mye data eller en treg Internett-tilkobling, det lar deg kjøre offline der Internett-tilkobling ikke er mulig, som på et skip eller i et katastrofeområde når du svarer på en humanitær krise, og det lar deg holde data private. Noen enheter vil inneholde prosesseringskode laget med skyverktøy og kjøre dette lokalt for å samle inn og svare på data uten å bruke en Internett-tilkobling for å ta en beslutning.

Et eksempel på dette er en smart hjemmeenhet som en Apple HomePod, Amazon Alexa eller Google Home, som vil lytte til stemmen din ved hjelp av AI-modeller trent i skyen, men som kjører lokalt på enheten. Disse enhetene vil 'våkne' når et bestemt ord eller en frase blir sagt, og først da sende talen din over Internett for behandling. Enheten vil slutte å sende tale på et passende tidspunkt, for eksempel når den oppdager en pause i talen din. Alt du sier før du vekker enheten med vekkeordet, og alt du sier etter at enheten har sluttet å lytte, vil ikke bli sendt over Internett til leverandøren av enheten, og vil derfor forbli privat.

✅ Tenk på andre scenarier der personvern er viktig, slik at behandling av data ville vært bedre gjort på kanten i stedet for i skyen. Som et hint - tenk på IoT-enheter med kameraer eller andre bildebehandlingsenheter.

### IoT-sikkerhet

Med enhver Internett-tilkobling er sikkerhet en viktig vurdering. Det er en gammel vits som sier at 'S-en i IoT står for sikkerhet' - det er ingen 'S' i IoT, noe som antyder at det ikke er sikkert.

IoT-enheter kobler seg til en skytjeneste, og er derfor bare så sikre som den skytjenesten - hvis skytjenesten din tillater at hvilken som helst enhet kobler seg til, kan ondsinnede data sendes, eller virusangrep kan finne sted. Dette kan ha svært reelle konsekvenser, ettersom IoT-enheter samhandler med og kontrollerer andre enheter. For eksempel manipulerte [Stuxnet-ormen](https://wikipedia.org/wiki/Stuxnet) ventiler i sentrifuger for å skade dem. Hackere har også utnyttet [dårlig sikkerhet for å få tilgang til babymonitorer](https://www.npr.org/sections/thetwo-way/2018/06/05/617196788/s-c-mom-says-baby-monitor-was-hacked-experts-say-many-devices-are-vulnerable) og andre overvåkingsenheter i hjemmet.

> 💁 Noen ganger kjører IoT-enheter og edge-enheter på et nettverk som er helt isolert fra Internett for å holde dataene private og sikre. Dette kalles [air-gapping](https://wikipedia.org/wiki/Air_gap_(networking)).

## Dypere titt på mikrokontrollere

I forrige leksjon introduserte vi mikrokontrollere. La oss nå se nærmere på dem.

### CPU

CPU-en er 'hjernen' i mikrokontrolleren. Det er prosessoren som kjører koden din og kan sende data til og motta data fra tilkoblede enheter. CPU-er kan inneholde én eller flere kjerner - i hovedsak én eller flere CPU-er som kan jobbe sammen for å kjøre koden din.

CPU-er er avhengige av en klokke som tikker mange millioner eller milliarder ganger i sekundet. Hvert tikk, eller syklus, synkroniserer handlingene som CPU-en kan utføre. For hvert tikk kan CPU-en utføre en instruksjon fra et program, for eksempel å hente data fra en ekstern enhet eller utføre en matematisk beregning. Denne regelmessige syklusen sørger for at alle handlinger fullføres før neste instruksjon behandles.

Jo raskere klokkesyklusen er, desto flere instruksjoner kan behandles hvert sekund, og dermed er CPU-en raskere. CPU-hastigheter måles i [Hertz (Hz)](https://wikipedia.org/wiki/Hertz), en standardenhet der 1 Hz betyr én syklus eller klokketikk per sekund.

> 🎓 CPU-hastigheter oppgis ofte i MHz eller GHz. 1MHz er 1 million Hz, 1GHz er 1 milliard Hz.

> 💁 CPU-er utfører programmer ved hjelp av [hent-dekoder-utfør-syklusen](https://wikipedia.org/wiki/Instruction_cycle). For hvert klokketikk vil CPU-en hente neste instruksjon fra minnet, dekode den, og deretter utføre den, for eksempel ved å bruke en aritmetisk logikkenhet (ALU) til å legge sammen to tall. Noen utførelser vil ta flere tikk å kjøre, så neste syklus vil kjøre ved neste tikk etter at instruksjonen er fullført.

![Hent-dekoder-utfør-syklusen som viser henting av en instruksjon fra programmet lagret i RAM, deretter dekoding og utføring på en CPU](../../../../../translated_images/no/fetch-decode-execute.2fd6f150f6280392807f4475382319abd0cee0b90058e1735444d6baa6f2078c.png)

Mikrokontrollere har mye lavere klokkehastigheter enn stasjonære eller bærbare datamaskiner, eller til og med de fleste smarttelefoner. Wio Terminal, for eksempel, har en CPU som kjører på 120MHz eller 120 000 000 sykluser per sekund.

✅ En gjennomsnittlig PC eller Mac har en CPU med flere kjerner som kjører på flere gigahertz, noe som betyr at klokken tikker milliarder av ganger i sekundet. Undersøk klokkehastigheten til datamaskinen din og sammenlign hvor mange ganger raskere den er enn Wio Terminal.

Hver klokkesyklus trekker strøm og genererer varme. Jo raskere tikkene er, desto mer strøm forbrukes og desto mer varme genereres. PC-er har kjøleribber og vifter for å fjerne varme, uten disse ville de overopphetes og slå seg av i løpet av sekunder. Mikrokontrollere har ofte ingen av delene, ettersom de kjører mye kjøligere og derfor mye saktere. PC-er kjører på strøm fra stikkontakten eller store batterier i noen timer, mens mikrokontrollere kan kjøre i dager, måneder eller til og med år på små batterier. Mikrokontrollere kan også ha kjerner som kjører på forskjellige hastigheter, og bytte til langsommere lavstrømskjerner når belastningen på CPU-en er lav for å redusere strømforbruket.

> 💁 Noen PC-er og Mac-er adopterer samme blanding av raske høyytelseskjerner og langsommere lavstrømskjerner, og bytter for å spare batteri. For eksempel kan M1-brikken i de nyeste Apple-laptopene bytte mellom 4 ytelseskjerner og 4 effektivitetskjerner for å optimalisere batterilevetid eller hastighet avhengig av oppgaven som kjøres.

✅ Gjør litt research: Les om CPU-er på [Wikipedia CPU-artikkelen](https://wikipedia.org/wiki/Central_processing_unit)

#### Oppgave

Undersøk Wio Terminal.

Hvis du bruker en Wio Terminal for disse leksjonene, prøv å finne CPU-en. Finn delen *Hardware Overview* på [Wio Terminal produktsiden](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) for et bilde av innsiden, og prøv å finne CPU-en gjennom det gjennomsiktige plastvinduet på baksiden.

### Minne

Mikrokontrollere har vanligvis to typer minne - programminne og RAM (random-access memory).

Programminne er ikke-flyktig, noe som betyr at det som er skrevet til det forblir der selv når enheten ikke har strøm. Dette er minnet som lagrer programkoden din.

RAM er minnet som brukes av programmet for å kjøre, og inneholder variabler allokert av programmet ditt og data samlet inn fra periferiutstyr. RAM er flyktig, og når strømmen går, går innholdet tapt, noe som i praksis tilbakestiller programmet ditt.
🎓 Programminne lagrer koden din og forblir intakt selv når det ikke er strøm.
🎓 RAM brukes til å kjøre programmet ditt og nullstilles når strømmen forsvinner

Akkurat som med CPU-en, er minnet på en mikrokontroller mange størrelsesordener mindre enn på en PC eller Mac. En typisk PC kan ha 8 gigabyte (GB) RAM, eller 8 000 000 000 byte, hvor hver byte har nok plass til å lagre en enkelt bokstav eller et tall fra 0-255. En mikrokontroller har derimot kun kilobyte (KB) RAM, hvor en kilobyte er 1 000 byte. Wio-terminalen som nevnes ovenfor har 192KB RAM, eller 192 000 byte – mer enn 40 000 ganger mindre enn en gjennomsnittlig PC!

Diagrammet nedenfor viser størrelsesforskjellen mellom 192KB og 8GB – den lille prikken i midten representerer 192KB.

![En sammenligning mellom 192KB og 8GB - mer enn 40 000 ganger større](../../../../../translated_images/no/ram-comparison.6beb73541b42ac6f.webp)

Programlagring er også mindre enn på en PC. En typisk PC kan ha en harddisk på 500GB for programlagring, mens en mikrokontroller kanskje bare har kilobyte eller noen få megabyte (MB) lagring (1MB er 1 000KB, eller 1 000 000 byte). Wio-terminalen har 4MB programlagring.

✅ Gjør litt research: Hvor mye RAM og lagring har datamaskinen du bruker til å lese dette? Hvordan sammenlignes dette med en mikrokontroller?

### Input/Output

Mikrokontrollere trenger inngangs- og utgangsforbindelser (I/O) for å lese data fra sensorer og sende kontrollsignaler til aktuatorer. De inneholder vanligvis et antall generelle inngangs-/utgangspinner (GPIO). Disse pinnene kan konfigureres i programvaren til å være inngang (det vil si at de mottar et signal) eller utgang (de sender et signal).

🧠⬅️ Inngangspinnene brukes til å lese verdier fra sensorer

🧠➡️ Utgangspinnene sender instruksjoner til aktuatorer

✅ Du vil lære mer om dette i en senere leksjon.

#### Oppgave

Undersøk Wio-terminalen.

Hvis du bruker en Wio-terminal for disse leksjonene, finn GPIO-pinnene. Finn delen *Pinout diagram* på [Wio Terminal-produktets nettside](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) for å lære hvilke pinner som er hvilke. Wio-terminalen leveres med et klistremerke som du kan feste på baksiden med pinnummer, så legg til dette nå hvis du ikke allerede har gjort det.

### Fysisk størrelse

Mikrokontrollere er vanligvis små i størrelse, med den minste, en [Freescale Kinetis KL03 MCU, som er liten nok til å passe i fordypningen på en golfball](https://www.edn.com/tiny-arm-cortex-m0-based-mcu-shrinks-package/). Bare CPU-en i en PC kan måle 40mm x 40mm, og det er uten å inkludere kjøleribber og vifter som trengs for å sikre at CPU-en kan kjøre i mer enn noen få sekunder uten overoppheting – betydelig større enn en komplett mikrokontroller. Wio-terminalens utviklingssett med en mikrokontroller, kabinett, skjerm og en rekke tilkoblinger og komponenter er ikke mye større enn en naken Intel i9 CPU, og betydelig mindre enn CPU-en med kjøleribbe og vifte!

| Enhet                          | Størrelse             |
| ------------------------------ | --------------------- |
| Freescale Kinetis KL03         | 1,6mm x 2mm x 1mm     |
| Wio-terminal                   | 72mm x 57mm x 12mm    |
| Intel i9 CPU, kjøleribbe og vifte | 136mm x 145mm x 103mm |

### Rammeverk og operativsystemer

På grunn av deres lave hastighet og minnestørrelse kjører ikke mikrokontrollere et operativsystem (OS) i den forstand vi kjenner fra skrivebordsmaskiner. Operativsystemet som får datamaskinen din til å fungere (Windows, Linux eller macOS) trenger mye minne og prosessorkraft for å kjøre oppgaver som er helt unødvendige for en mikrokontroller. Husk at mikrokontrollere vanligvis er programmert til å utføre én eller flere svært spesifikke oppgaver, i motsetning til en generell datamaskin som en PC eller Mac som må støtte et brukergrensesnitt, spille musikk eller filmer, tilby verktøy for å skrive dokumenter eller kode, spille spill eller surfe på Internett.

For å programmere en mikrokontroller uten et OS trenger du noen verktøy som lar deg bygge koden din på en måte som mikrokontrolleren kan kjøre, ved å bruke API-er som kan kommunisere med eventuelle periferiutstyr. Hver mikrokontroller er forskjellig, så produsenter støtter vanligvis standardrammeverk som lar deg følge en standard 'oppskrift' for å bygge koden din og få den til å kjøre på hvilken som helst mikrokontroller som støtter det rammeverket.

Du kan programmere mikrokontrollere med et OS – ofte referert til som et sanntidsoperativsystem (RTOS), da disse er designet for å håndtere sending av data til og fra periferiutstyr i sanntid. Disse operativsystemene er svært lette og gir funksjoner som:

* Multitråding, som lar koden din kjøre mer enn én kodeblokk samtidig, enten på flere kjerner eller ved å ta turer på én kjerne
* Nettverksfunksjoner for sikker kommunikasjon over Internett
* Komponenter for grafiske brukergrensesnitt (GUI) for å bygge brukergrensesnitt (UI) på enheter med skjermer.

✅ Les om noen forskjellige RTOS-er: [Azure RTOS](https://azure.microsoft.com/services/rtos/?WT.mc_id=academic-17441-jabenn), [FreeRTOS](https://www.freertos.org), [Zephyr](https://www.zephyrproject.org)

#### Arduino

![Arduino-logoen](../../../../../images/arduino-logo.svg)

[Arduino](https://www.arduino.cc) er sannsynligvis det mest populære mikrokontroller-rammeverket, spesielt blant studenter, hobbyister og skapere. Arduino er en åpen kildekode-plattform som kombinerer programvare og maskinvare. Du kan kjøpe Arduino-kompatible kort fra Arduino selv eller fra andre produsenter, og deretter kode ved hjelp av Arduino-rammeverket.

Arduino-kort programmeres i C eller C++. Bruk av C/C++ gjør at koden din kan kompileres svært liten og kjøre raskt, noe som er nødvendig på en begrenset enhet som en mikrokontroller. Kjernen i en Arduino-applikasjon kalles en sketch og er C/C++-kode med to funksjoner – `setup` og `loop`. Når kortet starter opp, vil Arduino-rammeverkskoden kjøre `setup`-funksjonen én gang, og deretter vil den kjøre `loop`-funksjonen igjen og igjen, kontinuerlig til strømmen slås av.

Du vil skrive oppstartskoden din i `setup`-funksjonen, for eksempel for å koble til WiFi og skytjenester eller initialisere pinner for inngang og utgang. Koden i `loop`-funksjonen vil deretter inneholde prosesseringskoden, for eksempel å lese fra en sensor og sende verdien til skyen. Du vil vanligvis inkludere en forsinkelse i hver loop, for eksempel hvis du bare vil sende sensordata hvert 10. sekund, legger du til en forsinkelse på 10 sekunder på slutten av loopen slik at mikrokontrolleren kan sove og spare strøm, og deretter kjøre loopen igjen når det trengs 10 sekunder senere.

![En Arduino-sketch som kjører setup først, deretter kjører loop gjentatte ganger](../../../../../translated_images/no/arduino-sketch.79590cb837ff7a7c6a68d1afda6cab83fd53d3bb1bd9a8bf2eaf8d693a4d3ea6.png)

✅ Denne programarkitekturen er kjent som en *event loop* eller *message loop*. Mange applikasjoner bruker dette i bakgrunnen og det er standarden for de fleste skrivebordsapplikasjoner som kjører på OS-er som Windows, macOS eller Linux. `loop` lytter etter meldinger fra brukergrensesnittkomponenter som knapper, eller enheter som tastaturet, og reagerer på dem. Du kan lese mer i denne [artikkelen om event loops](https://wikipedia.org/wiki/Event_loop).

Arduino tilbyr standardbiblioteker for å samhandle med mikrokontrollere og I/O-pinnene, med forskjellige implementeringer under panseret for å kjøre på forskjellige mikrokontrollere. For eksempel vil [`delay`-funksjonen](https://www.arduino.cc/reference/en/language/functions/time/delay/) pause programmet i en gitt tidsperiode, og [`digitalRead`-funksjonen](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/) vil lese en verdi av `HIGH` eller `LOW` fra den gitte pinnen, uavhengig av hvilket kort koden kjøres på. Disse standardbibliotekene betyr at Arduino-kode skrevet for ett kort kan kompileres på nytt for et annet Arduino-kort og vil kjøre, forutsatt at pinnene er de samme og kortene støtter de samme funksjonene.

Det finnes et stort økosystem av tredjeparts Arduino-biblioteker som lar deg legge til ekstra funksjoner i Arduino-prosjektene dine, som å bruke sensorer og aktuatorer eller koble til skybaserte IoT-tjenester.

##### Oppgave

Undersøk Wio-terminalen.

Hvis du bruker en Wio-terminal for disse leksjonene, les gjennom koden du skrev i forrige leksjon. Finn `setup`- og `loop`-funksjonene. Overvåk den serielle utgangen for at `loop`-funksjonen kalles gjentatte ganger. Prøv å legge til kode i `setup`-funksjonen for å skrive til den serielle porten og observer at denne koden kun kalles én gang hver gang du starter enheten på nytt. Prøv å starte enheten på nytt med strømbryteren på siden for å vise at dette kalles hver gang enheten starter på nytt.

## Dypdykk i enkortsdatorer

I forrige leksjon introduserte vi enkortsdatorer. La oss nå se nærmere på dem.

### Raspberry Pi

![Raspberry Pi-logoen](../../../../../translated_images/no/raspberry-pi-logo.4efaa16605cee054.webp)

[Raspberry Pi Foundation](https://www.raspberrypi.org) er en veldedig organisasjon fra Storbritannia som ble grunnlagt i 2009 for å fremme studiet av informatikk, spesielt på skolenivå. Som en del av dette oppdraget utviklet de en enkortsdator kalt Raspberry Pi. Raspberry Pi-er er for øyeblikket tilgjengelige i tre varianter – en full størrelse versjon, den mindre Pi Zero, og en beregningsmodul som kan bygges inn i din endelige IoT-enhet.

![En Raspberry Pi 4](../../../../../translated_images/no/raspberry-pi-4.fd4590d308c3d456.webp)

Den nyeste iterasjonen av full størrelse Raspberry Pi er Raspberry Pi 4B. Denne har en firekjerners (quad-core) CPU som kjører på 1,5GHz, 2, 4 eller 8GB RAM, gigabit ethernet, WiFi, 2 HDMI-porter som støtter 4k-skjermer, en lyd- og komposittvideoutgang, USB-porter (2 USB 2.0, 2 USB 3.0), 40 GPIO-pinner, en kamerakontakt for en Raspberry Pi-kameramodul, og en SD-kortspor. Alt dette på et kort som er 88mm x 58mm x 19,5mm og drives av en 3A USB-C strømforsyning. Disse starter på 35 USD, mye billigere enn en PC eller Mac.

> 💁 Det finnes også en Pi400, en alt-i-ett-datamaskin med en Pi4 innebygd i et tastatur.

![En Raspberry Pi Zero](../../../../../translated_images/no/raspberry-pi-zero.f7a4133e1e7d54bb.webp)

Pi Zero er mye mindre og har lavere strømforbruk. Den har en enkeltkjerne 1GHz CPU, 512MB RAM, WiFi (i Zero W-modellen), en enkelt HDMI-port, en mikro-USB-port, 40 GPIO-pinner, en kamerakontakt for en Raspberry Pi-kameramodul, og en SD-kortspor. Den måler 65mm x 30mm x 5mm og bruker svært lite strøm. Zero koster 5 USD, mens W-versjonen med WiFi koster 10 USD.

> 🎓 CPU-ene i begge disse er ARM-prosessorer, i motsetning til Intel/AMD x86 eller x64-prosessorer du finner i de fleste PC-er og Mac-er. Disse ligner på CPU-ene du finner i noen mikrokontrollere, samt nesten alle mobiltelefoner, Microsoft Surface X og de nye Apple Silicon-baserte Mac-ene.

Alle varianter av Raspberry Pi kjører en versjon av Debian Linux kalt Raspberry Pi OS. Dette er tilgjengelig som en lettversjon uten skrivebord, som er perfekt for 'headless'-prosjekter der du ikke trenger en skjerm, eller en fullversjon med et komplett skrivebordsmiljø, inkludert nettleser, kontorapplikasjoner, kodeverktøy og spill. Siden OS-et er en versjon av Debian Linux, kan du installere alle applikasjoner eller verktøy som kjører på Debian og er bygget for ARM-prosessoren inne i Pi.

#### Oppgave

Undersøk Raspberry Pi.

Hvis du bruker en Raspberry Pi for disse leksjonene, les om de forskjellige maskinvarekomponentene på kortet.

* Du finner detaljer om prosessorene som brukes på [Raspberry Pi-maskinvaredokumentasjonssiden](https://www.raspberrypi.org/documentation/hardware/raspberrypi/). Les om prosessoren som brukes i Pi-en du bruker.
* Finn GPIO-pinnene. Les mer om dem på [Raspberry Pi GPIO-dokumentasjonen](https://www.raspberrypi.org/documentation/hardware/raspberrypi/gpio/README.md). Bruk [GPIO Pin Usage guide](https://www.raspberrypi.org/documentation/usage/gpio/README.md) for å identifisere de forskjellige pinnene på din Pi.

### Programmering av enkortsdatorer

Enkortsdatorer er fullverdige datamaskiner som kjører et komplett OS. Dette betyr at det finnes et bredt spekter av programmeringsspråk, rammeverk og verktøy du kan bruke til å kode dem, i motsetning til mikrokontrollere som er avhengige av støtte for kortet i rammeverk som Arduino. De fleste programmeringsspråk har biblioteker som kan få tilgang til GPIO-pinnene for å sende og motta data fra sensorer og aktuatorer.

✅ Hvilke programmeringsspråk er du kjent med? Støttes de på Linux?

Det mest vanlige programmeringsspråket for å bygge IoT-applikasjoner på en Raspberry Pi er Python. Det finnes et stort økosystem av maskinvare designet for Pi, og nesten alle disse inkluderer den nødvendige koden for å bruke dem som Python-biblioteker. Noen av disse økosystemene er basert på 'hatter' – såkalte fordi de sitter oppå Pi-en som en hatt og kobles til med en stor kontakt til de 40 GPIO-pinnene. Disse hattene gir ekstra funksjonalitet, som skjermer, sensorer, fjernstyrte biler eller adaptere som lar deg koble til sensorer med standardiserte kabler.
### Bruk av enkretsdatamaskiner i profesjonelle IoT-implementeringer

Enkretsdatamaskiner brukes i profesjonelle IoT-implementeringer, ikke bare som utviklingssett. De kan være en kraftig måte å kontrollere maskinvare på og utføre komplekse oppgaver som å kjøre maskinlæringsmodeller. For eksempel finnes det en [Raspberry Pi 4 Compute Module](https://www.raspberrypi.org/blog/raspberry-pi-compute-module-4/) som gir all kraften til en Raspberry Pi 4, men i en kompakt og billigere formfaktor uten de fleste porter, designet for å bli installert i spesialtilpasset maskinvare.

---

## 🚀 Utfordring

Utfordringen i forrige leksjon var å liste opp så mange IoT-enheter som mulig som finnes i hjemmet ditt, på skolen eller arbeidsplassen. For hver enhet på denne listen, tror du de er bygget rundt mikrokontrollere eller enkretsdatamaskiner, eller kanskje en blanding av begge?

## Quiz etter forelesning

[Quiz etter forelesning](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/4)

## Gjennomgang og selvstudium

* Les [Arduino-kom-i-gang-guiden](https://www.arduino.cc/en/Guide/Introduction) for å forstå mer om Arduino-plattformen.
* Les [introduksjonen til Raspberry Pi 4](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/) for å lære mer om Raspberry Pi.
* Lær mer om noen av konseptene og forkortelsene i [artikkelen "What the FAQ are CPUs, MPUs, MCUs, and GPUs" i Electrical Engineering Journal](https://www.eejournal.com/article/what-the-faq-are-cpus-mpus-mcus-and-gpus/).

✅ Bruk disse veiledningene, sammen med kostnadene som vises ved å følge lenkene i [maskinvareguiden](../../../hardware.md), for å bestemme hvilken maskinvareplattform du vil bruke, eller om du heller vil bruke en virtuell enhet.

## Oppgave

[Sammenlign og kontraster mikrokontrollere og enkretsdatamaskiner](assignment.md)

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.