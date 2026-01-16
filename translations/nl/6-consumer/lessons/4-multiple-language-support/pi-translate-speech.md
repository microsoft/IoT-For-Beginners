<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "bbb5aa34221fe129dd3ce4d9ec33831a",
  "translation_date": "2025-08-27T22:17:03+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/pi-translate-speech.md",
  "language_code": "nl"
}
-->
# Vertaal spraak - Raspberry Pi

In dit deel van de les schrijf je code om tekst te vertalen met behulp van de vertaalservice.

## Converteer tekst naar spraak met behulp van de vertaalservice

De REST API van de spraakservice ondersteunt geen directe vertalingen. In plaats daarvan kun je de Translator-service gebruiken om de tekst te vertalen die is gegenereerd door de spraak-naar-tekstservice, evenals de tekst van de gesproken reactie. Deze service heeft een REST API die je kunt gebruiken om tekst te vertalen.

### Taak - gebruik de vertaalresource om tekst te vertalen

1. Je slimme timer zal twee talen hebben ingesteld: de taal van de server die is gebruikt om LUIS te trainen (dezelfde taal wordt ook gebruikt om berichten te maken die aan de gebruiker worden gesproken) en de taal die door de gebruiker wordt gesproken. Werk de variabele `language` bij naar de taal die door de gebruiker zal worden gesproken, en voeg een nieuwe variabele toe genaamd `server_language` voor de taal die is gebruikt om LUIS te trainen:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Vervang `<user language>` door de locatienaam van de taal waarin je zult spreken, bijvoorbeeld `fr-FR` voor Frans, of `zn-HK` voor Kantonees.

    Vervang `<server language>` door de locatienaam van de taal die is gebruikt om LUIS te trainen.

    Je kunt een lijst vinden van de ondersteunde talen en hun locatienamen in de [Documentatie over taal- en stemondersteuning op Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Als je niet meerdere talen spreekt, kun je een service zoals [Bing Translate](https://www.bing.com/translator) of [Google Translate](https://translate.google.com) gebruiken om te vertalen van je voorkeurstaal naar een taal naar keuze. Deze services kunnen vervolgens audio afspelen van de vertaalde tekst.
    >
    > Bijvoorbeeld, als je LUIS in het Engels traint, maar Frans wilt gebruiken als de gebruikers taal, kun je zinnen zoals "set a 2 minute and 27 second timer" van Engels naar Frans vertalen met Bing Translate, en vervolgens de knop **Luister naar vertaling** gebruiken om de vertaling in je microfoon te spreken.
    >
    > ![De knop Luister naar vertaling op Bing Translate](../../../../../translated_images/nl/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Voeg de API-sleutel van de vertaalservice toe onder de `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Vervang `<key>` door de API-sleutel voor je vertaalserviceresource.

1. Definieer boven de functie `say` een functie `translate_text` die tekst vertaalt van de servertaal naar de gebruikerstaal:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    De van- en naar-talen worden doorgegeven aan deze functie. Je app moet converteren van gebruikerstaal naar servertaal bij het herkennen van spraak, en van servertaal naar gebruikerstaal bij het geven van gesproken feedback.

1. Definieer binnen deze functie de URL en headers voor de REST API-aanroep:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    De URL voor deze API is niet locatie-specifiek. In plaats daarvan wordt de locatie doorgegeven als een header. De API-sleutel wordt direct gebruikt, dus in tegenstelling tot de spraakservice is het niet nodig om een toegangstoken te verkrijgen van de token-uitgever API.

1. Definieer hieronder de parameters en body voor de aanroep:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    De `params` definieert de parameters die worden doorgegeven aan de API-aanroep, waarbij de van- en naar-talen worden doorgegeven. Deze aanroep vertaalt tekst in de `from`-taal naar de `to`-taal.

    De `body` bevat de tekst die moet worden vertaald. Dit is een array, omdat meerdere tekstblokken in dezelfde aanroep kunnen worden vertaald.

1. Voer de REST API-aanroep uit en verkrijg de respons:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    De respons die terugkomt is een JSON-array, met één item dat de vertalingen bevat. Dit item heeft een array met vertalingen van alle items die in de body zijn doorgegeven.

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

1. Retourneer de eigenschap `text` van de eerste vertaling uit het eerste item in de array:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Werk de `while True`-lus bij om de tekst van de aanroep naar `convert_speech_to_text` te vertalen van de gebruikerstaal naar de servertaal:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    Deze code print ook de originele en vertaalde versies van de tekst naar de console.

1. Werk de functie `say` bij om de tekst die moet worden uitgesproken te vertalen van de servertaal naar de gebruikerstaal:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    Deze code print ook de originele en vertaalde versies van de tekst naar de console.

1. Voer je code uit. Zorg ervoor dat je functie-app draait en vraag een timer aan in de gebruikerstaal, door zelf in die taal te spreken of door een vertaalapp te gebruiken.

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

    > 💁 Vanwege de verschillende manieren om iets te zeggen in verschillende talen, kun je vertalingen krijgen die iets afwijken van de voorbeelden die je aan LUIS hebt gegeven. Als dit het geval is, voeg dan meer voorbeelden toe aan LUIS, train opnieuw en publiceer het model opnieuw.

> 💁 Je kunt deze code vinden in de map [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi).

😀 Je meertalige timerprogramma was een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in de oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor kritieke informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.