# Ordinateur monocarte virtuel

Au lieu d'acheter un appareil IoT avec des capteurs et des actionneurs, vous pouvez utiliser votre ordinateur pour simuler du matériel IoT. Le projet [CounterFit](https://github.com/CounterFit-IoT/CounterFit) vous permet d'exécuter une application localement qui simule du matériel IoT tel que des capteurs et des actionneurs, et d'accéder à ces capteurs et actionneurs depuis du code Python local, écrit de la même manière que le code que vous écririez sur un Raspberry Pi avec du matériel physique.

## Configuration

Pour utiliser CounterFit, vous devrez installer quelques logiciels gratuits sur votre ordinateur.

### Tâche

Installez les logiciels nécessaires.

1. Installez Python. Consultez la [page de téléchargement de Python](https://www.python.org/downloads/) pour obtenir des instructions sur l'installation de la dernière version de Python.

1. Installez Visual Studio Code (VS Code). C'est l'éditeur que vous utiliserez pour écrire le code de votre appareil virtuel en Python. Consultez la [documentation de VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) pour obtenir des instructions sur l'installation de VS Code.

    > 💁 Vous êtes libre d'utiliser n'importe quel IDE ou éditeur Python pour ces leçons si vous avez un outil préféré, mais les leçons fourniront des instructions basées sur l'utilisation de VS Code.

1. Installez l'extension Pylance pour VS Code. Il s'agit d'une extension pour VS Code qui offre un support pour le langage Python. Consultez la [documentation de l'extension Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) pour obtenir des instructions sur l'installation de cette extension dans VS Code.

Les instructions pour installer et configurer l'application CounterFit seront données au moment opportun dans les instructions de l'exercice, car elle est installée projet par projet.

## Hello World

Il est traditionnel, lorsque l'on débute avec un nouveau langage de programmation ou une nouvelle technologie, de créer une application 'Hello World' - une petite application qui affiche un texte tel que `"Hello World"` pour montrer que tous les outils sont correctement configurés.

L'application Hello World pour le matériel IoT virtuel permettra de vérifier que Python et Visual Studio Code sont correctement installés. Elle se connectera également à CounterFit pour les capteurs et actionneurs IoT virtuels. Elle n'utilisera aucun matériel, elle se connectera simplement pour prouver que tout fonctionne.

Cette application sera placée dans un dossier appelé `nightlight`, et elle sera réutilisée avec différents codes dans les parties ultérieures de cet exercice pour construire l'application de veilleuse.

### Configurer un environnement virtuel Python

L'une des fonctionnalités puissantes de Python est la possibilité d'installer des [packages Pip](https://pypi.org) - ce sont des packages de code écrits par d'autres personnes et publiés sur Internet. Vous pouvez installer un package Pip sur votre ordinateur avec une seule commande, puis utiliser ce package dans votre code. Vous utiliserez Pip pour installer un package permettant de communiquer avec CounterFit.

Par défaut, lorsque vous installez un package, il est disponible partout sur votre ordinateur, ce qui peut entraîner des problèmes de versions de packages - par exemple, une application dépendant d'une version d'un package qui cesse de fonctionner lorsque vous installez une nouvelle version pour une autre application. Pour contourner ce problème, vous pouvez utiliser un [environnement virtuel Python](https://docs.python.org/3/library/venv.html), qui est essentiellement une copie de Python dans un dossier dédié, et lorsque vous installez des packages Pip, ils sont installés uniquement dans ce dossier.

> 💁 Si vous utilisez un Raspberry Pi, vous n'avez pas configuré d'environnement virtuel sur cet appareil pour gérer les packages Pip, vous utilisez des packages globaux, car les packages Grove sont installés globalement par le script d'installation.

#### Tâche - configurer un environnement virtuel Python

Configurez un environnement virtuel Python et installez les packages Pip pour CounterFit.

1. Depuis votre terminal ou ligne de commande, exécutez la commande suivante à l'emplacement de votre choix pour créer et naviguer vers un nouveau répertoire :

    ```sh
    mkdir nightlight
    cd nightlight
    ```

1. Exécutez maintenant la commande suivante pour créer un environnement virtuel dans le dossier `.venv` :

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Vous devez explicitement appeler `python3` pour créer l'environnement virtuel au cas où vous auriez Python 2 installé en plus de Python 3 (la dernière version). Si vous avez Python 2 installé, appeler `python` utilisera Python 2 au lieu de Python 3.

1. Activez l'environnement virtuel :

    * Sur Windows :
        * Si vous utilisez l'invite de commande ou l'invite de commande via Windows Terminal, exécutez :

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Si vous utilisez PowerShell, exécutez :

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

            > Si vous obtenez une erreur indiquant que l'exécution de scripts est désactivée sur ce système, vous devrez activer l'exécution de scripts en définissant une politique d'exécution appropriée. Vous pouvez le faire en lançant PowerShell en tant qu'administrateur, puis en exécutant la commande suivante :

            ```powershell
            Set-ExecutionPolicy -ExecutionPolicy Unrestricted
            ```

            Entrez `Y` lorsque vous êtes invité à confirmer. Relancez ensuite PowerShell et réessayez.

            Vous pouvez réinitialiser cette politique d'exécution à une date ultérieure si nécessaire. Vous pouvez en savoir plus à ce sujet dans la [page sur les politiques d'exécution de Microsoft Docs](https://docs.microsoft.com/powershell/module/microsoft.powershell.core/about/about_execution_policies?WT.mc_id=academic-17441-jabenn).

    * Sur macOS ou Linux, exécutez :

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Ces commandes doivent être exécutées depuis le même emplacement où vous avez exécuté la commande pour créer l'environnement virtuel. Vous n'aurez jamais besoin de naviguer dans le dossier `.venv`, vous devez toujours exécuter la commande d'activation et toute commande pour installer des packages ou exécuter du code depuis le dossier où vous étiez lorsque vous avez créé l'environnement virtuel.

1. Une fois l'environnement virtuel activé, la commande `python` par défaut exécutera la version de Python utilisée pour créer l'environnement virtuel. Exécutez la commande suivante pour obtenir la version :

    ```sh
    python --version
    ```

    La sortie devrait contenir les informations suivantes :

    ```output
    (.venv) ➜  nightlight python --version
    Python 3.9.1
    ```

    > 💁 Votre version de Python peut être différente - tant qu'elle est en version 3.6 ou supérieure, c'est bon. Sinon, supprimez ce dossier, installez une version plus récente de Python et réessayez.

1. Exécutez les commandes suivantes pour installer les packages Pip pour CounterFit. Ces packages incluent l'application principale CounterFit ainsi que des shims pour le matériel Grove. Ces shims vous permettent d'écrire du code comme si vous programmiez avec des capteurs et actionneurs physiques du système Grove, mais connectés à des appareils IoT virtuels.

    ```sh
    pip install CounterFit
    pip install counterfit-connection
    pip install counterfit-shims-grove
    ```

    Ces packages Pip seront uniquement installés dans l'environnement virtuel et ne seront pas disponibles en dehors de celui-ci.

### Écrire le code

Une fois l'environnement virtuel Python prêt, vous pouvez écrire le code pour l'application 'Hello World'.

#### Tâche - écrire le code

Créez une application Python pour afficher `"Hello World"` dans la console.

1. Depuis votre terminal ou ligne de commande, exécutez la commande suivante dans l'environnement virtuel pour créer un fichier Python appelé `app.py` :

    * Sur Windows, exécutez :

        ```cmd
        type nul > app.py
        ```

    * Sur macOS ou Linux, exécutez :

        ```cmd
        touch app.py
        ```

1. Ouvrez le dossier actuel dans VS Code :

    ```sh
    code .
    ```

    > 💁 Si votre terminal retourne `command not found` sur macOS, cela signifie que VS Code n'a pas été ajouté à votre PATH. Vous pouvez ajouter VS Code à votre PATH en suivant les instructions dans la [section Lancer depuis la ligne de commande de la documentation VS Code](https://code.visualstudio.com/docs/setup/mac?WT.mc_id=academic-17441-jabenn#_launching-from-the-command-line) et exécuter la commande ensuite. VS Code est ajouté au PATH par défaut sur Windows et Linux.

1. Lorsque VS Code se lance, il activera l'environnement virtuel Python. L'environnement virtuel sélectionné apparaîtra dans la barre d'état en bas :

    ![VS Code montrant l'environnement virtuel sélectionné](../../../../../translated_images/fr/vscode-virtual-env.8ba42e04c3d533cf.webp)

1. Si le terminal VS Code est déjà en cours d'exécution lorsque VS Code démarre, il n'aura pas l'environnement virtuel activé. La solution la plus simple est de fermer le terminal en utilisant le bouton **Kill the active terminal instance** :

    ![Bouton VS Code Kill the active terminal instance](../../../../../translated_images/fr/vscode-kill-terminal.1cc4de7c6f25ee08.webp)

    Vous pouvez savoir si le terminal a l'environnement virtuel activé car le nom de l'environnement virtuel sera un préfixe sur l'invite du terminal. Par exemple, cela pourrait être :

    ```sh
    (.venv) ➜  nightlight
    ```

    Si vous n'avez pas `.venv` comme préfixe sur l'invite, l'environnement virtuel n'est pas activé dans le terminal.

1. Lancez un nouveau terminal VS Code en sélectionnant *Terminal -> New Terminal*, ou en appuyant sur `` CTRL+` ``. Le nouveau terminal chargera l'environnement virtuel, et l'appel pour l'activer apparaîtra dans le terminal. L'invite aura également le nom de l'environnement virtuel (`.venv`) :

    ```output
    ➜  nightlight source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Ouvrez le fichier `app.py` depuis l'explorateur VS Code et ajoutez le code suivant :

    ```python
    print('Hello World!')
    ```

    La fonction `print` affiche dans la console tout ce qui lui est passé.

1. Depuis le terminal VS Code, exécutez la commande suivante pour exécuter votre application Python :

    ```sh
    python app.py
    ```

    La sortie sera la suivante :

    ```output
    (.venv) ➜  nightlight python app.py 
    Hello World!
    ```

😀 Votre programme 'Hello World' a été un succès !

### Connecter le 'matériel'

Comme deuxième étape 'Hello World', vous allez exécuter l'application CounterFit et connecter votre code à celle-ci. C'est l'équivalent virtuel de brancher du matériel IoT à un kit de développement.

#### Tâche - connecter le 'matériel'

1. Depuis le terminal VS Code, lancez l'application CounterFit avec la commande suivante :

    ```sh
    counterfit
    ```

    L'application commencera à s'exécuter et s'ouvrira dans votre navigateur web :

    ![L'application CounterFit s'exécutant dans un navigateur](../../../../../translated_images/fr/counterfit-first-run.433326358b669b31.webp)

    Elle sera marquée comme *Disconnected*, avec la LED en haut à droite éteinte.

1. Ajoutez le code suivant en haut de `app.py` :

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

    Ce code importe la classe `CounterFitConnection` du module `counterfit_connection`, qui provient du package pip `counterfit-connection` que vous avez installé précédemment. Il initialise ensuite une connexion à l'application CounterFit exécutée sur `127.0.0.1`, qui est une adresse IP que vous pouvez toujours utiliser pour accéder à votre ordinateur local (souvent appelée *localhost*), sur le port 5000.

    > 💁 Si vous avez d'autres applications exécutées sur le port 5000, vous pouvez changer cela en mettant à jour le port dans le code, et en exécutant CounterFit avec `CounterFit --port <port_number>`, en remplaçant `<port_number>` par le port que vous souhaitez utiliser.

1. Vous devrez lancer un nouveau terminal VS Code en sélectionnant le bouton **Create a new integrated terminal**. Cela est dû au fait que l'application CounterFit s'exécute dans le terminal actuel.

    ![Bouton VS Code Create a new integrated terminal](../../../../../translated_images/fr/vscode-new-terminal.77db8fc0f9cd3182.webp)

1. Dans ce nouveau terminal, exécutez le fichier `app.py` comme précédemment. Le statut de CounterFit passera à **Connected** et la LED s'allumera.

    ![CounterFit affichant le statut connecté](../../../../../translated_images/fr/counterfit-connected.ed30b46d8f79b092.webp)

> 💁 Vous pouvez trouver ce code dans le dossier [code/virtual-device](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/virtual-device).

😀 Votre connexion au matériel a été un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction professionnelle réalisée par un humain. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.