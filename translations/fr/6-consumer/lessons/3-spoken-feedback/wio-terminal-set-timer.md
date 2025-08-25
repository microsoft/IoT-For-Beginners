<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-25T00:09:18+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "fr"
}
-->
# Régler un minuteur - Wio Terminal

Dans cette partie de la leçon, vous allez appeler votre code serverless pour comprendre la parole et régler un minuteur sur votre Wio Terminal en fonction des résultats.

## Régler un minuteur

Le texte renvoyé par l'appel de conversion de la parole en texte doit être envoyé à votre code serverless pour être traité par LUIS, qui renverra le nombre de secondes pour le minuteur. Ce nombre de secondes peut être utilisé pour régler un minuteur.

Les microcontrôleurs ne prennent pas en charge nativement les threads multiples dans Arduino, donc il n'existe pas de classes de minuteur standard comme celles que vous pourriez trouver en codant en Python ou dans d'autres langages de haut niveau. À la place, vous pouvez utiliser des bibliothèques de minuteurs qui fonctionnent en mesurant le temps écoulé dans la fonction `loop` et en appelant des fonctions lorsque le temps est écoulé.

### Tâche - envoyer le texte à la fonction serverless

1. Ouvrez le projet `smart-timer` dans VS Code s'il n'est pas déjà ouvert.

1. Ouvrez le fichier d'en-tête `config.h` et ajoutez l'URL de votre application de fonction :

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    Remplacez `<URL>` par l'URL de votre application de fonction que vous avez obtenue à la dernière étape de la leçon précédente, en pointant vers l'adresse IP de votre machine locale qui exécute l'application de fonction.

1. Créez un nouveau fichier dans le dossier `src` appelé `language_understanding.h`. Ce fichier sera utilisé pour définir une classe qui enverra la parole reconnue à votre application de fonction pour être convertie en secondes à l'aide de LUIS.

1. Ajoutez ce qui suit en haut de ce fichier :

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    Cela inclut certains fichiers d'en-tête nécessaires.

1. Définissez une classe appelée `LanguageUnderstanding` et déclarez une instance de cette classe :

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. Pour appeler votre application de fonction, vous devez déclarer un client WiFi. Ajoutez ce qui suit à la section `private` de la classe :

    ```cpp
    WiFiClient _client;
    ```

1. Dans la section `public`, déclarez une méthode appelée `GetTimerDuration` pour appeler l'application de fonction :

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. Dans la méthode `GetTimerDuration`, ajoutez le code suivant pour construire le JSON à envoyer à l'application de fonction :

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Cela convertit le texte passé à la méthode `GetTimerDuration` en JSON suivant :

    ```json
    {
        "text" : "<text>"
    }
    ```

    où `<text>` est le texte passé à la fonction.

1. En dessous, ajoutez le code suivant pour effectuer l'appel à l'application de fonction :

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Cela effectue une requête POST à l'application de fonction, en passant le corps JSON et en obtenant le code de réponse.

1. Ajoutez le code suivant en dessous :

    ```cpp
    int seconds = 0;
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonObject obj = doc.as<JsonObject>();
        seconds = obj["seconds"].as<int>();
    }
    else
    {
        Serial.print("Failed to understand text - error ");
        Serial.println(httpResponseCode);
    }
    ```

    Ce code vérifie le code de réponse. S'il est 200 (succès), alors le nombre de secondes pour le minuteur est récupéré à partir du corps de la réponse. Sinon, une erreur est envoyée au moniteur série et le nombre de secondes est défini sur 0.

1. Ajoutez le code suivant à la fin de cette méthode pour fermer la connexion HTTP et retourner le nombre de secondes :

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. Dans le fichier `main.cpp`, incluez ce nouvel en-tête :

    ```cpp
    #include "speech_to_text.h"
    ```

1. À la fin de la fonction `processAudio`, appelez la méthode `GetTimerDuration` pour obtenir la durée du minuteur :

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    Cela convertit le texte de l'appel à la classe `SpeechToText` en nombre de secondes pour le minuteur.

### Tâche - régler un minuteur

Le nombre de secondes peut être utilisé pour régler un minuteur.

1. Ajoutez la dépendance de bibliothèque suivante au fichier `platformio.ini` pour ajouter une bibliothèque permettant de régler un minuteur :

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. Ajoutez une directive d'inclusion pour cette bibliothèque dans le fichier `main.cpp` :

    ```cpp
    #include <arduino-timer.h>
    ```

1. Au-dessus de la fonction `processAudio`, ajoutez le code suivant :

    ```cpp
    auto timer = timer_create_default();
    ```

    Ce code déclare un minuteur appelé `timer`.

1. En dessous, ajoutez le code suivant :

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    Cette fonction `say` convertira éventuellement le texte en parole, mais pour l'instant, elle écrira simplement le texte passé au moniteur série.

1. En dessous de la fonction `say`, ajoutez le code suivant :

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    Il s'agit d'une fonction de rappel qui sera appelée lorsqu'un minuteur expirera. Elle reçoit un message à dire lorsque le minuteur expire. Les minuteurs peuvent se répéter, et cela peut être contrôlé par la valeur de retour de ce rappel - ici, cela retourne `false` pour indiquer que le minuteur ne doit pas se répéter.

1. Ajoutez le code suivant à la fin de la fonction `processAudio` :

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    Ce code vérifie le nombre total de secondes, et s'il est 0, retourne de l'appel de fonction pour qu'aucun minuteur ne soit réglé. Il convertit ensuite le nombre total de secondes en minutes et secondes.

1. En dessous de ce code, ajoutez ce qui suit pour créer un message à dire lorsque le minuteur démarre :

    ```cpp
    String begin_message;
    if (minutes > 0)
    {
        begin_message += minutes;
        begin_message += " minute ";
    }
    if (seconds > 0)
    {
        begin_message += seconds;
        begin_message += " second ";
    }

    begin_message += "timer started.";
    ```

1. En dessous, ajoutez un code similaire pour créer un message à dire lorsque le minuteur a expiré :

    ```cpp
    String end_message("Times up on your ");
    if (minutes > 0)
    {
        end_message += minutes;
        end_message += " minute ";
    }
    if (seconds > 0)
    {
        end_message += seconds;
        end_message += " second ";
    }

    end_message += "timer.";
    ```

1. Après cela, dites le message de démarrage du minuteur :

    ```cpp
    say(begin_message);
    ```

1. À la fin de cette fonction, démarrez le minuteur :

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    Cela déclenche le minuteur. Le minuteur est réglé en utilisant des millisecondes, donc le nombre total de secondes est multiplié par 1 000 pour convertir en millisecondes. La fonction `timerExpired` est passée comme rappel, et le `end_message` est passé comme argument au rappel. Ce rappel ne prend que des arguments de type `void *`, donc la chaîne est convertie de manière appropriée.

1. Enfin, le minuteur doit *avancer*, et cela se fait dans la fonction `loop`. Ajoutez le code suivant à la fin de la fonction `loop` :

    ```cpp
    timer.tick();
    ```

1. Compilez ce code, téléversez-le sur votre Wio Terminal et testez-le via le moniteur série. Une fois que vous voyez `Ready` dans le moniteur série, appuyez sur le bouton C (celui sur le côté gauche, le plus proche de l'interrupteur d'alimentation), et parlez. 4 secondes d'audio seront capturées, converties en texte, puis envoyées à votre application de fonction, et un minuteur sera réglé. Assurez-vous que votre application de fonction s'exécute localement.

    Vous verrez quand le minuteur démarre et quand il se termine.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Set a 2 minute and 27 second timer.","Offset":4700000,"Duration":35300000}
    Set a 2 minute and 27 second timer.
    {"seconds": 147}
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 Vous pouvez trouver ce code dans le dossier [code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal).

😀 Votre programme de minuteur a été un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.