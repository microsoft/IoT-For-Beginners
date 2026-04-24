# En djupare inblick i IoT

![En sketchnote-översikt av denna lektion](../../../../../translated_images/sv/lesson-2.324b0580d620c25e.webp)

> Sketchnote av [Nitya Narasimhan](https://github.com/nitya). Klicka på bilden för en större version.

Denna lektion hölls som en del av [Hello IoT-serien](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) från [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Lektionen bestod av två videor - en timmes lektion och en timmes frågestund där vi fördjupade oss i delar av lektionen och svarade på frågor.

[![Lektion 2: En djupare inblick i IoT](https://img.youtube.com/vi/t0SySWw3z9M/0.jpg)](https://youtu.be/t0SySWw3z9M)

[![Lektion 2: En djupare inblick i IoT - Frågestund](https://img.youtube.com/vi/tTZYf9EST1E/0.jpg)](https://youtu.be/tTZYf9EST1E)

> 🎥 Klicka på bilderna ovan för att titta på videorna

## Förtest inför lektionen

[Förtest inför lektionen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/3)

## Introduktion

Denna lektion går djupare in på några av de koncept som täcktes i den förra lektionen.

I denna lektion kommer vi att gå igenom:

* [Komponenter i en IoT-applikation](../../../../../1-getting-started/lessons/2-deeper-dive)
* [Djupdykning i mikrokontroller](../../../../../1-getting-started/lessons/2-deeper-dive)
* [Djupdykning i enkortsdatorer](../../../../../1-getting-started/lessons/2-deeper-dive)

## Komponenter i en IoT-applikation

De två huvudkomponenterna i en IoT-applikation är *Internet* och *saken*. Låt oss titta närmare på dessa två komponenter.

### Saken

![En Raspberry Pi 4](../../../../../translated_images/sv/raspberry-pi-4.fd4590d308c3d456.webp)

**Saken** i IoT syftar på en enhet som kan interagera med den fysiska världen. Dessa enheter är vanligtvis små, prisvärda datorer som arbetar med låg hastighet och låg strömförbrukning - till exempel enkla mikrokontroller med några kilobyte RAM (jämfört med gigabyte i en PC) som körs på bara några hundra megahertz (jämfört med gigahertz i en PC), men som ibland förbrukar så lite ström att de kan drivas i veckor, månader eller till och med år på batterier.

Dessa enheter interagerar med den fysiska världen, antingen genom att använda sensorer för att samla in data från sin omgivning eller genom att styra utgångar eller aktuatorer för att göra fysiska förändringar. Ett typiskt exempel är en smart termostat - en enhet som har en temperatursensor, ett sätt att ställa in önskad temperatur, som en ratt eller pekskärm, och en anslutning till ett värme- eller kylsystem som kan slås på när den uppmätta temperaturen är utanför det önskade intervallet. Temperatursensorn upptäcker att rummet är för kallt och en aktuator slår på värmen.

![Ett diagram som visar temperatur och en ratt som indata till en IoT-enhet, och styrning av en värmare som utdata](../../../../../translated_images/sv/basic-thermostat.a923217fd1f37e5a.webp)

Det finns ett enormt utbud av olika saker som kan fungera som IoT-enheter, från dedikerad hårdvara som mäter en enda sak till allmänna enheter, till och med din smartphone! En smartphone kan använda sensorer för att upptäcka världen omkring sig och aktuatorer för att interagera med världen - till exempel genom att använda en GPS-sensor för att upptäcka din plats och en högtalare för att ge dig navigationsinstruktioner till en destination.

✅ Tänk på andra system du har omkring dig som läser data från en sensor och använder den för att fatta beslut. Ett exempel skulle kunna vara termostaten i en ugn. Kan du hitta fler?

### Internet

**Internet**-delen av en IoT-applikation består av applikationer som IoT-enheten kan ansluta till för att skicka och ta emot data, samt andra applikationer som kan bearbeta data från IoT-enheten och hjälpa till att fatta beslut om vilka förfrågningar som ska skickas till IoT-enhetens aktuatorer.

En typisk uppsättning skulle kunna vara att ha någon form av molntjänst som IoT-enheten ansluter till. Denna molntjänst hanterar saker som säkerhet, tar emot meddelanden från IoT-enheten och skickar meddelanden tillbaka till enheten. Molntjänsten skulle sedan ansluta till andra applikationer som kan bearbeta eller lagra sensordata, eller använda sensordata tillsammans med data från andra system för att fatta beslut.

Enheter ansluter inte alltid direkt till Internet själva via WiFi eller trådbundna anslutningar. Vissa enheter använder mesh-nätverk för att prata med varandra via teknologier som Bluetooth och ansluter via en hubb-enhet som har en Internetanslutning.

I exemplet med en smart termostat skulle termostaten ansluta via hemmets WiFi till en molntjänst. Den skulle skicka temperaturdata till denna molntjänst, och därifrån skulle den skrivas till en databas av något slag som gör det möjligt för husägaren att kontrollera aktuella och tidigare temperaturer via en telefonapp. En annan tjänst i molnet skulle veta vilken temperatur husägaren vill ha och skicka meddelanden tillbaka till IoT-enheten via molntjänsten för att tala om för värmesystemet att slå på eller av.

![Ett diagram som visar temperatur och en ratt som indata till en IoT-enhet, IoT-enheten med tvåvägskommunikation till molnet, som i sin tur har tvåvägskommunikation till en telefon, och styrning av en värmare som utdata från IoT-enheten](../../../../../translated_images/sv/mobile-controlled-thermostat.4a994010473d8d6a.webp)

En ännu smartare version skulle kunna använda AI i molnet med data från andra sensorer anslutna till andra IoT-enheter, såsom rörelsesensorer som upptäcker vilka rum som används, samt data som väder och till och med din kalender, för att fatta beslut om hur temperaturen ska ställas in på ett smart sätt. Till exempel skulle den kunna stänga av värmen om den läser från din kalender att du är på semester, eller stänga av värmen rum för rum beroende på vilka rum du använder, och lära sig från datan för att bli mer och mer exakt över tid.

![Ett diagram som visar flera temperatursensorer och en ratt som indata till en IoT-enhet, IoT-enheten med tvåvägskommunikation till molnet, som i sin tur har tvåvägskommunikation till en telefon, en kalender och en vädertjänst, och styrning av en värmare som utdata från IoT-enheten](../../../../../translated_images/sv/smarter-thermostat.a75855f15d2d9e63.webp)

✅ Vilka andra data skulle kunna hjälpa till att göra en Internetansluten termostat smartare?

### IoT vid kanten (Edge)

Även om I:et i IoT står för Internet, behöver dessa enheter inte alltid ansluta till Internet. I vissa fall kan enheter ansluta till "edge"-enheter - gateway-enheter som körs på ditt lokala nätverk, vilket innebär att du kan bearbeta data utan att behöva göra en anslutning över Internet. Detta kan vara snabbare när du har mycket data eller en långsam Internetanslutning, det gör det möjligt att köra offline där Internetanslutning inte är möjlig, som på ett fartyg eller i ett katastrofområde vid humanitära insatser, och det gör att du kan hålla data privat. Vissa enheter innehåller processkod som skapats med molnverktyg och kör detta lokalt för att samla in och svara på data utan att använda en Internetanslutning för att fatta beslut.

Ett exempel på detta är en smart hem-enhet som en Apple HomePod, Amazon Alexa eller Google Home, som lyssnar på din röst med hjälp av AI-modeller som tränats i molnet men körs lokalt på enheten. Dessa enheter "vaknar" när ett visst ord eller fras sägs och skickar endast då din röst över Internet för bearbetning. Enheten slutar skicka röstdata vid en lämplig punkt, till exempel när den upptäcker en paus i ditt tal. Allt du säger innan enheten vaknar med väckningsordet och allt du säger efter att enheten har slutat lyssna skickas inte över Internet till leverantören av enheten och förblir därför privat.

✅ Tänk på andra scenarier där integritet är viktigt, så att bearbetning av data skulle vara bättre att göra vid kanten istället för i molnet. Som en ledtråd - tänk på IoT-enheter med kameror eller andra bildbehandlingsenheter.

### IoT-säkerhet

Med varje Internetanslutning är säkerhet en viktig aspekt. Det finns ett gammalt skämt som säger att "S:et i IoT står för säkerhet" - det finns inget "S" i IoT, vilket antyder att det inte är säkert.

IoT-enheter ansluter till en molntjänst och är därför bara så säkra som den molntjänsten är - om din molntjänst tillåter att vilken enhet som helst ansluter kan skadlig data skickas eller virusattacker ske. Detta kan få mycket verkliga konsekvenser eftersom IoT-enheter interagerar och styr andra enheter. Till exempel manipulerade [Stuxnet-masken](https://wikipedia.org/wiki/Stuxnet) ventiler i centrifuger för att skada dem. Hackare har också utnyttjat [bristande säkerhet för att få tillgång till babymonitorer](https://www.npr.org/sections/thetwo-way/2018/06/05/617196788/s-c-mom-says-baby-monitor-was-hacked-experts-say-many-devices-are-vulnerable) och andra övervakningsenheter i hemmet.

> 💁 Ibland körs IoT-enheter och edge-enheter på ett nätverk som är helt isolerat från Internet för att hålla data privat och säker. Detta kallas för [air-gapping](https://wikipedia.org/wiki/Air_gap_(networking)).

## Djupdykning i mikrokontroller

I den förra lektionen introducerade vi mikrokontroller. Låt oss nu titta närmare på dem.

### CPU

CPU:n är "hjärnan" i mikrokontrollern. Det är processorn som kör din kod och kan skicka data till och ta emot data från anslutna enheter. CPU:er kan innehålla en eller flera kärnor - i princip en eller flera CPU:er som kan arbeta tillsammans för att köra din kod.

CPU:er förlitar sig på en klocka som tickar miljontals eller miljarder gånger per sekund. Varje tick, eller cykel, synkroniserar de åtgärder som CPU:n kan utföra. Vid varje tick kan CPU:n utföra en instruktion från ett program, som att hämta data från en extern enhet eller utföra en matematisk beräkning. Denna regelbundna cykel gör det möjligt att slutföra alla åtgärder innan nästa instruktion bearbetas.

Ju snabbare klockcykeln är, desto fler instruktioner kan bearbetas per sekund och desto snabbare är CPU:n. CPU-hastigheter mäts i [Hertz (Hz)](https://wikipedia.org/wiki/Hertz), en standardenhet där 1 Hz betyder en cykel eller klocktick per sekund.

> 🎓 CPU-hastigheter anges ofta i MHz eller GHz. 1 MHz är 1 miljon Hz, 1 GHz är 1 miljard Hz.

> 💁 CPU:er kör program med hjälp av [fetch-decode-execute-cykeln](https://wikipedia.org/wiki/Instruction_cycle). Vid varje klocktick hämtar CPU:n nästa instruktion från minnet, avkodar den och utför den, till exempel genom att använda en aritmetisk logikenhet (ALU) för att addera två tal. Vissa exekveringar tar flera tick att köra, så nästa cykel körs vid nästa tick efter att instruktionen har slutförts.

![Fetch-decode-execute-cykeln som visar hur instruktioner hämtas från programmet i RAM, avkodas och exekveras på en CPU](../../../../../translated_images/sv/fetch-decode-execute.2fd6f150f6280392.webp)

Mikrokontroller har mycket lägre klockhastigheter än stationära eller bärbara datorer, eller till och med de flesta smartphones. Wio Terminal har till exempel en CPU som körs på 120 MHz eller 120 000 000 cykler per sekund.

✅ En genomsnittlig PC eller Mac har en CPU med flera kärnor som körs på flera gigahertz, vilket innebär att klockan tickar miljarder gånger per sekund. Undersök klockhastigheten på din dator och jämför hur många gånger snabbare den är än Wio Terminal.

Varje klockcykel drar ström och genererar värme. Ju snabbare tick, desto mer ström förbrukas och desto mer värme genereras. Datorer har kylflänsar och fläktar för att avleda värme, utan vilka de skulle överhettas och stängas av inom några sekunder. Mikrokontroller har ofta varken kylflänsar eller fläktar eftersom de körs mycket svalare och därför mycket långsammare. Datorer drivs av nätström eller stora batterier som räcker i några timmar, medan mikrokontroller kan drivas i dagar, månader eller till och med år på små batterier. Mikrokontroller kan också ha kärnor som körs i olika hastigheter och växlar till långsammare lågströmskärnor när CPU-belastningen är låg för att minska strömförbrukningen.

> 💁 Vissa datorer och Mac-datorer börjar använda samma blandning av snabba högprestandakärnor och långsammare lågströmskärnor, och växlar för att spara batteri. Till exempel kan M1-chippet i de senaste Apple-datorerna växla mellan 4 prestandakärnor och 4 effektivitetskärnor för att optimera batteritid eller hastighet beroende på vilken uppgift som körs.

✅ Gör lite efterforskning: Läs om CPU:er i [Wikipedia-artikeln om CPU](https://wikipedia.org/wiki/Central_processing_unit)

#### Uppgift

Undersök Wio Terminal.

Om du använder en Wio Terminal för dessa lektioner, försök att hitta CPU:n. Hitta avsnittet *Hardware Overview* på [Wio Terminal-produktens sida](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) för en bild av insidan och försök att hitta CPU:n genom det genomskinliga plastfönstret på baksidan.

### Minne

Mikrokontroller har vanligtvis två typer av minne - programminne och arbetsminne (RAM).

Programminne är icke-flyktigt, vilket innebär att det som skrivs till det finns kvar även när enheten är avstängd. Detta är minnet som lagrar din programkod.

RAM är minnet som används av programmet under körning och innehåller variabler som allokerats av ditt program och data som samlats in från kringutrustning. RAM är flyktigt, vilket innebär att innehållet försvinner när strömmen bryts, vilket i praktiken återställer ditt program.
🎓 Programminnet lagrar din kod och finns kvar även när det inte finns ström.
🎓 RAM används för att köra ditt program och återställs när det inte finns någon ström

Precis som med CPU:n är minnet i en mikrokontroller många gånger mindre än i en PC eller Mac. En typisk PC kan ha 8 Gigabyte (GB) RAM, eller 8 000 000 000 byte, där varje byte har tillräckligt med utrymme för att lagra en bokstav eller ett nummer från 0-255. En mikrokontroller har däremot bara Kilobyte (KB) RAM, där en kilobyte är 1 000 byte. Wio-terminalen som nämns ovan har 192KB RAM, eller 192 000 byte - mer än 40 000 gånger mindre än en genomsnittlig PC!

Diagrammet nedan visar den relativa storleksskillnaden mellan 192KB och 8GB - den lilla pricken i mitten representerar 192KB.

![En jämförelse mellan 192KB och 8GB - mer än 40 000 gånger större](../../../../../translated_images/sv/ram-comparison.6beb73541b42ac6f.webp)

Programlagring är också mindre än i en PC. En typisk PC kan ha en hårddisk på 500GB för programlagring, medan en mikrokontroller kan ha bara kilobyte eller kanske några megabyte (MB) lagring (1MB är 1 000KB, eller 1 000 000 byte). Wio-terminalen har 4MB programlagring.

✅ Gör lite research: Hur mycket RAM och lagring har datorn du använder för att läsa detta? Hur jämförs detta med en mikrokontroller?

### Input/Output

Mikrokontrollers behöver input- och output-anslutningar (I/O) för att läsa data från sensorer och skicka styrsignaler till aktuatorer. De innehåller vanligtvis ett antal allmänna input/output (GPIO)-pinnar. Dessa pinnar kan konfigureras i mjukvaran som input (dvs. de tar emot en signal) eller output (de skickar en signal).

🧠⬅️ Input-pinnar används för att läsa värden från sensorer

🧠➡️ Output-pinnar skickar instruktioner till aktuatorer

✅ Du kommer att lära dig mer om detta i en senare lektion.

#### Uppgift

Undersök Wio-terminalen.

Om du använder en Wio-terminal för dessa lektioner, hitta GPIO-pinnarna. Gå till avsnittet *Pinout diagram* på [Wio Terminal produktens sida](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) för att lära dig vilka pinnar som är vilka. Wio-terminalen levereras med en klistermärke som du kan fästa på baksidan med pinnummer, så sätt dit detta nu om du inte redan har gjort det.

### Fysisk storlek

Mikrokontrollers är vanligtvis små i storlek, med den minsta, en [Freescale Kinetis KL03 MCU som är liten nog att få plats i en golfbolls fördjupning](https://www.edn.com/tiny-arm-cortex-m0-based-mcu-shrinks-package/). Bara CPU:n i en PC kan mäta 40mm x 40mm, och det inkluderar inte kylflänsar och fläktar som behövs för att säkerställa att CPU:n kan köras mer än några sekunder utan att överhettas, vilket är betydligt större än en komplett mikrokontroller. Wio-terminalens utvecklingskit med en mikrokontroller, hölje, skärm och en rad anslutningar och komponenter är inte mycket större än en bar Intel i9 CPU, och betydligt mindre än CPU:n med kylfläns och fläkt!

| Enhet                           | Storlek               |
| ------------------------------- | --------------------- |
| Freescale Kinetis KL03          | 1.6mm x 2mm x 1mm     |
| Wio-terminal                    | 72mm x 57mm x 12mm    |
| Intel i9 CPU, kylfläns och fläkt | 136mm x 145mm x 103mm |

### Ramverk och operativsystem

På grund av deras låga hastighet och minnesstorlek kör mikrokontrollers inte ett operativsystem (OS) i den traditionella desktop-betydelsen. Operativsystemet som får din dator att fungera (Windows, Linux eller macOS) kräver mycket minne och processorkraft för att köra uppgifter som är helt onödiga för en mikrokontroller. Kom ihåg att mikrokontrollers vanligtvis programmeras för att utföra en eller flera mycket specifika uppgifter, till skillnad från en allmän dator som en PC eller Mac som behöver stödja ett användargränssnitt, spela musik eller filmer, tillhandahålla verktyg för att skriva dokument eller kod, spela spel eller surfa på internet.

För att programmera en mikrokontroller utan ett OS behöver du vissa verktyg som gör det möjligt att bygga din kod på ett sätt som mikrokontrollern kan köra, med hjälp av API:er som kan kommunicera med eventuella kringutrustningar. Varje mikrokontroller är olika, så tillverkare stöder normalt standardramverk som gör att du kan följa ett standardiserat "recept" för att bygga din kod och få den att fungera på vilken mikrokontroller som helst som stöder det ramverket.

Du kan programmera mikrokontrollers med ett OS - ofta kallat ett realtidsoperativsystem (RTOS), eftersom dessa är utformade för att hantera att skicka data till och från kringutrustning i realtid. Dessa operativsystem är mycket lätta och erbjuder funktioner som:

* Multitrådning, vilket gör att din kod kan köra mer än ett kodblock samtidigt, antingen på flera kärnor eller genom att turas om på en kärna
* Nätverk för att möjliggöra säker kommunikation över internet
* Grafiska användargränssnittskomponenter (GUI) för att bygga användargränssnitt (UI) på enheter med skärmar.

✅ Läs om några olika RTOS: [Azure RTOS](https://azure.microsoft.com/services/rtos/?WT.mc_id=academic-17441-jabenn), [FreeRTOS](https://www.freertos.org), [Zephyr](https://www.zephyrproject.org)

#### Arduino

![Arduino-logotypen](../../../../../images/arduino-logo.svg)

[Arduino](https://www.arduino.cc) är förmodligen det mest populära mikrokontroller-ramverket, särskilt bland studenter, hobbyister och skapare. Arduino är en öppen källkodsplattform som kombinerar mjukvara och hårdvara. Du kan köpa Arduino-kompatibla kort från Arduino själva eller från andra tillverkare, och sedan koda med Arduino-ramverket.

Arduino-kort programmeras i C eller C++. Att använda C/C++ gör att din kod kan kompileras mycket liten och köras snabbt, något som behövs på en begränsad enhet som en mikrokontroller. Kärnan i en Arduino-applikation kallas en sketch och är C/C++-kod med två funktioner - `setup` och `loop`. När kortet startar kommer Arduino-ramverkskoden att köra `setup`-funktionen en gång, och sedan kommer den att köra `loop`-funktionen om och om igen, kontinuerligt tills strömmen stängs av.

Du skulle skriva din setup-kod i `setup`-funktionen, såsom att ansluta till WiFi och molntjänster eller initiera pinnar för input och output. Din loop-kod skulle sedan innehålla bearbetningskod, såsom att läsa från en sensor och skicka värdet till molnet. Du skulle normalt inkludera en fördröjning i varje loop, till exempel om du bara vill att sensordata ska skickas var tionde sekund skulle du lägga till en fördröjning på 10 sekunder i slutet av loopen så att mikrokontrollern kan sova, spara ström och sedan köra loopen igen när det behövs 10 sekunder senare.

![En Arduino-sketch som kör setup först, och sedan kör loop upprepade gånger](../../../../../translated_images/sv/arduino-sketch.79590cb837ff7a7c.webp)

✅ Denna programarkitektur kallas en *event loop* eller *message loop*. Många applikationer använder detta i bakgrunden och det är standard för de flesta desktop-applikationer som körs på OS som Windows, macOS eller Linux. `loop` lyssnar efter meddelanden från användargränssnittskomponenter som knappar, eller enheter som tangentbordet, och svarar på dem. Du kan läsa mer i denna [artikel om event loop](https://wikipedia.org/wiki/Event_loop).

Arduino tillhandahåller standardbibliotek för att interagera med mikrokontrollers och I/O-pinnar, med olika implementationer under huven för att köras på olika mikrokontrollers. Till exempel kommer funktionen [`delay`](https://www.arduino.cc/reference/en/language/functions/time/delay/) att pausa programmet under en given tidsperiod, funktionen [`digitalRead`](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/) kommer att läsa ett värde av `HIGH` eller `LOW` från den angivna pinnen, oavsett vilket kort koden körs på. Dessa standardbibliotek innebär att Arduino-kod skriven för ett kort kan kompileras om för vilket annat Arduino-kort som helst och kommer att fungera, förutsatt att pinnarna är desamma och korten stöder samma funktioner.

Det finns ett stort ekosystem av tredjeparts Arduino-bibliotek som gör att du kan lägga till extra funktioner till dina Arduino-projekt, såsom att använda sensorer och aktuatorer eller ansluta till moln-IoT-tjänster.

##### Uppgift

Undersök Wio-terminalen.

Om du använder en Wio-terminal för dessa lektioner, läs om koden du skrev i förra lektionen. Hitta funktionerna `setup` och `loop`. Övervaka den seriella utgången för att se att `loop`-funktionen kallas upprepade gånger. Försök att lägga till kod i `setup`-funktionen för att skriva till den seriella porten och observera att denna kod bara kallas en gång varje gång du startar om. Försök att starta om din enhet med strömbrytaren på sidan för att visa att detta kallas varje gång enheten startas om.

## Djupare inblick i enkortsdatorer

I förra lektionen introducerade vi enkortsdatorer. Låt oss nu titta djupare på dem.

### Raspberry Pi

![Raspberry Pi-logotypen](../../../../../translated_images/sv/raspberry-pi-logo.4efaa16605cee054.webp)

[Raspberry Pi Foundation](https://www.raspberrypi.org) är en välgörenhetsorganisation från Storbritannien som grundades 2009 för att främja studier i datavetenskap, särskilt på skolnivå. Som en del av detta uppdrag utvecklade de en enkortsdator, kallad Raspberry Pi. Raspberry Pi finns för närvarande i tre varianter - en fullstor version, den mindre Pi Zero, och en beräkningsmodul som kan byggas in i din slutliga IoT-enhet.

![En Raspberry Pi 4](../../../../../translated_images/sv/raspberry-pi-4.fd4590d308c3d456.webp)

Den senaste iterationen av den fullstora Raspberry Pi är Raspberry Pi 4B. Den har en fyrkärnig (4 kärnor) CPU som körs på 1.5GHz, 2, 4 eller 8GB RAM, gigabit ethernet, WiFi, 2 HDMI-portar som stöder 4k-skärmar, en ljud- och kompositvideoutgångsport, USB-portar (2 USB 2.0, 2 USB 3.0), 40 GPIO-pinnar, en kamerakontakt för en Raspberry Pi-kameramodul och en SD-kortplats. Allt detta på ett kort som är 88mm x 58mm x 19.5mm och drivs av en 3A USB-C strömadapter. Dessa börjar på US$35, mycket billigare än en PC eller Mac.

> 💁 Det finns också en Pi400 allt-i-ett-dator med en Pi4 inbyggd i ett tangentbord.

![En Raspberry Pi Zero](../../../../../translated_images/sv/raspberry-pi-zero.f7a4133e1e7d54bb.webp)

Pi Zero är mycket mindre, med lägre effekt. Den har en enkelkärnig 1GHz CPU, 512MB RAM, WiFi (i Zero W-modellen), en enda HDMI-port, en mikro-USB-port, 40 GPIO-pinnar, en kamerakontakt för en Raspberry Pi-kameramodul och en SD-kortplats. Den mäter 65mm x 30mm x 5mm och drar väldigt lite ström. Zero kostar US$5, med W-versionen med WiFi US$10.

> 🎓 CPU:erna i båda dessa är ARM-processorer, till skillnad från Intel/AMD x86 eller x64-processorer som du hittar i de flesta PC och Mac. Dessa är liknande de CPU:er du hittar i vissa mikrokontrollers, samt nästan alla mobiltelefoner, Microsoft Surface X och de nya Apple Silicon-baserade Apple Mac-datorerna.

Alla varianter av Raspberry Pi kör en version av Debian Linux som kallas Raspberry Pi OS. Detta finns som en lätt version utan skrivbord, vilket är perfekt för "headless"-projekt där du inte behöver en skärm, eller en full version med en fullständig skrivbordsmiljö, med webbläsare, kontorsapplikationer, kodverktyg och spel. Eftersom OS är en version av Debian Linux kan du installera vilken applikation eller verktyg som helst som körs på Debian och är byggd för ARM-processorn i Pi.

#### Uppgift

Undersök Raspberry Pi.

Om du använder en Raspberry Pi för dessa lektioner, läs om de olika hårdvarukomponenterna på kortet.

* Du kan hitta detaljer om processorerna som används på [Raspberry Pi hårdvarudokumentationssidan](https://www.raspberrypi.org/documentation/hardware/raspberrypi/). Läs om processorn som används i den Pi du använder.
* Lokalisera GPIO-pinnarna. Läs mer om dem på [Raspberry Pi GPIO-dokumentationen](https://www.raspberrypi.org/documentation/hardware/raspberrypi/gpio/README.md). Använd [GPIO Pin Usage guide](https://www.raspberrypi.org/documentation/usage/gpio/README.md) för att identifiera de olika pinnarna på din Pi.

### Programmera enkortsdatorer

Enkortsdatorer är fullständiga datorer som kör ett fullständigt OS. Detta innebär att det finns ett brett utbud av programmeringsspråk, ramverk och verktyg du kan använda för att koda dem, till skillnad från mikrokontrollers som är beroende av stöd för kortet i ramverk som Arduino. De flesta programmeringsspråk har bibliotek som kan komma åt GPIO-pinnarna för att skicka och ta emot data från sensorer och aktuatorer.

✅ Vilka programmeringsspråk är du bekant med? Stöds de på Linux?

Det vanligaste programmeringsspråket för att bygga IoT-applikationer på en Raspberry Pi är Python. Det finns ett stort ekosystem av hårdvara designad för Pi, och nästan alla dessa inkluderar den relevanta koden som behövs för att använda dem som Python-bibliotek. Några av dessa ekosystem är baserade på "hattar" - så kallade eftersom de sitter ovanpå Pi som en hatt och ansluter med en stor kontakt till de 40 GPIO-pinnarna. Dessa hattar ger ytterligare funktioner, såsom skärmar, sensorer, fjärrstyrda bilar eller adaptrar för att ansluta sensorer med standardiserade kablar.
### Användning av enkortsdatorer i professionella IoT-implementeringar

Enkortsdatorer används för professionella IoT-implementeringar, inte bara som utvecklingskit. De kan erbjuda ett kraftfullt sätt att styra hårdvara och utföra komplexa uppgifter, såsom att köra maskininlärningsmodeller. Till exempel finns det en [Raspberry Pi 4 Compute Module](https://www.raspberrypi.org/blog/raspberry-pi-compute-module-4/) som ger all kraft från en Raspberry Pi 4 men i ett kompakt och billigare format utan de flesta portar, designad för att installeras i anpassad hårdvara.

---

## 🚀 Utmaning

Utmaningen i den senaste lektionen var att lista så många IoT-enheter som möjligt som finns i ditt hem, skola eller arbetsplats. För varje enhet i denna lista, tror du att de är byggda kring mikrokontroller eller enkortsdatorer, eller kanske en blandning av båda?

## Quiz efter föreläsningen

[Quiz efter föreläsningen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/4)

## Granskning & Självstudier

* Läs [Arduinos introduktionsguide](https://www.arduino.cc/en/Guide/Introduction) för att förstå mer om Arduino-plattformen.
* Läs [introduktionen till Raspberry Pi 4](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/) för att lära dig mer om Raspberry Pi.
* Lär dig mer om några av begreppen och akronymerna i [artikeln "What the FAQ are CPUs, MPUs, MCUs, and GPUs" i Electrical Engineering Journal](https://www.eejournal.com/article/what-the-faq-are-cpus-mpus-mcus-and-gpus/).

✅ Använd dessa guider, tillsammans med kostnaderna som visas genom att följa länkarna i [hårdvaruguiden](../../../hardware.md) för att bestämma vilken hårdvaruplattform du vill använda, eller om du hellre vill använda en virtuell enhet.

## Uppgift

[Jämför och kontrastera mikrokontroller och enkortsdatorer](assignment.md)

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiserade översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess ursprungliga språk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.