# Ajouter un capteur - le terminal Wio

Dans cette partie de la leçon, vous utiliserez le capteur de lumière sur votre terminal Wio.

## Matériel

Le capteur de cette leçon est un **capteur de lumière** qui utilise une [photodiode](https://fr.wikipedia.org/wiki/Photodiode) pour convertir la lumière en un signal électrique. Il s'agit d'un capteur analogique qui envoie une valeur entière comprise entre 0 et 1023 indiquant une quantité relative de lumière qui ne correspond à aucune unité de mesure standard telle que le [lux](https://wikipedia.org/wiki/Lux).

Le capteur de lumière est intégré au terminal Wio et est visible à travers la fenêtre en plastique transparent située à l'arrière.

![Le capteur de lumière au dos du terminal Wio](../../../../images/wio-light-sensor.png)

## Programmer le capteur de lumière

L'appareil peut maintenant être programmé pour utiliser le capteur de lumière intégré.

### Tâche

Programmez l'appareil.

1. Ouvrez le projet nightlight dans VS Code que vous avez créé dans la partie précédente de ce travail.

1. Ajoutez la ligne suivante à la fin de la fonction `setup` :

    ```cpp
    pinMode(WIO_LIGHT, INPUT);
    ```

    Cette ligne configure les broches utilisées pour communiquer avec le capteur.

    La broche `WIO_LIGHT` est le numéro de la broche GPIO connectée au capteur de lumière embarqué. Cette broche est réglée sur `INPUT`, ce qui signifie qu'elle se connecte à un capteur et que les données seront lues à partir de la broche.

1. Effacez le contenu de la fonction `loop`.

1. Ajoutez le code suivant à la fonction `loop` maintenant vide.

    ```cpp
    int light = analogRead(WIO_LIGHT);
    Serial.print("Light value: ");
    Serial.println(light);
    ```

    Ce code lit une valeur analogique sur la broche `WIO_LIGHT`. Il lit une valeur comprise entre 0 et 1023 à partir du capteur de lumière embarqué. Cette valeur est ensuite envoyée au port série afin que vous puissiez la lire dans le Serial Monitor lorsque ce code est exécuté. `Serial.print` écrit le texte sans nouvelle ligne à la fin, de sorte que chaque ligne commence par `Light value:` et se termine par la valeur réelle de la lumière.

1. Ajoutez un petit délai d'une seconde (1000 ms) à la fin de la `boucle` (`loop` en anglais), car les niveaux de lumière n'ont pas besoin d'être vérifiés en permanence. Un délai réduit la consommation d'énergie de l'appareil.

    ```cpp
    delay(1000);
    ```

1. Reconnectez le terminal Wio à votre ordinateur et téléchargez le nouveau code comme vous l'avez fait précédemment.

1. Connectez le moniteur série. Des valeurs lumineuses seront émises vers le terminal. Couvrez et découvrez le capteur de lumière à l'arrière du terminal Wio, et les valeurs changeront.

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

> 💁 Vous trouverez ce code dans le dossier [code-sensor/wio-terminal](../code-sensor/wio-terminal).

😀 L'ajout d'un capteur à votre programme de veilleuses a été un succès!
