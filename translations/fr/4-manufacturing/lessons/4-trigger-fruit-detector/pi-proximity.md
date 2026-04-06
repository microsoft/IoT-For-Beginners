# Détecter la proximité - Raspberry Pi

Dans cette partie de la leçon, vous allez ajouter un capteur de proximité à votre Raspberry Pi et lire les distances qu'il mesure.

## Matériel

Le Raspberry Pi nécessite un capteur de proximité.

Le capteur que vous utiliserez est un [capteur de distance Grove Time of Flight](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Ce capteur utilise un module de télémétrie laser pour détecter les distances. Il a une portée de 10mm à 2000mm (1cm - 2m) et fournit des valeurs assez précises dans cette plage, avec des distances supérieures à 1000mm rapportées comme 8109mm.

Le télémètre laser se trouve à l'arrière du capteur, du côté opposé à la prise Grove.

C'est un capteur I²C.

### Connecter le capteur Time of Flight

Le capteur Grove Time of Flight peut être connecté au Raspberry Pi.

#### Tâche - connecter le capteur Time of Flight

Connectez le capteur Time of Flight.

![Un capteur Grove Time of Flight](../../../../../translated_images/fr/grove-time-of-flight-sensor.d82ff2165bfded9f.webp)

1. Insérez une extrémité d'un câble Grove dans la prise du capteur Time of Flight. Il ne peut être inséré que dans un seul sens.

1. Avec le Raspberry Pi éteint, connectez l'autre extrémité du câble Grove à l'une des prises I²C marquées **I²C** sur le Grove Base Hat attaché au Pi. Ces prises se trouvent sur la rangée inférieure, à l'extrémité opposée des broches GPIO et à côté de l'emplacement du câble de la caméra.

![Le capteur Grove Time of Flight connecté à la prise I²C](../../../../../translated_images/fr/pi-time-of-flight-sensor.58c8dc04eb3bfb57.webp)

## Programmer le capteur Time of Flight

Le Raspberry Pi peut maintenant être programmé pour utiliser le capteur Time of Flight connecté.

### Tâche - programmer le capteur Time of Flight

Programmez l'appareil.

1. Allumez le Raspberry Pi et attendez qu'il démarre.

1. Ouvrez le code `fruit-quality-detector` dans VS Code, soit directement sur le Pi, soit en vous connectant via l'extension Remote SSH.

1. Installez le package Pip `rpi-vl53l0x`, un package Python qui interagit avec un capteur de distance VL53L0X Time of Flight. Installez-le en utilisant cette commande pip :

    ```sh
    pip install rpi-vl53l0x
    ```

1. Créez un nouveau fichier dans ce projet appelé `distance-sensor.py`.

    > 💁 Une façon simple de simuler plusieurs appareils IoT est de les gérer dans différents fichiers Python, puis de les exécuter simultanément.

1. Ajoutez le code suivant à ce fichier :

    ```python
    import time
    
    from grove.i2c import Bus
    from rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Cela importe la bibliothèque Grove I²C bus et une bibliothèque de capteurs pour le matériel principal intégré au capteur Grove Time of Flight.

1. En dessous, ajoutez le code suivant pour accéder au capteur :

    ```python
    distance_sensor = VL53L0X(bus = Bus().bus)
    distance_sensor.begin()    
    ```

    Ce code déclare un capteur de distance en utilisant le bus Grove I²C, puis démarre le capteur.

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

1. Vous verrez les mesures de distance apparaître dans la console. Placez des objets près du capteur et vous verrez la mesure de la distance :

    ```output
    pi@raspberrypi:~/fruit-quality-detector $ python3 distance_sensor.py 
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Le télémètre se trouve à l'arrière du capteur, alors assurez-vous d'utiliser le bon côté pour mesurer la distance.

    ![Le télémètre à l'arrière du capteur Time of Flight pointant vers une banane](../../../../../translated_images/fr/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 Vous pouvez trouver ce code dans le dossier [code-proximity/pi](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/pi).

😀 Votre programme de capteur de proximité est un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.