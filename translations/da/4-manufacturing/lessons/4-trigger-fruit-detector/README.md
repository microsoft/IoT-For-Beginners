<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f74f4ccb61f00e5f7e9f49c3ed416e36",
  "translation_date": "2025-08-27T20:29:11+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/README.md",
  "language_code": "da"
}
-->
# Udløs frugtkvalitetsdetektion fra en sensor

![En sketchnote-oversigt over denne lektion](../../../../../translated_images/da/lesson-18.92c32ed1d354caa5a54baa4032cf0b172d4655e8e326ad5d46c558a0def15365.jpg)

> Sketchnote af [Nitya Narasimhan](https://github.com/nitya). Klik på billedet for en større version.

## Quiz før lektionen

[Quiz før lektionen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/35)

## Introduktion

En IoT-applikation er ikke bare en enkelt enhed, der indsamler data og sender dem til skyen. Det er ofte flere enheder, der arbejder sammen for at indsamle data fra den fysiske verden via sensorer, træffe beslutninger baseret på disse data og interagere med den fysiske verden via aktuatorer eller visualiseringer.

I denne lektion vil du lære mere om at designe komplekse IoT-applikationer, der integrerer flere sensorer, flere cloud-tjenester til analyse og lagring af data, og viser en respons via en aktuator. Du vil lære, hvordan man designer en prototype til et frugtkvalitetskontrolsystem, herunder brug af nærhedssensorer til at udløse IoT-applikationen, og hvordan arkitekturen for denne prototype ville se ud.

I denne lektion dækker vi:

* [Design komplekse IoT-applikationer](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Design et frugtkvalitetskontrolsystem](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Udløs frugtkvalitetskontrol fra en sensor](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Data brugt til en frugtkvalitetsdetektor](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Brug udvikler-enheder til at simulere flere IoT-enheder](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Overgang til produktion](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)

> 🗑 Dette er den sidste lektion i dette projekt, så efter at have afsluttet denne lektion og opgaven, må du ikke glemme at rydde op i dine cloud-tjenester. Du vil have brug for tjenesterne for at fuldføre opgaven, så sørg for at fuldføre den først.
>
> Se [guiden til oprydning af dit projekt](../../../clean-up.md) om nødvendigt for instruktioner om, hvordan du gør dette.

## Design komplekse IoT-applikationer

IoT-applikationer består af mange komponenter. Dette inkluderer en række enheder og en række internettjenester.

IoT-applikationer kan beskrives som *ting* (enheder), der sender data, som genererer *indsigter*. Disse *indsigter* genererer *handlinger* for at forbedre en virksomhed eller proces. Et eksempel er en motor (tingen), der sender temperaturdata. Disse data bruges til at evaluere, om motoren fungerer som forventet (indsigten). Indsigten bruges til proaktivt at prioritere vedligeholdelsesplanen for motoren (handlingen).

* Forskellige ting indsamler forskellige datastykker.
* IoT-tjenester giver indsigt i disse data, nogle gange ved at supplere dem med data fra yderligere kilder.
* Disse indsigter driver handlinger, herunder styring af aktuatorer i enheder eller visualisering af data.

### Reference IoT-arkitektur

![En reference IoT-arkitektur](../../../../../translated_images/da/iot-reference-architecture.2278b98b55c6d4e89bde18eada3688d893861d43507641804dd2f9d3079cfaa0.png)

Diagrammet ovenfor viser en reference IoT-arkitektur.

> 🎓 En *referencearkitektur* er et eksempel på en arkitektur, du kan bruge som reference, når du designer nye systemer. I dette tilfælde, hvis du skulle bygge et nyt IoT-system, kan du følge referencearkitekturen og erstatte dine egne enheder og tjenester, hvor det er passende.

* **Ting** er enheder, der indsamler data fra sensorer, måske interagerer med edge-tjenester for at fortolke disse data, såsom billedklassifikatorer til at fortolke billeddata. Dataene fra enhederne sendes til en IoT-tjeneste.
* **Indsigter** kommer fra serverløse applikationer eller fra analyser, der køres på lagrede data.
* **Handlinger** kan være kommandoer sendt til enheder eller visualisering af data, der giver mennesker mulighed for at træffe beslutninger.

![En reference IoT-arkitektur](../../../../../translated_images/da/iot-reference-architecture-azure.0b8d2161af924cb18ae48a8558a19541cca47f27264851b5b7e56d7b8bb372ac.png)

Diagrammet ovenfor viser nogle af de komponenter og tjenester, der er dækket indtil videre i disse lektioner, og hvordan de hænger sammen i en reference IoT-arkitektur.

* **Ting** - du har skrevet enhedskode for at indsamle data fra sensorer og analysere billeder ved hjælp af Custom Vision, der kører både i skyen og på en edge-enhed. Disse data blev sendt til IoT Hub.
* **Indsigter** - du har brugt Azure Functions til at reagere på beskeder sendt til en IoT Hub og lagret data til senere analyse i Azure Storage.
* **Handlinger** - du har styret aktuatorer baseret på beslutninger truffet i skyen og kommandoer sendt til enhederne, og du har visualiseret data ved hjælp af Azure Maps.

✅ Tænk på andre IoT-enheder, du har brugt, såsom smarte hjemmeapparater. Hvad er tingene, indsigterne og handlingerne involveret i den enhed og dens software?

Dette mønster kan skaleres op eller ned, alt efter hvad du har brug for, ved at tilføje flere enheder og flere tjenester.

### Data og sikkerhed

Når du definerer arkitekturen for dit system, skal du konstant overveje data og sikkerhed.

* Hvilke data sender og modtager din enhed?
* Hvordan skal disse data sikres og beskyttes?
* Hvordan skal adgang til enheden og cloud-tjenesten kontrolleres?

✅ Tænk på datasikkerheden for de IoT-enheder, du ejer. Hvor mange af disse data er personlige og bør holdes private, både under transport og når de er lagret? Hvilke data bør ikke lagres?

## Design et frugtkvalitetskontrolsystem

Lad os nu tage denne idé om ting, indsigter og handlinger og anvende den på vores frugtkvalitetsdetektor for at designe en større end-to-end-applikation.

Forestil dig, at du har fået til opgave at bygge en frugtkvalitetsdetektor, der skal bruges i en forarbejdningsfabrik. Frugt transporteres på et transportbåndssystem, hvor medarbejdere i øjeblikket bruger tid på manuelt at kontrollere frugten og fjerne umoden frugt, når den ankommer. For at reducere omkostningerne ønsker fabriksejeren et automatiseret system.

✅ En af tendenserne med fremkomsten af IoT (og teknologi generelt) er, at manuelle job erstattes af maskiner. Undersøg: Hvor mange job anslås at gå tabt til IoT? Hvor mange nye job vil blive skabt ved at bygge IoT-enheder?

Du skal bygge et system, hvor frugt registreres, når det ankommer på transportbåndet, derefter fotograferes og kontrolleres ved hjælp af en AI-model, der kører på kanten. Resultaterne sendes derefter til skyen for at blive lagret, og hvis frugten er umoden, gives der en notifikation, så den umodne frugt kan fjernes.

|   |   |
| - | - |
| **Ting** | Detektor for frugt, der ankommer på transportbåndet<br>Kamera til at fotografere og klassificere frugten<br>Edge-enhed, der kører klassifikatoren<br>Enhed til at give besked om umoden frugt |
| **Indsigter** | Beslutning om at kontrollere frugtens modenhed<br>Lag resultaterne af modenhedsklassifikationen<br>Bestem, om der er behov for at advare om umoden frugt |
| **Handlinger** | Send en kommando til en enhed for at fotografere frugten og kontrollere den med en billedklassifikator<br>Send en kommando til en enhed for at advare om, at frugten er umoden |

### Prototyping af din applikation

![En reference IoT-arkitektur for frugtkvalitetskontrol](../../../../../translated_images/da/iot-reference-architecture-fruit-quality.cc705f121c3b6fa71c800d9630935ac34bc08223a04601e35f41d5e9b5dd5207.png)

Diagrammet ovenfor viser en referencearkitektur for denne prototype-applikation.

* En IoT-enhed med en nærhedssensor registrerer frugtens ankomst. Dette sender en besked til skyen om, at frugt er blevet registreret.
* En serverløs applikation i skyen sender en kommando til en anden enhed for at tage et fotografi og klassificere billedet.
* En IoT-enhed med et kamera tager et billede og sender det til en billedklassifikator, der kører på kanten. Resultaterne sendes derefter til skyen.
* En serverløs applikation i skyen lagrer disse oplysninger til senere analyse for at se, hvilken procentdel af frugten der er umoden. Hvis frugten er umoden, sender den en kommando til en anden IoT-enhed for at advare fabriksarbejdere om umoden frugt via en LED.

> 💁 Hele denne IoT-applikation kunne implementeres som en enkelt enhed med al logik til at starte billedklassifikationen og styre LED'en indbygget. Den kunne bruge en IoT Hub blot til at spore antallet af umodne frugter, der er registreret, og konfigurere enheden. I denne lektion er den udvidet for at demonstrere koncepterne for store IoT-applikationer.

For prototypen vil du implementere alt dette på en enkelt enhed. Hvis du bruger en mikrocontroller, vil du bruge en separat edge-enhed til at køre billedklassifikatoren. Du har allerede lært det meste af det, du skal bruge for at kunne bygge dette.

## Udløs frugtkvalitetskontrol fra en sensor

IoT-enheden har brug for en form for trigger for at indikere, hvornår frugten er klar til at blive klassificeret. En trigger for dette kunne være at måle, hvornår frugten er på det rigtige sted på transportbåndet ved at måle afstanden til en sensor.

![Nærhedssensorer sender laserstråler til objekter som bananer og måler tiden, indtil strålen reflekteres tilbage](../../../../../translated_images/da/proximity-sensor.f5cd752c77fb62fe.webp)

Nærhedssensorer kan bruges til at måle afstanden fra sensoren til et objekt. De sender normalt en stråle af elektromagnetisk stråling, såsom en laserstråle eller infrarødt lys, og registrerer derefter strålingen, der reflekteres fra et objekt. Tiden mellem laserstrålen, der sendes, og signalet, der reflekteres tilbage, kan bruges til at beregne afstanden til sensoren.

> 💁 Du har sandsynligvis brugt nærhedssensorer uden at vide det. De fleste smartphones slukker for skærmen, når du holder dem op til øret for at forhindre, at du ved et uheld afslutter et opkald med din øreflip. Dette fungerer ved hjælp af en nærhedssensor, der registrerer et objekt tæt på skærmen under et opkald og deaktiverer berøringsfunktionerne, indtil telefonen er en vis afstand væk.

### Opgave - udløs frugtkvalitetsdetektion fra en afstandssensor

Følg den relevante guide for at bruge en nærhedssensor til at registrere et objekt ved hjælp af din IoT-enhed:

* [Arduino - Wio Terminal](wio-terminal-proximity.md)
* [Single-board computer - Raspberry Pi](pi-proximity.md)
* [Single-board computer - Virtuel enhed](virtual-device-proximity.md)

## Data brugt til en frugtkvalitetsdetektor

Prototypen af frugtdetektoren har flere komponenter, der kommunikerer med hinanden.

![Komponenterne kommunikerer med hinanden](../../../../../translated_images/da/fruit-quality-detector-message-flow.adf2a65da8fd8741ac7af11361574de89adc126785d67606bb4d2ec00467e380.png)

* En nærhedssensor måler afstanden til et stykke frugt og sender dette til IoT Hub
* Kommandoen til at styre kameraet kommer fra IoT Hub til kameraenheden
* Resultaterne af billedklassifikationen sendes til IoT Hub
* Kommandoen til at styre en LED for at advare om, at frugten er umoden, sendes fra IoT Hub til enheden med LED'en

Det er en god idé at definere strukturen af disse beskeder på forhånd, før du bygger applikationen.

> 💁 Næsten enhver erfaren udvikler har på et tidspunkt i deres karriere brugt timer, dage eller endda uger på at jagte fejl forårsaget af forskelle i de data, der sendes, sammenlignet med hvad der forventes.

For eksempel - hvis du sender temperaturinformation, hvordan ville du definere JSON? Du kunne have et felt kaldet `temperature`, eller du kunne bruge den almindelige forkortelse `temp`.

```json
{
    "temperature": 20.7
}
```

sammenlignet med:

```json
{
    "temp": 20.7
}
```

Du skal også overveje enheder - er temperaturen i °C eller °F? Hvis du måler temperatur ved hjælp af en forbrugerenhed, og de ændrer visningsenhederne, skal du sørge for, at enhederne, der sendes til skyen, forbliver konsistente.

✅ Undersøg: Hvordan forårsagede enhedsproblemer, at Mars Climate Orbiter til en værdi af $125 millioner styrtede?

Tænk på de data, der sendes for frugtkvalitetsdetektoren. Hvordan ville du definere hver besked? Hvor ville du analysere dataene og træffe beslutninger om, hvilke data der skal sendes?

For eksempel - udløs billedklassifikationen ved hjælp af nærhedssensoren. IoT-enheden måler afstanden, men hvor træffes beslutningen? Beslutter enheden, at frugten er tæt nok og sender en besked til IoT Hub for at udløse klassifikationen? Eller sender den nærhedsmålinger og lader IoT Hub beslutte?

Svaret på spørgsmål som dette er - det afhænger. Hver brugssag er forskellig, hvilket er grunden til, at du som IoT-udvikler skal forstå det system, du bygger, hvordan det bruges, og de data, der registreres.

* Hvis beslutningen træffes af IoT Hub, skal du sende flere afstandsmålinger.
* Hvis du sender for mange beskeder, øger det omkostningerne ved IoT Hub og mængden af båndbredde, der kræves af dine IoT-enheder (især i en fabrik med millioner af enheder). Det kan også gøre din enhed langsommere.
* Hvis du træffer beslutningen på enheden, skal du give en måde at konfigurere enheden til at finjustere maskinen.

## Brug udvikler-enheder til at simulere flere IoT-enheder

For at bygge din prototype skal du bruge dit IoT-udviklingskit til at fungere som flere enheder, sende telemetri og reagere på kommandoer.

### Simulering af flere IoT-enheder på en Raspberry Pi eller virtuel IoT-hardware

Når du bruger en enkeltbrætscomputer som en Raspberry Pi, kan du køre flere applikationer på én gang. Dette betyder, at du kan simulere flere IoT-enheder ved at oprette flere applikationer, én pr. 'IoT-enhed'. For eksempel kan du implementere hver enhed som en separat Python-fil og køre dem i forskellige terminalsessioner.
> 💁 Vær opmærksom på, at noget hardware ikke fungerer, når det tilgås af flere applikationer, der kører samtidig.
### Simulering af flere enheder på en mikrocontroller

Mikrocontrollere er mere komplekse at simulere med flere enheder. I modsætning til single board-computere kan du ikke køre flere applikationer samtidig; du skal inkludere al logik for de separate IoT-enheder i én enkelt applikation.

Nogle forslag til at gøre denne proces lettere er:

* Opret en eller flere klasser pr. IoT-enhed - for eksempel klasser kaldet `DistanceSensor`, `ClassifierCamera`, `LEDController`. Hver klasse kan have sine egne `setup`- og `loop`-metoder, som kaldes af de primære `setup`- og `loop`-funktioner.
* Håndter kommandoer ét sted og diriger dem til den relevante enhedsklasse efter behov.
* I den primære `loop`-funktion skal du tage højde for timing for hver enhed. For eksempel, hvis du har en enhedsklasse, der skal behandles hvert 10. sekund, og en anden, der skal behandles hvert sekund, skal du bruge en forsinkelse på 1 sekund i din primære `loop`-funktion. Hver `loop`-kald aktiverer den relevante kode for enheden, der skal behandles hvert sekund, og brug en tæller til at tælle hvert loop, så den anden enhed behandles, når tælleren når 10 (og nulstil tælleren derefter).

## Overgang til produktion

Prototypen vil danne grundlaget for det endelige produktionssystem. Nogle af forskellene, når du går over til produktion, kunne være:

* Robust hardware - brug af komponenter designet til at modstå støj, varme, vibrationer og stress i en fabrik.
* Brug af intern kommunikation - nogle af komponenterne ville kommunikere direkte og undgå at hoppe til skyen, kun sende data til skyen for at blive gemt. Hvordan dette gøres afhænger af fabrikkens opsætning, enten via direkte kommunikation eller ved at køre en del af IoT-tjenesten på kanten ved hjælp af en gateway-enhed.
* Konfigurationsmuligheder - hver fabrik og anvendelse er forskellig, så hardwaren skal være konfigurerbar. For eksempel kan nærhedssensoren have brug for at registrere forskellige frugter på forskellige afstande. I stedet for at hardkode afstanden til at udløse klassifikationen, vil du gerne have, at dette kan konfigureres via skyen, for eksempel ved hjælp af en device twin.
* Automatisk fjernelse af frugt - i stedet for en LED til at advare om, at frugten er umoden, ville automatiske enheder fjerne den.

✅ Lav lidt research: På hvilke andre måder ville produktionsenheder adskille sig fra udviklingskits?

---

## 🚀 Udfordring

I denne lektion har du lært nogle af de begreber, du skal kende for at kunne designe et IoT-system. Tænk tilbage på de tidligere projekter. Hvordan passer de ind i den referencearkitektur, der er vist ovenfor?

Vælg et af projekterne indtil videre og tænk på designet af en mere kompleks løsning, der samler flere funktioner ud over det, der blev dækket i projekterne. Tegn arkitekturen og tænk på alle de enheder og tjenester, du ville have brug for.

For eksempel - en køretøjssporingsenhed, der kombinerer GPS med sensorer til at overvåge ting som temperaturer i en kølebil, motorens tænd/sluk-tider og chaufførens identitet. Hvilke enheder er involveret, hvilke tjenester er involveret, hvilke data bliver transmitteret, og hvilke sikkerheds- og privatlivsovervejelser skal der tages højde for?

## Quiz efter lektionen

[Quiz efter lektionen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/36)

## Gennemgang & Selvstudie

* Læs mere om IoT-arkitektur i [Azure IoT referencearkitektur-dokumentationen på Microsoft Docs](https://docs.microsoft.com/azure/architecture/reference-architectures/iot?WT.mc_id=academic-17441-jabenn)
* Læs mere om device twins i [forstå og brug device twins i IoT Hub-dokumentationen på Microsoft Docs](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-device-twins?WT.mc_id=academic-17441-jabenn)
* Læs om OPC-UA, en maskin-til-maskin-kommunikationsprotokol, der bruges i industriel automatisering, på [OPC-UA-siden på Wikipedia](https://wikipedia.org/wiki/OPC_Unified_Architecture)

## Opgave

[Byg en frugtkvalitetsdetektor](assignment.md)

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der opstår som følge af brugen af denne oversættelse.