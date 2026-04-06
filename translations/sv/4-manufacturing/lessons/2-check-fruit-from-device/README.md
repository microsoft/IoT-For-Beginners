# Kontrollera fruktkvalitet med en IoT-enhet

![En sketchnote-översikt av denna lektion](../../../../../translated_images/sv/lesson-16.215daf18b00631fb.webp)

> Sketchnote av [Nitya Narasimhan](https://github.com/nitya). Klicka på bilden för en större version.

## Quiz före föreläsningen

[Quiz före föreläsningen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/31)

## Introduktion

I den senaste lektionen lärde du dig om bildklassificerare och hur man tränar dem för att identifiera bra och dålig frukt. För att använda denna bildklassificerare i en IoT-applikation behöver du kunna ta en bild med någon form av kamera och skicka denna bild till molnet för att klassificeras.

I denna lektion kommer du att lära dig om kamerasensorer och hur man använder dem med en IoT-enhet för att ta en bild. Du kommer också att lära dig hur man anropar bildklassificeraren från din IoT-enhet.

I denna lektion kommer vi att täcka:

* [Kamerasensorer](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Ta en bild med en IoT-enhet](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Publicera din bildklassificerare](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Klassificera bilder från din IoT-enhet](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Förbättra modellen](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)

## Kamerasensorer

Kamerasensorer, som namnet antyder, är kameror som du kan ansluta till din IoT-enhet. De kan ta stillbilder eller spela in strömmande video. Vissa returnerar rå bilddata, medan andra komprimerar bilddata till en bildfil som JPEG eller PNG. Vanligtvis är kamerorna som fungerar med IoT-enheter mycket mindre och har lägre upplösning än vad du kanske är van vid, men det finns högupplösta kameror som kan mäta sig med toppmoderna mobiltelefoner. Du kan få alla möjliga utbytbara linser, flera kamerauppsättningar, infraröda termiska kameror eller UV-kameror.

![Ljuset från en scen passerar genom en lins och fokuseras på en CMOS-sensor](../../../../../translated_images/sv/cmos-sensor.75f9cd74decb1371.webp)

De flesta kamerasensorer använder bildsensorer där varje pixel är en fotodiod. En lins fokuserar bilden på bildsensorn, och tusentals eller miljoner fotodioder registrerar ljuset som faller på var och en och sparar det som pixeldata.

> 💁 Linser inverterar bilder, och kamerasensorn vänder sedan bilden rätt igen. Det är samma sak med dina ögon - det du ser registreras upp och ner på baksidan av ditt öga, och din hjärna korrigerar det.

> 🎓 Bildsensorn kallas för en Active-Pixel Sensor (APS), och den mest populära typen av APS är en komplementär metalloxid-halvledarsensor, eller CMOS. Du kanske har hört termen CMOS-sensor användas för kamerasensorer.

Kamerasensorer är digitala sensorer som skickar bilddata som digital data, vanligtvis med hjälp av ett bibliotek som tillhandahåller kommunikationen. Kameror ansluter med protokoll som SPI för att kunna skicka stora mängder data - bilder är betydligt större än enstaka siffror från en sensor, som en temperatursensor.

✅ Vilka begränsningar finns kring bildstorlek med IoT-enheter? Tänk på begränsningarna, särskilt på mikrocontroller-hårdvara.

## Ta en bild med en IoT-enhet

Du kan använda din IoT-enhet för att ta en bild som ska klassificeras.

### Uppgift - ta en bild med en IoT-enhet

Följ den relevanta guiden för att ta en bild med din IoT-enhet:

* [Arduino - Wio Terminal](wio-terminal-camera.md)
* [Enkorts-dator - Raspberry Pi](pi-camera.md)
* [Enkorts-dator - Virtuell enhet](virtual-device-camera.md)

## Publicera din bildklassificerare

Du tränade din bildklassificerare i den senaste lektionen. Innan du kan använda den från din IoT-enhet måste du publicera modellen.

### Modelliterationer

När din modell tränades i den senaste lektionen kanske du märkte att fliken **Prestanda** visar iterationer på sidan. När du först tränade modellen såg du *Iteration 1* under träning. När du förbättrade modellen med hjälp av förutsägelsebilder såg du *Iteration 2* under träning.

Varje gång du tränar modellen får du en ny iteration. Detta är ett sätt att hålla reda på de olika versionerna av din modell som tränats på olika dataset. När du gör ett **Snabbtest** finns det en rullgardinsmeny som du kan använda för att välja iteration, så att du kan jämföra resultaten mellan flera iterationer.

När du är nöjd med en iteration kan du publicera den för att göra den tillgänglig för användning från externa applikationer. På så sätt kan du ha en publicerad version som används av dina enheter, och sedan arbeta på en ny version över flera iterationer och publicera den när du är nöjd med den.

### Uppgift - publicera en iteration

Iterationer publiceras från Custom Vision-portalen.

1. Öppna Custom Vision-portalen på [CustomVision.ai](https://customvision.ai) och logga in om du inte redan har den öppen. Öppna sedan ditt projekt `fruit-quality-detector`.

1. Välj fliken **Prestanda** från alternativen högst upp.

1. Välj den senaste iterationen från listan *Iterationer* på sidan.

1. Välj knappen **Publicera** för iterationen.

    ![Publiceringsknappen](../../../../../translated_images/sv/custom-vision-publish-button.b7174e1977b0c33b.webp)

1. I dialogrutan *Publicera modell*, ställ in *Förutsägelse-resurs* till resursen `fruit-quality-detector-prediction` som du skapade i den senaste lektionen. Lämna namnet som `Iteration2` och välj knappen **Publicera**.

1. När den har publicerats, välj knappen **Förutsägelse-URL**. Detta visar detaljer om förutsägelse-API:et, och du kommer att behöva dessa för att anropa modellen från din IoT-enhet. Den nedre sektionen är märkt *Om du har en bildfil*, och detta är detaljerna du vill ha. Ta en kopia av URL:en som visas, som kommer att se ut ungefär så här:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/classify/iterations/Iteration2/image
    ```

    Där `<location>` är platsen du använde när du skapade din Custom Vision-resurs, och `<id>` är ett långt ID bestående av bokstäver och siffror.

    Ta också en kopia av värdet *Förutsägelse-nyckel*. Detta är en säker nyckel som du måste skicka när du anropar modellen. Endast applikationer som skickar denna nyckel får använda modellen, alla andra applikationer avvisas.

    ![Dialogrutan för förutsägelse-API som visar URL och nyckel](../../../../../translated_images/sv/custom-vision-prediction-key-endpoint.30c569ffd0338864.webp)

✅ När en ny iteration publiceras kommer den att ha ett annat namn. Hur tror du att du skulle ändra iterationen som en IoT-enhet använder?

## Klassificera bilder från din IoT-enhet

Du kan nu använda dessa anslutningsdetaljer för att anropa bildklassificeraren från din IoT-enhet.

### Uppgift - klassificera bilder från din IoT-enhet

Följ den relevanta guiden för att klassificera bilder med din IoT-enhet:

* [Arduino - Wio Terminal](wio-terminal-classify-image.md)
* [Enkorts-dator - Raspberry Pi/Virtuell IoT-enhet](single-board-computer-classify-image.md)

## Förbättra modellen

Du kanske märker att resultaten du får när du använder kameran ansluten till din IoT-enhet inte matchar vad du förväntar dig. Förutsägelserna är inte alltid lika exakta som när du använder bilder som laddats upp från din dator. Detta beror på att modellen tränades på annan data än den som används för förutsägelser.

För att få bästa resultat för en bildklassificerare vill du träna modellen med bilder som är så lika de bilder som används för förutsägelser som möjligt. Om du till exempel använde din telefonkamera för att ta bilder för träning, kommer bildkvaliteten, skärpan och färgen att skilja sig från en kamera ansluten till en IoT-enhet.

![2 bananbilder, en lågupplöst med dålig belysning från en IoT-enhet, och en högupplöst med bra belysning från en telefon](../../../../../translated_images/sv/banana-picture-compare.174df164dc326a42.webp)

I bilden ovan togs bananbilden till vänster med en Raspberry Pi-kamera, medan den till höger togs av samma banan på samma plats med en iPhone. Det är en märkbar skillnad i kvalitet - iPhone-bilden är skarpare, med ljusare färger och mer kontrast.

✅ Vad kan annars orsaka att bilder som tas av din IoT-enhet ger felaktiga förutsägelser? Tänk på miljön där en IoT-enhet kan användas, vilka faktorer kan påverka bilden som tas?

För att förbättra modellen kan du träna om den med bilder som tagits från IoT-enheten.

### Uppgift - förbättra modellen

1. Klassificera flera bilder av både mogen och omogen frukt med din IoT-enhet.

1. I Custom Vision-portalen, träna om modellen med bilderna på fliken *Förutsägelser*.

    > ⚠️ Du kan hänvisa till [instruktionerna för att träna om din klassificerare i lektion 1 om det behövs](../1-train-fruit-detector/README.md#retrain-your-image-classifier).

1. Om dina bilder ser väldigt olika ut jämfört med de ursprungliga som användes för träning, kan du ta bort alla ursprungliga bilder genom att välja dem på fliken *Träningsbilder* och välja knappen **Ta bort**. För att välja en bild, flytta markören över den och en bock visas, välj den bocken för att välja eller avmarkera bilden.

1. Träna en ny iteration av modellen och publicera den med stegen ovan.

1. Uppdatera endpoint-URL:en i din kod och kör appen igen.

1. Upprepa dessa steg tills du är nöjd med resultaten av förutsägelserna.

---

## 🚀 Utmaning

Hur mycket påverkar bildupplösning eller belysning förutsägelsen?

Prova att ändra upplösningen på bilderna i din enhetskod och se om det gör någon skillnad för bildkvaliteten. Prova också att ändra belysningen.

Om du skulle skapa en produktionsenhet att sälja till gårdar eller fabriker, hur skulle du säkerställa att den ger konsekventa resultat hela tiden?

## Quiz efter föreläsningen

[Quiz efter föreläsningen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/32)

## Granskning & Självstudier

Du tränade din Custom Vision-modell med hjälp av portalen. Detta förutsätter att du har tillgång till bilder - och i verkligheten kanske du inte kan få träningsdata som matchar vad kameran på din enhet fångar. Du kan kringgå detta genom att träna direkt från din enhet med hjälp av tränings-API:et, för att träna en modell med bilder som tagits från din IoT-enhet.

* Läs om tränings-API:et i [snabbstarten för att använda Custom Vision SDK](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/quickstarts/image-classification?WT.mc_id=academic-17441-jabenn&tabs=visual-studio&pivots=programming-language-python)

## Uppgift

[Reagera på klassificeringsresultat](assignment.md)

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiserade översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess ursprungliga språk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.