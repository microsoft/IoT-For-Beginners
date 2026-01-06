<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d105b44deae539165855c976dcdeca99",
  "translation_date": "2025-08-27T22:47:47+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/README.md",
  "language_code": "da"
}
-->
# Forudsig plantevækst med IoT

![En sketchnote-oversigt over denne lektion](../../../../../translated_images/lesson-5.42b234299279d263143148b88ab4583861a32ddb03110c6c1120e41bb88b2592.da.jpg)

> Sketchnote af [Nitya Narasimhan](https://github.com/nitya). Klik på billedet for en større version.

## Quiz før lektionen

[Quiz før lektionen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/9)

## Introduktion

Planter har brug for visse ting for at vokse - vand, kuldioxid, næringsstoffer, lys og varme. I denne lektion lærer du, hvordan man beregner vækst- og modningshastigheder for planter ved at måle lufttemperaturen.

I denne lektion dækker vi:

* [Digitalt landbrug](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Hvorfor er temperatur vigtigt i landbrug?](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Mål omgivelsestemperaturen](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Vækstgradedage (GDD)](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Beregn GDD ved hjælp af temperatursensordata](../../../../../2-farm/lessons/1-predict-plant-growth)

## Digitalt landbrug

Digitalt landbrug revolutionerer måden, vi dyrker jorden på, ved at bruge værktøjer til at indsamle, gemme og analysere data fra landbruget. Vi befinder os i øjeblikket i en periode, som Verdensøkonomiforum beskriver som den 'Fjerde Industrielle Revolution', og fremkomsten af digitalt landbrug er blevet kaldt den 'Fjerde Landbrugsrevolution' eller 'Landbrug 4.0'.

> 🎓 Begrebet Digitalt Landbrug omfatter også hele 'landbrugsværdikæden', det vil sige hele rejsen fra mark til bord. Det inkluderer sporing af fødevarekvalitet, mens maden transporteres og forarbejdes, lager- og e-handelssystemer, og endda apps til leje af traktorer!

Disse ændringer giver landmænd mulighed for at øge udbyttet, bruge mindre gødning og pesticider og vande mere effektivt. Selvom det primært bruges i rigere lande, falder priserne på sensorer og andre enheder langsomt, hvilket gør dem mere tilgængelige i udviklingslande.

Nogle teknikker, der muliggøres af digitalt landbrug, er:

* Temperaturmåling - måling af temperatur gør det muligt for landmænd at forudsige plantevækst og modning.
* Automatisk vanding - måling af jordfugtighed og aktivering af vandingssystemer, når jorden er for tør, i stedet for tidsindstillet vanding. Tidsindstillet vanding kan føre til, at afgrøder bliver undervandet under en varm, tør periode eller overvandet under regn. Ved kun at vande, når jorden har brug for det, kan landmænd optimere deres vandforbrug.
* Skadedyrsbekæmpelse - landmænd kan bruge kameraer på automatiserede robotter eller droner til at tjekke for skadedyr og derefter kun anvende pesticider, hvor det er nødvendigt, hvilket reducerer mængden af pesticider og mindsker pesticidafstrømning i lokale vandforsyninger.

✅ Lav lidt research. Hvilke andre teknikker bruges til at forbedre landbrugsudbyttet?

> 🎓 Begrebet 'Præcisionslandbrug' bruges til at definere observation, måling og reaktion på afgrøder på basis af individuelle marker eller endda dele af en mark. Dette inkluderer måling af vand-, næringsstof- og skadedyrsniveauer og præcist at reagere, som f.eks. kun at vande en lille del af en mark.

## Hvorfor er temperatur vigtigt i landbrug?

Når man lærer om planter, bliver de fleste elever undervist i nødvendigheden af vand, lys, kuldioxid og næringsstoffer. Planter har også brug for varme for at vokse - det er derfor, planter blomstrer om foråret, når temperaturen stiger, hvorfor vintergækker eller påskeliljer kan spire tidligt på grund af en kort varm periode, og hvorfor drivhuse og væksthuse er så gode til at få planter til at vokse.

> 🎓 Drivhuse og væksthuse har en lignende funktion, men med en vigtig forskel. Drivhuse opvarmes kunstigt og giver landmænd mulighed for at kontrollere temperaturen mere præcist, mens væksthuse er afhængige af solen for varme og normalt kun har vinduer eller andre åbninger til at slippe varmen ud.

Planter har en basistemperatur, en optimal temperatur og en maksimumtemperatur, alle baseret på daglige gennemsnitstemperaturer.

* Basistemperatur - dette er den minimale daglige gennemsnitstemperatur, der kræves for, at en plante kan vokse.
* Optimal temperatur - dette er den bedste daglige gennemsnitstemperatur for at opnå maksimal vækst.
* Maksimumtemperatur - dette er den maksimale temperatur, en plante kan tåle. Over denne temperatur stopper planten sin vækst for at forsøge at bevare vand og overleve.

> 💁 Dette er gennemsnitstemperaturer, beregnet som gennemsnittet af dag- og nattemperaturer. Planter har også brug for forskellige temperaturer dag og nat for at fotosyntetisere mere effektivt og spare energi om natten.

Hver plantesort har forskellige værdier for deres basis-, optimale og maksimale temperatur. Det er derfor, nogle planter trives i varme lande, og andre i koldere lande.

✅ Lav lidt research. For planter i din have, skole eller lokale park, kan du finde deres basistemperatur?

![En graf, der viser væksthastigheden stige, når temperaturen stiger, og derefter falde, når temperaturen bliver for høj](../../../../../translated_images/plant-growth-temp-graph.c6d69c9478e6ca83.da.png)

Grafen ovenfor viser et eksempel på en væksthastighed i forhold til temperatur. Op til basistemperaturen er der ingen vækst. Væksthastigheden stiger op til den optimale temperatur og falder derefter efter at have nået denne top. 

Grafens form varierer fra plantesort til plantesort. Nogle har skarpere fald over den optimale temperatur, mens andre har langsommere stigninger fra basis til optimal.

> 💁 For at en landmand kan opnå den bedste vækst, skal de kende de tre temperaturværdier og forstå grafens form for de planter, de dyrker.

Hvis en landmand har kontrol over temperaturen, for eksempel i et kommercielt drivhus, kan de optimere for deres planter. Et kommercielt drivhus, der dyrker tomater, vil for eksempel have temperaturen indstillet til omkring 25°C om dagen og 20°C om natten for at opnå den hurtigste vækst.

> 🍅 Ved at kombinere disse temperaturer med kunstigt lys, gødning og kontrollerede CO2-niveauer kan kommercielle dyrkere dyrke og høste året rundt.

## Mål omgivelsestemperaturen

Temperatursensorer kan bruges med IoT-enheder til at måle omgivelsestemperaturen.

### Opgave - mål temperaturen

Følg den relevante vejledning for at overvåge temperaturer ved hjælp af din IoT-enhed:

* [Arduino - Wio Terminal](wio-terminal-temp.md)
* [Single-board computer - Raspberry Pi](pi-temp.md)
* [Single-board computer - Virtuel enhed](virtual-device-temp.md)

## Vækstgradedage

Vækstgradedage (også kendt som vækstgradsenheder) er en måde at måle planters vækst baseret på temperaturen. Forudsat at en plante har nok vand, næringsstoffer og CO2, bestemmer temperaturen væksthastigheden.

Vækstgradedage, eller GDD, beregnes pr. dag som den gennemsnitlige temperatur i Celsius for en dag over plantens basistemperatur. Hver plante har brug for et bestemt antal GDD for at vokse, blomstre eller producere og modne en afgrøde. Jo flere GDD hver dag, jo hurtigere vokser planten.

> 🇺🇸 For amerikanere kan vækstgradedage også beregnes ved hjælp af Fahrenheit. 5 GDD (i Celsius) svarer til 9 GDD (i Fahrenheit).

Den fulde formel for GDD er lidt kompliceret, men der findes en forenklet ligning, der ofte bruges som en god tilnærmelse:

![GDD = T max + T min divideret med 2, alt minus T base](../../../../../translated_images/gdd-calculation.79b3660f9c5757aa92dc2dd2cdde75344e2d2c1565c4b3151640f7887edc0275.da.png)

* **GDD** - dette er antallet af vækstgradedage
* **T max** - dette er den daglige maksimumtemperatur i grader Celsius
* **T min** - dette er den daglige minimumtemperatur i grader Celsius
* **T base** - dette er plantens basistemperatur i grader Celsius

> 💁 Der findes variationer, der tager højde for T max over 30°C eller T min under T base, men vi ser bort fra disse for nu.

### Eksempel - Majs 🌽

Afhængigt af sorten har majs brug for mellem 800 og 2.700 GDD for at modne, med en basistemperatur på 10°C.

På den første dag over basistemperaturen blev følgende temperaturer målt:

| Måling      | Temp °C |
| :---------- | :-----: |
| Maksimum    | 16      |
| Minimum     | 12      |

Ved at indsætte disse tal i vores beregning:

* T max = 16
* T min = 12
* T base = 10

Dette giver en beregning på:

![GDD = 16 + 12 divideret med 2, alt minus 10, hvilket giver et svar på 4](../../../../../translated_images/gdd-calculation-corn.64a58b7a7afcd0dfd46ff733996d939f17f4f3feac9f0d1c632be3523e51ebd9.da.png)

Majsen modtog 4 GDD den dag. Hvis vi antager en majsvariant, der har brug for 800 GDD for at modne, vil den have brug for yderligere 796 GDD for at nå modenhed.

✅ Lav lidt research. For planter i din have, skole eller lokale park, kan du finde antallet af GDD, der kræves for at nå modenhed eller producere afgrøder?

## Beregn GDD ved hjælp af temperatursensordata

Planter vokser ikke på faste datoer - for eksempel kan du ikke plante et frø og vide, at planten vil bære frugt præcis 100 dage senere. I stedet kan en landmand have en grov idé om, hvor lang tid en plante tager at vokse, og derefter tjekke dagligt for at se, hvornår afgrøderne er klar.

Dette har en stor arbejdsbyrde på en stor gård og risikerer, at landmanden overser afgrøder, der er klar uventet tidligt. Ved at måle temperaturer kan landmanden beregne de GDD, en plante har modtaget, hvilket gør det muligt kun at tjekke tæt på den forventede modenhed.

Ved at indsamle temperaturdata ved hjælp af en IoT-enhed kan en landmand automatisk blive underrettet, når planter nærmer sig modenhed. En typisk arkitektur for dette er at lade IoT-enhederne måle temperaturen og derefter sende disse telemetridata over internettet ved hjælp af noget som MQTT. Serverkode lytter derefter til disse data og gemmer dem et sted, såsom i en database. Dette betyder, at dataene derefter kan analyseres senere, for eksempel et natligt job til at beregne dagens GDD, summere GDD for hver afgrøde hidtil og give besked, hvis en plante nærmer sig modenhed.

![Telemetridata sendes til en server og gemmes derefter i en database](../../../../../translated_images/save-telemetry-database.ddc9c6bea0c5ba39.da.png)

Serverkoden kan også tilføje ekstra information til dataene. For eksempel kan IoT-enheden sende en identifikator for at angive, hvilken enhed det er, og serverkoden kan bruge dette til at finde placeringen af enheden og hvilke afgrøder, den overvåger. Den kan også tilføje grundlæggende data som det aktuelle tidspunkt, da nogle IoT-enheder ikke har den nødvendige hardware til at holde styr på præcise tidspunkter eller kræver yderligere kode for at læse det aktuelle tidspunkt over internettet.

✅ Hvorfor tror du, at forskellige marker kan have forskellige temperaturer?

### Opgave - send temperaturinformation

Følg den relevante vejledning for at sende temperaturdata over MQTT ved hjælp af din IoT-enhed, så de kan analyseres senere:

* [Arduino - Wio Terminal](wio-terminal-temp-publish.md)
* [Single-board computer - Raspberry Pi/Virtuel IoT-enhed](single-board-computer-temp-publish.md)

### Opgave - indfang og gem temperaturinformation

Når IoT-enheden sender telemetri, kan serverkoden skrives til at abonnere på disse data og gemme dem. I stedet for at gemme dem i en database vil serverkoden gemme dem i en kommasepareret værdifil (CSV). CSV-filer gemmer data som rækker af værdier som tekst, hvor hver værdi er adskilt af et komma, og hver post på en ny linje. De er en praktisk, menneskeligt læsbar og bredt understøttet måde at gemme data som en fil.

CSV-filen vil have to kolonner - *dato* og *temperatur*. *Dato*-kolonnen angiver den aktuelle dato og tid, hvor beskeden blev modtaget af serveren, og *temperatur* kommer fra telemetribeskeden.

1. Gentag trinnene i lektion 4 for at oprette serverkode til at abonnere på telemetri. Du behøver ikke tilføje kode til at sende kommandoer.

    Trinnene for dette er:

    * Konfigurer og aktiver et Python-virtuelt miljø

    * Installer paho-mqtt pip-pakken

    * Skriv koden til at lytte efter MQTT-beskeder, der sendes på telemetriemnet

      > ⚠️ Du kan henvise til [instruktionerne i lektion 4 for at oprette en Python-app til at modtage telemetri, hvis det er nødvendigt](../../../1-getting-started/lessons/4-connect-internet/README.md#receive-telemetry-from-the-mqtt-broker).

    Navngiv mappen for dette projekt `temperature-sensor-server`.

1. Sørg for, at `client_name` afspejler dette projekt:

    ```cpp
    client_name = id + 'temperature_sensor_server'
    ```

1. Tilføj følgende imports øverst i filen, under de eksisterende imports:

    ```python
    from os import path
    import csv
    from datetime import datetime
    ```

    Dette importerer et bibliotek til læsning af filer, et bibliotek til at interagere med CSV-filer og et bibliotek til at hjælpe med datoer og tidspunkter.

1. Tilføj følgende kode før `handle_telemetry`-funktionen:

    ```python
    temperature_file_name = 'temperature.csv'
    fieldnames = ['date', 'temperature']
    
    if not path.exists(temperature_file_name):
        with open(temperature_file_name, mode='w') as csv_file:
            writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
            writer.writeheader()
    ```

    Denne kode erklærer nogle konstanter for navnet på filen, der skal skrives til, og navnet på kolonneoverskrifterne for CSV-filen. Den første række i en CSV-fil indeholder traditionelt kolonneoverskrifter adskilt af kommaer.

    Koden tjekker derefter, om CSV-filen allerede eksisterer. Hvis den ikke eksisterer, oprettes den med kolonneoverskrifterne på den første række.

1. Tilføj følgende kode til slutningen af `handle_telemetry`-funktionen:

    ```python
    with open(temperature_file_name, mode='a') as temperature_file:        
        temperature_writer = csv.DictWriter(temperature_file, fieldnames=fieldnames)
        temperature_writer.writerow({'date' : datetime.now().astimezone().replace(microsecond=0).isoformat(), 'temperature' : payload['temperature']})
    ```
Denne kode åbner CSV-filen og tilføjer en ny række i slutningen. Rækken indeholder den aktuelle dato og tid formateret i et menneskelæsbart format, efterfulgt af temperaturen modtaget fra IoT-enheden. Dataene gemmes i [ISO 8601 format](https://wikipedia.org/wiki/ISO_8601) med tidszone, men uden mikrosekunder.

1. Kør denne kode på samme måde som før, og sørg for, at din IoT-enhed sender data. En CSV-fil kaldet `temperature.csv` vil blive oprettet i samme mappe. Hvis du åbner den, vil du se dato/tidspunkter og temperaturmålinger:

    ```output
    date,temperature
    2021-04-19T17:21:36-07:00,25
    2021-04-19T17:31:36-07:00,24
    2021-04-19T17:41:36-07:00,25
    ```

1. Kør denne kode i et stykke tid for at indsamle data. Ideelt set bør du køre den i en hel dag for at samle nok data til GDD-beregninger.

    
> 💁 Hvis du bruger en virtuel IoT-enhed, skal du vælge tilfældighedsafkrydsningsfeltet og angive et interval for at undgå at få den samme temperatur hver gang temperaturværdien returneres.
    ![Vælg tilfældighedsafkrydsningsfeltet og angiv et interval](../../../../../translated_images/select-the-random-checkbox-and-set-a-range.32cf4bc7c12e797f.da.png) 

    > 💁 Hvis du vil køre dette i en hel dag, skal du sørge for, at computeren, som din serverkode kører på, ikke går i dvale, enten ved at ændre dine strømindstillinger eller ved at køre noget som [denne Python-script til at holde systemet aktivt](https://github.com/jaqsparow/keep-system-active).
    
> 💁 Du kan finde denne kode i mappen [code-server/temperature-sensor-server](../../../../../2-farm/lessons/1-predict-plant-growth/code-server/temperature-sensor-server).

### Opgave - beregn GDD ved hjælp af de gemte data

Når serveren har indsamlet temperaturdata, kan GDD for en plante beregnes.

Trinene til at gøre dette manuelt er:

1. Find basistemperaturen for planten. For eksempel er basistemperaturen for jordbær 10°C.

1. Fra `temperature.csv`, find dagens højeste og laveste temperaturer.

1. Brug GDD-beregningen, der blev givet tidligere, til at beregne GDD.

For eksempel, hvis dagens højeste temperatur er 25°C, og den laveste er 12°C:

![GDD = 25 + 12 divideret med 2, derefter træk 10 fra resultatet, hvilket giver 8.5](../../../../../translated_images/gdd-calculation-strawberries.59f57db94b22adb8ff6efb951ace33af104a1c6ccca3ffb0f8169c14cb160c90.da.png)

* 25 + 12 = 37
* 37 / 2 = 18.5
* 18.5 - 10 = 8.5

Derfor har jordbærrene modtaget **8.5** GDD. Jordbær har brug for omkring 250 GDD for at bære frugt, så der er stadig et stykke vej.

---

## 🚀 Udfordring

Planter har brug for mere end varme for at vokse. Hvilke andre ting er nødvendige?

For disse, undersøg om der findes sensorer, der kan måle dem. Hvad med aktuatorer til at kontrollere disse niveauer? Hvordan ville du sammensætte en eller flere IoT-enheder for at optimere plantevækst?

## Quiz efter forelæsning

[Quiz efter forelæsning](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/10)

## Gennemgang & Selvstudie

* Læs mere om digital landbrug på [Digital Agriculture Wikipedia-siden](https://wikipedia.org/wiki/Digital_agriculture). Læs også mere om præcisionslandbrug på [Precision Agriculture Wikipedia-siden](https://wikipedia.org/wiki/Precision_agriculture).
* Den fulde beregning af vækstdage (GDD) er mere kompliceret end den forenklede, der er givet her. Læs mere om den mere komplicerede ligning og hvordan man håndterer temperaturer under baseline på [Growing Degree Day Wikipedia-siden](https://wikipedia.org/wiki/Growing_degree-day).
* Mad kan blive knap i fremtiden, hvis vi fortsat bruger de samme metoder til landbrug. Lær mere om højteknologiske landbrugsteknikker i denne [Hi-Tech Farms of Future video på YouTube](https://www.youtube.com/watch?v=KIEOuKD9KX8).

## Opgave

[Visualiser GDD-data ved hjælp af en Jupyter Notebook](assignment.md)

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på at sikre nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der opstår som følge af brugen af denne oversættelse.