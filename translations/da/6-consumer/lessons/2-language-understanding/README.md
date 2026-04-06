# Forstå sprog

![En sketchnote oversigt over denne lektion](../../../../../translated_images/da/lesson-22.6148ea28500d9e00.webp)

> Sketchnote af [Nitya Narasimhan](https://github.com/nitya). Klik på billedet for en større version.

## Quiz før lektionen

[Quiz før lektionen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/43)

## Introduktion

I den sidste lektion konverterede du tale til tekst. For at kunne bruge dette til at programmere en smart timer, skal din kode kunne forstå, hvad der blev sagt. Du kunne antage, at brugeren vil sige en fast sætning, som "Sæt en 3-minutters timer", og analysere den sætning for at finde ud af, hvor lang tid timeren skal være. Men dette er ikke særlig brugervenligt. Hvis en bruger siger "Sæt en timer for 3 minutter", ville du og jeg forstå, hvad de mener, men din kode ville ikke, da den forventer en fast sætning.

Her kommer sprogforståelse ind i billedet, hvor AI-modeller bruges til at tolke tekst og returnere de nødvendige detaljer. For eksempel kan de tage både "Sæt en 3-minutters timer" og "Sæt en timer for 3 minutter" og forstå, at der skal sættes en timer for 3 minutter.

I denne lektion vil du lære om sprogforståelsesmodeller, hvordan man opretter dem, træner dem og bruger dem i din kode.

I denne lektion dækker vi:

* [Sprogforståelse](../../../../../6-consumer/lessons/2-language-understanding)
* [Opret en sprogforståelsesmodel](../../../../../6-consumer/lessons/2-language-understanding)
* [Intentioner og entiteter](../../../../../6-consumer/lessons/2-language-understanding)
* [Brug sprogforståelsesmodellen](../../../../../6-consumer/lessons/2-language-understanding)

## Sprogforståelse

Mennesker har brugt sprog til at kommunikere i hundrede tusinder af år. Vi kommunikerer med ord, lyde eller handlinger og forstår, hvad der bliver sagt, både betydningen af ordene, lydene eller handlingerne, men også deres kontekst. Vi forstår oprigtighed og sarkasme, hvilket gør det muligt for de samme ord at betyde forskellige ting afhængigt af tonen i vores stemme.

✅ Tænk på nogle af de samtaler, du har haft for nylig. Hvor meget af samtalen ville være svært for en computer at forstå, fordi den kræver kontekst?

Sprogforståelse, også kaldet naturlig sprogforståelse, er en del af et felt inden for kunstig intelligens kaldet naturlig sprogbehandling (eller NLP) og handler om læseforståelse, hvor man forsøger at forstå detaljerne i ord eller sætninger. Hvis du bruger en stemmeassistent som Alexa eller Siri, har du brugt sprogforståelsestjenester. Disse er de bagvedliggende AI-tjenester, der konverterer "Alexa, spil det nyeste album af Taylor Swift" til min datter, der danser rundt i stuen til sine yndlingssange.

> 💁 Computere, på trods af alle deres fremskridt, har stadig lang vej igen for virkelig at forstå tekst. Når vi taler om sprogforståelse med computere, mener vi ikke noget, der er i nærheden af menneskelig kommunikation. I stedet mener vi at tage nogle ord og udtrække nøgleoplysninger.

Som mennesker forstår vi sprog uden rigtig at tænke over det. Hvis jeg bad et andet menneske om at "spille det nyeste album af Taylor Swift", ville de instinktivt vide, hvad jeg mente. For en computer er dette sværere. Den ville skulle tage ordene, konverteret fra tale til tekst, og finde følgende oplysninger:

* Musik skal spilles
* Musikken er af kunstneren Taylor Swift
* Den specifikke musik er et helt album med flere numre i rækkefølge
* Taylor Swift har mange albums, så de skal sorteres kronologisk, og det senest udgivne er det, der ønskes

✅ Tænk på nogle andre sætninger, du har sagt, når du har lavet forespørgsler, som at bestille kaffe eller bede et familiemedlem om at række dig noget. Prøv at bryde dem ned i de oplysninger, en computer ville skulle udtrække for at forstå sætningen.

Sprogforståelsesmodeller er AI-modeller, der er trænet til at udtrække visse detaljer fra sprog og derefter trænes til specifikke opgaver ved hjælp af transfer learning, på samme måde som du trænede en Custom Vision-model ved hjælp af et lille sæt billeder. Du kan tage en model og derefter træne den med den tekst, du vil have den til at forstå.

## Opret en sprogforståelsesmodel

![LUIS-logoet](../../../../../translated_images/da/luis-logo.5cb4f3e88c020ee6.webp)

Du kan oprette sprogforståelsesmodeller ved hjælp af LUIS, en sprogforståelsestjeneste fra Microsoft, der er en del af Cognitive Services.

### Opgave - opret en forfatterressource

For at bruge LUIS skal du oprette en forfatterressource.

1. Brug følgende kommando til at oprette en forfatterressource i din `smart-timer`-ressourcegruppe:

    ```python
    az cognitiveservices account create --name smart-timer-luis-authoring \
                                        --resource-group smart-timer \
                                        --kind LUIS.Authoring \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Erstat `<location>` med den placering, du brugte, da du oprettede ressourcegruppen.

    > ⚠️ LUIS er ikke tilgængelig i alle regioner, så hvis du får følgende fejl:
    >
    > ```output
    > InvalidApiSetId: The account type 'LUIS.Authoring' is either invalid or unavailable in given region.
    > ```
    >
    > vælg en anden region.

    Dette vil oprette en gratis LUIS-forfatterressource.

### Opgave - opret en sprogforståelsesapp

1. Åbn LUIS-portalen på [luis.ai](https://luis.ai?WT.mc_id=academic-17441-jabenn) i din browser, og log ind med den samme konto, du har brugt til Azure.

1. Følg instruktionerne i dialogen for at vælge dit Azure-abonnement, og vælg derefter den `smart-timer-luis-authoring`-ressource, du lige har oprettet.

1. Fra listen *Conversation apps* skal du vælge knappen **New app** for at oprette en ny applikation. Navngiv den nye app `smart-timer`, og sæt *Culture* til dit sprog.

    > 💁 Der er et felt til en forudsigelsesressource. Du kan oprette en anden ressource kun til forudsigelse, men den gratis forfatterressource tillader 1.000 forudsigelser om måneden, hvilket burde være nok til udvikling, så du kan lade dette felt være tomt.

1. Læs vejledningen, der vises, når du opretter appen, for at få en forståelse af de trin, du skal tage for at træne sprogforståelsesmodellen. Luk vejledningen, når du er færdig.

## Intentioner og entiteter

Sprogforståelse er baseret på *intentioner* og *entiteter*. Intentioner er, hvad ordenes hensigt er, for eksempel at spille musik, sætte en timer eller bestille mad. Entiteter er, hvad intentionen refererer til, såsom albummet, længden af timeren eller typen af mad. Hver sætning, som modellen fortolker, bør have mindst én intention og eventuelt en eller flere entiteter.

Nogle eksempler:

| Sætning                                             | Intention         | Entiteter                                   |
| --------------------------------------------------- | ----------------- | ------------------------------------------ |
| "Spil det nyeste album af Taylor Swift"             | *spil musik*      | *det nyeste album af Taylor Swift*         |
| "Sæt en 3-minutters timer"                          | *sæt en timer*    | *3 minutter*                               |
| "Annuller min timer"                                | *annuller en timer* | Ingen                                      |
| "Bestil 3 store ananas-pizzaer og en caesarsalat"   | *bestil mad*      | *3 store ananas-pizzaer*, *caesarsalat*    |

✅ Med de sætninger, du tænkte på tidligere, hvad ville være intentionen og eventuelle entiteter i den sætning?

For at træne LUIS skal du først definere entiteterne. Disse kan være en fast liste over termer eller læres fra teksten. For eksempel kunne du give en fast liste over mad, der er tilgængelig på din menu, med variationer (eller synonymer) af hvert ord, såsom *aubergine* og *ægplante* som variationer af *aubergine*. LUIS har også forudbyggede entiteter, der kan bruges, såsom tal og placeringer.

For at sætte en timer kunne du have én entitet, der bruger de forudbyggede tal-entiteter til tiden, og en anden til enhederne, såsom minutter og sekunder. Hver enhed ville have flere variationer for at dække de entals- og flertalsformer - såsom minut og minutter.

Når entiteterne er defineret, opretter du intentioner. Disse læres af modellen baseret på eksempelsætninger, du giver (kendt som ytringer). For eksempel, for en *sæt timer*-intention, kunne du give følgende sætninger:

* `sæt en 1-sekunds timer`
* `sæt en timer for 1 minut og 12 sekunder`
* `sæt en timer for 3 minutter`
* `sæt en 9-minutters 30-sekunders timer`

Du fortæller derefter LUIS, hvilke dele af disse sætninger der svarer til entiteterne:

![Sætningen sæt en timer for 1 minut og 12 sekunder opdelt i entiteter](../../../../../translated_images/da/sentence-as-intent-entities.301401696f992259.webp)

Sætningen `sæt en timer for 1 minut og 12 sekunder` har intentionen `sæt timer`. Den har også 2 entiteter med 2 værdier hver:

|            | tid  | enhed   |
| ---------- | ---- | ------- |
| 1 minut    | 1    | minut   |
| 12 sekunder| 12   | sekund  |

For at træne en god model skal du bruge en række forskellige eksempelsætninger for at dække de mange forskellige måder, nogen kunne bede om det samme.

> 💁 Som med enhver AI-model, jo mere data og jo mere præcise data, du bruger til at træne, desto bedre bliver modellen.

✅ Tænk på de forskellige måder, du kunne bede om det samme og forvente, at et menneske forstår det.

### Opgave - tilføj entiteter til sprogforståelsesmodellerne

For timeren skal du tilføje 2 entiteter - én for tidsenheden (minutter eller sekunder) og én for antallet af minutter eller sekunder.

Du kan finde instruktioner til brug af LUIS-portalen i [Quickstart: Build your app in LUIS portal documentation on Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/luis/luis-get-started-create-app?WT.mc_id=academic-17441-jabenn).

1. Fra LUIS-portalen skal du vælge fanen *Entities* og tilføje den forudbyggede entitet *number* ved at vælge knappen **Add prebuilt entity** og derefter vælge *number* fra listen.

1. Opret en ny entitet for tidsenheden ved hjælp af knappen **Create**. Navngiv entiteten `time unit` og sæt typen til *List*. Tilføj værdier for `minute` og `second` til listen *Normalized values*, og tilføj entals- og flertalsformer til listen *synonyms*. Tryk på `return` efter at have tilføjet hver synonym for at tilføje den til listen.

    | Normalized value | Synonymer        |
    | ---------------- | ---------------- |
    | minute           | minut, minutter |
    | second           | sekund, sekunder |

### Opgave - tilføj intentioner til sprogforståelsesmodellerne

1. Fra fanen *Intents* skal du vælge knappen **Create** for at oprette en ny intention. Navngiv denne intention `set timer`.

1. I eksemplerne skal du indtaste forskellige måder at sætte en timer på ved hjælp af både minutter, sekunder og kombinationer af minutter og sekunder. Eksempler kunne være:

    * `sæt en 1-sekunds timer`
    * `sæt en 4-minutters timer`
    * `sæt en fire-minutters seks-sekunders timer`
    * `sæt en 9-minutters 30-sekunders timer`
    * `sæt en timer for 1 minut og 12 sekunder`
    * `sæt en timer for 3 minutter`
    * `sæt en timer for 3 minutter og 1 sekund`
    * `sæt en timer for tre minutter og et sekund`
    * `sæt en timer for 1 minut og 1 sekund`
    * `sæt en timer for 30 sekunder`
    * `sæt en timer for 1 sekund`

    Bland tal som ord og numeriske værdier, så modellen lærer at håndtere begge dele.

1. Når du indtaster hvert eksempel, vil LUIS begynde at registrere entiteter og understrege og mærke dem, den finder.

    ![Eksemplerne med tal og tidsenheder understreget af LUIS](../../../../../translated_images/da/luis-intent-examples.25716580b2d2723c.webp)

### Opgave - træn og test modellen

1. Når entiteterne og intentionerne er konfigureret, kan du træne modellen ved hjælp af knappen **Train** i topmenuen. Vælg denne knap, og modellen bør træne på få sekunder. Knappen vil være grå, mens træningen pågår, og blive aktiveret igen, når den er færdig.

1. Vælg knappen **Test** fra topmenuen for at teste sprogforståelsesmodellen. Indtast tekst som `sæt en timer for 5 minutter og 4 sekunder` og tryk på return. Sætningen vil vises i en boks under tekstboksen, du skrev den i, og nedenunder vil den *top intention* vises, eller den intention, der blev registreret med den højeste sandsynlighed. Dette bør være `set timer`. Intentionens navn vil blive efterfulgt af sandsynligheden for, at den registrerede intention var korrekt.

1. Vælg **Inspect** for at se en opdeling af resultaterne. Du vil se den intention med den højeste score og dens procentvise sandsynlighed sammen med lister over de registrerede entiteter.

1. Luk *Test*-panelet, når du er færdig med at teste.

### Opgave - udgiv modellen

For at bruge denne model fra kode skal du udgive den. Når du udgiver fra LUIS, kan du udgive til enten et staging-miljø til test eller et produktionsmiljø til en fuld udgivelse. I denne lektion er et staging-miljø fint.

1. Fra LUIS-portalen skal du vælge knappen **Publish** fra topmenuen.

1. Sørg for, at *Staging slot* er valgt, og vælg derefter **Done**. Du vil se en notifikation, når appen er udgivet.

1. Du kan teste dette ved hjælp af curl. For at opbygge curl-kommandoen skal du bruge tre værdier - endpointet, applikations-ID'et (App ID) og en API-nøgle. Disse kan tilgås fra fanen **MANAGE**, som kan vælges fra topmenuen.

    1. Fra sektionen *Settings* skal du kopiere App ID.
1. Fra sektionen *Azure Resources* skal du vælge *Authoring Resource* og kopiere *Primary Key* og *Endpoint URL*.

1. Kør følgende curl-kommando i din kommandoprompt eller terminal:

    ```sh
    curl "<endpoint url>/luis/prediction/v3.0/apps/<app id>/slots/staging/predict" \
          --request GET \
          --get \
          --data "subscription-key=<primary key>" \
          --data "verbose=false" \
          --data "show-all-intents=true" \
          --data-urlencode "query=<sentence>"
    ```

    Erstat `<endpoint url>` med Endpoint URL fra sektionen *Azure Resources*.

    Erstat `<app id>` med App ID fra sektionen *Settings*.

    Erstat `<primary key>` med Primary Key fra sektionen *Azure Resources*.

    Erstat `<sentence>` med den sætning, du vil teste med.

1. Outputtet af dette kald vil være et JSON-dokument, der beskriver forespørgslen, den højeste intent og en liste over entiteter opdelt efter type.

    ```JSON
    {
        "query": "set a timer for 45 minutes and 12 seconds",
        "prediction": {
            "topIntent": "set timer",
            "intents": {
                "set timer": {
                    "score": 0.97031575
                },
                "None": {
                    "score": 0.02205793
                }
            },
            "entities": {
                "number": [
                    45,
                    12
                ],
                "time-unit": [
                    [
                        "minute"
                    ],
                    [
                        "second"
                    ]
                ]
            }
        }
    }
    ```

    JSON-dokumentet ovenfor stammer fra forespørgslen `set a timer for 45 minutes and 12 seconds`:

    * `set timer` var den højeste intent med en sandsynlighed på 97 %.
    * To *number*-entiteter blev registreret: `45` og `12`.
    * To *time-unit*-entiteter blev registreret: `minute` og `second`.

## Brug sprogforståelsesmodellen

Når LUIS-modellen er publiceret, kan den kaldes fra kode. I tidligere lektioner har du brugt en IoT Hub til at håndtere kommunikation med cloud-tjenester, sende telemetri og lytte efter kommandoer. Dette er meget asynkront – når telemetri sendes, venter din kode ikke på et svar, og hvis cloud-tjenesten er nede, vil du ikke vide det.

For en smart timer ønsker vi et øjeblikkeligt svar, så vi kan fortælle brugeren, at en timer er sat, eller advare dem om, at cloud-tjenesterne ikke er tilgængelige. For at gøre dette vil vores IoT-enhed kalde en web-endpoint direkte i stedet for at stole på en IoT Hub.

I stedet for at kalde LUIS direkte fra IoT-enheden kan du bruge serverløs kode med en anden type trigger – en HTTP-trigger. Dette gør det muligt for din funktion at lytte efter REST-forespørgsler og svare på dem. Denne funktion vil være et REST-endpoint, som din enhed kan kalde.

> 💁 Selvom du kan kalde LUIS direkte fra din IoT-enhed, er det bedre at bruge noget som serverløs kode. På denne måde, når du vil ændre den LUIS-app, du kalder, for eksempel når du træner en bedre model eller træner en model på et andet sprog, skal du kun opdatere din cloud-kode og ikke genudrulle kode til potentielt tusinder eller millioner af IoT-enheder.

### Opgave - opret en serverløs funktionsapp

1. Opret en Azure Functions-app kaldet `smart-timer-trigger`, og åbn den i VS Code.

1. Tilføj en HTTP-trigger til denne app kaldet `speech-trigger` ved at bruge følgende kommando i VS Code-terminalen:

    ```sh
    func new --name text-to-timer --template "HTTP trigger"
    ```

    Dette vil oprette en HTTP-trigger kaldet `text-to-timer`.

1. Test HTTP-triggeren ved at køre funktionsappen. Når den kører, vil du se endpointet opført i outputtet:

    ```output
    Functions:
    
            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    ```

    Test dette ved at indlæse [http://localhost:7071/api/text-to-timer](http://localhost:7071/api/text-to-timer) i din browser.

    ```output
    This HTTP triggered function executed successfully. Pass a name in the query string or in the request body for a personalized response.
    ```

### Opgave - brug sprogforståelsesmodellen

1. SDK'en for LUIS er tilgængelig via en Pip-pakke. Tilføj følgende linje til filen `requirements.txt` for at tilføje afhængigheden til denne pakke:

    ```sh
    azure-cognitiveservices-language-luis
    ```

1. Sørg for, at VS Code-terminalen har det virtuelle miljø aktiveret, og kør følgende kommando for at installere Pip-pakkerne:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 Hvis du får fejl, skal du muligvis opgradere pip med følgende kommando:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Tilføj nye poster til filen `local.settings.json` for din LUIS API Key, Endpoint URL og App ID fra **MANAGE**-fanen i LUIS-portalen:

    ```JSON
    "LUIS_KEY": "<primary key>",
    "LUIS_ENDPOINT_URL": "<endpoint url>",
    "LUIS_APP_ID": "<app id>"
    ```

    Erstat `<endpoint url>` med Endpoint URL fra sektionen *Azure Resources* i **MANAGE**-fanen. Dette vil være `https://<location>.api.cognitive.microsoft.com/`.

    Erstat `<app id>` med App ID fra sektionen *Settings* i **MANAGE**-fanen.

    Erstat `<primary key>` med Primary Key fra sektionen *Azure Resources* i **MANAGE**-fanen.

1. Tilføj følgende imports til filen `__init__.py`:

    ```python
    import json
    import os
    from azure.cognitiveservices.language.luis.runtime import LUISRuntimeClient
    from msrest.authentication import CognitiveServicesCredentials
    ```

    Dette importerer nogle systembiblioteker samt bibliotekerne til at interagere med LUIS.

1. Slet indholdet af metoden `main`, og tilføj følgende kode:

    ```python
    luis_key = os.environ['LUIS_KEY']
    endpoint_url = os.environ['LUIS_ENDPOINT_URL']
    app_id = os.environ['LUIS_APP_ID']
    
    credentials = CognitiveServicesCredentials(luis_key)
    client = LUISRuntimeClient(endpoint=endpoint_url, credentials=credentials)
    ```

    Dette indlæser de værdier, du tilføjede til filen `local.settings.json` for din LUIS-app, opretter et credentials-objekt med din API-nøgle og opretter derefter et LUIS-klientobjekt til at interagere med din LUIS-app.

1. Denne HTTP-trigger vil blive kaldt med teksten, der skal forstås, som JSON, hvor teksten er i en egenskab kaldet `text`. Følgende kode udtrækker værdien fra HTTP-forespørgslens body og logger den til konsollen. Tilføj denne kode til funktionen `main`:

    ```python
    req_body = req.get_json()
    text = req_body['text']
    logging.info(f'Request - {text}')
    ```

1. Forudsigelser anmodes fra LUIS ved at sende en forudsigelsesforespørgsel – et JSON-dokument, der indeholder teksten, der skal forudsiges. Opret dette med følgende kode:

    ```python
    prediction_request = { 'query' : text }
    ```

1. Denne forespørgsel kan derefter sendes til LUIS ved hjælp af staging-slottet, som din app blev publiceret til:

    ```python
    prediction_response = client.prediction.get_slot_prediction(app_id, 'Staging', prediction_request)
    ```

1. Forudsigelsessvaret indeholder den højeste intent – den intent med den højeste forudsigelsesscore – sammen med entiteterne. Hvis den højeste intent er `set timer`, kan entiteterne læses for at få den tid, der er nødvendig for timeren:

    ```python
    if prediction_response.prediction.top_intent == 'set timer':
        numbers = prediction_response.prediction.entities['number']
        time_units = prediction_response.prediction.entities['time unit']
        total_seconds = 0
    ```

    `number`-entiteterne vil være en liste af tal. For eksempel, hvis du sagde *"Set a four minute 17 second timer."*, vil `number`-listen indeholde 2 heltal – 4 og 17.

    `time unit`-entiteterne vil være en liste af lister af strenge, hvor hver tidsenhed er en liste af strenge inde i listen. For eksempel, hvis du sagde *"Set a four minute 17 second timer."*, vil `time unit`-listen indeholde 2 lister med enkeltværdier – `['minute']` og `['second']`.

    JSON-versionen af disse entiteter for *"Set a four minute 17 second timer."* er:

    ```json
    {
        "number": [4, 17],
        "time unit": [
            ["minute"],
            ["second"]
        ]
    }
    ```

    Denne kode definerer også en tæller for den samlede tid for timeren i sekunder. Dette vil blive udfyldt med værdierne fra entiteterne.

1. Entiteterne er ikke linket, men vi kan lave nogle antagelser om dem. De vil være i den rækkefølge, de blev sagt, så positionen i listen kan bruges til at bestemme, hvilket tal der matcher hvilken tidsenhed. For eksempel:

    * *"Set a 30 second timer"* – dette vil have ét tal, `30`, og én tidsenhed, `second`, så det enkelte tal vil matche den enkelte tidsenhed.
    * *"Set a 2 minute and 30 second timer"* – dette vil have to tal, `2` og `30`, og to tidsenheder, `minute` og `second`, så det første tal vil være for den første tidsenhed (2 minutter), og det andet tal for den anden tidsenhed (30 sekunder).

    Følgende kode får antallet af elementer i `number`-entiteterne og bruger det til at udtrække det første element fra hver liste, derefter det andet osv. Tilføj dette inde i `if`-blokken.

    ```python
    for i in range(0, len(numbers)):
        number = numbers[i]
        time_unit = time_units[i][0]
    ```

    For *"Set a four minute 17 second timer."* vil dette loop køre to gange og give følgende værdier:

    | loop count | `number` | `time_unit` |
    | ---------: | -------: | ----------- |
    | 0          | 4        | minute      |
    | 1          | 17       | second      |

1. Inde i dette loop skal du bruge tallet og tidsenheden til at beregne den samlede tid for timeren, hvor der tilføjes 60 sekunder for hvert minut og antallet af sekunder for eventuelle sekunder.

    ```python
    if time_unit == 'minute':
        total_seconds += number * 60
    else:
        total_seconds += number
    ```

1. Uden for dette loop gennem entiteterne skal du logge den samlede tid for timeren:

    ```python
    logging.info(f'Timer required for {total_seconds} seconds')
    ```

1. Antallet af sekunder skal returneres fra funktionen som et HTTP-svar. I slutningen af `if`-blokken skal du tilføje følgende:

    ```python
    payload = {
        'seconds': total_seconds
    }
    return func.HttpResponse(json.dumps(payload), status_code=200)
    ```

    Denne kode opretter en payload, der indeholder det samlede antal sekunder for timeren, konverterer det til en JSON-streng og returnerer det som et HTTP-resultat med statuskoden 200, hvilket betyder, at kaldet var vellykket.

1. Til sidst, uden for `if`-blokken, skal du håndtere, hvis intenten ikke blev genkendt, ved at returnere en fejlkode:

    ```python
    return func.HttpResponse(status_code=404)
    ```

    404 er statuskoden for *not found*.

1. Kør funktionsappen og test den ved hjælp af curl.

    ```sh
    curl --request POST 'http://localhost:7071/api/text-to-timer' \
         --header 'Content-Type: application/json' \
         --include \
         --data '{"text":"<text>"}'
    ```

    Erstat `<text>` med teksten i din forespørgsel, for eksempel `set a 2 minutes 27 second timer`.

    Du vil se følgende output fra funktionsappen:

    ```output
    Functions:

            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    
    For detailed output, run func with --verbose flag.
    [2021-06-26T19:45:14.502Z] Worker process started and initialized.
    [2021-06-26T19:45:19.338Z] Host lock lease acquired by instance ID '000000000000000000000000951CAE4E'.
    [2021-06-26T19:45:52.059Z] Executing 'Functions.text-to-timer' (Reason='This function was programmatically called via the host APIs.', Id=f68bfb90-30e4-47a5-99da-126b66218e81)
    [2021-06-26T19:45:53.577Z] Timer required for 147 seconds
    [2021-06-26T19:45:53.746Z] Executed 'Functions.text-to-timer' (Succeeded, Id=f68bfb90-30e4-47a5-99da-126b66218e81, Duration=1750ms)
    ```

    Kaldet til curl vil returnere følgende:

    ```output
    HTTP/1.1 200 OK
    Date: Tue, 29 Jun 2021 01:14:11 GMT
    Content-Type: text/plain; charset=utf-8
    Server: Kestrel
    Transfer-Encoding: chunked
    
    {"seconds": 147}
    ```

    Antallet af sekunder for timeren er i værdien `"seconds"`.

> 💁 Du kan finde denne kode i mappen [code/functions](../../../../../6-consumer/lessons/2-language-understanding/code/functions).

### Opgave - gør din funktion tilgængelig for din IoT-enhed

1. For at din IoT-enhed kan kalde dit REST-endpoint, skal den kende URL'en. Da du tidligere tilgik det, brugte du `localhost`, som er en genvej til at tilgå REST-endpoints på din lokale maskine. For at give din IoT-enhed adgang skal du enten publicere til skyen eller finde din IP-adresse for at tilgå det lokalt.

    > ⚠️ Hvis du bruger en Wio Terminal, er det nemmere at køre funktionsappen lokalt, da der vil være en afhængighed af biblioteker, der betyder, at du ikke kan udrulle funktionsappen på samme måde som tidligere. Kør funktionsappen lokalt, og tilgå den via din computers IP-adresse. Hvis du ønsker at udrulle til skyen, vil der blive givet information i en senere lektion om, hvordan dette gøres.

    * Publicer funktionsappen – følg instruktionerne i tidligere lektioner for at publicere din funktionsapp til skyen. Når den er publiceret, vil URL'en være `https://<APP_NAME>.azurewebsites.net/api/text-to-timer`, hvor `<APP_NAME>` vil være navnet på din funktionsapp. Sørg også for at publicere dine lokale indstillinger.

      Når du arbejder med HTTP-triggere, er de som standard sikret med en funktionsappnøgle. For at få denne nøgle skal du køre følgende kommando:

      ```sh
      az functionapp keys list --resource-group smart-timer \
                               --name <APP_NAME>                               
      ```

      Kopiér værdien af `default`-posten fra sektionen `functionKeys`.

      ```output
      {
        "functionKeys": {
          "default": "sQO1LQaeK9N1qYD6SXeb/TctCmwQEkToLJU6Dw8TthNeUH8VA45hlA=="
        },
        "masterKey": "RSKOAIlyvvQEQt9dfpabJT018scaLpQu9p1poHIMCxx5LYrIQZyQ/g==",
        "systemKeys": {}
      }
      ```

      Denne nøgle skal tilføjes som en forespørgselsparameter til URL'en, så den endelige URL vil være `https://<APP_NAME>.azurewebsites.net/api/text-to-timer?code=<FUNCTION_KEY>`, hvor `<APP_NAME>` vil være navnet på din funktionsapp, og `<FUNCTION_KEY>` vil være din standard funktionsnøgle.

      > 💁 Du kan ændre typen af autorisation for HTTP-triggeren ved at bruge `authlevel`-indstillingen i filen `function.json`. Du kan læse mere om dette i [konfigurationssektionen af Azure Functions HTTP-triggerdokumentationen på Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python#configuration).

    * Kør funktionsappen lokalt, og tilgå den ved hjælp af IP-adressen – du kan finde din computers IP-adresse på dit lokale netværk og bruge den til at opbygge URL'en.

      Find din IP-adresse:

      * På Windows 10, følg [guiden til at finde din IP-adresse](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn).
      * På macOS, følg [guiden til at finde din IP-adresse på en Mac](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac).
      * På Linux, følg sektionen om at finde din private IP-adresse i [guiden til at finde din IP-adresse i Linux](https://opensource.com/article/18/5/how-find-ip-address-linux).

      Når du har din IP-adresse, vil du kunne tilgå funktionen på `http://`.

:7071/api/text-to-timer`, hvor `<IP_ADDRESS>` vil være din IP-adresse, for eksempel `http://192.168.1.10:7071/api/text-to-timer`.

      > 💁 Bemærk, at dette bruger port 7071, så efter IP-adressen skal du tilføje `:7071`.

      > 💁 Dette vil kun fungere, hvis din IoT-enhed er på samme netværk som din computer.

1. Test endpointet ved at tilgå det med curl.

---

## 🚀 Udfordring

Der er mange måder at anmode om det samme, som for eksempel at sætte en timer. Tænk på forskellige måder at gøre dette på, og brug dem som eksempler i din LUIS-app. Test dem for at se, hvor godt din model kan håndtere flere måder at anmode om en timer.

## Quiz efter forelæsning

[Quiz efter forelæsning](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/44)

## Gennemgang & Selvstudie

* Læs mere om LUIS og dets funktioner på [Language Understanding (LUIS) dokumentationssiden på Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/luis/?WT.mc_id=academic-17441-jabenn)
* Læs mere om sprogforståelse på [natural-language understanding siden på Wikipedia](https://wikipedia.org/wiki/Natural-language_understanding)
* Læs mere om HTTP-triggere i [Azure Functions HTTP trigger dokumentationen på Microsoft docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python)

## Opgave

[Annuller timeren](assignment.md)

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på at sikre nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der opstår som følge af brugen af denne oversættelse.