<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-24T23:01:00+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "fr"
}
-->
# Contrôlez votre veilleuse via Internet - Matériel IoT virtuel et Raspberry Pi

Dans cette partie de la leçon, vous allez envoyer des données de télémétrie avec les niveaux de lumière depuis votre Raspberry Pi ou votre appareil IoT virtuel vers un broker MQTT.

## Publier la télémétrie

L'étape suivante consiste à créer un document JSON contenant la télémétrie et à l'envoyer au broker MQTT.

### Tâche

Publiez la télémétrie sur le broker MQTT.

1. Ouvrez le projet de veilleuse dans VS Code.

1. Si vous utilisez un appareil IoT virtuel, assurez-vous que le terminal exécute l'environnement virtuel. Si vous utilisez un Raspberry Pi, vous n'aurez pas besoin d'utiliser un environnement virtuel.

1. Ajoutez l'import suivant en haut du fichier `app.py` :

    ```python
    import json
    ```

    La bibliothèque `json` est utilisée pour encoder la télémétrie sous forme de document JSON.

1. Ajoutez ce qui suit après la déclaration de `client_name` :

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    Le `client_telemetry_topic` est le sujet MQTT sur lequel l'appareil publiera les niveaux de lumière.

1. Remplacez le contenu de la boucle `while True:` à la fin du fichier par ce qui suit :

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    Ce code emballe le niveau de lumière dans un document JSON et le publie sur le broker MQTT. Ensuite, il met le programme en pause pour réduire la fréquence d'envoi des messages.

1. Exécutez le code de la même manière que vous avez exécuté le code dans la partie précédente de l'exercice. Si vous utilisez un appareil IoT virtuel, assurez-vous que l'application CounterFit est en cours d'exécution et que le capteur de lumière et la LED ont été créés sur les broches correctes.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 Vous pouvez trouver ce code dans le dossier [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) ou dans le dossier [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi).

😀 Vous avez réussi à envoyer des données de télémétrie depuis votre appareil.

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de faire appel à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.