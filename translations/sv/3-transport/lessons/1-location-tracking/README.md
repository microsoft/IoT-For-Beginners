# Platsspårning

![En sketchnote-översikt av denna lektion](../../../../../translated_images/sv/lesson-11.9fddbac4b664c6d5.webp)

> Sketchnote av [Nitya Narasimhan](https://github.com/nitya). Klicka på bilden för en större version.

## Quiz före föreläsningen

[Quiz före föreläsningen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/21)

## Introduktion

Huvudprocessen för att få mat från en bonde till en konsument innebär att lasta lådor med produkter på lastbilar, fartyg, flygplan eller andra kommersiella transportfordon och leverera maten någonstans – antingen direkt till en kund eller till en central hubb eller lager för bearbetning. Hela processen från gård till konsument är en del av en process som kallas *leveranskedjan*. Videon nedan från Arizona State Universitys W. P. Carey School of Business förklarar idén med leveranskedjan och hur den hanteras i mer detalj.

[![Vad är leveranskedjehantering? En video från Arizona State Universitys W. P. Carey School of Business](https://img.youtube.com/vi/Mi1QBxVjZAw/0.jpg)](https://www.youtube.com/watch?v=Mi1QBxVjZAw)

> 🎥 Klicka på bilden ovan för att titta på videon

Att lägga till IoT-enheter kan drastiskt förbättra din leveranskedja, vilket gör det möjligt att hantera var föremål befinner sig, planera transport och godshantering bättre samt reagera snabbare på problem.

När man hanterar en fordonsflotta, som lastbilar, är det användbart att veta var varje fordon befinner sig vid en given tidpunkt. Fordon kan utrustas med GPS-sensorer som skickar sin plats till IoT-system, vilket gör det möjligt för ägarna att lokalisera dem, se vilken rutt de har tagit och veta när de kommer att anlända till sin destination. De flesta fordon befinner sig utanför WiFi-täckning, så de använder mobilnät för att skicka denna typ av data. Ibland är GPS-sensorn inbyggd i mer komplexa IoT-enheter, som elektroniska loggböcker. Dessa enheter spårar hur länge en lastbil har varit i transit för att säkerställa att förarna följer lokala lagar om arbetstider.

I denna lektion kommer du att lära dig hur man spårar ett fordons plats med hjälp av en Global Positioning System (GPS)-sensor.

I denna lektion kommer vi att täcka:

* [Uppkopplade fordon](../../../../../3-transport/lessons/1-location-tracking)
* [Geospatiala koordinater](../../../../../3-transport/lessons/1-location-tracking)
* [Global Positioning Systems (GPS)](../../../../../3-transport/lessons/1-location-tracking)
* [Läsa GPS-sensordata](../../../../../3-transport/lessons/1-location-tracking)
* [NMEA GPS-data](../../../../../3-transport/lessons/1-location-tracking)
* [Avkoda GPS-sensordata](../../../../../3-transport/lessons/1-location-tracking)

## Uppkopplade fordon

IoT förändrar sättet varor transporteras på genom att skapa flottor av *uppkopplade fordon*. Dessa fordon är anslutna till centrala IT-system och rapporterar information om sin plats och annan sensordata. Att ha en flotta av uppkopplade fordon ger en rad fördelar:

* Platsspårning – du kan exakt lokalisera var ett fordon befinner sig när som helst, vilket gör det möjligt att:

  * Få aviseringar när ett fordon är på väg att anlända till en destination för att förbereda en besättning för lossning
  * Lokalisera stulna fordon
  * Kombinera plats- och ruttdata med trafikproblem för att kunna omdirigera fordon under resan
  * Följa skattelagar. Vissa länder tar ut avgifter för fordon baserat på körsträcka på allmänna vägar (som [Nya Zeelands RUC](https://www.nzta.govt.nz/vehicles/licensing-rego/road-user-charges/)), så att veta när ett fordon är på allmänna vägar kontra privata vägar gör det enklare att beräkna skatteskulden.
  * Veta var man ska skicka underhållsbesättningar vid ett haveri

* Förartelemetri – säkerställa att förare följer hastighetsbegränsningar, svänger i lämpliga hastigheter, bromsar tidigt och effektivt samt kör säkert. Uppkopplade fordon kan också ha kameror för att spela in incidenter. Detta kan kopplas till försäkringar och ge lägre premier för säkra förare.

* Efterlevnad av förartimmar – säkerställa att förare endast kör under sina lagligt tillåtna timmar baserat på tiderna de startar och stänger av motorn.

Dessa fördelar kan kombineras – till exempel att kombinera efterlevnad av förartimmar med platsspårning för att omdirigera förare om de inte kan nå sin destination inom sina tillåtna körtimmar. Dessa kan också kombineras med annan fordonspecifik telemetri, som temperaturdata från temperaturkontrollerade lastbilar, vilket gör det möjligt att omdirigera fordon om deras nuvarande rutt skulle innebära att varor inte kan hållas vid rätt temperatur.

> 🎓 Logistik är processen att transportera varor från en plats till en annan, som från en gård till en stormarknad via ett eller flera lager. En bonde packar lådor med tomater som lastas på en lastbil, levereras till ett centralt lager och lastas på en andra lastbil som kan innehålla en blandning av olika typer av produkter som sedan levereras till en stormarknad.

Den centrala komponenten i fordonsuppföljning är GPS – sensorer som kan exakt lokalisera sin position var som helst på jorden. I denna lektion kommer du att lära dig hur man använder en GPS-sensor, med början i att förstå hur man definierar en plats på jorden.

## Geospatiala koordinater

Geospatiala koordinater används för att definiera punkter på jordens yta, liknande hur koordinater kan användas för att rita en pixel på en datorskärm eller placera stygn i korsstygn. För en enskild punkt har du ett par koordinater. Till exempel ligger Microsofts campus i Redmond, Washington, USA på 47.6423109, -122.1390293.

### Latitud och longitud

Jorden är en sfär – en tredimensionell cirkel. På grund av detta definieras punkter genom att dela in den i 360 grader, samma som cirklarnas geometri. Latitud mäter antalet grader norr till söder, longitud mäter antalet grader öster till väster.

> 💁 Ingen vet riktigt varför cirklar delas in i 360 grader. [Wikipedia-sidan om grader (vinkel)](https://wikipedia.org/wiki/Degree_(angle)) täcker några av de möjliga anledningarna.

![Latitudlinjer från 90° vid Nordpolen, 45° halvvägs mellan Nordpolen och ekvatorn, 0° vid ekvatorn, -45° halvvägs mellan ekvatorn och Sydpolen och -90° vid Sydpolen](../../../../../translated_images/sv/latitude-lines.11d8d91dfb2014a5.webp)

Latitud mäts med linjer som cirklar jorden och löper parallellt med ekvatorn, vilket delar norra och södra halvkloten i 90° vardera. Ekvatorn är vid 0°, Nordpolen är vid 90°, även känd som 90° nordlig, och Sydpolen är vid -90°, eller 90° sydlig.

Longitud mäts som antalet grader öster och väster. 0°-ursprunget för longitud kallas *nollmeridianen* och definierades 1884 som en linje från Nordpolen till Sydpolen som går genom [British Royal Observatory i Greenwich, England](https://wikipedia.org/wiki/Royal_Observatory,_Greenwich).

![Longitudlinjer som går från -180° väster om nollmeridianen, till 0° på nollmeridianen, till 180° öster om nollmeridianen](../../../../../translated_images/sv/longitude-meridians.ab4ef1c91c064586.webp)

> 🎓 En meridian är en tänkt rak linje som går från Nordpolen till Sydpolen och bildar en halvcirkel.

För att mäta longituden för en punkt mäter du antalet grader runt ekvatorn från nollmeridianen till en meridian som passerar genom den punkten. Longitud går från -180°, eller 180° väst, genom 0° vid nollmeridianen, till 180°, eller 180° öst. 180° och -180° hänvisar till samma punkt, antimeridianen eller 180:e meridianen. Detta är en meridian på motsatt sida av jorden från nollmeridianen.

> 💁 Antimeridianen ska inte förväxlas med den internationella datumlinjen, som ligger ungefär på samma plats men inte är en rak linje och varierar för att passa runt geopolitiska gränser.

✅ Gör lite forskning: Försök att hitta latituden och longituden för din nuvarande plats.

### Grader, minuter och sekunder kontra decimala grader

Traditionellt mättes grader av latitud och longitud med sexagesimalt system, eller bas-60, ett numreringssystem som användes av de gamla babylonierna som först mätte och registrerade tid och avstånd. Du använder sexagesimalt varje dag utan att ens tänka på det – genom att dela timmar i 60 minuter och minuter i 60 sekunder.

Longitud och latitud mäts i grader, minuter och sekunder, där en minut är 1/60 av en grad och 1 sekund är 1/60 minut.

Till exempel, vid ekvatorn:

* 1° latitud är **111,3 kilometer**
* 1 minut latitud är 111,3/60 = **1,855 kilometer**
* 1 sekund latitud är 1,855/60 = **0,031 kilometer**

Symbolen för en minut är ett enkelt citattecken, för en sekund är det ett dubbelt citattecken. 2 grader, 17 minuter och 43 sekunder skulle till exempel skrivas som 2°17'43". Delar av sekunder anges som decimaler, till exempel är en halv sekund 0°0'0,5".

Datorer fungerar inte i bas-60, så dessa koordinater anges som decimala grader när GPS-data används i de flesta datasystem. Till exempel är 2°17'43" 2,295277. Gradtecknet utelämnas vanligtvis.

Koordinater för en punkt anges alltid som `latitud, longitud`, så exemplet tidigare med Microsofts campus på 47.6423109,-122.117198 har:

* En latitud på 47.6423109 (47.6423109 grader norr om ekvatorn)
* En longitud på -122.1390293 (122.1390293 grader väster om nollmeridianen).

![Microsofts campus på 47.6423109,-122.117198](../../../../../translated_images/sv/microsoft-gps-location-world.a321d481b010f6ad.webp)

## Global Positioning Systems (GPS)

GPS-system använder flera satelliter som kretsar runt jorden för att lokalisera din position. Du har förmodligen använt GPS-system utan att ens tänka på det – för att hitta din plats i en kartapp på din telefon som Apple Maps eller Google Maps, för att se var din skjuts befinner sig i en app som Uber eller Lyft, eller när du använder satellitnavigering (sat-nav) i din bil.

> 🎓 Satelliterna i "satellitnavigering" är GPS-satelliter!

GPS-system fungerar genom att ha ett antal satelliter som skickar en signal med varje satellits aktuella position och en exakt tidsstämpel. Dessa signaler skickas via radiovågor och upptäcks av en antenn i GPS-sensorn. En GPS-sensor upptäcker dessa signaler och använder den aktuella tiden för att mäta hur lång tid det tog för signalen att nå sensorn från satelliten. Eftersom radiovågornas hastighet är konstant kan GPS-sensorn använda tidsstämpeln som skickades för att räkna ut hur långt bort sensorn är från satelliten. Genom att kombinera data från minst tre satelliter med de positioner som skickas kan GPS-sensorn exakt lokalisera sin plats på jorden.

> 💁 GPS-sensorer behöver antenner för att upptäcka radiovågor. Antennerna som är inbyggda i lastbilar och bilar med inbyggd GPS är placerade för att få en bra signal, vanligtvis på vindrutan eller taket. Om du använder ett separat GPS-system, som en smartphone eller en IoT-enhet, måste du se till att antennen som är inbyggd i GPS-systemet eller telefonen har fri sikt mot himlen, till exempel genom att monteras på vindrutan.

![Genom att veta avståndet från sensorn till flera satelliter kan platsen beräknas](../../../../../translated_images/sv/gps-satellites.04acf1148fe25fbf.webp)

GPS-satelliter kretsar runt jorden och är inte på en fast punkt ovanför sensorn, så platsdata inkluderar höjd över havet samt latitud och longitud.

GPS hade tidigare begränsningar i noggrannhet som infördes av den amerikanska militären, vilket begränsade noggrannheten till cirka 5 meter. Denna begränsning togs bort år 2000, vilket möjliggjorde en noggrannhet på 30 centimeter. Att uppnå denna noggrannhet är dock inte alltid möjligt på grund av störningar i signalerna.

✅ Om du har en smartphone, starta kartappen och se hur exakt din plats är. Det kan ta en kort stund för din telefon att upptäcka flera satelliter för att få en mer exakt plats.
💁 Satelliterna innehåller atomur som är otroligt precisa, men de driver med 38 mikrosekunder (0,0000038 sekunder) per dag jämfört med atomur på jorden, på grund av att tiden saktar ner när hastigheten ökar, som förutspåtts av Einsteins teorier om den speciella och allmänna relativitetsteorin – satelliterna rör sig snabbare än jordens rotation. Denna avvikelse har använts för att bevisa förutsägelserna i den speciella och allmänna relativitetsteorin och måste justeras för i utformningen av GPS-system. Bokstavligen går tiden långsammare på en GPS-satellit.
GPS-system har utvecklats och implementerats av flera länder och politiska unioner, inklusive USA, Ryssland, Japan, Indien, EU och Kina. Moderna GPS-sensorer kan ansluta till de flesta av dessa system för att få snabbare och mer exakta positioner.

> 🎓 Grupperna av satelliter i varje system kallas för konstellationer.

## Läs GPS-sensordata

De flesta GPS-sensorer skickar GPS-data via UART.

> ⚠️ UART behandlades i [projekt 2, lektion 2](../../../2-farm/lessons/2-detect-soil-moisture/README.md#universal-asynchronous-receiver-transmitter-uart). Gå tillbaka till den lektionen vid behov.

Du kan använda en GPS-sensor på din IoT-enhet för att få GPS-data.

### Uppgift - anslut en GPS-sensor och läs GPS-data

Följ den relevanta guiden för att läsa GPS-data med din IoT-enhet:

* [Arduino - Wio Terminal](wio-terminal-gps-sensor.md)
* [Enkortsdator - Raspberry Pi](pi-gps-sensor.md)
* [Enkortsdator - Virtuell enhet](virtual-device-gps-sensor.md)

## NMEA GPS-data

När du körde din kod såg du förmodligen något som kan verka som nonsens i utdata. Detta är faktiskt standard GPS-data, och allt har en betydelse.

GPS-sensorer skickar data med NMEA-meddelanden enligt NMEA 0183-standarden. NMEA är en förkortning för [National Marine Electronics Association](https://www.nmea.org), en amerikansk branschorganisation som sätter standarder för kommunikation mellan marina elektroniska enheter.

> 💁 Denna standard är proprietär och kostar minst 2 000 USD, men tillräckligt med information om den finns i det offentliga området för att större delen av standarden har blivit omvänd ingenjörskonstruerad och kan användas i öppen källkod och annan icke-kommersiell kod.

Dessa meddelanden är textbaserade. Varje meddelande består av en *mening* som börjar med tecknet `$`, följt av två tecken som anger källan till meddelandet (t.ex. GP för det amerikanska GPS-systemet, GN för GLONASS, det ryska GPS-systemet), och tre tecken som anger typen av meddelande. Resten av meddelandet är fält separerade med kommatecken, avslutade med en radbrytning.

Några av de typer av meddelanden som kan tas emot är:

| Typ | Beskrivning |
| ---- | ----------- |
| GGA | GPS Fix Data, inklusive latitud, longitud och höjd för GPS-sensorn, samt antalet satelliter som används för att beräkna denna position. |
| ZDA | Aktuellt datum och tid, inklusive den lokala tidszonen |
| GSV | Detaljer om satelliter i sikte - definierade som de satelliter som GPS-sensorn kan ta emot signaler från |

> 💁 GPS-data inkluderar tidsstämplar, så din IoT-enhet kan få tiden från en GPS-sensor om det behövs, istället för att förlita sig på en NTP-server eller en intern realtidsklocka.

GGA-meddelandet inkluderar den aktuella positionen med formatet `(dd)dmm.mmmm`, tillsammans med ett tecken som anger riktning. `d` i formatet är grader, `m` är minuter, med sekunder som decimaler av minuter. Till exempel skulle 2°17'43" vara 217.716666667 - 2 grader, 17.716666667 minuter.

Riktningstecknet kan vara `N` eller `S` för latitud för att indikera nord eller syd, och `E` eller `W` för longitud för att indikera öst eller väst. Till exempel skulle en latitud på 2°17'43" ha riktningstecknet `N`, -2°17'43" skulle ha riktningstecknet `S`.

Exempel - NMEA-meningen `$GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67`

* Latituddelen är `4738.538654,N`, vilket omvandlas till 47.6423109 i decimalgrader. `4738.538654` är 47.6423109, och riktningen är `N` (nord), så det är en positiv latitud.

* Longituddelen är `12208.341758,W`, vilket omvandlas till -122.1390293 i decimalgrader. `12208.341758` är 122.1390293°, och riktningen är `W` (väst), så det är en negativ longitud.

## Dekodera GPS-sensordata

Istället för att använda rå NMEA-data är det bättre att dekodera den till ett mer användbart format. Det finns flera öppna källkodsbibliotek som du kan använda för att extrahera användbar data från de råa NMEA-meddelandena.

### Uppgift - dekodera GPS-sensordata

Följ den relevanta guiden för att dekodera GPS-sensordata med din IoT-enhet:

* [Arduino - Wio Terminal](wio-terminal-gps-decode.md)
* [Enkortsdator - Raspberry Pi/Virtuell IoT-enhet](single-board-computer-gps-decode.md)

---

## 🚀 Utmaning

Skriv din egen NMEA-dekoder! Istället för att förlita dig på tredjepartsbibliotek för att dekodera NMEA-meningar, kan du skriva din egen dekoder för att extrahera latitud och longitud från NMEA-meningar?

## Efterföreläsningsquiz

[Efterföreläsningsquiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/22)

## Granskning & Självstudier

* Läs mer om geospatiala koordinater på [Geografiskt koordinatsystem på Wikipedia](https://wikipedia.org/wiki/Geographic_coordinate_system).
* Läs om primmeridianer på andra himlakroppar än jorden på [Primmeridian på Wikipedia](https://wikipedia.org/wiki/Prime_meridian#Prime_meridian_on_other_planetary_bodies)
* Undersök de olika GPS-systemen från olika regeringar och politiska unioner som EU, Japan, Ryssland, Indien och USA.

## Uppgift

[Undersök annan GPS-data](assignment.md)

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiserade översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.