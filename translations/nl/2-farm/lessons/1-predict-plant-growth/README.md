<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d105b44deae539165855c976dcdeca99",
  "translation_date": "2025-08-27T21:01:07+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/README.md",
  "language_code": "nl"
}
-->
# Voorspel plantengroei met IoT

![Een schetsmatige weergave van deze les](../../../../../translated_images/nl/lesson-5.42b234299279d263143148b88ab4583861a32ddb03110c6c1120e41bb88b2592.jpg)

> Schetsnotitie door [Nitya Narasimhan](https://github.com/nitya). Klik op de afbeelding voor een grotere versie.

## Quiz voorafgaand aan de les

[Quiz voorafgaand aan de les](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/9)

## Inleiding

Planten hebben bepaalde dingen nodig om te groeien - water, koolstofdioxide, voedingsstoffen, licht en warmte. In deze les leer je hoe je de groei- en rijpheidssnelheid van planten kunt berekenen door de luchttemperatuur te meten.

In deze les behandelen we:

* [Digitale landbouw](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Waarom is temperatuur belangrijk bij landbouw?](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Meet de omgevingstemperatuur](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Groei-graad-dagen (GDD)](../../../../../2-farm/lessons/1-predict-plant-growth)
* [Bereken GDD met behulp van temperatuursensorgegevens](../../../../../2-farm/lessons/1-predict-plant-growth)

## Digitale landbouw

Digitale landbouw transformeert de manier waarop we landbouw bedrijven door gebruik te maken van tools om gegevens te verzamelen, op te slaan en te analyseren. We bevinden ons momenteel in een periode die door het World Economic Forum wordt beschreven als de 'Vierde Industriële Revolutie', en de opkomst van digitale landbouw wordt aangeduid als de 'Vierde Landbouwrevolutie' of 'Landbouw 4.0'.

> 🎓 De term Digitale Landbouw omvat ook de hele 'landbouwwaardeketen', dat wil zeggen de volledige reis van boerderij tot bord. Dit omvat het volgen van de kwaliteit van producten terwijl voedsel wordt verzonden en verwerkt, magazijn- en e-commercesystemen, en zelfs apps voor het huren van tractoren!

Deze veranderingen stellen boeren in staat om hogere opbrengsten te behalen, minder meststoffen en pesticiden te gebruiken en efficiënter water te geven. Hoewel deze technologieën voornamelijk in rijkere landen worden gebruikt, dalen de prijzen van sensoren en andere apparaten langzaam, waardoor ze toegankelijker worden in ontwikkelingslanden.

Enkele technieken die mogelijk worden gemaakt door digitale landbouw zijn:

* Temperatuurmeting - het meten van temperatuur stelt boeren in staat om plantengroei en rijpheid te voorspellen.
* Geautomatiseerd water geven - het meten van bodemvocht en het inschakelen van irrigatiesystemen wanneer de bodem te droog is, in plaats van op vaste tijden water te geven. Tijdgebonden water geven kan leiden tot onderbewatering tijdens een hete, droge periode, of overbewatering tijdens regen. Door alleen water te geven wanneer de bodem het nodig heeft, kunnen boeren hun watergebruik optimaliseren.
* Ongediertebestrijding - boeren kunnen camera's op geautomatiseerde robots of drones gebruiken om op ongedierte te controleren en vervolgens alleen pesticiden toe te passen waar dat nodig is, waardoor de hoeveelheid gebruikte pesticiden en de afvoer van pesticiden naar lokale waterbronnen wordt verminderd.

✅ Doe wat onderzoek. Welke andere technieken worden gebruikt om landbouwopbrengsten te verbeteren?

> 🎓 De term 'Precisielandbouw' wordt gebruikt om het observeren, meten en reageren op gewassen op basis van een veld of zelfs delen van een veld te definiëren. Dit omvat het meten van water-, voedings- en ongedierte-niveaus en het nauwkeurig reageren, zoals het alleen water geven van een klein deel van een veld.

## Waarom is temperatuur belangrijk bij landbouw?

Bij het leren over planten wordt de meeste studenten geleerd over de noodzaak van water, licht, koolstofdioxide en voedingsstoffen. Planten hebben echter ook warmte nodig om te groeien - dit is waarom planten in de lente bloeien als de temperatuur stijgt, waarom sneeuwklokjes of narcissen vroeg kunnen ontkiemen door een korte warme periode, en waarom kassen en serres zo goed zijn in het laten groeien van planten.

> 🎓 Kassen en serres doen een vergelijkbaar werk, maar met een belangrijk verschil. Kassen worden kunstmatig verwarmd en stellen boeren in staat om temperaturen nauwkeuriger te regelen, terwijl serres afhankelijk zijn van de zon voor warmte en meestal alleen ramen of andere openingen hebben om warmte te laten ontsnappen.

Planten hebben een basis- of minimumtemperatuur, een optimale temperatuur en een maximumtemperatuur, allemaal gebaseerd op dagelijkse gemiddelde temperaturen.

* Basistemperatuur - dit is de minimale dagelijkse gemiddelde temperatuur die nodig is voor een plant om te groeien.
* Optimale temperatuur - dit is de beste dagelijkse gemiddelde temperatuur om de meeste groei te bereiken.
* Maximumtemperatuur - dit is de maximale temperatuur die een plant kan verdragen. Boven deze temperatuur stopt de plant met groeien in een poging om water te besparen en te overleven.

> 💁 Dit zijn gemiddelde temperaturen, gemiddeld over de dag- en nachttemperaturen. Planten hebben ook verschillende temperaturen nodig overdag en 's nachts om efficiënter te kunnen fotosynthetiseren en 's nachts energie te besparen.

Elke plantensoort heeft verschillende waarden voor hun basis-, optimale en maximale temperatuur. Dit is waarom sommige planten gedijen in warme landen en andere in koudere landen.

✅ Doe wat onderzoek. Voor planten in je tuin, school of lokale park, kun je de basistemperatuur vinden?

![Een grafiek die de groeisnelheid toont die stijgt naarmate de temperatuur stijgt, en vervolgens daalt als de temperatuur te hoog wordt](../../../../../translated_images/nl/plant-growth-temp-graph.c6d69c9478e6ca83.webp)

De bovenstaande grafiek toont een voorbeeld van een groeisnelheid-temperatuur-grafiek. Tot aan de basistemperatuur is er geen groei. De groeisnelheid neemt toe tot de optimale temperatuur, en daalt daarna na het bereiken van deze piek. Bij de maximumtemperatuur stopt de groei.

De vorm van deze grafiek varieert per plantensoort. Sommige hebben scherpere dalingen boven de optimale temperatuur, andere hebben langzamere stijgingen van de basis- naar de optimale temperatuur.

> 💁 Om de beste groei te bereiken, moet een boer de drie temperatuurwaarden kennen en de vorm van de grafieken begrijpen voor de planten die hij of zij kweekt.

Als een boer de temperatuur kan regelen, bijvoorbeeld in een commerciële kas, dan kan hij of zij optimaliseren voor de planten. Een commerciële kas die tomaten kweekt, zal bijvoorbeeld de temperatuur instellen op ongeveer 25°C overdag en 20°C 's nachts om de snelste groei te bereiken.

> 🍅 Door deze temperaturen te combineren met kunstlicht, meststoffen en gecontroleerde CO2-niveaus kunnen commerciële telers het hele jaar door kweken en oogsten.

## Meet de omgevingstemperatuur

Temperatuursensoren kunnen worden gebruikt met IoT-apparaten om de omgevingstemperatuur te meten.

### Taak - meet temperatuur

Werk de relevante handleiding door om temperaturen te monitoren met je IoT-apparaat:

* [Arduino - Wio Terminal](wio-terminal-temp.md)
* [Single-board computer - Raspberry Pi](pi-temp.md)
* [Single-board computer - Virtueel apparaat](virtual-device-temp.md)

## Groei-graad-dagen

Groei-graad-dagen (ook wel groeigraad-eenheden genoemd) zijn een manier om de groei van planten te meten op basis van de temperatuur. Als een plant voldoende water, voedingsstoffen en CO2 heeft, bepaalt de temperatuur de groeisnelheid.

Groei-graad-dagen, of GDD, worden per dag berekend als de gemiddelde temperatuur in graden Celsius voor een dag boven de basistemperatuur van de plant. Elke plant heeft een bepaald aantal GDD nodig om te groeien, te bloeien of een gewas te produceren en te rijpen. Hoe meer GDD per dag, hoe sneller de plant groeit.

> 🇺🇸 Voor Amerikanen kunnen groei-graad-dagen ook worden berekend met Fahrenheit. 5 GDD (in Celsius) is gelijk aan 9 GDD (in Fahrenheit).

De volledige formule voor GDD is een beetje ingewikkeld, maar er is een vereenvoudigde vergelijking die vaak wordt gebruikt als een goede benadering:

![GDD = T max + T min gedeeld door 2, alles minus T base](../../../../../translated_images/nl/gdd-calculation.79b3660f9c5757aa92dc2dd2cdde75344e2d2c1565c4b3151640f7887edc0275.png)

* **GDD** - dit is het aantal groei-graad-dagen
* **T max** - dit is de dagelijkse maximumtemperatuur in graden Celsius
* **T min** - dit is de dagelijkse minimumtemperatuur in graden Celsius
* **T base** - dit is de basistemperatuur van de plant in graden Celsius

> 💁 Er zijn variaties die rekening houden met T max boven 30°C of T min onder T base, maar die negeren we voorlopig.

### Voorbeeld - Maïs 🌽

Afhankelijk van de variëteit heeft maïs tussen de 800 en 2.700 GDD nodig om te rijpen, met een basistemperatuur van 10°C.

Op de eerste dag boven de basistemperatuur werden de volgende temperaturen gemeten:

| Meting      | Temp °C |
| :---------- | :-----: |
| Maximum     | 16      |
| Minimum     | 12      |

Als we deze getallen in onze berekening invoeren:

* T max = 16
* T min = 12
* T base = 10

Geeft dit de volgende berekening:

![GDD = 16 + 12 gedeeld door 2, alles minus 10, geeft een antwoord van 4](../../../../../translated_images/nl/gdd-calculation-corn.64a58b7a7afcd0dfd46ff733996d939f17f4f3feac9f0d1c632be3523e51ebd9.png)

De maïs ontving 4 GDD op die dag. Als we uitgaan van een maïsvariëteit die 800 GDD nodig heeft om te rijpen, heeft het nog 796 GDD nodig om rijpheid te bereiken.

✅ Doe wat onderzoek. Voor planten in je tuin, school of lokale park, kun je het aantal GDD vinden dat nodig is om rijpheid te bereiken of gewassen te produceren?

## Bereken GDD met behulp van temperatuursensorgegevens

Planten groeien niet op vaste data - bijvoorbeeld, je kunt geen zaad planten en weten dat de plant precies 100 dagen later vruchten zal dragen. In plaats daarvan kun je als boer een ruwe schatting hebben van hoe lang een plant nodig heeft om te groeien, en dan dagelijks controleren om te zien wanneer de gewassen klaar zijn.

Dit heeft een enorme impact op de arbeidskosten op een grote boerderij en brengt het risico met zich mee dat de boer gewassen mist die onverwacht vroeg klaar zijn. Door temperaturen te meten, kan de boer de GDD berekenen die een plant heeft ontvangen, waardoor ze alleen hoeven te controleren wanneer de verwachte rijpheid nadert.

Door temperatuurgegevens te verzamelen met een IoT-apparaat, kan een boer automatisch een melding krijgen wanneer planten bijna rijp zijn. Een typische architectuur hiervoor is dat de IoT-apparaten de temperatuur meten en deze telemetriegegevens via internet publiceren met iets als MQTT. Servercode luistert vervolgens naar deze gegevens en slaat ze ergens op, bijvoorbeeld in een database. Dit betekent dat de gegevens later kunnen worden geanalyseerd, zoals een nachtelijke taak om de GDD voor de dag te berekenen, de totale GDD voor elk gewas tot nu toe op te tellen en een waarschuwing te geven als een plant bijna rijp is.

![Telemetriegegevens worden naar een server verzonden en vervolgens opgeslagen in een database](../../../../../translated_images/nl/save-telemetry-database.ddc9c6bea0c5ba39.webp)

De servercode kan de gegevens ook aanvullen door extra informatie toe te voegen. Bijvoorbeeld, het IoT-apparaat kan een identificator publiceren om aan te geven welk apparaat het is, en de servercode kan dit gebruiken om de locatie van het apparaat op te zoeken en welke gewassen het bewaakt. Het kan ook basisgegevens toevoegen zoals de huidige tijd, omdat sommige IoT-apparaten niet over de benodigde hardware beschikken om een nauwkeurige tijd bij te houden, of extra code nodig hebben om de huidige tijd via internet te lezen.

✅ Waarom denk je dat verschillende velden verschillende temperaturen kunnen hebben?

### Taak - publiceer temperatuurinformatie

Werk de relevante handleiding door om temperatuurgegevens via MQTT te publiceren met je IoT-apparaat, zodat deze later kunnen worden geanalyseerd:

* [Arduino - Wio Terminal](wio-terminal-temp-publish.md)
* [Single-board computer - Raspberry Pi/Virtual IoT device](single-board-computer-temp-publish.md)

### Taak - verzamel en sla de temperatuurinformatie op

Zodra het IoT-apparaat telemetrie publiceert, kan de servercode worden geschreven om zich op deze gegevens te abonneren en ze op te slaan. In plaats van ze op te slaan in een database, zal de servercode ze opslaan in een Comma Separated Values (CSV)-bestand. CSV-bestanden slaan gegevens op als rijen met waarden als tekst, waarbij elke waarde wordt gescheiden door een komma en elke record op een nieuwe regel staat. Ze zijn een handige, mens-leesbare en goed ondersteunde manier om gegevens als bestand op te slaan.

Het CSV-bestand zal twee kolommen hebben - *datum* en *temperatuur*. De *datum*-kolom wordt ingesteld als de huidige datum en tijd waarop het bericht door de server werd ontvangen, de *temperatuur* komt uit het telemetriebericht.

1. Herhaal de stappen in les 4 om servercode te maken om telemetrie te ontvangen. Je hoeft geen code toe te voegen om opdrachten te publiceren.

    De stappen hiervoor zijn:

    * Configureer en activeer een Python Virtual Environment

    * Installeer het paho-mqtt pip-pakket

    * Schrijf de code om te luisteren naar MQTT-berichten die op het telemetrieonderwerp worden gepubliceerd

      > ⚠️ Je kunt [de instructies in les 4 voor het maken van een Python-app om telemetrie te ontvangen indien nodig raadplegen](../../../1-getting-started/lessons/4-connect-internet/README.md#receive-telemetry-from-the-mqtt-broker).

    Noem de map voor dit project `temperature-sensor-server`.

1. Zorg ervoor dat de `client_name` overeenkomt met dit project:

    ```cpp
    client_name = id + 'temperature_sensor_server'
    ```

1. Voeg de volgende imports toe aan de bovenkant van het bestand, onder de bestaande imports:

    ```python
    from os import path
    import csv
    from datetime import datetime
    ```

    Dit importeert een bibliotheek voor het lezen van bestanden, een bibliotheek om met CSV-bestanden te werken, en een bibliotheek om te helpen met datums en tijden.

1. Voeg de volgende code toe vóór de functie `handle_telemetry`:

    ```python
    temperature_file_name = 'temperature.csv'
    fieldnames = ['date', 'temperature']
    
    if not path.exists(temperature_file_name):
        with open(temperature_file_name, mode='w') as csv_file:
            writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
            writer.writeheader()
    ```

    Deze code verklaart enkele constanten voor de naam van het bestand waarin moet worden geschreven en de namen van de kolomkoppen voor het CSV-bestand. De eerste rij van een CSV-bestand bevat traditioneel kolomkoppen gescheiden door komma's.

    De code controleert vervolgens of het CSV-bestand al bestaat. Als het niet bestaat, wordt het gemaakt met de kolomkoppen op de eerste rij.

1. Voeg de volgende code toe aan het einde van de functie `handle_telemetry`:

    ```python
    with open(temperature_file_name, mode='a') as temperature_file:        
        temperature_writer = csv.DictWriter(temperature_file, fieldnames=fieldnames)
        temperature_writer.writerow({'date' : datetime.now().astimezone().replace(microsecond=0).isoformat(), 'temperature' : payload['temperature']})
    ```
Deze code opent het CSV-bestand en voegt vervolgens een nieuwe rij toe aan het einde. De rij bevat de huidige datum en tijd in een menselijk leesbaar formaat, gevolgd door de temperatuur die is ontvangen van het IoT-apparaat. De gegevens worden opgeslagen in [ISO 8601-formaat](https://wikipedia.org/wiki/ISO_8601) met de tijdzone, maar zonder microseconden.

1. Voer deze code op dezelfde manier uit als eerder, en zorg ervoor dat je IoT-apparaat gegevens verzendt. Een CSV-bestand genaamd `temperature.csv` wordt aangemaakt in dezelfde map. Als je het opent, zie je datums/tijden en temperatuurmetingen:

    ```output
    date,temperature
    2021-04-19T17:21:36-07:00,25
    2021-04-19T17:31:36-07:00,24
    2021-04-19T17:41:36-07:00,25
    ```

1. Laat deze code een tijdje draaien om gegevens te verzamelen. Idealiter laat je dit een hele dag draaien om voldoende gegevens te verzamelen voor GDD-berekeningen.

    
> 💁 Als je een virtueel IoT-apparaat gebruikt, selecteer dan het willekeurige selectievakje en stel een bereik in om te voorkomen dat je steeds dezelfde temperatuurwaarde krijgt.
    ![Selecteer het willekeurige selectievakje en stel een bereik in](../../../../../translated_images/nl/select-the-random-checkbox-and-set-a-range.32cf4bc7c12e797f.webp) 

    > 💁 Als je dit een hele dag wilt laten draaien, zorg er dan voor dat de computer waarop je servercode draait niet in slaapstand gaat, door je energie-instellingen te wijzigen of iets te gebruiken zoals [dit Python-script om het systeem actief te houden](https://github.com/jaqsparow/keep-system-active).
    
> 💁 Je kunt deze code vinden in de map [code-server/temperature-sensor-server](../../../../../2-farm/lessons/1-predict-plant-growth/code-server/temperature-sensor-server).

### Taak - bereken GDD met behulp van de opgeslagen gegevens

Zodra de server temperatuurgegevens heeft vastgelegd, kan de GDD voor een plant worden berekend.

De stappen om dit handmatig te doen zijn:

1. Zoek de basistemperatuur voor de plant. Bijvoorbeeld, voor aardbeien is de basistemperatuur 10°C.

1. Zoek in de `temperature.csv` de hoogste en laagste temperaturen van de dag.

1. Gebruik de eerder gegeven GDD-berekening om de GDD te berekenen.

Bijvoorbeeld, als de hoogste temperatuur van de dag 25°C is en de laagste 12°C:

![GDD = 25 + 12 gedeeld door 2, trek vervolgens 10 af van het resultaat, wat 8,5 oplevert](../../../../../translated_images/nl/gdd-calculation-strawberries.59f57db94b22adb8ff6efb951ace33af104a1c6ccca3ffb0f8169c14cb160c90.png)

* 25 + 12 = 37
* 37 / 2 = 18,5
* 18,5 - 10 = 8,5

Daarom hebben de aardbeien **8,5** GDD ontvangen. Aardbeien hebben ongeveer 250 GDD nodig om vruchten te dragen, dus het duurt nog even.

---

## 🚀 Uitdaging

Planten hebben meer nodig dan alleen warmte om te groeien. Wat hebben ze nog meer nodig?

Zoek uit of er sensoren zijn die deze dingen kunnen meten. En hoe zit het met actuatoren om deze niveaus te regelen? Hoe zou je een of meer IoT-apparaten samenstellen om de plantengroei te optimaliseren?

## Quiz na de les

[Quiz na de les](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/10)

## Herziening & Zelfstudie

* Lees meer over digitale landbouw op de [Wikipedia-pagina over digitale landbouw](https://wikipedia.org/wiki/Digital_agriculture). Lees ook meer over precisielandbouw op de [Wikipedia-pagina over precisielandbouw](https://wikipedia.org/wiki/Precision_agriculture).
* De volledige berekening van groeigraaddagen is ingewikkelder dan de vereenvoudigde versie die hier wordt gegeven. Lees meer over de complexere vergelijking en hoe om te gaan met temperaturen onder de basislijn op de [Wikipedia-pagina over groeigraaddagen](https://wikipedia.org/wiki/Growing_degree-day).
* Voedsel kan in de toekomst schaars worden als we dezelfde methoden voor landbouw blijven gebruiken. Leer meer over hightech landbouwtechnieken in deze [Hi-Tech Farms of Future-video op YouTube](https://www.youtube.com/watch?v=KIEOuKD9KX8).

## Opdracht

[Visualiseer GDD-gegevens met behulp van een Jupyter Notebook](assignment.md)

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.