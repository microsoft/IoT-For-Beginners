# Introduktion till IoT

![En sketchnote-översikt av denna lektion](../../../../../translated_images/sv/lesson-1.2606670fa61ee904.webp)

> Sketchnote av [Nitya Narasimhan](https://github.com/nitya). Klicka på bilden för en större version.

Denna lektion hölls som en del av [Hello IoT-serien](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) från [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Lektionen presenterades i två videor - en 1-timmes lektion och en 1-timmes frågestund som gick djupare in i delar av lektionen och besvarade frågor.

[![Lektion 1: Introduktion till IoT](https://img.youtube.com/vi/bVFfcYh6UBw/0.jpg)](https://youtu.be/bVFfcYh6UBw)

[![Lektion 1: Introduktion till IoT - Frågestund](https://img.youtube.com/vi/YI772q5v3yI/0.jpg)](https://youtu.be/YI772q5v3yI)

> 🎥 Klicka på bilderna ovan för att titta på videorna

## Förkunskapstest

[Förkunskapstest](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/1)

## Introduktion

Denna lektion täcker några av de grundläggande ämnena kring Internet of Things och hjälper dig att komma igång med att konfigurera din hårdvara.

I denna lektion kommer vi att gå igenom:

* [Vad är 'Internet of Things'?](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [IoT-enheter](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Konfigurera din enhet](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Användningsområden för IoT](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Exempel på IoT-enheter du kan ha runt omkring dig](../../../../../1-getting-started/lessons/1-introduction-to-iot)

## Vad är 'Internet of Things'?

Termen 'Internet of Things' myntades av [Kevin Ashton](https://wikipedia.org/wiki/Kevin_Ashton) 1999 för att beskriva kopplingen mellan Internet och den fysiska världen via sensorer. Sedan dess har termen använts för att beskriva alla enheter som interagerar med den fysiska världen, antingen genom att samla in data från sensorer eller genom att tillhandahålla verkliga interaktioner via aktuatorer (enheter som gör något, som att slå på en strömbrytare eller tända en LED), vanligtvis anslutna till andra enheter eller Internet.

> **Sensorer** samlar in information från världen, som att mäta hastighet, temperatur eller plats.
>
> **Aktuatorer** omvandlar elektriska signaler till verkliga interaktioner, som att aktivera en strömbrytare, tända lampor, skapa ljud eller skicka styrsignaler till annan hårdvara, till exempel för att slå på ett eluttag.

IoT som teknikområde handlar om mer än bara enheter - det inkluderar molnbaserade tjänster som kan bearbeta sensordata eller skicka förfrågningar till aktuatorer anslutna till IoT-enheter. Det inkluderar också enheter som inte har eller inte behöver Internetanslutning, ofta kallade edge-enheter. Dessa är enheter som kan bearbeta och svara på sensordata själva, vanligtvis med hjälp av AI-modeller som tränats i molnet.

IoT är ett snabbt växande teknikområde. Det uppskattas att det i slutet av 2020 fanns 30 miljarder IoT-enheter som var distribuerade och anslutna till Internet. I framtiden förväntas det att IoT-enheter år 2025 kommer att samla in nästan 80 zettabyte data, eller 80 biljoner gigabyte. Det är enorma mängder data!

![En graf som visar aktiva IoT-enheter över tid, med en uppåtgående trend från under 5 miljarder 2015 till över 30 miljarder 2025](../../../../../images/connected-iot-devices.svg)

✅ Gör lite efterforskning: Hur mycket av den data som genereras av IoT-enheter används faktiskt, och hur mycket går till spillo? Varför ignoreras så mycket data?

Denna data är nyckeln till IoT:s framgång. För att bli en framgångsrik IoT-utvecklare behöver du förstå vilken data du behöver samla in, hur du samlar in den, hur du fattar beslut baserat på den och hur du använder dessa beslut för att interagera med den fysiska världen om det behövs.

## IoT-enheter

**T** i IoT står för **Things** - enheter som interagerar med den fysiska världen runt dem, antingen genom att samla in data från sensorer eller genom att tillhandahålla verkliga interaktioner via aktuatorer.

Enheter för produktion eller kommersiellt bruk, som konsumenters fitnessarmband eller industriella maskinkontroller, är vanligtvis specialtillverkade. De använder skräddarsydda kretskort, kanske till och med specialdesignade processorer, för att möta behoven för en specifik uppgift, oavsett om det handlar om att vara tillräckligt små för att passa på en handled eller robusta nog för att fungera i en högtemperatur-, högstress- eller högvibrationsmiljö i en fabrik.

Som utvecklare som antingen lär sig om IoT eller skapar en prototyp av en enhet behöver du börja med ett utvecklingskit. Dessa är allmänna IoT-enheter designade för utvecklare att använda, ofta med funktioner som du inte skulle ha på en produktionsenhet, som en uppsättning externa stift för att ansluta sensorer eller aktuatorer, hårdvara för att stödja felsökning eller ytterligare resurser som skulle öka kostnaden i en stor tillverkningsserie.

Dessa utvecklingskit faller vanligtvis in i två kategorier - mikrokontroller och enkortsdatorer. Dessa introduceras här, och vi kommer att gå in på mer detaljer i nästa lektion.

> 💁 Din telefon kan också betraktas som en allmän IoT-enhet, med inbyggda sensorer och aktuatorer, där olika appar använder sensorer och aktuatorer på olika sätt med olika molntjänster. Du kan till och med hitta några IoT-guider som använder en telefonapp som en IoT-enhet.

### Mikrokontroller

En mikrokontroller (även kallad MCU, kort för microcontroller unit) är en liten dator som består av:

🧠 En eller flera centralenheter (CPU) - "hjärnan" i mikrokontrollern som kör ditt program

💾 Minne (RAM och programminne) - där ditt program, data och variabler lagras

🔌 Programmerbara in-/utgångar (I/O) - för att kommunicera med externa enheter (anslutna enheter) som sensorer och aktuatorer

Mikrokontroller är vanligtvis billiga datorenheter, med genomsnittliga priser för de som används i specialtillverkad hårdvara som sjunker till cirka 0,50 USD, och vissa enheter är så billiga som 0,03 USD. Utvecklingskit kan börja så lågt som 4 USD, med kostnader som ökar när fler funktioner läggs till. [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html), ett mikrokontrollerutvecklingskit från [Seeed studios](https://www.seeedstudio.com) som har sensorer, aktuatorer, WiFi och en skärm, kostar cirka 30 USD.

![En Wio Terminal](../../../../../translated_images/sv/wio-terminal.b8299ee16587db9a.webp)

> 💁 När du söker på Internet efter mikrokontroller, var försiktig med att söka efter termen **MCU**, eftersom detta kan ge många resultat för Marvel Cinematic Universe istället för mikrokontroller.

Mikrokontroller är designade för att programmeras för att utföra ett begränsat antal mycket specifika uppgifter, snarare än att vara allmänna datorer som PC eller Mac. Förutom i mycket specifika scenarier kan du inte ansluta en skärm, tangentbord och mus och använda dem för allmänna uppgifter.

Utvecklingskit för mikrokontroller har vanligtvis ytterligare sensorer och aktuatorer inbyggda. De flesta kort har en eller flera programmerbara lysdioder (LED) samt andra enheter som standardkontakter för att lägga till fler sensorer eller aktuatorer via olika tillverkares ekosystem eller inbyggda sensorer (vanligtvis de mest populära, som temperatursensorer). Vissa mikrokontroller har inbyggd trådlös anslutning som Bluetooth eller WiFi, eller har ytterligare mikrokontroller på kortet för att lägga till denna anslutning.

> 💁 Mikrokontroller programmeras vanligtvis i C/C++.

### Enkortsdatorer

En enkortsdator är en liten datorenhet som har alla element av en komplett dator på ett enda litet kort. Dessa enheter har specifikationer som liknar en stationär eller bärbar dator, kör ett fullständigt operativsystem, men är små, använder mindre ström och är betydligt billigare.

![En Raspberry Pi 4](../../../../../translated_images/sv/raspberry-pi-4.fd4590d308c3d456.webp)

Raspberry Pi är en av de mest populära enkortsdatorerna.

Liksom en mikrokontroller har enkortsdatorer en CPU, minne och in-/utgångsstift, men de har ytterligare funktioner som ett grafikkort för att ansluta skärmar, ljudutgångar och USB-portar för att ansluta tangentbord, möss och andra standard-USB-enheter som webbkameror eller extern lagring. Program lagras på SD-kort eller hårddiskar tillsammans med ett operativsystem, istället för ett minneschip inbyggt i kortet.

> 🎓 Du kan tänka på en enkortsdator som en mindre, billigare version av den PC eller Mac du läser detta på, med tillägg av GPIO (general-purpose input/output)-stift för att interagera med sensorer och aktuatorer.

Enkortsdatorer är fullfjädrade datorer och kan programmeras i vilket språk som helst. IoT-enheter programmeras vanligtvis i Python.

### Hårdvaruval för resten av lektionerna

Alla efterföljande lektioner inkluderar uppgifter som använder en IoT-enhet för att interagera med den fysiska världen och kommunicera med molnet. Varje lektion stöder tre enhetsval - Arduino (med en Seeed Studios Wio Terminal) eller en enkortsdator, antingen en fysisk enhet (en Raspberry Pi 4) eller en virtuell enkortsdator som körs på din PC eller Mac.

Du kan läsa om den hårdvara som behövs för att slutföra alla uppgifter i [hårdvaruguiden](../../../hardware.md).

> 💁 Du behöver inte köpa någon IoT-hårdvara för att slutföra uppgifterna, du kan göra allt med en virtuell enkortsdator.

Vilken hårdvara du väljer är upp till dig - det beror på vad du har tillgängligt hemma eller i skolan och vilket programmeringsspråk du kan eller planerar att lära dig. Båda hårdvaruvarianterna kommer att använda samma sensorekosystem, så om du börjar med en väg kan du byta till den andra utan att behöva byta ut det mesta av utrustningen. Den virtuella enkortsdatorn kommer att motsvara att lära sig på en Raspberry Pi, med det mesta av koden överförbar till Pi om du så småningom skaffar en enhet och sensorer.

### Arduino-utvecklingskit

Om du är intresserad av att lära dig mikrokontrollerutveckling kan du slutföra uppgifterna med en Arduino-enhet. Du behöver en grundläggande förståelse för C/C++-programmering, eftersom lektionerna endast kommer att lära ut kod som är relevant för Arduino-ramverket, sensorerna och aktuatorerna som används samt de bibliotek som interagerar med molnet.

Uppgifterna kommer att använda [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn) med [PlatformIO-tillägget för mikrokontrollerutveckling](https://platformio.org). Du kan också använda Arduino IDE om du är erfaren med detta verktyg, men instruktioner kommer inte att tillhandahållas.

### Enkortsdator-utvecklingskit

Om du är intresserad av att lära dig IoT-utveckling med enkortsdatorer kan du slutföra uppgifterna med en Raspberry Pi eller en virtuell enhet som körs på din PC eller Mac.

Du behöver en grundläggande förståelse för Python-programmering, eftersom lektionerna endast kommer att lära ut kod som är relevant för sensorerna och aktuatorerna som används samt de bibliotek som interagerar med molnet.

> 💁 Om du vill lära dig att programmera i Python, kolla in följande två videoserier:
>
> * [Python för nybörjare](https://channel9.msdn.com/Series/Intro-to-Python-Development?WT.mc_id=academic-17441-jabenn)
> * [Mer Python för nybörjare](https://channel9.msdn.com/Series/More-Python-for-Beginners?WT.mc_id=academic-7372-jabenn)

Uppgifterna kommer att använda [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn).

Om du använder en Raspberry Pi kan du antingen köra din Pi med den fullständiga skrivbordsversionen av Raspberry Pi OS och göra all kodning direkt på Pi med [Raspberry Pi OS-versionen av VS Code](https://code.visualstudio.com/docs/setup/raspberry-pi?WT.mc_id=academic-17441-jabenn), eller köra din Pi som en headless-enhet och koda från din PC eller Mac med VS Code och [Remote SSH-tillägget](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) som låter dig ansluta till din Pi och redigera, felsöka och köra kod som om du kodade direkt på den.

Om du använder det virtuella enhetsalternativet kommer du att koda direkt på din dator. Istället för att använda sensorer och aktuatorer kommer du att använda ett verktyg för att simulera denna hårdvara, tillhandahålla sensordata som du kan definiera och visa resultaten av aktuatorer på skärmen.

## Konfigurera din enhet

Innan du kan börja programmera din IoT-enhet behöver du göra en liten mängd konfiguration. Följ de relevanta instruktionerna nedan beroende på vilken enhet du kommer att använda.
💁 Om du ännu inte har en enhet, hänvisa till [hårdvaruguiden](../../../hardware.md) för att hjälpa dig att bestämma vilken enhet du ska använda och vilken extra hårdvara du behöver köpa. Du behöver inte köpa någon hårdvara, eftersom alla projekt kan köras på virtuell hårdvara.
Dessa instruktioner inkluderar länkar till tredjepartswebbplatser från skaparna av den hårdvara eller de verktyg du kommer att använda. Detta är för att säkerställa att du alltid använder de mest uppdaterade instruktionerna för de olika verktygen och hårdvaran.

Gå igenom den relevanta guiden för att konfigurera din enhet och slutföra ett "Hello World"-projekt. Detta kommer att vara det första steget i att skapa en IoT-nattlampa under de fyra lektionerna i denna introduktionsdel.

* [Arduino - Wio Terminal](wio-terminal.md)
* [Enkortsdator - Raspberry Pi](pi.md)
* [Enkortsdator - Virtuell enhet](virtual-device.md)

✅ Du kommer att använda VS Code för både Arduino och enkortsdatorer. Om du inte har använt detta tidigare, läs mer om det på [VS Code-sidan](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn)

## Tillämpningar av IoT

IoT täcker ett enormt antal användningsområden, inom några breda grupper:

* Konsument-IoT
* Kommersiell IoT
* Industriell IoT
* Infrastruktur-IoT

✅ Gör lite research: För varje område som beskrivs nedan, hitta ett konkret exempel som inte nämns i texten.

### Konsument-IoT

Konsument-IoT avser IoT-enheter som konsumenter köper och använder i hemmet. Vissa av dessa enheter är otroligt användbara, såsom smarta högtalare, smarta värmesystem och robotdammsugare. Andra är mer tveksamma i sin användbarhet, såsom röststyrda kranar som gör att du inte kan stänga av dem eftersom röststyrningen inte kan höra dig över ljudet av rinnande vatten.

Konsument-IoT-enheter ger människor möjlighet att göra mer i sin omgivning, särskilt de 1 miljard människor som har en funktionsnedsättning. Robotdammsugare kan ge rena golv till personer med rörelsehinder som inte kan dammsuga själva, röststyrda ugnar gör det möjligt för personer med begränsad syn eller motorisk kontroll att värma sina ugnar med bara sin röst, hälsomonitorer gör det möjligt för patienter att övervaka kroniska tillstånd själva med mer regelbundna och detaljerade uppdateringar om deras hälsa. Dessa enheter blir så vanliga att även små barn använder dem som en del av sin vardag, till exempel elever som studerar virtuellt under COVID-pandemin och ställer in timers på smarta hem-enheter för att hålla koll på sitt skolarbete eller alarm för att påminna dem om kommande lektioner.

✅ Vilka konsument-IoT-enheter har du på dig eller i ditt hem?

### Kommersiell IoT

Kommersiell IoT omfattar användningen av IoT på arbetsplatsen. På ett kontor kan det finnas närvarosensorer och rörelsedetektorer för att hantera belysning och värme, så att ljus och värme bara är på när det behövs, vilket minskar kostnader och koldioxidutsläpp. På en fabrik kan IoT-enheter övervaka säkerhetsrisker, såsom arbetare som inte bär hjälm eller ljudnivåer som har nått farliga nivåer. Inom detaljhandeln kan IoT-enheter mäta temperaturen i kylförvaring och varna butikschefen om en kyl eller frys är utanför det rekommenderade temperaturområdet, eller de kan övervaka varor på hyllor för att dirigera anställda att fylla på produkter som har sålts. Transportindustrin förlitar sig alltmer på IoT för att övervaka fordonspositioner, spåra körsträckor för vägavgifter, övervaka förarens arbetstider och pauser, eller meddela personal när ett fordon närmar sig en depå för att förbereda lastning eller lossning.

✅ Vilka kommersiella IoT-enheter har du i din skola eller på din arbetsplats?

### Industriell IoT (IIoT)

Industriell IoT, eller IIoT, är användningen av IoT-enheter för att kontrollera och hantera maskiner i stor skala. Detta täcker ett brett spektrum av användningsområden, från fabriker till digitalt jordbruk.

Fabriker använder IoT-enheter på många olika sätt. Maskiner kan övervakas med flera sensorer för att spåra saker som temperatur, vibrationer och rotationshastighet. Dessa data kan sedan övervakas för att stoppa maskinen om den går utanför vissa toleranser - till exempel om den blir för varm och stängs av. Dessa data kan också samlas in och analyseras över tid för att utföra prediktivt underhåll, där AI-modeller analyserar data som leder fram till ett fel och använder det för att förutsäga andra fel innan de inträffar.

Digitalt jordbruk är viktigt för att planeten ska kunna föda den växande befolkningen, särskilt för de 2 miljarder människor i 500 miljoner hushåll som lever på [självförsörjningsjordbruk](https://wikipedia.org/wiki/Subsistence_agriculture). Digitalt jordbruk kan sträcka sig från några enkla sensorer för några dollar till massiva kommersiella installationer. En bonde kan börja med att övervaka temperaturer och använda [växtgraddagar](https://wikipedia.org/wiki/Growing_degree-day) för att förutsäga när en gröda kommer att vara redo för skörd. De kan koppla jordfuktighetsövervakning till automatiska bevattningssystem för att ge sina växter så mycket vatten som behövs, men inte mer, för att säkerställa att deras grödor inte torkar ut utan att slösa vatten. Bönder tar det till och med längre och använder drönare, satellitdata och AI för att övervaka grödtillväxt, sjukdomar och jordkvalitet över stora områden av jordbruksmark.

✅ Vilka andra IoT-enheter skulle kunna hjälpa bönder?

### Infrastruktur-IoT

Infrastruktur-IoT handlar om att övervaka och kontrollera den lokala och globala infrastrukturen som människor använder varje dag.

[Smarta städer](https://wikipedia.org/wiki/Smart_city) är urbana områden som använder IoT-enheter för att samla in data om staden och använda den för att förbättra hur staden fungerar. Dessa städer drivs vanligtvis genom samarbeten mellan lokala myndigheter, akademiska institutioner och lokala företag, och spårar och hanterar allt från transport till parkering och föroreningar. Till exempel, i Köpenhamn, Danmark, är luftföroreningar viktiga för de lokala invånarna, så det mäts och data används för att ge information om de renaste cykel- och joggingrutterna.

[Smarta elnät](https://wikipedia.org/wiki/Smart_grid) möjliggör bättre analys av energibehov genom att samla in användningsdata på nivån av enskilda hem. Dessa data kan vägleda beslut på nationell nivå, inklusive var nya kraftverk ska byggas, och på personlig nivå genom att ge användare insikter om hur mycket energi de använder, när de använder den, och till och med förslag på hur de kan minska kostnader, såsom att ladda elbilar på natten.

✅ Om du kunde lägga till IoT-enheter för att mäta något där du bor, vad skulle det vara?

## Exempel på IoT-enheter du kanske har runt dig

Du skulle bli förvånad över hur många IoT-enheter du har runt dig. Jag skriver detta hemifrån och jag har följande enheter anslutna till Internet med smarta funktioner som appkontroll, röststyrning eller möjligheten att skicka data till mig via min telefon:

* Flera smarta högtalare
* Kylskåp, diskmaskin, ugn och mikrovågsugn
* Elektricitetsmonitor för solpaneler
* Smarta pluggar
* Videodörrklocka och säkerhetskameror
* Smart termostat med flera smarta rumssensorer
* Garageportsöppnare
* Hemunderhållningssystem och röststyrda TV-apparater
* Lampor
* Fitness- och hälsomonitorer

Alla dessa typer av enheter har sensorer och/eller ställdon och pratar med Internet. Jag kan se från min telefon om min garageport är öppen och be min smarta högtalare att stänga den åt mig. Jag kan till och med ställa in en timer så att om den fortfarande är öppen på natten, stängs den automatiskt. När min dörrklocka ringer kan jag se från min telefon vem som är där, var jag än är i världen, och prata med dem via en högtalare och mikrofon inbyggd i dörrklockan. Jag kan övervaka mitt blodsocker, hjärtfrekvens och sömnmönster, och leta efter mönster i data för att förbättra min hälsa. Jag kan kontrollera mina lampor via molnet och sitta i mörkret när min Internetanslutning går ner.

---

## 🚀 Utmaning

Lista så många IoT-enheter du kan som finns i ditt hem, din skola eller din arbetsplats - det kan finnas fler än du tror!

## Efterföreläsningsquiz

[Efterföreläsningsquiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/2)

## Granskning & Självstudier

Läs om fördelarna och misslyckandena med konsument-IoT-projekt. Kolla nyhetssajter för artiklar om när det har gått fel, såsom integritetsproblem, hårdvaruproblem eller problem orsakade av bristande anslutning.

Några exempel:

* Kolla in Twitter-kontot **[Internet of Sh*t](https://twitter.com/internetofshit)** *(varning för svordomar)* för några bra exempel på misslyckanden med konsument-IoT.
* [c|net - Min Apple Watch räddade mitt liv: 5 personer delar sina berättelser](https://www.cnet.com/news/apple-watch-lifesaving-health-features-read-5-peoples-stories/)
* [c|net - ADT-tekniker erkänner sig skyldig till att ha spionerat på kunders kameraflöden i flera år](https://www.cnet.com/news/adt-home-security-technician-pleads-guilty-to-spying-on-customer-camera-feeds-for-years/) *(varning - icke-samtyckande voyeurism)*

## Uppgift

[Undersök ett IoT-projekt](assignment.md)

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiserade översättningar kan innehålla fel eller brister. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.