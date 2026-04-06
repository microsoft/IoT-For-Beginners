# Hold din plante sikker

![En sketchnote-oversigt over denne lektion](../../../../../translated_images/da/lesson-10.829c86b80b9403bb.webp)

> Sketchnote af [Nitya Narasimhan](https://github.com/nitya). Klik på billedet for en større version.

## Quiz før lektionen

[Quiz før lektionen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/19)

## Introduktion

I de sidste par lektioner har du oprettet en IoT-enhed til jordovervågning og forbundet den til skyen. Men hvad nu hvis hackere, der arbejder for en konkurrerende landmand, fik kontrol over dine IoT-enheder? Hvad hvis de sendte høje jordfugtighedsaflæsninger, så dine planter aldrig blev vandet, eller tændte dit vandingssystem konstant, hvilket dræbte dine planter på grund af overvanding og kostede dig en formue i vand?

I denne lektion vil du lære om at sikre IoT-enheder. Da dette er den sidste lektion i dette projekt, vil du også lære, hvordan du rydder op i dine skyressourcer for at reducere eventuelle omkostninger.

I denne lektion dækker vi:

* [Hvorfor skal du sikre IoT-enheder?](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Kryptografi](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Sikring af dine IoT-enheder](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Generering og brug af et X.509-certifikat](../../../../../2-farm/lessons/6-keep-your-plant-secure)

> 🗑 Dette er den sidste lektion i dette projekt, så efter at have gennemført denne lektion og opgaven, skal du huske at rydde op i dine skyservices. Du skal bruge tjenesterne for at fuldføre opgaven, så sørg for at gøre det først.
>
> Se [guiden til oprydning af dit projekt](../../../clean-up.md), hvis du har brug for instruktioner om, hvordan du gør dette.

## Hvorfor skal du sikre IoT-enheder?

IoT-sikkerhed handler om at sikre, at kun forventede enheder kan oprette forbindelse til din sky-IoT-tjeneste og sende telemetri, og at kun din skytjeneste kan sende kommandoer til dine enheder. IoT-data kan også være personlige, herunder medicinske eller intime data, så hele din applikation skal tage højde for sikkerhed for at forhindre, at disse data lækkes.

Hvis din IoT-applikation ikke er sikker, er der en række risici:

* En falsk enhed kunne sende forkerte data, hvilket får din applikation til at reagere forkert. For eksempel kunne de sende konstant høje jordfugtighedsaflæsninger, hvilket betyder, at dit vandingssystem aldrig tændes, og dine planter dør af mangel på vand.
* Uautoriserede brugere kunne læse data fra IoT-enheder, herunder personlige eller forretningskritiske data.
* Hackere kunne sende kommandoer for at kontrollere en enhed på en måde, der kunne forårsage skade på enheden eller tilsluttet hardware.
* Ved at oprette forbindelse til en IoT-enhed kan hackere bruge dette til at få adgang til yderligere netværk og få adgang til private systemer.
* Ondsindede brugere kunne få adgang til personlige data og bruge dem til afpresning.

Dette er scenarier fra den virkelige verden og sker hele tiden. Nogle eksempler blev givet i tidligere lektioner, men her er nogle flere:

* I 2018 brugte hackere et åbent WiFi-adgangspunkt på en termostat til en fisketank til at få adgang til et casinos netværk og stjæle data. [The Hacker News - Casino Gets Hacked Through Its Internet-Connected Fish Tank Thermometer](https://thehackernews.com/2018/04/iot-hacking-thermometer.html)
* I 2016 lancerede Mirai Botnet et denial-of-service-angreb mod Dyn, en internetudbyder, hvilket tog store dele af internettet ned. Denne botnet brugte malware til at forbinde til IoT-enheder som DVR'er og kameraer, der brugte standardbrugernavne og -adgangskoder, og derfra lancerede angrebet. [The Guardian - DDoS attack that disrupted internet was largest of its kind in history, experts say](https://www.theguardian.com/technology/2016/oct/26/ddos-attack-dyn-mirai-botnet)
* Spiral Toys havde en database med brugere af deres CloudPets-forbundne legetøj offentligt tilgængelig på internettet. [Troy Hunt - Data from connected CloudPets teddy bears leaked and ransomed, exposing kids' voice messages](https://www.troyhunt.com/data-from-connected-cloudpets-teddy-bears-leaked-and-ransomed-exposing-kids-voice-messages/).
* Strava markerede løbere, du løb forbi, og viste deres ruter, hvilket gjorde det muligt for fremmede at se, hvor du bor. [Kim Komndo - Fitness app could lead a stranger right to your home — change this setting](https://www.komando.com/security-privacy/strava-fitness-app-privacy/755349/).

✅ Lav noget research: Søg efter flere eksempler på IoT-hacks og brud på IoT-data, især med personlige genstande som internetforbundne tandbørster eller vægte. Tænk over, hvilken indvirkning disse hacks kunne have på ofrene eller kunderne.

> 💁 Sikkerhed er et enormt emne, og denne lektion vil kun berøre nogle af de grundlæggende ting omkring at forbinde din enhed til skyen. Andre emner, der ikke vil blive dækket, inkluderer overvågning af dataændringer under overførsel, hacking af enheder direkte eller ændringer i enhedskonfigurationer. IoT-hacking er en så stor trussel, at værktøjer som [Azure Defender for IoT](https://azure.microsoft.com/services/azure-defender-for-iot/?WT.mc_id=academic-17441-jabenn) er blevet udviklet. Disse værktøjer ligner de antivirus- og sikkerhedsværktøjer, du måske har på din computer, men er designet til små, lavdrevne IoT-enheder.

## Kryptografi

Når en enhed opretter forbindelse til en IoT-tjeneste, bruger den en ID til at identificere sig selv. Problemet er, at denne ID kan klones - en hacker kunne opsætte en ondsindet enhed, der bruger den samme ID som en rigtig enhed, men sender falske data.

![Både gyldige og ondsindede enheder kunne bruge den samme ID til at sende telemetri](../../../../../translated_images/da/iot-device-and-hacked-device-connecting.e0671675df74d6d9.webp)

Løsningen på dette er at konvertere de data, der sendes, til et krypteret format ved hjælp af en værdi, der kun er kendt af enheden og skyen. Denne proces kaldes *kryptering*, og værdien, der bruges til at kryptere dataene, kaldes en *krypteringsnøgle*.

![Hvis kryptering bruges, accepteres kun krypterede meddelelser, andre afvises](../../../../../translated_images/da/iot-device-and-hacked-device-connecting-encryption.5941aff601fc978f.webp)

Skytjenesten kan derefter konvertere dataene tilbage til et læsbart format ved hjælp af en proces kaldet *dekryptering*, enten ved hjælp af den samme krypteringsnøgle eller en *dekrypteringsnøgle*. Hvis den krypterede meddelelse ikke kan dekrypteres med nøglen, er enheden blevet hacket, og meddelelsen afvises.

Teknikken til at udføre kryptering og dekryptering kaldes *kryptografi*.

### Tidlig kryptografi

De tidligste typer kryptografi var substitutionskrypter, der går 3.500 år tilbage. Substitutionskrypter indebærer at erstatte ét bogstav med et andet. For eksempel indebærer [Caesar-krypteringen](https://wikipedia.org/wiki/Caesar_cipher) at forskyde alfabetet med en defineret mængde, hvor kun afsenderen af den krypterede meddelelse og den tilsigtede modtager ved, hvor mange bogstaver der skal forskydes.

[Vigenère-krypteringen](https://wikipedia.org/wiki/Vigenère_cipher) tog dette videre ved at bruge ord til at kryptere tekst, så hvert bogstav i den oprindelige tekst blev forskudt med en forskellig mængde i stedet for altid at forskyde med det samme antal bogstaver.

Kryptografi blev brugt til en bred vifte af formål, såsom at beskytte en pottemagers glasuropskrift i det gamle Mesopotamien, skrive hemmelige kærlighedsnoter i Indien eller holde gamle egyptiske magiske formularer hemmelige.

### Moderne kryptografi

Moderne kryptografi er meget mere avanceret og gør det sværere at bryde end tidlige metoder. Moderne kryptografi bruger kompliceret matematik til at kryptere data med alt for mange mulige nøgler til, at brute force-angreb er mulige.

Kryptografi bruges på mange forskellige måder til sikker kommunikation. Hvis du læser denne side på GitHub, bemærker du måske, at webadressen starter med *HTTPS*, hvilket betyder, at kommunikationen mellem din browser og GitHubs webservere er krypteret. Hvis nogen kunne læse internettrafikken mellem din browser og GitHub, ville de ikke kunne læse dataene, da de er krypteret. Din computer kan endda kryptere alle data på din harddisk, så hvis nogen stjæler den, kan de ikke læse nogen af dine data uden din adgangskode.

> 🎓 HTTPS står for HyperText Transfer Protocol **Secure**

Desværre er ikke alt sikkert. Nogle enheder har ingen sikkerhed, andre er sikret med lette at bryde nøgler, eller nogle gange bruger alle enheder af samme type den samme nøgle. Der har været beretninger om meget personlige IoT-enheder, der alle har den samme adgangskode til at forbinde til dem via WiFi eller Bluetooth. Hvis du kan forbinde til din egen enhed, kan du forbinde til andres. Når du er forbundet, kan du få adgang til meget private data eller få kontrol over deres enhed.

> 💁 På trods af kompleksiteten i moderne kryptografi og påstandene om, at det kan tage milliarder af år at bryde kryptering, har fremkomsten af kvantecomputing ført til muligheden for at bryde al kendt kryptering på meget kort tid!

### Symmetriske og asymmetriske nøgler

Kryptering findes i to typer - symmetrisk og asymmetrisk.

**Symmetrisk** kryptering bruger den samme nøgle til at kryptere og dekryptere dataene. Både afsender og modtager skal kende den samme nøgle. Dette er den mindst sikre type, da nøglen skal deles på en eller anden måde. For at en afsender kan sende en krypteret meddelelse til en modtager, skal afsenderen først sende modtageren nøglen.

![Symmetrisk nøglekryptering bruger den samme nøgle til at kryptere og dekryptere en meddelelse](../../../../../translated_images/da/send-message-symmetric-key.a2e8ad0d495896ff.webp)

Hvis nøglen bliver stjålet under overførsel, eller hvis afsenderen eller modtageren bliver hacket, og nøglen bliver fundet, kan krypteringen brydes.

![Symmetrisk nøglekryptering er kun sikker, hvis en hacker ikke får fat i nøglen - hvis det sker, kan de opsnappe og dekryptere meddelelsen](../../../../../translated_images/da/send-message-symmetric-key-hacker.e7cb53db1707adfb.webp)

**Asymmetrisk** kryptering bruger 2 nøgler - en krypteringsnøgle og en dekrypteringsnøgle, kendt som et offentligt/privat nøglepar. Den offentlige nøgle bruges til at kryptere meddelelsen, men kan ikke bruges til at dekryptere den, mens den private nøgle bruges til at dekryptere meddelelsen, men kan ikke bruges til at kryptere den.

![Asymmetrisk kryptering bruger en anden nøgle til at kryptere og dekryptere. Krypteringsnøglen sendes til enhver meddelelsesafsender, så de kan kryptere en meddelelse, før den sendes til modtageren, der ejer nøglerne](../../../../../translated_images/da/send-message-asymmetric.7abe327c62615b8c.webp)

Modtageren deler sin offentlige nøgle, og afsenderen bruger denne til at kryptere meddelelsen. Når meddelelsen er sendt, dekrypterer modtageren den med sin private nøgle. Asymmetrisk kryptering er mere sikker, da den private nøgle holdes privat af modtageren og aldrig deles. Alle kan få den offentlige nøgle, da den kun kan bruges til at kryptere meddelelser.

Symmetrisk kryptering er hurtigere end asymmetrisk kryptering, mens asymmetrisk er mere sikker. Nogle systemer bruger begge dele - asymmetrisk kryptering til at kryptere og dele den symmetriske nøgle og derefter den symmetriske nøgle til at kryptere alle data. Dette gør det mere sikkert at dele den symmetriske nøgle mellem afsender og modtager og hurtigere, når data krypteres og dekrypteres.

## Sikring af dine IoT-enheder

IoT-enheder kan sikres ved hjælp af symmetrisk eller asymmetrisk kryptering. Symmetrisk er lettere, men mindre sikker.

### Symmetriske nøgler

Da du opsatte din IoT-enhed til at interagere med IoT Hub, brugte du en forbindelsesstreng. Et eksempel på en forbindelsesstreng er:

```output
HostName=soil-moisture-sensor.azure-devices.net;DeviceId=soil-moisture-sensor;SharedAccessKey=Bhry+ind7kKEIDxubK61RiEHHRTrPl7HUow8cEm/mU0=
```

Denne forbindelsesstreng består af tre dele adskilt af semikolon, hvor hver del er en nøgle og en værdi:

| Nøgle | Værdi | Beskrivelse |
| --- | ----- | ----------- |
| HostName | `soil-moisture-sensor.azure-devices.net` | URL'en til IoT Hub |
| DeviceId | `soil-moisture-sensor` | Enhedens unikke ID |
| SharedAccessKey | `Bhry+ind7kKEIDxubK61RiEHHRTrPl7HUow8cEm/mU0=` | En symmetrisk nøgle kendt af enheden og IoT Hub |

Den sidste del af denne forbindelsesstreng, `SharedAccessKey`, er den symmetriske nøgle, der er kendt af både enheden og IoT Hub. Denne nøgle sendes aldrig fra enheden til skyen eller fra skyen til enheden. I stedet bruges den til at kryptere data, der sendes eller modtages.

✅ Lav et eksperiment. Hvad tror du, der vil ske, hvis du ændrer `SharedAccessKey`-delen af forbindelsesstrengen, når du forbinder din IoT-enhed? Prøv det.

Når enheden først forsøger at oprette forbindelse, sender den en delt adgangssignatur (SAS-token), der består af URL'en til IoT Hub, et tidsstempel for, hvornår adgangssignaturen udløber (normalt 1 dag fra det aktuelle tidspunkt), og en signatur. Denne signatur består af URL'en og udløbstiden krypteret med den delte adgangsnøgle fra forbindelsesstrengen.

IoT Hub dekrypterer denne signatur med den delte adgangsnøgle, og hvis den dekrypterede værdi matcher URL'en og udløbstiden, får enheden lov til at oprette forbindelse. Den verificerer også, at det aktuelle tidspunkt er før udløbstiden for at forhindre en ondsindet enhed i at opsnappe SAS-tokenet fra en rigtig enhed og bruge det.

Dette er en elegant måde at verificere, at afsenderen er den korrekte enhed. Ved at sende nogle kendte data i både en dekrypteret og krypteret form kan serveren verificere enheden ved at sikre, at når den dekrypterer de krypterede data, matcher resultatet den dekrypterede version, der blev sendt. Hvis det matcher, har både afsender og modtager den samme symmetriske krypteringsnøgle.
💁 På grund af udløbstiden skal din IoT-enhed kende den præcise tid, som normalt læses fra en [NTP](https://wikipedia.org/wiki/Network_Time_Protocol)-server. Hvis tiden ikke er korrekt, vil forbindelsen mislykkes.
Efter forbindelsen vil alle data, der sendes til IoT Hub fra enheden, eller til enheden fra IoT Hub, blive krypteret med den delte adgangsnøgle.

✅ Hvad tror du, der vil ske, hvis flere enheder deler den samme forbindelsesstreng?

> 💁 Det er en dårlig sikkerhedspraksis at gemme denne nøgle i koden. Hvis en hacker får adgang til din kildekode, kan de få fat i din nøgle. Det gør det også mere besværligt at udgive kode, da du skal genkompilere med en opdateret nøgle for hver enhed. Det er bedre at indlæse denne nøgle fra en hardware-sikkerhedsmodul - en chip på IoT-enheden, der gemmer krypterede værdier, som kan læses af din kode.
>
> Når man lærer om IoT, er det ofte nemmere at placere nøglen i koden, som du gjorde i en tidligere lektion, men du skal sikre dig, at denne nøgle ikke bliver tjekket ind i offentlig kildekodekontrol.

Enheder har 2 nøgler og 2 tilsvarende forbindelsesstrenge. Dette giver dig mulighed for at rotere nøglerne - det vil sige skifte fra en nøgle til en anden, hvis den første bliver kompromitteret, og derefter gendanne den første nøgle.

### X.509-certifikater

Når du bruger asymmetrisk kryptering med et offentligt/privat nøglepar, skal du give din offentlige nøgle til alle, der ønsker at sende dig data. Problemet er, hvordan kan modtageren af din nøgle være sikker på, at det faktisk er din offentlige nøgle og ikke en anden, der udgiver sig for at være dig? I stedet for at give en nøgle kan du i stedet give din offentlige nøgle i et certifikat, der er blevet verificeret af en betroet tredjepart, kaldet et X.509-certifikat.

X.509-certifikater er digitale dokumenter, der indeholder den offentlige nøgle-del af det offentlige/private nøglepar. De udstedes normalt af en række betroede organisationer kaldet [Certificeringsmyndigheder](https://wikipedia.org/wiki/Certificate_authority) (CAs) og er digitalt underskrevet af CA'en for at indikere, at nøglen er gyldig og kommer fra dig. Du stoler på certifikatet og på, at den offentlige nøgle er fra den, certifikatet siger, det er fra, fordi du stoler på CA'en, ligesom du ville stole på et pas eller kørekort, fordi du stoler på det land, der udsteder det. Certifikater koster penge, så du kan også 'selv-underskrive', det vil sige oprette et certifikat selv, der er underskrevet af dig, til testformål.

> 💁 Du bør aldrig bruge et selv-underskrevet certifikat til en produktionsudgivelse.

Disse certifikater har en række felter i sig, herunder hvem den offentlige nøgle er fra, oplysninger om CA'en, der udstedte det, hvor længe det er gyldigt, og selve den offentlige nøgle. Før du bruger et certifikat, er det god praksis at verificere det ved at kontrollere, at det er underskrevet af den oprindelige CA.

✅ Du kan læse en fuld liste over felterne i certifikatet i [Microsofts vejledning om X.509 Public Key Certificates](https://docs.microsoft.com/azure/iot-hub/tutorial-x509-certificates?WT.mc_id=academic-17441-jabenn#certificate-fields)

Når du bruger X.509-certifikater, vil både afsenderen og modtageren have deres egne offentlige og private nøgler samt begge have X.509-certifikater, der indeholder den offentlige nøgle. De udveksler derefter X.509-certifikater på en eller anden måde, bruger hinandens offentlige nøgler til at kryptere de data, de sender, og deres egne private nøgler til at dekryptere de data, de modtager.

![I stedet for at dele en offentlig nøgle kan du dele et certifikat. Brugeren af certifikatet kan verificere, at det kommer fra dig, ved at kontrollere med den certificeringsmyndighed, der har underskrevet det.](../../../../../translated_images/da/send-message-certificate.9cc576ac1e46b76e.webp)

En stor fordel ved at bruge X.509-certifikater er, at de kan deles mellem enheder. Du kan oprette ét certifikat, uploade det til IoT Hub og bruge det til alle dine enheder. Hver enhed skal derefter kun kende den private nøgle for at dekryptere de meddelelser, den modtager fra IoT Hub.

Certifikatet, der bruges af din enhed til at kryptere meddelelser, den sender til IoT Hub, er udgivet af Microsoft. Det er det samme certifikat, som mange Azure-tjenester bruger, og det er nogle gange indbygget i SDK'erne.

> 💁 Husk, en offentlig nøgle er netop det - offentlig. Azure's offentlige nøgle kan kun bruges til at kryptere data, der sendes til Azure, ikke til at dekryptere dem, så den kan deles overalt, inklusive i kildekode. For eksempel kan du se den i [Azure IoT C SDK kildekoden](https://github.com/Azure/azure-iot-sdk-c/blob/master/certs/certs.c).

✅ Der er mange fagudtryk med X.509-certifikater. Du kan læse definitionerne af nogle af de termer, du kan støde på, i [Den letforståelige guide til X.509-certifikat-jargon](https://techcommunity.microsoft.com/t5/internet-of-things/the-layman-s-guide-to-x-509-certificate-jargon/ba-p/2203540?WT.mc_id=academic-17441-jabenn)

## Generer og brug et X.509-certifikat

Trinene til at generere et X.509-certifikat er:

1. Opret et offentligt/privat nøglepar. En af de mest anvendte algoritmer til at generere et offentligt/privat nøglepar kaldes [Rivest–Shamir–Adleman](https://wikipedia.org/wiki/RSA_(cryptosystem))(RSA).

1. Indsend den offentlige nøgle med tilhørende data til underskrift, enten af en CA eller ved selv-underskrift.

Azure CLI har kommandoer til at oprette en ny enhedsidentitet i IoT Hub og automatisk generere det offentlige/private nøglepar og oprette et selv-underskrevet certifikat.

> 💁 Hvis du vil se trinnene i detaljer i stedet for at bruge Azure CLI, kan du finde det i [Brug af OpenSSL til at oprette selv-underskrevne certifikater i Microsoft IoT Hub-dokumentationen](https://docs.microsoft.com/azure/iot-hub/tutorial-x509-self-sign?WT.mc_id=academic-17441-jabenn)

### Opgave - opret en enhedsidentitet ved hjælp af et X.509-certifikat

1. Kør følgende kommando for at registrere den nye enhedsidentitet og automatisk generere nøgler og certifikater:

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor-x509 \
                                      --am x509_thumbprint \
                                      --output-dir . \
                                      --hub-name <hub_name>
    ```

    Erstat `<hub_name>` med navnet, du brugte til din IoT Hub.

    Dette vil oprette en enhed med et ID af `soil-moisture-sensor-x509` for at skelne fra den enhedsidentitet, du oprettede i den sidste lektion. Denne kommando vil også oprette 2 filer i den aktuelle mappe:

    * `soil-moisture-sensor-x509-key.pem` - denne fil indeholder den private nøgle til enheden.
    * `soil-moisture-sensor-x509-cert.pem` - dette er X.509-certifikatfilen til enheden.

    Hold disse filer sikre! Filen med den private nøgle bør ikke tjekkes ind i offentlig kildekodekontrol.

### Opgave - brug X.509-certifikatet i din enhedskode

Arbejd dig igennem den relevante vejledning for at forbinde din IoT-enhed til skyen ved hjælp af X.509-certifikatet:

* [Arduino - Wio Terminal](wio-terminal-x509.md)
* [Single-board computer - Raspberry Pi/Virtual IoT device](single-board-computer-x509.md)

---

## 🚀 Udfordring

Der er flere måder at oprette, administrere og slette Azure-tjenester som Resource Groups og IoT Hubs. En måde er [Azure Portal](https://portal.azure.com?WT.mc_id=academic-17441-jabenn) - en webbaseret grænseflade, der giver dig en GUI til at administrere dine Azure-tjenester.

Gå til [portal.azure.com](https://portal.azure.com?WT.mc_id=academic-17441-jabenn) og undersøg portalen. Se, om du kan oprette en IoT Hub ved hjælp af portalen, og derefter slette den.

**Tip** - når du opretter tjenester gennem portalen, behøver du ikke at oprette en Resource Group på forhånd, en kan oprettes, når du opretter tjenesten. Sørg for at slette den, når du er færdig!

Du kan finde masser af dokumentation, vejledninger og guides om Azure Portal i [Azure portal-dokumentationen](https://docs.microsoft.com/azure/azure-portal/?WT.mc_id=academic-17441-jabenn).

## Quiz efter lektionen

[Quiz efter lektionen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/20)

## Gennemgang & Selvstudie

* Læs om kryptografiens historie på [Historien om kryptografi-siden på Wikipedia](https://wikipedia.org/wiki/History_of_cryptography).
* Læs om X.509-certifikater på [X.509-siden på Wikipedia](https://wikipedia.org/wiki/X.509).

## Opgave

[Byg en ny IoT-enhed](assignment.md)

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der opstår som følge af brugen af denne oversættelse.