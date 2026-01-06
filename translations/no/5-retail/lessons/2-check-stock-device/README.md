<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1c9e5fa8b7be726c75a97232b1e41c97",
  "translation_date": "2025-08-27T22:17:12+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/README.md",
  "language_code": "no"
}
-->
# Sjekk lagerbeholdning fra en IoT-enhet

![En sketchnote-oversikt over denne leksjonen](../../../../../translated_images/lesson-20.0211df9551a8abb300fc8fcf7dc2789468dea2eabe9202273ac077b0ba37f15e.no.jpg)

> Sketchnote av [Nitya Narasimhan](https://github.com/nitya). Klikk på bildet for en større versjon.

## Quiz før leksjonen

[Quiz før leksjonen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/39)

## Introduksjon

I forrige leksjon lærte du om de ulike bruksområdene for objektdeteksjon i detaljhandel. Du lærte også hvordan du trener en objektdetektor til å identifisere lagerbeholdning. I denne leksjonen vil du lære hvordan du bruker objektdetektoren fra din IoT-enhet for å telle lagerbeholdning.

I denne leksjonen dekker vi:

* [Lagerbeholdningstelling](../../../../../5-retail/lessons/2-check-stock-device)
* [Kall objektdetektoren fra din IoT-enhet](../../../../../5-retail/lessons/2-check-stock-device)
* [Avgrensningsbokser](../../../../../5-retail/lessons/2-check-stock-device)
* [Tren modellen på nytt](../../../../../5-retail/lessons/2-check-stock-device)
* [Tell lagerbeholdning](../../../../../5-retail/lessons/2-check-stock-device)

> 🗑 Dette er den siste leksjonen i dette prosjektet, så etter at du har fullført denne leksjonen og oppgaven, ikke glem å rydde opp i skyressursene dine. Du vil trenge ressursene for å fullføre oppgaven, så sørg for å gjøre det først.
>
> Se [veiledningen for å rydde opp i prosjektet ditt](../../../clean-up.md) hvis du trenger instruksjoner for hvordan du gjør dette.

## Lagerbeholdningstelling

Objektdetektorer kan brukes til lagerkontroll, enten for å telle lagerbeholdning eller for å sikre at lageret er der det skal være. IoT-enheter med kameraer kan plasseres rundt i butikken for å overvåke lageret, med fokus på områder der det er viktig å ha varer på lager, som steder med få, men verdifulle varer.

For eksempel, hvis et kamera peker mot en hylle som kan holde 8 bokser med tomatpuré, og en objektdetektor bare oppdager 7 bokser, mangler én og må fylles på.

![7 bokser med tomatpuré på en hylle, 4 på øverste rad, 3 på nederste rad](../../../../../translated_images/stock-7-cans-tomato-paste.f86059cc573d7bec.no.png)

I bildet ovenfor har en objektdetektor oppdaget 7 bokser med tomatpuré på en hylle som kan holde 8 bokser. Ikke bare kan IoT-enheten sende en melding om behovet for påfyll, men den kan også gi en indikasjon på hvor den manglende varen befinner seg, viktig informasjon hvis du bruker roboter til å fylle på hyllene.

> 💁 Avhengig av butikken og populariteten til varen, ville påfyll sannsynligvis ikke skje hvis bare én boks mangler. Du må bygge en algoritme som avgjør når påfyll skal skje basert på produktet, kundene og andre kriterier.

✅ I hvilke andre situasjoner kan du kombinere objektdeteksjon og roboter?

Noen ganger kan feil varer havne på hyllene. Dette kan skyldes menneskelige feil under påfylling, eller kunder som ombestemmer seg og legger en vare tilbake på første tilgjengelige plass. Når dette gjelder varer som ikke er lett bedervelige, som hermetikk, er det en irritasjon. Hvis det gjelder lett bedervelige varer som frosne eller kjølte produkter, kan det bety at varen ikke lenger kan selges, da det kan være umulig å vite hvor lenge varen har vært ute av fryseren.

Objektdeteksjon kan brukes til å oppdage uventede varer, og varsle en person eller robot om å returnere varen så snart den oppdages.

![En boks med babymais på tomatpuréhylle](../../../../../translated_images/stock-rogue-corn.be1f3ada8c457854.no.png)

I bildet ovenfor har en boks med babymais blitt plassert på hyllen ved siden av tomatpuréen. Objektdetektoren har oppdaget dette, slik at IoT-enheten kan varsle en person eller robot om å returnere boksen til riktig plass.

## Kall objektdetektoren fra din IoT-enhet

Objektdetektoren du trente i forrige leksjon kan kalles fra din IoT-enhet.

### Oppgave - publiser en iterasjon av objektdetektoren din

Iterasjoner publiseres fra Custom Vision-portalen.

1. Åpne Custom Vision-portalen på [CustomVision.ai](https://customvision.ai) og logg inn hvis du ikke allerede har den åpen. Deretter åpner du prosjektet ditt `stock-detector`.

1. Velg **Performance**-fanen fra alternativene øverst.

1. Velg den nyeste iterasjonen fra listen *Iterations* på siden.

1. Klikk på **Publish**-knappen for iterasjonen.

    ![Publiser-knappen](../../../../../translated_images/custom-vision-object-detector-publish-button.34ee379fc650ccb9856c3868d0003f413b9529f102fc73c37168c98d721cc293.no.png)

1. I dialogboksen *Publish Model*, sett *Prediction resource* til ressursen `stock-detector-prediction` som du opprettet i forrige leksjon. La navnet være `Iteration2`, og klikk på **Publish**-knappen.

1. Når den er publisert, klikker du på **Prediction URL**-knappen. Dette vil vise detaljer om prediksjons-API-en, og du vil trenge disse for å kalle modellen fra din IoT-enhet. Den nederste delen er merket *If you have an image file*, og dette er detaljene du trenger. Ta en kopi av URL-en som vises, som vil være noe som:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/detect/iterations/Iteration2/image
    ```

    Der `<location>` vil være stedet du brukte da du opprettet din Custom Vision-ressurs, og `<id>` vil være en lang ID bestående av bokstaver og tall.

    Ta også en kopi av verdien *Prediction-Key*. Dette er en sikker nøkkel som du må sende når du kaller modellen. Bare applikasjoner som sender denne nøkkelen har lov til å bruke modellen, alle andre applikasjoner blir avvist.

    ![Dialogboksen for prediksjons-API som viser URL og nøkkel](../../../../../translated_images/custom-vision-prediction-key-endpoint.30c569ffd0338864f319911f052d5e9b8c5066cb0800a26dd6f7ff5713130ad8.no.png)

✅ Når en ny iterasjon publiseres, vil den ha et annet navn. Hvordan tror du du ville endret iterasjonen en IoT-enhet bruker?

### Oppgave - kall objektdetektoren fra din IoT-enhet

Følg den relevante veiledningen nedenfor for å bruke objektdetektoren fra din IoT-enhet:

* [Arduino - Wio Terminal](wio-terminal-object-detector.md)
* [Enkeltkortdatamaskin - Raspberry Pi/virtuell enhet](single-board-computer-object-detector.md)

## Avgrensningsbokser

Når du bruker objektdetektoren, får du ikke bare tilbake de oppdagede objektene med deres tagger og sannsynligheter, men også avgrensningsboksene for objektene. Disse definerer hvor objektdetektoren oppdaget objektet med den gitte sannsynligheten.

> 💁 En avgrensningsboks er en boks som definerer området som inneholder det oppdagede objektet, en boks som definerer grensen for objektet.

Resultatene av en prediksjon i **Predictions**-fanen i Custom Vision har avgrensningsboksene tegnet på bildet som ble sendt for prediksjon.

![4 bokser med tomatpuré på en hylle med prediksjoner for de 4 oppdagelsene med 35.8%, 33.5%, 25.7% og 16.6%](../../../../../translated_images/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.no.png)

I bildet ovenfor ble 4 bokser med tomatpuré oppdaget. I resultatene er en rød firkant lagt over hvert objekt som ble oppdaget i bildet, som indikerer avgrensningsboksen for bildet.

✅ Åpne prediksjonene i Custom Vision og sjekk avgrensningsboksene.

Avgrensningsbokser er definert med 4 verdier - topp, venstre, høyde og bredde. Disse verdiene er på en skala fra 0-1, som representerer posisjonene som en prosentandel av størrelsen på bildet. Origo (posisjonen 0,0) er øverst til venstre på bildet, så toppverdien er avstanden fra toppen, og bunnen av avgrensningsboksen er toppen pluss høyden.

![En avgrensningsboks rundt en boks med tomatpuré](../../../../../translated_images/bounding-box.1420a7ea0d3d15f71e1ffb5cf4b2271d184fac051f990abc541975168d163684.no.png)

Bildet ovenfor er 600 piksler bredt og 800 piksler høyt. Avgrensningsboksen starter 320 piksler ned, som gir en toppkoordinat på 0.4 (800 x 0.4 = 320). Fra venstre starter avgrensningsboksen 240 piksler inn, som gir en venstrekoordinat på 0.4 (600 x 0.4 = 240). Høyden på avgrensningsboksen er 240 piksler, som gir en høydeverdi på 0.3 (800 x 0.3 = 240). Bredden på avgrensningsboksen er 120 piksler, som gir en breddeverdi på 0.2 (600 x 0.2 = 120).

| Koordinat | Verdi |
| ---------- | ----: |
| Topp       | 0.4   |
| Venstre    | 0.4   |
| Høyde      | 0.3   |
| Bredde     | 0.2   |

Ved å bruke prosentverdier fra 0-1 betyr det at uansett hvilken størrelse bildet skaleres til, starter avgrensningsboksen 0.4 av veien langs og ned, og er 0.3 av høyden og 0.2 av bredden.

Du kan bruke avgrensningsbokser kombinert med sannsynligheter for å evaluere hvor nøyaktig en oppdagelse er. For eksempel kan en objektdetektor oppdage flere objekter som overlapper, for eksempel oppdage én boks inne i en annen. Koden din kan se på avgrensningsboksene, forstå at dette er umulig, og ignorere eventuelle objekter som har betydelig overlapping med andre objekter.

![To avgrensningsbokser som overlapper en boks med tomatpuré](../../../../../translated_images/overlap-object-detection.d431e03cae75072a2760430eca7f2c5fdd43045bfd72dadcbf12711f7cd6c2ae.no.png)

I eksempelet ovenfor indikerer én avgrensningsboks en oppdaget boks med tomatpuré med 78.3%. En annen avgrensningsboks er litt mindre og er inne i den første boksen med en sannsynlighet på 64.3%. Koden din kan sjekke avgrensningsboksene, se at de overlapper fullstendig, og ignorere den lavere sannsynligheten, da det ikke er mulig at én boks er inne i en annen.

✅ Kan du tenke deg en situasjon der det er gyldig å oppdage ett objekt inne i et annet?

## Tren modellen på nytt

Som med bildekategorisering, kan du trene modellen din på nytt ved å bruke data samlet inn av din IoT-enhet. Å bruke disse dataene fra virkeligheten vil sikre at modellen din fungerer godt når den brukes fra din IoT-enhet.

I motsetning til bildekategorisering, kan du ikke bare tagge et bilde. I stedet må du gjennomgå hver avgrensningsboks som modellen har oppdaget. Hvis boksen er rundt feil ting, må den slettes, og hvis den er på feil sted, må den justeres.

### Oppgave - tren modellen på nytt

1. Sørg for at du har samlet inn et utvalg bilder ved hjelp av din IoT-enhet.

1. Fra **Predictions**-fanen, velg et bilde. Du vil se røde bokser som indikerer avgrensningsboksene for de oppdagede objektene.

1. Gå gjennom hver avgrensningsboks. Velg den først, og du vil se en pop-up som viser taggen. Bruk håndtakene på hjørnene av avgrensningsboksen for å justere størrelsen hvis nødvendig. Hvis taggen er feil, fjern den med **X**-knappen og legg til riktig tag. Hvis avgrensningsboksen ikke inneholder et objekt, slett den med søppelbøtteknappen.

1. Lukk redigeringsverktøyet når du er ferdig, og bildet vil flytte seg fra **Predictions**-fanen til **Training Images**-fanen. Gjenta prosessen for alle prediksjonene.

1. Bruk **Train**-knappen for å trene modellen din på nytt. Når den er trent, publiser iterasjonen og oppdater IoT-enheten din til å bruke URL-en til den nye iterasjonen.

1. Re-deploy koden din og test IoT-enheten din.

## Tell lagerbeholdning

Ved å kombinere antall oppdagede objekter og avgrensningsboksene kan du telle lagerbeholdningen på en hylle.

### Oppgave - tell lagerbeholdning

Følg den relevante veiledningen nedenfor for å telle lagerbeholdning ved hjelp av resultatene fra objektdetektoren fra din IoT-enhet:

* [Arduino - Wio Terminal](wio-terminal-count-stock.md)
* [Enkeltkortdatamaskin - Raspberry Pi/virtuell enhet](single-board-computer-count-stock.md)

---

## 🚀 Utfordring

Kan du oppdage feil lagerbeholdning? Tren modellen din på flere objekter, og oppdater appen din til å varsle deg hvis feil lager oppdages.

Kanskje du kan ta dette et steg videre og oppdage lagerbeholdning side om side på samme hylle, og se om noe har blitt plassert på feil sted ved å definere grenser for avgrensningsboksene.

## Quiz etter leksjonen

[Quiz etter leksjonen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/40)

## Gjennomgang og selvstudium

* Lær mer om hvordan du kan designe et ende-til-ende lagerdeteksjonssystem fra [Out of stock detection at the edge pattern guide på Microsoft Docs](https://docs.microsoft.com/hybrid/app-solutions/pattern-out-of-stock-at-edge?WT.mc_id=academic-17441-jabenn)
* Lær andre måter å bygge ende-til-ende løsninger for detaljhandel ved å kombinere en rekke IoT- og sky-tjenester ved å se denne [Behind the scenes of a retail solution - Hands On! video på YouTube](https://www.youtube.com/watch?v=m3Pc300x2Mw).

## Oppgave

[Bruk objektdetektoren din på kanten](assignment.md)

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiske oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.