<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6f4ba69d77f16c4a5110623a96a215c3",
  "translation_date": "2025-08-27T22:20:25+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/README.md",
  "language_code": "nl"
}
-->
# Begrijp taal

![Een schetsnotitie-overzicht van deze les](../../../../../translated_images/lesson-22.6148ea28500d9e00c396aaa2649935fb6641362c8f03d8e5e90a676977ab01dd.nl.jpg)

> Schetsnotitie door [Nitya Narasimhan](https://github.com/nitya). Klik op de afbeelding voor een grotere versie.

## Quiz voorafgaand aan de les

[Quiz voorafgaand aan de les](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/43)

## Introductie

In de vorige les heb je spraak omgezet naar tekst. Om dit te gebruiken voor het programmeren van een slimme timer, moet je code begrijpen wat er gezegd is. Je zou kunnen aannemen dat de gebruiker een vaste zin zegt, zoals "Zet een timer van 3 minuten", en die uitdrukking analyseren om te bepalen hoe lang de timer moet zijn. Maar dit is niet erg gebruiksvriendelijk. Als een gebruiker bijvoorbeeld zegt: "Zet een timer voor 3 minuten", begrijpen jij en ik wat er bedoeld wordt, maar je code niet, omdat het een vaste zin verwacht.

Hier komt taalbegrip om de hoek kijken, waarbij AI-modellen worden gebruikt om tekst te interpreteren en de benodigde details terug te geven. Bijvoorbeeld, zowel "Zet een timer van 3 minuten" als "Zet een timer voor 3 minuten" kunnen worden begrepen als een verzoek om een timer van 3 minuten.

In deze les leer je over taalbegripsmodellen, hoe je ze maakt, traint en vanuit je code gebruikt.

In deze les behandelen we:

* [Taalbegrip](../../../../../6-consumer/lessons/2-language-understanding)
* [Een taalbegripsmodel maken](../../../../../6-consumer/lessons/2-language-understanding)
* [Intenties en entiteiten](../../../../../6-consumer/lessons/2-language-understanding)
* [Het taalbegripsmodel gebruiken](../../../../../6-consumer/lessons/2-language-understanding)

## Taalbegrip

Mensen gebruiken al honderdduizenden jaren taal om te communiceren. We communiceren met woorden, geluiden of acties en begrijpen wat er wordt gezegd, zowel de betekenis van de woorden, geluiden of acties als de context ervan. We begrijpen oprechtheid en sarcasme, waardoor dezelfde woorden verschillende dingen kunnen betekenen, afhankelijk van de toon van onze stem.

✅ Denk na over enkele gesprekken die je recent hebt gevoerd. Hoeveel van het gesprek zou moeilijk te begrijpen zijn voor een computer omdat het context nodig heeft?

Taalbegrip, ook wel natuurlijk taalbegrip genoemd, is een onderdeel van een kunstmatige intelligentieveld genaamd natuurlijke taalverwerking (of NLP) en houdt zich bezig met leesbegrip, waarbij wordt geprobeerd de details van woorden of zinnen te begrijpen. Als je een spraakassistent zoals Alexa of Siri gebruikt, maak je gebruik van taalbegripsdiensten. Dit zijn de achter-de-schermen AI-diensten die "Alexa, speel het nieuwste album van Taylor Swift" omzetten in mijn dochter die door de woonkamer danst op haar favoriete nummers.

> 💁 Computers, ondanks alle vooruitgang, hebben nog een lange weg te gaan om tekst echt te begrijpen. Wanneer we het hebben over taalbegrip bij computers, bedoelen we niet iets dat in de buurt komt van menselijke communicatie. We bedoelen het extraheren van belangrijke details uit woorden.

Als mensen begrijpen we taal zonder er echt over na te denken. Als ik een andere persoon zou vragen: "Speel het nieuwste album van Taylor Swift", dan zouden ze instinctief weten wat ik bedoel. Voor een computer is dit moeilijker. Het zou de woorden moeten nemen, omgezet van spraak naar tekst, en de volgende informatie moeten afleiden:

* Er moet muziek worden afgespeeld
* De muziek is van de artiest Taylor Swift
* Het gaat om een heel album met meerdere nummers in volgorde
* Taylor Swift heeft veel albums, dus ze moeten chronologisch worden gesorteerd en het meest recent gepubliceerde album is vereist

✅ Denk aan andere zinnen die je hebt uitgesproken bij het doen van verzoeken, zoals het bestellen van koffie of het vragen aan een familielid om iets aan te geven. Probeer ze op te splitsen in de informatie die een computer zou moeten extraheren om de zin te begrijpen.

Taalbegripsmodellen zijn AI-modellen die zijn getraind om bepaalde details uit taal te halen en vervolgens worden getraind voor specifieke taken met behulp van transfer learning, op dezelfde manier waarop je een Custom Vision-model hebt getraind met een kleine set afbeeldingen. Je kunt een model nemen en het trainen met de tekst die je wilt begrijpen.

## Een taalbegripsmodel maken

![Het LUIS-logo](../../../../../translated_images/luis-logo.5cb4f3e88c020ee6df4f614e8831f4a4b6809a7247bf52085fb48d629ef9be52.nl.png)

Je kunt taalbegripsmodellen maken met LUIS, een taalbegripsdienst van Microsoft die deel uitmaakt van Cognitive Services.

### Taak - een auteuringsresource maken

Om LUIS te gebruiken, moet je een auteuringsresource maken.

1. Gebruik de volgende opdracht om een auteuringsresource te maken in je `smart-timer` resourcegroep:

    ```python
    az cognitiveservices account create --name smart-timer-luis-authoring \
                                        --resource-group smart-timer \
                                        --kind LUIS.Authoring \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Vervang `<location>` door de locatie die je hebt gebruikt bij het maken van de resourcegroep.

    > ⚠️ LUIS is niet beschikbaar in alle regio's, dus als je de volgende foutmelding krijgt:
    >
    > ```output
    > InvalidApiSetId: The account type 'LUIS.Authoring' is either invalid or unavailable in given region.
    > ```
    >
    > kies dan een andere regio.

    Hiermee maak je een gratis LUIS-auteuringsresource.

### Taak - een taalbegripsapp maken

1. Open de LUIS-portal op [luis.ai](https://luis.ai?WT.mc_id=academic-17441-jabenn) in je browser en meld je aan met hetzelfde account dat je hebt gebruikt voor Azure.

1. Volg de instructies in het dialoogvenster om je Azure-abonnement te selecteren en selecteer vervolgens de `smart-timer-luis-authoring` resource die je zojuist hebt gemaakt.

1. Selecteer in de lijst *Conversation apps* de knop **New app** om een nieuwe applicatie te maken. Geef de nieuwe app de naam `smart-timer` en stel de *Culture* in op je taal.

    > 💁 Er is een veld voor een voorspellingsresource. Je kunt een tweede resource maken alleen voor voorspellingen, maar de gratis auteuringsresource biedt 1.000 voorspellingen per maand, wat voldoende zou moeten zijn voor ontwikkeling, dus je kunt dit veld leeg laten.

1. Lees de handleiding die verschijnt zodra je de app maakt om inzicht te krijgen in de stappen die je moet nemen om het taalbegripsmodel te trainen. Sluit deze handleiding wanneer je klaar bent.

## Intenties en entiteiten

Taalbegrip is gebaseerd op *intenties* en *entiteiten*. Intenties zijn wat de bedoeling van de woorden is, bijvoorbeeld muziek afspelen, een timer instellen of eten bestellen. Entiteiten zijn waar de intentie naar verwijst, zoals het album, de duur van de timer of het type eten. Elke zin die het model interpreteert, moet ten minste één intentie hebben en optioneel een of meer entiteiten.

Enkele voorbeelden:

| Zin                                                | Intentie         | Entiteiten                                   |
| -------------------------------------------------- | ---------------- | ------------------------------------------- |
| "Speel het nieuwste album van Taylor Swift"       | *muziek afspelen*| *het nieuwste album van Taylor Swift*       |
| "Zet een timer van 3 minuten"                     | *timer instellen*| *3 minuten*                                 |
| "Annuleer mijn timer"                             | *timer annuleren*| Geen                                        |
| "Bestel 3 grote pizza's met ananas en een caesarsalade" | *eten bestellen* | *3 grote pizza's met ananas*, *caesarsalade*|

✅ Met de zinnen waar je eerder aan dacht, wat zou de intentie en eventuele entiteiten in die zin zijn?

Om LUIS te trainen, stel je eerst de entiteiten in. Deze kunnen een vaste lijst van termen zijn of geleerd worden uit de tekst. Bijvoorbeeld, je kunt een vaste lijst van eten op je menu geven, met variaties (of synoniemen) van elk woord, zoals *aubergine* en *eggplant* als variaties van *aubergine*. LUIS heeft ook vooraf gebouwde entiteiten die kunnen worden gebruikt, zoals nummers en locaties.

Voor het instellen van een timer kun je één entiteit gebruiken met de vooraf gebouwde nummerentiteiten voor de tijd en een andere voor de eenheden, zoals minuten en seconden. Elke eenheid zou meerdere variaties hebben om de enkelvoudige en meervoudige vormen te dekken - zoals minuut en minuten.

Zodra de entiteiten zijn gedefinieerd, maak je intenties. Deze worden geleerd door het model op basis van voorbeeldzinnen die je opgeeft (bekend als uitingen). Bijvoorbeeld, voor een *timer instellen* intentie kun je de volgende zinnen opgeven:

* `zet een timer van 1 seconde`
* `zet een timer voor 1 minuut en 12 seconden`
* `zet een timer voor 3 minuten`
* `zet een timer van 9 minuten en 30 seconden`

Je geeft vervolgens aan welke delen van deze zinnen overeenkomen met de entiteiten:

![De zin "zet een timer voor 1 minuut en 12 seconden" opgesplitst in entiteiten](../../../../../translated_images/sentence-as-intent-entities.301401696f992259.nl.png)

De zin `zet een timer voor 1 minuut en 12 seconden` heeft de intentie `timer instellen`. Het heeft ook 2 entiteiten met elk 2 waarden:

|            | tijd | eenheid |
| ---------- | ----:| ------- |
| 1 minuut   | 1    | minuut  |
| 12 seconden| 12   | seconde |

Om een goed model te trainen, heb je een reeks verschillende voorbeeldzinnen nodig om de vele manieren te dekken waarop iemand hetzelfde kan vragen.

> 💁 Zoals bij elk AI-model geldt: hoe meer en hoe nauwkeuriger de gegevens die je gebruikt om te trainen, hoe beter het model.

✅ Denk na over de verschillende manieren waarop je hetzelfde zou kunnen vragen en verwachten dat een mens het begrijpt.

### Taak - entiteiten toevoegen aan het taalbegripsmodel

Voor de timer moet je 2 entiteiten toevoegen: één voor de tijdseenheid (minuten of seconden) en één voor het aantal minuten of seconden.

Je kunt instructies vinden voor het gebruik van de LUIS-portal in de [Quickstart: Build your app in LUIS portal documentatie op Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/luis/luis-get-started-create-app?WT.mc_id=academic-17441-jabenn).

1. Selecteer in de LUIS-portal het tabblad *Entities* en voeg de vooraf gebouwde entiteit *number* toe door op de knop **Add prebuilt entity** te klikken en vervolgens *number* uit de lijst te selecteren.

1. Maak een nieuwe entiteit voor de tijdseenheid met de knop **Create**. Geef de entiteit de naam `time unit` en stel het type in op *List*. Voeg waarden toe voor `minute` en `second` aan de lijst *Normalized values* en voeg de enkelvoudige en meervoudige vormen toe aan de lijst *synonyms*. Druk op `return` na het toevoegen van elk synoniem om het aan de lijst toe te voegen.

    | Genormaliseerde waarde | Synoniemen        |
    | ----------------------- | ----------------- |
    | minuut                 | minuut, minuten   |
    | seconde                | seconde, seconden |

### Taak - intenties toevoegen aan het taalbegripsmodel

1. Selecteer op het tabblad *Intents* de knop **Create** om een nieuwe intentie te maken. Geef deze intentie de naam `set timer`.

1. Voer in de voorbeelden verschillende manieren in om een timer in te stellen met zowel minuten, seconden als een combinatie van minuten en seconden. Voorbeelden kunnen zijn:

    * `zet een timer van 1 seconde`
    * `zet een timer van 4 minuten`
    * `zet een timer van vier minuten en zes seconden`
    * `zet een timer van 9 minuten en 30 seconden`
    * `zet een timer voor 1 minuut en 12 seconden`
    * `zet een timer voor 3 minuten`
    * `zet een timer voor 3 minuten en 1 seconde`
    * `zet een timer voor drie minuten en één seconde`
    * `zet een timer voor 1 minuut en 1 seconde`
    * `zet een timer voor 30 seconden`
    * `zet een timer voor 1 seconde`

    Wissel af tussen getallen als woorden en cijfers, zodat het model leert om met beide om te gaan.

1. Terwijl je elk voorbeeld invoert, zal LUIS beginnen met het detecteren van entiteiten en deze onderstrepen en labelen.

    ![De voorbeelden met de onderstreepte getallen en tijdseenheden door LUIS](../../../../../translated_images/luis-intent-examples.25716580b2d2723cf1bafdf277d015c7f046d8cfa20f27bddf3a0873ec45fab7.nl.png)

### Taak - het model trainen en testen

1. Zodra de entiteiten en intenties zijn geconfigureerd, kun je het model trainen met de knop **Train** in het bovenste menu. Selecteer deze knop en het model zou binnen enkele seconden moeten trainen. De knop wordt grijs tijdens het trainen en wordt opnieuw ingeschakeld zodra het klaar is.

1. Selecteer de knop **Test** in het bovenste menu om het taalbegripsmodel te testen. Voer tekst in zoals `zet een timer voor 5 minuten en 4 seconden` en druk op return. De zin verschijnt in een vak onder het tekstvak waarin je het hebt getypt, en daaronder wordt de *top intent* weergegeven, of de intentie die met de hoogste waarschijnlijkheid is gedetecteerd. Dit zou `set timer` moeten zijn. De intentienaam wordt gevolgd door de waarschijnlijkheid dat de gedetecteerde intentie correct is.

1. Selecteer de optie **Inspect** om een uitsplitsing van de resultaten te zien. Je ziet de intentie met de hoogste score en de bijbehorende waarschijnlijkheid, samen met lijsten van de gedetecteerde entiteiten.

1. Sluit het *Test*-venster wanneer je klaar bent met testen.

### Taak - het model publiceren

Om dit model vanuit code te gebruiken, moet je het publiceren. Bij het publiceren vanuit LUIS kun je publiceren naar een stagingomgeving voor testen of een productieomgeving voor een volledige release. Voor deze les is een stagingomgeving voldoende.

1. Selecteer in de LUIS-portal de knop **Publish** in het bovenste menu.

1. Zorg ervoor dat *Staging slot* is geselecteerd en selecteer vervolgens **Done**. Je ziet een melding wanneer de app is gepubliceerd.

1. Je kunt dit testen met curl. Om het curl-commando samen te stellen, heb je drie waarden nodig: de endpoint, de applicatie-ID (App ID) en een API-sleutel. Deze zijn toegankelijk vanuit het tabblad **MANAGE**, dat je kunt selecteren in het bovenste menu.

    1. Kopieer vanuit de sectie *Settings* de App ID.
1. Ga naar de sectie *Azure Resources*, selecteer *Authoring Resource*, en kopieer de *Primary Key* en *Endpoint URL*.

1. Voer het volgende curl-commando uit in je opdrachtprompt of terminal:

    ```sh
    curl "<endpoint url>/luis/prediction/v3.0/apps/<app id>/slots/staging/predict" \
          --request GET \
          --get \
          --data "subscription-key=<primary key>" \
          --data "verbose=false" \
          --data "show-all-intents=true" \
          --data-urlencode "query=<sentence>"
    ```

    Vervang `<endpoint url>` door de Endpoint URL uit de sectie *Azure Resources*.

    Vervang `<app id>` door de App ID uit de sectie *Settings*.

    Vervang `<primary key>` door de Primary Key uit de sectie *Azure Resources*.

    Vervang `<sentence>` door de zin waarmee je wilt testen.

1. De uitvoer van deze oproep zal een JSON-document zijn dat de query, de belangrijkste intentie en een lijst van entiteiten per type beschrijft.

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

    De bovenstaande JSON is afkomstig van een query met `set a timer for 45 minutes and 12 seconds`:

    * De intentie `set timer` was de belangrijkste intentie met een waarschijnlijkheid van 97%.
    * Twee *number*-entiteiten werden gedetecteerd: `45` en `12`.
    * Twee *time-unit*-entiteiten werden gedetecteerd: `minute` en `second`.

## Gebruik het taalbegripsmodel

Zodra het LUIS-model is gepubliceerd, kan het vanuit code worden aangeroepen. In eerdere lessen heb je een IoT Hub gebruikt om communicatie met cloudservices af te handelen, telemetrie te verzenden en te luisteren naar opdrachten. Dit is erg asynchroon - zodra telemetrie is verzonden, wacht je code niet op een antwoord, en als de cloudservice niet beschikbaar is, weet je dat niet.

Voor een slimme timer willen we direct een reactie, zodat we de gebruiker kunnen laten weten dat een timer is ingesteld, of hen kunnen waarschuwen dat de cloudservices niet beschikbaar zijn. Om dit te doen, zal ons IoT-apparaat direct een web-endpoint aanroepen in plaats van te vertrouwen op een IoT Hub.

In plaats van LUIS direct vanaf het IoT-apparaat aan te roepen, kun je serverloze code gebruiken met een ander type trigger - een HTTP-trigger. Hiermee kan je function app luisteren naar REST-verzoeken en erop reageren. Deze functie zal een REST-endpoint zijn dat je apparaat kan aanroepen.

> 💁 Hoewel je LUIS direct vanaf je IoT-apparaat kunt aanroepen, is het beter om iets zoals serverloze code te gebruiken. Op deze manier hoef je, wanneer je bijvoorbeeld een beter model traint of een model in een andere taal traint, alleen je cloudcode bij te werken en niet de code opnieuw te implementeren op mogelijk duizenden of miljoenen IoT-apparaten.

### Taak - maak een serverloze functies-app

1. Maak een Azure Functions-app genaamd `smart-timer-trigger` en open deze in VS Code.

1. Voeg een HTTP-trigger toe aan deze app genaamd `speech-trigger` met behulp van het volgende commando in de terminal van VS Code:

    ```sh
    func new --name text-to-timer --template "HTTP trigger"
    ```

    Dit zal een HTTP-trigger maken genaamd `text-to-timer`.

1. Test de HTTP-trigger door de functies-app uit te voeren. Wanneer deze draait, zie je het endpoint in de uitvoer:

    ```output
    Functions:
    
            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    ```

    Test dit door de URL [http://localhost:7071/api/text-to-timer](http://localhost:7071/api/text-to-timer) in je browser te laden.

    ```output
    This HTTP triggered function executed successfully. Pass a name in the query string or in the request body for a personalized response.
    ```

### Taak - gebruik het taalbegripsmodel

1. De SDK voor LUIS is beschikbaar via een Pip-pakket. Voeg de volgende regel toe aan het bestand `requirements.txt` om de afhankelijkheid van dit pakket toe te voegen:

    ```sh
    azure-cognitiveservices-language-luis
    ```

1. Zorg ervoor dat de terminal in VS Code de virtuele omgeving heeft geactiveerd en voer het volgende commando uit om de Pip-pakketten te installeren:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 Als je fouten krijgt, moet je mogelijk pip upgraden met het volgende commando:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Voeg nieuwe items toe aan het bestand `local.settings.json` voor je LUIS API Key, Endpoint URL en App ID uit het **MANAGE**-tabblad van de LUIS-portal:

    ```JSON
    "LUIS_KEY": "<primary key>",
    "LUIS_ENDPOINT_URL": "<endpoint url>",
    "LUIS_APP_ID": "<app id>"
    ```

    Vervang `<endpoint url>` door de Endpoint URL uit de sectie *Azure Resources* van het **MANAGE**-tabblad. Dit zal zijn `https://<location>.api.cognitive.microsoft.com/`.

    Vervang `<app id>` door de App ID uit de sectie *Settings* van het **MANAGE**-tabblad.

    Vervang `<primary key>` door de Primary Key uit de sectie *Azure Resources* van het **MANAGE**-tabblad.

1. Voeg de volgende imports toe aan het bestand `__init__.py`:

    ```python
    import json
    import os
    from azure.cognitiveservices.language.luis.runtime import LUISRuntimeClient
    from msrest.authentication import CognitiveServicesCredentials
    ```

    Dit importeert enkele systeembibliotheken en de bibliotheken om met LUIS te werken.

1. Verwijder de inhoud van de `main`-methode en voeg de volgende code toe:

    ```python
    luis_key = os.environ['LUIS_KEY']
    endpoint_url = os.environ['LUIS_ENDPOINT_URL']
    app_id = os.environ['LUIS_APP_ID']
    
    credentials = CognitiveServicesCredentials(luis_key)
    client = LUISRuntimeClient(endpoint=endpoint_url, credentials=credentials)
    ```

    Dit laadt de waarden die je hebt toegevoegd aan het bestand `local.settings.json` voor je LUIS-app, maakt een credentials-object met je API-sleutel en maakt vervolgens een LUIS-clientobject om met je LUIS-app te communiceren.

1. Deze HTTP-trigger wordt aangeroepen met de tekst die moet worden begrepen als JSON, met de tekst in een eigenschap genaamd `text`. De volgende code haalt de waarde uit de body van het HTTP-verzoek en logt deze naar de console. Voeg deze code toe aan de `main`-functie:

    ```python
    req_body = req.get_json()
    text = req_body['text']
    logging.info(f'Request - {text}')
    ```

1. Voorspellingen worden opgevraagd van LUIS door een voorspellingverzoek te verzenden - een JSON-document met de tekst om te voorspellen. Maak dit met de volgende code:

    ```python
    prediction_request = { 'query' : text }
    ```

1. Dit verzoek kan vervolgens naar LUIS worden verzonden, met behulp van de staging-slot waarop je app is gepubliceerd:

    ```python
    prediction_response = client.prediction.get_slot_prediction(app_id, 'Staging', prediction_request)
    ```

1. De voorspellingrespons bevat de belangrijkste intentie - de intentie met de hoogste voorspelling-score, samen met de entiteiten. Als de belangrijkste intentie `set timer` is, kunnen de entiteiten worden gelezen om de benodigde tijd voor de timer te krijgen:

    ```python
    if prediction_response.prediction.top_intent == 'set timer':
        numbers = prediction_response.prediction.entities['number']
        time_units = prediction_response.prediction.entities['time unit']
        total_seconds = 0
    ```

    De `number`-entiteiten zullen een array van getallen zijn. Bijvoorbeeld, als je zei *"Set a four minute 17 second timer."*, dan zal de `number`-array 2 gehele getallen bevatten - 4 en 17.

    De `time unit`-entiteiten zullen een array van arrays van strings zijn, met elke tijdseenheid als een array van strings binnen de array. Bijvoorbeeld, als je zei *"Set a four minute 17 second timer."*, dan zal de `time unit`-array 2 arrays bevatten met elk één waarde - `['minute']` en `['second']`.

    De JSON-versie van deze entiteiten voor *"Set a four minute 17 second timer."* is:

    ```json
    {
        "number": [4, 17],
        "time unit": [
            ["minute"],
            ["second"]
        ]
    }
    ```

    Deze code definieert ook een teller voor de totale tijd voor de timer in seconden. Deze zal worden gevuld met de waarden van de entiteiten.

1. De entiteiten zijn niet gekoppeld, maar we kunnen enkele aannames over hen maken. Ze zullen in de volgorde staan waarin ze zijn uitgesproken, dus de positie in de array kan worden gebruikt om te bepalen welk getal bij welke tijdseenheid hoort. Bijvoorbeeld:

    * *"Set a 30 second timer"* - dit zal één getal hebben, `30`, en één tijdseenheid, `second`, dus het enkele getal zal overeenkomen met de enkele tijdseenheid.
    * *"Set a 2 minute and 30 second timer"* - dit zal twee getallen hebben, `2` en `30`, en twee tijdseenheden, `minute` en `second`, dus het eerste getal zal voor de eerste tijdseenheid zijn (2 minuten), en het tweede getal voor de tweede tijdseenheid (30 seconden).

    De volgende code haalt het aantal items in de `number`-entiteiten op en gebruikt dat om het eerste item uit elke array te halen, vervolgens het tweede, enzovoort. Voeg dit toe binnen het `if`-blok.

    ```python
    for i in range(0, len(numbers)):
        number = numbers[i]
        time_unit = time_units[i][0]
    ```

    Voor *"Set a four minute 17 second timer."* zal dit twee keer doorlopen, met de volgende waarden:

    | loop count | `number` | `time_unit` |
    | ---------: | -------: | ----------- |
    | 0          | 4        | minute      |
    | 1          | 17       | second      |

1. Binnen deze lus, gebruik het getal en de tijdseenheid om de totale tijd voor de timer te berekenen, waarbij je 60 seconden toevoegt voor elke minuut en het aantal seconden voor eventuele seconden.

    ```python
    if time_unit == 'minute':
        total_seconds += number * 60
    else:
        total_seconds += number
    ```

1. Buiten deze lus door de entiteiten, log de totale tijd voor de timer:

    ```python
    logging.info(f'Timer required for {total_seconds} seconds')
    ```

1. Het aantal seconden moet worden geretourneerd vanuit de functie als een HTTP-respons. Voeg aan het einde van het `if`-blok het volgende toe:

    ```python
    payload = {
        'seconds': total_seconds
    }
    return func.HttpResponse(json.dumps(payload), status_code=200)
    ```

    Deze code maakt een payload met het totale aantal seconden voor de timer, converteert het naar een JSON-string en retourneert het als een HTTP-resultaat met een statuscode van 200, wat betekent dat de oproep succesvol was.

1. Tot slot, buiten het `if`-blok, handel af als de intentie niet werd herkend door een foutcode te retourneren:

    ```python
    return func.HttpResponse(status_code=404)
    ```

    404 is de statuscode voor *niet gevonden*.

1. Voer de functies-app uit en test deze met curl.

    ```sh
    curl --request POST 'http://localhost:7071/api/text-to-timer' \
         --header 'Content-Type: application/json' \
         --include \
         --data '{"text":"<text>"}'
    ```

    Vervang `<text>` door de tekst van je verzoek, bijvoorbeeld `set a 2 minutes 27 second timer`.

    Je zult de volgende uitvoer van de functies-app zien:

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

    De oproep naar curl zal het volgende retourneren:

    ```output
    HTTP/1.1 200 OK
    Date: Tue, 29 Jun 2021 01:14:11 GMT
    Content-Type: text/plain; charset=utf-8
    Server: Kestrel
    Transfer-Encoding: chunked
    
    {"seconds": 147}
    ```

    Het aantal seconden voor de timer staat in de waarde `"seconds"`.

> 💁 Je kunt deze code vinden in de map [code/functions](../../../../../6-consumer/lessons/2-language-understanding/code/functions).

### Taak - maak je functie beschikbaar voor je IoT-apparaat

1. Voor je IoT-apparaat om je REST-endpoint aan te roepen, moet het de URL weten. Toen je er eerder toegang toe kreeg, gebruikte je `localhost`, wat een snelkoppeling is om REST-endpoints op je lokale machine te benaderen. Om je IoT-apparaat toegang te geven, moet je ofwel naar de cloud publiceren, of je IP-adres gebruiken om lokaal toegang te krijgen.

    > ⚠️ Als je een Wio Terminal gebruikt, is het eenvoudiger om de functies-app lokaal uit te voeren, omdat er een afhankelijkheid is van bibliotheken die betekenen dat je de functies-app niet op dezelfde manier kunt implementeren als je eerder hebt gedaan. Voer de functies-app lokaal uit en krijg toegang via het IP-adres van je computer. Als je toch naar de cloud wilt implementeren, wordt in een latere les informatie gegeven over hoe je dit kunt doen.

    * Publiceer de functies-app - volg de instructies in eerdere lessen om je functies-app naar de cloud te publiceren. Zodra deze is gepubliceerd, zal de URL zijn `https://<APP_NAME>.azurewebsites.net/api/text-to-timer`, waarbij `<APP_NAME>` de naam van je functies-app is. Zorg ervoor dat je ook je lokale instellingen publiceert.

      Bij het werken met HTTP-triggers zijn deze standaard beveiligd met een functies-app-sleutel. Om deze sleutel te verkrijgen, voer je het volgende commando uit:

      ```sh
      az functionapp keys list --resource-group smart-timer \
                               --name <APP_NAME>                               
      ```

      Kopieer de waarde van de `default`-vermelding uit de sectie `functionKeys`.

      ```output
      {
        "functionKeys": {
          "default": "sQO1LQaeK9N1qYD6SXeb/TctCmwQEkToLJU6Dw8TthNeUH8VA45hlA=="
        },
        "masterKey": "RSKOAIlyvvQEQt9dfpabJT018scaLpQu9p1poHIMCxx5LYrIQZyQ/g==",
        "systemKeys": {}
      }
      ```

      Deze sleutel moet worden toegevoegd als een queryparameter aan de URL, zodat de uiteindelijke URL zal zijn `https://<APP_NAME>.azurewebsites.net/api/text-to-timer?code=<FUNCTION_KEY>`, waarbij `<APP_NAME>` de naam van je functies-app is en `<FUNCTION_KEY>` je standaard functiesleutel.

      > 💁 Je kunt het type autorisatie van de HTTP-trigger wijzigen met de instelling `authlevel` in het bestand `function.json`. Je kunt hier meer over lezen in de [configuratiesectie van de Azure Functions HTTP-triggerdocumentatie op Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python#configuration).

    * Voer de functies-app lokaal uit en krijg toegang via het IP-adres - je kunt het IP-adres van je computer op je lokale netwerk verkrijgen en dat gebruiken om de URL te bouwen.

      Vind je IP-adres:

      * Op Windows 10, volg de [gids om je IP-adres te vinden](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn).
      * Op macOS, volg de [gids om je IP-adres op een Mac te vinden](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac).
      * Op Linux, volg de sectie over het vinden van je privé-IP-adres in de [gids om je IP-adres in Linux te vinden](https://opensource.com/article/18/5/how-find-ip-address-linux).

      Zodra je je IP-adres hebt, kun je toegang krijgen tot de functie op `http://`.

:7071/api/text-to-timer`, waarbij `<IP_ADDRESS>` jouw IP-adres zal zijn, bijvoorbeeld `http://192.168.1.10:7071/api/text-to-timer`.

      > 💁 Let op dat dit poort 7071 gebruikt, dus na het IP-adres moet je `:7071` toevoegen.

      > 💁 Dit werkt alleen als jouw IoT-apparaat zich op hetzelfde netwerk bevindt als jouw computer.

1. Test de endpoint door deze te benaderen met curl.

---

## 🚀 Uitdaging

Er zijn veel manieren om hetzelfde te vragen, zoals het instellen van een timer. Bedenk verschillende manieren om dit te doen en gebruik ze als voorbeelden in jouw LUIS-app. Test deze uit om te zien hoe goed jouw model om kan gaan met meerdere manieren om een timer aan te vragen.

## Quiz na de les

[Quiz na de les](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/44)

## Review & Zelfstudie

* Lees meer over LUIS en zijn mogelijkheden op de [Language Understanding (LUIS) documentatiepagina op Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/luis/?WT.mc_id=academic-17441-jabenn)
* Lees meer over taalbegrip op de [pagina over natuurlijk taalbegrip op Wikipedia](https://wikipedia.org/wiki/Natural-language_understanding)
* Lees meer over HTTP-triggers in de [Azure Functions HTTP-trigger documentatie op Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python)

## Opdracht

[Annuleer de timer](assignment.md)

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.