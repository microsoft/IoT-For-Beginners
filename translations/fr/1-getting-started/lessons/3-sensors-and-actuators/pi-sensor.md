<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ea733bd0cdf2479e082373f765a08678",
  "translation_date": "2025-08-24T23:13:46+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-sensor.md",
  "language_code": "fr"
}
-->
# Construire une veilleuse - Raspberry Pi

Dans cette partie de la leçon, vous allez ajouter un capteur de lumière à votre Raspberry Pi.

## Matériel

Le capteur utilisé dans cette leçon est un **capteur de lumière** qui utilise une [photodiode](https://wikipedia.org/wiki/Photodiode) pour convertir la lumière en signal électrique. Il s'agit d'un capteur analogique qui envoie une valeur entière entre 0 et 1 000, indiquant une quantité relative de lumière qui ne correspond à aucune unité de mesure standard comme le [lux](https://wikipedia.org/wiki/Lux).

Le capteur de lumière est un capteur Grove externe et doit être connecté au Grove Base Hat sur le Raspberry Pi.

### Connecter le capteur de lumière

Le capteur de lumière Grove utilisé pour détecter les niveaux de lumière doit être connecté au Raspberry Pi.

#### Tâche - connecter le capteur de lumière

Connectez le capteur de lumière.

![Un capteur de lumière Grove](../../../../../translated_images/fr/grove-light-sensor.b8127b7c434e632d6bcdb57587a14e9ef69a268a22df95d08628f62b8fa5505c.png)

1. Insérez une extrémité d'un câble Grove dans la prise du module du capteur de lumière. Il ne peut être inséré que dans un seul sens.

1. Avec le Raspberry Pi éteint, connectez l'autre extrémité du câble Grove à la prise analogique marquée **A0** sur le Grove Base Hat attaché au Pi. Cette prise est la deuxième à partir de la droite, sur la rangée de prises à côté des broches GPIO.

![Le capteur de lumière Grove connecté à la prise A0](../../../../../translated_images/fr/pi-light-sensor.66cc1e31fa48cd7d5f23400d4b2119aa41508275cb7c778053a7923b4e972d7e.png)

## Programmer le capteur de lumière

L'appareil peut maintenant être programmé en utilisant le capteur de lumière Grove.

### Tâche - programmer le capteur de lumière

Programmez l'appareil.

1. Allumez le Pi et attendez qu'il démarre.

1. Ouvrez le projet de veilleuse dans VS Code que vous avez créé dans la partie précédente de cet exercice, soit directement sur le Pi, soit en utilisant l'extension Remote SSH.

1. Ouvrez le fichier `app.py` et supprimez tout le code qu'il contient.

1. Ajoutez le code suivant au fichier `app.py` pour importer les bibliothèques nécessaires :

    ```python
    import time
    from grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    L'instruction `import time` importe le module `time`, qui sera utilisé plus tard dans cet exercice.

    L'instruction `from grove.grove_light_sensor_v1_2 import GroveLightSensor` importe le `GroveLightSensor` des bibliothèques Python Grove. Cette bibliothèque contient le code pour interagir avec un capteur de lumière Grove et a été installée globalement lors de la configuration du Pi.

1. Ajoutez le code suivant après le code ci-dessus pour créer une instance de la classe qui gère le capteur de lumière :

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    La ligne `light_sensor = GroveLightSensor(0)` crée une instance de la classe `GroveLightSensor` connectée à la broche **A0** - la broche analogique Grove à laquelle le capteur de lumière est connecté.

1. Ajoutez une boucle infinie après le code ci-dessus pour interroger la valeur du capteur de lumière et l'afficher dans la console :

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Cela permettra de lire le niveau de lumière actuel sur une échelle de 0 à 1 023 en utilisant la propriété `light` de la classe `GroveLightSensor`. Cette propriété lit la valeur analogique de la broche. Cette valeur est ensuite affichée dans la console.

1. Ajoutez une petite pause d'une seconde à la fin de la `loop`, car les niveaux de lumière n'ont pas besoin d'être vérifiés en continu. Une pause réduit la consommation d'énergie de l'appareil.

    ```python
    time.sleep(1)
    ```

1. Depuis le terminal de VS Code, exécutez la commande suivante pour lancer votre application Python :

    ```sh
    python3 app.py
    ```

    Les valeurs de lumière seront affichées dans la console. Couvrez et découvrez le capteur de lumière, et les valeurs changeront :

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

> 💁 Vous pouvez trouver ce code dans le dossier [code-sensor/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/pi).

😀 Ajouter un capteur à votre programme de veilleuse a été un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction professionnelle réalisée par un humain. Nous ne sommes pas responsables des malentendus ou des interprétations erronées résultant de l'utilisation de cette traduction.