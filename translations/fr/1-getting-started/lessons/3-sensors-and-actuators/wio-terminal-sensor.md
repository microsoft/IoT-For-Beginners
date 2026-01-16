<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7f4ad0ef54f248b85b92187c94cf9dcb",
  "translation_date": "2025-08-24T23:25:45+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-sensor.md",
  "language_code": "fr"
}
-->
# Ajouter un capteur - Wio Terminal

Dans cette partie de la leçon, vous allez utiliser le capteur de lumière intégré à votre Wio Terminal.

## Matériel

Le capteur utilisé dans cette leçon est un **capteur de lumière** qui utilise une [photodiode](https://wikipedia.org/wiki/Photodiode) pour convertir la lumière en signal électrique. Il s'agit d'un capteur analogique qui envoie une valeur entière entre 0 et 1 023, indiquant une quantité relative de lumière qui ne correspond à aucune unité de mesure standard comme le [lux](https://wikipedia.org/wiki/Lux).

Le capteur de lumière est intégré au Wio Terminal et est visible à travers la fenêtre en plastique transparent à l'arrière.

![Le capteur de lumière à l'arrière du Wio Terminal](../../../../../translated_images/fr/wio-light-sensor.b1f529f3c95f5165.webp)

## Programmer le capteur de lumière

L'appareil peut maintenant être programmé pour utiliser le capteur de lumière intégré.

### Tâche

Programmez l'appareil.

1. Ouvrez le projet de veilleuse dans VS Code que vous avez créé dans la partie précédente de cet exercice.

1. Ajoutez la ligne suivante à la fin de la fonction `setup` :

    ```cpp
    pinMode(WIO_LIGHT, INPUT);
    ```

    Cette ligne configure les broches utilisées pour communiquer avec le matériel du capteur.

    La broche `WIO_LIGHT` correspond au numéro de la broche GPIO connectée au capteur de lumière intégré. Cette broche est définie comme `INPUT`, ce qui signifie qu'elle est connectée à un capteur et que des données seront lues à partir de cette broche.

1. Supprimez le contenu de la fonction `loop`.

1. Ajoutez le code suivant à la fonction `loop`, désormais vide.

    ```cpp
    int light = analogRead(WIO_LIGHT);
    Serial.print("Light value: ");
    Serial.println(light);
    ```

    Ce code lit une valeur analogique à partir de la broche `WIO_LIGHT`. Cela permet de récupérer une valeur entre 0 et 1 023 provenant du capteur de lumière intégré. Cette valeur est ensuite envoyée au port série, ce qui vous permet de la lire dans le moniteur série lorsque ce code est exécuté. `Serial.print` écrit le texte sans ajouter de saut de ligne à la fin, donc chaque ligne commencera par `Light value:` et se terminera par la valeur réelle de la lumière.

1. Ajoutez un petit délai d'une seconde (1 000 ms) à la fin de la fonction `loop`, car les niveaux de lumière n'ont pas besoin d'être vérifiés en continu. Un délai réduit la consommation d'énergie de l'appareil.

    ```cpp
    delay(1000);
    ```

1. Reconnectez le Wio Terminal à votre ordinateur et téléchargez le nouveau code comme vous l'avez fait précédemment.

1. Connectez le moniteur série. Les valeurs de lumière seront affichées dans le terminal. Couvrez et découvrez le capteur de lumière à l'arrière du Wio Terminal, et les valeurs changeront.

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

> 💁 Vous pouvez trouver ce code dans le dossier [code-sensor/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/wio-terminal).

😀 Ajouter un capteur à votre programme de veilleuse a été un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.