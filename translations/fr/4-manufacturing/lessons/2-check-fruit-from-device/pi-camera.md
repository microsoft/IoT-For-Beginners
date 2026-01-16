<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c677667095f6133eee418c7e53615d05",
  "translation_date": "2025-08-24T21:29:48+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/pi-camera.md",
  "language_code": "fr"
}
-->
# Capturer une image - Raspberry Pi

Dans cette partie de la leçon, vous allez ajouter un capteur de caméra à votre Raspberry Pi et lire des images à partir de celui-ci.

## Matériel

Le Raspberry Pi nécessite une caméra.

La caméra que vous utiliserez est un [module caméra Raspberry Pi](https://www.raspberrypi.org/products/camera-module-v2/). Cette caméra est conçue pour fonctionner avec le Raspberry Pi et se connecte via un connecteur dédié sur le Pi.

> 💁 Cette caméra utilise le [Camera Serial Interface, un protocole de la Mobile Industry Processor Interface Alliance](https://wikipedia.org/wiki/Camera_Serial_Interface), connu sous le nom de MIPI-CSI. Il s'agit d'un protocole dédié à la transmission d'images.

## Connecter la caméra

La caméra peut être connectée au Raspberry Pi à l'aide d'un câble ruban.

### Tâche - connecter la caméra

![Une caméra Raspberry Pi](../../../../../translated_images/fr/pi-camera-module.4278753c31bd6e757aa2b858be97d72049f71616278cefe4fb5abb485b40a078.png)

1. Éteignez le Raspberry Pi.

1. Connectez le câble ruban fourni avec la caméra à celle-ci. Pour ce faire, tirez doucement sur le clip en plastique noir du support pour qu'il sorte légèrement, puis insérez le câble dans la prise, avec le côté bleu orienté à l'opposé de l'objectif, et les bandes métalliques orientées vers l'objectif. Une fois le câble complètement inséré, repoussez le clip en plastique noir en place.

    Vous pouvez trouver une animation montrant comment ouvrir le clip et insérer le câble dans la [documentation Raspberry Pi pour débuter avec le module caméra](https://projects.raspberrypi.org/en/projects/getting-started-with-picamera/2).

    ![Le câble ruban inséré dans le module caméra](../../../../../translated_images/fr/pi-camera-ribbon-cable.0bf82acd251611c21ac616f082849413e2b322a261d0e4f8fec344248083b07e.png)

1. Retirez le Grove Base Hat du Raspberry Pi.

1. Faites passer le câble ruban à travers la fente pour caméra du Grove Base Hat. Assurez-vous que le côté bleu du câble est orienté vers les ports analogiques étiquetés **A0**, **A1**, etc.

    ![Le câble ruban passant à travers le Grove Base Hat](../../../../../translated_images/fr/grove-base-hat-ribbon-cable.501fed202fcf73b11b2b68f6d246189f7d15d3e4423c572ddee79d77b4632b47.png)

1. Insérez le câble ruban dans le port caméra du Raspberry Pi. Une fois encore, tirez le clip en plastique noir vers le haut, insérez le câble, puis repoussez le clip en place. Le côté bleu du câble doit être orienté vers les ports USB et Ethernet.

    ![Le câble ruban connecté à la prise caméra du Raspberry Pi](../../../../../translated_images/fr/pi-camera-socket-ribbon-cable.a18309920b11800911082ed7aa6fb28e6d9be3a022e4079ff990016cae3fca10.png)

1. Remettez en place le Grove Base Hat.

## Programmer la caméra

Le Raspberry Pi peut maintenant être programmé pour utiliser la caméra à l'aide de la bibliothèque Python [PiCamera](https://pypi.org/project/picamera/).

### Tâche - activer le mode caméra hérité

Malheureusement, avec la sortie de Raspberry Pi OS Bullseye, le logiciel de caméra inclus dans le système d'exploitation a changé, ce qui signifie que par défaut, PiCamera ne fonctionne plus. Un remplacement est en cours de développement, appelé PiCamera2, mais il n'est pas encore prêt à être utilisé.

Pour l'instant, vous pouvez configurer votre Raspberry Pi en mode caméra hérité pour permettre à PiCamera de fonctionner. Le port caméra est également désactivé par défaut, mais l'activation du logiciel de caméra hérité active automatiquement le port.

1. Allumez le Raspberry Pi et attendez qu'il démarre.

1. Lancez VS Code, soit directement sur le Raspberry Pi, soit en vous connectant via l'extension Remote SSH.

1. Exécutez les commandes suivantes depuis votre terminal :

    ```sh
    sudo raspi-config nonint do_legacy 0
    sudo reboot
    ```

    Cela activera un paramètre pour permettre l'utilisation du logiciel de caméra hérité, puis redémarrera le Raspberry Pi pour appliquer ce paramètre.

1. Attendez que le Raspberry Pi redémarre, puis relancez VS Code.

### Tâche - programmer la caméra

Programmez l'appareil.

1. Depuis le terminal, créez un nouveau dossier dans le répertoire personnel de l'utilisateur `pi` appelé `fruit-quality-detector`. Créez un fichier dans ce dossier nommé `app.py`.

1. Ouvrez ce dossier dans VS Code.

1. Pour interagir avec la caméra, vous pouvez utiliser la bibliothèque Python PiCamera. Installez le package Pip correspondant avec la commande suivante :

    ```sh
    pip3 install picamera
    ```

1. Ajoutez le code suivant à votre fichier `app.py` :

    ```python
    import io
    import time
    from picamera import PiCamera
    ```

    Ce code importe certaines bibliothèques nécessaires, y compris la bibliothèque `PiCamera`.

1. Ajoutez le code suivant en dessous pour initialiser la caméra :

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    
    time.sleep(2)
    ```

    Ce code crée un objet PiCamera et définit la résolution à 640x480. Bien que des résolutions plus élevées soient prises en charge (jusqu'à 3280x2464), le classificateur d'images fonctionne sur des images beaucoup plus petites (227x227), il n'est donc pas nécessaire de capturer et d'envoyer des images plus grandes.

    La ligne `camera.rotation = 0` définit la rotation de l'image. Le câble ruban entre par le bas de la caméra, mais si votre caméra est tournée pour mieux pointer vers l'objet que vous souhaitez classifier, vous pouvez modifier cette ligne avec le nombre de degrés de rotation.

    ![La caméra suspendue au-dessus d'une canette](../../../../../translated_images/fr/pi-camera-upside-down.5376961ba31459883362124152ad6b823d5ac5fc14e85f317e22903bd681c2b6.png)

    Par exemple, si vous suspendez le câble ruban de manière à ce qu'il soit au-dessus de la caméra, définissez la rotation à 180 :

    ```python
    camera.rotation = 180
    ```

    La caméra met quelques secondes à démarrer, d'où la ligne `time.sleep(2)`.

1. Ajoutez le code suivant en dessous pour capturer l'image sous forme de données binaires :

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    Ce code crée un objet `BytesIO` pour stocker les données binaires. L'image est lue depuis la caméra sous forme de fichier JPEG et stockée dans cet objet. Cet objet possède un indicateur de position pour savoir où il se trouve dans les données afin que d'autres données puissent être écrites à la fin si nécessaire. La ligne `image.seek(0)` repositionne cet indicateur au début pour que toutes les données puissent être lues plus tard.

1. En dessous, ajoutez le code suivant pour enregistrer l'image dans un fichier :

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    Ce code ouvre un fichier nommé `image.jpg` en écriture, puis lit toutes les données de l'objet `BytesIO` et les écrit dans le fichier.

    > 💁 Vous pouvez capturer l'image directement dans un fichier au lieu d'un objet `BytesIO` en passant le nom du fichier à l'appel `camera.capture`. La raison d'utiliser l'objet `BytesIO` est qu'ultérieurement dans cette leçon, vous pourrez envoyer l'image à votre classificateur d'images.

1. Pointez la caméra vers quelque chose et exécutez ce code.

1. Une image sera capturée et enregistrée sous le nom `image.jpg` dans le dossier actuel. Vous verrez ce fichier dans l'explorateur de VS Code. Sélectionnez le fichier pour afficher l'image. Si elle nécessite une rotation, mettez à jour la ligne `camera.rotation = 0` selon les besoins et prenez une autre photo.

> 💁 Vous pouvez trouver ce code dans le dossier [code-camera/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/pi).

😀 Votre programme de caméra a été un succès !

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.