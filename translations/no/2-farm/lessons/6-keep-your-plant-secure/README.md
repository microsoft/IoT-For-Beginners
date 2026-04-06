# Hold planten din trygg

![En sketchnote-oversikt over denne leksjonen](../../../../../translated_images/no/lesson-10.829c86b80b9403bb.webp)

> Sketchnote av [Nitya Narasimhan](https://github.com/nitya). Klikk på bildet for en større versjon.

## Quiz før leksjonen

[Quiz før leksjonen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/19)

## Introduksjon

I de siste leksjonene har du laget en IoT-enhet for jordovervåking og koblet den til skyen. Men hva om hackere som jobber for en rivaliserende bonde klarte å ta kontroll over IoT-enhetene dine? Hva om de sendte høye fuktighetsmålinger slik at plantene dine aldri ble vannet, eller skrudde på vanningssystemet ditt hele tiden, noe som ville drepe plantene dine av overvanning og koste deg en liten formue i vann?

I denne leksjonen vil du lære om å sikre IoT-enheter. Siden dette er den siste leksjonen for dette prosjektet, vil du også lære hvordan du rydder opp i skyressursene dine for å redusere potensielle kostnader.

I denne leksjonen dekker vi:

* [Hvorfor trenger du å sikre IoT-enheter?](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Kryptografi](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Sikre IoT-enhetene dine](../../../../../2-farm/lessons/6-keep-your-plant-secure)
* [Generere og bruke et X.509-sertifikat](../../../../../2-farm/lessons/6-keep-your-plant-secure)

> 🗑 Dette er den siste leksjonen i dette prosjektet, så etter å ha fullført denne leksjonen og oppgaven, ikke glem å rydde opp i skytjenestene dine. Du vil trenge tjenestene for å fullføre oppgaven, så sørg for å gjøre det først.
>
> Se [guiden for å rydde opp i prosjektet ditt](../../../clean-up.md) hvis du trenger instruksjoner om hvordan du gjør dette.

## Hvorfor trenger du å sikre IoT-enheter?

IoT-sikkerhet handler om å sørge for at kun forventede enheter kan koble seg til din skybaserte IoT-tjeneste og sende telemetri, og at kun din skytjeneste kan sende kommandoer til enhetene dine. IoT-data kan også være personlige, inkludert medisinske eller intime data, så hele applikasjonen din må ta hensyn til sikkerhet for å forhindre at disse dataene lekker.

Hvis IoT-applikasjonen din ikke er sikker, er det flere risikoer:

* En falsk enhet kan sende feil data, noe som får applikasjonen din til å reagere feil. For eksempel kan de sende konstante høye fuktighetsmålinger, noe som betyr at vanningssystemet ditt aldri slår seg på, og plantene dine dør av mangel på vann.
* Uautoriserte brukere kan lese data fra IoT-enheter, inkludert personlige eller forretningskritiske data.
* Hackere kan sende kommandoer for å kontrollere en enhet på en måte som kan skade enheten eller tilkoblet maskinvare.
* Ved å koble seg til en IoT-enhet kan hackere bruke dette til å få tilgang til andre nettverk og private systemer.
* Ondsinnede brukere kan få tilgang til personlige data og bruke dette til utpressing.

Dette er reelle scenarier som skjer hele tiden. Noen eksempler ble gitt i tidligere leksjoner, men her er noen flere:

* I 2018 brukte hackere et åpent WiFi-tilgangspunkt på et akvariumstermometer for å få tilgang til et kasino sitt nettverk og stjele data. [The Hacker News - Casino Gets Hacked Through Its Internet-Connected Fish Tank Thermometer](https://thehackernews.com/2018/04/iot-hacking-thermometer.html)
* I 2016 lanserte Mirai Botnet et tjenestenektangrep mot Dyn, en internettleverandør, som tok ned store deler av internett. Dette botnettet brukte skadelig programvare for å koble seg til IoT-enheter som DVR-er og kameraer som brukte standard brukernavn og passord, og derfra startet angrepet. [The Guardian - DDoS attack that disrupted internet was largest of its kind in history, experts say](https://www.theguardian.com/technology/2016/oct/26/ddos-attack-dyn-mirai-botnet)
* Spiral Toys hadde en database med brukere av deres CloudPets-tilkoblede leker offentlig tilgjengelig på internett. [Troy Hunt - Data from connected CloudPets teddy bears leaked and ransomed, exposing kids' voice messages](https://www.troyhunt.com/data-from-connected-cloudpets-teddy-bears-leaked-and-ransomed-exposing-kids-voice-messages/).
* Strava tagget løpere du løp forbi og viste rutene deres, noe som gjorde det mulig for fremmede å se hvor du bor. [Kim Komndo - Fitness app could lead a stranger right to your home — change this setting](https://www.komando.com/security-privacy/strava-fitness-app-privacy/755349/).

✅ Gjør litt research: Søk etter flere eksempler på IoT-hack og datainnbrudd knyttet til IoT-enheter, spesielt med personlige gjenstander som internett-tilkoblede tannbørster eller vekter. Tenk på hvilken innvirkning disse hackene kan ha på ofrene eller kundene.

> 💁 Sikkerhet er et enormt tema, og denne leksjonen vil bare berøre noen av de grunnleggende prinsippene rundt tilkobling av enheten din til skyen. Andre emner som ikke vil bli dekket inkluderer overvåking av datatransport, hacking av enheter direkte, eller endringer i enhetskonfigurasjoner. IoT-hacking er en så stor trussel at verktøy som [Azure Defender for IoT](https://azure.microsoft.com/services/azure-defender-for-iot/?WT.mc_id=academic-17441-jabenn) har blitt utviklet. Disse verktøyene ligner på antivirus- og sikkerhetsverktøyene du kanskje har på datamaskinen din, men er designet for små, lavstrøms IoT-enheter.

## Kryptografi

Når en enhet kobler seg til en IoT-tjeneste, bruker den en ID for å identifisere seg selv. Problemet er at denne ID-en kan klones – en hacker kan sette opp en ondsinnet enhet som bruker samme ID som en ekte enhet, men sender falske data.

![Både gyldige og ondsinnede enheter kan bruke samme ID for å sende telemetri](../../../../../translated_images/no/iot-device-and-hacked-device-connecting.e0671675df74d6d9.webp)

Løsningen på dette er å konvertere dataene som sendes til et kryptert format, ved å bruke en verdi som kun er kjent av enheten og skyen. Denne prosessen kalles *kryptering*, og verdien som brukes til å kryptere dataene kalles en *krypteringsnøkkel*.

![Hvis kryptering brukes, vil kun krypterte meldinger bli akseptert, andre vil bli avvist](../../../../../translated_images/no/iot-device-and-hacked-device-connecting-encryption.5941aff601fc978f.webp)

Skytjenesten kan deretter konvertere dataene tilbake til et lesbart format ved hjelp av en prosess som kalles *dekryptering*, ved å bruke enten samme krypteringsnøkkel eller en *dekrypteringsnøkkel*. Hvis den krypterte meldingen ikke kan dekrypteres med nøkkelen, har enheten blitt hacket, og meldingen blir avvist.

Teknikken for å utføre kryptering og dekryptering kalles *kryptografi*.

### Tidlig kryptografi

De tidligste typene kryptografi var substitusjonskrypteringer, som daterer seg tilbake 3 500 år. Substitusjonskrypteringer innebærer å erstatte én bokstav med en annen. For eksempel innebærer [Caesar-krypteringen](https://wikipedia.org/wiki/Caesar_cipher) å forskyve alfabetet med en definert mengde, der kun avsenderen av den krypterte meldingen og den tiltenkte mottakeren vet hvor mange bokstaver som skal forskyves.

[Vigenère-krypteringen](https://wikipedia.org/wiki/Vigenère_cipher) tok dette et skritt videre ved å bruke ord for å kryptere tekst, slik at hver bokstav i den opprinnelige teksten ble forskjøvet med en annen mengde, i stedet for alltid å forskyve med samme antall bokstaver.

Kryptografi ble brukt til en rekke formål, som å beskytte en keramikkglasuroppskrift i det gamle Mesopotamia, skrive hemmelige kjærlighetsbrev i India, eller holde gamle egyptiske magiske formler hemmelige.

### Moderne kryptografi

Moderne kryptografi er langt mer avansert, noe som gjør det vanskeligere å knekke enn tidlige metoder. Moderne kryptografi bruker komplisert matematikk for å kryptere data med altfor mange mulige nøkler til at brute force-angrep er mulig.

Kryptografi brukes på mange forskjellige måter for sikker kommunikasjon. Hvis du leser denne siden på GitHub, kan du legge merke til at nettadressen starter med *HTTPS*, noe som betyr at kommunikasjonen mellom nettleseren din og GitHubs webservere er kryptert. Hvis noen skulle lese internett-trafikken mellom nettleseren din og GitHub, ville de ikke kunne lese dataene fordi de er kryptert. Datamaskinen din kan til og med kryptere alle dataene på harddisken din, slik at hvis noen stjeler den, vil de ikke kunne lese noen av dataene uten passordet ditt.

> 🎓 HTTPS står for HyperText Transfer Protocol **Secure**

Dessverre er ikke alt sikkert. Noen enheter har ingen sikkerhet, andre er sikret med lettknekbare nøkler, eller noen ganger bruker alle enheter av samme type den samme nøkkelen. Det har vært tilfeller av svært personlige IoT-enheter som alle har samme passord for å koble seg til dem via WiFi eller Bluetooth. Hvis du kan koble deg til din egen enhet, kan du også koble deg til andres. Når du er tilkoblet, kan du få tilgang til svært private data eller kontrollere enheten deres.

> 💁 Til tross for kompleksiteten i moderne kryptografi og påstandene om at det kan ta milliarder av år å bryte kryptering, har fremveksten av kvantedatabehandling ført til muligheten for å bryte all kjent kryptering på svært kort tid!

### Symmetriske og asymmetriske nøkler

Kryptering kommer i to typer – symmetrisk og asymmetrisk.

**Symmetrisk** kryptering bruker samme nøkkel for å kryptere og dekryptere dataene. Både avsender og mottaker må kjenne til den samme nøkkelen. Dette er den minst sikre typen, siden nøkkelen må deles på en eller annen måte. For at en avsender skal sende en kryptert melding til en mottaker, må avsenderen først sende nøkkelen til mottakeren.

![Symmetrisk nøkkelkryptering bruker samme nøkkel for å kryptere og dekryptere en melding](../../../../../translated_images/no/send-message-symmetric-key.a2e8ad0d495896ff.webp)

Hvis nøkkelen blir stjålet under overføring, eller hvis avsenderen eller mottakeren blir hacket og nøkkelen blir funnet, kan krypteringen knekkes.

![Symmetrisk nøkkelkryptering er kun sikker hvis en hacker ikke får tak i nøkkelen – hvis det skjer, kan de avskjære og dekryptere meldingen](../../../../../translated_images/no/send-message-symmetric-key-hacker.e7cb53db1707adfb.webp)

**Asymmetrisk** kryptering bruker to nøkler – en krypteringsnøkkel og en dekrypteringsnøkkel, kjent som et offentlig/privat nøkkelpar. Den offentlige nøkkelen brukes til å kryptere meldingen, men kan ikke brukes til å dekryptere den. Den private nøkkelen brukes til å dekryptere meldingen, men kan ikke brukes til å kryptere den.

![Asymmetrisk kryptering bruker en annen nøkkel for å kryptere og dekryptere. Krypteringsnøkkelen sendes til meldingsavsendere slik at de kan kryptere en melding før de sender den til mottakeren som eier nøklene](../../../../../translated_images/no/send-message-asymmetric.7abe327c62615b8c.webp)

Mottakeren deler sin offentlige nøkkel, og avsenderen bruker denne til å kryptere meldingen. Når meldingen er sendt, dekrypterer mottakeren den med sin private nøkkel. Asymmetrisk kryptering er mer sikker, siden den private nøkkelen holdes privat av mottakeren og aldri deles. Alle kan ha den offentlige nøkkelen, siden den kun kan brukes til å kryptere meldinger.

Symmetrisk kryptering er raskere enn asymmetrisk kryptering, mens asymmetrisk er mer sikker. Noen systemer bruker begge deler – asymmetrisk kryptering for å kryptere og dele den symmetriske nøkkelen, og deretter symmetrisk kryptering for å kryptere alle data. Dette gjør det sikrere å dele den symmetriske nøkkelen mellom avsender og mottaker, og raskere når data krypteres og dekrypteres.

## Sikre IoT-enhetene dine

IoT-enheter kan sikres ved hjelp av symmetrisk eller asymmetrisk kryptering. Symmetrisk er enklere, men mindre sikkert.

### Symmetriske nøkler

Da du satte opp IoT-enheten din for å samhandle med IoT Hub, brukte du en tilkoblingsstreng. Et eksempel på en tilkoblingsstreng er:

```output
HostName=soil-moisture-sensor.azure-devices.net;DeviceId=soil-moisture-sensor;SharedAccessKey=Bhry+ind7kKEIDxubK61RiEHHRTrPl7HUow8cEm/mU0=
```

Denne tilkoblingsstrengen består av tre deler, separert med semikolon, der hver del er en nøkkel og en verdi:

| Nøkkel | Verdi | Beskrivelse |
| --- | ----- | ----------- |
| HostName | `soil-moisture-sensor.azure-devices.net` | URL-en til IoT Hub |
| DeviceId | `soil-moisture-sensor` | Den unike ID-en til enheten |
| SharedAccessKey | `Bhry+ind7kKEIDxubK61RiEHHRTrPl7HUow8cEm/mU0=` | En symmetrisk nøkkel kjent av enheten og IoT Hub |

Den siste delen av denne tilkoblingsstrengen, `SharedAccessKey`, er den symmetriske nøkkelen kjent av både enheten og IoT Hub. Denne nøkkelen sendes aldri fra enheten til skyen, eller fra skyen til enheten. I stedet brukes den til å kryptere data som sendes eller mottas.

✅ Gjør et eksperiment. Hva tror du vil skje hvis du endrer `SharedAccessKey`-delen av tilkoblingsstrengen når du kobler IoT-enheten din? Prøv det ut.

Når enheten først prøver å koble seg til, sender den en delt tilgangssignatur (SAS)-token som består av URL-en til IoT Hub, et tidsstempel for når tilgangssignaturen utløper (vanligvis 1 dag fra nåværende tid), og en signatur. Denne signaturen består av URL-en og utløpstiden kryptert med den delte tilgangsnøkkelen fra tilkoblingsstrengen.

IoT Hub dekrypterer denne signaturen med den delte tilgangsnøkkelen, og hvis den dekrypterte verdien samsvarer med URL-en og utløpstiden, får enheten lov til å koble seg til. Den verifiserer også at nåværende tid er før utløpstiden, for å forhindre at en ondsinnet enhet fanger opp SAS-tokenet til en ekte enhet og bruker det.

Dette er en elegant måte å verifisere at avsenderen er den riktige enheten. Ved å sende noen kjente data både i ukryptert og kryptert form, kan serveren verifisere enheten ved å sørge for at når den dekrypterer de krypterte dataene, samsvarer resultatet med den ukrypterte versjonen som ble sendt. Hvis det samsvarer, har både avsender og mottaker samme symmetriske krypteringsnøkkel.
💁 På grunn av utløpstiden må IoT-enheten din vite nøyaktig tid, som vanligvis hentes fra en [NTP](https://wikipedia.org/wiki/Network_Time_Protocol)-server. Hvis tiden ikke er nøyaktig, vil tilkoblingen mislykkes.
Etter tilkoblingen vil all data som sendes til IoT Hub fra enheten, eller til enheten fra IoT Hub, bli kryptert med den delte tilgangsnøkkelen.

✅ Hva tror du vil skje hvis flere enheter deler samme tilkoblingsstreng?

> 💁 Det er dårlig sikkerhetspraksis å lagre denne nøkkelen i kode. Hvis en hacker får tilgang til kildekoden din, kan de få tak i nøkkelen. Det blir også vanskeligere når du skal publisere kode, siden du må kompilere på nytt med en oppdatert nøkkel for hver enhet. Det er bedre å laste inn nøkkelen fra en maskinvarebasert sikkerhetsmodul – en brikke på IoT-enheten som lagrer krypterte verdier som kan leses av koden din.
>
> Når du lærer om IoT, er det ofte enklere å legge nøkkelen i koden, slik du gjorde i en tidligere leksjon, men du må sørge for at denne nøkkelen ikke sjekkes inn i offentlig kildekontroll.

Enheter har to nøkler og to tilsvarende tilkoblingsstrenger. Dette gjør det mulig å rotere nøklene – det vil si bytte fra én nøkkel til en annen hvis den første blir kompromittert, og generere den første nøkkelen på nytt.

### X.509-sertifikater

Når du bruker asymmetrisk kryptering med et offentlig/privat nøkkelpar, må du gi den offentlige nøkkelen din til alle som ønsker å sende deg data. Problemet er: Hvordan kan mottakeren av nøkkelen din være sikker på at det faktisk er din offentlige nøkkel, og ikke noen andre som utgir seg for å være deg? I stedet for å gi en nøkkel, kan du gi den offentlige nøkkelen din i et sertifikat som er bekreftet av en pålitelig tredjepart, kalt et X.509-sertifikat.

X.509-sertifikater er digitale dokumenter som inneholder den offentlige delen av et offentlig/privat nøkkelpar. De utstedes vanligvis av en rekke pålitelige organisasjoner kalt [sertifiseringsmyndigheter](https://wikipedia.org/wiki/Certificate_authority) (CAs) og signeres digitalt av CA-en for å indikere at nøkkelen er gyldig og kommer fra deg. Du stoler på sertifikatet og at den offentlige nøkkelen er fra den personen sertifikatet sier det er fra, fordi du stoler på CA-en, på samme måte som du ville stolt på et pass eller førerkort fordi du stoler på landet som utstedte det. Sertifikater koster penger, men du kan også "selv-signere", det vil si opprette et sertifikat selv som er signert av deg, for testformål.

> 💁 Du bør aldri bruke et selv-signert sertifikat i en produksjonsutgivelse.

Disse sertifikatene har en rekke felt, inkludert hvem den offentlige nøkkelen er fra, detaljene om CA-en som utstedte det, hvor lenge det er gyldig, og selve den offentlige nøkkelen. Før du bruker et sertifikat, er det god praksis å verifisere det ved å sjekke at det ble signert av den opprinnelige CA-en.

✅ Du kan lese en fullstendig liste over feltene i sertifikatet i [Microsofts veiledning om X.509 Public Key Certificates](https://docs.microsoft.com/azure/iot-hub/tutorial-x509-certificates?WT.mc_id=academic-17441-jabenn#certificate-fields).

Når du bruker X.509-sertifikater, vil både avsender og mottaker ha sine egne offentlige og private nøkler, samt X.509-sertifikater som inneholder de offentlige nøklene. De utveksler deretter X.509-sertifikater på en eller annen måte, bruker hverandres offentlige nøkler til å kryptere dataene de sender, og sine egne private nøkler til å dekryptere dataene de mottar.

![I stedet for å dele en offentlig nøkkel, kan du dele et sertifikat. Brukeren av sertifikatet kan verifisere at det kommer fra deg ved å sjekke med sertifiseringsmyndigheten som signerte det.](../../../../../translated_images/no/send-message-certificate.9cc576ac1e46b76e.webp)

En stor fordel med å bruke X.509-sertifikater er at de kan deles mellom enheter. Du kan opprette ett sertifikat, laste det opp til IoT Hub, og bruke det for alle enhetene dine. Hver enhet trenger da bare å kjenne til den private nøkkelen for å dekryptere meldingene den mottar fra IoT Hub.

Sertifikatet som brukes av enheten din til å kryptere meldinger den sender til IoT Hub, er publisert av Microsoft. Det er det samme sertifikatet som mange Azure-tjenester bruker, og det er noen ganger innebygd i SDK-ene.

> 💁 Husk, en offentlig nøkkel er nettopp det – offentlig. Den offentlige nøkkelen til Azure kan bare brukes til å kryptere data som sendes til Azure, ikke til å dekryptere dem, så den kan deles overalt, inkludert i kildekode. For eksempel kan du se den i [Azure IoT C SDK-kildekoden](https://github.com/Azure/azure-iot-sdk-c/blob/master/certs/certs.c).

✅ Det er mye sjargong knyttet til X.509-sertifikater. Du kan lese definisjonene av noen av begrepene du kan støte på i [The layman’s guide to X.509 certificate jargon](https://techcommunity.microsoft.com/t5/internet-of-things/the-layman-s-guide-to-x-509-certificate-jargon/ba-p/2203540?WT.mc_id=academic-17441-jabenn).

## Generere og bruke et X.509-sertifikat

Stegene for å generere et X.509-sertifikat er:

1. Opprett et offentlig/privat nøkkelpar. En av de mest brukte algoritmene for å generere et offentlig/privat nøkkelpar kalles [Rivest–Shamir–Adleman](https://wikipedia.org/wiki/RSA_(cryptosystem)) (RSA).

2. Send inn den offentlige nøkkelen med tilhørende data for signering, enten av en CA eller ved selv-signering.

Azure CLI har kommandoer for å opprette en ny enhetsidentitet i IoT Hub, automatisk generere det offentlige/private nøkkelparet og opprette et selv-signert sertifikat.

> 💁 Hvis du vil se stegene i detalj, i stedet for å bruke Azure CLI, kan du finne dem i [veiledningen om bruk av OpenSSL for å opprette selv-signerte sertifikater i Microsoft IoT Hub-dokumentasjonen](https://docs.microsoft.com/azure/iot-hub/tutorial-x509-self-sign?WT.mc_id=academic-17441-jabenn).

### Oppgave – opprett en enhetsidentitet ved hjelp av et X.509-sertifikat

1. Kjør følgende kommando for å registrere den nye enhetsidentiteten og automatisk generere nøklene og sertifikatene:

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor-x509 \
                                      --am x509_thumbprint \
                                      --output-dir . \
                                      --hub-name <hub_name>
    ```

    Erstatt `<hub_name>` med navnet du brukte for IoT Hub.

    Dette vil opprette en enhet med ID-en `soil-moisture-sensor-x509` for å skille den fra enhetsidentiteten du opprettet i forrige leksjon. Denne kommandoen vil også opprette to filer i den gjeldende katalogen:

    * `soil-moisture-sensor-x509-key.pem` – denne filen inneholder den private nøkkelen for enheten.
    * `soil-moisture-sensor-x509-cert.pem` – dette er X.509-sertifikatfilen for enheten.

    Hold disse filene trygge! Den private nøkkelfilen bør ikke sjekkes inn i offentlig kildekontroll.

### Oppgave – bruk X.509-sertifikatet i enhetskoden din

Følg den relevante veiledningen for å koble IoT-enheten din til skyen ved hjelp av X.509-sertifikatet:

* [Arduino - Wio Terminal](wio-terminal-x509.md)
* [Enkeltkortdatamaskin - Raspberry Pi/Virtual IoT device](single-board-computer-x509.md)

---

## 🚀 Utfordring

Det finnes flere måter å opprette, administrere og slette Azure-tjenester som Ressursgrupper og IoT Hubs. En måte er [Azure-portalen](https://portal.azure.com?WT.mc_id=academic-17441-jabenn) – et nettbasert grensesnitt som gir deg en GUI for å administrere Azure-tjenestene dine.

Gå til [portal.azure.com](https://portal.azure.com?WT.mc_id=academic-17441-jabenn) og undersøk portalen. Se om du kan opprette en IoT Hub ved hjelp av portalen, og deretter slette den.

**Tips** – når du oppretter tjenester gjennom portalen, trenger du ikke opprette en Ressursgruppe på forhånd, en kan opprettes samtidig som du oppretter tjenesten. Sørg for å slette den når du er ferdig!

Du finner mye dokumentasjon, veiledninger og guider om Azure-portalen i [Azure portal-dokumentasjonen](https://docs.microsoft.com/azure/azure-portal/?WT.mc_id=academic-17441-jabenn).

## Quiz etter forelesning

[Quiz etter forelesning](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/20)

## Gjennomgang og selvstudium

* Les om kryptografiens historie på [Wikipedia-siden om kryptografiens historie](https://wikipedia.org/wiki/History_of_cryptography).
* Les om X.509-sertifikater på [Wikipedia-siden om X.509](https://wikipedia.org/wiki/X.509).

## Oppgave

[Bygg en ny IoT-enhet](assignment.md)

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.