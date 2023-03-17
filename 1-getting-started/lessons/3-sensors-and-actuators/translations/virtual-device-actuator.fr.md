# Créer une veilleuse - Matériel IoT virtuel

Dans cette partie de la leçon, vous allez ajouter une LED à votre dispositif IoT virtuel et l'utiliser pour créer une veilleuse.

## Matériel virtuel

La veilleuse a besoin d'un actionneur, créé dans l'application CounterFit.

L'actionneur est une **LED**. Dans un dispositif IoT physique, il s'agirait d'une [diode électroluminescente](https://wikipedia.org/wiki/Light-emitting_diode) qui émet de la lumière lorsqu'elle est traversée par un courant. Il s'agit d'un actionneur numérique qui a deux états : allumé (`on`) et éteint (`off`). L'envoi d'une valeur de 1 allume la diode et celle de 0 l'éteint.

La logique de la veilleuse en pseudo-code est la suivante :

```sortie
Vérifier le niveau de lumière.
Si la lumière est inférieure à 300
    Allumer la LED
Sinon
    Eteindre la LED
```

### Ajouter l'actionneur à CounterFit

Pour utiliser une LED virtuelle, vous devez l'ajouter à l'application CounterFit.

#### Tâche - ajouter l'actionneur à CounterFit

Ajoutez la LED à l'application CounterFit.

1. Assurez-vous que l'application web CounterFit est en cours d'exécution depuis la partie précédente de ce travail. Si ce n'est pas le cas, démarrez-la et ajoutez à nouveau le capteur de lumière.

1. Créez une LED :

    1. Dans la case *Créer un actionneur* du volet *Actionneur*, dérouler la case *Type d'actionneur* et sélectionner *LED*.

    1. Réglez la *broche* sur *5*

    1. Sélectionnez le bouton **Ajouter** pour créer la LED sur la broche 5.

    ![Les paramètres de la LED](../../../../images/counterfit-create-led.png)

    La LED sera créée et apparaîtra dans la liste des actionneurs.

    ![La LED créée](../../../../images/counterfit-led.png)

    Une fois la LED créée, vous pouvez changer sa couleur en utilisant le sélecteur *Color*. Sélectionnez le bouton **Set** pour modifier la couleur après l'avoir sélectionnée.

### Programmer la veilleuse

La veilleuse peut maintenant être programmée à l'aide du capteur de lumière et de la LED CounterFit.

#### Tâche - programmer la veilleuse

Programmez la veilleuse.

1. Ouvrez le projet de veilleuse dans VS Code que vous avez créé dans la partie précédente de ce travail. Fermez et recréez le terminal pour vous assurer qu'il fonctionne en utilisant l'environnement virtuel si nécessaire.

1. Ouvrez le fichier `app.py`

1. Ajoutez le code suivant au fichier `app.py` pour vous connecter à l'importation d'une bibliothèque requise. Ceci doit être ajouté en haut, en dessous des autres lignes `import`.

    ```python
    from counterfit_shims_grove.grove_led import GroveLed
    ```

    L'instruction `from counterfit_shims_grove.grove_led import GroveLed` importe la `GroveLed` des bibliothèques Python de CounterFit Grove shim. Cette bibliothèque contient du code pour interagir avec une LED créée dans l'application CounterFit.

1. Ajoutez le code suivant après la déclaration `light_sensor` pour créer une instance de la classe qui gère la LED :

    ```python
    led = GroveLed(5)
    ```

    La ligne `led = GroveLed(5)` crée une instance de la classe `GroveLed` se connectant à la broche **5** - la broche CounterFit Grove à laquelle la LED est connectée.

1. Ajoutez une vérification à l'intérieur de la boucle `while`, et avant le `time.sleep` pour vérifier les niveaux de lumière et allumer ou éteindre la LED :

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Ce code vérifie la valeur de `light`. Si cette valeur est inférieure à 300, il appelle la méthode `on` de la classe `GroveLed` qui envoie une valeur numérique de 1 à la LED, l'allumant ainsi. Si la valeur de la lumière est supérieure ou égale à 300, elle appelle la méthode `off`, qui envoie une valeur numérique de 0 à la LED, l'éteignant.

    > 💁 Ce code doit être indenté au même niveau que la ligne `print('Light level:', light)` pour être à l'intérieur de la boucle while!

1. Depuis le terminal VS Code, exécutez ce qui suit pour lancer votre application Python :

    ```sh
    python3 app.py
    ```

    Les valeurs de lumière seront affichées sur la console.

    ```sortie
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

1. Modifiez les paramètres *Value* ou *Random* pour faire varier le niveau d'éclairage au-dessus et au-dessous de 300. La LED s'allume et s'éteint.

![La LED dans l'application CounterFit s'allume et s'éteint lorsque le niveau de lumière change](../../../../images/virtual-device-running-assignment-1-1.gif)

> 💁 Vous trouverez ce code dans le dossier [code-actuator/virtual-device](../code-actuator/virtual-device).

😀 Votre programme de veilleuse a été réalisé avec succès!
