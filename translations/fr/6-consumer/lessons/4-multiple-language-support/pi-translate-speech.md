<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "bbb5aa34221fe129dd3ce4d9ec33831a",
  "translation_date": "2025-08-24T23:54:56+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/pi-translate-speech.md",
  "language_code": "fr"
}
-->
# Traduire la parole - Raspberry Pi

Dans cette partie de la leçon, vous allez écrire du code pour traduire du texte en utilisant le service de traduction.

## Convertir du texte en parole à l'aide du service de traduction

L'API REST du service vocal ne prend pas en charge les traductions directes. Cependant, vous pouvez utiliser le service Translator pour traduire le texte généré par le service de reconnaissance vocale, ainsi que le texte de la réponse parlée. Ce service dispose d'une API REST que vous pouvez utiliser pour traduire le texte.

### Tâche - utiliser la ressource Translator pour traduire du texte

1. Votre minuteur intelligent aura deux langues définies : la langue du serveur utilisée pour entraîner LUIS (cette langue est également utilisée pour construire les messages destinés à l'utilisateur) et la langue parlée par l'utilisateur. Mettez à jour la variable `language` pour qu'elle corresponde à la langue parlée par l'utilisateur, et ajoutez une nouvelle variable appelée `server_language` pour la langue utilisée pour entraîner LUIS :

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Remplacez `<user language>` par le nom de la locale correspondant à la langue que vous utiliserez, par exemple `fr-FR` pour le français, ou `zn-HK` pour le cantonais.

    Remplacez `<server language>` par le nom de la locale correspondant à la langue utilisée pour entraîner LUIS.

    Vous pouvez trouver une liste des langues prises en charge et de leurs noms de locale dans la [documentation sur le support des langues et des voix sur Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Si vous ne parlez pas plusieurs langues, vous pouvez utiliser un service comme [Bing Translate](https://www.bing.com/translator) ou [Google Translate](https://translate.google.com) pour traduire de votre langue préférée vers une langue de votre choix. Ces services peuvent ensuite lire à haute voix le texte traduit.
    >
    > Par exemple, si vous entraînez LUIS en anglais mais souhaitez utiliser le français comme langue utilisateur, vous pouvez traduire des phrases comme "set a 2 minute and 27 second timer" de l'anglais au français en utilisant Bing Translate, puis utiliser le bouton **Écouter la traduction** pour prononcer la traduction dans votre microphone.
    >
    > ![Le bouton écouter la traduction sur Bing Translate](../../../../../translated_images/fr/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Ajoutez la clé API du service Translator sous la variable `speech_api_key` :

    ```python
    translator_api_key = '<key>'
    ```

    Remplacez `<key>` par la clé API de votre ressource Translator.

1. Au-dessus de la fonction `say`, définissez une fonction `translate_text` qui traduira le texte de la langue du serveur vers la langue de l'utilisateur :

    ```python
    def translate_text(text, from_language, to_language):
    ```

    Les langues source et cible sont passées à cette fonction. Votre application doit convertir de la langue utilisateur à la langue serveur lors de la reconnaissance vocale, et de la langue serveur à la langue utilisateur pour fournir un retour vocal.

1. À l'intérieur de cette fonction, définissez l'URL et les en-têtes pour l'appel à l'API REST :

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    L'URL de cette API n'est pas spécifique à une localisation. La localisation est plutôt transmise dans un en-tête. La clé API est utilisée directement, donc contrairement au service vocal, il n'est pas nécessaire d'obtenir un jeton d'accès depuis l'API d'émission de jetons.

1. En dessous, définissez les paramètres et le corps de l'appel :

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    Les `params` définissent les paramètres à transmettre à l'appel API, en spécifiant les langues source et cible. Cet appel traduira le texte de la langue source vers la langue cible.

    Le `body` contient le texte à traduire. Il s'agit d'un tableau, car plusieurs blocs de texte peuvent être traduits dans le même appel.

1. Effectuez l'appel à l'API REST et récupérez la réponse :

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    La réponse reçue est un tableau JSON, contenant un élément avec les traductions. Cet élément contient un tableau pour les traductions de tous les éléments transmis dans le corps de la requête.

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

1. Retournez la propriété `text` de la première traduction du premier élément du tableau :

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Mettez à jour la boucle `while True` pour traduire le texte obtenu par l'appel à `convert_speech_to_text` de la langue utilisateur vers la langue serveur :

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    Ce code affiche également les versions originale et traduite du texte dans la console.

1. Mettez à jour la fonction `say` pour traduire le texte à prononcer de la langue serveur vers la langue utilisateur :

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    Ce code affiche également les versions originale et traduite du texte dans la console.

1. Exécutez votre code. Assurez-vous que votre application fonctionnelle est en cours d'exécution, et demandez un minuteur dans la langue utilisateur, soit en parlant cette langue vous-même, soit en utilisant une application de traduction.

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

    > 💁 En raison des différentes façons de formuler une phrase dans différentes langues, vous pourriez obtenir des traductions légèrement différentes des exemples que vous avez donnés à LUIS. Si c'est le cas, ajoutez plus d'exemples à LUIS, réentraînez puis republiez le modèle.

> 💁 Vous pouvez trouver ce code dans le dossier [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi).

😀 Votre programme de minuteur multilingue est un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de faire appel à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.