# Förstå språk

![En sketchnote-översikt av denna lektion](../../../../../translated_images/sv/lesson-22.6148ea28500d9e00.webp)

> Sketchnote av [Nitya Narasimhan](https://github.com/nitya). Klicka på bilden för en större version.

## Förkunskapstest

[Förkunskapstest](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/43)

## Introduktion

I den senaste lektionen konverterade du tal till text. För att detta ska kunna användas för att programmera en smart timer behöver din kod förstå vad som sades. Du skulle kunna anta att användaren säger en fast fras, som "Ställ in en timer på 3 minuter", och analysera det uttrycket för att få fram hur lång tid timern ska vara, men detta är inte särskilt användarvänligt. Om en användare istället säger "Ställ in en timer för 3 minuter" skulle du eller jag förstå vad de menar, men din kod skulle inte göra det eftersom den förväntar sig en fast fras.

Det är här språkförståelse kommer in, genom att använda AI-modeller för att tolka text och returnera de detaljer som behövs. Till exempel att kunna tolka både "Ställ in en timer på 3 minuter" och "Ställ in en timer för 3 minuter" och förstå att en timer behövs för 3 minuter.

I denna lektion kommer du att lära dig om modeller för språkförståelse, hur man skapar dem, tränar dem och använder dem i din kod.

I denna lektion kommer vi att täcka:

* [Språkförståelse](../../../../../6-consumer/lessons/2-language-understanding)
* [Skapa en modell för språkförståelse](../../../../../6-consumer/lessons/2-language-understanding)
* [Intentioner och entiteter](../../../../../6-consumer/lessons/2-language-understanding)
* [Använd modellen för språkförståelse](../../../../../6-consumer/lessons/2-language-understanding)

## Språkförståelse

Människor har använt språk för att kommunicera i hundratusentals år. Vi kommunicerar med ord, ljud eller handlingar och förstår vad som sägs, både betydelsen av orden, ljuden eller handlingarna, men också deras kontext. Vi förstår uppriktighet och sarkasm, vilket gör att samma ord kan betyda olika saker beroende på tonfallet.

✅ Tänk på några av de samtal du nyligen har haft. Hur mycket av samtalet skulle vara svårt för en dator att förstå eftersom det kräver kontext?

Språkförståelse, även kallat naturlig språkförståelse, är en del av ett område inom artificiell intelligens som kallas naturlig språkbehandling (eller NLP) och handlar om läsförståelse, att försöka förstå detaljerna i ord eller meningar. Om du använder en röstassistent som Alexa eller Siri har du använt tjänster för språkförståelse. Dessa är AI-tjänster som omvandlar "Alexa, spela det senaste albumet av Taylor Swift" till att min dotter dansar runt i vardagsrummet till sina favoritlåtar.

> 💁 Datorer, trots alla framsteg, har fortfarande en lång väg att gå för att verkligen förstå text. När vi pratar om språkförståelse med datorer menar vi inte något som ens är i närheten av mänsklig kommunikation, utan snarare att ta några ord och extrahera nyckeldetaljer.

Som människor förstår vi språk utan att egentligen tänka på det. Om jag bad en annan människa att "spela det senaste albumet av Taylor Swift" skulle de instinktivt veta vad jag menade. För en dator är detta svårare. Den skulle behöva ta orden, konverterade från tal till text, och arbeta fram följande information:

* Musik behöver spelas
* Musiken är av artisten Taylor Swift
* Den specifika musiken är ett helt album med flera spår i ordning
* Taylor Swift har många album, så de behöver sorteras kronologiskt och det senast publicerade är det som krävs

✅ Tänk på några andra meningar du har sagt när du gjort förfrågningar, som att beställa kaffe eller be en familjemedlem att ge dig något. Försök att bryta ner dem i de informationsdelar en dator skulle behöva extrahera för att förstå meningen.

Modeller för språkförståelse är AI-modeller som tränas för att extrahera vissa detaljer från språk och sedan tränas för specifika uppgifter med hjälp av transfer learning, på samma sätt som du tränade en Custom Vision-modell med en liten uppsättning bilder. Du kan ta en modell och sedan träna den med den text du vill att den ska förstå.

## Skapa en modell för språkförståelse

![LUIS-logotypen](../../../../../translated_images/sv/luis-logo.5cb4f3e88c020ee6.webp)

Du kan skapa modeller för språkförståelse med hjälp av LUIS, en tjänst för språkförståelse från Microsoft som är en del av Cognitive Services.

### Uppgift - skapa en resurs för författande

För att använda LUIS behöver du skapa en resurs för författande.

1. Använd följande kommando för att skapa en resurs för författande i din `smart-timer`-resursgrupp:

    ```python
    az cognitiveservices account create --name smart-timer-luis-authoring \
                                        --resource-group smart-timer \
                                        --kind LUIS.Authoring \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Ersätt `<location>` med platsen du använde när du skapade resursgruppen.

    > ⚠️ LUIS är inte tillgängligt i alla regioner, så om du får följande fel:
    >
    > ```output
    > InvalidApiSetId: The account type 'LUIS.Authoring' is either invalid or unavailable in given region.
    > ```
    >
    > välj en annan region.

    Detta kommer att skapa en LUIS-resurs för författande med gratisnivå.

### Uppgift - skapa en app för språkförståelse

1. Öppna LUIS-portalen på [luis.ai](https://luis.ai?WT.mc_id=academic-17441-jabenn) i din webbläsare och logga in med samma konto som du har använt för Azure.

1. Följ instruktionerna i dialogrutan för att välja ditt Azure-abonnemang och välj sedan resursen `smart-timer-luis-authoring` som du just har skapat.

1. Från listan *Conversation apps* väljer du knappen **New app** för att skapa en ny applikation. Namnge den nya appen `smart-timer` och ställ in *Culture* på ditt språk.

    > 💁 Det finns ett fält för en prediktionsresurs. Du kan skapa en andra resurs bara för prediktion, men resursen för gratis författande tillåter 1 000 prediktioner per månad, vilket borde räcka för utveckling, så du kan lämna detta tomt.

1. Läs igenom guiden som visas när du skapar appen för att få en förståelse för de steg du behöver ta för att träna modellen för språkförståelse. Stäng guiden när du är klar.

## Intentioner och entiteter

Språkförståelse baseras på *intentioner* och *entiteter*. Intentioner är vad orden syftar till, till exempel att spela musik, ställa in en timer eller beställa mat. Entiteter är vad intentionen hänvisar till, som albumet, längden på timern eller typen av mat. Varje mening som modellen tolkar bör ha minst en intention och eventuellt en eller flera entiteter.

Några exempel:

| Mening                                              | Intention         | Entiteter                                   |
| --------------------------------------------------- | ----------------- | ------------------------------------------ |
| "Spela det senaste albumet av Taylor Swift"         | *spela musik*     | *det senaste albumet av Taylor Swift*      |
| "Ställ in en timer på 3 minuter"                    | *ställ in timer*  | *3 minuter*                                |
| "Avbryt min timer"                                  | *avbryt timer*    | Ingen                                      |
| "Beställ 3 stora pizzor med ananas och en caesarsallad" | *beställ mat*     | *3 stora pizzor med ananas*, *caesarsallad* |

✅ Med de meningar du tänkte på tidigare, vad skulle vara intentionen och eventuella entiteter i den meningen?

För att träna LUIS börjar du med att ställa in entiteter. Dessa kan vara en fast lista med termer eller läras från texten. Till exempel kan du tillhandahålla en fast lista med mat från din meny, med variationer (eller synonymer) av varje ord, som *aubergine* och *äggplanta* som variationer av *aubergine*. LUIS har också förbyggda entiteter som kan användas, som siffror och platser.

För att ställa in en timer kan du ha en entitet som använder de förbyggda siffertalen för tiden och en annan för enheterna, som minuter och sekunder. Varje enhet skulle ha flera variationer för att täcka singular- och pluralformer - som minut och minuter.

När entiteterna är definierade skapar du intentioner. Dessa lärs av modellen baserat på exempelmeningar som du tillhandahåller (kända som yttranden). Till exempel, för en intention *ställ in timer*, kan du tillhandahålla följande meningar:

* `ställ in en timer på 1 sekund`
* `ställ in en timer för 1 minut och 12 sekunder`
* `ställ in en timer för 3 minuter`
* `ställ in en timer på 9 minuter och 30 sekunder`

Du anger sedan för LUIS vilka delar av dessa meningar som motsvarar entiteter:

![Meningen "ställ in en timer för 1 minut och 12 sekunder" uppdelad i entiteter](../../../../../translated_images/sv/sentence-as-intent-entities.301401696f992259.webp)

Meningen `ställ in en timer för 1 minut och 12 sekunder` har intentionen `ställ in timer`. Den har också 2 entiteter med 2 värden vardera:

|            | tid  | enhet   |
| ---------- | ---- | ------- |
| 1 minut    | 1    | minut   |
| 12 sekunder| 12   | sekund  |

För att träna en bra modell behöver du en rad olika exempelmeningar för att täcka de många olika sätten någon kan be om samma sak.

> 💁 Som med alla AI-modeller, ju mer data och ju mer exakt data du använder för att träna, desto bättre blir modellen.

✅ Tänk på de olika sätten du kan be om samma sak och förvänta dig att en människa förstår.

### Uppgift - lägg till entiteter i modellerna för språkförståelse

För timern behöver du lägga till 2 entiteter - en för tidsenheten (minuter eller sekunder) och en för antalet minuter eller sekunder.

Du kan hitta instruktioner för att använda LUIS-portalen i [Quickstart: Build your app in LUIS portal documentation on Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/luis/luis-get-started-create-app?WT.mc_id=academic-17441-jabenn).

1. Från LUIS-portalen, välj fliken *Entities* och lägg till den förbyggda entiteten *number* genom att välja knappen **Add prebuilt entity** och sedan välja *number* från listan.

1. Skapa en ny entitet för tidsenheten med knappen **Create**. Namnge entiteten `time unit` och ställ in typen på *List*. Lägg till värden för `minute` och `second` i listan *Normalized values* och lägg till singular- och pluralformer i listan *synonyms*. Tryck på `return` efter att ha lagt till varje synonym för att lägga till den i listan.

    | Normaliserat värde | Synonymer        |
    | ------------------ | ---------------- |
    | minute             | minut, minuter   |
    | second             | sekund, sekunder |

### Uppgift - lägg till intentioner i modellerna för språkförståelse

1. Från fliken *Intents*, välj knappen **Create** för att skapa en ny intention. Namnge denna intention `set timer`.

1. I exemplen, ange olika sätt att ställa in en timer med både minuter, sekunder och kombinationer av minuter och sekunder. Exempel kan vara:

    * `ställ in en timer på 1 sekund`
    * `ställ in en timer på 4 minuter`
    * `ställ in en timer på fyra minuter och sex sekunder`
    * `ställ in en timer på 9 minuter och 30 sekunder`
    * `ställ in en timer för 1 minut och 12 sekunder`
    * `ställ in en timer för 3 minuter`
    * `ställ in en timer för 3 minuter och 1 sekund`
    * `ställ in en timer för tre minuter och en sekund`
    * `ställ in en timer för 1 minut och 1 sekund`
    * `ställ in en timer för 30 sekunder`
    * `ställ in en timer för 1 sekund`

    Variera mellan siffror som ord och numeriska värden så att modellen lär sig hantera båda.

1. När du anger varje exempel kommer LUIS att börja upptäcka entiteter och understryka och märka de den hittar.

    ![Exemplen med siffror och tidsenheter understrukna av LUIS](../../../../../translated_images/sv/luis-intent-examples.25716580b2d2723c.webp)

### Uppgift - träna och testa modellen

1. När entiteter och intentioner är konfigurerade kan du träna modellen med knappen **Train** i toppmenyn. Välj denna knapp, och modellen bör tränas på några sekunder. Knappen kommer att vara gråtonad under träningen och aktiveras igen när den är klar.

1. Välj knappen **Test** i toppmenyn för att testa modellen för språkförståelse. Ange text som `ställ in en timer för 5 minuter och 4 sekunder` och tryck på return. Meningen kommer att visas i en ruta under textfältet du skrev i, och under det kommer den *top intent*, eller den intention som upptäcktes med högst sannolikhet. Detta bör vara `set timer`. Intentionens namn kommer att följas av sannolikheten att den upptäckta intentionen var korrekt.

1. Välj alternativet **Inspect** för att se en uppdelning av resultaten. Du kommer att se den högst rankade intentionen med dess procentuella sannolikhet, tillsammans med listor över de upptäckta entiteterna.

1. Stäng *Test*-panelen när du är klar med testningen.

### Uppgift - publicera modellen

För att använda denna modell från kod behöver du publicera den. När du publicerar från LUIS kan du publicera till antingen en staging-miljö för testning eller en produktionsmiljö för en fullständig release. I denna lektion räcker det med en staging-miljö.

1. Från LUIS-portalen, välj knappen **Publish** i toppmenyn.

1. Se till att *Staging slot* är vald och välj sedan **Done**. Du kommer att se en notifikation när appen är publicerad.

1. Du kan testa detta med curl. För att bygga curl-kommandot behöver du tre värden - endpoint, applikations-ID (App ID) och en API-nyckel. Dessa kan nås från fliken **MANAGE** som kan väljas från toppmenyn.

    1. Från avsnittet *Settings*, kopiera App ID.
1. Från avsnittet *Azure Resources*, välj *Authoring Resource* och kopiera *Primary Key* och *Endpoint URL*.

1. Kör följande curl-kommando i din kommandotolk eller terminal:

    ```sh
    curl "<endpoint url>/luis/prediction/v3.0/apps/<app id>/slots/staging/predict" \
          --request GET \
          --get \
          --data "subscription-key=<primary key>" \
          --data "verbose=false" \
          --data "show-all-intents=true" \
          --data-urlencode "query=<sentence>"
    ```

    Ersätt `<endpoint url>` med Endpoint URL från avsnittet *Azure Resources*.

    Ersätt `<app id>` med App ID från avsnittet *Settings*.

    Ersätt `<primary key>` med Primary Key från avsnittet *Azure Resources*.

    Ersätt `<sentence>` med den mening du vill testa med.

1. Resultatet av detta anrop kommer att vara ett JSON-dokument som beskriver frågan, den främsta intentionen och en lista över entiteter uppdelade efter typ.

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

    JSON-dokumentet ovan kom från en fråga med `set a timer for 45 minutes and 12 seconds`:

    * `set timer` var den främsta intentionen med en sannolikhet på 97%.
    * Två *number*-entiteter identifierades, `45` och `12`.
    * Två *time-unit*-entiteter identifierades, `minute` och `second`.

## Använd språkförståelsemodellen

När LUIS-modellen har publicerats kan den anropas från kod. I tidigare lektioner har du använt en IoT Hub för att hantera kommunikationen med molntjänster, skicka telemetri och lyssna efter kommandon. Detta är mycket asynkront - när telemetri skickas väntar inte din kod på ett svar, och om molntjänsten är nere skulle du inte veta det.

För en smart timer vill vi ha ett omedelbart svar, så att vi kan informera användaren om att en timer har ställts in eller varna dem om att molntjänsterna inte är tillgängliga. För att göra detta kommer vår IoT-enhet att anropa en webbtjänst direkt istället för att förlita sig på en IoT Hub.

Istället för att anropa LUIS direkt från IoT-enheten kan du använda serverlös kod med en annan typ av trigger - en HTTP-trigger. Detta gör att din funktion kan lyssna efter REST-anrop och svara på dem. Funktionen kommer att vara en REST-endpoint som din enhet kan anropa.

> 💁 Även om du kan anropa LUIS direkt från din IoT-enhet är det bättre att använda något som serverlös kod. På så sätt, när du vill ändra LUIS-appen som du anropar, till exempel när du tränar en bättre modell eller en modell på ett annat språk, behöver du bara uppdatera din molnkod och inte distribuera om kod till potentiellt tusentals eller miljontals IoT-enheter.

### Uppgift - skapa en serverlös funktionsapp

1. Skapa en Azure Functions-app som heter `smart-timer-trigger` och öppna den i VS Code.

1. Lägg till en HTTP-trigger i denna app som heter `speech-trigger` med följande kommando från terminalen i VS Code:

    ```sh
    func new --name text-to-timer --template "HTTP trigger"
    ```

    Detta kommer att skapa en HTTP-trigger som heter `text-to-timer`.

1. Testa HTTP-triggern genom att köra funktionsappen. När den körs kommer du att se endpointen listad i utdata:

    ```output
    Functions:
    
            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    ```

    Testa detta genom att ladda [http://localhost:7071/api/text-to-timer](http://localhost:7071/api/text-to-timer) i din webbläsare.

    ```output
    This HTTP triggered function executed successfully. Pass a name in the query string or in the request body for a personalized response.
    ```

### Uppgift - använd språkförståelsemodellen

1. SDK för LUIS är tillgängligt via ett Pip-paket. Lägg till följande rad i filen `requirements.txt` för att lägga till beroendet för detta paket:

    ```sh
    azure-cognitiveservices-language-luis
    ```

1. Se till att terminalen i VS Code har den virtuella miljön aktiverad och kör följande kommando för att installera Pip-paketen:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 Om du får fel kan du behöva uppgradera pip med följande kommando:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Lägg till nya poster i filen `local.settings.json` för din LUIS API Key, Endpoint URL och App ID från **MANAGE**-fliken i LUIS-portalen:

    ```JSON
    "LUIS_KEY": "<primary key>",
    "LUIS_ENDPOINT_URL": "<endpoint url>",
    "LUIS_APP_ID": "<app id>"
    ```

    Ersätt `<endpoint url>` med Endpoint URL från avsnittet *Azure Resources* i **MANAGE**-fliken. Detta kommer att vara `https://<location>.api.cognitive.microsoft.com/`.

    Ersätt `<app id>` med App ID från avsnittet *Settings* i **MANAGE**-fliken.

    Ersätt `<primary key>` med Primary Key från avsnittet *Azure Resources* i **MANAGE**-fliken.

1. Lägg till följande imports i filen `__init__.py`:

    ```python
    import json
    import os
    from azure.cognitiveservices.language.luis.runtime import LUISRuntimeClient
    from msrest.authentication import CognitiveServicesCredentials
    ```

    Detta importerar några systembibliotek samt biblioteken för att interagera med LUIS.

1. Ta bort innehållet i metoden `main` och lägg till följande kod:

    ```python
    luis_key = os.environ['LUIS_KEY']
    endpoint_url = os.environ['LUIS_ENDPOINT_URL']
    app_id = os.environ['LUIS_APP_ID']
    
    credentials = CognitiveServicesCredentials(luis_key)
    client = LUISRuntimeClient(endpoint=endpoint_url, credentials=credentials)
    ```

    Detta laddar värdena du lade till i filen `local.settings.json` för din LUIS-app, skapar ett credentials-objekt med din API-nyckel och skapar sedan ett LUIS-klientobjekt för att interagera med din LUIS-app.

1. Denna HTTP-trigger kommer att anropas med texten som ska förstås som JSON, med texten i en egenskap som heter `text`. Följande kod extraherar värdet från kroppen av HTTP-anropet och loggar det till konsolen. Lägg till denna kod i funktionen `main`:

    ```python
    req_body = req.get_json()
    text = req_body['text']
    logging.info(f'Request - {text}')
    ```

1. Förutsägelser begärs från LUIS genom att skicka en förutsägelseförfrågan - ett JSON-dokument som innehåller texten att förutsäga. Skapa detta med följande kod:

    ```python
    prediction_request = { 'query' : text }
    ```

1. Denna förfrågan kan sedan skickas till LUIS, med hjälp av staging-slottet som din app publicerades till:

    ```python
    prediction_response = client.prediction.get_slot_prediction(app_id, 'Staging', prediction_request)
    ```

1. Förutsägelsesvaret innehåller den främsta intentionen - den intention med högst förutsägelsesscore, tillsammans med entiteter. Om den främsta intentionen är `set timer`, kan entiteterna läsas för att få den tid som behövs för timern:

    ```python
    if prediction_response.prediction.top_intent == 'set timer':
        numbers = prediction_response.prediction.entities['number']
        time_units = prediction_response.prediction.entities['time unit']
        total_seconds = 0
    ```

    `number`-entiteterna kommer att vara en array av siffror. Till exempel, om du sa *"Set a four minute 17 second timer."*, kommer `number`-arrayen att innehålla 2 heltal - 4 och 17.

    `time unit`-entiteterna kommer att vara en array av arrays av strängar, med varje tidsenhet som en array av strängar inuti arrayen. Till exempel, om du sa *"Set a four minute 17 second timer."*, kommer `time unit`-arrayen att innehålla 2 arrays med enskilda värden - `['minute']` och `['second']`.

    JSON-versionen av dessa entiteter för *"Set a four minute 17 second timer."* är:

    ```json
    {
        "number": [4, 17],
        "time unit": [
            ["minute"],
            ["second"]
        ]
    }
    ```

    Denna kod definierar också en räknare för den totala tiden för timern i sekunder. Denna kommer att fyllas med värden från entiteterna.

1. Entiteterna är inte länkade, men vi kan göra vissa antaganden om dem. De kommer att vara i den ordning de talades, så positionen i arrayen kan användas för att avgöra vilket nummer som matchar vilken tidsenhet. Till exempel:

    * *"Set a 30 second timer"* - detta kommer att ha ett nummer, `30`, och en tidsenhet, `second`, så det enda numret kommer att matcha den enda tidsenheten.
    * *"Set a 2 minute and 30 second timer"* - detta kommer att ha två nummer, `2` och `30`, och två tidsenheter, `minute` och `second`, så det första numret kommer att vara för den första tidsenheten (2 minuter) och det andra numret för den andra tidsenheten (30 sekunder).

    Följande kod hämtar antalet objekt i `number`-entiteterna och använder detta för att extrahera det första objektet från varje array, sedan det andra och så vidare. Lägg till detta inuti `if`-blocket.

    ```python
    for i in range(0, len(numbers)):
        number = numbers[i]
        time_unit = time_units[i][0]
    ```

    För *"Set a four minute 17 second timer."* kommer detta att loopa två gånger och ge följande värden:

    | loop count | `number` | `time_unit` |
    | ---------: | -------: | ----------- |
    | 0          | 4        | minute      |
    | 1          | 17       | second      |

1. Inuti denna loop, använd numret och tidsenheten för att beräkna den totala tiden för timern, och lägg till 60 sekunder för varje minut och antalet sekunder för eventuella sekunder.

    ```python
    if time_unit == 'minute':
        total_seconds += number * 60
    else:
        total_seconds += number
    ```

1. Utanför denna loop genom entiteterna, logga den totala tiden för timern:

    ```python
    logging.info(f'Timer required for {total_seconds} seconds')
    ```

1. Antalet sekunder behöver returneras från funktionen som ett HTTP-svar. I slutet av `if`-blocket, lägg till följande:

    ```python
    payload = {
        'seconds': total_seconds
    }
    return func.HttpResponse(json.dumps(payload), status_code=200)
    ```

    Denna kod skapar en payload som innehåller det totala antalet sekunder för timern, konverterar det till en JSON-sträng och returnerar det som ett HTTP-resultat med statuskoden 200, vilket betyder att anropet lyckades.

1. Slutligen, utanför `if`-blocket, hantera om intentionen inte kunde identifieras genom att returnera en felkod:

    ```python
    return func.HttpResponse(status_code=404)
    ```

    404 är statuskoden för *not found*.

1. Kör funktionsappen och testa den med curl.

    ```sh
    curl --request POST 'http://localhost:7071/api/text-to-timer' \
         --header 'Content-Type: application/json' \
         --include \
         --data '{"text":"<text>"}'
    ```

    Ersätt `<text>` med texten för din förfrågan, till exempel `set a 2 minutes 27 second timer`.

    Du kommer att se följande utdata från funktionsappen:

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

    Anropet till curl kommer att returnera följande:

    ```output
    HTTP/1.1 200 OK
    Date: Tue, 29 Jun 2021 01:14:11 GMT
    Content-Type: text/plain; charset=utf-8
    Server: Kestrel
    Transfer-Encoding: chunked
    
    {"seconds": 147}
    ```

    Antalet sekunder för timern finns i värdet `"seconds"`.

> 💁 Du kan hitta denna kod i [code/functions](../../../../../6-consumer/lessons/2-language-understanding/code/functions)-mappen.

### Uppgift - gör din funktion tillgänglig för din IoT-enhet

1. För att din IoT-enhet ska kunna anropa din REST-endpoint behöver den känna till URL:en. När du åtkomstade den tidigare använde du `localhost`, vilket är en genväg för att åtkomsta REST-endpoints på din lokala dator. För att ge din IoT-enhet åtkomst behöver du antingen publicera till molnet eller få din IP-adress för att åtkomsta den lokalt.

    > ⚠️ Om du använder en Wio Terminal är det enklare att köra funktionsappen lokalt, eftersom det kommer att finnas ett beroende av bibliotek som gör att du inte kan distribuera funktionsappen på samma sätt som du har gjort tidigare. Kör funktionsappen lokalt och åtkomsta den via din dators IP-adress. Om du vill distribuera till molnet kommer information att ges i en senare lektion om hur du gör detta.

    * Publicera funktionsappen - följ instruktionerna i tidigare lektioner för att publicera din funktionsapp till molnet. När den har publicerats kommer URL:en att vara `https://<APP_NAME>.azurewebsites.net/api/text-to-timer`, där `<APP_NAME>` kommer att vara namnet på din funktionsapp. Se till att också publicera dina lokala inställningar.

      När du arbetar med HTTP-triggers är de som standard säkrade med en funktionsapp-nyckel. För att få denna nyckel, kör följande kommando:

      ```sh
      az functionapp keys list --resource-group smart-timer \
                               --name <APP_NAME>                               
      ```

      Kopiera värdet för posten `default` från avsnittet `functionKeys`.

      ```output
      {
        "functionKeys": {
          "default": "sQO1LQaeK9N1qYD6SXeb/TctCmwQEkToLJU6Dw8TthNeUH8VA45hlA=="
        },
        "masterKey": "RSKOAIlyvvQEQt9dfpabJT018scaLpQu9p1poHIMCxx5LYrIQZyQ/g==",
        "systemKeys": {}
      }
      ```

      Denna nyckel måste läggas till som en query-parameter i URL:en, så den slutliga URL:en kommer att vara `https://<APP_NAME>.azurewebsites.net/api/text-to-timer?code=<FUNCTION_KEY>`, där `<APP_NAME>` kommer att vara namnet på din funktionsapp och `<FUNCTION_KEY>` kommer att vara din standard funktionsnyckel.

      > 💁 Du kan ändra typen av auktorisering för HTTP-triggern med inställningen `authlevel` i filen `function.json`. Du kan läsa mer om detta i [konfigurationsavsnittet i dokumentationen för Azure Functions HTTP-trigger på Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python#configuration).

    * Kör funktionsappen lokalt och åtkomsta den med IP-adressen - du kan få IP-adressen för din dator på ditt lokala nätverk och använda den för att bygga URL:en.

      Hitta din IP-adress:

      * På Windows 10, följ guiden [hitta din IP-adress](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn).
      * På macOS, följ guiden [hur du hittar din IP-adress på en Mac](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac).
      * På Linux, följ avsnittet om att hitta din privata IP-adress i guiden [hur du hittar din IP-adress i Linux](https://opensource.com/article/18/5/how-find-ip-address-linux).

      När du har din IP-adress kommer du att kunna åtkomsta funktionen på `http://`.

:7071/api/text-to-timer`, där `<IP_ADDRESS>` är din IP-adress, till exempel `http://192.168.1.10:7071/api/text-to-timer`.

      > 💁 Observera att detta använder port 7071, så efter IP-adressen behöver du lägga till `:7071`.

      > 💁 Detta fungerar endast om din IoT-enhet är på samma nätverk som din dator.

1. Testa endpointen genom att använda curl.

---

## 🚀 Utmaning

Det finns många sätt att begära samma sak, som att ställa in en timer. Fundera på olika sätt att göra detta och använd dem som exempel i din LUIS-app. Testa dessa för att se hur väl din modell klarar av flera sätt att begära en timer.

## Quiz efter föreläsningen

[Quiz efter föreläsningen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/44)

## Granskning & Självstudier

* Läs mer om LUIS och dess funktioner på [Language Understanding (LUIS) dokumentationssidan på Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/luis/?WT.mc_id=academic-17441-jabenn)
* Läs mer om språkförståelse på [sidan om naturlig språkförståelse på Wikipedia](https://wikipedia.org/wiki/Natural-language_understanding)
* Läs mer om HTTP-triggers i [Azure Functions HTTP trigger-dokumentationen på Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python)

## Uppgift

[Avbryt timern](assignment.md)

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiska översättningar kan innehålla fel eller inexaktheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.