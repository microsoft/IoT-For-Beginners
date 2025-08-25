<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-25T00:11:04+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "fr"
}
-->
# Texte en parole - Raspberry Pi

Dans cette partie de la leçon, vous allez écrire du code pour convertir du texte en parole en utilisant le service vocal.

## Convertir du texte en parole avec le service vocal

Le texte peut être envoyé au service vocal via l'API REST pour obtenir un fichier audio qui peut être lu sur votre appareil IoT. Lors de la demande de conversion en parole, vous devez spécifier la voix à utiliser, car la parole peut être générée avec une variété de voix différentes.

Chaque langue prend en charge une gamme de voix différentes, et vous pouvez effectuer une requête REST auprès du service vocal pour obtenir la liste des voix disponibles pour chaque langue.

### Tâche - obtenir une voix

1. Ouvrez le projet `smart-timer` dans VS Code.

1. Ajoutez le code suivant au-dessus de la fonction `say` pour demander la liste des voix disponibles pour une langue :

    ```python
    def get_voice():
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token()
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        first_voice = next(x for x in voices_json if x['Locale'].lower() == language.lower() and x['VoiceType'] == 'Neural')
        return first_voice['ShortName']
    
    voice = get_voice()
    print(f'Using voice {voice}')
    ```

    Ce code définit une fonction appelée `get_voice` qui utilise le service vocal pour obtenir une liste de voix. Il trouve ensuite la première voix correspondant à la langue utilisée.

    Cette fonction est ensuite appelée pour stocker la première voix, et le nom de la voix est affiché dans la console. Cette voix peut être demandée une fois et la valeur utilisée pour chaque appel de conversion de texte en parole.

    > 💁 Vous pouvez obtenir la liste complète des voix disponibles dans la [documentation sur le support des langues et des voix sur Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Si vous souhaitez utiliser une voix spécifique, vous pouvez supprimer cette fonction et coder en dur le nom de la voix à partir de cette documentation. Par exemple :
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### Tâche - convertir du texte en parole

1. En dessous, définissez une constante pour le format audio à récupérer auprès des services vocaux. Lorsque vous demandez un fichier audio, vous pouvez le faire dans une gamme de formats différents.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    Le format que vous pouvez utiliser dépend de votre matériel. Si vous obtenez des erreurs de type `Invalid sample rate` lors de la lecture de l'audio, modifiez cette valeur. Vous pouvez trouver la liste des valeurs prises en charge dans la [documentation de l'API REST pour la conversion de texte en parole sur Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs). Vous devrez utiliser un format audio `riff`, et les valeurs à essayer sont `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` et `riff-48khz-16bit-mono-pcm`.

1. En dessous, déclarez une fonction appelée `get_speech` qui convertira le texte en parole en utilisant l'API REST du service vocal :

    ```python
    def get_speech(text):
    ```

1. Dans la fonction `get_speech`, définissez l'URL à appeler et les en-têtes à transmettre :

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    Cela configure les en-têtes pour utiliser un jeton d'accès généré, définit le contenu en SSML et spécifie le format audio requis.

1. En dessous, définissez le SSML à envoyer à l'API REST :

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    Ce SSML définit la langue et la voix à utiliser, ainsi que le texte à convertir.

1. Enfin, ajoutez du code dans cette fonction pour effectuer la requête REST et retourner les données audio binaires :

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### Tâche - lire l'audio

1. En dessous de la fonction `get_speech`, définissez une nouvelle fonction pour lire l'audio retourné par l'appel à l'API REST :

    ```python
    def play_speech(speech):
    ```

1. Le `speech` passé à cette fonction sera les données audio binaires retournées par l'API REST. Utilisez le code suivant pour ouvrir cela en tant que fichier wave et le transmettre à PyAudio pour lire l'audio :

    ```python
    def play_speech(speech):
        with wave.open(speech, 'rb') as wave_file:
            stream = audio.open(format=audio.get_format_from_width(wave_file.getsampwidth()),
                                channels=wave_file.getnchannels(),
                                rate=wave_file.getframerate(),
                                output_device_index=speaker_card_number,
                                output=True)

            data = wave_file.readframes(4096)

            while len(data) > 0:
                stream.write(data)
                data = wave_file.readframes(4096)

            stream.stop_stream()
            stream.close()
    ```

    Ce code utilise un flux PyAudio, comme pour capturer de l'audio. La différence ici est que le flux est configuré comme un flux de sortie, et les données sont lues à partir des données audio et poussées dans le flux.

    Plutôt que de coder en dur les détails du flux tels que le taux d'échantillonnage, ils sont lus à partir des données audio.

1. Remplacez le contenu de la fonction `say` par le suivant :

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    Ce code convertit le texte en parole sous forme de données audio binaires, et lit l'audio.

1. Exécutez l'application, et assurez-vous que l'application fonctionnelle est également en cours d'exécution. Configurez des minuteries, et vous entendrez une réponse vocale indiquant que votre minuterie a été configurée, puis une autre réponse vocale lorsque la minuterie est terminée.

    Si vous obtenez des erreurs de type `Invalid sample rate`, modifiez le `playback_format` comme décrit ci-dessus.

> 💁 Vous pouvez trouver ce code dans le dossier [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi).

😀 Votre programme de minuterie est un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.