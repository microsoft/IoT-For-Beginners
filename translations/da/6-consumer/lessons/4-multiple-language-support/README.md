# Understøt flere sprog

![En sketchnote oversigt over denne lektion](../../../../../translated_images/da/lesson-24.4246968ed058510a.webp)

> Sketchnote af [Nitya Narasimhan](https://github.com/nitya). Klik på billedet for en større version.

Denne video giver en oversigt over Azure tale-tjenester, der dækker tale-til-tekst og tekst-til-tale fra tidligere lektioner, samt oversættelse af tale, som er emnet for denne lektion:

[![Genkend tale med få linjer Python fra Microsoft Build 2020](https://img.youtube.com/vi/h6xbpMPSGEA/0.jpg)](https://www.youtube.com/watch?v=h6xbpMPSGEA)

> 🎥 Klik på billedet ovenfor for at se videoen

## Quiz før lektionen

[Quiz før lektionen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/47)

## Introduktion

I de sidste 3 lektioner har du lært om at konvertere tale til tekst, sprogforståelse og konvertere tekst til tale, alt sammen drevet af AI. Et andet område inden for menneskelig kommunikation, hvor AI kan hjælpe, er sprogoversættelse - at konvertere fra et sprog til et andet, som f.eks. fra engelsk til fransk.

I denne lektion vil du lære om at bruge AI til at oversætte tekst, så din smarte timer kan interagere med brugere på flere sprog.

I denne lektion dækker vi:

* [Oversæt tekst](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Oversættelsestjenester](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Opret en oversætterressource](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Understøt flere sprog i applikationer med oversættelser](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Oversæt tekst ved hjælp af en AI-tjeneste](../../../../../6-consumer/lessons/4-multiple-language-support)

> 🗑 Dette er den sidste lektion i dette projekt, så efter at have afsluttet denne lektion og opgaven, må du ikke glemme at rydde op i dine cloud-tjenester. Du vil have brug for tjenesterne for at fuldføre opgaven, så sørg for at fuldføre den først.
>
> Se [guiden til oprydning af dit projekt](../../../clean-up.md) om nødvendigt for instruktioner om, hvordan du gør dette.

## Oversæt tekst

Tekstoversættelse har været et problem inden for datalogi, der er blevet forsket i over 70 år, og kun nu, takket være fremskridt inden for AI og computerkraft, er det tæt på at blive løst til et punkt, hvor det næsten er lige så godt som menneskelige oversættere.

> 💁 Oprindelsen kan spores endnu længere tilbage, til [Al-Kindi](https://wikipedia.org/wiki/Al-Kindi), en arabisk kryptograf fra det 9. århundrede, der udviklede teknikker til sprogoversættelse.

### Maskinoversættelser

Tekstoversættelse startede som en teknologi kendt som Maskinoversættelse (MT), der kan oversætte mellem forskellige sprogpar. MT fungerer ved at erstatte ord på ét sprog med et andet og tilføje teknikker til at vælge de korrekte måder at oversætte sætninger eller dele af sætninger, når en simpel ord-for-ord oversættelse ikke giver mening.

> 🎓 Når oversættere understøtter oversættelse mellem ét sprog og et andet, kaldes disse *sprogpar*. Forskellige værktøjer understøtter forskellige sprogpar, og disse er måske ikke komplette. For eksempel kan en oversætter understøtte engelsk til spansk som et sprogpar og spansk til italiensk som et sprogpar, men ikke engelsk til italiensk.

For eksempel kan oversættelsen af "Hello world" fra engelsk til fransk udføres med en substitution - "Bonjour" for "Hello" og "le monde" for "world", hvilket fører til den korrekte oversættelse "Bonjour le monde".

Substitutioner fungerer ikke, når forskellige sprog bruger forskellige måder at sige det samme på. For eksempel oversættes den engelske sætning "My name is Jim" til "Je m'appelle Jim" på fransk - bogstaveligt "Jeg kalder mig selv Jim". "Je" er fransk for "jeg", "moi" er mig, men det er sammenføjet med verbet, da det starter med en vokal, så det bliver "m'", "appelle" betyder at kalde, og "Jim" oversættes ikke, da det er et navn og ikke et ord, der kan oversættes. Ordrækkefølgen bliver også et problem - en simpel substitution af "Je m'appelle Jim" bliver "I myself call Jim", med en anden ordrækkefølge end på engelsk.

> 💁 Nogle ord oversættes aldrig - mit navn er Jim uanset hvilket sprog, der bruges til at introducere mig. Når man oversætter til sprog, der bruger forskellige alfabeter eller forskellige bogstaver for forskellige lyde, kan ord *translittereres*, dvs. vælge bogstaver eller tegn, der giver den passende lyd for at lyde som det givne ord.

Idiomer er også et problem for oversættelse. Disse er sætninger, der har en forstået betydning, der er forskellig fra en direkte fortolkning af ordene. For eksempel betyder idiomet "I've got ants in my pants" på engelsk ikke bogstaveligt, at man har myrer i tøjet, men at man er rastløs. Hvis du oversatte dette til tysk, ville du forvirre lytteren, da den tyske version er "I have bumble bees in the bottom".

> 💁 Forskellige lokaliteter tilføjer forskellige kompleksiteter. Med idiomet "ants in your pants" refererer "pants" i amerikansk engelsk til overtøj, mens "pants" i britisk engelsk er undertøj.

✅ Hvis du taler flere sprog, så tænk på nogle sætninger, der ikke direkte kan oversættes.

Maskinoversættelsessystemer er afhængige af store databaser med regler, der beskriver, hvordan man oversætter visse sætninger og idiomer, sammen med statistiske metoder til at vælge de passende oversættelser fra mulige muligheder. Disse statistiske metoder bruger enorme databaser med værker, der er oversat af mennesker til flere sprog, for at vælge den mest sandsynlige oversættelse, en teknik kaldet *statistisk maskinoversættelse*. Nogle af disse bruger mellemliggende repræsentationer af sproget, hvilket gør det muligt at oversætte ét sprog til det mellemliggende og derefter fra det mellemliggende til et andet sprog. På denne måde involverer tilføjelse af flere sprog oversættelser til og fra det mellemliggende, ikke til og fra alle andre sprog.

### Neurale oversættelser

Neurale oversættelser involverer brugen af AI til at oversætte, typisk ved at oversætte hele sætninger ved hjælp af én model. Disse modeller trænes på enorme datasæt, der er blevet oversat af mennesker, såsom websider, bøger og FN-dokumentation.

Neurale oversættelsesmodeller er normalt mindre end maskinoversættelsesmodeller, da de ikke behøver store databaser med sætninger og idiomer. Moderne AI-tjenester, der tilbyder oversættelser, blander ofte flere teknikker, der kombinerer statistisk maskinoversættelse og neurale oversættelser.

Der er ingen 1:1 oversættelse for noget sprogpar. Forskellige oversættelsesmodeller vil producere lidt forskellige resultater afhængigt af de data, der er brugt til at træne modellen. Oversættelser er ikke altid symmetriske - hvis du oversætter en sætning fra ét sprog til et andet og derefter tilbage til det første sprog, kan du få en lidt anderledes sætning som resultat.

✅ Prøv forskellige online oversættere som [Bing Translate](https://www.bing.com/translator), [Google Translate](https://translate.google.com) eller Apple Translate-appen. Sammenlign de oversatte versioner af nogle sætninger. Prøv også at oversætte i én og derefter oversætte tilbage i en anden.

## Oversættelsestjenester

Der findes en række AI-tjenester, som du kan bruge fra dine applikationer til at oversætte tale og tekst.

### Cognitive Services Speech Service

![Logoet for tale-tjenesten](../../../../../translated_images/da/azure-speech-logo.a1f08c4befb0159f.webp)

Tale-tjenesten, som du har brugt i de sidste par lektioner, har oversættelsesmuligheder for talegenkendelse. Når du genkender tale, kan du anmode om ikke kun teksten af talen på samme sprog, men også på andre sprog.

> 💁 Dette er kun tilgængeligt fra tale-SDK'en, REST API'en har ikke indbyggede oversættelser.

### Cognitive Services Translator Service

![Logoet for oversætter-tjenesten](../../../../../translated_images/da/azure-translator-logo.c6ed3a4a433edfd2.webp)

Translator-tjenesten er en dedikeret oversættelsestjeneste, der kan oversætte tekst fra ét sprog til ét eller flere målsprog. Ud over at oversætte understøtter den en bred vifte af ekstra funktioner, herunder maskering af bandeord. Den giver dig også mulighed for at angive en specifik oversættelse for et bestemt ord eller en sætning, så du kan arbejde med termer, du ikke ønsker oversat, eller have en specifik velkendt oversættelse.

For eksempel, når man oversætter sætningen "I have a Raspberry Pi", der refererer til den enkeltkort-computer, til et andet sprog som fransk, vil man gerne beholde navnet "Raspberry Pi" som det er og ikke oversætte det, hvilket giver "J’ai un Raspberry Pi" i stedet for "J’ai une pi aux framboises".

## Opret en oversætterressource

Til denne lektion skal du bruge en Translator-ressource. Du vil bruge REST API'en til at oversætte tekst.

### Opgave - opret en oversætterressource

1. Fra din terminal eller kommandoprompt skal du køre følgende kommando for at oprette en oversætterressource i din `smart-timer` ressourcegruppe.

    ```sh
    az cognitiveservices account create --name smart-timer-translator \
                                        --resource-group smart-timer \
                                        --kind TextTranslation \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Erstat `<location>` med den placering, du brugte, da du oprettede ressourcegruppen.

1. Få nøglen til oversætter-tjenesten:

    ```sh
    az cognitiveservices account keys list --name smart-timer-translator \
                                           --resource-group smart-timer \
                                           --output table
    ```

    Tag en kopi af en af nøglerne.

## Understøt flere sprog i applikationer med oversættelser

I en ideel verden bør hele din applikation forstå så mange forskellige sprog som muligt, fra at lytte til tale, til sprogforståelse, til at svare med tale. Dette er meget arbejde, så oversættelsestjenester kan fremskynde leveringstiden for din applikation.

![En smart timer-arkitektur, der oversætter japansk til engelsk, behandler på engelsk og derefter oversætter tilbage til japansk](../../../../../translated_images/da/translated-smart-timer.08ac20057fdc5c37.webp)

Forestil dig, at du bygger en smart timer, der bruger engelsk fra start til slut, forstår talt engelsk og konverterer det til tekst, kører sprogforståelse på engelsk, bygger svar på engelsk og svarer med engelsk tale. Hvis du ville tilføje understøttelse af japansk, kunne du starte med at oversætte talt japansk til engelsk tekst, derefter holde kernen af applikationen den samme og derefter oversætte svarteksten til japansk, før du taler svaret. Dette ville give dig mulighed for hurtigt at tilføje japansk understøttelse, og du kan senere udvide til at tilbyde fuld end-to-end japansk understøttelse.

> 💁 Ulempen ved at stole på maskinoversættelse er, at forskellige sprog og kulturer har forskellige måder at sige de samme ting på, så oversættelsen måske ikke matcher det udtryk, du forventer.

Maskinoversættelser åbner også op for muligheder for apps og enheder, der kan oversætte brugeroprettet indhold, mens det oprettes. Science fiction indeholder ofte 'universelle oversættere', enheder der kan oversætte fra fremmede sprog til (typisk) amerikansk engelsk. Disse enheder er mindre science fiction og mere videnskabelig fakta, hvis man ser bort fra den fremmede del. Der findes allerede apps og enheder, der tilbyder realtidsoversættelse af tale og skrevet tekst ved hjælp af kombinationer af tale- og oversættelsestjenester.

Et eksempel er [Microsoft Translator](https://www.microsoft.com/translator/apps/?WT.mc_id=academic-17441-jabenn) mobiltelefonappen, demonstreret i denne video:

[![Microsoft Translator live-funktion i aktion](https://img.youtube.com/vi/16yAGeP2FuM/0.jpg)](https://www.youtube.com/watch?v=16yAGeP2FuM)

> 🎥 Klik på billedet ovenfor for at se videoen

Forestil dig at have en sådan enhed til rådighed, især når du rejser eller interagerer med folk, hvis sprog du ikke kender. At have automatiske oversættelsesenheder i lufthavne eller hospitaler ville give meget tiltrængte forbedringer af tilgængeligheden.

✅ Lav lidt research: Er der nogen oversættelses-IoT-enheder kommercielt tilgængelige? Hvad med oversættelsesfunktioner indbygget i smarte enheder?

> 👽 Selvom der ikke findes ægte universelle oversættere, der giver os mulighed for at tale med fremmede, understøtter [Microsoft Translator faktisk klingon](https://www.microsoft.com/translator/blog/2013/05/14/announcing-klingon-for-bing-translator/?WT.mc_id=academic-17441-jabenn). Qapla’!

## Oversæt tekst ved hjælp af en AI-tjeneste

Du kan bruge en AI-tjeneste til at tilføje denne oversættelsesfunktion til din smarte timer.

### Opgave - oversæt tekst ved hjælp af en AI-tjeneste

Arbejd dig igennem den relevante guide for at konvertere tekstoversættelse på din IoT-enhed:

* [Arduino - Wio Terminal](wio-terminal-translate-speech.md)
* [Enkeltkort-computer - Raspberry Pi](pi-translate-speech.md)
* [Enkeltkort-computer - Virtuel enhed](virtual-device-translate-speech.md)

---

## 🚀 Udfordring

Hvordan kan maskinoversættelser gavne andre IoT-applikationer ud over smarte enheder? Tænk på forskellige måder, oversættelser kan hjælpe, ikke kun med talte ord, men også med tekst.

## Quiz efter lektionen

[Quiz efter lektionen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/48)

## Gennemgang & Selvstudie

* Læs mere om maskinoversættelse på [maskinoversættelsessiden på Wikipedia](https://wikipedia.org/wiki/Machine_translation)
* Læs mere om neurale maskinoversættelser på [neurale maskinoversættelsessiden på Wikipedia](https://wikipedia.org/wiki/Neural_machine_translation)
* Tjek listen over understøttede sprog for Microsoft tale-tjenester i [sprog- og stemmeunderstøttelse for tale-tjenestedokumentationen på Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn)

## Opgave

[Byg en universel oversætter](assignment.md)

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på at opnå nøjagtighed, skal det bemærkes, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.