# Lire les données GPS - Wio Terminal

Dans cette partie de la leçon, vous allez ajouter un capteur GPS à votre Wio Terminal et lire les valeurs qu'il fournit.

## Matériel

Le Wio Terminal nécessite un capteur GPS.

Le capteur que vous utiliserez est un [capteur Grove GPS Air530](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Ce capteur peut se connecter à plusieurs systèmes GPS pour obtenir une localisation rapide et précise. Le capteur est composé de deux parties : l'électronique principale du capteur et une antenne externe reliée par un fil fin pour capter les ondes radio des satellites.

C'est un capteur UART, il envoie donc les données GPS via UART.

### Connecter le capteur GPS

Le capteur Grove GPS peut être connecté au Wio Terminal.

#### Tâche - connecter le capteur GPS

Connectez le capteur GPS.

![Un capteur Grove GPS](../../../../../translated_images/fr/grove-gps-sensor.247943bf69b03f0d.webp)

1. Insérez une extrémité d'un câble Grove dans le connecteur du capteur GPS. Il ne peut être inséré que dans un seul sens.

1. Avec le Wio Terminal déconnecté de votre ordinateur ou de toute autre source d'alimentation, connectez l'autre extrémité du câble Grove au connecteur Grove situé à gauche sur le Wio Terminal, en regardant l'écran. C'est le connecteur le plus proche du bouton d'alimentation.

    ![Le capteur Grove GPS connecté au connecteur gauche](../../../../../translated_images/fr/wio-gps-sensor.19fd52b81ce58095.webp)

1. Positionnez le capteur GPS de manière à ce que l'antenne attachée ait une visibilité vers le ciel - idéalement près d'une fenêtre ouverte ou à l'extérieur. Il est plus facile d'obtenir un signal clair sans obstacle devant l'antenne.

1. Vous pouvez maintenant connecter le Wio Terminal à votre ordinateur.

1. Le capteur GPS dispose de deux LED : une LED bleue qui clignote lorsque des données sont transmises, et une LED verte qui clignote chaque seconde lorsqu'elle reçoit des données des satellites. Assurez-vous que la LED bleue clignote lorsque vous allumez le Wio Terminal. Après quelques minutes, la LED verte devrait clignoter - si ce n'est pas le cas, vous devrez peut-être repositionner l'antenne.

## Programmer le capteur GPS

Le Wio Terminal peut maintenant être programmé pour utiliser le capteur GPS connecté.

### Tâche - programmer le capteur GPS

Programmez l'appareil.

1. Créez un nouveau projet Wio Terminal en utilisant PlatformIO. Appelez ce projet `gps-sensor`. Ajoutez du code dans la fonction `setup` pour configurer le port série.

1. Ajoutez la directive suivante en haut du fichier `main.cpp`. Cela inclut un fichier d'en-tête avec des fonctions pour configurer le port Grove gauche pour UART.

    ```cpp
    #include <wiring_private.h>
    ```

1. En dessous, ajoutez la ligne de code suivante pour déclarer une connexion au port série UART :

    ```cpp
    static Uart Serial3(&sercom3, PIN_WIRE_SCL, PIN_WIRE_SDA, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    ```

1. Vous devez ajouter du code pour rediriger certains gestionnaires de signaux internes vers ce port série. Ajoutez le code suivant sous la déclaration `Serial3` :

    ```cpp
    void SERCOM3_0_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_1_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_2_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_3_Handler()
    {
        Serial3.IrqHandler();
    }
    ```

1. Dans la fonction `setup`, sous la configuration du port série `Serial`, configurez le port série UART avec le code suivant :

    ```cpp
    Serial3.begin(9600);

    while (!Serial3)
        ; // Wait for Serial3 to be ready

    delay(1000);
    ```

1. Sous ce code dans la fonction `setup`, ajoutez le code suivant pour connecter la broche Grove au port série :

    ```cpp
    pinPeripheral(PIN_WIRE_SCL, PIO_SERCOM_ALT);
    ```

1. Ajoutez la fonction suivante avant la fonction `loop` pour envoyer les données GPS au moniteur série :

    ```cpp
    void printGPSData()
    {
        Serial.println(Serial3.readStringUntil('\n'));
    }
    ```

1. Dans la fonction `loop`, ajoutez le code suivant pour lire les données du port série UART et les afficher dans le moniteur série :

    ```cpp
    while (Serial3.available() > 0)
    {
        printGPSData();
    }
    
    delay(1000);
    ```

    Ce code lit les données du port série UART. La fonction `readStringUntil` lit jusqu'à un caractère terminant, dans ce cas un saut de ligne. Cela permet de lire une phrase complète NMEA (les phrases NMEA se terminent par un caractère de saut de ligne). Tant que des données peuvent être lues du port série UART, elles sont lues et envoyées au moniteur série via la fonction `printGPSData`. Une fois qu'il n'y a plus de données à lire, la boucle attend une seconde (1 000 ms).

1. Compilez et téléchargez le code sur le Wio Terminal.

1. Une fois le code téléchargé, vous pouvez surveiller les données GPS en utilisant le moniteur série.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

> 💁 Vous pouvez trouver ce code dans le dossier [code-gps/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps/wio-terminal).

😀 Votre programme pour le capteur GPS a été un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.