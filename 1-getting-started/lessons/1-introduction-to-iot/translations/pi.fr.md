# Raspberry Pi

Le [Raspberry Pi](https://raspberrypi.org) est un nano-ordinateur monocarte. Vous pouvez y ajouter des capteurs et des actionneurs en utilisant une large gamme d'appareils et d'écosystèmes, et pour ces leçons en utilisant un écosystème matériel appelé [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html). Vous allez coder votre Pi et accéder aux capteurs Grove en utilisant Python.

![Un Raspberry Pi 4](../../../images/raspberry-pi-4.jpg)

## Configuration

Si vous utilisez un Raspberry Pi comme matériel IoT, vous avez deux choix - vous pouvez suivre toutes ces leçons et coder directement sur le Pi, ou vous pouvez vous connecter à distance à un Pi 'sans fils' et coder à partir de votre ordinateur.

Avant de commencer, vous devez également connecter le Grove Base Hat à votre Pi.

### Tâche - configuration

Installez le chapeau de base Grove sur votre Pi et configurez le Pi

1. Connectez le chapeau de base Grove à votre Pi. La prise sur le chapeau s'adapte sur tous les broches GPIO du Pi, glissant jusqu'en bas des broches pour s'asseoir fermement sur la base. Il est placé sur le Pi, couvert sur le chapeau.

    ![Installer le chapeau Grove](../../../images/pi-grove-hat-fitting.gif)

1. Décidez comment vous voulez programmer votre Pi, et accédez à la section correspondante ci-dessous :

    * [Travailler directement sur votre Pi](#travailler-directement-sur-votre-pi)
    * [Accès à distance pour coder le Pi](#accès-à-distance-pour-coder-le-pi)

### Travailler directement sur votre Pi

Si vous voulez travailler directement sur votre Pi, vous pouvez utiliser la version bureau de Raspberry Pi OS et installer tous les outils dont vous avez besoin.

#### Tâche - travailler directement sur votre Pi

Configurez votre Pi pour le développement.

1. Suivez les instructions du [guide de configuration Raspberry Pi](https://projects.raspberrypi.org/en/projects/raspberry-pi-setting-up) pour configurer votre Pi, le connecter à un clavier/souris/moniteur, le connecter à votre réseau WiFi ou Ethernet, et mettre à jour le logiciel.

En programmer le Pi à l'aide des capteurs et actionneurs Grove, vous devrez installer un éditeur pour vous permettre d'écrire le code de l'appareil, et diverses bibliothèques et outils qui interagissent avec le matériel Grove.

1. Après que votre Pi se redémarré, lancez le Terminal en cliquant sur l'icône **Terminal** dans la barre de menu supérieure, ou choisissez *Menu -> Accessoires -> Terminal*

1. Exécutez la commande suivante pour vous assurer que le système d'exploitation et les logiciels installés sont à jour :

    ```sh
    sudo apt update && sudo apt full-upgrade --yes
    ```

1. Exécutez les commandes suivantes pour installer toutes les bibliothèques nécessaires pour le matériel Grove :

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Cela commence par installer Git, ainsi que Pip pour installer des packages Python.

    L'une des fonctionnalités puissantes de Python est la possibilité d'installer des packages [Pip](https://pypi.org) - C'est de packages de code écrits par d'autres personnes et publiés sur l'Internet. Vous pouvez installer un package Pip sur votre ordinateur avec une seule commande, puis utiliser ce package dans votre code.

    Les packages Python Seeed Grove doivent être installés à partir de la source. Ces commandes cloneront le dépôt contenant le code source de ce package, puis l'installeront localement.

    > 💁 Par défaut, lorsque vous installez un package, il est disponible partout sur votre ordinateur, et cela peut entraîner des problèmes de version du package - comme une application dépendant d'une version d'un package qui ne fonctionne plus lorsque vous installez une nouvelle version pour une autre application. Pour contourner ce problème, vous pouvez utiliser un [environnement virtuel Python](https://docs.python.org/3/library/venv.html), essentiellement une copie de Python dans un répertoire dédié, et lorsque vous installez des packages Pip, ils sont installés uniquement dans ce répertoire. Vous n'utiliserez pas d'environnements virtuels lorsque vous utiliserez votre Pi. Le script d'installation Grove installe les packages Python Grove globalement, donc pour utiliser un environnement virtuel, vous devriez configurer un environnement virtuel puis réinstaller manuellement les packages Grove à l'intérieur de cet environnement. Il est plus facile d'utiliser des packages globaux, d'autant plus qu'un grand nombre de développeurs Pi réinitialiseront une carte SD propre pour chaque projet.

    Enfin, cela active l'interface I<sup>2</sup>C.

1. Redémarrez le PI à l'aide du menu ou en exécutant la commande suivante dans le terminal.

    ```sh
    sudo reboot
    ```

1. Après le Pi se redémarre, relancez le Terminal et exécutez la commande suivante pour installer [Visual Studio Code (VS Code)](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) - c'est de l'éditeur que vous utiliserez pour écrire votre code de périphérique en Python.

    ```sh
    sudo apt install code
    ```

    Après l'installation, VS Code sera disponible dans le menu supérieur.

    > 💁 Vous pouvez utiliser n'importe quel IDE ou éditeur Python pour ces leçons si vous avez un outil préféré, mais les leçons donneront des instructions basées sur l'utilisation de VS Code.

1. Installez Pylance. C'est d'une extension pour VS Code qui fournit la prise en charge du langage Python. Reportez-vous à la [documentation de l'extension Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) pour obtenir des instructions sur l'installation de cette extension dans VS Code.

### Accès à distance pour coder le Pi

Au lieu de coder directement sur le Pi, il peut fonctionner «sans fils», qui n'est pas connecté à un clavier/souris/moniteur, et configurer et coder à partir de votre ordinateur, en utilisant Visual Studio Code.

#### Configurer le Pi OS

Pour coder à distance, le Pi OS doit être installé sur une carte SD.

##### Tâche - configurer le Pi OS

Configurez le Pi OS sans fils.

1. Téléchargez le **Raspberry Pi Imager** depuis la [page de téléchargement du logiciel Raspberry Pi OS](https://www.raspberrypi.org/software/) et installez-le

1. Insérez une carte SD dans votre ordinateur, en utilisant un adaptateur si nécessaire

1. Lancez le Raspberry Pi Imager

1. Dans le Raspberry Pi Imager, sélectionnez le bouton **CHOOSE OS**, puis sélectionnez *Raspberry Pi OS (Other)*, suivi de *Raspberry Pi OS Lite (32-bit)*

    ![Le Raspberry Pi Imager avec Raspberry Pi OS Lite sélectionné](../../../images/raspberry-pi-imager.png)

    > 💁 Raspberry Pi OS Lite est une version de Raspberry Pi OS sans interface graphique ni outils basés sur l'interface graphique. Ceux-ci ne sont pas nécessaires pour un Pi sans fils et rendent l'installation plus petite et le démarrage plus rapide.

1. Sélectionnez le bouton **CHOOSE STORAGE**, puis sélectionnez votre carte SD

1. Lancez les **Options avancées** en appuyant sur `Ctrl+Shift+X`. Ces options permettent une pré-configuration du Raspberry Pi OS avant qu'il ne soit créé sur la carte SD.

    1. Cochez la case **Enable SSH**, et définissez un mot de passe pour l'utilisateur `pi`. C'est du mot de passe que vous utiliserez plus tard pour vous connecter au Pi.

    1. Si vous prévoyez de vous connecter au Pi via le WiFi, cochez la case **Configure WiFi**, et entrez votre SSID et mot de passe WiFi, ainsi que la sélection de votre pays WiFi. Vous n'avez pas besoin de le faire si vous utiliserez un câble Ethernet. Assurez-vous que le réseau auquel vous vous connectez est le même que celui de votre ordinateur.

    1. Cochez la case **Set locale settings**, et définissez votre pays et votre fuseau horaire

    1. Sélectionnez le bouton **SAVE**

1. Sélectionnez le bouton **WRITE** pour écrire le système d'exploitation sur la carte SD. Si vous utilisez macOS, il vous sera demandé de saisir votre mot de passe, car l'outil sous-jacent qui écrit les images disque besoins d'accès privilégié.

Le système d'exploitation sera écrit sur la carte SD, et après la fin de l'opération, la carte sera éjectée par le système d'exploitation, et vous serez notifié. Retirez la carte SD de votre ordinateur, insérez-la dans le Pi, démarre le Pi et attendez environ 2 minutes à se démarre correctement.

#### Se connecter au Pi

L'étape suivante consiste à accéder au Pi à distance. Vous pouvez le faire en utilisant `ssh`, qui est disponible sur macOS, Linux et les versions récentes de Windows.

##### Tâche - se connecter au Pi

Accédez au Pi à distance.

1. Lancez un Terminal ou une ligne de commande, et entrez la commande suivante pour vous connecter au Pi :

    ```sh
    ssh pi@raspberrypi.local
    ```

    Si vous êtes sous Windows en utilisant une version antérieure qui n'a pas `ssh` installé, vous pouvez utiliser OpenSSH. Vous pouvez trouver les instructions d'installation dans la [documentation d'installation d'OpenSSH](https://docs.microsoft.com//windows-server/administration/openssh/openssh_install_firstuse?WT.mc_id=academic-17441-jabenn).

1. Cela devrait vous connecter à votre Pi et vous demander le mot de passe.

    Pouvoir trouver des ordinateurs sur votre réseau en utilisant `<hostname>.local` est une fonctionnalité assez récente sous Linux et Windows. Si vous utilisez Linux ou Windows et que vous obtenez des erreurs concernant l'impossibilité de trouver le nom d'hôte, vous devrez installer un logiciel supplémentaire pour activer le réseau ZeroConf (également appelé Bonjour par Apple) :

    1. Si vous utilisez Linux, installez Avahi à l'aide de la commande suivante :

        ```sh
        sudo apt-get install avahi-daemon
        ```

    1. Si vous utilisez Windows, le moyen le plus simple d'activer ZeroConf est d'installer [Bonjour Print Services for Windows](http://support.apple.com/kb/DL999). Vous pouvez également installer [iTunes pour Windows](https://www.apple.com/itunes/download/) pour obtenir une version plus récente de l'outil (qui n'est pas disponible de manière autonome).

    > 💁 Si vous ne pouvez pas vous connecter avec `raspberrypi.local`, vous pouvez alors utiliser l'adresse IP de votre Pi. Reportez-vous à la [documentation sur l'adresse IP Raspberry Pi](https://www.raspberrypi.org/documentation/remote-access/ip-address.md) pour obtenir des instructions sur plusieurs façons d'obtenir l'adresse IP.

1. Entrez le mot de passe défini dans les options avancées du Raspberry Pi Imager

#### Configurer les logiciels sur le Pi

Après d'établir connection au Pi, vous devez vous assurer que le système d'exploitation est à jour et installer diverses bibliothèques et outils qui interagissent avec le matériel Grove.

##### Tâche - configurer les logiciels sur le Pi

Configurez les logiciels installés sur le Pi et installez les bibliothèques Grove.

1. À partir de votre session `ssh`, exécutez la commande suivante pour mettre à jour puis redémarrer le Pi :

    ```sh
    sudo apt update && sudo apt full-upgrade --yes && sudo reboot
    ```

    Le Pi sera mis à jour et redémarré. La session `ssh` se terminera lorsque le Pi redémarrera, laissez-le donc environ 30 secondes, puis reconnectez-vous.

1. À partir de la session `ssh` reconnectée, exécutez les commandes suivantes pour installer toutes les bibliothèques nécessaires pour le matériel Grove :

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Cela commence par installer Git, ainsi que Pip pour installer des packages Python.

    L'une des fonctionnalités puissantes de Python est la possibilité d'installer des packages [Pip](https://pypi.org) - C'est de packages de code écrits par d'autres personnes et publiés sur l'Internet. Vous pouvez installer un package Pip sur votre ordinateur avec une seule commande, puis utiliser ce package dans votre code.

    Les packages Python Seeed Grove doivent être installés à partir de la source. Ces commandes cloneront le dépôt contenant le code source de ce package, puis l'installeront localement.

    > 💁 Par défaut, lorsque vous installez un package, il est disponible partout sur votre ordinateur, et cela peut entraîner des problèmes de version du package - comme une application dépendant d'une version d'un package qui ne fonctionne plus lorsque vous installez une nouvelle version pour une autre application. Pour contourner ce problème, vous pouvez utiliser un [environnement virtuel Python](https://docs.python.org/3/library/venv.html), essentiellement une copie de Python dans un répertoire dédié, et lorsque vous installez des packages Pip, ils sont installés uniquement dans ce répertoire. Vous n'utiliserez pas d'environnements virtuels lorsque vous utiliserez votre Pi. Le script d'installation Grove installe les packages Python Grove globalement, donc pour utiliser un environnement virtuel, vous devriez configurer un environnement virtuel puis réinstaller manuellement les packages Grove à l'intérieur de cet environnement. Il est plus facile d'utiliser des packages globaux, d'autant plus qu'un grand nombre de développeurs Pi réinitialiseront une carte SD propre pour chaque projet.

    Enfin, cela active l'interface I<sup>2</sup>C.

1. Redémarrez le Pi en exécutant la commande suivante :

    ```sh
    sudo reboot
    ```

    La session `ssh` se terminera lorsque le Pi redémarrera. Il n'est pas nécessaire de se reconnecter.

#### Configurer VS Code pour l'accès à distance

Après que le Pi est configuré, vous pouvez vous y connecter à l'aide de Visual Studio Code (VS Code) à votre ordinateur - C'est d'un éditeur de texte gratuit pour développeur que vous utiliserez pour écrire votre code de périphérique en Python.

##### Tâche - Configurer vs code pour l'accès à distance

Installez le logiciel requis et connectez à distance à votre PI.

1. Installez VS Code sur votre ordinateur en suivant la documentation [VS Code](https://code.visualstudio.com?wt.mc_id=academic-17441-jabenn)

1. Suivez les instructions dans le [VS Code à l'aide de la documentation SSH](https://code.visualstudio.com/docs/remote/ssh?wt.mc_id=academic-17441-jabenn) à installer les composants nécessaires

1. En suivant les mêmes instructions, connectez le code VS au PI

1. Après d'établir connection, suivez les [extensions de gestion](https://code.visualstudio.com/docs/remote/ssh#_managing-extensions?WT.mc_id=academic-17441-jabenn) instructions de télécharger [Pylance extension](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) à distance sur le pi

## Hello world

C'est conventionnel au début de l'apprentissage d'un nouveau langage de programmation ou une technologie pour créer une application «Hello World» - une petite application qui publie quelque chose comme le texte «Hello World» «pour montrer que tous les outils sont correctement configurés.

L'application Hello World pour le PI s'assurera que le code Python et Visual Studio est correctement installé.

Cette application sera dans un répertoire appelé `nightlight`, et il sera réutilisé avec un code différent dans des parties ultérieures de cette affectation pour créer l'application Nightlight.

### Tâche - Hello World

Créez l'application Hello World.

1. Lancez VS Code, soit directement sur le PI, soit sur votre ordinateur et connecté au PI à l'aide de l'extension SSH distante

1. Lancez le terminal de code vs en sélectionnant * Terminal -> Nouveau terminal ou en appuyant sur `` Ctrl + `` `. Il s'ouvrira au répertoire domestique des utilisateurs «PI».

1. Exécutez les commandes suivantes pour créer un répertoire pour votre code et créez un fichier python appelé `app.py` à l'intérieur de ce répertoire:

     ```sh
     mkdir Nightlight
     cd nightlight
     touch app.py
     ```

1. Ouvrez ce répertoire dans VS Code en sélectionnant *File -> Open ...* et sélectionner le répertoire *nightlight*, puis sélectionnez **OK**

     ![La boîte de dialogue ouverte du code vs montrant le répertoire de nuit](../../../images/vscode-open-nightlight-remote.png)

1. Ouvrez le fichier `app.py` à partir de l'explorateur de code vs et ajoutez le code suivant:

     ```Python
     print('Hello World!')
     ```

     La fonction `print` imprime tout ce qui lui est transmis à la console.

1. À partir du terminal de code vs, exécutez ce qui suit pour exécuter votre application Python:

     ```sh
     python app.py
     ```

     > 💁 Vous devrez peut-être appeler explicitement `python3` pour exécuter ce code si vous avez installé Python 2 en plus de Python 3 (la dernière version). Si vous avez installé Python2, l'appel «Python» utilisera Python 2 au lieu de Python 3. Par défaut, les dernières versions Raspberry Pi OS ont uniquement installé Python 3.

     La sortie suivante apparaîtra dans le terminal:

     ```output
     pi@raspberrypi:~/nightlight $ python3 app.py
     Hello world!
     ```

> 💁 Vous pouvez trouver ce code dans le dépôt [code/pi] (code/pi).

😀 Votre programme «Hello World» a été un succès!