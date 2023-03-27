# Créer une veilleuse - Matériel IoT virtuel

Dans cette partie de la leçon, vous allez ajouter un capteur de lumière à votre dispositif IoT virtuel.

## Matériel virtuel

La veilleuse a besoin d'un actionneur, créé dans l'application CounterFit.

Le capteur est un **capteur de lumière**. Dans un dispositif IoT physique, il s'agirait d'une [photodiode](https://wikipedia.org/wiki/Photodiode) qui convertit la lumière en un signal électrique. Les capteurs de lumière sont des capteurs analogiques qui envoient une valeur entière indiquant une quantité relative de lumière, qui ne correspond à aucune unité de mesure standard telle que le [lux](https://wikipedia.org/wiki/Lux).

### Ajouter les capteurs à CounterFit

Pour utiliser un capteur de lumière virtuel, vous devez l'ajouter à l'application CounterFit.

#### Tâche - ajouter les capteurs à CounterFit

Ajoutez le capteur de lumière à l'application CounterFit.

1. Assurez-vous que l'application web CounterFit est en cours d'exécution depuis la partie précédente de ce travail. Si ce n'est pas le cas, démarrez-la.

1. Créez un capteur de lumière :

    1. Dans la case *Create sensor* du volet *Sensors*, déroulez la case *Sensor type* et sélectionnez *Light*.

    1. Laissez les *Unités* (*Units* en anglais) réglées sur *NoUnits*

    1. Assurez-vous que l'option *Pin* est réglée sur *0*.

    1. Sélectionnez le bouton **Add** pour créer le capteur de lumière sur la broche 0.

    ![Les paramètres du capteur de lumière](../../../../images/counterfit-create-light-sensor.png)

    Le capteur de lumière sera créé et apparaîtra dans la liste des capteurs.

    ![Le capteur de lumière créé](../../../../images/counterfit-light-sensor.png)

## Programmer le capteur de lumière

L'appareil peut maintenant être programmé pour utiliser le capteur de lumière intégré.

### Tâche - programmer le capteur de lumière

Programmez l'appareil.

1. Ouvrez le projet nightlight dans VS Code que vous avez créé dans la partie précédente de ce travail. Fermez et recréez le terminal pour vous assurer qu'il fonctionne en utilisant l'environnement virtuel si nécessaire.

1. Ouvrez le fichier `app.py`

1. Ajouter le code suivant au début du fichier `app.py` avec le reste des déclarations `import` pour se connecter à l'importation de certaines bibliothèques requises :

    ```python
    import time
    from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    L'instruction `import time` importe le module Python `time` qui sera utilisé plus tard dans ce travail.

    L'instruction `from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor` importe le `GroveLightSensor` des bibliothèques Python CounterFit Grove shim. Cette bibliothèque contient du code pour interagir avec un capteur de lumière créé dans l'application CounterFit.

1. Ajoutez le code suivant au bas du fichier pour créer des instances de classes qui gèrent le capteur de lumière :

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    La ligne `light_sensor = GroveLightSensor(0)` crée une instance de la classe `GroveLightSensor` se connectant au pin **0** - le pin du CounterFit Grove auquel le capteur de lumière est connecté.

1. Ajoutez une boucle infinie après le code ci-dessus pour interroger la valeur du capteur de lumière et l'imprimer sur la console :

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Ceci permet de lire le niveau de lumière actuel en utilisant la propriété `light` de la classe `GroveLightSensor`. Cette propriété lit la valeur analogique de la broche. Cette valeur est ensuite imprimée sur la console.

1. Ajoutez une petite mise en veille d'une seconde à la fin de la boucle `while` car les niveaux de lumière n'ont pas besoin d'être vérifiés continuellement. Une mise en veille réduit la consommation d'énergie de l'appareil.

    ```python
    time.sleep(1)
    ```

1. Depuis le terminal VS Code, exécutez les commandes suivantes pour lancer votre application Python :

    ```sh
    python3 app.py
    ```

    Les valeurs lumineuses seront affichées sur la console. Initialement, cette valeur sera de 0.

1. Depuis l'application CounterFit, changez la valeur du capteur de lumière qui sera lue par l'application. Vous pouvez le faire de deux façons :

    * Saisissez un nombre dans la case *Value* du capteur de lumière, puis sélectionnez le bouton **Set**. Le nombre que vous saisissez sera la valeur renvoyée par le capteur.

    * Cochez la case *Aléatoire* et entrez une valeur *Min* et *Max*, puis cliquez sur le bouton **Set**. Chaque fois que le capteur lira une valeur, il lira un nombre aléatoire entre *Min* et *Max*.

    Les valeurs que vous avez définies seront affichées sur la console. Modifiez les paramètres *Value* ou *Random* pour modifier la valeur.

    ```sortie
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

> 💁 Vous trouverez ce code dans le dossier [code-sensor/virtual-device](../code-sensor/virtual-device).

😀 Votre programme de veilleuse a été un succès!
