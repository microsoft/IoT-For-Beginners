<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-25T00:16:00+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "fr"
}
-->
# Texte en parole - Appareil IoT virtuel

Dans cette partie de la leçon, vous allez écrire du code pour convertir du texte en parole en utilisant le service vocal.

## Convertir du texte en parole

Le SDK des services vocaux que vous avez utilisé dans la leçon précédente pour convertir de la parole en texte peut également être utilisé pour convertir du texte en parole. Lors de la demande de synthèse vocale, vous devez spécifier la voix à utiliser, car la parole peut être générée avec une variété de voix différentes.

Chaque langue prend en charge une gamme de voix différentes, et vous pouvez obtenir la liste des voix disponibles pour chaque langue à partir du SDK des services vocaux.

### Tâche - convertir du texte en parole

1. Ouvrez le projet `smart-timer` dans VS Code, et assurez-vous que l'environnement virtuel est chargé dans le terminal.

1. Importez le `SpeechSynthesizer` depuis le package `azure.cognitiveservices.speech` en l'ajoutant aux imports existants :

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. Au-dessus de la fonction `say`, créez une configuration vocale à utiliser avec le synthétiseur vocal :

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    Cela utilise la même clé API, localisation et langue que celles utilisées par le reconnaisseur.

1. En dessous, ajoutez le code suivant pour obtenir une voix et la définir dans la configuration vocale :

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    Cela récupère une liste de toutes les voix disponibles, puis trouve la première voix correspondant à la langue utilisée.

    > 💁 Vous pouvez obtenir la liste complète des voix prises en charge dans la [documentation sur le support des langues et des voix sur Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Si vous souhaitez utiliser une voix spécifique, vous pouvez supprimer cette fonction et coder en dur la voix en utilisant le nom de la voix depuis cette documentation. Par exemple :
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. Mettez à jour le contenu de la fonction `say` pour générer du SSML pour la réponse :

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. En dessous, arrêtez la reconnaissance vocale, faites parler le SSML, puis redémarrez la reconnaissance :

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    La reconnaissance est arrêtée pendant que le texte est prononcé pour éviter que l'annonce du démarrage du minuteur ne soit détectée, envoyée à LUIS et éventuellement interprétée comme une demande de réglage d'un nouveau minuteur.

    > 💁 Vous pouvez tester cela en commentant les lignes pour arrêter et redémarrer la reconnaissance. Réglez un minuteur, et vous pourriez constater que l'annonce en configure un nouveau, ce qui entraîne une nouvelle annonce, puis un nouveau minuteur, et ainsi de suite à l'infini !

1. Exécutez l'application, et assurez-vous que l'application fonctionnelle est également en cours d'exécution. Réglez quelques minuteurs, et vous entendrez une réponse vocale indiquant que votre minuteur a été réglé, puis une autre réponse vocale lorsque le minuteur est terminé.

> 💁 Vous pouvez trouver ce code dans le dossier [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device).

😀 Votre programme de minuteur a été un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.