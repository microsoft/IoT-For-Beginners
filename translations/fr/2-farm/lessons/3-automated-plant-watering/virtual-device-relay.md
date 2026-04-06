# Contrôler un relais - Matériel IoT virtuel

Dans cette partie de la leçon, vous allez ajouter un relais à votre appareil IoT virtuel en plus du capteur d'humidité du sol, et le contrôler en fonction du niveau d'humidité du sol.

## Matériel virtuel

L'appareil IoT virtuel utilisera un relais Grove simulé. Cela permet de garder ce laboratoire identique à l'utilisation d'un Raspberry Pi avec un relais Grove physique.

Sur un appareil IoT physique, le relais serait un relais normalement ouvert (ce qui signifie que le circuit de sortie est ouvert ou déconnecté lorsqu'aucun signal n'est envoyé au relais). Un relais de ce type peut gérer des circuits de sortie jusqu'à 250V et 10A.

### Ajouter le relais à CounterFit

Pour utiliser un relais virtuel, vous devez l'ajouter à l'application CounterFit.

#### Tâche

Ajoutez le relais à l'application CounterFit.

1. Ouvrez le projet `soil-moisture-sensor` de la dernière leçon dans VS Code s'il n'est pas déjà ouvert. Vous allez ajouter à ce projet.

1. Assurez-vous que l'application web CounterFit est en cours d'exécution.

1. Créez un relais :

    1. Dans la boîte *Create actuator* du volet *Actuators*, déroulez la boîte *Actuator type* et sélectionnez *Relay*.

    1. Réglez la *Pin* sur *5*.

    1. Sélectionnez le bouton **Add** pour créer le relais sur la broche 5.

    ![Les paramètres du relais](../../../../../translated_images/fr/counterfit-create-relay.fa7c40fd0f2f6afc.webp)

    Le relais sera créé et apparaîtra dans la liste des actionneurs.

    ![Le relais créé](../../../../../translated_images/fr/counterfit-relay.bbf74c1dbdc8b9ac.webp)

## Programmer le relais

L'application du capteur d'humidité du sol peut maintenant être programmée pour utiliser le relais virtuel.

### Tâche

Programmez l'appareil virtuel.

1. Ouvrez le projet `soil-moisture-sensor` de la dernière leçon dans VS Code s'il n'est pas déjà ouvert. Vous allez ajouter à ce projet.

1. Ajoutez le code suivant au fichier `app.py` sous les imports existants :

    ```python
    from counterfit_shims_grove.grove_relay import GroveRelay
    ```

    Cette instruction importe le `GroveRelay` des bibliothèques shim Python Grove pour interagir avec le relais Grove virtuel.

1. Ajoutez le code suivant sous la déclaration de la classe `ADC` pour créer une instance de `GroveRelay` :

    ```python
    relay = GroveRelay(5)
    ```

    Cela crée un relais utilisant la broche **5**, la broche à laquelle vous avez connecté le relais.

1. Pour tester si le relais fonctionne, ajoutez ce qui suit à la boucle `while True:` :

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    Le code allume le relais, attend 0,5 seconde, puis éteint le relais.

1. Exécutez l'application Python. Le relais s'allumera et s'éteindra toutes les 10 secondes, avec un délai de 0,5 seconde entre l'allumage et l'extinction. Vous verrez le relais virtuel dans l'application CounterFit se fermer et s'ouvrir lorsque le relais est activé et désactivé.

    ![Le relais virtuel s'allume et s'éteint](../../../../../images/virtual-relay-turn-on-off.gif)

## Contrôler le relais en fonction de l'humidité du sol

Maintenant que le relais fonctionne, il peut être contrôlé en réponse aux lectures d'humidité du sol.

### Tâche

Contrôlez le relais.

1. Supprimez les 3 lignes de code que vous avez ajoutées pour tester le relais. Remplacez-les par le code suivant à leur place :

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    Ce code vérifie le niveau d'humidité du sol à partir du capteur d'humidité du sol. Si le niveau est supérieur à 450, il allume le relais, et l'éteint s'il descend en dessous de 450.

    > 💁 Rappelez-vous que le capteur capacitif d'humidité du sol lit : plus le niveau d'humidité du sol est bas, plus il y a d'humidité dans le sol, et vice versa.

1. Exécutez l'application Python. Vous verrez le relais s'allumer ou s'éteindre en fonction des niveaux d'humidité du sol. Modifiez les paramètres *Value* ou *Random* du capteur d'humidité du sol pour voir la valeur changer.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Vous pouvez trouver ce code dans le dossier [code-relay/virtual-device](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/virtual-device).

😀 Votre programme de capteur d'humidité du sol virtuel contrôlant un relais a été un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de faire appel à une traduction professionnelle humaine. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.