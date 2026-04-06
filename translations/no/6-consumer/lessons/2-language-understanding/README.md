# Forstå språk

![En sketchnote-oversikt over denne leksjonen](../../../../../translated_images/no/lesson-22.6148ea28500d9e00.webp)

> Sketchnote av [Nitya Narasimhan](https://github.com/nitya). Klikk på bildet for en større versjon.

## Quiz før forelesning

[Quiz før forelesning](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/43)

## Introduksjon

I forrige leksjon konverterte du tale til tekst. For at dette skal kunne brukes til å programmere en smart timer, må koden din forstå hva som ble sagt. Du kunne anta at brukeren vil si en fast frase, som "Sett en 3-minutters timer", og analysere den uttrykket for å finne ut hvor lenge timeren skal være, men dette er ikke veldig brukervennlig. Hvis en bruker sier "Sett en timer for 3 minutter", ville du eller jeg forstå hva de mener, men koden din ville ikke, da den forventer en fast frase.

Dette er hvor språkforståelse kommer inn, ved å bruke AI-modeller til å tolke tekst og returnere de nødvendige detaljene, for eksempel å kunne ta både "Sett en 3-minutters timer" og "Sett en timer for 3 minutter", og forstå at en timer er nødvendig for 3 minutter.

I denne leksjonen vil du lære om språkforståelsesmodeller, hvordan du lager dem, trener dem og bruker dem i koden din.

I denne leksjonen dekker vi:

* [Språkforståelse](../../../../../6-consumer/lessons/2-language-understanding)
* [Opprett en språkforståelsesmodell](../../../../../6-consumer/lessons/2-language-understanding)
* [Intensjoner og enheter](../../../../../6-consumer/lessons/2-language-understanding)
* [Bruk språkforståelsesmodellen](../../../../../6-consumer/lessons/2-language-understanding)

## Språkforståelse

Mennesker har brukt språk til å kommunisere i hundretusenvis av år. Vi kommuniserer med ord, lyder eller handlinger og forstår hva som blir sagt, både betydningen av ordene, lydene eller handlingene, men også deres kontekst. Vi forstår oppriktighet og sarkasme, som gjør at de samme ordene kan bety forskjellige ting avhengig av tonen i stemmen vår.

✅ Tenk på noen av samtalene du har hatt nylig. Hvor mye av samtalen ville være vanskelig for en datamaskin å forstå fordi den trenger kontekst?

Språkforståelse, også kalt naturlig språkforståelse, er en del av et felt innen kunstig intelligens kalt naturlig språkbehandling (eller NLP), og handler om leseforståelse, å prøve å forstå detaljene i ord eller setninger. Hvis du bruker en stemmeassistent som Alexa eller Siri, har du brukt språkforståelsestjenester. Dette er AI-tjenestene bak kulissene som konverterer "Alexa, spill det nyeste albumet til Taylor Swift" til at datteren min danser rundt i stuen til favorittlåtene sine.

> 💁 Datamaskiner, til tross for alle sine fremskritt, har fortsatt en lang vei å gå for virkelig å forstå tekst. Når vi refererer til språkforståelse med datamaskiner, mener vi ikke noe i nærheten av så avansert som menneskelig kommunikasjon, men heller å ta noen ord og trekke ut nøkkeldetaljer.

Som mennesker forstår vi språk uten egentlig å tenke over det. Hvis jeg ba en annen person om å "spille det nyeste albumet til Taylor Swift", ville de instinktivt vite hva jeg mente. For en datamaskin er dette vanskeligere. Den må ta ordene, konvertert fra tale til tekst, og finne ut følgende informasjon:

* Musikk må spilles
* Musikken er av artisten Taylor Swift
* Den spesifikke musikken er et helt album med flere spor i rekkefølge
* Taylor Swift har mange album, så de må sorteres kronologisk, og det nyeste er det som kreves

✅ Tenk på noen andre setninger du har sagt når du har kommet med forespørsler, som å bestille kaffe eller be et familiemedlem om å gi deg noe. Prøv å bryte dem ned i de detaljene en datamaskin ville trenge å trekke ut for å forstå setningen.

Språkforståelsesmodeller er AI-modeller som er trent til å trekke ut visse detaljer fra språk, og deretter trenes for spesifikke oppgaver ved hjelp av overføringslæring, på samme måte som du trente en Custom Vision-modell ved hjelp av et lite sett med bilder. Du kan ta en modell og deretter trene den med teksten du vil at den skal forstå.

## Opprett en språkforståelsesmodell

![LUIS-logoen](../../../../../translated_images/no/luis-logo.5cb4f3e88c020ee6.webp)

Du kan opprette språkforståelsesmodeller ved hjelp av LUIS, en språkforståelsestjeneste fra Microsoft som er en del av Cognitive Services.

### Oppgave - opprett en forfatterressurs

For å bruke LUIS, må du opprette en forfatterressurs.

1. Bruk følgende kommando for å opprette en forfatterressurs i ressursgruppen din `smart-timer`:

    ```python
    az cognitiveservices account create --name smart-timer-luis-authoring \
                                        --resource-group smart-timer \
                                        --kind LUIS.Authoring \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Erstatt `<location>` med plasseringen du brukte da du opprettet ressursgruppen.

    > ⚠️ LUIS er ikke tilgjengelig i alle regioner, så hvis du får følgende feil:
    >
    > ```output
    > InvalidApiSetId: The account type 'LUIS.Authoring' is either invalid or unavailable in given region.
    > ```
    >
    > velg en annen region.

    Dette vil opprette en gratis LUIS-forfatterressurs.

### Oppgave - opprett en språkforståelsesapp

1. Åpne LUIS-portalen på [luis.ai](https://luis.ai?WT.mc_id=academic-17441-jabenn) i nettleseren din, og logg inn med den samme kontoen du har brukt for Azure.

1. Følg instruksjonene i dialogen for å velge Azure-abonnementet ditt, og velg deretter ressursen `smart-timer-luis-authoring` som du nettopp har opprettet.

1. Fra listen *Conversation apps*, velg knappen **New app** for å opprette en ny applikasjon. Navngi den nye appen `smart-timer`, og sett *Culture* til språket ditt.

    > 💁 Det er et felt for en prediksjonsressurs. Du kan opprette en annen ressurs bare for prediksjon, men den gratis forfatterressursen tillater 1 000 prediksjoner per måned, noe som bør være nok for utvikling, så du kan la dette stå tomt.

1. Les gjennom veiledningen som vises når du oppretter appen for å få en forståelse av trinnene du må ta for å trene språkforståelsesmodellen. Lukk denne veiledningen når du er ferdig.

## Intensjoner og enheter

Språkforståelse er basert på *intensjoner* og *enheter*. Intensjoner er hva ordene har som hensikt, for eksempel å spille musikk, sette en timer eller bestille mat. Enheter er hva intensjonen refererer til, som albumet, lengden på timeren eller typen mat. Hver setning som modellen tolker, bør ha minst én intensjon, og eventuelt én eller flere enheter.

Noen eksempler:

| Setning                                             | Intensjon        | Enheter                                    |
| --------------------------------------------------- | ---------------- | ------------------------------------------ |
| "Spill det nyeste albumet til Taylor Swift"         | *spill musikk*   | *det nyeste albumet til Taylor Swift*      |
| "Sett en 3-minutters timer"                         | *sett en timer*  | *3 minutter*                               |
| "Avbryt timeren min"                                | *avbryt en timer*| Ingen                                      |
| "Bestill 3 store pizzaer med ananas og en cæsarsalat" | *bestill mat*    | *3 store pizzaer med ananas*, *cæsarsalat* |

✅ Med setningene du tenkte på tidligere, hva ville være intensjonen og eventuelle enheter i den setningen?

For å trene LUIS, må du først sette enhetene. Disse kan være en fast liste med termer, eller læres fra teksten. For eksempel kan du gi en fast liste med mat tilgjengelig fra menyen din, med variasjoner (eller synonymer) av hvert ord, som *aubergine* og *eggplant* som variasjoner av *aubergine*. LUIS har også forhåndsbygde enheter som kan brukes, som tall og steder.

For å sette en timer, kan du ha én enhet som bruker forhåndsbygde tall-enheter for tiden, og en annen for enhetene, som minutter og sekunder. Hver enhet vil ha flere variasjoner for å dekke entalls- og flertallsformer - som minutt og minutter.

Når enhetene er definert, oppretter du intensjoner. Disse læres av modellen basert på eksempels setninger som du gir (kjent som ytringer). For eksempel, for en *sett timer*-intensjon, kan du gi følgende setninger:

* `sett en 1-sekunds timer`
* `sett en timer for 1 minutt og 12 sekunder`
* `sett en timer for 3 minutter`
* `sett en 9-minutters 30-sekunders timer`

Du forteller deretter LUIS hvilke deler av disse setningene som samsvarer med enhetene:

![Setningen sett en timer for 1 minutt og 12 sekunder delt inn i enheter](../../../../../translated_images/no/sentence-as-intent-entities.301401696f992259.webp)

Setningen `sett en timer for 1 minutt og 12 sekunder` har intensjonen `sett timer`. Den har også 2 enheter med 2 verdier hver:

|            | tid  | enhet  |
| ---------- | ---: | ------ |
| 1 minutt   | 1    | minutt |
| 12 sekunder| 12   | sekund |

For å trene en god modell, trenger du et utvalg av forskjellige eksempels setninger for å dekke de mange forskjellige måtene noen kan be om det samme.

> 💁 Som med enhver AI-modell, jo mer data og jo mer nøyaktige data du bruker til å trene, desto bedre blir modellen.

✅ Tenk på de forskjellige måtene du kan be om det samme og forvente at en person forstår.

### Oppgave - legg til enheter i språkforståelsesmodellen

For timeren må du legge til 2 enheter - én for tidsenheten (minutter eller sekunder), og én for antall minutter eller sekunder.

Du finner instruksjoner for bruk av LUIS-portalen i [Quickstart: Build your app in LUIS portal-dokumentasjonen på Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/luis/luis-get-started-create-app?WT.mc_id=academic-17441-jabenn).

1. Fra LUIS-portalen, velg fanen *Entities* og legg til den forhåndsbygde enheten *number* ved å velge knappen **Add prebuilt entity**, og deretter velge *number* fra listen.

1. Opprett en ny enhet for tidsenheten ved å bruke knappen **Create**. Navngi enheten `time unit` og sett typen til *List*. Legg til verdier for `minute` og `second` i listen *Normalized values*, og legg til entalls- og flertallsformene i listen *synonyms*. Trykk `return` etter å ha lagt til hvert synonym for å legge det til i listen.

    | Normalisert verdi | Synonymer       |
    | ----------------- | --------------- |
    | minutt            | minutt, minutter|
    | sekund            | sekund, sekunder|

### Oppgave - legg til intensjoner i språkforståelsesmodellen

1. Fra fanen *Intents*, velg knappen **Create** for å opprette en ny intensjon. Navngi denne intensjonen `set timer`.

1. I eksemplene, skriv inn forskjellige måter å sette en timer på ved hjelp av både minutter, sekunder og kombinasjoner av minutter og sekunder. Eksempler kan være:

    * `sett en 1-sekunds timer`
    * `sett en 4-minutters timer`
    * `sett en fire-minutters seks-sekunders timer`
    * `sett en 9-minutters 30-sekunders timer`
    * `sett en timer for 1 minutt og 12 sekunder`
    * `sett en timer for 3 minutter`
    * `sett en timer for 3 minutter og 1 sekund`
    * `sett en timer for tre minutter og ett sekund`
    * `sett en timer for 1 minutt og 1 sekund`
    * `sett en timer for 30 sekunder`
    * `sett en timer for 1 sekund`

    Bland tall som ord og numeriske verdier slik at modellen lærer å håndtere begge deler.

1. Når du skriver inn hvert eksempel, vil LUIS begynne å oppdage enheter og understreke og merke dem den finner.

    ![Eksemplene med tallene og tidsenhetene understreket av LUIS](../../../../../translated_images/no/luis-intent-examples.25716580b2d2723c.webp)

### Oppgave - tren og test modellen

1. Når enhetene og intensjonene er konfigurert, kan du trene modellen ved å bruke knappen **Train** i toppmenyen. Velg denne knappen, og modellen skal trenes i løpet av noen sekunder. Knappen vil være grå mens treningen pågår, og bli aktivert igjen når den er ferdig.

1. Velg knappen **Test** fra toppmenyen for å teste språkforståelsesmodellen. Skriv inn tekst som `sett en timer for 5 minutter og 4 sekunder` og trykk return. Setningen vil vises i en boks under tekstboksen du skrev inn i, og under det vil være *top intent*, eller intensjonen som ble oppdaget med høyest sannsynlighet. Dette bør være `set timer`. Intensjonsnavnet vil bli etterfulgt av sannsynligheten for at den oppdagede intensjonen var riktig.

1. Velg alternativet **Inspect** for å se en detaljert oversikt over resultatene. Du vil se den høyest scorende intensjonen med prosentvis sannsynlighet, sammen med lister over de oppdagede enhetene.

1. Lukk *Test*-panelet når du er ferdig med testing.

### Oppgave - publiser modellen

For å bruke denne modellen fra kode, må du publisere den. Når du publiserer fra LUIS, kan du publisere til enten et staging-miljø for testing eller et produksjonsmiljø for full utgivelse. I denne leksjonen er et staging-miljø tilstrekkelig.

1. Fra LUIS-portalen, velg knappen **Publish** fra toppmenyen.

1. Sørg for at *Staging slot* er valgt, og velg deretter **Done**. Du vil se en melding når appen er publisert.

1. Du kan teste dette ved hjelp av curl. For å bygge curl-kommandoen trenger du tre verdier - endepunktet, applikasjons-ID (App ID) og en API-nøkkel. Disse kan nås fra fanen **MANAGE** som kan velges fra toppmenyen.

    1. Fra seksjonen *Settings*, kopier App ID.
1. Fra *Azure Resources*-seksjonen, velg *Authoring Resource*, og kopier *Primary Key* og *Endpoint URL*.

1. Kjør følgende curl-kommando i kommandolinjen eller terminalen din:

    ```sh
    curl "<endpoint url>/luis/prediction/v3.0/apps/<app id>/slots/staging/predict" \
          --request GET \
          --get \
          --data "subscription-key=<primary key>" \
          --data "verbose=false" \
          --data "show-all-intents=true" \
          --data-urlencode "query=<sentence>"
    ```

    Erstatt `<endpoint url>` med Endpoint URL fra *Azure Resources*-seksjonen.

    Erstatt `<app id>` med App ID fra *Settings*-seksjonen.

    Erstatt `<primary key>` med Primary Key fra *Azure Resources*-seksjonen.

    Erstatt `<sentence>` med setningen du vil teste.

1. Resultatet av denne forespørselen vil være et JSON-dokument som beskriver spørringen, den mest sannsynlige intensjonen, og en liste over entiteter sortert etter type.

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

    JSON-dokumentet ovenfor kom fra en spørring med `set a timer for 45 minutes and 12 seconds`:

    * `set timer` var den mest sannsynlige intensjonen med en sannsynlighet på 97 %.
    * To *number*-entiteter ble oppdaget, `45` og `12`.
    * To *time-unit*-entiteter ble oppdaget, `minute` og `second`.

## Bruk språkforståelsesmodellen

Når LUIS-modellen er publisert, kan den kalles fra kode. I tidligere leksjoner har du brukt en IoT Hub for å håndtere kommunikasjon med skytjenester, sende telemetri og lytte etter kommandoer. Dette er veldig asynkront – når telemetri sendes, venter ikke koden din på et svar, og hvis skytjenesten er nede, vil du ikke vite det.

For en smart timer ønsker vi et umiddelbart svar, slik at vi kan informere brukeren om at en timer er satt, eller varsle dem om at skytjenestene ikke er tilgjengelige. For å gjøre dette vil IoT-enheten din kalle en web-endepunkt direkte, i stedet for å stole på en IoT Hub.

I stedet for å kalle LUIS direkte fra IoT-enheten, kan du bruke serverløs kode med en annen type trigger – en HTTP-trigger. Dette lar funksjonsappen din lytte etter REST-forespørsler og svare på dem. Denne funksjonen vil være et REST-endepunkt som enheten din kan kalle.

> 💁 Selv om du kan kalle LUIS direkte fra IoT-enheten din, er det bedre å bruke noe som serverløs kode. På denne måten, når du vil endre LUIS-appen du kaller, for eksempel når du trener en bedre modell eller trener en modell på et annet språk, trenger du bare å oppdatere sky-koden din, ikke distribuere kode på nytt til potensielt tusenvis eller millioner av IoT-enheter.

### Oppgave – opprett en serverløs funksjonsapp

1. Opprett en Azure Functions-app kalt `smart-timer-trigger`, og åpne denne i VS Code.

1. Legg til en HTTP-trigger i denne appen kalt `speech-trigger` ved å bruke følgende kommando fra terminalen i VS Code:

    ```sh
    func new --name text-to-timer --template "HTTP trigger"
    ```

    Dette vil opprette en HTTP-trigger kalt `text-to-timer`.

1. Test HTTP-triggeren ved å kjøre funksjonsappen. Når den kjører, vil du se endepunktet oppført i utdataene:

    ```output
    Functions:
    
            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    ```

    Test dette ved å laste inn [http://localhost:7071/api/text-to-timer](http://localhost:7071/api/text-to-timer) URL-en i nettleseren din.

    ```output
    This HTTP triggered function executed successfully. Pass a name in the query string or in the request body for a personalized response.
    ```

### Oppgave – bruk språkforståelsesmodellen

1. SDK for LUIS er tilgjengelig via en Pip-pakke. Legg til følgende linje i `requirements.txt`-filen for å legge til avhengigheten til denne pakken:

    ```sh
    azure-cognitiveservices-language-luis
    ```

1. Sørg for at terminalen i VS Code har det virtuelle miljøet aktivert, og kjør følgende kommando for å installere Pip-pakkene:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 Hvis du får feil, kan det hende du må oppgradere pip med følgende kommando:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Legg til nye oppføringer i `local.settings.json`-filen for LUIS API Key, Endpoint URL, og App ID fra **MANAGE**-fanen i LUIS-portalen:

    ```JSON
    "LUIS_KEY": "<primary key>",
    "LUIS_ENDPOINT_URL": "<endpoint url>",
    "LUIS_APP_ID": "<app id>"
    ```

    Erstatt `<endpoint url>` med Endpoint URL fra *Azure Resources*-seksjonen i **MANAGE**-fanen. Dette vil være `https://<location>.api.cognitive.microsoft.com/`.

    Erstatt `<app id>` med App ID fra *Settings*-seksjonen i **MANAGE**-fanen.

    Erstatt `<primary key>` med Primary Key fra *Azure Resources*-seksjonen i **MANAGE**-fanen.

1. Legg til følgende imports i `__init__.py`-filen:

    ```python
    import json
    import os
    from azure.cognitiveservices.language.luis.runtime import LUISRuntimeClient
    from msrest.authentication import CognitiveServicesCredentials
    ```

    Dette importerer noen systembiblioteker, samt bibliotekene for å interagere med LUIS.

1. Slett innholdet i `main`-metoden, og legg til følgende kode:

    ```python
    luis_key = os.environ['LUIS_KEY']
    endpoint_url = os.environ['LUIS_ENDPOINT_URL']
    app_id = os.environ['LUIS_APP_ID']
    
    credentials = CognitiveServicesCredentials(luis_key)
    client = LUISRuntimeClient(endpoint=endpoint_url, credentials=credentials)
    ```

    Dette laster inn verdiene du la til i `local.settings.json`-filen for LUIS-appen din, oppretter et credentials-objekt med API-nøkkelen din, og deretter oppretter en LUIS-klient for å interagere med LUIS-appen din.

1. Denne HTTP-triggeren vil bli kalt med teksten som skal forstås som JSON, med teksten i en egenskap kalt `text`. Følgende kode trekker ut verdien fra kroppen av HTTP-forespørselen og logger den til konsollen. Legg til denne koden i `main`-funksjonen:

    ```python
    req_body = req.get_json()
    text = req_body['text']
    logging.info(f'Request - {text}')
    ```

1. Prediksjoner blir forespurt fra LUIS ved å sende en prediksjonsforespørsel – et JSON-dokument som inneholder teksten som skal predikeres. Opprett dette med følgende kode:

    ```python
    prediction_request = { 'query' : text }
    ```

1. Denne forespørselen kan deretter sendes til LUIS, ved å bruke staging-slot som appen din ble publisert til:

    ```python
    prediction_response = client.prediction.get_slot_prediction(app_id, 'Staging', prediction_request)
    ```

1. Prediksjonsresponsen inneholder den mest sannsynlige intensjonen – intensjonen med høyest prediksjonsscore, sammen med entitetene. Hvis den mest sannsynlige intensjonen er `set timer`, kan entitetene leses for å få tiden som trengs for timeren:

    ```python
    if prediction_response.prediction.top_intent == 'set timer':
        numbers = prediction_response.prediction.entities['number']
        time_units = prediction_response.prediction.entities['time unit']
        total_seconds = 0
    ```

    `number`-entitetene vil være en liste med tall. For eksempel, hvis du sa *"Set a four minute 17 second timer."*, vil `number`-listen inneholde 2 heltall – 4 og 17.

    `time unit`-entitetene vil være en liste med lister med strenger, der hver tidsenhet er en liste med strenger inne i listen. For eksempel, hvis du sa *"Set a four minute 17 second timer."*, vil `time unit`-listen inneholde 2 lister med enkeltverdier – `['minute']` og `['second']`.

    JSON-versjonen av disse entitetene for *"Set a four minute 17 second timer."* er:

    ```json
    {
        "number": [4, 17],
        "time unit": [
            ["minute"],
            ["second"]
        ]
    }
    ```

    Denne koden definerer også en teller for total tid for timeren i sekunder. Denne vil bli fylt med verdiene fra entitetene.

1. Entitetene er ikke koblet sammen, men vi kan gjøre noen antakelser om dem. De vil være i den rekkefølgen de ble sagt, så posisjonen i listen kan brukes til å avgjøre hvilket tall som matcher hvilken tidsenhet. For eksempel:

    * *"Set a 30 second timer"* – dette vil ha ett tall, `30`, og én tidsenhet, `second`, så det ene tallet vil matche den ene tidsenheten.
    * *"Set a 2 minute and 30 second timer"* – dette vil ha to tall, `2` og `30`, og to tidsenheter, `minute` og `second`, så det første tallet vil være for den første tidsenheten (2 minutter), og det andre tallet for den andre tidsenheten (30 sekunder).

    Følgende kode henter antall elementer i `number`-entitetene, og bruker dette til å trekke ut det første elementet fra hver liste, deretter det andre, og så videre. Legg dette inne i `if`-blokken.

    ```python
    for i in range(0, len(numbers)):
        number = numbers[i]
        time_unit = time_units[i][0]
    ```

    For *"Set a four minute 17 second timer."*, vil dette loope to ganger, og gi følgende verdier:

    | loop count | `number` | `time_unit` |
    | ---------: | -------: | ----------- |
    | 0          | 4        | minute      |
    | 1          | 17       | second      |

1. Inne i denne loopen, bruk tallet og tidsenheten til å beregne total tid for timeren, og legg til 60 sekunder for hver minutt, og antall sekunder for eventuelle sekunder.

    ```python
    if time_unit == 'minute':
        total_seconds += number * 60
    else:
        total_seconds += number
    ```

1. Utenfor denne loopen gjennom entitetene, logg total tid for timeren:

    ```python
    logging.info(f'Timer required for {total_seconds} seconds')
    ```

1. Antall sekunder må returneres fra funksjonen som en HTTP-respons. På slutten av `if`-blokken, legg til følgende:

    ```python
    payload = {
        'seconds': total_seconds
    }
    return func.HttpResponse(json.dumps(payload), status_code=200)
    ```

    Denne koden oppretter en payload som inneholder det totale antallet sekunder for timeren, konverterer det til en JSON-streng og returnerer det som et HTTP-resultat med statuskode 200, som betyr at forespørselen var vellykket.

1. Til slutt, utenfor `if`-blokken, håndter hvis intensjonen ikke ble gjenkjent ved å returnere en feilkode:

    ```python
    return func.HttpResponse(status_code=404)
    ```

    404 er statuskoden for *ikke funnet*.

1. Kjør funksjonsappen og test den med curl.

    ```sh
    curl --request POST 'http://localhost:7071/api/text-to-timer' \
         --header 'Content-Type: application/json' \
         --include \
         --data '{"text":"<text>"}'
    ```

    Erstatt `<text>` med teksten for forespørselen din, for eksempel `set a 2 minutes 27 second timer`.

    Du vil se følgende utdata fra funksjonsappen:

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

    Curl-kommandoen vil returnere følgende:

    ```output
    HTTP/1.1 200 OK
    Date: Tue, 29 Jun 2021 01:14:11 GMT
    Content-Type: text/plain; charset=utf-8
    Server: Kestrel
    Transfer-Encoding: chunked
    
    {"seconds": 147}
    ```

    Antall sekunder for timeren er i `"seconds"`-verdien.

> 💁 Du finner denne koden i [code/functions](../../../../../6-consumer/lessons/2-language-understanding/code/functions)-mappen.

### Oppgave – gjør funksjonen din tilgjengelig for IoT-enheten din

1. For at IoT-enheten din skal kunne kalle REST-endepunktet ditt, må den vite URL-en. Når du fikk tilgang til det tidligere, brukte du `localhost`, som er en snarvei for å få tilgang til REST-endepunkter på din lokale maskin. For å gi IoT-enheten din tilgang, må du enten publisere til skyen, eller finne IP-adressen din for å få tilgang lokalt.

    > ⚠️ Hvis du bruker en Wio Terminal, er det enklere å kjøre funksjonsappen lokalt, da det vil være en avhengighet til biblioteker som gjør at du ikke kan distribuere funksjonsappen på samme måte som du har gjort før. Kjør funksjonsappen lokalt og få tilgang via datamaskinens IP-adresse. Hvis du ønsker å distribuere til skyen, vil informasjon bli gitt i en senere leksjon om hvordan du gjør dette.

    * Publiser funksjonsappen – følg instruksjonene i tidligere leksjoner for å publisere funksjonsappen din til skyen. Når den er publisert, vil URL-en være `https://<APP_NAME>.azurewebsites.net/api/text-to-timer`, der `<APP_NAME>` vil være navnet på funksjonsappen din. Sørg også for å publisere dine lokale innstillinger.

      Når du arbeider med HTTP-triggere, er de som standard sikret med en funksjonsappnøkkel. For å få denne nøkkelen, kjør følgende kommando:

      ```sh
      az functionapp keys list --resource-group smart-timer \
                               --name <APP_NAME>                               
      ```

      Kopier verdien av `default`-oppføringen fra `functionKeys`-seksjonen.

      ```output
      {
        "functionKeys": {
          "default": "sQO1LQaeK9N1qYD6SXeb/TctCmwQEkToLJU6Dw8TthNeUH8VA45hlA=="
        },
        "masterKey": "RSKOAIlyvvQEQt9dfpabJT018scaLpQu9p1poHIMCxx5LYrIQZyQ/g==",
        "systemKeys": {}
      }
      ```

      Denne nøkkelen må legges til som en spørringsparameter i URL-en, så den endelige URL-en vil være `https://<APP_NAME>.azurewebsites.net/api/text-to-timer?code=<FUNCTION_KEY>`, der `<APP_NAME>` vil være navnet på funksjonsappen din, og `<FUNCTION_KEY>` vil være din standard funksjonsnøkkel.

      > 💁 Du kan endre typen autorisasjon for HTTP-triggeren ved å bruke `authlevel`-innstillingen i `function.json`-filen. Du kan lese mer om dette i [konfigurasjonsseksjonen i dokumentasjonen for Azure Functions HTTP-trigger på Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python#configuration).

    * Kjør funksjonsappen lokalt, og få tilgang ved hjelp av IP-adressen – du kan finne IP-adressen til datamaskinen din på det lokale nettverket, og bruke den til å bygge URL-en.

      Finn IP-adressen din:

      * På Windows 10, følg [veiledningen for å finne IP-adressen din](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn).
      * På macOS, følg [veiledningen for hvordan du finner IP-adressen din på en Mac](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac).
      * På Linux, følg delen om å finne din private IP-adresse i [veiledningen for hvordan du finner IP-adressen din i Linux](https://opensource.com/article/18/5/how-find-ip-address-linux).

      Når du har IP-adressen din, vil du kunne få tilgang til funksjonen på `http://`.

:7071/api/text-to-timer`, hvor `<IP_ADDRESS>` vil være din IP-adresse, for eksempel `http://192.168.1.10:7071/api/text-to-timer`.

      > 💁 Merk at dette bruker port 7071, så etter IP-adressen må du ha `:7071`.

      > 💁 Dette vil bare fungere hvis IoT-enheten din er på samme nettverk som datamaskinen din.

1. Test endepunktet ved å bruke curl for å få tilgang til det.

---

## 🚀 Utfordring

Det finnes mange måter å be om det samme, som å sette en timer. Tenk på ulike måter å gjøre dette på, og bruk dem som eksempler i LUIS-appen din. Test disse for å se hvor godt modellen din kan håndtere flere måter å be om en timer.

## Quiz etter forelesning

[Quiz etter forelesning](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/44)

## Gjennomgang & Selvstudium

* Les mer om LUIS og dets funksjoner på [Language Understanding (LUIS) dokumentasjonssiden på Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/luis/?WT.mc_id=academic-17441-jabenn)
* Les mer om språkforståelse på [natural-language understanding-siden på Wikipedia](https://wikipedia.org/wiki/Natural-language_understanding)
* Les mer om HTTP-triggere i [Azure Functions HTTP trigger-dokumentasjonen på Microsoft docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python)

## Oppgave

[Avbryt timeren](assignment.md)

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.