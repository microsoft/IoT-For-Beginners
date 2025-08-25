<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-25T00:23:44+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "fr"
}
-->
# Conversion de la parole en texte - Appareil IoT virtuel

Dans cette partie de la leçon, vous allez écrire du code pour convertir la parole captée par votre microphone en texte en utilisant le service de reconnaissance vocale.

## Convertir la parole en texte

Sur Windows, Linux et macOS, le SDK Python des services de reconnaissance vocale peut être utilisé pour écouter votre microphone et convertir toute parole détectée en texte. Il écoutera en continu, détectant les niveaux audio et envoyant la parole pour conversion en texte lorsque le niveau audio baisse, par exemple à la fin d'un bloc de parole.

### Tâche - convertir la parole en texte

1. Créez une nouvelle application Python sur votre ordinateur dans un dossier appelé `smart-timer` avec un seul fichier nommé `app.py` et un environnement virtuel Python.

1. Installez le package Pip pour les services de reconnaissance vocale. Assurez-vous de l'installer depuis un terminal avec l'environnement virtuel activé.

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ Si vous obtenez l'erreur suivante :
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > Vous devrez mettre à jour Pip. Faites-le avec la commande suivante, puis essayez d'installer à nouveau le package :
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Ajoutez les imports suivants au fichier `app.py` :

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    Cela importe certaines classes utilisées pour reconnaître la parole.

1. Ajoutez le code suivant pour déclarer une configuration :

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    Remplacez `<key>` par la clé API de votre service de reconnaissance vocale. Remplacez `<location>` par la localisation que vous avez utilisée lors de la création de la ressource du service de reconnaissance vocale.

    Remplacez `<language>` par le nom de la locale correspondant à la langue que vous allez parler, par exemple `en-GB` pour l'anglais ou `zn-HK` pour le cantonais. Vous pouvez trouver une liste des langues prises en charge et leurs noms de locale dans la [documentation sur le support des langues et des voix sur Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Cette configuration est ensuite utilisée pour créer un objet `SpeechConfig` qui servira à configurer les services de reconnaissance vocale.

1. Ajoutez le code suivant pour créer un reconnaisseur vocal :

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. Le reconnaisseur vocal fonctionne sur un thread en arrière-plan, écoutant l'audio et convertissant toute parole détectée en texte. Vous pouvez obtenir le texte en utilisant une fonction de rappel - une fonction que vous définissez et passez au reconnaisseur. Chaque fois qu'une parole est détectée, la fonction de rappel est appelée. Ajoutez le code suivant pour définir une fonction de rappel, la passer au reconnaisseur, ainsi que définir une fonction pour traiter le texte et l'écrire dans la console :

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. Le reconnaisseur commence à écouter uniquement lorsque vous le démarrez explicitement. Ajoutez le code suivant pour démarrer la reconnaissance. Cela fonctionne en arrière-plan, donc votre application aura également besoin d'une boucle infinie qui dort pour maintenir l'application en cours d'exécution.

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. Exécutez cette application. Parlez dans votre microphone et l'audio converti en texte sera affiché dans la console.

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    Essayez différents types de phrases, ainsi que des phrases où des mots sonnent de la même manière mais ont des significations différentes. Par exemple, si vous parlez en anglais, dites "I want to buy two bananas and an apple too", et remarquez comment il utilise correctement "to", "two" et "too" en fonction du contexte du mot, et pas seulement de son son.

> 💁 Vous pouvez trouver ce code dans le dossier [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device).

😀 Votre programme de conversion de la parole en texte a été un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.