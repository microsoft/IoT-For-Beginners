# Construire une veilleuse - Raspberry Pi

Dans cette partie de la leçon, vous allez ajouter un capteur de lumière à votre Raspberry Pi.

## Matériel

Le capteur utilisé pour cette leçon est un **capteur de lumière** qui utilise une [photodiode](https://wikipedia.org/wiki/Photodiode) pour convertir la lumière en un signal électrique. Il s'agit d'un capteur analogique qui envoie une valeur entière de 0 à 1000 indiquant une quantité relative de lumière qui ne correspond à aucune unité de mesure standard telle que le [lux](https://fr.wikipedia.org/wiki/Lux_(unit%C3%A9)).

Le capteur de lumière est un capteur Grove et doit être connecté au chapeau de base Grove sur le Raspberry Pi.

### Connecter le capteur de lumière

Le capteur de lumière Grove utilisé pour détecter les niveaux de lumière doit être connecté au Raspberry Pi.

#### Tâche - connecter le capteur de lumière

Connecter le capteur de lumière

![Un capteur de lumière Grove](../../../../images/grove-light-sensor.png)

1. Insérez une extrémité d'un câble Grove dans la prise du module du capteur de lumière. Il ne peut être inséré que dans un seul sens.

1. Le Raspberry Pi étant éteint, connectez l'autre extrémité du câble Grove à la prise analogique marquée **A0** sur le chapeau de base Grove fixé au Pi. Cette prise est la deuxième en partant de la droite, sur la rangée de prises à côté des broches GPIO.

![Le capteur de lumière Grove connecté à la prise A0](../../../../images/pi-light-sensor.png)

## Programmer le capteur de lumière

L'appareil peut maintenant être programmé à l'aide du capteur de lumière Grove.

### Tâche - programmer le capteur de lumière

Programmez l'appareil.

1. Allumez le Pi et attendez qu'il démarre

1. Ouvrez le projet nightlight dans VS Code que vous avez créé dans la partie précédente de ce travail, soit en l'exécutant directement sur le Pi, soit en le connectant à l'aide de l'extension Remote SSH.

1. Ouvrez le fichier `app.py` et supprimez tout le code qu'il contient.

1. Ajoutez le code suivant au fichier `app.py` pour importer certaines bibliothèques nécessaires :

    ```python
    import time
    from grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    L'instruction `import time` importe le module `time` qui sera utilisé plus tard dans ce travail.

    L'instruction `from grove.grove_light_sensor_v1_2 import GroveLightSensor` importe le module `GroveLightSensor` des bibliothèques Grove Python. Cette bibliothèque contient du code pour interagir avec un capteur de lumière Grove, et a été installée globalement lors de l'installation du Pi.

1. Ajoutez le code suivant après le code ci-dessus pour créer une instance de la classe qui gère le capteur de lumière :

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    La ligne `light_sensor = GroveLightSensor(0)` crée une instance de la classe `GroveLightSensor` se connectant à la broche **A0** - la broche analogique Grove à laquelle le capteur de lumière est connecté.

1. Ajoutez une boucle infinie après le code ci-dessus pour interroger la valeur du capteur de lumière et l'imprimer sur la console :

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Ceci va lire le niveau de lumière actuel sur une échelle de 0-1023 en utilisant la propriété `light` de la classe `GroveLightSensor`. Cette propriété lit la valeur analogique de la broche. Cette valeur est ensuite imprimée sur la console.

1. Ajoutez une petite mise en veille d'une seconde à la fin de la `boucle` (`loop`) car les niveaux de lumière n'ont pas besoin d'être vérifiés en permanence. Une mise en veille réduit la consommation d'énergie de l'appareil.

    ```python
    time.sleep(1)
    ```

1. Depuis le terminal VS Code, exécutez la commande suivante pour lancer votre application Python :

    ```sh
    python3 app.py
    ```

Les valeurs lumineuses sont transmises à la console. Couvrez et découvrez le capteur de lumière, et les valeurs changeront :

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

> 💁 Vous trouverez ce code dans le dossier [code-sensor/pi](../code-sensor/pi).

😀 L'ajout d'un capteur à votre programme de veilleuse a été un succès!
