<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f74f4ccb61f00e5f7e9f49c3ed416e36",
  "translation_date": "2025-08-27T20:54:04+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/README.md",
  "language_code": "nl"
}
-->
# Trigger fruitkwaliteit detecteren met een sensor

![Een schetsmatig overzicht van deze les](../../../../../translated_images/nl/lesson-18.92c32ed1d354caa5a54baa4032cf0b172d4655e8e326ad5d46c558a0def15365.jpg)

> Sketchnote door [Nitya Narasimhan](https://github.com/nitya). Klik op de afbeelding voor een grotere versie.

## Quiz voorafgaand aan de les

[Quiz voorafgaand aan de les](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/35)

## Introductie

Een IoT-toepassing bestaat niet alleen uit één enkel apparaat dat gegevens verzamelt en naar de cloud stuurt. Vaak werken meerdere apparaten samen om gegevens uit de fysieke wereld te verzamelen via sensoren, beslissingen te nemen op basis van die gegevens en terug te communiceren met de fysieke wereld via actuatoren of visualisaties.

In deze les leer je meer over het ontwerpen van complexe IoT-toepassingen, waarbij meerdere sensoren en cloudservices worden geïntegreerd om gegevens te analyseren en op te slaan, en een reactie wordt getoond via een actuator. Je leert hoe je een prototype voor een fruitkwaliteitscontrolesysteem kunt ontwerpen, inclusief het gebruik van nabijheidssensoren om de IoT-toepassing te activeren en hoe de architectuur van dit prototype eruit zou zien.

In deze les behandelen we:

* [Complexe IoT-toepassingen ontwerpen](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Een fruitkwaliteitscontrolesysteem ontwerpen](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Fruitkwaliteitscontrole activeren met een sensor](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Gegevens gebruikt voor een fruitkwaliteitsdetector](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Ontwikkelaarsapparaten gebruiken om meerdere IoT-apparaten te simuleren](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Overgang naar productie](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)

> 🗑 Dit is de laatste les in dit project, dus vergeet niet om na het voltooien van deze les en de opdracht je cloudservices op te ruimen. Je hebt de services nodig om de opdracht te voltooien, dus zorg ervoor dat je dat eerst doet.
>
> Raadpleeg [de gids voor het opruimen van je project](../../../clean-up.md) indien nodig voor instructies.

## Complexe IoT-toepassingen ontwerpen

IoT-toepassingen bestaan uit veel componenten. Dit omvat een verscheidenheid aan apparaten en internetservices.

IoT-toepassingen kunnen worden beschreven als *things* (apparaten) die gegevens verzenden die *insights* genereren. Deze *insights* leiden tot *actions* om een bedrijf of proces te verbeteren. Een voorbeeld is een motor (het apparaat) die temperatuurgegevens verzendt. Deze gegevens worden gebruikt om te evalueren of de motor naar verwachting presteert (het inzicht). Het inzicht wordt gebruikt om proactief prioriteit te geven aan het onderhoudsschema van de motor (de actie).

* Verschillende apparaten verzamelen verschillende soorten gegevens.
* IoT-services bieden inzichten op basis van die gegevens, soms aangevuld met gegevens uit andere bronnen.
* Deze inzichten leiden tot acties, zoals het aansturen van actuatoren in apparaten of het visualiseren van gegevens.

### Referentie IoT-architectuur

![Een referentie IoT-architectuur](../../../../../translated_images/nl/iot-reference-architecture.2278b98b55c6d4e89bde18eada3688d893861d43507641804dd2f9d3079cfaa0.png)

De bovenstaande afbeelding toont een referentie IoT-architectuur.

> 🎓 Een *referentiearchitectuur* is een voorbeeldarchitectuur die je kunt gebruiken als referentie bij het ontwerpen van nieuwe systemen. In dit geval kun je bij het bouwen van een nieuw IoT-systeem de referentiearchitectuur volgen en je eigen apparaten en services waar nodig vervangen.

* **Things** zijn apparaten die gegevens verzamelen via sensoren, mogelijk in interactie met edge-services om die gegevens te interpreteren, zoals beeldclassificators om beeldgegevens te interpreteren. De gegevens van de apparaten worden naar een IoT-service gestuurd.
* **Insights** komen van serverloze toepassingen of van analyses uitgevoerd op opgeslagen gegevens.
* **Actions** kunnen commando's zijn die naar apparaten worden gestuurd, of visualisaties van gegevens waarmee mensen beslissingen kunnen nemen.

![Een referentie IoT-architectuur](../../../../../translated_images/nl/iot-reference-architecture-azure.0b8d2161af924cb18ae48a8558a19541cca47f27264851b5b7e56d7b8bb372ac.png)

De bovenstaande afbeelding toont enkele van de componenten en services die tot nu toe in deze lessen zijn behandeld en hoe ze samenkomen in een referentie IoT-architectuur.

* **Things** - je hebt apparaatcode geschreven om gegevens te verzamelen via sensoren en afbeeldingen te analyseren met Custom Vision, zowel in de cloud als op een edge-apparaat. Deze gegevens werden naar IoT Hub gestuurd.
* **Insights** - je hebt Azure Functions gebruikt om te reageren op berichten die naar een IoT Hub werden gestuurd, en gegevens opgeslagen voor latere analyse in Azure Storage.
* **Actions** - je hebt actuatoren aangestuurd op basis van beslissingen die in de cloud zijn genomen en commando's die naar de apparaten zijn gestuurd, en je hebt gegevens gevisualiseerd met Azure Maps.

✅ Denk na over andere IoT-apparaten die je hebt gebruikt, zoals slimme huishoudelijke apparaten. Wat zijn de apparaten, inzichten en acties die betrokken zijn bij dat apparaat en de bijbehorende software?

Dit patroon kan zo groot of klein worden opgeschaald als nodig is, door meer apparaten en meer services toe te voegen.

### Gegevens en beveiliging

Bij het definiëren van de architectuur van je systeem moet je voortdurend rekening houden met gegevens en beveiliging.

* Welke gegevens verzendt en ontvangt je apparaat?
* Hoe moeten die gegevens worden beveiligd en beschermd?
* Hoe moet toegang tot het apparaat en de cloudservice worden gecontroleerd?

✅ Denk na over de gegevensbeveiliging van IoT-apparaten die je bezit. Hoeveel van die gegevens zijn persoonlijk en moeten privé worden gehouden, zowel tijdens verzending als wanneer ze worden opgeslagen? Welke gegevens mogen niet worden opgeslagen?

## Een fruitkwaliteitscontrolesysteem ontwerpen

Laten we nu het idee van apparaten, inzichten en acties toepassen op onze fruitkwaliteitsdetector om een grotere end-to-end toepassing te ontwerpen.

Stel je voor dat je de taak hebt gekregen om een fruitkwaliteitsdetector te bouwen die wordt gebruikt in een verwerkingsfabriek. Fruit beweegt op een transportsysteem waar werknemers momenteel handmatig het fruit controleren en onrijp fruit verwijderen zodra het arriveert. Om kosten te besparen wil de eigenaar van de fabriek een geautomatiseerd systeem.

✅ Een van de trends met de opkomst van IoT (en technologie in het algemeen) is dat handmatige banen worden vervangen door machines. Doe wat onderzoek: Hoeveel banen worden naar schatting verloren door IoT? Hoeveel nieuwe banen worden gecreëerd door het bouwen van IoT-apparaten?

Je moet een systeem bouwen waarin fruit wordt gedetecteerd zodra het op de transportband arriveert, vervolgens wordt gefotografeerd en gecontroleerd met een AI-model dat op de edge draait. De resultaten worden naar de cloud gestuurd om te worden opgeslagen, en als het fruit onrijp is, wordt een melding gegeven zodat het onrijpe fruit kan worden verwijderd.

|   |   |
| - | - |
| **Things** | Detector voor fruit dat aankomt op de transportband<br>Camera om het fruit te fotograferen en te classificeren<br>Edge-apparaat dat de classificator uitvoert<br>Apparaat om onrijp fruit te melden |
| **Insights** | Beslissen om de rijpheid van het fruit te controleren<br>De resultaten van de rijpheidsclassificatie opslaan<br>Bepalen of er een melding nodig is over onrijp fruit |
| **Actions** | Een commando sturen naar een apparaat om het fruit te fotograferen en te controleren met een beeldclassificator<br>Een commando sturen naar een apparaat om te melden dat het fruit onrijp is |

### Je toepassing prototypen

![Een referentie IoT-architectuur voor fruitkwaliteitscontrole](../../../../../translated_images/nl/iot-reference-architecture-fruit-quality.cc705f121c3b6fa71c800d9630935ac34bc08223a04601e35f41d5e9b5dd5207.png)

De bovenstaande afbeelding toont een referentiearchitectuur voor deze prototype-toepassing.

* Een IoT-apparaat met een nabijheidssensor detecteert de aankomst van fruit. Dit stuurt een bericht naar de cloud om te melden dat fruit is gedetecteerd.
* Een serverloze toepassing in de cloud stuurt een commando naar een ander apparaat om een foto te maken en te classificeren.
* Een IoT-apparaat met een camera maakt een foto en stuurt deze naar een beeldclassificator die op de edge draait. De resultaten worden vervolgens naar de cloud gestuurd.
* Een serverloze toepassing in de cloud slaat deze informatie op om later te analyseren welk percentage fruit onrijp is. Als het fruit onrijp is, stuurt het een commando naar een ander IoT-apparaat om fabrieksmedewerkers te waarschuwen via een LED.

> 💁 Deze hele IoT-toepassing kan worden geïmplementeerd als één enkel apparaat, met alle logica om de beeldclassificatie te starten en de LED aan te sturen ingebouwd. Het kan een IoT Hub gebruiken om alleen het aantal gedetecteerde onrijpe vruchten bij te houden en het apparaat te configureren. In deze les wordt het uitgebreid om de concepten voor grootschalige IoT-toepassingen te demonstreren.

Voor het prototype implementeer je alles op één apparaat. Als je een microcontroller gebruikt, gebruik je een apart edge-apparaat om de beeldclassificator uit te voeren. Je hebt al veel geleerd van wat je nodig hebt om dit te bouwen.

## Fruitkwaliteitscontrole activeren met een sensor

Het IoT-apparaat heeft een soort trigger nodig om aan te geven wanneer fruit klaar is om te worden geclassificeerd. Een mogelijke trigger hiervoor is het meten van wanneer het fruit zich op de juiste locatie op de transportband bevindt door de afstand tot een sensor te meten.

![Nabijheidssensoren sturen laserstralen naar objecten zoals bananen en meten hoe lang het duurt voordat de straal wordt teruggekaatst](../../../../../translated_images/nl/proximity-sensor.f5cd752c77fb62fe.webp)

Nabijheidssensoren kunnen worden gebruikt om de afstand van de sensor tot een object te meten. Ze zenden meestal een straal van elektromagnetische straling uit, zoals een laserstraal of infraroodlicht, en detecteren vervolgens de straling die van een object wordt teruggekaatst. De tijd tussen het verzenden van de straal en het terugkaatsen van het signaal kan worden gebruikt om de afstand tot de sensor te berekenen.

> 💁 Je hebt waarschijnlijk nabijheidssensoren gebruikt zonder het te weten. De meeste smartphones schakelen het scherm uit wanneer je ze tegen je oor houdt om te voorkomen dat je per ongeluk een oproep beëindigt met je oorlel. Dit werkt met een nabijheidssensor die een object dicht bij het scherm detecteert tijdens een oproep en de aanraakfunctionaliteit uitschakelt totdat de telefoon een bepaalde afstand heeft.

### Taak - fruitkwaliteitsdetectie activeren met een afstandssensor

Werk de relevante gids door om een nabijheidssensor te gebruiken om een object te detecteren met je IoT-apparaat:

* [Arduino - Wio Terminal](wio-terminal-proximity.md)
* [Single-board computer - Raspberry Pi](pi-proximity.md)
* [Single-board computer - Virtueel apparaat](virtual-device-proximity.md)

## Gegevens gebruikt voor een fruitkwaliteitsdetector

Het prototype van de fruitdetector heeft meerdere componenten die met elkaar communiceren.

![De componenten communiceren met elkaar](../../../../../translated_images/nl/fruit-quality-detector-message-flow.adf2a65da8fd8741ac7af11361574de89adc126785d67606bb4d2ec00467e380.png)

* Een nabijheidssensor die de afstand tot een stuk fruit meet en dit naar IoT Hub stuurt
* Het commando om de camera te bedienen dat van IoT Hub naar het camera-apparaat komt
* De resultaten van de beeldclassificatie die naar IoT Hub worden gestuurd
* Het commando om een LED te bedienen om te waarschuwen wanneer het fruit onrijp is, dat van IoT Hub naar het apparaat met de LED wordt gestuurd

Het is goed om de structuur van deze berichten vooraf te definiëren, voordat je de toepassing bouwt.

> 💁 Vrijwel elke ervaren ontwikkelaar heeft op een bepaald moment in zijn carrière uren, dagen of zelfs weken besteed aan het opsporen van bugs die werden veroorzaakt door verschillen in de gegevens die werden verzonden in vergelijking met wat werd verwacht.

Bijvoorbeeld - als je temperatuurinformatie verzendt, hoe zou je de JSON definiëren? Je zou een veld genaamd `temperature` kunnen hebben, of je zou de gebruikelijke afkorting `temp` kunnen gebruiken.

```json
{
    "temperature": 20.7
}
```

vergeleken met:

```json
{
    "temp": 20.7
}
```

Je moet ook rekening houden met eenheden - is de temperatuur in °C of °F? Als je de temperatuur meet met een consumentapparaat en ze veranderen de weergave-eenheden, moet je ervoor zorgen dat de eenheden die naar de cloud worden gestuurd consistent blijven.

✅ Doe wat onderzoek: Hoe hebben problemen met eenheden ervoor gezorgd dat de $125 miljoen kostende Mars Climate Orbiter crashte?

Denk na over de gegevens die worden verzonden voor de fruitkwaliteitsdetector. Hoe zou je elk bericht definiëren? Waar zou je de gegevens analyseren en beslissingen nemen over welke gegevens moeten worden verzonden?

Bijvoorbeeld - het activeren van de beeldclassificatie met behulp van de nabijheidssensor. Het IoT-apparaat meet de afstand, maar waar wordt de beslissing genomen? Beslist het apparaat dat het fruit dichtbij genoeg is en stuurt het een bericht naar de IoT Hub om de classificatie te activeren? Of stuurt het nabijheidsmetingen en laat het de IoT Hub beslissen?

Het antwoord op vragen zoals deze is - het hangt ervan af. Elk gebruiksscenario is anders, daarom moet je als IoT-ontwikkelaar het systeem dat je bouwt begrijpen, hoe het wordt gebruikt en de gegevens die worden gedetecteerd.

* Als de beslissing wordt genomen door de IoT Hub, moet je meerdere afstandsmetingen verzenden.
* Als je te veel berichten verzendt, verhoogt dit de kosten van de IoT Hub en de hoeveelheid bandbreedte die door je IoT-apparaten wordt gebruikt (vooral in een fabriek met miljoenen apparaten). Het kan ook je apparaat vertragen.
* Als je de beslissing op het apparaat neemt, moet je een manier bieden om het apparaat te configureren om de machine fijn af te stemmen.

## Ontwikkelaarsapparaten gebruiken om meerdere IoT-apparaten te simuleren

Om je prototype te bouwen, moet je IoT-ontwikkelingskit zich gedragen als meerdere apparaten, die telemetrie verzenden en reageren op commando's.

### Meerdere IoT-apparaten simuleren op een Raspberry Pi of virtuele IoT-hardware

Bij gebruik van een single-board computer zoals een Raspberry Pi kun je meerdere toepassingen tegelijk uitvoeren. Dit betekent dat je meerdere IoT-apparaten kunt simuleren door meerdere toepassingen te maken, één per 'IoT-apparaat'. Bijvoorbeeld, je kunt elk apparaat implementeren als een afzonderlijk Python-bestand en ze uitvoeren in verschillende terminalsessies.
> 💁 Houd er rekening mee dat sommige hardware niet werkt wanneer deze tegelijkertijd door meerdere applicaties wordt gebruikt.
### Meerdere apparaten simuleren op een microcontroller

Microcontrollers zijn ingewikkelder als het gaat om het simuleren van meerdere apparaten. In tegenstelling tot single board computers kun je niet meerdere applicaties tegelijkertijd uitvoeren; je moet alle logica voor de afzonderlijke IoT-apparaten in één applicatie opnemen.

Enkele suggesties om dit proces eenvoudiger te maken zijn:

* Maak één of meer klassen per IoT-apparaat - bijvoorbeeld klassen genaamd `DistanceSensor`, `ClassifierCamera`, `LEDController`. Elk van deze klassen kan zijn eigen `setup`- en `loop`-methoden hebben die worden aangeroepen door de hoofd-`setup`- en `loop`-functies.
* Verwerk commando's op één centrale plek en stuur ze naar de relevante apparaatklasse indien nodig.
* In de hoofd-`loop`-functie moet je rekening houden met de timing voor elk verschillend apparaat. Bijvoorbeeld, als je een apparaatklasse hebt die elke 10 seconden moet verwerken, en een andere die elke seconde moet verwerken, gebruik dan een vertraging van 1 seconde in je hoofd-`loop`-functie. Elke `loop`-aanroep activeert de relevante code voor het apparaat dat elke seconde moet verwerken, en gebruik een teller om elke loop te tellen, waarbij je het andere apparaat verwerkt wanneer de teller 10 bereikt (en de teller daarna reset).

## Overgang naar productie

Het prototype vormt de basis voor een definitief productiesysteem. Enkele verschillen wanneer je naar productie gaat zijn:

* Robuuste componenten - gebruik hardware die is ontworpen om bestand te zijn tegen de ruis, hitte, trillingen en stress van een fabriek.
* Gebruik van interne communicatie - sommige componenten communiceren rechtstreeks en vermijden de stap naar de cloud, waarbij alleen gegevens naar de cloud worden verzonden om te worden opgeslagen. Hoe dit wordt gedaan hangt af van de fabrieksconfiguratie, met directe communicatie of door een deel van de IoT-service op de edge uit te voeren via een gateway-apparaat.
* Configuratie-opties - elke fabriek en use case is anders, dus de hardware moet configureerbaar zijn. Bijvoorbeeld, de nabijheidssensor moet mogelijk verschillende soorten fruit op verschillende afstanden detecteren. In plaats van de afstand om de classificatie te activeren hard te coderen, wil je dit configureerbaar maken via de cloud, bijvoorbeeld met behulp van een device twin.
* Geautomatiseerde fruitverwijdering - in plaats van een LED die aangeeft dat fruit onrijp is, zouden geautomatiseerde apparaten het fruit verwijderen.

✅ Doe wat onderzoek: Op welke andere manieren zouden productieapparaten verschillen van ontwikkelaarskits?

---

## 🚀 Uitdaging

In deze les heb je enkele concepten geleerd die je nodig hebt om een IoT-systeem te ontwerpen. Denk terug aan de eerdere projecten. Hoe passen ze in de referentiearchitectuur die hierboven is getoond?

Kies een van de projecten tot nu toe en denk na over het ontwerp van een meer geavanceerde oplossing die meerdere mogelijkheden combineert, verdergaand dan wat in de projecten is behandeld. Teken de architectuur en denk na over alle apparaten en diensten die je nodig zou hebben.

Bijvoorbeeld - een voertuigvolgsysteem dat GPS combineert met sensoren om zaken zoals temperaturen in een gekoelde vrachtwagen, de aan- en uit-tijden van de motor, en de identiteit van de chauffeur te monitoren. Wat zijn de betrokken apparaten, de betrokken diensten, de gegevens die worden verzonden en de beveiligings- en privacyoverwegingen?

## Quiz na de les

[Quiz na de les](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/36)

## Review & Zelfstudie

* Lees meer over IoT-architectuur in de [Azure IoT referentiearchitectuur documentatie op Microsoft docs](https://docs.microsoft.com/azure/architecture/reference-architectures/iot?WT.mc_id=academic-17441-jabenn)
* Lees meer over device twins in de [begrijp en gebruik device twins in IoT Hub documentatie op Microsoft docs](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-device-twins?WT.mc_id=academic-17441-jabenn)
* Lees over OPC-UA, een machine-to-machine communicatieprotocol dat wordt gebruikt in industriële automatisering op de [OPC-UA pagina op Wikipedia](https://wikipedia.org/wiki/OPC_Unified_Architecture)

## Opdracht

[Bouw een fruitkwaliteitsdetector](assignment.md)

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.