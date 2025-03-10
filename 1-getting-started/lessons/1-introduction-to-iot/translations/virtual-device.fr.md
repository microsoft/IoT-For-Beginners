# Ordinateur monocarte virtuel

Au lieu d'acheter un dispositif IoT, ainsi que des capteurs et des actionneurs, vous pouvez utiliser votre ordinateur pour simuler le matériel IoT. Le [projet CounterFit](https://github.com/CounterFit-IoT/CounterFit) vous permet d'exécuter localement une application qui simule du matériel IoT, comme des capteurs et des actionneurs, et d'accéder aux capteurs et aux actionneurs à partir d'un code Python local écrit de la même manière que le code que vous écririez sur un Raspberry Pi en utilisant du matériel physique.


## Configuration

Pour utiliser CounterFit, vous devez installer un logiciel gratuit sur votre ordinateur.

### Tâche

Installez le logiciel requis.

1. Installez Python. Reportez-vous à la page [Python downloads page](https://www.python.org/downloads/) pour obtenir des instructions sur l'installation de la dernière version de Python.

1. Installez Visual Studio Code (VS Code). Il s'agit de l'éditeur que vous utiliserez pour écrire le code de votre dispositif virtuel en Python. Reportez-vous à la [documentation VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) pour obtenir des instructions sur l'installation de VS Code.

    > 💁  Vous êtes libre d'utiliser n'importe quel IDE ou éditeur Python pour ces leçons si vous avez un outil préféré, mais les leçons donneront des instructions basées sur l'utilisation de VS Code.

1. Installez l'extension Pylance de VS Code. Il s'agit d'une extension pour VS Code qui fournit le support du langage Python. Reportez-vous à la [documentation de l'extension Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) pour obtenir des instructions sur l'installation de cette extension dans VS Code.

Les instructions d'installation et de configuration de l'application CounterFit seront données au moment opportun dans les instructions de mission, car elle est installée sur la base de chaque projet.

## Bonjour le monde

Il est traditionnel, lorsqu'on commence à utiliser un nouveau langage de programmation ou une nouvelle technologie, de créer une application "Hello World" - une petite application qui produit quelque chose comme le texte "Hello World" pour montrer que tous les outils sont correctement configurés.

L'application Hello World pour le matériel IoT virtuel s'assurera que les codes Python et Visual Studio sont correctement installés. Elle se connectera également à CounterFit pour les capteurs et actionneurs IoT virtuels. Elle n'utilisera aucun matériel, elle se connectera simplement pour prouver que tout fonctionne.

Cette application sera dans un dossier appelé `nightlight`, et elle sera réutilisée avec un code différent dans les parties ultérieures de ce travail pour construire l'application de veilleuse.

### Configurer un environnement virtuel Python

L'une des puissantes fonctionnalités de Python est la possibilité d'installer des [Pip packages](https://pypi.org). Il s'agit de paquets de code écrits par d'autres personnes et publiés sur Internet. Vous pouvez installer un paquet Pip sur votre ordinateur à l'aide d'une seule commande, puis utiliser ce paquet dans votre code. Vous allez utiliser Pip pour installer un paquetage pour parler à CounterFit.

Par défaut, lorsque vous installez un paquetage, il est disponible partout sur votre ordinateur, ce qui peut entraîner des problèmes avec les versions du paquetage - par exemple, une application dépendant d'une version d'un paquetage qui se casse lorsque vous installez une nouvelle version pour une autre application. Pour contourner ce problème, vous pouvez utiliser un [environnement virtuel Python](https://docs.python.org/3/library/venv.html), essentiellement une copie de Python dans un dossier dédié, et lorsque vous installez les paquets Pip, ils sont installés uniquement dans ce dossier.

> 💁 Si vous utilisez un Raspberry Pi, vous n'avez pas configuré d'environnement virtuel sur ce périphérique pour gérer les paquets Pip, mais vous utilisez des paquets globaux, car les paquets Grove sont installés globalement par le script d'installation.

#### Tâche - configurer un environnement virtuel Python

Configurez un environnement virtuel Python et installez les paquets Pip pour CounterFit.

1. À partir de votre terminal ou de votre ligne de commande, exécutez la commande suivante à l'endroit de votre choix pour créer et naviguer vers un nouveau répertoire :

    ```sh
    mkdir nightlight
    cd nightlight
    ```

1. Exécutez maintenant ce qui suit pour créer un environnement virtuel dans le dossier `.venv`.

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Vous devez appeler explicitement `python3` pour créer l'environnement virtuel au cas où vous auriez installé Python 2 en plus de Python 3 (la dernière version). Si vous avez installé Python 2, l'appel de `python` utilisera Python 2 au lieu de Python 3.

1. Activez l'environnement virtuel :

    * Sous Windows :
        * Si vous utilisez l'Invite de commande, ou l'invite de commande via le Terminal Windows, exécutez :

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Si vous utilisez PowerShell, exécutez :

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * Sous macOS ou Linux, exécutez:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Ces commandes doivent être exécutées à partir du même endroit que celui où vous avez exécuté la commande de création de l'environnement virtuel. Vous n'aurez jamais besoin de naviguer dans le dossier `.venv`, vous devez toujours exécuter la commande d'activation et toutes les commandes pour installer des paquets ou exécuter du code à partir du dossier dans lequel vous étiez lorsque vous avez créé l'environnement virtuel.

1. Une fois l'environnement virtuel activé, la commande `python` par défaut lancera la version de Python qui a été utilisée pour créer l'environnement virtuel. Exécutez la commande suivante pour obtenir la version:

    ```sh
    python --version
    ```

    La sortie devrait contenir les éléments suivants:

    ```output
    (.venv) ➜  nightlight python --version
    Python 3.9.1
    ```

    > 💁 Votre version de Python peut être différente - tant qu'il s'agit de la version 3.6 ou supérieure, tout va bien. Sinon, supprimez ce dossier, installez une version plus récente de Python et réessayez.

1. Exécutez les commandes suivantes pour installer les paquets Pip pour CounterFit. Ces paquets comprennent l'application principale CounterFit ainsi que des cales pour le matériel Grove. Ces cales vous permettent d'écrire du code comme si vous programmiez à l'aide de capteurs et d'actionneurs physiques de l'écosystème Grove, mais connectés à des dispositifs IoT virtuels.

    ```sh
    pip install CounterFit
    pip install counterfit-connection
    pip install counterfit-shims-grove
    ```

    Ces paquets pip ne seront installés que dans l'environnement virtuel, et ne seront pas disponibles en dehors de celui-ci.
### Écrire le code

Une fois que l'environnement virtuel Python est prêt, vous pouvez écrire le code de l'application 'Hello World'.

#### Tâche - écrire le code

Créez une application Python pour imprimer `"Hello World"` à la console.

1. Depuis votre terminal ou votre ligne de commande, exécutez ce qui suit à l'intérieur de l'environnement virtuel pour créer un fichier Python appelé `app.py` :

    * Depuis Windows, exécutez:

        ```cmd
        type nul > app.py
        ```

    * Sous macOS ou Linux, exécutez:

        ```cmd
        touch app.py
        ```

1. Ouvrez le dossier actuel dans VS Code:

    ```sh
    code .
    ```

    > 💁 Si votre terminal retourne `command not found` sous macOS, cela signifie que VS Code n'a pas été ajouté à votre PATH. Vous pouvez ajouter VS Code à votre PATH en suivant les instructions de la section [Lancement depuis la ligne de commande de la documentation VS Code](https://code.visualstudio.com/docs/setup/mac?WT.mc_id=academic-17441-jabenn#_launching-from-the-command-line) et exécuter la commande ensuite. VS Code est installé par défaut dans votre PATH sous Windows et Linux.

1. Lorsque VS Code se lance, il active l'environnement virtuel Python. L'environnement virtuel sélectionné apparaîtra dans la barre d'état inférieure:

    ![Code VS montrant l'environnement virtuel sélectionné](../../../images/vscode-virtual-env.png)

1. Si le terminal VS Code est déjà en cours d'exécution lorsque VS Code démarre, l'environnement virtuel n'y sera pas activé. La chose la plus simple à faire est de tuer le terminal en utilisant le bouton **Kill the active terminal instance** :

    ![Code VS Tuer le bouton d'instance du terminal actif](../../../images/vscode-kill-terminal.png)

    Vous pouvez savoir si l'environnement virtuel est activé sur le terminal car le nom de l'environnement virtuel sera un préfixe sur l'invite du terminal. Par exemple, il peut s'agir de:

    ```sh
    (.venv) ➜  nightlight
    ```

    Si vous n'avez pas `.venv` comme préfixe à l'invite, l'environnement virtuel n'est pas actif dans le terminal.

1. Lancez un nouveau terminal VS Code en sélectionnant *Terminal -> Nouveau terminal, ou en appuyant sur `` CTRL+``. Le nouveau terminal chargera l'environnement virtuel, et l'invite pour l'activer apparaîtra dans le terminal. L'invite aura également le nom de l'environnement virtuel (`.venv`):

    ```output
    ➜  nightlight source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Ouvrez le fichier `app.py` depuis l'explorateur de code VS et ajoutez le code suivant:

    ```python
    print('Hello World!')
    ```

    La fonction `print` imprime sur la console ce qui lui est passé.

1. Depuis le terminal VS Code, exécutez ce qui suit pour lancer votre application Python:

    ```sh
    python app.py
    ```

    Les éléments suivants figureront dans la sortie:

    ```output
    (.venv) ➜  nightlight python app.py 
    Hello World!
    ```

😀 Votre programme "Hello World" a été un succès!

### Connectez le "matériel".

Dans un deuxième temps, vous allez exécuter l'application CounterFit et y connecter votre code. C'est l'équivalent virtuel de la connexion d'un matériel IoT à un kit de développement.

#### Tâche - connecter le "matériel".

1. Depuis le terminal VS Code, lancez l'application CounterFit avec la commande suivante:

    ```sh
    counterfit
    ```

    L'application commencera à fonctionner et s'ouvrira dans votre navigateur web:

    ![L'application Counter Fit fonctionnant dans un navigateur](../../../images/counterfit-first-run.png)

    Il sera marqué comme *Déconnecté*, avec la LED dans le coin supérieur droit éteinte.

1. Ajoutez le code suivant au début du fichier `app.py`:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

    Ce code importe la classe `CounterFitConnection` du module `counterfit_connection`, qui provient du paquet pip `counterfit-connection` que vous avez installé précédemment. Il initialise ensuite une connexion à l'application CounterFit qui tourne sur `127.0.0.1`, qui est une adresse IP que vous pouvez toujours utiliser pour accéder à votre ordinateur local (souvent appelé *localhost*), sur le port 5000.

    > 💁 Si vous avez d'autres applications fonctionnant sur le port 5000, vous pouvez changer cela en mettant à jour le port dans le code, et en exécutant CounterFit en utilisant `CounterFit --port <numéro_port>`, en remplaçant `<numéro_port>` par le port que vous voulez utiliser.

1. Vous devrez lancer un nouveau terminal VS Code en sélectionnant le bouton **Créer un nouveau terminal intégré**. Ceci est dû au fait que l'application CounterFit fonctionne dans le terminal actuel.

    ![Code VS Créer un nouveau bouton de terminal intégré](../../../images/vscode-new-terminal.png)

1. Dans ce nouveau terminal, exécutez le fichier `app.py` comme précédemment. Le statut de CounterFit passera à **Connected** et la LED s'allumera.

    ![Counter Fit apparaît comme connecté](../../../images/counterfit-connected.png)

> 💁 Vous pouvez trouver ce code dans le dossier[code/virtual-device](code/virtual-device).

😀 Votre connexion au matériel a été un succès!
