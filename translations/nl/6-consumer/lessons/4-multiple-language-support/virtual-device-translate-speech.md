<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d620a470d9dd8614d99824832978360a",
  "translation_date": "2025-08-27T22:18:03+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/virtual-device-translate-speech.md",
  "language_code": "nl"
}
-->
# Vertaal spraak - Virtueel IoT-apparaat

In dit deel van de les schrijf je code om spraak te vertalen bij het omzetten naar tekst met behulp van de spraakservice, en vervolgens tekst te vertalen met de Translator-service voordat je een gesproken reactie genereert.

## Gebruik de spraakservice om spraak te vertalen

De spraakservice kan spraak niet alleen omzetten naar tekst in dezelfde taal, maar ook de uitvoer vertalen naar andere talen.

### Taak - gebruik de spraakservice om spraak te vertalen

1. Open het `smart-timer`-project in VS Code en zorg ervoor dat de virtuele omgeving is geladen in de terminal.

1. Voeg de volgende importverklaringen toe onder de bestaande imports:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    Dit importeert klassen die worden gebruikt om spraak te vertalen, en een `requests`-bibliotheek die later in deze les wordt gebruikt om een oproep te doen naar de Translator-service.

1. Je slimme timer zal 2 talen hebben ingesteld - de taal van de server die is gebruikt om LUIS te trainen (dezelfde taal wordt ook gebruikt om berichten te maken om tegen de gebruiker te spreken), en de taal die door de gebruiker wordt gesproken. Werk de variabele `language` bij naar de taal die door de gebruiker zal worden gesproken, en voeg een nieuwe variabele toe genaamd `server_language` voor de taal die is gebruikt om LUIS te trainen:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Vervang `<user language>` door de locatienaam van de taal waarin je zult spreken, bijvoorbeeld `fr-FR` voor Frans, of `zn-HK` voor Kantonees.

    Vervang `<server language>` door de locatienaam van de taal die is gebruikt om LUIS te trainen.

    Je kunt een lijst vinden van de ondersteunde talen en hun locatienamen in de [Documentatie over taal- en stemondersteuning op Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Als je geen meerdere talen spreekt, kun je een service zoals [Bing Translate](https://www.bing.com/translator) of [Google Translate](https://translate.google.com) gebruiken om te vertalen van je voorkeurstaal naar een taal naar keuze. Deze services kunnen vervolgens audio afspelen van de vertaalde tekst. Houd er rekening mee dat de spraakherkenner sommige audio-uitvoer van je apparaat negeert, dus je moet mogelijk een extra apparaat gebruiken om de vertaalde tekst af te spelen.
    >
    > Bijvoorbeeld, als je LUIS in het Engels traint, maar Frans wilt gebruiken als de gebruikers taal, kun je zinnen zoals "stel een timer in van 2 minuten en 27 seconden" van Engels naar Frans vertalen met Bing Translate, en vervolgens de knop **Luister naar vertaling** gebruiken om de vertaling in je microfoon te spreken.
    >
    > ![De luister naar vertaling-knop op Bing Translate](../../../../../translated_images/nl/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Vervang de declaraties `recognizer_config` en `recognizer` door het volgende:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    Dit maakt een vertaalconfiguratie om spraak te herkennen in de gebruikers taal, en vertalingen te maken in de gebruikers- en servertaal. Vervolgens gebruikt het deze configuratie om een vertaalherkenner te maken - een spraakherkenner die de uitvoer van de spraakherkenning kan vertalen naar meerdere talen.

    > 💁 De oorspronkelijke taal moet worden opgegeven in de `target_languages`, anders krijg je geen vertalingen.

1. Werk de functie `recognized` bij door de volledige inhoud van de functie te vervangen door het volgende:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    Deze code controleert of het herkende evenement werd geactiveerd omdat spraak werd vertaald (dit evenement kan op andere momenten worden geactiveerd, zoals wanneer de spraak wordt herkend maar niet vertaald). Als de spraak werd vertaald, vindt het de vertaling in het woordenboek `args.result.translations` die overeenkomt met de servertaal.

    Het woordenboek `args.result.translations` is gesleuteld op het taaldeel van de locatienaam, niet de volledige instelling. Bijvoorbeeld, als je een vertaling aanvraagt naar `fr-FR` voor Frans, bevat het woordenboek een item voor `fr`, niet `fr-FR`.

    De vertaalde tekst wordt vervolgens naar de IoT Hub gestuurd.

1. Voer deze code uit om de vertalingen te testen. Zorg ervoor dat je functie-app actief is en vraag een timer aan in de gebruikers taal, door die taal zelf te spreken of door een vertaalapp te gebruiken.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## Vertaal tekst met behulp van de Translator-service

De spraakservice ondersteunt geen vertaling van tekst terug naar spraak, in plaats daarvan kun je de Translator-service gebruiken om de tekst te vertalen. Deze service heeft een REST API die je kunt gebruiken om de tekst te vertalen.

### Taak - gebruik de Translator-resource om tekst te vertalen

1. Voeg de Translator API-sleutel toe onder de `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Vervang `<key>` door de API-sleutel voor je Translator-service resource.

1. Definieer boven de functie `say` een functie `translate_text` die tekst zal vertalen van de servertaal naar de gebruikers taal:

    ```python
    def translate_text(text):
    ```

1. Definieer binnen deze functie de URL en headers voor de REST API-oproep:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    De URL voor deze API is niet locatie specifiek, in plaats daarvan wordt de locatie doorgegeven als een header. De API-sleutel wordt direct gebruikt, dus in tegenstelling tot de spraakservice is het niet nodig om een toegangstoken te verkrijgen van de token-uitgever API.

1. Definieer hieronder de parameters en body voor de oproep:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    De `params` definieert de parameters die worden doorgegeven aan de API-oproep, waarbij de van- en naar-talen worden doorgegeven. Deze oproep zal tekst in de `from`-taal vertalen naar de `to`-taal.

    De `body` bevat de tekst die moet worden vertaald. Dit is een array, omdat meerdere tekstblokken in dezelfde oproep kunnen worden vertaald.

1. Voer de REST API-oproep uit en ontvang de respons:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    De respons die terugkomt is een JSON-array, met één item dat de vertalingen bevat. Dit item heeft een array voor vertalingen van alle items die in de body zijn doorgegeven.

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

1. Geef de `text`-eigenschap terug van de eerste vertaling van het eerste item in de array:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Werk de functie `say` bij om de tekst te vertalen voordat de SSML wordt gegenereerd:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    Deze code print ook de originele en vertaalde versies van de tekst naar de console.

1. Voer je code uit. Zorg ervoor dat je functie-app actief is en vraag een timer aan in de gebruikers taal, door die taal zelf te spreken of door een vertaalapp te gebruiken.

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

    > 💁 Vanwege de verschillende manieren om iets te zeggen in verschillende talen, kun je vertalingen krijgen die enigszins verschillen van de voorbeelden die je aan LUIS hebt gegeven. Als dit het geval is, voeg meer voorbeelden toe aan LUIS, train opnieuw en publiceer het model opnieuw.

> 💁 Je kunt deze code vinden in de [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device) map.

😀 Je meertalige timerprogramma was een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.