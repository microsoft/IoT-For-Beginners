<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "8ff0d0a1d29832bb896b9c103b69a452",
  "translation_date": "2025-08-24T23:35:56+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/pi.md",
  "language_code": "fr"
}
-->
# Raspberry Pi

Le [Raspberry Pi](https://raspberrypi.org) est un ordinateur monocarte. Vous pouvez ajouter des capteurs et des actionneurs en utilisant une large gamme de dispositifs et d'écosystèmes, et pour ces leçons, nous utiliserons un écosystème matériel appelé [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html). Vous programmerez votre Pi et accéderez aux capteurs Grove en utilisant Python.

![Un Raspberry Pi 4](../../../../../translated_images/fr/raspberry-pi-4.fd4590d308c3d456.webp)

## Configuration

Si vous utilisez un Raspberry Pi comme matériel IoT, vous avez deux options : vous pouvez suivre toutes ces leçons et coder directement sur le Pi, ou vous pouvez vous connecter à distance à un Pi "sans tête" et coder depuis votre ordinateur.

Avant de commencer, vous devez également connecter le Grove Base Hat à votre Pi.

### Tâche - configuration

Installez le Grove Base Hat sur votre Pi et configurez le Pi.

1. Connectez le Grove Base Hat à votre Pi. Le connecteur sur le Hat s'insère sur tous les broches GPIO du Pi, en glissant complètement jusqu'à ce qu'il soit fermement fixé à la base. Il recouvre le Pi.

    ![Installation du Grove Hat](../../../../../images/pi-grove-hat-fitting.gif)

1. Décidez comment vous souhaitez programmer votre Pi, puis dirigez-vous vers la section correspondante ci-dessous :

    * [Travailler directement sur votre Pi](../../../../../1-getting-started/lessons/1-introduction-to-iot)
    * [Accès à distance pour coder sur le Pi](../../../../../1-getting-started/lessons/1-introduction-to-iot)

### Travailler directement sur votre Pi

Si vous souhaitez travailler directement sur votre Pi, vous pouvez utiliser la version desktop de Raspberry Pi OS et installer tous les outils nécessaires.

#### Tâche - travailler directement sur votre Pi

Configurez votre Pi pour le développement.

1. Suivez les instructions du [guide de configuration du Raspberry Pi](https://projects.raspberrypi.org/en/projects/raspberry-pi-setting-up) pour configurer votre Pi, le connecter à un clavier/souris/écran, le connecter à votre réseau WiFi ou Ethernet, et mettre à jour le logiciel.

Pour programmer le Pi en utilisant les capteurs et actionneurs Grove, vous devrez installer un éditeur pour écrire le code des dispositifs, ainsi que diverses bibliothèques et outils qui interagissent avec le matériel Grove.

1. Une fois que votre Pi a redémarré, lancez le Terminal en cliquant sur l'icône **Terminal** dans la barre de menu supérieure, ou choisissez *Menu -> Accessoires -> Terminal*.

1. Exécutez la commande suivante pour vous assurer que le système d'exploitation et les logiciels installés sont à jour :

    ```sh
    sudo apt update && sudo apt full-upgrade --yes
    ```

1. Exécutez les commandes suivantes pour installer toutes les bibliothèques nécessaires au matériel Grove :

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Cela commence par l'installation de Git, ainsi que de Pip pour installer les packages Python.

    Une des fonctionnalités puissantes de Python est la possibilité d'installer des [packages Pip](https://pypi.org) - ce sont des packages de code écrits par d'autres personnes et publiés sur Internet. Vous pouvez installer un package Pip sur votre ordinateur avec une seule commande, puis utiliser ce package dans votre code.

    Les packages Python Grove de Seeed doivent être installés à partir de la source. Ces commandes vont cloner le dépôt contenant le code source de ce package, puis l'installer localement.

    > 💁 Par défaut, lorsque vous installez un package, il est disponible partout sur votre ordinateur, ce qui peut entraîner des problèmes avec les versions des packages - par exemple, une application dépendant d'une version d'un package qui se casse lorsque vous installez une nouvelle version pour une autre application. Pour contourner ce problème, vous pouvez utiliser un [environnement virtuel Python](https://docs.python.org/3/library/venv.html), essentiellement une copie de Python dans un dossier dédié, et lorsque vous installez des packages Pip, ils sont installés uniquement dans ce dossier. Vous n'utiliserez pas d'environnements virtuels avec votre Pi. Le script d'installation Grove installe les packages Python Grove globalement, donc pour utiliser un environnement virtuel, vous devrez configurer un environnement virtuel puis réinstaller manuellement les packages Grove dans cet environnement. Il est plus simple d'utiliser des packages globaux, surtout que de nombreux développeurs Pi re-flashent une carte SD propre pour chaque projet.

    Enfin, cela active l'interface I<sup>2</sup>C.

1. Redémarrez le Pi en utilisant le menu ou en exécutant la commande suivante dans le Terminal :

    ```sh
    sudo reboot
    ```

1. Une fois que le Pi a redémarré, relancez le Terminal et exécutez la commande suivante pour installer [Visual Studio Code (VS Code)](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) - c'est l'éditeur que vous utiliserez pour écrire votre code de dispositif en Python.

    ```sh
    sudo apt install code
    ```

    Une fois installé, VS Code sera disponible dans le menu supérieur.

    > 💁 Vous êtes libre d'utiliser n'importe quel IDE ou éditeur Python pour ces leçons si vous avez un outil préféré, mais les leçons donneront des instructions basées sur l'utilisation de VS Code.

1. Installez Pylance. C'est une extension pour VS Code qui fournit un support pour le langage Python. Consultez la [documentation de l'extension Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) pour les instructions sur l'installation de cette extension dans VS Code.

### Accès à distance pour coder sur le Pi

Plutôt que de coder directement sur le Pi, il peut fonctionner "sans tête", c'est-à-dire non connecté à un clavier/souris/écran, et être configuré et codé depuis votre ordinateur, en utilisant Visual Studio Code.

#### Configurer le système d'exploitation du Pi

Pour coder à distance, le système d'exploitation du Pi doit être installé sur une carte SD.

##### Tâche - configurer le système d'exploitation du Pi

Configurez le système d'exploitation du Pi sans tête.

1. Téléchargez le **Raspberry Pi Imager** depuis la [page des logiciels Raspberry Pi OS](https://www.raspberrypi.org/software/) et installez-le.

1. Insérez une carte SD dans votre ordinateur, en utilisant un adaptateur si nécessaire.

1. Lancez le Raspberry Pi Imager.

1. Depuis le Raspberry Pi Imager, sélectionnez le bouton **CHOOSE OS**, puis sélectionnez *Raspberry Pi OS (Other)*, suivi de *Raspberry Pi OS Lite (32-bit)*.

    ![Le Raspberry Pi Imager avec Raspberry Pi OS Lite sélectionné](../../../../../translated_images/fr/raspberry-pi-imager.24aedeab9e233d84.webp)

    > 💁 Raspberry Pi OS Lite est une version de Raspberry Pi OS qui n'a pas d'interface utilisateur desktop ni d'outils basés sur l'interface utilisateur. Ceux-ci ne sont pas nécessaires pour un Pi sans tête et rendent l'installation plus légère et le temps de démarrage plus rapide.

1. Sélectionnez le bouton **CHOOSE STORAGE**, puis sélectionnez votre carte SD.

1. Lancez les **Options avancées** en appuyant sur `Ctrl+Shift+X`. Ces options permettent une pré-configuration du système d'exploitation Raspberry Pi avant qu'il ne soit écrit sur la carte SD.

    1. Cochez la case **Enable SSH**, et définissez un mot de passe pour l'utilisateur `pi`. C'est le mot de passe que vous utiliserez pour vous connecter au Pi plus tard.

    1. Si vous prévoyez de connecter le Pi via WiFi, cochez la case **Configure WiFi**, et entrez votre SSID WiFi et mot de passe, ainsi que votre pays WiFi. Vous n'avez pas besoin de faire cela si vous utilisez un câble Ethernet. Assurez-vous que le réseau auquel vous vous connectez est le même que celui de votre ordinateur.

    1. Cochez la case **Set locale settings**, et définissez votre pays et fuseau horaire.

    1. Sélectionnez le bouton **SAVE**.

1. Sélectionnez le bouton **WRITE** pour écrire le système d'exploitation sur la carte SD. Si vous utilisez macOS, il vous sera demandé d'entrer votre mot de passe car l'outil sous-jacent qui écrit les images disque nécessite un accès privilégié.

Le système d'exploitation sera écrit sur la carte SD, et une fois terminé, la carte sera éjectée par le système d'exploitation, et vous serez notifié. Retirez la carte SD de votre ordinateur, insérez-la dans le Pi, allumez le Pi et attendez environ 2 minutes pour qu'il démarre correctement.

#### Se connecter au Pi

La prochaine étape consiste à accéder au Pi à distance. Vous pouvez le faire en utilisant `ssh`, qui est disponible sur macOS, Linux et les versions récentes de Windows.

##### Tâche - se connecter au Pi

Accédez au Pi à distance.

1. Lancez un Terminal ou une invite de commande, et entrez la commande suivante pour vous connecter au Pi :

    ```sh
    ssh pi@raspberrypi.local
    ```

    Si vous êtes sous Windows avec une version plus ancienne qui n'a pas `ssh` installé, vous pouvez utiliser OpenSSH. Vous trouverez les instructions d'installation dans la [documentation d'installation d'OpenSSH](https://docs.microsoft.com//windows-server/administration/openssh/openssh_install_firstuse?WT.mc_id=academic-17441-jabenn).

1. Cela devrait vous connecter à votre Pi et demander le mot de passe.

    Pouvoir trouver des ordinateurs sur votre réseau en utilisant `<hostname>.local` est une fonctionnalité assez récente de Linux et Windows. Si vous utilisez Linux ou Windows et que vous obtenez des erreurs concernant le nom d'hôte introuvable, vous devrez installer un logiciel supplémentaire pour activer le réseau ZeroConf (également appelé Bonjour par Apple) :

    1. Si vous utilisez Linux, installez Avahi en utilisant la commande suivante :

        ```sh
        sudo apt-get install avahi-daemon
        ```

    1. Si vous utilisez Windows, le moyen le plus simple d'activer ZeroConf est d'installer [Bonjour Print Services pour Windows](http://support.apple.com/kb/DL999). Vous pouvez également installer [iTunes pour Windows](https://www.apple.com/itunes/download/) pour obtenir une version plus récente de l'utilitaire (qui n'est pas disponible en standalone).

    > 💁 Si vous ne pouvez pas vous connecter en utilisant `raspberrypi.local`, vous pouvez utiliser l'adresse IP de votre Pi. Consultez la [documentation sur l'adresse IP du Raspberry Pi](https://www.raspberrypi.org/documentation/remote-access/ip-address.md) pour des instructions sur plusieurs façons d'obtenir l'adresse IP.

1. Entrez le mot de passe que vous avez défini dans les options avancées du Raspberry Pi Imager.

#### Configurer les logiciels sur le Pi

Une fois connecté au Pi, vous devez vous assurer que le système d'exploitation est à jour, et installer diverses bibliothèques et outils qui interagissent avec le matériel Grove.

##### Tâche - configurer les logiciels sur le Pi

Configurez le logiciel installé sur le Pi et installez les bibliothèques Grove.

1. Depuis votre session `ssh`, exécutez la commande suivante pour mettre à jour puis redémarrer le Pi :

    ```sh
    sudo apt update && sudo apt full-upgrade --yes && sudo reboot
    ```

    Le Pi sera mis à jour et redémarré. La session `ssh` se terminera lorsque le Pi redémarrera, donc attendez environ 30 secondes puis reconnectez-vous.

1. Depuis la session `ssh` reconnectée, exécutez les commandes suivantes pour installer toutes les bibliothèques nécessaires au matériel Grove :

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Cela commence par l'installation de Git, ainsi que de Pip pour installer les packages Python.

    Une des fonctionnalités puissantes de Python est la possibilité d'installer des [packages Pip](https://pypi.org) - ce sont des packages de code écrits par d'autres personnes et publiés sur Internet. Vous pouvez installer un package Pip sur votre ordinateur avec une seule commande, puis utiliser ce package dans votre code.

    Les packages Python Grove de Seeed doivent être installés à partir de la source. Ces commandes vont cloner le dépôt contenant le code source de ce package, puis l'installer localement.

    > 💁 Par défaut, lorsque vous installez un package, il est disponible partout sur votre ordinateur, ce qui peut entraîner des problèmes avec les versions des packages - par exemple, une application dépendant d'une version d'un package qui se casse lorsque vous installez une nouvelle version pour une autre application. Pour contourner ce problème, vous pouvez utiliser un [environnement virtuel Python](https://docs.python.org/3/library/venv.html), essentiellement une copie de Python dans un dossier dédié, et lorsque vous installez des packages Pip, ils sont installés uniquement dans ce dossier. Vous n'utiliserez pas d'environnements virtuels avec votre Pi. Le script d'installation Grove installe les packages Python Grove globalement, donc pour utiliser un environnement virtuel, vous devrez configurer un environnement virtuel puis réinstaller manuellement les packages Grove dans cet environnement. Il est plus simple d'utiliser des packages globaux, surtout que de nombreux développeurs Pi re-flashent une carte SD propre pour chaque projet.

    Enfin, cela active l'interface I<sup>2</sup>C.

1. Redémarrez le Pi en exécutant la commande suivante :

    ```sh
    sudo reboot
    ```

    La session `ssh` se terminera lorsque le Pi redémarrera. Il n'est pas nécessaire de se reconnecter.

#### Configurer VS Code pour un accès à distance

Une fois le Pi configuré, vous pouvez vous connecter à celui-ci en utilisant Visual Studio Code (VS Code) depuis votre ordinateur - c'est un éditeur de texte gratuit pour développeurs que vous utiliserez pour écrire votre code de dispositif en Python.

##### Tâche - configurer VS Code pour un accès à distance

Installez le logiciel requis et connectez-vous à distance à votre Pi.

1. Installez VS Code sur votre ordinateur en suivant la [documentation de VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

1. Suivez les instructions de la [documentation sur le développement à distance avec SSH dans VS Code](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) pour installer les composants nécessaires.

1. En suivant les mêmes instructions, connectez VS Code au Pi.

1. Une fois connecté, suivez les instructions sur la [gestion des extensions](https://code.visualstudio.com/docs/remote/ssh#_managing-extensions?WT.mc_id=academic-17441-jabenn) pour installer l'[extension Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) à distance sur le Pi.

## Bonjour le monde
Il est traditionnel, lorsqu'on débute avec un nouveau langage de programmation ou une nouvelle technologie, de créer une application 'Hello World' - une petite application qui affiche un texte comme `"Hello World"` pour montrer que tous les outils sont correctement configurés.

L'application Hello World pour le Pi permettra de vérifier que Python et Visual Studio Code sont correctement installés.

Cette application sera placée dans un dossier appelé `nightlight`, et elle sera réutilisée avec différents codes dans les parties suivantes de cet exercice pour construire l'application nightlight.

### Tâche - hello world

Créez l'application Hello World.

1. Lancez VS Code, soit directement sur le Pi, soit sur votre ordinateur en vous connectant au Pi via l'extension Remote SSH.

1. Ouvrez le terminal de VS Code en sélectionnant *Terminal -> New Terminal*, ou en appuyant sur `` CTRL+` ``. Le terminal s'ouvrira dans le répertoire personnel de l'utilisateur `pi`.

1. Exécutez les commandes suivantes pour créer un répertoire pour votre code, et créez un fichier Python appelé `app.py` à l'intérieur de ce répertoire :

    ```sh
    mkdir nightlight
    cd nightlight
    touch app.py
    ```

1. Ouvrez ce dossier dans VS Code en sélectionnant *File -> Open...* et en choisissant le dossier *nightlight*, puis cliquez sur **OK**.

    ![La boîte de dialogue d'ouverture de VS Code montrant le dossier nightlight](../../../../../translated_images/fr/vscode-open-nightlight-remote.d3d2a4011e30d535.webp)

1. Ouvrez le fichier `app.py` depuis l'explorateur de VS Code et ajoutez le code suivant :

    ```python
    print('Hello World!')
    ```

    La fonction `print` affiche dans la console tout ce qui lui est passé en argument.

1. Depuis le terminal de VS Code, exécutez la commande suivante pour lancer votre application Python :

    ```sh
    python app.py
    ```

    > 💁 Vous devrez peut-être appeler explicitement `python3` pour exécuter ce code si vous avez Python 2 installé en plus de Python 3 (la dernière version). Si Python 2 est installé, l'appel à `python` utilisera Python 2 au lieu de Python 3. Par défaut, les dernières versions de Raspberry Pi OS n'ont que Python 3 installé.

    La sortie suivante apparaîtra dans le terminal :

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py
    Hello World!
    ```

> 💁 Vous pouvez trouver ce code dans le dossier [code/pi](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/pi).

😀 Votre programme 'Hello World' a été un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction professionnelle réalisée par un humain. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.