<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "52ed2bd997d08040f79a1a6ef2bac958",
  "translation_date": "2025-08-27T22:52:01+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/README.md",
  "language_code": "nl"
}
-->
# Locatietracking

![Een schetsnotitie-overzicht van deze les](../../../../../translated_images/nl/lesson-11.9fddbac4b664c6d50ab7ac9bb32f1fc3f945f03760e72f7f43938073762fb017.jpg)

> Schetsnotitie door [Nitya Narasimhan](https://github.com/nitya). Klik op de afbeelding voor een grotere versie.

## Quiz voorafgaand aan de les

[Quiz voorafgaand aan de les](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/21)

## Introductie

Het belangrijkste proces om voedsel van een boer naar een consument te brengen, omvat het laden van dozen met producten op vrachtwagens, schepen, vliegtuigen of andere commerciële transportvoertuigen en het afleveren van het voedsel ergens - ofwel direct bij een klant, ofwel bij een centraal knooppunt of magazijn voor verwerking. Het hele end-to-end proces van boer tot consument maakt deel uit van een proces dat de *supply chain* wordt genoemd. De onderstaande video van de W. P. Carey School of Business van de Arizona State University bespreekt het idee van de supply chain en hoe deze wordt beheerd in meer detail.

[![Wat is Supply Chain Management? Een video van de W. P. Carey School of Business van de Arizona State University](https://img.youtube.com/vi/Mi1QBxVjZAw/0.jpg)](https://www.youtube.com/watch?v=Mi1QBxVjZAw)

> 🎥 Klik op de afbeelding hierboven om een video te bekijken

Het toevoegen van IoT-apparaten kan je supply chain drastisch verbeteren, waardoor je beter kunt beheren waar items zich bevinden, transport en goederenverwerking beter kunt plannen en sneller kunt reageren op problemen.

Bij het beheren van een wagenpark, zoals vrachtwagens, is het handig om te weten waar elk voertuig zich op een bepaald moment bevindt. Voertuigen kunnen worden uitgerust met GPS-sensoren die hun locatie naar IoT-systemen sturen, zodat de eigenaren hun locatie kunnen bepalen, de afgelegde route kunnen zien en weten wanneer ze op hun bestemming aankomen. De meeste voertuigen opereren buiten WiFi-dekking, dus ze gebruiken mobiele netwerken om dit soort gegevens te verzenden. Soms is de GPS-sensor ingebouwd in complexere IoT-apparaten, zoals elektronische logboeken. Deze apparaten volgen hoe lang een vrachtwagen onderweg is om ervoor te zorgen dat chauffeurs voldoen aan de lokale wetgeving over werkuren.

In deze les leer je hoe je de locatie van een voertuig kunt volgen met behulp van een Global Positioning System (GPS)-sensor.

In deze les behandelen we:

* [Verbonden voertuigen](../../../../../3-transport/lessons/1-location-tracking)
* [Geospatiale coördinaten](../../../../../3-transport/lessons/1-location-tracking)
* [Global Positioning Systems (GPS)](../../../../../3-transport/lessons/1-location-tracking)
* [GPS-sensorgegevens lezen](../../../../../3-transport/lessons/1-location-tracking)
* [NMEA GPS-gegevens](../../../../../3-transport/lessons/1-location-tracking)
* [GPS-sensorgegevens decoderen](../../../../../3-transport/lessons/1-location-tracking)

## Verbonden voertuigen

IoT transformeert de manier waarop goederen worden vervoerd door wagenparken van *verbonden voertuigen* te creëren. Deze voertuigen zijn verbonden met centrale IT-systemen en rapporteren informatie over hun locatie en andere sensorgegevens. Het hebben van een vloot van verbonden voertuigen biedt een breed scala aan voordelen:

* Locatietracking - je kunt op elk moment bepalen waar een voertuig zich bevindt, waardoor je:

  * Waarschuwingen kunt ontvangen wanneer een voertuig bijna op een bestemming aankomt, zodat een team zich kan voorbereiden op het lossen
  * Gestolen voertuigen kunt lokaliseren
  * Locatie- en routedata kunt combineren met verkeersproblemen om voertuigen halverwege de reis om te leiden
  * Voldoet aan belastingregels. Sommige landen belasten voertuigen op basis van het aantal gereden kilometers op openbare wegen (zoals [Nieuw-Zeelands RUC](https://www.nzta.govt.nz/vehicles/licensing-rego/road-user-charges/)), dus weten wanneer een voertuig op openbare wegen versus privéwegen rijdt, maakt het gemakkelijker om de verschuldigde belasting te berekenen.
  * Weet waar je onderhoudsteams naartoe moet sturen in geval van pech

* Bestuurderstelemetrie - ervoor zorgen dat bestuurders zich houden aan snelheidslimieten, bochten nemen met gepaste snelheid, vroeg en efficiënt remmen en veilig rijden. Verbonden voertuigen kunnen ook camera's hebben om incidenten vast te leggen. Dit kan worden gekoppeld aan verzekeringen, met lagere tarieven voor goede bestuurders.

* Naleving van rijtijden - ervoor zorgen dat bestuurders alleen rijden binnen hun wettelijk toegestane uren op basis van de tijden waarop ze de motor aan- en uitzetten.

Deze voordelen kunnen worden gecombineerd - bijvoorbeeld, het combineren van naleving van rijtijden met locatietracking om bestuurders om te leiden als ze hun bestemming niet binnen hun toegestane rijtijden kunnen bereiken. Deze kunnen ook worden gecombineerd met andere voertuigspecifieke telemetrie, zoals temperatuurgegevens van temperatuurgecontroleerde vrachtwagens, zodat voertuigen kunnen worden omgeleid als hun huidige route betekent dat goederen niet op temperatuur kunnen worden gehouden.

> 🎓 Logistiek is het proces van het vervoeren van goederen van de ene plaats naar de andere, zoals van een boerderij naar een supermarkt via een of meer magazijnen. Een boer verpakt dozen met tomaten die op een vrachtwagen worden geladen, afgeleverd bij een centraal magazijn en vervolgens op een tweede vrachtwagen worden geplaatst die mogelijk een mix van verschillende soorten producten bevat die vervolgens naar een supermarkt worden geleverd.

Het kernonderdeel van voertuigtracking is GPS - sensoren die hun locatie overal op aarde kunnen bepalen. In deze les leer je hoe je een GPS-sensor gebruikt, te beginnen met het leren definiëren van een locatie op aarde.

## Geospatiale coördinaten

Geospatiale coördinaten worden gebruikt om punten op het aardoppervlak te definiëren, vergelijkbaar met hoe coördinaten kunnen worden gebruikt om een pixel op een computerscherm te tekenen of steken te positioneren bij borduren. Voor een enkel punt heb je een paar coördinaten. Bijvoorbeeld, de Microsoft Campus in Redmond, Washington, VS bevindt zich op 47.6423109, -122.1390293.

### Breedte- en lengtegraden

De aarde is een bol - een driedimensionale cirkel. Hierdoor worden punten gedefinieerd door deze in 360 graden te verdelen, hetzelfde als de geometrie van cirkels. Breedtegraad meet het aantal graden van noord naar zuid, lengtegraad meet het aantal graden van oost naar west.

> 💁 Niemand weet echt de oorspronkelijke reden waarom cirkels in 360 graden zijn verdeeld. De [pagina over graden (hoek) op Wikipedia](https://wikipedia.org/wiki/Degree_(angle)) behandelt enkele van de mogelijke redenen.

![Lijnen van breedtegraad van 90° op de Noordpool, 45° halverwege tussen de Noordpool en de evenaar, 0° op de evenaar, -45° halverwege tussen de evenaar en de Zuidpool, en -90° op de Zuidpool](../../../../../translated_images/nl/latitude-lines.11d8d91dfb2014a57437272d7db7fd6607243098e8685f06e0c5f1ec984cb7eb.png)

Breedtegraad wordt gemeten met lijnen die de aarde omcirkelen en parallel lopen aan de evenaar, waarbij het noordelijk en zuidelijk halfrond elk in 90° worden verdeeld. De evenaar ligt op 0°, de Noordpool op 90°, ook wel 90° Noord genoemd, en de Zuidpool op -90°, of 90° Zuid.

Lengtegraad wordt gemeten als het aantal graden gemeten van oost naar west. De oorsprong van 0° lengtegraad wordt de *Prime Meridian* genoemd en werd in 1884 gedefinieerd als een lijn van de Noordpool naar de Zuidpool die door het [British Royal Observatory in Greenwich, Engeland](https://wikipedia.org/wiki/Royal_Observatory,_Greenwich) loopt.

![Lijnen van lengtegraad die gaan van -180° ten westen van de Prime Meridian, naar 0° op de Prime Meridian, tot 180° ten oosten van de Prime Meridian](../../../../../translated_images/nl/longitude-meridians.ab4ef1c91c064586b0185a3c8d39e585903696c6a7d28c098a93a629cddb5d20.png)

> 🎓 Een meridiaan is een denkbeeldige rechte lijn die van de Noordpool naar de Zuidpool loopt en een halve cirkel vormt.

Om de lengtegraad van een punt te meten, meet je het aantal graden rond de evenaar van de Prime Meridian naar een meridiaan die door dat punt loopt. Lengtegraad gaat van -180°, of 180° West, via 0° op de Prime Meridian, tot 180°, of 180° Oost. 180° en -180° verwijzen naar hetzelfde punt, de antimeridiaan of 180e meridiaan. Dit is een meridiaan aan de andere kant van de aarde ten opzichte van de Prime Meridian.

> 💁 De antimeridiaan moet niet worden verward met de Internationale Datumgrens, die zich ongeveer op dezelfde positie bevindt, maar geen rechte lijn is en varieert om rond geopolitieke grenzen te passen.

✅ Doe wat onderzoek: Probeer de breedte- en lengtegraad van je huidige locatie te vinden.

### Graden, minuten en seconden versus decimale graden

Traditioneel werden metingen van graden van breedte- en lengtegraad gedaan met behulp van sexagesimale nummering, of basis-60, een nummersysteem dat werd gebruikt door de oude Babyloniërs die de eerste metingen en registraties van tijd en afstand deden. Je gebruikt waarschijnlijk elke dag sexagesimaal zonder het te beseffen - door uren in 60 minuten en minuten in 60 seconden te verdelen.

Lengte- en breedtegraden worden gemeten in graden, minuten en seconden, waarbij één minuut 1/60 van een graad is en 1 seconde 1/60 minuut.

Bijvoorbeeld, op de evenaar:

* 1° breedtegraad is **111,3 kilometer**
* 1 minuut breedtegraad is 111,3/60 = **1,855 kilometer**
* 1 seconde breedtegraad is 1,855/60 = **0,031 kilometer**

Het symbool voor een minuut is een enkele aanhalingsteken, voor een seconde een dubbele aanhalingsteken. 2 graden, 17 minuten en 43 seconden bijvoorbeeld, wordt geschreven als 2°17'43". Delen van seconden worden als decimalen gegeven, bijvoorbeeld een halve seconde is 0°0'0,5".

Computers werken niet in basis-60, dus deze coördinaten worden in decimale graden gegeven bij het gebruik van GPS-gegevens in de meeste computersystemen. Bijvoorbeeld, 2°17'43" is 2,295277. Het graadsymbool wordt meestal weggelaten.

Coördinaten voor een punt worden altijd gegeven als `breedtegraad, lengtegraad`, dus het eerder genoemde voorbeeld van de Microsoft Campus op 47.6423109,-122.117198 heeft:

* Een breedtegraad van 47.6423109 (47.6423109 graden ten noorden van de evenaar)
* Een lengtegraad van -122.1390293 (122.1390293 graden ten westen van de Prime Meridian).

![De Microsoft Campus op 47.6423109,-122.117198](../../../../../translated_images/nl/microsoft-gps-location-world.a321d481b010f6adfcca139b2ba0adc53b79f58a540495b8e2ce7f779ea64bfe.png)

## Global Positioning Systems (GPS)

GPS-systemen gebruiken meerdere satellieten die rond de aarde draaien om je positie te bepalen. Je hebt waarschijnlijk GPS-systemen gebruikt zonder het te weten - om je locatie te vinden in een kaartapp op je telefoon, zoals Apple Maps of Google Maps, om te zien waar je rit is in een app zoals Uber of Lyft, of bij het gebruik van satellietnavigatie (sat-nav) in je auto.

> 🎓 De satellieten in 'satellietnavigatie' zijn GPS-satellieten!

GPS-systemen werken door een aantal satellieten die een signaal uitzenden met de huidige positie van elke satelliet en een nauwkeurige tijdstempel. Deze signalen worden via radiogolven verzonden en worden gedetecteerd door een antenne in de GPS-sensor. Een GPS-sensor detecteert deze signalen en meet met behulp van de huidige tijd hoe lang het duurde voordat het signaal de sensor bereikte vanaf de satelliet. Omdat de snelheid van radiogolven constant is, kan de GPS-sensor met behulp van de verzonden tijdstempel berekenen hoe ver de sensor van de satelliet verwijderd is. Door de gegevens van minstens 3 satellieten te combineren met de verzonden posities, kan de GPS-sensor zijn locatie op aarde bepalen.

> 💁 GPS-sensoren hebben antennes nodig om radiogolven te detecteren. De antennes die zijn ingebouwd in vrachtwagens en auto's met ingebouwde GPS zijn zo geplaatst dat ze een goed signaal krijgen, meestal op de voorruit of het dak. Als je een apart GPS-systeem gebruikt, zoals een smartphone of een IoT-apparaat, moet je ervoor zorgen dat de antenne die in het GPS-systeem of de telefoon is ingebouwd een vrij zicht op de lucht heeft, bijvoorbeeld door deze op je voorruit te monteren.

![Door de afstand van de sensor tot meerdere satellieten te kennen, kan de locatie worden berekend](../../../../../translated_images/nl/gps-satellites.04acf1148fe25fbf1586bc2e8ba698e8d79b79a50c36824b38417dd13372b90f.png)

GPS-satellieten draaien rond de aarde en bevinden zich niet op een vaste plek boven de sensor, dus locatiegegevens omvatten hoogte boven zeeniveau naast breedte- en lengtegraad.

GPS had vroeger beperkingen op nauwkeurigheid die werden opgelegd door het Amerikaanse leger, waardoor de nauwkeurigheid werd beperkt tot ongeveer 5 meter. Deze beperking werd in 2000 opgeheven, waardoor een nauwkeurigheid van 30 centimeter mogelijk werd. Het is echter niet altijd mogelijk om deze nauwkeurigheid te bereiken vanwege interferentie met de signalen.

✅ Als je een smartphone hebt, open dan de kaartapp en kijk hoe nauwkeurig je locatie is. Het kan even duren voordat je telefoon meerdere satellieten detecteert om een nauwkeurigere locatie te krijgen.
💁 De satellieten bevatten atoomklokken die ongelooflijk nauwkeurig zijn, maar ze drijven dagelijks 38 microseconden (0,0000038 seconden) af in vergelijking met atoomklokken op aarde. Dit komt doordat tijd langzamer gaat naarmate snelheid toeneemt, zoals voorspeld door Einstein's theorieën van speciale en algemene relativiteit - de satellieten bewegen sneller dan de rotatie van de aarde. Deze afwijking is gebruikt om de voorspellingen van speciale en algemene relativiteit te bewijzen en moet worden gecorrigeerd in het ontwerp van GPS-systemen. Letterlijk loopt de tijd langzamer op een GPS-satelliet.
GPS-systemen zijn ontwikkeld en geïmplementeerd door verschillende landen en politieke unies, waaronder de VS, Rusland, Japan, India, de EU en China. Moderne GPS-sensoren kunnen verbinding maken met de meeste van deze systemen om sneller en nauwkeuriger posities te bepalen.

> 🎓 De groepen satellieten in elke implementatie worden constellaties genoemd.

## GPS-sensorgegevens lezen

De meeste GPS-sensoren verzenden GPS-gegevens via UART.

> ⚠️ UART werd behandeld in [project 2, les 2](../../../2-farm/lessons/2-detect-soil-moisture/README.md#universal-asynchronous-receiver-transmitter-uart). Raadpleeg die les indien nodig.

Je kunt een GPS-sensor op je IoT-apparaat gebruiken om GPS-gegevens te verkrijgen.

### Taak - verbind een GPS-sensor en lees GPS-gegevens

Volg de relevante handleiding om GPS-gegevens te lezen met je IoT-apparaat:

* [Arduino - Wio Terminal](wio-terminal-gps-sensor.md)
* [Single-board computer - Raspberry Pi](pi-gps-sensor.md)
* [Single-board computer - Virtueel apparaat](virtual-device-gps-sensor.md)

## NMEA GPS-gegevens

Wanneer je je code uitvoerde, zag je waarschijnlijk wat op het eerste gezicht onbegrijpelijke tekst leek. Dit zijn standaard GPS-gegevens, en alles heeft een betekenis.

GPS-sensoren geven gegevens uit met behulp van NMEA-berichten, volgens de NMEA 0183-standaard. NMEA is een acroniem voor de [National Marine Electronics Association](https://www.nmea.org), een in de VS gevestigde handelsorganisatie die standaarden vaststelt voor communicatie tussen maritieme elektronica.

> 💁 Deze standaard is eigendom en kost minstens US$2.000, maar er is genoeg informatie in het publieke domein beschikbaar, zodat het grootste deel van de standaard is gereverse-engineerd en kan worden gebruikt in open source- en andere niet-commerciële code.

Deze berichten zijn tekstgebaseerd. Elk bericht bestaat uit een *zin* die begint met een `$`-teken, gevolgd door 2 tekens om de bron van het bericht aan te geven (bijvoorbeeld GP voor het Amerikaanse GPS-systeem, GN voor GLONASS, het Russische GPS-systeem), en 3 tekens om het type bericht aan te geven. De rest van het bericht bestaat uit velden die gescheiden zijn door komma's en eindigen met een nieuwe regel.

Enkele typen berichten die kunnen worden ontvangen zijn:

| Type | Beschrijving |
| ---- | ----------- |
| GGA | GPS Fix Data, inclusief de breedtegraad, lengtegraad en hoogte van de GPS-sensor, samen met het aantal satellieten dat wordt gebruikt om deze fix te berekenen. |
| ZDA | De huidige datum en tijd, inclusief de lokale tijdzone |
| GSV | Details van de zichtbare satellieten - gedefinieerd als de satellieten waarvan de GPS-sensor signalen kan detecteren |

> 💁 GPS-gegevens bevatten tijdstempels, zodat je IoT-apparaat de tijd kan verkrijgen van een GPS-sensor, in plaats van te vertrouwen op een NTP-server of interne realtime klok.

Het GGA-bericht bevat de huidige locatie in het `(dd)dmm.mmmm`-formaat, samen met een enkel teken om de richting aan te geven. De `d` in het formaat staat voor graden, de `m` voor minuten, met seconden als decimalen van minuten. Bijvoorbeeld, 2°17'43" wordt 217.716666667 - 2 graden, 17.716666667 minuten.

Het richtingsteken kan `N` of `S` zijn voor breedtegraad om noord of zuid aan te geven, en `E` of `W` voor lengtegraad om oost of west aan te geven. Bijvoorbeeld, een breedtegraad van 2°17'43" zou een richtingsteken van `N` hebben, -2°17'43" zou een richtingsteken van `S` hebben.

Bijvoorbeeld - de NMEA-zin `$GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67`

* Het breedtegraadgedeelte is `4738.538654,N`, wat wordt omgerekend naar 47.6423109 in decimale graden. `4738.538654` is 47.6423109, en de richting is `N` (noord), dus het is een positieve breedtegraad.

* Het lengtegraadgedeelte is `12208.341758,W`, wat wordt omgerekend naar -122.1390293 in decimale graden. `12208.341758` is 122.1390293°, en de richting is `W` (west), dus het is een negatieve lengtegraad.

## GPS-sensorgegevens decoderen

In plaats van de ruwe NMEA-gegevens te gebruiken, is het beter om deze te decoderen naar een bruikbaarder formaat. Er zijn meerdere open-sourcebibliotheken beschikbaar die je kunnen helpen om nuttige gegevens uit de ruwe NMEA-berichten te halen.

### Taak - decodeer GPS-sensorgegevens

Volg de relevante handleiding om GPS-sensorgegevens te decoderen met je IoT-apparaat:

* [Arduino - Wio Terminal](wio-terminal-gps-decode.md)
* [Single-board computer - Raspberry Pi/Virtueel IoT-apparaat](single-board-computer-gps-decode.md)

---

## 🚀 Uitdaging

Schrijf je eigen NMEA-decoder! In plaats van te vertrouwen op bibliotheken van derden om NMEA-zinnen te decoderen, kun je je eigen decoder schrijven om breedte- en lengtegraad uit NMEA-zinnen te halen?

## Quiz na de les

[Quiz na de les](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/22)

## Herziening & Zelfstudie

* Lees meer over geospatiale coördinaten op de [pagina over het geografisch coördinatensysteem op Wikipedia](https://wikipedia.org/wiki/Geographic_coordinate_system).
* Lees over de nulmeridianen op andere hemellichamen dan de aarde op de [pagina over de nulmeridiaan op Wikipedia](https://wikipedia.org/wiki/Prime_meridian#Prime_meridian_on_other_planetary_bodies).
* Onderzoek de verschillende GPS-systemen van verschillende overheden en politieke unies zoals de EU, Japan, Rusland, India en de VS.

## Opdracht

[Onderzoek andere GPS-gegevens](assignment.md)

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we ons best doen voor nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in de oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.