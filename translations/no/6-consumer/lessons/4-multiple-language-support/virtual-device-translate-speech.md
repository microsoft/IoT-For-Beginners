<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d620a470d9dd8614d99824832978360a",
  "translation_date": "2025-08-27T21:17:19+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/virtual-device-translate-speech.md",
  "language_code": "no"
}
-->
# Oversett tale - Virtuell IoT-enhet

I denne delen av leksjonen skal du skrive kode for å oversette tale når den konverteres til tekst ved hjelp av tale-tjenesten, deretter oversette tekst ved hjelp av Translator-tjenesten før du genererer et muntlig svar.

## Bruk tale-tjenesten til å oversette tale

Tale-tjenesten kan ta tale og ikke bare konvertere den til tekst på samme språk, men også oversette resultatet til andre språk.

### Oppgave - bruk tale-tjenesten til å oversette tale

1. Åpne prosjektet `smart-timer` i VS Code, og sørg for at det virtuelle miljøet er lastet inn i terminalen.

1. Legg til følgende import-setninger under de eksisterende importene:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    Dette importerer klasser som brukes til å oversette tale, og et `requests`-bibliotek som vil bli brukt til å gjøre et kall til Translator-tjenesten senere i denne leksjonen.

1. Din smarte timer vil ha 2 språk satt - språket til serveren som ble brukt til å trene LUIS (det samme språket brukes også til å bygge meldingene som skal snakkes til brukeren), og språket som snakkes av brukeren. Oppdater variabelen `language` til å være språket som vil bli snakket av brukeren, og legg til en ny variabel kalt `server_language` for språket som ble brukt til å trene LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Erstatt `<user language>` med lokalitetsnavnet for språket du vil snakke, for eksempel `fr-FR` for fransk, eller `zn-HK` for kantonesisk.

    Erstatt `<server language>` med lokalitetsnavnet for språket som ble brukt til å trene LUIS.

    Du finner en liste over de støttede språkene og deres lokalitetsnavn i [Language and voice support-dokumentasjonen på Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Hvis du ikke snakker flere språk, kan du bruke en tjeneste som [Bing Translate](https://www.bing.com/translator) eller [Google Translate](https://translate.google.com) for å oversette fra ditt foretrukne språk til et språk du velger. Disse tjenestene kan deretter spille av lyd av den oversatte teksten. Vær oppmerksom på at talegjenkjenneren vil ignorere noe lydutgang fra enheten din, så du må kanskje bruke en ekstra enhet for å spille av den oversatte teksten.
    >
    > For eksempel, hvis du trener LUIS på engelsk, men vil bruke fransk som brukerspråk, kan du oversette setninger som "set a 2 minute and 27 second timer" fra engelsk til fransk ved hjelp av Bing Translate, og deretter bruke knappen **Lytt til oversettelse** for å snakke oversettelsen inn i mikrofonen din.
    >
    > ![Knappen for å lytte til oversettelse på Bing Translate](../../../../../translated_images/no/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Erstatt deklarasjonene for `recognizer_config` og `recognizer` med følgende:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    Dette oppretter en oversettelseskonfigurasjon for å gjenkjenne tale på brukerspråket og lage oversettelser på bruker- og serverspråket. Deretter bruker den denne konfigurasjonen til å opprette en oversettelsesgjenkjenner - en talegjenkjenner som kan oversette resultatet av talegjenkjenningen til flere språk.

    > 💁 Det opprinnelige språket må spesifiseres i `target_languages`, ellers vil du ikke få noen oversettelser.

1. Oppdater funksjonen `recognized`, og erstatt hele innholdet i funksjonen med følgende:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    Denne koden sjekker om den gjenkjente hendelsen ble utløst fordi tale ble oversatt (denne hendelsen kan utløses på andre tidspunkter, for eksempel når talen er gjenkjent, men ikke oversatt). Hvis talen ble oversatt, finner den oversettelsen i ordboken `args.result.translations` som samsvarer med serverspråket.

    Ordboken `args.result.translations` er nøkkelsatt basert på språkdelen av lokalitetsinnstillingen, ikke hele innstillingen. For eksempel, hvis du ber om en oversettelse til `fr-FR` for fransk, vil ordboken inneholde en oppføring for `fr`, ikke `fr-FR`.

    Den oversatte teksten sendes deretter til IoT Hub.

1. Kjør denne koden for å teste oversettelsene. Sørg for at funksjonsappen din kjører, og be om en timer på brukerspråket, enten ved å snakke det språket selv, eller ved å bruke en oversettelsesapp.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## Oversett tekst ved hjelp av Translator-tjenesten

Tale-tjenesten støtter ikke oversettelse av tekst tilbake til tale, i stedet kan du bruke Translator-tjenesten til å oversette teksten. Denne tjenesten har et REST API du kan bruke til å oversette teksten.

### Oppgave - bruk Translator-ressursen til å oversette tekst

1. Legg til Translator API-nøkkelen under `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Erstatt `<key>` med API-nøkkelen for Translator-tjenesteressursen din.

1. Over funksjonen `say`, definer en funksjon `translate_text` som vil oversette tekst fra serverspråket til brukerspråket:

    ```python
    def translate_text(text):
    ```

1. Inne i denne funksjonen, definer URL-en og overskriftene for REST API-kallet:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL-en for dette API-et er ikke stedsavhengig, i stedet sendes stedet som en overskrift. API-nøkkelen brukes direkte, så i motsetning til tale-tjenesten er det ikke nødvendig å hente en tilgangstoken fra tokenutsteder-API-et.

1. Under dette definerer du parametrene og kroppen for kallet:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` definerer parameterne som skal sendes til API-kallet, og sender fra- og til-språkene. Dette kallet vil oversette tekst på `from`-språket til `to`-språket.

    `body` inneholder teksten som skal oversettes. Dette er en matrise, ettersom flere tekstblokker kan oversettes i samme kall.

1. Gjør kallet til REST API-et, og hent responsen:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Responsen som kommer tilbake er en JSON-matrise, med ett element som inneholder oversettelsene. Dette elementet har en matrise for oversettelser av alle elementene som ble sendt i kroppen.

    ```json
    [
        {
            "translations": [
                {
                    "text": "Chronométrant votre minuterie de 2 minutes 27 secondes.",
                    "to": "fr"
                }
            ]
        }
    ]
    ```

1. Returner `test`-egenskapen fra den første oversettelsen fra det første elementet i matrisen:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Oppdater funksjonen `say` for å oversette teksten som skal sies før SSML genereres:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    Denne koden skriver også ut den originale og oversatte versjonen av teksten til konsollen.

1. Kjør koden din. Sørg for at funksjonsappen din kjører, og be om en timer på brukerspråket, enten ved å snakke det språket selv, eller ved å bruke en oversettelsesapp.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 På grunn av de forskjellige måtene å si noe på ulike språk, kan du få oversettelser som er litt forskjellige fra eksemplene du ga LUIS. Hvis dette er tilfelle, legg til flere eksempler i LUIS, tren modellen på nytt og publiser den på nytt.

> 💁 Du finner denne koden i [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device)-mappen.

😀 Programmet ditt for flerspråklige timere var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.