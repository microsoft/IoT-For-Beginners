# Publier la température - Matériel virtuel IoT et Raspberry Pi

Dans cette partie de la leçon, vous allez publier les valeurs de température détectées par le Raspberry Pi ou le dispositif IoT virtuel sur MQTT afin qu'elles puissent être utilisées ultérieurement pour calculer le DJC.

## Publier la temperature

Une fois la température lue, elle peut être publiée via MQTT vers un code "serveur" qui lira les valeurs et les stockera, prêtes à être utilisées pour un calcul de DJC.

### Tâche - Publier la température

Programmez l'appareil pour qu'il publie les données de température.

1. Ouvrez le projet d'application `temperature-sensor` s'il ne l'est pas déjà.

1. Répétez les étapes de la leçon 4 pour vous connecter à MQTT et envoyer la télémétrie. Vous utiliserez le même "broker" publique Mosquitto.

    Les étapes sont:

    - Ajout de la librairie pip de MQTT paho
    - Ajouter le code afin de se conecter au broker MQTT
    - Ajouter le code permettant de publier la télémètrie

    > ⚠️ Consultez les [instructions pour la connexion à MQTT](../../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md) ainsi que les [instructions pour l'envoi de la télémétrie](../../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md) de la leçon 4 si nécessaire.

1. Assurez-vous que le `client_name` reflète le nom de ce projet :

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. Pour la télémétrie, au lieu d'envoyer une valeur de lumière, envoyez la valeur de température lue par le capteur DHT dans une propriété du document JSON appelée `temperature` :

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. La valeur de la température n'a pas besoin d'être lue très souvent - elle ne changera pas beaucoup dans un court laps de temps, donc réglez le `time.sleep` à 10 minutes :

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 La fonction `sleep` prend le temps en secondes, donc pour faciliter la lecture, la valeur est passée comme le résultat d'un calcul. 60s en une minute, donc 10 x (60s en une minute) donne un délai de 10 minutes.

1. Exécutez le code de la même manière que vous avez exécuté le code de la partie précédente du devoir. Si vous utilisez un appareil IoT virtuel, assurez-vous que l'application CounterFit est en cours d'exécution et que les capteurs d'humidité et de température ont été créés sur les bonnes broches IO.

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 Vous pouvez trouver ce code dans le dossier [code-publish-temperature/virtual-device].(../code-publish-temperature/virtual-device) ou encore [code-publish-temperature/pi](../code-publish-temperature/pi).

😀 Vous avez publié avec succès la température en tant que télémétrie de votre appareil.
