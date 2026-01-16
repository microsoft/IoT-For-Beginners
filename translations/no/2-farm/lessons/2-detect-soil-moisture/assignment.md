<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "506d21b544d5de47406c89ad496a21cd",
  "translation_date": "2025-08-27T22:28:27+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/assignment.md",
  "language_code": "no"
}
-->
# Kalibrer sensoren din

## Instruksjoner

I denne leksjonen samlet du avlesninger fra jordfuktighetssensoren, målt som verdier fra 0-1023. For å konvertere disse til faktiske jordfuktighetsavlesninger, må du kalibrere sensoren din. Dette kan du gjøre ved å ta avlesninger fra jordprøver og deretter beregne gravimetrisk jordfuktighetsinnhold fra disse prøvene.

Du må gjenta disse trinnene flere ganger for å få de nødvendige avlesningene, med ulik fuktighet i jorden hver gang.

1. Ta en jordfuktighetsavlesning ved hjelp av jordfuktighetssensoren. Noter denne avlesningen.

1. Ta en prøve av jorden og vei den. Noter vekten.

1. Tørk jorden – en varm ovn på 110°C (230°F) i noen timer er den beste metoden. Du kan også gjøre dette i sollys eller plassere den på et varmt, tørt sted til jorden er helt tørr. Den skal være pulveraktig og løs.

    > 💁 På et laboratorium, for de mest nøyaktige resultatene, ville du tørke jorden i en ovn i 48-72 timer. Hvis skolen din har tørkeovner, se om du kan bruke disse til å tørke prøvene lenger. Jo lengre tørketid, desto tørrere prøve og mer nøyaktige resultater.

1. Vei jorden igjen.

    > 🔥 Hvis du tørket den i en ovn, sørg for at den har kjølt seg ned først!

Den gravimetriske jordfuktigheten beregnes som:

![jordfuktighet % er vekt våt minus vekt tørr, delt på vekt tørr, ganger 100](../../../../../translated_images/no/gsm-calculation.6da38c6201eec14e7573bb2647aa18892883193553d23c9d77e5dc681522dfb2.png)

* W - vekten av den våte jorden
* W - vekten av den tørre jorden

For eksempel, si at du har en jordprøve som veier 212g våt og 197g tørr.

![Beregningen fylt inn](../../../../../translated_images/no/gsm-calculation-example.99f9803b4f29e97668e7c15412136c0c399ab12dbba0b89596fdae9d8aedb6fb.png)

* W = 212g
* W = 197g
* 212 - 197 = 15
* 15 / 197 = 0.076
* 0.076 * 100 = 7.6%

I dette eksemplet har jorden en gravimetrisk jordfuktighet på 7.6%.

Når du har avlesninger for minst 3 prøver, lag en graf over jordfuktighet % mot jordfuktighetssensoravlesning og legg til en linje som best passer punktene. Du kan deretter bruke denne til å beregne gravimetrisk jordfuktighetsinnhold for en gitt sensoravlesning ved å lese verdien fra linjen.

## Vurderingskriterier

| Kriterier | Fremragende | Tilfredsstillende | Trenger forbedring |
| --------- | ----------- | ----------------- | ------------------ |
| Samle kalibreringsdata | Samle minst 3 kalibreringsprøver | Samle minst 2 kalibreringsprøver | Samle minst 1 kalibreringsprøve |
| Gjøre en kalibrert avlesning | Plotte kalibreringsgrafen og gjøre en avlesning fra sensoren, og konvertere den til gravimetrisk jordfuktighetsinnhold | Plotte kalibreringsgrafen | Ikke i stand til å plotte grafen |

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiske oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.