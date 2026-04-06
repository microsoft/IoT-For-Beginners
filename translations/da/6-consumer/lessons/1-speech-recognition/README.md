# Genkend tale med en IoT-enhed

![En sketchnote-oversigt over denne lektion](../../../../../translated_images/da/lesson-21.e34de51354d6606f.webp)

> Sketchnote af [Nitya Narasimhan](https://github.com/nitya). Klik på billedet for en større version.

Denne video giver en oversigt over Azure tale-tjenesten, et emne der vil blive dækket i denne lektion:

[![Sådan kommer du i gang med din Cognitive Services Speech-ressource fra Microsoft Azure YouTube-kanalen](https://img.youtube.com/vi/iW0Fw0l3mrA/0.jpg)](https://www.youtube.com/watch?v=iW0Fw0l3mrA)

> 🎥 Klik på billedet ovenfor for at se videoen

## Quiz før lektionen

[Quiz før lektionen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/41)

## Introduktion

'Alexa, sæt en timer på 12 minutter'

'Alexa, status på timer'

'Alexa, sæt en timer på 8 minutter kaldet damp broccoli'

Smarte enheder bliver mere og mere udbredte. Ikke kun som smarte højttalere som HomePods, Echos og Google Homes, men også indbygget i vores telefoner, ure og endda lysarmaturer og termostater.

> 💁 Jeg har mindst 19 enheder i mit hjem, der har stemmeassistenter, og det er bare dem, jeg kender til!

Stemmestyring øger tilgængeligheden ved at give folk med begrænset bevægelighed mulighed for at interagere med enheder. Uanset om det er en permanent funktionsnedsættelse som at være født uden arme, en midlertidig skade som brækkede arme, eller hvis man har hænderne fulde af indkøb eller små børn, kan det at styre vores hjem med stemmen i stedet for hænderne åbne op for en verden af muligheder. At råbe 'Hey Siri, luk min garageport' mens man håndterer en baby og en uregerlig tumling kan være en lille, men effektiv forbedring af hverdagen.

En af de mest populære anvendelser af stemmeassistenter er at sætte timere, især køkkentimere. At kunne sætte flere timere med bare stemmen er en stor hjælp i køkkenet - ingen grund til at stoppe med at ælte dej, røre i suppen eller rense hænderne for dumplingsfyld for at bruge en fysisk timer.

I denne lektion vil du lære om at integrere stemmegenkendelse i IoT-enheder. Du vil lære om mikrofoner som sensorer, hvordan man optager lyd fra en mikrofon tilsluttet en IoT-enhed, og hvordan man bruger AI til at konvertere det, der høres, til tekst. Gennem resten af dette projekt vil du bygge en smart køkkentimer, der kan sætte timere med din stemme på flere sprog.

I denne lektion vil vi dække:

* [Mikrofoner](../../../../../6-consumer/lessons/1-speech-recognition)
* [Optag lyd fra din IoT-enhed](../../../../../6-consumer/lessons/1-speech-recognition)
* [Tale til tekst](../../../../../6-consumer/lessons/1-speech-recognition)
* [Konverter tale til tekst](../../../../../6-consumer/lessons/1-speech-recognition)

## Mikrofoner

Mikrofoner er analoge sensorer, der konverterer lydbølger til elektriske signaler. Vibrationer i luften får komponenter i mikrofonen til at bevæge sig en smule, hvilket skaber små ændringer i elektriske signaler. Disse ændringer forstærkes derefter for at generere et elektrisk output.

### Mikrofontyper

Mikrofoner findes i forskellige typer:

* Dynamisk - Dynamiske mikrofoner har en magnet, der er fastgjort til en bevægelig membran, som bevæger sig i en spole af ledning og skaber en elektrisk strøm. Dette er det modsatte af de fleste højttalere, der bruger en elektrisk strøm til at bevæge en magnet i en spole af ledning, hvilket får en membran til at skabe lyd. Det betyder, at højttalere kan bruges som dynamiske mikrofoner, og dynamiske mikrofoner kan bruges som højttalere. I enheder som intercoms, hvor en bruger enten lytter eller taler, men ikke begge dele, kan én enhed fungere som både højttaler og mikrofon.

    Dynamiske mikrofoner behøver ikke strøm for at fungere; det elektriske signal skabes udelukkende af mikrofonen.

    ![Patti Smith synger i en Shure SM58 (dynamisk cardioid-type) mikrofon](../../../../../translated_images/da/dynamic-mic.8babac890a2d80df.webp)

* Bånd - Båndmikrofoner ligner dynamiske mikrofoner, men de har et metalbånd i stedet for en membran. Dette bånd bevæger sig i et magnetfelt og genererer en elektrisk strøm. Ligesom dynamiske mikrofoner behøver båndmikrofoner ikke strøm for at fungere.

    ![Edmund Lowe, amerikansk skuespiller, står ved en radiomikrofon (mærket for (NBC) Blue Network), holder manuskript, 1942](../../../../../translated_images/da/ribbon-mic.eacc8e092c7441ca.webp)

* Kondensator - Kondensatormikrofoner har en tynd metalmembran og en fast metalbagplade. Elektricitet påføres begge dele, og når membranen vibrerer, ændres den statiske ladning mellem pladerne og genererer et signal. Kondensatormikrofoner kræver strøm for at fungere - kaldet *Phantom power*.

    ![C451B små-membran kondensatormikrofon fra AKG Acoustics](../../../../../translated_images/da/condenser-mic.6f6ed5b76ca19e0e.webp)

* MEMS - Mikroelektromekaniske systemmikrofoner, eller MEMS, er mikrofoner på en chip. De har en trykfølsom membran ætset på en siliciumchip og fungerer på samme måde som en kondensatormikrofon. Disse mikrofoner kan være meget små og integreret i kredsløb.

    ![En MEMS-mikrofon på et kredsløb](../../../../../translated_images/da/mems-microphone.80574019e1f5e4d9.webp)

    På billedet ovenfor er chippen mærket **LEFT** en MEMS-mikrofon med en lille membran mindre end en millimeter bred.

✅ Undersøg: Hvilke mikrofoner har du omkring dig - enten i din computer, din telefon, dit headset eller i andre enheder? Hvilken type mikrofoner er det?

### Digital lyd

Lyd er et analogt signal, der bærer meget detaljeret information. For at konvertere dette signal til digitalt skal lyden samples mange tusinde gange i sekundet.

> 🎓 Sampling er processen med at konvertere lydsignalet til en digital værdi, der repræsenterer signalet på det pågældende tidspunkt.

![Et linjediagram, der viser et signal med diskrete punkter på faste intervaller](../../../../../translated_images/da/sampling.6f4fadb3f2d9dfe7.webp)

Digital lyd samples ved hjælp af Pulse Code Modulation, eller PCM. PCM indebærer at aflæse spændingen af signalet og vælge den nærmeste diskrete værdi til den spænding ved hjælp af en defineret størrelse.

> 💁 Du kan tænke på PCM som sensorversionen af pulsbreddemodulation, eller PWM (PWM blev dækket tilbage i [lektion 3 af introduktionsprojektet](../../../1-getting-started/lessons/3-sensors-and-actuators/README.md#pulse-width-modulation)). PCM indebærer at konvertere et analogt signal til digitalt, PWM indebærer at konvertere et digitalt signal til analogt.

For eksempel tilbyder de fleste streamingtjenester 16-bit eller 24-bit lyd. Det betyder, at de konverterer spændingen til en værdi, der passer ind i et 16-bit heltal eller 24-bit heltal. 16-bit lyd passer ind i en værdi, der spænder fra -32.768 til 32.767, 24-bit spænder fra −8.388.608 til 8.388.607. Jo flere bits, desto tættere er samplingen på det, vores ører faktisk hører.

> 💁 Du har måske hørt om 8-bit lyd, ofte kaldet LoFi. Dette er lyd samplet med kun 8 bits, altså -128 til 127. Den første computerlyd var begrænset til 8 bits på grund af hardwarebegrænsninger, så dette ses ofte i retrospil.

Disse samples tages mange tusinde gange i sekundet ved hjælp af veldefinerede samplingshastigheder målt i KHz (tusind aflæsninger pr. sekund). Streamingtjenester bruger 48KHz til de fleste lydfiler, men nogle 'lossless' lydfiler bruger op til 96KHz eller endda 192KHz. Jo højere samplingshastighed, desto tættere er lyden på originalen, op til et punkt. Der er debat om, hvorvidt mennesker kan høre forskel over 48KHz.

✅ Undersøg: Hvis du bruger en streamingtjeneste, hvilken samplingshastighed og størrelse bruger den? Hvis du bruger CD'er, hvad er samplingshastigheden og størrelsen på CD-lyd?

Der findes en række forskellige formater for lyddata. Du har sikkert hørt om mp3-filer - lyddata, der er komprimeret for at gøre dem mindre uden at miste kvalitet. Ukomprimeret lyd gemmes ofte som en WAV-fil - dette er en fil med 44 bytes headerinformation efterfulgt af rå lyddata. Headeren indeholder information som samplingshastighed (for eksempel 16000 for 16KHz) og sample-størrelse (16 for 16-bit) samt antallet af kanaler. Efter headeren indeholder WAV-filen de rå lyddata.

> 🎓 Kanaler refererer til, hvor mange forskellige lydstrømme der udgør lyden. For eksempel, for stereo-lyd med venstre og højre, ville der være 2 kanaler. For 7.1 surround sound til et hjemmebiografsystem ville dette være 8.

### Lyddata størrelse

Lyddata er relativt store. For eksempel, optagelse af ukomprimeret 16-bit lyd ved 16KHz (en tilstrækkelig hastighed til brug med tale-til-tekst-modeller) kræver 32KB data for hvert sekund af lyd:

* 16-bit betyder 2 bytes pr. sample (1 byte er 8 bits).
* 16KHz er 16.000 samples pr. sekund.
* 16.000 x 2 bytes = 32.000 bytes pr. sekund.

Dette lyder som en lille mængde data, men hvis du bruger en mikrocontroller med begrænset hukommelse, kan det være meget. For eksempel har Wio Terminal 192KB hukommelse, og den skal opbevare programkode og variabler. Selv hvis din programkode var meget lille, kunne du ikke optage mere end 5 sekunder lyd.

Mikrocontrollere kan få adgang til ekstra lagerplads, såsom SD-kort eller flash-hukommelse. Når du bygger en IoT-enhed, der optager lyd, skal du sikre dig, at du ikke kun har ekstra lagerplads, men også at din kode skriver den optagede lyd fra mikrofonen direkte til lageret. Når du sender det til skyen, skal du streame fra lageret til webanmodningen. På den måde undgår du at løbe tør for hukommelse ved at forsøge at holde hele lydblokken i hukommelsen på én gang.

## Optag lyd fra din IoT-enhed

Din IoT-enhed kan tilsluttes en mikrofon for at optage lyd, klar til konvertering til tekst. Den kan også tilsluttes højttalere for at afspille lyd. I senere lektioner vil dette blive brugt til at give lydfeedback, men det er nyttigt at opsætte højttalere nu for at teste mikrofonen.

### Opgave - konfigurer din mikrofon og højttalere

Følg den relevante vejledning for at konfigurere mikrofonen og højttalerne til din IoT-enhed:

* [Arduino - Wio Terminal](wio-terminal-microphone.md)
* [Single-board computer - Raspberry Pi](pi-microphone.md)
* [Single-board computer - Virtuel enhed](virtual-device-microphone.md)

### Opgave - optag lyd

Følg den relevante vejledning for at optage lyd på din IoT-enhed:

* [Arduino - Wio Terminal](wio-terminal-audio.md)
* [Single-board computer - Raspberry Pi](pi-audio.md)
* [Single-board computer - Virtuel enhed](virtual-device-audio.md)

## Tale til tekst

Tale til tekst, eller talegenkendelse, indebærer brug af AI til at konvertere ord i et lydsignal til tekst.

### Talegenkendelsesmodeller

For at konvertere tale til tekst grupperes samples fra lydsignalet og føres ind i en maskinlæringsmodel baseret på et Recurrent Neural Network (RNN). Dette er en type maskinlæringsmodel, der kan bruge tidligere data til at træffe beslutninger om indkommende data. For eksempel kunne RNN'en registrere én blok af lydsamples som lyden 'Hel', og når den modtager en anden blok, som den tror er lyden 'lo', kan den kombinere dette med den tidligere lyd, finde ud af at 'Hello' er et gyldigt ord og vælge det som resultat.

ML-modeller accepterer altid data af samme størrelse hver gang. Billedklassifikatoren, du byggede i en tidligere lektion, ændrer størrelsen på billeder til en fast størrelse og behandler dem. Det samme gælder for tale-modeller; de skal behandle faste størrelser af lydstykker. Tale-modeller skal kunne kombinere output fra flere forudsigelser for at få svaret, så de kan skelne mellem 'Hi' og 'Highway' eller 'flock' og 'floccinaucinihilipilification'.

Tale-modeller er også avancerede nok til at forstå kontekst og kan rette de ord, de registrerer, efterhånden som flere lyde behandles. For eksempel, hvis du siger "Jeg gik til butikkerne for at købe to bananer og et æble også", ville du bruge tre ord, der lyder ens, men staves forskelligt - to, to og too. Tale-modeller er i stand til at forstå konteksten og bruge den korrekte stavemåde af ordet.
💁 Nogle taletjenester tillader tilpasning, så de fungerer bedre i støjende miljøer som fabrikker, eller med branchespecifikke ord som kemiske navne. Disse tilpasninger trænes ved at levere prøveoptagelser og en transskription og fungerer ved hjælp af transfer learning, på samme måde som du tidligere trænede en billedklassifikator med kun få billeder i en tidligere lektion.
### Privatliv

Når man bruger tale-til-tekst på en forbruger-IoT-enhed, er privatliv ekstremt vigtigt. Disse enheder lytter kontinuerligt til lyd, så som forbruger ønsker man ikke, at alt, hvad man siger, bliver sendt til skyen og konverteret til tekst. Ikke alene vil dette bruge en masse internetbåndbredde, det har også store privatlivsmæssige konsekvenser, især når nogle producenter af smarte enheder tilfældigt udvælger lyd for [mennesker til at validere mod den genererede tekst for at forbedre deres model](https://www.theverge.com/2019/4/10/18305378/amazon-alexa-ai-voice-assistant-annotation-listen-private-recordings).

Man ønsker kun, at ens smarte enhed sender lyd til skyen til behandling, når man bruger den, ikke når den hører lyd i hjemmet, som kan inkludere private møder eller intime interaktioner. De fleste smarte enheder fungerer ved hjælp af et *vågningsord*, en nøglefrase som "Alexa", "Hey Siri" eller "OK Google", der får enheden til at 'vågne op' og lytte til, hvad man siger, indtil den registrerer en pause i talen, hvilket indikerer, at man er færdig med at tale til enheden.

> 🎓 Vågningsordsdetektion kaldes også *Keyword spotting* eller *Keyword recognition*.

Disse vågningsord registreres på enheden, ikke i skyen. Disse smarte enheder har små AI-modeller, der kører på enheden og lytter efter vågningsordet, og når det registreres, begynder de at streame lyden til skyen for genkendelse. Disse modeller er meget specialiserede og lytter kun efter vågningsordet.

> 💁 Nogle teknologivirksomheder tilføjer mere privatliv til deres enheder og udfører en del af tale-til-tekst-konverteringen på enheden. Apple har annonceret, at som en del af deres 2021 iOS- og macOS-opdateringer vil de understøtte tale-til-tekst-konvertering på enheden og kunne håndtere mange forespørgsler uden at skulle bruge skyen. Dette er muligt takket være kraftige processorer i deres enheder, der kan køre ML-modeller.

✅ Hvad mener du er de privatlivs- og etiske konsekvenser ved at gemme den lyd, der sendes til skyen? Bør denne lyd gemmes, og hvis ja, hvordan? Synes du, at brugen af optagelser til retshåndhævelse er en god afvejning i forhold til tabet af privatliv?

Vågningsordsdetektion bruger normalt en teknik kendt som TinyML, som er at konvertere ML-modeller til at kunne køre på mikrocontrollere. Disse modeller er små i størrelse og bruger meget lidt strøm til at køre.

For at undgå kompleksiteten ved at træne og bruge en vågningsordsmodel vil den smarte timer, du bygger i denne lektion, bruge en knap til at aktivere talegenkendelsen.

> 💁 Hvis du vil prøve at skabe en vågningsordsdetektionsmodel til at køre på Wio Terminal eller Raspberry Pi, kan du tjekke denne [vejledning om at reagere på din stemme fra Edge Impulse](https://docs.edgeimpulse.com/docs/responding-to-your-voice). Hvis du vil bruge din computer til dette, kan du prøve [kom godt i gang med Custom Keyword quickstart på Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/keyword-recognition-overview?WT.mc_id=academic-17441-jabenn).

## Konverter tale til tekst

![Logo for taletjenester](../../../../../translated_images/da/azure-speech-logo.a1f08c4befb0159f.webp)

Ligesom med billedklassifikation i et tidligere projekt findes der forudbyggede AI-tjenester, der kan tage tale som en lydfil og konvertere det til tekst. En sådan tjeneste er Speech Service, en del af Cognitive Services, forudbyggede AI-tjenester, du kan bruge i dine apps.

### Opgave - konfigurer en tale-AI-ressource

1. Opret en Ressourcegruppe til dette projekt kaldet `smart-timer`.

1. Brug følgende kommando til at oprette en gratis taleressource:

    ```sh
    az cognitiveservices account create --name smart-timer \
                                        --resource-group smart-timer \
                                        --kind SpeechServices \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Erstat `<location>` med den placering, du brugte, da du oprettede Ressourcegruppen.

1. Du skal bruge en API-nøgle for at få adgang til taleressourcen fra din kode. Kør følgende kommando for at få nøglen:

    ```sh
    az cognitiveservices account keys list --name smart-timer \
                                           --resource-group smart-timer \
                                           --output table
    ```

    Tag en kopi af en af nøglerne.

### Opgave - konverter tale til tekst

Gennemgå den relevante vejledning for at konvertere tale til tekst på din IoT-enhed:

* [Arduino - Wio Terminal](wio-terminal-speech-to-text.md)
* [Single-board computer - Raspberry Pi](pi-speech-to-text.md)
* [Single-board computer - Virtuel enhed](virtual-device-speech-to-text.md)

---

## 🚀 Udfordring

Talegenkendelse har eksisteret i lang tid og forbedres kontinuerligt. Undersøg de nuværende muligheder og sammenlign, hvordan disse har udviklet sig over tid, herunder hvor præcise maskintransskriptioner er sammenlignet med menneskelige.

Hvad tror du, fremtiden bringer for talegenkendelse?

## Quiz efter lektionen

[Quiz efter lektionen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/42)

## Gennemgang & Selvstudie

* Læs om de forskellige mikrofontyper, og hvordan de fungerer, i artiklen [hvad er forskellen mellem dynamiske og kondensatormikrofoner på Musician's HQ](https://musicianshq.com/whats-the-difference-between-dynamic-and-condenser-microphones/).
* Læs mere om Cognitive Services taletjeneste i [taletjenestens dokumentation på Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/?WT.mc_id=academic-17441-jabenn).
* Læs om keyword spotting i [dokumentationen om keyword recognition på Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/keyword-recognition-overview?WT.mc_id=academic-17441-jabenn).

## Opgave

[](assignment.md)

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på at sikre nøjagtighed, skal det bemærkes, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.