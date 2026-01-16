<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f6c164e349f8989959e02a90f37908d",
  "translation_date": "2025-08-24T23:49:34+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/wio-terminal-translate-speech.md",
  "language_code": "fr"
}
-->
# Traduire le discours - Wio Terminal

Dans cette partie de la leçon, vous allez écrire du code pour traduire du texte en utilisant le service de traduction.

## Convertir du texte en discours à l'aide du service de traduction

L'API REST du service de reconnaissance vocale ne prend pas en charge les traductions directes. Vous pouvez cependant utiliser le service de traduction pour traduire le texte généré par le service de reconnaissance vocale, ainsi que le texte de la réponse vocale. Ce service dispose d'une API REST que vous pouvez utiliser pour traduire le texte, mais pour simplifier son utilisation, il sera encapsulé dans un autre déclencheur HTTP dans votre application de fonctions.

### Tâche - créer une fonction sans serveur pour traduire du texte

1. Ouvrez votre projet `smart-timer-trigger` dans VS Code et ouvrez le terminal en vous assurant que l'environnement virtuel est activé. Si ce n'est pas le cas, fermez et recréez le terminal.

1. Ouvrez le fichier `local.settings.json` et ajoutez les paramètres pour la clé API et la localisation du service de traduction :

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    Remplacez `<key>` par la clé API de votre ressource de service de traduction. Remplacez `<location>` par la localisation que vous avez utilisée lors de la création de la ressource du service de traduction.

1. Ajoutez un nouveau déclencheur HTTP à cette application appelé `translate-text` en utilisant la commande suivante depuis le terminal VS Code dans le dossier racine du projet de l'application de fonctions :

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    Cela créera un déclencheur HTTP appelé `translate-text`.

1. Remplacez le contenu du fichier `__init__.py` dans le dossier `translate-text` par ce qui suit :

    ```python
    import logging
    import os
    import requests
    
    import azure.functions as func
    
    location = os.environ['TRANSLATOR_LOCATION']
    translator_key = os.environ['TRANSLATOR_KEY']
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        from_language = req_body['from_language']
        to_language = req_body['to_language']
        text = req_body['text']
        
        logging.info(f'Translating {text} from {from_language} to {to_language}')
    
        url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'
    
        headers = {
            'Ocp-Apim-Subscription-Key': translator_key,
            'Ocp-Apim-Subscription-Region': location,
            'Content-type': 'application/json'
        }
    
        params = {
            'from': from_language,
            'to': to_language
        }
    
        body = [{
            'text' : text
        }]
        
        response = requests.post(url, headers=headers, params=params, json=body)
        return func.HttpResponse(response.json()[0]['translations'][0]['text'])
    ```

    Ce code extrait le texte et les langues de la requête HTTP. Il effectue ensuite une requête à l'API REST du traducteur, en passant les langues comme paramètres pour l'URL et le texte à traduire comme corps. Enfin, la traduction est renvoyée.

1. Exécutez votre application de fonctions localement. Vous pouvez ensuite l'appeler en utilisant un outil comme curl, de la même manière que vous avez testé votre déclencheur HTTP `text-to-timer`. Assurez-vous de passer le texte à traduire et les langues comme corps JSON :

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    Cet exemple traduit *Définir une minuterie de 30 secondes* du français vers l'anglais américain. Il renverra *Set a 30-second timer*.

> 💁 Vous pouvez trouver ce code dans le dossier [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions).

### Tâche - utiliser la fonction de traduction pour traduire du texte

1. Ouvrez le projet `smart-timer` dans VS Code s'il n'est pas déjà ouvert.

1. Votre minuterie intelligente aura 2 langues définies : la langue du serveur utilisée pour entraîner LUIS (la même langue est également utilisée pour construire les messages à dire à l'utilisateur) et la langue parlée par l'utilisateur. Mettez à jour la constante `LANGUAGE` dans le fichier d'en-tête `config.h` pour qu'elle corresponde à la langue parlée par l'utilisateur, et ajoutez une nouvelle constante appelée `SERVER_LANGUAGE` pour la langue utilisée pour entraîner LUIS :

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    Remplacez `<user language>` par le nom de la locale de la langue que vous allez parler, par exemple `fr-FR` pour le français ou `zn-HK` pour le cantonais.

    Remplacez `<server language>` par le nom de la locale de la langue utilisée pour entraîner LUIS.

    Vous pouvez trouver une liste des langues prises en charge et leurs noms de locale dans la [documentation sur le support des langues et des voix sur Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Si vous ne parlez pas plusieurs langues, vous pouvez utiliser un service comme [Bing Translate](https://www.bing.com/translator) ou [Google Translate](https://translate.google.com) pour traduire de votre langue préférée vers une langue de votre choix. Ces services peuvent ensuite jouer l'audio du texte traduit.
    >
    > Par exemple, si vous entraînez LUIS en anglais mais souhaitez utiliser le français comme langue utilisateur, vous pouvez traduire des phrases comme "set a 2 minute and 27 second timer" de l'anglais au français en utilisant Bing Translate, puis utiliser le bouton **Écouter la traduction** pour parler la traduction dans votre microphone.
    >
    > ![Le bouton écouter la traduction sur Bing Translate](../../../../../translated_images/fr/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Ajoutez la clé API et la localisation du traducteur sous `SPEECH_LOCATION` :

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    Remplacez `<KEY>` par la clé API de votre ressource de service de traduction. Remplacez `<LOCATION>` par la localisation que vous avez utilisée lors de la création de la ressource du service de traduction.

1. Ajoutez l'URL du déclencheur du traducteur sous `VOICE_URL` :

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    Remplacez `<URL>` par l'URL du déclencheur HTTP `translate-text` de votre application de fonctions. Ce sera la même valeur que `TEXT_TO_TIMER_FUNCTION_URL`, sauf avec un nom de fonction `translate-text` au lieu de `text-to-timer`.

1. Ajoutez un nouveau fichier au dossier `src` appelé `text_translator.h`.

1. Ce nouveau fichier d'en-tête `text_translator.h` contiendra une classe pour traduire du texte. Ajoutez ce qui suit à ce fichier pour déclarer cette classe :

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    
    class TextTranslator
    {
    public:   
    private:
        WiFiClient _client;
    };
    
    TextTranslator textTranslator;
    ```

    Cela déclare la classe `TextTranslator`, ainsi qu'une instance de cette classe. La classe possède un seul champ pour le client WiFi.

1. Dans la section `public` de cette classe, ajoutez une méthode pour traduire du texte :

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    Cette méthode prend la langue source et la langue cible. Lors de la gestion du discours, le discours sera traduit de la langue utilisateur vers la langue du serveur LUIS, et lors de la réponse, il sera traduit de la langue du serveur LUIS vers la langue utilisateur.

1. Dans cette méthode, ajoutez du code pour construire un corps JSON contenant le texte à traduire et les langues :

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;
    doc["from_language"] = from_language;
    doc["to_language"] = to_language;

    String body;
    serializeJson(doc, body);

    Serial.print("Translating ");
    Serial.print(text);
    Serial.print(" from ");
    Serial.print(from_language);
    Serial.print(" to ");
    Serial.print(to_language);
    ```

1. En dessous, ajoutez le code pour envoyer le corps à l'application de fonctions sans serveur :

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Ensuite, ajoutez du code pour obtenir la réponse :

    ```cpp
    String translated_text = "";

    if (httpResponseCode == 200)
    {
        translated_text = httpClient.getString();
        Serial.print("Translated: ");
        Serial.println(translated_text);
    }
    else
    {
        Serial.print("Failed to translate text - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. Enfin, ajoutez du code pour fermer la connexion et renvoyer le texte traduit :

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### Tâche - traduire le discours reconnu et les réponses

1. Ouvrez le fichier `main.cpp`.

1. Ajoutez une directive d'inclusion en haut du fichier pour le fichier d'en-tête de la classe `TextTranslator` :

    ```cpp
    #include "text_translator.h"
    ```

1. Le texte prononcé lorsqu'une minuterie est définie ou expire doit être traduit. Pour ce faire, ajoutez ce qui suit comme première ligne de la fonction `say` :

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Cela traduira le texte dans la langue de l'utilisateur.

1. Dans la fonction `processAudio`, le texte est récupéré à partir de l'audio capturé avec l'appel `String text = speechToText.convertSpeechToText();`. Après cet appel, traduisez le texte :

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Cela traduira le texte de la langue de l'utilisateur vers la langue utilisée sur le serveur.

1. Compilez ce code, téléchargez-le sur votre Wio Terminal et testez-le via le moniteur série. Une fois que vous voyez `Ready` dans le moniteur série, appuyez sur le bouton C (celui situé sur le côté gauche, le plus proche de l'interrupteur d'alimentation) et parlez. Assurez-vous que votre application de fonctions est en cours d'exécution et demandez une minuterie dans la langue utilisateur, soit en parlant cette langue vous-même, soit en utilisant une application de traduction.

    ```output
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Définir une minuterie de 2 minutes 27 secondes.","Offset":9600000,"Duration":40400000}
    Translating Définir une minuterie de 2 minutes 27 secondes. from fr-FR to en-US
    Translated: Set a timer of 2 minutes 27 seconds.
    Set a timer of 2 minutes 27 seconds.
    {"seconds": 147}
    Translating 2 minute 27 second timer started. from en-US to fr-FR
    Translated: 2 minute 27 seconde minute a commencé.
    2 minute 27 seconde minute a commencé.
    Translating Times up on your 2 minute 27 second timer. from en-US to fr-FR
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

> 💁 Vous pouvez trouver ce code dans le dossier [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal).

😀 Votre programme de minuterie multilingue est un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de faire appel à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.