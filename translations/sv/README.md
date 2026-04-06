### Gå med i Azure AI Foundry-gemenskapen

Om du fastnar eller har några frågor om att bygga AI-appar. Gå med i andra elever och erfarna utvecklare i diskussioner om MCP. Det är en stödjande gemenskap där frågor är välkomna och kunskap delas fritt.

Om du har produktfeedback eller fel medan du bygger, besök:

Följ dessa steg för att börja använda dessa resurser:
1. **Forka repositoryt**: Klicka [![GitHub forks](https://img.shields.io/github/forks/microsoft/IoT-For-Beginners.svg?style=social&label=Fork)](https://GitHub.com/microsoft/IoT-For-Beginners/fork)
2. **Klona repositoryt**: `git clone https://github.com/microsoft/IoT-For-Beginners.git`
3. [**Gå med i Microsoft Foundry Discord och möt experter och andra utvecklare**](https://discord.com/invite/ByRwuEEgH4)

### 🌐 Fler språkstöd

#### Stöds via GitHub Action (Automatiserat & Alltid Uppdaterat)

> **Föredrar du att klona lokalt?**
>
> Detta repository innehåller över 50 språköversättningar vilket avsevärt ökar nedladdningsstorleken. För att klona utan översättningar, använd sparse checkout:
>
> **Bash / macOS / Linux:**
> ```bash
> git clone --filter=blob:none --sparse https://github.com/microsoft/IoT-For-Beginners.git
> cd IoT-For-Beginners
> git sparse-checkout set --no-cone '/*' '!translations' '!translated_images'
> ```
>
> **CMD (Windows):**
> ```cmd
> git clone --filter=blob:none --sparse https://github.com/microsoft/IoT-For-Beginners.git
> cd IoT-For-Beginners
> git sparse-checkout set --no-cone "/*" "!translations" "!translated_images"
> ```
>
> Detta ger dig allt du behöver för att slutföra kursen med en mycket snabbare nedladdning.

# IoT för nybörjare – En läroplan

Azure Cloud Advocates på Microsoft är glada att erbjuda en 12-veckors, 24-lektioners läroplan som handlar om grunderna i IoT. Varje lektion inkluderar för- och efter-quiz, skriftliga instruktioner för att slutföra lektionen, en lösning, en uppgift och mer. Vår projektbaserade pedagogik gör det möjligt för dig att lära dig medan du bygger, ett beprövat sätt för nya färdigheter att "fästa".

Projekten täcker resan för mat från gård till bord. Detta inkluderar jordbruk, logistik, tillverkning, detaljhandel och konsument – alla populära industrisegment för IoT-enheter.

> Sketchnote av [Nitya Narasimhan](https://github.com/nitya). Klicka på bilden för en större version.

**Stort tack till våra författare [Jen Fox](https://github.com/jenfoxbot), [Jen Looper](https://github.com/jlooper), [Jim Bennett](https://github.com/jimbobbennett), och vår sketchnote-artist [Nitya Narasimhan](https://github.com/nitya).**

**Tack också till vårt team av [Microsoft Learn Student Ambassadors](https://studentambassadors.microsoft.com?WT.mc_id=academic-17441-jabenn) som har granskat och översatt denna läroplan – [Aditya Garg](https://github.com/AdityaGarg00), [Anurag Sharma](https://github.com/Anurag-0-1-A), [Arpita Das](https://github.com/Arpiiitaaa), [Aryan Jain](https://www.linkedin.com/in/aryan-jain-47a4a1145/), [Bhavesh Suneja](https://github.com/EliteWarrior315), [Faith Hunja](https://faithhunja.github.io/), [Lateefah Bello](https://www.linkedin.com/in/lateefah-bello/), [Manvi Jha](https://github.com/Severus-Matthew), [Mireille Tan](https://www.linkedin.com/in/mireille-tan-a4834819a/), [Mohammad Iftekher (Iftu) Ebne Jalal](https://github.com/Iftu119), [Mohammad Zulfikar](https://github.com/mohzulfikar), [Priyanshu Srivastav](https://www.linkedin.com/in/priyanshu-srivastav-b067241ba), [Thanmai Gowducheruvu](https://github.com/innovation-platform), och [Zina Kamel](https://www.linkedin.com/in/zina-kamel/).**

Möt teamet!

**Gif av** [Mohit Jaisal](https://linkedin.com/in/mohitjaisal)

> 🎥 Klicka på bilden ovan för en video om projektet!

> **Lärare**, vi har [inkluderat några förslag](for-teachers.md) på hur man kan använda denna läroplan. Om du vill skapa egna lektioner har vi också inkluderat en [lektionmall](lesson-template/README.md).

> **[Studenter](https://aka.ms/student-page)**, för att använda denna läroplan självständigt, forka hela repositoriet och slutför övningarna själv, börja med ett för-quiz, sedan läsa lektionen och slutföra resten av aktiviteterna. Försök att skapa projekten genom att förstå lektionerna istället för att kopiera lösningskoden; dock finns koden tillgänglig i /solutions-mapparna i varje projektorienterad lektion. En annan idé är att bilda en studiegrupp med vänner och gå igenom materialet tillsammans. För vidare studier rekommenderar vi [Microsoft Learn](https://docs.microsoft.com/users/jimbobbennett/collections/ke2ehd351jopwr?WT.mc_id=academic-17441-jabenn).

För en videoöversikt av denna kurs, se denna video:

> 🎥 Klicka på bilden ovan för en video om projektet!

## Pedagogik

Vi har valt två pedagogiska principer när vi byggde denna läroplan: att säkerställa att den är projektbaserad och att den inkluderar frekventa quiz. I slutet av serien kommer studenter ha byggt ett system för bevakning och bevattning av växter, en fordonsföljare, en smart fabrikslösning för att spåra och kontrollera mat, samt en röststyrd kökstimern, och lärt sig grunderna i Internet of Things inklusive hur man skriver enhetskod, kopplar upp sig mot molnet, analyserar telemetri och kör AI vid kanten.

Genom att säkerställa att innehållet är kopplat till projekten görs processen mer engagerande för studenter och begreppens retention förstärks.

Dessutom sätter ett lågintensivt quiz innan lektionens start studentens avsikt mot att lära sig ett ämne, medan ett andra quiz efter lektionen säkerställer fortsatt retention. Denna läroplan är designad för att vara flexibel och rolig och kan tas helt eller delvis. Projekten startar smått och blir alltmer komplexa under de 12 veckorna.

Varje projekt baseras på verklig hårdvara som är tillgänglig för studenter och hobbyister. Varje projekt behandlar det specifika ämnesområdet och ger relevant bakgrundskunskap. För att bli en framgångsrik utvecklare hjälper det att förstå domänen där man löser problem; att förse elever med den bakgrundskunskapen låter dem tänka på sina IoT-lösningar och lärdomar i kontexten av den slags verkliga problem de kan bli ombedda att lösa som IoT-utvecklare. Studenter lär sig "varför" till lösningarna de bygger och får en uppskattning av slutanvändaren.

## Hårdvara
Vi har två val av IoT-hårdvara att använda för projekten beroende på personlig preferens, programmeringsspråkskunskap eller preferenser, lärandemål och tillgång. Vi har också tillhandahållit en 'virtuell hårdvaru' version för dem som inte har tillgång till hårdvara eller vill lära sig mer innan de bestämmer sig för ett köp. Du kan läsa mer och hitta en 'inköpslista' på [hårdvarusidan](./hardware.md), inklusive länkar för att köpa kompletta kit från våra vänner på Seeed Studio.

> 💁 Hitta vår [uppförandekod](CODE_OF_CONDUCT.md), [bidragsriktlinjer](CONTRIBUTING.md) och [översättningsriktlinjer](TRANSLATIONS.md). Vi välkomnar din konstruktiva feedback!
>
> 🔧 Problem? Kolla in vår [felsökningsguide](TROUBLESHOOTING.md) för lösningar på vanliga problem.

## Varje lektion inkluderar:

- sketchnote
- valfri kompletterande video
- för-lektions uppvärmningsquiz
- skriftlig lektion
- för projektbaserade lektioner, steg-för-steg-guider för hur man bygger projektet
- kunskapskontroller
- en utmaning
- kompletterande läsning
- uppgift
- [efter-lektionsquiz](https://ff-quizzes.netlify.app/en/)

> **En notering om quiz**: Alla quiz finns i quiz-app-mappen, med totalt 48 quiz med tre frågor vardera. De är länkade från lektionerna men quiz-appen kan köras lokalt eller distribueras till Azure; följ instruktionerna i `quiz-app`-mappen. De lokaliseras gradvis.

## Lektioner

|       |              Projektnamn              |                       Undervisade begrepp                       | Lärandemål                                                                                                                                                 |                                                        Länkad lektion                                                         |
| :---: | :------------------------------------: | :-------------------------------------------------------------: | ----------------------------------------------------------------------------------------------------------------------------------------------------------- | :----------------------------------------------------------------------------------------------------------------------------: |
|  01   | [Komma igång](./1-getting-started/README.md) |                     Introduktion till IoT                      | Lär dig grundprinciperna för IoT och de grundläggande byggstenarna i IoT-lösningar såsom sensorer och molntjänster medan du sätter upp din första IoT-enhet |                      [Introduktion till IoT](./1-getting-started/lessons/1-introduction-to-iot/README.md)                       |
|  02   | [Komma igång](./1-getting-started/README.md) |                   En djupare genomgång av IoT                  | Lär dig mer om komponenterna i ett IoT-system, samt mikrokontrollers och enkla datorer                                                                       |                        [En djupare genomgång av IoT](./1-getting-started/lessons/2-deeper-dive/README.md)                      |
|  03   | [Komma igång](./1-getting-started/README.md) | Interagera med den fysiska världen med sensorer och aktuatorer | Lär dig om sensorer för att samla data från den fysiska världen och aktuatorer för att skicka feedback, samtidigt som du bygger en nattlampa                  | [Interagera med den fysiska världen med sensorer och aktuatorer](./1-getting-started/lessons/3-sensors-and-actuators/README.md) |
|  04   | [Komma igång](./1-getting-started/README.md) |             Anslut din enhet till Internet                      | Lär dig hur du ansluter en IoT-enhet till Internet för att skicka och ta emot meddelanden genom att koppla din nattlampa till en MQTT-broker                 |               [Anslut din enhet till Internet](./1-getting-started/lessons/4-connect-internet/README.md)                       |
|  05   |            [Gård](./2-farm/README.md)           |                    Förutsäga växttillväxt                       | Lär dig hur du förutsäger växttillväxt med hjälp av temperaturdata fångad av en IoT-enhet                                                                    |                          [Förutsäga växttillväxt](./2-farm/lessons/1-predict-plant-growth/README.md)                          |
|  06   |            [Gård](./2-farm/README.md)           |                    Upptäcka jordfuktighet                       | Lär dig hur du upptäcker jordfuktighet och kalibrerar en jordfuktighetssensor                                                                              |                          [Upptäcka jordfuktighet](./2-farm/lessons/2-detect-soil-moisture/README.md)                          |
|  07   |            [Gård](./2-farm/README.md)           |                  Automatiserad bevattning                        | Lär dig hur du automatiserar och tidsbestämmer bevattning med en relä och MQTT                                                                              |                      [Automatiserad bevattning](./2-farm/lessons/3-automated-plant-watering/README.md)                       |
|  08   |            [Gård](./2-farm/README.md)           |               Migrera din växt till molnet                      | Lär dig om molnet och molnhostade IoT-tjänster och hur du ansluter din växt till en av dessa istället för en publik MQTT-broker                              |               [Migrera din växt till molnet](./2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md)                   |
|  09   |            [Gård](./2-farm/README.md)           |         Migrera din applikationslogik till molnet              | Lär dig hur du kan skriva applikationslogik i molnet som svarar på IoT-meddelanden                                                                         |         [Migrera din applikationslogik till molnet](./2-farm/lessons/5-migrate-application-to-the-cloud/README.md)          |
|  10   |            [Gård](./2-farm/README.md)           |                    Håll din växt säker                          | Lär dig om säkerhet med IoT och hur du håller din växt säker med nycklar och certifikat                                                                     |                        [Håll din växt säker](./2-farm/lessons/6-keep-your-plant-secure/README.md)                            |
|  11   |       [Transport](./3-transport/README.md)       |                      Positionsspårning                          | Lär dig om GPS-positionsspårning för IoT-enheter                                                                                                          |                           [Positionsspårning](./3-transport/lessons/1-location-tracking/README.md)                            |
|  12   |       [Transport](./3-transport/README.md)       |                     Lagra positionsdata                         | Lär dig hur du lagrar IoT-data för att kunna visualiseras eller analyseras senare                                                                           |                         [Lagra positionsdata](./3-transport/lessons/2-store-location-data/README.md)                          |
|  13   |       [Transport](./3-transport/README.md)       |                   Visualisera positionsdata                     | Lär dig om att visualisera positionsdata på en karta och hur kartor representerar den verkliga 3D-världen i 2 dimensioner                                    |                     [Visualisera positionsdata](./3-transport/lessons/3-visualize-location-data/README.md)                   |
|  14   |       [Transport](./3-transport/README.md)       |                          Geofence                               | Lär dig om geofence och hur de kan användas för att larma när fordon i leveranskedjan är nära sin destination                                             |                                   [Geofence](./3-transport/lessons/4-geofences/README.md)                                  |
|  15   |   [Tillverkning](./4-manufacturing/README.md)   |               Träna en kvalitetsdetektor för frukt             | Lär dig om att träna en bildklassificerare i molnet för att upptäcka fruktkvalitet                                                                         |                 [Träna en kvalitetsdetektor för frukt](./4-manufacturing/lessons/1-train-fruit-detector/README.md)          |
|  16   |   [Tillverkning](./4-manufacturing/README.md)   |           Kontrollera fruktkvalitet från en IoT-enhet          | Lär dig om hur du använder din kvalitetsdetektor för frukt från en IoT-enhet                                                                               |           [Kontrollera fruktkvalitet från en IoT-enhet](./4-manufacturing/lessons/2-check-fruit-from-device/README.md)       |
|  17   |   [Tillverkning](./4-manufacturing/README.md)   |             Kör din fruktdetektor på kanten                    | Lär dig om att köra din fruktdetektor på en IoT-enhet på kanten                                                                                             |             [Kör din fruktdetektor på kanten](./4-manufacturing/lessons/3-run-fruit-detector-edge/README.md)                 |
|  18   |   [Tillverkning](./4-manufacturing/README.md)   |        Trigga fruktkvalitetsdetektion från en sensor           | Lär dig om att trigga fruktkvalitetsdetektion från en sensor                                                                                               |        [Trigga fruktkvalitetsdetektion från en sensor](./4-manufacturing/lessons/4-trigger-fruit-detector/README.md)        |
|  19   |          [Detaljhandel](./5-retail/README.md)          |                   Träna en lagerdetektor                       | Lär dig hur man använder objektidentifiering för att träna en lagerdetektor för att räkna lager i en butik                                                |                        [Träna en lagerdetektor](./5-retail/lessons/1-train-stock-detector/README.md)                        |
|  20   |          [Detaljhandel](./5-retail/README.md)          |               Kontrollera lager från en IoT-enhet              | Lär dig hur man kontrollerar lager från en IoT-enhet med en modell för objektidentifiering                                                                |                     [Kontrollera lager från en IoT-enhet](./5-retail/lessons/2-check-stock-device/README.md)                |
|  21   |        [Konsument](./6-consumer/README.md)        |             Känna igen tal med en IoT-enhet                    | Lär dig hur du känner igen tal från en IoT-enhet för att bygga en smart timer                                                                             |                  [Känna igen tal med en IoT-enhet](./6-consumer/lessons/1-speech-recognition/README.md)                     |
|  22   |        [Konsument](./6-consumer/README.md)        |                     Förstå språk                               | Lär dig hur man förstår meningar som sägs till en IoT-enhet                                                                                               |                        [Förstå språk](./6-consumer/lessons/2-language-understanding/README.md)                               |
|  23   |        [Konsument](./6-consumer/README.md)        |           Sätt en timer och ge muntlig återkoppling           | Lär dig hur du ställer in en timer på en IoT-enhet och ger muntlig återkoppling om när timern startar och när den slutar                                   |                 [Sätt en timer och ge muntlig återkoppling](./6-consumer/lessons/3-spoken-feedback/README.md)               |
|  24   |        [Konsument](./6-consumer/README.md)        |                 Stöd för flera språk                           | Lär dig hur du stödjer flera språk, både vad gäller tal och svar från din smarta timer                                                                    |                   [Stöd för flera språk](./6-consumer/lessons/4-multiple-language-support/README.md)                        |

## Offline-åtkomst

Du kan köra denna dokumentation offline genom att använda [Docsify](https://docsify.js.org/#/). Forka detta repo, [installera Docsify](https://docsify.js.org/#/quickstart) på din lokala dator, och skriv sedan i rotmappen för detta repo `docsify serve`. Webbplatsen kommer att serveras på port 3000 på din localhost: `localhost:3000`.

## Quiz

Tack till communityn som värd för det interaktiva quizet som testar din kunskap i varje kapitel. Du kan testa dina kunskaper [här](https://ff-quizzes.netlify.app/en/)

### PDF

Du kan generera en PDF av detta innehåll för offline-åtkomst om så behövs. För att göra det, se till att du har [npm installerat](https://docs.npmjs.com/downloading-and-installing-node-js-and-npm) och kör följande kommandon i rotmappen för detta repo:

```sh
npm i
npm run convert
```

### Slides

Det finns presentationsbilder för några av lektionerna i [slides](../../slides)-mappen.


## Andra läroplaner

Vårt team producerar andra läroplaner! Kolla in:

<!-- CO-OP TRANSLATOR OTHER COURSES START -->
### LangChain
[![LangChain4j för nybörjare](https://img.shields.io/badge/LangChain4j%20for%20Beginners-22C55E?style=for-the-badge&&labelColor=E5E7EB&color=0553D6)](https://aka.ms/langchain4j-for-beginners)
[![LangChain.js för nybörjare](https://img.shields.io/badge/LangChain.js%20for%20Beginners-22C55E?style=for-the-badge&labelColor=E5E7EB&color=0553D6)](https://aka.ms/langchainjs-for-beginners?WT.mc_id=m365-94501-dwahlin)
[![LangChain för nybörjare](https://img.shields.io/badge/LangChain%20for%20Beginners-22C55E?style=for-the-badge&labelColor=E5E7EB&color=0553D6)](https://github.com/microsoft/langchain-for-beginners?WT.mc_id=m365-94501-dwahlin)
---

### Azure / Edge / MCP / Agents
[![AZD för nybörjare](https://img.shields.io/badge/AZD%20for%20Beginners-0078D4?style=for-the-badge&labelColor=E5E7EB&color=0078D4)](https://github.com/microsoft/AZD-for-beginners?WT.mc_id=academic-105485-koreyst)
[![Edge AI for Beginners](https://img.shields.io/badge/Edge%20AI%20for%20Beginners-00B8E4?style=for-the-badge&labelColor=E5E7EB&color=00B8E4)](https://github.com/microsoft/edgeai-for-beginners?WT.mc_id=academic-105485-koreyst)
[![MCP for Beginners](https://img.shields.io/badge/MCP%20for%20Beginners-009688?style=for-the-badge&labelColor=E5E7EB&color=009688)](https://github.com/microsoft/mcp-for-beginners?WT.mc_id=academic-105485-koreyst)
[![AI Agents for Beginners](https://img.shields.io/badge/AI%20Agents%20for%20Beginners-00C49A?style=for-the-badge&labelColor=E5E7EB&color=00C49A)](https://github.com/microsoft/ai-agents-for-beginners?WT.mc_id=academic-105485-koreyst)

---
 
### Generativ AI-serie
[![Generative AI for Beginners](https://img.shields.io/badge/Generative%20AI%20for%20Beginners-8B5CF6?style=for-the-badge&labelColor=E5E7EB&color=8B5CF6)](https://github.com/microsoft/generative-ai-for-beginners?WT.mc_id=academic-105485-koreyst)
[![Generative AI (.NET)](https://img.shields.io/badge/Generative%20AI%20(.NET)-9333EA?style=for-the-badge&labelColor=E5E7EB&color=9333EA)](https://github.com/microsoft/Generative-AI-for-beginners-dotnet?WT.mc_id=academic-105485-koreyst)
[![Generative AI (Java)](https://img.shields.io/badge/Generative%20AI%20(Java)-C084FC?style=for-the-badge&labelColor=E5E7EB&color=C084FC)](https://github.com/microsoft/generative-ai-for-beginners-java?WT.mc_id=academic-105485-koreyst)
[![Generative AI (JavaScript)](https://img.shields.io/badge/Generative%20AI%20(JavaScript)-E879F9?style=for-the-badge&labelColor=E5E7EB&color=E879F9)](https://github.com/microsoft/generative-ai-with-javascript?WT.mc_id=academic-105485-koreyst)

---
 
### Kärninlärning
[![ML for Beginners](https://img.shields.io/badge/ML%20for%20Beginners-22C55E?style=for-the-badge&labelColor=E5E7EB&color=22C55E)](https://aka.ms/ml-beginners?WT.mc_id=academic-105485-koreyst)
[![Data Science for Beginners](https://img.shields.io/badge/Data%20Science%20for%20Beginners-84CC16?style=for-the-badge&labelColor=E5E7EB&color=84CC16)](https://aka.ms/datascience-beginners?WT.mc_id=academic-105485-koreyst)
[![AI for Beginners](https://img.shields.io/badge/AI%20for%20Beginners-A3E635?style=for-the-badge&labelColor=E5E7EB&color=A3E635)](https://aka.ms/ai-beginners?WT.mc_id=academic-105485-koreyst)
[![Cybersecurity for Beginners](https://img.shields.io/badge/Cybersecurity%20for%20Beginners-F97316?style=for-the-badge&labelColor=E5E7EB&color=F97316)](https://github.com/microsoft/Security-101?WT.mc_id=academic-96948-sayoung)
[![Web Dev for Beginners](https://img.shields.io/badge/Web%20Dev%20for%20Beginners-EC4899?style=for-the-badge&labelColor=E5E7EB&color=EC4899)](https://aka.ms/webdev-beginners?WT.mc_id=academic-105485-koreyst)
[![IoT for Beginners](https://img.shields.io/badge/IoT%20for%20Beginners-14B8A6?style=for-the-badge&labelColor=E5E7EB&color=14B8A6)](https://aka.ms/iot-beginners?WT.mc_id=academic-105485-koreyst)
[![XR Development for Beginners](https://img.shields.io/badge/XR%20Development%20for%20Beginners-38BDF8?style=for-the-badge&labelColor=E5E7EB&color=38BDF8)](https://github.com/microsoft/xr-development-for-beginners?WT.mc_id=academic-105485-koreyst)

---
 
### Copilot-serie
[![Copilot for AI Paired Programming](https://img.shields.io/badge/Copilot%20for%20AI%20Paired%20Programming-FACC15?style=for-the-badge&labelColor=E5E7EB&color=FACC15)](https://aka.ms/GitHubCopilotAI?WT.mc_id=academic-105485-koreyst)
[![Copilot for C#/.NET](https://img.shields.io/badge/Copilot%20for%20C%23/.NET-FBBF24?style=for-the-badge&labelColor=E5E7EB&color=FBBF24)](https://github.com/microsoft/mastering-github-copilot-for-dotnet-csharp-developers?WT.mc_id=academic-105485-koreyst)
[![Copilot Adventure](https://img.shields.io/badge/Copilot%20Adventure-FDE68A?style=for-the-badge&labelColor=E5E7EB&color=FDE68A)](https://github.com/microsoft/CopilotAdventures?WT.mc_id=academic-105485-koreyst)
<!-- CO-OP TRANSLATOR OTHER COURSES END -->

## Bildangivelser

Du kan hitta alla angivelser för bilderna som används i denna kursplan där det krävs i [Attributions](./attributions.md).

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, vänligen var medveten om att automatiska översättningar kan innehålla fel eller brister. Originaldokumentet på dess ursprungliga språk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för några missförstånd eller feltolkningar som uppstår från användningen av denna översättning.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->