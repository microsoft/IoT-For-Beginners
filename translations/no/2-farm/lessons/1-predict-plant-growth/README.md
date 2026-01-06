<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d105b44deae539165855c976dcdeca99",
  "translation_date": "2025-08-27T22:49:08+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/README.md",
  "language_code": "no"
}
-->
## Forutsi plantevekst med IoT

![En sketchnote-oversikt over denne leksjonen](../../../../../translated_images/lesson-5.42b234299279d263143148b88ab4583861a32ddb03110c6c1120e41bb88b2592.no.jpg)

> Sketchnote av [Nitya Narasimhan](https://github.com/nitya). Klikk på bildet for en større versjon.

## Quiz før forelesning

[Quiz før forelesning](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/9)

## Introduksjon

Planter trenger visse ting for å vokse - vann, karbondioksid, næringsstoffer, lys og varme. I denne leksjonen vil du lære hvordan du beregner vekst- og modningsrater for planter ved å måle lufttemperaturen.

I denne leksjonen skal vi dekke:

* [Digitalt landbruk](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Hvorfor er temperatur viktig i landbruk?](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Mål omgivelsestemperatur](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Vekstgrad-dager (GDD)](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Beregn GDD ved hjelp av temperatursensordata](../../../../../2-farm/lessons/1-predict-plant-growth)

## Digitalt landbruk

Digitalt landbruk forandrer måten vi driver jordbruk på, ved å bruke verktøy for å samle inn, lagre og analysere data fra gårdsdrift. Vi er for øyeblikket i en periode som Verdens økonomiske forum beskriver som den 'Fjerde industrielle revolusjon', og fremveksten av digitalt landbruk har blitt kalt den 'Fjerde landbruksrevolusjonen', eller 'Landbruk 4.0'.

> 🎓 Begrepet digitalt landbruk inkluderer også hele 'verdikjeden for landbruk', altså hele reisen fra gård til bord. Det inkluderer sporing av produktkvalitet mens mat blir fraktet og bearbeidet, lager- og e-handelssystemer, til og med apper for traktorlån!

Disse endringene gjør det mulig for bønder å øke avlingene, bruke mindre gjødsel og plantevernmidler, og vanne mer effektivt. Selv om det primært brukes i rikere land, blir sensorer og andre enheter gradvis billigere, noe som gjør dem mer tilgjengelige i utviklingsland.

Noen teknikker muliggjort av digitalt landbruk er:

* Temperaturmåling - måling av temperatur gjør det mulig for bønder å forutsi plantevekst og modning.
* Automatisk vanning - måling av jordfuktighet og aktivering av vanningssystemer når jorden er for tørr, i stedet for tidsstyrt vanning. Tidsstyrt vanning kan føre til at avlinger blir under-vannet i en varm, tørr periode, eller over-vannet under regn. Ved å vanne kun når jorden trenger det, kan bønder optimalisere vannbruken.
* Skadedyrkontroll - bønder kan bruke kameraer på automatiserte roboter eller droner for å sjekke etter skadedyr, og deretter bruke plantevernmidler kun der det er nødvendig, noe som reduserer mengden plantevernmidler som brukes og minimerer avrenning til lokale vannkilder.

✅ Gjør litt research. Hvilke andre teknikker brukes for å forbedre avlingsutbyttet?

> 🎓 Begrepet 'Presisjonslandbruk' brukes for å definere observasjon, måling og respons på avlinger på en per-felt basis, eller til og med på deler av et felt. Dette inkluderer måling av vann-, nærings- og skadedyrnivåer og nøyaktig respons, som å vanne kun en liten del av et felt.

## Hvorfor er temperatur viktig i landbruk?

Når man lærer om planter, blir de fleste elever lært om nødvendigheten av vann, lys, karbondioksid og næringsstoffer. Planter trenger også varme for å vokse - dette er grunnen til at planter blomstrer om våren når temperaturen stiger, hvorfor snøklokker eller påskeliljer kan spire tidlig på grunn av en kort varm periode, og hvorfor drivhus og veksthus er så gode til å få planter til å vokse.

> 🎓 Drivhus og veksthus gjør en lignende jobb, men med en viktig forskjell. Drivhus varmes opp kunstig og lar bønder kontrollere temperaturen mer nøyaktig, mens veksthus er avhengige av solen for varme og vanligvis har kun vinduer eller andre åpninger for å slippe ut varme.

Planter har en basistemperatur eller minimumstemperatur, optimal temperatur og maksimumstemperatur, alle basert på daglige gjennomsnittstemperaturer.

* Basistemperatur - dette er den minimale daglige gjennomsnittstemperaturen som trengs for at en plante skal vokse.
* Optimal temperatur - dette er den beste daglige gjennomsnittstemperaturen for å oppnå maksimal vekst.
* Maksimumstemperatur - dette er den høyeste temperaturen en plante kan tåle. Over denne temperaturen vil planten stoppe veksten for å forsøke å bevare vann og overleve.

> 💁 Dette er gjennomsnittstemperaturer, beregnet som et gjennomsnitt av dag- og natt-temperaturer. Planter trenger også forskjellige temperaturer dag og natt for å fotosyntetisere mer effektivt og spare energi om natten.

Hver planteart har forskjellige verdier for sin basis-, optimal- og maksimumstemperatur. Dette er grunnen til at noen planter trives i varme land, og andre i kaldere land.

✅ Gjør litt research. For planter du har i hagen, på skolen eller i en lokal park, se om du kan finne basistemperaturen.

![En graf som viser vekstraten som øker med temperaturen, og deretter faller når temperaturen blir for høy](../../../../../translated_images/plant-growth-temp-graph.c6d69c9478e6ca83.no.png)

Grafen ovenfor viser et eksempel på en vekstrate til temperatur-graf. Opp til basistemperaturen er det ingen vekst. Vekstraten øker opp til den optimale temperaturen, og faller deretter etter å ha nådd denne toppen. 

Formen på denne grafen varierer fra planteart til planteart. Noen har brattere fall etter den optimale temperaturen, mens andre har langsommere økninger fra basistemperaturen til den optimale.

> 💁 For at en bonde skal oppnå best mulig vekst, må de kjenne til de tre temperaturverdiene og forstå formen på grafene for plantene de dyrker.

Hvis en bonde har kontroll over temperaturen, for eksempel i et kommersielt drivhus, kan de optimalisere for plantene sine. Et kommersielt drivhus som dyrker tomater, for eksempel, vil ha temperaturen satt til rundt 25°C om dagen og 20°C om natten for å oppnå raskest vekst.

> 🍅 Ved å kombinere disse temperaturene med kunstig lys, gjødsel og kontrollert CO
Denne koden åpner CSV-filen og legger til en ny rad på slutten. Raden inneholder dagens dato og klokkeslett formatert på en lesbar måte, etterfulgt av temperaturen mottatt fra IoT-enheten. Dataene lagres i [ISO 8601-format](https://wikipedia.org/wiki/ISO_8601) med tidssone, men uten mikrosekunder.

1. Kjør denne koden på samme måte som før, og sørg for at IoT-enheten din sender data. En CSV-fil kalt `temperature.csv` vil bli opprettet i samme mappe. Hvis du åpner den, vil du se dato/tid og temperaturmålinger:

    ```output
    date,temperature
    2021-04-19T17:21:36-07:00,25
    2021-04-19T17:31:36-07:00,24
    2021-04-19T17:41:36-07:00,25
    ```

1. Kjør denne koden en stund for å samle data. Ideelt sett bør du kjøre den i en hel dag for å samle nok data til GDD-beregninger.

    
> 💁 Hvis du bruker en virtuell IoT-enhet, velg avkrysningsboksen for tilfeldig og sett et område for å unngå å få samme temperatur hver gang temperaturen returneres.
    ![Velg avkrysningsboksen for tilfeldig og sett et område](../../../../../translated_images/select-the-random-checkbox-and-set-a-range.32cf4bc7c12e797f.no.png) 

    > 💁 Hvis du vil kjøre dette i en hel dag, må du sørge for at datamaskinen serverkoden din kjører på ikke går i dvale, enten ved å endre strøminnstillingene dine eller kjøre noe som [dette Python-skriptet for å holde systemet aktivt](https://github.com/jaqsparow/keep-system-active).
    
> 💁 Du finner denne koden i mappen [code-server/temperature-sensor-server](../../../../../2-farm/lessons/1-predict-plant-growth/code-server/temperature-sensor-server).

### Oppgave - beregn GDD ved hjelp av de lagrede dataene

Når serveren har fanget opp temperaturdata, kan GDD for en plante beregnes.

Stegene for å gjøre dette manuelt er:

1. Finn basistemperaturen for planten. For eksempel er basistemperaturen for jordbær 10°C.

1. Fra `temperature.csv`, finn dagens høyeste og laveste temperaturer.

1. Bruk GDD-beregningen som ble gitt tidligere for å beregne GDD.

For eksempel, hvis dagens høyeste temperatur er 25°C, og den laveste er 12°C:

![GDD = 25 + 12 delt på 2, deretter trekk 10 fra resultatet som gir 8,5](../../../../../translated_images/gdd-calculation-strawberries.59f57db94b22adb8ff6efb951ace33af104a1c6ccca3ffb0f8169c14cb160c90.no.png)

* 25 + 12 = 37
* 37 / 2 = 18,5
* 18,5 - 10 = 8,5

Derfor har jordbærene mottatt **8,5** GDD. Jordbær trenger omtrent 250 GDD for å bære frukt, så det er fortsatt en stund igjen.

---

## 🚀 Utfordring

Planter trenger mer enn varme for å vokse. Hva annet trenger de?

For disse, finn ut om det finnes sensorer som kan måle dem. Hva med aktuatorer for å kontrollere disse nivåene? Hvordan ville du satt sammen én eller flere IoT-enheter for å optimalisere plantevekst?

## Quiz etter forelesning

[Quiz etter forelesning](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/10)

## Gjennomgang og selvstudium

* Les mer om digitalt jordbruk på [Wikipedia-siden om digitalt jordbruk](https://wikipedia.org/wiki/Digital_agriculture). Les også mer om presisjonsjordbruk på [Wikipedia-siden om presisjonsjordbruk](https://wikipedia.org/wiki/Precision_agriculture).
* Den fullstendige beregningen av vekstgrader (GDD) er mer komplisert enn den forenklede versjonen som er gitt her. Les mer om den mer komplekse ligningen og hvordan man håndterer temperaturer under baselinja på [Wikipedia-siden om vekstgrader](https://wikipedia.org/wiki/Growing_degree-day).
* Mat kan bli en mangelvare i fremtiden hvis vi fortsatt bruker de samme metodene for jordbruk. Lær mer om høyteknologiske jordbruksteknikker i denne [YouTube-videoen om fremtidens høyteknologiske gårder](https://www.youtube.com/watch?v=KIEOuKD9KX8).

## Oppgave

[Visualiser GDD-data ved hjelp av en Jupyter Notebook](assignment.md)

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiske oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.