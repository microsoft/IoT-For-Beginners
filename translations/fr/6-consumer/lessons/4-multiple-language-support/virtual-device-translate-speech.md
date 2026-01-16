<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d620a470d9dd8614d99824832978360a",
  "translation_date": "2025-08-24T23:56:23+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/virtual-device-translate-speech.md",
  "language_code": "fr"
}
-->
# Traduire la parole - Appareil IoT Virtuel

Dans cette partie de la leçon, vous allez écrire du code pour traduire la parole en texte à l'aide du service de reconnaissance vocale, puis traduire le texte avec le service Translator avant de générer une réponse vocale.

## Utiliser le service de reconnaissance vocale pour traduire la parole

Le service de reconnaissance vocale peut non seulement convertir la parole en texte dans la même langue, mais aussi traduire le résultat dans d'autres langues.

### Tâche - utiliser le service de reconnaissance vocale pour traduire la parole

1. Ouvrez le projet `smart-timer` dans VS Code et assurez-vous que l'environnement virtuel est chargé dans le terminal.

1. Ajoutez les instructions d'importation suivantes sous les imports existants :

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    Cela importe les classes utilisées pour traduire la parole, ainsi qu'une bibliothèque `requests` qui sera utilisée pour effectuer un appel au service Translator plus tard dans cette leçon.

1. Votre minuteur intelligent aura 2 langues définies : la langue du serveur utilisée pour entraîner LUIS (la même langue est également utilisée pour construire les messages destinés à l'utilisateur) et la langue parlée par l'utilisateur. Mettez à jour la variable `language` pour qu'elle corresponde à la langue parlée par l'utilisateur, et ajoutez une nouvelle variable appelée `server_language` pour la langue utilisée pour entraîner LUIS :

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Remplacez `<user language>` par le nom de la locale correspondant à la langue que vous allez parler, par exemple `fr-FR` pour le français ou `zn-HK` pour le cantonais.

    Remplacez `<server language>` par le nom de la locale correspondant à la langue utilisée pour entraîner LUIS.

    Vous pouvez trouver une liste des langues prises en charge et leurs noms de locale dans la [documentation sur le support des langues et des voix sur Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Si vous ne parlez pas plusieurs langues, vous pouvez utiliser un service comme [Bing Translate](https://www.bing.com/translator) ou [Google Translate](https://translate.google.com) pour traduire de votre langue préférée vers une autre langue de votre choix. Ces services peuvent ensuite jouer un audio du texte traduit. Notez que le service de reconnaissance vocale peut ignorer certains audios provenant de votre appareil, vous pourriez donc avoir besoin d'un appareil supplémentaire pour jouer le texte traduit.
    >
    > Par exemple, si vous entraînez LUIS en anglais mais souhaitez utiliser le français comme langue utilisateur, vous pouvez traduire des phrases comme "set a 2 minute and 27 second timer" de l'anglais au français en utilisant Bing Translate, puis utiliser le bouton **Écouter la traduction** pour prononcer la traduction dans votre microphone.
    >
    > ![Le bouton écouter la traduction sur Bing Translate](../../../../../translated_images/fr/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Remplacez les déclarations `recognizer_config` et `recognizer` par ce qui suit :

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    Cela crée une configuration de traduction pour reconnaître la parole dans la langue utilisateur et générer des traductions dans la langue utilisateur et la langue serveur. Ensuite, cette configuration est utilisée pour créer un traducteur vocal - un outil de reconnaissance vocale capable de traduire le résultat de la reconnaissance vocale dans plusieurs langues.

    > 💁 La langue d'origine doit être spécifiée dans les `target_languages`, sinon vous n'obtiendrez aucune traduction.

1. Mettez à jour la fonction `recognized`, en remplaçant tout le contenu de la fonction par ce qui suit :

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    Ce code vérifie si l'événement de reconnaissance a été déclenché parce que la parole a été traduite (cet événement peut être déclenché à d'autres moments, comme lorsque la parole est reconnue mais non traduite). Si la parole a été traduite, il trouve la traduction dans le dictionnaire `args.result.translations` qui correspond à la langue serveur.

    Le dictionnaire `args.result.translations` est indexé par la partie langue de la configuration locale, et non par la configuration complète. Par exemple, si vous demandez une traduction en `fr-FR` pour le français, le dictionnaire contiendra une entrée pour `fr`, et non pour `fr-FR`.

    Le texte traduit est ensuite envoyé au IoT Hub.

1. Exécutez ce code pour tester les traductions. Assurez-vous que votre application fonctionnelle est en cours d'exécution et demandez un minuteur dans la langue utilisateur, soit en parlant cette langue vous-même, soit en utilisant une application de traduction.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## Traduire du texte avec le service Translator

Le service de reconnaissance vocale ne prend pas en charge la traduction du texte en parole. Vous pouvez utiliser le service Translator pour traduire le texte. Ce service dispose d'une API REST que vous pouvez utiliser pour effectuer la traduction.

### Tâche - utiliser la ressource Translator pour traduire du texte

1. Ajoutez la clé API du service Translator sous la variable `speech_api_key` :

    ```python
    translator_api_key = '<key>'
    ```

    Remplacez `<key>` par la clé API de votre ressource Translator.

1. Au-dessus de la fonction `say`, définissez une fonction `translate_text` qui traduira le texte de la langue serveur vers la langue utilisateur :

    ```python
    def translate_text(text):
    ```

1. À l'intérieur de cette fonction, définissez l'URL et les en-têtes pour l'appel à l'API REST :

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    L'URL de cette API n'est pas spécifique à un emplacement, l'emplacement est plutôt passé en tant qu'en-tête. La clé API est utilisée directement, donc contrairement au service de reconnaissance vocale, il n'est pas nécessaire d'obtenir un jeton d'accès à partir de l'API d'émission de jetons.

1. En dessous, définissez les paramètres et le corps de l'appel :

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    Les `params` définissent les paramètres à passer à l'appel API, en spécifiant les langues source et cible. Cet appel traduira le texte de la langue `from` vers la langue `to`.

    Le `body` contient le texte à traduire. C'est un tableau, car plusieurs blocs de texte peuvent être traduits dans le même appel.

1. Effectuez l'appel à l'API REST et obtenez la réponse :

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    La réponse qui revient est un tableau JSON, avec un élément contenant les traductions. Cet élément contient un tableau pour les traductions de tous les éléments passés dans le corps.

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

1. Retournez la propriété `text` de la première traduction du premier élément du tableau :

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Mettez à jour la fonction `say` pour traduire le texte à dire avant que le SSML ne soit généré :

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    Ce code imprime également les versions originale et traduite du texte dans la console.

1. Exécutez votre code. Assurez-vous que votre application fonctionnelle est en cours d'exécution et demandez un minuteur dans la langue utilisateur, soit en parlant cette langue vous-même, soit en utilisant une application de traduction.

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

    > 💁 En raison des différentes façons de dire quelque chose dans différentes langues, vous pourriez obtenir des traductions légèrement différentes des exemples que vous avez donnés à LUIS. Si c'est le cas, ajoutez plus d'exemples à LUIS, réentraînez et republiez le modèle.

> 💁 Vous pouvez trouver ce code dans le dossier [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device).

😀 Votre programme de minuteur multilingue est un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.