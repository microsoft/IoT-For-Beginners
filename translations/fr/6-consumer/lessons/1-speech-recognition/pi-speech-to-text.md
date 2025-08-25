<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-25T00:33:35+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "fr"
}
-->
# Conversion de la parole en texte - Raspberry Pi

Dans cette partie de la leçon, vous allez écrire du code pour convertir la parole captée dans l'audio en texte en utilisant le service de reconnaissance vocale.

## Envoyer l'audio au service de reconnaissance vocale

L'audio peut être envoyé au service de reconnaissance vocale en utilisant l'API REST. Pour utiliser ce service, vous devez d'abord demander un jeton d'accès, puis utiliser ce jeton pour accéder à l'API REST. Ces jetons d'accès expirent après 10 minutes, donc votre code doit les demander régulièrement pour s'assurer qu'ils sont toujours à jour.

### Tâche - Obtenir un jeton d'accès

1. Ouvrez le projet `smart-timer` sur votre Raspberry Pi.

1. Supprimez la fonction `play_audio`. Elle n'est plus nécessaire car vous ne voulez pas qu'un minuteur intelligent répète ce que vous avez dit.

1. Ajoutez l'import suivant en haut du fichier `app.py` :

    ```python
    import requests
    ```

1. Ajoutez le code suivant au-dessus de la boucle `while True` pour déclarer certains paramètres pour le service de reconnaissance vocale :

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    Remplacez `<key>` par la clé API de votre ressource de service de reconnaissance vocale. Remplacez `<location>` par la localisation que vous avez utilisée lors de la création de la ressource du service de reconnaissance vocale.

    Remplacez `<language>` par le nom de la locale correspondant à la langue que vous allez parler, par exemple `en-GB` pour l'anglais ou `zn-HK` pour le cantonais. Vous pouvez trouver une liste des langues prises en charge et leurs noms de locale dans la [documentation sur le support des langues et des voix sur Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

1. En dessous, ajoutez la fonction suivante pour obtenir un jeton d'accès :

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Cette fonction appelle un point de terminaison pour l'émission de jetons, en passant la clé API comme en-tête. Cet appel retourne un jeton d'accès qui peut être utilisé pour appeler les services de reconnaissance vocale.

1. En dessous, déclarez une fonction pour convertir la parole captée dans l'audio en texte en utilisant l'API REST :

    ```python
    def convert_speech_to_text(buffer):
    ```

1. À l'intérieur de cette fonction, configurez l'URL de l'API REST et les en-têtes :

    ```python
    url = f'https://{location}.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1'

    headers = {
        'Authorization': 'Bearer ' + get_access_token(),
        'Content-Type': f'audio/wav; codecs=audio/pcm; samplerate={rate}',
        'Accept': 'application/json;text/xml'
    }

    params = {
        'language': language
    }
    ```

    Cela construit une URL en utilisant la localisation de la ressource du service de reconnaissance vocale. Ensuite, les en-têtes sont remplis avec le jeton d'accès obtenu via la fonction `get_access_token`, ainsi que la fréquence d'échantillonnage utilisée pour capturer l'audio. Enfin, certains paramètres sont définis pour être passés avec l'URL, contenant la langue de l'audio.

1. En dessous, ajoutez le code suivant pour appeler l'API REST et récupérer le texte :

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    Cette fonction appelle l'URL et décode la valeur JSON reçue dans la réponse. La valeur `RecognitionStatus` dans la réponse indique si l'appel a réussi à extraire la parole en texte, et si cette valeur est `Success`, le texte est retourné par la fonction, sinon une chaîne vide est retournée.

1. Au-dessus de la boucle `while True:`, définissez une fonction pour traiter le texte retourné par le service de conversion de parole en texte. Cette fonction se contentera d'afficher le texte dans la console pour l'instant.

    ```python
    def process_text(text):
        print(text)
    ```

1. Enfin, remplacez l'appel à `play_audio` dans la boucle `while True` par un appel à la fonction `convert_speech_to_text`, en passant le texte à la fonction `process_text` :

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. Exécutez le code. Appuyez sur le bouton et parlez dans le microphone. Relâchez le bouton lorsque vous avez terminé, et l'audio sera converti en texte et affiché dans la console.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    Essayez différents types de phrases, ainsi que des phrases où des mots ont le même son mais des significations différentes. Par exemple, si vous parlez en anglais, dites "I want to buy two bananas and an apple too", et remarquez comment il utilise correctement "to", "two" et "too" en fonction du contexte du mot, et pas seulement de son son.

> 💁 Vous pouvez trouver ce code dans le dossier [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi).

😀 Votre programme de conversion de parole en texte est un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.