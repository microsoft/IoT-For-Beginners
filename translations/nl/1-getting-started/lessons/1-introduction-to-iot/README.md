<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9bae08314d8487cb76ddf3d8797e1544",
  "translation_date": "2025-08-27T21:58:23+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/README.md",
  "language_code": "nl"
}
-->
# Introductie tot IoT

![Een schetsnotitie-overzicht van deze les](../../../../../translated_images/nl/lesson-1.2606670fa61ee904687da5d6fa4e726639d524d064c895117da1b95b9ff6251d.jpg)

> Schetsnotitie door [Nitya Narasimhan](https://github.com/nitya). Klik op de afbeelding voor een grotere versie.

Deze les werd gegeven als onderdeel van de [Hello IoT-serie](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) van de [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). De les bestond uit twee video's: een les van 1 uur en een vragenuurtje van 1 uur waarin dieper werd ingegaan op onderdelen van de les en vragen werden beantwoord.

[![Les 1: Introductie tot IoT](https://img.youtube.com/vi/bVFfcYh6UBw/0.jpg)](https://youtu.be/bVFfcYh6UBw)

[![Les 1: Introductie tot IoT - Vragenuurtje](https://img.youtube.com/vi/YI772q5v3yI/0.jpg)](https://youtu.be/YI772q5v3yI)

> 🎥 Klik op de bovenstaande afbeeldingen om de video's te bekijken

## Quiz voorafgaand aan de les

[Quiz voorafgaand aan de les](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/1)

## Introductie

Deze les behandelt enkele inleidende onderwerpen over het Internet of Things en helpt je bij het opzetten van je hardware.

In deze les behandelen we:

* [Wat is het 'Internet of Things'?](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [IoT-apparaten](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Je apparaat instellen](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Toepassingen van IoT](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Voorbeelden van IoT-apparaten om je heen](../../../../../1-getting-started/lessons/1-introduction-to-iot)

## Wat is het 'Internet of Things'?

De term 'Internet of Things' werd in 1999 bedacht door [Kevin Ashton](https://wikipedia.org/wiki/Kevin_Ashton) om te verwijzen naar het verbinden van het internet met de fysieke wereld via sensoren. Sindsdien wordt de term gebruikt om elk apparaat te beschrijven dat interactie heeft met de fysieke wereld, hetzij door gegevens te verzamelen via sensoren, hetzij door interacties in de echte wereld te bieden via actuatoren (apparaten die iets doen, zoals een schakelaar omzetten of een LED aansteken), meestal verbonden met andere apparaten of het internet.

> **Sensoren** verzamelen informatie uit de wereld, zoals het meten van snelheid, temperatuur of locatie.
>
> **Actuatoren** zetten elektrische signalen om in interacties in de echte wereld, zoals het activeren van een schakelaar, het inschakelen van lampen, het maken van geluiden of het verzenden van besturingssignalen naar andere hardware, bijvoorbeeld om een stopcontact in te schakelen.

IoT als technologiegebied omvat meer dan alleen apparaten - het omvat ook cloudgebaseerde diensten die sensorgegevens kunnen verwerken of verzoeken kunnen sturen naar actuatoren die zijn aangesloten op IoT-apparaten. Het omvat ook apparaten die geen internetverbinding hebben of nodig hebben, vaak aangeduid als edge-apparaten. Dit zijn apparaten die sensorgegevens zelf kunnen verwerken en erop kunnen reageren, meestal met behulp van AI-modellen die in de cloud zijn getraind.

IoT is een snelgroeiend technologiedomein. Naar schatting waren er eind 2020 30 miljard IoT-apparaten geïmplementeerd en verbonden met het internet. Vooruitkijkend wordt geschat dat IoT-apparaten tegen 2025 bijna 80 zettabytes aan gegevens zullen verzamelen, oftewel 80 biljoen gigabytes. Dat is een enorme hoeveelheid data!

![Een grafiek die actieve IoT-apparaten in de loop van de tijd toont, met een stijgende lijn van minder dan 5 miljard in 2015 tot meer dan 30 miljard in 2025](../../../../../images/connected-iot-devices.svg)

✅ Doe wat onderzoek: Hoeveel van de gegevens die door IoT-apparaten worden gegenereerd, wordt daadwerkelijk gebruikt, en hoeveel wordt verspild? Waarom wordt zoveel data genegeerd?

Deze gegevens zijn de sleutel tot het succes van IoT. Om een succesvolle IoT-ontwikkelaar te worden, moet je begrijpen welke gegevens je moet verzamelen, hoe je ze verzamelt, hoe je beslissingen neemt op basis van die gegevens en hoe je die beslissingen kunt gebruiken om indien nodig interactie te hebben met de fysieke wereld.

## IoT-apparaten

De **T** in IoT staat voor **Things** - apparaten die interactie hebben met de fysieke wereld om hen heen, hetzij door gegevens te verzamelen via sensoren, hetzij door interacties in de echte wereld te bieden via actuatoren.

Apparaten voor productie of commercieel gebruik, zoals consumentgerichte fitnesstrackers of industriële machinecontrollers, zijn meestal op maat gemaakt. Ze gebruiken aangepaste printplaten, en mogelijk zelfs aangepaste processors, ontworpen om te voldoen aan de eisen van een specifieke taak, of dat nu klein genoeg is om om een pols te passen, of robuust genoeg om te werken in een omgeving met hoge temperaturen, veel stress of trillingen.

Als ontwikkelaar die IoT wil leren of een apparaatprototype wil maken, moet je beginnen met een ontwikkelaarskit. Dit zijn algemene IoT-apparaten die zijn ontworpen voor ontwikkelaars, vaak met functies die je niet op een productieapparaat zou hebben, zoals een set externe pinnen om sensoren of actuatoren aan te sluiten, hardware voor debugging of extra middelen die onnodige kosten zouden toevoegen bij massaproductie.

Deze ontwikkelaarskits vallen meestal in twee categorieën: microcontrollers en single-board computers. Deze worden hier geïntroduceerd, en we gaan er in de volgende les dieper op in.

> 💁 Je telefoon kan ook worden beschouwd als een algemeen IoT-apparaat, met ingebouwde sensoren en actuatoren, waarbij verschillende apps de sensoren en actuatoren op verschillende manieren gebruiken met verschillende clouddiensten. Je kunt zelfs enkele IoT-tutorials vinden die een telefoonapp gebruiken als IoT-apparaat.

### Microcontrollers

Een microcontroller (ook wel MCU genoemd, wat staat voor microcontroller unit) is een kleine computer die bestaat uit:

🧠 Een of meer centrale verwerkingseenheden (CPU's) - het 'brein' van de microcontroller dat je programma uitvoert

💾 Geheugen (RAM en programmageheugen) - waar je programma, gegevens en variabelen worden opgeslagen

🔌 Programmeerbare input/output (I/O)-aansluitingen - om te communiceren met externe randapparatuur (aangesloten apparaten) zoals sensoren en actuatoren

Microcontrollers zijn doorgaans goedkope computerapparaten, met gemiddelde prijzen voor die in aangepaste hardware dalend tot ongeveer US$0,50, en sommige apparaten zo goedkoop als US$0,03. Ontwikkelaarskits beginnen vanaf ongeveer US$4, met stijgende kosten naarmate je meer functies toevoegt. De [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html), een microcontroller-ontwikkelaarskit van [Seeed studios](https://www.seeedstudio.com) met sensoren, actuatoren, WiFi en een scherm, kost ongeveer US$30.

![Een Wio Terminal](../../../../../translated_images/nl/wio-terminal.b8299ee16587db9a.webp)

> 💁 Wees voorzichtig bij het zoeken naar microcontrollers op internet met de term **MCU**, omdat dit veel resultaten zal opleveren voor het Marvel Cinematic Universe in plaats van microcontrollers.

Microcontrollers zijn ontworpen om een beperkt aantal zeer specifieke taken uit te voeren, in plaats van algemene computers te zijn zoals pc's of Macs. Behalve in zeer specifieke scenario's kun je geen monitor, toetsenbord en muis aansluiten en ze gebruiken voor algemene taken.

Microcontroller-ontwikkelaarskits hebben meestal extra sensoren en actuatoren aan boord. De meeste borden hebben een of meer programmeerbare LED's, samen met andere apparaten zoals standaardpluggen voor het toevoegen van meer sensoren of actuatoren via verschillende ecosysteemfabrikanten of ingebouwde sensoren (meestal de populairste, zoals temperatuursensoren). Sommige microcontrollers hebben ingebouwde draadloze connectiviteit zoals Bluetooth of WiFi, of hebben extra microcontrollers op het bord om deze connectiviteit toe te voegen.

> 💁 Microcontrollers worden meestal geprogrammeerd in C/C++.

### Single-board computers

Een single-board computer is een klein computerapparaat dat alle elementen van een complete computer bevat op één enkele kleine printplaat. Dit zijn apparaten met specificaties die dicht bij een desktop- of laptop-pc of Mac liggen, een volledig besturingssysteem draaien, maar kleiner zijn, minder stroom verbruiken en aanzienlijk goedkoper zijn.

![Een Raspberry Pi 4](../../../../../translated_images/nl/raspberry-pi-4.fd4590d308c3d456.webp)

De Raspberry Pi is een van de populairste single-board computers.

Net als een microcontroller hebben single-board computers een CPU, geheugen en input/output-pinnen, maar ze hebben extra functies zoals een grafische chip om monitoren aan te sluiten, audio-uitgangen en USB-poorten om toetsenborden, muizen en andere standaard USB-apparaten zoals webcams of externe opslag aan te sluiten. Programma's worden opgeslagen op SD-kaarten of harde schijven samen met een besturingssysteem, in plaats van een geheugenchip die in het bord is ingebouwd.

> 🎓 Je kunt een single-board computer zien als een kleinere, goedkopere versie van de pc of Mac waarop je dit leest, met de toevoeging van GPIO (general-purpose input/output)-pinnen om te communiceren met sensoren en actuatoren.

Single-board computers zijn volledig uitgeruste computers en kunnen in elke taal worden geprogrammeerd. IoT-apparaten worden meestal geprogrammeerd in Python.

### Hardwarekeuzes voor de rest van de lessen

Alle volgende lessen bevatten opdrachten waarbij een IoT-apparaat wordt gebruikt om te communiceren met de fysieke wereld en de cloud. Elke les ondersteunt drie apparaatkeuzes: Arduino (met een Seeed Studios Wio Terminal), of een single-board computer, hetzij een fysiek apparaat (een Raspberry Pi 4) of een virtueel apparaat dat op je pc of Mac draait.

Je kunt lezen over de benodigde hardware om alle opdrachten te voltooien in de [hardwaregids](../../../hardware.md).

> 💁 Je hoeft geen IoT-hardware aan te schaffen om de opdrachten te voltooien; je kunt alles doen met een virtuele single-board computer.

Welke hardware je kiest, hangt af van wat je thuis of op school beschikbaar hebt en welke programmeertaal je kent of wilt leren. Beide hardwarevarianten gebruiken hetzelfde sensorecosysteem, dus als je met de ene begint, kun je overstappen naar de andere zonder de meeste onderdelen te hoeven vervangen. De virtuele single-board computer is vergelijkbaar met leren op een Raspberry Pi, waarbij de meeste code overdraagbaar is naar de Pi als je uiteindelijk een apparaat en sensoren aanschaft.

### Arduino-ontwikkelaarskit

Als je geïnteresseerd bent in het leren van microcontrollerontwikkeling, kun je de opdrachten voltooien met een Arduino-apparaat. Je hebt een basiskennis van C/C++-programmering nodig, omdat de lessen alleen code behandelen die relevant is voor het Arduino-framework, de gebruikte sensoren en actuatoren, en de bibliotheken die communiceren met de cloud.

De opdrachten maken gebruik van [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn) met de [PlatformIO-extensie voor microcontrollerontwikkeling](https://platformio.org). Je kunt ook de Arduino IDE gebruiken als je ervaring hebt met deze tool, maar er worden geen instructies gegeven.

### Single-board computer ontwikkelaarskit

Als je geïnteresseerd bent in het leren van IoT-ontwikkeling met single-board computers, kun je de opdrachten voltooien met een Raspberry Pi of een virtueel apparaat dat op je pc of Mac draait.

Je hebt een basiskennis van Python-programmering nodig, omdat de lessen alleen code behandelen die relevant is voor de gebruikte sensoren en actuatoren, en de bibliotheken die communiceren met de cloud.

> 💁 Als je Python wilt leren programmeren, bekijk dan de volgende twee videoseries:
>
> * [Python voor beginners](https://channel9.msdn.com/Series/Intro-to-Python-Development?WT.mc_id=academic-17441-jabenn)
> * [Meer Python voor beginners](https://channel9.msdn.com/Series/More-Python-for-Beginners?WT.mc_id=academic-7372-jabenn)

De opdrachten maken gebruik van [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn).

Als je een Raspberry Pi gebruikt, kun je je Pi gebruiken met de volledige desktopversie van Raspberry Pi OS en al het coderen direct op de Pi doen met [de Raspberry Pi OS-versie van VS Code](https://code.visualstudio.com/docs/setup/raspberry-pi?WT.mc_id=academic-17441-jabenn), of je Pi als een headless apparaat gebruiken en coderen vanaf je pc of Mac met VS Code en de [Remote SSH-extensie](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn), waarmee je verbinding kunt maken met je Pi en code kunt bewerken, debuggen en uitvoeren alsof je direct op de Pi aan het coderen bent.

Als je de virtuele apparaatoptie gebruikt, codeer je direct op je computer. In plaats van sensoren en actuatoren te gebruiken, gebruik je een tool om deze hardware te simuleren, waarbij je sensorgegevens kunt definiëren en de resultaten van actuatoren op het scherm kunt zien.

## Je apparaat instellen

Voordat je kunt beginnen met het programmeren van je IoT-apparaat, moet je een kleine hoeveelheid installatie uitvoeren. Volg de relevante instructies hieronder, afhankelijk van welk apparaat je gaat gebruiken.
💁 Als je nog geen apparaat hebt, raadpleeg dan de [hardwaregids](../../../hardware.md) om te bepalen welk apparaat je gaat gebruiken en welke extra hardware je moet aanschaffen. Het is niet nodig om hardware aan te schaffen, aangezien alle projecten op virtuele hardware kunnen worden uitgevoerd.
Deze instructies bevatten links naar websites van derden van de makers van de hardware of tools die je zult gebruiken. Dit is om ervoor te zorgen dat je altijd de meest actuele instructies gebruikt voor de verschillende tools en hardware.

Werk de relevante handleiding door om je apparaat in te stellen en een 'Hello World'-project te voltooien. Dit is de eerste stap in het maken van een IoT-nachtlampje gedurende de 4 lessen in dit introductiegedeelte.

* [Arduino - Wio Terminal](wio-terminal.md)  
* [Single-board computer - Raspberry Pi](pi.md)  
* [Single-board computer - Virtueel apparaat](virtual-device.md)  

✅ Je zult VS Code gebruiken voor zowel Arduino als single-board computers. Als je dit nog niet eerder hebt gebruikt, lees er dan meer over op de [VS Code-site](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

## Toepassingen van IoT

IoT bestrijkt een enorm scala aan toepassingen, verdeeld over een paar brede categorieën:

* Consumenten-IoT  
* Commerciële IoT  
* Industriële IoT  
* Infrastructuur-IoT  

✅ Doe wat onderzoek: Voor elk van de hieronder beschreven gebieden, zoek één concreet voorbeeld dat niet in de tekst wordt genoemd.

### Consumenten-IoT

Consumenten-IoT verwijst naar IoT-apparaten die consumenten kopen en thuis gebruiken. Sommige van deze apparaten zijn ongelooflijk nuttig, zoals slimme luidsprekers, slimme verwarmingssystemen en robotstofzuigers. Andere zijn twijfelachtig in hun nut, zoals spraakgestuurde kranen die je niet kunt uitzetten omdat de spraakbesturing je niet kan horen boven het geluid van stromend water.

Consumenten-IoT-apparaten stellen mensen in staat meer te bereiken in hun omgeving, vooral de 1 miljard mensen met een beperking. Robotstofzuigers kunnen schone vloeren bieden aan mensen met mobiliteitsproblemen die niet zelf kunnen stofzuigen, spraakgestuurde ovens stellen mensen met een beperkt zicht of motorische controle in staat hun ovens alleen met hun stem te bedienen, en gezondheidsmonitors stellen patiënten in staat chronische aandoeningen zelf te monitoren met meer regelmatige en gedetailleerde updates over hun toestand. Deze apparaten worden zo alomtegenwoordig dat zelfs jonge kinderen ze dagelijks gebruiken, bijvoorbeeld studenten die tijdens de COVID-pandemie virtueel onderwijs volgden en timers instelden op slimme thuisapparaten om hun schoolwerk bij te houden of alarmen om hen te herinneren aan aankomende lessen.

✅ Welke consumenten-IoT-apparaten heb je bij je of in je huis?

### Commerciële IoT

Commerciële IoT omvat het gebruik van IoT op de werkplek. In een kantooromgeving kunnen er bezettingssensoren en bewegingsdetectoren zijn om verlichting en verwarming te beheren, zodat deze alleen aanstaan wanneer nodig, wat kosten en CO2-uitstoot vermindert. In een fabriek kunnen IoT-apparaten veiligheidsrisico's monitoren, zoals werknemers die geen helmen dragen of geluid dat gevaarlijke niveaus bereikt. In de detailhandel kunnen IoT-apparaten de temperatuur van koelopslag meten en de winkelier waarschuwen als een koelkast of vriezer buiten het vereiste temperatuurbereik valt, of ze kunnen items op schappen monitoren om werknemers te sturen om uitverkochte producten aan te vullen. De transportsector maakt steeds meer gebruik van IoT om voertuiglocaties te monitoren, gereden kilometers bij te houden voor kilometerheffing, naleving van rij- en rusttijden te controleren, of personeel te waarschuwen wanneer een voertuig een depot nadert om zich voor te bereiden op laden of lossen.

✅ Welke commerciële IoT-apparaten heb je op school of op je werkplek?

### Industriële IoT (IIoT)

Industriële IoT, of IIoT, is het gebruik van IoT-apparaten om machines op grote schaal te beheren en te controleren. Dit omvat een breed scala aan toepassingen, van fabrieken tot digitale landbouw.

Fabrieken gebruiken IoT-apparaten op veel verschillende manieren. Machines kunnen worden gemonitord met meerdere sensoren om zaken als temperatuur, trillingen en rotatiesnelheid te volgen. Deze gegevens kunnen worden gemonitord om de machine te stoppen als deze buiten bepaalde toleranties gaat - bijvoorbeeld als deze te heet wordt en wordt uitgeschakeld. Deze gegevens kunnen ook over tijd worden verzameld en geanalyseerd voor voorspellend onderhoud, waarbij AI-modellen de gegevens analyseren die voorafgaan aan een storing en deze gebruiken om andere storingen te voorspellen voordat ze optreden.

Digitale landbouw is belangrijk om de groeiende wereldbevolking te voeden, vooral voor de 2 miljard mensen in 500 miljoen huishoudens die leven van [zelfvoorzienende landbouw](https://wikipedia.org/wiki/Subsistence_agriculture). Digitale landbouw kan variëren van een paar goedkope sensoren tot enorme commerciële installaties. Een boer kan beginnen met het monitoren van temperaturen en het gebruik van [groeigraden](https://wikipedia.org/wiki/Growing_degree-day) om te voorspellen wanneer een gewas klaar is voor de oogst. Ze kunnen bodemvochtmonitoring verbinden met geautomatiseerde bewateringssystemen om hun planten precies zoveel water te geven als nodig is, zonder verspilling. Boeren gaan zelfs verder door drones, satellietgegevens en AI te gebruiken om gewasgroei, ziektes en bodemkwaliteit over grote landbouwgebieden te monitoren.

✅ Welke andere IoT-apparaten zouden boeren kunnen helpen?

### Infrastructuur-IoT

Infrastructuur-IoT houdt toezicht op en beheert de lokale en wereldwijde infrastructuur die mensen dagelijks gebruiken.

[Smart Cities](https://wikipedia.org/wiki/Smart_city) zijn stedelijke gebieden die IoT-apparaten gebruiken om gegevens over de stad te verzamelen en deze te gebruiken om de werking van de stad te verbeteren. Deze steden worden meestal beheerd in samenwerking tussen lokale overheden, academische instellingen en lokale bedrijven, waarbij zaken worden gevolgd en beheerd zoals transport, parkeren en vervuiling. In Kopenhagen, Denemarken, is luchtvervuiling bijvoorbeeld belangrijk voor de lokale bewoners, dus wordt deze gemeten en worden de gegevens gebruikt om informatie te geven over de schoonste fiets- en joggingroutes.

[Smart power grids](https://wikipedia.org/wiki/Smart_grid) bieden betere analyses van stroomvraag door gebruiksgegevens te verzamelen op het niveau van individuele huishoudens. Deze gegevens kunnen beslissingen sturen op landelijk niveau, zoals waar nieuwe energiecentrales moeten worden gebouwd, en op persoonlijk niveau door gebruikers inzicht te geven in hun energieverbruik, wanneer ze energie gebruiken en zelfs suggesties te doen om kosten te verlagen, zoals het opladen van elektrische auto's 's nachts.

✅ Als je IoT-apparaten zou kunnen toevoegen om iets te meten waar je woont, wat zou dat dan zijn?

## Voorbeelden van IoT-apparaten die je om je heen kunt hebben

Je zou versteld staan van hoeveel IoT-apparaten je om je heen hebt. Ik schrijf dit vanuit huis en ik heb de volgende apparaten verbonden met het internet met slimme functies zoals app-bediening, spraakbesturing of de mogelijkheid om gegevens naar mij te sturen via mijn telefoon:

* Meerdere slimme luidsprekers  
* Koelkast, vaatwasser, oven en magnetron  
* Elektriciteitsmonitor voor zonnepanelen  
* Slimme stekkers  
* Videodeurbel en beveiligingscamera's  
* Slimme thermostaat met meerdere slimme kamertemperatuursensoren  
* Garagedeuropener  
* Home-entertainmentsystemen en spraakgestuurde tv's  
* Verlichting  
* Fitness- en gezondheidsmeters  

Al deze soorten apparaten hebben sensoren en/of actuatoren en communiceren via het internet. Ik kan via mijn telefoon zien of mijn garagedeur open is en mijn slimme luidspreker vragen deze te sluiten. Ik kan het zelfs instellen op een timer, zodat het 's nachts automatisch sluit als het nog open is. Wanneer mijn deurbel gaat, kan ik via mijn telefoon zien wie er is, waar ik ook ben, en met hen praten via een luidspreker en microfoon in de deurbel. Ik kan mijn bloedsuiker, hartslag en slaappatronen monitoren en patronen in de gegevens zoeken om mijn gezondheid te verbeteren. Ik kan mijn verlichting via de cloud bedienen en in het donker zitten als mijn internetverbinding uitvalt.

---

## 🚀 Uitdaging

Maak een lijst van zoveel mogelijk IoT-apparaten die je in je huis, school of werkplek hebt - er zijn er misschien meer dan je denkt!

## Quiz na de les

[Quiz na de les](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/2)

## Review & Zelfstudie

Lees meer over de voordelen en mislukkingen van consumenten-IoT-projecten. Zoek op nieuwssites naar artikelen over wanneer het misging, zoals privacykwesties, hardwareproblemen of problemen veroorzaakt door gebrek aan connectiviteit.

Enkele voorbeelden:

* Bekijk het Twitter-account **[Internet of Sh*t](https://twitter.com/internetofshit)** *(waarschuwing voor grof taalgebruik)* voor enkele goede voorbeelden van mislukkingen met consumenten-IoT.  
* [c|net - Mijn Apple Watch redde mijn leven: 5 mensen delen hun verhalen](https://www.cnet.com/news/apple-watch-lifesaving-health-features-read-5-peoples-stories/)  
* [c|net - ADT-technicus bekent schuld aan jarenlang bespioneren van camerafeeds van klanten](https://www.cnet.com/news/adt-home-security-technician-pleads-guilty-to-spying-on-customer-camera-feeds-for-years/) *(waarschuwing - niet-consensuele voyeurisme)*  

## Opdracht

[Onderzoek een IoT-project](assignment.md)  

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in de oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.