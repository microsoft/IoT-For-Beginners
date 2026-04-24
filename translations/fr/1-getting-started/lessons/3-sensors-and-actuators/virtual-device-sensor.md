# Construire une veilleuse - Matériel IoT virtuel

Dans cette partie de la leçon, vous allez ajouter un capteur de lumière à votre appareil IoT virtuel.

## Matériel virtuel

La veilleuse a besoin d'un capteur, créé dans l'application CounterFit.

Le capteur est un **capteur de lumière**. Dans un appareil IoT physique, il s'agirait d'une [photodiode](https://wikipedia.org/wiki/Photodiode) qui convertit la lumière en un signal électrique. Les capteurs de lumière sont des capteurs analogiques qui envoient une valeur entière indiquant une quantité relative de lumière, sans correspondre à une unité de mesure standard comme le [lux](https://wikipedia.org/wiki/Lux).

### Ajouter les capteurs à CounterFit

Pour utiliser un capteur de lumière virtuel, vous devez l'ajouter à l'application CounterFit.

#### Tâche - ajouter les capteurs à CounterFit

Ajoutez le capteur de lumière à l'application CounterFit.

1. Assurez-vous que l'application web CounterFit est en cours d'exécution depuis la partie précédente de cet exercice. Sinon, démarrez-la.

1. Créez un capteur de lumière :

    1. Dans la boîte *Create sensor* du volet *Sensors*, déroulez la liste *Sensor type* et sélectionnez *Light*.

    1. Laissez les *Units* sur *NoUnits*.

    1. Assurez-vous que le *Pin* est réglé sur *0*.

    1. Sélectionnez le bouton **Add** pour créer le capteur de lumière sur le Pin 0.

    ![Les paramètres du capteur de lumière](../../../../../translated_images/fr/counterfit-create-light-sensor.9f36a5e0d4458d8d.webp)

    Le capteur de lumière sera créé et apparaîtra dans la liste des capteurs.

    ![Le capteur de lumière créé](../../../../../translated_images/fr/counterfit-light-sensor.5d0f5584df56b90f.webp)

## Programmer le capteur de lumière

L'appareil peut maintenant être programmé pour utiliser le capteur de lumière intégré.

### Tâche - programmer le capteur de lumière

Programmez l'appareil.

1. Ouvrez le projet de veilleuse dans VS Code que vous avez créé dans la partie précédente de cet exercice. Tuez et recréez le terminal pour vous assurer qu'il fonctionne avec l'environnement virtuel si nécessaire.

1. Ouvrez le fichier `app.py`.

1. Ajoutez le code suivant en haut du fichier `app.py` avec les autres déclarations `import` pour importer des bibliothèques nécessaires :

    ```python
    import time
    from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    La déclaration `import time` importe le module Python `time` qui sera utilisé plus tard dans cet exercice.

    La déclaration `from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor` importe le `GroveLightSensor` des bibliothèques Python CounterFit Grove shim. Cette bibliothèque contient le code pour interagir avec un capteur de lumière créé dans l'application CounterFit.

1. Ajoutez le code suivant en bas du fichier pour créer des instances des classes qui gèrent le capteur de lumière :

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    La ligne `light_sensor = GroveLightSensor(0)` crée une instance de la classe `GroveLightSensor` connectée au pin **0** - le pin Grove de CounterFit auquel le capteur de lumière est connecté.

1. Ajoutez une boucle infinie après le code ci-dessus pour interroger la valeur du capteur de lumière et l'afficher dans la console :

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Cela lira le niveau de lumière actuel en utilisant la propriété `light` de la classe `GroveLightSensor`. Cette propriété lit la valeur analogique du pin. Cette valeur est ensuite affichée dans la console.

1. Ajoutez une petite pause d'une seconde à la fin de la boucle `while`, car les niveaux de lumière n'ont pas besoin d'être vérifiés en continu. Une pause réduit la consommation d'énergie de l'appareil.

    ```python
    time.sleep(1)
    ```

1. Depuis le terminal de VS Code, exécutez la commande suivante pour lancer votre application Python :

    ```sh
    python3 app.py
    ```

    Les valeurs de lumière seront affichées dans la console. Initialement, cette valeur sera 0.

1. Depuis l'application CounterFit, modifiez la valeur du capteur de lumière qui sera lue par l'application. Vous pouvez le faire de deux manières :

    * Entrez un nombre dans la boîte *Value* du capteur de lumière, puis sélectionnez le bouton **Set**. Le nombre que vous entrez sera la valeur renvoyée par le capteur.

    * Cochez la case *Random*, entrez une valeur *Min* et une valeur *Max*, puis sélectionnez le bouton **Set**. Chaque fois que le capteur lit une valeur, il lira un nombre aléatoire compris entre *Min* et *Max*.

    Les valeurs que vous définissez seront affichées dans la console. Modifiez la *Value* ou les paramètres *Random* pour faire varier la valeur.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

> 💁 Vous pouvez trouver ce code dans le dossier [code-sensor/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/virtual-device).

😀 Votre programme de veilleuse a été un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de faire appel à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.