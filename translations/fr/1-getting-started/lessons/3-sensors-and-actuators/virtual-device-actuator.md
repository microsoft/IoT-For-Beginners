# Construire une veilleuse - Matériel IoT Virtuel

Dans cette partie de la leçon, vous allez ajouter une LED à votre appareil IoT virtuel et l'utiliser pour créer une veilleuse.

## Matériel Virtuel

La veilleuse nécessite un actionneur, créé dans l'application CounterFit.

L'actionneur est une **LED**. Dans un appareil IoT physique, il s'agirait d'une [diode électroluminescente](https://wikipedia.org/wiki/Diode_%C3%A9lectroluminescente) qui émet de la lumière lorsqu'un courant la traverse. C'est un actionneur numérique qui possède deux états : allumé et éteint. Envoyer une valeur de 1 allume la LED, et une valeur de 0 l'éteint.

La logique de la veilleuse en pseudo-code est :

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Ajouter l'actionneur à CounterFit

Pour utiliser une LED virtuelle, vous devez l'ajouter à l'application CounterFit.

#### Tâche - ajouter l'actionneur à CounterFit

Ajoutez la LED à l'application CounterFit.

1. Assurez-vous que l'application web CounterFit fonctionne depuis la partie précédente de cet exercice. Si ce n'est pas le cas, démarrez-la et ré-ajoutez le capteur de lumière.

1. Créez une LED :

    1. Dans la boîte *Créer un actionneur* du volet *Actionneur*, déroulez la boîte *Type d'actionneur* et sélectionnez *LED*.

    1. Réglez la *Broche* sur *5*.

    1. Sélectionnez le bouton **Ajouter** pour créer la LED sur la broche 5.

    ![Les paramètres de la LED](../../../../../translated_images/fr/counterfit-create-led.ba9db1c9b8c622a6.webp)

    La LED sera créée et apparaîtra dans la liste des actionneurs.

    ![La LED créée](../../../../../translated_images/fr/counterfit-led.c0ab02de6d256ad8.webp)

    Une fois la LED créée, vous pouvez changer sa couleur en utilisant le sélecteur *Couleur*. Sélectionnez le bouton **Définir** pour changer la couleur après l'avoir choisie.

### Programmer la veilleuse

La veilleuse peut maintenant être programmée en utilisant le capteur de lumière et la LED de CounterFit.

#### Tâche - programmer la veilleuse

Programmez la veilleuse.

1. Ouvrez le projet de veilleuse dans VS Code que vous avez créé dans la partie précédente de cet exercice. Arrêtez et recréez le terminal pour vous assurer qu'il fonctionne avec l'environnement virtuel si nécessaire.

1. Ouvrez le fichier `app.py`.

1. Ajoutez le code suivant au fichier `app.py` pour importer une bibliothèque requise. Cela doit être ajouté en haut, sous les autres lignes `import`.

    ```python
    from counterfit_shims_grove.grove_led import GroveLed
    ```

    L'instruction `from counterfit_shims_grove.grove_led import GroveLed` importe la classe `GroveLed` des bibliothèques Python CounterFit Grove shim. Cette bibliothèque contient du code pour interagir avec une LED créée dans l'application CounterFit.

1. Ajoutez le code suivant après la déclaration `light_sensor` pour créer une instance de la classe qui gère la LED :

    ```python
    led = GroveLed(5)
    ```

    La ligne `led = GroveLed(5)` crée une instance de la classe `GroveLed` connectée à la broche **5** - la broche Grove de CounterFit à laquelle la LED est connectée.

1. Ajoutez une vérification à l'intérieur de la boucle `while`, et avant le `time.sleep`, pour vérifier les niveaux de lumière et allumer ou éteindre la LED :

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Ce code vérifie la valeur `light`. Si celle-ci est inférieure à 300, il appelle la méthode `on` de la classe `GroveLed`, qui envoie une valeur numérique de 1 à la LED, l'allumant. Si la valeur de lumière est supérieure ou égale à 300, il appelle la méthode `off`, envoyant une valeur numérique de 0 à la LED, l'éteignant.

    > 💁 Ce code doit être indenté au même niveau que la ligne `print('Light level:', light)` pour être à l'intérieur de la boucle while !

1. Depuis le terminal de VS Code, exécutez la commande suivante pour lancer votre application Python :

    ```sh
    python3 app.py
    ```

    Les valeurs de lumière seront affichées dans la console.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

1. Modifiez les paramètres *Valeur* ou *Aléatoire* pour faire varier le niveau de lumière au-dessus et en dessous de 300. La LED s'allumera et s'éteindra.

![La LED dans l'application CounterFit s'allume et s'éteint en fonction des variations du niveau de lumière](../../../../../images/virtual-device-running-assignment-1-1.gif)

> 💁 Vous pouvez trouver ce code dans le dossier [code-actuator/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/virtual-device).

😀 Votre programme de veilleuse est un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de faire appel à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.