# Mesurer l'humidité du sol - Matériel IoT Virtuel

Dans cette partie de la leçon, vous allez ajouter un capteur capacitif d'humidité du sol à votre appareil IoT virtuel et lire les valeurs qu'il fournit.

## Matériel Virtuel

L'appareil IoT virtuel utilisera un capteur capacitif d'humidité du sol simulé de type Grove. Cela permet de garder ce laboratoire identique à l'utilisation d'un Raspberry Pi avec un capteur capacitif d'humidité du sol physique.

Dans un appareil IoT physique, le capteur d'humidité du sol serait un capteur capacitif qui mesure l'humidité du sol en détectant la capacitance du sol, une propriété qui change en fonction de l'humidité. Lorsque l'humidité du sol augmente, la tension diminue.

C'est un capteur analogique, il utilise donc un convertisseur analogique-numérique (ADC) simulé sur 10 bits pour rapporter une valeur entre 1 et 1 023.

### Ajouter le capteur d'humidité du sol à CounterFit

Pour utiliser un capteur d'humidité du sol virtuel, vous devez l'ajouter à l'application CounterFit.

#### Tâche - Ajouter le capteur d'humidité du sol à CounterFit

Ajoutez le capteur d'humidité du sol à l'application CounterFit.

1. Créez une nouvelle application Python sur votre ordinateur dans un dossier appelé `soil-moisture-sensor` avec un fichier unique nommé `app.py` et un environnement virtuel Python, puis ajoutez les packages pip de CounterFit.

    > ⚠️ Vous pouvez vous référer [aux instructions pour créer et configurer un projet Python CounterFit dans la leçon 1 si nécessaire](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Assurez-vous que l'application web CounterFit est en cours d'exécution.

1. Créez un capteur d'humidité du sol :

    1. Dans la boîte *Create sensor* du volet *Sensors*, déroulez la liste *Sensor type* et sélectionnez *Soil Moisture*.

    1. Laissez les *Units* sur *NoUnits*.

    1. Assurez-vous que le *Pin* est défini sur *0*.

    1. Sélectionnez le bouton **Add** pour créer le capteur *Soil Moisture* sur le Pin 0.

    ![Les paramètres du capteur d'humidité du sol](../../../../../translated_images/fr/counterfit-create-soil-moisture-sensor.35266135a5e0ae68.webp)

    Le capteur d'humidité du sol sera créé et apparaîtra dans la liste des capteurs.

    ![Le capteur d'humidité du sol créé](../../../../../translated_images/fr/counterfit-soil-moisture-sensor.81742b2de0e9de60.webp)

## Programmer l'application du capteur d'humidité du sol

L'application du capteur d'humidité du sol peut maintenant être programmée en utilisant les capteurs CounterFit.

### Tâche - Programmer l'application du capteur d'humidité du sol

Programmez l'application du capteur d'humidité du sol.

1. Assurez-vous que l'application `soil-moisture-sensor` est ouverte dans VS Code.

1. Ouvrez le fichier `app.py`.

1. Ajoutez le code suivant en haut de `app.py` pour connecter l'application à CounterFit :

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Ajoutez le code suivant au fichier `app.py` pour importer certaines bibliothèques nécessaires :

    ```python
    import time
    from counterfit_shims_grove.adc import ADC
    ```

    L'instruction `import time` importe le module `time` qui sera utilisé plus tard dans cet exercice.

    L'instruction `from counterfit_shims_grove.adc import ADC` importe la classe `ADC` pour interagir avec un convertisseur analogique-numérique virtuel pouvant se connecter à un capteur CounterFit.

1. Ajoutez le code suivant en dessous pour créer une instance de la classe `ADC` :

    ```python
    adc = ADC()
    ```

1. Ajoutez une boucle infinie qui lit les données de cet ADC sur le pin 0 et écrit le résultat dans la console. Cette boucle peut ensuite attendre 10 secondes entre chaque lecture.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)
    
        time.sleep(10)
    ```

1. Depuis l'application CounterFit, modifiez la valeur du capteur d'humidité du sol qui sera lue par l'application. Vous pouvez le faire de deux manières :

    * Entrez un nombre dans la boîte *Value* du capteur d'humidité du sol, puis sélectionnez le bouton **Set**. Le nombre que vous entrez sera la valeur retournée par le capteur.

    * Cochez la case *Random*, entrez une valeur *Min* et une valeur *Max*, puis sélectionnez le bouton **Set**. Chaque fois que le capteur lit une valeur, il lira un nombre aléatoire compris entre *Min* et *Max*.

1. Exécutez l'application Python. Vous verrez les mesures d'humidité du sol écrites dans la console. Modifiez la *Value* ou les paramètres *Random* pour voir la valeur changer.

    ```output
    (.venv) ➜ soil-moisture-sensor $ python app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

> 💁 Vous pouvez trouver ce code dans le dossier [code/virtual-device](../../../../../2-farm/lessons/2-detect-soil-moisture/code/virtual-device).

😀 Votre programme de capteur d'humidité du sol a été un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de faire appel à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.