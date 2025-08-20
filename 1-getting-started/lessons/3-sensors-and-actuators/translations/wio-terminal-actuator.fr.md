# Créer une veilleuse - le terminale Wio

Dans cette partie de la leçon, vous ajouterez une LED à votre terminal Wio et l'utiliserez pour créer une veilleuse.

## Matériel

La veilleuse a maintenant besoin d'un actionneur.

L'actionneur est une **LED**, une [diode électroluminescente](https://wikipedia.org/wiki/Light-emitting_diode) qui émet de la lumière lorsqu'elle est traversée par un courant. Il s'agit d'un actionneur numérique qui a deux états : allumé (`on`) et éteint (`off`). L'envoi d'une valeur de 1 allume la LED et de 0 l'éteint. Il s'agit d'un actionneur Grove externe qui doit être connecté au terminal Wio.

La logique de la veilleuse en pseudo-code est la suivante :

```sortie
Vérifier le niveau de lumière.
Si la lumière est inférieure à 300
    Allumer la LED
Sinon
    Eteindre la LED
```

### Connecter la LED

La LED Grove est livrée sous forme de module avec une sélection de LED, ce qui vous permet de choisir la couleur.

#### Tâche - connecter la LED

Connecter la LED.

![Une LED grove](../../../../images/grove-led.png)

1. Choisissez votre LED préférée et insérez les pattes dans les deux trous du module LED.

    Les LEDs sont des diodes électroluminescentes, et les diodes sont des dispositifs électroniques qui ne peuvent transporter le courant que dans un sens. Cela signifie que la LED doit être connectée dans le bon sens, sinon elle ne fonctionnera pas.

    L'une des pattes de la LED est la broche positive, l'autre est la broche négative. La LED n'est pas parfaitement ronde, elle est légèrement plus plate d'un côté. Le côté légèrement plus plat est la broche négative. Lorsque vous connectez la LED au module, assurez-vous que la broche du côté arrondi est connectée à la prise marquée **+** à l'extérieur du module, et que le côté plus plat est connecté à la prise plus proche du milieu du module.

1. Le module LED est doté d'un bouton rotatif qui vous permet de contrôler la luminosité. Pour commencer, réglez-le à fond en le tournant dans le sens inverse des aiguilles d'une montre jusqu'à la butée à l'aide d'un petit tournevis cruciforme.

1. Insérez l'une des extrémités d'un câble Grove dans la prise du module LED. Il ne peut être inséré que dans un seul sens.

1. Le terminal Wio étant déconnecté de votre ordinateur ou de toute autre source d'alimentation, connectez l'autre extrémité du câble Grove à la prise Grove du côté droit du terminal Wio lorsque vous regardez l'écran. Il s'agit de la prise la plus éloignée du bouton d'alimentation.

    > 💁 La prise Grove de droite peut être utilisée avec des capteurs et des actionneurs analogiques ou numériques.La prise de gauche est réservée aux capteurs et actionneurs I<sup>2</sup>C et numériques. L'I<sup>2</sup>C sera abordé dans une leçon ultérieure.

![La LED grove connectée à la prise de droite](../../../../images/wio-led.png)

## Programmer la veilleuse

La veilleuse peut maintenant être programmée à l'aide du capteur de lumière intégré et de la LED Grove.

### Tâche - programmer la veilleuse

Programmer la veilleuse.

1. Ouvrez le projet de veilleuse dans VS Code que vous avez créé dans la partie précédente de ce devoir

1. Ajoutez la ligne suivante à la fin de la fonction `setup` :

    ```cpp
    pinMode(D0, OUTPUT);
    ```

    Cette ligne configure la broche utilisée pour communiquer avec la LED via le port Grove.

    La broche `D0` est la broche numérique pour la prise Grove de droite. Cette broche est réglée sur `OUTPUT`, ce qui signifie qu'elle se connecte à un actionneur et que des données seront écrites sur la broche.

1. Ajoutez le code suivant immédiatement avant le `delay` dans la fonction loop :

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

    Ce code vérifie la valeur `light`. Si cette valeur est inférieure à 300, il envoie une valeur `HIGH` à la broche numérique `D0`. Ce `HIGH` a une valeur de 1, ce qui allume la LED. Si la lumière est supérieure ou égale à 300, une valeur `LOW` de 0 est envoyée à la broche, ce qui éteint la LED.

    > 💁 Lors de l'envoi de valeurs numériques à des actionneurs, une valeur BASSE correspond à 0 V et une valeur HAUTE correspond à la tension maximale de l'appareil. Pour le terminal Wio, la tension HAUTE ("HIGH" en anglais) est de 3,3V.

1. Reconnectez le terminal Wio à votre ordinateur et téléchargez le nouveau code comme vous l'avez fait précédemment.

1. Connectez le moniteur série. Les valeurs lumineuses seront transmises au terminal.

    ```sortie
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

1. Couvrez et découvrez le capteur de lumière. Remarquez que la LED s'allume lorsque le niveau de luminosité est inférieur ou égal à 300, et s'éteint lorsque le niveau de luminosité est supérieur à 300.

![La LED connectée au WIO s'allume et s'éteint en fonction de l'intensité lumineuse.](../../../../images/wio-running-assignment-1-1.gif)

> 💁 Vous trouverez ce code dans le dossier [code-actuator/wio-terminal](../code-actuator/wio-terminal).

😀 Votre programme de veilleuse a été un succès!
