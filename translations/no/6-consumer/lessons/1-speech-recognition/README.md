# Gjenkjenne tale med en IoT-enhet

![En sketchnote som gir en oversikt over denne leksjonen](../../../../../translated_images/no/lesson-21.e34de51354d6606f.webp)

> Sketchnote av [Nitya Narasimhan](https://github.com/nitya). Klikk på bildet for en større versjon.

Denne videoen gir en oversikt over Azure tale-tjenesten, et tema som vil bli dekket i denne leksjonen:

[![Hvordan komme i gang med Cognitive Services Speech-ressursen fra Microsoft Azure YouTube-kanalen](https://img.youtube.com/vi/iW0Fw0l3mrA/0.jpg)](https://www.youtube.com/watch?v=iW0Fw0l3mrA)

> 🎥 Klikk på bildet ovenfor for å se videoen

## Quiz før leksjonen

[Quiz før leksjonen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/41)

## Introduksjon

'Alexa, sett en timer på 12 minutter'

'Alexa, status på timeren'

'Alexa, sett en timer på 8 minutter kalt damp brokkoli'

Smartenheter blir stadig mer utbredt. Ikke bare som smarthøyttalere som HomePods, Echos og Google Homes, men også integrert i telefoner, klokker, og til og med lysarmaturer og termostater.

> 💁 Jeg har minst 19 enheter i hjemmet mitt som har stemmeassistenter, og det er bare de jeg vet om!

Stemmestyring øker tilgjengeligheten ved å la personer med begrenset bevegelighet interagere med enheter. Enten det er en permanent funksjonsnedsettelse som å være født uten armer, en midlertidig skade som brukne armer, eller bare det å ha hendene fulle med matvarer eller små barn, kan det å styre huset med stemmen i stedet for hendene åpne opp en verden av muligheter. Å rope 'Hei Siri, lukk garasjeporten' mens du håndterer en bleieskift og en rampete smårolling kan være en liten, men effektiv forbedring i hverdagen.

En av de mest populære bruksområdene for stemmeassistenter er å sette timere, spesielt kjøkkentimere. Å kunne sette flere timere med bare stemmen er en stor hjelp på kjøkkenet – ingen grunn til å stoppe med å kna deigen, røre i suppen, eller vaske hendene for å bruke en fysisk timer.

I denne leksjonen vil du lære om hvordan du kan bygge stemmegjenkjenning inn i IoT-enheter. Du vil lære om mikrofoner som sensorer, hvordan du fanger lyd fra en mikrofon koblet til en IoT-enhet, og hvordan du bruker AI til å konvertere det som høres til tekst. Gjennom resten av dette prosjektet vil du bygge en smart kjøkkentimer som kan sette timere med stemmen din på flere språk.

I denne leksjonen dekker vi:

* [Mikrofoner](../../../../../6-consumer/lessons/1-speech-recognition)
* [Fange lyd fra IoT-enheten din](../../../../../6-consumer/lessons/1-speech-recognition)
* [Tale til tekst](../../../../../6-consumer/lessons/1-speech-recognition)
* [Konverter tale til tekst](../../../../../6-consumer/lessons/1-speech-recognition)

## Mikrofoner

Mikrofoner er analoge sensorer som konverterer lydbølger til elektriske signaler. Vibrasjoner i luften får komponenter i mikrofonen til å bevege seg små mengder, og dette forårsaker små endringer i elektriske signaler. Disse endringene forsterkes deretter for å generere et elektrisk output.

### Mikrofontyper

Mikrofoner finnes i en rekke typer:

* Dynamisk - Dynamiske mikrofoner har en magnet festet til en bevegelig membran som beveger seg i en spole av ledning og skaper en elektrisk strøm. Dette er motsatt av de fleste høyttalere, som bruker en elektrisk strøm til å bevege en magnet i en spole av ledning, og beveger en membran for å skape lyd. Dette betyr at høyttalere kan brukes som dynamiske mikrofoner, og dynamiske mikrofoner kan brukes som høyttalere. I enheter som intercoms, der en bruker enten lytter eller snakker, men ikke begge deler, kan én enhet fungere som både høyttaler og mikrofon.

    Dynamiske mikrofoner trenger ikke strøm for å fungere, det elektriske signalet skapes helt av mikrofonen.

    ![Patti Smith synger inn i en Shure SM58 (dynamisk kardioid-type) mikrofon](../../../../../translated_images/no/dynamic-mic.8babac890a2d80df.webp)

* Bånd - Båndmikrofoner ligner på dynamiske mikrofoner, bortsett fra at de har et metallbånd i stedet for en membran. Dette båndet beveger seg i et magnetfelt og genererer en elektrisk strøm. Som dynamiske mikrofoner trenger ikke båndmikrofoner strøm for å fungere.

    ![Edmund Lowe, amerikansk skuespiller, står ved en radiomikrofon (merket for (NBC) Blue Network), holder manus, 1942](../../../../../translated_images/no/ribbon-mic.eacc8e092c7441ca.webp)

* Kondensator - Kondensatormikrofoner har en tynn metallmembran og en fast metall bakplate. Elektrisitet påføres begge disse, og når membranen vibrerer, endres den statiske ladningen mellom platene og genererer et signal. Kondensatormikrofoner trenger strøm for å fungere – kalt *Phantom power*.

    ![C451B små-membran kondensatormikrofon fra AKG Acoustics](../../../../../translated_images/no/condenser-mic.6f6ed5b76ca19e0e.webp)

* MEMS - Mikroelektromekaniske systemmikrofoner, eller MEMS, er mikrofoner på en chip. De har en trykkfølsom membran etset på en silisiumchip, og fungerer på samme måte som en kondensatormikrofon. Disse mikrofonene kan være svært små og integrert i kretsløp.

    ![En MEMS-mikrofon på et kretskort](../../../../../translated_images/no/mems-microphone.80574019e1f5e4d9.webp)

    På bildet ovenfor er chipen merket **LEFT** en MEMS-mikrofon, med en liten membran mindre enn en millimeter bred.

✅ Gjør litt research: Hvilke mikrofoner har du rundt deg – enten i datamaskinen, telefonen, headsettet eller andre enheter? Hvilken type mikrofoner er de?

### Digital lyd

Lyd er et analogt signal som bærer svært fin-granulert informasjon. For å konvertere dette signalet til digitalt, må lyden samples mange tusen ganger i sekundet.

> 🎓 Sampling innebærer å konvertere lydsignalet til en digital verdi som representerer signalet på det tidspunktet.

![En linjediagram som viser et signal, med diskrete punkter på faste intervaller](../../../../../translated_images/no/sampling.6f4fadb3f2d9dfe7.webp)

Digital lyd samples ved hjelp av Pulse Code Modulation, eller PCM. PCM innebærer å lese spenningen i signalet og velge den nærmeste diskrete verdien til den spenningen ved hjelp av en definert størrelse.

> 💁 Du kan tenke på PCM som sensorversjonen av pulsbreddemodulasjon, eller PWM (PWM ble dekket tilbake i [leksjon 3 av introduksjonsprosjektet](../../../1-getting-started/lessons/3-sensors-and-actuators/README.md#pulse-width-modulation)). PCM innebærer å konvertere et analogt signal til digitalt, PWM innebærer å konvertere et digitalt signal til analogt.

For eksempel tilbyr de fleste strømmetjenester for musikk 16-bit eller 24-bit lyd. Dette betyr at de konverterer spenningen til en verdi som passer inn i et 16-bit heltall eller 24-bit heltall. 16-bit lyd passer verdien inn i et tall som varierer fra -32,768 til 32,767, 24-bit er i området −8,388,608 til 8,388,607. Jo flere biter, desto nærmere er samplingen det våre ører faktisk hører.

> 💁 Du har kanskje hørt om 8-bit lyd, ofte referert til som LoFi. Dette er lyd samplet med bare 8 biter, altså -128 til 127. Den første datamaskinlyden var begrenset til 8 biter på grunn av maskinvarebegrensninger, så dette sees ofte i retrospill.

Disse samplene tas mange tusen ganger per sekund, ved hjelp av veldefinerte samplingsfrekvenser målt i KHz (tusenvis av avlesninger per sekund). Strømmetjenester for musikk bruker 48KHz for de fleste lydspor, men noen 'lossless' lyd bruker opptil 96KHz eller til og med 192KHz. Jo høyere samplingsfrekvens, desto nærmere originalen vil lyden være, opp til et visst punkt. Det er debatt om mennesker kan merke forskjellen over 48KHz.

✅ Gjør litt research: Hvis du bruker en strømmetjeneste for musikk, hvilken samplingsfrekvens og størrelse bruker den? Hvis du bruker CD-er, hva er samplingsfrekvensen og størrelsen på CD-lyd?

Det finnes en rekke forskjellige formater for lyddata. Du har sikkert hørt om mp3-filer – lyddata som er komprimert for å gjøre dem mindre uten å miste kvalitet. Ukomprimert lyd lagres ofte som en WAV-fil – dette er en fil med 44 bytes med headerinformasjon, etterfulgt av rå lyddata. Headeren inneholder informasjon som samplingsfrekvensen (for eksempel 16000 for 16KHz) og samplingsstørrelsen (16 for 16-bit), og antall kanaler. Etter headeren inneholder WAV-filen de rå lyddataene.

> 🎓 Kanaler refererer til hvor mange forskjellige lydstrømmer som utgjør lyden. For eksempel, for stereo lyd med venstre og høyre, vil det være 2 kanaler. For 7.1 surroundlyd for et hjemmekinosystem vil dette være 8.

### Lyddatastørrelse

Lyddata er relativt store. For eksempel, å fange ukomprimert 16-bit lyd ved 16KHz (en god nok rate for bruk med tale-til-tekst-modeller), tar 32KB med data for hvert sekund med lyd:

* 16-bit betyr 2 bytes per sample (1 byte er 8 biter).
* 16KHz er 16,000 samples per sekund.
* 16,000 x 2 bytes = 32,000 bytes per sekund.

Dette høres ut som en liten mengde data, men hvis du bruker en mikrokontroller med begrenset minne, kan dette være mye. For eksempel har Wio Terminal 192KB med minne, og det må lagre programkode og variabler. Selv om programkoden din var liten, kunne du ikke fange mer enn 5 sekunder med lyd.

Mikrokontrollere kan få tilgang til ekstra lagring, som SD-kort eller flashminne. Når du bygger en IoT-enhet som fanger lyd, må du sørge for at du ikke bare har ekstra lagring, men at koden din skriver lyden som fanges fra mikrofonen direkte til den lagringen, og når du sender den til skyen, streamer fra lagring til webforespørselen. På den måten kan du unngå å gå tom for minne ved å prøve å holde hele lydblokken i minnet samtidig.

## Fange lyd fra IoT-enheten din

IoT-enheten din kan kobles til en mikrofon for å fange lyd, klar for konvertering til tekst. Den kan også kobles til høyttalere for å spille av lyd. I senere leksjoner vil dette brukes til å gi lydtilbakemelding, men det er nyttig å sette opp høyttalere nå for å teste mikrofonen.

### Oppgave - konfigurer mikrofonen og høyttalerne dine

Følg den relevante guiden for å konfigurere mikrofonen og høyttalerne for IoT-enheten din:

* [Arduino - Wio Terminal](wio-terminal-microphone.md)
* [Enkeltkortdatamaskin - Raspberry Pi](pi-microphone.md)
* [Enkeltkortdatamaskin - Virtuell enhet](virtual-device-microphone.md)

### Oppgave - fang lyd

Følg den relevante guiden for å fange lyd på IoT-enheten din:

* [Arduino - Wio Terminal](wio-terminal-audio.md)
* [Enkeltkortdatamaskin - Raspberry Pi](pi-audio.md)
* [Enkeltkortdatamaskin - Virtuell enhet](virtual-device-audio.md)

## Tale til tekst

Tale til tekst, eller talegjenkjenning, innebærer å bruke AI til å konvertere ord i et lydsignal til tekst.

### Talemodeller

For å konvertere tale til tekst, grupperes prøver fra lydsignalet sammen og mates inn i en maskinlæringsmodell basert på et Recurrent Neural Network (RNN). Dette er en type maskinlæringsmodell som kan bruke tidligere data til å ta en beslutning om innkommende data. For eksempel kan RNN oppdage én blokk med lydprøver som lyden 'Hel', og når den mottar en annen som den tror er lyden 'lo', kan den kombinere dette med den forrige lyden, finne ut at 'Hello' er et gyldig ord og velge det som resultat.

ML-modeller aksepterer alltid data av samme størrelse hver gang. Bildesorteringsmodellen du bygde i en tidligere leksjon endrer størrelsen på bilder til en fast størrelse og prosesserer dem. Det samme gjelder talemodeller, de må prosessere faste størrelser av lydblokker. Talemodellene må kunne kombinere resultatene av flere prediksjoner for å få svaret, slik at de kan skille mellom 'Hi' og 'Highway', eller 'flock' og 'floccinaucinihilipilification'.

Talemodeller er også avanserte nok til å forstå kontekst, og kan korrigere ordene de oppdager etter hvert som flere lyder prosesseres. For eksempel, hvis du sier "Jeg dro til butikken for å kjøpe to bananer og et eple også", vil du bruke tre ord som høres like ut, men staves forskjellig – to, two og too. Talemodeller er i stand til å forstå konteksten og bruke riktig stavemåte for ordet.
💁 Noen talegjenkjenningstjenester tillater tilpasning for å fungere bedre i støyende miljøer som fabrikker, eller med bransjespesifikke ord som kjemiske navn. Disse tilpasningene trenes ved å gi eksempellyd og en transkripsjon, og fungerer ved hjelp av transfer learning, på samme måte som du trente en bildegjenkjenner med bare noen få bilder i en tidligere leksjon.
### Personvern

Når du bruker tale-til-tekst på en forbruker-IoT-enhet, er personvern utrolig viktig. Disse enhetene lytter kontinuerlig til lyd, og som forbruker ønsker du ikke at alt du sier skal sendes til skyen og konverteres til tekst. Ikke bare vil dette bruke mye internettbåndbredde, det har også store personvernutfordringer, spesielt når noen produsenter av smarte enheter tilfeldig velger lyd for [mennesker å validere mot den genererte teksten for å forbedre modellen deres](https://www.theverge.com/2019/4/10/18305378/amazon-alexa-ai-voice-assistant-annotation-listen-private-recordings).

Du vil kun at din smarte enhet skal sende lyd til skyen for behandling når du bruker den, ikke når den hører lyd i hjemmet ditt, lyd som kan inkludere private møter eller intime interaksjoner. Måten de fleste smarte enheter fungerer på er med et *aktiveringsord*, en nøkkelfrase som "Alexa", "Hey Siri" eller "OK Google" som får enheten til å 'våkne' og lytte til det du sier frem til den oppdager en pause i talen din, som indikerer at du er ferdig med å snakke til enheten.

> 🎓 Aktiveringsordgjenkjenning kalles også *Keyword spotting* eller *Keyword recognition*.

Disse aktiveringsordene oppdages på enheten, ikke i skyen. Disse smarte enhetene har små AI-modeller som kjører på enheten og lytter etter aktiveringsordet, og når det oppdages, begynner de å strømme lyden til skyen for gjenkjenning. Disse modellene er svært spesialiserte og lytter kun etter aktiveringsordet.

> 💁 Noen teknologiselskaper legger til mer personvern i enhetene sine og utfører noe av tale-til-tekst-konverteringen på enheten. Apple har annonsert at som en del av deres 2021 iOS- og macOS-oppdateringer vil de støtte tale-til-tekst-konvertering på enheten og kunne håndtere mange forespørsler uten å bruke skyen. Dette er mulig takket være kraftige prosessorer i enhetene deres som kan kjøre ML-modeller.

✅ Hva mener du er de personvern- og etiske implikasjonene ved å lagre lyd som sendes til skyen? Bør denne lyden lagres, og i så fall, hvordan? Synes du bruken av opptak for rettshåndhevelse er en god avveining for tap av personvern?

Aktiveringsordgjenkjenning bruker vanligvis en teknikk kjent som TinyML, som innebærer å konvertere ML-modeller slik at de kan kjøre på mikrokontrollere. Disse modellene er små i størrelse og bruker svært lite strøm.

For å unngå kompleksiteten ved å trene og bruke en aktiveringsordmodell, vil den smarte timeren du bygger i denne leksjonen bruke en knapp for å aktivere talegjenkjenning.

> 💁 Hvis du vil prøve å lage en aktiveringsordmodell som kan kjøre på Wio Terminal eller Raspberry Pi, kan du sjekke ut denne [veiledningen om å svare på stemmen din fra Edge Impulse](https://docs.edgeimpulse.com/docs/responding-to-your-voice). Hvis du vil bruke datamaskinen din til dette, kan du prøve [komme i gang med Custom Keyword quickstart på Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/keyword-recognition-overview?WT.mc_id=academic-17441-jabenn).

## Konverter tale til tekst

![Logo for taletjenester](../../../../../translated_images/no/azure-speech-logo.a1f08c4befb0159f.webp)

Akkurat som med bildeklassifisering i et tidligere prosjekt, finnes det forhåndsbygde AI-tjenester som kan ta tale som en lydfil og konvertere den til tekst. En slik tjeneste er Speech Service, en del av Cognitive Services, forhåndsbygde AI-tjenester du kan bruke i appene dine.

### Oppgave - konfigurer en tale-AI-ressurs

1. Opprett en ressursgruppe for dette prosjektet kalt `smart-timer`.

1. Bruk følgende kommando for å opprette en gratis taleressurs:

    ```sh
    az cognitiveservices account create --name smart-timer \
                                        --resource-group smart-timer \
                                        --kind SpeechServices \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Erstatt `<location>` med stedet du brukte da du opprettet ressursgruppen.

1. Du trenger en API-nøkkel for å få tilgang til taleressursen fra koden din. Kjør følgende kommando for å hente nøkkelen:

    ```sh
    az cognitiveservices account keys list --name smart-timer \
                                           --resource-group smart-timer \
                                           --output table
    ```

    Ta en kopi av en av nøklene.

### Oppgave - konverter tale til tekst

Følg den relevante veiledningen for å konvertere tale til tekst på din IoT-enhet:

* [Arduino - Wio Terminal](wio-terminal-speech-to-text.md)
* [Enkeltkortdatamaskin - Raspberry Pi](pi-speech-to-text.md)
* [Enkeltkortdatamaskin - Virtuell enhet](virtual-device-speech-to-text.md)

---

## 🚀 Utfordring

Talegjenkjenning har eksistert lenge og forbedres kontinuerlig. Undersøk dagens kapabiliteter og sammenlign hvordan disse har utviklet seg over tid, inkludert hvor nøyaktige maskintranskripsjoner er sammenlignet med menneskelige.

Hva tror du fremtiden bringer for talegjenkjenning?

## Quiz etter forelesning

[Quiz etter forelesning](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/42)

## Gjennomgang og selvstudium

* Les om de forskjellige mikrofontypene og hvordan de fungerer i [artikkelen om forskjellen mellom dynamiske og kondensatormikrofoner på Musician's HQ](https://musicianshq.com/whats-the-difference-between-dynamic-and-condenser-microphones/).
* Les mer om Cognitive Services taletjeneste i [dokumentasjonen for taletjenesten på Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/?WT.mc_id=academic-17441-jabenn).
* Les om aktiveringsordgjenkjenning i [dokumentasjonen for aktiveringsordgjenkjenning på Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/keyword-recognition-overview?WT.mc_id=academic-17441-jabenn).

## Oppgave

[](assignment.md)

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiske oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.