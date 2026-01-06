<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4fb20273d299dc8d07a8f06c9cd0cdd9",
  "translation_date": "2025-08-27T21:22:45+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/README.md",
  "language_code": "nl"
}
-->
C, uitgesproken als *I-kwadraat-C*, is een multi-controller, multi-perifeer protocol, waarbij elk aangesloten apparaat kan fungeren als controller of perifere apparaat dat communiceert via de I²C-bus (de naam voor een communicatiesysteem dat gegevens overdraagt). Gegevens worden verzonden als geadresseerde pakketten, waarbij elk pakket het adres bevat van het aangesloten apparaat waarvoor het bedoeld is.

> 💁 Dit model werd vroeger aangeduid als master/slave, maar deze terminologie wordt verlaten vanwege de associatie met slavernij. De [Open Source Hardware Association heeft controller/perifeer aangenomen](https://www.oshwa.org/a-resolution-to-redefine-spi-signal-names/), maar je kunt nog steeds verwijzingen naar de oude terminologie tegenkomen.

Apparaten hebben een adres dat wordt gebruikt wanneer ze verbinding maken met de I²C-bus, en dit is meestal hardcoded op het apparaat. Bijvoorbeeld, elk type Grove-sensor van Seeed heeft hetzelfde adres, dus alle lichtsensoren hebben hetzelfde adres, alle knoppen hebben hetzelfde adres dat verschilt van het adres van de lichtsensor. Sommige apparaten hebben manieren om het adres te wijzigen, door jumperinstellingen te veranderen of pinnen aan elkaar te solderen.

I²C heeft een bus bestaande uit 2 hoofddraden, samen met 2 stroomdraden:

| Draad | Naam | Beschrijving |
| ---- | --------- | ----------- |
| SDA | Seriële Data | Deze draad wordt gebruikt om gegevens tussen apparaten te verzenden. |
| SCL | Seriële Klok | Deze draad verzendt een kloksignaal met een snelheid die is ingesteld door de controller. |
| VCC | Voltage common collector | De stroomvoorziening voor de apparaten. Deze is verbonden met de SDA- en SCL-draden om hun stroom te leveren via een pull-up weerstand die het signaal uitschakelt wanneer geen enkel apparaat de controller is. |
| GND | Aarde | Dit biedt een gemeenschappelijke grond voor het elektrische circuit. |

![I2C-bus met 3 apparaten aangesloten op de SDA- en SCL-draden, die een gemeenschappelijke aarddraad delen](../../../../../translated_images/i2c.83da845dde02256bdd462dbe0d5145461416b74930571b89d1ae142841eeb584.nl.png)

Om gegevens te verzenden, zal een apparaat een startconditie afgeven om aan te geven dat het klaar is om gegevens te verzenden. Het wordt dan de controller. De controller verzendt vervolgens het adres van het apparaat waarmee het wil communiceren, samen met de informatie of het gegevens wil lezen of schrijven. Nadat de gegevens zijn verzonden, stuurt de controller een stopconditie om aan te geven dat het klaar is. Hierna kan een ander apparaat de controller worden en gegevens verzenden of ontvangen.

I<sup>2</sup>C heeft snelheidslimieten, met 3 verschillende modi die op vaste snelheden werken. De snelste is de High Speed-modus met een maximale snelheid van 3,4 Mbps (megabits per seconde), hoewel maar weinig apparaten die snelheid ondersteunen. De Raspberry Pi bijvoorbeeld, is beperkt tot de snelle modus op 400 Kbps (kilobits per seconde). De standaardmodus werkt op 100 Kbps.

> 💁 Als je een Raspberry Pi gebruikt met een Grove Base hat als je IoT-hardware, kun je een aantal I<sup>2</sup>C-sockets op de printplaat zien die je kunt gebruiken om te communiceren met I<sup>2</sup>C-sensoren. Analoge Grove-sensoren gebruiken ook I<sup>2</sup>C met een ADC om analoge waarden als digitale gegevens te verzenden, dus de lichtsensor die je gebruikte simuleerde een analoge pin, waarbij de waarde via I<sup>2</sup>C werd verzonden omdat de Raspberry Pi alleen digitale pinnen ondersteunt.

### Universele asynchrone ontvanger-zender (UART)

UART omvat fysieke schakelingen die twee apparaten in staat stellen te communiceren. Elk apparaat heeft 2 communicatiepinnen - verzenden (Tx) en ontvangen (Rx), waarbij de Tx-pin van het eerste apparaat is verbonden met de Rx-pin van het tweede apparaat, en de Tx-pin van het tweede apparaat is verbonden met de Rx-pin van het eerste apparaat. Dit maakt het mogelijk om gegevens in beide richtingen te verzenden.

* Apparaat 1 verzendt gegevens vanaf zijn Tx-pin, die worden ontvangen door apparaat 2 op zijn Rx-pin.
* Apparaat 1 ontvangt gegevens op zijn Rx-pin die worden verzonden door apparaat 2 vanaf zijn Tx-pin.

![UART met de Tx-pin op één chip verbonden met de Rx-pin op een andere, en vice versa](../../../../../translated_images/uart.d0dbd3fb9e3728c6.nl.png)

> 🎓 De gegevens worden één bit tegelijk verzonden, en dit staat bekend als *seriële* communicatie. De meeste besturingssystemen en microcontrollers hebben *seriële poorten*, dat wil zeggen verbindingen die seriële gegevens kunnen verzenden en ontvangen en beschikbaar zijn voor je code.

UART-apparaten hebben een [baudrate](https://wikipedia.org/wiki/Symbol_rate) (ook bekend als symboolsnelheid), wat de snelheid is waarmee gegevens worden verzonden en ontvangen in bits per seconde. Een veelgebruikte baudrate is 9.600, wat betekent dat 9.600 bits (0's en 1's) gegevens per seconde worden verzonden.

UART gebruikt start- en stopbits - dat wil zeggen dat het een startbit verzendt om aan te geven dat het op het punt staat een byte (8 bits) gegevens te verzenden, en vervolgens een stopbit nadat het de 8 bits heeft verzonden.

De snelheid van UART is afhankelijk van de hardware, maar zelfs de snelste implementaties overschrijden niet 6,5 Mbps (megabits per seconde, of miljoenen bits, 0 of 1, verzonden per seconde).

Je kunt UART gebruiken via GPIO-pinnen - je kunt één pin instellen als Tx en een andere als Rx, en deze vervolgens verbinden met een ander apparaat.

> 💁 Als je een Raspberry Pi gebruikt met een Grove Base hat als je IoT-hardware, kun je een UART-socket op de printplaat zien die je kunt gebruiken om te communiceren met sensoren die het UART-protocol gebruiken.

### Seriële perifere interface (SPI)

SPI is ontworpen voor communicatie over korte afstanden, zoals op een microcontroller om te praten met een opslagapparaat zoals flashgeheugen. Het is gebaseerd op een controller/perifeermodel met een enkele controller (meestal de processor van het IoT-apparaat) die interactie heeft met meerdere perifere apparaten. De controller bestuurt alles door een perifere te selecteren en gegevens te verzenden of op te vragen.

> 💁 Net als bij I<sup>2</sup>C zijn de termen controller en perifere recente wijzigingen, dus je kunt de oudere termen nog steeds tegenkomen.

SPI-controllers gebruiken 3 draden, samen met 1 extra draad per perifere. Perifere apparaten gebruiken 4 draden. Deze draden zijn:

| Draad | Naam | Beschrijving |
| ---- | --------- | ----------- |
| COPI | Controller Output, Peripheral Input | Deze draad is voor het verzenden van gegevens van de controller naar de perifere. |
| CIPO | Controller Input, Peripheral Output | Deze draad is voor het verzenden van gegevens van de perifere naar de controller. |
| SCLK | Seriële klok | Deze draad verzendt een kloksignaal met een snelheid ingesteld door de controller. |
| CS   | Chip Select | De controller heeft meerdere draden, één per perifere, en elke draad is verbonden met de CS-draad op de corresponderende perifere. |

![SPI met één controller en twee perifere apparaten](../../../../../translated_images/spi.297431d6f98b386b.nl.png)

De CS-draad wordt gebruikt om één perifere tegelijk te activeren, waarbij communicatie plaatsvindt via de COPI- en CIPO-draden. Wanneer de controller van perifere moet wisselen, deactiveert hij de CS-draad die is verbonden met de momenteel actieve perifere, en activeert vervolgens de draad die is verbonden met de perifere waarmee hij als volgende wil communiceren.

SPI is *full-duplex*, wat betekent dat de controller tegelijkertijd gegevens kan verzenden en ontvangen van dezelfde perifere via de COPI- en CIPO-draden. SPI gebruikt een kloksignaal op de SCLK-draad om de apparaten synchroon te houden, dus in tegenstelling tot direct verzenden via UART heeft het geen start- en stopbits nodig.

Er zijn geen gedefinieerde snelheidslimieten voor SPI, met implementaties die vaak meerdere megabytes aan gegevens per seconde kunnen verzenden.

IoT-ontwikkelingskits ondersteunen vaak SPI via enkele van de GPIO-pinnen. Bijvoorbeeld, op een Raspberry Pi kun je GPIO-pinnen 19, 21, 23, 24 en 26 gebruiken voor SPI.

### Draadloos

Sommige sensoren kunnen communiceren via standaard draadloze protocollen, zoals Bluetooth (voornamelijk Bluetooth Low Energy, of BLE), LoRaWAN (een **Lo**ng **Ra**nge laag energieverbruik netwerkprotocol), of WiFi. Deze maken het mogelijk om sensoren op afstand te gebruiken die niet fysiek verbonden zijn met een IoT-apparaat.

Een voorbeeld hiervan is commerciële bodemvochtigheidssensoren. Deze meten de bodemvochtigheid in een veld en verzenden de gegevens via LoRaWAN naar een hubapparaat, dat de gegevens verwerkt of via het internet verzendt. Dit maakt het mogelijk dat de sensor zich op afstand bevindt van het IoT-apparaat dat de gegevens beheert, waardoor het energieverbruik en de behoefte aan grote WiFi-netwerken of lange kabels worden verminderd.

BLE is populair voor geavanceerde sensoren zoals fitness trackers die op de pols werken. Deze combineren meerdere sensoren en verzenden de sensorgegevens naar een IoT-apparaat, zoals je telefoon, via BLE.

✅ Heb je Bluetooth-sensoren bij je, in je huis of op school? Deze kunnen bijvoorbeeld temperatuursensoren, bezettingssensoren, apparaattrackers en fitnessapparaten zijn.

Een populaire manier voor commerciële apparaten om verbinding te maken is Zigbee. Zigbee gebruikt WiFi om mesh-netwerken tussen apparaten te vormen, waarbij elk apparaat verbinding maakt met zoveel mogelijk nabijgelegen apparaten, waardoor een groot aantal verbindingen ontstaat zoals een spinnenweb. Wanneer een apparaat een bericht naar het internet wil verzenden, kan het dit naar de dichtstbijzijnde apparaten sturen, die het vervolgens doorsturen naar andere nabijgelegen apparaten, enzovoort, totdat het een coördinator bereikt en naar het internet kan worden verzonden.

> 🐝 De naam Zigbee verwijst naar de wiegeldans van honingbijen na hun terugkeer naar de bijenkorf.

## Meet de vochtigheidsniveaus in de bodem

Je kunt het vochtigheidsniveau in de bodem meten met een bodemvochtigheidssensor, een IoT-apparaat en een kamerplant of een nabijgelegen stuk grond.

### Taak - meet bodemvochtigheid

Werk door de relevante gids om bodemvochtigheid te meten met je IoT-apparaat:

* [Arduino - Wio Terminal](wio-terminal-soil-moisture.md)
* [Single-board computer - Raspberry Pi](pi-soil-moisture.md)
* [Single-board computer - Virtueel apparaat](virtual-device-soil-moisture.md)

## Sensorcalibratie

Sensoren vertrouwen op het meten van elektrische eigenschappen zoals weerstand of capaciteit.

> 🎓 Weerstand, gemeten in ohm (Ω), is hoeveel tegenstand er is tegen de elektrische stroom die door iets reist. Wanneer een spanning wordt toegepast op een materiaal, is de hoeveelheid stroom die erdoorheen gaat afhankelijk van de weerstand van het materiaal. Je kunt meer lezen op de [pagina over elektrische weerstand op Wikipedia](https://wikipedia.org/wiki/Electrical_resistance_and_conductance).

> 🎓 Capaciteit, gemeten in farad (F), is het vermogen van een component of circuit om elektrische energie te verzamelen en op te slaan. Je kunt meer lezen over capaciteit op de [capaciteitspagina op Wikipedia](https://wikipedia.org/wiki/Capacitance).

Deze metingen zijn niet altijd nuttig - stel je een temperatuursensor voor die je een meting van 22,5 kΩ geeft! In plaats daarvan moet de gemeten waarde worden omgezet in een bruikbare eenheid door te worden gekalibreerd - dat wil zeggen het matchen van de gemeten waarden aan de gemeten hoeveelheid om nieuwe metingen om te zetten naar de juiste eenheid.

Sommige sensoren worden vooraf gekalibreerd geleverd. Bijvoorbeeld, de temperatuursensor die je in de vorige les gebruikte was al gekalibreerd zodat deze een temperatuurmeting in °C kan teruggeven. In de fabriek zou de eerste sensor die werd gemaakt worden blootgesteld aan een reeks bekende temperaturen en de weerstand worden gemeten. Dit zou dan worden gebruikt om een berekening te maken die kan omzetten van de gemeten waarde in Ω (de eenheid van weerstand) naar °C.

> 💁 De formule om weerstand te berekenen op basis van temperatuur wordt de [Steinhart–Hart-vergelijking](https://wikipedia.org/wiki/Steinhart–Hart_equation) genoemd.

### Calibratie van bodemvochtigheidssensor

Bodemvochtigheid wordt gemeten met behulp van gravimetrische of volumetrische waterinhoud.

* Gravimetrisch is het gewicht van water in een eenheid gewicht van bodem gemeten, als het aantal kilogram water per kilogram droge bodem.
* Volumetrisch is het volume van water in een eenheid volume van bodem gemeten, als het aantal kubieke meter water per kubieke meter droge bodem.

> 🇺🇸 Voor Amerikanen, vanwege de consistentie van de eenheden, kunnen deze worden gemeten in ponden in plaats van kilogrammen of kubieke voet in plaats van kubieke meter.

Bodemvochtigheidssensoren meten elektrische weerstand of capaciteit - dit varieert niet alleen door bodemvochtigheid, maar ook door bodemtype omdat de componenten in de bodem de elektrische eigenschappen kunnen veranderen. Idealiter moeten sensoren worden gekalibreerd - dat wil zeggen het nemen van metingen van de sensor en deze vergelijken met metingen die zijn verkregen met een meer wetenschappelijke aanpak. Bijvoorbeeld, een laboratorium kan de gravimetrische bodemvochtigheid berekenen met behulp van monsters van een specifiek veld die een paar keer per jaar worden genomen, en deze cijfers worden gebruikt om de sensor te kalibreren, waarbij de sensorlezing wordt gekoppeld aan de gravimetrische bodemvochtigheid.

![Een grafiek van spanning vs bodemvochtigheidsinhoud](../../../../../translated_images/soil-moisture-to-voltage.df86d80cda158700.nl.png)

De bovenstaande grafiek laat zien hoe een sensor kan worden gekalibreerd. De spanning wordt vastgelegd voor een bodemmonster dat vervolgens in een laboratorium wordt gemeten door het vochtige gewicht te vergelijken met het droge gewicht (door het gewicht nat te meten, vervolgens te drogen in een oven en het droge gewicht te meten). Zodra een paar metingen zijn genomen, kan dit worden uitgezet op een grafiek en een lijn worden aangepast aan de punten. Deze lijn kan vervolgens worden gebruikt om bodemvochtigheidssensorlezingen die door een IoT-apparaat worden genomen om te zetten in daadwerkelijke bodemvochtigheidsmetingen.

💁 Voor resistieve bodemvochtigheidssensoren neemt de spanning toe naarmate de bodemvochtigheid toeneemt. Voor capacitieve bodemvochtigheidssensoren neemt de spanning af naarmate de bodemvochtigheid toeneemt, dus de grafieken voor deze zouden naar beneden hellen, niet naar boven.

![Een bodemvochtigheidswaarde geïnterpoleerd uit de grafiek](../../../../../translated_images/soil-moisture-to-voltage-with-reading.681cb3e1f8b68caf.nl.png)

De bovenstaande grafiek toont een spanningsmeting van een bodemvochtigheidssensor, en door deze te volgen naar de lijn op de grafiek, kan de daadwerkelijke bodemvochtigheid worden berekend.

Deze aanpak betekent dat de boer slechts een paar laboratoriummetingen voor een veld hoeft te krijgen, waarna ze IoT-apparaten kunnen gebruiken om bodemvochtigheid te meten - wat de tijd om metingen te nemen drastisch versnelt.

---

## 🚀 Uitdaging

Resistieve en capacitieve bodemvochtigheidssensoren hebben een aantal verschillen. Wat zijn deze verschillen, en welk type (indien van toepassing) is het beste voor een boer om te gebruiken? Verandert dit antwoord tussen ontwikkelingslanden en ontwikkelde landen?

## Quiz na de les

[Quiz na de les](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/12)

## Review & Zelfstudie

Lees meer over de hardware en protocollen die door sensoren en actuatoren worden gebruikt:

* [GPIO Wikipedia-pagina](https://wikipedia.org/wiki/General-purpose_input/output)
* [UART Wikipedia-pagina](https://wikipedia.org/wiki/Universal_asynchronous_receiver-transmitter)
* [SPI Wikipedia-pagina](https://wikipedia.org/wiki/Serial_Peripheral_Interface)
* [I<sup>2</sup>C Wikipedia-pagina](https://wikipedia.org/wiki/I²C)
* [Zigbee Wikipedia-pagina](https://wikipedia.org/wiki/Zigbee)

## Opdracht

[Kalibreer je sensor](assignment.md)

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we ons best doen voor nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in de oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.