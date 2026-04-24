# Contrôler un relais - Raspberry Pi

Dans cette partie de la leçon, vous allez ajouter un relais à votre Raspberry Pi en plus du capteur d'humidité du sol, et le contrôler en fonction du niveau d'humidité du sol.

## Matériel

Le Raspberry Pi nécessite un relais.

Le relais que vous utiliserez est un [relais Grove](https://www.seeedstudio.com/Grove-Relay.html), un relais normalement ouvert (ce qui signifie que le circuit de sortie est ouvert ou déconnecté lorsqu'aucun signal n'est envoyé au relais) qui peut gérer des circuits de sortie jusqu'à 250V et 10A.

C'est un actionneur numérique, il se connecte donc à une broche numérique sur le Grove Base Hat.

### Connecter le relais

Le relais Grove peut être connecté au Raspberry Pi.

#### Tâche

Connectez le relais.

![Un relais Grove](../../../../../translated_images/fr/grove-relay.d426958ca210fbd0.webp)

1. Insérez une extrémité d'un câble Grove dans la prise du relais. Il ne peut être inséré que dans un seul sens.

1. Avec le Raspberry Pi éteint, connectez l'autre extrémité du câble Grove à la prise numérique marquée **D5** sur le Grove Base Hat attaché au Pi. Cette prise est la deuxième à partir de la gauche, sur la rangée de prises à côté des broches GPIO. Laissez le capteur d'humidité du sol connecté à la prise **A0**.

![Le relais Grove connecté à la prise D5, et le capteur d'humidité du sol connecté à la prise A0](../../../../../translated_images/fr/pi-relay-and-soil-moisture-sensor.02f3198975b8c53e.webp)

1. Insérez le capteur d'humidité du sol dans le sol, s'il n'est pas déjà en place depuis la leçon précédente.

## Programmer le relais

Le Raspberry Pi peut maintenant être programmé pour utiliser le relais connecté.

### Tâche

Programmez l'appareil.

1. Allumez le Pi et attendez qu'il démarre.

1. Ouvrez le projet `soil-moisture-sensor` de la leçon précédente dans VS Code s'il n'est pas déjà ouvert. Vous allez ajouter à ce projet.

1. Ajoutez le code suivant au fichier `app.py` sous les imports existants :

    ```python
    from grove.grove_relay import GroveRelay
    ```

    Cette instruction importe le `GroveRelay` des bibliothèques Python Grove pour interagir avec le relais Grove.

1. Ajoutez le code suivant sous la déclaration de la classe `ADC` pour créer une instance de `GroveRelay` :

    ```python
    relay = GroveRelay(5)
    ```

    Cela crée un relais utilisant la broche **D5**, la broche numérique à laquelle vous avez connecté le relais.

1. Pour tester si le relais fonctionne, ajoutez ce qui suit à la boucle `while True:` :

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    Le code allume le relais, attend 0,5 seconde, puis éteint le relais.

1. Exécutez l'application Python. Le relais s'allumera et s'éteindra toutes les 10 secondes, avec un délai de 0,5 seconde entre l'allumage et l'extinction. Vous entendrez le relais cliquer pour s'allumer, puis cliquer pour s'éteindre. Une LED sur la carte Grove s'allumera lorsque le relais est activé, puis s'éteindra lorsqu'il est désactivé.

    ![Le relais s'allume et s'éteint](../../../../../images/relay-turn-on-off.gif)

## Contrôler le relais en fonction de l'humidité du sol

Maintenant que le relais fonctionne, il peut être contrôlé en réponse aux lectures d'humidité du sol.

### Tâche

Contrôlez le relais.

1. Supprimez les 3 lignes de code que vous avez ajoutées pour tester le relais. Remplacez-les par le code suivant :

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    Ce code vérifie le niveau d'humidité du sol à partir du capteur d'humidité du sol. S'il est supérieur à 450, il active le relais, et le désactive lorsqu'il descend en dessous de 450.

    > 💁 Rappelez-vous que le capteur capacitif d'humidité du sol lit : plus le niveau d'humidité du sol est bas, plus il y a d'humidité dans le sol, et vice versa.

1. Exécutez l'application Python. Vous verrez le relais s'allumer ou s'éteindre en fonction du niveau d'humidité du sol. Essayez dans un sol sec, puis ajoutez de l'eau.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Vous pouvez trouver ce code dans le dossier [code-relay/pi](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/pi).

😀 Votre programme de contrôle de relais par le capteur d'humidité du sol est un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction professionnelle réalisée par un humain. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.