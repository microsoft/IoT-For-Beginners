# Construire une veilleuse - Wio Terminal

Dans cette partie de la leçon, vous allez ajouter une LED à votre Wio Terminal et l'utiliser pour créer une veilleuse.

## Matériel

La veilleuse a maintenant besoin d'un actionneur.

L'actionneur est une **LED**, une [diode électroluminescente](https://wikipedia.org/wiki/Diode_%C3%A9lectroluminescente) qui émet de la lumière lorsqu'un courant la traverse. C'est un actionneur numérique qui a deux états : allumé et éteint. Envoyer une valeur de 1 allume la LED, et une valeur de 0 l'éteint. Il s'agit d'un actionneur externe Grove qui doit être connecté au Wio Terminal.

La logique de la veilleuse en pseudo-code est la suivante :

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Connecter la LED

La LED Grove est fournie sous forme de module avec une sélection de LEDs, vous permettant de choisir la couleur.

#### Tâche - connecter la LED

Connectez la LED.

![Une LED Grove](../../../../../translated_images/fr/grove-led.6c853be93f473cf2.webp)

1. Choisissez votre LED préférée et insérez ses pattes dans les deux trous du module LED.

    Les LEDs sont des diodes électroluminescentes, et les diodes sont des dispositifs électroniques qui ne laissent passer le courant que dans un seul sens. Cela signifie que la LED doit être connectée dans le bon sens, sinon elle ne fonctionnera pas.

    Une des pattes de la LED est la broche positive, l'autre est la broche négative. La LED n'est pas parfaitement ronde et est légèrement plus plate d'un côté. Le côté légèrement plus plat correspond à la broche négative. Lorsque vous connectez la LED au module, assurez-vous que la patte du côté arrondi est connectée à la prise marquée **+** à l'extérieur du module, et que le côté plat est connecté à la prise plus proche du centre du module.

1. Le module LED dispose d'un bouton rotatif qui permet de contrôler la luminosité. Tournez-le complètement vers le haut pour commencer, en le faisant pivoter dans le sens antihoraire autant que possible à l'aide d'un petit tournevis cruciforme.

1. Insérez une extrémité d'un câble Grove dans la prise du module LED. Il ne s'insérera que dans un seul sens.

1. Avec le Wio Terminal déconnecté de votre ordinateur ou d'une autre source d'alimentation, connectez l'autre extrémité du câble Grove à la prise Grove située à droite du Wio Terminal lorsque vous regardez l'écran. C'est la prise la plus éloignée du bouton d'alimentation.

    > 💁 La prise Grove de droite peut être utilisée avec des capteurs et actionneurs analogiques ou numériques. La prise de gauche est réservée aux capteurs et actionneurs numériques uniquement. C

![La LED Grove connectée à la prise de droite](../../../../../translated_images/fr/wio-led.265a1897e72d7f21.webp)

## Programmer la veilleuse

La veilleuse peut maintenant être programmée en utilisant le capteur de lumière intégré et la LED Grove.

### Tâche - programmer la veilleuse

Programmez la veilleuse.

1. Ouvrez le projet de veilleuse dans VS Code que vous avez créé dans la partie précédente de cet exercice.

1. Ajoutez la ligne suivante à la fin de la fonction `setup` :

    ```cpp
    pinMode(D0, OUTPUT);
    ```

    Cette ligne configure la broche utilisée pour communiquer avec la LED via le port Grove.

    La broche `D0` est la broche numérique pour la prise Grove de droite. Cette broche est définie sur `OUTPUT`, ce qui signifie qu'elle est connectée à un actionneur et que des données seront écrites sur cette broche.

1. Ajoutez le code suivant juste avant le `delay` dans la fonction loop :

    ```cpp
    if (light < 300)
    {
        digitalWrite(D0, HIGH);
    }
    else
    {
        digitalWrite(D0, LOW);
    }
    ```

    Ce code vérifie la valeur `light`. Si cette valeur est inférieure à 300, il envoie une valeur `HIGH` à la broche numérique `D0`. Cette valeur `HIGH` correspond à 1, ce qui allume la LED. Si la lumière est supérieure ou égale à 300, une valeur `LOW` de 0 est envoyée à la broche, éteignant ainsi la LED.

    > 💁 Lors de l'envoi de valeurs numériques aux actionneurs, une valeur LOW correspond à 0V, et une valeur HIGH correspond à la tension maximale pour l'appareil. Pour le Wio Terminal, la tension HIGH est de 3,3V.

1. Reconnectez le Wio Terminal à votre ordinateur et téléchargez le nouveau code comme vous l'avez fait précédemment.

1. Connectez le moniteur série. Les valeurs de lumière seront affichées dans le terminal.

    ```output
    > Executing task: platformio device monitor <

    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Light value: 4
    Light value: 5
    Light value: 4
    Light value: 158
    Light value: 343
    Light value: 348
    Light value: 344
    ```

1. Couvrez et découvrez le capteur de lumière. Remarquez comment la LED s'allume si le niveau de lumière est de 300 ou moins, et s'éteint lorsque le niveau de lumière est supérieur à 300.

![La LED connectée au WIO s'allume et s'éteint en fonction des variations de lumière](../../../../../images/wio-running-assignment-1-1.gif)

> 💁 Vous pouvez trouver ce code dans le dossier [code-actuator/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/wio-terminal).

😀 Votre programme de veilleuse est un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction professionnelle réalisée par un humain. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.