<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "557f4ee96b752e0651d2e6e74aa6bd14",
  "translation_date": "2025-08-27T20:40:39+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/README.md",
  "language_code": "da"
}
-->
# Kontroller frugtkvalitet med en IoT-enhed

![En sketchnote oversigt over denne lektion](../../../../../translated_images/da/lesson-16.215daf18b00631fbdfd64c6fc2dc6044dff5d544288825d8076f9fb83d964c23.jpg)

> Sketchnote af [Nitya Narasimhan](https://github.com/nitya). Klik på billedet for en større version.

## Quiz før lektionen

[Quiz før lektionen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/31)

## Introduktion

I den sidste lektion lærte du om billedklassifikatorer, og hvordan man træner dem til at opdage god og dårlig frugt. For at bruge denne billedklassifikator i en IoT-applikation skal du kunne tage et billede med en slags kamera og sende dette billede til skyen for at blive klassificeret.

I denne lektion vil du lære om kamerasensorer, og hvordan man bruger dem med en IoT-enhed til at tage et billede. Du vil også lære, hvordan man kalder billedklassifikatoren fra din IoT-enhed.

I denne lektion dækker vi:

* [Kamerasensorer](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Tag et billede med en IoT-enhed](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Publicer din billedklassifikator](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Klassificer billeder fra din IoT-enhed](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Forbedr modellen](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)

## Kamerasensorer

Kamerasensorer, som navnet antyder, er kameraer, du kan tilslutte til din IoT-enhed. De kan tage stillbilleder eller optage streamingvideo. Nogle returnerer rå billeddata, mens andre komprimerer billeddataene til en billedfil som JPEG eller PNG. Normalt er de kameraer, der fungerer med IoT-enheder, meget mindre og har lavere opløsning end dem, du måske er vant til, men du kan få kameraer med høj opløsning, der kan konkurrere med de bedste smartphones. Du kan få alle slags udskiftelige linser, opsætninger med flere kameraer, infrarøde termiske kameraer eller UV-kameraer.

![Lyset fra en scene passerer gennem en linse og fokuseres på en CMOS-sensor](../../../../../translated_images/da/cmos-sensor.75f9cd74decb137149a4c9ea825251a4549497d67c0ae2776159e6102bb53aa9.png)

De fleste kamerasensorer bruger billedsensorer, hvor hver pixel er en fotodiode. En linse fokuserer billedet på billedsensoren, og tusinder eller millioner af fotodioder registrerer lyset, der falder på hver enkelt, og gemmer det som pixeldata.

> 💁 Linser vender billeder på hovedet, og kamerasensoren vender derefter billedet tilbage til den rigtige retning. Det samme sker i dine øjne - det, du ser, registreres på hovedet på bagsiden af dit øje, og din hjerne korrigerer det.

> 🎓 Billedsensoren kaldes en Active-Pixel Sensor (APS), og den mest populære type APS er en komplementær metal-oxid halvleder-sensor, eller CMOS. Du har måske hørt udtrykket CMOS-sensor brugt om kamerasensorer.

Kamerasensorer er digitale sensorer, der sender billeddata som digitale data, normalt med hjælp fra et bibliotek, der leverer kommunikationen. Kameraer tilsluttes ved hjælp af protokoller som SPI for at sende store mængder data - billeder er betydeligt større end enkeltværdier fra en sensor som en temperatursensor.

✅ Hvad er begrænsningerne omkring billedstørrelse med IoT-enheder? Tænk på begrænsningerne, især på mikrocontrollerhardware.

## Tag et billede med en IoT-enhed

Du kan bruge din IoT-enhed til at tage et billede, der skal klassificeres.

### Opgave - tag et billede med en IoT-enhed

Følg den relevante vejledning for at tage et billede med din IoT-enhed:

* [Arduino - Wio Terminal](wio-terminal-camera.md)
* [Single-board computer - Raspberry Pi](pi-camera.md)
* [Single-board computer - Virtuel enhed](virtual-device-camera.md)

## Publicer din billedklassifikator

Du trænede din billedklassifikator i den sidste lektion. Før du kan bruge den fra din IoT-enhed, skal du publicere modellen.

### Modeliterationer

Da din model blev trænet i den sidste lektion, har du måske bemærket, at fanen **Performance** viser iterationer på siden. Da du først trænede modellen, ville du have set *Iteration 1* under træning. Da du forbedrede modellen ved hjælp af forudsigelsesbillederne, ville du have set *Iteration 2* under træning.

Hver gang du træner modellen, får du en ny iteration. Dette er en måde at holde styr på de forskellige versioner af din model, der er trænet på forskellige datasæt. Når du udfører en **Quick Test**, er der en rullemenu, du kan bruge til at vælge iterationen, så du kan sammenligne resultaterne på tværs af flere iterationer.

Når du er tilfreds med en iteration, kan du publicere den, så den kan bruges fra eksterne applikationer. På denne måde kan du have en publiceret version, der bruges af dine enheder, og derefter arbejde på en ny version over flere iterationer, og publicere den, når du er tilfreds med den.

### Opgave - publicer en iteration

Iterationer publiceres fra Custom Vision-portalen.

1. Åbn Custom Vision-portalen på [CustomVision.ai](https://customvision.ai) og log ind, hvis du ikke allerede har den åben. Åbn derefter dit `fruit-quality-detector`-projekt.

1. Vælg fanen **Performance** fra mulighederne øverst.

1. Vælg den nyeste iteration fra listen *Iterations* på siden.

1. Vælg knappen **Publish** for iterationen.

    ![Publiceringsknappen](../../../../../translated_images/da/custom-vision-publish-button.b7174e1977b0c33b8b72d4e5b1326c779e0af196f3849d09985ee2d7d5493a39.png)

1. I dialogboksen *Publish Model* skal du indstille *Prediction resource* til den `fruit-quality-detector-prediction`-ressource, du oprettede i den sidste lektion. Lad navnet være `Iteration2`, og vælg knappen **Publish**.

1. Når den er publiceret, skal du vælge knappen **Prediction URL**. Dette vil vise detaljer om forudsigelses-API'en, og du vil få brug for disse for at kalde modellen fra din IoT-enhed. Den nederste sektion er mærket *If you have an image file*, og det er disse detaljer, du skal bruge. Tag en kopi af den viste URL, som vil være noget i stil med:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/classify/iterations/Iteration2/image
    ```

    Hvor `<location>` vil være den placering, du brugte, da du oprettede din Custom Vision-ressource, og `<id>` vil være en lang ID bestående af bogstaver og tal.

    Tag også en kopi af værdien *Prediction-Key*. Dette er en sikker nøgle, som du skal sende, når du kalder modellen. Kun applikationer, der sender denne nøgle, har tilladelse til at bruge modellen, alle andre applikationer afvises.

    ![Dialogboksen for forudsigelses-API, der viser URL og nøgle](../../../../../translated_images/da/custom-vision-prediction-key-endpoint.30c569ffd0338864f319911f052d5e9b8c5066cb0800a26dd6f7ff5713130ad8.png)

✅ Når en ny iteration publiceres, vil den have et andet navn. Hvordan tror du, du ville ændre den iteration, en IoT-enhed bruger?

## Klassificer billeder fra din IoT-enhed

Du kan nu bruge disse forbindelsesdetaljer til at kalde billedklassifikatoren fra din IoT-enhed.

### Opgave - klassificer billeder fra din IoT-enhed

Følg den relevante vejledning for at klassificere billeder ved hjælp af din IoT-enhed:

* [Arduino - Wio Terminal](wio-terminal-classify-image.md)
* [Single-board computer - Raspberry Pi/Virtuel IoT-enhed](single-board-computer-classify-image.md)

## Forbedr modellen

Du kan opleve, at de resultater, du får, når du bruger kameraet tilsluttet din IoT-enhed, ikke stemmer overens med, hvad du ville forvente. Forudsigelserne er ikke altid lige så nøjagtige som ved brug af billeder uploadet fra din computer. Dette skyldes, at modellen blev trænet på forskellige data end dem, der bruges til forudsigelser.

For at få de bedste resultater for en billedklassifikator vil du gerne træne modellen med billeder, der er så ens som muligt med de billeder, der bruges til forudsigelser. Hvis du for eksempel brugte dit telefonkamera til at tage billeder til træning, vil billedkvaliteten, skarpheden og farverne være anderledes end et kamera tilsluttet en IoT-enhed.

![2 bananbilleder, et lavopløsningsbillede med dårlig belysning fra en IoT-enhed, og et højopløsningsbillede med god belysning fra en telefon](../../../../../translated_images/da/banana-picture-compare.174df164dc326a42cf7fb051a7497e6113c620e91552d92ca914220305d47d9a.png)

På billedet ovenfor blev bananbilledet til venstre taget med et Raspberry Pi-kamera, mens det til højre blev taget af den samme banan på samme sted med en iPhone. Der er en tydelig forskel i kvalitet - iPhone-billedet er skarpere, med lysere farver og mere kontrast.

✅ Hvad kan ellers forårsage, at de billeder, der tages af din IoT-enhed, giver forkerte forudsigelser? Tænk på det miljø, en IoT-enhed kan bruges i, hvilke faktorer kan påvirke det billede, der tages?

For at forbedre modellen kan du genoptræne den ved hjælp af de billeder, der er taget fra IoT-enheden.

### Opgave - forbedr modellen

1. Klassificer flere billeder af både moden og umoden frugt ved hjælp af din IoT-enhed.

1. I Custom Vision-portalen skal du genoptræne modellen ved hjælp af billederne på fanen *Predictions*.

    > ⚠️ Du kan henvise til [instruktionerne for genoptræning af din klassifikator i lektion 1, hvis det er nødvendigt](../1-train-fruit-detector/README.md#retrain-your-image-classifier).

1. Hvis dine billeder ser meget anderledes ud end de oprindelige, der blev brugt til træning, kan du slette alle de oprindelige billeder ved at vælge dem på fanen *Training Images* og vælge knappen **Delete**. For at vælge et billede skal du føre din markør over det, og der vises et flueben, som du kan vælge eller fravælge.

1. Træn en ny iteration af modellen og publicer den ved hjælp af ovenstående trin.

1. Opdater endpoint-URL'en i din kode, og kør appen igen.

1. Gentag disse trin, indtil du er tilfreds med resultaterne af forudsigelserne.

---

## 🚀 Udfordring

Hvor meget påvirker billedopløsning eller belysning forudsigelsen?

Prøv at ændre opløsningen af billederne i din enhedskode og se, om det gør en forskel for kvaliteten af billederne. Prøv også at ændre belysningen.

Hvis du skulle skabe en produktionsenhed til salg til gårde eller fabrikker, hvordan ville du sikre, at den giver konsistente resultater hele tiden?

## Quiz efter lektionen

[Quiz efter lektionen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/32)

## Gennemgang & Selvstudie

Du trænede din Custom Vision-model ved hjælp af portalen. Dette afhænger af at have billeder tilgængelige - og i den virkelige verden kan du måske ikke få træningsdata, der matcher, hvad kameraet på din enhed fanger. Du kan omgå dette ved at træne direkte fra din enhed ved hjælp af trænings-API'en, for at træne en model ved hjælp af billeder taget fra din IoT-enhed.

* Læs om trænings-API'en i [quick start for brug af Custom Vision SDK](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/quickstarts/image-classification?WT.mc_id=academic-17441-jabenn&tabs=visual-studio&pivots=programming-language-python)

## Opgave

[Reager på klassifikationsresultater](assignment.md)

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.