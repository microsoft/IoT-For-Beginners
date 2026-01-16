<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b73fe10ec6b580fba2affb6f6e0a5c4d",
  "translation_date": "2025-08-27T20:53:34+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/README.md",
  "language_code": "da"
}
-->
# Indstil en timer og giv mundtlig feedback

![En sketchnote-oversigt over denne lektion](../../../../../translated_images/da/lesson-23.f38483e1d4df4828990d3f02d60e46c978b075d384ae7cb4f7bab738e107c850.jpg)

> Sketchnote af [Nitya Narasimhan](https://github.com/nitya). Klik på billedet for en større version.

## Quiz før lektionen

[Quiz før lektionen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/45)

## Introduktion

Smarte assistenter er ikke envejs kommunikationsenheder. Du taler til dem, og de svarer:

"Alexa, sæt en timer på 3 minutter"

"Ok, din timer er sat til 3 minutter"

I de sidste to lektioner lærte du, hvordan man tager tale og skaber tekst, og derefter udtrækker en "sæt timer"-anmodning fra den tekst. I denne lektion vil du lære, hvordan man indstiller timeren på IoT-enheden, svarer brugeren med talte ord, der bekræfter deres timer, og giver besked, når timeren er færdig.

I denne lektion dækker vi:

* [Tekst til tale](../../../../../6-consumer/lessons/3-spoken-feedback)
* [Indstil timeren](../../../../../6-consumer/lessons/3-spoken-feedback)
* [Konverter tekst til tale](../../../../../6-consumer/lessons/3-spoken-feedback)

## Tekst til tale

Tekst til tale, som navnet antyder, er processen med at konvertere tekst til lyd, der indeholder teksten som talte ord. Den grundlæggende idé er at nedbryde ordene i teksten til deres bestanddele lyde (kendt som fonemer) og sy sammen lyd for disse lyde, enten ved hjælp af forudindspillet lyd eller lyd genereret af AI-modeller.

![De tre trin i typiske tekst-til-tale-systemer](../../../../../translated_images/da/tts-overview.193843cf3f5ee09f.webp)

Tekst-til-tale-systemer har typisk 3 trin:

* Tekstanalyse
* Lingvistisk analyse
* Bølgeforms-generering

### Tekstanalyse

Tekstanalyse indebærer at tage den givne tekst og konvertere den til ord, der kan bruges til at generere tale. For eksempel, hvis du konverterer "Hello world", er der ingen tekstanalyse nødvendig, de to ord kan konverteres direkte til tale. Hvis du derimod har "1234", skal dette muligvis konverteres til enten ordene "Et tusind to hundrede fireogtredive" eller "En, to, tre, fire" afhængigt af konteksten. For "Jeg har 1234 æbler" ville det være "Et tusind to hundrede fireogtredive", men for "Barnet talte 1234" ville det være "En, to, tre, fire".

De ord, der skabes, varierer ikke kun for sproget, men også for den lokale dialekt. For eksempel, på amerikansk engelsk ville 120 være "One hundred twenty", mens det på britisk engelsk ville være "One hundred and twenty", med brugen af "and" efter hundrederne.

✅ Nogle andre eksempler, der kræver tekstanalyse, inkluderer "in" som en forkortelse for tomme og "st" som en forkortelse for helgen eller gade. Kan du tænke på andre eksempler på dit sprog, hvor ord er tvetydige uden kontekst?

Når ordene er defineret, sendes de til lingvistisk analyse.

### Lingvistisk analyse

Lingvistisk analyse nedbryder ordene til fonemer. Fonemer er baseret ikke kun på de anvendte bogstaver, men også på de andre bogstaver i ordet. For eksempel er 'a'-lyden i 'car' og 'care' forskellig på engelsk. Det engelske sprog har 44 forskellige fonemer for de 26 bogstaver i alfabetet, nogle delt mellem forskellige bogstaver, som det samme fonem, der bruges i starten af 'circle' og 'serpent'.

✅ Lav lidt research: Hvad er fonemerne for dit sprog?

Når ordene er konverteret til fonemer, kræver disse fonemer yderligere data for at understøtte intonation, justere tone eller varighed afhængigt af konteksten. Et eksempel er, at på engelsk kan tonehøjden stige for at omdanne en sætning til et spørgsmål, hvor en hævet tonehøjde på det sidste ord antyder et spørgsmål.

For eksempel - sætningen "You have an apple" er en erklæring, der siger, at du har et æble. Hvis tonehøjden stiger til sidst, især for ordet "apple", bliver det til spørgsmålet "You have an apple?", der spørger, om du har et æble. Den lingvistiske analyse skal bruge spørgsmålstegnet til at beslutte at hæve tonehøjden.

Når fonemerne er genereret, kan de sendes til bølgeforms-generering for at producere lydoutputtet.

### Bølgeforms-generering

De første elektroniske tekst-til-tale-systemer brugte enkeltstående lydoptagelser for hvert fonem, hvilket resulterede i meget monotone, robotagtige stemmer. Den lingvistiske analyse ville producere fonemer, som derefter blev hentet fra en database med lyde og syet sammen for at skabe lyden.

✅ Lav lidt research: Find nogle lydoptagelser fra tidlige talesyntesesystemer. Sammenlign dem med moderne talesyntese, som den der bruges i smarte assistenter.

Mere moderne bølgeforms-generering bruger ML-modeller bygget med dyb læring (meget store neurale netværk, der fungerer på en måde, der ligner neuroner i hjernen) til at producere mere naturligt lydende stemmer, der kan være umulige at skelne fra menneskelige stemmer.

> 💁 Nogle af disse ML-modeller kan genoplæres ved hjælp af transfer learning til at lyde som rigtige mennesker. Dette betyder, at brug af stemme som et sikkerhedssystem, noget som banker i stigende grad forsøger, ikke længere er en god idé, da enhver med en optagelse af blot få minutter af din stemme kan efterligne dig.

Disse store ML-modeller trænes til at kombinere alle tre trin i end-to-end talesyntese.

## Indstil timeren

For at indstille timeren skal din IoT-enhed kalde REST-endepunktet, du oprettede ved hjælp af serverløs kode, og derefter bruge det resulterende antal sekunder til at indstille en timer.

### Opgave - kald den serverløse funktion for at få timerens tid

Følg den relevante vejledning for at kalde REST-endepunktet fra din IoT-enhed og indstille en timer for den ønskede tid:

* [Arduino - Wio Terminal](wio-terminal-set-timer.md)
* [Single-board computer - Raspberry Pi/Virtual IoT device](single-board-computer-set-timer.md)

## Konverter tekst til tale

Den samme taleservice, du brugte til at konvertere tale til tekst, kan bruges til at konvertere tekst tilbage til tale, og dette kan afspilles gennem en højttaler på din IoT-enhed. Den tekst, der skal konverteres, sendes til taleservicen sammen med typen af ønsket lyd (såsom samplingsfrekvens), og binære data, der indeholder lyden, returneres.

Når du sender denne anmodning, bruger du *Speech Synthesis Markup Language* (SSML), et XML-baseret markup-sprog til talesynteseapplikationer. Dette definerer ikke kun teksten, der skal konverteres, men også sproget for teksten, stemmen, der skal bruges, og kan endda bruges til at definere hastighed, volumen og tonehøjde for nogle eller alle ordene i teksten.

For eksempel definerer denne SSML en anmodning om at konvertere teksten "Din 3 minutters og 5 sekunders timer er sat" til tale ved hjælp af en britisk engelsk stemme kaldet `en-GB-MiaNeural`

```xml
<speak version='1.0' xml:lang='en-GB'>
    <voice xml:lang='en-GB' name='en-GB-MiaNeural'>
        Your 3 minute 5 second time has been set
    </voice>
</speak>
```

> 💁 De fleste tekst-til-tale-systemer har flere stemmer for forskellige sprog med relevante accenter, såsom en britisk engelsk stemme med en engelsk accent og en newzealandsk engelsk stemme med en newzealandsk accent.

### Opgave - konverter tekst til tale

Arbejd dig igennem den relevante vejledning for at konvertere tekst til tale ved hjælp af din IoT-enhed:

* [Arduino - Wio Terminal](wio-terminal-text-to-speech.md)
* [Single-board computer - Raspberry Pi](pi-text-to-speech.md)
* [Single-board computer - Virtual device](virtual-device-text-to-speech.md)

---

## 🚀 Udfordring

SSML har måder at ændre, hvordan ord udtales, såsom at tilføje vægt på visse ord, tilføje pauser eller ændre tonehøjde. Prøv nogle af disse, send forskellige SSML fra din IoT-enhed, og sammenlign outputtet. Du kan læse mere om SSML, herunder hvordan man ændrer måden, ord udtales på, i [Speech Synthesis Markup Language (SSML) Version 1.1-specifikationen fra World Wide Web Consortium](https://www.w3.org/TR/speech-synthesis11/).

## Quiz efter lektionen

[Quiz efter lektionen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/46)

## Gennemgang & Selvstudie

* Læs mere om talesyntese på [talesyntese-siden på Wikipedia](https://wikipedia.org/wiki/Speech_synthesis)
* Læs mere om, hvordan kriminelle bruger talesyntese til at stjæle, i [fake voices 'help cyber crooks steal cash'-historien på BBC News](https://www.bbc.com/news/technology-48908736)
* Læs mere om risiciene for stemmeskuespillere fra syntetiserede versioner af deres stemmer i [denne TikTok-retssag fremhæver, hvordan AI skader stemmeskuespillere-artiklen på Vice](https://www.vice.com/en/article/z3xqwj/this-tiktok-lawsuit-is-highlighting-how-ai-is-screwing-over-voice-actors)

## Opgave

[Annuller timeren](assignment.md)

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der opstår som følge af brugen af denne oversættelse.