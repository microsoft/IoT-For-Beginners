<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1c9e5fa8b7be726c75a97232b1e41c97",
  "translation_date": "2025-08-27T20:28:05+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/README.md",
  "language_code": "nl"
}
-->
# Controleer voorraad met een IoT-apparaat

![Een schetsmatige samenvatting van deze les](../../../../../translated_images/lesson-20.0211df9551a8abb300fc8fcf7dc2789468dea2eabe9202273ac077b0ba37f15e.nl.jpg)

> Sketchnote door [Nitya Narasimhan](https://github.com/nitya). Klik op de afbeelding voor een grotere versie.

## Quiz voorafgaand aan de les

[Quiz voorafgaand aan de les](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/39)

## Introductie

In de vorige les heb je geleerd over de verschillende toepassingen van objectdetectie in de detailhandel. Je hebt ook geleerd hoe je een objectdetector kunt trainen om voorraad te identificeren. In deze les leer je hoe je je objectdetector kunt gebruiken vanaf je IoT-apparaat om voorraad te tellen.

In deze les behandelen we:

* [Voorraad tellen](../../../../../5-retail/lessons/2-check-stock-device)
* [Je objectdetector aanroepen vanaf je IoT-apparaat](../../../../../5-retail/lessons/2-check-stock-device)
* [Omgrenzende kaders](../../../../../5-retail/lessons/2-check-stock-device)
* [Het model opnieuw trainen](../../../../../5-retail/lessons/2-check-stock-device)
* [Voorraad tellen](../../../../../5-retail/lessons/2-check-stock-device)

> 🗑 Dit is de laatste les in dit project, dus vergeet niet om na het voltooien van deze les en de opdracht je clouddiensten op te ruimen. Je hebt de diensten nodig om de opdracht te voltooien, dus zorg ervoor dat je dat eerst doet.
>
> Raadpleeg [de gids voor het opruimen van je project](../../../clean-up.md) indien nodig voor instructies.

## Voorraad tellen

Objectdetectors kunnen worden gebruikt voor voorraadcontrole, zowel om voorraad te tellen als om te controleren of voorraad zich op de juiste plek bevindt. IoT-apparaten met camera's kunnen overal in de winkel worden ingezet om voorraad te monitoren, te beginnen met hotspots waar het belangrijk is dat items worden aangevuld, zoals gebieden waar kleine aantallen van waardevolle items worden opgeslagen.

Bijvoorbeeld, als een camera gericht is op een set planken die 8 blikken tomatenpuree kunnen bevatten, en een objectdetector detecteert slechts 7 blikken, dan ontbreekt er één en moet deze worden aangevuld.

![7 blikken tomatenpuree op een plank, 4 op de bovenste rij, 3 bovenaan](../../../../../translated_images/stock-7-cans-tomato-paste.f86059cc573d7bec.nl.png)

In de bovenstaande afbeelding heeft een objectdetector 7 blikken tomatenpuree gedetecteerd op een plank die 8 blikken kan bevatten. Niet alleen kan het IoT-apparaat een melding sturen dat er moet worden aangevuld, maar het kan zelfs een indicatie geven van de locatie van het ontbrekende item, belangrijke gegevens als je robots gebruikt om planken aan te vullen.

> 💁 Afhankelijk van de winkel en de populariteit van het item, zou aanvullen waarschijnlijk niet gebeuren als er slechts 1 blik ontbreekt. Je zou een algoritme moeten bouwen dat bepaalt wanneer er moet worden aangevuld op basis van je producten, klanten en andere criteria.

✅ In welke andere scenario's zou je objectdetectie en robots kunnen combineren?

Soms kan de verkeerde voorraad op de planken staan. Dit kan een menselijke fout zijn bij het aanvullen, of klanten die van gedachten veranderen over een aankoop en een item terugzetten op de eerste beschikbare plek. Wanneer dit een niet-bederfelijk item is, zoals conserven, is dit een ergernis. Als het een bederfelijk item is, zoals diepvries- of gekoelde goederen, kan dit betekenen dat het product niet meer verkocht kan worden omdat het onmogelijk kan zijn om te bepalen hoe lang het item uit de vriezer is geweest.

Objectdetectie kan worden gebruikt om onverwachte items te detecteren, en opnieuw een mens of robot te waarschuwen om het item zo snel mogelijk terug te brengen.

![Een verdwaald blikje babymaïs op de tomatenpureeplank](../../../../../translated_images/stock-rogue-corn.be1f3ada8c457854.nl.png)

In de bovenstaande afbeelding is een blikje babymaïs op de plank naast de tomatenpuree geplaatst. De objectdetector heeft dit gedetecteerd, waardoor het IoT-apparaat een mens of robot kan waarschuwen om het blikje terug te brengen naar de juiste locatie.

## Je objectdetector aanroepen vanaf je IoT-apparaat

De objectdetector die je in de vorige les hebt getraind, kan worden aangeroepen vanaf je IoT-apparaat.

### Taak - publiceer een iteratie van je objectdetector

Iteraties worden gepubliceerd vanuit het Custom Vision-portaal.

1. Start het Custom Vision-portaal op [CustomVision.ai](https://customvision.ai) en log in als je dat nog niet hebt gedaan. Open vervolgens je `stock-detector`-project.

1. Selecteer het tabblad **Performance** uit de opties bovenaan.

1. Selecteer de nieuwste iteratie uit de lijst *Iterations* aan de zijkant.

1. Selecteer de knop **Publish** voor de iteratie.

    ![De publiceerknop](../../../../../translated_images/custom-vision-object-detector-publish-button.34ee379fc650ccb9856c3868d0003f413b9529f102fc73c37168c98d721cc293.nl.png)

1. Stel in het dialoogvenster *Publish Model* de *Prediction resource* in op de `stock-detector-prediction`-resource die je in de vorige les hebt gemaakt. Laat de naam staan als `Iteration2` en selecteer de knop **Publish**.

1. Zodra het is gepubliceerd, selecteer je de knop **Prediction URL**. Dit toont details van de voorspelling-API, en je hebt deze nodig om het model vanaf je IoT-apparaat aan te roepen. Het onderste gedeelte is gelabeld *If you have an image file*, en dit zijn de details die je wilt. Neem een kopie van de URL die wordt weergegeven, iets zoals:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/detect/iterations/Iteration2/image
    ```

    Waar `<location>` de locatie is die je hebt gebruikt bij het maken van je Custom Vision-resource, en `<id>` een lange ID is bestaande uit letters en cijfers.

    Neem ook een kopie van de waarde *Prediction-Key*. Dit is een beveiligde sleutel die je moet doorgeven wanneer je het model aanroept. Alleen applicaties die deze sleutel doorgeven mogen het model gebruiken, andere applicaties worden geweigerd.

    ![Het dialoogvenster voorspelling-API met de URL en sleutel](../../../../../translated_images/custom-vision-prediction-key-endpoint.30c569ffd0338864f319911f052d5e9b8c5066cb0800a26dd6f7ff5713130ad8.nl.png)

✅ Wanneer een nieuwe iteratie wordt gepubliceerd, heeft deze een andere naam. Hoe denk je dat je de iteratie zou veranderen die een IoT-apparaat gebruikt?

### Taak - roep je objectdetector aan vanaf je IoT-apparaat

Volg de relevante gids hieronder om de objectdetector te gebruiken vanaf je IoT-apparaat:

* [Arduino - Wio Terminal](wio-terminal-object-detector.md)
* [Single-board computer - Raspberry Pi/Virtual device](single-board-computer-object-detector.md)

## Omgrenzende kaders

Wanneer je de objectdetector gebruikt, krijg je niet alleen de gedetecteerde objecten terug met hun tags en waarschijnlijkheden, maar ook de omgrenzende kaders van de objecten. Deze definiëren waar de objectdetector het object heeft gedetecteerd met de gegeven waarschijnlijkheid.

> 💁 Een omgrenzend kader is een kader dat het gebied definieert dat het gedetecteerde object bevat, een kader dat de grens voor het object definieert.

De resultaten van een voorspelling in het tabblad **Predictions** in Custom Vision hebben de omgrenzende kaders getekend op de afbeelding die werd verzonden voor voorspelling.

![4 blikken tomatenpuree op een plank met voorspellingen voor de 4 detecties van 35.8%, 33.5%, 25.7% en 16.6%](../../../../../translated_images/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.nl.png)

In de bovenstaande afbeelding zijn 4 blikken tomatenpuree gedetecteerd. In de resultaten is een rood vierkant over elk gedetecteerd object gelegd, wat het omgrenzende kader voor de afbeelding aangeeft.

✅ Open de voorspellingen in Custom Vision en bekijk de omgrenzende kaders.

Omgrenzende kaders worden gedefinieerd met 4 waarden - top, left, height en width. Deze waarden zijn op een schaal van 0-1, wat de posities als een percentage van de grootte van de afbeelding vertegenwoordigt. De oorsprong (de 0,0-positie) is de linkerbovenhoek van de afbeelding, dus de topwaarde is de afstand vanaf de bovenkant, en de onderkant van het omgrenzende kader is de top plus de hoogte.

![Een omgrenzend kader rond een blik tomatenpuree](../../../../../translated_images/bounding-box.1420a7ea0d3d15f71e1ffb5cf4b2271d184fac051f990abc541975168d163684.nl.png)

De bovenstaande afbeelding is 600 pixels breed en 800 pixels hoog. Het omgrenzende kader begint op 320 pixels naar beneden, wat een topcoördinaat van 0.4 geeft (800 x 0.4 = 320). Vanaf links begint het omgrenzende kader op 240 pixels naar rechts, wat een left-coördinaat van 0.4 geeft (600 x 0.4 = 240). De hoogte van het omgrenzende kader is 240 pixels, wat een hoogtewaarde van 0.3 geeft (800 x 0.3 = 240). De breedte van het omgrenzende kader is 120 pixels, wat een breedtewaarde van 0.2 geeft (600 x 0.2 = 120).

| Coördinaat | Waarde |
| ---------- | ----: |
| Top        | 0.4   |
| Left       | 0.4   |
| Height     | 0.3   |
| Width      | 0.2   |

Door percentagewaarden van 0-1 te gebruiken, maakt het niet uit hoe groot de afbeelding wordt geschaald, het omgrenzende kader begint 0.4 van de weg langs en naar beneden, en is 0.3 van de hoogte en 0.2 van de breedte.

Je kunt omgrenzende kaders combineren met waarschijnlijkheden om te evalueren hoe nauwkeurig een detectie is. Bijvoorbeeld, een objectdetector kan meerdere objecten detecteren die overlappen, bijvoorbeeld één blik dat binnen een ander blik wordt gedetecteerd. Je code kan de omgrenzende kaders bekijken, begrijpen dat dit onmogelijk is, en alle objecten negeren die significant overlappen met andere objecten.

![Twee omgrenzende kaders overlappen een blik tomatenpuree](../../../../../translated_images/overlap-object-detection.d431e03cae75072a2760430eca7f2c5fdd43045bfd72dadcbf12711f7cd6c2ae.nl.png)

In het bovenstaande voorbeeld gaf één omgrenzend kader een voorspeld blik tomatenpuree aan met 78.3%. Een tweede omgrenzend kader is iets kleiner en bevindt zich binnen het eerste omgrenzende kader met een waarschijnlijkheid van 64.3%. Je code kan de omgrenzende kaders controleren, zien dat ze volledig overlappen, en de lagere waarschijnlijkheid negeren omdat het onmogelijk is dat één blik binnen een ander blik zit.

✅ Kun je een situatie bedenken waarin het geldig is om één object binnen een ander te detecteren?

## Het model opnieuw trainen

Net als bij de beeldclassificator kun je je model opnieuw trainen met gegevens die zijn vastgelegd door je IoT-apparaat. Het gebruik van deze real-world gegevens zorgt ervoor dat je model goed werkt wanneer het wordt gebruikt vanaf je IoT-apparaat.

In tegenstelling tot de beeldclassificator kun je niet zomaar een afbeelding taggen. In plaats daarvan moet je elk omgrenzend kader dat door het model is gedetecteerd, beoordelen. Als het kader om het verkeerde object zit, moet het worden verwijderd, en als het op de verkeerde locatie zit, moet het worden aangepast.

### Taak - het model opnieuw trainen

1. Zorg ervoor dat je een reeks afbeeldingen hebt vastgelegd met je IoT-apparaat.

1. Selecteer een afbeelding vanuit het tabblad **Predictions**. Je ziet rode kaders die de omgrenzende kaders van de gedetecteerde objecten aangeven.

1. Werk elk omgrenzend kader door. Selecteer het eerst en je ziet een pop-up met de tag. Gebruik de handgrepen op de hoeken van het omgrenzende kader om de grootte indien nodig aan te passen. Als de tag verkeerd is, verwijder deze met de knop **X** en voeg de juiste tag toe. Als het omgrenzende kader geen object bevat, verwijder het dan met de prullenbakknop.

1. Sluit de editor wanneer je klaar bent en de afbeelding wordt verplaatst van het tabblad **Predictions** naar het tabblad **Training Images**. Herhaal het proces voor alle voorspellingen.

1. Gebruik de knop **Train** om je model opnieuw te trainen. Zodra het is getraind, publiceer je de iteratie en werk je je IoT-apparaat bij om de URL van de nieuwe iteratie te gebruiken.

1. Herdeploy je code en test je IoT-apparaat.

## Voorraad tellen

Met een combinatie van het aantal gedetecteerde objecten en de omgrenzende kaders kun je de voorraad op een plank tellen.

### Taak - voorraad tellen

Volg de relevante gids hieronder om voorraad te tellen met de resultaten van de objectdetector vanaf je IoT-apparaat:

* [Arduino - Wio Terminal](wio-terminal-count-stock.md)
* [Single-board computer - Raspberry Pi/Virtual device](single-board-computer-count-stock.md)

---

## 🚀 Uitdaging

Kun je verkeerde voorraad detecteren? Train je model op meerdere objecten en werk vervolgens je app bij om je te waarschuwen als de verkeerde voorraad wordt gedetecteerd.

Misschien kun je zelfs verder gaan en voorraad naast elkaar op dezelfde plank detecteren, en zien of iets op de verkeerde plek is gezet door grenzen te definiëren op de omgrenzende kaders.

## Quiz na de les

[Quiz na de les](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/40)

## Review & Zelfstudie

* Leer meer over hoe je een end-to-end voorraaddetectiesysteem kunt ontwerpen met de [Out of stock detection at the edge pattern guide op Microsoft Docs](https://docs.microsoft.com/hybrid/app-solutions/pattern-out-of-stock-at-edge?WT.mc_id=academic-17441-jabenn)
* Ontdek andere manieren om end-to-end retailoplossingen te bouwen door een reeks IoT- en clouddiensten te combineren door deze [Behind the scenes of a retail solution - Hands On! video op YouTube](https://www.youtube.com/watch?v=m3Pc300x2Mw) te bekijken.

## Opdracht

[Gebruik je objectdetector aan de rand](assignment.md)

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.