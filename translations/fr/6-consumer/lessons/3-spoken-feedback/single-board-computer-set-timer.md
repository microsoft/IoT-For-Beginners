<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64ad4ddb4de81a18b7252e968f10b404",
  "translation_date": "2025-08-25T00:04:55+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/single-board-computer-set-timer.md",
  "language_code": "fr"
}
-->
# Configurer un minuteur - Matériel IoT virtuel et Raspberry Pi

Dans cette partie de la leçon, vous allez appeler votre code sans serveur pour comprendre la parole et configurer un minuteur sur votre appareil IoT virtuel ou Raspberry Pi en fonction des résultats.

## Configurer un minuteur

Le texte renvoyé par l'appel de reconnaissance vocale doit être envoyé à votre code sans serveur pour être traité par LUIS, afin d'obtenir le nombre de secondes pour le minuteur. Ce nombre de secondes peut être utilisé pour configurer un minuteur.

Les minuteurs peuvent être configurés en utilisant la classe Python `threading.Timer`. Cette classe prend un temps de délai et une fonction, et après le temps de délai, la fonction est exécutée.

### Tâche - envoyer le texte à la fonction sans serveur

1. Ouvrez le projet `smart-timer` dans VS Code et assurez-vous que l'environnement virtuel est chargé dans le terminal si vous utilisez un appareil IoT virtuel.

1. Au-dessus de la fonction `process_text`, déclarez une fonction appelée `get_timer_time` pour appeler le point de terminaison REST que vous avez créé :

    ```python
    def get_timer_time(text):
    ```

1. Ajoutez le code suivant à cette fonction pour définir l'URL à appeler :

    ```python
    url = '<URL>'
    ```

    Remplacez `<URL>` par l'URL de votre point de terminaison REST que vous avez construit dans la leçon précédente, soit sur votre ordinateur, soit dans le cloud.

1. Ajoutez le code suivant pour définir le texte comme une propriété passée en JSON à l'appel :

    ```python
    body = {
        'text': text
    }
    
    response = requests.post(url, json=body)
    ```

1. En dessous, récupérez les `seconds` du payload de réponse, en retournant 0 si l'appel a échoué :

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```

    Les appels HTTP réussis renvoient un code de statut dans la plage 200, et votre code sans serveur renvoie 200 si le texte a été traité et reconnu comme une intention de configuration de minuteur.

### Tâche - configurer un minuteur sur un thread en arrière-plan

1. Ajoutez l'instruction d'importation suivante en haut du fichier pour importer la bibliothèque Python threading :

    ```python
    import threading
    ```

1. Au-dessus de la fonction `process_text`, ajoutez une fonction pour prononcer une réponse. Pour l'instant, cela écrira simplement dans la console, mais plus tard dans cette leçon, cela prononcera le texte.

    ```python
    def say(text):
        print(text)
    ```

1. En dessous, ajoutez une fonction qui sera appelée par un minuteur pour annoncer que le minuteur est terminé :

    ```python
    def announce_timer(minutes, seconds):
        announcement = 'Times up on your '
        if minutes > 0:
            announcement += f'{minutes} minute '
        if seconds > 0:
            announcement += f'{seconds} second '
        announcement += 'timer.'
        say(announcement)
    ```

    Cette fonction prend le nombre de minutes et de secondes pour le minuteur et construit une phrase pour dire que le minuteur est terminé. Elle vérifiera le nombre de minutes et de secondes, et n'inclura chaque unité de temps que si elle a un nombre. Par exemple, si le nombre de minutes est 0, seules les secondes sont incluses dans le message. Cette phrase est ensuite envoyée à la fonction `say`.

1. En dessous, ajoutez la fonction `create_timer` suivante pour créer un minuteur :

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

    Cette fonction prend le nombre total de secondes pour le minuteur qui sera envoyé dans la commande et le convertit en minutes et secondes. Elle crée ensuite et démarre un objet minuteur en utilisant le nombre total de secondes, en passant la fonction `announce_timer` et une liste contenant les minutes et les secondes. Lorsque le minuteur expire, il appellera la fonction `announce_timer` et passera le contenu de cette liste comme paramètres - donc le premier élément de la liste sera passé comme paramètre `minutes`, et le deuxième élément comme paramètre `seconds`.

1. À la fin de la fonction `create_timer`, ajoutez du code pour construire un message à prononcer à l'utilisateur pour annoncer que le minuteur démarre :

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

    Encore une fois, cela n'inclut que l'unité de temps qui a une valeur. Cette phrase est ensuite envoyée à la fonction `say`.

1. Ajoutez ce qui suit à la fin de la fonction `process_text` pour obtenir le temps du minuteur à partir du texte, puis créer le minuteur :

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

    Le minuteur est uniquement créé si le nombre de secondes est supérieur à 0.

1. Exécutez l'application et assurez-vous que l'application fonctionnelle est également en cours d'exécution. Configurez des minuteurs, et la sortie affichera le minuteur en cours de configuration, puis indiquera lorsqu'il expire :

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 Vous pouvez trouver ce code dans le dossier [code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi) ou [code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device).

😀 Votre programme de minuteur a été un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction professionnelle réalisée par un humain. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.