C, udtalt *I-squared-C*, er en multi-controller, multi-periferi protokol, hvor enhver tilsluttet enhed kan fungere som enten controller eller periferi og kommunikere over I²C-bussen (navnet for et kommunikationssystem, der overfører data). Data sendes som adresserede pakker, hvor hver pakke indeholder adressen på den tilsluttede enhed, den er beregnet til.

> 💁 Denne model blev tidligere omtalt som master/slave, men denne terminologi er ved at blive udfaset på grund af dens association med slaveri. [Open Source Hardware Association har vedtaget controller/periferi](https://www.oshwa.org/a-resolution-to-redefine-spi-signal-names/), men du kan stadig støde på referencer til den gamle terminologi.

Enheder har en adresse, der bruges, når de tilsluttes I²C-bussen, og denne adresse er normalt hardkodet på enheden. For eksempel har hver type Grove-sensor fra Seeed den samme adresse, så alle lyssensorer har den samme adresse, og alle knapper har en anden adresse, der adskiller sig fra lyssensorens adresse. Nogle enheder har måder at ændre adressen på, ved at ændre jumperindstillinger eller lodde pins sammen.

I²C har en bus bestående af 2 hovedledninger samt 2 strømledninger:

| Ledning | Navn | Beskrivelse |
| ---- | --------- | ----------- |
| SDA | Serial Data | Denne ledning bruges til at sende data mellem enheder. |
| SCL | Serial Clock | Denne ledning sender et clock-signal med en hastighed, der er indstillet af controlleren. |
| VCC | Voltage common collector | Strømforsyningen til enhederne. Denne er forbundet til SDA- og SCL-ledningerne for at levere deres strøm via en pull-up modstand, der slukker signalet, når ingen enhed er controller. |
| GND | Ground | Dette giver en fælles jordforbindelse for det elektriske kredsløb. |

![I2C-bus med 3 enheder forbundet til SDA- og SCL-ledningerne, der deler en fælles jordledning](../../../../../translated_images/da/i2c.83da845dde02256b.webp)

For at sende data vil en enhed udsende en startbetingelse for at vise, at den er klar til at sende data. Den vil derefter blive controller. Controlleren sender derefter adressen på den enhed, den ønsker at kommunikere med, sammen med information om, hvorvidt den vil læse eller skrive data. Når dataene er blevet overført, sender controlleren en stopbetingelse for at indikere, at den er færdig. Herefter kan en anden enhed blive controller og sende eller modtage data.

2</sup>C har hastighedsbegrænsninger med 3 forskellige tilstande, der kører med faste hastigheder. Den hurtigste er High Speed-tilstand med en maksimal hastighed på 3,4 Mbps (megabit per sekund), selvom meget få enheder understøtter denne hastighed. Raspberry Pi er for eksempel begrænset til fast mode ved 400 Kbps (kilobit per sekund). Standardtilstand kører ved 100 Kbps.

> 💁 Hvis du bruger en Raspberry Pi med en Grove Base hat som din IoT-hardware, vil du kunne se en række I<sup>2</sup>C-stik på kortet, som du kan bruge til at kommunikere med I<sup>2</sup>C-sensorer. Analoge Grove-sensorer bruger også I<sup>2</sup>C med en ADC til at sende analoge værdier som digitale data, så lyssensoren, du brugte, simulerede en analog pin, hvor værdien blev sendt over I<sup>2</sup>C, da Raspberry Pi kun understøtter digitale pins.

### Universal asynkron modtager-transmitter (UART)

UART involverer fysisk kredsløb, der gør det muligt for to enheder at kommunikere. Hver enhed har 2 kommunikationspins - transmit (Tx) og receive (Rx), hvor Tx-pinnen på den første enhed er forbundet til Rx-pinnen på den anden, og Tx-pinnen på den anden enhed er forbundet til Rx-pinnen på den første. Dette gør det muligt at sende data i begge retninger.

* Enhed 1 sender data fra sin Tx-pin, som modtages af enhed 2 på dens Rx-pin
* Enhed 1 modtager data på sin Rx-pin, som sendes af enhed 2 fra dens Tx-pin

![UART med Tx-pinnen på én chip forbundet til Rx-pinnen på en anden og omvendt](../../../../../translated_images/da/uart.d0dbd3fb9e3728c6.webp)

> 🎓 Data sendes én bit ad gangen, og dette kaldes *seriel* kommunikation. De fleste operativsystemer og mikrocontrollere har *serielle porte*, det vil sige forbindelser, der kan sende og modtage serielle data, som er tilgængelige for din kode.

UART-enheder har en [baudrate](https://wikipedia.org/wiki/Symbol_rate) (også kendt som symbolrate), som er den hastighed, data sendes og modtages med i bits per sekund. En almindelig baudrate er 9.600, hvilket betyder, at 9.600 bits (0'er og 1-taller) data sendes hvert sekund.

UART bruger start- og stopbits - det vil sige, at den sender et startbit for at indikere, at den er ved at sende en byte (8 bits) data, og derefter et stopbit, når de 8 bits er sendt.

UART-hastighed afhænger af hardware, men selv de hurtigste implementeringer overstiger ikke 6,5 Mbps (megabit per sekund, eller millioner af bits, 0 eller 1, sendt per sekund).

Du kan bruge UART over GPIO-pins - du kan sætte én pin som Tx og en anden som Rx og derefter forbinde disse til en anden enhed.

> 💁 Hvis du bruger en Raspberry Pi med en Grove Base hat som din IoT-hardware, vil du kunne se et UART-stik på kortet, som du kan bruge til at kommunikere med sensorer, der bruger UART-protokollen.

### Serial Peripheral Interface (SPI)

SPI er designet til kommunikation over korte afstande, såsom på en mikrocontroller til at tale med en lagringsenhed som flashhukommelse. Det er baseret på en controller/periferimodel med en enkelt controller (normalt processoren i IoT-enheden), der interagerer med flere perifere enheder. Controlleren styrer alt ved at vælge en periferienhed og sende eller anmode om data.

> 💁 Ligesom I<sup>2</sup>C er termerne controller og periferienhed nyere ændringer, så du kan støde på de ældre termer stadig i brug.

SPI-controllere bruger 3 ledninger sammen med 1 ekstra ledning per periferienhed. Periferienheder bruger 4 ledninger. Disse ledninger er:

| Ledning | Navn | Beskrivelse |
| ---- | --------- | ----------- |
| COPI | Controller Output, Peripheral Input | Denne ledning bruges til at sende data fra controlleren til periferienheden. |
| CIPO | Controller Input, Peripheral Output | Denne ledning bruges til at sende data fra periferienheden til controlleren. |
| SCLK | Seriel Clock | Denne ledning sender et clock-signal med en hastighed, der er indstillet af controlleren. |
| CS   | Chip Select | Controlleren har flere ledninger, én per periferienhed, og hver ledning forbinder til CS-ledningen på den tilsvarende periferienhed. |

![SPI med én controller og to periferienheder](../../../../../translated_images/da/spi.297431d6f98b386b.webp)

CS-ledningen bruges til at aktivere én periferienhed ad gangen og kommunikere over COPI- og CIPO-ledningerne. Når controlleren skal skifte periferienhed, deaktiverer den CS-ledningen, der er forbundet til den aktuelt aktive periferienhed, og aktiverer derefter ledningen, der er forbundet til den periferienhed, den ønsker at kommunikere med næste gang.

SPI er *fuld-dupleks*, hvilket betyder, at controlleren kan sende og modtage data samtidig fra den samme periferienhed ved hjælp af COPI- og CIPO-ledningerne. SPI bruger et clock-signal på SCLK-ledningen til at holde enhederne synkroniserede, så i modsætning til at sende direkte over UART, behøver den ikke start- og stopbits.

Der er ingen definerede hastighedsgrænser for SPI, og implementeringer kan ofte transmittere flere megabytes data per sekund.

IoT-udviklingssæt understøtter ofte SPI over nogle af GPIO-pinsene. For eksempel kan du på en Raspberry Pi bruge GPIO-pins 19, 21, 23, 24 og 26 til SPI.

### Trådløs

Nogle sensorer kan kommunikere over standard trådløse protokoller, såsom Bluetooth (primært Bluetooth Low Energy, eller BLE), LoRaWAN (en **Lo**ng **Ra**nge lavenergi-netværksprotokol) eller WiFi. Disse gør det muligt for fjernsensorer ikke fysisk at være forbundet til en IoT-enhed.

Et eksempel er kommercielle jordfugtighedssensorer. Disse måler jordfugtighed i en mark og sender derefter dataene over LoRaWAN til en hub-enhed, som behandler dataene eller sender dem over internettet. Dette gør det muligt for sensoren at være væk fra IoT-enheden, der administrerer dataene, hvilket reducerer strømforbruget og behovet for store WiFi-netværk eller lange kabler.

BLE er populært til avancerede sensorer som fitness-trackere, der bæres på håndleddet. Disse kombinerer flere sensorer og sender sensordataene til en IoT-enhed, som din telefon, via BLE.

✅ Har du nogen Bluetooth-sensorer på dig, i dit hjem eller på din skole? Disse kan omfatte temperatursensorer, tilstedeværelsessensorer, enhedssporere og fitness-enheder.

En populær måde for kommercielle enheder at forbinde på er Zigbee. Zigbee bruger WiFi til at danne mesh-netværk mellem enheder, hvor hver enhed forbinder til så mange nærliggende enheder som muligt og danner et stort antal forbindelser som et spindelvæv. Når en enhed ønsker at sende en besked til internettet, kan den sende den til de nærmeste enheder, som derefter videresender den til andre nærliggende enheder og så videre, indtil den når en koordinator og kan sendes til internettet.

> 🐝 Navnet Zigbee refererer til honningbiernes dans, når de vender tilbage til bikuben.

## Mål fugtighedsniveauet i jord

Du kan måle fugtighedsniveauet i jord ved hjælp af en jordfugtighedssensor, en IoT-enhed og en stueplante eller et nærliggende jordstykke.

### Opgave - mål jordfugtighed

Følg den relevante vejledning for at måle jordfugtighed ved hjælp af din IoT-enhed:

* [Arduino - Wio Terminal](wio-terminal-soil-moisture.md)
* [Single-board computer - Raspberry Pi](pi-soil-moisture.md)
* [Single-board computer - Virtuel enhed](virtual-device-soil-moisture.md)

## Sensor kalibrering

Sensorer er afhængige af at måle elektriske egenskaber som modstand eller kapacitans.

> 🎓 Modstand, målt i ohm (Ω), er hvor meget modstand der er mod den elektriske strøm, der passerer gennem noget. Når en spænding påføres et materiale, afhænger mængden af strøm, der passerer igennem, af materialets modstand. Du kan læse mere på [siden om elektrisk modstand på Wikipedia](https://wikipedia.org/wiki/Electrical_resistance_and_conductance).

> 🎓 Kapacitans, målt i farad (F), er en komponent eller et kredsløbs evne til at opsamle og lagre elektrisk energi. Du kan læse mere om kapacitans på [siden om kapacitans på Wikipedia](https://wikipedia.org/wiki/Capacitance).

Disse målinger er ikke altid nyttige - forestil dig en temperatursensor, der gav dig en måling på 22,5 kΩ! I stedet skal den målte værdi konverteres til en brugbar enhed ved at blive kalibreret - det vil sige at matche de målte værdier til den målte størrelse for at gøre det muligt at konvertere nye målinger til den rigtige enhed.

Nogle sensorer leveres forkalibrerede. For eksempel var temperatursensoren, du brugte i den sidste lektion, allerede kalibreret, så den kan returnere en temperaturmåling i °C. På fabrikken ville den første sensor, der blev skabt, blive udsat for en række kendte temperaturer, og modstanden ville blive målt. Dette ville derefter blive brugt til at opbygge en beregning, der kan konvertere fra den målte værdi i Ω (modstandens enhed) til °C.

> 💁 Formlen til at beregne modstand ud fra temperatur kaldes [Steinhart–Hart-ligningen](https://wikipedia.org/wiki/Steinhart–Hart_equation).

### Kalibrering af jordfugtighedssensor

Jordfugtighed måles ved hjælp af gravimetrisk eller volumetrisk vandindhold.

* Gravimetrisk er vægten af vand i en enhedsvægt af jord målt som antallet af kilogram vand per kilogram tør jord
* Volumetrisk er volumenet af vand i en enhedsvolumen af jord målt som antallet af kubikmeter vand per kubikmeter tør jord

> 🇺🇸 For amerikanere, på grund af enhedernes konsistens, kan disse måles i pund i stedet for kilogram eller kubikfod i stedet for kubikmeter.

Jordfugtighedssensorer måler elektrisk modstand eller kapacitans - dette varierer ikke kun med jordfugtighed, men også jordtype, da komponenterne i jorden kan ændre dens elektriske egenskaber. Ideelt set bør sensorer kalibreres - det vil sige at tage aflæsninger fra sensoren og sammenligne dem med målinger fundet ved hjælp af en mere videnskabelig tilgang. For eksempel kan et laboratorium beregne den gravimetriske jordfugtighed ved hjælp af prøver fra et specifikt felt taget et par gange om året, og disse tal kan bruges til at kalibrere sensoren, så sensoraflæsningen matcher den gravimetriske jordfugtighed.

![En graf over spænding vs jordfugtighedsindhold](../../../../../translated_images/da/soil-moisture-to-voltage.df86d80cda158700.webp)

Grafen ovenfor viser, hvordan man kalibrerer en sensor. Spændingen registreres for en jordprøve, der derefter måles i et laboratorium ved at sammenligne den fugtige vægt med den tørre vægt (ved at måle vægten våd, derefter tørre i en ovn og måle tør). Når der er taget et par aflæsninger, kan disse plottes på en graf, og en linje kan tilpasses punkterne. Denne linje kan derefter bruges til at konvertere jordfugtighedssensoraflæsninger taget af en IoT-enhed til faktiske jordfugtighedsmålinger.

💁 For resistive jordfugtighedssensorer stiger spændingen, når jordfugtigheden stiger. For kapacitive jordfugtighedssensorer falder spændingen, når jordfugtigheden stiger, så graferne for disse ville hælde nedad, ikke opad.

![En jordfugtighedsværdi interpoleret fra grafen](../../../../../translated_images/da/soil-moisture-to-voltage-with-reading.681cb3e1f8b68caf.webp)

Grafen ovenfor viser en spændingsaflæsning fra en jordfugtighedssensor, og ved at følge den til linjen på grafen kan den faktiske jordfugtighed beregnes.

Denne tilgang betyder, at landmanden kun behøver at få et par laboratoriemålinger for et felt, og derefter kan de bruge IoT-enheder til at måle jordfugtighed - hvilket drastisk fremskynder tiden til at tage målinger.

---

## 🚀 Udfordring

Resistive og kapacitive jordfugtighedssensorer har en række forskelle. Hvad er disse forskelle, og hvilken type (hvis nogen) er bedst for en landmand at bruge? Ændrer dette svar sig mellem udviklingslande og udviklede lande?

## Quiz efter lektionen

[Quiz efter lektionen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/12)

## Gennemgang & Selvstudie

Læs om hardware og protokoller, der bruges af sensorer og aktuatorer:

* [GPIO Wikipedia-side](https://wikipedia.org/wiki/General-purpose_input/output)
* [UART Wikipedia-side](https://wikipedia.org/wiki/Universal_asynchronous_receiver-transmitter)
* [SPI Wikipedia-side](https://wikipedia.org/wiki/Serial_Peripheral_Interface)
* [I<sup>2</sup>C Wikipedia-side](https://wikipedia.org/wiki/I²C)
* [Zigbee Wikipedia-side](https://wikipedia.org/wiki/Zigbee)

## Opgave

[Kalibrer din sensor](assignment.md)

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.