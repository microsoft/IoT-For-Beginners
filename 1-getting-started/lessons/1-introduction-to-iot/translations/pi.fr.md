# Raspberry Pi

Le [Raspberry Pi](https://raspberrypi.org) est un ordinateur monocarte. Vous pouvez ajouter des capteurs et des actionneurs en utilisant un large éventail de dispositifs et d'écosystèmes, et pour ces leçons, en utilisant un écosystème matériel appelé [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html). Vous allez coder votre Pi et accéder aux capteurs Grove en utilisant Python.

![Raspberry Pi 4](../../../../images/raspberry-pi-4.jpg)

## Configuration

Si vous utilisez un Raspberry Pi comme matériel IoT, vous avez deux possibilités : vous pouvez suivre toutes ces leçons et coder directement sur le Pi, ou vous pouvez vous connecter à distance à un Pi "sans tête" et coder depuis votre ordinateur.

Avant de commencer, vous devez également connecter le module Grove de base à votre Pi.

### Tâche - configuration

Installez le module de base Grove sur votre Pi et configurez le Pi.

1. Connectez le module de base Grove à votre Pi. La prise du module s'adapte à toutes les broches GPIO du Pi, en glissant tout le long des broches pour s'asseoir fermement sur la base. Il se place sur le Pi, le recouvrant.

    ![Ajustement du module Grove](../../../../images/pi-grove-hat-fitting.gif)

1. Décidez de la façon dont vous voulez programmer votre Pi, puis passez à la section correspondante ci-dessous:

    * [Travaillez directement sur votre Pi](#work-directly-on-your-pi)
    * [Accès à distance pour coder le Pi](#remote-access-to-code-the-pi)

### Travaillez directement sur votre Pi

Si vous souhaitez travailler directement sur votre Pi, vous pouvez utiliser la version de bureau du Raspberry Pi OS et installer tous les outils dont vous avez besoin.

#### Tâche - Travaillez directement sur votre Pi

Configurez votre Pi pour le développement.

1. Suivez les instructions du [Guide de configuration Raspberry Pi](https://projects.raspberrypi.org/en/projects/raspberry-pi-setting-up) pour configurer votre Pi, le connecter à un clavier/souris/moniteur, le connecter à votre réseau WiFi ou ethernet, et mettre à jour le logiciel. Le système d'exploitation que vous souhaitez installer est **Raspberry Pi OS (32 bit)**, il est affiché comme le système d'exploitation recommandé lorsque vous utilisez le créateur d'image Raspberry Pi pour créer une image de votre carte SD.

Pour programmer le Pi à l'aide des capteurs et actionneurs Grove, vous devrez installer un éditeur qui vous permettra d'écrire le code du périphérique, ainsi que diverses bibliothèques et outils qui interagissent avec le matériel Grove.

1. Une fois que votre Pi a redémarré, lancez le terminal en cliquant sur le bouton **Terminal** dans la barre du menu supérieur, ou choisissez *Menu -> Accessoires -> Terminal*.

1. Exécutez la commande suivante pour vous assurer que le système d'exploitation et les logiciels installés sont à jour :

    ```sh
    sudo apt update && sudo apt full-upgrade --yes
    ```

1. Exécutez la commande suivante pour installer toutes les bibliothèques nécessaires au matériel Grove :

    ```sh
    curl -sL https://github.com/Seeed-Studio/grove.py/raw/master/install.sh | sudo bash -s -
    ```

    L'une des fonctionnalités puissantes de Python est la possibilité d'installer [Paquet pip](https://pypi.org) - Il s'agit de paquets de code écrits par d'autres personnes et publiés sur Internet. Vous pouvez installer un paquet Pip sur votre ordinateur à l'aide d'une commande, puis utiliser ce paquet dans votre code. Ce script d'installation Grove installera les paquets Pip que vous utiliserez pour travailler avec le matériel Grove à partir de Python.

    > 💁 Par défaut, lorsque vous installez un paquet, il est disponible partout sur votre ordinateur, ce qui peut entraîner des problèmes avec les versions des paquets - par exemple, une application dépendant d'une version d'un paquet qui se casse lorsque vous installez une nouvelle version pour une autre application. Pour contourner ce problème, vous pouvez utiliser un paquetage [Environnement virtuel Python](https://docs.python.org/3/library/venv.html), essentiellement une copie de Python dans un dossier dédié, et lorsque vous installez les paquets Pip, ils sont installés uniquement dans ce dossier. Vous n'utiliserez pas d'environnements virtuels lorsque vous utiliserez votre Pi. Le script d'installation de Grove installe les paquets Python Grove de manière globale. Pour utiliser un environnement virtuel, vous devrez donc configurer un environnement virtuel, puis réinstaller manuellement les paquets Grove dans cet environnement. Il est plus facile d'utiliser les paquets globaux, d'autant plus que de nombreux développeurs de Pi re-flashent une carte SD propre pour chaque projet.

1. Redémarrez le Pi en utilisant le menu ou en exécutant la commande suivante dans le Terminal :

    ```sh
    sudo reboot
    ```

1. Une fois que le Pi a redémarré, relancez le terminal et exécutez la commande suivante pour l'installer [Visual Studio Code (VS Code)](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) - il s'agit de l'éditeur que vous utiliserez pour écrire le code de votre dispositif en Python.

    ```sh
    sudo apt install code
    ```

    Une fois installé, VS Code sera disponible dans le menu supérieur.

    > 💁 Vous êtes libre d'utiliser n'importe quel IDE ou éditeur Python pour ces leçons si vous avez un outil préféré, mais les leçons donneront des instructions basées sur l'utilisation de VS Code.

1. Installez Pylance. Il s'agit d'une extension pour VS Code qui fournit le support du langage Python. Référez-vous à la [documentation d'extension Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) pour obtenir des instructions sur l'installation de cette extension dans VS Code.

### Accès à distance pour coder le Pi

Plutôt que de coder directement sur le Pi, il peut fonctionner "sans tête", c'est-à-dire sans être connecté à un clavier/souris/moniteur, et configurer et coder sur lui depuis votre ordinateur, en utilisant Visual Studio Code.

#### Configurer le système d'exploitation du Pi

Pour coder à distance, le système d'exploitation du Pi doit être installé sur une carte SD.

##### Tâche - Configurer le système d'exploitation du Pi

Configurer l'OS Pi sans tête.

1. Télécharger le **Créateur d'image Raspberry Pi** à partir de [Page du logiciel Raspberry Pi OS](https://www.raspberrypi.org/software/) et installer le.

1. Insérez une carte SD dans votre ordinateur, en utilisant un adaptateur si nécessaire.

1. Lancer le créateur d'image Raspberry Pi

1. Dans le créateur d'image Raspberry Pi, appuyer sur le bouton **CHOOSE OS** , puis sélectionnez *Raspberry Pi OS (Other)*, suivi de *Raspberry Pi OS Lite (32-bit)*.

    ![Le créateur d'image Raspberry Pi avec Raspberry Pi OS Lite sélectionné](../../../../images/raspberry-pi-imager.png)

    > 💁 Raspberry Pi OS Lite est une version de Raspberry Pi OS qui n'a pas d'interface utilisateur de bureau ou d'outils basés sur l'interface utilisateur. Ceux-ci ne sont pas nécessaires pour un Pi sans tête et rendent l'installation plus petite et le temps de démarrage plus rapide.

1. Sélectionner le bouton **CHOOSE STORAGE**, puis sélectionnez votre carte SD

1. Lancer le **Advanced Options** en appuyant sur `Ctrl+Shift+X`. Ces options permettent une certaine pré-configuration du système d'exploitation du Raspberry Pi avant qu'il ne soit imagé sur la carte SD.

    1. Cochez la case **Enable SSH**, et définissez un mot de passe pour l'utilisateur `pi`. Il s'agit du mot de passe que vous utiliserez plus tard pour vous connecter au Pi.

    1. Si vous prévoyez de vous connecter au Pi via le WiFi, cochez la case **Configurer le WiFi** et saisissez votre SSID et votre mot de passe WiFi, ainsi que la sélection de votre pays WiFi. Vous n'avez pas besoin de faire cela si vous utilisez un câble Ethernet. Assurez-vous que le réseau auquel vous vous connectez est le même que celui de votre ordinateur.

    1. Cochez la case **Set locale settings**, puis définissez votre pays et votre fuseau horaire.

    1. Sélectionnez le bouton **SAVE**.

1. Sélectionnez le bouton **WRITE** pour mettre le système d'exploitation sur la carte SD. Si vous utilisez macOS, il vous sera demandé de saisir votre mot de passe, car l'outil sous-jacent qui écrit les images disque nécessite un accès privilégié.

Le système d'exploitation sera écrit sur la carte SD, et une fois terminé, la carte sera éjectée par le système d'exploitation, et vous en serez informé. Retirez la carte SD de votre ordinateur, insérez-la dans le Pi, allumez le Pi et attendez environ 2 minutes pour qu'il démarre correctement.

#### Connectez-vous au Pi

L'étape suivante consiste à accéder à distance au Pi. Vous pouvez le faire en utilisant `ssh`, qui est disponible sur macOS, Linux et les versions récentes de Windows.

##### Tâche - se connecter au Pi

Accéder à distance au Pi.

1. Lancez un terminal ou une invite de commande, et entrez la commande suivante pour vous connecter au Pi:

    ```sh
    ssh pi@raspberrypi.local
    ```

    Si vous êtes sous Windows et que vous utilisez une ancienne version qui n'a pas installé `ssh`, vous pouvez utiliser OpenSSH. Vous pouvez trouver les instructions d'installation dans la [documentation d'installation d'OpenSSH](https://docs.microsoft.com//windows-server/administration/openssh/openssh_install_firstuse?WT.mc_id=academic-17441-jabenn).

1. Cela devrait se connecter à votre Pi et vous demander le mot de passe.

    Pouvoir trouver des ordinateurs sur votre réseau en utilisant `<hostname>.local` est un ajout assez récent à Linux et Windows. Si vous utilisez Linux ou Windows et que vous obtenez des erreurs concernant le nom d'hôte introuvable, vous devrez installer un logiciel supplémentaire pour activer le réseau ZeroConf (également appelé Bonjour par Apple) :

    1. Si vous utilisez Linux, installez Avahi en utilisant la commande suivante :

        ```sh
        sudo apt-get install avahi-daemon
        ```

    1. Si vous utilisez Windows, le moyen le plus simple d'activer ZeroConf est d'installer [Bonjour Print Services for Windows](http://support.apple.com/kb/DL999). Vous pouvez également installer [iTunes pour Windows](https://www.apple.com/itunes/download/) pour obtenir une version plus récente de l'utilitaire (qui n'est pas disponible en version autonome).

    > 💁 Si vous ne pouvez pas vous connecter en utilisant `raspberrypi.local`, alors vous pouvez utiliser l'adresse IP de votre Pi. Reportez-vous à la [documentation sur l'adresse IP de Raspberry Pi](https://www.raspberrypi.org/documentation/remote-access/ip-address.md) pour obtenir des instructions sur les différentes manières d'obtenir l'adresse IP.

1. Saisissez le mot de passe que vous avez défini dans les options avancées du créateur d'image Raspberry Pi

#### Configurer le logiciel sur le Pi

Une fois que vous êtes connecté au Pi, vous devez vous assurer que le système d'exploitation est à jour et installer diverses bibliothèques et outils qui interagissent avec le matériel Grove.

##### Tâche - configurer le logiciel sur le Pi

Configurez les logiciels installés sur le Pi et installez les bibliothèques Grove.

1. Depuis votre session `ssh`, exécutez la commande suivante pour mettre à jour puis redémarrer le Pi :

    ```sh
    sudo apt update && sudo apt full-upgrade --yes && sudo reboot
    ```

    Le Pi sera mis à jour et redémarré. La session `ssh` se terminera lorsque le Pi sera redémarré, alors laissez-la pendant environ 30 secondes puis reconnectez-vous.

1. Depuis la session `ssh` reconnectée, exécutez la commande suivante pour installer toutes les bibliothèques nécessaires au matériel Grove :

    ```sh
    curl -sL https://github.com/Seeed-Studio/grove.py/raw/master/install.sh | sudo bash -s -
    ```

    L'une des puissantes fonctionnalités de Python est la possibilité d'installer des [Paquets Pip](https://pypi.org). Il s'agit de paquets de code écrits par d'autres personnes et publiés sur Internet. Vous pouvez installer un paquet Pip sur votre ordinateur à l'aide d'une commande, puis utiliser ce paquet dans votre code. Ce script d'installation Grove installera les paquets Pip que vous utiliserez pour travailler avec le matériel Grove à partir de Python.


    > 💁 Par défaut, lorsque vous installez un paquet, il est disponible partout sur votre ordinateur, ce qui peut entraîner des problèmes avec les versions des paquets - par exemple, une application dépendant d'une version d'un paquet qui se casse lorsque vous installez une nouvelle version pour une autre application. Pour contourner ce problème, vous pouvez utiliser un [environnement virtuel Python](https://docs.python.org/3/library/venv.html), essentiellement une copie de Python dans un dossier dédié, et lorsque vous installez les paquets Pip, ils sont installés uniquement dans ce dossier. Vous n'utiliserez pas d'environnement virtuel lorsque vous utiliserez votre Pi. Le script d'installation de Grove installe les paquets Python de Grove de manière globale. Pour utiliser un environnement virtuel, vous devrez donc configurer un environnement virtuel, puis réinstaller manuellement les paquets Grove dans cet environnement. Il est plus facile d'utiliser les paquets globaux, d'autant plus que de nombreux développeurs de Pi re-flashent une carte SD propre pour chaque projet.


1. Redémarrez le Pi en exécutant la commande suivante :

    ```sh
    sudo reboot
    ```

    La session `ssh` se terminera lorsque le Pi sera redémarré. Il n'est pas nécessaire de se reconnecter.

#### Configurer VS Code pour l'accès à distance

Une fois le Pi configuré, vous pouvez vous y connecter à l'aide de Visual Studio Code (VS Code) depuis votre ordinateur. Il s'agit d'un éditeur de texte gratuit pour développeurs que vous utiliserez pour écrire le code de votre appareil en Python.

##### Tâche - Configurer VS Code pour l'accès à distance

Installez le logiciel requis et connectez-vous à distance à votre Pi

1. Installez VS Code sur votre ordinateur en suivant la [documentation VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

1. Suivez les instructions de la [documentation VS Code Développement à distance par SSH](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) pour installer les composants nécessaires.

1. En suivant les mêmes instructions, connectez VS Code au Pi

1. Une fois connecté, suivez les instructions de [gestion des extensions](https://code.visualstudio.com/docs/remote/ssh#_managing-extensions?WT.mc_id=academic-17441-jabenn) pour installer l'[extension Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) à distance sur le Pi

## Bonjour le monde

Il est traditionnel, lorsqu'on débute avec un nouveau langage de programmation ou une nouvelle technologie, de créer une application "Hello World" - une petite application qui produit quelque chose comme le texte "Hello World" pour montrer que tous les outils sont correctement configurés.

L'application 'Hello World' pour le Pi vous permettra de vérifier que vous avez installé correctement le code Python et Visual Studio.

Cette application sera dans un dossier appelé `nightlight`, et elle sera réutilisée avec un code différent dans les parties ultérieures de ce travail pour construire l'application de veilleuse.

### Tâche - Bonjour le monde

Créez l'application 'Hello World'.

1. Lancez VS Code, soit directement sur le Pi, soit sur votre ordinateur et connecté au Pi en utilisant l'extension SSH à distance.

1. Lancez le terminal VS Code en sélectionnant *Terminal -> Nouveau terminal, ou en appuyant sur `` CTRL+``. Il s'ouvrira sur le répertoire personnel de l'utilisateur du `pi`.

1. Exécutez les commandes suivantes pour créer un répertoire pour votre code, et créez un fichier Python appelé `app.py` dans ce répertoire :

    ```sh
    mkdir nightlight
    cd nightlight
    touch app.py
    ```

1. Ouvrez ce dossier dans VS Code en sélectionnant *File -> Open...* et en sélectionnant le dossier *nightlight*, puis sélectionnez **OK**.

    ![Le dialogue d'ouverture de VS Code montrant le dossier nightlight](../../../../images/vscode-open-nightlight-remote.png)

1. Ouvrez le fichier `app.py` depuis l'explorateur de code VS et ajoutez le code suivant :

    ```python
    print('Hello World!')
    ```

    La fonction `print` affiche sur la console ce qui lui est passé.

1. Depuis le terminal VS Code, exécutez ce qui suit pour lancer votre application Python :

    ```sh
    python3 app.py
    ```

    > 💁 Vous devez appeler explicitement `python3` pour exécuter ce code au cas où vous auriez installé Python 2 en plus de Python 3 (la dernière version). Si vous avez installé Python 2, l'appel à `python` utilisera Python 2 au lieu de Python 3.

    La sortie suivante apparaîtra dans le terminal:

    ``sortie
    pi@raspberrypi:~/nightlight $ python3 app.py
    Bonjour le monde !
    ```

> 💁 Vous pouvez trouver ce code dans le dossier [code/pi](code/pi).

😀 Votre programme "Hello World" a été un succès !
