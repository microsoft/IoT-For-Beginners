<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c16de27b0074abe81d6a8bad5e5b1a6b",
  "translation_date": "2025-08-27T21:13:47+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/README.md",
  "language_code": "no"
}
-->
# Støtte for flere språk

![En sketchnote-oversikt over denne leksjonen](../../../../../translated_images/no/lesson-24.4246968ed058510ab275052e87ef9aa89c7b2f938915d103c605c04dc6cd5bb7.jpg)

> Sketchnote av [Nitya Narasimhan](https://github.com/nitya). Klikk på bildet for en større versjon.

Denne videoen gir en oversikt over Azure tale-tjenester, inkludert tale til tekst og tekst til tale fra tidligere leksjoner, samt oversettelse av tale, som er temaet i denne leksjonen:

[![Gjenkjenne tale med noen få linjer Python fra Microsoft Build 2020](https://img.youtube.com/vi/h6xbpMPSGEA/0.jpg)](https://www.youtube.com/watch?v=h6xbpMPSGEA)

> 🎥 Klikk på bildet over for å se videoen

## Quiz før leksjonen

[Quiz før leksjonen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/47)

## Introduksjon

I de siste tre leksjonene lærte du om å konvertere tale til tekst, språkforståelse og konvertere tekst til tale, alt drevet av AI. Et annet område innen menneskelig kommunikasjon der AI kan hjelpe, er språköversettelse – å konvertere fra ett språk til et annet, for eksempel fra engelsk til fransk.

I denne leksjonen vil du lære om å bruke AI til å oversette tekst, slik at din smarte timer kan samhandle med brukere på flere språk.

I denne leksjonen dekker vi:

* [Oversette tekst](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Oversettelsestjenester](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Opprette en oversetterressurs](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Støtte flere språk i applikasjoner med oversettelser](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Oversette tekst ved hjelp av en AI-tjeneste](../../../../../6-consumer/lessons/4-multiple-language-support)

> 🗑 Dette er den siste leksjonen i dette prosjektet, så etter å ha fullført denne leksjonen og oppgaven, ikke glem å rydde opp i skyressursene dine. Du vil trenge ressursene for å fullføre oppgaven, så sørg for å gjøre det først.
>
> Se [veiledningen for å rydde opp i prosjektet ditt](../../../clean-up.md) hvis nødvendig for instruksjoner om hvordan du gjør dette.

## Oversette tekst

Tekstoversettelse har vært et datavitenskapelig problem som har blitt forsket på i over 70 år, og først nå, takket være fremskritt innen AI og datakraft, nærmer det seg en løsning som er nesten like god som menneskelige oversettere.

> 💁 Opprinnelsen kan spores enda lenger tilbake, til [Al-Kindi](https://wikipedia.org/wiki/Al-Kindi), en arabisk kryptograf fra 800-tallet som utviklet teknikker for språkoversettelse.

### Maskinoversettelser

Tekstoversettelse startet som en teknologi kjent som maskinoversettelse (MT), som kan oversette mellom ulike språkpar. MT fungerer ved å erstatte ord på ett språk med et annet, og legge til teknikker for å velge de riktige måtene å oversette fraser eller deler av setninger på når en enkel ord-for-ord-oversettelse ikke gir mening.

> 🎓 Når oversettere støtter oversettelse mellom ett språk og et annet, kalles disse for *språkpar*. Ulike verktøy støtter ulike språkpar, og disse kan være ufullstendige. For eksempel kan en oversetter støtte engelsk til spansk som et språkpar, og spansk til italiensk som et språkpar, men ikke engelsk til italiensk.

For eksempel kan oversettelsen av "Hello world" fra engelsk til fransk utføres med en substitusjon – "Bonjour" for "Hello", og "le monde" for "world", noe som gir den korrekte oversettelsen "Bonjour le monde".

Substitusjoner fungerer ikke når ulike språk bruker forskjellige måter å si det samme på. For eksempel oversettes den engelske setningen "My name is Jim" til "Je m'appelle Jim" på fransk – bokstavelig talt "Jeg kaller meg Jim". "Je" er fransk for "jeg", "moi" er "meg", men det er sammensatt med verbet fordi det starter med en vokal, så det blir "m'", "appelle" betyr "å kalle", og "Jim" oversettes ikke fordi det er et navn og ikke et ord som kan oversettes. Også ordrekkefølgen blir et problem – en enkel substitusjon av "Je m'appelle Jim" blir "I myself call Jim", med en annen ordrekkefølge enn på engelsk.

> 💁 Noen ord oversettes aldri – navnet mitt er Jim uansett hvilket språk som brukes for å introdusere meg. Når man oversetter til språk som bruker andre alfabeter, eller bruker andre bokstaver for ulike lyder, kan ord bli *transliterert*, det vil si at man velger bokstaver eller tegn som gir den riktige lyden for å høres ut som det opprinnelige ordet.

Idiomer er også et problem for oversettelse. Dette er uttrykk som har en forstått betydning som er forskjellig fra en direkte tolkning av ordene. For eksempel, på engelsk betyr idiomet "I've got ants in my pants" ikke bokstavelig at man har maur i klærne, men at man er rastløs. Hvis du oversetter dette til tysk, vil du forvirre lytteren, da den tyske versjonen er "Ich habe Hummeln im Hintern".

> 💁 Ulike lokaliteter legger til ulike kompleksiteter. Med idiomet "ants in your pants", refererer "pants" i amerikansk engelsk til yttertøy, mens "pants" i britisk engelsk betyr undertøy.

✅ Hvis du snakker flere språk, tenk på noen uttrykk som ikke kan oversettes direkte.

Maskinoversettelsessystemer er avhengige av store databaser med regler som beskriver hvordan man oversetter visse fraser og idiomer, sammen med statistiske metoder for å velge de mest passende oversettelsene fra mulige alternativer. Disse statistiske metodene bruker enorme databaser med verk oversatt av mennesker til flere språk for å velge den mest sannsynlige oversettelsen, en teknikk kalt *statistisk maskinoversettelse*. Noen av disse bruker mellomliggende representasjoner av språket, slik at ett språk kan oversettes til det mellomliggende, og deretter fra det mellomliggende til et annet språk. På denne måten innebærer det å legge til flere språk oversettelser til og fra det mellomliggende, ikke til og fra alle andre språk.

### Nevrale oversettelser

Nevrale oversettelser bruker kraften i AI til å oversette, vanligvis ved å oversette hele setninger ved hjelp av én modell. Disse modellene trenes på enorme datasett som er oversatt av mennesker, som nettsider, bøker og FN-dokumentasjon.

Nevrale oversettelsesmodeller er vanligvis mindre enn maskinoversettelsesmodeller fordi de ikke trenger store databaser med fraser og idiomer. Moderne AI-tjenester som tilbyr oversettelser, blander ofte flere teknikker, som statistisk maskinoversettelse og nevrale oversettelser.

Det finnes ingen 1:1-oversettelse for noe språkpar. Ulike oversettelsesmodeller vil gi litt forskjellige resultater avhengig av dataene som ble brukt til å trene modellen. Oversettelser er ikke alltid symmetriske – hvis du oversetter en setning fra ett språk til et annet, og deretter tilbake til det første språket, kan du få en litt annen setning som resultat.

✅ Prøv ut ulike nettbaserte oversettere som [Bing Translate](https://www.bing.com/translator), [Google Translate](https://translate.google.com) eller Apple Translate-appen. Sammenlign de oversatte versjonene av noen setninger. Prøv også å oversette i én, og deretter oversette tilbake i en annen.

## Oversettelsestjenester

Det finnes en rekke AI-tjenester som kan brukes fra applikasjonene dine for å oversette tale og tekst.

### Cognitive Services Speech Service

![Logoen til tale-tjenesten](../../../../../translated_images/no/azure-speech-logo.a1f08c4befb0159f2cb5d692d3baf5b599e7b44759d316da907bda1508f46a4a.png)

Tale-tjenesten du har brukt i de siste leksjonene, har oversettelsesmuligheter for talegjenkjenning. Når du gjenkjenner tale, kan du be om ikke bare teksten til talen på samme språk, men også på andre språk.

> 💁 Dette er kun tilgjengelig fra tale-SDK-en, REST API-en har ikke innebygde oversettelser.

### Cognitive Services Translator Service

![Logoen til oversettertjenesten](../../../../../translated_images/no/azure-translator-logo.c6ed3a4a433edfd2f11577eca105412c50b8396b194cbbd730723dd1d0793bcd.png)

Oversettertjenesten er en dedikert oversettelsestjeneste som kan oversette tekst fra ett språk til ett eller flere målspråk. I tillegg til å oversette, støtter den et bredt spekter av ekstra funksjoner, inkludert maskering av banning. Den lar deg også spesifisere en bestemt oversettelse for et bestemt ord eller en setning, for å håndtere termer du ikke vil oversette, eller som har en spesifikk, velkjent oversettelse.

For eksempel, når du oversetter setningen "I have a Raspberry Pi", som refererer til en enkeltkortsdatamaskin, til et annet språk som fransk, vil du beholde navnet "Raspberry Pi" som det er, og ikke oversette det, noe som gir "J’ai un Raspberry Pi" i stedet for "J’ai une pi aux framboises".

## Opprette en oversetterressurs

For denne leksjonen trenger du en oversetterressurs. Du vil bruke REST API-en til å oversette tekst.

### Oppgave – opprette en oversetterressurs

1. Fra terminalen eller kommandolinjen, kjør følgende kommando for å opprette en oversetterressurs i ressursgruppen din `smart-timer`.

    ```sh
    az cognitiveservices account create --name smart-timer-translator \
                                        --resource-group smart-timer \
                                        --kind TextTranslation \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Erstatt `<location>` med plasseringen du brukte da du opprettet ressursgruppen.

1. Hent nøkkelen for oversettertjenesten:

    ```sh
    az cognitiveservices account keys list --name smart-timer-translator \
                                           --resource-group smart-timer \
                                           --output table
    ```

    Ta en kopi av en av nøklene.

## Støtte flere språk i applikasjoner med oversettelser

I en ideell verden bør hele applikasjonen din forstå så mange forskjellige språk som mulig, fra å lytte til tale, til språkforståelse, til å svare med tale. Dette er mye arbeid, så oversettelsestjenester kan fremskynde leveringstiden for applikasjonen din.

![En smart timer-arkitektur som oversetter japansk til engelsk, behandler på engelsk og deretter oversetter tilbake til japansk](../../../../../translated_images/no/translated-smart-timer.08ac20057fdc5c37.webp)

Tenk deg at du bygger en smart timer som bruker engelsk fra ende til ende, forstår talt engelsk og konverterer det til tekst, kjører språkforståelse på engelsk, bygger opp svar på engelsk og svarer med engelsk tale. Hvis du ønsket å legge til støtte for japansk, kunne du starte med å oversette talt japansk til engelsk tekst, deretter holde kjernen i applikasjonen den samme, og deretter oversette svarteksten til japansk før du snakker svaret. Dette ville tillate deg å raskt legge til støtte for japansk, og du kan senere utvide til å tilby fullstendig ende-til-ende-støtte for japansk.

> 💁 Ulempen med å stole på maskinoversettelse er at ulike språk og kulturer har forskjellige måter å si de samme tingene på, så oversettelsen kan ikke alltid matche uttrykket du forventer.

Maskinoversettelser åpner også opp muligheter for apper og enheter som kan oversette brukergenerert innhold mens det opprettes. Science fiction inneholder ofte "universelle oversettere", enheter som kan oversette fra fremmede språk til (typisk) amerikansk engelsk. Disse enhetene er mindre science fiction og mer vitenskapelig fakta, hvis du ser bort fra den fremmede delen. Det finnes allerede apper og enheter som gir sanntidsoversettelse av tale og skrevet tekst, ved hjelp av kombinasjoner av tale- og oversettelsestjenester.

Et eksempel er mobilappen [Microsoft Translator](https://www.microsoft.com/translator/apps/?WT.mc_id=academic-17441-jabenn), demonstrert i denne videoen:

[![Microsoft Translator live-funksjon i aksjon](https://img.youtube.com/vi/16yAGeP2FuM/0.jpg)](https://www.youtube.com/watch?v=16yAGeP2FuM)

> 🎥 Klikk på bildet over for å se videoen

Tenk deg å ha en slik enhet tilgjengelig, spesielt når du reiser eller samhandler med folk hvis språk du ikke kan. Å ha automatiske oversettelsesenheter på flyplasser eller sykehus ville gi sårt tiltrengte forbedringer i tilgjengelighet.

✅ Gjør litt research: Finnes det noen oversettelses-IoT-enheter kommersielt tilgjengelig? Hva med oversettelsesfunksjoner innebygd i smarte enheter?

> 👽 Selv om det ikke finnes ekte universelle oversettere som lar oss snakke med romvesener, støtter [Microsoft Translator faktisk klingonsk](https://www.microsoft.com/translator/blog/2013/05/14/announcing-klingon-for-bing-translator/?WT.mc_id=academic-17441-jabenn). Qapla’!

## Oversette tekst ved hjelp av en AI-tjeneste

Du kan bruke en AI-tjeneste til å legge til denne oversettelsesfunksjonen i din smarte timer.

### Oppgave – oversette tekst ved hjelp av en AI-tjeneste

Arbeid gjennom den relevante veiledningen for å oversette tekst på IoT-enheten din:

* [Arduino - Wio Terminal](wio-terminal-translate-speech.md)
* [Enkeltkortsdatamaskin - Raspberry Pi](pi-translate-speech.md)
* [Enkeltkortsdatamaskin - Virtuell enhet](virtual-device-translate-speech.md)

---

## 🚀 Utfordring

Hvordan kan maskinoversettelser være til nytte for andre IoT-applikasjoner utover smarte enheter? Tenk på ulike måter oversettelser kan hjelpe, ikke bare med talte ord, men også med tekst.

## Quiz etter leksjonen

[Quiz etter leksjonen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/48)

## Gjennomgang og selvstudium

* Les mer om maskinoversettelse på [maskinoversettelsessiden på Wikipedia](https://wikipedia.org/wiki/Machine_translation)
* Les mer om nevrale maskinoversettelser på [siden om nevrale maskinoversettelser på Wikipedia](https://wikipedia.org/wiki/Neural_machine_translation)
* Sjekk ut listen over støttede språk for Microsoft tale-tjenester i [dokumentasjonen for språk- og stemmestøtte for tale-tjenesten på Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn)

## Oppgave

[Bygg en universell oversetter](assignment.md)

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiske oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for eventuelle misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.