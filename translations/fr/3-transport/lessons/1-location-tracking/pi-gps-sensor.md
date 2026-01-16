<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3b2448c7ab4e9673e77e35a50c5e350d",
  "translation_date": "2025-08-25T00:53:26+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/pi-gps-sensor.md",
  "language_code": "fr"
}
-->
# Lire les données GPS - Raspberry Pi

Dans cette partie de la leçon, vous allez ajouter un capteur GPS à votre Raspberry Pi et lire les valeurs qu'il fournit.

## Matériel

Le Raspberry Pi nécessite un capteur GPS.

Le capteur que vous utiliserez est un [capteur Grove GPS Air530](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Ce capteur peut se connecter à plusieurs systèmes GPS pour obtenir une localisation rapide et précise. Le capteur est composé de deux parties : l'électronique principale du capteur et une antenne externe reliée par un fil fin pour capter les ondes radio des satellites.

C'est un capteur UART, il envoie donc les données GPS via UART.

## Connecter le capteur GPS

Le capteur GPS Grove peut être connecté au Raspberry Pi.

### Tâche - connecter le capteur GPS

Connectez le capteur GPS.

![Un capteur GPS Grove](../../../../../translated_images/fr/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.png)

1. Insérez une extrémité d'un câble Grove dans la prise du capteur GPS. Il ne peut être inséré que dans un seul sens.

1. Avec le Raspberry Pi éteint, connectez l'autre extrémité du câble Grove à la prise UART marquée **UART** sur le Grove Base Hat attaché au Pi. Cette prise se trouve sur la rangée du milieu, du côté le plus proche du slot pour carte SD, à l'opposé des ports USB et de la prise Ethernet.

    ![Le capteur GPS Grove connecté à la prise UART](../../../../../translated_images/fr/pi-gps-sensor.1f99ee2b2f6528915047ec78967bd362e0e4ee0ed594368a3837b9cf9cdaca64.png)

1. Positionnez le capteur GPS de manière à ce que l'antenne attachée ait une visibilité sur le ciel - idéalement près d'une fenêtre ouverte ou à l'extérieur. Il est plus facile d'obtenir un signal clair sans obstacle devant l'antenne.

## Programmer le capteur GPS

Le Raspberry Pi peut maintenant être programmé pour utiliser le capteur GPS connecté.

### Tâche - programmer le capteur GPS

Programmez l'appareil.

1. Allumez le Pi et attendez qu'il démarre.

1. Le capteur GPS dispose de 2 LED : une LED bleue qui clignote lorsque des données sont transmises, et une LED verte qui clignote toutes les secondes lorsqu'il reçoit des données des satellites. Assurez-vous que la LED bleue clignote lorsque vous allumez le Pi. Après quelques minutes, la LED verte devrait clignoter - si ce n'est pas le cas, vous devrez peut-être repositionner l'antenne.

1. Lancez VS Code, soit directement sur le Pi, soit en vous connectant via l'extension Remote SSH.

    > ⚠️ Vous pouvez vous référer [aux instructions pour configurer et lancer VS Code dans la leçon 1 si nécessaire](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Avec les versions plus récentes du Raspberry Pi qui prennent en charge le Bluetooth, il existe un conflit entre le port série utilisé pour le Bluetooth et celui utilisé par le port UART Grove. Pour résoudre ce problème, procédez comme suit :

    1. Depuis le terminal de VS Code, éditez le fichier `/boot/config.txt` en utilisant `nano`, un éditeur de texte intégré au terminal, avec la commande suivante :

        ```sh
        sudo nano /boot/config.txt
        ```

        > Ce fichier ne peut pas être modifié par VS Code car vous devez l'éditer avec des permissions `sudo`, des permissions élevées. VS Code ne fonctionne pas avec ces permissions.

    1. Utilisez les touches de direction pour naviguer jusqu'à la fin du fichier, puis copiez le code ci-dessous et collez-le à la fin du fichier :

        ```ini
        dtoverlay=pi3-miniuart-bt
        dtoverlay=pi3-disable-bt
        enable_uart=1
        ```

        Vous pouvez coller en utilisant les raccourcis clavier normaux de votre appareil (`Ctrl+v` sur Windows, Linux ou Raspberry Pi OS, `Cmd+v` sur macOS).

    1. Enregistrez ce fichier et quittez nano en appuyant sur `Ctrl+x`. Appuyez sur `y` lorsqu'on vous demande si vous voulez enregistrer le tampon modifié, puis appuyez sur `Entrée` pour confirmer que vous voulez écraser `/boot/config.txt`.

        > Si vous faites une erreur, vous pouvez quitter sans enregistrer, puis répéter ces étapes.

    1. Éditez le fichier `/boot/cmdline.txt` dans nano avec la commande suivante :

        ```sh
        sudo nano /boot/cmdline.txt
        ```

    1. Ce fichier contient plusieurs paires clé/valeur séparées par des espaces. Supprimez toutes les paires clé/valeur pour la clé `console`. Elles ressembleront probablement à ceci :

        ```output
        console=serial0,115200 console=tty1 
        ```

        Vous pouvez naviguer jusqu'à ces entrées à l'aide des touches de direction, puis les supprimer en utilisant les touches `del` ou `backspace`.

        Par exemple, si votre fichier original ressemble à ceci :

        ```output
        console=serial0,115200 console=tty1 root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

        La nouvelle version sera :

        ```output
        root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

    1. Suivez les étapes ci-dessus pour enregistrer ce fichier et quitter nano.

    1. Redémarrez votre Pi, puis reconnectez-vous dans VS Code une fois le Pi redémarré.

1. Depuis le terminal, créez un nouveau dossier dans le répertoire personnel de l'utilisateur `pi` appelé `gps-sensor`. Créez un fichier dans ce dossier appelé `app.py`.

1. Ouvrez ce dossier dans VS Code.

1. Le module GPS envoie des données UART via un port série. Installez le package Pip `pyserial` pour communiquer avec le port série depuis votre code Python :

    ```sh
    pip3 install pyserial
    ```

1. Ajoutez le code suivant à votre fichier `app.py` :

    ```python
    import time
    import serial
    
    serial = serial.Serial('/dev/ttyAMA0', 9600, timeout=1)
    serial.reset_input_buffer()
    serial.flush()
    
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    Ce code importe le module `serial` du package Pip `pyserial`. Il se connecte ensuite au port série `/dev/ttyAMA0` - c'est l'adresse du port série utilisé par le Grove Pi Base Hat pour son port UART. Il efface ensuite toutes les données existantes de cette connexion série.

    Ensuite, une fonction appelée `print_gps_data` est définie pour afficher dans la console la ligne qui lui est transmise.

    Ensuite, le code boucle indéfiniment, lisant autant de lignes de texte que possible depuis le port série à chaque itération. Il appelle la fonction `print_gps_data` pour chaque ligne.

    Une fois toutes les données lues, la boucle attend 1 seconde, puis recommence.

1. Exécutez ce code. Vous verrez la sortie brute du capteur GPS, quelque chose comme ceci :

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

    > Si vous obtenez l'une des erreurs suivantes en arrêtant et redémarrant votre code, ajoutez un bloc `try - except` à votre boucle while.

      ```output
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0x93 in position 0: invalid start byte
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0xf1 in position 0: invalid continuation byte
      ```

    ```python
    while True:
        try:
            line = serial.readline().decode('utf-8')
              
            while len(line) > 0:
                print_gps_data()
                line = serial.readline().decode('utf-8')
      
        # There's a random chance the first byte being read is part way through a character.
        # Read another full line and continue.

        except UnicodeDecodeError:
            line = serial.readline().decode('utf-8')

    time.sleep(1)
    ```

> 💁 Vous pouvez trouver ce code dans le dossier [code-gps/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps/pi).

😀 Votre programme pour le capteur GPS a été un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.