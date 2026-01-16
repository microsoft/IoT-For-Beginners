<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e9f05bdc50a40fd924b1d66934471bf",
  "translation_date": "2025-08-24T21:56:03+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/virtual-device-proximity.md",
  "language_code": "fr"
}
-->
# Détecter la proximité - Matériel IoT Virtuel

Dans cette partie de la leçon, vous allez ajouter un capteur de proximité à votre appareil IoT virtuel et lire les distances qu'il mesure.

## Matériel

L'appareil IoT virtuel utilisera un capteur de distance simulé.

Sur un appareil IoT physique, vous utiliseriez un capteur avec un module de télémétrie laser pour détecter les distances.

### Ajouter le capteur de distance à CounterFit

Pour utiliser un capteur de distance virtuel, vous devez en ajouter un dans l'application CounterFit.

#### Tâche - ajouter le capteur de distance à CounterFit

Ajoutez le capteur de distance à l'application CounterFit.

1. Ouvrez le code `fruit-quality-detector` dans VS Code et assurez-vous que l'environnement virtuel est activé.

1. Installez un package Pip supplémentaire pour ajouter un shim CounterFit capable de communiquer avec des capteurs de distance en simulant le package [rpi-vl53l0x Pip](https://pypi.org/project/rpi-vl53l0x/), un package Python qui interagit avec [un capteur de distance VL53L0X à temps de vol](https://wiki.seeedstudio.com/Grove-Time_of_Flight_Distance_Sensor-VL53L0X/). Assurez-vous d'installer cela depuis un terminal avec l'environnement virtuel activé.

    ```sh
    pip install counterfit-shims-rpi-vl53l0x
    ```

1. Assurez-vous que l'application web CounterFit est en cours d'exécution.

1. Créez un capteur de distance :

    1. Dans la boîte *Create sensor* du volet *Sensors*, déroulez la liste *Sensor type* et sélectionnez *Distance*.

    1. Laissez les *Units* sur `Millimeter`.

    1. Ce capteur est un capteur I²C, donc définissez l'adresse sur `0x29`. Si vous utilisiez un capteur VL53L0X physique, cette adresse serait codée en dur.

    1. Sélectionnez le bouton **Add** pour créer le capteur de distance.

    ![Les paramètres du capteur de distance](../../../../../translated_images/fr/counterfit-create-distance-sensor.967c9fb98f27888d95920c9784d004c972490eb71f70397fe13bd70a79a879a3.png)

    Le capteur de distance sera créé et apparaîtra dans la liste des capteurs.

    ![Le capteur de distance créé](../../../../../translated_images/fr/counterfit-distance-sensor.079eefeeea0b68afc36431ce8fcbe2f09a7e4916ed1cd5cb30e696db53bc18fa.png)

## Programmer le capteur de distance

L'appareil IoT virtuel peut maintenant être programmé pour utiliser le capteur de distance simulé.

### Tâche - programmer le capteur à temps de vol

1. Créez un nouveau fichier dans le projet `fruit-quality-detector` appelé `distance-sensor.py`.

    > 💁 Une façon simple de simuler plusieurs appareils IoT est de les programmer dans des fichiers Python différents, puis de les exécuter simultanément.

1. Démarrez une connexion à CounterFit avec le code suivant :

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Ajoutez le code suivant juste en dessous :

    ```python
    import time
    
    from counterfit_shims_rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Cela importe la bibliothèque shim pour le capteur VL53L0X à temps de vol.

1. Ensuite, ajoutez le code suivant pour accéder au capteur :

    ```python
    distance_sensor = VL53L0X()
    distance_sensor.begin()
    ```

    Ce code déclare un capteur de distance, puis démarre le capteur.

1. Enfin, ajoutez une boucle infinie pour lire les distances :

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Ce code attend qu'une valeur soit prête à être lue depuis le capteur, puis l'affiche dans la console.

1. Exécutez ce code.

    > 💁 N'oubliez pas que ce fichier s'appelle `distance-sensor.py` ! Assurez-vous de l'exécuter avec Python, et non avec `app.py`.

1. Vous verrez les mesures de distance apparaître dans la console. Modifiez la valeur dans CounterFit pour voir cette valeur changer, ou utilisez des valeurs aléatoires.

    ```output
    (.venv) ➜  fruit-quality-detector python distance-sensor.py 
    Distance = 37 mm
    Distance = 42 mm
    Distance = 29 mm
    ```

> 💁 Vous pouvez trouver ce code dans le dossier [code-proximity/virtual-iot-device](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/virtual-iot-device).

😀 Votre programme de capteur de proximité a été un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.