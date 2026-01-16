<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "bbb5aa34221fe129dd3ce4d9ec33831a",
  "translation_date": "2025-08-27T21:16:12+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/pi-translate-speech.md",
  "language_code": "no"
}
-->
# Oversett tale - Raspberry Pi

I denne delen av leksjonen skal du skrive kode for å oversette tekst ved hjelp av oversettertjenesten.

## Konverter tekst til tale ved hjelp av oversettertjenesten

REST-API-et for taletjenesten støtter ikke direkte oversettelser, men du kan bruke oversettertjenesten til å oversette teksten som genereres av tale-til-tekst-tjenesten, samt teksten i det talte svaret. Denne tjenesten har et REST-API som du kan bruke til å oversette teksten.

### Oppgave - bruk oversetterressursen til å oversette tekst

1. Din smarte timer vil ha 2 språk satt - språket til serveren som ble brukt til å trene LUIS (det samme språket brukes også til å bygge meldingene som skal snakkes til brukeren), og språket som snakkes av brukeren. Oppdater variabelen `language` til å være språket som skal snakkes av brukeren, og legg til en ny variabel kalt `server_language` for språket som ble brukt til å trene LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Erstatt `<user language>` med lokalitetsnavnet for språket du skal snakke, for eksempel `fr-FR` for fransk, eller `zn-HK` for kantonesisk.

    Erstatt `<server language>` med lokalitetsnavnet for språket som ble brukt til å trene LUIS.

    Du finner en liste over støttede språk og deres lokalitetsnavn i [dokumentasjonen for språk- og stemmestøtte på Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Hvis du ikke snakker flere språk, kan du bruke en tjeneste som [Bing Translate](https://www.bing.com/translator) eller [Google Translate](https://translate.google.com) for å oversette fra ditt foretrukne språk til et annet språk. Disse tjenestene kan også spille av lyd av den oversatte teksten.
    >
    > For eksempel, hvis du trener LUIS på engelsk, men ønsker å bruke fransk som brukerspråk, kan du oversette setninger som "set a 2 minute and 27 second timer" fra engelsk til fransk ved hjelp av Bing Translate, og deretter bruke knappen **Lytt til oversettelse** for å snakke oversettelsen inn i mikrofonen din.
    >
    > ![Knappen for å lytte til oversettelse på Bing Translate](../../../../../translated_images/no/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Legg til API-nøkkelen for oversetteren under `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Erstatt `<key>` med API-nøkkelen for ressursen din for oversettertjenesten.

1. Over `say`-funksjonen, definer en funksjon `translate_text` som vil oversette tekst fra serverspråket til brukerspråket:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    Fra- og til-språkene sendes til denne funksjonen - appen din må konvertere fra brukerspråk til serverspråk når den gjenkjenner tale, og fra serverspråk til brukerspråk når den gir talte tilbakemeldinger.

1. Inne i denne funksjonen, definer URL-en og overskriftene for REST-API-kallet:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL-en for dette API-et er ikke stedsavhengig, i stedet sendes lokasjonen som en overskrift. API-nøkkelen brukes direkte, så i motsetning til taletjenesten er det ikke nødvendig å hente en tilgangstoken fra tokenutsteder-API-et.

1. Under dette definerer du parametrene og kroppen for kallet:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` definerer parameterne som skal sendes til API-kallet, og sender fra- og til-språkene. Dette kallet vil oversette tekst fra `from`-språket til `to`-språket.

    `body` inneholder teksten som skal oversettes. Dette er en liste, siden flere tekstblokker kan oversettes i samme kall.

1. Utfør REST-API-kallet og hent responsen:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Responsen som kommer tilbake er en JSON-liste, med ett element som inneholder oversettelsene. Dette elementet har en liste for oversettelser av alle elementene som ble sendt i kroppen.

    ```json
    [
        {
            "translations": [
                {
                    "text": "Set a 2 minute 27 second timer.",
                    "to": "en"
                }
            ]
        }
    ]
    ```

1. Returner `test`-egenskapen fra den første oversettelsen fra det første elementet i listen:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Oppdater `while True`-løkken for å oversette teksten fra kallet til `convert_speech_to_text` fra brukerspråket til serverspråket:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    Denne koden skriver også ut de originale og oversatte versjonene av teksten til konsollen.

1. Oppdater `say`-funksjonen for å oversette teksten som skal sies fra serverspråket til brukerspråket:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    Denne koden skriver også ut de originale og oversatte versjonene av teksten til konsollen.

1. Kjør koden din. Sørg for at funksjonsappen din kjører, og be om en timer på brukerspråket, enten ved å snakke det språket selv eller ved å bruke en oversettelsesapp.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py
    Connecting
    Connected
    Using voice fr-FR-DeniseNeural
    Original: Définir une minuterie de 2 minutes et 27 secondes.
    Translated: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 På grunn av de forskjellige måtene å si noe på ulike språk, kan du få oversettelser som er litt forskjellige fra eksemplene du ga LUIS. Hvis dette er tilfelle, legg til flere eksempler i LUIS, tren modellen på nytt og publiser den på nytt.

> 💁 Du finner denne koden i [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi)-mappen.

😀 Programmet ditt for flerspråklige timere var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiske oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.