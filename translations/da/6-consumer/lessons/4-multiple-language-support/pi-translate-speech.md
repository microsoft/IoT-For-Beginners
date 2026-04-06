# Oversæt tale - Raspberry Pi

I denne del af lektionen skal du skrive kode for at oversætte tekst ved hjælp af oversættelsestjenesten.

## Konverter tekst til tale ved hjælp af oversættelsestjenesten

REST API'en for taletjenesten understøtter ikke direkte oversættelser, men du kan bruge oversættelsestjenesten til at oversætte teksten, der genereres af tale-til-tekst-tjenesten, samt teksten til det talte svar. Denne tjeneste har et REST API, som du kan bruge til at oversætte teksten.

### Opgave - brug oversættelsesressourcen til at oversætte tekst

1. Din smarte timer vil have 2 sprog indstillet - sproget på serveren, der blev brugt til at træne LUIS (det samme sprog bruges også til at opbygge beskeder til at tale til brugeren), og sproget, der tales af brugeren. Opdater variablen `language` til at være det sprog, som brugeren vil tale, og tilføj en ny variabel kaldet `server_language` for det sprog, der blev brugt til at træne LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Erstat `<user language>` med lokalitetsnavnet for det sprog, du vil tale, for eksempel `fr-FR` for fransk eller `zn-HK` for kantonesisk.

    Erstat `<server language>` med lokalitetsnavnet for det sprog, der blev brugt til at træne LUIS.

    Du kan finde en liste over de understøttede sprog og deres lokalitetsnavne i [Dokumentationen om sprog- og stemmestøtte på Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Hvis du ikke taler flere sprog, kan du bruge en tjeneste som [Bing Translate](https://www.bing.com/translator) eller [Google Translate](https://translate.google.com) til at oversætte fra dit foretrukne sprog til et andet sprog. Disse tjenester kan derefter afspille lyd af den oversatte tekst.
    >
    > For eksempel, hvis du træner LUIS på engelsk, men ønsker at bruge fransk som brugersprog, kan du oversætte sætninger som "set a 2 minute and 27 second timer" fra engelsk til fransk ved hjælp af Bing Translate og derefter bruge knappen **Lyt til oversættelse** til at tale oversættelsen ind i din mikrofon.
    >
    > ![Knappen lyt til oversættelse på Bing Translate](../../../../../translated_images/da/bing-translate.348aa796d6efe2a9.webp)

1. Tilføj oversættelses-API-nøglen under `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Erstat `<key>` med API-nøglen for din oversættelsestjenesteressource.

1. Over funktionen `say`, definer en funktion `translate_text`, der vil oversætte tekst fra serversproget til brugersproget:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    Fra- og til-sprogene sendes til denne funktion - din app skal konvertere fra brugersprog til serversprog, når den genkender tale, og fra serversprog til brugersprog, når den giver talte svar.

1. Inde i denne funktion, definer URL'en og headers for REST API-kaldet:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL'en for dette API er ikke lokalitetsspecifik, i stedet sendes lokaliteten som en header. API-nøglen bruges direkte, så i modsætning til taletjenesten er der ikke behov for at hente en adgangstoken fra token-udsteder-API'en.

1. Definer derefter parametrene og kroppen for kaldet:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` definerer parametrene, der skal sendes til API-kaldet, og sender fra- og til-sprog. Dette kald vil oversætte tekst fra `from`-sproget til `to`-sproget.

    `body` indeholder teksten, der skal oversættes. Dette er en array, da flere tekstblokke kan oversættes i samme kald.

1. Foretag kaldet til REST API'et, og få svaret:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Svaret, der kommer tilbage, er en JSON-array med ét element, der indeholder oversættelserne. Dette element har en array for oversættelser af alle de elementer, der blev sendt i kroppen.

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

1. Returner egenskaben `text` fra den første oversættelse fra det første element i arrayet:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Opdater `while True`-løkken til at oversætte teksten fra kaldet til `convert_speech_to_text` fra brugersproget til serversproget:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    Denne kode udskriver også de originale og oversatte versioner af teksten til konsollen.

1. Opdater funktionen `say` til at oversætte teksten, der skal siges, fra serversproget til brugersproget:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    Denne kode udskriver også de originale og oversatte versioner af teksten til konsollen.

1. Kør din kode. Sørg for, at din funktionsapp kører, og anmod om en timer på brugersproget, enten ved at tale det sprog selv eller ved at bruge en oversættelsesapp.

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

    > 💁 På grund af de forskellige måder at sige noget på på forskellige sprog, kan du få oversættelser, der er lidt anderledes end de eksempler, du gav LUIS. Hvis dette er tilfældet, tilføj flere eksempler til LUIS, gen-træn og gen-udgiv modellen.

> 💁 Du kan finde denne kode i [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi)-mappen.

😀 Dit flersprogede timerprogram var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på at sikre nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.