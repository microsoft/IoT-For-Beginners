<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "52ed2bd997d08040f79a1a6ef2bac958",
  "translation_date": "2025-08-27T21:22:42+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/README.md",
  "language_code": "no"
}
-->
# Sporing av lokasjon

![En sketchnote-oversikt over denne leksjonen](../../../../../translated_images/no/lesson-11.9fddbac4b664c6d50ab7ac9bb32f1fc3f945f03760e72f7f43938073762fb017.jpg)

> Sketchnote av [Nitya Narasimhan](https://github.com/nitya). Klikk på bildet for en større versjon.

## Quiz før forelesning

[Quiz før forelesning](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/21)

## Introduksjon

Hovedprosessen for å få mat fra en bonde til en forbruker innebærer å laste kasser med produkter på lastebiler, skip, fly eller andre kommersielle transportmidler, og levere maten et sted – enten direkte til en kunde, eller til et sentralt knutepunkt eller lager for videre behandling. Hele prosessen fra gård til forbruker er en del av det som kalles *forsyningskjeden*. Videoen nedenfor fra W. P. Carey School of Business ved Arizona State University forklarer konseptet med forsyningskjeden og hvordan den administreres i mer detalj.

[![Hva er Supply Chain Management? En video fra W. P. Carey School of Business ved Arizona State University](https://img.youtube.com/vi/Mi1QBxVjZAw/0.jpg)](https://www.youtube.com/watch?v=Mi1QBxVjZAw)

> 🎥 Klikk på bildet ovenfor for å se videoen

Ved å legge til IoT-enheter kan du drastisk forbedre forsyningskjeden din, slik at du kan administrere hvor varer befinner seg, planlegge transport og varehåndtering bedre, og reagere raskere på problemer.

Når du administrerer en flåte av kjøretøy som lastebiler, er det nyttig å vite hvor hvert kjøretøy befinner seg til enhver tid. Kjøretøy kan utstyres med GPS-sensorer som sender sin lokasjon til IoT-systemer, slik at eierne kan finne ut hvor de er, se ruten de har tatt, og vite når de vil ankomme destinasjonen. De fleste kjøretøy opererer utenfor WiFi-dekning, så de bruker mobilnettverk for å sende denne typen data. Noen ganger er GPS-sensoren innebygd i mer komplekse IoT-enheter som elektroniske loggbøker. Disse enhetene sporer hvor lenge en lastebil har vært i transitt for å sikre at sjåførene overholder lokale lover om arbeidstimer.

I denne leksjonen vil du lære hvordan du sporer et kjøretøys lokasjon ved hjelp av en Global Positioning System (GPS)-sensor.

I denne leksjonen dekker vi:

* [Tilkoblede kjøretøy](../../../../../3-transport/lessons/1-location-tracking)
* [Geospatiale koordinater](../../../../../3-transport/lessons/1-location-tracking)
* [Global Positioning Systems (GPS)](../../../../../3-transport/lessons/1-location-tracking)
* [Les GPS-sensordata](../../../../../3-transport/lessons/1-location-tracking)
* [NMEA GPS-data](../../../../../3-transport/lessons/1-location-tracking)
* [Dekode GPS-sensordata](../../../../../3-transport/lessons/1-location-tracking)

## Tilkoblede kjøretøy

IoT transformerer måten varer transporteres på ved å skape flåter av *tilkoblede kjøretøy*. Disse kjøretøyene er koblet til sentrale IT-systemer som rapporterer informasjon om deres lokasjon og andre sensordata. Å ha en flåte av tilkoblede kjøretøy gir en rekke fordeler:

* Lokasjonssporing – du kan finne ut hvor et kjøretøy befinner seg til enhver tid, noe som lar deg:

  * Få varsler når et kjøretøy er i ferd med å ankomme en destinasjon, slik at mannskapet kan forberede seg på lossing
  * Lokalisere stjålne kjøretøy
  * Kombinere lokasjons- og rutedata med trafikkproblemer for å omdirigere kjøretøy underveis
  * Overholde skattelovgivning. Noen land belaster kjøretøy for antall kilometer kjørt på offentlige veier (som [New Zealands RUC](https://www.nzta.govt.nz/vehicles/licensing-rego/road-user-charges/)), så det å vite når et kjøretøy er på offentlige veier kontra private veier gjør det enklere å beregne skyldig skatt.
  * Vite hvor man skal sende vedlikeholdsteam i tilfelle et sammenbrudd

* Sjåførtelemetri – sikre at sjåfører overholder fartsgrenser, tar svinger i passende hastigheter, bremser tidlig og effektivt, og kjører trygt. Tilkoblede kjøretøy kan også ha kameraer for å registrere hendelser. Dette kan kobles til forsikring, med reduserte priser for gode sjåfører.

* Overholdelse av sjåførens arbeidstimer – sikre at sjåfører kun kjører innenfor sine lovlige arbeidstimer basert på tidspunktene de starter og stopper motoren.

Disse fordelene kan kombineres – for eksempel ved å kombinere overholdelse av sjåførens arbeidstimer med lokasjonssporing for å omdirigere sjåfører hvis de ikke kan nå destinasjonen innenfor sine tillatte arbeidstimer. Disse kan også kombineres med annen kjøretøyspesifikk telemetri, som temperaturdata fra temperaturkontrollerte lastebiler, slik at kjøretøy kan omdirigeres hvis deres nåværende rute vil føre til at varer ikke kan holdes ved riktig temperatur.

> 🎓 Logistikk er prosessen med å transportere varer fra ett sted til et annet, for eksempel fra en gård til et supermarked via ett eller flere lagre. En bonde pakker kasser med tomater som lastes på en lastebil, leveres til et sentralt lager, og lastes på en annen lastebil som kan inneholde en blanding av forskjellige typer produkter som deretter leveres til et supermarked.

Kjernekomponenten i kjøretøysporing er GPS – sensorer som kan finne sin lokasjon hvor som helst på jorden. I denne leksjonen vil du lære hvordan du bruker en GPS-sensor, og begynner med å lære hvordan man definerer en lokasjon på jorden.

## Geospatiale koordinater

Geospatiale koordinater brukes til å definere punkter på jordens overflate, på samme måte som koordinater kan brukes til å tegne en piksel på en dataskjerm eller plassere sting i korssting. For et enkelt punkt har du et par koordinater. For eksempel ligger Microsoft Campus i Redmond, Washington, USA på 47.6423109, -122.1390293.

### Breddegrad og lengdegrad

Jorden er en kule – en tredimensjonal sirkel. På grunn av dette defineres punkter ved å dele den inn i 360 grader, det samme som geometrien til sirkler. Breddegrad måler antall grader nord til sør, lengdegrad måler antall grader øst til vest.

> 💁 Ingen vet egentlig den opprinnelige grunnen til at sirkler er delt inn i 360 grader. [Gradsiden på Wikipedia](https://wikipedia.org/wiki/Degree_(angle)) dekker noen av de mulige årsakene.

![Breddegradslinjer fra 90° ved Nordpolen, 45° halvveis mellom Nordpolen og ekvator, 0° ved ekvator, -45° halvveis mellom ekvator og Sydpolen, og -90° ved Sydpolen](../../../../../translated_images/no/latitude-lines.11d8d91dfb2014a57437272d7db7fd6607243098e8685f06e0c5f1ec984cb7eb.png)

Breddegrad måles ved hjelp av linjer som sirkler jorden og går parallelt med ekvator, og deler den nordlige og sørlige halvkule inn i 90° hver. Ekvator er på 0°, Nordpolen er 90°, også kjent som 90° Nord, og Sydpolen er på -90°, eller 90° Sør.

Lengdegrad måles som antall grader målt øst og vest. 0°-opprinnelsen til lengdegrad kalles *Prime Meridian*, og ble definert i 1884 som en linje fra Nordpolen til Sydpolen som går gjennom [British Royal Observatory i Greenwich, England](https://wikipedia.org/wiki/Royal_Observatory,_Greenwich).

![Lengdegradslinjer som går fra -180° vest for Prime Meridian, til 0° på Prime Meridian, til 180° øst for Prime Meridian](../../../../../translated_images/no/longitude-meridians.ab4ef1c91c064586b0185a3c8d39e585903696c6a7d28c098a93a629cddb5d20.png)

> 🎓 En meridian er en imaginær rett linje som går fra Nordpolen til Sydpolen og danner en halvsirkel.

For å måle lengdegraden til et punkt, måler du antall grader rundt ekvator fra Prime Meridian til en meridian som passerer gjennom det punktet. Lengdegrad går fra -180°, eller 180° Vest, gjennom 0° ved Prime Meridian, til 180°, eller 180° Øst. 180° og -180° refererer til samme punkt, antimeridianen eller den 180. meridianen. Dette er en meridian på motsatt side av jorden fra Prime Meridian.

> 💁 Antimeridianen må ikke forveksles med den internasjonale datolinjen, som ligger omtrent på samme sted, men som ikke er en rett linje og varierer for å passe rundt geopolitiske grenser.

✅ Gjør litt research: Prøv å finne breddegraden og lengdegraden til din nåværende lokasjon.

### Grader, minutter og sekunder vs desimalgrader

Tradisjonelt ble målinger av grader av breddegrad og lengdegrad gjort ved hjelp av sekstitalssystemet, eller base-60, et tallsystem brukt av de gamle babylonerne som gjorde de første målingene og registreringene av tid og avstand. Du bruker sekstitalsystemet hver dag uten å tenke over det – ved å dele timer inn i 60 minutter og minutter inn i 60 sekunder.

Lengdegrad og breddegrad måles i grader, minutter og sekunder, der ett minutt er 1/60 av en grad, og 1 sekund er 1/60 minutt.

For eksempel, ved ekvator:

* 1° breddegrad er **111,3 kilometer**
* 1 minutt breddegrad er 111,3/60 = **1,855 kilometer**
* 1 sekund breddegrad er 1,855/60 = **0,031 kilometer**

Symbolet for et minutt er en enkel apostrof, for et sekund er det en dobbel apostrof. 2 grader, 17 minutter og 43 sekunder, for eksempel, vil bli skrevet som 2°17'43". Deler av sekunder gis som desimaler, for eksempel en halv sekund er 0°0'0.5".

Datamaskiner fungerer ikke i base-60, så disse koordinatene gis som desimalgrader når GPS-data brukes i de fleste datasystemer. For eksempel er 2°17'43" 2.295277. Gradsymbolet utelates vanligvis.

Koordinater for et punkt gis alltid som `breddegrad, lengdegrad`, så eksempelet tidligere med Microsoft Campus på 47.6423109,-122.117198 har:

* En breddegrad på 47.6423109 (47.6423109 grader nord for ekvator)
* En lengdegrad på -122.1390293 (122.1390293 grader vest for Prime Meridian).

![Microsoft Campus på 47.6423109,-122.117198](../../../../../translated_images/no/microsoft-gps-location-world.a321d481b010f6adfcca139b2ba0adc53b79f58a540495b8e2ce7f779ea64bfe.png)

## Global Positioning Systems (GPS)

GPS-systemer bruker flere satellitter som går i bane rundt jorden for å finne din posisjon. Du har sannsynligvis brukt GPS-systemer uten å vite det – for å finne din lokasjon i en kartapp på telefonen din, som Apple Maps eller Google Maps, eller for å se hvor din transport er i en app som Uber eller Lyft, eller når du bruker satellittnavigasjon (sat-nav) i bilen din.

> 🎓 Satellittene i 'satellittnavigasjon' er GPS-satellitter!

GPS-systemer fungerer ved å ha et antall satellitter som sender et signal med hver satellitts nåværende posisjon og en nøyaktig tidsstempel. Disse signalene sendes over radiobølger og oppdages av en antenne i GPS-sensoren. En GPS-sensor vil oppdage disse signalene, og ved hjelp av den nåværende tiden måle hvor lang tid det tok for signalet å nå sensoren fra satellitten. Fordi hastigheten på radiobølger er konstant, kan GPS-sensoren bruke tidsstempelet som ble sendt for å finne ut hvor langt unna sensoren er fra satellitten. Ved å kombinere data fra minst 3 satellitter med posisjonene som ble sendt, kan GPS-sensoren finne sin lokasjon på jorden.

> 💁 GPS-sensorer trenger antenner for å oppdage radiobølger. Antennene som er innebygd i lastebiler og biler med innebygd GPS er plassert for å få et godt signal, vanligvis på frontruten eller taket. Hvis du bruker et separat GPS-system, som en smarttelefon eller en IoT-enhet, må du sørge for at antennen innebygd i GPS-systemet eller telefonen har fri sikt til himmelen, for eksempel ved å være montert på frontruten.

![Ved å vite avstanden fra sensoren til flere satellitter, kan lokasjonen beregnes](../../../../../translated_images/no/gps-satellites.04acf1148fe25fbf1586bc2e8ba698e8d79b79a50c36824b38417dd13372b90f.png)

GPS-satellitter sirkler jorden, ikke på et fast punkt over sensoren, så lokasjonsdata inkluderer høyde over havnivå i tillegg til breddegrad og lengdegrad.

GPS hadde tidligere begrensninger på nøyaktighet som ble håndhevet av det amerikanske militæret, og begrenset nøyaktigheten til rundt 5 meter. Denne begrensningen ble fjernet i 2000, noe som tillot en nøyaktighet på 30 centimeter. Å oppnå denne nøyaktigheten er ikke alltid mulig på grunn av forstyrrelser i signalene.

✅ Hvis du har en smarttelefon, åpne kartappen og se hvor nøyaktig din lokasjon er. Det kan ta litt tid for telefonen din å oppdage flere satellitter for å få en mer nøyaktig lokasjon.
💁 Satellittene inneholder atomklokker som er utrolig nøyaktige, men de avviker med 38 mikrosekunder (0,0000038 sekunder) per dag sammenlignet med atomklokker på jorden, på grunn av at tiden går saktere når hastigheten øker, slik Einstein forutså i sine teorier om spesiell og generell relativitet - satellittene beveger seg raskere enn jordens rotasjon. Denne avviket har blitt brukt til å bevise forutsigelsene om spesiell og generell relativitet, og må justeres i utformingen av GPS-systemer. Bokstavelig talt går tiden saktere på en GPS-satellitt.
GPS-systemer har blitt utviklet og tatt i bruk av flere land og politiske unioner, inkludert USA, Russland, Japan, India, EU og Kina. Moderne GPS-sensorer kan koble seg til de fleste av disse systemene for å få raskere og mer nøyaktige posisjonsdata.

> 🎓 Satellittgruppene i hver implementering kalles konstellasjoner.

## Les GPS-sensordata

De fleste GPS-sensorer sender GPS-data via UART.

> ⚠️ UART ble dekket i [prosjekt 2, leksjon 2](../../../2-farm/lessons/2-detect-soil-moisture/README.md#universal-asynchronous-receiver-transmitter-uart). Gå tilbake til den leksjonen om nødvendig.

Du kan bruke en GPS-sensor på IoT-enheten din for å hente GPS-data.

### Oppgave - koble til en GPS-sensor og les GPS-data

Følg den relevante veiledningen for å lese GPS-data med IoT-enheten din:

* [Arduino - Wio Terminal](wio-terminal-gps-sensor.md)
* [Enkeltkortdatamaskin - Raspberry Pi](pi-gps-sensor.md)
* [Enkeltkortdatamaskin - Virtuell enhet](virtual-device-gps-sensor.md)

## NMEA GPS-data

Når du kjørte koden din, så du kanskje noe som kan virke som uforståelig tekst i utdataene. Dette er faktisk standard GPS-data, og alt har en betydning.

GPS-sensorer sender data ved hjelp av NMEA-meldinger, i henhold til NMEA 0183-standarden. NMEA er et akronym for [National Marine Electronics Association](https://www.nmea.org), en amerikansk handelsorganisasjon som setter standarder for kommunikasjon mellom marinelektronikk.

> 💁 Denne standarden er proprietær og koster minst 2 000 USD, men nok informasjon om den er offentlig tilgjengelig til at mesteparten av standarden har blitt reversert og kan brukes i åpen kildekode og annen ikke-kommersiell programvare.

Disse meldingene er tekstbaserte. Hver melding består av en *setning* som starter med et `$`-tegn, etterfulgt av 2 tegn som indikerer kilden til meldingen (f.eks. GP for det amerikanske GPS-systemet, GN for GLONASS, det russiske GPS-systemet), og 3 tegn som indikerer typen melding. Resten av meldingen er felt separert med komma, og avsluttes med et linjeskift-tegn.

Noen av meldingstypene som kan mottas er:

| Type | Beskrivelse |
| ---- | ----------- |
| GGA | GPS Fix Data, inkludert breddegrad, lengdegrad og høyde for GPS-sensoren, sammen med antall satellitter i sikte for å beregne denne posisjonen. |
| ZDA | Gjeldende dato og tid, inkludert lokal tidssone |
| GSV | Detaljer om satellittene i sikte - definert som satellittene GPS-sensoren kan motta signaler fra |

> 💁 GPS-data inkluderer tidsstempler, så IoT-enheten din kan hente tid fra en GPS-sensor om nødvendig, i stedet for å stole på en NTP-server eller en intern sanntidsklokke.

GGA-meldingen inkluderer gjeldende posisjon i `(dd)dmm.mmmm`-formatet, sammen med et enkelt tegn for å indikere retning. `d` i formatet er grader, `m` er minutter, med sekunder som desimaler av minutter. For eksempel, 2°17'43" ville være 217.716666667 - 2 grader, 17.716666667 minutter.

Retningstegnet kan være `N` eller `S` for breddegrad for å indikere nord eller sør, og `E` eller `W` for lengdegrad for å indikere øst eller vest. For eksempel, en breddegrad på 2°17'43" ville ha et retningstegn `N`, -2°17'43" ville ha et retningstegn `S`.

For eksempel - NMEA-setningen `$GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67`

* Breddegradsdelen er `4738.538654,N`, som konverteres til 47.6423109 i desimalgrader. `4738.538654` er 47.6423109, og retningen er `N` (nord), så det er en positiv breddegrad.

* Lengdegradsdelen er `12208.341758,W`, som konverteres til -122.1390293 i desimalgrader. `12208.341758` er 122.1390293°, og retningen er `W` (vest), så det er en negativ lengdegrad.

## Dekode GPS-sensordata

I stedet for å bruke rå NMEA-data, er det bedre å dekode dem til et mer nyttig format. Det finnes flere åpne kildebiblioteker du kan bruke for å hjelpe til med å hente ut nyttige data fra de rå NMEA-meldingene.

### Oppgave - dekode GPS-sensordata

Følg den relevante veiledningen for å dekode GPS-sensordata med IoT-enheten din:

* [Arduino - Wio Terminal](wio-terminal-gps-decode.md)
* [Enkeltkortdatamaskin - Raspberry Pi/Virtual IoT-enhet](single-board-computer-gps-decode.md)

---

## 🚀 Utfordring

Skriv din egen NMEA-dekoder! I stedet for å stole på tredjepartsbiblioteker for å dekode NMEA-setninger, kan du skrive din egen dekoder for å hente ut breddegrad og lengdegrad fra NMEA-setninger?

## Quiz etter forelesning

[Quiz etter forelesning](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/22)

## Gjennomgang og selvstudium

* Les mer om geospatiale koordinater på [Geografisk koordinatsystem-siden på Wikipedia](https://wikipedia.org/wiki/Geographic_coordinate_system).
* Les om nullmeridianer på andre himmellegemer enn jorden på [Nullmeridian-siden på Wikipedia](https://wikipedia.org/wiki/Prime_meridian#Prime_meridian_on_other_planetary_bodies).
* Undersøk de ulike GPS-systemene fra forskjellige regjeringer og politiske unioner som EU, Japan, Russland, India og USA.

## Oppgave

[Undersøk andre GPS-data](assignment.md)

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for eventuelle misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.