<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1c9e5fa8b7be726c75a97232b1e41c97",
  "translation_date": "2025-08-27T22:16:30+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/README.md",
  "language_code": "da"
}
-->
# Tjek lager fra en IoT-enhed

![En sketchnote-oversigt over denne lektion](../../../../../translated_images/da/lesson-20.0211df9551a8abb300fc8fcf7dc2789468dea2eabe9202273ac077b0ba37f15e.jpg)

> Sketchnote af [Nitya Narasimhan](https://github.com/nitya). Klik på billedet for en større version.

## Quiz før lektionen

[Quiz før lektionen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/39)

## Introduktion

I den forrige lektion lærte du om de forskellige anvendelser af objektdetektion i detailhandlen. Du lærte også, hvordan man træner en objektdetektor til at identificere lager. I denne lektion vil du lære, hvordan du bruger din objektdetektor fra din IoT-enhed til at tælle lager.

I denne lektion dækker vi:

* [Lageroptælling](../../../../../5-retail/lessons/2-check-stock-device)
* [Kald din objektdetektor fra din IoT-enhed](../../../../../5-retail/lessons/2-check-stock-device)
* [Afgrænsningsbokse](../../../../../5-retail/lessons/2-check-stock-device)
* [Gen-træn modellen](../../../../../5-retail/lessons/2-check-stock-device)
* [Tæl lager](../../../../../5-retail/lessons/2-check-stock-device)

> 🗑 Dette er den sidste lektion i dette projekt, så efter at have gennemført denne lektion og opgaven, skal du huske at rydde op i dine cloud-tjenester. Du skal bruge tjenesterne for at fuldføre opgaven, så sørg for at gøre det først.
>
> Se [guiden til at rydde op i dit projekt](../../../clean-up.md), hvis du har brug for instruktioner til, hvordan du gør dette.

## Lageroptælling

Objektdetektorer kan bruges til lagerkontrol, enten til at tælle lager eller sikre, at lageret er, hvor det skal være. IoT-enheder med kameraer kan placeres rundt om i butikken for at overvåge lageret, startende med hotspots, hvor det er vigtigt at genopfylde varer, såsom områder med små mængder af højværdiartikler.

For eksempel, hvis et kamera peger på en hylde, der kan rumme 8 dåser tomatpuré, og en objektdetektor kun registrerer 7 dåser, mangler der én, som skal genopfyldes.

![7 dåser tomatpuré på en hylde, 4 på øverste række, 3 på nederste række](../../../../../translated_images/da/stock-7-cans-tomato-paste.f86059cc573d7bec.webp)

I billedet ovenfor har en objektdetektor registreret 7 dåser tomatpuré på en hylde, der kan rumme 8 dåser. Ikke alene kan IoT-enheden sende en notifikation om behovet for genopfyldning, men den kan også give en indikation af, hvor den manglende vare befinder sig, hvilket er vigtig information, hvis du bruger robotter til at genopfylde hylder.

> 💁 Afhængigt af butikken og varens popularitet ville genopfyldning sandsynligvis ikke ske, hvis kun én dåse manglede. Du skal bygge en algoritme, der bestemmer, hvornår der skal genopfyldes, baseret på dine varer, kunder og andre kriterier.

✅ I hvilke andre scenarier kunne du kombinere objektdetektion og robotter?

Nogle gange kan det forkerte lager være på hylderne. Dette kan skyldes menneskelige fejl under genopfyldning eller kunder, der ombestemmer sig og placerer en vare på den første ledige plads. Når det drejer sig om ikke-letfordærvelige varer som konserves, er dette en irritation. Hvis det er letfordærvelige varer som frosne eller kølede produkter, kan det betyde, at varen ikke længere kan sælges, da det kan være umuligt at afgøre, hvor længe varen har været ude af fryseren.

Objektdetektion kan bruges til at opdage uventede varer og igen advare en person eller robot om at returnere varen, så snart den opdages.

![En vildfaren dåse babymajs på tomatpuréhylden](../../../../../translated_images/da/stock-rogue-corn.be1f3ada8c457854.webp)

I billedet ovenfor er en dåse babymajs blevet placeret på hylden ved siden af tomatpuréen. Objektdetektoren har registreret dette, hvilket gør det muligt for IoT-enheden at give besked til en person eller robot om at returnere dåsen til dens korrekte placering.

## Kald din objektdetektor fra din IoT-enhed

Den objektdetektor, du trænede i den sidste lektion, kan kaldes fra din IoT-enhed.

### Opgave - udgiv en iteration af din objektdetektor

Iterationer udgives fra Custom Vision-portalen.

1. Åbn Custom Vision-portalen på [CustomVision.ai](https://customvision.ai), og log ind, hvis du ikke allerede har den åben. Åbn derefter dit `stock-detector`-projekt.

1. Vælg fanen **Performance** fra mulighederne øverst.

1. Vælg den nyeste iteration fra listen *Iterations* i siden.

1. Vælg knappen **Publish** for iterationen.

    ![Udgiv-knappen](../../../../../translated_images/da/custom-vision-object-detector-publish-button.34ee379fc650ccb9856c3868d0003f413b9529f102fc73c37168c98d721cc293.png)

1. I dialogboksen *Publish Model* skal du indstille *Prediction resource* til den `stock-detector-prediction`-ressource, du oprettede i den sidste lektion. Lad navnet være `Iteration2`, og vælg knappen **Publish**.

1. Når den er udgivet, skal du vælge knappen **Prediction URL**. Dette vil vise detaljer om forudsigelses-API'en, som du skal bruge for at kalde modellen fra din IoT-enhed. Den nederste sektion er mærket *If you have an image file*, og det er disse detaljer, du skal bruge. Tag en kopi af den viste URL, som vil være noget i stil med:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/detect/iterations/Iteration2/image
    ```

    Hvor `<location>` vil være den placering, du brugte, da du oprettede din Custom Vision-ressource, og `<id>` vil være en lang ID bestående af bogstaver og tal.

    Tag også en kopi af værdien *Prediction-Key*. Dette er en sikker nøgle, som du skal sende, når du kalder modellen. Kun applikationer, der sender denne nøgle, har tilladelse til at bruge modellen, alle andre applikationer afvises.

    ![Dialogboksen for forudsigelses-API, der viser URL og nøgle](../../../../../translated_images/da/custom-vision-prediction-key-endpoint.30c569ffd0338864f319911f052d5e9b8c5066cb0800a26dd6f7ff5713130ad8.png)

✅ Når en ny iteration udgives, vil den have et andet navn. Hvordan tror du, at du ville ændre den iteration, som en IoT-enhed bruger?

### Opgave - kald din objektdetektor fra din IoT-enhed

Følg den relevante guide nedenfor for at bruge objektdetektoren fra din IoT-enhed:

* [Arduino - Wio Terminal](wio-terminal-object-detector.md)
* [Single-board computer - Raspberry Pi/Virtual device](single-board-computer-object-detector.md)

## Afgrænsningsbokse

Når du bruger objektdetektoren, får du ikke kun de registrerede objekter med deres tags og sandsynligheder, men også afgrænsningsboksene for objekterne. Disse definerer, hvor objektdetektoren registrerede objektet med den givne sandsynlighed.

> 💁 En afgrænsningsboks er en boks, der definerer det område, der indeholder det registrerede objekt, en boks, der definerer grænsen for objektet.

Resultaterne af en forudsigelse i fanen **Predictions** i Custom Vision har afgrænsningsboksene tegnet på det billede, der blev sendt til forudsigelse.

![4 dåser tomatpuré på en hylde med forudsigelser for de 4 registreringer på 35,8 %, 33,5 %, 25,7 % og 16,6 %](../../../../../translated_images/da/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

I billedet ovenfor blev 4 dåser tomatpuré registreret. I resultaterne er en rød firkant overlejret for hvert objekt, der blev registreret i billedet, hvilket angiver afgrænsningsboksen for billedet.

✅ Åbn forudsigelserne i Custom Vision, og tjek afgrænsningsboksene.

Afgrænsningsbokse defineres med 4 værdier - top, venstre, højde og bredde. Disse værdier er på en skala fra 0-1, der repræsenterer positionerne som en procentdel af billedets størrelse. Oprindelsen (0,0-positionen) er øverste venstre hjørne af billedet, så topværdien er afstanden fra toppen, og bunden af afgrænsningsboksen er toppen plus højden.

![En afgrænsningsboks omkring en dåse tomatpuré](../../../../../translated_images/da/bounding-box.1420a7ea0d3d15f71e1ffb5cf4b2271d184fac051f990abc541975168d163684.png)

Billedet ovenfor er 600 pixels bredt og 800 pixels højt. Afgrænsningsboksen starter 320 pixels nede, hvilket giver en topkoordinat på 0,4 (800 x 0,4 = 320). Fra venstre starter afgrænsningsboksen 240 pixels inde, hvilket giver en venstre koordinat på 0,4 (600 x 0,4 = 240). Højden på afgrænsningsboksen er 240 pixels, hvilket giver en højdeværdi på 0,3 (800 x 0,3 = 240). Bredden på afgrænsningsboksen er 120 pixels, hvilket giver en breddeværdi på 0,2 (600 x 0,2 = 120).

| Koordinat | Værdi |
| --------- | ----: |
| Top       | 0,4   |
| Venstre   | 0,4   |
| Højde     | 0,3   |
| Bredde    | 0,2   |

Ved at bruge procentværdier fra 0-1 betyder det, at uanset hvilken størrelse billedet skaleres til, starter afgrænsningsboksen 0,4 af vejen hen og ned og er 0,3 af højden og 0,2 af bredden.

Du kan bruge afgrænsningsbokse kombineret med sandsynligheder til at evaluere, hvor præcis en registrering er. For eksempel kan en objektdetektor registrere flere objekter, der overlapper hinanden, for eksempel registrere én dåse inde i en anden. Din kode kunne se på afgrænsningsboksene, forstå, at dette er umuligt, og ignorere eventuelle objekter, der har en betydelig overlapning med andre objekter.

![To afgrænsningsbokse, der overlapper en dåse tomatpuré](../../../../../translated_images/da/overlap-object-detection.d431e03cae75072a2760430eca7f2c5fdd43045bfd72dadcbf12711f7cd6c2ae.png)

I eksemplet ovenfor angav en afgrænsningsboks en forudsagt dåse tomatpuré med 78,3 %. En anden afgrænsningsboks er lidt mindre og er inde i den første afgrænsningsboks med en sandsynlighed på 64,3 %. Din kode kan tjekke afgrænsningsboksene, se, at de overlapper fuldstændigt, og ignorere den lavere sandsynlighed, da det ikke er muligt, at én dåse er inde i en anden.

✅ Kan du tænke på en situation, hvor det er gyldigt at registrere ét objekt inde i et andet?

## Gen-træn modellen

Ligesom med billedklassifikatoren kan du gen-træne din model ved hjælp af data indsamlet af din IoT-enhed. Brug af disse data fra den virkelige verden vil sikre, at din model fungerer godt, når den bruges fra din IoT-enhed.

I modsætning til billedklassifikatoren kan du ikke bare tagge et billede. I stedet skal du gennemgå hver afgrænsningsboks, der er registreret af modellen. Hvis boksen er omkring det forkerte objekt, skal den slettes, og hvis den er på det forkerte sted, skal den justeres.

### Opgave - gen-træn modellen

1. Sørg for, at du har indsamlet en række billeder ved hjælp af din IoT-enhed.

1. Fra fanen **Predictions** skal du vælge et billede. Du vil se røde bokse, der angiver afgrænsningsboksene for de registrerede objekter.

1. Gennemgå hver afgrænsningsboks. Vælg den først, og du vil se en pop-up, der viser tagget. Brug håndtagene på hjørnerne af afgrænsningsboksen til at justere størrelsen, hvis det er nødvendigt. Hvis tagget er forkert, skal du fjerne det med knappen **X** og tilføje det korrekte tag. Hvis afgrænsningsboksen ikke indeholder et objekt, skal du slette den med skraldespandsknappen.

1. Luk editoren, når du er færdig, og billedet flyttes fra fanen **Predictions** til fanen **Training Images**. Gentag processen for alle forudsigelser.

1. Brug knappen **Train** til at gen-træne din model. Når den er trænet, skal du udgive iterationen og opdatere din IoT-enhed til at bruge URL'en for den nye iteration.

1. Genudrul din kode, og test din IoT-enhed.

## Tæl lager

Ved at kombinere antallet af registrerede objekter og afgrænsningsboksene kan du tælle lageret på en hylde.

### Opgave - tæl lager

Følg den relevante guide nedenfor for at tælle lager ved hjælp af resultaterne fra objektdetektoren fra din IoT-enhed:

* [Arduino - Wio Terminal](wio-terminal-count-stock.md)
* [Single-board computer - Raspberry Pi/Virtual device](single-board-computer-count-stock.md)

---

## 🚀 Udfordring

Kan du registrere forkert lager? Træn din model på flere objekter, og opdater derefter din app til at advare dig, hvis det forkerte lager registreres.

Måske kan du endda tage det et skridt videre og registrere lager side om side på samme hylde og se, om noget er blevet placeret forkert ved at definere grænser for afgrænsningsboksene.

## Quiz efter lektionen

[Quiz efter lektionen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/40)

## Gennemgang & Selvstudie

* Lær mere om, hvordan man arkitekterer et end-to-end lagerdetektionssystem fra [Out of stock detection at the edge pattern guide på Microsoft Docs](https://docs.microsoft.com/hybrid/app-solutions/pattern-out-of-stock-at-edge?WT.mc_id=academic-17441-jabenn)
* Lær andre måder at bygge end-to-end detailhandelsløsninger, der kombinerer en række IoT- og cloud-tjenester, ved at se denne [Behind the scenes of a retail solution - Hands On! video på YouTube](https://www.youtube.com/watch?v=m3Pc300x2Mw).

## Opgave

[Brug din objektdetektor på kanten](assignment.md)

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på at sikre nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.