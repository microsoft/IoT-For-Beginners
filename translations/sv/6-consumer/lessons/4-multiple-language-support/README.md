# Stöd för flera språk

![En sketchnote-översikt av denna lektion](../../../../../translated_images/sv/lesson-24.4246968ed058510a.webp)

> Sketchnote av [Nitya Narasimhan](https://github.com/nitya). Klicka på bilden för en större version.

Den här videon ger en översikt över Azure tal-tjänster, inklusive tal-till-text och text-till-tal från tidigare lektioner, samt talöversättning, ett ämne som behandlas i denna lektion:

[![Känna igen tal med några rader Python från Microsoft Build 2020](https://img.youtube.com/vi/h6xbpMPSGEA/0.jpg)](https://www.youtube.com/watch?v=h6xbpMPSGEA)

> 🎥 Klicka på bilden ovan för att se videon

## Quiz före lektionen

[Quiz före lektionen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/47)

## Introduktion

Under de senaste tre lektionerna har du lärt dig om att konvertera tal till text, språkförståelse och att konvertera text till tal, allt drivet av AI. Ett annat område inom mänsklig kommunikation där AI kan hjälpa till är språköversättning – att konvertera från ett språk till ett annat, som från engelska till franska.

I denna lektion kommer du att lära dig att använda AI för att översätta text, vilket gör att din smarta timer kan interagera med användare på flera språk.

I denna lektion kommer vi att behandla:

* [Översätta text](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Översättningstjänster](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Skapa en översättningsresurs](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Stöd för flera språk i applikationer med översättningar](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Översätta text med en AI-tjänst](../../../../../6-consumer/lessons/4-multiple-language-support)

> 🗑 Detta är den sista lektionen i detta projekt, så efter att du har slutfört denna lektion och uppgiften, glöm inte att städa upp dina molntjänster. Du kommer att behöva tjänsterna för att slutföra uppgiften, så se till att göra det först.
>
> Se [guiden för att städa upp ditt projekt](../../../clean-up.md) vid behov för instruktioner om hur du gör detta.

## Översätta text

Textöversättning har varit ett problem inom datavetenskap som har forskats på i över 70 år, och tack vare framsteg inom AI och datorkraft är det nu nära att lösas till en nivå som nästan är lika bra som mänskliga översättare.

> 💁 Ursprung kan spåras ännu längre tillbaka, till [Al-Kindi](https://wikipedia.org/wiki/Al-Kindi), en arabisk kryptograf från 800-talet som utvecklade tekniker för språköversättning.

### Maskinöversättningar

Textöversättning började som en teknik känd som Maskinöversättning (MT), som kan översätta mellan olika språkpar. MT fungerar genom att ersätta ord i ett språk med ett annat, och använder tekniker för att välja rätt sätt att översätta fraser eller delar av meningar när en enkel ord-för-ord-översättning inte fungerar.

> 🎓 När översättare stöder översättning mellan ett språk och ett annat, kallas dessa för *språkpar*. Olika verktyg stöder olika språkpar, och dessa kan vara ofullständiga. Till exempel kan en översättare stödja engelska till spanska som ett språkpar, och spanska till italienska som ett språkpar, men inte engelska till italienska.

Till exempel kan översättningen av "Hello world" från engelska till franska utföras med en substitution – "Bonjour" för "Hello", och "le monde" för "world", vilket leder till den korrekta översättningen "Bonjour le monde".

Substitutioner fungerar inte när olika språk använder olika sätt att säga samma sak. Till exempel översätts den engelska meningen "My name is Jim" till "Je m'appelle Jim" på franska – bokstavligen "Jag kallar mig Jim". "Je" är franska för "jag", "moi" är "mig", men det kombineras med verbet eftersom det börjar med en vokal, så det blir "m'", "appelle" betyder att kalla, och "Jim" översätts inte eftersom det är ett namn och inte ett ord som kan översättas. Ordföljden blir också ett problem – en enkel substitution av "Je m'appelle Jim" blir "I myself call Jim", med en annan ordföljd än engelska.

> 💁 Vissa ord översätts aldrig – mitt namn är Jim oavsett vilket språk som används för att presentera mig. När man översätter till språk som använder olika alfabet, eller olika bokstäver för olika ljud, kan ord *translitereras*, det vill säga välja bokstäver eller tecken som ger rätt ljud för att låta som det givna ordet.

Idiomer är också ett problem för översättning. Dessa är fraser som har en förstådd betydelse som skiljer sig från en direkt tolkning av orden. Till exempel, på engelska betyder idiomet "I've got ants in my pants" inte bokstavligen att ha myror i kläderna, utan att vara rastlös. Om du översätter detta till tyska skulle du förvirra lyssnaren, eftersom den tyska versionen är "Ich habe Hummeln im Hintern".

> 💁 Olika lokala variationer tillför olika komplexiteter. Med idiomet "ants in your pants", i amerikansk engelska syftar "pants" på ytterkläder, medan det i brittisk engelska betyder underkläder.

✅ Om du talar flera språk, tänk på några fraser som inte direkt kan översättas.

Maskinöversättningssystem förlitar sig på stora databaser med regler som beskriver hur man översätter vissa fraser och idiomer, tillsammans med statistiska metoder för att välja de mest lämpliga översättningarna från möjliga alternativ. Dessa statistiska metoder använder enorma databaser med verk som översatts av människor till flera språk för att välja den mest sannolika översättningen, en teknik som kallas *statistisk maskinöversättning*. Många av dessa använder mellanliggande representationer av språket, vilket gör att ett språk kan översättas till det mellanliggande, och sedan från det mellanliggande till ett annat språk. På detta sätt innebär tillägg av fler språk översättningar till och från det mellanliggande, inte till och från alla andra språk.

### Neurala översättningar

Neurala översättningar använder AI:s kraft för att översätta, vanligtvis genom att översätta hela meningar med en modell. Dessa modeller tränas på enorma dataset som har översatts av människor, såsom webbsidor, böcker och FN-dokumentation.

Neurala översättningsmodeller är vanligtvis mindre än maskinöversättningsmodeller eftersom de inte behöver stora databaser med fraser och idiomer. Moderna AI-tjänster som erbjuder översättningar blandar ofta flera tekniker, inklusive statistisk maskinöversättning och neurala översättningar.

Det finns ingen 1:1-översättning för något språkpar. Olika översättningsmodeller kommer att producera något olika resultat beroende på data som användes för att träna modellen. Översättningar är inte alltid symmetriska – om du översätter en mening från ett språk till ett annat, och sedan tillbaka till det första språket, kan du få en något annorlunda mening som resultat.

✅ Prova olika onlineöversättare som [Bing Translate](https://www.bing.com/translator), [Google Translate](https://translate.google.com) eller Apples översättningsapp. Jämför de översatta versionerna av några meningar. Prova också att översätta i en och sedan översätta tillbaka i en annan.

## Översättningstjänster

Det finns ett antal AI-tjänster som kan användas från dina applikationer för att översätta tal och text.

### Cognitive services Speech service

![Logotypen för tal-tjänsten](../../../../../translated_images/sv/azure-speech-logo.a1f08c4befb0159f.webp)

Tal-tjänsten som du har använt under de senaste lektionerna har översättningsmöjligheter för taligenkänning. När du känner igen tal kan du begära inte bara texten av talet på samma språk, utan också på andra språk.

> 💁 Detta är endast tillgängligt från tal-SDK:n, REST-API:n har inte inbyggda översättningar.

### Cognitive services Translator service

![Logotypen för översättningstjänsten](../../../../../translated_images/sv/azure-translator-logo.c6ed3a4a433edfd2.webp)

Översättningstjänsten är en dedikerad översättningstjänst som kan översätta text från ett språk till ett eller flera målspråk. Förutom att översätta stöder den ett brett utbud av extra funktioner, inklusive att maskera svordomar. Den låter dig också ange en specifik översättning för ett visst ord eller en mening, för att hantera termer du inte vill översätta eller har en specifik välkänd översättning.

Till exempel, när du översätter meningen "I have a Raspberry Pi", som hänvisar till enkortsdatorn, till ett annat språk som franska, skulle du vilja behålla namnet "Raspberry Pi" som det är och inte översätta det, vilket ger "J’ai un Raspberry Pi" istället för "J’ai une pi aux framboises".

## Skapa en översättningsresurs

För denna lektion behöver du en översättningsresurs. Du kommer att använda REST-API:n för att översätta text.

### Uppgift - skapa en översättningsresurs

1. Kör följande kommando från din terminal eller kommandotolk för att skapa en översättningsresurs i din `smart-timer`-resursgrupp.

    ```sh
    az cognitiveservices account create --name smart-timer-translator \
                                        --resource-group smart-timer \
                                        --kind TextTranslation \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Ersätt `<location>` med platsen du använde när du skapade resursgruppen.

1. Hämta nyckeln för översättningstjänsten:

    ```sh
    az cognitiveservices account keys list --name smart-timer-translator \
                                           --resource-group smart-timer \
                                           --output table
    ```

    Ta en kopia av en av nycklarna.

## Stöd för flera språk i applikationer med översättningar

I en idealisk värld bör hela din applikation förstå så många olika språk som möjligt, från att lyssna på tal, till språkförståelse, till att svara med tal. Detta är mycket arbete, så översättningstjänster kan påskynda leveranstiden för din applikation.

![En smart timer-arkitektur som översätter japanska till engelska, bearbetar på engelska och sedan översätter tillbaka till japanska](../../../../../translated_images/sv/translated-smart-timer.08ac20057fdc5c37.webp)

Föreställ dig att du bygger en smart timer som använder engelska från början till slut, förstår talad engelska och konverterar det till text, kör språkförståelse på engelska, bygger upp svar på engelska och svarar med engelskt tal. Om du ville lägga till stöd för japanska, skulle du kunna börja med att översätta talad japanska till engelsk text, sedan behålla kärnan i applikationen densamma, och sedan översätta svarstexten till japanska innan du talar svaret. Detta skulle göra det möjligt för dig att snabbt lägga till stöd för japanska, och du kan expandera till att erbjuda fullständigt stöd för japanska senare.

> 💁 Nackdelen med att förlita sig på maskinöversättning är att olika språk och kulturer har olika sätt att uttrycka samma saker, så översättningen kanske inte matchar det uttryck du förväntar dig.

Maskinöversättningar öppnar också upp möjligheter för appar och enheter som kan översätta användargenererat innehåll när det skapas. Science fiction innehåller regelbundet "universella översättare", enheter som kan översätta från främmande språk till (vanligtvis) amerikansk engelska. Dessa enheter är mindre science fiction och mer vetenskaplig verklighet, om man bortser från den främmande delen. Det finns redan appar och enheter som erbjuder realtidsöversättning av tal och skriven text, med kombinationer av tal- och översättningstjänster.

Ett exempel är mobilappen [Microsoft Translator](https://www.microsoft.com/translator/apps/?WT.mc_id=academic-17441-jabenn), som demonstreras i denna video:

[![Microsoft Translator live-funktion i aktion](https://img.youtube.com/vi/16yAGeP2FuM/0.jpg)](https://www.youtube.com/watch?v=16yAGeP2FuM)

> 🎥 Klicka på bilden ovan för att se videon

Föreställ dig att ha en sådan enhet tillgänglig, särskilt när du reser eller interagerar med personer vars språk du inte kan. Att ha automatiska översättningsenheter på flygplatser eller sjukhus skulle ge mycket behövda förbättringar av tillgängligheten.

✅ Gör lite forskning: Finns det några översättnings-IoT-enheter kommersiellt tillgängliga? Vad sägs om översättningsfunktioner inbyggda i smarta enheter?

> 👽 Även om det inte finns några riktiga universella översättare som låter oss prata med utomjordingar, stöder [Microsoft Translator faktiskt klingonska](https://www.microsoft.com/translator/blog/2013/05/14/announcing-klingon-for-bing-translator/?WT.mc_id=academic-17441-jabenn). Qapla’!

## Översätta text med en AI-tjänst

Du kan använda en AI-tjänst för att lägga till denna översättningsfunktion till din smarta timer.

### Uppgift - översätta text med en AI-tjänst

Arbeta igenom den relevanta guiden för att konvertera och översätta text på din IoT-enhet:

* [Arduino - Wio Terminal](wio-terminal-translate-speech.md)
* [Enkortsdator - Raspberry Pi](pi-translate-speech.md)
* [Enkortsdator - Virtuell enhet](virtual-device-translate-speech.md)

---

## 🚀 Utmaning

Hur kan maskinöversättningar gynna andra IoT-applikationer utöver smarta enheter? Tänk på olika sätt som översättningar kan hjälpa, inte bara med talade ord utan även med text.

## Quiz efter lektionen

[Quiz efter lektionen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/48)

## Granskning & Självstudier

* Läs mer om maskinöversättning på [maskinöversättningssidan på Wikipedia](https://wikipedia.org/wiki/Machine_translation)
* Läs mer om neurala maskinöversättningar på [neurala maskinöversättningssidan på Wikipedia](https://wikipedia.org/wiki/Neural_machine_translation)
* Kolla in listan över stödda språk för Microsoft tal-tjänster i [dokumentationen om språk- och röststöd för tal-tjänsten på Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn)

## Uppgift

[Bygg en universell översättare](assignment.md)

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiserade översättningar kan innehålla fel eller inexaktheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.