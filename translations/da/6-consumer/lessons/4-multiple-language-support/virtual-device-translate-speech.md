# Oversæt tale - Virtuel IoT-enhed

I denne del af lektionen skal du skrive kode til at oversætte tale, når den konverteres til tekst ved hjælp af tale-tjenesten, og derefter oversætte teksten ved hjælp af Translator-tjenesten, før der genereres et talt svar.

## Brug tale-tjenesten til at oversætte tale

Tale-tjenesten kan tage tale og ikke kun konvertere den til tekst på samme sprog, men også oversætte outputtet til andre sprog.

### Opgave - brug tale-tjenesten til at oversætte tale

1. Åbn projektet `smart-timer` i VS Code, og sørg for, at det virtuelle miljø er indlæst i terminalen.

1. Tilføj følgende import-sætninger under de eksisterende imports:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    Dette importerer klasser, der bruges til at oversætte tale, samt et `requests`-bibliotek, der senere i denne lektion vil blive brugt til at foretage et kald til Translator-tjenesten.

1. Din smarte timer vil have 2 sprog indstillet - sproget for serveren, der blev brugt til at træne LUIS (det samme sprog bruges også til at opbygge beskeder til brugeren), og sproget, som brugeren taler. Opdater variablen `language` til at være det sprog, brugeren vil tale, og tilføj en ny variabel kaldet `server_language` for sproget, der blev brugt til at træne LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Erstat `<user language>` med lokalitetsnavnet for det sprog, du vil tale, for eksempel `fr-FR` for fransk eller `zn-HK` for kantonesisk.

    Erstat `<server language>` med lokalitetsnavnet for sproget, der blev brugt til at træne LUIS.

    Du kan finde en liste over de understøttede sprog og deres lokalitetsnavne i [dokumentationen om sprog- og stemmeunderstøttelse på Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Hvis du ikke taler flere sprog, kan du bruge en tjeneste som [Bing Translate](https://www.bing.com/translator) eller [Google Translate](https://translate.google.com) til at oversætte fra dit foretrukne sprog til et sprog efter eget valg. Disse tjenester kan derefter afspille lyd af den oversatte tekst. Vær opmærksom på, at talegenkendelsen kan ignorere noget lydoutput fra din enhed, så du kan have brug for en ekstra enhed til at afspille den oversatte tekst.
    >
    > For eksempel, hvis du træner LUIS på engelsk, men ønsker at bruge fransk som brugersprog, kan du oversætte sætninger som "set a 2 minute and 27 second timer" fra engelsk til fransk ved hjælp af Bing Translate og derefter bruge knappen **Lyt til oversættelse** til at tale oversættelsen ind i din mikrofon.
    >
    > ![Knappen Lyt til oversættelse på Bing Translate](../../../../../translated_images/da/bing-translate.348aa796d6efe2a9.webp)

1. Erstat deklarationerne `recognizer_config` og `recognizer` med følgende:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    Dette opretter en oversættelseskonfiguration til at genkende tale på brugersproget og oprette oversættelser på bruger- og serversproget. Derefter bruges denne konfiguration til at oprette en oversættelsesgenkender - en talegenkender, der kan oversætte outputtet af talegenkendelsen til flere sprog.

    > 💁 Det oprindelige sprog skal specificeres i `target_languages`, ellers får du ingen oversættelser.

1. Opdater funktionen `recognized`, og erstat hele indholdet af funktionen med følgende:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    Denne kode tjekker, om den genkendte hændelse blev udløst, fordi tale blev oversat (denne hændelse kan udløses på andre tidspunkter, f.eks. når talen genkendes, men ikke oversættes). Hvis talen blev oversat, finder den oversættelsen i ordbogen `args.result.translations`, der matcher serversproget.

    Ordbogen `args.result.translations` er nøglebaseret på sprogdelen af lokalitetsindstillingen, ikke hele indstillingen. For eksempel, hvis du anmoder om en oversættelse til `fr-FR` for fransk, vil ordbogen indeholde en post for `fr`, ikke `fr-FR`.

    Den oversatte tekst sendes derefter til IoT Hub.

1. Kør denne kode for at teste oversættelserne. Sørg for, at din funktionsapp kører, og anmod om en timer på brugersproget, enten ved selv at tale det sprog eller ved at bruge en oversættelsesapp.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## Oversæt tekst ved hjælp af Translator-tjenesten

Tale-tjenesten understøtter ikke oversættelse af tekst tilbage til tale. I stedet kan du bruge Translator-tjenesten til at oversætte teksten. Denne tjeneste har et REST API, som du kan bruge til at oversætte teksten.

### Opgave - brug Translator-ressourcen til at oversætte tekst

1. Tilføj Translator API-nøglen under `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Erstat `<key>` med API-nøglen til din Translator-tjenesteressource.

1. Over funktionen `say`, definer en funktion `translate_text`, der oversætter tekst fra serversproget til brugersproget:

    ```python
    def translate_text(text):
    ```

1. Inde i denne funktion, definer URL'en og overskrifterne til REST API-kaldet:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL'en for dette API er ikke lokalitetsspecifik, i stedet sendes lokaliteten som en overskrift. API-nøglen bruges direkte, så i modsætning til tale-tjenesten er der ikke behov for at hente en adgangstoken fra token-udsteder-API'et.

1. Definer parametrene og kroppen til kaldet nedenfor:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` definerer parametrene, der skal sendes til API-kaldet, og angiver fra- og til-sprog. Dette kald vil oversætte tekst fra `from`-sproget til `to`-sproget.

    `body` indeholder teksten, der skal oversættes. Dette er et array, da flere tekstblokke kan oversættes i samme kald.

1. Foretag kaldet til REST API'et, og hent svaret:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Svaret, der kommer tilbage, er et JSON-array med et element, der indeholder oversættelserne. Dette element har et array for oversættelser af alle de elementer, der blev sendt i kroppen.

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

1. Returner egenskaben `text` fra den første oversættelse fra det første element i arrayet:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Opdater funktionen `say` til at oversætte teksten, der skal siges, før SSML genereres:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    Denne kode udskriver også den originale og oversatte version af teksten til konsollen.

1. Kør din kode. Sørg for, at din funktionsapp kører, og anmod om en timer på brugersproget, enten ved selv at tale det sprog eller ved at bruge en oversættelsesapp.

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

    > 💁 På grund af de forskellige måder at sige noget på på forskellige sprog, kan du få oversættelser, der er lidt anderledes end de eksempler, du gav LUIS. Hvis dette er tilfældet, tilføj flere eksempler til LUIS, træn modellen igen, og udgiv den på ny.

> 💁 Du kan finde denne kode i mappen [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device).

😀 Dit flersprogede timerprogram var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.