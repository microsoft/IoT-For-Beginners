<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4efc74299e19f5d08f2f3f34451a11ba",
  "translation_date": "2025-08-24T22:02:23+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/single-board-computer-temp-publish.md",
  "language_code": "fr"
}
-->
# Publier la température - Matériel IoT virtuel et Raspberry Pi

Dans cette partie de la leçon, vous allez publier les valeurs de température détectées par le Raspberry Pi ou le dispositif IoT virtuel via MQTT, afin qu'elles puissent être utilisées ultérieurement pour calculer les GDD.

## Publier la température

Une fois la température lue, elle peut être publiée via MQTT vers un code "serveur" qui lira les valeurs et les stockera pour être utilisées dans un calcul de GDD.

### Tâche - publier la température

Programmez l'appareil pour publier les données de température.

1. Ouvrez le projet de l'application `temperature-sensor` s'il n'est pas déjà ouvert.

1. Répétez les étapes effectuées dans la leçon 4 pour vous connecter à MQTT et envoyer des télémétries. Vous utiliserez le même broker public Mosquitto.

    Les étapes sont les suivantes :

    - Ajoutez le package pip MQTT
    - Ajoutez le code pour se connecter au broker MQTT
    - Ajoutez le code pour publier les télémétries

    > ⚠️ Consultez les [instructions pour se connecter à MQTT](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md) et les [instructions pour envoyer des télémétries](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md) de la leçon 4 si nécessaire.

1. Assurez-vous que le `client_name` reflète le nom de ce projet :

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. Pour la télémétrie, au lieu d'envoyer une valeur de lumière, envoyez la valeur de température lue par le capteur DHT dans une propriété du document JSON appelée `temperature` :

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. La valeur de température n'a pas besoin d'être lue très souvent - elle ne changera pas beaucoup en peu de temps, donc définissez le `time.sleep` à 10 minutes :

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 La fonction `sleep` prend le temps en secondes, donc pour simplifier la lecture, la valeur est passée comme le résultat d'un calcul. 60s dans une minute, donc 10 x (60s dans une minute) donne un délai de 10 minutes.

1. Exécutez le code de la même manière que vous avez exécuté le code de la partie précédente de l'exercice. Si vous utilisez un dispositif IoT virtuel, assurez-vous que l'application CounterFit est en cours d'exécution et que les capteurs d'humidité et de température ont été créés sur les broches correctes.

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 Vous pouvez trouver ce code dans le dossier [code-publish-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/virtual-device) ou le dossier [code-publish-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/pi).

😀 Vous avez publié avec succès la température en tant que télémétrie depuis votre appareil.

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.