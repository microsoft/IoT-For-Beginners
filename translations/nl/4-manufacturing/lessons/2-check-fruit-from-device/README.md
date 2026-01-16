<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "557f4ee96b752e0651d2e6e74aa6bd14",
  "translation_date": "2025-08-27T20:39:28+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/README.md",
  "language_code": "nl"
}
-->
# Controleer de kwaliteit van fruit met een IoT-apparaat

![Een schetsnotitie-overzicht van deze les](../../../../../translated_images/nl/lesson-16.215daf18b00631fbdfd64c6fc2dc6044dff5d544288825d8076f9fb83d964c23.jpg)

> Schetsnotitie door [Nitya Narasimhan](https://github.com/nitya). Klik op de afbeelding voor een grotere versie.

## Quiz voorafgaand aan de les

[Quiz voorafgaand aan de les](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/31)

## Introductie

In de vorige les heb je geleerd over beeldclassificatoren en hoe je ze kunt trainen om goed en slecht fruit te detecteren. Om deze beeldclassificator in een IoT-toepassing te gebruiken, moet je een afbeelding kunnen vastleggen met een camera en deze afbeelding naar de cloud kunnen sturen om te classificeren.

In deze les leer je over camerasensoren en hoe je deze kunt gebruiken met een IoT-apparaat om een afbeelding vast te leggen. Je leert ook hoe je de beeldclassificator vanaf je IoT-apparaat kunt aanroepen.

In deze les behandelen we:

* [Camerasensoren](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Een afbeelding vastleggen met een IoT-apparaat](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Je beeldclassificator publiceren](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Afbeeldingen classificeren vanaf je IoT-apparaat](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Het model verbeteren](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)

## Camerasensoren

Camerasensoren zijn, zoals de naam al aangeeft, camera's die je kunt aansluiten op je IoT-apparaat. Ze kunnen stilstaande beelden maken of videostreams vastleggen. Sommige geven ruwe beeldgegevens terug, terwijl andere de gegevens comprimeren tot een afbeeldingsbestand zoals een JPEG of PNG. Meestal zijn de camera's die werken met IoT-apparaten veel kleiner en hebben ze een lagere resolutie dan je gewend bent, maar je kunt ook camera's met een hoge resolutie krijgen die kunnen concurreren met de beste smartphones. Er zijn allerlei verwisselbare lenzen, opstellingen met meerdere camera's, infrarood thermische camera's of UV-camera's beschikbaar.

![Het licht van een scène gaat door een lens en wordt gefocust op een CMOS-sensor](../../../../../translated_images/nl/cmos-sensor.75f9cd74decb137149a4c9ea825251a4549497d67c0ae2776159e6102bb53aa9.png)

De meeste camerasensoren gebruiken beeldsensoren waarbij elke pixel een fotodiode is. Een lens richt het beeld op de beeldsensor, en duizenden of miljoenen fotodiodes detecteren het licht dat op elke diode valt en registreren dit als pixelgegevens.

> 💁 Lenzen draaien beelden om, waarna de camerasensor het beeld weer correct omdraait. Dit gebeurt ook in je ogen: wat je ziet, wordt ondersteboven waargenomen op de achterkant van je oog, en je hersenen corrigeren dit.

> 🎓 De beeldsensor wordt een Active-Pixel Sensor (APS) genoemd, en het meest populaire type APS is een complementaire metaaloxide-halfgeleider-sensor, of CMOS. Je hebt de term CMOS-sensor misschien wel eens gehoord in verband met camerasensoren.

Camerasensoren zijn digitale sensoren die beeldgegevens als digitale data verzenden, meestal met behulp van een bibliotheek die de communicatie verzorgt. Camera's maken gebruik van protocollen zoals SPI om grote hoeveelheden gegevens te verzenden - afbeeldingen zijn aanzienlijk groter dan enkele getallen van een sensor zoals een temperatuursensor.

✅ Wat zijn de beperkingen rond afbeeldingsgrootte bij IoT-apparaten? Denk aan de beperkingen, vooral bij hardware van microcontrollers.

## Een afbeelding vastleggen met een IoT-apparaat

Je kunt je IoT-apparaat gebruiken om een afbeelding vast te leggen die geclassificeerd moet worden.

### Taak - een afbeelding vastleggen met een IoT-apparaat

Volg de relevante handleiding om een afbeelding vast te leggen met je IoT-apparaat:

* [Arduino - Wio Terminal](wio-terminal-camera.md)
* [Single-board computer - Raspberry Pi](pi-camera.md)
* [Single-board computer - Virtueel apparaat](virtual-device-camera.md)

## Je beeldclassificator publiceren

Je hebt je beeldclassificator in de vorige les getraind. Voordat je deze kunt gebruiken vanaf je IoT-apparaat, moet je het model publiceren.

### Modeliteraties

Toen je model in de vorige les werd getraind, heb je misschien gemerkt dat het tabblad **Performance** iteraties aan de zijkant toont. Toen je het model voor het eerst trainde, zag je *Iteratie 1* in training. Toen je het model verbeterde met behulp van de voorspellingsafbeeldingen, zag je *Iteratie 2* in training.

Elke keer dat je het model traint, krijg je een nieuwe iteratie. Dit is een manier om de verschillende versies van je model bij te houden die op verschillende datasets zijn getraind. Wanneer je een **Quick Test** uitvoert, is er een dropdownmenu waarmee je de iteratie kunt selecteren, zodat je de resultaten van meerdere iteraties kunt vergelijken.

Wanneer je tevreden bent met een iteratie, kun je deze publiceren om beschikbaar te maken voor gebruik door externe toepassingen. Op deze manier kun je een gepubliceerde versie hebben die door je apparaten wordt gebruikt, terwijl je aan een nieuwe versie werkt over meerdere iteraties, en deze publiceert zodra je tevreden bent.

### Taak - een iteratie publiceren

Iteraties worden gepubliceerd vanuit het Custom Vision-portaal.

1. Open het Custom Vision-portaal op [CustomVision.ai](https://customvision.ai) en log in als je dat nog niet hebt gedaan. Open vervolgens je `fruit-quality-detector`-project.

1. Selecteer het tabblad **Performance** in de opties bovenaan.

1. Selecteer de nieuwste iteratie in de lijst *Iterations* aan de zijkant.

1. Klik op de knop **Publish** voor de iteratie.

    ![De publiceerknop](../../../../../translated_images/nl/custom-vision-publish-button.b7174e1977b0c33b8b72d4e5b1326c779e0af196f3849d09985ee2d7d5493a39.png)

1. Stel in het dialoogvenster *Publish Model* de *Prediction resource* in op de `fruit-quality-detector-prediction`-resource die je in de vorige les hebt gemaakt. Laat de naam staan als `Iteration2` en klik op de knop **Publish**.

1. Zodra het model is gepubliceerd, klik je op de knop **Prediction URL**. Dit toont de details van de voorspellings-API, die je nodig hebt om het model vanaf je IoT-apparaat aan te roepen. Het onderste gedeelte is gelabeld *If you have an image file*, en dit zijn de details die je nodig hebt. Kopieer de weergegeven URL, die er ongeveer zo uitziet:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/classify/iterations/Iteration2/image
    ```

    Waarbij `<location>` de locatie is die je hebt gebruikt bij het maken van je Custom Vision-resource, en `<id>` een lange ID is bestaande uit letters en cijfers.

    Kopieer ook de waarde van de *Prediction-Key*. Dit is een beveiligde sleutel die je moet doorgeven wanneer je het model aanroept. Alleen toepassingen die deze sleutel doorgeven, mogen het model gebruiken; andere toepassingen worden geweigerd.

    ![Het dialoogvenster van de voorspellings-API met de URL en sleutel](../../../../../translated_images/nl/custom-vision-prediction-key-endpoint.30c569ffd0338864f319911f052d5e9b8c5066cb0800a26dd6f7ff5713130ad8.png)

✅ Wanneer een nieuwe iteratie wordt gepubliceerd, heeft deze een andere naam. Hoe denk je dat je de iteratie kunt wijzigen die een IoT-apparaat gebruikt?

## Afbeeldingen classificeren vanaf je IoT-apparaat

Je kunt nu deze verbindingsgegevens gebruiken om de beeldclassificator vanaf je IoT-apparaat aan te roepen.

### Taak - afbeeldingen classificeren vanaf je IoT-apparaat

Volg de relevante handleiding om afbeeldingen te classificeren met je IoT-apparaat:

* [Arduino - Wio Terminal](wio-terminal-classify-image.md)
* [Single-board computer - Raspberry Pi/Virtueel IoT-apparaat](single-board-computer-classify-image.md)

## Het model verbeteren

Het kan zijn dat de resultaten die je krijgt bij het gebruik van de camera die op je IoT-apparaat is aangesloten, niet overeenkomen met wat je zou verwachten. De voorspellingen zijn niet altijd zo nauwkeurig als bij het gebruik van afbeeldingen die vanaf je computer zijn geüpload. Dit komt doordat het model is getraind op andere gegevens dan die worden gebruikt voor voorspellingen.

Om de beste resultaten voor een beeldclassificator te krijgen, wil je het model trainen met afbeeldingen die zo veel mogelijk lijken op de afbeeldingen die worden gebruikt voor voorspellingen. Als je bijvoorbeeld je telefooncamera hebt gebruikt om afbeeldingen voor training vast te leggen, zullen de beeldkwaliteit, scherpte en kleur anders zijn dan die van een camera die is aangesloten op een IoT-apparaat.

![2 bananenfoto's, een met lage resolutie en slechte belichting van een IoT-apparaat, en een met hoge resolutie en goede belichting van een telefoon](../../../../../translated_images/nl/banana-picture-compare.174df164dc326a42cf7fb051a7497e6113c620e91552d92ca914220305d47d9a.png)

In de afbeelding hierboven is de bananenfoto links gemaakt met een Raspberry Pi-camera, en de foto rechts is gemaakt van dezelfde banaan op dezelfde locatie met een iPhone. Er is een duidelijk verschil in kwaliteit: de iPhone-foto is scherper, met helderdere kleuren en meer contrast.

✅ Wat zou er nog meer voor kunnen zorgen dat de afbeeldingen die door je IoT-apparaat worden vastgelegd, onjuiste voorspellingen geven? Denk aan de omgeving waarin een IoT-apparaat wordt gebruikt en welke factoren de vastgelegde afbeelding kunnen beïnvloeden.

Om het model te verbeteren, kun je het opnieuw trainen met de afbeeldingen die zijn vastgelegd door het IoT-apparaat.

### Taak - het model verbeteren

1. Classificeer meerdere afbeeldingen van zowel rijp als onrijp fruit met je IoT-apparaat.

1. Train het model opnieuw in het Custom Vision-portaal met behulp van de afbeeldingen op het tabblad *Predictions*.

    > ⚠️ Je kunt [de instructies voor het opnieuw trainen van je classificator in les 1 raadplegen indien nodig](../1-train-fruit-detector/README.md#retrain-your-image-classifier).

1. Als je afbeeldingen er heel anders uitzien dan de originele afbeeldingen die voor training zijn gebruikt, kun je alle originele afbeeldingen verwijderen door ze te selecteren op het tabblad *Training Images* en op de knop **Delete** te klikken. Om een afbeelding te selecteren, beweeg je je cursor erover en verschijnt er een vinkje. Klik op dat vinkje om de afbeelding te selecteren of deselecteren.

1. Train een nieuwe iteratie van het model en publiceer deze met behulp van de bovenstaande stappen.

1. Werk de endpoint-URL in je code bij en voer de app opnieuw uit.

1. Herhaal deze stappen totdat je tevreden bent met de resultaten van de voorspellingen.

---

## 🚀 Uitdaging

Hoeveel invloed hebben de resolutie van de afbeelding of de belichting op de voorspelling?

Probeer de resolutie van de afbeeldingen in je apparaatcode te wijzigen en kijk of dit verschil maakt in de kwaliteit van de afbeeldingen. Probeer ook de belichting te veranderen.

Als je een productietoestel zou maken om te verkopen aan boerderijen of fabrieken, hoe zou je ervoor zorgen dat het altijd consistente resultaten geeft?

## Quiz na de les

[Quiz na de les](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/32)

## Herziening & Zelfstudie

Je hebt je Custom Vision-model getraind met behulp van het portaal. Dit is afhankelijk van het hebben van beschikbare afbeeldingen - en in de echte wereld is het misschien niet mogelijk om trainingsgegevens te verkrijgen die overeenkomen met wat de camera op je apparaat vastlegt. Je kunt dit omzeilen door direct vanaf je apparaat te trainen met behulp van de trainings-API, om een model te trainen met afbeeldingen die zijn vastgelegd door je IoT-apparaat.

* Lees meer over de trainings-API in de [quickstart voor het gebruik van de Custom Vision SDK](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/quickstarts/image-classification?WT.mc_id=academic-17441-jabenn&tabs=visual-studio&pivots=programming-language-python)

## Opdracht

[Reageer op classificatieresultaten](assignment.md)

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.