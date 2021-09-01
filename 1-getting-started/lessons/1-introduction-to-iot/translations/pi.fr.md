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

#### Tâche - travaillez directement sur votre Pi

Configurez votre Pi pour le développement.

1. Suivez les instructions du [Guide de configuration Raspberry Pi](https://projects.raspberrypi.org/en/projects/raspberry-pi-setting-up) pour configurer votre Pi, le connecter à un clavier/souris/moniteur, le connecter à votre réseau WiFi ou ethernet, et mettre à jour le logiciel. Le système d'exploitation que vous souhaitez installer est **Raspberry Pi OS (32 bit)**, il est affiché comme le système d'exploitation recommandé lorsque vous utilisez l'imageur Raspberry Pi pour créer une image de votre carte SD.

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

##### Tâche - configurer le système d'exploitation du Pi

Set up the headless Pi OS.

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

    Being able to find computers on your network by using `<hostname>.local` is a fairly recent addition to Linux and Windows. If you are using Linux or Windows and you get any errors about the Hostname not being found, you will need to install additional software to enable ZeroConf networking (also referred to by Apple as Bonjour):

    1. If you are using Linux, install Avahi using the following command:

        ```sh
        sudo apt-get install avahi-daemon
        ```

    1. If you are using Windows, the easiest way to enable ZeroConf is to install [Bonjour Print Services for Windows](http://support.apple.com/kb/DL999). You can also install [iTunes for Windows](https://www.apple.com/itunes/download/) to get a newer version of the utility (which is not available standalone).

    > 💁 If you cannot connect using `raspberrypi.local`, then you can use the IP address of your Pi. Refer to the [Raspberry Pi IP address documentation](https://www.raspberrypi.org/documentation/remote-access/ip-address.md) for instructions on a number of ways to get the IP address.

1. Enter the password you set in the Raspberry Pi Imager Advanced Options

#### Configure software on the Pi

Once you are connected to the Pi, you need to ensure the OS is up to date, and install various libraries and tools that interact with the Grove hardware.

##### Task - configure software on the Pi

Configure the installed Pi software and install the Grove libraries.

1. From your `ssh` session, run the following command to update then reboot the Pi:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes && sudo reboot
    ```

    The Pi will be updated and rebooted. The `ssh` session will end when the Pi is rebooted, so leave it for about 30 seconds then reconnect.

1. From the reconnected `ssh` session, run the following command to install all the needed libraries for the Grove hardware:

    ```sh
    curl -sL https://github.com/Seeed-Studio/grove.py/raw/master/install.sh | sudo bash -s -
    ```

    One of the powerful features of Python is the ability to install [Pip packages](https://pypi.org) - these are packages of code written by other people and published to the Internet. You can install a Pip package onto your computer with one command, then use that package in your code. This Grove install script will install the Pip packages you will use to work with the Grove hardware from Python.

    > 💁 By default when you install a package it is available everywhere on your computer, and this can lead to problems with package versions - such as one application depending on one version of a package that breaks when you install a new version for a different application. To work around this problem, you can use a [Python virtual environment](https://docs.python.org/3/library/venv.html), essentially a copy of Python in a dedicated folder, and when you install Pip packages they get installed just to that folder. You won't be using virtual environments when using your Pi. The Grove install script installs the Grove Python packages globally, so to use a virtual environment you would need to set up a virtual environment then manually re-install the Grove packages inside that environment. It's easier to just use global packages, especially as a lot of Pi developers will re-flash a clean SD card for each project.

1. Reboot the Pi by running the following command:

    ```sh
    sudo reboot
    ```

    The `ssh` session will end when the Pi is rebooted. There is no need to reconnect.

#### Configure VS Code for remote access

Once the Pi is configured, you can connect to it using Visual Studio Code (VS Code) from your computer - this is a free developer text editor you will be using to write your device code in Python.

##### Task - configure VS Code for remote access

Install the required software and connect remotely to your Pi.

1. Install VS Code on your computer by following the [VS Code documentation](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn)

1. Follow the instructions in the [VS Code Remote Development using SSH documentation](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) to install the components needed

1. Following the same instructions, connect VS Code to the Pi

1. Once connected, follow the [managing extensions](https://code.visualstudio.com/docs/remote/ssh#_managing-extensions?WT.mc_id=academic-17441-jabenn) instructions to install the [Pylance extension](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) remotely onto the Pi

## Hello world

It is traditional when starting out with a new programming language or technology to create a 'Hello World' application - a small application that outputs something like the text `"Hello World"` to show that all the tools are correctly configured.

The Hello World app for the Pi will ensure that you have Python and Visual Studio code installed correctly.

This app will be in a folder called `nightlight`, and it will be re-used with different code in later parts of this assignment to build the nightlight application.

### Task - hello world

Create the Hello World app.

1. Launch VS Code, either directly on the Pi, or on your computer and connected to the Pi using the Remote SSH extension

1. Launch the VS Code Terminal by selecting *Terminal -> New Terminal, or pressing `` CTRL+` ``. It will open to the `pi` users home directory.

1. Run the following commands to create a directory for your code, and create a Python file called `app.py` inside that directory:

    ```sh
    mkdir nightlight
    cd nightlight
    touch app.py
    ```

1. Open this folder in VS Code by selecting *File -> Open...* and selecting the *nightlight* folder, then select **OK**

    ![The VS Code open dialog showing the nightlight folder](../../../images/vscode-open-nightlight-remote.png)

1. Open the `app.py` file from the VS Code explorer and add the following code:

    ```python
    print('Hello World!')
    ```

    The `print` function prints whatever is passed to it to the console.

1. From the VS Code Terminal, run the following to run your Python app:

    ```sh
    python3 app.py
    ```

    > 💁 You need to explicitly call `python3` to run this code just in case you have Python 2 installed in addition to Python 3 (the latest version). If you have Python2 installed then calling `python` will use Python 2 instead of Python 3

    The following output will appear in the terminal:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py
    Hello World!
    ```

> 💁 You can find this code in the [code/pi](code/pi) folder.

😀 Your 'Hello World' program was a success!
