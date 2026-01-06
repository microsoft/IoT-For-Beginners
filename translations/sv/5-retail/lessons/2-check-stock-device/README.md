<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1c9e5fa8b7be726c75a97232b1e41c97",
  "translation_date": "2025-08-27T22:15:53+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/README.md",
  "language_code": "sv"
}
-->
# Kontrollera lager från en IoT-enhet

![En sketchnote-översikt av denna lektion](../../../../../translated_images/lesson-20.0211df9551a8abb300fc8fcf7dc2789468dea2eabe9202273ac077b0ba37f15e.sv.jpg)

> Sketchnote av [Nitya Narasimhan](https://github.com/nitya). Klicka på bilden för en större version.

## Quiz före föreläsningen

[Quiz före föreläsningen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/39)

## Introduktion

I den föregående lektionen lärde du dig om de olika användningsområdena för objektdetektering inom detaljhandeln. Du lärde dig också hur man tränar en objektdetektor för att identifiera lager. I denna lektion kommer du att lära dig hur du använder din objektdetektor från din IoT-enhet för att räkna lager.

I denna lektion kommer vi att täcka:

* [Lagerberäkning](../../../../../5-retail/lessons/2-check-stock-device)
* [Anropa din objektdetektor från din IoT-enhet](../../../../../5-retail/lessons/2-check-stock-device)
* [Avgränsningsrutor](../../../../../5-retail/lessons/2-check-stock-device)
* [Träna om modellen](../../../../../5-retail/lessons/2-check-stock-device)
* [Räkna lager](../../../../../5-retail/lessons/2-check-stock-device)

> 🗑 Detta är den sista lektionen i detta projekt, så efter att du har slutfört lektionen och uppgiften, glöm inte att städa upp dina molntjänster. Du kommer att behöva tjänsterna för att slutföra uppgiften, så se till att göra det först.
>
> Se [guiden för att städa upp ditt projekt](../../../clean-up.md) vid behov för instruktioner om hur du gör detta.

## Lagerberäkning

Objektdetektorer kan användas för lagerkontroll, antingen för att räkna lager eller för att säkerställa att lager finns där det ska vara. IoT-enheter med kameror kan placeras runt hela butiken för att övervaka lager, med början vid hotspots där det är viktigt att fylla på varor, såsom områden där små mängder av högvärdesprodukter lagras.

Till exempel, om en kamera pekar på en hylla som kan hålla 8 burkar tomatpuré, och en objektdetektor bara upptäcker 7 burkar, saknas en och behöver fyllas på.

![7 burkar tomatpuré på en hylla, 4 på den övre raden, 3 på den nedre](../../../../../translated_images/stock-7-cans-tomato-paste.f86059cc573d7bec.sv.png)

I bilden ovan har en objektdetektor upptäckt 7 burkar tomatpuré på en hylla som kan hålla 8 burkar. IoT-enheten kan inte bara skicka en notifikation om behovet av påfyllning, utan kan även ge en indikation om var den saknade varan finns, viktig information om du använder robotar för att fylla på hyllor.

> 💁 Beroende på butiken och varans popularitet skulle påfyllning förmodligen inte ske om bara 1 burk saknas. Du skulle behöva bygga en algoritm som avgör när påfyllning ska ske baserat på dina produkter, kunder och andra kriterier.

✅ I vilka andra scenarier skulle du kunna kombinera objektdetektering och robotar?

Ibland kan fel lager finnas på hyllorna. Detta kan bero på mänskliga misstag vid påfyllning, eller att kunder ändrar sig om ett köp och lägger tillbaka en vara på första bästa plats. När det gäller icke-färskvaror som konserver är detta en irritation. Om det är en färskvara som frysta eller kylda varor kan detta innebära att produkten inte längre kan säljas eftersom det kan vara omöjligt att avgöra hur länge varan varit utanför frysen.

Objektdetektering kan användas för att upptäcka oväntade varor, och återigen varna en människa eller robot för att returnera varan så snart den upptäcks.

![En burk babymajs på tomatpuréhyllan](../../../../../translated_images/stock-rogue-corn.be1f3ada8c457854.sv.png)

I bilden ovan har en burk babymajs placerats på hyllan bredvid tomatpurén. Objektdetektorn har upptäckt detta, vilket gör att IoT-enheten kan notifiera en människa eller robot att returnera burken till dess rätta plats.

## Anropa din objektdetektor från din IoT-enhet

Objektdetektorn du tränade i den senaste lektionen kan anropas från din IoT-enhet.

### Uppgift - publicera en iteration av din objektdetektor

Iterationer publiceras från Custom Vision-portalen.

1. Öppna Custom Vision-portalen på [CustomVision.ai](https://customvision.ai) och logga in om du inte redan har den öppen. Öppna sedan ditt projekt `stock-detector`.

1. Välj fliken **Performance** från alternativen högst upp.

1. Välj den senaste iterationen från listan *Iterations* på sidan.

1. Klicka på knappen **Publish** för iterationen.

    ![Publiceringsknappen](../../../../../translated_images/custom-vision-object-detector-publish-button.34ee379fc650ccb9856c3868d0003f413b9529f102fc73c37168c98d721cc293.sv.png)

1. I dialogrutan *Publish Model*, ställ in *Prediction resource* till resursen `stock-detector-prediction` som du skapade i den senaste lektionen. Låt namnet vara `Iteration2` och klicka på knappen **Publish**.

1. När den har publicerats, klicka på knappen **Prediction URL**. Detta visar detaljer om prediktions-API:et, och du kommer att behöva dessa för att anropa modellen från din IoT-enhet. Den nedre sektionen är märkt *If you have an image file*, och det är dessa detaljer du vill ha. Ta en kopia av den visade URL:en som kommer att se ut ungefär så här:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/detect/iterations/Iteration2/image
    ```

    Där `<location>` är platsen du använde när du skapade din Custom Vision-resurs, och `<id>` är ett långt ID bestående av bokstäver och siffror.

    Ta också en kopia av värdet *Prediction-Key*. Detta är en säker nyckel som du måste skicka när du anropar modellen. Endast applikationer som skickar denna nyckel får använda modellen, alla andra applikationer avvisas.

    ![Dialogrutan för prediktions-API som visar URL och nyckel](../../../../../translated_images/custom-vision-prediction-key-endpoint.30c569ffd0338864f319911f052d5e9b8c5066cb0800a26dd6f7ff5713130ad8.sv.png)

✅ När en ny iteration publiceras kommer den att ha ett annat namn. Hur tror du att du skulle ändra iterationen som en IoT-enhet använder?

### Uppgift - anropa din objektdetektor från din IoT-enhet

Följ relevant guide nedan för att använda objektdetektorn från din IoT-enhet:

* [Arduino - Wio Terminal](wio-terminal-object-detector.md)
* [Enkorts-dator - Raspberry Pi/Virtual device](single-board-computer-object-detector.md)

## Avgränsningsrutor

När du använder objektdetektorn får du inte bara tillbaka de upptäckta objekten med deras taggar och sannolikheter, utan du får också avgränsningsrutorna för objekten. Dessa definierar var objektdetektorn upptäckte objektet med den angivna sannolikheten.

> 💁 En avgränsningsruta är en ruta som definierar området som innehåller det upptäckta objektet, en ruta som definierar gränsen för objektet.

Resultaten av en prediktion i fliken **Predictions** i Custom Vision har avgränsningsrutorna ritade på bilden som skickades för prediktion.

![4 burkar tomatpuré på en hylla med prediktioner för de 4 upptäckterna med 35.8%, 33.5%, 25.7% och 16.6%](../../../../../translated_images/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.sv.png)

I bilden ovan upptäcktes 4 burkar tomatpuré. I resultaten är en röd fyrkant överlagd för varje objekt som upptäcktes i bilden, vilket indikerar avgränsningsrutan för bilden.

✅ Öppna prediktionerna i Custom Vision och kolla in avgränsningsrutorna.

Avgränsningsrutor definieras med 4 värden - top, left, height och width. Dessa värden är på en skala från 0-1, vilket representerar positionerna som en procentandel av bildens storlek. Ursprungspunkten (positionen 0,0) är det övre vänstra hörnet av bilden, så top-värdet är avståndet från toppen, och botten av avgränsningsrutan är top plus height.

![En avgränsningsruta runt en burk tomatpuré](../../../../../translated_images/bounding-box.1420a7ea0d3d15f71e1ffb5cf4b2271d184fac051f990abc541975168d163684.sv.png)

Bilden ovan är 600 pixlar bred och 800 pixlar hög. Avgränsningsrutan börjar 320 pixlar ner, vilket ger ett top-koordinat på 0.4 (800 x 0.4 = 320). Från vänster börjar avgränsningsrutan 240 pixlar in, vilket ger ett left-koordinat på 0.4 (600 x 0.4 = 240). Höjden på avgränsningsrutan är 240 pixlar, vilket ger ett height-värde på 0.3 (800 x 0.3 = 240). Bredden på avgränsningsrutan är 120 pixlar, vilket ger ett width-värde på 0.2 (600 x 0.2 = 120).

| Koordinat | Värde |
| ---------- | ----: |
| Top        | 0.4   |
| Left       | 0.4   |
| Height     | 0.3   |
| Width      | 0.2   |

Att använda procentvärden från 0-1 innebär att oavsett vilken storlek bilden skalas till, börjar avgränsningsrutan 0.4 av vägen längs och ner, och är 0.3 av höjden och 0.2 av bredden.

Du kan använda avgränsningsrutor kombinerat med sannolikheter för att utvärdera hur korrekt en upptäckt är. Till exempel kan en objektdetektor upptäcka flera objekt som överlappar, till exempel upptäcka en burk inuti en annan. Din kod kan titta på avgränsningsrutorna, förstå att detta är omöjligt, och ignorera alla objekt som har en betydande överlappning med andra objekt.

![Två avgränsningsrutor som överlappar en burk tomatpuré](../../../../../translated_images/overlap-object-detection.d431e03cae75072a2760430eca7f2c5fdd43045bfd72dadcbf12711f7cd6c2ae.sv.png)

I exemplet ovan indikerar en avgränsningsruta en förutsedd burk tomatpuré med 78.3%. En andra avgränsningsruta är något mindre och ligger inuti den första avgränsningsrutan med en sannolikhet på 64.3%. Din kod kan kontrollera avgränsningsrutorna, se att de överlappar helt, och ignorera den lägre sannolikheten eftersom det inte är möjligt att en burk är inuti en annan.

✅ Kan du tänka dig en situation där det är giltigt att upptäcka ett objekt inuti ett annat?

## Träna om modellen

Precis som med bildklassificeraren kan du träna om din modell med data som samlats in av din IoT-enhet. Att använda denna verkliga data kommer att säkerställa att din modell fungerar bra när den används från din IoT-enhet.

Till skillnad från bildklassificeraren kan du inte bara tagga en bild. Istället måste du granska varje avgränsningsruta som upptäckts av modellen. Om rutan är runt fel sak måste den tas bort, om den är på fel plats måste den justeras.

### Uppgift - träna om modellen

1. Se till att du har samlat in en mängd bilder med din IoT-enhet.

1. Från fliken **Predictions**, välj en bild. Du kommer att se röda rutor som indikerar avgränsningsrutorna för de upptäckta objekten.

1. Gå igenom varje avgränsningsruta. Välj den först så ser du en popup som visar taggen. Använd handtagen i hörnen på avgränsningsrutan för att justera storleken vid behov. Om taggen är fel, ta bort den med knappen **X** och lägg till rätt tagg. Om avgränsningsrutan inte innehåller ett objekt, ta bort den med papperskorgsknappen.

1. Stäng redigeraren när du är klar och bilden flyttas från fliken **Predictions** till fliken **Training Images**. Upprepa processen för alla prediktioner.

1. Använd knappen **Train** för att träna om din modell. När den har tränats, publicera iterationen och uppdatera din IoT-enhet för att använda URL:en för den nya iterationen.

1. Återimplementera din kod och testa din IoT-enhet.

## Räkna lager

Med en kombination av antalet upptäckta objekt och avgränsningsrutorna kan du räkna lagret på en hylla.

### Uppgift - räkna lager

Följ relevant guide nedan för att räkna lager med resultaten från objektdetektorn från din IoT-enhet:

* [Arduino - Wio Terminal](wio-terminal-count-stock.md)
* [Enkorts-dator - Raspberry Pi/Virtual device](single-board-computer-count-stock.md)

---

## 🚀 Utmaning

Kan du upptäcka felaktigt lager? Träna din modell på flera objekt och uppdatera sedan din app för att varna dig om fel lager upptäcks.

Kanske ta detta ännu längre och upptäcka lager sida vid sida på samma hylla, och se om något har placerats på fel plats genom att definiera gränser för avgränsningsrutorna.

## Quiz efter föreläsningen

[Quiz efter föreläsningen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/40)

## Granskning & Självstudier

* Läs mer om hur man arkitekterar ett end-to-end lagerdetekteringssystem från [Out of stock detection at the edge pattern guide på Microsoft Docs](https://docs.microsoft.com/hybrid/app-solutions/pattern-out-of-stock-at-edge?WT.mc_id=academic-17441-jabenn)
* Lär dig andra sätt att bygga end-to-end lösningar för detaljhandeln genom att kombinera en rad IoT- och molntjänster genom att titta på denna [Behind the scenes of a retail solution - Hands On! video på YouTube](https://www.youtube.com/watch?v=m3Pc300x2Mw).

## Uppgift

[Använd din objektdetektor vid kanten](assignment.md)

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, vänligen notera att automatiska översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.