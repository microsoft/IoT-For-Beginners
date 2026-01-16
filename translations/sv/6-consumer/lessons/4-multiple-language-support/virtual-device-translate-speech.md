<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d620a470d9dd8614d99824832978360a",
  "translation_date": "2025-08-27T21:16:31+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/virtual-device-translate-speech.md",
  "language_code": "sv"
}
-->
# Översätt tal - Virtuell IoT-enhet

I den här delen av lektionen kommer du att skriva kod för att översätta tal när det konverteras till text med hjälp av tal-tjänsten, och sedan översätta texten med Translator-tjänsten innan du genererar ett talat svar.

## Använd tal-tjänsten för att översätta tal

Tal-tjänsten kan ta tal och inte bara konvertera det till text på samma språk, utan också översätta resultatet till andra språk.

### Uppgift - använd tal-tjänsten för att översätta tal

1. Öppna projektet `smart-timer` i VS Code och se till att den virtuella miljön är laddad i terminalen.

1. Lägg till följande importsatser under de befintliga importerna:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    Detta importerar klasser som används för att översätta tal, samt ett `requests`-bibliotek som kommer att användas för att göra ett anrop till Translator-tjänsten senare i lektionen.

1. Din smarta timer kommer att ha två språk inställda - språket på servern som användes för att träna LUIS (samma språk används också för att bygga meddelanden som ska talas till användaren), och språket som talas av användaren. Uppdatera variabeln `language` till att vara språket som användaren kommer att tala, och lägg till en ny variabel som heter `server_language` för språket som användes för att träna LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Ersätt `<user language>` med lokalnamnet för språket du kommer att tala, till exempel `fr-FR` för franska eller `zn-HK` för kantonesiska.

    Ersätt `<server language>` med lokalnamnet för språket som användes för att träna LUIS.

    Du kan hitta en lista över de stödda språken och deras lokalnamn i [Language and voice support-dokumentationen på Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Om du inte talar flera språk kan du använda en tjänst som [Bing Translate](https://www.bing.com/translator) eller [Google Translate](https://translate.google.com) för att översätta från ditt föredragna språk till ett språk du väljer. Dessa tjänster kan sedan spela upp ljud av den översatta texten. Var medveten om att taligenkännaren kommer att ignorera viss ljudutgång från din enhet, så du kan behöva använda en extra enhet för att spela upp den översatta texten.
    >
    > Till exempel, om du tränar LUIS på engelska men vill använda franska som användarspråk, kan du översätta meningar som "set a 2 minute and 27 second timer" från engelska till franska med Bing Translate, och sedan använda knappen **Lyssna på översättning** för att tala översättningen i din mikrofon.
    >
    > ![Knappen för att lyssna på översättning på Bing Translate](../../../../../translated_images/sv/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Ersätt deklarationerna för `recognizer_config` och `recognizer` med följande:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    Detta skapar en översättningskonfiguration för att känna igen tal på användarspråket och skapa översättningar på användar- och serverspråket. Det använder sedan denna konfiguration för att skapa en översättningsigenkännare - en taligenkännare som kan översätta resultatet av taligenkänningen till flera språk.

    > 💁 Det ursprungliga språket måste anges i `target_languages`, annars får du inga översättningar.

1. Uppdatera funktionen `recognized` genom att ersätta hela innehållet i funktionen med följande:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    Denna kod kontrollerar om det erkända eventet utlösts eftersom talet översattes (detta event kan utlösas vid andra tillfällen, såsom när talet erkänns men inte översätts). Om talet översattes, hittar den översättningen i ordboken `args.result.translations` som matchar serverspråket.

    Ordboken `args.result.translations` är nycklad med språkdelen av lokalinställningen, inte hela inställningen. Till exempel, om du begär en översättning till `fr-FR` för franska, kommer ordboken att innehålla en post för `fr`, inte `fr-FR`.

    Den översatta texten skickas sedan till IoT Hub.

1. Kör denna kod för att testa översättningarna. Se till att din funktionsapp körs och begär en timer på användarspråket, antingen genom att tala det språket själv eller använda en översättningsapp.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## Översätt text med Translator-tjänsten

Tal-tjänsten stöder inte översättning av text tillbaka till tal, istället kan du använda Translator-tjänsten för att översätta texten. Denna tjänst har ett REST-API som du kan använda för att översätta texten.

### Uppgift - använd Translator-resursen för att översätta text

1. Lägg till Translator API-nyckeln under `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Ersätt `<key>` med API-nyckeln för din Translator-tjänstresurs.

1. Ovanför funktionen `say`, definiera en funktion `translate_text` som kommer att översätta text från serverspråket till användarspråket:

    ```python
    def translate_text(text):
    ```

1. Inuti denna funktion, definiera URL och headers för REST-API-anropet:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL:en för detta API är inte platsberoende, istället skickas platsen som en header. API-nyckeln används direkt, så till skillnad från tal-tjänsten finns det inget behov av att hämta en åtkomsttoken från tokenutgivaren API.

1. Nedanför detta definiera parametrarna och kroppen för anropet:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` definierar parametrarna som ska skickas med API-anropet, och skickar från- och till-språk. Detta anrop kommer att översätta text på `from`-språket till `to`-språket.

    `body` innehåller texten som ska översättas. Detta är en array, eftersom flera textblock kan översättas i samma anrop.

1. Gör anropet till REST-API:t och hämta svaret:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Svaret som kommer tillbaka är en JSON-array, med ett objekt som innehåller översättningarna. Detta objekt har en array för översättningar av alla objekt som skickades i kroppen.

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

1. Returnera egenskapen `text` från den första översättningen från det första objektet i arrayen:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Uppdatera funktionen `say` för att översätta texten som ska sägas innan SSML genereras:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    Denna kod skriver också ut den ursprungliga och översatta versionen av texten till konsolen.

1. Kör din kod. Se till att din funktionsapp körs och begär en timer på användarspråket, antingen genom att tala det språket själv eller använda en översättningsapp.

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

    > 💁 På grund av olika sätt att säga något på olika språk kan du få översättningar som skiljer sig något från de exempel du gav LUIS. Om detta är fallet, lägg till fler exempel i LUIS, träna om och publicera modellen igen.

> 💁 Du kan hitta denna kod i mappen [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device).

😀 Ditt flerspråkiga timerprogram blev en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiserade översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess ursprungliga språk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.