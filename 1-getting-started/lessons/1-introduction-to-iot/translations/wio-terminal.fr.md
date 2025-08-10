# Wio Terminal

Le [Wio Terminal de Seeed Studios](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) est un microcontrôleur compatible à l'Arduino, avec WiFi et certains capteurs et actionneurs intégrés, ainsi que des ports pour ajouter plus de capteurs et d'actionneurs, en utilisant un écosystème matériel appelé [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html). 

![Un Wio Terminal Seeed studios](../../../../images/wio-terminal.png)

## Configuration

Pour utiliser votre Wio Terminal, vous devrez installer certains logiciels gratuits sur votre ordinateur. Vous devrez également mettre à jour le micrologiciel Wio Terminal avant de pouvoir le connecter au WiFi.

### Tâche - configuration

Installez le logiciel requis et mettez à jour le micrologiciel.

1. Installez Visual Studio Code (VS Code). C'est de l'éditeur que vous utiliserez pour écrire votre code de périphérique en C/C++. Reportez-vous à la [documentation VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) pour obtenir des instructions sur l'installation de VS Code.

    > 💁 Un autre IDE populaire pour le développement Arduino est l'[Arduino IDE](https://www.arduino.cc/en/software). Si vous êtes déjà familier avec cet outil, vous pouvez l'utiliser à la place de VS Code et PlatformIO, mais les leçons donneront des instructions basées sur l'utilisation de VS Code.

1. Installez l'extension PlatformIO VS Code. C'est d'une extension pour VS Code qui prend en charge la programmation de microcontrôleurs en C/C++. Reportez-vous à la [documentation de l'extension PlatformIO](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=platformio.platformio-ide) pour obtenir des instructions sur l'installation de cette extension dans VS Code. Cette extension dépend de l'extension Microsoft C/C++ pour fonctionner avec le code C et C++, et l'extension C/C++ est installée automatiquement lorsque vous installez PlatformIO.

1. Connectez votre Wio Terminal à votre ordinateur. Le Wio Terminal dispose d'un port USB-C sur le bas et doit être connecté à un port USB de votre ordinateur. Le Wio Terminal est fourni avec un câble USB-C vers USB-A, mais si votre ordinateur ne dispose que de ports USB-C, vous aurez besoin d'un câble USB-C ou d'un adaptateur USB-A vers USB-C.

1. Suivez les instructions de la [documentation Wio Terminal Wiki WiFi Overview](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/) pour configurer votre Wio Terminal et mettre à jour le micrologiciel.

## L'application Hello World

Lorsque l'on commence avec un nouveau langage de programmation ou une nouvelle technologie, il est de tradition de créer une application "Hello World" - une petite application qui affiche quelque chose comme le texte `"Hello World"` pour montrer que tous les outils sont correctement configurés.

L'application Hello World pour le Wio Terminal s'assurera que vous avez correctement installé Visual Studio code avec PlatformIO et configuré pour le développement de microcontrôleurs.

### Créez un projet PlatformIO 

La première étape consiste à créer un nouveau projet à l'aide de PlatformIO configuré pour le Wio Terminal.  

#### Tâche - créer un projet PlatformIO

Créez le projet PlatformIO.

1. Connectez le Wio Terminal à votre ordinateur

1. Lancez VS Code

1. L'icône PlatformIO sera sur la barre de menu latérale :

    ![L'option de menu Platform IO](../../../../images/vscode-platformio-menu.png)

    Sélectionnez cet élément de menu, puis sélectionnez *PIO Home -> Open*

    ![L'option Open Platform IO](../../../../images/vscode-platformio-home-open.png)

1. À partir de l'écran d'accueil, sélectionnez le bouton **+ New Project**

    ![Le bouton de nouveau projet](../../../../images/vscode-platformio-welcome-new-button.png)

1. Configurez le projet dans l'*Assistant de projet* :

    1. Nommez votre projet `nightlight`

    1. Dans le menu déroulant *Board*, tapez `WIO` pour filtrer les cartes et sélectionnez *Seeeduino Wio Terminal*

    1. Laissez le *Framework* en tant que *Arduino*

    1. Laissez la case à cocher *Use default location* cochée ou décochez-la et sélectionnez un emplacement pour votre projet

    1. Sélectionnez le bouton **Finish**

    ![L'assistant de projet terminé](../../../../images/vscode-platformio-nightlight-project-wizard.png)

    PlatformIO téléchargera les composants dont il a besoin pour compiler le code pour le Wio Terminal et créera votre projet. Cela peut prendre quelques minutes.

### Examiner le projet PlatformIO

L'explorateur VS Code affichera un certain nombre de fichiers et de dossiers créés par l'assistant PlatformIO.

#### Dossiers

* `.pio` - ce dossier contient des données temporaires nécessaires à PlatformIO telles que des bibliothèques ou du code compilé. Il est recréé automatiquement s'il est supprimé et vous n'avez pas besoin de l'ajouter au contrôle de code source si vous partagez votre projet sur des sites tels que GitHub.
* `.vscode` - ce dossier contient la configuration utilisée par PlatformIO et VS Code. Il est recréé automatiquement s'il est supprimé et vous n'avez pas besoin de l'ajouter au contrôle de code source si vous partagez votre projet sur des sites tels que GitHub.
* `include` - ce dossier est destiné aux fichiers d'en-tête externes nécessaires lors de l'ajout de bibliothèques supplémentaires à votre code. Vous n'utiliserez pas ce dossier dans aucune de ces leçons.
* `lib` - ce dossier est destiné aux bibliothèques externes que vous souhaitez appeler à partir de votre code. Vous n'utiliserez pas ce dossier dans aucune de ces leçons. 
* `src` - ce dossier contient le code source principal de votre application. Initialement, il contiendra un seul fichier - `main.cpp`.
* `test` - c'est ici que vous mettriez des tests unitaires pour votre code

#### Fichiers

* `main.cpp` - ce fichier dans le dossier `src` contient le point d'entrée de votre application. Ouvrez ce fichier et il contiendra le code suivant :

    ```cpp
    #include <Arduino.h>
    
    void setup() {
      // Mettez votre code de configuration ici, pour exécuter une fois:
    }
    
    void loop() {
      // Mettez votre code principal ici, pour exécuter en boucle: 
    }
    ```

    Lorsque l'appareil démarre, le framework Arduino exécutera la fonction `setup` une fois, puis exécutera la fonction `loop` de manière répétée jusqu'à ce que l'appareil soit éteint.

* `.gitignore` - ce fichier répertorie les fichiers et répertoires à ignorer lors de l'ajout de votre code au contrôle de code source git, comme le téléchargement dans un dépôt sur GitHub.

* `platformio.ini` - ce fichier contient la configuration de votre appareil et de votre application. Ouvrez ce fichier et il contiendra le code suivant :

    ```ini
    [env:seeed_wio_terminal] 
    platform = atmelsam
    board = seeed_wio_terminal
    framework = arduino
    ```

    La section `[env:seeed_wio_terminal]` contient la configuration pour le Wio Terminal. Vous pouvez avoir plusieurs sections `env` afin que votre code puisse être compilé pour plusieurs cartes.

    Les autres valeurs correspondent à la configuration de l'assistant de projet :

  * `platform = atmelsam` définit le matériel que le Wio Terminal utilise (un microcontrôleur basé sur ATSAMD51)
  * `board = seeed_wio_terminal` définit le type de microcontrôleur de la carte (le Wio Terminal)
  * `framework = arduino` définit que ce projet utilise le framework Arduino.

### Écrivez l'application Hello World

Vous êtes maintenant prêt à écrire l'application Hello World.

#### Tâche - écrivez l'application Hello World

Écrivez l'application Hello World. 

1. Ouvrez le fichier `main.cpp` dans VS Code

1. Changez le code pour qu'il corresponde au suivant :

    ```cpp
    #include <Arduino.h>

    void setup()
    {
        Serial.begin(9600);

        while (!Serial)
            ; // Attendre que Serial soit prêt
    
        delay(1000); 
    }
    
    void loop() 
    {
        Serial.println("Hello World"); 
        delay(5000);
    }
    ```

    La fonction `setup` initialise une connexion au port série - dans ce cas, le port USB qui est utilisé pour connecter le Wio Terminal à votre ordinateur. Le paramètre `9600` est le [débit en bauds](https://en.wikipedia.org/wiki/Symbol_rate) (également connu sous le nom de débit symbole), ou la vitesse à laquelle les données seront envoyées sur le port série en bits par seconde. Ce paramètre signifie que 9.600 bits (0 et 1) de données sont envoyés chaque seconde. Il attend ensuite que le port série soit prêt.

    La fonction `loop` envoie la ligne `Hello World !` au port série, de sorte que les caractères de `Hello World !` ainsi qu'un caractère de nouvelle ligne. Il dort ensuite pendant 5.000 millisecondes ou 5 secondes. Après la fin de `loop`, il est exécuté à nouveau, et ainsi de suite tant que le microcontrôleur est sous tension.

1. Mettez votre Wio Terminal en mode de téléversement. Vous devrez le faire à chaque fois que vous téléversez un nouveau code sur l'appareil :

    1. Tirez deux fois rapidement sur l'interrupteur d'alimentation - il reviendra à la position de marche à chaque fois. 

    1. Vérifiez la LED bleue d'état sur le côté droit du port USB. Il devrait clignoter.
    
    [![Vidéo montrant comment mettre le Wio Terminal en mode téléversement](https://img.youtube.com/vi/LeKU_7zLRrQ/0.jpg)](https://youtu.be/LeKU_7zLRrQ)
    
    Cliquez sur l'image ci-dessus pour une vidéo montrant comment faire.

1. Générez et téléversez le code sur le Wio Terminal

    1. Ouvrez la palette de commandes VS Code

    1. Tapez `PlatformIO Upload` pour rechercher l'option de téléversement et sélectionnez *PlatformIO : Upload*

        ![L'option Téléverser PlatformIO dans la palette de commandes](../../../../images/vscode-platformio-upload-command-palette.png)

        PlatformIO génèrera automatiquement le code si nécessaire avant le téléversement.

    1. Le code sera compilé et téléversé vers le Wio Terminal

        > 💁 Si vous utilisez macOS, une notification concernant un *DISQUE NON ÉJECTÉ CORRECTEMENT* apparaîtra. C'est parce que le Wio Terminal est monté comme lecteur dans le cadre du processus de flashage, et il est déconnecté lorsque le code compilé est écrit sur l'appareil. Vous pouvez ignorer cette notification.

    ⚠️ Si vous obtenez des erreurs concernant la non-disponibilité du port de téléversement, assurez-vous d'abord que vous avez connecté le Wio Terminal à votre ordinateur et que vous l'avez allumé à l'aide de l'interrupteur situé sur le côté gauche de l'écran, et réglez-le en mode téléversement. La lumière verte au bas doit être allumée et la lumière bleue doit clignoter. Si vous obtenez toujours l'erreur, tirez l'interrupteur marche/arrêt vers le bas deux fois en succession rapide pour forcer le Wio Terminal en mode téléversement et essayez à nouveau le téléversement.

PlatformIO dispose d'un moniteur série qui peut surveiller les données envoyées via le câble USB depuis le Wio Terminal. Cela vous permet de surveiller les données envoyées par la commande `Serial.println("Hello World");`.  

1. Ouvrez la palette de commandes VS Code

1. Tapez `PlatformIO Serial` pour rechercher l'option Serial Monitor et sélectionnez *PlatformIO : Serial Monitor*

    ![L'option Moniteur série PlatformIO dans la palette de commandes](../../../../images/vscode-platformio-serial-monitor-command-palette.png)

    Un nouveau terminal s'ouvrira et les données envoyées sur le port série seront diffusées dans ce terminal :

    ```output
    > Executing task: platformio device monitor <

    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Hello World
    Hello World
    ```

    `Hello World` s'imprimera dans le moniteur sériel toutes les 5 secondes.  

> 💁 Vous pouvez trouver ce code dans le dossier [code/wio-terminal](code/wio-terminal).

😀 Votre programme « Hello World » a réussi !
