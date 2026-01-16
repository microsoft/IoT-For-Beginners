<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7678f7c67b97ee52d5727496dcd7d346",
  "translation_date": "2025-08-24T22:08:30+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/pi-temp.md",
  "language_code": "fr"
}
-->
# Mesurer la température - Raspberry Pi

Dans cette partie de la leçon, vous allez ajouter un capteur de température à votre Raspberry Pi.

## Matériel

Le capteur que vous utiliserez est un [capteur d'humidité et de température DHT11](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), combinant 2 capteurs en un seul module. Ce capteur est assez populaire, avec de nombreux modèles disponibles sur le marché combinant température, humidité et parfois pression atmosphérique. Le composant capteur de température est une thermistance à coefficient de température négatif (NTC), une thermistance dont la résistance diminue à mesure que la température augmente.

C'est un capteur numérique, il dispose donc d'un convertisseur analogique-numérique (ADC) intégré pour créer un signal numérique contenant les données de température et d'humidité que le microcontrôleur peut lire.

### Connecter le capteur de température

Le capteur de température Grove peut être connecté au Raspberry Pi.

#### Tâche

Connectez le capteur de température.

![Un capteur de température Grove](../../../../../translated_images/fr/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.png)

1. Insérez une extrémité d'un câble Grove dans la prise du capteur d'humidité et de température. Il ne peut être inséré que dans un seul sens.

1. Avec le Raspberry Pi éteint, connectez l'autre extrémité du câble Grove à la prise numérique marquée **D5** sur le Grove Base Hat attaché au Pi. Cette prise est la deuxième à partir de la gauche, sur la rangée de prises à côté des broches GPIO.

![Le capteur de température Grove connecté à la prise A0](../../../../../translated_images/fr/pi-temperature-sensor.3ff82fff672c8e565ef25a39d26d111de006b825a7e0867227ef4e7fbff8553c.png)

## Programmer le capteur de température

L'appareil peut maintenant être programmé pour utiliser le capteur de température connecté.

### Tâche

Programmez l'appareil.

1. Allumez le Pi et attendez qu'il démarre.

1. Lancez VS Code, soit directement sur le Pi, soit en vous connectant via l'extension Remote SSH.

    > ⚠️ Vous pouvez vous référer [aux instructions pour configurer et lancer VS Code dans la leçon 1 si nécessaire](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Depuis le terminal, créez un nouveau dossier dans le répertoire personnel de l'utilisateur `pi` appelé `temperature-sensor`. Créez un fichier dans ce dossier appelé `app.py` :

    ```sh
    mkdir temperature-sensor
    cd temperature-sensor
    touch app.py
    ```

1. Ouvrez ce dossier dans VS Code.

1. Pour utiliser le capteur de température et d'humidité, un package Pip supplémentaire doit être installé. Depuis le terminal dans VS Code, exécutez la commande suivante pour installer ce package Pip sur le Pi :

    ```sh
    pip3 install seeed-python-dht
    ```

1. Ajoutez le code suivant au fichier `app.py` pour importer les bibliothèques nécessaires :

    ```python
    import time
    from seeed_dht import DHT
    ```

    L'instruction `from seeed_dht import DHT` importe la classe `DHT` pour interagir avec un capteur de température Grove depuis le module `seeed_dht`.

1. Ajoutez le code suivant après le code ci-dessus pour créer une instance de la classe qui gère le capteur de température :

    ```python
    sensor = DHT("11", 5)
    ```

    Cela déclare une instance de la classe `DHT` qui gère le capteur numérique d'humidité et de température (**D**igital **H**umidity and **T**emperature). Le premier paramètre indique au code que le capteur utilisé est le capteur *DHT11* - la bibliothèque que vous utilisez prend en charge d'autres variantes de ce capteur. Le second paramètre indique au code que le capteur est connecté au port numérique `D5` sur le Grove Base Hat.

    > ✅ Rappelez-vous, toutes les prises ont des numéros de broches uniques. Les broches 0, 2, 4 et 6 sont des broches analogiques, les broches 5, 16, 18, 22, 24 et 26 sont des broches numériques.

1. Ajoutez une boucle infinie après le code ci-dessus pour interroger la valeur du capteur de température et l'afficher dans la console :

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    L'appel à `sensor.read()` renvoie un tuple contenant l'humidité et la température. Vous n'avez besoin que de la valeur de la température, donc l'humidité est ignorée. La valeur de la température est ensuite affichée dans la console.

1. Ajoutez une petite pause de dix secondes à la fin de la `loop`, car les niveaux de température n'ont pas besoin d'être vérifiés en continu. Une pause réduit la consommation d'énergie de l'appareil.

    ```python
    time.sleep(10)
    ```

1. Depuis le terminal de VS Code, exécutez la commande suivante pour lancer votre application Python :

    ```sh
    python3 app.py
    ```

    Vous devriez voir les valeurs de température s'afficher dans la console. Utilisez quelque chose pour chauffer le capteur, comme appuyer votre pouce dessus ou utiliser un ventilateur, pour voir les valeurs changer :

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py 
    Temperature 26°C
    Temperature 26°C
    Temperature 28°C
    Temperature 30°C
    Temperature 32°C
    ```

> 💁 Vous pouvez trouver ce code dans le dossier [code-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/pi).

😀 Votre programme de capteur de température a été un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.